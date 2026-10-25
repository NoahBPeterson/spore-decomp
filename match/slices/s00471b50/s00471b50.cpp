// s00471b50 -- /Od /Ob1 region.

#include <math.h>

extern "C" long _InterlockedExchange(long volatile*, long);
#pragma intrinsic(_InterlockedExchange)

typedef unsigned int uint32_t;
template <int N> inline void ScratchSlots()
{
    uint32_t s[N];
    (void)s;
}

class ThreadedObject {
public:
    void Release();
};

// @ 0x00472520
struct RefHolderA {
    ThreadedObject* p;
    ~RefHolderA();
};

RefHolderA::~RefHolderA()
{
    ScratchSlots<3>();
    if (p)
        p->Release();
}

class DefaultRefCounted {
public:
    void Release();
};

// @ 0x00472540
struct RefHolderB {
    DefaultRefCounted* p;
    ~RefHolderB();
};

RefHolderB::~RefHolderB()
{
    ScratchSlots<3>();
    if (p)
        p->Release();
}

// @ 0x00472640 -- index into a strided element array
struct StridedArr {
    int pad0;
    int off;
    unsigned short pad8;
    unsigned short stride;
    int get(int);
};

int StridedArr::get(int i)
{
    return i * stride + off;
}

extern int vtbl60[];

struct S60 {
    void* vt;
    unsigned short a, b;
    void* self;
};

// @ 0x00472660
S60* __fastcall Init72660(S60* p)
{
    p->vt = vtbl60;
    p->a = 0x218;
    p->b = 1;
    p->self = 0;
    p->vt = vtbl60;
    p->self = p ? (void*)((char*)p + 0xc) : 0;
    return p;
}

struct S61 {
    void* vt;
    unsigned short a, b;
    void* self;
};

// @ 0x004726d0
S61* __fastcall Init726d0(S61* p)
{
    p->vt = vtbl60;
    p->a = 0x238;
    p->b = 1;
    p->self = 0;
    p->vt = vtbl60;
    p->self = p ? (void*)((char*)p + 0xc) : 0;
    return p;
}

struct S62 {
    void* vt;
    unsigned short a, b;
    void* self;
};

// @ 0x00472a00
S62* __fastcall Init72a00(S62* p)
{
    p->vt = vtbl60;
    p->a = 0x21e;
    p->b = 0x10;
    p->self = 0;
    p->vt = vtbl60;
    p->self = p ? (void*)((char*)p + 0xc) : 0;
    return p;
}

// ---- helpers of the 0x00471ec0 element scan (all real image functions) ------
void  F_00409c00();     // 0x409c00 __thiscall: 0x18-byte box ctor (min/max, +0..+0x14)
void  F_00409930();     // 0x409930 __thiscall: 0x38-byte bound-record ctor
void  F_00402ab0();     // 0x402ab0 __thiscall: 0x24-byte 3x3 matrix ctor (no-op)
void  F_00409dd0();     // 0x409dd0 __thiscall: accumulate a bound record into a box
void  F_0043f050();     // 0x43f050 __thiscall: union a box into a box
void  F_00511140();     // 0x511140 __thiscall: copy a box out to the caller's object
void* F_0041de20(void* dest, void* a, void* b);   // 0x41de20 cdecl: fills dest, returns dest
void* F_00401010();     // 0x401010 cdecl: singleton getter (0x15d0c04)
void  F_004721e0();     // 0x4721e0 __thiscall: copy-construct a 0x1d8-byte element

typedef void  (__thiscall* TSelf0)(void* self);
typedef void  (__thiscall* TSelf1)(void* self, void* arg);
typedef bool  (__thiscall* TSix)(void* self, void* a1, void* a2, void* a3, void* a4, void* a5, void* a6);

struct Box18 { float v[6]; };            // +0x00 min xyz, +0x0c max xyz
struct Mat3_ { float m[9]; };            // 0x24 bytes
struct BoundRec {                        // 0x38 bytes
    unsigned short flags;                // +0x00
    unsigned short count;                // +0x02
    float x, y, z;                       // +0x04
    float w;                             // +0x10
    Mat3_ mat;                           // +0x14
};
struct Elem1d8 { int w[0x76]; };         // 0x1d8 opaque bytes (an int array keeps /GS quiet)

// @ 0x00471ec0
// Walks the 0x1d8-byte element array at arg1+0x98, asks the editor singleton
// (0x401010, vtable slot 0x54) to classify each element, accumulates the accepted
// ones into a bound record and unions the result into the box that is finally
// copied out to *self.  *out keeps a running sum of the box volumes.
void* F_00471ec0(void* self, unsigned char* arg1, float* out)
{
    Box18 box;
    ((TSelf0)F_00409c00)(&box);
    if (out != 0)
        *out = 0.0f;
    unsigned char* arr = arg1 + 0x98;
    int count = (*(int*)(arr + 4) - *(int*)arr) / 0x1d8;
    for (int i = 0; i < count; ++i) {
        Elem1d8 e;
        char* ep = (char*)&e;
        ((TSelf1)F_004721e0)(&e, (unsigned char*)*(void**)arr + i * 0x1d8);
        Box18 b;
        ((TSelf0)F_00409c00)(&b);
        void* p = F_00401010();
        bool ok = ((TSix)(*(void***)p)[0x54 / 4])(p, *(void**)(ep + 4), *(void**)(ep + 0),
                                                  ep + 0x94, *(void**)(ep + 0x90), &b, &b.v[3]);
        if (!ok)
            continue;
        BoundRec r;
        ((TSelf0)F_00409930)(&r);
        *(int*)&r.x = *(int*)(ep + 0x14);
        *(int*)&r.y = *(int*)(ep + 0x18);
        *(int*)&r.z = *(int*)(ep + 0x1c);
        r.flags |= 4;
        ++r.count;
        Mat3_ hidden;
        Mat3_* q = (Mat3_*)F_0041de20(&hidden, ep + 0x5c, ep + 0x38);
        Mat3_ tmp;
        ((TSelf0)F_00402ab0)(&tmp);
        tmp = *q;
        r.mat = tmp;
        r.flags |= 2;
        ++r.count;
        *(int*)&r.w = *(int*)(ep + 0x10);
        ++r.count;
        ((TSelf1)F_00409dd0)(&b, &r);
        ((TSelf1)F_0043f050)(&box, &b);
        if (out != 0) {
            float d0 = fabsf(b.v[3] - b.v[0]);
            float d1 = fabsf(b.v[4] - b.v[1]);
            float d2 = fabsf(b.v[5] - b.v[2]);
            *out = d0 * d1 * d2 + *out;
        }
    }
    ((TSelf1)F_00511140)(self, &box);
    return self;
}

// ==========================================================================
// cSerializedEditorBlock (0x1d8 bytes) -- retail block record
// ==========================================================================
namespace rw { namespace math { namespace fpu {

template <class T, int Aligned>
class Vector3Template {
public:
    T x, y, z;
};

template <class T, int Aligned>
class Matrix33Template {
public:
    Vector3Template<T, Aligned> xAxis, yAxis, zAxis;
    Matrix33Template& operator=(const Matrix33Template& v);   // 0x41cb40 (cSPMatrix3::Assign)
};

} } }

struct cSPVector3 : public rw::math::fpu::Vector3Template<float, 0> {};
struct cSPMatrix3 : public rw::math::fpu::Matrix33Template<float, 0> {};
struct cSPColorRGB : public rw::math::fpu::Vector3Template<float, 0> {};

struct Float8 { float v[8]; };
struct UInt8  { unsigned int v[8]; };
struct Int8   { int v[8]; };

namespace SP {

struct cSerializedEditorBlock {
    unsigned int mGroup;             // +0x00
    unsigned int mInstance;          // +0x04
    unsigned int mParentIndex;       // +0x08
    unsigned int mSymmetricIndex;    // +0x0c
    float mUniformScale;             // +0x10
    cSPVector3 mPosition;            // +0x14
    cSPVector3 mPinningDirection;    // +0x20
    cSPVector3 mPinningOrigin;       // +0x2c
    cSPMatrix3 mBaseOrientation;     // +0x38
    cSPMatrix3 mUserOrientation;     // +0x5c
    unsigned char mIsSnapped;        // +0x80
    unsigned char m_RESERVED1;       // +0x81
    unsigned char m_RESERVED2;       // +0x82
    unsigned char m_RESERVED3;       // +0x83
    unsigned int mLimbType;          // +0x84
    float mMuscleScale;              // +0x88
    float mBaseJointScale;           // +0x8c
    unsigned int mNumHandles;        // +0x90
    Float8 mHandlePositions;         // +0x94
    UInt8 mHandleAnimations;         // +0xb4
    unsigned int mNumPaintRegions;   // +0xd4
    Int8 mPaintRegions;              // +0xd8
    UInt8 mPaintIDs;                 // +0xf8
    cSPColorRGB mPaintColor1s[8];    // +0x118
    cSPColorRGB mPaintColor2s[8];    // +0x178

    cSerializedEditorBlock(const cSerializedEditorBlock&);
};

class cEditorResource {
public:
    unsigned int mPad00[6];             // +0x00
    unsigned int mModelType;            // +0x18 (cSerializedEditorModel::mModelType)
    unsigned int mPad1c[0x1f];          // +0x1c .. +0x97
    cSerializedEditorBlock* mBlocksBegin;   // +0x98
    cSerializedEditorBlock* mBlocksEnd;     // +0x9c
};

class cPropertyList;

namespace EditorUtils {
    void AddInitialBoundInfo(cEditorResource* pResource, cPropertyList* pList);
}

} // namespace SP

inline void CopyVec3f(cSPVector3* d, const cSPVector3* s)
{
    d->x = s->x;
    d->y = s->y;
    d->z = s->z;
}

inline void CopyColorArray(cSPColorRGB* d, const cSPColorRGB* s, int n)
{
    while (--n >= 0)
    {
        d->x = s->x;
        d->y = s->y;
        d->z = s->z;
        ++d;
        ++s;
    }
}

// @ 0x004721e0
SP::cSerializedEditorBlock::cSerializedEditorBlock(const SP::cSerializedEditorBlock& o)
{
    mGroup = o.mGroup;
    mInstance = o.mInstance;
    mParentIndex = o.mParentIndex;
    mSymmetricIndex = o.mSymmetricIndex;
    mUniformScale = o.mUniformScale;
    CopyVec3f(&mPosition, &o.mPosition);
    CopyVec3f(&mPinningDirection, &o.mPinningDirection);
    CopyVec3f(&mPinningOrigin, &o.mPinningOrigin);
    ScratchSlots<9>();
    mBaseOrientation = o.mBaseOrientation;
    ScratchSlots<9>();
    mUserOrientation = o.mUserOrientation;
    mIsSnapped = o.mIsSnapped;
    m_RESERVED1 = o.m_RESERVED1;
    m_RESERVED2 = o.m_RESERVED2;
    m_RESERVED3 = o.m_RESERVED3;
    mLimbType = o.mLimbType;
    mMuscleScale = o.mMuscleScale;
    mBaseJointScale = o.mBaseJointScale;
    mNumHandles = o.mNumHandles;
    mHandlePositions = o.mHandlePositions;
    mHandleAnimations = o.mHandleAnimations;
    mNumPaintRegions = o.mNumPaintRegions;
    mPaintRegions = o.mPaintRegions;
    mPaintIDs = o.mPaintIDs;
    CopyColorArray(mPaintColor1s, o.mPaintColor1s, 8);
    CopyColorArray(mPaintColor2s, o.mPaintColor2s, 8);
}

// ==========================================================================
// IntVecObj (two vptrs at +0/+4, refcount at +8, int vector at +0xc).
// The original class used multiple inheritance; the two base vptrs and their
// destructor vtable stores are written explicitly here so the layout and the
// observed writes stay identical.
// ==========================================================================
void F_00425990();               // 0x425990 __thiscall: vector<int>::~vector

struct ObjBase {
    void* mVtbl;                 // +0x00
    ObjBase() { mVtbl = (void*)0x13eb938; }
    ~ObjBase() { mVtbl = (void*)0x13eb938; }
};

struct RefCountedBase {
    void* mVtbl;                 // +0x00
    volatile long mRefCount;     // +0x04
    RefCountedBase()
    {
        mVtbl = (void*)0x13ef094;
        long volatile* pRef = &mRefCount;
        _InterlockedExchange(pRef, 0);
    }
    ~RefCountedBase() { mVtbl = (void*)0x13ef094; }
};

struct IntVector {
    int* mpBegin;                // +0x00
    int* mpEnd;                  // +0x04
    int* mpCapacity;             // +0x08
    void Init()
    {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
    }
    ~IntVector()
    {
        ScratchSlots<3>();
        for (int* p = mpBegin; p < mpEnd; ++p) { }
        ((TSelf0)F_00425990)(this);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    int* begin() const { return mpBegin; }
};

static int VecCount(const IntVector& v) { return (int)(v.mpEnd - v.mpBegin); }

struct RefTarget {
    virtual void AddRef();
};

struct IntrusivePtr {
    RefTarget* mPtr;             // +0x00
    IntrusivePtr& operator=(void* p)
    {
        mPtr = (RefTarget*)p;
        if (mPtr != 0)
            mPtr->AddRef();
        return *this;
    }
};

struct BufView {
    int count;                   // +0x00
    char* data;                  // +0x04
    unsigned short maskIdx;      // +0x08
    unsigned short stride;       // +0x0a
    IntrusivePtr ref;            // +0x0c
    void SetCount(int n) { count = n; }
};

struct IntVecObj : ObjBase, RefCountedBase {
    IntVector mVec;              // +0x0c
    unsigned int mPad18;         // +0x18
    unsigned int mPad1c;         // +0x1c
    int mField20;                // +0x20

    IntVecObj();
    ~IntVecObj();
    BufView* GetView(BufView* pView);
};

// @ 0x00472860
IntVecObj::IntVecObj()
{
    int dummy;
    (void)dummy;
    ObjBase::mVtbl = (void*)0x13ef09c;              // IntVecObj vftables
    RefCountedBase::mVtbl = (void*)0x13ef098;
    mVec.Init();
    mField20 = 0;
}

// @ 0x004728e0
BufView* IntVecObj::GetView(BufView* pView)
{
    int* pBegin = mVec.begin();
    IntrusivePtr* pRef;
    int nCount = mVec.size();
    pView->count = nCount;
    pView->data = (char*)pBegin;
    pView->maskIdx = 4;
    pView->stride = 4;
    pRef = &pView->ref;
    *pRef = this;
    return pView;
}

// @ 0x00472aa0
IntVecObj::~IntVecObj()
{
}

// ==========================================================================
// eastl::fixed_vector<int,1> (inline buffer at +0x18)
// ==========================================================================
struct FixedVecInt1 {
    int* mpBegin;                // +0x00
    int* mpEnd;                  // +0x04
    int* mpCapacity;             // +0x08
    unsigned int mPad0c;         // +0x0c
    unsigned int mPad10;         // +0x10
    unsigned int mHeapFlag;      // +0x14
    int mBuffer[1];              // +0x18
    FixedVecInt1(int n, const int& value);
};

void F_00474840();               // 0x474840 __thiscall: vector<int>::resize(n, value)

// @ 0x00472990
FixedVecInt1::FixedVecInt1(int n, const int& value)
{
    ScratchSlots<0x12>();
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    mHeapFlag = 0;
    mpBegin = mBuffer;
    mpEnd = mpBegin;
    mpCapacity = mpBegin + 1;
    ((void (__thiscall*)(void*, int, const int*))F_00474840)(this, n, &value);
}

// ==========================================================================
// SP::EditorUtils::AddInitialBoundInfo (0x71b50)
// ==========================================================================
struct FixedVecU64 {
    unsigned __int64* mpBegin;        // +0x00
    unsigned __int64* mpEnd;          // +0x04
    unsigned __int64* mpCapacity;     // +0x08
    unsigned int mPad0c;              // +0x0c
    unsigned int mPad10;              // +0x10
    unsigned int mHeapFlag;           // +0x14
    unsigned __int64 mBuffer[64];     // +0x18
};

struct FixedVecBox {
    Box18* mpBegin;                   // +0x00
    Box18* mpEnd;                     // +0x04
    Box18* mpCapacity;                // +0x08
    unsigned int mPad0c;              // +0x0c
    unsigned int mPad10;              // +0x10
    unsigned int mHeapFlag;           // +0x14
    Box18 mBuffer[64];                // +0x18
};

struct AllocTagByte { unsigned char b; };

extern cSPVector3 kDefaultBoundCenter;   // 0x15d4034
extern float kDefaultBoundRadius;        // 0x1488874

void F_00409ce0();               // 0x409ce0 __thiscall: box set center/radius
void F_00409dd0();               // 0x409dd0 __thiscall: box transform by record
void F_0041e770();               // 0x41e770 __thiscall: vector<Box18>::reserve
void F_0041e8b0();               // 0x41e8b0 __thiscall: vector<Box18>::push_back
void F_0041da70();               // 0x41da70 __thiscall: fixed_vector<Box18,64> ctor
void F_0041e730();               // 0x41e730 __thiscall: vector<Box18> dtor
void F_004756f0();               // 0x4756f0 __thiscall: vector<u64>::resize
void F_00475800();               // 0x475800 __thiscall: vector<u64>::push_back
void F_004c5e30();               // 0x4c5e30 __thiscall: fixed_vector<u64,64> ctor
void F_004cddd0();               // 0x4cddd0 __thiscall: vector<u64> dtor
void F_00540470();               // 0x540470 __thiscall: vector base ctor (allocator)
void F_00471000();               // 0x471000 cdecl: bound-info builder overload

// @ 0x00471b50
void SP::EditorUtils::AddInitialBoundInfo(SP::cEditorResource* pResource, SP::cPropertyList* pList)
{
    if (pResource == 0)
        return;

    FixedVecU64 keys;
    AllocTagByte allocA;
    ((void (__thiscall*)(void*, const void*))F_00540470)(&keys, &allocA);
    ((TSelf0)F_004c5e30)(&keys);

    FixedVecBox boxes;
    AllocTagByte allocB;
    ((void (__thiscall*)(void*, const void*))F_00540470)(&boxes, &allocB);
    ((TSelf0)F_0041da70)(&boxes);

    int count = (int)((char*)pResource->mBlocksEnd - (char*)pResource->mBlocksBegin) / 0x1d8;
    ((void (__thiscall*)(void*, int))F_004756f0)(&keys, count);
    ((void (__thiscall*)(void*, int))F_0041e770)(&boxes, count);

    for (int i = 0; i < count; ++i) {
        SP::cSerializedEditorBlock* e =
            (SP::cSerializedEditorBlock*)((char*)pResource->mBlocksBegin + i * 0x1d8);

        BoundRec rec;
        ((TSelf0)F_00409930)(&rec);
        *(int*)&rec.x = *(int*)&e->mPosition.x;
        *(int*)&rec.y = *(int*)&e->mPosition.y;
        *(int*)&rec.z = *(int*)&e->mPosition.z;
        rec.flags |= 4;
        ++rec.count;
        *(int*)&rec.w = *(int*)&e->mUniformScale;
        ++rec.count;

        Mat3_ hidden;
        Mat3_* q = (Mat3_*)((void* (__cdecl*)(void*, void*, void*))F_0041de20)
            (&hidden, &e->mUserOrientation, &e->mBaseOrientation);
        Mat3_ tmp = *q;
        rec.mat = tmp;
        rec.flags |= 2;
        ++rec.count;

        Box18 box;
        ((TSelf0)F_00409c00)(&box);
        void* singleton = ((void* (__cdecl*)())F_00401010)();
        bool belongs = ((TSix)(*(void***)singleton)[0x54 / 4])
            (singleton, (void*)*(int*)&e->mInstance, (void*)*(int*)&e->mGroup,
             (char*)e + 0x94, (void*)*(int*)&e->mNumHandles,
             &box.v[0], &box.v[3]);
        (void)belongs;

        if (box.v[0] > box.v[3]) {
            ((void (__thiscall*)(void*, const void*, float))F_00409ce0)
                (&box, &kDefaultBoundCenter, kDefaultBoundRadius);
        }
        ((TSelf1)F_00409dd0)(&box, &rec);
        ((TSelf1)F_0041e8b0)(&boxes, &box);

        unsigned __int64 key =
            ((unsigned __int64)e->mGroup << 32) | (unsigned __int64)e->mInstance;
        ((TSelf1)F_00475800)(&keys, &key);
    }

    ((void (__cdecl*)(unsigned __int64*, Box18*, int, int, SP::cPropertyList*))F_00471000)
        ((unsigned __int64*)keys.mpBegin, (Box18*)boxes.mpBegin, count,
         (int)pResource->mModelType, pList);
    ((TSelf0)F_0041e730)(&boxes);
    ((TSelf0)F_004cddd0)(&keys);
}
