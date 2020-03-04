rray_elements <- function(x) {
  .Call(export_rray_elements, x)
}

rray_elements_from_dims <- function(dims) {
  .Call(export_rray_elements_from_dims, dims)
}
