// Slice s00e972b0: 0x00E972B0..0x00E978E0.  The constructor, the effect-list clear and the
// per-frame "model group impostor" spawner of the creature-camera effects object (the class
// laid out by slice s00e97bf0, vtable 0x01486f04).  A neighbouring slice (s00e97bf0) already
// established the object layout, so it is reused here.
//
//   0x00e972b0 -> a 64-bit id range check: (hi:lo) - 0x5b02bb3 <= 5
//   0x00e972e0 -> cCreatureCameraEffects::cCreatureCameraEffects()
//   0x00e97310 -> cCreatureCameraEffects::ClearEffects(list)
//   0x00e97350 -> cCreatureCameraEffects::AddModelGroupImpostors()  (name coined)
//   0x00e978e0 -> cCreatureCameraEffects::UpdateSelectionEffect()   (name coined)
#include "types.h"

struct cIVisualEffect;

// eastl::vector<EA::AutoRefCount<cIVisualEffect>, sp_vector_allocator>
struct EffectList
{
    cIVisualEffect** mpBegin;      // +0x00
    cIVisualEffect** mpEnd;        // +0x04
    cIVisualEffect** mpCapacity;   // +0x08
    uint32_t         mAllocator;   // +0x0c
    uint32_t         mPad10;       // +0x10
    EffectList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void EraseRange(cIVisualEffect** first, cIVisualEffect** last);   // 0x00533500
};

// EA::AutoRefCount<cIVisualEffect>
struct RefPtr
{
    cIVisualEffect* mp;            // +0x00
    RefPtr() : mp(0) {}
};

struct cIVisualEffect
{
    virtual int  AddRef();         // +0x00
    virtual int  Release();        // +0x04
    virtual void Start(int);       // +0x08
    virtual void Stop(int);        // +0x0c
};

struct cCreature;

// Base of the effects view (ctor at 0x00e92af0).
struct cEffectsViewBase
{
    cEffectsViewBase();            // 0x00e92af0
    virtual void bv0();
    virtual void bv1();
    virtual void bv2();
    virtual void bv3();
    virtual void bv4();
    virtual void bv5();
    virtual void bv6();
    virtual void bv7();
    virtual void bv8();
    virtual void bv9();
    virtual void bv10();
    char mPad04[0x34 - 4];
};

class cCreatureCameraEffects : public cEffectsViewBase
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void* GetModel();                   // +0x2c
    virtual void  OnImpostorAdded(void*, void*);  // +0x30

    cCreature*    mpCreature;      // +0x34
    EffectList    mEffectsA;       // +0x38
    EffectList    mEffectsB;       // +0x4c
    RefPtr        mSelectedEffect; // +0x60
    RefPtr        mHiddenEffect;   // +0x64

    cCreatureCameraEffects();
    void ClearEffects(EffectList* list);
    void AddModelGroupImpostors();      // 0x00e97350
    void UpdateSelectionEffect();       // 0x00e978e0
};

// 0x00e972b0
// @ 0x00e972b0
bool IsIdInRange(uint64_t v)
{
    return v - 0x5b02bb3ULL <= 5;
}

// 0x00e972e0
// @ 0x00e972e0
cCreatureCameraEffects::cCreatureCameraEffects()
    : mpCreature(0)
{
}

// 0x00e97310
// @ 0x00e97310
void cCreatureCameraEffects::ClearEffects(EffectList* list)
{
    for (cIVisualEffect** it = list->mpBegin; it != list->mpEnd; ++it)
    {
        if (*it)
            (*it)->Stop(1);
    }
    list->EraseRange(list->mpBegin, list->mpEnd);
}

// ===========================================================================
// Types and helpers used by the two spawner functions below.  The helpers are
// declared here only; they live in other translation units of the game.
// ===========================================================================

struct cSPVector3 { float x, y, z; };

// A creature's "camera / selection" parameters, pointed at by cCreature::mpInfo.
struct cCreatureInfo
{
    char  mPad00[0xb0];
    float m_fb0;                 // +0xb0
    float m_fb4;                 // +0xb4
};

struct cCreature
{
    char           mPad00[0x13c];
    cCreatureInfo* mpInfo;             // +0x13c
    char           mPad140[0x170 - 0x140];
    void**         mpVec170Begin;      // +0x170
    void**         mpVec170End;        // +0x174
    void**         mpVec170Cap;        // +0x178
    char           mPad17c[0x184 - 0x17c];
    float          m_f184;             // +0x184
    char           mPad188[0x1bc - 0x188];
    unsigned       m_u1bc;             // +0x1bc
};

struct cModelManager
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09();
    virtual unsigned Lookup(unsigned hash, const char* name);      // +0x28
};
cModelManager* ModelManager();                                     // 0x0067dd80

struct cPropertyList
{
    virtual void v00();
    virtual int  Release();                                        // +0x04
};

struct cPropertyManager
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual bool GetPropertyList(unsigned id, unsigned key, cPropertyList** out);  // +0x2c
};
cPropertyManager* PropertyManager();                               // 0x0067de30
bool GetPropertyAsVector3(const cPropertyList*, unsigned, cSPVector3*);  // 0x006a1110

// The effect factory reachable through the effects holder (0x00b3d470).
struct cEffectFactory
{
    virtual void v00();
    virtual void v01();
    virtual bool Create(unsigned id, int zero, void** out);        // +0x08
};

struct cEffectsHolder
{
    char            mPad00[0x9c];
    cEffectFactory* mpFactory;                                     // +0x9c
};
cEffectsHolder* GetEffectsHolder();                                // 0x00b3d470

struct cCreatedEffect
{
    virtual int  AddRef();                                         // +0x00
    virtual int  Release();                                        // +0x04
    virtual void SetEnabled(int);                                  // +0x08
    virtual void v0c(int); virtual void v10(int); virtual void v14(int); virtual void v18(int);
    virtual void v1c(int); virtual void v20(int); virtual void v24(int); virtual void v28(int);
    virtual void v2c(int); virtual void v30(int); virtual void v34(int); virtual void v38(int);
    virtual void v3c(int);
    virtual void Configure(int, const cSPVector3*, int);           // +0x40
};

// The impostor ability object handed back by pAbilityFactory->vtbl0c(x, z, 0).
struct cImpostor
{
    void**         mpVtbl;         // +0x00
    unsigned       m_flags04;      // +0x04
    char           mPad08[0x0a - 8];
    unsigned short m_u0a;          // +0x0a
    char           mPad0c[0x18 - 0x0c];
    float          m_f18;          // +0x18
    char           mPad1c[0x40 - 0x1c];
    int            m_count40;      // +0x40
    unsigned       m_bits44[2];    // +0x44
    char           mPad4c[0x64 - 0x4c];
    void*          m_p64;          // +0x64
};

// The 0x1c-byte cCreatureAbility allocated for each impostor.
struct cCreatureAbility
{
    char      mPad00[0x08];
    unsigned* mpVecBegin;          // +0x08
    unsigned* mpVecEnd;            // +0x0c
    unsigned* mpVecCap;            // +0x10
};
void* cCreatureAbility_Ctor(void*);                                // 0x0077d1d0

// The identity 0x10c-byte map description handed to each impostor.
struct cMapDescription
{
    void**         mpVtbl;         // +0x00
    unsigned short m_u04;          // +0x04
    unsigned short m_u06;          // +0x06
    float*         mpFloats;       // +0x08
    float          m_f00c[16];     // +0x0c
};

struct cAbilityFactory;
cAbilityFactory* FUN_00b3d240();                                   // 0x00b3d240

void* FUN_00b3d360(...);                                           // 0x00b3d360
bool  FUN_00b7d4f0(void*);                                         // 0x00b7d4f0
void  FUN_00b7daf0(void*);                                         // 0x00b7daf0
void  FUN_00b7d440(void*);                                         // 0x00b7d440
void  FUN_00c72450(void*, void*);                                  // 0x00c72450
float* FUN_00c713e0(cCreature*);                                   // 0x00c713e0
void* GetUniverseContext();                                        // 0x01021080
void* EAAllocate(int size, const char* tag, int, int, int, int);   // 0x00f473a0
void  VectorInsertU32(unsigned* end, const unsigned* value);       // 0x004558a0
void  v0a360(void* end, void** value);                             // 0x00a0a360

typedef void* (__thiscall *PF_this_v)(void*);
typedef void* (__thiscall *PF_this_iii)(void*, int, int, int);
typedef void  (__thiscall *PF_this_ppv)(void*, void*, void*, int);
typedef void  (__thiscall *PF_this_pp)(void*, void*, void*);
typedef void  (__thiscall *PF_this_i)(void*, int);

#define VTSLOT(obj, off, type) ((type)(*(void***)(obj))[(off) / 4])

// 0x00e97350
// @ 0x00e97350
// Spawns the two "model group impostor" abilities for the viewed creature -- the
// "Atmosphere" variant and the default variant.  Each is created through the ability
// factory, given a fresh identity MapDescription plus a cCreatureAbility wrapper, and
// then registered with the creature.
void cCreatureCameraEffects::AddModelGroupImpostors()
{
    cModelManager*   pModels  = ModelManager();                              // 0x0067dd80
    cAbilityFactory* pFactory = FUN_00b3d240();                              // 0x00b3d240
    void*            pMgr     = VTSLOT(pFactory, 0x70, PF_this_v)(pFactory); // vtbl + 0x70

    if (GetUniverseContext() != 0)                                           // 0x01021080
    {
        if (!FUN_00b7d4f0(FUN_00b3d360(FUN_00c713e0(mpCreature))))
            FUN_00b7daf0(FUN_00b3d360(mpCreature));
    }

    cSPVector3 vecA = { 0.0f, 0.0f, 0.0f };
    cSPVector3 vecB = { 0.0f, 0.0f, 0.0f };
    float*     pPos = FUN_00c713e0(mpCreature);
    cSPVector3 pos  = { pPos[0], pPos[1], pPos[2] };
    void*      pSetup = FUN_00b3d360(pos, 0, 0, 0, 0, &vecB, &vecA);
    FUN_00b7d440(pSetup);

    cImpostor* pAtmo    = (cImpostor*)VTSLOT(pMgr, 0x0c, PF_this_iii)(pMgr, *(int*)&vecA.x, *(int*)&vecA.z, 0);
    if (pAtmo)
        ++pAtmo->m_count40;
    cImpostor* pDefault = (cImpostor*)VTSLOT(pMgr, 0x0c, PF_this_iii)(pMgr, *(int*)&vecB.x, *(int*)&vecB.z, 0);
    if (pDefault)
        ++pDefault->m_count40;

    if (pAtmo)
    {
        unsigned idx = pModels->Lookup(0x6f06a72e, "ModelGroupImpostorAtmosphere");
        if (idx < 0x40)
            pAtmo->m_bits44[idx >> 5] |= 1u << (idx & 0x1f);
        ++pAtmo->m_u0a;
        pAtmo->m_f18 = mpCreature->m_f184;
        pAtmo->m_flags04 |= 0x12;

        void* pAttach = (mpCreature != 0) ? (void*)((char*)mpCreature + 0xd4) : 0;
        if (pAttach != pAtmo->m_p64)
        {
            if (pAttach)
                VTSLOT(pAttach, 0x00, PF_this_v)(pAttach);
            void* pOld = pAtmo->m_p64;
            pAtmo->m_p64 = pAttach;
            if (pOld)
                VTSLOT(pOld, 0x04, PF_this_v)(pOld);
        }

        cMapDescription* pDesc = (cMapDescription*)EAAllocate(0x10c, "App", 0, 0, 0, 0);
        if (pDesc)
        {
            pDesc->m_u04    = 0x206;
            pDesc->m_u06    = 0x100;
            pDesc->mpVtbl   = (void**)0x1453948;
            pDesc->mpFloats = pDesc->m_f00c;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    pDesc->m_f00c[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
        }

        cCreatureAbility* pAbility = (cCreatureAbility*)EAAllocate(0x1c, "Simulator", 0, 0, 0, 0);
        if (pAbility)
            pAbility = (cCreatureAbility*)cCreatureAbility_Ctor(pAbility);

        unsigned value = (unsigned)pDesc;
        if (pAbility->mpVecEnd < pAbility->mpVecCap)
        {
            unsigned* pSlot = pAbility->mpVecEnd++;
            if (pSlot)
                *pSlot = value;
        }
        else
        {
            VectorInsertU32(pAbility->mpVecEnd, &value);
        }

        VTSLOT(pMgr, 0xa4, PF_this_ppv)(pMgr, pAtmo, pAbility, -1);

        if (mpCreature != 0)
            FUN_00c72450(pAtmo, pMgr);
    }

    if (pDefault)
    {
        unsigned idx = pModels->Lookup(0x1d191e82, "ModelGroupImpostor");
        if (idx < 0x40)
            pDefault->m_bits44[idx >> 5] |= 1u << (idx & 0x1f);
        ++pDefault->m_u0a;
        pDefault->m_f18 = mpCreature->m_f184;
        pDefault->m_flags04 |= 0x12;

        void* pAttach = (mpCreature != 0) ? (void*)((char*)mpCreature + 0xd4) : 0;
        if (pAttach != pDefault->m_p64)
        {
            if (pAttach)
                VTSLOT(pAttach, 0x00, PF_this_v)(pAttach);
            void* pOld = pDefault->m_p64;
            pDefault->m_p64 = pAttach;
            if (pOld)
                VTSLOT(pOld, 0x04, PF_this_v)(pOld);
        }

        cMapDescription* pDesc = (cMapDescription*)EAAllocate(0x10c, "App", 0, 0, 0, 0);
        if (pDesc)
        {
            pDesc->m_u04    = 0x206;
            pDesc->m_u06    = 0x100;
            pDesc->mpVtbl   = (void**)0x1453948;
            pDesc->mpFloats = pDesc->m_f00c;
            for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 4; ++j)
                    pDesc->m_f00c[i * 4 + j] = (i == j) ? 1.0f : 0.0f;
        }

        cCreatureAbility* pAbility = (cCreatureAbility*)EAAllocate(0x1c, "Simulator", 0, 0, 0, 0);
        if (pAbility)
            pAbility = (cCreatureAbility*)cCreatureAbility_Ctor(pAbility);

        unsigned value = (unsigned)pDesc;
        if (pAbility->mpVecEnd < pAbility->mpVecCap)
        {
            unsigned* pSlot = pAbility->mpVecEnd++;
            if (pSlot)
                *pSlot = value;
        }
        else
        {
            VectorInsertU32(pAbility->mpVecEnd, &value);
        }

        VTSLOT(pMgr, 0xa4, PF_this_ppv)(pMgr, pDefault, pAbility, -1);
        VTSLOT(this, 0x30, PF_this_pp)(this, pDefault, pMgr);
        mpCreature->m_u1bc |= 4;

        if (pDefault->m_count40 > 1)
            --pDefault->m_count40;
        else
            VTSLOT(pDefault, 0x170, PF_this_i)(pDefault, (pDefault->m_flags04 >> 31) & 1);
    }

    if (pAtmo)
    {
        if (pAtmo->m_count40 > 1)
            --pAtmo->m_count40;
        else
            VTSLOT(pAtmo, 0x170, PF_this_i)(pAtmo, (pAtmo->m_flags04 >> 31) & 1);
    }
}

// 0x00e978e0
// @ 0x00e978e0
// Picks a creature-selection visual effect from a small table of property vectors (read from
// the creature's property list, with built-in defaults) and plays it.
void cCreatureCameraEffects::UpdateSelectionEffect()
{
    cCreatureInfo* pInfo = mpCreature->mpInfo;

    cSPVector3 v0, v1, v2, v3, v4;
    float c1 = *(float*)0x13f7344;
    v0.x = v0.y = v0.z = c1;
    v1.x = v1.y = v1.z = c1;
    v2.x = v2.y = v2.z = c1;
    v3.x = *(float*)0x141b034;
    v3.y = *(float*)0x14471ec;
    v3.z = *(float*)0x1486f6c;
    v4.x = *(float*)0x13eb8c8;
    v4.y = *(float*)0x1488874;
    v4.z = 0.0f;

    cPropertyList*    props = 0;
    cPropertyManager* pm    = PropertyManager();                            // 0x0067de30
    if (pm->GetPropertyList(0x12e95823, 0x243ad2b, &props))                 // vtbl + 0x2c
    {
        GetPropertyAsVector3(props, 0x60321d8, &v1);                        // 0x006a1110
        GetPropertyAsVector3(props, 0x60321e4, &v2);
        GetPropertyAsVector3(props, 0x60321e7, &v0);
        GetPropertyAsVector3(props, 0x60321e9, &v3);
        GetPropertyAsVector3(props, 0x60321ee, &v4);
    }
    if (props)
        props->Release();

    unsigned id;
    float    f = pInfo->m_fb0;
    if (f <= 0.25f)
        id = 0x6b306eec;
    else if (f < 0.75f)
        id = 0x6b306eeb;
    else
        id = 0x6b306eea;

    cSPVector3 sel = v0;
    float      g   = pInfo->m_fb4;
    if (g <= 0.2f)
        sel = v1;
    else if (g <= 0.4f)
        sel = v2;
    else if (g <= 0.6f)
        sel = v0;
    else if (g <= 0.8f)
        sel = v3;
    else if (g <= 1.0f)
        sel = v4;

    cCreatedEffect* pEffect = 0;
    cEffectsHolder* pHolder = GetEffectsHolder();                           // 0x00b3d470
    if (pHolder->mpFactory->Create(id, 0, (void**)&pEffect))                // vtbl + 0x08
    {
        if (mpCreature->mpVec170End < mpCreature->mpVec170Cap)
        {
            void** pSlot = mpCreature->mpVec170End++;
            if (pSlot)
            {
                *pSlot = pEffect;
                if (pEffect)
                    pEffect->AddRef();
            }
        }
        else
        {
            v0a360(mpCreature->mpVec170End, (void**)&pEffect);              // 0x00a0a360
        }
        pEffect->Configure(5, &sel, 1);                                     // vtbl + 0x40
        pEffect->SetEnabled(0);                                             // vtbl + 0x08
    }
    if (pEffect)
        pEffect->Release();
}
