#include "usart.h"
#include "rcc.h"
#include <stdarg.h>

/* Status register flags */
#define USART_PE (1<<0) // Parity error
#define USART_FE (1<<1) // Framing error
#define USART_NF (1<<2) // Noise detected flag
#define USART_ORE (1<<3) // overrun error detected
#define USART_IDLE (1<<4) // IDLE line detected
#define USART_RXNE (1<<5) // read data register not empty
#define USART_TC (1<<6) // transmission complete
#define USART_TXE (1<<7) // transmit register data empty
#define USART_LBD (1<<8) // line break detection
#define USART_CTS (1<<9)

/* Control Register 1 flags */
#define USART_SBK (1<<0) // Send break
#define USART_RWU (1<<1) // Receiver wakeup
#define USART_RE (1<<2) // Receiver enable
#define USART_TE (1<<3) // Transmitter enable
#define USART_IDLEIE (1<<4) // IDLE line interrupt enable
#define USART_RXNEIE (1<<5) // rx not empty interrupt enable
#define USART_TCIE (1<<6) // Transmission complete interrupt enable
#define USART_TXEIE (1<<7) // tx data register empty interrupt enable
#define USART_PEIE (1<<8) // Parity error interrupt enable
#define USART_PS (1<<9) // Parity selection
#define USART_PCE (1<<10) // Parity control enable
#define USART_WAKE (1<<11) // Wakeup method
#define USART_M (1<<12) // Word length
#define USART_UE (1<<13) // USART enable
#define USART_OVER8 (1<<15) // Oversampling mode
#define USART_OVER8_OFFSET 15

/* Control Register 2 flags */
#define USART_ADD (1<<0) // Address of the USART node
#define USART_LBDL (1<<5) // LIN break detection length
#define USART_LBDIE (1<<6) // LIN break detection interrupt enable
#define USART_LBCL (1<<8) // Last bit clock pulse
#define USART_CPHA (1<<9) // Clock phase
#define USART_CPOL (1<<10) // Clock polarity
#define USART_CLKEN (1<<11) // Clock enable
#define USART_STOP (1<<12) // Number of stop bits
#define USART_LINEN (1<<14) // LIN mode enable

/* Control Register 3 flags */
#define USART_EIE (1<<0) // Error interrupt enable
#define USART_IREN (1<<1) // IrDA mode enable
#define USART_IRLP (1<<2) // IrDA low-power
#define USART_HDSEL (1<<3) // Half-duplex selection
#define USART_NACK (1<<4) // Smartcard NACK enable
#define USART_SCEN (1<<5) // Smartcard mode enable
#define USART_DMAR (1<<6) // DMA enable receiver
#define USART_DMAT (1<<7) // DMA enable transmitter
#define USART_RTSE (1<<8) // RTS enable
#define USART_CTSE (1<<9) // CTS enable
#define USART_CTSIE (1<<10) // CTS interrupt enable
#define USART_ONEBIT (1<<11) // One sample bit method enable

#define CLOCK_FREQ 8e6

struct USART_regs
{
  volatile uint32_t sr;
  volatile uint32_t dr;
  uint32_t brr;
  uint32_t cr1;
  uint32_t cr2;
  uint32_t cr3;
  uint32_t gtpr;
};

void USART_enable(USART usart)
{
  struct USART_regs* USART_regs = (struct USART_regs*) usart;
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;
  
  switch (usart)
  {
    case USART1:
      RCC_regs->apb2enr |= RCC_USART1_EN;
      break;
    case USART2:
      RCC_regs->apb1enr |= RCC_USART2_EN;
      break;
    case USART3:
      RCC_regs->apb1enr |= RCC_USART3_EN;
      break;
    case UART4:
      RCC_regs->apb1enr |= RCC_UART4_EN;
      break;
    case UART5:
      RCC_regs->apb1enr |= RCC_UART5_EN;
  }

  USART_regs->cr1 |= USART_UE;

  // hardcode to 9.6 kbaud
  USART_regs->brr = 0x683;
}

void USART_disable(USART usart)
{
  struct USART_regs* USART_regs = (struct USART_regs*) usart;
  struct RCC_regs* RCC_regs = (struct RCC_regs*) RCC_BASE;

  USART_regs->cr1 &= ~USART_UE;

  switch (usart)
  {
    case USART1:
      RCC_regs->apb2enr &= ~RCC_USART1_EN;
      break;
    case USART2:
      RCC_regs->apb1enr &= ~RCC_USART2_EN;
      break;
    case USART3:
      RCC_regs->apb1enr &= ~RCC_USART3_EN;
      break;
    case UART4:
      RCC_regs->apb1enr &= ~RCC_UART4_EN;
      break;
    case UART5:
      RCC_regs->apb1enr &= ~RCC_UART5_EN;
  }
}

void USART_enableTransmitter(USART usart)
{
  struct USART_regs* regs = (struct USART_regs*) usart;
  regs->cr1 |= USART_TE;
}

void USART_disableTransmitter(USART usart)
{
  struct USART_regs* regs = (struct USART_regs*) usart;
  regs->cr1 &= ~USART_TE;
}

void USART_enableReceiver(USART usart)
{
  struct USART_regs* regs = (struct USART_regs*) usart;
  regs->cr1 |= USART_RE;
}

void USART_disableReceiver(USART usart)
{
  struct USART_regs* regs = (struct USART_regs*) usart;
  regs->cr1 &= ~USART_RE;
}

int USART_read(USART base, char* buf, int len)
{
  struct USART_regs* regs = (struct USART_regs*) base;
  char* ptr = buf;

  if (len <= 0)
    return 0;

  while (1)
  {
    if (regs->sr & USART_RXNE && ptr-buf < len)
    {
      *ptr++ = regs->dr;
      continue;
    }

    if (ptr - buf > 0)
      break;
  }

  return ptr - buf;
}

int USART_write(USART base, const char* buf, int len)
{
  struct USART_regs* regs = (struct USART_regs*) base;

  int i = 0;
  while (i < len)
  {
    if (regs->sr & USART_TXE)
      regs->dr = buf[i++];
  }

  return i;
}

void USART_enableInterrupt(USART base, uint32_t flags)
{
  struct USART_regs* regs = (struct USART_regs*) base;
  regs->sr |= (flags & 0x3ff);
}

void USART_disableInterrupt(USART base, uint32_t flags)
{
  struct USART_regs* regs = (struct USART_regs*) base;
  regs->sr &= ~(flags & 0x3ff);
}