import json

pre = ""
watch_json = f"{pre}include/watches.json"
watch_c = f"{pre}src/watch/watch_list.c"
watch_h = f"{pre}include/watch_list.h"

warning = [
	"/*",
	"\tThis is an automatically generated file.",
	"\tPlease don't make edits to this file directly as they will be overwritten at next build.",
	"\tTo make amendments, see include/watches.json and build/watch_generator.py.",
	"\tThanks.",
	"*/",
]

lst_viewed = ["viewed","change","listed"]

with open(watch_c,"w") as f_c:
    with open(watch_h,"w") as f_h:
        for w in warning:
            f_c.write(f"{w}\n")
            f_h.write(f"{w}\n")
        f_c.write("\n#include \"../../include/common.h\"\n")
        f_h.write("\n")
        with open(watch_json,"r") as fh:
            data = json.load(fh)
            parent_data = data["parents"]
            watch_idx = 0
            master_idx = 0
            func_lst = []
            lsts = [
                {"name":"viewed","lines":["const char* watch_viewed_array[] = {"]},
                {"name":"listed","lines":["const char* watch_listed_array[] = {"]},
                {"name":"change","lines":["const char* watch_change_array[] = {"]},
            ]
            total_watch_count = 0
            for parent in parent_data:
                watch_type_name = parent["watch_type"]
                parent_vacant = False
                if "vacant" in parent:
                    if parent["vacant"]:
                        parent_vacant = True
                temp = []
                if not parent_vacant:
                    temp_lst_obj = {"name":watch_type_name,"lines":[f"const char* watch_{watch_type_name}_array[] = {{"]}
                    temp_lst_fnc = {"name":f"f{watch_type_name}","lines":[f"const int watch_{watch_type_name}_functions[] = {{"]}
                    temp_lst_scr = {"name":f"s{watch_type_name}","lines":[]}
                    f_c.write(f"\n// {watch_type_name}\n")
                    f_h.write(f"extern const char* watch_{watch_type_name}_array[{len(parent['watches'])}];\n")
                for watch in parent["watches"]:
                    new = -1
                    master_new = master_idx
                    master_idx += 1
                    is_vacant = False
                    is_null = False
                    if "null_index" in watch:
                        if watch["null_index"]:
                            is_null = True
                    if "vacant" in watch:
                        if watch["vacant"]:
                            is_vacant = True
                    if not is_null:
                        watch_idx += 1
                        new = master_idx
                        
                    temp.append(new)
                    if not parent_vacant:
                        temp_lst_obj["lines"].append(f"\tchange_{watch['prop']},")
                        func = "setWatch"
                        if "func" in watch:
                            func = watch["func"]
                        if func not in func_lst:
                            func_lst.append(func)
                        temp_lst_fnc["lines"].append(f"\t(int)&{func},")
                        f_c.write(f"static const char viewed_{watch['prop']}[] = \"}} {watch['text'].upper()}\";\n")
                        f_c.write(f"static const char change_{watch['prop']}[] = \"{{ {watch['text'].upper()}\";\n")
                    for a in lst_viewed:
                        b = a
                        if a == "listed":
                            b = "change"
                        if is_vacant:
                            [x for x in lsts if x["name"] == a][0]["lines"].append("\t0,")
                        else:
                            [x for x in lsts if x["name"] == a][0]["lines"].append(f"\t{b}_{watch['prop']},")
                    total_watch_count += 1
                    f_h.write(f"#define WATCH_{watch['prop'].upper()}_INDEX {master_new+1}\n")
                if len(temp) > 0:
                    seq_str = str(temp[0])
                    if len(temp) > 1:
                        for a in range(len(temp) - 1):
                            seq_str += f",{temp[a + 1]}"
                    if not parent_vacant:
                        f_c.write(f"const char watches_{watch_type_name}_indexes[] = {{{seq_str}}};\n")
                        f_h.write(f"extern const char watches_{watch_type_name}_indexes[{len(parent['watches'])}];\n")
                if not parent_vacant:
                    parent_screen = [
                        f"const Screen watch_{watch_type_name}_struct = {{",
                        f"\t.TextArray = (int*)watch_{watch_type_name}_array,",
                        f"\t.FunctionArray = watch_{watch_type_name}_functions,",
                        f"\t.ArrayItems = {len(parent['watches'])},",
                        "\t.ParentScreen = ACTIVEMENU_SCREEN_WATCH_ROOT,",
                        f"\t.ParentPosition = {parent['position']},"
                    ]
                    if "access" in parent:
                        if parent["access"]:
                            parent_screen.extend([
                                "\t.hasAccessArray = 1,",
                                f"\t.AccessArray = watch_{watch_type_name}_access,",
                            ])
                    temp_lst_scr["lines"] = parent_screen.copy()
                if not parent_vacant:
                    lsts.append(temp_lst_obj)
                    lsts.append(temp_lst_fnc)
                    lsts.append(temp_lst_scr)
            for a in lst_viewed:
                f_h.write(f"extern const char* watch_{a}_array[{total_watch_count}];\n")
            for a in lsts:
                [x for x in lsts if x["name"] == a["name"]][0]["lines"].append("};")
            for a in lsts:
                f_c.write("\n")
                for b in [x for x in lsts if x['name'] == a["name"]][0]['lines']:
                    f_c.write(f"{b}\n")
            f_h.write("\n")
            for f in func_lst:
                f_h.write(f"extern void {f}(void);\n")
print("Successfully built watches")