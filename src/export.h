#ifndef RRAY_EXPORT_H
#define RRAY_EXPORT_H


#include "r.h"

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
