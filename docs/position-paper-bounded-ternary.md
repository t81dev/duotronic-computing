# Bounded Ternary Computing

## A Cross-Layer Evaluation of Explicit Three-Valued Semantics in Binary Control Planes

**Author:** t81dev
**Affiliation:** Independent Research
**Date:** 2024-10-26

---

## Abstract

Binary computing dominates modern systems due to its physical simplicity, deterministic behavior, and mature ecosystem. However, real-world workloads frequently require representation of neutrality, indeterminacy, or symmetric signal states that binary systems encode indirectly using sentinel values, flags, or control-flow conventions. These patterns introduce structural overhead and semantic indirection.

This paper presents a cross-layer evaluation of *bounded ternary computing*: the disciplined introduction of explicit three-valued semantics (`−1, 0, +1`) within strictly binary control planes. We define a minimal ternary semantic kernel, evaluate structural complexity relative to optimized binary baselines, implement deterministic runtime enforcement, conduct ternary quantization experiments, and explore transistor-level feasibility through SPICE simulation.

Our findings indicate that ternary semantics reduce structural complexity in neutrality-dominant workloads but do not provide universal performance improvements. Hardware realization remains comparator-limited. We conclude that ternary computing is viable as a bounded semantic augmentation rather than a universal computational substrate.

---

# 1. Introduction

Binary logic is the universal substrate of modern computing. It excels at:

* Deterministic control flow
* Addressing and memory layout
* Exact invariants
* Ecosystem interoperability

Yet many computational domains naturally exhibit three semantic states:

* Allow / Abstain / Deny
* Positive / Neutral / Negative
* Present / Unknown / Absent
* High / High-Z / Low

Binary systems represent these using indirect conventions:

* Sentinel integers (e.g., `-1`, `INT_MIN`)
* Floating-point `NaN`
* Validity flags
* Nested conditionals
* Branch-heavy state machines

These techniques introduce semantic indirection and structural complexity. The fundamental question motivating this research is:

> Can explicit ternary semantics reduce structural complexity without compromising binary determinism?

We investigate this question across software, runtime systems, quantized inference, and transistor-level modeling.

---

# 2. Background and Prior Work

## 2.1 Multi-Valued Logic

Multi-valued logic (MVL) has a long history in hardware research, including the SETUN ternary computer (1958). Prior efforts often sought density or transistor-count reduction benefits. However, MVL adoption was limited by fabrication complexity and binary ecosystem dominance.

Our work differs by:

* Emphasizing semantic clarity rather than density.
* Constraining ternary logic within binary control planes.
* Treating ternary as optional and bounded.

## 2.2 Option Types and Neutral Propagation

Modern languages provide type-level constructs (e.g., `Option<T>`, `std::optional`) for missing values. These constructs operate at high abstraction layers. However, low-level arithmetic and control logic frequently reintroduce sentinel encodings.

We explore whether explicit ternary arithmetic kernels offer a lower-level structural alternative.

## 2.3 Quantized Neural Networks

Ternary weight quantization has been explored for model compression. Most work focuses on memory footprint and MAC reduction. We extend this inquiry by evaluating cross-layer structural implications rather than accuracy alone.

---

# 3. The Bounded Ternary Thesis

We do not propose replacing binary computing.

Instead, we propose a strict separation:

| Plane   | Responsibility                                 |
| ------- | ---------------------------------------------- |
| Binary  | Control, sequencing, addressing                |
| Ternary | Semantic arithmetic and neutrality propagation |

We define the containment invariant:

> Ternary values must never directly influence instruction sequencing.
> Any ternary-to-binary transition must be explicit and normalized.

This preserves:

* Deterministic execution
* Compiler compatibility
* ABI stability
* Formal reasoning boundaries

Ternary semantics operate only in data domains where neutrality or symmetry is intrinsic.

---

# 4. Formal Model

We define the ternary domain:

[
T = {-1, 0, +1}
]

with lattice ordering:

[
-1 < 0 < +1
]

All inputs are normalized to this domain via `norm(x)`.

## 4.1 TMIN / TMAX

[
TMIN(a,b) = min(norm(a), norm(b))
]

[
TMAX(a,b) = max(norm(a), norm(b))
]

These implement lattice operations with explicit neutrality.

## 4.2 TMAJ

[
TMAJ(a,b,c) = median(norm(a), norm(b), norm(c))
]

Implements symmetric consensus.

## 4.3 TMUX

Three-way selection:

* `-1 → A`
* `0 → B`
* `+1 → C`

Removes nested conditional cascades.

## 4.4 TNET

[
TNET(x) = \sum_i norm(x_i)
]

Implements symmetric accumulation.

---

# 5. Methodology

We evaluate ternary computing across four layers.

---

## 5.1 Structural Complexity Analysis

We compare ternary kernels against optimized binary baselines using:

* **Branch Density**
* **Cyclomatic Complexity**
* **Instruction Count**

Workloads:

* Majority voting
* Three-way state machines
* Signed accumulation
* Clamping logic

Binary baselines include nested conditionals and sorting networks.

---

## 5.2 Deterministic Runtime Enforcement

We implemented ternary operations inside a deterministic VM with:

* Explicit normalization boundaries
* Execution tracing
* Policy gating
* Reproducible replay

This allowed investigation of governance and determinism interactions.

---

## 5.3 Quantized Inference Experiments

Ternary quantization was applied to:

* Sparse inference models
* Zero-skip optimized loops

Metrics evaluated:

* Accuracy degradation
* MAC reduction
* Energy per inference

---

## 5.4 Hardware-Level Exploration

SPICE simulations evaluated:

* Encoder energy
* Differential sensing guard margins
* Monte Carlo mismatch resilience
* Comparator viability

Experiments included:

* ±10% VDD sweeps
* Noise injection (5–10 mV)
* Driver scaling (1.5×–2.5×)
* 50-seed Monte Carlo per corner

---

# 6. Results

---

## 6.1 Structural Complexity

In neutrality-dominant workloads:

* Cyclomatic complexity decreased significantly.
* Branch density decreased measurably.
* Control-flow graphs simplified.

However:

* Modern compilers often produce branchless code from binary equivalents.
* Instruction count reductions were workload-dependent.

Ternary semantics enforce neutrality propagation structurally rather than conventionally.

---

## 6.2 Runtime Determinism

The deterministic runtime revealed:

* Explicit boundaries improved traceability.
* Semantic propagation became auditable.
* Execution intent became enforceable.

Representation change alone was less impactful than boundary discipline.

---

## 6.3 Quantized Inference

Ternary weights proved viable for:

* Sparse models
* Zero-skippable architectures
* Energy-constrained environments

Accuracy trade-offs were bounded but model-dependent.

---

## 6.4 Hardware Experiments

### Guard Margins

Differential sensing headroom remained stable under:

* ±10% VDD
* Monte Carlo mismatch
* Noise stress

### Comparator Limitation

Despite stable guard margins:

* Comparator handoff under low-swing conditions failed stability criteria.
* Comparator did not consistently cross 0.5·VDD threshold.

This indicates physical realization challenges for balanced ternary memory.

---

# 7. Negative Results

Ternary computing does **not**:

* Replace binary control logic.
* Universally reduce instruction count.
* Guarantee performance improvement.
* Simplify physical memory realization.
* Eliminate normalization overhead.

Comparator complexity remains a physical bottleneck.

---

# 8. Discussion

---

## 8.1 Where Ternary Helps

* Consensus systems
* Signed signal domains
* Reliability layers
* Sparse inference

## 8.2 Where It Does Not

* Address arithmetic
* Control sequencing
* Bitwise operations
* Pointer logic

---

## 8.3 Cross-Layer Insight

The most durable outcome is boundary discipline:

* Explicit semantics reduce ambiguity.
* Determinism amplifies clarity.
* Physical constraints reshape theoretical claims.
* Universal replacement narratives collapse under cross-layer scrutiny.

Bounded claims survive.

---

# 9. Threats to Validity

* Structural metrics may not reflect cognitive clarity fully.
* Workloads were neutrality-centric.
* SPICE simulations do not guarantee fabrication viability.
* Quantized inference results are model-dependent.

---

# 10. Future Work

* Comparator topology redesign
* Hardware-assisted normalization
* Human-centered maintainability studies
* Formal proof integration
* Co-processor integration minimizing conversion overhead

---

# 11. Conclusion

Binary computing remains the optimal universal substrate.

Ternary computing is viable as a bounded semantic augmentation in neutrality-centric domains.

The primary contribution of this research is not a new substrate, but a clarified design boundary.

Explicit ternary semantics reduce structural complexity in specific domains while preserving binary determinism—when disciplined containment is enforced.

Ternary computing should be:

* Software-first
* Explicitly normalized
* Workload-validated
* Physically bounded
* Treated as optional

The value of ternary computing lies not in replacing binary logic, but in clarifying where binary logic was compensating for missing semantic structure.
