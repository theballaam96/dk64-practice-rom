#include "../include/common.h"
#include "../include/build_date.h"

//static const char build_date[32] = BUILD_DATE;

static char info_on = 0;
static char info_screen_index = 0;
static char info_next_screen_index = 0;
static short info_opacity = 0xFF;
static char info_opacity_direction = 0;
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
	return drawTextContainer(dl, INFO_STYLE, x, y, str, 0xFF, 0xFF, 0xFF, info_opacity, 0);
}
int* displayInfo(int* dl) {
	if (NewlyPressedControllerInput.Buttons & Start_Button) {
		info_on = 1 ^ info_on;
		if (info_on) {
			info_screen_index = 0;
			info_next_screen_index = 0;
			info_opacity = 0xFF;
			info_opacity_direction = 0;
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
				dl = drawImage(dl, IMAGE_GITHUB, RGBA16, 32, 32, 630, 500, 3.0f, 3.0f, info_opacity);
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
				dl = drawImage(dl, IMAGE_BALLAAM, RGBA16, 32, 32, 350, 350, 3.0f, 3.0f, info_opacity);
				dl = drawImage(dl, IMAGE_RAIN, RGBA16, 32, 32, 910, 430, 3.0f, 3.0f, info_opacity);
				dl = drawImage(dl, IMAGE_ISOTARGE, RGBA16, 32, 32, 350, 550, 3.0f, 3.0f, info_opacity);
				break;
			case 3:
				for (int i = 0; i < sizeof(info_3)/4;i++) {
					if (info_3[i]) {
						dl = drawInfoText(dl, 0, y, (char*)info_3[i]);
					}
					y += getYDiff(info_3[i]);
				}
			break;
		}
		if (info_opacity_direction < 0) {
			info_opacity -= 20;
			if (info_opacity < 0) {
				info_opacity = 0;
				info_opacity_direction = 1;
				info_screen_index = info_next_screen_index;
			}
		} else if (info_opacity_direction > 0) {
			info_opacity += 20;
			if (info_opacity > 255) {
				info_opacity = 255;
				info_opacity_direction = 0;
			}
		}
		dk_strFormat((char*)page_str,"PAGE %d",info_next_screen_index + 1);
		int line_center = getCenter(INFO_STYLE,page_str);
		dl = drawTextContainer(dl, INFO_STYLE, line_center, 275, (char*)page_str, 0xFF, 0xFF, 0xFF, 0xFF, 0);
		if (ROM_VERSION == 0) {
			if (info_next_screen_index > 0) {
				dl = drawTextContainer(dl, 1, 255, 442, "l", 0xFF, 0xFF, 0xFF, 0xFF, 0); // L
			}
			if (info_next_screen_index < 3) {
				dl = drawTextContainer(dl, 1, 360, 442, "r", 0xFF, 0xFF, 0xFF, 0xFF, 0); // R
			}
		}
		if (NewlyPressedControllerInput.Buttons & R_Button) {
			if (info_next_screen_index < 3) {
				info_next_screen_index += 1;
				if (info_opacity_direction >= 0) {
					info_opacity_direction = -1;
				}
			}
		} else if (NewlyPressedControllerInput.Buttons & L_Button) {
			if (info_next_screen_index > 0) {
				info_next_screen_index -= 1;
				if (info_opacity_direction >= 0) {
					info_opacity_direction = -1;
				}
			}
		}
	} else {
		if (!watchActive && (ROM_VERSION == 0)) {
			dl = drawTextContainer(dl, 1, 25, 525, "DK64 PRACTICE ROM", 0xFF, 0xFF, 0xFF, 0xFF, 0);
			dl = drawTextContainer(dl, 1, 25, 550, "VERSION 1.4.3", 0xFF, 0xFF, 0xFF, 0xFF, 0);		
		}
		dl = drawTextContainer(dl, 6, 25, 80, INFO_TEXT, 0xFF, 0, 0, 0xFF, 0);
		if (ROM_VERSION == 0) {
			dl = drawTextContainer(dl, 1, 85, 149, "g", 0xFF, 0xFF, 0xFF, 0xFF, 0); // Start Button
		}
	}
	return dl;
}