#ifndef RRAY_INTERNAL_CND_H
#define RRAY_INTERNAL_CND_H


#include "zzz-internal-r.h"


__attribute__((noreturn)) void r_abort(const char* fmt, ...);


void r_stop_scalar_type(sexp* x, const char* arg);


#endif
