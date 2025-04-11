/**
 * @file gf.cc
 * @author Lei Peng (peng.lei@n-hop.com)
 * @brief
 * @version 1.0.0
 * @date 2025-04-11
 *
 * Copyright (c) None.
 *
 */

#include "gf.h"

#include "arithmetic_table.h"

// gf poly multiplication
uint8_t gf_poly_mul(uint8_t a, uint8_t b) {
  uint16_t product = 0;
  for (int i = 0; i < 8; ++i) {
    if (b & (1 << i)) {
      product ^= uint16_t(a) << i;
    }
  }
  for (int bit = 15; bit >= 8; --bit) {
    if (product & (1 << bit)) {
      product ^= GF8_MOD << (bit - 8);
    }
  }
  return uint8_t(product & 0xFF);
}
uint8_t gf_poly_pow(uint8_t a, uint8_t exp) {
  uint8_t result = 1;
  while (exp) {
    if (exp & 1) {
      result = gf_poly_mul(result, a);
    }
    a = gf_poly_mul(a, a);
    exp >>= 1;
  }
  return result;
}
uint8_t gf_poly_inv(uint8_t a) { return gf_poly_pow(a, 254); }
uint8_t gf_poly_div(uint8_t a, uint8_t b) {
  return gf_poly_mul(a, gf_poly_inv(b));
}

// gf lut(lookup table)
uint8_t gf_lut_mul(uint8_t a, uint8_t b) {
  return Gf8MultiplicationTable[a << 8 | b];
}
uint8_t gf_lut_div(uint8_t a, uint8_t b) {
  return Gf8DivisionTable[(a << 8) + (b - a - 1)];
}
uint8_t gf_lut_add(uint8_t a, uint8_t b) { return a ^ b; }
uint8_t gf_lut_sub(uint8_t a, uint8_t b) { return a ^ b; }
uint8_t gf_lut_inv(uint8_t a) { return Gf8MultiplicationTable[0xFF - a]; }

bool InitGaloisField(GaloisField& gf, const GfImplType& type) {
  switch (type) {
    case GfImplType::GF_LUT:
      gf.mul = gf_lut_mul;
      gf.div = gf_lut_div;
      gf.add = gf_lut_add;
      gf.sub = gf_lut_sub;
      gf.inv = gf_lut_inv;
      break;
    case GfImplType::GF_POLY:
      gf.mul = gf_poly_mul;
      gf.div = gf_poly_div;
      gf.add = gf_lut_add;
      gf.sub = gf_lut_sub;
      gf.inv = gf_poly_inv;
      break;
    default:
      return false;
  }
  return true;
}