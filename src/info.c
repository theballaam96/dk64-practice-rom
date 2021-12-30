#include "../include/common.h"
#include "../include/build_date.h"

//static const char build_date[32] = BUILD_DATE;

static const char* info_text_list[] = {
	"DK64 PRACTICE ROM",
	BUILD_DATE,
	0,
	"DK64PRACTICEROM.COM",
	0,
	"DEVS: BALLAAM, RAIN, ISOTARGE",
	0,
	"WITH THANKS TO:",
	"GLORIOUSLIAR, WEDAROBI",
	"ADAM W, CHRISTIANVEGA64",
	"2DOS, CANDYBOOTS, ZNERNICUS",
	"HORHAY, ZORULDA, MINIOVEN"
};

int* displayInfo(int* dl) {
	if (ControllerInput.Buttons & Start_Button) {
		dl = drawScreenRect(dl, 250, 200, 1000, 700, 3, 3, 3, 1);
		int y = 139;
		for (int i = 0; i < (sizeof(info_text_list) / 4); i++) {
			if (info_text_list[i] != 0) {
				dl = drawTextContainer(dl, 6, 93, y, (char*)info_text_list[i], 0xFF, 0xFF, 0xFF, 0xFF, 0);
				y += 13;
			} else {
				y += 7;
			}
		}
	} else {
		if (!watchActive) {
			dl = drawTextContainer(dl, 1, 25, 525, "DK64 PRACTICE ROM", 0xFF, 0xFF, 0xFF, 0xFF, 0);
			dl = drawTextContainer(dl, 1, 25, 550, "VERSION 1.4.2", 0xFF, 0xFF, 0xFF, 0xFF, 0);		
		}
		dl = drawTextContainer(dl, 6, 25, 80, "INFO", 0xFF, 0, 0, 0xFF, 0);
		dl = drawTextContainer(dl, 1, 85, 149, "g", 0xFF, 0xFF, 0xFF, 0xFF, 0); // Start Button
	}
	return dl;
}