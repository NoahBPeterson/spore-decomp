// Slice s00ebfad0 — 0x00ebfad0 .. 0x00ec0970.
//
// Creature-AI "decider" predicates for the Simulator behaviour trees: animation
// deciders on cSPCreatureBase, combatant targeting, creature-info string table
// lookups, and the UI-layout teardown pair.  All are plain x86 cdecl with stack
// arguments (a few take the object in ECX because they call through a vtable).
//
// Several "deciders" are invoked from one generic dispatcher with a fixed
// argument frame, so they read parameters well past their apparent arity
// (e.g. 0x00ebff10 reads [esp+0x1c], 0x00ebff50 reads [esp+0x18]/[esp+0x20]).
// Those extra slots are modelled as explicit trailing parameters.
//
// Compile with /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (module is VS2008 SP1).

typedef unsigned int   uint32;
typedef unsigned char  uint8;
typedef unsigned short uint16;

// ---------------------------------------------------------------------------
// Externals (original addresses in comments).
//
// Entries whose object pointer arrives in ECX are __thiscall members of a
// wrapper API struct.  MSVC 2008 refuses __thiscall on free functions, so they
// are declared as members and invoked through a cast of the raw object pointer.
// ---------------------------------------------------------------------------
struct ExtApi {
    int  __thiscall i0();                          // 0x00c04750
    int  __thiscall i1();                          // 0x00c04790
    int  __thiscall i2();                          // 0x00c047d0
    char __thiscall c0();                          // 0x00c0c0e0 Flag388
    char __thiscall c1(int v);                     // 0x00c0e070
    char* __thiscall i3();                         // 0x00c0e370
    char __thiscall c2(int v);                     // 0x00c0e0c0
    int  __thiscall i4();                          // 0x00c0f780
    int  __thiscall i5();                          // 0x00c7d070 vector accessor
    int  __thiscall i6();                          // 0x00c7d080
    int  __thiscall i7(int a, int b);              // 0x00bc96a0 PlayIdleAnimation
    int  __thiscall i8(int a, int b, float c, int d); // 0x00bc97f0
    int  __thiscall i9(int a, int b);              // 0x00bc98f0 ClearAll
    int  __thiscall iA();                          // 0x00e31100 GetPriority
    char __thiscall iB();                          // 0x00c42e20 IsNearGoal
    int  __thiscall iC();                          // 0x00c2e4e0 SetSerializer
    void __thiscall v0(unsigned v);                // 0x00811ad0 Shutdown
    char __thiscall c3(char v);                    // 0x00810590 SetVisibility
    void __thiscall v1(int noun);                  // 0x00b225d0 RemoveNoun
    int  __thiscall iD();                          // 0x00b1fdb0 GetAvatar
    int  __thiscall iE();                          // 0x00b18530 cGameData
    int  __thiscall iF(int src, float a, float b); // 0x00f30cc0
    int  __thiscall iG();                          // 0x00f30bc0 SimSingleton ctor
    void __thiscall v2();                          // 0x00d997e0 stimuli GetAny
    int  __thiscall iH();                          // 0x00c04590
    int  __thiscall iI(int* key);                  // 0x00b72230 hash step
    void __thiscall v3();                          // 0x00b720e0 hash close
    int  __thiscall rnd(int n);                    // 0x00a68fb0 RandomUint32Uniform
};
// The three cSPCreatureBase animation entry points.
struct CSPCreatureBase {
    int  __thiscall PlayAnim(int a, int b, int c);       // 0x00c12190
    int  __thiscall InterruptAnim(int a, int b, int c);  // 0x00c12310
    char __thiscall AnimFinished(int a);                 // 0x00c12400
};
#define EXT(p)      (*(ExtApi*)(p))
#define CREATURE(p) (*(CSPCreatureBase*)(p))

extern "C" void  FUN_00f47380(void* p);               // operator delete
extern "C" void* FUN_00f473a0(int n, const char* tag, int a, int b, const char* f, int d);
extern "C" int   FUN_00a68fb0(int o, int n);          // RandomUint32Uniform
struct VecBool;                                        // eastl vector<bool> (3 ptrs)
extern "C" int   FUN_011e0744(void* a, void* b, int c); // eastl DoInsertValue
extern "C" int   FUN_00b3d300(void);                  // SP::NounManager
extern "C" int   FUN_00d99a10(int o);                 // 0x00d99a10
extern "C" int   FUN_00d998f0(int o);                 // 0x00d998f0
extern "C" int   FUN_00f5f5b0(int o, int a, void* b);  // eastl vector copy
extern "C" void  FUN_00f5ee00(void* p);                // eastl free

static int g_pSimSingleton;                            // 0x0168d824
static int g_SimSingletonCtor(int p) { return EXT(p).iG(); }

// Real .rdata / .data constants (addresses in comments).
static float* const g_pZero   = (float*)0x01485378;
static float* const g_p3      = (float*)0x013eb95c;
static float* const g_pBig    = (float*)0x01488900;
static float* const g_pDist2  = (float*)0x01486110;
static float* const g_p8      = (float*)0x013eeda0;
static float* const g_pDist1  = (float*)0x014853bc;
static float* const g_pSmall  = (float*)0x013eecd8;

// The shared decider state block used by several animation deciders.
struct DeciderState {
    int    tag;      // +0x00
    int    pad04;    // +0x04
    int    pad08;    // +0x08
    char   active;   // +0x0c
    char   pad0d[3];
    int    stage;    // +0x10  (1 == "start" stage)
    int    anim;     // +0x14
};

// Two-slot variant used by the "play tag / wait for finish" deciders.
struct AnimState {
    int tag;   // +0x00
    int anim;  // +0x04
};

// ---------------------------------------------------------------------------
// 0x00ebfad0 — two-phase teardown of every cSPUILayout in the UI hash at
// 0x016c744c.  The first pass flushes each layout's element vector through the
// eastl vector<bool> insert helper, the second runs FUN_00ebf480 over it.
// ---------------------------------------------------------------------------
struct LayoutElem {
    char pad00[0x14];
    int  beg;   // +0x14
    int  end;   // +0x18
    char pad1c[0x0c];
    int  sub;   // +0x28 cSPUILayout*
};

// The three-pointer eastl::vector<bool> layout; 0x00ebf480 swaps two of them.
struct VecBool {
    int b, e, c;
    void __thiscall swap(VecBool* other);   // 0x00ebf480
};

// @ 0x00ebfad0
void FUN_00ebfad0(void)
{
    int h = *(int*)0x016c744c;
    int key;
    int e;

    key = EXT(h).iA();
    e   = EXT(h).iI(&key);
    while (e != 0) {
        LayoutElem* L = (LayoutElem*)e;
        VecBool* v = (VecBool*)((char*)L + 0x14);
        int n = (v->e - v->b) >> 2;
        if (n > 0) {
            FUN_011e0744((void*)v->b, (void*)v->e, 0);
            v->e += ((v->e - v->b) >> 2) * -4;
        }
        {
            VecBool tmp;
            int m = (v->e - v->b) >> 2;
            tmp.c = 0;
            if (m == 0) {
                tmp.b = 0;
            } else {
                tmp.b = (int)FUN_00f473a0(m * 4, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                    0xd1);
            }
            tmp.c = tmp.b + m * 4;
            tmp.e = FUN_011e0744((void*)tmp.b, (void*)v->b, v->e - v->b) + m * 4;
            v->swap(&tmp);
            if (tmp.b != 0 && *(int*)(tmp.b - 4) != 0)
                FUN_00f47380((void*)tmp.b);
        }
        EXT(L->sub).v0(1);
        {
            int c = L->sub;
            if (c != 0) {
                L->sub = 0;
                (*(void (__thiscall**)(int))((*(int*)c) + 8))(c);
            }
        }
        e = EXT(h).iI(&key);
    }
    EXT(h).v3();
    if (h != 0) {
        EXT(h).iC();
        FUN_00f47380((void*)h);
    }
}

// @ 0x00ebfc20
void FUN_00ebfc20(void)
{
    int h = *(int*)0x016c744c;
    int key;
    int e;

    key = EXT(h).iA();
    e   = EXT(h).iI(&key);
    while (e != 0) {
        LayoutElem* L = (LayoutElem*)e;
        VecBool* v = (VecBool*)((char*)L + 0x14);
        EXT(L->sub).c3(0);
        FUN_011e0744((void*)v->b, (void*)v->e, 0);
        v->e += ((v->e - v->b) >> 2) * -4;
        if (((v->e - v->b) >> 2) > 0) {
            FUN_011e0744((void*)v->b, (void*)v->e, 0);
            v->e += ((v->e - v->b) >> 2) * -4;
        }
        {
            VecBool tmp;
            int m = (v->e - v->b) >> 2;
            tmp.c = 0;
            if (m == 0) {
                tmp.b = 0;
            } else {
                tmp.b = (int)FUN_00f473a0(m * 4, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                    0xd1);
            }
            tmp.c = tmp.b + m * 4;
            tmp.e = FUN_011e0744((void*)tmp.b, (void*)v->b, v->e - v->b) + m * 4;
            v->swap(&tmp);
            if (tmp.b != 0 && *(int*)(tmp.b - 4) != 0)
                FUN_00f47380((void*)tmp.b);
        }
        e = EXT(h).iI(&key);
    }
}

// @ 0x00ebfd50 — map a creature-info string id to its locale-specific replacement.
int FUN_00ebfd50(int obj, int def)
{
    int sel;
    int idx;
    int* p;

    if (EXT(obj).c0() != 0) {
        sel = 2;
    } else if ((*(uint32*)(*(int*)(obj + 0xb4c) + 0x5fc) >> 9 & 1) == 0) {
        return def;
    } else {
        sel = 1;
    }

    idx = 0;
    p   = (int*)0x1488908;
    for (;;) {
        if (*p == def) {
            int v = *(int*)(0x1488908 + (idx * 3 + sel) * 4);
            if (v != 0)
                def = v;
            return def;
        }
        p   += 3;
        idx += 1;
        if ((int)p >= 0x1488f44)
            return def;
    }
}

// @ 0x00ebfdc0
int FUN_00ebfdc0(int obj)
{
    switch (EXT(obj).i2()) {
    case 1:  return 0x7c7c136;
    case 2:  return 0x7c7bb42;
    case 3:  return 0x7c7bb42;
    case 4:  return 0x7c7b779;
    case 5:  return 0x7c7b779;
    default: return 0x7c7bb42;
    }
}

// @ 0x00ebfe00
float FUN_00ebfe00(int obj, int a, int b, uint32 flags)
{
    if (EXT(obj).i1() == 1) {
        if ((flags & 0x50000000u) != 0)
            return 1.0f;
    } else {
        int avatar = EXT(FUN_00b3d300()).iD();
        int x = (*(int (__thiscall**)(int))((*(int*)obj) + 0x4c))(obj);
        int y = (*(int (__thiscall**)(int))((*(int*)avatar) + 0x4c))(avatar);
        if (x == y && (flags & 0x80000000u) == 0)
            return 1.0f;
    }
    return 0.0f;
}

// @ 0x00ebfe60
float FUN_00ebfe60(int o)
{
    if (*(float*)(o + 0x1660) > *g_pZero &&
        *(int*)(o + 0x1664) != 5 &&
        *(char*)(o + 0x166c) != 0)
        return 1.0f;
    else
        return 0.0f;
}

// @ 0x00ebfe90
float FUN_00ebfe90(int o)
{
    if (*(float*)(o + 0x1660) > *g_pZero &&
        *(int*)(o + 0x1664) != 5 &&
        *(char*)(o + 0x166c) == 0)
        return 1.0f;
    else
        return 0.0f;
}

// @ 0x00ebfec0
int FUN_00ebfec0(int o)
{
    if (EXT(o).c0() != 0)
        return *(int*)(0x1488f44 + *(int*)(o + 0x1668) * 12);
    {
        int v = (*(int (__thiscall**)(int))((*(int*)o) + 0xd8))(o);
        return *(int*)(0x1488f44 + *(int*)(o + 0x1668) * 12 + (v != 0) * 4 + 4);
    }
}

// @ 0x00ebff10
char FUN_00ebff10(int obj, int a, int b, int c, int d, void* out)
{
    if (out != 0)
        *(int*)out = 5;
    {
        int anim = FUN_00ebfec0(obj);
        *(int*)out = *(int*)(obj + 0x1664);
        CREATURE(obj).PlayAnim(anim, 1, -1);
    }
    return 1;
}

// @ 0x00ebff50
char FUN_00ebff50(int obj, int a, int b, int c, int d, int* p, int e, float dt)
{
    float v = *(float*)(obj + 0x1660) - dt;
    *(float*)(obj + 0x1660) = v;
    if (v > 0.0f)
        return *(int*)(obj + 0x1664) == *p;
    else
        return 0;
}

// @ 0x00ebff90
char FUN_00ebff90(int o)
{
    return EXT(*(int*)(o + 0xb4c) + 8).i7(0, 0x40000) != 0;
}

// @ 0x00ebffb0
float FUN_00ebffb0(int o)
{
    if (*(int*)(EXT(o).i0() + 0x4b8) == 3)
        return 1.0f;
    return 0.0f;
}

// @ 0x00ebffd0
char FUN_00ebffd0(int obj)
{
    (*(void (__thiscall**)(int))((*(int*)(obj + 0xc0)) + 0xec))(obj + 0xc0);
    EXT(*(int*)(obj + 0xb4c) + 8).i9(0x8000000, 0);
    return 1;
}

// @ 0x00ec0010
char FUN_00ec0010(int obj, int a, int b, int c, int d, DeciderState* st)
{
    if (st->active != 0) {
        char flag;
        if (EXT(obj).i0() != 0 &&
            *(char*)(EXT(obj).i0() + 0x4c8) == 0 &&
            *(int*)(EXT(obj).i0() + 0x4b8) == 1)
            flag = 1;
        else
            flag = 0;

        if (EXT(obj + 0xc0).iB() != 0 || flag) {
            int v = st->stage - 1;
            st->active = 0;
            if (flag)
                v = (v != 0 ? 0x3baadcbu : 0u) + 0x40e01e0;
            else
                v = (v != 0 ? 0xfffffe6au : 0u) + 0x7c8b141;
            st->anim = CREATURE(obj).InterruptAnim( v, -1, 0);
        }
        return 1;
    }
    return (char)(CREATURE(obj).AnimFinished(st->anim) == 0);
}

// @ 0x00ec00e0
char FUN_00ec00e0(int noun, int a, int b, int c, int d, float* acc, int e, float dt)
{
    if ((*acc += dt) > *g_p3)
        EXT(FUN_00b3d300()).v1(noun);
    return 1;
}

// @ 0x00ec0110
int FUN_00ec0110(int o)
{
    int v = EXT(*(int*)(o + 0xb4c) + 8).i7(0x400, 0);
    if (v != 0 && *(int*)(v + 0xc) != 3) {
        int w = FUN_00d99a10(v);
        v = FUN_00d998f0(w);
        if (v != 0)
            return v;
        EXT(*(int*)(o + 0xb4c) + 8).i9(0x400, 0);
    }
    return 0;
}

// @ 0x00ec0160
char FUN_00ec0160(int obj, int a, int b, int c, int d, AnimState* st)
{
    if (EXT(obj + 0xc0).iB() != 0) {
        if (st->anim == 0) {
            st->anim = CREATURE(obj).InterruptAnim( st->tag, -1, 0);
        } else {
            if (EXT(obj).c1(st->anim) != 0 && (int)EXT(obj).i3() <= 0)
                return 1;
            return 0;
        }
    }
    return 1;
}

// @ 0x00ec01b0
char FUN_00ec01b0(int obj, int a, int b, int c, int d, AnimState* st)
{
    int tag;

    if (st != 0) {
        st->tag  = 0;
        st->anim = 0;
    }
    if (*(int*)(obj + 0x698) != 3)
        tag = 0x7ccb8cc;
    else
        tag = *(int*)(0x1488f74 + *(int*)(obj + 0x69c) * 4);
    st->tag = tag;

    (*(void (__thiscall**)(int))((*(int*)(obj + 0xc0)) + 0xec))(obj + 0xc0);
    st->anim = CREATURE(obj).InterruptAnim( st->tag, -1, 0);
    return 1;
}

// @ 0x00ec0220
char FUN_00ec0220(int obj, int a, int b, int c, int d, int* st)
{
    if (CREATURE(obj).AnimFinished(st[1]) != 0)
        st[1] = CREATURE(obj).PlayAnim(st[0], 1, -1);
    return 1;
}

// @ 0x00ec0270 — |b.pos - a.pos| minus the two objects' radii.
float FUN_00ec0270(int* a, int* b)
{
    float* pa = (float*)(*(int (__thiscall**)(int*))((*a) + 0x2c))(a);
    float* pb = (float*)(*(int (__thiscall**)(int*))((*b) + 0x2c))(b);
    float ra  = (*(float (__thiscall**)(int*))((*a) + 0x74))(a);
    float rb  = (*(float (__thiscall**)(int*))((*b) + 0x74))(b);
    float dx = pb[0] - pa[0];
    float dy = pb[1] - pa[1];
    float dz = pb[2] - pa[2];
    float d  = dx * dx + dy * dy + dz * dz;
    float r;

    __asm {
        fld     d
        fsqrt
        fsub    ra
        fsub    rb
        fstp    r
    }
    return r;
}

// @ 0x00ec02e0
void FUN_00ec02e0(int obj)
{
    if ((*(uint8*)(obj + 0x330) & 1) == 0)
        return;
    {
        char found = 0;
        int* p;
        for (p = (int*)0x1488f98; (int)p < 0x1488fa4; p++) {
            if (EXT(obj).c2(*p) != 0)
                found = 1;
        }
        if (found == 0) {
            int n = EXT(0x1601760).rnd(3);
            CREATURE(obj).InterruptAnim(*(int*)(0x1488f98 + n * 4), -1, 0);
        }
    }
}

// @ 0x00ec0340
int FUN_00ec0340(int* obj)
{
    int v;
    if (obj == 0)
        return 0;
    v = (*(int (__thiscall**)(int*, int))((*obj) + 0xc))(obj, 0xd0036e08);
    if (v != 0)
        return (*(uint32*)(*(int*)(v + 0xb4c) + 0x1cc) & 0x40000) != 0;
    v = (*(int (__thiscall**)(int*, int))((*obj) + 0xc))(obj, 0x137e8e0);
    if (v == 0)
        return 0;
    return (*(uint32*)(*(int*)(v + 0xaf0) + 0x1c8) & 0x8000) != 0;
}

// @ 0x00ec03c0 — first entry of the object-vector at obj+0x670 whose payload
// exposes a 0x17f243b interface reporting one of two type tags.
int FUN_00ec03c0(int obj)
{
    int base = obj + 0x670;
    int beg;
    int end;
    int p;

    beg = *(int*)EXT(base).i6();
    end = *(int*)(EXT(base).i6() + 4);
    if (beg != end) {
        do {
            int e = *(int*)beg;
            if (e != 0) {
                int s = (*(int (__thiscall**)(int, int))((*(int*)e) + 0xb8))(e, 0x17f243b);
                if (s != 0) {
                    int t = (*(int (__thiscall**)(int))((*(int*)s) + 0x20))(s);
                    if (t == 0x18c6de8 || t == 0x18eb45e)
                        return e;
                }
            }
            beg += 4;
        } while (beg != end);
    }
    return 0;
}

// @ 0x00ec0430 — pick an eligible victim for the "creature is tame / being
// tamed" decider and arm the approach action against it.
float FUN_00ec0430(int obj, int a, int b, int d)
{
    int* v;
    int* vec;
    int  n, i;

    v = (int*)EXT(obj).i0();
    if (*(int*)((char*)v + 0x4b0) != 2 && *(int*)((char*)v + 0x4b0) != 3)
        return 0.0f;
    if (EXT(obj).i4() > -1)
        return 0.0f;

    vec = (int*)EXT(obj + 0x670).i5();
    n   = (vec[1] - vec[0]) >> 2;
    if (n <= 0)
        return 0.0f;

    for (i = 0; i < n; i++) {
        int* s = *(int**)(vec[0] + i * 4);
        if (s != 0) {
            s = (int*)(*(int (__thiscall**)(int*, int))((*s) + 0xb8))(s, 0x17f243b);
            if (s != 0) {
                if ((*(int (__thiscall**)(int*))((*s) + 0x20))(s) == 0x3a2511e) {
                    int* f = (int*)(*(int (__thiscall**)(int*, int))((*s) + 0xc))(s, 0x1186577);
                    if ((f[0x14] & 0x100) == 0) {
                        if (*(int*)((char*)v + 0x4b0) != 3 || v[0x12f] == s[7]) {
                            int* r = (int*)EXT(*(int*)(obj + 0xb4c) + 8).i8(0, 0x40000, *g_pDist2, (int)s);
                            if (r != 0) {
                                r[3] = 4;
                                return 1.0f;
                            }
                        }
                    }
                }
            }
        }
    }
    return 0.0f;
}

extern "C" int FUN_008e7f80(int o);            // 0x008e7f80 GetFileCount

// @ 0x00ec0530 — nearest eligible combatant, arms the multistage attraction
// action (state 6) against it.
float FUN_00ec0530(int obj, int a, int b, int d)
{
    int*  v;
    int   beg, end;
    int   pick;
    float best;
    int   self;
    float* ps;

    v = (int*)EXT(obj).i0();
    if (*(int*)((char*)v + 0x4b4) != 2 && *(int*)((char*)v + 0x4b4) != 3)
        return 0.0f;
    if (EXT(obj).i4() == -1)
        return 0.0f;

    self = *(int*)(obj + 0x1c);
    best = *g_pBig;
    pick = 0;
    beg  = *(int*)EXT(obj + 0x670).i5();
    end  = *(int*)(EXT(obj + 0x670).i5() + 4);
    ps   = (float*)(*(int (__thiscall**)(int))((*(int*)(obj + 0xc0)) + 0x2c))(obj + 0xc0);
    if (beg == end)
        return 0.0f;
    do {
        int* e = *(int**)beg;
        if (e != 0) {
            int* s = (int*)(*(int (__thiscall**)(int*, int))((*e) + 0xb8))(e, 0x17f243b);
            if (s != 0) {
                int a1 = (*(int (__thiscall**)(int*, int))((*s) + 0xc))(s, 0xce9f6639);
                int a2 = (*(int (__thiscall**)(int*, int))((*s) + 0xc))(s, 0x70704db);
                int a3 = (*(int (__thiscall**)(int*, int))((*s) + 0xc))(s, 0x137e8e0);
                if ((a1 != 0 || a2 != 0 || a3 != 0) &&
                    s[7] != self &&
                    (*(int*)((char*)v + 0x4b4) != 3 ||
                     *(int*)((char*)v + 0x4c0) == s[7])) {
                    int cs = (*(int (__thiscall**)(int*, int))((*s) + 0xc))(s, 0x13f94d4);
                    if (cs == 0 || FUN_008e7f80(cs) != 2) {
                        int* f = (int*)(*(int (__thiscall**)(int*, int))((*s) + 0xc))(s, 0x1186577);
                        float* pf = (float*)(*(int (__thiscall**)(int*))((*f) + 0x2c))(f);
                        float dx = ps[0] - pf[0];
                        float dy = ps[1] - pf[1];
                        float dz = ps[2] - pf[2];
                        float ds = dx * dx + dy * dy + dz * dz;
                        if (ds < best) {
                            best = ds;
                            pick = (int)s;
                        }
                    }
                }
            }
        }
        beg += 4;
    } while (beg != end);

    if (pick != 0) {
        int t = EXT(obj).i4();
        int r = EXT(*(int*)(obj + 0xb4c) + 8).i8(0, 0x40000, *g_pBig, pick);
        if (r != 0) {
            *(int*)(r + 0x14) = pick;
            *(int*)(r + 0x10) = t;
            *(int*)(r + 0xc)  = 6;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00ec0740
float FUN_00ec0740(int obj)
{
    int v = EXT(*(int*)(obj + 0xb4c) + 8).i7(0, 0x40000);
    int* self = (int*)(obj + 0xc0);
    if (v != 0 && *(int*)(v + 0x14) != 0) {
        int p = *(int*)(v + 0x14);
        int o = (*(int (__thiscall**)(int, int))((*(int*)p) + 0xc))(p, 0x1186577);
        if (o != 0) {
            float d = FUN_00ec0270((int*)o, self);
            if (d > *g_p8)
                return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00ec07a0
float FUN_00ec07a0(int obj)
{
    int v = EXT(*(int*)(obj + 0xb4c) + 8).i7(0, 0x40000);
    if (v != 0) {
        int p    = *(int*)(v + 0x14);
        int keep = *(int*)(v + 0x10);
        if (p != 0) {
            int o = (*(int (__thiscall**)(int, int))((*(int*)p) + 0xc))(p, 0xce9f6639);
            if (o != 0) {
                int r = EXT(*(int*)(o + 0xb4c) + 8).i8(0, 0x40000, *g_pDist1, obj);
                if (r != 0) {
                    *(int*)(r + 0x10) = keep;
                    *(int*)(r + 0xc)  = 7;
                    return 1.0f;
                }
            }
        }
    }
    return 0.0f;
}

// @ 0x00ec0820
float FUN_00ec0820(int obj)
{
    int v = EXT(*(int*)(obj + 0xb4c) + 8).i7(0, 0x40000);
    if (v != 0) {
        int p    = *(int*)(v + 0x14);
        int keep = *(int*)(v + 0x10);
        if (p != 0) {
            int a = (*(int (__thiscall**)(int, int))((*(int*)p) + 0xc))(p, 0x137e8e0);
            int b = (*(int (__thiscall**)(int, int))((*(int*)p) + 0xc))(p, 0xe9cb8ba);
            if (a != 0) {
                EXT(*(int*)(a + 0xaf0) + 8).i8(0x8000, 0, *g_pSmall, 0);
                {
                    int r = EXT(*(int*)(a + 0xaf0) + 8).i8(0x8000, 0, *g_pBig, obj);
                    if (r != 0) {
                        *(int*)(r + 0x10) = keep;
                        return 1.0f;
                    }
                }
            } else if (b != 0) {
                return 1.0f;
            }
        }
    }
    return 0.0f;
}

// Lazy SimSingleton accessor used by 0x00ec08d0 and 0x00ec0970 (inlined in both).
static int sim_singleton(void)
{
    if (g_pSimSingleton == 0) {
        int p = (int)FUN_00f473a0(0x24, "Simulator/SimSingleton", 0, 0, 0, 0);
        g_pSimSingleton = (p != 0) ? g_SimSingletonCtor(p) : 0;
    }
    return g_pSimSingleton;
}

// @ 0x00ec08d0 — behave as an "inspect object" decider: creates the stimulus
// and reports whether one was produced.
float FUN_00ec08d0(int obj, int a, int b, int d, int stim, char* out)
{
    if (EXT(obj).i2() != 5 && EXT(obj).i2() != 4)
        return 0.0f;
    {
        int  src  = (obj == 0) ? 0 : obj + 0x5a8;
        int  sim  = sim_singleton();
        int  r;
        (void)a; (void)b; (void)d;
        r = EXT(sim).iF(src, 0.0f, 0.0f);
        if (r != 0) {
            if (stim != 0)
                EXT(stim).v2();
            *out = 1;
            *(int*)(stim + 4) = r;
            return 1.0f;
        }
    }
    return 0.0f;
}

// @ 0x00ec0970
float FUN_00ec0970(int obj, int a, int b, int d, int stim, char* out)
{
    int sim;
    int r;
    if (EXT(obj).i2() != 4)
        return 0.0f;
    (*(void (__thiscall**)(int))((*(int*)obj) + 0x4c))(obj);
    sim = sim_singleton();
    r   = EXT(sim).iF(obj + 0x5a8, 0.0f, 0.0f);
    if (r == 0)
        return 0.0f;
    if (stim != 0)
        EXT(stim).v2();
    *out = 1;
    {
        int t   = EXT(obj).iH();
        int sel = (obj == *(int*)(t + 0x164) &&
                   *(int*)(EXT(obj).iH() + 0x168) != EXT(obj).iH() + 0x168) ? 1 : 0;
        *(int*)(stim + 4)  = r;
        *(int*)(stim + 0x18) = sel;
        *(int*)(stim + 8)  = 0;
        *(int*)(stim + 0)  = 0;
    }
    (void)a; (void)b; (void)d;
    return 1.0f;
}
