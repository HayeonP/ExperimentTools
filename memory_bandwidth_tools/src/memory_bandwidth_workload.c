#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <omp.h>
#include <stdint.h>
#include <sched.h>

cpu_set_t mask;

#define GB2BYTE(v) v * 1024 * 1024 * 1024

#define ALL 0
#define SINGLE_LOOP 1
#define SINGLE_MEMSET 2
#define OMP_LOOP 3
#define OMP_MEMSET 4
#define NONE 0
#define REPEAT 1
#define LOG 2

void printBit(size_t n) {
    if(n>1) printBit(n>>1);
    printf("%d", n&1);
}

double current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    double timestamp;
    timestamp = te.tv_sec + te.tv_usec * 1e-6;

    return timestamp;
}

double write_memory_loop(void* array, size_t size){
    double start, end;
    size_t* carray = (size_t *) array;
    size_t i;

    start = current_timestamp();
    for(i = 0; i < size / sizeof(size_t); i++){
        carray[i] = 0;
    }
    end = current_timestamp();

    return end - start;
}

double write_memory_memset(void* array, size_t size){
    double start, end;
    size_t* carray = (size_t *) array;

    start = current_timestamp();
    memset(carray, 1, size);
    end = current_timestamp();

    return end - start;
}


double write_memory_loop_omp(void* array, size_t size){
    double start, end;
    size_t* carray = (size_t *) array;
    size_t i;
    int n;

#pragma omp parallel
    {
        n = omp_get_num_threads();

#pragma omp barrier

#pragma omp master
        start = current_timestamp();

#pragma omp for nowait
        for(i = 0; i < size / sizeof(size_t); i++){
            carray[i] = 0;
        }

#pragma omp barrier

#pragma omp master
        end = current_timestamp();

    }
    printf("%d",n);

    return end - start;
}

double write_memory_memset_omp(void* array, size_t size){
    double start, end;
    size_t* carray = (size_t *) array;
    int n, offset, total_idx;
    total_idx = size/sizeof(size_t);

#pragma omp parallel
    {
        n = omp_get_num_threads();
#pragma omp barrier

#pragma omp master
        start = current_timestamp();
        offset = omp_get_thread_num() * total_idx/n;
        memset(carray+offset, 1, size/n);

#pragma omp barrier

#pragma omp master
        end = current_timestamp();

    }
    printf("%d",n);

    return end - start;
}

int main(int argc, char* argv[]){
    int core;


    double gb;
    int type = ALL; // 0: all, 1: single loop, 2: single memset, 3: omp loop, 4: omp memset
    int mode = 0; // 0: none, 1: repeat, 2: log(1000 times)
    int affinity = -1;
    int log_cnt = 1000;

    // Arg: memory_bandwidth_workload size type mode affinity 

    if(argc == 1) gb = 1.0;
    if(argc >= 2) gb = atof(argv[1]);
    if(argc >= 3){
        type = atoi(argv[2]);
        if(type > 4 || type < 0){
            printf("Wrong type\n");
            exit(1);
        }
    }

    if(argc >= 4){
        mode = atoi(argv[3]);
        if(mode > 2 || mode < 0){
            printf("Wrong mode\n");
            exit(1);
        }
    }

    if(argc >=5){
        affinity = atoi(argv[4]);
        
        if(affinity != -1){
            printf("CPU Affinity: %d\n",core);
            CPU_ZERO(&mask);
            CPU_SET(affinity, &mask);
            sched_setaffinity(0, sizeof(mask), &mask);
        }
    }

   if(argc >= 6){
       if(mode != LOG){
           printf("Set mode to LOG for using the log_cnt argument.");
           exit(1);
       }
       log_cnt = atoi(argv[5]);
   }

    size_t size = GB2BYTE(gb); // 1 GB

    void *array1, *array2, *array3, *array4;
    array1 = (void *)malloc(size);
    array2 = (void *)malloc(size);
    array3 = (void *)malloc(size);
    array4 = (void *)malloc(size);

    printf("[Info]\n");
    printf("Total data size: %lf\n", gb);

    printf("[Initial state]\n");
    system("free -mh");
    printf("\n");
    printf("[Memory Bandwidth Profiling]\n");

    double elapsed_time;

    char filepath[128];
    FILE *fp;
    if(mode == LOG){
        char typename[16];
        switch(type){
            case ALL:
                sprintf(typename,"all");
                break;
            case SINGLE_LOOP:
                sprintf(typename, "single-loop");
                break;
            case SINGLE_MEMSET:
                sprintf(typename, "single-memset");
                break;
            case OMP_LOOP:
                sprintf(typename, "omp-loop");
                break;
            case OMP_MEMSET:
                sprintf(typename, "omp-memset");
                break;
        }
        sprintf(filepath, "./memory_bandwidth_%s.csv", typename);
        fp = fopen(filepath, "w");
        if(fp == NULL){
            printf("Cannot create log file: %s.\n", filepath);
            exit(1);
        }
        fprintf(fp, "type,elapsed_time(s),bandwidth(GB/s)\n");
    }

    int cnt = 0;
    while(1){
        switch(type){
            case ALL:
                elapsed_time = write_memory_loop(array1, size);
                printf("\twrite_memory_loop: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "SINGLE_LOOP,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                elapsed_time = write_memory_memset(array2, size);
                printf("\twrite_memory_memset: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "SINGLE_MEMSET,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                printf("\t[");
                elapsed_time = write_memory_loop_omp(array3, size);
                printf("]write_memory_loop_omp: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "OMP_LOOP,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                printf("\t[");
                elapsed_time = write_memory_memset_omp(array4, size);
                printf("]write_memory_memset_omp: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "OMP_MEMSET,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                break;
            case SINGLE_LOOP:
                elapsed_time = write_memory_loop(array1, size);
                printf("\twrite_memory_loop: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "SINGLE_LOOP,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                break;
            case SINGLE_MEMSET:
                elapsed_time = write_memory_memset(array2, size);
                printf("\twrite_memory_memset: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "SINGLE_MEMSET,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                break;
            case OMP_LOOP:
                printf("\t[");
                elapsed_time = write_memory_loop_omp(array3, size);
                printf("]write_memory_loop_omp: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "OMP_LOOP,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                break;
            case OMP_MEMSET:
                printf("\t[");
                elapsed_time = write_memory_memset_omp(array4, size);
                printf("]write_memory_memset_omp: %lfGB/s\n", gb/elapsed_time);
                if(mode==LOG) fprintf(fp, "OMP_MEMSET,%lf,%lf\n",elapsed_time, gb/elapsed_time);

                break;
        }

        cnt++;
        if(mode == NONE) break;
        else if(mode == LOG && cnt == log_cnt) break;
    }

    if(mode == LOG){
        fclose(fp);
    }

    return 0;
}