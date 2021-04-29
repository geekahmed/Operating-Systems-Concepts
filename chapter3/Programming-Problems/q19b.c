#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>

#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){
    if(argc > 2){
        printf("Too many arguments supplied.\n");
        return 1;
    } else if(argc == 1){
        printf("One argument expected.\n");
        return 1;
    }

    struct timeval write_msg, end;
    struct timeval read_msg;
    int fd[2];
    if (pipe(fd) == -1) {
        fprintf(stderr,"Pipe failed");
        return 1;
    }

    pid_t pid = fork();
    if(pid == 0){
        gettimeofday(&write_msg, NULL);
        close(fd[READ_END]);
        write(fd[WRITE_END], &write_msg, sizeof(struct timeval));
        execvp(argv[1], &argv[1]);
        close(fd[WRITE_END]);
    } else if (pid > 0){
        wait(NULL);
        close(fd[WRITE_END]);
        gettimeofday(&end, NULL);
        read(fd[READ_END], &read_msg, sizeof(struct timeval));
        printf("times taken for %s: second:%lu microsecond:%ld\n", argv[0], end.tv_sec - read_msg.tv_sec, end.tv_usec - read_msg.tv_usec);
        close(fd[READ_END]);
    } else if (pid < 0){
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    return 0;
}
