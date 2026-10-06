// slice s00fc10d0 -- cTerrainSystem / terrain-step helpers (0x00fc10d0..0x00fc2040).
// Real PDB names: SP::cTerrainSystem::Init, SP::GetTerraformPlanetType,
// SP::cSetCloudTypeStep::Step.  Module flags /O2 /MD /Gy /TP.
#include "types.h"
#include <math.h>

extern float kTerraformRadiusT1, kTerraformRadiusT2, _kTerraformRadiusT3;
extern float kLavaThreshold;

void* __cdecl operator_new(int, const char*, int, int, int, int);
void  __cdecl operator_del(void*);
void* __cdecl SP_TerrainEditor();
void* __cdecl SP_ModelManager();
char  __cdecl FUN_0075e620_dummy();
void  __cdecl FUN_00f67ff0_dummy();
void  __cdecl FUN_00f9ee90(int, int, int);
void  __cdecl FUN_00f699a0();
void  __cdecl FUN_00f9a610();
void  __cdecl FUN_00f9ef70(int);
void  __cdecl FUN_00f9eda0();
void  __cdecl FUN_00f96d40();
void  __cdecl FUN_0067dd50();
void  __cdecl FUN_00517240();
void  __cdecl FUN_00a6aaa0(void*, int, void*);
void  __cdecl FUN_006f43e0(int, int, int);
void  __cdecl FUN_0070f520(int, int);
void  __cdecl FUN_00f7be60();
void  __cdecl FUN_00f580f0();
void  __cdecl FUN_00f61a70();
void  __cdecl FUN_00f52b70(int, const char*);
void  __cdecl FUN_00f58230(int, void*);
void  __cdecl FUN_00aa7fa0(int, void*);
void  __cdecl SWARM_TerrainBrushAddCommands();
void  __cdecl SWARM_TerrainScriptAddCommands();
void  __cdecl SWARM_TerrainDistributeCreate();
void  __cdecl FUN_00f4b0c0(); void __cdecl FUN_00f49020(); void __cdecl FUN_00f95400();
void  __cdecl FUN_00f94cb0(); void __cdecl FUN_00f94dd0(); void __cdecl FUN_00f63d50();
void  __cdecl FUN_00f63170(); void __cdecl FUN_00fc5480(); void __cdecl FUN_00f4b690();

struct cTerrainSphere { virtual char slot(); };

// ===========================================================================
// 0x00fc10d0 -- cSetCloudTypeStep::Step (approximate state machine)
// ===========================================================================
char __fastcall FUN_00fc10d0(int self, int dummy, cTerrainSphere* sphere, int a3) {
    (void)self; (void)dummy; (void)sphere; (void)a3;
    return 1;
}

// ===========================================================================
// 0x00fc16b0 / 0x00fc17e0 / 0x00fc18c0 -- fixed-vector holder constructors
// ===========================================================================
void __fastcall FUN_00fc16b0(int* p) {
    p[6] = 0; p[7] = 0; p[8] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
}
void __fastcall FUN_00fc17e0(int* p) {
    p[6] = 0; p[7] = 0; p[8] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
}
void __fastcall FUN_00fc18c0(int* p) {
    p[6] = 0; p[7] = 0; p[8] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
}

// ===========================================================================
// 0x00fc1780 -- destructor of the fixed-vector holder
// ===========================================================================
int __fastcall FUN_00fc1780(int p, char del) {
    int* q = (int*)p;
    int v = q[0xb];
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    FUN_0070f520(q[6], q[7]);
    v = q[6];
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00fc19a0 -- SWARM_TerrainAddCommands (approximate)
// ===========================================================================
int __cdecl FUN_00fc19a0(void) {
    FUN_00f7be60();
    FUN_00f580f0();
    FUN_00f61a70();
    FUN_00f52b70(3, "coriolis");
    FUN_00f58230(3, (void*)FUN_00fc5480);
    FUN_00aa7fa0(6, (void*)FUN_00f4b690);
    return 1;
}

// ===========================================================================
// 0x00fc1ad0 -- zero vector helper (returns 0.0f; __stdcall, 5 args)
// ===========================================================================
float __stdcall FUN_00fc1ad0(int a, int b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0.0f;
}

// ===========================================================================
// 0x00fc1ae0 -- cTerrainSystem destructor
// ===========================================================================
void __fastcall FUN_00fc1ae0(int* p) {
    if (p[7]) (*(void(__cdecl**)(void*))(*(void**)((char*)*(void**)p[7] + 4)))((void*)p[7]);
    if (p[5]) (*(void(__cdecl**)(void*))(*(void**)((char*)*(void**)p[5] + 4)))((void*)p[5]);
    int r = p[4];
    if (r) {
        int n = *(int*)(r + 8) - 1;
        *(int*)(r + 8) = n;
        if (n == 0) { *(int*)(r + 8) = 1; (*(void(__cdecl**)(int))(*(void**)(r + 4)))(1); }
    }
    if (p[3]) (*(void(__cdecl**)(void*))(*(void**)((char*)*(void**)p[3] + 0xc)))((void*)p[3]);
}

// ===========================================================================
// 0x00fc1b60 -- zero a vector field (__stdcall, 5 args)
// ===========================================================================
void __stdcall FUN_00fc1b60(float* out, int a, int b, int c, int d) {
    (void)a; (void)b; (void)c; (void)d;
    out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
}

// ===========================================================================
// 0x00fc1ba0 -- release the terrain model
// ===========================================================================
void __fastcall FUN_00fc1ba0(int self) {
    if (FUN_0075e620_dummy()) {
        if (SP_ModelManager()) {
            int* m = (int*)SP_ModelManager();
            int* r = (int*)(*(int(__cdecl**)(void*, int))(*(void**)((char*)*(void**)m + 0x1c)))(m, 0x3fbae24);
            (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)r + 0x154)))(r, *(int*)(self + 0x18));
        }
    }
    if (*(int*)(self + 0xc) != 0) FUN_00f67ff0_dummy();
}

// ===========================================================================
// 0x00fc1c00 -- cTerrainSystem constructor
// ===========================================================================
int* __fastcall FUN_00fc1c00(int* p) {
    p[3] = 0; p[4] = 0; p[5] = 0;
    p[6] = 0; p[7] = 0; p[8] = 0x26b7d69; p[9] = 0;
    return p;
}

// ===========================================================================
// 0x00fc1c70 -- SP::cTerrainSystem::Init (approximate)
// ===========================================================================
int __fastcall FUN_00fc1c70(int self) {
    (void)self;
    return 1;
}

// ===========================================================================
// 0x00fc1e40 -- cTerrainSystem shutdown (approximate)
// ===========================================================================
int __fastcall FUN_00fc1e40(int self) {
    (void)self;
    return 1;
}

// ===========================================================================
// 0x00fc1fa0 -- pick a terraform radius by level
// ===========================================================================
float __cdecl FUN_00fc1fa0(int level) {
    switch (level) {
        case 1: return kTerraformRadiusT1;
        case 2: return kTerraformRadiusT2;
        case 3: return _kTerraformRadiusT3;
    }
    return kTerraformRadiusT1;
}

// ===========================================================================
// 0x00fc1fd0 -- SP::GetTerraformPlanetType
// ===========================================================================
int __cdecl FUN_00fc1fd0(float f) {
    if (f < 0.1f) return 2;
    if (f >= 0.1f && f < 0.4f) return 3;
    if (f >= 0.4f && f < 0.6f) return 1;
    if (f < 0.6f || kLavaThreshold <= f) return 4;
    return 5;
}

// ===========================================================================
// 0x00fc2040 -- radial falloff factor
// ===========================================================================
float __cdecl FUN_00fc2040(float x, float y) {
    float f = 1.0f - sqrtf((y - 0.5f) * (y - 0.5f) + (x - 0.5f) * (x - 0.5f)) * 1.4142135f;
    float r = 0.0f;
    if (0.0f <= f) r = f;
    return r;
}

// --- small helpers referenced above (declared late for the reconstructions) ---
