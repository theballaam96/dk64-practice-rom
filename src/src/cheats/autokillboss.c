#include "../../include/common.h"

void killBoss(void) {
	actorData* _actor;
	switch(CurrentMap) {
		case 0x8:
			// AD1
			_actor = findActorWithType(185);
			if (_actor) {
				playCutscene(_actor,7,0);
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xC5:
			// Dog 1
			_actor = findActorWithType(236);
			if (_actor) {
				playCutscene(0,2,1);
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0x9A:
			// MJ
			_actor = findActorWithType(204);
			if (_actor) {
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0x6F:
			// Pufftoss
			_actor = findActorWithType(216);
			if (_actor) {
				_actor->control_state = 0x4D;
				int ExtraPufftossInfo = *(int *)(_actor + 0x178);
				*(char *)(ExtraPufftossInfo + 0x14) = 4;
			}
			break;
		case 0x53:
			// Dog 2
			_actor = findActorWithType(236);
			if (_actor) {
				playCutscene(_actor,8,1);
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xC4:
			// AD2
			_actor = findActorWithType(185);
			if (_actor) {
				playCutscene(_actor,9,0);
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xC7:
			// KKO
			_actor = findActorWithType(165);
			if (_actor) {
				*(char *)(_actor + 0x18B) = 7;
			}
			break;
		case 0xCB:
			// DK Phase
			_actor = findActorWithType(281);
			if (_actor) {
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xCC:
			// Diddy Phase
			_actor = findActorWithType(292);
			if (_actor) {
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xCD:
			// Lanky Phase
			_actor = findActorWithType(293);
			if (_actor) {
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xCE:
			// Tiny Phase
			_actor = findActorWithType(294);
			if (_actor) {
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
			break;
		case 0xCF:
			// Chunky Phase
			_actor = findActorWithType(295);
			if (_actor) {
				_actor->control_state = 0x37;
				_actor->control_state_progress = 0;
			}
		break;
	}
}