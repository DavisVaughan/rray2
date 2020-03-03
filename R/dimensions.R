#' Compute dimensions
#'
#' @description
#' `rray_dims()` computes the dimensions of a vector.
#'
#' This is similar to [dim()], but errors on scalar objects and never
#' returns `NULL`. The dimensions of a bare vector like `1:5` are its length.
#'
#' @param x A vector
#'
#' @export
#' @examples
#' rray_dims(1)
#' rray_dims(array(1:6, dim = c(2, 3)))
#'
#' try(rray_dims(mean))
rray_dims <- function(x) {
  .Call(export_rray_dims, x)
}

rray_dims2 <- function(x, y) {
  .Call(export_rray_dims2, x, y)
}

rray_dims_common <- function(..., .dims = NULL, .absent = integer()) {
  .Call(export_rray_dims_common, .dims, .absent, environment())
}
