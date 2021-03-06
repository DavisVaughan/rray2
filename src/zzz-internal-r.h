#ifndef RRAY_INTERNAL_R_H
#define RRAY_INTERNAL_R_H


#include <inttypes.h>
#include <stdbool.h>

#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <Rversion.h>
#include <R_ext/Rdynload.h>

typedef struct SEXPREC sexp;

typedef R_xlen_t r_ssize;
#define R_SSIZE_MAX R_XLEN_T_MAX

#define R_SHORT_SSIZE_MAX R_LEN_T_MAX

typedef Rbyte r_byte_t;
typedef Rcomplex r_complex_t;

#define r_null R_NilValue

#define KEEP PROTECT
#define FREE UNPROTECT
#define KEEP_N(x, n) (++n, KEEP(x))
#define KEEP_WITH_INDEX(x, i) PROTECT_WITH_INDEX(x, &i)
#define REKEEP REPROTECT


#endif
