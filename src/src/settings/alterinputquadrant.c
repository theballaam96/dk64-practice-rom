#include "../../include/common.h"

static char quadrant_current_tl[] = "CURRENT: TOP LEFT";
static char quadrant_current_tr[] = "CURRENT: TOP RIGHT";
static char quadrant_current_bl[] = "CURRENT: BOTTOM LEFT";
static char quadrant_current_br[] = "CURRENT: BOTTOM RIGHT";

static char quadrant_setto_tl[] = "SET TO: TOP LEFT";
static char quadrant_setto_tr[] = "SET TO: TOP RIGHT";
static char quadrant_setto_bl[] = "SET TO: BOTTOM LEFT";
static char quadrant_setto_br[] = "SET TO: BOTTOM RIGHT";

static char* current_quadrants[] = {
	quadrant_current_tl,
	quadrant_current_tr,
	quadrant_current_bl,
	quadrant_current_br,
};

static char* quadrant_array[] = {
	quadrant_current_tl,
	quadrant_setto_tl,
	quadrant_setto_tr,
	quadrant_setto_bl,
	quadrant_setto_br,
};

void openInputQuadrantMenu(void) {
	quadrant_array[0] = current_quadrants[(int)InputDisplayQuadrant];
	changeMenu(59);
};

void changeInputQuadrant(void) {
	InputDisplayQuadrant = ActiveMenu.positionIndex - 1;
	saveSettings();
	openInputQuadrantMenu();
};

static const int quadrant_functions[] = {
	0,
	(int)&changeInputQuadrant,
	(int)&changeInputQuadrant,
	(int)&changeInputQuadrant,
	(int)&changeInputQuadrant,
};

const Screen quadrant_struct = {
	.TextArray = (int*)quadrant_array,
	.FunctionArray = quadrant_functions,
	.ArrayItems = 5,
	.ParentScreen = 57,
	.ParentPosition = 5
};