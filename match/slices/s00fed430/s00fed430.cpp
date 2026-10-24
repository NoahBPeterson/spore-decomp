// Slice s00fed430: cSPMissionManager mission bookkeeping helpers (21 functions,
// 0x00fed430 .. 0x00fee310).
//
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Layout notes (retail, differs from the 2008 dev PDB):
//   +0x14/+0x15/+0x16      bools (mbFlightSchoolFinished at +0x16)
//   +0x18                  mCheatMissionIDOverride
//   +0x1c                  mNextMissionID
//   +0x20/+0x34/+0x48      mission requisite vectors (0x14-byte eastl vectors)
//   +0x5c                  tutorial mission state map (0x1c, map<uint,uint>::operator[])
//   +0x78                  property list (intrusive ptr, property getters 0x1254b050/0x2ae1a8e)
//   +0x80                  mTutorialTargetPlanetKeys  (vector<uint32_t>, 4-byte elements)
//   +0x94                  mTutorialSpeciesIDs        (vector<Key>, 12-byte elements)
//   +0xa8                  mTrackedMissions           (vector<AutoRefCount<cSPMission>>, 4-byte)
//   +0xc8                  mRecentColonyMissions      (eastl::list<tRecentMission>, anchor itself)
//   +0xd4                  mRecentNPCMissions         (eastl::list<tRecentMission>)
//
// The eastl vector here is 0x14 bytes with the sp_vector_allocator FIRST: &vector == &allocator,
// so the vector's three pointers live at +4/+8/+0xc.  Every member function is out of line
// (their bodies are not emitted in this translation unit, so ODR is preserved for the ones we
// reference only by address).

#include "types.h"
#include <intrin.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define CAT2_(a, b) a##b
#define CAT_(a, b) CAT2_(a, b)
#define PV virtual void CAT_(_pv, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16

// ------------------------------------------------------------------ forward decls
struct cPropertyList; struct Property;
struct cEmpire; struct cPlanetRecord; struct RefCounted;
class cGameData;
struct cSPMission;
struct cSPMissionManager;
struct Record38;

// ------------------------------------------------------------------ eastl vector (0x14 bytes)
template <class T> class SPVector
{
public:
    T*     mpBegin;     // +0x00
    T*     mpEnd;       // +0x04
    T*     mpCapacity;  // +0x08
    struct Alloc
    {
        void* mpName;     // +0x0c
        void* mPool;      // +0x10
    };
    Alloc  mAlloc;      // +0x0c

    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }

    // out of line in the original; body is not emitted in this TU
    void assign(const SPVector<T>* src);   // 0x0050d4e0
    void reserve(uint32_t n);              // 0x004e0880
    void DoInsertValueI(T* where, T const& v);   // 0x004558a0
    void DoInsertKey(T* where, T const& v);      // 0x004e3e10
    void DoInsertPtr(T* where, T const& v);      // 0x00aea5d0
    void DoInsertKey4(T* where, T const& v);     // 0x00b96600

    void push_back(T const& v)
    {
        if (mpEnd < mpCapacity)
        {
            T* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot)
                *slot = v;
        }
        else
        {
            DoInsertKey(mpEnd, v);
        }
    }
};

// ------------------------------------------------------------------ property list
struct Property
{
    void*    mpData;      // +0x00
    uint32_t pad04;       // +0x04
    uint32_t mnCount;     // +0x08 (element count when array / external data)
    uint32_t pad0c;       // +0x0c
    uint8_t  mnFlags;     // +0x10 (0x30 = array / external data)
    uint8_t  pad11[1];
    uint16_t mnType;      // +0x12

    void* GetValuePtr()
    {
        if (mnFlags & 0x30)
            return mpData;
        else if (mnType != 0)
            return this;
        return 0;
    }
};

struct cPropertyList
{
    virtual int  AddRef();                                    // +0x00
    virtual int  Release();                                   // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual Property* GetProperty(uint32_t id);               // +0x28
    virtual bool GetProperty2(uint32_t id, uint32_t id2, void* out);  // +0x2c
};

cPropertyList* PropertyManager();                             // 0x0067de30

// ------------------------------------------------------------------ intrusive ref count
struct RefCounted
{
    virtual int  AddRef();                                    // +0x00
    virtual void Release();                                   // +0x04
};

struct AutoRefCount
{
    void* mpObject;
    AutoRefCount() : mpObject(0) {}
    ~AutoRefCount() { if (mpObject) ((RefCounted*)mpObject)->Release(); }
    AutoRefCount& operator=(RefCounted* p)
    {
        if (p) p->AddRef();
        if (mpObject) ((RefCounted*)mpObject)->Release();
        mpObject = p;
        return *this;
    }
};

// ------------------------------------------------------------------ resources
struct ResourceID
{
    uint32_t mTypeID;
    uint32_t mInstanceID;
    uint32_t mGroupID;
};

struct Key
{
    uint32_t mType;      // +0x00
    uint32_t mGroup;     // +0x04
    uint32_t mInstance;  // +0x08
};

// ------------------------------------------------------------------ timers
struct cGonzagoTimer                    // 0x20 bytes
{
    int64_t mElapsedTime;               // +0x00
    int64_t mBaseTime;                  // +0x08
    uint8_t mbRunning;                  // +0x10
    uint8_t pad11[3];
    uint32_t mGetMillisecondTime;       // +0x14
    uint8_t pad18[8];                   // +0x18 (base vtable slot)

    cGonzagoTimer();                    // 0x00b63890
    ~cGonzagoTimer();                   // 0x00b638b0
    void Restart();                     // 0x00bc3130
    cGonzagoTimer& operator=(const cGonzagoTimer& o)
    {
        mElapsedTime = o.mElapsedTime;
        mBaseTime = o.mBaseTime;
        mbRunning = o.mbRunning;
        mGetMillisecondTime = o.mGetMillisecondTime;
        return *this;
    }
};

struct tRecentMission                  // 0x34 bytes
{
    uint32_t      mID;                 // +0x00
    uint32_t      pad04;
    cGonzagoTimer mTime;               // +0x08
    Key           mKey;                // +0x28

    tRecentMission() : mID(0), mTime()
    {
        mKey.mType = 0;
        mKey.mGroup = 0;
        mKey.mInstance = 0;
    }
};

struct ListAnchor
{
    void* mpNext;      // +0x00
    void* mpPrev;      // +0x04
    void Ctor();                        // 0x00fecb20
    void Add(tRecentMission* v);        // 0x00fecfc0
};

extern Key kZeroKey;                    // 0x016dac78 (zero-initialized Key constant)
extern uint32_t kMinusOne;              // 0x014948cc (0xffffffff constant)
struct RecentNode { void* mpNext; void* mpPrev; tRecentMission mValue; };

// ------------------------------------------------------------------ game data plumbing
void GameData_cd7d10();  // 0x00cd7d10
void GameData_d3d420();  // 0x00d3d420
void GameData_fed010();  // 0x00fed010
void GameData_b1e520();  // 0x00b1e500 / 0x00b1e520

typedef void (*GameDataFn)();

struct GameDataList
{
    cGameData** mpBegin;     // +0x04
    cGameData** mpEnd;       // +0x08
    cGameData** mpCapacity;  // +0x0c
    void*       mAllocator;  // +0x10
};

struct GameDataVector
{
    uint32_t mbDirty;        // +0x00
    GameDataList mData;      // +0x04
};

class cGameData
{
public:
    PV2 PV                                    // +0x00..+0x08
    virtual void* Cast(uint32_t type);        // +0x0c (0x463329e -> cSPMission)
    PV16 PV8 PV4                              // +0x10..+0x7c
    virtual void g80();                       // +0x80
};

struct cGameNounManager
{
    GameDataVector* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d,
                                      uint32_t type);            // 0x00b21340
    void RemoveNoun(void* noun);                                 // 0x00b225d0
};

cGameNounManager* NounManager();               // 0x00b3d300
void*             SimTicker();                 // 0x00b3d330

// the sim ticker's vtable slot 0x50 is a thiscall that pops its single argument
struct cSimTicker
{
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void t30(); virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40(); virtual void t44(); virtual void t48(); virtual void t4c();
    virtual void RegisterMissionManager(void* mgr);   // +0x50
};
void*             StarManager();               // 0x00b3d2a0
void*             GetPlayerEmpire();           // 0x01021300
void*             GetPlayerHomePlanet();       // 0x01021370

// 0x00d01790 is a __thiscall on the vector (ecx), taking the desired size on the stack
struct cVectorMapper { void Assign(uint32_t n); };
void* MapPlanetRecordToKey(void* planetRecord);         // 0x00b8d8e0

// 0x00b8d8e0 is a __thiscall on the planet record (ecx), no stack arguments.
struct TC_PlanetRec { Key* MapToKey(); };
// a planet (returned by GetSourcePlanet/GetTargetPlanet) holds a record pointer at +0x13c
struct cPlanet
{
    uint32_t      pad00[0x13c / 4];   // +0x00
    TC_PlanetRec* mpRecord;           // +0x13c
};
void* GetEmpirePropList(void* empire);                  // 0x00baf700
uint32_t GetStarEmpireID(void* starManager, void* star);// 0x00885c90
struct cMissionRequisitesParser
{
    void FillList(void* out);                           // 0x00fef9f0
};
void* MakeRequisiteParser();                            // 0x00fef670
void* __stdcall MakeRequisiteParser(uint32_t id);       // 0x00fef670
void  __stdcall SetSerializer(void* parser, int zero);  // 0x00c2e4e0
struct cSerializerParser { void SetSerializer(); };     // 0x00c2e4e0 (thiscall, no args)

void  operator delete(void* p);                         // 0x00f47380 (scalar deleting dtor helper)
void* EAAllocate(int size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0
void  MessageBasicRCDtor(void* msg);                    // 0x00421cf0

// serial stream reader
void ReadInt32(void* reader, void* dst, int count, int flag);   // 0x0093a780

// serial stream: slot +0x18 yields a reader, +0x1c flushes, +0x20 yields the stream
struct cSerialStream
{
    virtual void  v00(); virtual void  v04(); virtual void  v08(); virtual void  v0c();
    virtual void  v10(); virtual void  v14();
    virtual void* v18();      // +0x18
    virtual void  v1c();      // +0x1c
    virtual void* v20();      // +0x20
};

struct cVarListSerializer
{
    void* mpValue;
    void* mpStream;      // +0x04
    void* mpVtbl0;       // +0x08
    uint32_t mFlags;     // +0x0c
    uint32_t mFlags2;    // +0x10
    uint8_t  mByte;      // +0x14
    uint32_t mDword;     // +0x18
    uint32_t mDword2;    // +0x1c
    uint32_t mDword3;    // +0x20
    uint32_t mDword4;    // +0x24

    cVarListSerializer(void* value, void* stream, uint32_t id);   // 0x00692f90
    bool Serialize(void* stream);                                 // 0x00693e10
};

struct MissionStateMap
{
    uint32_t* operator[](const uint32_t& key);   // 0x00643a40
};

struct MessageBasicRC5
{
    uint32_t vftable0;    // +0x00
    volatile long mRefCount;   // +0x04
    uint32_t mData[10];   // +0x08 (mUint32[5])
    uint32_t mId;         // +0x30
    uint32_t mPad34;      // +0x34 (never written)
    uint32_t mRCFlags;    // +0x38
    void*    pad3c;       // +0x3c
};

// destructor of MessageBasicRC<5> (0x00421cf0): __thiscall, no stack args
struct MsgRCDtor { void Destroy(); };

// message server: the send method is vtable slot +0x14 (index 5), __thiscall
struct cMessageServer
{
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void v0c(); virtual void v10();
    virtual void Send(uint32_t id, void* msg, int flag);   // +0x14
};
cMessageServer* MessageServer();                            // 0x0067dcc0

struct Record38
{
    uint32_t mWord0;      // +0x00
    uint32_t mWord1;      // +0x04
    SPVector<float> mVecA;  // +0x08 (0x14)
    SPVector<float> mVecB;  // +0x1c (0x14)
    uint32_t mWord30;     // +0x30
    uint32_t mWord34;     // +0x34
};



// serializer constructor helper stream constant
extern uint32_t kSerializerStream;    // 0x015b49b0

// weight curve constants used by the recent-mission list scans
extern float g_fWeightScale;          // 0x01488874
extern float g_fWeightBase;           // 0x013f9428

extern char g_cVarListSerializerVtbl;      // 0x01465d54
extern char g_cVarListSerializerVtbl2;     // 0x01464450
extern char g_MessageBasicRCvftable;       // 0x013eb90c
extern char g_MessageRCvftable;            // 0x013eb844

// ------------------------------------------------------------------ cSPMission
struct cSPMission
{
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void* Cast(uint32_t type);                       // +0x0c (0x463329e -> cSPMission)
    virtual void vf10(); virtual void vf14(); virtual void vf18(); virtual void vf1c();
    virtual void vf20(); virtual void vf24(); virtual void vf28(); virtual void vf2c();
    virtual void vf30(); virtual void vf34(); virtual void vf38(); virtual void vf3c();
    virtual void vf40(); virtual void vf44(); virtual void vf48(); virtual void vf4c();
    virtual void vf50(); virtual void vf54(); virtual void vf58(); virtual void vf5c();
    virtual void vf60(); virtual void vf64(); virtual void vf68(); virtual void vf6c();
    virtual void vf70(); virtual void vf74(); virtual void vf78(); virtual void vf7c();
    virtual void vf80(); virtual void vf84(); virtual void vf88(); virtual void vf8c();
    virtual void vf90(); virtual void vf94(); virtual void vf98(); virtual void vf9c();
    virtual void vfa0(); virtual void vfa4(); virtual void vfa8(); virtual void vfac();
    virtual void vfb0(); virtual void vfb4(); virtual void vfb8(); virtual void vfbc();
    virtual void vfc0(); virtual void vfc4(); virtual void vfc8(); virtual void vfcc();
    virtual void vfd0(); virtual void vfd4(); virtual void vfd8(); virtual void vfdc();
    virtual void vfe0(); virtual void vfe4(); virtual void vfe8(); virtual void vfec();
    virtual void vff0();                                     // +0xf0 (115)
    virtual bool vff4(void* a);                              // +0xf4 (116)
    virtual bool vff8();                                     // +0xf8
    virtual void vffc();
    virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c();
    virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c();
    virtual void v120(); virtual void v124(); virtual void v128(); virtual void v12c();
    virtual void v130(); virtual void v134(); virtual void v138(); virtual void v13c();
    virtual bool Query140(void* a, void* b);                 // +0x140
    virtual void v144(); virtual void v148(); virtual void v14c(); virtual void v150();
    virtual void v154(); virtual void v158(); virtual void v15c(); virtual void v160();
    virtual void v164(); virtual void v168(); virtual void v16c(); virtual void v170();
    virtual void SetTargetPlanet(void* planet);              // +0x174

    uint32_t pad04[0x130 / 4 - 1];                           // +0x04 (vptr at +0x00)
    uint8_t  mbEventFlag;                                    // +0x130 (bit 0)
    uint8_t  pad131[3];
    char     pad134[0x17c - 0x134];
    cSPMission* mpParentMission;                             // +0x17c

    cSPMission* GetSourcePlanet();                           // 0x00c45ce0
    void*       GetOwnerEmpire();                            // 0x00c451e0
    int         GetMissionID();                              // 0x01030e10
    void*       GetTargetPlanet();                           // 0x00970b30
    bool        IsActive();                                  // 0x00c44c80
    void        SP_CacheLocalizedStrings();                     // 0x00c44f50
};

void SP_CacheLocalizedStrings();   // 0x00c44f50

// ------------------------------------------------------------------ cSPMissionManager
struct cSPMissionManager
{
    char  pad00[0x14];
    bool  mbDebugDraw;            // +0x14
    bool  mbDebugFlag;            // +0x15
    bool  mbFlightSchoolFinished; // +0x16
    char  pad17;
    uint32_t mCheatMissionIDOverride;   // +0x18
    uint32_t mNextMissionID;            // +0x1c
    SPVector<void*> mTutorialMissionReqList;  // +0x20
    SPVector<void*> mNPCMissionReqList;       // +0x34
    SPVector<void*> mColonyMissionReqList;    // +0x48
    void*    mTutorialMissionStates;          // +0x5c (map, 0x1c)
    void*    pad60[6];                        // +0x60 .. +0x78
    cPropertyList* mpProperties;              // +0x78 (intrusive ptr)
    void*    pad7c;                           // +0x7c
    SPVector<uint32_t> mTutorialTargetPlanetKeys;  // +0x80
    SPVector<Key>      mTutorialSpeciesIDs;        // +0x94
    SPVector<AutoRefCount> mTrackedMissions;       // +0xa8
    char     padbc[0xc8 - 0xbc];
    ListAnchor mRecentColonyMissions;         // +0xc8
    void*      padc8_4;                       // +0xd0
    ListAnchor mRecentNPCMissions;            // +0xd4
    char     pade0[0x17c - 0xe0];

    // named methods
    uint32_t GetMissionWeightForColony(uint32_t key);          // 0x00fed430
    uint32_t GetMissionWeightForEmpire(void* empire, uint32_t key);  // 0x00fed640
    void*    GetMissionList();                                 // 0x00fedd50
    int      GetNumNonEventMissions(char includeEventChildren); // 0x00fedd80
    int      GetNumEventMissions();                            // 0x00feddf0
    bool     DoMissionsPreventHostility(void* a, void* b);     // 0x00fedea0
    void     SetTutorialMissionState1(uint32_t id);            // 0x00fede40
    void     SetTutorialMissionState2(uint32_t id);            // 0x00fede60
    void     SetTutorialMissionState3(uint32_t id);            // 0x00fede80
    float    FindListWeightA(uint32_t missionID);              // 0x00fedf20
    float    FindListWeightB(uint32_t missionID);              // 0x00fedfe0
    void     ForEachActiveSetTargetPlanet(void* planet);       // 0x00fee0a0
    bool     AnyActiveMatchA(void* a);                         // 0x00fee110
    bool     AnyActiveMatchB(void* a);                         // 0x00fee190
    cSPMission* FindMissionByTargetPlanet(void* planetRecord);  // 0x00fee220
    void     AddRecentMissionA(cSPMission* m, bool restart);   // 0x00fed890
    void     RemoveMissionInternal(cSPMission* m);             // 0x00febe00
    void     InitForGame();                                    // 0x00fedb50
    bool     RemoveMission(cSPMission* m);                     // 0x00fedca0
    void     PostLoad();                                       // 0x00fee310
    void     CacheProperties();                                // 0x00fed0b0
};

// another game-data subobject used by cSPMissionManager::RemoveMission (vtable+0x174 target)
struct cMissionTargetObj
{
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28(); virtual void t2c();
    virtual void t30(); virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40(); virtual void t44(); virtual void t48(); virtual void t4c();
    virtual void t50(); virtual void t54(); virtual void t58(); virtual void t5c();
    virtual void t60(); virtual void t64(); virtual void t68(); virtual void t6c();
    virtual void t70(); virtual void t74(); virtual void t78(); virtual void t7c();
    virtual void t80(); virtual void t84(); virtual void t88(); virtual void t8c();
    virtual void t90(); virtual void t94(); virtual void t98(); virtual void t9c();
    virtual void ta0(); virtual void ta4(); virtual void ta8(); virtual void tac();
    virtual void tb0(); virtual void tb4(); virtual void tb8(); virtual void tbc();
    virtual void tc0(); virtual void tc4(); virtual void tc8(); virtual void tcc();
    virtual void td0(); virtual void td4(); virtual void td8(); virtual void tdc();
    virtual void te0(); virtual void te4(); virtual void te8(); virtual void tec();
    virtual void tf0(); virtual void tf4(); virtual void tf8(); virtual void tfc();
    virtual void t100(); virtual void t104(); virtual void t108(); virtual void t10c();
    virtual void t110(); virtual void t114(); virtual void t118(); virtual void t11c();
    virtual void t120(); virtual void t124(); virtual void t128(); virtual void t12c();
    virtual void t130(); virtual void t134(); virtual void t138(); virtual void t13c();
    virtual void t140(); virtual void t144(); virtual void t148(); virtual void t14c();
    virtual void t150(); virtual void t154(); virtual void t158(); virtual void t15c();
    virtual void t160(); virtual void t164(); virtual void t168(); virtual void t16c();
    virtual void t170();
};

// 0x00fecb20 helper used by 0x00feda00
void InitList(void* anchor) { ((ListAnchor*)anchor)->Ctor(); }

// @ 0x00fed430
uint32_t cSPMissionManager::GetMissionWeightForColony(uint32_t key)
{
    cPropertyList*& props = *(cPropertyList**)&mpProperties;
    cPropertyList* localProps = mpProperties;
    if (localProps == 0)
    {
        cPropertyList* pm = PropertyManager();
        localProps = mpProperties;
        if (localProps)
        {
            mpProperties = 0;
            ((RefCounted*)localProps)->Release();
            props = 0;
        }
        pm->GetProperty2(0x1254b050, 0x2ae1a8e, &mpProperties);
        localProps = mpProperties;
    }

    uint32_t* keysBegin = 0; uint32_t* keysEnd = 0; uint32_t* keysCap = 0;
    Property* prop = localProps->GetProperty(0x3f3fa37);
    ((cVectorMapper*)&keysBegin)->Assign(prop->mnFlags & 0x30 ? prop->mnCount
                                                       : (uint32_t)(prop->mnType != 0));
    uint32_t* keys = (uint32_t*)prop->GetValuePtr();
    uint32_t count = prop->mnFlags & 0x30 ? prop->mnCount
                                          : (uint32_t)(prop->mnType != 0);
    if (count > 0)
    {
        uint32_t n = count;
        uint32_t* slot = keysBegin;
        uint32_t* cap = keysEnd;
        do
        {
            uint32_t v = *keys;
            if (slot < cap)
            {
                uint32_t* nxt = slot + 1;
                keysBegin = nxt;
                if (slot)
                    *slot = v;
            }
            else
            {
                ((SPVector<uint32_t>*)&keysBegin)->DoInsertKey4(slot, v);
            }
            keys += 3;
            --n;
        } while (n);
    }

    uint32_t* weightsBegin = 0; uint32_t* weightsEnd = 0; uint32_t* weightsCap = 0;
    Property* prop2 = localProps->GetProperty(0x3f3fa44);
    uint32_t wcount = prop2->mnFlags & 0x30 ? prop2->mnCount
                                            : (uint32_t)(prop2->mnType != 0);
    ((SPVector<uint32_t>*)&weightsBegin)->reserve(wcount);
    uint32_t* wsrc = (uint32_t*)prop2->GetValuePtr();
    if (wcount > 0)
    {
        uint32_t n = wcount;
        uint32_t* slot = weightsBegin;
        uint32_t* cap = weightsEnd;
        do
        {
            if (slot < cap)
            {
                uint32_t* nxt = slot + 1;
                weightsBegin = nxt;
                if (slot)
                    *slot = *wsrc;
            }
            else
            {
                ((SPVector<uint32_t>*)&weightsBegin)->DoInsertValueI(slot, *wsrc);
            }
            ++wsrc;
            --n;
        } while (n);
    }

    uint32_t* keysData = keysBegin;
    uint32_t* weightsData = weightsBegin;
    for (uint32_t i = 0; i < count; ++i)
    {
        if (keys[i] == key)
        {
            if (i == 0xffffffffu)
                break;
            uint32_t result = weightsData[i];
            if (weightsBegin && weightsBegin[-1] != 0)
                operator delete(weightsBegin);
            if (keysBegin && keysBegin[-1] != 0)
                operator delete(keysBegin);
            return result;
        }
    }

    if (weightsBegin && weightsBegin[-1] != 0)
        operator delete(weightsBegin);
    if (keysBegin && keysBegin[-1] != 0)
        operator delete(keysBegin);
    return 0;
}

// @ 0x00fed640
uint32_t cSPMissionManager::GetMissionWeightForEmpire(void* empire, uint32_t key)
{
    cPropertyList*& props = *(cPropertyList**)&mpProperties;
    cPropertyList* localProps = mpProperties;
    if (localProps == 0)
    {
        cPropertyList* pm = PropertyManager();
        localProps = mpProperties;
        if (localProps)
        {
            mpProperties = 0;
            ((RefCounted*)localProps)->Release();
            props = 0;
        }
        pm->GetProperty2(0x1254b050, 0x2ae1a8e, &mpProperties);
        localProps = mpProperties;
    }

    uint32_t* keysBegin = 0; uint32_t* keysEnd = 0; uint32_t* keysCap = 0;
    Property* prop = localProps->GetProperty(0x3f3fa37);
    uint32_t count = prop->mnFlags & 0x30 ? prop->mnCount
                                          : (uint32_t)(prop->mnType != 0);
    ((SPVector<uint32_t>*)&keysBegin)->reserve(count);
    uint32_t* keys = (uint32_t*)prop->GetValuePtr();
    if (count > 0)
    {
        uint32_t n = count;
        uint32_t* slot = keysBegin;
        uint32_t* cap = keysEnd;
        do
        {
            uint32_t v = *keys;
            if (slot < cap)
            {
                uint32_t* nxt = slot + 1;
                keysBegin = nxt;
                if (slot)
                    *slot = v;
            }
            else
            {
                ((SPVector<uint32_t>*)&keysBegin)->DoInsertKey4(slot, v);
            }
            keys += 3;
            --n;
        } while (n);
    }

    uint32_t propID = 0x5760d54;
    uint32_t* ep = (uint32_t*)empire;
    if (ep[0x84 / 4] != GetStarEmpireID(StarManager(), 0))
    {
        if (ep[0x5c / 4] != ep[0x60 / 4])
            propID = 0x5760d66;
        else if (ep[0x70 / 4] != ep[0x74 / 4])
            propID = 0x5760d6d;
    }

    cPropertyList* empireProps = (cPropertyList*)GetEmpirePropList(empire);

    uint32_t* weightsBegin = 0; uint32_t* weightsEnd = 0; uint32_t* weightsCap = 0;
    if (propID != 0 && empireProps != 0)
    {
        Property* prop2 = empireProps->GetProperty(propID);
        uint32_t wcount = prop2->mnFlags & 0x30 ? prop2->mnCount
                                                : (uint32_t)(prop2->mnType != 0);
        ((SPVector<uint32_t>*)&weightsBegin)->reserve(wcount);
        uint32_t* wsrc = (uint32_t*)prop2->GetValuePtr();
        if (wcount > 0)
        {
            uint32_t n = wcount;
            uint32_t* slot = weightsBegin;
            uint32_t* cap = weightsEnd;
            do
            {
                if (slot < cap)
                {
                    uint32_t* nxt = slot + 1;
                    weightsBegin = nxt;
                    if (slot)
                        *slot = *wsrc;
                }
                else
                {
                    ((SPVector<uint32_t>*)&weightsBegin)->DoInsertValueI(slot, *wsrc);
                }
                ++wsrc;
                --n;
            } while (n);
        }

        uint32_t* keysData = keysBegin;
        uint32_t* weightsData = weightsBegin;
        for (uint32_t i = 0; i < count; ++i)
        {
            if (keys[i] == key)
            {
                if (i == 0xffffffffu)
                    break;
                uint32_t result = weightsData[i];
                if (weightsBegin && weightsBegin[-1] != 0)
                    operator delete(weightsBegin);
                if (keysBegin && keysBegin[-1] != 0)
                    operator delete(keysBegin);
                return result;
            }
        }
    }

    if (weightsBegin && weightsBegin[-1] != 0)
        operator delete(weightsBegin);
    if (keysBegin && keysBegin[-1] != 0)
        operator delete(keysBegin);
    return 0;
}

// @ 0x00fed890
void cSPMissionManager::AddRecentMissionA(cSPMission* mission, bool restart)
{
    if (!mission->GetOwnerEmpire())
        return;
    if (!mission->GetSourcePlanet())
        return;

    if (((cPlanet*)mission->GetSourcePlanet())->mpRecord == (TC_PlanetRec*)GetPlayerHomePlanet())
        return;

    tRecentMission entry;
    entry.mID = mission->GetMissionID();

    Key* key = ((cPlanet*)mission->GetSourcePlanet())->mpRecord->MapToKey();
    entry.mKey.mType = key->mType;
    entry.mKey.mGroup = key->mGroup;
    entry.mKey.mInstance = key->mInstance;

    if (restart)
        entry.mTime.Restart();

    if (mission->GetOwnerEmpire() == GetPlayerEmpire())
        mRecentNPCMissions.Add(&entry);
    else
        mRecentColonyMissions.Add(&entry);

    // trim the NPC list to 10 entries (from the tail)
    while (true)
    {
        RecentNode* node = (RecentNode*)mRecentNPCMissions.mpNext;
        uint32_t n = 0;
        if (node == (RecentNode*)&mRecentNPCMissions)
            break;
        do { node = (RecentNode*)node->mpNext; ++n; } while (node != (RecentNode*)&mRecentNPCMissions);
        if (n <= 10)
            break;
        RecentNode* victim = (RecentNode*)mRecentNPCMissions.mpPrev;
        *(void**)victim->mpPrev = victim->mpNext;
        *(void**)((char*)victim->mpNext + 4) = victim->mpPrev;
        victim->mValue.mTime.~cGonzagoTimer();
        operator delete(victim);
    }

    // trim the colony list to 10 entries (from the tail)
    while (true)
    {
        RecentNode* node = (RecentNode*)mRecentColonyMissions.mpNext;
        uint32_t n = 0;
        if (node == (RecentNode*)&mRecentColonyMissions)
            break;
        do { node = (RecentNode*)node->mpNext; ++n; } while (node != (RecentNode*)&mRecentColonyMissions);
        if (n <= 10)
            break;
        RecentNode* victim = (RecentNode*)mRecentColonyMissions.mpPrev;
        *(void**)victim->mpPrev = victim->mpNext;
        *(void**)((char*)victim->mpNext + 4) = victim->mpPrev;
        victim->mValue.mTime.~cGonzagoTimer();
        operator delete(victim);
    }
}

// @ 0x00feda00
void RecentListRead(void* stream, ListAnchor* anchor)
{
    anchor->Ctor();
    anchor->mpNext = anchor;
    anchor->mpPrev = anchor;

    uint32_t count = 0;
    cSerialStream* s = (cSerialStream*)stream;
    cSerialStream* strm = (cSerialStream*)s->v20();
    void* reader = strm->v18();
    ReadInt32(reader, &count, 1, 0);

    for (uint32_t i = 0; i < count; ++i)
    {
        tRecentMission value;

        cVarListSerializer ser(&value, &kSerializerStream, 0x1a80d26);
        ser.Serialize(stream);

        RecentNode* node = (RecentNode*)EAAllocate(
            0x40, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
        if (node)
        {
            node->mValue = value;
            node->mpNext = anchor;
            node->mpPrev = anchor->mpPrev;
            *(void**)anchor->mpPrev = node;
            anchor->mpPrev = node;
        }
        value.mTime.~cGonzagoTimer();
    }

    s->v1c();
}

// @ 0x00fedb50
void cSPMissionManager::InitForGame()
{
    ((cSimTicker*)SimTicker())->RegisterMissionManager(this);

    CacheProperties();

    ((cSerializerParser*)MakeRequisiteParser())->SetSerializer();
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x6b5005e))->FillList(&mTutorialMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x994d1f83))->FillList(&mNPCMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0xa07f6fd6))->FillList(&mColonyMissionReqList);

    SP_CacheLocalizedStrings();

    mbFlightSchoolFinished = true;

    SPVector<uint32_t>& planetKeys = mTutorialTargetPlanetKeys;
    for (int i = 2; i != 0; --i)
    {
        uint32_t* slot = planetKeys.mpEnd;
        if (slot < planetKeys.mpCapacity)
        {
            planetKeys.mpEnd = slot + 1;
            if (slot)
                *slot = 0xffffffffu;
        }
        else
        {
            planetKeys.DoInsertValueI(slot, kMinusOne);
        }
    }
    SPVector<Key>& speciesIDs = mTutorialSpeciesIDs;
    for (int i = 2; i != 0; --i)
    {
        Key* slot = speciesIDs.mpEnd;
        if (slot < speciesIDs.mpCapacity)
        {
            speciesIDs.mpEnd = slot + 1;
            if (slot)
                *slot = kZeroKey;
        }
        else
        {
            speciesIDs.DoInsertKey(slot, kZeroKey);
        }
    }
    SPVector<AutoRefCount>& tracked = mTrackedMissions;
    for (int i = 3; i != 0; --i)
    {
        AutoRefCount zero;
        AutoRefCount* slot = tracked.mpEnd;
        if (slot < tracked.mpCapacity)
        {
            tracked.mpEnd = slot + 1;
            if (slot)
                slot->mpObject = 0;
        }
        else
        {
            tracked.DoInsertPtr(slot, zero);
        }
    }
}


// @ 0x00fedca0
bool cSPMissionManager::RemoveMission(cSPMission* mission)
{
    if (mission->mpParentMission == 0)
        AddRecentMissionA(mission, true);

    RemoveMissionInternal(mission);

    if (mission->mpParentMission == 0)
    {
        MessageBasicRC5 msg;
        msg.mId = 0x38cf2ff;
        msg.vftable0 = 0x13eb90c;
        _InterlockedExchange((volatile long*)&msg.mRefCount, 0);
        msg.vftable0 = 0x13eb844;
        msg.mRCFlags = 0;
        *(void**)&msg.mData = mission;
        cMessageServer* server = MessageServer();
        server->Send(msg.mId, &msg, 0);
        ((MsgRCDtor*)&msg)->Destroy();
    }

    cGameNounManager* nouns = NounManager();
    if (nouns)
    {
        nouns->RemoveNoun(mission);
        return true;
    }
    return false;
}

// @ 0x00fedd50
void* cSPMissionManager::GetMissionList()
{
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    return (char*)vec + 4;
}

// @ 0x00fedd80
int cSPMissionManager::GetNumNonEventMissions(char includeEventChildren)
{
    int n = 0;
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    cGameData** it = list.mpBegin;
    cGameData** end = list.mpEnd;
    for (; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (!m)
            continue;
        if ((m->mbEventFlag & 1) != 0)
            continue;
        if (m->mpParentMission != 0 && !includeEventChildren)
            continue;
        ++n;
    }
    return n;
}

// @ 0x00feddf0
int cSPMissionManager::GetNumEventMissions()
{
    int n = 0;
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    cGameData** it = list.mpBegin;
    cGameData** end = list.mpEnd;
    for (; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (m && (m->mbEventFlag & 1) != 0)
            ++n;
    }
    return n;
}

// @ 0x00fede40
void cSPMissionManager::SetTutorialMissionState1(uint32_t id)
{
    MissionStateMap* states = (MissionStateMap*)(char*)&mTutorialMissionStates;
    uint32_t key = id;
    *states->operator[](key) = 1;
}

// @ 0x00fede60
void cSPMissionManager::SetTutorialMissionState2(uint32_t id)
{
    MissionStateMap* states = (MissionStateMap*)(char*)&mTutorialMissionStates;
    uint32_t key = id;
    *states->operator[](key) = 2;
}

// @ 0x00fede80
void cSPMissionManager::SetTutorialMissionState3(uint32_t id)
{
    MissionStateMap* states = (MissionStateMap*)(char*)&mTutorialMissionStates;
    uint32_t key = id;
    *states->operator[](key) = 3;
}

// @ 0x00fedea0
bool cSPMissionManager::DoMissionsPreventHostility(void* a, void* b)
{
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    int count = (int)(list.mpEnd - list.mpBegin);
    for (int i = 0; i < count; ++i)
    {
        cSPMission* m = (cSPMission*)list.mpBegin[i];
        if (m->Query140(a, b))
            return true;
    }
    return false;
}

// @ 0x00fedf20
float cSPMissionManager::FindListWeightA(uint32_t missionID)
{
    RecentNode* node = (RecentNode*)mRecentColonyMissions.mpNext;
    RecentNode* end = (RecentNode*)&mRecentColonyMissions;
    uint32_t index = 0;
    while (node != end)
    {
        tRecentMission* rec = &node->mValue;
        if (rec && rec->mID == missionID)
            return (float)(int)index * g_fWeightScale + g_fWeightBase;
        node = (RecentNode*)node->mpNext;
        ++index;
    }

    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (m->IsActive() && m->GetMissionID() == missionID)
            return g_fWeightBase;
    }
    return 1.0f;
}

// @ 0x00fedfe0
float cSPMissionManager::FindListWeightB(uint32_t missionID)
{
    RecentNode* node = (RecentNode*)mRecentNPCMissions.mpNext;
    RecentNode* end = (RecentNode*)&mRecentNPCMissions;
    uint32_t index = 0;
    while (node != end)
    {
        tRecentMission* rec = &node->mValue;
        if (rec && rec->mID == missionID)
            return (float)(int)index * g_fWeightScale + g_fWeightBase;
        node = (RecentNode*)node->mpNext;
        ++index;
    }

    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (m->IsActive() && m->GetMissionID() == missionID)
            return g_fWeightBase;
    }
    return 1.0f;
}

// @ 0x00fee0a0
void cSPMissionManager::ForEachActiveSetTargetPlanet(void* planet)
{
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (m && m->IsActive())
            m->SetTargetPlanet(planet);
    }
}

// @ 0x00fee110
bool cSPMissionManager::AnyActiveMatchA(void* a)
{
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (m && m->IsActive() && m->vff4(a))
            return true;
    }
    return false;
}

// @ 0x00fee190
bool cSPMissionManager::AnyActiveMatchB(void* a)
{
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cSPMission* m = (cSPMission*)*it;
        if (m && m->IsActive() && (m->mbEventFlag & 1) != 0 && m->vff4(a))
            return true;
    }
    return false;
}

// @ 0x00fee220
cSPMission* cSPMissionManager::FindMissionByTargetPlanet(void* planetRecord)
{
    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cGameData* obj = *it;
        if (!obj)
            continue;
        cSPMission* m = (cSPMission*)obj->Cast(0x463329e);
        if (!m)
            continue;
        void* target = m->GetTargetPlanet();
        if (!target)
            continue;
        if (!mbDebugFlag && ((cPlanet*)target)->mpRecord != (TC_PlanetRec*)planetRecord)
            continue;
        return m;
    }
    return 0;
}

// @ 0x00fee2b0
Record38* CopyRecords(Record38* first, Record38* last, Record38* dest)
{
    if (first == last)
        goto done;
    for (; first != last; first += 1, dest += 1)
    {
        dest->mWord0 = first->mWord0;
        dest->mWord1 = first->mWord1;
        dest->mVecA.assign(&first->mVecA);
        dest->mVecB.assign(&first->mVecB);
        dest->mWord30 = first->mWord30;
        dest->mWord34 = first->mWord34;
    }
done:
    return dest;
}

// @ 0x00fee310
void cSPMissionManager::PostLoad()
{
    ((cSimTicker*)SimTicker())->RegisterMissionManager(this);

    CacheProperties();

    ((cSerializerParser*)MakeRequisiteParser())->SetSerializer();
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x6b5005e))->FillList(&mTutorialMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0x994d1f83))->FillList(&mNPCMissionReqList);
    ((cMissionRequisitesParser*)MakeRequisiteParser(0xa07f6fd6))->FillList(&mColonyMissionReqList);

    SP_CacheLocalizedStrings();

    cGameNounManager* nouns = NounManager();
    GameDataVector* vec = nouns->GetGameDataVector(GameData_cd7d10, GameData_d3d420,
                                                   GameData_fed010, GameData_b1e520, 0x2aa5ada);
    GameDataList& list = vec->mData;
    for (cGameData** it = list.mpBegin, **end = list.mpEnd; it != end; ++it)
    {
        cGameData* obj = *it;
        if (obj)
            obj->g80();
    }
}


