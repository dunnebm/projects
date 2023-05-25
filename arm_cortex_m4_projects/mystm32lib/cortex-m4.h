#ifndef CORTEX_M4_H
#define CORTEX_M4_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

struct scb {
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

typedef enum {
  AHB_DIV_8 = (0<<2),
  AHB = (1<<2)
} SysTickClockSource;

void SCB_EnableUnalignTrap();
void SCB_DisableUnalignTrap();
void SCB_SetSysTickExceptionToPending();
void SCB_ClearPendingSysTickException();
void SCB_EnableUsageFault();
void SCB_DisableUsageFault();
void SCB_EnableBusFault();
void SCB_DisableBusFault();
void SCB_EnableMemFault();
void SCB_DisableMemFault();
uint32_t SCB_SysTickExceptionActive();

void SysTick_Start();
void SysTick_Stop();
uint32_t SysTick_DidCountFinish();
void SysTick_SetTimer(uint32_t time);
void SysTick_SetClockSource(SysTickClockSource source);
void SysTick_EnableIRQ();
void SysTick_DisableIRQ();
void SysTick_Handler();

void NVIC_EnableIRQ(uint32_t irq);
void NVIC_DisableIRQ(uint32_t irq);
void NVIC_SetPendingIRQ(uint32_t irq);
void NVIC_ClearPendingIRQ(uint32_t irq);
void NVIC_SetPriority(uint32_t irq, uint32_t priority);
void NVIC_ClearPriority(uint32_t irq, uint32_t priority);
uint32_t NVIC_GetPendingIRQ(uint32_t irq);
uint32_t NVIC_GetPriority(uint32_t irq);

#ifdef __cplusplus
}
#endif

#endif