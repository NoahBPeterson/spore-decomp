// src/game/SPGonzago/SPViewObjectPlanet.cpp -- migrated from slice(s) s00e97bf0, s00e972b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPViewObjectPlanet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00e972b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cIVisualEffect;
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
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
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
struct cSPVector3_s00e9_72b0 { float x, y, z; };
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
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
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
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual bool GetPropertyList(unsigned id, unsigned key, cPropertyList** out);  // +0x2c
};
cPropertyManager* PropertyManager();                               // 0x0067de30
bool GetPropertyAsVector3(const cPropertyList*, unsigned, cSPVector3_s00e9_72b0*);  // 0x006a1110
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
virtual void v0c(int);
virtual void v10(int);
virtual void v14(int);
virtual void v18(int);
virtual void v1c(int);
virtual void v20(int);
virtual void v24(int);
virtual void v28(int);
virtual void v2c(int);
virtual void v30(int);
virtual void v34(int);
virtual void v38(int);
    virtual void v3c(int);
    virtual void Configure(int, const cSPVector3_s00e9_72b0*, int);           // +0x40
};
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
struct cCreatureAbility
{
    char      mPad00[0x08];
    unsigned* mpVecBegin;          // +0x08
    unsigned* mpVecEnd;            // +0x0c
    unsigned* mpVecCap;            // +0x10
};
void* cCreatureAbility_Ctor(void*);                                // 0x0077d1d0
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
// ---- items of slice s00e972b0 end

// ---- items of slice s00e97bf0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float gXformDefaultTranslation[3];                             // 0x016c6344
struct Vector3 { float x, y, z; };
struct Matrix33
{
    float m[9];
    Matrix33() {}
    Matrix33(const Matrix33& o);                     // 0x0041cb40 (Matrix3::Assign, out of line)
};
struct cTransform                   // 0x38
{
    uint16_t mFlags;                // bit 1: rotation, bit 2: translation
    uint16_t mModCount;
    Vector3  mTranslation;          // +0x04
    float    mScale;                // +0x10
    Matrix33 mRotation;             // +0x14
};
struct XformMsg
{
    __declspec(align(16)) uint16_t mFlags;
    uint16_t mModCount;
    Vector3  mTranslation;
    char     mPad[0x34 - 0x10];
    XformMsg();                                      // 0x00434040
    void SetPosition(const Vector3* p);              // 0x00571d40 (name guessed)
};
struct cIVisualEffect_s00e9_7bf0
{
    virtual int  AddRef();
    virtual int  Release();
    virtual void Start(int);                         // +0x08
    virtual void Stop(int);                          // +0x0c
    virtual bool IsActive();                         // +0x10
    virtual void SetTransform(XformMsg* msg);        // +0x14
    virtual void Move(XformMsg* msg);                // +0x18
};
struct RefPtr_s00e9_7bf0
{
    cIVisualEffect_s00e9_7bf0* mp;
    RefPtr_s00e9_7bf0() : mp(0) {}
    ~RefPtr_s00e9_7bf0() { if (mp) mp->Release(); }
    cIVisualEffect_s00e9_7bf0** AsPPTypeParam();                // 0x00a16f40
    void Reset() { cIVisualEffect_s00e9_7bf0* old = mp; if (old) { mp = 0; old->Release(); } }
};
struct cEffectsManager
{
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual bool CreateEffect(uint32_t id, int flags, cIVisualEffect_s00e9_7bf0** out);    // +0x2c
};
struct cEffectsWorld
{
virtual void v0();
virtual void v1();
    virtual bool CreateEffect(uint32_t id, int flags, cIVisualEffect_s00e9_7bf0** out);    // +0x08
};
struct cEffectsHolder_s00e9_7bf0
{
    char           mPad[0x94];
    cEffectsWorld* mpWorld94;                        // +0x94 (name guessed)
    char           mPad98[4];
    cEffectsWorld* mpWorld9c;                        // +0x9c (name guessed)
};
struct cModelBasis { char mPad[8]; void* mpBasis; };
struct cModelBasisRef { cModelBasis* mpBasis; };
struct cModelEntry { char mPad[8]; cModelBasisRef* mpRef; };
struct cModelWorld
{
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
virtual void v35();
virtual void v36();
virtual void v37();
virtual void v38();
virtual void v39();
virtual void v40();
virtual void v41();
    virtual cModelEntry* FindModel(void* model, int flags);                      // +0xa8
};
struct cLookTransform
{
    __declspec(align(16)) char mData[0x38];
    cLookTransform();                                // 0x00409930
    void Orient(const Vector3* dir, const Vector3* up);   // 0x006bac90 (name guessed)
    void Build(void* basis);                         // 0x006b9440 (name guessed)
};
struct cModelInstance                                // model with a transform at +8 (name guessed)
{
    void*      mPad0;
    uint32_t   mFlags;                               // +0x04, bit 0: visible, bit 15: has transform
    cTransform mTransform;                           // +0x08
};
struct cOwner                                        // creature owner (+0x13c of the creature)
{
    bool IsHidden();                                 // 0x00b8d970 (name guessed)
    bool IsAvatarA();                                // 0x00bba100 (name guessed)
    bool IsAvatarB();                                // 0x00bb9d90 (name guessed)
};
struct RefPtr_s00e9_7bf0;
struct EffectList_s00e9_7bf0                                    // eastl::vector<AutoRefCount<cIVisualEffect>>
{
    cIVisualEffect_s00e9_7bf0** mpBegin;
    cIVisualEffect_s00e9_7bf0** mpEnd;
    cIVisualEffect_s00e9_7bf0** mpCapacity;
    uint32_t         mAllocator;
    void push_back(RefPtr_s00e9_7bf0* ref);                     // 0x00a7f430 (name guessed)
};
struct cCreatureExtra { void Scale(const Vector3* pos, float s); };   // 0x00c3f160 (name guessed)
struct cCreature_s00e9_7bf0
{
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual const Vector3* GetPosition();                                         // +0x2c
    virtual const float*   GetOrientation();                                      // +0x30
    char            mPad[0xd4 - 4];
    char            mSub;                                                         // +0xd4
    char            mPad0d5[0x10c - 0xd5];
    Matrix33        mMatrix;                                                      // +0x10c
    char            mPad130[0x13c - 0x130];
    cOwner*         mpOwner;                                                      // +0x13c
    char            mPad140[0x170 - 0x140];
    EffectList_s00e9_7bf0      mEffects;                                                     // +0x170
    char            mPad180[0x184 - 0x180];
    float           mScale;                                                       // +0x184
    cCreatureExtra* mpExtra;                                                      // +0x188

    cModelInstance* GetSecondaryModel();                                          // 0x00c71460 (name guessed)
};
int   __cdecl GetCreatureMode(cCreature_s00e9_7bf0* c);                          // 0x01034680 (name guessed)
float __cdecl GetCreatureDrawScale(int mode, float dist, bool flag);  // 0x01034630 (name guessed)
void  __cdecl Matrix3FromQuaternion(Matrix33* out, const float* q);   // 0x0059c190
void  __cdecl SetModelBasis(cTransform* t, const Matrix33* m);        // 0x0073a850 (name guessed)
bool  __cdecl IsPlayerCreature(cOwner* owner, int empireID);          // 0x00c8b920 (name guessed)
void  __cdecl Vector3_Normalize(Vector3* out, const Vector3* in);     // 0x00436ce0
void  __cdecl EraseEffects(cIVisualEffect_s00e9_7bf0** first, cIVisualEffect_s00e9_7bf0** last, cIVisualEffect_s00e9_7bf0** dest);   // 0x0042f530 (name guessed)
int   __cdecl GetUniverseContext_s00e9_7bf0();                                   // 0x01021080
int   __cdecl GetPlayerEmpireID();                                    // 0x01021090
cEffectsManager* __cdecl GetEffectsManager();                         // 0x0067ddd0
cModelWorld*     __cdecl GetModelWorld();                             // 0x00b3d520
cEffectsHolder_s00e9_7bf0*  __cdecl GetEffectsHolder_s00e9_7bf0();                          // 0x00b3d470
struct cAvatarHolder { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
    virtual void* GetAvatar(); };                                      // +0x30
cAvatarHolder*   __cdecl GetAvatarHolder();                           // 0x00b3d240
struct cViewer { void GetCameraLocationInfo(Vector3* pos, int, int, int); };   // 0x007c3d30
struct cViewerHolder { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual cViewer* GetViewer(); };                                   // +0x1c
struct cApp { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
    virtual cViewerHolder* GetViewerHolder(); };                       // +0x50
cApp* __cdecl GetApp();                                               // 0x0067dd10
extern Matrix33 gIdentityMatrix;                                      // 0x016c6320
class cCreatureCameraEffects_s00e9_7bf0
{
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
    virtual void v10();
    virtual cModelInstance* GetModel();                                           // +0x2c

    char            mPad04[0x34 - 4];
    cCreature_s00e9_7bf0*      mpCreature;                                                   // +0x34
    EffectList_s00e9_7bf0      mEffectsA;                                                    // +0x38
    EffectList_s00e9_7bf0      mEffectsB;                                                    // +0x4c
    char            mPad5c[4];
    RefPtr_s00e9_7bf0          mSelectedEffect;                                              // +0x60
    RefPtr_s00e9_7bf0          mHiddenEffect;                                                // +0x64

    void ClearEffects(EffectList_s00e9_7bf0* list);                                          // 0x00e97310 (name guessed)
    void Update(int, int);                                                        // 0x00e97bf0 (name guessed)
};
static __forceinline void SetModelTransform(cModelInstance* m, const Vector3* pos, const Matrix33& rot, float scale)
{
    cTransform* t = &m->mTransform;
    t->mTranslation = *pos;
    t->mFlags |= 4;
    ++t->mModCount;
    t->mFlags |= 2;
    ++t->mModCount;
    t->mRotation = rot;
    ++t->mModCount;
    t->mScale = scale;
}
static __forceinline void FaceModelOutward(cCreature_s00e9_7bf0* creature, cModelInstance* model)
{
    cModelEntry* entry = GetModelWorld()->FindModel(model, -1);
    if (entry)
    {
        void* basis = entry->mpRef->mpBasis->mpBasis;
        Vector3 dir;
        Vector3_Normalize(&dir, creature->GetPosition());
        cLookTransform xf;
        Vector3 up;
        up.x = 0.0f;
        up.y = 0.0f;
        up.z = 1.0f;
        xf.Orient(&dir, &up);
        xf.Build(basis);
    }
}
struct CreatureOps { void Detach(); };                   // 0x00c723d0 (thiscall, this=creature)
struct EffectListOps { void Clear(); };                  // 0x004b5440 (thiscall, this=EffectList)
struct ViewEffectList
{
    cIVisualEffect_s00e9_7bf0** mpBegin;                        // +0x00
    cIVisualEffect_s00e9_7bf0** mpEnd;                          // +0x04
    cIVisualEffect_s00e9_7bf0** mpCapacity;                     // +0x08
    uint32_t         mAllocator;                     // +0x0c
    uint32_t         mPad10;                         // +0x10
};
struct cSpatialObjectView
{
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
    virtual cModelInstance* GetModel();              // +0x2c
    ~cSpatialObjectView() throw();                   // 0x00e92660
};
class cPlanetGfxView : public cSpatialObjectView
{
public:
    ~cPlanetGfxView() throw();

    char            mPad04[0x34 - 4];                // +0x04
    cCreature_s00e9_7bf0*      mpCreature;                      // +0x34
    ViewEffectList  mEffectsA;                       // +0x38
    ViewEffectList  mEffectsB;                       // +0x4c
    cIVisualEffect_s00e9_7bf0* mpSelected;                      // +0x60
    cIVisualEffect_s00e9_7bf0* mpHidden;                        // +0x64

    void ClearEffects(ViewEffectList* list);         // 0x00e97310
};
// ---- items of slice s00e97bf0 end

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

// @ 0x00e97350
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

    cSPVector3_s00e9_72b0 vecA = { 0.0f, 0.0f, 0.0f };
    cSPVector3_s00e9_72b0 vecB = { 0.0f, 0.0f, 0.0f };
    float*     pPos = FUN_00c713e0(mpCreature);
    cSPVector3_s00e9_72b0 pos  = { pPos[0], pPos[1], pPos[2] };
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

// @ 0x00e978e0
void cCreatureCameraEffects::UpdateSelectionEffect()
{
    cCreatureInfo* pInfo = mpCreature->mpInfo;

    cSPVector3_s00e9_72b0 v0, v1, v2, v3, v4;
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

    cSPVector3_s00e9_72b0 sel = v0;
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

// @ 0x00e97bf0
void cCreatureCameraEffects_s00e9_7bf0::Update(int, int)
{
    cModelInstance* modelA = GetModel();
    cModelInstance* modelB = mpCreature ? mpCreature->GetSecondaryModel() : 0;
    int universeContext = GetUniverseContext_s00e9_7bf0();

    Vector3 camPos;
    cViewer* viewer = GetApp()->GetViewerHolder()->GetViewer();
    viewer->GetCameraLocationInfo(&camPos, 0, 0, 0);
    const Vector3* cp = mpCreature->GetPosition();
    Vector3 delta;
    delta.x = camPos.x - cp->x;
    delta.y = camPos.y - cp->y;
    delta.z = camPos.z - cp->z;
    int mode = GetCreatureMode(mpCreature);
    float distScale = GetCreatureDrawScale(mode, sqrtf((delta.x * delta.x + delta.z * delta.z) + delta.y * delta.y),
                                           GetUniverseContext_s00e9_7bf0() == 0);
    const Vector3* pos = mpCreature->GetPosition();
    Matrix33 quatMatrix;
    Matrix3FromQuaternion(&quatMatrix, mpCreature->GetOrientation());

    Matrix33 rot;
    {
        const float* c = &mpCreature->mMatrix.m[0];
        const float* M = quatMatrix.m;
        float* out = rot.m;
        int n = 3;
        do
        {
            out[0] = (M[3] * c[1] + M[6] * c[2]) + M[0] * c[0];
            out[1] = (M[7] * c[2] + M[1] * c[0]) + M[4] * c[1];
            out[2] = (M[8] * c[2] + M[2] * c[0]) + M[5] * c[1];
            c += 3;
            out += 3;
        } while (--n);
    }

    float scale = mpCreature->mScale * distScale;
    if (mode == 2)
        scale = 15.0f * scale;
    if (mpCreature->mpExtra)
        mpCreature->mpExtra->Scale(pos, scale * (mode == 2 ? 1.5f : 5.0f));

    if (mpCreature->mpOwner->IsHidden())
    {
        if (modelA && (modelA->mFlags & 1))
            modelA->mFlags &= ~1u;
        if (modelB && (modelB->mFlags & 1))
            modelB->mFlags &= ~1u;

        if (!mHiddenEffect.mp)
        {
            cEffectsWorld* world = GetEffectsHolder_s00e9_7bf0()->mpWorld9c;
            mHiddenEffect.Reset();
            if (world->CreateEffect(0x77f5813c, 0, &mHiddenEffect.mp))
                mHiddenEffect.mp->Start(0);
        }
        if (mHiddenEffect.mp)
        {
            cTransform xf;
            xf.mTranslation.x = gXformDefaultTranslation[0];
            xf.mTranslation.y = gXformDefaultTranslation[1];
            xf.mFlags = 0;
            xf.mTranslation.z = gXformDefaultTranslation[2];
            xf.mModCount = 0;
            xf.mScale = 1.0f;
            xf.mRotation = Matrix33(gIdentityMatrix);
            xf.mTranslation = *pos;
            xf.mFlags |= 4;
            ++xf.mModCount;
            ++xf.mModCount;
            xf.mScale = scale;
            mHiddenEffect.mp->Move((XformMsg*)&xf);
        }
        ClearEffects(&mpCreature->mEffects);
        ClearEffects(&mEffectsA);
        ClearEffects(&mEffectsB);
        return;
    }

    if (mHiddenEffect.mp)
    {
        mHiddenEffect.mp->Stop(0);
        mHiddenEffect.Reset();
    }

    if (!(modelA && ((modelA->mFlags >> 15) & 1)))
    {
        if (!modelB || !((modelB->mFlags >> 15) & 1))
            return;
    }

    if (modelA && ((modelA->mFlags >> 15) & 1))
    {
        SetModelTransform(modelA, pos, rot, scale);
        if (universeContext == 0)
            SetModelBasis(&modelA->mTransform, &quatMatrix);
    }
    if (modelB && ((modelB->mFlags >> 15) & 1))
        SetModelTransform(modelB, pos, rot, scale);

    if (IsPlayerCreature(mpCreature->mpOwner, GetPlayerEmpireID()) && GetUniverseContext_s00e9_7bf0() == 1)
    {
        bool have = mSelectedEffect.mp != 0;
        if (!have)
        {
            cEffectsManager* em = GetEffectsManager();
            if (em->CreateEffect(0x69244d69, 0, mSelectedEffect.AsPPTypeParam()))
                mSelectedEffect.mp->Start(0);
            have = mSelectedEffect.mp != 0;
        }
        if (have)
        {
            XformMsg msg;
            msg.SetPosition(mpCreature->GetPosition());
            mSelectedEffect.mp->SetTransform(&msg);
        }
    }
    else if (mSelectedEffect.mp)
    {
        mSelectedEffect.mp->Stop(0);
        mSelectedEffect.Reset();
    }

    if (modelA)
        FaceModelOutward(mpCreature, modelA);
    if (modelB)
        FaceModelOutward(mpCreature, modelB);

    void* avatarSub = mpCreature ? (void*)&mpCreature->mSub : 0;
    EffectList_s00e9_7bf0* active;
    if (GetAvatarHolder()->GetAvatar() == avatarSub)
    {
        ClearEffects(&mEffectsA);
        if (mEffectsB.mpBegin == mEffectsB.mpEnd)
        {
            if (mpCreature->mpOwner->IsAvatarA() || mpCreature->mpOwner->IsAvatarB())
            {
                RefPtr_s00e9_7bf0 ref;
                cEffectsWorld* world = GetEffectsHolder_s00e9_7bf0()->mpWorld94;
                if (world->CreateEffect(0xc22c8057, 0, ref.AsPPTypeParam()))
                {
                    mEffectsB.push_back(&ref);
                    ref.mp->Start(0);
                }
            }
        }
        active = &mEffectsB;
    }
    else
    {
        ClearEffects(&mEffectsB);
        active = &mEffectsA;
    }

    if (active->mpBegin != active->mpEnd)
    {
        XformMsg msg;
        const Vector3* p = mpCreature->GetPosition();
        msg.mTranslation.x = p->x;
        msg.mTranslation.y = p->y;
        msg.mTranslation.z = p->z;
        msg.mFlags |= 4;
        ++msg.mModCount;
        cIVisualEffect_s00e9_7bf0** it = active->mpBegin;
        if (it != active->mpEnd)
        {
            cIVisualEffect_s00e9_7bf0** next = it + 1;
            do
            {
                cIVisualEffect_s00e9_7bf0* e = *it;
                if (e->IsActive())
                {
                    e->Move(&msg);
                    ++it;
                    ++next;
                }
                else
                {
                    if (next < active->mpEnd)
                        EraseEffects(next, active->mpEnd, it);
                    active->mpEnd -= 1;
                    cIVisualEffect_s00e9_7bf0* last = *active->mpEnd;
                    if (last)
                        last->Release();
                }
            } while (it != active->mpEnd);
        }
    }
}

// @ 0x00e98440
cPlanetGfxView::~cPlanetGfxView()
{
    if (mpCreature)
    {
        ClearEffects((ViewEffectList*)&mpCreature->mEffects);
        ((CreatureOps*)mpCreature)->Detach();
    }
    if (mpSelected)
    {
        mpSelected->Stop(1);
        cIVisualEffect_s00e9_7bf0* selected = mpSelected;
        if (selected)
        {
            mpSelected = 0;
            selected->Release();
        }
    }
    if (mpHidden)
    {
        mpHidden->Stop(1);
        cIVisualEffect_s00e9_7bf0* hidden = mpHidden;
        if (hidden)
        {
            mpHidden = 0;
            hidden->Release();
        }
    }
    ClearEffects(&mEffectsA);
    ClearEffects(&mEffectsB);
    if (mpHidden)
        mpHidden->Release();
    if (mpSelected)
        mpSelected->Release();
    ((EffectListOps*)&mEffectsB)->Clear();
    ((EffectListOps*)&mEffectsA)->Clear();
}
