import math
import random
import sys
import fileinput

class Node:
    def __init__(self, x, y, number):
        self.x = x
        self.y = y
        self.number = number

class State:
    def __init__(self):
        self.nodes = []
    def addNode(self, node:Node):
        self.nodes.append(node)
    def getRandomNewState(self):
        newNodes = self.nodes.copy()
        l = random.randint(0, len(newNodes)-1)
        i = random.randint(0, len(newNodes)-1)
        newNodes[i:(i + l)] = reversed(newNodes[i:(i + l)])
        # selectedPos = random.randint(0, len(newNodes)-1)
        # selected = newNodes[selectedPos]
        # newNodes.remove(selected)
        # newPos = random.randint(0, len(newNodes)-1)
        # newNodes.insert(newPos, selected)
        newState = State()
        newState.nodes = newNodes
        return newState
    def evaluation(self):
        distance = 0.0
        for i in range(len(self.nodes)-1):
            distance += int(round(math.sqrt((self.nodes[i+1].x - self.nodes[i].x) ** 2 + (self.nodes[i+1].y - self.nodes[i].y) ** 2)))
        distance += int(round(math.sqrt((self.nodes[0].x - self.nodes[len(self.nodes)-1].x) ** 2 + (self.nodes[0].y - self.nodes[len(self.nodes)-1].y) ** 2)))
        return distance

def euclideanDistance(node1: Node, node2: Node):
    return int(round(math.sqrt((node1.x - node2.x) ** 2 + (node1.y - node2.y) ** 2)))


def simulatedAnnealing(state: State, Tmin = 0.01, T = 100.0, r = 0.9999, stop_iteration = 100000):
    originalEval = state.evaluation()
    originalState = state
    iter = 0
    for i in range(3):
        while T > Tmin:
            secondState = originalState.getRandomNewState()
            secondEval = secondState.evaluation()
            if iter >= stop_iteration:
                break
            iter += 1
            dE = originalEval - secondEval
            print(secondEval)
            if dE >= 0: # accept this state
                originalEval = secondEval
                originalState = secondState
            else:
                if math.exp(dE/T) > random.uniform(0,1):
                    originalEval = secondEval
                    originalState = secondState
            T = r * T
        T = 40/(i+1)
    return originalState

# input and output
lineNumber = 0
nodeNumber = 0
state = State()

# for line in sys.stdin:
file = open("input")
for line in file:
    if lineNumber == 0:
        try:
            nodeNumber = int(round(float(line)))
        except ValueError:
            raise Exception("e1")
    else:
        coordinate = line.split(' ')
        coordinatex = 0.0
        coordinatey = 0.0
        try:
            coordinatex = float(coordinate[0])
            coordinatey = float(coordinate[1])
        except ValueError:
            raise Exception("e2")
        state.addNode(Node(coordinatex,coordinatey,lineNumber-1))
    lineNumber += 1
    if len(state.nodes) >= nodeNumber:
        break

if nodeNumber == 1:
    for node in state.nodes:
        print(node.number)
else:
    random.shuffle(state.nodes)
    newState = simulatedAnnealing(state)
    print("final:")
    print(newState.evaluation())
    for node in newState.nodes:
        print(node.number)