// Slice s00bcf6f0 (continued): transform helper 0x00bd0390.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;

struct Vector3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };

struct Matrix3 {
    float m[9];
    void Assign(const Matrix3& src);     // 0x0041cb40
};

// Returns `out` (a reference to the same object it was handed).
Matrix3& __cdecl Matrix3FromQuaternion(Matrix3& out, const Quaternion& q);   // 0x0059c190

extern const Matrix3 g_identityMatrix;   // 0x0168bc38

// The transform message filled in by the function (flags/count, position, scale, rotation).
struct Xform {
    uint16_t flags;          // +0x00  bit 1 = rotation valid, bit 2 = position valid
    int16_t  count;          // +0x02
    Vector3  pos;            // +0x04
    float    scale;          // +0x10
    Matrix3  rot;            // +0x14

    void SetRot(const Matrix3& m) { rot = m; flags |= 2; }
    void SetPos(const Vector3& p) { pos = p; flags |= 4; }
};

// The game object whose vtable is at offset 0; the function's `this` is the subobject
// 0x554 bytes into it.  Only the two vtable slots the function calls are modelled.
struct UFOBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual const Vector3&    GetPosition();     // 0x2c
    virtual const Quaternion& GetRotation();     // 0x30
};

// The subobject that `this` points at (UFOBase + 0x554).
struct UFOSlice {
    char    m_pad[0xcc];                  // 0x000 .. 0x0cb
    Vector3 m_localPos;                   // +0x0cc (object + 0x620)

    Vector3* GetTransformedPosition(Vector3* out);   // 0x00bd0390 (ret 4)
};

// @ 0x00bd0390
Vector3* UFOSlice::GetTransformedPosition(Vector3* out)
{
    out->x = m_localPos.x;
    out->y = m_localPos.y;
    out->z = m_localPos.z;

    Xform xf;
    xf.flags = 0;
    xf.scale = 1.0f;
    xf.rot.Assign(g_identityMatrix);

    UFOBase* base = (UFOBase*)((char*)this - 0x554);

    Matrix3 tmp;
    xf.SetRot(Matrix3FromQuaternion(tmp, base->GetRotation()));
    xf.SetPos(base->GetPosition());

    if (xf.flags & 2) {
        float px = out->x;
        float py = out->y;
        float pz = out->z;
        float nx = px * xf.rot.m[0] + py * xf.rot.m[3] + pz * xf.rot.m[6];
        float ny = px * xf.rot.m[1] + py * xf.rot.m[4] + pz * xf.rot.m[7];
        float nz = px * xf.rot.m[2] + py * xf.rot.m[5] + pz * xf.rot.m[8];
        out->x = nx;
        out->y = ny;
        out->z = nz;
    }

    out->x = out->x * xf.scale + xf.pos.x;
    out->y = out->y * xf.scale + xf.pos.y;
    // The original reuses pos.y here (it adds the same stack slot as the y term).
    out->z = out->z * xf.scale + xf.pos.y;

    return out;
}
