// Slice s00b5cfe0 (batch bfs1) — 18 functions.
// Module "Spore"; SP::cGonzagoMode and Gonzago UI helpers.  Each block starts with
// its original address.

#include "s00b5cfe0.h"

extern "C" void* operator_new_ea(unsigned, const char*, int, int, int, int);
extern "C" int   atexit(void (*)(void));
extern "C" void  FUN_013c29f0(void);
extern "C" void  FUN_0060c4a0(void*);       // eastl list DoClear
extern "C" void  DoClear_571db0(void*, void*, void*, void*, void*);
extern "C" void  operator_delete_00f47380(void*);
extern "C" void  RemoveHandler_571db0(void*, void*, void*, void*, void*);
extern "C" void  FUN_00ae6970(void*);

extern unsigned g_168710c;
extern int g_16870fc, g_1687100, g_1687104;
extern char g_1667bac;
extern char g_vt0dummy, g_vt1dummy, g_vt2dummy, g_vt3dummy;

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }

// @ 0x00b5d3f0
void FUN_00b5d3f0(int* param)
{
    void* p = operator_new_ea(4, "App", 0, 0, 0, 0);
    if (p) *(void**)p = &g_vt2dummy;
    else p = 0;
    ((void(__thiscall*)(void*, void*, void*, const char*))g_vfn(param, 0x20))
        (param, p, (void*)0x1654c08, "LoadGame");
}

// @ 0x00b5d760
void __stdcall FUN_00b5d760(int)
{
    if ((g_168710c & 1) == 0)
    {
        g_168710c |= 1;
        g_16870fc = (int)&g_1667bac;
        g_1687100 = (int)&g_1667bac;
        g_1687104 = 0x1667bad;
        atexit(FUN_013c29f0);
    }
}

// @ 0x00b5d7a0
void __stdcall FUN_00b5d7a0(int* p)
{
    p[0] = 0x412402d0;
    p[1] = 0x2f7d0004;
    p[2] = 0xca14de92;
}

// ---------------------------------------------------------------------------
// SP::cGonzagoMode
// ---------------------------------------------------------------------------

// @ 0x00b5d510
bool cGonzagoMode::FUN_00b5d510(int param)
{
    char* head = (char*)this + 0x20;
    char* n = *(char**)head;
    while (n != head)
    {
        if (*(int*)(n + 8) == param) return true;
        n = *(char**)n;
    }
    return false;
}

// @ 0x00b5d7c0 (destructor)
cGonzagoMode::~cGonzagoMode()
{
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    // eastl::vector<AutoRefCount<cStarRecord>> dtor at +0x5c
    // (approximated: the vector release is not reconstructed here)
    FUN_00ae6970((char*)this + 0x5c);
    if (*(int*)((char*)this + 0x48))
    {
        *(int*)((char*)this + 0x48) = 0;
        RemoveHandler_571db0((char*)this + 0x48, (char*)this + 0x4c,
                             (char*)this + 0x50, (char*)this + 0x54, (char*)this + 0x58);
    }
    if (*(int*)((char*)this + 0x34))
    {
        *(int*)((char*)this + 0x34) = 0;
        RemoveHandler_571db0((char*)this + 0x34, (char*)this + 0x38,
                             (char*)this + 0x3c, (char*)this + 0x40, (char*)this + 0x44);
    }
    FUN_0060c4a0((char*)this + 0x20);
    if (*(void**)((char*)this + 0x1c))
        ((void(__thiscall*)(void*))g_vfn(*(void**)((char*)this + 0x1c), 0xc))(*(void**)((char*)this + 0x1c));
    if (*(void**)((char*)this + 0x18))
        ((void(__thiscall*)(void*))g_vfn(*(void**)((char*)this + 0x18), 8))(*(void**)((char*)this + 0x18));
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
}

// @ 0x00b5db40
bool cGonzagoMode::FUN_00b5db40(int param)
{
    char* head = (char*)this + 0x20;
    char* n = *(char**)head;
    while (n != head)
    {
        if (*(int*)(n + 8) == param)
        {
            char* prev = *(char**)(n + 0);
            char* next = *(char**)(n + 4);
            *(char**)next = prev;
            *(char**)(prev + 4) = next;
            void* data = *(void**)(n + 8);
            if (data)
                ((void(__thiscall*)(void*))g_vfn(data, 8))(data);
            operator_delete_00f47380(n);
            return true;
        }
        n = *(char**)n;
    }
    return false;
}

// @ 0x00b5db90
void cGonzagoMode::FUN_00b5db90()
{
    char* l = (char*)this + 0x20;
    ((void(__thiscall*)(void*))FUN_0060c4a0)(l);
    *(void**)l = l;
    *(void**)(l + 4) = l;
}

// @ 0x00b5df90 (constructor)
cGonzagoMode::cGonzagoMode()
{
    vt4 = (void**)&g_vt1dummy;
    m08 = 0;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    b0c = b0d = b0e = 0;
    f10 = 0.0f;
    f14 = 0.0f;
    m18 = 0;
    m1c = 0;
    void** l = &listHead;
    listHead = l;
    listTail = l;
    b2c = 0;
    m30 = m34 = m38 = m3c = m40 = m44 = m48 = m4c = 0;
    m50 = m54 = m58 = m5c = m60 = m64 = 0;
}

// ---------------------------------------------------------------------------
// Reworked bodies.
//
// Retail callees are named after their address, so the equivalence harness can bind the
// symbol back to the original code.  A thunk-shaped callee is declared __fastcall with a
// spare second slot (a free __thiscall is C3865): cl then passes `this` in ecx and the real
// argument on the stack, with the callee popping it, exactly as the original call sites do.
// ---------------------------------------------------------------------------

struct EastlString8  { char* begin; char* end; char* cap; };
struct EastlString16 { unsigned short* begin; unsigned short* end; unsigned short* cap; };
struct EAVariant     { char raw[0x14]; };

extern "C" void* GameTimeManager_b3d380();
extern "C" void* App_67dd10();
extern "C" void* FUN_67dd50();
extern "C" void* EffectsMgr_67ddd0();
extern "C" void* MessageServer_67dcc0();
extern "C" void* FUN_67cab0();
extern "C" void* Telemetry_67de90();
extern "C" void* PlanetModel_b3d350();
extern "C" void* GetGameTerrainCursor_b30d70();
extern "C" void* FUN_b3d240();
extern "C" void* FUN_b3d320();
extern "C" void* FUN_bc8000();
extern "C" void* cCreatureModeStrategy_d38840();
extern "C" void* cTribeModeStrategy_cd40b0();
extern "C" void* cCivModeStrategy_cf74c0();
extern "C" void* FUN_fd9c60();
extern "C" void* GetEditSelection_d1bf00();
extern "C" void  FUN_b335d0(unsigned, unsigned);
extern "C" void* operator_new_0xf473a0(unsigned, const char*, int, int, const char*, int);
extern "C" void* memcpy_11e0744(void*, const void*, unsigned);
extern "C" int   eastlEq_555020(const char*, const char*);
extern "C" void  FUN_b1f960(int);
extern "C" void  FUN_c2e4e0(int);
extern "C" void* FUN_91ba90(void*, void*, const char*);
extern "C" void* GetSetting9_401090(void);
extern "C" void* ConvertToString8_93c570(void*, void*);
extern "C" int   IsModifierKeyDown_8d2fb0(int);
extern "C" void* g_appProps_15fd918;
extern "C" float g_1686b00, g_1686b04, g_1686b08;

int   __fastcall MainArguments_838020(void*, void*, int*, int, int);
void* __fastcall Args_OptionArguments_838330(void*, void*, const char*, int);
void  __fastcall GameTimeUpdate_b31a90(void*);
unsigned __fastcall GameTimeArg_b31c60(void*, void*, unsigned);
void  __fastcall SetEdgeDistance_b0f930(void*, void*, float*);
void  __fastcall MoveCamera_b148c0(void*, void*, float, float, float, float);
void  __fastcall Minimap_b8c330(void*, void*, int, int, int);
void  __fastcall FUN_bc7ac0(void*, void*, unsigned);
void* __fastcall FUN_b5d1b0(void*, void*, unsigned);
bool  __fastcall Variant_Construct_93dd80(void*, void*, unsigned short, unsigned short,
                                          const void*, unsigned, unsigned);
void  __fastcall Variant_Destruct_93db80(void*, void*, int);
void  __fastcall CmdLine_ctor_92c210(void*, void*, int);
void  __fastcall CmdLine_fini_5d7450(void*);
void  __fastcall cArguments_ctor_8386d0(void*, void*, int);
void  __fastcall cArguments_dtor_837fa0(void*);
int   __fastcall FindSwitch_92b300(void*, void*, const void*, int, void*, int);
void  __fastcall eastlAssign_454cb0(void*, void*, const char*, const char*);
bool  __fastcall GetEditorName_5805e0(void*, void*, void*);
void  __fastcall SetAvatarSpecies_4df310(void*, void*, void*);
void* __fastcall BuildSurfaceOrientation_b7f190(void*);
void  __fastcall FlushTelemetry_7ebce0(void*, void*, unsigned);
bool  __fastcall FindLocal_801bb0(void*, void*, unsigned);
bool  __fastcall Set_8017f0(void*, void*, void*);
void* __fastcall HashtableFind_645ed0(void*, void*, void*, const int*);
void  __fastcall FUN_c15fd0(void*, void*, void*, void*, void*);

// @ 0x00b5cfe0
void cGonzagoMode::FUN_00b5cfe0(unsigned t)
{
    GameTimeUpdate_b31a90(GameTimeManager_b3d380());
    unsigned ticks = GameTimeArg_b31c60(GameTimeManager_b3d380(), 0, t);

    void* p = App_67dd10();
    p = ((void* (__thiscall*)(void*))g_vfn(p, 0x50))(p);
    if (p)
    {
        p = ((void* (__thiscall*)(void*))g_vfn(p, 0x38))(p);
        if (p)
        {
            void* b = ((void* (__thiscall*)(void*, int))g_vfn(p, 0xc))(p, 0x11966ed);
            if (b)
            {
                void* m = FUN_67dd50();
                int* q = (int*)((int* (__thiscall*)(void*))g_vfn(m, 0x1c))(m);
                int w = q[0], h = q[1], x = q[2], y = q[3];
                float ex = 0.0f, ey = 0.0f;
                if (x >= 0 && x < w)
                {
                    if (x > w / 2) x -= w;
                    if (y >= 0 && y < h)
                    {
                        if (y > h / 2) y -= h;
                        ex = (float)x + 0.01f;
                        ey = (float)y + 0.01f;
                    }
                }
                float edge[2];
                edge[0] = ex;
                edge[1] = ey;
                SetEdgeDistance_b0f930(b, 0, edge);

                double dt = (double)(int)t;
                if ((int)t < 0) dt += 4294967296.0;
                MoveCamera_b148c0(b, 0, 0.0f, 0.0f, 0.0f,
                    (float)(dt * 0.001000000047497451305389404296875));
            }
        }
    }

    int n = (*(int*)((char*)this + 0x60) - *(int*)((char*)this + 0x5c)) >> 2;
    for (int i = 0; i < n; ++i)
    {
        void* e = (*(void***)((char*)this + 0x5c))[i];
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(e, 0x38))(e, t, ticks);
    }
}

// @ 0x00b5d130
void cGonzagoMode::FUN_00b5d130(unsigned t)
{
    unsigned ticks = GameTimeArg_b31c60(GameTimeManager_b3d380(), 0, t);
    ((void (__thiscall*)(void*, unsigned))g_vfn(this, 0x34))(this, t);
    Minimap_b8c330(PlanetModel_b3d350(), 0, t, 0, 0);

    int n = (*(int*)((char*)this + 0x60) - *(int*)((char*)this + 0x5c)) >> 2;
    for (int i = 0; i < n; ++i)
    {
        void* e = (*(void***)((char*)this + 0x5c))[i];
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(e, 0x3c))(e, t, ticks);
    }
    FUN_bc7ac0(FUN_bc8000(), 0, ticks);
}

// @ 0x00b5d220
void __fastcall FUN_00b5d220(void* self, void* dummy, unsigned n)
{
    void* nb = FUN_b5d1b0(self, 0, n);
    int count = *(int*)((char*)self + 8);
    for (int i = 0; i < count; ++i)
    {
        void** buckets = *(void***)((char*)self + 4);
        void* node = buckets[i];
        while (node)
        {
            unsigned key = *(unsigned*)node;
            void* next = *(void**)((char*)node + 8);
            buckets[i] = next;
            unsigned r = key % n;
            *(void**)((char*)node + 8) = ((void**)nb)[r];
            ((void**)nb)[r] = node;
            node = buckets[i];
        }
    }

    unsigned old = *(unsigned*)((char*)self + 4);
    if (count > 1 && old != *(unsigned*)((char*)self + 0x30))
    {
        if (old >= *(unsigned*)((char*)self + 0x24) &&
            old <  *(unsigned*)((char*)self + 0x28))
        {
            *(unsigned*)old = *(unsigned*)((char*)self + 0x1c);
            *(unsigned*)((char*)self + 0x1c) = old;
        }
        else
        {
            operator_delete_00f47380((void*)old);
        }
    }
    *(void**)((char*)self + 4) = nb;
    *(int*)((char*)self + 8) = (int)n;
}

// @ 0x00b5d2c0
void __fastcall FUN_00b5d2c0(void* self, void* dummy, void* args)
{
    float v[4];
    v[0] = v[1] = v[2] = v[3] = 1.0f;

    // MainArguments() writes the parsed arg array back through &args (the incoming slot), so the
    // handle used for the follow-up calls is the value the caller passed in, captured up front.
    void* self0 = args;
    MainArguments_838020(args, dummy, (int*)&args, 0, 1);

    int* opt = (int*)Args_OptionArguments_838330(self0, dummy, (const char*)0x14626b4, 1);
    if (opt)
    {
        float scratch[4];
        void* sec = *(void**)((char*)self + 4);
        float* q = (float*)((void* (__thiscall*)(void*, float*, int))g_vfn(sec, 0xb4))
                        (sec, scratch, *opt);
        v[0] = q[0];
        v[1] = q[1];
        v[2] = q[2];
        v[3] = 1.0f;
    }

    EAVariant var;
    *(unsigned short*)((char*)&var + 0x10) = 0;
    *(unsigned short*)((char*)&var + 0x12) = 0;
    Variant_Construct_93dd80(&var, dummy, 0x34, 0, v, 0x10, 1);

    void* g = g_appProps_15fd918;
    ((void (__thiscall*)(void*, unsigned, void*))g_vfn(g, 0x14))(g, 0x5d2c54b, &var);

    if (((unsigned char*)&var)[0x10] & 4)
        Variant_Destruct_93db80(&var, dummy, 0);
}

// @ 0x00b5d430
void cGonzagoMode::FUN_00b5d430(int mode)
{
    char* head = (char*)this + 0x20;
    b2c = 1;
    bool found = false;
    for (void* nd = *(void**)head; nd != head && !found; nd = *(void**)nd)
    {
        void* o = *(void**)((char*)nd + 8);
        if (((bool (__thiscall*)(void*, int))g_vfn(o, 0x10))(o, mode))
            found = true;
    }
    b2c = 0;

    if (IsModifierKeyDown_8d2fb0(0x3e9))
        return;

    void* pm = FUN_b3d240();
    char out1[12];
    ((void (__thiscall*)(void*, void*, int, float, float, float))g_vfn(pm, 0x38))
        (pm, out1, 0, g_1686b00, g_1686b04, g_1686b08);

    void* cur = GetGameTerrainCursor_b30d70();
    void* o34 = (char*)cur + 0x34;
    char out2[12];
    ((void (__thiscall*)(void*, void*))g_vfn(o34, 0x38))(o34, out2);

    void* cur2 = GetGameTerrainCursor_b30d70();
    void* o2 = (char*)cur2 + 0x34;
    void* bs = BuildSurfaceOrientation_b7f190(PlanetModel_b3d350());
    char out3[12], out4[12];
    ((void (__thiscall*)(void*, void*, void*, void*))g_vfn(o2, 0x3c))(o2, bs, out3, out4);
}

// @ 0x00b5d540
bool cGonzagoMode::FUN_00b5d540()
{
    bool res = true;

    int n = (*(int*)((char*)this + 0x60) - *(int*)((char*)this + 0x5c)) >> 2;
    for (int i = 0; i < n; ++i)
    {
        void* e = (*(void***)((char*)this + 0x5c))[i];
        int a = *(int*)((char*)FUN_b3d320() + 0x20);
        if (!((bool (__thiscall*)(void*, int))g_vfn(e, 0x24))(e, a))
            res = false;
    }

    {   // SP::cCreatureModeStrategy::Instance() + 8
        void* o = (char*)cCreatureModeStrategy_d38840() + 8;
        int a = *(int*)((char*)FUN_b3d320() + 0x20);
        bool r = ((bool (__thiscall*)(void*, int))g_vfn(o, 0x24))(o, a);
        res = r && res;
    }
    {   // SP::cTribeModeStrategy::Instance() + 0xc
        void* o = (char*)cTribeModeStrategy_cd40b0() + 0xc;
        int a = *(int*)((char*)FUN_b3d320() + 0x20);
        bool r = ((bool (__thiscall*)(void*, int))g_vfn(o, 0x24))(o, a);
        res = r && res;
    }
    {   // SP::cCivModeStrategy::Get() + 4
        void* o = (char*)cCivModeStrategy_cf74c0() + 4;
        int a = *(int*)((char*)FUN_b3d320() + 0x20);
        bool r = ((bool (__thiscall*)(void*, int))g_vfn(o, 0x24))(o, a);
        res = r && res;
    }
    {   // FUN_00fd9c60() + 8
        void* o = (char*)FUN_fd9c60() + 8;
        int a = *(int*)((char*)FUN_b3d320() + 0x20);
        bool r = ((bool (__thiscall*)(void*, int))g_vfn(o, 0x24))(o, a);
        res = r && res;
    }
    {   // GetEditSelection() + 8
        void* o = (char*)GetEditSelection_d1bf00() + 8;
        int a = *(int*)((char*)FUN_b3d320() + 0x20);
        bool r = ((bool (__thiscall*)(void*, int))g_vfn(o, 0x24))(o, a);
        res = r && res;
    }
    return res;
}

// @ 0x00b5d870
void __stdcall FUN_00b5d870(int param)
{
    char cl[0x54];
    CmdLine_ctor_92c210(cl, 0, param);
    EastlString16 ws;
    ws.begin = ws.end = (unsigned short*)0x1667bac;      // eastl::gEmptyString16
    ws.cap = (unsigned short*)0x1667bae;

    if (FindSwitch_92b300(cl, 0, (const void*)0x146287c /* L"gonzago" */, 0, &ws, 0) != -1)
    {
        EastlString8 out;
        ConvertToString8_93c570(&out, &ws);

        char args[0x14];
        cArguments_ctor_8386d0(args, 0, (int)out.begin);

        int count = 0;
        const char** arr = (const char**)MainArguments_838020(args, 0, &count, 0, 0x7fffffff);
        for (int i = 0; i < count; ++i)
        {
            const char* src = arr[i];
            unsigned len = 0;
            while (src[len]) ++len;

            char* begin;
            char* end;
            if (len + 1 < 2)
            {
                begin = (char*)0x1667bac;                    // eastl::gEmptyString
                end = (char*)0x1667bad;
            }
            else
            {
                begin = (char*)operator_new_0xf473a0(len + 1, (const char*)0x13f09b4 /*"Simulator"*/,
                                                     0, 0, (const char*)0x13ebb38, 0xd1);
                end = begin + len;
            }
            memcpy_11e0744(begin, src, len);
            begin[len] = 0;

            if (eastlEq_555020(begin, (const char*)0x1462874 /*"nouns"*/)) FUN_b1f960(1);
            if (eastlEq_555020(begin, (const char*)0x14555a4 /*"input"*/)) FUN_c2e4e0(1);

            if (end - begin > 1 && begin)
                operator_delete_00f47380(begin);
        }
        cArguments_dtor_837fa0(args);

        if (out.end - out.begin > 1 && out.begin)
            operator_delete_00f47380(out.begin);
    }

    if ((((char*)ws.end - (char*)ws.begin) & ~1) > 2 && ws.begin)
        operator_delete_00f47380(ws.begin);

    CmdLine_fini_5d7450(cl);
}

// @ 0x00b5da50
void cGonzagoMode::FUN_00b5da50(void* p, char head)
{
    if (((bool (__thiscall*)(void*, void*))g_vfn(this, 0x3c))(this, p))
        return;

    // Nodes are {next, prev, value} linked into a circular list whose sentinel lives at
    // this+0x20: head != 0 appends in front of the sentinel, head == 0 inserts in front of
    // the current first node (this+0x20 holds the sentinel's next link).
    void* anchor = (head != 0) ? (void*)((char*)this + 0x20)
                               : *(void**)((char*)this + 0x20);

    if (p)
        ((unsigned (__thiscall*)(void*))g_vfn(p, 4))(p);        // AddRef

    int* node = (int*)operator_new_0xf473a0(0xc, (const char*)0x13f09b4 /*"Simulator"*/,
                                            0, 0, (const char*)0x13ebb38, 0xd1);
    if (node)
    {
        node[2] = (int)p;
        if (p)
            ((unsigned (__thiscall*)(void*))g_vfn(p, 4))(p);    // AddRef
    }
    node[0] = (int)anchor;
    node[1] = *(int*)((char*)anchor + 4);
    *(void**)*(void**)((char*)anchor + 4) = node;
    *(void**)((char*)anchor + 4) = node;

    if (p)
        ((unsigned (__thiscall*)(void*))g_vfn(p, 8))(p);        // Release
}

// @ 0x00b5dbb0
void cGonzagoMode::FUN_00b5dbb0(unsigned a1, unsigned a2)
{
    void* em = EffectsMgr_67ddd0();
    ((void (__thiscall*)(void*))g_vfn(em, 0x48))(em);

    void* ms = MessageServer_67dcc0();
    ((void (__thiscall*)(void*, unsigned, void*, void*))g_vfn(ms, 0x14))(ms, 0x685f4af, 0, 0);

    bool flush = false;
    if (a2 == 0x2ccd1d2)
    {
        if (a1 == 0xdbdba1 || a1 == 0x1654c00 || a1 == 0x1654c01 ||
            a1 == 0x1654c02 || a1 == 0x1654c04 || a1 == 0x1654c05)
            flush = true;
    }
    else if (a2 == 0x1654c01 || a2 == 0x1654c02 || a2 == 0x1654c04 || a2 == 0x1654c05)
    {
        if (a1 == 0x1654c00 || a1 == 0x1654c01 || a1 == 0x1654c02 || a1 == 0x1654c04)
            flush = true;
    }
    if (flush)
        FlushTelemetry_7ebce0(Telemetry_67de90(), 0, 0xffffffffu);

    void* cm = FUN_67cab0();
    FindLocal_801bb0(cm, 0, 0x1002);
    Set_8017f0(cm, 0, 0);

    {
        void* o = (char*)cCreatureModeStrategy_d38840() + 8;
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(o, 0x18))(o, a1, a2);
    }
    {
        void* o = (char*)cTribeModeStrategy_cd40b0() + 0xc;
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(o, 0x18))(o, a1, a2);
    }
    {
        void* o = (char*)cCivModeStrategy_cf74c0() + 4;
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(o, 0x18))(o, a1, a2);
    }
    {
        void* o = (char*)FUN_fd9c60() + 8;
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(o, 0x18))(o, a1, a2);
    }
    {
        void* o = (char*)GetEditSelection_d1bf00() + 8;
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(o, 0x18))(o, a1, a2);
    }

    FUN_b335d0(a1, a2);

    int n = (*(int*)((char*)this + 0x60) - *(int*)((char*)this + 0x5c)) >> 2;
    for (int i = 0; i < n; ++i)
    {
        void* e = (*(void***)((char*)this + 0x5c))[i];
        ((void (__thiscall*)(void*, unsigned, unsigned))g_vfn(e, 0x18))(e, a1, a2);
    }

    EastlString8 str;
    str.begin = str.end = (char*)0x1667bac;                  // eastl::gEmptyString
    str.cap = (char*)0x1667bad;

    if ((a1 == 0x2ccd1d2 || a1 == 0xdbdba1) && a2 - 0x1654c00 <= 0x10)
    {
        switch (a2 - 0x1654c00)
        {
        case 0x0: eastlAssign_454cb0(&str, 0, (const char*)0x145d940, (const char*)0x145d948); break;
        case 0x1: eastlAssign_454cb0(&str, 0, (const char*)0x145d930, (const char*)0x145d93c); break;
        case 0x2: eastlAssign_454cb0(&str, 0, (const char*)0x145d924, (const char*)0x145d92d); break;
        case 0x4: eastlAssign_454cb0(&str, 0, (const char*)0x145d910, (const char*)0x145d920); break;
        case 0x5: eastlAssign_454cb0(&str, 0, (const char*)0x145d904, (const char*)0x145d90d); break;
        case 0xd: eastlAssign_454cb0(&str, 0, (const char*)0x146289c, (const char*)0x14628a8); break;
        case 0x10: eastlAssign_454cb0(&str, 0, (const char*)0x146289c, (const char*)0x14628a8); break;
        default: break;
        }
    }

    if (a2 == 0x2ccd1d2)
    {
        eastlAssign_454cb0(&str, 0, (const char*)0x146288c, (const char*)0x146289b);
        unsigned local[3];
        local[0] = local[1] = local[2] = 0;
        SetAvatarSpecies_4df310(GetSetting9_401090(), 0, local);
    }
    else if (a2 == 0xdbdba1)
    {
        void* app = App_67dd10();
        void* ed = ((void* (__thiscall*)(void*))g_vfn(app, 0x2c))(app);
        if (ed)
        {
            EastlString16 ws;
            ws.begin = ws.end = (unsigned short*)0x1667bac;  // eastl::gEmptyString16
            ws.cap = (unsigned short*)0x1667bae;

            if (GetEditorName_5805e0(ed, 0, &ws))
            {
                EastlString8 out;
                void* p = ConvertToString8_93c570(&out, &ws);
                if (p != (void*)&str)
                    eastlAssign_454cb0(&str, 0, ((char**)p)[0], ((char**)p)[1]);
                if (out.end - out.begin > 1 && out.begin)
                    operator_delete_00f47380(out.begin);

                void* p2 = FUN_91ba90(&out, &str, (const char*)0x13eb430);
                if (p2 != (void*)&str)
                    eastlAssign_454cb0(&str, 0, ((char**)p2)[0], ((char**)p2)[1]);
                if (out.end - out.begin > 1 && out.begin)
                    operator_delete_00f47380(out.begin);
            }
            if ((((char*)ws.end - (char*)ws.begin) & ~1) > 2 && ws.begin)
                operator_delete_00f47380(ws.begin);
        }
    }

    ((void (__thiscall*)(void*))g_vfn(this, 0x58))(this);

    if (str.end - str.begin > 1 && str.begin)
        operator_delete_00f47380(str.begin);
}

// @ 0x00b5e050
int __fastcall FUN_00b5e050(void* self, void* dummy, const int* key)
{
    // eastl::hashtable<unsigned, ...>::find() writes its iterator through the first stack
    // argument (the struct-return buffer); the node pointer is the iterator's first word.
    int it[2];                                       // find() output: {node, ...}
    HashtableFind_645ed0(self, dummy, it, key);

    if (it[0] != *(int*)(*(int*)((char*)self + 4) + *(int*)((char*)self + 8) * 4))
        return it[0] + 4;

    it[0] = *key;
    *(char*)&it[1] = 0;
    int out;
    FUN_c15fd0(self, dummy, &out, it, (void*)((unsigned)(size_t)key & 0xffffff00u));
    return out + 4;
}