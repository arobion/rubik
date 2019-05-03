from enum import Enum
from copy import deepcopy

class Rubik():
    def __init__(self):
        self.corners = {i : rubik_corner(i) for i in range(1, 9)}
        self.edges = {i : rubik_edge(i) for i in range(1, 13)}
        self.move_fp = {
            1: self.U,
            2: self.R,
            3: self.L,
            4: self.D,
            5: self.F,
            6: self.B,
            7: self.Ur,
            8: self.Rr,
            9: self.Lr,
            10: self.Dr,
            11: self.Fr,
            12: self.Br,
            13: self.U2,
            14: self.R2,
            15: self.L2,
            16: self.D2,
            17: self.F2,
            18: self.B2
        }
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
    
    def heuristic_manhattan(self):
        tot = 0
        for index in self.corners:
            tot += self.manhattan_dist["corner"][index][self.corners[index].final_position]
        for index in self.edges:
            tot += self.manhattan_dist["edge"][index][self.edges[index].final_position]
        return tot 

    def move(self, instruction):
        self.move_fp[instruction]()

    def U(self):
        #corner: 1 2 3 4, edges: 1 2 3 4
        self.corners[1], self.corners[2], self.corners[3], self.corners[4] = self.corners[4], self.corners[1], self.corners[2], self.corners[3]
        self.edges[1], self.edges[2], self.edges[3], self.edges[4] = self.edges[4], self.edges[1], self.edges[2], self.edges[3]

    def R(self):
        #corner: 1 5 6 2, edges: 2 5 10 6
        self.corners[2].orientation, self.corners[5].orientation = (self.corners[2].orientation + 1) % 3, (self.corners[5].orientation + 1) % 3
        self.corners[1].orientation, self.corners[6].orientation = (self.corners[1].orientation - 1) % 3, (self.corners[6].orientation - 1) % 3
        
        self.corners[1], self.corners[5], self.corners[6], self.corners[2] = self.corners[2], self.corners[1], self.corners[5], self.corners[6]
        self.edges[2], self.edges[5], self.edges[10], self.edges[6] = self.edges[6], self.edges[2], self.edges[5], self.edges[10]
    
    def L(self):
        #corner: 4 3 7 8, edges: 4 7 12 8
        self.corners[4].orientation, self.corners[7].orientation = (self.corners[4].orientation + 1) % 3, (self.corners[7].orientation + 1) % 3
        self.corners[3].orientation, self.corners[8].orientation = (self.corners[3].orientation - 1) % 3, (self.corners[8].orientation - 1) % 3
        
        self.corners[4], self.corners[3], self.corners[7], self.corners[8] = self.corners[8], self.corners[4], self.corners[3], self.corners[7]
        self.edges[4], self.edges[7], self.edges[12], self.edges[8] = self.edges[8], self.edges[4], self.edges[7], self.edges[12]
    
    def D(self):
        #corner: 5 8 7 6, edges: 9 12 11 10
        self.corners[5], self.corners[8], self.corners[7], self.corners[6] = self.corners[6], self.corners[5], self.corners[8], self.corners[7]
        self.edges[9], self.edges[12], self.edges[11], self.edges[10] = self.edges[10], self.edges[9], self.edges[12], self.edges[11]
    
    def F(self):
        #corner: 3 2 6 7, edges: 3 6 11 7
        self.corners[3].orientation, self.corners[6].orientation = (self.corners[3].orientation + 1) % 3, (self.corners[6].orientation + 1) % 3
        self.corners[2].orientation, self.corners[7].orientation = (self.corners[2].orientation - 1) % 3, (self.corners[7].orientation - 1) % 3
        
        self.edges[3].orientation, self.edges[11].orientation = (self.edges[3].orientation + 1) % 2, (self.edges[11].orientation + 1) %2
        self.edges[6].orientation, self.edges[7].orientation = (self.edges[6].orientation + 1) % 2, (self.edges[7].orientation + 1) %2
        
        self.corners[3], self.corners[2], self.corners[6], self.corners[7] = self.corners[7], self.corners[3], self.corners[2], self.corners[6]
        self.edges[3], self.edges[6], self.edges[11], self.edges[7] = self.edges[7], self.edges[3], self.edges[6], self.edges[11]
    
    def B(self):
        #corner: 1 4 8 5, edges: 1 8 9 5
        self.corners[1].orientation, self.corners[8].orientation = (self.corners[1].orientation + 1) % 3, (self.corners[8].orientation + 1) % 3
        self.corners[4].orientation, self.corners[5].orientation = (self.corners[4].orientation - 1) % 3, (self.corners[5].orientation - 1) % 3
        
        self.edges[1].orientation, self.edges[9].orientation = (self.edges[1].orientation + 1) % 2, (self.edges[9].orientation + 1) %2
        self.edges[5].orientation, self.edges[8].orientation = (self.edges[5].orientation + 1) % 2, (self.edges[8].orientation + 1) %2
        
        self.corners[1], self.corners[4], self.corners[8], self.corners[5] = self.corners[5], self.corners[1], self.corners[4], self.corners[8]
        self.edges[1], self.edges[8], self.edges[9], self.edges[5] = self.edges[5], self.edges[1], self.edges[8], self.edges[9]
    
    def Ur(self):
        #corner: 4 3 2 1, edges: 4 3 2 1
        self.corners[4], self.corners[3], self.corners[2], self.corners[1] = self.corners[1], self.corners[4], self.corners[3], self.corners[2]
        self.edges[4], self.edges[3], self.edges[2], self.edges[1] = self.edges[1], self.edges[4], self.edges[3], self.edges[2]

    def Rr(self):
        #corner: 2 6 5 1, edges: 6 10 5 2
        self.corners[2].orientation, self.corners[5].orientation = (self.corners[2].orientation + 1) % 3, (self.corners[5].orientation + 1) % 3
        self.corners[6].orientation, self.corners[1].orientation = (self.corners[6].orientation - 1) % 3, (self.corners[1].orientation - 1) % 3
        
        self.corners[2], self.corners[6], self.corners[5], self.corners[1] = self.corners[1], self.corners[2], self.corners[6], self.corners[5]
        self.edges[6], self.edges[10], self.edges[5], self.edges[2] = self.edges[2], self.edges[6], self.edges[10], self.edges[5]

    def Lr(self):
        #corner: 8 7 3 4, edges: 8 12 7 4
        self.corners[7].orientation, self.corners[4].orientation = (self.corners[7].orientation + 1) % 3, (self.corners[4].orientation + 1) % 3
        self.corners[8].orientation, self.corners[3].orientation = (self.corners[8].orientation - 1) % 3, (self.corners[3].orientation - 1) % 3
        
        self.corners[8], self.corners[7], self.corners[3], self.corners[4] = self.corners[4], self.corners[8], self.corners[7], self.corners[3]
        self.edges[8], self.edges[12], self.edges[7], self.edges[4] = self.edges[4], self.edges[8], self.edges[12], self.edges[7]
    
    def Dr(self):
        #corner: 6 7 8 5, edges: 10 11 12 9
        self.corners[6], self.corners[7], self.corners[8], self.corners[5] = self.corners[5], self.corners[6], self.corners[7], self.corners[8]
        self.edges[10], self.edges[11], self.edges[12], self.edges[9] = self.edges[9], self.edges[10], self.edges[11], self.edges[12]

    def Fr(self):
        #corner:7 6 2 3, edges: 7 11 6 3
        self.corners[6].orientation, self.corners[3].orientation = (self.corners[6].orientation + 1) % 3, (self.corners[3].orientation + 1) % 3
        self.corners[7].orientation, self.corners[2].orientation = (self.corners[7].orientation - 1) % 3, (self.corners[2].orientation - 1) % 3
        
        self.edges[3].orientation, self.edges[11].orientation = (self.edges[3].orientation + 1) % 2, (self.edges[11].orientation + 1) %2
        self.edges[6].orientation, self.edges[7].orientation = (self.edges[6].orientation + 1) % 2, (self.edges[7].orientation + 1) %2
        
        self.corners[7], self.corners[6], self.corners[2], self.corners[3] = self.corners[3], self.corners[7], self.corners[6], self.corners[2]
        self.edges[7], self.edges[11], self.edges[6], self.edges[3] = self.edges[3], self.edges[7], self.edges[11], self.edges[6]
    
    def Br(self):
        #corner: 5 8 4 1, edges: 5 9 8 1
        self.corners[1].orientation, self.corners[8].orientation = (self.corners[1].orientation + 1) % 3, (self.corners[8].orientation + 1) % 3
        self.corners[4].orientation, self.corners[5].orientation = (self.corners[4].orientation - 1) % 3, (self.corners[5].orientation - 1) % 3
        
        self.edges[1].orientation, self.edges[9].orientation = (self.edges[1].orientation + 1) % 2, (self.edges[9].orientation + 1) %2
        self.edges[5].orientation, self.edges[8].orientation = (self.edges[5].orientation + 1) % 2, (self.edges[8].orientation + 1) %2
        
        self.corners[5], self.corners[8], self.corners[4], self.corners[1] = self.corners[1], self.corners[5], self.corners[8], self.corners[4]
        self.edges[5], self.edges[9], self.edges[8], self.edges[1] = self.edges[1], self.edges[5], self.edges[9], self.edges[8]

    def U2(self):
        #corner: 1-3 4-2, edges: 1-3 4-2
        self.corners[1], self.corners[3], self.corners[4], self.corners[2] = self.corners[3], self.corners[1], self.corners[2], self.corners[4]
        self.edges[1], self.edges[3], self.edges[4], self.edges[2] = self.edges[3], self.edges[1], self.edges[4], self.edges[2]

    def R2(self):
        #corner: 1-6 2-5, edges: 2-10 5-6
        self.corners[1], self.corners[6], self.corners[2], self.corners[5] = self.corners[6], self.corners[1], self.corners[5], self.corners[2]
        self.edges[2], self.edges[10], self.edges[5], self.edges[6] = self.edges[10], self.edges[2], self.edges[6], self.edges[5]
    
    def L2(self):
        #corner: 4-7 3-8, edges: 4-12 7-8
        self.corners[4], self.corners[7], self.corners[3], self.corners[8] = self.corners[7], self.corners[4], self.corners[8], self.corners[3]
        self.edges[4], self.edges[12], self.edges[7], self.edges[8] = self.edges[12], self.edges[4], self.edges[8], self.edges[7]

    def D2(self):
        #corner: 5-7 6-8, edges: 9-11 10-12
        self.corners[5], self.corners[7], self.corners[6], self.corners[8] = self.corners[7], self.corners[5], self.corners[8], self.corners[6]
        self.edges[9], self.edges[11], self.edges[10], self.edges[12] = self.edges[11], self.edges[9], self.edges[12], self.edges[10]
    
    def F2(self):
        #corner: 2-7 3-6, edges: 3-11 6-7
        self.corners[2], self.corners[7], self.corners[3], self.corners[6] = self.corners[7], self.corners[2], self.corners[6], self.corners[3]
        self.edges[3], self.edges[11], self.edges[6], self.edges[7] = self.edges[11], self.edges[3], self.edges[7], self.edges[6]

    def B2(self):
        #corner: 1-8 4-5, edges: 1-9 5-8
        self.corners[1], self.corners[8], self.corners[4], self.corners[5] = self.corners[8], self.corners[1], self.corners[5], self.corners[4]
        self.edges[1], self.edges[9], self.edges[5], self.edges[8] = self.edges[9], self.edges[1], self.edges[8], self.edges[5]


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


r = Rubik()
print(r)
r.move(1)
r.U()
print(r)