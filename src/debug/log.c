#include "../include/common.h"

static char flaglog_item0[30] = "";
static char flaglog_item1[30] = "";
static char flaglog_item2[30] = "";
static char flaglog_item3[30] = "";
static char flaglog_item4[30] = "";
static char flaglog_item5[30] = "";
static char flaglog_item6[30] = "";
static char flaglog_item7[30] = "";
static char flaglog_item8[30] = "";
static char flaglog_item9[30] = "";

static flagLogData flaglog_data0 = {};
static flagLogData flaglog_data1 = {};
static flagLogData flaglog_data2 = {};
static flagLogData flaglog_data3 = {};
static flagLogData flaglog_data4 = {};
static flagLogData flaglog_data5 = {};
static flagLogData flaglog_data6 = {};
static flagLogData flaglog_data7 = {};
static flagLogData flaglog_data8 = {};
static flagLogData flaglog_data9 = {};

static flagLogData flaglog_currentf0 = {};
static flagLogData flaglog_currentf1 = {};
static flagLogData flaglog_currentf2 = {};
static flagLogData flaglog_currentf3 = {};
static flagLogData flaglog_currentf4 = {};
static flagLogData flaglog_currentf5 = {};
static flagLogData flaglog_currentf6 = {};
static flagLogData flaglog_currentf7 = {};
static flagLogData flaglog_currentf8 = {};
static flagLogData flaglog_currentf9 = {};

static char flagLog_count = 0;

static flagLogData* flagLog_dataitems[] = {
	&flaglog_data0,
	&flaglog_data1,
	&flaglog_data2,
	&flaglog_data3,
	&flaglog_data4,
	&flaglog_data5,
	&flaglog_data6,
	&flaglog_data7,
	&flaglog_data8,
	&flaglog_data9,
};

flagLogData* flagLog_currentfitems[] = {
	&flaglog_currentf0,
	&flaglog_currentf1,
	&flaglog_currentf2,
	&flaglog_currentf3,
	&flaglog_currentf4,
	&flaglog_currentf5,
	&flaglog_currentf6,
	&flaglog_currentf7,
	&flaglog_currentf8,
	&flaglog_currentf9,
};

static char* flagLog_items[] = {
	flaglog_item0,
	flaglog_item1,
	flaglog_item2,
	flaglog_item3,
	flaglog_item4,
	flaglog_item5,
	flaglog_item6,
	flaglog_item7,
	flaglog_item8,
	flaglog_item9,
};

static const char* flaglog_array[] = {
	flaglog_item0,
	flaglog_item1,
	flaglog_item2,
	flaglog_item3,
	flaglog_item4,
	flaglog_item5,
	flaglog_item6,
	flaglog_item7,
	flaglog_item8,
	flaglog_item9,
};

static const int flaglog_functions[10];

Screen flaglog_struct = {
	.TextArray = (int*)flaglog_array,
	.FunctionArray = flaglog_functions,
	.ArrayItems = 10,
	.ParentScreen = ACTIVEMENU_SCREEN_DEBUG_ROOT,
	.ParentPosition = 3
};

void writeFlagsToLog(void) {
	int shift_index = 0;
	if (FlagLogCurrentFCounter > 0) {
		for (int i = (9 - FlagLogCurrentFCounter); i >= 0 ; i--) {
			shift_index = i + FlagLogCurrentFCounter;
			if (shift_index < 10) {
				flagLog_dataitems[shift_index]->encoded_flag = flagLog_dataitems[i]->encoded_flag;
				flagLog_dataitems[shift_index]->output = flagLog_dataitems[i]->output;
				flagLog_dataitems[shift_index]->flag_type = flagLog_dataitems[i]->flag_type;
				flagLog_dataitems[shift_index]->set_frame = flagLog_dataitems[i]->set_frame;
			}
		}
		for (int i = 0; i < FlagLogCurrentFCounter; i++) {
			shift_index = FlagLogCurrentFCounter - i - 1;
			if ((shift_index < 10) && (i < 10)) {
				flagLog_dataitems[i]->encoded_flag = flagLog_currentfitems[shift_index]->encoded_flag;
				flagLog_dataitems[i]->output = flagLog_currentfitems[shift_index]->output;
				flagLog_dataitems[i]->flag_type = flagLog_currentfitems[shift_index]->flag_type;
				flagLog_dataitems[i]->set_frame = FrameReal;
			}
		}
	}
	flagLog_count += FlagLogCurrentFCounter;
	if (flagLog_count > 10) {
		flagLog_count = 10;
	}
	FlagLogCurrentFCounter = 0;
}

void openFlagLogMenu(void) {
	int _byte = 0;
	int _bit = 0;
	unsigned int _sec = 0;
	unsigned int _min = 0;
	unsigned int _hour = 0;
	unsigned int _diff = 0;
	char flagType0[] = "P";
	char flagType1[] = "G";
	char flagType2[] = "T";
	char flagSet0[] = "C";
	char flagSet1[] = "S";
	int count = flagLog_count;
	char* flagTypes[] = {
		flagType0,
		flagType1,
		flagType2,
	};
	char* flagSets[] = {
		flagSet0,
		flagSet1,
	};
	if (flagLog_count > 0) {
		for (int i = 0; i < flagLog_count; i++) {
			// 1: 0x000>0 PS 00:00:00 AGO
			_byte = flagLog_dataitems[i]->encoded_flag>>3;
			_bit = flagLog_dataitems[i]->encoded_flag - (_byte<<3);
			_diff = (FrameReal - flagLog_dataitems[i]->set_frame) / HERTZ;
			_hour = _diff / (60 * HERTZ);
			_min = (_diff - (60 * _hour)) / HERTZ;
			_sec = _diff - (3600 * _hour) - (60 * _min);
			dk_strFormat(
				flagLog_items[i],
				"%d: 0X%03X>%d %s%s %02d:%02d:%02d AGO",
				(i+1),
				_byte,
				_bit,
				flagTypes[(int)flagLog_dataitems[i]->flag_type],
				flagSets[(int)flagLog_dataitems[i]->output],
				_hour,
				_min,
				_sec
			);
		};
	} else {
		dk_strFormat(flagLog_items[0],"NO FLAGS IN LOG");
		count = 1;
	}
	flaglog_struct.ArrayItems = count;
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_FLAGLOG);
}