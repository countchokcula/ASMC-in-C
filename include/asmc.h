#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

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

int map_command(const char*);
void print_usages();
void parse_args(const attributes*);
void new_project(const char*);
void intialize_project();
void run_project();
void build_project();

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
void new_project(const char* project_name){
    char* p_name_ptr = (char*) malloc(sizeof(char) * strlen(project_name));
    sprintf(p_name_ptr, "./%s", project_name);
    struct stat st = {0};
    if(stat(p_name_ptr, &st) == -1){
        mkdir(p_name_ptr, 0700);
    }else{
        fprintf(stderr, "Directory already exists!\n");        
    }
    free(p_name_ptr);
}
void intialize_project(){

}
void run_project(){

}
void build_project(){

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