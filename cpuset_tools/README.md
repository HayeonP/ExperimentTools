# cpuset
Set of shell scripts for setup and leverage cpuset

---
## setup_cpuset.sh
Setup cpusets.
- Create **number_of_cpuset** cpusets.
- All current tasks are moved to **subset0**.
```
$ sudo bash setup_cpuset.sh {number_of_cpuset}
```
---
## add_taskset.sh
Add tasks to target cpuset
```
$ bash add_task.sh {task_pid} {target_cpuset}
```
---
## monitor_cpuset.sh
Monitor the status of cpuset.
- Manual is described in **-h** option.
```
$ bash monitor_cpuset.sh [option] {argument}
```
---
## move_cpuset.sh
Move all tasks in source cpuset to target cpuset
```
$ bash move_cpuset.sh {source_cpuset} {target_cpuset}
```
---



