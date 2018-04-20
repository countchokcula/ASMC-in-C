#include "../include/asmc.h"
int main(int argc, char** argv){
    printf("\t=== ASMC ===\n");

    short x=0;
    char* args[TOTAL_ATTRIBUTES];

    while(x++ < TOTAL_ATTRIBUTES) args[x] = "\0"; // Fills with 0 values
    for(int i = 0; i < argc; i++) args[i] = *(argv + i); //Fills remaining memory

    attributes attrs = {args[0], args[1], args[2], args[3]}; // NOTE: Constant attributes
    parse_args(&attrs);
    
    return 0;
}
