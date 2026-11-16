#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {

    

    cpu_set_t my_set;        /* Define your cpu_set bit mask. */
    CPU_ZERO(&my_set);       /* Initialize it all to 0, i.e. no CPUs selected. */
    CPU_SET(0, &my_set);     /* set the bit that represents core 0. */

    sched_setaffinity(0, sizeof(cpu_set_t), &my_set);

    char byte_ball= 'a';

    const int loop_count = 1000000;
    struct timespec start, end;

    int fd[2];
    int fd2[2];


    int pipe1 = pipe(fd);


    if (pipe1 < 0) {
        perror("Could not pipe 1");
        return 1;
    }

    int pipe2 = pipe(fd2);

    if (pipe2 < 0) {
        perror("could not pipe 2");
        return 1;
    }


    pid_t rc = fork();

    if (rc < 0) {
        perror("Could not fork into child");
        return 1;

    } else if (rc == 0) {
        for (int i = 0; i < loop_count; ++i){
            read(fd[0], &byte_ball, 1);
            write(fd2[1], &byte_ball, 1);
        }

        exit(0);
    }



    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < loop_count; ++i) {
        write(fd[1], &byte_ball, 1);
        read(fd2[0], &byte_ball, 1);
    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    wait(NULL);


    double elapsed = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);

    close(fd[0]);
    close(fd2[0]);

    // mesured that 242 is about the cost of a syscall
    const int amount_of_syscalls = 4;
    const int avg_time_per_syscall = 242;

    double per_round = elapsed/loop_count;
    double syscall_time = amount_of_syscalls * avg_time_per_syscall;
    double per_context_switch = (per_round - syscall_time) / 2;

    printf("Average for a context switch: %.2f nanoseconds\n", per_context_switch);
    printf("Context switch cost %.2fx a syscall\n", per_context_switch/avg_time_per_syscall);

    return 0;



}


