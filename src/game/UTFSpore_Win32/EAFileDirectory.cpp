// src/game/UTFSpore_Win32/EAFileDirectory.cpp -- migrated from slice(s) s0092f220, s0092e3d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAFileDirectory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/DateTime/DateTime.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern "C" int64_t __stdcall _alldiv(int, int, int, int);
extern wchar_t gEmptyStr;        // 0x01667bac: shared empty-string storage of eastl::basic_string<wchar_t>
extern wchar_t gEmptyStrEnd;     // 0x01667bae: one past it
extern const wchar_t kDot[];     // 0x01436614  L"."
extern const wchar_t kDotDot[];  // 0x0143660c  L".."
#include <time.h>
#include <string.h>
#include <new>
#include <windows.h>

// ---- items of slice s0092e3d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int64_t __stdcall _alldiv(int, int, int, int);
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
extern const wchar_t kDot[];     // 0x01436614  L"."
extern const wchar_t kDotDot[];  // 0x0143660c  L".."
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
static __forceinline unsigned StrLen16(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (unsigned)(p - s);
}
    void operator delete[](void*); // 0x00f47380
// ---- items of slice s0092e3d0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
EntryFindData* EntryFindFirst(const wchar_t* dir, const wchar_t* pattern, EntryFindData* data, bool wantTimes);  // 0x0092e730 (stays in the slice: not this object's)
EntryFindData* EntryFindNext(EntryFindData* data, bool wantTimes);  // 0x0092e8e0 (stays in the slice: not this object's)

// ---- items of slice s0092f220 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void FUN_004228e0(void*, unsigned);
extern "C" void FUN_005f8840(void*);
extern "C" void FUN_005f96c0(void*);
extern "C" void FUN_0092e9f0(void* self, int);
extern "C" void WString_Assign(void* self, const unsigned short*, const unsigned short*); // 0x00423650
extern "C" void WString_insert(void*, const unsigned short*, const unsigned short*);       // 0x005f7da0
extern "C" void WString_append(void*, const unsigned short*, int, unsigned short);         // 0x0092ea90
extern "C" int  EA_Text_WildcardMatch(const unsigned short*, const unsigned short*, int);
extern "C" void* Deque_Push(void*);                                                       // 0x0092eec0
extern "C" int* Deque_Last(void*);                                                        // 0x0092ea70
int  ConcatenatePathComponents(unsigned short* dst, const unsigned short* c1, const unsigned short* c2);
namespace EA {
namespace IO {
class DirectoryIterator { public:
    uint32_t mnListSize;            // +0
    int      mnRecursionIndex;      // +4
    unsigned short* mpBaseDirectory;// +8
    uint32_t mBaseDirectoryLength;  // +0xc

    uint32_t ReadRecursive(const unsigned short* pDir, void* pList, const unsigned short* pFilter,
                           uint32_t flags, char c6, char c7, uint32_t maxDepth, void* p9);
    int FillEntries(const unsigned short*, void*, int, int, int, void*);
};  // namespace EA::IO
}
}
using EA::IO::DirectoryIterator;
// ---- items of slice s0092f220 end

// @ 0x0092e680
__declspec(noinline) static int64_t GetFileTimeEpoch()
{
    SYSTEMTIME st;
    FILETIME ft;
    memset(&st, 0, sizeof(st));
    st.wYear = 1970;
    st.wMonth = 1;
    st.wDayOfWeek = 0;
    st.wDay = 1;
    SystemTimeToFileTime(&st, &ft);
    return _alldiv(ft.dwLowDateTime, ft.dwHighDateTime, 10000000, 0);
}

// @ 0x0092e6e0
static int64_t FileTimeToUnix(const FILETIME* ft)
{
    DWORD lo = ft->dwLowDateTime;
    DWORD hi = ft->dwHighDateTime;
    int64_t secs = _alldiv(lo, hi, 10000000, 0);
    static int64_t sEpoch = GetFileTimeEpoch();
    return secs - sEpoch;
}

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

// @ 0x0092eec0
__declspec(noinline) void Deque::push_back()
{
    if (mItEnd.mpCurrent + 1 != mItEnd.mpEnd) {
        Entry* p = mItEnd.mpCurrent++;
        if (p)
            new (p) Entry();
    } else {
        Entry tmp;
        DoPushBack(tmp);
    }
}

// @ 0x0092ef40
unsigned __stdcall DirectoryIteratorRead(const wchar_t* dir, Deque* list, const wchar_t* pattern, unsigned char flags, unsigned maxCount, bool wantTimes)
{
    EntryFindData scratch;
    unsigned n = 0;
    EntryFindData* e = EntryFindFirst(dir, pattern, &scratch, wantTimes);
    if (!e)
        return 0;
    do {
        if (n >= maxCount)
            goto done;
        if (wcscmp(e->mName, kDot) != 0 && wcscmp(e->mName, kDotDot) != 0) {
            if (e->mIsDirectory) {
                if (flags & 1) {
                    n++;
                    list->push_back();
                    list->back().mType = 1;
                    list->back().mName.assign(e->mName, e->mName + StrLen16(e->mName));
                    list->back().mTimes64[0] = e->mCreateTime;
                    list->back().mTimes64[1] = e->mWriteTime;
                    list->back().mTimes64[2] = e->mAccessTime;
                }
            } else if (flags & 2) {
                n++;
                list->push_back();
                list->back().mType = 2;
                list->back().mName.assign(e->mName, e->mName + StrLen16(e->mName));
                list->back().mTimes64[0] = e->mCreateTime;
                list->back().mTimes64[1] = e->mWriteTime;
                list->back().mTimes64[2] = e->mAccessTime;
            }
        }
    } while (EntryFindNext(e, wantTimes));
    EntryFindFinish(e);
done:
    if ((flags & 4) && n < maxCount) {
        n++;
        list->push_back();
        list->mItBegin.mpCurrent->mType = 1;
        list->mItBegin.mpCurrent->mName.append(kDot);
    }
    if ((flags & 8) && n < maxCount) {
        n++;
        list->push_back();
        list->mItBegin.mpCurrent->mType = 1;
        list->mItBegin.mpCurrent->mName.append(kDotDot);
    }
    return n;
}

// @ 0x0092f220
uint32_t DirectoryIterator::ReadRecursive(const unsigned short* pDir, void* pList, const unsigned short* pFilter, uint32_t flags, char c6, char c7, uint32_t maxDepth, void* p9)
{
    uint32_t oldIndex = mnRecursionIndex;
    int newIndex = oldIndex + 1;
    mnRecursionIndex = newIndex;
    if (oldIndex == 0) {
        mnListSize = 0;
        mpBaseDirectory = (unsigned short*)pDir;
        unsigned short* p = (unsigned short*)pDir;
        while (*p++) {}
        uint32_t len = (uint32_t)((char*)p - (char*)(pDir + 1)) >> 1;
        mBaseDirectoryLength = len;
        if (len == 0 || (pDir[len - 1] != '\\' && pDir[len - 1] != '/' && pDir[len - 1] != ':')) {
            mBaseDirectoryLength = len + 1;
        }
    }
    if ((flags & 2) != 0 && (c6 != 0 || newIndex > 1)) {
        if (mnListSize >= maxDepth) goto done;
        int n = FillEntries(pDir, 0, 0, 2, maxDepth - mnListSize, p9);
        // iterate a deque<Entry> whose live range is pList[0x18] .. pList[0x20]
        int* pFirst = *(int**)((char*)pList + 0x18);
        int* pLast  = *(int**)((char*)pList + 0x20);
        FUN_0092e9f0((char*)&n /*placeholder self*/, -n);
        if (pFirst != *(int**)((char*)pList + 0x18)) {
            do {
                mnListSize++;
                int* pEntry = pFirst;
                int elemCount = (*(int*)((char*)pEntry + 8) - *(int*)((char*)pEntry + 4));
                unsigned short* dst = (unsigned short*)*(int*)((char*)pEntry + 4);
                const unsigned short* q = pDir;
                while (*q) ++q;
                // string insert at dst with [pDir, q)
                extern void WString_insert(void*, const unsigned short*, const unsigned short*);
                WString_insert(&dst, pDir, q);
                int added = ((*(int*)((char*)pEntry + 8) - *(int*)((char*)pEntry + 4)) >> 1) - (elemCount >> 1);
                if (added != 0) {
                    unsigned short last = dst[added - 1];
                    if (last != '\\' && last != '/' && last != ':') {
                        extern void WString_append(void*, const unsigned short*, int, unsigned short);
                        WString_append(&dst, dst + added, 1, '\\');
                    }
                }
                if (c7 == 0) FUN_004228e0(0, mBaseDirectoryLength);
                pFirst += 0x30 / 4;
                if ((char*)pFirst == (char*)pLast) {
                    pLast = (int*)((char*)pLast + 4);
                    pFirst = (int*)*pLast;
                    pLast = (int*)((char*)pFirst + 0xc0);
                }
            } while ((char*)pFirst != (char*)*(int**)((char*)pList + 0x18));
        }
    }
    if (mnListSize < maxDepth) {
        // recursive scan built on a local deque
        char localDeque[0x18];
        int loc0 = *(int*)((char*)pList + 0x28);
        int loc1 = *(int*)((char*)pList + 0x2c);
        (void)loc0; (void)loc1;
        FUN_005f8840(localDeque);
        FillEntries(pDir, localDeque, 0, 1, 0x100000, p9);
        unsigned short buf[0x100];
        int* it = *(int**)(localDeque + 0x10);
        int* end = *(int**)(localDeque + 0x14);
        if (it != end) {
            do {
                if (mnListSize >= maxDepth) break;
                ConcatenatePathComponents(buf, pDir, *(const unsigned short**)((char*)it + 4));
                if ((flags & 1) != 0 &&
                    (pFilter == 0 || EA_Text_WildcardMatch(*(const unsigned short**)((char*)it + 4), pFilter, 1))) {
                    mnListSize++;
                    void* e = Deque_Push(localDeque);
                    (void)e;
                    int* out = Deque_Last(localDeque);
                    out[0] = 1;
                    unsigned short* q = buf;
                    while (*q) ++q;
                    void* s = (char*)out + 4;
                    WString_Assign(s, buf, q);
                    out[6] = *(int*)((char*)it + 0x18);
                    out[7] = *(int*)((char*)it + 0x1c);
                    out[8] = *(int*)((char*)it + 0x20);
                    out[9] = *(int*)((char*)it + 0x24);
                    out[10] = *(int*)((char*)it + 0x28);
                    out[11] = *(int*)((char*)it + 0x2c);
                    if (c7 == 0) FUN_004228e0(0, mBaseDirectoryLength);
                }
                ReadRecursive(buf, pList, pFilter, flags, 1, c7, maxDepth, p9);
                it = (int*)((char*)it + 0x30);
                if (it == end) {
                    int* nx = (int*)((char*)end + 4);
                    it = (int*)*nx;
                    end = (int*)((char*)it + 0xc0);
                }
            } while (it != *(int**)(localDeque + 0x14));
        }
        FUN_005f96c0(localDeque);
    }
done:
    uint32_t r = mnListSize;
    mnRecursionIndex--;
    return r;
}
