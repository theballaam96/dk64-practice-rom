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
	if (RAMDisplayOpen) {
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

	_dest_character = (Character + 1) % 5;
	if (Player) {
		tagKong(_dest_character + 2);
		clearTagSlide(Player);
		Player->new_kong = _dest_character + 2;
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
	  	if (Player->rendering_param_pointer) {
	  		if (Player->rendering_param_pointer->bone_array1) {
	  			Player->rendering_param_pointer->bone_array1->xPos = Player->xPos;
	  			Player->rendering_param_pointer->bone_array1->yPos = Player->yPos;
	  			Player->rendering_param_pointer->bone_array1->zPos = Player->zPos;
	  		}
	  		if (Player->rendering_param_pointer->bone_array2) {
	  			Player->rendering_param_pointer->bone_array2->xPos = Player->xPos;
	  			Player->rendering_param_pointer->bone_array2->yPos = Player->yPos;
	  			Player->rendering_param_pointer->bone_array2->zPos = Player->zPos;
	  		}
	  	}
	}
}