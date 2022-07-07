#include "../include/common.h"

void gainControl(void) {
	if (Player) {
		int _visibility = Player->obj_props_bitfield;
		_visibility = _visibility | 0x8;
		Player->obj_props_bitfield = _visibility;
		Player->control_state = 0xC;
		ButtonsEnabledBitfield = 0xFFFF;
		JoystickEnabledX = 0xFF;
		JoystickEnabledY = 0xFF;
		MapState = 8;
		Player->vehicle_actor_pointer = &Player;
	}
};