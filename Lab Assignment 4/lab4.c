#include <stdio.h>
#include <stdlib.h>
#define INTEGER_MAXVALUE 2147483647

int giveRandom(int lower, int upper)
{
        return (rand() % (upper - lower + 1)) + lower;
}

int FCFS (int initial_position, int *disc){
    int sum = 0;
    int temp = 0;
    int arrlength = (sizeof(disc));

    for(int i = 0; i < arrlength; i++){
        temp = initial_position - disc[i];
        if(temp < 0) {
            temp = temp*-1;
        }
        sum += temp;
        initial_position = disc[i];
    }

    return sum;
}

int SSTF (int initial_position, int *disc){
    int sum = 0;

    int temp = INTEGER_MAXVALUE;
    int diff = 0;
    int arrlength = (sizeof(disc));

for(int i = 0; i < arrlength; i++){
    for(int i = 0; i < arrlength; i++){
        diff = abs(initial_position - disc[i]);
        //printf("diff: %d\n", diff);
        if(diff < temp && diff != 0){
            temp = diff;
        }
    }
    initial_position = disc[i];
    disc[i] = 0;
    printf("temp: %d\n", temp);
    sum += temp;
    temp = INTEGER_MAXVALUE;
    //HÄR ÄR DET NÅGOT KNASIGT TROR JAG

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

    printf("FCFS: %d\n", FCFS(53,slide_numbers));
    printf("SSTF: %d\n", SSTF(53,slide_numbers));


    return 0;

}