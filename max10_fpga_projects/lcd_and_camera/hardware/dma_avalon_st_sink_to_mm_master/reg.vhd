library ieee;
use ieee.std_logic_1164.all;

entity reg is
   generic (DATA_WIDTH: natural := 8);
   port (
      D: in std_logic_vector(DATA_WIDTH - 1 downto 0);
      clk: in std_logic;
      rst: in std_logic;
      ld: in std_logic;
      Q: out std_logic_vector(DATA_WIDTH - 1 downto 0)
   );
end entity;

architecture rtl of reg is
begin

   process (clk)
   begin
      if rising_edge(clk) then
         if rst = '1' then
            Q <= (others => '0');
         elsif ld = '1' then
            Q <= D;
         end if;
      end if;
   end process;

end architecture;