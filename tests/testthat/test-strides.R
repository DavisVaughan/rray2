test_that("NULL produces a stride of 1", {
  expect_identical(rray_strides(NULL), 1)
})

test_that("strides for 1D objects are 1", {
  expect_identical(rray_strides(1), 1)
  expect_identical(rray_strides(letters), 1)
})

test_that("strides are a shifted cumulative product of the dimensions", {
  make_strides <- function(x) {
    dims <- rray_dims(x)
    shifted <- c(1L, dims[-length(dims)])
    cumprod(shifted)
  }

  x1 <- array(dim = c(2, 3))
  x2 <- array(dim = c(2, 3, 2))

  expect_identical(rray_strides(x1), make_strides(x1))
  expect_identical(rray_strides(x2), make_strides(x2))
})

test_that("strides of an array with shape, but 0 elements is computed correctly", {
  x <- array(dim = c(0, 2, 2))
  y <- array(dim = c(2, 0, 2))

  expect_identical(rray_strides(x), c(1, 0, 0))
  expect_identical(rray_strides(y), c(1, 2, 0))
})

test_that("broadcastable strides have a 0 where the dimensions were 1", {
  x <- array(dim = c(1, 1, 1))
  y <- array(dim = c(1, 2, 1, 2))

  expect_identical(rray_strides(x, broadcastable = TRUE), c(0, 0, 0))
  expect_identical(rray_strides(y, broadcastable = TRUE), c(0, 1, 0, 2))
})

test_that("broadcastable strides preserves the original cumulative product", {
  x <- array(dim = c(5, 4, 1, 3))

  strides <- rray_strides(x)
  strides[[3]] <- 0

  expect_identical(rray_strides(x, broadcastable = TRUE), strides)
})

test_that("`broadcastable` is validated", {
  expect_error(rray_strides(1, "x"), "must be")
  expect_error(rray_strides(1, c(TRUE, TRUE)), "must be")
  expect_error(rray_strides(1, NA), "must be")
})
