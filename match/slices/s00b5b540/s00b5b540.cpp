// Slice s00b5b540 (batch bfs1) — 39 functions.
// Module "Spore"; SP::cGonzagoSubsystem and related Gonzago helpers.  Each block
// starts with its original address.

#include "s00b5b540.h"

extern "C" void* FUN_00b3d320();
extern "C" void* FUN_00b3d3a0();
extern "C" void* SP_App_67dd10();
extern "C" void* SP_MessageServer_67dcc0();
extern "C" void* SP_GameTimeManager_00b3d380();
extern "C" void  FUN_00b96600(void*, void*);
extern "C" void  FUN_004cd3c0(void*);
extern "C" void  FUN_00586800(void*, int);
extern "C" void  FUN_005724e0(void*, int);
extern "C" void  FUN_00d3bd70(void*);
extern "C" void  RegisterAppMode_cGameEditModeStrategy(void*);
extern "C" void  RegisterAppMode_SPcTribeModeStrategy(void*);
extern "C" void  FUN_00cfa320(void*);
extern "C" void  FUN_00fddb40(void*);
extern "C" void  RegisterAppMode_cCellMode(void*);
extern "C" void  FUN_00b5d3f0(void*);
extern "C" void  FUN_00b32190(int, int, const char*);
extern "C" void  FUN_00b323f0(void*);
extern "C" void  FUN_00b6a530();
extern "C" void  FUN_00c103f0();
extern "C" void  FUN_00d1f2a0();
extern "C" void  FUN_00ec40b0();
extern "C" void  FUN_00b13b20();
extern "C" void  FUN_00bbb802();
extern "C" void  free_00f47380(void*);
extern "C" void  operator_delete_proxy(void*);
extern "C" void  FUN_00692f90(void*, void*, const char*, unsigned);
extern "C" void  FUN_00692900(void*, void*);
extern "C" char  FUN_00693e10(void*, void*);
extern "C" int   FUN_00574570();
extern "C" char  FUN_00dd18d0(int);
extern "C" void* FUN_00b3d220();

extern int* g_1686a18;   // vector begin
extern int* g_1686a1c;   // vector end
extern int* g_1686a20;   // vector capacity
extern char g_vt0dummy, g_vt1dummy;

static inline void* g_vt(void* p) { return *(void**)p; }
static inline void* g_vfn(void* p, int off) { return *(void**)((char*)g_vt(p) + off); }

// ---- wrappers / free helpers ------------------------------------------------

// @ 0x00b5b800
int FUN_00b5b800()
{
    GameModeObj* p = (GameModeObj*)FUN_00b3d320();
    if (p) return p->GetLocation();
    return -1;
}

// @ 0x00b5b820
int FUN_00b5b820()
{
    GameModeObj* p = (GameModeObj*)FUN_00b3d320();
    if (p) return p->FUN_00ff35d0();
    return -1;
}

// @ 0x00b5b690
void FUN_00b5b690(int v)
{
    int* p = g_1686a18;
    if (p == g_1686a1c) return;
    while (*p != v)
    {
        ++p;
        if (p == g_1686a1c) return;
    }
    if (p != g_1686a1c)
    {
        *p = g_1686a1c[-1];
        --g_1686a1c;
    }
}

// @ 0x00b5b6f0
void FUN_00b5b6f0(int v)
{
    int* p = g_1686a1c;
    if (p < g_1686a20)
    {
        g_1686a1c = p + 1;
        if (p) *p = v;
    }
    else
    {
        FUN_00b96600(g_1686a1c, &v);
    }
}

// @ 0x00b5ca60
bool __fastcall FUN_00b5ca60(int* p)
{
    return *(int*)((char*)p + 0x30) > 0;
}

// @ 0x00b5cb60
bool FUN_00b5cb60(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))g_vfn(obj, 0x2c))(obj, a);
    return true;
}

// @ 0x00b5cb80
bool FUN_00b5cb80(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))g_vfn(obj, 0x28))(obj, a);
    return true;
}

// @ 0x00b5cba0
bool FUN_00b5cba0(int a, int* p)
{
    void* sub = (char*)(void*)*p + 8;
    ((void(__thiscall*)(void*, int))g_vfn(sub, 0x14))(sub, a);
    return true;
}

// @ 0x00b5cbc0
bool FUN_00b5cbc0(int a, int* p)
{
    void* sub = (char*)(void*)*p + 8;
    ((void(__thiscall*)(void*, int))g_vfn(sub, 0x10))(sub, a);
    return true;
}

// @ 0x00b5cbe0
bool FUN_00b5cbe0(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))FUN_00586800)(obj, a);
    return true;
}

// @ 0x00b5cc00
bool FUN_00b5cc00(int a, int* p)
{
    void* obj = (void*)*p;
    ((void(__thiscall*)(void*, int))FUN_005724e0)(obj, a);
    return true;
}

// @ 0x00b5ca50
void FUN_00b5ca50()
{
    void* p = FUN_00b3d3a0();
    ((void(__thiscall*)(void*))g_vfn(p, 0x28))(p);
}

// @ 0x00b5c990
void FUN_00b5c990()
{
    void* a = SP_App_67dd10();
    RegisterAppMode_cGameEditModeStrategy(a);
    FUN_00d3bd70(a);
    RegisterAppMode_SPcTribeModeStrategy(a);
    FUN_00cfa320(a);
    FUN_00fddb40(a);
    RegisterAppMode_cCellMode(a);
    FUN_00b5d3f0(a);
}

// ===========================================================================
// SP::cGonzagoSubsystem
// ===========================================================================

#define V0_CALL(ret, slot, ...) ((ret(__thiscall*)(cGonzagoSubsystem*, ...))vt0[(slot)/4])(this, __VA_ARGS__)

// @ 0x00b5b840
bool cGonzagoSubsystem::CheckGonzagoSubsystemInitState(int param)
{
    if (param != ((int(__thiscall*)(void*))vt0[0x1c / 4])(this)) return false;
    if (param != ((int(__thiscall*)(void*))vt0[0x20 / 4])(this)) return false;
    if (mCurrent != -1) return false;
    return true;
}

// @ 0x00b5b880
void cGonzagoSubsystem::SetTransitionState1(int p)
{
    mPhase = 1;
    if (mCurrent == -1) mCurrent = p;
}

// @ 0x00b5b8a0
void cGonzagoSubsystem::SetTransitionState2(int p)
{
    mPhase = 2;
    if (mCurrent == -1) mCurrent = p;
}

// @ 0x00b5b8c0
void cGonzagoSubsystem::EndTransitionPre()
{
    mPreMode = mCurrent;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b8e0
void cGonzagoSubsystem::EndTransitionPost()
{
    mPostMode = mCurrent;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b900
void cGonzagoSubsystem::PostGameModeTransition(int, int mode)
{
    if (((int(__thiscall*)(void*))vt0[0x20 / 4])(this) != mode)
    {
        ((void(__thiscall*)(void*, int))vt0[0x44 / 4])(this, mode);
        ((void(__thiscall*)(void*))vt0[0x4c / 4])(this);
    }
}

// @ 0x00b5b930
void cGonzagoSubsystem::PreGameModeTransition(int, int mode)
{
    if (((int(__thiscall*)(void*))vt0[0x1c / 4])(this) != mode)
    {
        ((void(__thiscall*)(void*, int))vt0[0x40 / 4])(this, mode);
        ((void(__thiscall*)(void*))vt0[0x48 / 4])(this);
    }
}

// @ 0x00b5b960
cGonzagoSubsystem::cGonzagoSubsystem()
{
    vt4 = (void**)&g_vt1dummy;
    m08 = 0;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    mPreMode = -1;
    mPostMode = -1;
    mCurrent = -1;
    mPhase = 0;
}

// @ 0x00b5b9a0
cGonzagoSubsystem::~cGonzagoSubsystem()
{
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
}

// @ 0x00b5b9b0
void* cGonzagoSubsystem::ScalarDeletingDtor(char flags)
{
    void* self = this;
    vt0 = (void**)&g_vt0dummy;
    vt4 = (void**)&g_vt1dummy;
    if (flags & 1) free_00f47380(this);
    return self;
}

// ===========================================================================
// Remaining (complete behaviour / approximations)
// ===========================================================================

// @ 0x00b5b540
bool FUN_00b5b540(int* a, int* b, int, int p4)
{
    int* s = (int*)((int(__thiscall*)(void*))g_vfn(a, 0x10))(a);
    b[2] = s[0];
    b[3] = p4;
    b[4] = s[2];
    int r = ((int(__thiscall*)(void*, unsigned))g_vfn(b, 0xc))(b, 0x532dc8b);
    if (!r) return false;
    int* t = (int*)((int(__thiscall*)(void*))g_vfn(a, 0x18))(a);
    unsigned u = ((unsigned(__thiscall*)(void*))g_vfn(t, 0x1c))(t);
    FUN_004cd3c0((void*)u);
    int q = ((int(__thiscall*)(void*, int, unsigned))g_vfn(t, 0x30))(t, *(int*)(r + 0x18), u);
    return q != -1;
}

// @ 0x00b5b5d0
void* __fastcall FUN_00b5b5d0_adjust(void* self_, unsigned id)
{
    char* self = (char*)self_;
    if (id == 0x11416b8) return self - 8;
    if (id == 0x179c807) return (self - 8) ? self : 0;
    return 0;
}

// @ 0x00b5b6c0
void* cGonzagoSimulator_ctor(void* p)
{
    *(int*)((char*)p + 4) = (int)&g_vt0dummy;
    *(int*)((char*)p + 8) = 0x1444434;
    *(int*)((char*)p) = 0x146155c;
    *(int*)((char*)p + 8) = (int)&g_vt1dummy;
    *(char*)((char*)p + 0xc) = 0;
    *(char*)((char*)p + 0xd) = 0;
    *(char*)((char*)p + 0xe) = 0;
    return p;
}

// @ 0x00b5b730
void FUN_00b5b730(void) { /* eastl::vector<bool> insert/move; incomplete */ }

// @ 0x00b5ba30
void FUN_00b5ba30(int) { /* large universe/species setup; incomplete */ }

// @ 0x00b5be10
void FUN_00b5be10(void* self, void* stream)
{
    FUN_00b5ba30(1);
    char buf[0xa14];
    FUN_00692f90(buf, self, "cmp", 0x1a80d26);
    FUN_00692900(buf, stream);
}

// @ 0x00b5be60
bool FUN_00b5be60(void* self, void* stream)
{
    FUN_00b5ba30(0);
    char buf[0xa20];
    FUN_00692f90(buf, self, "cmp", 0x1a80d26);
    char ok = FUN_00693e10(buf, stream);
    if (ok) { /* species manager path approximated */ }
    return ok != 0;
}

// @ 0x00b5bf30
bool FUN_00b5bf30(void* self, void*)
{
    void* ms = SP_MessageServer_67dcc0();
    *(void**)((char*)self + 0x48) = ms;
    *(void**)((char*)self + 0x4c) = self;
    *(int*)((char*)self + 0x50) = (int)&g_vt0dummy;
    *(int*)((char*)self + 0x54) = 1;
    *(int*)((char*)self + 0x58) = 0;
    if (ms && self)
        ((void(__thiscall*)(void*, void*, unsigned))g_vfn(ms, 0x24))(ms, self, 0xf52feda1);
    FUN_00ec40b0();
    return true;
}

// @ 0x00b5bf80
bool FUN_00b5bf80(void* self, void*)
{
    void* ms = SP_MessageServer_67dcc0();
    *(void**)((char*)self + 0x34) = ms;
    *(void**)((char*)self + 0x38) = self;
    *(int*)((char*)self + 0x3c) = (int)&g_vt0dummy;
    *(int*)((char*)self + 0x40) = 0xc;
    *(int*)((char*)self + 0x44) = 0;
    if (ms && self)
        for (unsigned i = 0; i < 0x30; i += 4)
            ((void(__thiscall*)(void*, void*, int))g_vfn(ms, 0x24))(ms, self, 0);
    void* app = SP_App_67dd10();
    void* q = (void*)((int(__thiscall*)(void*))g_vfn(app, 0x50))(app);
    ((void(__thiscall*)(void*, int, void*))g_vfn(q, 0x20))(q, 0xebb802, (void*)&FUN_00b13b20);
    FUN_00b6a530();
    FUN_00c103f0();
    FUN_00d1f2a0();
    return true;
}

// @ 0x00b5c9d0
int FUN_00b5c9d0(void* p)
{
    unsigned v = (unsigned)p;
    if (v == 0x2ccd1d2 || v == 0x8916f92d || v == 0xfffffffe) return (int)p;
    if (v > 0x1654c10) return -1;
    if (v == 0x1654c10) return (int)p;
    if (v >= 0x1654c04) return (int)p;
    if (v == 0xdbdba1) return 0xdbdba1;
    if (v <= 0x1654bff) return -1;
    if (v <= 0x1654c02) return (int)p;
    if (v <= 0x1654c06) return -1;
    if (v == 0x1654c08) return (int)p;
    return -1;
}

// @ 0x00b5ca70
bool FUN_00b5ca70()
{
    int m = FUN_00b5b800();
    if (m == -1) return false;
    for (;;)
    {
        if (m == 0x1654c00 || m == 0x1654c01 || m == 0x1654c02 ||
            m == 0x1654c04 || m == 0x1654c05) return true;
        if (m == 0x1654c10 && *(int*)(0x16c7aa4 + 0xd0) == 2) return true;
        if (m == 0xdbdba1)
        {
            m = FUN_00574570();
            if (m == -1) return false;
            continue;
        }
        return false;
    }
}

// @ 0x00b5cb20
bool FUN_00b5cb20(int p)
{
    if (!FUN_00dd18d0(p)) return false;
    if (FUN_00b5b800() == 0xdbdba1 && FUN_00b5ca70()) return false;
    return true;
}

// @ 0x00b5cc80
void FUN_00b5cc80()
{
    void* gt = SP_GameTimeManager_00b3d380();
    ((void(__thiscall*)(void*))g_vfn(gt, 0))(gt);
    FUN_00b32190(0x600c4ae, 3, "cinematicAll");
    FUN_00b32190(0x4bf38a5, 1, "cinematic");
    FUN_00b32190(0x64beb65, 1, "tutorial");
    FUN_00b32190(0x4bf38a6, 1, "editor");
    FUN_00b32190(0x4d02e35, 3, "comm screen");
    FUN_00b32190(0x7e9e4b7, 1, "adventure dialog");
    FUN_00b323f0(gt);
}

// @ 0x00b5cd90
void FUN_00b5cd90(void* self_, int param)
{
    char* self = (char*)self_;
    unsigned n = (unsigned)((*(char**)(self + 0x60) - *(char**)(self + 0x5c)) >> 2);
    for (unsigned i = 0; i < n; ++i)
    {
        void* e = ((void**)*(void**)(self + 0x5c))[i];
        ((void(__thiscall*)(void*, int))g_vfn(e, 0x30))(e, param);
    }
}

// @ 0x00b5cde0
bool FUN_00b5cde0(int p)
{
    void* app = SP_App_67dd10();
    void* q = (void*)((int(__thiscall*)(void*))g_vfn(app, 0x50))(app);
    ((void(__thiscall*)(void*, int))g_vfn(q, 0x34))(q, p);
    void* r = FUN_00b3d220();
    if (!r) return false;
    app = SP_App_67dd10();
    q = (void*)((int(__thiscall*)(void*))g_vfn(app, 0x50))(app);
    void* s = (void*)((int(__thiscall*)(void*))g_vfn(q, 0x38))(q);
    if (s)
    {
        int v = ((int(__thiscall*)(void*, unsigned))g_vfn(s, 0xc))(s, 0x11966ed);
        *(int*)((char*)r + 0xc) = v;
        return v != 0;
    }
    *(int*)((char*)r + 0xc) = 0;
    return false;
}

// @ 0x00b5ce70
void FUN_00b5ce70(void*, int) { /* cGonzagoSimulator update; incomplete */ }