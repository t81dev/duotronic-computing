#include <chrono>
#include <cstdint>
#include <iostream>
#include <vector>

#include "tsl/reduce.hpp"
#include "tsl/trit.hpp"

static tsl::trit pseudo_trit(std::uint32_t x) {
  switch (x % 3u) {
    case 0u: return tsl::trit::neg;
    case 1u: return tsl::trit::zer;
    default: return tsl::trit::pos;
  }
}

int main(int argc, char** argv) {
  const std::size_t N = (argc > 1) ? static_cast<std::size_t>(std::stoull(argv[1])) : 10'000'000;
  const int iters = (argc > 2) ? std::stoi(argv[2]) : 10;

  std::vector<tsl::trit> xs;
  xs.reserve(N);

  std::uint32_t seed = 0x12345678u;
  for (std::size_t i = 0; i < N; ++i) {
    seed = seed * 1664525u + 1013904223u;
    xs.push_back(pseudo_trit(seed));
  }

  tsl::trit acc_sum = tsl::trit::zer;
  tsl::trit acc_maj = tsl::trit::zer;

  auto t0 = std::chrono::steady_clock::now();
  for (int k = 0; k < iters; ++k) {
    acc_sum = tsl::sum_sat(xs.begin(), xs.end());
    acc_maj = tsl::majority(xs.begin(), xs.end());
  }
  auto t1 = std::chrono::steady_clock::now();

  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

  std::cout << "N=" << N << " iters=" << iters
            << " elapsed_ms=" << ms
            << " sum=" << tsl::to_int(acc_sum)
            << " maj=" << tsl::to_int(acc_maj)
            << "\n";

  return 0;
}
