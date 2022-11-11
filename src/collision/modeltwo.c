#include "../../include/common.h"

static char m2colname_player[31] = "";
static char m2colname_unload[30] = "";
static char m2colname_item[30] = "";

static char* modeltwocol_toggleheads[] = {
    "PLAYER ITEM COLLISION SPHERE",
    "HIDE UNLOADED ITEMS",
    "ITEM COLLISIONS"
};

static char* modeltwocol_array[] = {
    m2colname_player,
    m2colname_unload,
    m2colname_item,
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
    resetQuadCache();
    openModelTwoMenu();
}

typedef struct sphere_cache_struct {
    /* 0x000 */ void* actor;
    /* 0x004 */ short id;
} sphere_cache_struct;

static int quad_cache_x = -100;
static int quad_cache_z = -100;
static unsigned char object_item_cache[0x56];
static sphere_cache_struct item_sphere_cache[50];

void wipeSphereCache(void) {
    for (int i = 0; i < 50; i++) {
        if (ObjectModel2Timer < 2) {
            item_sphere_cache[i].actor = 0;
            item_sphere_cache[i].id = -1;
        } else {
            actorData* actor = item_sphere_cache[i].actor;
            if (isRDRAM(actor)) {
                if (actor->actorType == 1) {
                    deleteActorContainer(actor);
                    item_sphere_cache[i].actor = 0;
                    item_sphere_cache[i].id = -1;
                }
            }
        }
    }
}

void handlePlayerCollision(void) {
    if (ObjectModel2Timer < 2) {
        resetQuadCache();
    }
    int player_quad_x = Player->xPos / 500;
    int player_quad_z = Player->zPos / 500;
    int update = 0;
    if ((player_quad_x != quad_cache_x) || (player_quad_z != quad_cache_z)) {
        update = 1;
    }
    quad_cache_x = player_quad_x;
    quad_cache_z = player_quad_z;
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
                actor->yPos = PlayerCollisions[0].y - PlayerCollisions[0].scale;
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
                spawnUnitSphere(collision->x, collision->y, collision->z, collision->scale, Player, 0xFF, 0, 0, 0x80, 0);
            }
        }
    }
    if (modeltwo_viewable & 2) {
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
    if (modeltwo_viewable & 4) {
        if (update) {
            // Replace object
            wipeSphereCache();
            int placement_index = 0;
            for (int i = 0; i < ObjectModel2Count; i++) {
                ModelTwoData* item = (ModelTwoData*)&ObjectModel2Pointer[i];
                int type = item->object_type;
                int offset = type >> 3;
                int shift = type & 7;
                if (object_item_cache[offset] & (1 << shift)) {
                    int item_quad_x = item->x / 500;
                    int item_quad_z = item->z / 500;
                    if ((item_quad_x == player_quad_x) && (item_quad_z == player_quad_z)) {
                        int j = 0;
                        modeltwo_collision_info* info = 0;
                        while (j < 42) {
                            if (ModelTwoCollisionInfo[j].type == type) {
                                info = (modeltwo_collision_info*)&ModelTwoCollisionInfo[j];
                                break;
                            }
                            j++;
                        }
                        if (info->hitbox_scale != 0) {
                            spawnUnitSphere(item->x, item->y + info->hitbox_y_center, item->z, info->hitbox_scale, item, 0, 0xFF, 0, 0xFF, 0);
                            item_sphere_cache[placement_index].actor = CurrentActorPointer;
                            item_sphere_cache[placement_index].id = item->object_id;
                            placement_index += 1;
                        }
                    }
                }
            }
        } else {
            // for (int i = 0; i < 50; i++) {
            //     int k = 0;
            //     while ()
            //     ModelTwoData* object = item_sphere_cache[i].modeltwo;
            //     if (object) {
            //         actorData* actor = item_sphere_cache[i].actor;
            //         if (object->object_id == item_sphere_cache[i].id) {
            //             int j = 0;
            //             modeltwo_collision_info* info = 0;
            //             while (j < 42) {
            //                 if (ModelTwoCollisionInfo[j].type == object->object_type) {
            //                     info = (modeltwo_collision_info*)&ModelTwoCollisionInfo[j];
            //                     break;
            //                 }
            //                 j++;
            //             }
            //             if (info) {
            //                 if (info->hitbox_scale != 0) {
            //                     actor->xPos = object->x;
            //                     actor->yPos = object->y + info->hitbox_y_center - info->hitbox_scale;
            //                     actor->zPos = object->z;
            //                 }
            //             }
            //         } else {
            //             if (isRDRAM(actor)) {
            //                 if (actor->actorType == 1) {
            //                     item_sphere_cache[i].modeltwo = 0;
            //                     deleteActorContainer(actor);
            //                     item_sphere_cache[i].actor = 0;
            //                     item_sphere_cache[i].id = -1;
            //                 }
            //             }
            //         }
            //     }
            // }
        }
    }
}

void updateItemCache(void) {
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
}

void resetQuadCache(void) {
    quad_cache_x = -100;
    quad_cache_z = -100;
}

void resetQuadrantScales(void) {
    updateItemCache();
    for (int i = 0; i < ObjectModel2Count; i++) {
        ModelTwoData* item = (ModelTwoData*)&ObjectModel2Pointer[i];
        ModelTwoModel* model = item->model;
        if (model) {
            model->scale = item->scale;
        }
    }
}

void resetQuadrantSpheres(void) {
    updateItemCache();
    wipeSphereCache();
    toggleModelTwoItem();
}

void toggleQuadrant(void) {
    resetQuadrantScales();
    wipeSphereCache();
    toggleModelTwoItem();
}

static const int modeltwocol_functions[] = {
    (int)&toggleModelTwoItem,
    (int)&toggleQuadrant,
    (int)&resetQuadrantSpheres,
};

const Screen modeltwocol_struct = {
	.TextArray = (int*)modeltwocol_array,
	.FunctionArray = modeltwocol_functions,
	.ArrayItems = 3,
	.ParentScreen = ACTIVEMENU_SCREEN_COLLISION_ROOT,
	.ParentPosition = 1,
};