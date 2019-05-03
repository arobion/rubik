from rubik_moves import move

class rubik_state():
    def __init__(self, parent, instruction):
        if instruction == 0:
            self.g = 0
            self.edges = parent.edges.copy()
            self.corners = parent.corners.copy()
        else:
            self.edges = parent.edges.copy()
            self.corners = parent.corners.copy()
            self.instruction = instruction
            move(self, instruction)

            self.g = parent.g + 1

        self.state = tuple([(sub.final_position, sub.orientation) for dic in [self.corners, self.edges] for sub in dic.values()])

    def __str__(self):
        ret = "g(x): {}\n".format(self.g)
        ret += "coins:\n"
        ret += "\t{}  {}\t{}  {}\n\t U\t D\n\t{}  {}\t{}  {}\n".format(self.corners[4].final_position, self.corners[1].final_position, self.corners[8].final_position, self.corners[5].final_position, self.corners[3].final_position, self.corners[2].final_position, self.corners[7].final_position, self.corners[6].final_position)
        ret += "aretes:\n"
        ret += "    {}        {}  {}        {}\n   {}  {}                {}  {}\n    {}        {}  {}        {}\n".format(self.edges[1].final_position,self.edges[8].final_position, self.edges[5].final_position, self.edges[9].final_position, self.edges[4].final_position, self.edges[2].final_position, self.edges[12].final_position, self.edges[10].final_position, self.edges[3].final_position, self.edges[7].final_position, self.edges[6].final_position, self.edges[11].final_position)
        return ret


