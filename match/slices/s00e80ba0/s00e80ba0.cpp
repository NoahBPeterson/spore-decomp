// Slice s00e80ba0 -- SPGonzago/SPCellGame.obj (cell stage):
//   0x00e80ba0  cell-stage (re)initialisation routine (SP::sInitCell-adjacent)
//   0x00e81120  EA::Locale::LocaleFormatter::ParseFormat  (game-message -> locale dispatch)
//   0x00e818f0  EA::Locale::SetTimeString-adjacent message router
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
//
// All three routines are large optimised dispatchers that inline heavily and hand helper
// subjects over in dedicated registers in the original object (e.g. sDoEnd's subject in EDI,
// the ParseFormat jump-table helpers), so single-function recompilation is not expected to be
// byte-identical.
#include "types.h"

typedef unsigned char  uint8;
typedef unsigned short uint16;
typedef unsigned int   uint32;

// ---------------------------------------------------------------- raw offset accessors
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- globals
extern char* gspCellGame;      // 0x016b3c04  the cell-game singleton
extern char* gspCellGfx;       // 0x016b3c08  the cell-gfx singleton
extern char* gspCellGameMode;  // 0x016b3c0c  the active cell-mode object
extern void* g_16b3de0;        // 0x016b3de0  current play-mode object
extern int   g_16b3c14;        // 0x016b3c14

// cell-game bounding box, stored as two Vec3 corners at 0x016b3c88
extern float g_bbMinX, g_bbMinY, g_bbMinZ;   // 0x016b3c88 / 8c / 90
extern float g_bbMaxX, g_bbMaxY, g_bbMaxZ;   // 0x016b3c94 / 98 / 9c

extern float gCellCenterX, gCellCenterY, gCellCenterZ;   // 0x015a7d3c / 40 / 44
extern float gCamOfsX, gCamOfsY, gCamOfsZ;               // 0x015a7c28 / 2c / 30
extern int   g_150d6d8;                                  // 0x0150d6d8

// ---------------------------------------------------------------- container vocabulary
struct Manager {                       // thiscall container (base passed in ECX)
    void  Init(int a, int b);          // 0x00b72080
    void  Destroy();                   // 0x00b720e0
};
struct ObjRegistry {                   // object registry rooted at gspCellGame+0x1c
    void* GetObj(int id);              // 0x00b721d0
};
struct cSPUILayout {
    void SetVisibility(int show);      // 0x00810590
};
struct CollectableItems {
    CollectableItems* Create();        // 0x00597e00  (ctor on raw storage)
    void Init(int a, int b, int c);    // 0x00599440
};

// ---------------------------------------------------------------- callees
void* MessageServer(void);             // 0x0067dcc0
void  FUN_00e75c20(void);              // 0x00e75c20
void  FUN_00e86ad0(void);              // 0x00e86ad0
void* FUN_00e86a50(void);              // 0x00e86a50  SphereTreeCreate
void* FUN_00bbb400(int a, int b);      // 0x00bbbe00  (thunk of FUN_00bbb400)
void* FUN_00e61630(void);              // 0x00e61630
void  FUN_00e5d500(void* p);           // 0x00e5d500
void  FUN_00e52c00(void);              // 0x00e52c00
void  FUN_00743b50(void* self);        // 0x00743b50  ctor on a stack temporary
void* FUN_00e4ce40(void* self);        // 0x00e4ce40
void  FUN_00e5f360(void);              // 0x00e5f360
void* FUN_00e4ecc0(void);              // 0x00e4ecc0
void  FUN_00e7fd00(int, int, int, int, char, int, int);   // 0x00e7fd00
void  FUN_00e4fac0(void* p);           // 0x00e4fac0
double FUN_00e52b70(void);             // 0x00e52b70
void  FUN_00e82130(void* self);        // 0x00e82130
void* operator_new(unsigned size, const char* name, int, int, int, int);  // 0x00f473a0
void* operator_new2(void* p, int, int);                                   // 0x011e073e
int   FUN_00b3d400(void);              // 0x00b3d400
void* FUN_00b3d400b(int a);            // 0x00b3d400 (overload)
void  FUN_00e14c10(void* self, int a); // 0x00e14c10

// ---- ParseFormat / SetTimeString callees
char  FUN_00b1fbf0(void);              // 0x00b1fbf0
char  FUN_00e82760(void);              // 0x00e82760
char  FUN_00e50f30(void);              // 0x00e50f30
void  FUN_00e50f60(int a);             // 0x00e50f60
void  FUN_00e7d070(int a, float f);    // 0x00e7d070
void  FUN_00e7ce10(int a, int b);      // 0x00e7ce10
void  FUN_00e629a0(void);              // 0x00e629a0
void  FUN_00e5da10(void);              // 0x00e5da10
void  FUN_00e61140(void);              // 0x00e61140
void  FUN_00e72c80(void);              // 0x00e72c80
void  FUN_00e82d30(void);              // 0x00e82d30
void  FUN_00e59800(int a);             // 0x00e59800
void  FUN_00e82d10(int a);             // 0x00e82d10
void  FUN_00e675f0(void);              // 0x00e675f0
void  FUN_00e7a4a0(void*, int, int, int, int, float);     // 0x00e7a4a0
int   FUN_00e4ee60(void);              // 0x00e4ee60  SP::sGetSourceLevel
int   FUN_00e4cce0(int, int, float, float, int, int, int); // 0x00e4cce0
void  FUN_00e53250(void);              // 0x00e53250
char  FUN_00e52b40(int a);             // 0x00e52b40
void  FUN_00e5d7b0(int a);             // 0x00e5d7b0
void  FUN_00e80660(int a);             // 0x00e80660  SP::sDeathFromBeingEaten_End
void  FUN_00e6e8c0(int a);             // 0x00e6e8c0
void  FUN_00e79720(void);              // 0x00e79720  SP::sCinematicGoldy_Start
void  FUN_00e53580(void);              // 0x00e53580
void  FUN_00e63d10(void* p);           // 0x00e63d10
void  FUN_00e4fcd0(void* p);           // 0x00e4fcd0
void  FUN_00e3c760(void);              // 0x00e3c760
void  FUN_00e394f0(float f, void* self, void*, void*, void*);   // 0x00e394f0
void  FUN_00e64a00(void);              // 0x00e64a00
void  FUN_00e7f9b0(void);              // 0x00e7f9b0
void  FUN_00e66980(void);              // 0x00e66980
void  FUN_00e548d0(void);              // 0x00e548d0
void  FUN_00e54270(int a);             // 0x00e54270
void  FUN_00e5dba0(void);              // 0x00e5dba0  SP::sInitGfx
void  FUN_00e55120(void);              // 0x00e55120  SP::sActivateGfx
char  FUN_00e7f630(int msg, uint32 flags);   // 0x00e7f630
char  FUN_00e82cc0(void);              // 0x00e82cc0
char  FUN_00e82900(int msg, uint32 flags);   // 0x00e82900

void  FUN_00e78b20(Vec3* self, int obj, float f);   // 0x00e78b20  (thiscall; self = out vector)
void  FUN_00e74a20(void* tree, Vec3* p, float f, int a, int b, float g, int c, int d, int e, int g2);

struct LocaleMode {
    char RouteMessage(int msg, uint32 flags);   // 0x00697a50  (member of gspCellGameMode)
};

// ---------------------------------------------------------------- virtual dispatch
typedef void (__thiscall *Vfn0)(void*);
typedef void (__thiscall *Vfn4)(void*, void*, int, int, int);
#define VTBL(o) (*(void***)(o))

// ================================================================ 0x00e80ba0
// @ 0x00e80ba0  cell-stage re-initialisation
void FUN_00e80ba0(void)
{
    void* ms = MessageServer();
    ((Vfn0)VTBL(ms)[0x38 / 4])(ms);

    ms = MessageServer();
    ((Vfn4)VTBL(ms)[0x28 / 4])(ms, (void*)FUN_00e75c20, 0, 0x4471c60, 0);

    I(gspCellGame, 0x5194) = 0;
    I(gspCellGame, 0x5198) = 0;
    B(gspCellGame, 0x5168) = 0;
    B(gspCellGame, 0x5169) = 0;
    I(gspCellGame, 0x515c) = 0;
    I(gspCellGame, 0x5160) = 0;
    I(gspCellGame, 0x516c) = 0;

    FUN_00e86ad0();
    P(gspCellGame, 0x40fc) = FUN_00e86a50();
    P(gspCellGame, 0x4100) = FUN_00e86a50();
    P(gspCellGame, 0x4104) = FUN_00bbb400(0x1000, 0x1000);

    B(gspCellGame, 0x5148) = 0;
    F(gspCellGame, 0x514c) = 0.5f;
    I(gspCellGame, 0x5154) = 0;
    F(gspCellGame, 0x5150) = F(gspCellGame, 0x514c);
    B(gspCellGame, 0x518c) = 0;

    ((Manager*)(gspCellGame + 0x8c))->Init(0x4c, 0x800);
    ((Manager*)(gspCellGame + 0x1c))->Init(0x398, 0x1000);
    ((Manager*)(gspCellGame + 0x38))->Init(0x304, 0x200);
    ((Manager*)(gspCellGame + 0x54))->Init(0x7c, 0x200);
    ((Manager*)(gspCellGame + 0xc4))->Init(0x40, 0x800);
    ((Manager*)(gspCellGame + 0xa8))->Init(0x48, 0x200);

    void* old;
    if (g_16b3de0 == 0) {
        void* n = FUN_00e61630();
        old = P(gspCellGame, 0x5190);
        if (n != old) {
            if (n) ((Vfn0)VTBL(n)[0])(n);
            P(gspCellGame, 0x5190) = n;
            if (old) ((Vfn0)VTBL(old)[1])(old);
        }
    } else {
        old = P(gspCellGame, 0x5190);
        if (g_16b3de0 != old) {
            ((Vfn0)VTBL(g_16b3de0)[0])(g_16b3de0);
            P(gspCellGame, 0x5190) = g_16b3de0;
            if (old) ((Vfn0)VTBL(old)[1])(old);
        }
        B(gspCellGame, 0x51da) = 1;
    }
    if (g_16b3de0 != 0) {
        void* p = g_16b3de0;
        g_16b3de0 = 0;
        ((Vfn0)VTBL(p)[1])(p);
    }

    FUN_00e5d500((char*)P(gspCellGame, 0x5190) + 0x10);
    if (B(P(gspCellGame, 0x5190), 0xe9) == 0) {
        FUN_00e52c00();
        B(P(gspCellGame, 0x5190), 0xe9) = 1;
    }

    char tmp[0x1c];
    FUN_00743b50(tmp);
    void* r = FUN_00e4ce40(tmp);
    I(gspCellGame, 0x4114) = I(r, 4);
    I(gspCellGame, 0x4118) = I(r, 0x18);

    FUN_00e5f360();
    g_bbMaxX = gCellCenterX + 10.0f;
    g_bbMinX = gCellCenterX - 10.0f;
    g_bbMaxY = gCellCenterY + 7.5f;
    g_bbMinY = gCellCenterY - 7.5f;
    g_bbMinZ = gCellCenterZ + 0.0f;
    g_bbMaxZ = gCellCenterZ + 0.0f;

    P(gspCellGame, 0x4108) = FUN_00e4ecc0();

    int mode = I(gspCellGame, 0x5190);
    FUN_00e7fd00(I(mode, 0x1c), I(mode, 0x20), I(mode, 0x24), I(mode, 0x28),
                 B(gspCellGame, 0x410c), I(gspCellGame, 0x4110), I(mode, 0x1c) == 0);

    I(gspCellGame, 0x4124) = 0x14;

    CollectableItems* ci = (CollectableItems*)operator_new(0x6dac, "Simulator/cCollectableItems", 0, 0, 0, 0);
    if (ci == 0) {
        ci = 0;
    } else {
        ci = ci->Create();
    }
    ci->Init(0, 0, g_150d6d8);
    B(ci, 0xc) = 0;

    void* oldci = P(gspCellGame, 0x5164);
    if (ci != oldci) {
        ((Vfn0)VTBL(ci)[0])(ci);
        P(gspCellGame, 0x5164) = ci;
        if (oldci) ((Vfn0)VTBL(oldci)[1])(oldci);
    }

    FUN_00e4fac0((char*)P(gspCellGame, 0x5190) + 0x34);
    I(gspCellGame, 0x51b0) = 0;
    I(gspCellGame, 0x51b4) = -1;
    F(gspCellGame, 0x51b8) = 0.0f;
    F(gspCellGame, 0x51bc) = (float)FUN_00e52b70();
    B(gspCellGame, 0x51c0) = 0;
    F(gspCellGame, 0x51c4) = 0.0f;
    F(gspCellGame, 0x51c8) = 0.0f;
    F(gspCellGame, 0x51d0) = 0.0f;
    F(gspCellGame, 0x51cc) = 0.0f;
    B(gspCellGame, 0x51db) = 0;
    B(gspCellGame, 0x51dc) = 0;
    I(gspCellGame, 0x51e0) = 0;

    ((cSPUILayout*)P(gspCellGameMode, 0x90))->SetVisibility(1);

    int v = FUN_00b3d400();
    if (v != 0) {
        void* obj = FUN_00b3d400b(1);
        FUN_00e14c10(obj, 1);
    }
    FUN_00e82130((char*)gspCellGame + 0);   // this = esp temp in original
}

// ================================================================ 0x00e81120
// @ 0x00e81120  EA::Locale::LocaleFormatter::ParseFormat(int msg, uint8 flags)
char FUN_00e81120(int msg, uint8 flags)
{
    if ((flags & 0x40) != 0 || FUN_00b1fbf0() == 1 ||
        (FUN_00e82760() == 0 && (flags & 6) != 6))
        return 0;

    switch (msg) {
    case 9:
        break;   // fall through to the shared "finish" block

    case 0x20:
        B(gspCellGfx, 0x16204) = (B(gspCellGfx, 0x16204) == 0);
        return 1;

    case 0x21:
        if (FUN_00e50f30() == 0) {
            if ((flags & 1) == 0) { FUN_00e50f60(1); return 1; }
            FUN_00e7d070(3, 0.0f);
            return 1;
        }
        break;

    case 0x22:
        if ((flags & 1) == 0) FUN_00e50f60(-1);
        break;

    case 0x26:
        if (FUN_00e50f30() == 0 && (flags & 2) != 0) { FUN_00e7ce10(0x32, 1); return 1; }
        break;

    case 0x28:
        if (FUN_00e50f30() == 0 && (flags & 2) != 0) { FUN_00e7ce10(-0x32, 1); return 1; }
        break;

    case 0x30:
        if (I(P(gspCellGame, 0x5190), 0xc) == 1) { FUN_00e629a0(); return 1; }
        FUN_00e5da10();
        FUN_00e61140();
        return 1;

    case 0x31: case 0x32: case 0x33: case 0x34: case 0x35: case 0x36:
        FUN_00e80660(msg - 0x31);
        return 1;

    case 0x38:
        FUN_00e6e8c0(1);
        return 1;

    case 0x39: case 0x54:
        FUN_00e5da10();
        FUN_00e72c80();
        return 1;

    case 0x42: case 0x4d:
        if (FUN_00e50f30() == 0) {
            FUN_00e82d30();
            for (int i = 0x14; i != 0; --i) FUN_00e7d070(3, 0.0f);
            return 1;
        }
        break;

    case 0x43:
        if ((flags & 6) == 6) { FUN_00e79720(); return 1; }
        return 0;

    case 0x45:
        FUN_00e59800(1);
        return 1;

    case 0x46:
        FUN_00e82d10(0x83932384);
        FUN_00e82d10(0xde776d90);
        FUN_00e82d10(0x0d0d8ca6);
        FUN_00e82d10(0x662732af);
        FUN_00e82d10(0x345fbd9f);
        return 1;

    case 0x47:
        FUN_00e675f0();
        return 1;

    case 0x48:
        if (FUN_00e50f30() == 0) { FUN_00e7d070(3, 0.0f); return 1; }
        break;

    case 0x4a:
        B(gspCellGfx, 0x16205) = (B(gspCellGfx, 0x16205) == 0);
        return 1;

    case 0x4b: {
        int o = (int)((ObjRegistry*)(gspCellGame + 0x1c))->GetObj(I(gspCellGame, 0x411c));
        if (o != 0) { FUN_00e7a4a0((void*)o, 0, I(o, 0x108), 1, 0, 0x3c23d70a); return 1; }
        break;
    }

    case 0x51: {
        int lvl = FUN_00e4ee60();
        int which, sel;
        switch (lvl - 4) {
        case 0: which = FUN_00e4cce0(0x13, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 6;  break;
        case 1: which = FUN_00e4cce0(0x14, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 7;  break;
        case 2: which = FUN_00e4cce0(0x15, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 8;  break;
        case 3: which = FUN_00e4cce0(0x16, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 9;  break;
        case 4: which = FUN_00e4cce0(0x17, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 10; break;
        case 5: which = FUN_00e4cce0(0x19, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 11; break;
        case 6: which = FUN_00e4cce0(0x19, lvl + 1, 1.0f, 0.0f, 1, 0, 0); sel = 12; break;
        default: return 0;
        }
        int o = (int)((ObjRegistry*)(gspCellGame + 0x1c))->GetObj(I(gspCellGame, 0x411c));
        if (o == 0) return 0;
        Vec3 pos;
        pos.x = F(o, 0x4c); pos.y = F(o, 0x50); pos.z = F(o, 0x54);
        FUN_00e78b20(&pos, I(gspCellGame, 0x411c), 100.0f);
        Vec3 p2;
        p2.x = gCamOfsX * 8.0f + pos.x;
        p2.y = gCamOfsY * 8.0f + pos.y;
        p2.z = gCamOfsZ * 8.0f + pos.z;
        FUN_00e74a20(P(gspCellGame, 0x40fc), &p2, 0.0f, which, sel, 1.0f, 0, 1, 0, 0);
        return 1;
    }

    case 0x52:
        B(gspCellGame, 0x410c) = (B(gspCellGame, 0x410c) == 0);
        I(gspCellGame, 0x4110) = 0;
        break;   // fall through to the shared "finish" block

    case 0x55:
        for (int i = 2; i < 0xc; ++i)
            if (FUN_00e52b40(i) == 0) FUN_00e5d7b0(i);
        return 1;

    case 0x58: {
        int o = (int)((ObjRegistry*)(gspCellGame + 0x1c))->GetObj(I(gspCellGame, 0x411c));
        if (o == 0) return 0;
        int lvl = FUN_00e4ee60();
        Vec3 pos;
        pos.x = F(o, 0x4c); pos.y = F(o, 0x50); pos.z = F(o, 0x54);
        FUN_00e78b20(&pos, I(gspCellGame, 0x411c), 100.0f);
        Vec3 p2;
        p2.x = gCamOfsX * 8.0f + pos.x;
        p2.y = gCamOfsY * 8.0f + pos.y;
        p2.z = gCamOfsZ * 8.0f + pos.z;
        int which = FUN_00e4cce0(0x13, lvl + 1, 1.0f, 0.0f, 1, 0, 0);
        FUN_00e74a20(P(gspCellGame, 0x40fc), &p2, 0.0f, which, 0, 1.0f, 0, 1, 0, 0);
        B(gspCellGame, 0x51c0) = 1;
        FUN_00e53250();
        I(gspCellGame, 0x51b4) = 3;
        I(gspCellGame, 0x51b0) = 0;   // original carries a leftover EDX here
        F(gspCellGame, 0x51b8) = 15.0f;
        return 1;
    }

    case 0x5a: {
        int o = (int)((ObjRegistry*)(gspCellGame + 0x1c))->GetObj(I(gspCellGame, 0x411c));
        if (o != 0) {
            B(o, 0x111) = (B(o, 0x111) == 0);
            return 1;
        }
        break;
    }

    default:
        return 0;
    }

    // shared "finish": shutdown + restart the cell stage in the 9 / 0x52 cases
    FUN_00e53580();
    FUN_00e63d10(P(gspCellGame, 0x5190));
    B(g_16b3de0, 0x69) = 0;
    B(g_16b3de0, 0x68) = 0;
    FUN_00e4fcd0((char*)P(gspCellGame, 0x5190) + 0x34);
    operator_new2((char*)P(gspCellGame, 0x5190) + 0x80, 0, 0x60);
    FUN_00e3c760();

    float scratch[9] = {0};
    FUN_00e394f0(0x3e2a3040, (char*)P(gspCellGame, 0x5190) + 0x10,
                 &scratch[2], &scratch[5], &scratch[8]);

    FUN_00e64a00();
    FUN_00e7f9b0();
    FUN_00e66980();
    FUN_00e548d0();
    FUN_00e54270(0);
    FUN_00e5dba0();
    FUN_00e80ba0();
    FUN_00e55120();
    return 1;
}

// ================================================================ 0x00e818f0
// @ 0x00e818f0  EA::Locale::SetTimeString-adjacent message router (__stdcall, 2 args)
char __stdcall FUN_00e818f0(int msg, uint32 flags)
{
    if (FUN_00e82900(msg, flags) == 0) {
        if (flags == 2 && msg == 0x48)
            B(gspCellGameMode, 0x937) = (B(gspCellGameMode, 0x937) == 0);

        // thiscall member: the mode object travels in ECX
        ((struct LocaleMode*)gspCellGameMode)->RouteMessage(msg, flags);

        char both;
        if ((flags & 2) == 0 || (both = 1, (flags & 4) == 0))
            both = 0;

        char c = FUN_00e82cc0();
        if (c != 0 && msg != 0x42)
            return 0;

        if (both) {
            c = FUN_00e81120(msg, (uint8)flags);
            if (c != 1 && (c = FUN_00e7f630(msg, flags)) != 1)
                return 0;
        } else {
            c = FUN_00e7f630(msg, flags);
            if (c != 1) {
                c = FUN_00e81120(msg, (uint8)flags);
                if (c != 1)
                    return 0;
                return 1;
            }
        }
    }
    return 1;
}
