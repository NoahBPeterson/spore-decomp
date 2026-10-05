// slice s006525d0: EASTL sort/heap + vector machinery for SP::cSPAssetGridEntry
// (the 0x20-byte retail grid entry) plus SP::cSPUIAssetGrid::UpdateStatsText.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// ---------------------------------------------------------------------------
// Refcounted object interface. AddRef/Release are virtual; definitions live in
// earlier slices, so calls are emitted as (masked) relocations.
// ---------------------------------------------------------------------------
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};

// m0c's object carries its refcount base at +0x10 (secondary IRefCount base);
// m10's is the primary vtable.  Modelled with smart-pointer members so cl
// generates the element copy ctor/dtor itself (matching the original inline
// AddRef/Release interleaving).
struct EntryPrimary { virtual void v(); char pad0[0xc]; };
struct EntryView : EntryPrimary, IRefCount {};   // IRefCount at +0x10
struct EntryData : IRefCount {};                  // IRefCount at +0x0

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(const AutoRefCount&);
};

struct GridEntry {
    void* m00;                       // +0x00
    void* m04;                       // +0x04
    void* m08;                       // +0x08
    AutoRefCount<EntryView> m0c;     // +0x0c  (refcount base at +0x10)
    AutoRefCount<EntryData> m10;     // +0x10
    float m14;                       // +0x14
    float m18;                       // +0x18
    bool  m1c;                       // +0x1c
    bool  m1d;                       // +0x1d
    GridEntry() {}
    GridEntry& operator=(const GridEntry&);   // 0x0064f450
};

struct CompareA {                 // 0x0064ff90: two entries BY VALUE (ret 0x40)
    bool operator()(GridEntry a, GridEntry b) const;
};
struct TypeGridEntrySort {        // 0x0066a830: two entries BY REFERENCE (ret 8)
    bool operator()(const GridEntry& a, const GridEntry& b) const;
};

// ---------------------------------------------------------------------------
// EASTL heap/sort primitives (structure from the byte-exact s004c2100/s005b7460).
// ---------------------------------------------------------------------------
namespace eastl {

template <typename It, typename Distance, typename T, typename Compare>
__declspec(noinline) void promote_heap(It first, Distance topPosition, Distance position,
                                       T value, Compare compare) {
    for (Distance parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(*(first + parentPosition), value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

template <typename It, typename Distance, typename T, typename Compare>
__declspec(noinline) void adjust_heap(It first, Distance topPosition, Distance heapSize,
                                      Distance position, T value, Compare compare) {
    Distance childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(*(first + childPosition), *(first + (childPosition - 1))))
            --childPosition;
        *(first + position) = *(first + childPosition);
        position = childPosition;
    }
    if (childPosition == heapSize) {
        *(first + position) = *(first + (childPosition - 1));
        position = childPosition - 1;
    }
    eastl::promote_heap<It, Distance, T, Compare>(first, topPosition, position, value, compare);
}

template <typename It, typename Compare>
__declspec(noinline) void make_heap(It first, It last, Compare compare) {
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            eastl::adjust_heap<It, int, GridEntry, Compare>(first, parentPosition, heapSize,
                                                            parentPosition,
                                                            *(first + parentPosition), compare);
        } while (parentPosition != 0);
    }
}

template <typename It, typename Compare>
__declspec(noinline) void pop_heap(It first, It last, Compare compare) {
    const GridEntry tempBottom(*(last - 1));
    *(last - 1) = *first;
    eastl::adjust_heap<It, int, GridEntry, Compare>(first, 0, (int)(last - first - 1), 0,
                                                    tempBottom, compare);
}

template <typename It, typename T, typename Compare>
__declspec(noinline) It get_partition(It first, It last, T pivotValue, Compare compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const T temp(*first);
        *first = *last;
        *last = temp;
    }
}

// --- set B (TypeGridEntrySort passed BY REFERENCE, like the original) --------
template <typename It, typename Distance, typename T, typename Compare>
void adjust_heap_ref(It first, Distance topPosition, Distance heapSize, Distance position,
                     T value, Compare& compare);   // defined in slice 62

template <typename It, typename Compare>
void pop_heap_ref(It first, It last, Compare& compare);   // defined in slice 62

template <typename It, typename Compare>
__declspec(noinline) void make_heap_ref(It first, It last, Compare& compare) {
    const int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            eastl::adjust_heap_ref<It, int, GridEntry, Compare>(
                first, parentPosition, heapSize, parentPosition, *(first + parentPosition),
                compare);
        } while (parentPosition != 0);
    }
}

template <typename It, typename T, typename Compare>
__declspec(noinline) It get_partition_ref(It first, It last, T pivotValue, Compare& compare) {
    for (;; ++first) {
        while (compare(*first, pivotValue))
            ++first;
        --last;
        while (compare(pivotValue, *last))
            --last;
        if (first >= last)
            return first;
        const T temp(*first);
        *first = *last;
        *last = temp;
    }
}

template <typename It, typename Compare>
__declspec(noinline) void partial_sort_ref(It first, It middle, It last, Compare& compare) {
    eastl::make_heap_ref<It, Compare>(first, middle, compare);
    for (It i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            const GridEntry temp(*i);
            *i = *first;
            eastl::adjust_heap_ref<It, int, GridEntry, Compare>(first, 0, (int)(middle - first), 0,
                                                                temp, compare);
        }
    }
    It last2 = middle;
    while ((last2 - first) > 1) {
        eastl::pop_heap_ref<It, Compare>(first, last2, compare);
        --last2;
    }
}

// Force exactly the instantiations the original emitted.
template void promote_heap<GridEntry*, int, GridEntry, CompareA>(GridEntry*, int, int, GridEntry, CompareA);
template void adjust_heap<GridEntry*, int, GridEntry, CompareA>(GridEntry*, int, int, int, GridEntry, CompareA);
template void pop_heap<GridEntry*, CompareA>(GridEntry*, GridEntry*, CompareA);
template GridEntry* get_partition<GridEntry*, GridEntry, CompareA>(GridEntry*, GridEntry*, GridEntry, CompareA);
template void make_heap<GridEntry*, CompareA>(GridEntry*, GridEntry*, CompareA);

template void make_heap_ref<GridEntry*, TypeGridEntrySort>(GridEntry*, GridEntry*, TypeGridEntrySort&);
template GridEntry* get_partition_ref<GridEntry*, GridEntry, TypeGridEntrySort>(GridEntry*, GridEntry*, GridEntry, TypeGridEntrySort&);
template void partial_sort_ref<GridEntry*, TypeGridEntrySort>(GridEntry*, GridEntry*, GridEntry*, TypeGridEntrySort&);

}  // namespace eastl

// ---------------------------------------------------------------------------
// External helpers (defined in earlier slices).
// ---------------------------------------------------------------------------
extern "C" void  EASTL_allocator_deallocate(void* p);                                   // 0xf47380
extern "C" void* EASTL_allocator_allocate(unsigned n, const char* name, int a, int b,
                                          const char* file, int line);                  // 0xf473a0
GridEntry* CopyRange(GridEntry* first, GridEntry* last, GridEntry* dest);               // 0x64f890
GridEntry* UninitializedCopy(GridEntry* first, GridEntry* last, GridEntry* dest);       // 0x64f7c0
GridEntry* UninitializedFillN(GridEntry* dest, unsigned n, const GridEntry& value, GridEntry*);  // 0x64f8d0
GridEntry* DestroyRange(GridEntry* first, GridEntry* last, GridEntry* dest);            // 0x64f840
void       CopyBackward(GridEntry* first, GridEntry* last, GridEntry* destEnd);         // 0x64f950
void       FillRange(GridEntry* first, GridEntry* last, const GridEntry& value);        // 0x651670

// ---------------------------------------------------------------------------
// eastl::vector<GridEntry, sp_vector_allocator> members.
// ---------------------------------------------------------------------------
struct GridVec {
    GridEntry* mpBegin;     // +0
    GridEntry* mpEnd;       // +4
    GridEntry* mpCapacity;  // +8

    void DoDestroyValues(GridEntry* first, GridEntry* last);                     // 0x0064f410
    GridEntry* ReallocateAndCopy(unsigned n, GridEntry* first, GridEntry* last); // 0x00651540
    GridVec& operator=(const GridVec& x);                                        // 0x00652ba0
    void DoInsertValues(GridEntry* position, unsigned n, const GridEntry& value); // 0x00652c90
    GridEntry* erase(GridEntry* position);                                       // 0x006534c0
    void swap(GridVec& other);                                                    // 0x00653510
};

// @ 0x00652ba0  vector::operator=(const vector&)
GridVec& GridVec::operator=(const GridVec& x) {
    if (this != &x) {
        const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
        if (n > (unsigned)(mpCapacity - mpBegin)) {
            GridEntry* pNewData = ReallocateAndCopy(n, x.mpBegin, x.mpEnd);
            DoDestroyValues(mpBegin, mpEnd);
            if (mpBegin && ((unsigned*)mpBegin)[-1])
                EASTL_allocator_deallocate(mpBegin);
            mpBegin = pNewData;
            mpEnd = pNewData + n;
            mpCapacity = pNewData + n;
        } else if ((unsigned)(mpEnd - mpBegin) < n) {
            CopyRange(x.mpBegin, x.mpBegin + (mpEnd - mpBegin), mpBegin);
            UninitializedCopy(x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd);
            mpEnd = mpBegin + n;
        } else {
            CopyRange(x.mpBegin, x.mpEnd, mpBegin);
            DoDestroyValues(mpBegin + n, mpEnd);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}

// @ 0x00652c90  vector::DoInsertValues(position, n, value)
void GridVec::DoInsertValues(GridEntry* position, unsigned n, const GridEntry& value) {
    if (n == 0)
        return;
    if ((unsigned)(mpCapacity - mpEnd) < n) {
        const unsigned nSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNew = nSize + n;
        unsigned grow = nSize * 2;
        if (nSize == 0)
            grow = 1;
        if (nNew < grow)
            nNew = grow;
        GridEntry* pNewData =
            (GridEntry*)EASTL_allocator_allocate(nNew * sizeof(GridEntry), "Editor", 0, 0,
                                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                                 "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                                 "EASTL/allocator.h",
                                                 0xd1);
        GridEntry* pNewEnd = UninitializedCopy(mpBegin, position, pNewData);
        UninitializedFillN(pNewEnd, n, value, 0);
        pNewEnd += n;
        UninitializedCopy(position, mpEnd, pNewEnd);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nSize + n;
        mpCapacity = pNewData + nNew;
    } else {
        GridEntry temp(value);
        const unsigned nEnd = (unsigned)(mpEnd - position);
        if (n < nEnd) {
            UninitializedCopy(mpEnd - n, mpEnd, mpEnd);
            CopyBackward(position, mpEnd - n, mpEnd);
            mpEnd += n;
            FillRange(position, position + n, temp);
        } else {
            UninitializedFillN(mpEnd, n - nEnd, temp, 0);
            mpEnd += n - nEnd;
            UninitializedCopy(position, mpEnd - n, mpEnd);
            mpEnd += nEnd;
            FillRange(position, mpEnd - n, temp);
        }
    }
}

// @ 0x006534c0  vector::erase(position)
GridEntry* GridVec::erase(GridEntry* position) {
    if ((position + 1) < mpEnd)
        CopyRange(position + 1, mpEnd, position);
    mpEnd -= 1;
    mpEnd->~GridEntry();
    return position;
}

// @ 0x00653510  vector::swap(vector&)
void GridVec::swap(GridVec& other) {
    if (mpBegin == 0 || ((unsigned*)mpBegin)[-1] != 0 ||
        other.mpBegin == 0 || ((unsigned*)other.mpBegin)[-1] != 0) {
        GridEntry* t0 = mpBegin; mpBegin = other.mpBegin; other.mpBegin = t0;
        GridEntry* t1 = mpEnd; mpEnd = other.mpEnd; other.mpEnd = t1;
        GridEntry* t2 = mpCapacity; mpCapacity = other.mpCapacity; other.mpCapacity = t2;
    } else {
        GridVec temp;
        temp = *this;
        *this = other;
        other = temp;
        temp.DoDestroyValues(temp.mpBegin, temp.mpEnd);
        if (temp.mpBegin && ((unsigned*)temp.mpBegin)[-1])
            EASTL_allocator_deallocate(temp.mpBegin);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006528f0  SP::cSPUIAssetGrid::UpdateStatsText
// ---------------------------------------------------------------------------
struct cString {
    wchar_t* mpBegin;      // +0
    wchar_t* mpEnd;        // +4
    wchar_t* mpCapacity;   // +8
    void*    mAllocator;   // +0xc
    cString();
    ~cString();
    void Load(unsigned int hash, int flags, const wchar_t* fmt);
    const wchar_t* c_str() const;
    cString& operator=(const wchar_t* s);
};

extern void* g_uiCtx;                                    // 0x015ee298
extern "C" void* AssetBrowser();                         // 0x00401030
extern "C" void  WString_Assign(cString* dst, const wchar_t* first, const wchar_t* last);  // 0x00423650
extern "C" void* FUN_00644a70(void*);                    // 0x00644a70

struct StatsGrid {
    char pad00[0x14];
    bool mIsVisible;                 // +0x14
    char pad15[0x1ac - 0x15];
    unsigned int mA;                 // +0x1ac
    unsigned int mB;                 // +0x1b0
    unsigned int mCount;             // +0x1b4
    void Scrollbar(unsigned a, unsigned b, unsigned c, unsigned d);  // 0x0064e980
    void UpdateStatsText();
};

void StatsGrid::UpdateStatsText() {
    if (!mIsVisible)
        return;
    if (!AssetBrowser())
        return;

    cString msg;
    *(unsigned int*)((char*)g_uiCtx + 0x28) = mA;
    *(unsigned int*)((char*)g_uiCtx + 0x2c) = mB;
    if (mA == mB)
        msg.Load(0x21671745, 0x30003, L"*Displaying n items.*");
    else
        msg.Load(0x21671745, 0x30005, L"*Displaying n of n items.*");

    const wchar_t* p = msg.c_str();
    const wchar_t* e = p;
    while (*e)
        ++e;
    WString_Assign(&msg, p, e);

    if (mCount == 0) {
        msg = L"";
    }

    unsigned int selected = 0;
    void* browser = AssetBrowser();
    unsigned int browserFlags = *(unsigned int*)((char*)browser + 0x20);
    void* items = FUN_00644a70(browser);
    int num = (*(int*)((char*)items + 4) - *(int*)items) / 0x14;  // element size 0x14
    if (browserFlags != 1 && num > 0) {
        *(unsigned int*)((char*)g_uiCtx + 0x34) = (unsigned int)num;
        cString sel;
        sel.Load(0x6f5943eb, 0x2000002, L"*Selected n items.*");
        msg = sel.c_str();
        if (browserFlags > 1 && (unsigned int)num > browserFlags)
            selected = 1;
        else
            selected = 0;
    }
    Scrollbar(mA, mB, selected, 0);
    msg.c_str();
}
