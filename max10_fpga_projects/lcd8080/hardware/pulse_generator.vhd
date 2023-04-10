library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity pulse_generator is
  port (
    clk: in std_logic;
    rst: in std_logic;
    cycles: in natural range 0 to 64;
    din: in std_logic;
    dout: out std_logic
  );
end entity;

architecture fsm of pulse_generator is

  type state_t is (s0, s1, s2, s3);
  signal state: state_t;
  signal count: natural range 0 to 64;

begin

  process (clk)
  begin
    if rising_edge(clk) then
      if rst = '1' then
        state <= s0;
      else
        case state is
          when s0 =>

            if din = '0' then
              state <= s1;
            end if;

            count <= cycles;

          when s1 =>

            if din = '1' and count > 1 then
              state <= s2;
            elsif din = '0' and count = 1 then
              state <= s3;
            elsif din = '1' and count = 1 then
              state <= s0;
            end if;

            count <= count - 1;

          when s2 =>

            if count = 1 then
              state <= s0;
            end if;

            count <= count - 1;

          when s3 =>

            if din = '1' then
              state <= s0;
            end if;

        end case;
      end if;
    end if;
  end process;

  process (state)
  begin
    case state is
      when s0 =>
        dout <= '1';
      when s1 =>
        dout <= '0';
      when s2 =>
        dout <= '0';
      when s3 =>
        dout <= '1';
    end case;
  end process;

end architecture;