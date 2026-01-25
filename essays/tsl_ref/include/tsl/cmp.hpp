#pragma once
#include "tsl/trit.hpp"
#include "tsl/policy.hpp"

namespace tsl {

// cmp returns:
//   neg if a < b
//   pos if a > b
//   zer if a == b
//
// Policy does not change the return value (still trit).
// Policy only affects whether zer is interpreted as "indeterminate" by helper APIs.
template <class Policy>
constexpr trit cmp(trit a, trit b) noexcept {
  const int da = to_int(a);
  const int db = to_int(b);

  if (da < db) return trit::neg;
  if (da > db) return trit::pos;
  return trit::zer;
}

// Under some policies, zer is treated as "indeterminate" in comparison contexts.
// This avoids overloading the trit value itself while still enabling experiments.
template <class Policy>
constexpr bool cmp_is_indeterminate(trit cmp_result) noexcept {
  if constexpr (Policy::zero_means_unknown_in_cmp) {
    return (cmp_result == trit::zer);
  } else {
    (void)cmp_result;
    return false;
  }
}

} // namespace tsl
