#ifndef N64_MESSAGE_H
#define N64_MESSAGE_H

#include "../ultra64.h"
#include "thread.h"

#define OS_MESG_NOBLOCK           0
#define OS_MESG_BLOCK             1

#define MQ_GET_COUNT(mq)          ((mq)->validCount)

typedef void       *OSMesg;

typedef struct
{
  OSMesgQueue      *messageQueue;             /* 0x0000 */
  OSMesg            message;                  /* 0x0004 */
} __OSEventState;

void    osSetEventMesg(OSEvent, OSMesgQueue*, OSMesg);

__attribute__((section(".bss")))
extern __OSEventState __osEventStateTab[OS_NUM_EVENTS];

__attribute__((section(".bss")))
extern unsigned int       __osViIntrCount;

#endif