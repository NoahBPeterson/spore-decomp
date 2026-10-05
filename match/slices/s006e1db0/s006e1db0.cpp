// slice s006e1db0: Wu quantiser close/remap/dither and a 16-dword copy helper.
//  006e1db0  WU_close
//  006e20f0  CRAPI_diffuseerror
//  006e22d0  CRAPI_getcolour (with its 1024-entry distance tables)
//  006e25f0  CRAPI_remap
//  006e2ae0  16-dword (4x4) block copy
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;
typedef unsigned char byte;

// externals used across the Wu module (masked)
extern "C" {
void* __stdcall galloc(unsigned n);
void  __stdcall gfree(void* p);
void  zero_mem(void* dst, int val, unsigned n);
void  fill_mem(void* dst, int val, unsigned n);
void  FUN_006e1260(int a, int b, int c, int d, int e);
int   FUN_006e1a30(int ctx, int* box, int* out);
double FUN_006e1780(int ctx, int* box);
void  FUN_006e1be0(int* box, unsigned char v, int array);
int   FUN_006e1480(int* box, int array);
byte  CRAPI_getcolour(uint col, int a, byte* pal, int flag);
void  CRAPI_diffuseerror(byte* src, byte* pal, int x, int y, int w, int h, int stride, int* map);
}

extern "C" {
extern int DAT_016100f0[];
extern int DAT_016080f0[];
extern int* DAT_01532fc4[];
}

// ---------------------------------------------------------------------------
// @ 0x006e1db0  WU_close
// ---------------------------------------------------------------------------
void* WU_close(int ctx, int nColors, int* outPal, int* outCount) {
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

// ---------------------------------------------------------------------------
// @ 0x006e20f0  CRAPI_diffuseerror
// ---------------------------------------------------------------------------
void CRAPI_diffuseerror(byte* src, byte* pal, int x, int y, int w, int h, int stride, int* map) {
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

// ---------------------------------------------------------------------------
// @ 0x006e22d0  CRAPI_getcolour
// ---------------------------------------------------------------------------
byte CRAPI_getcolour(uint color, int n, byte* pal, uint hint) {
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

// ---------------------------------------------------------------------------
// @ 0x006e25f0  CRAPI_remap
// ---------------------------------------------------------------------------
void CRAPI_remap(byte* dst, int ctx, int dstStride, byte* src, int srcStride, int wide,
                 uint mode, int diffuse, uint count, uint rows) {
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

// ---------------------------------------------------------------------------
// @ 0x006e2ae0  16-dword (4x4) block copy
// ---------------------------------------------------------------------------
struct Block16 {
    int v[16];
    Block16& Set(const int* a, const int* b, const int* c, const int* d);
};

Block16& Block16::Set(const int* a, const int* b, const int* c, const int* d) {
    v[0] = a[0]; v[1] = a[1]; v[2] = a[2]; v[3] = a[3];
    v[4] = b[0]; v[5] = b[1]; v[6] = b[2]; v[7] = b[3];
    v[8] = c[0]; v[9] = c[1]; v[10] = c[2]; v[11] = c[3];
    v[12] = d[0]; v[13] = d[1]; v[14] = d[2]; v[15] = d[3];
    return *this;
}
