#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
  I2C1 = 0x40005400,
  I2C2 = 0x40005800,
  I2C3 = 0x40005C00
} I2C;

void I2C_enableClock(I2C i2c);
void I2C_disableClock(I2C i2c);
void I2C_start(I2C i2c);
void I2C_setAddr(I2C i2c);
int I2C_write(I2C i2c, uint8_t regAddr, const uint8_t* buf, int len);
int I2C_read(I2C i2c, uint8_t regAddr, uint8_t* buf, int len);

#ifdef __cplusplus
}
#endif
#endif