class Rubik():
    def __init__(self):
#        self.corners = [rubik_corner(i) for i in range(1, 9)]
#        self.edges = [rubik_edge(i) for i in range(1, 13)]
        self.corners = {i : rubik_corner(i) for i in range(1, 9)}
        self.edges = {i : rubik_edge(i) for i in range(1, 13)}

    def __str__(self):
        ret = "coins:\n"
        ret += "\t{}  {}\t{}  {}\n\t U\t D\n\t{}  {}\t{}  {}\n".format(self.get_corner_by_position(4).final_position, self.get_corner_by_position(1).final_position, self.get_corner_by_position(8).final_position, self.get_corner_by_position(5).final_position, self.get_corner_by_position(3).final_position, self.get_corner_by_position(2).final_position, self.get_corner_by_position(7).final_position, self.get_corner_by_position(6).final_position)
        ret += "aretes:\n"
        ret += "    {}        {}  {}        {}\n   {}  {}                {}  {}\n    {}        {}  {}        {}\n".format(self.get_edge_by_position(1).final_position,self.get_edge_by_position(8).final_position, self.get_edge_by_position(5).final_position, self.get_edge_by_position(9).final_position, self.get_edge_by_position(4).final_position, self.get_edge_by_position(2).final_position, self.get_edge_by_position(12).final_position, self.get_edge_by_position(10).final_position, self.get_edge_by_position(3).final_position, self.get_edge_by_position(7).final_position, self.get_edge_by_position(6).final_position, self.get_edge_by_position(11).final_position)
        return ret

    def get_corner_by_number(self, number):
        for elem in self.corners:
            if number == elem.final_position:
                return elem

    def get_edge_by_number(self, number):
        for elem in self.edges:
            if number == elem.final_position:
                return elem

    def get_corner_by_position(self, position):
        return self.corners[position]

    def get_edge_by_position(self, position):
        return self.edges[position]



class rubik_corner():
    def __init__(self, position):
        self.orientation = 0
#        self.current_position = position
        self.final_position = position

    def __str__(self):
        return "orientation = {}\ncurrent_position = {}\nfinal_position = {}\n".format(self.orientation, self.current_position, self.final_position)


class rubik_edge():
    def __init__(self, position):
        self.orientation = 0
#        self.current_position = position
        self.final_position = position

    def __str__(self):
        return "orientation = {}\ncurrent_position = {}\nfinal_position = {}\n".format(self.orientation, self.current_position, self.final_position)

