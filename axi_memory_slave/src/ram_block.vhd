library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ram_block is
	generic (
		ADDR_WIDTH: natural := 8
	);
	port (
		clk: in std_logic;
		raddr, waddr: in integer range 0 to 2**ADDR_WIDTH - 1;
		wdata: in std_logic_vector(31 downto 0);
		rdata: out std_logic_vector(31 downto 0);
		be: in std_logic_vector(3 downto 0);
		we: in std_logic
	);
end entity;

architecture rtl of ram_block is
	
	type word_t is array 0 to 3 of std_logic_vector(7 downto 0);
	type ram_t is array (0 to 2**ADDR_WIDTH - 1) of word_t;
	signal ram: ram_t;
	signal q: word_t;

begin

	rdata(7 downto 0) <= q(0);
	rdata(15 downto 8) <= q(1);
	rdata(23 downto 16) <= q(2);
	rdata(31 downto 24) <= q(3);

	process (clk) 
	begin
		if rising_edge(clk) then
			q <= ram(raddr);
			if we = '1' then
				if be(0) = '1' then
					ram(waddr)(0) <= wdata(7 downto 0);
				end if;
				if be(1) = '1' then
					ram(waddr)(1) <= wdata(15 downto 8);
				end if;
				if be(2) = '1' then
					ram(waddr)(2) <= wdata(23 downto 16);
				end if;
				if be(3) = '1' then
					ram(waddr)(3) <= wdata(31 downto 24);
				end if;
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