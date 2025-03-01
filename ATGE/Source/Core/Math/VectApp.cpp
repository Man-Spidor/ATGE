#include "VectApp.h"

namespace Math
{
    void VectApp::Lerp(Vector4& out, const Vector4& a, const Vector4& b, const float t)
    {
        // out = (1 - t) * a + t * b
        __m128 t_v = _mm_set1_ps(t);          // Load t into a SIMD register
        __m128 one_minus_t = _mm_sub_ps(_mm_set1_ps(1.0f), t_v);  // (1 - t)

        // Calculate (1 - t) * a
        __m128 a_scaled = _mm_mul_ps(one_minus_t, a.vm);

        // Calculate t * b
        __m128 b_scaled = _mm_mul_ps(t_v, b.vm);

        // Add the results: out = (1 - t) * a + t * b
        out.vm = _mm_add_ps(a_scaled, b_scaled);
    }

    void VectApp::LerpArray(Vector4* out, const Vector4* a, const Vector4* b, const float t, const int numVects)
    {
        // SIMD version for efficiency
        __m128 t_v = _mm_set1_ps(t);          // Load t into a SIMD register
        __m128 one_minus_t = _mm_sub_ps(_mm_set1_ps(1.0f), t_v);  // (1 - t)

        for (int i = 0; i < numVects; i++) {
            // Calculate (1 - t) * a[i]
            __m128 a_scaled = _mm_mul_ps(one_minus_t, a[i].vm);

            // Calculate t * b[i]
            __m128 b_scaled = _mm_mul_ps(t_v, b[i].vm);

            // Add the results: out[i] = (1 - t) * a[i] + t * b[i]
            out[i].vm = _mm_add_ps(a_scaled, b_scaled);
        }
    }

    void VectApp::SumArray(Vector4& out, const Vector4* array, const int numVects)
    {
        for (int i = 0; i < numVects; i++) {
            out += array[i];
        }
    }

    void VectApp::GetRandPoint(Vector4& out, const Vector4& anchor, int randOffset)
    {
        float sign = 1.0f;
        if (rand() % 2)
            sign = -1.0f;

        out.X() = anchor.X() + (sign * (float)(rand() % randOffset));

        sign = 1.0f;
        if (rand() % 2)
            sign = -1.0f;

        out.Y() = anchor.Y() + (sign * (float)(rand() % randOffset));

        sign = 1.0f;
        if (rand() % 2)
            sign = -1.0f;

        out.Z() = anchor.Z() + (sign * (float)(rand() % randOffset));
    }
}
