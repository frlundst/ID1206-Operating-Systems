#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]){
    


    pid_t process = fork();
    char* buffer = "Hello World";

    if (0 == process){

        FILE* file;
        char character;
        file = fopen("file.txt", "r");

        while((character = fgetc(file)) != EOF){
            printf("%c", character);
        }

        mqd_t mqd = mq_open("my_queue", O_CREAT | O_EXCL | O_WRONLY,  0600, NULL);

        if (mqd == -1) {
            perror ("mq_open");
            exit (1);
        }
        mq_send (mqd,buffer , 11, 0);
        mq_close (mqd);

    }else if(-1 == process){
        exit(1);
    }else{
        mqd_t mqd = mq_open("my_queue", O_RDONLY);
        mq_receive (mqd, buffer, 8192, NULL);
        printf ("%s", buffer);
    }

    return 0;
}