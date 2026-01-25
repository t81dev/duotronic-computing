#pragma once
#include "tsl/trit.hpp"
#include <cstdint>
#include <optional>

namespace tsl {

// Stable byte encoding (v0.1):
//   neg (-1) -> 0xFF
//   zer ( 0) -> 0x00
//   pos (+1) -> 0x01
constexpr std::uint8_t encode(trit t) noexcept {
  switch (t) {
    case trit::neg: return 0xFF;
    case trit::zer: return 0x00;
    case trit::pos: return 0x01;
  }
  return 0x00; // defensive, unreachable for valid trit
}

constexpr std::optional<trit> decode(std::uint8_t b) noexcept {
  if (b == 0xFF) return trit::neg;
  if (b == 0x00) return trit::zer;
  if (b == 0x01) return trit::pos;
  return std::nullopt;
}

} // namespace tsl
