// N64 Buttons
#define L_Button 0x0020
#define D_Up 0x0800
#define D_Down 0x0400
#define D_Left 0x0200
#define D_Right 0x0100
#define B_Button 0x4000
#define A_Button 0x8000
#define Z_Button 0x2000
#define R_Button 0x0010
#define Start_Button 0x1000
#define C_Up 0x0008
#define C_Down 0x0004
#define C_Left 0x0002
#define C_Right 0x0001

// Colors
#define SelectedRGB 0xFFD700 // CSS Gold
#define ReturnRGB 0xFF4500 // CSS OrangeRed
#define KoshaRGB_Frozen 0x008B8B // CSS DarkCyan
#define KoshaRGB_CancelRange 0xFFD700 // CSS Gold
#define KoshaRGB_Music 0xD2691E // CSS Chocolate
#define KoshaRGB_Tantrum 0x8B0000 // CSS DarkRed
#define ISGRGB_FadeoutPending 0xFF4500 // CSS OrangeRed
#define ISGRGB_Fading 0xFF0000 // CSS Red
#define AngleRGB_PhaseState 0xFF4500 // CSS OrangeRed
#define HeldObject_ObjectExists 0xFF4500 // CSS OrangeRed

// Master Type
#define ACTOR_MASTER_TYPE_UNASSIGNED 0
#define ACTOR_MASTER_TYPE_UNUSED 1
#define ACTOR_MASTER_TYPE_3D 2
#define ACTOR_MASTER_TYPE_CONTROLLER 3
#define ACTOR_MASTER_TYPE_2D 4

// SFX Index
#define Banana 0x2A0
#define Okay 0x23C
#define UhOh 0x150
#define Bell 0x1F
#define KLumsy 0x31C
#define Wrong 0x98
#define Potion 0x214
#define AmmoPickup 0x157
#define Coin 0x1D1
#define BeepHigh 116
#define BeepLow 117
#define FeedMe 601
#define Bounce 458
#define TimerTock 143
#define ChunkyFallTooFar 197
#define Fire 234
#define MatchingSound 171
#define CameraPull 441
#define Quack 170
#define TagWarp 612
#define TakeWarp 230
#define Splat 22
#define Burp 530
#define ArcadeJump 65
#define ArcadeSpring 67
#define ArcadeFalling 68
#define ArcadeGrunt 83

// Other
#define MysteryWriteOffset 0x29C
#define CurrentCharacter 0x36C
#define MovesBaseSize 0x1D8
#define MaxMenuItems 20 // 32 (practice rom cap) - 8 (normal cap) - 4 (watch)
#define ErrorLength 180
#define WarpScreens 38
#define WatchCount 4
#define FileStateSize 0x340
#define flagMenuScreenCount 11
#define pointer_table_offset 0x101C50

#if ROM_VERSION == 1
	#define HERTZ 50 // PAL = 50Hz
#else
	#define HERTZ 60 // US/JP = 60 Hz
#endif

// Version Access
#define ACCESS_US 1
#define ACCESS_PAL 2
#define ACCESS_JP 4
#define ACCESS_N64 8
#define ACCESS_WIIU 16
#define ACCESS_EMU 32

// Dynamic Watch Types
#define DYNWATCH_UBYTE 0
#define DYNWATCH_SBYTE 1
#define DYNWATCH_HBYTE 2
#define DYNWATCH_USHORT 3
#define DYNWATCH_SSHORT 4
#define DYNWATCH_HSHORT 5
#define DYNWATCH_UINT 6
#define DYNWATCH_SINT 7
#define DYNWATCH_HINT 8
#define DYNWATCH_FLOAT 9

#if ROM_VERSION == 0
	#define IMAGE_FAIRYBOX 107
	#define IMAGE_FAIRYDOT 108
	#define IMAGE_GITHUB 109
	#define IMAGE_BALLAAM 110
	#define IMAGE_RAIN 111
	#define IMAGE_ISOTARGE 112
	#define IMAGE_CIRCLE 113
	#define INFO_SHOWN 1
	#define TEXT_Y_OFFSET 0
	#define INFO_TEXT "INFO"
#elif ROM_VERSION == 1
	#define IMAGE_FAIRYBOX 110
	#define IMAGE_FAIRYDOT 111
	#define IMAGE_GITHUB 112
	#define IMAGE_BALLAAM 113
	#define IMAGE_RAIN 114
	#define IMAGE_ISOTARGE 115
	#define IMAGE_CIRCLE 116
	#define INFO_SHOWN 1
	#define TEXT_Y_OFFSET 16
	#define INFO_TEXT "START FOR INFO"
#else
	#define IMAGE_FAIRYBOX 194
	#define IMAGE_FAIRYDOT 195
	#define IMAGE_GITHUB 196
	#define IMAGE_BALLAAM 197
	#define IMAGE_RAIN 198
	#define IMAGE_ISOTARGE 199
	#define IMAGE_CIRCLE 200
	#define INFO_SHOWN 0
	#define TEXT_Y_OFFSET 0
	#define INFO_TEXT ""
#endif