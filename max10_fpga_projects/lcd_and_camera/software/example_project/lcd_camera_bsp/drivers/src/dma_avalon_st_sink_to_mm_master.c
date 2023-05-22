/**
 * @file dma_avalon_st_sink_to_mm_master.c
 * @author Brandon Dunne
 * @brief 
 * 
 * 
 * @copyright Copyright (c) 2023
 */

#include <stddef.h>
#include "sys/alt_irq.h"
#include "dma_avalon_st_sink_to_mm_master.h"

extern alt_dev* alt_find_dev(const char* name, alt_llist* list);

ALT_LLIST_HEAD(dma_s2m_dev_list);

static void dma_s2m_irq_handler(void* context)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) context;
  dma_s2m_status_t status = dev->regs->csr;
  alt_irq_context cpu_sr;

  if (status & DMA_S2M_STATUS_FRAME_COMPLETE)
  {
    dev->regs->csr &= ~DMA_S2M_STATUS_FRAME_COMPLETE;
    cpu_sr = alt_irq_disable_all();
    dev->fc_callback(dev->fc_context);
    alt_irq_enable_all(cpu_sr);
  }
  else if (status & DMA_S2M_STATUS_OVERRUN_ERROR)
  {
    dev->regs->csr &= ~DMA_S2M_STATUS_OVERRUN_ERROR;
    cpu_sr = alt_irq_disable_all();
    dev->oe_callback(dev->oe_context);
    alt_irq_enable_all(cpu_sr);
  }
}

void dma_s2m_init(struct dma_s2m_dev* dev)
{
  extern alt_llist dma_s2m_dev_list;
  alt_dev_llist_insert((alt_dev_llist*) dev, &dma_s2m_dev_list);
  alt_ic_isr_register(dev->irq_id, dev->irq, dma_s2m_irq_handler, (void*) dev, NULL);
}

dma_s2m_handle_t dma_s2m_open(const char* name)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) alt_find_dev(name, &dma_s2m_dev_list);
  return (dma_s2m_handle_t) dev;
}

void dma_s2m_close(dma_s2m_handle_t handle)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->regs->csr &= ~(DMA_S2M_STATUS_STREAM_ENABLE | DMA_S2M_STATUS_FRAME_COMPLETE_IRQ_ENABLE | 
                      DMA_S2M_STATUS_OVERRUN_ERROR_IRQ_ENABLE);
  dev->fc_callback = NULL;
  dev->oe_callback = NULL;
  dev->fc_context = NULL;
  dev->oe_context = NULL;
}

void dma_s2m_register_fc_callback(
    dma_s2m_handle_t handle,
    dma_s2m_callback_t callback,
    void* context)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->fc_callback = callback;
  dev->fc_context = context;
  dev->regs->csr |= DMA_S2M_STATUS_FRAME_COMPLETE_IRQ_ENABLE;
}

void dma_s2m_register_oe_callback(
    dma_s2m_handle_t handle,
    dma_s2m_callback_t callback,
    void* context)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->oe_callback = callback;
  dev->oe_context = context;
  dev->regs->csr |= DMA_S2M_STATUS_OVERRUN_ERROR_IRQ_ENABLE;
}

void dma_s2m_unregister_fc_callback(dma_s2m_handle_t handle)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->fc_callback = NULL;
  dev->regs->csr &= ~DMA_S2M_STATUS_FRAME_COMPLETE_IRQ_ENABLE;
}

void dma_s2m_unregister_oe_callback(dma_s2m_handle_t handle)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->oe_callback = NULL;
  dev->regs->csr &= ~DMA_S2M_STATUS_OVERRUN_ERROR_IRQ_ENABLE;
}

void dma_s2m_set_base_addr(dma_s2m_handle_t handle, void* addr)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->regs->bar = (uint32_t) addr;
}

void dma_s2m_enable_stream(dma_s2m_handle_t handle)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->regs->csr |= DMA_S2M_STATUS_STREAM_ENABLE;
}

void dma_s2m_disable_stream(dma_s2m_handle_t handle)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  dev->regs->csr &= ~DMA_S2M_STATUS_STREAM_ENABLE;
}

dma_s2m_status_t dma_s2m_get_status(dma_s2m_handle_t handle)
{
  struct dma_s2m_dev* dev = (struct dma_s2m_dev*) handle;
  return (dma_s2m_status_t) dev->regs->csr;
}