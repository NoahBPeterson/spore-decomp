// src/game/Havok/_at_01070000.cpp -- migrated from slice(s) s0107d6a0 by tools/migrate/rewrite.py
// Object file: Havok/_at_01070000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_149c85c[];
extern "C" char g_149c894[];

#include "game/types.h"
#include <malloc.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" __int64 __stdcall _allmul(int lo, int hi, int mlo, int mhi); // lib_crt::allmul
extern "C" void __cdecl __debugbreak(void);
extern unsigned long g_tlsThreadMemory;           // 0x016e4174
extern void* g_hkStreambufFactorySingleton;   // 0x016e42b4
#if _MSC_VER >= 1400
#pragma intrinsic(__debugbreak)
#endif

// ---- items of slice s0107d6a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])
class Dummy;
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
void* hkMemSet(void* dst, int c, int n);          // 0x0107f470 hkString::memSet
extern "C" __int64 __stdcall _allmul(int lo, int hi, int mlo, int mhi); // lib_crt::allmul
extern "C" void __cdecl __debugbreak(void);
extern unsigned long g_tlsThreadMemory;           // 0x016e4174
class hkMemory;
class hkMemory {
public:
    void* mpVtbl;            // +0x00
    char pad04[8];
    int mnRefCount;          // +0x0c
    // virtuals: +0x10 allocate, +0x14 deallocate, +0x18 allocate2,
    //           +0x1c deallocate2, +0x34 destroy
    int getAllocatedSize(int size);                       // 0x0107dcf0
    static void replaceInstance(hkMemory* p);             // 0x0107dd30
    void* allocateChunkByRow(int row, int memClass);      // 0x0107dd70
    void deallocateChunkByRow(void* p, int row, int memClass); // 0x0107dda0
};
class hkMemoryVt {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void deallocate2(void* p, int row, int one);
    virtual bool v20();
};
extern hkMemory* g_hkMemory;      // 0x016e4178
class hkThreadMemDestroyVt {
public:
    virtual void v00();
    virtual void v04();
    virtual void destroy(int flags);
};
#if _MSC_VER >= 1400
inline void* hkAlloc(int size, int cls)
{
    return ((void*(__thiscall*)(void*, int, int))VFN(g_hkMemory, 0x10))(g_hkMemory, size, cls);
}
inline void hkFree(void* p, int size, int cls)
{
    ((void(__thiscall*)(void*, void*, int, int))VFN(g_hkMemory, 0x14))(g_hkMemory, p, size, cls);
}
#else
class hkMemoryAllocVt {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void* allocate(int size, int cls);
    virtual void deallocate(void* p, int size, int cls);
};
inline void* hkAlloc(int size, int cls)
{
    return ((hkMemoryAllocVt*)g_hkMemory)->allocate(size, cls);
}
inline void hkFree(void* p, int size, int cls)
{
    ((hkMemoryAllocVt*)g_hkMemory)->deallocate(p, size, cls);
}
#endif
template<class KEY> class hkPointerMapBase {
public:
    KEY* mTable;    // +0x0
    int  mCount;    // +0x4
    int  mMask;     // +0x8

    hkPointerMapBase();
    ~hkPointerMapBase();
    void clear();
    void insert(KEY k, KEY v);
    Dummy* findKey(KEY k) const;
    int findIndex(KEY k) const;   // findKey as Havok inlines it into get/hasKey
    hkResult get(KEY k, KEY* out) const;
    void remove(Dummy* d);
    hkResult remove(KEY k);
    KEY getWithDefault(KEY k, KEY def) const;
    void resizeTable(int newSize);
    void FUN_0107e5b0(int numElements);   // reserve, KEY = unsigned long (tail-calls resizeTable)
    void FUN_0107e5d0(int numElements);   // reserve, KEY = unsigned __int64
};
template<class KEY> inline int hkPointerMapBase<KEY>::findIndex(KEY k) const
{
    for (int i = (int)(((k >> 4) * (KEY)0x9e3779b1ul) & (KEY)mMask); mTable[i] != 0; i = (i + 1) & mMask)
        if (mTable[i] == k)
            return i;
    return mMask + 1;
}
template<> void hkPointerMapBase<unsigned long>::FUN_0107e5b0(int numElements);
template<> void hkPointerMapBase<unsigned __int64>::FUN_0107e5d0(int numElements);
template class hkPointerMapBase<unsigned long>;
template class hkPointerMapBase<unsigned __int64>;
extern void* g_hkStreambufFactorySingleton;   // 0x016e42b4
class hkStreambufFactory;
template<class T> class hkSingleton {
public:
    static T* ms_instance;
    static void replaceInstance(T* p);
};
template<class T> T* hkSingleton<T>::ms_instance = 0;
#include "_at_01070000_thread_memory.h"
struct hkSmallObj { void* FUN_0107dc90(); };
static __forceinline int hkSizeToClass(int size)
{
    if (size <= 8) return 1;
    if (size <= 0x10) return 2;
    if (size <= 0x20) return 3;
    if (size <= 0x30) return 4;
    if (size <= 0x40) return 5;
    if (size <= 0x60) return 6;
    if (size <= 0x80) return 7;
    if (size <= 0xa0) return 8;
    if (size <= 0xc0) return 9;
    if (size <= 0x100) return 10;
    if (size <= 0x140) return 11;
    if (size <= 0x200) return 12;
    if (size <= 0x400) return 13;
    if (size <= 0x800) return 14;
    if (size <= 0x1000) return 15;
    if (size <= 0x2000) return 16;
    __debugbreak();
    return -1;
}
// ---- items of slice s0107d6a0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern hkMemory* g_hkMemory;      // 0x016e4178

// @ 0x0107d740
#pragma optimize("s", on)
void hkThreadMemory::releaseCachedMemory()
{
    for (int cls = 0x10; cls >= 0; --cls) {
        int* head = &mRows[cls];
        while (*head != 0) {
            int* node = (int*)*head;
            *head = *node;
            ((hkMemoryVt*)mMemory)->deallocate2(node, cls, 1);
        }
        *head = 0;
        mRowCounts[cls] = 0;
    }
}
#pragma optimize("", on)


// @ 0x0107d7a0
void hkThreadMemory::setStackArea(void* p, int n)
{
    int a = (int)p;
    int rem = a & 0xf;
    mStackCurrent = -1;
    mStackSize = n;
    if (rem != 0) {
        int base = (a - rem) + 0x10;
        mStackBase = base;
        mStackEnd = (base - rem) + n;
    } else {
        mStackBase = a;
        mStackEnd = a + n;
    }
}

// @ 0x0107d7e0
hkThreadMemory::hkThreadMemory(hkMemory* memory, int stackSize)
{
    mpVtbl = (void*)0x149c848;
    mnRefCount = 1;
    mStackBase = 0;
    mStackAlloc = 0;
    mStackCurrent = -1;
    mStackEnd = 0;
    mMemory = memory;
    mMaxRows = ((hkMemoryVt*)memory)->v20() ? stackSize : 0;
    int* p = &mRowCounts[0x10];
    int n = 0x11;
    do {
        p[-0x11] = 0;
        *p = 0;
        --p;
    } while (--n);
    for (int s = 0; s <= 0x200; ++s) {
        int cls = hkSizeToClass(s);
        mClassForSize[s] = (signed char)cls;
        mClassMax[cls] = s;
    }
    int* extra = mExtra;
    for (int s = 0x400; s < 0x2400; s += 0x400) {
        int cls = hkSizeToClass(s);
        *extra++ = cls;
        mClassMax[cls] = s;
    }
}

#if _MSC_VER >= 1400
// @ 0x0107daa0
void* hkThreadMemory::allocateChunk(int size, int cls)
{
    if (size > 0x2000 || mMaxRows == 0)
        return ((void*(__thiscall*)(void*, int, int))VFN(mMemory, 0x10))(mMemory, size, cls);
    int row;
    if (size <= 0x200)
        row = mClassForSize[size];
    else
        row = *(int*)((char*)this + 0x308 + ((size - 1) >> 10) * 4);
    int head = *(int*)((char*)this + 0x38 + row * 4);
    if (head != 0) {
        --mRowCounts[row];
        *(int*)((char*)this + 0x38 + row * 4) = *(int*)head;
        return (void*)head;
    }
    return ((void*(__thiscall*)(void*, int, int))VFN(mMemory, 0x18))(mMemory, row, cls);
}

// @ 0x0107db10
void hkThreadMemory::deallocateChunk(void* p, int size, int cls)
{
    if (size > 0x2000 || mMaxRows == 0) {
        ((void(__thiscall*)(void*, void*, int, int))VFN(mMemory, 0x14))(mMemory, p, size, cls);
        return;
    }
    int row;
    if (size <= 0x200)
        row = mClassForSize[size];
    else
        row = *(int*)((char*)this + 0x308 + ((size - 1) >> 10) * 4);
    if (*(int*)((char*)this + 0x7c + row * 4) < mMaxRows) {
        *(int*)p = *(int*)((char*)this + 0x38 + row * 4);
        *(int*)((char*)this + 0x38 + row * 4) = (int)p;
        ++mRowCounts[row];
        return;
    }
    ((void(__thiscall*)(void*, void*, int, int))VFN(mMemory, 0x1c))(mMemory, p, row, cls);
}
#endif

// @ 0x0107db90
void hkThreadMemory::onStackUnderflow(void* p)
{
    int cur = mStackCurrent;
    int end = mStackEnd;
    int base = cur - 0x10;
    int n = (end - cur) + 0x10;
    mStackBase = *(int*)(base);
    mStackAlloc = *(int*)(base + 4);
    mStackCurrent = *(int*)(base + 8);
    mStackEnd = *(int*)(base + 0xc);
    deallocateChunk((void*)base, n, 0x14);
}

// @ 0x0107dbd0
void hkThreadMemory::replaceInstance(hkThreadMemory* p)
{
    if (p)
        ++p->mnRefCount;
    hkThreadMemory* old = (hkThreadMemory*)TlsGetValue(g_tlsThreadMemory);
    if (old != 0) {
        if (--old->mnRefCount == 0)
            ((hkThreadMemDestroyVt*)old)->destroy(1);
    }
    TlsSetValue(g_tlsThreadMemory, p);
}

// @ 0x0107dc10
void* hkThreadMemory::onStackOverflow(int stackSize)
{
    int n = stackSize + 0x400;
    if (n < 0x1000)
        n = 0x1000;
    hkThreadMemory* t = (hkThreadMemory*)TlsGetValue(g_tlsThreadMemory);
    int* src = &mStackBase;
    int* dst = (int*)t->allocateChunk(n + 0x10, 0x14);
    int* handle;
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
    dst[3] = src[3];
    handle = dst + 4;
    src[0] = (int)handle + stackSize;
    src[2] = (int)handle;
    src[3] = (int)handle + n;
    src[1] = (int)dst;
    return handle;
}

// @ 0x0107dc90
void* hkSmallObj::FUN_0107dc90()
{
    void* self = this;
    char* p = (char*)self;
    *(void**)p = (void*)g_149c85c;
    *(int*)(p + 0xc) = 1;
    *(int*)(p + 0x10) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x1c) = 0;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = 0;
    *(int*)(p + 4) = 0;
    *(int*)(p + 8) = 0x7fffffff;
    return self;
}

// @ 0x0107dcf0
int hkMemory::getAllocatedSize(int size) // 0x0107dcf0
{
    if (size > 0x10)
        return (size + 0xf & 0xfffffff0) + 0x10;
    return size + 8;
}

#if _MSC_VER >= 1400
// @ 0x0107dd30
void hkMemory::replaceInstance(hkMemory* p)
{
    if (p != 0)
        ++p->mnRefCount;
    hkMemory* old = g_hkMemory;
    if (old != 0) {
        if (--old->mnRefCount == 0)
            ((void(__thiscall*)(void*, int))VFN(old, 0x34))(old, 1);
    }
    g_hkMemory = p;
}

// @ 0x0107dd70
void* hkMemory::allocateChunkByRow(int row, int memClass)
{
    void* tls = TlsGetValue(g_tlsThreadMemory);
    return ((void*(__thiscall*)(void*, int, int))VFN(this, 0x10))
        (this, *(int*)((char*)tls + row * 4 + 0xc0), memClass);
}

// @ 0x0107dda0
void hkMemory::deallocateChunkByRow(void* p, int row, int memClass)
{
    void* tls = TlsGetValue(g_tlsThreadMemory);
    ((void(__thiscall*)(void*, void*, int, int))VFN(this, 0x14))
        (this, p, *(int*)((char*)tls + row * 4 + 0xc0), memClass);
}
#endif

// @ 0x0107ddd0
template<class KEY> void hkPointerMapBase<KEY>::clear()
{
    hkMemSet(mTable, 0, (mMask + 1) * (int)sizeof(KEY) * 2);
    mCount = 0;
}

// @ 0x0107de00
template<class KEY> hkPointerMapBase<KEY>::hkPointerMapBase()
{
    int bytes = 0x10 * (int)sizeof(KEY) * 2;
    mTable = (KEY*)hkAlloc(bytes, 0x14);
    hkMemSet(mTable, 0, bytes);
    mCount = 0;
    mMask = 0x0f;
    clear();
}

// @ 0x0107de50 ??1?$hkPointerMapBase@K@@QAE@XZ
template<class KEY> hkPointerMapBase<KEY>::~hkPointerMapBase()
{
    int n = (mMask + 1) * (int)sizeof(KEY) * 2;
    hkFree(mTable, n, 0x14);
}

// @ 0x0107de70
template<class KEY> void hkPointerMapBase<KEY>::insert(KEY k, KEY v)
{
    if (mCount * 2 > mMask)
        resizeTable(mMask * 2 + 2);
    KEY h = (KEY)((k >> 4) * (KEY)0x9e3779b1ul);
    int idx = (int)(h & (KEY)mMask);
    while (mTable[idx] != 0 && mTable[idx] != k)
        idx = (idx + 1) & mMask;
    if (mTable[idx] != k)
        ++mCount;
    mTable[idx] = k;
    mTable[mMask + 1 + idx] = v;
}

// @ 0x0107def0
template<class KEY> Dummy* hkPointerMapBase<KEY>::findKey(KEY k) const
{
    KEY h = (KEY)((k >> 4) * (KEY)0x9e3779b1ul);
    int idx = (int)(h & (KEY)mMask);
    while (mTable[idx] != 0) {
        if (mTable[idx] == k)
            return (Dummy*)idx;
        idx = (idx + 1) & mMask;
    }
    return (Dummy*)(mMask + 1);
}

// @ 0x0107df30
template<class KEY> hkResult hkPointerMapBase<KEY>::get(KEY k, KEY* out) const
{
    int i = findIndex(k);
    if (i <= mMask) {
        *out = mTable[mMask + 1 + i];
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

// @ 0x0107df90
template<> void hkPointerMapBase<unsigned long>::remove(Dummy* d)
{
    unsigned int i = (unsigned int)(int)d;
    --mCount;
    mTable[i] = 0;
    unsigned int mask = (unsigned int)mMask;
    unsigned int p = (mask + i) & mask;
    while (mTable[p] != 0)
        p = (p + mask) & mask;
    unsigned int s = (p + 1) & mask;
    for (unsigned int j = (i + 1) & mask; mTable[j] != 0; j = (j + 1) & mask) {
        unsigned long v = mTable[j];
        unsigned int k = ((unsigned int)(v >> 4) * 0x9e3779b1u) & mask;
        if (((j < s) || (k <= i)) &&
            ((i <= j) || (k <= i && j < k)) &&
            ((k <= i) || (s <= k))) {
            mTable[i] = v;
            mTable[mask + 1 + i] = mTable[mask + 1 + j];
            mTable[j] = 0;
            i = j;
        }
    }
}

// @ 0x0107e050
template<class KEY> void hkPointerMapBase<KEY>::resizeTable(int newSize)
{
    KEY* old = mTable;
    int oldCount = mMask + 1;
    KEY* nt = (KEY*)hkAlloc(newSize * (int)sizeof(KEY) * 2, 0x14);
    mTable = nt;
    hkMemSet(nt, 0, newSize * (int)sizeof(KEY));
    mMask = newSize - 1;
    mCount = 0;
    for (int i = 0; i < oldCount; ++i)
        if (old[i] != 0)
            insert(old[i], old[oldCount + i]);
    hkFree(old, oldCount * (int)sizeof(KEY) * 2, 0x14);
}

// @ 0x0107e2d0
template<> void hkPointerMapBase<unsigned __int64>::remove(Dummy* d)
{
    unsigned __int64 i = (unsigned __int64)(int)d;
    --mCount;
    mTable[i] = 0;
    unsigned __int64 mask = (unsigned __int64)mMask;
    unsigned __int64 p = (mask + i) & mask;
    while (mTable[p] != 0)
        p = (p + mask) & mask;
    unsigned __int64 s = (p + 1) & mask;
    for (unsigned __int64 j = (i + 1) & mask; mTable[j] != 0; j = (j + 1) & mask) {
        unsigned __int64 v = mTable[j];
        unsigned __int64 sh = v >> 4;
        __int64 prod = _allmul((int)sh, (int)(sh >> 32), (int)0x9e3779b1u, 0);
        unsigned __int64 k = (unsigned __int64)prod & mask;
        if (((j < s) || (k <= i)) &&
            ((i <= j) || (k <= i && j < k)) &&
            ((k <= i) || (s <= k))) {
            mTable[i] = v;
            mTable[mask + 1 + i] = mTable[mask + 1 + j];
            mTable[j] = 0;
            i = j;
        }
    }
}

// @ 0x0107e540
template<class KEY> KEY hkPointerMapBase<KEY>::getWithDefault(KEY k, KEY def) const
{
    if (get(k, &k) == HK_SUCCESS)
        return k;
    return def;
}

// @ 0x0107e560
template<class KEY> hkResult hkPointerMapBase<KEY>::remove(KEY k)
{
    KEY h = (KEY)((k >> 4) * (KEY)0x9e3779b1ul);
    int idx = (int)(h & (KEY)mMask);
    while (mTable[idx] != 0) {
        if (mTable[idx] == k)
            goto found;
        idx = (idx + 1) & mMask;
    }
    idx = mMask + 1;
found:
    if (idx <= mMask) {
        remove((Dummy*)idx);
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

// @ 0x0107e5b0
template<> void hkPointerMapBase<unsigned long>::FUN_0107e5b0(int numElements)
{
    int need = 3 * numElements;
    int s = 4;
    if (need > s) {
        do { s += s; } while (s < need);
    }
    resizeTable(s);
}

// @ 0x0107e5d0
template<> void hkPointerMapBase<unsigned __int64>::FUN_0107e5d0(int numElements)
{
    int need = 3 * numElements;
    int s = 4;
    if (need > s) {
        do { s += s; } while (s < need);
    }
    resizeTable(s);
}

#if _MSC_VER >= 1400
// @ 0x0107e5f0
template<> void hkSingleton<hkStreambufFactory>::replaceInstance(hkStreambufFactory* p)
{
    void* old = g_hkStreambufFactorySingleton;
    if (old == 0) {
        g_hkStreambufFactorySingleton = p;
        return;
    }
    if (*(short*)((char*)old + 4) != 0) {
        short* rc = (short*)((char*)old + 6);
        --*rc;
        if (*rc == 0)
            ((void(__thiscall*)(void*, int))VFN(old, 0))(old, 1);
        g_hkStreambufFactorySingleton = p;
        return;
    }
    g_hkStreambufFactorySingleton = p;
}
#endif

// @ 0x0107e640
void FUN_0107e640()
{
    struct Obj8 {
        void* vt;
        unsigned short memSizeAndFlags;
        unsigned short referenceCount;
    };
    Obj8* p = (Obj8*)hkAlloc(sizeof(Obj8), 0x15);
    p->memSizeAndFlags = 8;
    p->referenceCount = 1;
    p->vt = (void*)g_149c894;
}

// ---- items of slice s0107e670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C"
{
	__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
	__declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
	__declspec(dllimport) int __stdcall TryEnterCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);
	__declspec(dllimport) int __stdcall InitializeCriticalSectionAndSpinCount(void* cs, unsigned long spin);
	__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) void* __stdcall GetCurrentProcess(void);
	__declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
	__declspec(dllimport) int __stdcall FreeLibrary(void* module);
	__declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
}
extern void* SporeAlloc(size_t nbytes);                                                        // 0x006ABEB0
extern bool g_hkBaseSystemInitialized;                                                         // 0x016E4180
extern void* g_SymGetModuleBase64;                     // 0x016E418C
extern void* g_SymFunctionTableAccess64;               // 0x016E4190
extern void* g_StackWalk64;                            // 0x016E4194
extern int g_dbghelpRefCount;                          // 0x016E41A8
extern void* g_dbghelpModule;                          // 0x016E41AC
extern bool g_stackTracerReportedMissingSymbols;       // 0x016E41B0
extern const char* g_dbghelpName;                      // 0x015B9A48 -> "dbghelp.dll"
#define HK_BREAKPOINT() __debugbreak()
typedef int16_t hkInt16;
typedef uint16_t hkUint16;
typedef uint32_t hkUint32;
typedef uint64_t hkUint64;
class hkBool_s0107_e670
{
public:
	hkBool_s0107_e670() {}
	hkBool_s0107_e670(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};
enum
{
	HK_MEMORY_CLASS_ARRAY = 0x14,
	HK_MEMORY_CLASS_BASE = 0x15,
	HK_MEMORY_CLASS_STREAM = 0x17
};
struct hkMemoryStatistics
{
	int m_numBigBlocks;       // 0x10 in hkMemory
	int m_bigBlockBytes;      // 0x14
	int m_peakBigBlockBytes;  // 0x18
	int m_numPages;           // 0x1c
	int m_pageSize;           // 0x20
	int m_pageAlignment;      // 0x24
	int m_inUseBytes;         // 0x28
};
class hkOstream_s0107_e670;
class hkMemory_s0107_e670
{
public:
	virtual void* allocate(int nbytes, int cl);                          // 0
	virtual void deallocate(void* p);                                    // 1
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);    // 2
	virtual void alignedDeallocate(void* p);                             // 3
	virtual void* allocateChunk(int nbytes, int cl);                     // 4
	virtual void deallocateChunk(void* p, int nbytes, int cl);           // 5
	virtual void* allocateChunkByRow(int row, int cl);                   // 6 0x0107dd70
	virtual void deallocateChunkByRow(void* p, int row, int cl);         // 7 0x0107dda0
	virtual void slot8();                                                // 8 (0x00B1FBF0)
	virtual void printStatistics(hkOstream_s0107_e670* o);                          // 9
	virtual int getAllocatedSize(int nbytes);                            // 10 0x0107dcf0
	virtual void getStatSynopsis(hkMemoryStatistics* s);                 // 11
	virtual bool slot12();                                               // 12 (0x01091960, returns 0)
	virtual ~hkMemory_s0107_e670() {}                                               // 13 (deleting dtor 0x0107FBC0 for the pool)

	static hkMemory_s0107_e670* s_instance;
	static void replaceInstance(hkMemory_s0107_e670* m);  // 0x0107dd30 (hkMemory::replaceInstance)

	hkMemory_s0107_e670();                      // 0x0107DC90 (not in these slices)

	int m_unk04;                     // 0x04
	int m_unk08;                     // 0x08 (0x7FFFFFFF)
	int m_unk0c;                     // 0x0c (1)
	hkMemoryStatistics m_stats;      // 0x10..0x2b
};
class hkStatisticsCollector;
class hkBaseObject_s0107_e670
{
public:
	virtual ~hkBaseObject_s0107_e670() {} // one-slot primary base
};
class hkReferencedObject_s0107_e670 : public hkBaseObject_s0107_e670
{
public:
	virtual ~hkReferencedObject_s0107_e670() {}                                     // 0
	virtual void calcStatistics(hkStatisticsCollector*) const {}           // 1 (0x0052E650, empty, ret4)

	// HK_DECLARE_CLASS_ALLOCATOR with the stream memory class, as the binary allocates these objects.
	static void* operator new(size_t nbytes)
	{
		void* p = hkMemory_s0107_e670::s_instance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_STREAM);
		((hkReferencedObject_s0107_e670*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory_s0107_e670::s_instance->deallocateChunk(p, ((hkReferencedObject_s0107_e670*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_STREAM);
	}
	static void* operator new(size_t, void* p) { return p; }
	static void operator delete(void*, void*) {}

	// memSize == 0 means the object is not heap-owned and is never reference counted.
	void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			if (--m_referenceCount == 0)
				delete this;
		}
	}

	hkUint16 m_memSizeAndFlags; // 0x04
	hkInt16 m_referenceCount;   // 0x06

protected:
	hkReferencedObject_s0107_e670() : m_referenceCount(1) {}
};
class hkStreamReader : public hkReferencedObject_s0107_e670
{
public:
	enum SeekWhence { STREAM_SET = 0, STREAM_CUR = 1, STREAM_END = 2 };

	virtual hkBool_s0107_e670 isOk() const = 0;                              // 2
	virtual int read(void* buf, int nbytes) = 0;                  // 3
	virtual int skip(int nbytes);                                 // 4  0x010808F0
	virtual hkBool_s0107_e670 markSupported() const;                         // 5
	virtual hkResult setMark(int markLimit);                      // 6
	virtual hkResult rewindToMark();                              // 7
	virtual hkBool_s0107_e670 seekTellSupported() const;                     // 8
	virtual hkResult seek(int offset, SeekWhence whence);         // 9
	virtual int tell() const;                                     // 10
};
class hkSeekableStreamReader : public hkStreamReader
{
public:
	virtual hkResult setMark(int markLimit);                      // 0x0107E740
	virtual hkResult rewindToMark();                              // 0x0107E760
	int m_markPos;                                                // 0x08

protected:
	hkSeekableStreamReader() : m_markPos(-1) {}
};
class hkStreamWriter : public hkReferencedObject_s0107_e670
{
public:
	enum SeekWhence { STREAM_SET = 0, STREAM_CUR = 1, STREAM_END = 2 };

	virtual hkBool_s0107_e670 isOk() const = 0;                              // 2
	virtual int write(const void* buf, int nbytes) = 0;           // 3
	virtual void flush();                                         // 4
	virtual hkBool_s0107_e670 seekTellSupported() const;                     // 5
	virtual hkResult seek(int offset, SeekWhence whence);         // 6
	virtual int tell() const;                                     // 7
};
typedef struct _iobuf FILE;
class hkStdioStreamReader : public hkSeekableStreamReader
{
public:
	hkStdioStreamReader(const char* name);                        // 0x0107E700
	virtual ~hkStdioStreamReader();                               // 0x0107E7E0 (deleting)
	virtual hkBool_s0107_e670 isOk() const;
	virtual int read(void* buf, int nbytes);
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;

	FILE* m_file;                                                 // 0x0c
	hkBool_s0107_e670 m_ok;                                                  // 0x10
	void* scalar_deleting_dtor(unsigned char flags);              // 0x0107E7E0
};
class hkStdioStreamWriter : public hkStreamWriter
{
public:
	hkStdioStreamWriter(const char* name);                        // 0x0107E890
	virtual ~hkStdioStreamWriter();                               // 0x0107E9A0 (deleting)
	virtual hkBool_s0107_e670 isOk() const;                                  // 0x0107E950
	virtual int write(const void* buf, int nbytes);
	virtual void flush();
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;
	void close();                                                 // 0x0107E910

	FILE* m_file;                                                 // 0x08
	hkBool_s0107_e670 m_ownsFile;                                            // 0x0c
	void* scalar_deleting_dtor(unsigned char flags);              // 0x0107E9A0
};
class hkBufferedStreamReader : public hkStreamReader
{
public:
	hkBufferedStreamReader(hkStreamReader* s, int bufSize);       // 0x01080830
	virtual ~hkBufferedStreamReader();                            // 0x01080890 (deleting)
	virtual hkBool_s0107_e670 isOk() const;
	virtual int read(void* buf, int nbytes);
	virtual int skip(int nbytes);
	virtual hkBool_s0107_e670 markSupported() const;
	virtual hkResult setMark(int markLimit);
	virtual hkResult rewindToMark();
	virtual hkBool_s0107_e670 seekTellSupported() const;
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;
	virtual hkResult refillBuffer();                              // 11
	void prepareBufferForRefill();                                // 0x01080540

	hkStreamReader* m_stream;                                     // 0x08
	char* m_buf;                                                  // 0x0c
	int m_current;                                                // 0x10
	int m_end;                                                    // 0x14
	int m_bufSize;                                                // 0x18
	int m_markPos;                                                // 0x1c
	int m_markLimit;                                              // 0x20
};
class hkBufferedStreamWriter : public hkStreamWriter
{
public:
	hkBufferedStreamWriter(hkStreamWriter* s, int bufSize);       // 0x01080C30
	hkBufferedStreamWriter(void* buf, int bufSize, hkBool_s0107_e670 nullTerminate); // 0x01080B70
	virtual ~hkBufferedStreamWriter();                            // 0x01080BD0 (+ deleting 0x01080C90)
	virtual hkBool_s0107_e670 isOk() const;
	virtual int write(const void* buf, int nbytes);
	virtual void flush();
	virtual hkBool_s0107_e670 seekTellSupported() const;
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;
	int flushBuffer();                                            // 0x01080950

	hkStreamWriter* m_stream;                                     // 0x08
	char* m_buf;                                                  // 0x0c
	int m_current;                                                // 0x10
	int m_bufSize;                                                // 0x14
	bool m_ownBuf;                                                // 0x18
};
class hkOstream_s0107_e670 : public hkReferencedObject_s0107_e670
{
public:
	hkOstream_s0107_e670(void* buf, int bufSize, hkBool_s0107_e670 nullTerminate);      // 0x0107EF80
	virtual ~hkOstream_s0107_e670();                                         // 0x0107EFD0 (deleting 0x0107F000)
	hkOstream_s0107_e670& operator<<(char c);                                // 0x0107EE10
	hkOstream_s0107_e670& operator<<(const char* s);                         // 0x0107EE30
	hkOstream_s0107_e670& operator<<(int i);                                 // 0x0107EE80 ("%i")
	hkOstream_s0107_e670& operator<<(unsigned int u);                        // 0x0107EED0 ("%u")
	void printf(const char* fmt, ...);                            // 0x0107EF20

	hkStreamWriter* m_writer;                                     // 0x08
};
class hkStreambufFactory_s0107_e670 : public hkReferencedObject_s0107_e670
{
public:
	virtual hkStreamReader* openReader(const char* name) = 0;     // 2
	virtual hkStreamWriter* openWriter(const char* name) = 0;     // 3
	static void* operator new(size_t nbytes)
	{
		void* p = hkMemory_s0107_e670::s_instance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_BASE);
		((hkReferencedObject_s0107_e670*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory_s0107_e670::s_instance->deallocateChunk(p, ((hkReferencedObject_s0107_e670*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_BASE);
	}
};
class hkDefaultStreambufFactory : public hkStreambufFactory_s0107_e670
{
public:
	virtual hkStreamReader* openReader(const char* name);         // 0x0107E670
	virtual hkStreamWriter* openWriter(const char* name);         // 0x0107E820
};
struct hkArrayUtil
{
	static void _reserveMore(void* array, int elemSize);                               // 0x0107F530
	static void _reserveExactly(void* array, int newCapacity, int elemSize);           // 0x0107F4A0
	static void _reduce(void* array, int elemSize, void* inplaceStorage, int inplaceCapacity); // 0x0107F5D0
};
class hkThreadMemory_s0107_e670
{
public:
	static void* operator new(size_t, void* p) { return p; }
	void* allocateChunk(int nbytes, int cl);             // 0x0107DAA0
	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107DB10
	static hkThreadMemory_s0107_e670& getInstance();                // TlsGetValue(g_hkThreadMemoryTls), defined below
	static void replaceInstance(hkThreadMemory_s0107_e670* t);      // 0x0107DBD0
	hkThreadMemory_s0107_e670(hkMemory_s0107_e670* m, int n);                  // 0x0107D7E0
	void removeReference();                              // 0x0107D790
	virtual void releaseCachedMemory();                  // slot 1 (0x0107D740)
};
template <typename T>
class hkArray
{ public:
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	~hkArray()
	{
		m_size = 0;
		if (m_capacityAndFlags >= 0)
			hkThreadMemory_s0107_e670::getInstance().deallocateChunk(m_data, m_capacityAndFlags * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	void pushBack(const T& t)
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = t;
	}
};
class hkMonitorStream
{ public:
	static void init();   // 0x01080480
	static void quit();   // 0x010804C0
};
class hkError : public hkReferencedObject_s0107_e670
{
public:
	virtual void message(int severity, int id, const char* description, const char* file, int line) = 0; // 2
	static hkError* s_instance;   // 0x016E4184
};
struct hkSingletonInitNode
{
	typedef hkReferencedObject_s0107_e670* (*SingletonCreationFunction)();
	SingletonCreationFunction m_func;   // 0x00
	hkSingletonInitNode* m_next;        // 0x04
	void** m_value;                     // 0x08
};
extern hkUint32 g_hkThreadMemoryTls;     // 0x016E4174 hkThreadLocalData<hkThreadMemory_s0107_e670*>
extern hkSingletonInitNode* g_hkSingletonInitList;  // 0x016E429C
struct hkBaseSystem
{
	static hkResult init(hkMemory_s0107_e670* memoryManager, hkThreadMemory_s0107_e670* threadMemory,
	                     void (*errorReportFunction)(const char*, void*), void* errorReportObject); // 0x0107EB20
	static hkResult quit();               // 0x0107ED00
	static void initSingletons();         // 0x0107EA10
	static void quitSingletons();         // 0x0107EC20
};
class hkString
{ public:
	static int strCmp(const char* a, const char* b);   // 0x0107F3D0
	static int strLen(const char* s);                  // 0x0107F420
	static void memCpy(void* dst, const void* src, int n);   // 0x0107F440
	static void memSet(void* dst, int c, int n);       // 0x0107F470
	static void snprintf(char* buf, int n, const char* fmt, ...);  // 0x0107F390 (_vsnprintf)
	static void sprintf(char* buf, const char* fmt, ...);          // 0x0107F3B0 (vsprintf)
};
namespace hkMath
{
	hkBool_s0107_e670 equal(float a, float b, float eps);   // 0x01080E40
}
inline hkThreadMemory_s0107_e670& hkThreadMemory_s0107_e670::getInstance()
{
	return *(hkThreadMemory_s0107_e670*)TlsGetValue(g_hkThreadMemoryTls);
}
struct hkSingletonStreambufFactory { static void replaceInstance(hkStreambufFactory_s0107_e670* f); };   // 0x0107E5F0
class hkDefaultError : public hkError
{
public:
	hkDefaultError(void (*reportFn)(const char*, void*), void* reportObj);                    // 0x005D6AE0
	virtual void message(int severity, int id, const char* description, const char* file, int line);
};
struct hkErrorSingleton { static void replaceInstance(hkError* e); };                          // 0x005D6120
struct hkUnknownBaseObject { virtual void v0(); virtual void v1(); virtual void v2(); };      // object at 0x016E417C
extern hkUnknownBaseObject* g_hkBaseObject;
extern hkReferencedObject_s0107_e670* g_hkStreambufFactoryInstance;                                       // 0x016E42B4
hkStdioStreamReader::~hkStdioStreamReader()
{
	if (m_file)
		fclose(m_file);
}
hkStdioStreamWriter::~hkStdioStreamWriter()
{
	close();
}
typedef int (__stdcall *SymInitializeFn)(void* process, const char* userSearchPath, int invade);
typedef hkUint32 (__stdcall *SymGetOptionsFn)(void);
typedef hkUint32 (__stdcall *SymSetOptionsFn)(hkUint32 options);
struct HK_IMAGEHLP_SYMBOL
{
	hkUint32 SizeOfStruct, Address, Size, Flags, MaxNameLength;
	char Name[2008];
};
struct HK_IMAGEHLP_LINE64
{
	hkUint32 SizeOfStruct;
	void* Key;
	hkUint32 LineNumber;
	const char* FileName;
	hkUint64 Address;
};
typedef int (__stdcall *SymGetSymFromAddrFn)(void* process, hkUint32 addr, hkUint32* displacement, HK_IMAGEHLP_SYMBOL* sym);
typedef int (__stdcall *SymGetLineFromAddr64Fn)(void* process, hkUint64 addr, hkUint32* displacement, HK_IMAGEHLP_LINE64* line);
extern SymGetLineFromAddr64Fn g_SymGetLineFromAddr64;  // 0x016E4188
extern SymGetSymFromAddrFn g_SymGetSymFromAddr;        // 0x016E4198
extern SymSetOptionsFn g_SymSetOptions;                // 0x016E419C
extern SymGetOptionsFn g_SymGetOptions;                // 0x016E41A0
extern SymInitializeFn g_SymInitialize;                // 0x016E41A4
class hkStackTracer : public hkReferencedObject_s0107_e670
{
public:
	typedef void (*printFunc)(const char*, void*);
	hkStackTracer();
	virtual ~hkStackTracer();
	void dumpStackTrace(const hkUint32* addresses, int numAddresses, printFunc output, void* outputObject);
};
// ---- items of slice s0107e670 end

// @ 0x0107e770
int hkStdioStreamReader::read(void* buf, int nbytes)
{
	int r = (int)fread(buf, 1, nbytes, m_file);
	if (r <= 0)
		m_ok = false;
	return r;
}

// @ 0x0107e7a0
hkBool_s0107_e670 hkStdioStreamReader::isOk() const
{
	return m_ok;
}

// @ 0x0107e7b0
hkResult hkStdioStreamReader::seek(int offset, SeekWhence whence)
{
	return fseek(m_file, offset, whence) != 0 ? HK_FAILURE : HK_SUCCESS;
}

// @ 0x0107e7d0
int hkStdioStreamReader::tell() const
{
	return ftell(m_file);
}

// @ 0x0107e890
hkStdioStreamWriter::hkStdioStreamWriter(const char* name)
: m_ownsFile(true)
{
	// The original leaves m_file uninitialised when name is null (quirk kept).
	if (name)
		m_file = fopen(name, "wb");
}

// @ 0x0107e8d0
int hkStdioStreamWriter::write(const void* buf, int nbytes)
{
	if (m_file)
	{
		int w = (int)fwrite(buf, 1, nbytes, m_file);
		if (w <= 0)
			close();
		return w;
	}
	return 0;
}

// @ 0x0107e940
void hkStdioStreamWriter::flush()
{
	if (m_file)
		fflush(m_file);
}

// @ 0x0107e970
hkResult hkStdioStreamWriter::seek(int offset, SeekWhence whence)
{
	return fseek(m_file, offset, whence) != 0 ? HK_FAILURE : HK_SUCCESS;
}

// @ 0x0107e990
int hkStdioStreamWriter::tell() const
{
	return ftell(m_file);
}

// @ 0x0107f3b0
void hkString::sprintf(char* buf, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);
}

// @ 0x0107f420
__declspec(noinline) int hkString::strLen(const char* s)
{
	const char* p = s + 1;
	char c;
	do
	{
		c = *s;
		s = s + 1;
	} while (c != 0);
	return (int)(s - p);
}

// ---- items of slice s0107f4a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C"
{
	__declspec(dllimport) void* __stdcall TlsGetValue(unsigned long index);
	__declspec(dllimport) int __stdcall TlsSetValue(unsigned long index, void* value);
	__declspec(dllimport) int __stdcall TryEnterCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);
	__declspec(dllimport) int __stdcall InitializeCriticalSectionAndSpinCount(void* cs, unsigned long spin);
	__declspec(dllimport) unsigned long __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) void* __stdcall GetCurrentProcess(void);
	__declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
	__declspec(dllimport) int __stdcall FreeLibrary(void* module);
	__declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
}
    extern unsigned int g_hkThreadMemoryTls; // 0x016e4174
#define HK_BREAKPOINT() __debugbreak()
typedef int16_t hkInt16;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;
typedef uint32_t hkUint32;
typedef uint64_t hkUint64;
typedef size_t hkUlong;   // pointer-sized unsigned (address arithmetic)
class hkOstream_s0107_e670;
class hkStatisticsCollector;
extern hkUint32 g_hkThreadMemoryTls;     // 0x016E4174 hkThreadLocalData<hkThreadMemory_s0107_e670*>
extern hkUint32 g_hkMonitorTlsCurrent;   // 0x016E42A4
extern hkUint32 g_hkMonitorTlsEnd;       // 0x016E42A8
extern hkUint32 g_hkMonitorTlsEnabled;   // 0x016E42B8
hkUint64 hkGetCurrentThreadId();   // 0x01080CC0 (GetCurrentThreadId zero-extended)
class hkCriticalSection_s0107_e670
{
public:
	void enter();     // 0x0107F820
	void leave();     // inlined in the pool allocator
	char m_cs[24];    // CRITICAL_SECTION, 0x00
	hkUint64 m_owner; // 0x18 (thread id while locked, -1 otherwise)
};
class hkPoolMemory : public hkMemory_s0107_e670
{
public:
	hkPoolMemory();                                                  // 0x0107F910
	~hkPoolMemory();                                                 // 0x0107F6C0
	virtual void* allocate(int nbytes, int cl);                      // 0x0107F720
	virtual void deallocate(void* p);                                // 0x0107F750
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);// 0x0107F780
	virtual void alignedDeallocate(void* p);                         // 0x0107F7D0
	virtual void* allocateChunk(int nbytes, int cl);                 // 0x0107FBE0
	virtual void deallocateChunk(void* p, int nbytes, int cl);       // 0x0107FF60
	virtual void* allocateChunkByRow(int row, int cl);               // 0x0107FDD0
	virtual void deallocateChunkByRow(void* p, int row, int cl);     // 0x0107FFF0
	virtual void printStatistics(hkOstream_s0107_e670* o);                      // 0x0107F700
	virtual int getAllocatedSize(int nbytes);                        // 0x0107F670
	virtual void getStatSynopsis(hkMemoryStatistics* s);             // 0x0107F800

	void* _allocateFromRow(int row);

	hkUint8* m_pageList;            // 0x2c singly linked list of 0x2040-byte pages
	hkUint8* m_pageStart;           // 0x30
	hkUint8* m_pageEnd;             // 0x34
	hkUint8* m_pageCur;             // 0x38
	int m_pad3c;                    // 0x3c
	hkCriticalSection_s0107_e670 m_lock;       // 0x40
	void* m_freeLists[17];          // 0x60
	int m_rowSizes[17];             // 0xa4
	char m_sizeToRow[0x201];        // 0xe8
	char m_pad2e9[3];
	int m_bigSizeToRow[8];          // 0x2ec
	int m_rowCounts[17];            // 0x30c
};
inline void hkCriticalSection_s0107_e670::leave()
{
	m_owner = (hkUint64)-1;   // two dword stores of -1 in the binary
	LeaveCriticalSection(m_cs);
}
#define HK_RDTSC32() ((hkUint32)__rdtsc())
extern void (__cdecl* g_alignedFree_15b9a38)(void*);
#define _aligned_free(p) g_alignedFree_15b9a38(p)
struct hkArrayRaw
{
	void* m_data;
	int m_size;
	int m_capacityAndFlags;
};
static inline int hkPoolRowForSize(int n)
{
	int row;
	if (n < 9) row = 1;
	else if (n < 0x11) row = 2;
	else if (n < 0x21) row = 3;
	else if (n < 0x31) row = 4;
	else if (n < 0x41) row = 5;
	else if (n < 0x61) row = 6;
	else if (n < 0x81) row = 7;
	else if (n < 0xa1) row = 8;
	else if (n < 0xc1) row = 9;
	else if (n < 0x101) row = 10;
	else if (n < 0x141) row = 11;
	else if (n < 0x201) row = 12;
	else if (n < 0x401) row = 13;
	else if (n < 0x801) row = 14;
	else if (n < 0x1001) row = 15;
	else
	{
		if (0x2000 < n)
			HK_BREAKPOINT();
		row = 16;
	}
	return row;
}
void* hkPoolMemory::_allocateFromRow(int row)
{
	m_rowCounts[row] = m_rowCounts[row] + 1;
	m_stats.m_inUseBytes = m_stats.m_inUseBytes + m_rowSizes[row];
	void** head = (void**)m_freeLists[row];
	void* result;
	if (head == 0)
	{
		int sz = m_rowSizes[row];
		if (row < 0xd)
		{
			// Small rows are carved from the shared bump page.
			if ((hkUlong)m_pageEnd < (hkUlong)(m_pageCur + sz))
			{
				hkUint8* page = (hkUint8*)_aligned_malloc(0x2040, 0x40);
				*(hkUint8**)page = m_pageList;
				m_pageList = page;
				m_pageStart = page + 0x40;
				m_pageCur = page + 0x40;
				m_pageEnd = page + 0x2040;
				m_stats.m_numPages = m_stats.m_numPages + 1;
			}
			result = m_pageCur;
			hkUint8* p = m_pageCur + sz;
			m_pageCur = p;
			int saved = m_rowCounts[row];
			int off = sz;
			while (off < 0x100 && (hkUlong)(p + sz) < (hkUlong)m_pageEnd)
			{
				m_rowCounts[row] = m_rowCounts[row] - 1;
				*(void**)p = m_freeLists[row];
				m_freeLists[row] = p;
				p = m_pageCur + sz;
				off += sz;
				m_pageCur = p;
			}
			m_rowCounts[row] = saved;
		}
		else
		{
			// Large rows get a page of their own.
			hkUint8* page = (hkUint8*)_aligned_malloc(0x2040, 0x40);
			if (m_pageList == 0)
			{
				*(hkUint8**)page = 0;
				m_pageList = page;
			}
			else
			{
				*(hkUint8**)page = *(hkUint8**)m_pageList;
				*(hkUint8**)m_pageList = page;
			}
			m_stats.m_numPages = m_stats.m_numPages + 1;
			int saved = m_rowCounts[row];
			result = page + 0x40;
			hkUint8* p = (hkUint8*)result + sz;
			if (sz < 0x2000)
			{
				int off = (int)(p - (hkUint8*)result);
				do
				{
					m_rowCounts[row] = m_rowCounts[row] - 1;
					*(void**)p = m_freeLists[row];
					m_freeLists[row] = p;
					off += sz;
					p += sz;
				} while (off < 0x2000);
			}
			m_rowCounts[row] = saved;
		}
	}
	else
	{
		m_freeLists[row] = *head;
		result = head;
	}
	return result;
}
// ---- items of slice s0107f4a0 end

// @ 0x0107f670
int hkPoolMemory::getAllocatedSize(int nbytes)
{
	int row;
	if (nbytes <= 0x2000)
	{
		if (nbytes <= 0x200)
			row = m_sizeToRow[nbytes];
		else
			row = m_bigSizeToRow[(nbytes - 1) >> 10];
		return m_rowSizes[row];
	}
	return hkMemory_s0107_e670::getAllocatedSize(nbytes);
}

// @ 0x0107f700
void hkPoolMemory::printStatistics(hkOstream_s0107_e670* o)
{
	o->printf("Statistics are disabled, please enable them in hkbase/config/hkConfigMemoryStats.h\n");
}

// @ 0x0107f800
void hkPoolMemory::getStatSynopsis(hkMemoryStatistics* s)
{
	*s = m_stats;
}
