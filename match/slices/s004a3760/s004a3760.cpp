// Slice s004a3760: SP editor screen-position / block search helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <float.h>

// ---------------------------------------------------------------------------
// Math / window types.
// ---------------------------------------------------------------------------
struct Vec3 {
    union {
        struct { float x, y, z; };
        float m[3];
    };
    float& operator[](int i) { return m[i]; }
    const float& operator[](int i) const { return m[i]; }
};
Vec3 operator-(const Vec3& a, const Vec3& b);           // 0x41db10
float VectorLength(const Vec3* v);                      // 0x40ae50

struct Vec4 { float x, y, z, w; };                      // main-window rect

// ---------------------------------------------------------------------------
// eastl::vector<unsigned, sp_vector_allocator> (4-byte elements).
// Retail layout is 0x14 bytes: three pointers + the 8-byte allocator.
// The out-of-line template instance (dtor 0x4e1bf0, copy ctor 0x50d440,
// operator= 0x50d4e0) is the type FUN_4a3920 returns.
// ---------------------------------------------------------------------------
class cSPEditorBlock;
struct SPAlloc { char c; SPAlloc() {} };                // eastl::sp_vector_allocator

struct VectorStorage {
    cSPEditorBlock** mpBegin;                           // +0x0
    cSPEditorBlock** mpEnd;                             // +0x4
    cSPEditorBlock** mpCapacity;                        // +0x8
    uint32_t mAllocId;                                  // +0xc
    uint32_t mAllocPad;                                 // +0x10
    VectorStorage() {}
    VectorStorage(const SPAlloc& alloc);                // 0x540470
    void Deallocate();                                  // 0x425990
    bool empty() const;                                 // 0x526430
    void push_back(cSPEditorBlock* const& b);           // 0x454860
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock*& operator[](int i) { return mpBegin[i]; }
};

struct BlockVector;

// eastl::vector<unsigned, sp_vector_allocator>: out-of-line template instance.
struct EaVector : VectorStorage {
    EaVector() {}
    EaVector(const SPAlloc& alloc) : VectorStorage(alloc) {}
    EaVector(const EaVector& o);                        // 0x50d440
    EaVector(const BlockVector& o);                     // 0x50d440
    ~EaVector();                                        // 0x4e1bf0
    EaVector& operator=(const EaVector& o);             // 0x50d4e0
};

// SP::SimpleVector<unsigned>: same storage, destructor defined in the header.
struct BlockVector : VectorStorage {
    BlockVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    BlockVector(const BlockVector& o);                  // 0x50d440
    BlockVector(const SPAlloc& alloc) : VectorStorage(alloc) {}
    ~BlockVector()
    {
        for (cSPEditorBlock** it = mpBegin; it < mpEnd; ++it) { }
        Deallocate();
    }
    BlockVector& operator=(const EaVector& o);          // 0x50d4e0
};

// A 60-bit flag set at +0xdc8 (two dwords).
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const
    {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

class cSPEditorModel;

// EA::AutoRefCount<T>: a raw pointer with an implicit conversion (retail +0x0).
template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

class cSPEditorBlock {
public:
    char pad0[0x28];
    cSPEditorModel* mEditorModel;                       // +0x28
    char pad2c[0x48 - 0x2c];
    Vec3 mPosition;                                     // +0x48
    char pad54[0x33c - 0x54];
    AutoRefCount<cSPEditorBlock> mSocketConnector;      // +0x33c
    char pad340[0x3e0 - 0x340];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;       // +0x3e0
    char pad3e4[0xdc8 - 0x3e4];
    bitset<60> mFlags;                                  // +0xdc8

    bool IsInChain(cSPEditorBlock* other);              // 0x44a9a0
};

class cSPEditorModel {
public:
    bool UsingSymmetry() const;                         // 0x4adc40
    unsigned int GetBlockCount() const;                 // 0x4accf0
    cSPEditorBlock* GetBlock(unsigned int i) const;     // 0x4accb0
};

// Screen-space helpers -------------------------------------------------------
class cTransform {
public:
    void xform(Vec3* out, const Vec3* in);              // 0x7c4180
};

namespace SP {
class cApp {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15();
    virtual cTransform* GetTransform();                 // +0x58
};
cApp* App();                                            // 0x67dd10
}

Vec4* SPUIHelpers_GetMainWindowArea(Vec4* out);         // 0x805ea0

// Block search helpers ------------------------------------------------------
bool FUN_4a18b0(cSPEditorBlock* block, cSPEditorBlock* other, float dist); // 0x4a18b0
bool PostXformEffect(unsigned int id, cSPEditorBlock* block,
                     cSPEditorBlock** out);             // 0x4a88f0
EaVector FUN_4a3920(cSPEditorModel* model, bool symmetric); // 0x4a3920

// @ 0x4a3760
void FUN_4a3760(const Vec3* in, float* px, float* py)
{
    SP::cApp* obj = SP::App();
    Vec3 v;
    obj->GetTransform()->xform(&v, in);
    Vec4 res;
    SPUIHelpers_GetMainWindowArea(&res);
    *px = (1.0f + v[0]) * res.z * 0.5f;
    *py = (1.0f - v[1]) * res.w * 0.5f;
}

// @ 0x4a37f0
BlockVector FUN_4a37f0(cSPEditorModel* model, unsigned int effectId)
{
    BlockVector result;
    if (model) {
        BlockVector ids;
        ids = FUN_4a3920(model, false);
        if (!ids.empty()) {
            int i = 0;
            int n = ids.size();
            for (; i < n; i++) {
                cSPEditorBlock* p;
                bool ok = PostXformEffect(effectId, ids[i], &p);
                if (ok && p != 0)
                    result.push_back(p);
            }
        }
    }
    return result;
}

// @ 0x4a3920
EaVector FUN_4a3920(cSPEditorModel* model, bool symmetric)
{
    BlockVector result((SPAlloc()));
    BlockVector symList((SPAlloc()));
    if (model) {
        if (symmetric && !model->UsingSymmetry())
            symmetric = false;
        int i = 0;
        int n = (int)model->GetBlockCount();
        for (; i < n; i++) {
            cSPEditorBlock* block = model->GetBlock((unsigned int)i);
            cSPEditorBlock** end = symList.mpEnd;
            cSPEditorBlock** it = symList.mpBegin;
            while (it != end && *it != block)
                ++it;
            if (it != symList.mpEnd)
                continue;
            if (!block->mSocketConnector)
                continue;
            if (!block->mSocketConnector->mFlags.test(11))
                continue;
            if (block->mSocketConnector->mFlags.test(7))
                continue;
            if (!(block->mFlags.test(0x14) || block->mFlags.test(0x2d) ||
                  block->mFlags.test(0x2c)))
                continue;
            result.push_back(block);
            if (symmetric && block->mSymmetricBlock) {
                cSPEditorBlock* sym = block->mSymmetricBlock;
                symList.push_back(sym);
            }
        }
    }
    return result;
}

// @ 0x4a3c70
cSPEditorBlock* FUN_4a3c70(cSPEditorBlock* block, Vec3 target)
{
    if (!block->mSocketConnector)
        return 0;
    cSPEditorModel* p = block->mEditorModel;
    float value = FLT_MAX;
    cSPEditorBlock* res = 0;
    int i = 0;
    int num = (int)p->GetBlockCount();
    for (; i < num; i++) {
        cSPEditorBlock* other = p->GetBlock((unsigned int)i);
        if (other != block && other != block->mSymmetricBlock &&
            !other->IsInChain(block)) {
            Vec3 item = other->mPosition - target;
            float d = VectorLength(&item);
            if (FUN_4a18b0(block, other, d) && d < value) {
                value = d;
                res = other;
            }
        }
    }
    return res;
}
