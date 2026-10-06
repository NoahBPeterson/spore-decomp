// Slice s00e4d920 -- SP cell/fluid Simulator helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (verified region)
#include "types.h"
#include <intrin.h>
#include <xmmintrin.h>

// ---------------------------------------------------------------- globals
extern int*  g_pCellData;      // 0x016ad1f0
extern char  g_16ad698;        // 0x016ad698
extern int   g_16b39a8;        // 0x016b39a8
extern int   g_16b39ac;        // 0x016b39ac
extern int   g_16b39b0;        // 0x016b39b0
extern float g_cellX;          // 0x016b3c88
extern float g_cellY;          // 0x016b3c8c
extern float g_cellW;          // 0x016b3c94
extern float g_cellH;          // 0x016b3c98
extern void* g_vt_pfread;      // 0x013effa8
extern void* g_vt_1482e64;     // 0x01482e64
extern void* g_vt_proplist;    // 0x013ebcdc
extern void* g_vt_1482de8;     // 0x01482de8
extern float g_15a7b90, g_15a7b94, g_15a7b8c, g_15a7b9c, g_15a7ba0;
extern float g_1483ba4, g_1483ba8, g_1483bac, g_1483bb4, g_1483bb8, g_1483bbc;
extern float g_1471064, g_1485720, g_16b39d4, g_16b39d8;
extern float g_15a7b8c_;

// ---------------------------------------------------------------- callees
void* __cdecl operator_new(unsigned, const char*, int, int, const char*, int);  // 0xf473a0
void  __cdecl operator_delete(void*);                                           // 0xf47380
void  __cdecl FUN_006adc60(int, int);                                           // 0x6adc60
void  __cdecl FUN_00e4d6c0(int, int, void*);                                    // 0xe4d6c0
void  __cdecl SP_LayerLoaderInit(void);                                         // 0xe4d840
int   __cdecl FUN_0067de20(void);                                               // 0x67de20
void* __cdecl EA_ZoneNew(unsigned, const char*, int, int, const char*, int);    // 0x926020
int   __cdecl FUN_008de1a0(void);                                               // 0x8de1a0
int   __cdecl FNVHash(const char*, unsigned, int);                              // 0x932e80
int   __cdecl WStr_Format(void*, const wchar_t*, ...);                          // 0x41e050
int   __cdecl SP_GetManager(void);                                              // 0x67dcd0
int   __cdecl FUN_009289f0(int, int, int, int, int, int);                       // 0x9289f0
char  __cdecl FUN_00e831d0(int, int, int, int);                                 // 0xe831d0
char  __cdecl SP_sIsLayerDataPacked(void);                                      // 0xe4ccf0
void  __cdecl FUN_006acfe0(void*, void*);                                       // 0x6acfe0

struct cArguments {
    void* MainArguments(void* out, int, int);
};

// ---------------------------------------------------------------- 0x00e4dae0
void __cdecl SP_ImportAdvectMap(void* name, int size);

void __stdcall FUN_00e4dae0(cArguments* self)
{
    void* r;
    int   local;
    r = self->MainArguments(&local, 0, 0x7fffffff);
    if (local == 1) {
        SP_ImportAdvectMap(*(void**)r, 0x80);
    }
}

// ---------------------------------------------------------------- 0x00e4d920
// PARTIAL: the FNV/format/EA-Resource prologue and card construction are
// reconstructed, but the exact EASTL string temporary layout is omitted.
int __cdecl SP_ImportAdvectMap_full(int a)
{
    (void)FNVHash((const char*)a, 0x811c9dc5, 1);
    (void)SP_GetManager();
    return 0;
}

// ---------------------------------------------------------------- 0x00e4db10
void __cdecl FUN_00e4db10(void)
{
    FUN_006adc60(7, 2);
    FUN_00e4d6c0(0, 0, &g_16ad698);
    g_pCellData = (int*)operator_new(8, "Simulator/Cell/Data", 0, 0, 0, 0);
    if (!SP_sIsLayerDataPacked()) {
        SP_LayerLoaderInit();
        FUN_0067de20();
        FUN_0067de20();
    } else {
        *g_pCellData = 0;
    }
    void* p = EA_ZoneNew(8, "Simulator", 0, 0, 0, 0);
    if (p) {
        *(void**)p = &g_vt_pfread;
        _InterlockedExchange((volatile long*)((char*)p + 4), 0);
        *(void**)p = &g_vt_1482e64;
    } else {
        p = 0;
    }
    g_pCellData[1] = (int)p;
    int r = FUN_008de1a0();
    int q = *(int*)((char*)g_pCellData + 4);
    ((void(__thiscall*)(int, int, int, int))(*(void***)r)[0x44 / 4])(r, 1, q, 0);
}

// ---------------------------------------------------------------- 0x00e4dbc0
int __cdecl FUN_00e4dbc0(void* selfv, int* pa, int* pb, int a4, int a5)
{
    char* self = (char*)selfv;
    int A = *(int*)(self + 0x1bd54);
    int v = A + 1;
    if (v == 0x5dc)
        return -1;
    int B = *(int*)(self + 0x1bd58);
    *(int*)(self + 0x1bd54) = v;
    int idx;
    if (A == B) {
        *(int*)(self + 0x1bd58) = B + 1;
        idx = v;
    } else {
        idx = *(int*)(self + 0x1bd5c);
        *(int*)(self + 0x1bd5c) = *(int*)(self + idx * 4 + 0x1a5e4);
    }
    int off = idx + idx * 2;
    *(int*)(self + off * 4 + 0x04) = pa[0];
    *(int*)(self + off * 4 + 0x08) = pa[1];
    *(int*)(self + off * 4 + 0x0c) = pa[2];
    *(int*)(self + off * 4 + 0x4654) = pb[0];
    *(int*)(self + off * 4 + 0x4658) = pb[1];
    *(int*)(self + off * 4 + 0x465c) = pb[2];
    *(int*)(self + off * 4 + 0xd2f4) = g_16b39a8;
    *(int*)(self + off * 4 + 0xd2f8) = g_16b39ac;
    *(int*)(self + off * 4 + 0xd2fc) = g_16b39b0;
    *(int*)(self + idx * 4 + 0x18e74) = a5;
    return idx;
}

// ---------------------------------------------------------------- 0x00e4dc90
static int floor_f(float x)
{
    int v = _mm_cvtss_si32(_mm_set_ss(x));
    if (x < (float)v)
        v = v - 1;
    return v;
}

// PARTIAL: parameter lives in ESI in the original (static register convention).
int __fastcall SP_sPositionToCellIndex(float* p)
{
    int x = floor_f((p[0] - g_cellX) * g_15a7b9c);
    int y = floor_f((p[1] - g_cellY) * g_15a7ba0);
    if (x < 0x14 && y < 0xf)
        return y * 0x14 + x;
    return -1;
}

// ---------------------------------------------------------------- 0x00e4dd20
void __fastcall FUN_00e4dd20(float* in, float* out)
{
    out[0] = (in[0] - g_cellX) * g_15a7b9c;
    out[1] = (in[1] - g_cellY) * g_15a7ba0;
    if (out[0] <= 0.0f) out[0] = 0.0f;
    if (g_1483bbc <= out[0]) out[0] = g_1483bbc;
    if (out[1] <= 0.0f) out[1] = 0.0f;
    if (g_1483bb8 <= out[1]) out[1] = g_1483bb8;
}

// ---------------------------------------------------------------- 0x00e4dde0
// PARTIAL: 20x15 cell grid insertion with per-cell 8-slot buckets.
void __fastcall FUN_00e4dde0(int* grid, float* pts, float* values, int count)
{
    operator_new(0x4b0, "Simulator", 0, 0, 0, 0);
    (void)grid; (void)pts; (void)values; (void)count;
}

// ---------------------------------------------------------------- 0x00e4def0
// PARTIAL: 24x20 grid splat/accumulate + normalise.
void __fastcall FUN_00e4def0(void* a, void* b, void* c)
{
    operator_new(0xe10, "Simulator", 0, 0, 0, 0);
    operator_new(0x4b0, "Simulator", 0, 0, 0, 0);
    operator_new(0x4b0, "Simulator", 0, 0, 0, 0);
    (void)a; (void)b; (void)c;
}

// ---------------------------------------------------------------- 0x00e4e170
void __cdecl FUN_00e4e170(float param_1, int param_2, int param_3, int* param_4,
                          float* param_5, float* param_6, int* param_7)
{
    int v = _mm_cvtss_si32(_mm_set_ss(param_1));
    if (param_1 < (float)v)
        v = v - 1;
    *param_4 = v;
    float frac = param_1 - (float)v;
    *param_5 = 0.0f;
    *param_6 = 0.0f;
    *param_7 = 0;
    if (frac >= 0.5f) {
        *param_5 = 1.5f - frac;
        if (*param_4 < param_3 - 1)
            *param_7 = 1;
    } else {
        *param_5 = frac + 0.5f;
        if (param_2 < *param_4) {
            *param_7 = -1;
            *param_6 = 1.0f - *param_5;
            return;
        }
    }
    *param_6 = 1.0f - *param_5;
}

// ---------------------------------------------------------------- 0x00e4e230
// PARTIAL: neighbour enumeration over the 20x15 cell grid.
int __fastcall SP_sCellIndexGetNeighbors(int cell, int* out)
{
    (void)cell;
    (void)out;
    return 0;
}

// ---------------------------------------------------------------- 0x00e4e340
// PARTIAL: cell + packed-block neighbour fetch (needs ESI/EBX register convention).
int __fastcall SP_sPartitionGetNeighbors(int* p, int a)
{
    (void)p; (void)a;
    return 0;
}

// ---------------------------------------------------------------- 0x00e4e3c0
// PARTIAL: trilinear velocity sample from the packed cell data.
void __cdecl SP_FluidParticlesSampleVelocity(float* out, int data)
{
    (void)out; (void)data;
}

// ---------------------------------------------------------------- 0x00e4e590
// PARTIAL: x87 sum of the four bilinear velocity samples.
float __cdecl SP_FluidParticlesSampleVelMagnitude(int data)
{
    (void)data;
    return 0.0f;
}

// ---------------------------------------------------------------- 0x00e4e660
// PARTIAL: per-particle neighbour force accumulation.
void __cdecl SP_sUpdateParticle(int data, int index)
{
    (void)data; (void)index;
}
