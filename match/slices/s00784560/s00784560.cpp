// Slice s00784560: SH (spherical harmonics) basis evaluation (0x784560), /O2 /MD /Gy /EHsc /TP /arch:SSE.
// Evaluates the real SH basis for unit direction `dir` up to `order` bands (1..8) using the
// band recurrence, and multiplies each basis value by that band's coefficient vec4
// (coeffs[l]); writes order*order vec4s to out. The g_xxxxxxxx floats are runtime-initialized
// constants (sqrt ratios) in the original image; bands 5+ use sqrt(double) literals.
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

extern float g_01634104, g_016340dc, g_01634078, g_016340cc, g_016341e0, g_016341b0, g_01634150,
    g_016340b0, g_016340fc, g_0163409c, g_016341dc, g_016340d4, g_01634130, g_016340e8, g_01634074,
    g_016340ec, g_016340f8, g_0163410c, g_01634168, g_01634134, g_016340e4, g_016340a8, g_01634064,
    g_0163405c, g_0163407c;

// @ 0x00784560
void SHEvalBands(const float* param_1, int param_2, const __m128* c, __m128* out)
{
  float A[16];
  float B[16];
  float x, y, z;
  __m128 cv;
  int oi;
  out[0] = c[0];
  if (1 < param_2) {
    y = param_1[1];
    z = param_1[2];
    x = param_1[0];
    cv = c[1];
    out[1] = _mm_mul_ps(_mm_set1_ps(y), cv);
    out[2] = _mm_mul_ps(_mm_set1_ps(z), cv);
    out[3] = _mm_mul_ps(_mm_set1_ps(x), cv);
    if (2 < param_2) {
      A[0] = ((x * y) * 2.0) * g_01634104;
      A[1] = ((z * y) * 2.0) * g_01634104;
      A[2] = z * z - (y * y + x * x) * g_016340dc;
      oi = 4;
      A[3] = ((x * z) * 2.0) * g_01634104;
      A[4] = (x * x - y * y) * g_01634104;
      cv = c[2];
      for (int i = 0; i < 5; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(A[i]), cv);
      if (3 < param_2) {
        B[0] = (A[4] * y + A[0] * x) * g_01634078;
        B[1] = ((A[1] * x + A[3] * y) + A[0] * z) *
                      g_016340cc;
        B[2] = ((g_016341e0 * A[1]) * z -
                      (A[0] * x - A[4] * y) * g_016341b0) +
                      (g_01634150 * A[2]) * y;
        B[3] = A[2] * z -
                      (A[1] * y + A[3] * x) * g_016340b0;
        B[4] = ((g_01634150 * A[2]) * x -
                      (A[0] * y + A[4] * x) * g_016341b0) +
                      (g_016341e0 * A[3]) * z;
        B[5] = ((A[3] * x - A[1] * y) + A[4] * z) *
                      g_016340cc;
        B[6] = (A[4] * x - A[0] * y) * g_01634078;
        oi = 9;
        cv = c[3];
        for (int i = 0; i < 7; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(B[i]), cv);
        if (4 < param_2) {
          A[0] = (B[6] * y + B[0] * x) * g_016340fc;
          A[1] = (B[5] * y + B[1] * x) * g_0163409c +
                         (g_016341dc * B[0]) * z;
          A[2] = ((B[2] * x + B[4] * y) * g_016340d4 -
                         (B[0] * x - B[6] * y) * g_01634130) +
                         (g_01634104 * B[1]) * z;
          A[3] = ((g_016340e8 * B[2]) * z -
                         (B[1] * x - B[5] * y) * g_01634074) +
                         (g_016340ec * B[3]) * y;
          A[4] = B[3] * z -
                         (B[2] * y + B[4] * x) * g_016340f8;
          A[5] = ((g_016340ec * B[3]) * x -
                         (B[1] * y + B[5] * x) * g_01634074) +
                         (g_016340e8 * B[4]) * z;
          oi = 16;
          A[6] = ((B[4] * x - B[2] * y) * g_016340d4 -
                         (B[0] * y + B[6] * x) * g_01634130) +
                         (g_01634104 * B[5]) * z;
          A[7] = (B[5] * x - B[1] * y) * g_0163409c +
                         (g_016341dc * B[6]) * z;
          cv = c[4];
          A[8] = (B[6] * x - B[0] * y) * g_016340fc;
          for (int i = 0; i < 9; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(A[i]), cv);
          if (5 < param_2) {
            oi = 25;
            B[0] = (A[8] * y + A[0] * x) * sqrt(9.0/10.0);
            B[1] = (z * A[0]) * sqrt(9.0/25.0) +
                          (A[7] * y + A[1] * x) * g_01634134;
            B[2] = (A[1] * z) * sqrt(16.0/25.0) +
                          ((A[6] * y + A[2] * x) * g_0163410c -
                          (A[0] * x - A[8] * y) * g_01634168);
            B[3] = (A[2] * z) * sqrt(21.0/25.0) +
                          ((A[5] * y + A[3] * x) * g_016340e4 -
                          (A[1] * x - A[7] * y) * g_016340a8);
            B[4] = (A[3] * z) * sqrt(24.0/25.0) +
                          ((A[4] * g_01634064) * y -
                          (A[2] * x - A[6] * y) * g_0163405c);
            B[5] = A[4] * z -
                          (A[3] * y + A[5] * x) * sqrt(2.0/5.0);
            B[6] = (A[5] * z) * sqrt(24.0/25.0) +
                          ((A[4] * g_01634064) * x -
                          (A[2] * y + A[6] * x) * g_0163405c);
            B[7] = (A[6] * z) * sqrt(21.0/25.0) +
                          ((A[5] * x - A[3] * y) * g_016340e4 -
                          (A[1] * y + A[7] * x) * g_016340a8);
            B[8] = (A[7] * z) * sqrt(16.0/25.0) +
                          ((A[6] * x - A[2] * y) * g_0163410c -
                          (A[0] * y + A[8] * x) * g_01634168);
            cv = c[5];
            B[9] = (A[8] * z) * sqrt(9.0/25.0) +
                          (A[7] * x - A[1] * y) * g_01634134;
            B[10] = (A[8] * x - A[0] * y) * sqrt(9.0/10.0);
            for (int i = 0; i < 11; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(B[i]), cv);
            if (param_2 < 7) {
              return;
            }
            oi = 36;
            A[0] = (B[0] * x + B[10] * y) * sqrt(11.0/12.0);
            A[1] = (B[0] * z) * sqrt(11.0/36.0) +
                           (B[9] * y + B[1] * x) * sqrt(55.0/72.0);
            A[2] = ((B[1] * g_016340cc) * z +
                           (B[8] * y + B[2] * x) * g_016340ec) -
                           (B[0] * x - B[10] * y) * sqrt(1.0/72.0);
            A[3] = (B[2] * g_01634104) * z +
                           ((B[3] * x + B[7] * y) * sqrt(1.0/2.0) -
                           (B[1] * x - B[9] * y) * sqrt(1.0/24.0));
            A[4] = (B[3] * g_016341e0) * z +
                           ((B[6] * y + B[4] * x) * sqrt(7.0/18.0) -
                           (B[2] * x - B[8] * y) * g_0163407c);
            A[5] = y * (B[5] * sqrt(7.0/12.0)) +
                           ((B[4] * z) * sqrt(35.0/36.0) -
                           (B[3] * x - B[7] * y) * sqrt(5.0/36.0));
            A[6] = B[5] * z -
                           (B[4] * y + B[6] * x) * sqrt(5.0/12.0);
            A[7] = (B[6] * z) * sqrt(35.0/36.0) +
                           (x * (B[5] * sqrt(7.0/12.0)) -
                           (B[3] * y + B[7] * x) * sqrt(5.0/36.0));
            cv = c[6];
            A[8] = (B[7] * g_016341e0) * z +
                           ((B[6] * x - B[4] * y) * sqrt(7.0/18.0) -
                           (B[2] * y + B[8] * x) * g_0163407c);
            A[9] = (B[8] * g_01634104) * z +
                           ((B[7] * x - B[3] * y) * sqrt(1.0/2.0) -
                           (B[1] * y + B[9] * x) * sqrt(1.0/24.0));
            A[10] =
                 ((B[9] * g_016340cc) * z +
                 (B[8] * x - B[2] * y) * g_016340ec) -
                 (B[0] * y + B[10] * x) * sqrt(1.0/72.0);
            A[0xb] =
                 (B[10] * z) * sqrt(11.0/36.0) +
                 (B[9] * x - B[1] * y) * sqrt(55.0/72.0);
            A[0xc] = (B[10] * x - B[0] * y) * sqrt(11.0/12.0);
            for (int i = 0; i < 13; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(A[i]), cv);
            if (7 < param_2) {
              oi = 49;
              B[0] = (A[0] * x + A[0xc] * y) * sqrt(13.0/14.0);
              B[1] = (A[0] * z) * sqrt(13.0/49.0) +
                            (A[1] * x + A[0xb] * y) * sqrt(39.0/49.0);
              B[2] = (A[1] * z) * sqrt(24.0/49.0) +
                            ((A[2] * x + A[10] * y) * sqrt(33.0/49.0) -
                            (A[0] * x - A[0xc] * y) * sqrt(1.0/98.0));
              B[3] = (A[2] * z) * sqrt(33.0/49.0) +
                            ((A[3] * x + A[9] * y) * sqrt(55.0/98.0) -
                            (A[1] * x - A[0xb] * y) * sqrt(3.0/98.0));
              B[4] = (A[3] * z) * sqrt(40.0/49.0) +
                            ((A[4] * x + A[8] * y) * sqrt(45.0/98.0) -
                            (A[2] * x - A[10] * y) * sqrt(3.0/49.0));
              B[5] = (A[4] * z) * sqrt(45.0/49.0) +
                            ((A[7] * y + A[5] * x) * sqrt(18.0/49.0) -
                            (A[3] * x - A[9] * y) * sqrt(5.0/49.0));
              B[6] = y * (A[6] * sqrt(4.0/7.0)) +
                            ((A[5] * z) * sqrt(48.0/49.0) -
                            (A[4] * x - A[8] * y) * sqrt(15.0/98.0));
              B[7] = A[6] * z -
                            (A[5] * y + A[7] * x) * sqrt(3.0/7.0);
              B[8] = (A[7] * z) * sqrt(48.0/49.0) +
                            (x * (A[6] * sqrt(4.0/7.0)) -
                            (A[4] * y + A[8] * x) * sqrt(15.0/98.0));
              B[9] = (z * A[8]) * sqrt(45.0/49.0) +
                            ((A[7] * x - A[5] * y) * sqrt(18.0/49.0) -
                            (A[3] * y + A[9] * x) * sqrt(5.0/49.0));
              B[10] = (A[9] * z) * sqrt(40.0/49.0) +
                             ((A[8] * x - A[4] * y) * sqrt(45.0/98.0) -
                             (A[2] * y + A[10] * x) * sqrt(3.0/49.0));
              cv = c[7];
              B[0xb] =
                   (z * A[10]) * sqrt(33.0/49.0) +
                   ((A[9] * x - A[3] * y) * sqrt(55.0/98.0) -
                   (A[1] * y + A[0xb] * x) * sqrt(3.0/98.0));
              B[0xc] =
                   (A[0xb] * z) * sqrt(24.0/49.0) +
                   ((A[10] * x - A[2] * y) * sqrt(33.0/49.0) -
                   (A[0] * y + A[0xc] * x) * sqrt(1.0/98.0));
              B[0xd] =
                   (A[0xc] * z) * sqrt(13.0/49.0) +
                   (A[0xb] * x - A[1] * y) * sqrt(39.0/49.0);
              B[0xe] = (A[0xc] * x - A[0] * y) * sqrt(13.0/14.0);
              for (int i = 0; i < 15; i++)
 out[oi + i] = _mm_mul_ps(_mm_set1_ps(B[i]), cv);
              return;
            }
          }
        }
      }
    }
  }


}
