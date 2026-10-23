// Swarm particle / path-follow helpers (slice s00aa83b0).
// Built with VS2008 SP1 (cl 15.00.30729.01) at /O2 /arch:SSE.
// The SSE/integer leaves are reconstructed for byte-match; the larger mixed bodies are the
// behaviour-equivalent reconstruction.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Constants from the original image's float pool.
// ---------------------------------------------------------------------------
extern float g_01471064;   // 0x1471064   0.5f
extern float g_01485720;   // 0x1485720   1.0f
extern float g_01485378;   // 0x1485378   0.0f
extern float g_01565620;   // 0x1565620   (large sentinel)

// ---------------------------------------------------------------------------
// Extern helpers (addresses from the original image)
// ---------------------------------------------------------------------------
extern void __cdecl FUN_00a7f5a0(int a, int b, int c, int d, float e, int f, int g, int h, int i, int j, int k); // 0x00a7f5a0
struct KeyDesc;
struct Vec3 { float x, y, z; };
extern void __cdecl FUN_00a81a20(Vec3* v, void* out);                          // 0x00a81a20
extern void __cdecl FUN_00a6c7a0(int a, int b, int* count, void** outPtr, int* outCount); // 0x00a6c7a0
extern void __cdecl FUN_007cdbe0(void* a, void* b);                           // 0x007cdbe0
extern float __cdecl FUN_007cdb90(void* a);                                   // 0x007cdb90

extern void* __cdecl EA_Swarm_SnapParticleToPath(int a, int b, int c, Vec3* d, Vec3* e, int f); // 0x00a79f60

// ---------------------------------------------------------------------------
// thiscall callees modelled as member functions so ecx=this and ret N are reproduced
// ---------------------------------------------------------------------------
struct cRWState
{
    void Init(const KeyDesc* key, const Vec3* vec, bool flag);   // 0x00a79430
};

struct cSPTransformOps
{
    cSPTransformOps* Assign(const void* src);                    // 0x00537dc0
};

struct VTX
{
    void FUN_007cdee0(float* v);                                 // 0x007cdee0
};

struct SwarmPath
{
    void FUN_00aa89d0(float* param_2);                           // 0x00aa89d0
};

// ---------------------------------------------------------------------------
// @ 0x00aa83b0
// ---------------------------------------------------------------------------
uint8_t __cdecl FUN_00aa83b0(int param_1, float param_2, int param_3, int param_4)
{
    float fVar2 = *(float*)(param_1 + 0x1c);
    float fVar4 = *(float*)(param_1 + 0x20);
    float fVar1 = *(float*)(param_1 + 0x24);

    float dt = param_2 + *(float*)(param_1 + 8);
    *(float*)(param_1 + 8) = dt;
    if (*(float*)(param_1 + 0xc) <= dt)
        return 0;

    float acc1 = *(float*)(param_4 + 0x64);
    float acc2 = *(float*)(param_4 + 0x68);
    float acc3 = *(float*)(param_4 + 0x6c);

    float nv1 = fVar2 + acc1 * param_2;
    float nv2 = fVar4 + acc2 * param_2;
    float nv3 = fVar1 + acc3 * param_2;
    *(float*)(param_1 + 0x1c) = nv1;
    *(float*)(param_1 + 0x20) = nv2;
    *(float*)(param_1 + 0x24) = nv3;

    float damp = 1.0f - *(float*)(param_3 + 0x160) * param_2;
    nv1 *= damp;
    nv2 *= damp;
    nv3 *= damp;
    *(float*)(param_1 + 0x1c) = nv1;
    *(float*)(param_1 + 0x20) = nv2;
    *(float*)(param_1 + 0x24) = nv3;

    float half = param_2 * 0.5f;
    *(float*)(param_1 + 0x10) = *(float*)(param_1 + 0x10) + (nv1 + fVar2) * half;
    *(float*)(param_1 + 0x14) = *(float*)(param_1 + 0x14) + (nv2 + fVar4) * half;
    *(float*)(param_1 + 0x18) = *(float*)(param_1 + 0x18) + (nv3 + fVar1) * half;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x00aa84c0
// ---------------------------------------------------------------------------
void __cdecl FUN_00aa84c0(int param_1, int param_2, int param_3, int param_4)
{
    int iVar1 = param_4 + 0x214;
    if (*(int*)(param_4 + 0x214) == *(int*)(param_4 + 0x218))
        iVar1 = param_3 + 0x25c;

    int a1 = (param_1 == 0) ? 0 : param_1 + 8;

    float size = *(float*)(param_3 + 0x44);
    Vec3 vecA;
    vecA.x = (*(float*)(param_3 + 0x4c) + *(float*)(param_3 + 0x58)) * 0.5f;
    vecA.y = (*(float*)(param_3 + 0x5c) + *(float*)(param_3 + 0x50)) * 0.5f;
    vecA.z = (*(float*)(param_3 + 0x60) + *(float*)(param_3 + 0x54)) * 0.5f;
    Vec3 vecB;
    vecB.x = size * ((*(float*)(param_3 + 0x38) + *(float*)(param_3 + 0x2c)) * 0.5f);
    vecB.y = size * ((*(float*)(param_3 + 0x3c) + *(float*)(param_3 + 0x30)) * 0.5f);
    vecB.z = size * ((*(float*)(param_3 + 0x40) + *(float*)(param_3 + 0x34)) * 0.5f);

    EA_Swarm_SnapParticleToPath(a1, param_2, iVar1, &vecA, &vecB, param_4 + 200);
}

// ---------------------------------------------------------------------------
// @ 0x00aa85c0
// ---------------------------------------------------------------------------
void __fastcall FUN_00aa85c0(char* self)
{
    int* piVar1;
    if (*(uint8_t*)(self + 0xc) != 0)
        ((void (__thiscall*)(void*, int))((void**)(*(void**)self))[0xc / 4])(self, 1);

    if (-1 < *(int*)(self + 0x228))
    {
        void* P = *(void**)(self + 0x24);
        piVar1 = (int*)((int (__thiscall*)(void*))((void**)(*(void**)P))[0x20 / 4])(P);
        ((void (__thiscall*)(int*, int))((void**)(*(void**)piVar1))[0x30 / 4])(piVar1, *(int*)(self + 0x228));
    }
    if (-1 < *(int*)(self + 0x22c))
    {
        void* P = *(void**)(self + 0x24);
        piVar1 = (int*)((int (__thiscall*)(void*))((void**)(*(void**)P))[0x20 / 4])(P);
        ((void (__thiscall*)(int*, int))((void**)(*(void**)piVar1))[0x1c / 4])(piVar1, *(int*)(self + 0x22c));
    }
    if (*(void**)(self + 0x1a8) != 0)
    {
        ((void (__thiscall*)(void*))((void**)(*(void**)*(void**)(self + 0x1a8)))[0xc / 4])(*(void**)(self + 0x1a8));
        void* p = *(void**)(self + 0x1a8);
        if (p != 0)
        {
            *(void**)(self + 0x1a8) = 0;
            ((void (__thiscall*)(void*))((void**)(*(void**)p))[4 / 4])(p);
        }
    }
    if (*(void**)(self + 0x1ac) != 0)
    {
        ((void (__thiscall*)(void*))((void**)(*(void**)*(void**)(self + 0x1ac)))[0xc / 4])(*(void**)(self + 0x1ac));
        void* p = *(void**)(self + 0x1ac);
        if (p != 0)
        {
            *(void**)(self + 0x1ac) = 0;
            ((void (__thiscall*)(void*))((void**)(*(void**)p))[4 / 4])(p);
        }
    }
    if (*(void**)(self + 0x1b0) != 0)
    {
        ((void (__thiscall*)(void*))((void**)(*(void**)*(void**)(self + 0x1b0)))[0xc / 4])(*(void**)(self + 0x1b0));
        void* p = *(void**)(self + 0x1b0);
        if (p != 0)
        {
            *(void**)(self + 0x1b0) = 0;
            ((void (__thiscall*)(void*))((void**)(*(void**)p))[4 / 4])(p);
        }
    }
    *(int*)(self + 0x1c) = 0;
    *(int*)(self + 0x24) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00aa86a0
// ---------------------------------------------------------------------------
struct SwarmObj
{
    char          pad00[0xc];
    uint8_t       flag0c;         // +0x0c
    uint8_t       flag0d;         // +0x0d
    char          pad0e[0x1c - 0xe];
    int           int1c;          // +0x1c
    char          pad20[0x38 - 0x20];
    uint8_t       flag38;         // +0x38

    void __thiscall FUN_00aa86a0(int param_2);   // 0x00aa86a0
};

void SwarmObj::FUN_00aa86a0(int param_2)
{
    char* self = (char*)this;
    int run = 0;
    if (param_2 == 0)
    {
        run = 1;
    }
    else
    {
        int iVar2 = *(int*)(self + 0x1c);
        if (*(uint16_t*)(iVar2 + 0x80) == 0)
        {
            run = 1;
        }
        else
        {
            uint32_t uVar1 = *(uint32_t*)(iVar2 + 8);
            if (((uVar1 >> 2) & 1) != 0 || ((uVar1 >> 0x1c) & 1) != 0)
                run = 1;
        }
    }
    if (run)
    {
                if ((*(uint8_t*)(self + 0xc) == 0) || (*(uint8_t*)(self + 0xd) != 0))
                {
                    *(uint8_t*)(self + 0xd) = 0;
                    *(uint8_t*)(self + 0xc) = 1;
                }
                *(uint32_t*)(self + 0x40) = 0;
                *(uint32_t*)(self + 0x44) = 0;
                *(uint32_t*)(self + 0x30) = 0;
                *(uint32_t*)(self + 0x34) = 0;
                *(uint32_t*)(self + 0x130) = *(uint32_t*)(self + 0xc4);
                *(uint32_t*)(self + 0x134) = *(uint32_t*)(self + 0xc8);
                int iVar = *(int*)(self + 0x1c);
                *(uint32_t*)(self + 0x138) = *(uint32_t*)(self + 0xcc);
                *(uint32_t*)(self + 0x48) = 0;
                *(uint32_t*)(self + 0x58) = 0;
                *(uint32_t*)(self + 0x5c) = *(uint32_t*)(iVar + 0x13c);
                *(uint32_t*)(self + 0x60) = *(uint32_t*)(iVar + 0x140);
                *(uint32_t*)(self + 0x64) = *(uint32_t*)(iVar + 0x144);
                {
                    uint32_t uv = *(uint32_t*)(iVar + 8);
                    if (((uv >> 0x13) & 1) != 0)
                    {
                        Vec3 local_c;
                        FUN_007cdbe0(&local_c, (void*)(iVar + 0x2c));
                        ((cRWState*)(self + 0x68))->Init((const KeyDesc*)(*(int*)(self + 0x1c) + 0x200),
                                                         &local_c,
                                                         ((uv >> 0x14) & 1) != 0);
                    }
                }
                {
                    int iv = *(int*)(self + 0x1c);
                    if (*(float*)(iv + 0x1c) < 0.0f)
                    {
                        if (*(float*)(iv + 0x24) < 0.0f)
                            *(uint32_t*)(self + 0x94) = 0;
                        else
                            *(float*)(self + 0x94) = FUN_007cdb90((void*)(iv + 0x24));
                    }
                    else
                    {
                        *(float*)(self + 0x94) = FUN_007cdb90((void*)(iv + 0x1c));
                    }
                }
                *(uint8_t*)(self + 0x38) = (param_2 != 0);
                if (-1 < *(int*)(self + 0x22c))
                {
                    void* P = *(void**)(self + 0x24);
                    int* piVar3 = (int*)((int (__thiscall*)(void*))((void**)(*(void**)P))[0x20 / 4])(P);
                    ((void (__thiscall*)(int*, int, int))((void**)(*(void**)piVar3))[0x24 / 4])(piVar3, *(int*)(self + 0x22c), *(uint8_t*)(self + 0xe));
                    return;
                }
                if (-1 < *(int*)(self + 0x228))
                {
                    void* P = *(void**)(self + 0x24);
                    int* piVar3 = (int*)((int (__thiscall*)(void*))((void**)(*(void**)P))[0x20 / 4])(P);
                    ((void (__thiscall*)(int*, int, int))((void**)(*(void**)piVar3))[0x38 / 4])(piVar3, *(int*)(self + 0x228), *(uint8_t*)(self + 0xe));
                }
    }
}

// ---------------------------------------------------------------------------
// @ 0x00aa8840
// ---------------------------------------------------------------------------
struct HandleObj
{
    char pad00[0x220];
    int  cur;                     // +0x220

    void __thiscall FUN_00aa8840(int param_2);   // 0x00aa8840
};

void HandleObj::FUN_00aa8840(int param_2)
{
    int iVar1;
    if (param_2 == 0)
        param_2 = 0;
    else
        param_2 = param_2 - 8;

    iVar1 = this->cur;
    if (param_2 == iVar1)
    {
        *(uint8_t*)(iVar1 + 0x22c) = 1;
        return;
    }
    if (param_2 != 0)
    {
        ((void (__thiscall*)(int*))(*(void***)(param_2 + 8))[0x34 / 4])((int*)(param_2 + 8));
    }
    this->cur = param_2;
    if (iVar1 != 0)
    {
        ((void (__thiscall*)(int*))(*(void***)(iVar1 + 8))[0x38 / 4])((int*)(iVar1 + 8));
        *(uint8_t*)(this->cur + 0x22c) = 1;
        return;
    }
    *(uint8_t*)(param_2 + 0x22c) = 1;
}

// ---------------------------------------------------------------------------
// @ 0x00aa88c0
// ---------------------------------------------------------------------------
struct SwarmEmitter
{
    void __thiscall FUN_00aa88c0(int param_2, int param_3);   // 0x00aa88c0
};

void SwarmEmitter::FUN_00aa88c0(int param_2, int param_3)
{
    char* self = (char*)this;
    int iVar1 = *(int*)(self + 0x24);
    float* pfVar2 = *(float**)(iVar1 + 0x88);
    float fVar6 = *(float*)(self + 0x198) * *(float*)(param_2 + 0x28);

    if (pfVar2 != *(float**)(iVar1 + 0x8c))
    {
        volatile float ratio = *(float*)(param_2 + 8) / *(float*)(param_2 + 0xc);
        int iVar3 = (int)((*(int*)(iVar1 + 0x8c) - (int)pfVar2) >> 2) - 1;
        float fVar4;
        if (iVar3 == 0)
        {
            fVar4 = *pfVar2;
        }
        else
        {
            float fVar5 = (float)(unsigned)iVar3;
            fVar5 = fVar5 * ratio;
            iVar3 = (int)fVar5;
            int iv = *(int*)(iVar1 + 0x88);
            fVar5 = fVar5 - (float)iVar3;
            fVar4 = *(float*)(iv + iVar3 * 4);
            if (fVar5 > 0.0f)
                fVar4 = (*(float*)(iv + 4 + iVar3 * 4) - fVar4) * fVar5 + fVar4;
        }
        fVar6 = fVar4 * fVar6;
    }

    FUN_00a7f5a0(*(int*)(self + 0x28), *(int*)(self + 0x2c), (int)(self + 0x1e4),
                 *(int*)(self + 0x1fc), *(float*)(self + 0x110) * fVar6, param_3,
                 param_2 + 0x10, param_2 + 0x1c, *(char*)(self + 0x16) == 0,
                 (int)(self + 0x100), 0);
}

// ---------------------------------------------------------------------------
// @ 0x00aa89d0
// ---------------------------------------------------------------------------
void SwarmPath::FUN_00aa89d0(float* param_2)
{
    char* c = (char*)this;
    float fVar7 = param_2[0] - *(float*)(c + 0x104);
    float fVar6 = param_2[1] - *(float*)(c + 0x108);
    float fVar5 = param_2[2] - *(float*)(c + 0x10c);
    Vec3 v;
    uint32_t local_24[9];

    if (*(float*)(c + 0x110) != 1.0f)
    {
        float fVar4 = 1.0f / *(float*)(c + 0x110);
        fVar7 = fVar4 * fVar7;
        fVar6 = fVar6 * fVar4;
        fVar5 = fVar5 * fVar4;
    }
    float fVar4 = fVar6;
    float fVar3 = fVar7;
    if ((*(uint8_t*)(c + 0x100) & 2) != 0)
    {
        fVar3 = (*(float*)(c + 0x11c) * fVar5 + *(float*)(c + 0x118) * fVar6) + *(float*)(c + 0x114) * fVar7;
        fVar4 = (*(float*)(c + 0x128) * fVar5 + *(float*)(c + 0x124) * fVar6) + *(float*)(c + 0x120) * fVar7;
        fVar5 = (*(float*)(c + 0x134) * fVar5 + *(float*)(c + 0x130) * fVar6) + *(float*)(c + 0x12c) * fVar7;
    }
    v.x = fVar3 - *(float*)(c + 0xcc);
    v.y = fVar4 - *(float*)(c + 0xd0);
    v.z = fVar5 - *(float*)(c + 0xd4);
    if (*(float*)(c + 0xd8) != 1.0f)
    {
        float fVar = 1.0f / *(float*)(c + 0xd8);
        v.x = fVar * v.x;
        v.y = v.y * fVar;
        v.z = v.z * fVar;
    }
    if ((*(uint8_t*)(c + 0xc8) & 2) != 0)
    {
        float ox = v.x, oy = v.y, oz = v.z;
        v.x = (*(float*)(c + 0xe4) * oz + *(float*)(c + 0xe0) * oy) + *(float*)(c + 0xdc) * ox;
        v.y = (*(float*)(c + 0xf0) * oz + *(float*)(c + 0xec) * oy) + ox * *(float*)(c + 0xe8);
        v.z = (*(float*)(c + 0xfc) * oz + *(float*)(c + 0xf8) * oy) + *(float*)(c + 0xf4) * ox;
    }
    fVar7 = (*(float*)(*(int*)(c + 0x24) + 0x14) + *(float*)(*(int*)(c + 0x24) + 0x10)) * 0.5f;
    fVar6 = (fVar7 * fVar7) * 0.5f;
    v.z = v.z - *(float*)(c + 0x6c) * fVar6;
    v.y = v.y - *(float*)(c + 0x68) * fVar6;
    v.x = v.x - *(float*)(c + 0x64) * fVar6;
    fVar6 = (float)sqrt(((double)v.z * v.z + (double)v.y * v.y) + (double)v.x * v.x);
    if (0.0f < fVar6)
    {
        float fVar = 1.0f / fVar6;
        v.x = v.x * fVar;
        v.y = v.y * fVar;
        v.z = v.z * fVar;
    }
    FUN_00a81a20(&v, local_24);
    *(uint16_t*)(c + 0xc8) = *(uint16_t*)(c + 0xc8) | 2;
    *(int16_t*)(c + 0xca) = *(int16_t*)(c + 0xca) + 1;
    for (int i = 0; i < 9; i++)
        ((uint32_t*)(c + 0xdc))[i] = local_24[i];
    *(float*)(c + 0x160) =
        ((1.0f / fVar7) /
         ((*(float*)(*(int*)(c + 0x24) + 0x48) + *(float*)(*(int*)(c + 0x24) + 0x44)) * 0.5f)) * fVar6;
}

// ---------------------------------------------------------------------------
// @ 0x00aa8d30
// ---------------------------------------------------------------------------
int __cdecl FUN_00aa8d30(int param_1, int param_2, uint32_t* param_3, int param_4)
{
    int iVar3;
    int iStack_4 = 0;

    FUN_00a6c7a0(param_2 + 0x110, (*(uint32_t*)(param_2 + 8) >> 0x15) & 1, &iStack_4, (void**)&param_3, &param_4);
    (void)param_1;

    iVar3 = (*(int*)(param_2 + 0x1b0) - *(int*)(param_2 + 0x1ac)) / 0x58;
    for (int off = 0; iVar3 > 0; iVar3--, off += 0x58)
    {
        uint32_t uVar1 = *(uint32_t*)(off + 8 + *(int*)(param_2 + 0x1ac));
        uint32_t uVar2 = *(uint32_t*)(off + 0xc + *(int*)(param_2 + 0x1ac));
        if ((uVar1 & uVar2) != 0xffffffff)
        {
            iStack_4++;
            if (param_4 > 0)
            {
                *param_3 = uVar1;
                param_3[1] = uVar2;
                param_3[2] = 7;
                param_3 += 4;
                param_4--;
            }
        }
    }
    {
        uint32_t uVar1 = *(uint32_t*)(param_2 + 0x1ec);
        if ((*(uint32_t*)(param_2 + 0x1e8) & uVar1) != 0xffffffff)
        {
            iStack_4++;
            if (param_4 > 0)
            {
                *param_3 = *(uint32_t*)(param_2 + 0x1e8);
                param_3[1] = uVar1;
                param_3[2] = 5;
                param_3 += 4;
                param_4--;
            }
        }
    }
    {
        uint32_t uVar1 = *(uint32_t*)(param_2 + 0x1f4);
        if ((*(uint32_t*)(param_2 + 0x1f0) & uVar1) != 0xffffffff)
        {
            iStack_4++;
            if (param_4 > 0)
            {
                *param_3 = *(uint32_t*)(param_2 + 0x1f0);
                param_3[1] = uVar1;
                param_3[2] = 5;
                param_3 += 4;
                param_4--;
            }
        }
    }
    {
        uint32_t uVar1 = *(uint32_t*)(param_2 + 0x1fc);
        if ((*(uint32_t*)(param_2 + 0x1f8) & uVar1) != 0xffffffff)
        {
            iStack_4++;
            if (param_4 > 0)
            {
                *param_3 = *(uint32_t*)(param_2 + 0x1f8);
                param_3[1] = uVar1;
                param_3[2] = 5;
            }
        }
    }
    return iStack_4;
}

// ---------------------------------------------------------------------------
// @ 0x00aa8ea0
// ---------------------------------------------------------------------------
void __stdcall FUN_00aa8ea0(int* param_1, int* param_2)
{
    int* piVar1 = (int*)param_2[1];
    int iVar2 = *param_2;
    *piVar1 = iVar2;
    *(int**)(iVar2 + 4) = piVar1;
    *param_2 = 0;
    param_2[1] = 0;
    *param_1 = iVar2;
}

// ---------------------------------------------------------------------------
// @ 0x00aa8ed0
// ---------------------------------------------------------------------------
struct SwarmEd0
{
    void __thiscall FUN_00aa8ed0(int param_1, int param_2);   // 0x00aa8ed0
};

void SwarmEd0::FUN_00aa8ed0(int param_1, int param_2)
{
    char* self = (char*)this;
    uint16_t uVar4 = *(uint16_t*)(self + 0xfa);
    uint16_t uVar5 = *(uint16_t*)(self + 0xc2);

    ((cSPTransformOps*)(self + 0xc0))->Assign((const void*)param_1);
    ((cSPTransformOps*)(self + 0xf8))->Assign((const void*)param_2);

    if ((uint32_t)uVar4 + (uint32_t)uVar5 !=
        (uint32_t)*(uint16_t*)(self + 0xfa) + (uint32_t)*(uint16_t*)(self + 0xc2))
    {
        if (*(int*)(self + 0x1d8) != 0)
            ((SwarmPath*)(self - 8))->FUN_00aa89d0(*(float**)(self + 0x1d8));

        float fVar2 = *(float*)(self + 0xb4);
        float fVar6 = *(float*)(self + 0xb8);
        float fVar7 = *(float*)(self + 0xbc);
        *(uint8_t*)(self + 0x1f0) = 0;
        *(uint32_t*)(self + 0xb4) = *(uint32_t*)(self + 0xc4);
        *(uint32_t*)(self + 0xb8) = *(uint32_t*)(self + 0xc8);
        *(uint32_t*)(self + 0xbc) = *(uint32_t*)(self + 0xcc);
        ((VTX*)(self + 0xf8))->FUN_007cdee0((float*)(self + 0xb4));

        float fVar3 = *(float*)(self + 0x98);
        fVar6 = *(float*)(self + 0xb8) - fVar6;
        fVar7 = *(float*)(self + 0xbc) - fVar7;
        if (fVar3 != g_01565620 && fVar3 != -g_01565620)
        {
            *(float*)(self + 0x98) = fVar3 + (*(float*)(self + 0xb4) - fVar2);
            *(float*)(self + 0x9c) = fVar6 + *(float*)(self + 0x9c);
            *(float*)(self + 0xa0) = fVar7 + *(float*)(self + 0xa0);
            *(float*)(self + 0xa4) = *(float*)(self + 0xa4) + (*(float*)(self + 0xb4) - fVar2);
            *(float*)(self + 0xa8) = fVar6 + *(float*)(self + 0xa8);
            *(float*)(self + 0xac) = fVar7 + *(float*)(self + 0xac);
        }
    }
}
