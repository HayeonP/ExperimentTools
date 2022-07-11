import yaml
import csv
import matplotlib.pyplot as plt

def calculate_e2e_response_time(): #e2e reponse time
    # Load yamls
    with open('autoware_analyzer.yaml') as f:
        data = yaml.load(f, yaml.FullLoader)
        node_paths = data['node_paths']
        e2e_response_time_path = data['e2e_response_time_path']

    first_node_path = list(node_paths.items())[0][1]
    last_node_path = list(node_paths.items())[-1][1]

    e2e_response_time_data = [] # start, end, instance

    # Update last node
    with open(last_node_path) as f:
        reader = csv.reader(f)
        prev_instance = -1
        for i, row in enumerate(reader):
            if i == 0: continue

            end = float(row[3])
            activation = int(row[5])
            instance = int(row[4])
            
            # TODO: BUG - instance id is replicated!
            if instance == prev_instance: continue

            if activation == 0: continue # Skip actvation is 0
            line = [-1, end, instance] # start, -1, instance
            e2e_response_time_data.append(line)

            prev_instance = instance

    # Update first node
    with open(first_node_path) as f:
        reader = csv.reader(f)
        prev_instance = -1

        it = iter(e2e_response_time_data)
        target = it.__next__()
        last_instance = e2e_response_time_data[-1][2]
        for i, row in enumerate(reader):
            if i == 0: continue
            start = float(row[2])
            instance = int(row[4])
            actvation = int(row[5])
            
            if instance > last_instance: break

            target_instance = target[2]
            if target_instance != instance: continue            
            target[0] = start
            response_time = target[1] - target[0]
            target.append(response_time)
            try: target = it.__next__()
            except StopIteration as e: break
    
    with open(e2e_response_time_path, 'w') as f:
        writer = csv.writer(f)
        for line in e2e_response_time_data:
            writer.writerow(line)

    return 0

def plot_e2e_and_pose_diff():

    with open('autoware_analyzer.yaml') as f:
        data = yaml.load(f, yaml.FullLoader)
        pose_diff_path = data['pose_diff_path']
        e2e_response_time_path = data['e2e_response_time_path']

    pose_diff_stamp_list = []
    pose_diff_list = []
    print(pose_diff_path)
    with open(pose_diff_path) as f:
        reader = csv.reader(f)
        for i, line in enumerate(reader):
            if i == 0: continue
            stamp = float(line[0])
            
            pose_diff = abs(float(line[2]))
            pose_diff_stamp_list.append(stamp)
            pose_diff_list.append(pose_diff)
    
    e2e_response_stamp_list = []
    e2e_response_list = []
    with open(e2e_response_time_path) as f:
        reader = csv.reader(f)
        for i,  line in enumerate(reader):
            if i==0: continue
            # Assign response time to end time
            stamp = float(line[1])
            e2e_response = float(line[3])*1000
            e2e_response_stamp_list.append(stamp)
            e2e_response_list.append(e2e_response)
    
    
    ax1 = plt.subplot()
    ax1.set_ylabel('E2E response time(ms)')
    ax1.set_xlabel('Time stamp(s)')    
    lns1= ax1.plot(e2e_response_stamp_list, e2e_response_list, '-r', label='E2E reponse time')

    ax2 = ax1.twinx()    
    ax2.set_ylabel('Pose difference(m)')
    lns2 = ax2.plot(pose_diff_stamp_list, pose_diff_list, '-b', label='pose_diff')

    

    lns = lns1+lns2
    labs = [l.get_label() for l in lns]
    ax1.legend(lns, labs, loc='upper left')

    plt.show()
    plt.close()
        

if __name__ == '__main__':
    calculate_e2e_response_time()
    plot_e2e_and_pose_diff()