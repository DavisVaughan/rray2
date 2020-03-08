#' Strides
#'
#' @description
#' `rray_strides()` computes the _strides_ of an array.
#'
#' Strides represent the distance between elements of a particular axis. They
#' are computed from the dimensions of the array by:
#'
#' - Appending a `1L` to the front of the dimensions
#' - Dropping the last dimension
#' - Computing the cumulative product of the result
#'
#' Strides are used internally for broadcasting and help transition from
#' _array_ locations to _flat_ locations. For example, given a `(3, 2, 3)`
#' array, an array location of `[2, 1, 3]` would correspond to a flat location
#' of `14`, which could be used to index a 1D version of the array.
#'
#' @section Invariants:
#'
#' - `vec_size(rray_strides(x)) == vec_size(rray_dims(x))`
#'
#' - `rray_strides(x) == cumprod(c(1L, rray_dims(x)[-length(rray_dims(x))]))`
#'
#' @param x A vector
#'
#' @param broadcastable A single logical. Should broadcastable strides be
#'   computed? The only difference between this and non-broadcastable strides
#'   is that a `0` is returned as the stride value for any axis with a dimension
#'   size of `1`. Broadcastable strides generate the same flat location when
#'   combined with array locations, but greatly simplify internal calculations.
#'
#' @return A double vector with size equal to the dimensionality of `x` holding
#'   the strides.
#'
#' @export
#' @examples
#' rray_strides(1:5)
#' rray_strides(array(1, dim = c(2, 2, 2)))
#'
#' # ---------------------------------------------------------------------------
#'
#' x <- array(1:18, dim = c(3, 2, 3))
#' x_flat <- as.vector(x)
#'
#' # Look along the second axis
#' as.vector(x[, 1, , drop = FALSE])
#'
#' # We can use the strides to transform array locations to
#' # flat locations that we can index `x_flat` with to extract
#' # the first column. This algorithm only works if the
#' # array locations are 0-based, and it returns a 0-based location.
#' axis1 <- c(0, 1, 2, 0, 1, 2, 0, 1, 2)
#' axis2 <- c(0, 0, 0, 0, 0, 0, 0, 0, 0)
#' axis3 <- c(0, 0, 0, 1, 1, 1, 2, 2, 2)
#' strides <- rray_strides(x)
#'
#' locs <- axis1 * strides[[1]] +
#'         axis2 * strides[[2]] +
#'         axis3 * strides[[3]]
#'
#' x_flat[locs + 1]
#'
#' # ---------------------------------------------------------------------------
#'
#' # Non-broadcastable strides produce the same location
#' # values as broadcastable strides
#'
#' x <- array(1:6, dim = c(2, 1, 3))
#' x_flat <- as.vector(x)
#'
#' strides <- rray_strides(x)
#' strides
#'
#' strides_broadcastable <- rray_strides(x, broadcastable = TRUE)
#' strides_broadcastable
#'
#' # `axis2` can only ever be `0`, because
#' # it is a 0-based index and there is only 1 column
#' # in `x`. So the multiplication by the `0` stride value
#' # later on has no effect.
#' axis1 <- c(0, 1)
#' axis2 <- c(0, 0)
#' axis3 <- c(1, 1)
#'
#' locs1 <- axis1 * strides[[1]] +
#'          axis2 * strides[[2]] +
#'          axis3 * strides[[3]]
#'
#' locs2 <- axis1 * strides_broadcastable[[1]] +
#'          axis2 * strides_broadcastable[[2]] +
#'          axis3 * strides_broadcastable[[3]]
#'
#' # The array location
#' x[1:2, 1, 2]
#'
#' # The flat location with regular strides
#' x_flat[locs1 + 1]
#'
#' # The flat location with broadcastable strides
#' x_flat[locs2 + 1]
rray_strides <- function(x, broadcastable = FALSE) {
  .Call(export_rray_strides, x, broadcastable)
}

rray_strides_from_dims <- function(dims, broadcastable = FALSE) {
  .Call(export_rray_strides_from_dims, dims, broadcastable)
}
