#2 0 4 8 5 3 1 7 9 6
# 215
# 95.0129 61.5432
# 23.1139 79.1937
# 60.6843 92.1813
# 48.5982 73.8207
# 89.1299 17.6266
# 76.2097 40.5706
# 45.6468 93.5470
# 1.8504 91.6904
# 82.1407 41.0270
# 44.4703 89.3650
import math

order = [2,0,4,8,5,3,1,7,9,6]
coord = []
coord.append([95.0129,61.5432])
coord.append([23.1139,79.1937])
coord.append([60.6843,92.1813])
coord.append([48.5982,73.8207])
coord.append([89.1299,17.6266])
coord.append([76.2097,40.5706])
coord.append([45.6468,93.5470])
coord.append([1.8504,91.6904])
coord.append([82.1407,41.0270])
coord.append([44.4703,89.3650])
total = 0.0
for i in range(1,10):
    total += math.sqrt((coord[i][0]-coord[i-1][0]) ** 2 + (coord[i][1]-coord[i-1][1]) ** 2)

print(total)