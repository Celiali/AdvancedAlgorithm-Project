import random

N = 1000
print(N)
for i in range(N):
    rand1 = random.uniform(0,1000000)
    rand2 = random.uniform(0,1000000)
    print(str(rand1)+" "+str(rand2))