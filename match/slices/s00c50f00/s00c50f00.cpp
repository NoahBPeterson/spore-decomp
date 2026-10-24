// Slice s00c50f00 -- SPGonzago/SPMission.obj: SP::cSPMissionExplore, the "visit the cities" mission
// (constructor, Init, the city-visit effect vector, the minimap icons, tag/progress strings, the
// message handlers and the Update state machine), plus the vector/serializer helpers of that class.
//
// Retail layout: the object is 0x220 bytes.  Three vtable pointers are written by the constructor:
// +0x00 cSPMission main vtable (0x0146e4d8), +0x04 the secondary interface (0x0146f6a0) and +0x34 the
// message-handler sub-object (0x0146e4c4).  The cSPMissionExplore members start at +0x1f0.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

namespace SP {

struct Vec3 {
    float x, y, z;
};

// the reference-returning minimum the retail code inlines as a compare plus a stack temp
template <class T>
const T& sp_min(const T& a, const T& b)
{
    return b < a ? b : a;
}

// Unnamed-slot filler used to reach the high retail vtable slots.
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct IEmpty {};

struct cProperty;
struct cPropertyList;
struct cCity;
struct cPlanet;
struct cPlanetRecord;
struct cPlayerInventory;
struct tCityVisitInfo;

// ---------------------------------------------------------------------------------------------
// property bags
// ---------------------------------------------------------------------------------------------
struct cProperty {
    uint8_t   pad00[0x12];
    uint16_t  mType;                 // +0x12 value type: 1 bool, 9 int, 10 uint32, 13 float
    bool*     GetBool();             // 0x0041e920
    float*    GetFloat();            // 0x0041ea70
    int*      GetInt();              // 0x0041e990
    uint32_t* GetUInt();             // 0x0041ea00
};

// slot 0x24 of the property list resolves a hashed key to its property record; the list object
// itself is the virtual interface (its vtable pointer is its first word).
struct cPropertyList : VPad<9, IEmpty> {
    virtual bool GetProperty(uint32_t key, cProperty** out);   // 0x24
};

void __cdecl GetPropertyAsKeyInstance(cPropertyList* list, uint32_t key, uint32_t* out);   // 0x006a12a0

// ---------------------------------------------------------------------------------------------
// cSPMission interfaces (only the slots this slice calls are named)
// ---------------------------------------------------------------------------------------------
// main vtable 0x0146e4d8
struct IMission0 : VPad<27, IEmpty> {
    virtual void StartCompletedFeedbackTimer();              // 0x06c  0x00c47440
};
struct IMission1 : VPad<46, IMission0> {
    virtual bool SetupTargetPlanet();                        // 0x128  0x00c470a0
};
struct IMission2 : VPad<8, IMission1> {
    virtual void AddMessageHandler(uint32_t message);        // 0x14c  0x00c490e0
};
struct IMission3 : IMission2 {
    virtual void RemoveMessageHandler(uint32_t message);     // 0x150  0x00c48ba0
};
struct IMission4 : VPad<6, IMission3> {
    virtual void PreInit();                                  // 0x16c  0x00c2e4e0 (empty)
};
struct IMissionVtbl : IMission4 {
    virtual void DataExportOnInit();                         // 0x170  0x00c483d0
};

// message-handler sub-object vtable 0x0146e4c4 (stored at mission+0x34, slot 1 is overridden here)
struct IMissionHandler {
    virtual void* slot00();                                  // 0x00c5bcf0
    virtual bool  HandleMessage(uint32_t message, void* data);   // 0x04  0x00c51b10
    virtual void  slot08();                                  // 0x00b20170
    virtual void  slot0c();                                  // 0x00c406d0
};

struct ISecondaryVtbl;                                       // opaque, 0x0146f6a0

extern IMissionVtbl        g_vtblMissionExplore;             // 0x0146e4d8
extern ISecondaryVtbl      g_vtblMissionSecondary;           // 0x0146f6a0
extern IMissionHandler     g_vtblMissionHandler;             // 0x0146e4c4

// ---------------------------------------------------------------------------------------------
// strings / misc helpers
// ---------------------------------------------------------------------------------------------
struct WString {                     // eastl::basic_string<wchar_t, eastl::allocator>
    wchar_t* mpBegin;                // +0x00
    wchar_t* mpEnd;                  // +0x04
    wchar_t* mpCapacity;             // +0x08
    void RangeInitialize(const wchar_t* text);      // 0x00579a90
    void ConstructFrom(const WString* other);       // 0x0056e2d0
};

void  __cdecl ConvertToString16(WString* out, const char* text, int length);   // 0x0093c5a0
WString* __cdecl WStr_Format(WString* out, const wchar_t* format, ...);        // 0x0041e050
void  __cdecl EASTLFreeArray(void* block);                                     // 0x00f47380
void* __cdecl EASTLAlloc(uint32_t size, const char* name, int a, int b, const char* file, int line);  // 0x00f473a0

extern wchar_t       g_fmtProgress[];    // 0x0146e428 L"%d/%d"
extern wchar_t       g_fmtDecimal[];     // 0x013f01bc L"%d"
extern const wchar_t g_strList[];        // 0x013f58ac L"list"
extern char          g_allocatorName[];  // 0x013f09b4 "Simulator"
extern char          g_allocatorFile[];  // 0x013ebb38 "allocator.h"

struct tPlanetPick {                 // planet-pick descriptor, 0x44 bytes in retail
    uint32_t mMode;                  // +0x00 (0x3c selects a random planet)
    uint32_t pad04[16];              // +0x04 opaque fill
    void Construct();                // 0x00ba7bd0
    void Destroy();                  // 0x00ba8220
};

// ---------------------------------------------------------------------------------------------
// visited-city records: 0x14-byte elements of cSPMissionExplore::mCityVisitInfo
// ---------------------------------------------------------------------------------------------
struct tCityVisitInfo {
    Vec3     mPosition;              // +0x00
    bool     mbVisited;              // +0x0c
    uint8_t  pad0d;                  // +0x0d
    uint16_t pad0e;                  // +0x0e
    float    mEffectHeight;          // +0x10
};

struct tAllocHeader {                // element count stored in front of every sp_vector block
    uint32_t mCount;
};

struct tCityVisitInfoVector {
    tCityVisitInfo* mpBegin;         // +0x00
    tCityVisitInfo* mpEnd;           // +0x04
    tCityVisitInfo* mpCapacity;      // +0x08
    void Reserve(uint32_t count);                                          // 0x00c51240
    void InsertAtEnd(tCityVisitInfo* position, const tCityVisitInfo* value);  // 0x00c512f0
};

void* __cdecl FUN_00951bf0(tCityVisitInfo* first, tCityVisitInfo* last, tCityVisitInfo* dst);  // 0x00951bf0
void* __cdecl FUN_00c50e70(tCityVisitInfo* first, tCityVisitInfo* last, tCityVisitInfo* dst);  // 0x00c50e70
void __cdecl FUN_00c50ad0(tCityVisitInfo* first, tCityVisitInfo* last, tCityVisitInfo* dstEnd);  // 0x00c50ad0

// ---------------------------------------------------------------------------------------------
// nouns: the city list, a city, a planet
// ---------------------------------------------------------------------------------------------
struct tCityVector {                 // cGameNounManager::GetGameDataVector result (allocator first)
    void*   mpAllocator;             // +0x00
    cCity** mpBegin;                 // +0x04
    cCity** mpEnd;                   // +0x08
};

extern char g_nounTypeKey0[];        // 0x00cd7d10
extern char g_nounTypeKey1[];        // 0x00d3d420
extern char g_nounTypeKey2[];        // 0x00acdff0
extern char g_nounTypeKey3[];        // 0x00b1e500
extern char g_nounAllocator[];       // 0x018c43e8

class cGameNounManager {
 public:
    tCityVector* GetGameDataVector(void* typeKey0, void* typeKey1, void* typeKey2, void* typeKey3,
                                   void* allocator);         // 0x00b21340
    void* UnkAce2c0();                                       // 0x00ace2c0
};
extern "C" cGameNounManager* __cdecl NounManager();          // 0x00b3d300

struct cCitySpatial : VPad<11, IEmpty> {                     // sub-object at cCity+0x120
    virtual const Vec3* GetPosition();                       // 0x02c
};

class cCity {
 public:
    uint8_t      pad000[0x120];
    cCitySpatial mSpatial;           // +0x120
    uint8_t      pad124[0x1dc];
    float        mEffectHeight;      // +0x300
    void SetVisitEffectActive(bool active, float height);    // 0x00bd8380
};

class cPlanet {
 public:
    int  UnkC70e00();                // 0x00c70e00
    bool HasCommContextFlag();       // 0x00c73250
};

class cPlanetRecord {
 public:
    bool UnkBB9d40();                // 0x00bb9d40
};

extern "C" cPlanet*       __cdecl GetActivePlanet();         // 0x01021260
extern "C" cPlanetRecord* __cdecl GetActivePlanetRecord();   // 0x010212a0
extern "C" void*          __cdecl GetUniverseContext();      // 0x01021080
extern "C" cCity*         __cdecl FUN_00ac9dd0(void* nounGroup, const Vec3* position);   // 0x00ac9dd0

class cMinimapProvider;
class cMinimapWin {
 public:
    void RemoveIcon(cCity* city, int a, int b);              // 0x00e0f9c0
};
class cMinimapProvider {
 public:
    cMinimapWin* GetWin();                                   // 0x01067e60
};
extern "C" cMinimapProvider* __cdecl FUN_010666a0();                       // 0x010666a0
extern "C" void __cdecl FUN_01041d50(cCity* city, cMinimapWin* win);       // 0x01041d50

class cPlayerInventory {
 public:
    uint8_t pad000[0x718];
    Vec3    mPlayerPosition;         // +0x718
};
class cSPSimulatorSpaceGame {
 public:
    cPlayerInventory* GetPlayerInventory();                  // 0x00a1ad60
};
extern "C" cSPSimulatorSpaceGame* __cdecl GetUFOSimulator(); // 0x00ffbe50

class RandomLinearCongruential {
 public:
    double RandomDouble();                                   // 0x009360d0
};
extern RandomLinearCongruential g_spRandom;                  // 0x01601760

const Vec3* __cdecl Swarm_Normalize(Vec3* out, const Vec3* in);   // 0x006e6df0

// ---------------------------------------------------------------------------------------------
// serialization: archiver (0x00c51630 reads the record vector through one)
// ---------------------------------------------------------------------------------------------
struct IArchiveWriter : VPad<6, IEmpty> {
    virtual void* GetStream();                               // 0x18
};
struct IArchiver0 : VPad<6, IEmpty> {
    virtual void* GetStream();                               // 0x18
};
struct IArchiver1 : IArchiver0 {
    virtual void* EndRead();                                 // 0x1c
};
struct IArchiver2 : IArchiver1 {
    virtual IArchiveWriter* GetWriter();                     // 0x20
};
typedef IArchiver2 IArchiver;

void __cdecl EA_ReadInt32(void* stream, void* out, int count, int flag);   // 0x0093a780
void* __cdecl FUN_00c50b10(IArchiver* stream, tCityVisitInfo* record);     // 0x00c50b10

// 0x00c51440 writes one "list" section through this writer interface
struct IListWriter {
    virtual void BeginSection(const wchar_t* name);
    virtual void EndSection(const wchar_t* name);
};
char __cdecl FUN_00ac8050(IListWriter* writer, int flag, const tCityVisitInfo* record);  // 0x00ac8050

// ---------------------------------------------------------------------------------------------
// cSPMission -- retail base layout (dev PDB cSPMission + 0x68 for every member)
// The object's own vtable pointer (+0x000, 0x0146e4d8) comes from the IMissionVtbl interface; the
// secondary interface pointer and the message-handler sub-object pointer are plain members.
// ---------------------------------------------------------------------------------------------
class cSPMission : public IMissionVtbl {
 public:
    ISecondaryVtbl*  mpVtblSecondary;    // +0x004  0x0146f6a0
    uint8_t          pad008[0x02c];
    IMissionHandler* mpHandlerVtbl;      // +0x034  0x0146e4c4
    uint8_t          pad038[0x148];
    cPropertyList*   mpMissionPropList;  // +0x180
    uint8_t          pad184[0x06c];      // up to the cSPMissionExplore members at +0x1f0

    void     ConstructBase();                              // 0x00c48e90
    bool     Init();                                       // 0x00c4ad50
    uint32_t ReadTargetPlanetType();                       // 0x00c45b40
    void*    GetPlanetRecordFromTargetType(uint32_t type); // 0x00c474b0
    void     SetTargetPlanetRecord(void* record);          // 0x00c47180
    cPlanet* GetTargetPlanet();                            // 0x00970b30
    void*    PickPlanet(tPlanetPick* pick);                // 0x00c47e20
    void     TriggerUIUpdate();                            // 0x00c47d80
    bool     GetTagString(int tag, WString* out);          // 0x00c491c0
    void     OnAccept();                                   // 0x00c47a10
    void     ShutdownSystems();                            // 0x00c46590
    void     HandleMessage(uint32_t message, void* data);  // 0x00c4a6b0
    int      Update(uint32_t delta);                       // 0x00c478b0
    void     Unk471c0();                                   // 0x00c471c0
    void     Unk472e0();                                   // 0x00c472e0
    void     UnkC2e4e0();                                  // 0x00c2e4e0 (empty)
    void     UnkC44b80();                                  // 0x00c44b80
    void     UnkC44bd0();                                  // 0x00c44bd0
    void     UnkC4a0c0();                                  // 0x00c4a0c0
};

// The three vtable pointers the retail constructor installs, as a named view of the object head
// (the main one is the object's own vtable pointer, the other two are the sub-object pointers).
struct tMissionVtblSlots {
    IMissionVtbl*    mpMain;             // +0x000  0x0146e4d8
    ISecondaryVtbl*  mpSecondary;        // +0x004  0x0146f6a0
    uint8_t          pad008[0x02c];
    IMissionHandler* mpHandler;          // +0x034  0x0146e4c4
};

// ---------------------------------------------------------------------------------------------
// cSPMissionExplore -- retail size 0x220
// ---------------------------------------------------------------------------------------------
class cSPMissionExplore : public cSPMission {
 public:
    enum eExploreMissionState {
        kVisitPlanet = 0,
        kReturnForReward = 1,
    };

    eExploreMissionState mExploreMissionState;   // +0x1f0
    bool      mbVisitCities;                     // +0x1f4
    float     mVisitRadius;                      // +0x1f8
    float     mEffectHeight;                     // +0x1fc
    float     mEffectHeightJitter;               // +0x200
    int       mNumCitiesToVisit;                 // +0x204
    uint32_t  mNumVisitedCities;                 // +0x208
    uint32_t  mExploreType;                      // +0x20c
    bool      mbCityVisitInfoInitialized;        // +0x210
    uint8_t   pad211[3];
    tCityVisitInfoVector mCityVisitInfo;         // +0x214

    cSPMissionExplore* Construct();                                    // 0x00c50f50
    uint32_t GetVisitCountProperty();                                  // 0x00c50f00
    bool     Init();                                                   // 0x00c51010
    WString* GetProgressString(WString* out);                          // 0x00c51590
    bool     GetTagString(int tag, WString* out);                      // 0x00c515c0
    tCityVisitInfo* FindCityRecord(cCity* city);                       // 0x00c50d20
    void     MarkCityVisitedInMiniMap(cCity* city);                    // 0x00c50c30
    void     InitCityEffects();                                        // 0x00c51740
    void     RevertMiniMapIcons();                                     // 0x00c51900
    void     DestroyCityEffects();                                     // 0x00c519a0
    void     OnAccept();                                               // 0x00c51a10
    void     ShutdownSystems();                                        // 0x00c51aa0
    void     ReturnForRewards();                                       // 0x00c51ac0
    void     HandleMessage(uint32_t message, void* data);              // 0x00c51b10
    int      Update(uint32_t delta);                                   // 0x00c51bb0
    void     AbortToRewardState();                                     // 0x00c51e40
    void     AddMessageHandlers();                                     // 0x00c51f90
    void     RemoveMessageHandlers();                                  // 0x00c52000

    tCityVector* Cities()
    {
        return NounManager()->GetGameDataVector(g_nounTypeKey0, g_nounTypeKey1, g_nounTypeKey2,
                                                g_nounTypeKey3, g_nounAllocator);
    }
};

// ---------------------------------------------------------------------------------------------
// 0x00c50f00 -- GetVisitCountProperty: the "cities to visit" override key or the default key
// ---------------------------------------------------------------------------------------------
// @ 0x00c50f00
uint32_t cSPMissionExplore::GetVisitCountProperty()
{
    if (mbVisitCities) {
        uint32_t value = 0;
        cPropertyList* propList = mpMissionPropList;
        cProperty* property;
        if (propList && propList->GetProperty(0x61e37e5f, &property) && property->mType == 10)
            value = *property->GetUInt();
        return value;
    }
    return 0x74bf58cb;
}

// ---------------------------------------------------------------------------------------------
// 0x00c50f50 -- cSPMissionExplore::cSPMissionExplore
// ---------------------------------------------------------------------------------------------
// @ 0x00c50f50
cSPMissionExplore* cSPMissionExplore::Construct()
{
    ConstructBase();
    mExploreMissionState = kVisitPlanet;
    mbVisitCities = false;
    mNumCitiesToVisit = 0;
    mNumVisitedCities = 0;
    mbCityVisitInfoInitialized = false;
    tMissionVtblSlots* vptrs = (tMissionVtblSlots*)this;
    vptrs->mpMain = &g_vtblMissionExplore;
    mpVtblSecondary = &g_vtblMissionSecondary;
    vptrs->mpHandler = &g_vtblMissionHandler;
    mVisitRadius = 0.0f;
    mEffectHeight = 0.0f;
    mEffectHeightJitter = 0.0f;
    mCityVisitInfo.mpBegin = 0;
    mCityVisitInfo.mpEnd = 0;
    mCityVisitInfo.mpCapacity = 0;
    return this;
}

// ---------------------------------------------------------------------------------------------
// 0x00c51010 -- cSPMissionExplore::Init
// ---------------------------------------------------------------------------------------------
// @ 0x00c51010
bool cSPMissionExplore::Init()
{
    if (!cSPMission::Init())
        return false;
    PreInit();

    cProperty* property;
    if (mpMissionPropList && mpMissionPropList->GetProperty(0x55bbd02, &property) && property->mType == 1)
        mbVisitCities = *property->GetBool();

    if (mbVisitCities) {
        uint32_t targetPlanetKey;
        uint32_t targetTypeKey;
        GetPropertyAsKeyInstance(mpMissionPropList, 0x7a2db2dd, &targetPlanetKey);
        GetPropertyAsKeyInstance(mpMissionPropList, 0x55bbd04, &targetTypeKey);

        if (mpMissionPropList && mpMissionPropList->GetProperty(0x55bbd05, &property) && property->mType == 13)
            mVisitRadius = *property->GetFloat();
        if (mpMissionPropList && mpMissionPropList->GetProperty(0x55bbd06, &property) && property->mType == 13)
            mEffectHeight = *property->GetFloat();
        if (mpMissionPropList && mpMissionPropList->GetProperty(0x5ad6f10, &property) && property->mType == 13)
            mEffectHeightJitter = *property->GetFloat();
        if (mpMissionPropList && mpMissionPropList->GetProperty(0x55bbd07, &property) && property->mType == 9)
            mNumCitiesToVisit = *property->GetInt();
    }

    GetPropertyAsKeyInstance(mpMissionPropList, 0x55bbd08, &mExploreType);

    uint32_t targetType = ReadTargetPlanetType();
    if (targetType != 0x2ca33bdb) {
        void* record = GetPlanetRecordFromTargetType(targetType);
        if (record)
            SetTargetPlanetRecord(record);
        if (!GetTargetPlanet()) {
            tPlanetPick pick;
            pick.Construct();
            pick.mMode = 0x3c;
            void* planet = PickPlanet(&pick);
            if (!planet) {
                pick.Destroy();
                return false;
            }
            SetTargetPlanetRecord(planet);
            pick.Destroy();
        }
    }

    if (!SetupTargetPlanet())
        return false;
    UnkC4a0c0();
    DataExportOnInit();
    return true;
}

// ---------------------------------------------------------------------------------------------
// 0x00c512f0 -- tCityVisitInfoVector::InsertAtEnd
// ---------------------------------------------------------------------------------------------
// @ 0x00c512f0
void tCityVisitInfoVector::InsertAtEnd(tCityVisitInfo* position, const tCityVisitInfo* value)
{
    tCityVisitInfo* end = mpEnd;
    if (end != mpCapacity) {
        const tCityVisitInfo* source = value;
        if (position <= source && source < end)
            ++source;
        if (end) {
            end->mPosition.x = end[-1].mPosition.x;
            end->mPosition.y = end[-1].mPosition.y;
            end->mPosition.z = end[-1].mPosition.z;
            end->mbVisited = end[-1].mbVisited;
            end->mEffectHeight = end[-1].mEffectHeight;
        }
        FUN_00c50ad0(position, end - 1, end);
        *position = *source;
        mpEnd = end + 1;
        return;
    }

    uint32_t count = (uint32_t)(end - mpBegin) / sizeof(tCityVisitInfo);
    uint32_t capacity = count ? count * 2 : 1;
    tCityVisitInfo* block = capacity
        ? (tCityVisitInfo*)EASTLAlloc(capacity * sizeof(tCityVisitInfo), g_allocatorName, 0, 0, g_allocatorFile, 0xd1)
        : 0;
    tCityVisitInfo* first = (tCityVisitInfo*)FUN_00c50e70(mpBegin, position, block);
    if (first) {
        first->mPosition.x = value->mPosition.x;
        first->mPosition.y = value->mPosition.y;
        first->mPosition.z = value->mPosition.z;
        first->mbVisited = value->mbVisited;
        first->mEffectHeight = value->mEffectHeight;
    }
    tCityVisitInfo* last = (tCityVisitInfo*)FUN_00c50e70(position, mpEnd, first + 1);
    if (mpBegin && ((tAllocHeader*)mpBegin)[-1].mCount != 0)
        EASTLFreeArray(mpBegin);
    mpBegin = block;
    mpEnd = last;
    mpCapacity = block + capacity;
}

// ---------------------------------------------------------------------------------------------
// 0x00c51440 -- write the visited-city vector as a "list" section
// ---------------------------------------------------------------------------------------------
static void FreeWStringTemp(WString* text)
{
    if ((((uint32_t)text->mpEnd - (uint32_t)text->mpBegin) & 0xfffffffe) > 2 && text->mpBegin)
        EASTLFreeArray(text->mpBegin);
}

// @ 0x00c51440
bool __cdecl FUN_00c51440(IListWriter* writer, const char* name, const tCityVisitInfoVector* section)
{
    if (section->mpBegin == section->mpEnd)
        return true;

    // the section name is widened into a temporary wstring; a null name becomes the empty string
    WString converted;
    WString empty;
    const WString* source;
    if (name) {
        ConvertToString16(&converted, name, -1);
        source = &converted;
    } else {
        empty.mpBegin = 0;
        empty.mpEnd = 0;
        empty.mpCapacity = 0;
        empty.RangeInitialize(0);
        source = &empty;
    }
    WString title;
    title.ConstructFrom(source);
    if (!name)
        FreeWStringTemp(&empty);
    else
        FreeWStringTemp(&converted);

    const wchar_t* label = (title.mpBegin == title.mpEnd) ? g_strList : title.mpBegin;
    writer->BeginSection(label);
    const tCityVisitInfo* record = section->mpBegin;
    bool ok = true;
    for (; record != section->mpEnd; ++record)
        ok = ok && FUN_00ac8050(writer, 0, record) != 0;
    writer->EndSection(label);
    FreeWStringTemp(&title);
    return ok;
}

// ---------------------------------------------------------------------------------------------
// 0x00c51590 -- GetProgressString: "visited/to visit"
// ---------------------------------------------------------------------------------------------
// @ 0x00c51590
WString* cSPMissionExplore::GetProgressString(WString* out)
{
    return WStr_Format(out, g_fmtProgress, mNumVisitedCities, mNumCitiesToVisit);
}

// ---------------------------------------------------------------------------------------------
// 0x00c515c0 -- GetTagString
// ---------------------------------------------------------------------------------------------
// @ 0x00c515c0
bool cSPMissionExplore::GetTagString(int tag, WString* out)
{
    if (mbVisitCities) {
        if (tag == (int)0xabc4e416) {
            WStr_Format(out, g_fmtDecimal, mNumCitiesToVisit);
            return true;
        }
        if (tag == 0x322dd3e2) {
            WStr_Format(out, g_fmtDecimal, mNumCitiesToVisit - mNumVisitedCities);
            return true;
        }
    }
    return cSPMission::GetTagString(tag, out);
}

// ---------------------------------------------------------------------------------------------
// 0x00c51630 -- read the visited-city vector (clears it first, then count + records)
// ---------------------------------------------------------------------------------------------
// @ 0x00c51630
void __cdecl FUN_00c51630(IArchiver* stream, tCityVisitInfoVector* vector)
{
    tCityVisitInfo* begin = vector->mpBegin;
    tCityVisitInfo* end = vector->mpEnd;
    FUN_00951bf0(end, end, begin);                    // eastl::copy(last, mpEnd, first)
    vector->mpEnd -= end - begin;                     // erase(begin, end)

    uint32_t count = 0;
    EA_ReadInt32(stream->GetWriter()->GetStream(), &count, 1, 0);
    vector->Reserve(count);

    for (uint32_t i = 0; i < count; i++) {
        tCityVisitInfo record;
        record.mbVisited = false;
        record.mEffectHeight = 0.0f;
        FUN_00c50b10(stream, &record);
        if (vector->mpEnd < vector->mpCapacity) {
            tCityVisitInfo* slot = vector->mpEnd++;
            slot->mPosition.x = record.mPosition.x;
            slot->mPosition.y = record.mPosition.y;
            slot->mPosition.z = record.mPosition.z;
            slot->mbVisited = record.mbVisited;
            slot->mEffectHeight = record.mEffectHeight;
        } else {
            vector->InsertAtEnd(vector->mpEnd, &record);
        }
    }
    stream->EndRead();
}

// ---------------------------------------------------------------------------------------------
// 0x00c51740 -- InitCityEffects: seed one effect record per city, then apply the stored heights
// ---------------------------------------------------------------------------------------------
// @ 0x00c51740
void cSPMissionExplore::InitCityEffects()
{
    if (!mbCityVisitInfoInitialized) {
        mbCityVisitInfoInitialized = true;
        tCityVector* cities = Cities();
        int count = (int)(cities->mpEnd - cities->mpBegin);
        for (int i = 0; i < count; i++) {
            cCity* city = cities->mpBegin[i];
            const Vec3* position = city->mSpatial.GetPosition();
            float jitter = mEffectHeightJitter;

            tCityVisitInfo record;
            record.mPosition.x = position->x;
            record.mPosition.y = position->y;
            record.mPosition.z = position->z;
            record.mbVisited = false;

            double random = g_spRandom.RandomDouble();
            float offset = (float)(random * ((double)jitter - (double)-jitter) + (double)-jitter);
            if (offset < jitter) {
                if (offset < -jitter)
                    offset = -jitter;
            } else {
                offset = jitter;
            }
            record.mEffectHeight = (float)((double)offset + (double)mEffectHeight);

            if (mCityVisitInfo.mpEnd < mCityVisitInfo.mpCapacity) {
                tCityVisitInfo* slot = mCityVisitInfo.mpEnd++;
                slot->mPosition.x = record.mPosition.x;
                slot->mPosition.y = record.mPosition.y;
                slot->mPosition.z = record.mPosition.z;
                slot->mbVisited = false;
                slot->mEffectHeight = record.mEffectHeight;
            } else {
                mCityVisitInfo.InsertAtEnd(mCityVisitInfo.mpEnd, &record);
            }
        }
    }

    tCityVector* cities = Cities();
    int count = (int)(cities->mpEnd - cities->mpBegin);
    for (int i = 0; i < count; i++) {
        cCity* city = cities->mpBegin[i];
        tCityVisitInfo* record = FindCityRecord(city);
        if (record)
            city->SetVisitEffectActive(!record->mbVisited, record->mEffectHeight);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c51900 -- RevertMiniMapIcons
// ---------------------------------------------------------------------------------------------
// @ 0x00c51900
void cSPMissionExplore::RevertMiniMapIcons()
{
    if (!FUN_010666a0())
        return;
    if (!FUN_010666a0()->GetWin())
        return;
    cMinimapWin* win = FUN_010666a0()->GetWin();
    cGameNounManager* nounMgr = NounManager();
    tCityVector* cities = nounMgr->GetGameDataVector(g_nounTypeKey0, g_nounTypeKey1, g_nounTypeKey2,
                                                     g_nounTypeKey3, g_nounAllocator);
    int count = (int)(cities->mpEnd - cities->mpBegin);
    for (int i = 0; i < count; i++) {
        cCity* city = cities->mpBegin[i];
        win->RemoveIcon(city, 1, 0);
        FUN_01041d50(city, win);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c519a0 -- DestroyCityEffects
// ---------------------------------------------------------------------------------------------
// @ 0x00c519a0
void cSPMissionExplore::DestroyCityEffects()
{
    if (!mbVisitCities)
        return;
    cGameNounManager* nounMgr = NounManager();
    tCityVector* cities = nounMgr->GetGameDataVector(g_nounTypeKey0, g_nounTypeKey1, g_nounTypeKey2,
                                                     g_nounTypeKey3, g_nounAllocator);
    int count = (int)(cities->mpEnd - cities->mpBegin);
    for (int i = 0; i < count; i++) {
        cCity* city = cities->mpBegin[i];
        city->SetVisitEffectActive(false, city->mEffectHeight);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c51a10 -- OnAccept
// ---------------------------------------------------------------------------------------------
// @ 0x00c51a10
void cSPMissionExplore::OnAccept()
{
    cSPMission::OnAccept();
    if (!mbVisitCities)
        return;
    if (GetActivePlanet() != cSPMission::GetTargetPlanet())
        return;
    if (GetUniverseContext())
        return;

    tCityVector* cities = Cities();
    int count = (int)(cities->mpEnd - cities->mpBegin);
    mNumCitiesToVisit = sp_min(mNumCitiesToVisit, count);
    InitCityEffects();
}

// ---------------------------------------------------------------------------------------------
// 0x00c51aa0 -- ShutdownSystems
// ---------------------------------------------------------------------------------------------
// @ 0x00c51aa0
void cSPMissionExplore::ShutdownSystems()
{
    cSPMission::ShutdownSystems();
    DestroyCityEffects();
    RevertMiniMapIcons();
}

// ---------------------------------------------------------------------------------------------
// 0x00c51ac0 -- ReturnForRewards
// ---------------------------------------------------------------------------------------------
// @ 0x00c51ac0
void cSPMissionExplore::ReturnForRewards()
{
    if (mExploreMissionState == kReturnForReward)
        return;
    StartCompletedFeedbackTimer();
    if (mExploreMissionState != kReturnForReward) {
        mExploreMissionState = kReturnForReward;
        cSPMission::TriggerUIUpdate();
    }
    Unk472e0();
    Unk471c0();
    DestroyCityEffects();
}

// ---------------------------------------------------------------------------------------------
// 0x00c51b10 -- HandleMessage.  The original lives in the message-handler sub-object vtable, so it
// is entered with this == cSPMissionExplore + 0x34 and steps back (lea edi,[esi-0x34]); it is
// modelled here as a cSPMissionExplore member, which is ABI-equivalent for the fields it reads but
// does not reproduce the pointer adjustment.
// ---------------------------------------------------------------------------------------------
// @ 0x00c51b10
void cSPMissionExplore::HandleMessage(uint32_t message, void* data)
{
    if (message == 0x248975f) {
        if (mbVisitCities && cSPMission::GetTargetPlanet() == GetActivePlanet() && !GetUniverseContext())
            InitCityEffects();
    } else if (message == 0x2489760) {
        if (mbVisitCities && cSPMission::GetTargetPlanet() == GetActivePlanet() && !GetUniverseContext()) {
            DestroyCityEffects();
            cSPMission::HandleMessage(message, data);
            return;
        }
    }
    cSPMission::HandleMessage(message, data);
}

// ---------------------------------------------------------------------------------------------
// 0x00c51bb0 -- Update
// ---------------------------------------------------------------------------------------------
// @ 0x00c51bb0
int cSPMissionExplore::Update(uint32_t delta)
{
    int result = cSPMission::Update(delta);
    if (result != 3)
        return result;
    if (mExploreMissionState != kVisitPlanet)
        return result;

    if (cSPMission::GetTargetPlanet()) {
        if (mbVisitCities) {
            if (GetUniverseContext())
                return result;
            if (cSPMission::GetTargetPlanet() != GetActivePlanet())
                return result;

            float radiusSquared = mVisitRadius * mVisitRadius;
            cPlayerInventory* inventory = GetUFOSimulator()->GetPlayerInventory();
            Vec3 player;
            player.x = inventory->mPlayerPosition.x;
            player.y = inventory->mPlayerPosition.y;
            player.z = inventory->mPlayerPosition.z;

            cCity* city = FUN_00ac9dd0(NounManager()->UnkAce2c0(), &player);
            tCityVisitInfo* record = FindCityRecord(city);
            if (record && !record->mbVisited) {
                const Vec3* cityPosition = city->mSpatial.GetPosition();
                float height = record->mEffectHeight;
                Vec3 direction;
                Swarm_Normalize(&direction, cityPosition);
                float dx = player.x - (cityPosition->x + direction.x * height);
                float dy = player.y - (cityPosition->y + direction.y * height);
                float dz = player.z - (cityPosition->z + direction.z * height);
                if (radiusSquared > dx * dx + dy * dy + dz * dz) {
                    record->mbVisited = true;
                    city->SetVisitEffectActive(false, height);
                    ++mNumVisitedCities;
                    MarkCityVisitedInMiniMap(city);
                    cSPMission::TriggerUIUpdate();
                }
            }
            if ((int)mNumVisitedCities >= (int)mNumCitiesToVisit)
                ReturnForRewards();
            return result;
        }

        if (cSPMission::GetTargetPlanet() && cSPMission::GetTargetPlanet()->HasCommContextFlag())
            ReturnForRewards();
        return result;
    }

    if (mExploreType == 0xf0b5943d) {
        if (GetUniverseContext())
            return result;
        if (!GetActivePlanet())
            return result;
        if (GetActivePlanet()->UnkC70e00() != 2)
            return result;
        ReturnForRewards();
        return result;
    }
    if (mExploreType == 0x7ecbe6f5) {
        if (GetUniverseContext())
            return result;
        if (!GetActivePlanet())
            return result;
        if (GetActivePlanetRecord()->UnkBB9d40())
            ReturnForRewards();
    }
    return result;
}

// ---------------------------------------------------------------------------------------------
// 0x00c51e40 -- accept/fail path that force-closes the mission and drops its city effects
// ---------------------------------------------------------------------------------------------
// @ 0x00c51e40
void cSPMissionExplore::AbortToRewardState()
{
    UnkC2e4e0();
    if (mExploreMissionState == kReturnForReward)
        return;
    StartCompletedFeedbackTimer();
    if (mExploreMissionState != kReturnForReward) {
        mExploreMissionState = kReturnForReward;
        cSPMission::TriggerUIUpdate();
    }
    Unk472e0();
    Unk471c0();
    DestroyCityEffects();
}

// ---------------------------------------------------------------------------------------------
// 0x00c51f90 -- AddMessageHandlers
// ---------------------------------------------------------------------------------------------
// @ 0x00c51f90
void cSPMissionExplore::AddMessageHandlers()
{
    UnkC44b80();
    AddMessageHandler(0x3029f11);
    AddMessageHandler(0x3029f12);
    AddMessageHandler(0x248975f);
    AddMessageHandler(0x2489766);
    AddMessageHandler(0x248976a);
    AddMessageHandler(0x2e9977e);
}

// ---------------------------------------------------------------------------------------------
// 0x00c52000 -- RemoveMessageHandlers
// ---------------------------------------------------------------------------------------------
// @ 0x00c52000
void cSPMissionExplore::RemoveMessageHandlers()
{
    UnkC44bd0();
    RemoveMessageHandler(0x3029f11);
    RemoveMessageHandler(0x3029f12);
    RemoveMessageHandler(0x248975f);
    RemoveMessageHandler(0x2489766);
    RemoveMessageHandler(0x248976a);
    RemoveMessageHandler(0x2e9977e);
}

}  // namespace SP
