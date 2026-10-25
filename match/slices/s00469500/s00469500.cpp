// s00469500 -- functions 00469500 00469550 00469590 004696d0 00469790 00469920
// /Od /Ob1 region.

#include "types.h"

extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

struct S45sub {
    // 4-byte subobject constructed by FUN_00401b80(caller this+0x10, arg)
    S45sub(int);
};

// 00469500: 4 int members + a subobject at +0x10 constructed from the 5th arg.
struct S45a {
    int a, b, c, d;
    S45sub sub;
    S45a(int, int, int, int, int);
};

// @ 0x00469500
S45a::S45a(int a_, int b_, int c_, int d_, int e_)
    : a(a_), b(b_), c(c_), d(d_), sub(e_)
{
    int hole_;
    (void)hole_;
}

// 00469550: 5 int members.
struct S45b {
    int a, b, c, d, e;
    S45b* init(int, int, int, int, int);
};

// @ 0x00469550
S45b* S45b::init(int a_, int b_, int c_, int d_, int e_)
{
    a = a_;
    b = b_;
    c = c_;
    d = d_;
    e = e_;
    return this;
}

// 004696d0: copy-assignment; 7 members of 0x14 bytes, each assigned via its own
// out-of-line operator=.
struct M45 {
    char pad[0x14];
    M45& operator=(const M45&);
};

struct S45c {
    M45 m0, m1, m2, m3, m4, m5, m6;
    S45c& operator=(const S45c&);
};

// @ 0x004696d0
S45c& S45c::operator=(const S45c& o)
{
    m0 = o.m0;
    m1 = o.m1;
    m2 = o.m2;
    m3 = o.m3;
    m4 = o.m4;
    m5 = o.m5;
    m6 = o.m6;
    return *this;
}

// ---- MeshUploadJob ----------------------------------------------------------
// Editor model-mesh upload job.  The class is built from the retail object layout:
//   +0x00 cILayer-like primary base (vtable 0x13f1ab0) on IRefCount-like base (0x13eb938)
//   +0x04 refcount base (vtable 0x13ef094), its counter at +0x08
//   +0x0c ... data members (see below).  Only the ctor/dtor are in this slice; Run
//   lives in s004680c0.

struct ModelMesh {
    virtual int AddRef();                 // 0x00461290
    virtual int Release();                // 0x00472970
};

struct Holder10 {
    virtual int AddRef();
    virtual int Release();
};

struct ThreadedObject {
    void Release();                       // 0x00404f90
};

struct cJob {
    int Release();                        // 0x00690120
};

// EA::Thread::AtomicInt<int>: the ctor stores with an interlocked exchange.
struct AtomicInt {
    volatile long mValue;
    AtomicInt(long n = 0) { _InterlockedExchange(&mValue, n); }
};

// IRefCount-like primary base (vtable 0x13eb938).  Its destructor is the only
// user-declared destructor in the primary chain: the 0x13f1ab0 layer's is
// implicit, which is why the complete destructor restores 0x13eb938 and not
// 0x13f1ab0.
struct UploadIRef {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~UploadIRef() {}
};

// cILayer-like base (vtable 0x13f1ab0); implicit ctor/dtor.
struct UploadLayer : UploadIRef {
    virtual void DrawLayer() = 0;
};

// Refcount base (vtable 0x13ef094) with the counter at +0x04 of the subobject.
struct UploadRef {
    virtual ~UploadRef() {}
    AtomicInt mRefCount;
};

// /Od reserves a stack slot for an unused local of an inlined callee (the "declined inline hole"
// pattern of s004680c0); at function scope it lands at the bottom of the frame.
template <int N>
inline void ScratchSlots()
{
    uint32_t s[N];
}

struct MeshObjRef {
    ModelMesh* p;
    MeshObjRef() : p(0) {}
    ~MeshObjRef()
    {
        if (p)
            p->Release();
    }
};

struct HolderRef {
    Holder10* p;
    HolderRef() : p(0) {}
    ~HolderRef()
    {
        ScratchSlots<3>();
        if (p)
            p->Release();
    }
};

// 0x8c-byte editor subobject constructed by 0x00460f80, destroyed by 0x00418a10.
struct Sub14 {
    uint32_t mData[0x8c / 4];
    Sub14();                              // 0x00460f80
    ~Sub14();                             // 0x00418a10
};

// 0x14-byte vector with 0x38-byte elements: inline ctor zeroes the three pointers.
struct VecA0 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    VecA0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VecA0();                             // 0x0041e090
};

// 0x14-byte vector of eastl::string16.
struct StrVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    uint32_t mAllocator[2];
    StrVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~StrVec();                            // 0x004748c0
};

struct ThreadedRef {
    ThreadedObject* p;
    ThreadedRef() : p(0) {}
    ~ThreadedRef()
    {
        ScratchSlots<3>();
        if (p)
            p->Release();
    }
};

struct Vector3 {
    float x, y, z;
};

struct JobRef {
    cJob* p;
    JobRef() : p(0) {}
    ~JobRef()
    {
        if (p)
            p->Release();
    }
};

// eastl fixed_vector's destructor destroys the live range inline (trivial element dtors leave an
// empty step loop at /Od) and then calls the out-of-line storage base destructor.
template <class T>
inline void Destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}

// 0x38-byte fixed_vector<uint32_t, 8>: three pointers, two allocator words, a zeroed flag and
// 8 inline elements at +0x18.  ctor 0x00472740, storage dtor 0x00425990.
struct U32Vec {
    uint32_t* mpBegin;                    // +0x00
    uint32_t* mpEnd;                      // +0x04
    uint32_t* mpCapacity;                 // +0x08
    uint32_t mAllocator[2];               // +0x0c
    uint32_t mFlag;                       // +0x14
    uint32_t mStorage[8];                 // +0x18
    U32Vec();                             // 0x00472740
    void DoFree();                        // 0x00425990 (storage base destructor, thiscall)
    ~U32Vec() { Destruct(mpBegin, mpEnd); DoFree(); }
};

// 0x58-byte fixed_vector of 8-byte sized spans; ctor 0x004727a0, storage dtor 0x0045daf0.
struct SizedSpan {
    int mCount;
    void* mpData;
};

struct SpanVec {
    SizedSpan* mpBegin;                   // +0x00
    SizedSpan* mpEnd;                     // +0x04
    SizedSpan* mpCapacity;                // +0x08
    uint32_t mAllocator[2];               // +0x0c
    uint32_t mFlag;                       // +0x14
    SizedSpan mStorage[8];                // +0x18
    SpanVec();                            // 0x004727a0
    void DoFree();                        // 0x0045daf0 (storage base destructor, thiscall)
    ~SpanVec() { Destruct(mpBegin, mpEnd); DoFree(); }
};

// 0x1f18-byte fixed vector of 64 0x7c-byte elements (inline storage at +0x18).
// ctor 0x00472800; the destructor is inline: destroy the range, then free.
struct BigVec {
    uint32_t* mpBegin;                    // +0x00
    uint32_t* mpEnd;                      // +0x04
    uint32_t* mpCapacity;                 // +0x08
    uint32_t mAllocator[2];               // +0x0c
    uint32_t mFlags;                      // +0x14
    uint32_t mStorage[0x1f00 / 4];        // +0x18
    BigVec();                             // 0x00472800
    void DestroyRange(void* first, void* last);   // 0x004777e0 (thiscall)
    void DoFree();                        // 0x00424b40 (thiscall)
    ~BigVec()
    {
        DestroyRange(mpBegin, mpEnd);
        DoFree();
    }
};

class MeshUploadJob : public UploadLayer, public UploadRef {
public:
    virtual int AddRef();                 // 0x00461290
    virtual int Release();                // 0x00472970
    virtual void DrawLayer();             // 0x00561150

    MeshObjRef mpMesh;                    // +0x00c
    HolderRef mpHolder;                   // +0x010
    Sub14 mSub14;                         // +0x014
    VecA0 mVecA0;                         // +0x0a0
    StrVec mVecB4;                        // +0x0b4
    ThreadedRef mC8;                      // +0x0c8
    Vector3 mOffset;                      // +0x0cc
    uint32_t mInstanceID;                 // +0x0d8
    uint32_t mTypeID;                     // +0x0dc
    JobRef mJob;                          // +0x0e0
    uint8_t* mBytesBegin;                 // +0x0e4
    uint8_t* mBytesEnd;                   // +0x0e8
    U32Vec mPartRanges;                   // +0x0ec (fixed_vector, ends at +0x124)
    U32Vec mVertexCounts;                 // +0x124 (ends at +0x15c)
    SpanVec mSpans;                       // +0x15c
    BigVec mBig;                          // +0x1b4

    MeshUploadJob();
};

// @ 0x00469590
// The retail frame has two unused slots around the member-initialisation temps: `p30` occupies the
// top one and the inlined ScratchSlots local the bottom one (see od_names.py for the name).
MeshUploadJob::MeshUploadJob()
{
    int p30;
    ScratchSlots<1>();
}

// @ 0x00469790
// MeshUploadJob::~MeshUploadJob is compiler-generated from the member and base
// list above (no user destructor: the complete-object destructor has no derived
// vptr store at entry).
MeshUploadJob* g_meshUploadJob;
void ForceMeshUploadJobCtor() { g_meshUploadJob = new MeshUploadJob; }

// ---- not yet reproduced -----------------------------------------------------

// ---- LoadKeyDefault (0x00469920) -------------------------------------------
// Looks up a property list for (instanceID, groupID), falling back to the
// default key with progressively relaxed type bits, and returns a fresh
// property list through `out`.
extern const char kEditorAllocName[];   // "Editor" @ 0x013eb430
void* operator new(uint32_t size, const char* name, int, int, int, int);
void operator delete(void* p, const char* name, int, int, int, int);

struct cPropertyList;

struct IPropertyManager {
    virtual void pv0();
    virtual void pv1();
    virtual void pv2();
    virtual void pv3();
    virtual void pv4();
    virtual void pv5();
    virtual void pv6();
    virtual void pv7();
    virtual void pv8();
    virtual void pv9();
    virtual void pv10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, cPropertyList** out);   // +0x2c
    virtual void pv12();
    virtual void SetPropList(cPropertyList* list, uint32_t key, uint32_t typeID);               // +0x34
};
IPropertyManager* PropertyManager();   // 0x0067de30

struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    void SetParent(cPropertyList* parent);   // 0x006a1710
    cPropertyList();                         // 0x006a1c40
    uint32_t mPad[0x0d];                     // sizeof == 0x38
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount()
    {
        if (mpObject)
            mpObject->Release();
    }
    T** AsPPVoidParam();                     // out of line, like 0x41d870
    T** operator&() { return AsPPVoidParam(); }
    __forceinline T** AsOutParam()
    {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* old = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
    T* Detach()
    {
        T* p = mpObject;
        mpObject = 0;
        return p;
    }
};

template <class T>
T** AutoRefCount<T>::AsPPVoidParam()
{
    if (mpObject) {
        T* p = mpObject;
        mpObject = 0;
        p->Release();
    }
    return &mpObject;
}

struct TypeIDBits {
    uint32_t lo : 8;
    uint32_t variant : 8;
    uint32_t mid : 8;
    uint32_t field5 : 5;
    uint32_t rest : 3;
};

__forceinline uint32_t SetField5(uint32_t t, uint32_t v)
{
    ((TypeIDBits*)&t)->field5 = v;
    return t;
}

__forceinline uint32_t SetVariantLow(uint32_t t, uint32_t variant, uint32_t low)
{
    ((TypeIDBits*)&t)->variant = variant;
    ((TypeIDBits*)&t)->lo = low;
    return t;
}

// @ 0x00469920
bool LoadKeyDefault(uint32_t instanceID, uint32_t groupID, cPropertyList** out)
{
    AutoRefCount<cPropertyList> result;
    bool t = false;
    if (!PropertyManager()->GetPropertyList(instanceID, groupID, &result)) {
        uint32_t key2 = 0x4529f96f;
        uint32_t type2 = groupID;
        {
            AutoRefCount<cPropertyList> found;
            PropertyManager()->GetPropertyList(key2, type2, found.AsOutParam());
            if (!found) {
                type2 = SetField5(type2, 0);
                PropertyManager()->GetPropertyList(key2, type2, found.AsOutParam());
            }
            if (!found) {
                type2 = SetVariantLow(type2, 0x62, 0);
                PropertyManager()->GetPropertyList(key2, type2, found.AsOutParam());
            }
            result = new (kEditorAllocName, 0, 0, 0, 0) cPropertyList();
            t = true;
            if (found) {
                result->SetParent(found);
                PropertyManager()->SetPropList(result, instanceID, groupID);
            }
        }
    }
    if (out)
        *out = result.Detach();
    return t;
}
