#include <array>
#include <cassert>
#include <cstddef>
#include "tsl/reduce.hpp"
#include "tsl/cmp.hpp"

// Toy workload: "votes" in {-1,0,+1}. Some entries are neutral and should not bias.
// Compare two approaches: binary conventions vs. explicit trit semantics.
struct vote_bin {
  int value;      // -1, 0, +1
  bool valid;     // if false, entry should be ignored
  bool neutral;   // if true, should not bias aggregates (even if valid)
};

static void baseline_binary_style() {
  constexpr std::array<vote_bin, 7> xs{{
    {+1, true,  false},
    {-1, true,  false},
    { 0, true,  true },  // explicit neutral
    {+1, true,  false},
    { 0, false, false},  // invalid
    {+1, true,  false},
    { 0, true,  true },  // explicit neutral
  }};

  std::size_t pos = 0, neg = 0;
  for (auto &v : xs) {
    if (!v.valid) continue;
    if (v.neutral) continue;
    if (v.value > 0) ++pos;
    else if (v.value < 0) ++neg;
  }

  int maj = 0;
  if (pos > neg) maj = +1;
  else if (neg > pos) maj = -1;

  int s = 0;
  for (auto &v : xs) {
    if (!v.valid) continue;
    if (v.neutral) continue;
    s += v.value;
  }
  if (s > 1) s = 1;
  if (s < -1) s = -1;

  assert(maj == +1);
  assert(s == +1);
}

static void tsl_style() {
  constexpr std::array<tsl::trit, 5> xs{{
    tsl::trit::pos,
    tsl::trit::neg,
    tsl::trit::zer,
    tsl::trit::pos,
    tsl::trit::pos,
  }};

  const auto maj = tsl::majority(xs.begin(), xs.end());
  const auto s   = tsl::sum_sat(xs.begin(), xs.end());

  assert(maj == tsl::trit::pos);
  assert(s   == tsl::trit::pos);

  using policy_neutral = tsl::policy::neutral_as_neutral;
  using policy_za = tsl::policy::zero_as_unknown;

  auto r = tsl::cmp<policy_neutral>(maj, maj);
  assert(r == tsl::trit::zer);

  assert(tsl::cmp_is_indeterminate<policy_neutral>(r) == false);
  assert(tsl::cmp_is_indeterminate<policy_za>(r) == true);
}

int main() {
  baseline_binary_style();
  tsl_style();
  return 0;
}
