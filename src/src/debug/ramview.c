#include "../../include/common.h"

#define ByteFormat4 0
#define ByteFormat2 1
#define ByteFormat1 2

#define validRamReadStart 0x80000000
#define validRamReadEnd 0x807FFFC8

#define menuStateChangeStartAddr 00000000
#define menuStateSelectAddr 00000001 //for selecting a ram address to modify in the table
#define menuStatePokeAddr 00000002 //for changing a ram value

#define ramViewY 40
#define ramViewYOffset 22

char formatter08[] = "%02X:%08X %08X";
char formatter04[] = "%02X:%04X %04X %04X %04X";
char formatter02[] = "%02X:%02X %02X %02X %02X %02X %02X %02X %02X";
char formatterheaderViewText[] = "Addr: 0x%08X";

char openRamViewText[] = "Open RAM View";
char closeRamViewText[] = "Close RAM View";
char headerViewText[30] = "HEADER";
char line1[60] = "1";
char line2[60] = "2";
char line3[60] = "3";
char line4[60] = "4";
char line5[60] = "5";
char line6[60] = "6";
char line7[60] = "7";
char line8[60] = "8";
char focusedBytes[10] = "00";
char focusedAddrChar[2] = "0";
short focusedBytes_offset = 0;
char currentFormat = 0;
int* printStartAddr = (int*)0x80000000;
unsigned char headerStyle = 10;
unsigned char tableStyle = 5;
char editAddrPosition = 6;
unsigned int ramViewer_start = validRamReadStart;
unsigned int ramViewer_end = validRamReadEnd;
unsigned int focusValue = 0;
int ramViewEditMode = 0;

char* ramViewTextPtrs[] = {headerViewText, line1, line2, line3, line4, line5, line6, line7, line8};
char* focusedBytePtr = focusedBytes;
char* focusedAddrPtr = focusedAddrChar;
TextOverlay* textOverlayInstances[11] = {0};

static char* ramview_array[] = {
    openRamViewText,
    closeRamViewText,
};

void defineRAMViewerParameters(int* start, int* end) {
    ramViewer_start = (unsigned int)start;
    ramViewer_end = (unsigned int)end - 0x38;
    printStartAddr = start;
}

void dk_strFormatWrapper(char* destination, int byteFormat, int* address) {
    if (byteFormat == ByteFormat4) {
        dk_strFormat(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1));
    } else if (byteFormat == ByteFormat2) {
        dk_strFormat(destination, formatter04, ((unsigned int)address & 0x000000FF), *((unsigned short*)address), *((unsigned short*)address + 1), *((unsigned short*)address + 2), *((unsigned short*)address + 3));
    } else if (byteFormat == ByteFormat1) {
        dk_strFormat(destination, formatter02, ((unsigned int)address & 0x000000FF), *((unsigned char*)address), *((unsigned char*)address + 1), *((unsigned char*)address + 2), *((unsigned char*)address + 3), *((unsigned char*)address + 4), *((unsigned char*)address + 5), *((unsigned char*)address + 6), *((unsigned char*)address + 7));
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
    textOverlay = (TextOverlay*)spawnTextOverlayWrapper(headerStyle, 25, 25, headerViewText, 0, 0, 2, 0);
    textOverlay->string = ramViewTextPtrs[0];
    textOverlayInstances[0] = textOverlay;
    textOverlay->opacity = 0xFF;
    textOverlay->style = 128;
}

void updateHeader(int* address) {
    dk_strFormat(ramViewTextPtrs[0], formatterheaderViewText, address);
    textOverlayInstances[0]->string = ramViewTextPtrs[0];
}

void formatByteFocus(int* address, int byteFormat) {
    unsigned int addr_value = 0;
    char focus_format1[] = "%08X";
    char focus_format2[] = "%04X";
    char focus_format3[] = "%02X";
    char* focus_formats[] = {
        focus_format1,
        focus_format2,
        focus_format3,
    };
    int format_index = 0;
    if (byteFormat == ByteFormat4) {
        addr_value = *((unsigned int*)address + focusedBytes_offset);
        format_index = 0;
        //dk_strFormat((focusedBytePtr), "%08X", addr_value);
    } else if (byteFormat == ByteFormat2) {
        addr_value = *((unsigned short*)address + focusedBytes_offset);
        format_index = 1;
        //dk_strFormat((focusedBytePtr), "%04X", addr_value);
    } else if (byteFormat == ByteFormat1) {
        addr_value = *((unsigned char*)address + focusedBytes_offset);
        format_index = 2;
        //dk_strFormat((focusedBytePtr), "%02X", addr_value);
    } else {//unknown byte format, default to %08X
        addr_value = *((unsigned int*)address + focusedBytes_offset);
        format_index = 0;
        //dk_strFormat((focusedBytePtr), "%08X", addr_value);
    };
    if (ramViewEditMode > 1) {
        dk_strFormat((focusedBytePtr), focus_formats[format_index], focusValue);
    } else {
        dk_strFormat((focusedBytePtr), focus_formats[format_index], addr_value);
    }
    if (ramViewEditMode == 1) {
        focusValue = addr_value;
    }
}

void spawnAddrChanger(void) {
    TextOverlay* textOverlay;
    textOverlay = (TextOverlay*)spawnTextOverlayWrapper(tableStyle, 25, 25, (focusedAddrPtr), 0, 0, 2, 0);
    textOverlay->string = focusedAddrPtr;
    textOverlayInstances[10] = textOverlay;
    textOverlay->opacity = 0xFF;
    textOverlay->red = 0xFF;
    textOverlay->green = 0xD7;
    textOverlay->blue = 0;
    textOverlay->style = 128;
}

void initTable (int* address) {
    TextOverlay* textOverlay;
    int x = 10;
    int y = ramViewY;
    for (int i = 0; i < (sizeof(ramViewTextPtrs) / sizeof(char*)) -1; i++) {
        dk_strFormatWrapper((ramViewTextPtrs[i+1]), currentFormat, (address + (i * 2)));
        textOverlay = (TextOverlay*)spawnTextOverlayWrapper(tableStyle, x, y, (ramViewTextPtrs[i+1]), 0, 0, 2, 0);
        textOverlay->string = ramViewTextPtrs[i+1];
        textOverlayInstances[i+1] = textOverlay;
        textOverlay->opacity = 0xFF;
        y += ramViewYOffset;
    }
    // Focused Byte
    formatByteFocus(address, currentFormat);
    textOverlay = (TextOverlay*)spawnTextOverlayWrapper(tableStyle, 29, ramViewY, (focusedBytePtr), 0, 0, 2, 0);
    textOverlay->string = focusedBytePtr;
    textOverlayInstances[9] = textOverlay;
    textOverlay->opacity = 0xFF;
    textOverlay->red = 0xFF;
    textOverlay->green = 0xD7;
    textOverlay->blue = 0;
    // Focused Addr
    spawnAddrChanger();
}

void updateTable(int* address) {
    int offset_size = (2 << currentFormat);
    int byte_size = (2 << (2 - currentFormat));
    int focus_x = focusedBytes_offset % offset_size;
    int focus_y = (focusedBytes_offset - focus_x) / offset_size;
    int text_size = byte_size + 1;
    for (int i = 0; i < (sizeof(ramViewTextPtrs) / sizeof(char*)) -1; i++) { //max of 8 lines
        if (ramViewTextPtrs[i+1] != 0) {
            if (i < 8) {
                dk_strFormatWrapper((ramViewTextPtrs[i+1]), currentFormat, (address + (i * 2)));
                textOverlayInstances[i+1]->string = ramViewTextPtrs[i+1];
                //we do i+1 on lines because *lines[0] is header text
            }
        }
    }
    formatByteFocus(address, currentFormat);
    textOverlayInstances[9]->string = focusedBytes;
    if ((ControllerInput.Buttons & R_Button) == 0) {
        for (int i = 0; i < byte_size; i++) {
            ramViewTextPtrs[focus_y + 1][i + 3 + (focus_x * text_size)] = 0x20;
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

void updateRAMValue(int* address) {
    if (ControllerInput.Buttons & L_Button) {
        textOverlayInstances[9]->red = 0xFF;
        textOverlayInstances[9]->green = 0x45;
        textOverlayInstances[9]->blue = 0x00;
    } else {
        textOverlayInstances[9]->red = 0xFF;
        textOverlayInstances[9]->green = 0xD7;
        textOverlayInstances[9]->blue = 0x00;
    }
    if ((NewlyPressedControllerInput.Buttons & D_Up) && (ControllerInput.Buttons & L_Button)) {
        focusValue += 1;
    }

    if ((NewlyPressedControllerInput.Buttons & D_Down) && (ControllerInput.Buttons & L_Button)) {
        focusValue -= 1;
    }
    if (ramViewEditMode == 3) {
        if (currentFormat == ByteFormat4) {
            *((unsigned int*)address + focusedBytes_offset) = focusValue;
        } else if (currentFormat == ByteFormat2) {
            *((unsigned short*)address + focusedBytes_offset) = focusValue & 0xFFFF;
        } else if (currentFormat == ByteFormat1) {
            *((unsigned char*)address + focusedBytes_offset) = focusValue & 0xFF;
        } else {//unknown byte format, default to %08X
            *((unsigned int*)address + focusedBytes_offset) = focusValue;
        };
    }
}

int getGroovyCharKerning(int hex_digit) {
    switch (hex_digit) {
        case 0x0:
        case 0xA:
            return 32.8;
        case 0x1:
            return 19;
        case 0x2:
        case 0x5:
        case 0x6:
        case 0x7:
            return 36;
        case 0x3:
        case 0x8:
        case 0x9:
            return 39;
        case 0x4:
            return 42;
        case 0xB:
            return 35;
        case 0xC:
        case 0xE:
            return 29;
        case 0xD:
        case 0xF:
            return 32;
        break;
    }
    return 0;
}

void editAddress(void) {
    int x_pos = 0;
    int initial_digit = ((unsigned int)printStartAddr >> (4 * (6 - editAddrPosition))) & 0xF;
    int new_digit = initial_digit;
    int slot = 0xF;
    int opp_slot = -1;
    if ((ControllerInput.Buttons & R_Button) && (ControllerInput.Buttons & L_Button) == 0) {
        textOverlayInstances[9]->opacity = 0x0;
        textOverlayInstances[10]->opacity = 0xFF;
        if (NewlyPressedControllerInput.Buttons & D_Left) {
            editAddrPosition -= 1;
        } else if (NewlyPressedControllerInput.Buttons & D_Right) {
            editAddrPosition += 1;
        } else if (NewlyPressedControllerInput.Buttons & D_Up) {
            if (editAddrPosition == 6) {
                new_digit += 8;
            } else {
                new_digit += 1;
            }
            if (new_digit > 0xF) {
                new_digit = 0;
            }
        } else if (NewlyPressedControllerInput.Buttons & D_Down) {
            if (editAddrPosition == 6) {
                new_digit += 8;
            } else {
                new_digit -= 1;
            }
            if (new_digit < 0) {
                new_digit = 0xF;
            }
            if (new_digit > 0xF) {
                new_digit = 0;
            }
        }
        if (initial_digit != new_digit) {
            slot <<= (4 * (6 - editAddrPosition));
            opp_slot -= slot;
            printStartAddr = (int*)(((unsigned int)(printStartAddr) & opp_slot) | (new_digit << (4 * (6 - editAddrPosition))));
        }
        if ((int)printStartAddr < ramViewer_start) {
            printStartAddr = (int*)ramViewer_start;
        } else {
            if ((int)printStartAddr > ramViewer_end) {
                printStartAddr = (int*)ramViewer_end;
            }
        }
    } else {
        textOverlayInstances[9]->opacity = 0xFF;
        textOverlayInstances[10]->opacity = 0x00;
    }
    if (editAddrPosition < 1) {
        editAddrPosition = 1;
    } else {
        if (editAddrPosition > 6) {
            editAddrPosition = 6;
        }
    }
    x_pos = 377;
    for (int i = 0; i < (editAddrPosition - 1); i++) {
        x_pos += getGroovyCharKerning(((unsigned int)printStartAddr >> (4 * (5 - i))) & 0xF);
    }
    //x_pos = TestVariable;
    textOverlayInstances[10]->xPos = x_pos;
    dk_strFormat((focusedAddrPtr),"%1X",((unsigned int)printStartAddr >> (4 * (6 - editAddrPosition))) & 0xF);
}

void checkForFormatChange(void) {
    if (p1PressedButtons & D_Right && p1HeldButtons & L_Button) {
        if ( (currentFormat + 1) < 3) {
            currentFormat++;
            focusedBytes_offset <<= 1;
            ramViewEditMode = 0;
        }
    }
    
    if (p1PressedButtons & D_Left && p1HeldButtons & L_Button) {
        if ( currentFormat != 0) {
            currentFormat--;
            focusedBytes_offset >>= 1;
            ramViewEditMode = 0;
        }
    }
}

void closeRamViewerDisplay(void) {
    if (RAMDisplayOpen) {
        RAMDisplayOpen = 0;
        destroyTextObjects();
    }
}

void moveRAMViewFocus(void) {
    int focus_x;
    int focus_y;
    int offset_size;
    int x_offset_size = 0;
    if (((RAMDisplayOpen) && (ClosingMenu == 0))) {
        if ((ControllerInput.Buttons & R_Button) == 0) {
            offset_size = (2 << currentFormat);
            if ((ControllerInput.Buttons & L_Button) == 0) {
                if (NewlyPressedControllerInput.Buttons & D_Left) {
                    focusedBytes_offset -= 0x1;
                } else {
                    if (NewlyPressedControllerInput.Buttons & D_Right) {
                        focusedBytes_offset += 0x1;
                    } else {
                        if (NewlyPressedControllerInput.Buttons & D_Up) {
                            focusedBytes_offset -= offset_size;
                        } else {
                            if (NewlyPressedControllerInput.Buttons & D_Down) {
                                focusedBytes_offset += offset_size;
                            }
                        }
                    }
                }
            }
            if (focusedBytes_offset < 0) {
                printStartAddr -= 2;
                focusedBytes_offset += offset_size;
            }
            if (focusedBytes_offset >= (0x10 << currentFormat)) {
                printStartAddr += 2;
                focusedBytes_offset -= offset_size;
            }
            if ((int)printStartAddr < ramViewer_start) {
                printStartAddr = (int*)ramViewer_start;
            } else {
                if ((int)printStartAddr > ramViewer_end) {
                    printStartAddr = (int*)ramViewer_end;
                }
            }
            focus_x = focusedBytes_offset % offset_size;
            focus_y = (focusedBytes_offset - focus_x) / offset_size;
            switch(currentFormat) {
                case 0:
                    x_offset_size = 346.5;
                    break;
                case 1:
                    x_offset_size = 192.45;
                    break;
                case 2:
                    x_offset_size = 115.5;
                break;
            }
            textOverlayInstances[9]->xPos = (39 * 4) + (focus_x * x_offset_size);
            textOverlayInstances[9]->yPos = (ramViewY * 4) + (focus_y * (4 * ramViewYOffset));
        }
    }   
}

void detectLayering(void) {
    if ((int)textOverlayInstances[10] < (int)textOverlayInstances[0]) {
        if (textOverlayInstances[10] != NULL) {
            deleteActor((int*)textOverlayInstances[10]);
            textOverlayInstances[10] = NULL;
            spawnAddrChanger();
        }
    }
}

void ramViewUpdate(void) {
    if (RAMDisplayOpen) {
        detectLayering();
        if (ControllerInput.Buttons & L_Button) {
            if (ramViewEditMode == 1){
                ramViewEditMode = 2;
            } else {
                if (ramViewEditMode == 0) {
                    ramViewEditMode = 1;
                }
            }
        }
        if (ramViewEditMode == 3) {
            ramViewEditMode = 0;
        }
        if ((PreviouslyPressedButtons.Buttons & L_Button) && (ControllerInput.Buttons & L_Button) == 0) {
            ramViewEditMode = 3;
        }
        checkForFormatChange();
        moveRAMViewFocus();
        editAddress();
        updateRAMValue(printStartAddr);
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
        closeMenu();
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
	.ParentScreen = 76,
	.ParentPosition = 1
};

