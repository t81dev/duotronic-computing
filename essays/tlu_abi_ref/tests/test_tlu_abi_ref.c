#include "tlu_abi.h"
#include <stdio.h>
#include <stdlib.h>

static void expect_trit(const char* name, tlu_trit_t got, tlu_trit_t want) {
    if (got != want) {
        fprintf(stderr, "%s: got %d want %d\n", name, (int)got, (int)want);
        exit(1);
    }
}

static void expect_i32(const char* name, tlu_i32_t got, tlu_i32_t want) {
    if (got != want) {
        fprintf(stderr, "%s: got %d want %d\n", name, (int)got, (int)want);
        exit(1);
    }
}

int main(void) {
    /* Basic vectors from appendix.md (informative section) */
    expect_trit("TMIN(+1,0)", tlu_tmin(+1,0), 0);
    expect_trit("TMIN(0,-1)", tlu_tmin(0,-1), -1);
    expect_trit("TMAX(-1,0)", tlu_tmax(-1,0), 0);
    expect_trit("TMAX(0,+1)", tlu_tmax(0,+1), +1);

    expect_trit("TNOT(-1)", tlu_tnot(-1), +1);
    expect_trit("TNOT(0)",  tlu_tnot(0), 0);
    expect_trit("TNOT(+1)", tlu_tnot(+1), -1);

    expect_trit("TMUX(-1,A,B,C)", tlu_tmux(-1,-1,0,+1), -1);
    expect_trit("TMUX(0,A,B,C)",  tlu_tmux(0,-1,0,+1), 0);
    expect_trit("TMUX(+1,A,B,C)", tlu_tmux(+1,-1,0,+1), +1);

    /* Exhaustive TMAJ over 3^3 inputs */
    tlu_trit_t vals[3] = { -1, 0, +1 };
    for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) for (int k = 0; k < 3; ++k) {
        tlu_trit_t a = vals[i], b = vals[j], c = vals[k];
        /* Majority rule equivalence: median under ordering */
        /* Compute expected by sorting */
        tlu_trit_t x=a, y=b, z=c;
        if (x > y) { tlu_trit_t t=x; x=y; y=t; }
        if (y > z) { tlu_trit_t t=y; y=z; z=t; }
        if (x > y) { tlu_trit_t t=x; x=y; y=t; }
        expect_trit("TMAJ", tlu_tmaj(a,b,c), y);
    }

    /* TNET small checks */
    tlu_trit_t v1[3] = { +1, -1, 0 };
    expect_i32("TNET([+1,-1,0])", tlu_tnet(v1, 3), 0);

    tlu_trit_t v2[3] = { +1, +1, -1 };
    expect_i32("TNET([+1,+1,-1])", tlu_tnet(v2, 3), +1);

    /* Normalization checks: any nonzero positive -> +1, any negative -> -1 */
    expect_trit("norm(+7) in TNOT", tlu_tnot(+7), -1);
    expect_trit("norm(-7) in TNOT", tlu_tnot(-7), +1);

    printf("OK\n");
    return 0;
}
