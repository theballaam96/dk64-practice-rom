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
static const char actorscreen_viewprev[] = "< Actors";
static const char actorscreen_viewmore[] = "Actors >";

static const char detailsscreen_addr[20] = "Address: 0x0";
static const char detailsscreen_typename[25] = "Name: 0";
static const char detailsscreen_typehex[10] = "Type: 0x0";
static const char detailsscreen_delete[] = "Delete Actor";
static const char detailsscreen_grab[] = "Grab Actor";

static char startingActorIndex = 0;

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
	detailsscreen_delete,
	detailsscreen_grab,
};


void openActorMenu(void) {
	if (ActiveMenu.screenIndex != 77) {
		startingActorIndex = 0;
	}
	int actorAddr = 0;
	int loaded_shown = LoadedActorCount - startingActorIndex;
	int shown_items = loaded_shown;
	if (loaded_shown > 10) {
		loaded_shown = 10;
		shown_items = 11;
	}
	if (startingActorIndex > 0) {
		shown_items += 1;
	}
	for (int i = 0; i < loaded_shown; i++) {
		actorAddr = (int)LoadedActorArray[i + startingActorIndex].actor;
		int actorType = LoadedActorArray[i + startingActorIndex].actor->actorType;
		if (ActorNamesTable) {
			dk_strFormat((char *)actorscreen_viewed[i],"%2d: 0x%4X: %s",i + startingActorIndex,actorAddr, ActorNamesTable->actor_name[actorType]);
		} else {
			dk_strFormat((char *)actorscreen_viewed[i],"%2d: 0x%4X: %d",i + startingActorIndex,actorAddr, actorType);
		}
		actor_array[i] = actorscreen_viewed[i];
	}
	actor_struct.ArrayItems = shown_items;
	shown_items = loaded_shown;
	if ((LoadedActorCount - startingActorIndex) > 10) {
		actor_array[shown_items] = actorscreen_viewmore;
		shown_items += 1;
	}
	if (startingActorIndex > 0) {
		actor_array[shown_items] = actorscreen_viewprev;
	}
	
	changeMenu(77);
};

void deleteViewedActor(void) {
	if (FocusedActorViewPointer) {
		if (isAddressActor(FocusedActorViewPointer)) {
			deleteActor(FocusedActorViewPointer);
		}
	}
}

void grabViewedActor(void) {
	if (FocusedActorViewPointer) {
		if (isAddressActor(FocusedActorViewPointer)) {
			if (Player) {
				Player->held_actor = FocusedActorViewPointer;
			}
		}
	}
}

void viewActorInfo(int index) {
	int actorAddr = 0;
	actorAddr = (int)LoadedActorArray[index].actor;
	FocusedActorViewPointer = LoadedActorArray[index].actor;
	int actorType = LoadedActorArray[index].actor->actorType;
	dk_strFormat((char *)detailsscreen_addr,"Address: 0x%4X",actorAddr);
	dk_strFormat((char *)detailsscreen_typename,"Name: %s",ActorNamesTable->actor_name[actorType]);
	dk_strFormat((char *)detailsscreen_typehex,"Type: 0x%X",actorType);
	changeMenu(78);
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
	int actor_screen_count = LoadedActorCount - startingActorIndex;
	if ((LoadedActorCount - startingActorIndex) > 10) {
		actor_screen_count = 10;
	}
	if (ActiveMenu.positionIndex < actor_screen_count) {
		viewActorInfo(startingActorIndex + ActiveMenu.positionIndex);
	} else {
		if (ActiveMenu.positionIndex == actor_screen_count) {
			if (LoadedActorCount > 10) {
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
	(int)&deleteViewedActor,
	(int)&grabViewedActor,
};

const Screen detailsscreen_struct = {
	.TextArray = (int*)detailsscreen_array,
	.FunctionArray = detailsscreen_functions,
	.ArrayItems = 5,
	.ParentScreen = 77,
	.ParentPosition = 0
};