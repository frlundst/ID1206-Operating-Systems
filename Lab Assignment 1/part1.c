#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pipe(fd);

    switch (fork())
    {
    case -1: // fork error
        exit(1);
        break;

    case 0: // child
        dup2(fd[1], 1);
        close(fd[0]);
        execlp("ls", "ls", "/", NULL);
        break;

    default: // parent
        wait(NULL);
        dup2(fd[0], 0);
        close(fd[1]);
        execlp("wc", "wc", "-l", NULL);
        break;
    }

    return 0;
}