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

class GaloisField {
 public:
  uint8_t (*mul)(uint8_t, uint8_t) = nullptr;
  uint8_t (*div)(uint8_t, uint8_t) = nullptr;
  uint8_t (*add)(uint8_t, uint8_t) = nullptr;
  uint8_t (*sub)(uint8_t, uint8_t) = nullptr;
  uint8_t (*inv)(uint8_t) = nullptr;
  GfImplType gf_type = GfImplType::GF_LUT;
};

bool InitGaloisField(GaloisField& gf, const GfImplType& type);

#endif  // GF_H_
