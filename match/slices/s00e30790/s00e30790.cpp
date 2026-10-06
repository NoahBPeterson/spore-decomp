// Slice s00e30790 -- UI asset-discovery / flash window manager cluster.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
//
// Reconstructed from the disassembly; member names are placeholders where no
// 2008-PDB name survives.
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------- vtables (masked)
extern void* g_vt_flash0;    // 0x1481948  vtbl_UI::cUIFlashWindowManager
extern void* g_vt_flash1;    // 0x1481940
extern void* g_vt_card0;     // 0x1481968
extern void* g_vt_card1;     // 0x1481958
extern void* g_vt_sim;       // 0x13ec458
extern void* g_vt_paint;     // 0x13eb394
extern void* g_vt_editor;    // 0x13eb938
extern void* g_vt_gon0;      // 0x14818d8
extern void* g_vt_gon1;      // 0x14818d0
extern void* g_vt_gon2;      // 0x14818c0
extern void* g_data_154df28;

// ---------------------------------------------------------------- free callees
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int); // 0xf473a0
void  __cdecl operator_delete(void*);                                          // 0xf47380
void  __cdecl FUN_00847ff0(void*, void*, void*);                               // 0x847ff0
void  __cdecl EA_RemoveHandler(int, int, int, int, int);                       // 0x571db0
int   __cdecl SP_PropertyManager(void);                                        // 0x67de30
void  __cdecl SPUIShader_AcquireShaderProxy(void);                             // 0x82f630
void* __cdecl FUN_00e2e8a0(void*, void*, void*, int);                          // 0xe2e8a0

// thiscall callees (this in ecx); stubs to get the exact calling shape
struct TC {
    void  f_d73090(void*, void*);      // 0x00d73090
    void  f_d018d0(void*, void*);      // 0x00d018d0
    void  f_ca09f0(int);               // 0x00ca09f0
    void  f_60e660(void);              // 0x0060e660
    void  f_b5b9a0(void);              // 0x00b5b9a0
    void  f_b5b960(void);              // 0x00b5b960
    void  f_e2f480(void*);             // 0x00e2f480
    void* f_e30740(void*);             // 0x00e30740
    void  f_e2f3f0(void*, unsigned);   // 0x00e2f3f0
    void  f_e2ff50(void*, void*);      // 0x00e2ff50
    void  f_ac9480(void*);             // 0x00ac9480
    void  f_e2fcb0(void*);             // 0x00e2fcb0
    void  f_b5f950(void*);             // 0x00b5f950
    void  f_e30010(void*);             // 0x00e30010
    void  f_a3b2c0(void*, void*);      // 0x00a3b2c0  hashtable::find
    void  f_811ad0(int);               // 0x00811ad0
    char  f_810070(void);              // 0x00810070
    void  f_e2f6e0(int);               // 0x00e2f6e0
};

// ---------------------------------------------------------------- element / container types
struct Elem1c {
    uint32_t f0, f4, f8;
    void*    fc;
    uint32_t f10;
    uint8_t  f14;
    char     _pad[3];
    uint32_t f18;
};

struct NodeList {
    uint32_t pad0;
    void**   array;   // +0x04
    int      count;   // +0x08
    int      cap;     // +0x0c
    void destroy(void** a, unsigned n);   // 0x00e308d0
};

struct Vec1c {
    Elem1c* begin;    // +0x00
    Elem1c* end;      // +0x04
    Elem1c* cap;      // +0x08
    void  insert_(Elem1c* pos, const Elem1c* val);   // 0x00e30790
    void  push_back_default();                       // 0x00e30c00
    void  remove_head(uint32_t key);                 // 0x00e30a60
    void  remove_off8(uint32_t key);                 // 0x00e30ae0
    void  erase(void* a, void* b);                   // 0x00d018d0
};

struct MgrVec {
    char   pad0[0x0c];
    int    counter;   // +0x0c
    Vec1c  vec;       // +0x10
    char   pad1[0x24 - 0x1c];
    char   ht[0x0c];  // +0x24
    void  update(int dt);   // 0x00e30990
};

struct HT {
    char   pad0[4];
    void** buckets;   // +0x04
    int    nbuckets;  // +0x08
    char   pad1[4];
    void  find(void* out, void* key);         // 0x00a3b2c0
    void* find_or_add(void* key);             // 0x00e30b60
};

// ---------------------------------------------------------------- 0x00e30790
void Vec1c::insert_(Elem1c* pos, const Elem1c* val)
{
    if (end != cap) {
        const Elem1c* v = val;
        if ((char*)v >= (char*)pos && (char*)v < (char*)end)
            v = v + 1;
        if (end) *end = end[-1];
        for (Elem1c* p = end - 1; p != pos; --p)
            p[0] = p[-1];
        *pos = *v;
        ++end;
        return;
    }
    Elem1c* oldBegin = begin;
    unsigned size = (unsigned)(end - begin);
    unsigned ncap = size ? size * 2 : 1;
    Elem1c* nb = (Elem1c*)operator_new(ncap * 0x1c, "Simulator", 0, 0,
                                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\E", 0xd1);
    Elem1c tmp = *val;
    FUN_00847ff0(oldBegin, pos, nb);
    FUN_00847ff0((void*)((char*)nb + 0x1c), (void*)(pos + 1), (void*)((char*)nb + 0x40));
    if (begin && *(int*)((char*)begin - 4))
        operator_delete(begin);
    FUN_00847ff0((void*)end, (void*)end, (void*)((char*)nb + 0x1c));
    *(Elem1c*)((char*)nb + ((char*)pos - (char*)oldBegin)) = tmp;
    begin = nb;
    end = (Elem1c*)((char*)nb + 0x1c + ((char*)end - (char*)oldBegin));
    cap = nb + ncap;
}

// ---------------------------------------------------------------- 0x00e308d0
void NodeList::destroy(void** a, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        void* p = a[i];
        if (p) {
            do {
                void* o10 = *(void**)((char*)p + 0x10);
                void* next = *(void**)((char*)p + 0x14);
                if (o10) ((void(__thiscall*)(void*))(*(void***)o10)[1])(o10);
                void* o8 = *(void**)((char*)p + 0x8);
                if (o8) ((void(__thiscall*)(void*))(*(void***)o8)[1])(o8);
                operator_delete(p);
                p = next;
            } while (p);
        }
        a[i] = 0;
    }
}

// ---------------------------------------------------------------- 0x00e30930
struct MgrA {
    void** vt0;      // +0x00
    void** vt1;      // +0x04
    char   pad0[0x1c - 0x08];
    void** vt2;      // +0x1c
    char   pad1[0x24 - 0x20];
    char   sub24[0x2c]; // +0x24 .. +0x50
    void*  p50;         // +0x50
    MgrA* scalar_dtor(int flag);
};

MgrA* MgrA::scalar_dtor(int flag)
{
    ((void***)this)[0] = &g_vt_gon0;
    ((void***)this)[1] = &g_vt_gon1;
    ((void***)this)[7] = &g_vt_gon2;
    _ReadWriteBarrier();
    void* p = *(void**)((char*)this + 0x50);
    if (p)
        ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    ((TC*)((char*)this + 0x24))->f_60e660();
    *(void**)((char*)this + 0x1c) = &g_vt_paint;
    ((TC*)this)->f_b5b9a0();
    if (flag & 1)
        operator_delete(this);
    return this;
}

// ---------------------------------------------------------------- 0x00e30990
void MgrVec::update(int dt)
{
    if (vec.begin == vec.end) {
        counter = 0;
        return;
    }
    counter += dt;
    float t = (float)counter;
    if (counter < 0)
        t += 4294967296.0f;
    float s = 0.0f;  // sinf(t * 0.01f); the original uses x87 fsin
    Elem1c* e = vec.begin;
    while (e != vec.end) {
        e->f10 += dt;
        uint32_t limit = e->f18 ? *(uint32_t*)e->f18 : 0x1388u;
        if (limit != 0xffffffffu && e->f10 >= limit) {
            ((TC*)this)->f_e2f480(e);
            e = (Elem1c*)((TC*)((char*)this + 0x10))->f_e30740(e);
        } else {
            unsigned c = ((unsigned)(uint8_t)(int)((s + 1.0f) * 0.5f * 255.0f) << 24) | 0xffffffu;
            ((TC*)this)->f_e2f3f0(e, c);
            e += 1;
        }
    }
}

// ---------------------------------------------------------------- 0x00e30a60
void Vec1c::remove_head(uint32_t key)
{
    if (begin == end) return;
    Elem1c* cur = begin;
    while (cur != end) {
        if (cur->f0 == key || cur->f8 == key) {
            for (Elem1c* q = cur; q + 1 != end; ++q)
                q[0] = q[1];
            end = (Elem1c*)((char*)end - 0x1c);
        } else {
            cur += 1;
        }
    }
}

// ---------------------------------------------------------------- 0x00e30ae0
void Vec1c::remove_off8(uint32_t key)
{
    if (begin == end) return;
    Elem1c* cur = begin;
    while (cur != end) {
        if (cur->f8 == key) {
            for (Elem1c* q = cur; q + 1 != end; ++q)
                q[0] = q[1];
            end = (Elem1c*)((char*)end - 0x1c);
        } else {
            cur += 1;
        }
    }
}

// ---------------------------------------------------------------- 0x00e30b60
void* HT::find_or_add(void* key)
{
    char it[8];
    find(it, key);
    if (*(void**)((char*)this + 4) &&
        *(void**)it != *(void**)((char*)*(void**)((char*)this + 4) + *(int*)((char*)this + 8) * 4))
        return (char*)*(void**)it + 4;
    return (char*)*(void**)it + 4;
}

// ---------------------------------------------------------------- 0x00e30c00
void Vec1c::push_back_default()
{
    Elem1c* p = end;
    if (p < cap) {
        end = p + 1;
        if (p) {
            p->f0 = 0; p->f4 = 0; p->f8 = 0; p->fc = 0;
            p->f10 = 0; p->f14 = 0; p->f18 = 0;
        }
        return;
    }
    Elem1c tmp;
    tmp.f0 = 0; tmp.f4 = 0; tmp.f8 = 0; tmp.fc = 0;
    tmp.f10 = 0; tmp.f14 = 0; tmp.f18 = 0;
    insert_(end, &tmp);
}

// ---------------------------------------------------------------- 0x00e30c60
MgrA* __fastcall MgrA_ctor(MgrA* self)
{
    ((TC*)self)->f_b5b960();
    *(void* volatile*)((char*)self + 0x1c) = &g_vt_paint;
    char* ecx = (char*)self + 0x24;
    uint32_t z = 0;
    *(void* volatile*)((char*)self + 0) = &g_vt_gon0;
    *(void* volatile*)((char*)self + 4) = &g_vt_gon1;
    *(void* volatile*)((char*)self + 0x1c) = &g_vt_gon2;
    *(uint32_t*)(ecx + 0x00) = z;
    *(uint32_t*)(ecx + 0x04) = z;
    *(uint32_t*)(ecx + 0x08) = z;
    *(uint32_t*)(ecx + 0x0c) = z;
    *(uint32_t*)(ecx + 0x10) = z;
    *(uint32_t*)(ecx + 0x14) = z;
    *(uint32_t*)(ecx + 0x18) = z;
    *(uint32_t*)(ecx + 0x1c) = z;
    *(uint32_t*)(ecx + 0x20) = z;
    *(uint32_t*)(ecx + 0x24) = z;
    ((TC*)ecx)->f_ca09f0(0);
    *(uint32_t*)((char*)self + 0x50) = z;
    *(uint32_t*)((char*)self + 0x54) = z;
    *(uint32_t*)((char*)self + 0x58) = z;
    *(uint32_t*)((char*)self + 0x5c) = z;
    *(uint32_t*)((char*)self + 0x60) = z;
    *(uint32_t*)((char*)self + 0x64) = z;
    *(uint32_t*)((char*)self + 0x78) = z;
    *(uint32_t*)((char*)self + 0x7c) = z;
    *(uint32_t*)((char*)self + 0x80) = z;
    *(uint32_t*)((char*)self + 0x84) = z;
    *(uint32_t*)((char*)self + 0x88) = z;
    *(uint32_t*)((char*)self + 0x8c) = z;
    *(uint32_t*)((char*)self + 0x90) = z;
    *(uint32_t*)((char*)self + 0x94) = z;
    *(uint32_t*)((char*)self + 0x98) = z;
    *(uint32_t*)((char*)self + 0x9c) = z;
    *(float volatile*)((char*)self + 0x68) = 0.0f;
    *(float volatile*)((char*)self + 0x6c) = 0.0f;
    *(float volatile*)((char*)self + 0x70) = 0.0f;
    *(float volatile*)((char*)self + 0x74) = 0.0f;
    *(float volatile*)((char*)self + 0xa0) = 0.0f;
    return self;
}

// ---------------------------------------------------------------- 0x00e30d20
struct MgrCard {
    char pad0[0x24];
    char list[0x20];   // +0x24
    void Add(void** out, int p);
    void AddOrUpdate(int a, void* p, unsigned c, uint8_t flag, int e);
    void Wrapper(int a, int b, int c, int d);
    void Destroy();
};

struct Card {
    void** vt0;    // +0x00
    int    rc;     // +0x04
    void*  p08;
    void*  p0c;
    void*  p10;
    void*  p14;
    void*  p18;
};

void MgrCard::Add(void** out, int p)
{
    Card* c = (Card*)operator_new(0x1c, "UI/AssetDiscoveryCard", 0, 0, 0, 0);
    if (c) {
        c->rc = 0;
        ((void***)c)[1] = &g_vt_card0;
        c->p08 = 0; c->p0c = 0; c->p10 = 0; c->p14 = 0; c->p18 = 0;
    } else {
        c = 0;
    }
    if (c) ((void(__thiscall*)(void*))(*(void***)c)[1])(c);
    ((TC*)c)->f_e2f6e0(p);
    void** e = *(void***)((char*)this + 0x3c);
    void* n = (char*)e + 4;
    if (n == *(void**)((char*)this + 0x44)) {
        ((TC*)((char*)this + 0x24))->f_e30010(&c);
    } else {
        *(void**)((char*)this + 0x3c) = n;
        if (e) {
            *e = (void*)c;
            if (c) ((void(__thiscall*)(void*))(*(void***)c)[1])(c);
        }
    }
    if (c) ((void(__thiscall*)(void*))(*(void***)c)[2])(c);
}

// ---------------------------------------------------------------- 0x00e30dc0
void MgrCard::Destroy()
{
    ((TC*)((char*)this + 0x10))->f_d73090(*(void**)((char*)this + 0x10), *(void**)((char*)this + 0x14));
    ((NodeList*)((char*)this + 0x24))->destroy(*(void***)((char*)this + 0x28), *(int*)((char*)this + 0x2c));
    *(uint32_t*)((char*)this + 0x30) = 0;
    int h = *(int*)((char*)this + 0x44);
    if (h) {
        *(uint32_t*)((char*)this + 0x44) = 0;
        EA_RemoveHandler(h, *(int*)((char*)this + 0x48), *(int*)((char*)this + 0x4c),
                        *(int*)((char*)this + 0x50), *(int*)((char*)this + 0x54));
    }
}

// ---------------------------------------------------------------- 0x00e30e20
void MgrCard::AddOrUpdate(int a, void* p, unsigned c, uint8_t flag, int e)
{
    Elem1c* begin = *(Elem1c**)((char*)this + 0x10);
    Elem1c* end = *(Elem1c**)((char*)this + 0x14);
    for (Elem1c* q = begin; q != end; q += 1) {
        if (q->f0 == (uint32_t)a && q->f4 == (uint32_t)e) {
            q->f10 = 0;
            return;
        }
    }
    void* found = 0;
    if (p) {
        void* q = (void*)FUN_00e2e8a0(begin, end, p, 0);
        (void)q;
    }
    Vec1c* v = (Vec1c*)((char*)this + 0x10);
    v->push_back_default();
    Elem1c* el = (Elem1c*)(*(char**)((char*)this + 0x14) - 0x1c);
    el->f0 = (uint32_t)a;
    el->f4 = (uint32_t)e;
    el->f8 = c;
    el->fc = p;
    el->f10 = found ? *(uint32_t*)((char*)found + 0x10) : 0;
    el->f14 = flag;
    el->f18 = 0;

    HT* ht = (HT*)((char*)this + 0x24);
    char it[4];
    ht->find(it, &c);
    if (ht->buckets && *(void**)it != *(void**)((char*)ht->buckets + ht->nbuckets * 4)) {
        el->f18 = (uint32_t)((char*)*(void**)it + 4);
    } else {
        int pm = SP_PropertyManager();
        if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
        char ok = ((char(__thiscall*)(int, unsigned, int, void*))(*(void***)pm)[0x2c / 4])(pm, c, 0x689fa1a, &p);
        if (ok) {
            void* x = ht->find_or_add(&c);
            *(uint32_t*)x = 5000;
            SPUIShader_AcquireShaderProxy();
            ((TC*)((char*)x + 4))->f_b5f950(0);
            *((uint8_t*)x + 8) = 0;
            ((TC*)((char*)x + 0xc))->f_ac9480(&p);
            ((TC*)this)->f_e2fcb0(x);
            el->f18 = (uint32_t)x;
        }
    }
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
}

// ---------------------------------------------------------------- 0x00e30f90
struct FlashMgr {
    void** vt0;   // +0x00
    void*  m04;   // +0x04
    void** vt1;   // +0x08
    char   pad[0x10 - 0x0c];
    void*  buf;   // +0x10
    char   pad2[0x24 - 0x14];
    NodeList list; // +0x24
    char   pad3[0x44 - 0x34];
    int    handler; // +0x44
    int    h48, h4c, h50, h54;
    void dtor();
};

void FlashMgr::dtor()
{
    ((void***)this)[0] = &g_vt_flash0;
    ((void***)this)[2] = &g_vt_flash1;
    _ReadWriteBarrier();
    int h = handler;
    if (h) {
        handler = 0;
        EA_RemoveHandler(h, h48, h4c, h50, h54);
    }
    NodeList& l = *(NodeList*)((char*)this + 0x24);
    l.destroy(l.array, l.count);
    l.cap = 0;
    if ((unsigned)l.count > 1)
        operator_delete(l.array);
    void* b = buf;
    if (b && *(int*)((char*)b - 4))
        operator_delete(b);
    _ReadWriteBarrier();
    ((void***)this)[2] = &g_vt_paint;
    ((void***)this)[0] = &g_vt_sim;
}

// ---------------------------------------------------------------- 0x00e31030
void MgrCard::Wrapper(int a, int b, int c, int d)
{
    AddOrUpdate(a, 0, (unsigned)b, (uint8_t)c, d);
}

// ---------------------------------------------------------------- 0x00e31050
FlashMgr* __fastcall FlashMgr_ctor(FlashMgr* self)
{
    *(uint32_t volatile*)((char*)self + 4) = 0;
    *(void* volatile*)((char*)self + 8) = &g_vt_paint;
    *(void* volatile*)((char*)self + 0) = &g_vt_flash0;
    *(void* volatile*)((char*)self + 8) = &g_vt_flash1;
    *(uint32_t volatile*)((char*)self + 0x0c) = 0;
    *(uint32_t volatile*)((char*)self + 0x10) = 0;
    *(uint32_t volatile*)((char*)self + 0x14) = 0;
    *(uint32_t volatile*)((char*)self + 0x18) = 0;
    *(float volatile*)((char*)self + 0x34) = 1.0f;
    *(float volatile*)((char*)self + 0x38) = 2.0f;
    *(uint32_t volatile*)((char*)self + 0x2c) = 1;
    *(void* volatile*)((char*)self + 0x28) = &g_data_154df28;
    *(uint32_t volatile*)((char*)self + 0x30) = 0;
    *(uint32_t volatile*)((char*)self + 0x3c) = 0;
    *(uint32_t volatile*)((char*)self + 0x44) = 0;
    *(uint32_t volatile*)((char*)self + 0x48) = 0;
    *(uint32_t volatile*)((char*)self + 0x4c) = 0;
    *(uint32_t volatile*)((char*)self + 0x50) = 0;
    *(uint32_t volatile*)((char*)self + 0x54) = 0;
    return self;
}

// ---------------------------------------------------------------- 0x00e31100
int __fastcall UTFWin_IWinProc_GetPriority(void*)
{
    return 0;
}

// ---------------------------------------------------------------- 0x00e31110
int __fastcall FUN_00e31110(void* self)
{
    return *(float*)((char*)self + 0x68) >= 1.0f;
}

// ---------------------------------------------------------------- 0x00e31130
void __fastcall FUN_00e31130(void* self)
{
    char* p = *(char**)((char*)self + 0x0c);
    if (p) {
        ((TC*)p)->f_811ad0(1);
        p = *(char**)((char*)self + 0x0c);
        if (p) {
            *(uint32_t*)((char*)self + 0x0c) = 0;
            ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
        }
    }
}

// ---------------------------------------------------------------- 0x00e31170
int __fastcall FUN_00e31170(void* self)
{
    char* p = *(char**)((char*)self + 0x0c);
    if (p && ((TC*)p)->f_810070())
        return 1;
    return 0;
}

// ---------------------------------------------------------------- 0x00e31190
void __fastcall FUN_00e31190(void* self)
{
    void* p = *(void**)((char*)self + 0xa4);
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
}

// ---------------------------------------------------------------- 0x00e311b0
struct StateObj { void step(int state); };
void StateObj::step(int state)
{
    switch (state) {
    case 2: {
        void* p = *(void**)((char*)this + 0x9c);
        ((void(__thiscall*)(void*, int))(*(void***)p)[0x14 / 4])(p, 2);
        void* q = *(void**)((char*)this + 0xa0);
        ((void(__thiscall*)(void*, int))(*(void***)q)[0x14 / 4])(q, 3);
        break;
    }
    case 3: {
        void* p = *(void**)((char*)this + 0x9c);
        ((void(__thiscall*)(void*, int))(*(void***)p)[0x14 / 4])(p, 3);
        void* q = *(void**)((char*)this + 0xa0);
        ((void(__thiscall*)(void*, int))(*(void***)q)[0x14 / 4])(q, 4);
        break;
    }
    }
}

// ---------------------------------------------------------------- 0x00e31220
struct CardView {
    void** vt0;      // +0x00
    void** vt1;      // +0x04
    void*  p08;      // +0x08
    void*  p0c;      // +0x0c
    void*  vecBegin; // +0x10
    void*  vecEnd;   // +0x14
    void*  vecCap;   // +0x18
    void*  p1c;      // +0x1c
    void*  buf20;    // +0x20
    char   pad[0x68 - 0x24];
    float  f68;      // +0x68
    char   pad2[0x7c - 0x6c];
    uint8_t b7c;     // +0x7c
    char   pad3[0x80 - 0x7d];
    void*  a80;      // +0x80
    void*  a84;      // +0x84
    void*  a88;      // +0x88
    void*  a8c;      // +0x8c
    void*  a90;      // +0x90
    void*  a94;      // +0x94
    void*  a98;      // +0x98
    void*  a9c;      // +0x9c
    void*  aa0;      // +0xa0
    void*  aa4;      // +0xa4
    void dtor();
    void update(float dt);
    void hide();
    void show();
    void add(uint32_t a, uint32_t b);
};

void CardView::dtor()
{
    ((void***)this)[0] = &g_vt_card0;
    ((void***)this)[1] = &g_vt_card1;
    _ReadWriteBarrier();
    void* p;
    p = aa4; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = aa0; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a9c; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a98; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a94; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a90; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a8c; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a88; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a84; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    p = a80; if (p) ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    void* b = vecBegin;
    if (b && b != buf20)
        operator_delete(b);
    p = p0c;
    if (p) ((void(__thiscall*)(void*))(*(void***)p)[2])(p);
    ((void***)this)[0] = &g_vt_editor;
    ((void***)this)[1] = &g_vt_sim;
    _ReadWriteBarrier();
}

// ---------------------------------------------------------------- 0x00e31320
CardView* __fastcall CardView_ctor(CardView* self)
{
    *(void* volatile*)((char*)self + 4) = &g_vt_sim;
    *(uint32_t volatile*)((char*)self + 8) = 0;
    *(void* volatile*)((char*)self + 0) = &g_vt_card0;
    *(void* volatile*)((char*)self + 4) = &g_vt_card1;
    *(uint32_t volatile*)((char*)self + 0x0c) = 0;
    void* buf = (char*)self + 0x28;
    *(void* volatile*)((char*)self + 0x20) = buf;
    *(void* volatile*)((char*)self + 0x14) = buf;
    *(void* volatile*)((char*)self + 0x10) = buf;
    *(void* volatile*)((char*)self + 0x18) = (char*)buf + 0x40;
    *(float volatile*)((char*)self + 0x68) = 0.0f;
    *(uint8_t volatile*)((char*)self + 0x7c) = 0;
    *(uint32_t volatile*)((char*)self + 0x80) = 0;
    *(uint32_t volatile*)((char*)self + 0x84) = 0;
    *(uint32_t volatile*)((char*)self + 0x88) = 0;
    *(uint32_t volatile*)((char*)self + 0x8c) = 0;
    *(uint32_t volatile*)((char*)self + 0x90) = 0;
    *(uint32_t volatile*)((char*)self + 0x94) = 0;
    *(uint32_t volatile*)((char*)self + 0x98) = 0;
    *(uint32_t volatile*)((char*)self + 0x9c) = 0;
    *(uint32_t volatile*)((char*)self + 0xa0) = 0;
    *(uint32_t volatile*)((char*)self + 0xa4) = 0;
    return self;
}

// ---------------------------------------------------------------- 0x00e313c0
void CardView::update(float dt)
{
    if (b7c) {
        float v = f68 - dt * 0.4f;
        f68 = v;
        if (v <= 0.0f) {
            b7c = 0;
            f68 = 0.0f;
        }
        if (f68 <= 0.0f) {
            void* p = aa4;
            ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 0);
            return;
        }
    } else {
        if (f68 >= 1.0f) {
            void* p = a88; ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
            p = a90;       ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
            p = a98;       ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
            return;
        }
        float* p = (float*)vecBegin;
        float* e = (float*)vecEnd;
        for (; p != e; p += 2) {
            float t = p[1] * dt;
            float* src = &t;
            if (*p <= t) src = p;
            float val = *src;
            f68 = val + f68;
            float d = *p - val;
            *p = d;
            if (d <= 0.0f) {
                for (float* q = p; q + 2 != e; q += 2) {
                    q[0] = q[2];
                    q[1] = q[3];
                }
                e = (float*)((char*)e - 8);
                *(void**)((char*)this + 0x14) = e;
            }
        }
        if (f68 <= 0.0f)
            return;
    }
    void* p = aa4;
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[0x7c / 4])(p, 1, 1);
    ((void(__thiscall*)(void*, float, float))(*(void***)p)[0x68 / 4])(
        p, (*(float*)((char*)this + 0x74) - *(float*)((char*)this + 0x6c)) * f68,
        *(float*)((char*)this + 0x78) - *(float*)((char*)this + 0x70));
}

// ---------------------------------------------------------------- 0x00e31550
void CardView::hide()
{
    ((void(__thiscall*)(void*, int, int))(*(void***)a84)[0x7c / 4])(a84, 1, 1);
    ((void(__thiscall*)(void*, int, int))(*(void***)a88)[0x7c / 4])(a88, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a8c)[0x7c / 4])(a8c, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a90)[0x7c / 4])(a90, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a94)[0x7c / 4])(a94, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)a98)[0x7c / 4])(a98, 1, 0);
    ((void(__thiscall*)(void*, int, int))(*(void***)aa4)[0x7c / 4])(aa4, 1, 0);
    f68 = 0.0f;
    _ReadWriteBarrier();
    Vec1c* v = (Vec1c*)((char*)this + 0x10);
    v->erase(v->begin, v->end);
    b7c = 0;
}

// ---------------------------------------------------------------- 0x00e315f0
void CardView::add(uint32_t a, uint32_t b)
{
    uint32_t local[2];
    local[0] = a;
    local[1] = b;
    char* end = (char*)vecEnd;
    if (end < (char*)vecCap) {
        *(void**)((char*)this + 0x14) = end + 8;
        if (end) {
            *(uint32_t*)end = a;
            *(uint32_t*)(end + 4) = b;
        }
        return;
    }
    ((TC*)((char*)this + 0x10))->f_d73090((char*)local, (char*)local + 8);
}

// ---------------------------------------------------------------- 0x00e31650
void CardView::show()
{
    ((TC*)((char*)this + 0x10))->f_d018d0(vecBegin, vecEnd);
    b7c = 1;
}
