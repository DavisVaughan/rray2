#' Dimensions
#'
#' @description
#' - `rray_dims()` computes the dimensions of a vector.
#'
#' - `rray_dims_common()` computes the common dimensions of multiple vectors,
#'   using the rules of broadcasting.
#'
#' @details
#' `rray_dims()` is similar to [dim()], but errors on scalar objects and never
#' returns `NULL`. The dimensions of a bare vector, such as `1:5`, are its
#' length, and the dimensions of `NULL` are `0`.
#'
#' @section Invariants:
#'
#' - `vec_size(rray_dims(x)) == rray_dimensionality(x)`
#'
#' - `vec_ptype(rray_dims(x)) == integer()`
#'
#' - `vec_size(rray_dims_common(...)) == max(map(list(...), rray_dimensionality))`
#'
#' - `vec_ptype(rray_dims_common(...)) == integer()`
#'
#' @param x A vector
#' @param ... Vectors to find common dimensions for
#' @param .dims If `NULL`, the common dimensions are computed solely from
#'   `...`. Otherwise, an integer vector of dimensions to start the common
#'   dimension computation from.
#' @param .absent The dimensions to return when `...` is empty, or when all
#'   inputs are `NULL`.
#'
#' @return
#' - `rray_dims()`: An integer vector with a size equal to the dimensionality
#'   of `x` holding the dimensions.
#'
#' - `rray_dims_common()`: An integer vector with a size equal to the
#'   maximum dimensionality of the inputs holding the common dimensions.
#'
#' @export
#' @examples
#' rray_dims(1)
#' rray_dims(array(1:6, dim = c(2, 3)))
#'
#' rray_dims(NULL)
#'
#' rray_dims_common(1, 1:2)
#' rray_dims_common(
#'   matrix(1:5, ncol = 5),
#'   matrix(1:5, nrow = 5)
#' )
#'
#' # `.dims` starts the computation, but can still be broadcast
#' # against the dimensions of the input
#' rray_dims_common(matrix(1:5), .dims = c(1L, 5L))
#'
#' try(rray_dims(mean))
rray_dims <- function(x) {
  .Call(export_rray_dims, x)
}

#' @rdname rray_dims
#' @export
rray_dims_common <- function(..., .dims = NULL, .absent = 0L) {
  .Call(export_rray_dims_common, .dims, .absent, environment())
}

rray_dims2 <- function(x, y) {
  .Call(export_rray_dims2, x, y)
}

rray_dims_expand <- function(dims, dimensionality) {
  .Call(export_rray_dims_expand, dims, dimensionality)
}

rray_as_dims <- function(dims) {
  .Call(export_rray_as_dims, dims)
}
