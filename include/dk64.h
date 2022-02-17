//functions
extern void setFlag(int flagIndex, int value, char flagType);
extern int checkFlag(int flagIndex, char flagType);
extern void* dk_malloc(int size);
extern void dk_free(void* mallocPtr);
extern void playSound(short soundIndex, int unk0, int unk1, int unk2, int unk3, int unk4);
extern void initiateTransition(int map, int exit);
extern void initiateTransition_0(int map, int exit, int unk0, int unk1);
extern int* getFlagBlockAddress(char flagType);
extern int isAddressActor(void* address);
extern int getTimestamp();
extern void dmaFileTransfer(int romStart, int romEnd, int ramStart);
extern void deleteActor(void* actor);
extern int spawnActor(int actorID, int actorBehaviour);
extern void spawnTextOverlay(int style, int x, int y, char* string, int timer1, int timer2, unsigned char effect, unsigned char speed);
extern float dk_sqrt(float __x);
extern float dk_cos(float __x);
extern float dk_sin(float __x);
extern void dk_strFormat(char* destination, char* source, ...);
extern void dk_multiply(double val1, double val2, int unk1, int unk2);
extern double convertTimestamp(double unk0, double unk1, unsigned int unk2, unsigned int unk3);
extern void resetMap();
extern void prepKongColoring();
extern void callFunc(int* addr);
extern int getTimestampDiff(unsigned int major, unsigned int minor);
extern void patchHook(unsigned int hook_rdram_location, int offset_in_hook_list, char hook_byte_size);
extern void* dk_memcpy(void* _dest, void* _src, int size);
extern void getTimestampDiffInTicks(unsigned int major, unsigned int minor);
extern int timestampDiffToMilliseconds(unsigned int major, unsigned int minor);
extern void timestampAdd(int* timestamp1, int* timestamp2);
extern void SaveToGlobal();
extern int DetectGameOver();
extern int DetectAdventure();
extern void displaySprite(void* control_pointer, void* sprite, int x, int y, int scale, int gif_updatefrequency, int movement_style);
extern int* getOtherSpritePointer();
extern void alterSize(void* object, int size);
extern void unkSizeFunction(void* object);
extern void spawnRocketbarrel(void* object, int unk);
extern void* getObjectArrayAddr(void* init_address, int common_object_size, int index);
extern void playSong(int songIndex);
extern void loadExtraHooks();
extern void playCutscene(void* actor, int cutscene_index, int cutscene_type);
extern void setHUDItemAsInfinite(int item_index, int player_index, char isInfinite);
extern void osWritebackDCacheAll();
extern void copyFromROM(int rom_start, void* write_location, void* file_size_location, int unk1, int unk2, int unk3, int unk4);
extern int getActorSpawnerID(void* actor);
extern void textOverlayCode(void);
extern void spawnTransferredActor(void);
extern void resolveMovementBox(void* spawner);
extern void wipeMemory(void* location, int size);
extern int getNewSaveTime();
extern void loadExits(int map);
extern int updateModel2Allowances(int map, int update_pointer);
extern void handleSetup(void* setup, int unk1, int unk2);
extern void ObjectModel2Something(void);
extern void loadEnemies(void* enemy_setup);
extern void extraEnemyParser(void* enemy_setup);
extern void wipeActors(void);
extern void spawnPersistentActors(void);
extern void spawnCameraAndKong(int exit);
extern void resetModelTwoCollisions(void);
extern void updateCharChangeStruct(void);
extern void resetDisplayLists(int player_count);
extern void clearActorDL(void* actor, int unk0);
extern void deleteActorContainer(void* actor);
extern void deleteAllObjectModel2(void);
extern void deleteActorSpawner(void* actor_spawner, int delete_actor);
extern void deleteAllActorSpawners(void);
extern void complexFree(void* addr);

extern void setArcadeTextXY(int x, int y);
extern void spawnArcadeText(void* dl, void* text_pointer);
extern void setArcadeTextColor(int red, int green, int blue, int alpha);
extern int arcadeGetObjIndexOfType(int obj_type);
extern int arcadeGetNextVacantSlot(void);
extern void setArcadeSong(int songIndex);

extern void spawnJetpacText(void* dl, char* str, short x, short y, int background);
extern void setJetpacTextColor(int red, int green, int blue, int alpha);
extern void startJetpacGame(void);
extern void placeJetpacFloor(void);
extern void resetJetpacVars(void);
extern void increaseLevel(void);
extern void spawnJetpacItem(competitor_struct* competitor);
extern void resetJetpacMap(competitor_struct* competitor);
extern void changeJetpacMode(int mode_index);

extern void hideHUD(void);
extern void tagKong(int kong_actor_index);
extern void clearGun(void* player);
extern void playAnimation(void* player, int anim_index);
extern void clearTagSlide(void* player);
extern void initiateTransitionFade(int map, int cutscene, int gamemode);
extern void __osInvalICache(void* write_location, int size);
extern void __osInvalDCache(void* write_location, int size);
extern void __osWritebackDCache(void* write_location, int size);
extern void __osCreateMesgQueue(void* queue, void* message, int unk);
extern void __osRecvMesg(void* queue, void* message, int os_state);
extern void __osEPiStartDMA(void* unk, void* iomessage, int os_state);
extern void __osPiRawReadIo(int a0, void* a1);
extern int __osDisableInt();
extern void __osRestoreInt(int mask);
extern unsigned int __osVirtualToPhysical(void* addr);
extern void copyFunc(int rom_offset, int size, void* write_location);
extern void* getMapData(data_indexes data_idx, int _index, char compressbyte0, char compressbyte1);
extern void loadSetup(void* setup_file, int unk0, int unk1);
extern int getParentDataIndex(int map);

extern int* initDisplayList(int* dl);
extern int getTextStyleHeight(int style);
extern int* displayText(int* dl, int style, int x, int y, void* text_pointer, char unk0);
extern int* displayImage(int* dl, int texture_index, int unk3, codecs codec_index, int width, int height, int x, int y, float xScale, float yScale, int unk11, float unk12);
extern void getScreenPosition(float x, float y, float z, float* x_store, float* y_store, int unk8, float scale, char player_index);
extern int* textDraw(int* dl, int style, int x, int y, char* str);

//vanilla data
extern float TransitionSpeed;
extern char CutsceneWillPlay;
extern char KRoolRound;
extern KongBase MovesBase[6];
extern int PlayerOneColor;
extern char Mode;
extern char TBVoidByte;
extern int CurrentMap;
extern int DestMap;
extern int DestExit;
extern char StorySkip;
extern char HelmTimerShown;
extern char TempFlagBlock[0x10];
extern submapInfo SubmapData;
extern char HelmTimerPaused;
extern int LagBoost;
extern int FrameLag;
extern int FrameReal;
extern int RNG;
extern char BetaNinRWSkip;
extern char LogosDestMap;
extern char LogosDestMode;
extern char Gamemode;
extern int* ObjectModel2Pointer;
extern int ObjectModel2Timer;
extern int ObjectModel2Count;
extern int ObjectModel2Count_Dupe;
extern short CutsceneIndex;
extern char CutsceneActive;
extern cutsceneType* CutsceneTypePointer;
extern short PreviousCameraState;
extern short CurrentCameraState;
extern short CameraStateChangeTimer;
extern AutowalkData* AutowalkPointer;
extern char IsAutowalking;
extern WarpInfo PositionWarpInfo;
extern short PositionWarpBitfield;
extern float PositionFloatWarps[3];
extern unsigned short PositionFacingAngle;
extern char ChimpyCam;
extern char ScreenRatio;
extern int* CurrentActorPointer;
extern char LoadedActorCount;
extern loadedActorArr LoadedActorArray[64];
extern SpawnerMasterInfo SpawnerMasterData;
extern RGB MenuSkyTopRGB;
extern RGB MenuSkyRGB;
extern int* ActorArray[];
extern short ActorCount;
extern short ButtonsEnabledBitfield;
extern char JoystickEnabledX;
extern char JoystickEnabledY;
extern char MapState;
extern Controller ControllerInput;
extern Controller NewlyPressedControllerInput;
extern Controller PreviouslyPressedButtons;
extern playerData* Player;
extern SwapObjectData* SwapObject;
extern char Character;
extern cameraData* Camera;
extern char ISGActive;
extern unsigned int ISGTimestampMajor;
extern unsigned int ISGTimestampMinor;
extern char ISGPreviousFadeout;
extern unsigned int CurrentTimestampMajor;
extern unsigned int CurrentTimestampMinor;
extern ISGFadeoutData ISGFadeoutArray[];
extern InventoryBase CollectableBase;
extern char ModelTwoTouchCount;
extern short ModelTwoTouchArray[4];
extern char TransitionProgress;
extern Controller BackgroundHeldInput;
extern unsigned int PauseTimestampMajor;
extern unsigned int PauseTimestampMinor;
extern unsigned int HelmStartTimestampMajor;
extern unsigned int HelmStartTimestampMinor;
extern int HelmStartTime;
extern short p1PressedButtons;
extern short p1HeldButtons;
extern char player_count;
extern int* sprite_table[0xAF];
extern char sprite_translucency;
extern int* bbbandit_array[4];
extern char StoredDamage;
extern void* ActorSpawnerPointer;
extern char DebugInfoOn;
extern char CutsceneFadeActive;
extern short CutsceneFadeIndex;
extern heap* heap_pointer;
extern char stickX_magnitude;
extern char stickY_magnitude;
extern float phasewalk_stickmagnitude;
extern fairyInfo fairy_data;
extern short transferredActorType;
extern charSpawnerData characterSpawnerActors[0x71];
extern unsigned char levelIndexMapping[216];
extern char stickX_interpretted;
extern char stickY_interpretted;
extern char preventSongPlaying;
extern int parentDataCount;
extern parentMaps parentData[17];
extern void* SetupFilePointer;
extern int* focusedParentDataSetup[17];
extern hudData* HUD;
extern text_struct textData[6];
extern float LZFadeoutProgress;
extern int* mapFloorPointer;
extern int mapFloorBlockCount;
extern int displayListCount;
extern int IGT;
extern short CBTurnedInArray[8];
extern int* exitPointer;
extern int* BalloonPatchPointer;
extern int* ChunkArrayPointer;
extern char ActorMasterType[348];

extern short screenCenterX;
extern short screenCenterY;

extern short MapVoid_MinX;
extern short MapVoid_MinZ;
extern short MapVoid_MaxX;
extern short MapVoid_MaxZ;

extern char arcadeMap;
extern char arcadeMode;
extern char arcadeLevel;
extern arcadeObject arcadeObjBase[0x50];
extern char arcadeLives;
extern char arcadeLivesVisual;
extern int arcadeLevelTimer;
extern int arcadeGlobalTimer;
extern char arcadePause;
extern int arcadeRNG;
extern char arcadeJumpmanIndex;
extern int arcadeCurrentScore;
extern int arcadeHighScore;
extern char arcadeBonusTimer;
extern int arcadeSong;
extern int arcadeHammerTimer;
extern arcadeMoveFloorBase arcadeMovableFloor;
extern unsigned char arcadeRivetBitfield;

extern int jetpacMode;
extern competitor_struct competitors[2];
extern int jetpacLevelStartTimer;
extern jetpac_item1_struct jetpacObjectBase[20];
extern int jetpacPlayerIndex;

extern short objectSignalsCount;
extern short delayedKillsCount;
extern int lockStackCount;
extern short scriptsRunningCount;
extern unsigned char scriptsAttemptLoadCount;

//hack data
extern int TestVariable;
extern savedSettings StoredSettings;

extern TextOverlay* ActiveTools_Error;
extern char InBadMap;
extern char MenuSavestateAction;
extern char WatchIndex[4];
extern unsigned char NoVacantWatchTimer;
extern char InputDisplayType;
extern float AverageLag;
extern int ISGTimer;
extern char LagDocumentationIndex;
extern short StoredLag;
extern TimerInfo TimerData;
extern char StoredRound;
extern char DisablePositionButtons;
extern char DisableTagAnywhere;
extern int FrameAdvanceStart;
extern char DisableStartupSkip;
extern char DisableForcedStorySkip;
extern int* SandstormAddress;
extern char AutoPhaseStateOn;
extern GiantKoshaData* GiantKoshaTimerAddress;
extern short GiantKoshaTimerValue;
extern char MenuShortcutButtonsOff;
extern char FrameAdvancing;
extern char ArtificialPauseOn;
extern char InfiniteHealthCheatOn;
extern char LToLevitateOn;
extern ActiveMenuData ActiveMenu;
extern int NewMenu_ErrorStart;
extern char FocusedSavestate;
extern char AutoMoonkickOn;
extern char EnemySpawnOff;
extern PhaseCheckerData PhaseChecker;
extern char WatchTextSpace[4][0x30];
extern customFlagData CustomFlag;
extern char ISGStage;
extern char IsPauseMenuOpen;
extern short PreviousFrameButtons;
extern undoFlagData UndoFlag;
extern char LastLoadStateAction;
extern char PauseMenuMusicSetting;
extern char ClosingMenu;
extern char HasNeutralStickInput;
extern char TouchingGB;
extern char IsSuperspeedOn;
extern char LToCancelCSOn;
extern char LToToggleTBOn;
extern char LToEndGameOn;
extern unsigned int TempTimestampStorageMajor;
extern unsigned int TempTimestampStorageMinor;
extern TextOverlay* HackTitle;
extern TextOverlay* HackVersion;
extern int* graphicalOverlaySpace[32][3];
extern char Precision;
extern char LoadedHooks;
extern char PreviousLagArray[16];
extern char InputDisplayIndex;
extern char RAMDisplayOpen;
extern char LoadVarsOnMapLoad;
extern char ShowSavePrompts;
extern unsigned char SavePromptTimer;
extern TextOverlay* SavePromptActor;
extern char SavePromptIsSaving;
extern int* SpriteAddress;
extern char InputDisplayOpen;
extern char InputDisplayQuadrant;
extern char InputSpritesSpawned;
extern char TransformAutoRestockOff;
extern char KRoolRoundSetting;
extern char FileInitQOLOff;
extern char InputStickMax;
extern actorNames* ActorNamesTable;
extern actorNames* SnagNamesTable;
extern actorNames* SnagCapitalsTable;
extern actorData* FocusedActorViewPointer;
extern char ViewedSnagWatches[4];
extern char FlagLogCurrentFCounter;
extern char MinigameTimersInMS;
extern char ConvertTimerCountdown;
extern char FairyViewerOpen;
extern fairyInfo FairyViewerData;
extern actorData* FairyViewerFocus;
extern ActiveMenuData arcadeMenu;
extern int* MemoryViewerLastAddress;
extern console assignedConsole;
extern int* phasePointer;
extern short style128Mtx[0x10];
extern short style6Mtx[0x10];
extern short style2Mtx[0x10];
extern char watchActive;
extern char stateLoadTimer;
extern actorData* PausePointer;
extern char jetpacPaused;
extern char jetpacTimerState;
extern char jetmanColorIndex;
extern char disableMapGeometry;
extern int* customCollisionVerts;
extern int* vanillaVertBase;
extern unsigned char objectSignalsCountCopy;
extern unsigned char delayedKillsCountCopy;
extern unsigned char lockStackCountCopy;
extern char voidMapOn;
extern void* voidPointer;
extern char floorsPreloadedVanilla;
extern unsigned char savestateSettingsBitfield;
extern char voidsDisabled;

// Code
extern int debugColumnLoop;
extern int characterSpawnerMalloc;
extern char nfrTitleScreenSong;
extern int globalFlags[2];