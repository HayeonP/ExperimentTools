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

def plot_e2e_and_pose_diff_by_stamp():

    with open('autoware_analyzer.yaml') as f:
        data = yaml.load(f, yaml.FullLoader)
        pose_diff_path = data['pose_diff_path']
        e2e_response_time_path = data['e2e_response_time_path']


    pose_diff_stamp_list = []
    pose_diff_list = []

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

    e2e_response_start = -1.0
    with open(e2e_response_time_path) as f:
        reader = csv.reader(f)
        for i,  line in enumerate(reader):
            if i==0: continue
            # Assign response time to end time
            stamp = float(line[1])
            e2e_response = float(line[3])*1000
            e2e_response_stamp_list.append(stamp)
            e2e_response_list.append(e2e_response)
    
    
    # Calculate Offset
    stamp_offset = pose_diff_stamp_list[0] - e2e_response_stamp_list[0]

    for i, pose_stamp in enumerate(pose_diff_stamp_list):
        pose_diff_stamp_list[i] = pose_stamp - stamp_offset


    # if stamp_offset < 0: # if Autoawre PC is powered on first
    #     for pose_stamp in pose_diff_stamp_list:
    #         pose_stamp = pose_stamp + stamp_offset
    # else: # if simulation PC is powered on first
    #     for e2e_stamp in e2e_response_stamp_list:
    #         e2e_stamp = e2e_stamp - stamp_offset

    
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
        
def plot_e2e_and_pose_diff_by_instance():

    with open('autoware_analyzer.yaml') as f:
        data = yaml.load(f, yaml.FullLoader)
        pose_diff_path = data['pose_diff_path']
        e2e_response_time_path = data['e2e_response_time_path']
        pose_diff_ylim = data['pose_diff_ylim']
        e2e_response_ylim = data['e2e_response_time_ylim']

    pose_diff_instance_list = []
    pose_diff_list = []

    with open(pose_diff_path) as f:
        reader = csv.reader(f)
        
        for i, line in enumerate(reader):
            if i == 0: continue
            instance = float(line[4])
            
            pose_diff = abs(float(line[2]))
            pose_diff_instance_list.append(instance)
            pose_diff_list.append(pose_diff)

    pose_diff_avg = sum(pose_diff_list)/len(pose_diff_list)

    e2e_response_instance_list = []
    e2e_response_list = []

    e2e_response_start = -1.0
    with open(e2e_response_time_path) as f:
        reader = csv.reader(f)
        for i,  line in enumerate(reader):
            if i==0: continue
            # Assign response time to end time
            instance = float(line[2])
            e2e_response = float(line[3])*1000
            e2e_response_instance_list.append(instance)
            e2e_response_list.append(e2e_response)
    
    e2e_response_avg = sum(e2e_response_list)/len(e2e_response_list)

    ax1 = plt.subplot()
    ax1.set_ylabel('E2E response time(ms)')
    ax1.set_xlabel('Instance')    
    lns1= ax1.plot(e2e_response_instance_list, e2e_response_list, '-r', label='E2E reponse time')
    ax1.plot(e2e_response_instance_list, [e2e_response_avg for i in range(len(e2e_response_instance_list))], ':r')
    ax1.set_ylim(e2e_response_ylim)

    ax2 = ax1.twinx()    
    ax2.set_ylabel('Pose difference(m)')
    lns2 = ax2.plot(pose_diff_instance_list, pose_diff_list, '-b', label='pose_diff')
    ax2.plot(pose_diff_instance_list, [pose_diff_avg for i in range(len(pose_diff_instance_list))], ':b')
    ax2.set_ylim(pose_diff_ylim)

    lns = lns1+lns2
    labs = [l.get_label() for l in lns]
    ax1.legend(lns, labs, loc='upper left')

    # plt.show()
    plt.savefig('./results/result.png')
    plt.close()


if __name__ == '__main__':
    calculate_e2e_response_time()
    plot_e2e_and_pose_diff_by_instance()