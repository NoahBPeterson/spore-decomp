// Slice s0049c210: SP::EditorUtils tracker / pinning helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <float.h>

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
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
struct cSPMatrix3 : Matrix33T {
    cSPMatrix3() {}
    cSPMatrix3(const Matrix33T& m) : Matrix33T(m) {}
};
template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    T& operator*() const { return *mpObject; }
    T* get() const { return mpObject; }
};

struct cSPEditorBlock;
struct cSPTransform {
    unsigned short mFlags;
    unsigned short mModificationCount;
    cSPVector3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                              // @ 0x409930
    cSPTransform(const cSPTransform& t);                         // @ 0x40ce80
};
struct TrackerRecord {
    cSPEditorBlock* block;
    cSPTransform transform;
};
template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void push_back(const T& v);                                  // @ 0x4a9fa0
};

// ---- class stub ----
template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) {
            uint32_t word = mWord[i >> 5];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x48 - 4];
    cSPVector3 mPosition;                        // +0x48
    char pad1[0x60 - 0x54];
    cSPMatrix3 mOrientation;                     // +0x60
    char pad1b[0xa8 - 0x84];
    cSPVector3 mRestPose;                        // +0xa8
    char pad2[0x1d8 - 0xb4];
    float mScale;                                // +0x1d8
    char pad3[0x33c - 0x1dc];
    AutoRefCount<cSPEditorBlock> mParentBlock;   // +0x33c
    vector<AutoRefCount<cSPEditorBlock> > mSymmetricBlocks;  // +0x340
    char pad4[0x3e0 - 0x34c];
    AutoRefCount<cSPEditorBlock> mPinTarget;     // +0x3e0
    char pad5[0x3ec - 0x3e4];
    void* mSkin;                                 // +0x3ec
    char pad6[0xdc8 - 0x3f0];
    bitset<60> mFlags;                           // +0xdc8
    void FUN_438700(cSPEditorBlock* block);      // @ 0x438700
    void GetOffsetA(cSPVector3* out, bool f);    // @ 0x438120
    void GetOffsetB(cSPVector3* out, bool f);    // @ 0x4381e0
    void Place(cSPVector3 a, cSPVector3 b);      // @ 0x437b00
};

// ---- engine helpers ----
Vector3T operator-(const Vector3T& a, const Vector3T& b);      // @ 0x41db10
float VectorLength(const Vector3T& v);                         // @ 0x40ae50
cSPVector3 operator*(const cSPVector3& v, const cSPMatrix3& m);  // @ 0x41daf0
cSPVector3 operator+(const cSPVector3& a, const cSPVector3& b);  // @ 0x41dc10
cSPMatrix3 operator*(const cSPMatrix3& a, const cSPMatrix3& b);  // @ 0x41de20
cSPVector3 operator*(const cSPMatrix3& m, const cSPVector3& v);  // @ 0x41ded0
void RepinBlockToTorso(cSPEditorBlock* block, cSPVector3 t, cSPMatrix3 r, int flags);  // @ 0x49fbd0

namespace SP { namespace EditorUtils {
cSPVector3 GetSkinTip(cSPEditorBlock* block);                  // @ 0x4a5d10
cSPEditorBlock* FindSymmetricSpine(cSPEditorBlock* block);     // @ 0x4a5970

// @ 0x49c570
cSPEditorBlock* FindClosestSymmetry(cSPVector3 point, cSPEditorBlock* block)
{
    float p15 = FLT_MAX;
    cSPEditorBlock* nCount = block;
    cSPEditorBlock* t22 = 0;
    while (nCount) {
        cSPVector3 hi = GetSkinTip(nCount);
        cSPVector3 item = point - hi;
        float t26 = VectorLength(item);
        if (t26 < p15) {
            p15 = t26;
            t22 = nCount;
        }
        nCount = FindSymmetricSpine(nCount);
    }
    ScratchSlots<1>();
    return t22;
}

// @ 0x49ce40
void RepinBlocks(vector<TrackerRecord>* list)
{
    int i = 0;
    int n = list->size();
    for (; i < n; i++) {
        TrackerRecord& rec = list->mpBegin[i];
        cSPEditorBlock* block = rec.block;
        cSPTransform local(rec.transform);
        cSPEditorBlock* parent = block->mParentBlock;
        if (parent) {
            cSPVector3 pos = local.mTranslation * parent->mOrientation + parent->mPosition;
            cSPMatrix3 rot = local.mRotation * parent->mOrientation;
            RepinBlockToTorso(block, pos, rot, 0);
        }
    }
}

bool FUN_435c80(cSPEditorBlock* block);   // @ 0x435c80
bool FUN_43c510(cSPEditorBlock* block);   // @ 0x43c510
struct cSPEditorModel;

// @ 0x49c8f0
void BuildBlockTransforms(cSPEditorBlock* block, vector<TrackerRecord>* out, bool recurse)
{
    if (!block) return;
    if (FUN_435c80(block)) return;
    vector<AutoRefCount<cSPEditorBlock> >* syms = &block->mSymmetricBlocks;
    int count = syms->size();
    for (int i = 0; i < count; i++) {
        cSPEditorBlock* sym = syms->mpBegin[i];
        if (!FUN_435c80(sym) && sym->mSkin == 0) {
            cSPMatrix3 orient = block->mOrientation;
            cSPVector3 rel = sym->mPosition - block->mPosition;
            cSPVector3 a = orient * rel;
            cSPVector3 b = orient * sym->mRestPose;
            TrackerRecord rec;
            rec.block = block;
            rec.transform = cSPTransform();
            rec.transform.mTranslation = a + b;
            rec.transform.mRotation = orient;
            out->push_back(rec);
        }
        if (recurse) BuildBlockTransforms(sym, out, recurse);
    }
}

// @ 0x49cb90
void FUN_49cb90(vector<TrackerRecord>* list)
{
    int i = 0;
    int n = list->size();
    for (; i < n; i++) {
        TrackerRecord& rec = list->mpBegin[i];
        cSPEditorBlock* block = rec.block;
        cSPTransform local(rec.transform);
        cSPEditorBlock* target = block->mParentBlock->mPinTarget;
        if (target) {
            cSPVector3 pos = local.mTranslation * target->mOrientation + target->mPosition;
            cSPMatrix3 rot = local.mRotation * target->mOrientation;
            RepinBlockToTorso(block, pos, rot, 0);
            target->FUN_438700(block);
            if (!block->mFlags.test(10)) {
                cSPVector3 a;
                cSPVector3 b;
                block->GetOffsetA(&b, true);
                block->GetOffsetB(&a, true);
                block->Place(a, b);
            }
        }
    }
}

// @ 0x49c630
cSPVector3* FUN_49c630(cSPVector3* out, float x, float y, float z, cSPEditorModel* model)
{
    out->x = x;
    out->y = y;
    out->z = z;
    return out;
}

// @ 0x49c210
cSPMatrix3* FUN_49c210(cSPMatrix3* out, cSPEditorBlock* block, float x, float y, float z)
{
    if (!block) {
        *out = cSPMatrix3();
        return out;
    }
    if (!FUN_43c510(block)) {
        *out = block->mOrientation;
        return out;
    }
    *out = block->mOrientation;
    return out;
}
}}  // namespace SP::EditorUtils
