library ieee;
use ieee.std_logic_1164.all;

entity mealy_pulse_generator is
  port (
    clk: in std_logic;
    rst: in std_logic;
    cycles: in natural range 0 to 64;
    din: in std_logic;
    dout: out std_logic
  );
end entity;

architecture fsm of mealy_pulse_generator is

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

            if count = 1 and din = '0' then
              state <= s3;
            elsif count = 1 and din = '1' then
              state <= s0;
            elsif count > 1 and din = '1' then
              state <= s2;
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

  -- latch din when state = s0 and set dout when state = s3
  process (din, state)
  begin
    if state = s0 then
      dout <= din;
    elsif state = s3 then
      dout <= '1';
    end if;
  end process;

end architecture;