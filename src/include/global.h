#include "vars.h"

extern void spawnMenu(int screenIndex);
extern void changeMenu(int newScreenIndex);
extern void moveSlot(void);
extern void initWarpMenu(void);
extern void playSFX(short sfxIndex);
extern void setPermFlag(short flagIndex);
extern void openStateMenu(void);
extern void openTimerSettingsMenu(void);

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
extern void patchHooks(void);
extern void handleTimer(void);
extern void hideInputDisplay(void);
extern void savestateHandler(void);
extern void shorthandSavestate(void);

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

extern const MapWarp* warping_struct[WarpScreens];
extern const int maps_container_functions[9];

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