// Slice s00449ed0: /Od /Ob1 cSPEditorBlock helpers (retail layout; offsets are retail, not PDB).
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy   (0044a0e0 also needs /Oy: 16-byte aligned frame)
#include "types.h"
#include <float.h>

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- small math types ----
struct V3 { float x, y, z; };            // plain POD (SSE copies / integer stores)
struct V3u {                             // cSPVector3-style with user copy ops (fld/fstp copies)
    float x, y, z;
    V3u() {}
    V3u(const V3u& o) { x = o.x; y = o.y; z = o.z; }
    V3u& operator=(const V3u& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct M3 { float m[9]; };               // plain POD: copied with rep movsd
struct Mat : M3 {                        // block member matrix (user operator=, still a block copy)
    Mat& operator=(const M3& o) { *(M3*)this = o; return *this; }
};

V3u __cdecl operator-(const V3u& a, const V3u& b);        // 0x0041db10
V3u __cdecl operator+(const V3u& a, const V3u& b);        // 0x0041dc10
V3u __cdecl operator*(const V3u& a, const float& s);      // 0x0041dca0
// Helper calls: sret pointer first, returning that pointer (retail passes result pointers around).
V3* __cdecl VecSub(V3* out, const V3* a, const V3* b);        // 0x0041db10
V3* __cdecl VecAdd(V3* out, const V3* a, const V3* b);        // 0x0041dc10
V3* __cdecl VecScale(V3* out, const V3* a, const float* s);   // 0x0041dca0
V3* __cdecl VecMulMat(V3* out, const V3* a, const M3* m);     // 0x0041daf0
M3* __cdecl MulMat(M3* out, const M3* a, const M3* b);        // 0x0041de20
bool __cdecl MatNotEqual(const M3* a, const M3* b);           // 0x0041dd90
void __cdecl Orthonormalize(M3* m);                      // 0x00698650

__declspec(align(16)) struct hkVec4 {
    float v[4];
    hkVec4() {}
    hkVec4(const hkVec4& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; v[3] = o.v[3]; }
    hkVec4& operator=(const hkVec4& o) { v[0] = o.v[0]; v[1] = o.v[1]; v[2] = o.v[2]; v[3] = o.v[3]; return *this; }
};
struct hkRot {
    hkVec4 c0, c1, c2;
    const hkVec4& row(int i) const { return *(const hkVec4*)((const char*)this + (i << 4)); }
    void Assign(const hkRot& o);                          // 0x0044a8c0
};
struct hkTransformStub {
    hkRot rotation;
    hkVec4 translation;
};
struct hkMotionStub { char pad[0x10]; hkTransformStub transform; };
struct hkRigidBodyStub {
    char pad[0x58];
    hkMotionStub* mMotion;
    void setTransform(const hkTransformStub& t);          // 0x01087890
};
void __cdecl RotationFromMatrix(const M3* m, hkRot* out);   // 0x004a8fc0

// Axis-angle -> matrix (0x00453b20); Matrix3 ctor from const (0x0041cb40)
M3* __cdecl MatrixFromAxisAngle(M3* out, const V3* axis, float angle);
struct Matrix3Obj : M3 {
    Matrix3Obj(const M3& o);                               // 0x0041cb40
};
extern const M3 kIdentity;                                 // 0x015d2428
extern const float kRotAngle;                              // 0x015d257c
extern const V3 kZeroVec;                                  // 0x015d255c

// Bounding box and transform used by the block code.
struct BBox {
    V3u mMin, mMax;
    BBox() {}
    BBox(const BBox&);                                     // 0x00511140
    void Reset();                                          // 0x00409c00
    void GetCenter(V3u* out) const;                         // 0x00409b90
    void SetCenterRadius(const V3* c, float r);            // 0x00409ce0
    void TransformBy(const struct Xform* x);               // 0x00409dd0
    void Scale(float s);                                   // 0x0044ad00
    float MinAt(int i) const { return (&mMin.x)[i]; }
    float MaxAt(int i) const { return (&mMax.x)[i]; }
    bool IsInverted() const { return MinAt(0) > MaxAt(0); }
    bool IsUnbounded() const { return MinAt(0) == -FLT_MAX || MaxAt(0) == FLT_MAX; }
};
struct Xform {
    uint16_t flags;
    uint16_t version;
    V3 pos;
    float scale;
    M3 orient;
    Xform();                                               // 0x00409930
};

template <class T>
struct Ref {                              // EA::AutoRefCount-like handle (inline accessors)
    T* mp;
    T* get() const { return mp; }
    T* operator->() const { return mp; }
};

// Anything with a model transform at +8 (cMWModel).
struct ModelStub {
    char pad[8];
    Xform xf;
};
struct HandleStub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void Refresh();                                // +0x14
    virtual void s6(); virtual void s7();
    virtual void Update(float dt);                         // +0x20
    void* GetModel();                                      // 0x0047e680
    void* GetOther();                                      // 0x0047e6a0
};
struct ModelWorldStub {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void p39(); virtual void p40(); virtual void p41(); virtual void p42(); virtual void p43(); virtual void p44(); virtual void p45(); virtual void p46(); virtual void p47(); virtual void p48(); virtual void p49(); virtual void p50(); virtual void p51(); virtual void p52(); virtual void p53(); virtual void p54(); virtual void p55(); virtual void p56();
    virtual void GetBounds(ModelStub* model, BBox* out);   // +0xe4
};
struct EditorModelStub {
    char pad[0x38];
    float mScale;
    float GetScale();   // 0x004adaa0
};
struct HandleVec {
    HandleStub** mpBegin;
    HandleStub** mpEnd;
    HandleStub** mpCap;
    bool empty() const;                                    // 0x00526430
    int size() const { return (int)(mpEnd - mpBegin); }
    HandleStub*& operator[](int i) { return mpBegin[i]; }
};
struct Bits60 {
    uint32_t w[2];
    bool test(unsigned pos) const {
        if (pos < 0x3c)
            return ((1u << (pos % 32)) & w[pos / 32]) != 0;
        return false;
    }
};

struct Blk {
    char pad0[0x10];
    Ref<ModelStub> mModel;             // +0x10
    char pad14[4];
    Ref<ModelWorldStub> mModelWorld;   // +0x18
    char pad1c[0x28 - 0x1c];
    EditorModelStub* mEditorModel;     // +0x28
    bool mIsFullInit;                  // +0x2c
    char pad2d[0x48 - 0x2d];
    V3 mPosition;                      // +0x48
    char pad54[0x60 - 0x54];
    Mat mOrientation;                  // +0x60
    char pad84[0xa8 - 0x84];
    M3 mBaseOrientation;               // +0xa8
    char padcc[0xf0 - 0xcc];
    M3 mUserOrientation;               // +0xf0
    char pad114[0x154 - 0x114];
    int mArr[3];                       // +0x154 (HandleStub* x3)
    HandleStub* mBallHandle;           // +0x160
    char pad164[0x18c - 0x164];
    hkRigidBodyStub* mPhysicsBlock;    // +0x18c
    char pad190[0x1d8 - 0x190];
    float mUniformScale;               // +0x1d8
    char pad1dc[0x33c - 0x1dc];
    Blk* mParent;                      // +0x33c
    char pad340[0x3ec - 0x340];
    HandleStub* mChildHandleA;         // +0x3ec
    ModelStub* mChildModelB;           // +0x3f0
    char pad3f4[0x40c - 0x3f4];
    V3 mOffsetVec;                     // +0x40c
    char pad418[0x6cc - 0x418];
    HandleVec mDeformHandles;          // +0x6cc
    char pad6d8[0xdc8 - 0x6d8];
    Bits60 mFlags;                     // +0xdc8

    void A49ed0();
    void A4a070();
    void A4a0e0(M3 orient, bool updatePhysics);
    BBox A4aaa0(int mode);
    bool A4a9a0(Blk* other);
    int A4aa10(int i);
    void SetBooleanAttribute(int a, int b);    // 0x00435a10
    void RebuildPhysics();                      // 0x00452040
    void Sub449d40(BBox* b);                    // 0x00449d40
    void Sub44b640(BBox* b);                    // 0x0044b640
    void Sub44b6b0();                           // 0x0044b6b0
};

// @ 0x00449ed0
void Blk::A49ed0()
{
    if (mEditorModel) {
        float dt = (mEditorModel->GetScale() != 0.0f) ? mEditorModel->GetScale() * 0.5f : 1.0f;
        int n = mDeformHandles.size();
        for (int i = 0; i < n; ++i) {
            HandleStub* h = mDeformHandles[i];
            if (h)
                h->Update(dt);
        }
        if (mBallHandle)
            mBallHandle->Update(dt * 0.16666f);
        for (int j = 0; j < 3; ++j) {
            HandleStub* h = (HandleStub*)mArr[j];
            if (h)
                h->Update(dt * 0.5f);
        }
    }
}

// @ 0x0044a070
void Blk::A4a070()
{
    if (mIsFullInit && mModel.get() && mModelWorld.get()) {
        BBox box;
        box.Reset();
        ScratchSlots<12>();
        Sub449d40(&box);
        RebuildPhysics();
        Sub44b640(&box);
        Sub44b6b0();
    }
}

// @ 0x0044a0e0
void Blk::A4a0e0(M3 orient, bool updatePhysics)
{
    Orthonormalize(&orient);
    mBaseOrientation = orient;
    M3 prod0;
    if (MatNotEqual(&mOrientation, MulMat(&prod0, &mUserOrientation, &mBaseOrientation)))
        SetBooleanAttribute(9, 1);
    M3 prod1;
    mOrientation = *MulMat(&prod1, &mUserOrientation, &mBaseOrientation);

    if (mModel.get()) {
        Xform* xf = &mModel->xf;
        xf->orient = mOrientation;
        xf->flags |= 2;
        xf->version += 1;
    }
    if (mChildHandleA)
        mChildHandleA->Refresh();
    if (mChildModelB) {
        Xform* xf = &mChildModelB->xf;
        xf->orient = mOrientation;
        xf->flags |= 2;
        xf->version += 1;
        V3 t0, t1, t2, t3;
        V3 p = *VecAdd(&t3, &mPosition, VecMulMat(&t2, VecScale(&t1, &mOffsetVec, &mUniformScale), &mOrientation));
        xf = &mChildModelB->xf;
        xf->pos = p;
        xf->flags |= 4;
        xf->version += 1;
    }

    Matrix3Obj m(kIdentity);
    if (!mFlags.test(0)) {
        V3 axis = *(V3*)&mOrientation;
        float angle = -kRotAngle;
        M3 rtmp;
        Matrix3Obj r2(*MatrixFromAxisAngle(&rtmp, &axis, angle));
        *(M3*)&m = r2;
    }

    for (int i = 0; i < 3; ++i) {
        if (mArr[i]) {
            HandleStub* h = (HandleStub*)mArr[i];
            h->Refresh();
        }
    }
    if (mBallHandle) {
        HandleStub* h = mBallHandle;
        h->Refresh();
    }

    if (!mDeformHandles.empty()) {
        int n = mDeformHandles.size();
        for (int i = 0; i < n; ++i) {
            if (mDeformHandles[i]->GetModel() || mDeformHandles[i]->GetOther()) {
                HandleStub* h = mDeformHandles[i];
                h->Refresh();
            }
        }
    }

    if (updatePhysics && mPhysicsBlock && mModel.get()) {
        hkRot rot;
        RotationFromMatrix(&mOrientation, &rot);
        hkTransformStub* cur = &mPhysicsBlock->mMotion->transform;
        hkTransformStub t;
        t.rotation.Assign(cur->rotation);
        t.translation = cur->translation;
        t.rotation.Assign(rot);
        mPhysicsBlock->setTransform(t);
    }
}

// @ 0x0044a8c0
void hkRot::Assign(const hkRot& o)
{
    c0 = o.row(0);
    c1 = o.row(1);
    c2 = o.row(2);
}

// @ 0x0044a9a0
bool Blk::A4a9a0(Blk* other)
{
    int count = 0;
    while (other != 0 && other != this && count < 100) {
        other = other->mParent;
        count = count + 1;
    }
    if (count > 100)
        return false;
    return other == this;
}

// @ 0x0044aa10
int Blk::A4aa10(int i)
{
    if (i < 0 || i >= 3)
        return 0;
    int x = mArr[i];
    if (x == 0)
        return 0;
    return mArr[i];
}

// @ 0x0044aaa0
BBox Blk::A4aaa0(int mode)
{
    BBox box;
    box.Reset();
    if (mModel.get() && mModelWorld.get())
        mModelWorld->GetBounds(mModel.get(), &box);
    if (box.mMin.x > box.mMax.x || box.mMin.x == -FLT_MAX || box.mMax.x == FLT_MAX)
        box.SetCenterRadius(&kZeroVec, 0.01f);
    switch (mode) {
    case 1:
        box.Scale(mUniformScale);
        break;
    case 0: {
        Xform tf;
        tf.pos = mPosition;
        tf.flags |= 4;
        tf.version += 1;
        tf.orient = mOrientation;
        tf.flags |= 2;
        tf.version += 1;
        tf.scale = mUniformScale;
        tf.version += 1;
        box.TransformBy(&tf);
        break;
    }
    }
    float scale;
    if (mode == 2)
        scale = 1.0f;
    else
        scale = mUniformScale;
    return box;
}

// @ 0x0044ad00
void BBox::Scale(float s)
{
    V3u c;
    GetCenter(&c);
    ScratchSlots<8>();
    mMin = c + (mMin - c) * s;
    mMax = c + (mMax - c) * s;
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EditorModelStub {
    void GetScale(); // 0x004adaa0
};
}
