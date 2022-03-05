#include "vars.h"

extern void spawnMenu(int screenIndex);
extern void changeMenu(int newScreenIndex);
extern void moveSlot(void);
extern void initWarpMenu(void);
extern void playSFX(short sfxIndex);
extern float arctan(float val);
extern float arctan2(float x, float y);
extern void complexFreeCheck(void* ptr);
extern void clearDKPortal(void);
extern void setPermFlag(short flagIndex);
extern void openStateMenu(void);
extern void openTimerSettingsMenu(void);
extern void openFileStateMainMenu(void);
extern void openFlagSubmenu(int screenIndex);
extern void toggleFlag(void);
extern void handleMapWarping(int map, int exit, int levelIndex, load_modes load_mode);
extern int convertIDToIndex(short obj_index);
extern int convertSubIDToIndex(short obj_index);
extern void* findActorWithType(int search_actor_type);
extern void closeMenu(void);
extern void startRamViewerDisplay(void);
extern void closeRamViewerDisplay(void);
extern void defineRAMViewerParameters(int* start, int* end, int source);
extern int isRDRAM(void* address);
extern int pm64ReadFromROM(int rom_start, int rom_end, void* write_location);
extern void setWarpPosition(float x, float y, float z);
extern void hideRacePosition(int show);
extern void setDataStates(int state, int eightbit);
extern void customHideHUD(void);
extern int* drawText(int* dl, int style, float x, float y, char* str, int red, int green, int blue, int opacity);
extern int* drawTextContainer(int* dl, int style, float x, float y, char* str, int red, int green, int blue, int opacity, int background);
extern int* displayMenu(int* dl);
extern int* displayWatches(int* dl);
extern int* drawTri(int* dl, short x1, short y1, short x2, short y2, short x3, short y3, int red, int green, int blue, int alpha);
extern int* displayMemory(int* dl);
extern int* drawImage(int* dl, int text_index, codecs codec_index, int img_width, int img_height, int x, int y, float xScale, float yScale, int opacity);
extern int* displayFairy(int* dl);
extern int* displayInfo(int* dl);
extern int* drawPixelText(int* dl, int x, int y, char* str, int red, int green, int blue, int alpha);
extern int* drawPixelTextContainer(int* dl, int x, int y, char* str, int red, int green, int blue, int alpha, int offset);
extern int* drawScreenRect(int* dl, int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha);
extern int* displaySimpleInput(int* dl);
extern int* displayVoid(int* dl);
extern void drawJetpacPixelFont(int* dl, char* str, int x, int y, int red, int green, int blue, int alpha);
extern int* displaySavePrompt(int* dl);
extern int getCenter(int style, char* str);

extern int getFakeKeyStatus(void);
extern int getFakeProdRoomStatus(void);

extern void colorWatch(char _red, char _green, char _blue, int slot);
extern void openWatchSnagMenu(void);
extern void toggleFairyViewer(void);
extern void checkWatchCapacity(void);

extern void warpToMap(void);
extern void openJapesMenu(void);
extern void openAztecMenu(void);
extern void openFactoryMenu(void);
extern void openGalleonMenu(void);
extern void openFungiMenu(void);
extern void openCavesMenu(void);
extern void openCastleMenu(void);
extern void openHelmRoolMenu(void);
extern void openIslesMenu(void);
extern void openOtherMapsMenu(void);
extern void openBonusMainMenu(void);

extern void openFlagsMainMenu(void);
extern void openFlagsKongMenu(void);
extern void openFlagsKeysinMenu(void);
extern void openFlagsKeyshaveMenu(void);
extern void openFlagsLevelintrosMenu(void);
extern void openFlagsLeveltnsMenu(void);
extern void openFlagsLevelbossMenu(void);
extern void openFlagsCutsceneMenu(void);
extern void openFlagsModifierMenu(void);
extern void openFlagsFTTMenu(void);
extern void openFlagsMiscMenu(void);
extern void openFlagsCustomMenu(void);
extern void openFlagsTBarrelMenu(void);
extern void openBPortsMenu(void);

extern void openCheatsMenu(void);
extern void alterSkewAngle(void);
extern void cancelCutscene(void);
extern void gainControl(void);
extern void corruptGame(void);
extern void endMinigame(void);
extern void openGamemodeMenu(void);
extern void openTransformMenu(void);
extern void openMovesetInventoryMenu(void);
extern void openCrankyMenu(void);
extern void openFunkyMenu(void);
extern void openCandyMenu(void);
extern void openTogglesMenu(void);
extern void toggleSandstorm(void);
extern void toggleSpawnPrevention(void);
extern void toggleTBVoid(void);
extern void openSnagMenu(void);
extern void killBoss(void);
extern void toggleVisify(void);
extern void changeTimer_button(void);
extern void changeTimer_spawnTimer(void);
extern void openTrickToggleMenu(void);
extern void DiddyMoonMoves(void);

extern void openSettingsMainMenu(void);
extern void openKongColorsMenu(void);
extern void openInputQuadrantMenu(void);
extern void openDPadLRMenu(void);
extern void openDPadDMenu(void);
extern void openVanillaVarsMenu(void);
extern void openHackVarsMenu(void);

extern void openActorMenu(void);
extern void openDebugMenu(void);
extern void openHeapMenu(void);
extern void openFlagLogMenu(void);
extern void openForceSpawnActorMenu(void);
extern void openCollisionMenu(void);
extern void updateActorScreen(void);

extern void openWatchMenu(void);
extern void endClose(void);
extern void toggleMenu(void);
extern void moveSlot(void);
extern void colorMenuSky(void);
extern void colorKong(void);
extern void levitate(void);
extern void closeMenuOnTransition(void);
extern void emergencyClose(void);
extern void confirmOption(void);
extern void menuShortcutButtons(void);
extern void startupSkip(void);
extern void closeWatchesOnTransition(void);
extern void openWatchesOnTransition(void);
extern void handleWatch(void);
extern void clampWatchFloats(void);
extern void tagAnywhere(void);
extern void initHack(void);
extern void handleTimer(void);
extern void hideInputDisplay(void);
extern void savestateHandler(int action);
extern void shorthandSavestate(void);
extern void initRamViewerTab(void);
extern void ramViewUpdate(void);
extern void savestateLoadMapLoadVars(void);
extern void fileStateMapLoadVars(void);
extern void changeCustomFlagVariable(void);
extern void LToCancelCS(void);
extern void clearSavePromptFlag(void);
extern void displayInput(void);
extern void openInputOnTransition(void);
extern void closeInputOnTransition(void);
extern void handlePositionSavestates(void);
extern void toggleFrameAdvanceState(void);
extern void initFrameAdvance(void);
extern void exitFrameAdvance(void);
extern void LToEndMinigame(void);
extern void forceStorySkip(void);
extern void setKRoolRound(void);
extern void handleAutophase(void);
extern void handleAutomoonkick(void);
extern void getSandstormAddress(void);
extern void handleSpawnPrevention(void);
extern void handleLToTBV(void);
extern void handleInfinites(void);
extern void isPaused(void);
extern void checkMapType(void);
extern void fileInit(void);
extern void updateLoadedActorNoTextOverlayList(int callType);
extern void shouldRefreshTOMenu(void);
extern void analyzeInputs(void);
extern void writeFlagsToLog(void);
extern void controlFairyViewer(void);
extern void toggleSelectedActor(void);
extern void loadMapVars_0(void);
extern void disableVoid(void);
extern void cancelTextbox(void);
//extern void correctTagCode(void);
extern int* displayFloors(int* dl);
extern void openInfinitesMenu(void);

extern void toggleArcadeMenu(void);
extern void controlArcadeMenuActions(void);
extern void finishLoadingArcadeState(void);
extern void autoCloseArcadeMenu(void);

extern void toggleJetpacMenu(void);
extern void controlJetpacMenuActions(void);
extern void autoCloseJetpacMenu(void);

extern int* spawnConsoleMenu(int* dl);
extern void controlConsoleMenu(void);

extern void runTest(void);
extern void startTest(void);

extern void loadSettings(void);
extern void saveSettings(void);
extern void resetSettings(void);

extern void spawnOverlay(void);
extern void closeOverlay(void);

extern void preload_map_voids(void);
extern void openStateSettingsMenu(void);

extern const Screen* menu_screens[];
extern const MapWarp* warping_struct[WarpScreens];
extern const flagMenuData* flag_menus[flagMenuScreenCount];
extern const int maps_container_functions[11];
extern const int flagmain_functions[12];
extern char kongcolors[5];
extern char* snagwatch_names_array[];
extern const snagTableInfo snag_data[];
extern flagLogData* flagLog_currentfitems[];

extern spriteDisplay* displaySlots[13];
extern spriteControl* spriteSlots[13];
extern otherSpriteControl* otherSpriteData[13];

extern const MapWarp map_japes_struct;
extern const MapWarp map_japesmain_struct;
extern const MapWarp map_aztec_struct;
extern const MapWarp map_aztecmain_struct;
extern const MapWarp map_aztecfivedt_struct;
extern const MapWarp map_factory_struct;
extern const MapWarp map_factorymain_struct;
extern const MapWarp map_galleon_struct;
extern const MapWarp map_galleonmain_struct;
extern const MapWarp map_galleonships_struct;
extern const MapWarp map_fungi_struct;
extern const MapWarp map_fungimain_struct;
extern const MapWarp map_fungigmush_struct;
extern const MapWarp map_fungimills_struct;
extern const MapWarp map_caves_struct;
extern const MapWarp map_cavesmain_struct;
extern const MapWarp map_caves5dc_struct;
extern const MapWarp map_caves5di_struct;
extern const MapWarp map_castle_struct;
extern const MapWarp map_castlemain_struct;
extern const MapWarp map_castlecrypt_struct;
extern const MapWarp map_castletunnel_struct;
extern const MapWarp map_castleoutside_struct;
extern const MapWarp map_castlerooms_struct;
extern const MapWarp map_isles_struct;
extern const MapWarp map_islesmain_struct;
extern const MapWarp map_isleslobbies_struct;
extern const MapWarp map_helmrool_struct;
extern const MapWarp map_other_struct;
extern const MapWarp map_bonusjapes_struct;
extern const MapWarp map_bonusaztec_struct;
extern const MapWarp map_bonusfactory_struct;
extern const MapWarp map_bonusgalleon_struct;
extern const MapWarp map_bonusfungi_struct;
extern const MapWarp map_bonuscaves_struct;
extern const MapWarp map_bonuscastle_struct;
extern const MapWarp map_bonushelm_struct;
extern const MapWarp map_bonusisles_struct;

extern const flagMenuData flagmenu_kongmenu;
extern const flagMenuData flagmenu_keysinmenu;
extern const flagMenuData flagmenu_keyshavemenu;
extern const flagMenuData flagmenu_levelintrosmenu;
extern const flagMenuData flagmenu_leveltnsmenu;
extern const flagMenuData flagmenu_levelbossmenu;
extern const flagMenuData flagmenu_cutscenemenu;
extern const flagMenuData flagmenu_modifiermenu;
extern const flagMenuData flagmenu_fttmenu;
extern const flagMenuData flagmenu_miscmenu;
extern const flagMenuData flagmenu_tbarrelmenu;