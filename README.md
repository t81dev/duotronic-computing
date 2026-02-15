# Duotronic Computing

This repository contains **interpretive and contextual material** exploring
*duotronic computing*: the cooperative use of binary and ternary systems.

It is **not a specification**.

Formal semantics, conformance rules, and reference implementations for the
Ternary Logic Unit (TLU) live in the companion repository:

→ https://github.com/t81dev/duotronic-whitepaper

For an overview of how related repositories fit together, see:

→ `docs/ecosystem.md`

---

## Scope

This repository focuses on:

- motivation and conceptual framing  
- historical analogies (e.g., FPUs, SIMD, accelerators)  
- potential application domains  
- design intuition and trade-offs  
- negative space: where ternary semantics do *not* help  

No material here is normative or binding.

---

## Formal Evaluation

While primarily interpretive, this repository hosts the rigorous, falsifiable
evaluation framework used to validate or reject Duotronic claims.

→ `docs/FORMAL_EVALUATION.md` (Technical Criteria)
→ `docs/PAPER_OUTLINE.md` (Publication Structure)

These documents define:
- Testable hypotheses (H1-H4)
- Formal semantic definitions for TLU kernels
- Structural metrics (Branch Density, Cyclomatic Complexity)
- Binary baseline specifications
- Negative result scenarios

All future contributions must align with these criteria.

---

## Relationship to the TLU Specification

- This repository **depends on** the TLU specification.  
- It does not redefine semantics, operations, or correctness criteria.  
- Any disagreement between narrative material here and the specification
  must be resolved in favor of the specification.

---

## Status

This repository is exploratory by design.  
Content may evolve, be revised, or be abandoned without version guarantees.

---

## Findings (TSL reference, v0.1)

This repository includes a bounded, software-only probe (`essays/tsl_ref`) used to
evaluate whether explicit ternary semantics reduce semantic indirection under
constrained conditions.

The probe is intentionally minimal and **not intended for reuse as a
general-purpose library**.

### What was established

- **Method validity**  
  The hypothesis is testable with a software-first approach. Semantics can be
  specified, implemented, tested, and measured without hardware changes.

- **Measured cost**  
  Explicit ternary semantics incur a **real, measurable overhead** versus
  conventional binary representations with flags for the tested workloads.
  This cost is **bounded and predictable**, not catastrophic.

- **Containment holds**  
  Binary control semantics remain authoritative. Ternary values were kept as
  data only; no control-flow contamination or tooling failure occurred.

- **Failure modes are real**  
  Masking experiments show that **overloading meaning** (e.g., treating a
  single value as both neutral and masked) increases ambiguity. Domains that
  require this distinction need tagged states rather than additional policies.

### What was not established

- No performance advantage was demonstrated.  
- No general recommendation or adoption path is implied.  
- No hardware justification was found.  
- No claim is made beyond the tested scopes and workloads.

### Interpretation

The results support a **selective, correctness-oriented** view: if ternary
semantics are ever justified, it will be for **local clarity under specific
semantic load**, not for global speed, density, or replacement of binary systems.

### Status

The reference probe is **sealed at v0.1**.  
Further work would require a new, explicitly scoped investigation (e.g., tagged
state types) rather than incremental extension of this probe.
