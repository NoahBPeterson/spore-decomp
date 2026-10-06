// Slice s0044c690: SP::cSPEditorBlock::CalculateSnapAxes (3673 bytes, /Od /Ob1).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od module, no /EHsc).
//
// Casts a ray along each snap axis (computed from an angle list property, or evenly spread around the
// circle) from the block model's own transform (temporarily reset to identity), records for each axis
// the surface triangle it pins to and the pick-point origin in model space, then restores the transform.
#include "types.h"
#include <math.h>

void* operator new(unsigned int size, const char* name, int, int, int, int);

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)
inline float Abs(float x) { float r = (float)fabs(x); return r; }
inline float Cos(float x) { return cosf(x); }
inline float Sin(float x) { return sinf(x); }

inline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    float& operator[](int i) { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3(const cSPVector3& o);                                     // 0x004098a0
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

struct Matrix33T {                                                       // rw::math::fpu::Matrix33Template<float,0>
    Vector3T mRow[3];
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const cSPMatrix3& o);                                     // 0x0041cb40
};

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3T mTranslation;
    float mScale;
    Matrix33T mRotation;
    cSPTransform(const cSPTransform& o);                                 // 0x0040ce80
    cSPTransform& operator=(const cSPTransform& o);                      // 0x00537dc0
    void SetTranslation(const Vector3T& v);                              // 0x0044d4f0
};

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    Vector3T GetCenter() const;                                          // 0x00409b90
};

Vector3T operator+(const Vector3T& a, const Vector3T& b);                // 0x0041dc10
Vector3T operator-(const Vector3T& a, const Vector3T& b);                // 0x0041db10
Vector3T operator-(const Vector3T& v);                                   // 0x00422020
Vector3T operator*(const Vector3T& a, const float& s);                   // 0x0041dca0
Vector3T operator*(const Vector3T& v, const Matrix33T& m);               // 0x0041daf0
Matrix33T Inverse(const Matrix33T& m);                                   // 0x0041ded0
Vector3T* Normalize(Vector3T* out, const Vector3T* v);                   // 0x00436ce0 (cdecl)

extern const Matrix33T kIdentityRot;    // 0x015d2428
extern const Vector3T kZeroPos;        // 0x015d255c
extern float kTwoPi;                     // 0x015d2470
extern float kHalfPi;                    // 0x015d257c

namespace EA {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
};
}

namespace eastl {
struct sp_vector_allocator { sp_vector_allocator() {} };
}

namespace SP {
class cSPEditorBlock;

struct cSPEditorTrianglePinningInfo {
    char pad00[4];
    void* mTriangle;                                                     // +4
    char pad08[0x44];
    cSPEditorTrianglePinningInfo();                                      // 0x004e8f70
    void Init(cSPEditorBlock* owner, int triIndex, bool useHull);        // 0x004e9500
    void SetPosition(cSPEditorBlock* owner, void* tri, cSPVector3 pos, int a, int b);  // 0x004e9050
};

struct cSPEditorSnapVector {
    Vector3T mNormal;
    Vector3T mOrigin;
    cSPEditorTrianglePinningInfo* mTriangleInfo;
    bool mLockToAxis;
};

struct SnapVector {   // eastl::vector<cSPEditorSnapVector, sp_vector_allocator>
    cSPEditorSnapVector* mpBegin;
    cSPEditorSnapVector* mpEnd;
    cSPEditorSnapVector* mpCapacity;
    void erase(cSPEditorSnapVector* first, cSPEditorSnapVector* last);   // 0x00454dc0
    void resize(int n);                                                  // 0x00453e20
    void clear() { erase(mpBegin, mpEnd); }
};

struct BlockVector {   // eastl::vector<EA::AutoRefCount<cSPEditorBlock>, sp_vector_allocator>
    EA::AutoRefCount<cSPEditorBlock>* mpBegin;
    EA::AutoRefCount<cSPEditorBlock>* mpEnd;
    EA::AutoRefCount<cSPEditorBlock>* mpCapacity;
    BlockVector(const eastl::sp_vector_allocator& a = eastl::sp_vector_allocator());  // 0x00540470
    ~BlockVector();                                                      // 0x00453eb0
    void push_back(const EA::AutoRefCount<cSPEditorBlock>& v);           // 0x004541f0
};

struct Property {
    char data[8];
    int mCount;                  // +8
    char pad0c[4];
    uint16_t mFlags;             // +0x10
    uint16_t mType;              // +0x12
    float* GetFloat();           // 0x0041ea70
    int GetCount() {
        if (mFlags & 0x30)
            return mCount;
        else if (mType != 0)
            return 1;
        return 0;
    }
    float* GetData() {
        if (mFlags & 0x30)
            return *(float**)this;
        else if (mType != 0)
            return (float*)this;
        return 0;
    }
};

struct cPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);                               // +0x1c
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);               // +0x24
    virtual Property* GetPropertyData(uint32_t id);                      // +0x28
};

struct cMWModel {
    char pad00[8];
    cSPTransform mTransform;                                             // +0x08
};

namespace EditorUtils {
cSPEditorBlock* PickBlocks(BlockVector& ignore, cSPVector3 start, cSPVector3 dir,
                           cSPVector3& hitPos, cSPVector3& hitNormal, int* pIndex,
                           bool& bHit, int* pLevel);                     // 0x004a4840
}

class cSPEditorBlock {
public:
    virtual void v00();
    virtual int AddRef();                                                // +0x04
    virtual int Release();                                               // +0x08

    char pad04[8];
    EA::AutoRefCount<cPropertyList> mPropList;                           // +0x0c (as raw pointer)
    EA::AutoRefCount<cMWModel> mModel;                                   // +0x10
    char pad14[0x234 - 0x14];
    SnapVector mSnapAxes;                                                // +0x234
    char pad240[0x248 - 0x240];
    int mSnapAxesCount;                                                  // +0x248

    cSPBoundingBox GetBBox(bool a, bool b, bool c);                      // 0x0044ae00
    Vector3T GetPickOrigin(int a);                                     // 0x0043d240
    void CalculateSnapAxes();
};
}  // namespace SP

using namespace SP;

// @ 0x0044c690
void cSPEditorBlock::CalculateSnapAxes()
{
    mSnapAxes.clear();
    if (mSnapAxesCount > 0) {

    cSPTransform savedTransform(mModel->mTransform);
    {
        cSPTransform& t = mModel->mTransform;
        t.mRotation = kIdentityRot;
        t.mScale = 1.0f;
        t.mTranslation = kZeroPos;
        t.mFlags = 0;
        t.mModificationCount = 0;
    }

    BlockVector blocks;
    {
        EA::AutoRefCount<cSPEditorBlock> self(this);
        blocks.push_back(self);
    }

    cSPBoundingBox bbox = GetBBox(true, false, false);
    float zOffset = bbox.GetCenter()[2];
    if (mPropList->HasProperty(0x4f7ae2c)) {
        cPropertyList* pl = mPropList.mpObject;
        Property* prop;
        if (pl && pl->GetProperty(0x4f7ae2c, &prop) && prop->mType == 0xd)
            zOffset = *prop->GetFloat();
        zOffset = Clamp(zOffset, 0.0f, 1.0f);
        float lo = bbox.mMin[2];
        float range = bbox.mMax[2] - lo;
        range = range * zOffset;
        zOffset = lo + range;
    }

    if (mPropList->HasProperty(0x4f7dc1d)) {
        Property* angles = mPropList->GetPropertyData(0x4f7dc1d);
        mSnapAxesCount = angles->GetCount();
        float* data = angles->GetData();
        mSnapAxes.resize(mSnapAxesCount);
        for (int i = 0; i < mSnapAxesCount; i++) {
            float deg = data[i];
            if (fmodf(deg, 90.0f) == 0.0f)
                mSnapAxes.mpBegin[i].mLockToAxis = true;
            float rad = data[i] / 360.0f * kTwoPi;
            float c = Cos(rad);
            float s = Sin(rad);
            cSPVector3 dir(c, s, 0.0f);
            Vector3T n;
            Normalize(&n, &dir);
            mSnapAxes.mpBegin[i].mNormal = n;
        }
    } else {
        mSnapAxes.resize(mSnapAxesCount);
        float step = kTwoPi / (float)mSnapAxesCount;
        float angle = 0.0f;
        if (mPropList->HasProperty(0x4f7b20c)) {
            cPropertyList* pl = mPropList.mpObject;
            Property* prop;
            if (pl && pl->GetProperty(0x4f7b20c, &prop) && prop->mType == 0xd)
                angle = *prop->GetFloat();
            angle = angle / 360.0f * kTwoPi;
        }
        for (int i = 0; i < mSnapAxesCount; i++) {
            float a = angle;
            float m = kHalfPi;
            float r = fmodf(a, m);
            if (Abs(r) <= 1.1754944e-38f)
                mSnapAxes.mpBegin[i].mLockToAxis = true;
            float c = Cos(angle);
            float s = Sin(angle);
            cSPVector3 dir(c, s, 0.0f);
            Vector3T n;
            Normalize(&n, &dir);
            mSnapAxes.mpBegin[i].mNormal = n;
            angle += step;
        }
    }

    for (int i = 0; i < mSnapAxesCount; i++) {
        cSPVector3 axis(mSnapAxes.mpBegin[i].mNormal);
        cSPVector3 d0;
        d0 = axis * mModel->mTransform.mRotation;
        Vector3T e0 = GetPickOrigin(0);
        e0[2] = 0.0f;
        mModel->mTransform.SetTranslation(e0);
        float k = 100.0f;
        cSPVector3 ro;
        ro = e0 + d0 * k;
        ro[2] += zOffset;
        int hitIndex = -1;
        bool bHit = false;
        cSPVector3 hitPos;
        cSPVector3 hitNormal;
        if (!EditorUtils::PickBlocks(blocks, ro, -d0, hitPos, hitNormal, &hitIndex, bHit, 0) ||
            hitIndex == -1) {
            mSnapAxes.clear();
            break;
        }
        cSPEditorTrianglePinningInfo* info = new ("Editor", 0, 0, 0, 0) cSPEditorTrianglePinningInfo();
        mSnapAxes.mpBegin[i].mTriangleInfo = info;
        mSnapAxes.mpBegin[i].mTriangleInfo->Init(this, hitIndex, bHit);
        mSnapAxes.mpBegin[i].mTriangleInfo->SetPosition(this, mSnapAxes.mpBegin[i].mTriangleInfo->mTriangle, hitPos, 0, 0);
        cSPVector3 p;
        p = hitPos - mModel->mTransform.mTranslation;
        p = p * Inverse(mModel->mTransform.mRotation);
        p[2] = 0.0f;
        if (mSnapAxes.mpBegin[i].mLockToAxis) {
            if (Abs(p[0]) > 0.5f)
                p[1] = GetPickOrigin(0)[1];
            else if (Abs(p[1]) > 0.5f)
                p[0] = GetPickOrigin(0)[0];
        }
        mSnapAxes.mpBegin[i].mOrigin = p;
    }
    mModel->mTransform = savedTransform;
    }
}
