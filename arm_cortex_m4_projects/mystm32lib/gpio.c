#include "gpio.h"
#include "rcc.h"

struct GPIO_regs {
  uint32_t moder;
  uint32_t otyper;
  uint32_t ospeeder;
  uint32_t pupdr;
  volatile uint32_t idr;
  uint32_t odr;
  uint32_t bsrr;
  uint32_t lckr;
  uint32_t afrl;
  uint32_t afrh;
};

void GPIO_enableClock(GPIO gpio)
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;

  switch (gpio)
  {
    case GPIOA:
      RCC_regs->ahb1enr |= RCC_GPIOA_EN;
      break;
    case GPIOB:
      RCC_regs->ahb1enr |= RCC_GPIOB_EN;
      break;
    case GPIOC:
      RCC_regs->ahb1enr |= RCC_GPIOC_EN;
      break;
    case GPIOD:
      RCC_regs->ahb1enr |= RCC_GPIOD_EN;
      break;
    case GPIOE:
      RCC_regs->ahb1enr |= RCC_GPIOE_EN;
      break;
    case GPIOF:
      RCC_regs->ahb1enr |= RCC_GPIOF_EN;
      break;
    case GPIOG:
      RCC_regs->ahb1enr |= RCC_GPIOG_EN;
      break;
    case GPIOH:
      RCC_regs->ahb1enr |= RCC_GPIOH_EN;
  }
}

void GPIO_disableClock(GPIO gpio)
{
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;

  switch (gpio)
  {
    case GPIOA:
      RCC_regs->ahb1enr &= ~RCC_GPIOA_EN;
      break;
    case GPIOB:
      RCC_regs->ahb1enr &= ~RCC_GPIOB_EN;
      break;
    case GPIOC:
      RCC_regs->ahb1enr &= ~RCC_GPIOC_EN;
      break;
    case GPIOD:
      RCC_regs->ahb1enr &= ~RCC_GPIOD_EN;
      break;
    case GPIOE:
      RCC_regs->ahb1enr &= ~RCC_GPIOE_EN;
      break;
    case GPIOF:
      RCC_regs->ahb1enr &= ~RCC_GPIOF_EN;
      break;
    case GPIOG:
      RCC_regs->ahb1enr &= ~RCC_GPIOG_EN;
      break;
    case GPIOH:
      RCC_regs->ahb1enr &= ~RCC_GPIOH_EN;
  }
}

void GPIO_write(GPIO base, uint32_t val)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  regs->odr = (uint16_t) val;
}

void GPIO_set(GPIO base, uint32_t pin_mask)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  regs->bsrr = pin_mask << 16;
}

void GPIO_clear(GPIO base, uint32_t pin_mask)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  regs->bsrr = pin_mask & 0xffff;
}

uint32_t GPIO_readOutputData(GPIO base)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  return regs->odr;
}

uint32_t GPIO_readInputData(GPIO base)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  return regs->idr;
}

void GPIO_setMode(GPIO base, GPIO_PINS pin_mask, GPIO_MODE mode)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  for (uint32_t i = 0; i < 16; ++i)
  {
    if (pin_mask & 1<<i)
    {
      uint32_t val = regs->moder;
      val &= ~(3 << (2*i));
      val |= (uint32_t) mode << (2*i);
      regs->moder = val;
    }
  }
}

void GPIO_setOutputType(GPIO base, GPIO_PINS pin_mask, GPIO_OUTPUT_TYPE otype)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  for (uint32_t i = 0; i < 16; ++i)
  {
    if (pin_mask & 1<<i)
    {
      uint32_t val = regs->otyper;
      val &= ~(1<<i);
      val |= (uint32_t) otype << i;
      regs->otyper = val;
    }
  }
}

void GPIO_setOutputSpeed(GPIO base, GPIO_PINS pin_mask, GPIO_OUTPUT_SPEED ospeed)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  for (uint32_t i = 0; i < 16; ++i)
  {
    if (pin_mask & 1<<i)
    {
      uint32_t val = regs->ospeeder;
      val &= ~(3 << (2*i));
      val |= (uint32_t) ospeed << (2*i);
      regs->ospeeder = val;
    }
  }
}

void GPIO_setInputConfig(GPIO base, GPIO_PINS pin_mask, GPIO_INPUT_CONFIG iconfig)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  for (uint32_t i = 0; i < 16; ++i)
  {
    if (pin_mask & 1<<i)
    {
      uint32_t val = regs->pupdr;
      val &= ~(3 << (2*i));
      val |= (uint32_t) iconfig << (2*i);
      regs->pupdr = val;
    }
  }
}

void GPIO_setAltFunc(GPIO base, GPIO_PINS pin_mask, GPIO_ALT_FUNC gpio_alt_func)
{
  struct GPIO_regs* regs = (struct GPIO_regs*) base;
  for (uint32_t i = 0; i < 16; ++i)
  {
    if (pin_mask & 1<<i)
    {
      uint32_t val;
      if (i < 8)
      {
        val = regs->afrl;
        val &= ~(0xf << (4*i));
        val |= (uint32_t) gpio_alt_func << (4*i);
        regs->afrl = val;
      }
      else
      {
        uint32_t j = i - 8;
        val = regs->afrh;
        val &= ~(0xf << (4*j));
        val |= (uint32_t) gpio_alt_func << (j*4);
        regs->afrh = val;
      }
    }
  }
}