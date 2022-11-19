#pragma once
// Customized Math
#include <algorithm>

#define _USE_MATH_DEFINES
#include <math.h>

#define PI_2 (M_PI_2)
#define PI (M_PI)
#define TAU (PI * 2)


#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (b) : (a))

template <typename val_t, typename border_t>
val_t saturate(val_t val, border_t low_bound, border_t high_bound) {
    return MAX(low_bound, MIN(val, high_bound));
};
