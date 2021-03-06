% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/dimensions.R
\name{rray_dims}
\alias{rray_dims}
\alias{rray_dims_common}
\title{Dimensions}
\usage{
rray_dims(x)

rray_dims_common(..., .dims = NULL, .absent = 0L)
}
\arguments{
\item{x}{A vector}

\item{...}{Vectors to find common dimensions for}

\item{.dims}{If \code{NULL}, the common dimensions are computed solely from
\code{...}. Otherwise, an integer vector of dimensions to start the common
dimension computation from.}

\item{.absent}{The dimensions to return when \code{...} is empty, or when all
inputs are \code{NULL}.}
}
\value{
\itemize{
\item \code{rray_dims()}: An integer vector with a size equal to the dimensionality
of \code{x} holding the dimensions.
\item \code{rray_dims_common()}: An integer vector with a size equal to the
maximum dimensionality of the inputs holding the common dimensions.
}
}
\description{
\itemize{
\item \code{rray_dims()} computes the dimensions of a vector.
\item \code{rray_dims_common()} computes the common dimensions of multiple vectors,
using the rules of broadcasting.
}
}
\details{
\code{rray_dims()} is similar to \code{\link[=dim]{dim()}}, but errors on scalar objects and never
returns \code{NULL}. The dimensions of a bare vector, such as \code{1:5}, are its
length, and the dimensions of \code{NULL} are \code{0}.
}
\section{Invariants}{

\itemize{
\item \code{vec_size(rray_dims(x)) == rray_dimensionality(x)}
\item \code{vec_ptype(rray_dims(x)) == integer()}
\item \code{vec_size(rray_dims_common(...)) == max(map(list(...), rray_dimensionality))}
\item \code{vec_ptype(rray_dims_common(...)) == integer()}
}
}

\examples{
rray_dims(1)
rray_dims(array(1:6, dim = c(2, 3)))

rray_dims(NULL)

rray_dims_common(1, 1:2)
rray_dims_common(
  matrix(1:5, ncol = 5),
  matrix(1:5, nrow = 5)
)

# `.dims` starts the computation, but can still be broadcast
# against the dimensions of the input
rray_dims_common(matrix(1:5), .dims = c(1L, 5L))

try(rray_dims(mean))
}
