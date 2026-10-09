// Slice s00448fa0: cSPEditorBlock / bounding-box /Od /Ob1 helpers plus
// SP::normalized_safe (byte-exact).
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

float* sub_453880(float* tmp, const float* v, float* s);

// @ 0x00449c20  SP::normalized_safe  (byte-exact)
float* normalized_safe(float* out, const float* v)
{
    float v1 = v[0] * v[0] + v[1] * v[1] + v[2] * v[2] + 1e-8f;
    float p15 = sqrtf(v1);
    float n20[3];
    float* owner = sub_453880(n20, v, &p15);
    out[0] = owner[0];
    out[1] = owner[1];
    out[2] = owner[2];
    return out;
}

// ---------------------------------------------------------------------------
// SP::cSPEditorBlock members (retail layout, see s0044f7c0 for the full field list).
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct V3x : Vector3 {                          // Vector3 whose copy ctor is out of line (0x004098a0)
    V3x(const V3x& v);
};
struct Matrix3 {
    Vector3 r[3];
    Matrix3() {}
    Matrix3(const Matrix3& other);              // 0x0041cb40 (out of line)
    Vector3& operator[](int i) { return r[i]; }
};
struct cSPMatrix3 : Matrix3 {                   // ctors are out of line
    cSPMatrix3();                               // 0x00402ab0
    cSPMatrix3(const cSPMatrix3& o);            // 0x00449cc0
};
Vector3 operator-(const Vector3& v);                               // 0x00422020
Vector3& operator*=(Vector3& a, const float& s);                   // 0x0041dba0
Vector3 Normalize(const Vector3& v);                               // 0x00436ce0
Vector3 normalized_safe(const Vector3& v);                         // 0x00449c20 (value-returning view)
Vector3 Cross(const Vector3& a, const Vector3& b);                 // 0x00454c00
cSPMatrix3 MakeOrientation(const Vector3& fwd, const Vector3& up);    // 0x004a89e0
extern const Vector3 kAxis15d23f0, kAxis15d2478, kAxis15d23a8;

Matrix3 MirrorMatrix(const Matrix3& m, int flags);   // 0x004a8e10
bool operator!=(const Vector3& a, const Vector3& b);               // 0x0041dd30
Vector3 operator*(const Vector3& a, const float& s);               // 0x0041dca0
Vector3 operator*(const Vector3& v, const Matrix3& m);             // 0x0041daf0
Vector3 operator+(const Vector3& a, const Vector3& b);             // 0x0041dc10
extern const float kZero;                                          // 0x01485378

template <class T>
struct AutoRefCount {
    T* mpObject;
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
template <class T>
struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator;
    bool empty();                                                  // 0x00526430
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(size_t i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

struct __declspec(align(16)) hkVector4 {
    float x, y, z, w;
    hkVector4(float ax, float ay, float az, float aw) : x(ax), y(ay), z(az), w(aw) {}
};
struct hkRigidBody { void setPosition(const hkVector4& p); };      // 0x01087820

// the transform record at +8 of a cMWModel / handle model: flags, version, position
struct XformRec {
    uint16_t flags; uint16_t version; Vector3 pos;
};
struct cMWModel {
    char pad0[8];
    XformRec mXform;
};
struct cModelNode { char pad0[8]; XformRec mXform; };

struct cIModelWorld {
virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39(); virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66();
    virtual bool v67(cMWModel* m, void* bbox);   // +0x10c
    virtual bool v68(cMWModel* m, void* bbox);   // +0x110
};
struct cPropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual bool HasProperty(uint32_t id);
};
struct cSPEditorModel {
    bool IsSymmetryEnabled();                                      // 0x004adc40
};
struct cSPEditorHandle {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Update();                                         // +0x14
};
struct cSPBoundingBox { cSPBoundingBox(); Vector3 mMin, mMax; void Reset(); };   // 0x00409c00

struct cSPEditorBlock {
    char pad00[0x0c];
    AutoRefCount<cPropertyList> mPropList;                         // +0x0c
    AutoRefCount<cMWModel> mModel;                                 // +0x10
    char pad14[0x04];
    AutoRefCount<cIModelWorld> mModelWorld;                        // +0x18
    char pad1c[0x28 - 0x1c];
    cSPEditorModel* mEditorModel;                                  // +0x28
    char pad2c[0x48 - 0x2c];
    Vector3 mPosition;                                             // +0x48
    char pad54[0x60 - 0x54];
    Matrix3 mMat60;                                                // +0x60
    char pad84[0xa8 - 0x84];
    Matrix3 mOrientation;                                          // +0xa8
    char padcc[0x154 - 0xcc];
    AutoRefCount<cSPEditorHandle> mRotationRingHandles[3];         // +0x154
    AutoRefCount<cSPEditorHandle> mRotationBallHandle;             // +0x160
    char pad164[0x18c - 0x164];
    hkRigidBody* mPhysicsBody;                                     // +0x18c
    char pad190[0x1d8 - 0x190];
    float mScale;                                                  // +0x1d8
    char pad1dc[0x3e0 - 0x1dc];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;                  // +0x3e0
    char pad3e4[0x3ec - 0x3e4];
    AutoRefCount<cSPEditorHandle> mField3ec;                       // +0x3ec
    AutoRefCount<cMWModel> mField3f0;                              // +0x3f0
    char pad3f4[0x40c - 0x3f4];
    Vector3 mOffset40c;                                            // +0x40c
    char pad418[0x6cc - 0x418];
    vector<AutoRefCount<cSPEditorHandle> > mMorphHandles;          // +0x6cc
    char pad6dc[0xdc8 - 0x6dc];
    bitset<60> mFlags;                                             // +0xdc8

    void SetBooleanAttribute(int index, bool value);               // 0x00435a10
    Vector3 GetPosition();                                         // 0x00436210
    void ApplyOrientation(Matrix3 m, bool flag);                   // 0x0044a0e0
    void UpdateAfterClone();                                       // 0x0044a070

    void A48fa0(Vector3 pos, bool updatePhysics);
    void A49420(const Matrix3& m, bool flag);
    cSPMatrix3 A494b0(Vector3 dir);
    void A49ce0();
    void A49d40(cSPBoundingBox* bbox);
};

// @ 0x00448fa0
void cSPEditorBlock::A48fa0(Vector3 pos, bool updatePhysics)
{
    if (mPosition != pos)
        SetBooleanAttribute(9, true);
    mPosition = pos;
    if (mModel) {
        cMWModel* model = mModel;
        XformRec* x = &model->mXform;
        x->pos = mPosition;
        x->flags |= 4;
        x->version += 1;
    }
    if (mField3ec)
        mField3ec->Update();
    if (mField3f0) {
        Vector3 v = mPosition + mOffset40c * mScale * mMat60;
        cMWModel* model = mField3f0;
        XformRec* x = &model->mXform;
        x->pos = v;
        x->flags |= 4;
        x->version += 1;
    }
    for (int i = 0; i < 3; i++) {
        if (mRotationRingHandles[i])
            mRotationRingHandles[i]->Update();
    }
    if (mRotationBallHandle)
        mRotationBallHandle->Update();
    if (!mMorphHandles.empty()) {
        int count = mMorphHandles.size();
        for (int i = 0; i < count; i++) {
            if (mMorphHandles.mpBegin[i])
                mMorphHandles.mpBegin[i]->Update();
        }
    }
    if (updatePhysics && mPhysicsBody) {
        Vector3 p = GetPosition();
        float x = p[0];
        float y = p[1];
        float z = p[2];
        hkVector4 v(x, y, z, kZero);
        mPhysicsBody->setPosition(v);
    }
}

// @ 0x00449420
void cSPEditorBlock::A49420(const Matrix3& m, bool flag)
{
    uint32_t unusedFrame[12];
    ApplyOrientation(m, flag);
    if (mEditorModel && mEditorModel->IsSymmetryEnabled()) {
        cSPEditorBlock* sym = mSymmetricBlock;
        if (sym)
            sym->ApplyOrientation(MirrorMatrix(mOrientation, 0), flag);
    }
}

// @ 0x00449ce0
void cSPEditorBlock::A49ce0()
{
    UpdateAfterClone();
    cSPEditorBlock* sym = mSymmetricBlock;
    if (sym && mEditorModel->IsSymmetryEnabled() && mEditorModel)
        mSymmetricBlock->UpdateAfterClone();
}

// @ 0x00449d40
void cSPEditorBlock::A49d40(cSPBoundingBox* bbox)
{
    bool ok;
    if (bbox)
        bbox->Reset();
    if (!mFlags.test(10) || mFlags.test(7)) {
        ok = mModelWorld->v67(mModel, bbox);
        if (mPropList && mPropList->HasProperty(0xf9efc0)) {
            bool ok2 = mModelWorld->v68(mModel, bbox);
            ok = (ok && ok2) ? 1 : 0;
        }
    }
}

// @ 0x004494b0
cSPMatrix3 cSPEditorBlock::A494b0(Vector3 dir)
{
    if (mFlags.test(0xb))
        return *(cSPMatrix3*)&mMat60;
    cSPMatrix3 q;
    bool ok = (mEditorModel ? mEditorModel->IsSymmetryEnabled() : true) && mFlags.test(0xf);
    bool last = mFlags.test(0x22) || ok;
    Vector3 v18 = Vector3(-dir);
    if (last) {
        V3x a((const V3x&)kAxis15d23f0);
        V3x bb((const V3x&)kAxis15d2478);
        if (mPosition[0] < kZero) {
            a *= -1.0f;
            bb *= -1.0f;
        }
        V3x cc((const V3x&)kAxis15d23a8);
        q[0] = a;
        q[1] = bb;
        q[2] = cc;
    } else {
        Vector3 up = Vector3(-dir);
        up[2] = kZero;
        up = Normalize(up);
        q = MakeOrientation(up, kAxis15d23a8);
        if (mFlags.test(0x13)) {
            Vector3 r1 = Vector3(-kAxis15d23f0);
            Vector3 r0 = kAxis15d2478;
            if (mPosition[0] < kZero) {
                r0 *= -1.0f;
                r1 *= -1.0f;
            }
            r1[1] = kZero;
            r1 = normalized_safe(r1);
            Vector3 r2 = normalized_safe(Vector3(Cross(r0, r1)));
            if (r2[0] * r2[0] + r2[1] * r2[1] + r2[2] * r2[2] < 0.9f) {
                Matrix3 base(mMat60);
                r1 = base[1];
                r1[1] = kZero;
                r1 = Normalize(r1);
                r2 = Normalize(Vector3(Cross(r0, r1)));
            }
            q[0] = r0;
            q[1] = r1;
            q[2] = r2;
        }
    }
    return q;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct cSPEditorModel {
    void IsSymmetryEnabled(); // 0x004adc40
};
struct cSPMatrix3 {
    cSPMatrix3(); // 0x00402ab0
};
}
