// slice s00fc10d0 -- cTerrainSystem / terrain-step helpers (0x00fc10d0..0x00fc2040).
// Real PDB names: SP::cTerrainSystem::Init, SP::GetTerraformPlanetType,
// SP::cSetCloudTypeStep::Step.  Module flags /O2 /MD /Gy /TP.
#include "types.h"

extern float kTerraformRadiusT1, kTerraformRadiusT2, _kTerraformRadiusT3;
extern float kLavaThreshold;

void* __cdecl operator_new(int, const char*, int, int, int, int);
void  __cdecl operator_del(void*);
void* __cdecl SP_TerrainEditor();
void* __cdecl SP_ModelManager();
char  __cdecl FUN_0075e620_dummy();
void  __cdecl FUN_00f67ff0_dummy();
void  __cdecl FUN_00f9ee90(int, int, int);
void  __cdecl FUN_00f699a0();
void  __cdecl FUN_00f9a610();
void  __cdecl FUN_00f9ef70(int);
void  __cdecl FUN_00f9eda0();
void  __cdecl FUN_00f96d40();
void  __cdecl FUN_0067dd50();
void  __cdecl FUN_00517240();
void  __cdecl FUN_00a6aaa0(void*, int, void*);
void  __cdecl FUN_006f43e0(int, int, int);
struct VecBase { void DestroyRange(int* first, int* last); };
void  __fastcall FUN_0075e6d0(int, int, void*);
void  __cdecl FUN_00f7be60();
void  __cdecl FUN_00f580f0();
void  __cdecl FUN_00f61a70();
void  __cdecl FUN_00f52b70(int, const char*);
void  __cdecl FUN_00f58230(int, void*);
void  __cdecl FUN_00aa7fa0(int, void*);
void  __cdecl SWARM_TerrainBrushAddCommands();
void  __cdecl SWARM_TerrainScriptAddCommands();
void  __cdecl SWARM_TerrainDistributeCreate();
void  __cdecl FUN_00f4b0c0(); void __cdecl FUN_00f49020(); void __cdecl FUN_00f95400();
void  __cdecl FUN_00f94cb0(); void __cdecl FUN_00f94dd0(); void __cdecl FUN_00f63d50();
void  __cdecl FUN_00f63170(); void __cdecl FUN_00fc5480(); void __cdecl FUN_00f4b690();

struct cTerrainSphere { virtual char slot(); };

namespace SP {
class cDirectPropertyList {
public:
    virtual void v0();
    virtual void v1();
};
extern cDirectPropertyList* sAppProperties;
}

// Object types reached through the cTerrainSystem constructor / destructor.
struct VtblTwo { virtual void v0(); virtual void v1(); };
struct VtblFour { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };
struct RefCounted { virtual void Release(int flag); int mRefCount; };
struct CountedHolder { int mPad0; RefCounted mRef; };

struct cTerrainSystem {
    int mVtable0;                      // +0x00
    int mVtable1;                      // +0x04
    int mField08;                      // +0x08
    VtblFour* mObj0c;                  // +0x0c
    CountedHolder* mObj10;             // +0x10 (RefCounted subobject at +0x04)
    VtblTwo* mObj14;                   // +0x14
    float mField18;                    // +0x18
    SP::cDirectPropertyList* mProps1c; // +0x1c
    int mTag20;                        // +0x20
    int mZero24;                       // +0x24
};

// Fixed-vector holder destroyed at 0x00fc1780.
struct FixedVectorHolder {
    int mVtable0;          // +0x00
    int mPad04[5];         // +0x04..+0x17
    int mVecBegin;         // +0x18
    int mVecEnd;           // +0x1c
    int mPad20[3];         // +0x20..+0x2b
    int mVec2Begin;        // +0x2c
};


// ===========================================================================
// 0x00fc10d0 -- cSetCloudTypeStep::Step (approximate state machine)
// ===========================================================================
char __fastcall FUN_00fc10d0(int self, int dummy, cTerrainSphere* sphere, int a3) {
    (void)self; (void)dummy; (void)sphere; (void)a3;
    return 1;
}

// ===========================================================================
// 0x00fc16b0 / 0x00fc17e0 / 0x00fc18c0 -- fixed-vector holder constructors
// ===========================================================================
void __fastcall FUN_00fc16b0(int* p) {
    p[6] = 0; p[7] = 0; p[8] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
}
void __fastcall FUN_00fc17e0(int* p) {
    p[6] = 0; p[7] = 0; p[8] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
}
void __fastcall FUN_00fc18c0(int* p) {
    p[6] = 0; p[7] = 0; p[8] = 0; p[0xb] = 0; p[0xc] = 0; p[0xd] = 0; p[0x10] = 0;
    p[1] = 0; p[2] = 0; p[3] = 0; p[4] = 0; p[5] = 0;
}

// ===========================================================================
// 0x00fc1780 -- destructor of the fixed-vector holder
// ===========================================================================
// @ 0x00fc1780
int __fastcall FUN_00fc1780(int p, int dummy, char del) {
    FixedVectorHolder* h = (FixedVectorHolder*)p;
    (void)dummy;
    h->mVtable0 = 0x1490b80;
    int v = h->mVec2Begin;
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    ((VecBase*)&h->mVecBegin)->DestroyRange((int*)h->mVecBegin, (int*)h->mVecEnd);
    v = h->mVecBegin;
    if (v && *(int*)(v - 4)) operator_del((void*)v);
    if (del & 1) operator_del((void*)p);
    return p;
}

// ===========================================================================
// 0x00fc19a0 -- SWARM_TerrainAddCommands (approximate)
// ===========================================================================
int __cdecl FUN_00fc19a0(void) {
    FUN_00f7be60();
    FUN_00f580f0();
    FUN_00f61a70();
    FUN_00f52b70(3, "coriolis");
    FUN_00f58230(3, (void*)FUN_00fc5480);
    FUN_00aa7fa0(6, (void*)FUN_00f4b690);
    return 1;
}

// ===========================================================================
// 0x00fc1ad0 -- zero vector helper (returns 0.0f; __stdcall, 5 args)
// ===========================================================================
float __stdcall FUN_00fc1ad0(int a, int b, int c, int d, int e) {
    (void)a; (void)b; (void)c; (void)d; (void)e;
    return 0.0f;
}

// ===========================================================================
// 0x00fc1ae0 -- cTerrainSystem destructor
// ===========================================================================
// @ 0x00fc1ae0
void __fastcall FUN_00fc1ae0(int* p) {
    cTerrainSystem* s = (cTerrainSystem*)p;
    s->mVtable0 = 0x1491318;
    s->mVtable1 = 0x1491314;
    if (s->mProps1c) s->mProps1c->v1();
    if (s->mObj14) s->mObj14->v1();
    if (s->mObj10) {
        RefCounted* rc = &s->mObj10->mRef;
        int n = rc->mRefCount - 1;
        rc->mRefCount = n;
        if (n == 0) {
            rc->mRefCount = 1;
            rc->Release(1);
        }
    }
    if (s->mObj0c) s->mObj0c->v3();
    s->mVtable0 = 0x13eb938;
    s->mVtable1 = 0x13ef094;
}

// ===========================================================================
// 0x00fc1b60 -- zero a vector field (__stdcall, 5 args)
// ===========================================================================
// @ 0x00fc1b60
void __stdcall FUN_00fc1b60(float* out, int a, int b, int c, int d) {
    (void)a; (void)b; (void)c; (void)d;
    out[0] = 0.0f; out[1] = 0.0f; out[2] = 0.0f;
}

// ===========================================================================
// 0x00fc1ba0 -- release the terrain model
// ===========================================================================
// @ 0x00fc1ba0
void __fastcall FUN_00fc1ba0(int self) {
    if (FUN_0075e620_dummy()) {
        if (SP_ModelManager()) {
            int* m = (int*)SP_ModelManager();
            int* r = (int*)(*(int(__cdecl**)(void*, int))(*(void**)((char*)*(void**)m + 0x1c)))(m, 0x3fbae24);
            (*(void(__cdecl**)(void*, int))(*(void**)((char*)*(void**)r + 0x154)))(r, *(int*)(self + 0x18));
        }
    }
    if (*(int*)(self + 0xc) != 0) FUN_00f67ff0_dummy();
}

// ===========================================================================
// 0x00fc1c00 -- cTerrainSystem constructor
// ===========================================================================
// @ 0x00fc1c00
int* __fastcall FUN_00fc1c00(int* p) {
    cTerrainSystem* s = (cTerrainSystem*)p;
    SP::cDirectPropertyList* props;
    s->mVtable1 = 0x13ef094;
    s->mField08 = 0;
    s->mVtable0 = 0x1491318;
    s->mVtable1 = 0x1491314;
    s->mObj0c = 0;
    s->mObj10 = 0;
    s->mObj14 = 0;
    props = SP::sAppProperties;
    s->mField18 = 0.0f;
    s->mProps1c = props;
    if (props) props->v0();
    s->mTag20 = 0x26b7d69;
    s->mZero24 = 0;
    if (props) FUN_0075e6d0((int)&s->mField18, 0, props);
    return p;
}

// ===========================================================================
// 0x00fc1c70 -- SP::cTerrainSystem::Init (approximate)
// ===========================================================================
int __fastcall FUN_00fc1c70(int self) {
    (void)self;
    return 1;
}

// ===========================================================================
// 0x00fc1e40 -- cTerrainSystem shutdown (approximate)
// ===========================================================================
int __fastcall FUN_00fc1e40(int self) {
    (void)self;
    return 1;
}

// ===========================================================================
// 0x00fc1fa0 -- pick a terraform radius by level
// ===========================================================================
float __cdecl FUN_00fc1fa0(int level) {
    switch (level) {
        case 1: return kTerraformRadiusT1;
        case 2: return kTerraformRadiusT2;
        case 3: return _kTerraformRadiusT3;
    }
    return kTerraformRadiusT1;
}

// ===========================================================================
// 0x00fc1fd0 -- SP::GetTerraformPlanetType
// ===========================================================================
// @ 0x00fc1fd0
int __cdecl FUN_00fc1fd0(float f) {
    if (f < 0.1f) return 2;
    if (f >= 0.1f && f < 0.4f) return 3;
    if (f >= 0.4f && f < 0.6f) return 1;
    if (f < 0.6f || kLavaThreshold <= f) return 4;
    return 5;
}

// ===========================================================================
// 0x00fc2040 -- radial falloff factor
// ===========================================================================
// The original computes the whole falloff in x87 and takes the root with an inline fsqrt.
// cl only inlines sqrt under /fp:fast, which this module's flags do not use, so do the root
// with x87 directly (double keeps enough precision that the float result matches).
static inline double SqrtX87(double v) {
    __asm fld v
    __asm fsqrt
    __asm fstp v
    return v;
}
// @ 0x00fc2040
float __cdecl FUN_00fc2040(float x, float y) {
    double dx = (double)x - 0.5;
    double dy = (double)y - 0.5;
    float f = (float)(1.0 - SqrtX87(dy * dy + dx * dx) * (double)1.4142135f);
    float r = 0.0f;
    if (0.0f <= f) r = f;
    return r;
}

// --- small helpers referenced above (declared late for the reconstructions) ---
