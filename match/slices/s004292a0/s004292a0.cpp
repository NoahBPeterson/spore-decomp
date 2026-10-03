// EASTL string/vector helpers and a small record type, 0x004292A0..0x004297F0.
// Built without optimization: /Od /Ob1 /arch:SSE (frame pointer, locals in memory,
// small helpers still inlined).
#include "types.h"
#include <string.h>

typedef uint16_t wchar16;

// EASTL allocator entry points (callees; calling convention only matters).
void  __cdecl EASTL_allocator_deallocate(void* p) throw();
void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags,
                                       int align, const char* file, int line);
extern const char g_EditorName[];     // "Editor"
extern const char g_AllocatorHdr[];   // ".../EASTL/include/EASTL/allocator.h"
extern wchar16    g_EmptyWStr[];      // shared 1-char empty string storage

template <class T> static inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

static inline wchar16* WCopy(const wchar16* first, const wchar16* last, wchar16* dest)
{
    memcpy(dest, first, (last - first) * 2);
    return dest + (last - first);
}

static inline wchar16* WAlloc(uint32_t n)
{
    void* p = EASTL_allocator_allocate(n * 2, g_EditorName, 0, 0, g_AllocatorHdr, 0xd1);
    return (wchar16*)p;
}

static inline void Nop3() { volatile int u1, u2, u3; }
static inline void Nop5() { volatile int d0, d1, d2, d3, d4; }

// ---------------------------------------------------------------------------
// Vector/string with a fixed overflow buffer at +0x10, 16-bit elements.
struct WideFixedBuf {
    wchar16* mBegin; wchar16* mEnd; wchar16* mCap; int pad; wchar16* mFixed;
    void ReleaseHeap();
    void DoFree(wchar16* p, int n) { if (p && p != mFixed) { wchar16* q = p; EASTL_allocator_deallocate(q); } }
};

// @ 0x004292A0
void WideFixedBuf::ReleaseHeap()
{
    if ((mCap - mBegin) > 1) DoFree(mBegin, mCap - mBegin);
}

// Same, 8-bit elements.
struct ByteFixedBuf {
    char* mBegin; char* mEnd; char* mCap; int pad; char* mFixed;
    void ReleaseHeap();
    ByteFixedBuf* DeletingDtor(uint32_t flags);
    ByteFixedBuf* Identity(int unused);
    void DoFree(char* p, int n) { if (p && p != mFixed) { char* q = p; EASTL_allocator_deallocate(q); } }
    void DoFreeNoFixed(char* p, int n) { if (p) { char* q = p; EASTL_allocator_deallocate(q); } }
};

// @ 0x00429300
void ByteFixedBuf::ReleaseHeap()
{
    if ((mCap - mBegin) > 1) DoFree(mBegin, mCap - mBegin);
}

// @ 0x00429360
ByteFixedBuf* ByteFixedBuf::Identity(int) { return this; }

// @ 0x00429410
ByteFixedBuf* ByteFixedBuf::DeletingDtor(uint32_t flags)
{
    if ((mCap - mBegin) > 1) DoFreeNoFixed(mBegin, mCap - mBegin);
    if (flags & 1) EASTL_allocator_deallocate(this);
    return this;
}

// ---------------------------------------------------------------------------
// Holder: two byte vectors (+0x00, +0x10) and an Elem32Vec (+0x20).
struct ByteVec {
    char* mBegin; char* mEnd; char* mCap; int pad;
    void DoFree(char* p, int n) { if (p) { char* q = p; EASTL_allocator_deallocate(q); } }
    ~ByteVec() { if ((mCap - mBegin) > 1) DoFree(mBegin, mCap - mBegin); }
};
struct Elem32Vec { uint32_t a[4]; ~Elem32Vec() throw(); };
struct Holder {
    ByteVec a; ByteVec b; Elem32Vec c;
    ~Holder();
};

// @ 0x00429480
Holder::~Holder() { volatile int d0, d1, d2, d3, d4, d5, d6, d7, d8; }

// ---------------------------------------------------------------------------
// Record with two 0x38-byte sub-blocks, an int, a ref-counted pointer and a smart pointer.
struct RefCounted { virtual void AddRef(); virtual void Release(); };
struct Block38 { char d[0x38]; Block38& Assign(const Block38& o); };
struct SmartPtr { RefCounted* p; SmartPtr& Assign(const SmartPtr& o); };
struct RcPtr {
    RefCounted* p;
    void Assign(const RcPtr& o)
    {
        RefCounted* old; RefCounted* np = o.p;
        if (np != p) { old = p; if (np) np->AddRef(); p = np; if (old) old->Release(); }
    }
};
struct Record {
    Block38 a; Block38 b; int f70; RcPtr f74; SmartPtr f78;
    Record& Assign(const Record& o);
};

// @ 0x00429370
Record& Record::Assign(const Record& o)
{
    a.Assign(o.a);
    b.Assign(o.b);
    f70 = o.f70;
    f74.Assign(o.f74);
    Nop5();
    f78.Assign(o.f78);
    return *this;
}

// ---------------------------------------------------------------------------
// 16-bit string (eastl::basic_string<char16_t>) members.
struct WStr {
    wchar16* mBegin; wchar16* mEnd; wchar16* mCap;
    void Erase(wchar16* first, wchar16* last);
    void AppendFill(uint32_t n, wchar16 c);
    void FreeBuffer();
    void Resize(uint32_t n);
    WStr* Append(const wchar16* first, const wchar16* last);
    void AllocateSelf(uint32_t n);
};

// @ 0x00429520
void WStr::Resize(uint32_t n)
{
    uint32_t sz = mEnd - mBegin;
    if (n < sz) Erase(mBegin + n, mEnd);
    else if (n > sz) AppendFill(n - sz, 0);
}

// @ 0x00429760
void WStr::AllocateSelf(uint32_t n)
{
    if (n > 1) {
        void* p = EASTL_allocator_allocate(n * 2, g_EditorName, 0, 0, g_AllocatorHdr, 0xd1);
        mBegin = (wchar16*)p;
        mEnd = mBegin;
        mCap = mBegin + n;
    } else {
        mBegin = g_EmptyWStr;
        mEnd = mBegin;
        mCap = mBegin + 1;
    }
}

// @ 0x004297F0
wchar16* __cdecl WFindChar(wchar16* first, wchar16* last, wchar16 c);
wchar16* WSearch(wchar16* first1, wchar16* last1, wchar16* first2, wchar16* last2)
{
    if (first1 == last1 || first2 == last2) return first1;
    if (first2 + 1 == last2) return WFindChar(first1, last1, *first2);
    if ((last2 - first2) > (last1 - first1)) return last1;
    wchar16* cur = last1 - (last2 - first2) + 1;
    while (cur != first1) {
        wchar16* found = WFindChar(first1, cur, *first2);
        if (found == cur) return last1;
        wchar16* p = first2;
        while (*found++ == *p++) {
            if (p == last2) return found - (last2 - first2);
        }
        --cur;
    }
    return last1;
}

// @ 0x00429580
WStr* WStr::Append(const wchar16* first, const wchar16* last)
{
    uint32_t nOldSize; int n; uint32_t capacity; wchar16* yfv; int k; wchar16* pNewBegin; const wchar16* tvi;
    // Local names are load-bearing: /Od frame slot order follows the symbol table.
    if (first != last) {
        nOldSize = mEnd - mBegin;
        n = last - first;
        capacity = (mCap - mBegin) - 1;
        if (nOldSize + n > capacity) {
            uint32_t nRequired = nOldSize + n;
            uint32_t nGrow = (capacity > 8) ? capacity * 2 : 8;
            k = Max(nGrow, nRequired) + 1;
            pNewBegin = WAlloc(k);
            yfv = pNewBegin;
            yfv = WCopy(mBegin, mEnd, pNewBegin);
            yfv = WCopy(first, last, yfv);
            *yfv = 0;
            Nop3();
            FreeBuffer();
            mBegin = pNewBegin; mEnd = yfv; mCap = pNewBegin + k;
        } else {
            tvi = first; ++tvi;
            WCopy(tvi, last, mEnd + 1);
            mEnd[n] = 0; *mEnd = *first; mEnd = mEnd + n;
        }
    }
    return this;
}
