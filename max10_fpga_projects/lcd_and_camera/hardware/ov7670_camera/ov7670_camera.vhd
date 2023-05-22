-- Author: Brandon Dunne

library ieee;
use ieee.std_logic_1164.all;

entity ov7670_camera is
  port (
    -- Camera PLL 24MHz
    clk: in std_logic;
    rst: in std_logic;

    -- DMA clock source
    pixel_clk: out std_logic;

    -- Avalon ST Source interface signals
    stream_data: out std_logic_vector(10 downto 0);
    valid: out std_logic;
    ready: in std_logic;

    -- OV7670 camera interface signals
    href: in std_logic;
    vsync: in std_logic;
    pclk: in std_logic;
    xclk: out std_logic;
    camera_reset: out std_logic;
    camera_data: in std_logic_vector(7 downto 0)
  );
end entity;

architecture rtl of ov7670_camera is

  signal sync_rst: std_logic;
  signal reset: std_logic;

begin

  camera_reset <= rst;

  xclk <= clk;
  pixel_clk <= pclk;

  map_packet_controller: entity work.packet_controller
    port map (
      clk => pclk,
      arst => rst,

      href => href,
      vsync => vsync,

      camera_data => camera_data,
      packet => stream_data,
      valid => valid
    );

end architecture;