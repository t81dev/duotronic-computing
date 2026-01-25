#include <array>
#include <cassert>
#include "tsl/reduce.hpp"
#include "tsl/policy.hpp"

using tsl::trit;

int main() {
  using policy_mn = tsl::policy::masked_neutral;
  using policy_neutral = tsl::policy::neutral_as_neutral;

  constexpr std::array<trit,7> xs{
    trit::zer, trit::zer, trit::zer, trit::zer,
    trit::pos, trit::pos, trit::neg
  };

  assert(tsl::majority(xs.begin(), xs.end()) == trit::zer);
  assert(tsl::majority_policy<policy_mn>(xs.begin(), xs.end()) == trit::pos);
  assert(tsl::majority_policy<policy_neutral>(xs.begin(), xs.end()) == trit::zer);
  assert(tsl::sum_sat_policy<policy_mn>(xs.begin(), xs.end()) == trit::zer);

  return 0;
}
