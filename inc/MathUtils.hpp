#pragma once

#include <cmath>

class MathUtils
{
    public:
        static float toRadians(float degrees)
        {
            return degrees * M_PI / 180.0f;
        }

        static float toDegrees(float radians)
        {
            return radians * 180.0f / M_PI;
        }
};