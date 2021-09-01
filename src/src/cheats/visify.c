#include "../../include/common.h"

void toggleVisify(void) {
	if (Player) {
		if (Player->obj_props_bitfield & 0x4) {
			Player->obj_props_bitfield = Player->obj_props_bitfield & 0xBFFFFFFB;
		} else {
			Player->obj_props_bitfield = Player->obj_props_bitfield | 0x40000004;
		}
	}
}