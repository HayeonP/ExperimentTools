import csv
import matplotlib.pyplot as plt

def export_legend(legend, filename="legend.png"):
    fig  = legend.figure
    fig.canvas.draw()
    bbox  = legend.get_window_extent().transformed(fig.dpi_scale_trans.inverted())
    fig.savefig(filename, dpi="figure", bbox_inches=bbox)

def plot_graph(topic_name, data_list):

    for data_path in data_list:
        data_name = data_path.split('/')[-1].split('.')[0]

        file = open(data_path)
        reader = csv.reader(file, delimiter=' ')

        data = []
        
        for i, row in enumerate(reader):
            if i == 0: topic = row[2]
            if 'rate:' not in row:                
                continue
            data.append(float(row[2]))
        
        avg = sum(data)/len(data)
        avg_data = [avg for i in range(len(data))]

        plt.plot(data, label=data_name)
        # plt.plot(avg_data, label='avg_'+data_name)
    
    legend = plt.legend()
    export_legend(legend, 'results/'+topic_name+'_legend.png')
    legend.remove()
    plt.title("/twist_cmd frequency")
    plt.xlabel('iteration')
    plt.ylabel('frequency(hz)')
    plt.savefig('results/'+topic_name+'.png')
    plt.close()

    return

def main():
    data_list = ['data/hz_core_0_3_4_6.csv', 'data/hz_core_0_3.csv', 'data/hz_core_0.csv']
    plot_graph('twist_cmd', data_list)

    return

if __name__ == '__main__':
    main()