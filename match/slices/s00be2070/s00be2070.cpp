// Slice s00be2070: F_be2440, a 14-slot connectivity scorer (14x14 adjacency grid, ids[14]).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
#include "types.h"
#include <string.h>
#include <xmmintrin.h>

#define V4(a) virtual void a##0(); virtual void a##1(); virtual void a##2(); virtual void a##3();

struct PFIdx { uint32_t pad; int GetFileCount(); bool F_bfc600(); };
struct Part {
    uint32_t pad0[0x120 / 4 - 1];
    PFIdx idx;                      // +0x120
    uint32_t pad1[(0x28c - 0x124) / 4];
    uint32_t mF;                    // +0x28c
    int mCount;                     // +0x290
    uint32_t mE, mC, mD;            // +0x294.. +0x29c
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual uint32_t GetId();       // slot 8 (+0x20)
    void F_bcc6e0(bool b);
};
struct Wrap {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual Part* Query(uint32_t id);   // slot 3 (+0xc)
};
struct Item { Wrap* F_fcc210(); };
struct Table { uint32_t pad; Item* F_af9ff0(int i); };
struct Slot {
    uint32_t pad0[0x20 / 4];
    int mKind;                      // +0x20
    uint8_t mFlag;                  // +0x24
    uint8_t pad1[3];
    uint32_t mVal;                  // +0x28
    int mCount;                     // +0x2c
    int mIndex;                     // +0x30
    uint32_t mId;                   // +0x34
};
struct Obj3;
struct Obj2 {
    uint32_t pad0[0x2c / 4];
    int mScore;                     // +0x2c
    Slot* F_ff07a0(int i);
    bool F_ff0330(int a, int b);
    void F_ff08b0(float f, Obj3* o);
};
struct Obj1 {
    V4(a) V4(b) V4(c) V4(d) V4(e) V4(f)
    virtual void g0(); virtual void g1(); virtual void g2();
    virtual char* GetGrid();        // slot 27 (+0x6c)
    uint32_t pad0[(0x304 - 4) / 4];
    float mResult;                  // +0x304
    uint32_t pad1[(0x3ec - 0x308) / 4];
    Table tbl;                      // +0x3ec
    uint32_t pad2[(0x664 - 0x3f0) / 4];
    int mScore;                     // +0x664
    int mN1;                        // +0x668
    int mN2;                        // +0x66c
    uint32_t pad3[2];
    int mScore2;                    // +0x678
    void F_be0020();
};

enum { kA = 0x18ea1eb, kB = 0x18eb106, kC = 0x18ea2cc, kD = 0x1a56aba };

// @ 0x00be2440
void F_be2440(Obj1* a1, Obj2* a2, Obj3* a3)
{
    uint32_t D[14], C[14], E[14], F[14], ids[14];
    bool ok[14];
    int i0;
    for (i0 = 0; i0 < 14; ++i0) D[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) C[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) E[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) F[i0] = 0;
    for (i0 = 0; i0 < 14; ++i0) ok[i0] = false;
    for (i0 = 0; i0 < 14; ++i0) ids[i0] = 0;
    bool grid[14][14];
    memset(grid, 0, sizeof(grid));

    if (a1) {
        if (!a1->GetGrid()) return;
        for (uint32_t row = 0, off = 0; off < 0xc4; off += 14, ++row) {
            Item* it = a1->tbl.F_af9ff0(row);
            if (!it) continue;
            Wrap* w = it->F_fcc210();
            if (!w) continue;
            Part* p = w->Query(0xe9cb8ba);
            if (!p) continue;
            if (p->idx.GetFileCount() == 2) continue;
            if (p->mCount > 0) continue;
            if (p->idx.F_bfc600()) continue;
            ids[row] = p->GetId();
            for (uint32_t j = 0; j < 14; ++j) {
                const char* p = a1->GetGrid() + off;
                if (p[j + 0x274])
                    ((bool*)grid)[off + j] = true;
            }
        }
    } else {
        if (!a2) return;
        for (uint32_t i = 0; i < 14; ++i) {
            Slot* s = a2->F_ff07a0(i);
            if (!s) continue;
            int k = s->mIndex;
            if (s->mKind == 2) continue;
            if (s->mCount <= 0) continue;
            ids[k] = s->mId;
            for (uint32_t j = 0; j < 14; ++j) {
                if (a2->F_ff0330(k, j))
                    grid[k][j] = true;
            }
        }
    }

    for (int i = 0; i < 14; ++i)
        if (ids[i] == kA) ok[i] = true;

    bool changed;
    do {
        changed = false;
        for (int i = 0; i < 14; ++i) {
            if (ids[i] != 0 && !ok[i]) {
                for (int j = 0; j < 14; ++j) {
                    if (ids[j] != 0 && ok[j] && grid[i][j]) {
                        ok[i] = true;
                        changed = true;
                    }
                }
            }
        }
    } while (changed);

    int n1 = 0, score = 0, n2 = 0;
    int i, j;
    for (i = 0; i < 14; ++i) {
        uint32_t id = ids[i];
        if (id != 0 && ok[i]) {
            if (id == kD) { C[i] += 1; n1 += 1; }
            if (id == kC) { D[i] += 1; n2 += 1; }
            for (j = 0; j < 14; ++j) {
                uint32_t o = ids[j];
                if (i != j && o != 0) {
                    if (id == kC && (o == kA || o == kB) && grid[i][j]) { E[i] += 400; score += 400; }
                    if (id == kD && (o == kA || o == kB) && grid[i][j]) { C[i]++; n1++; }
                    if (id == kC && o == kD && grid[i][j]) { D[i]++; n2++; }
                }
            }
        }
    }

    float res = (float)(n1 - n2 + 5) * 10.0f;
    float lo = 0.0f, hi = 100.0f;
    __asm {
        movss xmm0, res
        maxss xmm0, lo
        minss xmm0, hi
        movss res, xmm0
    }

    if (a1) {
        for (int i = 0; i < 14; ++i) {
            Item* it = a1->tbl.F_af9ff0(i);
            if (!it) continue;
            Wrap* w = it->F_fcc210();
            if (!w) continue;
            Part* p = w->Query(0xe9cb8ba);
            if (!p) continue;
            p->F_bcc6e0(ok[i]);
            p->mF = F[i]; p->mE = E[i]; p->mC = C[i]; p->mD = D[i];
        }
    }
    if (a2) {
        for (int i = 0; i < 14; ++i) {
            Slot* s = a2->F_ff07a0(i);
            if (s) { s->mFlag = ok[s->mIndex]; s->mVal = F[s->mIndex]; }
        }
    }
    if (a1) {
        a1->mResult = res;
        a1->mScore = score; a1->mN1 = n1; a1->mN2 = n2; a1->mScore2 = score;
        a1->F_be0020();
    }
    if (a2) {
        a2->F_ff08b0(res, a3);
        a2->mScore = score;
    }
}

// ---------------------------------------------------------------------------
// Batch s00be2070: noun/part bookkeeping, ref-counted lists, timer message,
// trio de-serialisation and the 0x80-byte element vector insert.

struct NounMgrX
{
    void RemoveNoun(void* obj);          // 0xb225d0
    void* FindNoun(int id);              // 0xb25f40
};
extern "C" NounMgrX* NounManagerX();     // 0xb3d300
extern "C" void* GetCurrentGameModeX();  // 0xb5b800
extern "C" int GetPlayerEmpireIDX();     // 0x1021090
extern "C" void ReadInt32X(void* io, int* out, int count, int flags); // 0x93a780
extern "C" void* FUN_00d5aae0(void* vec, void** item, int unused);    // 0xd5aae0
extern "C" void* FUN_00bda980X(void* first, void* last, void* dest);  // 0xbda980
extern "C" void FUN_00be0c80X(void* vec, void** item);                // 0xbe0c80
extern "C" void* FUN_00f473a0(unsigned size, const char* name, int a, int b,
                              const char* file, int line);            // 0xf473a0
extern "C" void FUN_00f47380(void* p);                                // 0xf47380

struct UniverseX
{
    int F_c70e00();                      // 0xc70e00
};
extern "C" UniverseX* GetUniverseX();    // 0x1021260

struct Vt23X
{
    V4(q) V4(r) V4(s) V4(t) V4(u)
    virtual void q20(); virtual void q21(); virtual void q22();
    virtual void* Query(int id);          // slot 23 (+0x5c)
};
struct Has588X
{
    uint8_t pad[0x588];
    Vt23X sub;                            // +0x588
};
struct CircleX
{
    void RemoveAgent(void* obj);          // 0xafae50
};
struct TimerX
{
    void Restart();                       // 0xbc3130
};
struct NotifyX
{
    void F_ff03b0(int id);                // 0xff03b0
    void F_ff03c0(float f);               // 0xff03c0
};
struct V19X
{
    V4(a) V4(b) V4(c) V4(d)
    virtual void e0e(); virtual void e1e(); virtual void e2e();
    virtual int GetId19();                // slot 19 (+0x4c)
};
struct MapX
{
    uint8_t pad[0x1a8];
    int* F_get(const int* key);           // 0x643a40
};
struct Vec354X
{
    void** begin; void** end; void** cap;
};
struct PtrVecD0X
{
    void* begin; void* end; void* cap;
    void F_b48e40(void* first, void* last);                    // 0xb48e40
    void F_bdefa0(void* a, void* b, void* c, void* d);         // 0xbdefa0
};
struct Ref60X
{
    V4(r0) V4(r1) V4(r2) V4(r3) V4(r4) V4(r5)
    virtual void AddRef();                // slot 24 (+0x60)
    virtual void Release();               // slot 25 (+0x64)
};
struct RefVec60X
{
    Ref60X** begin; Ref60X** end; Ref60X** cap;
    void F_ae6ed0(Ref60X** pos, Ref60X** val);   // 0xae6ed0
};
struct RefVX
{
    virtual void AddRef();                // slot 0
    virtual void Release();               // slot 1
    virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7();
    virtual int GetId();                  // slot 8 (+0x20)
};
struct RefVecBX
{
    RefVX** begin; RefVX** end; RefVX** cap;
    void F_e25bd0(void* first, void* last);       // 0xe25bd0
    void F_aea5d0(RefVX** pos, RefVX** val);      // 0xaea5d0
};
struct MsgX
{
    uint32_t vt;                          // +0x00
    uint32_t pad0[3];
    float f;                              // +0x10
    uint32_t pad1;
    int i;                                // +0x18
    uint32_t pad2;
};
struct C2cObj
{
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4(); virtual void c5(); virtual void c6();
    virtual void F_1c();                  // slot 7 (+0x1c)
    virtual void* F_20();                 // slot 8 (+0x20)
    virtual void c9();
    virtual void F_28(int id, void** out, int unused);  // slot 10 (+0x28)
    virtual void c11(); virtual void c12();
    virtual void F_34(void* buf, int n);  // slot 13 (+0x34)
    void F_bdea50(int n);                 // 0xbdea50
};
struct IoObj
{
    V4(i0) virtual void i4(); virtual void i5();
    virtual void* F_18();                 // slot 6 (+0x18)
};
struct TrioX
{
    RefVX* a; RefVX* b; int c;
};
struct TrioVecX
{
    TrioX* begin; TrioX* end; TrioX* cap;
    void F_bda6d0(TrioX* first, TrioX* last);     // 0xbda6d0
    void F_bdf480(TrioX* pos, TrioX* val);        // 0xbdf480
};
struct AllocHdrX
{
    int mRef;                             // header word at elem[-4]
};
struct Timer80X
{
    uint8_t pad[0x20];
    void F_dtor();                        // 0xb638b0
};
struct RelObjX
{
    V4(r0) V4(r1) V4(r2) V4(r3) V4(r4) V4(r5)
    V4(r6) V4(r7) V4(r8) V4(r9) V4(r10) V4(r11)
    virtual void F_c0();                  // slot 48 (+0xc0)
};
struct Elem80X
{
    uint8_t hdr[0x30];
    Timer80X t30;                         // +0x30
    Timer80X t50;                         // +0x50
    RelObjX* p70;                         // +0x70
    uint32_t w74;                         // +0x74
    RelObjX* p78;                         // +0x78
    uint32_t w7c;                         // +0x7c
    void F_copy(const Elem80X* src);      // 0xbdd380
};
struct Vec80X
{
    Elem80X* begin; Elem80X* end; Elem80X* cap;
    void F2ee0(Elem80X* pos, unsigned n, Elem80X* value);
};
extern "C" Elem80X* F_bdd5c0X(Elem80X* first, Elem80X* last, Elem80X* dest); // 0xbdd5c0
extern "C" void F_bd8480X(Elem80X* first, Elem80X* last, Elem80X* dest);     // 0xbd8480
extern "C" void F_bdf1a0X(Elem80X* dest, unsigned n, const Elem80X* value);  // 0xbdf1a0
extern "C" void F_bdd580X(Elem80X** cursor, Elem80X* first, Elem80X* last,
                          Elem80X* dest, Elem80X* value);                    // 0xbdd580
extern "C" void F_bdd640X(Elem80X* first, Elem80X* last, Elem80X* dest);     // 0xbdd640
extern "C" void F_bdf170X(Elem80X* first, Elem80X* last, Elem80X* value);    // 0xbdf170

struct C2X
{
    V4(a) V4(b) V4(c) V4(d)
    virtual void e0e(); virtual void e1e(); virtual void e2e();
    virtual int F_GetId();                // slot 19 (+0x4c)
    uint8_t pad_0d0[0xd0 - 4];
    PtrVecD0X m_vecD0;                    // +0xd0
    uint8_t pad_250[0x250 - 0xdc];
    TimerX m_timer250;                    // +0x250
    uint8_t pad_2f0[0x2f0 - 0x251];
    NotifyX* m_notify;                    // +0x2f0
    uint8_t pad_340[0x340 - 0x2f4];
    RefVX** m_begin340;                   // +0x340
    RefVX** m_end344;                     // +0x344
    uint8_t pad_354[0x354 - 0x348];
    Vec354X m_vec354;                     // +0x354
    uint8_t pad_4b4[0x4b4 - 0x360];
    CircleX m_circle;                     // +0x4b4
    uint8_t pad_548[0x548 - 0x4b5];
    RefVec60X m_vec548;                   // +0x548
    uint8_t pad_590[0x590 - 0x554];
    V19X* m_590;                          // +0x590
    uint8_t pad_5a0[0x5a0 - 0x594];
    MapX m_map;                           // +0x5a0
    float m_timerA;                       // +0x748
    int m_idA;                            // +0x74c
    float m_score;                        // +0x750
    int m_idB;                            // +0x754
    float m_timerC;                       // +0x758
    int m_idC;                            // +0x75c

    bool F_00c004c0X(int v);              // 0xc004c0
    void FUN_00be2110();
    void FUN_00be2070(void* obj, int param3);
    PtrVecD0X* FUN_00be2340();
    void FUN_00be2390(Ref60X* obj);
    void FUN_00be2420(void* arg);
    void FUN_00be2b10(int id, RefVecBX* out);
    void FUN_00be2bb0(float f, int i);
    void F_be06c0X(void* msg, int a, int b);   // 0xbe06c0
    void F_00bd9e50X();                        // 0xbd9e50
};

// @ 0x00be2070
void C2X::FUN_00be2070(void* obj, int param3)
{
    if (m_vec354.begin == m_vec354.end)
        return;
    if (!obj)
    {
        void* raw = *m_vec354.begin;
        if (!raw)
            return;
        obj = ((Has588X*)raw)->sub.Query(0x436f315);
        if (!obj)
            return;
    }
    m_circle.RemoveAgent(obj);
    NounManagerX()->RemoveNoun(obj);
    FUN_00d5aae0(&m_vec354, &obj, param3);
    if ((uint8_t)param3 == 0 && GetCurrentGameModeX() == (void*)0x1654c05)
        F_00bd9e50X();
}

// @ 0x00be2110
void C2X::FUN_00be2110()
{
    if (GetCurrentGameModeX() == (void*)0x1654c05)
    {
        if (GetUniverseX()->F_c70e00() != 4)
            return;
        if (m_idA == GetPlayerEmpireIDX())
            return;
    }

    if (!F_00c004c0X(0))
    {
        float t = m_timerA - 0.1f;
        m_timerA = t;
        if (t <= 0.0f)
        {
            m_idA = -1;
            m_timerA = 0.0f;
        }
    }

    if (m_idB != -1)
    {
        int key = m_590->GetId19();
        int* p1 = m_map.F_get(&m_idB);
        float base = (float)(*p1 * 200);
        int* p2 = m_map.F_get(&m_idB);
        int* p3 = m_map.F_get(&key);
        float s = base / (float)(*p2 + *p3);
        m_score = s;
        float lo = 0.0f;
        float hi = 100.0f;
        s = s > lo ? s : lo;
        s = s < hi ? s : hi;
        m_score = s;
        if (s <= 0.0f)
        {
            m_idB = -1;
            m_score = 0.0f;
        }
    }

    if (m_idA != -1)
    {
        if (NounManagerX()->FindNoun(m_idA) == 0 || F_GetId() == m_idA)
        {
            m_idA = -1;
            m_timerA = 0.0f;
        }
    }
    if (m_idB != -1)
    {
        if (NounManagerX()->FindNoun(m_idB) == 0 || F_GetId() == m_idB)
        {
            m_idB = -1;
            m_timerA = 0.0f;
        }
    }
    if (m_idC != -1)
    {
        if (NounManagerX()->FindNoun(m_idC) == 0 || F_GetId() == m_idC)
        {
            m_idC = -1;
            m_timerC = 0.0f;
        }
    }

    if (m_notify)
    {
        m_notify->F_ff03b0(m_idA);
        m_notify->F_ff03c0(m_timerA);
    }
}

// @ 0x00be2340
PtrVecD0X* C2X::FUN_00be2340()
{
    C2X* const volatile self = this;
    PtrVecD0X* v = &m_vecD0;
    v->F_b48e40(v->begin, v->end);
    v->F_bdefa0(v->end, m_begin340, m_end344, self);
    return v;
}

// @ 0x00be2390
void C2X::FUN_00be2390(Ref60X* obj)
{
    Ref60X** it = m_vec548.begin;
    Ref60X** last = m_vec548.end;
    while (it != last && *it != obj)
        ++it;
    if (it != last)
        return;

    if (obj)
        obj->AddRef();
    if (m_vec548.end < m_vec548.cap)
    {
        Ref60X** slot = m_vec548.end;
        m_vec548.end = slot + 1;
        if (slot)
        {
            *slot = obj;
            if (obj)
                obj->AddRef();
        }
    }
    else
    {
        m_vec548.F_ae6ed0(m_vec548.end, &obj);
    }
    if (obj)
        obj->Release();
}

// @ 0x00be2420
void C2X::FUN_00be2420(void* arg)
{
    FUN_00be0c80X(&m_vec548, &arg);
}

// @ 0x00be2b10
void C2X::FUN_00be2b10(int id, RefVecBX* out)
{
    out->F_e25bd0(out->begin, out->end);
    for (RefVX** p = m_begin340; p != m_end344; ++p)
    {
        RefVX* o = *p;
        if (o && o->GetId() == id)
        {
            o->AddRef();
            if (out->end < out->cap)
            {
                RefVX** slot = out->end;
                out->end = slot + 1;
                if (slot)
                {
                    *slot = o;
                    o->AddRef();
                }
            }
            else
            {
                out->F_aea5d0(out->end, &o);
            }
            if (o)
                o->Release();
        }
    }
}

// @ 0x00be2bb0
void C2X::FUN_00be2bb0(float f, int i)
{
    MsgX m;
    m.vt = 0x5f601f4;
    m.f = f;
    m.i = i;
    F_be06c0X(&m, 2000, 0);
    m_timer250.Restart();
}

// @ 0x00be2c00
void FUN_00be2c00X(C2cObj* self, TrioVecX* vec)
{
    TrioX* first = vec->begin;
    TrioX* last = vec->end;
    void* copyEnd = FUN_00bda980X(last, last, first);
    vec->F_bda6d0((TrioX*)copyEnd, vec->end);
    vec->end = first;

    unsigned n = 0;
    IoObj* ioObj = (IoObj*)self->F_20();
    void* io = ioObj->F_18();
    ReadInt32X(io, (int*)&n, 1, 0);
    self->F_bdea50(n);

    TrioX trio;
    unsigned i = 0;
    if (n != 0)
    {
        do
        {
            trio.a = 0;
            trio.b = 0;
            self->F_28(0x2bca14b, (void**)&trio.b, 0);
            RefVX* oldA = trio.a;
            if (oldA)
            {
                trio.a = 0;
                oldA->Release();
            }
            self->F_28(0xee9b2232, (void**)&trio.a, 0);
            self->F_34(&trio.c, 4);

            if (vec->end < vec->cap)
            {
                TrioX* slot = vec->end;
                vec->end = slot + 1;
                if (slot)
                {
                    slot->a = trio.a;
                    if (trio.a)
                        trio.a->AddRef();
                    slot->b = trio.b;
                    if (trio.b)
                        trio.b->AddRef();
                    slot->c = trio.c;
                }
            }
            else
            {
                vec->F_bdf480(vec->end, &trio);
            }
            if (trio.b)
                trio.b->Release();
            if (trio.a)
                trio.a->Release();
            ++i;
        } while (i < n);
    }

    self->F_1c();
}

// @ 0x00be2ee0
void Vec80X::F2ee0(Elem80X* pos, unsigned n, Elem80X* value)
{
    unsigned capCount = (unsigned)(cap - end);
    if (capCount < n)
    {
        unsigned oldCount = (unsigned)(end - begin);
        unsigned newCap = oldCount * 2;
        if (oldCount == 0)
            newCap = 1;
        unsigned want = oldCount + n;
        if (want > newCap)
            newCap = want;

        Elem80X* buffer = 0;
        if (newCap != 0)
            buffer = (Elem80X*)FUN_00f473a0(newCap * 0x80, (const char*)0x13f09b4, 0, 0,
                                            (const char*)0x13ebb38, 0xd1);

        Elem80X* kept = F_bdd5c0X(begin, pos, buffer);
        F_bd8480X(begin, pos, buffer);
        F_bdf1a0X(kept, n, value);
        Elem80X* newEnd = F_bdd5c0X(pos, end, kept + n);
        F_bd8480X(pos, end, kept + n);

        if (begin && ((AllocHdrX*)begin)[-1].mRef != 0)
            FUN_00f47380(begin);

        begin = buffer;
        end = newEnd;
        cap = buffer + newCap;
        return;
    }

    if (n == 0)
        return;

    Elem80X temp;
    temp.F_copy(value);

    Elem80X* oldEnd = end;
    unsigned tailCount = (unsigned)(oldEnd - pos);
    Elem80X* fillEnd;
    Elem80X* cursor = 0;

    if (n < tailCount)
    {
        Elem80X* src = oldEnd - n;
        F_bdd580X(&cursor, src, oldEnd, oldEnd, cursor);
        end = end + n;
        F_bdd640X(pos, src, oldEnd);
        fillEnd = pos + n;
    }
    else
    {
        F_bdf1a0X(oldEnd, n - tailCount, &temp);
        end = end + (n - tailCount);
        F_bdd580X(&cursor, pos, oldEnd, end, cursor);
        end = end + tailCount;
        fillEnd = oldEnd;
    }

    F_bdf170X(pos, fillEnd, &temp);

    if (temp.p78)
        temp.p78->F_c0();
    if (temp.p70)
        temp.p70->F_c0();
    temp.t50.F_dtor();
    temp.t30.F_dtor();
}
