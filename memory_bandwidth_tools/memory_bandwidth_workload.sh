# !/bin/sh

NUM_THREAD=$1
GB=$2
TYPE=$3 # 0: ALL, 1: SINGLE_LOOP, 2: SINGLE_MEMSET, 3: OMP_LOOP, 4:OMP_MEMSET
MODE=$4 # 0: NONE, 1: REPEAT, 2: LOG(1000 times)
AFFINITY=$5
LOG_CNT=$6

# Arg: memory_bandwidth_workload size type mode affinity 
OMP_NUM_THREADS=${NUM_THREAD} ./memory_bandwidth_workload ${GB} ${TYPE} ${MODE} ${AFFINITY} ${LOG_CNT}