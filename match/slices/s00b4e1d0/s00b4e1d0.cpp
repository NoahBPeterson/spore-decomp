// slice s00b4e1d0 -- Simulator physics / effect glue:
//   0x00b4e1d0  push a game object's position/orientation onto a Havok shape phantom
//   0x00b4e620  set a batch of named "global properties" on the audio/SPUI system
//   0x00b4e820  collision-message wrapper #1 (type 0)
//   0x00b4e980  collision-message wrapper #2 (type 1, extra event sink)
//   0x00b4ead0  collision-message wrapper #3 (type 2, two objects)
//   0x00b4ec70  cubic brake/falloff curve (returns 0 when inactive)
//
// This range is ordinary game/physics code, not RenderWare-4 core, so byte-exactness is pursued.
// Objects are raw byte spans accessed at fixed offsets; interface calls go through the vtable slots
// the original uses (offsets noted inline).
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
//   /GS- is required: the 0x7a-byte cCollisionInfo local in 00b4e820/00b4e980/00b4ead0 contains arrays,
//   so with the default /GS MSVC emits a __security_cookie prologue that the original does not have.
#include "types.h"
#include <math.h>

typedef unsigned int  u32;
typedef unsigned char u8;
typedef signed   int  i32;

// ------------------------------------------------------------------------------------------------
// callees (declaration-only: chk masks the relocated call targets)
// ------------------------------------------------------------------------------------------------
u32   __cdecl GetSystemAT();                          // 0x00a206f0 EA::Audio::GetSystemAT
u32   __cdecl GetRecorderState();                     // 0x00435e90
void  __cdecl KillSetiEffects(u32 id, u32 state);     // 0x00435ed0 SP::cSPUISpace::KillSetiEffects
void  __cdecl SetGlobalProperty(u32 id, float v);     // 0x005ca880
u32   __cdecl GetCurrentGameMode();                   // 0x00b5b800 SP::GetCurrentGameMode
u32   __cdecl AudioSystem();                          // 0x0067cb00 SP::AudioSystem
void  __cdecl Simulator_OnEvent(void* info);          // 0x00f31220 Simulator_OnEvent
void  __cdecl FUN_00b4d470(char* dst, char* src);     // 0x00b4d470 repack into a dense record
void  __cdecl FUN_00b4dee0(char* self, u8 flag, float* out); // 0x00b4dee0 capsule/sphere contact

// thiscall callees: modelled as members of opaque structs so MSVC emits `this` in ecx exactly like
// the original.
struct HkObj {
    i32* find961(i32* out, i32 key);                  // 0x00496140 ?Find@D961
};

// vtable dispatches: the original loads the slot and calls through it, so the call sites model the
// slot contents as a __thiscall function pointer.
typedef float* (__thiscall *FnGetVec)(void* self, int a);
typedef char*  (__thiscall *FnGetByName)(void* self, char* name);

// ------------------------------------------------------------------------------------------------
// Havok pieces used by 0x00b4e1d0
// ------------------------------------------------------------------------------------------------
struct hkBool { u8 b; hkBool(); hkBool(const hkBool&); hkBool& operator=(const hkBool&); };
struct hkMatrix3 {
    hkBool isApproximatelyEqual(const hkMatrix3& other, float eps) const;   // 0x010815a0
};
struct hkShapePhantom {
    void setTransform(const void* xf);                // 0x0108db50
    void setPosition(const float* v, float w);        // 0x0108dbb0
};
struct hkTransform { float rot[12]; float tr[4]; };   // column-major hkRotation + hkVector4

// ------------------------------------------------------------------------------------------------
// SP::cCollisionInfo -- the record repacked at +0x00b4d470 and dispatched to the event sinks.
// 0x7a bytes; ctor at 0x00b3d8c0.
// ------------------------------------------------------------------------------------------------
struct cCollisionInfo {
    u32   collisionType;      // +0x00
    float data[0x19];         // +0x04 .. +0x67
    void* pGameDataA;         // +0x68
    void* pGameDataB;         // +0x6c
    u8    tail[0xa];          // +0x70 .. +0x79
    cCollisionInfo();         // 0x00b3d8c0
};

// ------------------------------------------------------------------------------------------------
// float constants / globals (declared by address; literals live in the image's read-only pool)
// ------------------------------------------------------------------------------------------------
extern float g_pi;        // 0x01569b18  (3.14159f)
extern float g_third;     // 0x013f26dc  (0.33333334f)
extern float g_three;     // 0x013eb95c  (3.0f)
extern float g_one;       // 0x015695f8  (1.0f)
extern float g_two;       // 0x01470f1c  (2.0f)
extern float g_eps;       // 0x014612dc  (1.5258789e-05f)
extern float g_thr1;      // 0x01569ae8  (1.0f)
extern float g_thr400;    // 0x01569aec  (400.0f)
extern float g_thr10000;  // 0x01569af0  (10000.0f)
extern float g_thr50;     // 0x01569af4  (50.0f)
extern float g_2p32;      // 0x013f4fd0  (4294967296.0f)
extern u32   g_recorder;  // 0x0167ece8
extern u32   g_patchId;   // 0x0167ece4
extern void (__cdecl* g_eventHandler)(void*);  // 0x0167eb88

// ================================================================================================
// 0x00b4e1d0  drive a Havok shape phantom from the object's position and orientation
// ================================================================================================
// @ 0x00b4e1d0
void __cdecl FUN_00b4e1d0(char* a1, char* a2)
{
    i32 key;
    i32* found = ((HkObj*)a2)->find961(&key, 6);
    u8 flag = (found[0] != 0);

    float* pp = ((FnGetVec)(*(void**)(*(u32*)a1 + 0x2c)))(a1, 0);
    float pos[4];
    pos[0] = pp[0];
    pos[1] = pp[1];
    pos[2] = pp[2];
    pos[3] = 0.0f;
    FUN_00b4dee0(a1, flag, pos);

    float* q = ((FnGetVec)(*(void**)(*(u32*)a1 + 0x30)))(a1, 0);
    float x = q[0], y = q[1], z = q[2], w = q[3];

    hkTransform xf;
    xf.rot[0]  = 1.0f - (z * z + y * y) * g_two;
    xf.rot[1]  = (w * z + y * x) * g_two;
    xf.rot[2]  = (z * x - w * y) * g_two;
    xf.rot[3]  = 0.0f;
    xf.rot[4]  = (y * x - w * z) * g_two;
    xf.rot[5]  = 1.0f - (z * z + x * x) * g_two;
    xf.rot[6]  = (w * x + z * y) * g_two;
    xf.rot[7]  = 0.0f;
    xf.rot[8]  = (w * y + z * x) * g_two;
    xf.rot[9]  = (z * y - w * x) * g_two;
    xf.rot[10] = 1.0f - (y * y + x * x) * g_two;
    xf.rot[11] = 0.0f;
    xf.tr[0] = pos[0];
    xf.tr[1] = pos[1];
    xf.tr[2] = pos[2];
    xf.tr[3] = pos[3];

    char* tr = *(char**)(a2 + 0x24);
    if (((hkMatrix3*)tr)->isApproximatelyEqual(*(hkMatrix3*)xf.rot, 0.001f).b == 0) {
        ((hkShapePhantom*)a2)->setTransform(&xf);
        return;
    }
    float* cur = (float*)(tr + 0x30);
    if (fabsf(pos[0] - cur[0]) > 0.001f ||
        fabsf(pos[1] - cur[1]) > 0.001f ||
        fabsf(pos[2] - cur[2]) > 0.001f) {
        ((hkShapePhantom*)a2)->setPosition(pos, 0.0f);
    }
}

// ================================================================================================
// 0x00b4e620  set the ten "global properties" driving one UI/audio effect
// ================================================================================================
// @ 0x00b4e620
void __cdecl FUN_00b4e620(u32 a1, float a2, float a3, u32 a4, float a5, float a6, float* a7)
{
    u32 sys = GetSystemAT();
    if ((sys != 0) && (a1 != 0) && (a4 != 0) && (g_thr1 < a2 + a5)) {
        float v[3];
        v[0] = a7[0];
        v[1] = a7[1];
        v[2] = a7[2];
        float thr = g_thr400;
        if ((g_thr50 < a3) || (g_thr50 < a6)) {
            thr = g_thr10000;
        }
        float* p = ((FnGetVec)(*(void**)(*(u32*)sys + 0x10)))((void*)sys, 0);
        float dy = p[1] - v[1];
        float dx = p[0] - v[0];
        float dz = p[2] - v[2];
        if (dz * dz + dx * dx + dy * dy <= thr) {
            if (g_recorder == 0) {
                g_recorder = GetRecorderState();
                KillSetiEffects(g_patchId, g_recorder);
            }
            SetGlobalProperty(0x393e0cdeu, (float)a1);
            SetGlobalProperty(0x393e0cddu, (float)a4);
            SetGlobalProperty(0x50c5d67u, a7[0]);
            SetGlobalProperty(0x50c5d66u, a7[1]);
            SetGlobalProperty(0x50c5d65u, a7[2]);
            SetGlobalProperty(0xbdf087bcu, a2);
            SetGlobalProperty(0xbdf087bfu, a5);
            SetGlobalProperty(0x64b5d38bu, a3);
            SetGlobalProperty(0x64b5d388u, a6);
            SetGlobalProperty(0xe7166a0u, 0.0f);
        }
    }
}

// ================================================================================================
// 0x00b4e820  collision-message wrapper (type 0)
// ================================================================================================
// @ 0x00b4e820
void __cdecl FUN_00b4e820(char* a1, char a2, char a3, float* a4)
{
    if (a3 != 0) {
        if (GetCurrentGameMode() == 0x1654c10u) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a4);
            info.collisionType = 0;
            info.pGameDataA = a1;
            Simulator_OnEvent(&info);
        }
        if (AudioSystem() != 0) {
            char* t;
            if (a1 != 0) {
                FnGetByName getByName = (FnGetByName)(*(void**)(*(u32*)a1 + 0xc));
                t = getByName(a1, (char*)0x1186577);
            } else {
                t = 0;
            }
            char* tgt = *(char**)(t + 0x58);
            if (tgt == 0) {
                tgt = *(char**)(t + 0x54);
            }
            float scale = *(float*)(t + 0x8c);
            if (a2 != 0) {
                FUN_00b4e620((u32)tgt,
                             -((a4[10] * a4[2] + a4[9] * a4[1]) + a4[8] * a4[0]),
                             a4[0x18] * scale,
                             3, 0.0f, 0.0f, a4 + 4);
            } else {
                FUN_00b4e620((u32)tgt,
                             (a4[0xe] * a4[2] + a4[0xd] * a4[1]) + a4[0xc] * a4[0],
                             a4[0x19] * scale,
                             3, 0.0f, 0.0f, a4 + 4);
            }
        }
    }
}

// ================================================================================================
// 0x00b4e980  collision-message wrapper (type 1, extra event sink at 0x0167eb88)
// ================================================================================================
// @ 0x00b4e980
void __cdecl FUN_00b4e980(char* a1, u32 a2, u32 a3, char a4, char a5, float* a6)
{
    if (a5 != 0) {
        if (g_eventHandler != 0) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a6);
            info.collisionType = 1;
            info.pGameDataA = a1;
            g_eventHandler(&info);
        }
        if (AudioSystem() != 0) {
            char* t;
            if (a1 != 0) {
                FnGetByName getByName = (FnGetByName)(*(void**)(*(u32*)a1 + 0xc));
                t = getByName(a1, (char*)0x1186577);
            } else {
                t = 0;
            }
            char* tgt = *(char**)(t + 0x58);
            if (tgt == 0) {
                tgt = *(char**)(t + 0x54);
            }
            float scale = *(float*)(t + 0x8c);
            if (a4 != 0) {
                FUN_00b4e620((u32)tgt,
                             -((a6[10] * a6[2] + a6[9] * a6[1]) + a6[8] * a6[0]),
                             a6[0x18] * scale,
                             a3, 0.0f, 0.0f, a6 + 4);
            } else {
                FUN_00b4e620((u32)tgt,
                             (a6[0xe] * a6[2] + a6[0xd] * a6[1]) + a6[0xc] * a6[0],
                             a6[0x19] * scale,
                             a3, 0.0f, 0.0f, a6 + 4);
            }
        }
        (void)a2;
    }
}

// ================================================================================================
// 0x00b4ead0  collision-message wrapper (type 2, two game objects)
// ================================================================================================
// @ 0x00b4ead0
void __cdecl FUN_00b4ead0(char* a1, char* a2, char a3, float* a4)
{
    if (a3 != 0) {
        if (GetCurrentGameMode() == 0x1654c10u) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a4);
            info.collisionType = 2;
            info.pGameDataA = a1;
            info.pGameDataB = a2;
            Simulator_OnEvent(&info);
        }
        if (g_eventHandler != 0) {
            cCollisionInfo info;
            FUN_00b4d470((char*)&info, (char*)a4);
            info.collisionType = 2;
            info.pGameDataA = a1;
            info.pGameDataB = a2;
            g_eventHandler(&info);
        }
        if (AudioSystem() != 0) {
            char* t1;
            if (a1 != 0) {
                t1 = ((FnGetByName)(*(void**)(*(u32*)a1 + 0xc)))(a1, (char*)0x1186577);
            } else {
                t1 = 0;
            }
            char* t2;
            if (a2 != 0) {
                t2 = ((FnGetByName)(*(void**)(*(u32*)a2 + 0xc)))(a2, (char*)0x1186577);
            } else {
                t2 = 0;
            }
            char* tg1 = *(char**)(t1 + 0x58);
            if (tg1 == 0) {
                tg1 = *(char**)(t1 + 0x54);
            }
            char* tg2 = *(char**)(t2 + 0x58);
            if (tg2 == 0) {
                tg2 = *(char**)(t2 + 0x54);
            }
            FUN_00b4e620((u32)tg1,
                         -((a4[9] * a4[1] + a4[10] * a4[2]) + a4[0] * a4[8]),
                         *(float*)(t1 + 0x8c) * a4[0x18],
                         (u32)tg2,
                         (a4[0xd] * a4[1] + a4[0xe] * a4[2]) + a4[0xc] * a4[0],
                         *(float*)(t2 + 0x8c) * a4[0x19],
                         a4 + 4);
        }
    }
}

// ================================================================================================
// 0x00b4ec70  cubic brake curve; writes out[i] = in[i] * (-pi*(b*t^2 - t^3/3) * scale)
// returns 0 (and leaves out untouched) when the input is inside the inactive band.
// ================================================================================================
// @ 0x00b4ec70
u8 __cdecl FUN_00b4ec70(float* out, float a, float b, float c, const float* in, float scale)
{
    float t;
    if (a <= 0.0f) {
        return 0;
    }
    t = c - (a - b);
    if (t <= g_eps) {
        return 0;
    }
    if (0.0f <= t) {
        if (t > b * g_two) t = b * g_two;
    } else {
        t = 0.0f;
    }
    float v = -((((((t * t) * b) * g_three - (t * t) * t) *
                  (g_pi * g_third)) * g_one) * scale);
    out[0] = in[0] * v;
    out[1] = in[1] * v;
    out[2] = in[2] * v;
    out[3] = in[3] * v;
    return 1;
}
