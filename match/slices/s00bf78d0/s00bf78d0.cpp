// Slice s00bf78d0 (0x00bf78d0..0x00bf8705) -- Simulator::cCivilization: the
// constructor, the cGameData_func3Ch / RemoveOwner overrides and the two
// owner/selection update helpers that drive the civilization AI timers.
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE

typedef unsigned char    uint8;
typedef unsigned short   uint16;
typedef unsigned int     uint32;
typedef unsigned __int64 uint64;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------- extern data
// The two game-mode objects: compared by address against GetCurrentGameMode().
extern char    DAT_01654c04;
extern char    DAT_01654c05;
extern int     DAT_0156f898;        // round-robin index into the 0x1c table
extern char    DAT_0168caf0[];      // table of 0x1c-byte records
extern char    DAT_0168cb0c[];      // &DAT_0168caf0[1]
extern wchar_t gEmptyString16[];    // 0x01667bac
extern wchar_t gEmptyString16b[];   // 0x01667bae

// ---------------------------------------------------------------- free functions
void*  SP_NounManager();                       // 0x00b3d300
void*  MessageServer();                        // 0x0067dcc0
void*  GetCurrentGameMode();                   // 0x00b5b800
void*  SP_RelationshipManager();               // 0x00b3d2c0
void*  SP_BehaviorManager();                   // 0x00b3d260
int    FUN_00b6e050();                         // 0x00b6e050
void*  FUN_00b6f0c0(int key);                  // 0x00b6f0c0
void*  FUN_01021260();                         // 0x01021260  GetActivePlanet
void*  FUN_01021370();                         // 0x01021370  GetPlayerHomePlanet
void*  FUN_00b26930();                         // 0x00b26930
void*  __stdcall FUN_00b3d2a0(int id);         // 0x00b3d2a0  StarManager (callee pops)
void*  EASTLAlloc(uint32 n, const char* pName, int a, int b, const char* c, int d);  // 0x00f473a0
void   FUN_00829110(void* dst, void* first, void* last, void* a, void* b);  // 0x00829110
void   operator_delete(void* p);               // 0x00f47380
void   FUN_00cd7d10();                         // table entries handed to GetGameDataVector
void   FUN_00d3d420();
void   FUN_00acdff0();
void   FUN_00b1e500();
void   FUN_00ae5ea0();
void   FUN_00bf6d80();

// ---------------------------------------------------------------- class stubs
class cCity;
class cCivilization;
class cGameData;
class cGameNounManager;

// A secondary polymorphic base that occupies a pointer-sized slot.
class BaseV { public: virtual void b0(); };

// The primary (Object) base: vtable slots 0x00..0x20.
class ObjectBase {
public:
    virtual void AddRef();          // 0x00
    virtual void Release();         // 0x04
    virtual void vdtor();           // 0x08
    virtual void Cast();            // 0x0c
    virtual void Write();           // 0x10
    virtual void Read();            // 0x14
    virtual void func18h();         // 0x18
    virtual void WriteToXML();      // 0x1c
    virtual int  GetNounID();       // 0x20
};

class cGameData : public ObjectBase, public BaseV {
public:
    virtual void SetDefinitionID();             // 0x24
    virtual void SetGameDataOwner();            // 0x28
    virtual bool IsDestroyed();                 // 0x2c
    virtual void* GetGameDataOwner();           // 0x30
    virtual void SetGameDataOwner2();           // 0x34
    virtual void* GetCastID();                  // 0x38
    virtual char cGameData_func3Ch(int param);  // 0x3c
    virtual void func40h();                     // 0x40
    virtual void RemoveOwner();                 // 0x44
    virtual void SetPoliticalID(int id);        // 0x48
    virtual int  GetPoliticalID();              // 0x4c
    virtual void WriteAsText();                 // 0x50

    char FUN_00bd7c60(int owner);    // 0x00bd7c60
    void FUN_00be10d0();             // 0x00be10d0

    char mPad08[0x34 - 8];
};

// A game-data object with data past 0x214 (cCommunity / cCity family).
class cCommunity : public cGameData {
public:
    void FUN_00bff750();             // 0x00bff750
    void Deactivate();               // 0x00bfe4d0
    char mPad34[0x214 - 0x34];
    cGameData* m214;                 // +0x214
};

// A secondary polymorphic base of cCivilization at +0x34.
class Base34 { public: virtual void b0(); };

// The message listener base at +0x38 (slots up to +0x2c are used).
class IMessageListener {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(); virtual void m24(); virtual void m28(); virtual void m2c();
};

// The base at +0x3c; only its +0x00 vtable pointer lives here.
class Base3C {
public:
    virtual void b0();
    void FUN_00c2e4e0();             // 0x00c2e4e0
    void FUN_00b6ee10();             // 0x00b6ee10
};

// cGonzagoTimer is a 0x20-byte cSPTimer.
class cGonzagoTimer {
public:
    char mData[0x20];
    cGonzagoTimer();                                 // 0x00b63890
    ~cGonzagoTimer();                                // 0x00b638b0
    void Start();                                    // 0x00bc30f0
    unsigned __int64 GetElapsedTime();               // 0x00bc3190
    void Restart();                                  // 0x00bc3130
};

// Red/black tree anchor, 0x10 bytes.
class TreeAnchor {
public:
    TreeAnchor* mpNodeLeft;          // +0x00
    TreeAnchor* mpNodeRight;         // +0x04
    TreeAnchor* mpNodeParent;        // +0x08
    char        mColor;              // +0x0c
    TreeAnchor() : mpNodeRight(0), mpNodeParent(0), mColor(0) { mpNodeLeft = this; }
};

// rbtree container: anchor + size, 0x14 bytes.
class RBTree {
public:
    TreeAnchor mAnchor;              // +0x00
    int        mnSize;               // +0x10
    RBTree() : mnSize(0) {}
};

// The 0x1c-byte container at cCivilization+0x6c.
class Map6C {
public:
    int        mUnknown;             // +0x00
    TreeAnchor mAnchor;              // +0x04
    int        mnSize;               // +0x14
    int        mPad18;               // +0x18
    Map6C() : mnSize(0) {}
    void FUN_00bf3460(void* p);      // 0x00bf3460
    void FUN_00bf4350(void* p);      // 0x00bf4350
};

// eastl::vector<T> (3 pointer representation).
template <class T>
class Vec {
public:
    T* mpBegin;                      // +0x00
    T* mpEnd;                        // +0x04
    T* mpCap;                        // +0x08
    Vec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    T* erase(T* first, T* last);     // 0x00b48e40
    void resize(int n);
};

// EA::intrusive_ptr-like 4-byte reference counted handle.
template <class T>
class AutoRefCount {
public:
    T* mpObject;                     // +0x00
    AutoRefCount() : mpObject(0) {}
    void Set(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
    }
};

// The vector returned by cGameNounManager::GetGameDataVector.
class cGameDataVector {
public:
    char        pad00[4];
    cGameData** mpBegin;             // +0x04
    cGameData** mpEnd;               // +0x08
    cGameData** mpCap;               // +0x0c
    void*       mpAlloc;             // +0x10
};

// The vector returned by cGameNounManager::GetCivilizationList.
class cCivList {
public:
    cCivilization** mpBegin;         // +0x00
    cCivilization** mpEnd;           // +0x04
};

class cGameNounManager {
public:
    cCivList* GetCivilizationList();                                   // 0x00b25ca0
    cGameDataVector* GetGameDataVector(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void RemoveNoun(void* p);                                          // 0x00b225d0
    void FUN_00b21410(cCivilization* civ);                             // 0x00b21410
    int  ClassifyById(int id);                                         // 0x00b20790
    void FUN_00b23560(cCivilization* civ);                             // 0x00b23560
    void* GetCurrentTerrainSphere();                                   // 0x00f67d90
};

class cMessageServer {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14(); virtual void m18(); virtual void m1c();
    virtual void m20(void* listener, int msg) {}
    virtual void m24(); virtual void m28();
    virtual void m2c(void* listener, int msg, int a) {}
};

class StarManager {
public:
    int   FUN_00ba6630();                    // 0x00ba6630
    void* GetEmpireByID();                   // 0x00ba9370
};

class Empire {
public:
    void* FUN_00bce4c0();                    // 0x00bce4c0
};

class SomeAE {
public:
    char FUN_00ae3600();                     // 0x00ae3600
};

// The object returned by FUN_01021260 (the active planet).
class PlanetStub {
public:
    char mPad13C[0x13c];
    volatile int m13C;                       // +0x13c
};

class TerrainSphere {
public:
    int FUN_00c75420();                      // 0x00c75420
};

class cCity : public cCommunity {
public:
    int  GetContinent(int def);              // 0x00bd8210
    char mPad218[0x519 - 0x218];             // +0x218
    char m519;                               // +0x519
};

class cRelationshipManager {
public:
    int   FUN_00d00a70(int a, int b, int c);              // 0x00d00a70
    float CalculateRelationshipPersonality(cCivilization* a, cCivilization* b);  // 0x00d02050
};

// ---------------------------------------------------------------- cCivilization
class cCivilization : public cGameData, public Base34, public IMessageListener, public Base3C {
public:
    cCivilization();                                 // 0x00bf78d0
    char cGameData_func3Ch(int param);               // 0x00bf8140 override
    void RemoveOwner();                              // 0x00bf7d80 override
    void FUN_00bf8170(int ownerId, char playerOwned, int key, char flag);  // 0x00bf8170
    void FUN_00bf8440();                             // 0x00bf8440

    void FUN_00bf23d0();                             // 0x00bf23d0
    void RebuildToolPages();                         // 0x00bf6ee0
    void FUN_00bf4eb0();                             // 0x00bf4eb0
    void FUN_00bf45f0(void* p, int a);               // 0x00bf45f0
    void FUN_00bf3b50(void* p);                      // 0x00bf3b50
    int  CommunityScoreSum();                        // 0x00bf7150
    int  FUN_00bf0f40();                             // 0x00bf0f40
    char city_on_continent(int continent);           // 0x00bf00a0

    int         m40;                                 // +0x40
    char        mPad44[0x1c];                        // +0x44
    Vec3        m60;                                 // +0x60
    Map6C       m6C;                                 // +0x6c
    uint8       m88, m89, m8A, m8B, m8C, m8D, m8E, m8F, m90, m91, m92, m93, m94;  // +0x88
    char        mPad95[3];                           // +0x95
    float       m98;                                 // +0x98
    Vec<cCity*> mCities;                             // +0x9c
    char        mPadA8[8];                           // +0xa8
    Vec<void*>  mUnits;                              // +0xb0
    char        mPadBC[8];                           // +0xbc
    Vec3        mC4;                                 // +0xc4
    int         mD0;                                 // +0xd0
    Vec<void*>  mD4Vec;                              // +0xd4
    char        mPadE0[8];                           // +0xe0
    cGonzagoTimer mTimers[12];                       // +0xe8
    int         m268, m26C, m270;                    // +0x268
    AutoRefCount<cGameData> mp274;                   // +0x274
    void*       mp278; void* mp27C; void* mp280;     // +0x278  mName
    char        mPad284[4];                          // +0x284
    void*       mp288; void* mp28C; void* mp290;     // +0x288  mDescription
    char        mPad294[4];                          // +0x294
    int         m298;                                // +0x298
    int         m29C;                                // +0x29c
    int         m2A0;                                // +0x2a0
    int         m2A4, m2A8;                          // +0x2a4
    AutoRefCount<cGameData> mp2AC;                   // +0x2ac
    cGonzagoTimer mT1;                               // +0x2b0
    AutoRefCount<cGameData> mF1; char mPad2D4[4];    // +0x2d0
    cGonzagoTimer mT2;                               // +0x2d8
    AutoRefCount<cGameData> mF2; char mPad2FC[4];    // +0x2f8
    cGonzagoTimer mT3;                               // +0x300
    uint8       mF3; char mPad321[7];                // +0x320
    cGonzagoTimer mT4;                               // +0x328
    uint8       mF4; char mPad349[7];                // +0x348
    cGonzagoTimer mT5;                               // +0x350
    uint8       mF5; char mPad371[7];                // +0x370
    cGonzagoTimer mT6;                               // +0x378
    uint8       mF6; char mPad399[7];                // +0x398
    cGonzagoTimer mT7;                               // +0x3a0
    uint8       mF7; char mPad3C1[7];                // +0x3c0
    cGonzagoTimer mT8;                               // +0x3c8
    uint8       mF8; char mPad3E9[7];                // +0x3e8
    cGonzagoTimer mT9;                               // +0x3f0
    char        mPad410[4];                          // +0x410
    RBTree      m414;                                // +0x414  (mnSize at +0x424)
    char        mPad428[4];                          // +0x428
    void*       mp42C;                               // +0x42c
    uint8       m430, m431;                          // +0x430
    char        mPad432[2];                          // +0x432
    int         m434, m438, m43C, m440, m444;        // +0x434
    float       m448;                                // +0x448
    int         m44C, m450, m454, m458, m45C, m460;  // +0x44c
    void*       mp464;                               // +0x464
    void*       mp468;                               // +0x468
    AutoRefCount<cCivilization> mp46C;               // +0x46c
    void*       mp470;                               // +0x470
    void*       mp474;                               // +0x474
    void*       mp478;                               // +0x478
    char        mPad47C[8];                          // +0x47c
    int         m484, m488, m48C;                    // +0x484
    Vec<cGonzagoTimer> mSuperTimers;                 // +0x490
    char        mPad49C[8];                          // +0x49c
    void*       mp4A4;                               // +0x4a4
    int         m4A8;                                // +0x4a8
    float       m4AC, m4B0;                          // +0x4ac
    int         m4B4, m4B8;                          // +0x4b4
    char        mPad4BC[4];                          // +0x4bc
    int         m4C0, m4C4, m4C8;                    // +0x4c0
    uint8       m4CC;                                // +0x4cc
    char        mPad4CD[3];                          // +0x4cd
    int         m4D0;                                // +0x4d0
};

// ---------------------------------------------------------------- extra externs
extern char  DAT_018c43e8;                  // table descriptor handed to GetGameDataVector
void* FUN_01062ee0(void* p);                // 0x01062ee0

// A BehaviourManager; only the virtual at +0x3c is used.
class BehaviorManager {
public:
    virtual void b00(); virtual void b04(); virtual void b08(); virtual void b0c();
    virtual void b10(); virtual void b14(); virtual void b18(); virtual void b1c();
    virtual void b20(); virtual void b24(); virtual void b28(); virtual void b2c();
    virtual void b30(); virtual void b34(); virtual void b38();
    virtual void b3c(void* p);
};

// Local eastl vector used for the temporary game-data list copies.
class TempVec {
public:
    void* mpBegin;                           // +0x00
    void* mpEnd;                             // +0x04
    void* mpCap;                             // +0x08
    void* mpAlloc;                           // +0x0c
    void FUN_00b93c60(int count, void* alloc);   // 0x00b93c60
};

// ---------------------------------------------------------------- 0x00bf78d0
// @ 0x00bf78d0 cCivilization::cCivilization
cCivilization::cCivilization()
    : m88(0), m89(0), m8A(0), m8B(0), m8C(0), m8D(0), m8E(0), m8F(0), m90(0), m91(0),
      m92(1), m93(1), m94(1), m98(0.0f),
      mD0(0),
      m268(0), m26C(0), m270(0),
      mp278(gEmptyString16), mp27C(gEmptyString16), mp280(gEmptyString16b),
      mp288(gEmptyString16), mp28C(gEmptyString16), mp290(gEmptyString16b),
      m298(1), m29C(-1), m2A0(-1), m2A4(0), m2A8(0),
      mF3(0), mF4(0), mF5(0), mF6(0), mF7(0), mF8(0),
      mp42C(0), m430(0), m431(0),
      m434(-1), m438(0), m43C(-1), m440(0), m444(0), m448(0.0f),
      m44C(0), m450(-1), m454(0), m458(0), m45C(0), m460(0),
      mp464(0), mp468(0), mp470(0), mp474(0), mp478(0),
      m484(0), m488(0), m48C(0), mp4A4(0), m4A8(-1), m4AC(0.0f), m4B0(0.0f),
      m4B4(0), m4B8(0), m4C0(0), m4C4(0), m4C8(0), m4CC(0), m4D0(0)
{
    for (int i = 0; i < 12; ++i)
        mTimers[i].Start();

    void* p = EASTLAlloc(0x18, "Simulator", 0, 0, 0, 0);
    mp42C = p ? FUN_01062ee0(p) : 0;

    m484 = 0;
    m488 = 0;
    m48C = 0;
    mSuperTimers.resize(12);
}

// ---------------------------------------------------------------- 0x00bf7d80
// @ 0x00bf7d80 cCivilization::RemoveOwner
void cCivilization::RemoveOwner()
{
    IMessageListener* listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m2c(listener, 0x1a0219e, 0xffffd8f1);
    listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m2c(listener, 0x20c089c, 0xffffd8f1);
    listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m2c(listener, 0x6524f8f, 0xffffd8f1);

    mD4Vec.erase(mD4Vec.mpBegin, mD4Vec.mpEnd);
    mp2AC.Set(0);
    mF1.Set(0);
    mF2.Set(0);
    while (mCities.mpBegin != mCities.mpEnd) {
        cCity* city = mCities.mpEnd[-1];
        if (city) city->AddRef();
        FUN_00bf45f0(city, 1);
        ((cGameNounManager*)SP_NounManager())->RemoveNoun(city);
        if (city) city->Release();
    }
    mp274.Set(0);
    while (mUnits.mpBegin != mUnits.mpEnd) {
        cGameData* unit = (cGameData*)mUnits.mpEnd[-1];
        void* behavior = 0;
        if (unit) {
            unit->AddRef();
            behavior = (char*)unit + 0x5d0;
        }
        ((BehaviorManager*)SP_BehaviorManager())->b3c(behavior);
        FUN_00bf3b50(unit);
        ((cGameNounManager*)SP_NounManager())->RemoveNoun(unit);
        if (unit) unit->Release();
    }
    mD4Vec.erase(mD4Vec.mpBegin, mD4Vec.mpEnd);

    void* pNounManager = SP_NounManager();
    int owner = GetPoliticalID();
    cGameDataVector* v1 = ((cGameNounManager*)pNounManager)->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00bf6d80,
        (void*)FUN_00b1e500, (void*)0x3d5c325);

    TempVec tmp1;
    tmp1.FUN_00b93c60((int)(v1->mpEnd - v1->mpBegin), (char*)v1 + 0x10);
    FUN_00829110(&tmp1, v1->mpBegin, v1->mpEnd, tmp1.mpEnd, tmp1.mpBegin);
    for (cGameData** it = (cGameData**)tmp1.mpBegin; it != (cGameData**)tmp1.mpEnd; ++it) {
        if ((*it)->FUN_00bd7c60(owner))
            (*it)->FUN_00be10d0();
    }

    cGameDataVector* v2 = ((cGameNounManager*)pNounManager)->GetGameDataVector(
        (void*)FUN_00cd7d10, (void*)FUN_00d3d420, (void*)FUN_00ae5ea0,
        (void*)FUN_00b1e500, (void*)0x403df5c);
    int n = (int)(v2->mpEnd - v2->mpBegin);
    cCommunity** arr;
    if (n == 0) {
        arr = 0;
    } else {
        arr = (cCommunity**)EASTLAlloc(n * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }
    TempVec tmp2;
    FUN_00829110(&tmp2, v2->mpBegin, v2->mpEnd, arr, tmp1.mpBegin);
    for (cCommunity** it = arr; it != (cCommunity**)tmp2.mpBegin; ++it) {
        cCommunity* item = *it;
        if (item->GetPoliticalID() == owner)
            item->FUN_00bff750();
        if ((int)item->m214 == owner)
            item->Deactivate();
    }

    ((Base3C*)((char*)this + 0x3c))->FUN_00b6ee10();
    ((cGameNounManager*)SP_NounManager())->FUN_00b21410(this);
    mp468 = 0;
    mp464 = 0;

    for (cCommunity** it = arr; it != (cCommunity**)tmp2.mpBegin; ++it) {
        if (*it) (*it)->Release();
    }
    if (arr != 0 && ((int*)arr)[-1] != 0)
        operator_delete(arr);
    for (cGameData** it = (cGameData**)tmp1.mpBegin; it != (cGameData**)tmp1.mpEnd; ++it) {
        if (*it) (*it)->Release();
    }
    if (tmp1.mpBegin != 0 && ((int*)tmp1.mpBegin)[-1] != 0)
        operator_delete(tmp1.mpBegin);
}

// ---------------------------------------------------------------- 0x00bf8140
// @ 0x00bf8140 cCivilization::cGameData_func3Ch
char cCivilization::cGameData_func3Ch(int param)
{
    char result = cGameData::cGameData_func3Ch(param);
    FUN_00bf23d0();
    RebuildToolPages();
    return result;
}

// ---------------------------------------------------------------- 0x00bf8170
// @ 0x00bf8170 cCivilization::FUN_00bf8170
void cCivilization::FUN_00bf8170(int ownerId, char playerOwned, int key, char flag)
{
    cGameNounManager* pNounManager = (cGameNounManager*)SP_NounManager();
    pNounManager->GetCivilizationList();
    pNounManager->GetGameDataVector((void*)FUN_00cd7d10, (void*)FUN_00d3d420,
        (void*)FUN_00acdff0, (void*)FUN_00b1e500, &DAT_018c43e8);

    if (m88)
        return;
    m88 = 1;
    m89 = playerOwned;
    if (GetCurrentGameMode() == &DAT_01654c04)
        m8A = (m89 == 0);
    else
        m8A = 0;

    IMessageListener* listener = (IMessageListener*)((char*)this + 0x38);
    ((cMessageServer*)MessageServer())->m20(listener, 0x1a0219e);
    if (playerOwned)
        ((cMessageServer*)MessageServer())->m20(listener, 0x6524f8f);
    ((Base3C*)((char*)this + 0x3c))->FUN_00c2e4e0();

    if (key == 0x53dbcf2 && playerOwned) {
        m40 = 0x53dbcf1;
        Vec3* p = (Vec3*)FUN_00b6f0c0(0x53dbcf1);
        mC4 = *p;
        Vec3 tmp = { mC4.x, mC4.y, mC4.z };
        m60 = tmp;
    } else {
        int k = (key == 0x53dbcf2) ? FUN_00b6e050() : key;
        m40 = k;
        Vec3* p = (Vec3*)FUN_00b6f0c0(k);
        mC4 = *p;
    }

    SetPoliticalID(ownerId);
    if (!playerOwned) {
        if (GetCurrentGameMode() != &DAT_01654c05) {
            if (FUN_01021260() == 0
                || ((PlanetStub*)FUN_01021260())->m13C != (int)FUN_01021370()) {
                DAT_0156f898 = 1;
                m6C.FUN_00bf3460(&DAT_0168cb0c);
            } else {
                int index;
                if (flag && ((SomeAE*)FUN_00b26930())->FUN_00ae3600()) {
                    index = 1;
                    DAT_0156f898 = 1;
                } else {
                    index = DAT_0156f898++;
                }
                m6C.FUN_00bf4350(DAT_0168caf0 + index * 0x1c);
            }
            if (DAT_0156f898 == 3)
                DAT_0156f898 = 1;
        }
    } else {
        m6C.FUN_00bf3460(&DAT_0168caf0);
        FUN_00bf4eb0();
    }

    if (ownerId == -1)
        ownerId = ((StarManager*)FUN_00b3d2a0(0))->FUN_00ba6630();

    ((cMessageServer*)MessageServer())->m20(listener, 0x20c089c);
    if (pNounManager->ClassifyById(ownerId) == 5) {
        Empire* empire = (Empire*)((StarManager*)FUN_00b3d2a0(ownerId))->GetEmpireByID();
        mp274.Set((cGameData*)empire->FUN_00bce4c0());
    }
    if (pNounManager->ClassifyById(ownerId) <= 4)
        pNounManager->FUN_00b23560(this);
    RebuildToolPages();
}

// ---------------------------------------------------------------- 0x00bf8440
// @ 0x00bf8440 cCivilization::FUN_00bf8440
void cCivilization::FUN_00bf8440()
{
    if (m89) {
        TerrainSphere* sphere =
            (TerrainSphere*)((cGameNounManager*)SP_NounManager())->GetCurrentTerrainSphere();
        if (sphere->FUN_00c75420() <= 0)
            return;
    }

    cGonzagoTimer* pTimer = (cGonzagoTimer*)((char*)this + 0x248);
    if (pTimer->GetElapsedTime() <= 60000)
        return;

    cCivilization* oldSelected = mp46C.mpObject;
    mp46C.Set(0);

    cCivilization* best = 0;
    float bestScore = 0.0f;

    if (mCities.mpEnd - mCities.mpBegin > 1) {
        cCivList* list = ((cGameNounManager*)SP_NounManager())->GetCivilizationList();
        cCivilization** it = list->mpBegin;
        cCivilization** end = list->mpEnd;
        if (it != end) {
            do {
                cCivilization* other = *it;
                if (other != this && other->m8A == 0 && other->m89 == 0) {
                    int myId = GetPoliticalID();
                    int hisId = other->GetPoliticalID();
                    if (((cRelationshipManager*)SP_RelationshipManager())->FUN_00d00a70(hisId, myId, 1) < 4
                        && other->mCities.mpEnd - other->mCities.mpBegin > 1) {
                        float score = -((cRelationshipManager*)SP_RelationshipManager())
                                            ->CalculateRelationshipPersonality(other, this);
                        score += (float)(other->mCities.mpEnd - other->mCities.mpBegin) * 2.0f;
                        score += (float)other->CommunityScoreSum() * 0.5f;
                        int count = (int)(other->mCities.mpEnd - other->mCities.mpBegin);
                        for (int i = 0; i < count; ++i) {
                            cCity* city = other->mCities.mpBegin[i];
                            if (city_on_continent(city->GetContinent(-1))) {
                                if (city->m519) {
                                    if (FUN_00bf0f40() == 1)
                                        score += 0.75f;
                                    else
                                        score += 3.0f;
                                } else {
                                    if (FUN_00bf0f40() == 1)
                                        score += 1.0f;
                                    else
                                        score += 4.0f;
                                }
                            }
                        }
                        if (oldSelected == other)
                            score += 5.0f;
                        if (score > bestScore) {
                            best = other;
                            bestScore = score;
                        }
                    }
                }
                ++it;
            } while (it != end);
        }
    }

    mp46C.Set(best);
    pTimer->Restart();
}

