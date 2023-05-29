/**
 * @file dma_avalon_st_sink_to_mm_master.h
 * @author Brandon Dunne
 * @brief This header file defines the device driver
 *  for the dma_avalon_st_sink_to_mm_master component.
 * 
 */

#ifndef DMA_AVALON_ST_SINK_TO_MM_MASTER_H
#define DMA_AVALON_ST_SINK_TO_MM_MASTER_H

#include "sys/alt_warning.h"
#include "sys/alt_dev.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t dma_s2m_status_t;
#define DMA_S2M_STATUS_STREAM_ENABLE (1<<0)
#define DMA_S2M_STATUS_FRAME_COMPLETE (1<<3)
#define DMA_S2M_STATUS_OVERRUN_ERROR (1<<4)
#define DMA_S2M_STATUS_FRAME_COMPLETE_IRQ_ENABLE (1<<1)
#define DMA_S2M_STATUS_OVERRUN_ERROR_IRQ_ENABLE (1<<2)

typedef void (*dma_s2m_callback_t)(void* context);


struct dma_s2m_regs {
  volatile uint32_t csr; // control-status register
  uint32_t bar;          // base-address register
};

struct dma_s2m_dev {
  alt_llist llist;                  
  const char* name;
  uint32_t irq;
  uint32_t irq_id;
  dma_s2m_callback_t fc_callback;
  dma_s2m_callback_t oe_callback;
  void* fc_context;
  void* oe_context;
  struct dma_s2m_regs* regs;
};

typedef struct dma_s2m_dev* dma_s2m_handle_t;

/**
 * @brief This function creates device-list so dma_s2m_open()
 *  can retrieve the device by name
 * 
 * @param dev 
 */
void dma_s2m_init(struct dma_s2m_dev* dev);

/**
 * @brief This function retrieves the device from the device
 *  list, and returns it as an opaque handle.
 * 
 * @param name 
 * @return dma_s2m_handle_t 
 */
dma_s2m_handle_t dma_s2m_open(const char* name);

/**
 * @brief This function registers a callback to handle frame-complete events.
 *  It also enables frame-complete interrupt requests.
 * 
 * @param handle 
 * @param callback
 * @param context: user-defined data
 */
void dma_s2m_register_fc_callback(
    dma_s2m_handle_t handle, 
    dma_s2m_callback_t callback, 
    void* context);

/**
 * @brief This function registers a callback to handle overrun-error events.
 *  It also enables overrun-error interrupt requests.
 * 
 * @param handle 
 * @param callback 
 * @param context 
 */
void dma_s2m_register_oe_callback(
    dma_s2m_handle_t handle,
    dma_s2m_callback_t callback,
    void* context);

/**
 * @brief This function unregisters the frame-complete callback, and disable frame-complete
 *  interrupt requests.
 * 
 * @param handle 
 */
void dma_s2m_unregister_fc_callback(dma_s2m_handle_t handle);

/**
 * @brief This funtion unregisters the overrun-error callback, and disable overrun-error
 *  interrupt requests.
 * 
 * @param handle 
 */
void dma_s2m_unregister_oe_callback(dma_s2m_handle_t handle);

/**
 * @brief This function sets the starting point where the data will be written to. The address-pointer 
 * resets to this address when a frame-complete event occurs, overrun-error event occurs, or when this
 * device gets disabled by software.
 * 
 * @param handle 
 * @param addr 
 */
void dma_s2m_set_base_addr(dma_s2m_handle_t handle, void* addr);

/**
 * @brief This function enables the stream. This means that the DMA will start
 * accepting data. 
 * 
 * @param handle 
 */
void dma_s2m_enable_stream(dma_s2m_handle_t handle);

/**
 * @brief This funtion disables the stream--stops accepting data.
 * 
 * @param handle 
 */
void dma_s2m_disable_stream(dma_s2m_handle_t handle);

/**
 * @brief This function returns the status of the DMA. This
 * information can be used to check whick event occured, if interrupts are
 * enabled, and if the stream is enabled.
 * 
 * @param handle 
 * @return dma_s2m_status_t 
 */
dma_s2m_status_t dma_s2m_get_status(dma_s2m_handle_t handle);

/* The two macros below are needed so the BSP tools will automatically 
   include them in alt_sys_init(). */

#define DMA_AVALON_ST_SINK_TO_MM_MASTER_INSTANCE(name, dev)    \
  static struct dma_s2m_dev dev = {                            \
    ALT_LLIST_ENTRY,                                           \
    name##_NAME,                                               \
    name##_IRQ,                                                \
    name##_IRQ_INTERRUPT_CONTROLLER_ID,                        \
    NULL, /* frame complete callback */                        \
    NULL, /* overrun error callback */                         \
    (struct dma_s2m_regs*) name##_BASE                         \
  }

#define DMA_AVALON_ST_SINK_TO_MM_MASTER_INIT(name, dev) dma_s2m_init(&dev)

#ifdef __cplusplus
}
#endif
#endif