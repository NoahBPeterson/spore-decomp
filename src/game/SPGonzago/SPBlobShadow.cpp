// src/game/SPGonzago/SPBlobShadow.cpp -- migrated from slice(s) s00536d40, s0041dd90, s0041d490 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBlobShadow.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdarg.h>
#include "EA/ArgScript/cArguments.h"
#include "cSPTransform.h"

// unnamed retail callees and globals (address in the comment)
extern void* vtbl_cCreatureAbility[];
extern "C" long _InterlockedIncrement(long volatile*);
#pragma intrinsic(_InterlockedIncrement)

// ---- items of slice s0041d490 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    void Set(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
};
struct AbilityBlockCopy {              // FUN_0041d7b0 body (copy two Vec4 rows)
    AbilityBlockCopy* CopyRows(const float* src);
};
extern void* vtbl_cCreatureAbility[];
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
struct cCreatureAbility {
    void*          vptr;      // 0
    unsigned short mId;       // 4
    unsigned short mSize;     // 6
    void*          mData;     // 8
    float          mBlock[8]; // 0xc (two rows of 4 floats)

    cCreatureAbility(const float* src);
    cCreatureAbility* Destroy(unsigned flags);
};
struct PoolAlloc { int tag; char* pool; };
struct FixedVecHdr {
    char* b; char* e; char* c;
    PoolAlloc a;
    int pad;
};
struct FixedVec8 : FixedVecHdr {
    char buf[8];
    FixedVec8();
};
struct Alloc { int x; };
struct StrBaseW { char* b; char* e; char* c; int a0, a1; void BaseInit(Alloc*); };
struct StrBaseA { char* b; char* e; char* c; int a0, a1; void BaseInit(Alloc*); };
struct WStr768 : StrBaseW { unsigned short buf[0x180]; WStr768* Init(); };
struct WStr512 : StrBaseW { unsigned short buf[0x100]; WStr512* Init(); };
struct WStr1024 : StrBaseW { unsigned short buf[0x200]; WStr1024* Init(); };
struct Str512 : StrBaseA { char buf[0x200]; Str512* Init(); };
struct FixedHdr2 { char* b; char* e; char* c; int pad[2]; int count; };
struct FixedVec192 : FixedHdr2 { char buf[0xc0]; void Init(); };
struct FixedVec1536 : FixedHdr2 { char buf[0x600]; void Init(); };
struct FixedVec896 : FixedHdr2 { char buf[0x380]; void Init(); };
struct PoolVec3072 : FixedVecHdr {
    char buf[0xc00];
    PoolVec3072(int arg);
    void ExtInit(int);
};
struct IObject { virtual void v0(); virtual void v1(); virtual void v2(); };
struct OwnPtrV1 { IObject* p; OwnPtrV1* Reset(); };
struct OwnPtrV2 { IObject* p; OwnPtrV2* Reset(); };
extern "C" long _InterlockedIncrement(long volatile*);
struct ThreadedObject { int vt; long rc; void Release(); };
struct DefaultRefCounted { int vt; int rc; void Release(); int AddRef() { int pad[3]; return rc++ + 1; } };
struct ThreadedRef { ThreadedObject* p; ThreadedRef* Assign(ThreadedObject* n); };
struct RcRef { DefaultRefCounted* p; RcRef* Reset(); };
void __fastcall ExtDestroy(void* obj);
struct ExtRef { void* p; ExtRef* Reset(); };
struct RcHolder { int vt; DefaultRefCounted rc; };  // refcounted base at +4
struct RcHolderRef { RcHolder* p; RcHolderRef* Assign(RcHolder* n); RcHolderRef* Reset(); };
void __cdecl ExtCopy(int a, int b, int c);
// ---- items of slice s0041d490 end

// ---- items of slice s0041dd90 begin (TODO(rewrite): local stubs, replace by canonical classes)
bool __cdecl PtrEqual(const void* a, const void* b);                     // FUN_00423250
struct Matrix3 {
    float m[3][3];
    float* operator[](int i) { return m[i]; }
};
struct Mat3Target { void Set(const float* m); };                         // FUN_0041cb40
// ---- items of slice s0041dd90 end

// ---- items of slice s00536d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPTransform_s0053_6d40 {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float mTranslation[3];  // +0x04
    float mScale;           // +0x10
    float mRotation[9];     // +0x14
    cSPTransform_s0053_6d40();                                                            // 0x00434040
    cSPTransform_s0053_6d40(const cSPTransform_s0053_6d40& x);                                       // @ 0x00538000
    cSPTransform_s0053_6d40& operator=(const cSPTransform_s0053_6d40& x);                            // @ 0x00537dc0
    void Compound(const cSPTransform_s0053_6d40& x);                                      // @ 0x00537f40
};
int VectorNotEqual(const float* a, const float* b);   // 0x0041dd30
int RotationNotEqual(const float* a, const float* b);// 0x0041dd90
cSPTransform_s0053_6d40& cSPTransform_s0053_6d40::operator=(const cSPTransform_s0053_6d40& x)
{
    bool bCopy = false;
    if (mFlags != x.mFlags)
        bCopy = true;
    else if (VectorNotEqual(mTranslation, x.mTranslation))
        bCopy = true;
    else if (!(mScale == x.mScale))
        bCopy = true;
    else if ((mFlags & 2) != 0 && RotationNotEqual(mRotation, x.mRotation))
        bCopy = true;
    if (bCopy) {
        mModCount = mModCount + 1;
        mFlags = x.mFlags;
        mTranslation[0] = x.mTranslation[0];
        mTranslation[1] = x.mTranslation[1];
        mTranslation[2] = x.mTranslation[2];
        mScale = x.mScale;
        for (int i = 0; i < 9; ++i)
            mRotation[i] = x.mRotation[i];
    }
    return *this;
}
struct cSPTransformOps {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    float mTranslation[3];  // +0x04
    float mScale;           // +0x10
    float mRotation[9];     // +0x14
    cSPTransformOps* Assign(const void* x);   // 0x00537dc0
};
// ---- items of slice s00536d40 end

// @ 0x0041d490
cCreatureAbility::cCreatureAbility(const float* src)
{
    int u1, u2, u3;
    vptr = vtbl_cCreatureAbility;
    mId = 0x21c;
    mSize = 0x20;
    mData = 0;
    ((AbilityBlockCopy*)mBlock)->CopyRows(src);
    vptr = vtbl_cCreatureAbility;
    mData = this ? (void*)mBlock : (void*)0;
}

// @ 0x0041d510
PoolVec3072::PoolVec3072(int arg)
{
    char* storage = buf;
    int* pad;
    b = 0; e = 0; c = 0;
    PoolAlloc* al = &a;
    al->pool = storage;
    e = buf;
    b = e;
    c = b + 0xc00;
    ExtInit(arg);
    { int bigpad[0x12]; } { int more; }
}

// @ 0x0041d590
FixedVec8::FixedVec8()
{
    char* storage = buf;
    int* pad;
    b = 0; e = 0; c = 0;
    PoolAlloc* al = &a;
    al->pool = storage;
    e = buf;
    b = e;
    c = b + 8;
}

// @ 0x0041d600
WStr768* WStr768::Init()
{
    unsigned short* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = (char*)buf;
    b = e;
    c = b + 0x300;
    *(unsigned short*)b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d660
WStr512* WStr512::Init()
{
    unsigned short* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = (char*)buf;
    b = e;
    c = b + 0x200;
    *(unsigned short*)b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d6c0
WStr1024* WStr1024::Init()
{
    unsigned short* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = (char*)buf;
    b = e;
    c = b + 0x400;
    *(unsigned short*)b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d720
Str512* Str512::Init()
{
    char* storage = buf;
    Alloc al;
    BaseInit(&al);
    e = buf;
    b = e;
    c = b + 0x200;
    *b = 0;
    { int pad; }
    return this;
}

// @ 0x0041d780
cCreatureAbility* cCreatureAbility::Destroy(unsigned flags)
{
    vptr = vtbl_cCreatureAbility;
    if (flags & 1)
        EASTL_allocator_deallocate(this);
    return this;
}

// @ 0x0041d7b0
AbilityBlockCopy* AbilityBlockCopy::CopyRows(const float* src)
{
    float* dst;
    const float* s;
    int rows;
    rows = 2;
    s = src;
    dst = (float*)this;
    while (--rows >= 0) {
        dst[0] = s[0];
        dst[1] = s[1];
        dst[2] = s[2];
        dst[3] = s[3];
        dst += 4;
        s += 4;
    }
    return this;
}

// @ 0x0041d830
void FixedVec192::Init()
{
    count = 0;
    b = buf;
    e = b;
    c = b + 0xc0;
}

// @ 0x0041d870
OwnPtrV1* OwnPtrV1::Reset()
{
    if (p) {
        IObject* o = p;
        p = 0;
        o->v1();
    }
    return this;
}

// @ 0x0041d8b0
ThreadedRef* ThreadedRef::Assign(ThreadedObject* n)
{
    if (n != p) {
        ThreadedObject* old = p;
        if (n)
            _InterlockedIncrement(&n->rc);
        p = n;
        if (old)
            old->Release();
    }
    { int pad[3]; }
    return this;
}

// @ 0x0041d900
RcRef* RcRef::Reset()
{
    if (p) {
        DefaultRefCounted* o = p;
        p = 0;
        o->Release();
    }
    { int pad[3]; }
    return this;
}

// @ 0x0041d940
ExtRef* ExtRef::Reset()
{
    if (p) {
        void* o = p;
        p = 0;
        ExtDestroy(o);
    }
    return this;
}

// @ 0x0041d980
RcHolderRef* RcHolderRef::Assign(RcHolder* n)
{
    if (n != p) {
        RcHolder* old = p;
        if (n) {
            n->rc.AddRef();
        }
        p = n;
        if (old)
            old->rc.Release();
    }
    
    return this;
}

// @ 0x0041d9f0
RcHolderRef* RcHolderRef::Reset()
{
    if (p) {
        RcHolder* o = p;
        p = 0;
        o->rc.Release();
    }
    { int pad[3]; }
    return this;
}

// @ 0x0041da30
OwnPtrV2* OwnPtrV2::Reset()
{
    if (p) {
        IObject* o = p;
        p = 0;
        o->v2();
    }
    return this;
}

// @ 0x0041da70
void FixedVec1536::Init()
{
    count = 0;
    b = buf;
    e = b;
    c = b + 0x600;
}

// @ 0x0041dab0
void FixedVec896::Init()
{
    count = 0;
    b = buf;
    e = b;
    c = b + 0x380;
}

// @ 0x0041daf0
int __cdecl Unchecked_idl0(int a, int b, int c)
{
    ExtCopy(a, b, c);
    return a;
}

// @ 0x0041db10
Vector3 operator-(const Vector3& a, const Vector3& b)
{
    Vector3 r(a.x - b.x, a.y - b.y, a.z - b.z);
    return r;
}

// @ 0x0041dba0
Vector3* ScaleInPlace(Vector3* v, const float* s)
{
    v->Set(v->x * *s, v->y * *s, v->z * *s);
    return v;
}

// @ 0x0041dc10
Vector3 operator+(const Vector3& a, const Vector3& b)
{
    Vector3 r(a.x + b.x, a.y + b.y, a.z + b.z);
    return r;
}

// @ 0x0041dca0
Vector3 operator*(const Vector3& a, const float& s)
{
    Vector3 r(a.x * s, a.y * s, a.z * s);
    return r;
}

// @ 0x0041dd30
bool operator!=(const Vector3& a, const Vector3& b)
{
    return !(a.x == b.x && a.y == b.y && a.z == b.z);
}

// @ 0x0041dd90
bool __cdecl NotEqual(const void* a, const void* b)
{
    return !PtrEqual(a, b);
}

// @ 0x0041ded0
Mat3Target* __cdecl Matrix3_Transposed(Mat3Target* out, const Matrix3* src)
{
    Matrix3 m;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            float* row;
            float t;
            t = src->m[j][i];
            row = m.m[i];
            row[j] = t;
        }
    { uint32_t unused[11]; }
    out->Set(m.m[0]);
    return out;
}

// @ 0x00537dc0
cSPTransformOps* cSPTransformOps::Assign(const void* xv)
{
    const cSPTransformOps* x = (const cSPTransformOps*)xv;
    bool bCopy = false;
    if (mFlags != x->mFlags)
        bCopy = true;
    else if (VectorNotEqual(mTranslation, x->mTranslation))
        bCopy = true;
    else if (!(mScale == x->mScale))
        bCopy = true;
    else if ((mFlags & 2) != 0 && RotationNotEqual(mRotation, x->mRotation))
        bCopy = true;
    if (bCopy) {
        mModCount = mModCount + 1;
        mFlags = x->mFlags;
        mTranslation[0] = x->mTranslation[0];
        mTranslation[1] = x->mTranslation[1];
        mTranslation[2] = x->mTranslation[2];
        mScale = x->mScale;
        for (int i = 0; i < 9; ++i)
            mRotation[i] = x->mRotation[i];
    }
    return this;
}
