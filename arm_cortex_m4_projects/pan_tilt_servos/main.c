/**
 * @file main.c
 * @author Brandon Dunne
 * 
 * @brief 
 *  This program polls the joystick for button presses and 
 *  position updates, then writes the value to the pan_tilt controller.
 *  The pan_tilt controller uses this value to control the pulse-width
 *  of both servos.
 */

#include <stdio.h>
#include "joystick.h"
#include "pan_tilt.h"

// Values between 0-1000 are allowed for the pan_tilt controller.
// The joystick has 6-bit resolution (0-64). Therefore, the conversion
// factor from joystick (ADC) to pan_tilt controller (servo) is 1000/64, which
// is approximately 6.
#define ADC_TO_SERVO_CONVERSION 6

int main()
{
  joystick_init();
  pt_init();

  int x, y, prev_x = 0, prev_y = 0;

  while (1)
  {
    if (joystick_updated())
    {
      if (joystick_pressed())
        printf("Button pressed! Do something.\n");

      x = (int) joystick_getX();
      y = (int) joystick_getY();
      
      pt_movePanServo(ADC_TO_SERVO_CONVERSION * (x - prev_x));
      pt_moveTiltServo(ADC_TO_SERVO_CONVERSION * (y - prev_y));

      prev_x = x;
      prev_y = y;
    }
  }

  return 0;
}