#ifndef TLU_ABI_H
#define TLU_ABI_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int8_t  tlu_trit_t;
typedef int32_t tlu_i32_t;

/* Scalar ops */
tlu_trit_t tlu_tmin(tlu_trit_t a, tlu_trit_t b);
tlu_trit_t tlu_tmax(tlu_trit_t a, tlu_trit_t b);
tlu_trit_t tlu_tmaj(tlu_trit_t a, tlu_trit_t b, tlu_trit_t c);
tlu_trit_t tlu_tnot(tlu_trit_t a);
tlu_trit_t tlu_tmux(tlu_trit_t cond, tlu_trit_t A, tlu_trit_t B, tlu_trit_t C);

/* Reduction */
tlu_i32_t  tlu_tnet(const tlu_trit_t* x, size_t n);

#ifdef __cplusplus
}
#endif

#endif /* TLU_ABI_H */
