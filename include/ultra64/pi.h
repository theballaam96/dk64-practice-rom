#ifndef N64_PI_H
#define N64_PI_H

#include "../ultra64.h"

#define PI_STATUS_DMA_BUSY        0x01
#define PI_STATUS_IO_BUSY         0x02
#define PI_STATUS_ERROR           0x04
#define PI_STATUS_RESET           0x01
#define PI_STATUS_CLR_INTR        0x02

#define DEVICE_TYPE_CART          0
#define DEVICE_TYPE_BULK          1
#define DEVICE_TYPE_64DD          2
#define DEVICE_TYPE_SRAM          3
#define DEVICE_TYPE_INIT          7

#define PI_DOMAIN1                0
#define PI_DOMAIN2                1

#define OS_MESG_PRI_NORMAL        0
#define OS_MESG_PRI_HIGH          1

#define OS_READ                   0
#define OS_WRITE                  1
#define OS_OTHERS                 2

typedef struct
{
  unsigned int          dram_addr;                /* 0x0000 */
  unsigned int          cart_addr;                /* 0x0004 */
  unsigned int          rd_len;                   /* 0x0008 */
  unsigned int          wr_len;                   /* 0x000C */
  unsigned int          status;                   /* 0x0010 */
  unsigned int          dom1_lat;                 /* 0x0014 */
  unsigned int          dom1_pwd;                 /* 0x0018 */
  unsigned int          dom1_pgs;                 /* 0x001C */
  unsigned int          dom1_rls;                 /* 0x0020 */
  unsigned int          dom2_lat;                 /* 0x0024 */
  unsigned int          dom2_pwd;                 /* 0x0028 */
  unsigned int          dom2_pgs;                 /* 0x002C */
  unsigned int          dom2_rls;                 /* 0x0030 */
                                              /* 0x0034 */
} pi_regs_t;

typedef struct OSPiHandle_s OSPiHandle;

int osEPiStartDma_t(OSPiHandle*, OSIoMesg*, int);

void __osPiGetAccess(void);
void __osPiRelAccess(void);

#define pi_regs                   (*(volatile pi_regs_t*)0xA4600000)

#endif