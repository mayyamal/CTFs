#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/types.h>
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

void validatePassword(char* secret) 
{
  unsigned char password_length = strlen(secret);
  if(password_length >= 5 && password_length < 12) 
  {
    if(!strncmp(secret+12, "1234", 4))
    {
      system("cat flag.txt");
    }
    else
    {
      puts("Your secret password got stored :)");
    }
  }
  else 
  {
    puts("Nope, wrong password length\n");
  }
}

//----------------------------------------------------------------------
int main(int argc, char* argv[])
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  // For simplicity: Make stdin and stdout unbuffered
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  
  char input[512];
  if(argc != 2) 
  {
    puts("Wrong usage");
    return 5;
  }
  memset(input, 0x00, sizeof(input));
  strncpy(input, argv[1], sizeof(input) - 1);
  validatePassword(input);
  return 0;
}
