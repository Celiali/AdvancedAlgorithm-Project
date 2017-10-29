import random
import math
# import fractions
import time

# 用的别人的miller，只是为了验证逻辑正确性，后面需要改掉
def miller_rabin(n, k=10):
    if n == 2:
        return True
    if not n & 1:
        return False

    def check(a, s, d, n):
        x = pow(a, d, n)
        if x == 1:
            return True
        for i in range(s - 1):
            if x == n - 1:
                return True
            x = pow(x, 2, n)
        return x == n - 1

    s = 0
    d = n - 1

    while d % 2 == 0:
        d >>= 1
        s += 1

    for i in range(k):
        a = random.randint(2, n - 1)
        if not check(a, s, d, n):
            return False
    return True

prime_table = (2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79)

def randGen(x, N):
    return (x**2 + 1) % N

# pollard
# input a list contains the original factor
# operate with the original list
def pollard(N):
    for element in N:
        if miller_rabin(element) is not True:
            N.remove(element)
            a = random.randint(1, element)
            x = a
            y = a
            # c = 1
            # while True:
            for i in range(1000000):
                x = randGen(x, element)
                y = randGen(randGen(y, element), element)
                if x!=y:
                    # d = fractions.gcd(abs(x-y), N)
                    d = math.gcd(int(abs(x-y)), element)
                    if (d > 1) and (d<element):
                        # return d
                        N.append(d)
                        N.append(element//d)
                        pollard(N)
                        return 1
                        # fraction_set.add(d)
                        # print(d)
                else:
                    x = random.randint(1,element)
                    y = x
    return 0

# 试除法调用的一个子函数
def extract(mlist, small_prime):
    for i in mlist:
        if i % small_prime == 0 and i != small_prime:
            mlist.remove(i)
            mlist.append(int(small_prime))
            mlist.append(int(i // small_prime))
            extract(mlist, small_prime)

# 试除
def trival_div(mlist, pri_table):
    for i in pri_table:
        extract(mlist, i)

M = [5794746215675376587969763525444444657]
# M=[807855320741025594307788028083709]
trival_div(M, prime_table)

big_factor = [M.pop()]
print(pollard(big_factor))
pollard(big_factor)
print(M+big_factor)
