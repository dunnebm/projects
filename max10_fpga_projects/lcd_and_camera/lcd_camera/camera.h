/**
 * @file camera.h
 * @author Brandon Dunne
 * @brief This header file defines the camera API.
 *  The API abstracts the I2C and dma_avalon_st_sink_to_mm_master drivers
 *  from the application.
 */

#ifndef CAMERA_H
#define CAMERA_H

typedef void (*CameraCallback_t)(void);

typedef enum {
  CAMERA_CALLBACK_ID_CAPTURE_COMPLETE,
  CAMERA_CALLBACK_ID_CAPTURE_FAILED
} CameraCallbackID_t;

typedef enum CameraStatus {
  CAMERA_STATUS_CAPTURE_IN_PROGRESS = 0,
  CAMERA_STATUS_CAPTURE_COMPLETE = 1<<3,
  CAMERA_STATUS_CAPTURE_FAILED = 1<<4
} CameraStatus_t;

int camera_horizontalFlip();
int camera_verticalFlip();

/**
 * @brief This function initializes I2C controller--addressing mode and serial-clock frequency.
 * Then, it sets the camera's pixel format to RGB565.
 * 
 * @return I2C status flags
 */
int camera_init();

/**
 * @brief This function registers callback, and enables the interrupt-request
 *  specified by the id parameter.
 * 
 * @param id 
 * @param callback 
 */
void camera_registerCallback(CameraCallbackID_t id, CameraCallback_t callback);
void camera_unregisterCallback(CameraCallbackID_t id);

/**
 * @brief This function initializes I2C controller--addressing mode and serial-clock frequency.
 *  Then, it sets the camera's pixel format to RGB565.
 * 
 * @param buf 
 * @return CameraStatus_t 
 */
CameraStatus_t camera_capture(void* buf);

#endif