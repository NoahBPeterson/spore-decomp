// Slice s00c71bf0: SP::cPlanet / cVisiblePlanet (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast.
#include "types.h"
#include <math.h>
#include <string.h>

struct PlanetData;
struct CPlanet;
struct IntVec2 { int* begin; int* end; int* cap; };
struct MinMax { float mn, mx; };
struct CtorScratch { float f0, f1, f2, f3, f4, f5, f6, f7, f8; };
struct Mat3 { float f0,f1,f2,f3,f4,f5,f6,f7,f8; };
struct Vec3 { float x,y,z; };
struct Quat4 { float x,y,z,w; };
// cSPTransform: retail has the flags pair + translation + scale BELOW the 9-float
// rotation (the Matrix33 ctor is given &mRotation == base+0x14) and is 0x38 bytes.
struct SPTransform {
    uint16_t mFlags;        // +0x00
    uint16_t mModCount;     // +0x02
    Vec3     mTranslation;  // +0x04  (x,y,z)
    float    mScale;        // +0x10
    Mat3     mRotation;     // +0x14  (9 floats, ends at +0x37)
};

struct Ser16 { uint32_t a0,a1,a2,a3,a4,a5,a6,a7,a8,a9,a10,a11,a12,a13,a14,a15; };
struct SerBuf {
    Ser16 s0,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,
          s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31,s32,s33,s34,s35,s36,s37,s38,s39;
    uint32_t tail0,tail1,tail2,tail3,tail4;
};

extern float g_01693efc, g_01693f00, g_01693f04;
extern float g_016944e0;
extern float g_01471064;
extern float g_0147256c;
extern float g_015787fc;
extern void* g_bgSimManager_016dda8c;
extern void* g_dummyMat_016944bc;
extern void* g_dummyVec_015787e4;
extern uint32_t g_016941dc;
extern float g_01578c18;                       // 0x01578c18 kScale

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
    float mB0, mB4, mB8;           // +0xb0, +0xb4, +0xb8
    char pad_c4[0xd0 - 0xbc];      // +0xbc .. +0xcf
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
    char pad_168[0x16c - 0x168];
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
    void  FUN_00c72190(float a);
    bool  FUN_00c72370();
    void  FUN_00c723d0();
    void  FUN_00c72450(int a, int b);
    void* FUN_00c72470(int free);
    void* ctor_00c725a0();
    void  FUN_00c72770(float f);
    void* FUN_00c729b0(void* out, uint32_t* key);
    void  FUN_00c72a10(void* v, uint32_t tail);
    void  FUN_00c72a70(void* pos, void* value);
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
void*  FUN_00453b20_00(void* out, void* vec, float z);
void   FUN_00478db0_00(void* self, void* v);   // 0x00478db0 __thiscall(self, arg)
void   FUN_00c75c30_00();
void*  FUN_01029790_00();
void   FUN_0102f810_00(int a);
void   FUN_0102f810(int a);
void   FUN_0102f8c0_00(int a);
void   FUN_01005c60_00(int a);
void   FUN_00bf6fa0_00(int a);
void*  cSPTransform_BackTransformPoint_004ff6d0(void* t, void* p);
void   FUN_00c70110_00(void* pp, void* v);
void   FUN_00b96f40_00(void* p, int a);
void   WString_Assign_00423650(void* self, void* begin, void* end);  // 0x00423650 __thiscall(self, first, last)
void   cGonzagoTimer_ctor_00b63890(void* p);
void   FUN_00fc20e0(void* out, float a, float b);
void   FUN_00801920_00(void* o);
void*  FUN_004554f0(void* a, void* b, void* c);
void*  FUN_00ba2e50(void* begin, void* end, void* key, int policy);
void   FUN_0102f810v();
void*  FUN_01029900_00();                    // 0x01029900 GetMaxSpicePerColony(this)
void*  FUN_0102fad0_00();                    // 0x0102fad0 GetSpiceProductionMultiplier(this)
void*  FUN_0102fa80_00();                    // 0x0102fa80 GetSpiceProductionHomeworldMultiplier(this)
void*  FUN_0102fb20_00();                    // 0x0102fb20 GetSpiceProductionStorageMultiplier(this)
void*  SpaceGameGet_01002bd0();              // 0x01002bd0
void*  GetCurrentTerrainSphere_00f67d90();   // 0x00f67d90
void   FUN_00692f90_00();                    // 0x00692f90 cVarListSerializer ctor
bool   FUN_00693e10_00();                    // 0x00693e10 cVarListSerializer::Read
void   FUN_00badab0_00();                    // 0x00badab0
void   FUN_00b8e040v();
float  FUN_00fd9410_00();                    // 0x00fd9410 (thiscall 0-stack-arg getter: st0 = *(float*)(this+0x1c))
void   FUN_00ff0350_00();                    // 0x00ff0350 cCityData::AddValue (thiscall, 1 float stack arg)
void*  FUN_00b8de30_00();                    // 0x00b8de30 (thiscall, ecx=planet)
void*  FUN_00b8dab0_00();                    // 0x00b8dab0 (thiscall, ecx=planet)
void*  FUN_00b8dec0_00();                    // 0x00b8dec0 (thiscall, ecx=planet, 1 stack arg)

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

    Mat3 scratch;
    SPTransform tr;
    tr.mFlags = 0;
    tr.mModCount = 0;
    ((void(__thiscall*)(void*, void*))Matrix3_Assign_0041cb40)(&tr.mRotation, &g_dummyMat_016944bc);

    void* q = ((void*(__thiscall*)(void*))(*(void***)active)[0x30 / 4])(active);
    float* m = Matrix3FromQuaternion_0059c190(&scratch, q);

    uint16_t flags = tr.mFlags;
    uint16_t mcount = tr.mModCount;
    memcpy(&tr.mRotation, m, sizeof(Mat3));

    tr.mScale = g_01578c18;
    float* tv = ((float*(__thiscall*)(void*))(*(void***)active)[0x2c / 4])(active);
    tr.mTranslation.x = tv[0];
    tr.mTranslation.y = tv[1];
    tr.mTranslation.z = tv[2];
    tr.mFlags = flags | 6;
    tr.mModCount = mcount + 3;

    Vec3 pt;
    float* mv = ((float*(__thiscall*)(void*))(*(void***)this)[0x2c / 4])(this);
    pt.x = mv[0];
    pt.y = mv[1];
    pt.z = mv[2];
    ((void(__thiscall*)(void*, void*))cSPTransform_BackTransformPoint_004ff6d0)(&tr, &pt);

    *(float*)((char*)out + 0) = pt.x;
    *(float*)((char*)out + 4) = pt.y;
    *(float*)((char*)out + 8) = pt.z;
}

// @ 0x00c71d30
float CPlanet::FUN_00c71d30()
{
    PlanetData* pd = mpPlanet;
    if (pd == 0) return 0.5f;
    float v = pd->mB8;
    if (v >= 0.0f) return v;
    void* o = FUN_00f48a80();
    float local;
    void* r = pd->fn_00b8d8e0(&local);
    ((void(__thiscall*)(void*, void*))(*(void***)o)[2])(o, r);
    return local;
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
float __cdecl FUN_00c71f00(float m, float b, float maxSpice, char hw, char storage, char param7, float param8, int planet, char param10)
{
    void* colony = FUN_01029790_00();
    float cap = (float)((int(__thiscall*)(void*))FUN_01029900_00)(colony);
    void* econ = (void*)((void*(__cdecl*)())FUN_0102f810v)();
    m = ((float(__thiscall*)(void*))FUN_0102fad0_00)(econ) * m * 0.0166666675f;
    if (hw == 0) {
        if (planet > 4) {
            m = (4.5f / (float)planet) * m;
        }
    } else {
        void* e2 = (void*)((void*(__cdecl*)())FUN_0102f810v)();
        m = ((float(__thiscall*)(void*))FUN_0102fa80_00)(e2) * m;
    }
    m = m * maxSpice;
    if (param7 != 0) {
        void* e3 = (void*)((void*(__cdecl*)())FUN_0102f810v)();
        cap = ((float(__thiscall*)(void*))FUN_0102fb20_00)(e3) * cap;
    }
    if (storage != 0) {
        void* sg = SpaceGameGet_01002bd0();
        if ((*(uint32_t*)((char*)sg + 0xc4) & 0x400) != 0) {
            float v = ((float(__thiscall*)(void*, int))FUN_01005c60_00)(SpaceGameGet_01002bd0(), 10);
            m = v * m;
        }
    }
    void* nm = NounManager_00b3d300();
    void* sphere = ((void*(__thiscall*)(void*))GetCurrentTerrainSphere_00f67d90)(nm);
    float t = ((float(__thiscall*)(void*, int))FUN_00c75c30_00)(sphere, 0xcde375c9);
    float result = t * m * param8;
    if (param10 == 0 && (result + b) > cap) {
        result = cap - b;
    }
    return result;
}

// @ 0x00c72030
float __cdecl FUN_00c72030(void* civ)
{
    void* planet = cSPLivingUniverse_GetActivePlanet_01021260();
    void* sortRes = ((void*(__thiscall*)(void*))FUN_00b8de30_00)(*(void**)((char*)planet + 0x13c));
    int arch = ((int(__thiscall*)(void*))FUN_00801920_00)(sortRes);

    int u4;
    switch (arch) {
    case 4: case 10: case 11: u4 = 1; break;
    case 5: case 7: case 8: case 9: u4 = 2; break;
    case 6: case 12: u4 = 0; break;
    default: u4 = 0; break;
    }

    void* tuning = (void*)((void*(__cdecl*)())FUN_0102f810v)();
    float fVar10 = ((float(__thiscall*)(void*, int))FUN_0102f8c0_00)(tuning, u4);

    void* empire = 0;
    int local8 = 0;
    {
        void* mpPlanet = *(void**)((char*)planet + 0x13c);
        if (mpPlanet != 0 && ((int(__thiscall*)(void*))FUN_00b8dab0_00)(mpPlanet) == 5) {
            void* gd = (char*)planet + 0xd4;
            void* u = ((void*(__thiscall*)(void*))(*(void***)gd)[0x13])(gd);
            void* sm = ((void*(__cdecl*)())StarManager_00b3d2a0)();
            empire = ((void*(__thiscall*)(void*, void*))cStarManager_GetEmpireByID_00ba9370)(sm, u);
            if (empire != 0) {
                if (*(void**)((char*)planet + 0x13c) ==
                    ((void*(__thiscall*)(void*))cEmpire_GetHomePlanet_00c31730)(empire)) {
                    void* pe = cSPLivingUniverse_GetPlayerEmpire_01021300();
                    local8 = 1;
                    if (empire != pe) local8 = 0;
                }
            }
        }
    }

    int uStackc = 0;
    if (empire != 0) {
        void* pe = cSPLivingUniverse_GetPlayerEmpire_01021300();
        uStackc = 1;
        if (empire != pe) uStackc = 0;
    }

    int count = 1;
    {
        void* mp = *(void**)((char*)planet + 0x13c);
        if (*(int*)((char*)mp + 0x15c) != *(int*)((char*)mp + 0x160)) {
            void* e = ((void*(__thiscall*)(void*, int))FUN_00b8dec0_00)(mp, 0);
            count = (*(int*)((char*)e + 0x40) - *(int*)((char*)e + 0x3c)) >> 2;
        }
    }

    float mc = ((float(__thiscall*)(void*, int))FUN_00bf6fa0_00)(civ, 0);
    return FUN_00c71f00(mc, 0.0f, 900.0f, (char)local8, (char)uStackc, 0, fVar10, count, 1);
}

// @ 0x00c72190
void CPlanet::FUN_00c72190(float a)
{
    if (mField1B8 != 0) return;

    void* sortRes = mpPlanet->fn_00b8de30();
    int arch = ((int(__thiscall*)(void*))FUN_00801920_00)(sortRes);
    int u4;
    switch (arch) {
    case 4: case 10: case 11: u4 = 1; break;
    case 5: case 7: case 8: case 9: u4 = 2; break;
    case 6: case 12: u4 = 0; break;
    default: u4 = 0; break;
    }

    void* tuning = (void*)((void*(__cdecl*)())FUN_0102f810v)();
    float fVar9 = ((float(__thiscall*)(void*, int))FUN_0102f8c0_00)(tuning, u4);

    int local_1c = 0;
    int uStack_18 = 0;
    {
        PlanetData* mp = mpPlanet;
        if (mp != 0 && mp->fn_00b8dab0() == 5) {
            void* gd = (char*)this + 0xd4;
            void* u = ((void*(__thiscall*)(void*))(*(void***)gd)[0x13])(gd);
            void* sm = ((void*(__cdecl*)())StarManager_00b3d2a0)();
            void* emp = ((void*(__thiscall*)(void*, void*))cStarManager_GetEmpireByID_00ba9370)(sm, u);
            if (emp != 0) {
                if (mpPlanet == ((void*(__thiscall*)(void*))cEmpire_GetHomePlanet_00c31730)(emp)) {
                    PlanetData* mp2 = mpPlanet;
                    local_1c = 1;
                    void* hp = ((void*(__thiscall*)(void*))cEmpire_GetHomePlanet_00c31730)(emp);
                    uStack_18 = 1;
                    if (mp2 != hp) uStack_18 = 0;
                }
            }
        }
    }

    uint8_t uVar2 = (uint8_t)mpPlanet->fn_00b8e040(g_016941dc);

    PlanetData* mp = mpPlanet;
    int iVar4 = (int)((int)mp->mp160 - (int)mp->mp15C) >> 2;
    for (int iStack_20 = 0; iStack_20 < iVar4; ++iStack_20) {
        PlanetData* iVar6 = (PlanetData*)mpPlanet->fn_00b8dec0(iStack_20);
        int iVar8 = (*(int*)((char*)iVar6 + 0x40) - *(int*)((char*)iVar6 + 0x3c)) >> 2;
        for (int iVar7 = 0; iVar7 < iVar8; ++iVar7) {
            void* elem = *(void**)(*(int*)((char*)iVar6 + 0x3c) + iVar7 * 4);
            int iVar1 = *(int*)((char*)elem + 0x2c);
            float fVar10 = ((float(__thiscall*)(void*))FUN_00fd9410_00)(elem);
            fVar10 = FUN_00c71f00((float)iVar1, fVar10, a, (char)uStack_18, (char)local_1c,
                                  (char)uVar2, fVar9, iVar8, 0);
            ((void(__thiscall*)(void*, float))FUN_00ff0350_00)(elem, fVar10);
        }
    }
}

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
        void* inner = *(void**)p;
        ((void(__thiscall*)(void*, void*, int))(*(void***)inner)[0x16c / 4])(inner, p, 0);
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
                void* inner2 = *(void**)p;
                ((void(__thiscall*)(void*, void*, int))(*(void***)inner2)[0x170 / 4])(inner2, p, f);
            }
        }
    }
}

// @ 0x00c72450
void CPlanet::FUN_00c72450(int a, int b)
{
    FUN_00c723d0();
    ((void(__thiscall*)(void*, void*))FUN_00478db0_00)((char*)this + 0x138, (void*)a);
    (void)b;
}

// @ 0x00c72470
void* CPlanet::FUN_00c72470(int free)
{
    *(void**)this = (void*)0x1472480;
    *(void**)((char*)this + 0xd4) = (void*)0x1472428;
    *(void**)((char*)this + 0xd8) = (void*)0x1472414;
    void* q = mpCommon;
    if (q != 0) ((void(__thiscall*)(void*))(*(void***)q)[0xc0 / 4])(q);
    ((void(__thiscall*)(void*))cGameData_dtor_00b184c0)((char*)this + 0xd4);
    ((void(__thiscall*)(void*))FUN_00c8a420_00)(this);
    if (free & 1) operator_delete_00f47380(this);
    return this;
}

// @ 0x00c72540
uint32_t* FUN_00c72540(uint32_t* begin, uint32_t* end, uint32_t* key)
{
    int n = (int)((char*)end - (char*)begin) / 0xb0;
    while (n > 0) {
        int half = n >> 1;
        uint32_t* mid = (uint32_t*)((char*)begin + (size_t)half * 0xb0);
        if (*mid < *(volatile uint32_t*)key) {
            begin = (uint32_t*)((char*)mid + 0xb0);
            n = n - half - 1;
        } else {
            n = half;
        }
    }
    return begin;
}

// @ 0x00c725a0
void* CPlanet::ctor_00c725a0()
{
    char* self = (char*)this;
    ((void(__thiscall*)(void*))cSpatialObject_ctor_00c89630)(self);
    ((void(__thiscall*)(void*))cGameData_ctor_00b18660)(self + 0xd4);
    *(void**)self = (void*)0x14725d8;
    *(void**)(self + 0xd4) = (void*)0x1472580;
    *(void**)(self + 0xd8) = (void*)0x1472570;
    *(uint32_t*)(self + 0x108) = 0;
    CtorScratch local;
    void* m = FUN_00453b20_00(&local, &g_dummyVec_015787e4, 0.0f);
    ((void(__thiscall*)(void*, void*))Matrix3_Assign_0041cb40)(self + 0x10c, m);
    *(uint32_t*)(self + 0x130) = 0;
    *(uint32_t*)(self + 0x134) = 0;
    *(uint32_t*)(self + 0x138) = 0;
    *(uint32_t*)(self + 0x13c) = 0;
    *(uint32_t*)(self + 0x144) = 0;
    *(float*)(self + 0x148) = g_01693efc;
    *(float*)(self + 0x14c) = g_01693f00;
    *(float*)(self + 0x150) = g_01693f04;
    *(uint32_t*)(self + 0x154) = 0;
    *(uint32_t*)(self + 0x158) = 0;
    *(uint32_t*)(self + 0x164) = 0x1667bae;
    *(void**)(self + 0x15c) = (void*)0x1667bac;
    *(void**)(self + 0x160) = (void*)0x1667bac;
    *(uint32_t*)(self + 0x170) = 0;
    *(uint32_t*)(self + 0x174) = 0;
    *(uint32_t*)(self + 0x178) = 0;
    *(float*)(self + 0x184) = 0.0f;
    *(uint32_t*)(self + 0x188) = 0;
    *(uint32_t*)(self + 0x18c) = 0;
    *(uint8_t*)(self + 0x190) = 1;
    ((void(__thiscall*)(void*))cGonzagoTimer_ctor_00b63890)(self + 0x198);
    *(uint8_t*)(self + 0x1b8) = 0;
    *(uint32_t*)(self + 0x1bc) = 0;
    *(uint32_t*)(self + 0x1c0) = 0;
    *(uint8_t*)(self + 0xa6) = 0;
    *(uint32_t*)(self + 0x1c4) = 0xffd3d3d3;
    return self;
}

// @ 0x00c72770
void CPlanet::FUN_00c72770(float f)
{
    PlanetData* pd = mpPlanet;
    if (pd == 0 || pd->mField98 != 0) {
        ((void(__thiscall*)(void*, void*))(*(void***)this)[0x3c / 4])(this, &g_015787fc);
        return;
    }

    float angle = ((f / pd->mA8) * g_016944e0) *
                  (*(float*)((char*)g_bgSimManager_016dda8c + 0x14)) * g_01471064;

    float s = sinf(angle);
    float c = cosf(angle);

    float t1 = pd->m9C * s;
    float t2 = pd->mA0 * s;
    float t3 = pd->mA4 * s;

    float* q = ((float*(__thiscall*)(void*))(*(void***)this)[0x30 / 4])(this);
    float qx = q[0], qy = q[1], qz = q[2], qw = q[3];

    float f10 = (qx * c + qw * t1) + (qz * t2 - qy * t3);
    float fc  = (qy * c + qw * t2) + (qx * t3 - qz * t1);
    float f8  = (qz * c + qw * t3) + (qy * t1 - qx * t2);
    float f4  = qw * c - ((qy * t2 + qz * t3) + qx * t1);

    float r = 1.0f / sqrtf((((f4 * f4 + f10 * f10) + fc * fc) + f8 * f8));

    Quat4 out;
    out.x = r * f10;
    out.y = r * fc;
    out.z = r * f8;
    out.w = r * f4;
    ((void(__thiscall*)(void*, void*))(*(void***)this)[0x3c / 4])(this, &out);
}

// @ 0x00c729b0
void* CPlanet::FUN_00c729b0(void* out, uint32_t* key)
{
    void* begin = *(void**)this;
    void* end = *(void**)((char*)this + 4);
    int policy = (int)*((uint8_t*)this + 0x14);
    void* res = FUN_00ba2e50(begin, end, key, policy);
    if (res != end) {
        uint32_t* r = (uint32_t*)res;
        bool less;
        if (key[0] != r[0]) less = key[0] < r[0];
        else if (key[2] != r[2]) less = key[2] < r[2];
        else less = key[1] < r[1];
        if (!less) {
            *(void**)out = res;
            *(void**)((char*)out + 4) = (char*)res + 0x10;
            return out;
        }
    }
    *(void**)out = res;
    *(void**)((char*)out + 4) = res;
    return out;
}

// @ 0x00c72a10
void CPlanet::FUN_00c72a10(void* v, uint32_t tail)
{
    int* p = (int*)v;
    if (p[0] != p[1]) {
        if (p != (int*)((char*)this + 0x15c))
            ((void(__thiscall*)(void*, void*, void*))WString_Assign_00423650)((char*)this + 0x15c, (void*)p[0], (void*)p[1]);
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
void CPlanet::FUN_00c72a70(void* p2, void* p3)
{
    uint32_t* begin = *(uint32_t**)this;
    uint32_t* end   = *(uint32_t**)((char*)this + 4);
    uint32_t* cap   = *(uint32_t**)((char*)this + 8);
    uint32_t* pos   = (uint32_t*)p2;
    uint32_t* val   = (uint32_t*)p3;

    if (end != cap) {
        uint32_t* v = val;
        if (v >= pos && v < end) v = v + 2;
        if (end != 0) {
            end[0] = end[-2];
            end[1] = end[-1];
        }
        uint32_t* dst = end;
        uint32_t* src = end - 2;
        if (src != pos) {
            do {
                src -= 2; dst -= 2;
                dst[0] = src[0];
                dst[1] = src[1];
            } while (src != pos);
        }
        pos[0] = v[0];
        pos[1] = v[1];
        *(uint32_t**)((char*)this + 4) = end + 2;
        return;
    }

    int n = (int)((char*)end - (char*)begin) / 8;
    int newcap;
    uint32_t* nb;
    if (n == 0) {
        newcap = 1;
        nb = (uint32_t*)operator_new_00f473a0(newcap * 8, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1);
    } else {
        newcap = n * 2;
        nb = newcap != 0 ? (uint32_t*)operator_new_00f473a0(newcap * 8, (const char*)0x13f09b4, 0, 0, 0x13ebb38, 0xd1) : 0;
    }
    uint32_t* mid = (uint32_t*)FUN_004554f0(begin, val, nb);
    if (mid != 0) {
        mid[0] = val[0];
        mid[1] = val[1];
    }
    uint32_t* ne = (uint32_t*)FUN_004554f0(val, end, mid + 2);
    if (begin != 0) operator_delete_00f47380(begin);
    *(uint32_t**)this = nb;
    *(uint32_t**)((char*)this + 4) = ne;
    *(uint32_t**)((char*)this + 8) = (uint32_t*)((char*)nb + (size_t)newcap * 8);
}

// @ 0x00c72b80
bool CPlanet::FUN_00c72b80(void* p)
{
    char* self = (char*)this;
    bool ok;
    if (!((bool(__thiscall*)(void*, void*))cGameData_Read_00b18600)(self + 0xd4, p)) {
        ok = false;
    } else if (!((bool(__thiscall*)(void*, void*))FUN_00c88b00_00)(self, p)) {
        ok = false;
    } else ok = true;

    SerBuf buf;
    ((void(__thiscall*)(void*, void*, void*, int))FUN_00692f90_00)(&buf, self, (void*)0x1578890, 0x1a80d26);

    if (!ok) return false;
    if (!((bool(__thiscall*)(void*, void*))FUN_00693e10_00)(&buf, p)) return false;

    void* sm = ((void*(__cdecl*)())StarManager_00b3d2a0)();
    void* newP = ((void*(__thiscall*)(void*, void*))FUN_00ba6dc0_00)(sm, *(void**)(self + 0x140));
    void* oldP = *(void**)(self + 0x13c);
    if (newP != oldP) {
        if (newP != 0) ((void(__thiscall*)(void*))(*(void***)newP)[0])(newP);
        *(void**)(self + 0x13c) = newP;
        if (oldP != 0) ((void(__thiscall*)(void*))(*(void***)oldP)[1])(oldP);
    }
    void* sm2 = ((void*(__cdecl*)())StarManager_00b3d2a0)();
    ((void(__thiscall*)(void*, void*))FUN_00badab0_00)(sm2, self);
    FUN_00c72a10(self + 0x15c, *(uint32_t*)(self + 0x16c));
    return true;
}
