#include "../../include/common.h"

void changeHelmTime(int difference) {
    int new_time = HelmStartTime + difference;
    if (new_time < 0) {
        new_time = 0;
    }
    HelmStartTime = new_time;
}

void inc10mins(void) {
    changeHelmTime(600);
}

void dec10mins(void) {
    changeHelmTime(-600);
}

void inc1min(void) {
    changeHelmTime(60);
}

void dec1min(void) {
    changeHelmTime(-60);
}

void inc10s(void) {
    changeHelmTime(10);
}

void dec10s(void) {
    changeHelmTime(-10);
}

void helm_timeout(void) {
    int diff = 0 - HelmCurrentTime;
    HelmStartTime += diff;
}

void helm_10mins(void) {
    int diff = (10 * 60) - HelmCurrentTime;
    HelmStartTime += diff;
}

void helm_infinite(void) {
    int diff = (801 * 60) - HelmCurrentTime;
    if (diff > 0) {
        HelmStartTime += diff;
    }
}

static char* helmtimer_array[] = {
    "INFINITE TIME",
	"ADD 10 MINUTES",
	"ADD 1 MINUTE",
	"ADD 10 SECONDS",
    "SET TO 10 MINUTES",
	"REMOVE 10 SECONDS",
	"REMOVE 1 MINUTE",
	"REMOVE 10 MINUTES",
	"TIME OUT",
};

static const int helmtimer_functions[] = {
	(int)&helm_infinite,
    (int)&inc10mins,
    (int)&inc1min,
    (int)&inc10s,
    (int)&helm_10mins,
    (int)&dec10s,
    (int)&dec1min,
    (int)&dec10mins,
    (int)&helm_timeout
};

const Screen helmtimer_struct = {
	.TextArray = (int*)helmtimer_array,
	.FunctionArray = helmtimer_functions,
	.ArrayItems = 9,
	.ParentScreen = ACTIVEMENU_SCREEN_CHEATS_ROOT,
	.ParentPosition = 7
};