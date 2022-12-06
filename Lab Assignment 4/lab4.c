#include <stdio.h>
#include <stdlib.h>
#define INTEGER_MAXVALUE 2147483647

int giveRandom(int lower, int upper)
{
        return (rand() % (upper - lower + 1)) + lower;
}

int FCFS (int initial_position, int *disc, int arrlength){
    int sum = 0;
    int temp = 0;

    for(int i = 0; i < arrlength; i++){
        temp = abs(initial_position - disc[i]);
        sum += temp;
        initial_position = disc[i];
    }

    return sum;
}

int SSTF (int initial_position, int *disc, int arrlength){
    int sum = 0;
    int temp = INTEGER_MAXVALUE;
    int diff, j, i = 0;
    int new_initial_position_index = 0;


    for(i = 0; i < arrlength; i++){
        for(j = 0; j < arrlength; j++){
            diff = abs(initial_position - disc[j]);
            if(diff < temp && diff != 0){
                temp = diff;
                new_initial_position_index = j;
            }
        }
        initial_position = disc[new_initial_position_index];
        disc[new_initial_position_index] = INTEGER_MAXVALUE;
        sum += temp;
        temp = INTEGER_MAXVALUE;
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
    
    while(i++<1000){
        random_series[i] = giveRandom(0,5000);
    }

    printf("FCFS: %d\n", FCFS(53,slide_numbers, sizeof(slide_numbers)/sizeof(slide_numbers[0])));
    printf("SSTF: %d\n", SSTF(53,slide_numbers, sizeof(slide_numbers)/sizeof(slide_numbers[0])));

    printf("STFF: %d\n", SSTF(2,random_series, sizeof(random_series)/sizeof(random_series[0])));

    return 0;

}



