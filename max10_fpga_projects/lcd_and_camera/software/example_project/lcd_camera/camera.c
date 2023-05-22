/**
 * @file camera.c
 * @author Brandon Dunne
 * @brief 
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "camera.h"
#include <drivers/inc/dma_avalon_st_sink_to_mm_master.h>
#include <drivers/inc/altera_avalon_i2c.h>
#include <stdint.h>

#define OV7670_GAIN_REG 0x00
#define OV7670_BLUE_REG 0x01
#define OV7670_RED_REG 0x02
#define OV7670_VREF_REG 0x03
#define OV7670_COM1_REG 0x04
#define OV7670_BAVE_REG 0x05
#define OV7670_GbAVE_REG 0x06
#define OV7670_AECHH_REG 0x07
#define OV7670_RAVE_REG 0x08
#define OV7670_COM2_REG 0x09
#define OV7670_PID_REG 0x0A
#define OV7670_VER_REG 0x0B
#define OV7670_COM3_REG 0x0C
#define OV7670_COM4_REG 0x0D
#define OV7670_COM5_REG 0x0E
#define OV7670_COM6_REG 0x0F
#define OV7670_AECH_REG 0x10
#define OV7670_CLKRC_REG 0x11

#define OV7670_COM7_REG 0x12
// bit[7]: SCCB Register Reset: 0 No change, 1 Resets all registers to default values
// bit[5]: output format - CIF selection
// bit[4]: output format - QVGA selection
// bit[3]: output format - QCIF selection
// bit[2]: output format - RGB selection

#define OV7670_COM8_REG 0x13
#define OV7670_COM9_REG 0x14
#define OV7670_COM10_REG 0x15
#define OV7670_HSTART_REG 0x16
#define OV7670_HSTOP_REG 0x18
#define OV7670_VSTART_REG 0x19
#define OV7670_VSTOP_REG 0x1A
#define OV7670_PSHFT_REG 0x1B
#define OV7670_MIDH_REG 0x1C
#define OV7670_MIDL_REG 0x1D
#define OV7670_MVFP_REG 0x1E
#define OV7670_LAEC_REG 0x1F
#define OV7670_ADCCTR0_REG 0x20
#define OV7670_ADCCTR1_REG 0x21
#define OV7670_ADCCTR2_REG 0x22
#define OV7670_ADCCTR3_REG 0x23
#define OV7670_AEW_REG 0x24
#define OV7670_AEB_REG 0x25
#define OV7670_VPT_REG 0x26
#define OV7670_BBIAS_REG 0x27
#define OV7670_GbBIAS_REG 0x28
#define OV7670_EXHCH_REG 0x2A
#define OV7670_EXHCL_REG 0x2B
#define OV7670_RBIAS_REG 0x2C
#define OV7670_ADVFL_REG 0x2D
#define OV7670_ADVFH_REG 0x2E
#define OV7670_YAVE_REG 0x2F
#define OV7670_HSYST_REG 0x30
#define OV7670_HSYEN_REG 0x31
#define OV7670_HREF_REG 0x32

#define OV7670_I2C_ADDR 0x21

struct CameraState {
  ALT_AVALON_I2C_DEV_t* i2c_ handle;
  dma_s2m_handle_t dma_handle;
}

int camera_init()
{
  ALT_AVALON_I2C_DEV_t* i2c_dev = alt_avalon_i2c_open("/open/i2c");

  /* configure I2C controller: 7-bit addressing mode, set scl frequency/duty-cycle, 
     set color format to RGB565 */

  ALT_AVALON_I2C_MASTER_CONFIG_t i2c_cfg;
  alt_avalon_i2c_master_config_get(i2c_dev, &i2c_cfg);

  i2c_cfg.addr_mode = ALT_AVALON_I2C_ADDR_MODE_7_BIT;
  i2c_cfg.speed_mode = ALT_AVALON_I2C_SPEED_FAST;
  i2c_cfg.scl_hcnt = (alt_u16) 100; // 100 10ns clock cycles
  i2c_cfg.scl_lcnt = (alt_u16) 200; // 200 10ns clock cycles
  i2c_cfg.sda_cnt = (alt_u16) 30; // 30 10ns clock cycles

  alt_avalon_i2c_master_config_set(i2c_dev, &i2c_cfg);

  // set slave address
  alt_avalon_i2c_master_target_set(i2c_dev, OV7670_I2C_ADDR);

  /* Set color format to RGB565 using the OV7670 camera's I2C interface */

  uint8_t buf[] = {OV7670_COM7_REG, 0x00}; // {register address, register value}

  // read-modify-write the COM7 register
  ALT_AVALON_I2C_STATUS_CODE status;
  
  do {
    // send command byte
    status = alt_avalon_i2c_master_transmit(i2c_dev, buf, 1, 0, 0);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  if (status < 0) return status;

  do {
    // read register value
    status = alt_avalon_i2c_master_receive(i2c_dev, &buf[1], 1, 0, 1);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  if (status < 0) return status;

  // clear COM7[0]
  buf[1] &= ~(1<<0);
  // set COM7[2]
  buf[1] |= (1<<2);

  do {
    // write modified value to register
    status = alt_avalon_i2c_master_transmit(i2c_dev, buf, 2, 0, 1);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  return status;
}

int camera_horizontalFlip()
{
  ALT_AVALON_I2C_DEV_t* i2c_dev = alt_avalon_i2c_open("/dev/i2c");

  uint8_t buf[] = {OV7670_MVFP_REG, 0x00}; // { register address, register value }
  
  ALT_AVALON_I2C_STATUS_CODE status;

  do {
    // send cmd byte to specify which register to read from 
    status = alt_avalon_i2c_master_transmit(i2c_dev, buf, 1, 0, 0);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);
  
  if (status < 0) return status;

  do {
    // read from the specified register
    status = alt_avalon_i2c_master_receive(i2c_dev, &buf[1], 1, 0, 1);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  if (status < 0) return status;

  // toggle the horizontal-flip bit
  buf[1] ^= (1<<5);

  do {
    // write modified result to the specified register
    status = alt_avalon_i2c_master_transmit(i2c_dev, buf, 2, 0, 1);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  return status;
}

int camera_verticalFlip()
{
  ALT_AVALON_I2C_DEV_t* i2c_dev = alt_avalon_i2c_open("/dev/i2c");

  uint8_t buf[] = {OV7670_MVFP_REG, 0x00}; // {register address, register value}

  ALT_AVALON_I2C_STATUS_CODE status;

  do {
    // send cmd byte to specify the register to read from
    status = alt_avalon_i2c_master_transmit(i2c_dev, buf, 1, 0, 0);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  if (status < 0) return status;

  do {
    // read from the specified register
    status = alt_avalon_i2c_master_receive(i2c_dev, &buf[1], 1, 0, 1);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  if (status < 0) return status;

  // toggle the vertical-flip bit
  buf[1] ^= (1<<4);

  do {
    // write modifed value to the specified register
    status = alt_avalon_i2c_master_transmit(i2c_dev, buf, 2, 0, 1);
  } while (status==ALT_AVALON_I2C_ARB_LOST_ERR || status==ALT_AVALON_I2C_NACK_ERR || status==ALT_AVALON_I2C_BUSY);

  return status;
}

CameraStatus_t camera_capture(void* dst)
{
  dma_s2m_handle_t handle = dma_s2m_open("/dev/dma_avalon_st_sink_to_mm_master_0");
  dma_s2m_set_base_addr(handle, dst);
  dma_s2m_enable_stream(handle);

  dma_s2m_status_t status = dma_s2m_get_status(handle);

  // If stream is enabled then a frame is still in progress. If
  // interrupts are enabled then no need to wait until the frame completes or overruns.
  if (status & DMA_S2M_STATUS_STREAM_ENABLE && status & DMA_S2M_STATUS_FRAME_COMPLETE_IRQ_ENABLE)
    return CAMERA_STATUS_CAPTURE_IN_PROGRESS;

  while (1)
  {
    if (status & DMA_S2M_STATUS_OVERRUN_ERROR)
      return CAMERA_STATUS_CAPTURE_FAILED;
    
    if (status & DMA_S2M_STATUS_FRAME_COMPLETE)
      return CAMERA_STATUS_CAPTURE_COMPLETE;

    status = dma_s2m_get_status(handle);
  }
}

void camera_registerCallback(CameraCallbackID_t id, CameraCallback_t callback, void* context)
{
  dma_s2m_handle_t handle = dma_s2m_open("/dev/dma_avalon_st_sink_to_mm_master_0");
  switch (id)
  {
    case CAMERA_CALLBACK_ID_CAPTURE_COMPLETE:
      dma_s2m_register_fc_callback(handle, callback, context);
      break;
    case CAMERA_CALLBACK_ID_CAPTURE_FAILED:
      dma_s2m_register_oe_callback(handle, callback, context);
  }
}

void camera_unregisterCallback(CameraCallbackID_t id)
{
  dma_s2m_handle_t handle = dma_s2m_open("/dev/dma_avalon_st_sink_to_mm_master");
  switch (id)
  {
    case CAMERA_CALLBACK_ID_CAPTURE_COMPLETE:
      dma_s2m_unregister_fc_callback(handle);
      break;
    case CAMERA_CALLBACK_ID_CAPTURE_FAILED:
      dma_s2m_unregister_oe_callback(handle);
  }
}