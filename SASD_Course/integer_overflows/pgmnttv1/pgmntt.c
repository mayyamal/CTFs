//
// This tool reads a ascii pgm image and inverts the image.
//
#include "pgmntt.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/types.h>

int setresgid(gid_t rgid, gid_t egid, gid_t sgid);

static pgm_image_t* load_image(const char *filename);
static void save_image(const char *filename, const pgm_image_t *img);

//----------------------------------------------------------------------
int main(int argc, char **argv)
{
  gid_t gid = getegid();
  setresgid(gid,gid,gid);
  pgm_image_t *img = NULL;

  // Parameter check
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "usage: %s <forward|inverse|filter:<coeff>> [infile [outfile]]\n", argv[0]);
    goto err;
  }

  const char *mode = argv[1];
  const char *infile = argc >= 3 ? argv[2] : NULL;
  const char *outfile = argc >= 4 ? argv[3] : NULL;

  // Load the source image ...
  img = load_image(infile);
  if (!img) {
    fprintf(stderr, "error: failed to load source pgm image\n");
    goto err;
  }

  // Determine type of transformation
  if (!strcmp(mode, "forward")) {
    // Forward NTT transform
    pgm_ntt_8x8(img, false);

  } else if (!strcmp(mode, "inverse")) {
    // Inverse NTT transform
    pgm_ntt_8x8(img, true);

  } else if (!strncmp(mode, "filter:", 7)) {
    // Filter with given coefficient file
    if (!pgm_filter_8x8(img, mode + 7)) {
      goto err;
    }

  } else {
    fprintf(stderr, "error: unsupported transform type '%s'\n", mode);
    goto err;
  }

  save_image(outfile, img);

 err:
  pgm_free(img);
  return 0;
}

//----------------------------------------------------------------------
static pgm_image_t* load_image(const char *filename)
{
  FILE *f = NULL;
  pgm_image_t *img = NULL;

  // Open the input file
  if (filename && strcmp(filename, "-") != 0) {
    f = fopen(filename, "rt");
    if (!f) {
      fprintf(stderr, "error: failed to open input file '%s'\n", filename);
      goto err;
    }
  }

  // Now load the image
  img = pgm_load(f ? f : stdin);

 err:
  if (f) {
    fclose(f);
  }

  return img;
}

//----------------------------------------------------------------------
static void save_image(const char *filename, const pgm_image_t *img)
{
  FILE *f = NULL;

  // Open the input file
  if (filename && strcmp(filename, "-") != 0) {
    f = fopen(filename, "wt");
    if (!f) {
      fprintf(stderr, "error: failed to open output file '%s'\n", filename);
      goto err;
    }
  }

  // Now load the image
  pgm_save(f ? f : stdout, img);

 err:
  if (f) {
    fclose(f);
  }
}
