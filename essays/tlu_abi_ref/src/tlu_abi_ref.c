#include "tlu_abi.h"

/* Normalize to {-1,0,+1} as specified in TLU_ABI.md */
static inline tlu_trit_t tlu_norm_trit(tlu_trit_t v) {
    if (v < 0) return (tlu_trit_t)-1;
    if (v > 0) return (tlu_trit_t)+1;
    return (tlu_trit_t)0;
}

/* Total order: -1 < 0 < +1 */
tlu_trit_t tlu_tmin(tlu_trit_t a, tlu_trit_t b) {
    a = tlu_norm_trit(a);
    b = tlu_norm_trit(b);
    return (a < b) ? a : b;
}

tlu_trit_t tlu_tmax(tlu_trit_t a, tlu_trit_t b) {
    a = tlu_norm_trit(a);
    b = tlu_norm_trit(b);
    return (a > b) ? a : b;
}

/* Median of three under ordering -1 < 0 < +1 */
tlu_trit_t tlu_tmaj(tlu_trit_t a, tlu_trit_t b, tlu_trit_t c) {
    a = tlu_norm_trit(a);
    b = tlu_norm_trit(b);
    c = tlu_norm_trit(c);

    /* Sorting network for 3 elements */
    tlu_trit_t x = a, y = b, z = c;
    if (x > y) { tlu_trit_t t = x; x = y; y = t; }
    if (y > z) { tlu_trit_t t = y; y = z; z = t; }
    if (x > y) { tlu_trit_t t = x; x = y; y = t; }
    return y; /* median */
}

tlu_trit_t tlu_tnot(tlu_trit_t a) {
    a = tlu_norm_trit(a);
    return (tlu_trit_t)(-a);
}

tlu_trit_t tlu_tmux(tlu_trit_t cond, tlu_trit_t A, tlu_trit_t B, tlu_trit_t C) {
    cond = tlu_norm_trit(cond);
    A = tlu_norm_trit(A);
    B = tlu_norm_trit(B);
    C = tlu_norm_trit(C);

    if (cond < 0) return A;
    if (cond > 0) return C;
    return B;
}

tlu_i32_t tlu_tnet(const tlu_trit_t* x, size_t n) {
    /* Caller must provide valid x when n>0 per ABI. */
    tlu_i32_t sum = 0;
    for (size_t i = 0; i < n; ++i) {
        tlu_trit_t v = tlu_norm_trit(x[i]);
        sum += (tlu_i32_t)v; /* v ∈ {-1,0,+1} */
    }
    return sum;
}
