from actor_names import actor_names

shortened_names = []

def shorten_mini(s,_in,_out):
	s = s.strip();
	if len(s) < 16:
		return s
	else:
		return s.replace(_in,_out)

def shorten(s):
	s = shorten_mini(s,"?","")
	s = shorten_mini(s,"Controller","Ctrlr")
	s = shorten_mini(s,"Loading Zone","LZ")
	s = shorten_mini(s,"Object Model 2","OM2")
	s = shorten_mini(s,"Strong Kong","SKong")
	s = shorten_mini(s,"SKong","SK")
	s = shorten_mini(s,"Rocketbarrel","RBarrel")
	s = shorten_mini(s,"RBarrel","RB")
	s = shorten_mini(s,"Orangstand","OStand")
	s = shorten_mini(s,"OStand","OS")
	s = shorten_mini(s,"Mini Monkey","MMonkey")
	s = shorten_mini(s,"MMonkey","MM")
	s = shorten_mini(s,"Hunky Chunky","HChunky")
	s = shorten_mini(s,"HChunky","HC")
	s = shorten_mini(s,"Blueprint","BP")
	s = shorten_mini(s,"Diddy 5DI","5DI")
	s = shorten_mini(s,"Kremling Kosh","KKosh")
	s = shorten_mini(s,"Big Bug Bash","BBBash")
	s = shorten_mini(s,"Hideout Helm","Helm")
	s = shorten_mini(s,"Bad Hit Detection Man","Toy Monster")
	s = shorten_mini(s,"K. Rool","K Rool")
	s = shorten_mini(s,"K. Lumsy","K Lumsy")
	s = shorten_mini(s," Phase)",")")
	s = shorten_mini(s,"TNT Barrel","TNT")
	s = shorten_mini(s,"Unused - K Rool","Unused")
	s = shorten_mini(s,"King Kut Out","KKO")
	s = shorten_mini(s,"Banana Fairy","Fairy")
	s = shorten_mini(s,"End Sequence","End Seq")
	s = shorten_mini(s,"Training Barrel","TBarrel")
	s = shorten_mini(s,"Camera Focus Point","Camera Focus")
	s = shorten_mini(s,"CB Single","CB")
	s = shorten_mini(s,"Banana Barrel","Peel")
	s = shorten_mini(s,"Fireball (With Glasses)","Cool Fireball")
	s = shorten_mini(s,"OS Sprint","OSprint")
	s = shorten_mini(s,"Steel Keg","Keg")
	s = shorten_mini(s,"Rainbow Coin","Rainbow")
	s = shorten_mini(s,"Kritter-in-a-Sheet","Ghost Kremling")
	s = shorten_mini(s,"Tag Barrel (KKO)","Fake Tag Barrel")
	s = shorten_mini(s," (Boat)","")
	s = shorten_mini(s," Dialog","")
	s = shorten_mini(s,"Spider Silk String","Silk String")
	s = shorten_mini(s,"Mad Jack","MJ")
	s = shorten_mini(s,"Barrel (Main Menu)","Menu Barrel")
	s = shorten_mini(s,"Bonus Barrel (Helm)","Helm Bonus")
	s = shorten_mini(s,"with spotlight","w light")
	s = shorten_mini(s,"Multiplayer Model (Main Menu)","MPlayer Model")
	s = shorten_mini(s,"Battle Crown","Crown")
	s = shorten_mini(s,"Cannon (Seasick Chunky)","Seasick Cannon")
	s = shorten_mini(s,"Text Overlay","Text")
	s = shorten_mini(s,"(Dogadon)","(Dog)")
	s = shorten_mini(s,"(Projectile)","")
	s = shorten_mini(s,"Large Brown Bridge","Brown Bridge")
	s = shorten_mini(s," Slice","")
	s = shorten_mini(s,"Enguarde Crate (Unused)","Enguarde Crate")
	s = shorten_mini(s,"Padlock (K Lumsy)","K Lumsy Padlock")
	s = shorten_mini(s,"Retexturing","Retexture")
	s = shorten_mini(s,"Tag Barrel","Tag Brrl")
	s = shorten_mini(s,"Locked Kong (Tag Brrl)","Locked Kong")
	s = shorten_mini(s," (Instrument)","")
	s = shorten_mini(s,"Skeleton","Bones")
	s = shorten_mini(s,"Fire Spawner (Dog)","Fire Wall")
	s = shorten_mini(s,"TNT Spawner (Dog)","TNT Spawner")
	s = shorten_mini(s,"Fire Column Spawner","Fire Column")
	s = shorten_mini(s,"Fireball Spawner","Fire Spawner")
	s = shorten_mini(s,"Fire Breath Spawner","Fire Spawner")
	s = shorten_mini(s,"Fire Shockwave (Dog)","Dogadon Wave")
	return s

def replace_unknown(s):
	if "Unknown " in s:
		return "Unknown " + hex(int(s.split("Unknown ")[1]))
	else:
		return s

def swap(s,key):
	if key + " (" in s:
		return s.split(key + " (")[1].split(")")[0] + " " + key
	else:
		return s

def kong_formatting(s):
	if "Balloon" in s:
		return swap(s,"Balloon").strip()
	elif "Kasplat" in s:
		return swap(s,"Kasplat").strip()
	elif "Klaptrap" in s:
		return swap(s,"Klaptrap").strip()
	else:
		return s.strip()

error_count = 0;
for y in range(len(actor_names)):
	x = actor_names[y].strip()
	x = replace_unknown(x)
	x = kong_formatting(x)
	if len(x) < 16:
		shortened_names.append(x)
	else:
		x = shorten(x)
		if len(x) > 15:
			print("Too long: [" + hex(y) + "] " + x + " (" + str(len(x) - 15) + ")")
			shortened_names.append("LONG ERROR")
			error_count += 1
		else:
			shortened_names.append(x)

with open("assets/Non-Code/actor_names.bin","wb") as fh:
	for x in shortened_names:
		arr = []
		for y in range(16):
			arr.append(0)
		x = x.replace("'","^")
		x = x.replace("(","<")
		x = x.replace(")",">")
		x = x.replace("-"," ")
		x = x.replace("+","PLUS")
		x = x.replace(": ",":")
		x = x.replace(". ",".")
		x = x.replace("&","#")
		x = x.upper()
		for y in range(len(x)):
			arr[y] = ord(x[y])
		fh.write(bytearray(arr))