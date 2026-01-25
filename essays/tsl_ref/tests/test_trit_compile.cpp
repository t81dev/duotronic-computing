#include <cstdint>
#include <type_traits>
#include "tsl/trit.hpp"

static_assert(sizeof(tsl::trit) == 1, "tsl::trit should be 1 byte");

static_assert(tsl::to_int(tsl::trit::neg) == -1);
static_assert(tsl::to_int(tsl::trit::zer) == 0);
static_assert(tsl::to_int(tsl::trit::pos) == 1);

static_assert(!std::is_convertible_v<tsl::trit, bool>,
              "tsl::trit must not be implicitly convertible to bool");

static_assert(std::is_enum_v<tsl::trit>, "tsl::trit must be an enum type");

static_assert(std::is_same_v<std::underlying_type_t<tsl::trit>, std::int8_t>,
              "tsl::trit underlying type must be int8_t");

static_assert(static_cast<std::int8_t>(tsl::trit::neg) == static_cast<std::int8_t>(-1));
static_assert(static_cast<std::int8_t>(tsl::trit::zer) == static_cast<std::int8_t>(0));
static_assert(static_cast<std::int8_t>(tsl::trit::pos) == static_cast<std::int8_t>(1));

int main() { return 0; }
