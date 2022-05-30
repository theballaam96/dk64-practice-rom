/*
	This is an automatically generated file.
	Please don't make edits to this file directly as they will be overwritten at next build.
	To make amendments, see include/symbols.json and build/symbols_generator.py.
	Thanks.
	Stats:
		Functions: 121/123(98.37%)
		Vanilla Vars: 166/168(98.81%)
		Hack Vars: 114/114(100.0%)
		Code: 58/60(96.67%)
		Overall: 459/465(98.71%)
*/

//functions
.definelabel setFlag, 0x80730A60
.definelabel checkFlag, 0x807308D0
.definelabel dk_malloc, 0x8060EA54
.definelabel dk_free, 0x8060EE74
.definelabel playSound, 0x80606B30
.definelabel initiateTransition, 0x805FCD18
.definelabel initiateTransition_0, 0x805FD34C
.definelabel getFlagBlockAddress, 0x8060BC6C
.definelabel isAddressActor, 0x806790F0
.definelabel getTimestamp, 0x80006320
.definelabel dmaFileTransfer, 0x800004CC
.definelabel deleteActor, 0x806766B4
.definelabel spawnActor, 0x80676088
.definelabel spawnTextOverlay, 0x8069B608
.definelabel dk_sqrt, 0x8000AED0
.definelabel dk_cos, 0x8000ABA0
.definelabel dk_sin, 0x8000AD10
.definelabel dk_strFormat, 0x800033F0
.definelabel dk_multiply, 0x80005B88
.definelabel convertTimestamp, 0x80005A88
.definelabel resetMap, 0x805FD974
.definelabel prepKongColoring, 0x80688778
.definelabel dk_memcpy, 0x80003210
.definelabel SaveToGlobal, 0x8060B8A8
.definelabel DetectGameOver, 0x80713A30
.definelabel DetectAdventure, 0x807139C8
.definelabel displaySprite, 0x806A9D04
.definelabel alterSize, 0x806CF45C
.definelabel unkSizeFunction, 0x806CEF90
.definelabel spawnRocketbarrel, 0x806C68EC
.definelabel playSong, 0x80600484
.definelabel playCutscene, 0x8061A6CC
.definelabel setHUDItemAsInfinite, 0x806FA9D4
.definelabel osWritebackDCacheAll, 0x80005550
.definelabel copyFromROM, 0x80608B30
.definelabel getActorSpawnerIDFromTiedActor, 0x80687068
.definelabel textOverlayCode, 0x8069BF74
.definelabel spawnTransferredActor, 0x806C6E28
.definelabel resolveMovementBox, 0x80727A18
.definelabel wipeMemory, 0x80005430
.definelabel hideHUD, 0x806FA8F4
.definelabel tagKong, 0x806C7B9C
.definelabel clearGun, 0x806F01D8
.definelabel playAnimation, 0x806128E8
.definelabel clearTagSlide, 0x806CEF90
.definelabel initiateTransitionFade, 0x80711A88
.definelabel __osInvalICache, 0x800054D0
.definelabel __osInvalDCache, 0x80004800
.definelabel __osWritebackDCache, 0x800058E0
.definelabel __osCreateMesgQueue, 0x80004C20
.definelabel __osRecvMesg, 0x800049A0
.definelabel __osEPiStartDMA, 0x80007180
.definelabel __osPiRawReadIo, 0x800048B0
.definelabel __osDisableInt, 0x80009210
.definelabel __osRestoreInt, 0x80009230
.definelabel __osVirtualToPhysical, 0x80009390
.definelabel copyFunc, 0x805F8F90
.definelabel getMapData, 0x80669108
.definelabel loadSetup, 0x806868E0
.definelabel getParentDataIndex, 0x80686F20
.definelabel getScreenPosition, 0x80624AC4
.definelabel getNewSaveTime, 0x805FA32C
.definelabel loadExits, 0x806C8314
.definelabel updateModel2Allowances, 0x8062FC0C
.definelabel handleSetup, 0x806868E0
.definelabel ObjectModel2Something, 0x80661D10
.definelabel loadEnemies, 0x807243E8
.definelabel extraEnemyParser, 0x80669444
.definelabel wipeActors, 0x80675E60
.definelabel spawnPersistentActors, 0x80688A20
.definelabel spawnCameraAndKong, 0x806C6A80
.definelabel resetModelTwoCollisions, 0x806F3D78
.definelabel updateCharChangeStruct, 0x8061C58C
.definelabel resetDisplayLists, 0x805FBEE4
.definelabel clearActorDL, 0x80611204
.definelabel deleteActorContainer, 0x806763A0
.definelabel deleteAllObjectModel2, 0x80633224
.definelabel deleteActorSpawner, 0x80687910
.definelabel deleteAllActorSpawners, 0x80687AA8
.definelabel complexFree, 0x8060ED78
.definelabel getModel2AndActorInfo, 0x8062FBB8
//.definelabel changeActorColor
.definelabel isBalloonOrPatch, 0x80686E84
.definelabel enableComplexFree, 0x80669434
.definelabel complexFreeWrapper, 0x80669444
.definelabel getWorld, 0x805FC9D0
.definelabel isSingleOrBunch, 0x8062FB18
.definelabel initDisplayList, 0x807128AC
.definelabel getTextStyleHeight, 0x806FCEC0
.definelabel displayText, 0x806FBA74
.definelabel displayImage, 0x8068A87C
.definelabel textDraw, 0x806FCA98
.definelabel frameLoop, 0x805F9B74
.definelabel getPointerTable14Texture, 0x8068A3EC
.definelabel cancelPausedCutscenes, 0x8061A594
.definelabel processPhase, 0x806DE764
//.definelabel renderActor
.definelabel getParentMapIndexFromCurrentMap, 0x805FDA2C
.definelabel getCenterOffset, 0x806FB184
.definelabel setWaterHeight, 0x8065F308
.definelabel updateObjectScript, 0x8063BDB0
.definelabel executeBehaviourScript, 0x8063BE0C
.definelabel setArcadeTextXY, 0x80017508
.definelabel spawnArcadeText, 0x8001751C
.definelabel setArcadeTextColor, 0x800174E4
.definelabel arcadeGetObjIndexOfType, 0x8001783C
.definelabel arcadeGetNextVacantSlot, 0x80017794
.definelabel setArcadeSong, 0x80018280
.definelabel spawnJetpacText, 0x8001DF1C
.definelabel setJetpacTextColor, 0x8001DEB4
.definelabel startJetpacGame, 0x8001763C
.definelabel placeJetpacFloor, 0x8001BC4C
.definelabel resetJetpacVars, 0x80017390
.definelabel increaseLevel, 0x800180B0
.definelabel spawnJetpacItem, 0x8001AD74
.definelabel resetJetpacMap, 0x8001A604
.definelabel changeJetpacMode, 0x80017F9C
.definelabel jetpacInitDL, 0x800185E4
.definelabel jetpacDrawFloors, 0x8001BE98
.definelabel jetpacDrawJetman, 0x80019AC0
.definelabel jetpacDrawEnemies, 0x8001DDAC
.definelabel jetpacDrawRocket, 0x8001B554
.definelabel jetpacUnkFunc, 0x80019D58

//vanilla data
.definelabel TransitionSpeed, 0x807FDD1C
.definelabel CutsceneWillPlay, 0x807553FB
.definelabel KRoolRound, 0x807503B4
.definelabel MovesBase, 0x807FCDE0
.definelabel PlayerOneColor, 0x807553B4
.definelabel Mode, 0x807553D8
.definelabel TBVoidByte, 0x807FBFD3
.definelabel CurrentMap, 0x8076A298
.definelabel DestMap, 0x80743DA4
.definelabel DestExit, 0x80743DA8
.definelabel StorySkip, 0x80743DEC
.definelabel HelmTimerShown, 0x80755410
.definelabel TempFlagBlock, 0x807FE220
.definelabel SubmapData, 0x8076A350
.definelabel HelmTimerPaused, 0x80713337
.definelabel LagBoost, 0x80743D38
.definelabel FrameLag, 0x8076B100
.definelabel FrameReal, 0x807F09D0
.definelabel RNG, 0x80746300
.definelabel BetaNinRWSkip, 0x807553E4
.definelabel LogosDestMap, 0x8071288F
.definelabel LogosDestMode, 0x8071289B
.definelabel Gamemode, 0x807553D4
.definelabel ObjectModel2Pointer, 0x807F6470
.definelabel ObjectModel2Timer, 0x8076A254
.definelabel ObjectModel2Count, 0x807F6474
.definelabel ObjectModel2Count_Dupe, 0x80747630
.definelabel CutsceneIndex, 0x80746FB4
.definelabel CutsceneActive, 0x80743DAC
.definelabel CutsceneTypePointer, 0x80746FBC
.definelabel PreviousCameraState, 0x807F6160
.definelabel CurrentCameraState, 0x807F6160
.definelabel CameraStateChangeTimer, 0x807F615C
.definelabel AutowalkPointer, 0x807FDB9C
.definelabel IsAutowalking, 0x80745C78
.definelabel PositionWarpInfo, 0x807FCDA8
.definelabel PositionWarpBitfield, 0x8076B0D2
.definelabel PositionFloatWarps, 0x8076B0D4
.definelabel PositionFacingAngle, 0x8076B0E0
.definelabel ChimpyCam, 0x80743DF0
.definelabel ScreenRatio, 0x80743D80
.definelabel CurrentActorPointer, 0x807FBFB4
.definelabel CurrentActorPointer_0, 0x807FBFB0
.definelabel LoadedActorCount, 0x807FBFA5
.definelabel LoadedActorArray, 0x807FBDA0
.definelabel SpawnerMasterData, 0x807FE118
.definelabel MenuSkyTopRGB, 0x8075500C
.definelabel MenuSkyRGB, 0x8075500F
.definelabel ActorArray, 0x807FC460
.definelabel ActorCount, 0x807FC860
.definelabel ButtonsEnabledBitfield, 0x807553C8
.definelabel JoystickEnabledX, 0x807553CC
.definelabel JoystickEnabledY, 0x807553D0
.definelabel MapState, 0x8076A2A1
.definelabel ControllerInput, 0x800150E4
.definelabel NewlyPressedControllerInput, 0x807ED1D6
.definelabel Player, 0x807FBFBC
.definelabel SwapObject, 0x807FCDB4
.definelabel Character, 0x8074E05C
.definelabel Camera, 0x807FBDD8
.definelabel ISGActive, 0x80755130
.definelabel ISGTimestampMajor, 0x807F6150
.definelabel ISGTimestampMinor, 0x807F6154
.definelabel ISGPreviousFadeout, 0x807F6184
.definelabel CurrentTimestampMajor, 0x80015300
.definelabel CurrentTimestampMinor, 0x80015304
.definelabel ISGFadeoutArray, 0x80746FC8
.definelabel CollectableBase, 0x807FD0D0
.definelabel ModelTwoTouchCount, 0x807FDC28
.definelabel ModelTwoTouchArray, 0x807FDC20
.definelabel TransitionProgress, 0x807ECE50
.definelabel BackgroundHeldInput, 0x807ED1B0
.definelabel PauseTimestampMajor, 0x80743E80
.definelabel PauseTimestampMinor, 0x80743E84
.definelabel HelmStartTimestampMajor, 0x80755400
.definelabel HelmStartTimestampMinor, 0x80755404
.definelabel HelmStartTime, 0x8075540C
.definelabel p1PressedButtons, 0x807ED1B8
.definelabel p1HeldButtons, 0x807ED1C8
.definelabel player_count, 0x807FCDB8
.definelabel sprite_table, 0x80755450
.definelabel sprite_translucency, 0x807FCC87
.definelabel StoredDamage, 0x807FD0DD
.definelabel ActorSpawnerPointer, 0x807FC870
.definelabel DebugInfoOn, 0x8075648C
.definelabel CutsceneFadeActive, 0x807553FB
.definelabel CutsceneFadeIndex, 0x807553FE
.definelabel PreviouslyPressedButtons, 0x807ED1D0
.definelabel heap_pointer, 0x807F0E00
.definelabel stickX_magnitude, 0x807FDAD0
.definelabel stickY_magnitude, 0x807FDAD1
.definelabel phasewalk_stickmagnitude, 0x807FDAA4
.definelabel fairy_data, 0x807FDC92
.definelabel transferredActorType, 0x807FDA00
.definelabel characterSpawnerActors, 0x8075ED40
.definelabel levelIndexMapping, 0x80743EA0
.definelabel stickX_interpretted, 0x807FDACE
.definelabel stickY_interpretted, 0x807FDACF
.definelabel preventSongPlaying, 0x80744F10
.definelabel parentDataCount, 0x807F5ED8
.definelabel parentData, 0x8076A350
.definelabel SetupFilePointer, 0x807F6480
.definelabel focusedParentDataSetup, 0x807F5EE0
.definelabel HUD, 0x80753B70
.definelabel textData, 0x80754B10
.definelabel LZFadeoutProgress, 0x807FDD18
.definelabel mapFloorPointer, 0x807F9984
.definelabel mapFloorBlockCount, 0x807F9988
.definelabel displayListCount, 0x8076A278
.definelabel IGT, 0x80750390
.definelabel CBTurnedInArray, 0x807FCDC0
.definelabel exitPointer, 0x807FCD90
.definelabel BalloonPatchPointer, 0x807FCA34
.definelabel ChunkArrayPointer, 0x807F7088
.definelabel ActorMasterType, 0x8074D1B4
.definelabel MapPropertiesBitfield, 0x807FBFD4
.definelabel screenCenterX, 0x80743D50
.definelabel screenCenterY, 0x80743D54
.definelabel MapVoid_MinX, 0x807F6454
.definelabel MapVoid_MinZ, 0x807F6456
.definelabel MapVoid_MaxX, 0x807F6458
.definelabel MapVoid_MaxZ, 0x807F645A
.definelabel MapVertsPointer, 0x807F6258
//.definelabel TriggerCount
//.definelabel TriggerArray
.definelabel balloonPatchCounts, 0x807FC878
.definelabel coloredBananaCounts, 0x807F65C0
.definelabel objectSignalsCount, 0x807FC448
.definelabel delayedKillsCount, 0x807FC380
.definelabel lockStackCount, 0x807F5ED8
.definelabel scriptsRunningCount, 0x807F6518
.definelabel scriptsAttemptLoadCount, 0x807F75B0
.definelabel scriptsLoadedArray, 0x807F6520
.definelabel StoredSettings, 0x807EDA10
.definelabel SetupCheck1, 0x8074F9D0
.definelabel SetupCheck2, 0x80747638
.definelabel overlayArray, 0x807FCAA0
.definelabel heap_arena_count, 0x807F0E98
.definelabel heap_arena_meta, 0x807F0DF8
.definelabel heap_end_pointer, 0x8076A250
.definelabel fbufferPointers, 0x80743D30
.definelabel simpleLagCalcDisabled, 0x8076B104
.definelabel DemoFadeoutTimer, 0x807553DC
.definelabel arcadeMap, 0x8003F4B3
.definelabel arcadeMode, 0x8003F4B4
.definelabel arcadeLevel, 0x8003D4FC
.definelabel arcadeObjBase, 0x8003EA60
.definelabel arcadeLives, 0x8003F4AB
.definelabel arcadeLivesVisual, 0x8003F4AC
.definelabel arcadeLevelTimer, 0x8003F46C
.definelabel arcadeGlobalTimer, 0x8003F468
.definelabel arcadePause, 0x8003F4AD
.definelabel arcadeRNG, 0x8003D4C8
.definelabel arcadeJumpmanIndex, 0x8003F4AF
.definelabel arcadeCurrentScore, 0x8003D4D8
.definelabel arcadeHighScore, 0x8003D4F0
.definelabel arcadeBonusTimer, 0x8003F4AE
.definelabel arcadeSong, 0x8003F4A4
.definelabel arcadeHammerTimer, 0x8003F4A0
.definelabel arcadeMovableFloor, 0x8003EA18
.definelabel arcadeRivetBitfield, 0x8003F4A8
.definelabel jetpacMode, 0x800223CC
.definelabel jetpacLevelStartTimer, 0x8002208C
.definelabel competitors, 0x80021C5C
.definelabel jetpacObjectBase, 0x80021F90
.definelabel jetpacPlayerIndex, 0x80021F84
.definelabel jetpacPlayerCount, 0x80021F88
.definelabel jetpacStoryMode, 0x800223D8

//hack data
.definelabel ViewedSnagWatches, 0x807FFF18 // u8 x 4
.definelabel ActiveTools_Error, 0x807FFF1C // 0x4
.definelabel style128Mtx, 0x807FF900 // 0x20
.definelabel style6Mtx, 0x807FF920 // 0x20
.definelabel style2Mtx, 0x807FF940 // 0x20
.definelabel watchActive, 0x807FFF60 // u8
.definelabel stateLoadTimer, 0x807FFF61 // u8
.definelabel TimerData, 0x807FFE90 // 0x14 bytes
.definelabel TestVariable, 0x807FFFFC // 0x4
.definelabel WatchIndex, 0x807FFFF8 // u8 x 4
.definelabel InBadMap, 0x807FFFF7 // u8 - Bool
.definelabel InputDisplayIndex, 0x807FFFF5 // u8
.definelabel RAMDisplayOpen, 0x807FFFF4 // u8
.definelabel LoadVarsOnMapLoad, 0x807FFFF3 // u8 - For savestates
.definelabel ShowSavePrompts, 0x807FFFF2 // u8
.definelabel SavePromptTimer, 0x807FFFF1 // u8
.definelabel SavePromptIsSaving, 0x807FFFF0 // u8
.definelabel LoadedHooks, 0x807FFFEF // u8
.definelabel Precision, 0x807FFFEE // u8
.definelabel NoVacantWatchTimer, 0x807FFFED // u8
.definelabel InputDisplayType, 0x807FFFEC // u8
.definelabel AverageLag, 0x807FFFE8 // f32
.definelabel SavePromptActor, 0x807FFFE4 // u32
.definelabel ISGTimer, 0x807FFFE0 // u32
.definelabel MinigameTimersInMS, 0x807FFFDF // u8
.definelabel LagDocumentationIndex, 0x807FFFDE // u8
.definelabel StoredLag, 0x807FFFDC // u16
.definelabel StoredRound, 0x807FFFDB // u8
.definelabel DisablePositionButtons, 0x807FFFDA // u8
.definelabel DisableTagAnywhere, 0x807FFFD9 // u8
.definelabel InputDisplayOpen, 0x807FFFD8 // u8
.definelabel InputDisplayQuadrant, 0x807FFFD7 // u8
.definelabel InputSpritesSpawned, 0x807FFFD6 // u8
.definelabel TransformAutoRestockOff, 0x807FFFD5 // u8
.definelabel KRoolRoundSetting, 0x807FFFD4 // u8
.definelabel FileInitQOLOff, 0x807FFFD3 // u8
.definelabel InputStickMax, 0x807FFFD2 // u8
.definelabel ConvertTimerCountdown, 0x807FFFD1 // u8
.definelabel FairyViewerOpen, 0x807FFFD0 // u8
.definelabel ActorNamesTable, 0x807FFFCC // u32 ptr
.definelabel FrameAdvanceStart, 0x807FFFC8 // u32
.definelabel DisableStartupSkip, 0x807FFFC7 // u8
.definelabel DisableForcedStorySkip, 0x807FFFC6 // u8
.definelabel SnagNamesTable, 0x807FFFC0 // u32 ptr
.definelabel SandstormAddress, 0x807FFDFC // u32
.definelabel AutoPhaseStateOn, 0x807FFDF8 // u8
.definelabel GiantKoshaTimerAddress, 0x807FFDF4 // u32
.definelabel GiantKoshaTimerValue, 0x807FFDF2 // u16
.definelabel FocusedActorViewPointer, 0x807FFDE8 // u32
.definelabel FlagLogCurrentFCounter, 0x807FFDDC // u8
.definelabel MenuShortcutButtonsOff, 0x807FFDDB // u8
.definelabel FrameAdvancing, 0x807FFDDA // u8
.definelabel ArtificialPauseOn, 0x807FFDD9 // u8
.definelabel InfiniteHealthCheatOn, 0x807FFDD8 // u8
.definelabel LToLevitateOn, 0x807FFDD7 // u8
.definelabel NewMenu_ErrorStart, 0x807FFDC0 // u32
.definelabel FocusedSavestate, 0x807FFDBF // u8
.definelabel AutoMoonkickOn, 0x807FFDBE // u8
.definelabel EnemySpawnOff, 0x807FFDBD // u8
.definelabel CustomFlag, 0x807FFF80 // 0x5 follows customflagdata struct
.definelabel ISGStage, 0x807FFF85 // u8
.definelabel IsPauseMenuOpen, 0x807FFF86 // u8
.definelabel PreviousFrameButtons, 0x807FFF88 // u16
.definelabel LastLoadStateAction, 0x807FFF8F // u8
.definelabel PauseMenuMusicSetting, 0x807FFF90 // u8
.definelabel ClosingMenu, 0x807FFF91 // u8
.definelabel HasNeutralStickInput, 0x807FFF92 // u8
.definelabel TouchingGB, 0x807FFF93 // u8
.definelabel IsSuperspeedOn, 0x807FFF94 // u8
.definelabel LToCancelCSOn, 0x807FFF95 // u8
.definelabel LToToggleTBOn, 0x807FFF96 // u8
.definelabel LToEndGameOn, 0x807FFF97 // u8
.definelabel TempTimestampStorageMajor, 0x807FFF98 // u32
.definelabel TempTimestampStorageMinor, 0x807FFF9C // u32
.definelabel HackTitle, 0x807FFFA0 // u32
.definelabel HackVersion, 0x807FFFA4 // u32
.definelabel SnagCapitalsTable, 0x807FFFA8 // u32
.definelabel SpriteAddress, 0x807FFFAC // u32
.definelabel PreviousLagArray, 0x807FFFB0 // u8 x 16
.definelabel PausePointer, 0x807FFB80 // ptr
.definelabel WatchTextSpace, 0x807FFB90 // 0x30 x 4
.definelabel PhaseChecker, 0x807FFC50 // 0x7 follows phasecheckerdata struct
.definelabel UndoFlag, 0x807FFC58 // u16
.definelabel FairyViewerData, 0x807FFC60 // 0x6 fairyInfo Struct
.definelabel FairyViewerFocus, 0x807FFC68 // ptr
.definelabel MemoryViewerLastAddress, 0x807FFC70 // ptr
.definelabel assignedConsole, 0x807FFC74 // u32
.definelabel phasePointer, 0x807FFC78 // ptr
.definelabel jetpacPaused, 0x807FFC7C // u8
.definelabel jetpacTimerState, 0x807FFC7D // u8
.definelabel jetmanColorIndex, 0x807FFC7E // u8
.definelabel disableMapGeometry, 0x807FFC7F // u8
.definelabel triggers_viewable, 0x807FFF8D // u8
.definelabel customCollisionVerts, 0x807FFC80 // ptr
.definelabel vanillaVertBase, 0x807FFC84 // ptr
.definelabel objectSignalsCountCopy, 0x807FFC88 // u8
.definelabel delayedKillsCountCopy, 0x807FFC89 // u8
.definelabel lockStackCountCopy, 0x807FFC8A // u8
.definelabel voidMapOn, 0x807FFC8B // u8
.definelabel voidPointer, 0x807FFC8C // ptr
.definelabel floorsPreloadedVanilla, 0x807FFC90 // u8
.definelabel savestateSettingsBitfield, 0x807FFC91 // u8
.definelabel voidsDisabled, 0x807FFC92 // u8
.definelabel disableCustomSFX, 0x807FFC93 // u8
.definelabel disableSavestateCombo, 0x807FFFC4 // u8
.definelabel ActiveMenu, 0x807FFDC4 // 0x6
.definelabel arcadeMenu, 0x807FFDDD // 0x6
.definelabel textboxCancel, 0x807FFDF9 // u8
.definelabel scriptsNotAutoloading, 0x807FFF8A // u8
.definelabel disableLockedCam, 0x807FFF8B // u8
.definelabel dynamic_watches, 0x807FFEB0 // 0x8 x 4
.definelabel doubleBeaverEnabledBitfield, 0x807FFF8C // u8
.definelabel altCollisionEnabled, 0x807FFF62 // u8
.definelabel collisiondrawmode, 0x807FFF63 // u8

// Code
.definelabel debugColumnLoop, 0x80731720
.definelabel characterSpawnerMalloc, 0x80727E0C
.definelabel nfrTitleScreenSong, 0x807455E0
.definelabel globalFlags, 0x807ED9C8
.definelabel heapEndWrite, 0x8060DF72
.definelabel fileStartMap, 0x80713BE3
.definelabel fileStartExit, 0x80713BF7
.definelabel kongColor1, 0x8068889F
.definelabel kongColor2, 0x806886C0
.definelabel kongColor3, 0x806886C8
.definelabel eepromPatch, 0x8060AF88
.definelabel bbbandit_array, 0x80020C60
.definelabel boot_lui1, 0x8001
.definelabel boot_lui2, 0xDF34
.definelabel setupCheckOverwrite, 0x805FC4A0
.definelabel frameHookLocation, 0x805F99F0
.definelabel customBootCodeStart, 0x80000AD0
.definelabel bootJumpStart, 0x8000081C
.definelabel bootJumpReturn, 0x8000083C
.definelabel bootFinalValue, 0xE
.definelabel t4BootAddition, 0x1620
.definelabel customLoopReturn, 0x805F99F8
.definelabel pauseHookWrite, 0x805FA230
.definelabel flagHookWrite, 0x80730A60
.definelabel spawnTimerHookWrite, 0x806A1168
.definelabel phaseCorrectionHookWrite, 0x806DF90C
.definelabel arcadeHookWrite, 0x805F99D0
.definelabel jetpacHookWrite, 0x805F99E0
.definelabel pause97HookWrite, 0x806A6928
.definelabel pause343HookWrite, 0x806ABB6C
.definelabel loadSetupHookWrite, 0x80686914
.definelabel resolveBarrelHookWrite, 0x80686F64
.definelabel fairyStoreHookWrite, 0x806C4AAC
.definelabel displayListHookWrite, 0x80713818
.definelabel vertBaseStoreHookWrite, 0x8062CE6C
.definelabel signalsStoreHookWrite, 0x806774F0
.definelabel delayedKillsStoreHookWrite, 0x806764AC
.definelabel lockStackStoreHookWrite, 0x8060E460
.definelabel storeFloorPreloadHookWrite, 0x806640DC
.definelabel giantKoshaHookWrite, 0x80643DB4
.definelabel lagHookWrite, 0x805FE024
.definelabel saveHookWrite, 0x8060B8CC
.definelabel spriteHookWrite, 0x806A9FE8
.definelabel speedHookWrite, 0x806632C4
.definelabel kongHookWrite, 0x806F2D10
.definelabel crcPatchMemory, 0x80002624
.definelabel crcPatchROM, 0x3224
.definelabel displayListCap, 0x805FC380
.definelabel lockedCamHookWrite, 0x8061D1E0
.definelabel overlayEntryPoint, 0x80017000
.definelabel arcadeTextHookWrite, 0x800249C0
.definelabel arcadeHasControlHookWrite, 0x800183EC
.definelabel arcadeHasControl2HookWrite, 0x800182D0
.definelabel arcadeHasControl3HookWrite, 0x8001A8F0
.definelabel jetpacTextHookWrite, 0x80018364
.definelabel jetpacPauseHookWrite, 0x80017954
.definelabel jetpac5000HookWrite, 0x8001ADC0
.definelabel doubleBeaverHookWrite, 0x806AC298
//.definelabel guardStoreHookWrite
//.definelabel guardLightHookWrite

.definelabel customCodeStart, 0x805d5600
.definelabel customCodeUpper, 0x805d
.definelabel customCodeLower, 0x5600
.definelabel customCodeSize, 0x23000
