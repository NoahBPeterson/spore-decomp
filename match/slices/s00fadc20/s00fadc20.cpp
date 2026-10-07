// Slice s00fadc20: 0x00FADC20, rebuilds the list of cube-map faces (and the [0,1]^2 face rectangles) that a
// view rectangle covers on a planet.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (same module as s00fab2b0).
//
// Behaviour:
//   * clears the face-rect vector at +0x80 (eastl::vector::erase(begin, end): copy 0x00fad0a0, no dtors);
//   * builds the 4 corners pos -/+ right*scale +/- up*scale*aspect of the view rectangle, and their unit
//     directions;
//   * stores the tangent plane of the sphere at pos (+0xf8, the normal is normalized twice: once by the
//     caller expression and once by the plane constructor);
//   * projects corners 3, 2, 1 onto that plane along their directions (ray from the origin, only when the
//     ray hits in front), and stores corner 3 (+0xec) plus the two edge axes/lengths (+0x108/+0x114,
//     +0x118/+0x124);
//   * for each of the 6 cube faces whose hemisphere contains all 4 directions (sign * n[w] >= 1e-6), projects
//     the directions to face coordinates in [0,1], takes their bounding rect, and if it overlaps the unit
//     rect, clips it (RectF::Intersect, 0x00634b60) and appends {face, rect} (push_back, 0x00fada70).
// NAMING NOTE: no symbol is known for 0x00FADC20 or its owner class; class/member/function names below are
// Claude-coined. The face-axis table at 0x01491030 is {u,v,w,pad} per axis pair: {0,1,2}, {1,2,0}, {2,0,1}.
#include "types.h"
#include <math.h>

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}

    Vector3& operator*=(const float& s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }

    float Dot(const Vector3& v) const { return x * v.x + y * v.y + z * v.z; }
    float Length() const { return sqrtf(x * x + y * y + z * z); }
    void Normalize()
    {
        // The original rounds 1/len to float before scaling (it spills it and multiplies in SSE); cl 15.00.30729
        // keeps it on the x87 stack instead, which differs for huge/denormal inputs. The volatile store
        // reproduces the rounding.
        volatile float inv = 1.0f / sqrtf(x * x + y * y + z * z);
        float s = inv;
        *this *= s;
    }
    Vector3 Normalized() const
    {
        Vector3 r(*this);
        r.Normalize();
        return r;
    }
};

static inline Vector3 operator+(const Vector3& a, const Vector3& b) { return Vector3(a.x + b.x, a.y + b.y, a.z + b.z); }
static inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }
static inline Vector3 operator*(const Vector3& a, float s) { return Vector3(a.x * s, a.y * s, a.z * s); }
static inline Vector3 operator/(const Vector3& a, float s)
{
    float inv = 1.0f / s;
    return Vector3(a.x * inv, a.y * inv, a.z * inv);
}

struct Plane
{
    Vector3 mNormal;
    float   mD;
    Plane() {}
    __forceinline Plane(const Vector3& normal, const Vector3& point)
    {
        mNormal = normal;
        mNormal.Normalize();
        mD = -mNormal.Dot(point);
    }
};

// Ray from `origin` along `dir`: moves `point` to the hit with `plane` if the hit lies in front.
static inline void IntersectRayPlane(const Plane& plane, const Vector3& origin, const Vector3& dir, Vector3& point)
{
    float denom = dir.Dot(plane.mNormal);
    if (denom != 0.0f)
    {
        float t = -(plane.mNormal.Dot(origin) + plane.mD) / denom;
        if (t >= 0.0f)
            point = dir * t;
    }
}

struct RectF                    // EA::RectT<float>
{
    float mLeft, mTop, mRight, mBottom;
    RectF() {}
    RectF(float l, float t, float r, float b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
    bool Intersect(const RectF& a, const RectF& b);     // 0x00634b60
};

template <typename T> inline const T& min_(const T& a, const T& b) { return (b < a) ? b : a; }
template <typename T> inline const T& max_(const T& a, const T& b) { return (a < b) ? b : a; }

// cube-face coordinate of one view corner
struct cFaceCoord
{
    float u, v;
    int   face;
    cFaceCoord(float au, float av, int f) : u(au), v(av), face(f) {}
};

// one covered cube face: face index + covered part of the face in [0,1]^2 (0x14 bytes)
struct cFaceRect
{
    int   mFace;
    RectF mRect;
};

// eastl::vector<cFaceRect>
struct cFaceRectVector
{
    cFaceRect* mpBegin;
    cFaceRect* mpEnd;
    cFaceRect* mpCapacity;
    uint32_t   mAllocator;

    void push_back(const cFaceRect& value);             // 0x00fada70
    cFaceRect* erase(cFaceRect* first, cFaceRect* last);
    void clear() { erase(mpBegin, mpEnd); }
};

cFaceRect* copy(cFaceRect* first, cFaceRect* last, cFaceRect* dest);  // 0x00fad0a0 (eastl::copy)

inline cFaceRect* cFaceRectVector::erase(cFaceRect* first, cFaceRect* last)
{
    cFaceRect* const pNewEnd = copy(last, mpEnd, first);
    (void)pNewEnd;
    mpEnd -= (last - first);
    return first;
}

// the view rectangle (layout from the reads at +4..+0x28)
struct cViewRect
{
    uint32_t mUnknown0;
    Vector3  mPosition;     // +0x04: center of the rectangle
    float    mScale;        // +0x10
    Vector3  mRight;        // +0x14
    Vector3  mUp;           // +0x20
};

extern const uint8_t gCubeFaceAxes[3][4];   // 0x01491030: {u, v, w, pad}

class cViewFaceCover
{
public:
    void Update(const cViewRect& view, float aspect);

    uint32_t        mPad0[0x20];
    cFaceRectVector mFaceRects;     // +0x80
    uint32_t        mPad90[0x17];
    Vector3         mOrigin;        // +0xec
    Plane           mPlane;         // +0xf8
    Vector3         mUAxis;         // +0x108
    float           mULength;       // +0x114
    Vector3         mVAxis;         // +0x118
    float           mVLength;       // +0x124
};

// @ 0x00fadc20
void cViewFaceCover::Update(const cViewRect& view, float aspect)
{
    mFaceRects.clear();

    Vector3 pos = view.mPosition;
    float scale = view.mScale;
    Vector3 right = view.mRight * scale;
    Vector3 up = view.mUp * scale * aspect;

    Vector3 c0 = pos - right + up;
    Vector3 c1 = pos + right + up;
    Vector3 c2 = pos + right - up;
    Vector3 c3 = pos - right - up;

    Vector3 n0 = c0.Normalized();
    Vector3 n1 = c1.Normalized();
    Vector3 n2 = c2.Normalized();
    Vector3 n3 = c3.Normalized();

    mPlane = Plane(pos.Normalized(), pos);

    Vector3 origin(0.0f, 0.0f, 0.0f);
    IntersectRayPlane(mPlane, origin, n3, c3);
    IntersectRayPlane(mPlane, origin, n2, c2);
    IntersectRayPlane(mPlane, origin, n1, c1);

    Vector3 uEdge = c2 - c3;
    Vector3 vEdge = c1 - c2;

    mOrigin = c3;
    mULength = uEdge.Length();
    mUAxis = uEdge / mULength;
    mVLength = vEdge.Length();
    mVAxis = vEdge / mVLength;

    RectF unit(0.0f, 0.0f, 1.0f, 1.0f);

    for (int face = 0; face < 6; ++face)
    {
        cFaceCoord f0(0.0f, 0.0f, face);
        cFaceCoord f1(1.0f, 0.0f, face);
        cFaceCoord f2(1.0f, 1.0f, face);
        cFaceCoord f3(0.0f, 1.0f, face);

        const uint8_t* axes = gCubeFaceAxes[face >> 1];
        float sign = (face & 1) ? -1.0f : 1.0f;
        int u = axes[0];
        int v = axes[1];
        int w = axes[2];

        if (sign * n0[w] < 1e-6f || n1[w] * sign < 1e-6f || n3[w] * sign < 1e-6f || n2[w] * sign < 1e-6f)
            continue;

        float sign2 = sign * sign;
        float inv0 = 1.0f / n0[w];
        float inv1 = 1.0f / n1[w];
        float inv2 = 1.0f / n2[w];
        float inv3 = 1.0f / n3[w];

        f0.u = (n0[u] * inv0 * sign2 + 1.0f) * 0.5f;
        f1.u = (n1[u] * inv1 * sign2 + 1.0f) * 0.5f;
        f2.u = (n2[u] * inv2 * sign2 + 1.0f) * 0.5f;
        f3.u = (n3[u] * inv3 * sign2 + 1.0f) * 0.5f;
        f0.v = (n0[v] * sign * inv0 + 1.0f) * 0.5f;
        f1.v = (n1[v] * sign * inv1 + 1.0f) * 0.5f;
        f2.v = (n2[v] * sign * inv2 + 1.0f) * 0.5f;
        f3.v = (n3[v] * sign * inv3 + 1.0f) * 0.5f;

        RectF r(min_(f2.u, min_(f3.u, min_(f0.u, f1.u))),
                min_(f2.v, min_(f3.v, min_(f0.v, f1.v))),
                max_(f2.u, max_(f3.u, max_(f0.u, f1.u))),
                max_(f2.v, max_(f3.v, max_(f0.v, f1.v))));

        if (r.mLeft < 1.0f && r.mRight > 0.0f && r.mTop < 1.0f && r.mBottom > 0.0f)
        {
            r.Intersect(r, unit);
            cFaceRect fr;
            fr.mFace = face;
            fr.mRect = r;
            mFaceRects.push_back(fr);
        }
    }
}
