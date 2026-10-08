// Slice s00faa5c0: SP::cTerrainSphere::SaveModifications @ 0x00faa5c0 (PDB-candidate name from Ghidra; unverified).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), same module as the other cTerrainSphere slices.
//
// If the sphere has a config/property sink (this+0x28), it packs three lists of 0xac-byte "relevel" records
// into (key array, transform array) variants and hands them to the sink:
//   1. list at +0x798 -> properties 0x3ad5568 (keys) / 0x3ad5569 (transforms)
//   2. lists at +0x770 then +0x784 concatenated -> properties 0x43b29e1 / 0x43b29e2
// then calls SetModels() to rebuild the placed models.
#include "types.h"
#include <new>

namespace EA { namespace ResourceMan { struct Key { uint32_t instance, type, group; }; } }
typedef EA::ResourceMan::Key Key;

struct Allocator { const char* mpName; };

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix3 {
    Vector3 row0, row1, row2;
    Matrix3() {}
    Matrix3& Assign(const Matrix3& m);          // 0x0041cb40
};

// Matrix3 with the out-of-line row copy (loop over the +0x798 list) and the same layout with an inline copy.
struct Matrix3I { Vector3 row0, row1, row2; };
struct cSPTransformI {                              // transform as copied by the +0x770/+0x784 loops
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3I mRot;
};
struct cSPTransform {
    uint16_t mFlags, mModCount;
    float mTx, mTy, mTz, mScale;
    Matrix3 mRot;
    cSPTransform() {}
    __forceinline cSPTransform(const cSPTransform& o) {
        mFlags = o.mFlags; mModCount = o.mModCount;
        mTx = o.mTx; mTy = o.mTy; mTz = o.mTz; mScale = o.mScale;
        mRot.Assign(o.mRot);
    }
    __forceinline cSPTransform(const cSPTransformI& o) {
        mFlags = o.mFlags; mModCount = o.mModCount;
        mTx = o.mTx; mTy = o.mTy; mTz = o.mTz; mScale = o.mScale;
        mRot.row0 = Vector3(o.mRot.row0);
        mRot.row1 = Vector3(o.mRot.row1);
        mRot.row2 = Vector3(o.mRot.row2);
    }
};
struct Rect { float l, t, r, b; };
struct cRelevelI {                                  // same record as cRelevel, other transform flavour
    cSPTransformI mTransform; Rect mBounds[6]; Key mKey; uint32_t mFlagsAndBits; uint32_t mExtra;
};
struct cRelevel {                                   // 0xac bytes in the retail layout
    cSPTransform mTransform;                        // +0x00
    Rect mBounds[6];                                // +0x38
    Key mKey;                                       // +0x98
    uint32_t mFlagsAndBits;                         // +0xa4
    uint32_t mExtra;                                // +0xa8
};

void __cdecl FreeBlock(void* p);                    // 0x00f47380 (operator_delete__)

struct KeyVector {
    Key* mBegin; Key* mEnd; Key* mCap; Allocator mAlloc;
    KeyVector() : mBegin(0), mEnd(0), mCap(0) {}
    void Reserve(int n);                            // 0x0041e4d0 (Vec3Vec_Reserve, 12-byte elements)
    void DoInsertValue(Key* pos, const Key& v);     // 0x004e3e10
    Key* erase(Key* first, Key* last);              // 0x0050f740
    __forceinline void push_back(const Key& v) {
        if (mEnd < mCap) ::new (mEnd++) Key(v);
        else DoInsertValue(mEnd, v);
    }
    ~KeyVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};
struct XformVector {
    cSPTransform* mBegin; cSPTransform* mEnd; cSPTransform* mCap; Allocator mAlloc;
    XformVector() : mBegin(0), mEnd(0), mCap(0) {}
    void Reserve(int n);                            // 0x00b04c50
    void DoInsertValue(cSPTransform* pos, const cSPTransform& v);   // 0x00423960
    void DoInsertValue(cSPTransform* pos, const cSPTransformI& v);  // same function; the record is passed by address
    template <class U> __forceinline void push_back(const U& v) {
        if (mEnd < mCap) ::new (mEnd++) cSPTransform(v);
        else DoInsertValue(mEnd, v);
    }
    void erase(cSPTransform* first, cSPTransform* last) { mEnd = mEnd - (last - first); }
    ~XformVector() { if (mBegin && ((int*)mBegin)[-1]) FreeBlock(mBegin); }
};

struct Variant {
    uint32_t data[4]; uint16_t flags; uint16_t type;
    Variant() { flags = 0; type = 0; }
    void Set(int a, int b, void* ptr, int elemSize, int count);     // 0x0093dd80
    void Destruct(int);                                             // 0x0093db80
    ~Variant() { if (flags & 4) Destruct(0); }
};

struct IConfigSink {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void SetProperty(uint32_t id, Variant* v);              // +0x14
};

template <class T> struct RecVec { T* mBegin; T* mEnd; T* mCap; Allocator mAlloc;
    int size() const { return mEnd - mBegin; } };

struct cTerrainSphere {
    char pad00[0x28];
    IConfigSink* mSink;                         // +0x28
    char pad2c[0x770 - 0x2c];
    RecVec<cRelevelI> mRelevelA;                 // +0x770
    char pad780[4];
    RecVec<cRelevelI> mRelevelB;                 // +0x784
    char pad794[4];
    RecVec<cRelevel> mRelevelC;                 // +0x798
    void SetModels();                           // 0x00fa96d0
    void SaveModifications();
};

template <class R> static __forceinline void AppendRelevels(KeyVector& keys, XformVector& xf, const RecVec<R>& v)
{
    int n = v.size();
    for (int i = 0; i < n; ++i) {
        keys.push_back(v.mBegin[i].mKey);
        xf.push_back(v.mBegin[i].mTransform);
    }
}

// @ 0x00faa5c0
void cTerrainSphere::SaveModifications()
{
    if (mSink) {
        KeyVector keys;
        XformVector xf;
        keys.Reserve(mRelevelC.size());
        xf.Reserve(mRelevelC.size());
        AppendRelevels(keys, xf, mRelevelC);
        Variant vKeys;
        vKeys.Set(0x20, 0x98, keys.mBegin, 0xc, keys.mEnd - keys.mBegin);
        Variant vXf;
        int nXf = xf.mEnd - xf.mBegin;
        vXf.Set(0x38, 0x98, xf.mBegin, 0x38, nXf);
        mSink->SetProperty(0x3ad5568, &vKeys);
        mSink->SetProperty(0x3ad5569, &vXf);
        keys.erase(keys.mBegin, keys.mEnd);
        xf.mEnd = xf.mEnd - nXf;

        keys.Reserve(mRelevelA.size() + mRelevelB.size());
        xf.Reserve(mRelevelA.size() + mRelevelB.size());
        AppendRelevels(keys, xf, mRelevelA);
        AppendRelevels(keys, xf, mRelevelB);
        Variant vKeys2;
        vKeys2.Set(0x20, 0x98, keys.mBegin, 0xc, keys.mEnd - keys.mBegin);
        Variant vXf2;
        vXf2.Set(0x38, 0x98, xf.mBegin, 0x38, xf.mEnd - xf.mBegin);
        mSink->SetProperty(0x43b29e1, &vKeys2);
        mSink->SetProperty(0x43b29e2, &vXf2);
        SetModels();
    }
}
