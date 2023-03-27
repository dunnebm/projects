/**
 * @file pan_tilt.c
 * @author Brandon Dunne
 * 
 * @brief 
 *  The pan_tilt driver uses a timer to drive two PWM signals, one for each servo. 
 *  The duty-cycle is 20ms and the active-high pulse must be between 1ms to 2ms.
 *  To accomplish this, the timer is configured as a microsecond counter, and it 
 *  counts to 20000 then resets. The two channels are configured to pulse high 
 *  between 18ms (18000) and 19ms (19000), and remain high until 20ms, then they 
 *  are pulled low and the cycle repeats.
 */

#include "pan_tilt.h"
#include "../mystm32lib/tim.h"
#include "../mystm32lib/gpio.h"

void pt_init()
{
  // PA8 -> TIM1_CH1 -> pan servo; PA9 -> TIM1_CH2 -> tilt servo
  GPIO_setMode(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_MODE_ALT_FUNC);
  GPIO_setOutputType(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_OUTPUT_TYPE_PUSH_PULL);
  GPIO_setAltFunc(GPIOA, GPIO_PIN_8 | GPIO_PIN_9, GPIO_ALT_FUNC_1);

  TIM_enableClock(TIM1);

  // use the prescalar to slow the clock down to 1MHz
  // prescalar = (freq_sys / freq_desired) + 1 = (16MHz / 1MHz) + 1 = 17
  TIM_setPrescaler(TIM1, 17);

  // Set the timer to count to 20000 (20ms) 
  TIM_setAutoReloadValue(TIM1, 20000);

  TIMConfiguration config;
  config.alignmentSelect = 0;
  config.autoReloadPreload = TIM_AUTO_RELOAD_PRELOAD_DISABLE;
  config.countDirection = TIM_COUNT_DIRECTION_UP;
  config.onePulseMode = TIM_ONE_PULSE_MODE_DISABLE;

  TIMChannelConfiguration chConfig;
  chConfig.mode = TIM_CHANNEL_MODE_OUTPUT_COMPARE;
  chConfig.outputConfig.mode = TIM_OUTPUT_COMPARE_MODE_PWM_MODE2;
  chConfig.outputConfig.preloadEnable = TIM_OUTPUT_COMPARE_PRELOAD_ENABLED;
  chConfig.outputConfig.fastEnable = 0;

  TIM_configure(TIM1, &config);
  TIM_configureChannel(TIM1, 1, &chConfig);
  TIM_configureChannel(TIM1, 2, &chConfig);
}

static void setServoPosition(int channel, int val)
{
  // val must be within [0,1000] or it gets clamped
  if (val > 1000)
    val = 1000;
  else if (val < 0)
    val = 0;

  TIM_setChannelValue(TIM1, (uint32_t) channel, 20000 - val);
}

void pt_setPanServo(int val)
{
  setServoPosition(1, val);
}

void pt_setTiltServo(int val)
{
  setServoPosition(2, val);
}

void pt_movePanServo(int val)
{
  val += (int)TIM_getChannelValue(TIM1, 1);
  setServoPosition(1, val);
}

void pt_moveTiltServo(int val)
{
  val += (int)TIM_getChannelValue(TIM1, 2);
  setServoPosition(2, val);
}