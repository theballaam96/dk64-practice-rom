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
static const char actorscreen_viewprev[] = "< PREV";
static const char actorscreen_viewmore[] = "NEXT >";

static const char detailsscreen_addr[20] = "ADDRESS:0X0";
static const char detailsscreen_typename[25] = "NAME:0";
static const char detailsscreen_typehex[15] = "TYPE:0X0";
static const char detailsscreen_sizehex[15] = "SIZE:0X0";
static const char detailsscreen_x[15] = "X:0";
static const char detailsscreen_y[15] = "Y:0";
static const char detailsscreen_z[15] = "Z:0";
static const char detailsscreen_grab[] = "GRAB ACTOR";
static const char detailsscreen_warp[] = "WARP TO ACTOR";
static const char detailsscreen_memory[] = "VIEW IN MEMORY";

static char startingActorIndex = 0;
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
	detailsscreen_memory,
};

void openActorMenu(void) {
	if (ActorNamesTable == 0) {
		actorNames* copy_space = dk_malloc(0x1580);
		ActorNamesTable = copy_space;
		int* file_size;
		*(int*)(&file_size) = 0x1580;
		copyFromROM(0x2020000,copy_space,&file_size,0,0,0,0);
	}
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
			dk_strFormat((char *)actorscreen_viewed[i],"%2d:0X%4X:%s",i + startingActorIndex,actorAddr, ActorNamesTable->actor_name[actorType]);
		} else {
			dk_strFormat((char *)actorscreen_viewed[i],"%2d:0X%4X:%d",i + startingActorIndex,actorAddr, actorType);
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

void shouldRefreshTOMenu(void) {
	if (ActiveMenu.isOpen) {
		if (ActiveMenu.screenIndex == 77) {
			if (LoadedActorCount != previousNoTOCount) {
				if (LoadedActorCount < (startingActorIndex + 1)) {
					startingActorIndex = LoadedActorCount - (LoadedActorCount % 10);
				}
				openActorMenu();
			}
		}
	}
}

void viewActorInfo(int index) {
	int actorAddr = 0;
	actorAddr = (int)LoadedActorArray[index].actor;
	FocusedActorViewPointer = LoadedActorArray[index].actor;
	int actorType = LoadedActorArray[index].actor->actorType;
	dk_strFormat((char *)detailsscreen_addr,"ADDRESS:0X%4X",actorAddr);
	dk_strFormat((char *)detailsscreen_typename,"NAME:%s",ActorNamesTable->actor_name[actorType]);
	dk_strFormat((char *)detailsscreen_typehex,"TYPE:0X%X",actorType);
	dk_strFormat((char *)detailsscreen_sizehex,"SIZE:0X%X",*(int*)(actorAddr - 0xC));
	dk_strFormat((char *)detailsscreen_x,"X:%f",LoadedActorArray[index].actor->xPos);
	dk_strFormat((char *)detailsscreen_y,"Y:%f",LoadedActorArray[index].actor->yPos);
	dk_strFormat((char *)detailsscreen_z,"Z:%f",LoadedActorArray[index].actor->zPos);
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

void openActorRAM(void) {
	if (assignedConsole != WIIU) {
		int actor_addr = (int)FocusedActorViewPointer;
		int actor_size = (int)*(int*)(actor_addr - 0xC);
		defineRAMViewerParameters((int*)actor_addr,(int*)(actor_addr + actor_size),1);
		startRamViewerDisplay();
	} else {
		playSFX(Wrong);
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
	int actor_screen_count = LoadedActorCount - startingActorIndex;
	if (actor_screen_count > 10) {
		actor_screen_count = 10;
	}
	if (ActiveMenu.positionIndex < actor_screen_count) {
		viewActorInfo(startingActorIndex + ActiveMenu.positionIndex);
	} else {
		if (ActiveMenu.positionIndex == actor_screen_count) {
			if ((LoadedActorCount - startingActorIndex) > 10) {
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
	(int)&openActorRAM,
};

const Screen detailsscreen_struct = {
	.TextArray = (int*)detailsscreen_array,
	.FunctionArray = detailsscreen_functions,
	.ArrayItems = 10,
	.ParentScreen = 77,
	.ParentPosition = 0
};