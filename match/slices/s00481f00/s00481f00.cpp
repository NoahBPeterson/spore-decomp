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

inline bool IsNaNF(float f)
{
    return (*(uint32_t*)&f & 0x7fffffff) > 0x7f800000u;
}

// @ 0x00481f00
bool IsNAN(const float* v)
{
    int n35;
    if (IsNaNF(v[0]) || IsNaNF(v[1]) || IsNaNF(v[2]))
        n35 = 1;
    else
        n35 = 0;
    return n35;
}

// cSPMatrix3 (3x3 basis); a struct, not a char buffer, so no /GS cookie
struct Mat3 { float m[9]; };

// cSPTransform -- dev size 0x38, layout confirmed by s0043cad0.
struct cSPTransform {
    uint16_t mFlags;               // +0x00
    uint16_t mModificationCount;   // +0x02
    Vector3  mTranslation;         // +0x04
    float    mScale;               // +0x10
    Mat3     mRotation;            // +0x14
    cSPTransform(const cSPTransform& src);     // 0x0040ce80 (copy ctor)
    void Invert();                             // 0x0040efa0
    void TransformPoint(Vector3& p);           // 0x0044d4f0
    // cSPTransform::SetTranslation / SetRotation (inline in the original)
    void SetTranslation(const Vector3& v)
    { mTranslation = v; mFlags |= 0x4; mModificationCount++; }   // kHasTranslation
    void SetRotation(const Mat3& r)
    { mRotation = r; mFlags |= 0x2; mModificationCount++; }      // kHasRotation
};

// cMWModel -- the model node whose cSPTransform sits at +0x08 (see s0043cad0).
struct cMWModel {
    char pad0[0x08];
    cSPTransform mTransform;      // +0x08
};

// cSPEditorBlock -- only the model slot at +0x10 (AutoRefCount<cMWModel>) is used here.
struct cSPEditorBlock {
    char pad0[0x10];
    cMWModel* mModel;              // +0x10
};

// RotHandle -- cSPEditorHandleDeform layout (size 0x1d8); vtable slot 19 is GetHandlePos.
#define RH_VIRT(n) virtual void vpad##n();
struct RotHandle {
    RH_VIRT(0) RH_VIRT(1) RH_VIRT(2) RH_VIRT(3) RH_VIRT(4) RH_VIRT(5) RH_VIRT(6)
    RH_VIRT(7) RH_VIRT(8) RH_VIRT(9) RH_VIRT(10) RH_VIRT(11) RH_VIRT(12)
    RH_VIRT(13) RH_VIRT(14) RH_VIRT(15) RH_VIRT(16) RH_VIRT(17) RH_VIRT(18)
    virtual Vector3* GetHandlePos(Vector3* out, float t);   // slot 19 (vptr+0x4c)

    uint32_t pad04[3];             // +0x04 (RefCountVTemplate vptr/refcount)
    cSPEditorBlock* mBlock;        // +0x10
    cMWModel* mModel;              // +0x14 (AutoRefCount<cMWModel>)
    cMWModel* mOverdrawModel;      // +0x18 (AutoRefCount<cMWModel>)
    char pad1c[0x74];              // +0x1c .. +0x8f
    Vector3 mP0;                   // +0x90
    Vector3 mP1;                   // +0x9c
    char padA8[0xc0];              // +0xa8 .. +0x167
    Vector3 mTriangleRelativeDirection;  // +0x168
    Vector3 mBasePositionOffset;         // +0x174
    float  mRadius;                // +0x180
    char pad184[0x51];             // +0x184 .. +0x1d4
    uint8_t mDoNotPlaceHandle;     // +0x1d5

    Vector3* GetDir(Vector3* out, bool useParent);
    Vector3* GetP0(Vector3* out, bool transform);
    Vector3* GetP1(Vector3* out, bool transform);
    void*    GetOrientation(void* out);
    void     Update();
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
    VSub(&d, &this->mP1, &this->mP0);
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

// cSPMatrix3 is assigned into via __thiscall (this = destination)
struct MatOut {
    void Assign(const Mat3* src);   // @ 0x0041cb40
};

// @ 0x004822d0
void* RotHandle::GetOrientation(void* out)
{
    Vector3 d, t;
    Mat3 basis;
    VSub(&d, &this->mP1, &this->mP0);
    VMul(&t, &d, (const Vector3*)(*(char**)((char*)this->mBlock + 0x10) + 0x1c));
    void BuildMatrix(Mat3*, const Vector3*, void*);   // @ 0x004a89e0
    BuildMatrix(&basis, &t, (void*)0x15d4e28);
    ((MatOut*)out)->Assign(&basis);
    return out;
}

// @ 0x004823b0
void RotHandle::Update()
{
    if (!mDoNotPlaceHandle) {
        Vector3 pos;
        mTriangleRelativeDirection = *GetHandlePos(&pos, mRadius);

        cSPTransform xform(mBlock->mModel->mTransform);
        xform.Invert();

        mBasePositionOffset = mTriangleRelativeDirection;
        xform.TransformPoint(mBasePositionOffset);

        Mat3 basis;
        GetOrientation(&basis);

        if (mModel) {
            mModel->mTransform.SetTranslation(mTriangleRelativeDirection);
            mModel->mTransform.SetRotation(basis);
        }
        if (mOverdrawModel) {
            mOverdrawModel->mTransform.SetTranslation(mTriangleRelativeDirection);
            mOverdrawModel->mTransform.SetRotation(basis);
        }
    }
}
