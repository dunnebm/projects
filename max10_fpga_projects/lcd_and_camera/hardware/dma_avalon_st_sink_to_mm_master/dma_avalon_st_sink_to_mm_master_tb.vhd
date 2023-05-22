-- Author: Brandon Dunne
-- Description: This testbench tests the dma_avalon_st_sink_to_mm_master
-- component by adjusting the input and output rates to puroposely cause
-- overrun errors. Overrun-error and frame-complete interrupts are enabled/disabled
-- to verify that an irq is only asserted when interrupts are endabled. 

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use ieee.math_real.all;

library osvvm;
use osvvm.CoveragePkg.all;
use osvvm.RandomPkg.all;

use work.queue_pkg.all;

entity dma_avalon_st_sink_to_mm_master_tb is
end entity;

architecture testbench of dma_avalon_st_sink_to_mm_master_tb is

   signal clk: std_logic := '0';
   signal rst: std_logic;

   signal control_status_address: std_logic;
   signal control_status_read_n: std_logic := '1';
   signal control_status_write_n: std_logic := '1';
   signal control_status_readdata: std_logic_vector(31 downto 0);
   signal control_status_writedata: std_logic_vector(31 downto 0);

   signal irq: std_logic;

   signal stream_sink_ready: std_logic;
   signal stream_sink_valid: std_logic := '0';
   signal stream_sink_data: std_logic_vector(10 downto 0);
   
   signal write_master_address: std_logic_vector(31 downto 0);
   signal write_master_write_n: std_logic;
   signal write_master_waitrequest_n: std_logic := '1';
   signal write_master_writedata: std_logic_vector(7 downto 0);

   -- internal signals used only for simulation
   signal fifo_empty: std_logic;
   signal fifo_full: std_logic;
   signal fifo_pop: std_logic;
   signal fifo_push: std_logic;
   signal fifo_packet_in: std_logic_vector(10 downto 0);
   signal fifo_packet_out: std_logic_vector(10 downto 0);
   signal stream_enable: std_logic;
   signal frame_complete: std_logic;
   signal overrun_error: std_logic;
   signal base_addr: std_logic_vector(31 downto 0);

   constant CLK_PERIOD: time := 10 ns;
   constant FRAME_SIZE: integer := 64;

   constant CSR_ADDR: std_logic := '0';
   constant BAR_ADDR: std_logic := '1';
   constant STREAM_ENABLE_BIT: integer := 0;
   constant FRAME_COMPLETE_BIT: integer := 3;
   constant OVERRUN_ERROR_BIT: integer := 4;
   constant FRAME_COMPLETE_IRQ_ENABLE_BIT: integer := 1;
   constant OVERRUN_ERROR_IRQ_ENABLE_BIT: integer := 2;

   shared variable queue: queue_t;
   signal stimulus_packet: packet_t;

   signal control_status_stimulus_request: boolean;
   signal control_status_stimulus_generated: boolean;
   signal stimulus_packet_request: boolean;
   signal stimulus_packet_generated: boolean;
   signal simulation_initialized: boolean := false;
   signal simulation_finished: boolean := false;
   signal write_frame_request: boolean;
   signal frame_written: boolean;
   signal frame_write_checker_active: boolean := false;
   signal overrun_checker_active: boolean := false;
   
   type control_status_stimulus_t is record
      base_addr: integer;
      fc_irq_enable: boolean;
      oe_irq_enable: boolean;
      fifo_input_period: integer;
      fifo_output_period: integer;
   end record;

   signal cs_stimulus: control_status_stimulus_t;

   -- The two signals below are used to adjust the input/output
   -- rate of the FIFO, and will be used to cause an overrun error.
   signal stream_input_delay: integer; -- units of clks
   signal waitrequest_duration: integer; -- units of clks

   shared variable cov: CovPType;

   function boolToStdLogic(bool: boolean) return std_logic is
   begin
      if bool then
         return '1';
      else
         return '0';
      end if;
   end function;

begin

   DUT: entity work.dma_avalon_st_sink_to_mm_master
      port map (
         clk => clk,
         rst => rst,

         control_status_address => control_status_address,
         control_status_read_n => control_status_read_n,
         control_status_write_n => control_status_write_n,
         control_status_readdata => control_status_readdata,
         control_status_writedata => control_status_writedata,

         irq => irq,

         stream_sink_ready => stream_sink_ready,
         stream_sink_valid => stream_sink_valid,
         stream_sink_data => stream_sink_data,
         
         write_master_address => write_master_address,
         write_master_write_n => write_master_write_n,
         write_master_waitrequest_n => write_master_waitrequest_n,
         write_Master_writedata => write_master_writedata,

         -- Internal signals user only for simulation
         sim_fifo_empty => fifo_empty,
         sim_fifo_full => fifo_full,
         sim_fifo_pop => fifo_pop,
         sim_fifo_push => fifo_push,
         sim_fifo_packet_in => fifo_packet_in,
         sim_fifo_packet_out => fifo_packet_out,
         sim_stream_enable => stream_enable,
         sim_frame_complete => frame_complete,
         sim_overrun_error => overrun_error,
         sim_base_addr => base_addr
      );

   clk <= not clk after CLK_PERIOD / 2;
   rst <= '1', '0' after CLK_PERIOD;

   control_status_driver: process
   begin
      wait until rst = '0' and clk = '1';

      -- Bin 1: frame_Complete_irq (enabled, disabled)
      -- Bin 2: overrun_error_irq (enabled, disabled)
      -- Bin 3: FIFO input period (example: a period of 3 means 1 packet is written every 3 cycles)
      -- Bin 4: FIFO output period (example: a period of 3 means 1 packet is read every 3 cycles)
      cov.AddCross(GenBin(0,1),GenBin(0,1),GenBin(1,3),GenBin(1,3));

      while not cov.isCovered loop
         control_status_stimulus_request <= true;
         wait on control_status_stimulus_generated'transaction;

         -- record generated stimuli so these values are not repeated
         cov.ICover((
            boolean'pos(cs_stimulus.fc_irq_enable), 
            boolean'pos(cs_stimulus.oe_irq_enable),
            cs_stimulus.fifo_input_period, 
            cs_stimulus.fifo_output_period)
         );

         -- Set base address: the address that is the write-master resets when
         -- when frame_start or rst is asserted
         control_status_address <= BAR_ADDR;
         control_status_writedata <= std_logic_vector(
            to_unsigned(cs_stimulus.base_addr, control_status_writedata'length));
         control_status_write_n <= '0';

         wait for CLK_PERIOD;

         -- Set enable/disable interrupts depending on stimuli generated,
         -- then enable stream
         control_status_address <= CSR_ADDR;
         control_status_writedata <= (
            FRAME_COMPLETE_IRQ_ENABLE_BIT => boolToStdLogic(cs_stimulus.fc_irq_enable),
            OVERRUN_ERROR_IRQ_ENABLE_BIT => boolToStdLogic(cs_stimulus.oe_irq_enable),
            STREAM_ENABLE_BIT => '1',
            others => '0'
         );
         control_status_write_n <= '0';

         wait for CLK_PERIOD;

         control_status_write_n <= '1';

         wait for CLK_PERIOD;

         --report "fc_irq_enable: " & boolean'image(cs_stimulus.fc_irq_enable);
         --report "oe_irq_enable: " & boolean'image(cs_stimulus.oe_irq_enable);
         --report "fifo_input_period: " & integer'image(cs_stimulus.fifo_input_period);
         --report "fifo_output_period: " & integer'image(cs_stimulus.fifo_output_period);

         write_frame_request <= true;
         wait on frame_written'transaction;
      end loop;

      assert false report "simulation finished" severity failure;
   end process;

   control_status_stimulus_generator: process
      variable rv: RandomPType;
      variable fc_irq_enable: integer;
      variable oe_irq_enable: integer;
      variable fifo_input_period: integer;
      variable fifo_output_period: integer;
   begin
      wait on control_status_stimulus_request'transaction;

      cs_stimulus.base_addr <= rv.RandInt(0, 2**26 - 1);
      (fc_irq_enable, oe_irq_enable, fifo_input_period, fifo_output_period) := cov.RandCovPoint;

      cs_stimulus.fc_irq_enable <= boolean'val(fc_irq_enable);
      cs_stimulus.oe_irq_enable <= boolean'val(oe_irq_enable);
      cs_stimulus.fifo_input_period <= fifo_input_period;
      cs_stimulus.fifo_output_period <= fifo_output_period;
      
      control_status_stimulus_generated <= true;
   end process;

   stream_sink_driver: process
      constant FRAME_SIZE: integer := 32;
      variable stimulus_packet: packet_t;
      variable rv: RandomPType;
   begin
      wait on write_frame_request'transaction;
      wait until clk = '1';

      for i in 0 to FRAME_SIZE loop
         if i = 0 then
            stimulus_packet.frame_start := '1';
            stimulus_packet.frame_end := '0';
            stimulus_packet.data_valid := '1';
         elsif i < FRAME_SIZE then
            stimulus_packet.frame_start := '0';
            stimulus_packet.frame_end := '0';
            stimulus_packet.data_valid := '1';
         else
            stimulus_packet.frame_start := '0';
            stimulus_packet.frame_end := '1';
            stimulus_packet.data_valid := '0';
         end if;
         stimulus_packet.data := rv.randSlv(stimulus_packet.data'length);

         stream_sink_data(10) <= stimulus_packet.frame_start;
         stream_sink_data(9) <= stimulus_packet.frame_end;
         stream_sink_data(8) <= stimulus_packet.data_valid;
         stream_sink_data(7 downto 0) <= stimulus_packet.data;

         -- update the queue to match the expected state of the FIFO
         if stream_enable = '0' then
            queue.clear;
         else
            queue.push(stimulus_packet);
         end if;

         stream_sink_valid <= '1';
         wait for CLK_PERIOD;

         if cs_stimulus.fifo_input_period > 1 then
            stream_sink_valid <= '0';
            wait for (cs_stimulus.fifo_input_period - 1)*CLK_PERIOD;
         end if;
      end loop;
      
      stream_sink_valid <= '0';

      -- do not signal frame_written until the overrun_checker and 
      -- frame_write_checker are inactive.
      while frame_write_checker_active or overrun_checker_active loop
         wait for CLK_PERIOD;
      end loop;

      -- Frame has been written. Ready for a new cs_stimulus
      frame_written <= true;
   end process;

   -- Responsible for asserting a waitrequest when the write-master
   -- asserts write_n
   write_master_driver: process
   begin
      wait until write_master_write_n = '0' and write_master_write_n'stable(0 ns);

      if cs_stimulus.fifo_output_period > 1 then
         write_master_waitrequest_n <= '0';
      
         wait for (cs_stimulus.fifo_output_period - 1)*CLK_PERIOD;

         write_master_waitrequest_n <= '1';
      end if;

   end process;

   frame_write_checker: process
      variable expected_waddr: std_logic_vector(write_master_address'range);
      variable packet: packet_t;

      function "+"(a: std_logic_vector; b: integer) return std_logic_vector is
         variable sum: integer;
      begin
         sum := to_integer(unsigned(a)) + b;
         return std_logic_vector(to_unsigned(sum, a'length));
      end function;

      function "="(a: std_logic_vector; b: packet_t) return boolean is
         variable frame_start: boolean;
         variable frame_end: boolean;
         variable data_valid: boolean;
         variable data: boolean;
      begin
         frame_start := a(10) = b.frame_start;
         frame_end := a(9) = b.frame_end;
         data_valid := a(8) = b.data_valid;
         data := a(7 downto 0) = b.data;

         return frame_start and frame_end and data_valid and data;
      end function;

   begin
      wait until fifo_pop = '1';

      frame_write_checker_active <= true;

      packet := queue.pop;

      -- If expecting a start packet, set the expected_waddr to
      -- the base_addr
      if packet.frame_start = '1' then
         expected_waddr := std_logic_vector(
            to_unsigned(cs_stimulus.base_addr, expected_waddr'length));
      end if;

      wait for CLK_PERIOD;

      -- while write_master_waitrequest_n is low write_master_address,
      -- write_master_write_n, and write_master_writedata should remain constant,
      -- unless the stream gets disabled.
      while write_master_waitrequest_n = '0' and stream_enable = '1' loop
         assert write_master_address = expected_waddr
         report "write_master_address = " & to_hstring(write_master_address) & ", expected_waddr = " & to_hstring(expected_waddr)
         severity failure;

         assert write_master_write_n = '0'
         report "write_master_write_n should be low"
         severity failure;

         assert write_master_writedata = packet.data
         report "write_master_writedata = " & to_hstring(write_master_writedata) & ", packet.data = " & to_hstring(packet.data)
         severity failure;

         wait for CLK_PERIOD;
      end loop;

      -- The write-pointer in the write_master_controller only increments
      -- at the end of a write transfer. This means that data_valid must be high,
      -- and waitrequest_n should have deasserted.
      if packet.data_valid = '1' and stream_enable = '1' then
         expected_waddr := expected_waddr + 1;
      end if;

      if packet.frame_end = '1' and stream_enable = '1' then

         wait for CLK_PERIOD;

         assert frame_complete = '1'
         report "frame_complete should be high"
         severity failure;

         wait for CLK_PERIOD;

         if cs_stimulus.fc_irq_enable then
            assert irq = '1'
            report "frame complete interrupt was expected"
            severity failure;
         end if;
      end if;

      frame_write_checker_active <= false;

   end process;

   -- This process checks the input/output rates of the FIFO to infer
   -- when an overrun will occur, and checks if it does.
   overrun_error_checker: process
      variable cycles_until_overrun: integer;
      variable count: integer;

      function calculate_cycles_until_overrun(input_period,output_period: integer) return integer is
         variable numerator: real;
         variable denominator: real;
         variable cycles_until_full: integer;
      begin
         if input_period >= output_period then
            return -1; -- no overrun error
         end if;
         numerator := real(input_period*(output_period*8 - 1));
         denominator := real(output_period - input_period);
         cycles_until_full := integer(ceil(numerator/denominator));

         -- The write cycle after the FIFO is full is when the overrun occurs,
         -- but the overrun_error signal is asserted one cycle after the overrun. This
         -- is why there is a plus 2.
         return cycles_until_full + 2; 
      end function;

   begin
      wait on write_frame_request'transaction;
      wait until clk = '1';

      overrun_checker_active <= true;

      cycles_until_overrun := calculate_cycles_until_overrun(
         cs_stimulus.fifo_input_period, cs_stimulus.fifo_output_period);

      if cycles_until_overrun > 0 then
         wait for cycles_until_overrun*CLK_PERIOD;

         assert overrun_error = '1'
         report "overrun_error should be high"
         severity error;

         wait for CLK_PERIOD;

         if cs_stimulus.oe_irq_enable then
            assert irq = '1'
            report "overrun interrupt should have been asserted"
            severity error;
         end if;
      end if;

      overrun_checker_active <= false;
   end process;

end architecture;