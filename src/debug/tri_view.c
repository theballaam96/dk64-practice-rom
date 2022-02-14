#include "../../include/common.h"

#define FLOORTRIANGLE_SIZE 0x18
#define FLOORTRIANGLE_BLOCKSIZE 0x14

#define FLOORTRI_VOID 0x4000
#define FLOORTRI_NONSOLID 0x0800
#define FLOORTRI_DAMAGE 0x0040
#define FLOORTRI_INSTADEATH 0x0010
#define FLOORTRI_WATER 0x0001

#define FLOORTRICAP_NORMAL 40
#define FLOORTRICAP_VOID 20
#define FLOORTRICAP_WATER 20
#define FLOORTRICAP_INSTADEATH 20
#define FLOORTRICAP_DAMAGE 20

typedef struct tri_storage {
	/* 0x000 */ int distance;
	/* 0x004 */ short x_screen[3];
	/* 0x00A */ short y_screen[3];
	/* 0x010 */ unsigned int used;
	/* 0x014 */ char floor_type;
	/* 0x015 */ char unk_15[0x18-0x15];
} tri_storage;

static short floor_shown_bitfield = 0;
// static tri_storage triarray_normal[FLOORTRICAP_NORMAL] = {};
// static tri_storage triarray_void[FLOORTRICAP_VOID] = {};
// static tri_storage triarray_water[FLOORTRICAP_WATER] = {};
// static tri_storage triarray_damage[FLOORTRICAP_DAMAGE] = {};
// static tri_storage triarray_instadeath[FLOORTRICAP_INSTADEATH] = {};

#define SCREEN_XMIN 40
#define SCREEN_YMIN 40
#define SCREEN_XMAX 1240
#define SCREEN_YMAX 920
#define SCREEN_XCEN 640
#define SCREEN_YCEN 480

#define FLOORTYPE_NORMAL 0
#define FLOORTYPE_VOID 1
#define FLOORTYPE_WATER 2
#define FLOORTYPE_INSTADEATH 3
#define FLOORTYPE_DAMAGE 4
#define FLOORTYPE_DAMAGEWATER 5

static char floortext_normal_off[] = "{ NORMAL";
static char floortext_void_off[] = "{ VOIDS";
static char floortext_water_off[] = "{ WATER";
static char floortext_damage_off[] = "{ DAMAGE";
static char floortext_instadeath_off[] = "{ INSTADEATH";

static char floortext_normal_on[] = "} NORMAL";
static char floortext_void_on[] = "} VOIDS";
static char floortext_water_on[] = "} WATER";
static char floortext_damage_on[] = "} DAMAGE";
static char floortext_instadeath_on[] = "} INSTADEATH";

static char floortext_clear[] = "CLEAR ALL FLOORS";

static const char collisiontext_floor[] = "FLOORS";
static const char collisiontext_wall[] = "WALLS";

#define FLOOR_TYPE_COUNT 5
static const short floor_order[] = {
	FLOORTRI_NONSOLID,
	FLOORTRI_VOID,
	FLOORTRI_WATER,
	FLOORTRI_DAMAGE,
	FLOORTRI_INSTADEATH,
};
static const short floor_check_order[] = {
	0xFFFF - FLOORTRI_NONSOLID - FLOORTRI_VOID - FLOORTRI_WATER - FLOORTRI_DAMAGE - FLOORTRI_INSTADEATH,
	FLOORTRI_VOID,
	FLOORTRI_WATER,
	FLOORTRI_DAMAGE,
	FLOORTRI_INSTADEATH,
};

static char* floor_off_order[] = {
	floortext_normal_off,
	floortext_void_off,
	floortext_water_off,
	floortext_damage_off,
	floortext_instadeath_off,
};

static char* floor_on_order[] = {
	floortext_normal_on,
	floortext_void_on,
	floortext_water_on,
	floortext_damage_on,
	floortext_instadeath_on,
};

// void outputFloors(int* mesh, int tri_count) {
// 	if (mesh) {
// 		for (int i = 0; i < tri_count; i++) {
// 			floor_tri* tri_base = getObjectArrayAddr(mesh,FLOORTRIANGLE_SIZE,i);
// 			if (tri_base) {
// 				int drawing_tri = 1;
// 				int x[3] = {};
// 				int y[3] = {};
// 				int j = 0;
// 				int dxyz = 0;
// 				while (j < 3) {
// 					if (drawing_tri) {
// 						float x_store = 0;
// 						float y_store = 0;
// 						float dx = tri_base->x[j]/6 - Player->xPos;
// 						float dy = tri_base->y[j]/6 - Player->yPos;
// 						float dz = tri_base->z[j]/6 - Player->zPos;
// 						int dxz = (dx * dx) + (dz * dz);
// 						dxyz = dxz + (dy * dy);
// 						if (dy < 0) {
// 							dy = -dy;
// 						}
// 						if ((dxz < 100000) && (dy < 100)) {
// 							float tri_y = tri_base->y[j]/6;
// 							if (tri_base->state_bitfield & FLOORTRI_VOID) {
// 								tri_y = Player->floor;
// 							}
// 							int check_success = 0;
// 							for (int a = 0; a < FLOOR_TYPE_COUNT; a++) {
// 								if (floor_shown_bitfield & floor_order[a]) {
// 									if (a == 0) {
// 										if ((tri_base->state_bitfield & (FLOORTRI_VOID | FLOORTRI_WATER | FLOORTRI_DAMAGE | FLOORTRI_INSTADEATH)) == 0) {
// 											check_success = 1;
// 										}
// 									} else {
// 										if (tri_base->state_bitfield & floor_check_order[a]) {
// 											check_success = 1;
// 										}
// 									}
// 								}
// 							}
// 							if (check_success) {
// 								getScreenPosition(tri_base->x[j]/6,tri_y,tri_base->z[j]/6,(float*)&x_store, (float*)&y_store,0,1.0f,0);
// 								if ((x_store != 0x4000) && (y_store != 0x4000)) {
// 									x[j] = (4 * x_store);
// 									y[j] = (4 * y_store);
// 								} else {
// 									drawing_tri = 0;
// 									break;
// 								}
// 							} else {
// 								drawing_tri = 0;
// 								break;
// 							}
// 						} else {
// 							drawing_tri = 0;
// 							break;
// 						}
// 					}
// 					j++;
// 				}
// 				if (drawing_tri) {				
// 					int bitfield = tri_base->state_bitfield;
// 					if ((bitfield & FLOORTRI_NONSOLID) == 0) {
// 						if ((bitfield & FLOORTRI_VOID) && (floor_shown_bitfield & FLOORTRI_VOID)) {
// 							int k = 0;
// 							int furthest = 0;
// 							int furthest_index = -1;
// 							int found_unused = -1;
// 							while (k < FLOORTRICAP_VOID) {
// 								if (triarray_void[k].used != FrameLag) {
// 									found_unused = k;
// 									break;
// 								} else {
// 									if (furthest < triarray_void[k].distance) {
// 										furthest = triarray_void[k].distance;
// 										furthest_index = k;
// 									}
// 								}
// 								k++;
// 							}
// 							int idx = furthest_index;
// 							if (found_unused > -1) {
// 								idx = found_unused;
// 							}
// 							if ((furthest > dxyz) || (found_unused > -1)) {
// 								triarray_void[idx].used = FrameLag;
// 								triarray_void[idx].distance = dxyz;
// 								triarray_void[idx].floor_type = FLOORTYPE_VOID;
// 								for (int a = 0; a < 3; a++) {
// 									triarray_void[idx].x_screen[a] = x[a];
// 									triarray_void[idx].y_screen[a] = y[a];
// 								}
// 							}
// 						} else if ((bitfield & FLOORTRI_INSTADEATH) && (floor_shown_bitfield & FLOORTRI_INSTADEATH)) {
// 							int k = 0;
// 							int furthest = 0;
// 							int furthest_index = -1;
// 							int found_unused = -1;
// 							while (k < FLOORTRICAP_INSTADEATH) {
// 								if (triarray_instadeath[k].used != FrameLag) {
// 									found_unused = k;
// 									break;
// 								} else {
// 									if (furthest < triarray_instadeath[k].distance) {
// 										furthest = triarray_instadeath[k].distance;
// 										furthest_index = k;
// 									}
// 								}
// 								k++;
// 							}
// 							int idx = furthest_index;
// 							if (found_unused > -1) {
// 								idx = found_unused;
// 							}
// 							if ((furthest > dxyz) || (found_unused > -1)) {
// 								triarray_instadeath[idx].used = FrameLag;
// 								triarray_instadeath[idx].distance = dxyz;
// 								triarray_instadeath[idx].floor_type = FLOORTYPE_INSTADEATH;
// 								for (int a = 0; a < 3; a++) {
// 									triarray_instadeath[idx].x_screen[a] = x[a];
// 									triarray_instadeath[idx].y_screen[a] = y[a];
// 								}
// 							}
// 						} else if ((bitfield & FLOORTRI_DAMAGE) && (floor_shown_bitfield & FLOORTRI_DAMAGE)) {
// 							int k = 0;
// 							int furthest = 0;
// 							int furthest_index = -1;
// 							int found_unused = -1;
// 							while (k < FLOORTRICAP_DAMAGE) {
// 								if (triarray_damage[k].used != FrameLag) {
// 									found_unused = k;
// 									break;
// 								} else {
// 									if (furthest < triarray_damage[k].distance) {
// 										furthest = triarray_damage[k].distance;
// 										furthest_index = k;
// 									}
// 								}
// 								k++;
// 							}
// 							int idx = furthest_index;
// 							if (found_unused > -1) {
// 								idx = found_unused;
// 							}
// 							if ((furthest > dxyz) || (found_unused > -1)) {
// 								triarray_damage[idx].used = FrameLag;
// 								triarray_damage[idx].distance = dxyz;
// 								triarray_damage[idx].floor_type = FLOORTYPE_DAMAGE;
// 								for (int a = 0; a < 3; a++) {
// 									triarray_damage[idx].x_screen[a] = x[a];
// 									triarray_damage[idx].y_screen[a] = y[a];
// 								}
// 							}
// 						} else if ((bitfield & FLOORTRI_WATER) && (floor_shown_bitfield & FLOORTRI_WATER)) {
// 							int k = 0;
// 							int furthest = 0;
// 							int furthest_index = -1;
// 							int found_unused = -1;
// 							while (k < FLOORTRICAP_WATER) {
// 								if (triarray_water[k].used != FrameLag) {
// 									found_unused = k;
// 									break;
// 								} else {
// 									if (furthest < triarray_water[k].distance) {
// 										furthest = triarray_water[k].distance;
// 										furthest_index = k;
// 									}
// 								}
// 								k++;
// 							}
// 							int idx = furthest_index;
// 							if (found_unused > -1) {
// 								idx = found_unused;
// 							}
// 							if ((furthest > dxyz) || (found_unused > -1)) {
// 								triarray_water[idx].used = FrameLag;
// 								triarray_water[idx].distance = dxyz;
// 								triarray_water[idx].floor_type = FLOORTYPE_WATER;
// 								for (int a = 0; a < 3; a++) {
// 									triarray_water[idx].x_screen[a] = x[a];
// 									triarray_water[idx].y_screen[a] = y[a];
// 								}
// 							}
// 						} else {
// 							if ((floor_shown_bitfield & (FLOORTRI_VOID | FLOORTRI_WATER | FLOORTRI_DAMAGE | FLOORTRI_INSTADEATH)) == 0) {
// 								int k = 0;
// 								int furthest = 0;
// 								int furthest_index = -1;
// 								int found_unused = -1;
// 								while (k < FLOORTRICAP_NORMAL) {
// 									if (triarray_normal[k].used != FrameLag) {
// 										found_unused = k;
// 										break;
// 									} else {
// 										if (furthest < triarray_normal[k].distance) {
// 											furthest = triarray_normal[k].distance;
// 											furthest_index = k;
// 										}
// 									}
// 									k++;
// 								}
// 								int idx = furthest_index;
// 								if (found_unused > -1) {
// 									idx = found_unused;
// 								}
// 								if ((furthest > dxyz) || (found_unused > -1)) {
// 									triarray_normal[idx].used = FrameLag;
// 									triarray_normal[idx].distance = dxyz;
// 									triarray_normal[idx].floor_type = FLOORTYPE_NORMAL;
// 									for (int a = 0; a < 3; a++) {
// 										triarray_normal[idx].x_screen[a] = x[a];
// 										triarray_normal[idx].y_screen[a] = y[a];
// 									}
// 								}
// 							}
// 						}
// 					}
// 				}
// 			}
// 		}
// 	}
// }


// static char disp_count[5] = "";
// int* displayFloors(int* dl) {
// 	if ((floor_shown_bitfield) && (!ActiveMenu.isOpen)) {
// 		floor_tri_data* floor_block;
// 		dk_strFormat(disp_count,"%d",displayListCount);
// 		dl = drawTextContainer(dl, 6, 20, 340, (char*)disp_count , 0xFF, 0xFF, 0xFF, 0xFF, 1);
// 		if (mapFloorPointer) {
// 			for (int i = 0; i < mapFloorBlockCount; i++) {
// 				floor_block = getObjectArrayAddr(mapFloorPointer,FLOORTRIANGLE_BLOCKSIZE,i);
// 				if (isRDRAM(floor_block->rdram_start)) {
// 					int num_tris = floor_block->size / FLOORTRIANGLE_SIZE;
// 					if (num_tris > 0) {
// 						outputFloors(floor_block->rdram_start, num_tris);
// 					}
// 				}
// 			}
// 			if (floor_shown_bitfield & FLOORTRI_VOID) {
// 				for (int i = 0; i < FLOORTRICAP_VOID; i++) {
// 					if (triarray_void[i].used == FrameLag) {
// 						dl = drawTri(dl,
// 							triarray_void[i].x_screen[0],
// 							triarray_void[i].y_screen[0],
// 							triarray_void[i].x_screen[1],
// 							triarray_void[i].y_screen[1],
// 							triarray_void[i].x_screen[2],
// 							triarray_void[i].y_screen[2],
// 							0xFF,0x00,0x00,0x80);
// 					}
// 				}
// 			}
// 			if (floor_shown_bitfield & FLOORTRI_INSTADEATH) {
// 				for (int i = 0; i < FLOORTRICAP_INSTADEATH; i++) {
// 					if (triarray_instadeath[i].used == FrameLag) {
// 						dl = drawTri(dl,
// 							triarray_instadeath[i].x_screen[0],
// 							triarray_instadeath[i].y_screen[0],
// 							triarray_instadeath[i].x_screen[1],
// 							triarray_instadeath[i].y_screen[1],
// 							triarray_instadeath[i].x_screen[2],
// 							triarray_instadeath[i].y_screen[2],
// 							0xFF,0x00,0xFF,0x80);
// 					}
// 				}
// 			}
// 			if (floor_shown_bitfield & FLOORTRI_DAMAGE) {
// 				for (int i = 0; i < FLOORTRICAP_DAMAGE; i++) {
// 					if (triarray_damage[i].used == FrameLag) {
// 						dl = drawTri(dl,
// 							triarray_damage[i].x_screen[0],
// 							triarray_damage[i].y_screen[0],
// 							triarray_damage[i].x_screen[1],
// 							triarray_damage[i].y_screen[1],
// 							triarray_damage[i].x_screen[2],
// 							triarray_damage[i].y_screen[2],
// 							0x00,0xFF,0x00,0x80);
// 					}
// 				}
// 			}
// 			if (floor_shown_bitfield & FLOORTRI_WATER) {
// 				for (int i = 0; i < FLOORTRICAP_WATER; i++) {
// 					if (triarray_water[i].used == FrameLag) {
// 						dl = drawTri(dl,
// 							triarray_water[i].x_screen[0],
// 							triarray_water[i].y_screen[0],
// 							triarray_water[i].x_screen[1],
// 							triarray_water[i].y_screen[1],
// 							triarray_water[i].x_screen[2],
// 							triarray_water[i].y_screen[2],
// 							0x00,0x00,0xFF,0x80);
// 					}
// 				}
// 			}
// 			if (floor_shown_bitfield & FLOORTRI_NONSOLID) {
// 				for (int i = 0; i < FLOORTRICAP_NORMAL; i++) {
// 					if (triarray_normal[i].used == FrameLag) {
// 						dl = drawTri(dl,
// 							triarray_normal[i].x_screen[0],
// 							triarray_normal[i].y_screen[0],
// 							triarray_normal[i].x_screen[1],
// 							triarray_normal[i].y_screen[1],
// 							triarray_normal[i].x_screen[2],
// 							triarray_normal[i].y_screen[2],
// 							0xFF,0xFF,0xFF,0x80);
// 					}
// 				}
// 			}
// 		}
// 	}
// 	return dl;
// }

// typedef struct vert {
// 	/* 0x000 */ short x;
// 	/* 0x002 */ short y;
// 	/* 0x004 */ short z;
// 	/* 0x006 */ short unk_06;
// 	/* 0x008 */ short mapping[2];
// 	/* 0x00C */ short shading[2]; 
// } vert;

// int* outputFloors(int* mesh, int tri_count) {
// 	if (mesh) {
// 		int* custom_verts = dk_malloc(tri_count * 0x30);
// 		for (int i = 0; i < tri_count; i++) {
// 			floor_tri* tri_base = getObjectArrayAddr(mesh,FLOORTRIANGLE_SIZE,i);
// 			if (tri_base) {
// 				for (int j = 0; j < 3; j++) {
// 					float x = tri_base->x[j];
// 					x *= 0.222; // 1/6 * 4/3
// 					float y = tri_base->y[j];
// 					y *= 0.222;
// 					float z = tri_base->z[j];
// 					z *= 0.222;
// 					int bitfield = tri_base->state_bitfield;
// 					vert* vert_focus = getObjectArrayAddr(custom_verts,0x10,(3 * i) + j);
// 					vert_focus->x = x;
// 					vert_focus->y = y;
// 					vert_focus->z = z;
// 					vert_focus->unk_06 = 0;
// 					for (int k = 0; k < 2; k++) {
// 						vert_focus->mapping[k] = 0;
// 						vert_focus->shading[k] = 0;
// 					}
// 					// if (bitfield & FLOORTRI_VOID) {
						
// 					// }
// 				}
// 			}
// 		}
// 		return custom_verts;
// 	}
// 	return 0;
// }


// int* displayFloors(int* dl) {
// 	floor_tri_data* floor_block;
// 	dk_strFormat(disp_count,"%d",displayListCount);
// 	dl = drawTextContainer(dl, 6, 20, 340, (char*)disp_count , 0xFF, 0xFF, 0xFF, 0xFF, 1);
// 	if (mapFloorPointer) {
// 		for (int i = 0; i < mapFloorBlockCount; i++) {
// 			floor_block = getObjectArrayAddr(mapFloorPointer,FLOORTRIANGLE_BLOCKSIZE,i);
// 			if (isRDRAM(floor_block->rdram_start)) {
// 				int num_tris = floor_block->size / FLOORTRIANGLE_SIZE;
// 				if (num_tris > 0) {
// 					if (customCollisionVerts == 0) {
// 						customCollisionVerts = outputFloors(floor_block->rdram_start, num_tris);
// 					}
// 				}
// 			}
// 		}
// 	}
// 	if (customCollisionVerts) {
// 		*(unsigned int*)(dl++) = 0xDB060018;
// 		*(unsigned int*)(dl++) = __osVirtualToPhysical(customCollisionVerts);
// 	}
// 	return dl;
// }

static char* floormenu_array[FLOOR_TYPE_COUNT + 1] = {};

void openFloorMenu(void) {
	for (int i = 0; i < FLOOR_TYPE_COUNT; i++) {
		if (floor_shown_bitfield & floor_order[i]) {
			floormenu_array[i] = floor_on_order[i];
		} else {
			floormenu_array[i] = floor_off_order[i];
		}
	}
	floormenu_array[FLOOR_TYPE_COUNT] = floortext_clear;
	changeMenu(101);
}

void openWallMenu(void) {

}

static const char* collisionmenu_array[] = {
	collisiontext_floor,
	collisiontext_wall,
};
static const int collisionmenu_functions[] = {
	(int)&openFloorMenu,
	(int)&openWallMenu,
};

void floortoggle(void) {
	int bit = floor_order[(int)ActiveMenu.positionIndex];
	if (floor_shown_bitfield & bit) {
		floor_shown_bitfield &= (0xFFFF - bit);
	} else {
		floor_shown_bitfield |= bit;
	}
	openFloorMenu();
}

void floorclear(void) {
	floor_shown_bitfield = 0;
	openFloorMenu();
}

static int floormenu_functions[] = {
	(int)&floortoggle,
	(int)&floortoggle,
	(int)&floortoggle,
	(int)&floortoggle,
	(int)&floortoggle,
	(int)&floorclear,
};

void openCollisionMenu(void) {
	changeMenu(100);
}

const Screen floormenu_struct = {
	.TextArray = (int*)floormenu_array,
	.FunctionArray = floormenu_functions,
	.ArrayItems = FLOOR_TYPE_COUNT + 1,
	.ParentScreen = 100,
	.ParentPosition = 0
};

const Screen collisionmenu_struct = {
	.TextArray = (int*)collisionmenu_array,
	.FunctionArray = collisionmenu_functions,
	.ArrayItems = 2,
	.ParentScreen = 76,
	.ParentPosition = 6
};


