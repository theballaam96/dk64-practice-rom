#include "../include/common.h"

void alterSkewAngle(void) {
	if (Player) {
		short _skew = Player->skew_angle;
		if (_skew == 0xC00) {
			Player->skew_angle = 0x400;
		} else {
			Player->skew_angle = 0xC00;
		}
	}
	openCheatsMenu();
}