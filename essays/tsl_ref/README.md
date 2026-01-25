# Ternary Semantic Library (TSL) — Reference Implementation

This directory contains a **software-only reference implementation** of a
minimal ternary semantic library written in C++.

It exists solely to support the *software-first validation* discussed in
Essay 06 (Open Questions).

This code:
- is not normative
- is not a proposal
- is not a performance claim
- is not an adoption pathway

It is a **measurement instrument** intended to test whether explicit ternary
semantics reduce semantic indirection in narrowly defined cases.

Removal of this directory constitutes complete removal of the experiment.

Binary control semantics remain authoritative at all times.

## What this is (and is not)

TSL is a **software-only probe** for evaluating whether explicit ternary semantics
reduce semantic indirection in narrowly defined situations.

It is not:
- a proposal for language changes
- a protocol design
- a performance claim
- a roadmap toward ternary architectures

Binary control semantics remain authoritative. Ternary values here are **data**, not control.

## Current surface area (v0.1)

Headers:
- `tsl/trit.hpp` — core trit type (`neg/zer/pos`)
- `tsl/policy.hpp` — policy scaffolding (compile-time)
- `tsl/ops.hpp` — `negate`, `meet`, `join`, `add_sat`
- `tsl/reduce.hpp` — `count`, `majority`, `sum_sat`
- `tsl/serialize.hpp` — stable byte encoding + decode
- `tsl/cmp.hpp` — policy-aware comparison + explicit indeterminate helper

## Validation case: toy pipeline

`tests/test_toy_pipeline.cpp` implements the same small aggregation task in two ways:

1) **Baseline binary conventions** using:
   - `int` values
   - explicit `valid` and `neutral` flags
   - filtering logic at each operation

2) **TSL style** using:
   - `tsl::trit` values
   - neutrality as `trit::zer`
   - invalid entries handled at the boundary (omitted from the input range)
   - reductions (`majority`, `sum_sat`) defined directly over trits

This test is not evidence of superiority. It exists to make *semantic overhead*
visible and measurable.

### Masking semantics note

`masked_neutral` intentionally conflates `zer` with “masked” during policy-aware reductions.
This is not presented as a best practice. It exists to stress the failure mode where a single
ternary value is asked to represent multiple meanings. Tagged-type alternatives would be the next
step if this ambiguity proves too costly.

## Build and run

From the repository root:

```bash
cmake -S essays/tsl_ref -B essays/tsl_ref/build
cmake --build essays/tsl_ref/build
ctest --test-dir essays/tsl_ref/build -V
```

## Microbenchmarks (optional)

Two small microbench executables are provided to measure *software overhead*.

- `bench_reduce` — uses `tsl::trit` + `sum_sat` + `majority`
- `bench_reduce_baseline` — uses a conventional binary representation:
  `int value` plus `valid` and `neutral` flags, with filtering logic

These benches do **not** demonstrate superiority. They exist to:
- quantify overhead introduced by explicit semantics
- expose branch/mask costs in conventional representations
- provide a reproducible comparison point for future experiments

### Run

From the repository root:

```bash
cmake -S essays/tsl_ref -B essays/tsl_ref/build
cmake --build essays/tsl_ref/build

./essays/tsl_ref/build/bench_reduce 1000000 20
./essays/tsl_ref/build/bench_reduce_baseline 1000000 20
```

### Interpretation constraints

* Treat single-run timings as noise.
* Compare only on the same machine, same compiler, same build type.
* Do not generalize results to other domains.
* A “faster” result is not evidence of semantic benefit.
* A “slower” result is not evidence that the model is wrong.
  The purpose is to measure cost so the boundary can be drawn honestly.

## Removal

Deleting `essays/tsl_ref/` removes the experiment completely.
