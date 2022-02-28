/*
	This is an automatically generated file.
	Please don't make edits to this file directly as they will be overwritten at next build.
	To make amendments, see include/symbols.json and build/symbols_generator.py.
	Thanks.
	Stats:
		Functions: 65/106(61.32%)
		Vanilla Vars: 76/153(49.67%)
		Hack Vars: 107/107(100.0%)
		Code: 0/11(0.0%)
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
//.definelabel spawnTextOverlay
.definelabel dk_sqrt, 0x8000AED0
.definelabel dk_cos, 0x8000ABA0
.definelabel dk_sin, 0x8000AD10
.definelabel dk_strFormat, 0x800033F0
.definelabel dk_multiply, 0x80005B88
.definelabel convertTimestamp, 0x80005A88
.definelabel resetMap, 0x805FD974
.definelabel prepKongColoring, 0x80688788
.definelabel dk_memcpy, 0x80003210
.definelabel SaveToGlobal, 0x8060B8A8
.definelabel DetectGameOver, 0x80713A30
.definelabel DetectAdventure, 0x807139C8
//.definelabel displaySprite
.definelabel alterSize, 0x806CF45C
.definelabel unkSizeFunction, 0x806CEF90
.definelabel spawnRocketbarrel, 0x806C68EC
.definelabel playSong, 0x80600484
.definelabel playCutscene, 0x8061A6CC
//.definelabel setHUDItemAsInfinite
.definelabel osWritebackDCacheAll, 0x80005550
.definelabel copyFromROM, 0x80608B30
//.definelabel getActorSpawnerIDFromTiedActor
.definelabel textOverlayCode, 0x8069BF74
//.definelabel spawnTransferredActor
//.definelabel resolveMovementBox
.definelabel wipeMemory, 0x80005430
//.definelabel hideHUD
//.definelabel tagKong
//.definelabel clearGun
//.definelabel playAnimation
//.definelabel clearTagSlide
.definelabel initiateTransitionFade, 0x80711A88
//.definelabel __osInvalICache
.definelabel __osInvalDCache, 0x80004800
//.definelabel __osWritebackDCache
//.definelabel __osCreateMesgQueue
.definelabel __osRecvMesg, 0x800049A0
//.definelabel __osEPiStartDMA
//.definelabel __osPiRawReadIo
//.definelabel __osDisableInt
//.definelabel __osRestoreInt
//.definelabel __osVirtualToPhysical
.definelabel copyFunc, 0x805F8F90
.definelabel getMapData, 0x80669108
//.definelabel loadSetup
//.definelabel getParentDataIndex
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
//.definelabel deleteAllObjectModel2
//.definelabel deleteActorSpawner
//.definelabel deleteAllActorSpawners
.definelabel complexFree, 0x8060ED78
.definelabel getModel2AndActorInfo, 0x8062FBB8
.definelabel isBalloonOrPatch, 0x80686E84
.definelabel enableComplexFree, 0x80669434
.definelabel complexFreeWrapper, 0x80669444
.definelabel getWorld, 0x805FC9D0
.definelabel isSingleOrBunch, 0x8062FB18
.definelabel initDisplayList, 0x807128AC
//.definelabel getTextStyleHeight
//.definelabel displayText
.definelabel displayImage, 0x8068A87C
.definelabel textDraw, 0x806FCA98
//.definelabel setArcadeTextXY
//.definelabel spawnArcadeText
//.definelabel setArcadeTextColor
//.definelabel arcadeGetObjIndexOfType
//.definelabel arcadeGetNextVacantSlot
//.definelabel setArcadeSong
//.definelabel spawnJetpacText
//.definelabel setJetpacTextColor
//.definelabel startJetpacGame
//.definelabel placeJetpacFloor
//.definelabel resetJetpacVars
//.definelabel increaseLevel
//.definelabel spawnJetpacItem
//.definelabel resetJetpacMap
//.definelabel changeJetpacMode

//vanilla data
.definelabel TransitionSpeed, 0x807FDD1C
.definelabel CutsceneWillPlay, 0x807553FB
.definelabel KRoolRound, 0x807503B4
.definelabel MovesBase, 0x807FCDE0
.definelabel PlayerOneColor, 0x807553B4
.definelabel Mode, 0x807553D8
//.definelabel TBVoidByte
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
.definelabel LogosDestMap, 0X8071288F
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
.definelabel LoadedActorCount, 0x807FBFA5
.definelabel LoadedActorArray, 0x807FBDA0
//.definelabel SpawnerMasterData
//.definelabel MenuSkyTopRGB
//.definelabel MenuSkyRGB
.definelabel ActorArray, 0x807FC460
.definelabel ActorCount, 0x807FC860
//.definelabel ButtonsEnabledBitfield
//.definelabel JoystickEnabledX
//.definelabel JoystickEnabledY
.definelabel MapState, 0x8076A2A1
//.definelabel ControllerInput
//.definelabel NewlyPressedControllerInput
.definelabel Player, 0x807FBFBC
//.definelabel SwapObject
.definelabel Character, 0x8074E05C
//.definelabel Camera
.definelabel ISGActive, 0x80755130
//.definelabel ISGTimestampMajor
//.definelabel ISGTimestampMinor
//.definelabel ISGPreviousFadeout
//.definelabel CurrentTimestampMajor
//.definelabel CurrentTimestampMinor
//.definelabel ISGFadeoutArray
.definelabel CollectableBase, 0x807FD0D0
.definelabel ModelTwoTouchCount, 0x807FDC28
//.definelabel ModelTwoTouchArray
//.definelabel TransitionProgress
//.definelabel BackgroundHeldInput
//.definelabel PauseTimestampMajor
//.definelabel PauseTimestampMinor
.definelabel HelmStartTimestampMajor, 0x80755400
.definelabel HelmStartTimestampMinor, 0x80755404
.definelabel HelmStartTime, 0x8075540C
//.definelabel p1PressedButtons
//.definelabel p1HeldButtons
//.definelabel player_count
//.definelabel sprite_table
//.definelabel sprite_translucency
//.definelabel bbbandit_array
//.definelabel StoredDamage
.definelabel ActorSpawnerPointer, 0x807FC870
.definelabel DebugInfoOn, 0x8075648C
.definelabel CutsceneFadeActive, 0x807553FB
.definelabel CutsceneFadeIndex, 0x807553FE
//.definelabel PreviouslyPressedButtons
.definelabel heap_pointer, 0x807F0E00
//.definelabel stickX_magnitude
//.definelabel stickY_magnitude
//.definelabel phasewalk_stickmagnitude
.definelabel fairy_data, 0x807FDC94
.definelabel transferredActorType, 0x807FDA00
//.definelabel characterSpawnerActors
.definelabel levelIndexMapping, 0x80743EA0
//.definelabel stickX_interpretted
//.definelabel stickY_interpretted
//.definelabel preventSongPlaying
//.definelabel parentDataCount
//.definelabel parentData
.definelabel SetupFilePointer, 0x807F6480
//.definelabel focusedParentDataSetup
//.definelabel HUD
//.definelabel textData
.definelabel LZFadeoutProgress, 0x807FDD18
//.definelabel mapFloorPointer
//.definelabel mapFloorBlockCount
.definelabel displayListCount, 0x8076A278
.definelabel IGT, 0x80750390
//.definelabel CBTurnedInArray
//.definelabel exitPointer
//.definelabel BalloonPatchPointer
//.definelabel ChunkArrayPointer
.definelabel ActorMasterType, 0x8074D1B4
//.definelabel MapPropertiesBitfield
//.definelabel screenCenterX
//.definelabel screenCenterY
.definelabel MapVoid_MinX, 0x807F6454
.definelabel MapVoid_MinZ, 0x807F6456
.definelabel MapVoid_MaxX, 0x807F6458
.definelabel MapVoid_MaxZ, 0x807F645A
.definelabel balloonPatchCounts, 0x807FC878
.definelabel coloredBananaCounts, 0x807F65C0
.definelabel objectSignalsCount, 0x807FC448
.definelabel delayedKillsCount, 0x807FC380
.definelabel lockStackCount, 0x807F5ED8
//.definelabel scriptsRunningCount
//.definelabel scriptsAttemptLoadCount
//.definelabel arcadeMap
//.definelabel arcadeMode
//.definelabel arcadeLevel
//.definelabel arcadeObjBase
//.definelabel arcadeLives
//.definelabel arcadeLivesVisual
//.definelabel arcadeLevelTimer
//.definelabel arcadeGlobalTimer
//.definelabel arcadePause
//.definelabel arcadeRNG
//.definelabel arcadeJumpmanIndex
//.definelabel arcadeCurrentScore
//.definelabel arcadeHighScore
//.definelabel arcadeBonusTimer
//.definelabel arcadeSong
//.definelabel arcadeHammerTimer
//.definelabel arcadeMovableFloor
//.definelabel arcadeRivetBitfield
//.definelabel jetpacMode
//.definelabel jetpacLevelStartTimer
//.definelabel competitors
//.definelabel jetpacObjectBase
//.definelabel jetpacPlayerIndex
//.definelabel jetpacPlayerCount

//hack data
.definelabel ViewedSnagWatches, 0x807FFF18 // u8 x 4
.definelabel ActiveTools_Error, 0x807FFF1C // 0x4
.definelabel style128Mtx, 0x807FF900 // 0x20
.definelabel style6Mtx, 0x807FF920 // 0x20
.definelabel style2Mtx, 0x807FF940 // 0x20
.definelabel watchActive, 0x807FFF60 // u8
.definelabel stateLoadTimer, 0x807FFF61 // u8
.definelabel StoredSettings, 0x807ED5A0 // Follows savedSettings struct
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

// Code
//.definelabel debugColumnLoop
//.definelabel characterSpawnerMalloc
//.definelabel nfrTitleScreenSong
//.definelabel globalFlags
//.definelabel heapEndWrite
//.definelabel fileStartMap
//.definelabel fileStartExit
//.definelabel kongColor1
//.definelabel kongColor2
//.definelabel kongColor3
//.definelabel eepromPatch
