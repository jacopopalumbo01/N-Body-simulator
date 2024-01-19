import numpy as np
from matplotlib import pyplot as plt
import matplotlib.animation
import pandas as pd
import ast

# array a size must be equal to N*Npart, where N is how many timestep you want and N_part the # of particles



with open('prova_out.txt') as f:
    input_string = f.readlines()

N = 168
N_part = 256

input_string = input_string[0]

# Add commas between the sublists and wrap the entire string in square brackets
formatted_string = "[" + input_string.replace("][", "], [") + "]"

# Convert the formatted string to a list of lists
result_list_of_lists = ast.literal_eval(formatted_string)

# Convert the list of lists to a NumPy array
result_array = np.array(result_list_of_lists)

a = result_array

a[0][0] = 30000
a[0][1] = 30000
a[0][2] = 30000
a[1][0] = -30000
a[1][1] = -30000
a[1][2] = -30000

print(a)

"""
N = 50
N_part = 5

#To have random numbers
a = np.random.rand(N*N_part, 3)*30
a[0] = [100,100,100]

#print(a)

#a = np.array([[10,20,30],[-10,-20,-30],[1,2,3],[4,5,6],[5,6,7],[7,6,5],[6,5,4],[5,4,3],[4,3,2],[3,2,1],[4,3,7],[8,6,2],[6,2,8],[7,6,2],[5,3,6]])

a =
[1,2,3
2,3,4
3,4,5
4,5,6
etc]

t timespan
"""

t = np.array([np.ones(N_part)*i for i in range(N)]).flatten()
df = pd.DataFrame({"time": t ,"x" : a[:,0], "y" : a[:,1], "z" : a[:,2]})

def update_graph(num):
    data=df[df['time']==num]
    graph._offsets3d = (data.x, data.y, data.z)
    title.set_text('N-Body particle simulator, time={}'.format(num))


fig = plt.figure(figsize=(8,8))
ax = fig.add_subplot(111, projection='3d')
title = ax.set_title('N-Body particle simulator')

data=df[df['time']==0]
graph = ax.scatter(data.x, data.y, data.y)

ani = matplotlib.animation.FuncAnimation(fig, update_graph, (N-1),
                               interval=100, blit=False)

ani.save("N-Body-simulator.mp4")
