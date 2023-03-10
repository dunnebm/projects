#ifndef SYSCFG_H
#define SYSCFG_H

#include <stdint.h>

#define SYSCFG_EVENT_SOURCE_GPIOA 0u
#define SYSCFG_EVENT_SOURCE_GPIOB 1u
#define SYSCFG_EVENT_SOURCE_GPIOC 2u
#define SYSCFG_EVENT_SOURCE_GPIOD 3u
#define SYSCFG_EVENT_SOURCE_GPIOE 4u
#define SYSCFG_EVENT_SOURCE_GPIOF 5u
#define SYSCFG_EVENT_SOURCE_GPIOG 6u

void SYSCFG_selectEXTISource(uint32_t EXTILine, uint32_t eventSource);

#endif