// slice s006e0030: SP chart/rect-pack rendering helpers.
//  006e0030  compute chart vertical min/max span tables
//  006e04d0  rect-pack charts (weighted area, retry loop, UV transform)
//  006e09d0  SP::RectPackCharts (compute scaled areas, pack, snap UVs)
//  006e0e00  Elem16 vector resize
//  006e0ea0  fill a chart's vertex array from the model
//  006e0f90  visit all chart lists and call a virtual
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;
typedef unsigned short ushort;

// 8-byte vertex/UV element
struct Vertex2 { float x, y; };

// ---------------------------------------------------------------------------
// SP chart object (layout from the 0x34-stride cClusterRect and the chart
// helpers; only the fields these functions touch are named)
// ---------------------------------------------------------------------------
struct Cluster {
    int       mIndex;        // +0x00
    int       m04;           // +0x04
    float     m08;           // +0x08
    int       mBegin;        // +0x0c
    int       mEnd;          // +0x10
    Vertex2*  mVertBegin;    // +0x14
    Vertex2*  mVertEnd;      // +0x18
    int       m1c;           // +0x1c
    int       m20;           // +0x20
    int       m24;           // +0x24
    float     m28;           // +0x28
    float     m2c;           // +0x2c
    char      mFlag30;       // +0x30
    char      pad31[4];      // +0x31
    int*      mArr34;        // +0x34
    int*      mArrEnd38;     // +0x38
    int       m3c;           // +0x3c
    int       m40;           // +0x40
    int       m44;           // +0x44
    int*      mArr48;        // +0x48
    int*      mArrEnd4c;     // +0x4c
    int       m50;           // +0x50
    int       m54;           // +0x54
    int       m58;           // +0x58
    int       mMax5c;        // +0x5c
    float     m60;           // +0x60
    float     m64;           // +0x64
};

// SP::cClusterRect as used by RectPackCharts (0x34 bytes)
namespace SP {
struct cClusterRect {
    uint  mStartIndices;   // +0x00
    uint  mEndIndices;     // +0x04
    float mArea;           // +0x08
    uint  mMeshIndex;      // +0x0c
    float mMinU;           // +0x10
    float mMinV;           // +0x14
    float mMaxU;           // +0x18
    float mMaxV;           // +0x1c
    float mTexU;           // +0x20
    float mTexV;           // +0x24
    float mAreaWeight;     // +0x28
    float mArea2;          // +0x2c
    float mLinearScale;    // +0x30
};
}

struct cRectAreaSort {
    bool operator()(const SP::cClusterRect& a, const SP::cClusterRect& b) const {
        return *(const uint*)&a.mArea > *(const uint*)&b.mArea;
    }
};

// ---------------------------------------------------------------------------
// Globals / externals (masked)
// ---------------------------------------------------------------------------
extern int   DAT_01532b94;      // grid resolution
extern float DAT_01532da4;
extern float _DAT_01532da0;
extern int   DAT_0170a6b4;

extern "C" {
void  FUN_004746c0(int n, void* p);
void  FUN_004cea40(void* dst, uint n, void* value);
void  FUN_0041ebe0(int* p);
void  FUN_007b00d0();
void  FUN_007b0fa0(int a, int b);
int   FUN_007b1e70(int a, int b);
int   FUN_0071ddc0(int a, int b, int c, int d, int e);
void  FUN_006dec60(int obj, float f);
char  FUN_006de710(int obj);
char  FUN_006de5e0(int obj);
void  FUN_006e0030(Cluster* c);
void  FUN_006dfa00();
void  FUN_006dfa80(void* a, void* b, int c);
void  FUN_006dfd90(void* self, int position, int n, void* value);
void  FUN_006dfca0(void* self, int position, int end);
void  VecBoolDoInsertValue(void* a, void* b, int c);
void  ThreadSleep(void* p);
void  operator_delete__(void* p);
void  QuickSortCRExtern(void* first, void* last, int cmp);
}

// ---------------------------------------------------------------------------
// @ 0x006e0030
// ---------------------------------------------------------------------------
int ChartBuildSpans(Cluster* self) {
    float f = (float)DAT_01532b94 * self->m28;
    int local_98 = (int)(f + 0.5f);
    if (f < (float)local_98)
        local_98 = local_98 - 1;
    float local_90 = (float)DAT_01532b94 * self->m2c;

    int* end4c = self->mArrEnd4c;
    int* begin48 = self->mArr48;
    VecBoolDoInsertValue(begin48, end4c, 0);
    self->mArrEnd4c = (int*)((int)self->mArrEnd4c + (((int)end4c - (int)begin48) >> 2) * -4);
    int* end38 = self->mArrEnd38;
    int* begin34 = self->mArr34;
    VecBoolDoInsertValue(begin34, end38, 0);
    self->mArrEnd38 = (int*)((int)self->mArrEnd38 + (((int)end38 - (int)begin34) >> 2) * -4);

    int n = local_98 + 1;
    FUN_004746c0(n, &DAT_01532b94);
    int zero = 0;
    FUN_004746c0(n, &zero);

    int i = 0;
    self->mMax5c = 0;
    int count = (int)(self->mVertEnd - self->mVertBegin);
    if (0 < count) {
        do {
            Vertex2* v = self->mVertBegin;
            float a = v[i].x;
            float c = v[i].y;
            i = i + 1;
            float b = v[i % count].x;
            float d = v[i % count].y;
            float lo = b, hi = a, loY = d, hiY = c;
            if (b <= a) {
                lo = a; a = b; loY = c; c = d;
                (void)lo; (void)loY;
            }
            // (the swap above mirrors the decompile's register shuffling)
            float mn = a, mx = b;
            float mnY = c, mxY = d;
            if (b <= a) {
                mn = b; mx = a; mnY = d; mxY = c;
            }
            int i0 = (int)((float)DAT_01532b94 * mn + 0.5f);
            if ((float)DAT_01532b94 * mn < (float)i0)
                i0 = i0 - 1;
            int i1 = (int)((float)DAT_01532b94 * mx + 0.5f);
            if ((float)DAT_01532b94 * mx < (float)i1)
                i1 = i1 - 1;
            if (i0 < 0)
                i0 = 0;
            if (local_98 <= i1)
                i1 = local_98;

            if (0.0001f <= (mx - mn < 0 ? mn - mx : mx - mn)) {
                float slope = (mxY - mnY) / (mx - mn);
                float base = (mnY - mn * slope) * (float)DAT_01532b94;
                for (int k = i0; k <= i1; ++k) {
                    float y0 = (k == i0) ? (float)DAT_01532b94 * mnY
                                         : (float)k * slope + base;
                    float y1 = (k == i1) ? (float)DAT_01532b94 * mxY
                                         : (float)(k + 1) * slope + base;
                    int lo2, hi2;
                    if (mxY <= mnY) {
                        hi2 = (int)(y1 + 0.5f);
                        if (y1 < (float)hi2) hi2 -= 1;
                        lo2 = (int)(y0 + 0.5f);
                        if ((float)lo2 < y0) lo2 += 1;
                    } else {
                        hi2 = (int)(y0 + 0.5f);
                        if (y0 < (float)hi2) hi2 -= 1;
                        lo2 = (int)(y1 + 0.5f);
                        if ((float)lo2 < y1) lo2 += 1;
                    }
                    if (*(int*)((char*)self->mArr34 + k * 4) < hi2)
                        *(int*)((char*)self->mArr34 + k * 4) = hi2;
                    if (lo2 < *(int*)((char*)self->mArr48 + k * 4))
                        *(int*)((char*)self->mArr48 + k * 4) = lo2;
                }
            } else {
                for (; i0 <= i1; ++i0) {
                    int lo2, hi2;
                    if (mxY <= mnY) {
                        float t = (float)DAT_01532b94 * mxY;
                        hi2 = (int)(t + 0.5f);
                        if (t < (float)hi2) hi2 -= 1;
                        float u = (float)DAT_01532b94 * mnY;
                        lo2 = (int)(u + 0.5f);
                        if ((float)lo2 < u) lo2 += 1;
                    } else {
                        float t = (float)DAT_01532b94 * mnY;
                        hi2 = (int)(t + 0.5f);
                        if (t < (float)hi2) hi2 -= 1;
                        float u = (float)DAT_01532b94 * mxY;
                        lo2 = (int)(u + 0.5f);
                        if ((float)lo2 < u) lo2 += 1;
                    }
                    if (*(int*)((char*)self->mArr34 + i0 * 4) < hi2)
                        *(int*)((char*)self->mArr34 + i0 * 4) = hi2;
                    if (lo2 < *(int*)((char*)self->mArr48 + i0 * 4))
                        *(int*)((char*)self->mArr48 + i0 * 4) = lo2;
                }
            }
        } while (i < count);
    }

    i = 0;
    int n2 = (int)(self->mArrEnd38 - self->mArr34);
    if (0 < n2) {
        do {
            int v = *(int*)((char*)self->mArr34 + i * 4);
            if (self->mMax5c < v)
                self->mMax5c = v;
            if (*(int*)((char*)self->mArr48 + i * 4) == DAT_01532b94)
                *(int*)((char*)self->mArr48 + i * 4) = 0;
            i = i + 1;
        } while (i < n2);
    }
    (void)local_90;
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x006e04d0
// ---------------------------------------------------------------------------
int RectPackCharts(int* self, int flag) {
    float fVar12 = 0.0f, fVar13 = 0.0f, fVar15 = 0.0f;
    float fVar14 = 1.0f / *(float*)((char*)self + 0x230);
    int n = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
    int step = 0;
    if (1 < n) {
        int* p = *(int**)((char*)self + 0x234);
        int m = ((n - 2) >> 1) + 1;
        step = m * 2;
        do {
            int a = p[0];
            int b = p[1];
            fVar12 = ((*(float*)(a + 8) * fVar14) * *(float*)(a + 0x2c)) * *(float*)(a + 0x28) + fVar12;
            p += 2;
            m = m - 1;
            fVar13 = ((*(float*)(b + 8) * fVar14) * *(float*)(b + 0x2c)) * *(float*)(b + 0x28) + fVar13;
        } while (m != 0);
    }
    if (step < n) {
        int o = *(int*)(*(int*)((char*)self + 0x234) + step * 4);
        fVar15 = ((*(float*)(o + 8) * fVar14) * *(float*)(o + 0x2c)) * *(float*)(o + 0x28);
    }
    n = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
    int k = 0;
    fVar12 = DAT_01532da4 / ((fVar12 + fVar13) + fVar15);
    if (0 < n) {
        do {
            int o = *(int*)(*(int*)((char*)self + 0x234) + k * 4);
            FUN_006dec60(o, (*(float*)(o + 8) * fVar14) * fVar12);
            k = k + 1;
        } while (k < n);
    }

    uint local_c = 0;
    if (flag == 0)
        FUN_006dfa00();
    else
        FUN_006dfa80(*(void**)((char*)self + 0x234), *(void**)((char*)self + 0x238), (int)local_c);

    local_c = 0;
    int local_8 = 0;
    char local_d = 1;
    do {
        void* end = *(void**)((char*)self + 0x260);
        void* beg = *(void**)((char*)self + 0x25c);
        VecBoolDoInsertValue(beg, end, 0);
        *(int*)((char*)self + 0x260) =
            *(int*)((char*)self + 0x260) + (((int)end - (int)beg) >> 2) * -4;
        void* e2 = *(void**)((char*)self + 0x260);
        int b2 = *(int*)((char*)self + 0x25c);
        uint have = ((int)e2 - b2) >> 2;
        if (have < (uint)DAT_01532b94) {
            FUN_004cea40(e2, DAT_01532b94 - have, &local_8);
        } else {
            void* pos = (void*)(b2 + DAT_01532b94 * 4);
            VecBoolDoInsertValue(pos, e2, 0);
            *(int*)((char*)self + 0x260) =
                *(int*)((char*)self + 0x260) + (((int)e2 - (int)pos) >> 2) * -4;
        }
        int i = 0;
        int cnt = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
        uint lim = (uint)DAT_01532b94;
        int local_4 = cnt;
        if (0 < cnt) {
            do {
                int o = *(int*)(*(int*)((char*)self + 0x234) + i * 4);
                if ((*(char*)(o + 0x30) == '\0') && (i < (int)(lim * lim))) {
                    FUN_006e0030((Cluster*)o);
                    char cv = (flag == 0) ? FUN_006de710(o) : FUN_006de5e0(o);
                    local_d = (cv == '\0');
                    cnt = local_4;
                    lim = (uint)DAT_01532b94;
                    if (local_d)
                        break;
                }
                i = i + 1;
            } while (i < cnt);
        }
        int sleepArg = 0;
        local_4 = 0;
        ThreadSleep(&sleepArg);
        local_c = local_c + 1;
        if (local_d == '\0')
            break;
        int i2 = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
        if (0 < i2) {
            int j = 0;
            do {
                FUN_006dec60(*(int*)(*(int*)((char*)self + 0x234) + j * 4), _DAT_01532da0);
                j = j + 1;
            } while (j < i2);
        }
    } while ((int)local_c < 0x20);

    int ncl = (*(int*)((char*)self + 0x238) - *(int*)((char*)self + 0x234)) >> 2;
    uint c2 = 0;
    if (0 < ncl) {
        do {
            int* cl = *(int**)(*(int*)((char*)self + 0x234) + c2 * 4);
            if (((char)cl[0xc] == '\0') && ((int)c2 < (int)(DAT_01532b94 * DAT_01532b94))) {
                float inv = 1.0f / (float)(int)DAT_01532b94;
                float du = (float)cl[0x18] * inv;
                float dv = (float)cl[0x19] * inv;
                float su = 1.0f, sv = 1.0f;
                if ((float)cl[10] < inv) su = inv / (float)cl[10];
                if ((float)cl[0xb] < inv) sv = inv / (float)cl[0xb];
                int v = cl[3];
                int model = *cl * 0x10 + *(int*)((char*)self + 0x18);
                if (v < cl[4]) {
                    do {
                        char* base = (char*)((uint)*(ushort*)(model + 10) * v + *(int*)(model + 4));
                        float* p = (float*)base;
                        p[1] = sv * p[1];
                        *p = *p * su;
                        p = (float*)((uint)*(ushort*)(model + 10) * v + *(int*)(model + 4));
                        *p = *p + du;
                        p[1] = dv + p[1];
                        int off = (uint)*(ushort*)(model + 10) * v;
                        *(uint*)(off + 4 + *(int*)(model + 4)) =
                            *(uint*)(off + 4 + *(int*)(model + 4)) ^ 0x80000000;
                        p = (float*)((uint)*(ushort*)(model + 10) * v + *(int*)(model + 4));
                        v = v + 1;
                        *p = 1.0f - *p;
                    } while (v < cl[4]);
                }
                int u = 0;
                int uvN = (cl[6] - cl[5]) >> 3;
                if (3 < uvN) {
                    do {
                        int o = u * 8;
                        float* q = (float*)(cl[5] + o);
                        *q = du + *q; q[1] = dv + q[1];
                        q = (float*)(cl[5] + 8 + o);
                        *q = du + *q; q[1] = dv + q[1];
                        q = (float*)(o + 0x10 + cl[5]);
                        *q = du + *q; q[1] = dv + q[1];
                        q = (float*)(cl[5] + o + 0x18);
                        *q = du + *q;
                        u = u + 4;
                        q[1] = dv + q[1];
                    } while (u < uvN - 3);
                }
                for (; u < uvN; u = u + 1) {
                    float* q = (float*)(cl[5] + u * 8);
                    *q = du + *q;
                    q[1] = dv + q[1];
                }
            } else {
                int v = cl[3];
                int model = *cl * 0x10 + *(int*)((char*)self + 0x18);
                if (v < cl[4]) {
                    do {
                        *(int*)((uint)*(ushort*)(model + 10) * v + 4 + *(int*)(model + 4)) = 0;
                        int off = (uint)*(ushort*)(model + 10) * v;
                        v = v + 1;
                        *(int*)(off + *(int*)(model + 4)) = 0;
                    } while (v < cl[4]);
                }
            }
            c2 = c2 + 1;
        } while ((int)c2 < ncl);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x006e09d0  SP::RectPackCharts
// ---------------------------------------------------------------------------
void SP_RectPackCharts(int* param_1, int* param_2, float param_3, int param_4) {
    uint local_74 = 0;
    int local_48 = 0;
    int local_34 = 0;
    FUN_007b00d0();
    float fVar17 = (float)param_4;
    FUN_007b0fa0(param_4, param_4);

    int first = *param_2;
    param_3 = 1.0f / param_3;
    float fVar18 = 0.0f, fVar20 = 0.0f, fVar19 = 0.0f;
    uint local_70 = (param_2[1] - first) / 0x34;
    uint uVar13 = 0;
    int local_7c = 0;
    bool bVar6 = false;
    if (1 < (int)local_70) {
        int m = ((int)(local_70 - 2) >> 1) + 1;
        char* p = (char*)(first + 0x58);
        uVar13 = m * 2;
        do {
            fVar19 = ((*(float*)(p - 0x50) * param_3) * *(float*)(p - 0x38)) * *(float*)(p - 0x34) + fVar19;
            float* pf1 = (float*)(p - 0x1c);
            float* pf2 = (float*)(p - 4);
            float f16 = *(float*)p;
            p += 0x68;
            m = m - 1;
            fVar20 = ((*pf1 * param_3) * *pf2) * f16 + fVar20;
        } while (m != 0);
    }
    if (uVar13 < local_70) {
        int o = (int)(uVar13 * 0x34) + first;
        fVar18 = ((*(float*)((int)(uVar13 * 0x34) + 8 + first) * param_3) *
                  *(float*)(o + 0x24)) * *(float*)(o + 0x20);
    }
    if (3 < (int)local_70) {
        int off = 0;
        uint m = (((int)local_70 - 4) >> 2) + 1;
        local_74 = m * 4;
        do {
            *(float*)(*param_2 + off + 0x28) = *(float*)(*param_2 + 8 + off) * param_3;
            *(float*)(*param_2 + off + 0x5c) = *(float*)(*param_2 + 0x3c + off) * param_3;
            int o = off + 0x9c;
            *(float*)(off + *param_2 + 0x90) = *(float*)(off + 0x70 + *param_2) * param_3;
            off = off + 0xd0;
            m = m - 1;
            *(float*)(*param_2 + o + 0x28) = *(float*)(*param_2 + 8 + o) * param_3;
        } while (m != 0);
    }
    if (local_74 < local_70) {
        uint off = local_74 * 0x34;
        uint m = local_70 - local_74;
        do {
            int o = *param_2 + off;
            off = off + 0x34;
            m = m - 1;
            *(float*)(o + 0x28) = *(float*)(o + 8) * param_3;
        } while (m != 0);
    }

    local_74 &= 0xffffff00;
    QuickSortCRExtern((void*)*param_2, (void*)param_2[1], (int)local_74);

    do {
        float f16 = (float)local_7c;
    retry:
        if (0.9f <= f16 * 0.01f)
            goto done;
        local_7c = local_7c + 1;
        local_74 = 0;
        if (local_70 != 0) {
            uint off = 0;
            do {
                int o = *param_2 + off;
                float sc = *(float*)(o + 0x28) *
                           ((0.9f - f16 * 0.01f) / ((fVar19 + fVar20) + fVar18));
                *(float*)(o + 0x30) = sc;
                int r = FUN_007b1e70(
                    (int)(((*(float*)(o + 0x18) - *(float*)(o + 0x10)) * sc) * fVar17 + 0.5f),
                    (int)(((*(float*)(o + 0x1c) - *(float*)(o + 0x14)) * fVar17) * sc + 0.5f));
                *(int*)(o + 0x2c) = r;
                if (r < 0) {
                    bVar6 = false;
                    goto retry;
                }
                if (local_74 == local_70 - 1)
                    bVar6 = true;
                off = off + 0x34;
                local_74 = local_74 + 1;
            } while (local_74 < local_70);
        }
    } while (!bVar6);

    if (local_70 != 0) {
        uint off = 0;
        do {
            uint* pu = (uint*)(*param_2 + off);
            int* pi = (int*)(pu[0xb] * 0x20 + local_48);
            int i12 = *pi;
            int i11 = pi[1];
            int i9 = FUN_0071ddc0(*(int*)(*param_1 + pu[3] * 4), 8, 1, 2, 0xe);
            int i7 = *(int*)(*(int*)(*param_1 + pu[3] * 4) + 8);
            i9 = i9 * 0x20;
            int* pi8 = *(int**)(i7 + 0x1c + i9);
            int i4 = *(int*)(i7 + 0x14 + i9);
            ushort u3 = *(ushort*)(i7 + i9 + 0x1a);
            if (pi8 != 0)
                (**(void(***)())pi8)();
            uint u13 = *pu;
            if (u13 < pu[1]) {
                uint u14 = u3;
                float* pf = (float*)(u14 * u13 + i4);
                do {
                    float w = (float)pu[0xc];
                    *pf = 1.0f - (w * *pf + (float)i12 * (1.0f / fVar17));
                    pf[1] = -(w * pf[1] + (float)i11 * (1.0f / fVar17));
                    u13 = u13 + 1;
                    pf = (float*)((int)pf + u14);
                } while (u13 < pu[1]);
            }
            if (pi8 != 0)
                (*(void(**)(int))((int*)pi8)[1])(0);
            off = off + 0x34;
            local_70 = local_70 - 1;
        } while (local_70 != 0);
    }

done:
    if (local_34 != 0 && *(int*)(local_34 - 4) != 0)
        operator_delete__((void*)local_34);
    if (local_48 != 0 && *(int*)(local_48 - 4) != 0)
        operator_delete__((void*)local_48);
}

// ---------------------------------------------------------------------------
// @ 0x006e0e00  Elem16 vector resize
// ---------------------------------------------------------------------------
struct Elem16 {
    uint32_t f0; uint32_t f4; uint16_t f8; uint16_t fa; void* ref;
};

void Elem16VecResize(int* self, uint n) {
    int begin = *self;
    if ((uint)(self[1] - begin >> 4) < n) {
        Elem16 proto;
        proto.f0 = 0; proto.f4 = 0; proto.f8 = 8; proto.fa = 8; proto.ref = 0;
        FUN_006dfd90(self, self[1], n - (self[1] - begin >> 4), (void*)&proto);
        return;
    }
    FUN_006dfca0(self, (int)(n * 0x10 + begin), self[1]);
}

// ---------------------------------------------------------------------------
// @ 0x006e0ea0
// ---------------------------------------------------------------------------
void FillVertices(int* self, int* list) {
    *(char*)self = 1;
    *(int*)((char*)self + 0x230) = 0;
    FUN_0041ebe0(list);
    Elem16VecResize(list, (list[1] - *list) >> 2);
    int i = 0;
    int n = list[1] - *list >> 2;
    if (0 < n) {
        int off = 0;
        do {
            int r = FUN_0071ddc0(*(int*)(*list + i * 4), 8, 1, 2, 0xe);
            if (-1 < r) {
                int model = *(int*)(*(int*)(*list + i * 4) + 8);
                int* dst = (int*)(*(int*)((char*)self + 0x18) + off);
                int src = model + 0x10 + r * 0x20;
                dst[0] = *(int*)(model + 0x10 + r * 0x20);
                dst[1] = *(int*)(src + 4);
                *(uint16_t*)(dst + 2) = *(uint16_t*)(src + 8);
                *(uint16_t*)((char*)dst + 10) = *(uint16_t*)(src + 10);
                void* oldRef = (void*)dst[3];
                void* newRef = *(void**)(src + 0xc);
                if (newRef != oldRef) {
                    if (newRef)
                        (*(void(**)(void*))newRef)(newRef);
                    dst[3] = (int)newRef;
                    if (oldRef)
                        (*(void(**)(void*))((int*)oldRef)[1])(oldRef);
                }
            }
            off = off + 0x10;
            i = i + 1;
        } while (i < n);
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e0f90
// ---------------------------------------------------------------------------
void VisitCharts() {
    uint buf[6];
    for (int p = DAT_0170a6b4; p != 0; p = *(int*)(p + 0xc)) {
        for (int* q = *(int**)(p + 8); q != 0; q = (int*)q[1]) {
            int* obj = (int*)*q;
            (*(void(__stdcall**)(int*, void*))(*obj + 0x34))(obj, buf);
        }
    }
}
