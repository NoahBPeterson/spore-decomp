// src/game/Havok/_at_01070000.cpp -- migrated from slice(s) s0107d6a0 by tools/migrate/rewrite.py
// Object file: Havok/_at_01070000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
extern "C" __int64 __stdcall _allmul(int lo, int hi, int mlo, int mhi); // lib_crt::allmul
extern "C" void __cdecl __debugbreak(void);
extern unsigned long g_tlsThreadMemory;           // 0x016e4174
extern void* g_hkStreambufFactorySingleton;   // 0x016e42b4
#pragma intrinsic(__debugbreak)

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
inline void* hkAlloc(int size, int cls)
{
    return ((void*(__thiscall*)(void*, int, int))VFN(g_hkMemory, 0x10))(g_hkMemory, size, cls);
}
inline void hkFree(void* p, int size, int cls)
{
    ((void(__thiscall*)(void*, void*, int, int))VFN(g_hkMemory, 0x14))(g_hkMemory, p, size, cls);
}
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
};
template<class KEY> inline int hkPointerMapBase<KEY>::findIndex(KEY k) const
{
    for (int i = (int)(((k >> 4) * (KEY)0x9e3779b1ul) & (KEY)mMask); mTable[i] != 0; i = (i + 1) & mMask)
        if (mTable[i] == k)
            return i;
    return mMask + 1;
}
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
    if (p != 0)
        ++p->mnRefCount;
    hkThreadMemory* old = (hkThreadMemory*)TlsGetValue(g_tlsThreadMemory);
    if (old != 0) {
        if (--old->mnRefCount == 0)
            ((void(__thiscall*)(void*, int))VFN(old, 8))(old, 1);
    }
    TlsSetValue(g_tlsThreadMemory, p);
}

// @ 0x0107dc10
void* hkThreadMemory::onStackOverflow(int size)
{
    int n = size + 0x400;
    if (n < 0x1000)
        n = 0x1000;
    hkThreadMemory* cur = (hkThreadMemory*)TlsGetValue(g_tlsThreadMemory);
    int* hdr = (int*)cur->allocateChunk(n + 0x10, 0x14);
    hdr[0] = mStackBase;
    hdr[1] = mStackAlloc;
    hdr[2] = mStackCurrent;
    hdr[3] = mStackEnd;
    int* data = hdr + 4;
    mStackBase = (int)data + size;
    mStackCurrent = (int)data;
    mStackEnd = (int)data + n;
    mStackAlloc = (int)hdr;
    return data;
}

// @ 0x0107dc90
void* hkSmallObj::FUN_0107dc90()
{
    void* self = this;
    char* p = (char*)self;
    *(void**)p = (void*)0x149c85c;
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

// @ 0x0107de50
template<class KEY> hkPointerMapBase<KEY>::~hkPointerMapBase()
{
    hkFree(mTable, (mMask + 1) * (int)sizeof(KEY) * 2, 0x14);
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
    if (idx > mMask)
        return HK_FAILURE;
    remove((Dummy*)idx);
    return HK_SUCCESS;
}

// @ 0x0107e5b0
void FUN_0107e5b0(hkPointerMapBase<unsigned long>* self, int n)
{
    int s = 4;
    if (3 * n > 4) {
        do { s += s; } while (s < 3 * n);
    }
    self->resizeTable(s);
}

// @ 0x0107e5d0
void FUN_0107e5d0(hkPointerMapBase<unsigned __int64>* self, int n)
{
    int s = 4;
    if (3 * n > 4) {
        do { s += s; } while (s < 3 * n);
    }
    self->resizeTable(s);
}

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

// @ 0x0107e640
void FUN_0107e640()
{
    unsigned char* p = (unsigned char*)hkAlloc(8, 0x15);
    *(unsigned int*)(p + 4) = 0x00010008u;
    *(void**)p = (void*)0x149c894;
}
