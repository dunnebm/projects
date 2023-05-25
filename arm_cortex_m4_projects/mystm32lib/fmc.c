#include "fmc.h"
#include "rcc.h"

#define FMC_BCR_MBKEN (1<<0)
#define FMC_BCR_MUXEN_BIT (1<<1)
#define FMC_BCR_MUXEN_OFFSET 1
#define FMC_BCR_MTYP_MASK (3<<2)
#define FMC_BCR_MTYP_OFFSET 2
#define FMC_BCR_MWID_MASK (3<<4)
#define FMC_BCR_MWID_OFFSET 4
#define FMC_BCR_FACCEN_BIT (1<<6)
#define FMC_BCR_FACCEN_OFFSET 6
#define FMC_BCR_BURSTEN_BIT (1<<8)
#define FMC_BCR_BURSTEN_OFFSET 8
#define FMC_BCR_WAITPOL_BIT (1<<9)
#define FMC_BCR_WAITPOL_OFFSET 9
#define FMC_BCR_WAITCFG_BIT (1<<11)
#define FMC_BCR_WAITCFG_OFFSET 11
#define FMC_BCR_WREN_BIT (1<<12)
#define FMC_BCR_WREN_OFFSET 12
#define FMC_BCR_WAITEN_BIT (1<<13)
#define FMC_BCR_WAITEN_OFFSET 13
#define FMC_BCR_EXTMOD_BIT (1<<14)
#define FMC_BCR_EXTMOD_OFFSET 14
#define FMC_BCR_ASYNCWAIT_BIT (1<<15)
#define FMC_BCR_ASYNCWAIT_OFFSET 15
#define FMC_BCR_CPSIZE_MASK (7<<16)
#define FMC_BCR_CPSIZE_OFFSET 16
#define FMC_BCR_CBURSTRW_BIT (1<<19)
#define FMC_BCR_CBURSTRW_OFFSET 19
#define FMC_BCR_CCLKEN_BIT (1<<20)
#define FMC_BCR_CCLKEN_OFFSET 20
#define FMC_BCR_WFDIS_BIT (1<<21)
#define FMC_BCR_WFDIS_OFFSET 21

#define FMC_BTR_ADDSET_MASK (0xf<<0)
#define FMC_BTR_ADDSET_OFFSET 0
#define FMC_BTR_ADDHLD_MASK (0xf<<4)
#define FMC_BTR_ADDHLD_OFFSET 4
#define FMC_BTR_DATAST_MASK (0xff<<8)
#define FMC_BTR_DATAST_OFFSET 8
#define FMC_BTR_BUSTURN_MASK (0xf<<16)
#define FMC_BTR_BUSTURN_OFFSET 16
#define FMC_BTR_CLKDIV_MASK (0xf<<20)
#define FMC_BTR_CLKDIV_OFFSET 20
#define FMC_BTR_DATLAT_MASK (0xf<<24)
#define FMC_BTR_DATLAT_OFFSET 24
#define FMC_BTR_ACCMOD_MASK (3<<28)
#define FMC_BTR_ACCMOD_OFFSET 28

#define FMC_BWTR_ADDSET_MASK (0xf<<0)
#define FMC_BWTR_ADDSET_OFFSET 0
#define FMC_BWTR_ADDHLD_MASK (0xf<<4)
#define FMC_BWTR_ADDHLD_OFFSET 4
#define FMC_BWTR_DATAST_MASK (0xff<<8)
#define FMC_BWTR_DATAST_OFFSET 8
#define FMC_BWTR_BUSTURN_MASK (0xf<<16)
#define FMC_BWTR_BUSTURN_OFFSET 16
#define FMC_BWTR_ACCMOD_MASK (3<<28)
#define FMC_BWTR_ACCMOD_OFFSET 28

#define FMC_PCR_PWAITEN_BIT (1<<1)
#define FMC_PCR_PBKEN_BIT (1<<2)
#define FMC_PCR_PTYP_BIT (1<<3)
#define FMC_PCR_PWID_MASK (3<<4)
#define FMC_PCR_PWID_OFFSET 4
#define FMC_PCR_ECCEN_BIT (1<<6)
#define FMC_PCR_TCLR_MASK (0xf<<9)
#define FMC_PCR_TCLR_OFFSET 9
#define FMC_PCR_TAR_MASK (0xf<<13)
#define FMC_PCR_TAR_OFFSET 13
#define FMC_PCR_ECCPS_MASK (7<<17)
#define FMC_PCR_ECCPS_OFFSET 17

#define FMC_SR_IRS_BIT (1<<0)
#define FMC_SR_ILS_BIT (1<<1)
#define FMC_SR_IFS_BIT (1<<2)
#define FMC_SR_IREN_BIT (1<<3)
#define FMC_SR_ILEN_BIT (1<<4)
#define FMC_SR_IFEN_BIT (1<<5)
#define FMC_SR_FEMPT_BIT (1<<6)

#define FMC_PMEM_MEMHOLDX_MASK (0xff<<0)
#define FMC_PMEM_MEMHOLDX_OFFSET 0
#define FMC_PMEM_MEMWAITX_MASK (0xff<<8)
#define FMC_PMEM_MEMWAITX_OFFSET 8
#define FMC_PMEM_MEMHOLDX_MASK (0xff<<16)
#define FMC_PMEM_MEMHOLDX_OFFSET 16
#define FMC_PMEM_MEMHIZX_MASK (0xff<<24)
#define FMC_PMEM_MEMHIZX_OFFSET 24

#define FMC_PATT_ATTSET_MASK (0xff<<0)
#define FMC_PATT_ATTSET_OFFSET 0
#define FMC_PATT_ATTWAIT_MASK (0xff<<8)
#define FMC_PATT_ATTWAIT_OFFSET 8
#define FMC_PATT_ATTHOLD_MASK (0xff<<16)
#define FMC_PATT_ATTHOLD_OFFSET 16
#define FMC_PATT_ATTHIZ_MASK (0xff<<24)
#define FMC_PATT_ATTHIZ_OFFSET 24

#define FMC_SDCR_NC_MASK (3<<0)
#define FMC_SDCR_NC_OFFSET 0
#define FMC_SDCR_NR_MASK (3<<2)
#define FMC_SDCR_NR_OFFSET 2
#define FMC_SDCR_MWID_MASK (3<<4)
#define FMC_SDCR_MWID_OFFSET 4
#define FMC_SDCR_NB_BIT (1<<6)
#define FMC_SDCR_NB_OFFSET 6
#define FMC_SDCR_CAS_MASK (3<<7)
#define FMC_SDCR_CAS_OFFSET 7
#define FMC_SDCR_WP_BIT (1<<9)
#define FMC_SDCR_WP_OFFSET 9
#define FMC_SDCR_SDCLK_BIT (3<<10)
#define FMC_SDCR_SDCLK_OFFSET 10
#define FMC_SDCR_RBURST_BIT (1<<12)
#define FMC_SDCR_RPIPE_MASK (3<<13)
#define FMC_SDCR_RPIPE_OFFSET 13

#define FMC_SDTR_TMRD_MASK (0xf<<0)
#define FMC_SDTR_TMRD_OFFSET 0
#define FMC_SDTR_TXSR_MASK (0xf<<4)
#define FMC_SDTR_TXSR_OFFSET 4
#define FMC_SDTR_TRAS_MASK (0xf<<8)
#define FMC_SDTR_TRAS_OFFSET 8
#define FMC_SDTR_TRC_MASK (0xf<<12)
#define FMC_SDTR_TRC_OFFSET 12
#define FMC_SDTR_TWR_MASK (0xf<<16)
#define FMC_SDTR_TWR_OFFSET 16
#define FMC_SDTR_TRP_MASK (0xf<<20)
#define FMC_SDTR_TRP_OFFSET 20
#define FMC_SDTR_TRCD_MASK (0xf<<24)
#define FMC_SDTR_TRCD_OFFSET 24

#define FMC_SDCMR_MODE_MASK (7<<0)
#define FMC_SDCMR_MODE_OFFSET 0
#define FMC_SDCMR_CTB2_BIT (1<<3)
#define FMC_SDCMR_CTR2_OFFSET 3
#define FMC_SDCMR_CTR1_BIT (1<<4)
#define FMC_SDCMR_CTR1_OFFSET 4
#define FMC_SDCMR_NRFS_MASK (0xf<<5)
#define FMC_SDCMR_NRFS_OFFSET 5
#define FMC_SDCMR_MRD_MASK (0x1fff<9)
#define FMC_SDCMR_MRD_OFFSET 9

#define FMC_SDRTR_CRE_BIT (1<<0)
#define FMC_SDTRT_CRE_OFFSET 0
#define FMC_SDRTR_COUNT_MASK (0x1ff<<1)
#define FMC_SDRTR_COUNT_OFFSET 1
#define FMC_SDRTR_REIE_BIT (1<<14)
#define FMC_SDRTR_REIE_OFFSET 14

#define FMC_SDSR_MODES1_MASK (3<<1)
#define FMC_SDSR_MODES1_OFFSET 1
#define FMC_SDSR_MODES2_MASK (3<<3)
#define FMC_SDSR_MODES2_OFFSET 3
#define FMC_SDSR_BUSY_BIT (1<<5)
#define FMC_SDSR_BUSY_OFFSET 5

#define FMC_BASE 0xA0000000
#define FMC_NFP_BASE FMC_BASE
#define FMC_NFP_WRITE_TIMING_BASE (FMC_BASE + 0x104)
#define FMC_NAND_FLASH_BASE (FMC_BASE + 0x80)
#define FMC_SDRAM_BASE (FMC_BASE + 0x140)

struct FMC_NFP_regs {
  uint32_t bcr1;
  uint32_t btr1;
  uint32_t bcr2;
  uint32_t btr2;
  uint32_t bcr3;
  uint32_t btr3;
  uint32_t bcr4;
  uint32_t btr4;
};

struct FMC_NFP_write_timing_regs {
  uint32_t bwtr1;
  uint32_t reserved1;
  uint32_t bwtr2;
  uint32_t reserved2;
  uint32_t bwtr3;
  uint32_t reserved3;
  uint32_t bwtr4;
};

struct FMC_NAND_Flash_regs {
  uint32_t pcr;
  uint32_t sr;
  uint32_t pmem;
  uint32_t patt;
  uint32_t reserved;
  uint32_t eccr;
};

struct FMC_SDRAM_regs {
  uint32_t sdcr1;
  uint32_t sdcr2;
  uint32_t sdtr1;
  uint32_t sdtr2;
  uint32_t sdcmr;
  uint32_t sdrtr;
  uint32_t sdsr;
};

void FMC_enableClock()
{
  struct RCC_regs* regs = (struct RCC_regs*) RCC_BASE;
  regs->ahb3enr |= RCC_FMC_EN;
}

void FMC_disableClock()
{
  struct RCC_regs* regs = (struct RCC_regs*) RCC_BASE;
  regs->ahb3enr &= ~RCC_FMC_EN;
}

void FMC_enableNFPBank(uint32_t bank)
{
  struct FMC_NFP_regs* regs = (void*) FMC_NFP_BASE;
  switch (bank)
  {
    case 1:
      regs->bcr1 |= FMC_BCR_MBKEN;
      break;
    case 2:
      regs->bcr2 |= FMC_BCR_MBKEN;
      break;
    case 3:
      regs->bcr3 |= FMC_BCR_MBKEN;
      break;
    case 4:
      regs->bcr4 |= FMC_BCR_MBKEN;
  }
}

void FMC_disableNFPBank(uint32_t bank)
{
  struct FMC_NFP_regs* regs = (void*) FMC_NFP_BASE;
  switch (bank)
  {
    case 1:
      regs->bcr1 &= ~FMC_BCR_MBKEN;
      break;
    case 2:
      regs->bcr2 &= ~FMC_BCR_MBKEN;
      break;
    case 3:
      regs->bcr3 &= ~FMC_BCR_MBKEN;
      break;
    case 4:
      regs->bcr4 &= ~FMC_BCR_MBKEN;
  }
}

void FMC_configureNFPBank(uint32_t bank, const FMC_NFP_Bank_Configuration* pConfig)
{
  struct FMC_NFP_regs* ctrl_regs = (void*) FMC_NFP_BASE;
  struct FMC_NFP_write_timing_regs* write_timing_regs = (void*) FMC_NFP_WRITE_TIMING_BASE;
  uint32_t bcr_val;
  uint32_t btr_val;
  uint32_t bwtr_val;

  /* Read values from regs */
  switch (bank)
  {
    case 1:
      bcr_val = ctrl_regs->bcr1;
      btr_val = ctrl_regs->btr1;
      bwtr_val = write_timing_regs->bwtr1;
      break;
    case 2:
      bcr_val = ctrl_regs->bcr2;
      btr_val = ctrl_regs->btr2;
      bwtr_val = write_timing_regs->bwtr2;
      break;
    case 3:
      bcr_val = ctrl_regs->bcr3;
      btr_val = ctrl_regs->btr3;
      bwtr_val = write_timing_regs->bwtr3;
      break;
    case 4:
      bcr_val = ctrl_regs->bcr4;
      btr_val = ctrl_regs->btr4;
      bwtr_val = write_timing_regs->bwtr4;
  }

  /* Modify values */

  bcr_val &= ~FMC_BCR_MTYP_MASK;
  bcr_val |= (pConfig->memType << FMC_BCR_MTYP_OFFSET) & FMC_BCR_MTYP_MASK;

  bcr_val &= ~FMC_BCR_MWID_MASK;
  bcr_val |= (pConfig->memDataBusWidth << FMC_BCR_MWID_OFFSET) & FMC_BCR_MWID_MASK;

  bcr_val &= ~FMC_BCR_MUXEN_BIT;
  bcr_val |= (pConfig->muxEnable << FMC_BCR_MUXEN_OFFSET) & FMC_BCR_MUXEN_BIT;

  bcr_val &= ~FMC_BCR_FACCEN_BIT;
  bcr_val |= (pConfig->flashAccessEnable << FMC_BCR_FACCEN_OFFSET);

  bcr_val &= ~FMC_BCR_BURSTEN_BIT;
  bcr_val |= (pConfig->burstEnable << FMC_BCR_BURSTEN_OFFSET) & FMC_BCR_BURSTEN_BIT;

  bcr_val &= ~FMC_BCR_WAITPOL_BIT;
  bcr_val |= (pConfig->waitSignalPolarity << FMC_BCR_WAITPOL_OFFSET) & FMC_BCR_WAITPOL_BIT;

  bcr_val &= ~FMC_BCR_WAITCFG_BIT;
  bcr_val |= (pConfig->waitConfig << FMC_BCR_WAITCFG_OFFSET) & FMC_BCR_WAITCFG_BIT;

  bcr_val &= ~FMC_BCR_WAITEN_BIT;
  bcr_val |= (pConfig->waitEnable << FMC_BCR_WAITEN_OFFSET) & FMC_BCR_WAITEN_BIT;

  bcr_val &= ~FMC_BCR_EXTMOD_BIT;
  bcr_val |= (pConfig->extendedMode << FMC_BCR_EXTMOD_OFFSET) & FMC_BCR_EXTMOD_BIT;

  bcr_val &= ~FMC_BCR_ASYNCWAIT_BIT;
  bcr_val |= (pConfig->asyncWaitEnable << FMC_BCR_ASYNCWAIT_OFFSET) & FMC_BCR_ASYNCWAIT_BIT;

  bcr_val &= ~FMC_BCR_WREN_BIT;
  bcr_val |= (pConfig->writeEnable << FMC_BCR_WREN_OFFSET) & FMC_BCR_WREN_BIT;

  bcr_val &= ~FMC_BCR_CPSIZE_MASK;
  bcr_val |= (pConfig->CRAMPageSize << FMC_BCR_CPSIZE_OFFSET) & FMC_BCR_CPSIZE_MASK;

  bcr_val &= ~FMC_BCR_CBURSTRW_BIT;
  bcr_val |= (pConfig->writeBurstEnable << FMC_BCR_CBURSTRW_OFFSET) & FMC_BCR_CBURSTRW_BIT;

  bcr_val &= ~FMC_BCR_CCLKEN_BIT;
  bcr_val |= (pConfig->continuousClockEnable << FMC_BCR_CCLKEN_OFFSET) & FMC_BCR_CCLKEN_BIT;

  bcr_val &= ~FMC_BCR_WFDIS_BIT;
  bcr_val |= (pConfig->writeFIFOEnable << FMC_BCR_WFDIS_OFFSET) & FMC_BCR_WFDIS_BIT;

  btr_val &= ~FMC_BTR_ACCMOD_MASK;
  btr_val |= (pConfig->readTiming.accessMode << FMC_BTR_ACCMOD_OFFSET) & FMC_BTR_ACCMOD_MASK;

  btr_val &= ~FMC_BTR_ADDSET_MASK;
  btr_val |= (pConfig->readTiming.addressSetupPhaseDuration << FMC_BTR_ADDSET_OFFSET) & FMC_BTR_ADDSET_MASK;

  btr_val &= ~FMC_BTR_ADDHLD_MASK;
  btr_val |= (pConfig->readTiming.addressHoldPhaseDuration << FMC_BTR_ADDHLD_OFFSET) & FMC_BTR_ADDHLD_MASK;

  btr_val &= ~FMC_BTR_DATAST_MASK;
  btr_val |= (pConfig->readTiming.dataPhaseDuration << FMC_BTR_DATAST_OFFSET) & FMC_BTR_DATAST_MASK;

  btr_val &= ~FMC_BTR_BUSTURN_MASK;
  btr_val |= (pConfig->readTiming.busTurnaroundPhaseDuration << FMC_BTR_BUSTURN_OFFSET) & FMC_BTR_BUSTURN_MASK;

  btr_val &= ~FMC_BTR_CLKDIV_MASK;
  btr_val |= (pConfig->readTiming.clockDivideRatio << FMC_BTR_CLKDIV_OFFSET) & FMC_BTR_CLKDIV_MASK;

  btr_val &= ~FMC_BTR_DATLAT_MASK;
  btr_val |= (pConfig->readTiming.dataLatency << FMC_BTR_DATLAT_OFFSET) & FMC_BTR_DATLAT_MASK;

  bwtr_val &= ~FMC_BWTR_ADDSET_MASK;
  bwtr_val |= (pConfig->writeTiming.addressSetupPhaseDuration << FMC_BWTR_ADDSET_OFFSET) & FMC_BWTR_ADDSET_MASK;

  bwtr_val &= ~FMC_BWTR_ADDHLD_MASK;
  bwtr_val |= (pConfig->writeTiming.addressHoldPhaseDuration << FMC_BWTR_ADDHLD_OFFSET) & FMC_BWTR_ADDHLD_MASK;

  bwtr_val &= ~FMC_BWTR_DATAST_MASK;
  bwtr_val |= (pConfig->writeTiming.dataPhaseDuration << FMC_BWTR_DATAST_OFFSET) & FMC_BWTR_DATAST_MASK;

  bwtr_val &= ~FMC_BWTR_BUSTURN_MASK;
  bwtr_val |= (pConfig->writeTiming.busTurnaroundPhaseDuration << FMC_BWTR_BUSTURN_OFFSET) & FMC_BWTR_BUSTURN_MASK;

  bwtr_val &= ~FMC_BWTR_ACCMOD_MASK;
  bwtr_val |= (pConfig->writeTiming.accessMode << FMC_BWTR_ACCMOD_OFFSET) & FMC_BWTR_ACCMOD_MASK;

  /* Write value to regs */
  switch (bank)
  {
    case 1:
      ctrl_regs->bcr1 = bcr_val;
      ctrl_regs->btr1 = btr_val;
      write_timing_regs->bwtr1 = bwtr_val;
      break;
    case 2:
      ctrl_regs->bcr2 = bcr_val;
      ctrl_regs->btr2 = btr_val;
      write_timing_regs->bwtr2 = bwtr_val;
      break;
    case 3:
      ctrl_regs->bcr3 = bcr_val;
      ctrl_regs->btr3 = btr_val;
      write_timing_regs->bwtr3 = bwtr_val;
      break;
    case 4:
      ctrl_regs->bcr4 = bcr_val;
      ctrl_regs->btr4 = btr_val;
      write_timing_regs->bwtr4 = bwtr_val;
  }
}

void FMC_getConfigNFPBank(uint32_t bank, FMC_NFP_Bank_Configuration* pConfig)
{
  struct FMC_NFP_regs* ctrl_regs = (void*) FMC_NFP_BASE;
  struct FMC_NFP_write_timing_regs* write_timing_regs = (void*) FMC_NFP_WRITE_TIMING_BASE;
  uint32_t bcr_val;
  uint32_t btr_val;
  uint32_t bwtr_val;

  switch (bank)
  {
    case 1:
      bcr_val = ctrl_regs->bcr1;
      btr_val = ctrl_regs->btr1;
      bwtr_val = write_timing_regs->bwtr1;
      break;
    case 2:
      bcr_val = ctrl_regs->bcr2;
      btr_val = ctrl_regs->btr2;
      bwtr_val = write_timing_regs->bwtr2;
      break;
    case 3:
      bcr_val = ctrl_regs->bcr3;
      btr_val = ctrl_regs->btr3;
      bwtr_val = write_timing_regs->bwtr3;
      break;
    case 4:
      bcr_val = ctrl_regs->bcr4;
      btr_val = ctrl_regs->btr4;
      bwtr_val = write_timing_regs->bwtr4;
  }

  pConfig->memType = (bcr_val & FMC_BCR_MTYP_MASK) >> FMC_BCR_MTYP_OFFSET;
  pConfig->memDataBusWidth = (bcr_val & FMC_BCR_MWID_MASK) >> FMC_BCR_MWID_OFFSET;
  pConfig->muxEnable = (bcr_val & FMC_BCR_MUXEN_BIT) >> FMC_BCR_MUXEN_OFFSET;
  pConfig->flashAccessEnable = (bcr_val & FMC_BCR_FACCEN_BIT) >> FMC_BCR_FACCEN_OFFSET;
  pConfig->burstEnable = (bcr_val & FMC_BCR_BURSTEN_BIT) >> FMC_BCR_BURSTEN_OFFSET;
  pConfig->waitSignalPolarity = (bcr_val & FMC_BCR_WAITPOL_BIT) >> FMC_BCR_WAITPOL_OFFSET;
  pConfig->waitConfig = (bcr_val & FMC_BCR_WAITCFG_BIT) >> FMC_BCR_WAITCFG_OFFSET;
  pConfig->waitEnable = (bcr_val & FMC_BCR_WAITEN_BIT) >> FMC_BCR_WAITEN_OFFSET;
  pConfig->asyncWaitEnable = (bcr_val & FMC_BCR_ASYNCWAIT_BIT) >> FMC_BCR_ASYNCWAIT_OFFSET;
  pConfig->writeEnable = (bcr_val & FMC_BCR_WREN_BIT) >> FMC_BCR_WREN_OFFSET;
  pConfig->extendedMode = (bcr_val & FMC_BCR_EXTMOD_BIT) >> FMC_BCR_EXTMOD_OFFSET;
  pConfig->CRAMPageSize = (bcr_val & FMC_BCR_CPSIZE_MASK) >> FMC_BCR_CPSIZE_OFFSET;
  pConfig->writeBurstEnable = (bcr_val & FMC_BCR_CBURSTRW_BIT) >> FMC_BCR_CBURSTRW_OFFSET;
  pConfig->continuousClockEnable = (bcr_val & FMC_BCR_CCLKEN_BIT) >> FMC_BCR_CCLKEN_OFFSET;
  pConfig->writeFIFOEnable = (bcr_val & FMC_BCR_WFDIS_BIT) >> FMC_BCR_WFDIS_OFFSET;

  pConfig->readTiming.addressSetupPhaseDuration = (btr_val & FMC_BTR_ADDSET_MASK) >> FMC_BTR_ADDSET_OFFSET;
  pConfig->readTiming.addressHoldPhaseDuration = (btr_val & FMC_BTR_ADDHLD_MASK) >> FMC_BTR_ADDHLD_OFFSET;
  pConfig->readTiming.dataPhaseDuration = (btr_val & FMC_BTR_DATAST_MASK) >> FMC_BTR_DATAST_OFFSET;
  pConfig->readTiming.busTurnaroundPhaseDuration = (btr_val & FMC_BTR_BUSTURN_MASK) >> FMC_BTR_BUSTURN_OFFSET;
  pConfig->readTiming.clockDivideRatio = (btr_val & FMC_BTR_CLKDIV_MASK) >> FMC_BTR_CLKDIV_OFFSET;
  pConfig->readTiming.dataLatency = (btr_val & FMC_BTR_DATLAT_MASK) >> FMC_BTR_DATLAT_OFFSET;
  pConfig->readTiming.accessMode = (btr_val & FMC_BTR_ACCMOD_MASK) >> FMC_BTR_ACCMOD_OFFSET;

  pConfig->writeTiming.addressSetupPhaseDuration = (bwtr_val & FMC_BWTR_ADDSET_MASK) >> FMC_BWTR_ADDSET_OFFSET;
  pConfig->writeTiming.addressHoldPhaseDuration = (bwtr_val & FMC_BWTR_ADDHLD_MASK) >> FMC_BWTR_ADDHLD_OFFSET;
  pConfig->writeTiming.dataPhaseDuration = (bwtr_val & FMC_BWTR_DATAST_MASK) >> FMC_BWTR_DATAST_OFFSET;
  pConfig->writeTiming.busTurnaroundPhaseDuration = (bwtr_val & FMC_BWTR_BUSTURN_MASK) >> FMC_BWTR_BUSTURN_OFFSET;
  pConfig->writeTiming.accessMode = (bwtr_val & FMC_BWTR_ACCMOD_MASK) >> FMC_BWTR_ACCMOD_OFFSET;
}

void FMC_configureNANDFlash(const FMC_NAND_FLASH_Configuration* pConfig)
{
  struct FMC_NAND_Flash_regs* regs = (void*) FMC_NAND_FLASH_BASE;
}

void FMC_getConfigNANDFlash(FMC_NAND_FLASH_Configuration* pConfig)
{
  struct FMC_NAND_Flash_regs* regs = (void*) FMC_NAND_FLASH_BASE;
}

void FMC_configureSDRAM(const FMC_SDRAM_Configuration* pConfig)
{
  struct FMC_SDRAM_regs* regs = (void*) FMC_SDRAM_BASE;
}

void FMC_getConfigSDRAM(FMC_SDRAM_Configuration* pConfig)
{
  struct FMC_SDRAM_regs* regs = (void*) FMC_SDRAM_BASE;
}