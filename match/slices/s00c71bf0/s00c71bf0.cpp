// Slice s00c71bf0: SP::cPlanet / cVisiblePlanet (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
#include "types.h"
#include <math.h>

struct PlanetData;
struct CPlanet;
struct IntVec2 { int* begin; int* end; int* cap; };
struct MinMax { float mn, mx; };

extern float g_01693efc, g_01693f00, g_01693f04;
extern float g_016944e0;
extern float g_01471064;
extern float g_0147256c;
extern float g_015787fc;
extern void* g_bgSimManager_016dda8c;
extern void* g_dummyMat_016944bc;
extern void* g_dummyVec_015787e4;
extern uint32_t g_016941dc;
extern void* vtbl_CPlanet_014725d8;
extern void* vtbl_CPlanet_gd_01472580;
extern void* vtbl_CPlanet_d8_01472570;

inline float MaxF(float a, float b) { __asm { movss xmm0, a
                                             maxss xmm0, b
                                             movss a, xmm0 } return a; }
inline float MinF(float a, float b) { __asm { movss xmm0, a
                                             minss xmm0, b
                                             movss a, xmm0 } return a; }

struct PlanetData {
    virtual int AddRef(); virtual int Release();
    char pad_08[0x28 - 4];
    uint32_t mField28;             // +0x28
    uint32_t mField2C;             // +0x2c
    char pad_30[0x98 - 0x30];
    uint8_t mField98;              // +0x98
    char pad_99[0x9c - 0x99];
    float m9C;                     // +0x9c
    float mA0;                     // +0xa0
    float mA4;                     // +0xa4
    float mA8;                     // +0xa8
    char pad_ac[0xb0 - 0xac];
    float mB0, mB4, mB8;
    char pad_c4[0xd0 - 0xc4];
    uint32_t* mpD0; uint32_t* mpD4;
    char pad_d8[0x124 - 0xd8];
    int mField124;
    char pad_128[0x15c - 0x128];
    uint32_t mp15C, mp160;
    char pad_164[0x170 - 0x164];
    uint32_t mp170, mp174;

    void* fn_00b8de30();
    void* fn_00b8dec0(int i);
    void  fn_00b8df80(int i);
    void  fn_00b8dfe0(int i);
    int   fn_00b8dab0();
    void* fn_00b8dad0();
    bool  fn_00b8dac0();
    void* fn_00b8da70();
    void  fn_00b8d910();
    void  fn_00b8d920(int b);
    void  fn_00b8dde0(int a, int b);
    void* fn_00b8d8e0(void* out);
    bool  fn_00b8e040(uint32_t key);
};

struct HasSlots {
    virtual void h00(); virtual void h04(); virtual void h08(); virtual void h0c();
    virtual void h10(); virtual void h14(); virtual void h18(); virtual void h1c();
    virtual void h20(); virtual void h24(); virtual void h28(); virtual void h2c();
    virtual void h30(); virtual void h34(); virtual void h38(); virtual void h3c();
    virtual void h40(); virtual void h44(); virtual void h48();
    virtual void* h4c();           // +0x4c
};

struct CPlanet {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int  v2c();
    virtual void* v30();
    virtual void v34(); virtual void v38();
    virtual void v3c(void* p);     // +0x3c

    char pad_04[0xa6 - 4];
    uint8_t mFieldA6;              // +0xa6
    char pad_a7[0xd4 - 0xa7];
    void* mpGDvptr;                // +0xd4
    char pad_d8[0x108 - 0xd8];
    void* mpCommon;                // +0x108
    char pad_10c[0x138 - 0x10c];
    void* mp138;                   // +0x138
    PlanetData* mpPlanet;          // +0x13c
    uint32_t mField140;            // +0x140
    uint32_t mField144;            // +0x144
    char pad_148[0x154 - 0x148];
    void* mp154;                   // +0x154
    uint32_t mField158;            // +0x158
    void* mStr15C;                 // +0x15c
    void* mStr160;                 // +0x160
    void* mStr164;                 // +0x164
    uint32_t mField16C;            // +0x16c
    char pad_170[0x184 - 0x170];
    float mField184;               // +0x184
    void* mp188;                   // +0x188
    void* mp18c;                   // +0x18c
    char pad_190[0x1b8 - 0x190];
    uint8_t mField1B8;             // +0x1b8
    char pad_1b9[0x1bc - 0x1b9];
    uint32_t mField1BC;            // +0x1bc

    void FUN_00c71bf0(void* out);
    float FUN_00c71d30();
    void  FUN_00c71da0(float f);
    void* FUN_00c71e30();
    void* FUN_00c71e70();
    void  FUN_00c72190(int a);
    bool  FUN_00c72370();
    void  FUN_00c723d0();
    void  FUN_00c72450(int a, int b);
    void* FUN_00c72470(int free);
    void  FUN_00c72540();
    void* ctor_00c725a0();
    void  FUN_00c72770(float f);
    void  FUN_00c729b0(void* out, uint32_t* key);
    void  FUN_00c72a10(void* v, uint32_t tail);
    void  FUN_00c72a70();
    bool  FUN_00c72b80(void* p);
    void  fn_00c8a420();
};

// ---------------------------------------------------------------- free calls
void*  cSPLivingUniverse_GetActivePlanet_01021260();
void*  cSPLivingUniverse_GetPlayerEmpire_01021300();
void*  StarManager_00b3d2a0(void* p);
void*  NounManager_00b3d300();
void*  NounManager_CreateNoun_00b20c60(void* mgr, uint32_t id);
void*  cStarManager_GetEmpireByID_00ba9370(void* sm);
void*  cEmpire_GetHomePlanet_00c31730(void* emp);
void*  FUN_00ba6dc0_00(void* sm);
void   FUN_00b3d3d0_00(void* p, int a);
void   FUN_00b3d2a0v(void* p);
void   FUN_00b184c0_00(void* p);
void   cGameData_dtor_00b184c0(void* p);
void   cGameData_ctor_00b18660(void* p);
bool   cGameData_Read_00b18600(void* p, void* s);
void   cSpatialObject_ctor_00c89630(void* p);
void   FUN_00c8a420_00(void* p);
void   FUN_00c8b2e0_00(void* p);
bool   FUN_00c88b00_00(void* p);
void   FUN_00c8b2e0(CPlanet* p);
void   operator_delete_00f47380(void* p);
void*  operator_new_00f473a0(int size, const char* file, int a, int b, int c, int d);
void   FUN_00f48a80_00();
void*  FUN_00f48a80();
void   FUN_00c7e280_00(void* p);
void   FUN_00c82f00_00(void* p);
float* Matrix3FromQuaternion_0059c190(void* out, void* q);
void   Matrix3_Assign_0041cb40(void* dst, void* src);
void   FUN_00453b20_00();
void   FUN_00478db0_00(void* p, void* v);
void   FUN_00c75c30_00();
void   FUN_01029790_00();
void   FUN_0102f810_00(int a);
void   FUN_0102f810(int a);
void   FUN_0102f8c0_00(int a);
void   FUN_01005c60_00(int a);
void   FUN_00bf6fa0_00(int a);
void*  cSPTransform_BackTransformPoint_004ff6d0(void* t, void* p);
void   FUN_00c70110_00(void* pp, void* v);
void   FUN_00b96f40_00(void* p, int a);
void   WString_Assign_00423650(void* a, void* b);
void   cGonzagoTimer_ctor_00b63890(void* p);
void   FUN_00fc20e0(void* out, float a, float b);
void   FUN_00801920_00(void* o);
void*  FUN_004554f0(void* a, void* b, void* c);
void   FUN_00ba2e50();
void   FUN_0102f810v();
void   FUN_00b8e040v();

// ================================================================ definitions

// @ 0x00c71bf0
void CPlanet::FUN_00c71bf0(void* out)
{
    void* active = cSPLivingUniverse_GetActivePlanet_01021260();
    if (active == this) {
        *(float*)((char*)out + 0) = g_01693efc;
        *(float*)((char*)out + 4) = g_01693f00;
        *(float*)((char*)out + 8) = g_01693f04;
        return;
    }
    float mat[9];
    Matrix3_Assign_0041cb40(mat, &g_dummyMat_016944bc);
    void* q = v30();
    float* p = Matrix3FromQuaternion_0059c190(mat, q);
    (void)p;
    *(float*)((char*)out + 0) = mat[0];
    *(float*)((char*)out + 4) = mat[1];
    *(float*)((char*)out + 8) = mat[2];
}

// @ 0x00c71d30
float CPlanet::FUN_00c71d30()
{
    PlanetData* pd = mpPlanet;
    if (pd == 0) return 0.5f;
    float v = pd->mB8;
    if (v >= 0.0f) return v;
    void* o = FUN_00f48a80();
    int vv = ((int(__thiscall*)(void*, void*))(*(void***)((char*)o + 8)))(o, 0);
    (void)vv;
    return 0.0f;
}

// @ 0x00c71da0
void CPlanet::FUN_00c71da0(float f)
{
    PlanetData* pd = mpPlanet;
    if (pd != 0 && pd->mB8 >= 0.0f) {
        MinMax mm;
        FUN_00fc20e0(&mm, pd->mB0, pd->mB4);
        f = MaxF(f, mm.mn);
        f = MinF(f, mm.mx);
        pd->mB8 = f;
    }
}

// @ 0x00c71e30
void* CPlanet::FUN_00c71e30()
{
    if (mpPlanet != 0 && mpPlanet->fn_00b8dab0() == 5) {
        void* e = ((HasSlots*)mpGDvptr)->h4c();
        void* sm = StarManager_00b3d2a0(e);
        return cStarManager_GetEmpireByID_00ba9370(sm);
    }
    return 0;
}

// @ 0x00c71e70
void* CPlanet::FUN_00c71e70()
{
    if (mp154 == 0) {
        void* mgr = NounManager_00b3d300();
        void* n = NounManager_CreateNoun_00b20c60(mgr, 0x3572e72);
        void* r;
        if (n == 0) r = 0;
        else r = ((void*(__thiscall*)(void*, uint32_t))(*(void***)n)[3])(n, 0x3572e6c);
        void* old = mp154;
        if (r != old) {
            if (r != 0) ((void(__thiscall*)(void*))(*(void***)r)[0])(r);
            mp154 = r;
            if (old != 0) ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
        }
        FUN_00c7e280_00(mp154);
        FUN_00c82f00_00(mp154);
    }
    return mp154;
}

// @ 0x00c71f00
float __cdecl FUN_00c71f00(float f, int a, float b, float maxSpice, char hw, char storage, char param7, float param8, int planet, char param10)
{
    (void)a;
    int mx = 0;
    FUN_0102f810_00(0);
    (void)mx;
    return 0.0f;
}

// @ 0x00c72030
void FUN_00c72030()
{
    CPlanet* p = (CPlanet*)cSPLivingUniverse_GetActivePlanet_01021260();
    void* o = p->mpPlanet->fn_00b8de30();
    FUN_00801920_00(o);
}

// @ 0x00c72190
void CPlanet::FUN_00c72190(int a) { (void)a; }

// @ 0x00c72370
bool CPlanet::FUN_00c72370()
{
    PlanetData* pd = mpPlanet;
    if (pd != 0 && pd->fn_00b8dab0() == 5) {
        void* e = ((HasSlots*)mpGDvptr)->h4c();
        void* sm = StarManager_00b3d2a0(e);
        void* emp = cStarManager_GetEmpireByID_00ba9370(sm);
        return emp == cSPLivingUniverse_GetPlayerEmpire_01021300();
    }
    return 0 == cSPLivingUniverse_GetPlayerEmpire_01021300();
}

// @ 0x00c723d0
void CPlanet::FUN_00c723d0()
{
    void* p = mp138;
    if (p != 0) {
        ((void(__thiscall*)(void*, int))(*(void***)p)[0x16c / 4])(p, 0);
        void* q = *(void**)((char*)mp138 + 0x64);
        if (q != 0) {
            *(void**)((char*)mp138 + 0x64) = 0;
            ((void(__thiscall*)(void*))(*(void***)q)[1])(q);
        }
        p = mp138;
        if (p != 0) {
            mp138 = 0;
            int rc = *(int*)((char*)p + 0x40);
            if (rc > 1) {
                *(int*)((char*)p + 0x40) = rc - 1;
            } else {
                int f = (*(unsigned*)((char*)p + 4)) >> 31;
                ((void(__thiscall*)(void*, int))(*(void***)p)[0x170 / 4])(p, f);
            }
        }
    }
}

// @ 0x00c72450
void CPlanet::FUN_00c72450(int a, int b)
{
    FUN_00c723d0();
    FUN_00478db0_00((char*)this + 0x138, (void*)a);
    (void)b;
}

// @ 0x00c72470
void* CPlanet::FUN_00c72470(int free)
{
    *(void**)this = vtbl_CPlanet_014725d8;
    *(void**)((char*)this + 0xd4) = vtbl_CPlanet_gd_01472580;
    *(void**)((char*)this + 0xd8) = vtbl_CPlanet_d8_01472570;
    void* q = mpCommon;
    if (q != 0) ((void(__thiscall*)(void*))(*(void***)q)[0xc0 / 4])(q);
    cGameData_dtor_00b184c0((char*)this + 0xd4);
    FUN_00c8a420_00(this);
    if (free & 1) operator_delete_00f47380(this);
    return this;
}

// @ 0x00c72540
void CPlanet::FUN_00c72540() {}

// @ 0x00c725a0
void* CPlanet::ctor_00c725a0()
{
    cSpatialObject_ctor_00c89630(this);
    cGameData_ctor_00b18660((char*)this + 0xd4);
    return this;
}

// @ 0x00c72770
void CPlanet::FUN_00c72770(float f) { (void)f; }

// @ 0x00c729b0
void CPlanet::FUN_00c729b0(void* out, uint32_t* key) { (void)out; (void)key; }

// @ 0x00c72a10
void CPlanet::FUN_00c72a10(void* v, uint32_t tail)
{
    int* p = (int*)v;
    if (p[0] != p[1]) {
        if (p != (int*)((char*)this + 0x15c))
            WString_Assign_00423650(p, (void*)p[1]);
        mField16C = 0;
        return;
    }
    mField16C = tail;
    if (mStr15C != mStr160) {
        *(uint16_t*)mStr15C = 0;
        mStr160 = mStr15C;
    }
}

// @ 0x00c72a70
void CPlanet::FUN_00c72a70() {}

// @ 0x00c72b80
bool CPlanet::FUN_00c72b80(void* p)
{
    bool b;
    if (cGameData_Read_00b18600((char*)this + 0xd4, p)) {
        b = FUN_00c88b00_00(this);
    } else b = false;
    return b;
}
