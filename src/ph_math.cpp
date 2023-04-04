#include "ph_math.h"
#include "constants.h"

double degree_to_radian(double degree) {
    return degree*PI/180.0;
}

double radian_to_degree(double radian) {
    return radian*180.0/PI;
}

Vector2f rotate_rad(const Vector2f& input, const Vector2f& origin, double angle_rad) {
    Vector2f position_wrt_origin = input - origin;
    angle_rad *= -1;
    double new_x = std::cos(angle_rad)*position_wrt_origin.x() -
        std::sin(angle_rad)*position_wrt_origin.y() + origin.x();
    double new_y = std::sin(angle_rad)*position_wrt_origin.x() +
        std::cos(angle_rad)*position_wrt_origin.y() + origin.y();
    return Vector2f{new_x, new_y};
}

Vector2f rotate(const Vector2f& input, const Vector2f& origin, double angle_deg) {
    return rotate_rad(input, origin, degree_to_radian(angle_deg));
}
