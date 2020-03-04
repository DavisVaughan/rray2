rray_broadcast <- function(x, dims) {
  .Call(export_rray_broadcast, x, dims)
}
