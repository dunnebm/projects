/**
 * @file camera.h
 * @author Brandon Dunne
 * @brief This header file defines the camera API.
 *  The API abstracts the I2C and dma_avalon_st_sink_to_mm_master drivers
 *  from the application.
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef CAMERA_H
#define CAMERA_H

struct CameraState;
typedef struct CameraState* CameraHandle_t;

typedef struct {
  CameraHandle_t handle;
  void* user_data;
} CameraCallbackContext_t;

typedef void (*CameraCallback_t)(CameraCallbackContext_t* context);

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
int camera_init();
void camera_registerCallback(CameraCallbackID_t id, CameraCallback_t callback, void* context);
void camera_unregisterCallback(CameraCallbackID_t id);
CameraStatus_t camera_capture(void* buf);

#endif