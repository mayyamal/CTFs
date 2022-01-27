//
// ntt.c - Number-Theoretic Transform
//
// This file implements a two-dimensional variant of the Number-Theoretic-Transform (NTT)
// (a generalized version of the Discrete Fourier Transform) on 8x8 blocks.
//
// We compute over a prime field modulo p with p=257.
//
#include "pgmntt.h"

//
// Forward transformation matrix for the 1-D NTT
//
static const uint16_t ntt_forward[8][8] = {
  {  1,   1,   1,   1,   1,   1,   1,   1 },
  {  1,  64, 241,   4, 256, 193,  16, 253 },
  {  1, 241, 256,  16,   1, 241, 256,  16 },
  {  1,   4,  16,  64, 256, 253, 241, 193 },
  {  1, 256,   1, 256,   1, 256,   1, 256 },
  {  1, 193, 241, 253, 256,  64,  16,   4 },
  {  1,  16, 256, 241,   1,  16, 256, 241 },
  {  1, 253,  16, 193, 256,   4, 241,  64 }
};

//
// Inverse transformation matrix for the 1-D NTT
//
static const uint16_t ntt_inverse[8][8] = {
 { 225, 225, 225, 225, 225, 225, 225, 225},
 { 225, 128,   2, 249,  32, 129, 255,   8},
 { 225,   2,  32, 255, 225,   2,  32, 255},
 { 225, 249, 255, 128,  32,   8,   2, 129},
 { 225,  32, 225,  32, 225,  32, 225,  32},
 { 225, 129,   2,   8,  32, 128, 255, 249},
 { 225, 255,  32,   2, 225, 255,  32,   2},
 { 225,   8, 255, 129,  32, 249,   2, 128},
};

static void ntt_8x8_core(uint16_t out[8][8], const uint16_t in[8][8],
			 const uint16_t kernel[8][8])
{
  // Compute the 1-D NTT along the rows
  uint16_t t0[8][8];
  
  for (uint16_t i = 0; i < 8; ++i) {
    for (uint16_t j = 0; j < 8; ++j) {
      uint32_t v = 0;
      
      for (uint16_t k = 0; k < 8; ++k) {
	v = (v + in[i][k] * (uint32_t) kernel[k][j]) % 257;	  
      }

      t0[i][j] = v;
    }
  }

  // Then compute the 1-D NTT along the columns
  for (uint16_t i = 0; i < 8; ++i) {
    for (uint16_t j = 0; j < 8; ++j) {
      uint32_t v = 0;
      
      for (uint16_t k = 0; k < 8; ++k) {
	v = (v + t0[k][j] * (uint32_t) kernel[i][k]) % 257;	  
      }

      out[i][j] = v;
    }
  }
}

void ntt_8x8(uint16_t out[8][8], const uint16_t in[8][8])
{
  ntt_8x8_core(out, in, ntt_forward);
}


void inverse_ntt_8x8(uint16_t out[8][8], const uint16_t in[8][8])
{
  ntt_8x8_core(out, in, ntt_inverse);  
}
