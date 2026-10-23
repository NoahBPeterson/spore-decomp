// Slice s00da8630: behavior-tree helpers around hut / animal stimuli decisions
// (0x00da8630..0x00da94c0).  Most are __cdecl with stack arguments and return either
// a boolean in al or an x87 float (long double) in st0.  The tree is talked to through
// the behaviour object at [self+0xb4c] shifted by 8: Play(a,flags), ClearAll(a,flags).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef long double    float10;

struct Vec3 { float x, y, z; };

extern double g_d01;          // 0x01447a10  0.1
extern double g_d09;          // 0x0147c248  0.9
extern float  g_f400;         // 0x013f0e84  400.0
extern float  g_half;         // 0x01471064  0.5

// ---------------------------------------------------------------------------
// forward declarations of callees
// ---------------------------------------------------------------------------
struct PlayObj {
    void* Play(int a, int flags);                     // 0x00bc96a0 (thiscall)
    void  ClearAll(int a, int flags);                 // 0x00bc98f0 (thiscall)
};
void* GetAny(void* stimuli);                          // 0x00d997e0 (thiscall on stimuli)
struct Stimuli { void GetAny(); };                    // 0x00d997e0 thiscall
void* GetAnimalFromStimulus(void* s);                 // 0x00d99980
void* GetTribe(void* c);                              // 0x00c22f50 (thiscall)
void* GetChieftain(void* tribe);                      // 0x00c8fd30 (thiscall)
double RandomDoubleUniform(void* rng);                // 0x009360d0
struct Rng { double RandomDoubleUniform(); };         // 0x009360d0 (thiscall, ecx=rng)
double HUT_IN_DANGER_Decide(void* c, ...);            // 0x00da6920

struct CreatureBase { bool IsSomething(); };          // 0x00c0b780 thiscall -> bool
bool CreatureBase_Check(void* c);                     // 0x00c0b780
void* FUN_00d998d0(void* anim, uint id);              // 0x00d998d0
void  FUN_00da6270(int self, int a);                  // 0x00da6270

extern "C" {
    int   g_flag169f3b4;                              // 0x0169f3b4
    float g_dist169f3b0;                              // 0x0169f3b0
}

// ---------------------------------------------------------------------------
// 00da9220 : try to start an idle play, then check the played entity is near
// ---------------------------------------------------------------------------
// @ 0x00da9220
bool FUN_00da9220(int self, void* stimuli, char* out, int a4, int a5)
{
    PlayObj* po = (PlayObj*)((char*)*(void**)(self + 0xb4c) + 8);
    void* ent = po->Play(a4, a5);
    if (ent) {
        if ((g_flag169f3b4 & 1) == 0) {
            g_flag169f3b4 |= 1;
            g_dist169f3b0 = g_f400;
        }
        Vec3* pos = (Vec3*)(*(void*(**)(int))(*(int*)(self + 0xc0) + 0x2c))(self + 0xc0);
        float dx = pos->x - *(float*)((char*)ent + 0x14);
        float dy = pos->y - *(float*)((char*)ent + 0x18);
        float dz = pos->z - *(float*)((char*)ent + 0x1c);
        float dist = dx * dx + dy * dy + dz * dz;
        if (g_dist169f3b0 > dist) {
            if (stimuli)
                ((Stimuli*)stimuli)->GetAny();
            *out = 1;
            *(int*)((char*)stimuli + 0x18) = *(int*)((char*)ent + 0xc);
            *(int*)((char*)stimuli + 0x1c) = *(int*)((char*)ent + 0x10);
            *(int*)((char*)stimuli + 0xc)  = *(int*)((char*)ent + 0x14);
            *(int*)((char*)stimuli + 0x10) = *(int*)((char*)ent + 0x18);
            *(int*)((char*)stimuli + 0x14) = *(int*)((char*)ent + 0x1c);
            po->ClearAll(a4, a5);
            return 1;
        }
        po->ClearAll(a4, a5);
    }
    return 0;
}

// @ 0x00da9330
float10 f00da9330(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (FUN_00da9220(a1, (void*)a5, (char*)a6, 0, 1))
        return (float10)1;
    return (float10)0;
}

// @ 0x00da9360
float10 f00da9360(int a1, int a2, int a3, int a4, int a5, int a6)
{
    if (FUN_00da9220(a1, (void*)a5, (char*)a6, 0, 4))
        return (float10)1;
    return (float10)0;
}

// @ 0x00da8fe0
float10 f00da8fe0(void)
{
    float10 fVar1 = (float10)((Rng*)0x01601760)->RandomDoubleUniform();
    float10 fVar2 = (float10)0.1;
    float10 fVar3 = fVar1 * (float10)0.9 + fVar2;
    fVar1 = (float10)1;
    if (fVar3 < fVar1) {
        fVar1 = fVar3;
        if (fVar3 < fVar2)
            return fVar2 * (float10)g_half;
    }
    return fVar1 * (float10)g_half;
}

// @ 0x00da8f20
float10 f00da8f20(int creature)
{
    void* chief = GetChieftain(GetTribe((void*)creature));
    if (!chief)
        return (float10)-1;
    Vec3* a = (Vec3*)(*(void*(**)(int))(*(int*)(creature + 0xc0) + 0x2c))(creature + 0xc0);
    Vec3* b = (Vec3*)(*(void*(**)(int))(*(int*)((char*)chief + 0xc0) + 0x2c))((int)chief + 0xc0);
    float dx = b->x - a->x;
    float dy = b->y - a->y;
    float dz = b->z - a->z;
    float d = dx * dx + dy * dy + dz * dz;
    float f = *(float*)((char*)chief + 0xcc) - *(float*)(creature + 0xcc);
    return (float10)(d * f);
}

// @ 0x00da8960
float10 FUN_00da8960(int self, int a2, int a3, int a4, void* stimuli, char* out)
{
    void* anim = ((PlayObj*)((char*)*(void**)(self + 0xb4c) + 8))->Play(0x4000000, 0);
    if (((CreatureBase*)self)->IsSomething()) {
        void* s = GetAnimalFromStimulus(anim);
        if (s && *(char*)((char*)s + 0xb5e) != 0 && *(float*)((char*)s + 0xb84) > 0.0f) {
            if (stimuli)
                ((Stimuli*)stimuli)->GetAny();
            *(int*)((char*)stimuli + 4) = (int)((int*)s + 0x16a);
            *out = 1;
            return (float10)1;
        }
    }
    int* p = (int*)FUN_00d998d0(anim, 0x2a0349a);
    if (p && *(char*)((char*)p + 0xa9) != 0) {
        bool b = ((bool(__thiscall*)(void*))(*(int*)(p[0] + 0x2c)))(p);
        if (!b && p[0x87] == 0) {
            if (stimuli)
                ((Stimuli*)stimuli)->GetAny();
            *(int*)((char*)stimuli + 8) = (int)p;
            *out = 1;
            return (float10)1;
        }
    }
    FUN_00da6270(self, 0x1b);
    return (float10)0;
}

// @ 0x00da8a40
void FUN_00da8a40(int self)
{
    (void)self;
}

// @ 0x00da8c40
void FUN_00da8c40(int self)
{
    (void)self;
}

// @ 0x00da8e20
void FUN_00da8e20(int self)
{
    (void)self;
}

// @ 0x00da8630
void FUN_00da8630(int self)
{
    (void)self;
}

// @ 0x00da9020
float10 IN_HUT_IN_DANGER_Decide(int self, double d, int a3, int a4, int a5, int a6, int a7)
{
    double f = HUT_IN_DANGER_Decide((void*)self, d, a3, a4, a5, a6, a7);
    if (f == 0.0)
        return (float10)0;
    return (float10)1;
}

// @ 0x00da9160
void InitNearHutForReaction(int self)
{
    (void)self;
}

// @ 0x00da9390
float10 f00da9390(int self, int a2)
{
    (void)self; (void)a2;
    return (float10)0;
}

// @ 0x00da94c0
void f00da94c0(int self)
{
    (void)self;
}
