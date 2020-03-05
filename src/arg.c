#include "rray.h"

const char* rray_as_arg(sexp* arg) {
  if (r_typeof(arg) != r_type_character) {
    r_abort("`arg` must be a character vector, not %s", r_sexp_as_friendly_c_string(arg));
  }

  if (r_length(arg) != 1) {
    r_abort("`arg` must have length 1, not %i", r_length(arg));
  }

  return r_chr_get_c_string(arg, 0);
}
