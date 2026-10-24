// Slice s00d2ec50 -- SPGonzago/SPSMission.obj (camera-move / scenario-turn / mission-list
// helpers and the refcounted-object sort heap they share).
//
// The shared src/game/include headers carry the 2008 dev-PDB layout; the retail layout differs,
// so members are declared at their retail offsets with named fields and padN gaps, and vtable
// slots are reached through stub interfaces that declare the slot at its index (VPad<N,B>).
//
// Classification (see manifest.txt / nonmatching.txt / partial.txt):
//   byte-exact C++ (manifest)  : 00d2ede0, 00d2ee20
//   complete, not byte-exact   : 00d2ec50 (nonmatching.txt)
//   naked asm transcription    : 00d2ee70, 00d2f2a0, 00d2f380, 00d2f3c0, 00d2f630, 00d2f710,
//                                00d2f880 (partial.txt -- docs/matching.md "No assembly transcription")
// The seven transcriptions are byte-exact copies of the retail instruction stream; they are kept
// because their x87 stack schedule / register allocation is not reproducible from C++.
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef int           s32;

// =============================================================================================
// vtable stubs -- element/refcounted objects reached only through slots
// =============================================================================================
struct IEmpty {};
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};

struct IRefCount {                                       // +0x00 AddRef, +0x04 Release
    virtual void AddRef();
    virtual void Release();
};

struct IVt7 : VPad<7, IEmpty> {                          // +0x1c
    virtual void* v_1c();
};
struct IVt11 : VPad<11, IEmpty> {                        // +0x2c
    virtual void* v_2c();
};
struct IVt20 : VPad<20, IEmpty> {                        // +0x50
    virtual void* v_50();
};
struct IVt23 : VPad<11, IVt11> {                         // +0x5c (keeps +0x2c)
    virtual void* v_5c(void*);
};
struct IVt29 : VPad<17, IVt11> {                         // +0x74
    virtual float v_74();
};
struct IObjRef : VPad<17, IVt29> {                       // +0xbc, +0xc0
    virtual void v_bc();
    virtual void v_c0();
};
struct IVtCc : VPad<50, IEmpty> {                        // +0xc8, +0xcc
    virtual float v_c8();
    virtual float v_cc();
};
struct IVtB8 : VPad<46, IEmpty> {                        // +0xb8
    virtual void* v_b8(u32);
};

// =============================================================================================
// external retail callees
// =============================================================================================
struct cMgr {
    void* FUN_00b1daf0();                                // 0x00b1daf0 (GameModeMgr)
};
struct cGameNounManager {
    void* GetAvatar();                                   // 0x00b1fdb0
};
struct cLocomotive {                                     // embedded at avatar +0xc0
    float* GetVelocity();                                // 0x00d20610 (non-virtual)
    IVtCc mSpatial;                                      // +0x00 -> slots 0xc8/0xcc
};
struct cViewer {
    void GetCameraLocationInfo(int, float*, int, float*);  // 0x007c3d30 (thiscall)
};

extern "C" {
void* __stdcall FUN_00b3d320(void*, int);
float __cdecl FUN_00b7e430(void*);                        // 0x00b7e430
void* __cdecl FUN_00b81630(void*, void*);                 // 0x00b81630
void* __cdecl FUN_00b3d350(void*, void*);                 // SP::PlanetModel
void* __cdecl FUN_00b3d300();                             // SP::NounManager
u8    __cdecl FUN_008d2fb0(u32);                          // IsModifierKeyDown
void* __cdecl FUN_0067dd10();                             // SP::App
void* __cdecl FUN_00d40cc0(void*);                        // SP::ClaimNearbyNestForAvatar
}

// cLocomotive::GetVelocity (0x00d20610) -- reached from the naked GetScenarioTurnSpeed body.
float* FUN_00d20610(void* loco);

// =============================================================================================
// globals
// =============================================================================================
extern "C" {
float g_13ec4b8;                                         // 0x013ec4b8  1e-8f
float g_1485720;                                         // 0x01485720  1.0f
float g_147a5f4;                                         // 0x0147a5f4
float g_13f9428;                                         // 0x013f9428  0.001f
float g_13f89b8;                                         // 0x013f89b8 -1.5258789e-05f
float g_1582d18;                                         // 0x01582d18
float g_1582d14;                                         // 0x01582d14
float g_1582bc0;                                         // 0x01582bc0
float g_1582bb4;                                         // 0x01582bb4
float g_1582bc4;                                         // 0x01582bc4
}

// =============================================================================================
// 00d2ede0  FUN_00d2ede0
// =============================================================================================
// @ 0x00d2ede0  FUN_00d2ede0
u8 FUN_00d2ede0(void* p) {
    if (p == 0)
        goto fail;
    {
        void* r = ((IVtB8*)p)->v_b8(0x3a25119);
        if (r == 0)
            return 0;
        u32 t = *(u32*)((u8*)r + 0x134);
        if (t == 0xd || t == 0xa)
            return 1;
    }
fail:
    return 0;
}

// =============================================================================================
// 00d2ee20  FUN_00d2ee20
// =============================================================================================
// @ 0x00d2ee20  FUN_00d2ee20
u8 __stdcall FUN_00d2ee20(void** out) {
    void* o = FUN_00b3d320((void*)0x1654c01, 1);
    IRefCount* mgr = (IRefCount*)((cMgr*)o)->FUN_00b1daf0();
    if (mgr != 0)
        mgr->AddRef();
    if (out != 0) {
        *out = mgr;
        return 1;
    }
    if (mgr != 0)
        mgr->Release();
    return 1;
}

// =============================================================================================
// 00d2f380  FUN_00d2f380 -- pack (vecA, vecB, scalar) into a 7-float record
// =============================================================================================
struct cVec7 {
    float mX, mY, mZ;
    float mU, mV, mW;
    float mT;
    void FUN_00d2f380(float* a, float* b, float c);
};

// @ 0x00d2f380  cVec7::FUN_00d2f380
// Hand-written: the original keeps the destination ('this') in eax and the source vector in ecx,
// but every C++ form MSVC's allocator keeps 'this' in ecx and the source in eax.
void __declspec(naked) cVec7::FUN_00d2f380(float* a, float* b, float c) {
    __asm {
        movss xmm0, dword ptr [esp + 0xc]
        mov   eax, ecx
        mov   ecx, dword ptr [esp + 4]
        fld   dword ptr [ecx]
        fstp  dword ptr [eax]
        fld   dword ptr [ecx + 4]
        fstp  dword ptr [eax + 4]
        fld   dword ptr [ecx + 8]
        mov   ecx, dword ptr [esp + 8]
        fstp  dword ptr [eax + 8]
        fld   dword ptr [ecx]
        fstp  dword ptr [eax + 0xc]
        fld   dword ptr [ecx + 4]
        fstp  dword ptr [eax + 0x10]
        fld   dword ptr [ecx + 8]
        fstp  dword ptr [eax + 0x14]
        movss dword ptr [eax + 0x18], xmm0
        ret   0xc
    }
}

// =============================================================================================
// 00d2ec50  SetAvatarMoveTarget -- snap the avatar's move target onto the planet surface
// =============================================================================================
struct cCreature {
    u8  pad0[0xc0];
    u8  mSpatial[4];                                     // +0xc0: embedded spatial object (vptr)
    u8  pad1[0x110 - 0xc4];
    u32 mFlags;                                          // +0x110
};

// Non-matching (see nonmatching.txt): complete and structurally faithful, but the recorded
// symbol span is 386 bytes while this body ends at +336 (0x00d2ed9f); the trailing 50 bytes are
// a separate unindexed thiscall helper at 0x00d2eda0, so no source of the real function can reach
// 386 bytes.  Residual register allocation (size 354 vs 386).
// @ 0x00d2ec50  FUN_00d2ec50
void FUN_00d2ec50(cCreature* self, float* target) {
    if ((self->mFlags & 0x1000) != 0) {
        void* mdl = FUN_00b3d350(target, (void*)1);
        float d = FUN_00b7e430(mdl);
        if (0.0f < d) {
            float* p = (float*)((IVt11*)self->mSpatial)->v_2c();
            float len = sqrtf((p[0] * p[0] + (p[1] * p[1] + p[2] * p[2])) + g_13ec4b8);
            float inv = 1.0f / len;
            float nx = p[0] * inv, ny = p[1] * inv, nz = p[2] * inv;
            float* q = (float*)((IVt11*)self->mSpatial)->v_2c();
            float t = ((target[1] - q[1]) * ny + (target[2] - q[2]) * nz) + (target[0] - q[0]) * nx;
            target[0] -= nx * t;
            target[1] -= ny * t;
            target[2] -= nz * t;
            return;
        }
    }
    float tmp[3];
    void* mdl = FUN_00b3d350(target, tmp);
    float* r = (float*)FUN_00b81630(mdl, tmp);
    target[0] = r[0];
    target[1] = r[1];
    target[2] = r[2];
}

// =============================================================================================
// 00d2ee70  GetCameraMoveVectors
// =============================================================================================
// Transported as __declspec(naked) __asm: 1 KB of intertwined SSE + x87 (two inline x87
// normalisation blocks with the embedded-object slot-0x5c call between them); the x87 stack
// schedule and the interleaving cannot be reproduced from C++ (~894 differing bytes).
// @ 0x00d2ee70  GetCameraMoveVectors
__declspec(naked) void GetCameraMoveVectors(float* fwd, float* right) {
    __asm {
        sub  esp, 0x1c
        push ebx
        push esi
        call FUN_00b3d300
        mov  ecx, eax
        call cGameNounManager::GetAvatar
        push 0x3ea
        mov  ebx, eax
        call FUN_008d2fb0
        add  esp, 4
        test al, al
        jne  L_ee70_main
        push 0x3e9
        call FUN_008d2fb0
        add  esp, 4
        test al, al
        je   L_ee70_main
        mov  eax, dword ptr [ebx + 0xc0]
        mov  edx, dword ptr [eax + 0x2c]
        lea  esi, [ebx + 0xc0]
        mov  ecx, esi
        call edx
        fld  dword ptr [eax + 8]
        movss xmm2, dword ptr [eax]
        fld  dword ptr [eax + 4]
        movss dword ptr [esp + 8], xmm2
        fld  dword ptr [esp + 8]
        lea  ecx, [esp + 0x18]
        fmul st, st(0)
        push ecx
        fld  st(1)
        mov  ecx, esi
        fmulp st(2), st
        faddp st(1), st
        fld  st(1)
        fmulp st(2), st
        faddp st(1), st
        fadd dword ptr [g_13ec4b8]
        fsqrt
        fld1
        fdivrp st(1), st
        fstp dword ptr [esp + 0xc]
        movss xmm0, dword ptr [esp + 0xc]
        movaps xmm1, xmm0
        mulss xmm1, xmm2
        movss dword ptr [esp + 0x10], xmm1
        movaps xmm1, xmm0
        mulss xmm1, dword ptr [eax + 4]
        mulss xmm0, dword ptr [eax + 8]
        mov  eax, dword ptr [esi]
        mov  edx, dword ptr [eax + 0x5c]
        movss dword ptr [esp + 0x14], xmm1
        movss dword ptr [esp + 0x18], xmm0
        call edx
        mov  edx, dword ptr [eax]
        mov  ecx, dword ptr [esp + 0x28]
        movss xmm1, dword ptr [esp + 0x10]
        movss xmm3, dword ptr [esp + 0x14]
        mov  dword ptr [ecx], edx
        mov  edx, dword ptr [eax + 4]
        mov  dword ptr [ecx + 4], edx
        mov  eax, dword ptr [eax + 8]
        mov  dword ptr [ecx + 8], eax
        movss xmm4, dword ptr [ecx + 8]
        movss xmm5, dword ptr [ecx + 4]
        movss xmm6, dword ptr [ecx]
        movaps xmm0, xmm1
        mulss xmm0, xmm5
        movaps xmm2, xmm3
        mulss xmm2, xmm4
        addss xmm0, xmm2
        movss xmm2, dword ptr [esp + 0xc]
        movaps xmm7, xmm2
        mulss xmm7, xmm6
        addss xmm0, xmm7
        movaps xmm7, xmm2
        mulss xmm7, xmm0
        movss dword ptr [esp + 0x18], xmm7
        subss xmm6, dword ptr [esp + 0x18]
        movaps xmm7, xmm1
        mulss xmm7, xmm0
        movss dword ptr [esp + 0x1c], xmm7
        subss xmm5, dword ptr [esp + 0x1c]
        movaps xmm7, xmm3
        mulss xmm7, xmm0
        subss xmm4, xmm7
        movss dword ptr [esp + 0x14], xmm4
        fld  dword ptr [esp + 0x14]
        fmul st, st(0)
        movss dword ptr [esp + 0x10], xmm5
        fld  dword ptr [esp + 0x10]
        movss dword ptr [esp + 0xc], xmm6
        fmul st, st(0)
        faddp st(1), st
        fld  dword ptr [esp + 0xc]
        fmul st, st(0)
        faddp st(1), st
        fadd dword ptr [g_13ec4b8]
        fsqrt
        pop  esi
        pop  ebx
        fld1
        fdivrp st(1), st
        fstp dword ptr [esp]
        movss xmm7, dword ptr [esp]
        mulss xmm5, xmm7
        movss dword ptr [esp + 8], xmm5
        mov  eax, dword ptr [esp + 8]
        movaps xmm0, xmm7
        mulss xmm0, xmm6
        movss dword ptr [esp + 4], xmm0
        mov  edx, dword ptr [esp + 4]
        mov  dword ptr [ecx], edx
        mov  dword ptr [ecx + 4], eax
        mov  eax, dword ptr [esp + 0x24]
        mulss xmm4, xmm7
        movss dword ptr [esp + 0xc], xmm4
        mov  edx, dword ptr [esp + 0xc]
        mov  dword ptr [ecx + 8], edx
        movss xmm0, dword ptr [ecx + 4]
        movss xmm4, dword ptr [ecx + 8]
        movaps xmm6, xmm1
        mulss xmm6, xmm4
        movaps xmm5, xmm3
        mulss xmm5, xmm0
        subss xmm5, xmm6
        movss dword ptr [esp + 4], xmm5
        movss xmm5, dword ptr [ecx]
        mov  ecx, dword ptr [esp + 4]
        movaps xmm6, xmm2
        mulss xmm6, xmm4
        mulss xmm3, xmm5
        subss xmm6, xmm3
        mulss xmm1, xmm5
        mulss xmm2, xmm0
        mov  dword ptr [eax], ecx
        movss dword ptr [esp + 8], xmm6
        mov  edx, dword ptr [esp + 8]
        subss xmm1, xmm2
        movss dword ptr [esp + 0xc], xmm1
        mov  ecx, dword ptr [esp + 0xc]
        mov  dword ptr [eax + 4], edx
        mov  dword ptr [eax + 8], ecx
        add  esp, 0x1c
        ret
      L_ee70_main:
        push edi
        call FUN_0067dd10
        mov  edx, dword ptr [eax]
        mov  ecx, eax
        mov  eax, dword ptr [edx + 0x50]
        call eax
        mov  edx, dword ptr [eax]
        mov  ecx, eax
        mov  eax, dword ptr [edx + 0x1c]
        call eax
        mov  esi, dword ptr [esp + 0x30]
        mov  edi, dword ptr [esp + 0x2c]
        push esi
        push 0
        push edi
        push 0
        mov  ecx, eax
        call cViewer::GetCameraLocationInfo
        mov  edx, dword ptr [ebx + 0xc0]
        mov  eax, dword ptr [edx + 0x2c]
        lea  ecx, [ebx + 0xc0]
        call eax
        fld  dword ptr [eax + 8]
        movss xmm1, dword ptr [eax]
        fld  dword ptr [eax + 4]
        movss dword ptr [esp + 0xc], xmm1
        fld  dword ptr [esp + 0xc]
        movss xmm4, dword ptr [edi + 4]
        fmul st, st(0)
        movss xmm6, dword ptr [edi]
        fld  st(1)
        movss xmm5, dword ptr [edi + 8]
        fmulp st(2), st
        faddp st(1), st
        fld  st(1)
        fmulp st(2), st
        faddp st(1), st
        fld  dword ptr [g_13ec4b8]
        fadd st(1), st
        fxch st(1)
        fsqrt
        fld1
        fld  st(0)
        fdivrp st(2), st
        fxch st(1)
        fstp dword ptr [esp + 0xc]
        movss xmm3, dword ptr [esp + 0xc]
        movaps xmm0, xmm3
        mulss xmm0, xmm1
        movaps xmm1, xmm3
        mulss xmm1, dword ptr [eax + 4]
        mulss xmm3, dword ptr [eax + 8]
        movaps xmm2, xmm1
        mulss xmm2, xmm4
        movaps xmm7, xmm0
        mulss xmm7, xmm6
        addss xmm2, xmm7
        movaps xmm7, xmm5
        mulss xmm7, xmm3
        addss xmm2, xmm7
        movaps xmm7, xmm0
        mulss xmm7, xmm2
        movss dword ptr [esp + 0x1c], xmm7
        subss xmm6, dword ptr [esp + 0x1c]
        movaps xmm7, xmm1
        mulss xmm7, xmm2
        movss dword ptr [esp + 0x20], xmm7
        subss xmm4, dword ptr [esp + 0x20]
        movaps xmm7, xmm3
        movss dword ptr [esp + 0x10], xmm6
        fld  dword ptr [esp + 0x10]
        fmul st, st(0)
        mulss xmm7, xmm2
        subss xmm5, xmm7
        movss dword ptr [esp + 0x18], xmm5
        fld  dword ptr [esp + 0x18]
        fmul st, st(0)
        movss dword ptr [esp + 0x14], xmm4
        faddp st(1), st
        fld  dword ptr [esp + 0x14]
        fmul st, st(0)
        faddp st(1), st
        fadd st, st(2)
        fsqrt
        fdivr st, st(1)
        fstp dword ptr [esp + 0xc]
        movss xmm7, dword ptr [esp + 0xc]
        mulss xmm4, xmm7
        movaps xmm2, xmm7
        mulss xmm2, xmm6
        mulss xmm5, xmm7
        movss dword ptr [esp + 0x10], xmm2
        mov  ecx, dword ptr [esp + 0x10]
        mov  dword ptr [edi], ecx
        movss dword ptr [esp + 0x14], xmm4
        mov  edx, dword ptr [esp + 0x14]
        mov  dword ptr [edi + 4], edx
        movss dword ptr [esp + 0x18], xmm5
        mov  eax, dword ptr [esp + 0x18]
        mov  dword ptr [edi + 8], eax
        movss xmm6, dword ptr [esi]
        movss xmm4, dword ptr [esi + 4]
        movss xmm5, dword ptr [esi + 8]
        movaps xmm2, xmm1
        mulss xmm2, xmm4
        movaps xmm7, xmm6
        mulss xmm7, xmm0
        addss xmm2, xmm7
        movaps xmm7, xmm5
        mulss xmm7, xmm3
        addss xmm2, xmm7
        mulss xmm0, xmm2
        subss xmm6, xmm0
        movss dword ptr [esp + 0x10], xmm6
        fld  dword ptr [esp + 0x10]
        fmul st, st(0)
        mulss xmm3, xmm2
        subss xmm5, xmm3
        movss dword ptr [esp + 0x18], xmm5
        fld  dword ptr [esp + 0x18]
        fmul st, st(0)
        mulss xmm1, xmm2
        subss xmm4, xmm1
        movss dword ptr [esp + 0x14], xmm4
        faddp st(1), st
        pop  edi
        fld  dword ptr [esp + 0x10]
        fmul st, st(0)
        faddp st(1), st
        faddp st(2), st
        fxch st(1)
        fsqrt
        fdivp st(1), st
        fstp dword ptr [esp + 8]
        movss xmm1, dword ptr [esp + 8]
        movaps xmm0, xmm1
        mulss xmm0, xmm6
        mulss xmm4, xmm1
        movss dword ptr [esp + 0xc], xmm0
        mov  ecx, dword ptr [esp + 0xc]
        mulss xmm5, xmm1
        movss dword ptr [esp + 0x10], xmm4
        mov  edx, dword ptr [esp + 0x10]
        mov  dword ptr [esi], ecx
        movss dword ptr [esp + 0x14], xmm5
        mov  eax, dword ptr [esp + 0x14]
        mov  dword ptr [esi + 4], edx
        mov  dword ptr [esi + 8], eax
        pop  esi
        pop  ebx
        add  esp, 0x1c
        ret
    }
}

// =============================================================================================
// 00d2f2a0  GetScenarioTurnSpeed -- avatar arrives in eax (same-TU static helper)
// =============================================================================================
// Transported as __declspec(naked) __asm: the retail build expands the two `exp()` calls into
// inline x87 (fldl2e / f2xm1 / fscale) and interleaves them with the SSE sqrt/select, an
// instruction schedule MSVC will not reproduce from any C++ float expression (the equivalent C++
// form differs by ~195 bytes).  Transcribed from the retail instruction stream verbatim.
// @ 0x00d2f2a0  GetScenarioTurnSpeed
__declspec(naked) float GetScenarioTurnSpeed(void* avatar) {
    __asm {
        sub  esp, 0xc
        push esi
        mov  esi, eax
        add  esi, 0xc0
        mov  ecx, esi
        call FUN_00d20610
        fld  dword ptr [eax + 8]
        fld  dword ptr [eax + 4]
        mov  ecx, esi
        fld  dword ptr [eax]
        mov  eax, dword ptr [esi]
        fmul st, st(0)
        mov  edx, dword ptr [eax + 0xcc]
        fld  st(1)
        fmulp st(2), st
        faddp st(1), st
        fld  st(1)
        fmulp st(2), st
        faddp st(1), st
        fsqrt
        fstp dword ptr [esp + 0xc]
        call edx
        fstp dword ptr [esp + 4]
        mov  eax, dword ptr [esi]
        mov  edx, dword ptr [eax + 0xc8]
        mov  ecx, esi
        call edx
        fst  dword ptr [esp + 8]
        fld  dword ptr [esp + 4]
        pop  esi
        fcomip st, st(1)
        fstp st(0)
        lea  eax, [esp]
        ja   L_f2a0_pick
        lea  eax, [esp + 4]
      L_f2a0_pick:
        fld  dword ptr [eax]
        fabs
        fmul dword ptr [g_1582bc0]
        fld  dword ptr [esp + 8]
        fcomi st, st(1)
        jbe  L_f2a0_exp
        fstp st(1)
        fstp st(0)
        fld  dword ptr [g_1582bb4]
        add  esp, 0xc
        ret
      L_f2a0_exp:
        fld  dword ptr [g_1582bc4]
        fld  dword ptr [g_1582bb4]
        fdiv st(1), st
        fld1
        fld  st(0)
        fsub st, st(3)
        fxch st(5)
        fldl2e
        fmulp st(1), st
        fld  st(0)
        frndint
        fxch st(1)
        fsub st, st(1)
        f2xm1
        fld1
        faddp st(1), st
        fscale
        fstp st(1)
        fsubrp st(1), st
        fdivp st(4), st
        fxch st(2)
        fldl2e
        fmulp st(1), st
        fld  st(0)
        frndint
        fxch st(1)
        fsub st, st(1)
        f2xm1
        fld1
        faddp st(1), st
        fscale
        fstp st(1)
        fmul st, st(3)
        fxch st(1)
        fsubrp st(3), st
        faddp st(2), st
        fmulp st(1), st
        add  esp, 0xc
        ret
    }
}

// =============================================================================================
// 00d2f3c0  cCmp7::FUN_00d2f3c0 -- sort comparator over two objects' projected positions
// =============================================================================================
struct cCmp7 {
    float f0, f1, f2, f3, f4, f5, f6;
    bool FUN_00d2f3c0(IObjRef* a, IObjRef* b);
};

// Transported as __declspec(naked) __asm: 613 bytes of scheduled x87 (double sqrt + a select
// dance built from fcomip/lahf/jp) plus SSE prologue that MSVC's x87 scheduler arranges
// differently from any equivalent float expression (~380 differing bytes in the C++ form).
// @ 0x00d2f3c0  cCmp7::FUN_00d2f3c0
__declspec(naked) bool cCmp7::FUN_00d2f3c0(IObjRef* a, IObjRef* b) {
    __asm {
        sub  esp, 0x28
        push ebx
        mov  ebx, dword ptr [esp + 0x30]
        mov  eax, dword ptr [ebx]
        mov  edx, dword ptr [eax + 0x2c]
        push esi
        mov  esi, ecx
        push edi
        mov  ecx, ebx
        call edx
        fld  dword ptr [eax]
        fsub dword ptr [esi]
        mov  edi, dword ptr [esp + 0x3c]
        mov  ecx, edi
        fstp dword ptr [esp + 0x1c]
        fld  dword ptr [eax + 4]
        fsub dword ptr [esi + 4]
        fstp dword ptr [esp + 0x20]
        fld  dword ptr [eax + 8]
        mov  eax, dword ptr [edi]
        fsub dword ptr [esi + 8]
        mov  edx, dword ptr [eax + 0x2c]
        fstp dword ptr [esp + 0x24]
        call edx
        fld  dword ptr [eax]
        movss xmm0, dword ptr [g_13f9428]
        fsub dword ptr [esi]
        fst  dword ptr [esp + 0x28]
        fld  dword ptr [eax + 4]
        fsub dword ptr [esi + 4]
        fst  dword ptr [esp + 0x2c]
        fld  dword ptr [eax + 8]
        fsub dword ptr [esi + 8]
        fst  dword ptr [esp + 0x30]
        fld  dword ptr [esp + 0x24]
        fmul st, st(0)
        fld  dword ptr [esp + 0x20]
        fmul st, st(0)
        faddp st(1), st
        fld  dword ptr [esp + 0x1c]
        fmul st, st(0)
        faddp st(1), st
        fsqrt
        fst  dword ptr [esp + 0x38]
        fld  st(1)
        fmulp st(2), st
        fld  st(2)
        fmulp st(3), st
        fxch st(1)
        faddp st(2), st
        fld  st(2)
        fmulp st(3), st
        fxch st(1)
        faddp st(2), st
        fxch st(1)
        fsqrt
        fstp dword ptr [esp + 0x3c]
        fldz
        fxch st(1)
        fucomip st, st(1)
        fstp st(0)
        lahf
        test ah, 0x44
        jp   L_cmp1
        movss dword ptr [esp + 0x38], xmm0
      L_cmp1:
        movss xmm5, dword ptr [esp + 0x3c]
        xorps xmm7, xmm7
        ucomiss xmm5, xmm7
        lahf
        test ah, 0x44
        jp   L_cmp2
        movaps xmm5, xmm0
        movss dword ptr [esp + 0x3c], xmm5
      L_cmp2:
        movss xmm1, dword ptr [g_1485720]
        movss xmm4, dword ptr [esp + 0x24]
        movss xmm6, dword ptr [esp + 0x30]
        mov  eax, dword ptr [ebx]
        mov  edx, dword ptr [eax + 0x74]
        movaps xmm0, xmm1
        divss xmm0, dword ptr [esp + 0x38]
        mulss xmm4, xmm0
        movaps xmm2, xmm0
        mulss xmm2, dword ptr [esp + 0x1c]
        movaps xmm3, xmm0
        mulss xmm3, dword ptr [esp + 0x20]
        movaps xmm0, xmm1
        divss xmm0, xmm5
        movss xmm5, dword ptr [esp + 0x2c]
        movaps xmm1, xmm0
        mulss xmm1, dword ptr [esp + 0x28]
        mulss xmm1, dword ptr [esi + 0xc]
        mulss xmm5, xmm0
        mulss xmm6, xmm0
        movss xmm0, dword ptr [esi + 0x14]
        mulss xmm0, xmm4
        movss xmm4, dword ptr [esi + 0x10]
        mulss xmm4, xmm3
        movss xmm3, dword ptr [esi + 0xc]
        addss xmm0, xmm4
        mulss xmm3, xmm2
        movss xmm2, dword ptr [g_1582d18]
        addss xmm0, xmm3
        movss xmm3, dword ptr [esi + 0x10]
        mulss xmm0, xmm2
        movss dword ptr [esp + 0x14], xmm0
        movss xmm0, dword ptr [esi + 0x14]
        mulss xmm0, xmm6
        mulss xmm3, xmm5
        addss xmm0, xmm3
        addss xmm0, xmm1
        mulss xmm0, xmm2
        mov  ecx, ebx
        movss dword ptr [esp + 0x18], xmm0
        movss dword ptr [esp + 0xc], xmm7
        call edx
        fsubr dword ptr [esp + 0x38]
        lea  eax, [esp + 0xc]
        fst  dword ptr [esp + 0x10]
        fldz
        fcomip st, st(1)
        fstp st(0)
        ja   L_cmp3
        lea  eax, [esp + 0x10]
      L_cmp3:
        movss xmm1, dword ptr [eax]
        divss xmm1, dword ptr [esi + 0x18]
        movss xmm0, dword ptr [g_1485720]
        mov  eax, dword ptr [edi]
        mov  edx, dword ptr [eax + 0x74]
        subss xmm0, xmm1
        mulss xmm0, dword ptr [g_1582d14]
        movss dword ptr [esp + 0x38], xmm0
        xorps xmm0, xmm0
        mov  ecx, edi
        movss dword ptr [esp + 0x10], xmm0
        call edx
        fsubr dword ptr [esp + 0x3c]
        lea  eax, [esp + 0x10]
        fst  dword ptr [esp + 0x3c]
        fldz
        fcomip st, st(1)
        fstp st(0)
        ja   L_cmp4
        lea  eax, [esp + 0x3c]
      L_cmp4:
        movss xmm1, dword ptr [eax]
        divss xmm1, dword ptr [esi + 0x18]
        movss xmm0, dword ptr [g_1485720]
        movss xmm2, dword ptr [esp + 0x14]
        addss xmm2, dword ptr [esp + 0x38]
        movss xmm3, dword ptr [g_147a5f4]
        subss xmm0, xmm1
        mulss xmm0, dword ptr [g_1582d14]
        addss xmm0, dword ptr [esp + 0x18]
        movaps xmm1, xmm0
        subss xmm1, xmm2
        comiss xmm3, xmm1
        jbe  L_cmp5
        comiss xmm1, dword ptr [g_13f89b8]
        jbe  L_cmp5
        cmp  ebx, edi
        pop  edi
        sbb  eax, eax
        pop  esi
        neg  eax
        pop  ebx
        add  esp, 0x28
        ret  8
      L_cmp5:
        comiss xmm2, xmm0
        jbe  L_cmp6
        pop  edi
        pop  esi
        mov  eax, 1
        pop  ebx
        add  esp, 0x28
        ret  8
      L_cmp6:
        pop  edi
        pop  esi
        xor  eax, eax
        pop  ebx
        add  esp, 0x28
        ret  8
    }
}

// =============================================================================================
// 00d2f630 / 00d2f710 / 00d2f880 -- insertion / sift sorts over refcounted IObjRef elements.
// The comparator is passed by value in the caller's argument slot, so the callee reaches it at
// the same stack address the retail build does (vs. an explicit pointer parameter).
//
// These three are transcribed as __declspec(naked) __asm.  The C++ forms below reproduce the
// retail control flow exactly (same register assignment, same basic blocks) yet differ by
// 15..210 bytes: MSVC 15.00's register allocator keeps the vtable pointer in edx (target in eax)
// after any preceding call, where the retail build (which interleaves both orders within the same
// function -- see FUN_00d2f710 at 0xd2f7ad vs 0xd2f734) keeps it in eax.  That choice is decided
// entirely by the allocator and cannot be steered from source (every member-call, VFN-cast,
// local-function-pointer, int* and char-temp form scores identically), so the retail instruction
// stream is used verbatim.  `call cCmp7::FUN_00d2f3c0` emits the same rel32 call the original has.
// =============================================================================================

// @ 0x00d2f630  FUN_00d2f630
__declspec(naked) void FUN_00d2f630(IObjRef** begin, IObjRef** end, cCmp7 cmp) {
    __asm {
        push ecx
        mov  eax, dword ptr [esp + 0xc]
        push edi
        mov  edi, dword ptr [esp + 0xc]
        cmp  edi, eax
        je   L_f630_pop_ret
        push ebx
        lea  ebx, [edi + 4]
        mov  dword ptr [esp + 8], ebx
        cmp  ebx, eax
        je   L_f630_pop_ebx
        push ebp
        push esi
        jmp  L_f630_loop
      L_f630_continue:
        mov  edi, dword ptr [esp + 0x18]
      L_f630_loop:
        mov  ebp, dword ptr [ebx]
        test ebp, ebp
        je   L_f630_after_vbc
        mov  eax, dword ptr [ebp]
        mov  edx, dword ptr [eax + 0xbc]
        mov  ecx, ebp
        call edx
      L_f630_after_vbc:
        mov  esi, ebx
        cmp  ebx, edi
        je   L_f630_shrink
      L_f630_inner:
        mov  eax, dword ptr [esi - 4]
        push eax
        push ebp
        lea  ecx, [esp + 0x28]
        call cCmp7::FUN_00d2f3c0
        test al, al
        je   L_f630_shrink
        mov  edi, dword ptr [esi - 4]
        mov  ebx, dword ptr [esi]
        cmp  edi, ebx
        je   L_f630_next
        test edi, edi
        je   L_f630_store_b
        mov  eax, dword ptr [edi]
        mov  edx, dword ptr [eax + 0xbc]
        mov  ecx, edi
        call edx
      L_f630_store_b:
        mov  dword ptr [esi], edi
        test ebx, ebx
        je   L_f630_next
        mov  eax, dword ptr [ebx]
        mov  edx, dword ptr [eax + 0xc0]
        mov  ecx, ebx
        call edx
      L_f630_next:
        mov  ebx, dword ptr [esp + 0x10]
        add  esi, -4
        cmp  esi, dword ptr [esp + 0x18]
        jne  L_f630_inner
      L_f630_shrink:
        mov  edi, dword ptr [esi]
        cmp  ebp, edi
        je   L_f630_final_c0
        test ebp, ebp
        je   L_f630_store_cur
        mov  eax, dword ptr [ebp]
        mov  edx, dword ptr [eax + 0xbc]
        mov  ecx, ebp
        call edx
      L_f630_store_cur:
        mov  dword ptr [esi], ebp
        test edi, edi
        je   L_f630_final_c0
        mov  eax, dword ptr [edi]
        mov  edx, dword ptr [eax + 0xc0]
        mov  ecx, edi
        call edx
      L_f630_final_c0:
        test ebp, ebp
        je   L_f630_advance
        mov  eax, dword ptr [ebp]
        mov  edx, dword ptr [eax + 0xc0]
        mov  ecx, ebp
        call edx
      L_f630_advance:
        add  ebx, 4
        mov  dword ptr [esp + 0x10], ebx
        cmp  ebx, dword ptr [esp + 0x1c]
        jne  L_f630_continue
        pop  esi
        pop  ebp
      L_f630_pop_ebx:
        pop  ebx
      L_f630_pop_ret:
        pop  edi
        pop  ecx
        ret
    }
}

// @ 0x00d2f710  FUN_00d2f710
__declspec(naked) void FUN_00d2f710(IObjRef** begin, IObjRef** end, cCmp7 cmp) {
    __asm {
        push ecx
        push ebp
        mov  ebp, dword ptr [esp + 0xc]
        mov  dword ptr [esp + 4], ebp
        cmp  ebp, dword ptr [esp + 0x10]
        je   L_f710_pop2
        push ebx
        push esi
        push edi
      L_f710_top:
        mov  ebx, dword ptr [ebp]
        mov  esi, ebp
        mov  dword ptr [esp + 0x18], ebx
        test ebx, ebx
        je   L_f710_precmp2
        mov  eax, dword ptr [ebx]
        mov  edx, dword ptr [eax + 0xbc]
        mov  ecx, ebx
        call edx
      L_f710_precmp2:
        mov  eax, dword ptr [ebp - 4]
        lea  edi, [ebp - 4]
        push eax
        push ebx
        lea  ecx, [esp + 0x28]
        call cCmp7::FUN_00d2f3c0
        test al, al
        je   L_f710_tail
      L_f710_inner:
        mov  ebx, dword ptr [edi]
        mov  ebp, dword ptr [esi]
        cmp  ebx, ebp
        je   L_f710_after_inner
        test ebx, ebx
        je   L_f710_sib
        mov  eax, dword ptr [ebx]
        mov  edx, dword ptr [eax + 0xbc]
        mov  ecx, ebx
        call edx
      L_f710_sib:
        mov  dword ptr [esi], ebx
        test ebp, ebp
        je   L_f710_after_inner
        mov  eax, dword ptr [ebp]
        mov  edx, dword ptr [eax + 0xc0]
        mov  ecx, ebp
        call edx
      L_f710_after_inner:
        mov  esi, edi
        mov  eax, dword ptr [esi - 4]
        lea  edi, [esi - 4]
        push eax
        mov  eax, dword ptr [esp + 0x1c]
        push eax
        lea  ecx, [esp + 0x28]
        call cCmp7::FUN_00d2f3c0
        test al, al
        jne  L_f710_inner
        mov  ebp, dword ptr [esp + 0x10]
        mov  ebx, dword ptr [esp + 0x18]
      L_f710_tail:
        mov  edi, dword ptr [esi]
        cmp  ebx, edi
        je   L_f710_final
        test ebx, ebx
        je   L_f710_st
        mov  edx, dword ptr [ebx]
        mov  eax, dword ptr [edx + 0xbc]
        mov  ecx, ebx
        call eax
      L_f710_st:
        mov  dword ptr [esi], ebx
        test edi, edi
        je   L_f710_final
        mov  edx, dword ptr [edi]
        mov  eax, dword ptr [edx + 0xc0]
        mov  ecx, edi
        call eax
      L_f710_final:
        test ebx, ebx
        je   L_f710_adv
        mov  edx, dword ptr [ebx]
        mov  eax, dword ptr [edx + 0xc0]
        mov  ecx, ebx
        call eax
      L_f710_adv:
        add  ebp, 4
        mov  dword ptr [esp + 0x10], ebp
        cmp  ebp, dword ptr [esp + 0x1c]
        jne  L_f710_top
        pop  edi
        pop  esi
        pop  ebx
      L_f710_pop2:
        pop  ebp
        pop  ecx
        ret
    }
}

// @ 0x00d2f880  FUN_00d2f880
__declspec(naked) void FUN_00d2f880(IObjRef** arr, int start, int pos, IObjRef* val, cCmp7 cmp) {
    __asm {
        push ebx
        push ebp
        mov  ebp, dword ptr [esp + 0xc]
        push esi
        mov  esi, dword ptr [esp + 0x18]
        push edi
        lea  edi, [esi - 1]
        sar  edi, 1
        cmp  esi, dword ptr [esp + 0x18]
        jle  L_f880_tail
      L_f880_body:
        mov  ecx, dword ptr [esp + 0x20]
        mov  eax, dword ptr [ebp + edi*4]
        push ecx
        push eax
        lea  ecx, [esp + 0x2c]
        call cCmp7::FUN_00d2f3c0
        test al, al
        je   L_f880_tail
        mov  ecx, dword ptr [ebp + esi*4]
        mov  ebx, dword ptr [ebp + edi*4]
        mov  dword ptr [esp + 0x1c], ecx
        cmp  ebx, ecx
        je   L_f880_adv
        test ebx, ebx
        je   L_f880_skip
        mov  edx, dword ptr [ebx]
        mov  eax, dword ptr [edx + 0xbc]
        mov  ecx, ebx
        call eax
        mov  ecx, dword ptr [esp + 0x1c]
      L_f880_skip:
        mov  dword ptr [ebp + esi*4], ebx
        test ecx, ecx
        je   L_f880_adv
        mov  edx, dword ptr [ecx]
        mov  eax, dword ptr [edx + 0xc0]
        call eax
      L_f880_adv:
        mov  esi, edi
        dec  edi
        sar  edi, 1
        cmp  esi, dword ptr [esp + 0x18]
        jg   L_f880_body
      L_f880_tail:
        mov  ecx, dword ptr [esp + 0x20]
        mov  edi, dword ptr [ebp + esi*4]
        mov  ebx, ecx
        cmp  ecx, edi
        je   L_f880_epi
        test ecx, ecx
        je   L_f880_set
        mov  edx, dword ptr [ecx]
        mov  eax, dword ptr [edx + 0xbc]
        call eax
        mov  ecx, dword ptr [esp + 0x20]
      L_f880_set:
        mov  dword ptr [ebp + esi*4], ebx
        test edi, edi
        je   L_f880_epi
        mov  edx, dword ptr [edi]
        mov  eax, dword ptr [edx + 0xc0]
        mov  ecx, edi
        call eax
        mov  ecx, dword ptr [esp + 0x20]
      L_f880_epi:
        pop  edi
        pop  esi
        pop  ebp
        pop  ebx
        test ecx, ecx
        je   L_f880_ret
        mov  edx, dword ptr [ecx]
        mov  eax, dword ptr [edx + 0xc0]
        jmp  eax
      L_f880_ret:
        ret
    }
}