#' Compute dimensionality
#'
#' `rray_dimensionality()` computes the dimensionality of an object. This is
#' also known as the "number of dimensions".
#'
#' @section Invariants:
#'
#' - `vec_size(rray_dimensionality(x)) == 1L`
#'
#' - `vec_ptype(rray_dimensionality(x)) == integer()`
#'
#' - `rray_dimensionality(x) == vec_size(rray_dims(x))`
#'
#' @param x A vector
#'
#' @return An integer of size 1 of the dimensionality of `x`.
#'
#' @export
#' @examples
#' rray_dimensionality(1)
#' rray_dimensionality(matrix())
#' rray_dimensionality(NULL)
rray_dimensionality <- function(x) {
  .Call(export_rray_dimensionality, x)
}

rray_as_dimensionality <- function(dimensionality) {
  .Call(export_rray_as_dimensionality, dimensionality)
}
