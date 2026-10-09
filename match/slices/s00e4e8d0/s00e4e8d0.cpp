// Slice s00e4e8d0 (gold0 slice 27).  Functions 0xe4e8d0 .. 0xe4f750.
// Cell-game fluid update + level tables + cell-gfx helpers.  Optimised with SSE:
// /O2 /MD /Gy /TP /arch:SSE.
#include "types.h"

static inline void** Vt(void* p) { return *(void***)p; }

// ---- operator new/delete ----
void* operator new(unsigned size, const char* name, int a, int b, int c, int d); // 0xf473a0
void  operator_delete__(void* p);                       // 0x00f47380
void* operator_new__(void* dst, int v, int n);          // 0x011e073e (operator new[])

// ---- external callees ----
void  FUN_00e4dde0(void* a, void* b, int n);            // 0x00e4dde0
void  FUN_00e4e8d0(void* p);                            // 0x00e4e8d0
void  FUN_00e4def0(void* p);                            // 0x00e4def0
void  FUN_00e4e660(void* p, int i);                     // 0x00e4e660
int   SP_sPartitionGetNeighbors(int* a, int* b);        // 0x00e4e340
void* FUN_00df5f50(void* out, void* src);               // 0x00df5f50
void* FUN_00e56d40(void* out, void* v);                 // 0x00e56d40
void  FUN_00a7c3d0(int n);                              // 0x00a7c3d0
float FUN_00a7c350();                                   // 0x00a7c350
void  FUN_00e84e40(const char* fmt, ...);               // 0x00e84e40
void  FUN_00743b50(void* p);                            // 0x00743b50
void* thunk_FUN_00e823a0(void* a, void* b);             // 0x00e823a0
void  FUN_00e82130(void* p);                            // 0x00e82130
char  FUN_00a02b40(void* p);                            // 0x00a02b40
void  FUN_00a04ce0(int a);                              // 0x00a04ce0
void  FUN_00a04d00(int a);                              // 0x00a04d00
void* FUN_00b3d4d0();                                   // 0x00b3d4d0
void  FUN_00ad7e40(void* p);                            // 0x00ad7e40

// ---- globals ----
extern int   g_15a7b94_hex;         // 0x015a7b94
extern float g_15a7b94f;            // alias
extern float g_16b39b4, g_16b39b8;  // 0x016b39b4 / 0x016b39b8
extern float g_16b3c88, g_16b3c8c;  // 0x016b3c88 / 0x016b3c8c
extern float g_16b3c94, g_16b3c98;  // 0x016b3c94 / 0x016b3c98
extern float g_16b39d0;             // 0x016b39d0
extern int   g_1483c34[];           // 0x01483c34 level threshold table (stride 7 dwords)
extern int   g_1483c14[];           // 0x01483c14 level value table
extern float g_1483c24[];           // 0x01483c24 level float table
extern float g_1483c20[];           // 0x01483c20 level float table
extern int   g_1483e60;             // 0x01483e60 special (level 1000)
extern void* g_16b3c08;             // 0x016b3c08 cell gfx globals ptr
extern void* g_16b3c0c;             // 0x016b3c0c ptr
struct cTriggerMgr { void FUN_00ad7e40(void* v); };
extern float g_1485720;             // 0x01485720
extern float g_1471064;             // 0x01471064 (0.5f)
extern float g_13eb1bc;             // 0x013eb1bc
extern float g_13ec5b4;             // 0x013ec5b4
extern float g_14851f0;             // 0x014851f0
extern float g_1550adc, g_1550af0, g_1550aec, g_1550ae0, g_1550ae4;
extern int   g_166c004, g_1550a84, g_1550ad8;
extern float g_16b3bf0, g_16b3bec, g_16b3be8, g_16b3be4, g_16b3be0;
extern int   g_16b3bfc, g_16b3bf8, g_16b3bf4;

// =====================================================================
// @ 0x00e4ee30
// =====================================================================
int FUN_00e4ee30(int n)
{
    if (n == 1000) return 0x14;
    int i = 0;
    if (n >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (n >= *p);
    }
    return i - 1;
}

// =====================================================================
// @ 0x00e4ee60
// =====================================================================
int __fastcall SP_sGetSourceLevel(int, int n)
{
    if (n == 1000) return g_1483e60;
    int i = 0;
    if (n >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (n >= *p);
    }
    return g_1483c14[i * 7];
}

// =====================================================================
// @ 0x00e4eea0
// =====================================================================
float __fastcall FUN_00e4eea0(int, int n)
{
    if (n == 1000) return *(float*)((char*)&g_1483e60 + 0x10) * g_1471064;
    int i = 0;
    if (n >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (n >= *p);
    }
    return g_1483c24[i * 7] * g_1471064;
}

// =====================================================================
// @ 0x00e4eef0
// =====================================================================
float __fastcall FUN_00e4eef0(int, int n)
{
    if (n == 1000)
        return (*(float*)((char*)&g_1483e60 + 0xc) / *(float*)((char*)&g_1483e60 + 0x10)) * g_14851f0;
    int i = 0;
    if (n >= 0) {
        int* p = g_1483c34;
        do { p += 7; ++i; } while (n >= *p);
    }
    return (g_1483c20[i * 7] / g_1483c24[i * 7]) * g_14851f0;
}

// =====================================================================
// @ 0x00e4ef60  SP::sDestroyCell
// =====================================================================
int SP_sDestroyCell(int n)
{
    switch (n) {
    case 0: return 0;
    case 1: return 200;
    case 2: return 400;
    case 3: return 600;
    case 4: return 800;
    case 5: return 1000;
    }
    return 0;
}

// =====================================================================
// @ 0x00e4f660
// =====================================================================
void FUN_00e4f660(int v)
{
    ((cTriggerMgr*)FUN_00b3d4d0())->FUN_00ad7e40((void*)v);
    *(char*)((char*)g_16b3c0c + 0x936) = (char)v;
}

// =====================================================================
// @ 0x00e4ebe0  SP::FluidParticlesUpdate
// =====================================================================
void SP_FluidParticlesUpdate(void* p)
{
    FUN_00e4dde0((char*)p + 0x4654, (char*)p + 0x15f94, 0x5dc);
    FUN_00e4e8d0(p);
    FUN_00e4def0((char*)p + 0x1d4d0);
}

// =====================================================================
// @ 0x00e4ec30
// =====================================================================
void FUN_00e4ec30(int base, int idx)
{
    char local[12];
    int* v = (int*)FUN_00df5f50(local, (void*)0x016b3c88);
    int slot = base + idx * 0xc;
    *(int*)(slot + 4) = v[0];
    *(int*)(slot + 8) = v[1];
    *(int*)(slot + 0xc) = v[2];
    int* w = (int*)FUN_00e56d40(local, (void*)(slot + 4));
    *(int*)(slot + 0x4654) = w[0];
    *(int*)(slot + 0x4658) = w[1];
    *(int*)(slot + 0x465c) = w[2];
    --*(int*)(base + 0x1bd54);
    *(int*)(base + idx * 4 + 0x18e74) = 0;
    *(int*)(base + idx * 4 + 0x1a5e4) = *(int*)(base + 0x1bd5c);
    *(int*)(base + 0x1bd5c) = idx;
}

// =====================================================================
// @ 0x00e4f000  SP::sMyCreateModel
// =====================================================================
void SP_sMyCreateModel(int arg)
{
    int* self = 0;
    int m = (*(int(__thiscall**)(void*, int, int, int))((char*)Vt(self) + 0xc))(self, arg, 0, 0);
    if (m == 0) {
        FUN_00e84e40("Unable to create model");
        m = (*(int(__thiscall**)(void*, int, int, int))((char*)Vt(self) + 0xc))(self, 0xcf571b4e, 0xd94352ed, 0);
    }
    ++*(int*)(m + 0x40);
}

// =====================================================================
// @ 0x00e4f680
// =====================================================================
void FUN_00e4f680(int val)
{
    int base = (int)g_16b3c08;
    int n = *(int*)(base + 0x16254);
    if (n <= 0) return;
    int* p = (int*)(base + 0x16214);
    int i = 0;
    while (*p != val) {
        ++i;
        ++p;
        if (i >= n) return;
    }
    *(int*)(base + 0x16214 + i * 4) = *(int*)(base + 0x16214 + n * 4);
    --*(int*)(base + 0x16254);
}

// =====================================================================
// @ 0x00e4f6d0
// =====================================================================
int FUN_00e4f6d0(int* node, int a, int b, int** out, int* counter)
{
    if (a == b) {
        *(int*)*out = *counter;
        *out = *out + 1;
        ++*counter;
        return 1;
    }
    int total = 0;
    int n = 4;
    do {
        ++node;
        if (*node) total += FUN_00e4f6d0((int*)*node, a, b + 1, out, counter);
        --n;
    } while (n != 0);
    return total;
}

// =====================================================================
// @ 0x00e4f550
// =====================================================================
void FUN_00e4f550()
{
    g_16b3bf0 = g_1550adc;
    g_16b3bec = g_1550af0;
    g_16b3be8 = g_1550aec;
    g_16b3be4 = g_1550ae0;
    g_16b3be0 = g_1550ae4;
    g_1550adc = 10.0f;
    g_1550af0 = 11.0f;
    g_1550aec = 90.0f;
    g_16b3bfc = g_166c004;
    g_1550ae0 = 1.0f;
    g_16b3bf8 = g_1550a84;
    g_16b3bf4 = g_1550ad8;
    g_166c004 = 1;
    g_1550a84 = 0;
    g_1550ad8 = 1;
    g_1550ae4 = 1.7f;
}

// =====================================================================
// @ 0x00e4efb0 (thiscall-like; edi carries self in original)
// =====================================================================
int FUN_00e4efb0(void* self, int arg)
{
    int r = (*(int(__thiscall**)(void*, int, int, int*, int*, int))((char*)Vt(self) + 0x30))
        (self, arg, 2, (int*)0x016b3c28, (int*)0x015a7c4c, 1);
    if (r) {
        (*(void(__thiscall**)(void*, int, int, int))((char*)Vt(self) + 0x40))(self, r, 0, 1);
        FUN_00a04ce0(1);
        FUN_00a04d00(1);
    }
    return r;
}

// =====================================================================
// @ 0x00e4f040
// =====================================================================
float FUN_00e4f040(int* self, int arg)
{
    if (self[9]) {
        float f = (*(float(__thiscall**)(void*, void*))((char*)Vt((void*)self[9]) + 0x60))((void*)self[9], &arg);
        if (f == 0.0f) return 1.0f;
        return f;
    }
    char local[4];
    FUN_00743b50(local);
    int* r = (int*)thunk_FUN_00e823a0((void*)self[5], local);
    int n = *(int*)((char*)r + 0x18);
    int i = 0;
    if (n > 0) {
        int* p = (int*)((char*)self + 0x2c);
        int* q = (int*)(*(int*)((char*)r + 0x14) + 4);
        while (!(*q == 3 && *p != 0)) {
            ++i; ++p; q += 10;
            if (i >= n) goto done;
        }
        {
            float f = (*(float(__thiscall**)(void*, void*))((char*)Vt((void*)*p) + 0x60))((void*)*p, &arg);
            if (f != 0.0f) { FUN_00e82130(local); return f; }
        }
    }
done:
    FUN_00e82130(local);
    return 1.0f;
}

// =====================================================================
// @ 0x00e4ecc0
// =====================================================================
int FUN_00e4ecc0()
{
    int base = (int)operator new(0x30580, "Simulator", 0, 0, 0, 0);
    float l10 = g_16b39b4;
    float lc = g_16b39b8;
    int l8 = 0, l4 = 0;
    FUN_00a7c3d0(2);
    char* p = (char*)(base + 4);
    int n = 0x5dc;
    do {
        FUN_00a7c350();
        *(float*)p = (g_16b3c94 - g_16b3c88) * l10 + g_16b3c88;
        *(float*)(p + 4) = (g_16b3c98 - g_16b3c8c) * lc + g_16b3c8c;
        *(float*)(p + 8) = 0.0f;
        char local[12];
        int* w = (int*)FUN_00e56d40(local, p);
        *(int*)(p + 0x4650) = w[0];
        *(int*)(p + 0x4654) = w[1];
        *(int*)(p + 0x4658) = w[2];
        p += 0xc;
        --n;
    } while (n != 0);
    operator_new__((void*)(base + 0x8ca4), 0, 18000);
    operator_new__((void*)(base + 0x4654), 0, 18000);
    operator_new__((void*)(base + 0x11944), 0, 18000);
    operator_new__((void*)(base + 0xd2f4), 0, 18000);
    operator_new__((void*)(base + 0x18e74), 0, 6000);
    *(int*)(base + 0x1bd54) = 0;
    *(int*)(base + 0x1bd58) = 0;
    *(int*)(base + 0x1bd5c) = -1;
    return base;
}

// =====================================================================
// @ 0x00e4e8d0 (fluid solver; best-effort)
// =====================================================================
void FUN_00e4e8d0(int param_1)
{
    char* dst = (char*)(param_1 + 0x15f94);
    operator_new__(dst, 0, 6000);
    float* pf = (float*)(param_1 + 4);
    int outer = 0x5dc;
    do {
        int nb[9], counts[9];
        int cnt = SP_sPartitionGetNeighbors(nb, counts);
        float radius = *(float*)&g_15a7b94_hex;
        for (int j = 0; j < cnt; ++j) {
            int k = counts[j];
            int done = 0;
            if (k > 3) {
                float* a = (float*)(nb[j] + 8);
                float* b = (float*)(nb[j] + 0x28);
                int groups = ((unsigned)(k - 4) >> 2) + 1;
                done = groups * 4;
                for (int g = 0; g < groups; ++g) {
                    for (int t = 0; t < 4; ++t) {
                        float* pa = a + t * 0x20 / 4;
                        float dx = pf[0] - pa[-2], dy = pf[1] - pa[-1], dz = pf[2] - pa[0];
                        float d = dx*dx + dy*dy + dz*dz;
                        if (d <= radius) { float e = radius - d; *(float*)dst += e*e*e; }
                    }
                    a += 0x20; b += 0x20;
                }
            }
            if (done < k) {
                float* q = (float*)(nb[j] + done * 0x20);
                for (int t = done; t < k; ++t) {
                    float dx = pf[0] - q[0], dy = pf[1] - q[1], dz = pf[2] - q[2];
                    float d = dx*dx + dy*dy + dz*dz;
                    if (d <= radius) { float e = radius - d; *(float*)dst += e*e*e; }
                    q += 8;
                }
            }
        }
        float v = *(float*)dst * g_16b39d0;
        *(float*)dst = v;
        ((float*)dst)[0x5dc] = v * 0.5f;
        *(float*)dst = 1.0f / (*(float*)dst + 1.5258789e-05f);
        dst += 4;
        pf += 3;
        --outer;
    } while (outer != 0);
    for (int i = 0; i < 0x5dc; ++i) FUN_00e4e660((void*)param_1, i);
}

// =====================================================================
// @ 0x00e4f100
// =====================================================================
struct cGfxObj {
    void* slot8(void* p, void* a);
    void* slotc(void* p, void* a);
    void* slot14(void* p, void* a);
    void* slot18(void* p);
    void* slot1c(void* p, void* a);
    void* slot24(void* p, void* a);
    void* slot28(void* p, void* a);
    void* slot2c(void* p, void* a);
    void* slot30(void* p, void* a);
    void* slot34(void* p, void* a);
    void* slot3c(void* p, void* a);
};
void FUN_00e4f100(int* self, void* arg, void* p3, void* p4)
{
    char local[4];
    FUN_00743b50(local);
    int* r = (int*)thunk_FUN_00e823a0((void*)self[5], local);
    int n = *(int*)((char*)r + 0x18);
    int i = 0;
    if (n > 0) {
        int* items = (int*)((char*)self + 0x2c);
        int* q = (int*)(*(int*)((char*)r + 0x14) + 4);
        do {
            if (*q == 3 && *items != 0 && !(*(char(__thiscall**)(void*, void*))((char*)Vt((void*)*items) + 0x20))((void*)*items, arg)) {
                cGfxObj* o = (cGfxObj*)*items;
                void* h = o->slot8(o, arg);
                o->slotc(o, (void*)2);
                o->slot14(o, (void*)0);
                o->slot18(o);
                o->slot34(o, p3);
                o->slot28(o, (void*)0);
                o->slot2c(o, (void*)0);
                o->slot30(o, (void*)0);
                o->slot24(o, 0);
                o->slot1c(o, (void*)0x447a0000);
                o->slot3c(o, p4);
            }
            ++i; ++items; q += 10;
        } while (i < n);
    }
    if (self[9]) {
        cGfxObj* o = (cGfxObj*)self[9];
        void* h = o->slot8(o, arg);
        o->slotc(o, (void*)2);
        o->slot14(o, (void*)0);
        o->slot18(o);
        o->slot34(o, p3);
        o->slot28(o, (void*)0);
        o->slot2c(o, (void*)0);
        o->slot30(o, (void*)0);
        o->slot24(o, 0);
        o->slot1c(o, (void*)0x447a0000);
    }
    FUN_00e82130(local);
}

// =====================================================================
// @ 0x00e4f330
// =====================================================================
void FUN_00e4f330(int* self, void* arg, void* p3, int flag)
{
    char local[4];
    FUN_00743b50(local);
    int* r = (int*)thunk_FUN_00e823a0((void*)self[5], local);
    int n = *(int*)((char*)r + 0x18);
    int i = 0;
    if (n > 0) {
        int* items = (int*)((char*)self + 0x2c);
        int* q = (int*)(*(int*)((char*)r + 0x14) + 4);
        do {
            if (*q == 3 && *items != 0) {
                cGfxObj* o = (cGfxObj*)*items;
                void* h = o->slot8(o, arg);
                o->slotc(o, (void*)1);
                o->slot14(o, p3);
                o->slot18(o);
                o->slot34(o, p3);
                o->slot28(o, (void*)0);
                o->slot2c(o, (void*)0);
                o->slot30(o, (void*)h);
                if (flag) { o->slot24(o, (void*)1); o->slot24(o, (void*)0xbf800000); }
            }
            ++i; ++items; q += 10;
        } while (i < n);
    }
    if (self[9]) {
        cGfxObj* o = (cGfxObj*)self[9];
        void* h = o->slot8(o, arg);
        o->slotc(o, (void*)1);
        o->slot14(o, p3);
        o->slot18(o);
        o->slot34(o, p3);
        o->slot28(o, (void*)0);
        o->slot2c(o, (void*)0);
        o->slot30(o, (void*)0);
        if (flag) { o->slot24(o, (void*)1); o->slot24(o, (void*)0xbf800000); }
    }
    FUN_00e82130(local);
}

// =====================================================================
// @ 0x00e4f750
// =====================================================================
int FUN_00e4f750(int* node, int a, int b, int c, int* out, int* counter)
{
    if (a == b) {
        int* e = (int*)node[0];
        e[0] = 1;
        e[2] = *counter;
        ++*counter;
        int* tmp = e + 3;
        int r = FUN_00e4f6d0((int*)node[1], 0, 0, &tmp, &c);
        e[1] = r;
        *out += r * 4 + 0xc;
        return 1;
    }
    if (a == c) {
        int* e = (int*)node[0];
        e[1] = 1;
        int* tmp = e + 2;
        int r = FUN_00e4f6d0((int*)node[1], 0, b, &tmp, (int*)&a);
        e[0] = r;
        e[2 + r] = *counter;
        ++*counter;
        *out += r * 4 + 0xc;
        return 1;
    }
    int total = 0;
    int n = 4;
    int* p = node + 1;
    do {
        if (*p) total += FUN_00e4f750((int*)node, a, b, c, out, counter);
        ++p;
        --n;
    } while (n != 0);
    return total;
}

