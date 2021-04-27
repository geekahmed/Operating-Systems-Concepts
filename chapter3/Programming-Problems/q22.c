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
    long long n = (long long ) atoi(argv[1]);
    if(n < 0){
        return 1;
    }
    // Shared Memory
    void *ptr;
    int fd = shm_open("collatz", O_RDWR| O_CREAT, S_IRUSR| S_IWUSR);
    ftruncate(fd, 4096);
    ptr = mmap(NULL, 4096, PROT_READ | PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, fd, 0);
    if (ptr == MAP_FAILED) {
        exit(0);
    }
    // Process Execution
    pid_t pid;
    pid = fork();
    if(pid == 0){
        long long result = n;
        int bytes = 0;

        while (1){
            memcpy(ptr + bytes, &result, sizeof(long long ));
            bytes += sizeof(long long);
            if(result == 1) break;
            if(result % 2 == 0){
                result /= 2;
            } else {
                result = 3 * result + 1 ;
            }
        }
        munmap(ptr, 4096);
        exit(0);
    } else if (pid > 0){
        int status;
        // parent
        wait(NULL);
        long long pbuffer[4096] = {0};
        memcpy(pbuffer, ptr, 4096);
        int idx = 0;
        while (pbuffer[idx] != 0) {
            printf("%lld ", pbuffer[idx]);
            idx++;
        }
        printf("\n");
        munmap(ptr, 4096);
    } else if (pid < 0){
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    return 0;
}

