#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>

#define EXTI_RISING_EDGE 1u
#define EXTI_FALLING_EDGE 3u
#define EXTI_BOTH_EDGES 7u

void EXTI_enableInterrupts(uint32_t mask, uint32_t edge);
void EXTI_disableInterrupts(uint32_t mask);
uint32_t EXTI_getPendingEvents();
void EXTI_clearPendingEvents(uint32_t mask);

#endif