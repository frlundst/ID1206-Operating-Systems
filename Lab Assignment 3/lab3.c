#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE_ENTRIES 256
#define BIN_FILE "data/BACKING_STORE.bin"

int page_table[PAGE_ENTRIES];

int get_page_number(int logical_address)
{
    return (0xFF00 & logical_address) >> 8;
}

int get_page_offset(int logical_address)
{
    return (0x00FF & logical_address);
}

int get_physical_address(int logical_address)
{
    int page_number = get_page_number(logical_address);
    int page_offset = get_page_offset(logical_address);
    int frame_number = page_table[page_number];
    // int frame_number = page_number;
    // return (frame_number << 8) | page_offset;
    return page_offset | frame_number;
    // return (frame_number * 256) + page_offset;
}

int main(int argc, char *argv[])
{

    FILE *fd;
    fd = fopen("./data/addresses.txt", "r");
    char *value = NULL;
    size_t len = 0;

    FILE *physical_memory = fopen(BIN_FILE, "rb");

    memset(page_table, -1, sizeof(page_table));

    int read, frame, i;
    while ((read = getline(&value, &len, fd)) != -1)
    {
        int logical_address = atoi(value);

        int page_number = get_page_number(logical_address);
        int page_offset = get_page_offset(logical_address);

        int f = 0;
        for (i = 0; i < PAGE_ENTRIES; i++)
        {
            if (page_table[i] == page_number)
            {
                frame = i;
                //fault++;
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

        printf("logical address %d page_number : %d page_offset : %d physical_address: %d \n",
               logical_address,
               get_page_number(logical_address),
               get_page_offset(logical_address),
               frame * 256 + page_offset);
    }

    return 0;
}