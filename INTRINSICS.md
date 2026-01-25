
# TLU Intrinsics Interface

This document describes the **compiler-facing intrinsic interface** for the
Ternary Logic Unit (TLU).

The intrinsic interface provides a **portable, stable call surface** that
programs may use to invoke TLU semantics without depending on hardware support
or compiler extensions.

This document is **non-normative** with respect to semantics.

---

## 1. Purpose

The purpose of the TLU intrinsic interface is to:

- make TLU semantics usable from C and C++ programs
- decouple source-level usage from ABI and hardware details
- allow compilers to recognize and optimize TLU operations
- preserve correct software fallback behavior

Intrinsics exist to improve *usability and reach*, not to define meaning.

---

## 2. Authority and Precedence

The following documents define authority, in descending order:

1. `TLU_WHITEPAPER.md` — semantic scope and evaluation criteria  
2. `appendix.md` — **normative** formal semantics  
3. `TLU_ABI.md` — calling conventions and binary interface  
4. `INTRINSICS.md` — source-level convenience only  

In the event of conflict, **this document has no authority** to alter
semantics or ABI behavior.

---

## 3. What Intrinsics Are

TLU intrinsics are:

- thin, inline wrappers
- ABI-lowering by default
- semantically transparent
- safe to call on any platform

They are intended to look like ordinary function calls and may be optimized
by compilers when appropriate.

---

## 4. What Intrinsics Are Not

TLU intrinsics are **not**:

- a new programming language
- a requirement for hardware support
- an instruction-set specification
- a performance guarantee
- a semantic definition

Programs using intrinsics must remain correct when all calls lower to
software ABI implementations.

---

## 5. Default Lowering Behavior

By default, all TLU intrinsics lower directly to the ABI functions defined in:

```

tlu_abi.h

````

This ensures:

- a single semantic authority
- consistent normalization behavior
- identical observable results across platforms

No intrinsic is permitted to bypass ABI semantics.

---

## 6. Optional Compiler Builtins

The intrinsic interface is designed to allow **optional compiler-specific
builtins** in the future.

Such builtins may:

- map intrinsics to vector instructions
- fuse operations
- lower to hardware accelerators

Builtins must:

- preserve exact semantic behavior
- be observationally equivalent to ABI calls
- remain interchangeable with software fallback

Programs must not rely on the presence of builtins for correctness.

---

## 7. Configuration Macros

The intrinsic header defines the following configuration macros:

- `TLU_USE_BUILTINS`  
  Enables compiler-specific builtins when available.

- `TLU_FORCE_ABI`  
  Forces all intrinsics to lower to ABI calls, even if builtins exist.

- `TLU_SHORT_NAMES`  
  Enables short macro aliases (e.g. `TMIN`, `TMAJ`) for convenience.

These macros affect **lowering behavior only**, not semantics.

---

## 8. Language Support

The intrinsic interface is defined for:

- C (C11 or later)
- C++ (C++17 or later)

The interface uses `extern "C"` where appropriate to ensure ABI compatibility.

Bindings for other languages, if provided, must lower to the same ABI surface.

---

## 9. Correctness Expectations

All intrinsic calls must:

- normalize inputs according to ABI rules
- produce results consistent with `appendix.md`
- behave identically in scalar and vectorized contexts

If an intrinsic produces a different result than the ABI reference,
the intrinsic implementation is incorrect.

---

## 10. Relationship to Conformance

Use of intrinsics does **not** by itself imply TLU conformance.

An implementation claiming TLU conformance must still:

- implement required operations
- pass reference tests
- match the executable semantic oracle

Intrinsics are a convenience layer, not a conformance mechanism.

---

## 11. Intended Usage Pattern

A typical usage pattern is:

```c
#include "tlu_intrinsics.h"

tlu_trit_t r = tlu_intrin_tmaj(a, b, c);
````

or, with short names enabled:

```c
#define TLU_SHORT_NAMES 1
#include "tlu_intrinsics.h"

tlu_trit_t r = TMAJ(a, b, c);
```

In all cases, observable behavior must match the reference semantics.

---

## 12. Stability Commitment

The intrinsic interface is intended to be **source-stable**.

Future changes may:

* add new intrinsics
* add new optional configuration macros

Future changes must not:

* change the meaning of existing intrinsics
* alter normalization behavior
* introduce mandatory hardware dependencies

---

## 13. Summary

The TLU intrinsic interface exists to:

* make ternary semantics accessible
* preserve semantic authority
* enable optimization without obligation

It is a bridge between **semantic definition** and **practical use**.

Semantics live elsewhere.

