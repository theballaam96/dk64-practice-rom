#include "vars.h"

extern void spawnMenu(int screenIndex);
extern void changeMenu(int newScreenIndex);
extern void moveSlot(void);
extern void initWarpMenu(void);
extern void playSFX(short sfxIndex);
extern void setPermFlag(short flagIndex);
extern void openStateMenu(void);
extern void openTimerSettingsMenu(void);
extern void openFileStateMainMenu(void);
extern void openFlagSubmenu(int screenIndex);
extern void toggleFlag(void);
extern void handleMapWarping(int map, int levelIndex);
extern int convertIDToIndex(short obj_index);

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

extern void openSettingsMainMenu(void);
extern void openKongColorsMenu(void);
extern void openInputQuadrantMenu(void);
extern void openDPadLRMenu(void);
extern void openDPadDMenu(void);
extern void openVanillaVarsMenu(void);
extern void openHackVarsMenu(void);

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
extern void savestateHandler(void);
extern void shorthandSavestate(void);
extern void initRamViewerTab(void);
extern void ramViewUpdate(void);
extern void savestateLoadMapLoadVars(void);
extern void changeCustomFlagVariable(void);
extern void LToCancelCS(void);
extern void displaySavePrompt(void);
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

extern void loadSettings(void);
extern void saveSettings(void);
extern void resetSettings(void);

extern const Screen maps_container_struct;
extern const Screen japes_mapwarp_struct;
extern const Screen japesmain_mapwarp_struct;
extern const Screen aztec_mapwarp_struct;
extern const Screen aztecmain_mapwarp_struct;
extern const Screen aztecfivedt_mapwarp_struct;
extern const Screen factory_mapwarp_struct;
extern const Screen factorymain_mapwarp_struct;
extern const Screen galleon_mapwarp_struct;
extern const Screen galleonmain_mapwarp_struct;
extern const Screen galleonships_mapwarp_struct;
extern const Screen watch_struct;
extern const Screen fungi_mapwarp_struct;
extern const Screen fungimain_mapwarp_struct;
extern const Screen fungigmush_mapwarp_struct;
extern const Screen fungimills_mapwarp_struct;
extern const Screen caves_mapwarp_struct;
extern const Screen cavesmain_mapwarp_struct;
extern const Screen caves5dc_mapwarp_struct;
extern const Screen caves5di_mapwarp_struct;
extern const Screen castle_mapwarp_struct;
extern const Screen castlemain_mapwarp_struct;
extern const Screen castlecrypt_mapwarp_struct;
extern const Screen castletunnel_mapwarp_struct;
extern const Screen castleoutside_mapwarp_struct;
extern const Screen castlerooms_mapwarp_struct;
extern const Screen isles_mapwarp_struct;
extern const Screen islesmain_mapwarp_struct;
extern const Screen isleslobbies_mapwarp_struct;
extern const Screen helmrool_mapwarp_struct;
extern const Screen state_struct;
extern const Screen changestate_struct;
extern const Screen timersettings_struct;
extern const Screen ramview_struct;
extern const Screen filestates_main_struct;
extern const Screen filestates_nle_struct;
extern const Screen filestates_101main_struct;
extern const Screen filestates_general_struct;
extern const Screen filestates_101org_struct;
extern const Screen filestates_101jfm_struct;
extern const Screen filestates_101ffm_struct;
extern const Screen viewstate_struct;
extern const Screen flagmain_struct;
extern const Screen flagmenu_kongs_struct;
extern const Screen flagmenu_keysin_struct;
extern const Screen flagmenu_keyshave_struct;
extern const Screen flagmenu_levelintros_struct;
extern const Screen flagmenu_leveltns_struct;
extern const Screen flagmenu_levelboss_struct;
extern const Screen flagmenu_cutscene_struct;
extern const Screen flagmenu_modifier_struct;
extern const Screen flagmenu_ftt_struct;
extern const Screen flagmenu_misc_struct;
extern const Screen flagcustom_struct;
extern const Screen cheats_struct;
extern const Screen gamemode_struct;
extern const Screen settings_struct;
extern const Screen kongcolors_struct;
extern const Screen quadrant_struct;
extern const Screen dpadlr_struct;
extern const Screen dpadd_struct;
extern const Screen transform_struct;
extern const Screen moveset_struct;
extern const Screen cranky_struct;
extern const Screen funky_struct;
extern const Screen candy_struct;
extern const Screen flagmenu_tbarrels_struct;
extern const Screen vanilla_struct;
extern const Screen hack_struct;

extern const Screen* menu_screens[];
extern const MapWarp* warping_struct[WarpScreens];
extern const flagMenuData* flag_menus[flagMenuScreenCount];
extern const int maps_container_functions[9];
extern const int flagmain_functions[11];
extern char kongcolors[5];

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