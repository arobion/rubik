from rubik_moves import move, move_translator
import copy

class rubik_state():
    def __init__(self, parent, instruction, h):
        self.g = 0
        self.edges = copy.deepcopy(parent.edges)
        self.corners = copy.deepcopy(parent.corners)
        self.instruction = instruction

        if instruction != 0:
            move(self, instruction)
            self.g = parent.g + 1

        self.corners_state = tuple([elem.orientation for elem in self.corners.values()])
        self.edges_state = tuple([elem.orientation for elem in self.edges.values()])
        self.slice_state = tuple([self.edges[i].final_position for i in range(5, 9)])
        self.h = h(self)
        self.f = self.g + self.h

        self.compressed = self.compress_state()
        self.state = tuple([(sub.final_position, sub.orientation) for dic in [self.corners, self.edges] for sub in dic.values()])

    def __str__(self):
        ret = "inst: {}\n".format(move_translator[self.instruction])
        ret += "eo: "
        for elem in self.edges.values():
            ret += "{} ".format(elem.orientation)
        ret += "\nep: "
        for elem in self.edges.values():
            ret += "{} ".format(elem.final_position)
        ret += "\nco: "
        for elem in self.corners.values():
            ret += "{} ".format(elem.orientation)
        ret += "\ncp: "
        for elem in self.corners.values():
            ret += "{} ".format(elem.final_position)
        '''
        ret = "instruction: {}\n".format(self.instruction)
        ret += "g(x): {}\n".format(self.g)
        ret += "coins:\n"
        ret += "\t{}  {}\t{}  {}\n\t U\t D\n\t{}  {}\t{}  {}\n".format(self.corners[4].final_position, self.corners[1].final_position, self.corners[8].final_position, self.corners[5].final_position, self.corners[3].final_position, self.corners[2].final_position, self.corners[7].final_position, self.corners[6].final_position)
        ret += "aretes:\n"
        ret += "    {}        {}  {}        {}\n   {}  {}                {}  {}\n    {}        {}  {}        {}\n".format(self.edges[1].final_position,self.edges[8].final_position, self.edges[5].final_position, self.edges[9].final_position, self.edges[4].final_position, self.edges[2].final_position, self.edges[12].final_position, self.edges[10].final_position, self.edges[3].final_position, self.edges[7].final_position, self.edges[6].final_position, self.edges[11].final_position)
        '''
        return ret

    def __lt__(self, other):
        if self.f != other.f:
            return self.f < other.f

        if self.h != other.h:
            return self.h < other.h

        return self.g < other.g 

    def compress_state(self):
        compressed = 0
        # first compress corners place
        for i in range(1, 9):
            compressed <<= 3
            compressed |= (self.corners[i].final_position - 1)
        # compress corners orientation
        for i in range(1, 9):
            compressed <<= 2
            compressed |= self.corners[i].orientation
        # compress edges place
        for i in range(1, 13):
            compressed <<= 4
            compressed |= self.edges[i].final_position
        # corners edges orientation
        for i in range(1, 13):
            compressed <<= 1
            compressed |= self.edges[i].orientation
        return str(compressed)
