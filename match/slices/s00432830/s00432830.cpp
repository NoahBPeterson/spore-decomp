// Editor/Graphics helpers around 0x00432830: a sprite-block initializer, the refcounted
// property-list resource chain (EditorResource <- BakeSprites <- PropertyList <- ResourceList
// <- SpriteBuffer, with a secondary base at +0x18), small pointer-vector destructors,
// adjustor thunks and a member-function-pointer call thunk.
// Built without optimization: /Od /Ob1 /arch:SSE (frame pointer, locals in memory).
#include "types.h"

extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* target, long value);
extern "C" long __cdecl _InterlockedIncrement(long volatile* target);
extern "C" long __cdecl _InterlockedDecrement(long volatile* target);
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int align,
                                       const char* file, int line);
void  __cdecl EASTL_allocator_deallocate(void* p);

extern float g_Zero;   // 0x01485378

// @ 0x00432830
struct SpriteBlock {
    float f[5];
    int   i[6];
    SpriteBlock();
};
SpriteBlock::SpriteBlock()
{
    f[0] = g_Zero; f[1] = g_Zero; f[2] = g_Zero; f[3] = g_Zero; f[4] = g_Zero;
    i[0] = 0; i[1] = 0; i[2] = 0; i[3] = 0; i[4] = 0; i[5] = 0;
}

// ---------------------------------------------------------------- generic Object refcount
class Object {
public:
    virtual int   v0();
    virtual int   v1();
    virtual ~Object();                       // scalar deleting destructor (+8)
    volatile long mRef;
    int AddRef();       // 0x00432A50
    int Release();      // 0x00432A70
};

// @ 0x00432A50
int Object::AddRef()
{
    return _InterlockedIncrement(&mRef);
}

// @ 0x00432A70
int Object::Release()
{
    int n = _InterlockedDecrement(&mRef);
    if (n == 0) {
        _InterlockedExchange(&mRef, 1);
        delete this;
    }
    return n;
}

// ---------------------------------------------------------------- property list resource
struct EditorResource {
    virtual void v0();
    virtual void v1();
    virtual ~EditorResource() {}
    void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
struct BakeSprites : EditorResource {
    virtual void v0();
    virtual void v1();
};
struct Triple { int a, b, c; Triple() { a = 0; b = 0; c = 0; } };

struct AtomicInt {
    volatile long v;
    AtomicInt() { _InterlockedExchange(&v, 0); }
};

struct PropertyList : BakeSprites {
    AtomicInt     mRefCount;
    Triple        mList;
    PropertyList();            // 0x004329E0
    int GetRefCount();         // 0x00432940
    int AddRef();              // 0x00432BE0
    virtual void v0();
    virtual void v1();
    virtual ~PropertyList() {}   // 0x00432B10 (scalar deleting form)
};

struct Listener { virtual void Notify(void* src); };

struct RefIface {              // secondary base at +0x18
    virtual void r0();
    virtual void r1();
};

struct ResourceList : PropertyList {
    Listener* mListener;
    ResourceList() { mListener = 0; }
    int Release();             // 0x00432B50
    virtual void v0();
    virtual void v1();
};

// @ 0x004329E0
PropertyList::PropertyList()
{
}

// @ 0x00432940
int PropertyList::GetRefCount()
{
    return _InterlockedExchangeAdd(&mRefCount.v, 0) >> 1;
}

// @ 0x00432BE0
int PropertyList::AddRef()
{
    return (_InterlockedExchangeAdd(&mRefCount.v, 2) + 2) >> 1;
}

// @ 0x00432B50
int ResourceList::Release()
{
    int n = _InterlockedExchangeAdd(&mRefCount.v, -2) - 2;
    if (n == 0) {
        _InterlockedExchange(&mRefCount.v, 2);
        delete this;
    } else if (n == 3 && mListener) {
        mListener->Notify(this);
    }
    return n;
}

struct SpriteGrid : ResourceList, RefIface {
    int  mWidth;
    int  mHeight;
    int  mState;
    int* mData;
    SpriteGrid(int w, int h);  // 0x00432960
    int ReleaseThunk();        // 0x00432C00
};

// @ 0x00432960
SpriteGrid::SpriteGrid(int w, int h)
{
    int pad1, pad2;
    mWidth = w;
    mHeight = h;
    mState = -1;
    mData = 0;
}

// @ 0x00432C00
int SpriteGrid::ReleaseThunk()
{
    int pad1, pad2, pad3;
    return ResourceList::Release();
}

struct SpriteBuffer : SpriteGrid {
    SpriteBuffer(int w, int h);    // 0x004328D0
};

inline int* DoAllocate(uint32_t n)
{
    return (int*)EASTL_allocator_allocate(n * 4, "Graphics", 0, 0, 0, 0);
}

// @ 0x004328D0
SpriteBuffer::SpriteBuffer(int w, int h) : SpriteGrid(w, h)
{
    int pad1, pad2, pad3;
    int* p = DoAllocate(w * h);
    mData = p;
    mState = 2;
}

// ---------------------------------------------------------------- adjustor thunks
extern "C" void __cdecl Target_004302F0();
extern "C" void __cdecl Target_00432BE0();
void __fastcall ReleaseThunkImpl();

// @ 0x00432EE0
__declspec(naked) void __fastcall AdjustThunk_00432EE0()
{
    __asm { sub ecx, 4 }
    __asm { jmp Target_004302F0 }
}

// @ 0x00432EF0
__declspec(naked) void __fastcall AdjustThunk_00432EF0()
{
    __asm { sub ecx, 0x18 }
    __asm { jmp ReleaseThunkImpl }
}

// @ 0x00432F00
__declspec(naked) void __fastcall AdjustThunk_00432F00()
{
    __asm { sub ecx, 0x18 }
    __asm { jmp Target_00432BE0 }
}

// ---------------------------------------------------------------- scalar deleting destructor
struct Base7043D0 { void Dtor(); };
struct Holder {
    Base7043D0 base;
    void* Destroy(unsigned flags);     // 0x00432C20
};

// @ 0x00432C20
void* Holder::Destroy(unsigned flags)
{
    base.Dtor();
    if (flags & 1) EASTL_allocator_deallocate(this);
    return this;
}

// ---------------------------------------------------------------- ability
struct Sub40CF60 { Sub40CF60(); };
struct AbilityBase {
    virtual void a0();
    short       mId;
    short       mCost;
    Sub40CF60*  mSub;
    AbilityBase() : mId(0x210), mCost(0x14), mSub(0) {}
};
struct CreatureAbility : AbilityBase, Sub40CF60 {
    virtual void a0();
    CreatureAbility();                 // 0x00432CF0
};

// @ 0x00432CF0
CreatureAbility::CreatureAbility()
{
    mSub = static_cast<Sub40CF60*>(this);
}

// ---------------------------------------------------------------- pointer vectors
struct DefaultRefCounted { void Release(); };      // 0x00453540
namespace Resource { struct ThreadedObject { void Release(); }; }  // 0x00404F90

template<class T> struct VecBase {
    T* mBegin; T* mEnd; T* mCap; int mAlloc[2];
    ~VecBase();
};

struct DestructTag {};
template<class T> inline void DestructImpl(T* first, T* last, DestructTag)
{
    for (; first < last; ++first)
        first->~T();
}
template<class T> inline void destruct(T* first, T* last)
{
    DestructImpl(first, last, DestructTag());
}

struct RefElem { DefaultRefCounted* p; ~RefElem() { if (p) p->Release(); } };
struct TObjElem { Resource::ThreadedObject* p; int tag; ~TObjElem() { if (p) p->Release(); } };

template<class T> inline void* DelDtor(T* p, unsigned flags)
{
    p->~T();
    if (flags & 1) EASTL_allocator_deallocate(p);
    return p;
}

struct TObjVec : VecBase<TObjElem> { ~TObjVec(); };                // 0x00432E80
struct TObjVecVec : VecBase<TObjVec> { ~TObjVecVec(); };           // 0x00432DE0
struct RefVec : VecBase<RefElem> { ~RefVec(); };                   // 0x00432D60

// @ 0x00432D60
RefVec::~RefVec()
{
    int pad1[3];
    (void)&pad1;
    RefElem* p;
    RefElem* last;
    int pad2[3];
    last = mEnd;
    p = mBegin;
    for (; p < last; ++p)
        p->~RefElem();
}

// @ 0x00432DE0
TObjVecVec::~TObjVecVec()
{
    int pad1[3];
    (void)&pad1;
    TObjVec* p;
    TObjVec* last;
    int pad2[3];
    last = mEnd;
    p = mBegin;
    for (; p < last; ++p)
        p->~TObjVec();
}

// @ 0x00432E80
TObjVec::~TObjVec()
{
    int pad1[3];
    (void)&pad1;
    TObjElem* p;
    TObjElem* last;
    int pad2[3];
    last = mEnd;
    p = mBegin;
    for (; p < last; ++p)
        p->~TObjElem();
}

// ---------------------------------------------------------------- member-function call thunk
struct HBaseA { virtual void a(); };
struct HBaseB { virtual void b(); };
struct Handler : HBaseA, HBaseB { void __thiscall Run(int arg); };   // 0x0042FF30

// @ 0x00432E40
void __cdecl CallHandler(int arg, Handler* obj)
{
    void (__thiscall Handler::*pm)(int) = &Handler::Run;
    (obj->*pm)(arg);
}

struct HandlerFunctor {
    void (__cdecl* mFn)(int, Handler*);
    int  mOwner;
    void Init(int owner);              // 0x00432DC0
};

// @ 0x00432DC0
void HandlerFunctor::Init(int owner)
{
    mFn = CallHandler;
    mOwner = owner;
}

// ---------------------------------------------------------------- query
struct Queryable {
    void* Cast(unsigned id);           // 0x00432AD0
};

// @ 0x00432AD0
void* Queryable::Cast(unsigned id)
{
    switch (id) {
    case 0x2269ed1:
        return this;
    case 0xee3f516e:
        return this;
    }
    return 0;
}
