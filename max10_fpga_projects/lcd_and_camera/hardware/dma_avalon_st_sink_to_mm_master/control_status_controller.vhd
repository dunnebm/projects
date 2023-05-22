-- Author: Brandon Dunne

library ieee;
use ieee.std_logic_1164.all;

entity control_status_controller is
  port (
    clk: in std_logic;
    rst: in std_logic;

    address: in std_logic;
    read_n: in std_logic;
    write_n: in std_logic;
    readdata: out std_logic_vector(31 downto 0);
    writedata: in std_logic_vector(31 downto 0);

    irq: out std_logic;

    frame_complete: in std_logic;
    overrun_error: in std_logic;
    stream_enable: buffer std_logic;

    base_addr: buffer std_logic_vector(31 downto 0)
  );
end entity;

architecture rtl of control_status_controller is

  constant STREAM_ENABLE_BIT: integer := 0;
  constant FRAME_COMPLETE_IRQ_ENABLE_BIT: integer := 1;
  constant OVERRUN_ERROR_IRQ_ENABLE_BIT: integer := 2;
  constant FRAME_COMPLETE_BIT: integer := 3;
  constant OVERRUN_ERROR_BIT: integer := 4;

  signal csr: std_logic_vector(31 downto 0);
  signal frame_complete_irq_enable: std_logic;
  signal overrun_error_irq_enable: std_logic;
  signal frame_complete_flag: std_logic;
  signal overrun_error_flag: std_logic;

  signal readdata_select: std_logic_vector(1 downto 0);

begin

  csr <= (0 => stream_enable, 3 => frame_complete_flag, 
          4 => overrun_error_flag, 1 => frame_complete_irq_enable, 
          2 => overrun_error_irq_enable, others => '0');


  irq <= (frame_complete_flag and frame_complete_irq_enable) or
         (overrun_error_flag and overrun_error_irq_enable);

  with readdata_select select readdata <=
    csr              when b"00",
    base_addr        when b"01",
    (others => '0')  when others;

  stream_enable_flipflop: process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        stream_enable <= '0';
      elsif frame_complete = '1' or overrun_error = '1' then
        stream_enable <= '0';
      elsif write_n = '0' and address = '0' then
        stream_enable <= writedata(STREAM_ENABLE_BIT);
      end if;
    end if;
  end process;

  frame_complete_flag0: process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        frame_complete_flag <= '0';
      elsif write_n = '0' and address = '0' and writedata(FRAME_COMPLETE_BIT) = '0' then
        frame_complete_flag <= '0';
      else
        frame_complete_flag <= frame_complete_flag or frame_complete;
      end if;
    end if;
  end process;

  overrun_error_flag0: process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        overrun_error_flag <= '0';
      elsif write_n = '0' and address = '0' and writedata(OVERRUN_ERROR_BIT) = '0' then
        overrun_error_flag <= '0';
      else
        overrun_error_flag <= overrun_error_flag or overrun_error;
      end if;
    end if;
  end process;

  irq_enable_control_bits: process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then 
        frame_complete_irq_enable <= '0';
        overrun_error_irq_enable <= '0';
      elsif write_n = '0' and address = '0' then
        frame_complete_irq_enable <= writedata(FRAME_COMPLETE_IRQ_ENABLE_BIT);
        overrun_error_irq_enable <= writedata(OVERRUN_ERROR_IRQ_ENABLE_BIT);
      end if;
    end if;
  end process;

  base_addr_register: process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        base_addr <= (others => '0');
      elsif write_n = '0' and address = '1' then
        base_addr <= writedata;
      end if;
    end if;
  end process;

end architecture;