// src/game/SPAudio/SPAudioAmbienceLayer.cpp -- migrated from slice(s) s00a35d20, s00a34e80 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioAmbienceLayer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>
#include <math.h>

// ---- items of slice s00a34e80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int   u32;
void* __cdecl operator_new(u32 size, const char* tag, int a3, int a4,
                           const char* file, int line);
void  __cdecl operator_delete__(void*);
void* __cdecl EA_Audio_GetSystemAT(void);                    // 0x00a206f0
void* __cdecl SP_App(void);                                  // SP::App
void* __cdecl FUN_SP_AudioSystem(void);                      // 0x0067cb00
void  __cdecl Memset32(void*, int, int);
void  __cdecl FUN_00621d50(void*, void*, void*);
void  __cdecl FUN_00621d10(void*, void*, void*);
void  __cdecl SetGlobalProperty(u32, float);                 // 0x005ca880
void* __cdecl FUN_011e0744(void*, void*, int);               // vector<bool> DoInsertValue
void  __cdecl FUN_00a1e320(void*, void*);
void  __cdecl FUN_00a1b6c0(void*, void*, void*);
void  __cdecl FUN_00a26ce0(void*, void*, void*);
void  __cdecl FUN_find(void*, u32, void*, void*);
struct Str10 { void assign(const char* s, const char* e); };
template<class R, class A1> static inline R vt(void* o, int off, A1 a1)
{ return ((R (__thiscall*)(void*, A1))(*(void***)o)[off / 4])(o, a1); }
template<class R> static inline R vt0(void* o, int off)
{ return ((R (__thiscall*)(void*))(*(void***)o)[off / 4])(o); }
struct F_a34fa0 { bool call(int a, int b); };
struct F_a350d0 { void call(float* p, float dt); };
struct F_a35420 { void call(float dt); };
struct F_a355e0 { void call(char* s); };
struct F_a35610 { void call(void** pos, void** val); };
struct F_a35840 { void call(u32 key, float value); };
struct F_a358d0 { void call(void** pos, void** val); };
struct F_a35c40 { void call(int* list, float dt); };
struct AmbLayer {
    void UpdatePrimitives(float a, int b);
};
const float g166e110 = 0.0f;
const float g166e114 = 0.0f;
const float g166e118 = 0.0f;
// ---- items of slice s00a34e80 end

// ---- items of slice s00a35d20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_0166e290;         // 0x166e290 free-list head
extern char g_0166e280;         // 0x166e280 FixedAllocatorBase
extern char c_014530c8[];       // 0x14530c8
extern char c_014530ca[];       // 0x14530ca
extern char c_014530bc[];       // 0x14530bc "_density"
extern char c_014530c4[];       // 0x14530c4
extern char c_014335e8[];       // 0x14335e8
extern char c_014335e4[];       // 0x14335e4
#define VFN(p, off) ((*(void***)(p))[(off) / 4])
void   __fastcall fA35150(void* self);                                              // 0xa35150
void   __cdecl    f572020(void* p, int v);                                          // 0x572020
void*  __cdecl    GetSystemAT(void);                                                // 0xa206f0
void   __cdecl    AudioSetListener3(void* s, float x, float y, float z);            // 0x9fbc50
void   __cdecl    Start3dSoundByName(void* id, void* h, float x, float y, float z); // 0x571f80
void   __fastcall fA35840(void* self, u32 dummy, u32 id, float v);                  // 0xa35840
void   __fastcall fA358d0(void* self, u32 dummy, void** a, void** b);               // 0xa358d0
void*  __cdecl    GetServer(void);                                                  // 0x883860
void*  __fastcall f621f50(void* self, u32 dummy, void* first, void* last);          // 0x621f50
void*  __fastcall fA36d60(void* self, u32 dummy, void* arg);                        // 0xa36d60
void   __fastcall fA16a30(void* self, u32 dummy, void* arg);                        // 0xa16a30
void*  __cdecl    Alloc38c(int size);                                               // 0xa36f00
void*  __fastcall fA37160(void* self, u32 dummy, void* arg);                        // 0xa37160
void   __fastcall fA171c0(void* self, u32 dummy, void* a, int b);                   // 0xa171c0
void   __fastcall fA37080(void* self, u32 dummy, void* a);                          // 0xa37080
void   __cdecl    opDelete(void* p);                                                // 0xf47380
namespace EA {
namespace Allocator {
struct CoreBlock_s0092_6410;
}
}
namespace EA {
namespace Allocator {
struct FixedAllocatorBase_s0092_6410 { bool AddCore(CoreBlock_s0092_6410* p, u32 n); }; // 0x926650
}
}
void*  __cdecl    f6abeb0(int size);                                                // 0x6abeb0
void   __fastcall EStrCtor(void* self, u32 dummy, void* src);                       // 0x57cb10
void   __fastcall EStrAppend(void* self, u32 dummy, const char* a, const char* b);  // 0x455d60
u32    __cdecl    FNV1_String8(const char* s, u32 seed, int flag);                  // 0x932e80
void   __fastcall EStrReplace(void* self, u32 dummy, int pos, int count, const char* s); // 0x91ba20
void   __fastcall EStrAssign(void* self, u32 dummy, const char* a, const char* b);  // 0x454cb0
void*  __cdecl    fA366e0(int size);                                                // 0xa366e0
void   __fastcall fA35EF0(void* self, u32 dummy, void** v);                         // 0xa35ef0
struct EString { char* b; char* e; char* c; };
namespace SP {
namespace Audio {
class cAmbienceLayer { public:
    char pad[0x400];

    void  Update();                 // 0xa35d20
    bool  Shutdown();               // 0xa35f70
    void  ConnectPrimitive(u32 key, void* primitive); // 0xa36070
    bool  ConfigurePrimitives();    // 0xa36250
    bool  ReadTuningValues();       // 0xa36490
    bool  Init();                   // 0xa36570
};
}
}
namespace SP {
namespace Audio {
struct AmbPair { u32 first; void* second; };
}
}
using SP::Audio::cAmbienceLayer;
struct S106 {
    char pad[0x100];
    void pushPair(void** v);            // 0xa35ef0
    void dtor();                        // 0xa36a10
    void vecInsert(void** pos, void** value); // 0xa36ad0
    bool vecRemove(u32 key);            // 0xa36c80
};
// ---- items of slice s00a35d20 end

// @ 0x00a34ee0
void AmbLayer::UpdatePrimitives(float a, int b)
{
    char* s = (char*)this;
    int n = (*(int*)(s + 0x78) - *(int*)(s + 0x74)) >> 3;
    for (int i = 0; i < n; ++i) {
        char* e = *(char**)(s + 0x74) + i * 8;
        char* obj = *(char**)(e + 4);
        u32 key = *(u32*)e;
        typedef void (__thiscall* F28)(void*, float, int);
        typedef float (__thiscall* F1c)(void*);
        ((F28)(*(void***)obj)[0x28 / 4])(obj, a, b);
        float f = ((F1c)(*(void***)obj)[0x1c / 4])(obj);
        if (key == 0xc1a03855)
            goto B89;
        if (key == 0xf8cbbf4c) {
            s[0x88] = (f != 0.0f);
            goto end;
        }
        goto end;
B89:
        s[0x89] = (f != 0.0f);
end:    ;
    }
}

// @ 0x00a34fa0
bool F_a34fa0::call(int a, int b)
{
    char* s = (char*)this;
    if (a == 0x3a127dc && *(int*)(b + 8) == 0x3a129e8 &&
        *(int*)(b + 0x10) == *(int*)(s + 0x64))
        s[0x60] = 0;
    return 1;
}

// @ 0x00a34fd0
void* __cdecl FUN_00a34fd0(void* p1, void* p2, void* p3)
{
    if (p1 == p2)
        return p3;
    do {
        char* q1 = (char*)p1;
        char* q3 = (char*)p3;
        *(int*)q3 = *(int*)q1;
        void* ref = *(void**)(q1 + 4);
        *(void**)(q3 + 4) = ref;
        if (ref != 0)
            vt0<void>(ref, 0);
        p1 = q1 + 8;
        p3 = q3 + 8;
    } while (p1 != p2);
    return p3;
}

// @ 0x00a35070
void* __cdecl FUN_00a35070(void* p1, void* p2, void* p3)
{
    if (p1 != p2) {
        do {
            char* q1 = (char*)p1;
            char* q3 = (char*)p3;
            *(int*)q3 = *(int*)q1;
            void* newref = *(void**)(q1 + 4);
            void* oldref = *(void**)(q3 + 4);
            if (newref != oldref) {
                if (newref != 0)
                    vt0<void>(newref, 0);
                *(void**)(q3 + 4) = newref;
                if (oldref != 0)
                    vt<void>(oldref, 4, 0);
            }
            p1 = q1 + 8;
            p3 = q3 + 8;
        } while (p1 != p2);
    }
    return p3;
}

// @ 0x00a350d0
void F_a350d0::call(float* p, float dt)
{
    float* self = (float*)this;
    self[0] = p[0];
    self[1] = p[1];
    self[2] = p[2];
    float d = self[1] - self[4];
    float e = self[2] - self[5];
    float f = self[0] - self[3];
    float dist = d * d + (e * e + f * f);
    dist = (float)sqrt((double)dist);
    if (dt != 0.0f && 1e-06f <= dist) {
        self[6] = (float)(dist / dt);
        return;
    }
    self[3] = p[0];
    self[4] = p[1];
    self[5] = p[2];
}

// @ 0x00a35150
void __fastcall FUN_00a35150(int param_1)
{
    int iVar9 = 0;
    if (SP_App() == 0)
        return;
    if (vt0<int>(SP_App(), 0x58) == 0)
        return;

    float afStack_64[3];
    float score[8];

    Memset32(&afStack_64[1], 0, 8);

    float* pfVar8 = (float*)vt<int>(EA_Audio_GetSystemAT(), 0x10, 0);
    int iVar6 = (*(int*)(param_1 + 0x28) - *(int*)(param_1 + 0x24)) >> 2;
    float fVar12 = (float)iVar6;
    if (iVar6 < 0)
        fVar12 += 4294967296.0f;
    int* piVar7 = *(int**)(param_1 + 0x24);
    *(float*)(param_1 + 0x294) = (float)(fVar12 / *(float*)(param_1 + 0x290));
    int* piVar5 = *(int**)(param_1 + 0x28);
    if (piVar7 != piVar5) {
        do {
            int iVar1 = *piVar7;
            float fVar14 = pfVar8[2] - *(float*)(iVar1 + 0x10);
            fVar12 = *pfVar8 - *(float*)(iVar1 + 8);
            float fVar13 = pfVar8[1] - *(float*)(iVar1 + 0xc);
            int iVar10 = 0;
            int iVar11 = 0;
            fVar12 = 1.0f / ((fVar14 * fVar14 + fVar12 * fVar12) + fVar13 * fVar13);
            if (iVar9 < 1) {
LAB_00a352b2:
                score[iVar10] = fVar12;
                afStack_64[iVar10 * 3] = *(float*)(iVar1 + 8);
                afStack_64[iVar10 * 3 + 1] = *(float*)(iVar1 + 0xc);
                afStack_64[iVar10 * 3 + 2] = *(float*)(iVar1 + 0x10);
                iVar9 = iVar9 + 1;
            } else {
                do {
                    if (score[iVar11] <= fVar12 && fVar12 != score[iVar11]) {
                        iVar1 = (iVar9 - iVar11) + -1;
                        memmove(&score[iVar11], &score[iVar11 + 1], iVar1 * 4);
                        memmove(&afStack_64[iVar11 * 3], &afStack_64[iVar11 * 3 + 3],
                                iVar1 * 0xc);
                        iVar9 = iVar9 + -1;
                        break;
                    }
                    iVar11 = iVar11 + 1;
                    iVar10 = iVar10 + 1;
                } while (iVar11 < iVar9);
                if (iVar10 < 8)
                    goto LAB_00a352b2;
            }
            piVar7 = piVar7 + 1;
        } while (piVar7 != piVar5);

        if (iVar9 != 0) {
            iVar6 = 0;
            float fStack_90 = 0.0f;
            float fStack_8c = 0.0f;
            float fStack_88 = 0.0f;
            if (3 < iVar9) {
                int iVar10 = ((u32)(iVar9 - 4) >> 2) + 1;
                float* p = afStack_64 + 2;
                iVar6 = iVar10 * 4;
                do {
                    float f = *p;
                    float* p2 = p + 3;
                    float* p3 = p + 6;
                    fStack_90 = p[7] + (p[4] + (p[1] + (p[-2] + fStack_90)));
                    fStack_8c = p[8] + (p[5] + (p[2] + (p[-1] + fStack_8c)));
                    float* p4 = p + 9;
                    p = p + 0xc;
                    iVar10 = iVar10 + -1;
                    fStack_88 = *p4 + (*p3 + (*p2 + (f + fStack_88)));
                } while (iVar10 != 0);
            }
            if (iVar6 < iVar9) {
                float* p = afStack_64 + iVar6 * 3 + 2;
                int c = iVar9 - iVar6;
                do {
                    fStack_90 = p[-2] + fStack_90;
                    fStack_8c = p[-1] + fStack_8c;
                    float f = *p;
                    p = p + 3;
                    c = c - 1;
                    fStack_88 = f + fStack_88;
                } while (c != 0);
            }
            fVar12 = 1.0f / (float)iVar9;
            fStack_90 = fVar12 * fStack_90;
            fStack_8c = fVar12 * fStack_8c;
            fStack_88 = fStack_88 * fVar12;
            ((F_a350d0*)(param_1 + 0x3c))->call(&fStack_90, *(float*)(param_1 + 0x68));
        }
    }
}

// @ 0x00a35420
void F_a35420::call(float dt)
{
    float* self = (float*)this;
    float x = self[0];
    if (self[3] == x && self[4] == self[1] && self[5] == self[2])
        return;

    float dx = x - self[3];
    float dy = self[1] - self[4];
    float dz = self[2] - self[5];
    float len = dy * dy + (dz * dz + dx * dx);
    float inv = (float)(1.0 / sqrt((double)len));
    float dist = (float)sqrt((double)((dy * dy + dz * dz) + (x - self[3]) * (x - self[3])));
    float step = self[6] * dt;
    if (dist < self[6] * dt)
        step = dist;
    self[3] = self[3] + (inv * dx) * step;
    self[4] = self[4] + (inv * dy) * step;
    self[5] = self[5] + (inv * dz) * step;
}

// @ 0x00a35570
void __fastcall FUN_00a35570(int* param_1)
{
    int e = param_1[1];
    for (int p = *param_1; p < e; p += 8) {
        int ref = *(int*)(p + 4);
        if (ref != 0)
            vt<void>((void*)ref, 4, 0);
    }
    if (*param_1 != 0)
        operator_delete__((void*)*param_1);
}

// @ 0x00a355e0
void F_a355e0::call(char* s)
{
    char* p = s;
    while (*p++)
        ;
    ((Str10*)((char*)this + 0x10))->assign(s, p - 1);
}

// @ 0x00a35610
void F_a35610::call(void** param_2, void** param_3)
{
    int* self = (int*)this;
    void** end = (void**)self[1];
    if (end != (void**)self[2]) {
        if (param_2 <= param_3 && param_3 < end)
            param_3 = (void**)((char*)param_3 + 4);
        if (end != 0)
            *end = end[-1];
        int s = (self[1] - 4) - (int)param_2;
        memmove((void*)(self[1] + (s >> 2) * -4), param_2, s);
        *param_2 = *param_3;
        self[1] = self[1] + 4;
        return;
    }
    int n = (self[1] - *self) >> 2;
    void* dst;
    if (n == 0) {
        n = 1;
    } else {
        n = n * 2;
        if (n == 0) {
            dst = 0;
            goto L_alloc_done;
        }
    }
    dst = operator_new(n * 4, "EASTL", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                       0xd1);
L_alloc_done:
    int s = (int)param_2 - *self;
    void* pv = FUN_011e0744(dst, (void*)*self, s);
    void** q = (void**)((char*)pv + (s >> 2) * 4);
    if (q != 0)
        *q = *param_3;
    int oldEnd = self[1];
    void* pv2 = FUN_011e0744(q + 1, param_2, oldEnd - (int)param_2);
    if (*self != 0)
        operator_delete__((void*)*self);
    *self = (int)dst;
    self[1] = (int)((char*)pv2 + ((oldEnd - (int)param_2) >> 2) * 4);
    self[2] = (int)dst + n * 4;
}

// @ 0x00a35720
void __fastcall FUN_00a35720(int* param_1)
{
    param_1[0] = 0x14530ac;
    param_1[1] = 0x14530a8;
    int v = param_1[0x9b];
    if (1 < param_1[0x9d] - v && v != 0)
        operator_delete__((void*)v);

    char* h = (char*)param_1 + 0x8c;
    FUN_00a1b6c0(h, (void*)param_1[0x24], (void*)param_1[0x25]);
    int* puVar2 = (int*)param_1[0x24];
    param_1[0x26] = 0;
    if (1 < (u32)param_1[0x25] && puVar2 != (int*)param_1[0x2f]) {
        if (puVar2 < (int*)param_1[0x2c] || (int*)param_1[0x2d] <= puVar2) {
            operator_delete__(puVar2);
        } else {
            *puVar2 = param_1[0x2a];
            param_1[0x2a] = (int)puVar2;
        }
    }
    FUN_00a35570((int*)((char*)param_1 + 0x74));
    if (param_1[9] != 0)
        operator_delete__((void*)param_1[9]);
    int v2 = param_1[4];
    if (1 < param_1[6] - v2 && v2 != 0)
        operator_delete__((void*)v2);
    if ((int*)param_1[3] != 0)
        vt<void>((void*)param_1[3], 4, 0);
    param_1[0] = 0x13eb394;
    param_1[1] = 0x13ef094;
}

// @ 0x00a35840
void F_a35840::call(u32 key, float value)
{
    int param_1 = (int)this;
    char* h = (char*)param_1 + 0x8c;
    u32 local_14 = 0;
    float local_10 = 0;
    FUN_find(h, key, &local_14, &local_10);
    int* hh = (int*)(param_1 + 0x8c);
    u32 uVar1 = key;
    if (local_14 == *(u32*)(*(int*)(param_1 + 0x90) + *(int*)(param_1 + 0x94) * 4)) {
        u32 tag = key & 0xffffff00;
        local_14 = uVar1;
        local_10 = value;
        FUN_00a26ce0(hh, &local_14, &tag);
    } else {
        if (*(float*)(local_14 + 4) == value)
            return;
        *(float*)(local_14 + 4) = value;
    }
    SetGlobalProperty(uVar1, value);
}

// @ 0x00a358d0
void F_a358d0::call(void** param_2, void** param_3)
{
    int* self = (int*)this;
    void** end = (void**)self[1];
    if (end != (void**)self[2]) {
        if (param_2 <= param_3 && param_3 < end)
            param_3 = (void**)((char*)param_3 + 8);
        if (end != 0) {
            *end = end[-2];
            void* ref = end[-1];
            end[1] = ref;
            if (ref != 0)
                vt0<void>(ref, 0);
        }
        FUN_00621d50(param_2, (void*)(self[1] - 8), (void*)self[1]);
        *param_2 = *param_3;
        void* src = param_3[1];
        void* cur = param_2[1];
        if (src != cur) {
            if (src != 0)
                vt0<void>(src, 0);
            param_2[1] = src;
            if (cur != 0)
                vt<void>(cur, 4, 0);
        }
        self[1] = self[1] + 8;
        return;
    }
    int n = (self[1] - *self) >> 3;
    void* dst;
    if (n == 0) {
        n = 1;
    } else {
        n = n * 2;
        if (n == 0) {
            dst = 0;
            goto L_alloc_done;
        }
    }
    dst = operator_new(n * 8, "EASTL", 0, 0,
                       "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                       0xd1);
L_alloc_done:
    int first = *self;
    void* pv = FUN_00a34fd0((void*)first, param_2, dst);
    FUN_00621d10((void*)first, param_2, dst);
    if (pv != 0) {
        *(void**)pv = *param_3;
        void* ref = param_3[1];
        *(void**)((char*)pv + 4) = ref;
        if (ref != 0)
            vt0<void>(ref, 0);
    }
    int oldEnd = self[1];
    int iv = (int)FUN_00a34fd0(param_2, (void*)oldEnd, (char*)pv + 8);
    FUN_00621d10(param_2, (void*)oldEnd, (char*)pv + 8);
    if (*self != 0)
        operator_delete__((void*)*self);
    *self = (int)dst;
    self[1] = iv;
    self[2] = (int)dst + n * 8;
}

// @ 0x00a35aa0
void* __fastcall FUN_00a35aa0(int* param_1)
{
    param_1[1] = 0x13ef094;
    param_1[2] = 0;
    param_1[0] = 0x14530ac;
    param_1[1] = 0x14530a8;
    param_1[3] = 0;
    param_1[4] = 0x1667bac;
    param_1[5] = 0x1667bac;
    param_1[6] = 0x1667bad;
    param_1[8] = 0;
    param_1[9] = 0;
    param_1[10] = 0;
    param_1[0xb] = 0;
    param_1[0xe] = 0;

    float v0 = g166e110;
    float v1 = g166e114;
    float v2 = g166e118;
    param_1[0xf] = *(int*)&v0;
    param_1[0x10] = *(int*)&v1;
    param_1[0x11] = *(int*)&v2;
    param_1[0x12] = *(int*)&v0;
    param_1[0x13] = *(int*)&v1;
    param_1[0x14] = *(int*)&v2;
    param_1[0x15] = 0;
    param_1[0x16] = 0x2b8cbccc;
    param_1[0x17] = 0;
    *((u8*)param_1 + 0x60) = 0;
    param_1[0x19] = 0;
    param_1[0x1a] = 0;
    param_1[0x1b] = 0;
    *((u8*)param_1 + 0x70) = 1;
    param_1[0x1d] = 0;
    param_1[0x1e] = 0;
    param_1[0x1f] = 0;
    *((u8*)param_1 + 0x88) = 1;
    *((u8*)param_1 + 0x89) = 0;
    FUN_00a1e320((char*)param_1 + 0x8c, (char*)param_1 + 0x8c);
    param_1[0x9b] = 0x1667bac;
    param_1[0x9c] = 0x1667bac;
    param_1[0x9d] = 0x1667bad;
    *((u8*)param_1 + 0x27c) = 0;
    param_1[0xa4] = 0;
    param_1[0xa5] = 0;
    param_1[0xa6] = 0;
    return param_1;
}

// @ 0x00a35c00
void __fastcall FUN_00a35c00(int param_1)
{
    void* _Src = *(void**)(param_1 + 0x28);
    void* _Dst = *(void**)(param_1 + 0x24);
    FUN_011e0744(_Dst, _Src, 0);
    *(int*)(param_1 + 0x28) = *(int*)(param_1 + 0x28) +
                              (((int)_Src - (int)_Dst) >> 2) * -4;
    *(float*)(param_1 + 0x290) = 0.0f;
    *(float*)(param_1 + 0x294) = 0.0f;
}

// @ 0x00a35c40
void F_a35c40::call(int* param_2, float param_3)
{
    int param_1 = (int)this;
    int* sys = (int*)FUN_SP_AudioSystem();
    int* a = (int*)vt<int>((void*)sys, 0x24, 0);
    float* pf = (float*)vt<int>((void*)a, 0x24, 0);
    int* pvEnd = (int*)param_2[1];
    int* pv = (int*)*param_2;
    for (; pv != pvEnd; pv = pv + 1) {
        int* pr = (int*)*pv;
        if (pr == 0 || *pr == 0)
            break;
        int id = pr[1];
        float dx = (float)pr[2] - *pf;
        float dy = (float)pr[3] - pf[1];
        float dz = (float)pr[4] - pf[2];
        if (sqrt(dx * dx + (dy * dy + dz * dz)) < *(float*)(param_1 + 0x6c)) {
            *(float*)(param_1 + 0x290) = *(float*)(param_1 + 0x290) + 1.0f;
            if (id == *(int*)(param_1 + 0x38)) {
                int* cur = *(int**)(param_1 + 0x28);
                if ((u32)cur < *(u32*)(param_1 + 0x2c)) {
                    *(int*)(param_1 + 0x28) = (int)(cur + 1);
                    if (cur != 0)
                        *cur = (int)pr;
                } else {
                    void* v = pr;
                    ((F_a35610*)(param_1 + 0x24))->call((void**)cur, &v);
                }
            }
        }
    }
    ((F_a35420*)(param_1 + 0x3c))->call(param_3);
    *(u8*)(param_1 + 0x70) =
        (*(int*)(param_1 + 0x24) == *(int*)(param_1 + 0x28));
}

// @ 0x00a35d20
namespace SP { namespace Audio {
void cAmbienceLayer::Update()
{
    char* self = (char*)this;
    fA35150(self);

    bool bVar5;
    if (*(int*)(self + 0x24) == *(int*)(self + 0x28)) bVar5 = false;
    else if (*(u8*)(self + 0x88) == 0)               bVar5 = false;
    else                                             bVar5 = (*(u8*)(self + 0x89) == 0);

    bool bVar4 = (*(int*)(self + 0x5c) != 0) && bVar5;

    if (*(u8*)(self + 0x60) != 0 && !bVar4) {
        f572020(*(void**)(self + 0x64), 0);
        void* h = *(void**)(self + 0x64);
        void* sys = GetSystemAT();
        if (sys) ((void(__thiscall*)(void*, void*))VFN(sys, 0x2c))(sys, h);
        *(void**)(self + 0x64) = 0;
        *(u8*)(self + 0x60) = 0;
    }

    if (bVar5) {
        if (*(u8*)(self + 0x70) != 0) {
            *(u32*)(self + 0x48) = *(u32*)(self + 0x3c);
            *(u32*)(self + 0x4c) = *(u32*)(self + 0x40);
            *(u32*)(self + 0x50) = *(u32*)(self + 0x44);
        }
        float x = *(float*)(self + 0x48);
        float y = *(float*)(self + 0x4c);
        float z = *(float*)(self + 0x50);
        fA35840(self, 0, *(u32*)(self + 0x28c), *(float*)(self + 0x294));
        fA35840(self, 0, *(u32*)(self + 0x280), x);
        fA35840(self, 0, *(u32*)(self + 0x284), y);
        fA35840(self, 0, *(u32*)(self + 0x288), z);
        if (*(u8*)(self + 0x60) != 0) {
            AudioSetListener3(*(void**)(self + 0x64), x, y, z);
            return;
        }
        if (bVar4) {
            void* sys = GetSystemAT();
            void* h = sys ? ((void*(__thiscall*)(void*))VFN(sys, 0x24))(sys) : 0;
            *(void**)(self + 0x64) = h;
            Start3dSoundByName(*(void**)(self + 0x5c), h, x, y, z);
            *(u8*)(self + 0x60) = 1;
            return;
        }
    } else {
        fA35840(self, 0, *(u32*)(self + 0x28c), 0.0f);
    }
}
}}  // namespace SP::Audio

// @ 0x00a35ef0
void S106::pushPair(void** v)
{
    char* self = (char*)this;
    void** end = *(void***)(self + 4);
    if (end < *(void***)(self + 8)) {
        *(void***)(self + 4) = end + 2;
        if (end) {
            end[0] = v[0];
            end[1] = v[1];
            if (end[1]) ((void(__thiscall*)(void*))VFN(end[1], 0))(end[1]);
        }
    } else {
        fA358d0(self, 0, end, v);
    }
}

// @ 0x00a35f70
namespace SP { namespace Audio {
bool cAmbienceLayer::Shutdown()
{
    char* self = (char*)this;
    void* srv = GetServer();
    if (srv) ((void(__thiscall*)(void*, void*, int, int))VFN(srv, 0x2c))(srv, self, 0x3a127dc, -9999);
    *(u8*)(self + 0x27c) = 0;
    if (*(u8*)(self + 0x60) != 0) {
        fA35840(self, 0, *(u32*)(self + 0x28c), 0.0f);
        fA35840(self, 0, *(u32*)(self + 0x280), 0.0f);
        fA35840(self, 0, *(u32*)(self + 0x284), 0.0f);
        fA35840(self, 0, *(u32*)(self + 0x288), 0.0f);
        f572020(*(void**)(self + 0x64), 1);
        *(u8*)(self + 0x60) = 0;
    }
    char* vec = self + 0x74;
    int n = (*(int*)(self + 0x78) - *(int*)(self + 0x74)) >> 3;
    for (int i = 0; i < n; ++i) {
        void* e = *(void**)(*(int*)vec + i * 8 + 4);
        if (((void*(__thiscall*)(void*))VFN(e, 0x30))(e) == self)
            ((void(__thiscall*)(void*))VFN(e, 0x14))(e);
    }
    f621f50(vec, 0, *(void**)vec, *(void**)(vec + 4));
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a36070
namespace SP { namespace Audio {
void cAmbienceLayer::ConnectPrimitive(u32 key, void* primitive)
{
    char* self = (char*)this;
    char* vec = self + 0x74;
    int n = (*(int*)(self + 0x78) - *(int*)(self + 0x74)) >> 3;
    AmbPair* found = 0;
    for (int i = 0; i < n; ++i) {
        AmbPair* p = (AmbPair*)(*(int*)vec + i * 8);
        if (p->first == key) { found = p; break; }
    }
    if (!found) {
        if (primitive) ((void(__thiscall*)(void*))VFN(primitive, 0))(primitive);
        AmbPair p; p.first = key; p.second = primitive;
        if (primitive) ((void(__thiscall*)(void*))VFN(primitive, 0))(primitive);
        ((void(__fastcall*)(void*, u32, void**))fA35EF0)(vec, 0, (void**)&p);
        if (p.second) ((void(__thiscall*)(void*))VFN(p.second, 4))(p.second);
        if (primitive) ((void(__thiscall*)(void*))VFN(primitive, 4))(primitive);
        return;
    }

    void* obj = found->second;
    if (obj) {
        void* qi = ((void*(__thiscall*)(void*, int))VFN(obj, 0xc))(obj, 0x4e73a43a);
        if (qi && ((void*(__thiscall*)(void*))VFN(obj, 0x30))(obj) == self) {
            ((void(__thiscall*)(void*, void*))VFN(qi, 0x10))(qi, primitive);
            return;
        }
    }

    void* mem = fA366e0(0x6c);
    void* canvas = mem ? fA36d60(mem, 0, self) : 0;
    void* cv = 0;
    if (canvas) { ((void(__thiscall*)(void*))VFN(canvas, 0))(canvas); cv = canvas; }
    fA16a30(cv, 0, (void*)key);
    ((void(__thiscall*)(void*))VFN(cv, 0x10))(cv);
    void* sub = *(void**)((char*)cv + 4);
    ((void(__thiscall*)(void*, void*))VFN(sub, 0x10))(sub, obj);
    ((void(__thiscall*)(void*, void*))VFN(sub, 0x10))(sub, primitive);
    void* old = found->second;
    if (cv != old) {
        ((void(__thiscall*)(void*))VFN(cv, 0))(cv);
        found->second = cv;
        if (old) ((void(__thiscall*)(void*))VFN(old, 4))(old);
    }
    ((void(__thiscall*)(void*))VFN(cv, 4))(cv);
}
}}  // namespace SP::Audio

// @ 0x00a36250
namespace SP { namespace Audio {
bool cAmbienceLayer::ConfigurePrimitives()
{
    char* self = (char*)this;
    void* cfg = *(void**)(self + 0xc);
    u32 count = 0;
    void* array = 0;
    if (!((bool(__thiscall*)(void*, u32, u32*, void**))VFN(cfg, 0x48))(cfg, 0x3da0a727, &count, &array))
        return false;
    if (count == 0) return true;

    while (count >= 2) {
        u32* a = (u32*)array;
        u32 k1 = a[0];
        u32 k2 = a[1];
        a += 2;
        count -= 2;
        u32 k3 = 0;
        if (count != 0) {
            k3 = a[0]; ++a; --count;
            if (count != 0 && a[0] == 0) { ++a; --count; }
        }
        if (k1 == 0 || k2 == 0) return false;

        void* obj = 0;
        if (k3 != 0) {
            void* c2 = *(void**)(self + 0xc);
            void* pa = 0; void* pb = 0;
            if (((bool(__thiscall*)(void*, u32, void**, void**))VFN(c2, 0x44))(c2, k3, &pb, &pa)) {
                void* mem = Alloc38c(0x38c);
                void* o = mem ? fA37160(mem, 0, self) : 0;
                if (o) { ((void(__thiscall*)(void*))VFN(o, 0))(o); obj = o; }
                fA171c0(obj, 0, pb, ((int)pa) >> 1);
            }
        }
        void* sys = GetSystemAT();
        void* got = 0;
        if (((bool(__thiscall*)(void*, u32, void**))VFN(sys, 0x34))(sys, k2, &got)) {
            if (obj) {
                fA37080(obj, 0, got);
                ((void(__thiscall*)(void*))VFN(obj, 0x10))(obj);
                if (obj != got) {
                    ((void(__thiscall*)(void*))VFN(obj, 0))(obj);
                    got = obj;
                }
            }
            ConnectPrimitive(k1, got);
        }
        if (got) ((void(__thiscall*)(void*))VFN(got, 4))(got);
        if (obj) ((void(__thiscall*)(void*))VFN(obj, 4))(obj);
    }
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a36490
namespace SP { namespace Audio {
bool cAmbienceLayer::ReadTuningValues()
{
    char* self = (char*)this;
    void* sys = GetSystemAT();
    char* cfg = self + 0xc;
    void* c = *(void**)(self + 0xc);
    if (c) { *(void**)(self + 0xc) = 0; ((void(__thiscall*)(void*))VFN(c, 4))(c); }
    if (!((bool(__thiscall*)(void*, u32, char*, int))VFN(sys, 0x14))(sys, *(u32*)(self + 0x20), cfg, 0x21407ee))
        return false;

    void* cc = *(void**)(self + 0xc);
    char* s = ((char*(__thiscall*)(void*, int))VFN(cc, 0x40))(cc, 0x2f8b3bf4);
    if (s) {
        char* e = s;
        while (*e) ++e;
        EStrAssign(self + 0x10, 0, s, e);
    }
    void* c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x30))(c2, 0xe0f9a433, self + 0x58);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x30))(c2, 0x2bd62d35, self + 0x68);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x30))(c2, 0x2e65b70f, self + 0x6c);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x38))(c2, 0x701ed91e, self + 0x5c);
    c2 = *(void**)(self + 0xc);
    ((void(__thiscall*)(void*, int, void*))VFN(c2, 0x38))(c2, 0x1e16cfe8, self + 0x38);
    ConfigurePrimitives();
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a36570
namespace SP { namespace Audio {
bool cAmbienceLayer::Init()
{
    char* self = (char*)this;
    if (!ReadTuningValues()) return false;
    char* name = self + 0x10;
    EString tmp;
    EStrCtor(&tmp, 0, name);
    EStrAppend(&tmp, 0, c_014530c8, c_014530ca);
    *(u32*)(self + 0x280) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    EStrReplace(&tmp, 0, (int)(tmp.e - tmp.b) - 1, 1, c_014335e8);
    *(u32*)(self + 0x284) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    EStrReplace(&tmp, 0, (int)(tmp.e - tmp.b) - 1, 1, c_014335e4);
    *(u32*)(self + 0x288) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    if (name != (char*)&tmp) EStrAssign(name, 0, tmp.b, tmp.e);
    EStrAppend(&tmp, 0, c_014530bc, c_014530c4);
    *(u32*)(self + 0x28c) = FNV1_String8(tmp.b, 0x811c9dc5, 1);
    void* srv = GetServer();
    if (srv) ((void(__thiscall*)(void*, void*, int))VFN(srv, 0x20))(srv, self, 0x3a127dc);
    if ((tmp.e - tmp.b) > 1 && tmp.b) opDelete(tmp.b);
    return true;
}
}}  // namespace SP::Audio

// @ 0x00a366e0
void* __cdecl fA366e0(int size)
{
    if (size == 0x6c) {
        char c;
        void* p;
        do {
            p = *(void**)&g_0166e290;
            if (p) { *(void**)&g_0166e290 = *(void**)p; return p; }
            c = ((EA::Allocator::FixedAllocatorBase_s0092_6410*)&g_0166e280)->AddCore(0, 0);
        } while (c);
        return 0;
    }
    return f6abeb0(size);
}
