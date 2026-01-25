// essays/tsl_ref/include/tsl/trit.hpp
#pragma once
#include <cstdint>

namespace tsl {

// Minimal ternary semantic scalar: {-1, 0, +1}.
// This type is intentionally small and explicit.
// - No implicit bool conversion.
// - No operator overloads.
// - No control-flow semantics.
// Higher-level semantics live in ops/reduce headers.
enum class trit : std::int8_t {
  neg = -1,
  zer =  0,
  pos =  1,
};

constexpr trit from_sign(long long x) noexcept {
  return (x > 0) ? trit::pos : (x < 0) ? trit::neg : trit::zer;
}

constexpr int to_int(trit t) noexcept {
  return static_cast<int>(static_cast<std::int8_t>(t));
}

// Total order is defined only for lattice-style ops (meet/join).
constexpr bool lt(trit a, trit b) noexcept { return to_int(a) < to_int(b); }
constexpr bool le(trit a, trit b) noexcept { return to_int(a) <= to_int(b); }
constexpr bool gt(trit a, trit b) noexcept { return to_int(a) > to_int(b); }
constexpr bool ge(trit a, trit b) noexcept { return to_int(a) >= to_int(b); }

} // namespace tsl
