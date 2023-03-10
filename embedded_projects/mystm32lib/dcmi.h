#ifndef DCMI_H
#define DCMI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define DCMI_FIFO_NOT_EMPTY_FLAG (1<<2)
#define DCMI_VSYNC_FLAG (1<<1)
#define DCMI_HSYNC_FLAG (1<<0)

#define DCMI_IRQ_FRAME_FLAG (1<<0)
#define DCMI_IRQ_OVERRUN_FLAG (1<<1)
#define DCMI_IRQ_SYNC_ERROR_FLAG (1<<2)
#define DCMI_IRQ_VSYNC_FLAG (1<<3)
#define DCMI_IRQ_LINE_FLAG (1<<4)

#define DCMI_PIXCLK_POLARITY_RISING_EDGE 1u
#define DCMI_PIXCLK_POLARITY_FALLING_EDGE 0u

#define DCMI_HSYNC_POLARITY_ACTIVE_LOW 0u
#define DCMI_HSYNC_POLARITY_ACTIVE_HIGH 1u

#define DCMI_VSYNC_POLARITY_ACTIVE_LOW 0u
#define DCMI_VSYNC_POLARITY_ACTIVE_HIGH 1u

#define DCMI_DATA_SIZE_8_BITS 0u
#define DCMI_DATA_SIZE_10_BITS 1u
#define DCMI_DATA_SIZE_12_BITS 2u
#define DCMI_DATA_SIZE_14_BITS 2u

#define DCMI_CAPTURE_MODE_SNAPSHOT 0u
#define DCMI_CAPTURE_MODE_CONTINUOUS 1u

typedef struct {
  uint32_t dataSize;
  uint32_t pixclkPolarity;
  uint32_t hsyncPolarity;
  uint32_t vsyncPolarity;
  uint32_t captureMode;
} DCMIConfiguration;

void DCMI_enableClock();
void DCMI_disableClock();
void DCMI_enable();
void DCMI_disable();
void DCMI_configure(const DCMIConfiguration* pConfig);
void DCMI_getConfig(DCMIConfiguration* pConfig);
void DCMI_enableInterrupts(uint32_t flags);
void DCMI_disableInterrupts(uint32_t flags);

#ifdef __cplusplus
}
#endif
#endif