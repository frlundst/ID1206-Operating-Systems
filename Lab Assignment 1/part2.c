#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>

int main(int argc, char* argv[]){
    


    switch (fork())
    {
    case -1: // fork error
        exit(1);
        break;

    case 0: // child
        FILE* file;
        char character;

        file = fopen("file.txt", "r");

        while((character = fgetc(file)) != EOF){
            printf("%c", character);
        }

        mqd_t mqd = mq_open ("my_queue", O_CREAT | O_EXCL | O_WRONLY,  0600, NULL);

        if (mqd == -1) {
            perror ("mq_open");
            exit (1);
        }
        mq_send (mqd, "Hello World", 11, 0);
        mq_close (mqd);


        break;

    default: // parent
        mqd_t mqd = mq_open ("my_queue", O_RDONLY);
        mq_receive (mqd, buffer, 8192, NULL);
        printf ("%s", buffer);

        break;
    }

    return 0;
}