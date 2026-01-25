#pragma once
#include "tsl/ops.hpp"
#include <cstddef>

namespace tsl {

struct counts {
  std::size_t neg = 0;
  std::size_t zer = 0;
  std::size_t pos = 0;
};

template <class It>
constexpr counts count(It first, It last) noexcept {
  counts c{};
  for (; first != last; ++first) {
    const trit t = *first;
    if (t == trit::neg) ++c.neg;
    else if (t == trit::pos) ++c.pos;
    else ++c.zer;
  }
  return c;
}

// majority: returns the value with the greatest count.
// ties (including "zer is max") resolve to zer.
// This is intentionally conservative; tagged Unknown can be added later.
template <class It>
constexpr trit majority(It first, It last) noexcept {
  const auto c = count(first, last);

  // Strict max checks
  if (c.pos > c.neg && c.pos > c.zer) return trit::pos;
  if (c.neg > c.pos && c.neg > c.zer) return trit::neg;

  // Any tie among maxima -> zer
  return trit::zer;
}

// sum with saturation
template <class It>
constexpr trit sum_sat(It first, It last) noexcept {
  int total = 0;
  for (; first != last; ++first) {
    total += to_int(*first);
  }
  return (total > 1) ? trit::pos
       : (total < -1) ? trit::neg
                      : from_sign(total);
}

template <class Policy, class It>
constexpr counts count_policy(It first, It last) noexcept {
  counts c{};
  for (; first != last; ++first) {
    const trit t = *first;

    if constexpr (Policy::zero_is_masked_in_reductions) {
      if (t == trit::zer) continue;
    }

    if (t == trit::neg) ++c.neg;
    else if (t == trit::pos) ++c.pos;
    else ++c.zer;
  }
  return c;
}

template <class Policy, class It>
constexpr trit majority_policy(It first, It last) noexcept {
  const auto c = count_policy<Policy>(first, last);

  if (c.pos > c.neg && c.pos > c.zer) return trit::pos;
  if (c.neg > c.pos && c.neg > c.zer) return trit::neg;

  return trit::zer;
}

template <class Policy, class It>
constexpr trit sum_sat_policy(It first, It last) noexcept {
  trit acc = trit::zer;
  for (; first != last; ++first) {
    const trit t = *first;
    if constexpr (Policy::zero_is_masked_in_reductions) {
      if (t == trit::zer) continue;
    }
    acc = add_sat(acc, t);
  }
  return acc;
}

} // namespace tsl
