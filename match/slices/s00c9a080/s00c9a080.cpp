// Slice s00c9a080 -- SP::cTribe::Init (spawn a tribe at a position: hut, food mat, tools, members).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (tribe module; no /EHsc; /fp:fast gives the inline fsqrt).
#include "types.h"
#include <math.h>

#define VPAD(n) virtual void vpad##n()

extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
};
struct Quaternion { float x, y, z, w; };
inline Vector3 operator-(const Vector3& v) { return Vector3(-v.x, -v.y, -v.z); }

// --------------------------------------------------------------------- reference counting
struct IRefCounted { virtual void AddRef(); virtual void Release(); };

template <class T> struct AutoRef {
    T* p;
    void Assign(T* n)
    {
        T* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
};

// --------------------------------------------------------------------- property lists
struct Property {
    uint32_t pad0[4];
    uint16_t mFlags;                    // +0x10 (0x30 = data behind a pointer)
    uint16_t mType;                     // +0x12 (0xd float, 0x10 void)
    float* GetValueFloat();
};
extern float kDefaultFloat;             // 0x015d9c6c
inline float* Property::GetValueFloat()
{
    if (mType == 0xd || mType == 0x10) {
        if (mFlags & 0x30)
            return *(float**)this;
        return mType ? (float*)this : 0;
    }
    return &kDefaultFloat;
}
struct PropertyList : IRefCounted {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6);   // +0x08 .. +0x20
    virtual bool GetProperty(uint32_t id, Property*& out);                     // +0x24
};
struct PropManager {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual bool GetPropertyList(uint32_t inst, uint32_t group, AutoRef<PropertyList>& dst);   // +0x2c
};
PropManager* PropertyManager();         // 0x0067de30

// --------------------------------------------------------------------- planet
struct IMapSet { float GetHeightAt(const Vector3* pos); };                     // 0x00f927c0
struct IDistGrid {
    VPAD(0); VPAD(1); VPAD(2);
    virtual IMapSet* GetMapSet();                                              // +0x0c
};
struct cPlanetModel {
    uint32_t pad[0x24 / 4];
    IDistGrid* mpGrid;                                                         // +0x24
    void DirectionToSurfacePosition(Vector3* out, const Vector3* dir);         // 0x00b815a0
    Quaternion BuildSurfaceOrientation(const Vector3& pos);                    // 0x00b7f190
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir);// 0x00b7f250
};
cPlanetModel* PlanetModel();            // 0x00b3d350
struct cModelWorld;
cModelWorld* GonzagoModelWorld();       // 0x00b3d520

// --------------------------------------------------------------------- spatial parts
struct cSpatialPart {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual const Vector3& GetPosition();                                      // +0x2c
    virtual const Quaternion& GetOrientation();                                // +0x30
    VPAD(13);
    virtual void SetPosition(const Vector3& p);                                // +0x38
    virtual void SetOrientation(const Quaternion& q);                          // +0x3c
    VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21);
    virtual bool IsEditor();                                                   // +0x58
};
// hut / food mat sub-object at +0x34
struct cPlacedPart {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13);
    virtual void SetPosition(const Vector3* p);                                // +0x38
    virtual void SetOrientation(const Quaternion* q);                          // +0x3c
    VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20); VPAD(21); VPAD(22);
    virtual Vector3 GetDirection();                                            // +0x5c
    VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30); VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39);
    virtual void SetModelWorld(cModelWorld* w);                                // +0xa0
};

struct cTribe;
struct cTribeNoun : IRefCounted {                                              // hut or food mat
    VPAD(0);                                                                   // +0x08
    virtual void* Cast(uint32_t id);                                           // +0x0c
    uint32_t pad04[(0x34 - 0x4) / 4];
    cPlacedPart mPart;                                                         // +0x34
};
struct cTribeHut : cTribeNoun {
    VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    virtual void SetTribe(cTribe* t);                                          // +0x54
};
struct cTribeFoodMat : cTribeNoun {
    VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10); VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    virtual void SetTribe(cTribe* t);                                          // +0x54
};

struct cTimerLike {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    virtual void SetEnabled(int on);                                           // +0x2c
};
struct BehaviorMgr {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13);
    virtual void Register(void* p);                                            // +0x38
};
BehaviorMgr* BehaviorManager();         // 0x00b3d260

extern const Vector3 kInvalidPos;       // 0x01695374

struct cCitizen : IRefCounted {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18); VPAD(19); VPAD(20);
    VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29); VPAD(30);
    VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39); VPAD(40);
    VPAD(41); VPAD(42); VPAD(43); VPAD(44); VPAD(45); VPAD(46); VPAD(47); VPAD(48); VPAD(49); VPAD(50);
    VPAD(51); VPAD(52); VPAD(53); VPAD(54); VPAD(55); 
    virtual void Init(int a, cTribe* tribe, int b, const Vector3* where);      // +0xe8
};
struct cNounManager { IRefCounted* CreateNoun(uint32_t id); };                  // 0x00b20c60
cNounManager* NounManager();            // 0x00b3d300

struct cSpecies { uint32_t pad[0x608 / 4]; uint32_t mCount608; uint32_t mCount60c; };
inline bool HasA(const cSpecies* s) { return s && s->mCount60c > 0; }
inline bool HasB(const cSpecies* s) { return s && s->mCount608 > 0; }
struct cSpeciesGlobals {
    float GetRadius(cSpecies* s);       // 0x00ce6a40
    int GetPopulation();                // 0x0104bd80
    int GetFood();                      // 0x0104c100
};
extern cSpeciesGlobals g_Species;       // 0x01581208

struct cBundle {                        // cGameBundleContainer at +0x20c
    void Init(cTribe* owner, int type, float cap, float amount, int mode);     // 0x00cee2c0
};
struct cBundleMgr { void Add(float amount, cBundle* b, int type); };           // 0x00ac7ab0
cBundleMgr* BundleManager();            // 0x00b3d2b0

struct cReservationGrid {
    float ComputeGridResolution(float res, float zero);    // 0x00cc7830
};
struct cTimer {
    void Restart();                                        // 0x00bc3130
};

struct IMsgServer {
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4);
    virtual void Post(uint32_t id, void* msg, int flags);                      // +0x14
};
IMsgServer* MessageServer();            // 0x0067dcc0

struct RefBaseA22 {
    virtual void v0();
    volatile long rc;
    RefBaseA22() { _InterlockedExchange(&rc, 0); }
};
struct MsgTribe : RefBaseA22 {
    cTribe* mTribe;                     // +8
    uint32_t pad[9];
    uint32_t mID;                       // +0x30
    uint32_t pad34;
    uint32_t mZero;                     // +0x38
    MsgTribe(cTribe* t) : mID(0x1e8c9e0), mZero(0), mTribe(t) {}
    ~MsgTribe();                        // 0x00421cf0 SlotMessage::Destruct
    virtual void v0();
};

// --------------------------------------------------------------------- the tribe
extern float g_ZoningRadius;            // 0x01581268

struct cIdentity { uint32_t d[12]; void Init(); };                              // 0x00c2e4e0 (cIdentityColorable)
struct cTribe {
    virtual void vp0();
    VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8); VPAD(9); VPAD(10);
    VPAD(11); VPAD(12); VPAD(13); VPAD(14); VPAD(15); VPAD(16); VPAD(17); VPAD(18);
    virtual int GetPoliticalID();                                              // +0x4c
    VPAD(20); VPAD(21); VPAD(22); VPAD(23); VPAD(24); VPAD(25); VPAD(26); VPAD(27); VPAD(28); VPAD(29);
    VPAD(30); VPAD(31); VPAD(32); VPAD(33); VPAD(34); VPAD(35); VPAD(36); VPAD(37); VPAD(38); VPAD(39);
    VPAD(40); VPAD(41);
    virtual void funcA8();                                                     // +0xa8

    uint32_t pad04[(0x38 - 0x4) / 4];
    uint32_t mField38;                                                         // +0x38 (FUN_00ff03b0)
    uint32_t pad3c[(0x6c - 0x3c) / 4];
    uint8_t mFlag6c;                                                           // +0x6c
    uint8_t pad6d[3];
    uint32_t pad70[(0x120 - 0x70) / 4];
    cSpatialPart mSpatial;                                                     // +0x120
    uint32_t pad124[(0x20c - 0x124) / 4];
    cBundle mBundle;                                                           // +0x20c
    uint32_t pad20c[(0x230 - 0x20c - 4) / 4];
    // +0x230: identity sub-object (cIdentityColorable)
    cIdentity mIdentity;                                                       // +0x230
    AutoRef<cTribeFoodMat> mpFoodMat;                                          // +0x260
    uint32_t pad264;
    float mRSquareSize;                                                        // +0x268
    uint32_t pad26c[(0x2d4 - 0x26c) / 4];
    AutoRef<PropertyList> mpPropList;                                          // +0x2d4
    uint32_t pad2d8[(0x2e8 - 0x2d8) / 4];
    Vector3 mCenter;                                                           // +0x2e8
    uint32_t pad2f4[(0x300 - 0x2f4) / 4];
    uint8_t mbCheckedForWater;                                                 // +0x300
    uint8_t pad301[0x2f];
    float mZoningRadius;                                                       // +0x330
    uint8_t mbRoboTribe;                                                       // +0x334
    uint8_t pad335[3];
    uint32_t mRoboPopulationCount;                                             // +0x338
    uint8_t mbVisualized;                                                      // +0x33c
    uint8_t pad33d[3];
    uint32_t pad340[(0x354 - 0x340) / 4];
    int* mSelectableBegin;                                                     // +0x354
    int* mSelectableEnd;                                                       // +0x358
    uint32_t pad35c[(0x368 - 0x35c) / 4];
    AutoRef<cTribeHut> mpHut;                                                  // +0x368
    uint32_t pad36c[(0x510 - 0x36c) / 4];
    cTimer mPopulationTimer;                                                   // +0x510
    uint32_t pad511[(0x550 - 0x514) / 4];
    uint32_t mTribeArchetype;                                                  // +0x550
    uint32_t pad554;
    cReservationGrid mRGrid;                                                   // +0x558
    uint32_t pad55c[(0x18cc - 0x55c) / 4];
    cSpecies* mpSpecies0;                                                      // +0x18cc

    // methods (all thiscall)
    void SetOwner(int a);                                                      // 0x00b18550
    Vector3* GetClosestWater();                                                // 0x00c8fe20
    void UpdateRoboTribeness();                                                // 0x00c8fbb0
    void SetupChatAreas();                                                     // 0x00c95af0
    void UpdateToolPositions();                                                // 0x00c91250
    void ResetToolLayout();                                                    // 0x00c951d0
    void ResetDefaultToolPlacement(int n);                                     // 0x00c8f770
    int GetMaxPopulation();                                                    // 0x00c8eae0
    void ChooseNewHutModel();                                                  // 0x00c99c30
    void ReserveToolsSlots(int n);                                             // 0x00c998c0
    void UpgradeHut();                                                         // 0x00c919e0
    void UpdateModel();                                                        // 0x00c91a40
    void FUN_00c91700();                                                       // 0x00c91700
    void AddExistingCreatureInternal(cCitizen* c, int flag);                   // 0x00c95d70
    void FUN_00ff03b0(int v);                                                  // 0x00ff03b0

    void Init(const Vector3* pos, int numMembers, int foodAmount, bool flag);
};
int FUN_00c00aa0(int n);                // 0x00c00aa0 (cdecl)

// @ 0x00c9a100  SP::cTribe::Init
void cTribe::Init(const Vector3* pos, int numMembers, int foodAmount, bool flag)
{
    SetOwner(0);
    mIdentity.Init();
    mZoningRadius = g_ZoningRadius;
    PlanetModel()->mpGrid->GetMapSet()->GetHeightAt(pos);
    Vector3 surfPos;
    PlanetModel()->DirectionToSurfacePosition(&surfPos, pos);
    cSpatialPart* sp = &mSpatial;
    sp->SetPosition(surfPos);
    Quaternion orient;
    if (sp->IsEditor()) {
        const Vector3* w = GetClosestWater();
        if (w->x == kInvalidPos.x && w->y == kInvalidPos.y && w->z == kInvalidPos.z) {
            orient = PlanetModel()->BuildSurfaceOrientation(surfPos);
        } else {
            const Vector3& c = sp->GetPosition();
            Vector3 d(w->x - c.x, w->y - c.y, w->z - c.z);
            float inv = 1.0f / sqrtf(d.x * d.x + d.y * d.y + d.z * d.z + 1e-8f);
            Vector3 dir(d.x * inv, d.y * inv, d.z * inv);
            orient = PlanetModel()->BuildSurfaceOrientation(surfPos, dir);
            mbCheckedForWater = 0;
        }
    } else {
        orient = PlanetModel()->BuildSurfaceOrientation(surfPos);
    }
    sp->SetOrientation(orient);
    UpdateRoboTribeness();
    if (GetPoliticalID() == -1)
        funcA8();
    mpHut.Assign((cTribeHut*)NounManager()->CreateNoun(0x1e4daae));
    {
        cTribeHut* hut = mpHut.p;
        hut->mPart.SetModelWorld(GonzagoModelWorld());
        hut->SetTribe(this);
        hut = mpHut.p;
        hut->mPart.SetOrientation(&sp->GetOrientation());
        hut = mpHut.p;
        hut->mPart.SetPosition(&sp->GetPosition());
        (void)sp->GetPosition();
    }
    PropManager* pm = PropertyManager();
    if (mpPropList.p) {
        PropertyList* old = mpPropList.p;
        mpPropList.p = 0;
        old->Release();
    }
    pm->GetPropertyList(0x535dc193, 0x2be764e2, mpPropList);
    SetupChatAreas();
    UpdateToolPositions();
    mFlag6c = 1;
    float scale = g_Species.GetRadius(mpSpecies0);
    float base;
    Property* prop;
    if (mpPropList.p && mpPropList.p->GetProperty(0x1fb2b4e, prop))
        base = *prop->GetValueFloat();
    else
        base = 1.5f;
    float r = base * scale * 2.0f;
    mRSquareSize = r;
    mRGrid.ComputeGridResolution(r, 0.0f);
    mPopulationTimer.Restart();
    Vector3 center = mCenter;
    {
        cTribeFoodMat* fm = (cTribeFoodMat*)0;
        IRefCounted* n = NounManager()->CreateNoun(0x629bafe);
        if (n) fm = (cTribeFoodMat*)((cTribeNoun*)n)->Cast(0x629baec);
        mpFoodMat.Assign(fm);
    }
    mpFoodMat.p->SetTribe(this);
    mpFoodMat.p->mPart.SetPosition(&center);
    {
        Vector3 nd = -mpHut.p->mPart.GetDirection();
        Quaternion q = PlanetModel()->BuildSurfaceOrientation(center, nd);
        mpFoodMat.p->mPart.SetOrientation(&q);
    }
    ResetToolLayout();
    ResetDefaultToolPlacement(10);
    if (!sp->IsEditor()) {
        int n = mTribeArchetype ? GetMaxPopulation() : numMembers;
        FUN_00ff03b0(FUN_00c00aa0(n));
    }
    ChooseNewHutModel();
    ReserveToolsSlots(1);
    if (!sp->IsEditor()) {
        int n = mTribeArchetype ? GetMaxPopulation() : numMembers;
        FUN_00ff03b0(FUN_00c00aa0(n));
        UpgradeHut();
    }
    UpdateModel();
    if (flag)
        FUN_00c91700();
    if (numMembers == 0x29a)
        numMembers = g_Species.GetPopulation();
    UpdateRoboTribeness();
    if (mbRoboTribe) {
        mRoboPopulationCount = numMembers;
    } else {
        int have = mSelectableEnd - mSelectableBegin;
        if (have < numMembers) {
            int n = numMembers - have;
            do {
                cCitizen* c;
                if (mbRoboTribe && !mbVisualized) {
                    c = 0;
                } else {
                    c = (cCitizen*)NounManager()->CreateNoun(0x18eb4b7);
                    c->Init(0, this, 1, &kInvalidPos);
                    ((cTimerLike*)((char*)c + 0x5a8))->SetEnabled(1);
                    BehaviorManager()->Register((char*)c + 0x58);
                }
                AddExistingCreatureInternal(c, 0);
            } while (--n);
        }
    }
    if (foodAmount == 0x29a)
        foodAmount = g_Species.GetFood();
    int mode;
    cSpecies* spc = mpSpecies0;
    if (spc && HasA(spc) && !HasB(spc)) mode = 1;
    else if (spc && HasB(spc) && !HasA(spc)) mode = 2;
    else mode = 3;
    float f = (float)foodAmount;
    mBundle.Init(this, 8, 1000.0f, f * 0.85f, mode);
    BundleManager()->Add(f * 0.15f, &mBundle, 4);
    MsgTribe msg(this);
    MessageServer()->Post(msg.mID, &msg, 0);
}
