def compress_state(state):
    compressed = 0
    # first compress corners place
    for i in range(1, 9):
        compressed <<= 3
        compressed |= state.corners[i].final_position
    # compress corners orientation
    for i in range(1, 9):
        compressed <<= 2
        compressed |= state.corners[i].orientation
    # compress edges place
    for i in range(1, 13):
        compressed <<= 4
        compressed |= state.edges[i].final_position
    # corners edges orientation
    for i in range(1, 13):
        compressed <<= 1
        compressed |= state.edges[i].orientation
    return str(compressed)


def gen_pruning(dico, curr_node, heuristic, depth):
    if depth < 8:
        next_depth = []
        for elem in get_nexts_2(curr_node):
            dico[compress_state(elem)] = heuristic(elem)
            next_depth.append(elem)
        for elem in next_depth:
            gen_pruning(dico, elem, heuristic, depth + 1)
