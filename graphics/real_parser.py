import numpy as np

# Specify the path to your file
file_path = './testVerlet.part'

# Initialize empty lists to store data
data_list = []

# Read the file and process the lines
with open(file_path, 'r') as file:
    for line in file:
        # Skip lines that start with '---'
        if not line.startswith('---'):
            # Split the line and extract numerical values
            values = [float(val) for val in line.split()[1:]]
            data_list.append(values)
            continue


with open('prova_out.txt', 'w') as file:
    for string in data_list:
        file.write(f"{string}")
