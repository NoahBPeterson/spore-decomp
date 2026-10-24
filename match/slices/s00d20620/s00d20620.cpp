// Slice s00d20620: 0x00D20620..0x00D20F00.
//  0x00d20620  float ramp / smoothstep interpolation       (216 B)
//  0x00d20700  dual-band clamped interpolation              (372 B)
//  0x00d20880  setter: two v3/v4 pairs + flag               (140 B)
//  0x00d20910  store float into four fields                 ( 41 B)
//  0x00d20950  clamped index store                          ( 18 B)
//  0x00d20970  mode / creature-strategy classifier          ( 64 B)
//  0x00d209b0  camera blend against a target point          (691 B)
//  0x00d20c70  orbit damping tick                           (505 B)
//  0x00d20e70  property-flag query                          (133 B)
//  0x00d20f00  camera focus update                          (1186 B)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- shared types

struct tVec3 { float x, y, z; };
struct tVec4 { float x, y, z, w; };

typedef long double float10;

// Camera / mission-control object shared by the methods in this slice.
struct tCamCtrl {
    char  pad_00[0x1c];
    float m1c;                 // +0x1c
    float m20;                 // +0x20
    float m24;                 // +0x24
    char  pad_28[0x48 - 0x28];
    float m48;                 // +0x48
    float m4c;                 // +0x4c
    float m50;                 // +0x50
    float m54;                 // +0x54
    float m58;                 // +0x58
    float m5c;                 // +0x5c
    char  pad_60[0x94 - 0x60];
    float m94;                 // +0x94
    float m98;                 // +0x98
    float m9c;                 // +0x9c
    float ma0;                 // +0xa0
    float ma4;                 // +0xa4
    float ma8;                 // +0xa8
    char  pad_ac[0x100 - 0xac];
    float m100;                // +0x100
    char  pad_104[0x108 - 0x104];
    float m108;                // +0x108
    float m10c;                // +0x10c
    float m110;                // +0x110
    float m114;                // +0x114
    float m118;                // +0x118
    float m11c;                // +0x11c
    char  pad_120[0x12c - 0x120];
    float m12c;                // +0x12c
    float m130;                // +0x130
    float m134;                // +0x134
    float m138;                // +0x138
    float m13c;                // +0x13c
    float m140;                // +0x140
    float m144;                // +0x144
    char  pad_148[0x17c - 0x148];
    float m17c;                // +0x17c
    char  pad_180[0x188 - 0x180];
    float m188;                // +0x188
    char  pad_18c[0x194 - 0x18c];
    float m194;                // +0x194
    char  pad_198[0x1ac - 0x198];
    tVec3 m1ac;                // +0x1ac
    tVec4 m1b8;                // +0x1b8
    tVec3 m1c8;                // +0x1c8
    tVec4 m1d4;                // +0x1d4
    char  pad_1e4[0x1e8 - 0x1e4];
    unsigned m1e8;             // +0x1e8
    char  pad_1ec[0x210 - 0x1ec];
    float m210;                // +0x210
    float m214;                // +0x214
    char  pad_218[0x258 - 0x218];
    float m258;                // +0x258
    float m25c;                // +0x25c
    char  pad_260[0x298 - 0x260];
    unsigned char m298;        // +0x298

    float10 FUN_00d20620(float p);                       // 0x00d20620
    void   FUN_00d20880(const tVec3& a, const tVec4& b); // 0x00d20880
    void   FUN_00d20910(float f);                       // 0x00d20910
    void   FUN_00d20950(unsigned n);                    // 0x00d20950
};

// ---------------------------------------------------------------- externs

void* __cdecl GetCurrentGameMode(void);          // 0x00b5b800  SP::GetCurrentGameMode
void* __cdecl CreatureModeStrategy_Instance(void); // 0x00d38840  SP::cCreatureModeStrategy::Instance

// Object pointed at by +0x54 of the mode managers probed by FUN_00d20970.
struct cModeTarget {
    char          pad_00[0x54];
    unsigned char m54;    // +0x54
};

struct cCreatureModeStrategy {
    char         pad_00[0x64];
    cModeTarget* m64;     // +0x64
};

struct cGlobalMgr {
    char         pad_00[0x68];
    cModeTarget* m68;     // +0x68
};

// ---------------------------------------------------------------- 0x00d20620

// @ 0x00d20620
float10 tCamCtrl::FUN_00d20620(float p)
{
    float lo = m210;
    if (p < lo)
        return *(float*)0x01582854;
    float hi = m214;
    if (hi < p)
        return *(float*)0x01582860;
    if (p <= lo)
        p = lo;
    if (hi <= p)
        p = hi;
    float t = (p - lo) / (hi - lo);
    float r = (((3.0f - t * 2.0f) * t) * t) * (*(float*)0x01582860 - *(float*)0x01582854)
              + *(float*)0x01582854;
    return r;
}

// ---------------------------------------------------------------- 0x00d20700

// @ 0x00d20700
void FUN_00d20700(void) {}

// ---------------------------------------------------------------- 0x00d20880

// @ 0x00d20880
void tCamCtrl::FUN_00d20880(const tVec3& a, const tVec4& b)
{
    m1ac = a;
    m1c8 = a;
    m1b8 = b;
    m1d4 = b;
    m298 = 1;
}

// ---------------------------------------------------------------- 0x00d20910

// @ 0x00d20910
void tCamCtrl::FUN_00d20910(float f)
{
    m17c = f;
    m100 = f;
    m188 = f;
    m194 = f;
}

// ---------------------------------------------------------------- 0x00d20950

// @ 0x00d20950
void tCamCtrl::FUN_00d20950(unsigned n)
{
    if (n <= 7)
        m1e8 = n;
}

// ---------------------------------------------------------------- 0x00d20970

// @ 0x00d20970
unsigned char FUN_00d20970(void)
{
    unsigned char r = 0;
    if (GetCurrentGameMode() == (void*)0x01654c05)
        return 1;
    if (static_cast<cCreatureModeStrategy*>(CreatureModeStrategy_Instance())->m64 != 0)
        return static_cast<cCreatureModeStrategy*>(CreatureModeStrategy_Instance())->m64->m54;
    cGlobalMgr* g = *(cGlobalMgr**)0x016c7aa4;
    cModeTarget* t = g->m68;
    if (t == 0)
        return r;
    return t->m54;
}

// ---------------------------------------------------------------- 0x00d209b0

// @ 0x00d209b0
void FUN_00d209b0(void) {}

// ---------------------------------------------------------------- 0x00d20c70

// @ 0x00d20c70
void FUN_00d20c70(void) {}

// ---------------------------------------------------------------- 0x00d20e70

// @ 0x00d20e70
void FUN_00d20e70(void) {}

// ---------------------------------------------------------------- 0x00d20f00

// @ 0x00d20f00
void FUN_00d20f00(void) {}