#ifndef N64_TASK_H
#define N64_TASK_H

#include "../ultra64.h"
#include "message.h"

typedef struct OSScTask_s OSScTask;

struct OSScTask_s
{
  OSScTask         *next;                     /* 0x0000 */
  unsigned int          state;                    /* 0x0004 */
  unsigned int          flags;                    /* 0x0008 */
  void             *framebuffer;              /* 0x000C */
  OSTask            list;                     /* 0x0010 */
  OSMesgQueue      *msgQ;                     /* 0x0050 */
  OSMesg            msg;                      /* 0x0054 */
                                              /* 0x0058 */
};

#endif