#!/bin/bash

while (( "$#" )); do
    case "$1" in
      -h|--help)
        echo "[Options]"
        echo "   -s | --status {target_cpuset  Print status of target cpuset"
        echo "   -t | --tasks {target_cpuset}  Print tasks in target cpuset"
        exit 1
        ;;
      -l|--list)
        echo "==========[Cpuset List]=========="
        echo " "
        for f in /sys/fs/cgroup/cpuset/*; do          
          if [ -d "$f" ]; then
            cpuset_name=$f
           printf "[${cpuset_name}] cpuset.cpus: "
            cat ${cpuset_name}/cpuset.cpus
            printf "[${cpuset_name}] cpuset.cpu_exclusive: "
            cat ${cpuset_name}/cpuset.cpu_exclusive
            printf "[${cpuset_name}] cpuset.sched_load_balance: "
            cat ${cpuset_name}/cpuset.sched_load_balance
            echo " "
          fi
        done
        echo "================================"
        shift 1
        ;;
      -s|--status)
        if [ -n "$2" ] && [ ${2:0:1} != "-" ]; then
          echo "================================="
          cpuset_name=$2
          printf "[${cpuset_name}] cpuset.cpus: "
          cat /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.cpus
          printf "[${cpuset_name}] cpuset.cpu_exclusive: "
          cat /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.cpu_exclusive
          printf "[${cpuset_name}] cpuset.sched_load_balance: "
          cat /sys/fs/cgroup/cpuset/${cpuset_name}/cpuset.sched_load_balance
          echo "================================="
          shift 2
        else
          echo "[Error] Argument for $1 is missing" >&2
          exit 1
        fi
        ;;
      -t|--tasks)
        if [ -n "$2" ] && [ ${2:0:1} != "-" ]; then
          cpuset_name=$2
          cat /sys/fs/cgroup/cpuset/${cpuset_name}/tasks          
          shift 2
        else
          echo "[Error] Argument for $1 is missing" >&2
          exit 1
        fi
        ;;
      -*|--*) # unsupported flags
          echo "Error: Unsupported flag: $1" >&2
          echo "$0 -h for help message" >&2
          exit 1
          ;;
      *)
          echo "Error: Arguments with not proper flag: $1" >&2
          echo "$0 -h for help message" >&2
          exit 1
          ;;
    esac
done
