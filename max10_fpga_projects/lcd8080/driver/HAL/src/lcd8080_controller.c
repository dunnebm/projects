#include "lcd8080_controller.h"
#include <sys/alt_dma.h>
#include <errno.h>

ALT_LLIST_HEAD(lcd8080_dev_list);

static void writeArgs(void* args, int nArgs);
static void readArgs(void* args, int nArgs);
static void writeData(void* data, int size);
static void readData(void* data, int size);

void lcd8080_init(alt_dev* dev)
{
  extern alt_llist lcd8080_dev_list;
  alt_dev_llist_insert((alt_dev_llist*) dev, &lcd8080_dev_list);

  alt_dev_reg(dev);

  struct lcd8080_regs* regs = ((struct lcd8080_dev*)dev)->regs;

  regs->command = LCD8080_CMD_SOFT_RESET;
  regs->command = LCD8080_CMD_DISPLAY_OFF;
}

int lcd8080_open(alt_fd* fd, const char* name, int flags, int mode)
{
  struct lcd8080_dev* dev = (struct lcd8080_dev*)fd->dev;

  uint16_t start = 0, end = LCD8080_ROWS - 1;

  dev->regs->command = LCD8080_ROW_ADDR_SET;
  dev->regs->data = (uint16_t)0; // start row;
  dev->regs->data = (uint16_t)LCD8080_ROWS - 1; // end row

  dev->regs->command = LCD8080_COL_ADDR_SET;
  dev->regs->data = (uin16_t)0; // start column
  dev->regs->data = (uint16_t)LCD8080_COLS - 1; // end column

  dev->regs->command = LCD8080_DISPLAY_ON;
}

int lcd8080_close(alt_fd* fd)
{
  struct lcd8080_dev* dev = (struct lcd8080_dev*)fd->dev;
  dev->regs->command = LCD8080_DISPLAY_OFF;
}

int lcd8080_ioctl(alt_fd* fd, int cmd, void* args)
{
  struct lcd8080_dev* dev = (struct lcd8080_dev*)fd->dev;

  switch (cmd)
  {
    case LCD8080_NOP:
    case LCD8080_SOFT_RESET:
    case LCD8080_SLEEP_IN:
    case LCD8080_SLEEP_OUT:
    case LCD8080_PARTIAL_MODE_ON:
    case LCD8080_NORMAL_DISPLAY_MODE_ON:
    case LCD8080_DISPLAY_INVERSION_OFF:
    case LCD8080_DISPLAY_INVERSION_ON:
    case LCD8080_DISPLAY_OFF:
    case LCD8080_DISPLAY_ON:
      dev->regs->command = cmd;
      break;
    case LCD8080_ROW_ADDR_SET:
    case LCD8080_COL_ADDR_SET:
      writeArgs(args, 4);
      break;
    case LCD8080_MEM_WRITE:
    case LCD8080_MEM_WRITE_CONT:
      dev->regs->command = cmd;
      writeData(args, LCD_ROWS*LCD_COLS);
      break;
    default:
      return -EINVAL;
  }
  return 0;
}