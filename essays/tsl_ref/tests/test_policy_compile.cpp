#include <type_traits>
#include "tsl/policy.hpp"

static_assert(tsl::policy::neutral_as_neutral::zero_means_unknown_in_cmp == false);
static_assert(tsl::policy::zero_as_unknown::zero_means_unknown_in_cmp == true);

static_assert(tsl::policy::neutral_as_neutral::zero_is_masked_in_reductions == false);
static_assert(tsl::policy::zero_as_unknown::zero_is_masked_in_reductions == false);
static_assert(tsl::policy::masked_neutral::zero_is_masked_in_reductions == true);

static_assert(tsl::policy::is_policy_v<tsl::policy::masked_neutral>);

static_assert(tsl::policy::is_policy_v<tsl::policy::neutral_as_neutral>);
static_assert(tsl::policy::is_policy_v<tsl::policy::zero_as_unknown>);

int main() { return 0; }
