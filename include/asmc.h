#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#define CMD_COUNT 4
#define DIRECTORY_COUNT 3
#define TOTAL_ATTRIBUTES 4
#define NO_COMMAND 404
#define MAIN_ASM_PATH "./src/main.asm"

typedef const struct {
    char* name;
    char* command; // for the program to execute
    char* params; // for command
    char* options; // extra options for command
} attributes;
enum COMMANDS {
    NEW,
    INITIALIZE,
    RUN,
    BUILD
};
//Tools
void create_folder(const char*); //creates directory
int map_command(const char*); //returns the ID of the corrosponding command  
char* read_file(char*); // reads file and outputs string
int FileExists(const char *filename);

//Program Logic
void print_usages(); //prints text on how to use program
void parse_args(attributes*); //reads arguments are executes them
void create_main_asm(char*); //creates src/main.asm

//Program Commands
void new_project(const char*); //creates folders and files needed for the project
void intialize_project(); //recreates any missing files or folders
void run_project(); //runs the project
void build_project(); //creates an executable


int map_command(const char* command){
    char* cmd[CMD_COUNT] = {"new", "initialize", "run", "build"};
    for(int i = 0; i < CMD_COUNT; i++) if(strcmp(command, cmd[i]) == 0) return i;
 
    return NO_COMMAND; // NOTE: returns 404 if none match;
}
void parse_args(attributes* args){
    switch(map_command(args->command)){
        case NEW:
            if(args->params == "\0" || strcmp(args->params, ".") == 0) { 
                fprintf(stderr, "Please enter a valid directory name\n");
                return;
            }
            new_project(args->params);
            break;
        case INITIALIZE:
            break;
        case RUN:
            if(!FileExists(MAIN_ASM_PATH)){
                fprintf(stderr, "Error: ./src/main.asm does not exist. please intialize with asmc 'intialize'");
                return;
            }
            run_project(args);
            break;
        case BUILD:
            if(!FileExists(MAIN_ASM_PATH)){
                fprintf(stderr, "Error: ./src/main.asm does not exist. please intialize with asmc 'intialize'");
                return;
            }
            build_project(args);
            break;
        default:
            print_usages();
            break;
    }
}

void new_project(const char* project_name){
    int project_name_length = strlen(project_name);
    char* dir_name_ptr = (char*) malloc(sizeof(char) * project_name_length); // NOTE: allocates size of project_name
    sprintf(dir_name_ptr, "./%s", project_name);
    create_folder(dir_name_ptr);

    char* dirs[DIRECTORY_COUNT] = {"src", "include", "target"};

    for(int i = 0; i < DIRECTORY_COUNT; i++){
        dir_name_ptr = realloc(dir_name_ptr, sizeof(char) * strlen(*(dirs + i)) + project_name_length); // NOTE: allocates size of new directory name
        sprintf(dir_name_ptr, "./%s/%s", project_name, *(dirs + i)); // formats string
        create_folder(dir_name_ptr); // create new folder

        if(*(dirs + i) == "src"){
            dir_name_ptr = realloc(dir_name_ptr, strlen(dir_name_ptr) + strlen("/main.asm")); // NOTE: allocates '/main.asm'
            strcat(dir_name_ptr, "/main.asm"); // ./project_name/src/main.asm
            create_main_asm(dir_name_ptr); // ^
        }

    }
    free(dir_name_ptr); // NOTE: Free here
}
void create_folder(const char* dir_name_ptr){
    struct stat st = {0}; // holds status
    if(stat(dir_name_ptr, &st) == -1){
        mkdir(dir_name_ptr, 0700);
        printf("\t=== %s created\n", dir_name_ptr);
    }else{
        fprintf(stderr, "\t=== %s already exists!\n", dir_name_ptr);        
    }
}
void create_main_asm(char* dir_name_ptr){
    FILE* main_asm = fopen(dir_name_ptr, "w+"); //creates main.asm in dir_name_ptr
    char* bootloader_txt = read_file("bootloader.txt");

    if(fprintf(main_asm, "%s", bootloader_txt) == 0){
        fprintf(stderr, "\t=== Could not create file %s\n", dir_name_ptr);
    }else{
        printf("\t=== %s created\n", dir_name_ptr);
    };

    fclose(main_asm);
}
void intialize_project(attributes* attrs){
    new_project(attrs->name);
}
void run_project(attributes* attrs){
    build_project(attrs);
    char buff[50];

    sprintf(buff, "./target/%s.bin", attrs->name);
    system(buff); // Executes code
}
void build_project(attributes* attrs){
    char buff[50];
    sprintf(buff, "nasm -f bin ./src/main.asm -o ./target/%s.bin", attrs->name);
    system(buff); // builds with gcc
    
}
char* read_file(char *filename) {
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler)
   {
       // Seek the last byte of the file
       fseek(handler, 0, SEEK_END);
       // Offset from the first to the last byte, or in other words, filesize
       string_size = ftell(handler);
       // go back to the start of the file
       rewind(handler);

       // Allocate a string that can hold it all
       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

       // Read it all in one operation
       read_size = fread(buffer, sizeof(char), string_size, handler);

       // fread doesn't set it so put a \0 in the last position
       // and buffer is now officially a string
       buffer[string_size] = '\0';

       if (string_size != read_size)
       {
           // Something went wrong, throw away the memory and set
           // the buffer to NULL
           free(buffer);
           buffer = NULL;
       }

       // Always remember to close the file.
       fclose(handler);
    }

    return buffer;
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
int FileExists(const char *filename) {
    struct stat st;
    int result = stat(filename, &st);
    return result == 0;
}