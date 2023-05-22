/**
 * @file lcd8080.c
 * @author Brandon Dunne
 * @brief lcd8080 driver implementation
 */

#include "lcd8080_controller.h"
#include <sys/alt_dma.h>
#include <errno.h>

ALT_LLIST_HEAD(lcd8080_dev_list);

void lcd8080_init(struct lcd8080_dev* dev)
{
  extern alt_llist lcd8080_dev_list;
  alt_dev_llist_insert((alt_dev_llist*) dev, &lcd8080_dev_list);

  struct lcd8080_regs* regs = dev->regs;

  regs->command = LCD8080_CMD_SOFT_RESET;
  regs->command = LCD8080_CMD_DISPLAY_ON;

  regs->command = LCD8080_CMD_ROW_ADDR_SET;
  regs->data = 0;
  regs->data = 0;
  regs->data = 0;
  regs->data = 0;

  regs->command = LCD8080_CMD_COL_ADDR_SET;
  regs->data = 0;
  regs->data = 0;
  regs->data = 0;
  regs->data = 0;

  regs->command = LCD8080_CMD_MEM_WRITE_CONT;
}

lcd8080_handle_t lcd8080_open(const char* name)
{
  struct lcd8080_dev* dev = (struct lcd8080_dev*) alt_find_dev(name, &lcd8080_dev_list);
  return (lcd8080_handle_t) dev;
}

int lcd8080_write(lcd8080_handle_t handle, void* data)
{
  struct lcd8080_dev* dev = (struct lcd8080_dev*) handle;

  uint16_t* ptr = (uint16_t*) data;

  for (int i = 0; i < LCD8080_ROWS*LCD8080_COLS; ++i)
    dev->regs->data = ptr++;
}