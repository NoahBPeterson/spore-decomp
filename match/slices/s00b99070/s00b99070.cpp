// 0x00b998a0: creates a new city (cCity) and its owning civilization from a spawn descriptor, then wires it up
// (name, colour, feedback event, terrain orientation, optional tutorial trigger posts) and removes the placeholder
// noun. Names are guesses from the callees; layouts come from the disassembly.
// Flags: /O2 /MD /Gy /GS- /TP /arch:SSE /fp:fast (no EH frame).

#include "types.h"

struct Vec3 { float x, y, z; Vec3() {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct Quat { float x, y, z, w; Quat() {} Quat(const Quat& o) : x(o.x), y(o.y), z(o.z), w(o.w) {} };

void* operator new(size_t n, const char* pName, int a, int b, int c, int d);   // 0x00f473a0
void operator delete[](void* p);

#define PV(n) virtual void s##n();

// ---- eastl::basic_string<wchar_t> (SSO-less shape used by this module) ----
extern wchar_t gEmptyString16[2];   // 0x01667bac
struct String16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    String16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~String16()
    {
        if ((int)((char*)mpCapacity - (char*)mpBegin) >> 1 > 1 && mpBegin)
            operator delete[](mpBegin);
    }
};

struct Ref {
    PV(0)
    virtual void Release();   // slot 1
};

// ---- cSPTransform (see s01315a50) ----
struct Matrix3 {
    float m[3][3];
    Matrix3& Assign(const Matrix3& other);   // 0x0041cb40
};
extern const Vec3 kDefaultOffset;            // 0x01688890
extern const Matrix3 kDefaultRotation;       // 0x01688924
struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vec3 mOffset;
    float mScale;
    Matrix3 mRotation;
    cSPTransform() : mFlags(0), mModificationCount(0), mOffset(kDefaultOffset), mScale(1.0f)
    {
        mRotation.Assign(kDefaultRotation);
    }
    void SetOffset(const Vec3& v) { mOffset = v; mFlags |= 4; mModificationCount++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
};
const Matrix3& Matrix3FromQuaternion(Matrix3* pOut, const Quat* pQuat);   // 0x0059c190 (cdecl)

// ---- action targets / triggers ----
struct cActionTarget {
    char pad[0x20];
    float mRadius;
    char pad2[0xc];
    cActionTarget(void* pObject);                        // 0x00ad7a30
    cActionTarget(const Vec3* pPos, const Quat* pRot);   // 0x00ad79d0
    ~cActionTarget();                                    // 0x00ad7ad0
};
struct cTriggerMgr {
    char pad[0x2c];
    int mMode;
    char pad30[0x148 - 0x30];
    uint32_t mScenarioID;
    void PostAction(uint32_t id, cActionTarget* pTarget, int flags);   // 0x00ae09b0
};
cTriggerMgr* GetTriggerMgr();   // 0x00b3d4d0

struct MessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMessage(uint32_t id, int a, int b);   // 0x14
};
MessageServer* GetMessageServer();   // 0x00883860

// ---- game objects ----
struct SubObj0 {                 // member with a vptr whose slot 0 takes one argument
    virtual void Slot0(const void* pArg);
};
struct SubPos {                  // member at +0x120 of the city: slot 14 sets the position
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual void SetPosition(const Vec3* pPos);
};
struct SubCityHall {             // member at +0x34 of the city hall; slot 12 returns a rotation
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11)
    virtual const Quat* GetRotation();
};
struct cBuilding {
    char pad[0x34];
    SubCityHall mSub34;
};
struct cCityFlags { char pad[0x108]; uint8_t mbFlag; };
struct cIntermediate { char pad[0xbc]; uint32_t mField_bc; uint32_t mField_c0; };
struct cTerrainSphereObj {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
    virtual uint32_t CreateHandle(const cSPTransform* pT, Ref* pRef);   // 0x54
};
struct cPlanetModel {
    char pad[0x24];
    cTerrainSphereObj* mpTerrain;
    Quat BuildSurfaceOrientation(const Vec3& pos, const Quat& q);       // 0x00b7f1f0
};
cPlanetModel* GetPlanetModel();   // 0x00b3d350

struct cCity {
    char pad0[0x34];
    SubObj0 mSub34;
    char pad38[0x120 - 0x38];
    SubPos mSub120;
    char pad124[0x2e8 - 0x124];
    uint32_t mHandle2e8;
    char pad2ec[0x2f0 - 0x2ec];
    cIntermediate* mpIntermediate;
    char pad2f4[0x324 - 0x2f4];
    cCityFlags* mpFlags;
    char pad328[0x51c - 0x328];
    Vec3 mVec51c;
    cBuilding* GetCityHall();                  // 0x00bd9b40
    cIntermediate* GetIntermediate();          // 0x00bd81f0
    void SetPlayerProfile(uint32_t a, int b);  // 0x00be73d0 (ret 8)
    void Setup(const Vec3* pPos, float f, int i, int a, int b, int c, int d, uint32_t e, const Quat* pQuat, bool bf);   // 0x00be8680 (ret 0x28)
    void GetBounds(Vec3* pOut, float* pRadius); // 0x00bd7f70 (ret 8)
};
cCity* CreateCityAt(const Vec3* pPos, void* pOwner);   // 0x00bd9d70 (cdecl)

struct cFeedbackEvent;
struct FeedbackNode { char pad[0x14]; Ref* mpValue; };
struct FeedbackTree {
    char data[0x8a - 0x44];
    struct Iter { FeedbackNode* mpNode; Iter() {} Iter(const Iter& o) : mpNode(o.mpNode) {} };
    Iter find(const uint32_t& key);            // 0x00e5c780
};

struct cSpeciesProfile {
    void GetUiName(String16* pOut);            // 0x004da330 (ret 4)
};
struct NameSlot { uint32_t d; void Set(const String16* pName); };   // 0x00b6f380 (ret 4)
struct cCivilization {
    char pad0[0x34];
    SubObj0 mSub34;
    char pad38[0x3c - 0x38];
    NameSlot mName;
    uint32_t mField40;
    FeedbackTree mFeedback;
    uint8_t mbNeutral;
    char pad8b[0x98 - 0x8b];
    float mTribeRadius;
    char pad9c[0xc4 - 0x9c];
    Vec3 mColor;
    void Init(void* pTribe, int zero, uint32_t id, int bFlag);   // 0x00bf8170 (ret 0x10)
    void SetColor(const Vec3* pColor);                            // 0x00bef8f0
    void AddCity(cCity* pCity);                                   // 0x00bf4370
    void Func_befd80(float f, int i);                             // 0x00befd80
    cSpeciesProfile* GetSpeciesProfile();                         // 0x00bef950
};

struct Noun {
    PV(0) PV(1) PV(2)
    virtual void* Cast(uint32_t typeID);   // slot 3
};
struct cGameNounManager {
    Noun* CreateNoun(uint32_t typeID);           // 0x00b20c60
    cCivilization* GetPlayerCivilization();          // 0x00b25fb0
    void RemoveNoun(void* pNoun);                    // 0x00b225d0
};
cGameNounManager* GetNounManager();   // 0x00b3d300

struct cSPNameGenerator {
    String16 GetName(uint32_t id);    // 0x005ecf80 (sret, ret 8)
};
cSPNameGenerator* GetNameGenerator(); // 0x004010a0

struct cCivModeStrategy {
    struct cHandler* GetHandler();   // 0x00cf7500 (returns [this+0xec])
    void PostFeedback(cCity* pCity, uint32_t a, uint32_t b, const Vec3* pPos, int x, int y, int z);   // 0x00cf9040 (ret 0x1c)
};
struct cHandler {
    void OnCityCreated(cCity* pCity);   // 0x00ce8de0
};
cCivModeStrategy* GetCivModeStrategy();   // 0x00cf74c0

struct Random {
    uint32_t RandomUint32Uniform(uint32_t n);   // 0x00a68fb0 (ret 4)
    double RandomDoubleUniform();               // 0x009360d0
};
extern Random gRandom;           // 0x01601760
extern int gRandMax;             // 0x01688884
extern int gRandMin;             // 0x01688888
extern float gRadiusHi;          // 0x0168887c
extern float gRadiusLo;          // 0x01688880

struct IPropertyManager {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual bool GetProperty(uint32_t a, uint32_t b, Ref** ppOut);   // 0x2c
};
IPropertyManager* GetPropertyManager();   // 0x0067de30

struct SimSingleton {
    SimSingleton();                 // 0x00ae5c30
    void Restart(bool b);           // 0x00ae3230 (ret 4)
    char data[0xc8];
};
extern SimSingleton* gSimSingleton;   // 0x0167a60c

void* FindPlaceholder(uint32_t id);   // 0x00b993c0 (cdecl)
const Vec3* GetCivColor(uint32_t id); // 0x00b6f0c0 (cdecl)
uint32_t MapSomething(uint32_t v);    // 0x00bef920 (cdecl)

struct CityDesc {
    uint32_t mPlaceholderID;       // 0x00
    Vec3 mPosition;                // 0x04
    Quat mRotation;                // 0x10
    char pad20[0x25 - 0x20];
    uint8_t mbNeutral;             // 0x25
    uint8_t mbPlayerCity;          // 0x26
    char pad27[0x28 - 0x27];
    uint32_t mField28;             // 0x28
    char pad2c[0x34 - 0x2c];
    uint32_t mField34;             // 0x34
    char pad38[0x3c - 0x38];
    void* mpTribe;                 // 0x3c
    char pad40[0x44 - 0x40];
    uint32_t mColorID;             // 0x44
    uint32_t mPropertyA;           // 0x48
    char pad4c[0x50 - 0x4c];
    uint32_t mPropertyB;           // 0x50
    void Func_ae42f0(int arg);     // 0x00ae42f0 (this+0x60 tail call)
};

// @ 0x00b998a0
cCity* CreateCity(CityDesc* d)
{
    cGameNounManager* pMgr = GetNounManager();
    Vec3 pos = d->mPosition;
    Quat rot = d->mRotation;
    rot = GetPlanetModel()->BuildSurfaceOrientation(pos, rot);
    d->mRotation = Quat(rot);

    cCity* pCity = CreateCityAt(&pos, 0);
    {
        String16 name = GetNameGenerator()->GetName(0x58f4c251);
        pCity->mSub34.Slot0(name.mpBegin);
    }

    Noun* pNoun = pMgr->CreateNoun(0x18c816a);
    cCivilization* pCiv = pNoun ? (cCivilization*)pNoun->Cast(0x901f1362) : 0;
    GetCivModeStrategy()->PostFeedback(pCity, 0x416ca7fa, 0xaa9a8ed7, &pos, 0, 0, 0);
    pCiv->Init(d->mpTribe, 0, 0x53dbcf2, d->mbPlayerCity);
    pCiv->mbNeutral = d->mbNeutral;
    pCiv->mField40 = d->mColorID;
    pCiv->SetColor(GetCivColor(d->mColorID));

    {
        String16 uiName;
        GetNounManager()->GetPlayerCivilization()->GetSpeciesProfile()->GetUiName(&uiName);
        pCiv->mName.Set(&uiName);
        uint32_t key = 1;
        pCiv->mSub34.Slot0(pCiv->mFeedback.find(key).mpNode->mpValue);
        pCity->SetPlayerProfile(MapSomething(d->mField28), 0);
        pCiv->AddCity(pCity);

        double lo = gRadiusLo;
        double hi = gRadiusHi;
        int variant = gRandom.RandomUint32Uniform(gRandMax - gRandMin + 1) + gRandMin;
        double r = gRandom.RandomDoubleUniform();
        double v = r * (hi - lo) + lo;
        if (v < hi) {
            if (v < lo)
                v = lo;
        } else {
            v = hi;
        }
        pCity->Setup(&pos, (float)v, variant, 0, 0, 0, 0, d->mField34, &rot, false);

        Ref* pRef = 0;
        IPropertyManager* pProps = GetPropertyManager();
        if (pRef) { Ref* p = pRef; pRef = 0; p->Release(); }
        if (pProps->GetProperty(d->mPropertyA, d->mPropertyB, &pRef)) {
            cSPTransform t;
            t.SetOffset(d->mPosition);
            Quat q = d->mRotation;
            Matrix3 m;
            t.SetRotation(Matrix3FromQuaternion(&m, &q));
            pCity->mHandle2e8 = GetPlanetModel()->mpTerrain->CreateHandle(&t, pRef);
            if (pCity->GetIntermediate()) {
                uint32_t h = pCity->mHandle2e8;
                cIntermediate* pI = pCity->GetIntermediate();
                pI->mField_bc = h;
                pI->mField_c0 = 0;
            }
        }
        d->Func_ae42f0(0);

        cTriggerMgr* pTrig = GetTriggerMgr();
        if ((pTrig->mMode == 1 || pTrig->mMode == 2) && GetTriggerMgr()->mScenarioID == 0x2d25aee1) {
            {
                cActionTarget target(&pCity->mSub120);
                GetTriggerMgr()->PostAction(0x9aa7f68f, &target, 0);
            }
            Vec3 cityPos;
            float radius;
            pCity->GetBounds(&cityPos, &radius);
            const Quat* pCityRot = pCity->GetCityHall()->mSub34.GetRotation();
            cActionTarget target2(&cityPos, pCityRot);
            target2.mRadius = radius;
            GetTriggerMgr()->PostAction(0x3f04cafe, &target2, 0);
            MessageServer* pServer = GetMessageServer();
            if (pServer)
                pServer->PostMessage(0x445f729, 0, 0);
        }

        GetNounManager()->RemoveNoun(FindPlaceholder(d->mPlaceholderID));
        if (pCiv->mbNeutral == 0)
            pCiv->Func_befd80(pCiv->mTribeRadius * 4.0f, 0);
        if (GetCivModeStrategy() && GetCivModeStrategy()->GetHandler())
            GetCivModeStrategy()->GetHandler()->OnCityCreated(pCity);
        pCity->mpFlags->mbFlag = 1;
        if (!gSimSingleton)
            gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        gSimSingleton->Restart(true);
        if (pRef)
            pRef->Release();
    }
    return pCity;
}
