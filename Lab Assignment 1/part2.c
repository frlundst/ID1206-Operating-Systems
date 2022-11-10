#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <string.h>



int main(int argc, char *argv[])
{
    int msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0600);

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

        if (NULL == file)
        {
            perror("file can't be opened \n");
        }

        // Testar printa ut fil, lägg till i parent istället
        char message[500], ch;
        int i;
        do
        {
            message[i++] = fgetc(file);
        } while (ch != EOF);
        
        printf("morsning");
        // Send file through message queue
        msgsnd(msgid, &message, 500, 0);
        printf(" korsning");
    }
    else
    { // parent
        wait(NULL);
        char rcv_message[500];
        msgrcv(msgid, &rcv_message, 500, 0, 0);
        printf("punkt");

        msgctl(msgid, IPC_RMID, NULL);
        exit(1);

    }

    return 0;
}