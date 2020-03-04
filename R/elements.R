#' Number of elements
#'
#' `rray_elements()` computes the number of individual elements in a vector.
#'
#' It generally computes the same thing as `length()`, but has a more
#' predictable name and errors on scalar objects.
#'
#' @param x A vector
#'
#' @return A single double. The number of elements in `x`.
#'
#' @export
#' @examples
#' rray_elements(1:5)
#'
#' rray_elements(matrix(1, 2, 2))
#'
#' # It is different from `vec_size()`,
#' # which returns the number of observations
#' library(vctrs)
#' vec_size(matrix(1, 2, 2))
rray_elements <- function(x) {
  .Call(export_rray_elements, x)
}

# For testing
rray_elements_from_dims <- function(dims) {
  .Call(export_rray_elements_from_dims, dims)
}
