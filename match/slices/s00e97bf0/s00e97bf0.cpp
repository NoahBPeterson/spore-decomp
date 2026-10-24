// Slice s00e97bf0: 0x00E97BF0, per-frame update of the effects / models attached to a creature in the
// creature camera view (class name unknown; "cCreatureCameraEffects" is Claude-coined).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc).
//
// Behaviour:
//   * fetch the two attached models (this->vfunc 0x2c, and the creature's secondary model 0x00c71460), the
//     universe context, the camera position and the creature position/orientation; the creature's draw scale is
//     creature+0x184 * (scale function of the camera distance 0x01034630) (times 15 in mode 2);
//     the orientation quaternion is turned into a matrix and multiplied into the creature's matrix (+0x10c);
//   * the creature's extra object (+0x188), if any, gets (position, scale * 1.5 or 5) (0x00c3f160);
//   * hidden creature (0x00b8d970 true): both models lose visibility bit 0, the "hidden" effect (this+0x64,
//     id 0x77f5813c) is created if needed and moved to the creature (identity rotation, scale), and the effect
//     lists (creature+0x170, this+0x38, this+0x4c) are released;
//   * visible creature: the hidden effect is stopped and released; when either model has bit 15 its transform
//     (translation, rotation, scale) is updated; the "selected" effect (this+0x60, id 0x69244d69) lives only
//     for the player's own creature in the living-universe context 1 and follows the creature's position;
//     both models are re-oriented to face away from the origin (position normalised, up (0,0,1));
//     depending on whether this creature is the current avatar the effect list at this+0x38 or this+0x4c is
//     released and the other one is kept alive (the +0x4c list is created with effect 0xc22c8057 when empty and
//     the creature qualifies), and every effect of the active list is moved to the creature position (dead
//     effects are erased from the list).
// NAMING NOTE: no symbol is known for 0x00E97BF0 or its callees; names are Claude-coined from behaviour.
#include "types.h"
#include <math.h>

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

// message object sent to effects (flags/modcount/translation prefix like cTransform)
struct XformMsg
{
    __declspec(align(16)) uint16_t mFlags;
    uint16_t mModCount;
    Vector3  mTranslation;
    char     mPad[0x34 - 0x10];
    XformMsg();                                      // 0x00434040
    void SetPosition(const Vector3* p);              // 0x00571d40 (name guessed)
};

struct cIVisualEffect
{
    virtual int  AddRef();
    virtual int  Release();
    virtual void Start(int);                         // +0x08
    virtual void Stop(int);                          // +0x0c
    virtual bool IsActive();                         // +0x10
    virtual void SetTransform(XformMsg* msg);        // +0x14
    virtual void Move(XformMsg* msg);                // +0x18
};

// EA::AutoRefCount<cIVisualEffect>
struct RefPtr
{
    cIVisualEffect* mp;
    RefPtr() : mp(0) {}
    ~RefPtr() { if (mp) mp->Release(); }
    cIVisualEffect** AsPPTypeParam();                // 0x00a16f40
    void Reset() { cIVisualEffect* old = mp; if (old) { mp = 0; old->Release(); } }
};

struct cEffectsManager
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual bool CreateEffect(uint32_t id, int flags, cIVisualEffect** out);    // +0x2c
};

struct cEffectsWorld
{
    virtual void v0(); virtual void v1();
    virtual bool CreateEffect(uint32_t id, int flags, cIVisualEffect** out);    // +0x08
};

struct cEffectsHolder
{
    char           mPad[0x94];
    cEffectsWorld* mpWorld94;                        // +0x94 (name guessed)
    char           mPad98[4];
    cEffectsWorld* mpWorld9c;                        // +0x9c (name guessed)
};

// basis target of a model (pointer found three levels down from the model world lookup)
struct cModelBasis { char mPad[8]; void* mpBasis; };
struct cModelBasisRef { cModelBasis* mpBasis; };
struct cModelEntry { char mPad[8]; cModelBasisRef* mpRef; };

struct cModelWorld
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34();
    virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41();
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

struct RefPtr;
struct EffectList                                    // eastl::vector<AutoRefCount<cIVisualEffect>>
{
    cIVisualEffect** mpBegin;
    cIVisualEffect** mpEnd;
    cIVisualEffect** mpCapacity;
    uint32_t         mAllocator;
    void push_back(RefPtr* ref);                     // 0x00a7f430 (name guessed)
};

struct cCreatureExtra { void Scale(const Vector3* pos, float s); };   // 0x00c3f160 (name guessed)

struct cCreature
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
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
    EffectList      mEffects;                                                     // +0x170
    char            mPad180[0x184 - 0x180];
    float           mScale;                                                       // +0x184
    cCreatureExtra* mpExtra;                                                      // +0x188

    cModelInstance* GetSecondaryModel();                                          // 0x00c71460 (name guessed)
};

// free helpers (cdecl)
int   __cdecl GetCreatureMode(cCreature* c);                          // 0x01034680 (name guessed)
float __cdecl GetCreatureDrawScale(int mode, float dist, bool flag);  // 0x01034630 (name guessed)
void  __cdecl Matrix3FromQuaternion(Matrix33* out, const float* q);   // 0x0059c190
void  __cdecl SetModelBasis(cTransform* t, const Matrix33* m);        // 0x0073a850 (name guessed)
bool  __cdecl IsPlayerCreature(cOwner* owner, int empireID);          // 0x00c8b920 (name guessed)
void  __cdecl Vector3_Normalize(Vector3* out, const Vector3* in);     // 0x00436ce0
void  __cdecl EraseEffects(cIVisualEffect** first, cIVisualEffect** last, cIVisualEffect** dest);   // 0x0042f530 (name guessed)
int   __cdecl GetUniverseContext();                                   // 0x01021080
int   __cdecl GetPlayerEmpireID();                                    // 0x01021090
cEffectsManager* __cdecl GetEffectsManager();                         // 0x0067ddd0
cModelWorld*     __cdecl GetModelWorld();                             // 0x00b3d520
cEffectsHolder*  __cdecl GetEffectsHolder();                          // 0x00b3d470
struct cAvatarHolder { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void* GetAvatar(); };                                      // +0x30
cAvatarHolder*   __cdecl GetAvatarHolder();                           // 0x00b3d240
struct cViewer { void GetCameraLocationInfo(Vector3* pos, int, int, int); };   // 0x007c3d30
struct cViewerHolder { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual cViewer* GetViewer(); };                                   // +0x1c
struct cApp { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual cViewerHolder* GetViewerHolder(); };                       // +0x50
cApp* __cdecl GetApp();                                               // 0x0067dd10

extern float gXformDefaultTranslation[3];                             // 0x016c6344
extern Matrix33 gIdentityMatrix;                                      // 0x016c6320

class cCreatureCameraEffects
{
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual cModelInstance* GetModel();                                           // +0x2c

    char            mPad04[0x34 - 4];
    cCreature*      mpCreature;                                                   // +0x34
    EffectList      mEffectsA;                                                    // +0x38
    EffectList      mEffectsB;                                                    // +0x4c
    char            mPad5c[4];
    RefPtr          mSelectedEffect;                                              // +0x60
    RefPtr          mHiddenEffect;                                                // +0x64

    void ClearEffects(EffectList* list);                                          // 0x00e97310 (name guessed)
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

static __forceinline void FaceModelOutward(cCreature* creature, cModelInstance* model)
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

// @ 0x00e97bf0
void cCreatureCameraEffects::Update(int, int)
{
    cModelInstance* modelA = GetModel();
    cModelInstance* modelB = mpCreature ? mpCreature->GetSecondaryModel() : 0;
    int universeContext = GetUniverseContext();

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
                                           GetUniverseContext() == 0);
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
            cEffectsWorld* world = GetEffectsHolder()->mpWorld9c;
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

    if (IsPlayerCreature(mpCreature->mpOwner, GetPlayerEmpireID()) && GetUniverseContext() == 1)
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
    EffectList* active;
    if (GetAvatarHolder()->GetAvatar() == avatarSub)
    {
        ClearEffects(&mEffectsA);
        if (mEffectsB.mpBegin == mEffectsB.mpEnd)
        {
            if (mpCreature->mpOwner->IsAvatarA() || mpCreature->mpOwner->IsAvatarB())
            {
                RefPtr ref;
                cEffectsWorld* world = GetEffectsHolder()->mpWorld94;
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
        cIVisualEffect** it = active->mpBegin;
        if (it != active->mpEnd)
        {
            cIVisualEffect** next = it + 1;
            do
            {
                cIVisualEffect* e = *it;
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
                    cIVisualEffect* last = *active->mpEnd;
                    if (last)
                        last->Release();
                }
            } while (it != active->mpEnd);
        }
    }
}

// =====================================================================
// Slice s00e97bf0 (continued): 0x00E98440 (view destructor),
// 0x00E98500 (cSPPlanetGfx::MakeView), 0x00E98A40 (creature-detail
// level from orbit distance), 0x00E98AE0 (sGetClosestDiseasedCreature).
// NAMING NOTE: no symbols are known for these; names are Claude-coined.
// =====================================================================

// --- accessors / helpers used by the four functions below ------------
extern "C" int   __cdecl GetUniverseModeA();                      // 0x01021080 (context; ==1 test)
extern "C" int   __cdecl GetUniverseModeB();                      // 0x01021090
extern "C" void* __cdecl GetActivePlanet();                       // 0x01021260
extern "C" void* __cdecl GetMissionManager();                     // 0x00feb9f0
extern "C" void  __cdecl EffectsInitEmpty(void* out);             // 0x004b5440
extern "C" void* __cdecl PlanetGfxAlloc(uint32_t size, const char* name,
                                        int, int, int, int);      // 0x00f473a0 (operator new)
extern "C" void* __cdecl AxisAngleMatrix(void* out, const void* axis, float a); // 0x00576b00
extern "C" void  __cdecl DtorXformMsg(void* msg);                 // 0x005765e0
extern "C" char  __cdecl GetOrbitPosition(void* orbit, void* out); // 0x00fe88d0 (name guessed)
extern "C" int   __cdecl GetPlanetName(void* out, int x, int y);  // 0x00576b00? (see below)

struct SimPlanet;

// Other classes referenced only by pointer here.
struct cIPlanetOrbit
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual void SetOrbit(void* a, int b);            // +0x40
};

struct SimPlanet
{
    char     mPad00[0x13c];
    void*    mpOwner;                                 // +0x13c (cOwner; name guessed)
    char     mPad140[0x15c - 0x140];
    int32_t  mField15c;                               // +0x15c
    void*    mpField160;                              // +0x160
    char     mPad164[0x16c - 0x164];
    void*    mpField16c;                              // +0x16c
    char     mPad170[0x1bc - 0x170];
    uint32_t mFlags1bc;                               // +0x1bc

    int32_t GetPlanetType();                          // 0x00c70880 (name guessed)
    void*   GetOrbit(uint32_t which);                 // 0x00c708a0 (name guessed)
    void*   GetNameRow(int32_t index);                // 0x00c707f0 (name guessed)
    int32_t GetCreatureField15c() { return mField15c; }
    void*   GetCreatureField160() { return mpField160; }
    void*   GetCreatureField16c() { return mpField16c; }
};

// ---------------------------------------------------------------------
// @ 0x00e98a40
// Creature detail level from the orbit distance: planet+0x540 is the
// current orbit radius, planet+0x508 is the orbit object whose vfunc
// +0x58 yields the reference radius; the ratio selects detail 0..3.
// ---------------------------------------------------------------------
struct SimPlanetOrbitView;

struct IOrbitRadius
{
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual float GetRadius();                        // +0x58
};

extern "C" float gDetailRatioHalf;                    // 0x01471064 (0.5f)
extern "C" float gDetailRatioThird;                   // 0x013ef568 (0.33f)
extern "C" float gDetailRatioFifth;                   // 0x013ec480 (0.2f)

struct SimPlanetOrbitView
{
    char         mPad00[0x508];
    IOrbitRadius mOrbit508;      // +0x508 (embedded object; vtable first)
    char         mPad50c[0x540 - 0x50c];
    float        mOrbitRadius540; // +0x540
};

// @ 0x00e98a40
int __cdecl GetCreatureDetailLevel(SimPlanetOrbitView* planet)
{
    float orbitRadius = planet->mOrbitRadius540;
    float reference = planet->mOrbit508.GetRadius();
    float ratio = orbitRadius / reference;
    if (gDetailRatioHalf <= ratio)
        return 0;
    float r = ratio;
    if (gDetailRatioThird <= r)
        return 1;
    if (r >= gDetailRatioFifth)
        return 2;
    return 3;
}

// --- SP mission objects (0x00E98AE0) ---------------------------------
struct cSPMission;

struct cSPMissionVtbl
{
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void* GetItem(uint32_t key);              // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
    virtual void v56(); virtual void v57(); virtual void v58(); virtual void v59();
    virtual void v60(); virtual void v61();
    virtual bool IsFlagged();                         // +0xf8
};

struct cSPMission : cSPMissionVtbl
{
    void* vfuncF8() { return (void*)(uint32_t)IsFlagged(); }
    bool  IsActive();                                 // 0x00c44c80
    void* GetTargetPlanet();                          // 0x00970b30
    void* GetItemKey(uint32_t key);                   // vtable +0x0c
};

struct MissionList
{
    cSPMission** mpBegin;            // +0x00
    cSPMission** mpEnd;              // +0x04
};

struct cSPMissionManager
{
    MissionList* GetMissionList();                    // 0x00fedd50
};

struct cSPMissionEradicate
{
    uint32_t GetClosestDiseasedAnimal(void* a, void* b);   // 0x00c50300
};

extern "C" void* __cdecl GetMissionMgr();             // 0x00feb9f0
extern "C" uint32_t __cdecl FUN_00c4cb90(void* a, void* b);   // 0x00c4cb90

// @ 0x00e98ae0
char __cdecl sGetClosestDiseasedCreature(void* param_1, void* param_2)
{
    void* activePlanet = GetActivePlanet();
    if (activePlanet == 0)
        return 0;

    void* local_c = 0;
    void* local_8 = 0;

    cSPMissionManager* mgr = (cSPMissionManager*)GetMissionMgr();
    MissionList* list = mgr->GetMissionList();
    int count = (int)(list->mpEnd - list->mpBegin);
    for (int i = 0; i < count; ++i)
    {
        cSPMission* mission = list->mpBegin[i];
        if (mission->IsActive())
        {
            if (!mission->IsFlagged())
            {
                if (mission->GetTargetPlanet() == activePlanet)
                {
                    if (local_c == 0)
                        local_c = mission->GetItemKey(0x2f9998c);
                    if (local_8 == 0)
                        local_8 = mission->GetItemKey(0x437443d);
                }
            }
        }
    }

    if (local_c != 0)
        return ((cSPMissionEradicate*)local_c)->GetClosestDiseasedAnimal(param_1, param_2);
    if (local_8 != 0)
        return FUN_00c4cb90(param_1, param_2);
    return 0;
}

// --- 0x00E98440: destructor of the planet-Gfx spatial view -----------
// Same object layout as the committed 0x00E97BF0 view; modelled with
// raw effect pointers so the explicit Stop/Release sequence is visible.
struct CreatureOps { void Detach(); };                   // 0x00c723d0 (thiscall, this=creature)
struct EffectListOps { void Clear(); };                  // 0x004b5440 (thiscall, this=EffectList)

struct ViewEffectList
{
    cIVisualEffect** mpBegin;                        // +0x00
    cIVisualEffect** mpEnd;                          // +0x04
    cIVisualEffect** mpCapacity;                     // +0x08
    uint32_t         mAllocator;                     // +0x0c
    uint32_t         mPad10;                         // +0x10
};

struct cSpatialObjectView
{
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual cModelInstance* GetModel();              // +0x2c
    ~cSpatialObjectView() throw();                   // 0x00e92660
};

class cPlanetGfxView : public cSpatialObjectView
{
public:
    ~cPlanetGfxView() throw();

    char            mPad04[0x34 - 4];                // +0x04
    cCreature*      mpCreature;                      // +0x34
    ViewEffectList  mEffectsA;                       // +0x38
    ViewEffectList  mEffectsB;                       // +0x4c
    cIVisualEffect* mpSelected;                      // +0x60
    cIVisualEffect* mpHidden;                        // +0x64

    void ClearEffects(ViewEffectList* list);         // 0x00e97310
};

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
        cIVisualEffect* selected = mpSelected;
        if (selected)
        {
            mpSelected = 0;
            selected->Release();
        }
    }
    if (mpHidden)
    {
        mpHidden->Stop(1);
        cIVisualEffect* hidden = mpHidden;
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
