#include "./../ultra64.h"

#define gDisplayListData(pgdl,d)      (*(Gfx**)(pgdl)-=(sizeof(d)+            \
                                       sizeof(Gfx)-1)/sizeof(Gfx),            \
                                       (__typeof__(&(d)))                     \
                                       dk_memcpy(*(Gfx**)(pgdl),&(d),sizeof(d)))