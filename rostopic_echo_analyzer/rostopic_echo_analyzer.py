import yaml
import csv
import matplotlib.pyplot as plt

def export_legend(legend, filename="legend.png"):
    fig  = legend.figure
    fig.canvas.draw()
    bbox  = legend.get_window_extent().transformed(fig.dpi_scale_trans.inverted())
    fig.savefig(filename, dpi="figure", bbox_inches=bbox)

def create_csv(topic_name, data_list):
    # Load yamls
    with open('rostopic_echo_analyzer.yaml') as f:
        data = yaml.load(f, yaml.FullLoader)
        node_paths = data['node_paths']
        e2e_response_time_path = data['e2e_response_time_path']

    for data_path in data_list:
        with open(data_path)

    return

def main():
    data_list = ['data/hz_core_0_3_4_6.csv', 'data/hz_core_0_3.csv', 'data/hz_core_0.csv']
    # plot_graph('twist_cmd', data_list)

    return

if __name__ == '__main__':
    main()