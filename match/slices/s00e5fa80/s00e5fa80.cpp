// Slice s00e5fa80 -- SPGonzago/SPCellGame.obj (cell stage): random cell extents,
// the "lookat target position" resolver, and a couple of small update helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast  (cell TU; no /EHsc)
#include "types.h"

typedef uint8_t  uint8;
typedef uint16_t uint16;
typedef uint32_t uint32;

#define I(p,o) (*(int*)((char*)(p) + (o)))
#define F(p,o) (*(float*)((char*)(p) + (o)))
#define B(p,o) (*(uint8*)((char*)(p) + (o)))
#define GF(a)  (*(float*)(a))
#define GI(a)  (*(int*)(a))

struct ObjectPool {                    // cSPObjectPool at gspCellGame + 0x1c
    void* Get(int id);                 // 0x00b72210
    void* GetSafe(int id);             // 0x00b721d0
};
extern char* gspCellGame;              // 0x016b3c04

struct RandomLCG {                     // EA::Random::RandomLinearCongruential
    uint32 RandomUint32Uniform(uint32 range);   // 0x00a68fb0
    double RandomDoubleUniform();               // 0x009360d0
};
extern RandomLCG gRandomLCG;           // 0x01601760

extern float gFMax;                    // 0x014851e8  ( 3.4028235e38)
extern float gFMin;                    // 0x013f51ac  (-3.4028235e38)
extern float gDirA[3];                 // 0x015a7c40
extern float gRotDir[3];               // 0x015a7c28

// ---------------------------------------------------------------- helpers
int   FUN_00e5fa00(void* self, int kind, void* out);   // 0x00e5fa00 (custom eax ABI)
float* FUN_00e5eb20(void* out, int cell);              // 0x00e5eb20
void  FUN_00e5aab0(float* out, int id);                // 0x00e5aab0
char  FUN_00e5aae0(float* out);                        // 0x00e5aae0 (out in ESI)
int   FUN_00e573e0(void* a, void* b);                  // 0x00e573e0
char  FUN_00e5cd00(void* cell);                        // 0x00e5cd00 (arg in EAX)
float FUN_00e50060();                                  // 0x00e50060
void  FUN_00e53460();                                  // 0x00e53460

// @ 0x00e5fa80  counts/sums the per-type cell limits into a 5-float stride array
// (the destination base arrives in EDI, a custom register ABI)
int FUN_00e5fa80(void* self, float* out)
{
    int n = 0;
    int a = FUN_00e5fa00(self, 2, 0);
    n += a;
    int b = FUN_00e5fa00(self, 1, out + n * 5);
    n += b;
    int c = FUN_00e5fa00(self, 0, out + n * 5);
    n += c;
    int d = FUN_00e5fa00(self, -1, out + n * 5);
    n += d;
    int e1 = FUN_00e5fa00(self, 4, out + n * 5);
    n += e1;
    int e2 = FUN_00e5fa00(self, 3, out + n * 5);
    n += e2;
    int e3 = FUN_00e5fa00(self, 2, out + n * 5);
    n += e3;
    int e4 = FUN_00e5fa00(self, 1, out + n * 5);
    n += e4;
    int e5 = FUN_00e5fa00(self, 0, out + n * 5);
    return n + e5;
}

// @ 0x00e5fb50  SP::sRandomExtents
float* sRandomExtents(float* out, float* in, float t)
{
    out[0] = gFMax;
    out[1] = gFMax;
    out[2] = gFMax;
    out[3] = gFMin;
    out[4] = gFMin;
    out[5] = gFMin;

    double lim = 1.0 - (double)t;

    double r1 = gRandomLCG.RandomDoubleUniform();
    double d1 = r1 * lim;
    float v1 = (float)d1;
    if (v1 >= (float)lim)
        v1 = (float)lim;
    if (v1 < 0.0f)
        v1 = 0.0f;

    double r2 = gRandomLCG.RandomDoubleUniform();
    double d2 = r2 * lim;
    float v2 = (float)d2;
    if (v2 >= (float)lim)
        v2 = (float)lim;
    if (v2 < 0.0f)
        v2 = 0.0f;

    out[0] = (in[3] - in[0]) * v1 + in[0];
    out[1] = (in[4] - in[1]) * v2 + in[0];
    out[2] = 0.0f;
    out[3] = (in[3] - in[0]) * t + out[0];
    out[4] = (in[4] - in[1]) * t + out[1];
    out[5] = 0.0f;
    return out;
}

// @ 0x00e5fc90  resolve a cell's lookat/target position from a mode selector
float* FUN_00e5fc90(float* out, int cell, int mode, int id)
{
    float dx, dy, dz;
    float rx, ry, rz;

    switch (mode) {
    case 1: {
        float tmp[3];
        float* p = FUN_00e5eb20(tmp, cell);
        dx = p[0];
        dy = p[1];
        dz = p[2];
        break;
    }
    case 2:
        dx = F(cell, 0x68) * gRotDir[1] + F(cell, 0x74) * gRotDir[2] + F(cell, 0x5c) * gRotDir[0];
        dy = F(cell, 0x6c) * gRotDir[1] + F(cell, 0x78) * gRotDir[2] + F(cell, 0x60) * gRotDir[0];
        dz = F(cell, 0x70) * gRotDir[1] + F(cell, 0x7c) * gRotDir[2] + F(cell, 0x64) * gRotDir[0];
        break;
    case 3:
        rx = F(cell, 0x4c) - (F(cell, 0x68) * gRotDir[1] + F(cell, 0x74) * gRotDir[2] +
                              F(cell, 0x5c) * gRotDir[0]) * 10.0f;
        ry = F(cell, 0x50) - (F(cell, 0x6c) * gRotDir[1] + F(cell, 0x78) * gRotDir[2] +
                              F(cell, 0x60) * gRotDir[0]) * 10.0f;
        rz = F(cell, 0x54) - (F(cell, 0x70) * gRotDir[1] + F(cell, 0x7c) * gRotDir[2] +
                              F(cell, 0x64) * gRotDir[0]) * 10.0f;
        goto store;
    case 4:
    case 5:
    case 6:
    case 7:
    case 8: {
        void* o = ((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(id);
        if (o != 0) {
            FUN_00e5aab0(out, id);
            return out;
        }
        /* fallthrough */
    }
    case 0:
        dx = gDirA[0];
        dy = gDirA[1];
        dz = gDirA[2];
        break;
    case 9:
        out[0] = F(cell, 8);
        out[1] = F(cell, 0xc);
        out[2] = F(cell, 0x10);
        return out;
    case 10: {
        float tmp[3];
        if (FUN_00e5aae0(tmp)) {
            out[0] = tmp[0];
            out[1] = tmp[1];
            out[2] = tmp[2];
            return out;
        }
        out[0] = F(cell, 0x4c);
        out[1] = F(cell, 0x50);
        out[2] = F(cell, 0x54);
        return out;
    }
    case 0xb: {
        void* o = ((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(I(gspCellGame, 0x411c));
        if (o != 0) {
            out[0] = F(o, 0x4c);
            out[1] = F(o, 0x50);
            out[2] = F(o, 0x54);
            return out;
        }
        out[0] = F(cell, 0x4c);
        out[1] = F(cell, 0x50);
        out[2] = F(cell, 0x54);
        return out;
    }
    default:
        out[0] = F(cell, 0x4c);
        out[1] = F(cell, 0x50);
        out[2] = F(cell, 0x54);
        return out;
    }

    rx = F(cell, 0x4c) + dx * 10.0f;
    ry = F(cell, 0x50) + dy * 10.0f;
    rz = F(cell, 0x54) + dz * 10.0f;
store:
    out[0] = rx;
    out[1] = ry;
    out[2] = rz;
    return out;
}

// @ 0x00e5ff70  per-frame "approach player" timer update
void FUN_00e5ff70(float dt)
{
    int state = I(gspCellGame, 0x51b4);
    if (state == -1)
        return;

    void* other = ((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(I(gspCellGame, 0x51b0));
    void* avatar = ((ObjectPool*)((char*)gspCellGame + 0x1c))->GetSafe(I(gspCellGame, 0x411c));

    if (other == 0 || B(other, 0x112) == 1 || avatar == 0 ||
        FUN_00e573e0(avatar, other) != 3) {
        state = I(gspCellGame, 0x51b4);
        if (state == 3)
            goto doState3;
        if (state == -1)
            goto clear;
    } else {
        if (FUN_00e5cd00(other) == 0) {
            float v = FUN_00e50060();
            float local = v;
            float* p = &local;
            if (!(F(gspCellGame, 0x51b8) < v))
                p = (float*)(gspCellGame + 0x51b8);
            F(gspCellGame, 0x51b8) = *p;
            return;
        }
        float left = F(gspCellGame, 0x51b8) - dt;
        F(gspCellGame, 0x51b8) = left;
        if (!(left <= 0.0f))
            return;
        state = I(gspCellGame, 0x51b4);
        if (state == 3) {
        doState3:
            FUN_00e53460();
            goto clear;
        }
    }

    *(int*)(I(gspCellGame, 0x5190) + (state + 8) * 0x10) = 3;
clear:
    I(gspCellGame, 0x51b4) = -1;
    I(gspCellGame, 0x51b0) = 0;
}
