#include "../../include/common.h"

#define COLLISION_CUBE 0
#define COLLISION_CYLINDER 1
#define COLLISION_SPHERE 2

// static const unsigned char collision_models[] = {0xE8,0x8F,0xBC};
static const unsigned char collision_models[] = {0xED,0xEE,0xEF};

void spawnCollision(int subtype, float x, float y, float z, float height, float width, float depth, void* uuid, int red, int green, int blue, int alpha, int force_y) {
    for (int i = 0; i < ActorCount; i++) {
        actorData* test_actor = (actorData*)ActorArray[i];
        if (test_actor->actorType == 1) {
            collision_paad* test_paad = (collision_paad*)test_actor->paad;
            if (test_paad) {
                if ((int)uuid == (int)test_paad->attached_attribute) {
                    return;
                }
            }
        }
    }
    int model_offset = 0;
    if (collisiondrawmode > 0) {
        model_offset = sizeof(collision_models);
    }
    spawnActor(1,collision_models[subtype] + model_offset);
    actorData* actor = (actorData*)CurrentActorPointer;
    actor->xPos = x;
    actor->yPos = y;
    actor->zPos = z;
    actor->red = red;
    actor->green = green;
    actor->blue = blue;
    actor->obj_props_bitfield |= 0x00800000;
    actor->noclip = 1;
    collision_paad* paad = (collision_paad*)actor->paad;
    if (paad) {
        paad->countdown = 1;
        paad->xScale = width;
        paad->yScale = height;
        paad->zScale = depth;
        paad->subtype = subtype;
        paad->attached_attribute = uuid;
        paad->force_y = force_y;
    }
}

int getCollisionModel(int subtype, int drawmode) {
    int model_offset = 0;
    if (drawmode > 0) {
        model_offset = sizeof(collision_models);
    }
    return collision_models[subtype] + model_offset;
}

void spawnUnitSphere(float x_center, float y_center, float z_center, float radius, void* uuid, int red, int green, int blue, int alpha, int follow) {
    float scaled_radius = radius * 0.055f;
    spawnCollision(COLLISION_SPHERE, x_center, y_center - radius, z_center, scaled_radius, scaled_radius, scaled_radius, uuid, red, green, blue, alpha, follow);
}

void* getCollisionUUID(actorData* actor) {
    collision_paad* paad = (collision_paad*)(actor->paad);
    return paad->attached_attribute;
}

void destroyAllCollision(void) {
    for (int i = 0; i < ActorCount; i++) {
        actorData* actor = (actorData*)(ActorArray[i]);
        if (actor) {
            if (actor->actorType == 1) {
                deleteActorContainer(actor);
            } else if (actor->actorType == 259) {
                guard_paad* paad = actor->paad;
                paad->tied_sphere = 0;
            }
        }
    }
    resetQuadCache();
}

#define FADE_LIMIT 5
void collisionCode(void) { 
    actorData* actor = (actorData*)CurrentActorPointer_0;
    collision_paad* paad = (collision_paad*)actor->paad;
    if ((actor->obj_props_bitfield & 0x10) == 0) {
        // Init
        actor->noclip = 1;
        if (paad) {
            paad->fade_countdown = FADE_LIMIT;
        }
        if (collisiondrawmode != 2) {
            actor->obj_props_bitfield &= 0xFFFF7FFF;
            if (collisiondrawmode == 0) {
                actor->shadow_intensity = 120;
            } else {
                actor->shadow_intensity = 50;
            }
        }
    }
    if (paad) {
        int countdown = paad->countdown;
        if (countdown > 1) {
            paad->countdown -= 1;
        } else if (countdown <= 1) {
            if (countdown == 1) {
                renderingParamsData* render = actor->render_pointer;
                if (render) {
                    render->scale_x = paad->xScale * 0.15f;
                    render->scale_y = paad->yScale * 0.15f;
                    render->scale_z = paad->zScale * 0.15f;
                }
            }
            paad->countdown = 0;
        }
        int fade = paad->fade_countdown;
        if (fade > 0) {
            paad->fade_countdown -= 1;
        } else {
            paad->fade_countdown = 0;
        }
        if (paad->force_y) {
            if (Player) {
                actor->yPos = Player->yPos - 20;
            }
        }
    }
    renderActor(CurrentActorPointer_0,0);
}