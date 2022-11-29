#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE_ENTRIES 256
#define BIN_FILE "data/BACKING_STORE.bin"

int page_table[PAGE_ENTRIES];

int get_page_number(int logical_address){
    return (0xFF00 & logical_address) >> 8;
}
int get_page_offset(int logical_address){
    return (0x00FF & logical_address);
}
int get_physical_address(int logical_address){
    int page_number = get_page_number(logical_address);
    int page_offset = get_page_offset(logical_address);
    int frame_number = page_table[page_number];
    return (frame_number << 8) | page_offset;
}

int main(int argc, char* argv[]){

    FILE *fd;
    fd=fopen(argv[1],"r");
    char *value = NULL;
    size_t len=0;
    

    getline(&value,&len,fd);

    FILE *physical_memory = fopen(BIN_FILE, "rb");


    int logical_address = atoi(value);

    printf("logical address %d page_number : %x page_offset : %x physical_address: %d \n", 
                logical_address,
                get_page_number(logical_address), 
                get_page_offset(logical_address),
                get_physical_address(logical_address));

    return 0;
}