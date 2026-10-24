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
    uint32_t GetContinent(const Vec3* pPos);                            // 0x00b88590
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
struct cSpeciesMgr {
    cSpeciesProfile* GetAvatarProfile();       // 0x004df420
};
cSpeciesMgr* FUN_00401090();                   // 0x00401090
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

// ---- shared noun data used by the city-spawn helpers (gold7 slice) ----
// The allocator field occupies +0x00; the vector fields live in a member at +0x04 (hence the
// `add eax,4` MSVC emits when the code takes the address of that member).
struct GameDataVectorCore {
    void**  mpBegin;            // +0x00 (object +0x04)
    void**  mpEnd;              // +0x04 (object +0x08)
    void**  mpEndCap;           // +0x08 (object +0x0c)
};
struct GameDataVec {
    void*                mpAllocator;   // +0x00
    GameDataVectorCore   mVec;          // +0x04
    void*                mpField10;     // +0x10
};

struct SubObj34 {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    virtual const Vec3* GetPosition();   // +0x2c
    virtual const Quat* GetRotation();   // +0x30
};

struct NounData {
    char     pad00[0x24];
    uint32_t mId24;              // +0x024
    char     pad28[0x34 - 0x28];
    SubObj34 mSub34;             // +0x034
    char     pad38[0xa9 - 0x38];
    uint8_t  mbFlagA9;           // +0x0a9
    char     padAA[0x108 - 0xaa];
    uint32_t mType108;           // +0x108
    void*    mpField10c;         // +0x10c
    uint32_t mSubtype110;        // +0x110
    Vec3     mVec114;            // +0x114
    char     pad120[0x1a4 - 0x120];
    void*    mpNoun1a4;          // +0x1a4
    Vec3     mVec1a8;            // +0x1a8
    Quat     mQuat1b4;           // +0x1b4
    uint8_t  mbFlag1c4;          // +0x1c4
};

struct cHerd {
    char  pad00[0xa4];
    void* mpProfileKeyA4;        // +0x0a4
    void* mpBeginA8;             // +0x0a8
    void* mpEndAc;               // +0x0ac
    void* GetProfileForGeneration(uint32_t gen);   // 0x00c6abf0
};

struct ProfileHolder {
    char     pad00[0x504];
    uint32_t mKey;               // +0x504
};

struct ObjectTemplateDB {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
    PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void* RegisterProfile(uint32_t* pKey, int zero);   // +0x58
};
ObjectTemplateDB* GetObjectTemplateDB();   // 0x0067cb40

struct cNearNoun {
    const Vec3* GetPosition();   // 0x00c6acc0
};

struct SimAllocHeader { uint32_t mSize; };
inline void FreeBuffer(uint32_t* p)
{
    if (p && ((SimAllocHeader*)p)[-1].mSize)
        operator delete[](p);
}

struct SPVectorU {
    uint32_t* mpBegin;           // +0x00
    uint32_t* mpEnd;             // +0x04
    uint32_t* mpEndCap;          // +0x08
    uint32_t  mField0c;          // +0x0c
    uint32_t  mField10;          // +0x10
    uint32_t  mField14;          // +0x14
    uint32_t  mBuffer[32];       // +0x18
    void DoInsertKey4(uint32_t* pos, const uint32_t* pValue);   // 0x00b96600
};

struct cDirectPropertyList {
    int GetIntProperty(uint32_t id);   // 0x006a2660
};
extern cDirectPropertyList* gAppProperties;   // 0x015fd918

struct PtrRange { void** mpBegin; void** mpEnd; };
void FUN_00b93c60(PtrRange* self, int count, void* pAlloc);                                   // 0x00b93c60
void FUN_00829110(PtrRange* pOut, void** first, void** last, void** a, void** b);             // 0x00829110
uint32_t* FUN_00b90960(uint32_t* begin, uint32_t* end, uint32_t key);                         // 0x00b90960
uint32_t* FUN_00b909a0(uint32_t* p, uint32_t* end, uint32_t* q, uint32_t key);                // 0x00b909a0
void FUN_00d1bef0(int idx);                                                                   // 0x00d1bef0
void* FUN_00b94150(const Vec3* pPos, uint32_t a, uint8_t b, int c);                           // 0x00b94150
void FUN_00ae38f0(void* pEntry);                                                              // 0x00ae38f0
void FUN_00cd7d10();
void FUN_00d3d420();
void FUN_00ace070();
void FUN_00b1e500();

struct CityEntry {
    uint32_t mID;                // +0x00
    char     pad04[0x24 - 0x04];
    uint8_t  mbFlag24;           // +0x24
    uint8_t  mbFlag25;           // +0x25
    char     pad26[0x28 - 0x26];
    uint32_t mField28;           // +0x28
    char     pad2c[0x31 - 0x2c];
    uint8_t  mByte31;            // +0x31
    char     pad32[0x44 - 0x32];
    uint32_t mField44;           // +0x44
};

struct Noun {
    PV(0) PV(1) PV(2)
    virtual void* Cast(uint32_t typeID);   // slot 3
};
typedef void (*GameDataFilter)();

struct cGameNounManager {
    Noun* CreateNoun(uint32_t typeID);           // 0x00b20c60
    cCivilization* GetPlayerCivilization();          // 0x00b25fb0
    void RemoveNoun(void* pNoun);                    // 0x00b225d0
    GameDataVec* GetGameDataVector(GameDataFilter f0, GameDataFilter f1, GameDataFilter f2, GameDataFilter f3, uint32_t id);  // 0x00b21340
    void* FUN_00989360();                            // 0x00989360
    void* FUN_00b23650(uint32_t a, uint32_t b, const Vec3* pPos, const Vec3* pPos2, const Quat* pRot);   // 0x00b23650
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
extern Random gRandom2;          // 0x016888e8
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
    char  pad00[0x14];
    char* mpEntries;                // +0x14
    char  pad18[0xac - 0x18];
    int   mCountAC;                 // +0xac
    char  padB0[0xc8 - 0xb0];
};
struct SpawnedObj { char pad00[0x234]; uint32_t mField234; };
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

// ---------------------------------------------------------------------------
// gold7 slice: city spawn / placeholder bookkeeping helpers
// ---------------------------------------------------------------------------

// @ 0x00b99070
bool FUN_00b99070(Vec3* pOut, uint8_t* pFlag)
{
    cGameNounManager* pMgr = GetNounManager();
    cNearNoun* pNear = (cNearNoun*)pMgr->FUN_00989360();
    if (pNear) {
        *pOut = *pNear->GetPosition();
        if (pFlag)
            *pFlag = 1;
        return true;
    }

    cPlanetModel* pPlanet = GetPlanetModel();
    SPVectorU v;
    v.mpBegin = v.mBuffer;
    v.mpEnd = v.mBuffer;
    v.mpEndCap = v.mBuffer + 32;
    uint32_t continent = 0xffffffff;

    GameDataVec* pData = pMgr->GetGameDataVector(&FUN_00cd7d10, &FUN_00d3d420,
                                                 &FUN_00ace070, &FUN_00b1e500, 0x36be27e);
    GameDataVectorCore* pVec = &pData->mVec;
    void** p = pVec->mpBegin;
    void** pEnd = pVec->mpEnd;
    for (; p != pEnd; ++p) {
        NounData* pObj = (NounData*)*p;
        uint32_t value = (uint32_t)pObj;
        if (pObj->mType108 == 0x91fe517b) {
            if (pObj->mSubtype110 == 0xd8c67022) {
                continent = pPlanet->GetContinent(pObj->mSub34.GetPosition());
                if (v.mpEnd < v.mpEndCap) {
                    *v.mpEnd = value;
                    ++v.mpEnd;
                } else {
                    v.DoInsertKey4(v.mpEnd, &value);
                }
            } else if (pObj->mSubtype110 == 0xaed08dd4) {
                if (v.mpEnd < v.mpEndCap) {
                    *v.mpEnd = value;
                    ++v.mpEnd;
                } else {
                    v.DoInsertKey4(v.mpEnd, &value);
                }
            }
        }
    }

    uint32_t* pMatch = FUN_00b90960(v.mpBegin, v.mpEnd, continent);
    if (pMatch != v.mpEnd)
        pMatch = FUN_00b909a0(pMatch + 1, v.mpEnd, pMatch, continent);
    v.mpEnd = pMatch;

    if (v.mpBegin == v.mpEnd) {
        FreeBuffer(v.mpBegin);
        return false;
    }

    int index = gAppProperties->GetIntProperty(0x508662a);
    int count = (int)(v.mpEnd - v.mpBegin);
    if (index < 0 || count <= index)
        index = (int)gRandom2.RandomUint32Uniform((uint32_t)count);
    FUN_00d1bef0(index);
    NounData* pCity = (NounData*)v.mpBegin[index];
    *pOut = *pCity->mSub34.GetPosition();
    FreeBuffer(v.mpBegin);
    return true;
}

// @ 0x00b992c0
void FUN_00b992c0()
{
    cGameNounManager* pMgr = GetNounManager();
    GameDataVec* pData = pMgr->GetGameDataVector(&FUN_00cd7d10, &FUN_00d3d420,
                                                 &FUN_00ace070, &FUN_00b1e500, 0x36be27e);
    GameDataVectorCore* pVec = &pData->mVec;
    PtrRange range;
    range.mpBegin = 0;
    range.mpEnd = 0;
    FUN_00b93c60(&range, (int)(pVec->mpEnd - pVec->mpBegin), pData->mpField10);
    FUN_00829110(&range, pVec->mpBegin, pVec->mpEnd, range.mpBegin, range.mpEnd);

    for (void** p = range.mpBegin; p != range.mpEnd; ++p) {
        NounData* pObj = (NounData*)*p;
        if (pObj->mpNoun1a4)
            pMgr->RemoveNoun(pObj->mpNoun1a4);
        if (pObj->mType108 == 0x91fe517b &&
            (pObj->mSubtype110 == 0xd8c67022 || pObj->mSubtype110 == 0xaed08dd4))
            pObj->mbFlag1c4 = 1;
        else
            pMgr->RemoveNoun(pObj);
    }
    for (void** p = range.mpBegin; p != range.mpEnd; ++p) {
        if (*p)
            ((Ref*)*p)->s0();
    }
    FreeBuffer((uint32_t*)range.mpBegin);
}

// @ 0x00b993c0
void* FindPlaceholder(uint32_t id)
{
    cGameNounManager* pMgr = GetNounManager();
    GameDataVec* pData = pMgr->GetGameDataVector(&FUN_00cd7d10, &FUN_00d3d420,
                                                 &FUN_00ace070, &FUN_00b1e500, 0x36be27e);
    GameDataVectorCore* pVec = &pData->mVec;
    void** p = pVec->mpBegin;
    void** pEnd = pVec->mpEnd;
    for (; p != pEnd; ++p) {
        NounData* pObj = (NounData*)*p;
        if (pObj->mType108 == 0xd18d25cd && pObj->mId24 == id)
            return pObj;
    }
    return 0;
}

// @ 0x00b99420
void FUN_00b99420()
{
    cSpeciesProfile* pAvatar = FUN_00401090()->GetAvatarProfile();
    ObjectTemplateDB* pDB = GetObjectTemplateDB();
    cGameNounManager* pMgr = GetNounManager();
    GameDataVec* pData = pMgr->GetGameDataVector(&FUN_00cd7d10, &FUN_00d3d420,
                                                 &FUN_00ace070, &FUN_00b1e500, 0x36be27e);
    GameDataVectorCore* pVec = &pData->mVec;
    void** p = pVec->mpBegin;
    void** pEnd = pVec->mpEnd;
    for (; p != pEnd; ++p) {
        NounData* pObj = (NounData*)*p;
        void* pNoun = pObj->mpNoun1a4;
        if (!pNoun)
            continue;
        cHerd* pHerd = (cHerd*)((Noun*)pNoun)->Cast(0x52aa6117);
        if (!pHerd)
            continue;
        void* pKey = pHerd->mpProfileKeyA4;
        if (!pKey || pKey == pAvatar)
            continue;
        pDB->RegisterProfile(&((ProfileHolder*)pKey)->mKey, 0);
        int count = (int)((char*)pHerd->mpEndAc - (char*)pHerd->mpBeginA8) / 0xc;
        for (int i = 0; i < count; ++i) {
            void* pProfile = pHerd->GetProfileForGeneration((uint32_t)i);
            if (pProfile)
                pDB->RegisterProfile(&((ProfileHolder*)pProfile)->mKey, 0);
        }
    }
}

// @ 0x00b99530
void FUN_00b99530(uint8_t bFilter, uint32_t* pIDs, uint32_t count)
{
    cGameNounManager* pMgr = GetNounManager();
    GameDataVec* pData = pMgr->GetGameDataVector(&FUN_00cd7d10, &FUN_00d3d420,
                                                 &FUN_00ace070, &FUN_00b1e500, 0x36be27e);
    GameDataVectorCore* pVec = &pData->mVec;
    void** p = pVec->mpBegin;
    void** pEnd = pVec->mpEnd;
    for (; p != pEnd; ++p) {
        NounData* pObj = (NounData*)*p;
        uint32_t key = (uint32_t)pObj->mpField10c;
        if (!key)
            continue;
        uint32_t sub = pObj->mSubtype110;
        if (!sub)
            continue;
        if (bFilter && (pObj->mpNoun1a4 || pObj->mbFlag1c4))
            continue;
        if (pIDs && count) {
            bool found = false;
            for (uint32_t i = 0; i < count; ++i) {
                found = (pIDs[i] == key);
                if (found)
                    break;
            }
            if (!found)
                continue;
        }
        void* pNew = pMgr->FUN_00b23650(key, sub, &pObj->mVec114, &pObj->mVec1a8, &pObj->mQuat1b4);
        if (pObj->mpNoun1a4)
            pMgr->RemoveNoun(pObj->mpNoun1a4);
        void* pOld = pObj->mpNoun1a4;
        if (pNew != pOld) {
            if (pNew)
                ((Ref*)pNew)->s0();
            pObj->mpNoun1a4 = pNew;
            if (pOld)
                ((Ref*)pOld)->Release();
        }
    }
}

// @ 0x00b99670
void FUN_00b99670()
{
    cGameNounManager* pMgr = GetNounManager();
    GameDataVec* pData = pMgr->GetGameDataVector(&FUN_00cd7d10, &FUN_00d3d420,
                                                 &FUN_00ace070, &FUN_00b1e500, 0x36be27e);
    GameDataVectorCore* pVec = &pData->mVec;
    void** p = pVec->mpBegin;
    void** pEnd = pVec->mpEnd;
    for (; p != pEnd; ++p) {
        NounData* pObj = (NounData*)*p;
        if (pObj->mpNoun1a4) {
            pMgr->RemoveNoun(pObj->mpNoun1a4);
            Ref* pRef = (Ref*)pObj->mpNoun1a4;
            if (pRef) {
                pObj->mpNoun1a4 = 0;
                pRef->Release();
            }
        }
        pObj->mVec1a8 = *pObj->mSub34.GetPosition();
        pObj->mQuat1b4 = *pObj->mSub34.GetRotation();
        pObj->mbFlag1c4 = 0;
        pObj->mbFlagA9 = 1;
    }
}

// @ 0x00b99760
void FUN_00b99760()
{
    for (int pass = 0; pass < 2; ++pass) {
        if (!gSimSingleton)
            gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
        int count = gSimSingleton->mCountAC;
        int offset = 0;
        while (count > 0) {
            if (!gSimSingleton)
                gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) SimSingleton();
            CityEntry* pEntry = (CityEntry*)(gSimSingleton->mpEntries + offset);
            if (pEntry->mbFlag24 == 0 && pEntry->mbFlag25 == (pass == 1)) {
                NounData* pCity = (NounData*)FindPlaceholder(pEntry->mID);
                Vec3 pos = *pCity->mSub34.GetPosition();
                void* pObj = FUN_00b94150(&pos, pEntry->mField28, pEntry->mByte31, 1);
                FUN_00ae38f0(pEntry);
                pEntry->mField44 = ((SpawnedObj*)pObj)->mField234;
            }
            offset += 0x64;
            --count;
        }
    }
}
