# ------------------------------------------------------------------------------
# rray_dims()

test_that("fails on non-vector types", {
  expect_error(rray_dims(mean), "must be a vector, not a function")
  expect_error(rray_dims(quote(x)), "must be a vector, not a symbol")
  expect_error(rray_dims(quote(x + y)), "must be a vector, not a call")
})

test_that("The dimensions of NULL are integer()", {
  expect_identical(rray_dims(NULL), integer())
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

# ------------------------------------------------------------------------------
# rray_dims2()

test_that("all NULL values returns integer(), like the default of rray_dims_common()", {
  expect_identical(rray_dims2(NULL, NULL), integer())
  expect_identical(rray_dims2(NULL, NULL), rray_dims_common(NULL, NULL))
})

# ------------------------------------------------------------------------------
# rray_dims_common()

test_that("NULL values are ignored", {
  expect_identical(rray_dims_common(NULL, 1, NULL, 1:5), 5L)
})

test_that("All NULL values returns `.absent`", {
  expect_identical(rray_dims_common(), integer())
  expect_identical(rray_dims_common(.absent = 5L), 5L)
  expect_identical(rray_dims_common(NULL), integer())
  expect_identical(rray_dims_common(NULL, NULL), integer())
})

test_that("Providing `.dims` overrides NULL + `.absent` behavior", {
  expect_identical(rray_dims_common(.dims = c(1L, 1L)), c(1L, 1L))
  expect_identical(rray_dims_common(NULL, .dims = c(1L, 1L)), c(1L, 1L))
})

test_that("`.dims` can be broadcast", {
  expect_identical(rray_dims_common(matrix(1:5), .dims = 1L), c(5L, 1L))
})

test_that("integer() `.dims` is always broadcast", {
  expect_identical(rray_dims_common(1, .dims = integer()), 1L)
})

test_that("exactly matching dimensions works", {
  expect_identical(rray_dims_common(integer(), integer()),  0L)
  expect_identical(rray_dims_common(1, 1),  1L)
  expect_identical(rray_dims_common(matrix(), matrix()),  c(1L, 1L))
})

test_that("dimensions along the same axis are broadcast", {
  expect_identical(rray_dims_common(1, 1:2), 2L)
  expect_identical(rray_dims_common(1:2, 1), 2L)

  expect_identical(rray_dims_common(matrix(1), matrix(1:2, nrow = 2)), c(2L, 1L))
  expect_identical(rray_dims_common(matrix(1), matrix(1:2, ncol = 2)), c(1L, 2L))
})

test_that("can broadcast multiple axes at once", {
  expect_identical(rray_dims_common(matrix(1:2, nrow = 2), matrix(1:2, ncol = 2)), c(2L, 2L))
})

test_that("implicit axes have a value of 1", {
  expect_identical(rray_dims_common(1, array(dim = c(1L, 2L, 2L))), c(1L, 2L, 2L))
})

test_that("errors with incompatible dimensions along an axis", {
  verify_output(test_path("output/test-dimensions-incompatible.txt"), {
    "# Cannot broadcast size 2 to 3"
    rray_dims_common(1:2, 2:3, 3:5)

    "# Cannot broadcast size 0 to 2"
    rray_dims_common(integer(), 1:2)

    "# Gives information about the axis"
    rray_dims_common(matrix(ncol = 2), matrix(ncol = 3))

    "# `.dims` respects broadcasting rules"
    rray_dims_common(1:2, .dims = 3L)
  })
})
