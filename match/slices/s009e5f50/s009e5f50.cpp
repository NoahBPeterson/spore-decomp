// checkerlib 4x4 Gauss-Jordan solver (A x = B in place, partial pivoting, B = numRhs 4-vectors).
// Built /O2 /arch:SSE.  cl itself unrolls the simple loops by four.
#include <math.h>
#pragma intrinsic(fabs)

namespace checkerlib
{
class vector_4 { public: float x, y, z, w; };
class matrix_4x4
{
public:
    float el[16];
};

inline void SwapF(float& a, float& b) { float t = a; a = b; b = t; }

// @ 0x009e6040
// returns false when the matrix is singular.
bool LinearSolveInPlace(matrix_4x4& m, vector_4* bv, int numRhs)
{
    float* a = m.el;
    float* b = (float*)bv;
    const int N = 4;

    for (int k = 0; k < N; ++k)
    {
        // pivot search over column k
        float best = 1.1754944e-38f;
        int piv = N;
        for (int i = k; i < N; ++i)
        {
            float v = (float)fabs(a[i * 4 + k]);
            if (best < v) { best = v; piv = i; }
        }
        if (piv >= N)
            return false;

        if (piv != k)
        {
            for (int j = k; j < N; ++j)
                SwapF(a[piv * 4 + j], a[k * 4 + j]);
            for (int j = 0; j < numRhs; ++j)
                SwapF(b[j * 4 + piv], b[j * 4 + k]);
        }

        float p = a[k * 4 + k];
        if (fabs(p) < 1e-6)
            return false;
        float inv = 1.0f / p;

        // scale the pivot row
        for (int j = k + 1; j < N; ++j)
            a[k * 4 + j] = inv * a[k * 4 + j];
        for (int j = 0; j < numRhs; ++j)
            b[j * 4 + k] = inv * b[j * 4 + k];

        // eliminate below
        for (int r = k + 1; r < N; ++r)
        {
            float f = a[r * 4 + k];
            for (int c = k + 1; c < N; ++c)
                a[r * 4 + c] = a[r * 4 + c] - a[k * 4 + c] * f;
            for (int c = 0; c < numRhs; ++c)
                b[c * 4 + r] = b[c * 4 + r] - b[c * 4 + k] * f;
        }
    }

    // back substitution
    for (int i = N - 1; i >= 0; --i)
    {
        for (int jj = N - 1; jj > i; --jj)
        {
            for (int j = 0; j < numRhs; ++j)
                b[j * 4 + i] = b[j * 4 + i] - b[j * 4 + jj] * a[i * 4 + jj];
        }
    }
    return true;
}
} // namespace checkerlib
