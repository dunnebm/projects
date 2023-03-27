#include "spi.h"
#include "rcc.h"

#define SPI_CR1_CPHA_BIT (1<<0)
#define SPI_CR1_CPHA_OFFSET 0
#define SPI_CR1_CPOL_BIT (1<<1)
#define SPI_CR1_CPOL_OFFSET 1
#define SPI_CR1_MSTR_BIT (1<<2)
#define SPI_CR1_MSTR_OFFSET 2
#define SPI_CR1_BR_MASK (7<<3)
#define SPI_CR1_BR_OFFSET 3
#define SPI_CR1_SPE_BIT (1<<6)
#define SPI_CR1_LSBFIRST_BIT (1<<7)
#define SPI_CR1_LSBFIRST_OFFSET 7
#define SPI_CR1_SSI_BIT (1<<8)
#define SPI_CR1_SSM_BIT (1<<9)
#define SPI_CR1_RXONLY_BIT (1<<10)
#define SPI_CR1_DFF_BIT (1<<11)
#define SPI_CR1_DFF_OFFSET 11
#define SPI_CR1_CRCNEXT_BIT (1<<12)
#define SPI_CR1_CRCEN_BIT (1<<13)
#define SPI_CR1_CRCEN_OFFSET 13
#define SPI_CR1_BIDIOE_BIT (1<<14)
#define SPI_CR1_BIDIMODE_BIT (1<<15)

#define SPI_CR2_RXDMAEN_BIT (1<<0)
#define SPI_CR2_TXDMAEN_BIT (1<<1)
#define SPI_CR2_SSOE_BIT (1<<2)
#define SPI_CR2_FRF_BIT (1<<4)
#define SPI_CR2_ERRIE_BIT (1<<5)
#define SPI_CR2_RXNEIE_BIT (1<<6)
#define SPI_CR2_TXEIE_BIT (1<<7)

struct SPI_regs {
  uint32_t cr1;
  uint32_t cr2;
  uint32_t sr;
  uint32_t dr;
  uint32_t crcpr;
  uint32_t rxcrcr;
  uint32_t txcrcr;
  uint32_t i2scfgr;
  uint32_t i2spr;
};

void SPI_enableClock(SPI spi)
{
  struct RCC_regs* regs = (struct RCC_regs*) RCC_BASE;
  switch (spi)
  {
    case SPI1:
      regs->apb2enr |= RCC_SPI1_EN;
      break;
    case SPI2:
      regs->apb2enr |= RCC_SPI2_EN;
      break;
    case SPI3:
      regs->apb2enr |= RCC_SPI3_EN;
      break;
    case SPI4:
      regs->apb2enr |= RCC_SPI4_EN;
  }
}

void SPI_disableClock(SPI spi)
{
  struct RCC_regs* regs = (struct RCC_regs*) RCC_BASE;
  switch (spi)
  {
    case SPI1:
      regs->apb2enr &= ~RCC_SPI1_EN;
      break;
    case SPI2:
      regs->apb2enr &= ~RCC_SPI2_EN;
      break;
    case SPI3:
      regs->apb2enr &= ~RCC_SPI3_EN;
      break;
    case SPI4:
      regs->apb2enr &= ~RCC_SPI4_EN;
  }
}

void SPI_enable(SPI base)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  regs->cr1 |= SPI_CR1_SPE_BIT;
}

void SPI_disable(SPI base)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  regs->cr1 &= ~SPI_CR1_SPE_BIT;
}

void SPI_configure(SPI base, const SPIConfiguration* pConfig)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  uint32_t val;

  val = regs->cr1;

  val &= ~SPI_CR1_BR_MASK;
  val |= (pConfig->baud << SPI_CR1_BR_OFFSET) & SPI_CR1_BR_MASK;

  val &= ~SPI_CR1_CPOL_BIT;
  val |= (pConfig->clockIdleState << SPI_CR1_CPOL_OFFSET) & SPI_CR1_CPOL_BIT;

  val &= ~SPI_CR1_CPHA_BIT;
  val |= (pConfig->clockPhase << SPI_CR1_CPHA_OFFSET) & SPI_CR1_CPHA_BIT;

  val &= ~SPI_CR1_LSBFIRST_BIT;
  val |= (pConfig->endianess << SPI_CR1_LSBFIRST_OFFSET) & SPI_CR1_LSBFIRST_BIT;

  val &= ~SPI_CR1_DFF_BIT;
  val |= (pConfig->frameSize << SPI_CR1_DFF_OFFSET) & SPI_CR1_DFF_BIT;

  val &= ~SPI_CR1_MSTR_BIT;
  val |= (pConfig->mode << SPI_CR1_MSTR_OFFSET) & SPI_CR1_MSTR_BIT;

  regs->cr1 = val;
}

void SPI_getConfig(SPI base, SPIConfiguration* pConfig)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  uint32_t cr1 = regs->cr1;

  pConfig->baud = (cr1 & SPI_CR1_BR_MASK) >> SPI_CR1_BR_OFFSET;
  pConfig->clockIdleState = (cr1 & SPI_CR1_CPOL_BIT) >> SPI_CR1_CPOL_OFFSET;
  pConfig->clockPhase = (cr1 & SPI_CR1_CPHA_BIT) >> SPI_CR1_CPHA_OFFSET;
  pConfig->endianess = (cr1 & SPI_CR1_LSBFIRST_BIT) >> SPI_CR1_LSBFIRST_OFFSET;
  pConfig->frameSize = (cr1 & SPI_CR1_DFF_BIT) >> SPI_CR1_DFF_OFFSET;
  pConfig->mode = (cr1 & SPI_CR1_MSTR_BIT) >> SPI_CR1_MSTR_OFFSET;
}

uint32_t SPI_getFlags(SPI base)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  return regs->sr;
}

void SPI_clearFlags(SPI base, uint32_t flags)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  regs->sr &= ~flags;
}

int SPI_read(SPI base, uint8_t* buf, int len)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  int i = 0;

  while (i < len)
  {
    if (regs->sr & SPI_FLAG_RXNE)
      buf[i++] = regs->dr;
  }

  return i;
}

int SPI_write(SPI base, const uint8_t* buf, int len)
{
  struct SPI_regs* regs = (struct SPI_regs*) base;
  int i = 0;

  while (i < len)
  {
    if (regs->sr & SPI_FLAG_TXE)
      regs->dr = buf[i++];
  }
  
  return i;
}