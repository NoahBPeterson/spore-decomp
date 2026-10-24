// Slice s0049cfd0: SP editor symmetric-limb / transform helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

// ---- math types ----
struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T {
    Vector3T xAxis, yAxis, zAxis;
    Matrix33T() {}
    Matrix33T(const Matrix33T& m) : xAxis(m.xAxis), yAxis(m.yAxis), zAxis(m.zAxis) {}
    void Assign(const Matrix33T& m) { xAxis = m.xAxis; yAxis = m.yAxis; zAxis = m.zAxis; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const Matrix33T& m) : Matrix33T(m) {}
};
struct cSPTransform {
    unsigned short mFlags;
    unsigned short mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    void TransformVector(cSPVector3* out);   // @ 0x49d640
};

// ---- small shared types ----
struct AllocTag { char c; };
struct bitset60 {
    uint32_t mWord[2];
    bool test(uint32_t i) const {
        if (i < 60) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

// ---- global float constants ----
extern const float kEps;          // 0x13f9428
extern const float kNegEps;       // 0x13ef56c
extern const float kZeroF;        // 0x1485378
extern const float kOneF;         // 0x1485720
extern const float kOneAndHalfF;  // 0x1485548
extern const float kMirrorScale;  // 0x13eb1bc

// ---- block types ----
struct cSPEditorBlock;
struct cSPEditorModel;

struct BlockVec {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** mpEnd;
    cSPEditorBlock** mpCapacity;
    uint32_t mAllocator[2];
    BlockVec(const AllocTag&);                          // 0x540470
    ~BlockVec();                                        // 0x453eb0
    void Clear();                                       // 0x453770
    void AssignFrom(const BlockVec&);                   // 0x453f20
    void push_back(cSPEditorBlock* const& p);           // 0x4541f0
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock*& operator[](int i) { return mpBegin[i]; }
};

struct cSPEditorModel {
    void AddBlock(cSPEditorBlock* b, bool notify);      // 0x4abaf0
    bool UsingSymmetry();                               // 0x4adc40
    void FUN_4adc20(int v);                             // 0x4adc20
};

struct cSPEditorSkinManager {
    bool PickSkin(int pickId, cSPVector3 org, cSPVector3 dir,
                  cSPVector3* a, cSPVector3* b, float* t, int c);   // 0x4c4a30
    cSPEditorBlock* GetBlockOnSkin(int id, cSPVector3 v);           // 0x4c4d30
};

struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x18 - 4];
    int mModelWorld;                             // +0x18
    char pad1c[0x28 - 0x1c];
    cSPEditorModel* mpEditorModel;               // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3 mPosition;                        // +0x48
    char pad54[0x60 - 0x54];
    cSPMatrix3 mOrientation;                     // +0x60
    char pad84[0xa8 - 0x84];
    cSPMatrix3 mBaseOrientation;                 // +0xa8
    char padcc[0xf0 - 0xcc];
    cSPMatrix3 mUserOrientation;                 // +0xf0
    char pad114[0x138 - 0x114];
    cSPVector3 mSomeVec;                         // +0x138
    char pad144[0x1e0 - 0x144];
    float mMinUniformScale;                      // +0x1e0
    float mMaxUniformScale;                      // +0x1e4
    char pad1e8[0x33c - 0x1e8];
    cSPEditorBlock* mSymmetricBlock;             // +0x33c
    BlockVec mChildren;                          // +0x340
    char pad34c[0x3e0 - 0x354];
    cSPEditorBlock* mLinkedBlock;                // +0x3e0
    char pad3e4[0x3f0 - 0x3e4];
    cSPEditorBlock* mAttachPoint;                // +0x3f0
    char pad3f4[0xdc8 - 0x3f4];
    bitset60 mFlags;                             // +0xdc8

    bool FUN_435c80();                                      // 0x435c80
    void SetFlag(int flag, bool value);                     // 0x435a10
    float GetScaleF();                                      // 0x435c00
    int GetSomeId();                                        // 0x4511d0
    void RecursiveFlagB();                                  // 0x44eea0
    void RecursiveFlagC();                                  // 0x44efb0
    void AddChild(cSPEditorBlock* child);                   // 0x438700
    cSPVector3* F3e080(cSPVector3* out);                    // 0x43e080
    void SetPosition(const cSPVector3& p, bool notify);     // 0x448e90
    void SetOrientation(const cSPMatrix3& m, bool notify);  // 0x449420
    void SetUserOrientation(cSPMatrix3 m);                  // 0x43ffa0
    void SetSymmetrySign(int sign);                         // 0x44e980
    int GetSymmetrySign();                                  // 0x44f220
    float GetAnim();                                        // 0x43eed0
    void SetAnim(float f);                                  // 0x43eb50
    void SetModelBasedOnSymmetrySign(int sign, bool mirror, bool recurse, int a, int b);  // 0x439110
    void SetUniformScale(float v, int flag);                // 0x440090
};

// ---- helpers ----
cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m);   // @ 0x41daf0
cSPVector3 operator-(const cSPVector3& a, const cSPVector3& b);   // @ 0x41db10
cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b);   // @ 0x41dc10
cSPMatrix3 operator*(const cSPMatrix3& a, const cSPMatrix3& b);   // @ 0x41de20
cSPMatrix3* Matrix33_Convert(cSPMatrix3* out, const cSPMatrix3* in);  // @ 0x41ded0
void ScaleVector(cSPVector3* v, const float& s);                  // @ 0x41dba0
void Vector3_Normalize(cSPVector3* out, const cSPVector3* in);    // @ 0x436ce0
float VectorLength(const cSPVector3& v);                          // @ 0x40ae50
void NegateX(cSPVector3* out, const cSPVector3* in);              // @ 0x4a8f40
void* BuildFacingMatrix(void* out, const void* in, unsigned char axis);  // @ 0x4a8e10
cSPEditorBlock* FUN_4a0b70(int world, int id, float scale);       // @ 0x4a0b70
bool HasSymmetricLimb(cSPEditorBlock* block);                    // @ 0x4a5fe0
void SetSymmetricBlocksUIState(cSPEditorBlock* b, int a, int c); // @ 0x4a7f30
cSPMatrix3* FUN_49c140(cSPMatrix3* out, cSPEditorBlock* block, cSPVector3 v);   // @ 0x49c140
bool FUN_498470(cSPEditorBlock* block, cSPVector3* pos, cSPMatrix3* a,
                cSPMatrix3* b, int f0, float scale, int f1, int f2);           // @ 0x498470
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 pos, cSPMatrix3 orient, bool flag);  // @ 0x49fbd0

static float AbsF(float x) { return x < 0.0f ? -x : x; }

// @ 0x49d640
void cSPTransform::TransformVector(cSPVector3* out)
{
    if (mFlags & 2) {
        *out = *out * mRotation;
    }
    ScaleVector(out, mScale);
}

// @ 0x49dca0
float ClampAndSetScale(cSPEditorBlock* block, float value, bool clamp)
{
    if (clamp) {
        float tmp = block->mMinUniformScale;
        if (tmp > value) value = block->mMinUniformScale;
        float t14 = block->mMaxUniformScale;
        if (value > t14) value = block->mMaxUniformScale;
    }
    block->SetUniformScale(value, 0);
    return value;
}

// @ 0x49cfd0
void FUN_49cfd0(cSPEditorBlock* block)
{
    cSPEditorBlock* conn = block->mSymmetricBlock;
    if (conn == 0) return;
    if (!block->FUN_435c80()) return;
    if (conn->FUN_435c80()) return;
    cSPEditorBlock* sym = conn->mLinkedBlock;
    if (sym == 0) return;
    if (HasSymmetricLimb(sym)) return;

    sym->SetFlag(0x3a, true);
    sym->SetFlag(0x39, true);
    sym->RecursiveFlagB();
    sym->RecursiveFlagC();
    conn->SetFlag(0x3a, true);
    conn->SetFlag(0x39, true);
    conn->RecursiveFlagB();
    conn->RecursiveFlagC();

    cSPEditorBlock* nb = FUN_4a0b70(conn->mModelWorld, conn->GetSomeId(), conn->GetScaleF());
    if (nb == 0) return;
    conn->mpEditorModel->AddBlock(nb, true);
    nb->SetFlag(0xc, true);
    conn->AddChild(nb);

    cSPVector3 offset;
    conn->F3e080(&offset);
    cSPVector3 pos = conn->mPosition + offset;
    nb->SetPosition(pos, false);
    nb->SetSymmetrySign(-2);
    nb->SetAnim(block->GetAnim());
    nb->SetFlag(0x3a, false);
    nb->SetFlag(0x39, true);
    SetSymmetricBlocksUIState(nb, 0, 0);
}

// @ 0x49d1f0
void FUN_49d1f0(cSPEditorBlock* block, float scale, bool a, bool b)
{
    if (block == 0) return;
    if (block->FUN_435c80()) return;

    bool skip = false;
    if (a) {
        if (block->mFlags.test(0x1f)) skip = true;
    }
    if (!skip) {
        cSPVector3 pos;
        NegateX(&pos, &block->mPosition);
        pos.x = pos.x + scale * 2.0f;
        block->SetPosition(pos, false);

        cSPMatrix3 m;
        BuildFacingMatrix(&m, &block->mUserOrientation, 0);
        block->SetUserOrientation(m);

        cSPMatrix3 m2;
        BuildFacingMatrix(&m2, &block->mBaseOrientation, 0);
        block->SetOrientation(m2, false);

        if (b) {
            block->SetModelBasedOnSymmetrySign(-block->GetSymmetrySign(), false, false, 0, 0);
        }
    }

    BlockVec* vec = &block->mChildren;
    int n = vec->size();
    for (int i = 0; i < n; ++i) {
        FUN_49d1f0((*vec)[i], scale, a, b);
    }
}

// @ 0x49d390
void FUN_49d390(cSPEditorBlock* block, cSPTransform t0, cSPTransform t1, bool flag)
{
    (void)flag;
    cSPMatrix3 mc;
    cSPMatrix3* pm = Matrix33_Convert(&mc, &t0.mRotation);
    cSPVector3 d = block->mPosition - t0.mTranslation;
    cSPVector3 r = d * (*pm);
    r.x = r.x * kMirrorScale;
    cSPVector3 r2 = r * t1.mRotation;
    cSPVector3 res = r2 + t1.mTranslation;
    block->SetPosition(res, true);
}

// @ 0x49d550
void FUN_49d550(cSPEditorBlock* block, cSPTransform t0, cSPTransform t1, bool flag)
{
    (void)flag;
    cSPMatrix3 m;
    cSPMatrix3* pm = Matrix33_Convert(&m, &t0.mRotation);
    cSPMatrix3 a = block->mBaseOrientation * (*pm);
    BuildFacingMatrix(&a, &a, 0);
    cSPMatrix3 c = a * t1.mRotation;
    cSPMatrix3 d;
    BuildFacingMatrix(&d, &block->mUserOrientation, 0);
    block->SetUserOrientation(d);
    block->SetOrientation(c, true);
}

// @ 0x49d6b0
bool FUN_49d6b0(cSPEditorBlock* block, cSPVector3 a, cSPVector3 b,
                cSPEditorSkinManager* skin, bool flag, float dist)
{
    int sym = block->GetSymmetrySign();

    cSPVector3 n;
    Vector3_Normalize(&n, &b);
    b = n;
    if (AbsF(b.x) < kEps) {
        if (sym != 0) {
            b.x = (float)sym * kEps;
        }
        else {
            b.x = (b.x < 0.0f) ? kNegEps : kEps;
        }
        cSPVector3 n2;
        Vector3_Normalize(&n2, &b);
        b = n2;
    }

    cSPVector3 hit;
    cSPVector3 nrm;
    bool picked = skin->PickSkin(0, a, b, &hit, &nrm, 0, 0);
    cSPVector3 d = block->mPosition - hit;
    float len = VectorLength(d);
    if (!picked) return false;
    if (dist <= len) return false;

    bool noSym = (sym == 0);
    bool usingSym = block->mpEditorModel->UsingSymmetry();
    if (!noSym) {
        block->mpEditorModel->FUN_4adc20(0);
    }

    block->mSomeVec = nrm;

    cSPMatrix3 orient = block->mBaseOrientation;
    if (flag) {
        cSPMatrix3 res;
        FUN_49c140(&res, block, nrm);
        orient = res;
    }

    block->mpEditorModel->FUN_4adc20(0);
    RepinBlockToTorso(block, hit, orient, false);
    block->mpEditorModel->FUN_4adc20(usingSym);

    if (block->mFlags.test(0xf)) {
        float s = kOneF;
        if (block->mFlags.test(0x22)) s = kOneAndHalfF;

        cSPVector3 pos = block->mPosition;
        cSPMatrix3 o1 = block->mBaseOrientation;
        cSPMatrix3 o2 = block->mUserOrientation;
        bool ok = FUN_498470(block, &pos, &o1, &o2, 0, s, 0, 1);
        if (ok) {
            if (flag) {
                block->SetUserOrientation(o2);
            }
            else {
                o1 = block->mBaseOrientation;
            }
            RepinBlockToTorso(block, pos, o1, false);
        }
    }

    cSPEditorBlock* found = skin->GetBlockOnSkin(0, hit);
    found->AddChild(block);
    return true;
}

// @ 0x49dd20
bool FUN_49dd20(cSPEditorBlock* block, BlockVec* out, bool b)
{
    bool result = false;
    if (block != 0) {
        AllocTag tag;
        BlockVec tmp(tag);
        tmp.Clear();
        tmp.AssignFrom(block->mChildren);
        int n = tmp.size();
        for (int i = 0; i < n; ++i) {
            cSPEditorBlock* child = tmp[i];
            if (child->FUN_435c80()) {
                out->push_back(tmp[i]);
                result = true;
            }
            if (b) {
                bool sub = FUN_49dd20(child, out, b);
                result = (result || sub);
            }
        }
    }
    return result;
}
