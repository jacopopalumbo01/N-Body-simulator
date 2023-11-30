import numpy as np
import matplotlib.pyplot as plt
import ast


with open('prova_out.txt') as f:
    input_string = f.readlines()

input_string = input_string[0]

# Add commas between the sublists and wrap the entire string in square brackets
formatted_string = "[" + input_string.replace("][", "], [") + "]"

# Convert the formatted string to a list of lists
result_list_of_lists = ast.literal_eval(formatted_string)

# Convert the list of lists to a NumPy array
result_array = np.array(result_list_of_lists)

a = result_array
b = []
c = []
d = []

##### 0 stands for X, 1 for Y, 2 for Z
for i in range(len(a)):
    if i % 2 == 0:
        b.append(a[i,0])
        c.append(a[i,1])
        d.append(a[i,2])

##### numero di iterazioni
N = len(b)
time = np.linspace(0,N,N)

# Plot the data
plt.plot(time, b[:])
plt.title('Plot of X Over Time')
plt.savefig("provaX.png")
plt.close()

# Plot the data
plt.plot(time, c[:])
plt.title('Plot of Y Over Time')
plt.savefig("provaY.png")
plt.close()

# Plot the data
plt.plot(time, d[:])
plt.title('Plot of Z Over Time')
plt.savefig("provaZ.png")
plt.close()