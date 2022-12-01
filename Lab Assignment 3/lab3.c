#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE_ENTRIES 256
#define BIN_FILE "data/BACKING_STORE.bin"
#define TLB_SIZE 16

int page_table[PAGE_ENTRIES];
int tlb[TLB_SIZE][2];
int number_of_hits, number_of_misses, hit, qp;
int number_of_occurencies = 0;

int get_page_number(int logical_address)
{
    return (0xFF00 & logical_address) >> 8;
}

int get_page_offset(int logical_address)
{
    return (0x00FF & logical_address);
}

int get_physical_address(int logical_address, int frame_number)
{
    int page_offset = get_page_offset(logical_address);
    
    return frame_number * 256 + page_offset;
}



int main(int argc, char *argv[])
{

    FILE *addresses, *physical_memory;

    addresses = fopen("./data/addresses.txt", "r");
    physical_memory = fopen(BIN_FILE, "rb");

    char *value = NULL;
    size_t len = 0;

    memset(page_table, -1, sizeof(page_table));
    memset(tlb,-1,TLB_SIZE*2*sizeof(tlb[0][0]));


    int read, frame, i;
    while ((read = getline(&value, &len, addresses)) != -1)
    {
        number_of_occurencies++;
        int logical_address = atoi(value);
        
        int page_number = get_page_number(logical_address);
        int page_offset = get_page_offset(logical_address);

        hit = 0;

        for(i=0;i<TLB_SIZE;i++)
		{
			if(tlb[i][0]==page_number)
			{
				hit=1;
				number_of_hits++;
				frame=tlb[i][1];
				break;
			}
		}
        
        if(hit == 0){
            int f = 0;
            for (i = 0; i < PAGE_ENTRIES; i++)
            {
                if (page_table[i] == page_number)
                {
                    frame = i;
                    number_of_misses++;
                    break;
                }   
                if (page_table[i] == -1)
                {
                    f = 1;

                    break;
                }
            }
            if (f == 1)
            {
                page_table[i] = page_number;
                frame = i;
            }
        tlb[qp%=15][0]=page_number;
        tlb[qp++][1]=i;	
        }

        char value = 0;

        fseek(physical_memory, logical_address, SEEK_SET);
        fread(&value, sizeof(char), 1, physical_memory);
        printf("logical address %d  physical_address: %d value: %d \n",
               logical_address,
               get_physical_address(logical_address, frame),
               value
               );
    }
    double hitrate = (double)number_of_hits/number_of_occurencies*100;
    double missrate = (double)number_of_misses/number_of_occurencies*100;
    printf("hitrate: %.2f%c\t\t missrate: %.2f%c \n", hitrate, '%', missrate, '%');
    printf("number of hits: %d \t number of misses: %d  occ %d\n", number_of_hits, number_of_misses,number_of_occurencies);

    return 0;
}