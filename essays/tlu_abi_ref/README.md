# tlu_abi_ref

Correctness-first reference implementation of the TLU ABI defined in `TLU_ABI.md`.

- No SIMD
- No platform-specific behavior
- Normalizes trits at the ABI boundary
- Intended to be boring and portable

Build:
```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build
