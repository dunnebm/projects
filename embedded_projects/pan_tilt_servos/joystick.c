/**
 * @file joystick.c
 * @author Brandon Dunne
 * 
 * @brief 
 *  The joystick driver uses an A/D converter, timer, and DMA.
 *  The timer is used to trigger the ADC to sample every 10ms, and 
 *  the DMA moves the sampled data into SRAM.
 */

#include "../mystm32lib/gpio.h"
#include "../mystm32lib/adc.h"
#include "../mystm32lib/dma.h"
#include "../mystm32lib/syscfg.h"
#include "../mystm32lib/exti.h"
#include "../mystm32lib/tim.h"

struct data {
  const volatile uint32_t x,y;
};

// DMA destination
static struct data data;

void joystick_init()
{
  GPIO_enableClock(GPIOA);

  // PA0 and PA1 is used as analog input to the ADC
  GPIO_setMode(GPIOA, GPIO_PIN_0 | GPIO_PIN_1, GPIO_MODE_ANALOG);

  // PA4 is used to capture button presses
  GPIO_setMode(GPIOA, GPIO_PIN_4, GPIO_MODE_INPUT);
  GPIO_setInputConfig(GPIOA, GPIO_PIN_4, GPIO_INPUT_CONFIG_PULL_UP);

  // This is for capturing falling-edge events (button presses) on PA4
  SYSCFG_selectEXTISource(4, SYSCFG_EVENT_SOURCE_GPIOA);
  EXTI_enableInterrupts(GPIO_PIN_4, EXTI_FALLING_EDGE);

  DMA_enableClock(DMA2);

  // Just in case DMA2-stream0 is already enabled, disable it so 
  // it can be reconfigured
  DMA_disable(DMA2, 0);
  DMA_clearStreamFlags(DMA2, 0, DMA_ALL_FLAGS);

  DMAStreamConfiguration DMA_config;
  DMA_config.channel = 0;
  DMA_config.priority = DMA_PRIORITY_VERY_HIGH;
  DMA_config.direction = DMA_DIRECTION_PERIPHERAL_TO_MEMORY;
  DMA_config.FIFOMode = DMA_FIFO_MODE_OFF;
  DMA_config.flowController = DMA_FLOW_CONTROLLER_DMA;
  DMA_config.periphSize = DMA_DATA_SIZE_WORD;
  DMA_config.memSize = DMA_DATA_SIZE_WORD;
  DMA_config.periphIncr = DMA_INCREMENT_MODE_DISABLED;
  DMA_config.memIncr = DMA_INCREMENT_MODE_ENABLED;
  DMA_config.doubleBufferMode = DMA_DOUBLE_BUFFER_MODE_DISABLED;
  DMA_config.circularMode = DMA_CIRCULAR_MODE_ENABLED;
  DMA_config.numDataToTransfer = 2;
  DMA_config.periphAddr = (uint32_t)ADC1 + 0x4C;
  DMA_config.memAddr0 = (uint32_t) &data;

  DMA_configureStream(DMA2, 0, &DMA_config);

  DMA_enable(DMA2, 0);

  /* Use TIM2 as an external trigger for ADC1 */

  TIM_enableClock(TIM2);

  TIMConfiguration TIM_config = { 0 };
  TIM_config.trgoSelect = TIM_TRGO_SELECT_UEV;

  TIM_configure(TIM2, &TIM_config);

  // make TIM2 update count every millisecond
  TIM_setPrescaler(TIM2, 16001u);
  // trigger an ADC conversion every 10ms.
  TIM_setAutoReloadValue(TIM2, 10u);

  ADC_enable(ADC1);

  ADC_clearFlags(ADC1, ADC_ALL_FLAGS); 

  ADCConfiguration ADC_config;
  ADC_config.conversionMode = ADC_CONVERSION_MODE_SINGLE;
  ADC_config.dataAlignment = ADC_DATA_ALIGNMENT_RIGHT_ALIGNED;
  ADC_config.DMATransferSelection = ADC_DMA_TRANSFER_SELECTION_CONTINUOUS;
  ADC_config.DMAMode = ADC_DMA_MODE_ENABLED;
  ADC_config.EOCSelect = ADC_EOC_SET_AFTER_SEQUENCE_OF_REGULAR_CONVERSIONS;
  ADC_config.resolution = ADC_RESOLUTION_6_BIT;
  ADC_config.SCANMode = ADC_SCAN_MODE_DISABLED;
  ADC_config.triggerDetection = ADC_TRIGGER_DETECTION_RISING_EDGE;
  ADC_config.trigger = ADC_EXTERNAL_TRIGGER_TIM2_TRGO_EVENT;
  
  ADC_configure(ADC1, &ADC_config);

  ADC_setChannelSamplingTime(ADC1, ADC_CHANNEL0, ADC_SAMPLING_TIME_15_CYCLES);
  ADC_setChannelSamplingTime(ADC1, ADC_CHANNEL1, ADC_SAMPLING_TIME_15_CYCLES);

  ADCChannel sequence[] = {ADC_CHANNEL0, ADC_CHANNEL1};
  ADC_setSequence(ADC1, sequence, 2);
  
  TIM_start(TIM2);
}

uint32_t joystick_updated()
{
  uint32_t updated = DMA_getStreamFlags(DMA2, 0) & DMA_TRANSFER_COMPLETE_FLAG;

  if (updated)
    DMA_clearStreamFlags(DMA2, 0, DMA_TRANSFER_COMPLETE_FLAG);

  return updated;
}

uint32_t joystick_pressed()
{
  uint32_t pressed = EXTI_getPendingEvents() & GPIO_PIN_4;

  if (pressed)
    EXTI_clearPendingEvents(GPIO_PIN_4);

  return pressed;
}

uint32_t joystick_getX()
{
  return data.x;
}

uint32_t joystick_getY()
{
  return data.y;
}