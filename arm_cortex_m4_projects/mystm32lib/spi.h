#ifndef SPI_H
#define SPI_H

#include <stdint.h>

// SPI1_NSS -> PA4, PA15
// SPI1_SCK -> PA5, PB3
// SPI1_MISO -> PA6, PB4
// SPI1_MOSI -> PA7, PB5

// SPI2_NSS -> PB9, PB12
// SPI2_SCK -> PA9, PB10, PB13
// SPI2_MISO -> PB14, PC2
// SPI2_MOSI -> PB15, PC3

#define SPI_FLAG_RXNE (1<<0)
#define SPI_FLAG_TXE (1<<1)
#define SPI_FLAG_CHSIDE (1<<2)
#define SPI_FLAG_UDR (1<<3)
#define SPI_FLAG_CRCERR (1<<4)
#define SPI_FLAG_MODF (1<<5)
#define SPI_FLAG_OVR (1<<6)
#define SPI_FLAG_BSY (1<<7)
#define SPI_FLAG_FRE (1<<8)

#define SPI_DATA_FRAME_SIZE_8_BIT 0u
#define SPI_DATA_FRAME_SIZE_16_BIT 1u

#define SPI_ENDIANESS_BIG_ENDIAN 0u
#define SPI_ENDIANESS_LITTLE_ENDIAN 1u

#define SPI_BAUD_2_CLK_PERIODS 0u
#define SPI_BAUD_4_CLK_PERIODS 1u
#define SPI_BAUD_8_CLK_PERIODS 2u
#define SPI_BAUD_16_CLK_PERIODS 4u
#define SPI_BAUD_32_CLK_PERIODS 5u
#define SPI_BAUD_64_CLK_PERIODS 6u
#define SPI_BAUD_128_CLK_PERIODS 7u
#define SPI_BAUD_256_CLK_PERIODS 8u

#define SPI_CLOCK_PHASE_FIRST_TRANSITION 0u
#define SPI_CLOCK_PHASE_SECOND_TRANSITION 1u

#define SPI_CLOCK_IDLE_STATE_LOW 0u
#define SPI_CLOCK_IDLE_STATE_HIGH 1u

#define SPI_MODE_MASTER 0u
#define SPI_MODE_SLAVE 1u

typedef enum {
  SPI1 = 0x40013000,
  SPI2 = 0x40003800,
  SPI3 = 0x40003C00,
  SPI4 = 0x40013400
} SPI;

typedef struct {
  uint32_t baud;
  uint32_t clockIdleState;
  uint32_t clockPhase;
  uint32_t endianess;
  uint32_t frameSize;
  uint32_t mode;
} SPIConfiguration;

void SPI_enableClock(SPI spi);
void SPI_disableClock(SPI spi);
void SPI_enable(SPI spi);
void SPI_disable(SPI spi);
void SPI_configure(SPI spi, const SPIConfiguration* pConfig);
void SPI_getConfig(SPI spi, SPIConfiguration* pConfig);
int SPI_read(SPI spi, uint8_t* buf, int len);
int SPI_write(SPI spi, const uint8_t* buf, int len);
uint32_t SPI_getFlags(SPI spi);
void SPI_clearFlags(SPI spi, uint32_t flags);

#endif