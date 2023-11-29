import numpy as np
import re

with open('example.txt') as f:
    lines = f.readlines()

result_list = []

for i in range(len(lines)):
    if("PART" in lines[i]):
        matches = re.findall(r'\{([^}]+)\}', lines[i])
        result_list.append([float(value) for match in matches for value in match.split(' ')])
        print(result_list)


with open('prova_out.txt', 'w') as file:
    for string in result_list:
        file.write(f"{string}")
