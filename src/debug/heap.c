#include "../../include/common.h"

static char memory_free[40] = "";
static char memory_used[40] = "";
static char memory_allocated[40] = "";
static char memory_total[40] = "";

unsigned int heap_free = 0;
unsigned int heap_used = 0;
unsigned int heap_allocated = 0;
unsigned int heap_total = 0;
float heap_free_percent = 0;
float heap_used_percent = 0;

void getMemoryStats(void) {
	heap_free = 0;
	heap_used = 0;
	heap_allocated = 0;
	for (int i = 0; i < heap_arena_count; i++) {
		heap* heap_dupe = heap_arena_meta[i].tail_pointer;
		while (0 == 0) {
			if (isRDRAM(heap_dupe)) {
				heap_used += heap_dupe->size;
				heap_allocated += 1;
				heap_dupe = (heap*)(heap_dupe->next);
			} else {
				break;
			}
		}
	}
	int end = 0;
	int fb1 = 0;
	int fb2 = 0;
	if (isRDRAM(heap_end_pointer)) {
		end = (unsigned int)(heap_end_pointer) - 0x80000000;
	}
	if (isRDRAM(fbufferPointers[1])) {
		fb2 = (unsigned int)(fbufferPointers[1]) - 0x80000000;
	}
	if (isRDRAM(fbufferPointers[0])) {
		fb1 = (unsigned int)(fbufferPointers[0]) - 0x80000000;
	}
	heap_total = end - ((2 * fb2) - fb1);
	heap_free = heap_total - heap_used;
	heap_free_percent = 100*((float)heap_free / (float)heap_total);
	heap_used_percent = 100*((float)heap_used / (float)heap_total);
}

void openHeapMenu(void) {
	getMemoryStats();
	dk_strFormat(memory_free, "FREE:0X%X BYTES <%f$>",heap_free,heap_free_percent);
	dk_strFormat(memory_used, "USED:0X%X BYTES <%f$>",heap_used,heap_used_percent);
	dk_strFormat(memory_allocated, "ALLOCATED:%d",heap_allocated);
	dk_strFormat(memory_total, "TOTAL:0X%X BYTES",heap_total);
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_HEAP);
}

static const char* heap_array[] = {
	memory_free,
	memory_used,
	memory_allocated,
	memory_total,
};

static const int heap_functions[] = {
	0,
	0,
	0,
	0,
};

const Screen heap_struct = {
	.TextArray = (int*)heap_array,
	.FunctionArray = heap_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_DEBUG_ROOT,
	.ParentPosition = 2
};