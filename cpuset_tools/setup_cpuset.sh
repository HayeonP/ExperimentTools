#!/bin/bash

if [ -z "$1" ]
  then
    echo "There is no input argument"
    echo "$ setup_cpuset.sh {number of cpuset}"
    exit
fi

if [[ $(id -u) -ne 0 ]]; then 
	echo "Please run as root"
  exit
fi

number_of_cpuset=$1
cpuset_id=`expr ${number_of_cpuset} - 1`
number_of_cores=`grep -c ^processor /proc/cpuinfo`
end_cpu=`expr ${number_of_cores}`

# sched rt check off
sudo echo -1 > /proc/sys/kernel/sched_rt_runtime_us 

# Root cpuset setup
/bin/echo 1 > /sys/fs/cgroup/cpuset/cpuset.cpu_exclusive
/bin/echo 1 > /sys/fs/cgroup/cpuset/cpuset.sched_load_balance

# sub cpuset setup
printf "=========== CPUSET STATUS ===========\n"
while [ ${cpuset_id} -ge 0 ]; do
  cpuset_name="subset"${cpuset_id}
  end_cpu=`expr ${end_cpu} - 1`
  if [ ${cpuset_id} -ne 0 ]; then 
    start_cpu=${end_cpu}
  else
    start_cpu=0
  fi

  if [ ! -d /sys/fs/cgroup/cpuset/${cpuset_name} ]; then
    mkdir /sys/fs/cgroup/cpuset/${cpuset_name} &> /dev/null
  fi

  /bin/echo 0 > /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.mems
  /bin/echo ${start_cpu}-${end_cpu} > /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.cpus
  /bin/echo 1 > /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.sched_load_balance
  /bin/echo 1 > /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.cpu_exclusive
  /bin/echo 0 > /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.mem_exclusive
  /bin/echo 1 > /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.memory_migrate

  printf "[${cpuset_name}] cpuset.cpus: "
  cat /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.cpus
  printf "[${cpuset_name}] cpuset.cpu_exclusive: "
  cat /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.cpu_exclusive
  printf "[${cpuset_name}] cpuset.sched_load_balance: "
  cat /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.sched_load_balance
  echo "================================="

  cpuset_id=`expr ${cpuset_id} - 1`
done

echo "[STATUS] Move [root] tasks to [subset0]..."
for T in $(cat /sys/fs/cgroup/cpuset/tasks);
do
  ./add_task.sh $T subset0 &> /dev/null    
done
echo "[STATUS] Complete"

exit



# let ros_core_num=$1-2
# let non_ros_core_num=$1-1

# if [[ $(id -u) -ne 0 ]]; then 
# 	echo "Please run as root"
#   exit
# fi

# if [ ! -d /sys/fs/cgroup/cpuset/ros ]; then
#     echo "/sys/fs/cgroup/cpuset/ros does not exist"
#     mkdir /sys/fs/cgroup/cpuset/ros
# fi

# if [ ! -d /sys/fs/cgroup/cpuset/non_ros ]; then
#     echo "/sys/fs/cgroup/cpuset/non_ros does not exist"
#     mkdir /sys/fs/cgroup/cpuset/non_ros
# fi

# sudo echo -1 > /proc/sys/kernel/sched_rt_runtime_us # sched rt check off

# /bin/echo 1 > /sys/fs/cgroup/cpuset/cpuset.cpu_exclusive
# /bin/echo 1 > /sys/fs/cgroup/cpuset/cpuset.sched_load_balance

# /bin/echo 0 > /sys/fs/cgroup/cpuset/ros/cpuset.mems
# /bin/echo 0-$ros_core_num > /sys/fs/cgroup/cpuset/ros/cpuset.cpus
# /bin/echo 1 > /sys/fs/cgroup/cpuset/ros/cpuset.sched_load_balance
# /bin/echo 1 > /sys/fs/cgroup/cpuset/ros/cpuset.cpu_exclusive
# /bin/echo 0 > /sys/fs/cgroup/cpuset/ros/cpuset.mem_exclusive
# /bin/echo 1 > /sys/fs/cgroup/cpuset/ros/cpuset.memory_migrate

# /bin/echo 0 > /sys/fs/cgroup/cpuset/non_ros/cpuset.mems
# /bin/echo $non_ros_core_num > /sys/fs/cgroup/cpuset/non_ros/cpuset.cpus
# /bin/echo 1 > /sys/fs/cgroup/cpuset/non_ros/cpuset.sched_load_balance
# /bin/echo 1 > /sys/fs/cgroup/cpuset/non_ros/cpuset.cpu_exclusive
# /bin/echo 0 > /sys/fs/cgroup/cpuset/non_ros/cpuset.mem_exclusive
# /bin/echo 1 > /sys/fs/cgroup/cpuset/non_ros/cpuset.memory_migrate


# printf "=========== CPUSET STATUS ===========\n"
# printf "[ros] cpuset.mems: "
# cat /sys/fs/cgroup/cpuset/ros/cpuset.mems
# printf "[ros] cpuset.cpus: "
# cat /sys/fs/cgroup/cpuset/ros/cpuset.cpus
# printf "[ros] cpuset.cpu_exclusive: "
# cat /sys/fs/cgroup/cpuset/ros/cpuset.cpu_exclusive
# printf "[ros] cpuset.mem_exclusive: "
# cat /sys/fs/cgroup/cpuset/ros/cpuset.mem_exclusive
# printf "[ros] cpuset.memory_migrate: "
# cat /sys/fs/cgroup/cpuset/ros/cpuset.memory_migrate

# printf "\n"

# printf "[non_ros] cpuset.mems: "
# cat /sys/fs/cgroup/cpuset/non_ros/cpuset.mems
# printf "[non_ros] cpuset.cpus: "
# cat /sys/fs/cgroup/cpuset/non_ros/cpuset.cpus
# printf "[non_ros] cpuset.cpu_exclusive: "
# cat /sys/fs/cgroup/cpuset/non_ros/cpuset.cpu_exclusive
# printf "[non_ros] cpuset.mem_exclusive: "
# cat /sys/fs/cgroup/cpuset/non_ros/cpuset.mem_exclusive
# printf "[non_ros] cpuset.memory_migrate: "
# cat /sys/fs/cgroup/cpuset/non_ros/cpuset.memory_migrate
# printf "=====================================\n"
