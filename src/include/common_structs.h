typedef struct playerData {
	/* 0x000 */ char unk_00[0x58];
	/* 0x058 */ int characterID; //02 is dk, 03 is diddy, 04 is lanky, etc
	/* 0x05C */ char unk_5C[0x07];
	/* 0x063 */ char visibility;
	/* 0x064 */ char unk_64[0x18];
	/* 0x07C */ float xPos;
	/* 0x080 */ float yPos;
	/* 0x084 */ float zPos;
	/* 0x088 */ char unk_88[0x38];
	/* 0x0C0 */ float yVelocity;
	/* 0x0C4 */ char unk_C4[0x90];
	/* 0x154 */ char control_state;
	/* 0x155 */ char control_state_progress;
	/* 0x156 */ char unk_156[0xB2];
	/* 0x208 */ int* vehicle_actor_pointer;
} playerData;//size 0x630

typedef struct TextOverlay {
	/* 0x000 */ char unk_00[0x15F];
	/* 0x004 */ //u16
	/* 0x006 */ //u16
	/* 0x008 */ //u8
	/* 0x009 */ //u8
	/* 0x054 */ //layer ID?
	/* 0x15F */ char opacity;
	/* 0x160 */ char unk_160[0x0A];
	/* 0x16A */ unsigned char red;
	/* 0x16B */ unsigned char green;
	/* 0x16C */ unsigned char blue;
	/* 0x16D */ char unk_16D[0x0B];
	/* 0x178 */ char* string;
} TextOverlay;

typedef struct Savestate {
	/* 0x000 */ char InventoryBase[0x10];
	/* 0x010 */ float xPos;
	/* 0x014 */ float yPos;
	/* 0x018 */ float zPos;
	/* 0x01C */ char Map;
	/* 0x01D */ char Exit;
	/* 0x01E */ char Character;
	/* 0x01F */ char HasData;
	/* 0x020 */ char TempFlagBlock[0x10];
	/* 0x030 */ char KongBase[0x1E0];
	/* 0x210 */ char PermanentFlagBlock[0x13C];
} Savestate;

typedef const struct Screen {
	/* 0x000 */ const int* TextArray;
	/* 0x004 */ const int* FunctionArray;
	/* 0x005 */ char ArrayItems;
	/* 0x006 */ char ParentScreen;
	/* 0x007 */ char ParentPosition;
} Screen;

typedef struct Controller {
	/* 0x000 */ short Buttons;
	/* 0x002 */ char stickX;
	/* 0x003 */ char stickY;
} Controller;

typedef struct InventoryBase {
	/* 0x000 */ short StandardAmmo;
	/* 0x002 */ short HomingAmmo;
	/* 0x004 */ short Oranges;
	/* 0x006 */ short Crystals;
	/* 0x008 */ short Film;
	/* 0x00A */ char unk0A;
	/* 0x00B */ char Health;
	/* 0x00C */ char Melons;
} InventoryBase;

typedef struct PosState {
	/* 0x000 */ float xCamera;
	/* 0x004 */ float yCamera;
	/* 0x008 */ float zCamera;
	/* 0x00C */ float yVelocity;
	/* 0x010 */ float yAccel;
	/* 0x014 */ float hVelocity;
	/* 0x018 */ float yFloor;
	/* 0x01C */ short xStored1;
	/* 0x01E */ short yStored1;
	/* 0x020 */ short zStored1;
	/* 0x022 */ short xStored2;
	/* 0x024 */ short yStored2;
	/* 0x026 */ short zStored2;
	/* 0x028 */ short yRot;
	/* 0x02A */ short zRot;
	/* 0x02C */ float xPos;
	/* 0x030 */ float yPos;
	/* 0x034 */ float zPos;
	/* 0x038 */ char control_state;
	/* 0x039 */ char control_state_progress;
	/* 0x03A */ char map;
	/* 0x03B */ char bone_array_counter;
} PosState;

typedef struct TimerInfo {
	/* 0x000 */ int Start;
	/* 0x004 */ int Timer;
	/* 0x008 */ char Mode;
	/* 0x009 */ char StartMode;
	/* 0x00A */ char PauseMode;
	/* 0x00B */ char FinishMode;
	/* 0x00C */ int Reduction;
	/* 0x010 */ int TimerPostReduction;
} TimerInfo;

typedef struct ActiveMenuData {
	/* 0x000 */ char screenIndex;
	/* 0x001 */ char positionIndex;
	/* 0x002 */ char isOpen;
} ActiveMenuData;

typedef struct PhaseCheckerData {
	/* 0x000 */ char previousMagnitude;
} PhaseCheckerData;

typedef struct RGB {
	/* 0x000 */ char red;
	/* 0x001 */ char green;
	/* 0x002 */ char blue;
} RGB;