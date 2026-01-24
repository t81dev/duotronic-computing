# 05 — Failure Modes

Any proposal that claims broad applicability without clearly identifying its failure modes is incomplete. This essay enumerates situations where ternary semantics add cost, confusion, or false clarity rather than value.

Failure here is not a defect. It is a boundary.

## 1. When Semantics Are Already Exact

Ternary semantics provide value primarily where meaning is ambiguous, neutral, or symmetric. In domains where values are already exact by definition, ternary logic offers little benefit.

Examples include:
- pointer arithmetic
- memory addressing
- protocol state machines
- cryptographic primitives
- file system metadata

Introducing ternary values in these domains risks:
- obscuring invariants
- complicating verification
- weakening guarantees that depend on exactness

Binary representations are not merely sufficient here; they are appropriate.

## 2. Accidental Ambiguity

A common failure mode is introducing ternary semantics where ambiguity is *unintended*.

In many systems, an “unknown” value signals an error, incomplete initialization, or a bug. Treating such states as neutral rather than exceptional can mask real problems.

If ternary semantics are applied indiscriminately:
- errors may propagate silently
- invalid states may appear meaningful
- debugging becomes harder, not easier

Ternary logic must never become a substitute for proper error handling.

## 3. Overloading Meaning

Another failure occurs when a single ternary value is asked to represent too much.

For example:
- using neutrality to mean both “missing” and “irrelevant”
- using the same value for “unknown,” “masked,” and “don’t care”

When distinct semantic categories collapse into one, clarity is lost. Binary sentinels and flags, while cumbersome, at least make distinctions explicit.

Ternary semantics must be introduced only when the meaning they represent is singular and well-defined.

## 4. Control-Flow Contamination

Allowing ternary values to influence control flow directly is a critical error.

Branching, looping, and addressing require determinism. Introducing multi-valued conditions at this level creates:
- unpredictable execution paths
- unclear fault semantics
- increased verification burden

Under the duotronic model, ternary values remain **data**, not **decisions**. Violating this separation undermines the model entirely.

## 5. Performance Without Payoff

Ternary semantics may impose overhead:
- additional encoding or decoding
- increased register pressure
- reduced vector density
- more complex lowering paths

If these costs are not offset by a reduction in semantic complexity, the result is net loss.

This failure mode is especially likely in:
- tight inner loops
- compute-bound kernels
- latency-critical paths

In such cases, binary representations are often simpler and faster.

## 6. Misplaced Expectations

Another failure arises from expecting ternary semantics to deliver:
- universal performance gains
- simpler systems everywhere
- automatic correctness improvements

Ternary logic is not a shortcut. It is a tool for specific semantic problems. When applied outside those problems, it creates disappointment and skepticism.

Managing expectations is as important as defining semantics.

## 7. Failure as a Valid Outcome

The most important failure mode is refusing to stop.

If experiments demonstrate that ternary semantics:
- do not reduce complexity
- do not improve clarity
- do not justify their overhead

then discontinuing their use is the correct outcome.

A system that cannot fail gracefully is not robust.

## 8. Boundaries as Success

Identifying where ternary semantics *do not* help is as valuable as identifying where they might.

Clear boundaries prevent misuse, protect binary systems from unnecessary complexity, and preserve trust in the overall architecture.

The final essay addresses the remaining open questions—what is still unknown, what would falsify the duotronic approach, and what evidence would be required to proceed further.
