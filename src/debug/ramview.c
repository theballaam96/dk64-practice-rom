#include "../../include/common.h"

#define ByteFormat4 0
#define ByteFormat2 1
#define ByteFormat1 2
#define ByteFormatH 3

#define validRamReadStart 0x80000000
#define validRamReadEnd 0x807FFFB8

#define extraFuncCount 6
#define maxFreeze 8

#define menuStateChangeStartAddr 00000000
#define menuStateSelectAddr 00000001 //for selecting a ram address to modify in the table
#define menuStatePokeAddr 00000002 //for changing a ram value

#define ramViewY 38
#define ramViewYOffset 13

#define FOCUSMENU_DEFAULT 0
#define FOCUSMENU_DETAILS 1

char formatter08[] = "%02X:%08X %08X";
char formatter04[] = "%02X:%04X %04X %04X %04X";
char formatter02[] = "%02X:%02X %02X %02X %02X %02X %02X %02X %02X";
char formatterheaderViewText[] = "ADDR:0X%08X";

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
char addrEndBytes[7] = "";
short focusedBytes_offset = 0;
char currentFormat = 0;
int* printStartAddr = (int*)0x80000000;
unsigned char headerStyle = 10;
unsigned char tableStyle = 2;
char editAddrPosition = 6;
unsigned int ramViewer_start = validRamReadStart;
unsigned int ramViewer_end = validRamReadEnd;
unsigned int focusValue = 0;
int ramViewEditMode = 0;
char access_type = 0; // 0 = Debug Menu, 1 = Actor Menu
char focus_menu = 0; // 0 = Normal, 1 = Additional Options
char details_index = 0;
char details_cap = 0;
char editing_address = 0;
float focusbyte_x = 0;
float focusbyte_y = 0;

static int extraFuncs[extraFuncCount] = {};
int* focused_address = 0;

char* ramViewTextPtrs[] = {headerViewText, line1, line2, line3, line4, line5, line6, line7, line8};
char* focusedBytePtr = focusedBytes;
char* focusedAddrPtr = focusedAddrChar;
char* addrEndPtr = addrEndBytes;
TextOverlay* textOverlayInstances[12] = {0};

static freeze_struct freeze_data[maxFreeze] = {};

char ramview_size_full[15] = "";
static char* ramview_sizes[] = {
    "INT",
    "SHORT",
    "BYTE",
    "HEX DIGIT",
};

void defineRAMViewerParameters(int* start, int* end, int source) {
    ramViewer_start = (unsigned int)start;
    ramViewer_end = (unsigned int)end - 0x38;
    access_type = source;
    if ((source == 0) && (MemoryViewerLastAddress)) {
        printStartAddr = MemoryViewerLastAddress;
    } else {
        printStartAddr = start;
    }
    focus_menu = FOCUSMENU_DEFAULT;
}

void dk_strFormatWrapper(char* destination, int byteFormat, int* address) {
    if (byteFormat == ByteFormat4) {
        dk_strFormat(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1));
    } else if (byteFormat == ByteFormat2) {
        dk_strFormat(destination, formatter04, ((unsigned int)address & 0x000000FF), *((unsigned short*)address), *((unsigned short*)address + 1), *((unsigned short*)address + 2), *((unsigned short*)address + 3));
    } else if ((byteFormat == ByteFormat1) || (byteFormat == ByteFormatH)) {
        dk_strFormat(destination, formatter02, ((unsigned int)address & 0x000000FF), *((unsigned char*)address), *((unsigned char*)address + 1), *((unsigned char*)address + 2), *((unsigned char*)address + 3), *((unsigned char*)address + 4), *((unsigned char*)address + 5), *((unsigned char*)address + 6), *((unsigned char*)address + 7));
    } else {//unknown byte format, default to %08X
        dk_strFormat(destination, formatter08, ((unsigned int)address & 0x000000FF), *(address), *(address + 1), *(address + 2), *(address + 3));
    }
}

void updateHeader(int* address) {
    dk_strFormat(ramViewTextPtrs[0], formatterheaderViewText, address);
}

void formatByteFocus(int* address, int byteFormat) {
    unsigned int addr_value = 0;
    char focus_format1[] = "%08X";
    char focus_format2[] = "%04X";
    char focus_format3[] = "%02X";
    char focus_format4[] = "%01X";
    char* focus_formats[] = {
        focus_format1,
        focus_format2,
        focus_format3,
        focus_format4,
    };
    int format_index = 0;
    unsigned int _cap = 0;
    if (byteFormat == ByteFormat4) {
        addr_value = *((unsigned int*)address + focusedBytes_offset);
        focused_address = (int*)(address + focusedBytes_offset);
        format_index = 0;
        _cap = 0xFFFFFFFF;
    } else if (byteFormat == ByteFormat2) {
        addr_value = *((unsigned short*)address + focusedBytes_offset);
        focused_address = (int*)(((short*)address + focusedBytes_offset));
        format_index = 1;
        _cap = 0xFFFF;
    } else if (byteFormat == ByteFormat1) {
        addr_value = *((unsigned char*)address + focusedBytes_offset);
        focused_address = (int*)(((char*)address + focusedBytes_offset));
        format_index = 2;
        _cap = 0xFF;
    } else if (byteFormat == ByteFormatH) {
        addr_value = (*((unsigned char*)address + (focusedBytes_offset / 2)) >> (4 * (1 - (focusedBytes_offset % 2)))) & 0xF;
        focused_address = (int*)(((char*)address + (focusedBytes_offset / 2)));
        format_index = 3;
        _cap = 0xF;
    } else {//unknown byte format, default to %08X
        addr_value = *((unsigned int*)address + focusedBytes_offset);
        focused_address = (int*)(address + focusedBytes_offset);
        format_index = 0;
        _cap = 0xFFFFFFFF;
    };
    if (ramViewEditMode > 1) {
        dk_strFormat((focusedBytePtr), focus_formats[format_index], focusValue & _cap);
    } else {
        dk_strFormat((focusedBytePtr), focus_formats[format_index], addr_value);
    }
    if (ramViewEditMode == 1) {
        focusValue = addr_value;
    }
}

void updateTable(int* address) {
    int offset_size = (2 << currentFormat);
    int byte_size = (2 << (2 - currentFormat));
    int focus_x = focusedBytes_offset % offset_size;
    int focus_y = (focusedBytes_offset - focus_x) / offset_size;
    int text_size = byte_size + 1;
    if ((ControllerInput.Buttons & R_Button) == 0) {
        if (currentFormat < 3) {
            for (int i = 0; i < byte_size; i++) {
                ramViewTextPtrs[focus_y + 1][i + 3 + (focus_x * text_size)] = 0x20;
            }
        } else {
            int sets = focus_x / 2;
            ramViewTextPtrs[focus_y + 1][3 + (sets * 3) + (focus_x % 2)] = 0x20;
        }
    }
}

void updateRAMValue(int* address) {
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
        } else if (currentFormat == ByteFormatH) {
            if (focusedBytes_offset % 2) {
                *((unsigned char*)address + (focusedBytes_offset / 2)) = (*((unsigned char*)address + (focusedBytes_offset / 2)) & 0xF0) + (focusValue & 0xF);
            } else {
                *((unsigned char*)address + (focusedBytes_offset / 2)) = (*((unsigned char*)address + (focusedBytes_offset / 2)) & 0xF) + ((focusValue & 0xF) << 4);
            }
        } else {//unknown byte format, default to %08X
            *((unsigned int*)address + focusedBytes_offset) = focusValue;
        };
    }
}

void editAddress(void) {
    int initial_digit = ((unsigned int)printStartAddr >> (4 * (6 - editAddrPosition))) & 0xF;
    int new_digit = initial_digit;
    int slot = 0xF;
    int opp_slot = -1;
    editing_address = 0;
    if (focus_menu == FOCUSMENU_DEFAULT) {
        if ((ControllerInput.Buttons & R_Button) && (ControllerInput.Buttons & L_Button) == 0) {
            editing_address = 1;
            // textOverlayInstances[9]->opacity = 0x0;
            // textOverlayInstances[10]->opacity = 0xFF;
            // textOverlayInstances[11]->opacity = 0xFF;
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
        }
    }
    if (editAddrPosition < 1) {
        editAddrPosition = 1;
    } else {
        if (editAddrPosition > 6) {
            editAddrPosition = 6;
        }
    }
    if (focus_menu == FOCUSMENU_DEFAULT) {
        if (ControllerInput.Buttons & R_Button) {
            int focus_char = 0x20;
            int _pos = editAddrPosition + 9;
            int addr_pos = 0;
            if (editAddrPosition == 6) {
                addrEndBytes[0] = 0x20;
                addrEndBytes[1] = 0;
            } else {
                while ((focus_char != 0) && (addr_pos < 7)) {
                    focus_char = ramViewTextPtrs[0][_pos++];
                    addrEndBytes[addr_pos++] = focus_char;
                }
                addrEndBytes[addr_pos] = 0; 
            }
            ramViewTextPtrs[0][editAddrPosition + 9] = 0;
        }
    }
    dk_strFormat((focusedAddrPtr),"%1X",((unsigned int)printStartAddr >> (4 * (6 - editAddrPosition))) & 0xF);
}

void checkForFormatChange(void) {
    if (p1PressedButtons & D_Right && p1HeldButtons & L_Button) {
        if ( (currentFormat + 1) < 4) {
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
    RAMDisplayOpen = 0;
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
                case 3:
                    x_offset_size = 77;
                break;
            }
            float a = 4.77f;
            if (currentFormat < 3) {
                focusbyte_x = 49 + (focus_x * (x_offset_size / a));
            } else {
                int sets = focus_x / 2;
                focusbyte_x = 49 + (sets * (115 / a)) + (8.125f * (focus_x % 2));
            }
            focusbyte_y = ramViewY + (focus_y * ramViewYOffset);
        }
    }   
}

void alterDetailsFocus(void) {
    if (details_cap > 1) {
        if (NewlyPressedControllerInput.Buttons & D_Down) {
            details_index += 1;
            if (details_index == details_cap) {
                details_index = 0;
            }
        } else if (NewlyPressedControllerInput.Buttons & D_Up) {
            if (details_index > 0) {
                details_index -= 1;
            } else {
                details_index = details_cap - 1;
            }
        }
    }
}

void ramViewUpdate(void) {
    if (RAMDisplayOpen) {
        if (focus_menu == FOCUSMENU_DEFAULT) {
            if (ControllerInput.Buttons & L_Button) {
                if (ramViewEditMode == 1){
                    ramViewEditMode = 2;
                } else if (ramViewEditMode == 0) {
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
        if (NewlyPressedControllerInput.Buttons & Z_Button) {
            if (currentFormat == ByteFormatH) {
                focus_menu = FOCUSMENU_DEFAULT;
            } else {
                focus_menu += 1;
                if (focus_menu == 2) {
                    focus_menu = 0;
                }
                if (focus_menu == FOCUSMENU_DETAILS) {
                    details_index = 0;
                }
            }
        }
        if (focus_menu == FOCUSMENU_DEFAULT) {
            checkForFormatChange();
            moveRAMViewFocus();
            updateRAMValue(printStartAddr);
        }
        editAddress();
        if (focus_menu == FOCUSMENU_DETAILS) {
            alterDetailsFocus();
            if ((NewlyPressedControllerInput.Buttons & L_Button) || ((NewlyPressedControllerInput.Buttons & D_Right) && (MenuShortcutButtonsOff == 0))) {
                callFunc((int*)extraFuncs[(int)details_index]);
            }
        }
        if (access_type == 0) {
            MemoryViewerLastAddress = printStartAddr;
        }
        if ((TransitionSpeed > 0) || ((CutsceneActive == 6) && (CurrentMap == 0x50))) {
            closeRamViewerDisplay();
        }
    }
}

int* drawExtraText(int* dl, char* str, int y, int focus_index, int details_index, int background, int func) {
    int colors[6] = {0xFF,0xFF,0xFF,0xFF,0xD7,0x00};
    dl = drawPixelTextContainer(dl, 120, y, str,
    //dl = drawTextContainer(dl, 128, 200, y, str,
        colors[(3 * (focus_index == details_index)) + 0],
        colors[(3 * (focus_index == details_index)) + 1],
        colors[(3 * (focus_index == details_index)) + 2],
        0xFF, background);
    extraFuncs[focus_index] = func;
    return dl;
}

void followPointerFunc(void) {
    int addr_reduction = (int)(*(int*)(focused_address) % 8);
    int* new_addr = (int*)(*(int*)(focused_address) - addr_reduction);
    MemoryViewerLastAddress = new_addr;
    defineRAMViewerParameters((int*)0x80000000,(int*)0x80800000,0);
    printStartAddr = new_addr;
    focusedBytes_offset = 0;
    focus_menu = FOCUSMENU_DEFAULT;
}

void addToWatchFunc(int index) {
    //TestVariable = 2;
    int found_used = 0;
    int i = 0;
    while((i < 4) && !found_used) {
        if (!dynamic_watches[i].used) {
            found_used = 1;
            dynamic_watches[i].address = focused_address;
            int _used = 1;
            if (currentFormat == ByteFormat4) {
                dynamic_watches[i].size = DYNWATCH_UINT + index;
            } else if (currentFormat == ByteFormat2) {
                dynamic_watches[i].size = DYNWATCH_USHORT + index;
            } else if (currentFormat == ByteFormat1) {
                dynamic_watches[i].size = DYNWATCH_UBYTE + index;
            } else {
                _used = 0;
            }
            int added_watch = 0;
            for (int j = 0; j < WatchCount; j++) {
                if ((WatchIndex[j] == 0) && (!added_watch)) {
                    dynamic_watches[i].watch_index = j;
                    WatchIndex[j] = 27;
                    added_watch = 1;
                }
            }
            dynamic_watches[i].used = _used & added_watch;
            break;
        } else if (dynamic_watches[i].address == focused_address) {
            dynamic_watches[i].used = 0;
            WatchIndex[((int)dynamic_watches[i].watch_index) % WatchCount] = 0;
            break;
        }
        i++;
        if (i == 4) {
            playSFX(Wrong);
        }
    }
}

void addToWatchFuncU(void) {
    addToWatchFunc(0);
}

void addToWatchFuncS(void) {
    addToWatchFunc(1);
}

void addToWatchFuncH(void) {
    addToWatchFunc(2);
}

void addToWatchFuncF(void) {
    addToWatchFunc(3);
}

int getDynWatchIndex(void) {
    for (int i = 0; i < 4; i++) {
        if (dynamic_watches[i].used) {
            if (dynamic_watches[i].address == focused_address) {
                return i;
            }
        }
    }
    return -1;
}

void freezeValueFunc(void) {
    int found_used = 0;
    int i = 0;
    while ((i < maxFreeze) && !found_used) {
        if (!freeze_data[i].used) {
            found_used = 1;
            freeze_data[i].addr = focused_address;
            freeze_data[i].used = 1;
            if (currentFormat == ByteFormat4) {
                freeze_data[i].size = SIZE_INT;
                freeze_data[i].value = (unsigned int)*(unsigned int*)(focused_address);
            } else if (currentFormat == ByteFormat2) {
                freeze_data[i].size = SIZE_SHORT;
                freeze_data[i].value = (unsigned int)*(unsigned short*)(focused_address);
            } else if (currentFormat == ByteFormat1) {
                freeze_data[i].size = SIZE_BYTE;
                freeze_data[i].value = (unsigned int)*(unsigned char*)(focused_address);
            } else if (currentFormat == ByteFormatH) {
                freeze_data[i].size = SIZE_HEXDIG;
                freeze_data[i].value = (unsigned int)*(unsigned char*)(focused_address);
            } else {
                freeze_data[i].size = SIZE_UNKNOWN;
            }
            break;
        } else if (freeze_data[i].addr == focused_address) {
            freeze_data[i].used = 0;
            break;
        }
        i++;
        if (i == maxFreeze) {
            playSFX(Wrong);
        }
    }
}

int getFreezeIndex(void) {
    for (int i = 0; i < maxFreeze; i++) {
        if (freeze_data[i].used) {
            if (freeze_data[i].addr == focused_address) {
                return i;
            }
        }
    }
    return -1;
}

void handleFrozenValues(void) {
    for (int i = 0; i < maxFreeze; i++) {
        if (freeze_data[i].used) {
            int size = freeze_data[i].size;
            int val = freeze_data[i].value;
            if (size == SIZE_INT) {
                *(unsigned int*)(freeze_data[i].addr) = val;
            } else if (size == SIZE_SHORT) {
                *(unsigned short*)(freeze_data[i].addr) = val;
            } else if (size == SIZE_BYTE) {
                *(unsigned char*)(freeze_data[i].addr) = val;
            }
        }
    }
}

static char freeze_name[20] = "";

static char* watch_types[] = {
    "UNSIGNED",
    "SIGNED",
    "HEX",
    "FLOAT",
};

static char watch_name0[20] = "";
static char watch_name1[20] = "";
static char watch_name2[20] = "";
static char watch_name3[20] = "";

static char* watch_names[] = {
    watch_name0,
    watch_name1,
    watch_name2,
    watch_name3,
};

static int watch_funcs[] = {
    (int)&addToWatchFuncU,
    (int)&addToWatchFuncS,
    (int)&addToWatchFuncH,
    (int)&addToWatchFuncF,
};

int* displayMemory(int* dl) {
    int focus_index = 0;
    int x = 25;
    int y = ramViewY;
    int background = 1;
    int focus_rgb[3] = {0,0,0};
    int size_rgb[3] = {0xFF,0xFF,0xFF};
    int addr_y = 25;
    int offset_size = (2 << currentFormat);
    int byte_size = (2 << (2 - currentFormat));
    int focus_x = focusedBytes_offset % offset_size;
    int focus_y = (focusedBytes_offset - focus_x) / offset_size;
    int text_size = byte_size + 1;
    if (RAMDisplayOpen) {
        dk_strFormat(ramViewTextPtrs[0], formatterheaderViewText, printStartAddr);
        dl = drawPixelTextContainer(dl, 25, addr_y, ramViewTextPtrs[0], 0xFF, 0xFF, 0xFF, 0xFF, background);
        //dl = drawTextContainer(dl, 128, 25, addr_y, ramViewTextPtrs[0],0xFF,0xFF,0xFF,0xFF, background);
        for (int i = 0; i < (sizeof(ramViewTextPtrs) / sizeof(char*)) -1; i++) {
            dk_strFormatWrapper((ramViewTextPtrs[i+1]), currentFormat, (printStartAddr + (i * 2)));
            if ((ControllerInput.Buttons & R_Button) == 0) {
                if (currentFormat < 3) {
                    for (int k = 0; k < byte_size; k++) {
                        ramViewTextPtrs[focus_y + 1][k + 3 + (focus_x * text_size)] = 0x20;
                    }
                } else {
                    int sets = focus_x / 2;
                    ramViewTextPtrs[focus_y + 1][3 + (sets * 3) + (focus_x % 2)] = 0x20;
                }
            }
            dl = drawPixelTextContainer(dl, x, y, ramViewTextPtrs[i+1], 0xFF, 0xFF, 0xFF, 0xFF, background);
            //dl = drawTextContainer(dl, tableStyle, x, y, ,0xFF,0xFF,0xFF,0xFF, background);
            y += ramViewYOffset;
        }
        int size_x = 175;
        dk_strFormat(ramview_size_full, "SIZE:%s", ramview_sizes[(int)currentFormat]);
        if (!editing_address) {
            if (focus_menu == FOCUSMENU_DEFAULT) {
                if (ControllerInput.Buttons & L_Button) {
                    focus_rgb[0] = 0xFF;
                    focus_rgb[1] = 0x45;
                    focus_rgb[2] = 0x00;
                    size_rgb[0] = 0xFF;
                    size_rgb[1] = 0x45;
                    size_rgb[2] = 0x00;
                    if (currentFormat == ByteFormat4) {
                        dk_strFormat(ramview_size_full, "SIZE:%s>", ramview_sizes[(int)currentFormat]);
                    } else {
                        size_x -= 8;
                        if (currentFormat == ByteFormatH) {
                            dk_strFormat(ramview_size_full, "<SIZE:%s", ramview_sizes[(int)currentFormat]);
                        } else {
                            dk_strFormat(ramview_size_full, "<SIZE:%s>", ramview_sizes[(int)currentFormat]);
                        }
                    }
                } else {
                    focus_rgb[0] = 0xFF;
                    focus_rgb[1] = 0xD7;
                    focus_rgb[2] = 0x00;
                } 
            } else {
                focus_rgb[0] = 0xFF;
                focus_rgb[1] = 0x03;
                focus_rgb[2] = 0x03;
            }
        }
        dl = drawPixelTextContainer(dl, size_x, addr_y, ramview_size_full, 
            size_rgb[0],
            size_rgb[1],
            size_rgb[2], 0xFF, background);
        // Focused Byte
        formatByteFocus(printStartAddr, currentFormat);
        if (!editing_address) {
            dl = drawPixelTextContainer(dl, focusbyte_x, focusbyte_y, focusedBytePtr,
                focus_rgb[0],
                focus_rgb[1],
                focus_rgb[2],
                0xFF, background);
            // dl = drawTextContainer(dl, tableStyle, focusbyte_x, focusbyte_y, focusedBytePtr,
            //     focus_rgb[0],
            //     focus_rgb[1],
            //     focus_rgb[2],
            //     0xFF, background);
        }
        // Focused Addr
        int x_pos = 356;
        int char_spacing = 29;
        for (int i = 0; i < (editAddrPosition - 1); i++) {
            x_pos += char_spacing;
        }
        if (editing_address) {

            dl = drawPixelTextContainer(dl, (x_pos / 3.65f), addr_y, focusedAddrPtr,0xFF,0xD7,0x00,0xFF, background);
            //dl = drawTextContainer(dl, 128, (x_pos / 3.65f), addr_y, focusedAddrPtr,0xFF,0xD7,0x00,0xFF, background);
            // Addr End
            x_pos += char_spacing;
            dl = drawPixelTextContainer(dl, (x_pos / 3.65f), addr_y, addrEndBytes,0xFF,0xFF,0xFF,0xFF, background);
            //dl = drawTextContainer(dl, 128, (x_pos / 3.65f), addr_y, addrEndBytes,0xFF,0xFF,0xFF,0xFF, background);
        }
        if (focus_menu == FOCUSMENU_DETAILS) {
            int background = 1;
            // int y = 265;
            int y = 150;
            if (currentFormat == ByteFormat4) {
                int val = *(int*)(focused_address);
                if ((val >= 0x80000000) && (val < 0x80800000)) {
                    dl = drawExtraText(dl, "FOLLOW POINTER", y, focus_index, details_index, background, (int)&followPointerFunc);
                    focus_index += 1;
                    y += 13;
                }
            }
            if (currentFormat != ByteFormatH) {
                if (getDynWatchIndex() > -1) {
                    dl = drawExtraText(dl, "REMOVE AS WATCH", y, focus_index, details_index, background, watch_funcs[0]);
                    focus_index += 1;
                    y += 13;
                } else {
                    int type_count = 3;
                    if (currentFormat == ByteFormat4) {
                        type_count = 4;
                    }
                    for (int k = 0; k < type_count; k++) {
                        dk_strFormat((char*)watch_names[k],"ADD AS WATCH <%s>",watch_types[k]);
                        dl = drawExtraText(dl, (char*)watch_names[k], y, focus_index, details_index, background, watch_funcs[k]);
                        focus_index += 1;
                        y += 13;
                    }
                }
                if (getFreezeIndex() > -1) {
                    dk_strFormat((char*)freeze_name,"%s","UNFREEZE VALUE");
                } else {
                    dk_strFormat((char*)freeze_name,"%s","FREEZE VALUE");
                }
                dl = drawExtraText(dl, (char*)freeze_name, y, focus_index, details_index, background, (int)&freezeValueFunc);
                focus_index += 1;
                y += 13;
            }
            if (details_index >= focus_index) {
                details_index = focus_index - 1;
            }
        }
        details_cap = focus_index;
    }
    return dl;
}

void startRamViewerDisplay (void) {
    if (RAMDisplayOpen == 0) {
        closeMenu();
        RAMDisplayOpen = 1;
    }
}

static char freeze_name_0[30] = "";
static char freeze_name_1[30] = "";
static char freeze_name_2[30] = "";
static char freeze_name_3[30] = "";
static char freeze_name_4[30] = "";
static char freeze_name_5[30] = "";
static char freeze_name_6[30] = "";
static char freeze_name_7[30] = "";

static char* freeze_screen_array[] = {
    freeze_name_0,
    freeze_name_1,
    freeze_name_2,
    freeze_name_3,
    freeze_name_4,
    freeze_name_5,
    freeze_name_6,
    freeze_name_7,
};

static char has_freeze = 0;
static char freeze_indexes[] = {
    -1,-1,-1,-1,
    -1,-1,-1,-1,
};

void turnOffFreeze(void) {
    if (has_freeze) {
        int freeze_index = freeze_indexes[(int)ActiveMenu.positionIndex];
        freeze_data[freeze_index].used = 0;
        openFreezeScreen();
    }
}

static const int freeze_screen_functions[] = {
    (int)&turnOffFreeze,
    (int)&turnOffFreeze,
    (int)&turnOffFreeze,
    (int)&turnOffFreeze,
    (int)&turnOffFreeze,
    (int)&turnOffFreeze,
    (int)&turnOffFreeze,
};

Screen freeze_screen_struct = {
    .TextArray = (int*)freeze_screen_array,
    .FunctionArray = freeze_screen_functions,
    .ArrayItems = maxFreeze,
    .ParentScreen = ACTIVEMENU_SCREEN_DEBUG_MEMORYROOT,
    .ParentPosition = 1,
};

static char* size_names[] = {
    "BYTE",
    "SHORT",
    "INT",
    "HEX DIGIT",
    "UNKNOWN"
};

void openFreezeScreen(void) {
    int search_start = 0;
    int found_item = 0;
    for (int i = 0; i < maxFreeze; i++) {
        while (search_start < maxFreeze) {
            if (freeze_data[search_start].used) {
                dk_strFormat(
                    (char*)freeze_screen_array[i],
                    "} %X <%s>: 0X%X",
                    freeze_data[search_start].addr,
                    (char*)size_names[freeze_data[search_start].size],
                    freeze_data[search_start].value
                );
                freeze_indexes[i] = search_start;
                search_start += 1;
                found_item += 1;
                break;
            } else {
                search_start += 1;
            }
        }
    }
    has_freeze = found_item != 0;
    if (found_item == 0) {
        dk_strFormat((char*)freeze_screen_array[0],"NO FROZEN VALUES");
        found_item += 1;
    }
    freeze_screen_struct.ArrayItems = found_item;
    changeMenu(ACTIVEMENU_SCREEN_DEBUG_MEMORYFREEZE);
}

static char dynwatch_name_0[30] = "";
static char dynwatch_name_1[30] = "";
static char dynwatch_name_2[30] = "";
static char dynwatch_name_3[30] = "";

static char* dynwatch_manage_array[] = {
    dynwatch_name_0,
    dynwatch_name_1,
    dynwatch_name_2,
    dynwatch_name_3,
};

static char has_dynwatch = 0;
static char dynwatch_indexes[] = {
    -1,-1,-1,-1
};

void turnOffDynWatch(void) {
    if (has_dynwatch) {
        int dynwatch_index = dynwatch_indexes[(int)ActiveMenu.positionIndex];
        dynamic_watches[dynwatch_index].used = 0;
        WatchIndex[(int)dynamic_watches[dynwatch_index].watch_index] = 0;
        openDynwatchScreen();
    }
}

static const int dynwatch_manage_functions[] = {
    (int)&turnOffDynWatch,
    (int)&turnOffDynWatch,
    (int)&turnOffDynWatch,
    (int)&turnOffDynWatch,
};

Screen dynwatch_manage_struct = {
    .TextArray = (int*)dynwatch_manage_array,
    .FunctionArray = dynwatch_manage_functions,
    .ArrayItems = 4,
    .ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,
    .ParentPosition = 6,
};

void openDynwatchScreen(void) {
    int search_start = 0;
    int found_item = 0;
    int sizes[] = {0,0,0,1,1,1,2,2,2,2};
    int types[] = {0,1,2,0,1,2,0,1,2,3};
    for (int i = 0; i < 4; i++) {
        while (search_start < 4) {
            if (dynamic_watches[search_start].used) {
                int size = sizes[(int)dynamic_watches[search_start].size];
                int _type = types[(int)dynamic_watches[search_start].size];
                if (_type != 3) {
                    dk_strFormat(
                        (char*)dynwatch_manage_array[i],
                        "} %X <%s %s>",
                        dynamic_watches[search_start].address,
                        (char*)watch_types[_type],
                        (char*)size_names[size]
                    );
                } else {
                    dk_strFormat(
                        (char*)dynwatch_manage_array[i],
                        "} %X <FLOAT>",
                        dynamic_watches[search_start].address
                    );
                }
                dynwatch_indexes[i] = search_start;
                search_start += 1;
                found_item += 1;
                break;
            } else {
                search_start += 1;
            }
        }
    }
    has_dynwatch = found_item != 0;
    if (found_item == 0) {
        dk_strFormat((char*)dynwatch_manage_array[0],"NO DYNAMIC WATCHES");
        found_item += 1;
    }
    dynwatch_manage_struct.ArrayItems = found_item;
    changeMenu(ACTIVEMENU_SCREEN_WATCH_DYNWATCH);
}