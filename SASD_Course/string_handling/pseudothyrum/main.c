//
// pseudothyrum.c - Passowrd check with backdoor?
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);


static const char backdoor[] = "errantis voluntas nulla est.";

//----------------------------------------------------------------------
static int sanity_check(const char *str)
{
  int valid = 1, c;

  while ((c = *str++) != '\0') {
    valid &= (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
      (c >= '0' && c <= '9') || (c == ' ');
  }

  return valid;
}

//----------------------------------------------------------------------
static int read_sane_line(char *buf, unsigned capacity)
{
  char *dst = buf;
  int c = EOF;

  while (dst - buf < capacity) {
    c = fgetc(stdin);
    if (c == EOF) {
      puts("i/o problem, giving up!");
      return 0;

    } else if (c == '\n') {
      *dst = '\0';
      break;

    } else {
      *dst++ = c;
    }
  }

  if (c != '\n') {
    puts("buffer overflow attempt detected, giving up!");
    return 0;
  }

  if (!sanity_check(buf)) {
    puts("insane input detected, giving up!");
    return 0;
  }

  return dst - buf;
}

//----------------------------------------------------------------------
int main(void)
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  char passphrase[128];
  int passlen;
  
  // Ask for the passphrase
  puts("passphrase?");
  if (!(passlen = read_sane_line(passphrase, sizeof(passphrase)))) {
    return EXIT_FAILURE;
  }

  // Now compare with the magic backdoor
  if (passlen != strlen(backdoor)) {
    puts("invalid password length");
    return EXIT_FAILURE;
  }
  if (strncmp(passphrase, backdoor, strlen(passphrase))) {
    puts("thou shalt not pass!");
    return EXIT_FAILURE;
  }
  puts("Congrats, you passed my (in)secure checks ;)");
  system("cat flag.txt");
  return EXIT_SUCCESS;
}
