// Slice s006de020: insertion-sort/heap helpers, mesh buffer init/teardown and
// image-region packing helpers from the D3D9 buffer-draw module.
#include "../s006ccf50/s006ccf50.h"

// ---- external helpers / globals (relocations are masked) --------------------
int* g_bufferDraw = 0;          // 0x01607728 cBufferDrawImpl singleton
int* _sAppProperties = 0;
void* __cdecl SP_CreateMesh(int type);        // SP::CreateMesh
int __cdecl FUN_00762c60(void* desc, int a, int b, int c, int d, int e);
int __cdecl FUN_00762a30(void* p);
int __cdecl FUN_011f4f20(int a, void* out);
void __cdecl FUN_011f4fd0(void* p);
void __cdecl FUN_00f47410(void* p);
int __cdecl FUN_011f1120();
void __cdecl FUN_006dd8b0();
void __cdecl FUN_006dd540(int a);
void __cdecl FUN_006ddd80(int a, int b, int c, int d);
int __cdecl FUN_006dd9b0(void* self, int count, void* out, uint32_t* stride, int flag);
void __cdecl CompiledState_Dispatch(void* cs);
void __cdecl GlobalState_D3D9Sync();

void* __cdecl sp_op_new(uint32_t size, const char* tag, int a, int b, const char* file, int line);

void* DAT_016079a0 = 0;
void* DAT_016079a4 = 0;
int DAT_016079a8 = 0;
int DAT_016f9200 = 0;
int DAT_01532b94 = 0;

// ---------------------------------------------------------------------------
// 0x006de020: draw an image quad / NDC quad.
void FUN_006de020(int param_1, int param_2, int param_3)   // @ 0x006de020
{
    int uVar1 = DAT_016f9200;
    DAT_016f9200 = 3;
    float local_18 = 0.0f;
    float local_14 = 0.0f;
    if (*(int*)(*(int*)((char*)_sAppProperties + 0x3c) + 0x110) != 0)
    {
        int iVar2 = FUN_011f1120();
        local_18 = -1.0f / (float)*(uint16_t*)(*(int*)(iVar2 + 0x40) + 0xc);
        iVar2 = FUN_011f1120();
        local_14 = 1.0f / (float)*(uint16_t*)(*(int*)(iVar2 + 0x40) + 0xe);
    }
    *(int*)((char*)g_bufferDraw + 0x1a0) = 1;
    float* local_10 = 0;
    uint32_t local_c = 0;
    int iVar2 = FUN_006dd9b0(g_bufferDraw, 4, &local_10, &local_c, 0);
    if (iVar2 != 4)
    {
        FUN_006dd8b0();
        DAT_016f9200 = uVar1;
        return;
    }
    local_10[0] = local_18 - 1.0f;
    local_10[1] = local_14 - 1.0f;
    local_10[2] = 0.0f;
    local_10[3] = 0.0f;
    local_10[4] = 1.0f;
    local_10[5] = local_18 + 1.0f;
    local_10[6] = local_14 - 1.0f;
    local_10[7] = 0.0f;
    local_10[8] = 1.0f;
    local_10[9] = 1.0f;
    local_10[10] = local_18 + 1.0f;
    local_10[0xb] = local_14 + 1.0f;
    local_10[0xc] = 0.0f;
    local_10[0xd] = 1.0f;
    local_10[0xf] = local_18 - 1.0f;
    local_10[0xe] = 0.0f;
    local_10[0x10] = local_14 + 1.0f;
    local_10[0x11] = 0.0f;
    local_10[0x12] = 0.0f;
    local_10[0x13] = 0.0f;
    if (param_2 != 0)
    {
        FUN_006ddd80(5, param_1, param_2, param_3);
        DAT_016f9200 = uVar1;
        return;
    }
    FUN_006dd8b0();
    CompiledState_Dispatch(*(void**)(param_1 + 4));
    GlobalState_D3D9Sync();
    *(int*)((char*)g_bufferDraw + 0x1a4) = 5;
    FUN_006dd540(param_3);
    DAT_016f9200 = uVar1;
}

// ---------------------------------------------------------------------------
// 0x006de2a0: lazily create the shared quad mesh + index buffer.
struct MeshBuf { int Lock(int a, void* out); void Unlock(void* p); };   // 0x011f4f20 / 0x011f4fd0
extern int DAT_015d07b0;

void FUN_006de2a0(void)   // @ 0x006de2a0
{
    int local_c[3];
    if (DAT_016079a8 == 0)
    {
        DAT_016079a0 = SP_CreateMesh(1);
        DAT_016079a4 = (void*)FUN_00762c60((void*)&DAT_015d07b0, 0xffc, 0x2ff4, 8, 4, 0);
        if (((MeshBuf*)DAT_016079a4)->Lock(2, local_c) != 0)
        {
            int i = 0;
            short* ps = (short*)(local_c[0] + 4);
            do
            {
                short s = (short)i;
                ps[-1] = s + 1;
                ps[-2] = s;
                ps[1] = s;
                ps[0] = s + 2;
                ps[2] = s + 2;
                ps[3] = s + 3;
                i += 4;
                ps += 6;
            } while (i < 0x1ff8);
            ((MeshBuf*)DAT_016079a4)->Unlock(local_c);
        }
    }
    DAT_016079a8 = DAT_016079a8 + 1;
}

// ---------------------------------------------------------------------------
// 0x006de350: release the shared quad mesh when the last user goes away.
void FUN_006de350(void)   // @ 0x006de350
{
    DAT_016079a8 = DAT_016079a8 - 1;
    if (DAT_016079a8 == 0)
    {
        if (DAT_016079a4 != 0)
        {
            FUN_00762a30(DAT_016079a4);
            DAT_016079a4 = 0;
        }
        if (DAT_016079a0 != 0)
        {
            FUN_00f47410(DAT_016079a0);
            DAT_016079a0 = 0;
        }
    }
}

// ---------------------------------------------------------------------------
// 0x006de3a0: binary insertion sort, descending key at (elem+4).
void FUN_006de3a0(int* param_1, int* param_2)   // @ 0x006de3a0
{
    int* pi2 = param_1;
    if (param_1 != param_2)
    {
        while (pi2 = pi2 + 1, pi2 != param_2)
        {
            int v = *pi2;
            int* pi3 = pi2;
            while (pi3 != param_1 && *(uint32_t*)(v + 4) > *(uint32_t*)(pi3[-1] + 4))
            {
                *pi3 = pi3[-1];
                pi3 = pi3 - 1;
            }
            *pi3 = v;
        }
    }
}

// 0x006de3f0: binary insertion sort variant.
void FUN_006de3f0(int* param_1, int* param_2)   // @ 0x006de3f0
{
    for (; param_1 != param_2; param_1 = param_1 + 1)
    {
        int v = *param_1;
        int prev = param_1[-1];
        int* ecx = param_1 - 1;
        int* eax = param_1;
        if (*(uint32_t*)(v + 4) > *(uint32_t*)(prev + 4))
        {
            do
            {
                *eax = prev;
                eax = ecx;
                prev = eax[-1];
                ecx = eax - 1;
            } while (*(uint32_t*)(v + 4) > *(uint32_t*)(prev + 4));
        }
        *eax = v;
    }
}

// 0x006de440: binary insertion sort (opposite comparison).
void FUN_006de440(int* param_1, int* param_2)   // @ 0x006de440
{
    int* pi2 = param_1;
    if (param_1 != param_2)
    {
        while (pi2 = pi2 + 1, pi2 != param_2)
        {
            int v = *pi2;
            int* pi3 = pi2;
            while (pi3 != param_1 && *(uint32_t*)(v + 4) < *(uint32_t*)(pi3[-1] + 4))
            {
                *pi3 = pi3[-1];
                pi3 = pi3 - 1;
            }
            *pi3 = v;
        }
    }
}

// 0x006de490: binary insertion sort variant (opposite comparison).
void FUN_006de490(int* param_1, int* param_2)   // @ 0x006de490
{
    for (; param_1 != param_2; param_1 = param_1 + 1)
    {
        int v = *param_1;
        int prev = param_1[-1];
        int* ecx = param_1 - 1;
        int* eax = param_1;
        if (*(uint32_t*)(v + 4) < *(uint32_t*)(prev + 4))
        {
            do
            {
                *eax = prev;
                eax = ecx;
                prev = eax[-1];
                ecx = eax - 1;
            } while (*(uint32_t*)(v + 4) < *(uint32_t*)(prev + 4));
        }
        *eax = v;
    }
}

// 0x006de4e0: heap sift-up (unsigned compare).
void FUN_006de4e0(int param_1, int param_2, int param_3, int param_4)   // @ 0x006de4e0
{
    if (param_3 <= param_2)
    {
        *(int*)(param_1 + param_3 * 4) = param_4;
        return;
    }
    int iVar2;
    do
    {
        iVar2 = (param_3 + -1) >> 1;
        int iVar1 = *(int*)(param_1 + iVar2 * 4);
        if (*(uint32_t*)(iVar1 + 4) <= *(uint32_t*)(param_4 + 4))
            break;
        *(int*)(param_1 + param_3 * 4) = iVar1;
        param_3 = iVar2;
    } while (param_2 < iVar2);
    *(int*)(param_1 + param_3 * 4) = param_4;
}

// 0x006de530: heap sift-up (signed compare).
void FUN_006de530(int param_1, int param_2, int param_3, int param_4)   // @ 0x006de530
{
    if (param_3 <= param_2)
    {
        *(int*)(param_1 + param_3 * 4) = param_4;
        return;
    }
    int iVar2;
    do
    {
        iVar2 = (param_3 + -1) >> 1;
        int iVar1 = *(int*)(param_1 + iVar2 * 4);
        if (*(uint32_t*)(param_4 + 4) <= *(uint32_t*)(iVar1 + 4))
            break;
        *(int*)(param_1 + param_3 * 4) = iVar1;
        param_3 = iVar2;
    } while (param_2 < iVar2);
    *(int*)(param_1 + param_3 * 4) = param_4;
}

// 0x006de580: heap sift-up for 0x34-byte elements.
void FUN_006de580(int param_1, int param_2, int param_3, uint32_t param_4, ...)   // @ 0x006de580
{
    uint32_t* args = &param_4;
    while (param_2 < param_3)
    {
        int iVar1 = (param_3 + -1) >> 1;
        int iVar2 = iVar1 * 0x34;
        if (*(uint32_t*)(iVar2 + 8 + param_1) <= args[2])
            break;
        uint32_t* pu4 = (uint32_t*)(iVar2 + param_1);
        uint32_t* pu5 = (uint32_t*)(param_3 * 0x34 + param_1);
        for (int i = 0xd; param_3 = iVar1, i != 0; --i)
            *pu5++ = *pu4++;
    }
    uint32_t* pu4 = args;
    uint32_t* pu5 = (uint32_t*)(param_3 * 0x34 + param_1);
    for (int i = 0xd; i != 0; --i)
        *pu5++ = *pu4++;
}

// ---------------------------------------------------------------------------
// 0x006de5e0: pick the best-fit image sub-block.
struct ImagePacker
{
    char pad[0x25c];
    int* mOffsets;
    void BestFit(int param_2);   // 0x006de5e0
    void BestFit2(int param_2);  // 0x006de710
};

void ImagePacker::BestFit(int param_2)   // @ 0x006de5e0
{
    int local_20, local_1c, local_18, local_14, local_10;
    local_18 = -1;
    local_10 = -1;
    int iVar7 = (*(int*)(param_2 + 0x4c) - *(int*)(param_2 + 0x48)) >> 2;
    local_14 = DAT_01532b94 * iVar7;
    bool bVar1 = false;
    bool bVar2 = false;
    local_1c = 0;
    if (-1 < DAT_01532b94 - iVar7)
    {
        do
        {
            int iVar6 = 0, iVar3 = 0;
            local_20 = 0;
            if (0 < iVar7)
            {
                int* pi5 = *(int**)(param_2 + 0x48);
                int* pi8 = (int*)(mOffsets + local_1c);
                do
                {
                    int iVar4 = *pi8 - *pi5;
                    bVar1 = bVar2;
                    if (DAT_01532b94 <= *(int*)(param_2 + 0x5c) + iVar4)
                        goto next;
                    local_20 += iVar4;
                    if (iVar3 < iVar4)
                        iVar3 = iVar4;
                    ++iVar6;
                    ++pi8;
                    ++pi5;
                } while (iVar6 < iVar7);
            }
            local_20 = iVar3 * iVar7 - local_20;
            if (local_20 < local_14)
            {
                bVar2 = true;
                local_18 = iVar3;
                local_14 = local_20;
                local_10 = local_1c;
                bVar1 = true;
            }
        next:
            ++local_1c;
        } while (local_1c <= DAT_01532b94 - iVar7);
        if (bVar1)
        {
            *(int*)(param_2 + 100) = local_18;
            int iVar3 = 0;
            *(int*)(param_2 + 0x60) = local_10;
            if (0 < iVar7)
            {
                int off = local_10 * 4;
                do
                {
                    *(int*)((char*)mOffsets + off) = *(int*)(*(int*)(param_2 + 0x34) + iVar3 * 4) + local_18;
                    ++iVar3;
                    off += 4;
                } while (iVar3 < iVar7);
            }
        }
    }
}

void ImagePacker::BestFit2(int param_2)   // @ 0x006de710
{
    int iVar7 = (*(int*)(param_2 + 0x4c) - *(int*)(param_2 + 0x48)) >> 2;
    int local_10 = DAT_01532b94;
    int iVar2 = 0;
    int local_8 = 0;
    int iVar4 = 0;
    if (-1 < DAT_01532b94 - iVar7)
    {
        do
        {
            iVar4 = 0;
            if (0 < iVar7)
            {
                int* pi6 = *(int**)(param_2 + 0x48);
                int* pi3 = (int*)(mOffsets + iVar2);
                int iVar5 = iVar7;
                do
                {
                    if (iVar4 < *pi3 - *pi6)
                        iVar4 = *pi3 - *pi6;
                    ++pi3;
                    ++pi6;
                    --iVar5;
                } while (iVar5 != 0);
            }
            if (iVar4 < local_10)
            {
                local_10 = iVar4;
                local_8 = iVar2;
            }
            ++iVar2;
            iVar4 = local_8;
        } while (iVar2 <= DAT_01532b94 - iVar7);
    }
    *(int*)(param_2 + 0x60) = iVar4;
    *(int*)(param_2 + 100) = local_10;
    int iVar5 = 0;
    bool bVar1 = true;
    int off = iVar4 * 4;
    do
    {
        if (iVar7 <= iVar5)
            return;
        *(int*)((char*)mOffsets + off) = *(int*)(*(int*)(param_2 + 0x34) + iVar5 * 4) + local_10;
        if (DAT_01532b94 <= *(int*)((char*)mOffsets + off))
            bVar1 = false;
        ++iVar5;
        off += 4;
    } while (bVar1);
}

// 0x006de7f0: copy a 0x34-byte mesh record (member-wise; float fields via x87).
struct Rec13
{
    int a, b;               // +0, +4
    float c;                // +8
    int d;                  // +c
    float e, f, g, h, i, j, k;   // +10..+28
    int l;                  // +2c
    float m;                // +30
    Rec13& operator=(const Rec13& src);   // 0x006de7f0
};

Rec13& Rec13::operator=(const Rec13& src)   // @ 0x006de7f0
{
    a = src.a;
    b = src.b;
    c = src.c;
    d = src.d;
    e = src.e;
    f = src.f;
    g = src.g;
    h = src.h;
    i = src.i;
    j = src.j;
    k = src.k;
    l = src.l;
    m = src.m;
    return *this;
}

// ---------------------------------------------------------------------------
// 0x006de850: construct a run of 0x10-byte ref-counted elements.
struct Elem16
{
    uint32_t a, b;
    uint16_t c, d;
    uint32_t pad;
    RefObject* mpRef;   // +0xc
};

int* FUN_006de850(int* param_1, uint32_t* param_2, uint32_t* param_3, int param_4)   // @ 0x006de850
{
    *param_1 = param_4;
    for (; param_2 != param_3; param_2 += 4)
    {
        Elem16* dst = (Elem16*)*param_1;
        if (dst != 0)
        {
            dst->a = param_2[0];
            dst->b = param_2[1];
            dst->c = *(uint16_t*)(param_2 + 2);
            dst->d = *(uint16_t*)((char*)param_2 + 10);
            dst->mpRef = (RefObject*)param_2[3];
            if (dst->mpRef)
                dst->mpRef->AddRef();
        }
        *param_1 = *param_1 + 0x10;
    }
    return param_1;
}

// 0x006de8f0: fill a run of 0x10-byte ref-counted elements from one source.
void FUN_006de8f0(uint32_t* param_1, int param_2, uint32_t* param_3)   // @ 0x006de8f0
{
    for (; param_2 != 0; --param_2)
    {
        if (param_1 != 0)
        {
            param_1[0] = param_3[0];
            param_1[1] = param_3[1];
            *(uint16_t*)(param_1 + 2) = *(uint16_t*)(param_3 + 2);
            *(uint16_t*)((char*)param_1 + 10) = *(uint16_t*)((char*)param_3 + 10);
            RefObject* p = (RefObject*)param_3[3];
            param_1[3] = (uint32_t)p;
            if (p)
                p->AddRef();
        }
        param_1 += 4;
    }
}

// ---------------------------------------------------------------------------
// 0x006de980: heap sift-down -> sift-up (unsigned).
void FUN_006de980(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)   // @ 0x006de980
{
    int iVar1, iVar2;
    while (true)
    {
        iVar1 = param_4 * 2;
        iVar2 = iVar1 + 2;
        if (param_3 <= iVar2)
            break;
        if (*(uint32_t*)(*(int*)(param_1 + -4 + iVar2 * 4) + 4) <
            *(uint32_t*)(*(int*)(param_1 + iVar2 * 4) + 4))
            iVar2 = iVar1 + 1;
        *(int*)(param_1 + param_4 * 4) = *(int*)(param_1 + iVar2 * 4);
        param_4 = iVar2;
    }
    if (iVar2 == param_3)
    {
        *(int*)(param_1 + param_4 * 4) = *(int*)(param_1 + -4 + iVar2 * 4);
        param_4 = iVar1 + 1;
    }
    FUN_006de4e0(param_1, param_2, param_4, param_5);
}

// 0x006de9f0: heap sift-down -> sift-up (signed).
void FUN_006de9f0(int param_1, int param_2, int param_3, int param_4, int param_5, int param_6)   // @ 0x006de9f0
{
    int iVar1, iVar2;
    while (true)
    {
        iVar1 = param_4 * 2;
        iVar2 = iVar1 + 2;
        if (param_3 <= iVar2)
            break;
        if (*(uint32_t*)(*(int*)(param_1 + iVar2 * 4) + 4) <
            *(uint32_t*)(*(int*)(param_1 + -4 + iVar2 * 4) + 4))
            iVar2 = iVar1 + 1;
        *(int*)(param_1 + param_4 * 4) = *(int*)(param_1 + iVar2 * 4);
        param_4 = iVar2;
    }
    if (iVar2 == param_3)
    {
        *(int*)(param_1 + param_4 * 4) = *(int*)(param_1 + -4 + iVar2 * 4);
        param_4 = iVar1 + 1;
    }
    FUN_006de530(param_1, param_2, param_4, param_5);
}

// 0x006dea60: heap sift-down for 0x34-byte elements.
void FUN_006dea60(int param_1, int param_2, int param_3, int param_4, ...)   // @ 0x006dea60
{
    int iVar1, iVar2;
    while (true)
    {
        iVar2 = param_4 * 2;
        iVar1 = iVar2 + 2;
        if (param_3 <= iVar1)
            break;
        if (*(uint32_t*)(iVar1 * 0x34 + param_1 + -0x2c) < *(uint32_t*)(iVar1 * 0x34 + 8 + param_1))
            iVar1 = iVar2 + 1;
        uint32_t* pu4 = (uint32_t*)(iVar1 * 0x34 + param_1);
        uint32_t* pu5 = (uint32_t*)(param_4 * 0x34 + param_1);
        for (int i = 0xd; param_4 = iVar1, i != 0; --i)
            *pu5++ = *pu4++;
    }
    if (iVar1 == param_3)
    {
        uint32_t* pu4 = (uint32_t*)(iVar1 * 0x34 + -0x34 + param_1);
        uint32_t* pu5 = (uint32_t*)(param_4 * 0x34 + param_1);
        for (int i = 0xd; i != 0; --i)
            *pu5++ = *pu4++;
        param_4 = iVar2 + 1;
    }
    FUN_006de580(param_1, param_2, param_4, 0, 0, 0, 0);
}

// 0x006deb70: make-heap on a newly pushed 0x34-byte element.
void FUN_006deb70(uint32_t* param_1, int param_2, uint32_t param_3)   // @ 0x006deb70
{
    uint32_t* pu15 = param_1;
    uint32_t* pu16 = (uint32_t*)(param_2 - 0x34);
    for (int i = 0xd; i != 0; --i)
        *pu16++ = *pu15++;
    FUN_006dea60((int)param_1, 0, ((param_2 - (int)param_1) / 0x34) - 1, 0);
}

// ---------------------------------------------------------------------------
// 0x006dec60: scale a mesh's position/uv data by sqrt(scale).
void FUN_006dec60(int param_1, int* param_2, float param_3)   // @ 0x006dec60
{
    if ((char)param_2[0xc] == '\0')
    {
        float f = (float)sqrt(param_3);
        int iVar4 = *param_2 * 0x10 + *(int*)(param_1 + 0x18);
        int iVar3 = param_2[3];
        if (iVar3 < param_2[4])
        {
            do
            {
                float* pf = (float*)((uint32_t)*(uint16_t*)(iVar4 + 10) * iVar3 + *(int*)(iVar4 + 4));
                ++iVar3;
                pf[0] = pf[0] * f;
                pf[1] = pf[1] * f;
            } while (iVar3 < param_2[4]);
        }
        iVar3 = 0;
        int n = (param_2[6] - param_2[5]) >> 3;
        if (3 < n)
        {
            do
            {
                int off = iVar3 * 8;
                float* pf = (float*)(param_2[5] + off);
                pf[0] = *(float*)(param_2[5] + off) * f;
                pf[1] = pf[1] * f;
                pf = (float*)(param_2[5] + 8 + off);
                pf[0] = *(float*)(param_2[5] + 8 + off) * f;
                pf[1] = pf[1] * f;
                off += 0x18;
                pf = (float*)(param_2[5] + -8 + off);
                pf[0] = *(float*)(param_2[5] + -8 + off) * f;
                pf[1] = pf[1] * f;
                pf = (float*)(param_2[5] + off);
                pf[0] = *(float*)(param_2[5] + off) * f;
                iVar3 += 4;
                pf[1] = pf[1] * f;
            } while (iVar3 < n - 3);
        }
        for (; iVar3 < n; ++iVar3)
        {
            float* pf = (float*)(param_2[5] + iVar3 * 8);
            pf[0] = *(float*)(param_2[5] + iVar3 * 8) * f;
            pf[1] = pf[1] * f;
        }
        param_2[0xb] = (int)(f * (float)param_2[0xb]);
        param_2[10] = (int)((float)param_2[10] * f);
        param_2[1] = (int)(param_3 * (float)param_2[1]);
    }
}

// 0x006dede0: insertion sort of 13-dword records by dword[+4].
void FUN_006dede0(uint32_t* param_1, uint32_t* param_2)   // @ 0x006dede0
{
    if (param_1 != param_2)
    {
        uint32_t* pu3 = param_1 + 0xd;
        if (pu3 != param_2)
        {
            uint32_t* pu1 = param_1 + 0x14;
            do
            {
                uint32_t tmp[13];
                tmp[2] = pu1[-5];
                tmp[3] = pu1[-4];
                tmp[0] = *pu3;
                tmp[1] = pu1[-6];
                tmp[4] = pu1[-3];
                tmp[5] = pu1[-2];
                tmp[6] = pu1[-1];
                tmp[7] = *pu1;
                tmp[8] = pu1[1];
                tmp[9] = pu1[2];
                tmp[10] = pu1[3];
                tmp[11] = pu1[4];
                tmp[12] = pu1[5];
                uint32_t* pu7 = pu3;
                while (pu7 != param_1 && pu7[-0xb] < tmp[2])
                {
                    uint32_t* pu5 = pu7 - 0xd;
                    uint32_t* pu6 = pu7;
                    uint32_t* pu4 = pu5;
                    for (int i = 0xd; pu7 = pu5, i != 0; --i)
                        *pu6++ = *pu4++;
                }
                pu3 += 0xd;
                pu1 += 0xd;
                uint32_t* pu5 = tmp;
                for (int i = 0xd; i != 0; --i)
                    *pu7++ = *pu5++;
            } while (pu3 != param_2);
        }
    }
}
