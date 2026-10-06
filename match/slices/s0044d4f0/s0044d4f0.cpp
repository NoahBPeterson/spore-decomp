// Slice s0044d4f0: /Od /Ob1 bounds/vector helpers.
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"
#include <math.h>

struct V3 { float x, y, z; V3& operator=(const V3& o) { x = o.x; y = o.y; z = o.z; return *this; } };
// Second vector flavour: float copies go through movss (SSE) in the original.
struct Vec3 {
    float x, y, z;
    float& operator[](int i) { return ((float*)this)[i]; }
    Vec3() {}
    Vec3(float a, float b, float c) { x = a; y = b; z = c; }
    Vec3& operator=(const Vec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; Mat3() {} };
// POD flavour (plain aggregate copy): used for the unit direction vectors.
struct VecC {
    float x, y, z;
    VecC() {}
    VecC(float a, float b, float c) { x = a; y = b; z = c; }
    float& operator[](int i) { return ((float*)this)[i]; }
};
VecC Normalize(const VecC& v);                  // 0x00436ce0
float Dot3(const VecC& a, const VecC& b);       // 0x00455cc0
V3 operator*(const V3& v, const Mat3& m);   // 0x0041daf0
V3& operator*=(V3& v, const float& s);      // 0x0041dba0
V3& operator+=(V3& v, const V3& o);         // 0x0041ddb0
struct Raw3 { int a, b, c; };
Vec3 operator*(const Vec3& v, const Mat3& m);   // 0x0041daf0
VecC Normalize(const Vec3& v);                  // 0x00436ce0
Vec3 operator-(const Vec3& v);                  // 0x00422020 (Vector3_Negate)
float Dot3(const Vec3& a, const Vec3& b);       // 0x00455cc0
struct V4;
V4 PlaneFromPointNormal(const Vec3& p, const Vec3& n);   // 0x0044e510
float PlaneEval(const V4& plane, const Vec3& p);         // 0x0044e5d0
bool IntersectRayPlane(const Vec3& o, const Vec3& d, const V4& plane, float* t);   // 0x0044e640
extern Vec3 g_Axis;                             // 0x015d23a8
Vec3 operator-(const Vec3& a, const Vec3& b);   // 0x0041db10
Vec3 operator+(const Vec3& a, const Vec3& b);   // 0x0041dc10
Vec3 operator*(const Vec3& v, const float& s);  // 0x0041dca0
Mat3 Transposed(const Mat3& m);                 // 0x0041ded0
Vec3& operator*=(Vec3& v, const float& s);      // 0x0041dba0
Vec3& operator+=(Vec3& v, const Vec3& o);       // 0x0041ddb0
// Clamp to [lo, hi]. The original builds this from SSE max/min scalar ops (maxss/minss), which
// cl only emits here through inline asm, so it is written portably.
inline float Clamp(float v, float lo, float hi) { v = v > lo ? v : lo; v = v < hi ? v : hi; return v; }
inline float Acos(float v) { float r = acosf(v); return r; }
inline float Abs(float f) { return fabsf(f); }
extern float g_TwoPi;                           // 0x015d2470 (runtime constant)
Vec3 Cross(const Vec3& a, const Vec3& b);       // 0x0044e460


// @ 0x0044e410  (byte-exact)
struct V4 {
    float x, y, z, w;
    V4() {}
    V4(float a, float b, float c, float d);
};
V4::V4(float a, float b, float c, float d)
{
    x = a;
    y = b;
    z = c;
    w = d;
}

struct Holder {
    void* a;    // +0
    void* b;    // +4
    void* GetB() { return b; }
    void Compute(Vec3* pos, Mat3* rot);   // 0x004e95e0
};

struct Bounds {
    V3 mn;      // +0x00
    V3 mx;      // +0x0c
    Holder* m18;    // +0x18
    bool m1c;   // +0x1c
    Bounds();                       // 0x00433960
    Bounds(const Bounds& o);        // same body as operator= (0x0044d960 shape)
    ~Bounds();                      // 0x004ae250
    Bounds& operator=(const Bounds& o);
};

// @ 0x0044d960  (byte-exact)
Bounds& Bounds::operator=(const Bounds& o)
{
    mn = o.mn;
    mx = o.mx;
    m18 = o.m18;
    m1c = o.m1c;
    return *this;
}
Bounds::Bounds(const Bounds& o)
{
    mn = o.mn;
    mx = o.mx;
    m18 = o.m18;
    m1c = o.m1c;
}

// Transform: scale/rotation/translation (flags bit 1 = has rotation)
struct Xform {
    uint16_t flags;     // +0x00
    uint16_t count;     // +0x02
    V3 pos;             // +0x04
    float scale;        // +0x10
    Mat3 rot;           // +0x14
    void Apply(V3* v);
};

// @ 0x0044d4f0
void Xform::Apply(V3* v)
{
    if (flags & 2)
        *v = *v * rot;
    *v *= scale;
    *v += pos;
}

struct BVec {
    Bounds* mBeg;   // +0x234
    Bounds* mEnd;   // +0x238
    int size() { return mEnd - mBeg; }
    Bounds& at(int i) { return mBeg[i]; }
};

struct Pose {
    char pad[0xc];
    Vec3 pos;           // +0x0c
    float pad18;
    Mat3 rot;           // +0x1c
};

struct BBox { Vec3 mn, mx; };

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Blk {
    char pad0[0x10];
    Pose* mXf;          // +0x10
    char pad1[0x48 - 0x14];
    Vec3 mPos;          // +0x48
    char pad2[0x60 - 0x54];
    Mat3 mRot;          // +0x60
    char pad3[0x234 - 0x84];
    BVec mVec;          // +0x234

    Pose* GetXf() { return mXf; }
    Bounds& Elem(int i) { return mVec.mBeg[i]; }
    Vec3& MaxPt(int i) { return *(Vec3*)&mVec.mBeg[i].mx; }
    Vec3& MinPt(int i) { return *(Vec3*)&mVec.mBeg[i].mn; }
    int Count();                                    // 0x0044e800
    void GetBBox(BBox* out, int a, int b, int c);   // 0x0044ae00
    Vec3* Corner(Vec3* out, int i);                 // 0x0043d240
    Vec3 Corner(int i);                             // 0x0043d240 (same function, sret form)

    Bounds GetBounds(int index);
    void D570();
    int D9e0(Vec3 p, float maxDist);
};

// @ 0x0044d570
void Blk::D570()
{
    BBox box;
    GetBBox(&box, 1, 0, 0);
    for (int i = 0, size = mVec.size(); i < size; i++) {
        if (mVec.mBeg[i].m18 && mVec.mBeg[i].m18->a) {
            if (mVec.at(i).m18->GetB()) {
                Vec3 last;
                Vec3 u;
                Mat3 v18;
                Vec3 v10;
                Vec3 t8;
                mVec.at(i).m18->Compute(&last, &v18);
                v10 = last - GetXf()->pos;
                v10 = v10 * Transposed(GetXf()->rot);
                Corner(&t8, 1);
                u = (t8 - GetXf()->pos) * Transposed(GetXf()->rot);
                v10[2] = 0.0f;
                if (mVec.mBeg[i].m1c) {
                    if (Abs(v10[0]) > 0.5f)
                        v10[1] = u[1];
                    else if (Abs(v10[1]) > 0.5f)
                        v10[0] = u[0];
                }
                *(Raw3*)&mVec.mBeg[i].mx = *(Raw3*)&v10;
            }
        }
    }
}

// @ 0x0044d8f0
Bounds Blk::GetBounds(int index)
{
    if (index >= 0 && index < mVec.size())
        return mVec.mBeg[index];
    Bounds b;
    ScratchSlots<4>();
    return b;
}

// @ 0x0044d9e0
int Blk::D9e0(Vec3 p, float maxDist)
{
    Vec3 local;
    local = (p - mPos) * Transposed(mRot);
    int count = Count();
    if (count > 0) {
        Vec3 d;
        d = local - Corner(0);
        VecC dir(d[0], d[1], 0.0f);
        Vec3 c0;
        Corner(&c0, 0);
        c0[2] = 0.0f;
        dir = Normalize(dir);
        VecC axis(1.0f, 0.0f, 0.0f);
        float base = Acos(Clamp(dir.x * axis.x + dir.y * axis.y + dir.z * axis.z, -1.0f, 1.0f));
        if (c0[1] > local[1])
            base = g_TwoPi - base;
        int best = -1;
        float bestDist = 3.402823466e+38f;
        for (int i = 0; i < count; i++) {
            Vec3 pa(MaxPt(i));
            Vec3 pb(MinPt(i));
            Vec3 cr = Cross(pb, g_Axis);
            V4 plane = PlaneFromPointNormal(pa, cr);
            float dist = Abs(PlaneEval(plane, local));
            bool inside = false;
            int prev = (i - 1) % count;
            if (prev < 0)
                prev += count;
            int next = (i + 1) % count;
            Bounds* bp = &Elem(prev);
            Vec3* mp = &MaxPt(prev);
            V4 planePrev(bp->mn.x, bp->mn.y, bp->mn.z, -Dot3(*mp, *(Vec3*)bp));
            Bounds* bn = &Elem(next);
            Vec3* mn2 = &MaxPt(next);
            V4 planeNext(bn->mn.x, bn->mn.y, bn->mn.z, -Dot3(*mn2, *(Vec3*)bn));
            Vec3 hitA;
            Vec3 hitB;
            float t;
            if (IntersectRayPlane(MaxPt(i), cr, planePrev, &t))
                hitA = MaxPt(i) + cr * t;
            if (IntersectRayPlane(MaxPt(i), -cr, planeNext, &t))
                hitB = MaxPt(i) - cr * t;
            VecC e0 = Normalize(Vec3(hitA - c0));
            VecC e1 = Normalize(Vec3(hitB - c0));
            float a0 = Acos(Clamp(Dot3(e0, axis), -1.0f, 1.0f));
            if (e0[1] < 0.0f)
                a0 = g_TwoPi - a0;
            float a1 = Acos(Clamp(Dot3(e1, axis), -1.0f, 1.0f));
            if (e1[1] < 0.0f)
                a1 = g_TwoPi - a1;
            float d0 = base - a0;
            a1 = a1 - a0;
            a0 = 0.0f;
            if (d0 < 0.0f)
                d0 = d0 + g_TwoPi;
            if (a1 < 0.0f)
                a1 = a1 + g_TwoPi;
            if (a0 <= d0 && d0 < a1)
                inside = true;
            if (inside && dist < bestDist) {
                bestDist = dist;
                best = i;
            }
        }
        if (maxDist <= 0.0f)
            return best;
        if (bestDist < maxDist)
            return best;
    }
    return -1;
}
