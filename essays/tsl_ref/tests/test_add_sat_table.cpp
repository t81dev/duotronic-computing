#include <array>
#include <cassert>
#include "tsl/ops.hpp"

using tsl::trit;

int main() {
  constexpr std::array<trit, 3> V{trit::neg, trit::zer, trit::pos};

  // Expected add_sat table:
  //      b:  neg  zer  pos
  // a:
  // neg     neg  neg  zer
  // zer     neg  zer  pos
  // pos     zer  pos  pos
  const trit E[3][3] = {
    {trit::neg, trit::neg, trit::zer},
    {trit::neg, trit::zer, trit::pos},
    {trit::zer, trit::pos, trit::pos},
  };

  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      assert(tsl::add_sat(V[i], V[j]) == E[i][j]);

  return 0;
}
