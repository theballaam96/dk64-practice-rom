#include "../include/common.h"
#include "../include/build_date.h"

//static const char build_date[32] = BUILD_DATE;

static char info_on = 0;
static char info_screen_index = 0;
static const char* info_0[] = {
	"DK64 PRACTICE ROM",
	BUILD_DATE,
	"DK64PRACTICEROM.COM",
	"GITHUB.DK64PRACTICEROM.COM"
};
static const short info_x0[] = {-1,-1,-1,-1};
static const short info_y0[] = {
	139,
	152,
	172,
	250
};
static const char* info_1[] = {
	"GETTING STARTED",
	"OPEN MENU: R THEN L",
	"NAVIGATE MENU: D-PAD",
	"ACCEPT OPTION: L OR D-RIGHT",
	"MANUAL.DK64PRACTICEROM.COM"
};
static const short info_x1[] = {-1,0,0,0,-1};
static const short info_y1[] = {
	139,
	172,
	185,
	198,
	235
};
static const char* info_2[] = {
	"DEVELOPERS",
	"BALLAAM",
	"RAIN",
	"ISOTARGE",
};
static const short info_x2[] = {-1,50,150,50};
static const short info_y2[] = {
	139,
	172,
	198,
	235,
}; 
static const char* info_3[] = {
	"WITH THANKS",
	0,
	"GLORIOUSLIAR, WEDAROBI",
	"ADAM W, CHRISTIANVEGA64",
	"2DOS, CANDYBOOTS, ZNERNICUS",
	"HORHAY, ZORULDA, MINIOVEN"
};
/*
	INFO PAGE IDEAS
		General:
			DK64 Practice ROM
			Build Date/Release Version
			Website
			GitHub
		Getting Started
			R + L to open menu
			D-Pad to navigate
			L or D-Right to accept option
			Manual for more
		Developers:
			Ballaam (K. Lumsy)
			Iso (Mad Jack)
			Rain (Snide)
		Other Credits:
			Adam, CV64, GL, Wed
			2dos, Candy, Znernicus
			Horhay, Zorulda
*/

int getYDiff(const char* text) {
	if (text != 0) {
		return 13;
	}
	return 7;
}

static char page_str[10] = "";
#define INFO_STYLE 6
int* drawInfoText(int* dl, int x_offset, int y, char* str) {
	int x = 93 + x_offset;
	if (x_offset == -1) {
		x = getCenter(INFO_STYLE,str);
	}
	return drawTextContainer(dl, INFO_STYLE, x, y, str, 0xFF, 0xFF, 0xFF, 0xFF, 0);
}
int* displayInfo(int* dl) {
	if (NewlyPressedControllerInput.Buttons & Start_Button) {
		info_on = 1 ^ info_on;
		if (info_on) {
			info_screen_index = 0;
		}
	}
	if (info_on) {
		dl = drawScreenRect(dl, 250, 200, 1000, 700, 3, 3, 3, 1);
		int y = 139;
		switch(info_screen_index) {
			case 0:
				for (int i = 0; i < sizeof(info_0)/4;i++) {
					if (info_0[i]) {
						dl = drawInfoText(dl, info_x0[i], info_y0[i], (char*)info_0[i]);
					}
				}
				dl = drawImage(dl, 50, RGBA16, 32, 32, 630, 500, 3.0f, 3.0f, 0xFF);
				break;
			case 1:
				for (int i = 0; i < sizeof(info_1)/4;i++) {
					if (info_1[i]) {
						dl = drawInfoText(dl, info_x1[i], info_y1[i], (char*)info_1[i]);
					}
				}
				break;
			case 2:
				for (int i = 0; i < sizeof(info_2)/4;i++) {
					if (info_2[i]) {
						dl = drawInfoText(dl, info_x2[i], info_y2[i], (char*)info_2[i]);
					}
					y += getYDiff(info_2[i]);
				}
				break;
			case 3:
				for (int i = 0; i < sizeof(info_3)/4;i++) {
					if (info_3[i]) {
						dl = drawInfoText(dl, TestVariable, y, (char*)info_3[i]);
					}
					y += getYDiff(info_3[i]);
				}
			break;
		}
		dk_strFormat((char*)page_str,"PAGE %d",info_screen_index + 1);
		int line_center = getCenter(INFO_STYLE,page_str);
		dl = drawTextContainer(dl, INFO_STYLE, line_center, 275, (char*)page_str, 0xFF, 0xFF, 0xFF, 0xFF, 0);
		if (NewlyPressedControllerInput.Buttons & R_Button) {
			if (info_screen_index < 3) {
				info_screen_index += 1;
			}
		} else if (NewlyPressedControllerInput.Buttons & L_Button) {
			if (info_screen_index > 0) {
				info_screen_index -= 1;
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