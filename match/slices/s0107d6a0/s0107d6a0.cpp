// Decompiled source for bfs3 slice 42: Havok hkThreadMemory / hkMemory /
// hkPointerMapBase template instantiations (+ a cWalkAroundInputStrategy::Shutdown).
#include "types.h"

#define VFN(p, slot) (((void**)*(void**)p)[(slot)/4])

class Dummy;
enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };

void EA_Messaging_RemoveHandler(int, int, int, int, int);
void FUN_00b1b830(void*);
void FUN_00e4b990(void*);

// ---- CRT / TLS ----------------------------------------------------------
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
extern "C" __declspec(dllimport) int   __stdcall TlsSetValue(unsigned long, void*);
void* hkMemSet(void* dst, int c, int n);          // 0x0107f470 hkString::memSet

extern unsigned long g_tlsThreadMemory;           // 0x016e4174
extern unsigned long g_tlsThreadMemory2;          // unused placeholder

// ---- hkMemory -----------------------------------------------------------
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

extern hkMemory* g_hkMemory;      // 0x016e4178

inline void* hkAlloc(int size, int cls)
{
    return ((void*(__thiscall*)(void*, int, int))VFN(g_hkMemory, 0x10))(g_hkMemory, size, cls);
}
inline void hkFree(void* p, int size, int cls)
{
    ((void(__thiscall*)(void*, void*, int, int))VFN(g_hkMemory, 0x14))(g_hkMemory, p, size, cls);
}

// ---- hkPointerMapBase ---------------------------------------------------
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

// @ 0x0107ddd0 (K) / (no _K clear in range)
template<class KEY> void hkPointerMapBase<KEY>::clear()
{
    hkMemSet(mTable, 0, (mMask + 1) * (int)sizeof(KEY) * 2);
    mCount = 0;
}

// @ 0x0107de00 (K) / 0x0107e0f0 (_K)
template<class KEY> hkPointerMapBase<KEY>::hkPointerMapBase()
{
    int bytes = 0x10 * (int)sizeof(KEY) * 2;
    mTable = (KEY*)hkAlloc(bytes, 0x14);
    hkMemSet(mTable, 0, bytes);
    mCount = 0;
    mMask = 0x0f;
    clear();
}

// @ 0x0107de50 (K) / 0x0107e140 (_K)
template<class KEY> hkPointerMapBase<KEY>::~hkPointerMapBase()
{
    hkFree(mTable, (mMask + 1) * (int)sizeof(KEY) * 2, 0x14);
}

// @ 0x0107de70 (K) / 0x0107e160 (_K)
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

// @ 0x0107def0 (K) / 0x0107e240 (_K)
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

template<class KEY> inline int hkPointerMapBase<KEY>::findIndex(KEY k) const
{
    for (int i = (int)(((k >> 4) * (KEY)0x9e3779b1ul) & (KEY)mMask); mTable[i] != 0; i = (i + 1) & mMask)
        if (mTable[i] == k)
            return i;
    return mMask + 1;
}

// @ 0x0107df30 (K) / (no _K get in range)
template<class KEY> hkResult hkPointerMapBase<KEY>::get(KEY k, KEY* out) const
{
    int i = findIndex(k);
    if (i <= mMask) {
        *out = mTable[mMask + 1 + i];
        return HK_SUCCESS;
    }
    return HK_FAILURE;
}

// @ 0x0107df90 (K) / 0x0107e2d0 (_K)
template<class KEY> void hkPointerMapBase<KEY>::remove(Dummy* d)
{
    int i = (int)d;
    --mCount;
    mTable[i] = 0;
    int mask = mMask;
    for (int j = (i + 1) & mask; mTable[j] != 0; j = (j + 1) & mask) {
        KEY h = (KEY)((mTable[j] >> 4) * (KEY)0x9e3779b1ul);
        int k = (int)(h & (KEY)mask);
        bool move;
        if (j > i)
            move = (k <= i || k > j);
        else
            move = (k <= i && k > j);
        if (move) {
            mTable[i] = mTable[j];
            mTable[mask + 1 + i] = mTable[mask + 1 + j];
            mTable[j] = 0;
            i = j;
        }
    }
}

// @ 0x0107e050 (K) / 0x0107e4a0 (_K)
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

// @ 0x0107e540 (K)
template<class KEY> KEY hkPointerMapBase<KEY>::getWithDefault(KEY k, KEY def) const
{
    if (get(k, &k) != HK_SUCCESS)
        k = def;
    return k;
}

// @ 0x0107e560 (K)
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

// force both instantiations
template class hkPointerMapBase<unsigned long>;
template class hkPointerMapBase<unsigned __int64>;

// @ 0x0107e5b0 / 0x0107e5d0: grow-to helper (tail-calls resizeTable).
void FUN_0107e5b0(hkPointerMapBase<unsigned long>* self, int n)
{
    int s = 4;
    if (3 * n > 4) {
        do { s += s; } while (s < 3 * n);
    }
    self->resizeTable(s);
}
void FUN_0107e5d0(hkPointerMapBase<unsigned __int64>* self, int n)
{
    int s = 4;
    if (3 * n > 4) {
        do { s += s; } while (s < 3 * n);
    }
    self->resizeTable(s);
}

// ---- hkSingleton --------------------------------------------------------
template<class T> class hkSingleton {
public:
    static T* ms_instance;
    static void replaceInstance(T* p);
};
template<class T> T* hkSingleton<T>::ms_instance = 0;

// @ 0x0107e5f0
template<class T> void hkSingleton<T>::replaceInstance(T* p)
{
    T* old = ms_instance;
    if (old == 0) {
        ms_instance = p;
        return;
    }
    if (*(short*)((char*)old + 4) != 0) {
        short* rc = (short*)((char*)old + 6);
        --*rc;
        if (*rc == 0)
            ((void(__thiscall*)(void*, int))VFN(old, 0))(old, 1);
        ms_instance = p;
        return;
    }
    ms_instance = p;
}

// @ 0x0107e640
void FUN_0107e640()
{
    unsigned char* p = (unsigned char*)hkAlloc(8, 0x15);
    *(unsigned short*)(p + 4) = 8;
    *(unsigned short*)(p + 6) = 1;
    *(void**)p = (void*)0x149c894;
}

// ---- hkMemory methods ---------------------------------------------------
int hkMemory::getAllocatedSize(int size)   // 0x0107dcf0
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

// ---- hkThreadMemory -----------------------------------------------------
class hkThreadMemory {
public:
    void* mpVtbl;          // +0x00
    char pad04[0x0c];      // +0x04..+0x0f pad
    hkMemory* mMemory;     // +0x10
    int mnRefCount;        // +0x14
    char pad18[8];         // +0x18..+0x1f
    int mStackBase;        // +0x20
    int mStackAlloc;       // +0x24
    int mStackCurrent;     // +0x28
    int mStackEnd;         // +0x2c
    int mStackSize;        // +0x30
    int mMaxRows;          // +0x34
    int mRows[0x11];       // +0x38..+0x7b (free list heads)
    int mRowCounts[0x11];  // +0x7c..+0xbf
    char padC0[0x44];      // +0xc0..+0x103 (per-thread class sizes)
    signed char mClassForSize[0x204]; // +0x104..+0x307
    int mExtra[0x40];                  // +0x308..

    void releaseCachedMemory();          // 0x0107d740
    void removeReference();              // 0x0107d790
    void setStackArea(void* p, int n);   // 0x0107d7a0
    void* allocateChunk(int size, int cls);     // 0x0107daa0
    void deallocateChunk(void* p, int size, int cls); // 0x0107db10
    void onStackUnderflow(void* p);      // 0x0107db90
    static void replaceInstance(hkThreadMemory* p);   // 0x0107dbd0
    void* onStackOverflow(int size);     // 0x0107dc10
};

// @ 0x0107d740
void hkThreadMemory::releaseCachedMemory()
{
    for (int cls = 0x10; cls >= 0; --cls) {
        int* head = &mRows[cls];
        while (*head != 0) {
            int* node = (int*)*head;
            *head = *node;
            ((void(__thiscall*)(void*, int*, int, int))VFN(mMemory, 0x1c))
                (mMemory, node, cls, 1);
        }
        *head = 0;
        mRowCounts[cls] = 0;
    }
}

// @ 0x0107d790
void hkThreadMemory::removeReference()
{
    if (--mnRefCount == 0)
        ((void(__thiscall*)(void*, int))VFN(this, 8))(this, 1);
}

// @ 0x0107d7a0
void hkThreadMemory::setStackArea(void* p, int n)
{
    int a = (int)p;
    int rem = a & 0xf;
    mStackCurrent = -1;
    mStackSize = n;
    if (rem != 0) {
        mStackBase = (a - rem) + 0x10;
        mStackEnd = (a - rem) + n;
    } else {
        mStackBase = a;
        mStackEnd = a + n;
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

// @ 0x0107dc90 (hkThreadMemory-like vtable init, separate small object)
void FUN_0107dc90(void* self)
{
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
}

// @ 0x0107d7e0: hkThreadMemory constructor (size->class table build)
void FUN_0107d7e0(void* self, void* memory, int stackSize)
{
    char* p = (char*)self;
    *(void**)p = (void*)0x149c848;
    *(int*)(p + 0x14) = 1;
    *(int*)(p + 0x20) = 0;
    *(int*)(p + 0x24) = 0;
    *(int*)(p + 0x28) = -1;
    *(int*)(p + 0x2c) = 0;
    *(void**)(p + 0x10) = memory;
    (void)stackSize;
    ((void(__thiscall*)(void*))VFN(memory, 0x20))(memory);
    for (int i = 0; i < 0x44; i += 4)
        *(int*)(p + 0xbc - i) = 0;   // rough clear of the tables
    for (int s = 0; s <= 0x200; ++s) {
        int cls;
        if (s <= 8) cls = 1;
        else if (s <= 0x10) cls = 2;
        else if (s <= 0x20) cls = 3;
        else if (s <= 0x30) cls = 4;
        else if (s <= 0x40) cls = 5;
        else if (s <= 0x60) cls = 6;
        else if (s <= 0x80) cls = 7;
        else if (s <= 0xa0) cls = 8;
        else if (s <= 0xc0) cls = 9;
        else if (s <= 0x100) cls = 10;
        else if (s <= 0x140) cls = 11;
        else if (s <= 0x200) cls = 12;
        else cls = -1;
        *(signed char*)(p + 0x104 + s) = (signed char)cls;
        *(int*)(p + 0xc0 + cls * 4) = s;
    }
}

// @ 0x0107d6a0  SP::cWalkAroundInputStrategy::Shutdown
void FUN_0107d6a0(void* self)
{
    char* p = (char*)self;
    int h = *(int*)(p + 0x108);
    if (h != 0) {
        int a = *(int*)(p + 0x118);
        int b = *(int*)(p + 0x114);
        int c = *(int*)(p + 0x110);
        int d = *(int*)(p + 0x10c);
        *(int*)(p + 0x108) = 0;
        EA_Messaging_RemoveHandler(h, d, c, b, a);
    }
    FUN_00b1b830(*(void**)(p + 0x10));
    *(void**)(p + 0x0c) = p + 8;
    *(int*)(p + 0x10) = 0;
    *(char*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(void**)(p + 0x08) = p + 8;
    FUN_00e4b990(*(void**)(p + 0x2c));
    *(void**)(p + 0x28) = p + 0x24;
    *(int*)(p + 0x2c) = 0;
    *(char*)(p + 0x30) = 0;
    *(int*)(p + 0x34) = 0;
    *(void**)(p + 0x24) = p + 0x24;
    void* obj = *(void**)(p + 0x11c);
    if (obj != 0) {
        *(void**)(p + 0x11c) = 0;
        ((void(__thiscall*)(void*, int))VFN(obj, 4))(obj, 1);
    }
}
