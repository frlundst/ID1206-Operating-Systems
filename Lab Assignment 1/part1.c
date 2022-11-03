#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h> 
#include <fcntl.h> 
#include <errno.h> 
#include <sys/wait.h>

int main(){
        int pipefds[2];
        int returnstatus;
        int pid;

        returnstatus = pipe(pipefds);
        if (returnstatus == -1) {
                printf("Unable to create pipe\n");
                return 1;
        }

        pid = fork();

        if (pid < 0) perror("Something failed on trying to create a child process!\n");
        else if (pid == 0) {
                dup2(pipefds[1], 1);
                close(pipefds[0]);
                execlp("ls", "ls", "/", NULL);
                
        } else {
                dup2(pipefds[0], 0);
                close(pipefds[1]);
                execlp("wc", "wc", "-l", NULL);
        }
        return 0;
}