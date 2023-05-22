library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity decoder is
	generic (ADDRESS_WIDTH: natural := 4);
	port (
		A: in std_logic_vector(ADDRESS_WIDTH-1 downto 0);
		Y: out std_logic_vector(2**ADDRESS_WIDTH - 1 downto 0)
	);
end entity;

architecture combinational of decoder is

	function build_decoder(data_in: std_logic_vector) return std_logic_vector is
		variable data_out: std_logic_vector(2**data_in'length - 1 downto 0);
		variable row_vector: std_logic_vector(data_in'range);
		variable result: std_logic;
	begin
	    for i in data_out'range loop	
			row_vector := std_logic_vector(to_unsigned(i, row_vector'length));
	    	result := '1';	
			for j in row_vector'range loop
				if row_vector(j) = '0' then
					result := result and not data_in(j);
				else
					result := result and data_in(j);
				end if;
			end loop;
			data_out(i) := result;	
		end loop;
		return data_out;
	end function;

begin

	Y <= build_decoder(A);

end architecture;