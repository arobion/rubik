import time

INFINITY = 2147483647
FOUND = "found"
NOT_FOUND = "not found"

class IDA:

    def __init__(self, start, heuristic, get_nexts, pruning):
        self.start = start
        self.start.g = 0
        self.h = heuristic
        self.get_nexts = get_nexts
        self.pruning = pruning

        # if we have pruning table we can set bound to this instead and it will improve the speed a lot
        # self.bound = 9
        self.bound = self.h(self.start)
        self.path = [self.start]
        self.set = set()
        self.nb = 0
    
    def run(self):
        while True:
            tmp = self.search()
            if tmp == FOUND:
                print(self.nb)
                return self.path
            if tmp == INFINITY:
                return NOT_FOUND
            self.bound = tmp
            print(self.bound)
    
    def search(self):
        self.nb += 1
        curr = self.path[-1]

        # optimize idea: precalculate heuristic will reduce time a lot
        h = self.h(curr)
        f = curr.g + h
        if f > self.bound:
            return f
        if h == 0:
            return FOUND
        min = INFINITY

        # optimize idea: change get_nexts() to create next one by one, maybe for i in range and create next base of move i, this will reduce the cost of unused state
        for next in self.get_nexts(curr, self.h):
            if next.state not in self.set:

                # optimize idea: instead of append and pop the path, send state as argument and store parent in node
                self.path.append(next)
                self.set.add(next.state)
                tmp = self.search()
                if tmp == FOUND:
                    return FOUND
                if tmp < min:
                    min = tmp
                    curr = next
                self.path.pop()
                self.set.remove(next.state)
                curr = self.path[-1]
        return min

    def found_in_pruning(self, cost, curr):
        if cost == 0:
            return self.path
        for next in self.get_nexts(curr, self.h):
            if next.compressed in self.pruning.keys():
                new_cost = self.pruning[next.compressed]
                if new_cost < cost:
                    self.path.append(next)
                    return self.found_in_pruning(new_cost, next)
