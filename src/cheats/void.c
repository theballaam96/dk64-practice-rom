#include "../include/common.h"

void disableVoid(void) {
	if (voidsDisabled) {
		if (Player) {
			Player->voiding = 1;
		}
	}
}