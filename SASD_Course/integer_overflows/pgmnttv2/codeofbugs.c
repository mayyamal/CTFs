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
  fprintf(stderr, "- congratulations, zippy is pleased and hands out an image:\n");

  // It was (not yet) late ...
  union {    
    struct {
      uint32_t magic;
      void (*whatever)();
      void (*whyever)();
      void *myself;
    } __attribute__((packed)) x;
    
    uint8_t raw[16 * 16];
  } __attribute__((packed)) u = {
    .x = {
      // ... coffee became scarce ...
      .whatever = (void (*)()) &mmap,
      .magic    = UINT32_C(0x21677562),
      .whyever  = (void (*)()) &mprotect,
      .myself   = &u
    }
  };

  // Populate the weird image
  pgm_image_t *img = pgm_create(16, 16, 257);
  for (int y = 0; y < 8; ++y) {
    for (int x = 0; x < 8; ++x) {
      pgm_setpixel(img, x, y, u.raw[y * 8 + x]);
    }
  }

  // ... and someone filed a CVE related to an old SASE hacklet from last year [sic!] ...
  pgm_ntt_8x8(img, false);  
  pgm_save(stdout, img);
  pgm_free(img);

  // ... finally we return
  puts("--- time of read, time of rop ;)");
  fflush(stdout);
  
  read(STDIN_FILENO, u.raw, 4096);
}
