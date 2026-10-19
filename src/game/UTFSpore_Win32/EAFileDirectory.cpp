// src/game/UTFSpore_Win32/EAFileDirectory.cpp -- migrated from slice(s) s0092e3d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFileDirectory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/DateTime/DateTime.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern wchar_t gEmptyStr;        // 0x01667bac: shared empty-string storage of eastl::basic_string<wchar_t>
extern wchar_t gEmptyStrEnd;     // 0x01667bae: one past it
#include <time.h>
#include <string.h>
#include <new>
#include <windows.h>

// ---- items of slice s0092e3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct EntryFindData {
    wchar_t  mName[260];        // +0x000
    char     mIsDirectory;      // +0x208
    char     mOwned;            // +0x209
    wchar_t  mBaseDir[260];     // +0x20a
    wchar_t  mPattern[260];     // +0x412
    char     pad[2];
    HANDLE   mHandle;           // +0x61c
    char     pad2[0x40];
    int64_t  mCreateTime;       // +0x660
    int64_t  mAccessTime;       // +0x668
    int64_t  mWriteTime;        // +0x670
    EntryFindData() { memset(this, 0, sizeof(*this)); }
};
void* operator new(unsigned, const char*, int, int, int, int);
void  operator delete[](void*);   // 0x00f47380
extern wchar_t gEmptyStr;        // 0x01667bac: shared empty-string storage of eastl::basic_string<wchar_t>
extern wchar_t gEmptyStrEnd;     // 0x01667bae: one past it
struct WString {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAlloc;       // +0x0c
    void AllocateSelf(unsigned n);                              // 0x00429760
    void assign(const wchar_t* b, const wchar_t* e);            // 0x00423650
    void append(const wchar_t* s);                              // 0x005c3d90
    void insert(wchar_t* p, unsigned n, wchar_t c);
    WString() : mpBegin(&gEmptyStr), mpEnd(&gEmptyStr), mpCapacity(&gEmptyStrEnd) {}
    WString(const WString& o) {
        mpBegin = 0;
        mpEnd = 0;
        mpCapacity = 0;
        const wchar_t* src = o.mpBegin;
        int n = (int)(o.mpEnd - src);
        AllocateSelf(n + 1);
        wchar_t* dst = mpBegin;
        memcpy(dst, src, n * 2);
        mpEnd = dst + n;
        *mpEnd = 0;
    }
    void DeallocateSelf() {
        wchar_t* b = mpBegin;
        if ((int)((int)mpCapacity - (int)b & 0xfffffffeU) > 2 && b)
            operator delete[](b);
    }
};
wchar_t* CharStringUninitializedFillN(wchar_t* p, unsigned n, wchar_t c);   // 0x00571e20
void     fill_n(wchar_t* p, unsigned n, wchar_t c);                         // 0x00674170
void* operator new(unsigned size, const char* name, int flags, int dbgFlags, const char* file, int line);
struct ICoreAllocator {
    virtual void  v0();
    virtual void  v1();
    virtual void* Alloc(unsigned size, int flags, const char* name);
    virtual void  Free(void* p, unsigned size);
};
static inline wchar_t* CharStringUninitializedCopy(const wchar_t* first, const wchar_t* last, wchar_t* dest) {
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}
static inline wchar_t* CharTypeMoveBackward(const wchar_t* first, const wchar_t* last, wchar_t* destEnd) {
    unsigned n = (unsigned)(last - first);
    return (wchar_t*)memmove(destEnd - n, first, n * 2);
}
struct Entry {
    int      mType;       // +0x00  1 = directory, 2 = file
    WString  mName;       // +0x04
    int      pad;         // +0x14
    union {
        uint32_t mTimes[6];   // +0x18  create / write / access, 64-bit seconds each
        int64_t  mTimes64[3];
    };
    Entry() : mType(0) {}
    Entry(const Entry& o);
    ~Entry() { mName.DeallocateSelf(); }
};
struct DequeIter {
    Entry*  mpCurrent;       // +0
    Entry*  mpBegin;         // +4
    Entry*  mpEnd;           // +8
    Entry** mpCurrentArrayPtr;  // +0xc
    DequeIter& operator+=(int n);
    void SetSubarray(Entry** pArrayPtr) {
        mpCurrentArrayPtr = pArrayPtr;
        mpBegin = *pArrayPtr;
        mpEnd = mpBegin + 4;
    }
};
struct Deque {
    Entry**   mpPtrArray;      // +0x00
    unsigned  mnPtrArraySize;  // +0x04
    DequeIter mItBegin;        // +0x08
    DequeIter mItEnd;          // +0x18
    ICoreAllocator* mpAllocator;  // +0x28
    const char* mpName;           // +0x2c

    Entry& back();
    void push_back();
    void DoPushBack(const Entry& value);
    void DoReallocPtrArray(unsigned nAdditional, int side);
};
static inline const unsigned& max_alt(const unsigned& a, const unsigned& b) { return a < b ? b : a; }
    void operator delete[](void*); // 0x00f47380
// ---- items of slice s0092e3d0 end

// @ 0x0092e9b0
void EntryFindFinish(EntryFindData* data)
{
    if (data) {
        HANDLE h = data->mHandle;
        if (h && h != INVALID_HANDLE_VALUE)
            FindClose(h);
        if (data->mOwned)
            operator delete[](data); // 0x00f47380
    }
}

// @ 0x0092e9f0
__declspec(noinline) DequeIter& DequeIter::operator+=(int n)
{
    int offset = n + (int)(mpCurrent - mpBegin);
    if ((unsigned)offset < 4) {
        mpCurrent += n;
    } else {
        int sub = (offset + 0x1000000) / 4 - 0x400000;
        SetSubarray(mpCurrentArrayPtr + sub);
        mpCurrent = mpBegin + (offset - sub * 4);
    }
    return *this;
}

// @ 0x0092ea70
__declspec(noinline) Entry& Deque::back()
{
    Entry* c = mItEnd.mpCurrent;
    Entry* b = mItEnd.mpBegin;
    Entry** arr = mItEnd.mpCurrentArrayPtr;
    if (c == b)
        return (*(arr - 1))[3];
    return c[-1];
}

// @ 0x0092ea90
__declspec(noinline) void WString::insert(wchar_t* p, unsigned n, wchar_t c)
{
    if (n) {
        if (n + 1 <= (unsigned)(mpCapacity - mpEnd)) {
            const unsigned nElementsAfter = (unsigned)(mpEnd - p);
            wchar_t* pOldEnd = mpEnd;
            if (n <= nElementsAfter) {
                CharStringUninitializedCopy(pOldEnd - n + 1, pOldEnd + 1, pOldEnd + 1);
                mpEnd += n;
                CharTypeMoveBackward(p, pOldEnd - n + 1, pOldEnd + 1);
                fill_n(p, n, c);
            } else {
                CharStringUninitializedFillN(mpEnd + 1, n - nElementsAfter - 1, c);
                mpEnd += n - nElementsAfter;
                CharStringUninitializedCopy(p, pOldEnd + 1, mpEnd);
                mpEnd += nElementsAfter;
                fill_n(p, nElementsAfter + 1, c);
            }
        } else {
            const unsigned nOldSize = (unsigned)(mpEnd - mpBegin);
            const unsigned nOldCap = (unsigned)((mpCapacity - mpBegin) - 1);
            unsigned grown = nOldCap > 8 ? nOldCap * 2 : 8;
            unsigned want = nOldSize + n;
            const unsigned nLength = (want > grown ? want : grown) + 1;
            wchar_t* pNewBegin = (wchar_t*)operator new(nLength * 2, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            wchar_t* pNewEnd = pNewBegin;
            pNewEnd = CharStringUninitializedCopy(mpBegin, p, pNewEnd);
            wchar_t* qEnd = pNewEnd + n;
            for (wchar_t* q = pNewEnd; q < qEnd; ++q)
                *q = c;
            pNewEnd = CharStringUninitializedCopy(p, mpEnd, qEnd);
            *pNewEnd = 0;
            DeallocateSelf();
            mpBegin = pNewBegin;
            mpEnd = pNewEnd;
            mpCapacity = pNewBegin + nLength;
        }
    }
}

// @ 0x0092ec60
__declspec(noinline) void Deque::DoReallocPtrArray(unsigned nAdditional, int side)
{
    int nUsedBytes = (int)((char*)mItEnd.mpCurrentArrayPtr - (char*)mItBegin.mpCurrentArrayPtr);
    int nUsed = (nUsedBytes >> 2) + 1;
    int nTotal = nUsed + nAdditional;
    Entry** pNewBegin;
    if ((unsigned)(nTotal * 2) >= mnPtrArraySize) {
        unsigned nNewSize = mnPtrArraySize + max_alt(mnPtrArraySize, nAdditional) + 2;
        Entry** pNewArray = (Entry**)mpAllocator->Alloc(nNewSize * 4, 0, mpName);
        Entry** src = mItBegin.mpCurrentArrayPtr;
        pNewBegin = pNewArray + ((src - mpPtrArray) + (side == 0 ? nAdditional : 0));
        if (mpPtrArray)
            memcpy(pNewBegin, src, (int)((char*)mItEnd.mpCurrentArrayPtr - (char*)src) + 4);
        if (mpPtrArray)
            mpAllocator->Free(mpPtrArray, mnPtrArraySize * 4);
        mpPtrArray = pNewArray;
        mnPtrArraySize = nNewSize;
    } else {
        pNewBegin = mpPtrArray + ((mnPtrArraySize - nTotal) / 2 + (side == 0 ? nAdditional : 0));
        if (pNewBegin < mItBegin.mpCurrentArrayPtr)
            memcpy(pNewBegin, mItBegin.mpCurrentArrayPtr, nUsedBytes + 4);
        else
            memmove(pNewBegin + (nUsed - ((nUsedBytes + 4) >> 2)), mItBegin.mpCurrentArrayPtr, nUsedBytes + 4);
    }
    mItBegin.SetSubarray(pNewBegin);
    mItEnd.SetSubarray(pNewBegin + nUsed - 1);
}

// @ 0x0092ed90
__declspec(noinline) Entry::Entry(const Entry& o)
: mType(o.mType), mName(o.mName) {
    mTimes[0] = o.mTimes[0];
    mTimes[1] = o.mTimes[1];
    mTimes[2] = o.mTimes[2];
    mTimes[3] = o.mTimes[3];
    mTimes[4] = o.mTimes[4];
    mTimes[5] = o.mTimes[5];
}

// @ 0x0092ee20
__declspec(noinline) void Deque::DoPushBack(const Entry& value)
{
    Entry valueSaved(value);
    if ((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1 >= (int)mnPtrArraySize)
        DoReallocPtrArray(1, 1);
    mItEnd.mpCurrentArrayPtr[1] = (Entry*)mpAllocator->Alloc(0xc0, 0, mpName);
    if (mItEnd.mpCurrent)
        new (mItEnd.mpCurrent) Entry(valueSaved);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
    mItEnd.mpCurrent = mItEnd.mpBegin;
}
