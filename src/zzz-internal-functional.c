#include "zzz-internal-r.h"
#include "zzz-internal-sexp.h"
#include "zzz-internal-vec-list.h"

#include "zzz-internal-functional.h"

sexp* reduce(sexp* current, sexp* rest, sexp* (*fn)(sexp* current, sexp* next)) {
  r_ssize size = r_length(rest);

  for (r_ssize i = 0; i < size; ++i) {
    KEEP(current);

    sexp* next = r_list_get(rest, i);
    current = fn(current, next);

    FREE(1);
  }

  return current;
}
