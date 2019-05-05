from enum import Enum
from copy import deepcopy

class Rubik():
    def __init__(self):
        self.corners = {i : rubik_corner(i) for i in range(1, 9)}
        self.edges = {i : rubik_edge(i) for i in range(1, 13)}
        self.create_dics_coord()
        self.precalc_h2()
        self.precalc_h1()

    def __str__(self):
        ret = "coins:\n"
        ret += "\t{}  {}\t{}  {}\n\t U\t D\n\t{}  {}\t{}  {}\n".format(self.corners[4].final_position, self.corners[1].final_position, self.corners[8].final_position, self.corners[5].final_position, self.corners[3].final_position, self.corners[2].final_position, self.corners[7].final_position, self.corners[6].final_position)
        ret += "aretes:\n"
        ret += "    {}        {}  {}        {}\n   {}  {}                {}  {}\n    {}        {}  {}        {}\n".format(self.edges[1].final_position,self.edges[8].final_position, self.edges[5].final_position, self.edges[9].final_position, self.edges[4].final_position, self.edges[2].final_position, self.edges[12].final_position, self.edges[10].final_position, self.edges[3].final_position, self.edges[7].final_position, self.edges[6].final_position, self.edges[11].final_position)
        return ret
        
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

        # everything is the same return 0
        # same a[1] > return 1
        # diff a[1] and same a[0] return 1
        # else return 2
    
    def calc_dist(self, a, b):
        return abs(b[0] - a[0]) + abs(b[1] - a[1]) + abs(b[2] - a[2])

    def calc_corner_move(self, a, b):
        if a[0] == b[0] and a[1] == b[1] and a[2] == b[2]:
            return 0
        if a[0] != b[0] and a[1] != b[1] and a[2] != b[2]:
            return 2
        return 1
    
    def calc_edge_move(self, a, b):
        if a[0] == b[0] and a[1] == b[1] and a[2] == b[2]:
            return 0
        if a[1] == a[1]:
            return 1
        if a[0] == a[0] and a[2] == a[2]:
            return 1
        return 2
    
    '''
    def precalc_h2(self):
        """
        {index: {cube: cout}}
        """
        # corners
        self.manhattan_dist = {}
        self.manhattan_dist["corner"] = {}
        for i in range(1, 9):
            self.manhattan_dist["corner"][i] = {}
            for j in range(1, 9):
                self.manhattan_dist["corner"][i][j] = self.calc_corner_move(self.corner_coord[i], self.corner_coord[j]) / 8
        #edges
        self.manhattan_dist["edge"] = {}
        for i in range(1, 13):
            self.manhattan_dist["edge"][i] = {}
            for j in range(1, 13):
                self.manhattan_dist["edge"][i][j] = self.calc_edge_move(self.edges_coord[i], self.edges_coord[j]) / 8

    def heuristic_h2(self, obj):
        tot = 0
        for index in obj.corners:
            tot += self.manhattan_dist["corner"][index][obj.corners[index].final_position]
        for index in obj.edges:
            tot += self.manhattan_dist["edge"][index][obj.edges[index].final_position]
        return tot 
    '''

    def precalc_h2(self):
        """
        {index: {cube: cout}}
        """
        # corners
        self.manhattan_dist = {}
        self.manhattan_dist["corner"] = {}
        for i in range(1, 9):
            self.manhattan_dist["corner"][i] = {}
            for j in range(1, 9):
                self.manhattan_dist["corner"][i][j] = self.calc_corner_move(self.corner_coord[i], self.corner_coord[j]) / 4
        #edges
        self.manhattan_dist["edge"] = {}
        for i in range(1, 13):
            self.manhattan_dist["edge"][i] = {}
            for j in range(1, 13):
                self.manhattan_dist["edge"][i][j] = self.calc_edge_move(self.edges_coord[i], self.edges_coord[j]) / 4

    def heuristic_h2(self, obj):
        tot_corner = 0
        tot_edge = 0
        for index in obj.corners:
            tot_corner += self.manhattan_dist["corner"][index][obj.corners[index].final_position]
        for index in obj.edges:
            tot_edge += self.manhattan_dist["edge"][index][obj.edges[index].final_position]
        return max(tot_corner, tot_edge) 

    def precalc_h1(self):
        """
        {index : {cube: cout}}
        """
        self.h1_dist = {}
        for i in range(1, 13):
            self.h1_dist[i] = {}
            for j in range(1, 13):
                if i == j:
                    self.h1_dist[i][j] = 0
                elif i not in [5, 6, 7, 8] and j not in [5, 6, 7, 8]:
                    self.h1_dist[i][j] = 0
                elif i in [5, 6, 7, 8] and j in [5, 6, 7, 8]:
                    self.h1_dist[i][j] = 0
                else:
                    self.h1_dist[i][j] = 1

    def heuristic_h1(self, obj):
        tot = 0
        for elem in obj.corners.values():
            if elem.orientation != 0:
                tot += 1
        for index in obj.edges:
            if obj.edges[index].orientation == 0:
                tot += self.h1_dist[index][obj.edges[index].final_position]
            else:
                tot += obj.edges[index].orientation
        return tot / 8


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
