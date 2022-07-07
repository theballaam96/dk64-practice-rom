#include "../include/common.h"

#define actorCap 343

static forceSpawnActorData spawnActorData = {};
static char viewed_actor_name[30] = "";
static char actor_spawn[] = "SPAWN";

static const uniqueSpawnFunction uniqueFuncs[] = {
	{
		.actor_type = 0x13F,
		.func = 0x80690470
	},
	{
		.actor_type = 0xCA,
		.func = 0x806D2AA0
	},
	{
		.actor_type = 0xB3,
		.func = 0x80687474
	},
	{
		.actor_type = 0x140,
		.func = 0x806EFA3C
	},
	{
		.actor_type = 0x118,
		.func = 0x806AD9AC
	},
};

static const actorWrapperParams wrapperParams[] = {
	{
		.actor_type = 0x10A,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x5F,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x157,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x136,
		.actor_behaviour = 0xA8,
	},
	{
		.actor_type = 0xAD,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x108,
		.actor_behaviour = 0x1D,
	},
	{
		.actor_type = 0xB1,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xDE,
		.actor_behaviour = 0xE5,
	},
	{
		.actor_type = 0x9C,
		.actor_behaviour = 0x53,
	},
	{
		.actor_type = 0x13D,
		.actor_behaviour = 0xD2,
	},
	{
		.actor_type = 0x13C,
		.actor_behaviour = 0x4,
	},
	{
		.actor_type = 0xCF,
		.actor_behaviour = 0xAD,
	},
	{
		.actor_type = 0x109,
		.actor_behaviour = 0xC0,
	},
	{
		.actor_type = 0xA,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xB,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xC,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xD,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xE,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xF,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x107,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xE8,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x102,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x104,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x94,
		.actor_behaviour = 0xE1,
	},
	{
		.actor_type = 0xB0,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x156,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xED,
		.actor_behaviour = 0xC2,
	},
	{
		.actor_type = 0x73,
		.actor_behaviour = 0x7D,
	},
	{
		.actor_type = 0xD3,
		.actor_behaviour = 0x24,
	},
	{
		.actor_type = 0x14E,
		.actor_behaviour = 0xCD,
	},
	{
		.actor_type = 0xE1,
		.actor_behaviour = 0x98,
	},
	{
		.actor_type = 0x18,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x1D,
		.actor_behaviour = 0x82,
	},
	{
		.actor_type = 0x25,
		.actor_behaviour = 0x8C,
	},
	{
		.actor_type = 0x13E,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0xBC,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x146,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x14F,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x150,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x153,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x11A,
		.actor_behaviour = 0x21,
	},
	{
		.actor_type = 0xDA,
		.actor_behaviour = 0x94,
	},
	{
		.actor_type = 0x3C,
		.actor_behaviour = 0x98,
	},
	{
		.actor_type = 0x141,
		.actor_behaviour = 0x3D,
	},
	{
		.actor_type = 0x136,
		.actor_behaviour = 0xA8,
	},
	{
		.actor_type = 0x117,
		.actor_behaviour = 0xC5,
	},
	{
		.actor_type = 0xEF,
		.actor_behaviour = 0xA6,
	},
	{
		.actor_type = 0x12B,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x152,
		.actor_behaviour = 0,
	},
	{
		.actor_type = 0x92,
		.actor_behaviour = 0x73,
	},
};

void spawnNewCharSpawner(int enemyValue) {
	int count = SpawnerMasterData.count;
	SpawnerInfo* spawner = &SpawnerMasterData.array->SpawnerData[count];
	if (count < 255) {
		if (Player) {
			spawner->enemy_value = enemyValue;
			spawner->yRot = 0;
			spawner->xPos = (short)Player->xPos;
			spawner->yPos = (short)Player->yPos;
			spawner->zPos = (short)Player->zPos;
			spawner->max_idle_speed = 0x3C;
			spawner->max_aggro_speed = 0x60;
			spawner->scale = 50;
			spawner->init_spawn_state = 2;
			spawner->unk_11 = 0;
			spawner->spawn_trigger = count + 1;
			spawner->respawnTimerInit = 0; // Prevents respawn
			spawner->spawn_state = spawner->init_spawn_state;
			spawner->alt_enemy_value = spawner->enemy_value;
			spawner->tied_actor = 0;
			spawner->unk_46 = 0;
			spawner->respawn_timer = 0;
			spawner->counter = 0;
			spawner->unk_3C = 0;
			spawner->unk_20 = dk_malloc(spawner->unk_11 << 1);
			spawner->movement_box = (movementBoxInfo*)dk_malloc(0x30);
			if (spawner->movement_box) {
				spawner->movement_box->count = 1;
				spawner->movement_box->unk_ptr = (aggrBoxInfo*)dk_malloc(6 * 4);
			}
			spawner->chunk = Player->chunk;
			resolveMovementBox(&spawner);
			SpawnerMasterData.count += 1;
		}
	}
}

void forceSpawnActor(void) {
	int char_spawner_index = -1;
	unsigned int in_unique_functions = 0;
	int wrapper_actor = -1;
	int wrapper_behaviour = -1;
	for (int i = 0; i < 0x70; i++) {
		if (characterSpawnerActors[i].actor_type == spawnActorData.actor_type) {
			char_spawner_index = i;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (uniqueFuncs[i].actor_type == spawnActorData.actor_type) {
			in_unique_functions = uniqueFuncs[i].func;
		}
	}
	for (int i = 0; i < 50; i++) {
		if (wrapperParams[i].actor_type == spawnActorData.actor_type) {
			wrapper_actor = wrapperParams[i].actor_type;
			wrapper_behaviour = wrapperParams[i].actor_behaviour;
		}
	}
	if (char_spawner_index > -1) {
		spawnNewCharSpawner(char_spawner_index);
	} else if (in_unique_functions) {
		callFunc((int *)in_unique_functions);
	} else if (wrapper_actor > -1) {
		spawnActor(wrapper_actor,wrapper_behaviour);
	} else {
		transferredActorType = spawnActorData.actor_type;
		spawnTransferredActor();
		transferredActorType = 0;
	}
}

void openForceSpawnActorMenu(void) {
	if (ActorNamesTable == 0) {
		actorNames* copy_space = dk_malloc(0x1580);
		ActorNamesTable = copy_space;
		int* file_size;
		*(int*)(&file_size) = 0x1580;
		copyFromROM(ActorNamesStart,copy_space,&file_size,0,0,0,0);
	}
	if (ActorNamesTable) {
		dk_strFormat(viewed_actor_name,"ACTOR:%s",ActorNamesTable->actor_name[(int)spawnActorData.actor_type]);
	} else {
		dk_strFormat(viewed_actor_name,"ACTOR:0X%X",spawnActorData.actor_type);
	}
	changeMenu(ACTIVEMENU_SCREEN_DEBUG_SPAWNACTOR);
}

void toggleSelectedActor(void) {
	if (ActiveMenu.isOpen) {
		if (ActiveMenu.screenIndex == ACTIVEMENU_SCREEN_DEBUG_SPAWNACTOR) {
			if (ActiveMenu.positionIndex == 0) {
				if (NewlyPressedControllerInput.Buttons & D_Left) {
					if (spawnActorData.actor_type == 0) {
						spawnActorData.actor_type = actorCap;
					} else {
						spawnActorData.actor_type -= 1;
					}
					openForceSpawnActorMenu();
				} else if (NewlyPressedControllerInput.Buttons & D_Right) {
					spawnActorData.actor_type += 1;
					if (spawnActorData.actor_type > actorCap) {
						spawnActorData.actor_type = 0;
					}
					openForceSpawnActorMenu();
				}
			}
		}
	}
}

static const char* forcespawn_array[] = {
	viewed_actor_name,
	actor_spawn,
};

static const int forcespawn_functions[] = {
	0,
	(int)&forceSpawnActor,
};

const Screen forcespawn_struct = {
	.TextArray = (int*)forcespawn_array,
	.FunctionArray = forcespawn_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_DEBUG_ROOT,
	.ParentPosition = 4
};