-- Author: Brandon Dunne
-- Description: The purpose of this component is to convert data from
-- Avalon Streaming to Avalon Memory-Mapped. This conversion is useful for
-- streaming data to SDRAM.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- Fix: change frame_complete alias

entity dma_avalon_st_sink_to_mm_master is
   port (
      clk: in std_logic;
      rst: in std_logic;

      -- Control-Status interface signals (Avalon MM Slave)
      control_status_address: in std_logic;
      control_status_read_n: in std_logic;
      control_status_write_n: in std_logic;
      control_status_readdata: out std_logic_vector(31 downto 0);
      control_status_writedata: in std_logic_vector(31 downto 0);

      -- Optional interrupt request when a frame completes or when an overrun error occurs
      irq: out std_logic;

      -- DMA Read Sink (Avalon ST Sink)
      stream_sink_ready: out std_logic;
      stream_sink_valid: in std_logic;
      stream_sink_data: in std_logic_vector(10 downto 0);

      -- DMA Write Master (Avalon MM Master)
      write_master_address: out std_logic_vector(31 downto 0);
      write_master_write_n: out std_logic;
      write_master_waitrequest_n: in std_logic;
      write_master_writedata: out std_logic_vector(7 downto 0)

--      -- Simulation only
--      sim_fifo_empty: out std_logic;
--      sim_fifo_full: out std_logic;
--      sim_fifo_pop: out std_logic;
--      sim_fifo_push: out std_logic;
--      sim_fifo_packet_in: out std_logic_vector(10 downto 0);
--      sim_fifo_packet_out: out std_logic_vector(10 downto 0);
--      sim_stream_enable: out std_logic;
--      sim_frame_complete: out std_logic;
--      sim_overrun_error: out std_logic;
--      sim_base_addr: out std_logic_vector(31 downto 0)
   );
end entity;

architecture rtl of dma_avalon_st_sink_to_mm_master is

   signal fifo_empty: std_logic;
   signal fifo_full: std_logic;
   signal fifo_pop: std_logic;
   signal fifo_push: std_logic;
   signal fifo_packet_in: std_logic_vector(stream_sink_data'range);
   signal fifo_packet_out: std_logic_vector(stream_sink_data'range);

   signal stream_enable: std_logic;
   signal frame_complete: std_logic;
   signal overrun_error: std_logic;
   signal base_addr: std_logic_vector(31 downto 0);

begin

--   -- Simulation-only signal assignments
--   sim_fifo_empty <= fifo_empty;
--   sim_fifo_full <= fifo_full;
--   sim_fifo_pop <= fifo_pop;
--   sim_fifo_push <= fifo_push;
--   sim_fifo_packet_in <= fifo_packet_in;
--   sim_fifo_packet_out <= fifo_packet_out;
--   sim_stream_enable <= stream_enable;
--   sim_frame_complete <= frame_complete;
--   sim_overrun_error <= overrun_error;
--   sim_base_addr <= base_addr;

   -- Control access to the Control-Status and Base-Address registers
   control_status_controller0: entity work.control_status_controller
      port map (
         clk => clk,
         rst => rst,

         address => control_status_address,
         read_n => control_status_read_n,
         write_n => control_status_write_n,
         readdata => control_status_readdata,
         writedata => control_status_writedata,

         irq => irq,

         frame_complete => frame_complete,
         overrun_error => overrun_error,
         stream_enable => stream_enable,

         base_addr => base_addr
      );

   -- Responsible for controlling writing incoming stream data to
   -- the FIFO, and generates an overrun error when trying to write to
   -- a full FIFO
   stream_sink_controller0: entity work.stream_sink_controller
      port map (
         clk => clk,
         rst => rst,

         -- avalon stream sink signals
         ready => stream_sink_ready,
         valid => stream_sink_valid,
         stream_data => stream_sink_data,

         fifo_full => fifo_full,
         fifo_push => fifo_push,
         fifo_packet => fifo_packet_in,

         -- control status signals
         stream_enable => stream_enable,
         overrun_error => overrun_error
      );

   -- FIFO constructed out of registers with
   -- a depth of 8
   fifo0: entity work.fifo
      port map (
         clk => clk,
         rst => rst or not stream_enable,
         push => fifo_push,
         pop => fifo_pop,
         empty => fifo_empty,
         full => fifo_full,
         data_in => fifo_packet_in,
         data_out => fifo_packet_out
      );

   -- Writes FIFO data to SDRAM. Responsible for incrementing the address
   -- ptr after each frame and reseting it when receiving a frame_start
   write_master_controller0: entity work.write_master_controller
      port map (
         clk => clk,
         rst => rst,
         
         fifo_packet => fifo_packet_out,
         fifo_empty => fifo_empty,
         fifo_pop => fifo_pop,

         -- avalon write master signal
         waitrequest_n => write_master_waitrequest_n,
         write_n => write_master_write_n,
         waddr => write_master_address,
         wdata => write_master_writedata,

         -- control status signals
         stream_enable => stream_enable,
         frame_complete => frame_complete,
         base_addr => base_addr
      );

end architecture;