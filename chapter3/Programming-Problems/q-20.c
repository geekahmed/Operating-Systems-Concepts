#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/time.h>
#include <malloc.h>
#include <stdlib.h>

#define MIN_PID 300
#define MAX_PID 5100

int allocate_map(void);
int test_pid(int pid);
int allocate_pid(void);
void release_pid(int pid);


int *bitmap;

int main(int argc, char *argv[]){
    int pid;
    printf("allocate_map(void): %d\n", allocate_map());

    pid = allocate_pid();
    printf("allocate_pid(void): %d\n", pid);

    release_pid(pid);
    printf("release_pid(%d):\n", pid);
    return 0;
}

int allocate_map(void){
    bitmap = (int  *) calloc((MAX_PID - MIN_PID)/32 + 1, sizeof(int));
    if(bitmap != NULL)
        return 1;
    return -1;
}

int test_pid(int pid){
    return ( (bitmap[pid/32] & (1 << (pid%32) )) != 0 );
}
int allocate_pid(void){
    // Generate Random PID
    int pid = 0;
    do {
        pid = rand() % (MAX_PID - MIN_PID + 1) + MIN_PID ;
    } while (test_pid(pid) != 0);

    bitmap[pid/32] |= 1 << (pid%32); // Allocate the PID
    return pid;
}
void release_pid(int pid){
    bitmap[pid/32] &= ~(1 << (pid%32));
}
