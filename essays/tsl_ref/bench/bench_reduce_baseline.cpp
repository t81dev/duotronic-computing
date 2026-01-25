#include <chrono>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <vector>

struct vote_bin {
  int value;
  bool valid;
  bool neutral;
};

static int pseudo_value(std::uint32_t x) {
  switch (x % 3u) {
    case 0u: return -1;
    case 1u: return 0;
    default: return +1;
  }
}

static bool pseudo_bool(std::uint32_t x, unsigned bit) {
  return ((x >> bit) & 1u) != 0u;
}

int main(int argc, char** argv) {
  const std::size_t N = (argc > 1) ? static_cast<std::size_t>(std::stoull(argv[1])) : 10'000'000;
  const int iters = (argc > 2) ? std::stoi(argv[2]) : 10;

  std::vector<vote_bin> xs;
  xs.reserve(N);

  std::uint32_t seed = 0x12345678u;
  for (std::size_t i = 0; i < N; ++i) {
    seed = seed * 1664525u + 1013904223u;

    vote_bin v{};
    v.value = pseudo_value(seed);
    v.valid = pseudo_bool(seed, 0);
    v.neutral = pseudo_bool(seed, 1);
    xs.push_back(v);
  }

  int acc_sum = 0;
  int acc_maj = 0;

  auto t0 = std::chrono::steady_clock::now();
  for (int k = 0; k < iters; ++k) {
    std::size_t pos = 0, neg = 0;
    for (auto &v : xs) {
      if (!v.valid) continue;
      if (v.neutral) continue;
      if (v.value > 0) ++pos;
      else if (v.value < 0) ++neg;
    }
    acc_maj = (pos > neg) ? +1 : (neg > pos) ? -1 : 0;

    int s = 0;
    for (auto &v : xs) {
      if (!v.valid) continue;
      if (v.neutral) continue;
      s += v.value;
    }
    if (s > 1) s = 1;
    if (s < -1) s = -1;
    acc_sum = s;
  }
  auto t1 = std::chrono::steady_clock::now();

  const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count();

  std::cout << "N=" << N << " iters=" << iters
            << " elapsed_ms=" << ms
            << " sum=" << acc_sum
            << " maj=" << acc_maj
            << "\n";

  return 0;
}
