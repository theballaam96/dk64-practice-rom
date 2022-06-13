savestate_allocation = [0,1,2,3]
current_allocation = [[2,"a"],[1,"b"],[3,0],[0,"d"]]

different_allocation = [False,False,False,False]
has_differences = False
new_swap_index = 0
current_allocation_copy = [0,0,0,0]
for x in range(4):
    old_val = savestate_allocation[x]
    new_val = current_allocation[x][0]
    current_allocation_copy[x] = new_val
    different_allocation[x] = (new_val != old_val) or new_val == 3
    if new_val == 3:
        new_swap_index = x
    has_differences = True
initial_swap = False
if has_differences:
    still_different = True
    for x in range(4):
        if still_different:
            if not initial_swap:
                if different_allocation[x]:
                    print(current_allocation[x])
                    print(f"{current_allocation[x][0]}->Slot {new_swap_index}")
                    current_allocation[new_swap_index][0] = current_allocation[x][0]
                    current_allocation[new_swap_index][1] = current_allocation[x][1]
                    current_allocation[x] = [3,0]
                    new_swap_index = x
                    still_different = False
                    for a in range(4):
                        if current_allocation[a][0] != savestate_allocation[a]:
                            still_different = True
                    initial_swap = True
                    print(current_allocation)
            else:
                print(current_allocation[x])
                slot_file = savestate_allocation[new_swap_index]
                print(f"Find slot with file {slot_file}")
                found_slot = -1
                for y in range(4):
                    if current_allocation[y][0] == slot_file:
                        found_slot = y
                if found_slot == -1:
                    print("Could not find slot")
                else:
                    current_allocation[new_swap_index][0] = current_allocation[found_slot][0]
                    current_allocation[new_swap_index][1] = current_allocation[found_slot][1]
                    current_allocation[found_slot] = [3,0]
                    new_swap_index = found_slot
                    still_different = False
                    for a in range(4):
                        if current_allocation[a][0] != savestate_allocation[a]:
                            still_different = True

print(current_allocation)
