#include <cassert>
#include <array>
#include "tsl/serialize.hpp"

using tsl::trit;

int main() {
  // Exact mapping
  assert(tsl::encode(trit::neg) == 0xFF);
  assert(tsl::encode(trit::zer) == 0x00);
  assert(tsl::encode(trit::pos) == 0x01);

  // Roundtrip
  constexpr std::array<trit,3> V{trit::neg, trit::zer, trit::pos};
  for (auto t : V) {
    auto b = tsl::encode(t);
    auto d = tsl::decode(b);
    assert(d.has_value());
    assert(*d == t);
  }

  // Invalid bytes reject
  for (unsigned x : {0x02u, 0x7Fu, 0x80u, 0xFEu}) {
    auto d = tsl::decode(static_cast<std::uint8_t>(x));
    assert(!d.has_value());
  }

  return 0;
}
