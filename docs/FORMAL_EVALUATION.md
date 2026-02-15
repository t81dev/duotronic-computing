# Formal Evaluation Framework: Duotronic / TLU Semantics

This document defines the formal, falsifiable evaluation criteria for the Ternary Logic Unit (TLU) and Duotronic semantics. It serves to transform qualitative architectural claims into rigorous, measurable hypotheses.

**Status:** Normative for evaluation.
**Scope:** TLU intrinsics and semantic kernels (TMIN, TMAX, TMAJ, TMUX, TNET).

---

## 1. Testable Hypotheses

We posit that under specific semantic workloads, TLU kernels reduce structural overhead compared to optimized binary baselines.

### Hypothesis H1: Reduction of Branch Density in Bounded Selection
**H1:** Under **workload W_BOUNDED** (selection from bounded intervals),
TLU semantic kernels **K_MIN / K_MAX**
reduce **Branch Density (D_branch)**
compared to **Binary Baseline B_COND** (conditional branches).

### Hypothesis H2: Reduction of Cyclomatic Complexity in Consensus Logic
**H2:** Under **workload W_VOTING** (majority consensus resolution),
TLU semantic kernel **K_MAJ**
reduces **Cyclomatic Complexity (M_cyclo)**
compared to **Binary Baseline B_MAJ** (sorting network or nested conditionals).

### Hypothesis H3: Reduction of Semantic Indirection in State Multiplexing
**H3:** Under **workload W_STATE** (three-way state transition logic),
TLU semantic kernel **K_MUX**
reduces **Instruction Count (I_count)**
compared to **Binary Baseline B_NEST** (nested ternary operators or switch statements).

### Hypothesis H4: Reduction of Accumulation Overhead in Sparse/Signed Sums
**H4:** Under **workload W_ACCUM** (summation of signed trits),
TLU semantic kernel **K_NET**
reduces **Control-Flow Depth (D_flow)**
compared to **Binary Baseline B_LOOP** (loop with conditional increment/decrement).

---

## 2. Formal Semantic Definitions

All inputs and outputs are normalized to the set **T = {-1, 0, +1}**.
Let `norm(x)` be the function that maps `x < 0` to `-1`, `x > 0` to `+1`, and `x == 0` to `0`.

### 2.1 TMIN (Ternary Minimum)
**Definition:** `TMIN(a, b) = min(norm(a), norm(b))`

| a | b | TMIN(a, b) |
|---|---|---|
| -1 | -1 | -1 |
| -1 |  0 | -1 |
| -1 | +1 | -1 |
|  0 | -1 | -1 |
|  0 |  0 |  0 |
|  0 | +1 |  0 |
| +1 | -1 | -1 |
| +1 |  0 |  0 |
| +1 | +1 | +1 |

**Properties:**
- Commutative: `TMIN(a, b) = TMIN(b, a)`
- Associative: `TMIN(a, TMIN(b, c)) = TMIN(TMIN(a, b), c)`
- Identity: `TMIN(a, +1) = norm(a)`
- Idempotence: `TMIN(a, a) = norm(a)`

### 2.2 TMAX (Ternary Maximum)
**Definition:** `TMAX(a, b) = max(norm(a), norm(b))`

| a | b | TMAX(a, b) |
|---|---|---|
| -1 | -1 | -1 |
| -1 |  0 |  0 |
| -1 | +1 | +1 |
|  0 | -1 |  0 |
|  0 |  0 |  0 |
|  0 | +1 | +1 |
| +1 | -1 | +1 |
| +1 |  0 | +1 |
| +1 | +1 | +1 |

**Properties:**
- Commutative: `TMAX(a, b) = TMAX(b, a)`
- Associative: `TMAX(a, TMAX(b, c)) = TMAX(TMAX(a, b), c)`
- Identity: `TMAX(a, -1) = norm(a)`
- Idempotence: `TMAX(a, a) = norm(a)`

### 2.3 TMAJ (Ternary Majority / Median)
**Definition:** `TMAJ(a, b, c) = median(norm(a), norm(b), norm(c))`
Equivalent to the value that appears at least twice, or the middle value if all distinct (which in ternary {-1, 0, +1} implies one of each, so median is 0).

**Propagation:**
- If any two inputs are equal, the result is that value.
- If inputs are distinct permutation of {-1, 0, +1}, result is 0.

**Properties:**
- Symmetric under permutation of arguments.
- `TMAJ(a, a, b) = norm(a)`

### 2.4 TMUX (Ternary Multiplexer)
**Definition:** `TMUX(c, A, B, C)` selects based on `norm(c)`:
- If `norm(c) == -1`, return `norm(A)`
- If `norm(c) ==  0`, return `norm(B)`
- If `norm(c) == +1`, return `norm(C)`

**Truth Table (partial for selection):**
| c | TMUX(c, A, B, C) |
|---|---|
| -1 | norm(A) |
|  0 | norm(B) |
| +1 | norm(C) |

**Ambiguity:**
- Behavior is undefined if `c` is not convertible to Trit (though normalization handles this).
- No "fallthrough"; selection is exclusive.

### 2.5 TNET (Ternary Network Sum)
**Definition:** `TNET(x, n) = sum(norm(x[i]))` for `i` in `0..n-1`.
Returns a standard integer (tlu_i32_t).

**Properties:**
- Order-independent (commutative/associative addition).
- Saturation is **NOT** applied in the current ABI definition (returns `int32_t`).

---

## 3. Structural Metrics

To evaluate H1-H4, we define the following measurement criteria.

### 3.1 Branch Density (D_branch)
**Definition:** The ratio of conditional branch instructions to total instructions in the compiled kernel.
`D_branch = (Count_conditional_branches) / (Count_total_instructions)`
*Lower is better.*

### 3.2 Cyclomatic Complexity (M_cyclo)
**Definition:** The number of linearly independent paths through the kernel's control flow graph.
`M = E - N + 2P`
Where E = edges, N = nodes, P = connected components (usually 1).
*Lower is better.*

### 3.3 Instruction Count (I_count)
**Definition:** The total number of instructions in the generated machine code for a reference architecture (x86-64 or ARM64).
*Lower is better, assuming constant CPI (Cycles Per Instruction).*

### 3.4 Control-Flow Depth (D_flow)
**Definition:** The maximum nesting level of control structures (loops, if/else blocks).
*Lower is better.*

### 3.5 Representation Overhead (O_rep)
**Definition:** Bits required to store N semantic elements.
- Binary: 2 bits per element (to represent 3 states: 00, 01, 10/11) or 8 bits (byte-aligned).
- Ternary Packed: log2(3) approx 1.58 bits.
*Lower is better.*

---

## 4. Binary Baseline Specifications

Evaluation requires comparison against "fair and optimized" binary implementations.

### 4.1 Baseline for TMIN/TMAX (B_COND)
Standard C implementation using `<algorithm>` or ternary operator.
```c
int min_val = (a < b) ? a : b;
```
*Note:* Modern compilers may optimize this to `cmov`. Evaluation must explicitly distinguish between `cmov` (data flow) and branching (control flow).

### 4.2 Baseline for TMAJ (B_MAJ)
A sorting network or series of comparisons.
```c
// Median of 3
if (a > b) swap(a, b);
if (b > c) swap(b, c);
if (a > b) swap(a, b);
return b;
```
Or boolean formulation if mapped to bits.

### 4.3 Baseline for TMUX (B_NEST)
Nested conditional checks.
```c
if (c < 0) return A;
else if (c > 0) return C;
else return B;
```

### 4.4 Baseline for TNET (B_LOOP)
Standard accumulation loop.
```c
int sum = 0;
for (int i=0; i<n; ++i) {
    if (x[i] == POS_TAG) sum++;
    else if (x[i] == NEG_TAG) sum--;
}
```

---

## 5. Negative Result Scenarios

The Duotronic hypothesis is **falsified** if:

1. **Complexity Increase:** TLU kernels result in higher `I_count` or `M_cyclo` than the binary baseline (e.g., due to expensive normalization).
2. **Ambiguity:** The "neutral" state (0) in TLU is consistently conflated with "error" or "missing" in actual usage, leading to logic bugs.
3. **No Structural Gain:** `D_branch` remains identical because the compiler effectively optimizes the binary baseline to branchless code (e.g., using `cmov` or SIMD), rendering TLU semantics redundant.
4. **Performance Regression:** The overhead of `tlu_norm_trit` dominates the execution time, making TLU strictly slower.

---

## 6. Threats to Validity

### 6.1 Compiler Optimization Bias
Modern compilers (GCC/Clang) are aggressive. They may auto-vectorize binary baselines or convert branches to `cmov`, narrowing the gap.
*Mitigation:* Analyze assembly output (`-S`) directly; disable specific optimizations if testing semantic structure rather than raw speed.

### 6.2 Workload Selection Bias
Choosing workloads that exclusively favor symmetric ternary logic (e.g., balanced ternary arithmetic) creates a tautology.
*Mitigation:* Include "hostile" workloads where binary signals are dominant and ternary is forced.

### 6.3 Measurement Noise
Instruction count does not equal latency. Branch prediction can hide the cost of branches.
*Mitigation:* Use `perf` counters for branch mispredictions; focus on code size and structure (static analysis) as primary proxies for "complexity".

---

## 7. Conclusion

This framework defines the "rules of engagement" for Duotronic evaluation. Future work must strictly report metrics defined here. If TLU fails to outperform baselines on these metrics, the project should be considered a negative result: a useful exploration of why binary remains dominant.
