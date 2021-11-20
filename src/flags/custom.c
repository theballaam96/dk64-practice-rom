#include "../../include/common.h"

static const char flag_byte[16] = "Byte: 0x0";
static const char flag_bit[16] = "Bit: 0";

static const char flag_type0[] = "Type: Permanent";
static const char flag_type1[] = "Type: Global";
static const char flag_type2[] = "Type: Temporary";

static const char flag_state_clear[] = "Current State: Clear";
static const char flag_state_set[] = "Current State: Set";

static const char flag_change_clear[] = "Clear";
static const char flag_change_set[] = "Set";

static const char* flagcustom_array[] = {
	flag_byte,
	flag_bit,
	flag_type0,
	flag_state_clear,
	flag_change_set,
};

static const char* flag_types[] = {
	flag_type0,
	flag_type1,
	flag_type2
};

void openFlagsCustomMenu(void) {
	dk_strFormat((char *)flag_byte, "Byte: 0x%04X",CustomFlag.byte);
	dk_strFormat((char *)flag_bit, "Bit: %1d",CustomFlag.bit);
	flagcustom_array[2] = flag_types[(int)CustomFlag.type];
	short _encodedflag = (CustomFlag.byte << 3) + CustomFlag.bit;
	char _flagset = checkFlag(_encodedflag,CustomFlag.type);
	if (_flagset) {
		flagcustom_array[3] = flag_state_set;
		flagcustom_array[4] = flag_change_clear;
	} else {
		flagcustom_array[3] = flag_state_clear;
		flagcustom_array[4] = flag_change_set;
	}
	changeMenu(54);
}

short getByteCap(char flagType) {
	switch (flagType) {
		case 0:
			return 0x13B;
			break;
		case 1:
			return 0x7;
			break;
		case 2:
			return 0xF;
		break;		
	}
	return 0;
}

void changeCustomFlagVariable(void) {
	char _change = 0;
	short _bytecap = 0x13C;
	short _newdata;
	if (ActiveMenu.isOpen) {
		if (ActiveMenu.screenIndex == 54) {
			if (NewlyPressedControllerInput.Buttons & D_Left) {
				_change = -1;
			} else {
				if (NewlyPressedControllerInput.Buttons & D_Right) {
					_change = 1;
				}
			}
			if (_change != 0) {
				_bytecap = getByteCap(CustomFlag.type);
				switch(ActiveMenu.positionIndex) {
					case 0:
						// Byte
						_newdata = CustomFlag.byte + _change;
						if (_newdata < 0) {
							_newdata = _bytecap;
						} else {
							if (_newdata > _bytecap) {
								_newdata = 0;
							}
						}
						CustomFlag.byte = _newdata;
						break;
					case 1:
						// Bit
						_newdata = CustomFlag.bit + _change;
						if (_newdata < 0) {
							_newdata = 7;
						} else {
							if (_newdata > 7) {
								_newdata = 0;
							}
						}
						CustomFlag.bit = _newdata;
						break;
					case 2:
						// Type
						_newdata = CustomFlag.type + _change;
						if (_newdata < 0) {
							_newdata = 2;
						} else {
							if (_newdata > 2) {
								_newdata = 0;
							}
						}
						CustomFlag.type = _newdata;
						_bytecap = getByteCap(CustomFlag.type);
						if (CustomFlag.byte > _bytecap) {
							CustomFlag.byte = _bytecap;
						}
					break;
				}
				openFlagsCustomMenu();
			}
		}
	}
}

void toggleCustomFlag(void) {
	short _encodedflag = (CustomFlag.byte << 3) + CustomFlag.bit;
	char _current_state = checkFlag(_encodedflag,CustomFlag.type);
	_current_state = 1 - _current_state;
	setFlag(_encodedflag,_current_state,CustomFlag.type);
	if (CustomFlag.type == 1) {
		SaveToGlobal();
	}
	playSFX(BeepHigh);
	openFlagsCustomMenu();
}

static const int flagcustom_functions[] = {
	(int)&toggleCustomFlag,
	(int)&toggleCustomFlag,
	(int)&toggleCustomFlag,
	0,
	(int)&toggleCustomFlag,
};

const Screen flagcustom_struct = {
	.TextArray = (int*)flagcustom_array,
	.FunctionArray = flagcustom_functions,
	.ArrayItems = 5,
	.ParentScreen = 43,
	.ParentPosition = 10
};