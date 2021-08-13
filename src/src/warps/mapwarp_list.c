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
	&map_fungi_struct,
	&map_fungimain_struct,
	&map_fungigmush_struct,
	&map_fungimills_struct,
	&map_caves_struct,
	&map_cavesmain_struct,
	&map_caves5dc_struct,
	&map_caves5di_struct,
	&map_castle_struct,
	&map_castlemain_struct,
	&map_castlecrypt_struct,
	&map_castletunnel_struct,
	&map_castleoutside_struct,
	&map_castlerooms_struct,
	&map_isles_struct,
	&map_islesmain_struct,
	&map_isleslobbies_struct,
	&map_helmrool_struct,
};

const int maps_container_functions[] = {
	(int)&openJapesMenu,
	(int)&openAztecMenu,
	(int)&openFactoryMenu,
	(int)&openGalleonMenu,
	(int)&openFungiMenu,
	(int)&openCavesMenu,
	(int)&openCastleMenu,
	(int)&openHelmRoolMenu,
	(int)&openIslesMenu
};