#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

// ILI9486 Commands
#define ILI9486_NOP 0x00
#define ILI9486_SOFT_RESET 0x01
#define ILI9486_DISPLAY_ON 0x29
#define ILI9486_COLUMN_ADDRESS_SET 0x2A
#define ILI9486_PAGE_ADDRESS_SET 0x2B
#define ILI9486_MEMORY_WRITE 0x2C

void display_init();
void display_sendCmd(uint8_t cmd);
void display_sendData(uint8_t* buf, int len);

#endif