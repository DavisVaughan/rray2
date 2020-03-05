# ------------------------------------------------------------------------------
# rray_dims()

test_that("fails on non-vector types", {
  expect_error(rray_dims(mean), "must be a vector, not a function")
  expect_error(rray_dims(quote(x)), "must be a vector, not a symbol")
  expect_error(rray_dims(quote(x + y)), "must be a vector, not a call")
})

test_that("The dimensions of NULL are 0L", {
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
  # Only if ALTREP is available, to avoid running out of memory
  # Always skip Windows, which seems to fail even with ALTREP
  skip_if(getRversion() < "3.6.0")
  skip_on_os("windows")

  x <- 1:(.Machine$integer.max + 1)
  expect_error(rray_dims(x), "must have length less than")
})

# ------------------------------------------------------------------------------
# rray_dims2()

test_that("all NULL values returns 0, like the default of rray_dims_common()", {
  expect_identical(rray_dims2(NULL, NULL), 0L)
  expect_identical(rray_dims2(NULL, NULL), rray_dims_common(NULL, NULL))
})

# ------------------------------------------------------------------------------
# rray_dims_common()

test_that("NULL values are ignored", {
  expect_identical(rray_dims_common(NULL, 1, NULL, 1:5), 5L)
})

test_that("All NULL values returns `.absent`", {
  expect_identical(rray_dims_common(), 0L)
  expect_identical(rray_dims_common(.absent = 5L), 5L)
  expect_identical(rray_dims_common(NULL), 0L)
  expect_identical(rray_dims_common(NULL, NULL), 0L)
})

test_that("Providing `.dims` overrides NULL + `.absent` behavior", {
  expect_identical(rray_dims_common(.dims = c(1L, 1L)), c(1L, 1L))
  expect_identical(rray_dims_common(NULL, .dims = c(1L, 1L)), c(1L, 1L))
})

test_that("`.dims` can be broadcast", {
  expect_identical(rray_dims_common(matrix(1:5), .dims = 1L), c(5L, 1L))
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

test_that("`.dims` can be an integerish double", {
  expect_identical(rray_dims_common(.dims = 1), 1L)
})

test_that("`.dims` is validated", {
  expect_error(rray_dims_common(.dims = integer()), "`.dims` must have a length of at least 1, not 0")
  expect_error(rray_dims_common(.dims = "x"), class = "vctrs_error_cast_lossy")
})

test_that("`.absent` can be an integerish double", {
  expect_identical(rray_dims_common(.absent = 1), 1L)
})

test_that("`.absent` is validated", {
  expect_error(rray_dims_common(.absent = integer()), "must not be length 0")
  expect_error(rray_dims_common(.absent = "x"), class = "vctrs_error_cast_lossy")
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

# ------------------------------------------------------------------------------
# rray_dims_expand()

test_that("can expand to the same dimensionality", {
  expect_identical(rray_dims_expand(1, 1), 1L)
})

test_that("can expand to higher dimensionality", {
  expect_identical(rray_dims_expand(2, 3), c(2L, 1L, 1L))
  expect_identical(rray_dims_expand(c(3, 2), 4), c(3L, 2L, 1L, 1L))
})

test_that("cannot reduce dimensionality", {
  expect_error(rray_dims_expand(c(2, 3), 1), "from 2 to 1")
  expect_error(rray_dims_expand(1, 0), "from 1 to 0")
})

# ------------------------------------------------------------------------------
# rray_dims_split()

test_that("can do a standard dims split", {
  expect_identical(rray_dims_split(c(1, 2), 1), list(1L, 2L))
})

test_that("can select no `axes`", {
  expect_identical(rray_dims_split(c(4, 2), integer()), list(integer(), c(4L, 2L)))
})

test_that("can select all `axes`", {
  expect_identical(rray_dims_split(c(4, 2), c(1, 2)), list(c(4L, 2L), integer()))
})

test_that("dims are split in the order specified by `axes`", {
  expect_identical(rray_dims_split(c(4, 3), c(2, 1)), list(c(3L, 4L), integer()))
  expect_identical(rray_dims_split(c(4, 3, 5), c(3, 1)), list(c(5L, 4L), 3L))
})

# ------------------------------------------------------------------------------
# rray_as_dims()

test_that("dims are cast to integer", {
  expect_type(rray_as_dims(1), "integer")
})

test_that("dims are allowed to be zero", {
  expect_identical(rray_as_dims(c(0, 1, 0)), c(0L, 1L, 0L))
})

test_that("cannot have negative dims", {
  verify_errors({
    expect_error(rray_as_dims(-1))
    expect_error(rray_as_dims(c(1, -1)))
  })
})

test_that("cannot have missing dims", {
  verify_errors({
    expect_error(rray_as_dims(NA_integer_))
  })
})

test_that("dims cannot be length 0", {
  verify_errors({
    expect_error(rray_as_dims(integer()))
  })
})

test_that("dims are type checked", {
  verify_errors({
    expect_error(rray_as_dims("x"), class = "vctrs_error_cast_lossy")
  })
})

test_that("dims_arg is validated", {
  verify_errors({
    expect_error(rray_as_dims(1, 1))
    expect_error(rray_as_dims(1, c("x", "y")))
  })
})

test_that("rray_as_dims() produces informative errors", {
  verify_output(test_path("output/test-axes-rray-as-dims.txt"), {
    "# cannot have negative dims"
    rray_as_dims(-1)
    rray_as_dims(c(1, -1))

    "# cannot have missing dims"
    rray_as_dims(NA_integer_)

    "# dims cannot be length 0"
    rray_as_dims(integer())

    "# dims are type checked"
    rray_as_dims("x")

    "# dims_arg is validated"
    rray_as_dims(1, 1)
    rray_as_dims(1, c("x", "y"))
  })
})

test_that("rray_as_dims() `dims_arg` argument can be controlled", {
  verify_output(test_path("output/test-axes-rray-as-dims-dims-arg.txt"), {
    "# dims_arg can be changed"
    rray_as_dims(-1, ".dims")
    rray_as_dims(NA, ".dims")
    rray_as_dims(integer(), ".dims")
  })
})
