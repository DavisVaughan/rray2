#' Arithmetic
#'
#' These functions perform arithmetic between multiple arrays, with
#' broadcasting.
#'
#' @param x,y Arrays
#'
#' @return An array with dimensions of `rray_dims_common(x, y)`.
#'
#' @export
#' @examples
#' rray_add(matrix(1:5, nrow = 1), matrix(1:5, ncol = 1))
rray_add <- function(x, y) {
  .Call(export_rray_add, x, y)
}
