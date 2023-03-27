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

#define DISPLAY_RED (0xFC<<16)
#define DISPLAY_GREEN (0xFC<<8)
#define DISPLAY_BLUE (0xFC<<0)
#define DISPLAY_WHITE ((0xFC<<16) | (0xFC<<8) | (0xFC<<0))
#define DISPLAY_BLACK 0u

#define DISPLAY_DATA_ADDR 0x60000000
#define DISPLAY_CMD_ADDR 0x60000001

void display_init();
void display_sendCmd(uint8_t cmd);
void display_sendData(uint8_t* buf, int len);

#endif