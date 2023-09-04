#include "../../include/common.h"

typedef struct ts {
    unsigned int major;
    unsigned int minor;
    char logged;
} ts;

#define TS_OFFSET 0
#define TS_SIZE 8

static ts stamps[TS_SIZE];

void logTimestamp(int order) {
    int idx = order + TS_OFFSET;
    if (stamps[idx].logged < 1) {
        logTimestampInternal();
        stamps[idx].major = TempTimestampStorageMajor;
        stamps[idx].minor = TempTimestampStorageMinor;
        stamps[idx].logged = += 1;
    }
}

void ts_reset(void) {
    for (int i = 0; i < TS_SIZE; i++) {
        stamps[i].major = 0;
        stamps[i].minor = 0;
        stamps[i].logged = 0;
        if (i == (1 + TS_OFFSET)) {
            stamps[i].logged = -1;
        }
    }
    TestVariable = (int)&stamps[0].major;
}

void ts_start(void* queue, void* message, int os_state) {
    
    logTimestamp(-TS_OFFSET);
    __osRecvMesg(queue, message, os_state);
}

void ts_vimgrmain(void) {
    logTimestamp(0);
}

void ts_frameloop(void) {
    logTimestamp(1);
}

void ts_save(void) {
    logTimestamp(4);
}

void ts_debug(void) {
    logTimestamp(2);
}

void ts_crash(void* data) {
    CrashHandler(data);
    logTimestamp(3);
}

void initTS(void) {
    writeFunction(0x8073231C, &ts_crash);
    // Debug
    loadSingularHook(0x8060F120, &ts_debughook);
    loadSingularHook(0x8060F130, &ts_debughook);
    loadSingularHook(0x8060F140, &ts_debughook);
    loadSingularHook(0x8060F150, &ts_debughook);
    loadSingularHook(0x8060F17C, &ts_debughook);
    loadSingularHook(0x8060F18C, &ts_debughook);
    // Saving
    loadSingularHook(0x8060E17C, &ts_savehook);
    // Frame Loops
    loadSingularHook(0x805FC270, &ts_frameloopend);
    // VI MGR
    loadSingularHook(0x80004F48, &ts_vimgrhook);
    //writeFunction(0x80004E8C, &ts_start);
}