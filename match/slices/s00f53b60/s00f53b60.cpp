// slice s00f53b60 -- `anonymous_namespace'::cCloudSourceCommand family
// ("cloud source" arg-script commands: shape/offsets, speed/dir, delay/strength/turn,
//  count/start/random, height range, ...).  All 10 functions are __thiscall, take one
//  EA::ArgScript::cArguments* and finish with `ret 4`.
//
//   0x00f53b60  cCloudSourceCommand::Execute(cArguments*)          (1243 bytes)
//   0x00f54040  cCloudSourceCommand::Speed(cArguments*)            ( 583 bytes)
//   0x00f54290  cCloudSourceCommand::Delay(cArguments*)            ( 524 bytes)
//   0x00f544d0  cCloudSourceCommand::Duration(cArguments*)         ( 225 bytes)
//   0x00f545c0  cCloudSourceCommand::SetCount(cArguments*)         ( 161 bytes)
//   0x00f54670  cCloudSourceCommand::Tile(cArguments*)             ( 290 bytes)
//   0x00f547a0  cCloudSourceCommand::Material(cArguments*)         ( 223 bytes)
//   0x00f54880  cCloudSourceCommand::Count(cArguments*)            ( 194 bytes)
//   0x00f54980  cCloudSourceCommand::HeightRange(cArguments*)      ( 293 bytes)
//   0x00f54ab0  cCloudSourceCommand::SetHeightRange(cArguments*)   (  50 bytes)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// Layout reconstructed from the disassembly: this+0x04 is the argument parser object
// (its vftable slots 0x98/0xa0/0xa4/0xa8 parse a float / bool / Vec2 / Vec3 out of a
// string) and this+0x0c is the destination parameter block (a bitfield of "set" flags
// at +0x10 and a pile of float/byte parameters).
#include "types.h"
#include <math.h>

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// argument-parser object (*(this+4)): virtual slot helpers.
//   +0x98  float  ParseFloat(const char* s)
//   +0xa0  bool   ParseBool (const char* s)
//   +0xa4  void   ParseVec2 (void* out, const char* s)
//   +0xa8  void*  ParseVec3 (void* out, const char* s)   (returns out)
// ---------------------------------------------------------------------------
typedef float (__thiscall *FN_FLOAT)(void* self, const char* s);
typedef char  (__thiscall *FN_BOOL) (void* self, const char* s);
typedef void  (__thiscall *FN_VEC2) (void* self, void* out, const char* s);
typedef void* (__thiscall *FN_VEC3) (void* self, void* out, const char* s);

static __forceinline FN_FLOAT SlotFloat(void* p) { return *(FN_FLOAT*)((char*)(*(void**)p) + 0x98); }
static __forceinline FN_BOOL  SlotBool (void* p) { return *(FN_BOOL *)((char*)(*(void**)p) + 0xa0); }
static __forceinline FN_VEC2  SlotVec2 (void* p) { return *(FN_VEC2 *)((char*)(*(void**)p) + 0xa4); }
static __forceinline FN_VEC3  SlotVec3 (void* p) { return *(FN_VEC3 *)((char*)(*(void**)p) + 0xa8); }

static __forceinline float ParseFloat(void* p, const char* s)             { return SlotFloat(p)(p, s); }
static __forceinline char  ParseBool (void* p, const char* s)             { return SlotBool (p)(p, s); }
static __forceinline void  ParseVec2 (void* p, void* out, const char* s)  { SlotVec2(p)(p, out, s); }
static __forceinline void* ParseVec3 (void* p, void* out, const char* s)  { return SlotVec3(p)(p, out, s); }

// ---------------------------------------------------------------------------
// EA::ArgScript::cArguments
// ---------------------------------------------------------------------------
namespace EA { namespace ArgScript {
class cArguments { public:
    const char** MainArguments(int n);                                      // 0x838320
    const char** MainArguments(int* pCount, int lo, int hi);                // 0x838020
    bool         HasFlag(const char* name);                                 // 0x8380b0
    const char** OptionArguments(const char* name, int n);                  // 0x838330
    const char** OptionArguments(const char* name, int* pCount, int lo, int hi); // 0x838130
};

float ParseRangedFloat(void* parser, const char* s, float lo, float hi);    // 0x840d50
}}  // namespace EA::ArgScript

namespace EA { namespace Swarm {
class cEffectsParser { public:
    // 0xa6ed80
    void ParseDrawInfoOptions(EA::ArgScript::cArguments* args, void* parser, void* out);
};
}}  // namespace EA::Swarm

// eastl::vector<Vector3, sp_vector_allocator> living at params+0x270 -------------
struct DrawInfoVector {
    long long resize(int n, const char* value);                             // 0xa6ec40
    long long FUN_00a6e600(const char* name);                               // 0xa6e600
};

// ---- free helpers (cdecl) -------------------------------------------------
void  __cdecl FUN_006e9910(float radius);                                   // 0x6e9910
void  __cdecl FUN_00a93c60(void* v);                                        // 0xa93c60

struct Vec3Helper { void FUN_00a9a1c0(float a, float b, float c); };        // 0xa9a1c0

// ---- module globals -------------------------------------------------------
struct CVec3 { float x, y, z; };
extern CVec3 g_cloudDir;            // 0x016c9234 (unit x/y/z triple)
extern float g_fUnset;              // 0x015b0be8 (sentinel compared against +-x)
extern float g_fEpsilon;            // 0x013ec4b8 (added before sqrt, ~1e-8)
extern float g_fHalf;               // 0x01471064 (0.5f)

using namespace EA::ArgScript;

// ---------------------------------------------------------------------------
// 0x00f53b60  cCloudSourceCommand::Execute(cArguments*)
//   shape selectors (point/square/quad/cube/box/circle/sphere/ellipse/ellipsoid/
//   ring/torus), an offset vector, then two flags.
// ---------------------------------------------------------------------------
struct cCloudSourceCommand {
    void* mVtbl;      // +0x00
    void* mParser;    // +0x04
    void* m08;        // +0x08
    void* mParams;    // +0x0c

    void Execute(cArguments* args);            // 0x00f53b60
    void Speed(cArguments* args);              // 0x00f54040
    void Delay(cArguments* args);              // 0x00f54290
    void Duration(cArguments* args);           // 0x00f544d0
    void SetCount(cArguments* args);           // 0x00f545c0
    void Tile(cArguments* args);               // 0x00f54670
    void Material(cArguments* args);           // 0x00f547a0
    void Count(cArguments* args);              // 0x00f54880
    void HeightRange(cArguments* args);        // 0x00f54980
    void SetHeightRange(cArguments* args);     // 0x00f54ab0
};

// ---------------------------------------------------------------------------
// @ 0x00f53b60  cCloudSourceCommand::Execute(cArguments*)
void cCloudSourceCommand::Execute(cArguments* args)
{
    float vout[3];          // shared Vec2/Vec3 parse buffer
    float lo0, lo1, lo2;    // inclusive bounds
    float hi0, hi1, hi2;    // exclusive bounds
    const char** a;

    args->MainArguments(0);
    lo0 = g_cloudDir.x;
    lo1 = g_cloudDir.y;
    lo2 = g_cloudDir.z;
    hi0 = lo0;
    hi1 = lo1;
    hi2 = lo2;
    *(u32*)((char*)mParams + 0x10) &= ~0x10u;

    if (args->HasFlag("point")) goto done;

    a = args->OptionArguments("square", 1);
    if (a) {
        float d = ParseFloat(mParser, a[0]);
        if (lo0 != g_fUnset && lo0 != -g_fUnset) {
            lo0 -= d; lo1 -= d; lo2 = lo2; hi0 += d; hi1 += d; hi2 = hi2;
        }
        goto done;
    }
    a = args->OptionArguments("quad", 1);
    if (a) {
        ParseVec2(mParser, vout, a[0]);
        if (lo0 != g_fUnset && lo0 != -g_fUnset) {
            lo0 -= vout[0]; lo1 -= vout[1]; lo2 = lo2; hi0 += vout[0]; hi1 += vout[1]; hi2 = hi2;
        }
        goto done;
    }
    a = args->OptionArguments("cube", 1);
    if (a) { FUN_006e9910(ParseFloat(mParser, a[0])); goto done; }

    a = args->OptionArguments("box", 1);
    if (a == 0) {
        a = args->OptionArguments("circle", 1);
        if (a) {
            *(u32*)((char*)mParams + 0x10) |= 0x10u;
            float r = ParseFloat(mParser, a[0]);
            ((Vec3Helper*)vout)->FUN_00a9a1c0(r, r, 0.0f);
            goto done;
        }
        a = args->OptionArguments("sphere", 1);
        if (a) {
            *(u32*)((char*)mParams + 0x10) |= 0x10u;
            FUN_006e9910(ParseFloat(mParser, a[0]));
            goto done;
        }
        a = args->OptionArguments("ellipse", 1);
        if (a) { ellipseBox: *(u32*)((char*)mParams + 0x10) |= 0x10u; goto parseBox; }
        a = args->OptionArguments("ellipsoid", 1);
        if (a) goto ellipseBox;

        a = args->OptionArguments("ring", 2);
        if (a) {
            float r = ParseFloat(mParser, a[0]);
            *(float*)((char*)mParams + 0x68) = ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
            ((Vec3Helper*)vout)->FUN_00a9a1c0(r, r, 0.0f);
            goto done;
        }
        a = args->OptionArguments("torus", 2);
        if (a) {
            ParseVec3(mParser, vout, a[0]);
            *(float*)((char*)mParams + 0x68) = ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
            goto offset;
        }
        goto done;
    }
parseBox:
    ParseVec3(mParser, vout, a[0]);
offset:
    FUN_00a93c60(vout);

done:
    a = args->OptionArguments("offset", 1);
    if (a) {
        float* p = (float*)ParseVec3(mParser, vout, a[0]);
        if (lo0 != g_fUnset && lo0 != -g_fUnset) {
            hi0 = p[0] + hi0;
            lo0 = p[0] + lo0;
            lo1 = p[1] + lo1;
            hi1 = p[1] + hi1;
            lo2 = p[2] + lo2;
            hi2 = p[2] + hi2;
        }
    }
    *(float*)((char*)mParams + 0x5c) = hi0;
    *(float*)((char*)mParams + 0x60) = hi1;
    *(float*)((char*)mParams + 0x64) = hi2;
    *(float*)((char*)mParams + 0x50) = lo0;
    *(float*)((char*)mParams + 0x54) = lo1;
    *(float*)((char*)mParams + 0x58) = lo2;
    if (args->HasFlag("scaleCloud"))    *(u32*)((char*)mParams + 0x10) |= 0x800u;
    if (args->HasFlag("resetIncoming")) *(u32*)((char*)mParams + 0x10) |= 0x4000000u;
}

// ---------------------------------------------------------------------------
// @ 0x00f54040  cCloudSourceCommand::Speed(cArguments*)
//   "speed <a> [b]" -> [a-b, a+b]; "dir <v> [base]" -> normalized basis vectors.
// ---------------------------------------------------------------------------
void cCloudSourceCommand::Speed(cArguments* args)
{
    float fdir[3];
    float tmp[3];
    int   n;
    args->MainArguments(0);
    const char** a = args->OptionArguments("speed", &n, 1, 0x7fffffff);
    if (a) {
        float v = ParseFloat(mParser, a[0]);
        float b = 0.0f;
        if (n > 1) b = ParseFloat(mParser, a[1]);
        *(float*)((char*)mParams + 0x48) = v - b;
        *(float*)((char*)mParams + 0x4c) = b + v;
    }
    a = args->OptionArguments("dir", &n, 1, 2);
    if (a) {
        ParseVec3(mParser, fdir, a[0]);
        float bx = g_cloudDir.x, by = g_cloudDir.y, bz = g_cloudDir.z;
        if (n > 1) {
            float* p = (float*)ParseVec3(mParser, tmp, a[1]);
            bx = p[0]; by = p[1]; bz = p[2];
        }
        float inv = 1.0f / sqrtf((float)(fdir[0] * fdir[0] + fdir[1] * fdir[1]
                                  + fdir[2] * fdir[2] + g_fEpsilon));
        float ux = fdir[0] * inv;
        float uy = fdir[1] * inv;
        float uz = fdir[2] * inv;
        *(float*)((char*)mParams + 0x30) = ux;
        *(float*)((char*)mParams + 0x3c) = ux;
        *(float*)((char*)mParams + 0x34) = uy;
        *(float*)((char*)mParams + 0x40) = uy;
        *(float*)((char*)mParams + 0x38) = uz;
        *(float*)((char*)mParams + 0x44) = uz;
        if (ux != g_fUnset && ux != -g_fUnset) {
            *(float*)((char*)mParams + 0x30) = ux - bx;
            *(float*)((char*)mParams + 0x34) = uy - by;
            *(float*)((char*)mParams + 0x38) = uz - bz;
            *(float*)((char*)mParams + 0x3c) = ux + bx;
            *(float*)((char*)mParams + 0x40) = uy + by;
            *(float*)((char*)mParams + 0x44) = uz + bz;
        }
    }
    if (args->HasFlag("base"))          *(u32*)((char*)mParams + 0x10) |= 0x8u;
    if (args->HasFlag("scaleExisting")) *(u32*)((char*)mParams + 0x10) |= 0x2000000u;
}

// ---------------------------------------------------------------------------
// @ 0x00f54290  cCloudSourceCommand::Delay(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::Delay(cArguments* args)
{
    int n;
    args->MainArguments(0);
    *(u32*)((char*)mParams + 0x10) |= 0x80000u;

    const char** a = args->OptionArguments("delay", &n, 1, 2);
    if (a) {
        float v = ParseFloat(mParser, a[0]);
        float b = 0.0f;
        if (n > 1) b = ParseFloat(mParser, a[1]);
        *(float*)((char*)mParams + 0x200) = v - b;
        *(float*)((char*)mParams + 0x204) = v + b;
    }
    a = args->OptionArguments("strength", &n, 1, 2);
    if (a) {
        float v = ParseFloat(mParser, a[0]);
        float b = 0.0f;
        if (n > 1) b = ParseFloat(mParser, a[1]);
        *(float*)((char*)mParams + 0x208) = v - b;
        *(float*)((char*)mParams + 0x20c) = v + b;
    }
    a = args->OptionArguments("turn", &n, 1, 0x7fffffff);
    if (a) {
        *(float*)((char*)mParams + 0x210) = ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);
        if (n < 2) *(u32*)((char*)mParams + 0x214) = 0;
        else       *(float*)((char*)mParams + 0x214) = ParseRangedFloat(mParser, a[1], 0.0f, 1.0f);
    }
    a = args->OptionArguments("mix", 1);
    if (a) *(float*)((char*)mParams + 0x218) = ParseRangedFloat(mParser, a[0], 0.0f, 1.0f);

    if (args->HasFlag("wait")) *(u32*)((char*)mParams + 0x10) |= 0x100000u;
}

// ---------------------------------------------------------------------------
// @ 0x00f544d0  cCloudSourceCommand::Duration(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::Duration(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 1, 0x7fffffff);
    float b = 0.0f;
    float v = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, a[0]);
    if (n > 1) b = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, a[1]);
    *(float*)((char*)mParams + 0x14) = v - b;
    *(float*)((char*)mParams + 0x18) = v + b;

    const char** p = args->OptionArguments("preroll", 1);
    if (p) {
        *(float*)((char*)mParams + 0x1c) =
            (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
        return;
    }
    *(float*)((char*)mParams + 0x1c) = v > 0.5f ? v : 0.5f;
}

// ---------------------------------------------------------------------------
// @ 0x00f545c0  cCloudSourceCommand::SetCount(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::SetCount(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 1);
    if (n > 0) {
        *(long long*)((char*)mParams + 0x110) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(1, a[0]);
    }
    *(u8*)((char*)mParams + 0x119) = 0x0f;
    const char** p = args->OptionArguments("overrideSet", 1);
    if (p) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x131) = fn(mParser, p[0]);
    }
    else *(u8*)((char*)mParams + 0x131) = 0;
    ((EA::Swarm::cEffectsParser*)*(void**)((char*)mParams + 0x270))
        ->ParseDrawInfoOptions(args, mParser, (char*)mParams + 0x110);
}

// ---------------------------------------------------------------------------
// @ 0x00f54670  cCloudSourceCommand::Tile(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::Tile(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 1);
    if (n > 0) {
        *(long long*)((char*)mParams + 0x110) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(0, a[0]);
    }
    const char** t = args->OptionArguments("tile", &n, 1, 2);
    if (t) {
        *(u8*)((char*)mParams + 0x132) =
            (*(FN_BOOL*)((char*)(*(void**)mParser) + 0xa0))(mParser, t[0]);
        if (n > 1)
            *(u8*)((char*)mParams + 0x133) =
                (*(FN_BOOL*)((char*)(*(void**)mParser) + 0xa0))(mParser, t[1]);
        else *(u8*)((char*)mParams + 0x133) = 1;
    }
    ((EA::Swarm::cEffectsParser*)*(void**)((char*)mParams + 0x270))
        ->ParseDrawInfoOptions(args, mParser, (char*)mParams + 0x110);
    const char** p = args->OptionArguments("overrideSet", 1);
    if (p) {
        *(u8*)((char*)mParams + 0x131) =
            (*(FN_BOOL*)((char*)(*(void**)mParser) + 0xa0))(mParser, p[0]);
    }
    else   *(u8*)((char*)mParams + 0x131) = 0;
    if (args->HasFlag("acceptComposite")) *(u32*)((char*)mParams + 0x10) |= 0x400000u;
    else                                  *(u32*)((char*)mParams + 0x10) &= 0xffbfffffu;
}

// ---------------------------------------------------------------------------
// @ 0x00f547a0  cCloudSourceCommand::Material(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::Material(cArguments* args)
{
    int n;
    const char** a = args->MainArguments(&n, 0, 1);
    if (n > 0) {
        *(long long*)((char*)mParams + 0x110) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(2, a[0]);
    }
    *(u32*)((char*)mParams + 0x10) |= 0x200000u;
    const char** m = args->OptionArguments("material", 1);
    if (m) {
        *(long long*)((char*)mParams + 0x128) =
            ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->resize(1, m[0]);
        *(u8*)((char*)mParams + 0x119) = 0x0f;
    }
    const char** p = args->OptionArguments("overrideSet", 1);
    if (p) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x131) = fn(mParser, p[0]);
    }
    else *(u8*)((char*)mParams + 0x131) = 0;
    ((EA::Swarm::cEffectsParser*)*(void**)((char*)mParams + 0x270))
        ->ParseDrawInfoOptions(args, mParser, (char*)mParams + 0x110);
}
// ---------------------------------------------------------------------------
// @ 0x00f54880  cCloudSourceCommand::Count(cArguments*)
void cCloudSourceCommand::Count(cArguments* args)
{
    args->MainArguments(0);
    if (const char** a = args->OptionArguments("speed", 1))
        *(float*)((char*)mParams + 0x138) =
            (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, a[0]);
    if (const char** a = args->OptionArguments("count", 1)) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x136) = fn(mParser, a[0]);
    }
    if (const char** a = args->OptionArguments("start", 1)) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x135) = fn(mParser, a[0]);
    }
    if (const char** a = args->OptionArguments("random", 1)) {
        FN_BOOL fn = SlotBool(mParser);
        *(u8*)((char*)mParams + 0x137) = fn(mParser, a[0]);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00f54980  cCloudSourceCommand::HeightRange(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::HeightRange(cArguments* args)
{
    const char** a = args->MainArguments(1);
    *(long long*)((char*)mParams + 0x1f0) =
        ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->FUN_00a6e600(a[0]);

    if (args->HasFlag("pinToSurface")) *(u32*)((char*)mParams + 0x10) |= 0x20u;

    const char** p = args->OptionArguments("belowHeight", 1);
    if (p) {
        *(u32*)((char*)mParams + 0x10) |= 0x40u;
        float* d = (float*)((char*)mParams + 0x1e4);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
    }
    p = args->OptionArguments("aboveHeight", 1);
    if (p) {
        *(u32*)((char*)mParams + 0x10) |= 0x40u;
        float* d = (float*)((char*)mParams + 0x1e0);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
    }
    p = args->OptionArguments("heightRange", 2);
    if (p) {
        *(u32*)((char*)mParams + 0x10) |= 0x40u;
        float* d = (float*)((char*)mParams + 0x1e0);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[0]);
        d = (float*)((char*)mParams + 0x1e4);
        *d = (*(FN_FLOAT*)((char*)(*(void**)mParser) + 0x98))(mParser, p[1]);
    }
    if (args->HasFlag("density")) *(u32*)((char*)mParams + 0x10) |= 0x80u;
}

// ---------------------------------------------------------------------------
// @ 0x00f54ab0  cCloudSourceCommand::SetHeightRange(cArguments*)
// ---------------------------------------------------------------------------
void cCloudSourceCommand::SetHeightRange(cArguments* args)
{
    const char** a = args->MainArguments(1);
    *(long long*)((char*)mParams + 0x1f8) =
        ((DrawInfoVector*)*(void**)((char*)mParams + 0x270))->FUN_00a6e600(a[0]);
}
