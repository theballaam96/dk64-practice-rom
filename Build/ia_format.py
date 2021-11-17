from PIL import Image
import math

def getNewFileName(f,iatype):
	return ".".join(f.split(".")[0:-1]) + "." + iatype

def getIntensity(px,x,y,intensity_cap,alpha_cap,alpha_correction):
	rgba = px[x,y]
	c = 0;
	for i in range(3):
		c += rgba[i] * (intensity_cap / 255)
	c = math.floor((c / 3))
	a = math.floor(((rgba[3] * alpha_cap)/255) + 0.5)
	if a == 0 and alpha_correction:
		c = 0
	return int(c & intensity_cap), int(a & alpha_cap)

def getImg(f):
	im = Image.open(f)
	return im, im.load(), im.size[0], im.size[1]

def to_ia4(f):
	im, pix, width, height = getImg(f);
	byte = 0;
	is_upper = 1;
	with open(getNewFileName(f,"ia4"),"wb") as ia4:
		for y in range(height):
			for x in range(width):
				c, a = getIntensity(pix,x,y,7,1,True)
				convert = ((c & 7) << 1) + (a & 1)
				if is_upper > 0:
					byte = convert << 4
				else:
					byte += convert
					ia4.write(bytearray([byte]))
				is_upper = 1 - is_upper;

def to_ia8(f):
	im, pix, width, height = getImg(f);
	with open(getNewFileName(f,"ia8"),"wb") as ia8:
		for y in range(height):
			for x in range(width):
				c, a = getIntensity(pix,x,y,15,15,True);
				convert = ((c % 15) << 4) + (a % 15)
				ia8.write(bytearray([convert]))
	#print(pix[,0])

def to_i8(f):
	im, pix, width, height = getImg(f);
	with open(getNewFileName(f,"i8"),"wb") as i8:
		for y in range(height):
			for x in range(width):
				c, a = getIntensity(pix,x,y,255,255,False);
				convert = c;
				i8.write(bytearray([convert]))

def to_i4(f):
	im, pix, width, height = getImg(f);
	byte = 0;
	is_upper = 1;
	with open(getNewFileName(f,"ia4"),"wb") as ia4:
		for y in range(height):
			for x in range(width):
				c, a = getIntensity(pix,x,y,16,16,False)
				convert = c;
				if is_upper > 0:
					byte = convert << 4
				else:
					byte += convert
					ia4.write(bytearray([byte]))
				is_upper = 1 - is_upper;