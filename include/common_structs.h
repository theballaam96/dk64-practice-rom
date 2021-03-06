typedef struct floatPos {
	/* 0x000 */ float xPos;
	/* 0x004 */ float yPos;
	/* 0x008 */ float zPos;
} floatPos;

typedef struct shortPos {
	/* 0x000 */ short xPos;
	/* 0x002 */ short yPos;
	/* 0x004 */ short zPos;
} shortPos;

typedef struct renderingParamsData {
	/* 0x000 */ char unk_00[0x34];
	/* 0x034 */ float scale_x;
	/* 0x038 */ float scale_y;
	/* 0x03C */ float scale_z;
} renderingParamsData;

typedef struct actorData {
	/* 0x000 */ void* model_pointer;
	/* 0x004 */ renderingParamsData* render_pointer;
	/* 0x008 */ char unk_08[0x58-0x8];
	/* 0x058 */ int actorType;
	/* 0x05C */ char unk_5C[0x60-0x5C];
	/* 0x060 */ unsigned int obj_props_bitfield;
	/* 0x064 */ char unk_64[0x7C-0x64];
	/* 0x07C */ float xPos;
	/* 0x080 */ float yPos;
	/* 0x084 */ float zPos;
	/* 0x088 */ char unk_80[0xB8-0x88];
	/* 0x0B8 */ float hSpeed;
	/* 0x0BC */ char unk_BC[0xE6-0xBC];
	/* 0x0E6 */ short facing_angle;
	/* 0x0E8 */ char unk_E8[0x128-0xE8];
	/* 0x128 */ short shadow_intensity;
	/* 0x12A */ short draw_distance;
	/* 0x12C */ char unk_12C[0x13C-0x12C];
	/* 0x13C */ void* collision_queue_pointer;
	/* 0x140 */ char unk_140[0x144-0x140];
	/* 0x144 */ char noclip;
	/* 0x145 */ char unk_145[0x154-0x145];
	/* 0x154 */ unsigned char control_state;
	/* 0x155 */ char control_state_progress;
	/* 0x156 */ char unk_156[0x16A-0x156];
	/* 0x16A */ unsigned char red;
	/* 0x16B */ unsigned char green;
	/* 0x16C */ unsigned char blue;
	/* 0x16D */ char unk_16D[0x174-0x16D];
	/* 0x174 */ void* paad;
	/* 0x178 */ char unk_178[0x180-0x178];
	/* 0x180 */ void* tied_character_spawner;
} actorData;

typedef struct beaverData {
	/* 0x000 */ actorData main;
	/* 0x184 */ char unk_184[0x192-0x184];
	/* 0x192 */ short scare_bitfield;
} beaverData;

typedef struct cameraData {
	/* 0x000 */ char unk_00[0x7C];
	/* 0x07C */ float xPos;
	/* 0x080 */ float yPos;
	/* 0x084 */ float zPos;
	/* 0x088 */ char unk_88[0x15F-0x88];
	/* 0x15F */ char facing_angle;
	/* 0x160 */ char unk_160[0x178-0x160];
	/* 0x178 */ void* focused_actor_pointer;
	/* 0x17C */ char unk_17C[0x1FC-0x17C];
	/* 0x1FC */ float viewportX;
	/* 0x200 */ float viewportY;
	/* 0x204 */ float viewportZ;
	/* 0x208 */ char unk_208[0x22A-0x208];
	/* 0x22A */ short viewportRotation;
	/* 0x22C */ char unk_22C[0x230-0x22C];
	/* 0x230 */ float viewportXRotation;
	/* 0x234 */ char unk_234[0x26B-0x234];
	/* 0x26B */ char camera_state;
} cameraData;

typedef struct tagBarrel {
	/* 0x000 */ char unk_00[0x1A0];
	/* 0x1A0 */ short tag_oscillation_timer;
} tagBarrel;

typedef struct timerActor {
	/* 0x000 */ char unk_00[0x15F];
	/* 0x15F */ char type;
	/* 0x160 */ char unk_160[0x184-0x160];
	/* 0x184 */ int test;
} timerActor;

typedef struct bone_array {
	/* 0x000 */ char unk_00[0x58];
	/* 0x058 */ short xPos;
	/* 0x05A */ short yPos;
	/* 0x05C */ short zPos;
} bone_array;

typedef struct rendering_params {
	/* 0x000 */ char unk_00[0x14];
	/* 0x014 */ bone_array* bone_array1;
	/* 0x018 */ bone_array* bone_array2;
	/* 0x01C */ char unk_1C[0x64-0x1C];
	/* 0x064 */ short anim_idx;
	/* 0x066 */ char unk_66[0x68-0x66];
	/* 0x068 */ int anim_ptr;
} rendering_params;

typedef struct bonepos {
	/* 0x000 */ char unk_00[0x0C - 0x00];
	/* 0x00C */ int boneX;
	/* 0x010 */ int boneY;
	/* 0x014 */ int boneZ;
	/* 0x018 */ void* unk_ptr;
	/* 0x01C */ void* next_bone;
} bonepos;

typedef struct bonedata {
	/* 0x000 */ char unk_00[0x84 - 0x00];
	/* 0x084 */ int timer;
	/* 0x088 */ char unk_88[0x90 - 0x88];
	/* 0x090 */ bonepos* bone_positions;
} bonedata;

typedef struct playerData {
	/* 0x000 */ char unk_00[0x4];
	/* 0x004 */ rendering_params* rendering_param_pointer;
	/* 0x008 */ char unk_08[0x58 - 0x8];
	/* 0x058 */ int characterID; //02 is dk, 03 is diddy, 04 is lanky, etc
	/* 0x05C */ char unk_5C[0x60-0x5C];
	/* 0x060 */ int obj_props_bitfield;
	/* 0x064 */ char unk_64[0x6A-0x64];
	/* 0x06A */ short grounded_bitfield;
	/* 0x06C */ short unk_bitfield;
	/* 0x06E */ char unk_6E[0x7C-0x6E];
	/* 0x07C */ float xPos;
	/* 0x080 */ float yPos;
	/* 0x084 */ float zPos;
	/* 0x088 */ char unk_88[0xA4-0x88];
	/* 0x0A4 */ float floor;
	/* 0x0A8 */ char unk_A8[0xAC-0xA8];
	/* 0x0AC */ float water_floor;
	/* 0x0B0 */ char unk_B0[0xB8-0xB0];
	/* 0x0B8 */ float hSpeed;
	/* 0x0BC */ char unk_BC[0x4];
	/* 0x0C0 */ float yVelocity;
	/* 0x0C4 */ float yAccel;
	/* 0x0C8 */ char unk_C4[0xE6 - 0xC8];
	/* 0x0E6 */ short facing_angle;
	/* 0x0E8 */ short skew_angle;
	/* 0x0EA */ char unk_EA[0xEE - 0xEA];
	/* 0x0EE */ short next_facing_angle;
	/* 0x0F0 */ char unk_F0[0x10C - 0xF0];
	/* 0x10C */ short standing_on_index;
	/* 0x10E */ char unk_10E[0x110-0x10E];
	/* 0x110 */ char touching_object;
	/* 0x111 */ char unk_111[0x128 - 0x111];
	/* 0x128 */ short strong_kong_value;
	/* 0x12A */ char unk_12A[2];
	/* 0x12C */ short chunk;
	/* 0x12E */ char unk_12E[0x13C - 0x12E];
	/* 0x13C */ int* collision_queue_pointer;
	/* 0x140 */ bonedata* bone_data;
	/* 0x144 */ char unk_140[0x147 - 0x144];
	/* 0x147 */ char hand_state;
	/* 0x148 */ char unk_148[0x154 - 0x148];
	/* 0x154 */ unsigned char control_state;
	/* 0x155 */ char control_state_progress;
	/* 0x156 */ char unk_156[0x18A-0x156];
	/* 0x18A */ short moving_angle;
	/* 0x18C */ char unk_18C[0x1B8-0x18C];
	/* 0x1B8 */ float velocity_cap;
	/* 0x1BC */ char unk_1BC[0x1D0-0x1BC];
	/* 0x1D0 */ short ostand_value;
	/* 0x1D2 */ char unk_1D2[0x208-0x1D2];
	/* 0x208 */ void* vehicle_actor_pointer;
	/* 0x20C */ char was_gun_out;
	/* 0x20D */ char unk_20D[0x23C - 0x20D];
	/* 0x23C */ short unk_rocketbarrel_value1;
	/* 0x23E */ short unk_rocketbarrel_value2;
	/* 0x240 */ char unk_240[0x284 - 0x240];
	/* 0x284 */ cameraData* camera_pointer;
	/* 0x288 */ char unk_288[0x2BC - 0x288];
	/* 0x2BC */ floatPos grabPos;
	/* 0x2C8 */ char unk_2C8[0x323 - 0x2C8];
	/* 0x323 */ char unk_rocketbarrel_value3;
	/* 0x324 */ char unk_324[0x328 - 0x324];
	/* 0x328 */ actorData* krool_timer_pointer;
	/* 0x32C */ actorData* held_actor;
	/* 0x330 */ char unk_330[0x36C - 0x330];
	/* 0x36C */ char fairy_state;
	/* 0x36D */ char unk_36D[0x36F - 0x36D];
	/* 0x36F */ char new_kong;
	/* 0x370 */ int strong_kong_ostand_bitfield;
	/* 0x374 */ char unk_374[0x3C4-0x374];
	/* 0x3C4 */ char voiding;
} playerData; //size 0x630

typedef struct TextOverlay {
	/* 0x000 */ char unk_00[0x7C];
	/* 0x004 */ //u16
	/* 0x006 */ //u16
	/* 0x008 */ //u8
	/* 0x009 */ //u8
	/* 0x054 */ //layer ID?
	/* 0x07C */ float xPos;
	/* 0x080 */ float yPos;
	/* 0x084 */ float style;
	/* 0x088 */ char unk_88[0x15F-0x88];
	/* 0x15F */ char opacity;
	/* 0x160 */ char unk_160[0x0A];
	/* 0x16A */ unsigned char red;
	/* 0x16B */ unsigned char green;
	/* 0x16C */ unsigned char blue;
	/* 0x16D */ char unk_16D[0x0B];
	/* 0x178 */ char* string;
} TextOverlay;

typedef struct Savestate {
	/* 0x000 */ char InventoryBase[0xC];
	/* 0x00C */ unsigned short facing_angle;
	/* 0x00E */ char HelmTimerOn;
	/* 0x00F */ char ISGOn;
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
	/* 0x34C */ short HelmStart;
	/* 0x34E */ char ISGPrevFade;
	/* 0x34F */ unsigned char camera_angle;
	/* 0x350 */ int HelmTimerDifferenceMajor;
	/* 0x354 */ int HelmTimerDifferenceMinor;
	/* 0x358 */ int ISGTimerDifferenceMajor;
	/* 0x35C */ int ISGTimerDifferenceMinor;
	/* 0x360 */ short skew_angle;
	/* 0x362 */ char stored_damage;
	/* 0x363 */ char nearest_tag_enabled;
	/* 0x364 */ int createdTime;
	/* 0x368 */ float floor;
	/* 0x36C */ unsigned int rng;
	/* 0x370 */ short nearest_tag_oscillation_timer;
	/* 0x372 */ unsigned char par_map;
	/* 0x373 */ unsigned char par_exit;
	/* 0x374 */ float par_x;
	/* 0x378 */ float par_y;
	/* 0x37C */ float par_z;
	/* 0x380 */ short par_tpb;
	/* 0x382 */ char par_bool;
	/* 0x383 */ char unk_383;
	/* 0x384 */ floatPos cameraPos;
	/* 0x390 */ short camera_rotation;
	/* 0x392 */ short cbs_turned_in[7];
	/* 0x3A0 */ float dark_attic_squawks_x;
	/* 0x3A4 */ float dark_attic_squawks_y;
	/* 0x3A8 */ float dark_attic_squawks_z;
	/* 0x3AC */ short dark_attic_squawks_angle;
	/* 0x3AE */ char dark_attic_squawks_spawned;
	/* 0x3AF */ unsigned char japes_freediddy_switches_pressed_bitfield;
	/* 0x3B0 */ unsigned char eeprom_allocation[4];
	/* 0x3B4 */ unsigned char gamemode;
	/* 0x3B5 */ unsigned char is_visible;
	/* 0x3B6 */ unsigned char dktv_demo;
	/* 0x3B7 */ unsigned char file;
} Savestate;

typedef struct Screen {
	/* 0x000 */ int* TextArray;
	/* 0x004 */ const int* FunctionArray;
	/* 0x008 */ char ArrayItems;
	/* 0x009 */ char ParentScreen;
	/* 0x00A */ char ParentPosition;
	/* 0x00B */ char hasAccessArray;
	/* 0x00C */ const char* AccessArray;
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
	/* 0x028 */ short facing_angle;
	/* 0x02A */ short skew_angle;
	/* 0x02C */ float xPos;
	/* 0x030 */ float yPos;
	/* 0x034 */ float zPos;
	/* 0x038 */ char control_state;
	/* 0x039 */ char control_state_progress;
	/* 0x03A */ unsigned char map;
	/* 0x03B */ char bone_array_counter;
	/* 0x03C */ short cameraRotation;
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
	/* 0x000 */ char isOpen;
	/* 0x001 */ unsigned char screenIndex;
	/* 0x002 */ unsigned char positionIndex;
	/* 0x003 */ unsigned char startIndex;
	/* 0x004 */ char hasScroll;
	/* 0x005 */ unsigned char totalItems;
} ActiveMenuData;

typedef struct AutowalkData {
	/* 0x000 */ char unk_00[0x12];
	/* 0x012 */ short xPos;
	/* 0x014 */ char unk_14[0x2];
	/* 0x016 */ short zPos;
} AutowalkData;

typedef struct PhaseCheckerData {
	/* 0x000 */ float previousMagnitude;
	/* 0x004 */ char assistant_on;
	/* 0x005 */ char reason_code;
		// 0 = Successful Phasewalk
		// 1 = Low Magnitude Diff (Moving too slow - Flick down too late)
		// 2 = No fast acceleration
		// 3 = Bad initial angle
		// 4 = Low Magnitude Diff (Moving too fast, got to other side without having a different magnitude diff)
		// 5 = Reading
		// 6 = Waiting for Phasewalk Initiation
		// 7 = Early Z Press
		// 8 = Late Z Press
		// 9 = Low Magnitude Diff (Moving too slow - Flick up too slow)
		// 10 = Low Magnitude Diff (Moving too slow - Release too slow)
		// 11 = No Down Flick
	/* 0x006 */ char prev_y_side;
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
	/* 0x000 */ char unk_00[0x210];
	/* 0x210 */ floatPos cameraPositions[4];
	/* 0x240 */ char unk_21C[0x284-0x240];
	/* 0x284 */ float near;
	/* 0x288 */ char unk_288[0x29C-0x288];
	/* 0x29C */ short action_type;
} SwapObjectData;

typedef struct sandstormData {
	/* 0x000 */ char unk_00[0x54];
	/* 0x054 */ char sandstorm_active;
} sandstormData;

typedef struct snagData {
	/* 0x000 */ char unk_00[0x48];
	/* 0x048 */ char reset;
	/* 0x049 */ char unk_49[0x4B-0x49];
	/* 0x04B */ char reset_next;
	/* 0x04C */ char unk_4C[0x54-0x4C];
	/* 0x054 */ char check;
	/* 0x055 */ char unk_55[0x60-0x55];
	/* 0x060 */ char state;
	/* 0x061 */ char unk_61[0x9B-0x61];
	/* 0x09B */ char resettrigger;
} snagData;

typedef struct ModelTwoData {
	/* 0x000 */ char unk_00[0x7C];
	/* 0x07C */ void* behaviour_pointer;
	/* 0x080 */ char unk_80[0x84-0x80];
	/* 0x084 */ short object_type;
	/* 0x086 */ char unk_86[0x2];
	/* 0x088 */ short sub_id;
	/* 0x08A */ short object_id;
	/* 0x08C */ char unk_8C[0x4];
} ModelTwoData;

typedef struct WarpInfo {
	/* 0x000 */ short xPos;
	/* 0x002 */ short yPos;
	/* 0x004 */ short zPos;
	/* 0x006 */ unsigned char facing_angle; // (val / 255) * 4096
	/* 0x007 */ unsigned char camera_angle; // (player + 0x284)->0x15F
	/* 0x008 */ char will_autowalk;
	/* 0x009 */ char spawn_at_origin;
} WarpInfo;

typedef struct savedSettings {
	/* 0x000 */ char hasSavedData;
	/* 0x001 */ char kongColors[5];
	/* 0x006 */ char quickStartup;
	/* 0x007 */ char forcedStorySkip;
	/* 0x008 */ char pauseVolume;
	/* 0x009 */ char navigateMenuMode;
	/* 0x00A */ char DPadLRFunction;
	/* 0x00B */ char DPadDFunction;
	/* 0x00C */ char displaySavePrompt;
	/* 0x00D */ char precision;
	/* 0x00E */ char input_quadrant;
	/* 0x00F */ char transform_autostock;
	/* 0x010 */ char krool_round_setting;
	/* 0x011 */ char file_init_qol;
	/* 0x012 */ char input_max;
	/* 0x013 */ char console;
	/* 0x014 */ char input_type;
	/* 0x015 */ char jetman_color;
	/* 0x016 */ char savestate_bitfield;
	/* 0x017 */ char disable_sfx;
	/* 0x018 */ char disable_save_combo;
	/* 0x019 */ unsigned char disabled_object_fixes;
} savedSettings;

typedef struct flagMenuData {
	/* 0x000 */ const short* flagArray;
	/* 0x004 */ const char* flagTypeArray;
	/* 0x008 */ const int* flagText;
	/* 0x00C */ char screenIndex;
	/* 0x00D */ char flagCount;
} flagMenuData;

typedef struct customFlagData {
	/* 0x000 */ short byte;
	/* 0x002 */ char bit;
	/* 0x003 */ char type;
	/* 0x004 */ char set;
} customFlagData;

typedef struct cutsceneInfo {
	/* 0x000 */ char csdata[0xC];
} cutsceneInfo;

typedef struct cutsceneType {
	/* 0x000 */ char unk_00[0xD0];
	/* 0x0D0 */ cutsceneInfo* cutscene_databank;
} cutsceneType;

typedef struct spriteDisplay {
	/* 0x000 */ int disappear;
	/* 0x004 */ char unk_04[0x11];
	/* 0x015 */ char unk_15;
} spriteDisplay;

typedef struct spriteControl {
	/* 0x000 */ float movement_style;
	/* 0x004 */ float pointer_offset_0x15;
	/* 0x008 */ float xPos;
	/* 0x00C */ float yPos;
	/* 0x010 */ float scale;
	/* 0x014 */ float unk_14;
	/* 0x018 */ int unk_18;
	/* 0x01C */ int unk_1C;
} spriteControl;

typedef struct otherSpriteControl {
	/* 0x000 */ char unk_000[0x28];
	/* 0x028 */ unsigned char left_stretch;
	/* 0x029 */ unsigned char right_stretch;
	/* 0x02A */ unsigned char up_stretch;
	/* 0x02B */ unsigned char down_stretch;
	/* 0x02C */ char unk_02C[0x340-0x2C];
	/* 0x340 */ float xPos;
	/* 0x344 */ float yPos;
	/* 0x348 */ char unk_348[8];
	/* 0x350 */ char gif_update_frequency;
	/* 0x351 */ char unk_351[0xB];
	/* 0x35C */ spriteControl* gif_control_pointer;
	/* 0x360 */ float xScale;
	/* 0x364 */ float yScale;
	/* 0x368 */ char unk_368[0x2];
	/* 0x36A */ char transparency1;
	/* 0x36B */ char transparency2;
	/* 0x36C */ char transparency3;
	/* 0x36D */ char transparency4;
	/* 0x36E */ char unk_36E[0x384-0x36E];
	/* 0x384 */ int* some_pointer;
} otherSpriteControl;

typedef struct submapInfo {
	/* 0x000 */ char in_submap;
	/* 0x001 */ char unk_01;
	/* 0x003 */ short transition_properties_bitfield;
	/* 0x004 */ char unk_04[0x12-4];
	/* 0x012 */ short parent_map;
	/* 0x014 */ char parent_exit;
} submapInfo;

typedef struct MinigameController {
	/* 0x000 */ char unk_00[0x1C5];
	/* 0X000 */ char hit_count;
} MinigameController;

typedef struct aggrBoxInfo {
	/* 0x000 */ shortPos position[255];
} aggrBoxInfo;

typedef struct movementBoxInfo {
	/* 0x000 */ char unk_00[0x8];
	/* 0x008 */ short count;
	/* 0x00A */ char unk_0A[0x2];
	/* 0x00C */ aggrBoxInfo* unk_ptr;
	/* 0x010 */ char unk_10[0x30-0x10];
} movementBoxInfo;

typedef struct SpawnerInfo {
	/* 0x000 */ unsigned char enemy_value;
	/* 0x001 */ char unk_01;
	/* 0x002 */ short yRot;
	/* 0x004 */ short xPos;
	/* 0x006 */ short yPos;
	/* 0x008 */ short zPos;
	/* 0x00A */ char cs_model;
	/* 0x00B */ char unk_0B;
	/* 0x00C */ unsigned char max_idle_speed;
	/* 0x00D */ unsigned char max_aggro_speed;
	/* 0x00E */ char unk_0E;
	/* 0x00F */ char scale;
	/* 0x010 */ char aggro_index;
	/* 0x011 */ char unk_11;
	/* 0x012 */ char init_spawn_state;
	/* 0x013 */ char spawn_trigger;
	/* 0x014 */ char respawnTimerInit;
	/* 0x015 */ char unk_15[0x18-0x15];
	/* 0x018 */ void* tied_actor;
	/* 0x01C */ movementBoxInfo* movement_box;
	/* 0x020 */ void* unk_20;
	/* 0x024 */ short respawn_timer;
	/* 0x026 */ char unk_26[0x3C-0x26];
	/* 0x03C */ float unk_3C;
	/* 0x040 */ short chunk;
	/* 0x042 */ char spawn_state;
	/* 0x043 */ char counter;
	/* 0x044 */ unsigned char alt_enemy_value;
	/* 0x045 */ char unk_45;
	/* 0x046 */ short unk_46;
} SpawnerInfo;

typedef struct pppanicController {
	/* 0x000 */ char unk_00[0x1B1];
	/* 0x1B1 */ char hit_count1;
	/* 0x1B2 */ char unk_1B2;
	/* 0x1B3 */ char hit_count2;
} pppanicController;

typedef struct krazykkcontroller {
	/* 0x000 */ char unk_00[0x1BD];
	/* 0x1BD */ char hit_count1;
	/* 0x1BE */ char unk_1BE;
	/* 0x1BF */ char hit_count2;
} krazykkcontroller;

typedef struct slotArray {
	/* 0x000 */ char unk_10[0x16];
	/* 0x016 */ short hit_count;
} slotArray;

typedef struct bbbanditcontroller {
	/* 0x000 */ char unk_00[0x11C];
	/* 0x11C */ actorData* slot_pointer;
	/* 0x120 */ char unk_120[0x154-0x120];
	/* 0x154 */ char control_state;
	/* 0x155 */ char unk_155[0x174-0x155];
	/* 0x174 */ slotArray* handle_pointer;
} bbbanditcontroller;

typedef struct bbbashcontroller {
	/* 0x000 */ char unk_00[0x1A1];
	/* 0x1A1 */ char hit_count;
} bbbashcontroller;

typedef struct kkoshcontroller {
	/* 0x000 */ char unk_00[0x1CB];
	/* 0x1CB */ char hit_count;
} kkoshcontroller;

typedef struct sseekcontroller {
	/* 0x000 */ char unk_00[0x19F];
	/* 0x19F */ char hit_count;
} sseekcontroller;

typedef struct SpawnerArray {
	/* 0x000 */ SpawnerInfo SpawnerData[120];
} SpawnerArray;

typedef struct SpawnerMasterInfo {
	/* 0x000 */ short count;
	/* 0x002 */ char unk_02[2];
	/* 0x004 */ SpawnerArray* array;
} SpawnerMasterInfo;

typedef struct undoFlagData {
	/* 0x000 */ short encoded_flag;
	/* 0x002 */ char output;
	/* 0x003 */ char flag_type;
	/* 0x004 */ char flag_stored;
} undoFlagData;

typedef struct flagLogData {
	/* 0x000 */ short encoded_flag;
	/* 0x002 */ char output;
	/* 0x003 */ char flag_type;
	/* 0x004 */ int set_frame;
} flagLogData;

typedef struct filestateInfo {
	/* 0x000 */ char perm_flags[0x140];
	/* 0x140 */ char moves_base[0x1D6];
	/* 0x316 */ short xPos;
	/* 0x318 */ short yPos;
	/* 0x31A */ short zPos;
	/* 0x31C */ char unk_31c[0x4];
	/* 0x320 */ char inventory[0xD];
	/* 0x32D */ unsigned char map;
	/* 0x32E */ char kong;
	/* 0x32F */ char unk_32f;
	/* 0x330 */ char temp_flags[0x10];
} filestateInfo;

typedef struct loadedActorArr {
	/* 0x000 */ actorData* actor;
	/* 0x004 */ int unk_04;
} loadedActorArr;

typedef struct actorNames {
	/* 0x000 */ char actor_name[344][0x10];
} actorNames;

typedef struct actorSpawnerData {
	/* 0x000 */ char unk_00[4];
	/* 0x004 */ floatPos positions;
	/* 0x010 */ char unk_10[0x44-0x10];
	/* 0x044 */ void* tied_actor;
	/* 0x048 */ char unk_48[0x5A-0x58];
	/* 0x05A */ short id;
	/* 0x05C */ char unk_5C[0x64-0x5C];
	/* 0x064 */ void* previous_spawner;
	/* 0x068 */ void* next_spawner;
} actorSpawnerData;

typedef union snagTableInfo {
    int data;
    struct {
        /* 0x000 */ short map;
        /* 0x002 */ short om2_id;
    };
} snagTableInfo;

typedef union encodedSnagState {
	unsigned int data;
	struct {
		/* 0x000 */ char state;
		/* 0x001 */ char check;
		/* 0x002 */ char reset;
		/* 0x003 */ char spawned;
	};
} encodedSnagState;

typedef union phaseInputs {
    int data;
    struct {
        /* 0x000 */ unsigned short buttons;
        /* 0x002 */ char stickX;
        /* 0x003 */ char stickY;
    };
} phaseInputs;

typedef struct heap {
	/* 0x000 */ void* unk;
	/* 0x004 */ int size;
	/* 0x008 */ void* next;
	/* 0x00C */ void* prev;
} heap;

typedef struct stickTestData {
	/* 0x000 */ char mag_max;
	/* 0x001 */ char mag_threshold;
} stickTestData;

typedef struct fairyInfo {
	/* 0x000 */ short max_dist_allowed;
	/* 0x002 */ short xPos;
	/* 0x004 */ short yPos;
} fairyInfo;

typedef struct charSpawnerData {
	/* 0x000 */ short actor_type;
	/* 0x002 */ short actor_behaviour;
	/* 0x004 */ char unk_04[0x18-0x4];
} charSpawnerData;

typedef struct uniqueSpawnFunction {
	/* 0x000 */ int actor_type;
	/* 0x004 */ int func;
} uniqueSpawnFunction;

typedef struct actorWrapperParams {
	/* 0x000 */ short actor_type;
	/* 0x002 */ short actor_behaviour;	
} actorWrapperParams;

typedef struct forceSpawnActorData {
	/* 0x000 */ short actor_type;
} forceSpawnActorData;

typedef struct arcadeObject {
	/* 0x000 */ float x;
	/* 0x004 */ float y;
	/* 0x008 */ float x_velocity;
	/* 0x00C */ float y_velocity;
	/* 0x010 */ char unk_10[0x14-0x10];
	/* 0x014 */ void* image_data_pointer;
	/* 0x018 */ char type;
	/* 0x019 */ char movement;
	/* 0x01A */ char unk_1A[0x1D-0x1A];
	/* 0x01D */ char jump_init_y;
	/* 0x01E */ char unk_1E[0x20-0x1E];
} arcadeObject;

typedef struct arcadeObjectBase {
	/* 0x000 */ arcadeObject object[0x50];
} arcadeObjectBase;

typedef struct arcadeMoveFloor {
	/* 0x000 */ float x;
	/* 0x004 */ float y;
	/* 0x008 */ float y_velocity;
} arcadeMoveFloor;

typedef struct arcadeMoveFloorBase {
	/* 0x000 */ arcadeMoveFloor floor[6];
} arcadeMoveFloorBase;

typedef struct arcadeSavestate {
	/* 0x000 */ arcadeObjectBase* base;
	/* 0x004 */ int RNG;
	/* 0x008 */ int global_timer;
	/* 0x00C */ int level_timer;
	/* 0x010 */ char map;
	/* 0x011 */ char level;
	/* 0x012 */ char mode;
	/* 0x013 */ char stored;
	/* 0x014 */ char lives;
	/* 0x015 */ char jumpman_index;
	/* 0x016 */ char bonus_timer;
	/* 0x017 */ unsigned char rivet_bitfield;
	/* 0x018 */ int current_score;
	/* 0x01C */ int high_score;
	/* 0x020 */ int song;
	/* 0x024 */ int hammer_timer;
	/* 0x028 */ arcadeMoveFloorBase* floors;
} arcadeSavestate;

typedef enum console {
    NONE,
    N64,
    WIIU,
    EMULATOR,
} console;

typedef enum data_indexes {
	Music_MIDI,
	Map_Geometry,
	Map_Walls,
	Map_Floors,
	ModelTwo_Geometry,
	Actor_Geometry,
	Unk06,
	Textures_Uncompressed,
	Cutscenes,
	Map_Setups,
	Map_Object_Scripts,
	Animations,
	Text,
	Unk0D,
	Textures,
	Map_Paths,
	Map_Character_Spawners,
	Unk11,
	Map_Loading_Zones,
	Unk13,
	Unk14,
	Map_Autowalks,
	Unk16,
	Map_Exits,
	Map_Race_Checkpoints,
	Textures_2,
	Uncompressed_File_Sizes,
	Unk1B,
	Unk1C,
	Unk1D,
	Unk1E,
	Unk1F,
	Unk20,
} data_indexes;

typedef enum load_modes {
	SAVESTATE,
	MAPWARP,
} load_modes;

typedef struct parentMaps {
	/* 0x000 */ char in_submap;
	/* 0x001 */ char unk_01;
	/* 0x002 */ unsigned short transition_properties_bitfield;
	/* 0x004 */ floatPos positions;
	/* 0x010 */ short facing_angle;
	/* 0x012 */ short map;
	/* 0x014 */ unsigned char exit;
	/* 0x015 */ char unk_15[0x18-0x15];
	/* 0x018 */ void* setup_pointer;
	/* 0x01C */ int behaviour_load;
	/* 0x020 */ char unk_1C[0xC0-0x20];
} parentMaps;

typedef struct LZTrigger {
	/* 0x000 */ shortPos position;
	/* 0x006 */ short radius;
	/* 0x008 */ short height;
	/* 0x00A */ short unk0A;
	/* 0x00C */ char activation_type;
	/* 0x00D */ char unk_0D[0x10-0xD];
	/* 0x010 */ short trigger_type;
	/* 0x012 */ short map;
	/* 0x014 */ short exit;
	/* 0x016 */ short unk_16;
	/* 0x018 */ short unk_18;
	/* 0x01A */ short cutscene_is_tied;
	/* 0x01C */ short cutscene_activated;
	/* 0x01E */ short shift_camera_to_kong;
	/* 0x020 */ char unk_20[0x38-0x20];
	/* 0x038 */ char not_in_zone;
	/* 0x039 */ char active;
} LZTrigger;

typedef struct hud_element {
	/* 0x000 */ void* item_count_pointer;
	/* 0x004 */ short visual_item_count;
	/* 0x006 */ short hud_state_timer;
	/* 0x008 */ int x;
	/* 0x00C */ int y;
	/* 0x010 */ float unk_10[4];
	/* 0x020 */ int hud_state;
	/* 0x024 */ char unk_24[0x2C-0x24];
	/* 0x02C */ char is_infinite;
	/* 0x02D */ char infinite_check;
	/* 0x02E */ char unk_2E[2];
} hud_element;

typedef struct hudData {
	/* 0x000 */ hud_element item[0xE];
} hudData;

typedef struct text_struct {
	/* 0x000 */ unsigned char width;
	/* 0x001 */ unsigned char file_count;
	/* 0x002 */ unsigned char height;
	/* 0x003 */ char kerning_space;
	/* 0x004 */ char kerning_char;
	/* 0x005 */ char kerning_anim;
} text_struct;

typedef enum codecs {
    IA4,
    IA8,
    RGBA16,
    RGBA32,
} codecs;

typedef enum freeze_sizes {
	SIZE_BYTE,
	SIZE_SHORT,
	SIZE_INT,
	SIZE_HEXDIG,
	SIZE_UNKNOWN,
} freeze_sizes;

typedef struct freeze_struct {
	/* 0x000 */ int* addr;
	/* 0x004 */ unsigned int value;
	/* 0x008 */ freeze_sizes size;
	/* 0x00C */ int used;
} freeze_struct;

typedef struct floor_tri {
	/* 0x000 */ short x[3];
	/* 0x006 */ short y[3];
	/* 0x00C */ short z[3];
	/* 0x012 */ unsigned short state_bitfield;
	/* 0x014 */ short sfx;
	/* 0x016 */ unsigned char brightness;
	/* 0x017 */ char unk_17;
} floor_tri;

typedef struct floor_tri_data {
	/* 0x000 */ int* rdram_start;
	/* 0x004 */ int* rdram_end;
	/* 0x008 */ int model2_timer;
	/* 0x00C */ int rom_start;
	/* 0x010 */ int size;
} floor_tri_data;

typedef struct chunk_struct {
	/* 0x000 */ char loaded;
	/* 0x001 */ char unk_001[0x1C8-0x1];
} chunk_struct;

typedef struct competitor_struct {
	/* 0x000 */ int level;
	/* 0x004 */ int score;
	/* 0x008 */ int lives;
	/* 0x00C */ int lives_consumed;
	/* 0x010 */ int unk_010;
	/* 0x014 */ char unk_014[0x114-0x14];
	/* 0x114 */ int unk_114;
	/* 0x118 */ char unk_118[0x194-0x118];

} competitor_struct;

typedef struct jetpac_item1_struct {
	/* 0x000 */ float x;
	/* 0x004 */ float y;
	/* 0x008 */ float velocity_x;
	/* 0x00C */ float velocity_y;
	/* 0x010 */ unsigned char red;
	/* 0x011 */ unsigned char green;
	/* 0x012 */ unsigned char blue;
	/* 0x013 */ char unk_13;
	/* 0x014 */ int state;
	/* 0x018 */ int facing_direction;
	/* 0x01C */ int hitbox_xl;
	/* 0x020 */ int hitbox_yt;
	/* 0x024 */ int hitbox_xr;
	/* 0x028 */ int hitbox_yb;
	/* 0x02C */ int spawn_timer;
	/* 0x030 */ int width;
} jetpac_item1_struct;

typedef struct collision_struct {
	/* 0x000 */ int header;
	/* 0x004 */ int unk_04;
	/* 0x008 */ void* targetActor;
	/* 0x00C */ int unk_0C;
	/* 0x010 */ int unk_10;
	/* 0x014 */ void* next_collision;
	/* 0x018 */ void* previous_collision;
} collision_struct;

typedef struct overlay_struct {
	/* 0x000 */ void* draw_code;
	/* 0x004 */ actorData* actor;
	/* 0x008 */ char order;
	/* 0x009 */ char unk_09[0xC-0x9];
} overlay_struct;

typedef enum file_state_indexes {
	NLE_GENERAL_JAPES1,
	NLE_HELMESCAPE_AZTEC,
	NLE_HELMESCAPE_FACTORY,
	NLE_HELMESCAPE_JAPES2,
	NLE_HELMESCAPE_GALLEON,
	NLE_HELMESCAPE_FUNGI,
	NLE_HELMESCAPE_CAVES,
	NLE_HELMESCAPE_CASTLE,
	NLE_HELMESCAPE_HELM,
	NLE_HELMESCAPE_TAKEOFF,
	NLE_40BP_AZTEC1,
	NLE_40BP_FACTORY,
	NLE_40BP_JAPES2,
	NLE_40BP_GALLEON,
	NLE_40BP_FUNGI,
	NLE_40BP_CAVES,
	NLE_40BP_CASTLE,
	NLE_40BP_AZTEC2,
	NLE_40BP_HELM,
	GENERAL_EMPTY,
	_101ORG_CAVES1,
	_101ORG_JAPES1,
	_101ORG_AZTEC1,
	_101ORG_FACTORY,
	_101ORG_GALLEON,
	_101ORG_HELM,
	_101ORG_CASTLE,
	_101ORG_AZTEC2,
	_101ORG_AZTEC2_ALT,
	_101ORG_CAVES2,
	_101ORG_JAPES2,
	_101GEN_FUNGI,
	_101JFM_AZTEC1,
	_101JFM_CASTLE1,
	_101JFM_JAPES,
	_101JFM_FACTORY,
	_101JFM_GALLEON,
	_101JFM_HELM,
	_101JFM_CASTLE2,
	_101JFM_AZTEC2,
	_101JFM_CAVES,
	GLITCHLESS_ANY_JAPES1,
	GLITCHLESS_ANY_AZTEC,
	GLITCHLESS_ANY_FACTORY,
	GLITCHLESS_ANY_JAPES2,
	GLITCHLESS_ANY_GALLEON,
	GLITCHLESS_ANY_FUNGI,
	GLITCHLESS_ANY_CAVES,
	GLITCHLESS_ANY_CASTLE,
	GLITCHLESS_ANY_HELM,
} file_state_indexes;

typedef struct heap_arena_struct {
	/* 0x000 */ void* index_pointer;
	/* 0x004 */ void* start;
	/* 0x008 */ void* tail_pointer;
	/* 0x00C */ unsigned int bin_size;
	/* 0x010 */ unsigned short chunk_data_size;
	/* 0x012 */ char unk_12[2];
} heap_arena_struct;

typedef struct dynamicWatchStruct {
	/* 0x000 */ void* address;
	/* 0x004 */ short size;
	/* 0x006 */ char watch_index;
	/* 0x007 */ char used;
} dynamicWatchStruct;

typedef struct guard_paad {
    /* 0x000 */ char unk_00[0x3C];
    /* 0x03C */ actorData* tied_sphere;
    /* 0x040 */ float sphere_x;
    /* 0x044 */ float sphere_z;
} guard_paad;