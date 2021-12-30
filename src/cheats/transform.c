#include "../../include/common.h"

void openTransformMenu(void) {
	changeMenu(62);
}

void checkCrystals(void) {
	if (TransformAutoRestockOff == 0) {
	// 	if (CollectableBase.Crystals < 450) {
	// 		CollectableBase.Crystals = 3000;
	// 	}
		setHUDItemAsInfinite(5,0,1);
	}
}

void transformStrongKong(void) {
	if (Player) {
		Player->strong_kong_ostand_bitfield = Player->strong_kong_ostand_bitfield | 0x10;
		Player->obj_props_bitfield = Player->obj_props_bitfield & 0xFFFF7FFF;
		Player->strong_kong_value = 0x7F;
		checkCrystals();
	}
};

void transformRocketbarrel(void) {
	if (Player) {
		spawnRocketbarrel(Player,0);
		Player->unk_rocketbarrel_value1 = 0x31;
		Player->unk_rocketbarrel_value2 = -1;
		Player->unk_rocketbarrel_value3 = 1;
		Player->control_state = 99;
		Player->control_state_progress = 0;
		if (Player->grounded_bitfield & 1) {
			Player->yVelocity = 200;
			Player->yPos = Player->yPos + 10;
			Player->grounded_bitfield = 0;
			Player->unk_bitfield = 0;
		}
		Player->velocity_cap = 300;
		checkCrystals();
	}
};

void transformOrangstand(void) {
	if (Player) {
		Player->strong_kong_ostand_bitfield = Player->strong_kong_ostand_bitfield | 0x20;
		Player->control_state = 0x3F;
		Player->control_state_progress = 1;
		Player->ostand_value = 1;
		Player->grounded_bitfield = 0;
		Player->unk_bitfield = 0;
		checkCrystals();
	}
};

void transformSizeBarrels(int size) {
	if (Player) {
		alterSize(Player, size);
		if (Player->characterID == 6) {
			Player->obj_props_bitfield = Player->obj_props_bitfield & 0xFFFF7FFF;
		} else {
			Player->obj_props_bitfield = Player->obj_props_bitfield | 0x8000;
		}
		unkSizeFunction(Player);
		checkCrystals();
	}
};

void transformMiniMonkey(void) {
	transformSizeBarrels(0);
};

void transformHunkyChunky(void) {
	transformSizeBarrels(2);
};

static const char* transform_array[] = {
	"STRONG KONG",
	"ROCKETBARREL",
	"ORANGSTAND SPRINT",
	"MINI MONKEY",
	"HUNKY CHUNKY",
};

static const int transform_functions[] = {
	(int)&transformStrongKong,
	(int)&transformRocketbarrel,
	(int)&transformOrangstand,
	(int)&transformMiniMonkey,
	(int)&transformHunkyChunky,
};

const Screen transform_struct = {
	.TextArray = (int*)transform_array,
	.FunctionArray = transform_functions,
	.ArrayItems = 5,
	.ParentScreen = 55,
	.ParentPosition = 9
};