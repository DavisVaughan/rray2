test_that("can reduce an array with dimensionality 1", {
  expect_identical(rray_sum(1L, 1), array(1))
  expect_identical(rray_sum(1:2, 1), array(3))
})

test_that("can reduce an array with dimensionality 2", {
  x <- array(1:6, c(2, 3))

  expect_identical(rray_sum(x, 1), array(c(3, 7, 11), c(1, 3)))
  expect_identical(rray_sum(x, 2), array(c(9, 12), c(2, 1)))

  expect_identical(rray_sum(x, c(1, 2)), array(21, c(1, 1)))
})

test_that("can reduce an array with dimensionality 3", {
  x <- array(1:8, c(2, 2, 2))

  expect_identical(rray_sum(x, 1), array(c(3, 7, 11, 15), c(1, 2, 2)))
  expect_identical(rray_sum(x, 2), array(c(4, 6, 12, 14), c(2, 1, 2)))
  expect_identical(rray_sum(x, 3), array(c(6, 8, 10, 12), c(2, 2, 1)))

  expect_identical(rray_sum(x, c(1, 2)), array(c(10, 26), c(1, 1, 2)))
  expect_identical(rray_sum(x, c(2, 3)), array(c(16, 20), c(2, 1, 1)))
  expect_identical(rray_sum(x, c(1, 3)), array(c(14, 22), c(1, 2, 1)))

  expect_identical(rray_sum(x, c(1, 2, 3)), array(36, c(1, 1, 1)))
})

test_that("reducing over no dimensions does nothing", {
  x <- array(1:6, c(2, 3))
  expect_equal(rray_sum(x, integer()), x)
})

test_that("can reduce an empty integer", {
  expect_identical(rray_sum(integer(), 1), array(0))
})

test_that("can reduce an empty matrix of varying types", {
  x <- matrix(integer(), nrow = 0, ncol = 0)
  y <- matrix(integer(), nrow = 2, ncol = 0)
  z <- matrix(integer(), nrow = 0, ncol = 2)

  expect_identical(rray_sum(x, 1), matrix(numeric(), nrow = 1, ncol = 0))
  expect_identical(rray_sum(x, 2), matrix(numeric(), nrow = 0, ncol = 1))

  expect_identical(rray_sum(y, 1), matrix(numeric(), nrow = 1, ncol = 0))

  # [2, 0] -> [2, 1] - fill with sum identity of 0
  expect_identical(rray_sum(y, 2), matrix(0, nrow = 2, ncol = 1))

  expect_identical(rray_sum(z, 1), matrix(0, nrow = 1, ncol = 2))

  # [0, 2] -> [1, 2] - fill with sum identity of 0
  expect_identical(rray_sum(z, 2), matrix(numeric(), nrow = 0, ncol = 1))
})
