#pragma once
#include "Vector.h"
#include <cmath>

namespace pba
{
    inline float getRangeLimiter(float dist, float R, float R_amp)
    {
        const float eps = 1.0e-8f;

        if (dist <= R)
        {
            return 1.0f;
        }

        if (R_amp <= eps)
        {
            return 0.0f;
        }

        if (dist >= R + R_amp)
        {
            return 0.0f;
        }

        float r_ab = 1.0f - (dist - R) / R_amp;

        if (r_ab < 0.0f)
        {
            return 0.0f;
        }
        if (r_ab > 1.0f)
        {
            return 1.0f;
        }
        return r_ab;
    }

    inline float getFOVLimiter(const Vector &dx_ab, const Vector &v_a, float cosTheta, float cosTheta_amp)
    {
        const float eps = 1.0e-8f;

        const float dx_mag = dx_ab.magnitude();
        const float v_mag = v_a.magnitude();

        if (dx_mag < eps || v_mag < eps)
        {
            return 1.0f;
        }

        float cosTheta_ab = (dx_ab * v_a) / (dx_mag * v_mag);

        if (cosTheta_ab > 1.0f)
        {
            cosTheta_ab = 1.0f;
        }
        else if (cosTheta_ab < -1.0f)
        {
            cosTheta_ab = -1.0f;
        }

        if (cosTheta_ab >= cosTheta)
        {
            return 1.0f;
        }
        if (cosTheta_ab <= cosTheta_amp)
        {
            return 0.0f;
        }

        const float denom = cosTheta - cosTheta_amp;
        if (std::fabs(denom) < eps)
        {
            return (cosTheta_ab >= cosTheta) ? 1.0f : 0.0f;
        }

        float f_ab = 1.0f - (cosTheta - cosTheta_ab) / denom;

        if (f_ab < 0.0f)
        {
            return 0.0f;
        }
        if (f_ab > 1.0f)
        {
            return 1.0f;
        }
        return f_ab;
    }
}