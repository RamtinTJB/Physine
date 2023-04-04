#include "math.h"

double degree_to_radian(double degree) {
    return degree*PI/180;
}

double radian_to_degree(double radian) {
    return radian*180/PI;
}

Vector2f rotate_rad(const Vector2f& input, const Vector2f& origin, double angle_rad) {
    return Vector2f();
}

Vector2f rotate(const Vector2f& input, const Vector2f& origin, double angle_deg) {
    return rotate_rad(input, origin, degree_to_radian(angle_deg));
}
