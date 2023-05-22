library ieee;
use ieee.std_logic_1164.all;

entity lcd8080_controller_tb is
end entity;

architecture testbench of lcd8080_controller_tb is

  signal clk: std_logic := '0';
  signal rst: std_logic;
  
  signal address: std_logic;
  signal write_n: std_logic := '1';
  signal waitrequest_n: std_logic;
  signal writedata: std_logic_vector(15 downto 0);

  signal csx_n: std_logic;
  signal dcx: std_logic;
  signal wrx_n: std_logic;
  signal rdx_n: std_logic;
  signal data: std_logic_vector(15 downto 0);

  constant CLK_PERIOD: time := 5 ns;
  constant ONE_DELTA_CYCLE: time := 0 ns;
  constant COMMAND_REGISTER: std_logic := '0';
  constant DATA_REGISTER: std_logic := '1';

  constant ILI9486_CMD_NOP: std_logic_vector(15 downto 0) := x"0000";
  constant ILI9486_CMD_SOFT_RESET: std_logic_vector(15 downto 0) := x"0001";
  constant ILI9486_CMD_DISPLAY_ON: std_logic_vector(15 downto 0) := x"0029";
  constant ILI9486_CMD_COLUMN_ADDRESS_SET: std_logic_vector(15 downto 0) := x"002A";
  constant ILI9486_CMD_PAGE_ADDRESS_SET: std_logic_vector(15 downto 0) := x"002B";
  constant ILI9486_CMD_PAGE_MEMORY_WRITE: std_logic_vector(15 downto 0) := x"002C";

  constant CMD_ENABLE_BIT: integer := 0;

begin

  DUT: entity work.lcd8080_controller
    port map (
      clk => clk,
      rst => rst,

      address => address,
      write_n => write_n,
      waitrequest_n => waitrequest_n,
      writedata => writedata,

      csx_n => csx_n,
      dcx => dcx,
      wrx_n => wrx_n,
      rdx_n => rdx_n,
      data => data
    );

  clk <= not clk after CLK_PERIOD/2;
  rst <= '1', '0' after CLK_PERIOD;

  test_cmds: process
  begin

    wait until rising_edge(clk) and rst = '0';
    wait for ONE_DELTA_CYCLE;

    address <= COMMAND_REGISTER;
    write_n <= '0';
    writedata <= ILI9486_CMD_SOFT_RESET;

    wait until rising_edge(waitrequest_n);

    -- release write_n 1 clock after waitrequest_n is released,
    -- because that is the expected behavior according to the Avalon spec.
    wait for CLK_PERIOD;

    write_n <= '1';

    wait for CLK_PERIOD;

    write_n <= '0';
    writedata <= ILI9486_CMD_DISPLAY_ON;

    wait until rising_edge(waitrequest_n);

    wait for CLK_PERIOD;

    write_n <= '1';

    wait for CLK_PERIOD;

    write_n <= '0';
    address <= DATA_REGISTER;
    writedata <= x"beef";

    wait until waitrequest_n = '0';
    wait until waitrequest_n = '1';

    wait for CLK_PERIOD;

  end process;

end architecture;