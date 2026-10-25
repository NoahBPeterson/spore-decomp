// Slice s00767ee0: "RenderAsset" raster writer, resource reload/arm helpers,
// 0x7c-stride vector resize and the BakeSprites job ctors/dtors.
// /O2 /MD /Gy /EHsc /TP.  The BakeSprites ctor/dtor rows need /GS- (retail has no
// stack cookie there; every manifest row states its own flags).
#include "types.h"
#include <intrin.h>
#include <string.h>
#include <new>

extern char g_file[];

extern "C" {
void* __cdecl Alloc6(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  __cdecl Dealloc(void* p);                                             // 0xf47380
void  __cdecl FUN_00764760(void* self, int v);                              // 0x764760 (thiscall)
void  __cdecl FUN_0041f2d0(void* p);                                        // 0x41f2d0
void  __cdecl FUN_00700670(void* a, void* b);                               // 0x700670
void  __cdecl FUN_00767760(void* p);                                        // 0x767760
void  __cdecl FUN_00767350(void* self, void* pos, uint32_t n, void* value); // 0x767350
void  __cdecl FUN_0041cc60(void* p);                                        // 0x41cc60
void  __cdecl FUN_007003a0(void* a, int n);                                 // 0x7003a0
bool  __cdecl ReadValue68(void* stream, void* dst, int n);   // 0x93a6c0
bool  __cdecl WriteValue68(void* stream, int a, uint32_t b); // 0x93a890
}
// C++ linkage on purpose: the dtor calls these from an EH-tracked cleanup sequence,
// so /EHsc (correctly) treats them as throwing and emits the unwind state stores.
void __cdecl UnionDestroy(void* p, int type);          // 0x7668c0
void __fastcall FUN_007642c0(void* self);              // 0x7642c0

// ===========================================================================
// @ 0x00767ee0  SP::cGraphicsResourceFactory::WriteResourceRaster
// ===========================================================================
struct Raster {
    char pad0[4];
    int mFlags;               // +0x4
    char pad8[4];
    unsigned short mWidth;    // +0xc
    unsigned short mHeight;   // +0xe
    unsigned char mLevels;    // +0x11
    unsigned char mFace;      // +0x12
};
int __stdcall WriteResourceRaster(void* arg, int* stream) {
    Raster* r = *(Raster**)((char*)arg + 0x18);
    (void)r; (void)stream;
    // full writer is a register-heavy event loop over mip levels/faces;
    // modelled only structurally here.
    return 1;
}

// ===========================================================================
// @ 0x00768200  release the current raster-load union state
// ===========================================================================
struct C68200 {
    char pad[0xd0];
    int mD0;                  // +0xd0
    void Release();
};
void C68200::Release() {
    int v = mD0;
    if (v) {
        if (v == 5) {
            FUN_007642c0(this);
        } else {
            UnionDestroy(this, v);
        }
        mD0 = 0;
    }
}

// ===========================================================================
// @ 0x00768240  ctor: init a 0x7c-stride inline vector and register a job
// ===========================================================================
struct C68240 {
    void* m0;                 // +0x00
    void* m4;                 // +0x04
    void* m8;                 // +0x08
    int   mc;                 // +0x0c
    void* m10;                // +0x10
    int   m14;                // +0x14
    char  m18[0x7c];          // +0x18 inline storage
    C68240(void* arg);
    // 0x00767760 takes this in ecx (0x767762 mov %ecx,%edi; reads 0x0/0x4(%edi)) and the count as
    // its single stack argument, so it must be called as a member, not as a cdecl free function.
    void RegisterJob(void* arg);                               // 0x00767760
};
C68240::C68240(void* arg) {
    char* base = m18;
    m10 = base;
    m4 = base;
    m0 = base;
    m8 = base + 0x80;
    RegisterJob(arg);
}

// ===========================================================================
// @ 0x007682a0  vector<0x7c>::resize(n)
// ===========================================================================
// The 0x7c-byte element temp that Resize constructs on the stack: both helpers take the buffer in
// ecx (0x764760 reads/writes (%esi).., 0x41f2d0 touches +0x74/+0x78), so they are spelled as
// members of the temp type and called through the object.
struct Tmp7c {
    char raw[0x7c];
    void Init(int v);          // 0x00764760
    void Destroy();            // 0x0041F2D0
};

struct V7cB {
    char* b; char* e; char* c;
    void Resize(uint32_t n);
    // Both helpers take the vector in ecx and all their arguments on the stack:
    // 0x7682ea pushes value (the stack temp), count and e, then sets %ecx before calling 0x767350.
    void InsertFill(char* pos, uint32_t n, void* value);       // 0x00767350
    void DestroyRange(char* first, char* last);                // 0x00700670
};
void V7cB::Resize(uint32_t n) {
    uint32_t count = (uint32_t)((e - b) / 0x7c);
    if (count < n) {
        Tmp7c tmp;
        tmp.Init(0);
        InsertFill(e, n - count, &tmp);
        tmp.Destroy();
    } else {
        DestroyRange(b + n * 0x7c, e);
    }
}

// ===========================================================================
// BakeSprites job object (0x00768370 ctor / 0x00768540 dtor)
// ===========================================================================
// EA::Thread::AtomicInt<int>
struct AtomicInt {
    volatile long mValue;
    AtomicInt(long n = 0) { _InterlockedExchange(&mValue, n); }
};

// primary base chain: BakeIRef (vtable 0x13f1ab0) <- BakeLayer
struct BakeIRef {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~BakeIRef() {}
};
struct BakeLayer : BakeIRef {
    virtual void DrawLayer() = 0;
};
// secondary base (vtable 0x13ef094), its refcount lives inside the subobject
struct BakeRef {
    virtual ~BakeRef() {}
    AtomicInt mRefCount;
};

// IObj: AddRef = slot 1, Release = slot 2, kind query = slot 3, child factory = slot 6
struct IObj {
    virtual void v0();
    virtual int  AddRef();
    virtual int  Release();
    virtual int  GetKind();
    virtual void v4();
    virtual void v5();
    virtual IObj* GetChild();
};
// IRefB: AddRef = slot 0, Release = slot 1
struct IRefB {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// discriminated union member at +0x2c, tag at its end (+0xd0)
struct UnionState {
    char mBytes[0xd0];
    int  mType;
    UnionState() : mType(0) {}
    ~UnionState();
};
UnionState::~UnionState()
{
    if (mType) {
        if (mType == 5) FUN_007642c0(mBytes);
        else            UnionDestroy(mBytes, mType);
        mType = 0;
    }
}

// fixed-capacity vectors
struct VecA {
    IRefB** mpBegin;                    // +0x00
    IRefB** mpEnd;                      // +0x04
    IRefB** mpCapacity;                 // +0x08
    uint32_t mAllocator[2];             // +0x0c
    uint32_t mFlag;                     // +0x14
    void*   mStorage[0x80 / 4];         // +0x18
    VecA()
    {
        mpBegin = (IRefB**)mStorage;
        mpEnd   = mpBegin;
        mFlag = 0;
        mpCapacity = (IRefB**)((char*)mpBegin + 0x80);
    }
    ~VecA();                            // 0x4b5440
};
struct VecB {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCapacity;                  // +0x08
    uint32_t mAllocator[2];             // +0x0c
    uint32_t mFlag;                     // +0x14
    void*  mStorage[0x180 / 4];         // +0x18
    VecB()
    {
        mpBegin = mStorage;
        mpEnd   = mpBegin;
        mFlag = 0;
        mpCapacity = (void**)((char*)mpBegin + 0x180);
    }
    ~VecB()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            Dealloc(mpBegin);
    }
};

// object built by the ctor's child step (0x34 bytes; allocated through the global
// operator new 0xf473a0, ctor 0x93b530)
void* operator new(unsigned size, const char* name, int, int, int, int);
void  operator delete(void* p, const char* name, int, int, int, int);
struct Child : IObj {
    Child(int, int, IObj*);             // 0x93b530
    char mPad[0x30];                    // sizeof == 0x34
};

class C68370 : public BakeLayer, public BakeRef {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void DrawLayer();

    C68370(IRefB* a, IObj* b, int* c, IObj* d, int e);
    ~C68370();

    AutoRef<IObj> m_pC;                 // +0x0c
    AutoRef<IObj> m_pE;                 // +0x10
    AutoRef<IRefB> m_pA;                // +0x14
    int   m_v18;                        // +0x18
    int   m_v1c;                        // +0x1c
    int   m_v20;                        // +0x20
    int   m_v24;                        // +0x24
    AutoRef<IObj> m_p28;                // +0x28
    UnionState m_state;                 // +0x2c
    AutoRef<IRefB> m_100;               // +0x100
    VecA  m_vecA;                       // +0x104
    VecB  m_vecB;                       // +0x19c
    char  m334;                         // +0x334
};

// @ 0x00768370
C68370::C68370(IRefB* a, IObj* b, int* c, IObj* d, int e)
    : m_pC(b), m_pE(d), m_pA(a), m_v18(e), m_v1c(c[0]), m_v20(c[1]), m_v24(c[2])
{
    m334 = 0;
    IObj* p = m_pE->GetChild();
    if (p) {
        if (p->GetKind() == 0x34722300)
            p = new ("Graphics", 0, 0, 0, 0) Child(0x2000, 0, p);
        m_p28 = p;
    }
}

// @ 0x00768540
C68370::~C68370()
{
}

// ===========================================================================
// @ 0x00768650  load a set of 0x7c records and attach visual effects
// ===========================================================================
struct C68650 {
    char pad[0x108];
    void* vecBegin;           // +0x108
    char pad10c[4];
    void* vecEnd;             // +0x10c  (approximate)
};
bool __stdcall LoadRecords(void* stream, int obj) {
    uint32_t count;
    if (!ReadValue68(stream, &count, 4))
        return false;
    if (!WriteValue68(stream, 0x38, count))
        return false;
    // per-record load + visual-effect attach (structurally modelled)
    for (uint32_t i = 0; i < count; i++) {
        void* rec = (void*)(*(int*)(obj + 0x108) + i * 0x7c);
        if (!ReadValue68(stream, rec, 0x38)) return false;
        if (!ReadValue68(stream, (char*)rec + 0x38, 0x38)) return false;
        if (!ReadValue68(stream, (char*)rec + 0x70, 4)) return false;
    }
    return true;
}
