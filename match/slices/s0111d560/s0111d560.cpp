// Mopp (Multiresolution Oriented Point Pair) compiler helpers (slice s0111d560).
// Built with VS2008 SP1 (cl 15.00.30729.01) at /arch:SSE /fp:fast.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <math.h>

// ---------------------------------------------------------------------------
// Extern helpers (addresses from the original image)
// ---------------------------------------------------------------------------
extern float __cdecl FUN_0120ac90(float x);                                  // 0x0120ac90  hkFloor
extern int   __cdecl FUN_0120ad30(float x);                                  // 0x0120ad30  hkFloatToInt

struct MoppCodeWriter
{
    char pad00[0x0c];
    int  cursor;                                  // +0x0c
    void putByte(int b);                          // 0x0111eb70
};

struct MoppNode;

// MOPP cell/frame work record (the 0x48-byte "local_50" copy, 0x12 dwords).
struct MoppCell
{
    int           depth;       // +0x00
    unsigned char flag;        // +0x04
    char          pad05[3];
    int           level;       // +0x08
    struct Span { int lo, hi; };
    Span          span[3];     // +0x0c   per-axis [lo,hi]
    int           cellShift;   // +0x24
    int           cellBase[3]; // +0x28
    int           field34;     // +0x34
    int           field38;     // +0x38
    int           field3c;     // +0x3c
    int           field40;     // +0x40
    int           lo[3];       // +0x44
    int           out[3];      // +0x50

    void FUN_0111cdb0(MoppNode* child);                     // 0x0111cdb0
    void FUN_0111d2b0(MoppNode* child, float* origin);      // 0x0111d2b0
    void FUN_0111d340();                                    // 0x0111d340
};

// One MOPP tree node.
struct MoppNode
{
    char  pad00[4];
    char  flag04;         // +0x04   leaf flag
    char  pad05[0x0c - 0x05];
    float span[3][2];     // +0x0c..+0x20   per-axis [lo,hi]
    char  pad24[0x39 - 0x24];
    char  flag39;         // +0x39
    char  pad3a[2];
    char  flag3c;         // +0x3c   fully subdivided flag
    char  pad3d[3];
    char  cells[3];       // +0x40..+0x42
    char  pad43[0xb8 - 0x43];
    float* normal;        // +0xb8
    float  planeMin;      // +0xbc
    float  planeMax;      // +0xc0
    char  padc4[0xec - 0xc4];
    MoppNode* childEC;    // +0xec
    MoppNode* childF0;    // +0xf0
};

// The MOPP compiler (ECX in the original).
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
    char FUN_0111d410(char* out, MoppNode* node, MoppCell* build, MoppCell* in);  // 0x0111d410
    void FUN_0111d450(MoppCell* build, MoppCell* in, char* out);                  // 0x0111d450
    void FUN_0111d7f0(MoppCell* src, MoppCell* above);                            // 0x0111d7f0
    void FUN_0111d8e0(int p2, int p3, int p4, int p5, int p6);                    // 0x0111d8e0
    void FUN_0111db80(MoppNode* node, MoppCell* build, int* outHi, int* outLo);   // 0x0111db80
    int  FUN_0111d560(MoppNode* node, MoppCell* build, MoppCell* in);             // 0x0111d560
};

// One entry of the static 13-orientation table at 0x016e5ad0.
struct MoppBasis
{
    float v[3];      // +0x00
    float w;         // +0x0c
    float u;         // +0x10
    int   index;     // +0x14
    int   pad18[2];
};
extern MoppBasis g_moppBasis[13];   // 0x016e5ad0

struct MoppBuilder
{
    void*          vtable;      // +0x00
    char           pad04[2];
    unsigned short flags;       // +0x06
    int            field08;     // +0x08
    int            field0c;     // +0x0c
    int            field10;     // +0x10
    char           pad14[0x40 - 0x14];
    float          f40;         // +0x40
    float          f44;         // +0x44
    float          f48;         // +0x48
    char           pad4c[4];
    float          f50;         // +0x50
    float          f54;         // +0x54
    float          f58;         // +0x58
    float          f5c;         // +0x5c
    int            i60;         // +0x60

    void* FUN_0111df20(float* params, int a, int b);   // 0x0111df20
};

extern float g_01488874;   // 0x1488874   0.1f
extern float g_013eb964;   // 0x13eb964  -0.1f
extern float g_01485378;   // 0x1485378   0.0f
extern float g_01487180;   // 0x1447180 254.0f
extern float g_0142ea5c;   // 0x142ea5c 65536.0f

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
void MoppCompiler::FUN_0111d7f0(MoppCell* src, MoppCell* above)
{
    float* scan = this->scan;
    int*   out  = src->out;
    int    i;

    for (i = 0; i < 3; i++)
    {
        float limit = (float)(1 << (above->cellShift & 0x1f)) / this->sat;
        if (limit <= this->minCell)
            limit = this->minCell;

        float v = scan[i];
        if (src->span[i].hi - src->span[i].lo < v && v <= limit)
            limit = v;

        int n = FUN_0120ad30(this->sat * limit);
        out[i]     = above->span[i].hi + 1 + n;
        out[i - 3] = above->span[i].lo - n;
    }
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
void MoppCompiler::FUN_0111db80(MoppNode* node, MoppCell* build, int* outHi, int* outLo)
{
    float* normal = node->normal;

    int axis = 0;                 // last non-zero axis (ebx)
    int count = 0;                // iVar7
    int neg = 0;                  // local_40

    if (normal[0] != 0.0f) { count = 1; axis = 0; if (normal[0] < 0.0f) neg = 1; }
    if (normal[1] != 0.0f) { count++;  axis = 1; if (normal[1] < 0.0f) neg++; }
    if (normal[2] != 0.0f) { count++;  axis = 2; if (normal[2] < 0.0f) neg++; }

    float hi = node->planeMax;    // +0xc0
    float lo = node->planeMin;    // +0xbc

    if (count == 1)
    {
        int a = FUN_0120ad30(FUN_0120ac90((lo - this->origin[axis]) * this->sat));
        int b = FUN_0120ad30(FUN_0120ac90((hi - this->origin[axis]) * this->sat));
        int base = build->cellBase[axis];
        int sh   = build->cellShift;

        int m = (a - base) >> sh;         // edi  (from planeMin)
        int n = ((b - base) >> sh) + 1;   // eax  (from planeMax)

        if (m < 1) m = 0; else if (m > 0xfe) m = 0xff;
        if (n < 1) n = 0; else if (n > 0xfe) n = 0xff;

        *outLo = m;
        *outHi = n;
        if (*outLo < 0) *outLo = 0;
        return;
    }

    float invSat = 1.0f / this->sat;
    float plane =
          (build->cellBase[0] * invSat + this->origin[0]) * normal[0]
        + (build->cellBase[1] * invSat + this->origin[1]) * normal[1]
        + (build->cellBase[2] * invSat + this->origin[2]) * normal[2];

    float invCells = 1.0f / (float)(1 << (build->cellShift & 0x1f));

    float mul = 1.0f;         // diagonal scale (sqrt(count))
    float recip = 1.0f;       // 1.0, 1/sqrt(2), 1/sqrt(3)
    if (count == 2)      { mul = 1.4142135f; recip = 0.5f; }
    else if (count == 3) { mul = 1.7320508f; recip = 0.33333334f; }

    float a = ((lo - plane) * this->sat) * invCells * mul;
    float b = ((hi - plane) * this->sat) * invCells * mul;

    if (neg != 0)
    {
        float off = (float)(neg * 0xff);
        a += off;
        b += off;
    }

    int low  = FUN_0120ad30(FUN_0120ac90(recip * a));
    int high = FUN_0120ad30(FUN_0120ac90(recip * b)) + 1;

    if (low < 1) low = 0; else if (low > 0xfe) low = 0xff;

    if (high < 1)
    {
        *outLo = low;
        *outHi = 0;
        return;
    }
    if (high > 0xfe) high = 0xff;

    *outLo = low;
    *outHi = high;
}

// ---------------------------------------------------------------------------
// @ 0x0111d560
int MoppCompiler::FUN_0111d560(MoppNode* node, MoppCell* build, MoppCell* in)
{
    int limit0 = in->level;                 // frame value at +0x08

    if (node->flag04 == 0)
    {
        // ----- interior node -----
        if (node->flag39 == 0 && in->depth < this->maxDepth)
        {
            char probe = 0;
            this->FUN_0111d410(&probe, node, build, in);
            if (probe != 0)
                node->flag3c = 1;
        }

        char childInfo[20];
        if (node->flag3c == 1)
            this->FUN_0111d450(build, in, childInfo);

        int bestEC = -1;
        int bestF0 = -1;
        int limit  = 0x7fffffff;

        // Iteration order matches the original: childF0 first, then childEC.
        MoppNode* order[2];
        order[0] = node->childF0;
        order[1] = node->childEC;

        for (int i = 0; i < 2; i++)
        {
            MoppNode* c = order[i];
            if (c == 0)
                continue;

            MoppCell sub;
            memcpy(&sub, in, 0x48);
            sub.FUN_0111cdb0(c);
            sub.FUN_0111d2b0(c, this->origin);
            sub.depth = in->depth + 1;
            sub.flag  = 0;
            sub.FUN_0111d340();

            int r = this->FUN_0111d560(c, build, &sub);
            if (i == 0) bestF0 = r; else bestEC = r;
            if (sub.level <= limit)
                limit = sub.level;
        }

        int value = (int)((unsigned)limit + 2u);
        int alt   = limit0 + 2;
        if (alt < value)
            value = alt;

        if (node->childEC != 0)
        {
            MoppNode* c = node->childEC;
            int threshold = (node->flag39 == 0) ? limit0 : value;
            if ((node->flag39 == 0 || c->flag39 == 0) && bestEC < threshold)
                c->flag3c = 1;
            if (c->flag3c == 0 && bestEC <= value)
                value = bestEC;
        }
        if (node->childF0 != 0)
        {
            MoppNode* c = node->childF0;
            int threshold = (node->flag39 == 0) ? limit0 : value;
            if ((node->flag39 == 0 || c->flag39 == 0) && bestF0 < threshold)
                c->flag3c = 1;
            if (c->flag3c == 0 && bestF0 <= value)
                value = bestF0;
        }
        return value;
    }

    // ----- leaf node -----
    float  limit = this->minCell;
    float* span  = &node->span[0][0];

    for (int i = 0; i < 3; i++)
    {
        if (node->flag39 == 0)
            node->cells[i] = 1;

        float v = this->scan[i];
        if (span[1] - span[0] < v && v < limit)
        {
            int q = FUN_0120ad30(this->sat * v);
            if (q * 0x80 < (1 << (limit0 & 0x1f)))
            {
                if (node->flag39 == 0)
                    node->cells[i] = 2;
            }
            else
            {
                limit = v;
            }
        }
        span += 2;
    }

    unsigned u = (unsigned)FUN_0120ad30((this->sat * 0.9f) * limit);
    int bits = 0;
    if (u != 0)
    {
        do { u >>= 1; bits++; } while (u != 0);
    }
    if (bits + 6 <= limit0)
        return limit0;
    return bits + 6;
}

// @ 0x0111df20
void* MoppBuilder::FUN_0111df20(float* params, int param_3, int param_4)
{
    this->flags  = 1;
    this->vtable = (void*)0x014a60e8u;
    this->f40 = 0.5f;
    this->f48 = 1.0f;
    this->i60 = 4;
    this->f44 = 0.2f;
    this->f50 = 0.2f;
    this->f54 = 0.2f;
    this->f58 = 0.05f;
    this->f5c = 0.0f;

    g_moppBasis[0].v[0] = 1.0f;
    g_moppBasis[0].v[1] = 0.0f;
    g_moppBasis[0].v[2] = 0.0f;
    g_moppBasis[0].w    = 0.0f;
    g_moppBasis[1].v[0] = 0.0f;
    g_moppBasis[1].v[1] = 1.0f;
    g_moppBasis[1].v[2] = 0.0f;
    g_moppBasis[1].w    = 0.0f;
    g_moppBasis[2].v[0] = 0.0f;
    g_moppBasis[2].v[1] = 0.0f;
    g_moppBasis[2].v[2] = 1.0f;
    g_moppBasis[2].w    = 0.0f;
    g_moppBasis[0].u    = 0.0f;
    g_moppBasis[1].u    = 0.0f;
    g_moppBasis[2].u    = 0.0f;
    g_moppBasis[3].v[0] = 0.0f;
    g_moppBasis[3].v[1] = 1.0f;
    g_moppBasis[3].v[2] = 1.0f;
    g_moppBasis[3].w    = 0.0f;
    g_moppBasis[4].v[0] = 1.0f;
    g_moppBasis[4].v[1] = 0.0f;
    g_moppBasis[4].v[2] = 1.0f;
    g_moppBasis[4].w    = 0.0f;
    g_moppBasis[5].v[0] = 1.0f;
    g_moppBasis[5].v[1] = 1.0f;
    g_moppBasis[5].v[2] = 0.0f;
    g_moppBasis[5].w    = 0.0f;
    g_moppBasis[3].u    = 0.2f;
    g_moppBasis[4].u    = 0.2f;
    g_moppBasis[5].u    = 0.2f;
    g_moppBasis[6].v[0] = 0.0f;
    g_moppBasis[6].v[1] = 1.0f;
    g_moppBasis[6].v[2] = -1.0f;
    g_moppBasis[6].w    = 0.0f;
    g_moppBasis[7].v[0] = 1.0f;
    g_moppBasis[7].v[1] = 0.0f;
    g_moppBasis[7].v[2] = -1.0f;
    g_moppBasis[7].w    = 0.0f;
    g_moppBasis[8].v[0] = 1.0f;
    g_moppBasis[8].v[1] = -1.0f;
    g_moppBasis[8].v[2] = 0.0f;
    g_moppBasis[8].w    = 0.0f;
    g_moppBasis[6].u    = 0.25f;
    g_moppBasis[7].u    = 0.25f;
    g_moppBasis[8].u    = 0.25f;
    g_moppBasis[9].v[0] = 1.0f;
    g_moppBasis[9].v[1] = 1.0f;
    g_moppBasis[9].v[2] = 1.0f;
    g_moppBasis[9].w    = 0.0f;
    g_moppBasis[10].v[0] = 1.0f;
    g_moppBasis[10].v[1] = 1.0f;
    g_moppBasis[10].v[2] = -1.0f;
    g_moppBasis[10].w    = 0.0f;
    g_moppBasis[11].v[0] = 1.0f;
    g_moppBasis[11].v[1] = -1.0f;
    g_moppBasis[11].v[2] = -1.0f;
    g_moppBasis[11].w    = 0.0f;
    g_moppBasis[12].v[0] = 1.0f;
    g_moppBasis[12].v[1] = -1.0f;
    g_moppBasis[12].v[2] = -1.0f;
    g_moppBasis[12].w    = 0.0f;
    g_moppBasis[9].u     = 0.3f;
    g_moppBasis[10].u    = 0.32f;
    g_moppBasis[11].u    = 0.32f;
    g_moppBasis[12].u    = 0.34f;

    for (int i = 0; i < 13; i++)
    {
        MoppBasis* e = &g_moppBasis[i];
        float dot = e->v[1] * e->v[1] + (e->v[0] * e->v[0] + e->v[2] * e->v[2]);
        float scale;
        if (dot == 0.0f)
            scale = 0.0f;
        else
            scale = 1.0f / sqrtf(dot);

        e->v[0] *= scale;
        e->v[1] *= scale;
        e->v[2] *= scale;
        e->w    *= scale;
        e->index = i;
    }

    this->f40 = params[0];
    this->f44 = params[1];
    this->f48 = params[2];
    this->f50 = params[4];
    this->f54 = params[5];
    this->f58 = params[6];
    this->f5c = params[7];
    this->i60 = *(int*)&params[8];
    this->field08 = param_4;
    this->field10 = param_3;
    this->field0c = 0;
    return this;
}
