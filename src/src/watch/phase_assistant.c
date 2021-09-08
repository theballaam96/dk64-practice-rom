#include "../../include/common.h"

static phaseInputs phaseass_inputs00[] = {0};
static phaseInputs phaseass_inputs01[] = {0};
static phaseInputs phaseass_inputs02[] = {0};
static phaseInputs phaseass_inputs03[] = {0};
static phaseInputs phaseass_inputs04[] = {0};
static phaseInputs phaseass_inputs05[] = {0};
static phaseInputs phaseass_inputs06[] = {0};
static phaseInputs phaseass_inputs07[]= {0};
static phaseInputs phaseass_inputs08[] = {0};
static phaseInputs phaseass_inputs09[] = {0};
static phaseInputs phaseass_inputs10[] = {0};
static phaseInputs phaseass_inputs11[] = {0};
static phaseInputs phaseass_inputs12[] = {0};
static phaseInputs phaseass_inputs13[] = {0};
static phaseInputs phaseass_inputs14[] = {0};

static phaseInputs* phaseass_input_list[] = {
	phaseass_inputs00,
	phaseass_inputs01,
	phaseass_inputs02,
	phaseass_inputs03,
	phaseass_inputs04,
	phaseass_inputs05,
	phaseass_inputs06,
	phaseass_inputs07,
	phaseass_inputs08,
	phaseass_inputs09,
	phaseass_inputs10,
	phaseass_inputs11,
	phaseass_inputs12,
	phaseass_inputs13,
	phaseass_inputs14,
};

static int phase_frame_counter = 0;
static int phase_initiated = 0;
static int y_side = 0;
static int phasewalk_state = 0;
	// 0 = Initial State
	// 1 = Back
	// 2 = Neutral
	// 3 = Forward
	// 4 = Z
static char phase_accelerated = 0;

int adjustStickMagnitude(int axis_value) {
	if (axis_value < -70) {
		return -70;
	} else {
		if (axis_value > 70) {
			return 70;
		} else {
			if ((axis_value > -6) && (axis_value < 6)) {
				return 0;
			}
		}
	}
	return axis_value;
}

void logInputs(void) {
	char _x = ControllerInput.stickX;
	char _y = ControllerInput.stickY;
	phaseass_input_list[phase_frame_counter]->buttons = ControllerInput.Buttons;
	_x = adjustStickMagnitude(_x);
	_y = adjustStickMagnitude(_y);
	y_side = 0;
	if (_y > 0) {
		y_side = 1;
	} else {
		if (_y < 0) {
			y_side = -1;
		}
	};
	PhaseChecker.previousMagnitude = (unsigned char)(float)(dk_sqrt((_x * _x) + (_y * _y)));
	phaseass_input_list[phase_frame_counter]->stickX = _x;
	phaseass_input_list[phase_frame_counter]->stickY = _y;
}

void analyzeInputs(void) {
	unsigned int last_frame_magnitude = 0;
	int mag_diff = 0;
	int movement = 0;
	char _x = 0;
	char _y = 0;
	int calculate_phase = 0;
	if (PhaseChecker.assistant_on) {
		if (Player) {
			movement = Player->control_state;
			_x = adjustStickMagnitude(ControllerInput.stickX);
			_y = adjustStickMagnitude(ControllerInput.stickY);
			if ((movement == 2) || (movement == 4)) {
				if (Player->control_state_progress < 11) {
					PhaseChecker.reason_code = 6;
				}
			}
			if (phase_initiated == 0) {
				if (NewlyPressedControllerInput.Buttons & C_Up) {
					phase_initiated = 1;
					PhaseChecker.previousMagnitude = 127; // High value to cover off low mag diff reasoning
					phase_frame_counter = 0;
					phasewalk_state = 0;
					PhaseChecker.prev_y_side = 0;
					PhaseChecker.reason_code = 5;
					phase_accelerated = 0;
				}
			} else {
				if (phase_frame_counter > 14) {
					phase_initiated = 0;
				}
				
			}
			if ((movement == 2) || (movement == 4)) {
				if (Player->control_state_progress == 0) {
					if ((Player->facing_angle >= 2048) && (Player->facing_angle < 4096)) {
						PhaseChecker.reason_code = 3;
						phase_initiated = 0;
					}
					calculate_phase = 1;
				}
			} else {
				calculate_phase = 1;
			}
			if ((phase_initiated) && (calculate_phase)) {
				last_frame_magnitude = PhaseChecker.previousMagnitude;
				logInputs();
				mag_diff = last_frame_magnitude - PhaseChecker.previousMagnitude;
				switch(phasewalk_state) {
					case 0:
						if ((mag_diff < 14) && (mag_diff > -14)) {
							PhaseChecker.reason_code = 1;
							phase_initiated = 0;
						} else {
							if (y_side == -1) {
								phasewalk_state = 1;
							}
						}
						break;
					case 1:
						if ((mag_diff < 14) && (mag_diff > -14)) {
							if (y_side == 1) {
								PhaseChecker.reason_code = 4;
							} else {
								PhaseChecker.reason_code = 9;
							}
							phase_initiated = 0;
						} else {
							if (y_side == 0) {
								phasewalk_state = 2;
							} else {
								if (y_side == 1) {
									phasewalk_state = 3;
								}
							}
						}
						break;
					case 2:
						if ((mag_diff < 14) && (mag_diff > -14)) {
							PhaseChecker.reason_code = 9;
							phase_initiated = 0;
						} else {
							if (y_side == 1) {
								phasewalk_state = 3;
							} else {
								if (y_side == -1){
									phasewalk_state = 1;
								}
							}
						}
						break;
					case 3:
						if ((mag_diff < 14) && (mag_diff > -14)) {
							PhaseChecker.reason_code = 10;
							phase_initiated = 0;
						} else {
							if ((Player->hSpeed < 40) && (phase_accelerated == 0)) {
								PhaseChecker.reason_code = 2;
								phase_initiated = 0;
							} else {
								phase_accelerated = 1;
								if ((Player->facing_angle >= 2048) && (Player->facing_angle < 4096)) {
									PhaseChecker.reason_code = 3;
									phase_initiated = 0;
								} else {
									if (ControllerInput.Buttons & Z_Button) {
										if ((_x == 0) && (_y == 0)) {
											phase_initiated = 0;
											PhaseChecker.reason_code = 0;
										} else {
											phasewalk_state = 4;
										}
									} else {
										if ((_x == 0) && (_y == 0)) {
											phase_initiated = 0;
											PhaseChecker.reason_code = 8;
										}
									}
								}
							}
						}
						break;
					case 4:
						if ((_x == 0) && (_y == 0)) {
							PhaseChecker.reason_code = 0;
						} else {
							PhaseChecker.reason_code = 7;
						}
						phase_initiated = 0;
					break;
				}
				phase_frame_counter++;
				PhaseChecker.prev_y_side = y_side;
			}
		}
	}
}