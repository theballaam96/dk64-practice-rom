import math

inputs = [0x20080000,0x200804E7,0x0008C250,0x0008DD58,0x0008DDB4];

def convertStickToSigned(val):
	if val > 127:
		return val - 255;
	return val;

def convertInputs(input_seq):
	inversed_seq = [];
	for x in range(len(input_seq)):
		index = (len(input_seq) - 1) - x;
		stick_x = convertStickToSigned((input_seq[index] >> 8) & 0xFF);
		stick_y = convertStickToSigned(input_seq[index] & 0xFF);
		mag = math.pow(((stick_x * stick_x) + (stick_y * stick_y)),0.5);
		if (mag > 70):
			mag = 70;
		buttons_half = (input_seq[index] >> 16) & 0xFFFF;
		inversed_seq.append({
			"x": stick_x,
			"y": stick_y,
			"mag": mag,
			"buttons": {
				#"L": buttons_half & 0x0020 != 0,
				#"DU": buttons_half & 0x0800 != 0,
				#"DD": buttons_half & 0x0400 != 0,
				#"DL": buttons_half & 0x0200 != 0,
				#"DR": buttons_half & 0x0100 != 0,
				#"B": buttons_half & 0x4000 != 0,
				#"A": buttons_half & 0x8000 != 0,
				"Z": buttons_half & 0x2000 != 0,
				#"R": buttons_half & 0x0010 != 0,
				#"S": buttons_half & 0x1000 != 0,
				"CU": buttons_half & 0x0008 != 0,
				"CD": buttons_half & 0x0004 != 0,
				#"CL": buttons_half & 0x0002 != 0,
				#"CR": buttons_half & 0x0001 != 0,
			},
		})
	print(inversed_seq)
convertInputs(inputs)