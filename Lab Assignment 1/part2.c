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
            ch = fgetc(file);
            message[i++] = ch;
        } while (ch != EOF);

        // Send file through message queue
        msgsnd(msgid, &message, 500, 0);
    }
    else
    { // parent
        wait(NULL);
        char rcv_message[500];
        msgrcv(msgid, &rcv_message, 500, 0, 0);

        printf("%s \n", rcv_message);
        
        int count = 1;
        for(int i = 0; rcv_message[i] != NULL; i++){
            if(rcv_message[i] == ' ' || rcv_message[i] == '\n'){
                count++;
            }
        }

        printf("Number of words: %d \n", count);
        msgctl(msgid, IPC_RMID, NULL);
        exit(1);
    }

    return 0;
}