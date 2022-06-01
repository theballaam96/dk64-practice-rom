#ifndef UTIL_H
#define UTIL_H
#include "../ultra64.h"
#include "mips.h"
#include "n64.h"
#include "startup.h"

/* set irq bit and return previous value */
static inline int set_irqf(int irqf)
{
  unsigned int sr;

  __asm__ ("mfc0    %[sr], $12;" : [sr] "=r"(sr));
  int old_irqf = sr & MIPS_STATUS_IE;

  sr = (sr & ~MIPS_STATUS_IE) | (irqf & MIPS_STATUS_IE);
  __asm__ ("mtc0    %[sr], $12;" :: [sr] "r"(sr));

  return old_irqf;
}

static inline int get_irqf(void)
{
  unsigned int sr;

  __asm__ ("mfc0    %[sr], $12;" : [sr] "=r"(sr));

  return sr & MIPS_STATUS_IE;
}

static inline void dcache_inv(const void *ptr, size_t len)
{
  unsigned int p = (unsigned int)ptr & ~0xF;
  unsigned int e = (unsigned int)ptr + len;
  while (p < e) {
    __asm__ ("cache   0x11, 0x0000(%[p]);" :: [p] "r"(p));
    p += 0x10;
  }
}

static inline void dcache_wbinv(const void *ptr, size_t len)
{
  unsigned int p = (unsigned int)ptr & ~0xF;
  unsigned int e = (unsigned int)ptr + len;
  while (p < e) {
    __asm__ ("cache   0x15, 0x0000(%[p]);" :: [p] "r"(p));
    p += 0x10;
  }
}

static inline void dcache_wb(const void *ptr, size_t len)
{
  unsigned int p = (unsigned int)ptr & ~0xF;
  unsigned int e = (unsigned int)ptr + len;
  while (p < e) {
    __asm__ ("cache   0x19, 0x0000(%[p]);" :: [p] "r"(p));
    p += 0x10;
  }
}

/* safe (non-signaling) nan check */
static inline _Bool is_nan(float f)
{
  unsigned int exp_mask = 0b01111111100000000000000000000000;
  unsigned int sig_mask = 0b00000000011111111111111111111111;
  union
  {
    unsigned int  w;
    float     f;
  } pun;
  pun.f = f;
  return (pun.w & exp_mask) == exp_mask && (pun.w & sig_mask) != 0;
}

static inline void maybe_init_gp(void)
{
#ifndef NO_GP
  init_gp();
#endif
}

#endif