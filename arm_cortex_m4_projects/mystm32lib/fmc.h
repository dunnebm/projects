#ifndef FMC_H
#define FMC_H

#include <stdint.h>

#define FMC_CRAM_PAGE_SIZE_128_BYTES 1u
#define FMC_CRAM_PAGE_SIZE_256_BYTES 2u
#define FMC_CRAM_PAGE_SIZE_512_BYTES 3u
#define FMC_CRAM_PAGE_SIZE_1024_BYTES 4u

#define FMC_ASYNCWAIT_DISABLE 0u
#define FMC_ASYNCWAIT_ENABLE 1u

#define FMC_EXTENDED_MODE_DISABLED 0u
#define FMC_EXTENDED_MODE_ENABLED 1u

#define FMC_WAIT_SIGNAL_DISABLED 0u
#define FMC_WAIT_SIGNAL_ENABLED 1u

#define FMC_WAIT_SIGNAL_POLARITY_ACTIVE_LOW 0u
#define FMC_WAIT_SIGNAL_POLARITY_ACTIVE_HIGH 1u

#define FMC_BURST_MODE_DISABLED 0u
#define FMC_BURST_MODE_ENABLED 1u

#define FMC_FLASH_ACCESS_DISABLED 0u
#define FMC_FLASH_ACCESS_ENABLED 1u

#define FMC_MEMORY_DATA_BUS_WIDTH_8_BITS 0u
#define FMC_MEMORY_DATA_BUS_WIDTH_16_BITS 1u

#define FMC_MEMORY_TYPE_SRAM 0u
#define FMC_MEMORY_TYPE_PSRAM 1u
#define FMC_MEMORY_TYPE_NOR_FLASH 3u

#define FMC_MULTIPLEXED_DISABLED 0u
#define FMC_MULTIPLEXED_ENABLED 1u

#define FMC_COMUMN_ADDRESS_SIZE_8_BITS 0u
#define FMC_COLUMN_ADDRESS_SIZE_9_BITS 1u
#define FMC_COLUMN_ADDRESS_SIZE_10_BITS 2u
#define FMC_COLUMN_ADDRESS_SIZE_11_BITS 3u

#define FMC_ROW_ADDRESS_SIZE_11_BITS 0u
#define FMC_ROW_ADDRESS_SIZE_12_BITS 1u
#define FMC_ROW_ADDRESS_SIZE_13_BITS 2u

#define FMC_NUMBER_OF_INTERNAL_BANKS_TWO 0u
#define FMC_NUMBER_OF_INTERNAL_BANKS_FOUR 1u

#define FMC_CAS_LATENCY_1_CYCLE 1u
#define FMC_CAS_LATENCY_2_CYCLES 2u
#define FMC_CAS_LATENCY_3_CYCLES 3u

#define FMC_WRITE_PROTECTION_ACCESS_ALLOWED 0u
#define FMC_WRITE_PROTECTION_ACCESS_IGNORED 1u

#define FMC_SDCLK_DISABLED 0u
#define FMC_SDCLK_2_TIMES_HCLK 2u
#define FMC_SDCLK_3_TIMES_HCLK 3u

#define FMC_SDRAM_TIMING_DELAY_1_CYCLE 0u
#define FMC_SDRAM_TIMING_DELAY_2_CYCLES 1u
#define FMC_SDRAM_TINING_DELAY_3_CYCLES 2u
#define FMC_SDRAM_TIMING_DELAY_4_CYCLES 3u
#define FMC_SDRAM_TIMING_DELAY_5_CYCLES 4u
#define FMC_SDRAM_TIMING_DELAY_6_CYCLES 5u
#define FMC_SDRAM_TIMING_DELAY_7_CYCLES 6u
#define FMC_SDRAM_TIMING_DELAY_8_CYCLES 7u
#define FMC_SDRAM_TIMING_DELAY_9_CYCLES 8u
#define FMC_SDRAM_TIMING_DELAY_10_CYCLES 9u
#define FMC_SDRAM_TIMING_DELAY_11_CYCLES 10u
#define FMC_SDRAM_TIMING_DELAY_12_CYCLES 11u
#define FMC_SDRAM_TIMING_DELAY_13_CYCLES 12u
#define FMC_SDRAM_TIMING_DELAY_14_CYCLES 13u
#define FMC_SDRAM_TIMING_DELAY_15_CYCLES 14u
#define FMC_SDRAM_TIMING_DELAY_16_CYCLES 15u

#define FMC_SDRAM_CMD_MODE_NORMAL 0u
#define FMC_SDRAM_CMD_MODE_CLK_CONFIG_ENABLE 1u
#define FMC_SDRAM_CMD_MODE_PRECHARGE_ALL 2u
#define FMC_SDRAM_CMD_MODE_AUTO_REFRESH 3u
#define FMC_SDRAM_CMD_MODE_LOAD 4u
#define FMC_SDRAM_CMD_MODE_SELF_REFRESH 5u
#define FMC_SDRAM_CMD_MODE_POWER_DOWN 6u

#define FMC_ACCESS_MODE_A 0u
#define FMC_ACCESS_MODE_B 1u
#define FMC_ACCESS_MODE_C 2u
#define FMC_ACCESS_MODE_D 3u

#define FMC_DATA_LATENCY_2_CYCLES 0u
#define FMC_DATA_LATENCY_3_CYCLES 1u
#define FMC_DATA_LATENCY_4_CYCLES 2u
#define FMC_DATA_LATENCY_5_CYCLES 3u
#define FMC_DATA_LATENCY_6_CYCLES 4u
#define FMC_DATA_LATENCY_7_CYCLES 5u
#define FMC_DATA_LATENCY_8_CYCLES 6u
#define FMC_DATA_LATENCY_9_CYCLES 7u
#define FMC_DATA_LATENCY_10_CYCLES 8u
#define FMC_DATA_LATENCY_11_CYCLES 9u
#define FMC_DATA_LATENCY_12_CYCLES 10u
#define FMC_DATA_LATENCY_13_CYCLES 11u
#define FMC_DATA_LATENCY_14_CYCLES 12u
#define FMC_DATA_LATENCY_15_CYCLES 13u
#define FMC_DATA_LATENCY_16_CYCLES 14u
#define FMC_DATA_LATENCY_17_CYCLES 15u

#define FMC_DURATION_2_TIMES_HCLK 1u
#define FMC_DURATION_3_TIMES_HCLK 2u
#define FMC_DURATION_4_TIMES_HCLK 3u
#define FMC_DURATION_5_TIMES_HCLK 4u
#define FMC_DURATION_6_TIMES_HCLK 5u
#define FMC_DURATION_7_TIMES_HCLK 6u
#define FMC_DURATION_8_TIMES_HCLK 7u
#define FMC_DURATION_9_TIMES_HCLK 8u
#define FMC_DURATION_10_TIMES_HCLK 9u
#define FMC_DURATION_11_TIMES_HCLK 10u
#define FMC_DURATION_12_TIMES_HCLK 11u
#define FMC_DURATION_13_TIMES_HCLK 12u
#define FMC_DURATION_14_TIMES_HCLK 13u
#define FMC_DURATION_15_TIMES_HCLK 14u
#define FMC_DURATION_16_TIMES_HCLK 15u

#define FMC_WRITE_FIFO_ENABLED 0u
#define FMC_WRITE_FIFO_DISABLED 1u

typedef struct {
  uint32_t addressSetupPhaseDuration;
  uint32_t addressHoldPhaseDuration;
  uint32_t dataPhaseDuration;
  uint32_t busTurnaroundPhaseDuration;
  uint32_t clockDivideRatio;
  uint32_t dataLatency;
  uint32_t accessMode;
} FMC_NFP_ReadTimeConstraints;

typedef struct {
  uint32_t addressSetupPhaseDuration;
  uint32_t addressHoldPhaseDuration;
  uint32_t dataPhaseDuration;
  uint32_t busTurnaroundPhaseDuration;
  uint32_t accessMode;
} FMC_NFP_WriteTimeConstraints;

// NOR/PSRAM Bank1
// subbank1 0x6000_0000 - 0x600f_ffff
// subbank2 0x6010_0000 - 0x601f_ffff
// subbank3 0x6020_0000 - 0x602f_ffff
// subbank4 0x6030_0000 - 0x603f_ffff

// NAND Flash Bank3
// subbank1 0x8000_0000 - 0x800f_ffff
// subbank2 0x8010_0000 - 0x801f_ffff
// subbank3 0x8020_0000 - 0x802f_ffff
// subbank4 0x8030_0000 - 0x803f_ffff

// SDRAM Bank1
// subbank1 0xC000_0000 - 0xC00f_ffff
// subbank2 0xC010_0000 - 0xC01f_ffff
// subbank3 0xC020_0000 - 0xC02f_ffff
// subbank4 0xC030_0000 - 0xC03f_ffff

// SDRAM Bank2
// subbank1 0xD000_0000 - 0xD00f_ffff
// subbank2 0xD010_0000 - 0xD01f_ffff
// subbank3 0xD020_0000 - 0xD02f_ffff
// subbank4 0xD030_0000 - 0xD03f_ffff

typedef struct {
  uint32_t memType;
  uint32_t memDataBusWidth;
  uint32_t muxEnable;
  uint32_t flashAccessEnable;
  uint32_t burstEnable;
  uint32_t waitSignalPolarity;
  uint32_t waitConfig;
  uint32_t waitEnable;
  uint32_t asyncWaitEnable;
  uint32_t writeEnable;
  uint32_t extendedMode;
  uint32_t CRAMPageSize;
  uint32_t writeBurstEnable;
  uint32_t continuousClockEnable;
  uint32_t writeFIFOEnable;
  FMC_NFP_ReadTimeConstraints readTiming;
  FMC_NFP_WriteTimeConstraints writeTiming;
} FMC_NFP_Bank_Configuration;

typedef struct {
  uint32_t waitFeatureEnable;
  uint32_t dataBusWidth;
  uint32_t eccComputationLogicEnable;
  uint32_t cleToReDelay;
  uint32_t aleToReDelay;
  uint32_t eccPageSize;
} FMC_NAND_FLASH_Configuration;

typedef struct {
  uint32_t loadToActiveDelay;
  uint32_t exitSelfRefreshDelay;
  uint32_t selfRefreshDelay;
  uint32_t rowCycleDelay;
  uint32_t recoveryDelay;
  uint32_t rowPrechargeDelay;
  uint32_t rowToColumnDelay;
} FMC_SDRAM_Configuration;

void FMC_enableClock();
void FMC_disableClock();
void FMC_enableNFPBank(uint32_t bank);
void FMC_disableNFPBank(uint32_t bank);
void FMC_configureNFPBank(uint32_t bank, const FMC_NFP_Bank_Configuration* pConfig);
void FMC_getConfigNFPBank(uint32_t bank, FMC_NFP_Bank_Configuration* pConfig);
void FMC_enableNANDFlash();
void FMC_disableNANDFlash();
void FMC_configureNANDFlash(const FMC_NAND_FLASH_Configuration* pConfig);
void FMC_getConfigNANDFlash(FMC_NAND_FLASH_Configuration* pConfig);
void FMC_enableSDRAM();
void FMC_disableSDRAM();
void FMC_configureSDRAM(const FMC_SDRAM_Configuration* pConfig);
void FMC_getConfigSDRAM(FMC_SDRAM_Configuration* pConfig);

#endif