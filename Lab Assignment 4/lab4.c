#include <stdio.h>
#include <stdlib.h>

int giveRandom(int lower, int upper)
{
        return (rand() % (upper - lower + 1)) + lower;
}

int FCFS (int initial_position, int disc[]){
    int sum = 0;
    int temp = 0;

    for(int i = 0; i < (int)( sizeof(disc) / sizeof(disc[0]); i++){
        temp = initial_position - disc[i];
        printf("%d \n", temp);
        if(temp < 0) {
            temp = temp*-1;
        }
        sum += temp;
        initial_position = disc[i];
        printf("%d, %d, %d\n", temp, sum, initial_position);
    }

    return sum;
}

int main(){
    int i = 0;
    int sequence[5000];
    int random_series[1000];
    int slide_numbers[] = {98,183,37,122,14,124,65,67};

    while(i < 5000){
        sequence[i] = i;
        i++;

    }
    i = 0;
    
    while(i<1000){
        random_series[i] = giveRandom(0,5000);
        //printf("%d\n", random_series[i]);
        i++;
    }

    int sum = FCFS(53,slide_numbers);
    printf("%d\n", sum);


    return 0;

}