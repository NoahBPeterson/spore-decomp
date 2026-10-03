// Slice s00428900: EASTL container internals (vector of 20-byte elements, wide string
// range insert, rbtree unique insert keyed by ResourceKey) and pointer-to-member
// call thunks for the editor / updater message handlers.
// Built without optimization: /Od /Ob1 (frame pointer, every local in memory,
// only functions marked inline are expanded).
#include "types.h"
#include <new>

typedef unsigned int size_t;
extern "C" {
__declspec(dllimport) void* __cdecl memmove(void*, const void*, size_t);
void* __cdecl memcpy(void*, const void*, size_t);
}

// ---------------------------------------------------------------------------
// Pointer-to-member call thunks. Each takes (arg, object) and invokes a member
// function of an object with two polymorphic bases (an 8-byte member pointer:
// function + this adjustment).
// ---------------------------------------------------------------------------
struct MsgBaseA { virtual void a0(); };
struct MsgBaseB { virtual void b0(); };

struct EditorResource : MsgBaseA, MsgBaseB {
    void Setup(int);          // 0x00418ae0
    void NotifyA(int);        // 0x00418f90
    void NotifyB(int);        // 0x00418fd0
    void Handler419000(int);  // 0x00419000
    void Handler419690(int);  // 0x00419690
};
struct Updater : MsgBaseA, MsgBaseB {
    void UpdateModels(int);   // 0x00419780
    void Dispatch(int);       // 0x00419ff0
    void Handler41A0C0(int);  // 0x0041a0c0
};

// @ 0x00428ec0
void __cdecl CallEditorSetup(int arg, EditorResource* obj)
{
    void (EditorResource::*pmf)(int) = &EditorResource::Setup;
    (obj->*pmf)(arg);
}

// @ 0x00428f00
void __cdecl CallEditorNotifyA(int arg, EditorResource* obj)
{
    void (EditorResource::*pmf)(int) = &EditorResource::NotifyA;
    (obj->*pmf)(arg);
}

// @ 0x00428f40
void __cdecl CallEditorHandler419000(int arg, EditorResource* obj)
{
    void (EditorResource::*pmf)(int) = &EditorResource::Handler419000;
    (obj->*pmf)(arg);
}

// @ 0x00428f80
void __cdecl CallEditorHandler419690(int arg, EditorResource* obj)
{
    void (EditorResource::*pmf)(int) = &EditorResource::Handler419690;
    (obj->*pmf)(arg);
}

// @ 0x00428fc0
void __cdecl CallEditorNotifyB(int arg, EditorResource* obj)
{
    void (EditorResource::*pmf)(int) = &EditorResource::NotifyB;
    (obj->*pmf)(arg);
}

// @ 0x00429000
void __cdecl CallUpdaterUpdateModels(int arg, Updater* obj)
{
    void (Updater::*pmf)(int) = &Updater::UpdateModels;
    (obj->*pmf)(arg);
}

// @ 0x00429040
void __cdecl CallUpdaterDispatch(int arg, Updater* obj)
{
    void (Updater::*pmf)(int) = &Updater::Dispatch;
    (obj->*pmf)(arg);
}

// @ 0x00429080
void __cdecl CallUpdaterHandler41A0C0(int arg, Updater* obj)
{
    void (Updater::*pmf)(int) = &Updater::Handler41A0C0;
    (obj->*pmf)(arg);
}

// ---------------------------------------------------------------------------
// EASTL allocator entry points (shared across the binary).
// ---------------------------------------------------------------------------
extern void* __cdecl EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int align, const char* file, int line);
extern void __cdecl EASTL_allocator_deallocate(void* p);

// ---------------------------------------------------------------------------
// vector<Elem20>::DoInsertValue(position, value)
// ---------------------------------------------------------------------------
struct Elem20 { uint32_t v[5]; };
extern Elem20* __cdecl AllocElems(void* alloc, uint32_t bytes, uint32_t align, uint32_t off);  // 0x0042dee0
extern Elem20* __cdecl UninitMove(Elem20* first, Elem20* last, Elem20* dest);                    // 0x0047b3d0

typedef const bool& TagRef;
__forceinline Elem20* move_backward_impl(Elem20* first, Elem20* last, Elem20* resultEnd, TagRef, TagRef, TagRef)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
__forceinline Elem20* copy_backward(Elem20* first, Elem20* last, Elem20* resultEnd)
{
    return move_backward_impl(first, last, resultEnd, false, false, false);
}
__forceinline void Dealloc(void* const& p) { EASTL_allocator_deallocate(p); }
__forceinline void DoFree(Elem20* p, uint32_t n)
{
    if (p && ((int*)p)[-1])
        Dealloc(p);
}
// Reserves stack the way the original's inlined helpers did (unused locals at /Od).
__forceinline void ReserveInlineStack() { volatile uint32_t pad[16]; (void)pad; }

struct Vec20 {
    Elem20* mBegin; Elem20* mEnd; Elem20* mCap; uint32_t mAlloc;
    void DoInsertValue(Elem20* position, const Elem20& value);
};

// @ 0x00428900
void Vec20::DoInsertValue(Elem20* position, const Elem20& value)
{
    if (mEnd != mCap) {
        const Elem20* pValue = &value;
        if (pValue >= position && pValue < mEnd)
            ++pValue;
        new(mEnd) Elem20(*(mEnd - 1));
        copy_backward(position, mEnd - 1, mEnd);
        *position = *pValue;
        ++mEnd;
    } else {
        const uint32_t prev = (uint32_t)(mEnd - mBegin);
        const uint32_t newSize = prev > 0 ? prev * 2 : 1;
        Elem20* pNewData = newSize ? AllocElems(&mAlloc, newSize * 20, 4, 0) : 0;
        Elem20* pNewEnd = UninitMove(mBegin, position, pNewData);
        new(pNewEnd) Elem20(value);
        ++pNewEnd;
        pNewEnd = UninitMove(position, mEnd, pNewEnd);
        ReserveInlineStack();
        DoFree(mBegin, (uint32_t)(mCap - mBegin));
        mBegin = pNewData; mEnd = pNewEnd; mCap = pNewData + newSize;
    }
}

// ---------------------------------------------------------------------------
// basic_string<wchar_t>::insert(p, pBegin, pEnd)
// ---------------------------------------------------------------------------
template <class T> inline const T& emax(const T& a, const T& b) { return (a < b) ? b : a; }

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
__forceinline wchar_t* UCopy(const wchar_t* first, const wchar_t* last, wchar_t* dest)
{
    memcpy(dest, first, (size_t)(last - first) * 2);
    return dest + (last - first);
}
__forceinline void* AllocRaw(uint32_t n)
{
    return EASTL_allocator_allocate(n, "Editor", 0, 0, ALLOC_FILE, 0xd1);
}
__forceinline wchar_t* DoAlloc(uint32_t n)
{
    void* p = AllocRaw(n * 2);
    return (wchar_t*)p;
}
__forceinline void ReserveInlineStack3() { volatile uint32_t pad[3]; (void)pad; }

struct WString {
    wchar_t* mBegin; wchar_t* mEnd; wchar_t* mCap; uint32_t mAlloc; wchar_t* mLocal;
    void DeallocateSelf();  // 0x004292a0
    void Insert(wchar_t* p, const wchar_t* pBegin, const wchar_t* pEnd);
};

// @ 0x00428b90
void WString::Insert(wchar_t* p, const wchar_t* pBegin, const wchar_t* pEnd)
{
    const int n = (int)(pEnd - pBegin);
    if (n) {
        const bool bCapacityIsSufficient = ((mCap - mEnd) >= (n + 1));
        const bool bSourceIsFromSelf = ((pEnd >= mBegin) && (pBegin <= mEnd));
        if (bCapacityIsSufficient && !bSourceIsFromSelf) {
            const int nElementsAfter = (int)(mEnd - p);
            wchar_t* pOldEnd = mEnd;
            if (nElementsAfter >= n) {
                memmove(mEnd + 1, mEnd - n + 1, n * 2);
                mEnd += n;
                memmove(p + n, p, (nElementsAfter - n + 1) * 2);
                memcpy(p, pBegin, (pEnd - pBegin) * 2);
            } else {
                const wchar_t* pTemp = pBegin + nElementsAfter + 1;
                memmove(mEnd + 1, pTemp, (pEnd - pTemp) * 2);
                mEnd += n - nElementsAfter;
                memmove(mEnd, p, (pOldEnd - p) * 2 + 2);
                mEnd += nElementsAfter;
                memcpy(p, pBegin, (pTemp - pBegin) * 2);
            }
        } else {
            int nOldSize; uint32_t nOldCap; uint32_t nNewLen; wchar_t* pNewBegin; wchar_t* pNewEnd;
            nOldSize = (int)(mEnd - mBegin);
            nOldCap = (uint32_t)(mCap - mBegin) - 1;
            if (bCapacityIsSufficient) {
                nNewLen = nOldSize + n + 1;
            } else {
                const uint32_t nLen = nOldSize + n;
                const uint32_t nGrow = (nOldCap > 8) ? nOldCap * 2 : 8;
                nNewLen = emax(nGrow, nLen) + 1;
            }
            pNewBegin = DoAlloc(nNewLen);
            pNewEnd = pNewBegin;
            pNewEnd = UCopy(mBegin, p, pNewBegin);
            pNewEnd = UCopy(pBegin, pEnd, pNewEnd);
            pNewEnd = UCopy(p, mEnd, pNewEnd);
            *pNewEnd = 0;
            ReserveInlineStack3();
            DeallocateSelf();
            mBegin = pNewBegin; mEnd = pNewEnd; mCap = pNewBegin + nNewLen;
        }
    }
}

// ---------------------------------------------------------------------------
// rbtree<ResourceKey>::DoInsertValue(value, true_type): unique insert
// ---------------------------------------------------------------------------
struct ResKey { uint32_t instance, type, group; };
struct Node { Node* right; Node* left; Node* parent; uint32_t color; ResKey value; };
struct Iter { Node* mp; Iter(Node* n); };  // out-of-line ctor at 0x00566c50
struct TrueType {};
struct PairIB {
    Iter first; bool second;
    PairIB(const Iter& a, const bool& b) : first(a), second(b) {}
};
extern Node* __cdecl RBTreeDecrement(Node* n);  // 0x009215c0

__forceinline bool KeyLess(const ResKey& a, const ResKey& b)
{
    bool r;
    if (a.instance != b.instance) r = a.instance < b.instance;
    else if (a.group != b.group) r = a.group < b.group;
    else r = a.type < b.type;
    return r;
}

struct Tree {
    uint32_t mCompare;
    Node mAnchor;
    Iter DoInsertValueImpl(Node* parent, const ResKey& v, bool forceLeft);  // 0x0042c1c0
    PairIB DoInsertValue(const ResKey& value, const TrueType&);
};

// @ 0x004290c0
PairIB Tree::DoInsertValue(const ResKey& value, const TrueType&)
{
    Node* pUnused;
    Node* pCurrent = mAnchor.parent;
    Node* pLowerBound = &mAnchor;
    bool bValueLessThanNode = true;
    while (pCurrent) {
        bValueLessThanNode = KeyLess(value, pCurrent->value);
        pLowerBound = pCurrent;
        if (bValueLessThanNode) pCurrent = pCurrent->left;
        else pCurrent = pCurrent->right;
    }
    Node* pParent = pLowerBound;
    if (bValueLessThanNode) {
        if (pLowerBound != mAnchor.left)
            pLowerBound = RBTreeDecrement(pLowerBound);
        else
        { Iter itA = DoInsertValueImpl(pLowerBound, value, false); return PairIB(itA, true); }
    }
    if (KeyLess(pLowerBound->value, value))
    { Iter itB = DoInsertValueImpl(pParent, value, false); return PairIB(itB, true); }
    return PairIB(Iter(pLowerBound), false);
}
