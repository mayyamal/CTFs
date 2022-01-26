#include <stdio.h>
#include <alloca.h>
#include <string.h>

#define MAX_SIZE 512

int main();

void start_shellcode(char* shellcode)  {
    // put it on the (executable) stack
    char* sc = alloca(MAX_SIZE);
    strncpy(sc, shellcode, MAX_SIZE);
              
    // black magic with a bit of voodoo
    for(size_t i = 0; i < 10; i++) {
        if(*(&i + i) >= (size_t)main && *(&i + i) < (size_t)main + 0x100) {
            if(*(&i + i - 1) >= (size_t)&i - 4 * MAX_SIZE && *(&i + i - 1) <= (size_t)&i + 4 * MAX_SIZE) {
              *(&i + i) = (size_t)sc;
              break;
            }
        }
    }
}

int main() {
    char input[MAX_SIZE];
    int c, ptr = 0;
    while((c = getchar()) != EOF) {
        if((((c | 0x20) >= 'a' && (c | 0x20) <= 'z') || (c >= '0' && c <= '9')) && ptr < MAX_SIZE) {
            input[ptr++] = c;
        }
    }
    start_shellcode(input);
    return 0;
}
