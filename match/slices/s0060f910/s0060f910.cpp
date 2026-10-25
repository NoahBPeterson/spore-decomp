// SP::cPollinator transaction poster helpers (CreateMyFeed / UpdateMyFeed / DeleteMyFeed /
// SubscribeToFeed / UnsubscribeToFeed) built on an EASTL deque<AutoRefCount<cITransaction>>,
// plus outline ports of Init / ProcessTransactionQueue / the feed-edit helpers.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc).
#include "types.h"
#include <string.h>

typedef unsigned int uint32_t;
typedef unsigned int size_t;

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd)
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);
void __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

namespace eastl {
class allocator { public:
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
}  // namespace eastl

// Transaction: primary vtable slot 1 = AddRef, slot 2 = Release.
struct cITransaction {
    virtual void v0();
    virtual void AddRef();   // +0x4
    virtual void Release();  // +0x8
};

template <class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p = 0) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
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

template <class T, int kSubarraySize = 64>
struct DequeIterator {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    DequeIterator() {}
    DequeIterator(const DequeIterator& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) { mpCurrentArrayPtr = p; mpBegin = *p; mpEnd = mpBegin + kSubarraySize; }
    DequeIterator& operator--() {
        if (mpCurrent == mpBegin) {
            --mpCurrentArrayPtr;
            SetSubarray(mpCurrentArrayPtr);
            mpCurrent = mpEnd;
        }
        --mpCurrent;
        return *this;
    }
    DequeIterator& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
};

void PushFrontSlowHelper(void* value);  // 0x0060db40

template <class T, int kSubarraySize = 64>
struct deque {
    typedef DequeIterator<T, kSubarraySize> iterator;
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    iterator mItBegin;
    iterator mItEnd;
    eastl::allocator mAllocator;
    void push_front(const T& value) {
        if (mItBegin.mpCurrent == mItBegin.mpBegin) {
            PushFrontSlowHelper((void*)&value);
        } else {
            --mItBegin.mpCurrent;
            *mItBegin.mpCurrent = value;
        }
    }
};

typedef deque<AutoRefCount<cITransaction>, 64> TransactionDeque;

// Transaction constructors run in place on the freshly allocated block (ecx = block).
struct TxnMem {
    cITransaction* GetAssetFeed(void* a, void* b);  // 0x0061a810
    cITransaction* EditFeed(int a);                 // 0x0061a970
    cITransaction* EatFeed(void* a);                // 0x0061c5e0
    cITransaction* DeleteMyFeed(void* a);           // 0x00619150
    cITransaction* SubscribeFeed(int a, void* b, int c);  // 0x00618da0
    cITransaction* UnsubscribeFeed(void* a);        // 0x006191d0
};

void* __cdecl Alloc0xf0(size_t);
void* __cdecl Alloc0x70(size_t);
void* __cdecl Alloc0x18(size_t);

// cString::Format-style variadic helper (self, format, ...): writes a cString in place.
void __cdecl StringFormat(void* self, const char* fmt, ...);   // 0x00472fe0

// Array container passed to UpdateMyFeed: data pointer at +4, element count at +8.
struct FeedContainer {
    int     mField0;      // +0x0
    void**  mpData;       // +0x4
    int     mnSize;       // +0x8
};

// Feed assembler sub-object (t+0x30 / t+0x50): four-argument thiscall helper.
struct FeedAssembler {
    void FUN_0060f0d0(void* a, void* b, void* c, void* d);   // 0x0060f0d0
};

// Replicates the shipped first-non-null scan then forwards to 0x60f0d0.
static void FeedAppendEntry(void* obj, void* container) {
    FeedContainer* fc = (FeedContainer*)container;
    void** data = fc->mpData;
    void** endPtr = data + fc->mnSize;
    void* endVal = *endPtr;
    void** cur = data;
    void* val = *cur;
    if (val == 0) {
        do { ++cur; } while (*cur == 0);
        val = *cur;
    }
    ((FeedAssembler*)obj)->FUN_0060f0d0(val, cur, endVal, endPtr);
}

namespace SP {
class cPollinator { public:
    virtual void v0();
    virtual void v1();
    void* mpHTTPClient;                  // +0x4
    TransactionDeque mTransactionQueue;  // +0x8 (deque: ptr array, size, begin, end, allocator)
    char pad34[0x48 - 0x34];
    int mnActiveLowWater;                // +0x48
    char pad4c[0x50 - 0x4c];
    int mnActiveHighWater;               // +0x50
    void* mpNextAssetID;                 // +0x54
    int mNextAssetSub;                   // +0x58
    char mEnabled;                       // +0xf1

    void ProcessTransactionQueue();                       // 0x00610140
    void CreateMyFeed(void* a, void* b, int c);           // 0x006104f0
    void UpdateMyFeed(void* a, void* b, void* c, void* d); // 0x006105d0
    void DeleteMyFeed(void* a);                           // 0x006106f0
    void SubscribeToFeed(void* a);                        // 0x00610780
    void UnsubscribeToFeed(void* a);                      // 0x00610810
    void PostGetAssetFeed(void* a, void* b);              // 0x006103d0
    void PostEatFeed(void* a);                            // 0x00610460
};

// @ 0x6103d0  (SP::cPollinator::GetAssetFeed candidate)
void cPollinator::PostGetAssetFeed(void* a, void* b) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0xf0(0xf0);
    if (mem) t = ((TxnMem*)mem)->GetAssetFeed(a, b);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x610460  (SP::cPollinator::EatFeed candidate)
void cPollinator::PostEatFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0xf0(0xf0);
    if (mem) t = ((TxnMem*)mem)->EatFeed(a);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x6104f0  (SP::cPollinator::CreateMyFeed)
void cPollinator::CreateMyFeed(void* a, void* b, int c) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x70(0x70);
    if (mem) t = ((TxnMem*)mem)->EditFeed(0);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x6105d0  (SP::cPollinator::UpdateMyFeed)
void cPollinator::UpdateMyFeed(void* a, void* b, void* c, void* d) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x70(0x70);
    if (mem) t = ((TxnMem*)mem)->EditFeed(1);
    StringFormat((char*)t + 0x10, (const char*)0x13f5b98, a);
    StringFormat((char*)t + 0x20, (const char*)0x13ef064, b);
    FeedAppendEntry((char*)t + 0x30, c);
    FeedAppendEntry((char*)t + 0x50, d);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x6106f0  (SP::cPollinator::DeleteMyFeed)
void cPollinator::DeleteMyFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x18(0x18);
    if (mem) t = ((TxnMem*)mem)->DeleteMyFeed(a);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        if (mTransactionQueue.mItBegin.mpCurrent == mTransactionQueue.mItBegin.mpBegin) {
            PushFrontSlowHelper(&ref);
        } else {
            mTransactionQueue.mItBegin.mpCurrent = mTransactionQueue.mItBegin.mpCurrent - 1;
            *mTransactionQueue.mItBegin.mpCurrent = ref;
        }
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x610780  (SP::cPollinator::SubscribeToFeed)
void cPollinator::SubscribeToFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0xf0(0xf0);
    if (mem) t = ((TxnMem*)mem)->SubscribeFeed(1, a, 0);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}

// @ 0x610810  (SP::cPollinator::UnsubscribeToFeed)
void cPollinator::UnsubscribeToFeed(void* a) {
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x18(0x18);
    if (mem) t = ((TxnMem*)mem)->UnsubscribeFeed(a);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}
}  // namespace SP

// ---------------------------------------------------------------------------
// Remaining functions of the slice: cPollinator::Init, the feed-post helper and
// cPollinator::ProcessTransactionQueue.  All three are large outline ports built
// on the helper infrastructure above; see nonmatching.txt.
// ---------------------------------------------------------------------------

// Extra helper entry points used by Init / the queue pump.  Every name is either
// a real shipped symbol or a hex-encoded stub (FUN_<va>) so the equivalence
// resolver can bind the calls; addresses are masked at match time.
extern "C" void* FUN_0067de20();                       // CheatManager / MessageServer
extern "C" void  FUN_0083c800(void* self);             // cCommandBase ctor
extern "C" void* FUN_00943f60();                       // EA::Internet::HTTPClient ctor
extern "C" void  FUN_00942150(void* self, void* fn, int a);  // SetNotificationTarget
extern "C" void* FUN_0067de40();                       // ConfigManager
extern "C" void* FUN_0067de00();                       // PropertyManager
extern "C" void* FUN_00943d70(void* self);             // CookieHandler register
extern "C" void* FUN_0060b760();                       // job-queue ctor
extern "C" void  FUN_0060b8b0(void* self);             // job-queue init
extern "C" void* FUN_0054ddf0();                       // asset directory ctor
extern "C" void  FUN_0054df60();                       // asset directory init
extern "C" void* FUN_00613790();                       // pollen manager ctor
extern "C" void  FUN_006145d0(void* self);             // pollen manager attach
extern "C" void  FUN_00941f80(unsigned n);             // set async poll count
extern "C" void  FUN_0060d9f0(void* out, void* a);     // QueueEntry ctor
extern "C" void  FUN_0060e5b0(void* self);             // JobHolder dtor
extern "C" void* FUN_00946680(void* self, void* stub, int a, int b, unsigned id); // AddNewJob
extern "C" void  FUN_0060f260(void* tree, void* value, unsigned flag);  // Rbtree::DoInsertValue
extern "C" void  FUN_00e2fd40(void);                   // erase iterator
extern "C" void  FUN_00944d50(void* self, int field, void* value);       // HTTPHeaders::AddField
extern "C" void  FUN_005648c0(void* self);             // HTTP task reset
extern "C" void  FUN_0060f010(void);                   // local transaction notify
extern "C" void* FUN_006895b0();                       // HTTP message table
extern "C" int   FUN_0060d800(void);                   // notification callback
extern "C" void  FUN_00607530(void* self);             // auth manager register
extern "C" void  FUN_00943980(void* self, const char* ua);  // SetUserAgent
extern "C" void* FUN_00944020(void* self, int a, int b);    // CookieHandler ctor
extern "C" int   FUN_00943fb0(void* self);                  // cAuthManager ctor
extern "C" void  operator_delete__(void* p);                // 0x00f47380
extern "C" void* operator_new(unsigned size, const char* name, int a, int b,
                              const char* file, int line);  // 0x00f473a0
extern "C" void* MessageServer();                           // EA::Messaging server

// Application property list (&_sAppProperties) and the static tables.
extern "C" char  g_sAppProperties[];                   // 0x0151fa24-area
extern "C" char  g_unknownName8[];                     // 0x0165fea3 network-tag marker
extern "C" char  g_pollinatorUrlTable[];               // 0x0151fafc per-job URL table

// SSO eastl::basic_string<char> used only as a temporary here.
struct TempCString {
    char* mpBegin;  // +0x0
    char* mpEnd;    // +0x4
    char* mpCap;    // +0x8
};

// cPollinator::Init (0x0060f910): build the HTTP client, cookie/auth managers,
// subscribe the message handlers and read the pollinator configuration.
// @ 0x60f910
void cPollinatorInit(void* selfp) {
    SP::cPollinator* self = (SP::cPollinator*)selfp;
    if (FUN_0067de20() != 0) {
        char* mem = (char*)operator_new(0x10, "Pollinator", 0, 0, 0, 0);
        if (mem) {
            FUN_0083c800(mem);
            *(void**)(mem) = (void*)0x13fbb28;      // vtable
        }
        mem = (char*)operator_new(0x18, "Pollinator", 0, 0, 0, 0);
        if (mem) {
            FUN_0083c800(mem);
            *(void**)(mem + 0x10) = (void*)0x13eb394;
            *(void**)(mem) = (void*)0x13fb82c;
            *(void**)(mem + 0x10) = (void*)0x13fb824;
            *(int*)(mem + 0x14) = 0;
        }
    }

    char* clientMem = (char*)operator_new(0x168, "Pollinator", 0, 0, 0, 0);
    void* newClient = clientMem ? FUN_00943f60() : 0;
    void* oldClient = *(void**)((char*)self + 4);
    if (newClient != oldClient) {
        if (newClient) (*(void(__thiscall**)(void*))*(void**)newClient)(newClient);
        *(void**)((char*)self + 4) = newClient;
        if (oldClient) (*(void(__thiscall**)(void*))(*(void**)oldClient))(oldClient);
    }
    FUN_00942150(*(void**)((char*)self + 4), (void*)0x0060d800, 0);

    // Build "Unknown" (SSO) strings and publish the user-agent template.
    TempCString lower, upper;
    lower.mpBegin = (char*)operator_new(8, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    lower.mpCap = lower.mpBegin + 8;
    memcpy(lower.mpBegin, "Unknown", 8);
    lower.mpEnd = lower.mpBegin + 7;
    upper.mpBegin = (char*)operator_new(8, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    upper.mpCap = upper.mpBegin + 8;
    memcpy(upper.mpBegin, "Unknown", 8);
    upper.mpEnd = upper.mpBegin + 7;

    const char* tmpl = (*(int*)(g_sAppProperties + 0x118) == 0)
                           ? "SPORE/%s (Pollinator; %s)"
                           : "SPORE-CSA-2-COMPLETE/%s (Pollinator; %s)";
    TempCString ua;
    StringFormat(&ua, tmpl, lower.mpBegin, upper.mpBegin);
    FUN_00943980(*(void**)((char*)self + 4), (const char*)ua.mpBegin);
    if (ua.mpCap - ua.mpBegin > 1 && ua.mpBegin) operator_delete__(ua.mpBegin);
    {
        void* client = *(void**)((char*)self + 4);
        (*(void(__thiscall**)(void*))((char*)*(void**)(char*)client + 0x10))(client);
    }

    // Cookie handler (0x48 bytes, ctor takes (10, 0x800)).
    char* cookieMem = (char*)operator_new(0x48, "Pollinator", 0, 0, 0, 0);
    void* cookie = cookieMem ? FUN_00944020(cookieMem, 10, 0x800) : 0;
    if (cookie) {
        *(void**)((char*)cookie) = (char*)(*(void**)cookie) + 1;
    }
    FUN_00943d70(cookie);

    // Job-queue object (0x20 bytes).
    char* jqMem = (char*)operator_new(0x20, "Pollinator", 0, 0, 0, 0);
    void* jq = 0;
    if (jqMem) {
        jq = FUN_0060b760();
        if (jq) (*(void(__thiscall**)(void*))(*(void**)(char*)jq))(jq);
    }
    (*(void(__thiscall**)(void*))((char*)*(void**)(char*)jq + 0x10))(jq);
    FUN_0060b8b0(jq);

    // Auth manager (0x70 bytes).
    char* amMem = (char*)operator_new(0x70, "Pollinator", 0, 0, 0, 0);
    void* am = 0;
    if (amMem) {
        int r = FUN_00943fb0(amMem);
        if (r) am = (char*)r + 0x1c;
    }
    if (am) (*(void(__thiscall**)(void*))(*(void**)(char*)am))(am);
    (*(void(__thiscall**)(void*))((char*)*(void**)(char*)am + 0x10))(am);
    FUN_00607530(am);

    // Subscribe the pollinator's message handlers.
    void* server = FUN_0067de20();
    if (server) {
        void* const msgIds[] = {
            (void*)0x0164d214, (void*)0x2ba2010, (void*)0x73e46f6, (void*)0x611a3f72,
            (void*)0x238de9c, (void*)0x457076f, (void*)0x46d05ee, (void*)0x55be439,
            (void*)0x55e8bc8, (void*)0x55e8be4, (void*)0x56cd8c4, (void*)0x49a3777,
            (void*)0x5d313c7, (void*)0x5fff3ff,
        };
        for (unsigned i = 0; i < sizeof(msgIds) / sizeof(msgIds[0]); ++i) {
            (*(void(__thiscall**)(void*, void*, void*))((char*)*(void**)(char*)server + 0x24))(server, self, msgIds[i]);
        }
        void* table = FUN_006895b0();
        (*(void(__thiscall**)(void*, void*, int))((char*)*(void**)(char*)table + 0x20))(table, g_pollinatorUrlTable, 3);
        for (void** p = (void**)g_pollinatorUrlTable; p < (void**)0x151fb20; p += 3) {
            void* s = FUN_0067de20();
            (*(void(__thiscall**)(void*, void*, void*))((char*)*(void**)(char*)s + 0x24))(s, self, *p);
        }
    }

    // Asset directory (0x120 bytes).
    char* adMem = (char*)operator_new(0x120, "Pollinator", 0, 0, 0, 0);
    void* ad = adMem ? FUN_0054ddf0() : 0;
    *(void**)((char*)self + 0x10c) = ad;
    if (ad) FUN_0054df60();

    // Pollen manager (0xa0 bytes).
    char* pmMem = (char*)operator_new(0xa0, "Pollinator", 0, 0, 0, 0);
    void* pm = pmMem ? FUN_00613790() : 0;
    *(void**)((char*)self + 0x5c) = pm;
    if (pm) FUN_006145d0(self);

    // Read the pollinator configuration.
    int* prop = (int*)FUN_0067de00();
    (*(void(__thiscall**)(int*, int, void*, void**))((char*)*(void**)(char*)prop + 0x2c))(prop, 0x21d4b8c, (void*)0x21403e6, &am);
    if (am != 0) {
        (*(void(__thiscall**)(void*, int, void**))((char*)*(void**)(char*)am + 0x24))(am, 0x4363000, &am);
    }
    unsigned lowWater = 0x1e;
    if (am != 0 &&
        (*(char(__thiscall**)(void*, int, void**))((char*)*(void**)(char*)am + 0x24))(am, 0x5c29d33, &am) != 0 &&
        *(short*)((char*)am + 0x12) == 10) {
            void* value = am;
            if ((*(unsigned*)((char*)am + 0x10) & 0x30) != 0) value = *(void**)(char*)am;
            lowWater = *(unsigned*)value;
    }
    FUN_00941f80(lowWater);

    if (am != 0) {
        if ((*(char(__thiscall**)(void*, int, void**))((char*)*(void**)(char*)am + 0x24))(am, 0x5433c88, &am) != 0 &&
            *(short*)((char*)am + 0x12) == 10) {
            void* value = am;
            if ((*(unsigned*)((char*)am + 0x10) & 0x30) != 0) value = *(void**)(char*)am;
            self->mnActiveLowWater = *(int*)value;
        }
        if (am != 0) {
            if ((*(char(__thiscall**)(void*, int, void**))((char*)*(void**)(char*)am + 0x24))(am, 0x5433ca3, &am) != 0 &&
                *(short*)((char*)am + 0x12) == 10) {
                void* value = am;
                if ((*(unsigned*)((char*)am + 0x10) & 0x30) != 0) value = *(void**)(char*)am;
                self->mnActiveHighWater = *(int*)value;
            }
            if (am != 0 &&
                (*(char(__thiscall**)(void*, int, void**))((char*)*(void**)(char*)am + 0x24))(am, 0x4598a70, &am) != 0) {
                // (config-driven active-transaction preload; outline only)
                (void)jq;
                (void)ad;
                (void)pm;
                (void)cookieMem;
                (void)jqMem;
                (void)amMem;
                (void)tmpl;
            }
        }
    }

    // Final user-agent header append: "<locale>, en;q=0.5".
    void* cfg = FUN_0067de40();
    (*(void(__cdecl**)(void*, const char*, ...))((char*)*(void**)(char*)cfg + 0x14))(cfg, "%ls, en;q=0.5",
                                                                                    FUN_006895b0());
    if (am != 0) (*(void(__thiscall**)(void*))((char*)*(void**)(char*)am + 4))(am);
    (*(void(__thiscall**)(void*))((char*)*(void**)(char*)jq + 4))(jq);
    (*(void(__thiscall**)(void*))((char*)*(void**)(char*)lower.mpBegin + 4))(lower.mpBegin);
    if ((int)((char*)ua.mpCap - (char*)ua.mpBegin) > 1 && ua.mpBegin) operator_delete__(ua.mpBegin);
    if ((int)((char*)upper.mpCap - (char*)upper.mpBegin) > 1 && upper.mpBegin) operator_delete__(upper.mpBegin);
}

// Helper at 0x00610070: if the client is connected, post the entry's HTTP job
// and record it in the active-transaction tree on the pollinator.
// @ 0x610070
void FeedHelper00610070(void* selfp, void* entry) {
    SP::cPollinator* self = (SP::cPollinator*)selfp;
    void* conn = *(void**)((char*)entry + 4);
    void* a = *(void**)((char*)conn + 0xd8c);
    if (a != 0) {
        if ((*(char(__thiscall**)(void*, int, int))((char*)*(void**)(char*)a + 0x28))(a, 0, 0) == 0) return;
    }
    void* b = *(void**)((char*)conn + 0xd90);
    if (b != 0) {
        if ((*(char(__thiscall**)(void*, int, int))((char*)*(void**)(char*)b + 0x28))(b, 0, 0) == 0) return;
        if ((*(char(__thiscall**)(void*, int))((char*)*(void**)(char*)b + 0x20))(b, 0) == 0) return;
    }

    void* req = *(void**)(char*)entry;
    unsigned id = (*(unsigned(__thiscall**)(void*))((char*)*(void**)(char*)req + 0x1c))(req);
    unsigned job = (unsigned)FUN_00946680(*(void**)((char*)self + 4), conn, 0, 0, id);
    if (job == 0) return;

    ++*(unsigned short*)((char*)entry + 8);
    char entryBlock[0x18];
    FUN_0060d9f0(entryBlock, entry);
    char flag = 0;
    FUN_0060f260((char*)self + 0x34, entryBlock, (unsigned)(unsigned char)flag);
    FUN_0060e5b0(entryBlock);
}

// cPollinator::ProcessTransactionQueue (0x00610140): drain the transaction
// deque, posting HTTP jobs for the entries that are ready and retiring the
// ones that do not need a request, until a low/high-water mark is reached.
// @ 0x610140
void SP::cPollinator::ProcessTransactionQueue() {
    // Deque empty and no active transactions -> disable pollination.
    if (mTransactionQueue.mItBegin.mpCurrent == mTransactionQueue.mItEnd.mpCurrent) {
        if (*(int*)((char*)this + 0x48) == 0) {
            if (mEnabled != 0) {
                void* s = FUN_0067de20();
                (*(void(__thiscall**)(void*, int, int, int))((char*)*(void**)(char*)s + 0x14))(s, 0x269c832, 0, 0);
            }
            mEnabled = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x48) >= *(int*)((char*)this + 0x50)) return;

    if (mTransactionQueue.mItBegin.mpCurrent != mTransactionQueue.mItEnd.mpCurrent) {
        do {
            if (*(int*)((char*)this + 0x50) <= *(int*)((char*)this + 0x48)) break;

            cITransaction* txn = mTransactionQueue.mItBegin.mpCurrent->mpObject;
            void* result = 0;
            if ((*(char(__thiscall**)(void*, void**))((char*)*(void**)txn + 0x14))(txn, &result) == 0) {
                // Transaction needs no network hop: fire the local notifications.
                void* tag = (*(void*(__thiscall**)(void*))((char*)*(void**)txn + 0x10))(txn);
                if (tag == (void*)g_unknownName8) {
                    mpNextAssetID = *(void**)((char*)txn + 0x10);
                    mNextAssetSub = *(int*)((char*)txn + 0x14);
                    FUN_005648c0((char*)txn + 4);
                    FUN_0060f010();
                    void* s = FUN_0067de20();
                    (*(void(__thiscall**)(void*, int, void*, int))((char*)*(void**)(char*)s + 0x14))(s, 0x68cd252, 0, 0);
                }
                FUN_00e2fd40();
            } else {
                FUN_00944d50((char*)result + 0x2f4, 0xb, (char*)this + 0x110);
                unsigned id = (*(unsigned(__thiscall**)(void*))((char*)*(void**)txn + 0x1c))(txn);
                unsigned job = (unsigned)FUN_00946680(*(void**)((char*)this + 4), result, 0, 0, id);
                if (job != 0) {
                    (*(void(__thiscall**)(void*))((char*)*(void**)txn + 4))(txn);
                    if (result) ++*(int*)((char*)result + 4);
                    unsigned char flag = 0;
                    FUN_0060f260((char*)this + 0x34, &id, flag);
                    (*(void(__thiscall**)(void*))((char*)*(void**)txn + 8))(txn);
                    if (result && --*(int*)((char*)result + 4) == 1) {
                        *(int*)((char*)result + 4) = 1;
                        (*(void(__thiscall**)(void*, int))((char*)*(void**)(char*)result))(result, 1);
                    }
                }
            }
            if (result && --*(int*)((char*)result + 4) == 1) {
                *(int*)((char*)result + 4) = 1;
                (*(void(__thiscall**)(void*, int))((char*)*(void**)(char*)result))(result, 1);
            }
        } while (mTransactionQueue.mItBegin.mpCurrent != mTransactionQueue.mItEnd.mpCurrent);
    }
    mEnabled = 1;
}

