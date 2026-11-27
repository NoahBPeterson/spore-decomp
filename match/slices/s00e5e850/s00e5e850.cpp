// @ 0x00e5e850
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// SP::sCellSetOrientation (dev PDB: SP::sCellSetOrientation, SPGonzago/SPCellGame.obj).
// Gives a cell a new orientation and carries its fluid nodes along: every node is taken
// back into cell space with the old transform and out again with the new one.

// RenderWare's FPU vector/matrix types (rw::math::fpu, the bases of cSPVector3 / cSPMatrix3), as the
// prototype's out-of-line copies show them: scalars by const T&, row vector * Matrix33Template by value,
// and the compound operators compute all three components before storing (operator/= member-wise).
namespace rw { namespace math { namespace fpu {

template <class T, int Aligned> class Vector3Template {
public:
    T x, y, z;
    Vector3Template() {}
    Vector3Template(T ax, T ay, T az) : x(ax), y(ay), z(az) {}
    Vector3Template(const Vector3Template& v) : x(v.x), y(v.y), z(v.z) {}
};

template <class T, int Aligned>
class Matrix33Template {
public:
    T m[9];
};

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator-(const Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    return Vector3Template<T, Aligned>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator*(const Vector3Template<T, Aligned>& v, const T& s)
{
    return Vector3Template<T, Aligned>(v.x * s, v.y * s, v.z * s);
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator+(const Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    Vector3Template<T, Aligned> r;
    r.x = a.x + b.x;
    r.y = a.y + b.y;
    r.z = a.z + b.z;
    return r;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned> operator*(const Vector3Template<T, Aligned>& v, const Matrix33Template<T, Aligned>& m)
{
    Vector3Template<T, Aligned> r;
    r.x = v.x * m.m[0] + v.y * m.m[3] + v.z * m.m[6];
    r.y = v.x * m.m[1] + v.y * m.m[4] + v.z * m.m[7];
    r.z = v.x * m.m[2] + v.y * m.m[5] + v.z * m.m[8];
    return r;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator-=(Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    T x = a.x - b.x;
    T y = a.y - b.y;
    T z = a.z - b.z;
    a.x = x;
    a.y = y;
    a.z = z;
    return a;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator+=(Vector3Template<T, Aligned>& a, const Vector3Template<T, Aligned>& b)
{
    T x = a.x + b.x;
    T y = a.y + b.y;
    T z = a.z + b.z;
    a.x = x;
    a.y = y;
    a.z = z;
    return a;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator*=(Vector3Template<T, Aligned>& v, const T& s)
{
    T x = v.x * s;
    T y = v.y * s;
    T z = v.z * s;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

template <class T, int Aligned>
inline Vector3Template<T, Aligned>& operator/=(Vector3Template<T, Aligned>& v, const T& s)
{
    T inv = 1.0f / s;
    v.x *= inv;
    v.y *= inv;
    v.z *= inv;
    return v;
}

} } }

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : rw::math::fpu::Vector3Template<float, 0>(ax, ay, az) {}
    cSPVector3(const cSPVector3& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3(const rw::math::fpu::Vector3Template<float, 0>& v) : rw::math::fpu::Vector3Template<float, 0>(v) {}
    cSPVector3& operator=(const rw::math::fpu::Vector3Template<float, 0>& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

// 3x3 rotation.  Its copy constructor is the out-of-line Matrix3::Assign at 0x0041cb40; the body here lets
// cl see that it only reads the source and writes *this.
struct cSPMatrix3 : public rw::math::fpu::Matrix33Template<float, 0> {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& src);
};

__declspec(noinline) cSPMatrix3::cSPMatrix3(const cSPMatrix3& src)
{
    for (int k = 0; k < 9; ++k)
        m[k] = src.m[k];
}

inline cSPVector3& operator*=(cSPVector3& v, const cSPMatrix3& m)
{
    v = v * m;
    return v;
}

inline cSPVector3 operator*(const cSPMatrix3& m, const cSPVector3& v)
{
    return cSPVector3(m.m[0] * v.x + m.m[1] * v.y + m.m[2] * v.z, m.m[3] * v.x + m.m[4] * v.y + m.m[5] * v.z, m.m[6] * v.x + m.m[7] * v.y + m.m[8] * v.z);
}

struct cSPQuaternion {
    float x, y, z, w;
};

cSPMatrix3& Matrix3FromQuaternion(cSPMatrix3& out, const cSPQuaternion& q);   // 0x0059c190

struct cSPTransform {
    enum tFlags {
        kHasScale = 1,
        kHasRotation = 2,
        kHasTranslation = 4,
        kCompressed = 8,
    };

    unsigned short mFlags;               // +0x00 tFlags
    unsigned short mModificationCount;   // +0x02
    cSPVector3     mTranslation;         // +0x04
    float          mScale;               // +0x10
    cSPMatrix3     mRotation;            // +0x14

    cSPTransform(const cSPTransform& o)
        : mFlags(o.mFlags), mModificationCount(o.mModificationCount), mTranslation(o.mTranslation),
          mScale(o.mScale), mRotation(o.mRotation) {}

    float Scale() const { return mScale; }
    const cSPVector3& Translation() const { return mTranslation; }
    const cSPMatrix3& Rotation() const { return mRotation; }
    bool HasRotation() const { return (mFlags & kHasRotation) != 0; }

    void SetRotation(const cSPMatrix3& rotation)
    {
        mRotation = rotation;
        mModificationCount++;
        mFlags |= kHasRotation;
    }

    // Cell space -> world space.
    void TransformPoint(cSPVector3& v) const
    {
        if (mFlags & kHasRotation)
            v *= mRotation;
        v *= mScale;
        v += mTranslation;
    }

    // World space -> cell space (out-of-line copy @ 0x004ff6d0).
    void BackTransformPoint(cSPVector3& v) const
    {
        v -= mTranslation;
        if (mScale != 1.0f)
            v /= mScale;
        if (mFlags & kHasRotation)
            v = mRotation * v;
    }
};

namespace SP {

struct cSPFluidParticles {
    int        buffer;           // +0x0000
    cSPVector3 position[1500];   // +0x0004
};

struct cCellGame {
    char               pad_0000[0x4108];   // +0x0000
    cSPFluidParticles* mpFluidParticles;   // +0x4108
};

extern cCellGame* gspCellGame;   // 0x016b3c04

struct cSPCell {
    char         pad_000[0x48];             // +0x000
    cSPTransform mTransform;                // +0x048
    char         pad_080[0x248 - 0x080];    // +0x080
    unsigned int mGfxID;                    // +0x248
    int          mTessilation;              // +0x24c
    int          mNumNodes;                 // +0x250
    int          mNodeIndicies[64];         // +0x254 FluidIndex: slot in cSPFluidParticles
};

// @ 0x00e5e850
void sCellSetOrientation(cSPCell& cell, const cSPQuaternion& orientation)
{
    cSPTransform oldTransform(cell.mTransform);

    cSPMatrix3 rotation;
    cell.mTransform.SetRotation(Matrix3FromQuaternion(rotation, orientation));

    if (cell.mGfxID == 0 || cell.mNumNodes <= 1)
        return;

    for (int i = 0; i < cell.mNumNodes; ++i) {
        cSPFluidParticles* fluid = gspCellGame->mpFluidParticles;
        int node = cell.mNodeIndicies[i];
        cSPVector3* pp = &fluid->position[node];
        cSPVector3& p = *pp;
        oldTransform.BackTransformPoint(p);
        cell.mTransform.TransformPoint(p);
    }
}

}  // namespace SP
