//
// no idea how this ended up in our hacklet ;)
//
#include "pgmntt.h"

#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//----------------------------------------------------------------------
void codeofbugs(void)
{  
  fprintf(stderr, "- congratulations, you solved the first task:\n");
  // ... finally we return
  puts("--- Congratz enjoy your image ;)");
  fflush(stdout);
  system("cat flag.txt");
}
