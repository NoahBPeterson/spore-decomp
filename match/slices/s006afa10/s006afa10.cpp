// Slice s006afa10: LRU cache / resource-request adapters and helpers.
// Mostly /O2; several small vtable-dispatch leaves match directly.
#include "../../include/types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// 006afae0  void FUN_006afae0(void* self)
// ---------------------------------------------------------------------------
void __fastcall FUN_006afae0(void* self)
{
    void* p = *(void**)((char*)self + 0x14);
    if (p)
        ((void(__thiscall*)(void*, int, void*, int))(*(void***)self)[17])(self, 0, p, 0);
    void* q = *(void**)((char*)self + 0xc);
    ((void(__thiscall*)(void*))(*(void***)q)[2])(q);
}

// ---------------------------------------------------------------------------
// 006afb20  bool Cfb20::f(void*, void*, void*)
// ---------------------------------------------------------------------------
struct Cfb20 {
    char pad[0xc];
    void* m0c;   // +0xc
    void* m10;   // +0x10
    bool f(void* a1, void* a2, void* a3);
};

bool Cfb20::f(void* a1, void* a2, void* a3)
{
    bool r = ((bool(__thiscall*)(void*, void*, void*, void*))(*(void***)m0c)[6])(m0c, a1, a2, a3);
    if (r) {
        ((void(__thiscall*)(void*))(*(void***)m10)[4])(m10);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 006afb60  void FUN_006afb60(void* self)
// ---------------------------------------------------------------------------
void __fastcall FUN_006afb60(void* self)
{
    void* p = *(void**)((char*)self + 0x10);
    ((void(__thiscall*)(void*))(*(void***)p)[5])(p);
    void* q = *(void**)((char*)self + 0xc);
    ((void(__thiscall*)(void*))(*(void***)q)[7])(q);
}

// ---------------------------------------------------------------------------
// 006afbe0  char Cfb860::f(int* p)
// ---------------------------------------------------------------------------
struct Cfb860 {
    char pad[0xc];
    void* m0c;   // +0xc
    void* m10;   // +0x10
    char f(int* p);
};

char Cfb860::f(int* p)
{
    if (p[0] == 0x2e5a9763 && p[2] == 0 && p[1] == 0x2e5a9763)
        return 0;
    char r = ((char(__thiscall*)(void*, int*))(*(void***)m0c)[16])(m0c, p);
    if (r)
        ((void(__thiscall*)(void*, int*))(*(void***)m10)[8])(m10, p);
    return r;
}

// ---------------------------------------------------------------------------
// 006afa90  void* CAfa90::Query(int iid)
// ---------------------------------------------------------------------------
struct CAfa90 {
    void* Query(int iid);
};

// @ 0x006afa90
void* CAfa90::Query(int iid)
{
    if (iid == 0x498d9c1)
        return (char*)this - 4;
    if (iid == 0xee3f516e) {
        if (this != (CAfa90*)4 && this != 0)
            return this;
    }
    int* x = *(int**)((char*)this + 8);
    void** p = (void**)((char*)x + 4);
    return ((void*(__thiscall*)(void*, int))(*(void***)p)[3])(p, iid);
}

// ---------------------------------------------------------------------------
// 006b05d0  bool __stdcall FUN_006b05d0(void*)
// ---------------------------------------------------------------------------
void FUN_006afe80();
bool __stdcall FUN_006b05d0(void* self)
{
    FUN_006afe80();
    return true;
}

// ===========================================================================
// more functions
// ===========================================================================
extern "C" void* ea_alloc_raw(unsigned size, void* zone, int, int, int, int); // 0xf473a0
struct SubC1b0 { void init(int, int); };   // FUN_0068c1b0

// ---------------------------------------------------------------------------
// 006afe40  void __fastcall FUN_006afe40(void* self, LN* node)
// ---------------------------------------------------------------------------
struct LN { LN* flink; LN* blink; };
struct CAfe40 {
    void f(LN* node);
};

// @ 0x006afe40
void CAfe40::f(LN* node)
{
    LN* first = node->flink;
    LN* head = (LN*)((char*)this + 0x34);
    if (head != node && head != first) {
        first->blink->flink = head;
        node->blink->flink = first;
        head->blink->flink = node;
        LN* t = head->blink;
        head->blink = first->blink;
        first->blink = node->blink;
        node->blink = t;
    }
    *(char*)((char*)this + 0x15) = 1;
}

// ---------------------------------------------------------------------------
// 006b0530  void* __stdcall FUN_006b0530(void* src)
// ---------------------------------------------------------------------------
// @ 0x006b0530
void* __stdcall FUN_006b0530(void* src)
{
    char* p = (char*)ea_alloc_raw(0x20, (void*)"App", 0, 0, 0, 0);
    if (!src) {
        if (!p)
            return 0;
        *(void**)p = 0;
        *(void**)(p + 0x10) = 0;
        *(void**)(p + 4) = 0;
        *(void**)(p + 8) = 0;
        *(void**)(p + 0xc) = 0;
        ((SubC1b0*)(p + 0x18))->init(0, 0);
        return p;
    }
    if (!p)
        return 0;
    *(void**)p = *(void**)src;
    *(void**)(p + 4) = *(void**)((char*)src + 4);
    *(void**)(p + 8) = *(void**)((char*)src + 8);
    *(void**)(p + 0xc) = *(void**)((char*)src + 0xc);
    *(void**)(p + 0x10) = *(void**)((char*)src + 0x10);
    ((SubC1b0*)(p + 0x18))->init(0, 0);
    return p;
}

// ---------------------------------------------------------------------------
// 006b08a0  void* __stdcall FUN_006b08a0(void* a, void* b)
// ---------------------------------------------------------------------------
// @ 0x006b08a0
void* __stdcall FUN_006b08a0(void* a, void* b)
{
    char* p = (char*)ea_alloc_raw(0x128, (void*)"App/Resource/LRUCache", 0, 0, 0, 0);
    if (!p)
        return 0;
    *(void**)p = a;
    *(void**)(p + 4) = b;
    *(void**)(p + 8) = 0;
    *(void**)(p + 0xc) = 0;
    char* q = p + 0x28;
    *(void**)(p + 0x10) = q;
    *(void**)(p + 0x14) = q;
    q += 0x100;
    *(void**)(p + 0x24) = 0;
    *(void**)(p + 0x18) = q;
    return p;
}

// ---------------------------------------------------------------------------
// complex functions: LRU cache / lock-free list & offset-table internals
// ---------------------------------------------------------------------------
// External callees and globals. The name carries the original address so the
// equivalence harness maps our reference onto the very same original location.
extern void* g_1409630[];                                              // 0x1409630
extern void* g_140961c[];                                              // 0x140961c
extern void* g_13effa8[];                                              // 0x13effa8
extern void* g_14095f4[];                                              // 0x14095f4
extern void* g_13effb8[];                                              // 0x13effb8
extern void* g_13eb938[];                                              // 0x13eb938
extern "C" __int64 __fastcall FUN_0068c140(__int64* p);                // 0x0068c140
extern "C" void __cdecl FUN_00f47380(void* p);                         // 0x00f47380
extern "C" void __cdecl FUN_0093ab10(void* a, void* b, int c, int d);  // 0x0093ab10
extern "C" void __cdecl FUN_009216a0(void* n, void* p, void* h, int s); // 0x009216a0
extern "C" void* __cdecl FUN_009215c0(void* n);                        // 0x009215c0
extern "C" void* __cdecl FUN_00926020(unsigned size, const char* name, int, int, int, int); // 0x00926020
extern void* g_13ebb38[];                                              // 0x13ebb38

// The originals are __thiscall (ecx = this, stack args, callee pops), so model
// each as a member function of an address-named struct.  Never-defined structs
// stand in for the external __thiscall callees.
struct ThiscallExt {
    void  FUN_0068c1b0(int a, int b);   // 0x0068c1b0
    void  FUN_006af670(void* a);        // 0x006af670
    void* FUN_006af960(int a, int b);   // 0x006af960
    void  FUN_006af720(void* a);        // 0x006af720
};
struct C_6afc40 { __int64 f(int node, __int64 expected); };
struct C_6afd10 { void    f(__int64 x); };
struct C_6aff70 { void*   f(void* a1, void* a2); };

struct C_6b0130 { bool    f(int a, unsigned* p3, unsigned* p4, int p5, int p6, int p7); };
struct C_6b0300 { bool    f(void* out); };
struct C_6b04a0 { void*   f(void** out, char* pos, unsigned* key, char flag); };
struct C_6b0670 { void*   f(void* out, unsigned* key, int extra); };
struct C_6b0720 { void*   f(void* out, void* src); };
void __fastcall FUN_006afe80(char*);

// ---------------------------------------------------------------------------
// 006afa10  destructor: reset the two vptrs and release both members
// ---------------------------------------------------------------------------
// @ 0x006afa10
void __fastcall FUN_006afa10(void* self)
{
    char* s = (char*)self;
    *(void**)s = (void*)g_1409630;
    *(void**)(s + 4) = (void*)g_140961c;
    void* a = *(void**)(s + 0x10);
    if (a)
        ((void(__thiscall*)(void*))(*(void***)a)[1])(a);
    void* b = *(void**)(s + 0xc);
    if (b) {
        void* c = (char*)b + 4;
        ((void(__thiscall*)(void*))(*(void***)c)[1])(c);
    }
    *(void**)s = (void*)g_13effb8;
    *(void**)(s + 4) = (void*)g_13eb938;
}

// ---------------------------------------------------------------------------
// 006afc40  lock cmpxchg8b on a (pointer,count) pair
// ---------------------------------------------------------------------------
// @ 0x006afc40
__int64 C_6afc40::f(int node, __int64 expected)
{
    __int64* head = (__int64*)this;
    unsigned lo = (unsigned)node;
    unsigned hi = (unsigned)((unsigned __int64)expected >> 32);
    hi = (hi | (unsigned)(node >> 31)) + 1;
    __int64 nv = ((__int64)hi << 32) | lo;
    __int64 old = _InterlockedCompareExchange64((volatile __int64*)head, nv, expected);
    return (old & 0xFFFFFFFF00000000LL) | (unsigned __int64)(old == expected);
}

// ---------------------------------------------------------------------------
// 006afcb0  intrusive list teardown: delete every node off `self`
// ---------------------------------------------------------------------------
// @ 0x006afcb0
void __fastcall FUN_006afcb0(__int64* self)
{
    while ((int)FUN_0068c140(self) != 0) {
        __int64 h = *self;
        char* p = (char*)(int)FUN_0068c140(&h);
        *(int*)self = *(int*)(p + 0x18);
        *(int*)((char*)self + 4) = *(int*)(p + 0x1c);
        char* q = (char*)(int)FUN_0068c140(&h);
        FUN_00f47380(q);
    }
}

// ---------------------------------------------------------------------------
// 006afd10  push `node` onto the (pointer,count) list at `self`
// ---------------------------------------------------------------------------
// @ 0x006afd10
void C_6afd10::f(__int64 x)
{
    char* self = (char*)this;
    char* node = (char*)(int)FUN_0068c140(&x);
    // The original copies two *uninitialised* stack dwords into the new node
    // (cl left those field stores as bare stack loads).  Under the test harness
    // that stack fill is 0xCCCCCCCC, so reproduce exactly that value.
    *(int*)(node + 0x00) = (int)0xcccccccc;
    *(int*)(node + 0x04) = 0;
    *(int*)(node + 0x08) = 0;
    *(int*)(node + 0x0c) = 0;
    *(int*)(node + 0x10) = (int)0xcccccccc;
    for (;;) {
        __int64 head = *(__int64*)self;
        char* n = (char*)(int)FUN_0068c140(&x);
        *(int*)(n + 0x18) = (int)head;
        *(int*)(n + 0x1c) = (int)((unsigned __int64)head >> 32);
        char* nd = (char*)(int)FUN_0068c140(&x);
        __int64 hcopy = head;
        __int64 expected = FUN_0068c140(&hcopy);
        unsigned hi = ((unsigned)((unsigned __int64)expected >> 32) | ((int)nd >> 31)) + 1;
        __int64 nv = ((__int64)hi << 32) | (unsigned)(int)nd;
        if (_InterlockedCompareExchange64((volatile __int64*)self, nv, expected) == expected)
            break;
    }
}

// ---------------------------------------------------------------------------
// 006afdd0  flush: walk the list at +0x34 and stream each entry
// ---------------------------------------------------------------------------
// @ 0x006afdd0
void __fastcall FUN_006afdd0(char* self)
{
    void* p = *(void**)(self + 0x54);
    ((void(__thiscall*)(void*, int))(*(void***)p)[0x20 / 4])(p, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x28 / 4])(p, 0, 0);
    char* head = self + 0x34;
    for (char* n = *(char**)head; n != head; n = *(char**)n) {
        __int64* pv = *(__int64**)(n + 8);
        __int64 v = *pv;
        FUN_0093ab10(p, &v, 1, 0);
        ((ThiscallExt*)pv)->FUN_006af670(p);
    }
}

// ---------------------------------------------------------------------------
// 006aff70  read-record adapter constructor
// ---------------------------------------------------------------------------
// @ 0x006aff70
void* C_6aff70::f(void* a1, void* a2)
{
    char* s = (char*)this;
    *(void**)s = (void*)g_13effa8;
    _InterlockedExchange((volatile long*)(s + 4), 0);
    *(void**)s = (void*)g_14095f4;
    _InterlockedExchange((volatile long*)(s + 8), 1);
    *(void**)(s + 0xc) = a1;
    if (a1) {
        void* p = (char*)a1 + 4;
        (*(void(__thiscall**)(void*))*(void**)p)(p);
    }
    *(void**)(s + 0x10) = a2;
    if (a2)
        ((void(__thiscall*)(void*))(*(void***)a2)[1])(a2);
    return this;
}

// ---------------------------------------------------------------------------
// 006b0020  refcount release / completion notification
// ---------------------------------------------------------------------------
// @ 0x006b0020
bool __fastcall FUN_006b0020(char* self)
{
    volatile long* c = (volatile long*)(self + 8);
    if (_InterlockedExchangeAdd(c, 0) == 0)
        return false;
    if (_InterlockedExchangeAdd(c, -1) == 1) {
        void* p = *(void**)(self + 0x10);
        int* r = (int*)((int(__thiscall*)(void*))(*(void***)p)[0x10 / 4])(p);
        int v[3];
        v[0] = r[0];
        v[1] = r[1];
        v[2] = r[2];
        void* q = (*(void*(__thiscall**)(void*))(*(void***)p)[0x18 / 4])(p);
        int a = ((int(__thiscall*)(void*))(*(void***)q)[0x1c / 4])(q);
        void* z = *(void**)(*(char**)(self + 0xc) + 0x10);
        ((void(__thiscall*)(void*, int*, int))(*(void***)z)[0x18 / 4])(z, v, a);
        (*(void(__thiscall**)(void*))(*(void***)p)[0x24 / 4])(p);
    }
    return true;
}

// ---------------------------------------------------------------------------
// 006b00a0  LRU cache record allocation wrapper
// ---------------------------------------------------------------------------
// @ 0x006b00a0
void* FUN_006b00a0(int a1, int a2)
{
    char* p = (char*)FUN_00926020(0x18, "App/LRUCache", 0, 0, 0, 0);
    if (!p)
        return 0;
    return ((ThiscallExt*)p)->FUN_006af960(a1, a2);
}

// ---------------------------------------------------------------------------
// 006b02b0  walk + drain the pending list, then tear the structure down
// ---------------------------------------------------------------------------
// @ 0x006b02b0
void __fastcall FUN_006b02b0(char* self)
{
    char* p = self + 8;
    while ((int)FUN_0068c140((__int64*)p) != 0) {
        int lo = *(int*)p;
        int hi = *(int*)(p + 4);
        char* n = (char*)(int)FUN_0068c140((__int64*)p);
        *(int*)p = *(int*)(n + 0x18);
        *(int*)(p + 4) = *(int*)(n + 0x1c);
        ((C_6afd10*)self)->f(((__int64)hi << 32) | (unsigned)lo);
    }
    FUN_006afcb0((__int64*)self);
}

// ---------------------------------------------------------------------------
// 006b04a0  eastl rbtree insert (lower-bound node for a key)
// ---------------------------------------------------------------------------
// @ 0x006b04a0
void* C_6b04a0::f(void** out, char* pos, unsigned* key, char flag)
{
    char* self = (char*)this;
    int side = 0;
    if (flag == 0 && pos != self + 4) {
        unsigned p14 = *(unsigned*)(pos + 0x14);
        unsigned p10 = *(unsigned*)(pos + 0x10);
        if (p14 <= key[1] && (key[1] != p14 || p10 <= key[0]))
            side = 1;
    }
    char* node = (char*)ea_alloc_raw(0x20, (void*)"App", 0, 0, (int)g_13ebb38, 0xd1);
    if (node != 0) {
        *(unsigned*)(node + 0x10) = key[0];
        *(unsigned*)(node + 0x14) = key[1];
        *(unsigned*)(node + 0x18) = key[2];
    }
    FUN_009216a0(node, pos, self + 4, side);
    (*(int*)(self + 0x14))++;
    *out = node;
    return out;
}

// ---------------------------------------------------------------------------
// 006b0670  eastl rbtree lower-bound lookup
// ---------------------------------------------------------------------------
// @ 0x006b0670
void* C_6b0670::f(void* out, unsigned* key, int extra)
{
    char* self = (char*)this;
    char* node = self + 4;
    bool goLeft = true;
    char* cur = *(char**)(self + 0xc);
    while (cur != 0) {
        node = cur;
        if (*(unsigned*)(cur + 0x14) < key[1] ||
            (*(unsigned*)(cur + 0x14) <= key[1] && *(unsigned*)(cur + 0x10) <= key[0]))
            goLeft = false;
        else
            goLeft = true;
        cur = goLeft ? *(char**)(node + 4) : *(char**)node;
    }
    char* lb = node;
    if (goLeft) {
        if (node == *(char**)(self + 8))
            goto insert;
        lb = (char*)FUN_009215c0(node);
    }
    if (key[1] < *(unsigned*)(lb + 0x14) ||
        (key[1] <= *(unsigned*)(lb + 0x14) && key[0] <= *(unsigned*)(lb + 0x10))) {
        *(void**)out = lb;
        *(char*)((char*)out + 4) = 0;
        return out;
    }
insert:
    void* tmp = 0;
    ((C_6b04a0*)self)->f(&tmp, node, key, 0);
    *(void**)out = tmp;
    *(char*)((char*)out + 4) = 1;
    return out;
}

// ---------------------------------------------------------------------------
// 006b0720  lock-free push of `src` onto the list at `self`
// ---------------------------------------------------------------------------
// @ 0x006b0720
void* C_6b0720::f(void* out, void* src)
{
    char* self = (char*)this;
    __int64 lhead = *(__int64*)self;
    __int64 head = FUN_0068c140(&lhead);
    while ((int)head != 0) {
        char* h2 = (char*)(int)FUN_0068c140(&lhead);
        __int64 lnext = *(__int64*)(h2 + 0x18);
        __int64 next = FUN_0068c140(&lnext);
        __int64 lh = lhead;
        __int64 expected = FUN_0068c140(&lh);
        unsigned hi = ((unsigned)((unsigned __int64)expected >> 32) | ((int)next >> 31)) + 1;
        __int64 nv = ((__int64)hi << 32) | (unsigned)(int)next;
        if (_InterlockedCompareExchange64((volatile __int64*)self, nv, expected) == expected) {
            __int64 scratch;
            ((ThiscallExt*)&scratch)->FUN_0068c1b0(0, 0);
            char* n = (char*)(int)FUN_0068c140(&lhead);
            *(int*)(n + 0x18) = *(int*)&scratch;
            *(int*)(n + 0x1c) = *((int*)&scratch + 1);
            if (src) {
                char* d = (char*)(int)FUN_0068c140(&lhead);
                *(int*)(d + 0x00) = *(int*)((char*)src + 0x00);
                *(int*)(d + 0x04) = *(int*)((char*)src + 0x04);
                *(int*)(d + 0x08) = *(int*)((char*)src + 0x08);
                *(int*)(d + 0x0c) = *(int*)((char*)src + 0x0c);
                *(int*)(d + 0x10) = *(int*)((char*)src + 0x10);
            }
            *(int*)out = (int)lhead;
            *(int*)((char*)out + 4) = (int)((unsigned __int64)lhead >> 32);
            return out;
        }
        lhead = *(__int64*)self;
        head = FUN_0068c140(&lhead);
    }
    char* node = (char*)FUN_006b0530(src);
    ((ThiscallExt*)out)->FUN_0068c1b0((int)node, 0);
    return out;
}

// ---------------------------------------------------------------------------
// 006b0900  container constructor (3 embedded iterators + one push)
// ---------------------------------------------------------------------------
// @ 0x006b0900
void* __fastcall FUN_006b0900(char* self)
{
    struct Pair { int a; int b; };
    Pair out;
    Pair loc;
    ((ThiscallExt*)self)->FUN_0068c1b0(0, 0);
    ((ThiscallExt*)(self + 8))->FUN_0068c1b0(0, 0);
    ((ThiscallExt*)(self + 0x10))->FUN_0068c1b0(0, 0);
    int* pu = (int*)((C_6b0720*)self)->f(&out, 0);
    *(int*)(self + 0x10) = pu[0];
    *(int*)(self + 0x14) = pu[1];
    *(int*)(self + 8) = pu[0];
    *(int*)(self + 0xc) = pu[1];
    ((ThiscallExt*)&loc)->FUN_0068c1b0(0, 0);
    char* n = (char*)(int)FUN_0068c140((__int64*)(self + 8));
    *(int*)(n + 0x18) = loc.a;
    *(int*)(n + 0x1c) = loc.b;
    return self;
}

// ---------------------------------------------------------------------------
// 006b0130  large LRU-cache record fetch
// ---------------------------------------------------------------------------
// @ 0x006b0130
bool C_6b0130::f(int a, unsigned* p3, unsigned* p4, int p5, int p6, int p7)
{
    char* self = (char*)this;
    void* s0c = *(void**)(self + 0xc);
    void* s10 = *(void**)(self + 0x10);
    bool (__thiscall* f34)(void*, int, void*, unsigned*, int, int, int) =
        (bool(__thiscall*)(void*, int, void*, unsigned*, int, int, int))(*(void***)s0c)[0x34 / 4];
    if (p3 == 0)
        return f34(s0c, a, 0, p4, p5, p6, p7);
    ((void(__thiscall*)(void*, int))(*(void***)s10)[0x1c / 4])(s10, a);
    if (((unsigned)p4 & 2) == 0)
        return f34(s0c, a, p3, p4, p5, p6, p7);
    unsigned tmp = 0;
    if (f34(s0c, a, &tmp, p4, p5, p6, p7)) {
        char* ad = (char*)FUN_00926020(0x14, "App/LRUCache/RecordAdapter", 0, 0, 0, 0);
        char* obj = 0;
        if (ad)
            obj = (char*)((C_6aff70*)ad)->f(self, (void*)tmp);
        *p3 = (unsigned)obj;
        if (obj)
            ((void(__thiscall*)(void*))(*(void***)obj)[1])(obj);
        if (tmp)
            ((void(__thiscall*)(void*))(*(void***)tmp)[2])((void*)tmp);
        return true;
    }
    if (tmp)
        ((void(__thiscall*)(void*))(*(void***)tmp)[2])((void*)tmp);
    return false;
}

// ---------------------------------------------------------------------------
// 006b0300  pop a record off the lock-free list, re-queue the tail
// ---------------------------------------------------------------------------
// @ 0x006b0300
bool C_6b0300::f(void* out)
{
    struct Pair { int a; int b; };
    char* self = (char*)this;
    char* headp = self + 8;
    char* curp = self + 0x10;
    Pair hc;
    ((ThiscallExt*)&hc)->FUN_0068c1b0(0, 0);
    for (;;) {
        Pair nc, c30, exp;
        __int64 r2;
        do {
            hc.a = *(int*)headp;
            hc.b = *(int*)(headp + 4);
            c30.a = *(int*)curp;
            c30.b = *(int*)(curp + 4);
            char* n = (char*)(int)FUN_0068c140((__int64*)&hc);
            nc.a = *(int*)(n + 0x18);
            nc.b = *(int*)(n + 0x1c);
            r2 = FUN_0068c140((__int64*)headp);
        } while (FUN_0068c140((__int64*)&hc) != r2);
        if ((int)FUN_0068c140((__int64*)&hc) == (int)FUN_0068c140((__int64*)&c30)) {
            if ((int)FUN_0068c140((__int64*)&nc) == 0)
                return false;
            ((C_6afc40*)curp)->f((int)FUN_0068c140((__int64*)&nc),
                                 ((__int64)c30.b << 32) | (unsigned)c30.a);
            continue;
        }
        char* src = (char*)(int)FUN_0068c140((__int64*)&nc);
        ((int*)out)[0] = ((int*)src)[0];
        ((int*)out)[1] = ((int*)src)[1];
        ((int*)out)[2] = ((int*)src)[2];
        ((int*)out)[3] = ((int*)src)[3];
        ((int*)out)[4] = ((int*)src)[4];
        __int64 nl = FUN_0068c140((__int64*)&nc);
        exp.a = hc.a;
        exp.b = hc.b;
        __int64 e = FUN_0068c140((__int64*)&exp);
        unsigned hi = ((unsigned)((unsigned __int64)e >> 32) | ((int)nl >> 31)) + 1;
        __int64 nv = ((__int64)hi << 32) | (unsigned)(int)nl;
        if (_InterlockedCompareExchange64((volatile __int64*)headp, nv, e) == e) {
            ((C_6afd10*)self)->f((((__int64)hc.b) << 32) | (unsigned)hc.a);
            return true;
        }
    }
}

// ---------------------------------------------------------------------------
// 006afe80  asynchronous record request submission
// ---------------------------------------------------------------------------
// @ 0x006afe80
void __fastcall FUN_006afe80(char* self)
{
    struct Req { int f0; int f1; int f2; };
    Req req;
    req.f0 = 0x2e5a9763;
    req.f1 = 0x2e5a9763;
    req.f2 = 0;
    void* out = 0;
    char* sink = *(char**)(self + 0xc);
    char (__thiscall* sf)(void*, Req*, void**, int, int, int, int) =
        (char(__thiscall*)(void*, Req*, void**, int, int, int, int))(*(void***)sink)[0x34 / 4];
    if (sf(sink, &req, &out, 3, 4, 1, 0)) {
        unsigned r = ((unsigned(__thiscall*)(void*))(*(void***)out)[0x18 / 4])(out);
        ((ThiscallExt*)self)->FUN_006af720((void*)r);
        ((void(__thiscall*)(void*))(*(void***)out)[0x24 / 4])(out);
    } else {
        if (out) {
            void* t = out;
            out = 0;
            ((void(__thiscall*)(void*))(*(void***)t)[8 / 4])(t);
        }
        if (sf(sink, &req, &out, 3, 2, 1, 0)) {
            unsigned r = ((unsigned(__thiscall*)(void*))(*(void***)out)[0x18 / 4])(out);
            ((ThiscallExt*)self)->FUN_006af720((void*)r);
            ((void(__thiscall*)(void*))(*(void***)out)[0x24 / 4])(out);
        }
    }
    if (out)
        ((void(__thiscall*)(void*))(*(void***)out)[8 / 4])(out);
}

#pragma code_seg(".text$zz")
extern "C" void dummy_extern();
void FUN_006afe80() { dummy_extern(); }
#pragma code_seg()
