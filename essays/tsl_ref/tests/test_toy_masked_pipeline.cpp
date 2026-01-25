#include <array>
#include <cassert>
#include <cstddef>
#include "tsl/reduce.hpp"
#include "tsl/policy.hpp"

using tsl::trit;

struct sample_bin {
  int value;
  bool masked;
};

static void baseline_binary_masked() {
  constexpr std::array<sample_bin, 9> xs{{
    { 0, true },
    { 0, true },
    { 0, true },
    { 0, true },
    {+1,false },
    {+1,false },
    {-1,false },
    { 0,false },
    { 0,false },
  }};

  std::size_t pos = 0, neg = 0, zer = 0;
  for (auto &s : xs) {
    if (s.masked) continue;
    if (s.value > 0) ++pos;
    else if (s.value < 0) ++neg;
    else ++zer;
  }

  int maj = 0;
  if (pos > neg && pos > zer) maj = +1;
  else if (neg > pos && neg > zer) maj = -1;
  else maj = 0;

  assert(maj == 0);
}

static void tsl_masked_policy() {
  using MN = tsl::policy::masked_neutral;

  constexpr std::array<trit, 9> xs{
    trit::zer, trit::zer, trit::zer, trit::zer,
    trit::pos, trit::pos, trit::neg,
    trit::zer, trit::zer
  };

  assert(tsl::majority_policy<MN>(xs.begin(), xs.end()) == trit::pos);
}

int main() {
  baseline_binary_masked();
  tsl_masked_policy();
  return 0;
}
