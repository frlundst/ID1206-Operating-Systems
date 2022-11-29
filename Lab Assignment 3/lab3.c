#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PAGE_ENTRIES 256


int get_page_number(int logical_address){
    return (0xFF00 & logical_address) >> 8;
}
int get_page_offset(int logical_address){
    return (0x00FF & logical_address);
}

int page_table[PAGE_ENTRIES];

int main(int argc, char* argv[]){

    FILE *fd;
    fd=fopen(argv[1],"r");
    char *value = NULL;
    size_t len=0;
    

    getline(&value,&len,fd);


    int logical_address = atoi(value);

    printf("logical address %d ", logical_address);
    printf(" page_number : %x ", get_page_number(logical_address));
    printf(" page_offset : %x \n", get_page_offset(logical_address));

    return 0;
}