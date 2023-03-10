#include "cortex-m4.h"

#define AUXILIARY_CONTROL_BASE 0xE000E008
#define SYSTEM_CONTROL_BLOCK_BASE 0xE000ED00
#define SYSTICK_BASE 0xE000E010
#define MEMORY_PROTECTION_UNIT_BASE 0xE000ED90

#define NVIC_ISER_BASE 0xE000E100
#define NVIC_ICER_BASE 0xE000E180
#define NVIC_ISPR_BASE 0xE000E200
#define NVIC_ICPR_BASE 0xE000E280
#define NVIC_IABR_BASE 0xE000E300
#define NVIC_IPR_BASE 0xE000E400
#define NVIC_STIR_BASE 0xE000EF00

#define COPROCESSOR_ACCESS_CONTROL_BASE 0xE000ED88
#define FPU_BASE 0xE000EF30

#define ACTLR 0xE000E008 // Auxiliary Control Register
#define STIR  0xE000EF00 // Software Triggered Interrupt Register
#define CPACR 0xE000ED88 // Coprocessor Access Control Register

/* CPUID base register */
#define IMPLEMENTER_OFFSET (1<<24)
#define IMPLEMENTER_MASK (0xFF<<24)
#define VARIANT_OFFSET (1<<20)
#define VARIANT_MASK (0xF<<20)
#define PARTNO_OFFSET (1<<4)
#define PARTNO_MASK (0xFFF<<4)
#define REVISION_OFFSET (1<<0)
#define REVISION_MASK (0xF<<0)

/* Interrupt control and state register (AIRCR) */
#define NMIPENDSET (1<<31)
#define PENDSVSET (1<<28)
#define PENDSVCLR (1<<27)
#define PENDSTSET (1<<26)
#define PENDSTCLR (1<<25)
#define ISRPENDING (1<<22)
#define VECTPENDING_OFFSET (1<<12)
#define VECTPENDING_MASK (0x7F<<16)
#define RETOBASE (1<<11)
#define VECTACTIVE_OFFSET (1<<0)
#define VECTACTIVE_MASK (0x1FF)

/* Configuration and control register (CCR) */
#define STKALIGN (1<<9)
#define BFHFNMIGN (1<<8)
#define DIV_0_TRP (1<<4)
#define UNALIGN_TRP (1<<3)
#define USERSETMPEND (1<<1)
#define NONBASESETHRDENA (1<<0)

/* System handler control and state register (SHCSR) */
#define USAGE_FAULT_ENABLE (1<<18)
#define BUS_FAULT_ENABLE (1<<17)
#define MEMORY_FAULT_ENABLE (1<<16)
#define SV_CALL_PENDING (1<<15)
#define BUS_FAULT_PENDING (1<<14)
#define MEMORY_FAULT_PENDING (1<<13)
#define USAGE_FAULT_PENDING (1<<12)
#define SYSTICK_ACTIVE (1<<11)
#define PEND_SV_ACTIVE (1<<10)
#define MONITOR_ACTIVE (1<<8)
#define SV_CALL_ACTIVE (1<<7)
#define USAGE_FAULT_ACTIVE (1<<3)
#define BUS_FAULT_ACTIVE (1<<1)
#define MEMORY_FAULT_ACTIVE (1<<0)

/* System control register (SCR) */
#define SEVEONPEN (1<<4)
#define SLEEPDEEP (1<<2)
#define SLEEPONEXIT (1<<1)

/* SysTick Control and Status Register (SYST_CSR) */
#define SYSTICK_ENABLE_BIT (1<<0)
#define SYSTICK_INTERRUPT_ENABLE_BIT (1<<1)
#define SYSTICK_CLKSOURCE_BIT (1<<2)
#define SYSTICK_COUNTFLAG_BIT (1<<16)
#define SYSTICK_COUNTFLAG_OFFSET 16

#define SYSCTL_BASE 0xE000ED00

struct sysctl_regs {
  uint32_t cpuid;
  uint32_t icsr;
  uint32_t vtor;
  uint32_t aircr;
  uint32_t scr;
  uint32_t ccr;
  uint32_t shpr1;
  uint32_t shpr2;
  uint32_t shpr3;
  uint32_t shcsr;
  uint32_t cfsr;
  uint32_t hfsr;
  uint32_t dfsr;
  uint32_t mmfar;
  uint32_t bfar;
  uint32_t afsr;
  uint32_t id_pfr0;
  uint32_t id_pfr1;
  uint32_t id_dfr0;
  uint32_t id_afr0;
  uint32_t id_mmfr0;
  uint32_t id_mmfr1;
  uint32_t id_mmfr2;
  uint32_t id_mmfr3;
  uint32_t id_isar0;
  uint32_t id_isar1;
  uint32_t id_isar2;
  uint32_t id_isar3;
  uint32_t id_isar4;
};

struct systick_regs {
  uint32_t ctrl;
  uint32_t load;
  uint32_t val;
  uint32_t calib;
};

void SysTick_Start()
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  regs->ctrl |= SYSTICK_ENABLE_BIT;
}

void SysTick_Stop()
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  regs->ctrl &= ~SYSTICK_ENABLE_BIT;
}

uint32_t SysTick_DidCountFinish()
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  uint32_t count_finished = (regs->ctrl & SYSTICK_COUNTFLAG_BIT) >> SYSTICK_COUNTFLAG_OFFSET;

  // If the count flag is set, clear it.
  if (count_finished)
    regs->ctrl &= ~SYSTICK_COUNTFLAG_BIT;

  return count_finished;
}

void SysTick_SetTimer(uint32_t time)
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  regs->load = time;
}

void SysTick_SetClockSource(SysTickClockSource source)
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  uint32_t val = regs->ctrl;
  val &= ~SYSTICK_CLKSOURCE_BIT;
  val |= source;
  regs->ctrl = val;
}

void SysTick_EnableIRQ()
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  regs->ctrl |= SYSTICK_INTERRUPT_ENABLE_BIT;
}

void SysTick_DisableIRQ()
{
  struct systick_regs* regs = (struct systick_regs*) SYSTICK_BASE;
  regs->ctrl &= ~SYSTICK_INTERRUPT_ENABLE_BIT;
}

void NVIC_EnableIRQ(uint32_t irq)
{
  uint32_t register_number = irq / 32;
  uint32_t bit = irq % 32;
  uint32_t* iser = (uint32_t*) NVIC_ISER_BASE;

  iser[register_number] |= bit;
}

void NVIC_DisableIRQ(uint32_t irq)
{
  uint32_t register_number = irq / 32;
  uint32_t bit = irq % 32;
  uint32_t* icer = (uint32_t*) NVIC_ICER_BASE;

  icer[register_number] |= bit;
}

void NVIC_SetPendingIRQ(uint32_t irq)
{
  uint32_t register_number = irq / 32;
  uint32_t bit = irq % 32;
  uint32_t* ispr = (uint32_t*) NVIC_ISPR_BASE;

  ispr[register_number] |= bit;
}

void NVIC_ClearPendingIRQ(uint32_t irq)
{
  uint32_t register_number = irq / 32;
  uint32_t bit = irq % 32;
  uint32_t* icpr = (uint32_t*) NVIC_ICPR_BASE;

  icpr[register_number] |= bit;
}

uint32_t NVIC_GetPendingIRQ(uint32_t irq)
{
  uint32_t register_number = irq / 32;
  uint32_t bit = irq % 32;
  uint32_t* icpr = (uint32_t*) NVIC_ISPR_BASE;

  return (icpr[register_number] & bit) >> bit;
}

void NVIC_SetPriority(uint32_t irq, uint32_t priority)
{
  uint32_t register_number = irq / 4;
  uint32_t offset = (irq % 4)*8;
  uint32_t* ipr = (uint32_t*) NVIC_IPR_BASE;

  uint32_t val = ipr[register_number];
  val &= ~(0xFF<<offset);
  val |= priority<<offset;
  ipr[register_number] = val;
}

uint32_t NVIC_GetPriority(uint32_t irq)
{
  uint32_t register_number = irq / 4;
  uint32_t offset = (irq % 4) * 8;
  uint32_t* ipr = (uint32_t*) NVIC_IPR_BASE;

  uint32_t priority = (ipr[register_number] & (0xFF<<offset)) >> offset; 

  return priority;
}

void SCB_EnableUnalignTrap()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->ccr |= UNALIGN_TRP;
}

void SCB_DisableUnalignTrap()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->ccr &= ~UNALIGN_TRP;
}

void SCB_SetSysTickExceptionToPending()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->icsr |= PENDSTSET;
}

void SCB_ClearPendingSysTickException()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->icsr |= PENDSTCLR;
}

void SCB_EnableUsageFault()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->shcsr |= USAGE_FAULT_ENABLE;
}

void SCB_DisableUsageFault()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->shcsr &= ~USAGE_FAULT_ENABLE;
}

void SCB_EnableBusFault()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->shcsr |= BUS_FAULT_ENABLE;
}

void SCB_DisableBusFault()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->shcsr &= ~BUS_FAULT_ENABLE;
}

void SCB_EnableMemFault()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->shcsr |= MEMORY_FAULT_ENABLE;
}

void SCB_DisableMemFault()
{
  struct sysctl_regs* regs = (struct sysctl_regs*) SYSCTL_BASE;
  regs->shcsr &= ~MEMORY_FAULT_ENABLE;
}