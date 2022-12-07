#include <stdio.h>
#include <stdlib.h>
#define INTEGER_MAXVALUE 2147483647
#define DISC_SIZE 4999

/*
* Insertion sort taken from GeeksForGeeks
*/
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int giveRandom(int lower, int upper)
{
    return (rand() % (upper - lower + 1)) + lower;
}

int FCFS(int initial_position, int *disc, int arrlength)
{
    int sum = 0;
    int temp = 0;

    for (int i = 0; i < arrlength; i++)
    {
        temp = abs(initial_position - disc[i]);
        sum += temp;
        initial_position = disc[i];
    }

    return sum;
}

int SSTF(int initial_position, int *disc, int arrlength)
{
    int sum = 0;
    int temp = INTEGER_MAXVALUE;
    int diff, j, i = 0;
    int new_initial_position_index = 0;

    for (i = 0; i < arrlength; i++)
    {
        for (j = 0; j < arrlength; j++)
        {
            diff = abs(initial_position - disc[j]);
            if (diff < temp && diff != 0)
            {
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

int SCAN(int initial_position, int *disc, int arrlength)
{
    insertionSort(disc, arrlength);
    // Lägg till disc[0] eftersom distansen längst till vänster "glöms bort" annars.
    int sum = disc[0] * 2;
    int max_lower_than_initial = INTEGER_MAXVALUE * -1, index = 0;
    for (int i = 0; i < arrlength; i++)
    {
        if (disc[i] < initial_position && disc[i] > max_lower_than_initial)
        {
            max_lower_than_initial = disc[i];
            index = i;
        }
    }

    int flag = 1;
    for (int i = index; i < arrlength && i >= 0;)
    {
        if (i == 0)
        {
            flag = 0;
        }

        if (disc[i] != INTEGER_MAXVALUE)
        {
            sum += abs(initial_position - disc[i]);
            initial_position = disc[i];
            disc[i] = INTEGER_MAXVALUE;
        }

        if (flag == 1)
        {
            i--;
        }
        else
        {
            i++;
        }
    }
    return sum;
}

int CSCAN(int initial_position, int *disc, int arrlength){
    insertionSort(disc, arrlength);

    int sum = 0;
    sum =  DISC_SIZE + abs(DISC_SIZE - disc[arrlength-1]);
    int start_index = 0;

    for(int i = 0; i < arrlength; i++){
        if(disc[i] > initial_position){
            sum += abs(disc[i] - initial_position);
            start_index = i;
            initial_position = disc[i];
            disc[i] = INTEGER_MAXVALUE;
            break;
        }
    }

    for(int i = start_index; i < arrlength; i++){
        if(disc[i] != INTEGER_MAXVALUE){
            sum += abs(initial_position - disc[i]);
            initial_position = disc[i];
        }
    }

    initial_position = 0;

    for(int i = 0; i < start_index; i++){
        if(disc[i] != INTEGER_MAXVALUE){
            sum += abs(initial_position - disc[i]);
            initial_position = disc[i];
        }
    }

    return sum;
}

int CLOOK (int initial_position, int *disc, int arrlength){
    insertionSort(disc, arrlength);
    int sum = 0;
    int start_index=0;
    //find start element and it's index
    for(int i = 0; i < arrlength; i++){
        if(disc[i] > initial_position){
            sum += abs(disc[i] - initial_position);
            start_index = i;
            initial_position = disc[i];
            disc[i] = INTEGER_MAXVALUE;
            break;
        }
    }

    for(int i = start_index; i < arrlength; i++){
        if(disc[i] != INTEGER_MAXVALUE){
            sum += abs(initial_position - disc[i]);
            initial_position = disc[i];
        }
    }

    sum += abs(initial_position - disc[0]);
    initial_position = disc[0];

    for(int i = 0; i < start_index; i++){
        if(disc[i] != INTEGER_MAXVALUE){
            sum += abs(initial_position - disc[i]);
            initial_position = disc[i];
        }
    }

    return sum;
}
int LOOK(int initial_position, int *disc, int arrlength){
    insertionSort(disc, arrlength);
    int sum = 0;
    int max_lower_than_initial = INTEGER_MAXVALUE * -1, index = 0;
    for (int i = 0; i < arrlength; i++)
    {
        if (disc[i] < initial_position && disc[i] > max_lower_than_initial)
        {
            max_lower_than_initial = disc[i];
            index = i;
        }
    }

    int flag = 1;
    for (int i = index; i < arrlength && i >= 0;)
    {
        if (i == 0)
        {
            flag = 0;
        }

        if (disc[i] != INTEGER_MAXVALUE)
        {
            sum += abs(initial_position - disc[i]);
            initial_position = disc[i];
            disc[i] = INTEGER_MAXVALUE;
        }

        if (flag == 1)
        {
            i--;
        }
        else
        {
            i++;
        }
    }
    return sum;
}

//function that makes a shallow copy of an array
int* copyArray(int *source, int length){
    int *destination = malloc(sizeof(int) * length);
    for(int i = 0; i < length; i++){
        destination[i] = source[i];
    }
    return destination;
}

int main(int argc, char *argv[])
{
    int i = 0;
    int sequence[5000];
    int random_series[1000];
    int startpos = atoi(argv[1]);
    //int slide_numbers[] = {98, 183, 37, 122, 14, 124, 65, 67};
    //int webiste_numbers[] = {98, 183, 41, 122, 14, 124, 65, 67};
    //int geeks4geeks[] = {176, 79, 34, 60, 92, 11, 41, 114};
    

    while (i++ < 1000)
    {
        random_series[i] = giveRandom(0, 5000);
    }

    printf("FCFS: %d\n", FCFS(startpos, random_series, sizeof(random_series)/sizeof(random_series[0])));
    printf("SSTF: %d\n", SSTF(startpos, copyArray(random_series, 1000), sizeof(random_series)/sizeof(random_series[0])));
    printf("SCAN: %d\n", SCAN(startpos, copyArray(random_series, 1000), sizeof(random_series) / sizeof(random_series[0])));
    printf("CSCAN: %d\n", CSCAN(startpos, copyArray(random_series, 1000), sizeof(random_series) / sizeof(random_series[0])));
    printf("CLOOK: %d\n", CLOOK(startpos, copyArray(random_series, 1000), sizeof(random_series) / sizeof(random_series[0])));
    printf("LOOK: %d\n", LOOK(startpos, copyArray(random_series, 1000), sizeof(random_series) / sizeof(random_series[0])));




    return 0;
}
