#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>

#define JOYSTICK_MOVED (1<<0)
#define JOYSTICK_PRESSED (1<<1)

void joystick_init();
uint32_t joystick_updated();
uint32_t joystick_pressed();
uint32_t joystick_getX();
uint32_t joystick_getY();

#endif