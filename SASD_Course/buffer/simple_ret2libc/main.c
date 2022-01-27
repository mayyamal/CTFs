#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/types.h>
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);


void do_fun_stuff()
{
  //TODO: do some really fun stuff here :P
  char* fun =  "I have got really much fun using my favourite shell: /bin/sh";
  char* fun2 = "Others prefer using cat flag.txt";
  return;
}

void command(){
  char buffer[0x70];

  int val = read(0, &buffer, 400);
  printf("Input was: %s\n", buffer);
  printf("Try harder...\n");
}

int main(int argc, char** argv) {
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  command();
  return 0x539;
}
