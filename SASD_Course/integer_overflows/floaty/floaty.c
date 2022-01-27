//
// floaty.c - fun with floating point numbers and GCC's nested function extension
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/types.h>
int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

//----------------------------------------------------------------------
int main(void)
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  unsigned buf[16] = { 0, };

  // For simplicity: Make stdin and stdout unbuffered
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);

  // Read some user input
  __extension__ int read_numbers(void)
  {
    unsigned start, end;

    // Read start, end, and prefix
    if (scanf("%u %u", &start, &end) != 2) 
    {
      fprintf(stderr, "error: please enter start and end of the range\n");
      return 0;
    }

    if (end < start || end - start >= 16) 
    {
      fprintf(stderr, "error: bad range\n");
      return 0;
    }

    // Read the input char by char
    unsigned *ptr = &buf[0];
    for (float i = start; i < end; i += 1) 
    {
      if (scanf("%x", ptr++) != 1) {
	     break;
      }

      // You'll get an important hint
      if (ptr - buf == 42) 
      {
      	unsigned hint = (unsigned) &main ^ 0xDEADC0DE;
      	printf("Hint: 0x%08x\n", hint);
      }
    }

    return 1;
  }

  if (!read_numbers()) {
    return EXIT_FAILURE;
  }

  // Now sort the numbers
  // (we used glibc's qsort and GCC's nested functions extension)
  __extension__ int compare_uints(const void *p_a, const void *p_b)
  {
    int i = (const unsigned *) p_a - buf;
    int j = (const unsigned *) p_b - buf;
    return buf[i] > buf[j] ? 1 : buf[i] < buf[j] ? -1 : 0;
  }

  puts("--- sorting");
  qsort(buf, 16, sizeof(unsigned), &compare_uints);

  // And print the sorted numbers
  puts("--- result");
  for (unsigned i = 0; i < 16; ++i) {
    printf("buf[%2d] %x\n", i, buf[i]);
  }

  return EXIT_SUCCESS;
}
