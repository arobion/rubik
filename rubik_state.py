from rubik_cubes import Rubik

class rubik_state():
    def __init__(self, Rubik, parent, instruction):
        self.edges = parent.edges.copy()
        self.corners = parent.corners.copy()
        self.instruction = instruction
        Rubik.move(instruction, self)

        self.g = parent.g + 1
#        self.h = Rubik.heuristic_manhattan(self)
#        self.f = self.g + self.h

        self.state = self.construct_state()

    def construct_state(self):
        pass

