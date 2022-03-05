"""Encode text file to ROM."""
from getVersion import getVersion
rom_version = getVersion();

def writeText(file_name, text):
    """Write the text to ROM."""
    with open(file_name, "wb") as fh:
        fh.write(bytearray([len(text)]))
        position = 0
        for textbox in text:
            fh.write(bytearray([1, 1, len(textbox)]))
            for string in textbox:
                fh.write(position.to_bytes(4, "big"))
                fh.write(len(string).to_bytes(2, "big"))
                fh.write(bytearray([0, 0]))
                position += len(string)
            fh.write(bytearray([0, 0, 0, 0]))
        fh.write(bytearray(position.to_bytes(2,"big")))
        for textbox in text:
            for string in textbox:
                if rom_version < 2:
                    fh.write(string.encode("ascii"))
                else:
                    index = 0;
                    for x in string.encode("ascii"):
                        if x >= 0x30:
                            fh.write(bytearray([x-0x17]))
                        elif x == 0x20:
                            fh.write(bytearray([0xF]))
                        elif x == 0 and index == 0:
                            fh.write(bytearray([0x10]))
                        else:
                            fh.write(bytearray([x]))
                        x += 1