// Slice s00bd2840: the single function here is 0x00BD2AF0 (1845 bytes, __thiscall, no args), an
// object whose embedded cLocomotiveObject (at +0x34) supplies position, orientation and scale.
// It rebuilds the object's world-space geometry:
//   - every local hull point (+0x2a0) is scaled, rotated by the orientation quaternion, offset by
//     the position and snapped to the planet surface (DirectionToSurfacePosition) -> +0x2c8;
//   - every local normal (+0x2b4) is rotated by the same quaternion -> +0x2dc;
//   - the dirty flag (+0x2f0) is set;
//   - every local part transform (+0x2f4) is composed with (position, scale, rotation) -> +0x308;
//   - the attached helper object (+0x1f0), if any, is told to update.
// The class name is Claude-coined (the PDB candidate "SP::AddTribeRoads" is a caller-scored guess).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar SSE; no EH frame).
#include "types.h"

// ---- math ---------------------------------------------------------------------------------
struct Vector3 { float x, y, z; };                       // plain copies go through integer registers

struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) : x(q.x), y(q.y), z(q.z), w(q.w) {}
};

struct Matrix3 { float m[9]; };

// cSPTransform / cTransform (0x38 bytes)
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3 mOffset;
    float mScale;
    Matrix3 mRotation;

    cSPTransform() : mFlags(0), mModificationCount(0) {}
    cSPTransform& operator=(const cSPTransform& o);      // 0x00537dc0
    void Accumulate(const cSPTransform* other);          // 0x0040ccb0
    void SetOffset(const Vector3& v) { mOffset = v; mFlags |= 4; mModificationCount++; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetRotation(const Matrix3& r) { mRotation = r; mFlags |= 2; mModificationCount++; }
};

namespace SP { Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quaternion& q); }   // 0x0059c190 (cdecl)

// ---- containers -----------------------------------------------------------------------------
template <class T> struct SpVector {                     // eastl::vector with sp_vector_allocator (0x14 bytes)
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void resize(int n);
};
template <> void SpVector<Vector3>::resize(int n);       // 0x00473810
template <> void SpVector<cSPTransform>::resize(int n);  // 0x0041e3b0

// ---- game objects ---------------------------------------------------------------------------
class cLocomotiveObject {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0c();
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1c();
    virtual void _v20(); virtual void _v24(); virtual void _v28();
    /* 2ch */ virtual const Vector3& GetPosition();
    /* 30h */ virtual const Quaternion& GetOrientation();
    /* 34h */ virtual float GetScale();
};

struct cPlanetModel {
    Vector3* DirectionToSurfacePosition(Vector3* out, Vector3* dir);   // 0x00b815a0
};
namespace SP { cPlanetModel* __cdecl PlanetModel(); }                  // 0x00b3d350

struct cHelperObject { void Update(); };                               // 0x00be0020 (thiscall)

class cPlacedModel {
public:
    char _pad00[0x34];
    cLocomotiveObject mLocomotive;           // +0x34
    char _pad38[0x1f0 - 0x38];
    cHelperObject* mpHelper;                 // +0x1f0
    char _pad1f4[0x2a0 - 0x1f4];
    SpVector<Vector3> mLocalPoints;          // +0x2a0
    SpVector<Vector3> mLocalNormals;         // +0x2b4
    SpVector<Vector3> mWorldPoints;          // +0x2c8
    SpVector<Vector3> mWorldNormals;         // +0x2dc
    uint8_t mWorldDirty;                     // +0x2f0
    char _pad2f1[3];
    SpVector<cSPTransform> mLocalTransforms; // +0x2f4
    SpVector<cSPTransform> mWorldTransforms; // +0x308

    void UpdateWorldGeometry();
};

// Rotate a vector by a unit quaternion (standard quaternion-to-matrix terms).
static __forceinline Vector3 Rotate(const Quaternion& q, const Vector3& v)
{
    float yy = q.y * q.y;
    float xy = q.y * q.x;
    float zz = q.z * q.z;
    float zx = q.z * q.x;
    float zy = q.z * q.y;
    float zw = q.z * q.w;
    float xx = q.x * q.x;
    float wx = q.w * q.x;
    float wy = q.w * q.y;
    Vector3 r;
    r.x = ((xy - zw) * v.y + (wy + zx) * v.z) * 2.0f + (1.0f - (zz + yy) * 2.0f) * v.x;
    r.y = ((zw + xy) * v.x + (zy - wx) * v.z) * 2.0f + (1.0f - (zz + xx) * 2.0f) * v.y;
    r.z = ((zx - wy) * v.x + (wx + zy) * v.y) * 2.0f + (1.0f - (yy + xx) * 2.0f) * v.z;
    return r;
}

// @ 0x00BD2AF0
void cPlacedModel::UpdateWorldGeometry()
{
    int count = mLocalPoints.size();
    mWorldPoints.resize(count);
    mWorldNormals.resize(count);

    float scale = mLocomotive.GetScale();
    Quaternion q = mLocomotive.GetOrientation();
    const Vector3* pPosition = &mLocomotive.GetPosition();

    if (count > 0) {
        float yy = q.y * q.y;
        float xy = q.y * q.x;
        float zz = q.z * q.z;
        float zx = q.z * q.x;
        float zy = q.z * q.y;
        float zw = q.z * q.w;
        float xx = q.x * q.x;
        float wx = q.w * q.x;
        float wy = q.w * q.y;
        float a01 = xy - zw;
        float a02 = wy + zx;
        float m00 = 1.0f - (zz + yy) * 2.0f;
        float a12 = zy - wx;
        float a10 = zw + xy;
        float m11 = 1.0f - (zz + xx) * 2.0f;
        float a21 = wx + zy;
        float a20 = zx - wy;
        float m22 = 1.0f - (yy + xx) * 2.0f;

        for (int i = 0; i < count; ++i) {
            Vector3 p = mLocalPoints[i];
            Vector3 v;
            v.x = p.x * scale;
            v.y = p.y * scale;
            v.z = p.z * scale;
            Vector3 r = Rotate(q, v);
            Vector3 dir;
            dir.x = pPosition->x + r.x;
            dir.y = pPosition->y + r.y;
            dir.z = pPosition->z + r.z;
            Vector3 tmp;
            dir = *SP::PlanetModel()->DirectionToSurfacePosition(&tmp, &dir);
            mWorldPoints[i] = dir;

            float nx = mLocalNormals[i].x;
            float ny = mLocalNormals[i].y;
            float nz = mLocalNormals[i].z;
            Vector3& out = mWorldNormals[i];
            out.x = (a02 * nz + a01 * ny) * 2.0f + m00 * nx;
            out.y = (a10 * nx + a12 * nz) * 2.0f + m11 * ny;
            out.z = (a20 * nx + a21 * ny) * 2.0f + m22 * nz;
        }
    }

    mWorldDirty = 1;

    Matrix3 rotation;
    cSPTransform xf;
    xf.SetOffset(*pPosition);
    xf.SetRotation(*SP::Matrix3FromQuaternion(&rotation, q));

    int numParts = mLocalTransforms.size();
    mWorldTransforms.resize(numParts);
    for (int i = 0; i < numParts; ++i) {
        cSPTransform t;
        t.SetOffset(xf.mOffset);
        t.SetScale(scale);
        t.SetRotation(xf.mRotation);
        t.Accumulate(&mLocalTransforms[i]);
        mWorldTransforms[i] = t;
    }

    if (mpHelper)
        mpHelper->Update();
}
