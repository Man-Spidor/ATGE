#include "Util.h"

namespace Math
{
    bool MathUtil::isEqual(const float a, const float b, const float epsilon)
    {
        return (a <= b + epsilon) && (a >= b - epsilon);
    }

    bool MathUtil::isNotEqual(const float a, const float b, const float epsilon)
    {
        return (a >= b + epsilon) || (a <= b - epsilon);
    }

    bool MathUtil::isOne(const float a, const float epsilon)
    {
        return (a <= 1.0f + epsilon) && (a >= 1.0f - epsilon);
    }

    bool MathUtil::isNonZero(const float a, const float epsilon)
    {
        return a >= epsilon || a <= epsilon;
    }

    bool MathUtil::isZero(const float a, const float epsilon)
    {
        return a <= epsilon && a >= -epsilon;
    }

    void MathUtil::clampNum(float& num, const float min, const float max)
    {
        if (num <= min)
            num = min;

        else if (num >= max)
            num = max;
    }
}
