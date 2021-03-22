#!/usr/bin/env python3
import sys
from PIL import Image, ImageDraw

im = Image.open(sys.argv[1])
w = im.width
h = im.height
minx = h/2
maxx = h/2
miny = w/2
maxy = w/2
for x in range(h):
	for y in range(w):
		px = im.getpixel((x, y))
		if px < 255: # TODO: better metric
			minx = min(minx, x)
			maxx = max(maxx, x)
			miny = min(miny, y)
			maxy = max(maxy, y)
	
new_dimen = max(maxy-miny, maxx-minx)
r = new_dimen//2
im = im.crop((w//2 - r, h//2 - r, w//2 + r, h//2 + r))
im = im.resize((17, 17))

im = im.quantize(2)

draw = ImageDraw.Draw(im)
draw.line((0, 8, 17, 8), fill=127)
draw.line((5, 0, 5, 17), fill=127)
draw.line((11, 0, 11, 17), fill=127)

im.save("out_" + sys.argv[1], "PNG")

chars = []

for y in [0, 9]:
	for x in [0, 6, 12]:
		char = []
		for yy in range(y, y+8):
			scanline = 0
			for xx in range(x, x+5):
				px = im.getpixel((xx, yy))
				if px == 127:
					print(f"got 127 at {xx}, {yy}")
					sys.exit(1)
				scanline = (scanline << 1) + px
			char.append(scanline)
		chars.append(char)


fname = sys.argv[1].replace(".png", "")
for i in range(6):
	for ii in range(8):
		s = f"\tlogos[{fname}][{i}][{ii}] = {chars[i][ii]};";
		print(s)

