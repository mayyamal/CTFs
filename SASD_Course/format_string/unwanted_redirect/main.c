#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


#include <sys/types.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

//TODO: remove function
void unsupportedOperation()
{
  printf("This will never be executed. Muahaha.\n");
  printf("WHAT?!");
  printf("How did you do that?\n");
  FILE* f = fopen("flag.txt", "r");
  assert(f);
  char c;
  while((c=fgetc(f))!=EOF){
        printf("%c",c);
  }

  fclose(f);
}

void echoService()
{
  //just echoing the users input
  //what could go wrong here :P
  char buffer[512];
  fgets(buffer, sizeof(buffer), stdin);
  printf(buffer);
  write(1,"Nope\n",5);
}

int main(int argc, char **argv)
{
  // For simplicity: Make stdin and stdout unbuffered
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  //start the echoService
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  echoService();
}
