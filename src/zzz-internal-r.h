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

enum r_type {
  r_type_null        = 0,
  r_type_symbol      = 1,
  r_type_pairlist    = 2,
  r_type_closure     = 3,
  r_type_environment = 4,
  r_type_promise     = 5,
  r_type_call        = 6,
  r_type_special     = 7,
  r_type_builtin     = 8,
  r_type_string      = 9,
  r_type_logical     = 10,
  r_type_integer     = 13,
  r_type_double      = 14,
  r_type_complex     = 15,
  r_type_character   = 16,
  r_type_dots        = 17,
  r_type_any         = 18,
  r_type_list        = 19,
  r_type_expression  = 20,
  r_type_bytecode    = 21,
  r_type_pointer     = 22,
  r_type_weakref     = 23,
  r_type_raw         = 24,
  r_type_s4          = 25,

  r_type_new         = 30,
  r_type_free        = 31,

  r_type_function    = 99
};

typedef R_xlen_t r_ssize;
#define R_SSIZE_MAX R_XLEN_T_MAX

typedef Rbyte r_byte_t;
typedef Rcomplex r_complex_t;

#define r_null R_NilValue

#define KEEP PROTECT
#define FREE UNPROTECT
#define KEEP_N(x, n) (++n, KEEP(x))
#define KEEP_WITH_INDEX(x, i) PROTECT_WITH_INDEX(x, &i)
#define REKEEP REPROTECT

#define r_mark_precious R_PreserveObject
#define r_unmark_precious R_ReleaseObject


#endif
