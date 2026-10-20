// slice s009fdb00 -- SPCreatureAnim/parts_caps.obj: capability_name vector/map/sort
// instantiations, four AnimCommand Execute bodies, the registry teardown and the binary reader.
//
//   VA 0x009fdb00  vector<capability_name>::DoInsertValues
//   VA 0x009fdd10  eastl::quick_sort<capability_name*, less>
//   VA 0x009fdec0  cRemapCommand::Execute
//   VA 0x009fdf80  cDeformBlocksEnabledCommand::Execute(bool)
//   VA 0x009fe010  eastl::sort<capability_name*, less>
//   VA 0x009fe1a0  nSPCreatureAnim::PurgeCapabilityTables
//   VA 0x009fe2d0  vector<capability_name>::resize
//   VA 0x009fe350  cSetThresholdCommand::Execute
//   VA 0x009fe390  cAddCapabilityCommand::Execute
//   VA 0x009fe560  rbtree<u32, SimpleVector<u32>>::operator[]
//   VA 0x009fe610  cSetCapabilitiesCommand::Execute
//   VA 0x009fe6c0  nSPCreatureAnim::ReadPartsCapsBinary
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define VT(o) (*(void***)(o))
#define VT_CALL0(o, slot, T) ((T)VT(o)[(slot) / 4])(o)
#define VT_CALL1(o, slot, T, a1) ((T)VT(o)[(slot) / 4])(o, (a1))

// ---------------------------------------------------------------- imported helpers
extern void*  EAAllocate(uint32 size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern void   ElemFree(void* p);                                       // 0x00f47380
extern uint32 FNV1String8(const char* s, uint32 seed, int a);          // 0x00932e80
extern uint32 PackFourCC(const char* s);                               // 0x009fc090
extern void   ErrorString(void* out, const char* fmt, ...);            // 0x0052df30
extern __declspec(noreturn) void CxxThrowException(void* a, void* b);  // 0x011e0912
extern void*  g_TI_cError;                                             // 0x014f9174
extern char   g_emptyStr[];                                            // 0x01667bac
extern float  g_1550b84;                                               // 0x01550b84
extern void*  g_166c070;                                               // 0x0166c070
extern void*  g_166c074;                                               // 0x0166c074
extern void*  g_166c078;                                               // 0x0166c078
extern void*  g_166c080;                                               // 0x0166c080
extern float  g_1485720;                                               // 0x01485720

struct TreeFind { void find(void* outIter, const uint32* key); };      // 0x00e5c780
struct cErr16 { void* p0; void* p1; void* p2; void* p3; };

// element-range utilities (defined in parts_caps.obj outside this slice)
extern void   ElemConstructRange(void** out, void* first, void* last, void* dst, void* extra); // 0x009fc5b0
extern void   ElemFill(void* first, uint32 n, const void* value, void* extra);                 // 0x009fc6c0
extern void*  ElemCopyRange(void* first, void* last, void* dst);       // 0x009fc8b0
extern void   ElemDestroy3(void* a, void* b, void* c);                 // 0x009fc390
extern void   ElemAssignFrom(void* first, void* last, const void* src);// 0x009fc680
extern void*  ElemMove3(void* first, void* last, void* dst);           // 0x009fc970

// ---------------------------------------------------------------- capability_name
// { eastl::basic_string<char> name@0 (begin/end/capacity/4 pad), uint32 fourcc@0x10 }, size 0x14.
struct CapName;

struct Str16 {
    void* b;
    void* e;
    void* c;
    uint32 pad;
    Str16() : b(g_emptyStr), e(g_emptyStr), c(g_emptyStr + 1) {}
    void assign(const char* first, const char* last);                  // 0x00454cb0
    Str16& operator=(const char* s) { assign(s, s + strlen(s)); return *this; }
};

struct CapName {
    Str16  name;
    uint32 val;
    CapName() {}
    CapName(const CapName& o);                                         // 0x009fc440
    CapName& operator=(const CapName& o)
    {
        if (&o != this) name.assign((const char*)o.name.b, (const char*)o.name.e);
        val = o.val;
        return *this;
    }
};

typedef bool (*CapCmp)(const CapName&, const CapName&);

// eastl heap/sort instantiations defined in the previous slice
extern void*  CopyBackwardElem(void* first, void* last, void* result);                              // 0x009fca70
extern void   insertion_sort_elem(void* first, void* last, CapCmp compare);                         // 0x009fcdb0
extern void   insertion_sort_simple_elem(void* first, void* last, CapCmp compare);                  // 0x009fcef0
extern void*  get_partition_elem(void* first, void* last, CapName pivot, CapCmp compare);            // 0x009fd5a0
extern void   partial_sort_elem(void* first, void* middle, void* last, CapCmp compare);             // 0x009fd620

struct DescVec16 {
    char* begin;
    char* end;
    char* cap;
    void DoInsertValues(char* pos, uint32 n, const void* value);       // 0x009fcc10
};

// ---------------------------------------------------------------- vector<capability_name>
struct CapVec {
    CapName* begin;
    CapName* end;
    CapName* cap;
    void resize(uint32 n);                                                       // 0x009fe2d0
    void DoInsertValues(CapName* pos, uint32 n, const CapName& value);           // 0x009fdb00
    void erase(CapName* first, CapName* last);                                   // 0x009fda60
};

// ---------------------------------------------------------------- rbtree maps
struct MapIdxA {
    void* f0;
    void* anchor0;
    void* anchor1;
    void* root;
    void* f10;
    uint32 size;
    void* insert(const uint32& key);                                   // 0x009fd950
};

struct MapIdxB {
    void* f0;
    void* anchor0;
    void* anchor1;
    void* root;
    void* f10;
    uint32 size;
    void* insert(const uint32& key);                                   // 0x009fd9e0
};

struct SimpleVec32 {
    uint32* begin;
    uint32* end;
    uint32* cap;
    void DoInsertValue(uint32* pos, const uint32* value);              // 0x004558a0
};

struct MapIdxC {
    void* f0;
    void* anchor0;
    void* anchor1;
    void* root;
    void* f10;
    uint32 size;
    uint32* insert(const uint32& key);                                 // 0x009fe560
    void* insertImpl(void* out, void* hint, const void* key, const void* value, int flag); // 0x009fe490
};

struct VecImpl { void DoAllocate(uint32 n, const void* allocSrc); };   // 0x004aa350
extern void* DoInsertValue(void* this_, void* pos, int flag);          // 0x0011e0744

// settings object reached through a command's +0xc member: threshold float at +0x1c
struct ThresholdTarget { char pad[0x1c]; float thr; };
struct BlockTarget { void* f0; uint32 f4; void* f8; char pad[0x10]; float thr; };

// ---------------------------------------------------------------- command plumbing
struct ArgArgs { uint32* MainArguments(int n); };                      // 0x00838320 thiscall ret 4
struct ArgArgsN { const char** MainArguments(int* n, int a, int b); }; // 0x00838320 (ArgScript overload) ret 0xc
struct StrArgs  { const char** MainArguments(int* n, int a, int b); }; // 0x00838320

typedef float (__thiscall *Fn_fp)(void*, uint32);
typedef int   (__thiscall *Fn_ip)(void*);

#define EXEC_ARGS ArgArgs* args

// ================================================================== @ 0x009fdb00

// @ 0x009fdb00
void CapVec::DoInsertValues(CapName* pos, uint32 n, const CapName& value)
{
    if (n <= (uint32)((char*)cap - (char*)end) / 0x14) {
        if (n > 0) {
            CapName temp(value);
            uint32 nExtra = (uint32)((char*)end - (char*)pos) / 0x14;
            if (n < nExtra) {
                void* out = 0;
                ElemConstructRange(&out, (char*)end - n * 0x14, (char*)end, (char*)end, (void*)pos);
                end = (CapName*)((char*)end + n * 0x14);
                CopyBackwardElem(out, (char*)end - n * 0x14, (char*)end);
                ElemAssignFrom(pos, (char*)pos + n * 0x14, &temp);
            }
            else {
                uint32 nNew = n - nExtra;
                ElemFill((char*)end, nNew, &temp, (void*)pos);
                end = (CapName*)((char*)end + nNew * 0x14);
                char* newEnd = (char*)end;
                void* out = 0;
                ElemConstructRange(&out, (void*)pos, (char*)newEnd - nNew * 0x14, newEnd, (void*)pos);
                end = (CapName*)((char*)end + nExtra * 0x14);
                ElemAssignFrom(pos, (char*)pos + nExtra * 0x14, &temp);
            }
        }
    }
    else {
        uint32 nPrevSize = (uint32)((char*)end - (char*)begin) / 0x14;
        uint32 nGrowSize = nPrevSize << 1;
        if (nPrevSize == 0)
            nGrowSize = 1;
        uint32 nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        CapName* pNewData = 0;
        if (nNewSize)
            pNewData = (CapName*)EAAllocate(nNewSize * 0x14, "Anim/partscaps/untagged", 0, 0, ALLOC_FILE, 0xd1);
        CapName* pNewEnd = (CapName*)ElemCopyRange(begin, pos, pNewData);
        char* pNewEnd2 = (char*)pNewEnd;
        ElemDestroy3(begin, pos, pNewData);
        ElemFill(pNewEnd2, n, &value, pNewEnd2);
        char* pTail = pNewEnd2 + n * 0x14;
        char* pOldEnd = (char*)end;
        CapName* pRes = (CapName*)ElemCopyRange(pos, pOldEnd, pTail);
        ElemDestroy3(pos, pOldEnd, pTail);
        if (begin != 0 && *(uint32*)((char*)begin - 4) != 0)
            ElemFree(begin);
        begin = pNewData;
        end = pRes;
        cap = (CapName*)((char*)pNewData + nNewSize * 0x14);
    }
}

// ================================================================== @ 0x009fdd10

// @ 0x009fdd10
void quick_sort_elem(CapName* first, CapName* last, int nDepth, CapCmp compare)
{
    for (;;) {
        uint32 nCount = (uint32)((char*)last - (char*)first) / 0x14;
        if (nCount < 0x1d || nDepth < 1) {
            if (nDepth == 0)
                partial_sort_elem(first, last, last, compare);
            return;
        }
        CapName* mid = first + (ptrdiff_t)((uint32)((char*)last - (char*)first) / 0x14 / 2);
        CapName* lastMinus = last - 1;
        CapName* pivot;
        if (compare(*first, *mid)) {
            if (compare(*mid, *lastMinus))
                pivot = mid;
            else if (compare(*first, *lastMinus))
                pivot = lastMinus;
            else
                pivot = first;
        }
        else {
            if (compare(*first, *lastMinus))
                pivot = first;
            else if (compare(*mid, *lastMinus))
                pivot = lastMinus;
            else
                pivot = mid;
        }
        CapName* middle = (CapName*)get_partition_elem(first, last, CapName(*pivot), compare);
        quick_sort_elem(middle, last, nDepth - 1, compare);
        last = middle;
        nDepth = nDepth - 1;
    }
}

// ================================================================== @ 0x009fdec0

struct Node16 { char pad[0x14]; uint32 v0; uint32 v1; };

struct cRemapCommand {
    char pad[0xc];
    void* p0c;
    void Execute(EXEC_ARGS);
};

// @ 0x009fdec0
void cRemapCommand::Execute(EXEC_ARGS)
{
    if (g_1550b84 >= *(float*)((char*)p0c + 0x1c))
        return;
    void* tree = g_166c074;
    uint32* a = (uint32*)args->MainArguments(2);
    void* iter;
    uint32 hash;
    hash = FNV1String8((const char*)a[1], 0x811c9dc5, 1);
    ((TreeFind*)tree)->find(&iter, &hash);
    Node16* node = (Node16*)iter;
    if (iter == (void*)((char*)tree + 4)) {
        cErr16 buf;
        ErrorString(&buf, "remap capability \"%s\" doesn't exist", a[1]);
        CxxThrowException(&buf, &g_TI_cError);
    }
    hash = FNV1String8((const char*)a[0], 0x811c9dc5, 1);
    uint32* v = (uint32*)((MapIdxA*)tree)->insert(hash);
    v[0] = node->v0;
    v[1] = node->v1;
}

// ================================================================== @ 0x009fdf80

struct cDeformBlocksEnabledCommand {
    char pad[0x30];
    void* p30;
    void Execute(bool enable);
};

// @ 0x009fdf80
void cDeformBlocksEnabledCommand::Execute(bool enable)
{
    void* o = p30;
    if (!enable) {
        if (*(float*)((char*)o + 0x1c) > g_1550b84) {
            uint32 key = *(uint32*)((char*)o + 4);
            uint32* n = (uint32*)((MapIdxB*)g_166c078)->insert(key);
            n[0] = *(uint32*)((char*)o + 8);
            *(int*)((char*)p30 + 8) = 0;
        }
        else {
            *(int*)((char*)o + 8) = 0;
        }
        return;
    }
    int* q = *(int**)((char*)o + 8);
    if (q != 0) {
        int x = *q;
        if (x != 0 && *(int*)(x - 4) != 0)
            ElemFree((void*)x);
        ElemFree(q);
    }
    *(int**)((char*)p30 + 8) = 0;
}

// ================================================================== @ 0x009fe010

// @ 0x009fe010
void sort_elem(CapName* first, CapName* last, CapCmp compare)
{
    if (first != last) {
        int nCount = (int)(last - first);
        int i = nCount;
        int nDepth = 0;
        while (i != 0) {
            i >>= 1;
            ++nDepth;
        }
        quick_sort_elem(first, last, nDepth * 2 - 2, compare);
        if (nCount > 0x1c) {
            insertion_sort_elem(first, first + 0x1c, compare);
            insertion_sort_simple_elem(first + 0x1c, last, compare);
        }
        else {
            insertion_sort_elem(first, last, compare);
        }
    }
}

// ================================================================== @ 0x009fe1a0

struct RawTree {
    void* f0;
    void* anchor;
    char* minNode;
    char* root;
    uint8 color;
    uint8 pad[3];
    uint32 size;
};

struct Nuke1 { void f(void* node); };                                  // 0x009a9600
struct Nuke2 { void DoNukeSubtree(void* node); };                      // 0x005d9320
struct VecErase { void f(void* a, void* b); };                         // 0x0083fd70
extern void* RBTreeIncrement(void* node);                              // 0x00921580

// @ 0x009fe1a0
void PurgeCapabilityTables()
{
    {
        CapVec* caps = (CapVec*)g_166c070;
        void* r = ElemMove3(caps->begin, caps->end, caps->end);
        ((VecErase*)caps)->f(r, caps->end);
        uint32 count = (uint32)((char*)caps->end - (char*)caps->begin) / 0x14;
        caps->end = (CapName*)((char*)caps->end + count * 0x14);
    }
    {
        RawTree* t = (RawTree*)g_166c074;
        ((Nuke1*)t)->f(t->root);
        t->minNode = (char*)t + 4;
        t->root = 0;
        t->color = 0;
        t->size = 0;
        *(void**)((char*)t + 4) = (char*)t + 4;
    }
    {
        RawTree* t = (RawTree*)g_166c080;
        ((Nuke2*)t)->DoNukeSubtree(t->root);
        t->root = 0;
        *(void**)((char*)t + 4) = (char*)t + 4;
        t->minNode = (char*)t + 4;
        t->color = 0;
        t->size = 0;
    }
    {
        RawTree* t = (RawTree*)g_166c078;
        char* anchor = (char*)t + 4;
        char* node = t->minNode;
        while (node != anchor) {
            int* v = *(int**)(node + 0x14);
            if (v != 0) {
                int x = *v;
                if (x != 0 && *(int*)(x - 4) != 0)
                    ElemFree((void*)x);
                ElemFree(v);
            }
            node = (char*)RBTreeIncrement(node);
        }
        char* root = t->root;
        while (root != 0) {
            char* left = *(char**)root;
            ((Nuke1*)t)->f(left);
            char* right = *(char**)(root + 4);
            ElemFree(root);
            root = right;
        }
        t->color = 0;
        t->size = 0;
        t->minNode = anchor;
        t->root = 0;
        *(void**)anchor = anchor;
    }
}

// ================================================================== @ 0x009fe2d0

// @ 0x009fe2d0
void CapVec::resize(uint32 n)
{
    if (n > (uint32)(int)(end - begin)) {
        CapName value;
        DoInsertValues(end, n - (uint32)(int)(end - begin), value);
    }
    else {
        erase(begin + n, end);
    }
}

// ================================================================== @ 0x009fe350

struct cSetThresholdCommand {
    char pad4[4];
    void* p4;
    char pad8[4];
    ThresholdTarget* pc;
    void Execute(EXEC_ARGS);
};

// @ 0x009fe350
void cSetThresholdCommand::Execute(EXEC_ARGS)
{
    uint32* a = (uint32*)args->MainArguments(1);
    pc->thr = ((Fn_fp)VT(p4)[0x98 / 4])(p4, a[0]);
    if (g_1550b84 < pc->thr)
        PurgeCapabilityTables();
}

// ================================================================== @ 0x009fe390

struct cAddCapabilityCommand {
    char pad4[4];
    void* p4;
    char pad8[4];
    ThresholdTarget* pc;
    void Execute(EXEC_ARGS);
};

// @ 0x009fe390
void cAddCapabilityCommand::Execute(EXEC_ARGS)
{
    if (!(g_1550b84 >= pc->thr)) {
    CapVec* v = (CapVec*)g_166c070;
    const char** a = (const char**)args->MainArguments(2);
    v->resize((int)((char*)v->end - (char*)v->begin) / 0x14 + 1);
    v->end[-1].name = a[0];
    uint32 fourcc = PackFourCC(a[1]);
    v->end[-1].val = fourcc;
    uint32 idx = (uint32)((int)((char*)v->end - (char*)v->begin) / 0x14 - 1);
    uint32 h1 = FNV1String8((const char*)v->end[-1].name.b, 0x811c9dc5, 1);
    uint32* n1 = (uint32*)((MapIdxA*)g_166c074)->insert(h1);
    n1[0] = fourcc;
    n1[1] = idx;
    uint32 h2 = FNV1String8(a[1], 0x811c9dc5, 1);
    uint32* n2 = (uint32*)((MapIdxA*)g_166c074)->insert(h2);
    n2[0] = fourcc;
    n2[1] = idx;
    }
}

// ================================================================== @ 0x009fe560

// @ 0x009fe560
uint32* MapIdxC::insert(const uint32& key)
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
    if (result != anchor && key >= *(uint32*)(result + 0x10))
        return (uint32*)(result + 0x14);
    SimpleVec32 tmp;
    tmp.begin = 0;
    tmp.end = 0;
    tmp.cap = 0;
    ((VecImpl*)&tmp)->DoAllocate(0, (char*)this + 0x10);
    tmp.end = (uint32*)DoInsertValue(tmp.begin, 0, 0);
    void* out = 0;
    insertImpl(&out, result, 0, &tmp, 0);
    if (tmp.begin != 0 && *(int*)((char*)tmp.begin - 4) != 0)
        ElemFree(tmp.begin);
    return (uint32*)((char*)out + 0x14);
}

// ================================================================== @ 0x009fe610

struct cSetCapabilitiesCommand {
    char pad4[4];
    void* p4;
    char pad8[4];
    ThresholdTarget* pc;
    void Execute(EXEC_ARGS);
};

// @ 0x009fe610
void cSetCapabilitiesCommand::Execute(EXEC_ARGS)
{
    if (g_1550b84 >= pc->thr)
        return;
    int n;
    const char** a = ((ArgArgsN*)args)->MainArguments(&n, 0, 0x7fffffff);
    uint32 fourcc = PackFourCC(a[0]);
    for (int i = 1; i < n; ++i) {
        uint32 val = fourcc;
        uint32 k = PackFourCC(a[i]);
        SimpleVec32* v = (SimpleVec32*)((MapIdxC*)g_166c080)->insert(k);
        uint32* p = v->end;
        if (p < v->cap) {
            v->end = p + 1;
            if (p != 0)
                *p = fourcc;
        }
        else {
            v->DoInsertValue(p, &val);
        }
    }
}

// ================================================================== @ 0x009fe6c0

extern void ReadInt32x(void* stream, void* out, int a, int b);         // 0x0093a780
extern int  ReadString(void* stream, char* buf, int n, int a);         // 0x0093acd0

// @ 0x009fe6c0
bool ReadPartsCapsBinary(void* stream)
{
    uint32 version = 0;
    ReadInt32x(stream, &version, 1, 0);
    if (version < 2)
        return false;
    float threshold = 0.0f;
    if (version >= 4)
        ReadInt32x(stream, &threshold, 1, 0);
    if (threshold <= g_1550b84)
        return false;
    g_1550b84 = threshold;
    PurgeCapabilityTables();

    uint32 nCaps = 0;
    ReadInt32x(stream, &nCaps, 1, 0);
    {
        CapVec* caps = (CapVec*)g_166c070;
        for (uint32 i = 0; i < nCaps; ++i) {
            caps->resize((uint32)((char*)caps->end - (char*)caps->begin) / 0x14 + 1);
            char buf[512];
            ReadString(stream, buf, 0x200, 0);
            CapName* e = caps->end - 1;
            e->name = buf;
            uint32 v = 0;
            ReadInt32x(stream, &v, 1, 0);
            e->val = v;
        }
    }

    uint32 nRemap = 0;
    ReadInt32x(stream, &nRemap, 1, 0);
    {
        MapIdxA* m = (MapIdxA*)g_166c074;
        for (uint32 i = 0; i < nRemap; ++i) {
            uint32 src = 0;
            uint32 dst = 0;
            uint32 filler = 0;
            ReadInt32x(stream, &filler, 1, 0);
            ReadInt32x(stream, &src, 1, 0);
            ReadInt32x(stream, &dst, 1, 0);
            uint32* n = (uint32*)m->insert(src);
            n[0] = filler;
            n[1] = dst;
        }
    }

    uint32 nBehav = 0;
    ReadInt32x(stream, &nBehav, 1, 0);
    {
        for (uint32 i = 0; i < nBehav; ++i) {
            uint32 key = 0;
            ReadInt32x(stream, &key, 1, 0);
            uint32 count = 0;
            ReadInt32x(stream, &count, 1, 0);
            SimpleVec32* v = (SimpleVec32*)((MapIdxC*)g_166c080)->insert(key);
            for (uint32 j = 0; j < count; ++j) {
                uint32 val = 0;
                ReadInt32x(stream, &val, 1, 0);
                uint32* p = v->end;
                if (p < v->cap) {
                    v->end = p + 1;
                    if (p != 0)
                        *p = val;
                }
                else {
                    v->DoInsertValue(p, &val);
                }
            }
        }
    }

    uint32 nGroups = 0;
    ReadInt32x(stream, &nGroups, 1, 0);
    {
        RawTree* t = (RawTree*)g_166c078;
        for (uint32 i = 0; i < nGroups; ++i) {
            uint32 filler = 0;
            uint32 key = 0;
            ReadInt32x(stream, &filler, 1, 0);
            ReadInt32x(stream, &key, 1, 0);
            uint32* n = (uint32*)((MapIdxB*)t)->insert(key);
            uint32 count;
            if (n[0] == 0) {
                char* p = (char*)EAAllocate(0x14, "Anim/deformdesc", 0, 0, 0, 0);
                if (p != 0) {
                    *(uint32*)p = 0;
                    *(uint32*)(p + 4) = 0;
                    *(uint32*)(p + 8) = 0;
                }
                n = (uint32*)((MapIdxB*)t)->insert(key);
                n[0] = (uint32)p;
                count = 0;
            }
            else {
                char* vec = (char*)n[0];
                count = (uint32)(*(char**)(vec + 4) - *(char**)vec) >> 4;
            }
            uint32 total = count + filler;
            uint32* n2 = (uint32*)((MapIdxB*)t)->insert(key);
            DescVec16* dv = (DescVec16*)n2[0];
            if ((uint32)(dv->end - dv->begin) >> 4 < total) {
                uint32 pad[4] = { 0, 0, 0, 0 };
                dv->DoInsertValues(dv->end, total - ((uint32)(dv->end - dv->begin) >> 4), pad);
            }
            else {
                char* pNew = dv->begin + total * 0x10;
                dv->end = dv->begin + total * 0x10;
                (void)pNew;
            }
            uint32* n3 = (uint32*)((MapIdxB*)t)->insert(key);
            char* vec = (char*)n3[0];
            for (uint32 j = count; j < count + filler; ++j) {
                uint32 a0 = 0;
                float a1 = 0.0f;
                float a2 = 0.0f;
                uint32 a3 = 0;
                ReadInt32x(stream, &a0, 1, 0);
                *(uint32*)(vec + j * 0x10) = a0;
                ReadInt32x(stream, &a1, 1, 0);
                *(float*)(vec + j * 0x10 + 4) = a1;
                if (version < 3) {
                    *(float*)(vec + j * 0x10 + 8) = g_1485720;
                }
                else {
                    ReadInt32x(stream, &a2, 1, 0);
                    *(float*)(vec + j * 0x10 + 8) = a2;
                }
                ReadInt32x(stream, &a3, 1, 0);
                *(uint32*)(vec + j * 0x10 + 0xc) = a3;
            }
        }
    }
    return true;
}
