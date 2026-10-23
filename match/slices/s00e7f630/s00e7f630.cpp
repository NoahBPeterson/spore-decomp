// Slice s00e7f630 -- SPGonzago/SPCellGame.obj (cell stage):
//   0x00e7f630  SP::cGalaxyGameEntryImpl::HandleMessage  (message dispatcher switch)
//   0x00e7f9b0  SP::sShutdownGame
//   0x00e7fc00  SP::cCellMode::Deactivate
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
//
// All three routines call SP::sDoEnd (0x00e7e130).  In the original object sDoEnd is a same-TU
// static helper whose subject pointer cl hands over in EDI; recompiled as an ordinary function
// the subject travels on the stack, so the call sites cannot be byte-identical in isolation.
#include "types.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

// ---------------------------------------------------------------- raw offset accessors
#define I(p,o) (*(int*)((char*)(p) + (o)))
#define U(p,o) (*(uint32*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))
#define P(p,o) (*(void**)((char*)(p) + (o)))

// ---------------------------------------------------------------- globals
extern char* gspCellGame;      // 0x016b3c04
extern char* gspCellGameMode;  // 0x016b3c0c

// Copy source/destination globals of cCellMode::Deactivate.
extern float g_16b3be0, g_16b3be4, g_16b3be8, g_16b3bec, g_16b3bf0;
extern int   g_16b3bf4, g_16b3bf8, g_16b3bfc;
extern float g_1550adc, g_1550ae0, g_1550ae4, g_1550aec, g_1550af0;
extern int   g_1550a84, g_1550ad8, g_166c004;

// ---------------------------------------------------------------- container vocabulary
// Several of the callees are __thiscall members; declaring them as members keeps the original
// `this`-in-ECX protocol.
struct Container {                       // a generic Eastl-ish holder
    void Destroy();                      // 0x00b720e0
};
struct Tree {                            // red-black tree head
    void Nuke(void* node);               // 0x009a9600
};
struct Vec {
    void Erase(void* begin, void* end);  // 0x00d018d0
};
struct Manager {                         // the +0x54 runtime object registry
    void* GetObj(int id);                // 0x00b721d0
    void* Next(int* cursor);             // 0x00b72230
    int   GetPriority();                 // 0x00e31100
    void  Destroy();                     // 0x00b720e0
    void  Reset();                       // 0x00b72110
};
struct RefObj  { char Check(); };        // 0x00e18c70
struct RefObj2 { char Check(); };        // 0x00e393b0

static Manager* manager()      { return (Manager*)(gspCellGame + 0x54); }
static Manager* otherManager() { return (Manager*)(gspCellGame + 0x38); }

// ---------------------------------------------------------------- callees
void* FUN_00b3d3f0(int a);              // 0x00b3d3f0
void* FUN_00b3d410(void);               // 0x00b3d410
int   FUN_00e61320(int a);              // 0x00e61320
char  FUN_00e82da0(void);               // 0x00e82da0  (thunk of FUN_00809970)
char  FUN_00e00ac0(void);               // 0x00e00ac0
char  FUN_00e50f30(void);               // 0x00e50f30
char  FUN_00e82cc0(void);               // 0x00e82cc0
char  FUN_00e82cd0(void);               // 0x00e82cd0
void  FUN_00e53860(int a);              // 0x00e53860
void  FUN_00e538b0(int a);              // 0x00e538b0
void  FUN_00e53920(void);               // 0x00e53920
void  FUN_00e53950(int a);              // 0x00e53950
void  FUN_00e53660(int a, int b);       // 0x00e53660
void  FUN_00e02200(void);               // 0x00e02200  (SP::ShowContextSensitiveSporeGuide)
void  FUN_00e7f5a0(void);               // 0x00e7f5a0
void  FUN_00e76320(void);               // 0x00e76320
void  FUN_00e4dc80(void* p);            // 0x00e4dc80  (operator delete)
void  FUN_00bbb0d0(void* p);            // 0x00bbb0d0
void  FUN_00e86ae0(void);               // 0x00e86ae0
void  FUN_00e53580(void);               // 0x00e53580
void  FUN_00e64a00(void);               // 0x00e64a00
void  FUN_00e82d40(void);               // 0x00e82d40
void  FUN_00e75c20(void);               // 0x00e75c20

void  sDoEnd(void* self, float dt, int a2, int a3);   // 0x00e7e130  (self in EDI in original)

void* MessageServer(void);              // 0x0067dcc0
void* EffectsManager(void);             // 0x0067ddd0

// ---------------------------------------------------------------- virtual dispatch
typedef void (__thiscall *Vfn1)(void*);
typedef void (__thiscall *Vfn2)(void*, int);
typedef void (__thiscall *Vfn2i)(void*, int, int);
typedef void (__thiscall *Vfn3)(void*, int, int, int);
#define VTBL(o) (*(void***)(o))

// ================================================================ 0x00e7f630
// @ 0x00e7f630  SP::cGalaxyGameEntryImpl::HandleMessage(int msg, uint32 flags)
char FUN_00e7f630(int msg, uint32 flags)
{
    if (flags & 0x40)
        return 0;

    switch (msg) {
    case 8:
        if (!FUN_00e82da0() && !FUN_00e50f30())
            FUN_00e76320();
        break;

    case 0x1b:
        FUN_00e7f5a0();
        return 1;

    case 0x31:
    case 0x32:
        return (char)FUN_00e61320(msg - 0x31);

    case 0x42:
        if (FUN_00e82cc0()) {
            void** ms = (void**)MessageServer();
            ((Vfn3)VTBL(ms)[5])(ms, 0x574f0a6, 0, 0);
            return 1;
        }
        if (!FUN_00e82da0() && !FUN_00e00ac0() && !FUN_00e50f30()) {
            FUN_00e538b0(1);
            return 1;
        }
        break;

    case 0x48:
    case 0xbf:
        if (flags == 0) {
            if (msg != 0x48 && msg != 0xbf)
                return 1;
        } else {
            if (flags != 1)
                return 1;
            if (msg != 0xbf)
                return 1;
        }
        if (FUN_00e82cd0()) {
            void** ms = (void**)MessageServer();
            ((Vfn3)VTBL(ms)[5])(ms, 0x5b9ba6c, 0, 0);
            return 1;
        }
        if (!FUN_00e82da0() && !FUN_00e00ac0() && !FUN_00e50f30()) {
            if (!FUN_00e00ac0())
                FUN_00e53660(2, 1);
            FUN_00e02200();
            return 1;
        }
        break;

    case 0x4c:
        if (((RefObj*)FUN_00b3d3f0(0))->Check() ||
            (!FUN_00e82da0() && !FUN_00e50f30())) {
            char c = ((RefObj*)FUN_00b3d3f0(0))->Check();
            FUN_00e53860(c == 0);
            return 1;
        }
        break;

    case 0x50:
    case 0xc0:
        if (!FUN_00e82da0() && !FUN_00e00ac0() && !FUN_00e50f30()) {
            FUN_00e53920();
            return 1;
        }
        break;

    case 0x53:
        if (flags == 2 && B(gspCellGameMode, 0x937) == 0 &&
            !FUN_00e50f30() && !FUN_00e00ac0()) {
            void** ms = (void**)MessageServer();
            ((Vfn3)VTBL(ms)[5])(ms, 0x1cd20f0, 0, 0);
            return 1;
        }
        break;

    case 0x54:
        if (!((RefObj2*)FUN_00b3d410())->Check() &&
            !FUN_00e82da0() && !FUN_00e00ac0() && !FUN_00e50f30()) {
            FUN_00e53950(1);
            return 1;
        }
        break;

    default:
        return 0;
    }
    return 1;
}

// ================================================================ 0x00e7f9b0
// @ 0x00e7f9b0  SP::sShutdownGame
void FUN_00e7f9b0(void)
{
    I(gspCellGame, 0x411c) = 0;

    void* p = P(gspCellGame, 0);
    if (p != 0) {
        P(gspCellGame, 0) = 0;
        ((Vfn1)VTBL(p)[1])(p);
    }
    FUN_00e4dc80(P(gspCellGame, 0x4108));

    // tear down the red-black tree rooted at +0x5170
    ((Tree*)(gspCellGame + 0x5170))->Nuke(P(gspCellGame, 0x517c));
    void** head = (void**)(gspCellGame + 0x5170);
    head[1] = (char*)head + 4;
    head[2] = (char*)head + 4;
    head[3] = 0;
    B(gspCellGame, 0x5180) = 0;
    I(gspCellGame, 0x5184) = 0;

    ((Container*)(gspCellGame + 0xa8))->Destroy();
    ((Container*)(gspCellGame + 0xc4))->Destroy();
    ((Vec*)(gspCellGame + 0xe0))->Erase(P(gspCellGame, 0xe0), P(gspCellGame, 0xe4));

    // tear down the red-black tree rooted at +0x70
    ((Tree*)(gspCellGame + 0x70))->Nuke(P(gspCellGame, 0x7c));
    head = (void**)(gspCellGame + 0x70);
    head[1] = (char*)head + 4;
    head[2] = (char*)head + 4;
    head[3] = 0;
    B(gspCellGame, 0x80) = 0;
    I(gspCellGame, 0x84) = 0;

    ((Container*)(gspCellGame + 0x8c))->Destroy();

    // retire every live cell object
    int h = manager()->GetPriority();
    for (void* o = manager()->Next(&h); o != 0; o = manager()->Next(&h))
        sDoEnd(o, 0.0f, 0, 1);
    manager()->Destroy();

    // retire the layout/world objects
    int h2 = otherManager()->GetPriority();
    for (void* it = otherManager()->Next(&h2); it != 0; it = otherManager()->Next(&h2)) {
        void* q = P(it, 0x300);
        if (q != 0) {
            ((Vfn2)VTBL(q)[3])(q, 1);
            P(it, 0x300) = 0;
            ((Vfn1)VTBL(q)[1])(q);
        }
    }
    otherManager()->Destroy();
    ((Container*)(gspCellGame + 0x1c))->Destroy();

    ((Vec*)(gspCellGame + 0x4128))->Erase(P(gspCellGame, 0x4128), P(gspCellGame, 0x412c));
    FUN_00bbb0d0(P(gspCellGame, 0x4104));
    FUN_00e86ae0();

    void** ms = (void**)MessageServer();
    ((Vfn3)VTBL(ms)[0x30 / 4])(ms, (int)FUN_00e75c20, 0x4471c60, (int)0xffffd8f1);

    p = P(gspCellGame, 0x5164);
    if (p != 0) {
        P(gspCellGame, 0x5164) = 0;
        ((Vfn1)VTBL(p)[1])(p);
    }
}

// ================================================================ 0x00e7fc00
// @ 0x00e7fc00  SP::cCellMode::Deactivate
void FUN_00e7fc00(void)
{
    FUN_00e53580();

    g_1550adc = g_16b3bf0;
    g_1550af0 = g_16b3bec;
    g_1550a84 = g_16b3bf8;
    g_1550aec = g_16b3be8;
    g_1550ae0 = g_16b3be4;
    g_166c004 = g_16b3bfc;
    g_1550ad8 = g_16b3bf4;
    g_1550ae4 = g_16b3be0;

    int h = manager()->GetPriority();
    for (void* o = manager()->Next(&h); o != 0; o = manager()->Next(&h))
        sDoEnd(o, 0.0f, 0, 1);

    manager()->Reset();

    void** em = (void**)EffectsManager();
    ((Vfn2i)VTBL(em)[0x98 / 4])(em, 7, 0);

    FUN_00e64a00();
    FUN_00e82d40();
}
