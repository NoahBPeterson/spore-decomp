// Slice s00bfec30 -- Simulator::cCommodityNode: constructor/destructor, the
// chunked intrusive-pointer container helpers, and the mine-state setters.
#include "types.h"
#include <string.h>

typedef unsigned char u8;
typedef unsigned int  u32;

extern char vtbl_1469b08;      // cGameData vtable
extern char vtbl_1469af4;      // DefaultRefCounted vtable
extern char vtbl_1469a30;      // cSpatialObject vtable
extern char vtbl_14699c8;      // vtbl_Simulator::cCommodityNode

// ---------------------------------------------------------------------------
// Out-of-line callees.
// ---------------------------------------------------------------------------
struct V4 { int a, b, c, d; };
V4*   __cdecl FUN_00bfe7c0(V4* ret, V4, V4, int* key);
void  __cdecl FUN_00ca09f0(int);
void  __fastcall FUN_00bfcd00(void* self);
void  __fastcall FUN_00bfeb00(void* self);
void  __fastcall FUN_00bfe530(void* self);
void* __cdecl   SP_GonzagoModelWorld();
void  __fastcall FUN_00c8a420(void* self);
void  __fastcall FUN_00b184c0(void* self);
void  __fastcall FUN_00abf900(void* self);
struct TG   { void ctor(); };
struct TS   { void ctor(); };
struct TC   { void ctor(); };
struct TMR  { void Restart(); };
struct TMS  { void Start(); };
struct TDT  { void dtor(); };

struct RefObj {
    virtual void AddRef();
    virtual void Release();
};

// Chunked container: two eastl-style iterators, each {cur, begin, end, arrayptr}.
struct Iter {
    int*  cur;
    int*  begin;
    int*  end;
    int** arr;
};

struct Container {
    void* m00;
    void* m04;
    Iter  begin;
    Iter  end;
    V4    FUN_00c95660(Iter iter);
    void  FUN_00c92b70();
    void  FUN_00c92bd0(RefObj** p);
};

struct CommodityNode {
    void* vt0;                    // +0x000
    void* vt1;                    // +0x004
    char  pad0[0x34 - 8];
    void* vt2;                    // +0x034 (cSpatialObject)
    char  pad2[0x108 - 0x38];
    void* vt3;                    // +0x108 (cCombatant)
    char  pad3[0x1d0 - 0x10c];
    float m1d0;                   // +0x1d0 resource points
    float m1d4;                   // +0x1d4 max resource points
    void* m1d8;                   // +0x1d8
    void* m1dc;                   // +0x1dc
    void* m1e0;                   // +0x1e0
    u8    m1e4, m1e5, m1e6, m1e7, m1e8, m1e9;
    char  pad4[2];
    int   m1ec;                   // +0x1ec mine state
    char  timer1[0x20];           // +0x1f0 cSPTimer
    int   m210;                   // +0x210
    int   m214, m218, m21c, m220;
    float m224, m228, m22c;
    Container m230;               // +0x230
    char  pad5[8];
    int   m260, m264;             // +0x260
    char  timer2[0x20];           // +0x268 cGonzagoTimer
    void* m288;                   // +0x288

    __declspec(noinline) void FUN_00bff2d0(int a, int b);
    void FUN_00bff140(RefObj* obj);
    void FUN_00bff290(int key);
    void FUN_00bff6e0(int a);
    void FUN_00bff750();
};

// @ 0x00bfec30
bool __cdecl FUN_00bfec30(void* cont, int* key)
{
    V4 end;
    end.a = *(int*)((char*)cont + 0x18);
    end.b = *(int*)((char*)cont + 0x1c);
    end.c = *(int*)((char*)cont + 0x20);
    end.d = *(int*)((char*)cont + 0x24);
    V4 begin;
    begin.a = *(int*)((char*)cont + 8);
    begin.b = *(int*)((char*)cont + 0xc);
    begin.c = *(int*)((char*)cont + 0x10);
    begin.d = *(int*)((char*)cont + 0x14);
    V4 r;
    V4* rp = FUN_00bfe7c0(&r, begin, end, key);
    return rp->a != *(int*)((char*)cont + 0x18);
}

// @ 0x00bfed50
void __fastcall FUN_00bfed50(CommodityNode* n)
{
    n->vt0 = &vtbl_1469b08;
    n->vt1 = &vtbl_1469af4;
    n->vt2 = &vtbl_1469a30;
    n->vt3 = &vtbl_14699c8;
    ((TDT*)n->timer2)->dtor();
    FUN_00abf900(&n->m230);
    ((TDT*)n->timer1)->dtor();
    if (n->m1e0 != 0)
        ((RefObj*)n->m1e0)->Release();
    void* p = n->m1dc;
    if (p != 0) {
        int c = *(int*)((char*)p + 0x40);
        if (c > 1) {
            *(int*)((char*)p + 0x40) = c - 1;
        } else {
            typedef void (__thiscall* Fn)(void*, unsigned);
            unsigned flag = (*(unsigned*)((char*)p + 4) >> 31) & 1;
            (*(Fn)(*(char**)*(char**)p + 0x170))(p, flag);
        }
    }
    if (n->m1d8 != 0)
        ((RefObj*)n->m1d8)->Release();
    FUN_00bfcd00(&n->vt3);
    FUN_00c8a420(&n->vt2);
    FUN_00b184c0(n);
}

// @ 0x00bff010
CommodityNode* __fastcall FUN_00bff010(CommodityNode* n)
{
    ((TG*)n)->ctor();
    ((TS*)&n->vt2)->ctor();
    ((TC*)&n->vt3)->ctor();
    n->vt3 = &vtbl_14699c8;
    n->vt2 = &vtbl_1469a30;
    n->vt0 = &vtbl_1469b08;
    n->vt1 = &vtbl_1469af4;
    n->m1d0 = 100.0f;
    n->m1d4 = 100.0f;
    n->m1d8 = 0;
    n->m1dc = 0;
    n->m1e0 = 0;
    n->m1e4 = 0;
    n->m1e5 = 0;
    n->m1e6 = 0;
    n->m1e7 = 0;
    n->m1e8 = 0;
    n->m1e9 = 0;
    n->m1ec = 0;
    ((TG*)n->timer1)->ctor();
    n->m210 = 0;
    n->m224 = 0.0f;
    n->m228 = 0.0f;
    n->m22c = 0.0f;
    n->m214 = -1;
    n->m218 = -1;
    n->m21c = -1;
    n->m220 = -1;
    Container* c = &n->m230;
    c->m00 = 0;
    c->m04 = 0;
    c->begin.cur = 0;
    c->begin.begin = 0;
    c->begin.end = 0;
    c->begin.arr = 0;
    c->end.cur = 0;
    c->end.begin = 0;
    c->end.end = 0;
    c->end.arr = 0;
    FUN_00ca09f0(0);
    n->m260 = 0;
    n->m264 = 0;
    ((TG*)n->timer2)->ctor();
    n->m288 = 0;
    ((TMS*)n->timer1)->Start();
    return n;
}

// @ 0x00bff140
void CommodityNode::FUN_00bff140(RefObj* obj)
{
    CommodityNode* n = this;
    Container* c = &n->m230;
    if (FUN_00bfec30(c, (int*)&obj))
        return;
    RefObj* p = obj;
    if (p != 0)
        p->AddRef();
    int** cur = (int**)c->end.cur;
    if (cur + 1 != (int**)c->end.end) {
        c->end.cur = (int*)(cur + 1);
        if (cur != 0) {
            *cur = (int*)p;
            if (p != 0)
                p->AddRef();
        }
    } else {
        c->FUN_00c92bd0(&obj);
    }
    if (p != 0)
        p->Release();
}

// @ 0x00bff220
bool __cdecl FUN_00bff220(Container* c, int* key)
{
    int* cur   = c->begin.cur;
    int* last  = c->end.cur;
    int* begin = c->begin.begin;
    int* end   = c->begin.end;
    int** arr  = c->begin.arr;
    if (cur != last) {
        int k = *key;
        do {
            if (*cur == k) {
                Iter it;
                it.cur = cur;
                it.begin = begin;
                it.end = end;
                it.arr = arr;
                (void)c->FUN_00c95660(it);
                return true;
            }
            ++cur;
            if (cur == end) {
                begin = arr[1];
                ++arr;
                end = begin + 0x40;
                cur = begin;
            }
        } while (cur != last);
    }
    return false;
}

// @ 0x00bff290
void CommodityNode::FUN_00bff290(int key)
{
    Container* c = &m230;
    if (m230.begin.cur != m230.end.cur && key == *m230.begin.cur) {
        c->FUN_00c92b70();
        return;
    }
    FUN_00bff220(c, &key);
}

// @ 0x00bff6e0
void CommodityNode::FUN_00bff6e0(int a)
{
    CommodityNode* n = this;
    n->FUN_00bff2d0(a, -1);
    FUN_00bfe530(n);
    void** vt = *(void***)&n->vt2;
    void* world = SP_GonzagoModelWorld();
    (*(void (__thiscall*)(void*, void*))vt[0x28])(&n->vt2, world);
    FUN_00bfeb00(n);
    if (n->m1ec != 3) {
        n->m1ec = 3;
        ((TMR*)n->timer1)->Restart();
    }
    if (n->m288 != 0)
        *(int*)((char*)n->m288 + 4) = 3;
}

// @ 0x00bff750
void CommodityNode::FUN_00bff750()
{
    CommodityNode* n = this;
    n->m1e7 = 0;
    n->FUN_00bff2d0(-1, -1);
    n->m210 = 0x9c4;
    if (n->m1ec != 5) {
        n->m1ec = 5;
        ((TMR*)n->timer1)->Restart();
    }
    if (n->m288 != 0)
        *(int*)((char*)n->m288 + 4) = 5;
}

// ---------------------------------------------------------------------------
// Large handlers (not reconstructed byte-exactly).
// ---------------------------------------------------------------------------
// @ 0x00bff2d0  -- out of line, large state dispatcher (declared above).
// @ 0x00bff7a0
void __fastcall FUN_00bff7a0(CommodityNode* n)
{
    (void)n;
}
