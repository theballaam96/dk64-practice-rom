/*
	This is an automatically generated file.
	Please don't make edits to this file directly as they will be overwritten at next build.
	To make amendments, see include/symbols.json and build/symbols_generator.py.
	Thanks.
	Stats:
		Functions: 95/121(78.51%)
		Vanilla Vars: 28/165(16.97%)
		Hack Vars: 110/110(100.0%)
		Code: 1/57(1.75%)
		Overall: 234/453(51.66%)
*/

//functions
.definelabel setFlag, 0x8072B9E0
.definelabel checkFlag, 0x8072B850
.definelabel dk_malloc, 0x8060A244
.definelabel dk_free, 0x8060A664
.definelabel playSound, 0x80602210
.definelabel initiateTransition, 0x805F83F8
.definelabel initiateTransition_0, 0x805F8A2C
.definelabel getFlagBlockAddress, 0x8060732C
.definelabel isAddressActor, 0x80674374
.definelabel getTimestamp, 0x800062C0
.definelabel dmaFileTransfer, 0x800004CC
.definelabel deleteActor, 0x80671A04
.definelabel spawnActor, 0x806713D8
.definelabel spawnTextOverlay, 0x806967D4
.definelabel dk_sqrt, 0x8000AE70
.definelabel dk_cos, 0x8000ABD0
.definelabel dk_sin, 0x8000ACB0
.definelabel dk_strFormat, 0x80003390
.definelabel dk_multiply, 0x80005B28
.definelabel convertTimestamp, 0x80005A28
.definelabel resetMap, 0x805F9054
.definelabel prepKongColoring, 0x80683948
.definelabel dk_memcpy, 0x800031B0
.definelabel SaveToGlobal, 0x80606F7C
.definelabel DetectGameOver, 0x8070E9E0
.definelabel DetectAdventure, 0x8070E978
//.definelabel displaySprite
.definelabel alterSize, 0x806CA610
.definelabel unkSizeFunction, 0x806CA144
.definelabel spawnRocketbarrel, 0x806C1B2C
.definelabel playSong, 0x805FBB64
.definelabel playCutscene, 0x80615F0C
.definelabel setHUDItemAsInfinite, 0x806F5A90
.definelabel osWritebackDCacheAll, 0x800054F0
.definelabel copyFromROM, 0x80604210
.definelabel getActorSpawnerIDFromTiedActor, 0x806822A8
.definelabel textOverlayCode, 0x80697130
.definelabel spawnTransferredActor, 0X806C2064
.definelabel resolveMovementBox, 0x80722988
.definelabel wipeMemory, 0x800053D0
.definelabel hideHUD, 0x806F59B0
.definelabel tagKong, 0x806C2DD8
.definelabel clearGun, 0x806EB318
.definelabel playAnimation, 0x8060E108
.definelabel clearTagSlide, 0x806CA144
.definelabel initiateTransitionFade, 0x8070CA38
.definelabel __osInvalICache, 0x80005470
.definelabel __osInvalDCache, 0x800047A0
.definelabel __osWritebackDCache, 0x80005880
.definelabel __osCreateMesgQueue, 0x80004BC0
.definelabel __osRecvMesg, 0x80004940
.definelabel __osEPiStartDMA, 0x80007120
.definelabel __osPiRawReadIo, 0x80004850
.definelabel __osDisableInt, 0x800091B0
.definelabel __osRestoreInt, 0x800091D0
.definelabel __osVirtualToPhysical, 0x80009330
.definelabel copyFunc, 0x805F4790
.definelabel getMapData, 0x80664528
.definelabel loadSetup, 0x80681B20
.definelabel getParentDataIndex, 0x80682160
.definelabel getScreenPosition, 0x80620290
.definelabel getNewSaveTime, 0x805F5A0C
.definelabel loadExits, 0x806C3550
.definelabel updateModel2Allowances, 0x8062B2CC
.definelabel handleSetup, 0x80681B20
.definelabel ObjectModel2Something, 0x8065D1C0
.definelabel loadEnemies, 0x8071F2C8
.definelabel extraEnemyParser, 0x80664864
.definelabel wipeActors, 0x806711B0
.definelabel spawnPersistentActors, 0x80683BF0
.definelabel spawnCameraAndKong, 0x806C1CC0
.definelabel resetModelTwoCollisions, 0x806EEE78
.definelabel updateCharChangeStruct, 0x80617D58
.definelabel resetDisplayLists, 0x805F75C4
.definelabel clearActorDL, 0x8060C9F4
.definelabel deleteActorContainer, 0x806716F0
.definelabel deleteAllObjectModel2, 0x8062E8A8
.definelabel deleteActorSpawner, 0x80682B50
.definelabel deleteAllActorSpawners, 0x80682CE8
.definelabel complexFree, 0x8060A568
.definelabel getModel2AndActorInfo, 0x8062B278
.definelabel isBalloonOrPatch, 0x806820C4
.definelabel enableComplexFree, 0x80664854
.definelabel complexFreeWrapper, 0x80664864
.definelabel getWorld, 0x805F80B0
.definelabel isSingleOrBunch, 0x8062B1D8
.definelabel initDisplayList, 0x8070D85C
.definelabel getTextStyleHeight, 0x806F7F04
.definelabel displayText, 0x806F6AB8
.definelabel displayImage, 0x80685A38
//.definelabel textDraw
.definelabel frameLoop, 0x805F5330
.definelabel getPointerTable14Texture, 0x806855BC
.definelabel cancelPausedCutscenes, 0x80615DD4
//.definelabel processPhase
.definelabel getParentMapIndexFromCurrentMap, 0x805F910C
.definelabel getCenterOffset, 0x806F6298
.definelabel setWaterHeight, 0x806588BC
//.definelabel updateObjectScript
//.definelabel executeBehaviourScript
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
//.definelabel jetpacInitDL
//.definelabel jetpacDrawFloors
//.definelabel jetpacDrawJetman
//.definelabel jetpacDrawEnemies
//.definelabel jetpacDrawRocket
//.definelabel jetpacUnkFunc

//vanilla data
//.definelabel TransitionSpeed
//.definelabel CutsceneWillPlay
//.definelabel KRoolRound
//.definelabel MovesBase
.definelabel PlayerOneColor, 0x8074FB74
.definelabel Mode, 0x8074FB98
//.definelabel TBVoidByte
.definelabel CurrentMap, 0x80764BC8
.definelabel DestMap, 0x8073EC34
.definelabel DestExit, 0x8073EC38
//.definelabel StorySkip
//.definelabel HelmTimerShown
.definelabel TempFlagBlock, 0x807FDCD0
//.definelabel SubmapData
//.definelabel HelmTimerPaused
//.definelabel LagBoost
.definelabel FrameLag, 0x80765A30
.definelabel FrameReal, 0x807627E4
.definelabel RNG, 0x807411A0
//.definelabel BetaNinRWSkip
//.definelabel LogosDestMap
//.definelabel LogosDestMode
.definelabel Gamemode, 0x8074FB94
//.definelabel ObjectModel2Pointer
//.definelabel ObjectModel2Timer
//.definelabel ObjectModel2Count
//.definelabel ObjectModel2Count_Dupe
//.definelabel CutsceneIndex
.definelabel CutsceneActive, 0x8073EC3C
//.definelabel CutsceneTypePointer
//.definelabel PreviousCameraState
//.definelabel CurrentCameraState
//.definelabel CameraStateChangeTimer
//.definelabel AutowalkPointer
//.definelabel IsAutowalking
//.definelabel PositionWarpInfo
//.definelabel PositionWarpBitfield
//.definelabel PositionFloatWarps
//.definelabel PositionFacingAngle
//.definelabel ChimpyCam
.definelabel ScreenRatio, 0x8073EC10
.definelabel CurrentActorPointer, 0x807FBA64
.definelabel LoadedActorCount, 0x807FBA54
.definelabel LoadedActorArray, 0x807FB850
//.definelabel SpawnerMasterData
//.definelabel MenuSkyTopRGB
//.definelabel MenuSkyRGB
//.definelabel ActorArray
//.definelabel ActorCount
//.definelabel ButtonsEnabledBitfield
//.definelabel JoystickEnabledX
//.definelabel JoystickEnabledY
.definelabel MapState, 0x80764BD1
//.definelabel ControllerInput
//.definelabel NewlyPressedControllerInput
//.definelabel Player
.definelabel SwapObject, 0x807FC864
//.definelabel Character
//.definelabel Camera
//.definelabel ISGActive
//.definelabel ISGTimestampMajor
//.definelabel ISGTimestampMinor
//.definelabel ISGPreviousFadeout
//.definelabel CurrentTimestampMajor
//.definelabel CurrentTimestampMinor
//.definelabel ISGFadeoutArray
//.definelabel CollectableBase
//.definelabel ModelTwoTouchCount
//.definelabel ModelTwoTouchArray
//.definelabel TransitionProgress
//.definelabel BackgroundHeldInput
//.definelabel PauseTimestampMajor
//.definelabel PauseTimestampMinor
//.definelabel HelmStartTimestampMajor
//.definelabel HelmStartTimestampMinor
//.definelabel HelmStartTime
//.definelabel p1PressedButtons
//.definelabel p1HeldButtons
.definelabel player_count, 0x807FC868
//.definelabel sprite_table
//.definelabel sprite_translucency
//.definelabel StoredDamage
.definelabel ActorSpawnerPointer, 0x807FC320
.definelabel DebugInfoOn, 0x80750C44
//.definelabel CutsceneFadeActive
//.definelabel CutsceneFadeIndex
//.definelabel PreviouslyPressedButtons
//.definelabel heap_pointer
//.definelabel stickX_magnitude
//.definelabel stickY_magnitude
//.definelabel phasewalk_stickmagnitude
//.definelabel fairy_data
//.definelabel transferredActorType
//.definelabel characterSpawnerActors
//.definelabel levelIndexMapping
//.definelabel stickX_interpretted
//.definelabel stickY_interpretted
.definelabel preventSongPlaying, 0x8073FDA0
//.definelabel parentDataCount
//.definelabel parentData
//.definelabel SetupFilePointer
//.definelabel focusedParentDataSetup
//.definelabel HUD
//.definelabel textData
.definelabel LZFadeoutProgress, 0x807FD7C8
//.definelabel mapFloorPointer
//.definelabel mapFloorBlockCount
.definelabel displayListCount, 0x80764BA8
//.definelabel IGT
//.definelabel CBTurnedInArray
//.definelabel exitPointer
//.definelabel BalloonPatchPointer
//.definelabel ChunkArrayPointer
//.definelabel ActorMasterType
//.definelabel MapPropertiesBitfield
//.definelabel screenCenterX
//.definelabel screenCenterY
//.definelabel MapVoid_MinX
//.definelabel MapVoid_MinZ
//.definelabel MapVoid_MaxX
//.definelabel MapVertsPointer
//.definelabel MapVoid_MaxZ
//.definelabel balloonPatchCounts
//.definelabel coloredBananaCounts
.definelabel objectSignalsCount, 0x807FBEF8
.definelabel delayedKillsCount, 0x807FBE30
//.definelabel lockStackCount
//.definelabel scriptsRunningCount
//.definelabel scriptsAttemptLoadCount
//.definelabel scriptsLoadedArray
//.definelabel StoredSettings
//.definelabel SetupCheck1
//.definelabel SetupCheck2
//.definelabel overlayArray
.definelabel heap_arena_count, 0x807F0948
.definelabel heap_arena_meta, 0x807F08A8
//.definelabel heap_end_pointer
//.definelabel fbufferPointers
.definelabel simpleLagCalcDisabled, 0x80765A34
//.definelabel DemoFadeoutTimer
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
//.definelabel jetpacStoryMode

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
//.definelabel bbbandit_array
//.definelabel boot_lui1
//.definelabel boot_lui2
//.definelabel setupCheckOverwrite
//.definelabel frameHookLocation
//.definelabel customBootCodeStart
//.definelabel bootJumpStart
//.definelabel bootJumpReturn
//.definelabel bootFinalValue
//.definelabel t4BootAddition
//.definelabel customLoopReturn
//.definelabel pauseHookWrite
//.definelabel flagHookWrite
//.definelabel spawnTimerHookWrite
//.definelabel phaseCorrectionHookWrite
//.definelabel arcadeHookWrite
//.definelabel jetpacHookWrite
//.definelabel pause97HookWrite
//.definelabel pause343HookWrite
//.definelabel loadSetupHookWrite
//.definelabel resolveBarrelHookWrite
//.definelabel fairyStoreHookWrite
//.definelabel displayListHookWrite
//.definelabel vertBaseStoreHookWrite
//.definelabel signalsStoreHookWrite
//.definelabel delayedKillsStoreHookWrite
//.definelabel lockStackStoreHookWrite
//.definelabel storeFloorPreloadHookWrite
//.definelabel giantKoshaHookWrite
//.definelabel lagHookWrite
//.definelabel saveHookWrite
//.definelabel spriteHookWrite
//.definelabel speedHookWrite
//.definelabel kongHookWrite
//.definelabel crcPatchMemory
//.definelabel crcPatchROM
//.definelabel displayListCap
//.definelabel lockedCamHookWrite
.definelabel overlayEntryPoint, 0x80017000
//.definelabel arcadeTextHookWrite
//.definelabel arcadeHasControlHookWrite
//.definelabel arcadeHasControl2HookWrite
//.definelabel arcadeHasControl3HookWrite
//.definelabel jetpacTextHookWrite
//.definelabel jetpacPauseHookWrite
//.definelabel jetpac5000HookWrite

