def U(obj):
    #corner: 1 2 3 4, edges: 1 2 3 4
    obj.corners[1], obj.corners[2], obj.corners[3], obj.corners[4] = obj.corners[4], obj.corners[1], obj.corners[2], obj.corners[3]
    obj.edges[1], obj.edges[2], obj.edges[3], obj.edges[4] = obj.edges[4], obj.edges[1], obj.edges[2], obj.edges[3]

def R(obj):
    #corner: 1 5 6 2, edges: 2 5 1 6
    obj.corners[2].orientation, obj.corners[5].orientation = (obj.corners[2].orientation + 1) % 3, (obj.corners[5].orientation + 1) % 3
    obj.corners[1].orientation, obj.corners[6].orientation = (obj.corners[1].orientation - 1) % 3, (obj.corners[6].orientation - 1) % 3
    
    obj.corners[1], obj.corners[5], obj.corners[6], obj.corners[2] = obj.corners[2], obj.corners[1], obj.corners[5], obj.corners[6]
    obj.edges[2], obj.edges[5], obj.edges[10], obj.edges[6] = obj.edges[6], obj.edges[2], obj.edges[5], obj.edges[10]

def L(obj):
    #corner: 4 3 7 8, edges: 4 7 12 8
    obj.corners[4].orientation, obj.corners[7].orientation = (obj.corners[4].orientation + 1) % 3, (obj.corners[7].orientation + 1) % 3
    obj.corners[3].orientation, obj.corners[8].orientation = (obj.corners[3].orientation - 1) % 3, (obj.corners[8].orientation - 1) % 3
    
    obj.corners[4], obj.corners[3], obj.corners[7], obj.corners[8] = obj.corners[8], obj.corners[4], obj.corners[3], obj.corners[7]
    obj.edges[4], obj.edges[7], obj.edges[12], obj.edges[8] = obj.edges[8], obj.edges[4], obj.edges[7], obj.edges[12]

def D(obj):
    #corner: 5 8 7 6, edges: 9 12 11 10
    obj.corners[5], obj.corners[8], obj.corners[7], obj.corners[6] = obj.corners[6], obj.corners[5], obj.corners[8], obj.corners[7]
    obj.edges[9], obj.edges[12], obj.edges[11], obj.edges[10] = obj.edges[10], obj.edges[9], obj.edges[12], obj.edges[11]

def F(obj):
    #corner: 3 2 6 7, edges: 3 6 11 7
    obj.corners[3].orientation, obj.corners[6].orientation = (obj.corners[3].orientation + 1) % 3, (obj.corners[6].orientation + 1) % 3
    obj.corners[2].orientation, obj.corners[7].orientation = (obj.corners[2].orientation - 1) % 3, (obj.corners[7].orientation - 1) % 3
    
    obj.edges[3].orientation, obj.edges[11].orientation = (obj.edges[3].orientation + 1) % 2, (obj.edges[11].orientation + 1) %2
    obj.edges[6].orientation, obj.edges[7].orientation = (obj.edges[6].orientation + 1) % 2, (obj.edges[7].orientation + 1) %2
    
    obj.corners[3], obj.corners[2], obj.corners[6], obj.corners[7] = obj.corners[7], obj.corners[3], obj.corners[2], obj.corners[6]
    obj.edges[3], obj.edges[6], obj.edges[11], obj.edges[7] = obj.edges[7], obj.edges[3], obj.edges[6], obj.edges[11]

def B(obj):
    #corner: 1 4 8 5, edges: 1 8 9 5
    obj.corners[1].orientation, obj.corners[8].orientation = (obj.corners[1].orientation + 1) % 3, (obj.corners[8].orientation + 1) % 3
    obj.corners[4].orientation, obj.corners[5].orientation = (obj.corners[4].orientation - 1) % 3, (obj.corners[5].orientation - 1) % 3
    
    obj.edges[1].orientation, obj.edges[9].orientation = (obj.edges[1].orientation + 1) % 2, (obj.edges[9].orientation + 1) %2
    obj.edges[5].orientation, obj.edges[8].orientation = (obj.edges[5].orientation + 1) % 2, (obj.edges[8].orientation + 1) %2
    
    obj.corners[1], obj.corners[4], obj.corners[8], obj.corners[5] = obj.corners[5], obj.corners[1], obj.corners[4], obj.corners[8]
    obj.edges[1], obj.edges[8], obj.edges[9], obj.edges[5] = obj.edges[5], obj.edges[1], obj.edges[8], obj.edges[9]

def Ur(obj):
    #corner: 4 3 2 1, edges: 4 3 2 1
    obj.corners[4], obj.corners[3], obj.corners[2], obj.corners[1] = obj.corners[1], obj.corners[4], obj.corners[3], obj.corners[2]
    obj.edges[4], obj.edges[3], obj.edges[2], obj.edges[1] = obj.edges[1], obj.edges[4], obj.edges[3], obj.edges[2]

def Rr(obj):
    #corner: 2 6 5 1, edges: 6 10 5 2
    obj.corners[2].orientation, obj.corners[5].orientation = (obj.corners[2].orientation + 1) % 3, (obj.corners[5].orientation + 1) % 3
    obj.corners[6].orientation, obj.corners[1].orientation = (obj.corners[6].orientation - 1) % 3, (obj.corners[1].orientation - 1) % 3
    
    obj.corners[2], obj.corners[6], obj.corners[5], obj.corners[1] = obj.corners[1], obj.corners[2], obj.corners[6], obj.corners[5]
    obj.edges[6], obj.edges[10], obj.edges[5], obj.edges[2] = obj.edges[2], obj.edges[6], obj.edges[10], obj.edges[5]

def Lr(obj):
    #corner: 8 7 3 4, edges: 8 12 7 4
    obj.corners[7].orientation, obj.corners[4].orientation = (obj.corners[7].orientation + 1) % 3, (obj.corners[4].orientation + 1) % 3
    obj.corners[8].orientation, obj.corners[3].orientation = (obj.corners[8].orientation - 1) % 3, (obj.corners[3].orientation - 1) % 3
    
    obj.corners[8], obj.corners[7], obj.corners[3], obj.corners[4] = obj.corners[4], obj.corners[8], obj.corners[7], obj.corners[3]
    obj.edges[8], obj.edges[12], obj.edges[7], obj.edges[4] = obj.edges[4], obj.edges[8], obj.edges[12], obj.edges[7]

def Dr(obj):
    #corner: 6 7 8 5, edges: 10 11 12 9
    obj.corners[6], obj.corners[7], obj.corners[8], obj.corners[5] = obj.corners[5], obj.corners[6], obj.corners[7], obj.corners[8]
    obj.edges[10], obj.edges[11], obj.edges[12], obj.edges[9] = obj.edges[9], obj.edges[10], obj.edges[11], obj.edges[12]

def Fr(obj):
    #corner:7 6 2 3, edges: 7 11 6 3
    obj.corners[6].orientation, obj.corners[3].orientation = (obj.corners[6].orientation + 1) % 3, (obj.corners[3].orientation + 1) % 3
    obj.corners[7].orientation, obj.corners[2].orientation = (obj.corners[7].orientation - 1) % 3, (obj.corners[2].orientation - 1) % 3
    
    obj.edges[3].orientation, obj.edges[11].orientation = (obj.edges[3].orientation + 1) % 2, (obj.edges[11].orientation + 1) %2
    obj.edges[6].orientation, obj.edges[7].orientation = (obj.edges[6].orientation + 1) % 2, (obj.edges[7].orientation + 1) %2
    
    obj.corners[7], obj.corners[6], obj.corners[2], obj.corners[3] = obj.corners[3], obj.corners[7], obj.corners[6], obj.corners[2]
    obj.edges[7], obj.edges[11], obj.edges[6], obj.edges[3] = obj.edges[3], obj.edges[7], obj.edges[11], obj.edges[6]

def Br(obj):
    #corner: 5 8 4 1, edges: 5 9 8 1
    obj.corners[1].orientation, obj.corners[8].orientation = (obj.corners[1].orientation + 1) % 3, (obj.corners[8].orientation + 1) % 3
    obj.corners[4].orientation, obj.corners[5].orientation = (obj.corners[4].orientation - 1) % 3, (obj.corners[5].orientation - 1) % 3
    
    obj.edges[1].orientation, obj.edges[9].orientation = (obj.edges[1].orientation + 1) % 2, (obj.edges[9].orientation + 1) %2
    obj.edges[5].orientation, obj.edges[8].orientation = (obj.edges[5].orientation + 1) % 2, (obj.edges[8].orientation + 1) %2
    
    obj.corners[5], obj.corners[8], obj.corners[4], obj.corners[1] = obj.corners[1], obj.corners[5], obj.corners[8], obj.corners[4]
    obj.edges[5], obj.edges[9], obj.edges[8], obj.edges[1] = obj.edges[1], obj.edges[5], obj.edges[9], obj.edges[8]

def U2(obj):
    #corner: 1-3 4-2, edges: 1-3 4-2
    obj.corners[1], obj.corners[3], obj.corners[4], obj.corners[2] = obj.corners[3], obj.corners[1], obj.corners[2], obj.corners[4]
    obj.edges[1], obj.edges[3], obj.edges[4], obj.edges[2] = obj.edges[3], obj.edges[1], obj.edges[4], obj.edges[2]

def R2(obj):
    #corner: 1-6 2-5, edges: 2-10 5-6
    obj.corners[1], obj.corners[6], obj.corners[2], obj.corners[5] = obj.corners[6], obj.corners[1], obj.corners[5], obj.corners[2]
    obj.edges[2], obj.edges[10], obj.edges[5], obj.edges[6] = obj.edges[10], obj.edges[2], obj.edges[6], obj.edges[5]

def L2(obj):
    #corner: 4-7 3-8, edges: 4-12 7-8
    obj.corners[4], obj.corners[7], obj.corners[3], obj.corners[8] = obj.corners[7], obj.corners[4], obj.corners[8], obj.corners[3]
    obj.edges[4], obj.edges[12], obj.edges[7], obj.edges[8] = obj.edges[12], obj.edges[4], obj.edges[8], obj.edges[7]

def D2(obj):
    #corner: 5-7 6-8, edges: 9-11 10-12
    obj.corners[5], obj.corners[7], obj.corners[6], obj.corners[8] = obj.corners[7], obj.corners[5], obj.corners[8], obj.corners[6]
    obj.edges[9], obj.edges[11], obj.edges[10], obj.edges[12] = obj.edges[11], obj.edges[9], obj.edges[12], obj.edges[10]

def F2(obj):
    #corner: 2-7 3-6, edges: 3-11 6-7
    obj.corners[2], obj.corners[7], obj.corners[3], obj.corners[6] = obj.corners[7], obj.corners[2], obj.corners[6], obj.corners[3]
    obj.edges[3], obj.edges[11], obj.edges[6], obj.edges[7] = obj.edges[11], obj.edges[3], obj.edges[7], obj.edges[6]

def B2(obj):
    #corner: 1-8 4-5, edges: 1-9 5-8
    obj.corners[1], obj.corners[8], obj.corners[4], obj.corners[5] = obj.corners[8], obj.corners[1], obj.corners[5], obj.corners[4]
    obj.edges[1], obj.edges[9], obj.edges[5], obj.edges[8] = obj.edges[9], obj.edges[1], obj.edges[8], obj.edges[5]

move_fp = {
    1: U,
    2: R,
    3: L,
    4: D,
    5: F,
    6: B,
    7: Ur,
    8: Rr,
    9: Lr,
    10: Dr,
    11: Fr,
    12: Br,
    13: U2,
    14: R2,
    15: L2,
    16: D2,
    17: F2,
    18: B2
}

def move(obj, instruction):
    move_fp[instruction](obj)

move_notation_fp = {
    "U": U,
    "R": R,
    "L": L,
    "D": D,
    "F": F,
    "B": B,
    "U'": Ur,
    "R'": Rr,
    "L'": Lr,
    "D'": Dr,
    "F'": Fr,
    "B'": Br,
    "U2": U2,
    "R2": R2,
    "L2": L2,
    "D2": D2,
    "F2": F2,
    "B2": B2
}

def move_by_notation(obj, notation):
    move_notation_fp[notation](obj)
