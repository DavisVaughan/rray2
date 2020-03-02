# nocov start

.onLoad <- function(libname, pkgname) {
  .Call(export_rray_init_library)
}

# nocov end
