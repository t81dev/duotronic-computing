#pragma once
#include <type_traits>

namespace tsl::policy {

// Policy concept (v0.1):
// - comparison can treat "zer" as either equality or indeterminate (epistemic).
// - no effect on arithmetic yet (kept out-of-scope until ops land).
struct neutral_as_neutral {
  static constexpr bool zero_means_unknown_in_cmp = false;
  static constexpr bool zero_is_masked_in_reductions = false;
};

struct zero_as_unknown {
  static constexpr bool zero_means_unknown_in_cmp = true;
  static constexpr bool zero_is_masked_in_reductions = false;
};

struct masked_neutral {
  static constexpr bool zero_means_unknown_in_cmp = false;
  static constexpr bool zero_is_masked_in_reductions = true;
};

// Concept check helper (optional, keeps errors readable).
template <class P>
inline constexpr bool is_policy_v =
  std::is_same_v<decltype(P::zero_means_unknown_in_cmp), const bool> &&
  std::is_same_v<decltype(P::zero_is_masked_in_reductions), const bool>;

} // namespace tsl::policy
