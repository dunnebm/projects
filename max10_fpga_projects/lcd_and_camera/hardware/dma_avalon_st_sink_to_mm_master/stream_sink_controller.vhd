-- Author: Brandon Dunne
-- Description: This component controls what is written to
-- the FIFO and signals an overrun error if the FIFO overwhelmed
-- by incoming data.

library ieee;
use ieee.std_logic_1164.all;

entity stream_sink_controller is
	port (
		clk: in std_logic;
		rst: in std_logic;

		fifo_full: in std_logic;
		fifo_push: out std_logic;
		fifo_packet: out std_logic_vector(10 downto 0);

		valid: in std_logic;
		ready: out std_logic;
		stream_data: in std_logic_vector(10 downto 0);

		stream_enable: in std_logic;
		overrun_error: out std_logic
	);
end entity;

architecture rtl of stream_sink_controller is

	type state_t is (stream_disabled, stream_enabled, overrun);
	signal state: state_t;

begin
	-- instead of using the ready signal, this component signals an
	-- overrun error.
	ready <= '1';
	fifo_packet <= stream_data;

	process (clk)
	begin
		if rising_edge(clk) then
			if rst = '1' or stream_enable = '0' then
				state <= stream_disabled;
			else
				case state is
					when stream_disabled =>
						if stream_enable = '1' then
							state <= stream_enabled;
						end if;
					when stream_enabled =>
						if valid = '1' and fifo_full = '1' then
							state <= overrun;
						end if;
					when overrun =>
						state <= stream_disabled;
				end case;
			end if;
		end if;
	end process;

	process (state, valid, fifo_full, stream_enable)
	begin
		case state is
			when stream_disabled =>
				fifo_push <= '0';
				overrun_error <= '0';
			when stream_enabled =>
				fifo_push <= valid;
				overrun_error <= '0';
			when overrun =>
				fifo_push <= '0';
				overrun_error <= '1';
		end case;
	end process;

end architecture;