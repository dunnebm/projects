/**
 * @file main.c
 * @author Brandon Dunne
 * @brief This program reads data from the camera, and forwards it
 *  to the LCD. The camera data is written to SDRAM using a DMA, and two callbacks
 *  are registered to handle DMA events; one for completed frames, and one for overrun errors.
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include "camera.h"
#include <drivers/inc/lcd8080.h>

#define LCD_ROWS 320
#define LCD_COLS 480

uint16_t buffer1[480*640];
uint16_t buffer2[480*640];
uint16_t framebuffer[320*480];
uint16_t* front_buffer = buffer1;
uint16_t* back_buffer = buffer2;
int capture_failed = 0;
int capture_complete = 0;

static void captureFailedHandler(void* context)
{
  capture_failed = 1;
}

static void captureCompleteHandler(void* context)
{
  capture_complete = 1;
}

static void swapBuffers()
{
  uint16_t* tmp = front_buffer;
  front_buffer = back_buffer;
  back_buffer = tmp;
}

static void changeCameraToLCDResolution()
{
  int p1 = 3; // row down-sample factor
  int q1 = 2; // row up-sample factor
  int p2 = 4; // column down-sample factor
  int q2 = 3; // column up-sample factor

  for (int i = 0; i < LCD_ROWS; ++i)
  {
    for (int j = 0; j < LCD_COLS; ++j)
    {
      int m1 = p1*i / q1;
      int m2 = m1 + q1;
      int n1 = p2*j / q2;
      int n2 = n1 + q2;

      int interpolate_row = p1*i % q1;
      int interpolate_col = p2*j % q2;

      if (interpolate_row==0 && interpolate_col==0)
        framebuffer[i*LCD_COLS + j] = front_buffer[(p1*i/q1)*LCD_COLS + (p2*j/q2)];
      else if (interpolate_row!=0 && interpolate_col==0)
      {
        float t = (float) (i % q1) / q1;
        float pixel_data = (front_buffer[m2*LCD_COLS + n1] - front_buffer[m1*LCD_COLS + n1])*t + front_buffer[m1*LCD_COLS + n1];
        framebuffer[i*LCD_COLS + j] = (uint16_t) pixel_data;
      }
      else if (interpolate_row==0 && interpolate_col!=0)
      {
        float t = (float) (j % q2) / q2;
        float pixel_data = (front_buffer[m1*LCD_COLS + n2] - front_buffer[m1*LCD_COLS + n1])*t + front_buffer[m1*LCD_COLS + n1];
        framebuffer[i*LCD_COLS + j] = (uint16_t) pixel_data;
      }
      else
      {
        float t1 = (float) (i % q1) / q1;
        float t2 = (float) (j % q2) / q2;
        float u1 = (front_buffer[m2*LCD_COLS + n1] - front_buffer[m1*LCD_COLS + n1])*t1 + front_buffer[m1*LCD_COLS + n1];
        float u2 = (front_buffer[m1*LCD_COLS + n2] - front_buffer[m1*LCD_COLS + n1])*t2 + front_buffer[m1*LCD_COLS + n1];
        uint16_t pixel_data = (uint16_t) (t1*u1 + t2*u2);
        framebuffer[i*LCD_COLS + j] = pixel_data;
      }
    }
  }
}

int main()
{
  if (camera_init())
  {
    printf("camera_init() failed!\n");
    return 1;
  }

  lcd8080_handle_t lcd8080_handle = lcd8080_open("/dev/lcd8080");

  camera_registerCallback(CAMERA_CALLBACK_ID_CAPTURE_COMPLETE, captureCompleteHandler);
  camera_registerCallback(CAMERA_CALLBACK_ID_CAPTURE_FAILED, captureFailedHandler);

  camera_capture(back_buffer);

  while (1)
  {
    if (capture_failed)
    {
      printf("capture failed: DMA overrun error!\n");
      return 1;
    }

    if (capture_complete)
    {
      capture_complete = 0;

      swapBuffers();

      // read frame from camera
      camera_capture(back_buffer); // returns before reading completes

      changeCameraToLCDResolution();

      // write front_buffer to the LCD framebuffer
      lcd8080_write(lcd8080_handle, framebuffer); // returns after writing completes
    }
  }

  return 0;
}