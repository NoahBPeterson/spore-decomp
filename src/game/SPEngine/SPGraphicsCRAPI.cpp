// src/game/SPEngine/SPGraphicsCRAPI.cpp -- migrated from slice(s) s006e1db0, s006e0fd0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsCRAPI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __stdcall galloc(unsigned n);   // 0x0087d4a0 (equiv t2)
extern "C" void  __stdcall gfree(void* p);   // 0x0087d4c0 (equiv t2)
extern "C" void  zero_mem(void* dst, int val, unsigned n);   // misnamed operator_new in the decompile

// ---- items of slice s006e0fd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
typedef unsigned char byte;
extern "C" void* __stdcall galloc(unsigned n);   // 0x0087d4a0 (equiv t2)
extern "C" void  __stdcall gfree(void* p);   // 0x0087d4c0 (equiv t2)
extern "C" void  zero_mem(void* dst, int val, unsigned n);   // misnamed operator_new in the decompile
struct WuData {
    int* weights;   // +0x00
    int* wt;        // +0x04
    int* mr;        // +0x08
    int* mg;        // +0x0c
    int* mb;        // +0x10
    int  data;      // +0x14
    int  width;     // +0x18
    int  height;    // +0x1c
    int  stride;    // +0x20
    int* big;       // +0x24
};
struct WuContext {
    int tag;        // +0x00 = 'WUCR' 0x57554352
    int version;    // +0x04 = 4
    int field8;     // +0x08
    WuData* data;   // +0x0c
};
// ---- items of slice s006e0fd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* operator_new(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0

// ---- items of slice s006e1db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  FUN_006e1260(int a, int b, int c, int d, int e);
extern "C" int   FUN_006e1a30(int ctx, int* box, int* out);
extern "C" double FUN_006e1780(int ctx, int* box);
extern "C" void  FUN_006e1be0(int* box, unsigned char v, int array);
extern "C" int   FUN_006e1480(int* box, int array);
extern "C" extern int DAT_016100f0[];
extern "C" extern int DAT_016080f0[];
extern "C" extern int* DAT_01532fc4[];
extern "C" byte  CRAPI_getcolour(uint col, int a, byte* pal, int flag);
extern "C" void  CRAPI_diffuseerror(byte* src, byte* pal, int x, int y, int w, int h, int stride, int* map);
// ---- items of slice s006e1db0 end

// @ 0x006e1150
void Hist3d(WuData* self, int* wt, int* mr, int* mg, int* mb, float* weights)
{
    int sq[256];
    for (int i = 0; i < 0x100; ++i)
        sq[i] = i * i;
    int y = 0;
    if (0 < self->height) {
        do {
            byte* p = (byte*)(self->stride * y + self->data);
            for (int n = self->width; n != 0; --n) {
                uint b = p[2];
                uint g = p[1];
                uint r = p[0];
                int idx = (((int)b >> 2) * 0x41 + ((int)g >> 2)) * 0x41 + 0x10c3 + ((int)r >> 2);
                wt[idx] += 1;
                mr[idx] += (int)b;
                mg[idx] += (int)g;
                mb[idx] += (int)r;
                p += 4;
                weights[idx] = (float)(sq[r] + sq[g] + sq[b]) + weights[idx];
            }
            y = y + 1;
        } while (y < self->height);
    }
    (void)mb; (void)mr; (void)mg; (void)wt;
}

// @ 0x006e1260
void MomentPass(int param_1, int param_2, int param_3, int param_4, int param_5)
{
    int* local_568 = (int*)(param_3 + 0x430c);
    int* local_570 = (int*)(param_2 + 0x108);
    int outer = 0x40;
    do {
        float local_110[67];
        int local_530[66];
        int local_428[66];
        int local_320[66];
        int local_218[66];
        for (int i = 0; i < 0x41; ++i) local_110[i] = 0.0f;
        for (int i = 0; i < 0x41; ++i) local_530[i] = 0;
        for (int i = 0; i < 0x41; ++i) local_218[i] = 0;
        for (int i = 0; i < 0x41; ++i) local_428[i] = 0;
        for (int i = 0; i < 0x41; ++i) local_320[i] = 0;
        int mid = 0x40;
        int* piVar2 = local_568;
        int* piVar5 = local_570;
        do {
            int iVar4 = 0;
            int iVar9 = 0;
            int iVar7 = 0;
            int local_574 = 0;
            int local_56c = 0;
            float fVar11 = 0.0f;
            int inner = 0x40;
            int* piVar3 = piVar2;
            int* piVar6 = piVar5;
            do {
                iVar7 = iVar7 + *(int*)((int)piVar3 + (param_1 - param_3));
                local_56c = local_56c + piVar6[0x1081];
                local_574 = local_574 + *piVar3;
                iVar9 = iVar9 + *(int*)((int)piVar3 + (param_4 - param_3));
                int* dst = (int*)((int)local_320 + iVar4 + 4);
                *dst = *dst + iVar9;
                float fVar10 = *(float*)((int)piVar3 + (param_5 - param_3));
                dst = (int*)((int)local_218 + iVar4 + 4);
                *dst = *dst + local_56c;
                dst = (int*)((int)local_530 + iVar4 + 4);
                *dst = *dst + iVar7;
                dst = (int*)((int)local_428 + iVar4 + 4);
                *dst = *dst + local_574;
                fVar11 = fVar10 + fVar11;
                *(int*)((int)piVar3 + (param_1 - param_3)) =
                    *(int*)((param_1 - param_2) + (int)piVar6) + *(int*)((int)local_530 + iVar4 + 4);
                piVar6[0x1081] = *piVar6 + *(int*)((int)local_218 + iVar4 + 4);
                float fv = *(float*)((int)local_110 + iVar4 + 4);
                *piVar3 = *(int*)((param_3 - param_2) + (int)piVar6) + *(int*)((int)local_428 + iVar4 + 4);
                fv = fv + fVar11;
                *(int*)((int)piVar3 + (param_4 - param_3)) =
                    *(int*)((param_4 - param_2) + (int)piVar6) + *(int*)((int)local_320 + iVar4 + 4);
                *(float*)((int)piVar3 + (param_5 - param_3)) =
                    *(float*)((param_5 - param_2) + (int)piVar6) + fv;
                *(float*)((int)local_110 + iVar4 + 4) = fv;
                piVar3 = piVar3 + 1;
                piVar6 = piVar6 + 1;
                iVar4 = iVar4 + 4;
                inner = inner - 1;
            } while (inner != 0);
            piVar2 = piVar2 + 0x41;
            piVar5 = piVar5 + 0x41;
            mid = mid - 1;
        } while (mid != 0);
        local_570 = local_570 + 0x1081;
        local_568 = local_568 + 0x1081;
        outer = outer - 1;
    } while (outer != 0);
}

// @ 0x006e1480
int BoxMoments(int* box, int array)
{
    int iVar2 = box[5];
    int iVar1 = box[4];
    int iVar3 = (box[3] + box[1] * 0x41) * 0x41;
    int iVar4 = (box[1] * 0x41 + box[2]) * 0x41;
    int iVar5 = (*box * 0x41 + box[3]) * 0x41;
    int iVar6 = (*box * 0x41 + box[2]) * 0x41;
    return ((((*(int*)(array + (iVar1 + iVar5) * 4) - *(int*)(array + (iVar6 + iVar1) * 4)) -
              *(int*)(array + (iVar5 + iVar2) * 4)) - *(int*)(array + (iVar4 + iVar2) * 4)) -
             *(int*)(array + (iVar1 + iVar3) * 4)) + *(int*)(array + (iVar6 + iVar2) * 4) +
           *(int*)(array + (iVar4 + iVar1) * 4) + *(int*)(array + (iVar2 + iVar3) * 4);
}

// @ 0x006e1520
int PlaneMoments(int* box, char axis, int array)
{
    if (axis == '\0') {
        int iVar1 = box[4];
        return ((*(int*)(array + ((box[2] + box[1] * 0x41) * 0x41 + iVar1) * 4) -
                 *(int*)(array + ((box[1] * 0x41 + box[3]) * 0x41 + iVar1) * 4)) -
                *(int*)(array + ((box[2] + *box * 0x41) * 0x41 + iVar1) * 4)) +
               *(int*)(array + ((*box * 0x41 + box[3]) * 0x41 + iVar1) * 4);
    }
    if (axis != '\x01') {
        if (axis != '\x02')
            return 0;
        int iVar1 = (box[3] + *box * 0x41) * 0x41;
        int iVar2 = (box[2] + *box * 0x41) * 0x41;
        return ((*(int*)(array + (iVar2 + box[5]) * 4) -
                 *(int*)(array + (iVar2 + box[4]) * 4)) -
                *(int*)(array + (box[5] + iVar1) * 4)) +
               *(int*)(array + (box[4] + iVar1) * 4);
    }
    int iVar1 = (box[1] * 0x41 + box[2]) * 0x41;
    int iVar2 = (*box * 0x41 + box[2]) * 0x41;
    return ((*(int*)(array + (iVar2 + box[5]) * 4) -
             *(int*)(array + (iVar2 + box[4]) * 4)) -
            *(int*)(array + (box[5] + iVar1) * 4)) +
           *(int*)(array + (box[4] + iVar1) * 4);
}

// @ 0x006e1650
int PlaneMoments2(int* box, char axis, int coord, int array)
{
    if (axis == '\0') {
        return ((*(int*)(array + ((box[3] + box[1] * 0x41) * 0x41 + coord) * 4) -
                 *(int*)(array + ((box[3] + *box * 0x41) * 0x41 + coord) * 4)) -
                *(int*)(array + ((box[1] * 0x41 + box[2]) * 0x41 + coord) * 4)) +
               *(int*)(array + ((box[2] + *box * 0x41) * 0x41 + coord) * 4);
    }
    if (axis != '\x01') {
        if (axis != '\x02')
            return 0;
        int iVar1 = (box[3] + coord * 0x41) * 0x41;
        int iVar2 = (box[2] + coord * 0x41) * 0x41;
        return ((*(int*)(array + (iVar2 + box[4]) * 4) -
                 *(int*)(array + (iVar2 + box[5]) * 4)) -
                *(int*)(array + (box[4] + iVar1) * 4)) +
               *(int*)(array + (box[5] + iVar1) * 4);
    }
    int iVar1 = (box[1] * 0x41 + coord) * 0x41;
    int iVar2 = (*box * 0x41 + coord) * 0x41;
    return ((*(int*)(array + (iVar2 + box[4]) * 4) -
             *(int*)(array + (iVar2 + box[5]) * 4)) -
            *(int*)(array + (box[4] + iVar1) * 4)) +
           *(int*)(array + (box[5] + iVar1) * 4);
}

// @ 0x006e1780
double BoxVariance(int ctx, int box)
{
    int w8 = BoxMoments((int*)box, *(int*)(ctx + 8));
    int wc = BoxMoments((int*)box, *(int*)(ctx + 0xc));
    int w10 = BoxMoments((int*)box, *(int*)(ctx + 0x10));
    int w4 = BoxMoments((int*)box, *(int*)(ctx + 4));
    if (w4 == 0)
        return 0.0;
    return (double)w8 - (double)wc / (double)w4;
    (void)w10;
}

// @ 0x006e1880
double MaximizeVariance(int ctx, int box, int axis, int lo, int hi, int* cut, int w8, int wc, int w10, int w4)
{
    int b8 = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 8));
    int bc = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 0xc));
    int b10 = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 0x10));
    int b4 = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 4));
    volatile float best = 0.0f;
    *cut = -1;
    for (; lo < hi; lo = lo + 1) {
        int a8 = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 8));
        int ac = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 0xc));
        int a10 = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 0x10));
        int a4 = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 4));
        a4 = a4 + b4;
        if (a4 != 0) {
            if (w4 - a4 != 0) {
                float var = ((float)(a8 + b8) * (float)(a8 + b8)
                           + (float)(ac + bc) * (float)(ac + bc)
                           + (float)(a10 + b10) * (float)(a10 + b10)) / (float)a4
                          + ((float)(w8 - (a8 + b8)) * (float)(w8 - (a8 + b8))
                           + (float)(wc - (ac + bc)) * (float)(wc - (ac + bc))
                           + (float)(w10 - (a10 + b10)) * (float)(w10 - (a10 + b10)))
                          / (float)(w4 - a4);
                if (best < var) {
                    *cut = lo;
                    best = var;
                }
            }
        }
    }
    return (double)best;
}

// @ 0x006e1a30
int CutBox(int param_1, int* box, int* out)
{
    int* p = box;
    int w0 = BoxMoments(p, *(int*)(param_1 + 8));
    int w1 = BoxMoments(p, *(int*)(param_1 + 0xc));
    int w2 = BoxMoments(p, *(int*)(param_1 + 0x10));
    int w3 = BoxMoments(p, *(int*)(param_1 + 4));
    int local_10, local_4, cutMax;
    float s0 = (float)MaximizeVariance(param_1, (int)p, 2, *p + 1, p[1], &local_10, w0, w1, w2, w3);
    float s1 = (float)MaximizeVariance(param_1, (int)p, 1, p[2] + 1, p[3], &local_4, w0, w1, w2, w3);
    float s2 = (float)MaximizeVariance(param_1, (int)p, 0, p[4] + 1, p[5], &cutMax, w0, w1, w2, w3);
    int which;
    if (s1 < s0 || s2 < s0) {
        if (s1 < s0 && s1 < s2)
            which = 0;
        else
            which = 1;
    } else {
        which = 2;
        if (local_10 < 0)
            return 0;
    }
    out[1] = p[1];
    out[3] = p[3];
    out[5] = p[5];
    if (which == 0) {
        p[5] = cutMax; out[4] = cutMax;
        out[0] = *p; out[2] = p[2];
    } else if (which == 1) {
        p[3] = local_4; out[2] = local_4;
        out[0] = *p; out[4] = p[4];
    } else if (which == 2) {
        p[1] = local_10; out[0] = local_10;
        out[2] = p[2]; out[4] = p[4];
    }
    p[6] = (p[1] - *p) * (p[5] - p[4]) * (p[3] - p[2]);
    out[6] = (out[3] - out[2]) * (out[5] - out[4]) * (out[1] - *out);
    return 1;
}

// @ 0x006e1be0
void FillRegion(int* box, unsigned char value, int array)
{
    int i = *box;
    if (i < box[1]) {
        int row = i << 6;
        do {
            int y = box[2];
            if (y < box[3]) {
                int zend = box[5];
                do {
                    int z = box[4];
                    if (z < zend) {
                        do {
                            *(unsigned char*)((y + row) * 0x40 + 0x10 + array + z) = value;
                            zend = box[5];
                            z = z + 1;
                        } while (z < zend);
                    }
                    y = y + 1;
                } while (y < box[3]);
            }
            i = i + 1;
            row = row + 0x40;
        } while (i < box[1]);
    }
}

// @ 0x006e1c50
WuData* AllocWuData()
{
    WuData* p = (WuData*)galloc(0x28);
    if (p != 0) {
        p->weights = 0; p->wt = 0; p->mr = 0; p->mg = 0; p->mb = 0;
        p->data = 0; p->width = 0; p->height = 0; p->stride = 0; p->big = 0;
        int big = (int)galloc(0x430c10);
        p->big = (int*)big;
        int w = (int)galloc(0x10c304);
        void* dst = p->big;
        p->weights = (int*)w;
        if (dst != 0) {
            if (w != 0) {
                zero_mem(dst, 0, 0x430c10);
                zero_mem(p->weights, 0, 0x10c304);
                int base = (int)p->big;
                p->wt = (int*)base;
                p->mr = (int*)(base + 0x10c304);
                p->mg = (int*)(base + 0x218608);
                p->mb = (int*)(base + 0x32490c);
                return p;
            }
            if (dst != 0)
                gfree(dst);
        }
        if (p->weights != 0)
            gfree(p->weights);
        gfree(p);
    }
    return 0;
}

// @ 0x006e1d10
WuContext* WU_open()
{
    WuContext* p = (WuContext*)galloc(0x10);
    if (p != 0) {
        WuData* d = AllocWuData();
        if (d != 0) {
            p->field8 = 0;
            p->data = d;
            p->tag = 0x57554352;
            p->version = 4;
            return p;
        }
        gfree(p);
    }
    return 0;
}

// @ 0x006e1d50
int WU_read(int ctx, int desc, int pixels, int stride)
{
    WuData* d = *(WuData**)(ctx + 0xc);
    if (*(int*)(desc + 0x18) != 0x20)
        return 0;
    d->width = *(int*)(desc + 0x10);
    d->height = *(int*)(desc + 0x14);
    d->stride = stride;
    d->data = pixels;
    Hist3d(d, d->wt, d->mr, d->mg, d->mb, (float*)d->weights);
    return 1;
}

// @ 0x006e1db0
void* WU_close(int ctx, int nColors, int* outPal, int* outCount)
{
    int* data = *(int**)(ctx + 0xc);
    int* boxes = (int*)galloc(nColors * 0x1c);
    float* scores = (float*)galloc(nColors * 4);
    FUN_006e1260(data[1], data[2], data[3], data[4], data[0]);
    int i = 0;
    int local_c = nColors;
    int count = 1;
    boxes[4] = 0;
    boxes[2] = 0;
    boxes[0] = 0;
    boxes[1] = 0x40;
    boxes[3] = 0x40;
    boxes[5] = 0x40;
    int iVar5 = local_c;
    int* local_18 = 0;
    int* puVar1 = 0;
    float fVar12 = 0.0f;
    if (1 < nColors) {
        float fVar13 = 0.0f;
        int* puVar6 = boxes;
        do {
            local_18 = puVar6 + 7;
            puVar1 = boxes + i * 7;
            int r = FUN_006e1a30((int)data, puVar1, local_18);
            if (r == 0) {
                count = count - 1;
                scores[i] = fVar13;
                local_18 = puVar6;
            } else {
                float fVar12 = fVar13;
                if (1 < puVar1[6])
                    fVar13 = (float)FUN_006e1780((int)data, puVar1);
                scores[i] = fVar13;
                if (puVar6[0xd] < 2) {
                    scores[count] = fVar12;
                    fVar13 = fVar12;
                } else {
                    scores[count] = (float)FUN_006e1780((int)data, local_18);
                    fVar13 = fVar12;
                }
            }
            fVar12 = scores[0];
            i = 0;
            iVar5 = 1;
            if (3 < count) {
                float* p = scores + 3;
                do {
                    if (fVar12 < p[-2]) { i = iVar5; fVar12 = p[-2]; }
                    if (fVar12 < p[-1]) { i = iVar5 + 1; fVar12 = p[-1]; }
                    if (fVar12 < *p)   { i = iVar5 + 2; fVar12 = *p; }
                    if (fVar12 < p[1])  { i = iVar5 + 3; fVar12 = p[1]; }
                    iVar5 = iVar5 + 4;
                    p = p + 4;
                } while (iVar5 <= count - 3);
            }
            for (; iVar5 <= count; iVar5 = iVar5 + 1) {
                if (fVar12 < scores[iVar5]) { i = iVar5; fVar12 = scores[iVar5]; }
            }
            count = count + 1;
            iVar5 = count;
        } while ((fVar13 < fVar12) && (iVar5 = local_c, puVar6 = local_18, count < nColors));
    }
    local_c = iVar5;
    gfree((void*)*data);
    unsigned total = nColors * 4 + 4;
    *data = 0;
    void* dst = (void*)galloc(total);
    if (outPal != 0) {
        int* pal = (int*)galloc(0x40010);
        *outPal = (int)pal;
        pal[0] = 0x494e5657;
        pal[1] = 0x40010;
        ((byte*)pal)[8] = 0;
        ((byte*)pal)[9] = 6;
        ((byte*)pal)[10] = 6;
        ((byte*)pal)[11] = 6;
    }
    if (dst != 0) {
        zero_mem(dst, 0, total);
        if (outPal != 0 && *outPal != 0)
            zero_mem((void*)(*outPal + 0x10), 0, 0x40000);
        int idx = 0;
        if (0 < local_c) {
            byte* out = (byte*)((int)dst + 2);
            int* box = boxes;
            do {
                if (outPal != 0 && *outPal != 0)
                    FUN_006e1be0(box, (byte)idx, *outPal);
                int w = FUN_006e1480(box, data[1]);
                if (w != 0) {
                    out[1] = 0xff;
                    int r = FUN_006e1480(box, data[2]);
                    *out = (char)(r / w);
                    int g = FUN_006e1480(box, data[3]);
                    out[-1] = (char)(g / w);
                    int b = FUN_006e1480(box, data[4]);
                    out[-2] = (char)(b / w);
                }
                idx = idx + 1;
                box = box + 7;
                out = out + 4;
            } while (idx < local_c);
        }
    }
    gfree(boxes);
    if (scores != 0)
        gfree(scores);
    if (data[9] != 0)
        gfree((void*)data[9]);
    if (*data != 0)
        gfree((void*)*data);
    gfree(data);
    gfree((void*)ctx);
    if (outCount != 0)
        *outCount = local_c;
    return dst;
}

// @ 0x006e20f0
void CRAPI_diffuseerror(byte* src, byte* pal, int x, int y, int w, int h, int stride, int* map)
{
    byte* p = src;
    byte* pb = src + 2;
    int d0 = (uint)*src - (uint)*pal;
    int d1 = (uint)src[1] - (uint)pal[1];
    int d2 = (uint)*pb - (uint)pal[2];
    if (0x40 < d2) d2 = 0x40;
    if (0x40 < d1) d1 = 0x40;
    if (0x40 < d0) d0 = 0x40;
    int iVar1 = map[1];
    int iVar2 = map[2];
    int iVar3 = map[0];
    int iVar4 = map[3];
    int* mapv = map + 4;
    int row = 0;
    if (0 < iVar1) {
        p = p + iVar2 * 4 + 1;
        do {
            if (h <= y + row)
                return;
            int col = x + iVar2;
            byte* pp = p;
            int n = iVar3;
            if (0 < iVar3) {
                do {
                    int e = *mapv;
                    mapv = mapv + 1;
                    if (e != 0 && -1 < col && col < w) {
                        int half = iVar4 / 2;
                        uint v;
                        if (d2 < 0) { v = (uint)pp[1] + (e * d2 - half) / iVar4; v = ((int)v < 0) - 1 & v; }
                        else        { v = (e * d2 + half) / iVar4 + (uint)pp[1]; if (0xff < (int)v) v = 0xff; }
                        pp[1] = (byte)v;
                        if (d1 < 0) { v = (uint)*pp + (e * d1 - half) / iVar4; v = ((int)v < 0) - 1 & v; }
                        else        { v = (e * d1 + half) / iVar4 + (uint)*pp; if (0xff < (int)v) v = 0xff; }
                        *pp = (byte)v;
                        if (d0 < 0) { v = (uint)pp[-1] + (e * d0 - half) / iVar4; v = ((int)v < 0) - 1 & v; }
                        else        { v = (e * d0 + half) / iVar4 + (uint)pp[-1]; if (0xff < (int)v) v = 0xff; }
                        pp[-1] = (byte)v;
                    }
                    n = n - 1;
                    col = col + 1;
                    pp = pp + 4;
                } while (n != 0);
            }
            p = p + stride;
            row = row + 1;
        } while (row < iVar1);
    }
}

// @ 0x006e22d0
byte CRAPI_getcolour(uint color, int n, byte* pal, uint hint)
{
    int local_1000[512];
    int local_800[512];
    uint best = 1000000;
    byte bVar1 = (byte)(color >> 0x18);
    uint uVar8;
    byte local_1013;
    uint uVar2;
    if ((hint & 1) == 0) {
        uVar8 = color >> 0x10;
        local_1013 = (byte)(color >> 8);
        uVar2 = color;
    } else {
        int k = (color >> 0x19) + 0x80;
        uVar8 = ((color >> 0x10 & 0xff) * k + 0x80) / 0xff;
        local_1013 = (byte)(((color >> 8 & 0xff) * k + 0x80) / 0xff);
        uVar2 = ((color & 0xff) * k + 0x80) / 0xff;
    }
    int v = -0x100;
    int* pi = local_800;
    int c = 0x200;
    do {
        *pi = v * v;
        v = v + 1;
        pi = pi + 1;
        c = c - 1;
    } while (c != 0);
    pi = local_1000;
    v = -0x100;
    do {
        int t = (v + 0x100 < 0x100) ? v * v : v * v * 10;
        *pi = t;
        int next = v + 0x101;
        pi = pi + 1;
        v = v + 1;
        (void)next;
    } while (v + 0x100 < 0x200);
    // (the original loop bound is v+0x101 < 0x200; reproduced below)
    zero_mem(&DAT_016100f0, -1, 0x8000);
    zero_mem(&DAT_016080f0, -1, 0x8000);
    uint uVar5 = ((color >> 8 & 0xff) * 0x21 + (color >> 0x10 & 0xff)) * 0x21 +
                 (color & 0xff) * 0xc61 + 0xf85 + (color >> 0x18) & 0x1fff;
    if ((*(uint*)(&DAT_016080f0[uVar5]) != color) || (DAT_016100f0[uVar5] < 0)) {
        byte* local_100c = pal;
        signed char sVar11;
        if ((hint & 1) == 0) sVar11 = 0;
        else if (bVar1 == 0) sVar11 = 4;
        else if ((bVar1 < 0x11) || ((0x6f < bVar1 && bVar1 < 0x91) || (0xef < bVar1))) sVar11 = 2;
        else sVar11 = 1;
        int local_1010 = 0;
        byte* pbVar10 = pal;
        if (0 < n) {
            byte* pbVar7 = pal + 1;
            do {
                pbVar10 = pbVar7 - 1;
                uint uVar3;
                if (n < 3) {
                    uVar3 = (local_1000[((uint)bVar1 - (uint)pbVar7[2]) + 0x100] << sVar11) +
                            local_1000[((uVar8 & 0xff) - (uint)pbVar7[1]) + 0x100] +
                            local_1000[((uVar2 & 0xff) - (uint)*pbVar10) + 0x100] +
                            local_1000[((uint)local_1013 - (uint)*pbVar7) + 0x100];
                } else {
                    uVar3 = (local_800[((uint)bVar1 - (uint)pbVar7[2]) + 0x100] << sVar11) +
                            local_800[((uVar8 & 0xff) - (uint)pbVar7[1]) + 0x100] +
                            local_800[((uVar2 & 0xff) - (uint)*pbVar10) + 0x100] +
                            local_800[((uint)local_1013 - (uint)*pbVar7) + 0x100];
                }
                if (uVar3 < best) {
                    local_100c = pbVar10;
                    best = uVar3;
                    if (uVar3 == 0) break;
                }
                local_1010 = local_1010 + 1;
                pbVar7 = pbVar7 + 4;
                pbVar10 = local_100c;
            } while (local_1010 < n);
        }
        *(uint*)(&DAT_016080f0[uVar5]) = color;
        DAT_016100f0[uVar5] = (int)pbVar10 - (int)pal >> 2;
    }
    return 0;
}

// @ 0x006e25f0
void CRAPI_remap(byte* dst, int ctx, int dstStride, byte* src, int srcStride, int wide, uint mode, int diffuse, uint count, uint rows)
{
    int iVar2 = mode;
    bool bVar1 = 0 < *(int*)(ctx + 0x438);
    int table = (int)galloc(0x400);
    if (bVar1) {
        byte* pb = (byte*)(ctx + 0x2b);
        byte* out = (byte*)(table + 2);
        int k = 0x40;
        do {
            out[1] = *pb;
            *out = (char)(((( *pb >> 1) + 0x80) * (uint)pb[-1] + 0x80) / 0xff);
            out[-1] = (char)(((( *pb >> 1) + 0x80) * (uint)pb[-2] + 0x80) / 0xff);
            out[-2] = (char)(((( *pb >> 1) + 0x80) * (uint)pb[-3] + 0x80) / 0xff);
            out[5] = pb[4];
            out[4] = (char)((((pb[4] >> 1) + 0x80) * (uint)pb[3] + 0x80) / 0xff);
            out[3] = (char)((((pb[4] >> 1) + 0x80) * (uint)pb[2] + 0x80) / 0xff);
            out[2] = (char)((((pb[4] >> 1) + 0x80) * (uint)pb[1] + 0x80) / 0xff);
            out[9] = pb[8];
            out[8] = (char)((((pb[8] >> 1) + 0x80) * (uint)pb[7] + 0x80) / 0xff);
            out[7] = (char)((((pb[8] >> 1) + 0x80) * (uint)pb[6] + 0x80) / 0xff);
            out[6] = (char)((((pb[8] >> 1) + 0x80) * (uint)pb[5] + 0x80) / 0xff);
            out[0xd] = pb[0xc];
            out[0xc] = (char)((((pb[0xc] >> 1) + 0x80) * (uint)pb[0xb] + 0x80) / 0xff);
            out[0xb] = (char)((((pb[0xc] >> 1) + 0x80) * (uint)pb[10] + 0x80) / 0xff);
            out[10] = (char)((((pb[0xc] >> 1) + 0x80) * (uint)pb[9] + 0x80) / 0xff);
            out = out + 0x10;
            pb = pb + 0x10;
            k = k - 1;
        } while (k != 0);
    } else {
        byte* out = (byte*)(table + 2);
        byte* in = (byte*)(ctx + 0x2a);
        int k = 0x100;
        do {
            out[1] = in[1];
            *out = *in;
            out[-1] = in[-1];
            out[-2] = in[-2];
            in = in + 4;
            out = out + 4;
            k = k - 1;
        } while (k != 0);
    }
    if (mode == 0)
        zero_mem(&DAT_016100f0, -1, 0x8000);
    if (diffuse < 0 || 3 < diffuse)
        diffuse = 1;
    uint row = 0;
    if (rows != 0) {
        do {
            if (wide < 9) {
                if (count != 0) {
                    uint cnt = count;
                    byte* p = src;
                    do {
                        byte col;
                        if (iVar2 == 0) {
                            col = CRAPI_getcolour(*(uint*)(ctx + 0x28 + (uint)*p * 4),
                                                         *(int*)(ctx + 0x24), (byte*)table, bVar1);
                        } else {
                            col = *(byte*)((uint)(p[2] >> (8U - *(char*)(iVar2 + 9) & 0x1f)) *
                                           (1 << (*(byte*)(iVar2 + 9) & 0x1f)) *
                                           (1 << (*(byte*)(iVar2 + 9) & 0x1f)) + 0x10 +
                                           (uint)(p[1] >> (8 - *(byte*)(iVar2 + 10) & 0x1f)) *
                                           (1 << (*(byte*)(iVar2 + 10) & 0x1f)) + iVar2 +
                                           (uint)(*p >> (8U - *(char*)(iVar2 + 0xb) & 0x1f)));
                        }
                        p[(int)dst - (int)src] = col;
                        p = p + 1;
                        cnt = cnt - 1;
                    } while (cnt != 0);
                }
            } else {
                uint col2 = 0;
                byte* p = dst;
                byte* q = src;
                if (count != 0) {
                    do {
                        byte col;
                        if (iVar2 == 0) {
                            col = CRAPI_getcolour(*(uint*)q, *(int*)(ctx + 0x24), (byte*)table, bVar1);
                        } else {
                            if (0xf9 < q[3]) {
                                col = *(byte*)((uint)(q[2] >> (8U - *(char*)(iVar2 + 9) & 0x1f)) *
                                               (1 << (*(byte*)(iVar2 + 9) & 0x1f)) *
                                               (1 << (*(byte*)(iVar2 + 9) & 0x1f)) + 0x10 +
                                               (uint)(q[1] >> (8 - *(byte*)(iVar2 + 10) & 0x1f)) *
                                               (1 << (*(byte*)(iVar2 + 10) & 0x1f)) + iVar2 +
                                               (uint)(*q >> (8U - *(char*)(iVar2 + 0xb) & 0x1f)));
                            } else {
                                col = 0xff;
                            }
                        }
                        *p = col;
                        if (diffuse != 0)
                            CRAPI_diffuseerror(q, (byte*)(ctx + 0x28 + (uint)*p * 4), col2, row, count,
                                               rows, srcStride, (int*)DAT_01532fc4[diffuse]);
                        col2 = col2 + 1;
                        p = p + 1;
                        q = q + 4;
                    } while (col2 < count);
                }
            }
            dst = dst + dstStride;
            src = src + srcStride;
            row = row + 1;
        } while (row < rows);
    }
    if (table != 0)
        gfree((void*)table);
}
