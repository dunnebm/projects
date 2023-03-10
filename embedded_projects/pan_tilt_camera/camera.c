#include "camera.h"
#include "../mystm32lib/gpio.h"
#include "../mystm32lib/dcmi.h"
#include "../mystm32lib/dma.h"
#include "../mystm32lib/i2c.h"

#define CAMERA_WIDTH 128
#define CAMERA_HEIGHT 128

static const volatile uint16_t captured_data[CAMERA_WIDTH * CAMERA_HEIGHT];

void camera_init()
{
  /* Configure GPIO pins */
  GPIO_enableClock(GPIOC);
  GPIO_setMode(GPIOC, 
    GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
    GPIO_PIN_11 | GPIO_PIN_12, GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOC,
    GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
    GPIO_PIN_11 | GPIO_PIN_12, GPIO_ALT_FUNC_13);

  GPIO_enableClock(GPIOB);
  GPIO_setMode(GPIOB,
    GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_5 | GPIO_PIN_7,
    GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOB,
    GPIO_PIN_6 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_5 | GPIO_PIN_7,
    GPIO_ALT_FUNC_13);

  GPIO_enableClock(GPIOD);
  GPIO_setMode(GPIOB, GPIO_PIN_2, GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOD, GPIO_PIN_2, GPIO_ALT_FUNC_13);

  GPIO_enableClock(GPIOG);
  GPIO_setMode(GPIOG, GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOG, GPIO_PIN_6 | GPIO_PIN_7, GPIO_ALT_FUNC_13);
  
  GPIO_enableClock(GPIOA);
  GPIO_setMode(GPIOA, GPIO_PIN_4 | GPIO_PIN_6, GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOA, GPIO_PIN_4 | GPIO_PIN_6, GPIO_ALT_FUNC_13);

  /* Configure DMA */
  DMA_enableClock(DMA2);
  DMA_disable(DMA2, 7);
  DMA_clearStreamFlags(DMA2, 7, DMA_ALL_FLAGS);

  DMAStreamConfiguration DMA_config = { 0 };
  DMA_config.channel = 1;
  DMA_config.circularMode = DMA_CIRCULAR_MODE_ENABLED;
  DMA_config.direction = DMA_DIRECTION_PERIPHERAL_TO_MEMORY;
  DMA_config.periphIncr = DMA_INCREMENT_MODE_DISABLED;
  DMA_config.memIncr = DMA_INCREMENT_MODE_ENABLED;
  DMA_config.periphSize = DMA_DATA_SIZE_WORD;
  DMA_config.memSize = DMA_DATA_SIZE_WORD;
  DMA_config.periphAddr = (uint32_t) 0x50050028;
  DMA_config.memAddr0 = (uint32_t) &captured_data;
  DMA_config.numDataToTransfer = (uint32_t) CAMERA_WIDTH * CAMERA_HEIGHT;

  DMA_configureStream(DMA2, 7, &DMA_config);

  DCMIConfiguration DCMI_config = { 0 };
  DCMI_config.captureMode = DCMI_CAPTURE_MODE_SNAPSHOT;
  DCMI_config.dataSize = DCMI_DATA_SIZE_14_BITS;
  DCMI_config.pixclkPolarity = DCMI_PIXCLK_POLARITY_RISING_EDGE;
  DCMI_config.hsyncPolarity = DCMI_HSYNC_POLARITY_ACTIVE_HIGH;
  DCMI_config.vsyncPolarity = DCMI_VSYNC_POLARITY_ACTIVE_HIGH;

  DCMI_configure(&DCMI_config);
}