# 06 — Open Questions

This collection has argued for restraint: that ternary semantics, if useful at all, are useful only within narrow, well-defined boundaries. Even within those boundaries, significant questions remain unresolved.

This essay enumerates those questions explicitly. They are not a roadmap. They are a set of conditions that must be satisfied before any further commitment is justified.

## 1. Where Does Semantic Overhead Actually Dominate?

Much of the motivation for ternary semantics rests on the claim that certain workloads incur persistent structural overhead when modeled in binary.

An open question is how often this situation occurs in practice.

Specifically:
- How frequently do neutrality and uncertainty appear as first-class concepts rather than edge cases?
- In which domains does semantic indirection meaningfully dominate other sources of complexity?
- Are these patterns stable over time, or artifacts of current software practice?

Without clear answers, ternary semantics risk solving rare or transient problems.

## 2. Measurement Without Bias

Evaluating ternary semantics requires care.

If benchmarks are chosen because they favor ternary representations, results are misleading. If benchmarks ignore semantic complexity and focus only on raw throughput, results are equally misleading.

Open questions include:
- How should “semantic complexity” be measured?
- What constitutes a fair comparison between explicit semantics and implicit conventions?
- How can negative results be reported without discouraging exploration?

Until measurement practices are agreed upon, claims of benefit should be treated as provisional.

## 3. Interaction with Existing Toolchains

Modern software systems are deeply shaped by their tooling:
- compilers
- debuggers
- profilers
- verification frameworks

Introducing ternary semantics raises questions such as:
- How visible should ternary values be during debugging?
- How should static analysis reason about neutrality or uncertainty?
- Can existing optimization passes preserve ternary meaning, or will they erase it?

If ternary semantics cannot be observed and reasoned about effectively, their clarity at the semantic level may not translate into clarity at the system level.

## 4. Software Costs vs. Hardware Justification

The duotronic model insists on software-first validation. Hardware acceleration is an optimization, not a prerequisite.

Open questions include:
- How large is the software overhead of maintaining ternary semantics?
- At what point does that overhead justify specialized hardware?
- Can hardware acceleration remain bounded without creeping into control logic?

Answering these questions requires restraint. Premature hardware design risks locking in assumptions that software experiments have not yet validated.

## 5. Interoperability and Containment

Another open question is how ternary semantics interact with binary-dominated ecosystems.

Specifically:
- How easily can ternary values be introduced and removed at system boundaries?
- What invariants must be preserved to avoid semantic leakage?
- Can ternary semantics be localized to small regions of code without infecting interfaces?

If containment fails, the duotronic model fails with it.

## 6. What Would Falsify This Approach?

A credible proposal must specify what would disprove it.

The duotronic approach should be considered falsified if:
- semantic complexity does not decrease in practice
- software fallback proves unwieldy or error-prone
- benefits vanish under realistic workloads
- containment boundaries cannot be maintained
- failure modes outweigh clarity gains

Any of these outcomes is sufficient reason to abandon the approach.

## 7. Criteria for Proceeding

Conversely, proceeding further would require evidence that:
- ternary semantics reduce semantic indirection in identifiable domains
- the reduction persists across implementations
- costs remain bounded and local
- binary control remains uncompromised

Absent such evidence, restraint remains the correct position.

## 8. An Ending That Is Not a Conclusion

This collection does not argue that ternary semantics *should* be adopted.

It argues that, under strict constraints, they *might* reduce structural overhead in limited contexts—and that this possibility is worth examining carefully.

If that examination leads nowhere, the result is still valuable: a clearer understanding of where meaning belongs in computing systems, and where it does not.

Sometimes the most productive outcome of an investigation is a well-defined stopping point.
