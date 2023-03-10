#include "exti.h"

#define EXTI_BASE 0x40013C00

struct {
  uint32_t imr;
  uint32_t emr;
  uint32_t rtsr;
  uint32_t ftsr;
  uint32_t swier;
  volatile uint32_t pr;
} *EXTI_regs = (void*) EXTI_BASE;

void EXTI_enableInterrupts(uint32_t mask, uint32_t edge)
{
  EXTI_regs->imr |= mask;
  
  switch (edge)
  {
    case EXTI_RISING_EDGE:
      EXTI_regs->rtsr |= mask;
      EXTI_regs->ftsr &= ~mask;
      break;
    case EXTI_FALLING_EDGE:
      EXTI_regs->rtsr &= ~mask;
      EXTI_regs->ftsr |= mask;
      break;
    case EXTI_BOTH_EDGES:
      EXTI_regs->rtsr |= mask;
      EXTI_regs->ftsr |= mask;
  }
}

void EXTI_disableInterrupts(uint32_t mask)
{
  EXTI_regs->imr &= ~mask;
}

uint32_t EXTI_getPendingEvents()
{
  return EXTI_regs->pr;
}

void EXTI_clearPendingEvents(uint32_t mask)
{
  EXTI_regs->pr |= mask;
}