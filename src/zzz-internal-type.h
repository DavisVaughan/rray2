#ifndef RRAY_INTERNAL_TYPE_H
#define RRAY_INTERNAL_TYPE_H


#include "zzz-internal-r.h"
#include "zzz-internal-util.h"

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

static inline enum r_type r_typeof(sexp* x) {
  return TYPEOF(x);
}

static inline const char* r_type_as_friendly_c_string(enum r_type type) {
  switch (type) {
  case r_type_null:         return "NULL";
  case r_type_symbol:       return "a symbol";
  case r_type_pairlist:     return "a pairlist node";
  case r_type_closure:      return "a function";
  case r_type_environment:  return "an environment";
  case r_type_promise:      return "an internal promise";
  case r_type_call:         return "a call";
  case r_type_special:      return "a primitive function";
  case r_type_builtin:      return "a primitive function";
  case r_type_string:       return "an internal string";
  case r_type_logical:      return "a logical vector";
  case r_type_integer:      return "an integer vector";
  case r_type_double:       return "a double vector";
  case r_type_complex:      return "a complex vector";
  case r_type_character:    return "a character vector";
  case r_type_dots:         return "an internal dots object";
  case r_type_any:          return "an internal `any` object";
  case r_type_list:         return "a list";
  case r_type_expression:   return "an expression vector";
  case r_type_bytecode:     return "an internal bytecode object";
  case r_type_pointer:      return "a pointer";
  case r_type_weakref:      return "a weak reference";
  case r_type_raw:          return "a raw vector";
  case r_type_s4:           return "an S4 object";

  case r_type_new:          return "an internal `new` object";
  case r_type_free:         return "an internal `free` object";

  case r_type_function:     return "a function";
  }

  never_reached("r_type_as_friendly_c_string");
}

static inline const char* r_sexp_as_friendly_c_string(sexp* x) {
  return r_type_as_friendly_c_string(r_typeof(x));
}

#endif
