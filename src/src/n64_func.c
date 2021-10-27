#include "../include/common.h"

static OSPiHandle CartROMHandle;
static OSPiHandle* osPiTable;

OSPiHandle* osCartROMInit(void) {
	int domain = 0;
	int saveMask;

	TestVariable = (int)&CartROMHandle;
	if (CartROMHandle.baseAddress == PHYS_TO_K1(PI_DOM1_ADDR2)) {
		return &CartROMHandle;
	}
	CartROMHandle.type = DEVICE_TYPE_CART;
	CartROMHandle.baseAddress = PHYS_TO_K1(PI_DOM1_ADDR2);
	__osPiRawReadIo(0, &domain);
	CartROMHandle.latency = domain & 0xFF;
	CartROMHandle.pulse = (domain >> 8) & 0xFF;
	CartROMHandle.pageSize = (domain >> 0x10) & 0xF;
	CartROMHandle.relDuration = (domain >> 0x14) & 0xF;
	CartROMHandle.domain = PI_DOMAIN1;
	wipeMemory(&CartROMHandle.transferInfo, sizeof(__OSTranxInfo));
	saveMask = __osDisableInt();
	CartROMHandle.next = osPiTable;
	osPiTable = &CartROMHandle;
	__osRestoreInt(saveMask);
	return &CartROMHandle;
}

void nuPiReadROM(int rom_start, void* buf_ptr, int size) {
	OSIoMesg ioMesg;
	OSMesg mesg;
	OSMesgQueue queue;
	int mesgSize;
	OSPiHandle* handle;
	handle = osCartROMInit();

	__osCreateMesgQueue(&queue, &mesg, 1);
	ioMesg.hdr.pri = OS_MESG_PRI_NORMAL;
	ioMesg.hdr.retQueue = &queue;
	__osInvalDCache(buf_ptr, size);
	__osInvalICache(buf_ptr, size);

	while (size != 0) {
		mesgSize = size;
		if (size > 0x4000) {
			mesgSize = 0x4000;
		}
		ioMesg.dramAddr = buf_ptr;
		ioMesg.devAddr = rom_start;
		ioMesg.size = mesgSize;
		__osEPiStartDMA(&CartROMHandle, &ioMesg, OS_READ);
		__osRecvMesg(&queue, &mesg, OS_MESG_BLOCK);
		rom_start += mesgSize;
		buf_ptr += mesgSize;
		size -= mesgSize;
	}
}

int pm64ReadFromROM(int rom_start, int rom_end, void* write_location) {
	int offset = 0;
	int diff = rom_end - rom_start;
	__osInvalICache(write_location, diff);
	if (0x2000 < diff) {
		while (0 == 0) {
			nuPiReadROM(rom_start + offset, write_location + offset, 0x2000);
			offset += 0x2000;
			if ((offset + 0x2000) >= diff) {
				break;
			}
		}
	}
	if (offset != diff) {
		nuPiReadROM(rom_start + offset, write_location + offset, diff - offset);
	}
	return offset;
}