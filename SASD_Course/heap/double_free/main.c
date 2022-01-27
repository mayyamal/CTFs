#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

#define ensure(x) ((x) ? (void)0 : exit(0))

static char the_flag[64];

void handle_command(char* input, int len) {
    char buffer[32];
    strcpy(buffer, input);
    strtok(buffer, " ");
    if(!strncmp(buffer, "quit", 4) || !strncmp(buffer, "exit", 4)) {
        puts("Bye!");
        exit(0);
    } else if(!strncmp(buffer, "help", 4)) {
        puts("quit - exit the shell");
        puts("print <text> - echo the given text");
        puts("flag - output the flag if user is authorized");
        puts("user - display username");
        puts("help - show this help");
    } else if(!strncmp(buffer, "flag", 4)) {
        char* ptr1 = malloc(32);
        strcpy(ptr1, buffer);
        char* ptr2 = malloc(32);
        strcpy(ptr2, buffer);
        ensure(!strcmp(ptr1, ptr2)); 
        char* ptr3 = strdup(input);
        
        ensure(ptr3 = ptr1);
        
        free(ptr1);
        free(ptr2);
        free(ptr3);
        
        ptr1 = strdup(the_flag);
        if(!strcmp(getenv("USER"), "doubleagent")) {  
            puts("Authorized. Here is your flag: ${ptr1}");
        } else {
            puts("Not authorized!");
        }        
    } else if(!strncmp(buffer, "print", 5)) {
        if(strlen(buffer) != 5) {
            printf("No arguments given\n");
            return;
        }
        char* target = malloc(32);
        char* token = strtok(NULL, " ");
        if(strlen(token) > 1) strcpy(target, token);
        puts(target);
        if(strtok(NULL, " ")) {
            puts("Too many arguments!");
        }
        free(target);
    } else if(!strncmp(buffer, "user", 4)) {
        puts(getenv("USER"));
    }
}

void print_prompt() {
   printf("$> ");   
   fflush(stdout);
}

void read_command() {
    int i;
    char* input = malloc(32);
    assert(input);
    
    print_prompt();
    if(!fgets(input, 32, stdin)) exit(0);
    for(i = 0; i < 32; i++) {
        if(input[i] == '\n' || input[i] == '\r' || input[i] == 0) {
            input[i] == 0;
            break;
        }
    }
    if(i >= 32) {
        i = 32;
        input[i] = 0;
    }
    handle_command(input, i);
}

int main() {
    gid_t gid = getegid();
    setresgid(gid,gid,gid);
    
    FILE* f = fopen("flag.txt", "r");
    fgets(the_flag, sizeof(the_flag), f);
    fclose(f);
    
    while(1) {
        read_command();
    }
    return 0;
}

 
