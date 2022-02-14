#include "../../include/common.h"

#define BORDER_TL 100
#define BORDER_BR 500
#define BORDER_PD 20
#define BORDER_EXTERN 0
#define BORDER_INTERN 10
#define POINTER_MAX 50
#define POINTER_MIN 25
#define CENTER 300
#define VIEWPORT_RANGE 500
#define MINIMAP_RANGE 180

// Cornflower Blue
#define VOID_RED 12
#define VOID_GREEN 18
#define VOID_BLUE 29
#define VOID_RED_BYTE 0x64
#define VOID_GREEN_BYTE 0x95
#define VOID_BLUE_BYTE 0xED

typedef struct stored_floor {
	/* 0x000 */ short x[3];
	/* 0x006 */ short z[3];
	/* 0x00C */ int used;
} stored_floor;

static int void_floor_count = 0;

int* displayVoidBorder(int* dl) {
	dl = drawScreenRect(dl, 
						BORDER_TL, 
						BORDER_TL, 
						BORDER_BR, 
						BORDER_BR, 
						BORDER_EXTERN, 
						BORDER_EXTERN, 
						BORDER_EXTERN,
						1);
	dl = drawScreenRect(dl,
						BORDER_TL + BORDER_PD,
						BORDER_TL + BORDER_PD, 
						BORDER_BR - BORDER_PD, 
						BORDER_BR - BORDER_PD, 
						BORDER_INTERN, 
						BORDER_INTERN, 
						BORDER_INTERN, 
						1);
	return dl;
}

static float x[3] = {};
static float y[3] = {};

int* displayPlayerMarker(int* dl) {
	float angle = 0;
	if (Player) {
		angle = Player->facing_angle;
		angle *= -0.00153397949f; // 2 * pi / 4096
	}
	int dist = 0;
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			dist = POINTER_MAX;
		} else {
			dist = POINTER_MIN;
		}
		x[i] = CENTER + (dist * dk_sin(angle + (i * 2.09439510f)));
		y[i] = CENTER - (dist * dk_cos(angle + (i * 2.09439510f)));
	}
	dl = drawTri(dl, x[0], y[0], x[1], y[1], x[2], y[2], 0xFF, 0xFF, 0xFF, 0x80);
	return dl;
}

int* drawBoxVoid(int* dl) {
	if (Player) {
		int minX_dx = Player->xPos - MapVoid_MinX;
		int maxX_dx = Player->xPos - MapVoid_MaxX;
		int minZ_dz = Player->zPos - MapVoid_MinZ;
		int maxZ_dz = Player->zPos - MapVoid_MaxZ;
		float delta = 0;
		if ((maxZ_dz < VIEWPORT_RANGE) && (maxZ_dz > (0 - VIEWPORT_RANGE))) {
			delta = maxZ_dz;
			delta /= VIEWPORT_RANGE;
			delta *= MINIMAP_RANGE;
			dl = drawScreenRect(dl,
								BORDER_TL + BORDER_PD,
								BORDER_TL + BORDER_PD,
								BORDER_BR - BORDER_PD,
								CENTER + delta,
								VOID_RED,
								VOID_GREEN,
								VOID_BLUE,
								1);
		}
		if ((minZ_dz < VIEWPORT_RANGE) && (minZ_dz > (0 - VIEWPORT_RANGE))) {
			delta = minZ_dz;
			delta /= VIEWPORT_RANGE;
			delta *= MINIMAP_RANGE;
			dl = drawScreenRect(dl,
								BORDER_TL + BORDER_PD,
								CENTER + delta,
								BORDER_BR - BORDER_PD,
								BORDER_BR - BORDER_PD,
								VOID_RED,
								VOID_GREEN,
								VOID_BLUE,
								1);
		}
		if ((maxX_dx < VIEWPORT_RANGE) && (maxX_dx > (0 - VIEWPORT_RANGE))) {
			delta = maxX_dx;
			delta /= VIEWPORT_RANGE;
			delta *= MINIMAP_RANGE;
			dl = drawScreenRect(dl,
								BORDER_TL + BORDER_PD,
								BORDER_TL + BORDER_PD,
								CENTER + delta,
								BORDER_BR - BORDER_PD,
								VOID_RED,
								VOID_GREEN,
								VOID_BLUE,
								1);
		}
		if ((minX_dx < VIEWPORT_RANGE) && (minX_dx > (0 - VIEWPORT_RANGE))) {
			delta = minX_dx;
			delta /= VIEWPORT_RANGE;
			delta *= MINIMAP_RANGE;
			dl = drawScreenRect(dl,
								CENTER + delta,
								BORDER_TL + BORDER_PD,
								BORDER_BR - BORDER_PD,
								BORDER_BR - BORDER_PD,
								VOID_RED,
								VOID_GREEN,
								VOID_BLUE,
								1);
		}
	}
	return dl;
}

#define FLOORTRIANGLE_BLOCKSIZE 0x14
#define FLOORTRIANGLE_SIZE 0x18
#define FLOORTRI_VOID 0x4000

int* drawFloors(int* dl, int x1, int z1, int x2, int z2, int x3, int z3) {
	float diffs[6] = {};
	int pass = 1;
	if (Player) {
		diffs[0] = Player->xPos - x1;
		diffs[1] = Player->zPos - z1;
		diffs[2] = Player->xPos - x2;
		diffs[3] = Player->zPos - z2;
		diffs[4] = Player->xPos - x3;
		diffs[5] = Player->zPos - z3;
		for (int i = 0; i < 6; i++) {
			if ((diffs[i] >= (-VIEWPORT_RANGE-2)) && (diffs[i] <= (VIEWPORT_RANGE+2))) {
				diffs[i] /= VIEWPORT_RANGE;
				diffs[i] *= MINIMAP_RANGE;
				diffs[i] += CENTER;
			} else {
				pass = 0;
			}
		}
		if (pass) {
			dl = drawTri(dl,
						diffs[0],
						diffs[1],
						diffs[2],
						diffs[3],
						diffs[4],
						diffs[5],
						VOID_RED_BYTE,
						VOID_GREEN_BYTE,
						VOID_BLUE_BYTE,
						1);
		}
	}
	return dl;
}

int det(int a0, int a1, int b0, int b1) {
	return a0 * b1 - a1 * b0;
}

int getLineIntersection(int ax, int az, int bx, int bz, int cx, int cz, int dx, int dz, int ret_z) {
	int div = det(ax - bx, cx - dx, az - bz, cz - dz);
	if (div == 0) {
		return 0;
	}
	int d0 = det(ax,az,bx,bz);
	int d1 = det(cx,cz,dx,dz);
	if (ret_z == 0) {
		return det(d0, d1, ax - bx, cx - dx) / div;
	} else {
		return det(d0, d1, az - bz, cz - dz) / div;
	}
}

static int px[5] = {};
static int pz[5] = {};

int* calculateTris(int* dl, int x1, int z1, int x2, int z2, int x3, int z3, int range_count, int range_bitfield, int bx1, int bz1, int bx2, int bz2, int bx3, int bz3) {
	if (Player) {
		if (range_count == 3) {
			dl = drawFloors(dl,x1,z1,x2,z2,x3,z3);
		} else if (range_count == 2) {
			int far_px = 0;
			int far_pz = 0;
			int far_bx = 0;
			int far_bz = 0;
			if ((range_bitfield & 0x4) == 0) {
				px[0] = x1;
				pz[0] = z1;
				px[1] = x2;
				pz[1] = z2;
				far_px = x3;
				far_pz = z3;
				far_bx = bx3;
				far_bz = bz3;
			} else if ((range_bitfield & 0x2) == 0) {
				px[0] = x1;
				pz[0] = z1;
				px[1] = x3;
				pz[1] = z3;
				far_px = x2;
				far_pz = z2;
				far_bx = bx2;
				far_bz = bz2;
			} else {
				px[0] = x2;
				pz[0] = z2;
				px[1] = x3;
				pz[1] = z3;
				far_px = x1;
				far_pz = z1;
				far_bx = bx1;
				far_bz = bz1;
			}
			int absolute_far_bx = Player->xPos + far_bx;
			int absolute_far_bz = Player->zPos + far_bz;
			int satisfied_d = 0;
			int satisfied_e = 0;
			if (far_bx != 0) {
				satisfied_d = 1;
				satisfied_e = 1;
				px[2] = absolute_far_bx;
				pz[2] = getLineIntersection(far_px,far_pz,px[0],pz[0],absolute_far_bx,Player->zPos - (5 * VIEWPORT_RANGE),absolute_far_bx,Player->zPos + (5 * VIEWPORT_RANGE),1);
				px[3] = absolute_far_bx;
				pz[3] = getLineIntersection(far_px,far_pz,px[1],pz[1],absolute_far_bx,Player->zPos - (5 * VIEWPORT_RANGE),absolute_far_bx,Player->zPos + (5 * VIEWPORT_RANGE),1);
				if ((pz[2] > Player->zPos + VIEWPORT_RANGE) || (pz[2] < (Player->zPos - VIEWPORT_RANGE))) {
					satisfied_d = 0;
				}
				if ((pz[3] > Player->zPos + VIEWPORT_RANGE) || (pz[3] < (Player->zPos - VIEWPORT_RANGE))) {
					satisfied_e = 0;
				}
			}
			if (!satisfied_d) {
				px[2] = getLineIntersection(far_px,far_pz,px[0],pz[0],Player->xPos - (5 * VIEWPORT_RANGE),absolute_far_bz,Player->xPos + (5 * VIEWPORT_RANGE),absolute_far_bz,0);
				pz[2] = absolute_far_bz;
			}
			if (!satisfied_e) {
				px[3] = getLineIntersection(far_px,far_pz,px[1],pz[1],Player->xPos - (5 * VIEWPORT_RANGE),absolute_far_bz,Player->xPos + (5 * VIEWPORT_RANGE),absolute_far_bz,0);
				px[3] = absolute_far_bz;
			}
			dl = drawFloors(dl,px[0],pz[0],px[1],pz[1],px[2],pz[2]);
			dl = drawFloors(dl,px[1],pz[1],px[2],pz[2],px[3],pz[3]);
			if (satisfied_d != satisfied_e) {
				dl = drawFloors(dl,px[2],pz[2],px[3],pz[3],absolute_far_bx,absolute_far_bz);
			}
		}
	}
	return dl;
}

#define COPY_BLOCK_SIZE 0x10
int correctSize(int size) {
	if ((size % COPY_BLOCK_SIZE) == 0) {
		return size;
	} else {
		int offset = size % COPY_BLOCK_SIZE;
		return size + (COPY_BLOCK_SIZE - offset);
	}
}

int upload_void(void* source_mesh, int num_tris, int void_index) {
	for (int j = 0; j < num_tris; j++) {
		floor_tri* tri_base = getObjectArrayAddr(source_mesh,FLOORTRIANGLE_SIZE,j);
		if (tri_base) {
			if ((tri_base->state_bitfield & FLOORTRI_VOID) && (void_index < 511)) {
				stored_floor* floor_base = getObjectArrayAddr(voidPointer, 0x10, void_index);
				void_index += 1;
				for (int k = 0; k < 3; k++) {
					floor_base->x[k] = tri_base->x[k];
					floor_base->z[k] = tri_base->z[k];
				}
				floor_base->used = 1;
			}
		}
	}
	return void_index;
}

void preload_map_voids(void) {
	if (voidPointer == 0) {
		floor_tri_data* floor_block = 0;
		int* block_floors = 0;
		int* file_size;
		void_floor_count = 0;
		if (mapFloorPointer) {
			voidPointer = dk_malloc(0x2000); // Accounts for 512 Void Floors
			int void_index = 0;
			int max_size = 0;
			for (int i = 0; i < mapFloorBlockCount; i++) {
				floor_block = getObjectArrayAddr(mapFloorPointer,FLOORTRIANGLE_BLOCKSIZE,i);
				if (floor_block->size > max_size) {
					max_size = correctSize(floor_block->size);
				}
			}
			if (floorsPreloadedVanilla == 0) {
				block_floors = dk_malloc(max_size);
			}
			for (int i = 0; i < mapFloorBlockCount; i++) {
				if (floorsPreloadedVanilla == 0) {
					wipeMemory(block_floors,max_size);
					floor_block = getObjectArrayAddr(mapFloorPointer,FLOORTRIANGLE_BLOCKSIZE,i);
					if (floor_block->size > 0) {
						int num_tris = floor_block->size / FLOORTRIANGLE_SIZE;
						*(int*)(&file_size) = floor_block->size;
						copyFromROM(floor_block->rom_start, block_floors, &file_size, 0, 0, 0, 0);
						void_index = upload_void(block_floors,num_tris,void_index);
					}
				} else {
					floor_block = getObjectArrayAddr(mapFloorPointer,FLOORTRIANGLE_BLOCKSIZE,i);
					if (floor_block->size > 0) {
						int num_tris = floor_block->size / FLOORTRIANGLE_SIZE;
						void_index = upload_void(floor_block->rdram_start,num_tris,void_index);
					}
				}
			}
			if (floorsPreloadedVanilla == 0) {
				complexFree(block_floors);
			}
			stored_floor* floor_base = getObjectArrayAddr(voidPointer, 0x10, void_index);
			floor_base->used = 0;
			void_floor_count = void_index;
		}
	}
}

int* displayVoidFloors(int* dl) {
	if (voidPointer) {
		for (int i = 0; i < void_floor_count; i++) {
			stored_floor* floor_base = getObjectArrayAddr(voidPointer, 0x10, i);
			if (floor_base->used) {
				int range_count = 0;
				int range_bitfield = 0;
				float x[3] = {};
				float z[3] = {};
				float bx[3] = {0.0f,0.0f,0.0f};
				float bz[3] = {0.0f,0.0f,0.0f};
				for (int j = 0; j < 3; j++) {
					float tri_x = floor_base->x[j];
					float tri_z = floor_base->z[j];
					x[j] = tri_x / 6;
					z[j] = tri_z / 6;
					if (Player) {
						int dx = Player->xPos - x[j];
						int dz = Player->zPos - z[j];
						if ((dx < VIEWPORT_RANGE) && (dx > (0 - VIEWPORT_RANGE))) {
							if ((dz < VIEWPORT_RANGE) && (dz > (0 - VIEWPORT_RANGE))) {
								range_count += 1;
								range_bitfield |= (1 << j);
							}
						}
						if (dx > VIEWPORT_RANGE) {
							bx[j] = -VIEWPORT_RANGE;
						} else if (dx < (0 - VIEWPORT_RANGE)) {
							bx[j] = VIEWPORT_RANGE;
						}
						if (dz > VIEWPORT_RANGE) {
							bz[j] = -VIEWPORT_RANGE;
						} else if (dz < (0 - VIEWPORT_RANGE)) {
							bz[j] = VIEWPORT_RANGE;
						}
					}
				}
				if (range_count > 0) {
					dl = calculateTris(dl, x[0], z[0], x[1], z[1], x[2], z[2], range_count, range_bitfield, bx[0],bz[0],bx[1],bz[1],bx[2],bz[2]);
				}
			}
		}
	}
	return dl;
}

int* displayVoid(int* dl) {
	if (voidMapOn) {
		dl = displayVoidBorder(dl);
		dl = drawBoxVoid(dl);
		dl = drawText(dl, 6, 40, 100, "VOID MAP", 0xFF, 0xFF, 0xFF, 0xFF);
		dl = displayVoidFloors(dl);
		dl = displayPlayerMarker(dl);
	}
	return dl;
}