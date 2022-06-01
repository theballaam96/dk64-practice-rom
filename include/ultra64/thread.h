#ifndef N64_THREAD_H
#define N64_THREAD_H

#include "../ultra64.h"

#define OS_STATE_STOPPED          1
#define OS_STATE_RUNNABLE         2
#define OS_STATE_RUNNING          4
#define OS_STATE_WAITING          8

#define OS_PRIORITY_IDLE          0
#define OS_PRIORITY_APPMAX        127
#define OS_PRIORITY_SIMGR         140
#define OS_PRIORITY_PIMGR         150
#define OS_PRIORITY_RMONSPIN      200
#define OS_PRIORITY_RMON          250
#define OS_PRIORITY_VIMGR         254
#define OS_PRIORITY_MAX           255

typedef struct OSThread_s OSThread;

void      osCreateThread(OSThread*, OSId, void(*)(void*), void*, void*, OSPri);
void      osDestroyThread(OSThread*);
void      osYieldThread(void);
void      osStartThread(OSThread*);
void      osStopThread(OSThread*);
OSId      osGetThreadId(OSThread*);
void      osSetThreadPri(OSThread*, OSPri);
OSPri     osGetThreadPri(OSThread*);
OSThread *osGetCurrFaultedThread(void);
OSThread *osGetNextFaultedThread(OSThread*);

__attribute__((section(".bss")))
extern OSThread       viThread;
__attribute__((section(".bss")))
extern OSThread       piThread;

#endif