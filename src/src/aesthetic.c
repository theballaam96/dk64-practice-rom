#include "../include/common.h"

void colorMenuSky(void) {
	MenuSkyTopRGB.red = 0;
	MenuSkyTopRGB.green = 0;
	MenuSkyTopRGB.blue = 0xFF;
	MenuSkyRGB.red = 0;
	MenuSkyRGB.green = 0;
	MenuSkyRGB.blue = 0;
};

void colorKong(void) {
	prepKongColoring();
	PlayerOneColor = 2;
	if ((Character == 2) || (Character == 4)) {
		PlayerOneColor = 1;
	}
}