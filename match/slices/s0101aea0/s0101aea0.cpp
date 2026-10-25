// Slice s0101aea0 -- SP::cUFOLocomotion / cDefaultCameraController methods
// (0x0101aea0..0x0101bd02).  Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <intrin.h>
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef int            intptr_t;

extern float DAT_015b6da4, DAT_015b6da0, DAT_015b6d9c, DAT_015b6d94;
extern u8    DAT_015b6d98;
extern float DAT_015b6da8, DAT_01495390, DAT_01495394, DAT_01485720, DAT_01495934;
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
void* __cdecl FUN_01021230();                        // 0x01021230
void* __cdecl FUN_00a206f0();                        // EA::Audio::GetSystemAT
void  __cdecl FUN_00435ed0(u32, int);                // KillSetiEffects
void  __stdcall FUN_00d018d0(void*, void*);          // 0x00d018d0
void  __cdecl FUN_01017fe0();                        // 0x01017fe0
long long __cdecl FUN_0101aea0_x();                  // placeholder
void* __cdecl FUN_00b3d350();                        // SP::PlanetModel
void* __cdecl FUN_00c37360();                        // 0x00c37360
void* __cdecl FUN_010666a0();                        // 0x010666a0
void* __cdecl FUN_00b3d470();                        // 0x00b3d470
void* __cdecl FUN_0067cac0();                        // 0x0067cac0
void* __cdecl FUN_00b3d4d0();                        // GetTriggerMgr
void* __cdecl FUN_00b534c0(void*, void*);             // 0x00b534c0 (vector append)
unsigned char __cdecl FUN_01044920();                // 0x01044920
unsigned char __cdecl FUN_010422e0();                // TransitionFromSolarToGalaxy
unsigned char __cdecl FUN_01042450();                // 0x01042450
unsigned char __cdecl FUN_010423d0();                // 0x010423d0
void  __cdecl FUN_01042480(float*, float*);          // 0x01042480
float __cdecl FUN_00c375d0(float*);                  // 0x00c375d0
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

// The locomotion/camera sample vector at UFO+0x48 holds 8-byte samples {float time; char keep;}
// (three padding bytes). The vector's end/capacity words live at +0x4c/+0x50.
struct UFO_Sample {
    union {
        long long raw;      // the stopwatch's 64-bit value is spilled into the sample's own storage
        struct {
            float t;
            char  keep;
        };
    };
};

// The same vector seen as an object: 0x00b534c0 is its thiscall grow/append helper, called with
// ecx = the vector base (UFO+0x48) and the old end pointer plus the sample pushed on the stack.
struct UFO_SampleVec {
    UFO_Sample* begin;
    UFO_Sample* end;
    UFO_Sample* cap;
    void FUN_00B534C0(UFO_Sample* e, UFO_Sample* s);   // 0x00b534c0
    void FUN_Erase(UFO_Sample* first, UFO_Sample* last); // 0x00d018d0 eastl::vector::erase
};

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

    // drop the stale prefix of the sample vector (8-byte {float t; char keep;} elements)
    UFO_Sample* begin = *(UFO_Sample**)(s + 0x48);
    UFO_Sample* end = *(UFO_Sample**)(s + 0x4c);
    if (begin != end) {
        char dl = ((char*)end)[-4];
        UFO_Sample* mark = begin;
        bool found = false;
        for (UFO_Sample* it = begin; it != end; ++it) {
            if (it->keep != dl || (fVar12 - it->t) > DAT_015b6da4) {
                mark = it + 1;
                found = true;
            }
        }
        if (found) {
            UFO_Sample* dst = begin;
            for (UFO_Sample* src = mark; src != end; ++src) *dst++ = *src;
            *(UFO_Sample**)(s + 0x4c) = end - (mark - begin);
        }
    }

    int mode = *(int*)(s + 0x5c);
    if (mode != 0) {
        float k = (mode == 1) ? DAT_01485720 : DAT_013eb1bc;
        int n = *(int*)(s + 0x4c) - *(int*)(s + 0x48);
        n >>= 3;
        float q = (float)(unsigned)n / DAT_015b6da0;
        q = q * delta;
        q = q * DAT_013fdf1c;
        float z = *(float*)(s + 0x60);
        *(float*)(s + 0x60) = z + (1.0f - expf(q)) * (k - z);
    } else {
        bool run = true;
        if (*(int*)(s + 0x48) != *(int*)(s + 0x4c)) {
            float d = fVar12 - (*(UFO_Sample**)(s + 0x4c))[-1].t;
            if (!(d > DAT_015b6d9c)) run = false;
        }
        if (run) {
            if (DAT_015b6d98 != 0) {
                float z = *(float*)(s + 0x60);
                float q = delta / DAT_015b6d94;
                q = q * DAT_013fdf1c;
                *(float*)(s + 0x60) = z - (1.0f - expf(q)) * z;
            } else {
                *(float*)(s + 0x60) = 0.0f;
            }
        }
    }

    float z = *(float*)(s + 0x60);
    if (z > DAT_01495934 && DAT_01495934 > *(float*)(s + 0x64)) {
        void* a = FUN_00a206f0();
        int r = a ? ((int(__thiscall*)(void*))VTP(a)[0x20 / 4])(a) : 0;
        void* b = FUN_00a206f0();
        if (b) {
            ((void(__thiscall*)(void*, int))VTP(b)[0x38 / 4])(b, 0x3475365);
            ((void(__thiscall*)(void*, int, int))VTP(b)[0x40 / 4])(b, 0x3475381, 0xfeb2337b);
            ((void(__thiscall*)(void*, int, int))VTP(b)[0x40 / 4])(b, 0x3475385, r);
            ((void(__thiscall*)(void*))VTP(b)[0x58 / 4])(b);
        }
        *(int*)(s + 0x5c) = 0;
        return;
    }
    if (DAT_013f89b8 > z && *(float*)(s + 0x64) >= DAT_013f89b8) {
        void* a = FUN_00a206f0();
        int r = a ? ((int(__thiscall*)(void*))VTP(a)[0x20 / 4])(a) : 0;
        FUN_00435ed0(0x5677db96, r);
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
    u32 hi;
    if (*(int*)(sw + 0x10) == 1) {
        unsigned long long t = __rdtsc();
        *(u32*)sw = (u32)t;
        hi = (u32)(t >> 32);
    } else {
        unsigned long long t;
        QueryPerformanceCounter((long long*)&t);
        *(u32*)sw = (u32)t;
        hi = (u32)(t >> 32);
    }
    *(u32*)(sw + 4) = hi;
    *(u32*)(sw + 8) = 0;
    *(u32*)(sw + 0xc) = 0;
    UFO_SampleVec* vec = (UFO_SampleVec*)(s + 0x48);
    vec->FUN_Erase(vec->begin, vec->end);   // 0x00d018d0 eastl::vector::erase
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
    float f = *(float*)(s + 0x68);
    float speed = -(p2 * p3);
    float lo = 0.0f;
    if (ctx == 1) lo = DAT_016dd3d0;
    else if (ctx == 2) lo = DAT_016dd384;
    float clampLo = lo;
    float hi = 0.0f;
    if (ctx == 1) hi = DAT_016dd3b4;
    else if (ctx == 2) hi = DAT_016dd374;
    float clampHi = hi;
    float nearT, farT;
    if (ctx == 1) {
        nearT = E(FUN_01021230())->FUN_00c8b800() ? DAT_016dd3cc : 400.0f;
        farT = DAT_016dd3b8;
    } else {
        nearT = DAT_016dd380;
        farT = DAT_016dd374;
    }

    void* inv = E(FUN_00ffbe50())->FUN_00a1ad60();
    float cur = *(float*)(s + 0xb4);
    char cKeep = *(char*)((char*)inv + 0x74c);
    bool near = DAT_01495934 > fabs(f - cur);
    bool outside = (cur <= lo) || (hi <= cur);
    *(char*)(s + 0xd5) = cKeep && near && outside;

    if (*(char*)(s + 0xd7) != 0) {
        if (f >= nearT && farT >= f && fabs(speed) > DAT_01495934 && (cur - f) * speed < 0.0f)
            *(char*)(s + 0xd7) = 0;
    }

    if (*(char*)(s + 0xd7) == 0) {
        E(FUN_00ffbe50())->FUN_00a1ad60();
        char trans;
        if (ctx == 1) trans = FUN_010422e0();
        else trans = FUN_01042450();
        if (!trans || f > nearT) {
            clampLo = nearT;
            *(char*)(s + 0xd9) = 0;
        } else if (f == nearT) {
            if (!*(char*)(s + 0xd9)) {
                *(char*)(s + 0xd9) = 1;
                b0f0();
                speed = 0.0f;
            }
        } else {
            *(char*)(s + 0xd7) = 1;
            *(float*)(s + 0xb4) = lo;
            FUN_01017fe0();
        }
        if (ctx != 1 || !FUN_010423d0() || f < farT) {
            clampHi = farT;
            *(char*)(s + 0xda) = 0;
        } else if (f == farT) {
            if (!*(char*)(s + 0xda)) {
                *(char*)(s + 0xda) = 1;
                b0f0();
                speed = 0.0f;
            }
        } else {
            *(char*)(s + 0xd7) = 1;
            *(float*)(s + 0xb4) = hi;
            FUN_01017fe0();
        }
    }

    *(char*)(s + 0xd6) = cKeep && near && *(float*)(s + 0xb4) == nearT && 0.0f > speed;

    if (*(char*)(s + 0xd7) == 0) {
        bool up = f > *(float*)(s + 0xb4);
        float v = E(s)->FUN_01017790(0, up) * speed + f;
        if (v < clampLo) v = clampLo;
        if (v > clampHi) v = clampHi;
        *(float*)(s + 0xb4) = v;
    }
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

    float camDist = E(FUN_00c37360())->FUN_00fb7ba0();
    float radius = E(FUN_00b3d350())->FUN_00b7e4d0();
    float farDist = radius + DAT_016dd3ec;
    float nearDist = DAT_016dd3e8 + radius;

    float x = *(float*)((char*)inv + 0x718);
    float y = *(float*)((char*)inv + 0x71c);
    float z = *(float*)((char*)inv + 0x720);
    float dist = sqrtf(x * x + y * y + z * z);
    float minDist = FUN_00c375d0((float*)E(s)->FUN_0107b70_getUFO()) + camDist;

    float ratio = (dist - minDist) / (nearDist - minDist);
    float clamped = ratio;
    if (clamped < 0.0f) clamped = 0.0f;
    if (clamped > 1.0f) clamped = 1.0f;
    float rampT = (DAT_016dd414 - DAT_016dd418) * clamped + DAT_016dd418;

    float alt = *(float*)(s + 0x8c);
    if (alt == 0.0f) alt = E(s)->FUN_01017d30();
    float height = E(inv)->FUN_00c37120();
    float absAlt = fabs(alt);

    if (absAlt > 0.1f) {
        void* q = FUN_0067cac0();
        int* o = *(int**)((char*)q + 0x4c);
        if (o && o[2] == 0x1930f01e) {
            E(q)->FUN_0067c8c0(0x1930f01e, 1);
            E(FUN_010666a0())->FUN_01065d20();
        }
    }
    if (*(char*)(s + 0x13d) != 0) {
        if (fabs(dist - height) < 1.0f) *(char*)(s + 0x13d) = 0;
    }

    char canRamp = FUN_01044920();
    if (*(char*)(s + 0x13d) == 0) {
        if (!canRamp || nearDist > dist) {
            *(char*)(s + 0x13e) = 0;
        } else if (dist == nearDist) {
            if (!*(char*)(s + 0x13e)) {
                *(char*)(s + 0x13e) = 1;
                b0f0();
                E(inv)->FUN_00c3daa0(nearDist);
                return;
            }
        } else {
            *(char*)(s + 0x13d) = 1;
            *(char*)(s + 0x13e) = 0;
            *(u8*)(s + 0x194) = 1;
            E(inv)->FUN_00c3daa0(height * 2.0f);
            return;
        }
        if (absAlt > DAT_01495934) {
            param = (height - dist) * DAT_015b6da8 + dist - alt * clamped * param;
            float* pMax = &param;
            if (minDist > param) pMax = &minDist;
            E(inv)->FUN_00c3daa0(*pMax);
        }
        if (*(float*)(s + 0x60) > 0.0f || *(float*)(s + 0x8c) > 0.0f) *(u8*)(s + 0x194) = 0;
        else if (*(float*)(s + 0x60) < 0.0f || *(float*)(s + 0x8c) < 0.0f) *(u8*)(s + 0x194) = 1;
    }
    if (canRamp) param = FUN_00b0f060(DAT_016dd3e4, DAT_016dd3e0, dist - radius);
    else param = 0.0f;
    E(FUN_00ffbe50())->FUN_00ffe3d0(param, *(u8*)(s + 0x194));
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
    int v = a;
    int local = 100;
    int* p = &v;
    if (v >= 100) p = &local;
    aea0((float)*p * 0.001f);
}

// ===========================================================================
// 0x0101bb10
// ===========================================================================
// @ 0x0101bb10
char UFO::bb10(int a, int b, int c, int d) {
    (void)b; (void)c; (void)d;
    char* s = (char*)raw;
    if (a == 0) return 0;
    UFO_Sample smp;
    smp.raw = E(s + 0x30)->FUN_0093a3a0();
    smp.t = (float)smp.raw * *(float*)(s + 0x44);
    smp.keep = (a > 0);
    UFO_Sample* end = *(UFO_Sample**)(s + 0x4c);
    if (end < *(UFO_Sample**)(s + 0x50)) {
        *(UFO_Sample**)(s + 0x4c) = end + 1;
        if (end) *end = smp;
    } else {
        ((UFO_SampleVec*)(s + 0x48))->FUN_00B534C0(end, &smp);
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

    float buf[3];
    float* a = FUN_0059aed0(buf, (void*)param2,
                            ((void*(__thiscall*)(void*))VTP(planet)[0x30 / 4])(planet));
    float v[3];
    v[0] = a[0];
    v[1] = a[1];
    v[2] = a[2];
    FUN_01042480((float*)(s + 0x68), v);

    b0f0();
    b4c0(DAT_016dd3c8);

    float* p = FUN_0105c3d0(buf, planet, E(inv)->FUN_00c3ae70());
    *(float*)(s + 0x98) = *(float*)((char*)inv + 0x718) + p[0];
    *(float*)(s + 0x9c) = *(float*)((char*)inv + 0x71c) + p[1];
    *(float*)(s + 0xa0) = *(float*)((char*)inv + 0x720) + p[2];

    *(int*)(s + 0x88) = 1;
    *(float*)(s + 0xb4) = DAT_016dd3c4;
    *(u8*)(s + 0xd7) = 1;
    if (param3 != 0) {
        ((void(__thiscall*)(void*, int))VTP(this)[0x64 / 4])(this, 1);
        *(u8*)(s + 0xd8) = 0;
    }

    void* mgr = FUN_00b3d470();
    void** slot = (void**)((char*)mgr + 0xc4);
    if (*slot) {
        mgr = FUN_00b3d470();
        slot = (void**)((char*)mgr + 0xc4);
        void* obj = *slot;
        ((void(__thiscall*)(void*, int))VTP(obj)[0xc / 4])(obj, 1);
        mgr = FUN_00b3d470();
        slot = (void**)((char*)mgr + 0xc4);
        void* old = *slot;
        if (old) {
            *slot = 0;
            ((void(__thiscall*)(void*))VTP(old)[4 / 4])(old);
        }
    }
}
