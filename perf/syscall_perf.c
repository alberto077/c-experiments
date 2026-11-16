#include <fcntl.h> 
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>

int main(void) {

    int fd = open("notes.txt", O_RDONLY);

    if (fd < 0) {
    perror("Could not open file");
}

    
    sched_setaffinity();

    const int loop_count = 10000000;
    char buffer[10];
    struct timespec start, end;

    // Warm-up call to load code into instruction cache
    read(fd, buffer, sizeof(buffer));

    clock_gettime(CLOCK_MONOTONIC, &start);
    for (int i = 0; i < loop_count; ++i) {
        ssize_t res = read(fd, buffer, sizeof(buffer));

        if (res < 0) {
            perror("read");
            close(fd);
            return 1;
        }

    }
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate elapsed time in nanoseconds
    double elapsed = (end.tv_sec - start.tv_sec) * 1e9 + (end.tv_nsec - start.tv_nsec);
    close(fd);
    printf("Average for a system call: %.2f nanoseconds\n", elapsed/loop_count);

}
