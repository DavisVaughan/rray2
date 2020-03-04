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
