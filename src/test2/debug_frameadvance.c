#include "include/common.h"

void toggleFrameAdvanceState(void) {
	if (ArtificialPauseOn == 0) {
		PreviousFrameButtons = 0;
	}
	if (DisablePositionButtons == 1) {
		if ((ActiveMenu.isOpen == 0) && (RAMDisplayOpen == 0)) {
			if (ClosingMenu == 0) {
				if (IsPauseMenuOpen == 0) {
					if (NewlyPressedControllerInput.Buttons & D_Right) {
						if (ArtificialPauseOn) {
							// Play
							FrameAdvancing = 0;
							TBVoidByte = TBVoidByte & 0xFD;
							ArtificialPauseOn = 0;
							if ((PauseTimestampMajor) || (PauseTimestampMinor)) {
								if (HelmTimerShown) {
									getTimestampDiffInTicks(PauseTimestampMajor,PauseTimestampMinor);
									timestampAdd((int*)&TempTimestampStorageMajor,(int*)&HelmStartTimestampMajor);
									HelmStartTimestampMajor = TempTimestampStorageMajor;
									HelmStartTimestampMinor = TempTimestampStorageMinor;
								}
							}
							PauseTimestampMajor = 0;
							PauseTimestampMinor = 0;
						} else {
							// Pause
							PreviousFrameButtons = ControllerInput.Buttons;
							TBVoidByte = TBVoidByte | 2;
							ArtificialPauseOn = 1;
							PauseTimestampMajor = CurrentTimestampMajor;
							PauseTimestampMinor = CurrentTimestampMinor;
						}
					}
				}
			}
		}
	}
};

void initFrameAdvance(void) {
	short _buttons;
	if (DisablePositionButtons == 1) {
		if (IsPauseMenuOpen == 0) {
			if ((ActiveMenu.isOpen == 0) && (RAMDisplayOpen == 0)) {
				if (ClosingMenu == 0) {
					if (NewlyPressedControllerInput.Buttons & D_Left) {
						if (FrameAdvancing == 0) {
							PreviousFrameButtons = ControllerInput.Buttons;
						}
						FrameAdvancing = 1;
						FrameAdvanceStart = FrameLag;
						TBVoidByte = TBVoidByte & 0xFD;
						ArtificialPauseOn = 0;
						_buttons = PreviousFrameButtons | 0xF00;
						BackgroundHeldInput.Buttons = BackgroundHeldInput.Buttons & _buttons;
						if ((PauseTimestampMajor) || (PauseTimestampMinor)) {
							if (HelmTimerShown) {
								getTimestampDiffInTicks(PauseTimestampMajor,PauseTimestampMinor);
								timestampAdd((int*)&TempTimestampStorageMajor,(int*)&HelmStartTimestampMajor);
								HelmStartTimestampMajor = TempTimestampStorageMajor;
								HelmStartTimestampMinor = TempTimestampStorageMinor;
							}
						}
						PauseTimestampMajor = 0;
						PauseTimestampMinor = 0;
					}
				}
			}
		}
	}
}

void exitFrameAdvance(void) {
	unsigned int _diff;
	if (FrameAdvancing) {
		if (IsPauseMenuOpen == 0) {
			if ((ActiveMenu.isOpen == 0) && (RAMDisplayOpen == 0)) {
				if (ClosingMenu == 0) {
					_diff = FrameLag - FrameAdvanceStart;
					if (_diff > 0) {
						if ((TBVoidByte & 2) == 0) {
							PreviousFrameButtons = ControllerInput.Buttons;
							PauseTimestampMajor = CurrentTimestampMajor;
							PauseTimestampMinor = CurrentTimestampMinor;
						}
						TBVoidByte = TBVoidByte | 2;
						ArtificialPauseOn = 1;
					}
				}
			}
		}
	}
}