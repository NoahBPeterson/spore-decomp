// src/game/SPGonzago/SPBlobShadow.cpp -- migrated from slice(s) s0041cb40, s00536d40, s0041dd90, s0041d490 by tools/migrate/rewrite.py
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

// ---- items of slice s0041cb40 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0041_cb40 {
    float x, y, z;
    Vector3_s0041_cb40() {}
    Vector3_s0041_cb40(const Vector3_s0041_cb40& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix3_s0041_cb40 {
    Vector3_s0041_cb40 row0, row1, row2;
    Matrix3_s0041_cb40& Assign(const Matrix3_s0041_cb40& m);
};
struct VirtualRefObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
struct VirtualRefPtr {
    VirtualRefObject* mp;
    VirtualRefPtr() : mp(0) {}
    VirtualRefPtr(VirtualRefObject* p);
    VirtualRefPtr(const VirtualRefPtr& o) { mp = o.mp; if (mp) mp->AddRef(); }
    ~VirtualRefPtr() { if (mp) mp->Release(); }
};
struct DefaultRefCounted_s0041_cb40 {
    int mVtbl;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};
struct TargetPtr {
    DefaultRefCounted_s0041_cb40* mp;
    TargetPtr& Assign(DefaultRefCounted_s0041_cb40* p);
    TargetPtr& Init(DefaultRefCounted_s0041_cb40* p);
};
struct SharedObject {
    void AddRef();
    void Release();
};
struct SharedPtr {
    SharedObject* mp;
    SharedPtr& Assign(SharedObject* p);
};
struct FixedAllocator {
    uint32_t pad;
    void*    mpPool;
    FixedAllocator(void* pool) { mpPool = pool; }
    FixedAllocator(const FixedAllocator& a) { mpPool = a.mpPool; }
};
inline void InlineScratch()
{
    uint32_t unused[7];
}
struct VectorBase {
    char*          mpBegin;
    char*          mpEnd;
    char*          mpCapacity;
    FixedAllocator mAllocator;
    VectorBase(const FixedAllocator& a) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
};
template <int Bytes>
struct FixedVector : VectorBase {
    uint32_t       pad;
    char           mBuffer[Bytes];
    void           Reserve(uint32_t n);   // external
    FixedVector(uint32_t n);
    FixedVector() : VectorBase(FixedAllocator(mBuffer))
    {
        mpEnd = mBuffer;
        mpBegin = mpEnd;
        mpCapacity = mpBegin + Bytes;
    }
};
template <int Bytes>
FixedVector<Bytes>::FixedVector(uint32_t n) : VectorBase(FixedAllocator(mBuffer))
{
    mpEnd = mBuffer;
    mpBegin = mpEnd;
    mpCapacity = mpBegin + Bytes;
    InlineScratch();
    Reserve(n);
}
template FixedVector<0x180>::FixedVector();
struct InsertTag {};
template <class K, class M>
struct HashMap {
    struct value_type {
        K first;
        M second;
        // The retail value_type is 16 bytes: the node's mpNext sits at +0x10 and the
        // node allocator (0x00425240) copies all 16 bytes, so the surrounding map
        // instantiations see 4 bytes of padding after `second` (left uninitialised).
        uint32_t mPad;
        value_type(const K& k, const M& m) : first(k), second(m) {}
    };
    struct Node {
        value_type mValue;
        Node*      mpNext;
    };
    struct Iterator {
        Node*  mpNode;
        Node** mpBucket;
        Iterator() {}
        Iterator(Node* pNode, Node** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
        bool operator!=(const Iterator& o) const { return mpNode != o.mpNode; }
    };
    struct InsertResult {
        Iterator first;
        bool     second;
    };

    uint32_t pad;
    Node**   mpBucketArray;
    uint32_t mnBucketCount;

    Iterator     find(const K& key);
    InsertResult DoInsert(const value_type& v, InsertTag tag);
    InsertResult insert(const value_type& v) { return DoInsert(v, InsertTag()); }
    Iterator     end() { Node** b = mpBucketArray + mnBucketCount; Node* n = *b; return Iterator(n, b); }
    M&           operator[](const K& key);
};
inline void InlineScratch48();  // 0x0041d420 (defined below; used by a stub's inline body)
template <class K, class M>
M& HashMap<K, M>::operator[](const K& key)
{
    InlineScratch48();
    Iterator it = find(key);
    if (it != end())
        return it.mpNode->mValue.second;
    return insert(value_type(key, M())).first.mpNode->mValue.second;
}
struct Key8 { uint32_t a, b; };
template struct HashMap<Key8, VirtualRefPtr>;
template struct HashMap<Key8, int>;
template <int Bytes>
struct FixedBuffer {
    char*    mpBegin;
    char*    mpEnd;
    char*    mpCapacity;
    uint32_t pad[2];
    uint32_t mFlags;       // +0x14
    char     mBuffer[Bytes];
    FixedBuffer()
    {
        uint32_t unused;   // dead local of the original (frame size only)
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        mFlags = 0;
        mpBegin = mBuffer;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + Bytes;
    }
};
template struct HashMap<uint32_t, float>;
struct ConstructTag {};
struct RangeOwner {
    void* mpFirst;
    void* mpLast;
    void Destroy(void* first, void* last);                     // external
    void Construct(void* first, void* last, ConstructTag tag); // external
    void Copy(void* first, void* last) { ConstructTag tag; Construct(first, last, tag); }
    RangeOwner& Assign(const RangeOwner& o);
};
struct FlagTag {};
struct FlagObject {
    void Setup(int zero, const FlagTag& f5, const FlagTag& f4, const FlagTag& f3, const FlagTag& f2, const FlagTag& f1, void* arg);   // external
    FlagObject(void* arg);
};
// ---- items of slice s0041cb40 end

// @ 0x0041cb40
Matrix3_s0041_cb40& Matrix3_s0041_cb40::Assign(const Matrix3_s0041_cb40& m)
{
    row0 = Vector3_s0041_cb40(m.row0);
    row1 = Vector3_s0041_cb40(m.row1);
    row2 = Vector3_s0041_cb40(m.row2);
    return *this;
}

// @ 0x0041cc20
VirtualRefPtr::VirtualRefPtr(VirtualRefObject* p)
{
    mp = p;
    if (mp)
        mp->AddRef();
}

// @ 0x0041cc60
TargetPtr& TargetPtr::Assign(DefaultRefCounted_s0041_cb40* p)
{
    if (p != mp) {
        DefaultRefCounted_s0041_cb40* old = mp;
        uint32_t unused[3];   // dead locals of the original (frame size only)
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    return *this;
}

// @ 0x0041ccc0
TargetPtr& TargetPtr::Init(DefaultRefCounted_s0041_cb40* p)
{
    mp = p;
    if (mp)
        mp->AddRef();
    return *this;
}

// @ 0x0041cd10
SharedPtr& SharedPtr::Assign(SharedObject* p)
{
    if (p != mp) {
        SharedObject* old = mp;
        if (p)
            p->AddRef();
        mp = p;
        if (old)
            old->Release();
    }
    return *this;
}

// @ 0x0041cf00
template FixedVector<0xC0>::FixedVector()
;

// @ 0x0041cf70
template FixedVector<0x380>::FixedVector()
;

// @ 0x0041cfe0
template FixedVector<0x40>::FixedVector()
;

// @ 0x0041d050
template FixedVector<0x100>::FixedVector()
;

// @ 0x0041d0c0
template FixedVector<0x100>::FixedVector(uint32_t)
;

// @ 0x0041d140
RangeOwner& RangeOwner::Assign(const RangeOwner& o)
{
    uint32_t unused[4];   // dead locals of the original (frame size only)
    if (this != &o) {
        Destroy(mpFirst, mpLast);
        Copy(o.mpFirst, o.mpLast);
    }
    return *this;
}

// @ 0x0041d1a0
FlagObject::FlagObject(void* arg)
{
    Setup(0, FlagTag(), FlagTag(), FlagTag(), FlagTag(), FlagTag(), arg);
}

// @ 0x0041d360
template FixedBuffer<0x200>::FixedBuffer()
;

// @ 0x0041d3c0
template FixedBuffer<0xA0>::FixedBuffer()
;

// @ 0x0041d420
inline void InlineScratch48()
{
    uint32_t unused[12];
}

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
