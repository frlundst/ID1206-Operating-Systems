#include <stdio.h>
#include <stdlib.h>
#define INTEGER_MAXVALUE 2147483647

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

int main()
{
    int i = 0;
    int sequence[5000];
    int random_series[1000];
    int slide_numbers[] = {98, 183, 37, 122, 14, 124, 65, 67};

    while (i < 5000)
    {
        sequence[i] = i;
        i++;
    }
    i = 0;

    while (i++ < 1000)
    {
        random_series[i] = giveRandom(0, 5000);
    }

    // printf("FCFS: %d\n", FCFS(53,slide_numbers, sizeof(slide_numbers)/sizeof(slide_numbers[0])));
    // printf("SSTF: %d\n", SSTF(53,slide_numbers, sizeof(slide_numbers)/sizeof(slide_numbers[0])));
    // printf("SSTF: %d\n", SSTF(2,random_series, sizeof(random_series)/sizeof(random_series[0])));

    printf("SCAN: %d\n", SCAN(53, slide_numbers, sizeof(slide_numbers) / sizeof(slide_numbers[0])));

    return 0;
}
