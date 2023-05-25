#include "dcmi.h"
#include "rcc.h"

// DCMI_D0 -> PA9, PC6
// DCMI_D1 -> PA10, PC7
// DCMI_D2 -> PC8, PE0, PG10
// DCMI_D3 -> PC9, PE1, PG11
// DCMI_D4 -> PC11, PE4
// DCMI_D5 -> PB6, PD3
// DCMI_D6 -> PB8, PE5
// DCMI_D7 -> PB9, PE6
// DCMI_D8 -> PC10
// DCMI_D9 -> PC12
// DCMI_D10 -> PB5, PD6
// DCMI_D11 -> PD2, PF10
// DCMI_D12 -> PF11, PG6
// DCMI_D13 -> PG7, PG15
// DCMI_PIXCLK -> PA6
// DCMI_HSYNC -> PA4
// DCMI_VSYNC -> PB7, PG9

#define DCMI_CR_CAPTURE_BIT (1<<0)
#define DCMI_CR_CAPTURE_OFFSET 0
#define DCMI_CR_CM_BIT (1<<1)
#define DCMI_CR_CM_OFFSET 1
#define DCMI_CR_CROP_BIT (1<<2)
#define DCMI_CR_CROP_OFFSET 2
#define DCMI_CR_JPEG_BIT (1<<3)
#define DCMI_CR_ESS_BIT (1<<4)
#define DCMI_CR_ESS_OFFSET 4
#define DCMI_CR_PCKPOL_BIT (1<<5)
#define DCMI_CR_PCKPOL_OFFSET 5
#define DCMI_CR_HSPOL_BIT (1<<6)
#define DCMI_CR_HSPOL_OFFSET 6
#define DCMI_CR_VSPOL_BIT (1<<7)
#define DCMI_CR_VSPOL_OFFSET 7
#define DCMI_CR_FCRC_MASK (3<<8)
#define DCMI_CR_FCRC_OFFSET 8
#define DCMI_CR_EDM_MASK (3<<10)
#define DCMI_CR_EDM_OFFSET 10
#define DCMI_CR_ENABLE_BIT (1<<14)
#define DCMI_CR_BSM_MASK (3<<16)
#define DCMI_CR_BSM_OFFSET 16
#define DCMI_CR_OEBS_BIT (1<<18)
#define DCMI_CR_OEBS_OFFSET 18
#define DCMI_CR_LSM_BIT (1<<19)
#define DCMI_CR_LSM_OFFSET 19
#define DCMI_CR_OELS_BIT (1<<20)
#define DCMI_CR_OELS_OFFSET 20

#define DCMI_BASE 0x50050000

struct {
  uint32_t cr;
  uint32_t sr;
  uint32_t ris;
  uint32_t ier;
  uint32_t mis;
  uint32_t icr;
  uint32_t escr;
  uint32_t esur;
  uint32_t cwstrt;
  uint32_t cwsize;
  uint32_t dr;
} *DCMI_regs = (uint32_t) DCMI_BASE;

void DCMI_enableClock()
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;
  RCC_regs->ahb2enr |= RCC_DCMI_EN;
}

void DCMI_disableClock()
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;
  RCC_regs->ahb2enr &= ~RCC_DCMI_EN;
}

void DCMI_enable()
{
  DCMI_regs->cr |= DCMI_CR_ENABLE_BIT;
}

void DCMI_disable()
{
  DCMI_regs->cr &= ~DCMI_CR_ENABLE_BIT;
}