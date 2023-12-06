import numpy as np
import matplotlib.pyplot as plt

readTestVerlet = []
testVerlet = []

with open("./testVerlet.part", 'r') as file:
    for line in file:
        if not line.startswith('---'):
            values = [float(val) for val in line.split()[1:]]
            readTestVerlet.append(values)
            continue

for i in range(len(readTestVerlet)):
    if i%2 == 0:
        testVerlet.append(readTestVerlet[i])

readTestEuler = []
testEuler = []

with open("./test.part", 'r') as file:
    for line in file:
        if not line.startswith('---'):
            values = [float(val) for val in line.split()[1:]]
            readTestEuler.append(values)
            continue

for i in range(len(readTestEuler)):
    if i%2 == 0:
        testEuler.append(readTestEuler[i])

x_axis = np.linspace(0,len(testVerlet), len(testVerlet))

testVerlet = np.array(testVerlet)
testEuler = np.array(testEuler)

difference = np.abs(testVerlet-testEuler)

plt.plot(x_axis, difference[:,0], label = "difference x axis")
plt.plot(x_axis, difference[:,1], label = "difference y axis")
plt.plot(x_axis, difference[:,2], label = "difference z axis")
plt.title('Plot of diff btw Euler and Verlet Over Time')
plt.legend(loc="upper left")
plt.savefig("comparison.png")
plt.close()