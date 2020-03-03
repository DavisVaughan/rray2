#ifndef RRAY_EXPORT_H
#define RRAY_EXPORT_H


#define R_NO_REMAP
#include <R.h>
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

// Compile with `-fvisibility=hidden -DHAVE_VISIBILITY_ATTRIBUTE`
// if you link to this library
#include <R_ext/Visibility.h>
#define export attribute_visible extern


typedef DL_FUNC r_fn_ptr;
typedef R_CallMethodDef r_callable;
typedef R_ExternalMethodDef r_external;
typedef DllInfo r_dll_info;


static inline void r_register_r_callables(r_dll_info* dll,
                                          const r_callable* callables,
                                          const r_external* externals) {
  R_registerRoutines(dll, NULL, callables, NULL, externals);
  R_useDynamicSymbols(dll, FALSE);
}


#endif
