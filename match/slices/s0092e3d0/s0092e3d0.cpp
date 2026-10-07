// Slice s0092e3d0: EA::DateTime helpers, EA::IO directory iteration (EntryFindFirst/Next/Close,
// DirectoryIterator::Read) and the eastl::deque<DirectoryIterator::Entry> support it uses.
#include "types.h"
#include <time.h>
#include <string.h>
#include <new>
#include <windows.h>

extern "C" int64_t __stdcall _alldiv(int, int, int, int);
extern "C" int64_t __stdcall _allmul(int, int, int, int);

// ---------------------------------------------------------------------------------------------
// EA::DateTime::DateTime  (one __int64 count of seconds)
// ---------------------------------------------------------------------------------------------
struct DateTime {
    int64_t mnSeconds;
    int  GetParameter(int which);
    void SetDate(int year, int month, int day, int hour, int minute, int second);
    void Set(int utc);
    void Add(int unit, int amount);
};

// @ 0x0092e3d0  EA::DateTime::DateTime::Set  (current time; utc==1 selects gmtime)
void DateTime::Set(int utc) {
    time_t t = _time64(0);
    tm* p;
    if (utc == 1)
        p = _gmtime64(&t);
    else
        p = _localtime64(&t);
    if (p)
        SetDate(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

// @ 0x0092e440  fields of a struct tm forwarded to SetDate on the DateTime passed second
// (cdecl, two stack args: the original loads ecx from [esp+0x1c] after five pushes = arg 2)
void SetDateFromTm(const tm* p, DateTime* d) {
    d->SetDate(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
}

// @ 0x0092e470  EA::DateTime::DateTime::Add(unit, amount)
void DateTime::Add(int unit, int amount) {
    switch (unit) {
    case 1: {
        int y = GetParameter(1) + amount;
        SetDate(y, -1, -1, -1, -1, -1);
        break;
    }
    case 2: {
        int years = amount / 12;
        int y = GetParameter(1) + years;
        int m = amount + GetParameter(2) - years * 12;
        if (m < 1) {
            y--;
            m += 12;
        } else if (m > 12) {
            y++;
            m -= 12;
        }
        SetDate(y, m, -1, -1, -1, -1);
        break;
    }
    case 5:
    case 6:
    case 7:
        mnSeconds += (int64_t)(amount * 86400);
        break;
    case 8:
        mnSeconds += (int64_t)(amount * 3600);
        break;
    case 9:
        mnSeconds += (int64_t)(amount * 60);
        break;
    case 10:
        mnSeconds += (int64_t)amount;
        break;
    case 3:
    case 4:
        mnSeconds += (int64_t)(amount * 604800);
        break;
    }
}

// @ 0x0092e5a0  seconds between local time and UTC (rounded down to the hour)
int64_t GetLocalTimeBias() {
    time_t t = _time64(0);
    tm* p = _localtime64(&t);
    if (p)
        ((DateTime*)(p->tm_mon + 1))->SetDate(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    int64_t localHours = _alldiv((int)t, (int)(t >> 32), 3600, 0);
    t = _time64(0);
    p = _gmtime64(&t);
    if (p)
        ((DateTime*)(p->tm_mon + 1))->SetDate(p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    int64_t gmHours = _alldiv((int)t, (int)(t >> 32), 3600, 0);
    return _allmul((int)(localHours - gmHours), (int)((localHours - gmHours) >> 32), 3600, 0);
}

// @ 0x0092e680  FILETIME epoch (1970-01-01) in seconds
__declspec(noinline) static int64_t GetFileTimeEpoch() {
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

// @ 0x0092e6e0  FILETIME -> seconds since 1970 (epoch computed once)
static int64_t FileTimeToUnix(const FILETIME* ft) {
    int64_t secs = _alldiv(ft->dwLowDateTime, ft->dwHighDateTime, 10000000, 0);
    static int64_t sEpoch = GetFileTimeEpoch();
    return secs - sEpoch;
}

// ---------------------------------------------------------------------------------------------
// EA::IO entry search
// ---------------------------------------------------------------------------------------------
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

void  EnsureTrailingPathSeparator(wchar_t* path, int len);
void  ConcatenatePathComponents(wchar_t* out, const wchar_t* dir, const wchar_t* name);
void* operator new(unsigned, const char*, int, int, int, int);
void  operator delete[](void*);

static inline void CopyW(wchar_t* d, const wchar_t* s) {
    do {
    } while ((*d++ = *s++) != 0);
}

// @ 0x0092e730  EA::IO::EntryFindFirst
EntryFindData* EntryFindFirst(const wchar_t* dir, const wchar_t* pattern, EntryFindData* data, bool wantTimes) {
    wchar_t defPattern[2] = { L'*', 0 };
    WIN32_FIND_DATAW fd;
    wchar_t full[260];
    ConcatenatePathComponents(full, dir, pattern ? pattern : defPattern);
    if (!data) {
        data = new ("UTF/EAFileDirectory/EntryFindData", 0, 0, 0, 0) EntryFindData();
        data->mOwned = 1;
    }
    HANDLE h = FindFirstFileW(full, &fd);
    if (h != INVALID_HANDLE_VALUE) {
    const wchar_t* s = fd.cFileName;
    wchar_t* d = data->mName;
    CopyW(d, s);
    data->mIsDirectory = (char)((fd.dwFileAttributes >> 4) & 1);
    if (data->mIsDirectory)
        EnsureTrailingPathSeparator(data->mName, -1);
    if (dir) {
        s = dir;
        d = data->mBaseDir;
        CopyW(d, s);
    } else
        data->mBaseDir[0] = 0;
    if (pattern) {
        s = pattern;
        d = data->mPattern;
        CopyW(d, s);
    } else
        data->mPattern[0] = 0;
    data->mHandle = h;
    if (wantTimes) {
        data->mCreateTime = FileTimeToUnix(&fd.ftCreationTime);
        data->mWriteTime = FileTimeToUnix(&fd.ftLastWriteTime);
        data->mAccessTime = FileTimeToUnix(&fd.ftLastAccessTime);
    }
    return data;
    }
    return 0;
}

// @ 0x0092e8e0  EA::IO::EntryFindNext
EntryFindData* EntryFindNext(EntryFindData* data, bool wantTimes) {
    WIN32_FIND_DATAW fd;
    if (data) {
      HANDLE h = data->mHandle;
      if (FindNextFileW(h, &fd)) {
        const wchar_t* s = fd.cFileName;
        wchar_t* d = data->mName;
        CopyW(d, s);
        data->mIsDirectory = (char)((fd.dwFileAttributes >> 4) & 1);
        if (data->mIsDirectory)
            EnsureTrailingPathSeparator(data->mName, -1);
        if (wantTimes) {
            data->mCreateTime = FileTimeToUnix(&fd.ftCreationTime);
            data->mWriteTime = FileTimeToUnix(&fd.ftLastWriteTime);
            data->mAccessTime = FileTimeToUnix(&fd.ftLastAccessTime);
        }
        return data;
      }
    }
    return 0;
}

// @ 0x0092e9b0  EA::IO::EntryFindFinish
void EntryFindFinish(EntryFindData* data) {
    if (data) {
        HANDLE h = data->mHandle;
        if (h && h != INVALID_HANDLE_VALUE)
            FindClose(h);
        if (data->mOwned)
            operator delete[](data);
    }
}

// ---------------------------------------------------------------------------------------------
// EASTL pieces used by EA::IO::DirectoryIterator (wide string, deque<Entry>)
// ---------------------------------------------------------------------------------------------
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

// @ 0x0092ea90  eastl::basic_string<wchar_t>::insert(iterator p, size_type n, value_type c)
__declspec(noinline) void WString::insert(wchar_t* p, unsigned n, wchar_t c) {
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

// EA::IO::DirectoryIterator::Entry (0x30 bytes)
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

// @ 0x0092ed90  Entry::Entry(const Entry&)
__declspec(noinline) Entry::Entry(const Entry& o) : mType(o.mType), mName(o.mName) {
    mTimes[0] = o.mTimes[0];
    mTimes[1] = o.mTimes[1];
    mTimes[2] = o.mTimes[2];
    mTimes[3] = o.mTimes[3];
    mTimes[4] = o.mTimes[4];
    mTimes[5] = o.mTimes[5];
}

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

// @ 0x0092e9f0  eastl::DequeIterator<Entry,...>::operator+=
__declspec(noinline) DequeIter& DequeIter::operator+=(int n) {
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

// eastl::deque<EA::IO::DirectoryIterator::Entry, EASTLCoreAllocator, 8>
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

// @ 0x0092ea70  eastl::deque::back
__declspec(noinline) Entry& Deque::back() {
    Entry* c = mItEnd.mpCurrent;
    Entry* b = mItEnd.mpBegin;
    Entry** arr = mItEnd.mpCurrentArrayPtr;
    if (c == b)
        return (*(arr - 1))[3];
    return c[-1];
}

static inline const unsigned& max_alt(const unsigned& a, const unsigned& b) { return a < b ? b : a; }

// @ 0x0092ec60  eastl::deque::DoReallocPtrArray(nAdditional, side)  (side 0 = front)
__declspec(noinline) void Deque::DoReallocPtrArray(unsigned nAdditional, int side) {
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

// @ 0x0092ee20  eastl::deque<Entry>::DoPushBack
__declspec(noinline) void Deque::DoPushBack(const Entry& value) {
    Entry valueSaved(value);
    if ((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1 >= (int)mnPtrArraySize)
        DoReallocPtrArray(1, 1);
    mItEnd.mpCurrentArrayPtr[1] = (Entry*)mpAllocator->Alloc(0xc0, 0, mpName);
    if (mItEnd.mpCurrent)
        new (mItEnd.mpCurrent) Entry(valueSaved);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
    mItEnd.mpCurrent = mItEnd.mpBegin;
}

// @ 0x0092eec0  eastl::deque<Entry>::push_back()
__declspec(noinline) void Deque::push_back() {
    if (mItEnd.mpCurrent + 1 != mItEnd.mpEnd) {
        Entry* p = mItEnd.mpCurrent++;
        if (p)
            new (p) Entry();
    } else {
        Entry tmp;
        DoPushBack(tmp);
    }
}

static __forceinline unsigned StrLen16(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (unsigned)(p - s);
}

// @ 0x0092ef40  EA::IO::DirectoryIterator::Read
unsigned __stdcall DirectoryIteratorRead(const wchar_t* dir, Deque* list, const wchar_t* pattern,
                                         unsigned char flags, unsigned maxCount, bool wantTimes) {
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
