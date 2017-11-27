import fraction
prime_table = []

for i in range(2, 500000):
    if fraction.miller_rabin(i):
        prime_table.append(i)

print(prime_table)