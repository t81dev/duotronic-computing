#include <cassert>
#include "tsl/cmp.hpp"

using tsl::trit;

int main() {
  using NAN = tsl::policy::neutral_as_neutral;
  using ZAU = tsl::policy::zero_as_unknown;

  // Basic ordering
  assert(tsl::cmp<NAN>(trit::neg, trit::zer) == trit::neg);
  assert(tsl::cmp<NAN>(trit::pos, trit::zer) == trit::pos);
  assert(tsl::cmp<NAN>(trit::zer, trit::zer) == trit::zer);

  // Policy interpretation (only affects indeterminate helper)
  assert(tsl::cmp_is_indeterminate<NAN>(trit::zer) == false);
  assert(tsl::cmp_is_indeterminate<ZAU>(trit::zer) == true);

  // Non-zero compare results are never indeterminate
  assert(tsl::cmp_is_indeterminate<ZAU>(trit::neg) == false);
  assert(tsl::cmp_is_indeterminate<ZAU>(trit::pos) == false);

  return 0;
}
