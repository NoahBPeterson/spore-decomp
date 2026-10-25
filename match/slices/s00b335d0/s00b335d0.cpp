// Slice s00b335d0 -- unnamed gameplay/front-end state class (vtable at +0,
// state field +0x84, ref-counted client +0x88, flags +0x10e/+0x10f), the
// star-database reload loop, a heap sift-up helper, and a terrain-height query.
// No dev-PDB symbols exist for this module; names are FUN_<va>.
#include "types.h"
#include <string.h>

typedef unsigned char  u8;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------
// Out-of-line callees (named by retail VA so the difftest resolver can bind).
// ---------------------------------------------------------------------------
void* __cdecl   FUN_00b3d340();
void* __cdecl   FUN_00b3d2a0();                       // SP::StarManager
void* __cdecl   SP_ObjectTemplateDB();
void* __cdecl   SP_PlanetModel();
void  __cdecl   Fn436ce0(float* out, int x);
void* __cdecl   Fn449c20(float* out);                 // SP::normalized_safe
float __fastcall FUN_00c887c0(int value);

struct TFn0  { void  f(); };                          // 0x00b28c20
struct TFn1  { void  f(); };                          // 0x00bb8b20
struct TFn2  { int   f(); };                          // 0x00bb9b80
struct TFn3  { void  f(int); };                       // 0x00b3d520
struct TFnH  { float f(int); };                       // 0x00f927c0
struct TFnN  { void* f(float*); };                    // 0x00f92c20

// ---------------------------------------------------------------------------
// Common object: vptr +0, state tag +0x84, owned object +0x88.
// ---------------------------------------------------------------------------
struct RefObj {
    virtual void v00();
    virtual void Release();          // slot 1 (+0x04)
};

struct StateObj {
    virtual void s00();              // +0x00
    virtual void s01();              // +0x04
    virtual void s02();              // +0x08
    virtual void s03();              // +0x0c
    virtual void s04();              // +0x10
    virtual void s05();              // +0x14
    virtual void s06();              // +0x18
    virtual void s07();              // +0x1c
    virtual void s08();              // +0x20
    virtual void s09();              // +0x24
    virtual void s10();              // +0x28
    virtual void s11();              // +0x2c
    virtual void s12();              // +0x30
    virtual void s13();              // +0x34
    virtual void s14();              // +0x38
    virtual void s15();              // +0x3c
    virtual void s16();              // +0x40
    virtual void s17();              // +0x44
    virtual void s18();              // +0x48
    virtual void s19();              // +0x4c
    virtual void s20();              // +0x50
    virtual void s21();              // +0x54
    virtual void s22();              // +0x58
    virtual void s23(int, int, int, int, int, float);  // +0x5c
    char  mPad0[0x84 - 4];
    void* mState;                    // +0x84
    RefObj* mRef;                    // +0x88
    char  mPad1[0x10e - 0x8c];
    u8    m10e;                      // +0x10e
    u8    m10f;                      // +0x10f

    void FUN_00b33ca0(int a, int b, int c);
    void FUN_00b33d00();
    void FUN_00b33d20();
    void FUN_00b33d40(void* state);
    void FUN_00b33dd0();
    u8   FUN_00b33e10(unsigned id);
};

// @ 0x00b33c30
void __cdecl FUN_00b33c30(double value, int a, int b)
{
    extern void* PTR_01569488;
    extern void FUN_008822e0(double, int, int, int, int);
    FUN_008822e0(value, a, b, (int)PTR_01569488, 0x01460564);
}

// @ 0x00b33c70
void __fastcall FUN_00b33c70(char* p)
{
    typedef void (__thiscall* Fn)(void*);
    ((Fn)(*(void**)(*(char**)(p - 8) + 0x10)))(p - 8);
}

// @ 0x00b33ca0
void StateObj::FUN_00b33ca0(int a, int b, int c)
{
    s23(a, b, c, -1, -1, 1.0f);
}

// @ 0x00b33d00
void StateObj::FUN_00b33d00()
{
    if (mState != (void*)0x1654c00) {
        typedef void (__thiscall* Fn)(void*);
        char* vt = *(char**)this;
        void* fn = *(void**)(vt + 0x14);
        mState = (void*)0x1654c08;
        ((Fn)fn)(this);
    }
}

// @ 0x00b33d20
void StateObj::FUN_00b33d20()
{
    typedef void (__thiscall* Fn)(void*);
    char* vt = *(char**)this;
    void* fn = *(void**)(vt + 0x18);
    mState = (void*)0x1654c00;
    ((Fn)fn)(this);
}

// @ 0x00b33d40
void StateObj::FUN_00b33d40(void* state)
{
    RefObj* r = mRef;
    if (r != 0) {
        mRef = 0;
        r->Release();
    }
    typedef void (__thiscall* Fn)(void*);
    switch ((int)state) {
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c06:
    case 0x1654c10:
    case 0x2ccd1d2:
        (*(Fn*)(*(char**)this + 0x14))(this);
        break;
    default:
        (*(Fn*)(*(char**)this + 0x18))(this);
        break;
    }
    mState = state;
}

// @ 0x00b33dd0
void StateObj::FUN_00b33dd0()
{
    RefObj* r = mRef;
    if (r != 0) {
        mRef = 0;
        r->Release();
    }
    if (mState != (void*)-1) {
        typedef void (__thiscall* Fn)(void*);
        (*(Fn*)(*(char**)this + 0x18))(this);
        mState = (void*)-1;
    }
}

// @ 0x00b33e10
u8 StateObj::FUN_00b33e10(unsigned id)
{
    switch (id) {
    case 0x2399be55: return m10e;
    case 0x24682294:
    case 0x476a98c7: return m10f;
    default: return 0;
    }
}

// @ 0x00b33ea0
void __cdecl FUN_00b33ea0(int* base, int start, int pos, int value)
{
    int parent = (pos - 1) >> 1;
    if (pos > start) {
        do {
            if (!(FUN_00c887c0(base[parent]) < FUN_00c887c0(value)))
                break;
            base[pos] = base[parent];
            pos = parent;
            parent = (pos - 1) >> 1;
        } while (pos > start);
    }
    base[pos] = value;
}

// ---------------------------------------------------------------------------
// 0x00b338f0 -- reload the star database and notify every registered template.
// ---------------------------------------------------------------------------
struct StarManager {
    char  mPad[0xf0];
    int*  mpBegin;                    // +0xf0
    int*  mpEnd;                      // +0xf4
};

// @ 0x00b338f0
void __cdecl FUN_00b338f0()
{
    void* a = FUN_00b3d340();
    ((TFn0*)a)->f();
    StarManager* sm = (StarManager*)FUN_00b3d2a0();
    ((TFn1*)sm)->f();
    StarManager* sm2 = (StarManager*)FUN_00b3d2a0();
    int count = (int)(sm2->mpEnd - sm2->mpBegin);
    for (int i = 0; i < count; i++) {
        int* db = (int*)SP_ObjectTemplateDB();
        int obj = sm2->mpBegin[i];
        int v = ((TFn2*)(void*)obj)->f();
        typedef void (__thiscall* Fn)(void*, int);
        (*(Fn)(*(char**)db + 0x60))(db, v);
    }
}

// ---------------------------------------------------------------------------
// 0x00b34280 -- terrain height / water height query with optional normal.
// ---------------------------------------------------------------------------
struct TerrainMap {
    char  mPad[0x34];
    float m34;                        // +0x34
    float m38;                        // +0x38
    float m3c;                        // +0x3c
};

// @ 0x00b34280
float __cdecl FUN_00b34280(int, int, int x, float* out, char useWater, char waterOnly)
{
    int pm = (int)SP_PlanetModel();
    if (pm == 0)
        return 0.0f;
    int* tm = *(int**)(pm + 0x24);
    if (tm == 0)
        return 0.0f;
    typedef void* (__thiscall* Fn)(void*);
    TerrainMap* map = (TerrainMap*)(*(Fn)(*(char**)tm + 0x0c))(tm);
    if (waterOnly)
        return map->m3c * map->m38 + map->m34;

    float h = ((TFnH*)map)->f(x);
    if (useWater) {
        float w = map->m3c * map->m38 + map->m34;
        if (w >= h) {
            h = w;
            if (out != 0) {
                float v[3];
                Fn436ce0(v, x);
                memcpy(out, v, 12);
            }
            return h;
        }
    }
    if (out != 0) {
        if (*(char*)(pm + 0xf0) != 0) {
            float v[3];
            void* r = Fn449c20(v);
            memcpy(out, r, 12);
        } else {
            float v[3];
            void* r = ((TFnN*)map)->f(v);
            memcpy(out, r, 12);
        }
    }
    return h;
}

// ---------------------------------------------------------------------------
// Front-end state-transition dispatchers and render-state handlers.
// ---------------------------------------------------------------------------
#define VSLOT(p, off, T) ((T)(*(void***)(p))[(off) / 4])

// Engine singletons / managers reached through their retail VA thunks.
void* __cdecl FUN_00b3d3e0();          // SP::EventLog
void* __cdecl FUN_00b3d4f0();
void* __cdecl FUN_00b3d300();          // SP::NounManager
void* __cdecl FUN_00b3d4b0();
void* __cdecl FUN_00b3d470();
void* __cdecl FUN_00b3d400();
void* __cdecl FUN_00b3d320();          // global app object
void* __cdecl FUN_00b3d310();
void* __cdecl FUN_00b3d240();
void* __cdecl FUN_00b3d430();          // SP::TerraformingManager
void* __cdecl FUN_00b3d3b0();
void* __cdecl FUN_00b3d330();          // SP::SimTicker
void* __cdecl FUN_00b3d410();
void* __cdecl FUN_00b3d3c0();
void* __cdecl FUN_00b3d250();          // SP::GameInputManager
void* __cdecl FUN_00b3d520();          // SP::GonzagoModelWorld
void* __cdecl FUN_00fd9c60();
void* __cdecl FUN_0067dd40();

// thiscall methods on those singletons (declared cdecl, called through a cast).
void FUN_00dd6d70();   // cSPUIEventLog::clear_events
void FUN_00e30680();   // cSPUIAssetDiscoveryManager::Reset
void FUN_00b225b0();   // cGameNounManager::Dummy225b0
void FUN_00d00440();
void FUN_00b28990();   // GameModeSave
void FUN_01035900();   // cSPSpaceGfx::InitForGame
void FUN_00e15b70();   // cUIMissionCardPanel::ShowAllCards
void FUN_00e15b60();
void FUN_00b1dfc0();
void FUN_00b5a390();
void FUN_00fdf8e0();   // cAppModeSpace::ExitPlanetTransition
void FUN_00b18dd0();
void FUN_00e44200();
void FUN_00b72640();
void FUN_00bc20e0();   // CityDisplayOwner::SetSubject
void FUN_00b2f680();
void FUN_00801400();   // SimTicker byte getter
void FUN_010829f0();

#define TC1(fn, T)  ((T)(fn))
#define TCV(fn)     ((void (__thiscall*)(void*))(fn))
#define TCVi(fn)    ((void (__thiscall*)(void*, int))(fn))
#define TCVp(fn)    ((void (__thiscall*)(void*, void*))(fn))

// Free transition helpers.
void __cdecl FUN_00b32a10(void*, void*);
void __cdecl FUN_00b328e0(void*);
void __cdecl FUN_00b32970(void*, void*);
void __cdecl FUN_00b33540();
void __cdecl FUN_00b33130(void*);
void __cdecl FUN_00b33030(void*);
void __cdecl FUN_00b32e80(void*);
void __cdecl FUN_00b32b20(void*);
void __cdecl FUN_00b32ce0(void*);
void __cdecl FUN_00b334e0();
void __cdecl FUN_00b33350(void*);
void __cdecl FUN_00b330e0(void*);
void __cdecl FUN_00b32f60(void*);
void __cdecl FUN_00b32dd0(void*);
void __cdecl FUN_00b32aa0(void*);
void __cdecl FUN_00b32c60(void*);
void __cdecl FUN_006b2350();           // SP_SomethingAllSaveAreas
void __cdecl FUN_006ad800(int);
void __cdecl FUN_00bca6f0();           // cAgentOrderManager::RegisterClassCallbacks

// 0x00b32890 advances the front-end state; its argument arrives in eax.
extern "C" int __cdecl FUN_00b32890(int);

struct FlagObj {                       // object returned by FUN_00b3d320
    char mPad[0x29];
    u8   m29;                          // +0x29
};

extern void*  g_015e4ef0;              // active UI root object
extern u32    g_016f948c;
extern u32    g_016f94e4;
extern u32    g_016f924c;
extern u32    g_016f922c;
extern u32    g_016f9230;
extern u32    g_016fa38c;
extern u32    g_016fa3a0;
extern void*  g_016f89d0;              // IDirect3DDevice9 wrapper

// The six "front-end" state tags.
static bool IsFrontState(int v)
{
    switch (v) {
    case 0x1654c00:
    case 0x1654c01:
    case 0x1654c02:
    case 0x1654c04:
    case 0x1654c05:
    case 0x1654c10:
        return true;
    default:
        return false;
    }
}

// Scratch cells for the eax-convention state call (globals keep the frame
// pointer out of the generated code).
static volatile int g_stateArg;
static volatile int g_stateNext;

// @ 0x00b335d0
void __cdecl FUN_00b335d0(void* from, void* to)
{
    int fromv = (int)from;
    int tov = (int)to;
    u8 dl = IsFrontState(fromv);
    u8 cl = IsFrontState(tov);

    u8 f14 = (cl && fromv == 0xdbdba1);
    u8 f18 = (fromv == 0xdbdba1 && tov == 0x2ccd1d2);
    u8 fe  = (fromv == 0x1654c08);

    u8 fa = 0;
    if (dl && cl) {
        g_stateArg = fromv;
        __asm {
            mov eax, g_stateArg
            call FUN_00b32890
            mov g_stateNext, eax
        }
        fa = (tov == g_stateNext);
    }
    u8 fb = ((fromv == 0x2ccd1d2 || fromv == -1) && cl)
            || (fromv == 0x1654c11 && tov == 0x1654c00);
    u8 fc = (dl && tov == 0x2ccd1d2);
    u8 fd = (dl && tov == -1);
    u8 fm1 = (fromv == -1);
    u8 f8 = (fromv == 0x1654c05 && tov == 0x1654c10);
    u8 f9 = (fromv == 0x1654c10 && tov == 0x1654c05);
    u8 ff = (tov == 0x1654c08);

    FUN_00b32970(from, to);
    if (FUN_00b3d3e0() != 0)
        TCV(FUN_00dd6d70)(FUN_00b3d3e0());
    TCV(FUN_00e30680)(FUN_00b3d4f0());
    TCV(FUN_00b225b0)(FUN_00b3d300());
    TCV(FUN_00b225b0)(FUN_00b3d300());
    if (fromv != 0xdbdba1 && tov != 0xdbdba1)
        TCV(FUN_00d00440)(FUN_00b3d4b0());
    if (tov == 0x1654c08)
        TCV(FUN_00b28990)(FUN_00b3d340());
    if (fm1) {
        TCV(FUN_01035900)(FUN_00b3d470());
        FUN_00bca6f0();
    }
    if (f14)
        TCV(FUN_00e15b70)(FUN_00b3d400());
    if (f18)
        TCV(FUN_00b1dfc0)(FUN_00b3d320());
    if (f8)
        FUN_00b33540();
    if (f9) {
        TCV(FUN_00b5a390)(FUN_00b3d310());
        TCV(FUN_00fdf8e0)(FUN_00fd9c60());
    }
    if (fe)
        FUN_00b33130(to);
    if (fa)
        FUN_00b33030(to);
    if (fb)
        FUN_00b32e80(to);
    if (fc)
        FUN_00b32b20(from);
    if (fd)
        FUN_00b32ce0(from);
    if (ff) {
        TCVp(FUN_00bc20e0)(FUN_00b3d430(), to);
        TCVp(FUN_00b2f680)(FUN_00b3d3b0(), to);
        if (tov == 0x1654c00) {
            // unreachable in practice; the original still emitted this branch
            ((StateObj*)FUN_00b3d240())->FUN_00b33dd0();
        }
    }
    FUN_006b2350();
    FlagObj* g = (FlagObj*)FUN_00b3d320();
    if (g->m29 != 0)
        FUN_006ad800(1);
    g = (FlagObj*)FUN_00b3d320();
    g->m29 = 0;
    u8 tick = ((u8 (__thiscall*)(void*))FUN_00801400)(FUN_00b3d330());
    TCVi(FUN_010829f0)(FUN_00b3d330(), tick);
}

// @ 0x00b33970
void __cdecl FUN_00b33970(void* from, void* to)
{
    int fromv = (int)from;
    int tov = (int)to;
    u8 dl = IsFrontState(fromv);
    u8 cl = IsFrontState(tov);

    u8 f1c = (dl && tov == 0xdbdba1);
    u8 f20 = (cl && fromv == 0xdbdba1);
    u8 f0f = (fromv == 0x2ccd1d2 && tov == 0xdbdba1);
    u8 f10 = (fromv == 0xdbdba1 && tov == 0x2ccd1d2);
    u8 f16 = (tov == 0x1654c08);
    u8 f17 = (fromv == 0x1654c08);

    u8 f12 = 0;
    if (dl && cl) {
        g_stateArg = fromv;
        __asm {
            mov eax, g_stateArg
            call FUN_00b32890
            mov g_stateNext, eax
        }
        f12 = (tov == g_stateNext);
    }
    u8 f13 = ((fromv == 0x2ccd1d2 || fromv == -1) && cl)
            || (fromv == 0x1654c11 && tov == 0x1654c00);
    u8 f14 = (dl && tov == 0x2ccd1d2);
    u8 f15 = (dl && tov == -1);
    u8 f11 = (fromv == 0x1654c05 && tov == 0x1654c10);

    FUN_00b32a10(from, to);
    FUN_00b328e0(to);
    TCVi(FUN_00e44200)(FUN_00b3d410(), 0);
    TCVp(FUN_00b72640)(FUN_00b3d3c0(), to);
    TCV(FUN_00b18dd0)(FUN_00b3d250());
    if (fromv == -1)
        FUN_00b338f0();
    if (f1c) {
        if (fromv != 0x1654c00) {
            void* o = FUN_00b3d240();
            VSLOT(o, 0x18, void(__thiscall*)(void*))(o);
        }
        TCV(FUN_00e15b60)(FUN_00b3d400());
    }
    if (f20) {
        if (tov != 0x1654c00) {
            void* o = FUN_00b3d240();
            VSLOT(o, 0x14, void(__thiscall*)(void*))(o);
        }
    }
    if (f0f)
        VSLOT(g_015e4ef0, 0x58, void(__thiscall*)(void*))(g_015e4ef0);
    if (f10)
        VSLOT(g_015e4ef0, 0x54, void(__thiscall*)(void*))(g_015e4ef0);
    if (f11)
        FUN_00b334e0();
    if (f16)
        FUN_00b33350(from);
    if (f17)
        FUN_00b330e0(to);
    if (f12)
        FUN_00b32f60(from);
    if (f13)
        FUN_00b32dd0(to);
    if (f14)
        FUN_00b32aa0(from);
    if (f15)
        FUN_00b32c60(from);
}

// ---------------------------------------------------------------------------
// 0x00b33f50 -- render one viewer target: 0xf copy, 0x11 render, 0x1a capture.
// ---------------------------------------------------------------------------
struct Color4 {
    void*    mpViewer;                 // +0x00
    unsigned m1;                       // +0x04
    unsigned m2;                       // +0x08
    unsigned m3;                       // +0x0c
};

struct ViewerHost {
    char     mPad0[0xe8];
    void*    mpWorld;                  // +0xe8
    void*    mpViewerA;                // +0xec
    void*    mpViewerB;                // +0xf0
    char     mPad1[4];
    unsigned mClear;                   // +0xf8
    char     mPad2[0x108 - 0xfc];
    void*    mpExtra;                  // +0x108
};

void FUN_007c50b0();   // cViewer::Copy
void FUN_007c3ce0();   // cViewer::SetRenderType
void FUN_007c3c50();   // cViewer::Clear
void FUN_007c3cc0();   // cViewer::Clear variant
void FUN_007c3c20();   // cViewer::SetClearColor
void FUN_007c4be0();   // cViewer::SetRaster
void __cdecl FUN_011f21a0();  // rw::graphics::GlobalState::D3D9Sync

#define TV4(fn) ((void (__thiscall*)(void*, void*, int, int))(fn))
#define TV2i(fn) ((void (__thiscall*)(void*, int, int))(fn))
#define TV1u(fn) ((void (__thiscall*)(void*, unsigned))(fn))
#define TV1p(fn) ((void (__thiscall*)(void*, const void*))(fn))
#define TVr(fn) ((void (__thiscall*)(void*, int*, int))(fn))

typedef void (__stdcall* DevStateFn)(void*, unsigned, unsigned);

// @ 0x00b33f50
void __fastcall FUN_00b33f50(ViewerHost* self, int dummy, int flags, int code, Color4* color, void* arg4)
{
    if (code == 0xf) {
        TV4(FUN_007c50b0)(self->mpViewerA, color->mpViewer, 0, 0);
        TV2i(FUN_007c3ce0)(self->mpViewerA, 0xf, 0);
        Color4 local;
        local.mpViewer = self->mpViewerA;
        local.m1 = color->m1;
        local.m2 = color->m2;
        local.m3 = color->m3;
        void* world = self->mpWorld;
        void* r = VSLOT(world, 0x13c, void*(__thiscall*)(void*))(world);
        VSLOT(r, 0xc, void(__thiscall*)(void*, int, int, Color4*, void*))(r, flags, 0xf, &local, arg4);
        if (self->mpExtra != 0)
            VSLOT(self->mpExtra, 0xc, void(__thiscall*)(void*, int, int, Color4*, void*))(self->mpExtra, flags, 0x10, &local, arg4);
    } else if (code == 0x11) {
        void* world = FUN_00b3d520();
        if (world != 0) {
            VSLOT(world, 0x0, void(__thiscall*)(void*))(world);
            if (self->mpViewerB != 0) {
                TV4(FUN_007c50b0)(self->mpViewerB, color->mpViewer, 0, 0);
                int raster[2];
                raster[0] = -1;
                raster[1] = -1;
                void* o = FUN_0067dd40();
                VSLOT(o, 0xa8, void(__thiscall*)(void*, int, int*, int))(o, 1, raster, 0);
                TVr(FUN_007c4be0)(self->mpViewerB, raster, 1);
                TV1u(FUN_007c3cc0)(self->mpViewerB, self->mClear);
                float clear[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
                TV1p(FUN_007c3c20)(self->mpViewerB, clear);
                TV1u(FUN_007c3c50)(self->mpViewerB, 7);
                Color4 local;
                local.mpViewer = self->mpViewerB;
                local.m1 = color->m1;
                local.m2 = color->m2;
                local.m3 = color->m3;
                void* r = VSLOT(world, 0x13c, void*(__thiscall*)(void*))(world);
                VSLOT(r, 0xc, void(__thiscall*)(void*, int, int, Color4*, void*))(r, flags, 0x11, &local, arg4);
            }
            VSLOT(world, 0x4, void(__thiscall*)(void*))(world);
        }
    } else if (code == 0x1a) {
        void* world = FUN_00b3d520();
        if (world != 0) {
            VSLOT(world, 0x0, void(__thiscall*)(void*))(world);
            u32 old948c = g_016f948c;
            u32 old94e4 = g_016f94e4;
            u32 old924c = g_016f924c;
            u32 old922c = g_016f922c;
            u32 old9230 = g_016f9230;
            g_016fa3a0 |= 0x4000010;
            g_016f924c = 1;
            g_016f948c = 1;
            g_016f94e4 = 0x50505050;
            g_016f922c = 5;
            g_016fa38c |= 0x100000 | 0x3000;
            g_016f9230 = 6;
            FUN_011f21a0();
            void* dev = g_016f89d0;
            ((DevStateFn)VSLOT(dev, 0xe4, void*))(dev, 0x13, 0xe);
            ((DevStateFn)VSLOT(dev, 0xe4, void*))(dev, 0x14, 0xf);
            TV1u(FUN_007c3c50)(color->mpViewer, 6);
            unsigned modFlags = ((unsigned)flags & 0xfffff7ffu) | 0x7700u;
            void* r = VSLOT(world, 0x13c, void*(__thiscall*)(void*))(world);
            VSLOT(r, 0xc, void(__thiscall*)(void*, int, int, Color4*, void*))(r, (int)modFlags, 0x1a, color, arg4);
            dev = g_016f89d0;
            ((DevStateFn)VSLOT(dev, 0xe4, void*))(dev, 0x13, old922c);
            ((DevStateFn)VSLOT(dev, 0xe4, void*))(dev, 0x14, old9230);
            g_016fa38c |= 0x103000;
            g_016fa3a0 |= 0x4000010;
            g_016f922c = old922c;
            g_016f9230 = old9230;
            g_016f924c = old924c;
            g_016f948c = old948c;
            g_016f94e4 = old94e4;
            VSLOT(world, 0x4, void(__thiscall*)(void*))(world);
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00b34380 -- per-noun draw/particle pass over the current draw list.
// ---------------------------------------------------------------------------
struct ObjVec {
    void** mpBegin;                    // +0x00
    void** mpEnd;                      // +0x04
};

struct DrawEnt {
    char  mPad00[4];
    float m4;                          // +0x04
    char  mPad08[8];
    float m10, m14, m18, m1c;          // +0x10 orientation
    float m20, m24, m28;               // +0x20 direction
    char  mPad2c[0x64 - 0x2c];
    u8    m64;                         // +0x64
    char  mPad65[0x180 - 0x65];
    char* m180;                        // +0x180
};

float __cdecl FUN_004885d0(const float*);            // SP::Dot3
void* __cdecl FUN_0059aed0(float*, float*, void*);
void  FUN_00c446d0();
void* __cdecl FUN_00b33e40(void*);
void* __cdecl FUN_00b33e60(void*);
void* __cdecl FUN_00ae66f0(void*);                   // CastCreature

// @ 0x00b34380
void __cdecl FUN_00b34380(int* self, float dt)
{
    int mode = *(int*)((char*)FUN_00b3d310() + 0x2c);
    ObjVec* vec = VSLOT(self, 0x44, ObjVec*(__thiscall*)(void*))(self);
    unsigned count = (unsigned)(vec->mpEnd - vec->mpBegin);
    for (unsigned i = 0; i < count; i++) {
        DrawEnt* e = (DrawEnt*)vec->mpBegin[i];
        if (e == 0)
            continue;
        if (e->m64 == 0)
            continue;
        char* p180 = e->m180;
        if (p180 == 0)
            continue;
        void* q = *(void**)(p180 + 0x64);
        if (q == 0)
            continue;
        void* r = VSLOT(q, 0xc, void*(__thiscall*)(void*, void*))(q, (void*)0x1186577);
        if (r == 0)
            continue;
        if (*(u8*)((char*)r + 0x75) == 0)
            continue;

        if (mode == 0) {
            if (dt > 0.0f && FUN_004885d0(&e->m20) > 1.5258789e-05f) {
                *(u8*)((char*)r + 0x77) = 0;
                void* c = FUN_00b33e40(r);
                if (c != 0) {
                    float inv = 1.0f / dt;
                    float v[3];
                    v[0] = -(e->m20 * inv);
                    v[1] = -(e->m24 * inv);
                    v[2] =  (e->m28 * inv);
                    void* obj = VSLOT(r, 0x30, void*(__thiscall*)(void*))(r);
                    float out[3];
                    FUN_0059aed0(out, v, obj);
                    ((void (__thiscall*)(void*, float*, int))FUN_00c446d0)(c, out, 1);
                    *(int*)((char*)c + 0x1f0) = 3;
                }
            }
        } else if (mode == 1) {
            VSLOT(r, 0x38, void(__thiscall*)(void*, void*))(r, &e->m4);
            float qv[4] = { e->m10, e->m14, e->m18, e->m1c };
            void* a = FUN_00b33e60(r);
            void* b = FUN_00ae66f0(r);
            if (b != 0 || (a != 0 && *(int*)((char*)a + 0xd04) != 0)) {
                float q0 = qv[0];
                qv[0] = qv[1];
                qv[1] = -q0;
                float q2 = qv[2];
                qv[2] = qv[3];
                qv[3] = -q2;
            }
            VSLOT(r, 0x3c, void(__thiscall*)(void*, float*))(r, qv);
        }
    }
}
