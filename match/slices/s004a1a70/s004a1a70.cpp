// Slice s004a1a70: SP editor block/model helpers (symmetry/snap/replace).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <new>
#include <math.h>
#pragma intrinsic(fabs)

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
};
template<class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// rw::math::fpu::Vector3Template<float,0>: copy ctor is out of line (0x004098a0)
struct rwVec3 {
    float x, y, z;
    rwVec3() {}
    rwVec3(const rwVec3& v);                      // 0x004098a0
    rwVec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float& operator[](int i) { return (&x)[i]; }
};
struct rwMat3 {                                   // 3 rows of rwVec3
    rwVec3 r[3];
    rwMat3();                                     // 0x00402ab0
    rwMat3(const rwMat3& m);                      // 0x00449cc0
    rwVec3& operator[](int i) { return r[i]; }
};
struct BBox { rwVec3 mn, mx; };
struct Mat9 { float f[9]; };

struct Bitset60 {
    uint32_t w[2];
    bool test(uint32_t i) const
    {
        if (i < 60) {
            uint32_t word = w[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

class cSPEditorBlock;
typedef AutoRefCount<cSPEditorBlock> BlockRef;

struct Alloc {
    Alloc() {}
    Alloc(const Alloc& o);                              // 0x00429360
};
struct BlockVec {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapEnd;
    Alloc mAlloc;
    BlockVec(const Alloc& a);                          // 0x00540470 (out-of-line ctor)
    BlockVec() : mpBegin(0), mpEnd(0), mpCapEnd(0), mAlloc(Alloc()) {}
    ~BlockVec();                                       // 0x00453eb0
    void push_back(const BlockRef& r);                 // 0x004541f0
    void DoDestroy(BlockRef* first, BlockRef* last);   // 0x00454280
    BlockRef& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cSPEditorModel;
struct cSPEditorBlock {
    virtual void _v0();
    virtual void AddRef();                       // +4
    virtual void Release();                      // +8
    char pad0[0x28 - 4];
    cSPEditorModel* mpModel;                     // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3 mPosition;                        // +0x48
    char pad2[0x60 - 0x54];
    rwMat3 mOrientation;                         // +0x60
    char pad3[0xa8 - 0x84];
    float mBaseOrientation[9];                   // +0xa8
    char pad4[0x144 - 0xcc];
    cSPVector3 mField144;                        // +0x144
    char pad5[0x33c - 0x150];
    AutoRefCount<cSPEditorBlock> mParent;        // +0x33c
    char pad6[0x3e0 - 0x340];
    AutoRefCount<cSPEditorBlock> mPinTarget;     // +0x3e0
    char pad7[0xdc8 - 0x3e4];
    Bitset60 mFlags;                             // +0xdc8
    cSPEditorBlock* GetParent() const { return mParent; }
    cSPEditorModel* GetModel() const { return mpModel; }
    bool GetBooleanAttribute(uint32_t id) const { return mFlags.test(id); }
    void SetBooleanAttribute(int id, bool v);    // 0x435a10
    void FUN_4a1d60(const cSPVector3* p);        // @ 0x4a1d60
    void FUN_44ba20(int a, int b);               // 0x44ba20
    void FUN_44bcf0(int a, int b);               // 0x44bcf0
    bool FUN_44c030();                           // 0x44c030
    void FUN_44c0e0(int* a, int* b, int* c);     // 0x44c0e0 (picks an axis)
    BBox* GetBBox(BBox* out, int a, int b, int c);   // 0x44ae00
    void FUN_438a40(cSPEditorBlock* o);          // 0x438a40
    void FUN_438700(cSPEditorBlock* o);          // 0x438700
    void* GetA();                                // 0x4511f0
    void SetRef(void* r);                        // 0x451280
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
};
struct IMessageManager { void Post(uint32_t id, int a, void* data, int b); };   // 0x45ae40
struct IMessageServer { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                        virtual void Send(uint32_t id, int a, int b); };      // +0x14

void* FUN_00401060();                                               // editor context
IMessageManager* MessageManager();                                  // 0x401050
IMessageServer* MessageServer();                                    // 0x67dcc0
void BuildPileList(cSPEditorBlock* b, BlockVec* v, int flag);       // 0x48c790
void SetSymmetricBlocksUIState(cSPEditorBlock* b, int a, int c);    // 0x4a7f30
void FUN_4a6d20(cSPEditorBlock* b, int a, int c, int d, int e, int f, int g, int h);  // 0x4a6d20
bool FUN_4a1e10(cSPEditorBlock* block);          // defined below
void FUN_4a1d60g(cSPEditorBlock* b, const cSPVector3* p);
void FUN_43f050(BBox* acc, BBox* other);        // 0x43f050 (merge)
rwVec3* Mat3MulVec(rwVec3* out, rwVec3* v, rwMat3* m);   // 0x41daf0 (_Unchecked_idl0)

extern const cSPVector3 kSnapZero;               // 0x015d64d8

// @ 0x4a1d60
void cSPEditorBlock::FUN_4a1d60(const cSPVector3* p)
{
    mField144 = *p;
    if (mPinTarget) {
        cSPVector3 v = *p;
        v[0] *= -1.0f;
        mPinTarget->mField144 = v;
    }
}

// @ 0x4a2560
bool FUN_4a2560(cSPEditorModel* model)
{
    bool result = 0;
    if (model) {
        int i = 0;
        int n = model->GetBlockCount();
        for (; i < n; i++) {
            cSPEditorBlock* b = model->GetBlock(i);
            bool block = FUN_4a1e10(b);
            result = block || result;
        }
    }
    return result;
}

// @ 0x4a1a70
void FUN_4a1a70(void* unused, cSPEditorBlock* block)
{
    if (block) {
        if (!block->GetBooleanAttribute(0x2a)) {
            void* ctx = FUN_00401060();
            if (ctx) {
                rwVec3 v(*(rwVec3*)&block->mField144);
                Alloc al;
                BlockVec vec(al);
                {
                    BlockRef r(block);
                    vec.push_back(r);
                }
                BuildPileList(block, &vec, 0);
                for (int i = 0, n = vec.size(); i < n; i++) {
                    cSPEditorBlock* b = vec[i];
                    b->FUN_4a1d60((const cSPVector3*)&v);
                    b->SetBooleanAttribute(0x2a, true);
                    b->FUN_44ba20(0, 0);
                    if (b->mPinTarget) {
                        cSPEditorBlock* pin = b->mPinTarget;
                        pin->SetBooleanAttribute(0x2a, true);
                    }
                }
                if (block->mPinTarget) {
                    cSPEditorBlock* pin0 = block->mPinTarget;
                    v = *(rwVec3*)&pin0->mField144;
                    vec.DoDestroy(vec.mpBegin, vec.mpEnd);
                    {
                        BlockRef r(pin0);
                        vec.push_back(r);
                    }
                    BuildPileList(pin0, &vec, 0);
                    for (int i = 0, n = vec.size(); i < n; i++) {
                        cSPEditorBlock* b = vec[i];
                        b->FUN_4a1d60((const cSPVector3*)&v);
                        b->SetBooleanAttribute(0x2a, true);
                        b->FUN_44ba20(0, 0);
                        if (b->mPinTarget) {
                            cSPEditorBlock* pin = b->mPinTarget;
                            pin->SetBooleanAttribute(0x2a, true);
                        }
                    }
                }
            }
            SetSymmetricBlocksUIState(block, 0, 0);
            FUN_4a6d20(block, 0, 0, 0, 0, 0, 1, 1);
        }
    }
}

// @ 0x4a1e10
// SP::EditorUtils::UnsnapReplaceBlock (PDB candidate)
bool FUN_4a1e10(cSPEditorBlock* block)
{
    bool result = false;
    if (block->GetBooleanAttribute(0x2a)) {
        void* ctx = FUN_00401060();
        if (ctx) {
            BlockVec vec;
            {
                BlockRef r(block);
                vec.push_back(r);
            }
            BuildPileList(block, &vec, 0);
            if (block->mPinTarget) {
                cSPEditorBlock* pin0 = block->mPinTarget;
                {
                    BlockRef r(pin0);
                    vec.push_back(r);
                }
                BuildPileList(pin0, &vec, 0);
            }
            for (int i = 0, n = vec.size(); i < n; i++) {
                cSPEditorBlock* b = vec[i];
                b->FUN_4a1d60(&kSnapZero);
                b->SetBooleanAttribute(0x2a, false);
                b->FUN_44bcf0(0, 0);
                if (b->mPinTarget) {
                    cSPEditorBlock* pin = b->mPinTarget;
                    pin->SetBooleanAttribute(0x2a, false);
                }
            }
        }
        if (!block->FUN_44c030())
            block->FUN_44bcf0(1, 1);
        SetSymmetricBlocksUIState(block, 0, 0);
        FUN_4a6d20(block, 0, 0, 0, 0, 0, 1, 1);
        MessageManager()->Post(0x3f1bf59, 0, block, 0);
        result = true;
    }
    return result;
}

// @ 0x4a2060
bool FUN_4a2060(cSPEditorBlock* block)
{
    if (block) {
        if (block->GetBooleanAttribute(7) || block->GetBooleanAttribute(0x14) || block->GetBooleanAttribute(1))
            return false;
        return true;
    } else {
        return false;
    }
}

extern const float kSnapScale;                   // 0x013ef578 (1.3f)

// @ 0x4a2180
rwVec3* FUN_4a2180(rwVec3* ret, cSPEditorBlock* a, cSPEditorBlock* b)
{
    int i0, axis, i2;                             // axis is the 2nd out value
    b->FUN_44c0e0(&i0, &axis, &i2);
    BBox bbA;
    a->GetBBox(&bbA, 1, 0, 0);
    BlockVec vec;
    BuildPileList(a, &vec, 0);
    for (int i = 0, n = vec.size(); i < n; i++) {
        BBox bbi;
        BBox* r = vec[i]->GetBBox(&bbi, 1, 0, 0);
        FUN_43f050(&bbA, r);
    }
    rwVec3 mn(bbA.mn);
    BBox bbB;
    b->GetBBox(&bbB, 1, 0, 0);
    rwVec3 mx(bbB.mx);
    rwVec3 d;
    d.x = 0.0f;
    d.y = 0.0f;
    d.z = 0.0f;
    d[axis] = (mn[axis] - mx[axis]) * kSnapScale;
    rwVec3 tmp;
    rwVec3* t = Mat3MulVec(&tmp, &d, &b->mOrientation);
    d.x = t->x;
    d.y = t->y;
    d.z = t->z;
    new (ret) rwVec3(d);
    return ret;
}

// @ 0x4a2350
// SP::EditorUtils::DoSnapReplace
bool FUN_4a2350(cSPEditorBlock* editor, cSPEditorBlock* src, rwVec3* outPos, float* outMat)
{
    bool result = false;
    if (src != 0) {
        *(Vector3T*)outPos = src->mPosition;
        *(Mat9*)outMat = *(Mat9*)src->mBaseOrientation;
        cSPEditorBlock* parent = src->GetParent();
        if (editor->mParent != parent) {
            if (editor->mParent) {
                editor->mParent->FUN_438a40(editor);
            }
            if (parent) {
                parent->FUN_438700(editor);
                editor->SetRef(src->GetA());
            }
        }
        editor->SetBooleanAttribute(0xf, src->GetBooleanAttribute(0xf));
        if (!src->GetBooleanAttribute(0x2a)) {
            MessageManager()->Post(0x3f1bf58, 0, editor, 0);
            rwVec3 d;
            src->FUN_4a1d60((const cSPVector3*)FUN_4a2180(&d, editor, src));
            FUN_4a1a70(editor, src);
        }
        result = true;
    } else {
        ScratchSlots<5>();
        bool changed = FUN_4a2560(editor->GetModel());
        if (changed)
            MessageManager()->Post(0x3f1bf59, 0, editor, 0);
        MessageServer()->Send(0x48e5912, 0, 0);
    }
    return result;
}

// ---- 0x4a25f0: build an orthonormal orientation from a base matrix and a snap mode ----
extern rwVec3 kUpAxis;                        // 0x015d6370
extern rwVec3 kBlendAxis;                     // 0x015d6324
rwVec3* Vec3Normalize(rwVec3* out, const rwVec3* in);              // 0x436ce0
rwVec3 Vec3Normalized(const rwVec3& in);                           // 0x436ce0 (by-value form)
rwVec3* Vec3Negate(rwVec3* out, const rwVec3* in);                 // 0x422020
rwVec3* Vec3Cross(rwVec3* out, const rwVec3* a, const rwVec3* b);  // 0x454c00
rwVec3* Vec3Lerp(rwVec3* out, const rwVec3* a, const rwVec3* b, float t);   // 0x413cc0
float Vec3Length(const rwVec3* v);                                 // 0x4885d0
extern const float kDegenerateEps;            // 0x013ef4c4 (1/65536)

// @ 0x4a25f0
rwMat3 FUN_4a25f0(rwMat3 m, int mode)
{
    rwMat3 result;
    rwVec3 up(m[1]);
    float a = (float)fabs((up.x * kUpAxis.x + up.y * kUpAxis.y) + up.z * kUpAxis.z);
    rwVec3 dir;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 0.0f;
    if (mode == 0) {
        static rwVec3 sNegX = Vec3Normalized(rwVec3(-1.0f, 0.0f, 0.0f));     // 0x015d60d8
        dir = sNegX;
    } else {
        static rwVec3 sPosX = Vec3Normalized(rwVec3(1.0f, 0.0f, 0.2f));      // 0x015d60cc
        static rwVec3 sNegX2 = Vec3Normalized(rwVec3(-1.0f, 0.0f, 0.2f));    // 0x015d60c0 (guard 0x015d60e4)
        rwVec3* p = (mode == 1) ? &sPosX : &sNegX2;
        rwVec3 base(*p);
        rwVec3 tmp;
        rwVec3* l = Vec3Lerp(&tmp, &base, &kBlendAxis, a);
        dir = *l;
    }
    rwVec3 tmp2;
    rwVec3 x(*Vec3Cross(&tmp2, &up, &dir));
    rwVec3 z;
    if (Vec3Length(&x) < kDegenerateEps) {
        rwVec3 t3;
        new (&x) rwVec3(*Vec3Negate(&t3, &kUpAxis));
        rwVec3 t4;
        new (&z) rwVec3(*Vec3Cross(&t4, &x, &up));
        rwVec3 t5;
        z = *Vec3Normalize(&t5, &z);
        rwVec3 t6;
        new (&up) rwVec3(*Vec3Cross(&t6, &z, &x));
    } else {
        rwVec3 t7;
        new (&z) rwVec3(*Vec3Cross(&t7, &x, &up));
        rwVec3 t8;
        z = *Vec3Normalize(&t8, &z);
    }
    rwVec3 t9;
    x = *Vec3Normalize(&t9, &x);
    result[0] = x;
    result[1] = up;
    result[2] = z;
    return result;
}
