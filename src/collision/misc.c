#include "../../include/common.h"

void spawnGuardSphere(actorData* actor) {
    guard_paad* paad = actor->paad;
    float sphere_radius = 70.0f * 0.055f;
    spawnCollision(2,paad->sphere_x,actor->yPos-70.0f,paad->sphere_z,sphere_radius,sphere_radius,sphere_radius,actor,0xFF,0x00,0x00,0x80,0);
}

static const unsigned char snoop_maps[] = {0xB,0x41,0x7E,0x7F,0x80};

void controlGuardSpheres(void) {
    if (altCollisionEnabled & 1) {
        int in_snoop = 0;
        for (int i = 0; i < sizeof(snoop_maps); i++) {
            if (CurrentMap == snoop_maps[i]) {
                in_snoop = 1;
            }
        }
        if (in_snoop) {
            for (int i = 0; i < ActorCount; i++) {
                actorData* actor = (actorData*)ActorArray[i];
                if (actor) {
                    if (actor->actorType == 259) {
                        guard_paad* paad = actor->paad;
                        if (paad->tied_sphere == 0) {
                            spawnGuardSphere(actor);
                            paad->tied_sphere = (actorData*)CurrentActorPointer;
                        } else {
                            paad->tied_sphere->xPos = paad->sphere_x;
                            paad->tied_sphere->yPos = actor->yPos - 70.0f;
                            paad->tied_sphere->zPos = paad->sphere_z;
                        }
                    }
                }
            }
        }
    }
}

static char collisionhead_snoop[30] = "";

static char* collisionheads[] = {
    "SNOOP SPHERES"
};

static char* colmisc_array[] = {
	collisionhead_snoop,
};

void openCollisionMisc(void) {
    for (int i = 0; i < sizeof(collisionheads)/4; i++) {
        if (altCollisionEnabled & (1 << i)) {
            dk_strFormat(colmisc_array[i],"} %s",collisionheads[i]);
        } else {
            dk_strFormat(colmisc_array[i],"{ %s",collisionheads[i]);
        }
    }
    changeMenu(ACTIVEMENU_SCREEN_COLLISION_MISC);
}

void toggleMisc(void) {
    int position = ActiveMenu.positionIndex;
    int shift = 1 << position;
    if (altCollisionEnabled & shift) {
        altCollisionEnabled &= (0xFF - shift);
    } else {
        altCollisionEnabled |= shift;
    }
    destroyAllCollision();
    openCollisionMisc();
}

static const int colmisc_functions[] = {
    (int)&toggleMisc,
};

const Screen colmisc_struct = {
	.TextArray = (int*)colmisc_array,
	.FunctionArray = colmisc_functions,
	.ArrayItems = 1,
	.ParentScreen = ACTIVEMENU_SCREEN_COLLISION_ROOT,
	.ParentPosition = 1,
};