// Slice s00e855e0 (0x00e855e0..0x00e85dbb) -- shape-matching covariance helpers.
//
//   0x00e855e0  void FUN_00e855e0(float* a, int n)                       (1144 bytes)
//       In-place inverse of an n x n row-major float matrix, Gauss-Jordan style.
//       For pivot r: d = a[r][r]; if |d| < 1e-8 the pivot is defective and the
//       r-th row and column are cleared, otherwise
//           inv       = 1/d
//           a[r][r]   = inv
//           a[r][c]   = -(a[r][c] * inv)     for c != r   (row pass)
//           a[k][r]   =  a[k][r] * inv       for k != r   (column pass)
//           a[i][j]  += (a[r][j] / inv) * a[i][r]   for i,j != r
//       The row pass negates so the rank-1 update can be an addition.
//
//   0x00e85a60  void FUN_00e85a60(int n, const Vector3* pts, const float* masses,
//                                 Vector3* centred, Vector3* centre, float* aqq)
//                                                                         (860 bytes)
//       One covariance step over n particles:
//         1. centre = mass-weighted centre of mass of pts          (0x00e853c0)
//         2. centred[i] = pts[i] - centre
//         3. zero the 0x144-byte aqq workspace                     (0x011e073e)
//         4. aqq += sum_i m_i * q_i q_i^T  (symmetric 3x3, row-major)
//         5. invert the 3x3 block in place                          (0x00e855e0, n=3)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (no /EHsc, /GS-)

#include "types.h"
#include <math.h>

struct Vector3 {
    float x, y, z;
};

// ---------------------------------------------------------------------------------------------
// external helpers
// ---------------------------------------------------------------------------------------------
// mass-weighted centre of mass of n particles (0x00e853c0)
void __cdecl ComputeCenterOfMass(int n, const Vector3* positions, const float* masses,
                                 Vector3* center);
// block fill used for the 0x144-byte covariance workspace (0x011e073e, memset-like)
void* __cdecl FUN_011e073e(void* dst, int value, unsigned size);

// =============================================================================================
// @ 0x00e855e0
//
//   void FUN_00e855e0(float* a, int n)
//
// `a` is n rows of n floats (row-major), i.e. a[i*n + j] is element (i, j). The matrix is
// inverted in place; a defective pivot (|a[r][r]| < 1e-8) clears row r and column r.
// =============================================================================================
// @ 0x00e855e0
void FUN_00e855e0(float* a, int n)
{
    int last = n - 1;
    int r = 0;
    if (last < 0) {
        last = 0;
        r = n - 1;
    }
    if (r > last)
        return;

    for (; r <= last; ++r) {
        const float d = a[r * n + r];

        if (fabsf(d) < 1e-8f) {
            // defective pivot: clear the r-th row and the r-th column
            for (int k = 0; k < n; ++k) {
                a[k * n + r] = 0.0f;   // column r
                a[r * n + k] = 0.0f;   // row r
            }
        } else {
            const float inv = 1.0f / d;
            a[r * n + r] = inv;

            // row pass: negate the scaled off-diagonal elements of row r
            for (int c = 0; c < n; ++c) {
                if (c != r)
                    a[r * n + c] = -(a[r * n + c] * inv);
            }

            // column pass: scale the off-diagonal elements of column r
            for (int k = 0; k < n; ++k) {
                if (k != r)
                    a[k * n + r] = a[k * n + r] * inv;
            }

            // rank-1 update of the remaining submatrix
            for (int j = 0; j < n; ++j) {
                if (j == r)
                    continue;
                const float f = a[r * n + j] / inv;
                for (int i = 0; i < n; ++i) {
                    if (i != r)
                        a[i * n + j] += f * a[i * n + r];
                }
            }
        }
    }
}

// =============================================================================================
// @ 0x00e85a60
//
//   void FUN_00e85a60(int n, const Vector3* pts, const float* masses,
//                     Vector3* centred, Vector3* centre, float* aqq)
//
// aqq is a workspace of 0x144 bytes (81 floats); only the leading symmetric 3x3 block
// (aqq[0]..aqq[8]) is filled and inverted here.
// =============================================================================================
// @ 0x00e85a60
void FUN_00e85a60(int n, const Vector3* pts, const float* masses,
                  Vector3* centred, Vector3* centre, float* aqq)
{
    ComputeCenterOfMass(n, pts, masses, centre);

    // shift the particles into centre-relative coordinates
    for (int i = 0; i < n; ++i) {
        centred[i].x = pts[i].x - centre->x;
        centred[i].y = pts[i].y - centre->y;
        centred[i].z = pts[i].z - centre->z;
    }

    FUN_011e073e(aqq, 0, 0x144);

    // aqq = sum_i m_i * q_i q_i^T for the centred particles, laid out row-major as
    //   [ xx xy xz ]
    //   [ xy yy yz ]
    //   [ xz yz zz ]
    for (int i = 0; i < n; ++i) {
        const float x = centred[i].x;
        const float y = centred[i].y;
        const float z = centred[i].z;
        const float w = masses[i];

        aqq[0] += x * x * w;
        aqq[1] += x * y * w;
        aqq[2] += x * z * w;
        aqq[3] += x * y * w;
        aqq[4] += y * y * w;
        aqq[5] += y * z * w;
        aqq[6] += x * z * w;
        aqq[7] += y * z * w;
        aqq[8] += z * z * w;
    }

    FUN_00e855e0(aqq, 3);
}
