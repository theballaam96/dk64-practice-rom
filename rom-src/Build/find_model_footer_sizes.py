from ctypes import pointer
import zlib
import os

base_rom = "../rom/dk64.z64"
pointer_table_offset = 0x101C50

def assessModel(data,index):
    data_size = len(data)
    footer_length = 0
    temp_file = "temp.bin"
    with open(temp_file,"wb") as fg:
        fg.write(data)
    with open(temp_file,"rb") as fg:
        fg.seek(8)
        footer_pointer = int.from_bytes(fg.read(4),"big")
        fg.seek(0)
        start_pointer = int.from_bytes(fg.read(4),"big")
        footer_start = (footer_pointer - start_pointer) + 0x28
        footer_length = data_size - footer_start
    if os.path.exists(temp_file):
        os.remove(temp_file)
    return {
        "index": hex(index),
        "length": footer_length,
        "hex_length": hex(footer_length)
    }
        

def getModelFiles():
    with open(base_rom,"rb") as fh:
        fh.seek(pointer_table_offset + (5 * 0x4))
        model_table = pointer_table_offset + int.from_bytes(fh.read(4),"big")
        model_list = []
        for index in range(0xEC):
            fh.seek(model_table + (index * 4))
            model_start = pointer_table_offset + int.from_bytes(fh.read(4),"big")
            model_finish = pointer_table_offset + int.from_bytes(fh.read(4),"big")
            model_size = model_finish - model_start
            fh.seek(model_start)
            compress = fh.read(model_size)
            decompress = zlib.decompress(compress, (15+32))
            model_data = assessModel(decompress,index)
            model_list.append(model_data)
        new_list = sorted(model_list, key=lambda d: d['length'])
        for x in new_list:
            print(x)
        
getModelFiles()