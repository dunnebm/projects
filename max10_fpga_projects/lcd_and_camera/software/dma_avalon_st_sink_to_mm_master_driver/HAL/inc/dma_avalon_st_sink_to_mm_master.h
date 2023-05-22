/**
 * @file dma_avalon_st_sink_to_mm_master.h
 * @author Brandon Dunne
 * @brief 
 * @version 0.1
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
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
  volatile uint32_t csr;
  uint32_t bar;
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

void dma_s2m_init(struct dma_s2m_dev* dev);

dma_s2m_handle_t dma_s2m_open(const char* name);

void dma_s2m_register_fc_callback(
    dma_s2m_handle_t handle, 
    dma_s2m_callback_t callback, 
    void* context);

void dma_s2m_register_oe_callback(
    dma_s2m_handle_t handle,
    dma_s2m_callback_t callback,
    void* context);

void dma_s2m_unregister_fc_callback(dma_s2m_handle_t handle);

void dma_s2m_unregister_oe_callback(dma_s2m_handle_t handle);

void dma_s2m_set_base_addr(dma_s2m_handle_t handle, void* addr);

void dma_s2m_enable_stream(dma_s2m_handle_t handle);

void dma_s2m_disable_stream(dma_s2m_handle_t handle);

dma_s2m_status_t dma_s2m_get_status(dma_s2m_handle_t handle);

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