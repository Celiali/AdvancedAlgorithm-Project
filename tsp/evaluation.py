import random

N = 50
file = open('input', 'wt')
file.truncate()
file.write(str(N)+"\n")
for i in range(N):
    rand1 = random.uniform(0,1000000)
    rand2 = random.uniform(0,1000000)
    file.write(str(rand1)+" "+str(rand2)+"\n")