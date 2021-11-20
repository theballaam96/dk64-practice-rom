#include "../../include/common.h"

void levitate(void) {
	float increment;
	if (LToLevitateOn) {
		if ((TBVoidByte & 2) == 0) {
			if (ActiveMenu.isOpen == 0) {
				if (ControllerInput.Buttons & L_Button) {
					if (Player) {
						increment = 10;
						if (ControllerInput.Buttons & Z_Button) {
							increment = 5;
						} else {
							if (ControllerInput.Buttons & R_Button) {
								increment = 20;
							}
						}
						Player->yPos = Player->yPos + increment;
						Player->yVelocity = 0;
						Player->touching_object = 0;
						Player->collision_queue_pointer = 0;
					}
				}
			}
		}
	}
}