// Slice 8: nSPSkinner vector/normalize helpers and a small packed-value unpacker.
// Unoptimized editor module: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"

void* FUN_0050a880(void* out, int p);          // 0x0050a880
int   FUN_004fddb0(void* v);                   // 0x004fddb0
void* FUN_0044e460(void* out, ...);             // 0x0044e460
void* FUN_00436ce0(void* out, void* a);        // 0x00436ce0
void  FUN_004a9d20(void* a, void* b);          // 0x004a9d20
float FUN_011e0738(float x);                   // 0x011e0738 lib_cblock sqrt
void  FUN_00520220(int p, float* outA, float* outB);

extern float g_1485720;   // 1.0f
extern float g_1485378;   // 0.0f

// @ 0x00520110
unsigned FUN_00520110(int p, unsigned v)
{
    if (v & 0x80000000u)
        return (unsigned)*(unsigned char*)(*(int*)(p + 0x20) + (v & 0x7fffffffu));
    return v;
}

// @ 0x00520140
void FUN_00520140(int p, int flags, float* outDir, float* outVal)
{
    float local_10, local_c, local_8;
    FUN_0044e460(&local_10, &g_1485720, p);
    (void)flags;
    float len2 = (local_10 * local_10 + local_c * local_c) + local_8 * local_8;
    if (len2 <= g_1485378) {
        FUN_00520220(p, outDir, outVal);
    } else {
        float inv = FUN_011e0738(len2);
        FUN_004a9d20(&local_10, &inv);
        outVal[0] = local_10;
        outVal[1] = local_c;
        outVal[2] = local_8;
        void* t = FUN_0044e460(&local_10, &local_10, p);
        float* n = (float*)FUN_00436ce0(&local_10, t);
        outDir[0] = n[0];
        outDir[1] = n[1];
        outDir[2] = n[2];
    }
}

// @ 0x00520220
void FUN_00520220(int p, float* outA, float* outB)
{
    float v[3]; v[0] = g_1485720; v[1] = g_1485720; v[2] = g_1485720;
    float tmp[3];
    int idx = FUN_004fddb0(FUN_0050a880(tmp, p));
    v[idx] = 0.0f;
    float t2[3], t3[3];
    float* n1 = (float*)FUN_00436ce0(t3, FUN_0044e460(t2, v, p));
    outA[0] = n1[0]; outA[1] = n1[1]; outA[2] = n1[2];
    float t4[3], t5[3];
    float* n2 = (float*)FUN_00436ce0(t5, FUN_0044e460(t4, p, outA));
    outB[0] = n2[0]; outB[1] = n2[1]; outB[2] = n2[2];
}

// @ 0x0051fb90 -- PARTIAL skeleton (1404-byte /Od body not reconstructed)
void FUN_0051fb90(void* self) { (void)self; }
