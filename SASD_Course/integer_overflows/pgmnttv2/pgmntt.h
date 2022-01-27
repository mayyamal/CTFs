#ifndef PGMNTT_8X8_H_
#define PGMNTT_8X8_H_ 1

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

//----------------------------------------------------------------------
// 8x8 Number-Theoretic Transform
//
void ntt_8x8(uint16_t out[8][8], const uint16_t in[8][8]);
void inverse_ntt_8x8(uint16_t out[8][8], const uint16_t in[8][8]);

//----------------------------------------------------------------------
// PGM image manipulation
//
typedef struct pgm_image pgm_image_t;
pgm_image_t* pgm_create(uint16_t width, uint16_t height, uint16_t max_color);
void pgm_free(pgm_image_t *pgm);

uint16_t pgm_width(pgm_image_t *img);
uint16_t pgm_height(pgm_image_t *img);

void pgm_setpixel(pgm_image_t *img, uint16_t x, uint16_t y, uint16_t value);
uint16_t pgm_getpixel(pgm_image_t *img, uint16_t x, uint16_t y);

pgm_image_t* pgm_load(FILE *in);
bool pgm_save(FILE *out, const pgm_image_t *img);
void pgm_ntt_8x8(pgm_image_t *pgm, bool inverse);
bool pgm_filter_8x8(pgm_image_t *img, const char *filter);

#endif // PGMNTT_8X8_H_
