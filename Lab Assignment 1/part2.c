#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[])
{
    key_t key;
    int msgflg;
    int msgid = msgget(key, msgflg);

    if (msgid == -1)
    { 
        perror("message queue error \n");
        exit(1);
    }

    pid_t id = fork();

    if (id < 0)
    {
        perror("fork error \n");
        exit(1);
    }

    if (id == 0)
    { // child
        FILE *file = fopen("part2.txt", "r");

        if (file == NULL)
        {
            perror("file can't be opened \n");
        }

        // Testar printa ut fil, lägg till i parent istället
        char ch;
        do
        {
            ch = fgetc(file);
            printf("%c", ch);
        } while (ch != EOF);

        // Send file through message queue
        msgsnd(key, &file, 500, msgflg);
    }
    else
    { // parent
    }

    return 0;
}