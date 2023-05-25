#include "syscfg.h"

#define SYSCFG_BASE 0x40013800

struct {
  uint32_t memrmp;
  uint32_t pmc;
  uint32_t exticr1;
  uint32_t exticr2;
  uint32_t exticr3;
  uint32_t exticr4;
  uint32_t cmpcr;
  uint32_t cfgr;
} *SYSCFG_regs = (void*) SYSCFG_BASE;

void SYSCFG_selectEXTISource(uint32_t EXTILine, uint32_t eventSource)
{
  uint32_t val;
  uint32_t offset;
  if (EXTILine < 4)
  {
    val = SYSCFG_regs->exticr1;
    val &= ~(0xf << EXTILine);
    val |= (eventSource & 0xf) << EXTILine;
    SYSCFG_regs->exticr1 = val;
  }
  else if (EXTILine < 8)
  {
    val = SYSCFG_regs->exticr2;
    offset = EXTILine - 4;
    val &= ~(0xf << offset);
    val |= (eventSource & 0xf) << offset;
    SYSCFG_regs->exticr2 = val;
  }
  else if (EXTILine < 12)
  {
    val = SYSCFG_regs->exticr3;
    offset = EXTILine - 8;
    val &= ~(0xf << offset);
    val |= (eventSource & 0xf) << offset;
    SYSCFG_regs->exticr3 = val;
  }
  else if (EXTILine < 16)
  {
    val = SYSCFG_regs->exticr4;
    offset = EXTILine - 12;
    val &= ~(0xf << offset);
    val |= (eventSource & 0xf) << offset;
    SYSCFG_regs->exticr4 = val;
  }
}