#ifndef _LCD8080_H_
#define _LCD8080_H_

#include <sys/alt_dev.h>
#include <stdint.h>

#define LCD8080_ROWS 320
#define LCD8080_COLS 480

/* below are commands used for ioctl */

// Example of a command with no arguments:
// ioctl(fd, cmd, ignored);


// No operation: does nothing
// no args
#define LCD8080_NOP 0x00

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
#define LCD8080_MEM_READ 0x2E

// args: ID1[7:0], ID2[7:0], ID3[7:0]; 
#define LCD8080_READ_DISPLAY_ID_INFO 0x04

// args: D[31:24], D[23:16], D[15:8], D[7:0]
#define LCD8080_READ_DISPLAY_STATUS 0x00

// arg: D[7:0]; D[7:4] = DPI[3:0]; D[2:0] = DBI[2:0]
#define LCD8080_READ_PIXEL_FORMAT 0x0C

// Sleep in: put device in sleep mode
// no args
#define LCD8080_SLEEP_IN 0x10

// Sleep out: exit sleep mode
// no args
#define LCD8080_SLEEP_OUT 0x11

// Partial mode on: what is partial mode
// no args
#define LCD8080_PARTIAL_MODE_ON 0x12

// Normal display mode on: what is normal display mode
#define LCD8080_NORMAL_DISPLAY_MODE_ON 0x13
#define LCD8080_DISPLAY_INVERSION_OFF 0x20
#define LCD8080_DISPLAY_INVERSION_ON 0x21
#define LCD8080_DISPLAY_OFF 0x28
#define LCD8080_DISPLAY_ON 0x29

struct lcd8080_regs {
  uint16_t command;
  uint16_t data;
};

struct lcd8080_dev {
  alt_llist_llist;
  const char* name;
  struct lcd8080_regs* regs;
};

typedef struct lcd8080_dev* lcd8080_handle_t;

void lcd8080_init(struct lcd8080_dev* dev);
lcd8080_handle_t lcd8080_open(const char* name);
void lcd8080_write(lcd8080_handle_t handle, void* data);


#define LCD8080_INSTANCE(name, dev)      \
  static struct lcd8080_dev dev = {      \
    ALT_LLIST_ENTRY,                     \
    name##_NAME,                         \
    name##_IRQ,                          \
    (struct lcd8080_regs*) name##_BASE   \
  }                                      

  #define LCD8080_INIT(name, dev) lcd8080_init(&dev)

#endif