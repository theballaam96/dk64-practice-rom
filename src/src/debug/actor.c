#include "../../include/common.h"

static const char actorscreen_view0[40] = "";
static const char actorscreen_view1[40] = "";
static const char actorscreen_view2[40] = "";
static const char actorscreen_view3[40] = "";
static const char actorscreen_view4[40] = "";
static const char actorscreen_view5[40] = "";
static const char actorscreen_view6[40] = "";
static const char actorscreen_view7[40] = "";
static const char actorscreen_view8[40] = "";
static const char actorscreen_view9[40] = "";
static const char actorscreen_viewprev[] = "< Prev";
static const char actorscreen_viewmore[] = "Next >";

static const char detailsscreen_addr[20] = "Address: 0x0";
static const char detailsscreen_typename[25] = "Name: 0";
static const char detailsscreen_typehex[15] = "Type: 0x0";
static const char detailsscreen_sizehex[15] = "Size: 0x0";
static const char detailsscreen_x[15] = "X: 0";
static const char detailsscreen_y[15] = "Y: 0";
static const char detailsscreen_z[15] = "Z: 0";
static const char detailsscreen_grab[] = "Grab Actor";
static const char detailsscreen_warp[] = "Warp to Actor";

static char startingActorIndex = 0;

static actorData* loadedActorsNoTextOverlays[64];
static int loadedActorNoTOCount = 0;
static int previousNoTOCount = 0;

static const char* actorscreen_viewed[10] = {
	actorscreen_view0,
	actorscreen_view1,
	actorscreen_view2,
	actorscreen_view3,
	actorscreen_view4,
	actorscreen_view5,
	actorscreen_view6,
	actorscreen_view7,
	actorscreen_view8,
	actorscreen_view9,
};

static const char* actor_array[] = {
	actorscreen_view0,
	actorscreen_view1,
	actorscreen_view2,
	actorscreen_view3,
	actorscreen_view4,
	actorscreen_view5,
	actorscreen_view6,
	actorscreen_view7,
	actorscreen_view8,
	actorscreen_view9,
	actorscreen_viewprev,
	actorscreen_viewmore,
};

static const int actor_functions[12];

Screen actor_struct = {
	.TextArray = (int*)actor_array,
	.FunctionArray = actor_functions,
	.ArrayItems = 12,
	.ParentScreen = 76,
	.ParentPosition = 0
};

static const char* detailsscreen_array[] = {
	detailsscreen_addr,
	detailsscreen_typename,
	detailsscreen_typehex,
	detailsscreen_sizehex,
	detailsscreen_x,
	detailsscreen_y,
	detailsscreen_z,
	detailsscreen_grab,
	detailsscreen_warp,
};

void updateLoadedActorNoTextOverlayList(int callType) { // callType: 0 = every frame, checks screen Index. 1 = From openactormenu.
	if (ActiveMenu.isOpen) {
		if ((callType) || (ActiveMenu.screenIndex == 77) || (ActiveMenu.screenIndex == 78)) {
			previousNoTOCount = loadedActorNoTOCount;
			for (int i = 0; i < 64; i++) {
				loadedActorsNoTextOverlays[i] = 0;
			}
			int no_to_running_count = 0;
			for (int i = 0; i < LoadedActorCount; i++) {
				if (LoadedActorArray[i].actor->actorType != 0xE8) { // Not Text Overlay
					loadedActorsNoTextOverlays[no_to_running_count] = LoadedActorArray[i].actor;
					no_to_running_count += 1;
				}
			}
			loadedActorNoTOCount = no_to_running_count;
		}
	}
}

void openActorMenu(void) {
	updateLoadedActorNoTextOverlayList(1);
	if (ActiveMenu.screenIndex != 77) {
		startingActorIndex = 0;
	}
	int actorAddr = 0;
	int loaded_shown = loadedActorNoTOCount - startingActorIndex;
	int shown_items = loaded_shown;
	if (loaded_shown > 10) {
		loaded_shown = 10;
		shown_items = 11;
	}
	if (startingActorIndex > 0) {
		shown_items += 1;
	}
	for (int i = 0; i < loaded_shown; i++) {
		actorAddr = (int)loadedActorsNoTextOverlays[i + startingActorIndex];
		int actorType = loadedActorsNoTextOverlays[i + startingActorIndex]->actorType;
		if (ActorNamesTable) {
			dk_strFormat((char *)actorscreen_viewed[i],"%2d: 0x%4X: %s",i + startingActorIndex,actorAddr, ActorNamesTable->actor_name[actorType]);
		} else {
			dk_strFormat((char *)actorscreen_viewed[i],"%2d: 0x%4X: %d",i + startingActorIndex,actorAddr, actorType);
		}
		actor_array[i] = actorscreen_viewed[i];
	}
	actor_struct.ArrayItems = shown_items;
	shown_items = loaded_shown;
	if ((loadedActorNoTOCount - startingActorIndex) > 10) {
		actor_array[shown_items] = actorscreen_viewmore;
		shown_items += 1;
	}
	if (startingActorIndex > 0) {
		actor_array[shown_items] = actorscreen_viewprev;
	}
	
	changeMenu(77);
};

void shouldRefreshTOMenu(void) {
	if (ActiveMenu.isOpen) {
		if (ActiveMenu.screenIndex == 77) {
			if (loadedActorNoTOCount != previousNoTOCount) {
				if (loadedActorNoTOCount < (startingActorIndex + 1)) {
					startingActorIndex = loadedActorNoTOCount - (loadedActorNoTOCount % 10);
				}
				openActorMenu();
			}
		}
	}
}

void viewActorInfo(int index) {
	int actorAddr = 0;
	actorAddr = (int)loadedActorsNoTextOverlays[index];
	FocusedActorViewPointer = loadedActorsNoTextOverlays[index];
	int actorType = loadedActorsNoTextOverlays[index]->actorType;
	dk_strFormat((char *)detailsscreen_addr,"Address: 0x%4X",actorAddr);
	dk_strFormat((char *)detailsscreen_typename,"Name: %s",ActorNamesTable->actor_name[actorType]);
	dk_strFormat((char *)detailsscreen_typehex,"Type: 0x%X",actorType);
	dk_strFormat((char *)detailsscreen_sizehex,"Size: 0x%X",*(int*)(actorAddr - 0xC));
	dk_strFormat((char *)detailsscreen_x,"X: %f",loadedActorsNoTextOverlays[index]->xPos);
	dk_strFormat((char *)detailsscreen_y,"Y: %f",loadedActorsNoTextOverlays[index]->yPos);
	dk_strFormat((char *)detailsscreen_z,"Z: %f",loadedActorsNoTextOverlays[index]->zPos);
	changeMenu(78);
}

void grabViewedActor(void) {
	if (FocusedActorViewPointer) {
		if (isAddressActor(FocusedActorViewPointer)) {
			if (Player) {
				Player->held_actor = FocusedActorViewPointer;
			}
		} else {
			openActorMenu();
		}
	}
}

void warpToActor(void) {
	if (FocusedActorViewPointer) {
		if (isAddressActor(FocusedActorViewPointer)) {
			if (Player) {
				Player->xPos = FocusedActorViewPointer->xPos;
				Player->yPos = FocusedActorViewPointer->yPos;
				Player->zPos = FocusedActorViewPointer->zPos;
				Player->touching_object = 0;
				Player->collision_queue_pointer = 0;
			}
		} else {
			openActorMenu();
		}
	}
}

void incrementActorIndexShown(void) {
	startingActorIndex += 10;
	openActorMenu();
	ActiveMenu.positionIndex = 0;
}

void decrementActorIndexShown(void) {
	startingActorIndex -= 10;
	openActorMenu();
	ActiveMenu.positionIndex = 0;
}

void handleActorOption(void) {
	int actor_screen_count = loadedActorNoTOCount - startingActorIndex;
	if (actor_screen_count > 10) {
		actor_screen_count = 10;
	}
	if (ActiveMenu.positionIndex < actor_screen_count) {
		viewActorInfo(startingActorIndex + ActiveMenu.positionIndex);
	} else {
		if (ActiveMenu.positionIndex == actor_screen_count) {
			if ((loadedActorNoTOCount - startingActorIndex) > 10) {
				incrementActorIndexShown();
			} else {
				decrementActorIndexShown();
			}
		} else {
			decrementActorIndexShown();
		}
	}
}

static const int actor_functions[] = {
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
	(int)&handleActorOption,
};

static const int detailsscreen_functions[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	(int)&grabViewedActor,
	(int)&warpToActor,
};

const Screen detailsscreen_struct = {
	.TextArray = (int*)detailsscreen_array,
	.FunctionArray = detailsscreen_functions,
	.ArrayItems = 9,
	.ParentScreen = 77,
	.ParentPosition = 0
};