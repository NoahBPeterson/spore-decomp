// SP::cPollinator transaction handling: the rbtree walk (CancelTransactions), the deque
// ctors/erase helpers, the feed-description vector erase and the transaction poster helpers.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;
typedef unsigned int size_t;
void* memcpy(void* d, const void* s, size_t n);
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
namespace eastl { struct allocator {
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
}; }

// cITransaction: vtable slot 1 = AddRef(+4), slot 2 = Release(+8), slot 4 = GetId(+0x10).
struct cITransaction {
    virtual void v0(); virtual void AddRef(); virtual void Release(); virtual void v3();
    virtual int GetId();
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& x) {
        T* const pNew = x.mpObject;
        if (pNew != mpObject) {
            T* const pOld = mpObject;
            if (pNew) pNew->AddRef();
            mpObject = pNew;
            if (pOld) pOld->Release();
        }
        return *this;
    }
};

template <class T, int N = 64>
struct DequeIterator {
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator() {}
    DequeIterator(const DequeIterator& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) { mpCurrentArrayPtr = p; mpBegin = *p; mpEnd = mpBegin + N; }
    DequeIterator& operator--() {
        if (mpCurrent == mpBegin) { --mpCurrentArrayPtr; SetSubarray(mpCurrentArrayPtr); mpCurrent = mpEnd; }
        --mpCurrent; return *this;
    }
    DequeIterator& operator++() {
        if (++mpCurrent == mpEnd) { SetSubarray(mpCurrentArrayPtr + 1); mpCurrent = mpBegin; }
        return *this;
    }
};

void DequeCtor31(void* allocator, int n);  // 0x0060d4f0 (allocator-adapter ctor)
void PushFrontSlow(void* value);           // 0x0060db40
void PushBackSlow(void* value);            // 0x0060dbd0
template <class T, int N = 64>
struct deque {
    typedef DequeIterator<T, N> iterator;
    T** mpPtrArray; uint32_t mnPtrArraySize; iterator mItBegin; iterator mItEnd; eastl::allocator mAllocator;
    void Init() {
        mpPtrArray = 0; mnPtrArraySize = 0;
        mItBegin.mpCurrent = 0; mItBegin.mpBegin = 0; mItBegin.mpEnd = 0; mItBegin.mpCurrentArrayPtr = 0;
        mItEnd.mpCurrent = 0; mItEnd.mpBegin = 0; mItEnd.mpEnd = 0; mItEnd.mpCurrentArrayPtr = 0;
        DequeCtor31(&mAllocator, 0);
    }
    void push_front(const T& value) {
        if (mItBegin.mpCurrent == mItBegin.mpBegin) {
            PushFrontSlow((void*)&value);
        } else {
            --mItBegin.mpCurrent;
            new ((void*)mItBegin.mpCurrent) T(value);
        }
    }
    void push_back(const T& value) {
        T* const p = mItEnd.mpCurrent;
        T* const newCur = p + 1;
        if (newCur != mItEnd.mpEnd) {
            mItEnd.mpCurrent = newCur;
            if (p) new ((void*)p) T(value);
        } else {
            PushBackSlow((void*)&value);
        }
    }
    void CancelId(int id);   // 0x00610df0
    void PopFront();         // 0x00610e90
    void PushSlow(void* value, bool flag);  // 0x0060eaf0
};
typedef deque<AutoRefCount<cITransaction>, 64> TransactionDeque;

struct RbNodeBase { RbNodeBase* mpRight; RbNodeBase* mpLeft; RbNodeBase* mpParent; char mColor; };
RbNodeBase* RBTreeIncrementNode(RbNodeBase* node);  // 0x00921580
struct IFeedRemover { void Remove(void* p); };       // 0x00943910
// ---------------------------------------------------------------------------
// FeedDescription records: an eastl::vector<FeedDescription> whose element is 0x70 bytes;
// the erase helper (0x0060ee50) relocates the tail and the dtor (0x00547840) destroys the last.
struct FeedDescription { char mData[0x70]; ~FeedDescription(); };  // dtor 0x00547840
void FeedVecCopyRange(FeedDescription* first, FeedDescription* last, FeedDescription* dest); // 0x0060ee50
struct FeedVec {
    FeedDescription* mpBegin;   // +0
    FeedDescription* mpEnd;     // +4
    FeedDescription* mpCap;     // +8
    FeedDescription* erase(FeedDescription* p);
};

// @ 0x611550
FeedDescription* FeedVec::erase(FeedDescription* p) {
    if (p + 1 < mpEnd)
        FeedVecCopyRange(p + 1, mpEnd, p);
    --mpEnd;
    mpEnd->~FeedDescription();
    return p;
}

void DequePopFrontHelper(void* self);      // 0x00610e90
void DequeCancelIdHelper(void* self, int id); // 0x00610df0

// ---------------------------------------------------------------------------
void* __cdecl Alloc0x18(size_t);   // 0x00615970
void* __cdecl Alloc0x10(size_t);   // 0x006159a0
void* __cdecl Alloc0x110(size_t);  // 0x00615910
// Poster constructors run in place on the freshly allocated block (this = block).
struct TxnFab {
    cITransaction* Make0x18(void* a, void* b, void* c);                        // 0x00616260
    cITransaction* Make0x10(unsigned long long id);                            // 0x006162d0
    cITransaction* Make0xa8(void* a, void* b, void* c, void* d, void* e, void* f); // 0x0061be80
};
struct IAssetDir {
    bool GetServerId(void* key, unsigned long long* out, bool flag);  // 0x0054e530
    void AddPending2(unsigned long long id);                          // 0x0054e870
};
int AssetDirCount(void* key);  // 0x00552300 (cdecl)
struct TxnMem { cITransaction* GetAssetFeedEx(void* a, void* b); };  // 0x0061a8b0
void* Object67cb30();      // 0x0067cb30
namespace SP { namespace Pollen { struct cAssetDirectory { void PurgePendingAssets(); }; } }  // 0x005502b0 (thiscall)
typedef SP::Pollen::cAssetDirectory AssetDir;

namespace SP {

class cPollinator { public:
    virtual void v0();
    virtual void v1();
    uint32_t mField4;                                 // +0x4
    TransactionDeque mTransactionQueue;               // +0x8
    uint32_t mPad34;                                  // +0x34
    RbNodeBase mActiveAnchor;                         // +0x38
    char pad48[0x58 - 0x48];
    void* mField58;                                   // +0x58
    void* mField5c;                                   // +0x5c
    char pad[0xf1 - 0x60];
    char mEnabled;                                    // +0xf1

    void* Create();                                   // 0x00611580 (ctor-equivalent; returns this)
    void Destroy();                                   // 0x006116c0 (dtor-equivalent teardown)
    bool Shutdown();                                  // 0x00610f30
    void CancelTransactions(int id);                  // 0x00611170
    void CancelAllTransactions();                     // 0x00611540
    void PostGetAssetFeedEx(void* a, void* b);        // 0x00610c20
    void PostTxn0x18(void* a, void* b, void* c);      // 0x00610cb0
    void PostTxn0xa8(void* a, void* b, void* c);      // 0x00611480
    void PostAddPending(void* key);                   // 0x00610d40
    void ProcessTransactionQueue();                   // 0x00610140
};

// @ 0x611170
void cPollinator::CancelTransactions(int id) {
    RbNodeBase* const end = &mActiveAnchor;
    for (RbNodeBase* p = mActiveAnchor.mpLeft; p != end; p = RBTreeIncrementNode(p)) {
        cITransaction* txn = *(cITransaction**)((char*)p + 0x14);
        if (txn->GetId() == id)
            ((IFeedRemover*)mField4)->Remove(*(void**)((char*)p + 0x10));
    }
    mTransactionQueue.CancelId(id);
}

// @ 0x611540
void cPollinator::CancelAllTransactions() { CancelTransactions(0x3c88992); }

// @ 0x610cb0
void cPollinator::PostTxn0x18(void* a, void* b, void* c) {
    if (mEnabled == 0) return;
    void* const mem = Alloc0x18(0x18);
    cITransaction* t = mem ? ((TxnFab*)mem)->Make0x18(a, b, c) : 0;
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
    }
    ProcessTransactionQueue();
}

// @ 0x611480
void cPollinator::PostTxn0xa8(void* a, void* b, void* c) {
    mTransactionQueue.PopFront();
    ((AssetDir*)*(void**)((char*)Object67cb30() + 0x58))->PurgePendingAssets();
    cITransaction* t = 0;
    void* const mem = EASTL_allocator_allocate(0xa8, "Pollinator", 0, 0, 0, 0);
    if (mem)
        t = ((TxnFab*)mem)->Make0xa8(a, b, c, (char*)this + 0xb4, (char*)this + 0xc8, (char*)this + 0xdc);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_back(ref);
    }
    ProcessTransactionQueue();
}

// @ 0x610c20
void cPollinator::PostGetAssetFeedEx(void* a, void* b) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x110(0x110);
    if (mem) t = ((TxnMem*)mem)->GetAssetFeedEx(a, b);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
    }
    ProcessTransactionQueue();
}

// @ 0x610d40
void cPollinator::PostAddPending(void* key) {
    if (mEnabled == 0) return;
    unsigned long long id;
    if (!((IAssetDir*)mField58)->GetServerId(key, &id, false)) return;
    void* const mem = Alloc0x10(0x10);
    cITransaction* t = mem ? ((TxnFab*)mem)->Make0x10(id) : 0;
    mTransactionQueue.PushSlow(t, true);
    ProcessTransactionQueue();
    if (AssetDirCount(key) != 1)
        ((IAssetDir*)mField58)->AddPending2(id);
}
}  // namespace SP

// ---------------------------------------------------------------------------
// Outline ports of the remaining functions of the slice.
// Restored from HEAD (dropped by the agent rewrite).
void ProcessTransactionQueueGlobal();
namespace SP {
// @ 0x610140 (declared in this TU only; body lives in slice 17)
__declspec(noinline) void cPollinator::ProcessTransactionQueue() { ProcessTransactionQueueGlobal(); }
}  // namespace SP
// @ 0x610df0
void FUN_00610df0(void* self, int id) { (void)self; (void)id; }
// @ 0x610e90
void FUN_00610e90(void* self, void* a) { (void)self; (void)a; }
// @ 0x6108a0
void FUN_006108a0(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }
// @ 0x6111c0
void FUN_006111c0(void* self, void* a) { (void)self; (void)a; }

// ---------------------------------------------------------------------------
// cPollinator ctor / dtor (0x00611580 / 0x006116c0).
namespace SP {
struct FeedVec7c {
    void Dtor(void* arg);        // 0x004e8a30 (thiscall + pushed arg)
};
struct RbAnchor34 {
    void Release(void* node);    // 0x0060f8a0 (thiscall + pushed arg)
};
struct Deque8 {
    void Ctor(int n);            // 0x0060d4f0 (thiscall)
    void Dtor();                 // 0x0060e660 (thiscall)
};
// +0x4 field object: vtbl slot +4 is its Release (0x6116c0 calls [vtbl+4]).
struct IField4Obj { virtual void v0(); virtual void Release(); };

// --- 0x00610f30 (Shutdown) helpers -----------------------------------------
void* Object67de20();          // 0x0067de20
void* Object883860();          // 0x00883860
void* Object6895b0();          // 0x006895b0
void* Object607a60();          // 0x00607a60
void Call60b8b0(void* a);      // 0x0060b8b0 (cdecl, 1 arg)
void Call607530(void* a);      // 0x00607530 (cdecl, 1 arg)
struct Field5c {
    void Fn();                   // 0x00613a10 (thiscall)
};
struct Field58 {
    void Fn();                   // 0x0054e020 (thiscall)
};
// Vtable shims: s5=+0x14, s7=+0x1c, s11=+0x2c, s1=+0x4, s0=+0x0.
struct IVtA {
    virtual void s0(int);
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(void*);
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual void s11(void*, unsigned int, int);
};
struct IVtB {   // same layout; +0x2c takes two args at this call site
    virtual void s0(int);
    virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7(void*);
    virtual void s8(); virtual void s9(); virtual void s10();
    virtual void s11(void*, int);
};

// @ 0x611580
void* cPollinator::Create() {
    char* const p = (char*)this;
    *(void**)p = (void*)0x13fc000;                  // vtable
    *(void**)(p + 4) = 0;
    for (int off = 8; off <= 0x2c; off += 4) *(void**)(p + off) = 0;
    ((Deque8*)(p + 8))->Ctor(0);                    // deque ctor (thiscall, arg 0 at +0x30 allocator)
    {
        char* const a = p + 0x38;
        *(void**)(a + 4) = 0; *(void**)(a + 8) = 0; *(void**)(a + 0xc) = 0;
        *(void**)(p + 0x3c) = a; *(void**)a = a;
    }
    *(void**)(p + 0x40) = 0; *(char*)(p + 0x44) = 0; *(void**)(p + 0x48) = 0;
    *(void**)(p + 0x58) = 0;
    { const unsigned int minus1 = (unsigned int)-1; *(void**)(p + 0x50) = (void*)minus1; *(void**)(p + 0x54) = (void*)minus1;
      *(void**)(p + 0x60) = (void*)minus1; *(void**)(p + 0x64) = (void*)minus1; }
    *(void**)(p + 0x68) = 0; *(void**)(p + 0x6c) = 0; *(void**)(p + 0x70) = 0;
    *(void**)(p + 0x84) = 0; *(void**)(p + 0x88) = 0; *(void**)(p + 0x8c) = 0;
    *(void**)(p + 0x88) = 0; *(char*)(p + 0x8c) = 0; *(void**)(p + 0x90) = 0;
    { char* const a = p + 0x80; *(void**)(p + 0x84) = a; *(void**)a = a; }
    *(void**)(p + 0x98) = 0; *(void**)(p + 0x9c) = 0; *(void**)(p + 0xa0) = 0;
    *(char*)(p + 0xb0) = 0; *(char*)(p + 0xb1) = 0;
    *(void**)(p + 0xb4) = 0; *(void**)(p + 0xb8) = 0; *(void**)(p + 0xbc) = 0;
    *(void**)(p + 0xc8) = 0; *(void**)(p + 0xcc) = 0; *(void**)(p + 0xd0) = 0;
    *(void**)(p + 0xdc) = 0; *(void**)(p + 0xe0) = 0; *(void**)(p + 0xe4) = 0;
    *(char*)(p + 0xf0) = 0; *(char*)(p + 0xf1) = 0;
    *(void**)(p + 0xf4) = 0; *(void**)(p + 0xf8) = 0; *(void**)(p + 0xfc) = 0;
    *(void**)(p + 0x10c) = (void*)0xf;
    void* const q = (void*)0x1667bac;
    *(void**)(p + 0x110) = q; *(void**)(p + 0x114) = q;
    *(void**)(p + 0x118) = (void*)0x1667bad;
    return this;
}

// @ 0x6116c0
void cPollinator::Destroy() {
    char* const p = (char*)this;
    {   // +0x110 / +0x118 block, stride 1
        char* const beg = *(char**)(p + 0x110);
        const int n = (int)(*(char**)(p + 0x118) - beg);
        if (n > 1 && beg) EASTL_allocator_deallocate(beg);
    }
    if (*(void**)(p + 0xf4)) EASTL_allocator_deallocate(*(void**)(p + 0xf4));
    // +0xdc, +0xc8, +0xb4: vector<FeedDescription> (stride 0x70).
#define TEARDOWN_FEEDVEC(OFF)                                                        \
    {                                                                                \
        FeedDescription* const end = *(FeedDescription**)(p + (OFF) + 4);            \
        FeedDescription* it = *(FeedDescription**)(p + (OFF));                       \
        while (it < end) { it->~FeedDescription(); ++it; }                           \
        char* const beg = *(char**)(p + (OFF));                                      \
        if (beg && *(int*)(beg - 4) != 0) EASTL_allocator_deallocate(beg);           \
    }
    TEARDOWN_FEEDVEC(0xdc)
    TEARDOWN_FEEDVEC(0xc8)
    TEARDOWN_FEEDVEC(0xb4)
#undef TEARDOWN_FEEDVEC
    if (*(void**)(p + 0x98)) EASTL_allocator_deallocate(*(void**)(p + 0x98));
    {   // 0x4e8a30(ecx=this+0x7c, arg=[this+0x88])
        FeedVec7c* const fv = (FeedVec7c*)(p + 0x7c);
        void* const arg = *(void**)(p + 0x88);
        fv->Dtor(arg);
    }
    if (*(void**)(p + 0x68) && *(int*)(*(char**)(p + 0x68) - 4) != 0)
        EASTL_allocator_deallocate(*(void**)(p + 0x68));
    {   // 0x60f8a0(ecx=this+0x34, arg=[this+0x40])
        RbAnchor34* const rb = (RbAnchor34*)(p + 0x34);
        void* const arg = *(void**)(p + 0x40);
        rb->Release(arg);
    }
    ((Deque8*)(p + 8))->Dtor();                             // 0x60e660(ecx=this+8)
    {
        void* const o = *(void**)(p + 4);
        if (o) ((IField4Obj*)o)->Release();          // vtbl slot +4
    }
    *(void**)p = (void*)0x13eb394;                  // reset vtable
}

// @ 0x610f30
bool cPollinator::Shutdown() {
    char* const p = (char*)this;
    {
        void* const o = Object67de20();
        if (o) {
            ((IVtA*)o)->s7(*(void**)0x151fb20);
            ((IVtA*)o)->s7(*(void**)0x151fb24);
        }
    }
    {   // two-step release of mField4
        void* t = *(void**)(p + 4);
        if (t) {
            ((IVtA*)t)->s5();
            t = *(void**)(p + 4);
            if (t) {
                *(void**)(p + 4) = 0;
                ((IVtA*)t)->s1();
            }
        }
    }
    {   // reset the container header at +0x34
        char* const q = p + 0x34;
        ((RbAnchor34*)q)->Release(*(void**)(p + 0x40));
        *(void**)(q + 4) = q + 4;
        *(void**)(q + 8) = q + 4;
        *(void**)(q + 0xc) = 0;
        *(char*)(q + 0x10) = 0;
        *(void**)(q + 0x14) = 0;
    }
    {
        void* const o = Object883860();
        if (o) {
            IVtA* const r = (IVtA*)o;
            r->s11(p, 0x164d214u, -9999);
            r->s11(p, 0x2ba2010u, -9999);
            r->s11(p, 0x73e46f6u, -9999);
            r->s11(p, 0x611a3f72u, -9999);
            r->s11(p, 0x238de9cu, -9999);
            r->s11(p, 0x457076fu, -9999);
            r->s11(p, 0x46d05eeu, -9999);
            r->s11(p, 0x55be439u, -9999);
            r->s11(p, 0x55e8bc8u, -9999);
            r->s11(p, 0x55e8be4u, -9999);
            r->s11(p, 0x56cd8c4u, -9999);
            r->s11(p, 0x49a3777u, -9999);
            r->s11(p, 0x5d313c7u, -9999);
            r->s11(p, 0x5fff3ffu, -9999);
            ((IVtB*)Object6895b0())->s11((void*)0x151fafc, 3);
            for (int q = 0x151fafc; q < 0x151fb20; q += 0xc) {
                void* const o3 = Object883860();
                ((IVtA*)o3)->s11(p, *(unsigned int*)q, -9999);
            }
        }
    }
    Call60b8b0(0);
    ((IVtA*)Object607a60())->s5();
    Call607530(0);
    {
        void* t = *(void**)(p + 0x5c);
        if (t) {
            ((Field5c*)t)->Fn();
            t = *(void**)(p + 0x5c);
            if (t) ((IVtA*)t)->s0(1);
            *(void**)(p + 0x5c) = 0;
        }
    }
    {
        void* t = *(void**)(p + 0x58);
        if (t) {
            ((Field58*)t)->Fn();
            t = *(void**)(p + 0x58);
            if (t) ((IVtA*)t)->s0(1);
            *(void**)(p + 0x58) = 0;
        }
    }
    return true;
}
}  // namespace SP
