for i = 0, 512 do
	print("#"..bizstring.hex(mainmemory.readbyte(0x33624 + i)).."#,");
	if (0x33624 + i) == 0x33724 then
		print("Addr was last readout, offset "..i)
	end
end