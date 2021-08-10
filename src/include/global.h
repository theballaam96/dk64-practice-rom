extern void spawnMenu(int screenIndex);
extern void changeMenu(int newScreenIndex);
extern void moveSlot(void);
extern void initWarpMenu(void);
extern void playSFX(short sfxIndex);
extern void setPermFlag(short flagIndex);
extern void warpToMap(void);
extern void openJapesMenu(void);

extern const Screen maps_container_struct;
extern const Screen japes_mapwarp_struct;

extern const MapWarp* warping_struct[1];
extern const int maps_container_functions[9];

extern const MapWarp map_japes_struct;
