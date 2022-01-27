#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_flag()
{
  char* flag = NULL;
  size_t n = 0;
  FILE* flagfile = fopen("flag.txt", "r");
  if (flagfile == NULL) {
    err(1, "Sorry couldn't open flag :( report this to the admin!");
  }
  getline(&flag, &n, flagfile);
  printf("There you go:\n %s\n", flag);
  free(flag);
}

void vuln(void)
{
  char buffer[64];
  fgets(buffer, 0x64, stdin);
}

int main(int argc, char** argv)
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);
  vuln();
  return 0;
}
