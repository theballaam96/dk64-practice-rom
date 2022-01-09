#include "../../include/common.h"

void handleAutophase(void) {
	short _facing;
	if (AutoPhaseStateOn) {
		if (ControllerInput.Buttons & D_Up) {
			if (Player) {
				if (Player->facing_angle < 2048) {
					_facing = Player->facing_angle + 4096;
					Player->facing_angle = _facing;
					Player->next_facing_angle = _facing;
					Player->moving_angle = (Player->moving_angle + 4096) & 0x1FFF;
				}
			}
		}
	}
}