#ifndef RRAY_INTERNAL_FUNCTIONAL_H
#define RRAY_INTERNAL_FUNCTIONAL_H

#include "zzz-internal-r.h"

sexp* reduce(sexp* current, sexp* rest, sexp* (*fn)(sexp* current, sexp* next));


#endif
