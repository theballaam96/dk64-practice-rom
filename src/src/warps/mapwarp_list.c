#include "../../include/common.h"

const MapWarp* warping_struct[] = {
	&map_japes_struct,
	&map_japesmain_struct,
	&map_aztec_struct,
	&map_aztecmain_struct,
	&map_aztecfivedt_struct,
	&map_factory_struct,
	&map_factorymain_struct,
	&map_galleon_struct,
	&map_galleonmain_struct,
	&map_galleonships_struct,
};

const int maps_container_functions[] = {
	(int)&openJapesMenu,
	(int)&openAztecMenu,
	(int)&openFactoryMenu,
	(int)&openGalleonMenu,
	0,
	0,
	0,
	0,
	0
};