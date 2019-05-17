from enum import Enum
from copy import deepcopy

class Rubik():
    def __init__(self):
        self.corners = {i : rubik_corner(i) for i in range(1, 9)}
        self.edges = {i : rubik_edge(i) for i in range(1, 13)}
        self.pruning_phase1_corners = {}
        self.pruning_phase1_edges = {}
        self.pruning_phase1_slice = {}
        self.pruning_phase2 = {}
        self.corners_state = tuple([elem.orientation for elem in self.corners.values()])
        self.edges_state = tuple([elem.orientation for elem in self.edges.values()])
        self.slice_state = tuple([self.edges[i].final_position for i in range(5, 9)])

    def __str__(self):
        ret = "coins:\n"
        ret += "\t{}  {}\t{}  {}\n\t U\t D\n\t{}  {}\t{}  {}\n".format(self.corners[4].final_position, self.corners[1].final_position, self.corners[8].final_position, self.corners[5].final_position, self.corners[3].final_position, self.corners[2].final_position, self.corners[7].final_position, self.corners[6].final_position)
        ret += "aretes:\n"
        ret += "    {}        {}  {}        {}\n   {}  {}                {}  {}\n    {}        {}  {}        {}\n".format(self.edges[1].final_position,self.edges[8].final_position, self.edges[5].final_position, self.edges[9].final_position, self.edges[4].final_position, self.edges[2].final_position, self.edges[12].final_position, self.edges[10].final_position, self.edges[3].final_position, self.edges[7].final_position, self.edges[6].final_position, self.edges[11].final_position)
        return ret

class rubik_corner():
    def __init__(self, position):
        self.orientation = 0
        self.final_position = position

    def __str__(self):
        return "orientation = {}\nfinal_position = {}\n".format(self.orientation, self.final_position)


class rubik_edge():
    def __init__(self, position):
        self.orientation = 0
        self.final_position = position

    def __str__(self):
        return "orientation = {}\nfinal_position = {}\n".format(self.orientation, self.final_position)
