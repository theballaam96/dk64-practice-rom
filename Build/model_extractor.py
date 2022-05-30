from ctypes import pointer
from inspect import trace
import json
from lib2to3.pytree import convert
from turtle import update
import zlib
import math
import os
import struct

pre = "" # Change to "../" if you want to run locally
rt = f"{pre}assets/Non-Code/Models/" # Modify to be your models directory
base_model = 0x7b # Cannon. The base model file that your new models will be transplanted onto (Not related to the file index it's saved at)

def extractBase():
    rom = f"{pre}rom/dk64.z64"
    pointer_table_offset = 0x101C50
    with open(rom,"rb") as fh:
        fh.seek(pointer_table_offset + (4 * 5))
        actor_geo_table = pointer_table_offset + int.from_bytes(fh.read(4),"big")
        fh.seek(actor_geo_table + (base_model * 4))
        base_start = pointer_table_offset + int.from_bytes(fh.read(4),"big")
        base_end = pointer_table_offset + int.from_bytes(fh.read(4),"big")
        size = base_end - base_start
        fh.seek(base_start)
        compress = fh.read(size)
        with open(f"{rt}base.bin","wb") as fg:
            dec = zlib.decompress(compress, 15+32)
            fg.write(dec)

def getStart(buffer_size):
    if buffer_size == 32:
        return 0x40
    return 0x10

def unsignedshorttosigned(us):
    if us > 32767:
        return -65536 + us
    return us

def signedtobytearray(num):
    sign_bit = 0x0
    if num < 0:
        num += 65536
        sign_bit = 0x80
    return [int(num / 256) | sign_bit, int(num % 256)]

def int_to_float(val):
    if val == 0:
        return 0
    return struct.unpack("!f", bytes.fromhex(hex(val).split("0x")[1]))[0]

def dumpModel(file):
    info_file = file.replace(".bin",".txt")
    with open(file,"r+b") as model:
        pointers = []
        for x in range(5):
            pointers.append(int.from_bytes(model.read(4),"big"))
        model.seek(0x1C)
        bounds = []
        for x in range(2):
            bounds.append(unsignedshorttosigned(int.from_bytes(model.read(2),"big")))
        footer_vert_count = int.from_bytes(model.read(1),"big")
        model.seek(0)
        header = model.read(0x28)
        vertex_info = (pointers[1]-pointers[0]) + 0x28
        model.seek(vertex_info)
        vertex_start = 0x28
        vertex_end = vertex_start + (int.from_bytes(model.read(4),"big")-pointers[0])
        vertex_count = int((vertex_end-vertex_start)/16)
        footer_start = model.tell() + 4
        footer = model.read()
        vertices = []
        for x in range(vertex_count):
            file_start = 0x28 + (16 * x)
            model.seek(file_start)
            vertex = {
                "index": x,
                "offset": hex(file_start)
            }
            params = ["x","y","z","control","u","v"]
            for param in params:
                vertex[param] = unsignedshorttosigned(int.from_bytes(model.read(2),"big"))
            params_rgba = ["r","g","b","a"]
            for colortype in params_rgba:
                vertex[colortype] = int.from_bytes(model.read(1),"big")
            vertices.append(vertex)
        dl_start = vertex_end
        dl_end = (pointers[1]-pointers[0])+0x28
        dl_count = int((dl_end-dl_start)/8)
        display_instructions = []
        for x in range(dl_count):
            model.seek(dl_start + (8 * x))
            dl_0 = hex(int.from_bytes(model.read(4),"big"))
            dl_1 = hex(int.from_bytes(model.read(4),"big"))
            display_instructions.append(f"{dl_0} {dl_1}")
        footer_data = []
        for x in range(footer_vert_count):
            model.seek(footer_start + (x * 0x10))
            c = []
            for y in range(3):
                c.append(int_to_float(int.from_bytes(model.read(4),"big")))
            i = []
            for y in range(3):
                i.append(int.from_bytes(model.read(1),"big"))
            footer_data.append({
                "index": x,
                "offset": hex(footer_start + (x * 0x10)),
                "coords": c.copy(),
                "verts": i.copy()
            })
            
        with open(info_file,"w") as info:
            info.write("POINTERS\n")
            for pointer in pointers:
                info.write(f"\t{hex(pointer)} ({hex(pointer + 0x28 - pointers[0])})\n")
            info.write("Y BOUNDS\n")
            for bound in bounds:
                info.write(f"\t{bound}\n")
            info.write("VERTICES\n")
            for vertex in vertices:
                info.write(f"\t{vertex['index']}: {vertex}\n")
            info.write("DISPLAY LIST\n")
            for dl in display_instructions:
                info.write(f"\t{dl}\n")
            info.write("FOOTER VERTS\n")
            for vert in footer_data:
                info.write(f"\t{vert['index']}: {vert}\n")
    header_bytes = []
    footer_bytes = []
    for x in header:
        header_bytes.append(x)
    for x in footer:
        footer_bytes.append(x)
    return {
        "header": header_bytes,
        "footer": footer_bytes,
        "pointers": pointers,
        "vertices": vertices,
        "display_list": display_instructions
    }

def convertListing(listing):
    pre_commands = []
    pre_lines = listing.split("\n")
    for line in pre_lines:
        if line.strip()[:1] != "#":
            if line.strip() != "":
                cmd = line.strip().split(" ")
                new_cmd = []
                for c in cmd:
                    c_str = f"0x{c}"
                    new_cmd.append(int(c_str,16))
                pre_commands.append(new_cmd)
    return pre_commands.copy()

def createModelFileFromBase(folder,base,obj_file,new_file,double_sided,translucent,dim0,dim1,dim2):
    print(f"Making {new_file}")
    base = folder + base
    obj_file = folder + obj_file
    new_file = folder + new_file
    model_info = dumpModel(base)
    with open(base.replace(".bin",".dump"),"w") as fh:
        json_pp = json.dumps(model_info, indent=4)
        fh.write(str(json_pp))
    vertex_list = []
    quads = []
    tri_count = 0
    poly_count = 0
    vert_count = 0
    with open(obj_file,"r") as obj:
        lines = obj.readlines()
        for line in lines:
            if line[:2] == "v ":
                # Is Vertex
                vertex_list.append(line[2:].replace("\n","").split(" "))
                vert_count += 1
            elif line[:2] == "f ":
                # Is Quad
                quad = line[2:].replace("\n","").split(" ")
                temp = []
                poly_vert_count = 0
                for q in quad:
                    if q != "":
                        poly_vert_count += 1
                        temp.append(int(q.split("/")[0])-1)
                if poly_vert_count > 1:
                    tri_count += (poly_vert_count - 2)
                quads.append(temp)
                poly_count += 1
    print(f"\t{tri_count} Tris")
    print(f"\t{poly_count} Polygons")
    print(f"\t{vert_count} Verts")
    translucent_f3dex2 = """
        E7 00 00 00 00 00 00 00
        E3 00 10 01 00 00 00 00
        D9 FF FB FF 00 00 00 00
        D9 FF FF FF 00 00 00 01
        D7 00 00 02 FF FF FF FF
        D9 F9 FF FF 00 00 00 00
        E7 00 00 00 00 00 00 00
        E2 00 00 1C 0C 18 49 D8
        E3 00 0A 01 00 10 00 00
        E3 00 0F 00 00 00 00 00
        E7 00 00 00 00 00 00 00
        FC 12 18 03 FF FF FF F8
        E7 00 00 00 00 00 00 00
        FD 18 00 00 00 00 02 70
        F5 18 00 00 07 01 40 50
        E6 00 00 00 00 00 00 00
        F3 00 00 00 07 3F F0 80
        E7 00 00 00 00 00 00 00
        F5 18 10 00 00 01 40 50
        F2 00 00 00 00 07 C0 7C
        E7 00 00 00 00 00 00 00
        E3 00 10 01 00 00 00 00
        DA 38 00 03 04 00 00 40
    """
    single_sided = """
        E7 00 00 00 00 00 00 00
        E3 00 0A 01 00 00 00 00
        E2 00 00 1C 00 55 20 78
        FC 12 18 83 FF 2F FF FF
        D7 00 00 02 FF FF FF FF
        E3 00 0D 01 00 00 00 00
        E3 00 12 01 00 00 20 00
        D9 FF FF FF 00 00 04 00
        DA 38 00 03 04 00 00 40
    """
    double_sided_f3dex2 = """
        E7 00 00 00 00 00 00 00
        E3 00 0A 01 00 01 00 00
        E2 00 00 1C 00 55 20 78
        FC 12 18 83 FF 2F FF FF
        D7 00 00 02 FF FF FF FF
        E3 00 0D 01 00 00 00 00
        E3 00 12 01 00 00 20 00
        D9 FF FF FF 00 00 04 00
        DA 38 00 03 04 00 00 40
    """
    double_sided_back = """
        E7 00 00 00 00 00 00 00
        E3 00 0A 01 00 01 00 00
        E2 00 00 1C 00 55 20 78
        FC 12 18 83 FF 2F FF FF
        D7 00 00 02 FF FF FF FF
        E3 00 0D 01 00 00 00 00
        E3 00 12 01 00 00 20 00
        D9 FF FF FF 00 00 04 00
        DA 38 00 03 04 00 00 40
    """
    if translucent:
        pre_listing = translucent_f3dex2
    else:
        if double_sided:
            pre_listing = double_sided_f3dex2
        else:
            pre_listing = single_sided
    # Original geo mode command: D9 FF FF FF 00 00 04 00
    # Remove Z buffer Geo: D9 FF FF FE 00 00 04 00
    pre_commands = convertListing(pre_listing)
    if translucent:
        double_command = convertListing(translucent_f3dex2)
    else:
        double_command = convertListing(double_sided_back)
    mid_commands = []
    end_commands = [
        [0xDF,0x00,0x00,0x00,0x00,0x00,0x00,0x00]
    ]
    rgba = [0xFF,0xFF,0xFF,0x80]
    gen_type = "grouped" # Types "grouped" and "glorious"
    with open(new_file,"wb") as fh:
        fh.write(bytes(model_info["header"]))
        if len(vertex_list) < 33 and not double_sided:
            # Regular Assignment
            for vertex in vertex_list:
                coords = []
                scale_factor = 1
                coords.append(int(float(vertex[0]) * scale_factor))
                coords.append(int(float(vertex[1]) * scale_factor))
                coords.append(int(float(vertex[2]) * scale_factor))
                texs = []
                texs.append(0)
                texs.append(0)
                for coord in coords:
                    fh.write(bytearray(signedtobytearray(coord)))
                fh.write(bytearray([0,0]))
                for tex in texs:
                    fh.write(tex.to_bytes(2,"big"))
                for color_channel in rgba:
                    fh.write(color_channel.to_bytes(1,"big"))
            vert_end = fh.tell()
            for command in pre_commands:
                fh.write(bytearray(command))
            segments = math.ceil(len(vertex_list)/32)
            for segment in range(segments):
                segment_start = 32 * segment
                buffer_size = min(32,len(vertex_list)-segment_start)
                buffer_upper = buffer_size >> 4
                buffer_lower = (buffer_size << 4) & 0xFF
                start = getStart(buffer_size)
                fh.write(bytearray([0x01,buffer_upper,buffer_lower,start,0x03,0x00,2*segment,0x00]))
                for quad in quads:
                    if len(quad) == 4:
                        fh.write(bytearray([0x06,int(quad[0])*2,int(quad[1])*2,int(quad[2])*2,0x00,int(quad[0])*2,int(quad[2])*2,int(quad[3])*2]))
                    elif len(quad) == 3:
                        fh.write(bytearray([0x05,int(quad[0])*2,int(quad[1])*2,int(quad[2])*2,0x00,0x00,0x00,0x00]))
                if segments - 1 > segment:
                    for command in mid_commands:
                        fh.write(bytearray(command))
                if segment == segments - 1:
                    for command in end_commands:
                        fh.write(bytearray(command))
        else:
            # More than 32 vertices, needing another algorithm to handle this
            if gen_type == "grouped":
                # Grouped Assignment
                vertex_copy = vertex_list.copy()
                quad_copy = quads.copy()
                used_quads = []
                unused_quads = quad_copy.copy()
                vertex_list_new = []
                vertex_grouping = []
                quad_grouping = []
                # Assign Quads and Verts into groups where the vertex list for a group does not exceed 32 elements (max verts that can be stored in a buffer)
                while True:
                    if len(unused_quads) == 0:
                        break
                    vertex_safe_group = []
                    vertex_test_group = []
                    quad_sub_grouping = []
                    for quad_set in quad_copy:
                        if quad_set in unused_quads:
                            for q in quad_set:
                                vert_index = q
                                if vert_index not in vertex_test_group:
                                    vertex_test_group.append(vert_index)
                            if len(vertex_test_group) < 33:
                                vertex_safe_group = vertex_test_group.copy()
                                used_quads.append(quad_set)
                                quad_sub_grouping.append(quad_set)
                                unused_quads.remove(quad_set)
                            vertex_test_group = vertex_safe_group.copy()
                    vertex_list_new.extend(vertex_safe_group)
                    vertex_grouping.append(vertex_safe_group)
                    quad_grouping.append(quad_sub_grouping)
                # Fix Quad list to link properly with new vertex ordering
                updated_quads = []
                for group_index in range(len(quad_grouping)):
                    focused_quad_group = quad_grouping[group_index]
                    focused_vert_group = vertex_grouping[group_index]
                    updated_quad_indexes = []
                    for quad in focused_quad_group:
                        new_quad = []
                        for q in quad:
                            new_quad.append(focused_vert_group.index(q))
                        updated_quad_indexes.append(new_quad)
                    updated_quads.append(updated_quad_indexes)
                # Write Vertex List
                vertex_list = []
                for vert_group in vertex_grouping:
                    for vert_index in vert_group:
                        vertex_list.append(vertex_copy[vert_index])
                # Write Vertices to File
                for vertex in vertex_list:
                    coords = []
                    scale_factor = 1
                    coords.append(int(float(vertex[0]) * scale_factor))
                    coords.append(int(float(vertex[1]) * scale_factor))
                    coords.append(int(float(vertex[2]) * scale_factor))
                    texs = []
                    texs.append(0)
                    texs.append(0)
                    for coord in coords:
                        fh.write(bytearray(signedtobytearray(coord)))
                    fh.write(bytearray([0,0]))
                    for tex in texs:
                        fh.write(tex.to_bytes(2,"big"))
                    for color_channel in rgba:
                        fh.write(color_channel.to_bytes(1,"big"))
                vert_end = fh.tell()
                for command in pre_commands:
                    fh.write(bytearray(command))
                lim = 1
                if double_sided:
                    lim = 2
                for l in range(lim):
                    if l == 1:
                        for command in double_command:
                            fh.write(bytearray(command))
                    position = 0
                    for quad_group_index in range(len(updated_quads)):
                        quad_group = updated_quads[quad_group_index]
                        vert_group = vertex_grouping[quad_group_index]
                        buffer_size = len(vert_group)
                        buffer_upper = buffer_size >> 4
                        buffer_lower = (buffer_size << 4) & 0xFF
                        position_arr = signedtobytearray(position * 0x10)
                        # start = getStart(buffer_size)
                        start = buffer_size * 2
                        if quad_group_index != 0:
                            for command in mid_commands:
                                fh.write(bytearray(command))
                        fh.write(bytearray([0x01,buffer_upper,buffer_lower,start,0x03,0x00,position_arr[0],position_arr[1]]))
                        for quad in quad_group:
                            if l == 1:
                                quad.reverse()
                            if len(quad) == 4:
                                fh.write(bytearray([0x06,int(quad[0])*2,int(quad[1])*2,int(quad[2])*2,0x00,int(quad[0])*2,int(quad[2])*2,int(quad[3])*2]))
                            elif len(quad) == 3:
                                fh.write(bytearray([0x05,int(quad[0])*2,int(quad[1])*2,int(quad[2])*2,0x00,0x00,0x00,0x00]))
                        position += buffer_size
                for command in end_commands:
                    fh.write(bytearray(command))
            elif gen_type == "glorious":
                # Glorious's Algorithm
                print("Unsupported")
                # for vertex in vertex_list:
                #     coords = []
                #     scale_factor = 1
                #     coords.append(int(float(vertex[0]) * scale_factor))
                #     coords.append(int(float(vertex[1]) * scale_factor))
                #     coords.append(int(float(vertex[2]) * scale_factor))
                #     texs = []
                #     texs.append(0)
                #     texs.append(0)
                #     for coord in coords:
                #         fh.write(bytearray(signedtobytearray(coord)))
                #     fh.write(bytearray([0,0]))
                #     for tex in texs:
                #         fh.write(tex.to_bytes(2,"big"))
                #     for color_channel in rgba:
                #         fh.write(color_channel.to_bytes(1,"big"))
                # vert_end = fh.tell()
                # for command in pre_commands:
                #     fh.write(bytearray(command))
                # buffer_chunk = -1
                # for quad in quads:
                #     base_val = int(quad[0] / 32)
                #     accept_buffer = True
                #     for q in quad:
                #         if base_val != int(q/32):
                #             accept_buffer = False
                #     if accept_buffer:
                #         # All in same block of 32
                #         if buffer_chunk != base_val:
                #             buffer_chunk = base_val
                #             segmented_addr = (buffer_chunk * 32 * 16) & 0xFFFFFF
                #             fh.write(bytearray([0x01,0x02,0x00,0x04,0x03]))
                #             fh.write(segmented_addr.to_bytes(3,"big"))
                #             if len(quad) == 4:
                #                 fh.write(bytearray([0x06,(int(quad[0])*2)%64,(int(quad[1])*2)%64,(int(quad[2])*2)%64,0x00,(int(quad[0])*2)%64,(int(quad[2])*2)%64,(int(quad[3])*2)%64]))
                #             elif len(quad) == 3:
                #                 fh.write(bytearray([0x05,(int(quad[0])*2)%64,(int(quad[1])*2)%64,(int(quad[2])*2)%64,0x00,0x00,0x00,0x00]))
                #     else:
                #         # Exception
                #         segmented_addr_list = []
                #         for q in quad:
                #             segmented_addr_list.append((q * 16) & 0xFFFFFF)
                #         for x in range(len(quad)):
                #             fh.write(bytearray([0x01,0x00,0x10,x*2,0x03]))
                #             fh.write(segmented_addr_list[x].to_bytes(3,"big"))
                #         if len(quad) == 4:
                #             fh.write(bytearray([0x06,0x00,0x02,0x04,0x00,0x00,0x04,0x06]))
                #         else:
                #             fh.write(bytearray([0x05,0x00,0x02,0x04,0x00,0x00,0x00,0x00]))
                #         buffer_chunk = -1
                # for command in end_commands:
                #     fh.write(bytearray(command))

        dl_end = fh.tell()
        fh.seek(4)
        dl_end_pointer = model_info["pointers"][0] + dl_end - 0x28
        fh.write(dl_end_pointer.to_bytes(4,"big"))
        fh.seek(8)
        footer_pointer = dl_end_pointer + (model_info["pointers"][2]-model_info["pointers"][1])
        fh.write(footer_pointer.to_bytes(4,"big"))
        fh.seek(0xC)
        footer_pointer_0 = dl_end_pointer + (model_info["pointers"][3]-model_info["pointers"][1])
        fh.write(footer_pointer_0.to_bytes(4,"big"))
        fh.seek(dl_end)
        vert_end_pointer = model_info["pointers"][0] + vert_end - 0x28
        fh.write(vert_end_pointer.to_bytes(4,"big"))
        fh.write(bytes(model_info["footer"]))
        file_end = fh.tell() - 4
        file_end_pointer = model_info["pointers"][0] + file_end - 0x28
        fh.seek(0x10)
        fh.write(file_end_pointer.to_bytes(4,"big"))
        fh.seek(0x1C)
        fh.write(bytearray(signedtobytearray(dim0)))
        fh.seek(0x1E)
        fh.write(bytearray(signedtobytearray(dim1)))
        # fh.seek(0x20)
        # fh.write(bytearray(signedtobytearray(dim2)))
    #dumpModel(new_file)

extractBase()
model_list = ["cube","cylinder","sphere"]
for model in model_list:
    suf_idx = 0
    for suf in ["","_simple"]:
        createModelFileFromBase(
            rt,
            "base.bin",
            f"{model}/{model}.obj",
            f"{model}{suf}.bin",
            False,
            suf_idx == 0,
            -83,
            198,
            0x0601,
        )
        suf_idx += 1
cleanup = [
    "base.bin",
    "base.dump",
    "base.txt"
]
for item in cleanup:
    sub_item = f"{rt}{item}"
    if os.path.exists(sub_item):
        os.remove(sub_item)
