// slice s006535b0: eastl::vector<SP::cSPAssetGridEntry> growth helpers, the
// quick_sort_impl/partial_sort A+B instantiations, and cSPUIAssetGrid methods.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <new>

struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
struct EntryPrimary { virtual void v(); char pad0[0xc]; };
struct EntryView : EntryPrimary, IRefCount {};
struct EntryData : IRefCount {};

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
    void* m00;
    void* m04;
    void* m08;
    AutoRefCount<EntryView> m0c;
    AutoRefCount<EntryData> m10;
    float m14;
    float m18;
    bool  m1c;
    bool  m1d;
    GridEntry() {}
    GridEntry& operator=(const GridEntry&);   // 0x0064f450
};

struct CompareA {                 // 0x0064ff90: by value
    bool operator()(GridEntry a, GridEntry b) const;
};
struct TypeGridEntrySort {        // 0x0066a830: by reference
    bool operator()(const GridEntry& a, const GridEntry& b) const;
};

// ---- external helpers (earlier slices) ------------------------------------
extern "C" void  EASTL_allocator_deallocate(void* p);                       // 0xf47380
extern "C" void* EASTL_allocator_allocate(unsigned, const char*, int, int, const char*, int);  // 0xf473a0
GridEntry* CopyRange(GridEntry* first, GridEntry* last, GridEntry* dest);              // 0x64f890
GridEntry* UninitializedCopy(GridEntry* first, GridEntry* last, GridEntry* dest);      // 0x64f7c0
GridEntry* DestroyRange(GridEntry* first, GridEntry* last, GridEntry* dest);           // 0x64f840
void       CopyBackward(GridEntry* first, GridEntry* last, GridEntry* destEnd);        // 0x64f950
void       FillRange(GridEntry* first, GridEntry* last, const GridEntry&);             // 0x651670

// heap/sort helpers from slice s006525d0 (and s006515a0 for median A)
GridEntry* GetPartitionA(GridEntry* first, GridEntry* last, GridEntry pivot);          // 0x652e70
GridEntry* GetPartitionB(GridEntry* first, GridEntry* last, GridEntry pivot);          // 0x653110
void       MakeHeapA(GridEntry* first, GridEntry* last);                               // 0x6533d0
void       AdjustHeapA(GridEntry* first, int top, int heapSize, int pos, GridEntry value);  // 0x6525d0
void       SortHeapA(GridEntry* first, GridEntry* last);                               // 0x653470
void       PartialSortB(GridEntry* first, GridEntry* middle, GridEntry* last);         // 0x653230
GridEntry  MedianA(GridEntry a, GridEntry b, GridEntry c);                             // 0x6515a0
void       DoInsertValuesEx(GridEntry* position, unsigned n, const GridEntry& value);  // 0x652c90

// ---- eastl::vector<GridEntry, sp_vector_allocator> ------------------------
struct GridVec {
    GridEntry* mpBegin;
    GridEntry* mpEnd;
    GridEntry* mpCapacity;

    void DoDestroyValues(GridEntry* first, GridEntry* last);                      // 0x0064f410
    GridEntry* ReallocateAndCopy(unsigned n, GridEntry* first, GridEntry* last);  // 0x00651540
    void DoInsertValue(GridEntry* position, const GridEntry& value);              // 0x006535b0
    void resize(unsigned n);                                                      // 0x00653e40
    void reserve(unsigned n);                                                     // 0x00654490
    void swap(GridVec& other);                                                    // 0x00653510
};

// @ 0x006535b0  vector::DoInsertValue(position, value)
void GridVec::DoInsertValue(GridEntry* position, const GridEntry& value) {
    if (mpEnd != mpCapacity) {
        const GridEntry* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new ((void*)mpEnd) GridEntry(*(mpEnd - 1));
        CopyBackward(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = (nPrevSize == 0) ? 1 : nPrevSize * 2;
        GridEntry* pNewData = nNewSize
            ? (GridEntry*)EASTL_allocator_allocate(nNewSize * sizeof(GridEntry), "Editor", 0, 0,
                                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                                   "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                                   "EASTL/allocator.h",
                                                   0xd1)
            : 0;
        GridEntry* pNewEnd = UninitializedCopy(mpBegin, position, pNewData);
        DestroyRange(mpBegin, position, pNewData);
        if (pNewEnd)
            ::new ((void*)pNewEnd) GridEntry(value);
        pNewEnd += 1;
        GridEntry* pEnd = UninitializedCopy(position, mpEnd, pNewEnd);
        DestroyRange(position, mpEnd, pNewEnd);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpBegin = pNewData;
        mpEnd = pEnd;
        mpCapacity = pNewData + nNewSize;
    }
}

// @ 0x00653e40  vector::resize(n)
void GridVec::resize(unsigned n) {
    const unsigned cur = (unsigned)(mpEnd - mpBegin);
    if (cur < n) {
        GridEntry empty;
        DoInsertValuesEx(mpEnd, n - cur, empty);
    } else {
        GridEntry* pos = mpBegin + n;
        CopyRange(mpEnd, mpEnd, pos);
        DestroyRange(pos, mpEnd, pos);
        mpEnd -= (unsigned)(mpEnd - pos);
    }
}

// @ 0x00654490  vector::reserve(n)
void GridVec::reserve(unsigned n) {
    const unsigned cur = (unsigned)(mpEnd - mpBegin);
    if (n > cur) {
        GridEntry* pNewData = n
            ? (GridEntry*)EASTL_allocator_allocate(n * sizeof(GridEntry), "Editor", 0, 0,
                                                   "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\"
                                                   "SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\"
                                                   "EASTL/allocator.h",
                                                   0xd1)
            : 0;
        GridEntry* pEnd = UninitializedCopy(mpBegin, mpEnd, pNewData);
        DestroyRange(mpBegin, mpEnd, pNewData);
        if (mpBegin && ((unsigned*)mpBegin)[-1])
            EASTL_allocator_deallocate(mpBegin);
        mpCapacity = pNewData + n;
        mpBegin = pNewData;
        mpEnd = pEnd;
    } else {
        if (n < cur)
            resize(n);
        DoInsertValuesEx(mpBegin, 0, (const GridEntry&)*(GridEntry*)0);
    }
}

// ---- quick_sort_impl / partial_sort ---------------------------------------
static const int kQuickSortLimit = 28;

inline const GridEntry& medianRef(const GridEntry& a, const GridEntry& b, const GridEntry& c) {
    TypeGridEntrySort cmp;
    if (cmp(a, b)) {
        if (cmp(b, c)) return b;
        else if (cmp(a, c)) return c;
        else return a;
    } else if (cmp(a, c)) {
        return a;
    } else if (cmp(b, c)) {
        return c;
    }
    return b;
}

void PartialSortA(GridEntry* first, GridEntry* middle, GridEntry* last);

// @ 0x00653f50  quick_sort_impl<GridEntry*,int,CompareA>
void QuickSortImplA(GridEntry* first, GridEntry* last, int kRecursionCount) {
    while (((last - first) > kQuickSortLimit) && (kRecursionCount > 0)) {
        GridEntry pivot = MedianA(*first, *(first + (last - first) / 2), *(last - 1));
        GridEntry* position = GetPartitionA(first, last, pivot);
        QuickSortImplA(position, last, --kRecursionCount);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortA(first, last, last);
}

// @ 0x00653820  quick_sort_impl<GridEntry*,int,TypeGridEntrySort>
void QuickSortImplB(GridEntry* first, GridEntry* last, int kRecursionCount) {
    while (((last - first) > kQuickSortLimit) && (kRecursionCount > 0)) {
        GridEntry* mid = first + (last - first) / 2;
        const GridEntry* p = &medianRef(*first, *mid, *(last - 1));
        GridEntry* position = GetPartitionB(first, last, *p);
        QuickSortImplB(position, last, --kRecursionCount);
        last = position;
    }
    if (kRecursionCount == 0)
        PartialSortB(first, last, last);
}

// @ 0x00653960  partial_sort<GridEntry*,CompareA>
void PartialSortA(GridEntry* first, GridEntry* middle, GridEntry* last) {
    MakeHeapA(first, middle);
    for (GridEntry* i = middle; i < last; ++i) {
        if (CompareA()(*i, *first)) {
            GridEntry temp(*i);
            *i = *first;
            AdjustHeapA(first, 0, (int)(middle - first), 0, temp);
        }
    }
    SortHeapA(first, middle);
}

// ===========================================================================
// cSPUIAssetGrid helper methods.
// ===========================================================================
extern "C" void* AssetBrowser();                       // 0x00401030
extern "C" void* FUN_00644a70(void*);                  // 0x00644a70
extern "C" int   FUN_00646030(void*, void*, void*, char);  // 0x00646030
extern "C" char  SetAssetData(void*, int);             // 0x004bbe20
extern "C" int*  FUN_00555a20(int*, int*, int*, char); // 0x00555a20
extern "C" void* FUN_0065f810(int);                    // 0x0065f810
extern "C" void* cSPUIAssetView_InitVerbCollection(void*);  // 0x004bb860
extern "C" void  fixed_vector_DoInsertValue(void*, void*, void*);  // 0x0060a600
extern "C" void* AppSystem();                          // 0x0067dd00
extern "C" void  cSPUILayout_Shutdown(void*, int);     // 0x00811ad0
extern "C" void  FUN_0065aeb0();                       // 0x0065aeb0
extern "C" void  FUN_0065fa20(void*);                  // 0x0065fa20
extern "C" void  cSPUISearchBox_Shutdown(void*);       // 0x00671c00
extern "C" void  Messaging_RemoveHandler(void*, void*, void*, void*, void*);  // 0x00571db0
extern "C" void  FUN_00659340(void*);                  // 0x00659340
extern "C" void  cSPUIAssetView_SelectAsset(void*, int, int, int, int, int);  // 0x00657a30
extern "C" void  SPUIHelpers_UpdateMouseFocus(int);    // 0x00804f50
extern "C" void  FUN_00671c50(void*);                  // 0x00671c50

// @ 0x006536e0  filter over a 0x10-byte record range (remove_if-like)
int* Filter16(int* p, int* end, int* keysBegin, int* keysEnd, char* attr) {
    for (; p != end; p += 4) {
        if (SetAssetData((void*)p[1], 0)) {
            int* lo = keysBegin;
            int n = (int)(keysEnd - keysBegin);
            while (n > 0) {
                int half = n >> 1;
                if (lo[half] < (unsigned)p[1]) {
                    lo = lo + half + 1;
                    n = n - 1 - half;
                } else {
                    n = half;
                }
            }
            if ((lo == keysEnd) || ((unsigned)p[1] < (unsigned)*lo) || (lo == lo + 1))
                break;
        }
    }
    if (keysBegin && keysBegin != (int*)attr)
        EASTL_allocator_deallocate(keysBegin);
    return p;
}

// @ 0x00653780  copy_if over a 0x10-byte record range
void* Filter16Copy(int* p, int* end, int* out, int* keysBegin, int* keysEnd, char* attr) {
    for (; p != end; p += 4) {
        if (!SetAssetData((void*)p[1], 0)) {
            // keep predicate false -> skip
        } else {
            int* lo = FUN_00555a20(keysBegin, keysEnd, p + 1, *attr);
            if (!((lo != keysEnd && *lo <= (unsigned)p[1]) && (lo != lo + 1)))
                continue;
        }
        out[0] = p[0]; out[1] = p[1]; out[2] = p[2]; out[3] = p[3];
        out += 4;
    }
    if (keysBegin && (char*)keysBegin != attr)
        EASTL_allocator_deallocate(keysBegin);
    return out;
}

// @ 0x00653b80  forward index scan
int GridScanFwd(void* self) {
    AssetBrowser();
    int* info = (int*)FUN_00644a70(0);
    int* b = (int*)info[0];
    int* e = (int*)info[1];
    if (b == e)
        return -1;
    char* gridBegin = (char*)*(void**)((char*)self + 0xe8);
    char* gridEnd = (char*)*(void**)((char*)self + 0xec);
    unsigned count = (unsigned)((gridEnd - gridBegin) >> 5);
    for (unsigned i = 0; i < count; ++i) {
        int* found = (int*)FUN_00646030(b, e, gridBegin + i * 0x20, (char)info[5]);
        if (found != e) {
            int* g = (int*)(gridBegin + i * 0x20);
            bool lt;
            if (*g != *found) lt = *g < (unsigned)*found;
            else if (g[2] != found[2]) lt = g[2] < (unsigned)found[2];
            else lt = g[1] < (unsigned)found[1];
            if (!lt && found != found + 5)
                return (int)i;
        }
    }
    return -1;
}

// @ 0x00653c40  reverse index scan
int GridScanRev(void* self) {
    AssetBrowser();
    int* info = (int*)FUN_00644a70(0);
    int* b = (int*)info[0];
    int* e = (int*)info[1];
    if (b == e)
        return -1;
    char* gridBegin = (char*)*(void**)((char*)self + 0xe8);
    char* gridEnd = (char*)*(void**)((char*)self + 0xec);
    int i = (int)((gridEnd - gridBegin) >> 5) - 1;
    for (;;) {
        int* g = (int*)(gridBegin + i * 0x20);
        int* found = (int*)FUN_00646030(b, e, g, (char)info[5]);
        if (found != e) {
            bool lt;
            if (*g != *found) lt = *g < (unsigned)*found;
            else if (g[2] != found[2]) lt = g[2] < (unsigned)found[2];
            else lt = g[1] < (unsigned)found[1];
            if (!lt && found != found + 5)
                return i;
        }
        --i;
    }
}

// @ 0x006543a0  cSPUIAssetGrid::Clear()
void GridClear(void* self) {
    char* s = (char*)self;
    void* p = *(void**)(s + 0xfc);
    if (p) {
        void* q = *(void**)((char*)p + 0x10);
        if (q)
            FUN_00659340(q);
        *(void**)(s + 0xfc) = 0;
    }
    s[0x100] = 0;
    GridVec* v = (GridVec*)(s + 0xe8);
    int count = (int)(v->mpEnd - v->mpBegin);
    for (int i = 0; i < count; ++i) {
        void* obj = *(void**)((char*)v->mpBegin + i * 0x20 + 0x10);
        if (obj)
            (*(void(__thiscall**)(void*))((char*)*(void**)obj + 0x20))(obj);
    }
    v->DoDestroyValues(v->mpBegin, v->mpEnd);
    v->mpEnd = v->mpBegin;
    *(float*)(s + 0x180) = 0.0f;
    *(float*)(s + 0x184) = 0.0f;
    *(int*)(s + 0x198) = 1;
    void* mgr = *(void**)(s + 0x18c);
    if (mgr) {
        void* w = *(void**)((char*)mgr + 0x20);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w + 0x24))(w, 0, 1);
    }
}

// @ 0x00654650  cSPUIAssetGrid::Shutdown()
void GridShutdown(void* self) {
    char* s = (char*)self;
    if (s[0x10c]) {
        void* app = AppSystem();
        (*(void(__thiscall**)(void*, int))((char*)*(void**)app + 0x40))(app, 0);
        s[0x10c] = 0;
    }
    GridClear(self);
    FUN_0065aeb0();
    void* layout = *(void**)(s + 0x18);
    if (layout) {
        cSPUILayout_Shutdown(layout, 1);
        void* p = *(void**)(s + 0x18);
        if (p) {
            *(void**)(s + 0x18) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 8))(p);
        }
    }
    void* e0 = *(void**)(s + 0xe0);
    if (e0) {
        FUN_0065fa20(e0);
        void* p = *(void**)(s + 0xe0);
        if (p) {
            *(void**)(s + 0xe0) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    void* e4 = *(void**)(s + 0xe4);
    if (e4) {
        cSPUISearchBox_Shutdown(e4);
        void* p = *(void**)(s + 0xe4);
        if (p) {
            *(void**)(s + 0xe4) = 0;
            (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
        }
    }
    void* h = *(void**)(s + 0x138);
    if (h) {
        *(void**)(s + 0x138) = 0;
        Messaging_RemoveHandler(h, *(void**)(s + 0x13c), *(void**)(s + 0x140),
                                *(void**)(s + 0x144), *(void**)(s + 0x148));
    }
}

// @ 0x00653cf0  cSPUIAssetView verb collection (PARTIAL: fixed_vector ctor +
// collect loop; the lower_bound/insert path is a skeleton).
void* VerbCollect(void* self, unsigned enabled) {
    char* s = (char*)self;
    *(void**)(s + 0x10) = s + 0x18;
    *(void**)(s + 4) = s + 0x18;
    *(void**)(s + 0) = s + 0x18;
    *(void**)(s + 8) = s + 0x18 + 0x78;
    if (!enabled)
        return self;
    void* v = FUN_0065f810(1);
    char* begin = *(char**)v;
    int n = (int)((*(char**)v + 4) - begin);
    for (unsigned i = 0; i < (unsigned)(n / 0x34); ++i) {
        void* verb = cSPUIAssetView_InitVerbCollection(*(void**)(begin + i * 0x34));
        if (verb) {
            char* end = *(char**)(s + 4);
            int* lo = FUN_00555a20((int*)*(void**)s, (int*)end, (int*)&verb, s[0x90]);
            if (lo == (int*)end) {
                // append
                *(char**)(s + 4) = end + 4;
                if (end)
                    *(void**)end = verb;
            } else if (verb < (void*)*lo) {
                fixed_vector_DoInsertValue((void*)s, lo, &verb);
            }
        }
    }
    return self;
}

// @ 0x00654100  cSPUIAssetGrid::HandleMessage (PARTIAL: large input switch).
char GridHandleMessage(void* self, int wparam, unsigned lparam) {
    (void)self; (void)wparam; (void)lparam;
    return 0;
}

