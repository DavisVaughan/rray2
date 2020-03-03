#' Compute dimensionality
#'
#' `rray_dimensionality()` computes the dimensionality of an object. This is
#' also known as the "number of dimensions".
#'
#' @section Invariants:
#'
#' - `vec_size(rray_dims(x)) == rray_dimensionality(x)`
#'
#' @param x A vector
#'
#' @export
#' @examples
#' rray_dimensionality(1)
#' rray_dimensionality(matrix())
#' rray_dimensionality(NULL)
rray_dimensionality <- function(x) {
  .Call(export_rray_dimensionality, x)
}
