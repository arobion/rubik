from rubik_state import rubik_state
import heapq

forbidden_move_phase_1 = {
    0: [0],
    1: [1, 7, 13],
    7: [1, 7, 13],
    13: [1, 7, 13],
    2: [2, 8, 14],
    8: [2, 8, 14],
    14: [2, 8, 14],
    3: [3, 9, 15],
    9: [3, 9, 15],
    15: [3, 9, 15],
    4: [4, 10, 16],
    10: [4, 10, 16],
    16: [4, 10, 16],
    5: [5, 11, 17],
    11: [5, 11, 17],
    17: [5, 11, 17],
    6: [6, 12, 18],
    12: [6, 12, 18],
    18: [6, 12, 18],

}

def get_nexts_1(state, h):
    nexts = []
    for i in range(1, 19):
        if i not in forbidden_move_phase_1[state.instruction]:
            heapq.heappush(nexts, rubik_state(state, i, h))
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

def get_nexts_2(state, h):
    nexts = []
    for i in [13, 14, 15, 16, 17, 18, 1, 4, 7, 10]:
        if i not in forbidden_move_phase_2[state.instruction]:
            heapq.heappush(nexts, rubik_state(state, i, h))
    return nexts

#    return [rubik_state(state, i) for i in [13, 14, 15, 16, 17, 18, 1, 4, 7, 10] if i not in forbidden_move_phase_2[state.instruction]]
