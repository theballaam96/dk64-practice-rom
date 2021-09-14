#include "../include/common.h"

static PosState pos_state1 = {};
static PosState pos_state2 = {};
static PosState pos_state3 = {};
static PosState pos_state4 = {};

static PosState* pos_states[] = {
	&pos_state1,
	&pos_state2,
	&pos_state3,
	&pos_state4
};

void handlePositionSavestates(void) {
	int _focused_state = FocusedSavestate;
	if ((ActiveMenu.isOpen == 0) && (RAMDisplayOpen == 0)) {
		if (ClosingMenu == 0) {
			if (DisablePositionButtons == 0) {
				if (NewlyPressedControllerInput.Buttons & D_Right) {
					// Save Position
					if (Player) {
						// Position
						pos_states[_focused_state]->xPos = Player->xPos;
						pos_states[_focused_state]->yPos = Player->yPos;
						pos_states[_focused_state]->zPos = Player->zPos;
						if (SwapObject) {
							pos_states[_focused_state]->xCamera = SwapObject->cameraPositions[0].xPos;
							pos_states[_focused_state]->yCamera = SwapObject->cameraPositions[0].yPos;
							pos_states[_focused_state]->zCamera = SwapObject->cameraPositions[0].zPos;
						}
						if (Camera) {
							pos_states[_focused_state]->cameraRotation = Camera->viewportRotation;
						}
						pos_states[_focused_state]->yFloor = Player->floor;
						// Stored Position
						if (Player->rendering_param_pointer) {
							if (Player->rendering_param_pointer->bone_array1) {
								pos_states[_focused_state]->xStored1 = Player->rendering_param_pointer->bone_array1->xPos;
								pos_states[_focused_state]->yStored1 = Player->rendering_param_pointer->bone_array1->yPos;
								pos_states[_focused_state]->zStored1 = Player->rendering_param_pointer->bone_array1->zPos;
							}
							if (Player->rendering_param_pointer->bone_array2) {
								pos_states[_focused_state]->xStored2 = Player->rendering_param_pointer->bone_array2->xPos;
								pos_states[_focused_state]->yStored2 = Player->rendering_param_pointer->bone_array2->yPos;
								pos_states[_focused_state]->zStored2 = Player->rendering_param_pointer->bone_array2->zPos;
							}
						}
						// Angles
						pos_states[_focused_state]->facing_angle = Player->facing_angle;
						pos_states[_focused_state]->skew_angle = Player->skew_angle;
						// Speed Components
						pos_states[_focused_state]->hVelocity = Player->hSpeed;
						pos_states[_focused_state]->yVelocity = Player->yVelocity;
						pos_states[_focused_state]->yAccel = Player->yAccel;
						// Boolean Data
						pos_states[_focused_state]->map = CurrentMap;
						playSFX(Bell);
					}
				} else {
					if (NewlyPressedControllerInput.Buttons & D_Left) {
						// Load Position
						if (pos_states[_focused_state]->map == CurrentMap) {
							TimerData.Start = 0;
							TimerData.Mode = 0;
							TimerData.Timer = 0;
							if (Player) {
								Player->xPos = pos_states[_focused_state]->xPos;
								Player->yPos = pos_states[_focused_state]->yPos;
								Player->zPos = pos_states[_focused_state]->zPos;
								Player->floor = pos_states[_focused_state]->yFloor;
								if (SwapObject) {
									for (int i = 0; i < 4; i++) {
										SwapObject->cameraPositions[i].xPos = pos_states[_focused_state]->xCamera;
										SwapObject->cameraPositions[i].yPos = pos_states[_focused_state]->yCamera;
										SwapObject->cameraPositions[i].zPos = pos_states[_focused_state]->zCamera;
									}
								}
								if (Camera) {
									Camera->viewportX = pos_states[_focused_state]->xCamera;
									Camera->viewportY = pos_states[_focused_state]->yCamera;
									Camera->viewportZ = pos_states[_focused_state]->zCamera;
									Camera->viewportRotation = pos_states[_focused_state]->cameraRotation;
								}
								if ((CurrentMap != 0xCC) || (CurrentMap != 0xCD) || (CurrentMap != 0xCF)) {
									if (IsAutowalking) {
										if ((AutowalkPointer) && ((int)AutowalkPointer >= 0x80000000) && ((int)AutowalkPointer < 0x80800000)) {
											AutowalkPointer->xPos = (short)Player->xPos;
											AutowalkPointer->zPos = (short)Player->zPos;
										}
									}
								}
								if ((Player->obj_props_bitfield & 4) == 0) {
									if (Player->rendering_param_pointer) {
										if (Player->rendering_param_pointer->bone_array1) {
											Player->rendering_param_pointer->bone_array1->xPos = pos_states[_focused_state]->xStored1;
											Player->rendering_param_pointer->bone_array1->yPos = pos_states[_focused_state]->yStored1;
											Player->rendering_param_pointer->bone_array1->zPos = pos_states[_focused_state]->zStored1;
										}
										if (Player->rendering_param_pointer->bone_array2) {
											Player->rendering_param_pointer->bone_array2->xPos = pos_states[_focused_state]->xStored2;
											Player->rendering_param_pointer->bone_array2->yPos = pos_states[_focused_state]->yStored2;
											Player->rendering_param_pointer->bone_array2->zPos = pos_states[_focused_state]->zStored2;
										}
									}
								}
								Player->facing_angle = pos_states[_focused_state]->facing_angle;
								Player->skew_angle = pos_states[_focused_state]->skew_angle;
								Player->hSpeed = pos_states[_focused_state]->hVelocity;
								Player->yVelocity = pos_states[_focused_state]->yVelocity;
								Player->yAccel = pos_states[_focused_state]->yAccel;
								// Some hacks to make position warping work
								Player->touching_object = 0;
								Player->collision_queue_pointer = 0;
							}
						}
					}
				}
			}
		}
	}
}