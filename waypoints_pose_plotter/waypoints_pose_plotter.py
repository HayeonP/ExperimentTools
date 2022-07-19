import csv
import matplotlib.pyplot as plt
import rospy
import rosbag
from geometry_msgs.msg import PoseStamped

def mouse_event(event):
    print('x: {} and y: {}'.format(event.xdata, event.ydata))

if __name__ == '__main__':
    rosbag_path = 'data/test_gnss_pose.bag'

    with open('data/cubetown_waypoints.csv') as f:
        reader = csv.reader(f)

        waypoints_x = []
        waypoints_y = []
        
        for i, line in enumerate(reader):
            if i == 0: continue
            waypoints_x.append(float(line[0]))
            waypoints_y.append(float(line[1]))

    pose_x = []
    pose_y = []

    with rosbag.Bag(rosbag_path) as bag:
        for topic, msg, ts in bag.read_messages(topics='/gnss_pose'):
            pose_x.append(msg.pose.position.x)
            pose_y.append(msg.pose.position.y)

    fig = plt.figure()
    cid = fig.canvas
    cid = fig.canvas.mpl_connect('button_press_event', mouse_event)

    plt.plot(waypoints_x, waypoints_y, label='Center line')
    plt.plot(pose_x, pose_y, label='Ego position')

    plt.legend()
    plt.show()

    plt.close()