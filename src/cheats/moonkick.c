#include "../../include/common.h"

void handleAutomoonkick(void) {
	if (AutoMoonkickOn) {
		if (Character == 0) {
			if (Player) {
				if (Player->control_state == 0x29) {
					Player->yAccel = -2.5;
				}
			}
		}
	}
}