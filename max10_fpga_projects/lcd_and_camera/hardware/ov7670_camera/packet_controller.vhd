library ieee;
use ieee.std_logic_1164.all;

entity packet_controller is
  port (
    clk: in std_logic;
    arst: in std_logic;

    vsync: in std_logic;
    href: in std_logic;
    valid: out std_logic;

    camera_data: in std_logic_vector(7 downto 0);
    packet: out std_logic_vector(10 downto 0)
  );
end entity; 

architecture fsm of packet_controller is

  type state_t is (idle, waiting_for_frame_start, start_of_frame, writing_frame, end_of_frame);
  signal state: state_t;

  -- bit fields in the packet
  signal frame_start, frame_end, data_valid: std_logic;

  -- This signal is used to latch vsync edges;
  -- falling edges signal the start of a frame. In other words,
  -- means that the FSM will start the sequence of writing a frame.
  signal start_frame: std_logic;

begin

  packet(10) <= frame_start;
  packet(9) <= frame_end;
  packet(8) <= data_valid;
  packet(7 downto 0) <= camera_data;

  process (clk)
  begin
    if arst = '1' then
      state <= idle;
    elsif rising_edge(clk) then
      case state is
        when idle =>
          if vsync = '1' then
            state <= waiting_for_frame_start;
          end if;
        when waiting_for_frame_start =>
          if vsync = '0' then
            state <= start_of_frame;
          end if;
        when start_of_frame =>
          state <= writing_frame;
        when writing_frame =>
          if vsync = '1' then
            state <= end_of_frame;
          end if;
        when end_of_frame =>
          state <= waiting_for_frame_start;
      end case;
    end if;
  end process;

  process (state, href)
  begin
    case state is
      when idle =>
        valid <= '0';
        frame_start <= '0';
        frame_end <= '0';
        data_valid <= '0';
      when waiting_for_frame_start =>
        valid <= '0';
        frame_start <= '0';
        frame_end <= '0';
        data_valid <= '0';
      when start_of_frame =>
        valid <= '1';
        frame_start <= '1';
        frame_end <= '0';
        data_valid <= '0';
      when writing_frame =>
        valid <= href;
        frame_start <= '0';
        frame_end <= '0';
        data_valid <= href;
      when end_of_frame =>
        valid <= '1';
        frame_start <= '0';
        frame_end <= '1';
        data_valid <= '0';
    end case;
  end process;

end architecture;