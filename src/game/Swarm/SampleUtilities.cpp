// src/game/Swarm/SampleUtilities.cpp -- migrated from slice(s) s00a7c630 by tools/migrate/rewrite.py
// Object file: Swarm/SampleUtilities.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00a7c630 begin (TODO(rewrite): local stubs, replace by canonical classes)
static const float kCenterX   = 1.0f;    // 0x01677520
static const float kCenterY   = 1.0f;    // 0x01677524
struct SinCos { float sinv, cosv; };
extern const SinCos kSinCosTable[16];    // 0x01677840
// ---- items of slice s00a7c630 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern const SinCos kSinCosTable[16];    // 0x01677840

// @ 0x00a7c630
void __cdecl SquareToCircle(float* out, float a, float b)
{
  float x = b * 2.0f - kCenterY;          // -1..1
  float y = a * 2.0f - kCenterX;
  float ax = -x;                          // xmm2 = -x

  float t, r;
  if (y <= ax) {
    // left half
    if (y < x) {
      r = x;
      t = (x / y + 4.0f) * (3.14159274f * 0.25f);
      ax = -y;
    } else {
      r = x;
      t = 0.0f;
      if (x != 0.0f)
        t = (6.0f - y / x) * (3.14159274f * 0.25f);
    }
  } else if (x < y) {
    r = y;
    t = (x / y) * (3.14159274f * 0.25f);
  } else {
    r = y;
    t = (2.0f - y / x) * (3.14159274f * 0.25f);
  }

  float s = 2.54647899f * t + 12582912.0f;        // bias to integer range
  unsigned e = (unsigned&)s & 0xf;
  float cs = kSinCosTable[e].sinv;
  float sn = kSinCosTable[e].cosv;
  float q  = t - (float)((int)s + (int)0xb4c00000) * 0.392699093f;

  out[0] = (sn - ((sn * q) * 0.5f + cs) * q) * r;
  out[1] = ((sn - (cs * q) * 0.5f) * q + cs) * r;
}
