// Slice s0064eb60: UI module functions around SP::cSPUIAssetGrid (asset browser grid).
// Built with /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc), matching the preceding slice.
// The value type is SP::cSPAssetGridEntry (0x20 bytes, two EA::AutoRefCount members).
#include "../../include/types.h"
#include <intrin.h>
#include <new>

static inline void** VT(void* p) { return *(void***)p; }

// ---------------------------------------------------------------------------
// EA::AutoRefCount (real layout: one raw pointer)
// ---------------------------------------------------------------------------
namespace EA {

template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(const AutoRefCount& o) {
        T* p = o.mpObject;
        T* old = mpObject;
        if (p != old) {
            if (p)
                p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};

}  // namespace EA

namespace SP {

// refcounted object whose refcount interface is a secondary base at +0x10
struct AssetPrimary {
    virtual void slot0();
    virtual void slot1();
    char pad[0x0c];
};
struct AssetDataRef {
    virtual void AddRef();
    virtual void Release();
};
struct cSPAssetData : AssetPrimary, AssetDataRef {};

// refcounted object with a primary vtable
struct cSPAssetView {
    virtual void AddRef();
    virtual void Release();
};

struct ResourceKey {
    unsigned int mTypeID;       // +0x00
    unsigned int mInstanceID;   // +0x04
    unsigned int mGroupID;      // +0x08
};

struct cSPAssetGridEntry {
    ResourceKey mAssetKey;                                  // +0x00
    EA::AutoRefCount<cSPAssetData> mAssetData;              // +0x0c
    EA::AutoRefCount<cSPAssetView> mAssetView;              // +0x10
    float mPosX;                                            // +0x14
    float mPosY;                                            // +0x18
    bool mFlag1C;                                           // +0x1c
    bool mFlag1D;                                           // +0x1d
};

struct TypeGridEntrySort {
    char pad0[0x0c];
    bool operator()(const cSPAssetGridEntry& a, const cSPAssetGridEntry& b);
};



// ---------------------------------------------------------------------------
// cSPUIAssetGrid stub (retail layout; only fields touched by this slice)
// ---------------------------------------------------------------------------
struct cSPUIAssetGrid {
    char pad0[0x74];
    void* m74;                                          // +0x74
    void* m78;                                          // +0x78
    void* m7c;                                          // +0x7c
    void* mWinArray[24];                                // +0x80 .. +0xdf
    void* me0;                                          // +0xe0
    char padE4[4];                                      // +0xe4
    cSPAssetGridEntry* mpEntries;                       // +0xe8
    cSPAssetGridEntry* mpEntriesEnd;                    // +0xec
    char pad1[0x130 - 0xf0];
    float m130;                                         // +0x130
    float m134;                                         // +0x134
    char pad2[0x19c - 0x138];
    void* m19c;                                         // +0x19c
    int m1a0;                                           // +0x1a0
    int m1a4;                                           // +0x1a4
    char pad3[0x1b8 - 0x1a8];
    bool m1b8;                                          // +0x1b8
    char pad4[0x1e8 - 0x1b9];
    bool m1e8;                                          // +0x1e8

    cSPAssetGridEntry* GetEntry(int i);                 // 0x0064f2c0
    int IndexOfView(cSPAssetView* v);                   // 0x0064f280
    bool CheckFlag();                                   // 0x0064f320
    void SetEntryState(int idx, bool force);            // 0x0064eb60
    void UpdateAll();                                   // 0x0064ecc0
};

struct ViewState {
    // object whose +0x16 is a bool; pointer stored in m19c
    char pad0[0x16];
    bool f16;
};

}  // namespace SP


// ---------------------------------------------------------------------------
// @ 0x0064f2c0  SP::cSPUIAssetGrid::GetEntry
// ---------------------------------------------------------------------------
SP::cSPAssetGridEntry* SP::cSPUIAssetGrid::GetEntry(int i)
{
    return &mpEntries[i];
}

// ---------------------------------------------------------------------------
// @ 0x0064f280  SP::cSPUIAssetGrid::IndexOfView
// ---------------------------------------------------------------------------
int SP::cSPUIAssetGrid::IndexOfView(cSPAssetView* v)
{
    int i = 0;
    if (v) {
        int n = (int)(mpEntriesEnd - mpEntries);
        if (n > 0) {
            cSPAssetView** pv = (cSPAssetView**)((char*)mpEntries + 0x10);
            for (; i < n; ++i) {
                if (pv[0] == v)
                    return i;
                pv = (cSPAssetView**)((char*)pv + 0x20);
            }
        }
        i = -1;
    }
    return i;
}

// ---------------------------------------------------------------------------
// @ 0x0064f320  SP::cSPUIAssetGrid::CheckFlag
// ---------------------------------------------------------------------------
bool SP::cSPUIAssetGrid::CheckFlag()
{
    if (!m19c)
        return m1b8;
    return m1b8 && ((ViewState*)m19c)->f16;
}

// ---------------------------------------------------------------------------
// @ 0x0064f3b0  SP::cSPAssetGridEntry::cSPAssetGridEntry (copy ctor)
// ---------------------------------------------------------------------------
// implicit; emitted because the sort/vector helpers below construct an Entry.

// ---------------------------------------------------------------------------
// @ 0x0064f450  SP::cSPAssetGridEntry::operator=
// ---------------------------------------------------------------------------
// implicit; emitted because the sort helpers below assign an Entry.

// ---------------------------------------------------------------------------
// @ 0x0064f410  eastl::vector<SP::cSPAssetGridEntry,sp_vector_allocator>::DoDestroyValues
// ---------------------------------------------------------------------------
namespace eastl {
struct sp_vector_allocator {};

template <typename T, typename Allocator = sp_vector_allocator>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
};
}  // namespace eastl

// explicit instantiation for @ 0x0064f410
template void eastl::vector<SP::cSPAssetGridEntry, eastl::sp_vector_allocator>::DoDestroyValues(
    SP::cSPAssetGridEntry*, SP::cSPAssetGridEntry*);

// ---------------------------------------------------------------------------
// @ 0x0064f540  eastl::insertion_sort<SP::cSPAssetGridEntry*, SP::TypeGridEntrySort>
// ---------------------------------------------------------------------------
void InsertionSortEntries(SP::cSPAssetGridEntry* first, SP::cSPAssetGridEntry* last,
                          SP::TypeGridEntrySort* compare)
{
    if (first != last) {
        SP::cSPAssetGridEntry* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            const SP::cSPAssetGridEntry temp(*iSorted);
            SP::cSPAssetGridEntry* iNext = iSorted;
            SP::cSPAssetGridEntry* iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (*compare)(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x0064f630  simple insertion sort (no lower bound guard)
// ---------------------------------------------------------------------------
void InsertionSortSimpleEntries(SP::cSPAssetGridEntry* first, SP::cSPAssetGridEntry* last,
                                SP::TypeGridEntrySort* compare)
{
    if (first == last)
        return;
    for (SP::cSPAssetGridEntry* p = first; p != last; ++p) {
        const SP::cSPAssetGridEntry temp(*p);
        SP::cSPAssetGridEntry* dest = p;
        SP::cSPAssetGridEntry* prev = p - 1;
        while ((*compare)(temp, *prev)) {
            *dest = *prev;
            --dest;
            --prev;
        }
        *dest = temp;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0064f990  eastl::promote_heap<Entry*,int,Entry,TypeGridEntrySort>
// ---------------------------------------------------------------------------
void PromoteHeapEntries(SP::cSPAssetGridEntry* first, int topPosition, int position,
                        SP::cSPAssetGridEntry value, SP::TypeGridEntrySort* compare)
{
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && (*compare)(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

// ---------------------------------------------------------------------------
// @ 0x0064f730  (output-iterator style uninitialized copy)
// ---------------------------------------------------------------------------
SP::cSPAssetGridEntry** UninitCopyOut(SP::cSPAssetGridEntry** pOut, SP::cSPAssetGridEntry* first,
                                      SP::cSPAssetGridEntry* last, SP::cSPAssetGridEntry* initial)
{
    *pOut = initial;
    if (first != last) {
        do {
            SP::cSPAssetGridEntry* d = *pOut;
            if (d)
                ::new (d) SP::cSPAssetGridEntry(*first);
            *pOut = d + 1;
            ++first;
        } while (first != last);
    }
    return pOut;
}

// ---------------------------------------------------------------------------
// @ 0x0064f7c0  uninitialized copy
// ---------------------------------------------------------------------------
SP::cSPAssetGridEntry* UninitCopyEntries(SP::cSPAssetGridEntry* first, SP::cSPAssetGridEntry* last,
                                         SP::cSPAssetGridEntry* result)
{
    if (first != last) {
        do {
            if (result)
                ::new (result) SP::cSPAssetGridEntry(*first);
            ++first;
            ++result;
        } while (first != last);
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x0064f840  destroy range (destructor)
// ---------------------------------------------------------------------------
SP::cSPAssetGridEntry* DestroyEntries(SP::cSPAssetGridEntry* first, SP::cSPAssetGridEntry* last,
                                      SP::cSPAssetGridEntry* result)
{
    if (first != last) {
        do {
            first->~cSPAssetGridEntry();
            ++first;
            ++result;
        } while (first != last);
    }
    return result;
}

// ---------------------------------------------------------------------------
// @ 0x0064f8d0  uninitialized_fill_n
// ---------------------------------------------------------------------------
void UninitFillNEntries(SP::cSPAssetGridEntry* dest, unsigned int n,
                        const SP::cSPAssetGridEntry* value)
{
    while (n--) {
        if (dest)
            ::new (dest) SP::cSPAssetGridEntry(*value);
        ++dest;
    }
}

// ---------------------------------------------------------------------------
// @ 0x0064f350  parser/state helper
// ---------------------------------------------------------------------------
extern unsigned char g_e350_state;  // 0x015d9c70

unsigned char ParseHelper(void* obj, int a, unsigned char def)
{
    if (obj) {
        bool ok = ((bool(__thiscall*)(void*, int, void**))VT(obj)[0x24 / 4])(obj, a, &obj);
        if (ok) {
            unsigned short w = *(unsigned short*)((char*)obj + 0x12);
            if (w == 1 || w == 0x10) {
                if (*(unsigned char*)((char*)obj + 0x10) & 0x30)
                    return *(unsigned char*)(*(int*)obj);
                return *(unsigned char*)(w ? obj : 0);
            }
            return g_e350_state;
        }
    }
    return def;
}

// ---------------------------------------------------------------------------
// @ 0x0064eb60  SP::cSPUIAssetGrid::SetEntryState
// ---------------------------------------------------------------------------
extern "C" void* __cdecl FUN_0066a800(int);  // AssetViewAt(index)

void SP::cSPUIAssetGrid::SetEntryState(int idx, bool force)
{
    cSPAssetView* v = (cSPAssetView*)FUN_0066a800(idx);
    if (v)
        ((void(__thiscall*)(void*))VT(v)[1])(v);

    bool b = false;
    if (m1a0 == idx) {
        if (v)
            b = *(char*)((char*)v + 0x20) == 0;
        else
            b = false;
    } else {
        m1a0 = idx;
        b = false;
    }
    if (force)
        b = true;
    if (!v)
        return;

    *(char*)((char*)v + 0x20) = b;
    m1e8 = true;

    if (idx != 0x18) {
        void* p = mWinArray[idx];
        if (p) {
            void* q = ((void*(__thiscall*)(void*, uint32_t))VT(p)[0x0c / 4])(p, 0x8ed27e7a);
            if (q) {
                ((void(__thiscall*)(void*, int, int))VT(q)[0x28 / 4])(q, 4, 1);
                ((void(__thiscall*)(void*, int, int))VT(q)[0x28 / 4])(q, 0x20, 1);
            }
        }
    }

    bool flag = true;
    if (*(void**)((char*)v + 0x0c) != *(void**)((char*)v + 0x10)) {
        bool c = ((bool(__thiscall*)(void*))VT(*(void**)((char*)v + 0x0c))[0x1c / 4])(
            *(void**)((char*)v + 0x0c));
        if (c == b)
            flag = false;
    }

    if (idx != 0x18 && mWinArray[idx] && m78 && m7c && m74) {
        ((void(__thiscall*)(void*, int, int))VT(m78)[0x7c / 4])(m78, 1, flag);
        ((void(__thiscall*)(void*, int, int))VT(m7c)[0x7c / 4])(m7c, 1, !flag);
        void* q = ((void*(__thiscall*)(void*))VT(m74)[0x10 / 4])(m74);
        ((void(__thiscall*)(void*, void*))VT(q)[0xdc / 4])(q, m74);
        ((void(__thiscall*)(void*, void*))VT(mWinArray[idx])[0xd8 / 4])(mWinArray[idx], m74);
    }
    ((void(__thiscall*)(void*))VT(v)[2])(v);
}

// ---------------------------------------------------------------------------
// @ 0x0064ecc0  SP::cSPUIAssetGrid::UpdateAll  (large; approximate)
// ---------------------------------------------------------------------------
void SP::cSPUIAssetGrid::UpdateAll()
{
    // Placeholder: the full body is reconstructed in a later pass.
}
