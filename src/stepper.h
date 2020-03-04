#ifndef RRAY_STEPPER_H
#define RRAY_STEPPER_H


#include "internal.h"

/*
 * @param loc The flat location that matches the shaped location
 *   currently in `loc_dims`. If `outdated` is `true`, this `loc` needs
 *   to be updated with a call to `stepper_loc()`.
 *
 * @param loc_dims The current shaped location. This is updated through
 *   `p_loc_dims` when `stepper_step()` or `stepper_reset()` is called.
 * @param p_loc_dims The pointer to `loc_dims`.
 *
 * @param broadcastable A raw vector storing an array of booleans. These return
 *   true of `dim[axis]` is 1, and false otherwise.
 * @param p_broadcastable A bool pointer to the underlying data stored in
 *   `broadcastable`.
 *
 * @param strides The strides for the original dimensions.
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

  sexp* loc_dims;
  int* p_loc_dims;

  sexp* broadcastable;
  const bool* p_broadcastable;

  sexp* strides;
  const double* p_strides;

  r_ssize dimensionality;
  bool outdated;
};


#define KEEP_RRAY_STEPPER(stepper, n) do { \
  KEEP((stepper)->loc_dims);               \
  KEEP((stepper)->broadcastable);          \
  KEEP((stepper)->strides);                \
  n += 3;                                  \
} while (0)


struct rray_stepper new_stepper(sexp* dims);

void stepper_step(struct rray_stepper* p_stepper, r_ssize axis, r_ssize n);
void stepper_reset(struct rray_stepper* p_stepper, r_ssize axis);
void stepper_loc(struct rray_stepper* p_stepper);


#endif
