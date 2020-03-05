#ifndef RRAY_STEPPER_H
#define RRAY_STEPPER_H

#include "location.h"
#include "internal.h"

/*
 * @param loc The flat location that matches the array location
 *   currently in `array_loc`. If `outdated` is `true`, this `loc` needs
 *   to be updated with a call to `stepper_sync()`.
 *
 * @param array_loc The current array location. This is updated through
 *   `p_array_loc` when `stepper_step()` or `stepper_reset()` is called.
 * @param p_array_loc The pointer to `array_loc`.
 *
 * @param broadcastable A raw vector storing an array of booleans. These return
 *   true of `dim[axis]` is 1, and false otherwise.
 * @param p_broadcastable A bool pointer to the underlying data stored in
 *   `broadcastable`.
 *
 * @param strides The strides for the original dimensions. These are stored as
 *   a raw vector backed by a r_ssize array.
 * @param p_strides A pointer to `strides`.
 *
 * @param dimensionality The number of original dimensions.
 *
 * @param outdated A signal for whether `stepper_loc()` needs to update the
 *   stored location or not. If we are broadcasting an axis, no updating needs
 *   to happen because we are repeatedly accessing the same value.
 */
struct rray_stepper {
  r_ssize loc;

  sexp* array_loc;
  int* p_array_loc;

  sexp* broadcastable;
  const bool* p_broadcastable;

  sexp* strides;
  const r_ssize* p_strides;

  r_ssize dimensionality;
  bool outdated;
};


#define KEEP_RRAY_STEPPER(stepper, n) do { \
  KEEP((stepper)->array_loc);              \
  KEEP((stepper)->broadcastable);          \
  KEEP((stepper)->strides);                \
  n += 3;                                  \
} while (0)


struct rray_stepper new_stepper(sexp* dims);

// -----------------------------------------------------------------------------

static inline void stepper_step(struct rray_stepper* p_stepper, r_ssize axis, r_ssize n) {
  const r_ssize dimensionality = p_stepper->dimensionality;

  if (axis >= dimensionality) {
    return;
  }

  const bool* p_broadcastable = p_stepper->p_broadcastable;

  if (p_broadcastable[axis]) {
    return;
  }

  p_stepper->p_array_loc[axis] += n;
  p_stepper->outdated = true;
}

static inline void stepper_reset(struct rray_stepper* p_stepper, r_ssize axis) {
  const r_ssize dimensionality = p_stepper->dimensionality;

  if (axis >= dimensionality) {
    return;
  }

  const bool* p_broadcastable = p_stepper->p_broadcastable;

  if (p_broadcastable[axis]) {
    return;
  }

  p_stepper->p_array_loc[axis] = 0;
  p_stepper->outdated = true;
}

static inline void stepper_sync(struct rray_stepper* p_stepper) {
  if (!p_stepper->outdated) {
    return;
  }

  const r_ssize dimensionality = p_stepper->dimensionality;
  const int* p_array_loc = p_stepper->p_array_loc;
  const r_ssize* p_strides = p_stepper->p_strides;

  p_stepper->loc = rray_array_loc_as_flat_loc(
    p_array_loc,
    p_strides,
    dimensionality
  );

  p_stepper->outdated = false;
}

// -----------------------------------------------------------------------------

/*
 * Macros to help with broadcasting functions
 *
 * The intent is to mask most of the stepping implementation details, and
 * let the user write a loop where they get to deal directly with `out`, `x`
 * and `y` objects that they have defined. Rather than indexing `p_x` and `p_y`
 * with `i`, the user will create `x_loc` and `y_loc` and pass them to
 * `STEPPER_SYNC()`, which will update them with the correct indexing value
 * at each iteration.
 */


#define STEPPER_UNARY_INIT(X_DIMS, OUT_DIMENSIONALITY, N_PROTECT)           \
  struct rray_stepper x_stepper = new_stepper(X_DIMS);                      \
  struct rray_stepper* p_x_stepper = &x_stepper;                            \
  KEEP_RRAY_STEPPER(p_x_stepper, N_PROTECT);                                \
                                                                            \
  sexp* out_array_loc = KEEP_N(r_new_int(OUT_DIMENSIONALITY), N_PROTECT);   \
  int* p_out_array_loc = r_int_deref(out_array_loc);                        \
  memset(p_out_array_loc, 0, OUT_DIMENSIONALITY * sizeof(int))


#define STEPPER_UNARY_SYNC(X_LOC) do { \
  stepper_sync(p_x_stepper);           \
  X_LOC = x_stepper.loc;               \
} while (0)


#define STEPPER_UNARY_NEXT(OUT_DIMENSIONALITY, P_OUT_DIMS) do { \
  for (r_ssize axis = 0; axis < OUT_DIMENSIONALITY; ++axis) {   \
    ++p_out_array_loc[axis];                                    \
    stepper_step(p_x_stepper, axis, 1);                         \
                                                                \
    /* Continue along axis */                                   \
    if (p_out_array_loc[axis] < P_OUT_DIMS[axis]) {             \
      break;                                                    \
    }                                                           \
                                                                \
    /* Reset this axis, then move to the next axis */           \
    p_out_array_loc[axis] = 0;                                  \
    stepper_reset(p_x_stepper, axis);                           \
  }                                                             \
} while (0)


#define STEPPER_BINARY_INIT(X_DIMS, Y_DIMS, OUT_DIMENSIONALITY, N_PROTECT)  \
  struct rray_stepper x_stepper = new_stepper(X_DIMS);                      \
  struct rray_stepper* p_x_stepper = &x_stepper;                            \
  KEEP_RRAY_STEPPER(p_x_stepper, N_PROTECT);                                \
                                                                            \
  struct rray_stepper y_stepper = new_stepper(Y_DIMS);                      \
  struct rray_stepper* p_y_stepper = &y_stepper;                            \
  KEEP_RRAY_STEPPER(p_y_stepper, N_PROTECT);                                \
                                                                            \
  sexp* out_array_loc = KEEP_N(r_new_int(OUT_DIMENSIONALITY), N_PROTECT);   \
  int* p_out_array_loc = r_int_deref(out_array_loc);                        \
  memset(p_out_array_loc, 0, OUT_DIMENSIONALITY * sizeof(int))


#define STEPPER_BINARY_SYNC(X_LOC, Y_LOC) do { \
  stepper_sync(p_x_stepper);                   \
  X_LOC = x_stepper.loc;                       \
                                               \
  stepper_sync(p_y_stepper);                   \
  Y_LOC = y_stepper.loc;                       \
} while (0)


#define STEPPER_BINARY_NEXT(OUT_DIMENSIONALITY, P_OUT_DIMS) do { \
  for (r_ssize axis = 0; axis < OUT_DIMENSIONALITY; ++axis) {    \
    ++p_out_array_loc[axis];                                     \
    stepper_step(p_x_stepper, axis, 1);                          \
    stepper_step(p_y_stepper, axis, 1);                          \
                                                                 \
    /* Continue along axis */                                    \
    if (p_out_array_loc[axis] < P_OUT_DIMS[axis]) {              \
      break;                                                     \
    }                                                            \
                                                                 \
    /* Reset this axis, then move to the next axis */            \
    p_out_array_loc[axis] = 0;                                   \
    stepper_reset(p_x_stepper, axis);                            \
    stepper_reset(p_y_stepper, axis);                            \
  }                                                              \
} while (0)

// -----------------------------------------------------------------------------

#endif
