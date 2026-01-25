#include <array>
#include <cassert>
#include "tsl/reduce.hpp"

using tsl::trit;

int main() {
  // count
  {
    constexpr std::array<trit,5> xs{trit::neg, trit::zer, trit::pos, trit::pos, trit::zer};
    auto c = tsl::count(xs.begin(), xs.end());
    assert(c.neg == 1);
    assert(c.zer == 2);
    assert(c.pos == 2);
  }

  // majority basic
  {
    constexpr std::array<trit,3> xs{trit::pos, trit::pos, trit::neg};
    assert(tsl::majority(xs.begin(), xs.end()) == trit::pos);
  }

  // majority tie -> zer
  {
    constexpr std::array<trit,2> xs{trit::pos, trit::neg};
    assert(tsl::majority(xs.begin(), xs.end()) == trit::zer);
  }

  // majority where zer dominates -> zer
  {
    constexpr std::array<trit,5> xs{trit::zer, trit::zer, trit::pos, trit::neg, trit::zer};
    assert(tsl::majority(xs.begin(), xs.end()) == trit::zer);
  }

  // sum_sat
  {
    constexpr std::array<trit,4> xs{trit::neg, trit::neg, trit::pos, trit::zer};
    // -1 + -1 + +1 + 0 = -1 (saturating add stays within trit range)
    assert(tsl::sum_sat(xs.begin(), xs.end()) == trit::neg);
  }

  // sum_sat saturation to pos
  {
    constexpr std::array<trit,3> xs{trit::pos, trit::pos, trit::pos};
    assert(tsl::sum_sat(xs.begin(), xs.end()) == trit::pos);
  }

  return 0;
}
