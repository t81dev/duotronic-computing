#ifndef TLU_INTRINSICS_H
#define TLU_INTRINSICS_H

/*
 * TLU compiler surface (non-normative convenience layer).
 *
 * This header defines a stable, portable call surface for TLU operations.
 * By default it lowers to the TLU ABI functions defined in tlu_abi.h.
 *
 * This header does not define semantics. Semantics are normative in appendix.md.
 * Conformance is defined in CONFORMANCE.md.
 *
 * Optional compiler-specific acceleration hooks may be added later behind
 * feature macros without changing user call sites.
 */

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ---- ABI dependency ---- */

#include "tlu_abi.h"

/* ---- Feature macros ---- */

/*
 * Define TLU_USE_BUILTINS to 1 to enable compiler-specific builtins
 * when available. Default is 0 (always use ABI).
 *
 * Builtins are intentionally not defined in this header yet; the macro
 * exists to stabilize the configuration surface.
 */
#ifndef TLU_USE_BUILTINS
#define TLU_USE_BUILTINS 0
#endif

/*
 * Define TLU_FORCE_ABI to 1 to force ABI calls even if builtins exist.
 * This is useful for debugging or differential testing.
 */
#ifndef TLU_FORCE_ABI
#define TLU_FORCE_ABI 0
#endif

/* ---- Inline wrappers (portable default) ---- */

static inline tlu_trit_t tlu_intrin_tmin(tlu_trit_t a, tlu_trit_t b) {
#if TLU_USE_BUILTINS && !TLU_FORCE_ABI
    /* Reserved for future builtins. Fall back to ABI for now. */
#endif
    return tlu_tmin(a, b);
}

static inline tlu_trit_t tlu_intrin_tmax(tlu_trit_t a, tlu_trit_t b) {
#if TLU_USE_BUILTINS && !TLU_FORCE_ABI
    /* Reserved for future builtins. */
#endif
    return tlu_tmax(a, b);
}

static inline tlu_trit_t tlu_intrin_tmaj(tlu_trit_t a, tlu_trit_t b, tlu_trit_t c) {
#if TLU_USE_BUILTINS && !TLU_FORCE_ABI
    /* Reserved for future builtins. */
#endif
    return tlu_tmaj(a, b, c);
}

static inline tlu_trit_t tlu_intrin_tnot(tlu_trit_t a) {
#if TLU_USE_BUILTINS && !TLU_FORCE_ABI
    /* Reserved for future builtins. */
#endif
    return tlu_tnot(a);
}

static inline tlu_trit_t tlu_intrin_tmux(tlu_trit_t cond, tlu_trit_t A, tlu_trit_t B, tlu_trit_t C) {
#if TLU_USE_BUILTINS && !TLU_FORCE_ABI
    /* Reserved for future builtins. */
#endif
    return tlu_tmux(cond, A, B, C);
}

/* Reduction */
static inline tlu_i32_t tlu_intrin_tnet(const tlu_trit_t* x, size_t n) {
#if TLU_USE_BUILTINS && !TLU_FORCE_ABI
    /* Reserved for future builtins. */
#endif
    return tlu_tnet(x, n);
}

/* ---- Optional alias macros (ergonomics) ---- */
/*
 * Define TLU_SHORT_NAMES to 1 to enable short operator names
 * without the tlu_intrin_ prefix.
 */
#ifndef TLU_SHORT_NAMES
#define TLU_SHORT_NAMES 0
#endif

#if TLU_SHORT_NAMES
  #define TMIN(a,b)        tlu_intrin_tmin((a),(b))
  #define TMAX(a,b)        tlu_intrin_tmax((a),(b))
  #define TMAJ(a,b,c)      tlu_intrin_tmaj((a),(b),(c))
  #define TNOT(a)          tlu_intrin_tnot((a))
  #define TMUX(c,A,B,C)    tlu_intrin_tmux((c),(A),(B),(C))
  #define TNET(x,n)        tlu_intrin_tnet((x),(n))
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* TLU_INTRINSICS_H */
