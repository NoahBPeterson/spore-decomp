// RenderWare shader constant-builder callbacks + arena resolve helpers, 0x011fab10-0x011fba34.
// Reconstructed from the retail disassembly + Ghidra decompile.
#include "types.h"
#include <intrin.h>
#include <xmmintrin.h>

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t  i32;

// ---- engine entry points (cdecl unless noted) ----
void __cdecl D3DXMatrixTranspose(void* out, const void* m);      // 0x11e1fec
void __cdecl D3DXMatrixMultiply(void* out, const void* a, const void* b); // 0x11e1ff2
int  __cdecl Arena_ObjectToId(void* arena, u32 obj);          // 0x11e3c30
int  __cdecl Arena_IdToObject(void* arena, u32 id);           // 0x11e2300
struct Arena {
    int ObjectToId(u32 obj);   // 0x11e3c30 (__thiscall)
    int IdToObject(u32 id);    // 0x11e2300 (__thiscall)
};
long long __cdecl allrem(long long num, long long den);          // 0x11e0d60
extern "C" void __stdcall QueryPerformanceFrequency(void* f);     // kernel32 IAT
extern "C" void __stdcall QueryPerformanceCounter(void* c);       // kernel32 IAT

struct Matrix44 { float m[16]; };
struct Vector4f { float x, y, z, w; };
struct Matrix33 { float m[9]; };

struct IDirect3DDevice9 {
    virtual long __stdcall slot0() { return 0; }
    virtual long __stdcall slot1() { return 0; }
    virtual long __stdcall slot2() { return 0; }
    virtual long __stdcall slot3() { return 0; }
    virtual long __stdcall slot4() { return 0; }
    virtual long __stdcall slot5() { return 0; }
    virtual long __stdcall slot6() { return 0; }
    virtual long __stdcall slot7() { return 0; }
    virtual long __stdcall slot8() { return 0; }
    virtual long __stdcall slot9() { return 0; }
    virtual long __stdcall slot10() { return 0; }
    virtual long __stdcall slot11() { return 0; }
    virtual long __stdcall slot12() { return 0; }
    virtual long __stdcall slot13() { return 0; }
    virtual long __stdcall slot14() { return 0; }
    virtual long __stdcall slot15() { return 0; }
    virtual long __stdcall slot16() { return 0; }
    virtual long __stdcall slot17() { return 0; }
    virtual long __stdcall slot18() { return 0; }
    virtual long __stdcall slot19() { return 0; }
    virtual long __stdcall slot20() { return 0; }
    virtual long __stdcall slot21() { return 0; }
    virtual long __stdcall slot22() { return 0; }
    virtual long __stdcall slot23() { return 0; }
    virtual long __stdcall slot24() { return 0; }
    virtual long __stdcall slot25() { return 0; }
    virtual long __stdcall slot26() { return 0; }
    virtual long __stdcall slot27() { return 0; }
    virtual long __stdcall slot28() { return 0; }
    virtual long __stdcall slot29() { return 0; }
    virtual long __stdcall slot30() { return 0; }
    virtual long __stdcall slot31() { return 0; }
    virtual long __stdcall slot32() { return 0; }
    virtual long __stdcall slot33() { return 0; }
    virtual long __stdcall slot34() { return 0; }
    virtual long __stdcall slot35() { return 0; }
    virtual long __stdcall slot36() { return 0; }
    virtual long __stdcall slot37() { return 0; }
    virtual long __stdcall slot38() { return 0; }
    virtual long __stdcall slot39() { return 0; }
    virtual long __stdcall slot40() { return 0; }
    virtual long __stdcall slot41() { return 0; }
    virtual long __stdcall slot42() { return 0; }
    virtual long __stdcall slot43() { return 0; }
    virtual long __stdcall slot44() { return 0; }
    virtual long __stdcall slot45() { return 0; }
    virtual long __stdcall slot46() { return 0; }
    virtual long __stdcall slot47() { return 0; }
    virtual long __stdcall slot48() { return 0; }
    virtual long __stdcall slot49() { return 0; }
    virtual long __stdcall slot50() { return 0; }
    virtual long __stdcall slot51() { return 0; }
    virtual long __stdcall slot52() { return 0; }
    virtual long __stdcall slot53() { return 0; }
    virtual long __stdcall slot54() { return 0; }
    virtual long __stdcall slot55() { return 0; }
    virtual long __stdcall slot56() { return 0; }
    virtual long __stdcall slot57() { return 0; }
    virtual long __stdcall slot58() { return 0; }
    virtual long __stdcall slot59() { return 0; }
    virtual long __stdcall slot60() { return 0; }
    virtual long __stdcall slot61() { return 0; }
    virtual long __stdcall slot62() { return 0; }
    virtual long __stdcall slot63() { return 0; }
    virtual long __stdcall slot64() { return 0; }
    virtual long __stdcall slot65() { return 0; }
    virtual long __stdcall slot66() { return 0; }
    virtual long __stdcall slot67() { return 0; }
    virtual long __stdcall slot68() { return 0; }
    virtual long __stdcall slot69() { return 0; }
    virtual long __stdcall slot70() { return 0; }
    virtual long __stdcall slot71() { return 0; }
    virtual long __stdcall slot72() { return 0; }
    virtual long __stdcall slot73() { return 0; }
    virtual long __stdcall slot74() { return 0; }
    virtual long __stdcall slot75() { return 0; }
    virtual long __stdcall slot76() { return 0; }
    virtual long __stdcall slot77() { return 0; }
    virtual long __stdcall slot78() { return 0; }
    virtual long __stdcall slot79() { return 0; }
    virtual long __stdcall slot80() { return 0; }
    virtual long __stdcall slot81() { return 0; }
    virtual long __stdcall slot82() { return 0; }
    virtual long __stdcall slot83() { return 0; }
    virtual long __stdcall slot84() { return 0; }
    virtual long __stdcall slot85() { return 0; }
    virtual long __stdcall slot86() { return 0; }
    virtual long __stdcall slot87() { return 0; }
    virtual long __stdcall slot88() { return 0; }
    virtual long __stdcall slot89() { return 0; }
    virtual long __stdcall slot90() { return 0; }
    virtual long __stdcall slot91() { return 0; }
    virtual long __stdcall slot92() { return 0; }
    virtual long __stdcall slot93() { return 0; }
    virtual long __stdcall SetVertexShaderConstantF(unsigned reg, const void* data, unsigned count) { return 0; }
    virtual long __stdcall slot95() { return 0; }
    virtual long __stdcall slot96() { return 0; }
    virtual long __stdcall slot97() { return 0; }
    virtual long __stdcall slot98() { return 0; }
    virtual long __stdcall slot99() { return 0; }
    virtual long __stdcall slot100() { return 0; }
    virtual long __stdcall slot101() { return 0; }
    virtual long __stdcall slot102() { return 0; }
    virtual long __stdcall slot103() { return 0; }
    virtual long __stdcall slot104() { return 0; }
    virtual long __stdcall slot105() { return 0; }
    virtual long __stdcall slot106() { return 0; }
    virtual long __stdcall slot107() { return 0; }
    virtual long __stdcall slot108() { return 0; }
    virtual long __stdcall SetPixelShaderConstantF(unsigned reg, const void* data, unsigned count) { return 0; }
};

extern IDirect3DDevice9* g_d3dDeviceP; // 0x16f89d0
struct __declspec(align(16)) Vec4 { union { __m128 m; struct { float x, y, z, w; }; }; };
struct __declspec(align(16)) Mat4 { Vec4 r[4]; };
struct Light { u32 type; float range; u32 pad[2]; Vec4 dir; Vec4 color; Vec4 pos; };
extern Mat4* g_worldMat; // 0x16fa5b8
extern Light* g_activeLights[8]; // 0x16f656c


// ---- globals ----
extern Matrix44 g_projMatrix;          // 0x16f90d0
extern u32 g_softState;                // 0x16f9110
extern void* g_lights[8];              // 0x16f656c
extern int g_fogType; extern float g_fogStart; extern float g_fogEnd; // 0x16f90c0 / 0x16f5c54 / 0x16f8d00
extern Vec4 g_colorActive;             // 0x16f6590
extern Vec4 g_ambientActive;           // 0x16f5c40
extern Vec4 g_timeActive;              // 0x16f9168
extern u32  g_viewportWidth;           // 0x16f91a4
extern Matrix44 g_16f8b10;             // 0x16f8b10
extern long long g_timeSinceStart; // 0x16f9128

#define DEV_SET(a, p, n) do { IDirect3DDevice9* _d = g_d3dDeviceP; if (c != 0) _d->SetVertexShaderConstantF((a), (p), (n)); else _d->SetPixelShaderConstantF((a), (p), (n)); } while (0)

extern const float kZero; // 0x1485378
extern const float kOne;  // 0x1485720
extern const float kTwo32; // 0x13f4fd0 (2^32, unsigned fixup)
extern const float kFltMax; // 0x14f811c
extern const float kLog2e; // 0x14f8144
extern const float kNegOne; // 0x13eb1bc
extern const float kSqrt2; // 0x141e714
struct __declspec(align(16)) Vec4v : Vec4 {
    Vec4v(float a, float b, float c_, float d) { x = a; y = b; z = c_; w = d; }
};
struct __declspec(align(16)) Vec4c : Vec4 {
    Vec4c(const float& a, const float& b, const float& c_, const float& d) { x = a; y = b; z = c_; w = d; }
};

static const Light* FirstLight(u32 &i0)
{
    u32 i = 0;
    if (g_activeLights[0] == 0) {
        do { ++i; } while (g_activeLights[i] == 0);
        if (i >= 8) return 0;
    }
    return g_activeLights[i];
}

// @ 0x011fab10
void __cdecl SetWorldViewProjT(u32 a, u32 b, int c)
{
    Mat4 local;
    D3DXMatrixTranspose(&local, &g_projMatrix);
    DEV_SET(a, &local, b);
}

// @ 0x011fab60
void __cdecl SetWorldViewProj(u32 a, u32 b, int c)
{
    DEV_SET(a, &g_projMatrix, b);
}

// @ 0x011fab90
void __cdecl SetLightPos(u32 a, u32 b, int c)
{
    Vec4 v;
    u32 dummy;
    const Light* l = FirstLight(dummy);
    __m128 r;
    if (l && l->type != 0 && l->type != 4) r = l->pos.m;
    else { Vec4v z(0.0f, 0.0f, 0.0f, 0.0f); r = z.m; }
    v.m = r;
    DEV_SET(a, &v, 1);
}

// @ 0x011fac30
void __cdecl SetLightColor(u32 a, u32 b, int c)
{
    Vec4 v;
    u32 dummy;
    const Light* l = FirstLight(dummy);
    if (l && l->type != 1 && l->type != 3) { v = l->color; v.w = 0.0f; }
    else { v.x = 0.0f; v.y = 0.0f; v.z = 0.0f; v.w = 0.0f; }
    DEV_SET(a, &v, 1);
}

// @ 0x011face0
void __cdecl SetLightDir2(u32 a, u32 b, int c)
{
    Vec4 v;
    u32 dummy;
    const Light* l = FirstLight(dummy);
    if (l) v = l->dir;
    else { v.x = 0.0f; v.y = 0.0f; v.z = 0.0f; v.w = 0.0f; }
    DEV_SET(a, &v, 1);
}

// @ 0x011fad70
void __cdecl SetLightRange(u32 a, u32 b, int c)
{
    u32 dummy;
    Vec4c t(kZero, kZero, kZero, kOne);
    Vec4 v = t;
    const Light* l = FirstLight(dummy);
    float r;
    if (l && l->type != 0 && l->type != 4) r = l->range;
    else r = kFltMax;
    v.z = r;
    DEV_SET(a, &v, 1);
}

// @ 0x011fae40
void __cdecl SetWorldMatrixRow3(u32 a, u32 b, int c)
{
    Mat4 m = *g_worldMat;
    DEV_SET(a, &m.r[3], 1);
}

// @ 0x011faea0
void __cdecl SetWorldMatrixRows23(u32 a, u32 b, int c)
{
    Mat4 m = *g_worldMat;
    DEV_SET(a, &m.r[2], 1);
}

// @ 0x011faf00
void __cdecl SetMaterialColor(u32 a, u32 b, int c)
{
    DEV_SET(a, &g_colorActive, 1);
}

// @ 0x011faf30
void __cdecl SetAmbientColor(u32 a, u32 b, int c)
{
    DEV_SET(a, &g_ambientActive, 1);
}

// @ 0x011faf60
void __cdecl SetTime(u32 a, u32 b, int c)
{
    DEV_SET(a, &g_timeActive, 1);
}

// @ 0x011faf90
void __cdecl SetPointSize(u32 a, u32 b, int c)
{
    float f = (float)g_viewportWidth;
    if ((int)g_viewportWidth < 0) f += kTwo32;
    f *= kSqrt2;
    Vec4c t(f, kZero, kZero, kOne);
    Vec4 v = t;
    DEV_SET(a, &v, 1);
}

// @ 0x011fb030
void __cdecl SetTimeSeconds(u32 a, u32 b, int c)
{
    long long freq, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&now);
    now -= g_timeSinceStart;
    float f = (float)((double)now / (double)freq);
    Vec4c t(f, kZero, kZero, kOne);
    Vec4 v = t;
    DEV_SET(a, &v, 1);
}

// @ 0x011fb0f0
void __cdecl SetTimeMod(u32 a, u32 b, int c)
{
    long long freq, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&now);
    now -= g_timeSinceStart;
    now = allrem(now, freq);
    float f = (float)((double)now / (double)freq);
    Vec4c t(f, kZero, kZero, kOne);
    Vec4 v = t;
    DEV_SET(a, &v, 1);
}

// @ 0x011fb1c0
void __cdecl ResolveTwo(u32 p, void* arenaHolder)
{
    void* arena = *(void**)((char*)arenaHolder + 0x1c);
    arena = *(void**)((char*)arena + 0x78);
    void* self = (void*)p;
    *(u32*)((char*)self + 0xc) = ((Arena*)arena)->ObjectToId(*(u32*)((char*)self + 0xc));
    *(u32*)((char*)self + 0x10) = ((Arena*)arena)->ObjectToId(*(u32*)((char*)self + 0x10));
}

// @ 0x011fb1f0
void __cdecl UnresolveTwo(u32 p, void* arenaHolder)
{
    void* arena = *(void**)((char*)arenaHolder + 0x78);
    void* self = (void*)p;
    *(u32*)((char*)self + 0xc) = ((Arena*)arena)->IdToObject(*(u32*)((char*)self + 0xc));
    *(u32*)((char*)self + 0x10) = ((Arena*)arena)->IdToObject(*(u32*)((char*)self + 0x10));
}

// @ 0x011fb220
void __cdecl NoOp() {}

// @ 0x011fb230
void __cdecl CalcLightRange(Vec4* v)
{
    if (g_fogType > 0) {
        Vec4 t = *v;
        if (g_fogType < 3) {
            t.x = g_fogStart * kLog2e;
            t.y = 0.0f;
        } else if (g_fogType == 3) {
            t.x = kNegOne / (g_fogEnd - g_fogStart);
            *v = t;
            t.y = g_fogEnd / (g_fogEnd - g_fogStart);
        } else goto tail;
        *v = t;
    }
tail:
    Vec4 u = *v;
    u.z = 0.0f;
    Vec4 w = u;
    w.w = 1.0f;
    *v = w;
}

extern const float kEpsilon;
extern Mat4* g_transform;      // 0x16f85ac
extern int   g_transformType;  // 0x16f8b50
extern Mat4* g_cachedInverse;  // 0x16f9120
extern Mat4  g_invStorage;     // 0x1718a60
extern Mat4  g_identity;       // 0x1718aa0
 // 0x14f8140 (FLT_EPSILON)
extern Mat4* g_transform;      // 0x16f85ac
extern int   g_transformType;  // 0x16f8b50
extern Mat4  g_invStorage;     // 0x1718a60
extern Mat4  g_identity;       // 0x1718aa0
void __stdcall D3DXVec3Transform(Vec4* out, const Vec4* v, const Mat4* m); // 0x120bb5c

// @ 0x011fb310  (inverse of an affine 4x4 matrix: 3x3 cofactor inverse + translation; w lanes untouched)
Mat4* __cdecl Matrix44Invert(Mat4* out, const Mat4* in)
{
    const float* m = &in->r[0].x;
    float* o = &out->r[0].x;
    float c00 = m[5] * m[10] - m[6] * m[9];
    float c01 = 0.0f - (m[1] * m[10] - m[2] * m[9]);
    float c02 = m[1] * m[6] - m[2] * m[5];
    float det = (c00 * m[0] + c01 * m[4]) + c02 * m[8];
    float inv = 1.0f;
    if (!(((-det > det) ? -det : det) <= kEpsilon)) inv = 1.0f / det;
    o[0] = c00 * inv;
    o[1] = c01 * inv;
    o[2] = c02 * inv;
    o[4] = (0.0f - (m[4] * m[10] - m[6] * m[8])) * inv;
    o[5] = (m[0] * m[10] - m[2] * m[8]) * inv;
    o[6] = (0.0f - (m[0] * m[6] - m[2] * m[4])) * inv;
    o[8] = (m[4] * m[9] - m[5] * m[8]) * inv;
    o[9] = (0.0f - (m[0] * m[9] - m[1] * m[8])) * inv;
    o[10] = (m[0] * m[5] - m[1] * m[4]) * inv;
    o[12] = 0.0f - ((m[12] * o[0] + m[13] * o[1]) + m[14] * o[2]);
    o[13] = 0.0f - ((m[12] * o[4] + m[13] * o[5]) + m[14] * o[6]);
    o[14] = 0.0f - ((m[12] * o[8] + m[13] * o[9]) + m[14] * o[10]);
    return out;
}

// @ 0x011fb750  (inverse of a rigid matrix: transpose the 3x3, translation = -(t * R^T); w lanes kept)
void __cdecl Matrix44InvertRigid(Mat4* out, const Mat4* in)
{
    float* o = &out->r[0].x;
    const float* m = &in->r[0].x;
    o[0] = m[0]; o[4] = m[1]; o[8] = m[2];
    o[1] = m[4]; o[5] = m[5]; o[9] = m[6];
    o[2] = m[8]; o[6] = m[9]; o[10] = m[10];
    float tx = m[12], ty = m[13], tz = m[14];
    o[12] = 0.0f - ((tx * m[0] + ty * m[1]) + tz * m[2]);
    o[13] = 0.0f - ((tx * m[4] + ty * m[5]) + tz * m[6]);
    o[14] = 0.0f - ((tx * m[8] + ty * m[9]) + tz * m[10]);
}

// @ 0x011fb950
void __cdecl TransformPoint(Vec4* out, const Vec4* v)
{
    if (g_cachedInverse == 0) {
        if (g_transformType == 3) {
            Matrix44InvertRigid(&g_invStorage, g_transform);
        } else if (g_transformType == 4) {
            g_cachedInverse = &g_identity;
            *out = *v;
            return;
        } else {
            Mat4 tmp;
            g_invStorage = *Matrix44Invert(&tmp, g_transform);
        }
        g_cachedInverse = &g_invStorage;
    }
    if (g_cachedInverse == &g_identity) {
        *out = *v;
        return;
    }
    Vec4 t;
    D3DXVec3Transform(&t, v, g_cachedInverse);
    Vec4 r = *out;
    r.x = t.x; r.y = t.y; r.z = t.z;
    *out = r;
}
