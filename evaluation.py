import fraction
import random
import time
import matplotlib.pyplot as plt

def generateTesting(fromN,toN,Amount):
    data = []
    for i in range(Amount):
        data.append(random.randint(fromN,toN))
    return data

def testing(data,Brent=True):
    start = time.time()
    # print("Start: " + str(start))
    for i in data:
        M = [i]
        fraction.trivial_div(M, fraction.prime_table)
        # if the last one is prime number, then finish
        if fraction.miller_rabin(M[-1]) is True:
            continue
        # else use brent/pollard to factorize
        big_factor = [M.pop()]
        if Brent:
            fraction.brent(big_factor)
        else:
            fraction.pollard(big_factor)
    stop = time.time()
    # print("Stop: " + str(stop))
    print("Time:" + str((stop - start)/len(data)) + "seconds")
    return (stop - start)/len(data)

def drawing():
    magnitude = []
    time1 = []
    time2 = []

    for i in range(28):
        if i == 0:
            continue
        if i == 1:
            data = generateTesting(10 ** i, 10 ** (i + 1), 10)
            time1.append(testing(data))
            time2.append(testing(data, False))
            magnitude.append(i + 1)
            continue
        data = generateTesting(10 ** i, 10 ** (i + 1), 500)
        time1.append(testing(data))
        time2.append(testing(data, False))
        magnitude.append(i + 1)
    l1 = plt.plot(magnitude, time1, label='Brent')
    l2 = plt.plot(magnitude, time2, label='Pollard')
    plt.legend(loc='upper right')
    plt.plot()
    plt.xlabel('Magnitude (digit)')
    plt.ylabel('Time (second)')
    plt.show()

drawing()