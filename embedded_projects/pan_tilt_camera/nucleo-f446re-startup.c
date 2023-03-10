#include <stdint.h>
#include "../mystm32lib/cortex-m4.h"
#include "../mystm32lib/usart.h"
#include "../mystm32lib/gpio.h"


extern uint32_t _stack;
extern uint32_t _text_start, _text_end;
extern uint32_t _rodata_start, _rodata_end;
extern uint32_t _la_data;
extern uint32_t _data_start, _data_end;
extern uint32_t _bss_start, _bss_end;

extern int main();
extern void __libc_init_array();

void Default_Handler()
{
  while (1);
}

void Reset_Handler(void);
void NMI_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void HardFault_Handler(void)  __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler(void)  __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler(void)        __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler(void)   __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler(void)     __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler(void)    __attribute__ ((weak, alias("Default_Handler")));

void WWDG_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler()                __attribute__ ((weak, alias("Default_Handler")));
void TAMP_STAMP_IRQHandler()         __attribute__ ((weak, alias("Default_Handler")));
void RTC_WKUP_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void FLASH_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void RCC_IRQHandler()                __attribute__ ((weak, alias("Default_Handler")));
void EXTI0_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void EXTI1_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void EXTI2_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void EXTI3_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void EXTI4_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream0_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream1_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream2_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream3_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream4_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream5_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream6_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void ADC_IRQHandler()                __attribute__ ((weak, alias("Default_Handler")));
void CAN1_TX_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX0_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void CAN1_RX1_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void EXTI9_5_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void TIM1_BRK_TIM9_IRQHandler()      __attribute__ ((weak, alias("Default_Handler")));
void TIM1_UP_TIM10_IRQHandler()      __attribute__ ((weak, alias("Default_Handler")));
void TIM1_TRG_COM_TIM11_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void TIM2_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void TIM3_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void TIM4_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void I2C1_EV_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void I2C1_ER_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void I2C2_EV_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void I2C2_ER_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void SPI1_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void SPI2_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void USART1_IRQHandler()             __attribute__ ((weak, alias("Default_Handler")));
void USART2_IRQHandler()             __attribute__ ((weak, alias("Default_Handler")));
void USART3_IRQHandler()             __attribute__ ((weak, alias("Default_Handler")));
void EXTI15_10_IRQHandler()          __attribute__ ((weak, alias("Default_Handler")));
void RTC_Alarm_IRQHandler()          __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_WKUP_IRQHandler()        __attribute__ ((weak, alias("Default_Handler")));
void TIM8_BRK_TIM12_IRQHandler()     __attribute__ ((weak, alias("Default_Handler")));
void TIM8_UP_TIM18_IRQ_Handler()     __attribute__ ((weak, alias("Default_Handler")));
void TIM8_TRG_COM_TIM14_IRQHandler() __attribute__ ((weak, alias("Default_Handler")));
void TIM8_CC_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void FMC_IRQHandler()                __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler()              __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler()             __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler()       __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler()             __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler()     __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler()      __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler()        __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler()             __attribute__ ((weak, alias("Default_Handler")));
void DCMI_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler()                __attribute__ ((weak, alias("Default_Handler")));
void SPI4_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void SAI1_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void SAI2_IRQHandler()               __attribute__ ((weak, alias("Default_Handler")));
void QUADSPI_IRQHandler()            __attribute__ ((weak, alias("Default_Handler")));
void CEC_IRQHandler()                __attribute__ ((weak, alias("Default_Handler")));
void SPDIF_RX_IRQHandler()           __attribute__ ((weak, alias("Default_Handler")));
void FMPI2C1_EV_IRQHandler()         __attribute__ ((weak, alias("Default_Handler")));
void FMPI2C1_ER_IRQHandler()         __attribute__ ((weak, alias("Default_Handler")));

uint32_t isr_table[] __attribute__ ((section(".isr_vectors"))) = {
  (uint32_t)&_stack,
  (uint32_t)&Reset_Handler,
  (uint32_t)&NMI_Handler,
  (uint32_t)&HardFault_Handler,
  (uint32_t)&MemManage_Handler,
  (uint32_t)&BusFault_Handler,
  (uint32_t)&UsageFault_Handler,
  0u,
  0u,
  0u,
  0u,
  (uint32_t)&PendSV_Handler,
  (uint32_t)&SysTick_Handler,
  (uint32_t)&WWDG_IRQHandler,
  (uint32_t)&PVD_IRQHandler,
  (uint32_t)&TAMP_STAMP_IRQHandler,
  (uint32_t)&RTC_WKUP_IRQHandler,
  (uint32_t)&FLASH_IRQHandler,
  (uint32_t)&RCC_IRQHandler,
  (uint32_t)&EXTI0_IRQHandler,
  (uint32_t)&EXTI1_IRQHandler,
  (uint32_t)&EXTI2_IRQHandler,
  (uint32_t)&EXTI3_IRQHandler,
  (uint32_t)&EXTI4_IRQHandler,
  (uint32_t)&DMA1_Stream0_IRQHandler,
  (uint32_t)&DMA1_Stream1_IRQHandler,
  (uint32_t)&DMA1_Stream2_IRQHandler,
  (uint32_t)&DMA1_Stream3_IRQHandler,
  (uint32_t)&DMA1_Stream4_IRQHandler,
  (uint32_t)&DMA1_Stream5_IRQHandler,
  (uint32_t)&DMA1_Stream6_IRQHandler,
  (uint32_t)&ADC_IRQHandler,
  (uint32_t)&CAN1_TX_IRQHandler,
  (uint32_t)&CAN1_RX0_IRQHandler,
  (uint32_t)&CAN1_RX1_IRQHandler,
  (uint32_t)&CAN1_SCE_IRQHandler,
  (uint32_t)&EXTI9_5_IRQHandler,
  (uint32_t)&TIM1_BRK_TIM9_IRQHandler,
  (uint32_t)&TIM1_UP_TIM10_IRQHandler,
  (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,
  (uint32_t)&TIM1_CC_IRQHandler,
  (uint32_t)&TIM2_IRQHandler,
  (uint32_t)&TIM3_IRQHandler,
  (uint32_t)&I2C1_EV_IRQHandler,
  (uint32_t)&I2C1_ER_IRQHandler,
  (uint32_t)&I2C2_EV_IRQHandler,
  (uint32_t)&I2C2_ER_IRQHandler,
  (uint32_t)&SPI1_IRQHandler,
  (uint32_t)&SPI2_IRQHandler,
  (uint32_t)&USART1_IRQHandler,
  (uint32_t)&USART2_IRQHandler,
  (uint32_t)&USART3_IRQHandler,
  (uint32_t)&EXTI15_10_IRQHandler,
  (uint32_t)&RTC_Alarm_IRQHandler,
  (uint32_t)&OTG_FS_WKUP_IRQHandler,
  (uint32_t)&TIM8_BRK_TIM12_IRQHandler,
  (uint32_t)&TIM8_TRG_COM_TIM14_IRQHandler,
  (uint32_t)&TIM8_CC_IRQHandler,
  (uint32_t)&DMA1_Stream7_IRQHandler,
  (uint32_t)&FMC_IRQHandler,
  (uint32_t)&SDIO_IRQHandler,
  (uint32_t)&TIM5_IRQHandler,
  (uint32_t)&SPI3_IRQHandler,
  (uint32_t)&UART4_IRQHandler,
  (uint32_t)&UART5_IRQHandler,
  (uint32_t)&TIM6_DAC_IRQHandler,
  (uint32_t)&TIM7_IRQHandler,
  (uint32_t)&DMA2_Stream0_IRQHandler,
  (uint32_t)&DMA2_Stream1_IRQHandler,
  (uint32_t)&DMA2_Stream2_IRQHandler,
  (uint32_t)&DMA2_Stream3_IRQHandler,
  (uint32_t)&DMA2_Stream4_IRQHandler,
  0u,
  0u,
  (uint32_t)&CAN2_TX_IRQHandler,
  (uint32_t)&CAN2_RX0_IRQHandler,
  (uint32_t)&CAN2_RX1_IRQHandler,
  (uint32_t)&CAN2_RX1_IRQHandler,
  (uint32_t)&CAN2_SCE_IRQHandler,
  (uint32_t)&OTG_FS_IRQHandler,
  (uint32_t)&DMA2_Stream5_IRQHandler,
  (uint32_t)&DMA2_Stream6_IRQHandler,
  (uint32_t)&DMA2_Stream7_IRQHandler,
  0u,
  0u,
  (uint32_t)&FPU_IRQHandler,
  0u,
  0u,
  (uint32_t)&SPI4_IRQHandler,
  0u,
  0u,
  (uint32_t)&SAI1_IRQHandler,
  0u,
  0u,
  0u,
  (uint32_t)&SAI2_IRQHandler,
  (uint32_t)&QUADSPI_IRQHandler,
  (uint32_t)&CEC_IRQHandler,
  (uint32_t)&SPDIF_RX_IRQHandler,
  (uint32_t)&FMPI2C1_EV_IRQHandler,
  (uint32_t)&FMPI2C1_ER_IRQHandler
};

void Reset_Handler(void)
{
  uint32_t size;
  uint32_t *pSrc, *pDst;

  // Load .data section from FLASH to SRAM
  size = (uint32_t)&_data_end - (uint32_t)&_data_start;
  pSrc = &_la_data;
  pDst = &_data_start;
  for (uint32_t i = 0; i < size; ++i)
    *pDst++ = *pSrc++;

  // Initialize .bss section to zero in SRAM
  size = (uint32_t)&_bss_end - (uint32_t)&_bss_start;
  pDst = &_bss_start;
  for (uint32_t i = 0; i < size; ++i)
    *pDst++ = 0;

  SCB_DisableUnalignTrap();
  SCB_EnableUsageFault();
  SCB_EnableBusFault();
  SCB_EnableMemFault();

  // GPIO pins PA2 and PA3 are used by USART2
  GPIO_enableClock(GPIOA);
  
  // Configure PA2 and PA3 to be used by USART2
  GPIO_setMode(GPIOA, GPIO_PIN_2 | GPIO_PIN_3, GPIO_MODE_ALT_FUNC);
  GPIO_setAltFunc(GPIOA, GPIO_PIN_2 | GPIO_PIN_3, GPIO_ALT_FUNC_7);

  // Initialize USART2 for standard I/O
  USART_enable(USART2);
  USART_enableReceiver(USART2);
  USART_enableTransmitter(USART2);

  __libc_init_array();

  main();

  // never return
  while (1) {}
}