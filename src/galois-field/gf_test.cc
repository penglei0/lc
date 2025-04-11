#include "gf.h"

#include <cstdint>
#include <iostream>

int main() {
  GaloisField gf_poly;
  GaloisField gf_lut;
  if (!InitGaloisField(gf_poly, GfImplType::GF_POLY)) {
    std::cerr
        << "Failed to initialize Galois Field with polynomial implementation."
        << std::endl;
    return -1;
  }
  if (!InitGaloisField(gf_lut, GfImplType::GF_LUT)) {
    std::cerr << "Failed to initialize Galois Field with LUT implementation."
              << std::endl;
    return -1;
  }
  for (int x = 0; x < 256; ++x) {
    for (int y = 0; y < 256; ++y) {
      uint8_t poly_result = gf_poly.mul(x, y);
      uint8_t lut_result = gf_lut.mul(x, y);
      if (poly_result != lut_result) {
        std::cerr << "Mismatch in multiplication: " << int(x) << " * " << int(y)
                  << " = " << int(poly_result) << " (poly), " << int(lut_result)
                  << " (lut)" << std::endl;
        return -1;
      }
    }
  }
  std::cout << "All multiplication tests passed!" << std::endl;

  for (int x = 1; x < 256; ++x) {
    for (int y = 1; y < 256; ++y) {
      uint8_t poly_result = gf_poly.div(x, y);
      uint8_t lut_result = gf_lut.div(x, y);
      if (poly_result != lut_result) {
        std::cerr << "Mismatch in division: " << int(x) << " / " << int(y)
                  << " = " << int(poly_result) << " (poly), " << int(lut_result)
                  << " (lut)" << std::endl;
        return -1;
      }
    }
  }
  std::cout << "All division tests passed!" << std::endl;
  return 0;
}
