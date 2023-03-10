#include "dma.h"
#include "rcc.h"

#define DMA_SCR_EN_BIT (1<<0)
#define DMA_SCR_EN_OFFSET 0
#define DMA_SCR_DMEIE_BIT (1<<1) // direct mode error interrupt enable
#define DMA_SCR_DMEIE_OFFSET 1
#define DMA_SCR_TEIE_BIT (1<<2) // transfer error interrupt enable
#define DMA_SCR_TEIE_OFFSET 2
#define DMA_SCR_HTIE_BIT (1<<3) // half transfer interrupt enable
#define DMA_SCR_HTIE_OFFSET 3
#define DMA_SCR_TCIE_BIT (1<<4) // transfer complete interrupt enable
#define DMA_SCR_TCIE_OFFSET 4
#define DMA_SCR_PFCTRL_BIT (1<<5) // peripheral flow controller
#define DMA_SCR_PFCTRL_OFFSET 5
#define DMA_SCR_DIR_MASK (0x3<<6)
#define DMA_SCR_DIR_OFFSET 6
#define DMA_SCR_CIRC_BIT (1<<8) // circular mode
#define DMA_SCR_CIRC_OFFSET 8
#define DMA_SCR_PINC_BIT (1<<9) // peripheral increment mode
#define DMA_SCR_PINC_OFFSET 9
#define DMA_SCR_MINC_BIT (1<<10) // memory increment mode
#define DMA_SCR_MINC_OFFSET 10
#define DMA_SCR_PSIZE_MASK (0x3<<11) // peripheral size
#define DMA_SCR_PSIZE_OFFSET 11
#define DMA_SCR_MSIZE_MASK (0x3<<13) // memory size
#define DMA_SCR_MSIZE_OFFSET 13
#define DMA_SCR_PINCOS_BIT (1<<15) // peripheral increment offset size
#define DMA_sCR_PINCOS_OFFSET 15
#define DMA_SCR_PL_MASK (0x3<<16) // priority level
#define DMA_SCR_PL_OFFSET 16
#define DMA_SCR_DBM_BIT (1<<18) // double-buffer mode
#define DMA_SCR_DBM_OFFSET 18
#define DMA_SCR_CT_BIT (1<<19) // current target (only in double-buffer mode)
#define DMA_SCR_CT_OFFSET 19
#define DMA_SCR_PBURST_MASK (0x3<<21)
#define DMA_SCR_PBURST_OFFSET 21
#define DMA_SCR_MBURST_MASK (0x3<<23)
#define DMA_SCR_MBURST_OFFSET 23
#define DMA_SCR_CHSEL_MASK (0x7<<25)
#define DMA_SCR_CHSEL_OFFSET 25

#define DMA_SFCR_FTH_MASK (0x3<<0)
#define DMA_SFCR_FTH_OFFSET 0
#define DMA_SFCR_DMDIS_BIT (1<<2)
#define DMA_SFCR_DMDIS_OFFSET 2
#define DMA_SFCR_FS_MASK (0x7<<3)
#define DMA_SFCR_FS_OFFSET 3
#define DMA_SFCR_FS_BIT (1<<7)

struct DMA_stream_regs {
  volatile uint32_t scr;
  volatile uint32_t sndtr;
  volatile uint32_t spar;
  volatile uint32_t sm0ar;
  volatile uint32_t sm1ar;
  volatile uint32_t sfcr;
};

struct DMA_regs {
  volatile uint32_t lisr;
  volatile uint32_t hisr;
  uint32_t lifcr;
  uint32_t hifcr;
  struct DMA_stream_regs streams[8];
};

void DMA_enableClock(DMA dma)
{
  struct RCC_regs* rcc = (struct RCC_regs*) RCC_BASE;

  switch (dma)
  {
    case DMA1:
      rcc->ahb1enr |= RCC_DMA1_EN;
      break;
    case DMA2:
      rcc->ahb1enr |= RCC_DMA2_EN;
  }
}

void DMA_disableClock(DMA dma)
{
  struct RCC_regs* rcc = (struct RCC_regs*) RCC_BASE;

  switch (dma)
  {
    case DMA1:
      rcc->ahb1enr &= ~RCC_DMA1_EN;
      break;
    case DMA2:
      rcc->ahb1enr &= ~RCC_DMA2_EN;
  }
}

void DMA_enable(DMA base, uint32_t stream)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;
  regs->streams[stream].scr |= DMA_SCR_EN_BIT;
}

void DMA_disable(DMA base, uint32_t stream)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;
  regs->streams[stream].scr &= ~DMA_SCR_EN_BIT;

  // wait until this stream is disabled
  while (regs->streams[stream].scr & DMA_SCR_EN_BIT);
}

void DMA_configureStream(DMA base, uint32_t stream, const DMAStreamConfiguration* pConfig)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;
  uint32_t val;

  if (stream > 7) return;

  val = regs->streams[stream].scr;

  val &= ~DMA_SCR_CHSEL_MASK;
  val |= (pConfig->channel << DMA_SCR_CHSEL_OFFSET) & DMA_SCR_CHSEL_MASK;

  val &= ~DMA_SCR_PFCTRL_BIT;
  val |= (pConfig->flowController << DMA_SCR_PFCTRL_OFFSET) & DMA_SCR_PFCTRL_BIT;

  val &= ~DMA_SCR_DIR_MASK;
  val |= (pConfig->direction << DMA_SCR_DIR_OFFSET) & DMA_SCR_DIR_MASK;

  val &= ~DMA_SCR_DBM_BIT;
  val |= (pConfig->doubleBufferMode << DMA_SCR_DBM_OFFSET) & DMA_SCR_DBM_BIT;

  val &= ~DMA_SCR_CIRC_BIT;
  val |= (pConfig->circularMode << DMA_SCR_CIRC_OFFSET) & DMA_SCR_CIRC_BIT;

  val &= ~DMA_SCR_PINC_BIT;
  val |= (pConfig->periphIncr << DMA_SCR_PINC_OFFSET) & DMA_SCR_PINC_BIT;

  val &= ~DMA_SCR_MINC_BIT;
  val |= (pConfig->memIncr << DMA_SCR_MINC_OFFSET) & DMA_SCR_MINC_BIT;

  val &= ~DMA_SCR_PSIZE_MASK;
  val |= (pConfig->periphSize << DMA_SCR_PSIZE_OFFSET) & DMA_SCR_PSIZE_MASK;

  val &= ~DMA_SCR_MSIZE_MASK;
  val |= (pConfig->memSize << DMA_SCR_MSIZE_OFFSET) & DMA_SCR_MSIZE_MASK;

  val &= ~DMA_SCR_PL_MASK;
  val |= (pConfig->priority << DMA_SCR_PL_OFFSET) & DMA_SCR_PL_MASK;

  val &= ~DMA_SCR_PBURST_MASK;
  val |= (pConfig->periphBurst << DMA_SCR_PBURST_OFFSET) & DMA_SCR_PBURST_MASK;

  val &= ~DMA_SCR_MBURST_MASK;
  val |= (pConfig->memBurst << DMA_SCR_MBURST_OFFSET) & DMA_SCR_MBURST_MASK;

  regs->streams[stream].scr = val;

  val = regs->streams[stream].sfcr;

  val &= ~DMA_SFCR_DMDIS_BIT;
  val |= (pConfig->FIFOMode << DMA_SFCR_DMDIS_OFFSET) & DMA_SFCR_DMDIS_BIT;

  val &= ~DMA_SFCR_FTH_MASK;
  val |= (pConfig->FIFOThreshold << DMA_SFCR_FTH_OFFSET) & DMA_SFCR_FTH_MASK;

  regs->streams[stream].sfcr = val;

  regs->streams[stream].sndtr = pConfig->numDataToTransfer;
  regs->streams[stream].spar = pConfig->periphAddr;
  regs->streams[stream].sm0ar = pConfig->memAddr0;
  regs->streams[stream].sm1ar = pConfig->memAddr1;
}

void DMA_getStreamConfiguration(DMA base, uint32_t stream, DMAStreamConfiguration* pConfig)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;

  pConfig->channel = (regs->streams[stream].scr & DMA_SCR_CHSEL_MASK) >> DMA_SCR_CHSEL_OFFSET;
  pConfig->direction = (regs->streams[stream].scr & DMA_SCR_DIR_MASK) >> DMA_SCR_DIR_OFFSET;
  pConfig->periphIncr = (regs->streams[stream].scr & DMA_SCR_PINC_BIT) >> DMA_SCR_PINC_OFFSET;
  pConfig->periphSize = (regs->streams[stream].scr & DMA_SCR_PSIZE_MASK) >> DMA_SCR_PSIZE_OFFSET;
  pConfig->periphBurst = (regs->streams[stream].scr & DMA_SCR_PBURST_MASK) >> DMA_SCR_PBURST_OFFSET;
  pConfig->memIncr = (regs->streams[stream].scr & DMA_SCR_MINC_BIT) >> DMA_SCR_MINC_OFFSET;
  pConfig->memSize = (regs->streams[stream].scr & DMA_SCR_MSIZE_MASK) >> DMA_SCR_MSIZE_OFFSET;
  pConfig->memBurst = (regs->streams[stream].scr & DMA_SCR_MBURST_MASK) >> DMA_SCR_MBURST_OFFSET;
  pConfig->doubleBufferMode = (regs->streams[stream].scr & DMA_SCR_DBM_BIT) >> DMA_SCR_DBM_OFFSET;
  pConfig->circularMode = (regs->streams[stream].scr & DMA_SCR_CIRC_BIT) >> DMA_SCR_CIRC_OFFSET;
  pConfig->flowController = (regs->streams[stream].scr & DMA_SCR_PFCTRL_BIT) >> DMA_SCR_PFCTRL_OFFSET;
  pConfig->priority = (regs->streams[stream].scr & DMA_SCR_PL_MASK) >> DMA_SCR_PL_OFFSET;
  pConfig->FIFOMode = (regs->streams[stream].scr & DMA_SFCR_DMDIS_BIT) >> DMA_SFCR_DMDIS_OFFSET;
  pConfig->FIFOThreshold = (regs->streams[stream].scr & DMA_SFCR_FTH_MASK) >> DMA_SFCR_FTH_OFFSET;
  pConfig->periphAddr = regs->streams[stream].spar;
  pConfig->memAddr0 = regs->streams[stream].sm0ar;
  pConfig->memAddr1 = regs->streams[stream].sm1ar;
  pConfig->numDataToTransfer = regs->streams[stream].sndtr;
}

uint32_t DMA_getStreamFlags(DMA base, uint32_t stream)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;
  const uint32_t mask = 0x2f;
  uint32_t status = 0;

  switch (stream)
  {
    case 0:
      status = regs->lisr & mask;
      break;
    case 1:
      status = (regs->lisr>>6) & mask;
      break;
    case 2:
      status = (regs->lisr>>16) & mask;
      break;
    case 3:
      status = (regs->lisr>>22) & mask;
      break;
    case 4:
      status = regs->hisr & mask;
      break;
    case 5:
      status = (regs->hisr>>6) & mask;
      break;
    case 6:
      status = (regs->hisr>>16) & mask;
      break;
    case 7:
      status = (regs->hisr>>22) & mask;
  }

  return status;
}

void DMA_clearStreamFlags(DMA base, uint32_t stream, uint32_t flags)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;
  const uint32_t mask = 0x3D; // only allow this stream's bits to be mutable
  flags &= mask;

  switch (stream)
  {
    case 0:
      regs->lifcr |= flags;
      break;
    case 1:
      regs->lifcr |= flags << 6;
      break;
    case 2:
      regs->lifcr |= flags << 16;
      break;
    case 3:
      regs->lifcr |= flags << 22;
      break;
    case 4:
      regs->hifcr |= flags;
      break;
    case 5:
      regs->hifcr |= flags << 6;
      break;
    case 6:
      regs->hifcr |= flags << 16;
      break;
    case 7:
      regs->hifcr |= flags << 22;
  }
}

void DMA_enableInterrupts(DMA base, uint32_t stream, uint32_t flags)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;

  // bitwise AND with 0x1E ensures only the interrupt bits are modified
  regs->streams[stream].scr |= flags & 0x1E;
  // FIFO error flag is in the sfcr register
  regs->streams[stream].scr |= flags & 1;
}

void DMA_disableInterrupts(DMA base, uint32_t stream, uint32_t flags)
{
  struct DMA_regs* regs = (struct DMA_regs*) base;

  regs->streams[stream].scr &= ~(flags & 0x1E);
  regs->streams[stream].sfcr &= ~(flags & 1);
}