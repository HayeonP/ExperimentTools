all: memory_bandwidth_workload

memory_bandwidth_workload: memory_bandwidth_workload.c
	gcc -o memory_bandwidth_workload memory_bandwidth_workload.c -fopenmp
clean:
	rm -f memory_bandwidth_workload *.o