#include <sys/types.h>

#include <stdio.h>

#include <unistd.h>
#include <stdlib.h>

int main()

{

pid_t pid;

/* fork a child process */

pid = fork();

if (pid < 0) { /* error occurred */

fprintf(stderr, "Fork Failed");

return 1;

}

else if (pid == 0) { /* child process */

printf("Hello World from the child process\n");

}

else { /* parent process */
printf("Hello from the parent process\n");
sleep(10);
}

return 0;

}
