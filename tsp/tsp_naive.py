import sys
from math import sqrt


def dist(p1, p2):
	return int(sqrt((p2[0] - p1[0])**2 + (p2[1] - p1[1])**2 ))


def greedy_tour(nodes):
	tour = [0]
	used = [True]
	for _ in range(len(nodes)-1):
		used.append(False)
	print(len(used), " ", used)
	for i in range(1, len(nodes)):
		best = -1
		for j in range(len(nodes)):
			print(i, " ", j, " best:", best, "D1:", dist(nodes[i - 1], nodes[j]), "D2:", dist(nodes[i - 1], nodes[best]))
			if not used[j] and (best == -1 or dist(nodes[i-1], nodes[j]) < dist(nodes[i-1], nodes[best])):
				best = j

		tour.append(best)
		used[best] = True
	return tour


f = open("input", "r")
nodes = []
for line in f.readlines():

	if " " in line:
		position = line.split(" ")
		x, y = float(position[0]), float(position[1])
		nodes.append((x, y))
print(greedy_tour(nodes))

# # input and output for Kattis
# for input in sys.stdin:
# 	nodes = int(input)
#
#     M = [int(input)]
#     # use trivial division first to find small prime factors first
#     trivial_div(M, prime_table)
#
#     # if the last one is prime number, then output
#     if miller_rabin(M[-1]) is True:
#         for factor in M:
#             print(factor)
#         print()
#         continue
#
#     # if it's too long, then print fail
#     if len(str(M[-1])) > 25:
#         print("fail")
#         print()
#         continue
#
#     # then use pollard brent to find big factors
#     big_factor = [M.pop()]
#     brent(big_factor)
#     for factor in M + big_factor:
#         print(factor)
#     print()