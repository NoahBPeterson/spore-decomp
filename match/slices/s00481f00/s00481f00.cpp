// Slice s00481f00: cSPEditorHandleRotationBall geometry accessors, /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 { float x, y, z; };

// vector / transform helpers (masked relocations)
Vector3* VSub(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041db10
Vector3* VNorm(Vector3* out, const Vector3* a);                    // @ 0x00436ce0
Vector3* VAdd(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041dca0
Vector3* VMul(Vector3* out, const Vector3* a, const Vector3* b);   // @ 0x0041daf0
void     TransformPoint(void* xform, Vector3* p);                  // @ 0x0044d4f0 (ecx=xform)
Vector3* Interp(Vector3* out, const Vector3* a, const Vector3* b, float t); // @ 0x00413cc0

// @ 0x00481f00
inline bool IsNaNF(float f)
{
    return (*(uint32_t*)&f & 0x7fffffff) > 0x7f800000u;
}

bool IsNAN(const float* v)
{
    int n35;
    if (IsNaNF(v[0]) || IsNaNF(v[1]) || IsNaNF(v[2]))
        n35 = 1;
    else
        n35 = 0;
    return n35;
}

struct cSPEditorBlock;

struct RotHandle {
    char pad0[0x10];
    void* mBlock;                  // +0x10
    char pad14[0x7c];
    Vector3 mP0;                   // +0x90
    Vector3 mP1;                   // +0x9c
    char padA8[0xd8];
    float  mRadius;                // +0x180
    char pad184[0x4c];
    uint8_t mDone;                 // +0x1d5

    Vector3* GetHandlePos(Vector3* out, float t);
    Vector3* GetDir(Vector3* out, bool useParent);
    Vector3* GetP0(Vector3* out, bool transform);
    Vector3* GetP1(Vector3* out, bool transform);
    void*    GetOrientation(void* out);
    void     Update();             // 0x4823b0, partial
};

struct EntityXform {
    char pad[8];
    void TransformPoint(Vector3* p);   // uses 0x44d4f0 on this+8
};

// @ 0x00481fa0
Vector3* RotHandle::GetHandlePos(Vector3* out, float t)
{
    if (t == -1.0f)
        t = this->mRadius;
    Vector3 local;
    Interp(&local, &this->mP0, &this->mP1, t);
    ((EntityXform*)(*(char**)((char*)this->mBlock + 0x10) + 8))->TransformPoint(&local);
    out->x = local.x;
    out->y = local.y;
    out->z = local.z;
    return out;
}

// @ 0x00482040
Vector3* RotHandle::GetDir(Vector3* out, bool useParent)
{
    Vector3 d;
    VSub(&d, &this->mP0, &this->mP1);
    Vector3 n;
    VNorm(&n, &d);
    if (useParent) {
        Vector3 t;
        VMul(&t, &n, (const Vector3*)(*(char**)((char*)this->mBlock + 0x10) + 0x1c));
        n = t;
    }
    out->x = n.x;
    out->y = n.y;
    out->z = n.z;
    return out;
}

// @ 0x00482130
Vector3* RotHandle::GetP0(Vector3* out, bool transform)
{
    Vector3 v = this->mP1;
    if (transform) {
        ((EntityXform*)(*(char**)((char*)this->mBlock + 0x10) + 8))->TransformPoint(&v);
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
    } else {
        out->x = this->mP1.x;
        out->y = this->mP1.y;
        out->z = this->mP1.z;
    }
    return out;
}

// @ 0x00482200
Vector3* RotHandle::GetP1(Vector3* out, bool transform)
{
    Vector3 v = this->mP0;
    if (transform) {
        ((EntityXform*)(*(char**)((char*)this->mBlock + 0x10) + 8))->TransformPoint(&v);
        out->x = v.x;
        out->y = v.y;
        out->z = v.z;
    } else {
        out->x = this->mP0.x;
        out->y = this->mP0.y;
        out->z = this->mP0.z;
    }
    return out;
}

// @ 0x004822d0
void* RotHandle::GetOrientation(void* out)
{
    Vector3 d, n, t;
    char basis[0x24];
    VSub(&d, &this->mP0, &this->mP1);
    VMul(&t, &d, (const Vector3*)(*(char**)((char*)this->mBlock + 0x10) + 0x1c));
    void BuildMatrix(void*, const Vector3*, void*);   // @ 0x004a89e0
    BuildMatrix(basis, &t, (void*)0x15d4e28);
    void Matrix3Assign(void*, const void*);           // @ 0x0041cb40
    Matrix3Assign(out, basis);
    return out;
}

// @ 0x004823b0 -- PARTIAL: handle-sync update; only the early-out and the local
// transform fetch are reproduced, the rest of the body is omitted.
void RotHandle::Update()
{
    if (this->mDone)
        return;
    char xform[0x38];
    void GetLocalTransform(void*, void*);              // @ 0x0040ce80
    GetLocalTransform(*(char**)((char*)this->mBlock + 0x10) + 8, xform);
    void PartTransformInvert(void*);                   // @ 0x0040efa0
    PartTransformInvert(xform);
}
