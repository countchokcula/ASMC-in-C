#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CMD_COUNT 4

typedef const struct {
    char* name;
    char* command;
    char* params;
    char* options;
} attributes;
enum COMMANDS {
    NEW,
    INITIALIZE,
    RUN,
    BUILD
};

void print_usages();
int map_command(const char*);
void parse_args(const attributes*);


int map_command(const char* command){
    char* cmd[CMD_COUNT] = {"new", "initialize", "run", "build"};
    for(int i = 0; i < CMD_COUNT; i++){
        if(strcmp(command, cmd[i]) == 0){
            return i;            
        }
    }
}
void parse_args(const attributes* args){
    if(args->command != '\0'){
        switch(map_command(args->command)){
            case NEW:
                break;
            case INITIALIZE:
                break;
            case RUN:
                break;
            case BUILD:
                break;
            default:
                print_usages();
                break;
        }
    }else{
        print_usages();
    }
    return;
}
void print_usages(){
    const char* commands[CMD_COUNT] = {
        "new: creates new project with parameters: [name]; For example type 'asmc new project'", 
        "initialize: recreates files in project dir",
        "build: builds files required executable code", 
        "run: builds & execute the x86 Assembly code"
    };
    printf("\n\t\t=== ASMC COMMANDS ===\n");
    for(short row = 0; row < CMD_COUNT; row++){
        printf("\t%s\n", commands[row]);
    }
    printf("\n");
    return;
} 