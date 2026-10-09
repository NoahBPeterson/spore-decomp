// Slice s00bb8b20: cStarManager star-database load / galaxy setup (0x00BB8B20, 3627 bytes).
// Flags region: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: string temporaries have no EH frame).
//
// Layout: the retail cStarManager (ModAPI Simulator::cStarManager, size 0x22C).
// Flow:
//  - bail out (return false) when the pre-check FUN_00ba9bc0 fails;
//  - writes the "dbreadinitiated" crash marker into the save area and removes "dbreadcompleted";
//  - sizes the 64x64 star grid, builds <dir>stars.db (dir = data dir + "TestScripts\" in the test
//    area, else the save area);
//  - if stars.db exists, opens it through a cObjectDatabase, reads the header var list (version,
//    build string, timestamp) and, when the save version is new enough, the star manager var list;
//    otherwise (or when the save is too old) stamps a fresh header (0x250003, "1.3.0.29",
//    localtime) and generates the galaxy (generation passes + the property-driven seed points);
//  - opens planetRecords.pkt (temp) and planetRecords.pkp (permanent) package databases and
//    registers them with the resource manager;
//  - seeds 50 random possible start locations when there are none, rebuilds the civ map,
//    creates the global CLG collectable items, runs the post-load passes, validates the adventure
//    planet ids and finally writes the "dbreadcompleted" marker.
//  Returns true when the galaxy was (re)generated.
#include "types.h"
#include <math.h>
#include <string.h>
#include <time.h>

#pragma pack(push, 4)

inline void* operator new(size_t, void* p) { return p; }

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t> (16 bytes incl. allocator)
extern wchar_t gEmptyString16[2];       // 0x01667BAC (EASTL gEmptyString)

struct string16
{
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;

    string16() { mpBegin = mpEnd = gEmptyString16; mpCapacity = gEmptyString16 + 1; }
    string16(const wchar_t* p) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; RangeInitialize(p); }
    string16(const string16& x) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; RangeInitialize(x.mpBegin, x.mpEnd); }
    string16(const wchar_t* p, int n) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; RangeInitialize(p, p + n); }
    int length() const { return (int)(mpEnd - mpBegin); }
    ~string16() { DeallocateSelf(); }

    void RangeInitialize(const wchar_t* p);                         // 0x00579A90
    void RangeInitialize(const wchar_t* pBegin, const wchar_t* pEnd)
    {
        const int n = (int)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n * sizeof(wchar_t));
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    void AllocateSelf(int n);                                       // 0x00429760
    void assign(const wchar_t* pBegin, const wchar_t* pEnd);        // 0x00423650
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            operator delete[](mpBegin);
    }
    string16& operator=(const string16& x)
    {
        if (&x != this)
            assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    string16& operator=(const wchar_t* p)
    {
        const wchar_t* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        assign(p, p + (pCurrent - p));
        return *this;
    }
    const wchar_t* c_str() const { return mpBegin; }
};

// A separate, out-of-line copy constructor instance (0x0056E2D0).
struct string16Copy : string16
{
    string16Copy(const string16& x);                                // 0x0056E2D0
    using string16::operator=;
};

string16 operator+(const string16& a, const wchar_t* b);           // 0x0057CBA0
string16 operator+(const string16& a, const string16& b);          // 0x00688F00

namespace EA {
    string16 ConvertToString16(const char* p, int n);               // 0x0093C5A0
    namespace IO { namespace File {
        bool Create(const wchar_t* path, bool bTruncate);           // 0x00931F20
        bool Exists(const wchar_t* path);                           // 0x00931FA0
        bool Remove(const wchar_t* path);                           // 0x00931FD0
    } }
}

// ---------------------------------------------------------------------------------------------
struct IFolder {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual const wchar_t* GetPath();                               // +0x28
};
IFolder* GetSaveArea(uint32_t id);                                  // 0x006B1F90
const wchar_t* GetDataDir();                                        // 0x00688CB0

struct IScriptFolders {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual int HasFolder(const wchar_t* name);                     // +0x1C
};
IScriptFolders* GetScriptFolders();                                 // 0x00F48A80

// EA::ResourceMan ------------------------------------------------------------------------------
struct RefObject {
    virtual int AddRef();
    virtual int Release();
};

template<class T> inline void Unused(const T& x) { (void)x; }

struct ZoneObject {
    static void* operator new(size_t n, const char* name, int, unsigned, const char*, int); // 0x00926020
};

struct IDatabase : ZoneObject {
    virtual void v00();
    virtual bool Initialize();                                      // +0x04
    virtual bool Dispose();                                         // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual bool Open(int access, int cd, bool autoOpen);           // +0x18
    virtual bool Close();                                           // +0x1C
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool SetLocation(const wchar_t* path);                  // +0x2C
};

struct DatabasePackedFile : IDatabase, RefObject {
    DatabasePackedFile(const wchar_t* location, void* pAllocator);  // 0x008D9F80
    uint32_t pad[(0x388 - 8) / 4];
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual bool RegisterDatabase(bool add, IDatabase* pDatabase, int priority); // +0x50
};
IResourceManager* GetResourceManager();                             // 0x0067DCD0

// SP::cObjectDatabase (0x24 bytes): ref-counted primary base, database interface at +4.
struct IObjectDatabase {
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c();
    virtual bool IsVersionSupported(int version);                   // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34(); virtual void v38();
    virtual void SetMode(int a, int b);                             // +0x3C
};
struct cObjectDatabase : IObjectDatabase, IDatabase {
    cObjectDatabase(DatabasePackedFile* pDBPF);                     // 0x0069FA60
    uint32_t pad[(0x24 - 8) / 4];
};

template<class T> struct AutoRefCount
{
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T*& AsOutParam()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return mpObject;
    }
};

// Object-database stream reader (opens a record of the cObjectDatabase).
struct ResourceKey { uint32_t instance, type, group; };
// The record key is passed BY VALUE: the original pushes 0x01897C18 three times as plain
// (non-relocated) immediates, i.e. the key {0x01897C18, 0x01897C18, 0x01897C18}.
struct cDatabaseStream {
    // (ResourceKey by value, spelled as its three dwords: instance, type, group)
    cDatabaseStream(cObjectDatabase* pDB, uint32_t instance, uint32_t type, uint32_t group); // 0x00693CD0
    ~cDatabaseStream();                                             // 0x00693900
    void Open();                                                    // 0x00692EA0
    void SetVersion(int version);                                   // 0x00692EC0
    uint32_t field_0;
    uint32_t field_4;
    void* mpStream;                                                 // +0x08
    uint32_t field_c;
};

// SP::cVarListSerializer (0xA14 bytes)
struct cVarListSerializer {
    cVarListSerializer(void* pObject, const void* pVarList, uint32_t signature); // 0x00692F90
    void Serialize(void* pStream);                                  // 0x00693E10
    uint32_t mData[0xA14 / 4];
};
extern const char kStarDatabaseHeaderVars[];                        // 0x01689C50
extern const char kStarManagerVars[];                               // 0x0156C668

// Header record of stars.db (serialized through kStarDatabaseHeaderVars).
struct StarDatabaseHeader {
    int mVersion;                   // +0x00
    uint32_t mSaveVersion;          // +0x04
    string16 mBuild;                // +0x08
    string16 mName;                 // +0x18
    tm mTime;                       // +0x28
    uint32_t pad[9];                // +0x4C
    ~StarDatabaseHeader();                                          // 0x00D167E0
};

// Property manager ------------------------------------------------------------------------------
struct cPropertyList { virtual int AddRef(); virtual int Release(); };
struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual bool HasPropertyList(uint32_t instance, uint32_t group);           // +0x28
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList*& pList); // +0x2C
};
IPropertyManager* PropertyManager();                                // 0x0067DE30
bool GetPropertyAsFloatArray(cPropertyList* pList, uint32_t id, int& count, float*& pValues); // 0x006A08B0

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t id, void* pData, void* pSender);  // +0x14
};
IMessageServer* MessageServer();                                    // 0x0067DCC0

struct RandomLinearCongruential {
    double RandomDoubleUniform();                                   // 0x009360D0
};
extern RandomLinearCongruential sMathRandom;                        // 0x01601760

struct cGameTimeManager;
cGameTimeManager* GameTimeManager();                                // 0x00B3D380
extern cGameTimeManager* gSerializedTimeManager;                    // 0x01689644
extern void* gSerializedRelationshipManager;                        // 0x01689640

struct WStringSet {
    void clear();                                                   // 0x005EA010
};
extern WStringSet gLoadedNames;                                     // 0x0156C64C
struct NameRegistry {
    void Assign(WStringSet* pSet);                                  // 0x00B21DA0
};
struct AppData { uint32_t pad[0x3C0 / 4]; NameRegistry mNames; };
AppData* GetAppData();                                              // 0x004010A0

extern int kStarDatabaseVersion;                                    // 0x0145F8DC (0x250003)
extern uint32_t gCLGCategory;                                       // 0x0150D6D8

struct cStarManager;
cStarManager* StarManager();                                        // 0x00B3D2A0

// Simulator ------------------------------------------------------------------------------------
struct Vector3 { float x, y, z; };
struct StarRequestFilter {
    int starTypes;
    int techLevels;
    int flags;
    float minDistance;
    float maxDistance;
    float field_14;
    int field_18;
};
struct GalaxyPoint { uint32_t v; };
void ToGalaxyPoint(float x, float y, GalaxyPoint* pOut);            // 0x01065A50

struct cPlanetRecord {
    const ResourceKey* GetPropListKey();                            // 0x00B8D8E0
};
struct cStarRecord {
    virtual int AddRef();
    virtual int Release();
    cPlanetRecord* GetPlanet(uint32_t index);                       // 0x00BBAA60
};
void ValidateAdventurePlanet(cPlanetRecord* pPlanet, uint32_t adventureID); // 0x00BA7C20

struct cCollectableItems {
    virtual int AddRef();
    virtual int Release();
    cCollectableItems();                                            // 0x00597E00
    void Configure(int a, int b, uint32_t category);                // 0x00599440
    void Unlock(uint64_t rowID, int b);                             // 0x00596DA0
    uint32_t field_4;
    uint32_t field_8;
    bool field_c;
    uint32_t pad[(0x6DAC - 0x10) / 4];
};
uint64_t GetCollectableRowID(uint32_t category, uint32_t id);       // 0x00593980
void* operator new(size_t n, const char* name, int, unsigned, const char*, int); // 0x00F473A0

struct StarRecordVec { cStarRecord** mpBegin; cStarRecord** mpEnd; cStarRecord** mpCapacity; uint32_t mAllocator; uint32_t field_10; };
struct StarGrid {
    StarRecordVec* mpBegin; StarRecordVec* mpEnd; StarRecordVec* mpCapacity; uint32_t mAllocator; uint32_t field_10;
    void resize(int n);                                             // 0x00C77A00
};

struct StarRecordPtrVec {
    AutoRefCount<cStarRecord>* mpBegin;
    AutoRefCount<cStarRecord>* mpEnd;
    AutoRefCount<cStarRecord>* mpCapacity;
    uint32_t mAllocator;
    uint32_t field_10;
    void DoInsertValue(AutoRefCount<cStarRecord>* pos, const AutoRefCount<cStarRecord>& v); // 0x00AEA5D0
    void push_back(const AutoRefCount<cStarRecord>& v)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) AutoRefCount<cStarRecord>(v);
        else
            DoInsertValue(mpEnd, v);
    }
};

struct rbtree_node_base { rbtree_node_base* mpNodeRight; rbtree_node_base* mpNodeLeft; rbtree_node_base* mpNodeParent; uint32_t mColor; };
struct AdventureNode : rbtree_node_base { uint32_t mPlanetID; uint32_t mAdventureID; };
rbtree_node_base* RBTreeIncrement(const rbtree_node_base* pNode);  // 0x00921580

struct cCivData { uint32_t pad[0x70 / 4]; void* mpCiv; };
struct cPlanet {
    uint32_t pad[0x48 / 4];
    cCivData* mpData;
    void* GetCiv() const { return mpData->mpCiv; }
};
struct CivMap { uint32_t& operator[](void* const& key); };          // 0x00BADEA0

struct cStarManager
{
    uint32_t pad_00[0x20 / 4];
    CivMap field_20;                                    // +0x20
    uint32_t pad_24[(0x3C - 0x24) / 4];
    cPlanet** field_3C_begin;                           // +0x3C
    cPlanet** field_3C_end;                             // +0x40
    uint32_t pad_44[(0x64 - 0x44) / 4];
    bool mUseTestArea;                                  // +0x64
    int mDatabaseVersion;                               // +0x68
    string16 mBuild;                                    // +0x6C
    tm mTime;                                           // +0x7C
    uint32_t* mAvailableStarterWorlds_begin;            // +0xA0
    uint32_t* mAvailableStarterWorlds_end;              // +0xA4
    uint32_t pad_a8[(0xC8 - 0xA8) / 4];
    StarGrid mStarRecordGrid;                           // +0xC8
    uint32_t pad_dc[(0x118 - 0xDC) / 4];
    StarRecordPtrVec mPossibleStartLocations;           // +0x118
    uint32_t pad_12c[(0x14C - 0x12C) / 4];
    cStarRecord* mpTempStar;                            // +0x14C
    uint32_t pad_150[(0x164 - 0x150) / 4];
    uint32_t mEmpiresSize;                              // +0x164
    uint32_t pad_168[(0x188 - 0x168) / 4];
    rbtree_node_base mAdventureIDsAnchor;               // +0x188
    uint32_t pad_198[(0x204 - 0x198) / 4];
    void* mpRelationshipManager;                        // +0x204
    uint32_t pad_208[(0x220 - 0x208) / 4];
    AutoRefCount<cCollectableItems> mpGlobalCLGItems;   // +0x220
    AutoRefCount<DatabasePackedFile> mpPlanetRecordsTempDatabase; // +0x224
    AutoRefCount<DatabasePackedFile> mpPlanetRecordsDatabase;     // +0x228

    bool CanLoad();                                     // 0x00BA9BC0
    void ResetGalaxy();                                 // 0x00BB6390
    void GenerateStars(bool b);                         // 0x00BAC620
    void GeneratePass2();                               // 0x00BB7820
    void GeneratePass3();                               // 0x00BB2A50
    void AddSeedPoint(const GalaxyPoint& p);            // 0x00BB28C0
    void GeneratePass4();                               // 0x00BB80F0
    void GeneratePass5();                               // 0x00BAAC30
    void PostLoad();                                    // 0x00BB6040
    cStarRecord* FindClosestStar(const Vector3& pos, const StarRequestFilter& filter); // 0x00BB0E90
    void UpdateEmpires();                               // 0x00BA6CF0
    void CreateEmpires();                               // 0x00BB2070
    void UpdateStars(int a);                            // 0x00BA6E00
    void CreateTempStar();                              // 0x00BAE6F0

    cPlanetRecord* GetPlanetRecord(uint32_t planetID)
    {
        if (planetID == 0xFFFFFFFF)
            return 0;
        uint32_t starIndex = planetID & 0xFFFFFF;
        cStarRecord* pStar = mStarRecordGrid.mpBegin[starIndex >> 12].mpBegin[starIndex & 0xFFF];
        return pStar->GetPlanet(planetID >> 24);
    }

    bool LoadStarDatabase();
};

bool cStarManager::LoadStarDatabase()
{
    if (!CanLoad())
        return false;

    string16 readInitiatedPath(GetSaveArea(0x4729A47)->GetPath());
    readInitiatedPath = readInitiatedPath + L"dbreadinitiated";
    EA::IO::File::Create(readInitiatedPath.c_str(), true);

    string16 readCompletedPath(GetSaveArea(0x4729A47)->GetPath());
    readCompletedPath = readCompletedPath + L"dbreadcompleted";
    EA::IO::File::Remove(readCompletedPath.c_str());

    ResetGalaxy();
    bool hasPlanetScripts = 0 != GetScriptFolders()->HasFolder(L"PlanetScripts");
    Unused(hasPlanetScripts);
    mStarRecordGrid.resize(0x1000);

    string16 starsDbName(L"stars.db");
    string16 dir;
    int access = 3;
    if (mUseTestArea) {
        dir = GetDataDir();
        dir = dir + L"TestScripts\\";
        access = 1;
    }
    else {
        dir = GetSaveArea(0x4729A47)->GetPath();
    }

    string16Copy dbPath(dir);
    dbPath = dbPath + starsDbName;

    bool exists = EA::IO::File::Exists(dbPath.c_str());
    bool isNew = !exists;
    if (exists) {
        AutoRefCount<DatabasePackedFile> pDBPF(new("Simulator", 0, 0, 0, 0) DatabasePackedFile(0, 0));
        cObjectDatabase* pODB = new("Simulator", 0, 0, 0, 0) cObjectDatabase(pDBPF);
        if (pODB)
            pODB->AddRef();
        pODB->Initialize();
        pODB->SetLocation(dbPath.c_str());
        pODB->SetMode(1, 0);
        {
        cDatabaseStream stream(pODB, 0x01897C18, 0x01897C18, 0x01897C18);
        stream.Open();
        void* pStream = stream.mpStream;
        StarDatabaseHeader header;
        {
            cVarListSerializer serializer(&header, kStarDatabaseHeaderVars, 0x1A80D26);
            serializer.Serialize(pStream);
        }
        stream.SetVersion(header.mSaveVersion);
        mDatabaseVersion = header.mVersion;
        mBuild = header.mBuild;
        mTime = header.mTime;
        if (header.mSaveVersion < 0xA0000) {
            isNew = true;
        }
        else if (pODB->IsVersionSupported(header.mSaveVersion)) {
            gSerializedTimeManager = GameTimeManager();
            gSerializedRelationshipManager = mpRelationshipManager;
            cVarListSerializer serializer(this, kStarManagerVars, 0x1A80D26);
            serializer.Serialize(pStream);
            AppData* pApp = GetAppData();
            pApp->mNames.Assign(&gLoadedNames);
            gLoadedNames.clear();
        }
        }
        pODB->Close();
        pODB->Dispose();
        pODB->Release();
    }

    if (isNew) {
        mDatabaseVersion = kStarDatabaseVersion;
        mBuild = EA::ConvertToString16("1.3.0.29", -1);
        __time64_t now = _time64(0);
        tm* pTime = _localtime64(&now);
        if (pTime)
            mTime = *pTime;
        else
            memset(&mTime, 0, sizeof(mTime));
        GenerateStars(true);
        GeneratePass2();
        GeneratePass3();

        AutoRefCount<cPropertyList> pPropList;
        if (PropertyManager()->GetPropertyList(0x288CFA78, 0, pPropList.AsOutParam())) {
            int count = 0;
            float* pValues;
            if (GetPropertyAsFloatArray(pPropList, 0x61341E4, count, pValues)) {
                for (int i = 0; i < count; i += 2) {
                    GalaxyPoint point;
                    ToGalaxyPoint(pValues[i], pValues[i + 1], &point);
                    AddSeedPoint(point);
                }
            }
        }
        GeneratePass4();
        GeneratePass5();
    }

    mpPlanetRecordsTempDatabase = new("Simulator", 0, 0, 0, 0) DatabasePackedFile(0, 0);
    mpPlanetRecordsTempDatabase->Initialize();
    string16 tempPath(dir);
    tempPath = tempPath + L"planetRecords.pkt";
    EA::IO::File::Remove(tempPath.c_str());
    mpPlanetRecordsTempDatabase->SetLocation(tempPath.c_str());
    mpPlanetRecordsTempDatabase->Open(3, 6, false);
    GetResourceManager()->RegisterDatabase(true, mpPlanetRecordsTempDatabase, 1000);

    mpPlanetRecordsDatabase = new("Simulator", 0, 0, 0, 0) DatabasePackedFile(0, 0);
    mpPlanetRecordsDatabase->Initialize();
    string16 permPath(dir);
    permPath = permPath + L"planetRecords.pkp";
    mpPlanetRecordsDatabase->SetLocation(permPath.c_str());
    mpPlanetRecordsDatabase->Open(access, 6, false);
    GetResourceManager()->RegisterDatabase(true, mpPlanetRecordsDatabase, 0);

    PostLoad();

    if (mPossibleStartLocations.mpBegin == mPossibleStartLocations.mpEnd) {
        for (int i = 0; i < 50; i++) {
            Vector3 pos;
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;
            double r = sMathRandom.RandomDoubleUniform();
            pos.x = (float)r;
            pos.y = (float)sqrt(1.0 - r * r);
            double dist = (sMathRandom.RandomDoubleUniform() + 1.0) * 150.0;
            if (dist >= 300.0)
                dist = 300.0;
            else if (dist < 150.0)
                dist = 150.0;
            pos.x = (float)(pos.x * dist);
            pos.y = (float)(pos.y * dist);
            pos.z = (float)(pos.z * dist);

            StarRequestFilter filter;
            filter.starTypes = 0x1FFF;
            filter.techLevels = 2;
            filter.flags = 0;
            filter.minDistance = -1.0f;
            filter.maxDistance = 5.0f;
            filter.field_14 = -1.0f;
            filter.field_18 = 0;
            AutoRefCount<cStarRecord> pStar(FindClosestStar(pos, filter));
            mPossibleStartLocations.push_back(pStar);
        }
    }

    unsigned count = (unsigned)(field_3C_end - field_3C_begin);
    for (unsigned i = 0; i < count; i++) {
        cPlanet*& pPlanet = field_3C_begin[i];
        field_20[pPlanet->GetCiv()] = (uint32_t)pPlanet;
    }

    if (!mpGlobalCLGItems) {
        mpGlobalCLGItems = new("Simulator", 0, 0, 0, 0) cCollectableItems();
        mpGlobalCLGItems->Configure(0, 0, gCLGCategory);
        mpGlobalCLGItems->field_c = false;
        mpGlobalCLGItems->Unlock(GetCollectableRowID(gCLGCategory, 0x3824091B), 0);
        mpGlobalCLGItems->Unlock(GetCollectableRowID(gCLGCategory, 0x026D3C30), 0);
        mpGlobalCLGItems->Unlock(GetCollectableRowID(gCLGCategory, 0x5683C01E), 0);
        mpGlobalCLGItems->Unlock(GetCollectableRowID(gCLGCategory, 0x35916FD9), 0);
        mpGlobalCLGItems->Unlock(GetCollectableRowID(gCLGCategory, 0xA1C47665), 0);
    }

    UpdateEmpires();
    if (mEmpiresSize == 0)
        CreateEmpires();
    if (mAvailableStarterWorlds_begin == mAvailableStarterWorlds_end)
        GenerateStars(false);
    MessageServer()->PostMSG(0x625D27D, 0, 0);
    UpdateStars(0);
    StarManager();
    StarManager();
    if (!mpTempStar)
        CreateTempStar();

    for (rbtree_node_base* it = mAdventureIDsAnchor.mpNodeLeft; it != &mAdventureIDsAnchor; it = RBTreeIncrement(it)) {
        AdventureNode* pNode = (AdventureNode*)it;
        uint32_t adventureID = pNode->mAdventureID;
        cPlanetRecord* pPlanet = GetPlanetRecord(pNode->mPlanetID);
        const ResourceKey* pKey = pPlanet->GetPropListKey();
        if (!PropertyManager()->HasPropertyList(pKey->instance, pKey->group))
            ValidateAdventurePlanet(pPlanet, adventureID);
    }

    EA::IO::File::Create(readCompletedPath.c_str(), true);
    return isNew;
}

#pragma pack(pop)
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct NameRegistry {
    void Assign(void*); // 0x00b21da0
};
struct WStringSet {
    void clear(); // 0x005ea010
};
}
