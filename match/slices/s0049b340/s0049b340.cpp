// Slice s0049b340 (batch w1g0, slice 99), 0x0049b340..0x0049c20c.
// /Od editor-region code.
//
// 0049b460 SP::EditorUtils::GetSnapOrientation  -- snap/symmetry basis from the block orientation
// 0049b8b0 SP::EditorUtils::GetMissPlane        -- position + surface normal used by the pin/miss logic
// 0049bcc0 pile re-pin helper                    -- drop a repinned block onto the pile top / hit plane
// 0049c140 SP::EditorUtils::GetOrientationFromNormal -- behavior orientation for a surface normal

#include "types.h"

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

struct Matrix3 {
    Vector3 xAxis, yAxis, zAxis;
    Matrix3();                                   // 0x402ab0 identity
    Vector3& operator[](int i) { return (&xAxis)[i]; }
};

struct cSPEditorBlock;
struct cSPEditorModel;
struct cSPEditorSnapVector;

Matrix3 Transposed(const Matrix3& m);                          // 0x41ded0
Vector3 operator-(const Vector3& a, const Vector3& b);         // 0x41db10
Vector3 operator+(const Vector3& a, const Vector3& b);         // 0x41dc10
Vector3 operator*(const Vector3& v, const Matrix3& m);         // 0x41daf0
Vector3 operator*(const Vector3& v, const float& s);           // 0x41dca0
Vector3* Vector3_Scale(Vector3* out, const float* s, const Vector3* v);   // 0x41de40 (plane-hit path)
Vector3 operator-(const Vector3& v);                           // 0x422020
Vector3 Normalize(const Vector3& v);                           // 0x436ce0
Vector3 Cross(const Vector3& a, const Vector3& b);             // 0x44e460
Matrix3 operator*(const Matrix3& a, const Matrix3& b);         // 0x41de20
bool Vector3Equal(const Vector3* a, const Vector3* b);         // 0x4232c0
float Dot3(const Vector3* a, const Vector3* b);                // 0x455cc0

extern Vector3 g_SymmetryAxis;      // 0x15d63f4
extern Vector3 g_ZAxis;             // 0x15d6324
extern Vector3 g_UpAxis;            // 0x15d6370
extern Vector3 g_ZeroVector;        // 0x15d64d8
extern Matrix3 g_IdentityMatrix;    // 0x15d63a8

struct BBox {
    Vector3 mMin, mMax;
};

struct cSPBoundingBox : BBox {
    void Add(const BBox& b);                             // 0x43f050
};

struct Plane {
    float nx, ny, nz, d;
    Plane(float x, float y, float z, float w);           // 0x44e410
};
bool IntersectRayPlane(const Vector3* o, const Vector3* d, const Plane* p, float* t);   // 0x44e640

struct AllocTag { AllocTag() {} };

struct BlockVector {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** mpEnd;
    cSPEditorBlock** mpCap;
    uint32_t mAlloc[2];
    BlockVector(const AllocTag& a);                      // 0x540470
    void DestroyRange(cSPEditorBlock** b, cSPEditorBlock** e);   // 0x454e90
    void Free();                                         // 0x425990
    ~BlockVector() { DestroyRange(mpBegin, mpEnd); Free(); }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock* operator[](int i) { return mpBegin[i]; }
};

void BuildPileList(cSPEditorBlock* block, BlockVector* list, bool b);        // 0x48c790
bool FUN_0049a030(Vector3 origin, Vector3 dir, Vector3* out);               // 0x49a030
void RepinBlockToTorso(cSPEditorBlock* block, Vector3 pos, Matrix3 m, bool flag);   // 0x49fbd0
Matrix3 FUN_49c210(cSPEditorBlock* block, float x, float y, float z);       // 0x49c210
bool GetRotationAndPositionBasedOnBehavior(cSPEditorBlock* block, Vector3& pos, Matrix3& orient,
                                           Vector3 dir, bool bAlignToParent, bool bSnapToSymmetry); // 0x4942b0

struct cSPEditorSnapVector {
    Vector3 mNormal;                                     // +0x00
    char pad[0x20 - 0x0c];
    ~cSPEditorSnapVector();                              // 0x4ae250
};

struct cSPEditorModel {
    bool UsingSymmetry();                                // 0x4adc40
    float FUN_4adaa0();                                  // 0x4adaa0
    Vector3 FUN_4abbc0(Vector3 pos, cSPEditorBlock* block, char a, char b, Vector3 axis);  // 0x4abbc0
};

struct cSPEditorBlock {
    virtual void v0();
    char pad04[0x28 - 4];
    cSPEditorModel* mEditorModel;                        // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                                   // +0x48
    char pad54[0x60 - 0x54];
    Matrix3 mOrientation;                                // +0x60
    char pad84[0xa8 - 0x84];
    Matrix3 mBaseOrientation;                            // +0xa8
    char padcc[0x3c9 - 0xcc];
    bool mIsOnGround;                                    // +0x3c9
    char pad3ca[0x3e0 - 0x3ca];
    cSPEditorBlock* mPinTarget;                          // +0x3e0
    char pad3e4[0xdc8 - 0x3e4];
    uint32_t mFlags[2];                                  // +0xdc8

    bool TestFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = mFlags[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
    Vector3* F3d240(Vector3* out, char a);                       // 0x43d240
    int FUN_0044e800();                                          // 0x44e800
    cSPEditorSnapVector GetBounds(Vector3 pos, float f);          // 0x44e720
    bool IsPinnedOrLocked(char b);                               // 0x43bbc0
    BBox* GetBBox(BBox* out, int a, bool b, bool c);             // 0x44ae00
    void SetIsOnGround(bool b);                                  // 0x49c0f0
};

struct BitOwner {
    char pad0[0xdc8];
    uint32_t bits[2];                     // 0xdc8, 0xdcc
    bool GetFlag(unsigned i) const {
        if (i < 0x3c) {
            uint32_t w = bits[i >> 5];
            return (w & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

// @ 0x0049b340
bool FUN_0049b340(BitOwner* p) {
    if (p != 0) {
        if (p->GetFlag(7))
            return true;
        if (p->GetFlag(8))
            return true;
        if (p->GetFlag(0x23))
            return true;
    }
    return false;
}

// @ 0x0049c0f0
struct Y9c0 {
    char pad0[0x3c9];
    char flag;                            // 0x3c9
    char pad1[0x3e0 - 0x3ca];
    void* tracker;                        // 0x3e0
    void Set(char v);
};
void Y9c0::Set(char v) {
    this->flag = v;
    Y9c0* t = (Y9c0*)this->tracker;
    if (t != 0) {
        Y9c0* t2 = (Y9c0*)this->tracker;
        t2->flag = v;
    }
}

// @ 0x0049b460
Matrix3 GetSnapOrientation(cSPEditorBlock* block, Vector3 dir)
{
    Vector3 tmp;
    Vector3 v = (*block->F3d240(&tmp, 1) - dir) * Transposed(block->mOrientation);
    int snapCount = block->FUN_0044e800();

    if (block->TestFlag(0x31)) {
        Vector3 forward = -v;
        forward.z = 0.0f;
        forward = Normalize(forward);
        Vector3 up = -g_ZAxis;
        Vector3 right = Cross(up, forward);
        Matrix3 basis;
        basis.xAxis = right;
        basis.yAxis = up;
        basis.zAxis = forward;
        return basis * block->mOrientation;
    }

    if (snapCount < 1)
        return g_IdentityMatrix;

    cSPEditorSnapVector snap = block->GetBounds(dir, -1.0f);
    Vector3 forward = -snap.mNormal;
    Vector3 up = -g_ZAxis;
    Vector3 right = Cross(up, forward);
    Matrix3 basis;
    basis.xAxis = right;
    basis.yAxis = up;
    basis.zAxis = forward;
    return basis * block->mOrientation;
}

// @ 0x0049b8b0
void GetMissPlane(cSPEditorBlock* block, Vector3 dir, Vector3* outPos, Vector3* outNormal)
{
    float d = dir.x * g_SymmetryAxis.x + dir.y * g_SymmetryAxis.y + dir.z * g_SymmetryAxis.z;
    cSPEditorModel* model = block->mEditorModel;

    if (model->UsingSymmetry() && block->TestFlag(0xf) && fabs(d) < 0.8f) {
        *outNormal = g_UpAxis;
        *outPos = g_ZeroVector;
        return;
    }

    if (block->IsPinnedOrLocked(0)) {
        Vector3 side = -dir;
        side.z = 0.0f;

        *outPos = model->FUN_4abbc0(block->mPosition, block, 1, 1, g_ZAxis);

        Vector3 negOne;
        negOne.x = -1.0f;
        negOne.y = -1.0f;
        negOne.z = -1.0f;
        if (Vector3Equal(outPos, &negOne))
            *outPos = (side * model->FUN_4adaa0()) * 0.5f;

        *outNormal = -dir;
        outNormal->z = 0.0f;
        *outNormal = Normalize(*outNormal);
    } else {
        *outNormal = -dir;
        outNormal->z = 0.0f;
        *outNormal = Normalize(*outNormal);
        *outPos = block->mPosition;
    }
}

// @ 0x0049bcc0
void FUN_0049bcc0(cSPEditorBlock* block, Vector3 origin, Vector3 dir, Vector3 a, Vector3 b, bool flag)
{
    cSPEditorModel* model = block->mEditorModel;
    float floorZ = 0.0f;
    Vector3 hit;

    if (flag) {
        FUN_0049a030(origin, dir, &hit);

        cSPBoundingBox bounds;
        block->GetBBox(&bounds, 0, 0, 0);
        if (!block->TestFlag(8)) {
            AllocTag alloc;
            BlockVector pile(alloc);
            BuildPileList(block, &pile, 0);
            for (int i = 0; i < pile.size(); i++) {
                BBox other;
                pile[i]->GetBBox(&other, 0, 0, 0);
                bounds.Add(other);
            }
        }

        Vector3 rel = block->mPosition - bounds.mMin;
        floorZ = -rel.z;
        float t = (rel.z - origin.z) / dir.z;
        hit = origin + dir * t;
    }

    Vector3 result(block->mPosition);
    float dp = -Dot3(&a, &b);
    Plane plane(b.x, b.y, b.z, dp);

    float t;
    Vector3 planeHit;
    if (IntersectRayPlane(&origin, &dir, &plane, &t)) {
        Vector3 scaled;
        Vector3_Scale(&scaled, &t, &dir);
        planeHit = origin + scaled;
    } else
        planeHit = block->mPosition;

    block->mIsOnGround = false;
    if (block->mPinTarget != 0)
        block->mPinTarget->mIsOnGround = false;

    if (!flag) {
        result = planeHit;
    } else if (hit.z > planeHit.z) {
        block->SetIsOnGround(true);
        result = hit;
    } else {
        result = planeHit;
    }

    RepinBlockToTorso(block, result, block->mBaseOrientation, false);
}

// @ 0x0049c140
Matrix3 GetOrientationFromNormal(cSPEditorBlock* block, Vector3 normal)
{
    Matrix3 orient = FUN_49c210(block, normal.x, normal.y, normal.z);
    Vector3 pos = block->mPosition;
    GetRotationAndPositionBasedOnBehavior(block, pos, orient, block->mPosition, false, false);
    return orient;
}
