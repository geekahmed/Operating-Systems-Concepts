#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[]){
    if(argc > 3){
        printf("Too many arguments supplied.\n");
        return 1;
    } else if(argc < 3){
        printf("Three argument expected.\n");
        return 1;
    }
    char contents[BUFFER_SIZE];
    int fd[2];
    FILE *fp;
    char *p;
    char ch;
    pid_t pid;
    if (pipe(fd) == -1){
        fprintf(stderr, "Pipe filed");
        return 1;
    }

    pid = fork();
    if (pid == 0){
        close(fd[WRITE_END]);
        read(fd[READ_END], contents, BUFFER_SIZE);
        fp = fopen(argv[2], "w");
        if (fp == NULL){
            fprintf(stderr, "Error in opening the file %s\n", argv[2]);
            return 1;
        }
        p = &contents[0];
        while (*p != EOF){
            fprintf(fp, "%c", *p);
            p++;
        }
        close(fd[READ_END]);

    }else{
        close(fd[READ_END]);
        fp = fopen(argv[1], "r");
        if (fp == NULL){
            fprintf(stderr, "Error in opening the file %s\n", argv[1]);
            return 1;
        }
        p = &contents[0];
        while ((ch = fgetc(fp)) != EOF){
            sprintf(p, "%c",ch);
            p++;
        }
        sprintf(p, "%c", EOF);
        write(fd[WRITE_END], contents, strlen(contents) + 1);
        close(fd[WRITE_END]);
    }

    return 0;
}
