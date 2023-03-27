#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define EXTI_BASE 0x40013C00

typedef enum {
  GPIOA = 0x40020000,
  GPIOB = 0x40020400,
  GPIOC = 0x40020800,
  GPIOD = 0x40020C00,
  GPIOE = 0x40021000,
  GPIOF = 0x40021400,
  GPIOG = 0x40021800,
  GPIOH = 0x40021C00
} GPIO;

/*
typedef enum {
  PA0 = 0, PA1 = 1, PA2 = 2, PA3 = 3, PA4 = 4, PA5 = 5, PA6 = 6, PA7 = 7, PA8 = 8, PA9 = 9, PA10 = 10, PA11 = 11, PA12 = 12, PA13 = 13, PA14 = 14, PA15 = 15,
  PB0 = 16, PB1 = 17, PB2 = 18, PB3 = 19, PB4 = 20, PB5 = 21, PB6 = 22, PB7 = 23, PB8 = 24, PB9 = 25, PB10 = 26, PB11 = 27, PB12 = 28, PB13 = 29, PB14 = 30, PB15 = 31,
  PC0 = 32, PC1 = 33, PC2 = 34, PC3 = 35, PC4 = 36, PC5 = 37, PC6 = 38, PC7 = 39, PC8 = 40, PC9 = 41, PC10 = 42, PC11 = 43, PC12 = 44, PC13 = 45, PC14 = 46, PC15 = 47,
  PD0 = 48, PD1 = 49, PD2 = 50, PD3 = 51, PD4 = 52, PD5 = 53, PD6 = 54, PD7 = 55, PD8 = 56, PD9 = 57, PD10 = 58, PD11 = 59, PD12 = 60, PD13 = 61, PD14 = 62, PD15 = 63,
  PE0 = 64, PE1 = 65, PE2 = 66, PE3 = 67, PE4 = 68, PE5 = 69, PE6 = 70, PE7 = 71, PE8 = 72, PE9 = 73, PE10 = 74, PE11 = 75, PE12 = 76, PE13 = 77, PE14 = 78, PE15 = 79,
  PF0 = 80, PF1 = 81, PF2 = 82, PF3 = 83, PF4 = 84, PF5 = 85, PF6 = 86, PF7 = 87, PF8 = 88, PF9 = 89, PF10 = 90, PF11 = 91, PF12 = 92, PF13 = 93, PF14 = 94, PF15 = 95,
  PG0 = 96, PG1 = 97, PG2 = 98, PG3 = 99, PG4 = 100, PG5 = 101, PG6 = 102, PG7 = 103, PG8 = 104, PG9 = 105, PG10 = 106, PG11 = 107, PG12 = 108, PG13 = 109, PG14 = 110, PG15 = 111,
  PH0 = 112, PH1 = 113, PH2 = 114, PH3 = 115, PH4 = 116, PH5 = 117, PH6 = 118, PH7 = 119, PH8 = 120, PH9 = 121, PH10 = 123, PH11 = 124, PH12 = 125, PH13 = 126, PH14 = 127, PH15 = 128
} GPIO_PIN;
*/

typedef enum {
  GPIO_MODE_INPUT = 0,
  GPIO_MODE_OUTPUT = 1,
  GPIO_MODE_ALT_FUNC = 2,
  GPIO_MODE_ANALOG = 3
} GPIO_MODE;

typedef enum {
  GPIO_OUTPUT_TYPE_PUSH_PULL = 0,
  GPIO_OUTPUT_TYPE_OPEN_DRAIN = 1
} GPIO_OUTPUT_TYPE;

typedef enum {
  GPIO_OUTPUT_SPEED_LOW_SPEED = 0,
  GPIO_OUTPUT_SPEED_MEDIUM_SPEED = 1,
  GPIO_OUTPUT_SPEED_FAST_SPEED = 2,
  GPIO_OUTPUT_SPEED_HIGH_SPEED = 3
} GPIO_OUTPUT_SPEED;

typedef enum {
  GPIO_INPUT_CONFIG_NO_PULL_UP_NO_PULL_DOWN = 0,
  GPIO_INPUT_CONFIG_PULL_UP = 1,
  GPIO_INPUT_CONFIG_PULL_DOWN = 3
} GPIO_INPUT_CONFIG;

typedef enum {
  GPIO_PIN_0 = 1<<0,
  GPIO_PIN_1 = 1<<1,
  GPIO_PIN_2 = 1<<2,
  GPIO_PIN_3 = 1<<3,
  GPIO_PIN_4 = 1<<4,
  GPIO_PIN_5 = 1<<5,
  GPIO_PIN_6 = 1<<6,
  GPIO_PIN_7 = 1<<7,
  GPIO_PIN_8 = 1<<8,
  GPIO_PIN_9 = 1<<9,
  GPIO_PIN_10 = 1<<10,
  GPIO_PIN_11 = 1<<11,
  GPIO_PIN_12 = 1<<12,
  GPIO_PIN_13 = 1<<13,
  GPIO_PIN_14 = 1<<14,
  GPIO_PIN_15 = 1<<15
} GPIO_PINS;

typedef enum {
  GPIO_ALT_FUNC_0 = 0x0,
  GPIO_ALT_FUNC_1 = 0x1,
  GPIO_ALT_FUNC_2 = 0x2,
  GPIO_ALT_FUNC_3 = 0x3,
  GPIO_ALT_FUNC_4 = 0x4,
  GPIO_ALT_FUNC_5 = 0x5,
  GPIO_ALT_FUNC_6 = 0x6,
  GPIO_ALT_FUNC_7 = 0x7,
  GPIO_ALT_FUNC_8 = 0x8,
  GPIO_ALT_FUNC_9 = 0x9,
  GPIO_ALT_FUNC_10 = 0xA,
  GPIO_ALT_FUNC_11 = 0xB,
  GPIO_ALT_FUNC_12 = 0xC,
  GPIO_ALT_FUNC_13 = 0xD,
  GPIO_ALT_FUNC_14 = 0xE,
  GPIO_ALT_FUNC_15 = 0xF
} GPIO_ALT_FUNC;

typedef struct {
  GPIO_MODE mode;
  GPIO_OUTPUT_TYPE otype;
  GPIO_OUTPUT_SPEED ospeed;
  GPIO_INPUT_CONFIG iconfig;
} GPIO_CONFIG;

struct gpio_resource {
  GPIO gpio;
  GPIO_PINS pin;
  GPIO_ALT_FUNC af;
};

void GPIO_enableClock(GPIO gpio);
void GPIO_disableClock(GPIO gpio);
void GPIO_write(GPIO gpio, uint32_t val);
void GPIO_set(GPIO gpio, uint32_t pin_mask);
void GPIO_clear(GPIO gpio, uint32_t pin_mask);
uint32_t GPIO_readOutputData(GPIO gpio);
uint32_t GPIO_readInputData(GPIO gpio);
void GPIO_setMode(GPIO gpio, GPIO_PINS pin_mask, GPIO_MODE mode);
void GPIO_setOutputType(GPIO gpio, GPIO_PINS pin_mask, GPIO_OUTPUT_TYPE otype);
void GPIO_setOutputSpeed(GPIO gpio, GPIO_PINS pins, GPIO_OUTPUT_SPEED ospeed);
void GPIO_setInputConfig(GPIO gpio, GPIO_PINS pins, GPIO_INPUT_CONFIG config);
void GPIO_setAltFunc(GPIO gpio, GPIO_PINS pin_mask, GPIO_ALT_FUNC gpio_alt_func);

#ifdef __cplusplus
}
#endif

#endif