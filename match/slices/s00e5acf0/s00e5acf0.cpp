// Slice s00e5acf0 -- 0x00e5acf0: distance of an object from the cell-game bounds.
//
// The cell-game extents (0x016b3c88..0x016b3c98: the max corner summed with the min corner, times
// the half-scale constant at 0x01471064) give the centre; the object's position (+0x4c..+0x54) is
// the third vector component of each axis.  The length goes through x87, the object's radius
// (+0x58) is subtracted and the result clamped at zero with the SSE max idiom.  If the distance is
// not above the constant at 0x014851ec the result is 1.0; otherwise the object is re-aligned
// (0x00e513d0) with the factor at 0x014007f4 and the result is 0.0.
//
// Local stand-in layout (retail offsets).  Not byte-exact yet: see nonmatching.txt.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

typedef unsigned char uint8_t;

extern const float gbbX0, gbbY0, gbbZ0;         // 0x016b3c88, 0x016b3c8c, 0x016b3c90
extern const float gbbX1, gbbY1, gbbZ1;         // 0x016b3c94, 0x016b3c98, 0x016b3c9c
extern const float kHalf;                       // 0x01471064
extern const float kNearLimit;                  // 0x014851ec
extern const float kFarAlign;                   // 0x014007f4

// The object being measured.
struct Bounded {
    uint8_t pad00[0x4c];
    float   mX;                 // +0x4c
    float   mY;                 // +0x50
    float   mZ;                 // +0x54
    float   mRadius;            // +0x58
};

// Re-aligns the object against the cell floor with the given factor. 0x00e513d0
void AlignToFloor(float* self, float a, float b, float c, float d, float factor);

// @ 0x00e5acf0
float DistanceToBounds(Bounded* self)
{
    // Centre of the cell-game extents and the offset from it (SSE).
    float cx = gbbX1 + gbbX0;
    float cy = gbbY1 + gbbY0;
    float cz = gbbZ1 + gbbZ0;

    float fx = cx * kHalf;
    float fy = cy * kHalf - self->mY;
    float fz = cz * kHalf - self->mZ;

    // Length and radius offset in x87; the clamp at zero is the SSE max idiom.
    float x2 = fx * fx;
    float y2 = fy * fy;
    float z2 = fz * fz;
    float sq = x2 + y2 + z2;

    float len = sqrt(sq);
    float d = len - self->mRadius;
    if (d < 0.0f)
        d = 0.0f;

    if (!(d > kNearLimit))
        return 1.0f;

    AlignToFloor(&self->mX, fx, d, 0.0f, 0.0f, kFarAlign);
    return 0.0f;
}
