#ifndef RCC_H
#define RCC_H

#ifdef __cplusplus
extern "C" {
#endif


/* RCC base address */
#define RCC_BASE 0x40023800

/* RCC clock control register flags */
#define RCC_HSI_ON (1<<0)
#define RCC_HSI_RDY (1<<1)
#define RCC_HSI_TRIM (1<<3)
#define RCC_HSI_CAL (1<<8)
#define RCC_HSE_ON (1<<16)
#define RCC_HSE_RDY (1<<17)
#define RCC_HSE_BYP (1<<18)
#define RCC_CSS_ON (1<<19)
#define RCC_PLL_ON (1<<24)
#define RCC_PLL_RDY (1<<25)
#define RCC_PLLI2S_ON (1<<26)
#define RCC_PLLI2S_RDY (1<<27)
#define RCC_PLLSAI_ON (1<<28)
#define RCC_PLLSAI_RDY (1<<29)

/* RCC PLL configuration register flags */
#define RCC_PLLM (1<<0)
#define RCC_PLLN (1<<6)
#define RCC_PLLP (1<<16)
#define RCC_PLLSRC (1<<22)
#define RCC_PLLQ (1<<24)
#define RCC_PLLR (1<<28)

/* RCC clock configuration register flags */
#define RCC_SW (1<<0)
#define RCC_SWS (1<<2)
#define RCC_HPRE (1<<4)
#define RCC_PPRE1 (1<<10)
#define RCC_RTCPRE (1<<16)
#define RCC_MC01 (1<<21)
#define RCC_MC01_PRE (1<<24)
#define RCC_MC02_PRE (1<<27)
#define RCC_MC02 (1<<30)

/* RCC clock interrupt register flags */
#define RCC_LSI_RDYF (1<<0)
#define RCC_LSE_RDYF (1<<1)
#define RCC_HSI_RDYF (1<<2)
#define RCC_HSE_RDYF (1<<3)
#define RCC_PLL_RDYF (1<<4)
#define RCC_PLLI2S_RDYF (1<<5)
#define RCC_PLLSAI_RDYF (1<<6)
#define RCC_CSSF (1<<7)
#define RCC_LSI_RDYIE (1<<8)
#define RCC_LSE_RDYIE (1<<9)
#define RCC_HSI_RDYIE (1<<10)
#define RCC_HSE_RDYIE (1<<11)
#define RCC_PLL_RDYIE (1<<12)
#define RCC_PLLI2S_RDYIE (1<<13)
#define RCC_PLLSAI_RDYIE (1<<14)
#define RCC_LSI_RDYC (1<<16)
#define RCC_LSE_RDYC (1<<17)
#define RCC_HSI_RDYC (1<<18)
#define RCC_HSE_RDYC (1<<19)
#define RCC_PLL_RDYC (1<<20)
#define RCC_PLLI2S_RDYC (1<<21)
#define RCC_PLLSAI_RDYC (1<<22)
#define RCC_CSSC (1<<23)

/* RCC AHB1 peripheral reset register flags */
#define RCC_GPIOA_RST (1<<0)
#define RCC_GPIOB_RST (1<<1)
#define RCC_GPIOC_RST (1<<2)
#define RCC_GPIOD_RST (1<<3)
#define RCC_GPIOE_RST (1<<4)
#define RCC_GPIOF_RST (1<<5)
#define RCC_GPIOG_RST (1<<6)
#define RCC_GPIOH_RST (1<<7)
#define RCC_CRC_RST (1<<12)
#define RCC_DMA1_RST (1<<21)
#define RCC_DMA2_RST (1<<22)
#define RCC_OTGHS_RST (1<<29)

/* RCC AHB2 peripheral reset register */
#define RCC_DCMI_RST (1<<0)
#define RCC_OTGFS_RST (1<<7)

/* RCC AHB3 peripheral reset register */
#define RCC_FMC_RST (1<<0)
#define RCC_QSPI_RST (1<<1)

/* RCC APB1 peripheral reset register */
#define RCC_TIM2_RST (1<<0)
#define RCC_TIM3_RST (1<<1)
#define RCC_TIM4_RST (1<<2)
#define RCC_TIM5_RST (1<<3)
#define RCC_TIM6_RST (1<<4)
#define RCC_TIM7_RST (1<<5)
#define RCC_TIM12_RST (1<<6)
#define RCC_TIM13_RST (1<<7)
#define RCC_TIM14_RST (1<<8)
#define RCC_WWDG_RST (1<<11)
#define RCC_SPI2_RST (1<<14)
#define RCC_SPI3_RST (1<<15)
#define RCC_SPDIFRX_RST (1<<16)
#define RCC_UART2_RST (1<<17)
#define RCC_UART3_RST (1<<18)
#define RCC_UART4_RST (1<<19)
#define RCC_UART5_RST (1<<20)
#define RCC_I2C1_RST (1<<21)
#define RCC_I2C2_RST (1<<22)
#define RCC_I2C3_RST (1<<23)
#define RCC_FMPI2C1_RST (1<<24)
#define RCC_CAN1_RST (1<<25)
#define RCC_CAN2_RST (1<<26)
#define RCC_CEC_RST (1<<27)
#define RCC_PWR_RST (1<<28)
#define RCC_DAC_RST (1<<29)

/* RCC APB2 peripheral reset register */
#define RCC_TIM1_RST (1<<0)
#define RCC_TIM8_RST (1<<1)
#define RCC_USART1_RST (1<<4)
#define RCC_USART6_RST (1<<6)
#define RCC_ADC_RST (1<<8)
#define RCC_SDIO_RST (1<<11)
#define RCC_SPI1_RST (1<<12)
#define RCC_SPI4_RST (1<<13)
#define RCC_SYSCFG_RST (1<<14)
#define RCC_TIM9_RST (1<<16)
#define RCC_TIM10_RST (1<<17)
#define RCC_TIM11_RST (1<<18)
#define RCC_SAI1_RST (1<<22)
#define RCC_SAI2_RST (1<<23)

/* RCC AHB1 peripheral clock enable register flags */
#define RCC_GPIOA_EN (1<<0)
#define RCC_GPIOB_EN (1<<1)
#define RCC_GPIOC_EN (1<<2)
#define RCC_GPIOD_EN (1<<3)
#define RCC_GPIOE_EN (1<<4)
#define RCC_GPIOF_EN (1<<5)
#define RCC_GPIOG_EN (1<<6)
#define RCC_GPIOH_EN (1<<7)
#define RCC_CRC_EN (1<<12)
#define RCC_BKPSRAM_EN (1<<18)
#define RCC_DMA1_EN (1<<21)
#define RCC_DMA2_EN (1<<22)
#define RCC_OTGHS_EN (1<<29)
#define RCC_OTGHSULPI_EN (1<<30)

/* RCC AHB2 peripheral clock enable register flags */
#define RCC_DCMI_EN (1<<0)
#define RCC_OTGFS_EN (1<<7)

/* RCC AHB3 peripheral clock enable register flags */
#define RCC_FMC_EN (1<<0)
#define RCC_QSPI_EN (1<<1)

/* RCC APB1 peripheral clock enable register flags */
#define RCC_TIM2_EN (1<<0)
#define RCC_TIM3_EN (1<<1)
#define RCC_TIM4_EN (1<<2)
#define RCC_TIM5_EN (1<<3)
#define RCC_TIM6_EN (1<<4)
#define RCC_TIM7_EN (1<<5)
#define RCC_TIM12_EN (1<<6)
#define RCC_TIM13_EN (1<<7)
#define RCC_TIM14_EN (1<<8)
#define RCC_WWDG_EN (1<<11)
#define RCC_SPI2_EN (1<<14)
#define RCC_SPI3_EN (1<<15)
#define RCC_SPDIFRX_EN (1<<16)
#define RCC_USART2_EN (1<<17)
#define RCC_USART3_EN (1<<18)
#define RCC_UART4_EN (1<<19)
#define RCC_UART5_EN (1<<20)
#define RCC_I2C1_EN (1<<21)
#define RCC_I2C2_EN (1<<22)
#define RCC_I2C3_EN (1<<23)
#define RCC_FMPI2C1_EN (1<<24)
#define RCC_CAN1_EN (1<<25)
#define RCC_CAN2_EN (1<<26)
#define RCC_CEC_EN (1<<27)
#define RCC_PWR_EN (1<<28)
#define RCC_DAC_EN (1<<29)

/* RCC APB2 peripheral clock enable register (APB2ENR) */
#define RCC_TIM1_EN (1<<0)
#define RCC_TIM8_EN (1<<1)
#define RCC_USART1_EN (1<<4)
#define RCC_USART6_EN (1<<5)
#define RCC_ADC1_EN (1<<8)
#define RCC_ADC2_EN (1<<9)
#define RCC_ADC3_EN (1<<10)
#define RCC_SDIO_EN (1<<11)
#define RCC_SPI1_EN (1<<12)
#define RCC_SPI4_EN (1<<13)
#define RCC_SYSCFG_EN (1<<14)
#define RCC_TIM9_EN (1<<16)
#define RCC_TIM10_EN (1<<17)
#define RCC_TIM11_EN (1<<18)
#define RCC_SAI1_EN (1<<22)
#define RCC_SAI2_EN (1<<23)

/* RCC AHB1 peripheral clock enable in low power mode register */
#define RCC_GPIOALP_EN (1<<0)
#define RCC_GPIOBLP_EN (1<<1)
#define RCC_GPIOCLP_EN (1<<2)
#define RCC_GPIODLP_EN (1<<3)
#define RCC_GPIOELP_EN (1<<4)
#define RCC_GPIOFLP_EN (1<<5)
#define RCC_GPIOGLP_EN (1<<6)
#define RCC_GPIOHLP_EN (1<<7)
#define RCC_CRCLP_EN (1<<12)
#define RCC_FLITFLP_EN (1<<15)
#define RCC_SRAM1LP_EN (1<<16)
#define RCC_SRAM2LP_EN (1<<17)
#define RCC_BKPSRAMLP_EN (1<<18)
#define RCC_DMA1LP_EN (1<<21)
#define RCC_DMA2LP_EN (1<<22)
#define RCC_OTGHSLP_EN (1<<29)
#define RCC_LTGHSULPILP_EN (1<<30)

/* RCC AHB2 periperal clock enable in low power mode register */
#define RCC_DCMILP_EN (1<<0)
#define RCC_OTGFSLP_EN (1<<7)

/* RCC AHB3 peirpheral clock enable in low power mode register */
#define RCC_FMC_LPEN (1<<0)
#define RCC_QSPI_LPEN (1<<1)

/* RCC APB! peripheral clock enable in low power mode register */
#define RCC_TIM2_LPEN (1<<0)
#define RCC_TIM3_LPEN (1<<1)
#define RCC_TIM4_LPEN (1<<2)
#define RCC_TIM5_LPEN (1<<3)
#define RCC_TIM6_LPEN (1<<4)
#define RCC_TIM7_LPEN (1<<5)
#define RCC_TIM12_LPEN (1<<6)
#define RCC_TIM13_LPEN (1<<7)
#define RCC_TIM14_LPEN (1<<8)
#define RCC_WWDG_LPEN (1<<11)
#define RCC_SPI2_LPEN (1<<14)
#define RCC_SPI3_LPEN (1<<15)
#define RCC_SPDIFRC_LPEN (1<<16)
#define RCC_USART2_LPEN (1<<17)
#define RCC_USART3_LPEN (1<<18)
#define RCC_UART4_LPEN (1<<19)
#define RCC_UART5_LPEN (1<<20)
#define RCC_I2C1_LPEN (1<<21)
#define RCC_I2C2_LPEN (1<<22)
#define RCC_I2C3_LPEN (1<<23)
#define RCC_FMPI2C1_LPEN (1<<24)
#define RCC_CAN1_LPEN (1<<25)
#define RCC_CAN2_LPEN (1<<26)
#define RCC_CEC_LPEN (1<<27)
#define RCC_PWR_LPEN (1<<28)
#define RCC_DAC_LPEN (1<<29)

/* RCC APB2 peripheral clock enabled in low power mode register */
#define RCC_TIM1_LPEN (1<<0)
#define RCC_TIM8_LPEN (1<<1)
#define RCC_USART1_LPEN (1<<4)
#define RCC_USART6_LPEN (1<<5)
#define RCC_ADC1_LPEN (1<<8)
#define RCC_ADC2_LPEN (1<<9)
#define RCC_ADC3_LPEN (1<<10)
#define RCC_SDIO_LPEN (1<<11)
#define RCC_SPI1_LPEN (1<<12)
#define RCC_SPI4_LPEN (1<<13)
#define RCC_SYSCFG_LPEN (1<<14)
#define RCC_TIM9_LPEN (1<<16)
#define RCC_TIM10_LPEN (1<<17)
#define RCC_TIM11_LPEN (1<<18)
#define RCC_SAI1_LPEN (1<<22)
#define RCC_SAI2_LPEN (1<<23)

/* RCC Backup domain control register */
#define RCC_LSEON (1<<0)
#define RCC_LSERDY (1<<1)
#define RCC_LSEBYP (1<<2)
#define RCC_LSEMOD (1<<3)
#define RCC_RTCSEL (3<<8)
#define RCC_RTC_EN (1<<15)
#define RCC_BD_RST (1<<16)

/* RCC clock control & status register (CSR) */
#define RCC_LSI_ON (1<<0)
#define RCC_LSI_RDY (1<<1)
#define RCC_RMVF (1<<24)
#define RCC_BOR_RSTF (1<<25)
#define RCC_PIN_RSTF (1<<26)
#define RCC_POR_RSTF (1<<27)
#define RCC_SFT_RSTF (1<<28)
#define RCC_IWDG_RSTF (1<<29)
#define RCC_WWDG_RSTF (1<<30)
#define RCC_LPWR_RSTF (1<<31)

/* RCC spread spectrum clock generation register (SSCGR) */
#define RCC_MODPER (0xFFF)
#define RCC_INCSTEP (0x7FFF<<13)
#define RCC_SPREADSEL (1<<30)
#define RCC_SSCG_EN (1<<31)

/* RCC PLLI2S configuration register (PLLI2SCFGR) */
#define RCC_PLLI2SM (0x1F<<0)
#define RCC_PLLI2SN (0x1FF<<6)
#define RCC_PLLI2SP (0x3<<16)
#define RCC_PLLI2SQ (0xF<<24)
#define RCC_PLLI2SR (0x7<<28)

/* RCC PLL configuration register (PLLSAICFGR) */
#define RCC_PLLSAIM (0x3F<<0)
#define RCC_PLLSAIN (0x1FF<<6)
#define RCC_PLLSAIP (0x3<<16)
#define RCC_PLLSAIQ (0xF<<24)

/* RCC dedicated clock configuration register (DCKCFGR) */
#define RCC_PLLIS2DIVQ (0x1F<<0)
#define RCC_PLLSAIDIVQ (0x1F<<8)
#define RCC_SAI1SRC (0x3<<20)
#define RCC_SAI2SRC (0x3<<22)
#define RCC_TIMPRE (1<<24)
#define RCC_I2S1SRC (0x3<<25)
#define RCC_I2SSRC (0x3<<27)

/* RCC clocks gated enable register (CKGATENR) */
#define RCC_AHB2APB1_CKEN (1<<0)
#define RCC_AHB2APB2_CKEN (1<<0)
#define RCC_CM4DBG_CKEN (1<<2)
#define RCC_SPARE_CKEN (1<<3)
#define RCC_SRAM_CKEN (1<<4)
#define RCC_FLITF_CKEN (1<<5)
#define RCC_CKEN (1<<6)

/* RCC dedicated clocks configuration register 2 (DCKCFGR2) */
#define RCC_FMPI2C1SEL (0x3<<22)
#define RCC_CECSEL (1<<26)
#define RCC_CK48MSEL (1<<27)
#define RCC_SDIOSEL (1<<28)
#define RCC_SPDIFRXSEL (1<<29)

struct RCC_regs {
  volatile uint32_t cr;
  volatile uint32_t pllcfgr;
  volatile uint32_t cfgr;
  volatile uint32_t cir;
  volatile uint32_t ahb1rstr;
  volatile uint32_t ahb2rstr;
  volatile uint32_t ahb3rstr;
  uint32_t reserved0;
  volatile uint32_t apb1rstr;
  volatile uint32_t apb2rstr;
  uint32_t reserved1;
  uint32_t reserved2;
  volatile uint32_t ahb1enr;
  volatile uint32_t ahb2enr;
  volatile uint32_t ahb3enr;
  uint32_t reserved3;
  volatile uint32_t apb1enr;
  volatile uint32_t apb2enr;
  uint32_t reserved4;
  uint32_t reserved5;
  volatile uint32_t ahb1lpenr;
  volatile uint32_t ahb2lpenr;
  volatile uint32_t ahb3lpenr;
  uint32_t reserved6;
  volatile uint32_t apb1lpenr;
  volatile uint32_t apb2lpenr;
  uint32_t reserved7;
  uint32_t reserved8;
  volatile uint32_t bdcr;
  volatile uint32_t csr;
  uint32_t reserved9;
  uint32_t reserved10;
  volatile uint32_t sscgr;
  volatile uint32_t plli2scfgr;
  volatile uint32_t pllsaicfgr;
  volatile uint32_t dckcfgr;
  volatile uint32_t ckgatenr;
  volatile uint32_t dckcfgr2;
};

#ifdef __cplusplus
}
#endif
#endif