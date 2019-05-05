from rubik_state import rubik_state

def get_nexts_1(state):
    nexts = []
    for i in range(1, 19):
        next = rubik_state(state, i)
        nexts.append(next)
    return nexts

def get_nexts_2(state):
    nexts = []
    for i in [13, 14, 15, 16, 17, 18, 1, 4, 7, 10]:
        next = rubik_state(state, i)
        nexts.append(next)
    return nexts
