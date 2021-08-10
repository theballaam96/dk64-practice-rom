#include "../include/common.h"

void gainControl(void) {
	if (Player) {
		char _visibility = Player->visibility;
		_visibility = _visibility | 0x8;
		Player->visibility = _visibility;
		Player->control_state = 0xC;
		ButtonsEnabledBitfield = 0xFFFF;
		JoystickEnabledX = 0xFF;
		JoystickEnabledY = 0xFF;
		MapState = 8;
		Player->vehicle_actor_pointer = (int *)&Player;
	}
};