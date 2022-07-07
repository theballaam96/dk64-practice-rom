#include "../include/common.h"

static const int bbbchecks[4] = {
	0x80025EC0,
	0x80025EE0,
	0x80025F00,
	0x80025F20,
};

void endMinigame(void) {
	char _actorSearchOn = 0;
	unsigned short _actor;
	unsigned char _index;
	void* _actor_addr = 0;
	SpawnerArray* spawner_array;
	pppanicController* _pppanic_addr;
	krazykkcontroller* _krazykk_addr;
	bbbanditcontroller* _bbbandit_addr;
	bbbashcontroller* _bbbash_addr;
	kkoshcontroller* _kkosh_addr;
	sseekcontroller* _sseek_addr;
	actorData* _actor_formatted_addr;
	SpawnerInfo* focused_spawner;
	if (MinigameTimersInMS == 0) {
		switch(CurrentMap) {
			case 0x68: // BBother Easy
			case 0x88: // BBother Normal
			case 0x89: // BBother Hard
			case 0x0B: // SSnoop Normal No Logo
			case 0x41: // SSnoop Normal
			case 0x7E: // SSnoop V Easy
			case 0x7F: // SSnoop Easy
			case 0x80: // SSnoop Hard
			case 0x63: // SSSortie Easy
			case 0x86: // SSSortie Normal
			case 0x87: // SSSortie Hard
			case 0x60: // SSSalvage Normal
			case 0x84: // SSSalvage Hard
			case 0x85: // SSSalvage Easy
			case 0x23: // DK BBlast
			case 0xD4: // DK Rambi
			case 0xA5: // Diddy Kremling
			case 0xC9: // Diddy Rocketbarrel
			case 0x03: // Lanky Maze
			case 0xCA: // Lanky Zinger
			case 0x32: // Tiny Bounce
			case 0xD2: // Tiny Floor is lava
			case 0xD1: // Chunky ? Box
			case 0xD3: // Chunky Gun
			case 0x4E: // BBBarrage Easy
			case 0x4F: // BBBarrage Normal
			case 0x83: // BBBarrage Hard
			case 0x42: // MMMaul Hard
			case 0x44: // MMMaul Easy
			case 0x45: // MMMaul Normal
			case 0x7C: // MMMaul Insane
			case 0x43: // SSnatch Normal
			case 0x4A: // SSnatch Easy
			case 0x4B: // SSnatch Hard
			case 0x7D: // SSnatch Insane
				spawner_array = SpawnerMasterData.array;
				for (int i = 0; i < SpawnerMasterData.count; i++) {
					focused_spawner = getObjectArrayAddr(spawner_array,0x48,i);
					if (focused_spawner->enemy_value == 0x4C) {
						if (focused_spawner->tied_actor) {
							focused_spawner->respawnTimerInit = 4;
							MinigameController* minigame_controller = focused_spawner->tied_actor;
							minigame_controller->hit_count = 0;
						}
					}
				}
				break;
			case 0x90: // PPPanic V Easy
			case 0x91: // PPPanic Easy
			case 0x92: // PPPanic Normal
			case 0x93: // PPPanic Hard
				_actorSearchOn = 1;
				_actor = 124;
				_index = 1;
				break;
			case 0x65: // KrazyKK Easy
			case 0x8D: // KrazyKK Normal
			case 0x8E: // KrazyKK Hard
			case 0x8F: // KrazyKK Insane
				_actorSearchOn = 1;
				_actor = 125;
				_index = 2;
				break;
			case 0x20: // BBBandit V Easy
			case 0x79: // BBBandit Easy
			case 0x7A: // BBBandit Normal
			case 0x7B: // BBBandit Hard
				_actorSearchOn = 1;
				_actor = 218;
				_index = 3;
				break;
			case 0x66: // BBBash V Easy
			case 0x94: // BBBash Easy
			case 0x95: // BBBash Normal
			case 0x96: // BBBash Hard
				_actorSearchOn = 1;
				_actor = 126;
				_index = 4;
				break;
			case 0x0A: // KKosh V Easy
			case 0x73: // KKosh Easy
			case 0x74: // KKosh Normal
			case 0x75: // KKosh Hard
				_actorSearchOn = 1;
				_actor = 34;
				_index = 5;
				break;
			case 0x67: // SSeek V Easy
			case 0x8A: // SSeek Easy
			case 0x8B: // SSeek Normal
			case 0x8C: // SSeek Hard
				_actorSearchOn = 1;
				_actor = 127;
				_index = 6;
				break;
			case 0xB1: // Dive Barrel
			case 0xB4: // Orange Barrel
			case 0xB5: // Barrel Barrel
			case 0xB6: // Vine Barrel
				_actorSearchOn = 1;
				_actor = 336;
				_index = 7;
				break;
			case 0x4D: // MMayhem Easy
			case 0x81: // MMayhem Normal
			case 0x82: // MMayhem Hard
			case 0x12: // TTTrouble V Easy
			case 0x76: // TTTrouble Easy
			case 0x77: // TTTrouble Normal
			case 0x78: // TTTrouble Hard
				_actorSearchOn = 1;
				_actor = 176;
				_index = 8;
			break;
		};
		if (_actorSearchOn) {
			_actor_addr = findActorWithType(_actor);
			if (_actor_addr) {
				switch(_index) {
					case 1:
						_pppanic_addr = (pppanicController*) _actor_addr;
						_pppanic_addr->hit_count1 = 0;
						_pppanic_addr->hit_count2 = 0;
						break;
					case 2:
						_krazykk_addr = (krazykkcontroller*)_actor_addr;
						_krazykk_addr->hit_count1 = 0;
						_krazykk_addr->hit_count2 = 0;
						break;
					case 3:
						_bbbandit_addr = (bbbanditcontroller*)_actor_addr;
						if (_bbbandit_addr->slot_pointer) {
							_bbbandit_addr->control_state = 7;
							_bbbandit_addr->handle_pointer->hit_count = 1;
							_bbbandit_addr->slot_pointer->control_state = 0;
							for (int i = 0; i < 4; i++) {
								*(int *)bbbchecks[i] = 0;
							}
						}
						break;
					case 4:
						_bbbash_addr = (bbbashcontroller*)_actor_addr;
						_bbbash_addr->hit_count = 0;
						break;
					case 5:
						_kkosh_addr = (kkoshcontroller*)_actor_addr;
						_kkosh_addr->hit_count = 0;
						break;
					case 6:
						_sseek_addr = (sseekcontroller*)_actor_addr;
						_sseek_addr->hit_count = 0;
						break;
					case 7:
						_actor_formatted_addr = (actorData*)_actor_addr;
						if (CutsceneActive == 0) {
							_actor_formatted_addr->control_state = 3;
						}
						break;
					case 8:
						_actor_formatted_addr = (actorData*)_actor_addr;
						_actor_formatted_addr->control_state = 5;
					break;
				}
			}
		}
	}
};

void LToEndMinigame(void) {
	if (LToEndGameOn) {
		if (ActiveMenu.isOpen == 0) {
			if (ClosingMenu == 0) {
				if (NewlyPressedControllerInput.Buttons & L_Button) {
					endMinigame();
				}
			}
		}
	}
};