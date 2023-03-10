#include <stdio.h>
#include "joystick.h"
#include "pan_tilt.h"

#define ADC_TO_SERVO_CONVERSION ((int) 1000/64)

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
        printf("Snap a picture\n");

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