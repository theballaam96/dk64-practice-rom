#include "../../include/common.h"

static char m2colname_player[30] = "";
static char m2colname_unload[30] = "";

static char* modeltwocol_toggleheads[] = {
    "PLAYER COLLISION",
    "HIDE UNLOADED ITEMS",
};

static char* modeltwocol_array[] = {
    m2colname_player,
    m2colname_unload,
};

void openModelTwoMenu(void) {
    for (int i = 0; i < sizeof(modeltwocol_toggleheads)/4; i++) {
        if (modeltwo_viewable & (1 << i)) {
            dk_strFormat(modeltwocol_array[i],"} %s",modeltwocol_toggleheads[i]);
        } else {
            dk_strFormat(modeltwocol_array[i],"{ %s",modeltwocol_toggleheads[i]);
        }
    }
    changeMenu(ACTIVEMENU_SCREEN_COLLISION_MODELTWO);
}

void toggleModelTwoItem(void) {
    int position = ActiveMenu.positionIndex;
    int shift = 1 << position;
    if (modeltwo_viewable & shift) {
        modeltwo_viewable &= (0xFF - shift);
    } else {
        modeltwo_viewable |= shift;
    }
    for (int i = 0; i < ActorCount; i++) {
        actorData* actor = (actorData*)(ActorArray[i]);
        if (actor) {
            if (actor->actorType == 1) {
                deleteActorContainer(actor);
            }
        }
    }
    openModelTwoMenu();
}



static int quad_cache_x = -100;
static int quad_cache_z = -100;
static unsigned char object_item_cache[0x56];

void handlePlayerCollision(void) {
    if (modeltwo_viewable & 1) {
        // Player Collision
        if (Player) {
            actorData* actor = 0;
            for (int i = 0; i < LoadedActorCount; i++) {
                actorData* ref_actor = (actorData*)LoadedActorArray[i].actor;
                if (ref_actor) {
                    if (ref_actor->actorType == 1) {
                        collision_paad* paad = ref_actor->paad;
                        if (paad) {
                            if (paad->attached_attribute == Player) {
                                actor = ref_actor;
                            }
                        }
                    }
                }
            }
            if (actor) {
                // Actor found
                actor->xPos = PlayerCollisions[0].x;
                actor->yPos = PlayerCollisions[0].y;
                actor->zPos = PlayerCollisions[0].z;
                renderingParamsData* render = actor->render_pointer;
                if (render) {
                    float ref_scale = PlayerCollisions[0].scale * 0.055f * 0.15f;
                    render->scale_x = ref_scale;
                    render->scale_y = ref_scale;
                    render->scale_z = ref_scale;
                }
            } else {
                // No actor
                player_collision_data* collision = (player_collision_data*)&PlayerCollisions[0];
                float ref_scale = collision->scale * 0.055f;
                spawnCollision(2, collision->x, collision->y - collision->scale, collision->z, ref_scale, ref_scale, ref_scale, Player, 0xFF, 0, 0, 0x80, 0);
            }
        }
    }
    if (modeltwo_viewable & 2) {
        if (ObjectModel2Timer < 2) {
            quad_cache_x = -100;
            quad_cache_z = -100;
        }
        int player_quad_x = Player->xPos / 500;
        int player_quad_z = Player->zPos / 500;
        int update = 0;
        if ((player_quad_x != quad_cache_x) || (player_quad_z != quad_cache_z)) {
            update = 1;
        }
        quad_cache_x = player_quad_x;
        quad_cache_z = player_quad_z;
        if (update) {
            for (int i = 0; i < ObjectModel2Count; i++) {
                ModelTwoData* item = (ModelTwoData*)&ObjectModel2Pointer[i];
                int offset = item->object_type >> 3;
                int shift = item->object_type & 7;
                if (object_item_cache[offset] & (1 << shift)) {
                    int item_quad_x = item->x / 500;
                    int item_quad_z = item->z / 500;
                    if ((item_quad_x == player_quad_x) && (item_quad_z == player_quad_z)) {
                        // Current Quad
                        ModelTwoModel* model = item->model;
                        if (model) {
                            model->scale = item->scale;
                        }
                    } else {
                        ModelTwoModel* model = item->model;
                        if (model) {
                            model->scale = 0;
                        }
                    }
                }
            }
        }
    }
}

void resetQuadrantScales(void) {
    for (int i = 0; i < sizeof(object_item_cache); i++) {
        object_item_cache[i] = 0;
    }
    for (int i = 0; i < 0x2B7; i++) {
        int offset = i >> 3;
        int shift = i & 7;
        int j = 0;
        int is_item = 0;
        while (j < 42) {
            if (ModelTwoCollisionInfo[j].type == i) {
                is_item = 1;
                break;
            }
            j++;
        }
        if (is_item) {
            object_item_cache[offset] |= (1 << shift);
        }
    }
    for (int i = 0; i < ObjectModel2Count; i++) {
        ModelTwoData* item = (ModelTwoData*)&ObjectModel2Pointer[i];
        ModelTwoModel* model = item->model;
        if (model) {
            model->scale = item->scale;
        }
    }
    quad_cache_x = -100;
    quad_cache_z = -100;
}

void toggleQuadrant(void) {
    resetQuadrantScales();
    toggleModelTwoItem();
}

static const int modeltwocol_functions[] = {
    (int)&toggleModelTwoItem,
    (int)&toggleQuadrant,
};

const Screen modeltwocol_struct = {
	.TextArray = (int*)modeltwocol_array,
	.FunctionArray = modeltwocol_functions,
	.ArrayItems = 2,
	.ParentScreen = ACTIVEMENU_SCREEN_COLLISION_ROOT,
	.ParentPosition = 1,
};