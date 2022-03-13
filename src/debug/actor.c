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
static const char detailsscreen_collisions[15] = "COLLISIONS:0";
static const char detailsscreen_lastcollision[50] = "LAST COLLISION: 0";
static const char detailsscreen_grab[] = "GRAB ACTOR";
static const char detailsscreen_warp[] = "WARP TO ACTOR";
static const char detailsscreen_memory[] = "VIEW IN MEMORY";
static const char detailsscreen_focus[] = "FOCUS ON ACTOR";

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
	.ParentScreen = ACTIVEMENU_SCREEN_DEBUG_ROOT,
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
	detailsscreen_collisions,
	detailsscreen_lastcollision,
	detailsscreen_grab,
	detailsscreen_warp,
	detailsscreen_memory,
	detailsscreen_focus,
};

void openActorMenu(void) {
	if (ActorNamesTable == 0) {
		actorNames* copy_space = dk_malloc(0x1580);
		ActorNamesTable = copy_space;
		int* file_size;
		*(int*)(&file_size) = 0x1580;
		copyFromROM(ActorNamesStart,copy_space,&file_size,0,0,0,0);
	}
	if (ActiveMenu.screenIndex != ACTIVEMENU_SCREEN_DEBUG_ACTORLIST) {
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
	
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_ACTORLIST);
};

void shouldRefreshTOMenu(void) {
	if (ActiveMenu.isOpen) {
		if (ActiveMenu.screenIndex == ACTIVEMENU_SCREEN_DEBUG_ACTORLIST) {
			if (LoadedActorCount != previousNoTOCount) {
				if (LoadedActorCount < (startingActorIndex + 1)) {
					startingActorIndex = LoadedActorCount - (LoadedActorCount % 10);
				}
				openActorMenu();
			}
		}
	}
}

static void* lastActorRecording = 0;
static unsigned int lastHeader = 0;
static unsigned short lastActorType = 0;

void updateActorInfo(actorData* actor) {
	if (isAddressActor(actor)) {
		dk_strFormat((char *)detailsscreen_x,"X:%f",actor->xPos);
		dk_strFormat((char *)detailsscreen_y,"Y:%f",actor->yPos);
		dk_strFormat((char *)detailsscreen_z,"Z:%f",actor->zPos);
		unsigned int collision_count = 0;
		collision_struct* collision = actor->collision_queue_pointer;
		if (lastActorRecording != actor) {
			lastActorRecording = 0;
			dk_strFormat((char*)detailsscreen_lastcollision,"LAST COL:NONE");
		}
		if (collision) {
			lastActorRecording = actor;
			lastHeader = collision->header;
			actorData* collision_target = collision->targetActor;
			if (collision_target) {
				lastActorType = collision_target->actorType;
			} else {
				lastActorType = 0;
			}
			while (collision) {
				collision_count += 1;
				if (collision->next_collision == 0) {
					break;
				} else {
					lastHeader = collision->header;
					collision_target = collision->targetActor;
					if (collision_target) {
						lastActorType = collision_target->actorType;
					} else {
						lastActorType = 0;
					}
				}
				collision = collision->next_collision;
			}
		}
		if (lastActorRecording) {
			dk_strFormat((char*)detailsscreen_lastcollision,"LAST COL:%s<0X%X>",ActorNamesTable->actor_name[lastActorType],lastHeader);
		}
		dk_strFormat((char *)detailsscreen_collisions,"COLLISIONS:%d",collision_count);
	}
}

void updateActorScreen(void) {
	if (FocusedActorViewPointer) {
		updateActorInfo((actorData*)FocusedActorViewPointer);
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
	updateActorInfo((actorData*)LoadedActorArray[index].actor);
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_ACTORDETAILS);
}

#define ACTOR_FILTER_VALID_POINTER 1
#define ACTOR_FILTER_IS_ACTOR 2
#define ACTOR_FILTER_IS_SAFE 4

int filterActor(int play_error) {
	int ret = 0;
	if (FocusedActorViewPointer) {
		ret |= ACTOR_FILTER_VALID_POINTER;
		if (isAddressActor(FocusedActorViewPointer)) {
			ret |= ACTOR_FILTER_IS_ACTOR;
			int actor_type = FocusedActorViewPointer->actorType;
			int actor_master_type = ActorMasterType[actor_type];
			if (((actor_master_type == ACTOR_MASTER_TYPE_3D) || (actor_master_type == ACTOR_MASTER_TYPE_2D)) && (actor_type != 0xBC)) {
				ret |= ACTOR_FILTER_IS_SAFE;
			} else if (play_error) {
				playSFX(Wrong);
			}
		}
	}
	return ret;
}

void grabViewedActor(void) {
	int state = filterActor(1);
	if (state & ACTOR_FILTER_IS_SAFE) {
		if (Player) {
			Player->held_actor = FocusedActorViewPointer;
		}
	} else if ((state & ACTOR_FILTER_IS_ACTOR) == 0) {
		openActorMenu();
	}
}

void focusViewedActor(void) {
	int state = filterActor(1);
	if (state & ACTOR_FILTER_IS_SAFE) {
		if (Camera) {
			Camera->focused_actor_pointer = FocusedActorViewPointer;
		}
	} else if ((state & ACTOR_FILTER_IS_ACTOR) == 0) {
		openActorMenu();
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
	int state = filterActor(1);
	if (state & ACTOR_FILTER_IS_SAFE) {
		if (Player) {
			Player->xPos = FocusedActorViewPointer->xPos;
			Player->yPos = FocusedActorViewPointer->yPos;
			Player->zPos = FocusedActorViewPointer->zPos;
			Player->touching_object = 0;
			Player->collision_queue_pointer = 0;
		}
	} else if ((state & ACTOR_FILTER_IS_ACTOR) == 0) {
		openActorMenu();
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

static const char detailsscreen_access[] = {
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Address
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Name
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Type
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Size
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // X
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Y
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Z
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Collisions
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Last Collision
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Grab Actor
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Warp to Actor
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_EMU, // View in Memory
	ACCESS_US | ACCESS_PAL | ACCESS_JP | ACCESS_N64 | ACCESS_WIIU | ACCESS_EMU, // Focus on Actor
};

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
	0,
	0,
	(int)&grabViewedActor,
	(int)&warpToActor,
	(int)&openActorRAM,
	(int)&focusViewedActor,
};

const Screen detailsscreen_struct = {
	.TextArray = (int*)detailsscreen_array,
	.FunctionArray = detailsscreen_functions,
	.ArrayItems = 13,
	.ParentScreen = ACTIVEMENU_SCREEN_DEBUG_ACTORLIST,
	.ParentPosition = 0,
	.hasAccessArray = 1,
	.AccessArray = detailsscreen_access
};