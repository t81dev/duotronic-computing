#pragma once
#include "tsl/trit.hpp"

namespace tsl {

// Symmetric sign inversion.
// neg -> pos, zer -> zer, pos -> neg
constexpr trit negate(trit t) noexcept {
  return (t == trit::pos) ? trit::neg
       : (t == trit::neg) ? trit::pos
                          : trit::zer;
}

// Lattice-style meet/join over the total order neg < zer < pos.
// These are semantic aggregation helpers, not boolean logic.
constexpr trit meet(trit a, trit b) noexcept {
  return lt(a, b) ? a : b; // min
}

constexpr trit join(trit a, trit b) noexcept {
  return gt(a, b) ? a : b; // max
}

// Saturating addition over {-1, 0, +1}.
// This is intentionally not multi-trit arithmetic.
constexpr trit add_sat(trit a, trit b) noexcept {
  const int s = to_int(a) + to_int(b);
  return (s > 1) ? trit::pos
       : (s < -1) ? trit::neg
                  : from_sign(s);
}

} // namespace tsl
