rray_as_axes <- function(axes, dimensionality) {
  .Call(export_rray_as_axes, axes, dimensionality)
}

rray_axes_complement <- function(axes, dimensionality) {
  .Call(export_rray_axes_complement, axes, dimensionality)
}
