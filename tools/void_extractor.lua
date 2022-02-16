print(
	"var void_bounds = {'x':["
	..mainmemory.read_s16_be(0x7F5FE4)
	..","
	..mainmemory.read_s16_be(0x7F5FE8)
	.."],'z':["
	..mainmemory.read_s16_be(0x7F5FE6)
	..","
	..mainmemory.read_s16_be(0x7F5FEA)
	.."]}"
)


addr = mainmemory.read_u32_be(0x7FFC8C) - 0x80000000;
stop = 0;
print("var void_data = [");
for i = 0, 511 do
	if stop == 0 then
		str = "{'x':[";
		for j = 0, 2 do
			str = str..mainmemory.read_s16_be(addr + (i * 0x10) + (j * 2));
			if j ~= 2 then
				str = str..",";
			end
		end
		str = str.."],'z':[";
		for j = 0, 2 do
			str = str..mainmemory.read_s16_be(addr + (i * 0x10) + 6 + (j * 2));
			if j ~= 2 then
				str = str..",";
			end
		end
		used = mainmemory.read_s32_be(addr + (i * 0x10) + 0xC);
		str = str.."],'used':"..used.."},";
		if used == 0 then
			stop = 1
		end
		print(str)
	end
end
print("]");