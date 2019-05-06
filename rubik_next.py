from rubik_state import rubik_state

def get_nexts_1(state):
    nexts = []
    for i in range(1, 19):
        next = rubik_state(state, i)
        nexts.append(next)
    return nexts

forbidden_move_phase_2 = {
    0: [0],
    1: [1, 7, 13],
    7: [1, 7, 13],
    13: [1, 7, 13],
    4: [4, 10, 16],
    10: [4, 10, 16],
    16: [4, 10, 16],
    14: [14],
    15: [15],
    17: [17],
    18: [18],
}

def get_nexts_2(state):
    return [rubik_state(state, i) for i in [13, 14, 15, 16, 17, 18, 1, 4, 7, 10] if i not in forbidden_move_phase_2[state.instruction]]
