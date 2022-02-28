
def patchStaticCode(filename):
	jump_data_start = 0x1FFF000
	with open("rom/dk64-practice-rom-temp.z64", "rb") as fg:
		fg.seek(jump_data_start + 0x00)
		patch_gktimer_hook = fg.read(8)
		fg.seek(jump_data_start + 0x8)
		patch_lag_hook = fg.read(0x8)
		fg.seek(jump_data_start + 0x10)
		patch_save_hook = fg.read(0x8)
		fg.seek(jump_data_start + 0x18)
		patch_sprite_hook = fg.read(0x8)
		fg.seek(jump_data_start + 0x20)
		patch_speed_hook = fg.read(0x8)
	with open(filename, "r+b") as fh:
		# RDRAM Address - 0x5FB300 = ROM address
		# GK Timer Hook
		fh.seek(0x4AD74)
		fh.write(patch_gktimer_hook)
		# Lag Hook
		fh.seek(0x5374)
		fh.write(patch_lag_hook)
		# Save Hook
		fh.seek(0x12BCC)
		fh.write(patch_save_hook)
		# Sprite Hook
		fh.seek(0xB04D0)
		fh.write(patch_sprite_hook)
		# Speed hook
		fh.seek(0x6A054)
		fh.write(patch_speed_hook)