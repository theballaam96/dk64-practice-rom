#include "../../../include/common.h"

static const char candy_upgrade[18] = "UPGRADE LEVEL: 0";
static const char candy_melons[10] = "MELONS: 0";

static const char candy_dk0[] = "DK: NO INSTRUMENT";
static const char candy_dk1[] = "DK: BONGO BLAST";

static const char candy_di0[] = "DIDDY: NO INSTRUMENT";
static const char candy_di1[] = "DIDDY: GUITAR GAZUMP";

static const char candy_la0[] = "LANKY: NO INSTRUMENT";
static const char candy_la1[] = "LANKY: TROMBONE TREMOR";

static const char candy_ti0[] = "TINY: NO INSTRUMENT";
static const char candy_ti1[] = "TINY: SAXOPHONE SLAM";

static const char candy_ch0[] = "CHUNKY: NO INSTRUMENT";
static const char candy_ch1[] = "CHUNKY: TRIANGLE TRAMPLE";

static const char* candy_array[] = {
	candy_dk0,
	candy_di0,
	candy_la0,
	candy_ti0,
	candy_ch0,
	candy_upgrade,
	candy_melons,
};

static const char* candy_list_dk[] = {
	candy_dk0,
	candy_dk1,
};

static const char* candy_list_di[] = {
	candy_di0,
	candy_di1,
};

static const char* candy_list_la[] = {
	candy_la0,
	candy_la1,
};

static const char* candy_list_ti[] = {
	candy_ti0,
	candy_ti1,
};

static const char* candy_list_ch[] = {
	candy_ch0,
	candy_ch1,
};

static const int* candy_list_kong[] = {
	(int*)candy_list_dk,
	(int*)candy_list_di,
	(int*)candy_list_la,
	(int*)candy_list_ti,
	(int*)candy_list_ch,
};

void openCandyMenu(void) {
	char _bitfield = MovesBase[0].instrument_bitfield & 8;
	char _level = 0;
	if (_bitfield) {
		_level = 3;
	} else {
		_bitfield = MovesBase[0].instrument_bitfield & 4;
		if (_bitfield) {
			_level = 2;
		} else {
			_bitfield = MovesBase[0].instrument_bitfield & 2;
			if (_bitfield) {
				_level = 1;
			}
		}
	}
	dk_strFormat((char *)candy_upgrade,"UPGRADE LEVEL: %d",_level);
	dk_strFormat((char *)candy_melons,"MELONS: %d",CollectableBase.Melons);
	for (int i = 0; i < 5; i++) {
		candy_array[i] = (char*)candy_list_kong[i][(int)MovesBase[i].instrument_bitfield & 1];
	}
	changeMenu(66);
};

void toggleMelonCount(void) {
	char _base = CollectableBase.Melons + 1;
	if (_base > 3) {
		_base = 1;
	}
	CollectableBase.Melons = _base;
	CollectableBase.Health = CollectableBase.Melons << 2;
	openCandyMenu();
};

void toggleInstrument(void) {
	char _base = MovesBase[(int)ActiveMenu.positionIndex].instrument_bitfield & 1;
	if (_base) {
		MovesBase[(int)ActiveMenu.positionIndex].instrument_bitfield = MovesBase[(int)ActiveMenu.positionIndex].instrument_bitfield & 0xFE;	
	} else {
		MovesBase[(int)ActiveMenu.positionIndex].instrument_bitfield = MovesBase[(int)ActiveMenu.positionIndex].instrument_bitfield | 1;
	}
	openCandyMenu();
};

void toggleUpgradeLevel(void) {
	char _base = MovesBase[0].instrument_bitfield & 8;
	char _orstate = 2;
	if (_base) {
		_orstate = 0;
	} else {
		_base = MovesBase[0].instrument_bitfield & 4;
		if (_base) {
			_orstate = 14;
		} else {
			_base = MovesBase[0].instrument_bitfield & 2;
			if (_base) {
				_orstate = 6;
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		MovesBase[i].instrument_bitfield = (MovesBase[i].instrument_bitfield & 0xF1) | _orstate;
	}
	openCandyMenu();
};

static const int candy_functions[] = {
	(int)&toggleInstrument,
	(int)&toggleInstrument,
	(int)&toggleInstrument,
	(int)&toggleInstrument,
	(int)&toggleInstrument,
	(int)&toggleUpgradeLevel,
	(int)&toggleMelonCount,
};

const Screen candy_struct = {
	.TextArray = (int*)candy_array,
	.FunctionArray = candy_functions,
	.ArrayItems = 7,
	.ParentScreen = 63,
	.ParentPosition = 4
};