#include "i2c.h"
#include "rcc.h"

#define I2C_CR1_PE_BIT (1<<0)
#define I2C_CR1_SMBUS_BIT (1<<1)
#define I2C_CR1_SMBUS_OFFSET 1
#define I2C_CR1_SMBTYPE_BIT (1<<3)
#define I2C_CR1_SMBTYPE_OFFSET 3
#define I2C_CR1_ENARP_BIT (1<<4)
#define I2C_CR1_ENPEC_BIT (1<<5)
#define I2C_CR1_ENGC_BIT (1<<6)
#define I2C_CR1_NOSTRETCH_BIT (1<<7)
#define I2C_CR1_START_BIT (1<<8)
#define I2C_CR1_STOP_BIT (1<<9)
#define I2C_CR1_ACK_BIT (1<<10)
#define I2C_CR1_POS_BIT (1<<11)
#define I2C_CR1_PEC_BIT (1<<12)
#define I2C_CR1_ALERT_BIT (1<<13)
#define I2C_CR1_SWRST_BIT (1<<15)

#define I2C_CR2_FREQ_MASK (0x1f<<0)
#define I2C_CR2_FREQ_OFFSET 0
#define I2C_CR2_ITERREN_BIT (1<<8)
#define I2C_CR2_ITEVTEN_BIT (1<<9)
#define I2C_CR2_ITBUFEN_BIT (1<<10)
#define I2C_CR2_DMAEN_BIT (1<<11)
#define I2C_CR2_LAST_BIT (1<<12)

#define I2C_OAR1_ADD0_BIT (1<<0)
#define I2C_OAR1_ADD0_OFFSET 0
#define I2C_OAR1_ADDR_MASK (0x7f<<1)
#define I2C_OAR1_ADDR_OFFSET 1
#define I2C_OAR1_ADDMODE_BIT (1<<15)
#define I2C_OAR1_ADDMODE_OFFSET 15

#define I2C_OAR2_ENDUAL_BIT (1<<0)
#define I2C_OAR2_ENDUAL_OFFSET 0

#define I2C_SR1_SB_BIT (1<<0)
#define I2C_SR1_ADDR_BIT (1<<1)
#define I2C_SR1_BTF_BIT (1<<2)
#define I2C_SR1_ADD10_BIT (1<<3)
#define I2C_SR1_STOPF_BIT (1<<4)
#define I2C_SR1_RXNE_BIT (1<<6)
#define I2C_SR1_TXE_BIT (1<<7)
#define I2C_SR1_BERR_BIT (1<<8)
#define I2C_SR1_ARL0_BIT (1<<9)
#define I2C_SR1_AF_BIT (1<<10)
#define I2C_SR1_OVR_BIT (1<<11)
#define I2C_SR1_PECERR_BIT (1<<12)
#define I2C_SR1_TIMEOUT_BIT (1<<14)
#define I2C_SR1_SMBALERT_BIT (1<<15)

#define I2C_SR2_MSL_BIT (1<<0)
#define I2C_SR2_BUSY_BIT (1<<1)
#define I2C_SR2_TRA_BIT (1<<2)
#define I2C_SR2_GENCALL_BIT (1<<4)
#define I2C_SR2_SMBDEFAULT_BIT (1<<5)
#define I2C_SR2_SMBHOST_BIT (1<<6)
#define I2C_SR2_DUALF_BIT (1<<7)
#define I2C_SR2_PEC_MASK (0xff<<8)

struct I2C_regs {
  uint32_t cr1;
  uint32_t cr2;
  uint32_t oar1;
  uint32_t oar2;
  uint32_t dr;
  uint32_t sr1;
  uint32_t sr2;
  uint32_t ccr;
  uint32_t trise;
  uint32_t fltr;
};

void I2C_enableClock(I2C i2c)
{
  struct RCC_regs* regs = (struct RCC_regs*) RCC_BASE;
  switch (i2c)
  {
    case I2C1:
      regs->apb1enr |= RCC_I2C1_EN;
      break;
    case I2C2:
      regs->apb1enr |= RCC_I2C2_EN;
      break;
    case I2C3:
      regs->apb1enr |= RCC_I2C3_EN;
  }
}

void I2C_disableClock(I2C i2c)
{
  struct RCC_regs* regs = (struct RCC_regs*) RCC_BASE;
  switch (i2c)
  {
    case I2C1:
      regs->apb1enr &= ~RCC_I2C1_EN;
      break;
    case I2C2:
      regs->apb1enr &= ~RCC_I2C2_EN;
      break;
    case I2C3:
      regs->apb1enr &= ~RCC_I2C3_EN;
  }
}

int I2C_read(I2C base, uint8_t regAddr, uint8_t* buf, int len)
{
  struct I2C_regs* regs = (struct I2C_regs*) base;

  // master transmitter mode to specify which register to read from
  regs->oar1 &= ~I2C_OAR1_ADD0_BIT;
  // start communication
  regs->cr1 |= I2C_CR1_START_BIT;

  while (1)
  {
    uint32_t status = regs->sr1;
    if (status & I2C_SR1_AF_BIT)
      return -1;

    if (status & I2C_SR1_TXE_BIT)
      break;
  }
  
  regs->dr = regAddr;

  // master receiver mode
  regs->oar1 |= I2C_OAR1_ADD0_BIT;

  // start communication reading from regAddr
  regs->cr1 |= I2C_CR1_START_BIT;

  // wait until address is sent, and make sure it was
  // acknowledged
  while (1)
  {
    uint32_t status = regs->sr1;
    if (status & I2C_SR1_AF_BIT)
      return -1;

    if (status & I2C_SR1_ADDR_BIT)
      break;
  }

  for (int i = 0; i < len; ++i)
  {
    if (regs->sr1 & I2C_SR1_RXNE_BIT)
      buf[i] = regs->dr;
  }
}

int I2C_write(I2C base, uint8_t regAddr, const uint8_t* buf, int len)
{
  struct I2C_regs* regs = (struct I2C_regs*) base;

  // transmitter mode
  regs->oar1 &= ~I2C_OAR1_ADD0_BIT;

  // start communication
  regs->cr1 |= I2C_CR1_START_BIT;

  for (int i = 0; i < len; ++i)
  {
    uint32_t status = regs->sr1;
    if (status & I2C_SR1_AF_BIT)
      return -1; // did not receive an ACK
    else if (status & I2C_SR1_TXE_BIT && status)
      regs->dr = buf[i];
  }
}