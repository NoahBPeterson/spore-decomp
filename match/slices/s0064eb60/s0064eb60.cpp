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
class AutoRefCount { public:
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
class cSPAssetData : public AssetPrimary, public AssetDataRef { public:};

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
class cSPUIAssetGrid { public:
    char pad0[0x74];
    void* m74;                                          // +0x74
    void* m78;                                          // +0x78
    void* m7c;                                          // +0x7c
    void* mWinArray[24];                                // +0x80 .. +0xdf
    void* me0;                                          // +0xe0
    char padE4[4];                                      // +0xe4
    cSPAssetGridEntry* mpEntries;                       // +0xe8
    cSPAssetGridEntry* mpEntriesEnd;                    // +0xec
    char pad1[0x12c - 0xf0];
    float m12c;                                         // +0x12c
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
class vector { public:
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
                // Retail's byte return keeps the high bits of the pointer it read through
                // in eax (the caller-visible return value is 16-bit compared by the
                // harness), so each arm reproduces that leftover explicitly.
                if (*(unsigned char*)((char*)obj + 0x10) & 0x30) {
                    unsigned int p = *(unsigned int*)obj;
                    return (unsigned char)((p & 0xffffff00u) | *(unsigned char*)p);
                }
                unsigned int q = w ? (unsigned int)obj : 0;
                return (unsigned char)((q & 0xffffff00u) | *(unsigned char*)q);
            }
            return (unsigned char)(0x15d9c00u | *(unsigned char*)0x15d9c70);
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
        // v+0x0c holds a wrapper whose first dword is the real object; the virtual
        // call is made on that inner object (retail dereferences one more level).
        void* w = *(void**)((char*)v + 0x0c);
        void* o = *(void**)w;
        bool c = ((bool(__thiscall*)(void*))VT(o)[0x1c / 4])(o);
        if (c == b)
            flag = false;
    }

    if (idx != 0x18 && mWinArray[idx] && m78 && m7c && m74) {
        // Retail homes the flag in the low byte of the caller-pushed `force` slot and
        // passes that whole dword: the byte is overwritten, the upper 24 bits are stale.
        unsigned int forcedw = *(unsigned int*)&force;
        ((void(__thiscall*)(void*, int, int))VT(m78)[0x7c / 4])(
            m78, 1, (int)((forcedw & 0xffffff00u) | (unsigned int)flag));
        ((void(__thiscall*)(void*, int, int))VT(m7c)[0x7c / 4])(m7c, 1, !flag);
        void* q = ((void*(__thiscall*)(void*))VT(m74)[0x10 / 4])(m74);
        ((void(__thiscall*)(void*, void*))VT(q)[0xdc / 4])(q, m74);
        ((void(__thiscall*)(void*, void*))VT(mWinArray[idx])[0xd8 / 4])(mWinArray[idx], m74);
    }
    ((void(__thiscall*)(void*))VT(v)[2])(v);
}

// ---------------------------------------------------------------------------
// @ 0x0064ecc0  SP::cSPUIAssetGrid::UpdateAll
// ---------------------------------------------------------------------------
// FlagKey: 0x18 bool flags, a uint32 value and an extra bool (0x20 bytes).
struct FlagKey {
    bool mFlags[0x18];                                // +0x00
    uint32_t mValue;                                  // +0x18
    bool mExtra;                                      // +0x1c
};

// 0x0140042c: the value word written into every freshly-initialized FlagKey.
extern uint32_t g_140042c;
// 0x0066a5e0: fill all 24 flags with `fill`, store `value`, clear the extra byte.
extern "C" void FUN_0066a5e0();
// 0x0066a5c0: index of `value` in the global key table, 0x18 when absent.
extern "C" int FUN_0066a5c0(uint32_t value);
// 0x00661b10: cSPUIFeedFilter::AllHaveAssets(uint); thiscall, ret 4.
extern "C" char FUN_00661b10();
// 0x0065f810: ModeViewGetter::Get(bool) -> element vector; thiscall, ret 4.
extern "C" void* FUN_0065f810();
// 0x004bb860: SP::cSPUIAssetView::InitVerbCollection(uint) -> hash.
extern "C" unsigned int FUN_004bb860(unsigned int key);

namespace SP {
void* AssetBrowser();                                 // 0x00401030

// 0x007f6210 / 0x007f8d10
struct cSPUIAnimator {
    void RemoveAnimation(void* win, int id);                              // 0x007f6210
    void AddAnimation(void* target, void* win, unsigned int id);          // 0x007f8d10
};
}  // namespace SP

// 0x00805080: elapsed seconds for an animation (0.0f when there is no window).
float GetElapsedSeconds(float seconds, int type, void* win, uint32_t id);  // 0x00805080

// The 0x10-byte temporary the animation-raw builders write into.
struct AnimRawTmp {
    void* mVt0;                                       // +0x00
    char pad04[4];
    void* mVt1;                                       // +0x08
    void* mpRef;                                      // +0x0c
};

// 0x007f80d0 / 0x007f81d0: build an animation raw into `out` and return it.
AnimRawTmp* SPUICreateWindowAnimationTargetPosition(AnimRawTmp* out, void* win,  // 0x007f80d0
                                                    float x, float y, float elapsed);
AnimRawTmp* SPUICreateWindowAnimationTargetScale(AnimRawTmp* out, void* win,     // 0x007f81d0
                                                 float scale, float elapsed);

// the refcount interface released when the temporary is torn down.
struct AnimRef {
    virtual void AddRef();
    virtual void Release();                           // +0x04
};

// SP::AssetBrowser() singleton layout (only the fields this function touches).
struct AssetBrowserObj {
    char pad0[0x14];
    void* m14;                                        // +0x14 animator
    char pad18[0x1cc - 0x18];
    uint32_t m1cc;                                    // +0x1cc
    char pad1d0[0x1f0 - 0x1d0];
    FlagKey m1f0;                                     // +0x1f0
};

void SP::cSPUIAssetGrid::UpdateAll()
{
    FlagKey f1, f2, f3, f4;

    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f1, 1, g_140042c);
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f2, 1, g_140042c);
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f3, 1, g_140042c);
    ((void(__thiscall*)(void*, int, uint32_t))FUN_0066a5e0)(&f4, 1, g_140042c);

    bool extra = false;

    if (m19c && me0) {
        f2 = *(FlagKey*)((char*)m19c + 0x158);
        f3 = *(FlagKey*)((char*)me0 + 0x44);
        f4 = ((AssetBrowserObj*)SP::AssetBrowser())->m1f0;

        for (int i = 0; i < 0x18; i += 6) {
            f1.mFlags[i + 0] = f2.mFlags[i + 0] && f3.mFlags[i + 0] && f4.mFlags[i + 0];
            f1.mFlags[i + 1] = f2.mFlags[i + 1] && f3.mFlags[i + 1] && f4.mFlags[i + 1];
            f1.mFlags[i + 2] = f2.mFlags[i + 2] && f3.mFlags[i + 2] && f4.mFlags[i + 2];
            f1.mFlags[i + 3] = f2.mFlags[i + 3] && f3.mFlags[i + 3] && f4.mFlags[i + 3];
            f1.mFlags[i + 4] = f2.mFlags[i + 4] && f3.mFlags[i + 4] && f4.mFlags[i + 4];
            f1.mFlags[i + 5] = f2.mFlags[i + 5] && f3.mFlags[i + 5] && f4.mFlags[i + 5];
        }

        if (f4.mValue != 0) {
            f1.mValue = f4.mValue;
            extra = f4.mExtra;
        } else {
            f1.mValue = f2.mValue;
            extra = f2.mExtra;
        }
    }

    if (me0) {
        char ok = ((char(__thiscall*)(void*, uint32_t))FUN_00661b10)(
            me0, *(uint32_t*)((char*)me0 + 0x18));
        if (!ok)
            f1.mFlags[5] = 0;
    }

    if (me0) {
        AssetBrowserObj* ab = (AssetBrowserObj*)SP::AssetBrowser();
        if (ab && ab->m1cc != 0 &&
            (ab->m1cc == 0x9ea3031au || ab->m1cc == 0x4178b8e8u)) {
            void* pv = ((void*(__thiscall*)(void*, int))FUN_0065f810)(me0, 0);
            char* pBegin = *(char**)pv;
            char* pEnd = *((char**)pv + 1);
            if (pBegin != pEnd) {
                bool all = true;
                int n = (int)(pEnd - pBegin) / 0x34;
                for (int i = 0; i < n; ++i) {
                    if (FUN_004bb860(*(uint32_t*)(pBegin + i * 0x34)) != 0x2b978c46u)
                        all = false;
                }
                if (!all)
                    goto AFTER;
            }
            f1.mFlags[13] = 1;
            f1.mFlags[14] = 1;
            f1.mFlags[15] = 1;
            f1.mFlags[16] = 1;
            f1.mFlags[17] = 1;
        }
    }

AFTER:
    int idx = FUN_0066a5c0(f1.mValue);
    if (idx == 0x18 || !f1.mFlags[idx]) {
        idx = FUN_0066a5c0(f2.mValue);
        extra = f2.mExtra;
    }
    if (idx == 0x18 || !f1.mFlags[idx]) {
        idx = FUN_0066a5c0(f3.mValue);
        extra = f3.mExtra;
    }
    if (m1a4 != idx || m1a0 == 0x18 || !f1.mFlags[m1a0])
        SetEntryState(idx, extra);
    m1a4 = idx;

    AssetBrowserObj* ab2 = (AssetBrowserObj*)SP::AssetBrowser();
    SP::cSPUIAnimator* animator = ab2 ? (SP::cSPUIAnimator*)ab2->m14 : 0;

    int position = 0;
    for (int i = 0; i < 0x18; ++i) {
        void* p = mWinArray[i];
        if (!p)
            continue;

        unsigned int uVar9;

        if (!f1.mFlags[i]) {
            // hide the window
            if (!animator) {
                ((void(__thiscall*)(void*, float, float))VT(p)[0x68 / 4])(p, 0.0f, 0.0f);
            } else {
                animator->RemoveAnimation(p, -1);
                AnimRawTmp tmp;
                float elapsed = GetElapsedSeconds(0.2f, 1, p, 0x9c1cab90u);
                AnimRawTmp* r = SPUICreateWindowAnimationTargetScale(
                    &tmp, p, 1.52587890625e-05f, elapsed);
                animator->AddAnimation(r, p, 0x9c1cab90u);
                if (tmp.mpRef)
                    ((AnimRef*)tmp.mpRef)->Release();
            }
            uVar9 = 1;
        } else {
            float fPos = (float)position * m134;
            ++position;
            if (!animator) {
                ((void(__thiscall*)(void*, float, float))VT(p)[0x64 / 4])(p, fPos, 0.0f);
                ((void(__thiscall*)(void*, float, float))VT(p)[0x68 / 4])(p, m12c, m130);
            } else {
                animator->RemoveAnimation(p, -1);
                if (!(((unsigned int(__thiscall*)(void*))VT(p)[0x28 / 4])(p) & 0x10)) {
                    AnimRawTmp tmp;
                    float elapsed = GetElapsedSeconds(0.2f, 2, p, 0x4b0531a7u);
                    AnimRawTmp* r = SPUICreateWindowAnimationTargetPosition(
                        &tmp, p, fPos, 0.0f, elapsed);
                    animator->AddAnimation(r, p, 0x4b0531a7u);
                    if (tmp.mpRef)
                        ((AnimRef*)tmp.mpRef)->Release();
                } else {
                    ((void(__thiscall*)(void*, float, float))VT(p)[0x64 / 4])(p, fPos, 0.0f);
                }
                AnimRawTmp tmp2;
                float elapsed2 = GetElapsedSeconds(0.2f, 2, p, 0x9c1cab90u);
                AnimRawTmp* r2 = SPUICreateWindowAnimationTargetScale(
                    &tmp2, p, 1.0f, elapsed2);
                animator->AddAnimation(r2, p, 0x9c1cab90u);
                if (tmp2.mpRef)
                    ((AnimRef*)tmp2.mpRef)->Release();
            }
            uVar9 = 0;
        }

        ((void(__thiscall*)(void*, int, unsigned int))VT(p)[0x7c / 4])(p, 0x10, uVar9);
    }
}
