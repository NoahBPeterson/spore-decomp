// Slice s00ebb4c0: planet path/waypoint dynamics + waypoint registry.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Vector3 { float x, y, z; Vector3() {} Vector3(float a,float b,float c):x(a),y(b),z(c){} };
struct Matrix3 { float m[9]; };

// EASTL allocator entry point (0x00f473a0): size, tag, flags, debug, file, line.
void* FUN_00f473a0(unsigned n, const char* tag, int a, int b, const char* file, int line);
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// Minimal polymorphic owner: the original performs virtual `this`-calls through
// refcounted objects (vtable slot +0 = release/destroy, +4 = other). Modelling the object as a
// real class makes the compiler emit the same `mov ecx,obj` / `call [vtable+slot]`.
struct IRefObj { virtual void slot0(); virtual void slot4(); };

// thiscall-shaped callees: self in ECX, remaining args on the stack, callee pops them.
struct RbtreeNode {
    void destroy(void* node);                       // 0xd0c930
};
struct Subtree {
    void nuke(void* root);                          // 0x9a9600
};
struct Inner {
    void clear();                                   // 0xbf1b60
};
struct SpaceSim {
    int getPlayerInventory();                       // 0xa1ad60
};
struct Avatar {
    char isBusy();                                  // 0xff6550
    char isOther();                                 // 0xff5b90
};
struct cGameNounManager {
    int GetAvatar();                                // 0xb1fdb0
};
struct TerraformMgr {
    int allowed();                                  // 0xbbc670
};
struct PlanetModel {
    int*  offsetDir(void* out);                     // 0xb81720
    int*  orient(void* out, void* q);               // 0xb7f190
    float radiusAt(void* dir);                      // 0xb7ef70
    float waterHeight();                            // 0xb7e390
};

// thiscall-shaped function-pointer types (used for the vtable-slot calls below).
typedef int*  (__thiscall *TSlotP)(void* o);
typedef int*  (__thiscall *TSlotP1)(void* o, void* a);
typedef float (__thiscall *TSlotF)(void* o);
typedef int   (__thiscall *TSlotIF)(void* o, float a);
typedef int   (__thiscall *TSlotI)(void* o, int a);
typedef void  (__thiscall *TSlotV)(void* o);
typedef void  (__thiscall *TSlotV1)(void* o, void* a);
typedef char  (__thiscall *TSlotC)(void* o);

#define VTSLOT(o, off) (*(void**)((*(int*)(o)) + (off)))

struct WaypointXform {
    unsigned short id;
    unsigned short type;
    float x, y, z, w;
    Matrix3 rot;
};

// The registry / tree / list objects the claimed functions are members of.
struct WpRegistry { void dtor(); };                                            // 0xebbf00
struct WpTree     { void insert(int* out, int pos, unsigned* key, char flag); };// 0xebbd70
struct WpCuller   { void cull(int* a2); };                                     // 0xebbfb0
struct WpList     { void grow(unsigned a2, unsigned a3); };                    // 0xebc1a0

extern "C" {
extern char DAT_016c7330;       // int* gCurPath      0x16c7330
extern char DAT_016c7334;       // int* gCurNode      0x16c7334
extern char DAT_016c7370;       // path struct        0x16c7370
extern char DAT_016c73b4;       //                    0x16c73b4
extern char DAT_016c7380;       //                    0x16c7380
extern float DAT_016c739c;      //                    0x16c739c
extern float DAT_016c73cc;      //                    0x16c73cc
extern float DAT_016c73d0;      //                    0x16c73d0
extern float DAT_016c73d4;      //                    0x16c73d4
extern char DAT_016c7aa4;       //                    0x16c7aa4
extern float DAT_015a95e8;      //                    0x15a95e8
extern float DAT_015a95ec;      //                    0x15a95ec
extern char DAT_01186577;
extern float DAT_016c725c, DAT_016c7260, DAT_016c7264, DAT_016c7268, DAT_016c726c, DAT_016c7270;
}

// callees
void FUN_00ebb2e0(unsigned* p);
void FUN_00ebacb0();
void FUN_00ebb0b0();
void* FUN_00eba860(void* out, void* a, void* b, float c);
unsigned char FUN_00eba7f0(int a, void* b, void* c, unsigned d, unsigned char e);
void* FUN_00eba170(void* a, void* out);
void FUN_00ebafe0(void* a, int b, ...);
int  FUN_00ebbe30(int a, int b, int c);
int  FUN_00ebbdf0(int a, int b, int c);
void __fastcall cGonzagoTimer_dtor(void* p);   // 0x00b638b0
int  FUN_00b3d4d0();
void* FUN_00b5b800();
void* FUN_01002bd0();
void* FUN_00b3d300();
void* FUN_00b3d350();
void* FUN_00b3d430(int a);
void* FUN_00ffbe50();
void* FUN_010212a0();
void* FUN_00921580(void* n);
void  FUN_00921880(void* n, void* tree);
void  FUN_009216a0(void* node, void* parent, void* tree, int pos);
void  FUN_00f47380(void* p);
void  FUN_0059c190(Matrix3* dst, void* src);

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
    while (a != b) {
        if (*(int**)(a + 0x4c) != 0)
            (*(void(**)(void))(** (int**)(a + 0x4c) + 4))();
        if (*(int**)(a + 0x48) != 0)
            (*(void(**)(void))(** (int**)(a + 0x48) + 4))();
        cGonzagoTimer_dtor((void*)(a + 0x28));
        a += 0x50;
        c += 0x50;
    }
    return c;
}

// @ 0x00ebbb10
void __fastcall FUN_00ebbb10(int p)
{
    *(int*)(p + 4) -= 0x50;
    int iVar1 = *(int*)(p + 4);
    IRefObj* o = *(IRefObj**)(iVar1 + 0x4c);
    if (o)
        o->slot4();
    o = *(IRefObj**)(iVar1 + 0x48);
    if (o)
        o->slot4();
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
struct WpStub { int* asg(int* p2); int* cpy(int* p2); };
int* WpStub::asg(int* p1x)
{
    int* p1 = (int*)this; int* p2 = p1x;
    p1[0]=p2[0]; p1[1]=p2[1]; p1[2]=p2[2]; p1[3]=p2[3];
    p1[4]=p2[4]; p1[5]=p2[5]; p1[6]=p2[6]; p1[7]=p2[7]; p1[8]=p2[8];
    p1[0xc]=p2[0xc]; p1[0xd]=p2[0xd]; p1[0xe]=p2[0xe]; p1[0xf]=p2[0xf];
    *(char*)(p1+0x10) = *(char*)(p2+0x10);
    p1[0x11]=p2[0x11];
    int* a = (int*)p2[0x12];
    int* b = (int*)p1[0x12];
    if (a != b) { if (a) ((IRefObj*)a)->slot0(); p1[0x12]=(int)a; if (b) ((IRefObj*)b)->slot4(); }
    a = (int*)p2[0x13];
    b = (int*)p1[0x13];
    if (a != b) { if (a) ((IRefObj*)a)->slot0(); p1[0x13]=(int)a; if (b) ((IRefObj*)b)->slot4(); }
    return p1;
}

// @ 0x00ebbcd0
int* WpStub::cpy(int* p2)
{
    int* p1 = (int*)this;
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
    if (a) ((IRefObj*)a)->slot0();
    a = (int*)p2[0x13];
    p1[0x13]=(int)a;
    if (a) ((IRefObj*)a)->slot0();
    return p1;
}

// @ 0x00ebc120
int* __fastcall FUN_00ebc120(int* p)
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
    return p;
}

// @ 0x00ebbd70
void WpTree::insert(int* out, int pos, unsigned* key, char flag)
{
    int self = (int)this;
    int cond = (flag == 0 && pos != self + 4 &&
                *key >= *(unsigned*)(pos + 0x10)) ? 1 : 0;
    int n = (int)FUN_00f473a0(0x14, "Simulator", 0, 0, ALLOC_FILE, 0xd1);
    if ((unsigned*)(n + 0x10) != 0)
        *(unsigned*)(n + 0x10) = *key;
    FUN_009216a0((void*)n, (void*)pos, (void*)(self + 4), cond);
    int* o = out;
    *(int*)(self + 0x14) += 1;
    *o = n;
}

// @ 0x00ebbf00
void WpRegistry::dtor()
{
    int* p = (int*)this;
    p[0] = 0x148889c;
    ((RbtreeNode*)((char*)p + 0x4c))->destroy((void*)p[0x16]);
    ((Subtree*)((char*)p + 0x30))->nuke((void*)p[0x0f]);
    ((Inner*)((char*)p + 0x1c))->clear();
    FUN_00ebb820((unsigned)p[2], (unsigned)p[3]);
    int* q = (int*)p[2];
    if (q != 0 && *(q - 1) != 0)
        FUN_00f47380(q);
    p[0] = 0x13ef094;
}

// @ 0x00ebbf60
void __fastcall FUN_00ebbf60(int p)
{
    for (int iVar1 = *(int*)(p + 0x54); iVar1 != p + 0x50; iVar1 = (int)FUN_00921580((void*)iVar1))
        (*(void(**)(int))(**(int**)(iVar1 + 0x14) + 0xc))(1);
    int iVar1 = p + 0x50;
    *(int*)(p + 0x54) = iVar1;
    *(int*)iVar1 = iVar1;
    *(int*)(p + 0x58) = 0;
    *(char*)(p + 0x5c) = 0;
    *(int*)(p + 0x60) = 0;
}

// @ 0x00ebb4c0
void FUN_00ebb4c0(unsigned* p, int a2, int a3)
{
    int mode = (*p & 0x1000) ? 1 : a2;
    if (mode == 1)
        FUN_00ebb2e0(p);
    else if (mode == 2)
        FUN_00ebacb0();
    else if (mode == 3)
        FUN_00ebb0b0();

    Vector3 saved;
    saved.x = *(float*)(p + 0x11);
    saved.y = *(float*)(p + 0x12);
    saved.z = *(float*)(p + 0x13);

    float* v = (float*)(p + 0x11);
    float nx = *(float*)(p + 1);
    float ny = *(float*)(p + 2);
    float nz = *(float*)(p + 3);
    v[0] = nx; v[1] = ny; v[2] = nz;

    if ((*p & 1) != 0) {
        float sum = nx * nx + ny * ny + nz * nz;
        float r = ((PlanetModel*)FUN_00b3d350())->radiusAt(v);
        if (sum < r * r) {
            float s = (float)(1.0 / sqrt((double)((nx * nx + ny * ny) + nz * nz) + 1e-08));
            v[0] = (v[0] * s) * r;
            v[1] = (v[1] * s) * r;
            v[2] = (v[2] * s) * r;
        }
    }
    if ((*p & 2) != 0) {
        float sum = v[0] * v[0] + v[1] * v[1] + v[2] * v[2];
        float r = ((PlanetModel*)FUN_00b3d350())->waterHeight();
        if (sum < r * r) {
            float s = (float)(1.0 / sqrt((double)((v[0] * v[0] + v[1] * v[1]) + v[2] * v[2]) + 1e-08));
            v[0] = (v[0] * s) * r;
            v[1] = (v[1] * s) * r;
            v[2] = (v[2] * s) * r;
        }
    }
    if ((*p & 4) != 0) {
        Vector3 local_c;
        float* r = (float*)FUN_00eba860(&local_c, &saved, v, *(float*)(p + 0xb));
        v[0] = r[0]; v[1] = r[1]; v[2] = r[2];
    }
    *(unsigned char*)(p + 0x10) =
        FUN_00eba7f0(a3, &saved, (int*)v, *p, *(unsigned char*)(p + 0x10));
}

// @ 0x00ebb720
void FUN_00ebb720(int* p, int a2)
{
    if (p == 0) {
        *(int*)&DAT_016c7334 = 0;
        *(int*)&DAT_016c7330 = 0;
        return;
    }
    if (*(int*)&DAT_016c7330 != (int)p) {
        int* obj = ((TSlotP)(VTSLOT(p, 0xac)))(p);
        float f1 = *(float*)((char*)obj + 0x80);
        float f2 = *(float*)((char*)obj + 0x74);
        float q = ((TSlotF)(VTSLOT(p, 0x34)))(p) * (f1 - f2);
        int r = ((TSlotIF)(VTSLOT(p, 0x30)))(p, q);
        r = ((TSlotI)(VTSLOT(p, 0x2c)))(p, r);
        FUN_00ebafe0(&DAT_016c7370, 0, r, r, q, a2);
        *(int*)&DAT_016c7330 = (int)p;
    }
    int iVar5 = (int)FUN_00eba170(&DAT_016c7370, &p);
    if (*(int*)&DAT_016c7334 != iVar5) {
        *(int*)&DAT_016c7334 = iVar5;
        FUN_00ebafe0(&DAT_016c7370, iVar5, &DAT_016c73b4, &DAT_016c7380, DAT_016c739c, a2);
    }
    FUN_00ebb4c0((unsigned*)&DAT_016c7370, *(int*)&DAT_016c7334, (int)p);
    ((TSlotV1)(VTSLOT(p, 0x38)))(p, &DAT_016c73b4);
    ((TSlotV1)(VTSLOT(p, 0x3c)))(p, &DAT_016c7380);
}

// @ 0x00ebb8b0
bool FUN_00ebb8b0()
{
    int iVar1 = FUN_00b3d4d0();
    char* p = *(char**)(iVar1 + 0x2c);
    if (p == (char*)1 || p == (char*)2)
        return 0;
    char* mode = (char*)FUN_00b5b800();
    if (mode != (char*)0x1654c05) {
        if (mode == (char*)0x1654c10) {
            char* q = *(char**)(*(char**)&DAT_016c7aa4 + 0x18);
            if (q != 0 && q[0x18d] != 0) {
                int* rec = (int*)FUN_010212a0();
                if (!(*(float*)((char*)rec + 0xb0) <= DAT_015a95ec &&
                      DAT_015a95e8 <= *(float*)((char*)rec + 0xb0) &&
                      *(float*)((char*)rec + 0xb4) <= DAT_015a95ec &&
                      DAT_015a95e8 <= *(float*)((char*)rec + 0xb4)))
                    return 1;
                return 0;
            }
        }
        return 0;
    }
    int av = ((cGameNounManager*)FUN_01002bd0())->GetAvatar();
    if (av != 0) {
        if (((Avatar*)av)->isBusy() != 0)
            return 0;
        if (((Avatar*)av)->isOther() != 0)
            return 0;
        if (*(char*)((char*)av + 0x158) == 0)
            goto terraform;
        return 0;
    }
terraform:
    return ((TerraformMgr*)FUN_00b3d430(0))->allowed() != 0;
}

// @ 0x00ebb980
void FUN_00ebb980(int* p1, float* p2)
{
    Vector3 local;
    if (FUN_00b5b800() == (void*)0x1654c05) {
        int inv = ((SpaceSim*)FUN_00ffbe50())->getPlayerInventory();
        int* v = ((TSlotP)(VTSLOT((char*)inv + 0x34, 0x2c)))((char*)inv + 0x34);
        p1[0] = v[0]; p1[1] = v[1]; p1[2] = v[2];
        float f0 = *(float*)((char*)inv + 0x724) * 1000.0f;
        float f1 = *(float*)((char*)inv + 0x728) * 1000.0f;
        float f2 = *(float*)((char*)inv + 0x72c) * 1000.0f;
        p2[0] = f0; p2[1] = f1; p2[2] = f2;
        if ((f0 * f0 + f1 * f1) + f2 * f2 < 1.0f) {
            int* q = ((TSlotP1)(VTSLOT((char*)inv + 0x34, 0x5c)))((char*)inv + 0x34, &local);
            p2[0] = *(float*)q; p2[1] = *(float*)(q + 1); p2[2] = *(float*)(q + 2);
        }
        return;
    }
    if (*(int*)(*(char**)&DAT_016c7aa4 + 0xcc) == 2) {
        int av = ((cGameNounManager*)FUN_00b3d300())->GetAvatar();
        int* v = ((TSlotP)(VTSLOT((char*)av + 0xc0, 0x2c)))((char*)av + 0xc0);
        p1[0] = v[0]; p1[1] = v[1]; p1[2] = v[2];
        int* q = ((TSlotP1)(VTSLOT((char*)av + 0xc0, 0x5c)))((char*)av + 0xc0, &local);
        p1[0] = q[0]; p1[1] = q[1]; p1[2] = q[2];
        return;
    }
    int* v = ((PlanetModel*)FUN_00b3d350())->offsetDir(&local);
    p1[0] = v[0]; p1[1] = v[1]; p1[2] = v[2];
    p2[0] = DAT_016c73cc;
    p2[1] = DAT_016c73d0;
    p2[2] = DAT_016c73d4;
}

// @ 0x00ebbfb0
void WpCuller::cull(int* a2)
{
    int* p = (int*)this;
    if (p[0x18] == 0)
        return;
    int* obj = 0;
    if (a2 != 0)
        obj = ((TSlotP1)(VTSLOT(a2, 0x5c)))(a2, &DAT_01186577);
    int* pos = ((TSlotP)(VTSLOT(obj, 0x2c)))(obj);
    Vector3 local;
    Matrix3 m;
    int* q = ((PlanetModel*)FUN_00b3d350())->orient(&local, pos);
    FUN_0059c190(&m, q);
    int node = p[0x15];
    while (node != (int)p + 0x50) {
        int* ref = *(int**)(node + 0x14);
        int* head = *(int**)((char*)p + 0x3c);
        int* cur = head;
        int* y = (int*)((char*)p + 0x34);
        while (cur != 0) {
            if (*(unsigned*)((char*)cur + 0x10) < *(unsigned*)(node + 0x10))
                cur = *(int**)cur;
            else { y = cur; cur = *(int**)((char*)cur + 4); }
        }
        int* res = (int*)((char*)p + 0x34);
        if (y != (int*)((char*)p + 0x34) &&
            !(*(unsigned*)(node + 0x10) < *(unsigned*)((char*)y + 0x10)))
            res = y;
        if (res == (int*)((char*)p + 0x34))
            ((TSlotV)(VTSLOT(ref, 0xc)))(ref);
        if (((TSlotC)(VTSLOT(ref, 0x10)))(ref) == 0) {
            p[0x18] -= 1;
            int next = (int)FUN_00921580((void*)node);
            FUN_00921880((void*)node, (void*)((char*)p + 0x50));
            int* z = *(int**)(node + 0x14);
            if (z != 0)
                (*(void(**)(void))(*z + 4))();
            FUN_00f47380((void*)node);
            node = next;
        } else {
            WaypointXform xf;
            xf.id = 6;
            xf.type = 2;
            xf.x = *(float*)pos; xf.y = *(float*)(pos + 1); xf.z = *(float*)(pos + 2); xf.w = 1.0f;
            xf.rot = m;
            ((TSlotV1)(VTSLOT(ref, 0x18)))(ref, &xf);
            node = (int)FUN_00921580((void*)node);
        }
    }
}

// @ 0x00ebc1a0
void WpList::grow(unsigned a2, unsigned a3)
{
    int* p = (int*)this;
    unsigned end = (unsigned)p[1];
    if (end != (unsigned)p[2]) {
        unsigned ins = a3;
        if (a2 <= a3 && a3 < end)
            ins = a3 + 0x50;
        if (end != 0)
            ((WpStub*)end)->cpy((int*)(end - 0x50));
        FUN_00ebbe30((int)a2, p[1] - 0x50, p[1]);
        ((WpStub*)a2)->asg((int*)ins);
        p[1] = p[1] + 0x50;
        return;
    }
    int count = (p[1] - p[0]) / 0x50;
    int buf;
    int cap;
    if (count == 0) {
        cap = 1;
        goto alloc;
    }
    cap = count * 2;
    if (cap == 0) {
        buf = 0;
        goto done;
    }
alloc:
    buf = (int)FUN_00f473a0(cap * 0x50, "Simulator", 0, 0, ALLOC_FILE, 0xd1);
done:
    {
        int dst = FUN_00ebbdf0(p[0], (int)a2, buf);
        FUN_00ebb860(p[0], (int)a2, buf);
        if (dst != 0)
            ((WpStub*)dst)->cpy((int*)a3);
        int old = p[1];
        int newEnd = FUN_00ebbdf0((int)a2, old, dst + 0x50);
        FUN_00ebb860((int)a2, old, dst + 0x50);
        int base = p[0];
        if (base != 0 && *(int*)(base - 4) != 0)
            FUN_00f47380((void*)base);
        p[0] = buf;
        p[1] = newEnd;
        p[2] = cap * 0x50 + buf;
    }
}