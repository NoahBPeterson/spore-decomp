// Mopp (Multiresolution Oriented Point Pair) compiler helpers (slice s0111d560).
// Built with VS2008 SP1 (cl 15.00.30729.01) at /arch:SSE /fp:fast.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// Extern helpers (addresses from the original image)
// ---------------------------------------------------------------------------
extern float __cdecl FUN_0120ac90(float x);                                  // 0x0120ac90  hkFloor
extern int   __cdecl FUN_0120ad30(float x);                                  // 0x0120ad30  hkFloatToInt

extern float g_01488874;   // 0x1488874   0.1f
extern float g_013eb964;   // 0x13eb964  -0.1f
extern float g_01485378;   // 0x1485378   0.0f
extern float g_01487180;   // 0x1447180 254.0f
extern float g_0142ea5c;   // 0x142ea5c 65536.0f

struct MoppCodeWriter
{
    char pad00[0x0c];
    int  cursor;                                  // +0x0c
    void putByte(int b);                          // 0x0111eb70
};

// ---------------------------------------------------------------------------
// Stub: the Mopp compiler object (ECX in the original).
//   +0x10  writer pointer        +0x18  max depth
//   +0x30  per-axis cell origin (3 floats = +0x30,+0x34,+0x38)
//   +0x3c  saturation / cell scale       +0x48  minimum cell size
//   +0x50  per-axis scan values (3 floats)
// ---------------------------------------------------------------------------
struct MoppCompiler
{
    char  pad00[0x10];
    void* writer;                                 // +0x10
    char  pad14[4];
    int   maxDepth;                               // +0x18
    char  pad1c[0x30 - 0x1c];
    float origin[3];                              // +0x30
    float sat;                                    // +0x3c
    char  pad40[8];
    float minCell;                                // +0x48
    float scan[3];                                // +0x50

    void putByte(int b);                          // 0x0111eb70
    void FUN_0111d260(int a);                     // 0x0111d260
    void FUN_0111d7f0(int param_2, int param_3);                              // 0x0111d7f0
    void FUN_0111d8e0(int p2, int p3, int p4, int p5, int p6);                // 0x0111d8e0
    void FUN_0111db80(int param_2, int param_3, int* param_4, int* param_5);  // 0x0111db80
    int  FUN_0111d560(int param_2, int param_3, int* param_4);                // 0x0111d560
};

// 0x0111d340 is a member helper whose ECX is the compiler object.
extern void __cdecl FUN_0111d340(MoppCompiler* self, int* p);
extern char* __cdecl FUN_0111d410(char* out, void* node, int a, int* b);      // 0x0111d410
extern void  __cdecl FUN_0111d450(void* a, int* b, char* out);                // 0x0111d450
extern void  __cdecl FUN_0111cdb0(void* a);                                   // 0x0111cdb0
extern void* __cdecl FUN_0111d2b0(void* a, void* b);                          // 0x0111d2b0

// ---------------------------------------------------------------------------
// @ 0x0111da50
// ---------------------------------------------------------------------------
int __stdcall FUN_0111da50(float* n)
{
    float f0 = n[0];
    if (f0 > g_01488874)
    {
        float f2 = n[2];
        int r = 0;
        if (f2 <= g_01488874)
        {
            if (g_013eb964 <= f2)
            {
                if (g_01488874 < n[1]) return 7;
                if (n[1] < g_013eb964) return 8;
            }
            else
            {
                r = 6;
                if (g_01488874 < n[1]) return 10;
                if (n[1] < g_013eb964) return 0xc;
            }
        }
        else
        {
            r = 5;
            if (g_01488874 < n[1]) return 9;
            if (n[1] < g_013eb964) return 0xb;
        }
        return r;
    }
    if (n[1] <= g_01488874) return 2;
    if (g_01488874 < n[2]) return 3;
    if (n[2] < g_013eb964) return 4;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x0111de80
// ---------------------------------------------------------------------------
void __stdcall FUN_0111de80(int param_1, int* param_2)
{
    float fVar3;
    float fVar4;
    int uVar1 = *(int*)(param_1 + 0x1c);
    int uVar2 = *(int*)(param_1 + 0x0c);
    param_2[1] = *(int*)(param_1 + 0x14);
    param_2[0] = uVar2;
    param_2[3] = 0;
    param_2[2] = uVar1;
    fVar3 = 0.0f;
    fVar4 = *(float*)(param_1 + 0x10) - *(float*)(param_1 + 0x0c);
    if (0.0f <= fVar4) {
        fVar3 = fVar4;
    }
    fVar4 = *(float*)(param_1 + 0x18) - *(float*)(param_1 + 0x14);
    if (fVar3 <= fVar4) {
        fVar3 = fVar4;
    }
    fVar4 = *(float*)(param_1 + 0x20) - *(float*)(param_1 + 0x1c);
    if (fVar3 <= fVar4) {
        fVar3 = fVar4;
    }
    *(float*)(param_2 + 3) = (254.0f / fVar3) * 65536.0f;
}

// ---------------------------------------------------------------------------
// @ 0x0111d7f0
// ---------------------------------------------------------------------------
void MoppCompiler::FUN_0111d7f0(int param_2, int param_3)
{
    float* local_18 = this->scan;                 // this+0x50
    int*   piVar6   = (int*)(param_2 + 0x50);
    int*   piVar5   = (int*)(param_3 + 0x10);
    float* pfVar7   = (float*)(param_2 + 0x0c);
    int    local_10 = 3;

    do
    {
        float fVar3 = (float)(1 << (*(uint32_t*)(param_3 + 0x24) & 0x1f)) / this->sat;
        if (fVar3 <= this->minCell)
            fVar3 = this->minCell;

        float fVar1 = *local_18;
        if (pfVar7[1] - *pfVar7 < fVar1 && fVar1 <= fVar3)
            fVar3 = fVar1;

        int iVar4 = FUN_0120ad30(this->sat * fVar3);
        int iVar2 = *(int*)((char*)pfVar7 + (param_3 - param_2));
        *piVar6 = *piVar5 + 1 + iVar4;
        piVar6[-3] = iVar2 - iVar4;

        local_18++;
        piVar6++;
        pfVar7 += 2;
        piVar5 += 2;
        local_10--;
    } while (local_10 != 0);
}

// ---------------------------------------------------------------------------
// @ 0x0111d8e0
// ---------------------------------------------------------------------------
void MoppCompiler::FUN_0111d8e0(int param_2, int param_3, int param_4, int param_5, int param_6)
{
    int   iVar1 = *(int*)((char*)this->writer + 0xc);
    char* iVar3 = (char*)(iVar1 - param_6);

    if (param_4 < 3)
    {
        int iVar2 = iVar1 - param_5;
        if ((iVar2 > 0 || (int)iVar3 > 0xf8) && iVar2 < 0x10000 && (int)iVar3 < 0x10000)
        {
            ((MoppCodeWriter*)this->writer)->putByte((int)iVar3 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte((int)iVar3 >> 8 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte(iVar2 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte(iVar2 >> 8 & 0xff);
            ((MoppCodeWriter*)this->writer)->putByte(param_2);
            ((MoppCodeWriter*)this->writer)->putByte(param_3);
            ((MoppCodeWriter*)this->writer)->putByte(param_4 + 0x23);
            return;
        }
        if (param_3 - param_2 == 1)
        {
            if ((int)iVar3 > 0xfb)
            {
                FUN_0111d260(param_6);
                param_6 = *(int*)((char*)this->writer + 0xc);
            }
            FUN_0111d260(param_5);
            ((MoppCodeWriter*)this->writer)->putByte(*(int*)((char*)this->writer + 0xc) - param_6);
            ((MoppCodeWriter*)this->writer)->putByte(param_2);
            ((MoppCodeWriter*)this->writer)->putByte(param_4 + 0x20);
            return;
        }
    }

    if ((int)iVar3 > 0xfb)
    {
        FUN_0111d260(param_6);
        param_6 = *(int*)((char*)this->writer + 0xc);
    }
    FUN_0111d260(param_5);
    ((MoppCodeWriter*)this->writer)->putByte(*(int*)((char*)this->writer + 0xc) - param_6);
    ((MoppCodeWriter*)this->writer)->putByte(param_2);
    ((MoppCodeWriter*)this->writer)->putByte(param_3);
    ((MoppCodeWriter*)this->writer)->putByte(param_4 + 0x10);
}

// ---------------------------------------------------------------------------
// @ 0x0111db80
// ---------------------------------------------------------------------------
void MoppCompiler::FUN_0111db80(int param_2, int param_3, int* param_4, int* param_5)
{
    float* pfVar2 = *(float**)(param_2 + 0xb8);
    int iVar8 = 0;
    int iVar7 = 0;
    int local_40 = 0;

    if (pfVar2[0] != g_01485378 && (iVar7 = 1, pfVar2[0] < g_01485378))
        local_40 = 1;
    if (pfVar2[1] != g_01485378)
    {
        iVar7++;
        iVar8 = 1;
        if (pfVar2[1] < g_01485378) local_40++;
    }
    if (pfVar2[2] != g_01485378)
    {
        iVar7++;
        iVar8 = 2;
        if (pfVar2[2] < g_01485378) local_40++;
    }

    float fVar1 = *(float*)(param_2 + 0xc0);

    if (iVar7 == 1)
    {
        int iVar4 = FUN_0120ad30(FUN_0120ac90((*(float*)(param_2 + 0xbc) - this->origin[iVar8]) * this->sat));
        int iVar5 = FUN_0120ad30(FUN_0120ac90((fVar1 - this->origin[iVar8]) * this->sat));
        int base  = *(int*)(param_3 + 0x28 + iVar8 * 4);
        int sh    = *(uint32_t*)(param_3 + 0x24);
        int lo = (iVar4 - base) >> sh;
        int hi = ((iVar5 - base) >> sh) + 1;

        if (lo < 1) lo = 0; else if (lo > 0xfe) lo = 0xff;
        if (hi < 1) hi = 0; else if (hi > 0xfe) hi = 0xff;

        *param_5 = lo;
        *param_4 = hi;
        if (*param_5 < 0) *param_5 = 0;
        return;
    }

    // general path
    float invSat = 1.0f / this->sat;
    float d0 = (invSat * (float)*(int*)(param_3 + 0x28) + this->origin[0]) * pfVar2[0]
             + ((float)*(int*)(param_3 + 0x2c) * invSat + this->origin[1]) * pfVar2[1]
             + ((float)*(int*)(param_3 + 0x30) * invSat + this->origin[2]) * pfVar2[2];

    float invCells = 1.0f / (float)(1 << (*(uint32_t*)(param_3 + 0x24) & 0x1f));

    float fVar10 = 1.0f;
    float local_20 = 1.0f;
    if (iVar7 == 2) { fVar10 = 1.4142135f; local_20 = 0.5f; }
    else if (iVar7 == 3) { fVar10 = 1.7320508f; local_20 = 0.33333334f; }

    double local_30 = (double)(((*(float*)(param_2 + 0xbc) - d0) * this->sat) * invCells) * fVar10;
    double local_38 = (double)(((fVar1 - d0) * this->sat) * invCells) * fVar10;

    if (local_40 != 0)
    {
        local_30 = local_30 + (double)(local_40 * 0xff);
        local_38 = (double)(local_40 * 0xff) + local_38;
    }

    int iVar7b = FUN_0120ad30(FUN_0120ac90((float)(local_20 * local_30)));
    int hi = FUN_0120ad30(FUN_0120ac90((float)(local_20 * local_38)));
    hi++;

    if (iVar7b < 1) iVar7b = 0; else if (iVar7b > 0xfe) iVar7b = 0xff;

    if (hi < 1)
    {
        *param_5 = iVar7b;
        *param_4 = 0;
        return;
    }
    if (hi > 0xfe) hi = 0xff;

    *param_5 = iVar7b;
    *param_4 = hi;
}

// ---------------------------------------------------------------------------
// @ 0x0111d560
// ---------------------------------------------------------------------------
int MoppCompiler::FUN_0111d560(int param_2, int param_3, int* param_4)
{
    char* node = (char*)param_2;
    int   local_74 = param_4[2];
    float local_84 = 0.0f;
    int   local_80 = -1;
    float local_7c = 0.0f;
    float local_78 = 0.0f;
    int   iVar6;
    float fVar5;

    if (*(char*)(node + 4) == 0)
    {
        MoppCompiler* local_70 = this;
        if (*(char*)(node + 0x39) == 0 && *param_4 < this->maxDepth)
        {
            char local_85 = 0;
            char* pcVar3 = FUN_0111d410(&local_85, node, param_3, param_4);
            if (*pcVar3 != 0)
                *(char*)(node + 0x3c) = 1;
        }
        if (*(char*)(node + 0x3c) == 1)
        {
            char local_64[20];
            FUN_0111d450((void*)param_3, param_4, local_64);

            int local_68;
            int local_6c = *(int*)(node + 0xec);
            local_68 = *(int*)(node + 0xf0);
            local_80 = -1;
            local_7c = 0.0f;
            local_78 = 0.0f;
            local_84 = 0.0f;
            iVar6 = local_6c;
            int local_80v = -1;
            (void)local_80v;
            int savedMin = -1;

            do
            {
                int iVar1 = *(int*)(local_64 + (int)local_78 - 4);
                if (iVar1 != 0)
                {
                    int local_50[0x12];
                    int local_48;
                    for (int k = 0; k < 0x12; k++)
                        local_50[k] = param_4[k];
                    FUN_0111cdb0((void*)iVar1);
                    FUN_0111d2b0((void*)iVar1, (void*)((char*)local_70 + 0x30));
                    local_50[0] = *param_4 + 1;
                    FUN_0111d340(local_70, 0);
                    int r = this->FUN_0111d560(iVar1, (int)param_4, local_50);
                    iVar6 = local_6c;
                    local_80 = r;
                    if (local_48 <= (int)local_7c)
                        local_7c = (float)local_48;
                }
                local_78 = (float)((int)local_78 - 4);
            } while ((int)local_78 > -5);
            (void)savedMin;

            local_84 = 0.0f;
            float fA = (float)((int)local_7c + 2);
            fVar5 = fA;
            if (local_74 + 2 < (int)local_7c + 2)
                fVar5 = (float)(local_74 + 2);
        }
        else
        {
            fVar5 = (float)local_74;
        }
    }
    else
    {
        local_78 = this->minCell;
        float* local_70 = (float*)(node + 0x0c);
        float* local_7c = this->scan;
        iVar6 = 0;
        do
        {
            if (*(char*)(node + 0x39) == 0)
                *(char*)(iVar6 + 0x40 + param_2) = 1;
            local_84 = *local_7c;
            if (local_70[1] - *local_70 < local_84 && local_84 < local_78)
            {
                int iVar1 = FUN_0120ad30(this->sat * local_84);
                if (iVar1 * 0x80 < 1 << ((unsigned char)local_74 & 0x1f))
                {
                    if (*(char*)(node + 0x39) == 0)
                        *(char*)(iVar6 + 0x40 + param_2) = 2;
                }
                else
                {
                    local_78 = local_84;
                }
            }
            local_7c++;
            iVar6++;
            local_70 += 2;
        } while (iVar6 < 3);

        unsigned uVar2 = (unsigned)FUN_0120ad30((this->sat * 0.9f) * local_78);
        iVar6 = 0;
        if (uVar2 != 0)
        {
            do { uVar2 >>= 1; iVar6++; } while (uVar2 != 0);
        }
        fVar5 = (float)(iVar6 + 6);
        if (iVar6 + 6 <= local_74)
            return local_74;
    }
    return (int)fVar5;
}

// ---------------------------------------------------------------------------
// @ 0x0111df20
// ---------------------------------------------------------------------------
struct MoppBuilder
{
    void* FUN_0111df20(int* param_2, int param_3, int param_4);   // 0x0111df20
};

void* MoppBuilder::FUN_0111df20(int* param_2, int param_3, int param_4)
{
    char* p = (char*)this;
    *(uint16_t*)(p + 6) = 1;
    *(uint32_t*)p = 0x014a60e8u;
    *(uint32_t*)(p + 0x40) = 0x3f000000u;
    *(uint32_t*)(p + 0x48) = 0x3f800000u;
    *(uint32_t*)(p + 0x60) = 4;
    *(uint32_t*)(p + 0x44) = 0x3e4ccccdu;
    *(uint32_t*)(p + 0x50) = 0x3e4ccccdu;
    *(uint32_t*)(p + 0x54) = 0x3e4ccccdu;
    *(uint32_t*)(p + 0x58) = 0x3d4ccccdu;
    *(uint32_t*)(p + 0x5c) = 0;

    float* g = (float*)0x016e5ad0;
    (void)g;
    *(uint32_t*)0x016e5ad0 = 0x3f800000u;
    *(uint32_t*)0x016e5ad4 = 0;
    *(uint32_t*)0x016e5ad8 = 0;
    *(uint32_t*)0x016e5adc = 0;
    *(uint32_t*)0x016e5af0 = 0;
    *(uint32_t*)0x016e5af4 = 0x3f800000u;
    *(uint32_t*)0x016e5af8 = 0;
    *(uint32_t*)0x016e5afc = 0;
    *(uint32_t*)0x016e5b10 = 0;
    *(uint32_t*)0x016e5b14 = 0;
    *(uint32_t*)0x016e5b18 = 0x3f800000u;
    *(uint32_t*)0x016e5b1c = 0;
    *(uint32_t*)0x016e5ae0 = 0;
    *(uint32_t*)0x016e5b00 = 0;
    *(uint32_t*)0x016e5b20 = 0;
    *(uint32_t*)0x016e5b30 = 0;
    *(uint32_t*)0x016e5b34 = 0x3f800000u;
    *(uint32_t*)0x016e5b38 = 0x3f800000u;
    *(uint32_t*)0x016e5b3c = 0;
    *(uint32_t*)0x016e5b50 = 0x3f800000u;
    *(uint32_t*)0x016e5b54 = 0;
    *(uint32_t*)0x016e5b58 = 0x3f800000u;
    *(uint32_t*)0x016e5b5c = 0;
    *(uint32_t*)0x016e5b70 = 0x3f800000u;
    *(uint32_t*)0x016e5b74 = 0x3f800000u;
    *(uint32_t*)0x016e5b78 = 0;
    *(uint32_t*)0x016e5b7c = 0;
    *(uint32_t*)0x016e5b40 = 0x3e4ccccdu;
    *(uint32_t*)0x016e5b60 = 0x3e4ccccdu;
    *(uint32_t*)0x016e5b80 = 0x3e4ccccdu;
    *(uint32_t*)0x016e5b90 = 0;
    *(uint32_t*)0x016e5b94 = 0x3f800000u;
    *(uint32_t*)0x016e5b98 = 0xbf800000u;
    *(uint32_t*)0x016e5b9c = 0;
    *(uint32_t*)0x016e5bb0 = 0x3f800000u;
    *(uint32_t*)0x016e5bb4 = 0;
    *(uint32_t*)0x016e5bb8 = 0xbf800000u;
    *(uint32_t*)0x016e5bbc = 0;
    *(uint32_t*)0x016e5bd0 = 0x3f800000u;
    *(uint32_t*)0x016e5bd4 = 0xbf800000u;
    *(uint32_t*)0x016e5bd8 = 0;
    *(uint32_t*)0x016e5bdc = 0;
    *(uint32_t*)0x016e5ba0 = 0x3e800000u;
    *(uint32_t*)0x016e5bc0 = 0x3e800000u;
    *(uint32_t*)0x016e5be0 = 0x3e800000u;
    *(uint32_t*)0x016e5bf0 = 0x3f800000u;
    *(uint32_t*)0x016e5bf4 = 0x3f800000u;
    *(uint32_t*)0x016e5bf8 = 0x3f800000u;
    *(uint32_t*)0x016e5bfc = 0;
    *(uint32_t*)0x016e5c10 = 0x3f800000u;
    *(uint32_t*)0x016e5c14 = 0x3f800000u;
    *(uint32_t*)0x016e5c18 = 0xbf800000u;
    *(uint32_t*)0x016e5c1c = 0;
    *(uint32_t*)0x016e5c30 = 0x3f800000u;
    *(uint32_t*)0x016e5c34 = 0xbf800000u;
    *(uint32_t*)0x016e5c38 = 0xbf800000u;
    *(uint32_t*)0x016e5c3c = 0;
    *(uint32_t*)0x016e5c50 = 0x3f800000u;
    *(uint32_t*)0x016e5c54 = 0xbf800000u;
    *(uint32_t*)0x016e5c58 = 0xbf800000u;
    *(uint32_t*)0x016e5c5c = 0;
    *(uint32_t*)0x016e5c00 = 0x3e99999au;
    *(uint32_t*)0x016e5c20 = 0x3ea3d70au;
    *(uint32_t*)0x016e5c40 = 0x3ea3d70au;
    *(uint32_t*)0x016e5c60 = 0x3eae147bu;

    float fVar4 = 0.0f;
    float* pfVar2 = (float*)0x016e5ad8;
    float* pfVar3;
    do
    {
        float fVar1 = pfVar2[-1] * pfVar2[-1] + (pfVar2[-2] * pfVar2[-2] + *pfVar2 * *pfVar2);
        if (fVar1 == 0.0f) fVar1 = 0.0f;
        else fVar1 = 1.0f / FUN_0120ac90(fVar1);
        pfVar3 = pfVar2 + 8;
        pfVar2[-2] = fVar1 * pfVar2[-2];
        pfVar2[-1] = fVar1 * pfVar2[-1];
        *pfVar2 = fVar1 * *pfVar2;
        pfVar2[1] = fVar1 * pfVar2[1];
        pfVar2[3] = fVar4;
        fVar4 = (float)((int)fVar4 + 1);
        pfVar2 = pfVar3;
    } while ((int)pfVar3 < 0x16e5c78);

    *(int*)(p + 0x40) = param_2[0];
    *(int*)(p + 0x44) = param_2[1];
    *(int*)(p + 0x48) = param_2[2];
    *(int*)(p + 0x50) = param_2[4];
    *(int*)(p + 0x54) = param_2[5];
    *(int*)(p + 0x58) = param_2[6];
    *(int*)(p + 0x5c) = param_2[7];
    *(int*)(p + 0x60) = param_2[8];
    *(int*)(p + 0x08) = param_4;
    *(int*)(p + 0x10) = param_3;
    *(int*)(p + 0x0c) = 0;
    return p;
}
