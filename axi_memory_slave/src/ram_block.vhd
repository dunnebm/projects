library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ram_block is
	generic (
		ADDR_WIDTH: natural := 8;
    DATA_WIDTH: natural := 8;
	);
	port (
		rclk, wclk: in std_logic;
		raddr, waddr: in integer range 0 to 2**ADDR_WIDTH - 1;
		wdata: in std_logic_vector(DATA_WIDTH - 1 downto 0);
		rdata: out std_logic_vector(DATA_WIDTH - 1 downto 0);
		we: in std_logic
	);
end entity;

architecture rtl of ram_block is
	
	type ram_t is array (0 to 2**ADDR_WIDTH - 1) of std_logic_vector(DATA_WIDTH - 1 downto 0);
	signal ram: ram_t;

begin

	process (wclk) 
	begin
		if rising_edge(wclk) then
			if we = '1' then
				ram(waddr) <= wdata;
			end if;	
		end if;
	end process;

  process (rclk)
  begin
    if rising_edge(rclk)
      rdata <= ram(raddr);
    end if;
  end process;
	
end architecture;