import matplotlib.pyplot as plt
import csv

class MemoryBandwidth:
    def __init__(self):
        self.type = 'none'
        self.elapsed_time = [] # sec
        self.bandwidth = [] # GB/s

def main():
    filepath_list_list= [[   '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_single-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_single-memset.csv',
                        '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_omp-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_omp-memset.csv'],
                    
                    [   '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_single-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_single-memset.csv',
                        '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_omp-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_omp-memset.csv'],
                    
                    [   '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_single-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_single-memset.csv',
                        '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_omp-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_omp-memset.csv'],
                    
                    [   '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_single-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_single-memset.csv',
                        '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_omp-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_omp-memset.csv'],
                    
                    [   '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_single-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_single-memset.csv',
                        '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_omp-loop.csv',
                        '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_omp-memset.csv'] 
                    ]
    
    for filepath_list in filepath_list_list:
        memory_bandwidth_list = []

        for filepath in filepath_list:
            memory_bandwidth = MemoryBandwidth()
            f = open(filepath)
            reader = csv.reader(f)
            next(reader)
            
            for row in reader:
                if memory_bandwidth.type == 'none':
                    memory_bandwidth.type = row[0]
                memory_bandwidth.elapsed_time.append(float(row[1]))
                memory_bandwidth.bandwidth.append(float(row[2]))
            
            memory_bandwidth_list.append(memory_bandwidth)

        for i in range(len(memory_bandwidth_list)):
            memory_bandwidth = memory_bandwidth_list[i]
            plt.plot(memory_bandwidth.elapsed_time[5:], label=memory_bandwidth.type, linewidth=0.5)
        
        plt.legend()
        plt.title(filepath_list[0].split('/')[3]+' elapsed time')
        plt.xlabel('Iteration')
        plt.ylabel('Elapsed time(sec)')
        plt.savefig(filepath_list[0].split('/')[3]+'_elapsed_time.png')
        plt.close()
        
        for i in range(len(memory_bandwidth_list)):
            memory_bandwidth = memory_bandwidth_list[i]
            plt.plot(memory_bandwidth.bandwidth[5:], label=memory_bandwidth.type, linewidth=0.5)
        
        plt.legend()
        plt.title(filepath_list[0].split('/')[3]+ ' bandwidth')
        plt.xlabel('Iteration')
        plt.ylabel('Bandwidth(GB/s)')
        plt.savefig(filepath_list[0].split('/')[3]+'_bandwidth.png')
        plt.close()
    
    #######################
    
    filepath_list_list= [[  '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_single-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_single-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_single-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_single-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_single-loop.csv'],
                         
                         [  '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_single-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_single-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_single-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_single-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_single-memset.csv'],
                         
                         [  '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_omp-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_omp-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_omp-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_omp-loop.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_omp-loop.csv'],
                         
                         [  '../results/220531_memory_bandwidth_test/android_none/memory_bandwidth_omp-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_single-loop/memory_bandwidth_omp-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_single-memset/memory_bandwidth_omp-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-loop/memory_bandwidth_omp-memset.csv',
                            '../results/220531_memory_bandwidth_test/android_omp-memset/memory_bandwidth_omp-memset.csv']
                    ]
    
    for filepath_list in filepath_list_list:
        memory_bandwidth_list = []

        for filepath in filepath_list:
            memory_bandwidth = MemoryBandwidth()
            f = open(filepath)
            reader = csv.reader(f)
            next(reader)
            
            for row in reader:
                if memory_bandwidth.type == 'none':
                    memory_bandwidth.type = row[0]
                memory_bandwidth.elapsed_time.append(float(row[1]))
                memory_bandwidth.bandwidth.append(float(row[2]))
            
            memory_bandwidth_list.append(memory_bandwidth)

        for i in range(len(memory_bandwidth_list)):
            memory_bandwidth = memory_bandwidth_list[i]
            plt.plot(memory_bandwidth.elapsed_time[5:], label=filepath_list[i].split('/')[3], linewidth=0.5)
        
        plt.legend()
        plt.title(filepath_list[0].split('/')[-1].split('.')[0] + ' elapsed time')
        plt.xlabel('Iteration')
        plt.ylabel('Elapsed time(sec)')
        plt.savefig(filepath_list[0].split('/')[-1].split('.')[0]+'_elapsed_time.png')
        plt.close()
        
        for i in range(len(memory_bandwidth_list)):
            memory_bandwidth = memory_bandwidth_list[i]
            plt.plot(memory_bandwidth.bandwidth[5:], label=filepath_list[i].split('/')[3], linewidth=0.5)
        
        plt.legend()
        plt.title(filepath_list[0].split('/')[-1].split('.')[0]+ ' bandwidth')
        plt.xlabel('Iteration')
        plt.ylabel('Bandwidth(GB/s)')
        plt.savefig(filepath_list[0].split('/')[-1].split('.')[0]+'_bandwidth.png')
        plt.close()

    return



if __name__ == '__main__':
    main()