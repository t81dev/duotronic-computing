# Duotronic Computing — Ecosystem Map

This document describes how the repositories under  
https://github.com/t81dev relate to one another.

It is **descriptive**, not prescriptive.
Nothing in this document is normative.

---

## Overview

The duotronic ecosystem is intentionally modular. Each repository has a
clearly defined role, ranging from formal specification to narrative
exploration to experimental falsification.

The guiding principle is **separation of concerns**:
- specifications remain authoritative and frozen
- narrative material remains non-normative
- experiments are disposable by design

---

## 1. Core Specification and Semantics

These repositories define **authoritative semantics** and correctness rules.

### ● duotronic-whitepaper  
https://github.com/t81dev/duotronic-whitepaper

The normative specification of the **Ternary Logic Unit (TLU)**.

Contents include:
- formal semantic definitions
- truth tables and properties
- conformance criteria
- executable reference implementations

This repository is the **single source of truth** for TLU semantics.
All other repositories must defer to it on questions of correctness.

---

## 2. Interpretive and Narrative Context

These repositories explore *why* duotronic ideas exist and *where* they may
or may not apply. They do not define semantics.

### ● duotronic-computing  
https://github.com/t81dev/duotronic-computing

A non-normative companion to the TLU specification.

Focus areas:
- motivation and historical context
- architectural boundaries
- failure modes
- falsification criteria

This repository is intentionally conservative and closed-ended.
It depends conceptually on `duotronic-whitepaper` but does not modify it.

---

## 3. Experimental Falsification Probes

These repositories test duotronic and ternary ideas under real constraints.
Negative results are expected and acceptable.

### ● ternary-pager  
https://github.com/t81dev/ternary-pager

A user-space paging experiment exploring whether ternary semantic compression
can reduce memory traffic under read-heavy numeric workloads.

Purpose:
- measurement, not advocacy
- falsification before kernel or hardware changes

---

### ● ternary_gcc_plugin  
https://github.com/t81dev/ternary_gcc_plugin

A GCC plugin that introduces ternary helpers and lowering paths.

Purpose:
- validate software-first execution of ternary semantics
- explore compiler integration costs
- provide a bridge between semantics and real toolchains

---

## 4. Numeric Primitives and Tooling

These repositories provide **balanced ternary numerics** and supporting tools.
They may be used by experiments but do not define semantics independently.

### ● t81lib  
https://github.com/t81dev/t81lib

A modern C++ (and Python-bound) library implementing balanced ternary numeric
types and operations.

Purpose:
- reusable ternary arithmetic primitives
- vectorization and performance exploration
- support for experimental workloads

---

### ● t81-foundation  
https://github.com/t81dev/t81-foundation

A broader, exploratory balanced-ternary computing stack, including:
- virtual machines
- language experiments
- numeric representations
- system-level design sketches

This project has its **own scope** and should not be conflated with the
duotronic/TLU effort, though ideas may overlap.

---

## 5. AI / Quantization Context (Adjacent)

These repositories explore intersections between ternary representations and
AI/ML workflows. They are **contextual**, not authoritative.

### ● ternary / GGUF-related tooling  
(Various repositories under https://github.com/t81dev)

Purpose:
- ternary or low-precision quantization
- model inspection and conversion
- exploratory integration with existing ML tooling

These efforts inform experiments but do not define duotronic semantics.

---

## 6. Relationship Summary

| Layer | Repository | Role |
|-----|-----------|------|
| Normative | duotronic-whitepaper | Formal semantics and conformance |
| Interpretive | duotronic-computing | Narrative, boundaries, philosophy |
| Experimental | ternary-pager | Paging / memory falsification |
| Experimental | ternary_gcc_plugin | Compiler-level validation |
| Numeric | t81lib | Balanced ternary primitives |
| Exploratory | t81-foundation | Broader ternary system experiments |

---

## 7. Design Intent

This ecosystem is designed to:
- prevent scope creep
- separate meaning from mechanism
- allow failure without reputational cost
- make stopping a valid outcome

No repository is required to justify the existence of another.
Each may stand or fall independently.

---

## Status

This ecosystem map reflects the current state of exploration.
It may evolve, but it does not imply future work or endorsement.
