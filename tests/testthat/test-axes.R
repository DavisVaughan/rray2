test_that("axes are cast to integer", {
  expect_type(rray_as_axes(c(1, 2), 2), "integer")
})

test_that("out of order axes are allowed", {
  expect_identical(rray_as_axes(c(2, 1), 2), c(2L, 1L))
})

# TODO: use `vec_unique()` and check lengths
test_that("duplicate axes are checked for", {
  expect_failure({
    expect_error(rray_as_axes(c(1, 1), 1))
  })
})

test_that("cannot select negative axes", {
  verify_errors({
    expect_error(rray_as_axes(-1, 1))
    expect_error(rray_as_axes(c(1, -1), 1))
  })
})

test_that("cannot select `NA` axes", {
  verify_errors({
    expect_error(rray_as_axes(NA_integer_, 1))
  })
})

test_that("cannot select axes past the dimensionality", {
  verify_errors({
    expect_error(rray_as_axes(3, 2))
  })
})

test_that("rray_as_axes() produces informative errors", {
  verify_output(test_path("output/test-axes-rray-as-axes.txt"), {
    "# cannot select negative axes"
    rray_as_axes(-1, 1)
    rray_as_axes(c(1, -1), 1)

    "# cannot select `NA` axes"
    rray_as_axes(NA_integer_, 1)

    "# cannot select axes past the dimensionality"
    rray_as_axes(3, 2)
  })
})
