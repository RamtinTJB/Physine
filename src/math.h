#ifndef PHYSINE_MATH_H_
#define PHYSINE_MATH_H_

#include "common.h"
#include "constants.h"

double degree_to_radian(double degree);
double radian_to_degree(double radian);
Vector2f rotate_rad(const Vector2f& input, const Vector2f& origin, double angle_rad);
Vector2f rotate(const Vector2f& input, const Vector2f& origin, double angle_deg);

#endif
