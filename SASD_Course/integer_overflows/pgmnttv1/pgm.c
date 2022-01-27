//
// pgm.c - pgm image load/store routines
//
#include "pgmntt.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Internal structure for holding the image
struct pgm_image
{
  uint16_t width;
  uint16_t height;
  uint16_t max_color;
  uint16_t data[];
};

//----------------------------------------------------------------------
// Convenience wrapper around fgets
//
static char* get_line(char *line, size_t size, FILE *in)
{
  size_t len;

  // Grab the line
  if (!fgets(line, size, in)) {
    perror("error: i/o error (failed to read a line)");
    return 0;
  }

  // Trim the '\n', fail if nothing could be found
  len = strlen(line);
  if (len < 1 || line[len - 1] != '\n') {
    return 0;
  }

  line[len - 1] = '\0';
  return line;
}

//----------------------------------------------------------------------
pgm_image_t* pgm_create(uint16_t width, uint16_t height, uint16_t max_color)
{
  pgm_image_t *pgm = malloc(sizeof(pgm_image_t) + sizeof(uint16_t) * width * height);
  if (!pgm) {
    return NULL;
  }

  pgm->width = width;
  pgm->height = height;
  pgm->max_color = max_color;
  memset(pgm->data, 0, sizeof(uint16_t) * width * height);
  return pgm;
}

//----------------------------------------------------------------------
void pgm_free(pgm_image_t *pgm)
{
  if (pgm) {
    memset(pgm, 0, sizeof(pgm_image_t) + sizeof(uint16_t) * pgm->width * pgm->height);
    free(pgm);
  }
}

//----------------------------------------------------------------------
// Save a PGM image from a pgm_image_t structure to a file stream.
//
bool pgm_save(FILE *out, const pgm_image_t *img)
{
  uint16_t max_gray = 0;
  for (int n = 0; n < img->width * img->height; ++n) {
    max_gray = (img->data[n] > max_gray)? img->data[n] : max_gray;
  }

  fprintf(out, "P2\n# Nothing to hide ;)\n%hu %hu\n%hu\n",
	  img->width, img->height, max_gray);

  const uint16_t *p = img->data;
  for (int y = 0; y < img->height; ++y) {
    for (int x = 0; x < img->width; ++x) {
      fprintf(out, (x > 0 ? " %-3hu" : "%-3hu"), *p++);
    }

    fprintf(out, "\n");
  }

  return 0;
}

//----------------------------------------------------------------------
uint16_t pgm_width(pgm_image_t *img)
{
  return img ? img->width : 0;
}

//----------------------------------------------------------------------
uint16_t pgm_height(pgm_image_t *img)
{
  return img ? img->height : 0;
}

//----------------------------------------------------------------------
void pgm_setpixel(pgm_image_t *img, uint16_t x, uint16_t y, uint16_t value)
{
  if (img && img->width > x && img->height > y) {
    img->data[img->width * y + x] = value;
  }
}

//----------------------------------------------------------------------
uint16_t pgm_getpixel(pgm_image_t *img, uint16_t x, uint16_t y)
{
  uint16_t v = 0;
  if (img && x < img->width && y < img->height) {
    v =img->data[img->width * y + x];
  }
  return v;
}

//----------------------------------------------------------------------
// Load a PGM image from a file stream into a pgm_image_t structure.
//
pgm_image_t* pgm_load(FILE *in)
{
  pgm_image_t *img = NULL;
  bool success = false;
  uint16_t width, height, max_color;
  char line[1024];

  // P2 header
  if (!get_line(line, sizeof(line), in)) {
    goto err;

  } else if (strcmp(line, "P2") != 0) {
    fprintf(stderr, "error: expected P2 image header\n");
    goto err;
  }

  // Skip comment lines
  do {
    if (!get_line(line, sizeof(line), in)) {
      goto err;
    }
  } while (line[0] == '#');

  // Read the next parts of the header
  if (sscanf(line, "%hu%hu", &width, &height) != 2) {
    perror("error: malformed width/height information");
    goto err;
  }

  if (!get_line(line, sizeof(line), in) ||
      sscanf(line, "%hu", &max_color) != 1) {
    perror("error: malformed color depth information");
    goto err;
  }

  // Allocate the image
  img = pgm_create(width, height, max_color);
  if (!img) {
    fprintf(stderr, "error: image allocation failed\n");
    goto err;
  }

  // Now load the data
  uint16_t *p = img->data;
  for (int y = 0; !feof(in) && !ferror(in) && y < img->height; ++y) {
    for (int x = 0; x < img->width; ++x) {
      if (fscanf(in, "%hu", p++) != 1) {
	printf("error: failed to read pixel at (%d,%d) - ignoring the rest\n", x, y);
	goto err;
      }
    }
  }

  // Loading succeeded
  success = true;

 err:
  if (!success) {
    pgm_free(img);
    img = NULL;
  }

  return img;
}

//----------------------------------------------------------------------
void pgm_ntt_8x8(pgm_image_t *pgm, bool inverse)
{
  uint16_t tmp[8][8];

  for (uint16_t row = 0; row < pgm->height / 8; ++row) {
    for (uint16_t col = 0; col < pgm->width / 8; ++col) {
      // Copy the current block into the input buffer
      for (uint16_t y = 0; y < 8; ++y) {
	for (uint16_t x = 0; x < 8; ++x) {
	  tmp[y][x] = pgm->data[(row * 8 + y) * pgm->width + col * 8 + x];
	}
      }

      if (inverse) {
	inverse_ntt_8x8(tmp, tmp);
      } else {
	ntt_8x8(tmp, tmp);
      }

      // Copy the output buffer back into the block
      for (uint16_t y = 0; y < 8; ++y) {
	for (uint16_t x = 0; x < 8; ++x) {
	  pgm->data[(row * 8 + y) * pgm->width + col * 8 + x] = tmp[y][x];
	}
      }
    }
  }
}

//----------------------------------------------------------------------
static bool pgm_filter_coeff_load(uint16_t kernel[8][8], FILE *f,
				  uint8_t width, uint8_t height)
{
  uint8_t size = width * height * sizeof(uint16_t);
  uint8_t buf[size];

  if (fread(buf, 1, width * height * sizeof(uint16_t), f) != size) {
    fprintf(stderr, "error: failed to read raw filter data\n");
    return false;

  } else if (width != 8 || height != 8) {
    fprintf(stderr, "error: unsupported filter size (only 8x8 is supported at the moment)\n");
    return false;
  }

  // Extract the filter coefficients (the are stored in big-endian format for portability)
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      int off = sizeof(uint16_t) * (j * 8 + i);
      kernel[j][i] = ((uint16_t) buf[off + 0] << 8) | (uint16_t) buf[off + 1];
    }
  }

  // Forward transform the convolution kernel
  ntt_8x8(kernel, kernel);
  return true;
}

//----------------------------------------------------------------------
static bool pgm_filter_load(uint16_t kernel[8][8], const char *filter)
{
  FILE *f = NULL;
  bool success = false;
  uint8_t hdr[6];

  // Open the filter input file
  f = fopen(filter, "rb");
  if (!f) {
    fprintf(stderr, "error: failed to open filter file '%s'\n", filter);
    goto err;
  }

  // Read the filter header
  if (fread(hdr, sizeof(hdr), 1, f) != 1) {
    fprintf(stderr, "error: i/o error while reading the filter header\n");
    goto err;
  }

  if (hdr[0] != 'f' || hdr[1] != 'i' || hdr[2] != 'l' || hdr[3] != 't') {
    fprintf(stderr, "error: bad filter header magic\n");
    goto err;
  }

  // Read and translate the raw filter coefficients
  if (!hdr[4] || !hdr[5] ||
      hdr[4] >= (UINT8_MAX / 8) ||
      hdr[5] >= (UINT8_MAX / 8)) {
    fprintf(stderr, "error: invalid filter size\n");
    goto err;
  }

  // Load the coefficients
  success = pgm_filter_coeff_load(kernel, f, hdr[4], hdr[5]);

 err:
  if (f) {
    fclose(f);
  }

  return success;
}

//----------------------------------------------------------------------
bool pgm_filter_8x8(pgm_image_t *img, const char *filter)
{
  uint16_t kernel[8][8];

  // Load the convolution kernel of the filter
  if (!pgm_filter_load(kernel, filter)) {
    fprintf(stderr, "error: failed to load the filter coefficients\n");
    return false;
  }

  // Forward transform the image
  pgm_ntt_8x8(img, false);

  // Multiply with the transformed filter coefficients
  // (= convolution with filter after inverse transformation)

  for (int j = 0; j < img->height; ++j) {
    for (int i = 0; i < img->width; ++i) {
      unsigned index = j * img->width + i;
      img->data[index] = (img->data[index] * kernel[j % 8][i % 8]) % 257;
    }
  }

  // Inverse transformation of the image
  pgm_ntt_8x8(img, true);
  return true;
}
