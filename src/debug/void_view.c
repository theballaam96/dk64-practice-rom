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
#define PLAYER_SQ_SIZE 5

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
		x[i] = CENTER + (dist * dk_sin(angle + (i * 2.09439510f))); // 2.09439 = 2 * PI / 3
		y[i] = CENTER - (dist * dk_cos(angle + (i * 2.09439510f)));
	}
	int red = 0xFF;
	int green = 0xFF;
	int blue = 0xFF;
	if (assignedConsole == WIIU) {
		red = 0;
		green = 0;
		blue = 0;
	}
	dl = drawTri(dl, x[0], y[0], x[1], y[1], x[2], y[2], red, green, blue, 0x80);
	dl = drawScreenRect(dl,
						CENTER - PLAYER_SQ_SIZE,
						CENTER - PLAYER_SQ_SIZE,
						CENTER + PLAYER_SQ_SIZE,
						CENTER + PLAYER_SQ_SIZE,
						0x1F,
						0,
						0,
						1);
	return dl;
}

int* drawBoxVoid(int* dl) {
	if (Player) {
		int minX_dx = Player->xPos - MapVoid_MinX;
		int maxX_dx = Player->xPos - MapVoid_MaxX;
		int minZ_dz = Player->zPos - MapVoid_MinZ;
		int maxZ_dz = Player->zPos - MapVoid_MaxZ;
		float delta = 0;
		int drawn = 0;
		if ((maxZ_dz > VIEWPORT_RANGE) || (minZ_dz < (0 - VIEWPORT_RANGE)) || (maxX_dx > VIEWPORT_RANGE) || (minX_dx < (0 - VIEWPORT_RANGE))) {
			dl = drawScreenRect(dl,
				BORDER_TL + BORDER_PD,
				BORDER_TL + BORDER_PD,
				BORDER_BR - BORDER_PD,
				BORDER_BR - BORDER_PD,
				VOID_RED,
				VOID_GREEN,
				VOID_BLUE,
				1);
			drawn = 1;
		}
		if (!drawn) {
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
		int red = VOID_RED_BYTE;
		int green = VOID_GREEN_BYTE;
		int blue = VOID_BLUE_BYTE;
		if (assignedConsole == WIIU) {
			red = 0;
			green = 0;
			blue = 0;
		}
		if (pass) {
			dl = drawTri(dl,
						diffs[0],
						diffs[1],
						diffs[2],
						diffs[3],
						diffs[4],
						diffs[5],
						red,
						green,
						blue,
						1);
		}
	}
	return dl;
}

int point_in_line(int a, int b, int c) {
	if (a == b) {
		if (c == a) {
			return 1;
		} else if (((a - 2) < c) && (c < (a + 2))) {
			return 1;
		}
	} else if (a > b) {
		if ((a >= c) && (c >= b)) {
			return 1;
		}
	} else if (b > a) {
		if ((b >= c) && (c >= a)) {
			return 1;
		}
	}
	return 0;
}

float det(float a0, float a1, float b0, float b1) {
	return (a0 * b1) - (a1 * b0);
}

#define LINE_INTERSECTION_ERROR 0x7FFFFFFF
static int detected_intersects[2] = {};

void getLineIntersection(int ax, int az, int bx, int bz, int cx, int cz, int dx, int dz) {
	int div = det(ax - bx, cx - dx, az - bz, cz - dz);
	if (div == 0) {
		detected_intersects[0] = LINE_INTERSECTION_ERROR;
		detected_intersects[1] = LINE_INTERSECTION_ERROR;
		return;
	}
	int d0 = det(ax,az,bx,bz);
	int d1 = det(cx,cz,dx,dz);
	float x = det(d0, d1, ax - bx, cx - dx);
	float z = det(d0, d1, az - bz, cz - dz);
	x /= div;
	z /= div;
	int satisfy_counter = 0;
	satisfy_counter += point_in_line(ax, bx, x);
	satisfy_counter += point_in_line(cx, dx, x);
	satisfy_counter += point_in_line(az, bz, z);
	satisfy_counter += point_in_line(cz, dz, z);
	if (satisfy_counter < 4) {
		detected_intersects[0] = LINE_INTERSECTION_ERROR;
		detected_intersects[1] = LINE_INTERSECTION_ERROR;
	} else {
		detected_intersects[0] = x;
		detected_intersects[1] = z;
	}
}

#define MAX_POLY_VERTICES 12
static short px[MAX_POLY_VERTICES] = {};
static short pz[MAX_POLY_VERTICES] = {};
static short vertex_index = 0;
static short boundary_x[4] = {};
static short boundary_z[4] = {};
static int vertex_order[MAX_POLY_VERTICES] = {};
static int boundary_x_max = 0;
static int boundary_x_min = 0;
static int boundary_z_max = 0;
static int boundary_z_min = 0;

void pushToVertexArray(int x, int z) {
	px[(int)vertex_index] = x;
	pz[(int)vertex_index] = z;
	vertex_index += 1;
}

int sign(int x1, int y1, int x2, int y2, int x3, int y3) {
	return (x1 - x3) * (y2 - y3) - (x2 - x3) * (y1 - y3);
}

int isPointInsideTri(int ax, int az, int bx, int bz, int cx, int cz, int px, int pz) {
	int d1 = sign(px,pz,ax,az,bx,bz);
	int d2 = sign(px,pz,bx,bz,cx,cz);
	int d3 = sign(px,pz,cx,cz,ax,az);
	int has_neg = 0;
	int has_pos = 0;
	if ((d1 < 0) || (d2 < 0) || (d3 < 0)) {
		has_neg = 1;
	}
	if ((d1 > 0) || (d2 > 0) || (d3 > 0)) {
		has_pos = 1;
	}
	if (has_pos && has_neg) {
		return 0;
	} else {
		return 1;
	}
}

int isIndexUsed(int index) {
	for (int i = 0; i < vertex_index; i++) {
		if (vertex_order[i] > -1) {
			if (index == vertex_order[i]) {
				return 1;
			}
		}
	}
	return 0;
}

void addClosestVertex(int hook_index, int write_index) {
	int hook_x = px[(int)vertex_order[hook_index]];
	int hook_z = pz[(int)vertex_order[hook_index]];
	unsigned int min_dist = 0xFFFFFFFF;
	int min_index = -1;
	for (int i = 0; i < vertex_index; i++) {
		if (!isIndexUsed(i)) {
			int dx = hook_x - px[i];
			int dz = hook_z - pz[i];
			int dist = (dx * dx) + (dz * dz);
			if (dist < min_dist) {
				min_dist = dist;
				min_index = i;
			}
		}
	}
	if (min_index > -1) {
		vertex_order[write_index] = min_index;
	}
}

int getMin(int a, int b, int c, int d) {
	int min = a;
	if (b < min) {
		min = b;
	}
	if (c < min) {
		min = c;
	}
	if (d < min) {
		min = d;
	}
	return min;
}

int* calculateTris(int* dl, int x1, int z1, int x2, int z2, int x3, int z3, int range_count, int tri_index) {
	if (Player) {
		if (range_count == 3) {
			dl = drawFloors(dl,x1,z1,x2,z2,x3,z3);
		} else {
			vertex_index = 0;
			int tri_x[] = {x1,x2,x3};
			int tri_z[] = {z1,z2,z3};
			for (int i = 0; i < 3; i++) {
				if ((tri_x[i] >= boundary_x_min) && (tri_x[i] <= boundary_x_max)) {
					if ((tri_z[i] >= boundary_z_min) && (tri_z[i] <= boundary_z_max)) {
						pushToVertexArray(tri_x[i],tri_z[i]);
					}
				}
			}
			for (int i = 0; i < 4; i++) {
				if (isPointInsideTri(x1,z1,x2,z2,x3,z3,boundary_x[i],boundary_z[i])) {
					pushToVertexArray(boundary_x[i],boundary_z[i]);
				}
			}
			for (int tri_edge = 0; tri_edge < 3; tri_edge++) {
				for (int viewport_edge = 0; viewport_edge < 4; viewport_edge++) {
					int pass = 1;
					int x_min = getMin(tri_x[tri_edge],tri_x[(tri_edge + 1) % 3],boundary_x[viewport_edge],boundary_x[(viewport_edge + 1) % 4]);
					int z_min = getMin(tri_z[tri_edge],tri_z[(tri_edge + 1) % 3],boundary_z[viewport_edge],boundary_z[(viewport_edge + 1) % 4]);
					int x_offsets[4] = {
						tri_x[tri_edge] - x_min,
						tri_x[(tri_edge + 1) % 3] - x_min,
						boundary_x[viewport_edge] - x_min,
						boundary_x[(viewport_edge + 1) % 4] - x_min
					};
					int z_offsets[4] = {
						tri_z[tri_edge] - z_min,
						tri_z[(tri_edge + 1) % 3] - z_min,
						boundary_z[viewport_edge] - z_min,
						boundary_z[(viewport_edge + 1) % 4] - z_min
					};
					getLineIntersection(x_offsets[0],z_offsets[0],
										x_offsets[1],z_offsets[1],
										x_offsets[2],z_offsets[2],
										x_offsets[3],z_offsets[3]);
					for (int axis = 0; axis < 2; axis++) {
						if (detected_intersects[axis] == LINE_INTERSECTION_ERROR) {
							pass = 0;
						} 
					}
					if (pass) {
						pushToVertexArray(detected_intersects[0] + x_min,detected_intersects[1] + z_min);
					}
				}
			}
			if (vertex_index == 3) {
				dl = drawFloors(dl,px[0],pz[0],px[1],pz[1],px[2],pz[2]);
			} else if (vertex_index > 3) {
				for (int i = 0; i < MAX_POLY_VERTICES; i++) {
					vertex_order[i] = -1;
				}
				vertex_order[0] = 0;
				for (int i = 1; i < vertex_index; i++) {
					addClosestVertex(i - 1,i);
				}
				for (int i = 0; i < (vertex_index - 2); i++) {
					int hook = vertex_order[0];
					int vertex_1 = vertex_order[i+1];
					int vertex_2 = vertex_order[i+2];
					dl = drawFloors(dl,px[hook],pz[hook],px[vertex_1],pz[vertex_1],px[vertex_2],pz[vertex_2]);
				}
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

int upload_void(void* source_mesh, int num_tris, int void_index, int block_index) {
	for (int j = 0; j < num_tris; j++) {
		floor_tri* tri_base = getObjectArrayAddr(source_mesh,FLOORTRIANGLE_SIZE,j);
		if (tri_base) {
			if ((tri_base->state_bitfield & FLOORTRI_VOID) && (void_index < 511)) {
				stored_floor* floor_base = getObjectArrayAddr(voidPointer, 0x10, void_index);
				int upload = 1;
				for (int a = 0; a < void_index; a++) {
					stored_floor* floor_base_test = getObjectArrayAddr(voidPointer, 0x10, a);
					int indiv_check = 0;
					if (floor_base_test->used) {
						indiv_check = 1;
						for (int b = 0; b < 3; b++) {
							int new = 0;
							if (floor_base_test->x[b] == tri_base->x[b]) {
								if (floor_base_test->z[b] == tri_base->z[b]) {
									new = 1;
								}
							}
							indiv_check &= new;
						}
					}
					upload &= (1 ^ indiv_check);
				}
				if (upload) {
					void_index += 1;
					for (int k = 0; k < 3; k++) {
						floor_base->x[k] = tri_base->x[k];
						floor_base->z[k] = tri_base->z[k];
					}
					floor_base->used = 1;
				}
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
						void_index = upload_void(block_floors,num_tris,void_index,i);
					}
				} else {
					floor_block = getObjectArrayAddr(mapFloorPointer,FLOORTRIANGLE_BLOCKSIZE,i);
					if (floor_block->size > 0) {
						int num_tris = floor_block->size / FLOORTRIANGLE_SIZE;
						void_index = upload_void(floor_block->rdram_start,num_tris,void_index,i);
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
		boundary_x_max = Player->xPos + VIEWPORT_RANGE;
		boundary_x_min = Player->xPos - VIEWPORT_RANGE;
		boundary_z_max = Player->zPos + VIEWPORT_RANGE;
		boundary_z_min = Player->zPos - VIEWPORT_RANGE;
		boundary_x[0] = boundary_x_max;
		boundary_x[1] = boundary_x_max;
		boundary_x[2] = boundary_x_min;
		boundary_x[3] = boundary_x_min;
		boundary_z[0] = boundary_z_max;
		boundary_z[1] = boundary_z_min;
		boundary_z[2] = boundary_z_min;
		boundary_z[3] = boundary_z_max;
		for (int i = 0; i < void_floor_count; i++) {
			stored_floor* floor_base = getObjectArrayAddr(voidPointer, 0x10, i);
			if (floor_base->used) {
				int range_count = 0;
				float x[3] = {};
				float z[3] = {};
				int coord_check[] = {0,0,0,0};
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
							}
						}
						int xp = Player->xPos;
						int zp = Player->zPos;
						if (x[j] > xp + VIEWPORT_RANGE) {
							coord_check[0] += 1;
						}
						if (x[j] < xp - VIEWPORT_RANGE) {
							coord_check[1] += 1;
						}
						if (z[j] > zp + VIEWPORT_RANGE) {
							coord_check[2] += 1;
						}
						if (z[j] < zp - VIEWPORT_RANGE) {
							coord_check[3] += 1;
						}
					}
				}
				int pass = 1;
				for (int j = 0; j < 4; j++) {
					if (coord_check[j] >= 3) {
						pass = 0;
					}
				}
				if (pass) {
					dl = calculateTris(dl, x[0], z[0], x[1], z[1], x[2], z[2], range_count, i);
				}
			}
		}
	}
	return dl;
}

int* displayVoid(int* dl) {
	int void_enabled = !(MapPropertiesBitfield & 0x4000);
	if (voidMapOn) {
		if (assignedConsole == WIIU) {
			//dl = drawString(dl,6,20,210,"TEST");
			dl = drawPixelTextContainer(dl, 20, 210, "REMOVECHRISTIAN", 0xFF, 0xFF, 0xFF, 0xFF,0);
		}
		dl = displayVoidBorder(dl);
		if (void_enabled) {
			dl = drawBoxVoid(dl);
			if (assignedConsole != WIIU) {
				dl = drawText(dl, 6, 40, 100, "V", 0xFF, 0xFF, 0xFF, 0xFF);
			}
			dl = displayVoidFloors(dl);
		}
		dl = displayPlayerMarker(dl);
		if (assignedConsole != WIIU) {
			dl = drawText(dl, 6, 40, 100, "VOID MAP", 0xFF, 0xFF, 0xFF, 0xFF);
		} else {
			dl = drawText(dl, 6, 40, 100, "VOID BOUNDARIES", 0xFF, 0xFF, 0xFF, 0xFF);
		}
	}
	return dl;
}