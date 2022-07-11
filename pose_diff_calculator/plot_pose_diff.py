import matplotlib.pyplot as plt
import csv


data_path = 'data/ndt/test.csv'

file = open(data_path)
reader = csv.reader(file)
offset_list = []

for i, row in enumerate(reader):
    if i == 0: continue
    offset_list.append(float(row[2]))

plt.plot(offset_list)
plt.show()
plt.close()