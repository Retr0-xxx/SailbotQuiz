#include "stdbool.h"
#include "standard_calc.h"

/**
 * @brief Bounds the provided angle between [-180, 180) degrees.
 *
 * e.g.)
 *      bound_to_180(135) = 135.0
 *      bound_to_180(200) = -160.0
 *
 * @param angle: The input angle in degrees.
 *
 * @return float: The bounded angle in degrees.
 */
float bound_to_180(float angle) {
    // bring into range [0, 360)
    while (angle < 0.0f) {
        angle += 360.0f;
    }
    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    // shift into [-180, 180)
    if (angle >= 180.0f) {
        angle -= 360.0f;
    }

    return angle;
}

/**
 * @brief Determines whether an angle is between two other angles
 *
 *  e.g.)
 *      is_angle_between(0, 45, 90) = true
 *      is_angle_between(45, 90, 270) = false
 * 
 * @param first_angle:  The first bounding angle in degrees.
 * @param middle_angle: The angle in question in degrees.
 * @param second_angle: The second bounding angle in degrees.
 * @return bool: TRUE when `middle_angle` is not in the reflex angle of `first_angle` and `second_angle`, FALSE otherwise
 */
bool is_angle_between(float first_angle, float middle_angle, float second_angle) {
    // normalize relative to first_angle
    float a = bound_to_180(second_angle - first_angle);
    float b = bound_to_180(middle_angle - first_angle);

    // if second_angle lies “ahead” in the positive direction,
    // then middle_angle must also be ahead but not beyond
    if (a > 0) {
        return (b >= 0 && b <= a);
    } 
    // otherwise, second_angle is “behind” (negative direction)
    else {
        return (b <= 0 && b >= a);
    }
}
