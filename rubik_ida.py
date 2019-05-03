INFINITY = 2147483647
FOUND = "Found"


class IDA:

    def __init__(self, start, heuristic):
        self.start = start
        self.h = heuristic

        self.bound = self.h(self.start)
        self.path = [self.start]
        self.set = set()
    
    def run(self):
        while True:
            tmp = self.search()
            if tmp == FOUND:
                return self.path
            if tmp == INFINITY:
                return "not found"
            self.bound = tmp
    
    def search(self):
        curr = self.path[-1]
        h = self.h(curr)
        f = curr.g + h
        if f > self.bound:
            return f
        if h == 0:
            return FOUND
        min = INFINITY
        for next in curr.get_nexts():
            if next.state not in self.set:
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



