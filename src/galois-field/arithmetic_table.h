/**
 * @file arithmetic_table.h
 * @author Lei Peng (peng.lei@n-hop.com)
 * @brief
 * @version 1.0.0
 * @date 2025-04-11
 *
 * Copyright (c) None.
 *
 */

#ifndef ARITHMETIC_TABLE_H_
#define ARITHMETIC_TABLE_H_

#include <array>
#include <cstdint>

// x^4 + x + 1
// polynomial: x^4 + x + 1 -> 0x13
constexpr uint16_t GF4_MOD = 0x13;
// AES polynomial: x^8 + x^4 + x^3 + x^2 + 1 -> 0x11D
constexpr uint16_t GF8_MOD = 0x11D;
extern std::array<uint8_t, 65536> Gf8MultiplicationTable;
extern std::array<uint8_t, 65280> Gf8DivisionTable;

#endif  // ARITHMETIC_TABLE_H_
