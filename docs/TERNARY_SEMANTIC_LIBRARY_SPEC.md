## Ternary Semantic Library Specification (TSL) v0.1

### 0. Purpose

Define a minimal, implementation-agnostic semantic library for **ternary values** in a binary language (C++ or Rust) to evaluate whether explicit neutrality/uncertainty reduces semantic indirection in practice.

This library is a **measurement instrument**:

* It must be easy to remove.
* It must interoperate with binary code.
* It must not imply hardware, protocols, or ecosystem direction.

### 1. Scope

**In-scope**

* A tri-state scalar type (`Trit`) representing **{-1, 0, +1}**.
* A small set of operations with **explicit, testable** propagation rules.
* “Policy” mechanisms to model alternative semantics without rewriting callers.
* Deterministic conversion boundaries to/from binary types.
* A reference test suite with truth tables and property tests.
* Microbench harnesses to measure semantic overhead.

**Out-of-scope**

* Ternary control flow (no `if (Trit)` semantics beyond explicit conversions).
* Memory addressing, pointer arithmetic, cryptography, filesystem metadata.
* Claims of performance advantage.
* New number systems, floating formats, or ternary storage protocols.
* Network/protocol changes.

### 2. Terminology

* **Neutral**: the middle value `0`, not “false” and not “missing” by default.
* **Uncertain**: a semantic interpretation that may be represented by `0` under a specific policy, but must not be conflated silently with neutral unless chosen explicitly.
* **Policy**: a compile-time or runtime selection of propagation rules.

### 3. Type Model

#### 3.1 Core Type

**C++**

```cpp
enum class trit : int8_t { neg = -1, zer = 0, pos = 1 };
```

**Rust**

```rust
#[repr(i8)]
pub enum Trit { Neg = -1, Zer = 0, Pos = 1 }
```

Constraints:

* `sizeof(Trit)` is 1 byte (target; allow larger if ABI forces it).
* Total ordering is defined (`neg < zer < pos`) but must not be used to imply probability.

#### 3.2 Optional Tagged Variant (to avoid semantic overload)

To prevent “neutral means everything” drift, provide an *optional* tagged form:

* `Trit` remains the bare value set.
* `Tri` adds meaning tags:

  * `Neutral` (intended neutral)
  * `Unknown` (indeterminate)
  * `Masked` (excluded from reductions)
  * `Value(Trit)` (neg/zer/pos)

This is optional but recommended for serious experiments because it tests Essay 05’s failure mode: *overloading meaning*.

### 4. Operations and Semantics

#### 4.1 Arithmetic-like (balanced)

* `negate(t)` : flips sign, preserves zero
* `add(a,b)` : balanced addition with saturation policy
* `sub(a,b)` : defined as `add(a, negate(b))`

Default arithmetic policy:

* **Saturating** on overflow of the set {-1,0,+1}:

  * `pos + pos = pos`
  * `neg + neg = neg`
  * `pos + neg = zer`
  * `pos + zer = pos`, etc.

Rationale: keep semantics local and predictable; avoid expanding into multi-trit numerics.

#### 4.2 Lattice-like (logic)

Define two primitives that behave like tri-state “and/or” but remain semantic, not boolean:

* `meet(a,b)` (“conjunction-like”): returns the more conservative / lower element
* `join(a,b)` (“disjunction-like”): returns the more permissive / higher element

With ordering `neg < zer < pos`:

* `meet = min`
* `join = max`

These are useful for aggregation, not truth.

#### 4.3 Comparisons

Comparisons must not create ternary control flow implicitly.

Provide:

* `cmp(a,b) -> Trit` where:

  * `neg` means a < b
  * `zer` means a == b OR indeterminate depending on policy
  * `pos` means a > b

If `Tri` tagged form is used, `Unknown` must map to indeterminate.

#### 4.4 Reductions

Provide explicit reduction operators:

* `majority(trits...) -> Trit`
* `median(trits...) -> Trit`
* `sum_sat(trits...) -> Trit`
* `count_pos/neg/zer`

Rules:

* `majority` must define tie behavior explicitly:

  * default: ties return `zer` (neutral)
  * alternative: ties return `Unknown` if using tagged variant

### 5. Propagation Policies

Policies exist to test whether semantics help or harm. A policy is a named bundle of truth tables.

Required policies:

1. **Neutral-as-neutral (NAN)**
   `zer` means neutral; it participates but does not assert uncertainty.

2. **Zero-as-unknown (ZAU)**
   `zer` is treated as indeterminate in comparisons and selection; reductions may preserve unknown.

3. **Masked-neutral (MN)**
   `zer` is neutral for arithmetic but masked in certain reductions (configurable).

Implementation requirement:

* Policy must be selectable without changing call sites:

  * C++: template parameter or strategy object
  * Rust: trait + generic type parameter

### 6. Interoperability Boundaries

#### 6.1 Conversions (explicit only)

* `from_sign(i)` converts:

  * negative → `neg`
  * zero → `zer`
  * positive → `pos`
* `to_int(t)` converts:

  * `neg` → -1
  * `zer` → 0
  * `pos` → 1

No implicit bool conversion.

#### 6.2 Serialization

For now: only a stable byte encoding:

* `0xFF` = neg (-1)
* `0x00` = zer (0)
* `0x01` = pos (+1)

If `Tri` tagged variant exists, tags must be encoded separately; do not silently map to 0.

### 7. Safety and Containment Requirements

* Must be “opt-in”: no global operator overloads that change program meaning.
* Must be localizable: can be removed by replacing `Trit` with `int8_t` and using helper funcs.
* Must not affect control flow unless explicitly converted by the caller.

### 8. Testing Requirements

#### 8.1 Truth-table tests

Every operator must ship with a 3x3 truth table test (or higher for reductions).

#### 8.2 Property tests

Required properties:

* `negate(negate(t)) == t`
* `meet/join` commutativity and associativity
* `meet(a, join(a,b)) == a` and dual (lattice absorption)
* `majority` permutation invariance

#### 8.3 Negative tests

Ensure:

* no implicit `bool` conversion
* policy boundaries are enforced
* tagged `Unknown` is not silently collapsed

### 9. Benchmark Requirements (Software-first validation)

Provide microbenchmarks:

* throughput for map/reduce over arrays of Trit
* overhead of policy dispatch
* comparison vs baseline binary conventions (flags/sentinels)

Provide macrobench “toy workloads” that mirror Essay 02:

* masked reductions
* majority voting
* neutral propagation through pipelines

### 10. Acceptance Criteria (falsifiable)

The library is “useful” only if experiments show at least one:

* reduced code size or fewer conditionals in neutral/unknown-heavy pipelines
* fewer state bugs (missed flag checks) in small case studies
* comparable performance to conventional patterns in targeted domains

The library is “not useful” if:

* it increases semantic confusion (overload)
* callers immediately reintroduce flags/sentinels
* performance overhead dominates without clarity gains
* containment boundaries fail (it spreads into control logic)

---

