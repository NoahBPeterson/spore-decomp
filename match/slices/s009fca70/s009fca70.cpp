// slice s009fca70 -- SPCreatureAnim/parts_caps.obj: EASTL heap/sort/vector instantiations for
// nSPCreatureAnim::capability_name, the two AnimCommand Execute bodies, and two map operator[]
// instantiations.
//
//   VA 0x009fca70  copy_backward_impl::do_copy<Elem14*>
//   VA 0x009fcac0  eastl::swap<Elem14>
//   VA 0x009fcb30  cDeformSpecBlockCommand::Execute
//   VA 0x009fcc10  vector<deform_description>::DoInsertValues
//   VA 0x009fcdb0  eastl::insertion_sort<Elem14*, cmp>
//   VA 0x009fcef0  eastl::Internal::insertion_sort_simple<Elem14*, cmp>
//   VA 0x009fd040  eastl::adjust_heap<Elem14*, cmp>
//   VA 0x009fd1a0  eastl::pop_heap<Elem14*, cmp>
//   VA 0x009fd3d0  eastl::make_heap<Elem14*, cmp>
//   VA 0x009fd4d0  eastl::sort_heap<Elem14*, cmp>
//   VA 0x009fd5a0  eastl::get_partition<Elem14*, cmp>
//   VA 0x009fd620  eastl::partial_sort<Elem14*, cmp>
//   VA 0x009fd7f0  vector4 copy-construct (1 source)
//   VA 0x009fd840  cDeformBlockCommand::Execute
//   VA 0x009fd950  rbtree<u32,...>::operator[] (variant 1)
//   VA 0x009fd9e0  rbtree<u32,...>::operator[] (variant 2)
//   VA 0x009fdab0  vector4 copy-construct (2 sources)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// ---------------------------------------------------------------- imported helpers
extern void*  EAAllocate(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern void   ElemFree(void* p);                       // 0x00f47380  operator delete
extern void*  DoInsertValue(void* dst, const void* src, uint32 n);   // 0x011e0744  memcpy-like
extern void*  UninitCopy16(void** out, const void* first, const void* last, void* dst);  // 0x007f1890
extern void*  UninitMove16(const void* first, const void* last, void* dst);              // 0x00c7ea30
extern void   CopyBackward16(void* dst, void* first, void* last);                        // 0x00edba80
extern void   Fill16(void* first, void* last, const void* value);                        // 0x00898580
extern void   UninitFillN16(void* dst, uint32 n, const void* value);                     // 0x0088f820
struct VecImpl { void DoAllocate(uint32 n, const void* allocSrc); };                      // 0x004aa350 thiscall
extern uint32 FNV1String8(const char* s, uint32 seed, int a);   // 0x00932e80
extern uint32 PackFourCC(const char* s);                        // 0x009fc090
extern void   ErrorString(void* out, const char* fmt, ...);     // 0x0052df30
extern __declspec(noreturn) void CxxThrowException(void*, void*); // _CxxThrowException
extern void*  g_TI_cError;                                      // 0x014f9174  ThrowInfo
struct TreeFind { void find(void* outIter, const uint32* key); };// 0x00e5c780 thiscall ret 8
struct cErr16 { void* p0; void* p1; void* p2; void* p3; };     // 16-byte cError temp
struct TreeInsertA_t { void insert(void** out, void* hint, const uint32* key, int zero); }; // 0x009fd230 thiscall ret 0x10
struct TreeInsertB_t { void insert(void** out, void* hint, const uint32* key, int zero); }; // 0x009fd300 thiscall ret 0x10
extern void   ElemRangeInitialize(void* self, uint32 n);        // 0x00475ab0  thiscall
extern void   VecDeformResize(void* self, int n);               // 0x009fd530  thiscall ret 4

// globals
extern float  g_1550b84;   // 0x01550b84  threshold
extern float  g_1485720;   // 0x01485720  float literal (1.0f)
extern void*  g_166c074;   // 0x0166c074  global rbtree (map)
extern void*  g_1667bac;   // 0x01667bac  eastl::gEmptyString16 sentinel

// ---------------------------------------------------------------- nSPCreatureAnim::capability_name
// Flat 0x14-byte element {string{begin,end,capacity}, 4 pad, uint32 fourcc}.  Reuses the exact
// shape proven byte-exact in src/game/SPCreatureAnim/parts_caps.cpp.
struct Elem14 {
    void* b;            // +0x00  string begin
    void* e;            // +0x04  string end
    void* c;            // +0x08  string capacity end
    uint32 pad;         // +0x0c
    uint32 val;         // +0x10  packed fourcc
    Elem14() {}
    Elem14(const Elem14& o);                                    // 0x009fc440
    ~Elem14() { if ((char*)c - (char*)b > 1 && b != 0) ElemFree(b); }
    Elem14& operator=(const Elem14& o) { if (&o != this) Assign(o.b, o.e); val = o.val; return *this; }
    void Assign(void* begin, void* end);                        // 0x00454cb0
    void RangeInitialize(uint32 n) { ElemRangeInitialize(this, n); }
};
typedef bool (*ElemCmp)(const Elem14&, const Elem14&);

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// The copy-construct of the heap string (basic_string RangeInitialize -> AllocateSelf) as it is
// inlined at hot call sites: zero the triple, allocate n+1 (or the gEmptyString sentinel), copy
// the payload, terminate, then store the fourcc.  The out-of-line copy ctor (0x009fc440) is left
// as an external symbol so cool call sites (pop_heap) keep their call.
__forceinline void ElemInitCopy(Elem14* d, const Elem14& s)
{
    uint32 n = (uint32)((char*)s.e - (char*)s.b);
    d->b = d->e = d->c = 0;
    if (n + 1 > 1) {
        d->b = EAAllocate(n + 1, "Anim/partscaps/untagged", 0, 0, ALLOC_FILE, 0xd1);
        d->c = (char*)d->b + (n + 1);
    } else {
        d->b = g_1667bac;
        d->c = (char*)g_1667bac + 1;
    }
    d->e = d->b;
    DoInsertValue(d->b, s.b, n);
    d->e = (char*)d->b + n;
    *(char*)d->e = 0;
    d->val = s.val;
}

inline Elem14::Elem14(const Elem14& o) { ElemInitCopy(this, o); }

// ================================================================== @ 0x009fca70

// @ 0x009fca70
Elem14* copy_backward_elem(Elem14* first, Elem14* last, Elem14* result)
{
    while (last != first) {
        --last;
        --result;
        *result = *last;
    }
    return result;
}

// @ 0x009fcac0
void swap_elem(Elem14* a, Elem14* b)
{
    Elem14 tmp(*a);
    if (b != a) a->Assign(b->b, b->e);
    a->val = b->val;
    if (&tmp != b) b->Assign(tmp.b, tmp.e);
    b->val = tmp.val;
}

// ================================================================== @ 0x009fcc10

struct Desc16 { uint32 f0, f4, f8, fc; };
struct DescVec16 {
    Desc16* begin; Desc16* end; Desc16* cap;
    void DoInsertValues(Desc16* pos, uint32 n, const Desc16& value);
};

// @ 0x009fcc10
void DescVec16::DoInsertValues(Desc16* pos, uint32 n, const Desc16& value)
{
    if (n <= (uint32)((char*)cap - (char*)end) >> 4) {
        if (n > 0) {
            const Desc16 temp = value;
            uint32 nExtra = (uint32)((char*)end - (char*)pos) >> 4;
            uint32 nBytes = n << 4;
            if (n < nExtra) {
                void* out;
                UninitCopy16(&out, (char*)end - nBytes, end, end);
                end = (Desc16*)((char*)end + nBytes);
                CopyBackward16(out, pos, (char*)end - nBytes);
                Fill16(pos, (char*)pos + nBytes, &temp);
            }
            else {
                UninitFillN16(end, n - nExtra, &temp);
                end = (Desc16*)((char*)end + ((n - nExtra) << 4));
                void* e = end;
                UninitCopy16((void**)&e, pos, (char*)e - ((n - nExtra) << 4), (char*)e - ((n - nExtra) << 4));
                end = (Desc16*)((char*)end + (nExtra << 4));
                Fill16(pos, (char*)pos + nExtra * 0x10, &temp);
            }
        }
    }
    else {
        uint32 nPrevSize = (uint32)((char*)end - (char*)begin) >> 4;
        uint32 nGrowSize = nPrevSize << 1;
        if (nPrevSize == 0)
            nGrowSize = 1;
        uint32 nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        Desc16* pNewData = 0;
        if (nNewSize)
            pNewData = (Desc16*)EAAllocate(nNewSize << 4, "Anim/partscaps/untagged", 0, 0,
                                           "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        Desc16* pNewEnd = (Desc16*)UninitMove16(begin, pos, pNewData);
        UninitFillN16(pNewEnd, n, &value);
        pNewEnd = (Desc16*)UninitMove16(pos, end, (char*)pNewEnd + (n << 4));
        if (begin != 0 && *(uint32*)((char*)begin - 4) != 0)
            ElemFree(begin);
        begin = pNewData;
        end = pNewEnd;
        cap = (Desc16*)((char*)pNewData + (nNewSize << 4));
    }
}

// ================================================================== @ 0x009fcdb0

// @ 0x009fcdb0
void insertion_sort_elem(Elem14* first, Elem14* last, ElemCmp compare)
{
    if (first != last) {
        Elem14* iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            Elem14 temp;
            ElemInitCopy(&temp, *iSorted);
            Elem14* iNext = iSorted;
            Elem14* iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && compare(temp, *iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x009fcef0
void insertion_sort_simple_elem(Elem14* first, Elem14* last, ElemCmp compare)
{
    for (Elem14* current = first; current != last; ++current) {
        Elem14* end = current;
        Elem14* prev = current;
        Elem14 temp;
        ElemInitCopy(&temp, *current);
        for (--prev; compare(temp, *prev); --end, --prev)
            *end = *prev;
        *end = temp;
    }
}

// ================================================================== @ 0x009fc9c0 (promote_heap)

// @ 0x009fc9c0
void promote_heap_elem(Elem14* first, int topPosition, int position, Elem14 value, ElemCmp compare)
{
    int parentPosition = (position - 1) >> 1;
    while ((position > topPosition) && compare(first[parentPosition], value)) {
        first[position] = first[parentPosition];
        position = parentPosition;
        parentPosition = (position - 1) >> 1;
    }
    first[position] = value;
}

// ================================================================== @ 0x009fd040

// @ 0x009fd040
void adjust_heap_elem(Elem14* first, int topPosition, int heapSize, int position, Elem14 value, ElemCmp compare)
{
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    promote_heap_elem(first, topPosition, position, value, compare);
}

// ================================================================== @ 0x009fd1a0

// @ 0x009fd1a0
void pop_heap_elem(Elem14* first, Elem14* last, ElemCmp compare)
{
    Elem14 tempBottom(*(last - 1));
    *(last - 1) = *first;
    adjust_heap_elem(first, 0, (int)(last - first) - 1, 0, tempBottom, compare);
}

// ================================================================== @ 0x009fd3d0

// @ 0x009fd3d0
void make_heap_elem(Elem14* first, Elem14* last, ElemCmp compare)
{
    int heapSize = (int)(last - first);
    if (heapSize >= 2) {
        int parentPosition = ((heapSize - 2) >> 1) + 1;
        do {
            --parentPosition;
            Elem14 temp;
            ElemInitCopy(&temp, first[parentPosition]);
            adjust_heap_elem(first, parentPosition, heapSize, parentPosition, temp, compare);
        } while (parentPosition != 0);
    }
}

// ================================================================== @ 0x009fd4d0

// @ 0x009fd4d0
void sort_heap_elem(Elem14* first, Elem14* last, ElemCmp compare)
{
    while ((int)(last - first) > 1) {
        pop_heap_elem(first, last, compare);
        --last;
    }
}

// ================================================================== @ 0x009fd5a0

// @ 0x009fd5a0
Elem14* get_partition_elem(Elem14* first, Elem14* last, Elem14 pivot, ElemCmp compare)
{
    for (;; ++first) {
        while (compare(*first, pivot))
            ++first;
        --last;
        while (compare(pivot, *last))
            --last;
        if (first >= last)
            return first;
        swap_elem(first, last);
    }
}

// ================================================================== @ 0x009fd620

// @ 0x009fd620
void partial_sort_elem(Elem14* first, Elem14* middle, Elem14* last, ElemCmp compare)
{
    make_heap_elem(first, middle, compare);
    for (Elem14* i = middle; i < last; ++i) {
        if (compare(*i, *first)) {
            Elem14 temp;
            ElemInitCopy(&temp, *i);
            *i = *first;
            adjust_heap_elem(first, 0, (int)(middle - first), 0, temp, compare);
        }
    }
    sort_heap_elem(first, middle, compare);
}

// ================================================================== @ 0x009fd7f0 / @ 0x009fdab0

// Source of a 4-vector copy: {begin@0, end@4, cap@8, allocator@0xc}.
struct Raw4 { void* b; void* e; void* c; char alloc[0x10]; };

// { uint32 tag@0; eastl::vector<4-byte> @4 (begin@4/end@8/cap@0xc); allocator@0x10 }.
struct Vec4 {
    uint32   tag;      // +0x00
    void*    begin;    // +0x04
    void*    end;      // +0x08
    void*    cap;      // +0x0c
    char     alloc[0x10];  // +0x10
    Vec4(const Vec4& s);
    Vec4(const uint32* tagSrc, const Raw4* v);
};

// @ 0x009fd7f0
Vec4::Vec4(const Vec4& s)
{
    tag = s.tag;
    int nBytes = (int)((char*)s.end - (char*)s.begin);
    ((VecImpl*)(void*)&begin)->DoAllocate((uint32)(nBytes >> 2), s.alloc);
    end = (char*)DoInsertValue(begin, s.begin, (uint32)nBytes) + (nBytes >> 2) * 4;
}

// @ 0x009fdab0
Vec4::Vec4(const uint32* tagSrc, const Raw4* v)
{
    tag = *tagSrc;
    int nBytes = (int)((char*)v->e - (char*)v->b);
    ((VecImpl*)(void*)&begin)->DoAllocate((uint32)(nBytes >> 2), v->alloc);
    end = (char*)DoInsertValue(begin, v->b, (uint32)nBytes) + (nBytes >> 2) * 4;
}

// ================================================================== command + map bodies

struct ArgArgs {
    uint32* MainArguments(int n);          // 0x00838320  thiscall ret 4
};

typedef int   (__thiscall *Fn_iv)(void*);
typedef int   (__thiscall *Fn_ii)(void*, int);
typedef float (__thiscall *Fn_fi)(void*, int);
typedef void  (__thiscall *Fn_vp)(void*, void*);
#define VT(o) (*(void***)(o))

struct cDeformSpecBlockCommand {
    char pad[0x34];
    void Execute(ArgArgs* args);
};

struct cDeformBlockCommand {
    char pad[0x10];
    void Execute(ArgArgs* args);
};

// @ 0x009fcb30
void cDeformSpecBlockCommand::Execute(ArgArgs* args)
{
    if (g_1550b84 < *(float*)((char*)(*(void**)((char*)this + 0x30)) + 0x1c)) {
        uint32* a = (uint32*)args->MainArguments(1);
        uint32 name = *a;
        uint32 fourcc = PackFourCC((const char*)name);
        void* tree = g_166c074;
        uint32 hash = FNV1String8((const char*)name, 0x811c9dc5, 1);
        void* iter;
        ((TreeFind*)tree)->find(&iter, &hash);
        if (iter == (void*)((char*)tree + 4)) {
            cErr16 buf;
            ErrorString(&buf, "deformSpec capability \"%s\" doesn't exist", *a);
            CxxThrowException(&buf, &g_TI_cError);
        }
        *(uint32*)((char*)(*(void**)((char*)this + 0x30)) + 4) = fourcc;
        void* p = EAAllocate(0x14, "Anim/partscaps/deformdesc", 0, 0, 0, 0);
        if (p != 0) { p = (char*)p; *(uint32*)p = 0; *(uint32*)((char*)p + 4) = 0; *(uint32*)((char*)p + 8) = 0; }
        else p = 0;
        *(void**)((char*)(*(void**)((char*)this + 0x30)) + 8) = p;
    }
    void* base = *(void**)((char*)this + 4);
    ((Fn_vp)VT(base)[0x8c / 4])(base, this);
}

// @ 0x009fd840
void cDeformBlockCommand::Execute(ArgArgs* args)
{
    if (*(float*)((char*)(*(void**)((char*)this + 0xc)) + 0x1c) > g_1550b84) {
        int r = ((Fn_iv)VT(*(void**)((char*)this + 4))[0x2c / 4])(*(void**)((char*)this + 4));
        uint32* a = (uint32*)args->MainArguments(4 + (r >= 3));
        DescVec16* v = *(DescVec16**)((char*)(*(void**)((char*)this + 0xc)) + 8);
        VecDeformResize(v, (int)(((char*)v->end - (char*)v->begin) >> 4) + 1);
        Desc16* d = (Desc16*)((char*)(*(DescVec16**)((char*)(*(void**)((char*)this + 0xc)) + 8))->end - 0x10);
        d->f0 = FNV1String8((const char*)a[0], 0x811c9dc5, 1);
        int i = 1;
        *(float*)&d->f4 = ((Fn_fi)VT(*(void**)((char*)this + 4))[0x98 / 4])(*(void**)((char*)this + 4), a[1]);
        if (r >= 3) {
            i = 2;
            *(float*)&d->f8 = ((Fn_fi)VT(*(void**)((char*)this + 4))[0x98 / 4])(*(void**)((char*)this + 4), a[2]);
        }
        else {
            *(float*)&d->f8 = g_1485720;
        }
        d->fc = 0;
        d->fc |= (((Fn_ii)VT(*(void**)((char*)this + 4))[0x9c / 4])(*(void**)((char*)this + 4), a[i + 1]) == 0) ? 1 : 0;
        d->fc |= (((Fn_ii)VT(*(void**)((char*)this + 4))[0x9c / 4])(*(void**)((char*)this + 4), a[i + 2]) != 0) ? 2 : 0;
    }
}

// map object: {comparator@0, rbtree anchor@4 (node base), root@0xc, size@0x14}; node key@0x10, value@0x14.
struct MapIdxA {
    void* f0;            // +0
    void* anchor0;       // +4
    void* anchor4;       // +8
    void* root;          // +0xc
    void* f10;           // +0x10
    uint32 size;         // +0x14
    void* insert(const uint32& key);
};

struct MapIdxB {
    void* f0;            // +0
    void* anchor0;       // +4
    void* anchor4;       // +8
    void* root;          // +0xc
    void* f10;           // +0x10
    uint32 size;         // +0x14
    void* insert(const uint32& key);
};

// @ 0x009fd950
void* MapIdxA::insert(const uint32& key)
{
    char* root = (char*)this->root;
    char* result = (char*)this + 4;
    char* anchor = (char*)this + 4;
    while (root) {
        if (*(uint32*)(root + 0x10) < key)
            root = *(char**)root;
        else {
            result = root;
            root = *(char**)(root + 4);
        }
    }
    if (result != anchor && *(uint32*)(result + 0x10) <= key)
        return result + 0x14;
    uint32 k = key;
    void* out = 0;
    ((TreeInsertA_t*)this)->insert(&out, result, &k, 0);
    return (char*)out + 0x14;
}

// @ 0x009fd9e0
void* MapIdxB::insert(const uint32& key)
{
    char* root = (char*)this->root;
    char* result = (char*)this + 4;
    char* anchor = (char*)this + 4;
    while (root) {
        if (*(uint32*)(root + 0x10) < key)
            root = *(char**)root;
        else {
            result = root;
            root = *(char**)(root + 4);
        }
    }
    if (result != anchor && *(uint32*)(result + 0x10) <= key)
        return result + 0x14;
    uint32 k = key;
    void* out = 0;
    ((TreeInsertB_t*)this)->insert(&out, result, &k, 0);
    return (char*)out + 0x14;
}
