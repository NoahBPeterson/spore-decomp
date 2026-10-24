// Slice s00a34e80 -- SP::Audio ambience-layer helpers: primitive update/
// selection, small vector/string helpers and a fixed-vector-backed object.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int   u32;

void* __cdecl operator_new(u32 size, const char* tag, int a3, int a4,
                           const char* file, int line);
void  __cdecl operator_delete__(void*);

// --- resolved-by-address externals -------------------------------------------
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

// stub structs so that logical __thiscall functions become member methods
struct F_a34fa0 { bool call(int a, int b); };
struct F_a350d0 { void call(float* p, float dt); };
struct F_a35420 { void call(float dt); };
struct F_a355e0 { void call(char* s); };
struct F_a35610 { void call(void** pos, void** val); };
struct F_a35840 { void call(u32 key, float value); };
struct F_a358d0 { void call(void** pos, void** val); };
struct F_a35c40 { void call(int* list, float dt); };

// ===========================================================================
// 0x00a34e80
// ===========================================================================
// @ 0x00a34e80
void __fastcall FUN_00a34e80(int* self)
{
    *(int*)((char*)self + 0xc) = *(int*)((char*)self + 8);
}

// ===========================================================================
// 0x00a34e90
// ===========================================================================
// @ 0x00a34e90
int __cdecl FUN_00a34e90(void)
{
    char* p = (char*)EA_Audio_GetSystemAT();
    if (p != 0) {
        typedef int (__thiscall* Fn)(void*);
        return ((Fn)(*(void***)p)[0x24 / 4])(p);
    }
    return 0;
}

// ===========================================================================
// 0x00a34eb0
// ===========================================================================
// @ 0x00a34eb0
void __fastcall FUN_00a34eb0(int* self)
{
    ((u8*)self)[0x27c] = (((u8*)self)[0x27c] == 0);
}

// ===========================================================================
// 0x00a34ee0  SP::Audio::cAmbienceLayer::UpdatePrimitives
// ===========================================================================
struct AmbLayer {
    void UpdatePrimitives(float a, int b);
};

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

// ===========================================================================
// 0x00a34fa0
// ===========================================================================
// @ 0x00a34fa0
bool F_a34fa0::call(int a, int b)
{
    char* s = (char*)this;
    if (a == 0x3a127dc && *(int*)(b + 8) == 0x3a129e8 &&
        *(int*)(b + 0x10) == *(int*)(s + 0x64))
        s[0x60] = 0;
    return 1;
}

// ===========================================================================
// 0x00a34fd0  copy-construct [p1,p2) into p3 (AutoRefCount AddRef)
// ===========================================================================
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

// ===========================================================================
// 0x00a35070  assign-copy [p1,p2) into buffered range starting at p3
// ===========================================================================
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

// ===========================================================================
// 0x00a350d0  travel-segment update
// ===========================================================================
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

// ===========================================================================
// 0x00a35150  recentre an ambience cluster on its dominant primitives
// ===========================================================================
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

// ===========================================================================
// 0x00a35420  move segment endpoint along its direction by dt*speed
// ===========================================================================
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
    double len = (double)dx * dx + (double)dz * dz + (double)dy * dy;
    float inv = (float)(1.0 / sqrt(len));
    double dist2 = (double)dz * dz + (double)dy * dy + ((double)x - (double)self[3]) * ((double)x - (double)self[3]);
    float dist = (float)sqrt(dist2);
    float step = self[6] * dt;
    if (step > dist)
        step = dist;
    self[3] = self[3] + (inv * dx) * step;
    self[4] = self[4] + (inv * dy) * step;
    self[5] = self[5] + (inv * dz) * step;
}

// ===========================================================================
// 0x00a35570  destroy a vector of AutoRefCount<IPrimitive> and free storage
// ===========================================================================
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

// ===========================================================================
// 0x00a355e0  basic_string::assign(const char*)
// ===========================================================================
// @ 0x00a355e0
void F_a355e0::call(char* s)
{
    char* p = s;
    while (*p++)
        ;
    ((Str10*)((char*)this + 0x10))->assign(s, p - 1);
}

// ===========================================================================
// 0x00a35610  vector<4-byte>::insert at position
// ===========================================================================
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

// ===========================================================================
// 0x00a35720  destructor for the StyleManager-map-backed handler object
// ===========================================================================
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

// ===========================================================================
// 0x00a35840  set a global audio style property and cache it
// ===========================================================================
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

// ===========================================================================
// 0x00a358d0  vector<8-byte AutoRefCount pair>::insert (EH-aware)
// ===========================================================================
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

// ===========================================================================
// 0x00a35aa0  constructor of the ambience-layer object
// ===========================================================================
const float g166e110 = 0.0f;
const float g166e114 = 0.0f;
const float g166e118 = 0.0f;

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

// ===========================================================================
// 0x00a35c00  clear the primitive vector and reset accumulators
// ===========================================================================
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

// ===========================================================================
// 0x00a35c40  update selected primitives and recentre the cluster
// ===========================================================================
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
