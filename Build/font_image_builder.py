import subprocess
import os

fonts = [
	{
		"font_key": "arcade_font",
		"overall_width": 512,
		"images": [
			{
				"img": "arcade/colon.png",
				"x": 248,
				"w": 8,
			},
			{
				"img": "arcade/ampersand.png",
				"x": 392,
				"w": 8,
			},
			{
				"img": "arcade/apostrophe.png",
				"x": 416,
				"w": 8,
			},
			{
				"img": "arcade/percent.png",
				"x": 400,
				"w": 8,
			},
			{
				"img": "arcade/roman_1.png",
				"x": 232,
				"w": 8,
			},
			{
				"img": "arcade/roman_2.png",
				"x": 240,
				"w": 8,
			}
		]
	}
];

codecs_8 = ["ia8","i8"]
codecs_4 = ["ia4","i4"]

def build_font(extract,codec,key):
	temp_font = [];
	codec_size = 0;
	if codec in codecs_8:
		codec_size = 8;
	elif codec in codecs_4:
		codec_size = 4;
	if codec_size == 4 or codec_size == 8:
		with open(extract,"r+b") as ex:
			for font in fonts:
				if font["font_key"] == key:
					for i in font["images"]:
						rt_str = "";
						rt = extract.split("/")
						for t in range(len(rt)):
							if (t + 1) != len(rt):
								rt_str += rt[t] + "/"
						new = rt_str + i["img"]
						new_codec = new.replace(".png","." + codec)
						temp_font.append({
							"img": new,
							"x": i["x"],
							"w": i["w"],
						})
						result = subprocess.check_output(["./build/n64tex.exe", codec, new])
						with open(new_codec,"r+b") as ch:
							character_length = len(ch.read());
							hw = character_length * (8 / codec_size);
							for index in range(character_length):
								ch.seek(index);
								byte_val = int.from_bytes(ch.read(1),"big");
								for index2 in range(int(8 / codec_size)):
									w_offset = int((index * (8 / codec_size)) % i["w"])
									h_offset = int(((index * (8 / codec_size)) - w_offset) / i["w"]);
									offset = ((i["x"] + w_offset) + (font["overall_width"] * h_offset) + index2) / (8 / codec_size);
									_offset = int(offset - (offset % 1));
									if codec_size == 4:
										if index2:
											read_val = (byte_val & 0xF0) >> 4
										else:
											read_val = byte_val & 0xF;
									else:
										read_val = byte_val;
									if codec_size == 4:
										if (offset % 1) == 0.5:
											ex.seek(_offset)
											old_byte = int.from_bytes(ex.read(1),"big")
											ex.seek(_offset)
											ex.write(bytearray([((read_val & 0xF) << 4) | (old_byte & 0xF)]))
										else:
											ex.seek(_offset)
											old_byte = int.from_bytes(ex.read(1),"big")
											ex.seek(_offset)
											ex.write(bytearray([(read_val & 0xF) | (old_byte & 0xF0)]))
									else:
										ex.seek(_offset)
										ex.write(bytearray([read_val]))
						if os.path.exists(new_codec):
							os.remove(new_codec)