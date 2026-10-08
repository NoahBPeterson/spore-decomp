// Slice s00ac4ff0: 0x00AC5590, path relaxation on a planet. Takes an array of 0x3c-byte path points
// (position in the first three floats), copies the positions into three fixed vectors (current,
// next and original), then runs gNumPasses relaxation passes: each interior point is pulled toward
// the closest point on the segment between its neighbours (blend factor gBlend), kept within gMaxMove
// of its original position, and accepted unless the caller's validity callback (cb->fn, keyed by a
// packed cube-face direction code of the new offset) returns the "reject" sentinel. Finally every
// point is projected back onto the planet surface (cPlanetModel method 0x00b81630).
// Names are Claude-coined from usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>
#include <new>

extern void __cdecl operator_delete__(void* p);     // 0x00f47380

typedef unsigned int uint;

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec3Plain { float x, y, z; };

template <typename T, int N>
struct fixed_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    void* mAllocatorPad0;
    void* mpPoolBegin;
    void* mAllocatorPad1;
    T mBuffer[N];

    fixed_vector() {
        mpPoolBegin = mBuffer;
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + N;
    }
    ~fixed_vector() {
        if (mpBegin && mpBegin != mBuffer)
            operator_delete__(mpBegin);
    }
    void DoInsertValue(T* position, const T& value);        // 0x00ac4720 (thiscall, ret 8)
    void push_back(const T& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    T& operator[](int i) { return mpBegin[i]; }
};
typedef fixed_vector<Vector3, 256> PointVec;
extern void __cdecl SwapPointVecs(PointVec* a, PointVec* b);        // 0x00ac54d0

struct PathPoint {                 // 0x3c bytes
    Vec3Plain pos;
    float rest[12];
};
struct PathPoints {                // eastl::vector<PathPoint>
    PathPoint* mpBegin;
    PathPoint* mpEnd;
};

struct Callbacks {
    uint pad[3];
    float (__cdecl *fn)(Vector3* origPos, uint dirCode);          // +0x0c
};

struct cPlanetModel {
    Vec3Plain* Project(Vec3Plain* out, const Vector3* in);        // 0x00b81630 (thiscall, ret 8)
};
cPlanetModel* PlanetModel();                                      // 0x00b3d350

extern void __cdecl ClosestPointOnSegment(Vector3* out, const Vector3* p, const Vector3* a, const Vector3* b);   // 0x00698e00

extern int   gNumPasses;           // 0x01565bf4
extern float gBlend;               // 0x01565bf0
extern float gMaxMove;             // 0x01565bec
extern float gRejectValue;         // 0x01565ba4
extern const float kOne;           // 0x01485720
extern const float kZero;          // 0x01485378
extern const float kScale64;       // 0x0140f334

// truncating float -> int: the module's asm helper (cvttss2si from the argument's stack slot)
static __forceinline int TruncToInt(float f)
{
    __asm { cvttss2si eax, f }
}
static inline float Quant(float num, float den) { return (num / den + kOne) * kScale64; }

// @ 0x00ac5590
void __cdecl RelaxPath(PathPoints* pts, Callbacks* cb)
{
    uint n = (uint)(pts->mpEnd - pts->mpBegin);
    if (n < 3)
        return;

    PointVec orig;
    PointVec next;
    PointVec cur;

    for (int i = 0; i < (int)n; i++) {
        PathPoint* pp = pts->mpBegin + i;
        Vector3 v(pp->pos.x, pp->pos.y, pp->pos.z);
        cur.push_back(v);
        next.push_back(v);
        orig.push_back(v);
    }

    uint key = n;
    for (int pass = 0; pass < gNumPasses; pass++) {
        for (int i = 1; i < (int)n - 1; i++) {
            Vector3 p = cur[i];
            Vector3 q;
            ClosestPointOnSegment(&q, &p, &cur[i - 1], &cur[i + 1]);
            Vector3 nw((q.x - p.x) * gBlend + p.x,
                       (q.y - p.y) * gBlend + p.y,
                       (q.z - p.z) * gBlend + p.z);
            const Vector3* res = &nw;
            if (!(p.x == nw.x && p.y == nw.y && p.z == nw.z)) {
                Vector3 o = orig[i];
                float dx = nw.x - o.x;
                float dy = nw.y - o.y;
                float dz = nw.z - o.z;
                float len = sqrtf(dx * dx + (dy * dy + dz * dz));
                if (len > gMaxMove) {
                    float s = gMaxMove / len;
                    nw.y = dy * s + o.y;
                    nw.x = dx * s + o.x;
                    nw.z = dz * s + o.z;
                }
                float ax = fabsf(nw.x);
                float ay = fabsf(nw.y);
                float az = fabsf(nw.z);
                int u, v, face;
                if (az < ax || az < ay) {
                    if (ay < ax) {
                        u = TruncToInt(Quant(nw.y, nw.x));
                        v = TruncToInt(Quant(nw.z, ax));
                        face = (nw.x < kZero) ? 3 : 2;
                    } else {
                        u = TruncToInt(Quant(nw.z, nw.y));
                        v = TruncToInt(Quant(nw.x, ay));
                        face = (nw.y < kZero) ? 5 : 4;
                    }
                } else {
                    u = TruncToInt(Quant(nw.x, nw.z));
                    v = TruncToInt(Quant(nw.y, az));
                    face = (nw.z < kZero) ? 1 : 0;
                }
                if (u == 0x80) u = 0x7f;
                if (v == 0x80) v = 0x7f;
                key = (key & 0x10000) | (((v & 0xff) | (face << 9)) << 8) | (u & 0xff);
                if (cb->fn(&o, key) == gRejectValue)
                    res = &p;
            }
            next[i] = *res;
        }
        SwapPointVecs(&cur, &next);
    }

    cPlanetModel* pm = PlanetModel();
    for (int i = 0; i < (int)n; i++) {
        Vec3Plain tmp;
        Vec3Plain* r = pm->Project(&tmp, &cur[i]);
        pts->mpBegin[i].pos = *r;
    }
}
