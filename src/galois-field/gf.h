/**
 * @file gf.h
 * @author Lei Peng (peng.lei@n-hop.com)
 * @brief
 * @version 1.0.0
 * @date 2025-04-11
 *
 * Copyright (c) None.
 *
 */
#ifndef GF_H_
#define GF_H_

#include <cstdint>

enum class GfImplType : uint8_t {
  GF_LUT,
  GF_POLY,
};

typedef uint8_t (*gf_mul_func)(uint8_t, uint8_t);
typedef uint8_t (*gf_div_func)(uint8_t, uint8_t);
typedef uint8_t (*gf_add_func)(uint8_t, uint8_t);
typedef uint8_t (*gf_sub_func)(uint8_t, uint8_t);
typedef uint8_t (*gf_inv_func)(uint8_t);

class GaloisField {
 public:
  gf_mul_func mul = nullptr;
  gf_div_func div = nullptr;
  gf_add_func add = nullptr;
  gf_sub_func sub = nullptr;
  gf_inv_func inv = nullptr;
};

bool InitGaloisField(GaloisField& gf, const GfImplType& type);

#endif  // GF_H_
