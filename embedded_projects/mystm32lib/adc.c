#include "adc.h"
#include "rcc.h"

// ADC1 DMA reuest mapping: DMA2->stream0->channel0 and DMA2->stream4->channel0
// ADC2 DMA request mapping: DMA2->stream2->channel1 and DMA2->stream3->channel1
// ADC3 DMA request mapping: DMA2->stream0->channel2 and DMA2->stream1->channel2

#define ADC_CR1_AWDCH_MASK (0x1f<<0)
#define ADC_CR1_AWDCH_OFFSET 0
#define ADC_CR1_EOCIE_BIT (1<<5)
#define ADC_CR1_AWDIE_BIT (1<<6)
#define ADC_CR1_JEOCIE_BIT (1<<7)
#define ADC_CR1_SCAN_BIT (1<<8)
#define ADC_CR1_SCAN_OFFSET 8
#define ADC_CR1_AWDSGL_BIT (1<<9)
#define ADC_CR1_JAUTO_BIT (1<<10)
#define ADC_CR1_DISCEN_BIT (1<<11)
#define ADC_CR1_JDISCEN_BIT (1<<12)
#define ADC_CR1_DISCNUM_MASK (0x7<<13)
#define ADC_CR1_DISCNUM_OFFSET 13
#define ADC_CR1_JAWDEN_BIT (1<<22)
#define ADC_CR1_AWDEN_BIT (1<<23)
#define ADC_CR1_RES_MASK (0x3<<24)
#define ADC_CR1_RES_OFFSET 24
#define ADC_CR1_OVRIE_BIT (1<<26)

#define ADC_CR2_ADON_BIT (1<<0)
#define ADC_CR2_CONT_BIT (1<<1)
#define ADC_CR2_CONT_OFFSET 1
#define ADC_CR2_DMA_BIT (1<<8)
#define ADC_CR2_DMA_OFFSET 8
#define ADC_CR2_DDS_BIT (1<<9)
#define ADC_CR2_DDS_OFFSET 9
#define ADC_CR2_EOCS_BIT (1<<10)
#define ADC_CR2_EOCS_OFFSET 10
#define ADC_CR2_ALIGN_BIT (1<<11)
#define ADC_CR2_ALIGN_OFFSET 11
#define ADC_CR2_JEXTSEL_MASK (0xf<<16)
#define ADC_CR2_JEXTSEL_OFFSET 16
#define ADC_CR2_JEXTEN_MASK (0x3<<20)
#define ADC_CR2_JEXTEN_OFFSET 20
#define ADC_CR2_JSWSTART_BIT (1<<22)
#define ADC_CR2_EXTSEL_MASK (0xf<<24)
#define ADC_CR2_EXTSEL_OFFSET 24
#define ADC_CR2_EXTEN_MASK (0x3<<28)
#define ADC_CR2_EXTEN_OFFSET 28
#define ADC_CR2_SWSTART_BIT (1<<30)

#define ADC_SQR1_LENGTH_OFFSET 20

#define ADC_CSR_AWD1_BIT (1<<0)
#define ADC_CSR_EOC1_BIT (1<<1)
#define ADC_CSR_JEOC1_BIT (1<<2)
#define ADC_CSR_JSTRT1_BIT (1<<3)
#define ADC_CSR_STRT1_BIT (1<<4)
#define ADC_CSR_OVR1_BIT (1<<5)
#define ADC_CSR_AWD2_BIT (1<<8)
#define ADC_CSR_EOC2_BIT (1<<9)
#define ADC_CSR_JEOC2_BIT (1<<10)
#define ADC_CSR_JSTRT2_BIT (1<<11)
#define ADC_CSR_STRT2_BIT (1<<12)
#define ADC_CSR_OVR2_BIT (1<<13)
#define ADC_CSR_AWD3_BIT (1<<16)
#define ADC_CSR_EOC3_BIT (1<<17)
#define ADC_CSR_JEOC3_BIT (1<<18)
#define ADC_CSR_JSTRT3_BIT (1<<19)
#define ADC_CSR_STRT3_BIT (1<<20)
#define ADC_CSR_OVR3_BIT (1<<21)

#define ADC_CCR_MULTI_MASK (0x1f<<0)
#define ADC_CCR_MULTI_OFFSET 0
#define ADC_CCR_DELAY_MASK (0xf<<8)
#define ADC_CCR_DELAY_OFFSET 8
#define ADC_CCR_DDS_BIT (1<<13)
#define ADC_CCR_DMA_MASK (0x3<<14)
#define ADC_CCR_DMA_OFFSET 14
#define ADC_CCR_ADCPRE_MASK (0x3<<16)
#define ADC_CCR_ADCPRE_OFFSET 16
#define ADC_CCR_VBATE_BIT (1<<22)
#define ADC_CCR_TSVREFE_BIT (1<<23)

struct ADC_regs {
  volatile uint32_t sr;
  uint32_t cr1;
  uint32_t cr2;
  uint32_t smpr1;
  uint32_t smpr2;
  uint32_t jofr1;
  uint32_t jofr2;
  uint32_t jofr3;
  uint32_t jofr4;
  uint32_t htr;
  uint32_t ltr;
  uint32_t sqr1;
  uint32_t sqr2;
  uint32_t sqr3;
  volatile uint32_t jdr1;
  volatile uint32_t jdr2;
  volatile uint32_t jdr3;
  volatile uint32_t jdr4;
  volatile uint32_t dr;
};

struct ADC_common_regs {
  volatile uint32_t csr;
  uint32_t ccr;
  volatile uint32_t cdr;
};

void ADC_enable(ADC adc)
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;
  struct ADC_regs* ADC_regs = (struct ADC_regs*) adc;

  switch (adc)
  {
    case ADC1:
      RCC_regs->apb2enr |= RCC_ADC1_EN;
      break;
    case ADC2:
      RCC_regs->apb2enr |= RCC_ADC2_EN;
      break;
    case ADC3:
      RCC_regs->apb2enr |= RCC_ADC3_EN;
  }

  ADC_regs->cr2 |= ADC_CR2_ADON_BIT;
}

void ADC_disable(ADC adc)
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;
  struct ADC_regs* ADC_regs = (struct ADC_regs*) adc;

  ADC_regs->cr2 &= ~ADC_CR2_ADON_BIT;

  switch (adc)
  {
    case ADC1:
      RCC_regs->apb2enr &= ~RCC_ADC1_EN;
      break;
    case ADC2:
      RCC_regs->apb2enr &= ~RCC_ADC2_EN;
      break;
    case ADC3:
      RCC_regs->apb2enr &= ~RCC_ADC3_EN;
  }
}

void ADC_configure(ADC base, const ADCConfiguration* pConfig)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  uint32_t val;

  val = regs->cr1;

  val &= ~ADC_CR1_RES_MASK;
  val |= (pConfig->resolution << ADC_CR1_RES_OFFSET) & ADC_CR1_RES_MASK;

  val &= ~ADC_CR1_SCAN_BIT;
  val |= (pConfig->SCANMode << ADC_CR1_SCAN_OFFSET) & ADC_CR1_SCAN_BIT;

  val &= ~ADC_CR1_AWDCH_MASK;
  val |= (pConfig->AWDChannelSelect << ADC_CR1_AWDCH_OFFSET) & ADC_CR1_AWDCH_MASK;

  regs->cr1 = val;

  val = regs->cr2;

  val &= ~ADC_CR2_EXTEN_MASK;
  val |= (pConfig->triggerDetection << ADC_CR2_EXTEN_OFFSET) & ADC_CR2_EXTEN_MASK;

  val &= ~ADC_CR2_EXTSEL_MASK;
  val |= (pConfig->trigger << ADC_CR2_EXTSEL_OFFSET) & ADC_CR2_EXTSEL_MASK;

  val &= ~ADC_CR2_ALIGN_BIT;
  val |= (pConfig->dataAlignment << ADC_CR2_ALIGN_OFFSET) & ADC_CR2_ALIGN_BIT;

  val &= ~ADC_CR2_DDS_BIT;
  val |= (pConfig->DMATransferSelection << ADC_CR2_DDS_OFFSET) & ADC_CR2_DDS_BIT;

  val &= ~ADC_CR2_DMA_BIT;
  val |= (pConfig->DMAMode << ADC_CR2_DMA_OFFSET) & ADC_CR2_DMA_BIT;

  val &= ~ADC_CR2_CONT_BIT;
  val |= (pConfig->conversionMode << ADC_CR2_CONT_OFFSET) & ADC_CR2_CONT_BIT;

  val &= ~ADC_CR2_EOCS_BIT;
  val |= (pConfig->EOCSelect << ADC_CR2_EOCS_OFFSET) & ADC_CR2_EOCS_BIT;

  regs->cr2 = val;
}

void ADC_getConfiguration(ADC base, ADCConfiguration* pConfig)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;

  pConfig->resolution = (regs->cr1 & ADC_CR1_RES_MASK) >> ADC_CR1_RES_OFFSET;
  pConfig->SCANMode = (regs->cr1 & ADC_CR1_SCAN_BIT) >> ADC_CR1_SCAN_OFFSET;
  pConfig->AWDChannelSelect = (regs->cr1 & ADC_CR1_AWDCH_MASK) >> ADC_CR1_AWDCH_OFFSET;
  pConfig->triggerDetection = (regs->cr2 & ADC_CR2_EXTEN_MASK) >> ADC_CR2_EXTEN_OFFSET;
  pConfig->trigger = (regs->cr2 & ADC_CR2_EXTSEL_MASK) >> ADC_CR2_EXTSEL_OFFSET;
  pConfig->conversionMode = (regs->cr2 & ADC_CR2_CONT_BIT) >> ADC_CR2_CONT_OFFSET;
  pConfig->dataAlignment = (regs->cr2 & ADC_CR2_ALIGN_BIT) >> ADC_CR2_ALIGN_OFFSET;
  pConfig->DMATransferSelection = (regs->cr2 & ADC_CR2_DDS_BIT) >> ADC_CR2_DDS_OFFSET;
  pConfig->DMAMode = (regs->cr2 & ADC_CR2_DMA_BIT) >> ADC_CR2_DMA_OFFSET;
  pConfig->EOCSelect = (regs->cr2 & ADC_CR2_EOCS_BIT) >> ADC_CR2_EOCS_OFFSET;
}

void ADC_start(ADC base)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  regs->cr2 |= ADC_CR2_SWSTART_BIT;
}

void ADC_setSequence(ADC base, ADCChannel sequence[], uint8_t size)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  uint32_t val;
  uint32_t offset;
  uint32_t i;
  for (i = 0; i < size && i < 16; ++i)
  {
    if (i < 6)
    {
      val = regs->sqr3;
      offset = 5*i;
      val &= ~(0x1f<<offset);
      val |= (sequence[i] & 0x1f) << offset;
      regs->sqr3 = val;
    }
    else if (i >= 6 && i < 12)
    {
      val = regs->sqr2;
      offset = 5*(i-6);
      val &= ~(0x1f<<offset);
      val |= (sequence[i] & 0x1f) << offset;
      regs->sqr2 = val;
    }
    else
    {
      val = regs->sqr1;
      offset = 5*(i-12);
      val &= ~(0x1f<<offset);
      val |= (sequence[i] & 0x1f) << offset;
      regs->sqr1 = val;
    }
  }
  
  // set length field in sqr1 to i-1
  val = regs->sqr1;
  val &= ~(0xf<<20);
  val |= (i-1)<<20;
  regs->sqr1 = val;
}

void ADC_setChannelSamplingTime(ADC base, ADCChannel channel, uint32_t cycles)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  uint32_t val;
  uint32_t offset;
  
  if (channel < 10)
  {
    val = regs->smpr2;
    val &= ~(0x7<<channel);
    val |= (cycles & 0x7) << channel;
    regs->smpr2 = val;
  }
  else
  {
    val = regs->smpr1;
    offset = channel - 10;
    val &= ~(0x7<<offset);
    val |= (cycles & 0x7) << offset;
    regs->smpr2 = val;
  }
}

uint32_t ADC_read(ADC base)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  return regs->dr;
}

uint32_t ADC_getFlags(ADC base)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  return (uint32_t) regs->sr;
}

uint32_t ADC_clearFlags(ADC base, uint32_t flags)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  regs->sr &= ~flags;
}

void ADC_enableInterrupts(ADC base, uint32_t flags)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  if (flags & ADC_END_OF_CONVERSION_FLAG)
    regs->cr1 |= ADC_CR1_EOCIE_BIT;
  if (flags & ADC_ANALOG_WATCHDOG_FLAG)
    regs->cr1 |= ADC_CR1_AWDIE_BIT;
  if (flags & ADC_OVERRUN_ERROR_FLAG)
    regs->cr1 |= ADC_CR1_OVRIE_BIT;
}

void ADC_disableInterrupts(ADC base, uint32_t flags)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  if (flags & ADC_END_OF_CONVERSION_FLAG)
    regs->cr1 &= ~ADC_CR1_EOCIE_BIT;
  if (flags & ADC_ANALOG_WATCHDOG_FLAG)
    regs->cr1 &= ~ADC_CR1_AWDIE_BIT;
  if (flags & ADC_OVERRUN_ERROR_FLAG)
    regs->cr1 &= ~ADC_CR1_OVRIE_BIT;
}

uint32_t ADC_getDataRegisterAddr(ADC base)
{
  struct ADC_regs* regs = (struct ADC_regs*) base;
  return (uint32_t) &regs->dr;
}