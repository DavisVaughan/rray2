library(bench)
library(rray2)

# ------------------------------------------------------------------------------
# Non-broadcasting addition

x_1x5000 <- matrix(1:5000 + 0L, nrow = 1)

mark(
  rray_add(x_1x5000, x_1x5000),
  iterations = 10000
)

x_5000x1 <- matrix(1:5000 + 0L, ncol = 1)

mark(
  rray_add(x_5000x1, x_5000x1),
  iterations = 10000
)

# ------------------------------------------------------------------------------
# Broadcasting addition

x_1x500 <- matrix(1:500 + 0L, nrow = 1)
x_500x1 <- matrix(1:500 + 0L, ncol = 1)

mark(
  rray_add(x_1x500, x_500x1),
  iterations = 2000
)
