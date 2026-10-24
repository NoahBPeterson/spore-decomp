// s005b5110 -- SP::cSPEditorManipulationRotationHandle ctor/setters/dtor plus
// EA::Swarm cTransform transform-multiply (0x005b51b0).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- math types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3 operator+(const Vector3& b) const { return Vector3(x + b.x, y + b.y, z + b.z); }
    Vector3 operator*(float s) const { return Vector3(x * s, y * s, z * s); }
};
struct Matrix3 { Vector3 row[3]; Matrix3() {} };

extern const Matrix3 kIdentityMatrix;   // 0x015e9f94
extern const float   kOneConst;         // 0x01485720

// ---------------------------------------------------------------- vtables
extern void* vtbl_13f7634[];            // derived, +0x00
extern void* vtbl_13f7624[];            // derived, +0x14
extern void* vtbl_13ec458[];            // base,    +0x14
extern void* vtbl_13eb938[];            // base,    +0x00

// ---------------------------------------------------------------- helpers
void  OpDelete(void* p);                                                       // 0x00f47380
void  BuildPileList(void* block, void* pile, int flag);                        // 0x0048c790
void  PileSetup(char* block, void* pile);                                      // 0x004961d0
Matrix3* MatMul(Matrix3* out, const Matrix3* a, const Matrix3* b);             // 0x0041de20
void  CopyAddRefPtrs(void** pOutEnd, void** first, void** last, void** dest, void* owner);  // 0x004b2220

Vector3 MulVecMat(const Vector3& v, const Matrix3& m)
{
    return Vector3(v.x * m.row[0].x + v.z * m.row[2].x + v.y * m.row[1].x,
                   v.x * m.row[0].y + v.z * m.row[2].y + v.y * m.row[1].y,
                   v.x * m.row[0].z + v.z * m.row[2].z + v.y * m.row[1].z);
}

// ---------------------------------------------------------------- referenced classes
class Block;
struct PileList {
    void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator;
    void Dtor();                                        // 0x00453eb0 (thiscall)
    void VectorCtor(int count, void* alloc);            // 0x0066aec0 (thiscall)
};

class Handle {
public:
    virtual int  AddRef();                          // 0x00
    virtual int  Release();                         // 0x04
    virtual void v08();
    virtual void* Cast(uint32_t typeID);            // 0x0c
    virtual uint32_t GetType();                     // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual Vector3 GetPosition();                  // 0x24
    virtual void v28();
    virtual void v2c();
    virtual void SetState(int state, int flag);     // 0x30
    Block* GetEditorBlock();                        // 0x0047e6c0 (non-virtual)
};

class Ring : public Handle {
public:
    Vector3 GetForwardVector(bool a);               // 0x00484ee0
    Vector3 GetRotationAxis(bool a);                // 0x00484e40
};

class Block {
public:
    virtual void v00();
    virtual int  AddRef();                          // 0x04
    virtual int  Release();                         // 0x08
    void Refresh();                                 // 0x00448a80
    void F3cfc0(int h, char d);                     // 0x0043cfc0

    char pad00[0x24];                               // vptr is at +0x00
    void* mEditorModel;                             // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                              // +0x48
    Vector3 mHistoryPosition;                       // +0x54
    Matrix3 mOrientation;                           // +0x60
    Matrix3 mHistoryOrientation;                    // +0x84
    Matrix3 mBaseOrientation;                       // +0xa8
    Matrix3 mHistoryBaseOrientation;                // +0xcc
    Matrix3 mUserOrientation;                       // +0xf0
    Matrix3 mHistoryUserOrientation;                // +0x114
    char pad138[0x33c - 0x138];
    Block* mParentBlock;                            // +0x33c
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

class cViewer {
public:
    bool GetWorldRayFromScreenCoords(float x, float y, Vector3* origin, Vector3* dir);   // 0x007c4730
};
class cApp {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cViewer* GetViewer();                   // 0x58
};
cApp* App();                                        // 0x0067dd10

// ---------------------------------------------------------------- the handle class
struct RotationHandle {
    void*      vtbl0;                    // +0x00
    uint8_t    bFlag04;                  // +0x04
    uint8_t    pad05[7];
    float      f0c;                      // +0x0c
    float      f10;                      // +0x10
    void*      vtbl14;                   // +0x14
    uint32_t   d18;                      // +0x18
    AutoRefCount<Handle> mRotationHandle;   // +0x1c
    AutoRefCount<Block>  mBlock;            // +0x20
    PileList   mPileList;                // +0x24
    uint32_t   pad34;                    // +0x34
    Vector3    mMouseOffset;             // +0x38
    Vector3    mInitialClickPosition;    // +0x44
    float      mHistoryAppliedRoll;      // +0x50
    Matrix3    mRotationModifier;        // +0x54
    Matrix3    mBaseOrientation;         // +0x78
    Matrix3    mInitialUserOrientation;  // +0x9c
    Vector3    mRotationAxis;            // +0xc0
    Vector3    mBlockHistoryForward;     // +0xcc
    Vector3    mPlaneNormal;             // +0xd8
    Matrix3    mParentOrientation;       // +0xe4
    Matrix3    mGeometryOrientation;     // +0x108
    float      mTimeSpentSnapped;        // +0x12c
    uint8_t    mOutsideInitialSnapRange; // +0x130
    uint8_t    pad131[3];
    float      mTargetRoll;              // +0x134
    float      mActualRoll;              // +0x138
    float      mSymmetryModifier;        // +0x13c
    float      mX;                       // +0x140
    float      mY;                       // +0x144
    Vector3    mCameraPlanePoint;        // +0x148
    uint32_t   d154;                     // +0x154

    void BaseManipCtor();                                   // 0x005b0f80 (thiscall)
    RotationHandle* Init();
    RotationHandle* Destroy(uint32_t flags);
    void SetInput(Handle* h, Vector3 a, Vector3 b);
    bool DoOnMouseDown(float unused, float x, float y, uint32_t z);
    PileList* GetPileCopy(PileList* out) const;
    void Update(float x, float y);
};

// ---------------------------------------------------------------- 0x005b5110
// @ 0x005b5110
void RotationHandle::SetInput(Handle* h, Vector3 a, Vector3 b)
{
    mMouseOffset = a;
    mCameraPlanePoint = b;
    mTimeSpentSnapped = 0.0f;
    mRotationHandle = h;
    mBlock = mRotationHandle->GetEditorBlock();
}

// ---------------------------------------------------------------- 0x005b53c0
// @ 0x005b53c0
RotationHandle* RotationHandle::Init()
{
    BaseManipCtor();
    *(void* volatile*)&vtbl14 = vtbl_13ec458;
    d18 = 0;
    *(void* volatile*)&vtbl0 = vtbl_13f7634;
    *(void* volatile*)&vtbl14 = vtbl_13f7624;
    mRotationHandle.mpObject = 0;
    mBlock.mpObject = 0;
    mPileList.mpBegin = 0;
    mPileList.mpEnd = 0;
    mPileList.mpCapacity = 0;
    mMouseOffset.x = 0.0f;
    mMouseOffset.y = 0.0f;
    mMouseOffset.z = 0.0f;
    mOutsideInitialSnapRange = 0;
    d154 = 0;
    bFlag04 = 0;
    mHistoryAppliedRoll = 0.0f;
    mTimeSpentSnapped = 0.0f;
    mTargetRoll = 0.0f;
    mActualRoll = 0.0f;
    mSymmetryModifier = kOneConst;
    mX = 0.0f;
    mY = 0.0f;
    return this;
}

// ---------------------------------------------------------------- 0x005b5900
// @ 0x005b5900
bool RotationHandle::DoOnMouseDown(float unused, float x, float y, uint32_t z)
{
    (void)unused;
    mX = x;
    mY = y;
    f0c = x;
    f10 = y;
    d154 = z;
    Update(x, y);
    mBlock->Refresh();
    mBlock->F3cfc0((int)mRotationHandle.mpObject, 1);
    mRotationHandle->SetState(2, 1);
    return false;
}

// ---------------------------------------------------------------- 0x005b5980
// @ 0x005b5980
PileList* RotationHandle::GetPileCopy(PileList* out) const
{
    int count = (int)((char*)mPileList.mpEnd - (char*)mPileList.mpBegin) >> 2;
    PileList* p = out;
    p->VectorCtor(count, (void*)&mPileList.mAllocator);
    CopyAddRefPtrs((void**)&out, (void**)mPileList.mpBegin, (void**)mPileList.mpEnd, (void**)p->mpBegin, out);
    p->mpEnd = out;
    return p;
}

// ---------------------------------------------------------------- 0x005b59d0
// @ 0x005b59d0
RotationHandle* RotationHandle::Destroy(uint32_t flags)
{
    vtbl0 = vtbl_13f7634;
    vtbl14 = vtbl_13f7624;
    mPileList.Dtor();
    if (mBlock.mpObject) mBlock.mpObject->Release();
    if (mRotationHandle.mpObject) mRotationHandle.mpObject->Release();
    vtbl14 = vtbl_13ec458;
    vtbl0 = vtbl_13eb938;
    if (flags & 1) OpDelete(this);
    return this;
}

// ---------------------------------------------------------------- 0x005b51b0
struct cTransform {
    uint16_t flags;      // +0x00
    uint16_t count;      // +0x02
    uint8_t  pad04[0x10];
    Matrix3  rotation;   // +0x14
    void PreRotate(const Matrix3& m);
};

// @ 0x005b51b0
void cTransform::PreRotate(const Matrix3& m)
{
    if (flags & 2) {
        Matrix3 t;
        t.row[0].x = m.row[0].x * rotation.row[0].x + m.row[0].y * rotation.row[1].x + m.row[0].z * rotation.row[2].x;
        t.row[0].y = m.row[0].x * rotation.row[0].y + m.row[0].y * rotation.row[1].y + m.row[0].z * rotation.row[2].y;
        t.row[0].z = m.row[0].x * rotation.row[0].z + m.row[0].y * rotation.row[1].z + m.row[0].z * rotation.row[2].z;
        t.row[1].x = m.row[1].x * rotation.row[0].x + m.row[1].y * rotation.row[1].x + m.row[1].z * rotation.row[2].x;
        t.row[1].y = m.row[1].x * rotation.row[0].y + m.row[1].y * rotation.row[1].y + m.row[1].z * rotation.row[2].y;
        t.row[1].z = m.row[1].x * rotation.row[0].z + m.row[1].y * rotation.row[1].z + m.row[1].z * rotation.row[2].z;
        t.row[2].x = m.row[2].x * rotation.row[0].x + m.row[2].y * rotation.row[1].x + m.row[2].z * rotation.row[2].x;
        t.row[2].y = m.row[2].x * rotation.row[0].y + m.row[2].y * rotation.row[1].y + m.row[2].z * rotation.row[2].y;
        t.row[2].z = m.row[2].x * rotation.row[0].z + m.row[2].y * rotation.row[1].z + m.row[2].z * rotation.row[2].z;
        rotation = t;
    } else {
        rotation = m;
        flags |= 2;
    }
    ++count;
}

// ---------------------------------------------------------------- 0x005b5470
// @ 0x005b5470
void RotationHandle::Update(float x, float y)
{
    if (mBlock.mpObject == 0 || mRotationHandle.mpObject == 0)
        return;

    mOutsideInitialSnapRange = 0;
    mHistoryAppliedRoll = 0.0f;
    BuildPileList(mBlock.mpObject, &mPileList, 0);
    PileSetup((char*)mBlock.mpObject, &mPileList);

    mGeometryOrientation = kIdentityMatrix;
    mTargetRoll = 0.0f;
    mActualRoll = 0.0f;

    Block* b = mBlock.mpObject;
    const Matrix3* pParent;
    if (b->mParentBlock != 0)
        pParent = &b->mParentBlock->mOrientation;
    else
        pParent = &kIdentityMatrix;
    mParentOrientation = *pParent;

    mInitialUserOrientation = b->mHistoryUserOrientation;
    mBaseOrientation = b->mHistoryBaseOrientation;
    mRotationModifier = kIdentityMatrix;

    Vector3 origin, dir;
    App()->GetViewer()->GetWorldRayFromScreenCoords(x, y, &origin, &dir);

    if (mRotationHandle->GetType() != 0x50a2ed2)
        return;

    Ring* ring = mRotationHandle.mpObject ? (Ring*)mRotationHandle.mpObject->Cast(0x50a2ed2) : 0;

    Vector3 fwd = ring->GetForwardVector(false);
    mBlockHistoryForward = MulVecMat(fwd, b->mHistoryOrientation);
    mRotationAxis = MulVecMat(ring->GetRotationAxis(false), mInitialUserOrientation);

    Matrix3 local;
    MatMul(&local, &b->mHistoryUserOrientation, &b->mHistoryBaseOrientation);

    Vector3 v = MulVecMat(ring->GetRotationAxis(false), local);

    float inv = (float)(1.0 / sqrt((double)v.x * (double)v.x + (double)v.y * (double)v.y + (double)v.z * (double)v.z));
    mPlaneNormal = v * inv;

    float planeD = -(mPlaneNormal.x * b->mHistoryPosition.x + mPlaneNormal.y * b->mHistoryPosition.y + mPlaneNormal.z * b->mHistoryPosition.z);
    float denom = mPlaneNormal.x * dir.x + mPlaneNormal.y * dir.y + mPlaneNormal.z * dir.z;
    if (denom != 0.0f) {
        float t = -((origin.x * mPlaneNormal.x + origin.y * mPlaneNormal.y + origin.z * mPlaneNormal.z) + planeD) / denom;
        if (t >= 0.0f)
            mInitialClickPosition = origin + dir * t;
    }
}