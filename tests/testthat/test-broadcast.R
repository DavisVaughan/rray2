test_that("broadcasting works with implicit dimensionality expansion", {
  expect_identical(
    rray_broadcast(1L, c(1, 2)),
    matrix(1L, nrow = 1, ncol = 2)
  )
})
