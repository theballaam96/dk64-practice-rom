#include "../include/common.h"

int* drawString(int* dl, int style, float x, float y, char* str) {
	float height = (float)getTextStyleHeight(style);
	float text_y = y - (height * 0x5);
	int* dl_copy = displayText(dl, style, 4 * x, 4 * text_y, str, 0);
	return dl_copy;
}

int* drawText(int* dl, int style, float x, float y, char* str, int red, int green, int blue, int opacity) {
	dl = initDisplayList(dl);
	if (style == 1) {
		*(unsigned int*)(dl++) = 0xFCFFFFFF;
		*(unsigned int*)(dl++) = 0xFFFCF279;
		*(unsigned int*)(dl++) = 0xDA380003;
		*(unsigned int*)(dl++) = 0x807FDAC0;
	} else {
		*(unsigned int*)(dl++) = 0xDE000000; // G_DL 0
		*(unsigned int*)(dl++) = 0x01000118; // G_VTX 0 11
		*(unsigned int*)(dl++) = 0xFC119623; // G_SETCOMBINE
		*(unsigned int*)(dl++) = 0xFF2FFFFF; // G_SETCIMG format: 1, 1, -1
		if (style == 6) {
			*(unsigned int*)(dl++) = 0xDA380003;
			*(unsigned int*)(dl++) = (int)&style6Mtx[0];
			// gSPMatrix(dl, (int)&style6Mtx[0], 3);
			// dl += 2;
		} else if (style == 2) {
			*(unsigned int*)(dl++) = 0xDA380003;
			*(unsigned int*)(dl++) = (int)&style2Mtx[0];
			// gSPMatrix(dl, (int)&style2Mtx[0], 3);
			// dl += 2;
		// } else if (style == 128) {
			// gSPMatrix(dl, (int)&style128Mtx[0], 3);
			// dl += 2;
		}
		gDPSetPrimColor(dl, 0, 0, red, green, blue, opacity);
		dl += 2;
	}
	dl = drawString(dl,style,x,y,str);
	return dl;
}

int* drawTextContainer(int* dl, int style, float x, float y, char* str, int red, int green, int blue, int opacity, int background) {
	if (background) {
		dl = drawText(dl,style,x-background,y+background,str,0,0,0,opacity);
	}
	dl = drawText(dl,style,x,y,str,red,green,blue,opacity);
	return dl;
}

int* drawImage(int* dl, int text_index, codecs codec_index, int img_width, int img_height, int x, int y, float xScale, float yScale, int opacity) {
	dl = initDisplayList(dl);
	*(unsigned int*)(dl++) = 0xE200001C;
	*(unsigned int*)(dl++) = 0x00504240;
	gDPSetPrimColor(dl, 0, 0, 0xFF, 0xFF, 0xFF, opacity);
	dl += 2;
	*(unsigned int*)(dl++) = 0xFCFF97FF;
	*(unsigned int*)(dl++) = 0xFF2CFE7F;
	*(unsigned int*)(dl++) = 0xE3001201;
	*(unsigned int*)(dl++) = 0x00000000;
	dl = displayImage(dl++, text_index, 0, codec_index, img_width, img_height, x, y, xScale, yScale, 0, 0.0f);
	return dl;
};

int* drawTri(int* dl, short x1, short y1, short x2, short y2, short x3, short y3, int red, int green, int blue, int alpha) {
	dl = initDisplayList(dl);
	if (assignedConsole != WIIU) {
		// Set Combine
		*(unsigned int*)(dl++) = 0xFC7EA004;
		*(unsigned int*)(dl++) = 0x100C00F4;
	} else {
		alpha = 0xFF;
	}
	// Vertex 0
	*(unsigned int*)(dl++) = 0x02180000;
	*(unsigned int*)(dl++) = (x1 << 16) | y1;
	*(unsigned int*)(dl++) = 0x02100000;
	*(unsigned int*)(dl++) = 0xFFFFFFFF;
	// Vertex 1
	*(unsigned int*)(dl++) = 0x02180002;
	*(unsigned int*)(dl++) = (x2 << 16) | y2;
	*(unsigned int*)(dl++) = 0x02100002;
	*(unsigned int*)(dl++) = 0xFFFFFFFF;
	// Vertex 2
	*(unsigned int*)(dl++) = 0x02180004;
	*(unsigned int*)(dl++) = (x3 << 16) | y3;
	*(unsigned int*)(dl++) = 0x02100004;
	*(unsigned int*)(dl++) = 0xFFFFFFFF;
	gDPSetPrimColor(dl, 0, 0, red, green, blue, alpha);
	dl += 2;
	// Draw Tri
	*(unsigned int*)(dl++) = 0x05000204;
	*(unsigned int*)(dl++) = 0x00000000;
	return dl;
}

int* drawPixelText(int* dl, int x, int y, char* str, int red, int green, int blue, int alpha) {
	*(unsigned int*)(dl++) = 0xE7000000;
    *(unsigned int*)(dl++) = 0x00000000;
    *(unsigned int*)(dl++) = 0xE3000A01;
    *(unsigned int*)(dl++) = 0x00000000;
    *(unsigned int*)(dl++) = 0xD9000000;
    *(unsigned int*)(dl++) = 0x00000000;
    *(unsigned int*)(dl++) = 0xD9FFFFFF;
    *(unsigned int*)(dl++) = 0x00200004;
    gDPSetPrimColor(dl, 0, 0, red, green, blue, alpha);
    dl += 2;
    *(unsigned int*)(dl++) = 0xFC119623;
    *(unsigned int*)(dl++) = 0xFF2FFFFF;
    *(unsigned int*)(dl++) = 0xE200001C;
    *(unsigned int*)(dl++) = 0x00504240;
    dl = textDraw(dl,2,x,y,str);
	return dl;
};

int* drawPixelTextContainer(int* dl, int x, int y, char* str, int red, int green, int blue, int alpha, int offset) {
	if (offset) {
		dl = drawPixelText(dl,x-offset,y+offset,str,0,0,0,alpha);
	}
	dl = drawPixelText(dl,x,y,str,red,green,blue,alpha);
	return dl;
}

int* drawScreenRect(int* dl, int x1, int y1, int x2, int y2, int red, int green, int blue, int alpha) {
	*(unsigned int*)(dl++) = 0xE7000000;
	*(unsigned int*)(dl++) = 0x00000000;
	*(unsigned int*)(dl++) = 0xE3000A01;
	*(unsigned int*)(dl++) = 0x00300000;
	*(unsigned int*)(dl++) = 0xE200001C;
	*(unsigned int*)(dl++) = 0x00000000;
	*(unsigned int*)(dl++) = 0xD9FFFFFE;
	*(unsigned int*)(dl++) = 0x00000000;
	*(unsigned int*)(dl++) = 0xF7000000;
	*(unsigned int*)(dl++) = ((red & 0x1F) << 11) | ((green & 0x1F) << 6) | ((blue & 0x1F) << 1) | (alpha & 0x1);
	*(unsigned int*)(dl++) = 0xED000000 | (((0xA * 4) & 0xFFF) << 12) | ((4 * 0xA) & 0xFFF);
	*(unsigned int*)(dl++) = (((4 * 0x135) & 0xFFF) << 12) | ((4 * 0xE5) & 0xFFF);
	*(unsigned int*)(dl++) = 0xF6000000 | ((x2 & 0x3FF) << 12) | (y2 & 0x3FF);
	*(unsigned int*)(dl++) = ((x1 & 0x3FF) << 12) | (y1 & 0x3FF);
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