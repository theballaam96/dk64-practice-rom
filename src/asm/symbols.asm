//functions
.definelabel setFlag, 0x8073129C
.definelabel checkFlag, 0x8073110C
.definelabel dk_malloc, 0x80610FE8
.definelabel free, 0x80611408
.definelabel playSound, 0x80609140
.definelabel initiateTransition, 0x805FF378
.definelabel getFlagBlockAddress, 0x8060E25C
.definelabel isAddressActor, 0x8067AF44
.definelabel getTimestamp, 0x800060B0
.definelabel dmaFileTransfer, 0x80000450
.definelabel deleteActor, 0x806785D4
.definelabel spawnActor, 0x80677FA8
.definelabel spawnTextOverlay, 0x8069D0F8
.definelabel dk_sqrt, 0x8000AC60
.definelabel dk_strFormat, 0x800031E0
.definelabel dk_multiply, 0x80005918
.definelabel convertTimestamp, 0x80005818
.definelabel resetMap, 0x805FFFC8
.definelabel prepKongColoring, 0x8068A508
.definelabel dk_memcpy, 0x80003000

//vanilla data
.definelabel TransitionSpeed, 0x807FD88C
.definelabel CutsceneWillPlay, 0x8075533B
.definelabel KRoolRound, 0x80750AD4
.definelabel MovesBase,  0x807FC950 // End: 0x807FCB28
.definelabel PlayerOneColor, 0x807552F4
.definelabel Mode, 0x80755318
.definelabel TBVoidByte, 0x807FBB63
.definelabel CurrentMap, 0x8076A0A8
.definelabel DestMap, 0x807444E4
.definelabel DestExit, 0x807444E8
.definelabel StorySkip, 0x8074452C
.definelabel HelmTimerShown, 0x80755350 // u8
.definelabel TempFlagBlock, 0x807FDD90
.definelabel InSubmap, 0x8076A170
.definelabel ParentMap, 0x8076A172
.definelabel ParentExit, 0x8076A174
.definelabel HelmTimerPaused, 0x80713C9B // u8
.definelabel LagBoost, 0x80744478 // u32
.definelabel FrameLag, 0x8076AF10
.definelabel FrameReal, 0x80767CC4
.definelabel RNG, 0x80746A40 // u32
.definelabel BetaNinRWSkip, 0x80755324 // u8
.definelabel LogosDestMap, 0x807132BF // u8
.definelabel LogosDestMode, 0x807132CB // u8
.definelabel Gamemode, 0x80755314 // u8
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
.definelabel PositionWarpInfo, 0x807FC918 // WarpInfo Struct
.definelabel PositionWarpBitfield, 0x8076AEE2
.definelabel PositionFloatWarps, 0x8076AEE4 // f32 x 3
.definelabel PositionFacingAngle, 0x8076AEF0 // u16
.definelabel ChimpyCam, 0x80744530
.definelabel ScreenRatio, 0x807444C0
.definelabel CurrentActorPointer, 0x807FBB44
.definelabel LoadedActorCount, 0x807FBB35
.definelabel SpawnerArray, 0x807FDC8C
.definelabel SpawnerCount, 0x807FDC88
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
.definelabel ModelTwoTouchCount, 0x807FD798 // u8
.definelabel ModelTwoTouchArray, 0x807FD790 // u16 array
.definelabel TransitionProgress, 0x807ECC60 // u8
.definelabel BackgroundHeldInput, 0x807ECD40 // u32
.definelabel PauseTimestampMajor, 0x807445C0 // u32
.definelabel PauseTimestampMinor, 0x807445C4 // u32
.definelabel HelmStartTimestampMajor, 0x80755340 // u32
.definelabel HelmStartTimestampMinor, 0x80755344 // u32
.definelabel HelmStartTime, 0x8075534C // u32
.definelabel p1PressedButtons, 0x807ECD48
.definelabel p1HeldButtons, 0x807ECD58

//hack data
.definelabel ActiveTools_Error, 0x807FFF1C // 0x4
.definelabel ActiveToolsMenu, 0x807FFF20 // 0x60
.definelabel StoredSettings, 0x807FCB30 // Follows savedSettings struct

.definelabel PositionSavestate, 0x807FFEA4 // 0x3C Byttes
.definelabel TimerData, 0x807FFE90 // 0x14 bytes

.definelabel TestVariable, 0x807FFFFC

.definelabel WatchIndex, 0x807FFFF8 // u8 array (size 4)
.definelabel InBadMap, 0x807FFFF7 // u8 - Bool
.definelabel MenuSavestateAction, 0x807FFFF6 // u8 - 0 = Save, 1 = Load
.definelabel InputDisplayIndex, 0x807FFFF5 // u8
.definelabel RAMDisplayOpen, 0x807FFFF4 // u8
.definelabel LoadVarsOnMapLoad, 0x807FFFF3 // u8 - For savestates
.definelabel LoadedHooks, 0x807FFFEF // u8
.definelabel Precision, 0x807FFFEE // u8
.definelabel SniperOn, 0x807FFFED // u8
.definelabel SlamLevel, 0x807FFFEC // u8
.definelabel AverageLag, 0x807FFFE8 // f32
.definelabel ISGTimer, 0x807FFFE0 // u32
.definelabel LagDocumentationIndex, 0x807FFFDE // u8
.definelabel StoredLag, 0x807FFFDC // u16
.definelabel StoredRound, 0x807FFFDB // u8
.definelabel DisablePositionButtons, 0x807FFFDA // u8
.definelabel DisableTagAnywhere, 0x807FFFD9 // u8
.definelabel FrameAdvanceStart, 0x807FFFC8 // u32
.definelabel DisableStartupSkip, 0x807FFFC7 // u8
.definelabel DisableForcedStorySkip, 0x807FFFC6 // u8
.definelabel SandstormAddress, 0x807FFDFC // u32
.definelabel AutoPhaseStateOn, 0x807FFDF8 // u8
.definelabel GiantKoshaTimerAddress, 0x807FFDF4 // u32
.definelabel GiantKoshaTimerValue, 0x807FFDF2 // u16
.definelabel MenuShortcutButtonsOff, 0x807FFDDB // u8
.definelabel FrameAdvancing, 0x807FFDDA // u8
.definelabel ArtificialPauseOn, 0x807FFDD9 // u8
.definelabel InfiniteHealthCheatOn, 0x807FFDD8 // u8
.definelabel LToLevitateOn, 0x807FFDD7 // u8
.definelabel ActiveMenu, 0x807FFDC4 // 0x3
.definelabel NewMenu_ErrorStart, 0x807FFDC0 // u32
.definelabel FocusedSavestate, 0x807FFDBF // u8
.definelabel AutoMoonkickOn, 0x807FFDBE // u8
.definelabel EnemySpawnOff, 0x807FFDBD // u8

.definelabel PhaseChecker, 0x807FFDB7 // 0x1
.definelabel CustomFlagByte, 0x807FFF80 // u16
.definelabel CustomFlagBit, 0x807FFF82 // u8
.definelabel CustomFlagType, 0x807FFF83 // u8
.definelabel CustomFlagSet, 0x807FFF84 // u8

.definelabel ISGStage, 0x807FFF85 // u8
.definelabel IsPauseMenuOpen, 0x807FFF86 // u8
.definelabel PreviousFrameButtons, 0x807FFF88 // u16
.definelabel UndoFlag_EncodedFlag, 0x807FFF8A // u16
.definelabel UndoFlag_OutputBool, 0x807FFF8C // u8
.definelabel UndoFlag_FlagType, 0x807FFF8D // u8
.definelabel UndoFlag_FlagStored, 0x807FFF8E // u8
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
.definelabel AddedCorruptionActorCount, 0x807FFFA8 // u8
.definelabel PreviousLagArray, 0x807FFFB0; // u8 array

.definelabel graphicalOverlaySpace, 0x807FFA00 // 0x180
.definelabel WatchActor, 0x807FFB80 // u32 x 4
.definelabel WatchTextSpace, 0x807FFB90 // 0x30 x 4
