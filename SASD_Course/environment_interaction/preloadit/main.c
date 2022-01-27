#define _GNU_SOURCE
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

// in this challenge everything is allowed :D but watch out, this hacklet
// will be marked as non-readable and non-writable
#define MR_BOND 7

static const char flag[] = "SASD{XXXXXXXXXXXXXXXXXXXXXXXXXX}";

int checkUID();

int main(int argc, char **argv, char **envp)
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);

  int ret = checkUID();
  if (ret)
  {
  	printf("ALERT\nYou are not agent 007\n");
  	return 0;
  }
  printf("Hello, Mr Bond\n");
  printf("%s\n", flag);
  return 0xCAFE;
}

int checkUID()
{
  if(getuid() == MR_BOND) 
  {
    return 0;
  }
  else
  {
  	return 1;
  }
}
