#' Compute dimensionality
#'
#' `rray_dimensionality()` computes the dimensionality of an object. This is
#' also known as the "number of dimensions".
#'
#' @param x A vector
#'
#' @export
#' @examples
#' rray_dimensionality(1)
#' rray_dimensionality(matrix())
rray_dimensionality <- function(x) {
  .Call(export_rray_dimensionality, x)
}
