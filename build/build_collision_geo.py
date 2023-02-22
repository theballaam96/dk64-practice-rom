import zlib
import os
import math
import sys
import json

data_tables = ["geometry", "walls", "floors"]

pointer_table_offset = 0x101C50

rom_name = "rom/dk64.z64"
temp_name = "temp.bin"
geo_temp = "geo_temp.bin"

double_render = False

def readS16(raw: int) -> int:
    if raw > 32767:
        return raw - 65536
    return raw

def getFile(table_name: str, map_index: int, starting_verts: list = []):
    if table_name in ("floors","walls"):
        getFile("geometry", map_index)
        with open(temp_name, "rb") as fh:
            with open(geo_temp, "wb") as fg:
                fg.write(fh.read())
    with open(rom_name,"rb") as rom:
        table_index = data_tables.index(table_name) + 1
        rom.seek(pointer_table_offset + (table_index * 4))
        table_start = pointer_table_offset + int.from_bytes(rom.read(4), "big")
        rom.seek(table_start + (map_index * 4))
        file_start = pointer_table_offset + (int.from_bytes(rom.read(4), "big") & 0x7FFFFFFF)
        file_end = pointer_table_offset + (int.from_bytes(rom.read(4), "big") & 0x7FFFFFFF)
        file_size = file_end - file_start
        rom.seek(file_start)
        indic = int.from_bytes(rom.read(2), "big")
        rom.seek(file_start)
        data = rom.read(file_size)
        if indic == 0x1F8B:
            data = zlib.decompress(data, (15+32))
        with open(temp_name, "wb") as fh:
            fh.write(data)
        with open(temp_name, "rb") as fh:
            if table_name in ("floors","walls"):
                floor_count = 0
                with open(geo_temp, "rb") as fg:
                    if table_name == "floors":
                        fg.seek(0x18)
                    else:
                        fg.seek(0x10)
                    dim0 = int.from_bytes(fg.read(2), "big")
                    dim1 = int.from_bytes(fg.read(2), "big")
                    floor_count = dim0 * dim1
                start = 8
                floor_data = []
                vert_list = starting_verts
                for floor_index in range(floor_count):
                    fh.seek(start - 4)
                    end = int.from_bytes(fh.read(4), "big")
                    count = int((end - start) / 0x18)
                    for i in range(count):
                        tri_data = {}
                        if table_name == "floors":
                            for attr in ("x","y","z"):
                                attr_data = []
                                for node in range(3):
                                    attr_data.append(int(readS16(int.from_bytes(fh.read(2), "big")) / 6))
                                tri_data[attr] = attr_data.copy()
                        else:
                            for node in range(3):
                                for attr in ("x", "y", "z"):
                                    val = readS16(int.from_bytes(fh.read(2), "big"))
                                    if attr in tri_data:
                                        tri_data[attr].append(val)
                                    else:
                                        tri_data[attr] = [val]
                        verts_in_tri = []
                        for j in range(3):
                            ref_node = (tri_data["x"][j], tri_data["y"][j], tri_data["z"][j])
                            if ref_node not in vert_list:
                                vert_list.append(ref_node)
                            verts_in_tri.append(vert_list.index(ref_node))
                        tri_data = {
                            "verts": verts_in_tri.copy()
                        }
                        tri_data["props"] = int.from_bytes(fh.read(2), "big")
                        tri_data["sfx"] = int.from_bytes(fh.read(2), "big")
                        tri_data["brightness"] = int.from_bytes(fh.read(1), "big")
                        tri_data["unk17"] = int.from_bytes(fh.read(1), "big")
                        if table_name == "walls":
                            tri_data["color"] = [0x00,0x00,0x80]
                        else:
                            # Floors
                            tri_data["color"] = [0x80,0x00,0x00]
                        floor_data.append(tri_data)
                    start = end + 4
                # print(floor_data)
                # print(vert_list)
                return (floor_data, vert_list)

starting_dl = (
    (0xE7000000, 0x00000000),
    (0xE3000A01, 0x00100000),
    (0xE200001C, 0x00552078),
    (0xFC41FE83, 0xFFFFF9FC),
    (0xD7000002, 0xFFFFFFFF),
    (0xE3000D01, 0x00000000),
    (0xE3001201, 0x00002000),
    (0xD9FFFFFF, 0x00000401),
)

joining_dl = (
    (0xE7000000, 0x00000000),
    (0xE200001C, 0x005049D8),
    (0xD9FFF9FF, 0x00000401),
)

ending_dl = (
    (0xDF000000, 0x00000000),
)

def concatGeoFiles(files: list):
    vert_count = 0
    dl = []
    verts = []
    bounds = [0] * 6
    for fi, f in enumerate(files):
        with open(f, "rb") as fh:
            # Recalculate Bounds
            fh.seek(0x118)
            if fi == 0:
                for x in range(6):
                    val = int.from_bytes(fh.read(2), "big")
                    if val > 32767:
                        val -= 65536
                    bounds[x] = val
            else:
                for x in range(6):
                    val = int.from_bytes(fh.read(2), "big")
                    if val > 32767:
                        val -= 65536
                    if x < 3:
                        if val < bounds[x]:
                            bounds[x] = val
                    else:
                        if val > bounds[x]:
                            bounds[x] = val
            # Get Verts
            fh.seek(0x38)
            vert_start = int.from_bytes(fh.read(4), "big")
            fh.seek(0x40)
            vert_end = int.from_bytes(fh.read(4), "big")
            vert_size = vert_end - vert_start
            fh.seek(vert_start)
            verts.append(fh.read(vert_size))
            # Display List
            fh.seek(0x34)
            dl_start = int.from_bytes(fh.read(4), "big")
            dl_size = vert_start - dl_start
            fh.seek(dl_start)
            dl_started = False
            start_index = 0
            while not dl_started:
                fh.seek(dl_start + (8 * start_index))
                dl_started = int.from_bytes(fh.read(1), "big") != 0
                if not dl_started:
                    start_index += 1
                    dl_size -= 8
            fh.seek(dl_start + (8 * start_index))
            with open(temp_name, "wb") as fg:
                fg.write(fh.read(dl_size))
            # Update DL to align with shift
            with open(temp_name, "r+b") as fg:
                for x in range(int(dl_size / 8)):
                    fg.seek(x * 8)
                    command = int.from_bytes(fg.read(1), "big")
                    if command == 1:
                        fg.seek((x * 8) + 4)
                        address = int.from_bytes(fg.read(4), "big")
                        address += (vert_count * 0x10)
                        fg.seek((x * 8) + 4)
                        fg.write(address.to_bytes(4, "big"))
                fg.seek(0)
                dl.append(fg.read())
            vert_count = int(vert_size / 0x10)
    with open(files[0], "rb") as fh:
        with open(temp_name, "w+b") as fg:
            fh.seek(0x34)
            dl_start = int.from_bytes(fh.read(4), "big")
            fh.seek(0)
            fg.write(fh.read(dl_start))
            dl_size = 0
            dl_started = False
            start_index = 0
            while not dl_started:
                fh.seek(dl_start + (start_index * 8))
                dl_started = int.from_bytes(fh.read(1), "big") != 0
                if not dl_started:
                    fh.seek(dl_start + (start_index * 8))
                    fg.write(fh.read(8))
                    dl_size += 8
                    start_index += 1
            vert_size = 0
            for di, d in enumerate(dl):
                if di != 0:
                    fg.seek(fg.tell() - 8)
                    dl_size -= 8
                dl_size += len(d)
                fg.write(d)
            for v in verts:
                vert_size += len(v)
                fg.write(v)
            fh.seek(0x40)
            footer_start = int.from_bytes(fh.read(4), "big")
            fh.seek(footer_start)
            fg.write(fh.read())
            fg.seek(0x38)
            fg.write((dl_start + dl_size).to_bytes(4, "big"))
            fg.seek(0x40)
            old = int.from_bytes(fg.read(4), "big")
            diff = (dl_start + dl_size + vert_size) - old
            for x in range(13):
                fg.seek(0x40 + (4 * x))
                old = int.from_bytes(fg.read(4), "big")
                fg.seek(0x40 + (4 * x))
                fg.write((old + diff).to_bytes(4, "big"))
            fg.seek(0x118)
            for x in bounds:
                val = x
                if val < 0:
                    val += 65536
                fg.write(val.to_bytes(2, "big"))

def getFileName(index: int) -> str:
    return f"newgeo_{index}.bin"

def makeNewGeoFile(reference: str, map_index: int):
    if reference == "both":
        order = ["floors", "walls"]
        makeNewGeoFile(order[0], map_index)
        with open(getFileName(map_index), "rb") as fh:
            with open(f"{order[0]}.bin", "wb") as fg:
                fg.write(fh.read())
        makeNewGeoFile(order[1], map_index)
        concatGeoFiles([f"{order[0]}.bin", getFileName(map_index)])
        with open(temp_name,"rb") as fh:
            with open(getFileName(map_index), "wb") as fg:
                fg.write(fh.read())
        return
    else:
        ref_data, verts = getFile(reference, map_index)
    getFile("geometry", 0)
    with open(temp_name, "rb") as fh:
        with open(getFileName(map_index), "w+b") as fg:
            fh.seek(0x34)
            dl_start = int.from_bytes(fh.read(4), "big")
            fh.seek(0)
            fg.write(fh.read(dl_start))
            dl_started = False
            start_index = 0
            while not dl_started:
                fh.seek(dl_start + (8 * start_index))
                dl_started = int.from_bytes(fh.read(1), "big") != 0
                if not dl_started:
                    fh.seek(dl_start + (8 * start_index))
                    fg.write(fh.read(8))
                start_index += 1
            # Write DL
            # Start
            for ins in starting_dl:
                for sub in ins:
                    fg.write(sub.to_bytes(4, "big"))
            # Vert draws
            unreferenced_verts = ref_data.copy()
            blocks = math.ceil(len(verts) / 32)
            vert_assignment = []
            vert_bounds = [[99999, -99999],[99999, -99999],[99999, -99999]]
            for vert in verts:
                for ci, c in enumerate(vert):
                    if c < vert_bounds[ci][0]:
                        vert_bounds[ci][0] = c
                    if c > vert_bounds[ci][1]:
                        vert_bounds[ci][1] = c
            for block in range(blocks):
                start = block * 32
                end = start + 32
                tris_in_chunk = [x for x in unreferenced_verts if max(x["verts"]) < end and min(x["verts"]) >= start]
                unreferenced_verts = [x for x in unreferenced_verts if min(x["verts"]) < start or max(x["verts"]) >= end]
                starting_size = len(vert_assignment)
                dl_commands = []
                vert_indexes = []
                ending = 0
                for tri_index, tri in enumerate(tris_in_chunk):
                    if (tri_index & 1) == 0:
                        vert_indexes = [] # Wipe vert indexes
                    for vert in tri["verts"]:
                        if vert not in vert_assignment:
                            vert_assignment.append(vert)
                        vert_indexes.append((vert_assignment.index(vert) - starting_size) << 1)
                    # print(vert_indexes)
                    if (tri_index & 1) == 1:
                        sub = []
                        sub0 = []
                        for x in range(2):
                            v = 0
                            v0 = 0
                            if x == 0:
                                v = 6 << 24
                                v0 = 6 << 24
                            for y in range(3):
                                local_vi = y + (3 * x)
                                v |= (vert_indexes[local_vi] << (8 * (2 - y)))
                                if y == 0:
                                    v0 |= (vert_indexes[local_vi] << 16)
                                else:
                                    v0 |= (vert_indexes[local_vi] << (8 - (8 * (2 - y))))
                            sub.append(v)
                            sub0.append(v0)
                        if double_render:
                            dl_commands.append(sub)
                            dl_commands.append(sub0)
                        else:
                            # print([hex(sub[0]), hex(sub[1])])
                            dl_commands.append(sub)
                    ending = tri_index & 1
                # print(vert_indexes)
                if ending == 0 and len(tris_in_chunk) > 0:
                    if double_render:
                        dl_commands.append([(5 << 24) | (vert_indexes[0] << 16) | (vert_indexes[1] << 8) | vert_indexes[2], 0])
                        dl_commands.append([(5 << 24) | (vert_indexes[0] << 16) | (vert_indexes[2] << 8) | vert_indexes[1], 0])
                    else:
                        dl_commands.append([(5 << 24) | (vert_indexes[0] << 16) | (vert_indexes[1] << 8) | vert_indexes[2], 0])
                size = len(vert_assignment) - starting_size
                vtx_load = (1 << 24) | (size << 12) | (size << 1)
                fg.write(vtx_load.to_bytes(4, "big"))
                vtx_load = (6 << 24) | (starting_size << 4)
                fg.write(vtx_load.to_bytes(4, "big"))
                for dl in dl_commands:
                    for x in range(2):
                        fg.write((dl[x]).to_bytes(4, "big"))
                if block < (blocks - 1) or len(unreferenced_verts) > 0:
                    for ins in joining_dl:
                        for sub in ins:
                            fg.write(sub.to_bytes(4, "big"))
            blocks = math.ceil(len(unreferenced_verts) / 10)
            for block in range(blocks):
                tris_handled = unreferenced_verts[(block * 10):((block + 1) * 10)]
                vert_index_start = len(vert_assignment)
                sub_vert_assignment = []
                dl_commands = []
                vert_indexes = []
                ending = 0
                for tri_index, tri in enumerate(tris_handled):
                    if (tri_index & 1) == 0:
                        vert_indexes = [] # Wipe vert indexes
                    for vert in tri["verts"]:
                        if vert not in sub_vert_assignment:
                            sub_vert_assignment.append(vert)
                        vert_indexes.append(sub_vert_assignment.index(vert) << 1)
                    if (tri_index & 1) == 1:
                        sub = []
                        sub0 = []
                        for x in range(2):
                            v = 0
                            v0 = 0
                            if x == 0:
                                v = 6 << 24
                                v0 = 6 << 24
                            for y in range(3):
                                local_vi = y + (3 * x)
                                v |= (vert_indexes[local_vi] << (8 * (2 - y)))
                                if y == 0:
                                    v0 |= (vert_indexes[local_vi] << 16)
                                else:
                                    v0 |= (vert_indexes[local_vi] << (8 - (8 * (2 - y))))
                            sub.append(v)
                            sub0.append(v0)
                        if double_render:
                            dl_commands.append(sub)
                            dl_commands.append(sub0)
                        else:
                            dl_commands.append(sub)
                    ending = tri_index & 1
                if ending == 0 and len(tris_handled) > 0:
                    if double_render:
                        dl_commands.append([(5 << 24) | (vert_indexes[0] << 16) | (vert_indexes[1] << 8) | vert_indexes[2], 0])
                        dl_commands.append([(5 << 24) | (vert_indexes[0] << 16) | (vert_indexes[2] << 8) | vert_indexes[1], 0])
                    else:
                        dl_commands.append([(5 << 24) | (vert_indexes[0] << 16) | (vert_indexes[1] << 8) | vert_indexes[2], 0])
                size = len(sub_vert_assignment)
                starting_size = len(vert_assignment)
                vert_assignment.extend(sub_vert_assignment)
                vtx_load = (1 << 24) | (size << 12) | (size << 1)
                fg.write(vtx_load.to_bytes(4, "big"))
                vtx_load = (6 << 24) | (starting_size << 4)
                fg.write(vtx_load.to_bytes(4, "big"))
                for dl in dl_commands:
                    for x in range(2):
                        fg.write((dl[x]).to_bytes(4, "big"))
                if block < (blocks - 1):
                    for ins in joining_dl:
                        for sub in ins:
                            fg.write(sub.to_bytes(4, "big"))
            # End
            for ins in ending_dl:
                for sub in ins:
                    fg.write(sub.to_bytes(4, "big"))
            dl_end = fg.tell()
            dl_size = dl_end - dl_start
            # Write Verts
            for vert in vert_assignment:
                vert_tri = verts[vert]
                for coord in vert_tri:
                    c = coord
                    if c < 0:
                        c += 65536
                    fg.write(c.to_bytes(2, "big"))
                for x in range(3):
                    fg.write((0).to_bytes(2, "big"))
                color = [0xFF,0xFF,0xFF]
                for tri in ref_data:
                    if vert in tri["verts"]:
                        color = tri["color"]
                new_color = color.copy()
                new_color.append(0xC0)
                for x in new_color:
                    fg.write(x.to_bytes(1, "big"))
            vert_size = len(vert_assignment) * 0x10
            # Write rest
            fh.seek(0x40)
            end_portion_start = int.from_bytes(fh.read(4), "big")
            fh.seek(end_portion_start)
            fg.write(fh.read())
            # Reallocate internal pointers
            fg.seek(0x38)
            fg.write(dl_end.to_bytes(4, "big"))
            fg.seek(0x40)
            old = int.from_bytes(fg.read(4), "big")
            new = dl_end + vert_size
            diff = new - old
            for x in range(13):
                fg.seek(0x40 + (4 * x))
                old = int.from_bytes(fg.read(4), "big")
                fg.seek(0x40 + (4 * x))
                new = old + diff
                fg.write(new.to_bytes(4, "big"))
            fg.seek(0x118)
            for c in vert_bounds:
                cv = c[0]
                if cv < 0:
                    cv += 65536
                fg.write(cv.to_bytes(2, "big"))
            for c in vert_bounds:
                cv = c[1]
                if cv < 0:
                    cv += 65536
                fg.write(cv.to_bytes(2, "big"))
    getFile("geometry", map_index)
    with open(temp_name, "rb") as fh:
        with open(getFileName(map_index), "r+b") as fg:
            fg.write(fh.read(0x30))

makeNewGeoFile("both",0x2A)