#include "../../include/common.h"

static const int trigger_rgb[] = {
    0xFF0000, // Loading Zone
    0x00FF00, // Cutscene Trigger
    0x0000FF, // Autowalk
    0xFF00FF, // State
    0x00FFFF, // Weather
    0xFFFF00, // Object Control
    0xFFFFFF, // Cheat
};

void spawnLoadingZone(float x, float y, float z, int radius, int height, void* uuid, int type) {
    float r_f = radius;
    float h_f = height;
    if (height == -1) {
        h_f = 50.0f;
    }
    r_f *= 0.055f;
    h_f *= 0.0205f;
    int red = (trigger_rgb[type] >> 16) & 0xFF;
    int green = (trigger_rgb[type] >> 8) & 0xFF;
    int blue = trigger_rgb[type] & 0xFF;
    // y -= (5.0f * r_f);
    spawnCollision(1,x,y,z,h_f,r_f,r_f,uuid,red,green,blue,0x80,height==-1);
}

#define TRIGGERVIEWER_UD -1 // Undefined
#define TRIGGERVIEWER_LZ 0 // Loading Zone
#define TRIGGERVIEWER_CS 1 // Cutscene Trigger
#define TRIGGERVIEWER_AW 2 // Autowalk
#define TRIGGERVIEWER_ST 3 // State
#define TRIGGERVIEWER_WE 4 // Weather
#define TRIGGERVIEWER_AC 5 // Object Control
#define TRIGGERVIEWER_CH 6 // Cheat

static unsigned char viewer_types[0x27] = {
    TRIGGERVIEWER_AC, // 0x00: Spawn Trigger (0x12 - Character Spawner "Spawn Trigger")
    TRIGGERVIEWER_UD, // 0x01
    TRIGGERVIEWER_AC, // 0x02: Despawn Trigger (0x12 - Character Spawner "Spawn Trigger")
    TRIGGERVIEWER_AC, // 0x03: Boss Door Trigger
    TRIGGERVIEWER_AC, // 0x04: Update Actor Trigger (0x14 - Actor Spawner ID. Makes Rock fall in Fungi Minecart)
    TRIGGERVIEWER_CS, // 0x05: Cutscene Trigger
    TRIGGERVIEWER_WE, // 0x06: Weather Overlay Force Trigger (Spawns DK in treehouse?)
    TRIGGERVIEWER_WE, // 0x07: Weather Overlay Set Trigger
    TRIGGERVIEWER_WE, // 0x08: Weather Overlay Remove Trigger
    TRIGGERVIEWER_LZ, // 0x09: Loading Zone
    TRIGGERVIEWER_CS, // 0x0A: Cutscene Trigger
    TRIGGERVIEWER_AC, // 0x0B: Init TNT Minecart (Minecart Mayhem)
    TRIGGERVIEWER_LZ, // 0x0C: Loading Zone + Objects
    TRIGGERVIEWER_LZ, // 0x0D: Loading Zone
    TRIGGERVIEWER_UD, // 0x0E
    TRIGGERVIEWER_LZ, // 0x0F: Warp Trigger
    TRIGGERVIEWER_LZ, // 0x10: Loading Zone
    TRIGGERVIEWER_LZ, // 0x11: Parent Map Loading Zone
    TRIGGERVIEWER_ST, // 0x12: Coin Shower Trigger
    TRIGGERVIEWER_ST, // 0x13: Detransform Trigger
    TRIGGERVIEWER_LZ, // 0x14: Boss Door LZ
    TRIGGERVIEWER_AW, // 0x15: Autowalk Trigger
    TRIGGERVIEWER_ST, // 0x16: Sound Trigger
    TRIGGERVIEWER_CS, // 0x17: Cutscene Trigger
    TRIGGERVIEWER_UD, // 0x18: In Fungi Minecart? Unsure on function
    TRIGGERVIEWER_UD, // 0x19: Everywhere in Seal Race. Unsure on function?
    TRIGGERVIEWER_ST, // 0x1A: Gravity Trigger
    TRIGGERVIEWER_ST, // 0x1B: Slide Trigger
    TRIGGERVIEWER_ST, // 0x1C: Unslide Trigger
    TRIGGERVIEWER_LZ, // 0x1D: Zipper Trigger
    TRIGGERVIEWER_ST, // 0x1E: Song Trigger
    TRIGGERVIEWER_UD, // 0x1F
    TRIGGERVIEWER_CS, // 0x20: Cutscene Trigger
    TRIGGERVIEWER_UD, // 0x21
    TRIGGERVIEWER_UD, // 0x22
    TRIGGERVIEWER_UD, // 0x23
    TRIGGERVIEWER_ST, // 0x24: Detransform Trigger
    TRIGGERVIEWER_ST, // 0x25: Load Chunk Textures Trigger
    TRIGGERVIEWER_CH, // 0x26: K. Lumsy Cheat Trigger
};

void parseLoadingZones(void) {
    if (triggers_viewable) {
        if (Player) {
            for (int i = 0; i < TriggerCount; i++) {
                LZTrigger* trigger = getObjectArrayAddr(TriggerArray,0x3A,i);
                if (trigger) {
                    int type = trigger->trigger_type;
                    int vtype = viewer_types[type];
                    if (trigger->active) {
                        if (vtype > -1) {
                            if (triggers_viewable & (1 << vtype)) {
                                int t_x = trigger->position.xPos;
                                int t_y = trigger->position.yPos;
                                int t_z = trigger->position.zPos;
                                int p_x = Player->xPos;
                                int p_y = Player->yPos;
                                int p_z = Player->zPos;
                                int dx = t_x - p_x;
                                int dy = t_y - p_y;
                                int dz = t_z - p_z;
                                int y = trigger->position.yPos;
                                if (trigger->height == -1) {
                                    dy = 0;
                                    y = Player->yPos;
                                }
                                int d = (dx * dx) + (dy * dy) + (dz * dz);
                                int view_thresh = 100000;
                                int destroy_limit = view_thresh * 2;
                                if (d < view_thresh) {
                                    spawnLoadingZone(trigger->position.xPos,y,trigger->position.zPos,trigger->radius,trigger->height,trigger,vtype);
                                } else if (d < destroy_limit) {
                                    for (int j = 0; j < ActorCount; j++) {
                                        actorData* actor = (actorData*)(ActorArray[j]);
                                        if (actor) {
                                            if (actor->actorType == 1) {
                                                if ((int)(trigger) == (int)(getCollisionUUID(actor))) {
                                                    deleteActorContainer(actor);
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

static char triggername_lz[30] = "";
static char triggername_cs[30] = "";
static char triggername_aw[30] = "";
static char triggername_st[30] = "";
static char triggername_we[30] = "";
static char triggername_ac[30] = "";
static char triggername_ch[30] = "";

static char* trigger_toggleheads[] = {
    "LOADING ZONES",
    "CUTSCENE TRIGGERS",
    "AUTOWALK TRIGGERS",
    "STATE CHANGE TRIGGERS",
    "WEATHER TRIGGERS",
    "OBJECT CONTROL TRIGGERS",
    "CHEAT TRIGGERS",
};

static char* triggers_array[] = {
    triggername_lz,
    triggername_cs,
    triggername_aw,
    triggername_st,
    triggername_we,
    triggername_ac,
    triggername_ch,
    "TURN OFF ALL",
};

static char drawmode_translucent[] = "DRAW MODE:TRANSLUCENT";
static char drawmode_faketranslucent[] = "DRAW MODE:FAKE TRANSLUCENT";
static char drawmode_opaque[] = "DRAW MODE:OPAQUE";

static char* drawmode_array[] = {
    drawmode_translucent,
    drawmode_faketranslucent,
    drawmode_opaque,
};

static char* colroot_array[] = {
	"TRIGGERS",
    "MODEL TWO",
    "MISC",
    drawmode_translucent,
};

void openCollisionRootMenu(void) {
    colroot_array[3] = drawmode_array[(int)collisiondrawmode];
	changeMenu(ACTIVEMENU_SCREEN_COLLISION_ROOT);
}

void openTriggersMenu(void) {
    for (int i = 0; i < sizeof(trigger_toggleheads)/4; i++) {
        if (triggers_viewable & (1 << i)) {
            dk_strFormat(triggers_array[i],"} %s",trigger_toggleheads[i]);
        } else {
            dk_strFormat(triggers_array[i],"{ %s",trigger_toggleheads[i]);
        }
    }
    changeMenu(ACTIVEMENU_SCREEN_COLLISION_TRIGGERS);
}

void toggledrawmode(void) {
    int old_col_mode = collisiondrawmode;
    collisiondrawmode = (collisiondrawmode + 1) % 3;
    for (int i = 0; i < LoadedActorCount; i++) {
        actorData* actor = (actorData*)LoadedActorArray[i].actor;
        if (actor->actorType == 1) {
            collision_paad* paad = actor->paad;
            int old_model = getCollisionModel(paad->subtype, old_col_mode);
            int new_model = getCollisionModel(paad->subtype, collisiondrawmode);
            if (old_model != new_model) {
                actor->model = 0;
                setModel(actor, new_model);
            }
            if (collisiondrawmode != 2) {
                actor->obj_props_bitfield &= 0xFFFF7FFF;
                if (collisiondrawmode == 0) {
                    actor->shadow_intensity = 120;
                } else {
                    actor->shadow_intensity = 50;
                }
            } else {
                actor->obj_props_bitfield |= 0x8000;
            }
        }
    }
    openCollisionRootMenu();
}

void toggleTrigger(void) {
	int position = ActiveMenu.positionIndex;
    int shift = 1 << position;
    if (triggers_viewable & shift) {
        triggers_viewable &= (0xFF - shift);
    } else {
        triggers_viewable |= shift;
    }
    for (int i = 0; i < ActorCount; i++) {
        actorData* actor = (actorData*)(ActorArray[i]);
        if (actor) {
            if (actor->actorType == 1) {
                deleteActorContainer(actor);
            }
        }
    }
	openTriggersMenu();
}

void toggleAllTriggers(void) {
    triggers_viewable = 0;
    destroyAllCollision();
    openTriggersMenu();
}

static const int colroot_functions[] = {
	(int)&openTriggersMenu,
    (int)&openModelTwoMenu,
    (int)&openCollisionMisc,
    (int)&toggledrawmode,
};

static const int triggers_functions[] = {
    (int)&toggleTrigger,
    (int)&toggleTrigger,
    (int)&toggleTrigger,
    (int)&toggleTrigger,
    (int)&toggleTrigger,
    (int)&toggleTrigger,
    (int)&toggleTrigger,
    (int)&toggleAllTriggers,
};

const Screen colroot_struct = {
	.TextArray = (int*)colroot_array,
	.FunctionArray = colroot_functions,
	.ArrayItems = 4,
	.ParentScreen = ACTIVEMENU_SCREEN_ROOT,
	.ParentPosition = 4,
};

const Screen triggers_struct = {
	.TextArray = (int*)triggers_array,
	.FunctionArray = triggers_functions,
	.ArrayItems = 8,
	.ParentScreen = ACTIVEMENU_SCREEN_COLLISION_ROOT,
	.ParentPosition = 0,
};