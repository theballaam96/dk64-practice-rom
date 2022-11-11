/*
	This is an automatically generated file.
	Please don't make edits to this file directly as they will be overwritten at next build.
	To make amendments, see include/symbols.json and build/symbols_generator.py.
	Thanks.
	Stats:
		Functions: 125/125(100.0%)
		Vanilla Vars: 175/175(100.0%)
		Hack Vars: 116/116(100.0%)
		Code: 62/62(100.0%)
		Overall: 478/478(100.0%)
*/

//functions
.definelabel setFlag, 0x8073129C
.definelabel checkFlag, 0x8073110C
.definelabel dk_malloc, 0x80610FE8
.definelabel dk_free, 0x80611408
.definelabel playSound, 0x80609140
.definelabel initiateTransition, 0x805FF378
.definelabel initiateTransition_0, 0x805FF9AC
.definelabel getFlagBlockAddress, 0x8060E25C
.definelabel isAddressActor, 0x8067AF44
.definelabel getTimestamp, 0x800060B0
.definelabel dmaFileTransfer, 0x80000450
.definelabel deleteActor, 0x806785D4
.definelabel checkParent, 0x805FFE50
.definelabel getRNGLower31, 0x80611A44
.definelabel spawnActor, 0x80677FA8
.definelabel spawnTextOverlay, 0x8069D0F8
.definelabel dk_sqrt, 0x8000AC60
.definelabel dk_cos, 0x8000A930
.definelabel dk_sin, 0x8000AAA0
.definelabel dk_strFormat, 0x800031E0
.definelabel dk_multiply, 0x80005918
.definelabel convertTimestamp, 0x80005818
.definelabel resetMap, 0x805FFFC8
.definelabel prepKongColoring, 0x8068A508
.definelabel dk_memcpy, 0x80003000
.definelabel SaveToGlobal, 0x8060DEA8
.definelabel DetectGameOver, 0x80714394
.definelabel DetectAdventure, 0x8071432C
.definelabel displaySprite, 0x806AB4EC
.definelabel alterSize, 0x806D0468
.definelabel unkSizeFunction, 0x806CFF9C
.definelabel spawnRocketbarrel, 0x806C7BAC
.definelabel playSong, 0x80602A94
.definelabel playCutscene, 0x8061CC40
.definelabel setHUDItemAsInfinite, 0x806FB370
.definelabel osWritebackDCacheAll, 0x800052E0
.definelabel copyFromROM, 0x8060B140
.definelabel getActorSpawnerIDFromTiedActor, 0x80688E68
.definelabel textOverlayCode, 0x8069DA54
.definelabel spawnTransferredActor, 0x806C80E4
.definelabel resolveMovementBox, 0x8072827C
.definelabel wipeMemory, 0x800051C0
.definelabel hideHUD, 0x806FB218
.definelabel tagKong, 0x806C8E58
.definelabel clearGun, 0x806F0C18
.definelabel playAnimation, 0x80614E78
.definelabel clearTagSlide, 0x806CFF9C
.definelabel initiateTransitionFade, 0x807124B8
.definelabel __osInvalICache, 0x80005260
.definelabel __osInvalDCache, 0x80004520
.definelabel __osWritebackDCache, 0x80005670
.definelabel __osCreateMesgQueue, 0x80004950
.definelabel __osRecvMesg, 0x800046C0
.definelabel __osEPiStartDMA, 0x80006F10
.definelabel __osPiRawReadIo, 0x800045D0
.definelabel __osDisableInt, 0x80009020
.definelabel __osRestoreInt, 0x80009040
.definelabel __osVirtualToPhysical, 0x80008FA0
.definelabel copyFunc, 0x805FB750
.definelabel getMapData, 0x8066B0F8
.definelabel loadSetup, 0x806886E0
.definelabel getParentDataIndex, 0x80688D20
.definelabel getScreenPosition, 0x80626F8C
.definelabel getNewSaveTime, 0x805FC98C
.definelabel loadExits, 0x806C95D0
.definelabel updateModel2Allowances, 0x80631FAC
.definelabel handleSetup, 0x806886E0
.definelabel ObjectModel2Something, 0x80663DA0
.definelabel loadEnemies, 0x80724C78
.definelabel extraEnemyParser, 0x8066B434
.definelabel wipeActors, 0x80677D80
.definelabel spawnPersistentActors, 0x8068A7B0
.definelabel spawnCameraAndKong, 0x806C7D40
.definelabel resetModelTwoCollisions, 0x806F4778
.definelabel updateCharChangeStruct, 0x8061EA78
.definelabel resetDisplayLists, 0x805FE544
.definelabel clearActorDL, 0x80613794
.definelabel deleteActorContainer, 0x806782C0
.definelabel deleteAllObjectModel2, 0x80635588
.definelabel deleteActorSpawner, 0x80689710
.definelabel deleteAllActorSpawners, 0x806898A8
.definelabel complexFree, 0x8061130C
.definelabel getModel2AndActorInfo, 0x80631F58
.definelabel changeActorColor, 0x807149C8
.definelabel isBalloonOrPatch, 0x80688C84
.definelabel enableComplexFree, 0x8066B424
.definelabel complexFreeWrapper, 0x8066B434
.definelabel getWorld, 0x805FF030
.definelabel isSingleOrBunch, 0x80631EB8
.definelabel initDisplayList, 0x807132DC
.definelabel getTextStyleHeight, 0x806FD894
.definelabel displayText, 0x806FC530
.definelabel displayImage, 0x8068C5A8
.definelabel textDraw, 0x806FD490
.definelabel frameLoop, 0x805FC2B0
.definelabel getPointerTable14Texture, 0x8068C12C
.definelabel cancelPausedCutscenes, 0x8061CB08
.definelabel processPhase, 0x806DF494
.definelabel renderActor, 0x806319C4
.definelabel getParentMapIndexFromCurrentMap, 0x80600080
.definelabel getCenterOffset, 0x806FBD5C
.definelabel setWaterHeight, 0x80661398
.definelabel updateObjectScript, 0x8063E078
.definelabel executeBehaviourScript, 0x8063E0D4
.definelabel setArcadeTextXY, 0x80024508
.definelabel spawnArcadeText, 0x8002451C
.definelabel setArcadeTextColor, 0x800244E4
.definelabel arcadeGetObjIndexOfType, 0x80024860
.definelabel arcadeGetNextVacantSlot, 0x800247B8
.definelabel setArcadeSong, 0x800252A4
.definelabel spawnJetpacText, 0x8002AEFC
.definelabel setJetpacTextColor, 0x8002AE94
.definelabel startJetpacGame, 0x8002463C
.definelabel placeJetpacFloor, 0x80028C3C
.definelabel resetJetpacVars, 0x80024390
.definelabel increaseLevel, 0x800250A0
.definelabel spawnJetpacItem, 0x80027D64
.definelabel resetJetpacMap, 0x800275F4
.definelabel changeJetpacMode, 0x80024F9C
.definelabel jetpacInitDL, 0x800255D4
.definelabel jetpacDrawFloors, 0x80028E88
.definelabel jetpacDrawJetman, 0x80026AB0
.definelabel jetpacDrawEnemies, 0x8002AD8C
.definelabel jetpacDrawRocket, 0x80028544
.definelabel jetpacUnkFunc, 0x80026D48

//vanilla data
.definelabel TransitionSpeed, 0x807FD88C
.definelabel CutsceneWillPlay, 0x8075533B
.definelabel KRoolRound, 0x80750AD4
.definelabel MovesBase, 0x807FC950
.definelabel PlayerOneColor, 0x807552F4
.definelabel Mode, 0x80755318
.definelabel TBVoidByte, 0x807FBB63
.definelabel CurrentMap, 0x8076A0A8
.definelabel DestMap, 0x807444E4
.definelabel DestExit, 0x807444E8
.definelabel StorySkip, 0x8074452C
.definelabel HelmTimerShown, 0x80755350
.definelabel TempFlagBlock, 0x807FDD90
.definelabel SubmapData, 0x8076A160
.definelabel HelmTimerPaused, 0x80713C9B
.definelabel LagBoost, 0x80744478
.definelabel FrameLag, 0x8076AF10
.definelabel FrameReal, 0x80767CC4
.definelabel RNG, 0x80746A40
.definelabel BetaNinRWSkip, 0x80755324
.definelabel LogosDestMap, 0x807132BF
.definelabel LogosDestMode, 0x807132CB
.definelabel Gamemode, 0x80755314
.definelabel ObjectModel2Pointer, 0x807F6000
.definelabel ObjectModel2Timer, 0x8076A064
.definelabel ObjectModel2Count, 0x807F6004
.definelabel ObjectModel2Count_Dupe, 0x80747D70
.definelabel CutsceneIndex, 0x807476F4
.definelabel CutsceneActive, 0x807444EC
.definelabel CutsceneTypePointer, 0x807476FC
.definelabel PreviousCameraState, 0x807F5CF0
.definelabel CurrentCameraState, 0x807F5CF2
.definelabel CameraStateChangeTimer, 0x807F5CEC
.definelabel AutowalkPointer, 0x807FD70C
.definelabel IsAutowalking, 0x807463B8
.definelabel PositionWarpInfo, 0x807FC918
.definelabel PositionWarpBitfield, 0x8076AEE2
.definelabel PositionFloatWarps, 0x8076AEE4
.definelabel PositionFacingAngle, 0x8076AEF0
.definelabel ChimpyCam, 0x80744530
.definelabel ScreenRatio, 0x807444C0
.definelabel CurrentActorPointer, 0x807FBB44
.definelabel CurrentActorPointer_0, 0x807FBB40
.definelabel LoadedActorCount, 0x807FBB35
.definelabel LoadedActorArray, 0x807FB930
.definelabel SpawnerMasterData, 0x807FDC88
.definelabel MenuSkyTopRGB, 0x80754F4C
.definelabel MenuSkyRGB, 0x80754F4F
.definelabel ActorArray, 0x807FBFF0
.definelabel ActorCount, 0x807FC3F0
.definelabel ButtonsEnabledBitfield, 0x80755308
.definelabel JoystickEnabledX, 0x8075530C
.definelabel JoystickEnabledY, 0x80755310
.definelabel MapState, 0x8076A0B1
.definelabel ControllerInput, 0x80014DC4
.definelabel NewlyPressedControllerInput, 0x807ECD66
.definelabel Player, 0x807FBB4C
.definelabel SwapObject, 0x807FC924
.definelabel Character, 0x8074E77C
.definelabel Camera, 0x807FB968
.definelabel ISGActive, 0x80755070
.definelabel ISGTimestampMajor, 0x807F5CE0
.definelabel ISGTimestampMinor, 0x807F5CE4
.definelabel ISGPreviousFadeout, 0x807F5D14
.definelabel CurrentTimestampMajor, 0x80014FE0
.definelabel CurrentTimestampMinor, 0x80014FE4
.definelabel ISGFadeoutArray, 0x80747708
.definelabel CollectableBase, 0x807FCC40
.definelabel ModelTwoTouchCount, 0x807FD798
.definelabel ModelTwoTouchArray, 0x807FD790
.definelabel TransitionProgress, 0x807ECC60
.definelabel BackgroundHeldInput, 0x807ECD40
.definelabel PauseTimestampMajor, 0x807445C0
.definelabel PauseTimestampMinor, 0x807445C4
.definelabel HelmStartTimestampMajor, 0x80755340
.definelabel HelmStartTimestampMinor, 0x80755344
.definelabel HelmCurrentTime, 0x80755348
.definelabel HelmStartTime, 0x8075534C
.definelabel p1PressedButtons, 0x807ECD48
.definelabel p1HeldButtons, 0x807ECD58
.definelabel player_count, 0x807FC928
.definelabel sprite_table, 0x80755390
.definelabel sprite_translucency, 0x807FC80F
.definelabel StoredDamage, 0x807FCC4D
.definelabel ActorSpawnerPointer, 0x807FC400
.definelabel DebugInfoOn, 0x807563B4
.definelabel CutsceneFadeActive, 0x8075533B
.definelabel CutsceneFadeIndex, 0x8075533E
.definelabel PreviouslyPressedButtons, 0x807ECD60
.definelabel heap_pointer, 0x807F0990
.definelabel stickX_magnitude, 0x807FD640
.definelabel stickY_magnitude, 0x807FD641
.definelabel phasewalk_stickmagnitude, 0x807FD614
.definelabel fairy_data, 0x807FD802
.definelabel transferredActorType, 0x807FD570
.definelabel characterSpawnerActors, 0x8075EB80
.definelabel levelIndexMapping, 0x807445E0
.definelabel stickX_interpretted, 0x807FD63E
.definelabel stickY_interpretted, 0x807FD63F
.definelabel preventSongPlaying, 0x80745650
.definelabel parentDataCount, 0x807F5A68
.definelabel parentData, 0x8076A160
.definelabel SetupFilePointer, 0x807F6010
.definelabel focusedParentDataSetup, 0x807F5A70
.definelabel HUD, 0x80754280
.definelabel textData, 0x80754A34
.definelabel LZFadeoutProgress, 0x807FD888
.definelabel mapFloorPointer, 0x807F9514
.definelabel mapFloorBlockCount, 0x807F9518
.definelabel displayListCount, 0x8076A088
.definelabel IGT, 0x80750AB0
.definelabel CBTurnedInArray, 0x807FC930
.definelabel exitPointer, 0x807FC900
.definelabel BalloonPatchPointer, 0x807FC5C4
.definelabel ChunkArrayPointer, 0x807F6C18
.definelabel ActorMasterType, 0x8074D8D4
.definelabel MapPropertiesBitfield, 0x807FBB64
.definelabel screenCenterX, 0x80744490
.definelabel screenCenterY, 0x80744494
.definelabel MapVoid_MinX, 0x807F5FE4
.definelabel MapVoid_MinZ, 0x807F5FE6
.definelabel MapVoid_MaxX, 0x807F5FE8
.definelabel MapVoid_MaxZ, 0x807F5FEA
.definelabel MapVertsPointer, 0x807F5DE8
.definelabel TriggerCount, 0x807FDCB0
.definelabel TriggerArray, 0x807FDCB4
.definelabel DKTVCounter, 0x80755328
.definelabel EEPROMSlots, 0x807EDEA8
.definelabel File, 0x807467C8
.definelabel EEPROMStorage, 0x807ED6A8
.definelabel balloonPatchCounts, 0x807FC408
.definelabel coloredBananaCounts, 0x807F6150
.definelabel objectSignalsCount, 0x807FBFD8
.definelabel delayedKillsCount, 0x807FBF10
.definelabel lockStackCount, 0x807F5A68
.definelabel scriptsRunningCount, 0x807F60A8
.definelabel scriptsAttemptLoadCount, 0x807F7140
.definelabel scriptsLoadedArray, 0x807F60B0
.definelabel PlayerCollisions, 0x807FD740
.definelabel ModelTwoCollisionInfo, 0x80753EF0
.definelabel StoredSettings, 0x807ED5A0
.definelabel SetupCheck1, 0x807500B0
.definelabel SetupCheck2, 0x80747D78
.definelabel overlayArray, 0x807FC630
.definelabel heap_arena_count, 0x807F0A28
.definelabel heap_arena_meta, 0x807F0988
.definelabel heap_end_pointer, 0x8076A060
.definelabel fbufferPointers, 0x80744470
.definelabel simpleLagCalcDisabled, 0x8076AF14
.definelabel DemoFadeoutTimer, 0x8075531C
.definelabel arcadeMap, 0x8004C723
.definelabel arcadeMode, 0x8004C724
.definelabel arcadeLevel, 0x8004A76C
.definelabel arcadeObjBase, 0x8004BCD0
.definelabel arcadeLives, 0x8004C71B
.definelabel arcadeLivesVisual, 0x8004C71C
.definelabel arcadeLevelTimer, 0x8004C6DC
.definelabel arcadeGlobalTimer, 0x8004C6D8
.definelabel arcadePause, 0x8004C71D
.definelabel arcadeRNG, 0x8004A738
.definelabel arcadeJumpmanIndex, 0x8004C71F
.definelabel arcadeCurrentScore, 0x8004A748
.definelabel arcadeHighScore, 0x8004A760
.definelabel arcadeBonusTimer, 0x8004C71E
.definelabel arcadeSong, 0x8004C714
.definelabel arcadeHammerTimer, 0x8004C710
.definelabel arcadeMovableFloor, 0x8004BC88
.definelabel arcadeRivetBitfield, 0x8004C718
.definelabel jetpacMode, 0x8002F3BC
.definelabel jetpacLevelStartTimer, 0x8002F07C
.definelabel competitors, 0x8002EC4C
.definelabel jetpacObjectBase, 0x8002EF80
.definelabel jetpacPlayerIndex, 0x8002EF74
.definelabel jetpacPlayerCount, 0x8002EF78
.definelabel jetpacStoryMode, 0x8002F3C8

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
.definelabel modeltwo_viewable, 0x807FFF8E // u8
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
.definelabel disablelightning, 0x807FFF64 // u8

// Code
.definelabel debugColumnLoop, 0x80731F78
.definelabel characterSpawnerMalloc, 0x80728670
.definelabel nfrTitleScreenSong, 0x80745D20
.definelabel globalFlags, 0x807ED558
.definelabel heapEndWrite, 0x80610512
.definelabel fileStartMap, 0x80714547
.definelabel fileStartExit, 0x8071455B
.definelabel kongColor1, 0x8068A62F
.definelabel kongColor2, 0x8068A450
.definelabel kongColor3, 0x8068A458
.definelabel eepromPatch, 0x8060D588
.definelabel bbbandit_array, 0x8002DB80
.definelabel boot_lui1, 0x8001
.definelabel boot_lui2, 0xDCC4
.definelabel setupCheckOverwrite, 0x805FEB00
.definelabel frameHookLocation, 0x805FC164
.definelabel customBootCodeStart, 0x80000A30
.definelabel bootJumpStart, 0x80000764
.definelabel bootJumpReturn, 0x80000784
.definelabel bootFinalValue, 0xD
.definelabel t4BootAddition, 0x1320
.definelabel customLoopReturn, 0x805FC16C
.definelabel pauseHookWrite, 0x805FC890
.definelabel flagHookWrite, 0x8073129C
.definelabel spawnTimerHookWrite, 0x806A2AF8
.definelabel phaseCorrectionHookWrite, 0x806E063C
.definelabel arcadeHookWrite, 0x805FC144
.definelabel jetpacHookWrite, 0x805FC154
.definelabel pause97HookWrite, 0x806A8158
.definelabel pause343HookWrite, 0x806ACFFC
.definelabel loadSetupHookWrite, 0x80688714
.definelabel resolveBarrelHookWrite, 0x80688D64
.definelabel fairyStoreHookWrite, 0x806C5D9C
.definelabel displayListHookWrite, 0x8071417C
.definelabel vertBaseStoreHookWrite, 0x8062F200
.definelabel signalsStoreHookWrite, 0x80679344
.definelabel delayedKillsStoreHookWrite, 0x806783CC
.definelabel lockStackStoreHookWrite, 0x806109F4
.definelabel storeFloorPreloadHookWrite, 0x8066610C
.definelabel giantKoshaHookWrite, 0x80646074
.definelabel lagHookWrite, 0x80600674
.definelabel saveHookWrite, 0x8060DECC
.definelabel spriteHookWrite, 0x806AB7D0
.definelabel speedHookWrite, 0x80665354
.definelabel kongHookWrite, 0x806F3750
.definelabel crcPatchMemory, 0x80002554
.definelabel crcPatchROM, 0x3154
.definelabel displayListCap, 0x805FE9E0
.definelabel lockedCamHookWrite, 0x8061F6CC
.definelabel overlayEntryPoint, 0x80024000
.definelabel arcadeTextHookWrite, 0x80031C30
.definelabel arcadeHasControlHookWrite, 0x80025410
.definelabel arcadeHasControl2HookWrite, 0x800252F4
.definelabel arcadeHasControl3HookWrite, 0x80027914
.definelabel jetpacTextHookWrite, 0x80025354
.definelabel jetpacPauseHookWrite, 0x80024954
.definelabel jetpac5000HookWrite, 0x80027DB0
.definelabel doubleBeaverHookWrite, 0x806AD728
.definelabel guardStoreHookWrite, 0x806AE4AC
.definelabel guardLightHookWrite, 0x806AE4C4
.definelabel parentCheckBypassHookWrite, 0x806416B4
.definelabel initHookWrite, 0x805FBDEC

.definelabel customCodeStart, 0x805d6e00
.definelabel customCodeUpper, 0x805d
.definelabel customCodeLower, 0x6e00
.definelabel customCodeSize, 0x24000
