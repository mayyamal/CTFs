//
// zippy's call of bugs
//
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static unsigned buggy_cookie;

//----------------------------------------------------------------------
void callofbugs(unsigned cookie_0)
{
  printf("-- Challenging with a cookie: 0x%08x\n", cookie_0);
  if (cookie_0 != buggy_cookie) 
  {
    puts("[!] Incorrect cookie");
    printf("the correct cookie would have been: %08x\n", cookie_0);
    abort();
  } else 
  {
    int c;
    FILE *file;
    file = fopen("flag.txt", "r");
    if (file) {
      while ((c = getc(file)) != EOF)
        putchar(c);
      fclose(file);
    } 
  }
}

//----------------------------------------------------------------------
static __attribute__((constructor)) void setup_bugs(void)
{
  // Store some random value related to the stack canary
  const unsigned *fp = __builtin_frame_address(0);
  buggy_cookie = fp[-3];
}
