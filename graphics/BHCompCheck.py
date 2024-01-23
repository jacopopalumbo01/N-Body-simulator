import numpy as np
import matplotlib.pyplot as plt

numPart = 7

readEULER = []
testEULER = []

with open("./test.part", 'r') as file:
    for line in file:
        if not line.startswith('---'):
            values = [float(val) for val in line.split()[1:]]
            readEULER.append(values)
            continue

for i in range(len(readEULER)):
    if i%numPart == 0:
        testEULER.append(readEULER[i])

readBH = []
testBH = []

with open("./testBH.part", 'r') as file:
    for line in file:
        if not line.startswith('---'):
            values = [float(val) for val in line.split()[1:]]
            readBH.append(values)
            continue

for i in range(len(readBH)):
    if i%numPart == 0:
        testBH.append(readBH[i])

x_axis = np.linspace(0,len(testBH), len(testBH))

testEULER = np.array(testEULER)
testBH = np.array(testBH)

difference = np.abs(testBH-testEULER)

plt.plot(x_axis, difference[:,0], label = "difference x axis")
plt.plot(x_axis, difference[:,1], label = "difference y axis")
plt.plot(x_axis, difference[:,2], label = "difference z axis")
plt.title('Plot of diff btw direct-sum and BH computation on part 1 Over Time')
plt.legend(loc="upper left")
plt.savefig("IsBHgood.png")
plt.close()