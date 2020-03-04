test_that("number of elements in NULL is `0` to match rray_dims() returning `0`", {
  # This invariant should always hold
  # prod(rray_dims(x)) == rray_elements(x)
  expect_identical(rray_elements(NULL), 0)
  expect_identical(rray_elements(NULL), rray_elements_from_dims(rray_dims(NULL)))
})
