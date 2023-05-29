/**
 * @file lcd8080.h
 * @author Brandon Dunne
 * @brief This header defines the device driver used to drive
 *  the LCD8080 device.
 */

#ifndef _LCD8080_H_
#define _LCD8080_H_

#include <sys/alt_dev.h>
#include <stdint.h>

struct lcd8080_regs {
  uint16_t command; // send command to the LCD
  uint16_t data; // send data/args to the LCD
};

struct lcd8080_dev {
  alt_llist_llist;
  const char* name;
  struct lcd8080_regs* regs;
};

typedef struct lcd8080_dev* lcd8080_handle_t;

/**
 * @brief This function creates a device list with one device in it, 
 *  perform a soft reset, turn the display on, set the row and column bounds, then
 *  put the LCD in write continuous mode.
 * 
 * @param dev 
 */
void lcd8080_init(struct lcd8080_dev* dev);

/**
 * @brief This functions used so application code get
 *  a handle to the LCD device.
 * 
 * @param name of the device listed in system.h
 * @return lcd8080_handle_t 
 */
lcd8080_handle_t lcd8080_open(const char* name);

/**
 * @brief This function writes to the LCD with void* data,
 *  and expects it to be the same size as the LCD resolution 320x480.
 * 
 * @param handle 
 * @param data
 */
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