#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

 
//bypass the mechanisms and 
//make the program open the restricted file

int handleInput(int argument_count,char** arguments);


int main(int argc, char **argv, char **envp)
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  int error_code = handleInput(argc,argv);
  return error_code;
}


int handleInput(int argument_count,char** arguments)
{
  char file_content[1024];
  int file_descriptor = 0;
 
  if(argument_count == 1) {
    printf("Usage: <%s [file to read]>\n", arguments[0]);
    return 0x12;
  }
   
  //if file name is restricted_file no access
  if(strstr(arguments[1], "flag") != NULL) {
    printf("You are not allowed to read this file '%s'\n", arguments[1]);
    return 0x34;
  }
  
  //
  file_descriptor = open(arguments[1], O_RDONLY);
  if(file_descriptor == -1) {
    printf("Nope, that is not allowed %s", arguments[1]);
    return 0x56;
  }
 
  if(read(file_descriptor, file_content, sizeof(file_content)) == -1) {
    printf("Unable to read file_descriptor %d", file_descriptor);
    return 0x78;
  }
 
  //print file content
  printf("%s",file_content);
  return 0;
}
