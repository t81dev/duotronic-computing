#include <array>
#include <cassert>
#include "tsl/ops.hpp"

using tsl::trit;

static constexpr std::array<trit, 3> V{trit::neg, trit::zer, trit::pos};

static void test_negate_table() {
  assert(tsl::negate(trit::neg) == trit::pos);
  assert(tsl::negate(trit::zer) == trit::zer);
  assert(tsl::negate(trit::pos) == trit::neg);
}

static void test_meet_table() {
  // meet = min over neg < zer < pos
  const trit E[3][3] = {
    {trit::neg, trit::neg, trit::neg},
    {trit::neg, trit::zer, trit::zer},
    {trit::neg, trit::zer, trit::pos},
  };

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      assert(tsl::meet(V[i], V[j]) == E[i][j]);
}

static void test_join_table() {
  // join = max over neg < zer < pos
  const trit E[3][3] = {
    {trit::neg, trit::zer, trit::pos},
    {trit::zer, trit::zer, trit::pos},
    {trit::pos, trit::pos, trit::pos},
  };

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      assert(tsl::join(V[i], V[j]) == E[i][j]);
}

static void test_lattice_identities() {
  // absorption: meet(a, join(a,b)) == a and join(a, meet(a,b)) == a
  for (auto a : V) for (auto b : V) {
    assert(tsl::meet(a, tsl::join(a, b)) == a);
    assert(tsl::join(a, tsl::meet(a, b)) == a);
  }
}

int main() {
  test_negate_table();
  test_meet_table();
  test_join_table();
  test_lattice_identities();
  return 0;
}
