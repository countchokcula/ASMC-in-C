#include "../include/asmc.h"
int main(int argc, char** argv){
    short x=0;
    char* args[TOTAL_ATTRIBUTES];

    while(x++ < TOTAL_ATTRIBUTES) args[x] = NULL; // Fills with null values
    for(int i = 0; i < argc; i++) args[i] = *(argv + i);

    attributes attrs = {args[0], args[1], args[2], args[3]}; // NOTE: Constant
    parse_args(&attrs);
    return 0;
}
