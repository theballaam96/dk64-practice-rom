#ifndef PI_H
#define PI_H
#include "../ultra64.h"
#include "n64.h"

void pi_write_locked(unsigned int dev_addr, const void *src, size_t size);
void pi_read_locked(unsigned int dev_addr, void *dst, size_t size);
void pi_write(unsigned int dev_addr, const void *src, size_t size);
void pi_read(unsigned int dev_addr, void *dst, size_t size);

static inline void __pi_wait(void)
{
  while (pi_regs.status & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY))
    ;
}

static inline unsigned int __pi_read_raw(unsigned int dev_addr)
{
  __pi_wait();
  return *(volatile unsigned int *)dev_addr;
}

static inline void __pi_write_raw(unsigned int dev_addr, unsigned int value)
{
  __pi_wait();
  *(volatile unsigned int *)dev_addr = value;
}

#endif