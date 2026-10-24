// Slice s00c0ce80 - cCreatureBase animation / hunger helpers.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <math.h>

typedef void* P;

// ---- externals --------------------------------------------------------
void* __cdecl SP_GetCurrentGameMode();                    // 0x00b5b800
void* __cdecl FUN_00c03260(void*, int);                   // 0x00c03260
int   __cdecl FUN_00b3d230();                             // 0x00b3d230
void* __cdecl SP_GameTimeManager();                       // 0x00b3d380
void  __cdecl FUN_00bc86e0(double, void*, void*, void*, int, int); // 0x00bc86e0

struct F_ce30   { int   __thiscall f(int, int); };        // 0x00c0ce30
struct F_f31500 { float __thiscall f(); };                // 0x00f31500
struct F_a02bf0 { void  __thiscall f(int, int); };        // 0x00a02bf0
struct F_a062a0 { void  __thiscall f(int, int); };        // 0x00a062a0
struct F_a06250 { void  __thiscall f(int); };             // 0x00a06250
struct F_c0b9d0 { void  __thiscall f(float); };           // 0x00c0b9d0
struct F_b316c0 { long long __thiscall f(); };            // 0x00b316c0
struct F_a05270 { void  __thiscall Release(); };          // 0x00a05270
struct F_a048a0 { float* __thiscall f(); };                // 0x00a048a0
struct F_c0c080 { int   __thiscall f(int); };              // 0x00c0c080
struct F_b1daf0 { void* __thiscall f(); };                 // 0x00b1daf0
struct F_41ea70 { float* __thiscall f(); };                // 0x0041ea70
struct F_c88670 { void  __thiscall f(float*); };           // 0x00c88670
struct F_terrain { char __thiscall q(int, void*); };        // 0x00b1daf0 result
struct F_d9030 {
    int* __thiscall f(void*);                              // 0x004d9030
};
// note: 0x004d9030 is a thiscall wrapper (ret 4) around SpeciesProfile::GetVariantB
void* __cdecl FUN_00b3d320(void*);                         // 0x00b3d320
float* __cdecl FUN_0099c1a0(void*, void*, void*);          // 0x0099c1a0

struct F_timer {
    bool      __thiscall IsRunning();                     // 0x00feba90
    long long __thiscall GetElapsedTime();                // 0x00bc3190
    void      __thiscall Stop();                          // 0x00bc3110
    void      __thiscall Restart();                       // 0x00bc3130
};

#define G32(a)  (*(uint32_t*)(a))
#define GF(a)   (*(float*)(a))

struct CCB {
    float __thiscall ce80(int, int);
    void  __thiscall cf50();
    float __thiscall cfa0(int, char);
    void  __thiscall cff0(int);
    int   __thiscall d050(float);
    void  __thiscall d0c0(uint32_t, char);
    void  __thiscall d1e0(int);
    void  __thiscall d200(int, int);
    void  __thiscall d240();
    float* __thiscall d310(float*, int);
    void  __thiscall d340(int);
    void  __thiscall UpdateHunger(float);
    bool  __thiscall d560(int, float, float);
    void  __thiscall d660(float*);
    void  __thiscall d860(float*);
    void  __thiscall d950(char);
    void  __thiscall d970(float*);
    void  __thiscall d9b0();
    int   __thiscall dac0();
    int   __thiscall db10();
    int   __thiscall db60();
    void  __thiscall dd40(float*);
    void  __thiscall dd70(float*, float);
};

float __cdecl FUN_00c0db80(float, int);   // 0x00c0db80
float __cdecl FUN_00c0dcb0(float);        // 0x00c0dcb0

// ======================================================================
// @ 0x00c0ce80
float __thiscall CCB::ce80(int index, int flag) {
    if (index == 0) return 0.0f;
    int iVar2 = ((F_ce30*)this)->f(index, flag);
    void* gm = SP_GetCurrentGameMode();
    float local_4;
    if (gm == (void*)0x1654c10) {   // needs the dword at 0x1654c10 (DAT_01654c10)
        void* r = FUN_00c03260(this, iVar2);
        local_4 = ((F_f31500*)r)->f();
    } else {
        local_4 = GF(0x15d9650 + iVar2 * 4);
    }
    if ((*(char(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x58 / 4]))((char*)this + 0xc0)) {
        float p = local_4;
        if (iVar2 + 1U < 6) p = GF(0x15d9654 + iVar2 * 4);
        else if (iVar2 != 0) p = GF(0x15d964c + iVar2 * 4);
        return fabsf(local_4 - p) * GF(0x1471064) + local_4;
    }
    return local_4;
}

// ======================================================================
// @ 0x00c0cf50
void __thiscall CCB::cf50() {
    G32((char*)this + 0xfa8) = 0;
    GF((char*)this + 0xfac) = ce80(1, 1);
    GF((char*)this + 0xfb0) = ce80(2, 1);
    GF((char*)this + 0xfb4) = ce80(3, 1);
    G32((char*)this + 0x2a4) = G32((char*)this + 0xfb0);
}

// ======================================================================
// @ 0x00c0cfa0
float __thiscall CCB::cfa0(int index, char flag) {
    if (*(char*)((char*)this + 0xbb0) != 0)
        return ce80(2, 1) + GF(0x150c900);
    if (flag != 0)
        return GF((char*)this + 0xfa8 + index * 4);
    return ce80(index, 0);
}

// ======================================================================
// @ 0x00c0cff0
void __thiscall CCB::cff0(int param) {
    G32((char*)this + 0xf98) = param;
    float v;
    if (*(char*)((char*)this + 0xbb0) != 0)
        v = ce80(2, 1) + GF(0x150c900);
    else
        v = ce80(param, 0);
    GF((char*)this + 0x2a0) = v;
}

// ======================================================================
// @ 0x00c0d050
int __thiscall CCB::d050(float param) {
    int iVar1 = 0;
    do {
        if (iVar1 != 1) {
            float f;
            if (*(char*)((char*)this + 0xbb0) == 0) f = ce80(iVar1, 0);
            else f = ce80(2, 1) + GF(0x150c900);
            if (f >= param) return iVar1;
        }
        ++iVar1;
        if (iVar1 > 3) return 3;
    } while (true);
}

// ======================================================================
// @ 0x00c0d0c0
void __thiscall CCB::d0c0(uint32_t param_2, char param_3) {
    bool bVar3;
    if (param_2 < 8) {
        uint32_t bit = 1u << (param_2 & 0x1f);
        bVar3 = (G32((char*)this + 0xfa4) & bit) != 0;
        if (param_3 == 0) G32((char*)this + 0xfa4) &= ~bit;
        else G32((char*)this + 0xfa4) |= bit;
    } else bVar3 = false;
    if (param_3 == bVar3) return;
    int iVar1 = (param_3 == 0 || bVar3) ? -1 : 1;
    int* pfa0 = (int*)((char*)this + 0xfa0);
    switch (param_2) {
    case 0: *pfa0 += iVar1; break;
    case 1: case 2: case 3: *pfa0 -= iVar1; break;
    case 4: iVar1 = -iVar1 * 2; *pfa0 += iVar1; break;
    case 5: *pfa0 += (*(int*)((char*)*(void**)((char*)this + 0xb20) + 0x5d0)) * iVar1; break;
    case 6: iVar1 = -iVar1 * 4; *pfa0 += iVar1; break;
    case 7: *pfa0 += iVar1 * 2; break;
    }
    float v;
    if (*(char*)((char*)this + 0xbb0) == 0) v = ce80(G32((char*)this + 0xf98), 0);
    else v = ce80(2, 1) + GF(0x150c900);
    GF((char*)this + 0x2a0) = v;
}

// ======================================================================
// @ 0x00c0d1e0
void __thiscall CCB::d1e0(int param) {
    void* p = *(void**)((char*)this + 0xb54);
    if (p != 0) ((F_a02bf0*)p)->f(param, 1);
}

// ======================================================================
// @ 0x00c0d200
void __thiscall CCB::d200(int param_2, int param_3) {
    if (*(int*)((char*)this + 0xb54) != 0) {
        void* eax = *(void**)((char*)param_2 + 0xb54);
        if (eax != 0) {
            void* ths = *(void**)((char*)this + 0xb54);
            if (param_3 != -1) ((F_a062a0*)ths)->f((int)eax, param_3);
            else ((F_a06250*)ths)->f((int)eax);
        }
    }
}

// ======================================================================
// @ 0x00c0d240  SP::cSPCreatureBase::IsAnimationQueuedOrCurrent
void __thiscall CCB::d240() {
    void* p = *(void**)((char*)this + 0xb54);
    if (p != 0) {
        float local_14 = *(float*)((char*)p + 0x3c) * GF(0x1473c70);
        float r = (*(float(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x74 / 4]))((char*)this + 0xc0);
        float af[2]; af[0] = r;
        float* pf = &local_14;
        if (local_14 <= r) pf = af;
        float neg = -(*pf);
        *(uint32_t*)((char*)p + 0x154) = 1;
        void* q = *(void**)((char*)this + 0xb54);
        *(uint32_t*)((char*)q + 0x164) = 0;
        *(float*)((char*)q + 0x168) = neg;
        *(uint32_t*)((char*)q + 0x16c) = 0;
        void* r2 = *(void**)((char*)this + 0xb54);
        if (*(int*)((char*)r2 + 0x15c) != 0) {
            void* contained = *(void**)((char*)r2 + 0x15c);
            *(uint32_t*)((char*)r2 + 0x15c) = 0;
            ((F_a05270*)contained)->Release();
        }
    }
    *(uint8_t*)((char*)this + 0xb66) = 0;
}

// ======================================================================
// @ 0x00c0d310
float* __thiscall CCB::d310(float* param_2, int param_3) {
    float* pu = (float*)(*(void*(__thiscall*)(void*))((*(void***)((char*)this + 0x8c))[0x2c / 4]))((char*)this + 0x8c);
    param_2[0] = pu[0];
    param_2[1] = pu[1];
    param_2[2] = pu[2];
    return param_2;
}

// ======================================================================
// @ 0x00c0d340
void __thiscall CCB::d340(int param_2) {
    void* iVar2 = *(void**)((char*)param_2 + 0x34);
    *(uint32_t*)((char*)param_2 + 0x130) = 0;
    float* u = (float*)(*(float*(__thiscall**)(void*))((*(void***)((char*)this + 0x8c))[0x2c / 4]))((char*)this + 0x8c);
    void* self2 = (char*)param_2 + 0x34;
    (*(void(__thiscall**)(void*, void*))(*(void**)((char*)iVar2 + 0x38)))(self2, u);
    void* piVar3 = *(void**)((char*)this + 0x18);
    void* piVar1 = (char*)this - 0x34;
    if (piVar1 != piVar3) {
        if (piVar1) (*(void(__thiscall**)(void*))((*(void***)piVar1)[0]))(piVar1);
        *(void**)((char*)this + 0x18) = piVar1;
        if (piVar3) (*(void(__thiscall**)(void*))((*(void***)piVar3)[1]))(piVar3);
    }
}

// ======================================================================
// @ 0x00c0d3a0
void __cdecl FUN_00c0d3a0(int param_1) {
    if (*(void**)(param_1 + 0xb4c) != 0 && **(int**)(param_1 + 0xb4c) != 0) {
        if (FUN_00b3d230() != 0) {
            if (SP_GameTimeManager() != 0) {
                void* g = SP_GameTimeManager();
                unsigned long long u = (unsigned long long)((F_b316c0*)g)->f();
                void* pu = *(void**)(param_1 + 0xb4c);
                double d = 0.0;
                if ((long long)u < 0) d = (double)(long long)u; else d = (double)u;
                FUN_00bc86e0(d * 0.001f, pu, (void*)param_1, (char*)pu + 0x1d0,
                             *(int*)((char*)pu + 0x5e8), *(int*)((char*)pu + 0x5fc));
            }
        }
    }
}

// ======================================================================
// @ 0x00c0d440  Simulator::cCreatureBase::UpdateHunger
void __thiscall CCB::UpdateHunger(float param) {
    if (!(*(char(__thiscall**)(void*))((*(void***)((char*)this + 0xc0))[0x58 / 4]))((char*)this + 0xc0)) return;
    if (((G32((char*)this + 0xb58) >> 8) & 1) != 0) return;
    if (SP_GetCurrentGameMode() == (void*)0x1654c10) return;
    F_timer* pcVar1 = (F_timer*)((char*)this + 0xb90);
    float fVar6;
    if (pcVar1->IsRunning()) {
        long long u = pcVar1->GetElapsedTime();
        if ((int)((unsigned long long)u >> 32) == 0 && G32((char*)this + 0xb8c) > (uint32_t)u) {
            fVar6 = GF(0x1687a00);
        } else goto LAB_d4b5;
    } else {
    LAB_d4b5:
        if (!pcVar1->IsRunning() && GF((char*)this + 0xbbc) == GF(0x1687a00)) {
            if (*(int*)((char*)this + 0xb34) == 1) pcVar1->Restart();
            goto LAB_d511;
        }
        pcVar1->Stop();
        fVar6 = GF((char*)this + 0xbb8) * param + GF((char*)this + 0xbbc);
    }
    ((F_c0b9d0*)this)->f(fVar6);
LAB_d511:
    if (GF((char*)this + 0xbbc) < 1.0f) {
        void* vt = *(void**)((char*)this + 0x5a8);
        float x = GF(0x1687a1c) * param;
        (*(void(__thiscall**)(void*, float, int, int, int, int))(*(void**)((char*)vt + 0x18)))(
            (char*)this + 0x5a8, x, -1, 5, 0x168d910, 0);
    }
}

// ======================================================================
// @ 0x00c0d560
bool __thiscall CCB::d560(int other, float scale, float dist) {
    if (GF((char*)other + 0xb80) <= 0.0f) return false;
    void* e = *(void**)((char*)this + 0xe84);
    float thr;
    if (e == 0) thr = GF(0x150c8b4);
    else {
        float v = GF((char*)e + 0x354);
        if (v < 0.0f) thr = GF(0x150c8b4);
        else thr = v;
    }
    thr = thr * scale + GF((char*)other + 0xb80);
    if (fabsf(dist) <= 0.0f) {
        float* p1 = (float*)(*(void*(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x2c / 4]))((char*)this + 0xc0);
        float* p2 = (float*)(*(void*(__thiscall*)(void*))((*(void***)((char*)other + 0xc0))[0x2c / 4]))((char*)other + 0xc0);
        float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
        float d = sqrtf(dx * dx + dy * dy + dz * dz + GF(0x13ec4b8));
        float r2 = (*(float(__thiscall*)(void*))((*(void***)((char*)other + 0xc0))[0x74 / 4]))((char*)other + 0xc0);
        float r1 = (*(float(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x74 / 4]))((char*)this + 0xc0);
        if (d - (r2 + r1) < thr) return true;
    } else if (dist < thr) return true;
    return false;
}

// ======================================================================
// @ 0x00c0d660
void __thiscall CCB::d660(float* param_2) {
    int* pi = ((F_d9030*)*(void**)((char*)this + 0xb20))->f(*(void**)((char*)this + 0xb54));
    if (pi[0] == pi[1]) {
        void* self = (char*)this + 0xc0;
        char* eax = (char*)(*(void*(__thiscall*)(void*))((*(void***)self)[0x68 / 4]))(self);
        float fv = (GF(eax + 0x14) - GF(eax + 8)) * GF(0x13ec4b0);
        float fwd[3];
        (*(void(__thiscall*)(void*, float*))((*(void***)self)[0x5c / 4]))(self, fwd);
        float* p1 = (float*)(*(void*(__thiscall*)(void*))((*(void***)self)[0x2c / 4]))(self);
        float inv = 1.0f / sqrtf(p1[0] * p1[0] + p1[1] * p1[1] + p1[2] * p1[2] + GF(0x13ec4b8));
        float* p2 = (float*)(*(void*(__thiscall*)(void*))((*(void***)self)[0x2c / 4]))(self);
        param_2[0] = p2[0] + (p1[0] * inv) * fv + fwd[0] * GF(0x13ec4b0);
        param_2[1] = p2[1] + (p1[1] * inv) * fv + fwd[1] * GF(0x13ec4b0);
        param_2[2] = p2[2] + (p1[2] * inv) * fv + fwd[2] * GF(0x13ec4b0);
    } else {
        int iVar9 = *(int*)(*(int*)((char*)this + 0xb54) + 0x17c);
        int* pu = ((F_d9030*)*(void**)((char*)this + 0xb20))->f(*(void**)((char*)this + 0xb54));
        int iVar10 = *(int*)(*(int*)((char*)this + 0xb54) + 0x17c);
        float local_c[3];
        float* pf = FUN_0099c1a0(local_c, (void*)(iVar10 + 0x3c),
                                  (void*)(*(int*)(*pu) * 0x2bc + *(int*)(iVar10 + 0x2e4) + 0x10));
        param_2[0] = pf[0] + GF(iVar9 + 0x18);
        param_2[1] = pf[1] + GF(iVar9 + 0x1c);
        param_2[2] = pf[2] + GF(iVar9 + 0x20);
    }
}

// ======================================================================
// @ 0x00c0d860
void __thiscall CCB::d860(float* param_2) {
    float* pf = ((F_a048a0*)(*(void**)((char*)this + 0xb54)))->f();
    float f1 = pf[0], f2 = pf[1], f3 = pf[2];
    float inv = 1.0f / sqrtf(f1 * f1 + f2 * f2 + f3 * f3 + GF(0x13ec4b8));
    char* iVar8 = (char*)(*(void*(__thiscall*)(void*))((*(void***)((char*)this + 0xc0))[0x68 / 4]))((char*)this + 0xc0);
    float f9 = GF(iVar8 + 0x14) + GF(0x13ec480);
    param_2[0] = pf[0] + (f1 * inv) * f9;
    param_2[1] = pf[1] + (f2 * inv) * f9;
    param_2[2] = pf[2] + (f3 * inv) * f9;
}

// ======================================================================
// @ 0x00c0d950
void __thiscall CCB::d950(char param_2) {
    *(uint8_t*)((char*)this + 0xb65) = (uint8_t)param_2;
    *(uint8_t*)((char*)*(void**)((char*)this + 0xb54) + 0x84) = (uint8_t)param_2;
}

// ======================================================================
// @ 0x00c0d970  Simulator::cCreatureBase::SetIdentityColor
void __thiscall CCB::d970(float* param_2) {
    char* p = *(char**)((char*)this + 0xb54);
    *(uint32_t*)(p + 0x74) = ((uint32_t*)param_2)[0];
    *(uint32_t*)(p + 0x78) = ((uint32_t*)param_2)[1];
    *(uint32_t*)(p + 0x7c) = ((uint32_t*)param_2)[2];
    char* q = *(char**)((char*)this + 0xb54);
    *(float*)(q + 0x80) = GF(0x1485720);
}

// ======================================================================
// @ 0x00c0d9b0
void __thiscall CCB::d9b0() {
    void* c = *(void**)((char*)this + 0xb54);
    void* b = *(void**)((char*)this + 0xb20);
    float f = GF((char*)c + 0x3c);
    float x = GF((char*)b + 0x554) * f;
    float y = GF((char*)b + 0x558) * f;
    float z = GF((char*)b + 0x55c);
    float fVar4 = x * -0.5f;
    float fVar5 = y * -0.5f;
    float fVar2 = z * f;
    void* self = (char*)this + 0xc0;
    float r = (*(float(__thiscall*)(void*))((*(void***)self)[0x34 / 4]))(self);
    float vec[6];
    vec[0] = fVar4; vec[1] = fVar5; vec[2] = 0.0f;
    vec[3] = -fVar4; vec[4] = -fVar5; vec[5] = fVar2;
    (*(void(__thiscall*)(void*, float*, float))((*(void***)self)[0x64 / 4]))(self, vec, 1.0f);
    G32((char*)self + 0x50) |= 0x20;
    GF((char*)this + 0x124) = r;
    GF((char*)this + 0x13c) = r;
}

// ======================================================================
// @ 0x00c0dac0
int __thiscall CCB::dac0() {
    int u = ((F_c0c080*)this)->f(0x25);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        u = ((F_c0c080*)this)->f(0x54);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        return ((F_c0c080*)this)->f(0x4d);
    return u;
}

// ======================================================================
// @ 0x00c0db10
int __thiscall CCB::db10() {
    int u = ((F_c0c080*)this)->f(0x1e);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        u = ((F_c0c080*)this)->f(0x3e);
    if ((*(int(__thiscall*)(void*, int))((*(void***)this)[0xb4 / 4]))(this, u) == 0)
        return ((F_c0c080*)this)->f(0x4a);
    return u;
}

// ======================================================================
// @ 0x00c0db60
int __thiscall CCB::db60() {
    if (*(int*)((char*)this + 0xa94) != 0)
        return *(int*)(*(int*)((char*)this + 0xa94) + 0x180);
    return *(int*)((char*)this + 0x9c);
}

// ======================================================================
// @ 0x00c0db80
float __cdecl FUN_00c0db80(float param_1, int param_2) {
    void* a = FUN_00b3d320(SP_GetCurrentGameMode());
    void* t = ((F_b1daf0*)a)->f();
    float local_c = GF(0x13ec4d0);
    float local_4 = GF(0x1486114);
    float local_10 = GF(0x1488874);
    float fVar7 = local_4;
    if (t != 0) {
        void* h = 0;
        if (((F_terrain*)t)->q(0x7422b3b, &h) && *(short*)((char*)h + 0x12) == 0xd)
            local_c = *((F_41ea70*)h)->f();
        h = 0;
        if (((F_terrain*)t)->q(0x760c17c, &h) && *(short*)((char*)h + 0x12) == 0xd) {
            local_4 = *((F_41ea70*)h)->f();
            fVar7 = local_4;
        }
        h = 0;
        if (((F_terrain*)t)->q(0x760c181, &h) && *(short*)((char*)h + 0x12) == 0xd)
            local_10 = *((F_41ea70*)h)->f();
    }
    float fVar8 = local_10 * param_1 * fVar7 * local_c + GF(param_2 + 0xe58);
    float* pf5 = (float*)(param_2 + 0xe58);
    float* pf6 = (float*)(param_2 + 0xe5c);
    *pf5 = fVar8;
    if (fVar8 > *pf6) *pf5 = *pf6;
    return param_1 - fVar7 * param_1;
}

// ======================================================================
// @ 0x00c0dcb0
float __cdecl FUN_00c0dcb0(float param_1) {
    void* a = FUN_00b3d320(SP_GetCurrentGameMode());
    void* t = ((F_b1daf0*)a)->f();
    float local_8 = GF(0x13eb8a0);
    if (t != 0) {
        void* h = 0;
        ((F_terrain*)t)->q(0x7422b3b, &h);
        h = 0;
        if (((F_terrain*)t)->q(0x760c184, &h) && *(short*)((char*)h + 0x12) == 0xd)
            local_8 = *((F_41ea70*)h)->f();
    }
    return param_1 - local_8 * param_1;
}

// ======================================================================
// @ 0x00c0dd40
void __thiscall CCB::dd40(float* param_2) {
    ((F_c88670*)this)->f(param_2);
    char* eax = *(char**)((char*)this + 0xa94);
    if (eax != 0) {
        *(int*)(eax + 4) = *(int*)param_2;
        *(int*)(eax + 8) = *(int*)((char*)param_2 + 4);
        *(int*)(eax + 0xc) = *(int*)((char*)param_2 + 8);
    }
}

// ======================================================================
// @ 0x00c0dd70
void __thiscall CCB::dd70(float* param_2, float param_3) {
    char* p = *(char**)((char*)this + 0xb54);
    if (p != 0) {
        *(int*)(p + 0x44) = *(int*)param_2;
        *(int*)(p + 0x48) = *(int*)((char*)param_2 + 4);
        *(int*)(p + 0x4c) = *(int*)((char*)param_2 + 8);
        char* q = *(char**)((char*)this + 0xb54);
        *(float*)(q + 0x40) = param_3;
    }
}
