#ifndef _LCD8080_H_
#define _LCD8080_H_

#include <sys/alt_dev.h>
#include <stdint.h>

#define LCD8080_ROWS 320
#define LCD8080_COLS 480


// Soft reset: resets the display and the row and column counters.
// no args
#define LCD8080_CMD_SOFT_RESET 0x01

// Column address set: sets the column bounds for read and write commands
// args: uint16_t array[] = {start, end};
#define LCD8080_CMD_COL_ADDR_SET 0x2A

// Row address set: sets the row bounds for read and write commands
// args: uint16_t array[] = {start, end};
#define LCD8080_CMD_ROW_ADDR_SET 0x2B

// Memory write: command sets the row and column counters to the start positions
//               specified in the "row address set" and "column address set" commands.
//               Next, data is sent in the RGB565 format, row-by-row, until all the
//               pixels covered in the bounds have been written to; all other writes are ignored.
// args: uint16_t array[(endRow - startRow) * (endCol - startCol)] = {rgb565, ..., rgb565};
#define LCD8080_CMD_MEM_WRITE 0x2C

// Memory write continue: This command writes to frame memory like the "Memory write" command,
//                        but it doesn't reset the row and column counters, and when the last pixel
//                        in the bounds is reached the counters reset to the first pixel in the bounds.
#define LCD8080_CMD_MEM_WRITE_CONT 0x3C

#define LCD8080_CMD_DISPLAY_OFF 0x28
#define LCD8080_CMD_DISPLAY_ON 0x29

struct lcd8080_regs {
  uint16_t command;
  uint16_t data;
};

struct lcd8080_dev {
  alt_llist llist;
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
    (struct lcd8080_regs*) name##_BASE   \
  }                                      

  #define LCD8080_INIT(name, dev) lcd8080_init(&dev)

#endif