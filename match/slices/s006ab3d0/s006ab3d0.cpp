// Slice s006ab3d0 — fixed-allocator / cache / primitive EA helpers (mixed).
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"
#include <intrin.h>

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

void  WString_Assign(const wchar_t* first, const wchar_t* last);   // 0x00423650 (basic_string<wchar_t>::assign)
void  EASTL_allocator_deallocate(void* p);                          // 0x00f47380
void* EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0

// ===========================================================================
// eastl::basic_string<wchar_t>
// ===========================================================================
struct WString {
    wchar_t* mpBegin;    // +0
    wchar_t* mpEnd;      // +4
    wchar_t* mpCapacity; // +8
    void*    mAllocator; // +0xc

    WString() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
    ~WString()
    {
        int n = (int)((char*)mpCapacity - (char*)mpBegin);
        if ((n & 0xfffffffe) > 2 && mpBegin != 0)
            EASTL_allocator_deallocate(mpBegin);
    }

    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650
    void assign(const wchar_t* p, unsigned n);                 // @ 0x006ab7e0
    void range_initialize(const wchar_t* p);                   // 0x00579a90
    int  rfind(wchar_t c, unsigned pos) const;                 // 0x0041dfc0
    void erase(unsigned pos, unsigned count);                  // 0x004228e0
    WString(const WString& src, unsigned pos, unsigned count); // 0x0065bce0
};

// @ 0x006ab7e0
void WString::assign(const wchar_t* p, unsigned n)
{
    assign(p, p + n);
}

// @ 0x006ab800
void __fastcall FUN_006ab800(WString* self, int /*edx unused*/, WString* src, int idx, unsigned count)
{
    unsigned size = (unsigned)(src->mpEnd - src->mpBegin);
    unsigned n = size - idx;
    if (n > count)
        n = count;
    self->assign(src->mpBegin + idx, src->mpBegin + idx + n);
}

// ===========================================================================
// atomics / refcount
// ===========================================================================

// @ 0x006abdf0
int __fastcall FUN_006abdf0(void** self)
{
    return _InterlockedExchangeAdd((volatile long*)*self, -2);
}

// @ 0x006abe00
void __fastcall FUN_006abe00(void** self)
{
    int* p = (int*)*self;
    _InterlockedExchangeAdd((volatile long*)p, -1);
    _InterlockedExchangeAdd((volatile long*)(p + 2), 1);
}

// @ 0x006abee0
bool __fastcall FUN_006abee0(char* self)
{
    if (self[8] == 0)
        self[8] = 1;
    return true;
}

// ===========================================================================
// fixed allocator
// ===========================================================================
struct FixedAlloc {
    char pad00[0x10];
    void* mpFreeList;         // +0x10
    bool AddCore(int, int);   // 0x00926650
    void* AllocateChunk(uint32_t size, int flags);
    void Ctor(unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned); // 0x00926720
    bool Init(unsigned, unsigned, unsigned, unsigned, unsigned, void*, void*, void*);          // 0x009266b0
    FixedAlloc* InitDefaults(int unused);                                                     // @ 0x006ac140
};

// @ 0x006abe50
void* FixedAlloc::AllocateChunk(uint32_t size, int flags)
{
    FixedAlloc* self = this;
    if (size > 0x14)
        return EASTL_allocator_allocate(size, "App", flags, 0, ALLOC_FILE, 0xd1);
    for (;;) {
        void* c = *(void**)((char*)self + 0x10);
        if (c) {
            *(void**)((char*)self + 0x10) = *(void**)c;
            return c;
        }
        if (!self->AddCore(0, 0))
            return 0;
    }
}

// ===========================================================================
// small copy / free helpers
// ===========================================================================

// @ 0x006ac440
uint32_t* FUN_006ac440(uint32_t* dst, uint32_t count, const uint32_t* src)
{
    uint32_t* p = dst;
    while (count != 0) {
        if (p) {
            p[0] = src[0];
            p[1] = src[1];
        }
        p += 2;
        --count;
    }
    return p;
}

// @ 0x006ac470
void __fastcall FUN_006ac470(int self)
{
    int p = *(int*)(self + 4);
    if (p != 0 && p != *(int*)(self + 0x14))
        EASTL_allocator_deallocate((void*)p);
}

// @ 0x006abeb0
extern void* g_cacheManager;   // 0x016c8b44
struct CacheManager {
    void Method(void* p, int a, int b, int c, int d, int e);   // 0x009289f0
};
void FUN_006abeb0(void* p)
{
    ((CacheManager*)g_cacheManager)->Method(p, 0, 0, 0, 0, 0);
}

// ===========================================================================
// caching type accessors
// ===========================================================================
extern char sNullCache;            // 0x0152f7bc
extern char sManualExplicitCache;  // 0x0152f7c0
extern char sLRUCaches;            // 0x016032a8

// @ 0x006ac040
bool SetCachingType(int type, void* obj)
{
    if (*(void**)((char*)obj + 0x14) != 0)
        return false;
    if (type == 2) { *(void**)((char*)obj + 0x14) = &sNullCache; return true; }
    if (type == 1) { *(void**)((char*)obj + 0x14) = &sManualExplicitCache; return true; }
    if ((unsigned)(type - 3) <= 0xa) {
        *(void**)((char*)obj + 0x14) = (char*)&sLRUCaches + (type - 3) * 0x150;
        return true;
    }
    if (type != 0)
        return false;
    return true;
}

struct CacheHolder { void** vtbl; };
inline int CacheHolder_Find(CacheHolder* o, int id)
{
    typedef int (__thiscall* Fn)(void*, int);
    return ((Fn)o->vtbl[0xc / 4])(o, id);
}

// @ 0x006ac0a0
bool FUN_006ac0a0(uint32_t type, CacheHolder* obj)
{
    if (!obj)
        return false;
    int v = CacheHolder_Find(obj, 0x355d6f5);
    if (!v)
        return false;
    return SetCachingType(type, (void*)v);
}

// @ 0x006ac0d0
int FUN_006ac0d0(CacheHolder* obj)
{
    if (!obj)
        return 0;
    int v = CacheHolder_Find(obj, 0x355d6f5);
    if (!v)
        return 0;
    void** c = *(void***)(v + 0x14);
    if (!c)
        return 0;
    if (c == (void**)&sManualExplicitCache) return 1;
    if (c == (void**)&sNullCache) return 2;
    if ((uint32_t)c > 0x16032a7u && (uint32_t)c < 0x1604118u)
        return (int)((char*)c - 0x16032a8) / 0x150 + 3;
    return 0;
}

// ===========================================================================
// Shared declarations for the remaining slice functions
// ===========================================================================

// --- Win32 registry API (imported, stdcall) ---------------------------------
extern "C" __declspec(dllimport) long __stdcall RegOpenKeyExW(void* hKey, const wchar_t* lpSubKey,
        unsigned long ulOptions, unsigned long samDesired, void** phkResult);
extern "C" __declspec(dllimport) long __stdcall RegQueryValueExW(void* hKey, const wchar_t* lpValueName,
        unsigned long* lpReserved, unsigned long* lpType, unsigned char* lpData, unsigned long* lpcbData);
extern "C" __declspec(dllimport) long __stdcall RegCloseKey(void* hKey);
extern "C" __declspec(dllimport) long __stdcall RegEnumKeyExW(void* hKey, unsigned long dwIndex,
        wchar_t* lpName, unsigned long* lpcchName, unsigned long* lpReserved, wchar_t* lpClass,
        unsigned long* lpcchClass, void* lpftLastWriteTime);

extern "C" void* __cdecl memset(void* dst, int value, unsigned size);

void WStr_Format(WString* out, const wchar_t* fmt, uint32_t value);   // 0x0041e050
void operator_delete__(void* p);                                     // 0x00f47410

// Addresses of constants/data in the original image (absolute, as in retail).
#define VA_EMPTY16    0x01667bac
#define VA_EMPTY16_1  0x01667bad
#define VA_EMPTY16_2  0x01667bae
#define VA_REG_FORMAT 0x013fa490
#define VA_ONE_F      0x01485720
#define VA_TWO_F      0x01470f1c

// --- eastl wstring vector used by the RegEnumKeyExW enumeration ------------
struct WStrVector {
    WString* mpBegin;      // +0
    WString* mpEnd;        // +4
    WString* mpCapacity;   // +8
    void push_back(const WString& value);                    // 0x00553f10
    WString* DoDestroyValues(WString* first, WString* last); // 0x0084aad0
};
WString* CopyWStrings(const WString* first, const WString* last, WString* dst);  // 0x0084ab40

// --- subobject constructors referred to by the big object constructor ------
struct cPropertyList {
    void Ctor();   // 0x006a1c40
};

struct cArguments {
    void Ctor();   // 0x00837ff0
};

// --- property descriptor blocks (0x20-byte stride) -------------------------
struct PropBlock {
    void*    mpSchema;     // +0x00 = 0x0154df28
    uint32_t mCount;       // +0x04 = 1
    void*    mpValue;      // +0x08
    float    mMin;         // +0x0c = 1.0f
    float    mMax;         // +0x10 = 2.0f
    void*    mpDefault;    // +0x14
    uint32_t mUnused18;
    uint32_t mUnused1c;
};

struct PropBlockTail {     // last block, clipped by the string member at +0x1c
    void*    mpSchema;
    uint32_t mCount;
    void*    mpValue;
    float    mMin;
    float    mMax;
    void*    mpDefault;
    uint32_t mUnused18;
};

inline void InitPropBlock(PropBlock& b)
{
    b.mMin = *(const float*)VA_ONE_F;
    b.mMax = *(const float*)VA_TWO_F;
    b.mCount = 1;
    b.mpSchema = (void*)0x0154df28;
    b.mpValue = 0;
    b.mpDefault = 0;
}

inline void InitPropBlockTail(PropBlockTail& b)
{
    b.mMin = *(const float*)VA_ONE_F;
    b.mMax = *(const float*)VA_TWO_F;
    b.mCount = 1;
    b.mpSchema = (void*)0x0154df28;
    b.mpValue = 0;
    b.mpDefault = 0;
}

// --- the 0x1ec-byte object built by 006ab3d0 ------------------------------
struct CtorObj_006ab3d0 {
    void* volatile mpVtbl00;   // +0x000
    void* volatile mpVtbl04;   // +0x004
    volatile long  mAtomic08;  // +0x008
    void* volatile mpVtbl0c;   // +0x00c
    void* volatile mpFn10;     // +0x010
    uint8_t  mFlag14;          // +0x014
    uint8_t  mFlag15;          // +0x015
    char     pad16[2];
    void*    mpField18;        // +0x018
    uint8_t  mFlag1c;          // +0x01c
    char     pad1d[3];
    char     pad20[4];
    void*    mpListNext;       // +0x024 (self-referential list sentinel)
    void*    mpListPrev;       // +0x028
    volatile uint32_t mField2c;// +0x02c
    volatile uint32_t mField30;// +0x030
    void*    mpField34;        // +0x034
    char     pad38[4];
    char     mPropertyList[0x3c];   // +0x03c  cPropertyList
    PropBlock mBlocks[5];           // +0x078 0x78, 0x98, 0xb8, 0xd8, 0xf8
    uint32_t mZero118;              // +0x118
    uint32_t mZero11c;              // +0x11c
    char     pad120[0xc];
    PropBlock     mBlock5;          // +0x12c
    PropBlockTail mBlock6;          // +0x14c
    WString  mStr168;               // +0x168
    uint32_t mZero178;              // +0x178
    uint32_t mZero17c;              // +0x17c
    WString  mStr180;               // +0x180
    char     mArguments[0x44];      // +0x190  cArguments
    void*    mpField1d4;            // +0x1d4
    WString  mStr1d8;               // +0x1d8
    uint8_t  mFlag1e8;              // +0x1e8
    char     pad1e9[3];
};

// @ 0x006ab3d0
CtorObj_006ab3d0* __fastcall FUN_006ab3d0(CtorObj_006ab3d0* self)
{
    self->mpVtbl00 = (void*)0x01408ad8;
    self->mpVtbl04 = (void*)0x013effa8;
    _InterlockedExchange(&self->mAtomic08, 0);
    self->mpVtbl04 = (void*)0x013eff74;
    self->mpVtbl0c = (void*)0x013eb384;
    self->mpFn10 = (void*)0x00ad77c2;
    self->mpVtbl00 = (void*)0x014091e8;
    self->mpVtbl04 = (void*)0x014091b0;
    self->mpVtbl0c = (void*)0x014091a0;
    self->mFlag14 = 0;
    self->mFlag15 = 0;
    self->mpField18 = 0;
    self->mFlag1c = 0;

    self->mpListPrev = 0;
    self->mField2c = 0;
    self->mField30 = 0;
    self->mpListNext = &self->mpListNext;
    self->mpListPrev = &self->mpListNext;
    self->mField2c = 0;
    *(volatile uint8_t*)&self->mField30 = 0;
    self->mpField34 = 0;

    ((cPropertyList*)(void*)self->mPropertyList)->Ctor();
    InitPropBlock(self->mBlocks[0]);
    InitPropBlock(self->mBlocks[1]);
    InitPropBlock(self->mBlocks[2]);
    InitPropBlock(self->mBlocks[3]);
    InitPropBlock(self->mBlocks[4]);
    self->mBlocks[4].mUnused1c = 0;
    self->mZero118 = 0;
    self->mZero11c = 0;
    InitPropBlock(self->mBlock5);
    InitPropBlockTail(self->mBlock6);

    self->mStr168.mpBegin = (wchar_t*)VA_EMPTY16;
    self->mStr168.mpEnd = (wchar_t*)VA_EMPTY16;
    self->mStr168.mpCapacity = (wchar_t*)VA_EMPTY16_1;
    self->mZero178 = 0;
    self->mZero17c = 0;
    self->mStr180.mpBegin = (wchar_t*)VA_EMPTY16;
    self->mStr180.mpEnd = (wchar_t*)VA_EMPTY16;
    self->mStr180.mpCapacity = (wchar_t*)VA_EMPTY16_1;

    ((cArguments*)(void*)self->mArguments)->Ctor();
    self->mpField1d4 = 0;
    self->mStr1d8.mpBegin = (wchar_t*)VA_EMPTY16;
    self->mStr1d8.mpEnd = (wchar_t*)VA_EMPTY16;
    self->mStr1d8.mpCapacity = (wchar_t*)VA_EMPTY16_1;
    self->mFlag1e8 = 0;
    return self;
}

// @ 0x006ab6c0
bool FUN_006ab6c0(void* hRoot, const wchar_t* subKey, const wchar_t* valueName, uint32_t* out)
{
    void* hKey = 0;
    if (RegOpenKeyExW(hRoot, subKey, 0, 1, &hKey) == 0) {
        bool ok = false;
        unsigned long type;
        if (RegQueryValueExW(hKey, valueName, 0, &type, 0, 0) == 0) {
            if (type == 4) {
                unsigned long size = 4;
                uint32_t value;
                if (RegQueryValueExW(hKey, valueName, 0, &type, (unsigned char*)&value, &size) == 0) {
                    *out = value;
                    ok = true;
                }
            }
        }
        RegCloseKey(hKey);
        return ok;
    }
    return false;
}

__declspec(noinline) bool FUN_006ab760(void* self, const wchar_t* key);

// @ 0x006ab760
// eastl::hashtable<basic_string<wchar_t>, pair<const basic_string<wchar_t>, basic_string<wchar_t>>,
//                  fixed_hashtable_allocator<6,36,4,4,0,1>>::DoFindNode<wchar_t*, equal_to_2<...>>
bool FUN_006ab760(void* self, const wchar_t* key)
{
    // TODO(partial): fixed-hashtable node search by wchar_t* key.
    (void)self; (void)key;
    return false;
}

// @ 0x006ab840
bool FUN_006ab840(void* hRoot, const wchar_t* subKey, const wchar_t* valueName, WString* out)
{
    void* hKey = 0;
    if (RegOpenKeyExW(hRoot, subKey, 0, 1, &hKey) == 0) {
        bool ok = false;
        unsigned long size;
        unsigned long type;
        uint32_t value;
        wchar_t buffer[0x402];
        if (RegQueryValueExW(hKey, valueName, 0, &type, 0, 0) == 0) {
            if (type == 4) {
                size = type;
                if (RegQueryValueExW(hKey, valueName, 0, &type, (unsigned char*)&value, &size) == 0) {
                    WStr_Format(out, (const wchar_t*)VA_REG_FORMAT, value);
                    ok = true;
                }
            } else if (type == 1) {
                size = 0x400;
                if (RegQueryValueExW(hKey, valueName, 0, &type, (unsigned char*)buffer, &size) == 0) {
                    out->assign(buffer, size - 1);
                    ok = true;
                }
            }
        }
        RegCloseKey(hKey);
        return ok;
    }
    return false;
}

// @ 0x006ab950
bool FUN_006ab950(void* hRoot, const wchar_t* path, WString* out)
{
    WString s;
    s.range_initialize(path);
    int idx = s.rfind(L'\\', 0xffffffffu);
    unsigned size = (unsigned)(s.mpEnd - s.mpBegin);
    if ((unsigned)idx < size) {
        WString tail(s, (unsigned)idx + 1, size - (unsigned)idx - 1);
        s.erase((unsigned)idx, size - (unsigned)idx);
        return FUN_006ab840(hRoot, s.mpBegin, tail.mpBegin, out);
    }
    return false;
}

// @ 0x006aba80
bool D3D9ShaderGeneric3DMorphingInitialize(const wchar_t* path, WString* out)
{
    WString root;
    root.mpBegin = (wchar_t*)VA_EMPTY16;
    root.mpEnd = (wchar_t*)VA_EMPTY16;
    root.mpCapacity = (wchar_t*)VA_EMPTY16_2;

    WString s;
    s.range_initialize(path);
    unsigned size = (unsigned)(s.mpEnd - s.mpBegin);
    unsigned idx = 0xffffffff;
    for (unsigned i = 0; i < size; ++i) {
        if (s.mpBegin[i] == L'\\') {
            idx = i;
            break;
        }
    }
    if (size <= idx)
        return false;
    root.assign(s.mpBegin, s.mpBegin + idx);
    s.erase(0, idx + 1);

    void* key;
    if (FUN_006ab760(&root, (const wchar_t*)0x01409350))        // L"HKEY_CLASSES_ROOT"
        key = (void*)0x80000000;
    else if (FUN_006ab760(&root, (const wchar_t*)0x0140932c))   // L"HKEY_CURRENT_USER"
        key = (void*)0x80000001;
    else if (FUN_006ab760(&root, (const wchar_t*)0x01409304))   // L"HKEY_LOCAL_MACHINE"
        key = (void*)0x80000002;
    else if (FUN_006ab760(&root, (const wchar_t*)0x014092ec))   // L"HKEY_USERS"
        key = (void*)0x80000003;
    else if (FUN_006ab760(&root, (const wchar_t*)0x014092c4))   // L"HKEY_CURRENT_CONFIG"
        key = (void*)0x80000005;
    else
        return false;
    return FUN_006ab950(key, s.mpBegin, out);
}

// @ 0x006abc90
int FUN_006abc90(void* hRoot, const wchar_t* subKey, WStrVector* out)
{
    WString* first = out->mpBegin;
    WString* last = out->mpEnd;
    WString* r = CopyWStrings(last, last, first);
    out->DoDestroyValues(r, out->mpEnd);
    out->mpEnd += out->mpBegin - out->mpEnd;

    void* hKey = 0;
    if (RegOpenKeyExW(hRoot, subKey, 0, 8, &hKey) == 0) {
        bool stop = false;
        unsigned long index = 0;
        do {
            unsigned long size = 0x400;
            WString temp;
            wchar_t buffer[0x402];
            long rc = RegEnumKeyExW(hKey, index, buffer, &size, 0, 0, 0, 0);
            if (rc == 0) {
                temp.range_initialize(buffer);
                out->push_back(temp);
            } else if (rc == 0x103) {
                stop = true;
            }
            ++index;
        } while (!stop);
        RegCloseKey(hKey);
        return (int)(out->mpEnd - out->mpBegin);
    }
    return 0;
}

// --- spin/"critical section"-style object used by the two retire helpers ---
struct SpinObj {
    volatile long mWord;   // +0x00
    volatile long mBegin;  // +0x04
    volatile long mEnd;    // +0x08
    int  mSpin;            // +0x0c

    void RetireOne();      // @ 0x006abf20
    void RetireTwo();      // @ 0x006abfa0
};
extern "C" void ThreadSleep(const void* ms);   // 0x00921df0

// @ 0x006abf20
void SpinObj::RetireOne()
{
    int spin = mSpin;
    while (mEnd != mBegin) {
        if (spin > 0) {
            --spin;
            _mm_pause();
        } else {
            spin = mSpin;
            ThreadSleep((const void*)0x014093b0);
        }
    }
    _InterlockedExchangeAdd((volatile long*)&mWord, 2);
    spin = mSpin;
    while ((mWord & 1) != 0) {
        if (spin > 0) {
            --spin;
            _mm_pause();
        } else {
            spin = mSpin;
            ThreadSleep((const void*)0x014093b0);
        }
    }
}

// @ 0x006abfa0
void SpinObj::RetireTwo()
{
    int target = _InterlockedIncrement((volatile long*)&mBegin) - 1;
    int spin = mSpin;
    while (mEnd != target) {
        if (spin > 0) {
            --spin;
            _mm_pause();
        } else {
            spin = mSpin;
            ThreadSleep((const void*)0x014093b0);
        }
    }
    while (_InterlockedCompareExchange((volatile long*)&mWord, 1, 0) != 0) {
        while (mWord != 0) {
            if (spin > 0) {
                --spin;
                _mm_pause();
            } else {
                spin = mSpin;
                ThreadSleep((const void*)0x014093b0);
            }
        }
    }
}

// --- eastl fixed hashtable used by the last four targets -------------------
struct RefCounted {
    void** mpVtbl;   // +0x00
};
typedef void (__fastcall* RefCountCall)(void*);
inline void RefAddRef(RefCounted* p)    { ((RefCountCall)p->mpVtbl[0])(p); }
inline void RefRelease(RefCounted* p)   { ((RefCountCall)p->mpVtbl[1])(p); }

struct HashNode {
    union { uint32_t mHash; HashNode* mpFreeNext; };  // +0x00 (free-list link while free)
    uint32_t   mKey;      // +0x04
    uint32_t   mExtra;    // +0x08
    RefCounted* mpValue;  // +0x0c
    HashNode*  mpNext;    // +0x10
};

struct HashTable {
    void*       mpAllocator;    // +0x00
    HashNode**  mpBuckets;      // +0x04
    uint32_t    mBucketCount;   // +0x08
    char        pad0c[0x10];
    FixedAlloc  mAlloc;         // +0x1c (free list at +0x2c)
    HashNode* AllocateNode(const HashNode* value);            // @ 0x006ac260
    void      Rehash(unsigned count);                         // @ 0x006ac2f0
    void      FreeBuckets(HashNode** buckets, unsigned count); // @ 0x006ac5d0
};

struct NodeFactory {
    void* NewNode(void** value);   // @ 0x006ac3c0
};

// @ 0x006ac140
FixedAlloc* FixedAlloc::InitDefaults(int unused)
{
    (void)unused;
    Ctor(0, 0, 0x80, 0, 0xffffffff, 0, 0, 0);
    Init(0x14, 0, 0x200, 0, 0xffffffff, (void*)0x006abeb0, (void*)0x00f47410, this);
    return this;
}

// @ 0x006ac260
HashNode* HashTable::AllocateNode(const HashNode* value)
{
    HashNode* node;
    for (;;) {
        node = (HashNode*)mAlloc.mpFreeList;
        if (node) {
            mAlloc.mpFreeList = node->mpFreeNext;
            break;
        }
        if (!mAlloc.AddCore(0, 0)) {
            node = 0;
            break;
        }
    }
    if (node) {
        node->mHash = value->mHash;
        node->mKey = value->mKey;
        node->mExtra = value->mExtra;
        node->mpValue = value->mpValue;
        if (node->mpValue)
            RefAddRef(node->mpValue);
    }
    node->mpNext = 0;
    return node;
}

// @ 0x006ac2f0
void HashTable::Rehash(unsigned count)
{
    uint32_t size = count * 4;
    HashNode** buckets = (HashNode**)mAlloc.AllocateChunk(size + 4, 0);
    memset(buckets, 0, size);
    *(uint32_t*)((char*)buckets + size) = 0xffffffff;
    for (unsigned i = 0; i < mBucketCount; ++i) {
        HashNode* node = mpBuckets[i];
        while (node) {
            unsigned index = (node->mExtra ^ node->mHash) % count;
            mpBuckets[i] = node->mpNext;
            node->mpNext = buckets[index];
            buckets[index] = node;
            node = mpBuckets[i];
        }
    }
    if (mBucketCount > 1) {
        if (mBucketCount * 4 + 4 <= 0x14) {
            *(void**)mpBuckets = mAlloc.mpFreeList;
            mAlloc.mpFreeList = mpBuckets;
        } else {
            EASTL_allocator_deallocate(mpBuckets);
        }
    }
    mBucketCount = count;
    mpBuckets = buckets;
}

// @ 0x006ac3c0
void* NodeFactory::NewNode(void** value)
{
    char* node = (char*)EASTL_allocator_allocate(0xc, "App", 0, 0, ALLOC_FILE, 0xd1);
    RefCounted** slot = (RefCounted**)(node + 8);
    *slot = *(RefCounted**)value;
    if (*slot)
        RefAddRef(*slot);
    return node;
}

// @ 0x006ac5d0
void HashTable::FreeBuckets(HashNode** buckets, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        HashNode* p = buckets[i];
        while (p) {
            HashNode* node = p;
            p = node->mpNext;
            if (node->mpValue)
                RefRelease(node->mpValue);
            node->mpFreeNext = (HashNode*)mAlloc.mpFreeList;
            mAlloc.mpFreeList = node;
        }
        buckets[i] = 0;
    }
}
