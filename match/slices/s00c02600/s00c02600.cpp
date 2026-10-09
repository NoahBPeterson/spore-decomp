// Slice s00c02600: Simulator::cCreatureBase helpers / near-list predicates (retail).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast (SSE scalar moves; MinF/MaxF/round helpers are __asm).
// Retail layout differs from the 2008 PDB; offsets below come from the disassembly.
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- forward decls
struct CreatureBase;
struct NounManager_t;
struct SpeciesManager;
struct cSPTimer;
struct PropList;
struct Property;
struct ObjA;

extern int   g_0169e370;                          // current brain level
extern char  g_0169e37c;
extern char  g_01654c10, g_01654c05, g_01654c01;
extern char  g_018eb45e;
extern float g_01687a00, g_01687a0c, g_01687a10;
extern float g_01687a20, g_01687a24, g_01687a34, g_01687a38;

// ---------------------------------------------------------------- asm helpers
inline int RoundToInt(float f) { __asm cvtss2si eax, f }
inline float MaxF(float a, float b) { __asm { movss xmm0, a
                                             maxss xmm0, b
                                             movss a, xmm0 } return a; }
inline float MinF(float a, float b) { __asm { movss xmm0, a
                                             minss xmm0, b
                                             movss a, xmm0 } return a; }

// ---------------------------------------------------------------- stub types
struct Vec3 { float x, y, z; };
struct Vec3v {
    float x, y, z;
    Vec3v& operator=(const Vec3v& o) { x = o.x; y = o.y; z = o.z; return *this; }
};

struct PropList {
    virtual void p00(); virtual void p04(); virtual void p08(); virtual void p0c();
    virtual void p10(); virtual void p14(); virtual void p18(); virtual void p1c();
    virtual void p20();
    virtual bool GetProperty_00c033d0(uint32_t id, Property*& prop);   // +0x24
};
struct Property {
    uint32_t mData[4];
    uint8_t  mFlags;      // +0x10
    uint8_t  pad11;
    uint16_t mType;       // +0x12
    float* GetFloat_0041ea70();
};

struct cSPTimer {
    char pad[0x18];
    bool mRunning;             // +0x18
    char pad2[3];
    void* mGetMillisecondTime; // +0x1c
    bool IsRunning_00feba90() { return mRunning; }
    uint64_t GetElapsedTime_00bc3190();
};

struct SpatialObj {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28(); virtual void s2c();
    virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
    virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
    virtual void s50(); virtual void s54();
    virtual bool s58();   // +0x58
};
struct CombatantObj {
    virtual void c00(); virtual void c04(); virtual void c08(); virtual void c0c();
    virtual void c10(); virtual void c14(); virtual void c18(); virtual void c1c();
    virtual void c20(); virtual void c24(); virtual void c28(); virtual void c2c();
    virtual void c30(); virtual void c34(); virtual void c38(); virtual void c3c();
    virtual void c40(); virtual void c44(); virtual void c48(); virtual void c4c();
    virtual void c50(); virtual void c54();
    virtual float GetMaxHitPoints();   // +0x58
    float f_00bfc490();
    void PartialRepair_00bfd1a0(float f);
};

// target object of funcB8h: slot +0xc returns a creature, +0x20 returns a type id.
struct ObjA {
    virtual void a00(); virtual void a04(); virtual void a08();
    virtual CreatureBase* a0c();     // +0xc
    virtual void a10(); virtual void a14(); virtual void a18(); virtual void a1c();
    virtual int a20();               // +0x20
};
struct ObjB { char pad[0x10]; void* field_10; };   // +0x10 holds a pointer
struct FruitRec { char pad[0x10]; void* field_10; };

struct LocationProvider { void* GetLocation_00a42730(); };
struct RandomLCG { uint32_t RandomUint32Uniform_00a68fb0(int); };
extern RandomLCG g_rng_01601760;

struct NounManager_t {
    CreatureBase* GetAvatar_00b1fdb0();
    void RemoveNoun_00b225d0(CreatureBase* obj);
};
struct BehaviorManager_t {
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0c();
    virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28(); virtual void b2c();
    virtual void b30(); virtual void b34();
    virtual void b38(void*);   // +0x38
};
struct MgrB { void f_00b453a0(void*); };
struct TriggerMgr { int f_00ba3f90(uint32_t* key, CreatureBase* a, CreatureBase* b); };
struct T1624 { void f_00bc9de0(int); };
struct ToolMgr_t { bool f_00acd410(CreatureBase* c); };
struct PosseSim { void f_00d52e90(int a, int b); };
struct Strategy_t { void f_00d39360(uint32_t id, void* data); };
struct SpeciesManager {
    void* GetAvatarProfile_004df420();
    void* GetProfile_004df550(uint32_t* key);
    char  f_004df7d0(uint32_t* key, int id, uint32_t* out);
    char  f_004df830(uint32_t* key, void* p, uint32_t* out);
};

// ---------------------------------------------------------------- globals fns
CreatureBase*      GetCurrentGameMode_00b5b800();
NounManager_t*     NounManager_00b3d300();
SpeciesManager*    GetSetting9_00401090();
void*              f_00b3d310();
LocationProvider*  f_00b3d320();
TriggerMgr*        f_00b3d4c0();
void*              f_00b3d4d0();
ToolMgr_t*         f_00b3d480();
BehaviorManager_t* BehaviorManager_00b3d260();
Strategy_t*        cCreatureModeStrategy_Instance_00d38840();
PosseSim*          f_00d539d0();
void __cdecl         f_00ba5df0(uint32_t* key, uint32_t* out);
char __cdecl         SP_GetPropertyAsFloatArray_006a08b0(void* list, uint32_t id, int* count, float** arr);
int  __cdecl         FUN_00c028b0(int* profile, char b);

// ---------------------------------------------------------------- class
struct CreatureBase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  v20(); virtual void v24(); virtual void v28();
    virtual bool v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc(int);
    virtual bool vd0();

    char pad_04[0x84 - 4];
    uint8_t mFlags84;             // +0x84
    char pad_85[0xa9 - 0x85];
    uint8_t mFieldA9;             // +0xa9
    char pad_aa[0xc0 - 0xaa];
    SpatialObj mSpatial;          // +0xc0
    char pad_c4[0x110 - 0xc4];
    uint8_t mFlags110;            // +0x110
    char pad_111[0x135 - 0x111];
    uint8_t mField135;            // +0x135
    char pad_136[0x5a8 - 0x136];
    CombatantObj mCombatant;      // +0x5a8
    char pad_5ac[0xa98 - 0x5ac];
    uint32_t mFlagsA98;           // +0xa98
    char pad_a9c[0xb20 - 0xa9c];
    void* mpSpeciesProfile;       // +0xb20
    char pad_b24[0xb28 - 0xb24];
    uint32_t mKey0B28[3];         // +0xb28
    char pad_b34[0xb4c - 0xb34];
    void* mpFieldB4C;             // +0xb4c
    char pad_b50[0xb54 - 0xb50];
    void* mpFieldB54;             // +0xb54
    uint32_t mGeneralFlags;       // +0xb58
    char pad_b5c[0xb5e - 0xb5c];
    uint8_t mFieldB5E;            // +0xb5e
    char pad_b5f[0xb61 - 0xb5f];
    uint8_t mFieldB61;            // +0xb61
    char pad_b62[0xb63 - 0xb62];
    uint8_t mFieldB63;            // +0xb63
    char pad_b64[0xb67 - 0xb64];
    uint8_t mFieldB67;            // +0xb67
    char pad_b68[0xbbc - 0xb68];
    float mFieldBBC;              // +0xbbc
    char pad_bc0[0xcc0 - 0xbc0];
    int mLastMotiveState;         // +0xcc0
    char pad_cc4[0xe84 - 0xcc4];
    void* mpFieldE84;             // +0xe84
    char pad_e88[0xfb8 - 0xe88];
    uint8_t mFieldFB8;            // +0xfb8
    char pad_fb9[0xfc0 - 0xfb9];
    cSPTimer mHungerTimer;        // +0xfc0
    char pad_fe0[0x1010 - 0xfe0];
    Vec3 mIdentityColor;          // +0x1010
    char pad_101c[0x1624 - 0x101c];
    void* mpField1624;            // +0x1624
    char pad_1628[0x1678 - 0x1628];
    int mField1678;               // +0x1678
    char pad_167c[0x1684 - 0x167c];
    int mField1684;               // +0x1684

    CreatureBase* Cast_00c027d0(int type);
    int  GetCurrentBrainLevel_00c02900();
    void SetCurrentBrainLevel_00c02950(int level);
    void FUN_00c02970(int arg);
    int  FUN_00c029b0();
    char FUN_00c029e0(ObjA* target, int a, int b);
    void FUN_00c02b10(float f);
    void FUN_00c02ba0();
    void FUN_00c02c20(int arg);
    void FUN_00c02c80(float f);
    void FUN_00c02c90();
    void UpdateHunger_00c02cb0(float f);
    void UpdateMotiveState_00c02df0();
    bool FUN_00c02e90();
    bool FUN_00c02eb0(CreatureBase* other);
    char FUN_00c03010();
    void FUN_00c03120(char b);
    uint32_t FUN_00c03190(int a, int b, float c, int d, int e, int f, int g);
    void SetIdentityColor_00c03210(Vec3* c);
    Vec3v* FUN_00c03570(Vec3v* out, char* obj);
    void FUN_00c035b0(int arg);

    void* f_00c0b670(int type);
    void  f_00c0d0c0(int a, int b);
    void  f_00c1cf20();
    void  f_00c43e40(int arg);
    void  f_00c15310(float f);
    void  f_00c0d970(Vec3* c);
    void  UpdateHunger2_00c0d440(float f);
    uint32_t f_00c0bf10(int, int, int, int, float, int, int, int, int, int, int);
    CreatureBase* f_00c0ee90();
    void* GetSpeciesProfile_00c0bbd0();
    void  f_00c12190(uint32_t id, int a, int b);
    bool  f_00c0b780();
    bool  f_00c0bb90();
    float f_00c0b9c0();
    float f_00bfc490();
    void  f_00c0b9a0();
    char  ApplyAttackEffect_00c20230(ObjA* target, int a, int b);
    void  f_00c0b9a0_reset();
    CreatureBase* GetTargetAsCreature_00c0ee70();
};

// ================================================================ definitions

// @ 0x00c02600  SP::IsValidNeighbourEntry
int __stdcall SP_IsValidNeighbourEntry(void* entry)
{
    CreatureBase* c = *(CreatureBase**)((char*)entry + 8);
    if (c->v2c() || (((unsigned char)(c->mGeneralFlags >> 9)) & 1) || c->mField135 == 0 || (c->mFlags110 & 0x10))
        return 0;
    return 1;
}

// @ 0x00c02650
int __stdcall FUN_00c02650(void* entry)
{
    CreatureBase* c = *(CreatureBase**)((char*)entry + 8);
    if (c->v2c() || c->mFieldA9 == 0 || (c->mFlags84 & 0x10))
        return 0;
    return 1;
}

// @ 0x00c02690
void __cdecl FUN_00c02690(float* v)
{
    float x = v[0];
    float y = v[1];
    float z = v[2];
    float inv = 1.0f / sqrtf(z * z + (y * y + x * x) + 1e-8f);
    v[0] = x * inv;
    v[1] = y * inv;
    v[2] = z * inv;
}

// @ 0x00c02710
int __cdecl FUN_00c02710(float f)
{
    float local = f * 0.1f;
    SpeciesManager* m = GetSetting9_00401090();
    void* p = m->GetAvatarProfile_004df420();
    if (p != 0) {
        local = (f - (*(float*)((char*)p + 0x5b0) + *(float*)((char*)p + 0x56c)) * 0.1f) * 0.1f + 5.0f;
    }
    int r = RoundToInt(local);
    if (r < 0) return 0;
    if (r > 10) r = 10;
    return r;
}

// @ 0x00c02790
int __cdecl FUN_00c02790(void* entry)
{
    CreatureBase* c = *(CreatureBase**)((char*)entry + 8);
    if (c->v2c() || (((unsigned char)(c->mGeneralFlags >> 9)) & 1) || c->mField135 == 0 || (c->mFlags110 & 0x10))
        return 1;
    return 0;
}

// @ 0x00c027d0  Object::Cast
CreatureBase* CreatureBase::Cast_00c027d0(int type)
{
    switch (type) {
    case 0x23a7919:
        if (((unsigned char)(mGeneralFlags >> 9)) & 1) return 0;
        if (((unsigned char)(mGeneralFlags >> 8)) & 1) return 0;
        break;
    case (int)0xd0036e08:
        return this;
    case 0x23a6cc8:
        return ((mGeneralFlags >> 9) & 1) ? this : 0;
    case 0x23a6ccd: {
        CreatureBase* r = 0;
        CreatureBase* a = NounManager_00b3d300()->GetAvatar_00b1fdb0();
        if (a != 0 && a->GetTargetAsCreature_00c0ee70() == this && mFieldB5E == 0) r = this;
        return r;
    }
    case 0x23a79d8:
        if (!(((unsigned char)(mGeneralFlags >> 8)) & 1)) return 0;
        break;
    case 0x2785dd8:
        if (((unsigned char)(mGeneralFlags >> 9)) & 1) return 0;
        if (mFieldB5E == 0) return 0;
        return this;
    default:
        return (CreatureBase*)f_00c0b670(type);
    }
    if (mFieldB5E == 0) return this;
    return 0;
}

// @ 0x00c028b0
__declspec(noinline) int __cdecl FUN_00c028b0(int* profile, char b)
{
    int v = *(int*)((char*)profile + 0x57c);
    switch (v) {
    case 0x372e2c04: return 5;
    case 0x9ea3031a: return 3;
    case (int)0xccc35c46:
    case 0x4178b8e8:
    case 0x65672ade:
        return (b != 0) + 5;
    default: return 0;
    }
}

// @ 0x00c02900
int CreatureBase::GetCurrentBrainLevel_00c02900()
{
    if ((void*)GetCurrentGameMode_00b5b800() == (void*)&g_01654c10)
        return FUN_00c028b0((int*)mpSpeciesProfile, (char)((mGeneralFlags >> 9) & 1));
    if ((((unsigned char)(mGeneralFlags >> 9)) & 1) || (((unsigned char)(mGeneralFlags >> 8)) & 1))
        return g_0169e370;
    return 0;
}

// @ 0x00c02950
void CreatureBase::SetCurrentBrainLevel_00c02950(int level)
{
    if (((unsigned char)(mGeneralFlags >> 9)) & 1) g_0169e370 = level;
}

// @ 0x00c02970
void CreatureBase::FUN_00c02970(int arg)
{
    if (((unsigned char)(mFlagsA98 >> 9)) & 1) {
        if (f_00b3d320()->GetLocation_00a42730() == (void*)&g_01654c01) g_0169e37c = 0;
    }
    f_00c43e40(arg);
}

// @ 0x00c029b0
int CreatureBase::FUN_00c029b0()
{
    if (mField1684 == 0)
        mField1684 = g_rng_01601760.RandomUint32Uniform_00a68fb0(3) + 1;
    return mField1684;
}

// @ 0x00c029e0
char CreatureBase::FUN_00c029e0(ObjA* target, int a, int b)
{
    char r = ApplyAttackEffect_00c20230(target, a, b);
    if ((void*)GetCurrentGameMode_00b5b800() == (void*)&g_01654c10) return r;
    CreatureBase* t = target->a0c();
    if (t == 0 || t->v20() != 0x18eb45e) t = 0;
    if (r != 0 && t != 0) {
        bool fire = mSpatial.s58();
        if (!fire) {
            if (f_00b3d4c0()->f_00ba3f90(mKey0B28, 0, 0) == 6) {
                cSPTimer* timer = (cSPTimer*)((char*)t + 0xfe0);
                if (timer->IsRunning_00feba90()) {
                    float secs = (float)timer->GetElapsedTime_00bc3190() * 0.001f;
                    if (secs < 20.0f) fire = true;
                }
            }
        }
        if (fire) {
            void* res = target->a0c();
            uint32_t data[3];
            data[0] = (uint32_t)this;
            data[1] = (uint32_t)res;
            data[2] = 0;
            cCreatureModeStrategy_Instance_00d38840()->f_00d39360(0xd335362c, data);
        }
    }
    return r;
}

// @ 0x00c02b10
void CreatureBase::FUN_00c02b10(float f)
{
    float v = f;
    if (((unsigned char)(mGeneralFlags >> 9)) & 1) {
        float t = 0.25f * f;
        t = MaxF(t, 1.0f);
        v = MinF(t, 5.0f);
    }
    f_00c0bf10(0x1000, 0, 0x1000, 0, v, 0, 0x4000000, 0, 0, 0, 0);
}

// @ 0x00c02ba0
void CreatureBase::FUN_00c02ba0()
{
    f_00c0b9a0();
    if (f_00b3d310() != 0) {
        void* p = (this == 0) ? 0 : (void*)((char*)this + 0xc0);
        ((MgrB*)f_00b3d310())->f_00b453a0(p);
    }
    vcc(0);
    f_00c12190(0x2481de5, 1, -1);
    BehaviorManager_00b3d260()->b38((void*)((char*)this + 0x58));
    ((T1624*)mpField1624)->f_00bc9de0(-1);
    vbc();
}

// @ 0x00c02c20
void CreatureBase::FUN_00c02c20(int arg)
{
    if (((unsigned char)(mGeneralFlags >> 9)) & 1) {
        if (arg > 0) f_00c0d0c0(3, 1);
        else         f_00c0d0c0(3, 0);
        mField1678 = arg;
    } else {
        mField1678 = arg;
    }
}

// @ 0x00c02c80
void CreatureBase::FUN_00c02c80(float f)
{
    f_00c15310(f);
}

// @ 0x00c02c90
void CreatureBase::FUN_00c02c90()
{
    f_00c1cf20();
    mGeneralFlags &= ~8u;
}

// @ 0x00c02cb0
void CreatureBase::UpdateHunger_00c02cb0(float f)
{
    if (mSpatial.s58()) {
        if ((void*)GetCurrentGameMode_00b5b800() == (void*)&g_01654c05) return;
        int s = *(int*)((char*)f_00b3d4d0() + 0x2c);
        if (s == 1) return;
        if (s == 2) return;
    }
    UpdateHunger2_00c0d440(f);
    if (mFieldFB8 != 0) {
        float m = mCombatant.GetMaxHitPoints();
        mCombatant.PartialRepair_00bfd1a0(m * g_01687a24 * f);
    } else if (((unsigned char)(mGeneralFlags >> 9)) & 1) {
        float secs = (float)mHungerTimer.GetElapsedTime_00bc3190() * 0.001f;
        if (secs > g_01687a34) {
            float hp = mCombatant.GetMaxHitPoints() * g_01687a38;
            if (hp > *(float*)((char*)&mCombatant + 0x38)) {
                float hp2 = mCombatant.GetMaxHitPoints() * g_01687a20;
                mCombatant.PartialRepair_00bfd1a0(hp2 * f);
            }
        }
    }
}

// @ 0x00c02df0
void CreatureBase::UpdateMotiveState_00c02df0()
{
    int state;
    if (f_00c0bb90()) {
        if (f_00c0b9c0() < g_01687a10) {
            state = 3;
            goto done;
        }
    }
    if (f_00c0bb90()) {
        state = 5;
    } else {
        if (mCombatant.f_00bfc490() * g_01687a00 < g_01687a0c) {            state = 4;
        } else {
            state = (g_01687a0c > f_00c0b9c0()) ? 2 : 1;
        }
    }
done:
    if (state != mLastMotiveState) {
        mLastMotiveState = state;
        mFieldB61 = 1;
    }
}

// @ 0x00c02e90
bool CreatureBase::FUN_00c02e90()
{
    return (mFlagsA98 & 0x300) != 0;
}

// @ 0x00c02eb0
bool CreatureBase::FUN_00c02eb0(CreatureBase* other)
{
    bool b = f_00c0b780();
    if (!b) return b;
    if (vd0() || (((unsigned char)(mGeneralFlags >> 8)) & 1)) {
        CreatureBase* a = NounManager_00b3d300()->GetAvatar_00b1fdb0();
        if (a != 0 && *(int*)(*(char**)((char*)a + 0xb4c) + 0x1d8) == (int)0x941bd4bf) {
            CreatureBase* t = a->f_00c0ee90();
            if (t != 0 && a->f_00c0ee90()->GetSpeciesProfile_00c0bbd0() == other->GetSpeciesProfile_00c0bbd0())
                return false;
        }
    }
    TriggerMgr* m = f_00b3d4c0();
    if (m != 0)
        return m->f_00ba3f90(mKey0B28, other, this) == 1;
    return mpSpeciesProfile != other->mpSpeciesProfile;
}

// @ 0x00c03010
char CreatureBase::FUN_00c03010()
{
    uint32_t* key = mKey0B28;
    if (key[0] != 0 && GetSetting9_00401090()->GetProfile_004df550(key) == 0) {
        void* p = mpFieldE84;
        uint32_t loc[3];
        loc[0] = 0; loc[1] = 0; loc[2] = 0;
        char r;
        if (p == 0) r = GetSetting9_00401090()->f_004df7d0(key, 0xdada0591, loc);
        else        r = GetSetting9_00401090()->f_004df830(key, p, loc);
        if (r != 0) {
            f_00ba5df0(key, loc);
            key[0] = loc[0]; key[1] = loc[1]; key[2] = loc[2];
        }
        return r;
    }
    return 1;
}

// @ 0x00c03120
void CreatureBase::FUN_00c03120(char b)
{
    mFieldB63 = (b == 0);
    if (b != 0) {
        if (mFieldB67 != 0) {
            if (f_00b3d480()->f_00acd410(this)) return;
        }
        NounManager_00b3d300()->RemoveNoun_00b225d0(this);
    }
}

// @ 0x00c03190
uint32_t CreatureBase::FUN_00c03190(int a, int b, float c, int d, int e, int f, int g)
{
    uint32_t r = f_00c0bf10(a, b, 0x2788b9, 0x40049000, c, 0x100000, 0, d, e, f, g);
    if ((a & 0x70411) | (b & 0x40010)) {
        f_00d539d0()->f_00d52e90(a, b);
    }
    return r;
}

// @ 0x00c03210
void CreatureBase::SetIdentityColor_00c03210(Vec3* c)
{
    f_00c0d970(c);
    int* d = (int*)&mIdentityColor;
    int* s = (int*)c;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
}

// @ 0x00c032c0
int* __cdecl FUN_00c032c0(int* first, int* last, int* out, char (__cdecl* pred)(int))
{
    while (first != last) {
        if (!pred(*first)) { *out = *first; ++out; }
        ++first;
    }
    return out;
}

// @ 0x00c03300   eastl::insertion_sort on pointers-to-float (compare dereferences)
void __cdecl FUN_00c03300(float** first, float** last)
{
    if (first != last) {
        float** iSorted = first;
        for (++iSorted; iSorted != last; ++iSorted) {
            float* temp = *iSorted;
            float** iNext = iSorted;
            float** iCurrent = iSorted;
            for (--iCurrent; (iNext != first) && (*temp < **iCurrent); --iNext, --iCurrent)
                *iNext = *iCurrent;
            *iNext = temp;
        }
    }
}

// @ 0x00c03350   same insertion loop without the lower bound test
void __cdecl FUN_00c03350(float** first, float** last)
{
    for (float** iSorted = first; iSorted != last; ++iSorted) {
        float* value = *iSorted;
        float** end = iSorted;
        float** prev = iSorted;
        for (--prev; *value < **prev; --end, --prev)
            *end = *prev;
        *end = value;
    }
}

// @ 0x00c033d0
float __cdecl FUN_00c033d0(char* obj)
{
    float result = 0.1f;
    if (obj != 0) {
        PropList* list = (PropList*)*(void**)(obj + 0x43c);
        if (list != 0) {
            Property* prop;
            if (list->GetProperty_00c033d0(0xe6f2fce8, prop) && prop->mType == 0xd) {
                float v = *prop->GetFloat_0041ea70();
                result = v;
                if (v < 0.0f) result = 0.1f;
            }
        }
    }
    return result;
}

// @ 0x00c03440
float __cdecl FUN_00c03440(int param)
{
    int n = g_0169e370 * 2 - param;
    float result = 1.0f;
    if (n >= 0) {
        int count = 0;
        float* arr = 0;
        void* list = *(void**)((char*)cCreatureModeStrategy_Instance_00d38840() + 0xb4);
        SP_GetPropertyAsFloatArray_006a08b0(list, 0x3819a4d3, &count, &arr);
        if (count > 0) {
            int idx = (n < count) ? n : count;
            result = arr[idx];
        }
    }
    return result;
}

struct cPred { int Test_00c034d0(FruitRec* r); };

// @ 0x00c034d0  cPred::Test
int cPred::Test_00c034d0(FruitRec* r)
{
    CreatureBase* c = (CreatureBase*)r->field_10;
    if (!c || c->v20() != 0x2c9cc91) c = 0;
    if (c->v2c() || c->mFieldA9 == 0 || (c->mFlags84 & 0x10)) return 0;
    return 1;
}

// @ 0x00c03520
int __stdcall FUN_00c03520(ObjB* obj)
{
    void* p = obj->field_10;
    void* t;
    if (p != 0)
        t = ((void* (__thiscall*)(void*, int)) (*(void***)p)[0x0c / 4])(p, 0x1186577);
    else
        t = 0;
    if (((bool (__thiscall*)(void*)) (*(void***)obj->field_10)[0x2c / 4])(obj->field_10)
        || ((char*)t)[0x75] == 0
        || (((uint8_t*)t)[0x50] & 0x10))
        return 0;
    return 1;
}

// @ 0x00c03570
Vec3v* CreatureBase::FUN_00c03570(Vec3v* out, char* obj)
{
    char* p;
    if (obj != 0) p = obj + 0x34;
    else p = (char*)this + 0x8c;
    void* r = ((void* (__thiscall*)(void*)) (*(void***)p)[0x2c / 4])(p);
    *out = *(Vec3v*)r;
    return out;
}

// @ 0x00c035b0
void CreatureBase::FUN_00c035b0(int)
{
    char* cur = *(char**)((char*)this + 0x18);
    char* node = (char*)this - 0x34;
    if (node != cur) {
        if (node != 0) {
            ((void (__thiscall*)(void*)) (*(void***)node)[0])(node);
        }
        *(char**)((char*)this + 0x18) = node;
        if (cur != 0) {
            ((void (__thiscall*)(void*)) (*(void***)cur)[1])(cur);
        }
    }
}
