function getMapObjectSetupData()
	objM2_header = mainmemory.read_u32_be(0x7F6010);
	if objM2_header > 0x7FFFFFFF and objM2_header < 0x80800000 then
		objM2_header = objM2_header - 0x80000000;
		objM2_count = mainmemory.read_u32_be(objM2_header);
		objM1_header = objM2_header + (2 * 0x4) + (0x30 * objM2_count);
		objM1_count = mainmemory.read_u32_be(objM1_header);
		return {objM2_header + 0x4, objM2_count, objM1_header + 0x4, objM1_count};
	end
	return {};
end

function populatePointers()
	mapObjectSetup_data = getMapObjectSetupData();
	object_pointers = {};
	mapObjectSetup_objM1_offset = 0x10;
	if #mapObjectSetup_data > 0 then
		local objM2Spawner_Array = mapObjectSetup_data[1];
		local objM2Spawner_Count = mapObjectSetup_data[2];
		local objM1Spawner_Array = mapObjectSetup_data[3];
		local objM1Spawner_Count = mapObjectSetup_data[4];
		if objM2Spawner_Count > 0 then
			for i = 1, objM2Spawner_Count do
				local slotBase = objM2Spawner_Array + ((i - 1) * 0x30);
				table.insert(object_pointers, slotBase);
			end
		end
		if objM1Spawner_Count > 0 then
			for i = 1, objM1Spawner_Count do
				local slotBase = objM1Spawner_Array + ((i - 1) * 0x38);
				table.insert(object_pointers, slotBase);
			end
		end
	end
	return object_pointers
end

function getActorFromEnemyType(index)
	local enemyTypeSize = 0x18;
	local behaviorIndex = mainmemory.read_u16_be(0x75EB80 + index * enemyTypeSize);
	return actor_types[behaviorIndex] or "Unknown 0x"..bizstring.hex(behaviorIndex);
end

function getSpawnerCount()
	endpoint_found = false;
	actorSpawner_header = mainmemory.read_u32_be(0x7FC400);
	count = 0;
	nextSpawner = actorSpawner_header;
	if actorSpawner_header > 0x7FFFFFFF and actorSpawner_header < 0x80800000 then
		actorSpawner_header = actorSpawner_header - 0x80000000;
		nextSpawner = actorSpawner_header;
		while not endpoint_found do
			count = count + 1;
			nextSpawner = mainmemory.read_u32_be(nextSpawner + 0x68);
			if nextSpawner < 0x80000000 or nextSpawner > 0x807FFFFF then
				endpoint_found = true;
			 	return count;
			end
			nextSpawner = nextSpawner - 0x80000000;
			emu.yield();
		end
	end
	return 0;
end

function populateActorSpawnerPointers()
	local actorSpawnerArray = mainmemory.read_u32_be(0x7FC400);
	mapObjectSetup_objM1_offset = 0x10;
	actor_spawners = {};
	if actorSpawnerArray > 0x7FFFFFFF and actorSpawnerArray < 0x80800000 then
		actorSpawnerArray = actorSpawnerArray - 0x80000000;
		local spawnerCount = getSpawnerCount();
		local nextSpawner = actorSpawnerArray;
		for i = 1, spawnerCount do
			local slotBase = nextSpawner;
			nextSpawner = mainmemory.read_u32_be(slotBase + 0x68) - 0x80000000;
			table.insert(actor_spawners, slotBase);
		end
	end
	return actor_spawners
end

function createFile()
	file = io.open("object_data.json", "w+")
	file:close(file)
end

function writeToFile(line)
	file = io.open("object_data.json", "a")
	file:write(line,"\n");
	file:close(file)
end

function printData()
	local list_data = getMapObjectSetupData();
	local pointers = populatePointers();
	local actor_counts = {};
	local objm2_counts = {};
	local actor_cap = 343;
	local objm2_cap = #object_types;
	local map_value = mainmemory.read_u32_be(0x76A0A8)
	local map_name = maps[map_value + 1] or "Unknown 0x"..bizstring.hex(map_value);
	print("Printing Data for Map #"..map_value.." ("..map_name..")")
	writeToFile("{");
	writeToFile("\"map\": \""..map_name.."\",")
	writeToFile("\"obj\": [");
	--print("First Actor: 0x"..bizstring.hex(list_data[3]))
	if map_value ~= 2 and map_value ~= 9 then
		if #pointers > 0 then
			for i = 1, #pointers do
				local focused_pointer = pointers[i];
				--print("0x"..bizstring.hex(focused_pointer))
				if focused_pointer < list_data[3] then
					--print("Obj M2")
					-- Object Model Two
					local id = mainmemory.read_u16_be(focused_pointer + 0x28);
					if objm2_counts[id] == nil then
						objm2_counts[id] = 1;
					else
						objm2_counts[id] = objm2_counts[id] + 1;
					end
				else
					--[[
					--print("Actor")
					-- Object Model One / Actor
					local id = mainmemory.read_u16_be(focused_pointer + 0x32) + 16;
					if actor_counts[id] == nil then
						actor_counts[id] = 1;
					else
						actor_counts[id] = actor_counts[id] + 1;
					end
					]]--
				end
			end
			--[[
			for i = 0, actor_cap do
				if actor_counts[i] ~= nil then
					if actor_counts[i] > 0 then
						local name = actor_types[i] or "Unknown 0x"..bizstring.hex(i);
						writeToFile("{\"name\": \""..name.."\", \"type\": \"actor\", \"count\": "..actor_counts[i].."},")
					end
				end
			end
			]]--
			for i = 0, objm2_cap do
				if objm2_counts[i] ~= nil then
					if objm2_counts[i] > 0 then
						local name = object_types[i] or "Unknown 0x"..bizstring.hex(i);
						writeToFile("{\"name\": \""..name.."\", \"type\": \"modeltwo\", \"count\": "..objm2_counts[i].."},")
					end
				end
			end
		end
		local actor_pointers = populateActorSpawnerPointers();
		if #actor_pointers > 0 then
			for i = 1, #actor_pointers do
				local id = mainmemory.read_u16_be(actor_pointers[i]) + 0x10
				if actor_counts[id] == nil then
					actor_counts[id] = 1;
				else
					actor_counts[id] = actor_counts[id] + 1;
				end
			end
		end
		for i = 0, actor_cap do
			if actor_counts[i] ~= nil then
				if actor_counts[i] > 0 then
					local name = actor_types[i] or "Unknown 0x"..bizstring.hex(i);
					writeToFile("{\"name\": \""..name.."\", \"type\": \"actor\", \"count\": "..actor_counts[i].."},")
				end
			end
		end

		local enemyRespawnObject = mainmemory.read_u32_be(0x7FDC8C);
		local enemySlotSize = 0x48;
		local enemy_counts = {};
		dual_enemy_counts = {};
		dual_enemy_indexes = {};
		local max_enemy_index = 0x70;
		if enemyRespawnObject > 0x7FFFFFFF and enemyRespawnObject < 0x80800000 then
			enemyRespawnObject = enemyRespawnObject - 0x80000000
			local numberOfEnemies = mainmemory.read_u16_be(0x7FDC88);
			for i = 1, numberOfEnemies do
				local slotBase = enemyRespawnObject + (i - 1) * enemySlotSize;
				local type_primary = mainmemory.readbyte(slotBase);
				local type_secondary = mainmemory.readbyte(slotBase + 0x44);
				if map_value == 48 then -- Fungi Forest
					if type_secondary == 0x2C then
						type_secondary = 0x67;
					elseif type_secondary == 0x9 then
						type_secondary = 0x54;
					elseif type_secondary == 0x1C then
						type_secondary = 0x63;
					end
				end
				--print("Type P: 0x"..type_primary..", Type S: 0x"..type_secondary)
				if type_primary == type_secondary then
					if enemy_counts[type_primary] == nil then
						enemy_counts[type_primary] = 1;
					else
						enemy_counts[type_primary] = enemy_counts[type_primary] + 1;
					end
				else
					local code = (type_primary * 256) + type_secondary;
					if #dual_enemy_indexes > 0 then
						local index_found = false
						for j = 1, #dual_enemy_indexes do
							if dual_enemy_indexes[j] == code then
								index_found = true;
							end
						end
						if index_found then
							dual_enemy_counts[code] = dual_enemy_counts[code] + 1;
						else
							dual_enemy_counts[code] = 1;
							table.insert(dual_enemy_indexes, code)
						end
					else
						table.insert(dual_enemy_indexes, code)
						dual_enemy_counts[code] = 1;
					end

				end
			end
			for i = 0, max_enemy_index do
				if enemy_counts[i] ~= nil then
					if enemy_counts[i] > 0 then
						local name = getActorFromEnemyType(i)
						writeToFile("{\"name\": \""..name.."\", \"type\": \"character\", \"count\": "..enemy_counts[i].."},")
					end
				end
			end
			if #dual_enemy_indexes > 0 then
				for i = 1, #dual_enemy_indexes do
					local focused_index = dual_enemy_indexes[i];
					local type_secondary = focused_index % 256;
					local type_primary = (focused_index - type_secondary) / 256;
					local name_primary = getActorFromEnemyType(type_primary);
					local name_secondary = getActorFromEnemyType(type_secondary);
					writeToFile("{\"name\": \""..name_primary.."\", \"altname\": \""..name_secondary.."\", \"type\": \"character\", \"count\": "..dual_enemy_counts[focused_index].."},")
				end
			end
		end
	end
	writeToFile("]");
	writeToFile("},");
end

maps = {
	"Test Map", -- 0
		"Funky's Store",
		"DK Arcade",
		"K. Rool Barrel: Lanky's Maze",
		"Jungle Japes: Mountain",
		"Cranky's Lab",
		"Jungle Japes: Minecart",
		"Jungle Japes",
		"Jungle Japes: Army Dillo",
		"Jetpac",
		"Kremling Kosh! (very easy)", -- 10
		"Stealthy Snoop! (normal, no logo)",
		"Jungle Japes: Shell",
		"Jungle Japes: Lanky's Cave",
		"Angry Aztec: Beetle Race",
		"Snide's H.Q.",
		"Angry Aztec: Tiny's Temple",
		"Hideout Helm",
		"Teetering Turtle Trouble! (very easy)",
		"Angry Aztec: Five Door Temple (DK)",
		"Angry Aztec: Llama Temple", -- 20
		"Angry Aztec: Five Door Temple (Diddy)",
		"Angry Aztec: Five Door Temple (Tiny)",
		"Angry Aztec: Five Door Temple (Lanky)",
		"Angry Aztec: Five Door Temple (Chunky)",
		"Candy's Music Shop",
		"Frantic Factory",
		"Frantic Factory: Car Race",
		"Hideout Helm (Level Intros, Game Over)",
		"Frantic Factory: Power Shed",
		"Gloomy Galleon", -- 30
		"Gloomy Galleon: K. Rool's Ship",
		"Batty Barrel Bandit! (easy)",
		"Jungle Japes: Chunky's Cave",
		"DK Isles Overworld",
		"K. Rool Barrel: DK's Target Game",
		"Frantic Factory: Crusher Room",
		"Jungle Japes: Barrel Blast",
		"Angry Aztec",
		"Gloomy Galleon: Seal Race",
		"Nintendo Logo", -- 40
		"Angry Aztec: Barrel Blast",
		"Troff 'n' Scoff", -- 42
		"Gloomy Galleon: Shipwreck (Diddy, Lanky, Chunky)",
		"Gloomy Galleon: Treasure Chest",
		"Gloomy Galleon: Mermaid",
		"Gloomy Galleon: Shipwreck (DK, Tiny)",
		"Gloomy Galleon: Shipwreck (Lanky, Tiny)",
		"Fungi Forest",
		"Gloomy Galleon: Lighthouse",
		"K. Rool Barrel: Tiny's Mushroom Game", -- 50
		"Gloomy Galleon: Mechanical Fish",
		"Fungi Forest: Ant Hill",
		"Battle Arena: Beaver Brawl!",
		"Gloomy Galleon: Barrel Blast",
		"Fungi Forest: Minecart",
		"Fungi Forest: Diddy's Barn",
		"Fungi Forest: Diddy's Attic",
		"Fungi Forest: Lanky's Attic",
		"Fungi Forest: DK's Barn",
		"Fungi Forest: Spider", -- 60
		"Fungi Forest: Front Part of Mill",
		"Fungi Forest: Rear Part of Mill",
		"Fungi Forest: Mushroom Puzzle",
		"Fungi Forest: Giant Mushroom",
		"Stealthy Snoop! (normal)",
		"Mad Maze Maul! (hard)",
		"Stash Snatch! (normal)",
		"Mad Maze Maul! (easy)",
		"Mad Maze Maul! (normal)", -- 69
		"Fungi Forest: Mushroom Leap", -- 70
		"Fungi Forest: Shooting Game",
		"Crystal Caves",
		"Battle Arena: Kritter Karnage!",
		"Stash Snatch! (easy)",
		"Stash Snatch! (hard)",
		"DK Rap",
		"Minecart Mayhem! (easy)", -- 77
		"Busy Barrel Barrage! (easy)",
		"Busy Barrel Barrage! (normal)",
		"Main Menu", -- 80
		"Title Screen (Not For Resale Version)",
		"Crystal Caves: Beetle Race",
		"Fungi Forest: Dogadon",
		"Crystal Caves: Igloo (Tiny)",
		"Crystal Caves: Igloo (Lanky)",
		"Crystal Caves: Igloo (DK)",
		"Creepy Castle",
		"Creepy Castle: Ballroom",
		"Crystal Caves: Rotating Room",
		"Crystal Caves: Shack (Chunky)", -- 90
		"Crystal Caves: Shack (DK)",
		"Crystal Caves: Shack (Diddy, middle part)",
		"Crystal Caves: Shack (Tiny)",
		"Crystal Caves: Lanky's Hut",
		"Crystal Caves: Igloo (Chunky)",
		"Splish-Splash Salvage! (normal)",
		"K. Lumsy",
		"Crystal Caves: Ice Castle",
		"Speedy Swing Sortie! (easy)",
		"Crystal Caves: Igloo (Diddy)", -- 100
		"Krazy Kong Klamour! (easy)",
		"Big Bug Bash! (very easy)",
		"Searchlight Seek! (very easy)",
		"Beaver Bother! (easy)",
		"Creepy Castle: Tower",
		"Creepy Castle: Minecart",
		"Kong Battle: Battle Arena",
		"Creepy Castle: Crypt (Lanky, Tiny)",
		"Kong Battle: Arena 1",
		"Frantic Factory: Barrel Blast", -- 110
		"Gloomy Galleon: Pufftoss",
		"Creepy Castle: Crypt (DK, Diddy, Chunky)",
		"Creepy Castle: Museum",
		"Creepy Castle: Library",
		"Kremling Kosh! (easy)",
		"Kremling Kosh! (normal)",
		"Kremling Kosh! (hard)",
		"Teetering Turtle Trouble! (easy)",
		"Teetering Turtle Trouble! (normal)",
		"Teetering Turtle Trouble! (hard)", -- 120
		"Batty Barrel Bandit! (easy)",
		"Batty Barrel Bandit! (normal)",
		"Batty Barrel Bandit! (hard)",
		"Mad Maze Maul! (insane)",
		"Stash Snatch! (insane)",
		"Stealthy Snoop! (very easy)",
		"Stealthy Snoop! (easy)",
		"Stealthy Snoop! (hard)",
		"Minecart Mayhem! (normal)",
		"Minecart Mayhem! (hard)", -- 130
		"Busy Barrel Barrage! (hard)",
		"Splish-Splash Salvage! (hard)",
		"Splish-Splash Salvage! (easy)",
		"Speedy Swing Sortie! (normal)",
		"Speedy Swing Sortie! (hard)",
		"Beaver Bother! (normal)",
		"Beaver Bother! (hard)",
		"Searchlight Seek! (easy)",
		"Searchlight Seek! (normal)",
		"Searchlight Seek! (hard)", -- 140
		"Krazy Kong Klamour! (normal)",
		"Krazy Kong Klamour! (hard)",
		"Krazy Kong Klamour! (insane)",
		"Peril Path Panic! (very easy)",
		"Peril Path Panic! (easy)",
		"Peril Path Panic! (normal)",
		"Peril Path Panic! (hard)",
		"Big Bug Bash! (easy)",
		"Big Bug Bash! (normal)",
		"Big Bug Bash! (hard)", -- 150
		"Creepy Castle: Dungeon",
		"Hideout Helm (Intro Story)",
		"DK Isles (DK Theatre)",
		"Frantic Factory: Mad Jack",
		"Battle Arena: Arena Ambush!",
		"Battle Arena: More Kritter Karnage!",
		"Battle Arena: Forest Fracas!",
		"Battle Arena: Bish Bash Brawl!",
		"Battle Arena: Kamikaze Kremlings!",
		"Battle Arena: Plinth Panic!", -- 160
		"Battle Arena: Pinnacle Palaver!",
		"Battle Arena: Shockwave Showdown!",
		"Creepy Castle: Basement",
		"Creepy Castle: Tree",
		"K. Rool Barrel: Diddy's Kremling Game",
		"Creepy Castle: Chunky's Toolshed",
		"Creepy Castle: Trash Can",
		"Creepy Castle: Greenhouse",
		"Jungle Japes Lobby",
		"Hideout Helm Lobby", -- 170
		"DK's House",
		"Rock (Intro Story)",
		"Angry Aztec Lobby",
		"Gloomy Galleon Lobby",
		"Frantic Factory Lobby",
		"Training Grounds",
		"Dive Barrel",
		"Fungi Forest Lobby",
		"Gloomy Galleon: Submarine",
		"Orange Barrel", -- 180
		"Barrel Barrel",
		"Vine Barrel",
		"Creepy Castle: Crypt",
		"Enguarde Arena",
		"Creepy Castle: Car Race",
		"Crystal Caves: Barrel Blast",
		"Creepy Castle: Barrel Blast",
		"Fungi Forest: Barrel Blast",
		"Fairy Island",
		"Kong Battle: Arena 2", -- 190
		"Rambi Arena",
		"Kong Battle: Arena 3",
		"Creepy Castle Lobby",
		"Crystal Caves Lobby",
		"DK Isles: Snide's Room",
		"Crystal Caves: Army Dillo",
		"Angry Aztec: Dogadon",
		"Training Grounds (End Sequence)",
		"Creepy Castle: King Kut Out",
		"Crystal Caves: Shack (Diddy, upper part)", -- 200
		"K. Rool Barrel: Diddy's Rocketbarrel Game",
		"K. Rool Barrel: Lanky's Shooting Game",
		"K. Rool Fight: DK Phase",
		"K. Rool Fight: Diddy Phase",
		"K. Rool Fight: Lanky Phase",
		"K. Rool Fight: Tiny Phase",
		"K. Rool Fight: Chunky Phase",
		"Bloopers Ending",
		"K. Rool Barrel: Chunky's Hidden Kremling Game",
		"K. Rool Barrel: Tiny's Pony Tail Twirl Game", -- 210
		"K. Rool Barrel: Chunky's Shooting Game",
		"K. Rool Barrel: DK's Rambi Game",
		"K. Lumsy Ending",
		"K. Rool's Shoe",
		"K. Rool's Arena", -- 215
}

actor_types = { -- These are different on Kiosk
	[2] = "DK",
		[3] = "Diddy",
		[4] = "Lanky",
		[5] = "Tiny",
		[6] = "Chunky",
		[7] = "Krusha",
		[8] = "Rambi",
		[9] = "Enguarde",
		--[10] = "Unknown", -- Always loaded -- TODO: Figure out what actors 10-15 do
		--[11] = "Unknown", -- Always loaded -- What is this?
		[12] = "Loading Zone Controller", -- Always loaded
		[13] = "Object Model 2 Controller", -- Always loaded
		--[14] = "Unknown", -- Always loaded -- What is this?
		--[15] = "Unknown", -- Always loaded -- What is this?
		[17] = "Cannon Barrel",
		[18] = "Rambi Crate",
		[19] = "Barrel (Diddy 5DI)",
		[20] = "Camera Focus Point", -- Exists during some cutscenes
		[21] = "Pushable Box",
		[22] = "Barrel Spawner", -- Normal barrel on a star pad, unused?
		[23] = "Cannon",
		[24] = "Race Hoop", -- Vulture Race
		[25] = "Hunky Chunky Barrel",
		[26] = "TNT Barrel",
		[27] = "TNT Barrel Spawner", -- Army Dillo
		[28] = "Bonus Barrel",
		[29] = "Minecart",
		[30] = "Fireball", -- Boss fights
		[31] = "Bridge (Castle)",
		[32] = "Swinging Light",
		[33] = "Vine", -- Brown
		[34] = "Kremling Kosh Controller",
		[35] = "Melon (Projectile)",
		[36] = "Peanut",
		[37] = "Rocketbarrel", -- On Kong
		[38] = "Pineapple",
		[39] = "Large Brown Bridge", -- Unused?
		[40] = "Mini Monkey Barrel",
		[41] = "Orange",
		[42] = "Grape",
		[43] = "Feather",
		[44] = "Laser", -- Projectile
		[45] = "Golden Banana", -- Vulture, bonus barrels (US code 0x6818EE), probably some other places
		[46] = "Barrel Gun", -- Teetering Turtle Trouble
		[47] = "Watermelon Slice",
		[48] = "Coconut",
		[49] = "Rocketbarrel", -- The Barrel
		[50] = "Lime",
		[51] = "Ammo Crate", -- Dropped by Red Klaptrap
		[52] = "Orange Pickup", -- Dropped by Klump & Purple Klaptrap
		[53] = "Banana Coin", -- Dropped by "Diddy", otherwise unused?
		[54] = "DK Coin", -- Minecart
		[55] = "Small Explosion", -- Seasick Chunky
		[56] = "Orangstand Sprint Barrel",
		[57] = "Strong Kong Barrel",
		[58] = "Swinging Light",
		[59] = "Fireball", -- Mad Jack etc.
		[60] = "Bananaporter",
		[61] = "Boulder",
		[62] = "Minecart", -- DK?
		[63] = "Vase (O)",
		[64] = "Vase (:)",
		[65] = "Vase (Triangle)",
		[66] = "Vase (+)",
		[67] = "Cannon Ball",
		-- [68] = "Unknown",
		[69] = "Vine", -- Green
		[70] = "Counter", -- Unused?
		[71] = "Kremling (Red)", -- Lanky's Keyboard Game in R&D
		[72] = "Boss Key",
		[73] = "Cannon", -- Galleon Minigame
		[74] = "Cannon Ball", -- Galleon Minigame Projectile
		[75] = "Blueprint (Diddy)",
		[76] = "Blueprint (Chunky)",
		[77] = "Blueprint (Lanky)",
		[78] = "Blueprint (DK)",
		[79] = "Blueprint (Tiny)",
		[80] = "Minecart", -- Chunky?
		[81] = "Fire Spawner? (Dogadon)", -- TODO: Verify
		[82] = "Boulder Debris", -- Minecart
		[83] = "Spider Web", -- Fungi miniBoss
		[84] = "Steel Keg Spawner",
		[85] = "Steel Keg",
		[86] = "Crown",
		[87] = "Minecart", -- BONUS
		-- [88] = "Unknown",
		[89] = "Fire", -- Unused?
		[90] = "Ice Wall?",
		[91] = "Balloon (Diddy)",
		[92] = "Stalactite",
		[93] = "Rock Debris", -- Rotating, Unused?
		[94] = "Car", -- Unused?
		[95] = "Pause Menu",
		[96] = "Hunky Chunky Barrel (Dogadon)",
		[97] = "TNT Barrel Spawner (Dogadon)",
		[98] = "Tag Barrel",
		[99] = "Fireball", -- Get Out
		[100] = "1 Pad (Diddy 5DI)",
		[101] = "2 Pad (Diddy 5DI)",
		[102] = "3 Pad (Diddy 5DI)",
		[103] = "4 Pad (Diddy 5DI)",
		[104] = "5 Pad (Diddy 5DI)",
		[105] = "6 Pad (Diddy 5DI)",
		[106] = "Kong Reflection",
		[107] = "Bonus Barrel (Hideout Helm)",
		-- [108] = "Unknown",
		[109] = "Race Checkpoint",
		[110] = "CB Bunch", -- Unused? Doesn't seem to work, these are normally model 2
		[111] = "Balloon (Chunky)",
		[112] = "Balloon (Tiny)",
		[113] = "Balloon (Lanky)",
		[114] = "Balloon (DK)",
		[115] = "K. Lumsy's Cage", -- TODO: Also rabbit race finish line?
		[116] = "Chain",
		[117] = "Beanstalk",
		[118] = "Yellow ?", -- Unused?
		[119] = "CB Single (Blue)", -- Unused? Doesn't seem to work, these are normally model 2
		[120] = "CB Single (Yellow)", -- Unused? Doesn't seem to work, these are normally model 2
		[121] = "Crystal Coconut", -- Unused? Doesn't seem to work, these are normally model 2
		[122] = "DK Coin", -- Multiplayer
		[123] = "Kong Mirror", -- Creepy Castle Museum
		[124] = "Barrel Gun", -- Peril Path Panic
		[125] = "Barrel Gun", -- Krazy Kong Klamour
		[126] = "Fly Swatter",
		[127] = "Searchlight", -- Searchlight Seek
		[128] = "Headphones",
		[129] = "Enguarde Crate",
		[130] = "Apple", -- Fungi
		[131] = "Worm", -- Fungi
		[132] = "Enguarde Crate (Unused?)",
		[133] = "Barrel",
		[134] = "Training Barrel",
		[135] = "Boombox", -- Treehouse
		[136] = "Tag Barrel",
		[137] = "Tag Barrel", -- Troff'n'Scoff
		[138] = "B. Locker",
		[139] = "Rainbow Coin Patch",
		[140] = "Rainbow Coin",
		-- [141] = "Unknown",
		-- [142] = "Unknown",
		-- [143] = "Unknown",
		-- [144] = "Unknown",
		[145] = "Cannon (Seasick Chunky)", -- Internal name "Puffer cannon"
		-- [146] = "Unknown",
		[147] = "Balloon (Unused - K. Rool)", -- Internal Name: K. Rool Banana Balloon, unsure of purpose. Can only be popped by Lanky
		[148] = "Rope", -- K. Rool's Arena
		[149] = "Banana Barrel", -- Lanky Phase
		[150] = "Banana Barrel Spawner", -- Lanky Phase, internal name "Skin barrel generator"
		-- [151] = "Unknown",
		-- [152] = "Unknown",
		-- [153] = "Unknown",
		-- [154] = "Unknown",
		-- [155] = "Unknown",
		[156] = "Wrinkly",
		-- [157] = "Unknown",
		-- [158] = "Unknown",
		-- [159] = "Unknown",
		-- [160] = "Unknown",
		-- [161] = "Unknown",
		-- [162] = "Unknown",
		[163] = "Banana Fairy (BFI)",
		[164] = "Ice Tomato",
		[165] = "Tag Barrel (King Kut Out)",
		[166] = "King Kut Out Part",
		[167] = "Cannon",
		-- [168] = "Unknown",
		[169] = "Pufftup", -- Pufftoss Fight
		[170] = "Damage Source", -- K. Rool's Glove
		[171] = "Orange", -- Krusha's Gun
		[173] = "Cutscene Controller",
		-- [174] = "Unknown",
		[175] = "Kaboom",
		[176] = "Timer",
		[177] = "Timer Controller", -- Pufftoss Fight & Fac Beaver Bother Spawn Timer
		[178] = "Beaver", -- Blue
		[179] = "Shockwave (Mad Jack)",
		[180] = "Krash", -- Minecart Club Guy
		[181] = "Book", -- Castle Library
		[182] = "Klobber",
		[183] = "Zinger",
		[184] = "Snide",
		[185] = "Army Dillo",
		[186] = "Kremling", -- Kremling Kosh
		[187] = "Klump",
		[188] = "Camera",
		[189] = "Cranky",
		[190] = "Funky",
		[191] = "Candy",
		[192] = "Beetle", -- Race
		[193] = "Mermaid",
		[194] = "Vulture",
		[195] = "Squawks",
		[196] = "Cutscene DK",
		[197] = "Cutscene Diddy",
		[198] = "Cutscene Lanky",
		[199] = "Cutscene Tiny",
		[200] = "Cutscene Chunky",
		[201] = "Llama",
		[202] = "Fairy Picture",
		[203] = "Padlock (T&S)",
		[204] = "Mad Jack",
		[205] = "Klaptrap", -- Green
		[206] = "Zinger",
		[207] = "Vulture (Race)",
		[208] = "Klaptrap (Purple)",
		[209] = "Klaptrap (Red)",
		[210] = "GETOUT Controller",
		[211] = "Klaptrap (Skeleton)",
		[212] = "Beaver (Gold)",
		[213] = "Fire Column Spawner", -- Japes Minecart
		[214] = "Minecart (TNT)", -- Minecart Mayhem
		[215] = "Minecart (TNT)",
		[216] = "Pufftoss",
		-- [217] = "Unknown",
		[218] = "Handle",
		[219] = "Slot",
		[220] = "Cannon (Seasick Chunky)",
		[221] = "Light Piece", -- Lanky Phase
		[222] = "Banana Peel", -- Lanky Phase
		[223] = "Fireball Spawner", -- Factory Crusher Room
		[224] = "Mushroom Man",
		-- [225] = "Unknown",
		[226] = "Troff",
		[227] = "K. Rool's Foot", -- Including leftmost toe
		[228] = "Bad Hit Detection Man",
		[229] = "K. Rool's Toe", -- Rightmost 3 toes
		[230] = "Ruler",
		[231] = "Toy Box",
		[232] = "Text Overlay",
		[233] = "Squawks",
		[234] = "Scoff",
		[235] = "Robo-Kremling",
		[236] = "Dogadon",
		-- [237] = "Unknown",
		[238] = "Kremling",
		[239] = "Bongos",
		[240] = "Spotlight Fish",
		[241] = "Kasplat (DK)",
		[242] = "Kasplat (Diddy)",
		[243] = "Kasplat (Lanky)",
		[244] = "Kasplat (Tiny)",
		[245] = "Kasplat (Chunky)",
		[246] = "Mechanical Fish",
		[247] = "Seal",
		[248] = "Banana Fairy",
		[249] = "Squawks with spotlight",
		[250] = "Owl",
		[251] = "Spider miniBoss",
		[252] = "Rabbit", -- Fungi
		[253] = "Nintendo Logo",
		[254] = "Cutscene Object", -- For objects animated by Cutscenes
		[255] = "Shockwave",
		[256] = "Minigame Controller",
		[257] = "Fire Breath Spawner", -- Aztec Beetle Race
		[258] = "Shockwave", -- Boss
		[259] = "Guard", -- Stealthy Snoop
		[260] = "Text Overlay", -- K. Rool fight
		[261] = "Robo-Zinger",
		[262] = "Krossbones",
		[263] = "Fire Shockwave (Dogadon)",
		[264] = "Squawks",
		[265] = "Light beam", -- Boss fights etc
		[266] = "DK Rap Controller", -- Handles the lyrics etc
		[267] = "Shuri",
		[268] = "Gimpfish",
		[269] = "Mr. Dice",
		[270] = "Sir Domino",
		[271] = "Mr. Dice",
		[272] = "Rabbit",
		[273] = "Fireball (With Glasses)", -- From Chunky 5DI
		-- [274] = "Unknown",
		[275] = "K. Lumsy",
		[276] = "Spiderling",
		[277] = "Squawks",
		[278] = "Projectile", -- Spider miniBoss
		-- [279] = "Unknown",
		[280] = "Spider Silk String", -- Spider miniBoss
		[281] = "K. Rool (DK Phase)",
		[282] = "Retexturing Controller", -- Beaver Bother
		[283] = "Skeleton Head",
		-- [284] = "Unknown",
		[285] = "Bat",
		[286] = "Giant Clam",
		-- [287] = "Unknown",
		[288] = "Tomato", -- Fungi
		[289] = "Kritter-in-a-Sheet",
		[290] = "Pufftup",
		[291] = "Kosha",
		[292] = "K. Rool (Diddy Phase)",
		[293] = "K. Rool (Lanky Phase)",
		[294] = "K. Rool (Tiny Phase)",
		[295] = "K. Rool (Chunky Phase)",
		-- [296] = "Unknown",
		[297] = "Battle Crown Controller",
		-- [298] = "Unknown",
		[299] = "Textbox",
		[300] = "Snake", -- Teetering Turtle Trouble
		[301] = "Turtle", -- Teetering Turtle Trouble
		[302] = "Toy Car", -- Player in the Factory Toy Car Race
		[303] = "Toy Car",
		[304] = "Camera", -- Factory Toy Car Race
		[305] = "Missile", -- Car Race
		-- [306] = "Unknown",
		-- [307] = "Unknown",
		[308] = "Seal",
		[309] = "Kong Logo (Instrument)", -- DK for DK, Star for Diddy, DK for Lanky, Flower for Tiny, DK for Chunky
		[310] = "Spotlight", -- Tag barrel, instrument etc.
		[311] = "Race Checkpoint", -- Seal race & Castle car race
		[312] = "Minecart (TNT)",
		[313] = "Idle Particle",
		[314] = "Rareware Logo",
		-- [315] = "Unknown",
		[316] = "Kong (Tag Barrel)",
		[317] = "Locked Kong (Tag Barrel)",
		-- [318] = "Unknown",
		[319] = "Propeller (Boat)",
		[320] = "Potion", -- Cranky Purchase
		[321] = "Fairy (Refill)", -- Refill Fairy
		[322] = "Car", -- Car Race
		[323] = "Enemy Car", -- Car Race, aka George
		[324] = "Text Overlay Controller", -- Candy's
		[325] = "Shockwave", -- Simian Slam
		[326] = "Main Menu Controller",
		[327] = "Kong", -- Krazy Kong Klamour
		[328] = "Klaptrap", -- Peril Path Panic
		[329] = "Fairy", -- Peril Path Panic
		[330] = "Bug", -- Big Bug Bash
		[331] = "Klaptrap", -- Searchlight Seek
		[332] = "Big Bug Bash Controller?", -- TODO: Fly swatter?
		[333] = "Barrel (Main Menu)",
		[334] = "Padlock (K. Lumsy)",
		[335] = "Snide's Menu",
		[336] = "Training Barrel Controller",
		[337] = "Multiplayer Model (Main Menu)",
		[338] = "End Sequence Controller",
		[339] = "Arena Controller", -- Rambi/Enguarde
		[340] = "Bug", -- Trash Can
		[342] = "Try Again Dialog",
		[343] = "Pause Menu", -- Mystery menu bosses
};

object_types = { -- "-" means that spawning this object crashes the game
	[0x00] = "Nothing", -- "test" internal name
		[0x01] = "Thin Flame?", -- 2D
		[0x02] = "-",
		[0x03] = "Tree", -- 2D
		[0x04] = "-",
		[0x05] = "Yellow Flowers", -- 2D
		[0x06] = "-",
		[0x07] = "-",
		[0x08] = "Xmas Holly?", -- 2D
		[0x09] = "-",
		[0x0A] = "CB Single (Diddy)",
		[0x0B] = "Large Wooden Panel", -- 2D
		[0x0C] = "Flames", -- 2D
		[0x0D] = "CB Single (DK)",
		[0x0E] = "Large Iron Bars Panel", -- 2D
		[0x0F] = "Goo Hand", -- Castle
		[0x10] = "Flame", -- 2D
		[0x11] = "Homing Ammo Crate",
		[0x12] = "Coffin Door",
		[0x13] = "Coffin Lid",
		[0x14] = "Skull", -- Castle, it has a boulder in it
		[0x15] = "Wooden Crate",
		[0x16] = "CB Single (Tiny)",
		[0x17] = "Shield", -- Castle
		[0x18] = "Metal thing",
		[0x19] = "Coffin",
		[0x1A] = "Metal Panel",
		[0x1B] = "Rock Panel",
		[0x1C] = "Banana Coin (Tiny)",
		[0x1D] = "Banana Coin (DK)",
		[0x1E] = "CB Single (Lanky)",
		[0x1F] = "CB Single (Chunky)",
		[0x20] = "Tree", -- Japes?
		[0x21] = "-",
		[0x22] = "Metal Panel",
		[0x23] = "Banana Coin (Lanky)",
		[0x24] = "Banana Coin (Diddy)",
		[0x25] = "Metal Panel",
		[0x26] = "Metal Panel Red",
		[0x27] = "Banana Coin (Chunky)",
		[0x28] = "Metal Panel Grey",
		[0x29] = "Tree", -- Japes?
		[0x2A] = "-",
		[0x2B] = "CB Bunch (DK)",
		[0x2C] = "Hammock",
		[0x2D] = "Small jungle bush plant",
		[0x2E] = "-",
		[0x2F] = "Small plant",
		[0x30] = "Bush", -- Japes
		[0x31] = "-",
		[0x32] = "-",
		[0x33] = "-", -- Fungi Lobby, Unknown
		[0x34] = "Metal Bridge", -- Helm Lobby
		[0x35] = "Large Blue Crystal", -- Crystal Caves Lobby
		[0x36] = "Plant",
		[0x37] = "Plant",
		[0x38] = "-",
		[0x39] = "White Flowers",
		[0x3A] = "Stem 4 Leaves",
		[0x3B] = "-",
		[0x3C] = "-",
		[0x3D] = "Small plant",
		[0x3E] = "-",
		[0x3F] = "-",
		[0x40] = "-",
		[0x41] = "-",
		[0x42] = "-",
		[0x43] = "Yellow Flower",
		[0x44] = "Blade of Grass Large",
		[0x45] = "Lilypad?",
		[0x46] = "Plant",
		[0x47] = "Iron Bars", -- Castle Lobby Coconut Switch
		[0x48] = "Nintendo Coin", -- Not sure if this is collectable
		[0x49] = "Metal Floor",
		[0x4A] = "-",
		[0x4B] = "-",
		[0x4C] = "Bull Rush",
		[0x4D] = "-",
		[0x4E] = "-",
		[0x4F] = "Metal box/platform",
		[0x50] = "K Crate", -- DK Helm Target Barrel
		[0x51] = "-",
		[0x52] = "Wooden panel",
		[0x53] = "-",
		[0x54] = "-",
		[0x55] = "-",
		[0x56] = "Orange",
		[0x57] = "Watermelon Slice",
		[0x58] = "Tree", -- Unused?
		[0x59] = "Tree", -- Unused
		[0x5A] = "Tree",
		[0x5B] = "Tree (Black)", -- Unused
		[0x5C] = "-",
		[0x5D] = "Light Green platform",
		[0x5E] = "-",
		[0x5F] = "-",
		[0x60] = "-",
		[0x61] = "-",
		[0x62] = "Brick Wall",
		[0x63] = "-",
		[0x64] = "-",
		[0x65] = "-",
		[0x66] = "-",
		[0x67] = "Wrinkly Door (Tiny)",
		[0x68] = "-",
		[0x69] = "-",
		[0x6A] = "-",
		[0x6B] = "Conveyor Belt",
		[0x6C] = "Tree", -- Japes?
		[0x6D] = "Tree",
		[0x6E] = "Tree",
		[0x6F] = "-",
		[0x70] = "Primate Punch Switch", -- Factory
		[0x71] = "Hi-Lo toggle machine",
		[0x72] = "Breakable Metal Grate", -- Factory
		[0x73] = "Cranky's Lab",
		[0x74] = "Golden Banana",
		[0x75] = "Metal Platform",
		[0x76] = "Metal Bars",
		[0x77] = "-",
		[0x78] = "Metal fence",
		[0x79] = "Snide's HQ",
		[0x7A] = "Funky's Armory",
		[0x7B] = "-",
		[0x7C] = "Blue lazer field",
		[0x7D] = "-",
		[0x7E] = "Bamboo Gate",
		[0x7F] = "-",
		[0x80] = "Tree Stump",
		[0x81] = "Breakable Hut", -- Japes
		[0x82] = "Mountain Bridge", -- Japes
		[0x83] = "Tree Stump", -- Japes
		[0x84] = "Bamboo Gate",
		[0x85] = "-",
		[0x86] = "Blue/green tree",
		[0x87] = "-",
		[0x88] = "Mushroom",
		[0x89] = "-",
		[0x8A] = "Disco Ball",
		[0x8B] = "2 Door (5DS)", -- Galleon
		[0x8C] = "3 Door (5DS)", -- Galleon
		[0x8D] = "Map of DK island",
		[0x8E] = "Crystal Coconut",
		[0x8F] = "Ammo Crate",
		[0x90] = "Banana Medal",
		[0x91] = "Peanut",
		[0x92] = "Simian Slam Switch (Chunky, Green)",
		[0x93] = "Simian Slam Switch (Diddy, Green)",
		[0x94] = "Simian Slam Switch (DK, Green)",
		[0x95] = "Simian Slam Switch (Lanky, Green)",
		[0x96] = "Simian Slam Switch (Tiny, Green)",
		[0x97] = "Baboon Blast Pad",
		[0x98] = "Film",
		[0x99] = "Chunky Rotating Room", -- Aztec, Tiny Temple
		[0x9A] = "Stone Monkey Face",
		[0x9B] = "Stone Monkey Face",
		[0x9C] = "Aztec Panel blue",
		[0x9D] = "-", -- templestuff, in Tiny Temple
		[0x9E] = "Ice Floor",
		[0x9F] = "Ice Pole", -- I think this is a spotlight
		[0xA0] = "Big Blue wall panel",
		[0xA1] = "Big Blue wall panel",
		[0xA2] = "Big Blue wall panel",
		[0xA3] = "Big Blue wall panel",
		[0xA4] = "KONG Letter (K)",
		[0xA5] = "KONG Letter (O)",
		[0xA6] = "KONG Letter (N)",
		[0xA7] = "KONG Letter (G)",
		[0xA8] = "Bongo Pad", -- DK
		[0xA9] = "Guitar Pad", -- Diddy
		[0xAA] = "Saxaphone Pad", -- Tiny
		[0xAB] = "Triangle Pad", -- Chunky
		[0xAC] = "Trombone Pad", -- Lanky
		[0xAD] = "Wood panel small",
		[0xAE] = "Wood panel small",
		[0xAF] = "Wood panel small",
		[0xB0] = "Wood Panel small",
		[0xB1] = "Wall Panel", -- Aztec
		[0xB2] = "Wall Panel", -- Caves?
		[0xB3] = "Stone Monkey Face (Not Solid)",
		[0xB4] = "Feed Me Totem", -- Aztec
		[0xB5] = "Melon Crate",
		[0xB6] = "Lava Platform", -- Aztec, Llama temple
		[0xB7] = "Rainbow Coin",
		[0xB8] = "Green Switch",
		[0xB9] = "Coconut Indicator", -- Free Diddy
		[0xBA] = "Snake Head", -- Aztec, Llama temple
		[0xBB] = "Matching Game Board", -- Aztec, Llama temple
		[0xBC] = "Stone Monkey Head", -- Aztec
		[0xBD] = "Large metal section",
		[0xBE] = "Production Room Crusher", -- Factory
		[0xBF] = "Metal Platform",
		[0xC0] = "Metal Object",
		[0xC1] = "Metal Object",
		[0xC2] = "Metal Object",
		[0xC3] = "Gong", -- Diddy Kong
		[0xC4] = "Platform", -- Aztec
		[0xC5] = "Bamboo together",
		[0xC6] = "Metal Bars",
		[0xC7] = "Target", -- Minigames
		[0xC8] = "Wooden object",
		[0xC9] = "Ladder",
		[0xCA] = "Ladder",
		[0xCB] = "Wooden pole",
		[0xCC] = "Blue panel",
		[0xCD] = "Ladder",
		[0xCE] = "Grey Switch",
		[0xCF] = "D Block for toy world",
		[0xD0] = "Hatch (Factory)",
		[0xD1] = "Metal Bars",
		[0xD2] = "Raisable Metal Platform",
		[0xD3] = "Metal Cage",
		[0xD4] = "Simian Spring Pad",
		[0xD5] = "Power Shed", -- Factory
		[0xD6] = "Metal platform",
		[0xD7] = "Sun Lighting effect panel",
		[0xD8] = "Wooden Pole",
		[0xD9] = "Wooden Pole",
		[0xDA] = "Wooden Pole",
		[0xDB] = "-",
		[0xDC] = "Question Mark Box",
		[0xDD] = "Blueprint (Tiny)",
		[0xDE] = "Blueprint (DK)",
		[0xDF] = "Blueprint (Chunky)",
		[0xE0] = "Blueprint (Diddy)",
		[0xE1] = "Blueprint (Lanky)",
		[0xE2] = "Tree Dark",
		[0xE3] = "Rope",
		[0xE4] = "-",
		[0xE5] = "-",
		[0xE6] = "Lever",
		[0xE7] = "Green Croc Head (Minecart)",
		[0xE8] = "Metal Gate with red/white stripes",
		[0xE9] = "-",
		[0xEA] = "Purple Croc Head (Minecart)",
		[0xEB] = "Wood panel",
		[0xEC] = "DK coin",
		[0xED] = "Wooden leg",
		[0xEE] = "-",
		[0xEF] = "Wrinkly Door (Lanky)",
		[0xF0] = "Wrinkly Door (DK)",
		[0xF1] = "Wrinkly Door (Chunky)",
		[0xF2] = "Wrinkly Door (Diddy)",
		[0xF3] = "Torch",
		[0xF4] = "Number Game (1)", -- Factory
		[0xF5] = "Number Game (2)", -- Factory
		[0xF6] = "Number Game (3)", -- Factory
		[0xF7] = "Number Game (4)", -- Factory
		[0xF8] = "Number Game (5)", -- Factory
		[0xF9] = "Number Game (6)", -- Factory
		[0xFA] = "Number Game (7)", -- Factory
		[0xFB] = "Number Game (8)", -- Factory
		[0xFC] = "Number Game (9)", -- Factory
		[0xFD] = "Number Game (10)", -- Factory
		[0xFE] = "Number Game (11)", -- Factory
		[0xFF] = "Number Game (12)", -- Factory
		[0x100] = "Number Game (13)", -- Factory
		[0x101] = "Number Game (14)", -- Factory
		[0x102] = "Number Game (15)", -- Factory
		[0x103] = "Number Game (16)", -- Factory
		[0x104] = "Bad Hit Detection Wheel", -- Factory
		[0x105] = "Breakable Gate", -- Galleon Primate Punch
		[0x106] = "-",
		[0x107] = "Picture of DK island",
		[0x108] = "White flashing thing",
		[0x109] = "Barrel", -- Galleon Ship
		[0x10A] = "Gorilla Gone Pad",
		[0x10B] = "Monkeyport Pad",
		[0x10C] = "Baboon Balloon Pad",
		[0x10D] = "Light", -- Factory?
		[0x10E] = "Light", -- Factory?
		[0x10F] = "Barrel", -- Galleon Ship
		[0x110] = "Barrel", -- Galleon Ship
		[0x111] = "Barrel", -- Galleon Ship
		[0x112] = "Barrel", -- Galleon Ship
		[0x113] = "Pad", -- TODO: Empty blue pad? Where is this used?
		[0x114] = "Red Light", -- Factory?
		[0x115] = "Breakable X Panel", -- To enter Japes underground
		[0x116] = "Power Shed Screen", -- Factory
		[0x117] = "Crusher", -- Factory
		[0x118] = "Floor Panel",
		[0x119] = "Metal floor panel mesh",
		[0x11A] = "Metal Door", -- Factory or Car Race
		[0x11B] = "Metal Door", -- Factory or Car Race
		[0x11C] = "Metal Door", -- Factory or Car Race
		[0x11D] = "Metal Door", -- Factory or Car Race
		[0x11E] = "Metal Door", -- Factory or Car Race
		[0x11F] = "Metal Door", -- Factory or Car Race
		[0x120] = "Toyz Box",
		[0x121] = "O Pad", -- Aztec Chunky Puzzle
		[0x122] = "Bonus Barrel Trap", -- Aztec
		[0x123] = "Sun Idol", -- Aztec, top of "feed me" totem
		[0x124] = "Candy's Shop",
		[0x125] = "Pineapple Switch",
		[0x126] = "Peanut Switch",
		[0x127] = "Feather Switch",
		[0x128] = "Grape Switch",
		[0x129] = "Coconut Switch",
		[0x12A] = "-",
		[0x12B] = "Kong Pad",
		[0x12C] = "Boss Door", -- Troff'n'Scoff
		[0x12D] = "Troff 'n' Scoff Feed Pad",
		[0x12E] = "Metal Bars horizontal",
		[0x12F] = "Metal Bars",
		[0x130] = "Harbour Gate", -- Galleon
		[0x131] = "K. Rool's Ship", -- Galleon
		[0x132] = "Metal Platform",
		[0x133] = "-",
		[0x134] = "Flame",
		[0x135] = "Flame",
		[0x136] = "Scoff n Troff platform",
		[0x137] = "Troff 'n' Scoff Banana Count Pad (DK)",
		[0x138] = "Torch",
		[0x139] = "-",
		[0x13A] = "-",
		[0x13B] = "-",
		[0x13C] = "Boss Key",
		[0x13D] = "Machine",
		[0x13E] = "Metal Door", -- Factory or Car Race - Production Room & Lobby - Unused?
		[0x13F] = "Metal Door", -- Factory or Car Race - Testing Dept. & Krem Storage
		[0x140] = "Metal Door", -- Factory or Car Race - R&D
		[0x141] = "Metal Door", -- Factory or Car Race - Testing Dept.
		[0x142] = "Piano Game", -- Factory, Lanky
		[0x143] = "Troff 'n' Scoff Banana Count Pad (Diddy)",
		[0x144] = "Troff 'n' Scoff Banana Count Pad (Lanky)",
		[0x145] = "Troff 'n' Scoff Banana Count Pad (Chunky)",
		[0x146] = "Troff 'n' Scoff Banana Count Pad (Tiny)",
		[0x147] = "Door 1342",
		[0x148] = "Door 3142",
		[0x149] = "Door 4231",
		[0x14A] = "1 Switch (Red)",
		[0x14B] = "2 Switch (Blue)",
		[0x14C] = "3 Switch (Orange)",
		[0x14D] = "4 Switch (Green)",
		[0x14E] = "-",
		[0x14F] = "Metal Archway",
		[0x150] = "Green Crystal thing",
		[0x151] = "Red Crystal thing",
		[0x152] = "Propeller",
		[0x153] = "Large Metal Bar",
		[0x154] = "Ray Sheild?",
		[0x155] = "-",
		[0x156] = "-",
		[0x157] = "-",
		[0x158] = "-",
		[0x159] = "Light",
		[0x15A] = "Target", -- Fungi/Castle minigames
		[0x15B] = "Ladder",
		[0x15C] = "Metal Bars",
		[0x15D] = "Red Feather",
		[0x15E] = "Grape",
		[0x15F] = "Pinapple",
		[0x160] = "Coconut",
		[0x161] = "Rope",
		[0x162] = "On Button",
		[0x163] = "Up Button",
		[0x164] = "Metal barrel or lid",
		[0x165] = "Simian Slam Switch (Chunky, Red)",
		[0x166] = "Simian Slam Switch (Diddy, Red)",
		[0x167] = "Simian Slam Switch (DK, Red)",
		[0x168] = "Simian Slam Switch (Lanky, Red)",
		[0x169] = "Simian Slam Switch (Tiny, Red)",
		[0x16A] = "Simian Slam Switch (Chunky, Blue)",
		[0x16B] = "Simian Slam Switch (Diddy, Blue)",
		[0x16C] = "Simian Slam Switch (DK, Blue)",
		[0x16D] = "Simian Slam Switch (Lanky, Blue)",
		[0x16E] = "Simian Slam Switch (Tiny, Blue)",
		[0x16F] = "Metal Grate", -- Lanky Attic
		[0x170] = "Pendulum", -- Fungi Clock
		[0x171] = "Weight", -- Fungi Clock
		[0x172] = "Door", -- Fungi Clock
		[0x173] = "Day Switch", -- Fungi Clock
		[0x174] = "Night Switch", -- Fungi Clock
		[0x175] = "Hands", -- Fungi Clock
		[0x176] = "Bell", -- (Minecart?)
		[0x177] = "Grate", -- (Minecart?)
		[0x178] = "Crystal", -- Red - No Hitbox (Minecart)
		[0x179] = "Crystal", -- Blue - No Hitbox (Minecart)
		[0x17A] = "Crystal", -- Green - No Hitbox (Minecart)
		[0x17B] = "Door", -- Fungi
		[0x17C] = "Gate", -- Fungi, angled
		[0x17D] = "Breakable Door", -- Fungi
		[0x17E] = "Night Gate", -- Fungi, angled
		[0x17F] = "Night Grate", -- Fungi
		--[0x180] = "Unknown", -- Internal name is "minecart"
		[0x181] = "Metal Grate", -- Fungi, breakable, well
		[0x182] = "Mill Pulley Mechanism", -- Fungi
		[0x183] = "Metal Bar", -- No Hitbox (Unknown Location)
		[0x184] = "Water Wheel", -- Fungi
		[0x185] = "Crusher", -- Fungi Mill
		[0x186] = "Coveyor Belt",
		[0x187] = "Night Gate",
		[0x188] = "Question Mark Box", -- Factory Lobby, probably other places too
		[0x189] = "Spider Web", -- Door
		[0x18A] = "Grey Croc Head", -- Minecart?
		[0x18B] = "Caution Sign (Falling Rocks)", -- Minecart
		[0x18C] = "Door", -- Minecart
		[0x18D] = "Battle Crown",
		[0x18E] = "-",
		[0x18F] = "-",
		[0x190] = "Dogadon Arena Background",
		[0x191] = "Skull Door (Small)", -- Minecart
		[0x192] = "Skull Door (Big)", -- Minecart
		[0x193] = "-",
		[0x194] = "Tombstone", -- RIP, Minecart
		[0x195] = "-",
		[0x196] = "DK Star", -- Baboon Blast
		[0x197] = "K. Rool's Throne",
		[0x198] = "Bean", -- Fungi
		[0x199] = "Power Beam", -- Helm (Lanky - BoM)
		[0x19A] = "Power Beam", -- Helm (Diddy - BoM)
		[0x19B] = "Power Beam", -- Helm (Tiny - Medal Room)
		[0x19C] = "Power Beam", -- Helm (Tiny - BoM)
		[0x19D] = "Power Beam", -- Helm (Chunky - Medal Room)
		[0x19E] = "Power Beam", -- Helm (Chunky - BoM)
		[0x19F] = "Power Beam", -- Helm (Lanky - Medal Room)
		[0x1A0] = "Power Beam", -- Helm (DK - Medal Room)
		[0x1A1] = "Power Beam", -- Helm (DK - BoM)
		[0x1A2] = "Power Beam", -- Helm (Diddy - Medal Room)
		[0x1A3] = "Warning Lights", -- Helm Wheel Room
		[0x1A4] = "K. Rool Door", -- Helm
		[0x1A5] = "Metal Grate",
		[0x1A6] = "Crown Door", -- Helm
		[0x1A7] = "Coin Door", -- Helm
		[0x1A8] = "Medal Barrier (DK)", -- Helm
		[0x1A9] = "Medal Barrier (Diddy)", -- Helm
		[0x1AA] = "Medal Barrier (Tiny)", -- Helm
		[0x1AB] = "Medal Barrier (Chunky)", -- Helm
		[0x1AC] = "Medal Barrier (Lanky)", -- Helm
		[0x1AD] = "I Door (Helm, DK)",
		[0x1AE] = "V Door (Helm, Diddy)",
		[0x1AF] = "III Door (Helm, Tiny)",
		[0x1B0] = "II Door (Helm, Chunky)",
		[0x1B1] = "IV Door (Helm, Lanky)",
		[0x1B2] = "Metal Door", -- Helm CS
		[0x1B3] = "Stone Wall", -- Helm
		[0x1B4] = "Pearl", -- Galleon
		[0x1B5] = "Small Door", -- Fungi
		[0x1B6] = "-",
		[0x1B7] = "Cloud", -- Castle, Fungi?
		[0x1B8] = "Warning Lights", -- Crusher/Grinder
		[0x1B9] = "Door", -- Fungi
		[0x1BA] = "Mushroom (Yellow)",
		[0x1BB] = "Mushroom (Purple)",
		[0x1BC] = "Mushroom (Blue)",
		[0x1BD] = "Mushroom (Green)",
		[0x1BE] = "Mushroom (Red)",
		[0x1BF] = "Mushroom Puzzle Instructions",
		[0x1C0] = "Face Puzzle Board", -- Fungi
		[0x1C1] = "Mushroom", -- Climbable, Fungi
		[0x1C2] = "Small Torch", -- Internal name "test", interestingly
		[0x1C3] = "DK Arcade Machine",
		[0x1C4] = "Simian Slam Switch (Any Kong?)", -- Mad Jack fight
		[0x1C5] = "Spotlight (Crown Arena?)",
		[0x1C6] = "Battle Crown Pad",
		[0x1C7] = "Seaweed",
		[0x1C8] = "Light", -- Galleon Lighthouse
		[0x1C9] = "Dust?",
		[0x1CA] = "Moon Trapdoor", -- Fungi
		[0x1CB] = "Ladder", -- Fungi
		[0x1CC] = "Mushroom Board", -- 5 gunswitches, Fungi
		[0x1CD] = "DK Star",
		[0x1CE] = "Wooden Box", -- Galleon?
		[0x1CF] = "Yellow CB Powerup", -- Multiplayer
		[0x1D0] = "Blue CB Powerup", -- Multiplayer
		[0x1D1] = "Coin Powerup?", -- Multiplayer, causes burp
		[0x1D2] = "DK Coin", -- Multiplayer?
		[0x1D3] = "Snide's Mechanism",
		[0x1D4] = "Snide's Mechanism",
		[0x1D5] = "Snide's Mechanism",
		[0x1D6] = "Snide's Mechanism",
		[0x1D7] = "Snide's Mechanism",
		[0x1D8] = "Snide's Mechanism",
		[0x1D9] = "Snide's Mechanism",
		[0x1DA] = "Snide's Mechanism",
		[0x1DB] = "Snide's Mechanism",
		[0x1DC] = "Snide's Mechanism",
		[0x1DD] = "Snide's Mechanism",
		[0x1DE] = "Blue Flowers", -- 2D
		[0x1DF] = "Plant (Green)", -- 2D
		[0x1E0] = "Plant (Brown)", -- 2D
		[0x1E1] = "Plant", -- 2D
		[0x1E2] = "Pink Flowers", -- 2D
		[0x1E3] = "Pink Flowers", -- 2D
		[0x1E4] = "Plant", -- 2D
		[0x1E5] = "Yellow Flowers", -- 2D
		[0x1E6] = "Yellow Flowers", -- 2D
		[0x1E7] = "Plant", -- 2D
		[0x1E8] = "Blue Flowers", -- 2D
		[0x1E9] = "Blue Flower", -- 2D
		[0x1EA] = "Plant", -- 2D
		[0x1EB] = "Plant", -- 2D
		[0x1EC] = "Red Flowers", -- 2D
		[0x1ED] = "Red Flower", -- 2D
		[0x1EE] = "Mushrooms (Small)", -- 2D
		[0x1EF] = "Mushrooms (Small)", -- 2D
		[0x1F0] = "Purple Flowers", -- 2D
		[0x1F1] = "Tree", -- Castle?
		[0x1F2] = "Cactus", -- Unused
		[0x1F3] = "Cactus", -- Unused
		[0x1F4] = "Ramp", -- Car Race?
		[0x1F5] = "Submerged Pot", -- Unused
		[0x1F6] = "Submerged Pot", -- Unused
		[0x1F7] = "Ladder", -- Fungi
		[0x1F8] = "Ladder", -- Fungi
		[0x1F9] = "Floor Texture?", -- Fungi
		[0x1FA] = "Iron Gate", -- Fungi
		[0x1FB] = "Day Gate", -- Fungi
		[0x1FC] = "Night Gate", -- Fungi
		[0x1FD] = "Cabin Door", -- Caves
		[0x1FE] = "Ice Wall (Breakable)", -- Caves
		[0x1FF] = "Igloo Door", -- Caves
		[0x200] = "Castle Top", -- Caves
		[0x201] = "Ice Dome", -- Caves
		[0x202] = "Boulder Pad", -- Caves
		[0x203] = "Target", -- Caves, Tiny 5DI
		[0x204] = "Metal Gate",
		[0x205] = "CB Bunch (Lanky)",
		[0x206] = "CB Bunch (Chunky)",
		[0x207] = "CB Bunch (Tiny)",
		[0x208] = "CB Bunch (Diddy)",
		[0x209] = "Blue Aura",
		[0x20A] = "Ice Maze", -- Caves
		[0x20B] = "Rotating Room", -- Caves
		[0x20C] = "Light + Barrier", -- Caves
		[0x20D] = "Light", -- Caves
		[0x20E] = "Trapdoor", -- Caves
		[0x20F] = "Large Wooden Door", -- Aztec, Llama Temple?
		[0x210] = "Warp 5 Pad",
		[0x211] = "Warp 3 Pad",
		[0x212] = "Warp 4 Pad",
		[0x213] = "Warp 2 Pad",
		[0x214] = "Warp 1 Pad",
		[0x215] = "Large Door", -- Castle
		[0x216] = "Library Door (Revolving?)", -- Castle
		[0x217] = "Blue Platform", -- Factory / K. Rool, Unused?
		[0x218] = "White Platform", -- Factory / K. Rool, Unused?
		[0x219] = "Wooden Platform", -- Castle
		[0x21A] = "Wooden Bridge", -- Castle
		[0x21B] = "Wooden Door", -- Castle
		[0x21C] = "Metal Grate", -- Castle Pipe
		[0x21D] = "Metal Door", -- Castle Greenhouse
		[0x21E] = "Large Metal Door", -- Castle?
		[0x21F] = "Rotating Chair", -- Castle
		[0x220] = "Baboon Balloon Pad (with platform)",
		[0x221] = "Large Aztec Door",
		[0x222] = "Large Aztec Door",
		[0x223] = "Large Wooden Door", -- Castle Tree
		[0x224] = "Large Breakable Wooden Door", -- Castle Tree
		[0x225] = "Pineapple Switch (Rotating)", -- Castle Tree
		[0x226] = ": Pad", -- Aztec Chunky Puzzle
		[0x227] = "Triangle Pad", -- Aztec Chunky Puzzle
		[0x228] = "+ Pad", -- Aztec Chunky Puzzle
		[0x229] = "Stone Monkey Head", -- Aztec
		[0x22A] = "Stone Monkey Head", -- Aztec
		[0x22B] = "Stone Monkey Head", -- Aztec
		[0x22C] = "Door", -- Caves Beetle Race
		[0x22D] = "Broken Ship Piece", -- Galleon
		[0x22E] = "Broken Ship Piece", -- Galleon
		[0x22F] = "Broken Ship Piece", -- Galleon
		[0x230] = "Flotsam", -- Galleon
		[0x231] = "Metal Grate", -- Factory, above crown pad
		[0x232] = "Treasure Chest", -- Galleon
		[0x233] = "Up Switch", -- Galleon
		[0x234] = "Down Switch",
		[0x235] = "DK Star", -- Caves
		[0x236] = "Enguarde Door", -- Galleon
		[0x237] = "Trash Can", -- Castle
		[0x238] = "Fluorescent Tube", -- Castle Toolshed?
		[0x239] = "Wooden Door Half", -- Castle
		[0x23A] = "Stone Platform", -- Aztec Lobby?
		[0x23B] = "Stone Panel", -- Aztec Lobby?
		[0x23C] = "Stone Panel (Rotating)", -- Aztec Lobby
		[0x23D] = "Wrinkly Door Wheel", -- Fungi Lobby
		[0x23E] = "Wooden Door", -- Fungi Lobby
		[0x23F] = "Wooden Panel", -- Fungi? Lobby?
		[0x240] = "Electricity Shields?", -- One for each kong, roughly in shape of Wrinkly Door wheel -- TODO: Unused?
		--[0x241] = "Unknown", -- Internal name is "torches"
		[0x242] = "Boulder Pad (Red)", -- Caves
		[0x243] = "Candelabra", -- Castle?
		[0x244] = "Banana Peel", -- Slippery
		[0x245] = "Skull+Candle", -- Castle?
		[0x246] = "Metal Box",
		[0x247] = "1 Switch",
		[0x248] = "2 Switch",
		[0x249] = "3 Switch",
		[0x24A] = "4 Switch",
		[0x24B] = "Metal Grate (Breakable?)",
		[0x24C] = "Pound The X Platform", -- DK Isles
		[0x24D] = "Wooden Door", -- Castle Shed
		[0x24E] = "Chandelier", -- Castle
		[0x24F] = "Bone Door", -- Castle
		[0x250] = "Metal Bars", -- Galleon
		[0x251] = "4 Door (5DS)",
		[0x252] = "5 Door (5DS)",
		[0x253] = "Door (Llama Temple)", -- Aztec
		[0x254] = "Coffin Door", -- Breakable?
		[0x255] = "Metal Bars",
		[0x256] = "Metal Grate", -- Galleon
		[0x257] = "-",
		[0x258] = "-",
		[0x259] = "-",
		[0x25A] = "-",
		[0x25B] = "-",
		[0x25C] = "-",
		[0x25D] = "-",
		[0x25E] = "-",
		[0x25F] = "-",
		[0x260] = "-",
		[0x261] = "-",
		[0x262] = "-",
		[0x263] = "-",
		[0x264] = "-",
		[0x265] = "-",
		[0x266] = "Boulder", -- DK Isles, covering cannon to Fungi
		[0x267] = "Boulder", -- DK Isles
		[0x268] = "K. Rool Ship Jaw Bottom", -- DK Isles
		[0x269] = "Blast-O-Matic Cover?", -- DK Isles
		[0x26A] = "Blast-O-Matic Cover", -- DK Isles
		[0x26B] = "Door", -- DK Isles, covering factory lobby, not solid
		[0x26C] = "Platform", -- DK Isles, up to Factory Lobby
		[0x26D] = "Propeller", -- K. Rool's Ship
		[0x26E] = "K. Rool's Ship", -- DK Isles, Intro Story
		[0x26F] = "Mad Jack Platform (White)",
		[0x270] = "Mad Jack Platform (White)", -- Factory
		[0x271] = "Mad Jack Platform (Blue)", -- Factory
		[0x272] = "Mad Jack Platform (Blue)", -- Factory
		[0x273] = "Skull Gate (Minecart)", -- 2D
		[0x274] = "Dogadon Arena Outer",
		[0x275] = "Boxing Ring Corner (Red)",
		[0x276] = "Boxing Ring Corner (Green)",
		[0x277] = "Boxing Ring Corner (Blue)",
		[0x278] = "Boxing Ring Corner (Yellow)",
		[0x279] = "Lightning Rod", -- Pufftoss Fight, DK Isles for some reason
		[0x27A] = "Green Electricity", -- Helm? Chunky BoM stuff?
		[0x27B] = "Blast-O-Matic",
		[0x27C] = "Target", -- K. Rool Fight (Diddy Phase)
		[0x27D] = "Spotlight", -- K. Rool Fight
		[0x27E] = "-",
		[0x27F] = "Vine", -- Unused?
		[0x280] = "Director's Chair", -- Blooper Ending
		[0x281] = "Spotlight", -- Blooper Ending
		[0x282] = "Spotlight", -- Blooper Ending
		[0x283] = "Boom Microphone", -- Blooper Ending
		[0x284] = "Auditions Sign", -- Blooper Ending
		[0x285] = "Banana Hoard",
		[0x286] = "Boulder", -- DK Isles, covering Caves lobby
		[0x287] = "Boulder", -- DK Isles, covering Japes lobby
		[0x288] = "Rareware GB",
		[0x289] = "-",
		[0x28A] = "-",
		[0x28B] = "-",
		[0x28C] = "-",
		[0x28D] = "Platform (Crystal Caves Minigame)", -- Tomato game
		[0x28E] = "King Kut Out Arm (Bloopers)",
		[0x28F] = "Rareware Coin", -- Not collectable?
		[0x290] = "Golden Banana", -- Not collectable?
		[0x291] = "-",
		[0x292] = "-",
		[0x293] = "-",
		[0x294] = "-",
		[0x295] = "-",
		[0x296] = "-",
		[0x297] = "-",
		[0x298] = "-",
		[0x299] = "-",
		[0x29A] = "-",
		[0x29B] = "-",
		[0x29C] = "-",
		[0x29D] = "-",
		[0x29E] = "-",
		[0x29F] = "-",
		[0x2A0] = "-",
		[0x2A1] = "-",
		[0x2A2] = "Rock", -- DK Isles, Covering Castle Cannon?
		[0x2A3] = "K. Rool's Ship", -- DK Isles, Entrance to final fight
		[0x2A4] = "-",
		[0x2A5] = "-",
		[0x2A6] = "-",
		[0x2A7] = "Wooden Door", -- BFI Guarding Rareware GB
		[0x2A8] = "-",
		[0x2A9] = "-",
		[0x2AA] = "-",
		[0x2AB] = "Nothing?",
		[0x2AC] = "Troff'n'Scoff Portal",
		[0x2AD] = "Level Entry/Exit",
		[0x2AE] = "K. Lumsy Key Indicator?",
		[0x2AF] = "-",
		[0x2B0] = "-",
		[0x2B1] = "-",
		[0x2B2] = "-",
		[0x2B3] = "-",
		[0x2B4] = "Red Bell", -- 2D, Minecart
		[0x2B5] = "Green Bell", -- 2D, Minecart
		[0x2B6] = "Race Checkpoint",
		-- Tested up to 0x2CF inclusive, all crashes so far
};

createFile();
writeToFile("{")
writeToFile("\"data\": [")
for k = 0, 215 do
	savestate.loadslot(3)
	local has_transition = false;
	local has_loaded = false;
	local has_written = false;
	local proceed = false;
	local focused_map = maps[k + 1] or "Unknown 0x"..bizstring.hex(k);
	print("Looking at Map #"..k.." ("..focused_map..")")
	while not proceed do
		mainmemory.write_u32_be(0x7444E4, k); -- Map
		mainmemory.write_u32_be(0x7444E8, 0); -- Loading Zone
		local modeltwotimer = mainmemory.read_u32_be(0x76A064);
		local start_frame = 0;
		local current_frame = emu.framecount();
		local load_limit = 600; -- 10s
		if modeltwotimer == 0 then
			if not has_transition then
				start_frame = emu.framecount();
			end
			has_transition = true;
		end
		if modeltwotimer > 0 and has_transition then
			has_loaded = true;
		end
		if current_frame > (start_frame + load_limit) then
			if start_frame > 0 then
				print("Hit Load Limit")
				if not has_written then
					printData();
				end
				has_written = true;
			end
		end
		if has_transition and has_loaded then
			if not has_written then
				printData();
			end
			has_written = true;
		end
		if has_transition and has_loaded and has_written then
			proceed = true;
		end
		emu.yield();
	end
	print("")
	if k % 10 == 0 then
		console.clear()
	end
end
writeToFile("]}");