#ifndef _COMMON_H_
#define _COMMON_H_

/*
	rom_version.h is dynamically created by the build system
	It only stores 1 variable, ROM_VERSION
	This is an index ranging between 4 values
	0 = US (Retail Only, Not Kiosk)
	1 = PAL (Australia/Europe)
	2 = JP
	3 = Unknown
*/
#include "rom_version.h"

#if ROM_VERSION == 1
	#define HERTZ 50 // PAL = 50Hz
#else
	#define HERTZ 60 // US/JP = 60 Hz
#endif

#define F3DEX_GBI_2
#include "ultra64.h"
#include "common_structs.h"
#include "dk64.h"
#include "enums.h"
#include "flags.h"
#include "screen_struct_def.h"
#include "global.h"
#include "screens_list.h"
#include "vars.h"

#endif