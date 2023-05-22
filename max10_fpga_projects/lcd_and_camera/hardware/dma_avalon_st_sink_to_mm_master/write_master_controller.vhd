-- Author: Brandon Dunne
-- Description: This component reads packets from the FIFO, interprets them,
-- then drives the Avalon MM Master signals accordingly.

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity write_master_controller is
   port (
      clk: in std_logic;
      rst: in std_logic;

      fifo_packet: in std_logic_vector(10 downto 0);
      fifo_empty: in std_logic;
      fifo_pop: out std_logic;

      -- avalon write master signals
      waitrequest_n: in std_logic;
      write_n: out std_logic;
      waddr: out std_logic_vector(31 downto 0);
      wdata: out std_logic_vector(7 downto 0);

      -- control status signals
      stream_enable: in std_logic;
      frame_complete: out std_logic;
      base_addr: in std_logic_vector(31 downto 0)
   );
end entity;

architecture fsm of write_master_controller is

   type state_t is (stream_disabled, stream_enabled, write_to_dst, frame_completed);

   signal state: state_t;

   signal ptr: integer range 0 to 2**26 - 1;

   constant FRAME_START: integer := 10;
   constant FRAME_END: integer := 9;
   constant DATA_VALID: integer := 8;
   

   signal packet_reg: std_logic_vector(10 downto 0);

begin

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
                  packet_reg <= fifo_packet;
                  if fifo_empty = '0' then
                     if fifo_packet(DATA_VALID) = '1' then
                        state <= write_to_dst;
                     elsif fifo_packet(DATA_VALID) = '0' and fifo_packet(FRAME_END) = '1' then
                        state <= frame_completed;
                     end if;

                     if fifo_packet(FRAME_START) = '1' then
                        ptr <= to_integer(unsigned(base_addr));
                     end if;
                  end if;
               when write_to_dst =>
                  if waitrequest_n = '1' then
                     ptr <= ptr + 1;
                  end if;

                  if waitrequest_n = '1' and packet_reg(FRAME_END) = '1' then
                     state <= frame_completed;
                  elsif waitrequest_n = '1' then
                     state <= stream_enabled;
                  end if;
               when frame_completed =>
                  state <= stream_disabled;
            end case;
         end if;
      end if;
   end process;

   process (state, waitrequest_n, fifo_empty, fifo_packet, packet_reg)
   begin
      case state is
         when stream_disabled =>
            fifo_pop <= '0';
            write_n <= '1';
            frame_complete <= '0';
            wdata <= (others => '-');
            waddr <= (others => '-');
         when stream_enabled =>
            fifo_pop <= not fifo_empty;
            write_n <= not fifo_empty nand fifo_packet(DATA_VALID);
            frame_complete <= '0';
            wdata <= fifo_packet(7 downto 0);
            case fifo_packet(FRAME_START) is
               when '1' =>    waddr <= base_addr;
               when others => waddr <= std_logic_vector(to_unsigned(ptr, waddr'length));
            end case;
         when write_to_dst =>
            fifo_pop <= '0';
            write_n <= waitrequest_n;
            frame_complete <= '0';
            wdata <= packet_reg(7 downto 0);
            waddr <= std_logic_vector(to_unsigned(ptr, waddr'length));
         when frame_completed =>
            fifo_pop <= '0';
            write_n <= '1';
            frame_complete <= '1';
            wdata <= (others => '-');
            waddr <= (others => '-');
      end case;
   end process;

end architecture;