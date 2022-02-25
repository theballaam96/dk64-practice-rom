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
	int next_active = 0;
	int prev_active = 0;
	heap_free = 0;
	heap_used = 0;
	heap_allocated = 0;
	unsigned int size = 0;
	heap* heap_dupe = heap_pointer;
	if (heap_dupe) {
		while (0 == 0) {
			next_active = isRDRAM(heap_dupe->next);
			prev_active = isRDRAM(heap_dupe->prev);
			if ((next_active) || (prev_active)) {
				heap_free += heap_dupe->size;
			} else {
				heap_used += heap_dupe->size;
				heap_allocated += 1;
			}
			size = heap_dupe->size;
			heap_dupe = (heap *)((int)heap_dupe + 0x10 + size);
			prev_active = isRDRAM(heap_dupe);
			next_active = isRDRAM(heap_dupe->unk);
			if ((prev_active == 0) || (next_active == 0)) {
				break;
			}
		}
	}
	heap_total = heap_free + heap_used;
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