-- Author: Brandon Dunne
-- Description:
--  This controller drives LCDs that support the Intel's 8080 MCU interface.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity lcd8080_controller is
  port (
    clk: in std_logic;
    rst: in std_logic;

    -- DMA Avalon MM slave interface
    address: in std_logic;
    write_n: in std_logic;
    waitrequest_n: out std_logic;
    writedata: in std_logic_vector(15 downto 0);

    -- Intel 8080 16-bit lcd interface
    csx_n: out std_logic;
    dcx: out std_logic;
    wrx_n: out std_logic;
    rdx_n: out std_logic;
    data: out std_logic_vector(15 downto 0)
  );
end entity;

architecture rtl of lcd8080_controller is

  signal command_register: std_logic_vector(15 downto 0);
  signal data_register: std_logic_vector(15 downto 0);
  
  constant WRITE_DURATION: natural := 5; -- 5 10ns clock cycles
  constant WRITE_LOW_PULSE_DURATION: natural := 3; -- 3 10ns clock cycles

begin

  rdx_n <= '1'; -- not using this pin
  dcx <= address;
  csx_n <= write_n;
  data <= writedata;

  waitrequest_pulse: entity work.mealy_pulse_generator
    port map (
      clk => clk,
      rst => rst,
      cycles => WRITE_DURATION - 1,
      din => write_n,
      dout => waitrequest_n
    );

  wrx_n_pulse: entity work.pulse_generator
    port map (
      clk => clk,
      rst => rst,
      cycles => WRITE_LOW_PULSE_DURATION,
      din => write_n,
      dout => wrx_n
    );

end architecture;