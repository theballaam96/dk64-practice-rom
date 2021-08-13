typedef struct actorData {
	/* 0x000 */ char unk_00[0x58];
	/* 0x058 */ int actorType;
	/* 0x05C */ char unk_5C[0x7C-0x5C];
	/* 0x07C */ float xPos;
} actorData;

typedef struct playerData {
	/* 0x000 */ char unk_00[0x58];
	/* 0x058 */ int characterID; //02 is dk, 03 is diddy, 04 is lanky, etc
	/* 0x05C */ char unk_5C[0x07];
	/* 0x063 */ char visibility;
	/* 0x064 */ char unk_64[0x18];
	/* 0x07C */ float xPos;
	/* 0x080 */ float yPos;
	/* 0x084 */ float zPos;
	/* 0x088 */ char unk_88[0x30];
	/* 0x0B8 */ float hSpeed;
	/* 0x0BC */ char unk_BC[0x4];
	/* 0x0C0 */ float yVelocity;
	/* 0x0C4 */ char unk_C4[0xE6 - 0xC4];
	/* 0x0E6 */ short facing_angle;
	/* 0x0E8 */ char unk_E8[0x12c-0xE8];
	/* 0x12C */ short chunk;
	/* 0x12E */ char unk_12E[0x147 - 0x12E];
	/* 0x147 */ char hand_state;
	/* 0x148 */ char unk_148[0x154 - 0x148];
	/* 0x154 */ char control_state;
	/* 0x155 */ char control_state_progress;
	/* 0x156 */ char unk_156[0xB2];
	/* 0x208 */ int* vehicle_actor_pointer;
	/* 0x20C */ char was_gun_out;
	/* 0x20D */ char unk_20D[0x328 - 0x20D];
	/* 0x328 */ actorData* krool_timer_pointer;
	/* 0x32C */ actorData* held_actor;
	/* 0x330 */ char unk_330[0x36F - 0x330];
	/* 0x36F */ char new_kong;
} playerData; //size 0x630

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
	/* 0x01C */ unsigned char Map;
	/* 0x01D */ unsigned char Exit;
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

typedef const struct MapWarp {
	/* 0x000 */ const unsigned char* maps;
	/* 0x004 */ const unsigned char* exits;
	/* 0x008 */ char screen;
} MapWarp;

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
	/* 0x000 */ unsigned int Start;
	/* 0x004 */ unsigned int Timer;
	/* 0x008 */ char Mode;
	/* 0x009 */ char StartMode;
	/* 0x00A */ char PauseMode;
	/* 0x00B */ char FinishMode;
	/* 0x00C */ unsigned int Reduction;
	/* 0x010 */ unsigned int TimerPostReduction;
} TimerInfo;

typedef struct ActiveMenuData {
	/* 0x000 */ unsigned char screenIndex;
	/* 0x001 */ unsigned char positionIndex;
	/* 0x002 */ char isOpen;
} ActiveMenuData;

typedef struct PhaseCheckerData {
	/* 0x000 */ char previousMagnitude;
} PhaseCheckerData;

typedef struct RGB {
	/* 0x000 */ unsigned char red;
	/* 0x001 */ unsigned char green;
	/* 0x002 */ unsigned char blue;
} RGB;

typedef struct KongBase {
	/* 0x000 */ char special_moves;
	/* 0x001 */ char simian_slam;
	/* 0x002 */ char weapon_bitfield;
	/* 0x003 */ char ammo_belt;
	/* 0x004 */ char instrument_bitfield;
	/* 0x005 */ char unk_05[0x2];
	/* 0x007 */ char coins;
	/* 0x008 */ short instrument_energy;
	/* 0x00A */ short cb_count[0xE];
	/* 0x026 */ short tns_cb_count[0xE];
	/* 0x042 */ short gb_count[0xE];
} KongBase;

typedef struct ISGFadeoutData {
	/* 0x000 */ int FadeoutTime;
	/* 0x004 */ char FadeoutMap;
	/* 0x005 */ char unk_05[0x3];
} ISGFadeoutData;

typedef struct GiantKoshaData {
	/* 0x000 */ short timer;
} GiantKoshaData;

typedef struct SwapObjectData {
	/* 0x000 */ char unk_00[0x29C];
	/* 0x29C */ short action_type;
} SwapObjectData;

typedef struct ModelTwoData {
	/* 0x000 */ char unk_00[0x84];
	/* 0x084 */ short object_type;
	/* 0x086 */ char unk_86[0x4];
	/* 0x08A */ short object_id;
	/* 0x08C */ char unk_8C[0x4];
} ModelTwoData;