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
    // Process Execution
    pid_t pid;
    pid = fork();
    if(pid == 0){
        long long result = n;
        printf("%lld", n);
        while (1){
            if(result == 1) break;
            if(result % 2 == 0){
                result /= 2;
            } else {
                result = 3 * result + 1 ;
            }
            printf(" %lld", result);
        }
        printf("\n");
        exit(0);
    } else if (pid > 0){
        wait(NULL);
        printf("Program Finished!!\n");
    } else if (pid < 0){
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    return 0;
}

