#ifndef DMA_H
#define DMA_H

#include <stdint.h>

#define DMA_FLOW_CONTROLLER_DMA 0u
#define DMA_FLOW_CONTROLLER_PERIPHERAL 1u

#define DMA_DIRECTION_PERIPHERAL_TO_MEMORY 0u
#define DMA_DIRECTION_MEMORY_TO_PERIPHERAL 1u
#define DMA_DIRECTION_MEMORY_TO_MEMORY 2u

#define DMA_CIRCULAR_MODE_DISABLED 0u
#define DMA_CIRCULAR_MODE_ENABLED 1u

#define DMA_DATA_SIZE_BYTE 0u
#define DMA_DATA_SIZE_HALF_WORD 1u
#define DMA_DATA_SIZE_WORD 2u

#define DMA_FIFO_MODE_OFF 0u
#define DMA_FIFO_MODE_ON 1u

#define DMA_FIFO_THRESHOLD_QUARTER_FULL 0u
#define DMA_FIFO_THRESHOLD_HALF_FULL 1u
#define DMA_FIFO_THRESHOLD_THREE_QUARTERS_FULL 2u
#define DMA_FIFO_THRESHOLD_FULL 3u

#define DMA_FIFO_ERROR_FLAG (1<<0)
#define DMA_DIRECT_MODE_ERROR_FLAG (1<<2)
#define DMA_TRANSFER_ERROR_FLAG (1<<3)
#define DMA_HALF_TRANSFER_FLAG (1<<4)
#define DMA_TRANSFER_COMPLETE_FLAG (1<<5)
#define DMA_ALL_FLAGS (DMA_FIFO_ERROR_FLAG | DMA_DIRECT_MODE_ERROR_FLAG |\
                       DMA_HALF_TRANSFER_FLAG | DMA_TRANSFER_COMPLETE_FLAG)

#define DMA_BURST_SINGLE_TRANSFER 0u
#define DMA_BURST_INCR4 1u
#define DMA_BURST_INCR8 2u
#define DMA_BURST_INCR16 3u

#define DMA_DOUBLE_BUFFER_MODE_DISABLED 0u
#define DMA_DOUBLE_BUFFER_MODE_ENABLED 1u

#define DMA_PRIORITY_LOW 0u
#define DMA_PRIORITY_MEDIUM 1u
#define DMA_PRIORITY_HIGH 2u
#define DMA_PRIORITY_VERY_HIGH 3u

#define DMA_INCREMENT_MODE_DISABLED 0u
#define DMA_INCREMENT_MODE_ENABLED 1u

typedef enum {
  DMA1 = 0x40026000,
  DMA2 = 0x40026400
} DMA;

typedef struct {
  uint32_t channel;
  uint32_t flowController;
  uint32_t direction;
  uint32_t circularMode;
  uint32_t doubleBufferMode;
  uint32_t periphIncr;
  uint32_t memIncr;
  uint32_t periphSize;
  uint32_t memSize;
  uint32_t priority;
  uint32_t periphBurst;
  uint32_t memBurst;
  uint32_t FIFOMode;
  uint32_t FIFOThreshold;
  uint32_t numDataToTransfer;
  uint32_t periphAddr;
  uint32_t memAddr0;
  uint32_t memAddr1;
} DMAStreamConfiguration;

void DMA_enableClock(DMA dma);
void DMA_disableClock(DMA dma);
void DMA_enable(DMA dma, uint32_t stream);
void DMA_disable(DMA dma, uint32_t stream);
void DMA_configureStream(DMA dma, uint32_t stream, const DMAStreamConfiguration* pConfig);
void DMA_getStreamConfiguration(DMA dma, uint32_t stream, DMAStreamConfiguration* pConfig);
uint32_t DMA_getStreamFlags(DMA dma, uint32_t stream);
void DMA_clearStreamFlags(DMA dma, uint32_t stream, uint32_t events);
void DMA_enableInterrupts(DMA dma, uint32_t stream, uint32_t flags);
void DMA_disableInterrupts(DMA dma, uint32_t stream, uint32_t flags);

#endif