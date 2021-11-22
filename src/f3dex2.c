#include "../include/common.h"

int* drawString(int* dl, int style, float x, float y, char* str) {
	float height = (float)getTextStyleHeight(style);
	float text_y = y - (height * 0x5);
	int* dl_copy = displayText(dl, style, 4 * x, 4 * text_y, str, 0);
	return dl_copy;
}

int* colorText(unsigned char* dl, int red, int green, int blue, int opacity) {
	*(unsigned char*)(dl + 0x4) = red;
	*(unsigned char*)(dl + 0x5) = green;
	*(unsigned char*)(dl + 0x6) = blue;
	*(unsigned char*)(dl + 0x7) = opacity;
	return (int*)dl;
}

int* drawText(int* dl, int style, float x, float y, char* str, int red, int green, int blue, int opacity) {
	dl = initDisplayList(dl);
	if (style == 1) {
		*(unsigned int*)(dl + 0) = 0xFCFFFFFF;
		*(unsigned int*)(dl + 1) = 0xFFFCF279;
		*(unsigned int*)(dl + 2) = 0xDA380003;
		*(unsigned int*)(dl + 3) = 0x807FDAC0;
		dl += 4;
	} else {
		*(unsigned int*)(dl + 0) = 0xDE000000; // G_DL 0
		*(unsigned int*)(dl + 1) = 0x01000118; // G_VTX 0 11
		*(unsigned int*)(dl + 2) = 0xFC119623; // G_SETCOMBINE
		*(unsigned int*)(dl + 3) = 0xFF2FFFFF; // G_SETCIMG format: 1, 1, -1
		dl += 4;
		if (style == 6) {
			*(unsigned int*)(dl + 0) = 0xDA380003;
			*(unsigned int*)(dl + 1) = (int)&style6Mtx[0];
			dl += 2;
		}
		*(unsigned int*)(dl + 0) = 0xFA000000; // G_SETPRIMCOLOR
		dl = colorText((unsigned char*)dl,red,green,blue,opacity);
		dl += 2;
	}
	dl = drawString(dl,style,x,y,str);
	return dl;
}

int* drawTextContainer(int* dl, int style, float x, float y, char* str, int red, int green, int blue, int opacity, int background) {
	if (background) {
		int offset = 1;
		dl = drawText(dl,style,x-offset,y+offset,str,0,0,0,0xFF);
	}
	dl = drawText(dl,style,x,y,str,red,green,blue,0xFF);
	return dl;
}

int* drawImage(int* dl, int text_index, codecs codec_index, int img_width, int img_height, int x, int y, float xScale, float yScale, int opacity) {
	dl = initDisplayList(dl);
	*(unsigned int*)(dl++) = 0xE200001C;
	*(unsigned int*)(dl++) = 0x00504240;
	*(unsigned int*)(dl++) = 0xFA000000;
	*(unsigned int*)(dl++) = 0xFFFFFF00 | opacity; // Last 2 bits == Opacity
	*(unsigned int*)(dl++) = 0xFCFF97FF;
	*(unsigned int*)(dl++) = 0xFF2CFE7F;
	*(unsigned int*)(dl++) = 0xE3001201;
	*(unsigned int*)(dl++) = 0x00000000;
	dl = displayImage(dl++, 48, 0, codec_index, 32, 32, x, y, xScale, yScale, 0, 0.0f);
	return dl;
};

int* drawTri(int* dl) {
	dl = initDisplayList(dl);
	//*(unsigned int*)(dl++) = 0xDE000000; // G_DL 0
	// gSPModifyVertex(dl++,0,G_MWO_POINT_XYSCREEN,0x00800080);
	// gSPModifyVertex(dl++,1,G_MWO_POINT_XYSCREEN,0x00A000A0);
	// gSPModifyVertex(dl++,2,G_MWO_POINT_XYSCREEN,0x00A00080);
	// gSPVertex(dl++,0,3,0);
	// gSP1Triangle(dl++,0,1,2,0);
	return dl;
}

// void tri_norm(floatPos* v1, floatPos* v2, floatPos* v3, floatPos* norm) {
//   	norm->xPos = (v2->yPos - v1->yPos) * (v3->zPos - v1->zPos) - (v2->zPos - v1->zPos) * (v3->yPos - v1->yPos);
//  	norm->yPos = (v2->zPos - v1->zPos) * (v3->xPos - v1->xPos) - (v2->xPos - v1->xPos) * (v3->zPos - v1->zPos);
//   	norm->zPos = (v2->xPos - v1->xPos) * (v3->yPos - v1->yPos) - (v2->yPos - v1->yPos) * (v3->xPos - v1->xPos);
//   	float norm_d = dk_sqrt(norm->xPos * norm->xPos + norm->yPos * norm->yPos + norm->zPos * norm->zPos);
//  	if (norm_d != 0.f) {
// 	    norm->xPos *= 127.f / norm_d;
// 	    norm->yPos *= 127.f / norm_d;
// 	    norm->zPos *= 127.f / norm_d;
//   	}
// }

// void draw_tri(Gfx **p_gfx_p, Gfx **p_gfx_d, floatPos* v1, floatPos* v2, floatPos* v3) {
//   	floatPos norm;
//   	tri_norm(v1, v2, v3, &norm);

//   	Vtx v[3] = {
// 	    gdSPDefVtxN(v1->xPos, v1->yPos, v1->zPos, 0, 0, norm.xPos, norm.yPos, norm.zPos, 0xFF),
// 	    gdSPDefVtxN(v2->xPos, v2->yPos, v2->zPos, 0, 0, norm.xPos, norm.yPos, norm.zPos, 0xFF),
// 	    gdSPDefVtxN(v3->xPos, v3->yPos, v3->zPos, 0, 0, norm.xPos, norm.yPos, norm.zPos, 0xFF),
// 	};

//   	gSPVertex((*p_gfx_p)++, gDisplayListData(p_gfx_d, v), 3, 0); // 01003000 vAddr
//   	gSP1Triangle((*p_gfx_p)++, 0, 1, 2, 0); // 05000204 00000000
// }