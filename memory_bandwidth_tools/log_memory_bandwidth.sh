# !/bin/sh

NUM_THREAD=4
GB=0.1
# TYPE=$3 # 0: ALL, 1: SINGLE_LOOP, 2: SINGLE_MEMSET, 3: OMP_LOOP, 4:OMP_MEMSET
MODE=2 # 0: NONE, 1: REPEAT, 2: LOG(1000 times)
LOG_CNT=100

# OMP_NUM_THREADS=${NUM_THREAD} ./profile_memory_bandwidth ${GB} 1 ${MODE} ${LOG_CNT}
# OMP_NUM_THREADS=${NUM_THREAD} ./profile_memory_bandwidth ${GB} 2 ${MODE} ${LOG_CNT}
# OMP_NUM_THREADS=${NUM_THREAD} ./profile_memory_bandwidth ${GB} 3 ${MODE} ${LOG_CNT}
OMP_NUM_THREADS=${NUM_THREAD} ./profile_memory_bandwidth ${GB} 4 ${MODE} ${LOG_CNT}