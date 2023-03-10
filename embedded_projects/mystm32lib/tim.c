#include "tim.h"
#include "rcc.h"

#define TIM_CR1_CEN_BIT (1<<0)
#define TIM_CR1_CEN_OFFSET 0
#define TIM_CR1_UDIS_BIT (1<<1)
#define TIM_CR1_URS_BIT (1<<2)
#define TIM_CR1_OPM_BIT (1<<3)
#define TIM_CR1_OPM_OFFSET 3
#define TIM_CR1_DIR_BIT (1<<4)
#define TIM_CR1_DIR_OFFSET 4
#define TIM_CR1_CMS_MASK (3<<5)
#define TIM_CR1_CMS_OFFSET 5
#define TIM_CR1_ARPE_BIT (1<<7)
#define TIM_CR1_ARPE_OFFSET 7
#define TIM_CR1_CKD_MASK (3<<8)
#define TIM_CR1_CKD_OFFSET 8

#define TIM_CR2_CCPC_BIT (1<<0)
#define TIM_CR2_CCUS_BIT (1<<2)
#define TIM_CR2_CCDS_BIT (1<<3)
#define TIM_CR2_MMS_MASK (7<<4)
#define TIM_CR2_MMS_OFFSET 4
#define TIM_CR2_TI1S_BIT (1<<7)
#define TIM_CR2_OIS1_BIT (1<<8)
#define TIM_CR2_OIS1N_BIT (1<<9)
#define TIM_CR2_OIS2_BIT (1<<10)
#define TIM_CR2_OIS2N_BIT (1<<11)
#define TIM_CR2_OIS3_BIT (1<<12)
#define TIM_CR2_OIS3N_BIT (1<<13)
#define TIM_CR2_OIS4_BIT (1<<14)

#define TIM_SMCR_SMS_MASK (0x7<<0)
#define TIM_SMCR_SMS_OFFSET 0
#define TIM_SMCR_TS_MASK (0x7<<4)
#define TIM_SMCR_TS_OFFSET 4
#define TIM_SMCR_MSM_BIT (1<<7)
#define TIM_SMCR_ETF_MASK (0xf<<8)
#define TIM_SMCR_ETF_OFFSET 8
#define TIM_SMCR_ETPS_MASK (0x3<<12)
#define TIM_SMCR_ETPS_OFFSET 12
#define TIM_SMCR_ECE_BIT (1<<14)
#define TIM_SMCR_ETP_BIT (1<<15)

#define TIM_CCMR1_CC1S_MASK (3<<0)
#define TIM_CCMR1_CC1S_OFFSET 0
#define TIM_CCMR1_CC2S_MASK (3<<8)
#define TIM_CCMR1_CC2S_OFFSET 8

#define TIM_CCMR1_OC1FE_BIT (1<<2)
#define TIM_CCMR1_OC1FE_OFFSET 2
#define TIM_CCMR1_OC1PE_BIT (1<<3)
#define TIM_CCMR1_OC1PE_OFFSET 3
#define TIM_CCMR1_OC1M_MASK (7<<4)
#define TIM_CCMR1_OC1M_OFFSET 4
#define TIM_CCMR1_OC1CE_BIT (1<<7)
#define TIM_CCMR1_OC2FE_BIT (1<<10)
#define TIM_CCMR1_OC2FE_OFFSET 10
#define TIM_CCMR1_OC2PE_BIT (1<<11)
#define TIM_CCMR1_OC2PE_OFFSET 11
#define TIM_CCMR1_OC2M_MASK (7<<12)
#define TIM_CCMR1_OC2M_OFFSET 12
#define TIM_CCMR1_OC2CE_BIT (1<<15)

#define TIM_CCMR1_IC1PSC_MASK (3<<2)
#define TIM_CCMR1_IC1PSC_OFFSET 2
#define TIM_CCMR1_IC1F_MASK (0xf<<4)
#define TIM_CCMR1_IC1F_OFFSET 4
#define TIM_CCMR1_IC2PSC_MASK (3<<10)
#define TIM_CCMR1_IC2PSC_OFFSET 10
#define TIM_CCMR1_IC2F_MASK (0xf<<12)
#define TIM_CCMR1_IC2F_OFFSET 12

#define TIM_CCER_CC1E_BIT (1<<0)
#define TIM_CCER_CC1P_BIT (1<<1)
#define TIM_CCER_CC1NE_BIT (1<<2)
#define TIM_CCER_CC1NP_BIT (1<<3)
#define TIM_CCER_CC2E_BIT (1<<4)
#define TIM_CCER_CC2P_BIT (1<<5)
#define TIM_CCER_CC2NE_BIT (1<<6)
#define TIM_CCER_CC2NP_BIT (1<<7)
#define TIM_CCER_CC3E_BIT (1<<8)
#define TIM_CCER_CC3P_BIT (1<<9)
#define TIM_CCER_CC3NE_BIT (1<<10)
#define TIM_CCER_CC3NP_BIT (1<<11)
#define TIM_CCER_CC4E_BIT (1<<12)
#define TIM_CCER_CC4P_BIT (1<<13)

struct TIM_regs {
  uint32_t cr1;
  uint32_t cr2;
  uint32_t smcr;
  uint32_t dier;
  volatile uint32_t sr;
  uint32_t egr;
  uint32_t ccmr1;
  uint32_t ccmr2;
  uint32_t ccer;
  volatile uint32_t cnt;
  uint32_t psc;
  uint32_t arr;
  uint32_t rcr;
  volatile uint32_t ccr1;
  volatile uint32_t ccr2;
  volatile uint32_t ccr3;
  volatile uint32_t ccr4;
  uint32_t bdtr;
  uint32_t dcr;
  uint32_t dmar;
};

void TIM_enableClock(TIM tim)
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;

  switch (tim)
  {
    case TIM1:
      RCC_regs->apb2enr |= RCC_TIM1_EN;
      break;
    case TIM2:
      RCC_regs->apb1enr |= RCC_TIM2_EN;
      break;
    case TIM3:
      RCC_regs->apb1enr |= RCC_TIM3_EN;
      break;
    case TIM4:
      RCC_regs->apb1enr |= RCC_TIM4_EN;
      break;
    case TIM5:
      RCC_regs->apb1enr |= RCC_TIM5_EN;
      break;
    case TIM6:
      RCC_regs->apb1enr |= RCC_TIM6_EN;
      break;
    case TIM7:
      RCC_regs->apb1enr |= RCC_TIM7_EN;
      break;
    case TIM8:
      RCC_regs->apb2enr |= RCC_TIM8_EN;
  }
}

void TIM_disableClock(TIM tim)
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;

  switch (tim)
  {
    case TIM1:
      RCC_regs->apb2enr &= ~RCC_TIM1_EN;
      break;
    case TIM2:
      RCC_regs->apb1enr &= ~RCC_TIM2_EN;
      break;
    case TIM3:
      RCC_regs->apb1enr &= ~RCC_TIM3_EN;
      break;
    case TIM4:
      RCC_regs->apb1enr &= ~RCC_TIM4_EN;
      break;
    case TIM5:
      RCC_regs->apb1enr &= ~RCC_TIM5_EN;
      break;
    case TIM6:
      RCC_regs->apb1enr &= ~RCC_TIM6_EN;
      break;
    case TIM7:
      RCC_regs->apb1enr &= ~RCC_TIM7_EN;
      break;
    case TIM8:
      RCC_regs->apb2enr &= ~RCC_TIM8_EN;
  }
}

void TIM_configure(TIM base, const TIMConfiguration* pConfig)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  uint32_t val;

  val = regs->cr1;
  val &= ~TIM_CR1_DIR_BIT;
  val |= (pConfig->countDirection << TIM_CR1_DIR_OFFSET) & TIM_CR1_DIR_BIT;

  val &= ~TIM_CR1_OPM_BIT;
  val |= (pConfig->onePulseMode << TIM_CR1_OPM_OFFSET) & TIM_CR1_OPM_BIT;

  val &= ~TIM_CR1_CMS_MASK;
  val |= (pConfig->alignmentSelect << TIM_CR1_CMS_OFFSET) & TIM_CR1_CMS_MASK;

  val &= ~TIM_CR1_ARPE_BIT;
  val |= (pConfig->autoReloadPreload << TIM_CR1_ARPE_OFFSET) & TIM_CR1_ARPE_BIT;

  regs->cr1 = val;

  val = regs->cr2;

  val &= ~TIM_CR2_MMS_MASK;
  val |= (pConfig->trgoSelect << TIM_CR2_MMS_OFFSET) & TIM_CR2_MMS_MASK;

  regs->cr2 = val;

  val = regs->smcr;

  val &= ~TIM_SMCR_SMS_MASK;
  val |= (pConfig->trgiSelect << TIM_SMCR_SMS_OFFSET) & TIM_SMCR_SMS_MASK;

  regs->smcr = val;   
}

static void configureChannelAsOutputCompare(TIM base, uint32_t channel, const TIMChannelConfiguration* pConfig)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  uint32_t val;

  switch (channel)
  {
    case 1:
      val = regs->ccmr1;
      val &= ~TIM_CCMR1_CC1S_MASK;
      val |= (pConfig->mode << TIM_CCMR1_CC1S_OFFSET) & TIM_CCMR1_CC1S_MASK;
      
      val &= ~TIM_CCMR1_OC1PE_BIT;
      val |= (pConfig->outputConfig.preloadEnable << TIM_CCMR1_OC1PE_OFFSET) & TIM_CCMR1_OC1PE_BIT;

      val &= ~TIM_CCMR1_OC1FE_BIT;
      val |= (pConfig->outputConfig.fastEnable << TIM_CCMR1_OC1FE_OFFSET) & TIM_CCMR1_OC1FE_BIT;

      val &= ~TIM_CCMR1_OC1M_MASK;
      val |= (pConfig->outputConfig.mode << TIM_CCMR1_OC1M_OFFSET) & TIM_CCMR1_OC1M_MASK;

      regs->ccmr1 = val;
      break;
    case 2:
      val = regs->ccmr1;
      val &= ~TIM_CCMR1_CC2S_MASK;
      val |= (pConfig->mode << TIM_CCMR1_CC2S_OFFSET) & TIM_CCMR1_CC2S_MASK;
      
      val &= ~TIM_CCMR1_OC2PE_BIT;
      val |= (pConfig->outputConfig.preloadEnable << TIM_CCMR1_OC2PE_OFFSET) & TIM_CCMR1_OC2PE_BIT;

      val &= ~TIM_CCMR1_OC1FE_BIT;
      val |= (pConfig->outputConfig.fastEnable << TIM_CCMR1_OC2FE_OFFSET) & TIM_CCMR1_OC2FE_BIT;

      val &= ~TIM_CCMR1_OC1M_MASK;
      val |= (pConfig->outputConfig.mode << TIM_CCMR1_OC2M_OFFSET) & TIM_CCMR1_OC2M_MASK;

      regs->ccmr1 = val;
      break;
    case 3:
      val = regs->ccmr2;
      val &= ~TIM_CCMR1_CC1S_MASK;
      val |= (pConfig->mode << TIM_CCMR1_CC1S_OFFSET) & TIM_CCMR1_CC1S_MASK;
      
      val &= ~TIM_CCMR1_OC1PE_BIT;
      val |= (pConfig->outputConfig.preloadEnable << TIM_CCMR1_OC1PE_OFFSET) & TIM_CCMR1_OC1PE_BIT;

      val &= ~TIM_CCMR1_OC1FE_BIT;
      val |= (pConfig->outputConfig.fastEnable << TIM_CCMR1_OC1FE_OFFSET) & TIM_CCMR1_OC1FE_BIT;

      val &= ~TIM_CCMR1_OC1M_MASK;
      val |= (pConfig->outputConfig.mode << TIM_CCMR1_OC1M_OFFSET) & TIM_CCMR1_OC1M_MASK;

      regs->ccmr2 = val;
      break;
    case 4:
      val = regs->ccmr2;
      val &= ~TIM_CCMR1_CC2S_MASK;
      val |= (pConfig->mode << TIM_CCMR1_CC2S_OFFSET) & TIM_CCMR1_CC2S_MASK;
      
      val &= ~TIM_CCMR1_OC2PE_BIT;
      val |= (pConfig->outputConfig.preloadEnable << TIM_CCMR1_OC2PE_OFFSET) & TIM_CCMR1_OC2PE_BIT;

      val &= ~TIM_CCMR1_OC2FE_BIT;
      val |= (pConfig->outputConfig.fastEnable << TIM_CCMR1_OC2FE_OFFSET) & TIM_CCMR1_OC2FE_BIT;

      val &= ~TIM_CCMR1_OC2M_MASK;
      val |= (pConfig->outputConfig.mode << TIM_CCMR1_OC2M_OFFSET) & TIM_CCMR1_OC2M_MASK;

      regs->ccmr2 = val;
  }
}

static void configureChannelAsInputCapture(TIM base, uint32_t channel, const TIMChannelConfiguration* pConfig)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  uint32_t val;

  switch (channel)
  {
    case 1:
      val = regs->ccmr1;
      val &= ~TIM_CCMR1_IC1PSC_MASK;
      val |= (pConfig->inputConfig.prescaler << TIM_CCMR1_IC1PSC_OFFSET) & TIM_CCMR1_IC1PSC_MASK;
      
      val &= ~TIM_CCMR1_IC1F_MASK;
      val |= (pConfig->inputConfig.filter << TIM_CCMR1_IC1F_OFFSET) & TIM_CCMR1_IC1F_MASK;

      regs->ccmr1 = val;
      break;
    case 2:
      val = regs->ccmr1;
      val &= ~TIM_CCMR1_IC2PSC_MASK;
      val |= (pConfig->inputConfig.prescaler << TIM_CCMR1_IC2PSC_OFFSET) & TIM_CCMR1_IC2PSC_MASK;
      
      val &= ~TIM_CCMR1_IC2F_MASK;
      val |= (pConfig->inputConfig.filter << TIM_CCMR1_IC2F_OFFSET) & TIM_CCMR1_IC2F_MASK;

      regs->ccmr1 = val;
      break;
    case 3:
      val = regs->ccmr2;
      val &= ~TIM_CCMR1_IC1PSC_MASK;
      val |= (pConfig->inputConfig.prescaler << TIM_CCMR1_IC1PSC_OFFSET) & TIM_CCMR1_IC1PSC_MASK;
      
      val &= ~TIM_CCMR1_IC1F_MASK;
      val |= (pConfig->inputConfig.filter << TIM_CCMR1_IC1F_OFFSET) & TIM_CCMR1_IC1F_MASK;

      regs->ccmr2 = val;
      break;
    case 4:
      val = regs->ccmr2;
      val &= ~TIM_CCMR1_IC2PSC_MASK;
      val |= (pConfig->inputConfig.prescaler << TIM_CCMR1_IC2PSC_OFFSET) & TIM_CCMR1_IC2PSC_MASK;
      
      val &= ~TIM_CCMR1_IC2F_MASK;
      val |= (pConfig->inputConfig.filter << TIM_CCMR1_IC2F_OFFSET) & TIM_CCMR1_IC2F_MASK;

      regs->ccmr2 = val;
  }
}

void TIM_configureChannel(TIM base, uint32_t channel, const TIMChannelConfiguration* pConfig)
{
  if (pConfig->mode == TIM_CHANNEL_MODE_OUTPUT_COMPARE)
    configureChannelAsOutputCompare(base, channel, pConfig);
  else
    configureChannelAsInputCapture(base, channel, pConfig);
}

void TIM_start(TIM base)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->cr1 |= TIM_CR1_CEN_BIT;
}

void TIM_stop(TIM base)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->cr1 &= ~TIM_CR1_CEN_BIT;
}

void TIM_enableChannel(TIM base, uint32_t channel)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;

  if (channel == 1)
    regs->ccer |= TIM_CCER_CC1E_BIT;
  else if (channel == 2)
    regs->ccer |= TIM_CCER_CC2E_BIT;
  else if (channel == 3)
    regs->ccer |= TIM_CCER_CC3E_BIT;
  else if (channel == 4)
    regs->ccer |= TIM_CCER_CC4E_BIT;
}

void TIM_disableChannel(TIM base, uint32_t channel)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;

  if (channel == 1)
    regs->ccer &= ~TIM_CCER_CC1E_BIT;
  else if (channel == 2)
    regs->ccer &= ~TIM_CCER_CC2E_BIT;
  else if (channel == 3)
    regs->ccer &= ~TIM_CCER_CC3E_BIT;
  else if (channel == 4)
    regs->ccer &= ~TIM_CCER_CC4E_BIT;
}

void TIM_setAutoReloadValue(TIM base, uint32_t val)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->arr = val;
}

void TIM_setPrescaler(TIM base, uint32_t val)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->psc = val;
}

uint32_t TIM_getCount(TIM base)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  return regs->cnt;
}

void TIM_setChannelValue(TIM base, uint32_t channel, uint32_t val)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  if (channel == 1)
    regs->ccr1 = val;
  else if (channel == 2)
    regs->ccr2 = val;
  else if (channel == 3)
    regs->ccr3 = val;
  else if (channel == 4)
    regs->ccr4 = val;
}

uint32_t TIM_getChannelValue(TIM base, uint32_t channel)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  uint32_t retval = 0xffffffff;

  if (channel == 1)
    retval = regs->ccr1;
  else if (channel == 2)
    retval = regs->ccr2;
  else if (channel == 3)
    retval = regs->ccr3;
  else if (channel == 4)
    retval = regs->ccr4;

  return retval;
}

uint32_t TIM_getEvents(TIM base)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  return regs->sr;
}

void TIM_clearEvents(TIM base, uint32_t flags)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->sr &= ~flags;
}

void TIM_enableInterrupts(TIM base, uint32_t flags)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->dier |= flags;
}

void TIM_disableInterrupts(TIM base, uint32_t flags)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->dier &= ~flags;
}

void TIM_enableDMARequests(TIM base, uint32_t flags)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->dier |= flags << 8;
}

void TIM_disableDMARequests(TIM base, uint32_t flags)
{
  struct TIM_regs* regs = (struct TIM_regs*) base;
  regs->dier &= ~(flags << 8);
}