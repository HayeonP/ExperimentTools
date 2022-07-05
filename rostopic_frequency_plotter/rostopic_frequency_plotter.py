import csv
import matplotlib.pyplot as plt

def main():
    data_path = './data/hz.csv'
    # data_path = './data/test.csv'
    file = open(data_path)
    reader = csv.reader(file, delimiter=' ')

    data = []
    
    for i, row in enumerate(reader):
        if i == 0: topic = row[2]
        if i%2 != 1: continue
        data.append(float(row[2]))
    
    avg = sum(data)/len(data)
    avg_data = [avg for i in range(len(data))]

    plt.plot(data, label=topic)
    plt.plot(avg_data, label='avg')
    plt.legend()
    plt.xlabel('iteration')
    plt.ylabel('frequency')
    plt.show()
    plt.close()

    return

if __name__ == '__main__':
    main()