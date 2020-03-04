test_that("fails on non-vector types", {
  expect_error(rray_dimensionality(mean), "must be a vector, not a function")
  expect_error(rray_dimensionality(quote(x)), "must be a vector, not a symbol")
  expect_error(rray_dimensionality(quote(x + y)), "must be a vector, not a call")
})

test_that("the dimensionality of NULL is `1`, to match the dimensions of NULL being `0`", {
  # This invariant should always hold
  # length(rray_dims(x)) == rray_dimensionality(x)
  expect_identical(rray_dimensionality(NULL), 1L)
})

test_that("works with bare vectors", {
  expect_identical(rray_dimensionality(lgl()), 1L)
  expect_identical(rray_dimensionality(int()), 1L)
  expect_identical(rray_dimensionality(dbl()), 1L)
  expect_identical(rray_dimensionality(raw()), 1L)
  expect_identical(rray_dimensionality(cpl()), 1L)
  expect_identical(rray_dimensionality(list()), 1L)
})

test_that("works with S3 types", {
  expect_identical(rray_dimensionality(factor()), 1L)
})

test_that("considers data frames as 1-D", {
  expect_identical(rray_dimensionality(data.frame()), 1L)
})

test_that("works with matrices", {
  expect_identical(rray_dimensionality(matrix()), 2L)
})

test_that("works with arrays of all dimensionalities", {
  x0 <- array(int())
  x1 <- array(1)
  x11 <- array(1, dim = c(1, 1))
  x111 <- array(1, dim = c(1, 1, 1))

  expect_identical(rray_dimensionality(x0), 1L)
  expect_identical(rray_dimensionality(x1), 1L)
  expect_identical(rray_dimensionality(x11), 2L)
  expect_identical(rray_dimensionality(x111), 3L)
})
