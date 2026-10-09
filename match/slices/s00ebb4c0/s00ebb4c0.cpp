// Slice s00ebb4c0: planet path/waypoint dynamics + waypoint registry.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; Vector3() {} Vector3(float a,float b,float c):x(a),y(b),z(c){} };
struct Matrix3 { float m[9]; };
void* operator_new_(unsigned n);

extern "C" {
extern char DAT_016c7330;       // int* gCurPath
extern char DAT_016c7334;       // int* gCurNode
extern char DAT_016c7370;       // path struct
extern char DAT_016c73b4;
extern char DAT_016c7380;
extern char DAT_016c739c;
extern char DAT_016c73cc[3];
extern char DAT_016c7aa4;
extern float DAT_015a95e8;
extern float DAT_015a95ec;
extern float DAT_016c725c, DAT_016c7260, DAT_016c7264, DAT_016c7268, DAT_016c726c, DAT_016c7270;
}

// callees
void FUN_00ebb2e0(unsigned* p);
void FUN_00ebacb0();
void FUN_00ebb0b0();
void* FUN_00eba860(void* out, void* a, void* b, int c);
unsigned char FUN_00eba7f0(int a, void* b, void* c, unsigned d, unsigned char e);
void* FUN_00eba170(void* a, void* out);
void FUN_00ebafe0(void* a, int b, ...);
void* FUN_00ebbe30(int a, int b, int c);
int  FUN_00ebbdf0(int a, int b, int c);
void FUN_00ebbe30b();
int  FUN_00bf1b60();
void __fastcall cGonzagoTimer_dtor(void* p);   // 0x00b638b0
int  FUN_00b3d4d0();
void* SP_GetCurrentGameMode();
void* SP_SpaceGameGet();
void* SP_NounManager();
void* SP_PlanetModel();
void* SP_TerraformingManager(int a);
int  FUN_00ff6550();
int  FUN_00ff5b90();
void* FUN_00ffbe50();
int  FUN_00bbc670(int x);
void* FUN_00b81720(void* p);
void* cSPLivingUniverse_GetActivePlanetRecord();
void* RBTreeIncrement(void* n);
void RBTreeErase(void* n, void* tree);
void RBTreeInsert(void* node, void* parent, void* tree, int pos);
void operator_delete_(void* p);

class RandomLCG { public: double RandomDoubleUniform(); };
extern RandomLCG gMathRandom;

// @ 0x00ebb820
void __stdcall FUN_00ebb820(unsigned a, unsigned b)
{
    for (; a < b; a += 0x50) {
        if (*(int**)(a + 0x4c) != 0)
            (*(void(**)(void))(** (int**)(a + 0x4c) + 4))();
        if (*(int**)(a + 0x48) != 0)
            (*(void(**)(void))(** (int**)(a + 0x48) + 4))();
        cGonzagoTimer_dtor((void*)(a + 0x28));
    }
}

// @ 0x00ebb860
int FUN_00ebb860(int a, int b, int c)
{
    if (a == b)
        return c;
    do {
        if (*(int**)(a + 0x4c) != 0)
            (*(void(**)(void))(** (int**)(a + 0x4c) + 4))();
        if (*(int**)(a + 0x48) != 0)
            (*(void(**)(void))(** (int**)(a + 0x48) + 4))();
        cGonzagoTimer_dtor((void*)(a + 0x28));
        a += 0x50;
        c += 0x50;
    } while (a != b);
    return c;
}

// @ 0x00ebbb10
void __fastcall FUN_00ebbb10(int p)
{
    *(int*)(p + 4) -= 0x50;
    int iVar1 = *(int*)(p + 4);
    if (*(int**)(iVar1 + 0x4c) != 0)
        (*(void(**)(void))(** (int**)(iVar1 + 0x4c) + 4))();
    if (*(int**)(iVar1 + 0x48) != 0)
        (*(void(**)(void))(** (int**)(iVar1 + 0x48) + 4))();
    cGonzagoTimer_dtor((void*)(iVar1 + 0x28));
}

// @ 0x00ebbb40
void FUN_00ebbb40(float* param_1)
{
    float fVar1, fVar2, fVar5;
    do {
        double r = gMathRandom.RandomDoubleUniform();
        double t = (r + r) - 1.0;
        float f = (float)t;
        if (f > 1.0f) f = 1.0f;
        if (f < -1.0f) f = -1.0f;
        fVar1 = f;
        r = gMathRandom.RandomDoubleUniform();
        t = (r + r) - 1.0;
        f = (float)t;
        if (f > 1.0f) f = 1.0f;
        if (f < -1.0f) f = -1.0f;
        fVar2 = f;
        fVar5 = fVar2 * fVar2 + fVar1 * fVar1;
    } while (1.0f < fVar5 || fVar5 < 0.0001f);
    float inv = (float)(1.0 / sqrt((double)fVar5));
    *param_1 = inv * fVar1;
    param_1[1] = inv * fVar2;
}

// @ 0x00ebbc10
int* FUN_00ebbc10(int* p1, int* p2)
{
    p1[0]=p2[0]; p1[1]=p2[1]; p1[2]=p2[2]; p1[3]=p2[3];
    p1[4]=p2[4]; p1[5]=p2[5]; p1[6]=p2[6]; p1[7]=p2[7]; p1[8]=p2[8];
    p1[0xc]=p2[0xc]; p1[0xd]=p2[0xd]; p1[0xe]=p2[0xe]; p1[0xf]=p2[0xf];
    *(char*)(p1+0x10) = *(char*)(p2+0x10);
    p1[0x11]=p2[0x11];
    int* a = (int*)p2[0x12];
    int* b = (int*)p1[0x12];
    if (a != b) { if (a) (*(void(**)(void))*a)(); p1[0x12]=(int)a; if (b) (*(void(**)(void))(*b+4))(); }
    a = (int*)p2[0x13];
    b = (int*)p1[0x13];
    if (a != b) { if (a) (*(void(**)(void))*a)(); p1[0x13]=(int)a; if (b) (*(void(**)(void))(*b+4))(); }
    return p1;
}

// @ 0x00ebbcd0
int* FUN_00ebbcd0(int* p1, int* p2)
{
    p1[0]=p2[0]; p1[1]=p2[1]; p1[2]=p2[2]; p1[3]=p2[3];
    p1[4]=p2[4]; p1[5]=p2[5]; p1[6]=p2[6]; p1[7]=p2[7]; p1[8]=p2[8];
    p1[10]=0x1465d54;
    p1[0xb]=0;
    p1[0xc]=p2[0xc]; p1[0xd]=p2[0xd]; p1[0xe]=p2[0xe]; p1[0xf]=p2[0xf];
    *(char*)(p1+0x10) = *(char*)(p2+0x10);
    p1[0x11]=p2[0x11];
    p1[10]=0x1464450;
    int* a = (int*)p2[0x12];
    p1[0x12]=(int)a;
    if (a) (*(void(**)(void))*a)();
    a = (int*)p2[0x13];
    p1[0x13]=(int)a;
    if (a) (*(void(**)(void))*a)();
    return p1;
}

// @ 0x00ebc120
void __fastcall FUN_00ebc120(int* p)
{
    p[1]=0;
    p[0]=0x148889c;
    p[2]=0; p[3]=0; p[4]=0;
    p[7]=0; p[8]=0; p[9]=0;
    p[0xe]=0; p[0xf]=0; p[0x10]=0;
    int* q = p + 0xd;
    *q = (int)q;
    p[0xe]=(int)q;
    p[0xf]=0;
    *(char*)(p+0x10)=0;
    p[0x11]=0;
    q = p + 0x14;
    p[0x15]=0; p[0x16]=0; p[0x17]=0;
    *q = (int)q;
    p[0x15]=(int)q;
    p[0x16]=0;
    *(char*)(p+0x17)=0;
    p[0x18]=0;
}

// @ 0x00ebbd70
void FUN_00ebbd70(int p1, int* out, int pos, unsigned* key, char flag)
{
    int cond = (flag == 0 && pos != p1 + 4 && *(unsigned*)(pos + 0x10) <= *key) ? 1 : 0;
    int n = (int)operator_new_(0x14);   // approximate alloc
    (void)n;
    RBTreeInsert((void*)n, (void*)pos, (void*)(p1 + 4), cond);
    *(int*)(p1 + 0x14) += 1;
    *out = n;
}

// @ 0x00ebbf60
void __fastcall FUN_00ebbf60(int p)
{
    for (int iVar1 = *(int*)(p + 0x54); iVar1 != p + 0x50; iVar1 = (int)RBTreeIncrement((void*)iVar1))
        (*(void(**)(int))(**(int**)(iVar1 + 0x14) + 0xc))(1);
    int iVar1 = p + 0x50;
    *(int*)(p + 0x54) = iVar1;
    *(int*)iVar1 = iVar1;
    *(int*)(p + 0x58) = 0;
    *(char*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
}

// @ 0x00ebbf00
void __fastcall FUN_00ebbf00(int* p)
{
    p[0] = 0x148889c;
    FUN_00bf1b60();
    FUN_00ebb820(p[2], p[3]);
    int iVar1 = p[2];
    if (iVar1 != 0 && *(int*)(iVar1 - 4) != 0)
        operator_delete_((void*)iVar1);
    p[0] = 0x0;
}

// @ 0x00ebb4c0
void FUN_00ebb4c0(unsigned* p, int a2, int a3)
{
    int mode = ((*p & 0x1000) == 0) ? a2 : 1;
    if (mode == 1) FUN_00ebb2e0(p);
    else if (mode == 2) FUN_00ebacb0();
    else if (mode == 3) FUN_00ebb0b0();
    unsigned local_18 = p[0x11], local_14 = p[0x12], local_10 = p[0x13];
    p[0x11] = p[1]; p[0x12] = p[2]; p[0x13] = p[3];
    if ((*p & 1) != 0) {
        float f5 = 0;
        (void)f5;
    }
    if ((*p & 2) != 0) {
    }
    if ((*p & 4) != 0) {
        float* r = (float*)FUN_00eba860((void*)0, &local_18, p + 0x11, p[0xb]);
        p[0x11] = (unsigned)r[0];
        p[0x12] = (unsigned)r[1];
        p[0x13] = (unsigned)r[2];
    }
    *(char*)(p + 0x10) = FUN_00eba7f0(a3, &local_18, p + 0x11, *p, *(unsigned char*)(p + 0x10));
}

// @ 0x00ebb720
void FUN_00ebb720(int* p, int a2)
{
    if (p == 0) { DAT_016c7334 = 0; DAT_016c7330 = 0; return; }
    if ((int*)&DAT_016c7330 != p) {
        DAT_016c7330 = (char)p;
    }
    int iVar5 = (int)FUN_00eba170(&DAT_016c7370, &p);
    DAT_016c7334 = (char)iVar5;
    FUN_00ebb4c0((unsigned*)&DAT_016c7370, iVar5, (int)p);
}

// @ 0x00ebb8b0
unsigned FUN_00ebb8b0()
{
    int iVar1 = FUN_00b3d4d0();
    char* puVar2 = *(char**)(iVar1 + 0x2c);
    if (puVar2 == (char*)1 || puVar2 == (char*)2)
        return (unsigned)(int)puVar2 & 0xffffff00;
    puVar2 = (char*)SP_GetCurrentGameMode();
    return (unsigned)(int)puVar2 & 0xffffff00;
}

// @ 0x00ebb980
void FUN_00ebb980(int* p1, float* p2)
{
    (void)p1; (void)p2;
}

// @ 0x00ebbfb0
void FUN_00ebbfb0(int p, int* a2)
{
    (void)p; (void)a2;
}

// @ 0x00ebc1a0
void FUN_00ebc1a0(int* p, unsigned a, unsigned b)
{
    (void)p; (void)a; (void)b;
}
