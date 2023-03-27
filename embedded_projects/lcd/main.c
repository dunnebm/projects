/**
 * @file main.c
 * @author Brandon Dunne
 * 
 * @brief 
 *  This program draws a red squared 100x100 red square on the top right
 *  corner of the ILI9486 LCD screen.
 */

#include "display.h"
#include <stdio.h>

int main()
{
  display_init();

  display_sendCmd(ILI9486_DISPLAY_ON);

  uint8_t dimensions[] = {0, 100};
  uint8_t red[] = {255u, 0u, 0u};

  // number of rows
  display_sendCmd(ILI9486_PAGE_ADDRESS_SET);
  display_sendData(&dimensions, sizeof(dimensions));

  // number of columns
  display_sendCmd(ILI9486_COLUMN_ADDRESS_SET);
  display_sendData(&dimensions, sizeof(dimensions));

  display_sendCmd(ILI9486_MEMORY_WRITE);

  // draw a red square
  for (int i = 0; i < 100; ++i)
  {
    for (int j = 0; j < 100; ++j)
    {
      display_sendData(red, sizeof(red));
    }
  }

  while (1);
}