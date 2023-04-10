#ifndef LCD8080_CONTROLLER_H
#define LCD8080_CONTROLLER_H

#include <sys/alt_dev.h>
#include <stdint.h>

#define LCD8080_ROWS 320
#define LCD8080_COLS 480

#define LCD8080_NOP 0x00
#define LCD8080_SOFT_RESET 0x01
#define LCD8080_COL_ADDR_SET 0x2A
#define LCD8080_ROW_ADDR_SET 0x2B
#define LCD8080_MEM_WRITE 0x2C
#define LCD8080_MEM_WRITE_CONT 0x3C
#define LCD8080_MEM_READ 0x2E

// args: ID1[7:0], ID2[7:0], ID3[7:0]; 
#define LCD8080_READ_DISPLAY_ID_INFO 0x04

// args: D[31:24], D[23:16], D[15:8], D[7:0]
#define LCD8080_READ_DISPLAY_STATUS 0x00

// arg: D[7:0]; D[7:4] = DPI[3:0]; D[2:0] = DBI[2:0]
#define LCD8080_READ_PIXEL_FORMAT 0x0C

#define LCD8080_SLEEP_IN 0x10
#define LCD8080_SLEEP_OUT 0x11
#define LCD8080_PARTIAL_MODE_ON 0x12
#define LCD8080_NORMAL_DISPLAY_MODE_ON 0x13
#define LCD8080_DISPLAY_INVERSION_OFF 0x20
#define LCD8080_DISPLAY_INVERSION_ON 0x21
#define LCD8080_DISPLAY_OFF 0x28
#define LCD8080_DISPLAY_ON 0x29

#define LCD8080_DMA_WRITE_ENABLE 0x0100
#define LCD8080_DMA_WRITE_REQUEST 0x0200
#define LCD8080_DMA_READ_ENABLE 0x0300
#define LCD8080_DMA_READ_REQUEST 0x0400

int lcd8080_open(alt_fd* fd, const char* name, int flags, int mode);
int lcd8080_close(alt_fd* fd);
int lcd8080_ioctl(alt_fd* fd, int req, void* arg);

void lcd8080_init(alt_dev* pDev);

struct lcd8080_regs {
  uint16_t command;
  uint16_t data;
};

struct lcd8080_dev {
  alt_dev dev;
  struct lcd8080_regs* regs;
};

#define LCD8080_DRIVER_INSTANCE(name, d) \
  static struct lcd8080_dev d = {        \
    {                                    \
      ALT_LLIST_ENTRY,                   \
      name##_NAME,                       \
      lcd8080_open,                      \
      lcd8080_close,                     \
      lcd8080_read,                      \
      lcd8080_write,                     \
      NULL, /* lseek */                  \
      NULL, /* fstat */                  \
      lcd8080_ioctl,                     \
    },                                   \
    (struct lcd8080_regs*) name##_BASE   \
  }                                      \

  LCD8080_DRIVER_INIT(name, d) lcd8080_init(&d)

  #define LCD8080_CONTROLLER_INSTANCE(name, dev) LCD8080_DRIVER(name, dev)
  #define LCD8080_CONTROLLER_INIT(name, dev) LCD8080_DRIVER_INIT(name, dev)

#endif