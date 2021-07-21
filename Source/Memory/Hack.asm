// INTERNAL
[MenuOpen]: 0x807FFFFF // u8
[SpecialFlagIndex]: 0x807FFFFE // u8
[Slot3Position]: 0x807FFFFD // u8
[MenuPosition]: 0x807FFFFB // u8
[MenuActionCooldown]: 0x807FFFFA // u8 - Prevents crashes
[PauseMenuNextScreen]: 0x807FFFF9 // u8
[HasASavestate]: 0x807FFFF8 // u8 - Bool
[InBadMap]: 0x807FFFF7 // u8 - Bool
[MenuSavestateAction]: 0x807FFFF6 // u8 - 0 = Save, 1 = Load
[StickWasNonNeutral]: 0x807FFFF5 // u8 - Bool
[PauseMenuScreen]: 0x807FFFF4 // u8
[StoredMainMenuTextPointer]: 0x807FFFF0 // u32 pointer
[VariableDisplayOn]: 0x807FFFEF // u8
[ExtraSlotPosition]: 0x807FFFEE // u8
[SniperOn]: 0x807FFFED // u8
[SlamLevel]: 0x807FFFEC // u8
[CumulativeLag]: 0x807FFFE8 // u32
[ISGTimer]: 0x807FFFE0 // u64
[StoredLag]: 0x807FFFDC // u32
[StoredTime]: 0x807FFFD8 // u32
[StoredStart]: 0x807FFFD4 // u32
[StoredTimerMode]: 0x807FFFD3 // u8 - 0: Reset/Zeroed, 1: Started, 2: Stopped
[StoredRound]: 0x807FFFD2 // u8
[DisablePositionButtons]: 0x807FFFD1 // u8
[DisableTagAnywhere]: 0x807FFFD0 // u8
[SelectedMasterLevelIndex]: 0x807FFFCF // u8
[SelectedMapIndex]: 0x807FFFCE // u8
[SelectedMapCap]: 0x807FFFCD // u8
[MenuSlide]: 0x807FFFCC // u8
[FrameAdvanceStart]: 0x807FFFC8 // u32
[DisableStartupSkip]: 0x807FFFC7 // u8
[DisableForcedStorySkip]: 0x807FFFC6 // u8
[SandstormAddress]: 0x807FFDFC // u32
[SandstormActive]: 0x807FFDFB // u8
[SandstormChange]: 0x807FFDFA // u8
[SandstormChangeCountdown]: 0x807FFDF9 // u8
[AutoPhaseStateOn]: 0x807FFDF8 // u8
[GiantKoshaTimerAddress]: 0x807FFDF4 // u32
[GiantKoshaTimerValue]: 0x807FFDF2 // u16
[DisplayText]: 0x807FFDE0 // 0x10
[FrameAdvancing]: 0x807FFDDA // u8
[ArtificialPauseOn]: 0x807FFDD9 // u8
[InfiniteHealthCheatOn]: 0x807FFDD8 // u8
[LToLevitateOn]: 0x807FFDD7 // u8
[SelectedFileStatus]: 0x807FFDD6 // u8
[SelectedLMode]: 0x807FFDD5 // u8
[SelectedIndependentCheat]: 0x807FFDD4 // u8
[TimerStartMode]: 0x807FFDD3 // u8
[TimerPauseMode]: 0x807FFDD2 // u8
[TimerFinishMode]: 0x807FFDD1 // u8
[SelectedMasterWarpLevel]: 0x807FFDD0 // u8
[TimerReduction]: 0x807FFDCC // u32 - Pause Menu
[TimerAfterReduction]: 0x807FFDC8 // u32
[SelectedSubWarpLevel]: 0x807FFDC7 // u8
[NewMenuOpen]: 0x807FFDC6 // u8
[NewMenu_Position]: 0x807FFDC5 // u8
[NewMenu_Screen]: 0x807FFDC4 // u8
[NewMenu_ErrorStart]: 0x807FFDC0 // u32
[FocusedSavestate]: 0x807FFDBF // u8
[AutoMoonkickOn]: 0x807FFDBE // u8
[EnemySpawnOff]: 0x807FFDBD // u8
[WatchActor]: 0x807FFDB8 // u32
[PhaseChecker_PreviousMagnitude]: 0x807FFDB7 // u8
[WatchTextSpace]: 0x807FFD80 // 0x30 (47 characters)
[CustomFlagByte]: 0x807FFF80 // u16
[CustomFlagBit]: 0x807FFF82 // u8
[CustomFlagType]: 0x807FFF83 // u8
[CustomFlagSet]: 0x807FFF84 // u8
[ISGStage]: 0x807FFF85 // u8
[IsPauseMenuOpen]: 0x807FFF86 // u8
[PreviousFrameButtons]: 0x807FFF88 // u16
[UndoFlag_EncodedFlag]: 0x807FFF8A // u16
[UndoFlag_OutputBool]: 0x807FFF8C // u8
[UndoFlag_FlagType]: 0x807FFF8D // u8
[UndoFlag_FlagStored]: 0x807FFF8E // u8
[LastLoadStateAction]: 0x807FFF8F // u8
[PauseMenuMusicSetting]: 0x807FFF90 // u8
[ClosingMenu]: 0x807FFF91 // u8
[HasNeutralStickInput]: 0x807FFF92 // u8
[TouchingGB]: 0x807FFF93 // u8
[IsSuperspeedOn]: 0x807FFF94 // u8
[LToCancelCSOn]: 0x807FFF95 // u8
[LToToggleTBOn]: 0x807FFF96 // u8
[TempTimestampStorage]: 0x807FFF98 // u64
[HackTitle]: 0x807FFFA0 // u32
[HackVersion]: 0x807FFFA4 // u32