// Slice s0101aea0 -- SP::cUFOLocomotion / cDefaultCameraController methods
// (0x0101aea0..0x0101bd02).  Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            intptr_t;

extern float DAT_015b6da4, DAT_015b6da0, DAT_015b6d9c, DAT_015b6d98, DAT_015b6d94;
extern float DAT_015b6da8, DAT_01495390, DAT_01495394, DAT_01485720;
extern float DAT_013f4fd0, DAT_013fdf1c, DAT_013f89b8, DAT_013f9428, DAT_01470f1c;
extern float DAT_013eb1bc, DAT_013f0e84;
extern float DAT_016dd3d0, DAT_016dd384, DAT_016dd3b4, DAT_016dd374, DAT_016dd3cc;
extern float DAT_016dd3b8, DAT_016dd380, DAT_016dd3e8, DAT_016dd3ec, DAT_016dd3e0;
extern float DAT_016dd3e4, DAT_016dd414, DAT_016dd418, DAT_016dd3c8, DAT_016dd3c4;
extern u32   DAT_016dd444, DAT_016dd448, DAT_016dd44c;
extern int   DAT_016dd36c, DAT_016dd370, DAT_016dd3ac, DAT_016dd3b0;

// ---------------------------------------------------------------------------
void* __cdecl FUN_00ffbe50();                        // SP::GetUFOSimulator
int   __cdecl FUN_01021080();                        // GetUniverseContext
void* __cdecl FUN_01021260();                        // GetActivePlanet
int   __stdcall FUN_01021230(int);                   // 0x01021230
void* __cdecl FUN_00a206f0();                        // EA::Audio::GetSystemAT
void  __cdecl FUN_00435ed0(u32, int);                // KillSetiEffects
void  __stdcall FUN_00d018d0(void*, void*);          // 0x00d018d0
long long __cdecl FUN_0101aea0_x();                  // placeholder
void* __cdecl FUN_00b3d350();                        // SP::PlanetModel
void* __cdecl FUN_00c37360();                        // 0x00c37360
void* __cdecl FUN_010666a0();                        // 0x010666a0
void* __cdecl FUN_00b3d470();                        // 0x00b3d470
void* __cdecl FUN_0067cac0();                        // 0x0067cac0
void* __cdecl FUN_00b3d4d0();                        // GetTriggerMgr
void* __cdecl FUN_00b534c0(void*, float*);           // 0x00b534c0
unsigned char __cdecl FUN_01044920();                // 0x01044920
unsigned char __cdecl FUN_010422e0();                // TransitionFromSolarToGalaxy
unsigned char __cdecl FUN_01042450();                // 0x01042450
unsigned char __cdecl FUN_010423d0();                // 0x010423d0
float __cdecl FUN_01042480(float*, float*);          // 0x01042480
float* __cdecl FUN_0105c3d0(void*, void*, float);    // 0x0105c3d0
float* __cdecl FUN_0059aed0(void*, void*, void*);    // 0x0059aed0
float __cdecl FUN_01017d30_x();                      // placeholder
float __cdecl FUN_00b0f060(float, float, float);     // KeyboardRamp
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long*);

// thiscall callees
struct Ext {
    long long FUN_0093a3a0();                // EA::Stopwatch::GetElapsedTimeFloat
    void FUN_0093a1a0(int);                  // EA::Stopwatch::SetUnits
    char FUN_00c8b800();                     // 0x00c8b800
    void* FUN_00a1ad60();                    // GetPlayerInventory
    void FUN_00c3daa0(float);                // 0x00c3daa0
    void FUN_01017fe0();                     // 0x01017fe0
    float FUN_01017790(int, int);            // 0x01017790
    float FUN_01017d30();                    // 0x01017d30
    float FUN_00c37120();                    // 0x00c37120
    char FUN_00c37170();                     // 0x00c37170
    float FUN_00c3ae70();                    // 0x00c3ae70
    void FUN_00ffe3d0(float, int);           // 0x00ffe3d0
    float FUN_00fb7ba0();                    // 0x00fb7ba0
    float FUN_00b7e4d0();                    // 0x00b7e4d0
    float FUN_00b7ef70(void*);               // GetRadiusAt
    void* FUN_0107b70_getUFO();              // GetUFOPosition (placeholder naming)
    void FUN_0067c8c0(u32, int);             // 0x0067c8c0
    void FUN_01065d20();                     // 0x01065d20
};
static inline Ext* E(void* p) { return (Ext*)p; }
static inline void** VTP(void* o) { return *(void***)o; }

struct UFO {
    u8 raw[0x300];
    void  aea0(float delta);   // UpdateMouseWheel
    void  b0f0();
    void  b160(float, float);
    void  b4c0(float);
    void  b530(char);
    void  b670(float);
    void  b9e0();
    void  ba10(char);
    void  bad0(int, int);
    char  bb10(int, int, int, int);
    void  bb90(int, char);
};

// ===========================================================================
// 0x0101aea0
// ===========================================================================
// @ 0x0101aea0
void UFO::aea0(float delta) {
    char* s = (char*)raw;
    long long lVar = E(s + 0x30)->FUN_0093a3a0();
    float fVar12 = (float)lVar * *(float*)(s + 0x44);
    *(float*)(s + 0x64) = *(float*)(s + 0x60);
    if (*(int*)(s + 0x48) != *(int*)(s + 0x4c)) {
        char* end = *(char**)(s + 0x4c);
        char* begin = *(char**)(s + 0x48);
        char dl = end[-4];
        char* found = end;
        void* xmm0v = (void*)0;
        (void)xmm0v;
        for (char* it = begin; it != end; it += 8) {
            bool cond = (it[4] != dl) || (fVar12 - *(float*)it > DAT_015b6da4);
            if (cond) found = it;
        }
        (void)found;
    }
    *(int*)(s + 0x5c) = 0;
}

// ===========================================================================
// 0x0101b0f0
// ===========================================================================
// @ 0x0101b0f0
void UFO::b0f0() {
    char* s = (char*)raw;
    char* sw = s + 0x30;
    E(sw)->FUN_0093a1a0(5);
    unsigned long long q;
    if (*(int*)(sw + 0x10) == 1) {
        q = __rdtsc();
    } else {
        QueryPerformanceCounter((long long*)&q);
    }
    *(u32*)sw = (u32)q;
    *(u32*)(sw + 4) = (u32)(q >> 32);
    *(u32*)(sw + 8) = 0;
    *(u32*)(sw + 0xc) = 0;
    FUN_00d018d0(*(void**)(s + 0x48), *(void**)(s + 0x4c));
    *(u32*)(s + 0x5c) = 0;
    *(float*)(s + 0x60) = 0.0f;
}

// ===========================================================================
// 0x0101b160
// ===========================================================================
// @ 0x0101b160
void UFO::b160(float p2, float p3) {
    char* s = (char*)raw;
    int ctx = FUN_01021080();
    float fVar11 = *(float*)(s + 0x68);
    float local_38 = 0.0f;
    float fVar10;
    if (ctx == 1) fVar10 = DAT_016dd3d0;
    else if (ctx == 2) fVar10 = DAT_016dd384;
    else fVar10 = 0.0f;
    if (ctx == 1 || ctx == 2) local_38 = fVar10;
    float local_34 = 0.0f;
    fVar10 = DAT_016dd3b4;
    if (ctx == 1 || ctx == 2) local_34 = (ctx == 1) ? DAT_016dd3b4 : DAT_016dd374;
    void* inv = E(FUN_00ffbe50())->FUN_00a1ad60();
    (void)inv;
}

// ===========================================================================
// 0x0101b4c0
// ===========================================================================
// @ 0x0101b4c0
void UFO::b4c0(float f) {
    char* s = (char*)raw;
    if (f > 0.0f) {
        *(float*)(s + 0xb4) = f;
        *(float*)(s + 0x68) = f;
    } else {
        *(float*)(s + 0x68) = *(float*)(s + 0xb4);
    }
    *(float*)(s + 0xb8) = 0.0f;
    *(u32*)(s + 0xa4) = DAT_016dd444;
    *(u32*)(s + 0xa8) = DAT_016dd448;
    *(u32*)(s + 0xac) = DAT_016dd44c;
    b0f0();
    *(u8*)(s + 0xd5) = 0;
}

// ===========================================================================
// 0x0101b530
// ===========================================================================
// @ 0x0101b530
void UFO::b530(char param) {
    char* s = (char*)raw;
    int ctx = FUN_01021080();
    float local_c = 0.0f, local_8 = 0.0f;
    if (ctx == 1) local_c = DAT_016dd3b4;
    else if (ctx == 2) local_c = DAT_016dd374;
    if (ctx == 1) local_8 = DAT_016dd3d0;
    else if (ctx == 2) local_8 = DAT_016dd384;
    float fv = ((float(__thiscall*)(void*))VTP(this)[0x5c / 4])(this);
    *(u8*)(s + 0xd7) = 1;
    *(u8*)(s + 0xd8) = 1;
    b0f0();
    int iVar2 = DAT_016dd36c;
    int iVar3 = DAT_016dd370;
    if (ctx == 1) { iVar2 = DAT_016dd3ac; iVar3 = DAT_016dd3b0; }
    if (param == 0) {
        *(float*)(s + 0xb4) = local_8;
        if (!iVar3 || iVar2 < 1) return;
        int i = iVar2 - 1;
        if (i < 0) return;
        while (!(fv > *(float*)(iVar3 + i * 4))) {
            if (--i < 0) return;
        }
        *(float*)(s + 0xb4) = *(float*)(iVar3 + i * 4);
    } else {
        *(float*)(s + 0xb4) = local_c;
        if (!iVar3 || iVar2 < 1) return;
        int i = 0;
        while (!(*(float*)(iVar3 + i * 4) > fv)) {
            if (++i >= iVar2) return;
        }
        *(float*)(s + 0xb4) = *(float*)(iVar3 + i * 4);
    }
}

// ===========================================================================
// 0x0101b670
// ===========================================================================
// @ 0x0101b670
void UFO::b670(float param) {
    char* s = (char*)raw;
    void* inv = E(FUN_00ffbe50())->FUN_00a1ad60();
    if (!inv) return;
    if (!E(inv)->FUN_00c37170()) return;
    void* tm = FUN_00b3d4d0();
    if (*(int*)((char*)tm + 0x2c) == 1 || *(int*)((char*)tm + 0x2c) == 2) return;
    void* pm = FUN_00c37360();
    float f1 = E(pm)->FUN_00fb7ba0();
    void* model = FUN_00b3d350();
    float f2 = E(model)->FUN_00b7e4d0();
    float local_24 = DAT_016dd3e8 + f2;
    float x = *(float*)((char*)inv + 0x718);
    float y = *(float*)((char*)inv + 0x71c);
    float z = *(float*)((char*)inv + 0x720);
    float fv = x * x + y * y + z * z;
    (void)f1; (void)local_24; (void)fv;
}

// ===========================================================================
// 0x0101b9e0
// ===========================================================================
// @ 0x0101b9e0
void UFO::b9e0() {
    char* s = (char*)raw;
    char b = 0;
    *(u8*)(s + 0x194) = b;
    if (*(u8*)(s + 0x140) != b) b0f0();
    *(u8*)(s + 0xcc) = b;
    *(u8*)(s + 0x13e) = b;
}

// ===========================================================================
// 0x0101ba10
// ===========================================================================
// @ 0x0101ba10
void UFO::ba10(char param) {
    char* s = (char*)raw;
    void* inv = E(FUN_00ffbe50())->FUN_00a1ad60();
    b0f0();
    *(u8*)(s + 0x13d) = 1;
    if (param != 0) {
        void* model = FUN_00b3d350();
        float f = E(model)->FUN_00b7e4d0();
        E(inv)->FUN_00c3daa0((f + DAT_016dd3e8) * 2.0f);
        *(u8*)(s + 0x194) = 1;
        return;
    }
    char* p = (char*)inv + 0x750;
    void* model = FUN_00b3d350();
    float f = E(model)->FUN_00b7ef70(p);
    void* pm = FUN_00c37360();
    float f2 = E(pm)->FUN_00fb7ba0();
    float v = f2 + f2 + f;
    float h = E(inv)->FUN_00c37120();
    if (v < h) {
        E(inv)->FUN_00c3daa0(v);
        *(u8*)(s + 0x194) = 0;
        return;
    }
    *(u8*)(s + 0x194) = 0;
}

// ===========================================================================
// 0x0101bad0
// ===========================================================================
// @ 0x0101bad0
void UFO::bad0(int a, int b) {
    (void)b;
    int local = 100;
    int* p = &a;
    if (a >= 100) p = &local;
    aea0((float)*p * 0.001f);
}

// ===========================================================================
// 0x0101bb10
// ===========================================================================
// @ 0x0101bb10
char UFO::bb10(int a, int b, int c, int d) {
    (void)c; (void)d;
    char* s = (char*)raw;
    if (a == 0) return 0;
    long long lVar = E(s + 0x30)->FUN_0093a3a0();
    float local_8 = (float)lVar * *(float*)(s + 0x44);
    float fStack_4 = (a > 0) ? 1.0f : 0.0f;
    float* p = *(float**)(s + 0x4c);
    if (p < *(float**)(s + 0x50)) {
        *(float**)(s + 0x4c) = p + 2;
        if (p) { p[0] = local_8; p[1] = fStack_4; }
    } else {
        FUN_00b534c0(p, &local_8);
    }
    *(int*)(s + 0x5c) = (a < 1) + 1;
    return 0;
}

// ===========================================================================
// 0x0101bb90
// ===========================================================================
// @ 0x0101bb90
void UFO::bb90(int param2, char param3) {
    char* s = (char*)raw;
    void* planet = FUN_01021260();
    void* inv = E(FUN_00ffbe50())->FUN_00a1ad60();
    E(FUN_00ffbe50())->FUN_00ffe3d0(0.0f, 1);
    void* p30 = ((void*(__thiscall*)(void*))VTP(planet)[0x30 / 4])(planet);
    (void)p30; (void)param2; (void)param3; (void)inv;
    *(int*)(s + 0x88) = 1;
    *(u32*)(s + 0xb4) = DAT_016dd3c4;
    *(u8*)(s + 0xd7) = 1;
}
