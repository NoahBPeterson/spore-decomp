// slice s00f3fd90 -- scenario-tutorial surface-node helpers (0x00f3fd90..0x00f40c20).
// Module flags: /O2 /MD /Gy /TP /arch:SSE.  See manifest.txt / nonmatching.txt / partial.txt.
//
// These functions operate on the 0x238-byte "surface node" entries of the scenario-tutorial
// system: each entry is an 8-byte allocation header followed by a Noun payload.  Only the
// fields touched by these functions are named; everything else is an explicit pad.
#include "types.h"

struct Noun;
struct Entry;
struct C;

// ---------------------------------------------------------------------------
// callee stubs.  Call targets are masked relocations, so only the calling
// convention and the number of stack arguments have to be right.
// ---------------------------------------------------------------------------
void* __stdcall FUN_00f3e8a0(int nounId);       // noun lookup by id (ret 4)
void  __cdecl   FUN_00f3b710(void* e);          // per-entry reset
void* __stdcall SP_NounManager();               // cGameNounManager* (0 args)
void* __cdecl   FUN_00efe5a0();
void  __cdecl   FUN_00adc970(void* a, void* b);
void  __cdecl   FUN_00eec2b0(void* a, void* b, int c, void* d, int e);
void  __cdecl   operator_delete(void* p);
void* __cdecl   FUN_00b18e00(void* p);
uint8_t __cdecl FUN_00c9e8e0(int a, void* b);
float __cdecl   FUN_00eed3f0(int a, int b, float c, int d, float* e);
void  __cdecl   FUN_00f21850(Noun* n, float* a, float* b, float* c, float* d, int** e);
void  __cdecl   FUN_00f3b5e0(void* p, float f);
void  __cdecl   FUN_00b96600(void* a, void* b);
void* __cdecl   FUN_00b18530(void* p);

extern char DAT_01186577;
extern int  DAT_016c7aa4;   // Simulator*
extern int  DAT_015ad298;   // global object with vtable

struct Vec3p {
    void* begin;                            // +0
    void* end;                              // +4
    void* cap;                              // +8
    void dtor(void* b, void* e);
    void grow(void* a, void* b);            // push_back slow path
};

struct HTab {
    char pad[0x20];
    void find(void* out, void* key);
};

struct Entry38 {
    char pad[0x38];
    void* ctor();                           // FUN_00f257b0
};

// entry payload: 0x00 noun id, 0x70/0x74 element vector, 0x224 flags, 0x22c state.
struct Noun {
    int      nounId;                 // +0x000
    char     pad004[0x20 - 0x04];
    float    f20;                    // +0x020
    int      i24;                    // +0x024
    char     pad028[0x6e - 0x28];
    uint8_t  b6e;                    // +0x06e
    char     pad06f[0x70 - 0x6f];
    void*    arr70;                  // +0x070
    void*    arr74;                  // +0x074
    char     pad078[0x224 - 0x78];
    uint32_t flags;                  // +0x224
    char     pad228[4];
    int      state;                  // +0x22c

    // thiscall helpers (targets masked, names arbitrary)
    char  m25ee0(); char m25f20(); char m25670(); char m25680();
    char  m25730(); char m25370(); char m25490(); char m254d0();
    char  m25530(); int  m25750(); char m253f0(); char m27730();
    char  m25330(); char m25ed0(); char m253e0(); char m3b990();
    void* m_b18530();
};

// manager for SP::NounManager
struct Mgr {
    void* GetAvatar();
    void  RemoveNoun(void* n);
};

struct Hdr {
    uint32_t lo  : 30;
    uint32_t b30 : 1;
    uint32_t b31 : 1;
};
struct Entry {
    Hdr      hdr;                    // +0x000
    Noun     node;                   // +0x004
    char     tail[0x238 - 4 - sizeof(Noun)];
};

struct World {
    char    pad000[0x178];
    Vec3p   v38;                     // +0x178
    char    pad184[0x238 - 0x184];
    int     n238;                    // +0x238
    char    pad23c[0x2c10 - 0x23c];
    Vec3p   v238;                    // +0x2c10
    char    pad2c1c[8];
    uint32_t n2c24;                  // +0x2c24
};

struct C {
    char    pad000[0x10];
    World*  world;                   // +0x010
    char    pad014[0x8c - 0x14];
    Noun*   m8c;                     // +0x08c
    HTab    h90;                     // +0x090
    HTab    hB0;                     // +0x0b0

    void* m3d780(Noun* n);
    char  m3b9e0(Noun* n, void* o, int x);
    void  m3ecb0(Noun* ent, Noun* n, void* buf);
    char  m3f110(Noun* ent, void* buf, Noun* n, Entry* e, int x);
    void  m3d900();

    void    FUN_00f3fd90(int* p);
    char    FUN_00f3ff70(Noun* n);
    char    FUN_00f40090(Noun* n);
    uint8_t FUN_00f401a0();
    uint8_t FUN_00f40240(Noun* n, uint32_t* pstart);
    uint8_t FUN_00f40370();
    uint8_t FUN_00f40500(int a, int b, int c);
    int     FUN_00f40ae0(void* e);
    void    FUN_00f40c20(uint32_t key, uint32_t* out);
};

uint32_t __stdcall ScenarioTutorials_GetActive();

// ---------------------------------------------------------------------------
// @ 0x00f3fd90
// ---------------------------------------------------------------------------
void C::FUN_00f3fd90(int* p)
{
    if (*p == -2) {
        World* w = world;
        int n = (int)((char*)w->v38.end - (char*)w->v38.begin) / 0x38;
        if (n > 0) {
            int off = 0;
            do {
                FUN_00f3b710((char*)w->v38.begin + off);
                off += 0x38;
                --n;
            } while (n != 0);
        }
        Mgr* mgr = (Mgr*)SP_NounManager();
        void* avatar = mgr->GetAvatar();
        if (*(int*)((char*)DAT_016c7aa4 + 0xcc) == 1) {
            if (FUN_00efe5a0() == avatar) {
                void* g = *(void**)&DAT_015ad298;
                ((void(__thiscall*)(void*, int))(*(void***)g)[8])(g, 0);
            }
        }
        mgr = (Mgr*)SP_NounManager();
        mgr->RemoveNoun(avatar);
        Noun* obj = m8c;
        if (obj) {
            void* q = *(void**)((char*)obj + 0x20c);
            if (q && *(int*)((char*)q - 4) != 0)
                operator_delete(q);
            Vec3p* v = (Vec3p*)((char*)obj + 0x28);
            v->dtor(v->begin, v->end);
            void* r = v->begin;
            if (r && *(int*)((char*)r - 4) != 0)
                operator_delete(r);
            operator_delete(obj);
        }
        m8c = 0;
        return;
    }

    // non-destruction path: dequeue the node from the 0xb0 table and remove it.
    char* pp = (char*)p;
    char found[8];
    hB0.find(found, pp + 0x228);
    if (*(void**)((char*)this + 0xb4 + *(int*)((char*)this + 0xb8) * 4) != *(void**)found) {
        Noun* n = (Noun*)*(void**)(found + 4);
        if (*(int*)((char*)DAT_016c7aa4 + 0xcc) == 1) {
            if (FUN_00efe5a0() == n) {
                void* g = *(void**)&DAT_015ad298;
                ((void(__thiscall*)(void*, int))(*(void***)g)[8])(g, 0);
            }
        }
        Noun* o2 = (Noun*)FUN_00f3e8a0(*(int*)*(void**)(pp + 0x228));
        if (o2->m253e0())
            n->m3b990();
        Mgr* mgr = (Mgr*)SP_NounManager();
        mgr->RemoveNoun(n);
        FUN_00adc970(found, found);
        char k2[8];
        h90.find(k2, found);
        h90.find(found, k2);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f3ff70
// ---------------------------------------------------------------------------
char C::FUN_00f3ff70(Noun* n)
{
    char c2 = 0;
    Noun* obj = (Noun*)FUN_00f3e8a0(n->nounId);
    if (obj == 0) {
        if (n != m8c)
            goto check;
        n->state = -1;
        return 1;
    } else {
        char c1 = obj->m25ee0();
        c2 = obj->m25f20();
        if (c1 == 0)
            goto check;
    }
    goto ffed;
check:
    if (FUN_00c9e8e0(1, (char*)n + 4)) {
        n->state = 1;
        return 0;
    }
ffed:
    if (c2 != 0)
        goto ret1;
    if (FUN_00c9e8e0(0, (char*)n + 4) != 0)
        goto ret1;
    {
        bool b;
        if (obj == 0)
            b = true;
        else
            b = (obj->m25680() == 0);
        int local = 1;
        char buf[12];
        FUN_00eec2b0(buf, (char*)n + 4, b ? 1 : 0, &local, 1);
        if (local != 4)
            goto ret1;
        if (obj != 0 && obj->m25670() == 0) {
            n->state = 0;
            return 0;
        }
        n->state = 2;
        return 0;
    }
ret1:
    n->state = -1;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00f40090
// ---------------------------------------------------------------------------
char C::FUN_00f40090(Noun* n)
{
    if (FUN_00f3ff70(n) == 0)
        n->flags |= 2;
    else
        n->flags &= ~2u;

    Noun* ent = (Noun*)m3d780(n);
    if (ent != 0) {
        Noun* o = (Noun*)FUN_00b18e00(ent);
        if (o != 0) {
            if (m3b9e0(n, o, 0) == 0)
                n->flags |= 0x10;
            else
                n->flags &= ~0x10u;
        }
        uint32_t f = n->flags;
        bool b = ((f >> 4) & 1) != 0 || ((f >> 1) & 1) != 0 || ((f >> 2) & 1) != 0;
        Noun* q = (Noun*)FUN_00b18e00(ent);
        q->b6e = b;
        void* vt = *(void**)q;
        void* rr = ((void*(__thiscall*)(void*))((void**)vt)[0xac / 4])(q);
        if (rr != 0) {
            if (!b) {
                *(uint32_t*)((char*)rr + 4) &= ~8u;
            } else {
                *(uint32_t*)((char*)rr + 4) |= 8u;
                *(uint8_t*)((char*)rr + 0x5c) = 1;
            }
        }
    }
    uint32_t f = n->flags;
    if (((f >> 4) & 1) == 0 && ((f >> 1) & 1) == 0 && ((f >> 2) & 1) == 0)
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f401a0
// ---------------------------------------------------------------------------
uint8_t C::FUN_00f401a0()
{
    uint8_t b = 1;
    if (m8c != 0)
        b = (uint8_t)(FUN_00f40090(m8c) != 0);

    World* w = world;
    Entry* e = (w->n2c24 < 0x3fffffff)
             ? (Entry*)(w->n2c24 * 0x238 + (int)w->v238.begin)
             : (Entry*)w->v238.end;
    Entry* end = (Entry*)w->v238.end;
    while (end != e) {
        uint8_t r = (uint8_t)(FUN_00f40090(&e->node) != 0);
        b = (b && r) ? 1 : 0;
        for (;;) {
            uint32_t f = e->hdr.b30;
            e = (Entry*)((char*)e + 0x238);
            if (f) break;
            if (!e->hdr.b31) break;
        }
    }
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x00f40240
// ---------------------------------------------------------------------------
uint8_t C::FUN_00f40240(Noun* n, uint32_t* pstart)
{
    Noun* ent = (Noun*)m3d780(n);
    Noun* o = (Noun*)FUN_00b18e00(ent);
    char buf[12];
    m3ecb0(ent, n, buf);
    uint8_t b;
    if (o == 0)
        b = 1;
    else
        b = (uint8_t)m3b9e0(n, o, 0);
    if (b == 0)
        n->flags |= 0x10;
    else
        n->flags &= ~0x10u;
    b &= 1;
    if (ent != 0) {
        Noun* q = (Noun*)FUN_00b18530(ent);
        if (q != 0 && q->m25ed0() != 0) {
            n->flags &= ~4u;
            return 1;
        }
    }
    Entry* e = (Entry*)world->v238.end;
    Entry* end = (Entry*)*pstart;
    while (e != end) {
        if (((n->flags >> 2) & 1) == 0 || ((e->node.flags >> 2) & 1) == 0) {
            if (m3f110(ent, buf, n, e, 0) == 0) {
                b = 0;
                n->flags |= 4;
                e->node.flags |= 4;
            }
        }
        for (;;) {
            uint32_t f = e->hdr.b30;
            e = (Entry*)((char*)e + 0x238);
            if (f) break;
            if (!e->hdr.b31) break;
        }
    }
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x00f40370
// ---------------------------------------------------------------------------
uint8_t C::FUN_00f40370()
{
    uint8_t b = 1;
    if (m8c != 0)
        m8c->flags &= ~4u;

    World* w = world;
    Entry* e = (w->n2c24 < 0x3fffffff)
             ? (Entry*)(w->n2c24 * 0x238 + (int)w->v238.begin)
             : (Entry*)w->v238.end;
    Entry* end = (Entry*)w->v238.end;
    while (end != e) {
        e->node.flags &= ~4u;
        for (;;) {
            uint32_t f = e->hdr.b30;
            e = (Entry*)((char*)e + 0x238);
            if (f) break;
            if (!e->hdr.b31) break;
        }
    }

    if (m8c != 0) {
        Entry* st = (world->n2c24 < 0x3fffffff)
                  ? (Entry*)(world->n2c24 * 0x238 + (int)world->v238.begin)
                  : (Entry*)world->v238.end;
        b = FUN_00f40240(m8c, (uint32_t*)&st) & 1;
    }

    w = world;
    Entry* e2 = (w->n2c24 < 0x3fffffff)
              ? (Entry*)(w->n2c24 * 0x238 + (int)w->v238.begin)
              : (Entry*)w->v238.end;
    Entry* end2 = (Entry*)w->v238.end;
    while (end2 != e2) {
        Entry* cur = e2;
        for (;;) {
            uint32_t f = e2->hdr.b30;
            e2 = (Entry*)((char*)e2 + 0x238);
            if (f) break;
            if (!e2->hdr.b31) break;
        }
        b &= FUN_00f40240(&cur->node, (uint32_t*)&e2);
    }

    if (*(int*)((char*)DAT_016c7aa4 + 0xcc) != 2)
        m3d900();
    return b;
}

// ---------------------------------------------------------------------------
// @ 0x00f40500
// ---------------------------------------------------------------------------
uint8_t C::FUN_00f40500(int a, int b, int c)
{
    // State machine not reconstructed (see partial.txt).
    (void)a; (void)b; (void)c;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00f409a0
// ---------------------------------------------------------------------------
float __cdecl FUN_00f409a0(int* p, int a, float lo, int b, float* out)
{
    if (*p == -2)
        return FUN_00eed3f0(a, b, lo, 1, out);

    Noun* obj = (Noun*)FUN_00f3e8a0(*p);
    if (obj->m253f0() != 0) {
        float v18 = 0, v14 = 0, v20 = 0, v1c = 0;
        FUN_00f21850(obj, &v18, &v14, &v20, &v1c, &p);
        float r = lo;
        if (r < v18) r = v18;
        if (v14 < r) r = v14;
        if (out != 0) {
            if (lo < v20)
                *out = ((lo - v20) / ((v1c - v20) + 0.0000152587890625f)) * 0.5f;
            else
                *out = ((lo - v20) / ((v1c - v20) + 0.0000152587890625f)) * 0.5f + 0.5f;
        }
        return r;
    }
    return FUN_00eed3f0(a, b, lo, 0, out);
}

// ---------------------------------------------------------------------------
// @ 0x00f40ae0
// ---------------------------------------------------------------------------
int C::FUN_00f40ae0(void* e)
{
    World* w = world;
    int idx = (int)((char*)w->v38.end - (char*)w->v38.begin) / 0x38;
    if (idx >= w->n238)
        return -1;
    if ((uint32_t)w->v38.end < (uint32_t)w->v38.cap) {
        Entry38* slot = (Entry38*)w->v38.end;
        w->v38.end = (char*)w->v38.end + 0x38;
        if (slot)
            slot->ctor();
    } else {
        char tmp[0x10];
        Entry38* t = (Entry38*)tmp;
        void* v = t->ctor();
        w->v38.grow(w->v38.end, v);
    }
    World* w2 = world;
    char* dst = (char*)w2->v38.end - 0x38;
    ((uint32_t*)dst)[0] = ((uint32_t*)e)[0];
    ((uint32_t*)dst)[1] = ((uint32_t*)e)[1];
    ((uint32_t*)dst)[2] = ((uint32_t*)e)[2];
    if (m8c != 0)
        FUN_00f3b5e0((char*)m8c + 4, m8c->f20);
    return idx;
}

// @ 0x00f40bb0
void __stdcall FUN_00f40bb0(int* a, void* b)
{
    if (!a)
        return;
    void* obj = FUN_00f3e8a0(*a);
    if (!obj)
        return;
    uint32_t u = ScenarioTutorials_GetActive();
    int count = (*(int*)((char*)obj + 0x74) - *(int*)((char*)obj + 0x70)) / 0x4e0;
    if (u >= (uint32_t)count)
        return;
    char* node = (char*)(*(int*)((char*)obj + 0x70) + u * 0x4e0);
    if (!b)
        return;
    void* vt = *(void**)b;
    void* r = ((void*(__thiscall*)(void*, int))((void**)vt)[3])(b, (int)&DAT_01186577);
    if (!r)
        return;
    *(uint8_t*)((char*)r + 0x78) = (node[0] == 0);
}

// ---------------------------------------------------------------------------
// @ 0x00f40c20
// ---------------------------------------------------------------------------
void C::FUN_00f40c20(uint32_t key, uint32_t* out)
{
    if (key == 0xfffffffeu) {
        uint32_t* p = (uint32_t*)out[1];
        if (p >= (uint32_t*)out[2]) {
            void* a = (void*)((char*)this + 0x8c);
            FUN_00b96600(a, &out);
            return;
        }
        out[1] = (uint32_t)(p + 1);
        if (p)
            *p = *(uint32_t*)((char*)this + 0x8c);
        return;
    }
    World* w = world;
    Entry* e = (w->n2c24 < 0x3fffffff)
             ? (Entry*)(w->n2c24 * 0x238 + (int)w->v238.begin)
             : (Entry*)w->v238.end;
    Entry* end = (Entry*)w->v238.end;
    while (e != end) {
        if (e->node.nounId == (int)key) {
            uint32_t* p = (uint32_t*)out[1];
            if (p < (uint32_t*)out[2]) {
                out[1] = (uint32_t)(p + 1);
                if (p)
                    *p = (uint32_t)&e->node;
            } else {
                FUN_00b96600((void*)p, &e);
            }
        }
        for (;;) {
            uint32_t f = e->hdr.b30;
            e = (Entry*)((char*)e + 0x238);
            if (f) break;
            if (!e->hdr.b31) break;
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f404d0
// ---------------------------------------------------------------------------
uint8_t __stdcall FUN_00f404d0(int nounId, int index)
{
    void* p = FUN_00f3e8a0(nounId);
    if (p)
        return *(uint8_t*)(*(int*)((char*)p + 0x70) + index * 0x4e0 + 2);
    return 0;
}
