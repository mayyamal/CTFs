#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

int echo() 
{
    //in order 
    setbuf(stdout, 0);
    char buf[0x96];
    memset(buf, 0, 0x96);
    printf("Enter some content:");
    ssize_t b = read(0, buf, 0x190);
    write(1, buf, b);
    printf("ROP ME if you can :P");
    return 0;
}

//hm, why is this here :) ?
void hint() 
{
    asm("pop %rdi; pop %rsi; pop %rdx; ret");
}

int main(int argc, char *argv[])
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  echo();
  return 0;
}
