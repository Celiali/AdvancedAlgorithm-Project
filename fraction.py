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
def pollard(N):
    a = random.randint(1, N)
    x = a
    y = a
    fraction_set = set()
    # c = 1
    # while True:
    for i in range(1000000):
        x = randGen(x, N)
        y = randGen(randGen(y, N), N)
        if x!=y:
            # d = fractions.gcd(abs(x-y), N)
            d = math.gcd(int(abs(x-y)), N)
            if (d > 1) and (d<N):
                return d
                # fraction_set.add(d)
                # print(d)
        else:
            x = random.randint(1,N)
            y = x

# 试除法调用的一个子函数
def extract(mlist, small_prime):
    for i in mlist:
        if i % small_prime == 0 and i != small_prime:
            mlist.remove(i)
            mlist.append(int(small_prime))
            mlist.append(int(i / small_prime))
            extract(mlist, small_prime)

# 试除
def trival_div(mlist, pri_table):
    for i in pri_table:
        extract(mlist, i)

# print(pollard(1681))