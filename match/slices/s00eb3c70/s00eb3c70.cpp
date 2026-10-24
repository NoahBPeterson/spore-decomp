// Slice s00eb3c70: Spore object state / mode-transition routines.  These four functions
// used to be naked __asm/_emit transcriptions (not allowed); below are the decompiled
// bodies.  Behaviour follows the original instruction stream; the switch in FUN_00eb3c70
// dispatches on a mode (0..4) and each arm rewrites the cached orientation/bounds block,
// the new mode always landing in +0x14.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Constants the originals load out of read-only .rdata, spelled inline with the address
// they came from:
//   0x01485720 = 1.0f (_HK_REAL_ONE)   0x0148866c = 0.15f   0x01488670 = 0.0225f
//   0x01473c70 = 10.0f                 0x013eb1bc = -1.0f
#include "types.h"

#define F4(p, off) (*(float*)((char*)(p) + (off)))
#define U4(p, off) (*(unsigned*)((char*)(p) + (off)))
#define U1(p, off) (*(unsigned char*)((char*)(p) + (off)))

// The CRT math entry points are declared here rather than pulled in through <math.h>
// (the slice uses no other part of it); /O2 intrinsifies both, and float<->double
// conversions are exact, so the values are unchanged.
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl sqrt(double);
#define ABSF(x) ((float)fabs(x))

// --- callees ----------------------------------------------------------------
void* __cdecl FUN_00472b80(void* dst, const void* src, float w);   // 0x00472b80

// __thiscall-shaped externals: the sub-object travels in ecx.  They are declared on a
// dummy holder because cl rejects __thiscall on free functions (C3865); declarations
// only, never defined here.
struct ExtEB {
    void ClearSpine(void);             // 0x00eb2eb0
    void ClearM(void);                 // 0x0069d090
    void ClearV(void);                 // 0x0069d100
    void ClearQ(void);                 // 0x0069d150
    void RectInit(const float* src);   // 0x00572600
};

typedef void (__thiscall *FnThisVoid)(void*);

// --- globals the initialisers copy in ---------------------------------------
extern int DAT_015a940c;   // 0x015a940c
extern int DAT_015a9410;   // 0x015a9410
extern int DAT_015a9414;   // 0x015a9414
extern int DAT_015a9424;   // 0x015a9424
extern int DAT_015a9428;   // 0x015a9428
extern int DAT_015a942c;   // 0x015a942c
extern int DAT_016c7290;   // 0x016c7290
extern int DAT_016c7294;   // 0x016c7294
extern int DAT_016c7298;   // 0x016c7298
extern int DAT_016c729c;   // 0x016c729c

// The mode setter is __thiscall(int): `this` in ecx, the mode on the stack.
struct ObjEB3C70 {
    void FUN_00eb3c70(int mode);       // 0x00eb3c70
};

// @ 0x00eb3c70  ObjEB3C70::FUN_00eb3c70
__declspec(noinline) void ObjEB3C70::FUN_00eb3c70(int mode)
{
    char* p = (char*)this;

    switch (mode)
    {
    case 0:
        if (U4(p, 0x14) != 0)
            F4(p, 0xF0) = 0.0f;
        F4(p, 0xEC) = F4(p, 0xF0);
        {
            float tmp[4];
            FUN_00472b80(tmp, p + 0x188, 0.0f);
            unsigned* q = (unsigned*)tmp;      // copied as dwords: leaves the SSE file alone
            U4(p, 0x140) = q[0];
            U4(p, 0x144) = q[1];
            U4(p, 0x148) = q[2];
            U4(p, 0x14C) = q[3];
        }
        F4(p, 0x130) = F4(p, 0x140);
        F4(p, 0x134) = F4(p, 0x144);
        F4(p, 0x138) = F4(p, 0x148);
        F4(p, 0x13C) = F4(p, 0x14C);
        break;

    case 1:
        F4(p, 0xEC) = F4(p, 0xF0);              // +0x2c <- +0x30 was copied above the fold
        F4(p, 0x2C) = F4(p, 0x30);
        F4(p, 0x18) = F4(p, 0x1C);
        F4(p, 0x6C) = F4(p, 0x54);
        F4(p, 0x70) = F4(p, 0x58);
        F4(p, 0x74) = F4(p, 0x5C);
        F4(p, 0x130) = F4(p, 0x140);
        F4(p, 0x134) = F4(p, 0x144);
        F4(p, 0x138) = F4(p, 0x148);
        F4(p, 0x13C) = F4(p, 0x14C);
        U4(p, 0xA4) = U4(p, 0x8C);
        U4(p, 0xA8) = U4(p, 0x90);
        U4(p, 0xAC) = U4(p, 0x94);
        F4(p, 0xF8) = 0.0f;
        F4(p, 0x38) = 0.0f;
        F4(p, 0x24) = 0.0f;
        F4(p, 0x160) = 0.0f;
        F4(p, 0xB4) = 0.0f;
        F4(p, 0xD0) = 0.0f;
        F4(p, 0x7C) = 0.0f;
        break;

    case 2:
        U4(p, 0x54) = U4(p, 0x178);             // axis = reference axis
        U4(p, 0x6C) = U4(p, 0x178);
        U4(p, 0x58) = U4(p, 0x17C);
        U4(p, 0x70) = U4(p, 0x17C);
        U4(p, 0x5C) = U4(p, 0x180);
        U4(p, 0x74) = U4(p, 0x180);
        F4(p, 0xF0) = 0.0f;
        F4(p, 0xEC) = 0.0f;
        F4(p, 0xF8) = 0.0f;
        F4(p, 0x30) = 0.0f;
        F4(p, 0x34) = 0.0f;
        F4(p, 0x2C) = 0.0f;
        F4(p, 0x38) = 0.0f;
        F4(p, 0x1C) = 0.0f;
        F4(p, 0x20) = 0.0f;
        F4(p, 0x18) = 0.0f;
        F4(p, 0x24) = 0.0f;
        F4(p, 0x44) = 0.0f;
        F4(p, 0x48) = 0.0f;
        F4(p, 0x40) = 0.0f;
        F4(p, 0x4C) = 0.0f;
        F4(p, 0x7C) = 0.0f;
        F4(p, 0x130) = F4(p, 0x140);
        F4(p, 0x134) = F4(p, 0x144);
        F4(p, 0x138) = F4(p, 0x148);
        F4(p, 0x13C) = F4(p, 0x14C);
        F4(p, 0x160) = 0.0f;
        {
            // The original evaluates this in x87 (fld/fmul/fadd/fsqrt); 0x007F control word
            // means every step rounds to single, so keeping it in x87 reproduces it bit for bit.
            double x = F4(p, 0x54);
            double y = F4(p, 0x58);
            double z = F4(p, 0x5C);
            F4(p, 0x1AC) = (float)sqrt((x * x + y * y) + z * z);
        }
        break;

    case 3:
        U4(p, 0x6C) = U4(p, 0x54);
        U4(p, 0x70) = U4(p, 0x58);
        U4(p, 0x74) = U4(p, 0x5C);
        F4(p, 0x7C) = 0.0f;
        break;

    case 4:
        if (U4(p, 0x14) == 0)
        {
            U4(p, 0x54) = U4(p, 0x178);
            U4(p, 0x6C) = U4(p, 0x178);
            U4(p, 0x58) = U4(p, 0x17C);
            U4(p, 0x70) = U4(p, 0x17C);
            F4(p, 0xF0) = 0.0f;
            F4(p, 0xEC) = 0.0f;
            U4(p, 0x5C) = U4(p, 0x180);
            U4(p, 0x74) = U4(p, 0x180);
        }
        else
        {
            int prev = U4(p, 0x14);
            if (prev == 2 || prev == 3)
            {
                U4(p, 0x54) = U4(p, 0x178);
                U4(p, 0x6C) = U4(p, 0x178);
                U4(p, 0x58) = U4(p, 0x17C);
                U4(p, 0x70) = U4(p, 0x17C);
                F4(p, 0xEC) = 0.0f;
                F4(p, 0xF0) = 0.0f;
                U4(p, 0x5C) = U4(p, 0x180);
                U4(p, 0x74) = U4(p, 0x180);
                F4(p, 0x4C) = 0.0f;
                F4(p, 0x40) = 0.0f;
                F4(p, 0x48) = 0.0f;
                F4(p, 0x44) = 0.0f;
                F4(p, 0x24) = 0.0f;
                F4(p, 0x18) = 0.0f;
                F4(p, 0x20) = 0.0f;
                F4(p, 0x1C) = 0.0f;
                F4(p, 0x38) = 0.0f;
                F4(p, 0x2C) = 0.0f;
                F4(p, 0x34) = 0.0f;
                F4(p, 0x30) = 0.0f;
                {
                    float tmp[4];
                    FUN_00472b80(tmp, p + 0x188, 0.0f);
                    ((ExtEB*)(p + 0x140))->RectInit(tmp);
                }
                F4(p, 0x130) = F4(p, 0x140);
                F4(p, 0x134) = F4(p, 0x144);
                F4(p, 0x138) = F4(p, 0x148);
                F4(p, 0x13C) = F4(p, 0x14C);
            }
        }
        break;
    }

    U4(p, 0x14) = (unsigned)mode;
}

// @ 0x00eb4040  FUN_00eb4040
// Tolerance test: 1 if any of the three orientation deltas exceeds 0.15f, or the
// position delta or the 54/58/5c vector difference exceeds 0.0225f (0.15^2).
__declspec(noinline) unsigned char __fastcall FUN_00eb4040(void* obj)
{
    char* p = (char*)obj;

    if (ABSF(F4(p, 0x30) - F4(p, 0x34)) > 0.15f) return 1;
    if (ABSF(F4(p, 0x1C) - F4(p, 0x20)) > 0.15f) return 1;
    if (ABSF(F4(p, 0x44) - F4(p, 0x48)) > 0.15f) return 1;
    if (ABSF(F4(p, 0xF0) - F4(p, 0xF4)) > 0.0225f) return 1;
    {
        float dx = F4(p, 0x54) - F4(p, 0x60);
        float dz = F4(p, 0x5C) - F4(p, 0x68);
        float dy = F4(p, 0x58) - F4(p, 0x64);
        if ((dz * dz + dy * dy) + dx * dx > 0.0225f) return 1;
    }
    return 0;
}

// @ 0x00eb4130  FUN_00eb4130
// Fills the 0x44-byte record at `obj` with three {0,0,0,1.0f} rows, a zero and four
// globals out of .data.
__declspec(noinline) void __fastcall FUN_00eb4130(void* obj)
{
    char* p = (char*)obj;

    U4(p, 0x00) = 0;          U4(p, 0x04) = 0;          U4(p, 0x08) = 0;
    U4(p, 0x0C) = 0x3F800000u;                                    // 0x01485720 = 1.0f
    U4(p, 0x10) = 0;          U4(p, 0x14) = 0;          U4(p, 0x18) = 0;
    U4(p, 0x1C) = 0x3F800000u;
    U4(p, 0x20) = 0;          U4(p, 0x24) = 0;          U4(p, 0x28) = 0;
    U4(p, 0x2C) = 0x3F800000u;
    U4(p, 0x30) = 0;
    U4(p, 0x34) = (unsigned)DAT_016c7290;
    U4(p, 0x38) = (unsigned)DAT_016c7294;
    U4(p, 0x3C) = (unsigned)DAT_016c7298;
    U4(p, 0x40) = (unsigned)DAT_016c729c;
}

// @ 0x00eb41f0  FUN_00eb41f0
// Big default-state initialiser: field block, two spine clears, three spline clears
// and a virtual tail call when +0x10 is set.
__declspec(noinline) void __fastcall FUN_00eb41f0(void* obj)
{
    char* p = (char*)obj;

    F4(p, 0x104) = -1.0f;                                  // 0x013eb1bc = -1.0f
    F4(p, 0x100) = -1.0f;
    F4(p, 0x10C) = 0.0f;
    U1(p, 0x10A) = 0;
    U1(p, 0x108) = 0;

    F4(p, 0x1C) = 0.0f;   F4(p, 0x20) = 0.0f;   F4(p, 0x18) = 0.0f;
    F4(p, 0x24) = 0.0f;   F4(p, 0x28) = 0.0f;   F4(p, 0x30) = 0.0f;
    F4(p, 0x34) = 0.0f;   F4(p, 0x2C) = 0.0f;   F4(p, 0x38) = 0.0f;
    F4(p, 0x3C) = 0.0f;   F4(p, 0x44) = 0.0f;   F4(p, 0x48) = 0.0f;
    F4(p, 0x40) = 0.0f;   F4(p, 0x4C) = 0.0f;   F4(p, 0x50) = 0.0f;

    F4(p, 0xE4) = 0.0f;   F4(p, 0xE8) = 0.0f;
    F4(p, 0xE0) = -1.0f;  F4(p, 0xDC) = -1.0f;  F4(p, 0xD8) = -1.0f;

    ((ExtEB*)(p + 0x54))->ClearSpine();                    // 0x00eb2eb0
    ((ExtEB*)(p + 0x8C))->ClearSpine();

    F4(p, 0xC8) = 0.0f;   F4(p, 0xCC) = 0.0f;   F4(p, 0xC4) = 0.0f;
    F4(p, 0xD0) = 0.0f;   F4(p, 0xD4) = 0.0f;   F4(p, 0xF8) = 0.0f;
    F4(p, 0xFC) = 0.0f;

    F4(p, 0xF0) = 10.0f;                                   // 0x01473c70 = 10.0f
    F4(p, 0xF4) = 10.0f;
    F4(p, 0xEC) = 10.0f;

    FUN_00eb4130(p + 0x130);

    U4(p, 0x114) = 0;
    U4(p, 0x110) = 1000;
    U4(p, 0x118) = (unsigned)DAT_015a940c;
    U4(p, 0x11C) = (unsigned)DAT_015a9410;
    U4(p, 0x120) = (unsigned)DAT_015a9414;
    U4(p, 0x124) = (unsigned)DAT_015a9424;
    U4(p, 0x128) = (unsigned)DAT_015a9428;
    U4(p, 0x12C) = (unsigned)DAT_015a942c;
    U4(p, 0x2DC) = 0;
    U4(p, 0x2E0) = 0;
    U4(p, 0x2E4) = 0;

    ((ExtEB*)(p + 0x2A0))->ClearV();                       // 0x0069d100
    U4(p, 0x14) = 4;
    ((ExtEB*)(p + 0x1B0))->ClearM();                       // 0x0069d090
    ((ExtEB*)(p + 0x228))->ClearV();
    ((ExtEB*)(p + 0x1EC))->ClearM();
    ((ExtEB*)(p + 0x264))->ClearQ();                       // 0x0069d150

    if (U4(p, 0x10) != 0)
    {
        void** vt = *(void***)p;
        ((FnThisVoid)vt[0x50 / 4])(p);
    }
}