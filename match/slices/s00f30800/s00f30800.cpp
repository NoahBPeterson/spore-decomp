// Slice s00f30800 -- Simulator scenario impact-list region (bfs2), part 2.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// Sixteen functions: eastl vector<PairBlock> helpers (element stride 0x84 with
// two ref-counted interface pointers and a 0x7c-byte payload), the SimSingleton
// ctor/dtor, and two simulator AI/terraform routines.  Retail layout is reached
// through raw byte offsets; direct callees are declared with their original VA.
#include "types.h"

// --- direct callees (address comments; call targets are relocations) --------
void  __cdecl FUN_00f30800_impl(void*, void*);                 // 0x00F30800 (payload copy, thiscall)
void  __cdecl FUN_00f308d0_impl(void*, void*);                 // 0x00F308D0 (range destroy)
void* __cdecl FUN_00f30910_impl(void*, void*);                 // 0x00F30910 (element assign)
void* __cdecl FUN_00f30980_impl(void*, void*, void*);          // 0x00F30980 (range destroy -> dst)
void* __cdecl FUN_00f30a10_impl(void*, void*, void*);          // 0x00F30A10 (range move-destroy)
void* __cdecl FUN_00f30b20_impl(void*, void*);                 // 0x00F30B20 (elem construct)
void* __cdecl FUN_00f30b60_impl(void*, void*, void*);          // 0x00F30B60 (range construct)
void* __cdecl FUN_00f309d0_impl(void*, void*, void*);          // 0x00F309D0 (range shift)
void* __cdecl FUN_00f31040_impl(void*, void*);                 // 0x00F31040 (grow insert)
void* __cdecl FUN_00f31190_impl(void*);                        // 0x00F31190 (push-back)

void  __cdecl SP_cGonzagoSimulator_ctor(void*);                // 0x00B5B6C0
void  __cdecl SP_cGonzagoSimulator_a(void*);                   // 0x00B5B6F0
void  __cdecl SP_cGonzagoSimulator_b(void*);                   // 0x00B5B690
void  __cdecl operator_delete__(void*);                        // 0x00F47380
void* __cdecl FUN_00f3f950(void*);                            // 0x00F3F950
int   __cdecl FUN_00c7d070(void*);                             // 0x00C7D070
bool  __cdecl FUN_00c7d6d0(void*, void*);                      // 0x00C7D6D0
int   __cdecl FUN_006c0200(void*);                             // 0x006C0200
bool  __cdecl FUN_00bfc480(void*);                             // 0x00BFC480
int   __cdecl Resource_GetFileCount(void*);                    // 0x008E7F80
void* __cdecl FUN_00ac80d0(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*); // 0x00AC80D0
void* __cdecl FUN_01021260(void);                              // 0x01021260
float __cdecl FUN_00c70a20(void*);                             // 0x00C70A20
void* __cdecl FUN_01049a10(void);                              // 0x01049A10
float __cdecl cTerraformTuning_GetLavaThreshold(void*);        // 0x01049BF0
void* __cdecl SP_PlanetModel(void);                            // 0x00B3D350
float __cdecl cPlanetModel_GetWaterHeight(void*);              // 0x00B7E390
bool  __cdecl FUN_00b7e3e0(void*, void*);                      // 0x00B7E3E0
void* __cdecl SP_NounManager(void);                            // 0x00B3D300
void* __cdecl cGameNounManager_GetGameDataVector(void*, void*, void*, void*, void*, void*); // 0x00B21340
void* __cdecl FUN_00b3d320(void*, int);                        // 0x00B3D320
void* __cdecl TerrainMgr_Fn1(void*);                           // 0x00B1DAF0
bool  __cdecl SP_GetPropertyAsFloatArray(void*, unsigned, void*, void*); // 0x006A08B0
void  __cdecl SpVectorM_resize(void*, int);                    // 0x004AFC80
void  __cdecl FUN_00f23d20(void*, void*, void*);               // 0x00F23D20
void* __cdecl FUN_00bc97f0(int, int, int, int);                // 0x00BC97F0
void* __cdecl FUN_00f30210(void*, void*, void*, void*);        // 0x00F30210 PairBlock::ctor
void  __cdecl FUN_00f30290(void*, void*);                      // 0x00F30290 Scenario_TouchDamage
void  __cdecl FUN_00f305d0(void*, void*, void*, void*, void*, void*, void*, void*, void*, void*, void*); // 0x00F305D0 Scenario_Impact
void  __cdecl FUN_00f307e0(void*);                             // 0x00F307E0 PairBlock::dtor
float __cdecl FUN_00c03250(void*);                             // 0x00C03250
void  __cdecl FUN_00b1e500(void);                              // 0x00B1E500
void  __cdecl FUN_00ace0f0(void);                              // 0x00ACE0F0
void  __cdecl FUN_00d3d420(void);                              // 0x00D3D420
void  __cdecl FUN_00cd7d10(void);                              // 0x00CD7D10

// --- data -------------------------------------------------------------------
extern int      g_16c84dc;           // 0x016C84DC  vector<PairBlock>::mpBegin
extern int      g_16c84e0;           // 0x016C84E0  vector<PairBlock>::mpEnd
extern int      g_16c84e4;           // 0x016C84E4  vector<PairBlock>::mpCap
extern int      g_16c8480;           // 0x016C8480  frame counter
extern int      g_168d824;           // 0x0168D824  the SimSingleton global
extern int      g_16c7aa4;           // 0x016C7AA4  global manager
extern void*    g_148cec4;           // 0x0148CEC4  float constant (FLT_MAX)
extern void*    g_15b0124;           // 0x015B0124  float constant
extern void*    g_13f9428;           // 0x013F9428  float constant (0.001f)
extern void*    g_13f94d4;           // 0x013F94D4  interface id
extern void*    g_13eb8a0;           // 0x013EB8A0  float constant
extern void*    g_1471064;           // 0x01471064  float constant (0.5f)
extern void*    g_13f09b4;           // 0x013F09B4  "Simulator"
extern void*    g_16c848c;           // 0x016C848C
extern void*    g_1654c10;           // 0x01654C10
extern char*    g_148cf14;           // 0x0148CF14  vtbl_Simulator::SimSingleton
extern char*    g_148cef0;           // 0x0148CEF0
extern char*    g_148cf54;           // 0x0148CF54
extern char*    g_148cf30;           // 0x0148CF30
extern char*    g_13ec458;           // 0x013EC458
extern char*    g_13eb938;           // 0x013EB938
extern void*    g_18eb45e;           // 0x018EB45E  class id constant

// ---------------------------------------------------------------------------
// A single impact-list entry: two ref-counted interface pointers (vtable slot
// 0 = AddRef, slot 4 = Release) followed by a 0x7c-byte payload.
// The 0x7c-byte payload that rides after the two interface pointers.  The copy
// routine (0x00F30800) is entered with `this` = the payload, not the entry.
struct Payload {
    unsigned u0;            // +0x00
    float    f[25];         // +0x04 .. +0x67
    unsigned u1;            // +0x68
    unsigned u2;            // +0x6c
    float    f2;            // +0x70
    float    f3;            // +0x74
    char     c0;            // +0x78
    char     c1;            // +0x79

    void __thiscall CopyFrom(const Payload* s);             // 0x00F30800
};

struct PairBlock {
    void*    p0;
    void*    p1;
    Payload  payload;

    static const unsigned STRIDE = 0x84;

    PairBlock* __thiscall Assign(const PairBlock* s);       // 0x00F30910
    PairBlock* __thiscall Construct(const PairBlock* s);    // 0x00F30B20
};

// The impact-list vector itself (only the ops that live in this slice).
struct ImpactList {
    void __thiscall DestroyRange(PairBlock* first, PairBlock* last);  // 0x00F308D0
};

// Vtable-slot helpers --------------------------------------------------------
static inline float SqrtFF(float x) {
    float r;
    __asm { fld x  __asm fsqrt  __asm fstp r }
    return r;
}
static inline void AddRef(void* p) {
    if (p) (*(void(__thiscall**)(void*))(*(char**)p))(p);
}
static inline void Release(void* p) {
    if (p) (*(void(__thiscall**)(void*))(*(char**)p + 4))(p);
}

// ---------------------------------------------------------------------------
// @ 0x00f30800
void __thiscall Payload::CopyFrom(const Payload* s)
{
    u0 = s->u0;
    f[0] = s->f[0];   f[1] = s->f[1];   f[2] = s->f[2];   f[3] = s->f[3];
    f[4] = s->f[4];   f[5] = s->f[5];   f[6] = s->f[6];   f[7] = s->f[7];
    f[8] = s->f[8];   f[9] = s->f[9];   f[10] = s->f[10]; f[11] = s->f[11];
    f[12] = s->f[12]; f[13] = s->f[13]; f[14] = s->f[14]; f[15] = s->f[15];
    f[16] = s->f[16]; f[17] = s->f[17]; f[18] = s->f[18]; f[19] = s->f[19];
    f[20] = s->f[20]; f[21] = s->f[21]; f[22] = s->f[22]; f[23] = s->f[23];
    f[24] = s->f[24];
    u1 = s->u1;
    u2 = s->u2;
    f2 = s->f2;
    f3 = s->f3;
    c0 = s->c0;
    c1 = s->c1;
}

// ---------------------------------------------------------------------------
// @ 0x00f308d0
void __thiscall ImpactList::DestroyRange(PairBlock* first, PairBlock* last)
{
    for (; first < last; first = (PairBlock*)((char*)first + PairBlock::STRIDE)) {
        Release(first->p1);
        Release(first->p0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f30910
PairBlock* __thiscall PairBlock::Assign(const PairBlock* s)
{
    if (s->p0 != p0) {
        AddRef(s->p0);
        void* old = p0;
        p0 = s->p0;
        Release(old);
    }
    if (s->p1 != p1) {
        AddRef(s->p1);
        void* old = p1;
        p1 = s->p1;
        Release(old);
    }
    payload = s->payload;
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00f30980
PairBlock* __cdecl RangeDestroyTo(PairBlock* first, PairBlock* last, PairBlock* dst)
{
    if (first == last) return dst;
    do {
        Release(first->p1);
        Release(first->p0);
        first = (PairBlock*)((char*)first + PairBlock::STRIDE);
        dst = (PairBlock*)((char*)dst + PairBlock::STRIDE);
    } while (first != last);
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00f30a10
PairBlock* __cdecl RangeMoveDestroy(PairBlock* first, PairBlock* last, PairBlock* dst)
{
    if (last == first) return dst;
    PairBlock* out = dst;
    do {
        --last;
        --dst;
        if (last->p0 != dst->p0) {
            AddRef(last->p0);
            void* old = dst->p0;
            dst->p0 = last->p0;
            Release(old);
        }
        if (last->p1 != dst->p1) {
            AddRef(last->p1);
            void* old = dst->p1;
            dst->p1 = last->p1;
            Release(old);
        }
        dst->payload = last->payload;
        out = dst;
    } while (last != first);
    return out;
}

// ---------------------------------------------------------------------------
// @ 0x00f30b20
PairBlock* __thiscall PairBlock::Construct(const PairBlock* s)
{
    p0 = s->p0;
    AddRef(p0);
    p1 = s->p1;
    AddRef(p1);
    payload.CopyFrom(&s->payload);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00f30b60
PairBlock* __cdecl RangeConstruct(PairBlock* first, PairBlock* last, PairBlock* dst)
{
    if (first == last) return dst;
    do {
        if (dst) {
            dst->p0 = first->p0;
            AddRef(dst->p0);
            dst->p1 = first->p1;
            AddRef(dst->p1);
            dst->payload.CopyFrom(&first->payload);
        }
        first = (PairBlock*)((char*)first + PairBlock::STRIDE);
        dst = (PairBlock*)((char*)dst + PairBlock::STRIDE);
    } while (first != last);
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00f30bc0
void* __fastcall SimSingleton_ctor(void* self)
{
    SP_cGonzagoSimulator_ctor(self);
    *(char**)self = g_148cf14;
    *(char**)((char*)self + 8) = g_148cef0;
    g_168d824 = (int)self;
    SP_cGonzagoSimulator_a(self);
    *(char**)self = g_148cf54;
    *(char**)((char*)self + 8) = g_148cf30;
    *(int*)((char*)self + 0x10) = 0;
    *(int*)((char*)self + 0x14) = 0;
    *(int*)((char*)self + 0x18) = 0;
    return self;
}

// ---------------------------------------------------------------------------
// @ 0x00f30c40
void __fastcall SimSingleton_dtor(void* self)
{
    *(char**)self = g_148cf54;
    *(char**)((char*)self + 8) = g_148cf30;
    int p = *(int*)((char*)self + 0x10);
    if (p && *(int*)(p - 4)) operator_delete__((void*)p);
    *(char**)self = g_148cf14;
    *(char**)((char*)self + 8) = g_148cef0;
    SP_cGonzagoSimulator_b(self);
    if (g_168d824 == (int)self) g_168d824 = 0;
    *(char**)self = g_13ec458;
    *(char**)((char*)self + 8) = g_13eb938;
}

// ---------------------------------------------------------------------------
// @ 0x00f30cc0
void* __cdecl Scenario_PickNearest(void* mgr, float range)
{
    if (!mgr) return 0;
    void* cis = (*(void*(__thiscall**)(void*, unsigned))(*(char**)mgr + 0x5c))(mgr, 0x7b3a16f);
    if (!cis) return 0;

    int mg = g_16c7aa4;
    void* a = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0xc))(mgr);
    void* ctx = FUN_00f3f950(a);
    void* b = (*(void*(__thiscall**)(void*))(*(char**)mgr + 0xc))(mgr);
    unsigned ownerId = (*(unsigned(__thiscall**)(void*))(*(char**)b + 0x4c))(b);
    int stateId = -1;
    if (ctx && *(int*)((char*)ctx + 0x4b8) == 5)
        stateId = *(int*)((char*)ctx + 0x4c4);

    void* c = (*(void*(__thiscall**)(void*))(*(char**)mgr + 8))(mgr);
    float* pos = (float*)(*(void*(__thiscall**)(void*))(*(char**)c + 0x2c))(c);
    float px = pos[0], py = pos[1], pz = pos[2];

    void* v = (void*)FUN_00c7d070((void*)cis);
    unsigned* it = *(unsigned**)v;
    unsigned* end = *(unsigned**)((char*)v + 4);

    void* best = 0;
    float bestDist = *(float*)&g_148cec4;
    char f13 = 0, b10 = 0, b13 = 0, hasBest = 0;

    for (; it != end; ++it) {
        void* e = (void*)*it;
        if (!e) continue;
        void* cbt = (*(void*(__thiscall**)(void*, void*))(*(char**)e + 0xb8))(e, (void*)&g_13f94d4);
        if (!cbt) continue;
        if (Resource_GetFileCount(cbt) == 2) continue;
        unsigned v25 = (*(unsigned(__thiscall**)(void*))(*(char**)cbt + 0x10))(cbt);
        if (v25 == ownerId) continue;
        void* cx = (*(void*(__thiscall**)(void*))(*(char**)cbt + 0xc))(cbt);
        int kind = (*(int(__thiscall**)(void*))(*(char**)cx + 0x20))(cx);
        if (kind == 0x18c84a9 || kind == 0x3a2511e || kind == 0x18c88e4) continue;

        float* ep = (float*)(*(void*(__thiscall**)(void*))(*(char**)e + 0x2c))(e);
        float f4 = ep[0], f5 = ep[1], f6 = ep[2];
        float rad = (*(float(__thiscall**)(void*))(*(char**)e + 0x74))(e);
        float dist = SqrtFF((f6 - pz) * (f6 - pz) + (f5 - py) * (f5 - py) + (f4 - px) * (f4 - px));
        dist -= rad;

        (*(int(__thiscall**)(void*))(*(char**)cbt + 0xc))(cbt);
        bool b29 = FUN_00c7d6d0((void*)((char*)mgr + 0xc), 0);
        bool b11 = false;
        if (stateId != -1) {
            void* cz = (*(void*(__thiscall**)(void*))(*(char**)cbt + 0xc))(cbt);
            int* q = (int*)FUN_006c0200(cz);
            if (q && *q == stateId) b11 = true;
        }
        bool b12 = !(ownerId > 4 || v25 > 4);
        bool b15 = false;
        bool b9 = true;
        if (ctx && *(int*)((char*)ctx + 0x4b8) == 1) {
            if (!(range <= dist || dist <= *(float*)&g_148cec4 || range <= 0.0f)) {
                b9 = false;
                if (!hasBest) b15 = true;
            }
        }
        void* cw = (*(void*(__thiscall**)(void*))(*(char**)cbt + 0xc))(cbt);
        int kind2 = (*(int(__thiscall**)(void*))(*(char**)cw + 0x20))(cw);
        bool accept = ((kind2 != 0x70703b3 || !((b11 || b12) && !FUN_00bfc480(cbt)))
                       && (!b29 || b13)
                       && (b11 || !b10)
                       && (b9 || !hasBest)
                       && (b15 || (b12 || !f13))
                       && ((b13 && !b29) || ((b11 && !b10) || (b9 && !hasBest))
                           || (((!b15 && b12) && !f13) || dist < bestDist)));
        if (accept) {
            bestDist = dist;
            best = cbt;
            hasBest = b9;
            b10 = b11;
            f13 = b12;
            b13 = b29;
        }
    }
    return best;
}

// ---------------------------------------------------------------------------
// @ 0x00f311c0
void __cdecl ImpactList_Clear(void)
{
    int iVar1 = g_16c84e0;
    int iVar3 = g_16c84dc;
    g_16c8480 = 0;
    void* u = FUN_00f309d0_impl((void*)g_16c84e0, (void*)g_16c84e0, (void*)g_16c84dc);
    FUN_00f308d0_impl(u, (void*)g_16c84e0);
    int d = iVar1 - iVar3;
    d = (int)((long long)d * -0x3e0f83e1 >> 32);
    d = (d >> 5) + ((unsigned)d >> 31);
    g_16c84e0 += d * 0x84;
}

// ---------------------------------------------------------------------------
// @ 0x00f31220
void __cdecl Simulator_OnEvent(int* p)
{
    void* a = (void*)p[0x1a];
    void* b = (void*)p[0x1b];
    void* ia = a ? (*(void*(__thiscall**)(void*, unsigned))(*(char**)a + 0xc))(a, 0x8367427) : 0;
    void* ib = b ? (*(void*(__thiscall**)(void*, unsigned))(*(char**)b + 0xc))(b, 0x8367427) : 0;

    int kind = *p;
    if (kind == 0) {
        if (!ia) return;
        PairBlock tmp;
        FUN_00f30210(&tmp, a, b, p);
        if (g_16c84e0 < g_16c84e4) {
            int e = g_16c84e0;
            g_16c84e0 = e + 0x84;
            if (e) FUN_00f30b20_impl((void*)e, &tmp);
        } else {
            FUN_00f31040_impl((void*)g_16c84e0, &tmp);
        }
        Release(tmp.p1);
        Release(tmp.p0);
        return;
    }
    if (kind == 2) {
        bool b0b = false;
        if (ia) {
            if (*(int*)((char*)ia + 4) == 0xb) b0b = true;
            else if (ib && *(int*)((char*)ib + 4) == 0xb) b0b = true;
        } else if (ib) {
            if (*(int*)((char*)ib + 4) == 0xb) b0b = true;
        }
        if (b0b) {
            PairBlock tmp;
            FUN_00f30210(&tmp, a, b, p);
            FUN_00f31190_impl(&tmp);
            Release(tmp.p1);
            Release(tmp.p0);
        } else if ((ia || ib) && ((char*)p)[0x78] == 0 && ((char*)p)[0x79] == 0) {
            PairBlock tmp;
            FUN_00f30210(&tmp, a, b, p);
            FUN_00f31190_impl(&tmp);
            Release(tmp.p1);
            Release(tmp.p0);
        }
    } else if (kind == 3) {
        if (!ia && !ib) return;
        PairBlock tmp;
        FUN_00f30210(&tmp, a, b, p);
        if (g_16c84e0 < g_16c84e4) {
            int e = g_16c84e0;
            g_16c84e0 = e + 0x84;
            if (e) FUN_00f30b20_impl((void*)e, &tmp);
        } else {
            FUN_00f31040_impl((void*)g_16c84e0, &tmp);
        }
        Release(tmp.p1);
        Release(tmp.p0);
    } else {
        return;
    }

    {
        int kindA = (*(int(__thiscall**)(void*))(*(char**)a + 0x20))(a);
        int kindB = (*(int(__thiscall**)(void*))(*(char**)b + 0x20))(b);
        if (kindA != 0x18eb45e) {
            if (kindB == 0x18eb45e) {
                void* u = (void*)FUN_00ac80d0(a, (void*)&g_18eb45e, 0, 0, 0, 0, 0, 0, 0, 0, 0);
                FUN_00f30290(b, u);
                return;
            }
            FUN_00f305d0(a, b, p + 0x17, p + 0x11, p + 0xb, (void*)p[0x1d],
                         p + 2, p + 0x14, p + 0xe, p + 8, (void*)p[0x1c]);
            return;
        }
        if (kindB == 0x18eb45e) return;
        void* u = (void*)FUN_00ac80d0(b, (void*)&g_18eb45e, p + 0x14, p + 0xe, p + 8,
                                      (void*)p[0x1c], p + 2, p + 0x17, p + 0x11, p + 0xb, (void*)p[0x1d]);
        FUN_00f30290(a, u);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f31500
float __cdecl Simulator_GetTuningValue(int self, int unused, unsigned idx)
{
    int* vec = (int*)(self + 0x10);
    if (*(int*)(self + 0x10) == *(int*)(self + 0x14)) {
        void* terrain = FUN_00b3d320((void*)&g_1654c10, 0);
        void* t = TerrainMgr_Fn1(terrain);
        if (t) {
            int n = 0, ptr = 0;
            bool ok = SP_GetPropertyAsFloatArray(t, 0xc0b3b39a, &n, &ptr);
            if (ok) {
                SpVectorM_resize(vec, n);
                for (int i = 0; i < n; ++i)
                    ((float*)*vec)[i] = ((float*)ptr)[i];
            }
        }
    }
    if (idx < (unsigned)((vec[1] - *vec) >> 2))
        return ((float*)*vec)[idx];
    return 1.0f;
}

// ---------------------------------------------------------------------------
// @ 0x00f315a0
void __cdecl Simulator_PlaceEffect(float* pos, float radius, int a, int b)
{
    void* nm = SP_NounManager();
    void* vec = cGameNounManager_GetGameDataVector(nm, (void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                   (void*)FUN_00ace0f0, (void*)FUN_00b1e500,
                                                   (void*)&g_18eb45e);
    unsigned* end = *(unsigned**)((char*)vec + 8);
    for (unsigned* it = *(unsigned**)((char*)vec + 4); it != end; ++it) {
        void* o = (void*)*it;
        if ((*(char(__thiscall**)(void*))(*(char**)o + 0x2c))(o)) continue;
        if (Resource_GetFileCount((void*)((char*)o + 0x5a8)) == 2) continue;
        void* q = (void*)((char*)o + 0xc0);
        float* op = (float*)(*(void*(__thiscall**)(void*))(*(char**)q + 0x2c))(q);
        float dx = op[0] - pos[0], dy = op[1] - pos[1], dz = op[2] - pos[2];
        float dist = SqrtFF(dx * dx + dy * dy + dz * dz);
        if (!(dist < FUN_00c03250(q) + radius)) continue;
        int sel = a;
        if (b != -1 &&
            (*(int(__thiscall**)(void*))(*(char**)o + 0x4c))(o) != b) {
            if (a == 0) sel = 1;
            else if (a == 1) sel = 0;
        }
        void* r = FUN_00bc97f0(0, 0x80000, *(int*)&g_13eb8a0, 0);
        *(float*)((char*)r + 0xc) = pos[0];
        *(float*)((char*)r + 0x10) = pos[1];
        *(float*)((char*)r + 0x14) = pos[2];
        *(int*)((char*)r + 0x18) = sel;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f316d0
void __cdecl DebugDraw3DTerraformBullseye(float scale)
{
    void* lu = FUN_01021260();
    float lava = FUN_00c70a20(lu);
    void* tt = FUN_01049a10();
    if (!(cTerraformTuning_GetLavaThreshold(tt) < lava)) return;

    void* pm = SP_PlanetModel();
    float water = cPlanetModel_GetWaterHeight(pm);
    void* nm = SP_NounManager();
    void* vec = cGameNounManager_GetGameDataVector(nm, (void*)FUN_00cd7d10, (void*)FUN_00d3d420,
                                                   (void*)FUN_00ace0f0, (void*)FUN_00b1e500,
                                                   (void*)&g_18eb45e);
    unsigned* end = *(unsigned**)((char*)vec + 8);
    for (unsigned* it = *(unsigned**)((char*)vec + 4); it != end; ++it) {
        void* o = (void*)*it;
        if ((*(char(__thiscall**)(void*))(*(char**)o + 0x2c))(o)) continue;
        void* res = (void*)((char*)o + 0x5a8);
        if (Resource_GetFileCount(res) == 2) continue;
        void* q = (void*)((char*)o + 0xc0);
        if (!FUN_00b7e3e0(pm, (void*)(*(void*(__thiscall**)(void*))(*(char**)q + 0x2c))(q))) continue;
        float* op = (float*)(*(void*(__thiscall**)(void*))(*(char**)q + 0x2c))(q);
        float len = SqrtFF(op[0] * op[0] + op[1] * op[1] + op[2] * op[2]) - water;
        if (!(*(float*)&g_15b0124 < len)) continue;
        void* base = *(char**)res;
        float f = (*(float(__thiscall**)(void*, int, int, void*, int))(*(char**)q + 0x58))(q, -1, 0x12, &g_16c848c, 0);
        (*(void(__thiscall**)(void*, float))(*(char**)q + 0x18))(q, (f * scale) * *(float*)&g_1471064);
        (void)base;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f31810
void __cdecl TerraformUpdate(unsigned lo, unsigned hi)
{
    unsigned __int64 bits = ((unsigned __int64)hi << 32) | lo;
    float f = (float)((double)bits * *(float*)&g_13f9428);
    DebugDraw3DTerraformBullseye(f);
    ++g_16c8480;
    if (g_16c8480 > 1 && g_16c84dc != g_16c84e0) {
        do {
            int e = g_16c84e0;
            FUN_00f23d20((void*)*(int*)(e - 0x84), (void*)*(int*)(e - 0x80), (void*)(e - 0x7c));
            g_16c84e0 = e - 0x84;
            Release(*(char**)(e - 0x80));
            Release(*(char**)(e - 0x84));
        } while (g_16c84dc != g_16c84e0);
    }
}
