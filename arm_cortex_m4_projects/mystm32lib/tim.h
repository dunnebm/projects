#ifndef TIM_H
#define TIM_H

#include <stdint.h>

#define TIM_TRIGGER_ITR0 0u // Internal Trigger 0
#define TIM_TRIGGER_ITR1 1u // Internal Trigger 1
#define TIM_TRIGGER_ITR2 2u // Internal Trigger 2
#define TIM_TRIGGER_ITR3 3u // Internal Trigger 3
#define TIM_TRIGGER_TI1F_ED 4u // TI1 Edge Detector
#define TIM_TRIGGER_TI1FP1 5u // Filtered Timer Input 1
#define TIM_TRIGGER_TI2FP2 6u // Filtered Timer Input 2
#define TIM_TRIGGER_ETRF 7u // External Trigger Input

#define TIM_SLAVE_MODE_DISABLED 0u
#define TIM_SLAVE_MODE_ENCODER_MODE1 1u
#define TIM_SLAVE_MODE_ENCODER_MODE2 2u
#define TIM_SLAVE_MODE_ENCODER_MODE3 3u
#define TIM_SLAVE_MODE_RESET_MODE 4u
#define TIM_SLAVE_MODE_GATED_MODE 5u
#define TIM_SLAVE_MODE_TRIGGER_MODE 6u
#define TIM_SLAVE_MODE_EXTERNAL_CLOCK_MODE 7u

#define TIM_EVENT_UIF (1<<0)
#define TIM_EVENT_CC1IF (1<<1)
#define TIM_EVENT_CC2IF (1<<2)
#define TIM_EVENT_CC3IF (1<<3)
#define TIM_EVENT_CC4IF (1<<4)
#define TIM_EVENT_COMIF (1<<5)
#define TIM_EVENT_TIF (1<<6)
#define TIM_EVENT_BIF (1<<7)
#define TIM_EVENT_CC1OF (1<<9)
#define TIM_EVENT_CC2OF (1<<10)
#define TIM_EVENT_CC3OF (1<<11)
#define TIM_EVENT_CC4OF (1<<12)

#define TIM_CH4_OUTPUT_COMPARE 0u
#define TIM_CH4_INPUT_CAPTURE_TI4 1u
#define TIM_CH4_INPUT_CAPTURE_TI3 2u
#define TIM_CH4_INPUT_CAPTURE_TRC 3u

#define TIM_CH3_OUTPUT_COMPARE 0u
#define TIM_CH3_INPUT_CAPTURE_TI3 1u
#define TIM_CH3_INPUT_CAPTURE_TI4 2u
#define TIM_CH3_INPUT_CAPTURE_TRC 3u

#define TIM_CH2_OUTPUT_COMPARE 0u
#define TIM_CH2_INPUT_CAPTURE_TI2 1u
#define TIM_CH2_INPUT_CAPTURE_TI1 2u
#define TIM_CH2_INPUT_CAPTURE_TRC 3u

#define TIM_CH1_OUTPUT_COMPARE 0u
#define TIM_CH1_INPUT_CAPTURE_TI1 1u
#define TIM_CH1_INPUT_CAPTURE_TI2 2u
#define TIM_CH1_INPUT_CAPTURE_TRC 3u

#define TIM_CHANNEL_MODE_OUTPUT_COMPARE 0u
#define TIM_CHANNEL_MODE_INPUT_CAPTURE_1 1u
#define TIM_CHANNEL_MODE_INPUT_CAPTURE_2 2u
#define TIM_CHANNEL_MODE_INPUT_CAPTURE_3 3u

#define TIM_COUNT_DIRECTION_UP 0u
#define TIM_COUNT_DIRECTION_DOWN 1u

#define TIM_OUTPUT_COMPARE_MODE_FROZEN 0u
#define TIM_OUTPUT_COMPARE_MODE_ACTIVE_ON_MATCH 1u
#define TIM_OUTPUT_COMPARE_MODE_INACTIVE_ON_MATCH 2u
#define TIM_OUTPUT_COMPARE_MODE_TOGGLE 3u
#define TIM_OUTPUT_COMPARE_MODE_FORCE_INACTIVE 4u
#define TIM_OUTPUT_COMPARE_MODE_FORCE_ACTIVE 5u
#define TIM_OUTPUT_COMPARE_MODE_PWM_MODE1 6u
#define TIM_OUTPUT_COMPARE_MODE_PWM_MODE2 7u

#define TIM_INPUT_CAPTURE_EVERY_EVENT 0u
#define TIM_INPUT_CAPTURE_EVERY_2_EVENTS 1u
#define TIM_INPUT_CAPTURE_EVERY_4_EVENTS 2u
#define TIM_INPUT_CAPTURE_EVERY_8_EVENTS 3u

#define TIM_OUTPUT_COMPARE_PRELOAD_DISABLED 0u
#define TIM_OUTPUT_COMPARE_PRELOAD_ENABLED 1u

#define TIM_AUTO_RELOAD_PRELOAD_DISABLE 0u
#define TIM_AUTO_RELOAD_PRELOAD_ENABLE 1u

#define TIM_ONE_PULSE_MODE_DISABLE 0u
#define TIM_ONE_PULSE_MODE_ENABLE 1u

#define TIM_TRGO_SELECT_UG 0u
#define TIM_TRGO_SELECT_CEN 1u
#define TIM_TRGO_SELECT_UEV 2u
#define TIM_TRGO_SELECT_COMPARE_PULSE 3u
#define TIM_TRGO_SELECT_OC1REF 4u
#define TIM_TRGO_SELECT_OC2REF 5u
#define TIM_TRGO_SELECT_OC3REF 6u
#define TIM_TRGO_SELECT_OC4REF 7u

#define TIM_CAPTURE_COMPARE_DMA_REQUEST_ON_CCX_EVENT 0u
#define TIM_CAPTURE_COMPARE_DMA_REQUEST_ON_UPDATE_EVENT 1u

typedef enum {
  TIM1 = 0x40010000,
  TIM2 = 0x40000000,
  TIM3 = 0x40000400,
  TIM4 = 0x40000800,
  TIM5 = 0x40000C00,
  TIM6 = 0x40001000,
  TIM7 = 0x40001400,
  TIM8 = 0x40010400
} TIM;

typedef struct {
  uint32_t preloadEnable;
  uint32_t fastEnable;
  uint32_t mode;
} TIMOutputCompareConfiguration;

typedef struct {
  uint32_t prescaler;
  uint32_t filter;
} TIMInputCaptureConfiguration;

typedef struct {
  uint32_t mode;
  union {
    TIMOutputCompareConfiguration outputConfig;
    TIMInputCaptureConfiguration inputConfig;
  };
} TIMChannelConfiguration;

typedef struct {
  uint32_t countDirection;
  uint32_t onePulseMode;
  uint32_t autoReloadPreload;
  uint32_t alignmentSelect;
  uint32_t trgoSelect;
  uint32_t trgiSelect;
} TIMConfiguration;

void TIM_enableClock(TIM tim);
void TIM_disableClock(TIM tim);
void TIM_configure(TIM tim, const TIMConfiguration* pConfig);
void TIM_configureChannel(TIM tim, uint32_t channel, const TIMChannelConfiguration* pConfig);
void TIM_start(TIM tim);
void TIM_stop(TIM tim);
void TIM_enableChannel(TIM tim, uint32_t channel);
void TIM_disableChannel(TIM tim, uint32_t channel);
uint32_t TIM_getEvents(TIM tim);
void TIM_clearEvents(TIM tim, uint32_t flags);
void TIM_setChannelValue(TIM tim, uint32_t channel, uint32_t val);
uint32_t TIM_getChannelValue(TIM tim, uint32_t channel);
void TIM_setAutoReloadValue(TIM tim, uint32_t val);
void TIM_setPrescaler(TIM tim, uint32_t val);
uint32_t TIM_getCount(TIM tim);
void TIM_enableInterrupts(TIM tim, uint32_t flags);
void TIM_disableInterrupts(TIM tim, uint32_t flags);
void TIM_enableDMARequests(TIM tim, uint32_t flags);
void TIM_disableDMARequests(TIM tim, uint32_t flags);

#endif