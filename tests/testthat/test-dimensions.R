test_that("fails on non-vector types", {
  expect_error(rray_dims(mean), "must be a vector, not a function")
  expect_error(rray_dims(quote(x)), "must be a vector, not a symbol")
  expect_error(rray_dims(quote(x + y)), "must be a vector, not a call")
})

test_that("works with NULL", {
  expect_identical(rray_dims(NULL), 0L)
})

test_that("works with bare vectors", {
  expect_identical(rray_dims(lgl()), 0L)
  expect_identical(rray_dims(int()), 0L)
  expect_identical(rray_dims(dbl()), 0L)
  expect_identical(rray_dims(raw()), 0L)
  expect_identical(rray_dims(cpl()), 0L)
  expect_identical(rray_dims(list()), 0L)
})

test_that("a bare vector's length is its dimensions", {
  expect_identical(rray_dims(1:5), 5L)
})

test_that("works with S3 types", {
  expect_identical(rray_dims(factor("a")), 1L)
})

# TODO: Is this right?
test_that("considers data frames as lists and uses the length", {
  expect_identical(rray_dims(data.frame(x = 1, y = 2)), 2L)
})

test_that("works with matrices", {
  expect_identical(rray_dims(matrix()), c(1L, 1L))
})

test_that("works with arrays of all dimensionalities", {
  x0 <- array(int())
  x1 <- array(1)
  x11 <- array(1, dim = c(1, 1))
  x111 <- array(1, dim = c(1, 1, 1))
  x213 <- array(1, dim = c(2, 1, 3))

  expect_identical(rray_dims(x0), 0L)
  expect_identical(rray_dims(x1), 1L)
  expect_identical(rray_dims(x11), c(1L, 1L))
  expect_identical(rray_dims(x111), c(1L, 1L, 1L))
  expect_identical(rray_dims(x213), c(2L, 1L, 3L))
})

test_that("errors on long vectors, since R internally does not have support for long matrices", {
  x <- 1:(.Machine$integer.max + 1)
  expect_error(rray_dims(x), "must have length less than")
})
