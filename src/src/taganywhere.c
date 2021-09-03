#include "../include/common.h"

void tagAnywhere(void) {
	int _dest_character;
	char _weapon_bitfield;

	if (TBVoidByte & 2) {
		return;
	}
	if (CurrentMap == 0x50) {
		return;
	}
	if (Character > 4) {
		return;
	}
	if (ActiveMenu.isOpen && !(ControllerInput.Buttons & R_Button)) {
		return;
	}
  	if (!(NewlyPressedControllerInput.Buttons & D_Down)) {
    	return;
  	}

  	if (DisableTagAnywhere) {
  		return;
  	}

 	_dest_character = Character + 1;
  	if (_dest_character > 4) {
    	_dest_character = 0;
  	}
  	if (Player) {
    	_weapon_bitfield = MovesBase[_dest_character].weapon_bitfield;
    	if (((_weapon_bitfield & 1) == 0) || (Player->was_gun_out == 0)) {
      		Player->hand_state = 1;
      		Player->was_gun_out = 0;
      		if (_dest_character == 1) {
        		Player->hand_state = 0;
      		}
    	} else {
      		Player->hand_state = 2;
      		Player->was_gun_out = 1;
      		if (_dest_character == 1) {
        		Player->hand_state = 3;
      		}
    	};
    	Player->new_kong = (_dest_character + 2);
    	if (SwapObject) {
      		SwapObject->action_type = 0x3B;
    	}
  	}
}