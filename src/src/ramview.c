#include "../include/common.h"

#define ByteFormat4 0
#define ByteFormat2 1
#define ByteFormat1 2

#define validRamReadStart 0x80000000
#define validRamReadEnd 0x807FFF90

#define menuStateChangeStartAddr 00000000
#define menuStateSelectAddr 00000001 //for selecting a ram address to modify in the table
#define menuStatePokeAddr 00000002 //for changing a ram value

char formatter08[] = "%02X:%08X %08X %08X %08X";
char formatter04[] = "%02X:%04X %04X %04X %04X %04X %04X %04X %04X";
char formatter02[] = "%02X:%02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X %02X";
char formatterheaderViewText[] = "ADDR: %08X";

char openRamViewText[] = "OPEN RAM VIEW";
char closeRamViewText[] = "CLOSE RAM VIEW";
char headerViewText[30] = "HEADER";
char line1[60] = "1";
char line2[60] = "2";
char line3[60] = "3";
char line4[60] = "4";
char line5[60] = "5";
char line6[60] = "6";
char line7[60] = "7";
char line8[60] = "8";
char currentFormat = 0;
int* printStartAddr = (int*)0x80000000;
unsigned char headerStyle = 10;
unsigned char tableStyle = 5;

char* ramViewTextPtrs[] = {headerViewText, line1, line2, line3, line4, line5, line6, line7, line8};
TextOverlay* textOverlayInstances[9] = {0};

static char* ramview_array[] = {
    openRamViewText,
    closeRamViewText,
};

void dk_strFormatWrapper(char* destination, int byteFormat, int* address) {
    if (byteFormat == ByteFormat4) {
        dk_strFormat(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1), *(address + 2), *(address + 3));
    } else if (byteFormat == ByteFormat2) {
        dk_strFormat(destination, formatter04, ((unsigned int)address & 0x000000FF), *((unsigned short*)address), *((unsigned short*)address + 1), *((unsigned short*)address + 2), *((unsigned short*)address + 3), *((unsigned short*)address + 4), *((unsigned short*)address + 5), *((unsigned short*)address + 6), *((unsigned short*)address + 7));
    } else if (byteFormat == ByteFormat1) {
        dk_strFormat(destination, formatter02, ((unsigned int)address & 0x000000FF), *((unsigned char*)address), *((unsigned char*)address + 1), *((unsigned char*)address + 2), *((unsigned char*)address + 3), *((unsigned char*)address + 4), *((unsigned char*)address + 5), *((unsigned char*)address + 6), *((unsigned char*)address + 7), *((unsigned char*)address + 8), *((unsigned char*)address + 9), *((unsigned char*)address + 10), *((unsigned char*)address + 11), *((unsigned char*)address + 12), *((unsigned char*)address + 13), *((unsigned char*)address + 14), *((unsigned char*)address + 15));
    } else {//unknown byte format, default to %08X
        dk_strFormat(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1), *(address + 2), *(address + 3));
    }
}

int* spawnTextOverlayWrapper(int style, int x, int y, char* string, int timer1, int timer2, unsigned char effect, unsigned char speed) {
    spawnTextOverlay(style, x, y, string, timer1, timer2, effect, speed);
    return CurrentActorPointer;
}

void initHeader(int* address) {
    TextOverlay* textOverlay;

    dk_strFormat(ramViewTextPtrs[0], formatterheaderViewText, address);
    textOverlay = (TextOverlay*)spawnTextOverlayWrapper(headerStyle, 60, 15, headerViewText, 0, 0, 2, 0);
    textOverlay->string = ramViewTextPtrs[0];
    textOverlayInstances[0] = textOverlay;
    textOverlay->opacity = 0xFF;
}

void updateHeader(int* address) {
    dk_strFormat(ramViewTextPtrs[0], formatterheaderViewText, address);
    textOverlayInstances[0]->string = ramViewTextPtrs[0];
}

void initTable (int* address) {
    TextOverlay* textOverlay;
    int x = 10;
    int y = 60;

    for (int i = 0; i < (sizeof(ramViewTextPtrs) / sizeof(char*)) -1; i++) {
        dk_strFormatWrapper((ramViewTextPtrs[i+1]), currentFormat, (address + (i * 4)));
        textOverlay = (TextOverlay*)spawnTextOverlayWrapper(tableStyle, x, y, (ramViewTextPtrs[i+1]), 0, 0, 2, 0);
        textOverlay->string = ramViewTextPtrs[i+1];
        textOverlayInstances[i+1] = textOverlay;
        textOverlay->opacity = 0xFF;
        y += 15;
    }
}

void updateTable(int* address) {
    for (int i = 0; i < (sizeof(ramViewTextPtrs) / sizeof(char*)) -1; i++) { //max of 8 lines
        if (ramViewTextPtrs[i+1] != 0) {
            dk_strFormatWrapper((ramViewTextPtrs[i+1]), currentFormat, (address + (i * 4)));
            textOverlayInstances[i+1]->string = ramViewTextPtrs[i+1];
            //we do i+1 on lines because *lines[0] is header text
        }
    }
}

void destroyTextObjects(void) {
    for (int i = 0; i < sizeof(textOverlayInstances) / sizeof(TextOverlay*); i++) {
        if (textOverlayInstances[i] != NULL) {
            deleteActor((int*)textOverlayInstances[i]);
            textOverlayInstances[i] = NULL;
        }
    }
}

void scrollRAMViewer(void) {
    if (p1PressedButtons & D_Up && p1HeldButtons & L_Button) {
        if ( (unsigned int)(printStartAddr - 4) < (unsigned int) validRamReadStart) {
            //prevents reading from invalid memory
        } else {
            printStartAddr -= 0x4;
        }
    }

    if (p1PressedButtons & D_Down && p1HeldButtons & L_Button) {
        if ( (unsigned int) (printStartAddr + 4) >= (unsigned int) validRamReadEnd) { //we display 0x10 bytes * 8 therefore we stop advancing at 807FFF90
            //prevents reading from invalid memory
        } else {
            printStartAddr += 0x4;
        }
    }
}

void checkForFormatChange(void) {
    if (p1PressedButtons & D_Right && p1HeldButtons & L_Button) {
        if ( (currentFormat + 1) < 3) {
            currentFormat++;
        }
    }
    
    if (p1PressedButtons & D_Left && p1HeldButtons & L_Button) {
        if ( currentFormat != 0) {
            currentFormat--;
        }
    }
}

void closeRamViewerDisplay(void){
    if (RAMDisplayOpen == 1) {
        RAMDisplayOpen = 0;
        destroyTextObjects();
    }
}

void ramViewUpdate(void) {
    if (RAMDisplayOpen == 1) {
        checkForFormatChange();
        scrollRAMViewer();
        updateHeader(printStartAddr);
        updateTable(printStartAddr);
        if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
            closeRamViewerDisplay();
        }
    }
}

void startRamViewerDisplay (void) {
    if (RAMDisplayOpen == 0) {
        initHeader(printStartAddr);
        initTable(printStartAddr);
        RAMDisplayOpen = 1;
    }
}

void initRamViewerTab(void) {
	changeMenu(34);
};

static const int ramview_functions[] = {
	(int)&startRamViewerDisplay,
	(int)&closeRamViewerDisplay,
};

const Screen ramview_struct = {
	.TextArray = (int*)ramview_array,
	.FunctionArray = ramview_functions,
	.ArrayItems = 2,
	.ParentScreen = 0,
	.ParentPosition = 4
};

