#include "../include/common.h"

void recolorKlaptrap(void) {
	actorData* klaptrap = findActorWithType(0x11A);
	if (klaptrap != 0) {
		if (klaptrap->control_state == 0) {
			klaptrap->obj_props_bitfield &= 0xFF7FFFFF;
		} else {
			klaptrap->obj_props_bitfield |= 0x00800000;
			klaptrap->red = 0xFF;
			klaptrap->green = 0;
			klaptrap->blue = 0;
		}
	}
}

#define DOUBLEBEAVER_BARK 0x01
#define DOUBLEBEAVER_SCARE 0x02
#define DOUBLEBEAVER_RANGECOLOR 0x04
#define DOUBLEBEAVER_DROPINDICATOR 0x08
#define DOUBLEBEAVER_SUCCESSDING 0x10

void recolorBeavers(void) {
	beaverData* beaver = 0;
	for (int i = 0; i < LoadedActorCount; i++) {
		beaver = (beaverData*)LoadedActorArray[i].actor;
		if (beaver->main.actorType == 178) {
			int scared = 0;
			int in_range = 0;
			if (beaver->scare_bitfield & 0x8000) {
				scared = 1;
			}
			if (doubleBeaverEnabledBitfield & DOUBLEBEAVER_RANGECOLOR) {
				if (Player) {
					int dx = Player->xPos - beaver->main.xPos;
					int dz = Player->zPos - beaver->main.zPos;
					int dist2 = (dx * dx) + (dz * dz);
					if (dist2 < 1600) {
						in_range = 1;
					}
				}
			}
			scared &= ((doubleBeaverEnabledBitfield & DOUBLEBEAVER_SCARE) != 0);
			in_range &= ((doubleBeaverEnabledBitfield & DOUBLEBEAVER_RANGECOLOR) != 0);
			if (scared || in_range) {
				beaver->main.obj_props_bitfield |= 0x00800000;
				if (scared) {
					beaver->main.red = 0xFF;
					beaver->main.green = 0;
					if (in_range) {
						beaver->main.blue = 0xFF;
					} else {
						beaver->main.blue = 0;
					}
				} else {
					beaver->main.red = 0;
					beaver->main.green = 0xFF;
					beaver->main.blue = 0;
				}
			} else {
				beaver->main.obj_props_bitfield &= 0xFF7FFFFF;
			}
		}
	}
}
void playBeaverSuccessDing(void) {
	if (doubleBeaverEnabledBitfield & DOUBLEBEAVER_SUCCESSDING) {
		playSFX(Bell);
	}
}

void controlDoubleBeaver(void) {
	if (doubleBeaverEnabledBitfield & DOUBLEBEAVER_BARK) {
		recolorKlaptrap();
	}
	if (doubleBeaverEnabledBitfield & (DOUBLEBEAVER_SCARE | DOUBLEBEAVER_RANGECOLOR)) {
		recolorBeavers();
	}
}

int* displayDropCircle(int* dl) {
	if (doubleBeaverEnabledBitfield & DOUBLEBEAVER_DROPINDICATOR) {
		beaverData* beaver = 0;
		for (int i = 0; i < LoadedActorCount; i++) {
			beaver = (beaverData*)LoadedActorArray[i].actor;
			if (beaver->main.actorType == 178) {
				if (beaver->main.control_state == 0x40) {
					if (beaver->main.yPos < 0) {
						int x_pos[4] = {};
						int z_pos[4] = {};
						int max_screen_x = 0;
						int max_screen_y = 0;
						int min_screen_x = 0;
						int min_screen_y = 0;
						float x_store = 0;
						float y_store = 0;
						int bx = beaver->main.xPos;
						int bz = beaver->main.zPos;
						x_pos[0] = bx - 40;
						x_pos[1] = bx;
						x_pos[2] = bx;
						x_pos[3] = bx + 40;
						z_pos[0] = bz;
						z_pos[1] = bz - 40;
						z_pos[2] = bz + 40;
						z_pos[3] = bz;
						int pass = 1;
						for (int j = 0; j < 4; j++) {
							if (pass) {
								getScreenPosition(x_pos[j],0,z_pos[j],(float*)&x_store, (float*)&y_store,0,1.0f,0);
								if ((x_store != 0x4000) && (y_store != 0x4000)) {
									if (j == 0) {
										min_screen_x = x_store;
									} else if (j == 1) {
										min_screen_y = y_store;
									} else if (j == 2) {
										max_screen_y = y_store;
									} else if (j == 3) {
										max_screen_x = x_store;
									}
								} else {
									pass = 0;
								}
							}
						}
						if (pass) {
							float xScale = (max_screen_x - min_screen_x) * 0.1f;
							float yScale = (max_screen_y - min_screen_y) * 0.1f;
							int x = (min_screen_x * 4) + 150;
							int y = (min_screen_y * 4) + 150;
							dl = drawImage(dl, IMAGE_CIRCLE, RGBA16, 32, 32, x, y, xScale, yScale, 0x80);
						}
					}	
				}
			}
		}
	}
	return dl;
}

static char* beaver_true[] = {
	"} BARK INDICATOR",
	"} SCARED INDICATOR",
	"} RANGE INDICATOR",
	"} TIMING INDICATOR",
	"} SUCCESS INDICATOR"
};

static char* beaver_false[] = {
	"{ BARK INDICATOR",
	"{ SCARED INDICATOR",
	"{ RANGE INDICATOR",
	"{ TIMING INDICATOR",
	"{ SUCCESS INDICATOR"
};

static char* beaver_array[] = {
	0,
	0,
	0,
	0,
	0,
	"TURN OFF ALL",
};

void openBeaverBotherMenu(void) {
	for (int i = 0; i < 5; i++) {
		if (doubleBeaverEnabledBitfield & (1 << i)) {
			beaver_array[i] = beaver_true[i];
		} else {
			beaver_array[i] = beaver_false[i];
		}
	}
	changeMenu(ACTIVEMENU_SCREEN_WATCH_DOUBLEBEAVER);
}

void toggleBeaverBotherIndicator(void) {
	int shift = 1 << ActiveMenu.positionIndex;
	if (doubleBeaverEnabledBitfield & shift) {
		doubleBeaverEnabledBitfield &= (-1 - shift);
	} else {
		doubleBeaverEnabledBitfield |= shift;
	}
	openBeaverBotherMenu();
}

void beaverBotherTurnOff(void) {
	doubleBeaverEnabledBitfield = 0;
	openBeaverBotherMenu();
}

static const int beaver_functions[] = {
	(int)&toggleBeaverBotherIndicator,
	(int)&toggleBeaverBotherIndicator,
	(int)&toggleBeaverBotherIndicator,
	(int)&toggleBeaverBotherIndicator,
	(int)&toggleBeaverBotherIndicator,
	(int)&beaverBotherTurnOff,
};

const Screen beaver_struct = {
	.TextArray = (int*)beaver_array,
	.FunctionArray = beaver_functions,
	.ArrayItems = 6,
	.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
	.ParentPosition = 7,
};