#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc > 2){
        printf("Too many arguments supplied.\n");
        return 1;
    } else if(argc == 1){
        printf("One argument expected.\n");
        return 1;
    }
    // Shared Memory
    int fd;
    struct timeval start, end;
    void *ptr;

    ptr = mmap(NULL, sizeof(struct timeval) * 2, PROT_READ | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    if (ptr == MAP_FAILED) {
        exit(0);
    }
    // Process Execution
    pid_t pid;
    pid = fork();
    if(pid == 0){
        gettimeofday(&start, NULL);
        memcpy(ptr, &start, sizeof(struct timeval));
        execvp(argv[1], &argv[1]);
    } else if (pid > 0){
        wait(NULL);
        struct timeval tstart;
        gettimeofday(&end, NULL);
        memcpy(&tstart, ptr, sizeof(struct timeval));
        printf("times taken for %s: second:%lu microsecond:%ld\n", argv[0], end.tv_sec - tstart.tv_sec, end.tv_usec - tstart.tv_usec);
        munmap(ptr, sizeof(struct timeval));
    } else if (pid < 0){
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    return 0;
}
