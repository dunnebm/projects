#include "display.h"
#include "../mystm32lib/gpio.h"
#include "../mystm32lib/spi.h"

void display_init()
{
  // Configure PB14 as MISO and PB15 as MOSI
  GPIO_enableClock(GPIOB);
  GPIO_setMode(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOB, GPIO_PIN_14 | GPIO_PIN_15, GPIO_ALT_FUNC_5);
  
  // Configure PB8 as D/CX and PB7 as CS
  GPIO_setMode(GPIOB, GPIO_PIN_8, GPIO_MODE_OUTPUT);
  GPIO_setOutputType(GPIOB, GPIO_PIN_8, GPIO_OUTPUT_TYPE_PUSH_PULL);

  // Set PB7 as high because the chip-select is active low
  GPIO_set(GPIOB, GPIO_PIN_7);

  SPI_enableClock(SPI2);

  SPIConfiguration SPI_config = { 0 };
  SPI_config.baud = SPI_BAUD_4_CLK_PERIODS;
  SPI_config.endianess = SPI_ENDIANESS_BIG_ENDIAN;
  SPI_config.frameSize = SPI_DATA_FRAME_SIZE_8_BIT;
  SPI_config.mode = SPI_MODE_MASTER;
  SPI_config.clockIdleState = SPI_CLOCK_IDLE_STATE_LOW;
  SPI_config.clockPhase = SPI_CLOCK_PHASE_FIRST_TRANSITION;

  SPI_configure(SPI2, &SPI_config);
  SPI_enable(SPI2);
}

void display_sendCmd(uint8_t cmd)
{
  // Pull chip-select low
  GPIO_clear(GPIOB, GPIO_PIN_7);

  // Pull D/CX low to send a command
  GPIO_clear(GPIOB, GPIO_PIN_8);

  SPI_write(SPI2, &cmd, 1);

  // Pull chip-select high
  GPIO_set(GPIOB, GPIO_PIN_7);
}

void display_sendData(uint8_t* buf, int len)
{
  // Pull chip-select low
  GPIO_clear(GPIOB, GPIO_PIN_7);

  // Pull D/CX high to send data/args
  GPIO_set(GPIOB, GPIO_PIN_8);

  SPI_write(SPI2, buf, len);

  // Pull chip-select high
  GPIO_set(GPIOB, GPIO_PIN_7);
}