// Slice s00c709d0: Simulator::cVisiblePlanet / SP::cPlanet helpers (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
#include "types.h"
#include <math.h>

inline float MaxF(float a, float b) { __asm { movss xmm0, a
                                             maxss xmm0, b
                                             movss a, xmm0 } return a; }
inline float MinF(float a, float b) { __asm { movss xmm0, a
                                             minss xmm0, b
                                             movss a, xmm0 } return a; }

struct PlanetData;
struct VPlanet;
struct IntVec { int* begin; int* end; int* cap; };
struct MinMax { float mn, mx; };

struct RandomLCG;
extern RandomLCG g_rng_01601760;
extern uint32_t g_01693f08, g_01693f0c, g_01693f10;
extern void* g_simSingleton_0167a60c;
extern void* vtbl_VPlanet_01472480;
extern void* vtbl_VPlanet_gd_01472428;
extern void* vtbl_VPlanet_d8_01472414;
extern float g_f_013f1cac;
extern float g_f_01486110;
extern float g_f_01485720;
extern float g_f_01472568;
extern float g_f_013ef550;

struct PropertyT {
    uint32_t mData[4];
    uint8_t  mFlags;
    uint8_t  pad11;
    uint16_t mType;
    uint32_t* GetUInt_0041ea00();
};
struct PropMgr {
    virtual void q00(); virtual void q04(); virtual void q08(); virtual void q0c();
    virtual void q10(); virtual void q14(); virtual void q18(); virtual void q1c();
    virtual void q20();
    virtual bool GetProperty_0041ea70(uint32_t id, PropertyT*& out);   // +0x24
    virtual void q28();
    virtual void GetByKey_2c(void* a, uint32_t id, void** out);        // +0x2c
};
struct RefObj {
    virtual int AddRef(); virtual int Release();
};
struct PropertyUser {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20();
    virtual bool GetProperty_0041ea70(uint32_t id, PropertyT*& out);   // +0x24
};

struct PlanetData {
    virtual int AddRef();          // +0x0
    virtual int Release();         // +0x4
    char pad_08[0x28 - 4];
    uint32_t mField28;             // +0x28
    uint32_t mField2C;             // +0x2c
    char pad_2d[0x98 - 0x30];
    uint8_t mField98;              // +0x98
    char pad_99[0xb0 - 0x99];
    float mB0;                     // +0xb0
    float mB4;                     // +0xb4
    float mB8;                     // +0xb8
    uint32_t* mpBC;                // +0xbc
    uint32_t* mpC0;                // +0xc0
    char pad_c4[0xd0 - 0xc4];
    uint32_t* mpD0;                // +0xd0
    uint32_t* mpD4;                // +0xd4
    char pad_d8[0x124 - 0xd8];
    int mField124;                 // +0x124
    char pad_128[0x15c - 0x128];
    uint32_t mp15C;               // +0x15c
    uint32_t mp160;               // +0x160
    char pad_164[0x170 - 0x164];
    uint32_t mp170;               // +0x170
    uint32_t mp174;               // +0x174

    void* fn_00b8dec0(int i);
    void* fn_00b8de30();
    void  fn_00b8df80(int i);
    void  fn_00b8dfe0(int i);
    int   fn_00b8dab0();
    void* fn_00b8dad0();
    bool  fn_00b8dac0();
    void* fn_00b8da70();
    void  fn_00b8d920(int b);
    void  fn_00b8d910();
    void  fn_00b8dde0(int a, int b);
};

struct cCivData {
    IntVec* GetCities_005c65e0();
    void    EraseCity_00ff1fb0(int idx);
    int     GetAccessFlags_00ff0420();
};
struct SimSingleton { bool FUN_00ae3740(); bool FUN_00ae4180_00(int id); };
struct NodeBB9 { int fn_00bb9ae0(); };
struct StarMgr { void* GetEmpireByID_00ba9370(); };
struct Empire { int GetHomePlanet_00c31730(); };

// Node with a vtable slot 0xac returning a pointer.
struct Node0AC {
    virtual void n00(); virtual void n04(); virtual void n08(); virtual void n0c();
    virtual void n10(); virtual void n14(); virtual void n18(); virtual void n1c();
    virtual void n20(); virtual void n24(); virtual void n28(); virtual void n2c();
    virtual void n30(); virtual void n34(); virtual void n38(); virtual void n3c();
    virtual void n40(); virtual void n44(); virtual void n48(); virtual void n4c();
    virtual void n50(); virtual void n54(); virtual void n58(); virtual void n5c();
    virtual void n60(); virtual void n64(); virtual void n68(); virtual void n6c();
    virtual void n70(); virtual void n74(); virtual void n78(); virtual void n7c();
    virtual void n80(); virtual void n84(); virtual void n88(); virtual void n8c();
    virtual void n90(); virtual void n94(); virtual void n98(); virtual void n9c();
    virtual void na0(); virtual void na4(); virtual void na8();
    virtual void* naC();           // +0xac
};

struct VPlanet {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual int  v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();

    char pad_68[0x68 - 4];
    void* mp68;                    // +0x68
    char pad_6c[0xa6 - 0x6c];
    uint8_t mFieldA6;              // +0xa6
    char pad_a7[0xd4 - 0xa7];      // +0xd4 cGameData subobject
    void* mpGD_vptr;               // +0xd4
    char pad_d8[0x100 - 0xd8];
    void* mp100;                   // +0x100
    char pad_104[0x108 - 0x104];
    void* mpCommon;                // +0x108
    char pad_10c[0x13c - 0x10c];
    PlanetData* mpPlanet;          // +0x13c
    uint32_t mField140;            // +0x140
    char pad_144[0x154 - 0x144];
    void* mp154;                   // +0x154
    uint32_t mField158;            // +0x158
    char pad_15c[0x184 - 0x15c];
    float mField184;               // +0x184
    void* mp188;                   // +0x188
    void* mp18c;                   // +0x18c
    char pad_190[0x1bc - 0x190];
    uint32_t mField1BC;            // +0x1bc
    char pad_1c0[0x1c4 - 0x1c0];
    uint32_t mField1C4;            // +0x1c4

    float FUN_00c709d0();
    void  FUN_00c70a00(float f);
    float FUN_00c70a20();
    void  FUN_00c70a50(float f);
    int   FUN_00c70a70();
    void  FUN_00c70aa0(float f);
    bool  FUN_00c70b20(int a, int b);    bool  FUN_00c70b50();
    void  FUN_00c70bc0(int v);
    int   FUN_00c70c10();
    int   FUN_00c70c90();
    bool  FUN_00c70d10(uint32_t* key);
    bool  FUN_00c70d40(uint32_t* key);
    int   FUN_00c70d70(uint32_t* key);
    int   FUN_00c70e00();
    void  FUN_00c70fb0();
    int   FUN_00c70fd0(int a);
    PlanetData* FUN_00c71040(int a);
    int   FUN_00c710c0();
    int   FUN_00c71120();
    void  FUN_00c711e0(int id);
    void  FUN_00c71370(int id);
    void  FUN_00c713c0(int a);
    void  FUN_00c713f0();
    bool  FUN_00c71400(int i);
    void  FUN_00c71430(int i, char on);
    int   FUN_00c71470();
    void  FUN_00c71560(uint32_t mask);
    void  FUN_00c71680();
    void  FUN_00c71750(PlanetData* p);
    void  FUN_00c71910();
    void  FUN_00c719d0(int mode);
    void* FUN_00c71570();
    void  fn_00c8b2e0();
};

// ---------------------------------------------------------------- free calls
void*  StarManager_00b3d2a0(void* avatar);
void*  NounManager_00b3d300();
PropMgr* PropertyManager_0067de30();
void*  MessageServer_0067dcc0();
void*  __stdcall TerraformingManager_00b3d430(void* p);
struct TerraformingMgr { void F670(); };
struct NounMgr { void* GetAvatar(); };
void*  GetSetting9_00401090();
void*  FUN_00b3d420(int p);
void*  FUN_00b90410_00(void* mgr, int id);
uint32_t* eastl_find_00ac0d80(uint32_t* first, uint32_t* last, uint32_t* key);
void   FUN_00fc20e0(void* out, float a, float b);
bool   FUN_00c70150_00(PlanetData* pd, int a, int b);
int    FUN_00c70880_this(VPlanet* self);
int    FUN_00c705c0_00(PlanetData* pd, int a);
void   SetPlanetTechLevel_00c706d0(PlanetData* pd, int v);
void*  operator_new_00f473a0(int size, const char* file, int a, int b, int c, int d);
void*  SimSingleton_ctor_00ae5c30(void* mem);
void*  FUN_00c65e0_00();
void   cSpatialObject_ctor_00c89630(void* p);
void   cGameData_ctor_00b18660(void* p);
void   FUN_00c8b2e0(VPlanet* p);
uint32_t RandomUint32Uniform_00a68fb0(void* rng, int n);
struct RandomLCG { uint32_t RandomUint32Uniform(int n); };
struct HasAccess { int GetAccessFlags_00ff0420(); };
extern char g_rngObj_01601760;
void*  GetProfile_004df550(void* mgr, uint32_t* key);
void*  cStarRecordRef_GetCommContext_00ce6950(PlanetData* p);
void   FUN_0103ca40_00(PlanetData* p, int a);
void   FUN_00b96f40_00(PlanetData* p, int a);
void   FUN_00c3f2d0_00(void* o, void* p);
void   FUN_00b3d3d0_00(void* p, int a);
void   FUN_00c3f1b0_00(void* o, float a, float b);
void*  FUN_00c7e280_00(void* p);
void*  FUN_00c716d0_00(void* mgr);
void*  FUN_00c716f0_00(void* mgr);
void   FUN_00c70110_00(void* pp, void* val);
void   FUN_00c3f160_00(void* o, void* p);
void   FUN_00b225d0_00(void* mgr, void* p);
void   FUN_00571d90_00(void* o);
void   FUN_007d44a0_00(void* o);
void*  GetAvatar_00b1fdb0_00(void* o);
void*  GetEmpireByID_00ba9370_00(void* sm);
int    GetHomePlanet_00c31730_00(void* emp);
void*  FUN_00ba6dc0_00(void* sm);
void*  GetSpeciesFromID_00b90410(void* mgr, int id);
void*  FUN_00b3d2a0_00(void* p);

// ================================================================ definitions

// @ 0x00c709d0
float VPlanet::FUN_00c709d0()
{
    if (mpPlanet != 0) return mpPlanet->mB0;
    return 0.5f;
}

// @ 0x00c70a00
void VPlanet::FUN_00c70a00(float f) { mpPlanet->mB0 = f; }

// @ 0x00c70a20
float VPlanet::FUN_00c70a20()
{
    if (mpPlanet != 0) return mpPlanet->mB4;
    return 0.5f;
}

// @ 0x00c70a50
void VPlanet::FUN_00c70a50(float f) { mpPlanet->mB4 = f; }

// @ 0x00c70a70
int VPlanet::FUN_00c70a70()
{
    if (mpPlanet != 0 && mpPlanet->mB8 >= 0.0f) return 1;
    return 0;
}

// @ 0x00c70aa0
void VPlanet::FUN_00c70aa0(float f)
{
    if (mpPlanet != 0) {
        MinMax mm;
        FUN_00fc20e0(&mm, mpPlanet->mB0, mpPlanet->mB4);
        f = MaxF(f, mm.mn);
        f = MinF(f, mm.mx);
        mpPlanet->mB8 = f;
    }
}

// @ 0x00c70b20
bool VPlanet::FUN_00c70b20(int a, int b)
{
    if (a == 0) return false;
    return FUN_00c70150_00(mpPlanet, a, b);
}

// @ 0x00c70b50
bool VPlanet::FUN_00c70b50()
{
    PlanetData* pd = mpPlanet;
    NodeBB9* o = (NodeBB9*)pd->fn_00b8de30();
    if (o->fn_00bb9ae0() == 5) {
        void* av = ((NounMgr*)o)->GetAvatar();
        void* sm = StarManager_00b3d2a0(av);
        void* emp = ((StarMgr*)sm)->GetEmpireByID_00ba9370();
        return ((Empire*)emp)->GetHomePlanet_00c31730() == (int)pd;
    }
    return false;
}

// @ 0x00c70bc0
void VPlanet::FUN_00c70bc0(int v) { if (mpPlanet != 0) mpPlanet->mField124 = v; }

// @ 0x00c70c10
int VPlanet::FUN_00c70c10()
{
    PlanetData* pd = mpPlanet;
    int n = (int)(pd->mpD4 - pd->mpD0) / 3;
    if (n > 0) {
        int idx = g_rng_01601760.RandomUint32Uniform(n);
        uint32_t* e = pd->mpD0 + idx * 3;
        if (e[0] != g_01693f08 || e[1] != g_01693f0c || e[2] != g_01693f10)
            return (int)GetProfile_004df550(GetSetting9_00401090(), e);
    }
    return 0;
}

// @ 0x00c70c90
int VPlanet::FUN_00c70c90()
{
    PlanetData* pd = mpPlanet;
    int n = (int)(pd->mpC0 - pd->mpBC) / 3;
    if (n > 0) {
        int idx = g_rng_01601760.RandomUint32Uniform(n);
        uint32_t* e = pd->mpBC + idx * 3;
        if (e[0] != g_01693f08 || e[1] != g_01693f0c || e[2] != g_01693f10)
            return (int)GetSpeciesFromID_00b90410(FUN_00b3d420((int)e), (int)e);
    }
    return 0;
}

// @ 0x00c70d10
bool VPlanet::FUN_00c70d10(uint32_t* key)
{
    PlanetData* pd = mpPlanet;
    uint32_t* last = pd->mpD4;
    return eastl_find_00ac0d80(pd->mpD0, last, key) != last;
}

// @ 0x00c70d40
bool VPlanet::FUN_00c70d40(uint32_t* key)
{
    PlanetData* pd = mpPlanet;
    uint32_t* last = pd->mpC0;
    return eastl_find_00ac0d80(pd->mpBC, last, key) != last;
}

// @ 0x00c70d70
int VPlanet::FUN_00c70d70(uint32_t* key)
{
    PlanetData* pd = mpPlanet;
    if (pd == 0) return -1;
    int n = (int)(pd->mpD4 - pd->mpD0) / 3;
    uint32_t* e = pd->mpD0;
    for (int i = 0; i < n; ++i, e += 3)
        if (e[0] == key[0] && e[1] == key[1] && e[2] == key[2]) return i;
    return -1;
}

// @ 0x00c70e00
int VPlanet::FUN_00c70e00()
{
    PlanetData* pd = mpPlanet;
    if (pd != 0) return pd->fn_00b8dab0();
    return 1;
}

// @ 0x00c70e20
float __cdecl FUN_00c70e20(PlanetData* pd, int mode)
{
    if (!pd->fn_00b8dac0())
        return -1.0f * 0.0f + sqrtf(pd->mB0 * pd->mB0 + (pd->mB4 * pd->mB4) + pd->mB8 * pd->mB8);
    void* a = pd->fn_00b8da70();
    void* sm = StarManager_00b3d2a0(a);
    int* o = (int*)FUN_00ba6dc0_00(sm);
    int* ref = 0;
    if (o != 0) { ((void(__thiscall*)(void*))(*(void***)o)[0])(o); ref = o; }
    float dist;
    void* fl = (char*)ref + 0x44;
    if (mode == 0) {
        dist = sqrtf(*(float*)((char*)ref + 0x44) * *(float*)((char*)ref + 0x44)
                   + (*(float*)((char*)ref + 0x48) * *(float*)((char*)ref + 0x48))
                   + *(float*)((char*)ref + 0x4c) * *(float*)((char*)ref + 0x4c))
             - sqrtf(pd->mB0 * pd->mB0 + (pd->mB4 * pd->mB4) + pd->mB8 * pd->mB8);
    } else if (mode == 1) {
        dist = sqrtf(*(float*)((char*)ref + 0x44) * *(float*)((char*)ref + 0x44)
                   + (*(float*)((char*)ref + 0x48) * *(float*)((char*)ref + 0x48))
                   + *(float*)((char*)ref + 0x4c) * *(float*)((char*)ref + 0x4c));
    } else if (mode == 2) {
        dist = sqrtf(pd->mB0 * pd->mB0 + (pd->mB4 * pd->mB4) + pd->mB8 * pd->mB8)
             + sqrtf(*(float*)((char*)ref + 0x44) * *(float*)((char*)ref + 0x44)
                   + (*(float*)((char*)ref + 0x48) * *(float*)((char*)ref + 0x48))
                   + *(float*)((char*)ref + 0x4c) * *(float*)((char*)ref + 0x4c));
    } else {
        dist = 0.0f;
    }
    (void)fl;
    if (ref != 0) ((void(__thiscall*)(void*))(*(void***)ref)[1])(ref);
    return dist;
}

// @ 0x00c70fb0
void VPlanet::FUN_00c70fb0()
{
    ((TerraformingMgr*)TerraformingManager_00b3d430(mpPlanet))->F670();
}

// @ 0x00c70fd0
int VPlanet::FUN_00c70fd0(int a)
{
    if (mp154 == 0) return 0;
    PlanetData* pd = mpPlanet;
    return FUN_00c705c0_00(pd, a);
}

// @ 0x00c71040
PlanetData* VPlanet::FUN_00c71040(int a)
{
    PlanetData* pd = mpPlanet;
    int n = (int)(pd->mp160 - pd->mp15C) >> 2;
    for (int i = 0; i < n; ++i) {
        void* o = pd->fn_00b8dec0(i);
        if (((HasAccess*)o)->GetAccessFlags_00ff0420() == a) return (PlanetData*)o;
    }
    return 0;
}

// @ 0x00c710c0
int VPlanet::FUN_00c710c0()
{
    return (int)(mpPlanet->mp160 - mpPlanet->mp15C) >> 2;
}

// @ 0x00c71120
int VPlanet::FUN_00c71120()
{
    return (int)(mpPlanet->mp174 - mpPlanet->mp170) >> 2;
}

// @ 0x00c71160  SP::RemoveArtifact
void __cdecl RemoveArtifact_00c71160(char* p, int* key, short id)
{
    int n = (int)(*(int*)(p + 0x138) - *(int*)(p + 0x134)) / 0x2c;
    int* e = *(int**)(p + 0x134);
    for (int i = 0; i < n; ++i, e += 0xb) {
        if (e[0] == key[0] && (short)e[4] == id) {
            int* dst = *(int**)(p + 0x134) + i * 0xb;
            int* src = (int*)(*(int*)(p + 0x138) - 0x2c);
            for (int k = 11; k != 0; --k) *dst++ = *src++;
            *(int*)(p + 0x138) -= 0x2c;
            return;
        }
    }
}

// @ 0x00c711e0
void VPlanet::FUN_00c711e0(int id)
{
    PlanetData* pd = mpPlanet;
    int n = (int)(pd->mp160 - pd->mp15C) >> 2;
    for (int i = 0; i < n; ++i) {
        cCivData* civ = (cCivData*)pd->fn_00b8dec0(i);
        IntVec* vec = civ->GetCities_005c65e0();
        int cnt = (int)(vec->end - vec->begin);
        int* p = vec->begin;
        for (int j = 0; j < cnt; ++j, ++p) {
            if (*p == id) {
                civ->EraseCity_00ff1fb0(j);
                if (vec->begin == vec->end) {
                    if (g_simSingleton_0167a60c == 0) {
                        void* mem = operator_new_00f473a0(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
                        g_simSingleton_0167a60c = mem ? SimSingleton_ctor_00ae5c30(mem) : 0;
                    }
                    int acc = ((HasAccess*)civ)->GetAccessFlags_00ff0420();
                    if (!((SimSingleton*)g_simSingleton_0167a60c)->FUN_00ae4180_00(acc))
                        mpPlanet->fn_00b8df80(i);
                }
                goto check;
            }
        }
    }
check:
    if (mpPlanet->mp15C == mpPlanet->mp160) {
        if (g_simSingleton_0167a60c == 0) {
            void* mem = operator_new_00f473a0(0xc8, "Simulator/SimSingleton", 0, 0, 0, 0);
            g_simSingleton_0167a60c = mem ? SimSingleton_ctor_00ae5c30(mem) : 0;
        }
        if (!((SimSingleton*)g_simSingleton_0167a60c)->FUN_00ae3740()) {
            void* ms = MessageServer_0067dcc0();
            ((void(__thiscall*)(void*, uint32_t, int, int, int))(*(void***)ms)[6])(ms, 0x43f2583, 0, 0, 0);
            SetPlanetTechLevel_00c706d0(mpPlanet, 1);
        }
    }
}

// @ 0x00c71370
void VPlanet::FUN_00c71370(int id)
{
    PlanetData* pd = mpPlanet;
    int n = (int)(pd->mp174 - pd->mp170) >> 2;
    uint32_t* e = (uint32_t*)pd->mp170;
    for (int i = 0; i < n; ++i, ++e)
        if (*e == (uint32_t)id) { pd->fn_00b8dfe0(i); return; }
}

// @ 0x00c713c0
void VPlanet::FUN_00c713c0(int a) { if (mpPlanet != 0) mpPlanet->fn_00b8dde0(a, 0); }

// @ 0x00c713f0
void VPlanet::FUN_00c713f0()
{
    ((NounMgr*)((PlanetData*)mp68)->fn_00b8de30())->GetAvatar();
}

// @ 0x00c71400
bool VPlanet::FUN_00c71400(int i)
{
    if ((unsigned)i < 5) {
        uint32_t bit = 1u << (i & 0x1f);
        return (mField1BC & bit) != 0;
    }
    return false;
}

// @ 0x00c71430
void VPlanet::FUN_00c71430(int i, char on)
{
    if ((unsigned)i < 5) {
        uint32_t bit = 1u << (i & 0x1f);
        if (on) mField1BC |= bit;
        else    mField1BC &= ~bit;
    }
}

// @ 0x00c71470
int VPlanet::FUN_00c71470()
{
    PlanetData* pd = mpPlanet;
    if (pd != 0 && pd->mField28 == 0) {
        // original returns the raw float bits as int
        float f = 0.0f;
        (void)f;
    }
    float v = 0.0f;
    if ((pd == 0 || pd->mField28 != 0)) {
        void* o;
        if (mp18c != 0 && ((void*(__thiscall*)(void*))(*(void***)mp18c)[0xac / 4])(mp18c) != 0)
            o = mp18c;
        else if (mp188 != 0 && ((void*(__thiscall*)(void*))(*(void***)((char*)mp188 + 0x70))[0xac / 4])((char*)mp188 + 0x70) != 0)
            o = (char*)mp188 + 0x70;
        else return 0;
        void* r = ((void*(__thiscall*)(void*))(*(void***)o)[0xac / 4])(o);
        v = *(float*)((char*)r + 0x18);
    }
    union { float f; int i; } u; u.f = v; return u.i;
}

// @ 0x00c71560
void VPlanet::FUN_00c71560(uint32_t mask) { mpPlanet->mField2C &= mask; }

// @ 0x00c71570
void* VPlanet::FUN_00c71570()
{
    cSpatialObject_ctor_00c89630(this);
    cGameData_ctor_00b18660((char*)this + 0xd4);
    *(void**)this = vtbl_VPlanet_01472480;
    *(void**)((char*)this + 0xd4) = vtbl_VPlanet_gd_01472428;
    *(void**)((char*)this + 0xd8) = vtbl_VPlanet_d8_01472414;
    mpCommon = 0;
    mFieldA6 = 0;
    return this;
}

// @ 0x00c71680
void VPlanet::FUN_00c71680()
{
    void* p = mpCommon;
    if (p != 0) {
        mpCommon = 0;
        ((void(__thiscall*)(void*))(*(void***)p)[0xc0 / 4])(p);
    }
    void* q = mp100;
    if (q != 0) {
        mp100 = 0;
        ((void(__thiscall*)(void*))(*(void***)q)[4 / 4])(q);
    }
    fn_00c8b2e0();
}

// @ 0x00c71750
void VPlanet::FUN_00c71750(PlanetData* p)
{
    PlanetData* old = mpPlanet;
    if (p != old) {
        if (p != 0) p->AddRef();
        mpPlanet = p;
        if (old != 0) old->Release();
    }
    mField140 = (uint32_t)cStarRecordRef_GetCommContext_00ce6950(p);
    bool b = (p->mField2C & 0x21) != 0;
    if (p->fn_00b8dab0() == 5 && b) p->fn_00b8d920(0);
    switch (p->mField28) {
    case 0:
        if (mpPlanet != 0) mpPlanet->mField98 = 1;
    case 1:
        mField184 = 1.0f;
        break;
    case 2: case 3: case 4: case 5:
        mField184 = 5.0f;
        FUN_00b3d3d0_00(p, 0);
        FUN_0103ca40_00(p, 0);
        break;
    }
    int s = p->fn_00b8dab0();
    if (s > 1 && p->fn_00b8dab0() < 6 && p->mp15C == p->mp160 && p->mp170 == p->mp174 && !b)
        FUN_00b96f40_00(p, p->fn_00b8dab0());
    p->fn_00b8d910();
    if (mpPlanet != 0) {
        void* ref = 0;
        PropMgr* pm = PropertyManager_0067de30();
        void* x = p->fn_00b8dad0();
        pm->GetByKey_2c(*(void**)x, 0x34d97fa, &ref);
        if (ref != 0) {
            PropertyT* prop = 0;
            if (((PropertyUser*)ref)->GetProperty_0041ea70(0x58cbb75, prop) && prop->mType == 10)
                mField1C4 = *prop->GetUInt_0041ea00();
            ((RefObj*)ref)->Release();
        }
    }
}

// @ 0x00c71910
void VPlanet::FUN_00c71910()
{
    if (mp154 != 0) FUN_00c7e280_00(this);
    if (mpPlanet != 0) {
        void* ref = 0;
        PropMgr* pm = PropertyManager_0067de30();
        void* x = mpPlanet->fn_00b8dad0();
        pm->GetByKey_2c(*(void**)x, 0x34d97fa, &ref);
        if (ref != 0) {
            PropertyT* prop = 0;
            if (((PropertyUser*)ref)->GetProperty_0041ea70(0x58cbb75, prop) && prop->mType == 10)
                mField1C4 = *prop->GetUInt_0041ea00();
            ((RefObj*)ref)->Release();
        }
    }
}

// @ 0x00c719d0
void VPlanet::FUN_00c719d0(int mode)
{
    int old = (int)mField158;
    if (old == mode) return;
    bool handled = false;
    if (mode == 3) {
        if (old == 2 && mp18c != 0
            && ((void*(__thiscall*)(void*))(*(void***)mp18c)[0xac / 4])(mp18c) != 0) {
            FUN_00571d90_00(((void*(__thiscall*)(void*))(*(void***)mp18c)[0xac / 4])(mp18c));
            handled = true;
        }
    } else if (mode == 2 && old == 3 && mp18c != 0
               && ((void*(__thiscall*)(void*))(*(void***)mp18c)[0xac / 4])(mp18c) != 0) {
        FUN_007d44a0_00(((void*(__thiscall*)(void*))(*(void***)mp18c)[0xac / 4])(mp18c));
        handled = true;
    }
    mField158 = mode;
    mField1BC |= 4;
    if (handled) return;
    if (mode == 0 || mode == 3) {
        if (mp18c != 0) {
            FUN_00b225d0_00(NounManager_00b3d300(), (char*)mp18c + 0xd4);
            if (mp18c != 0) { mp18c = 0; ((void(__thiscall*)(void*))(*(void***)mp18c)[0xc0 / 4])(mp18c); }
        }
    } else if (mp18c == 0) {
        void* m = NounManager_00b3d300();
        FUN_00c70110_00(&mp18c, FUN_00c716d0_00(m));
        ((void(__thiscall*)(void*, int))(*(void***)mp18c)[0x38 / 4])(mp18c, v2c());
        FUN_00c70110_00((char*)this + 0x108, (void*)this);
    }
    if (mode == 1) {
        if (mp188 == 0 && (mpPlanet == 0 || mpPlanet->mField28 != 0)) {
            void* m = NounManager_00b3d300();
            void* r = FUN_00c716f0_00(m);
            FUN_00c3f160_00(r, r);
            float f = mField184 * 5.0f;
            void* a = (void*)v2c();
            FUN_00c3f160_00(a, (void*)(int)f);
            FUN_00c3f1b0_00(0, 50.0f, 3.4e38f);
            float ff = (FUN_00c70880_this(this), 1) ? 0.96f : 0.20f;
            *(float*)((char*)mp188 + 0x240) = ff;
            FUN_00c3f2d0_00(mp188, (char*)this + 0xd4);
        }
    } else {
        if (mp188 != 0) {
            FUN_00b225d0_00(NounManager_00b3d300(), mp188);
            if (mp188 != 0) { mp188 = 0; ((void(__thiscall*)(void*))(*(void***)mp188)[4 / 4])(mp188); }
        }
    }
}
