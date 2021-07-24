.align
Maps_HideoutHelmKRool_DestMap:
	.byte 0x11
	.byte 0x11
	.byte 0x11
	// END OF HELM
	.byte 0xCB
	.byte 0xCC
	.byte 0xCD
	.byte 0xCE
	.byte 0xCF

.align
Maps_HideoutHelmKRool_DestExit:
	.byte 0x0
	.byte 0x3
	.byte 0x4
	// END OF HELM
	.byte 0
	.byte 0
	.byte 0
	.byte 0
	.byte 0

.align
Maps_HideoutHelmKRool_Struct:
	.word Maps_HideoutHelmKRool_DestMap // Map
	.word Maps_HideoutHelmKRool_DestExit // Exit
	.byte 9 // Screen

.align
Menu_Maps_HideoutHelmKRool_Entry:	
	.asciiz "HELM - ENTRANCE"
Menu_Maps_HideoutHelmKRool_BOM:	
	.asciiz "HELM - BOM ROOM"
Menu_Maps_HideoutHelmKRool_W1Room:	
	.asciiz "HELM - NAVIGATION ROOM"
Menu_Maps_HideoutHelmKRool_DKPhase:	
	.asciiz "K. ROOL - DK PHASE"
Menu_Maps_HideoutHelmKRool_DiddyPhase:	
	.asciiz "K. ROOL - DIDDY PHASE"
Menu_Maps_HideoutHelmKRool_LankyPhase:	
	.asciiz "K. ROOL - LANKY PHASE"
Menu_Maps_HideoutHelmKRool_TinyPhase:	
	.asciiz "K. ROOL - TINY PHASE"
Menu_Maps_HideoutHelmKRool_ChunkyPhase:	
	.asciiz "K. ROOL - CHUNKY PHASE"

.align
Menu_MapHelmKRool_Array:
	.word Menu_Maps_HideoutHelmKRool_Entry
	.word Menu_Maps_HideoutHelmKRool_BOM
	.word Menu_Maps_HideoutHelmKRool_W1Room
	.word Menu_Maps_HideoutHelmKRool_DKPhase
	.word Menu_Maps_HideoutHelmKRool_DiddyPhase
	.word Menu_Maps_HideoutHelmKRool_LankyPhase
	.word Menu_Maps_HideoutHelmKRool_TinyPhase
	.word Menu_Maps_HideoutHelmKRool_ChunkyPhase
	.word Menu_Return

.align
Menu_MapHelmKRool_Functions:
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_WarpToMap
	.word ActiveMenu_PreviousScreen

.align
Menu_MapHelmKRool_Struct:
	.word Menu_MapHelmKRool_Array // Text Array
	.word Menu_MapHelmKRool_Functions // Function Array
	.byte 9 // Array Items
	.byte 1 // Parent Screen
	.byte 7 // Parent Position