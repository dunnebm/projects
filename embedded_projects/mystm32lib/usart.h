#ifndef USART_H
#define USART_H

#include <stdint.h>

#define USART_TX_DATA_REGISTER_EMPTY_FLAG (1<<7)
#define USART_CTS_FLAG (1<<9)
#define USART_TRANSMISSION_COMPLETE_FLAG (1<<6)
#define USART_RX_DATA_REGISTER_NOT_EMPTY_FLAG (1<<5)
#define USART_OVERRUN_ERROR_FLAG (1<<3)
#define USART_IDLE_FLAG (1<<4)
#define USART_PARITY_ERROR_FLAG (1<<0)
#define USART_BREAK_FLAG (1<<8)
#define USART_NOISE_FLAG (1<<2)

typedef enum {
  USART1 = 0x40010400,
  USART2 = 0x40004400,
  USART3 = 0x40004800,
  UART4 = 0x40004C00,
  UART5 = 0x40005000
} USART;

void USART_enableTransmitter(USART usart);
void USART_disableTransmitter(USART usart);
void USART_enableReceiver(USART usart);
void USART_disableReceiver(USART usart);
void USART_enable(USART usart);
void USART_disable(USART usart);
int USART_read(USART base, char* buf, int len);
int USART_write(USART base, const char* buf, int len);
void USART_enableInterrupts(USART usart, uint32_t flags);
void USART_disableInterrupts(USART usart, uint32_t flags);

#endif