from enum import Enum
from copy import deepcopy

class Rubik():
    def __init__(self):
        self.corners = {i : rubik_corner(i) for i in range(1, 9)}
        self.edges = {i : rubik_edge(i) for i in range(1, 13)}
        self.create_dics_coord()
        self.precalc_manhattan_dist()

    def __str__(self):
        ret = "coins:\n"
        ret += "\t{}  {}\t{}  {}\n\t U\t D\n\t{}  {}\t{}  {}\n".format(self.get_corner_by_position(4).final_position, self.get_corner_by_position(1).final_position, self.get_corner_by_position(8).final_position, self.get_corner_by_position(5).final_position, self.get_corner_by_position(3).final_position, self.get_corner_by_position(2).final_position, self.get_corner_by_position(7).final_position, self.get_corner_by_position(6).final_position)
        ret += "aretes:\n"
        ret += "    {}        {}  {}        {}\n   {}  {}                {}  {}\n    {}        {}  {}        {}\n".format(self.get_edge_by_position(1).final_position,self.get_edge_by_position(8).final_position, self.get_edge_by_position(5).final_position, self.get_edge_by_position(9).final_position, self.get_edge_by_position(4).final_position, self.get_edge_by_position(2).final_position, self.get_edge_by_position(12).final_position, self.get_edge_by_position(10).final_position, self.get_edge_by_position(3).final_position, self.get_edge_by_position(7).final_position, self.get_edge_by_position(6).final_position, self.get_edge_by_position(11).final_position)
        return ret
        
#    def get_corner_by_number(self, number):
#        for elem in self.corners:
#            if number == elem.final_position:
#                return elem
#
#    def get_edge_by_number(self, number):
#        for elem in self.edges:
#            if number == elem.final_position:
#                return elem


    def get_corner_by_position(self, position):
        return self.corners[position]

    def get_edge_by_position(self, position):
        return self.edges[position]

    def create_dics_coord(self):
        """
        {index: (x, y, z)}
        le point 7 est le point 0, 0, 0
        """
        
        self.corner_coord = {}
        self.corner_coord[1] = (2, 2, 2) 
        self.corner_coord[2] = (2, 2, 0)
        self.corner_coord[3] = (0, 2, 0)
        self.corner_coord[4] = (0, 2, 2)
        self.corner_coord[5] = (2, 0, 2)
        self.corner_coord[6] = (2, 0, 0)
        self.corner_coord[7] = (0, 0, 0)
        self.corner_coord[8] = (0, 0, 2)
        
        self.edges_coord = {}
        self.edges_coord[1] = (1, 2, 2)
        self.edges_coord[2] = (2, 2, 1)
        self.edges_coord[3] = (1, 2, 0)
        self.edges_coord[4] = (0, 2, 1)
        self.edges_coord[5] = (2, 1, 2)
        self.edges_coord[6] = (2, 1, 0)
        self.edges_coord[7] = (0, 1, 0)
        self.edges_coord[8] = (0, 1, 2)
        self.edges_coord[9] = (1, 0, 2)
        self.edges_coord[10] = (2, 0, 1)
        self.edges_coord[11] = (1, 0, 0)
        self.edges_coord[12] = (0, 0, 1)
    
    def calc_dist(self, a, b):
        return abs(b[0] - a[0]) + abs(b[1] - a[1]) + abs(b[2] - a[2])
    
    def precalc_manhattan_dist(self):
        """
        {index: {cube: cout}}
        """
        # corners
        self.manhattan_dist = {}
        self.manhattan_dist["corner"] = {}
        for i in range(1, 9):
            self.manhattan_dist["corner"][i] = {}
            for j in range(1, 9):
                self.manhattan_dist["corner"][i][j] = self.calc_dist(self.corner_coord[i], self.corner_coord[j]) / 8
        #edges
        self.manhattan_dist["edge"] = {}
        for i in range(1, 13):
            self.manhattan_dist["edge"][i] = {}
            for j in range(1, 13):
                self.manhattan_dist["edge"][i][j] = self.calc_dist(self.edges_coord[i], self.edges_coord[j]) / 8
    
    def heuristic(self, obj):
        tot = 0
        for index in obj.corners:
            tot += self.manhattan_dist["corner"][index][obj.corners[index].final_position]
        for index in obj.edges:
            tot += self.manhattan_dist["edge"][index][obj.edges[index].final_position]
        return tot 


class rubik_corner():
    def __init__(self, position):
        self.orientation = 0
#        self.current_position = position
        self.final_position = position

    def __str__(self):
        return "orientation = {}\nfinal_position = {}\n".format(self.orientation, self.final_position)


class rubik_edge():
    def __init__(self, position):
        self.orientation = 0
#        self.current_position = position
        self.final_position = position

    def __str__(self):
        return "orientation = {}\nfinal_position = {}\n".format(self.orientation, self.final_position)
