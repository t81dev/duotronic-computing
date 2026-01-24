# Duotronic Computing — Working Outline

This outline describes the conceptual arc of the essays in this repository.
It is descriptive, not aspirational.

The goal of the collection is to explore whether duotronic computing
(the cooperative use of binary and ternary systems) has a narrowly defined,
defensible role — and to clearly identify where it does not.

---

## 1. Why Binary Won

An examination of the physical, architectural, and ecosystem reasons binary
computing became dominant.

Binary is treated as a success case:
- reliable signaling
- deterministic control
- exact addressing
- scalable tooling and verification

This section establishes binary computing as the correct substrate for
modern systems, not a limitation to be overcome.

---

## 2. When Binary Struggles

Identification of specific semantic patterns where binary representations
introduce structural overhead:

- unknown or indeterminate values
- neutrality and non-bias
- symmetric positive/negative signals
- majority and consensus logic

The focus is on *semantic indirection*, not computational inadequacy.

---

## 3. Ternary as Semantics (Not Substrate)

Introduction of ternary logic strictly as a semantic tool:

- three-valued meaning (negative / neutral / positive)
- direct representation of neutrality and uncertainty
- balanced arithmetic and symmetric reduction

This section explicitly rejects ternary as a storage format, control plane,
or replacement for binary systems.

---

## 4. Duotronic, Not Replacement

Definition of the duotronic model:

- binary remains the control substrate
- ternary is optional, bounded, and subordinate
- coprocessor-style integration as the only viable path

Replacement is rejected as both impractical and unnecessary.

---

## 5. Failure Modes

Explicit enumeration of where ternary semantics fail or should not be applied:

- domains requiring exact invariants
- accidental ambiguity masking real errors
- control-flow contamination
- performance costs without semantic payoff

Failure is treated as a boundary, not a defect.

---

## 6. Open Questions and Falsification Criteria

Identification of unresolved questions and conditions under which the
duotronic approach should be abandoned:

- unclear dominance of semantic overhead in practice
- measurement challenges and bias
- tooling and debugging implications
- software costs versus hardware justification
- containment and interoperability risks

Proceeding further requires evidence.
Stopping is a valid and expected outcome.

---

## Status

This outline reflects a complete exploratory arc.
It does not imply future work, adoption, or advocacy.
