test_that("1D arithmetic is correct", {
  expect_equal(rray_add(1L, 1L), array(2))
  expect_equal(rray_add(1L, -1L), array(0))
})

test_that("broadcasting one input works", {
  x <- matrix(1:5)
  expect <- matrix(2:6)
  expect_equal(rray_add(1L, x), expect)
  expect_equal(rray_add(matrix(1L), x), expect)

  x <- matrix(1:5, nrow = 1)
  expect <- matrix(2:6, nrow = 1)
  expect_equal(rray_add(1L, x), expect)
  expect_equal(rray_add(matrix(1L), x), expect)
})

test_that("broadcasting both inputs works", {
  x <- matrix(1:5)
  y <- matrix(1:5, nrow = 1)
  expect <- apply(x, 1, function(x) x + y)

  expect_equal(rray_add(x, y), expect)
})

test_that("broadcasting works with 3 dimensions", {
  x <- array(1:8, c(2, 2, 2))

  a <- matrix(1:2)
  b <- matrix(1:2, nrow = 1)
  c <- matrix(1:4, nrow = 2, ncol = 2)

  xa <- x + 1:2
  xb <- x + rep(c(1, 1, 2, 2), 2)
  xc <- x + rep(1:4, 2)


  expect_equal(rray_add(x, x), x + x)
  expect_equal(rray_add(x, a), xa)
  expect_equal(rray_add(x, b), xb)
  expect_equal(rray_add(x, c), xc)
})
