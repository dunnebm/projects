/**
 * @file lcd8080.c
 * @author Brandon Dunne
 * @brief lcd8080 driver implementation
 */

#include "lcd8080_controller.h"

#define LCD8080_ROWS 320
#define LCD8080_COLS 480

// Soft reset: resets the display and the row and column counters.
// no args
#define LCD8080_SOFT_RESET 0x01

// Column address set: sets the column bounds for read and write commands
// args: uint16_t array[] = {start, end};
#define LCD8080_COL_ADDR_SET 0x2A

// Row address set: sets the row bounds for read and write commands
// args: uint16_t array[] = {start, end};
#define LCD8080_ROW_ADDR_SET 0x2B

// Memory write: command sets the row and column counters to the start positions
//               specified in the "row address set" and "column address set" commands.
//               Next, data is sent in the RGB565 format, row-by-row, until all the
//               pixels covered in the bounds have been written to; all other writes are ignored.
// args: uint16_t array[(endRow - startRow) * (endCol - startCol)] = {rgb565, ..., rgb565};
#define LCD8080_MEM_WRITE 0x2C

// Memory write continue: This command writes to frame memory like the "Memory write" command,
//                        but it doesn't reset the row and column counters, and when the last pixel
//                        in the bounds is reached the counters reset to the first pixel in the bounds.
#define LCD8080_MEM_WRITE_CONT 0x3C

#define LCD8080_DISPLAY_INVERSION_OFF 0x20
#define LCD8080_DISPLAY_INVERSION_ON 0x21
#define LCD8080_DISPLAY_OFF 0x28
#define LCD8080_DISPLAY_ON 0x29

ALT_LLIST_HEAD(lcd8080_dev_list);

void lcd8080_init(struct lcd8080_dev* dev)
{
  extern alt_llist lcd8080_dev_list;
  alt_dev_llist_insert((alt_dev_llist*) dev, &lcd8080_dev_list);

  struct lcd8080_regs* regs = dev->regs;

  uint16_t start_row = 0;
  uint16_t end_row = LCD8080_ROWS - 1;
  
  uint16_t start_col = 0;
  uint16_t end_col = LCD8080_COLS - 1;

  regs->command = LCD8080_CMD_SOFT_RESET;
  regs->command = LCD8080_CMD_DISPLAY_ON;

  // To set the row counter: send a command followed by a start and end 
  // row address as arguments.
  regs->command = LCD8080_CMD_ROW_ADDR_SET;
  regs->data = start_row >> 8;     // start row [15:8]
  regs->data = start_row & 0x00ff; // start row [7:0]
  regs->data = end_row >> 8;       // end row [15:8]
  regs->data = end_row & 0x00ff;   // end row [7:8]

  regs->command = LCD8080_CMD_COL_ADDR_SET;
  regs->data = start_col >> 8;     // start column [15:8]
  regs->data = start_col & 0x00ff; // start column [7:0]
  regs->data = end_col >> 8;       // end column [15:8]
  regs->data = end_col & 0x00ff;   // end column [7:0]

  // Any data sent to the LCD after this command will continue to
  // write row-by-row until the last pixel address; the next write will
  // be to the beginning.
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