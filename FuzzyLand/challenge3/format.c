#include <stdio.h>
#include <string.h>

char secret[15] __attribute__ ((section (".secret")));

int main(int argc, char* argv[]) {
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  
  char buffer[16];
  strcpy(secret, "<THE FLAG!>");
  fgets(buffer, 16, stdin);
  printf(buffer);
} 
