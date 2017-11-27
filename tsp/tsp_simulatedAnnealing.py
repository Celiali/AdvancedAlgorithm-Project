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
        selectedPos = random.randint(0, len(newNodes)-1)
        selected = newNodes[selectedPos]
        newNodes.remove(selected)
        newPos = random.randint(0, len(newNodes)-1)
        newNodes.insert(newPos, selected)
        newState = State()
        newState.nodes = newNodes
        return newState
    def evaluation(self):
        distance = 0.0
        for i in range(len(self.nodes)-1):
            distance += math.sqrt((self.nodes[i+1].x - self.nodes[i].x)**2 + (self.nodes[i+1].y - self.nodes[i].y)**2)
        return distance

def simulatedAnnealing(state: State, SAprocess, temperature, Tmin = 0.01, T = 10.0, r = 0.8):
    originalEval = state.evaluation()
    originalState = state
    for i in range(3):
        while T > Tmin:
            secondState = originalState.getRandomNewState()
            secondEval = secondState.evaluation()
            dE = originalEval - secondEval
            if dE >= 0: # accept this state
                originalEval = secondEval
                originalState = secondState
                SAprocess.append(originalEval)
                temperature.append(T)
            else:
                if math.exp(dE/T) > random.uniform(0,1):
                    originalEval = secondEval
                    originalState = secondState
                    SAprocess.append(originalEval)
                    temperature.append(T)
            T = r * T
        T = 40/(i+1)
    return originalState

# input and output
lineNumber = 0
state = State()

# for line in sys.stdin:
file = open("input")
for line in file:
    if lineNumber == 0:
        nodeNumber = 0
        try:
            nodeNumber = int(line)
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

SAprocess = []
temperature = []
newState = simulatedAnnealing(state, SAprocess, temperature)
for node in newState.nodes:
    print(node.number)