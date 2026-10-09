// slice s006e0fd0: vertex/index-buffer cheats plus the embedded Wu colour
// quantiser (WUINTERNAL histogram moments, box cutting, WU_read).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint;
typedef unsigned char byte;

// ---------------------------------------------------------------------------
// Cheat-command stubs (only the vtable slots these functions touch)
// ---------------------------------------------------------------------------
struct cICommand {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void Register(void* arg);   // +0x1c
};
struct cCommandBase {
    cICommand base_cICommand;
};
struct cArguments {
    char HasFlag(const void* flag);
};

extern "C" void* operator_new(unsigned n, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void  operator_delete__(void* p);

// ---------------------------------------------------------------------------
// Globals / externals (masked)
// ---------------------------------------------------------------------------
extern int  DAT_0170a798;
extern int  DAT_0170a6b4;
extern void* PTR_DAT_01532db0;
extern void* PTR_DAT_01532dac;
extern int  DAT_0140a944;
extern void* PTR_FUN_0140a92c;
extern void* PTR_FUN_0140a9a8;

extern "C" {
void* SP_CheatManager();
void  FUN_006e0f90();
void  FUN_006e0fd0();
void  cCommandBase_ctor(cCommandBase* p);
void* __stdcall galloc(unsigned n);
void  __stdcall gfree(void* p);
void  zero_mem(void* dst, int val, unsigned n);   // misnamed operator_new in the decompile
void* operator_new__(void* dst, int val, unsigned n);
}

// ---------------------------------------------------------------------------
// @ 0x006e0fd0  visit index-buffer lists
// ---------------------------------------------------------------------------
void VisitIndexBuffers() {
    uint buf[5];
    for (int p = DAT_0170a798; p != 0; p = *(int*)(p + 0xc)) {
        for (int* q = *(int**)(p + 8); q != 0; q = (int*)q[1]) {
            int* obj = (int*)*q;
            (*(void(__stdcall**)(int*, void*))(*obj + 0x34))(obj, buf);
        }
    }
}

// ---------------------------------------------------------------------------
// @ 0x006e1010  register the two buffer cheats
// ---------------------------------------------------------------------------
void RegisterBufferCheats() {
    cCommandBase* p = (cCommandBase*)SP_CheatManager();
    (*(void(__thiscall**)(void*, void*))(*(int*)p + 0x1c))(p, PTR_DAT_01532db0);
    p = (cCommandBase*)SP_CheatManager();
    (*(void(__thiscall**)(void*, void*))(*(int*)p + 0x1c))(p, PTR_DAT_01532dac);
}

// ---------------------------------------------------------------------------
// @ 0x006e1040  cheat command: dump vertex buffers
// ---------------------------------------------------------------------------
void __stdcall CommandDumpVertex(cArguments* args) {
    if (args->HasFlag(&DAT_0140a944) != '\0')
        FUN_006e0f90();
}

// ---------------------------------------------------------------------------
// @ 0x006e1070  cheat command: dump index buffers
// ---------------------------------------------------------------------------
void __stdcall CommandDumpIndex(cArguments* args) {
    if (args->HasFlag(&DAT_0140a944) != '\0')
        FUN_006e0fd0();
}

// ---------------------------------------------------------------------------
// @ 0x006e10a0  create the two command objects
// ---------------------------------------------------------------------------
void CreateBufferCheats() {
    cCommandBase* p = (cCommandBase*)operator_new(0x10, "Graphics/VertexBufferCheat", 0, 0, 0, 0);
    if (p != 0) {
        cCommandBase_ctor(p);
        *(void**)p = PTR_FUN_0140a92c;
    }
    SP_CheatManager();
    p = (cCommandBase*)operator_new(0x10, "Graphics/IndexBufferCheat", 0, 0, 0, 0);
    if (p != 0) {
        cCommandBase_ctor(p);
        *(void**)p = PTR_FUN_0140a9a8;
    }
    SP_CheatManager();
}

// ---------------------------------------------------------------------------
// Wu quantiser
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// @ 0x006e1150  WUINTERNAL::Hist3d
// ---------------------------------------------------------------------------
void Hist3d(WuData* self, int* wt, int* mr, int* mg, int* mb, float* weights) {
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

// ---------------------------------------------------------------------------
// @ 0x006e1260  3D cumulative-moment pass
// ---------------------------------------------------------------------------
void MomentPass(int param_1, int param_2, int param_3, int param_4, int param_5) {
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

// ---------------------------------------------------------------------------
// @ 0x006e1480  box moment sum
// ---------------------------------------------------------------------------
int BoxMoments(int* box, int array) {
    int iVar1 = box[4];
    int iVar3 = (box[3] + box[1] * 0x41) * 0x41;
    int iVar2 = box[5];
    int iVar4 = (box[1] * 0x41 + box[2]) * 0x41;
    int iVar5 = (*box * 0x41 + box[3]) * 0x41;
    int iVar6 = (*box * 0x41 + box[2]) * 0x41;
    return ((((*(int*)(array + (iVar1 + iVar5) * 4) - *(int*)(array + (iVar6 + iVar1) * 4)) -
              *(int*)(array + (iVar5 + iVar2) * 4)) - *(int*)(array + (iVar4 + iVar2) * 4)) -
             *(int*)(array + (iVar1 + iVar3) * 4)) + *(int*)(array + (iVar6 + iVar2) * 4) +
           *(int*)(array + (iVar4 + iVar1) * 4) + *(int*)(array + (iVar2 + iVar3) * 4);
}

// ---------------------------------------------------------------------------
// @ 0x006e1520  plane moment sum (axis selector)
// ---------------------------------------------------------------------------
int PlaneMoments(int* box, char axis, int array) {
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

// ---------------------------------------------------------------------------
// @ 0x006e1650  plane moment sum with a fixed coordinate
// ---------------------------------------------------------------------------
int PlaneMoments2(int* box, char axis, int coord, int array) {
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

// ---------------------------------------------------------------------------
// @ 0x006e1780  box variance (float distance moment minus colour moments)
// ---------------------------------------------------------------------------
double BoxVariance(int ctx, int box) {
    int w8 = BoxMoments((int*)box, *(int*)(ctx + 8));
    int wc = BoxMoments((int*)box, *(int*)(ctx + 0xc));
    int w10 = BoxMoments((int*)box, *(int*)(ctx + 0x10));
    int w4 = BoxMoments((int*)box, *(int*)(ctx + 4));
    if (w4 == 0)
        return 0.0;
    return (double)w8 - (double)wc / (double)w4;
    (void)w10;
}

// ---------------------------------------------------------------------------
// @ 0x006e1880  maximise variance along one axis
// ---------------------------------------------------------------------------
double MaximizeVariance(int ctx, int box, int axis, int lo, int hi, int* cut,
                        int w8, int wc, int w10, int w4) {
    int b8 = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 8));
    int bc = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 0xc));
    int b10 = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 0x10));
    int b4 = PlaneMoments((int*)box, (char)axis, *(int*)(ctx + 4));
    float best = 0.0f;
    *cut = -1;
    for (; lo < hi; lo = lo + 1) {
        int a8 = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 8));
        int ac = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 0xc));
        int a10 = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 0x10));
        int a4 = PlaneMoments2((int*)box, (char)axis, lo, *(int*)(ctx + 4));
        a4 = a4 + b4;
        if (a4 != 0) {
            float f12 = (float)(ac + bc);
            float f11 = (float)(a8 + b8);
            float f9 = (float)(a10 + b10);
            if (w4 - a4 != 0) {
                float f14 = (float)(wc - (ac + bc));
                float f13 = (float)(w10 - (a10 + b10));
                float f10 = (float)(w8 - (a8 + b8));
                float var = ((f10 * f10 + f14 * f14) + f13 * f13) / (float)(w4 - a4)
                          + ((f11 * f11 + f12 * f12) + f9 * f9) / (float)a4;
                if (best < var) {
                    *cut = lo;
                    best = var;
                }
            }
        }
    }
    return (double)best;
}

// ---------------------------------------------------------------------------
// @ 0x006e1a30  cut a box into two along the best axis
// ---------------------------------------------------------------------------
int CutBox(int param_1, int* box, int* out) {
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

// ---------------------------------------------------------------------------
// @ 0x006e1be0  fill a 3D region with a byte
// ---------------------------------------------------------------------------
void FillRegion(int* box, unsigned char value, int array) {
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

// ---------------------------------------------------------------------------
// @ 0x006e1c50  WUINTERNAL::AllocWuData
// ---------------------------------------------------------------------------
WuData* AllocWuData() {
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

// ---------------------------------------------------------------------------
// @ 0x006e1d10  WU_open
// ---------------------------------------------------------------------------
struct WuContext {
    int tag;        // +0x00 = 'WUCR' 0x57554352
    int version;    // +0x04 = 4
    int field8;     // +0x08
    WuData* data;   // +0x0c
};

WuContext* WU_open() {
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

// ---------------------------------------------------------------------------
// @ 0x006e1d50  WU_read
// ---------------------------------------------------------------------------
int WU_read(int ctx, int desc, int pixels, int stride) {
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
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
