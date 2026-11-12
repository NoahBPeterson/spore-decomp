// src/game/SPGonzago/SPBadgeManager.cpp -- migrated from slice(s) s00fe5a20, s00fe4be0, s00fe3b10 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBadgeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cISerializableObject.h"
#include "SP/cIObjectDatabaseOStream.h"
#include "SP/cPropertyList.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"
#include "EA/Variant.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern const uint32_t g_badgeEventIds[];        // 0x01494214 (the ten tracked badge event ids)
extern const char g_statStrings[];              // 0x063bb6d0 (GetStatString texts, laid end to end)
extern const char g_badgePropNames[];           // 0x04a37dfb (two adjacent property names)
extern const char g_serializedFieldName[];      // 0x015b42f8 (name handed to cVarListSerializer)
extern void* g_pSpaceTokenTranslator;           // 0x016e0d08 (its +0x44 holds the badge being named)

// ---- items of slice s00fe3b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
static inline size_t WStrLen(const wchar_t* pszText)
{
    const wchar_t* pszEnd = pszText;
    while (*pszEnd != 0)
        ++pszEnd;
    return (size_t)(pszEnd - pszText);
}
void        __cdecl FUN_00f47380(void* pBlock);            // 0x00f47380 operator delete[]
void        __cdecl FUN_01068400(void** ppItems, uint32_t nCount);   // 0x01068400
void        __cdecl FUN_0093c5a0(void* pOut, const char* pszText, int nLength); // 0x0093c5a0
void        __cdecl FUN_00579a90(void* pString, uint32_t nCount);    // 0x00579a90
void        __cdecl FUN_0056e2d0(void* pString, const void* pOther); // 0x0056e2d0
struct tRBNode;
tRBNode*    __cdecl RBTreeIncrement(tRBNode* pNode);       // 0x00921580
void        __cdecl GetPropertyAsText(void* pObject, const char* pszName, void* pOut); // 0x006a1360
void        __cdecl GetPropertyAsKeyInstance(void* pObject, uint32_t id, void* pOut);   // 0x006a12a0
namespace EA {
namespace IO {
class IStream_s00fe_3b10;
}
}
namespace EA {
namespace IO {
bool __cdecl WriteUint32(IStream_s00fe_3b10* pStream, const uint32_t* pData, int nCount, int nFlags); // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool __cdecl ReadInt32(IStream_s00fe_3b10* pStream, uint32_t* pData, int nCount, int nFlags);         // 0x0093a780
}
}
struct tRBNode {                        // eastl::rbtree_node_base
    tRBNode* mpNodeRight;               // +0x00
    tRBNode* mpNodeLeft;                // +0x04
    tRBNode* mpNodeParent;              // +0x08
    uint32_t mColor;                    // +0x0c
};
struct tPairNode {                      // rbtree node holding pair<const unsigned, unsigned>
    tRBNode  mBase;                     // +0x00
    uint32_t mKey;                      // +0x10
    uint32_t mValue;                    // +0x14
};
class tU32Tree {
public:
    uint32_t    mBase00;                // +0x00
    tRBNode     mAnchor;                // +0x04
    uint32_t    mnSize;                 // +0x14
    uint32_t    mAllocator18;           // +0x18
    tPairNode** find(tPairNode** ppOut, const uint32_t* pKey) const; // 0x00e5c780
    void        DoNukeSubtree(tRBNode* pNode);                       // 0x009a9600
    tPairNode*  begin() const { return (tPairNode*)mAnchor.mpNodeLeft; }
    tPairNode*  end() const { return (tPairNode*)&mAnchor; }
    ~tU32Tree()                                                      // inline in the original
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
    }
    void clear()                                                     // inline in the original
    {
        DoNukeSubtree(mAnchor.mpNodeParent);
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
        mAnchor.mpNodeRight = &mAnchor;
    }
};
class tBadgeTree {
public:
    uint32_t    mBase00;                // +0x00
    tRBNode     mAnchor;                // +0x04
    uint32_t    mnSize;                 // +0x14
    uint32_t    mAllocator18;           // +0x18
    tPairNode** find(tPairNode** ppOut, const uint32_t* pKey) const; // 0x00e5c780
    void        DoNukeBadgeSubtree(tRBNode* pNode);                  // 0x00d0c930
    tPairNode*  begin() const { return (tPairNode*)mAnchor.mpNodeLeft; }
    tPairNode*  end() const { return (tPairNode*)&mAnchor; }
    ~tBadgeTree()                                                    // inline in the original
    {
        DoNukeBadgeSubtree(mAnchor.mpNodeParent);
    }
};
class eastlWString {
public:
    wchar_t* mpBegin;                   // +0x00
    wchar_t* mpEnd;                     // +0x04
    wchar_t* mpCapacity;                // +0x08
    void assign(const wchar_t* pFirst, const wchar_t* pLast);        // 0x00423650
    const wchar_t* c_str() const { return mpBegin; }
};
class cString {
public:
    eastlWString mText;                 // +0x00
    cString();                                                     // 0x006b5060
    ~cString();                                                    // 0x006b5240
    const wchar_t* GetText() const;                                // 0x006b55c0
};
struct tHashNode {
    tHashNode*   mpNext;                // +0x00
    eastlWString mValue;                // +0x04
};
class tHintTable {
public:
    uint32_t    mBase00;                // +0x00
    tHashNode** mpBucketArray;          // +0x04
    uint32_t    mnBucketCount;          // +0x08
    uint32_t    mnElementCount;         // +0x0c
    tHashNode** find(tHashNode** ppOut, const uint32_t* pKey) const; // 0x00a3b2c0
    tHashNode*  end() const { return mpBucketArray[mnBucketCount]; }
    ~tHintTable()                                                    // inline in the original
    {
        FUN_01068400((void**)mpBucketArray, mnBucketCount);
        mnElementCount = 0;
        if (mnBucketCount > 1)
            FUN_00f47380(mpBucketArray);
    }
};
class cVarListSerializer {
public:
    cVarListSerializer(const void* pOwner, const char* pszName, uint32_t nVersion);  // 0x00692f90
    bool Serialize(class cOutStream* pStream);                                      // 0x00692900
    bool Serialize(class cInStream* pStream);                                       // 0x00693e10
    uint32_t mPad00[0xa14 / 4];         // +0x0000
};
class cSaveStream {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual EA::IO::IStream_s00fe_3b10* GetIStream();                           // +0x18
};
class cOutStream {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual void EndElement();                                       // +0x1c
    virtual cSaveStream* GetStream();                                // +0x20
};
struct tBadgeRecord {
    uint32_t mId;                       // +0x00
    uint32_t mValue04;                  // +0x04
    uint32_t mValue08;                  // +0x08
};
struct tRecordArray {
    tBadgeRecord* mpData;               // +0x00
    uint32_t      mPad04;               // +0x04
    uint32_t      mnCount;              // +0x08
    uint32_t      mPad0c;               // +0x0c
    uint32_t      mFlags;               // +0x10
    uint16_t      mPad14;               // +0x14
    uint16_t      mType;                // +0x16
};
struct tVariant {
    uint32_t mPad00[4];                 // +0x00
    uint16_t mPad10;                    // +0x10
    uint16_t mType;                     // +0x12
    int32_t* GetInt();                                               // 0x0041e990
};
class cPropertyList {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual bool HasProperty(uint32_t nId);                          // +0x1c
    virtual void v08();                                              // +0x20
    virtual bool GetProperty(uint32_t nId, tVariant** ppOut);        // +0x24
    virtual tRecordArray* GetRecords(uint32_t nId);                  // +0x28
};
class cUIMissionCardPanel {
public:
    void RemoveBadgeCard(void* pCard);                               // 0x00e15d30
    void AddBadgeCard(void* pCard);                                  // 0x00e18150
};
cUIMissionCardPanel* __cdecl FUN_00b3d400();                         // 0x00b3d400
class cStringContext {
public:
    const wchar_t* GetStatText();                                    // 0x00adde90
};
cStringContext* __cdecl FUN_00b3d4d0(uint32_t nId, const void* pDesc, int nFlags); // 0x00b3d4d0
class cContentValidationSummarizer {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual void v06();
    virtual ~cContentValidationSummarizer() {}
    uint32_t mPad04;                    // +0x04
};
class cISerializableObject {
public:
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
    virtual void Write(cOutStream* pStream);                         // slot 4
    virtual void Read(cOutStream* pStream);                          // slot 5
    virtual ~cISerializableObject() {}
    uint32_t mPad04;                    // +0x04
};
class cSPBadgeManager : public cContentValidationSummarizer, public cISerializableObject {
public:
    tBadgeTree  mBadgeMap;              // +0x10
    tU32Tree    mEventCounts;           // +0x2c
    tU32Tree    mPropList;              // +0x48
    tU32Tree    mHintMap;               // +0x64
    tHintTable  mHintStrings;           // +0x80
    uint32_t    mPad90[5];              // +0x90
    void*       mpCurrentCard;          // +0xa4
    uint32_t    mPadA8;                 // +0xa8
    cString     mHintText;              // +0xac

    void     FUN_00fe3cc0(void* pCard);
    uint32_t FUN_00fe4150(uint32_t nBadge) const;
    bool     FUN_00fe4180(uint32_t nBadge) const;
    uint32_t GetReplacement(uint32_t nBadge) const;
    uint32_t FUN_00fe4230(uint32_t nBadge) const;
    int      FUN_00fe42a0() const;
    bool     FUN_00fe43c0(uint32_t nBadge, uint32_t nIndex) const;
    bool     FUN_00fe43c0(void* pCard, uint32_t nBadge) const;
    const wchar_t* FUN_00fe45f0(uint32_t nBadge, bool bIgnoreStatus) const;
    bool     FUN_00fe46a0(uint32_t nBadge) const;
    void     GetBadgeName(uint32_t nBadge, eastlWString& strOut) const;
    void     GetBadgeDescription(uint32_t nBadge, eastlWString& strOut) const;
    void     GetBadgeHintActionString(uint32_t nBadge, eastlWString& strOut) const;
    void     FUN_00fe4900(uint32_t nBadge, eastlWString& strOut) const;
    void     FUN_00fe49a0(uint32_t nBadge, eastlWString& strOut) const;
    int      FUN_00fe3f50(uint32_t nValue) const;
    uint32_t FUN_00fe3f80(uint32_t nValue, uint32_t nIndex) const;
    ~cSPBadgeManager();
};
struct tStatStringDesc {
    const char* mpText;                 // +0x00
    uint32_t    mPad04;                 // +0x04
    uint32_t    mId;                    // +0x08
};
// ---- items of slice s00fe3b10 end

// ---- items of slice s00fe4be0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
class Property;
class cBadgeObject {
public:
virtual void v000();
virtual void v004();
virtual void v008();
virtual void v00c();
virtual void v010();
virtual void v014();
virtual void v018();
virtual void v01c();
    virtual void v020();
    virtual bool ResolveProperty(uint32_t key, Property** ppValue); // +0x24
};
class Property {
public:
    uint32_t* GetUInt();                                 // 0x0041ea00

    uint8_t  pad000[0x12];                               // +0x00 .. +0x11
    uint16_t mType;                                      // +0x12
};
class cBadgePropertyMap {
public:
    cBadgeObject** FUN_00dd85c0(Property** ppValue);     // 0x00dd85c0
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
class cBadgeCounterMap {
public:
    uint32_t* operator[](const uint32_t* pKey);          // 0x00badea0
};
bool __cdecl GetPropertyAsKey(cBadgeObject* pObject, uint32_t nId, ResourceKey* pOut); // 0x006a1250
struct tEventNode {
    tRBNode  mBase;                     // +0x00
    uint32_t mKey;                      // +0x10
    uint32_t mValue;                    // +0x14
};
struct tEventTree {
    uint32_t   mBase00;                 // +0x00
    tRBNode    mAnchor;                 // +0x04
    uint32_t   mnSize;                  // +0x14
    tEventNode** find(tEventNode** ppOut, const uint32_t* pKey); // 0x00e39fb0
    uint32_t*    operator[](const uint32_t* pKey);               // 0x00de7630
};
namespace SP {
class cSPBadgeManager_s00fe_4be0 {
public:
    void     FUN_00fe5430(uint32_t nBadge, int nCount);  // 0x00fe5430
    uint32_t FUN_00fe54d0(Property* pProperty);
    ResourceKey* GetBadgeImageKey(ResourceKey* pOut, uint32_t nBadge); // 0x00fe5520
    void     TestRequirement();  // 0x00fe55b0 (SP::cSPBadgeManager::TestRequirement)

    uint8_t             pad000[0x10];                    // +0x00 .. +0x0f
    cBadgePropertyMap   mBadgeMap;                       // +0x10
    uint8_t             pad11[0x2c - 0x11];              // +0x11 .. +0x2b
    cBadgeCounterMap    mStatus;                         // +0x2c
    uint8_t             pad2d[0xa4 - 0x2d];              // +0x2d .. +0xa3
    void*               mpCurrentCard;                   // +0xa4
};  // namespace SP
}
// ---- items of slice s00fe4be0 end

// ---- items of slice s00fe5a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void TickProbe0();                                                 // 0xb3d4a0
extern "C" int  TickProbe1();                                                 // 0xae9390
extern "C" int  TickProbe2();                                                 // 0x1075500
extern "C" int  TickProbe3();                                                 // 0xb18e40
extern "C" int  TickProbe4();                                                 // 0xd09660
extern "C" int  TickProbe5();                                                 // 0xff6550
extern "C" void* GetWorldMode();                                              // 0xb3d4d0
extern "C" void* GetGameTimeManager();                                        // SP::GameTimeManager
extern "C" int  RequirementCount(void* props);                                // 0x571ef0
extern "C" int* RequirementList();                                            // 0x446ff0
extern "C" int  GetEventIndex();                                              // 0xfe42a0
extern "C" void SetNumberString(int v, int pad, wchar_t* buf, int len);       // 0x881ae0
extern "C" void WStr_Format(void* str, const wchar_t* fmt, ...);              // 0x41e050
extern "C" void AppendFormatted(void* str, const wchar_t* fmt, ...);          // 0x4e0850
typedef uint32_t uint32;
extern ResourceKey kNullKey;   // 0x016d9fb4
struct Property_s00fe_5a20 {
    char pad0[8];
    int count;          // +8 (indirect arrays)
    unsigned short flags;   // +0x10, bits 0x30 = indirect
    unsigned short type;    // +0x12
};
static __forceinline int* PropData(Property_s00fe_5a20* p) { return (p->flags & 0x30) ? *(int**)p : (int*)p; }
static __forceinline int PropArrayCount(Property_s00fe_5a20* p) { return (p->flags & 0x30) ? p->count : (p->type != 0); }
static __forceinline ResourceKey* PropArrayData(Property_s00fe_5a20* p)
{
    return (ResourceKey*)((p->flags & 0x30) ? *(void**)p : (p->type ? (void*)p : (void*)0));
}
struct IPropList {
    virtual void v00();
    virtual void Release();                                  // +4
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
    virtual bool Has(uint32 id);                             // +0x1c
    virtual void v20();
    virtual bool GetProperty(uint32 id, Property_s00fe_5a20** pp);      // +0x24
    virtual Property_s00fe_5a20* GetPropertyRef(uint32 id);             // +0x28
};
bool GetPropertyAsKeyInstance(IPropList* list, uint32 id, uint32* value);   // 0x6a12a0 cdecl
struct cString_s00fe_5a20 {
    uint32 mData[5];
    cString_s00fe_5a20();                          // 0x6b5060
    ~cString_s00fe_5a20();                         // 0x6b5240
    const wchar_t* GetText();           // 0x6b55c0
};
bool GetPropertyAsText(IPropList* list, uint32 id, cString_s00fe_5a20* out);           // 0x6a1360 cdecl
struct RBNode {
    RBNode* mpNodeRight;    // +0
    RBNode* mpNodeLeft;     // +4
    RBNode* mpNodeParent;   // +8
    uint32 mColor;          // +0xc
    uint32 key;             // +0x10
    uint32 value;           // +0x14
};
RBNode* RBTreeIncrement(RBNode* n);     // 0x921580, cdecl
struct PropMap {            // map<uint32, AutoRefCount<cPropertyList> > at +0x10
    uint32 pad;
    RBNode anchor;
    IPropList*& operator[](const uint32& key);   // 0xdd85c0
    RBNode* end() { return &anchor; }
    RBNode* lower_bound(const uint32& key)
    {
        RBNode* pCurrent = anchor.mpNodeParent;
        RBNode* pRangeEnd = &anchor;
        while (pCurrent) {
            if (!(pCurrent->key < key)) {
                pRangeEnd = pCurrent;
                pCurrent = pCurrent->mpNodeLeft;
            } else
                pCurrent = pCurrent->mpNodeRight;
        }
        return pRangeEnd;
    }
    RBNode* find(const uint32& key)
    {
        RBNode* it = lower_bound(key);
        RBNode* itEnd = end();
        return (it == itEnd || key < it->key) ? itEnd : it;
    }
};
struct StatusMap {          // map<uint32, int> at +0x2c
    uint32 pad;
    RBNode anchor;
    int& operator[](const uint32& key);          // 0xbadea0
};
struct StageMap {           // map<uint32, uint32> at +0x48
    uint32 pad;
    RBNode anchor;
    uint32& operator[](const uint32& key);       // 0x643a40
};
struct IRef { virtual void v0(); virtual void Release(); };
struct Tool { virtual void v0(); virtual void v1(); virtual void Release(); };   // release at +8
struct ToolManager { bool CreateToolFromToolID(ResourceKey* id, Tool** out); };    // 0x104e340 ret 8
struct Inventory {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
virtual void v6c();
virtual void v70();
    virtual bool HasTool(ResourceKey* id);                       // +0x74
virtual void v78();
virtual void v7c();
    virtual void AddTool(Tool* t, int a, int b);                 // +0x80
virtual void v84();
virtual void v88();
virtual void v8c();
virtual void v90();
    virtual void GrantReward(int v);                             // +0x94
};
struct SubSystemData { char pad[0x1c]; uint32 badge; };
struct SubSystem {
    char pad[0xc]; SubSystemData* data;
    void Activate(int v);                                          // 0x7eb820 ret 4
};
struct SpaceGame {
    char pad[0x40];
    Inventory* GetPlayerInventory();                              // 0xa1ad60
    void* GetAvatar();                                            // noun manager avatar
    SubSystem* GetSubSystem(int v);                                   // 0x1005180 ret 4
};
struct TerrainSphere {
    void Unlock(int v);                                         // 0xc755c0 ret 4
};
struct TerrainEditor { TerrainSphere* GetCurrentTerrainSphere(); };   // 0xf67d90
struct MissionCardPanel { void RemoveBadgeCard(uint32 id); };   // 0xe15d30 ret 4
struct EventLogT {
    uint32 PostFeedbackEvent(uint32 a, uint32 b, int c, int d, int e, int f);   // 0xdd8640 ret 0x18
    void ModifyEventText(uint32 id, const wchar_t* text);                        // 0xdd6df0 ret 8
};
struct GMgr {
    void OnBadgeUnlocked(uint32 badge);    // 0x103d360 ret 4
    void SetMasterBadgeFlag(int v);        // 0x1039b00 ret 4
};
struct GNamed { uint32 Lookup(const char* name, int a, int b, int c, int d, int e); };   // 0xae0930 ret 0x18
struct UFOSim { void CalcMaxTravelDistance(); };                  // 0xffc6d0
struct Empire { char pad[0x58]; int archetype; };
struct Achievements {
    void AutoTest(uint32 id, int v);                              // 0x676e90 ret 8
    void AwardAchievement(uint32 id);                             // 0x676710 ret 4
    bool IsAwarded(uint32 id);                                    // 0x675e80 ret 4
};
struct MsgServer {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
    virtual void MessageSend(uint32 id, void* msg, int flag);     // +0x14
    virtual void Post(uint32 id, void* msg, int a, int b);        // +0x18
};
GMgr* GetGMgr();           // 0xb3d3d0
TerrainEditor* NounManager();      // 0xb3d300
MissionCardPanel* GetCardPanel();  // 0xb3d400
ToolManager* GetToolManager();     // 0xb3d390
EventLogT* EventLog();             // 0xb3d3e0
GNamed* GetGNamed();             // 0xb3d4d0
SpaceGame* SpaceGameGet();         // 0x1002bd0
UFOSim* GetUFOSimulator();         // 0xffbe50
Empire* GetPlayerEmpire();         // 0x1021300
Achievements* AchievementsController();   // 0x675250
MsgServer* MessageServer();        // 0x67dcc0
MsgServer* GetMessagingServer();   // 0x883860
void FUN_00fe3d30(int index, uint32 v);                           // 0xfe3d30 cdecl
struct Z12 { uint32 a, b, c; };
void FUN_00e39ab0(uint32 a, int b, Z12* c, Z12* d, int e, uint32 badge, Z12* f, Z12* g);   // 0xe39ab0 cdecl
void* OperatorNew(uint32 size, const char* name, uint32 a, uint32 b, uint32 c, uint32 d);   // 0xf473a0 cdecl
typedef void (__thiscall *VFn)(void*);
struct HeapMsg {
virtual void v0();
virtual void AddRef();
virtual void Release();
    int refcount;               // +4
    uint32 slot0;               // +8
    char pad[0x24];             // +0xc..0x2f
    uint32 id30;                // +0x30
    uint32 pad34;
    uint32 mask38;              // +0x38
    uint32 pad3c;
};
struct StackMsg {
    void* vtbl;                 // +0
    long refcount;              // +4
    struct Slot { uint32 v, pad; } slot[5];   // +8
    uint32 id30;                // +0x30
    uint32 pad34;
    uint32 mask38;              // +0x38
    uint32 pad3c;
    StackMsg(uint32 a)
    {
        id30 = 0;
        vtbl = (void*)0x13eb90c;
        _InterlockedExchange(&refcount, 0);
        vtbl = (void*)0x13eb844;
        mask38 = 0;
        slot[0].v = a;
    }
    __forceinline ~StackMsg()
    {
        vtbl = (void*)0x13eb844;
        uint32 bit = 1;
        for (int i = 0; i < 32; i++) {
            if (mask38 & bit) {
                IRef* p = *(IRef**)((char*)this + 8 + i * 8);
                if (p) p->Release();
            }
            bit = (bit << 1) | ((int)bit < 0);
        }
    }
};
struct cSPBadgeManager_s00fe_5a20 {
    char pad0[0x10];
    PropMap mBadges;            // +0x10 (anchor +0x14)
    StatusMap mStatus;          // +0x2c (anchor +0x30)
    StageMap mStage;            // +0x48
    char pad64[0xa4 - 0x64];
    uint32 mCurrentBadgeCard;   // +0xa4
    uint32 mTickAccum;          // +0x38 area in retail (event timer)
    uint32 mSuppressUnlock;     // event-map flag
    void*  mLastEvent;          // last reported event

    bool IsMasterBadgePart(uint32 badge);         // 0xfe3df0 ret 4
    int GetMasterBadgeCount();                    // 0xfe42a0
    void ShowBadgeCard(uint32 badge);             // 0xfe3cc0 ret 4
    void AddToBadgeProgress(int ev, int value);   // 0xfe5430 ret 8
    void UnlockBadge(uint32 badge);               // 0xfe5a20
    long double GetProgressScore(uint32 id, int mode, void* buf, uint32 len);  // 0xfe6210
    void OnTick(int delta);                       // 0xfe6490
};
extern "C" void* BadgeProps(uint32 event);                                    // 0x642c10
extern "C" void ReportBadgeProgress(uint32 event);                            // 0xe17470
struct PropsObj { void GetKey(uint32 id); };
extern "C" void** MapFind(void* tree, void** out, const uint32* key);        // 0xe5c780 (ret 8)
extern "C" int  GetReplacement(cSPBadgeManager_s00fe_5a20* self, uint32 id);             // 0xfe41c0 (ret 4)
extern "C" int  TestRequirement(uint32 id);                                   // requirement value lookup
extern "C" int  EnumRequirements(void* reqs, uint32 key, int* count, int* data);
extern "C" int  GetPropertyAsInt(void* props, uint32 id, int* out);           // 0x410270 (ret 0xc)
extern uint32 g_eventSteps[10];                                               // 0x1494214
struct ReqVec {
    int  Amount(uint32 id);
    char pad00[0x14];
};
struct EventNode {
    uint32 mId;                                        // +0x00
    char   pad04[0x10];
    uint32 mCount14;                                   // +0x14
    uint32 mState18;                                   // +0x18
};
struct EventMap {
    char pad00[0x2c];
    StatusMap mEvents;                                 // +0x2c (anchor +0x30)
    cSPBadgeManager_s00fe_5a20* mOwner;                           // +0x38
    long double GetScore(uint32 id);                   // 0xfe6690 (ret 4)
    int  GetScoreRounded(uint32 id);                   // 0xfe66f0 (ret 4)
    long double GetWeightedScore();                    // 0xfe67b0
    void FormatScore(uint32 id, void* text);           // 0xfe6800 (ret 8)
};
// ---- items of slice s00fe5a20 end

// @ 0x00fe3c40
void cISerializableObject::Write(cOutStream* pStream)
{
    uint32_t nVersion;
    cSaveStream* pSaveStream = pStream->GetStream();
    EA::IO::IStream_s00fe_3b10* pIStream = pSaveStream->GetIStream();
    nVersion = 0x2cb0ede;
    EA::IO::WriteUint32(pIStream, &nVersion, 1, 0);
    cVarListSerializer serializer((const char*)this - 8, g_serializedFieldName, 0x1a80d26);
    serializer.Serialize(pStream);
}

// @ 0x00fe3cc0
void cSPBadgeManager::FUN_00fe3cc0(void* pCard)
{
    if (mpCurrentCard != pCard) {
        cUIMissionCardPanel* pPanel = FUN_00b3d400();
        if (mpCurrentCard != 0 && pPanel != 0)
            pPanel->RemoveBadgeCard(mpCurrentCard);
        mpCurrentCard = pCard;
        if (pCard != 0 && pPanel != 0)
            pPanel->AddBadgeCard(pCard);
    }
}

// @ 0x00fe3d30
const wchar_t* __cdecl FUN_00fe3d30(int nType)
{
    const char* pszText;
    switch (nType) {
    case 1:  pszText = g_statStrings + 0x00; break;
    case 2:  pszText = g_statStrings + 0x06; break;
    case 3:  pszText = g_statStrings + 0x0a; break;
    case 4:  pszText = g_statStrings + 0x0f; break;
    case 5:  pszText = g_statStrings + 0x13; break;
    case 6:  pszText = g_statStrings + 0x18; break;
    case 7:  pszText = g_statStrings + 0x1e; break;
    case 8:  pszText = g_statStrings + 0x22; break;
    case 9:  pszText = g_statStrings + 0x26; break;
    case 10: pszText = g_statStrings + 0x2a; break;
    default: pszText = (const char*)nType; break;
    }
    tStatStringDesc desc;
    desc.mpText = pszText;
    desc.mPad04 = 0;
    desc.mId = 0x974299be;
    return FUN_00b3d4d0(0x6a9c6745, &desc, 0)->GetStatText();
}

// @ 0x00fe3df0
int32_t __stdcall FUN_00fe3df0(uint32_t nId)
{
    if (nId == 0x58b78701 || nId == 0x58b78702 || nId == 0x58b78703 || nId == 0x58b78704 ||
        nId == 0x58b78705 || nId == 0x58b78706 || nId == 0x58b78707 || nId == 0x58b78708 ||
        nId == 0x58b78709 || nId == 0xa9e986a3)
        return true;
    return false;
}

// @ 0x00fe3e50
int32_t __stdcall FUN_00fe3e50(uint32_t nId)
{
    int32_t nResult = 0;
    uint32_t i = 0;
    do {
        if (g_badgeEventIds[i] == nId) {
            nResult = (int32_t)i + 1;
            break;
        }
        ++i;
    } while (i < 10);
    return nResult;
}

// @ 0x00fe3e80
void FUN_00fe3e80(cOutStream* pStream, tU32Tree* pMap)
{
    uint32_t nValue = pMap->mnSize;
    EA::IO::WriteUint32(pStream->GetStream()->GetIStream(), &nValue, 1, 0);
    for (tPairNode* p = pMap->begin(); p != pMap->end(); p = (tPairNode*)RBTreeIncrement(&p->mBase)) {
        nValue = p->mKey;
        EA::IO::WriteUint32(pStream->GetStream()->GetIStream(), &nValue, 1, 0);
        pStream->EndElement();
        nValue = p->mValue;
        EA::IO::WriteUint32(pStream->GetStream()->GetIStream(), &nValue, 1, 0);
        pStream->EndElement();
    }
    pStream->EndElement();
}

// @ 0x00fe3f50
int cSPBadgeManager::FUN_00fe3f50(uint32_t nValue) const
{
    int nCount = 0;
    for (tPairNode* p = mPropList.begin(); p != mPropList.end(); p = (tPairNode*)RBTreeIncrement(&p->mBase)) {
        if (nValue == p->mValue)
            ++nCount;
    }
    return nCount;
}

// @ 0x00fe3f80
uint32_t cSPBadgeManager::FUN_00fe3f80(uint32_t nValue, uint32_t nIndex) const
{
    uint32_t nFound = 0;
    for (tPairNode* p = mPropList.begin(); p != mPropList.end(); p = (tPairNode*)RBTreeIncrement(&p->mBase)) {
        if (nValue == p->mValue) {
            if (nFound == nIndex)
                return p->mKey;
            ++nFound;
        }
    }
    return 0;
}

// @ 0x00fe3fd0
void FUN_00fe3fd0(tU32Tree* pMap, cOutStream* pStream)
{
    uint32_t nValue = pMap->mnSize;
    EA::IO::WriteUint32(pStream->GetStream()->GetIStream(), &nValue, 1, 0);
    for (tPairNode* p = pMap->begin(); p != pMap->end(); p = (tPairNode*)RBTreeIncrement(&p->mBase)) {
        nValue = p->mKey;
        EA::IO::WriteUint32(pStream->GetStream()->GetIStream(), &nValue, 1, 0);
        pStream->EndElement();
        nValue = p->mValue;
        EA::IO::WriteUint32(pStream->GetStream()->GetIStream(), &nValue, 1, 0);
        pStream->EndElement();
    }
    pStream->EndElement();
}

// @ 0x00fe40a0
void cISerializableObject::Read(cOutStream* pStream)
{
    uint32_t nUnused;
    EA::IO::ReadInt32(pStream->GetStream()->GetIStream(), &nUnused, 1, 0);
    cSPBadgeManager* pOwner = (cSPBadgeManager*)((char*)this - 8);
    pOwner->mEventCounts.clear();
    pOwner->mHintMap.clear();
    cVarListSerializer serializer((const char*)this - 8, g_serializedFieldName, 0x1a80d26);
    serializer.Serialize(pStream);
}

// @ 0x00fe4150
uint32_t cSPBadgeManager::FUN_00fe4150(uint32_t nBadge) const
{
    tPairNode* pFound;
    tPairNode** ppFound = mEventCounts.find(&pFound, &nBadge);
    if (*ppFound != mEventCounts.end())
        return (*ppFound)->mValue;
    return 5;
}

// @ 0x00fe4180
bool cSPBadgeManager::FUN_00fe4180(uint32_t nBadge) const
{
    tPairNode* pFound;
    tPairNode** ppFound = mEventCounts.find(&pFound, &nBadge);
    if (*ppFound != mEventCounts.end() && (*ppFound)->mValue <= 1)
        return true;
    return false;
}

// @ 0x00fe41c0
uint32_t cSPBadgeManager::GetReplacement(uint32_t nBadge) const
{
    uint32_t nKey = nBadge;
    tPairNode* pFound;
    tPairNode** ppFound = mBadgeMap.find(&pFound, &nKey);
    cPropertyList* pList = (*ppFound != mBadgeMap.end()) ? (cPropertyList*)(*ppFound)->mValue : 0;
    uint32_t nResult = 0;
    if (pList != 0 && pList->HasProperty(0x036c4148))
        GetPropertyAsKeyInstance(pList, 0x036c4148, &nResult);
    return nResult;
}

// @ 0x00fe4230
uint32_t cSPBadgeManager::FUN_00fe4230(uint32_t nBadge) const
{
    tVariant* pValue;
    tPairNode* pFound;
    tPairNode** ppFound = mBadgeMap.find(&pFound, &nBadge);
    if (*ppFound == mBadgeMap.end())
        return 0;
    cPropertyList* pList = (cPropertyList*)(*ppFound)->mValue;
    if (pList == 0)
        return 0;
    if (!pList->GetProperty(0x043333dd, &pValue))
        return 0;
    if (pValue->mType != 9)
        return 0;
    return *pValue->GetInt();
}

// @ 0x00fe42a0
int cSPBadgeManager::FUN_00fe42a0() const
{
    int i;
    for (i = 9; i >= 0; --i) {
        tPairNode* pFound;
        mEventCounts.find(&pFound, &g_badgeEventIds[i]);
        if (pFound != mEventCounts.end() && pFound->mValue <= 1)
            return i + 1;
    }
    return i + 1;
}

// @ 0x00fe43c0
bool cSPBadgeManager::FUN_00fe43c0(uint32_t nBadge, uint32_t nIndex) const
{
    tPairNode* pFound;
    mBadgeMap.find(&pFound, &nBadge);
    cPropertyList* pList = (pFound == mBadgeMap.end()) ? 0 : (cPropertyList*)pFound->mValue;
    tRecordArray* pRecords = pList->GetRecords(0x2cc641b);
    const tBadgeRecord* pData;
    uint32_t nCount;
    if ((pRecords->mFlags & 0x30) != 0) {
        nCount = pRecords->mnCount;
        pData = pRecords->mpData;
    } else {
        nCount = (pRecords->mType != 0) ? 1 : 0;
        pData = (pRecords->mType != 0) ? (const tBadgeRecord*)pRecords : 0;
    }
    for (uint32_t i = 0; i < nCount; ++i) {
        switch (pData[i].mId) {
        case 0x31611e3a: return nIndex == 0;
        case 0xd1fa0631: return nIndex == 1;
        case 0x47da68d6: return nIndex == 2;
        case 0xb9547ef2: return nIndex == 3;
        case 0x8924fd25: return nIndex == 4;
        case 0xa3e30892: return nIndex == 5;
        case 0x9e1db41e: return nIndex == 7;
        case 0xa29e0098: return nIndex == 8;
        case 0x2f45f0a4: return nIndex == 9;
        case 0x0aacb7e2: return nIndex == 10;
        case 0x1f6ee366: return nIndex == 11;
        case 0x37a262d3: return nIndex == 12;
        case 0x8067c9b6: return nIndex == 13;
        case 0x81f2f78a: return nIndex == 14;
        case 0xe84d2d88: return nIndex == 15;
        case 0x77eb981b: return nIndex == 16;
        case 0x56b5c1d1: return nIndex == 17;
        case 0x5e814d93: return nIndex == 30;
        case 0x697063d2: return nIndex == 18;
        case 0x44340b8f: return nIndex == 19;
        case 0xc1cb1d84: return nIndex == 20;
        case 0x0d403154: return nIndex == 21;
        case 0x376826b0: return nIndex == 22;
        case 0x48b1e34d: return nIndex == 23;
        case 0xe21c0641: return nIndex == 24;
        case 0x3872bad2: return nIndex == 25;
        case 0xadaca7eb: return nIndex == 26;
        case 0x49b76eb1: return nIndex == 27;
        case 0x25f2300a: return nIndex == 28;
        }
    }
    return false;
}

// @ 0x00fe45f0
const wchar_t* cSPBadgeManager::FUN_00fe45f0(uint32_t nBadge, bool bIgnoreStatus) const
{
    uint32_t nKey = nBadge;
    tPairNode* pFound;
    tHashNode* pHit;
    if (!bIgnoreStatus) {
        tPairNode** ppFound = mEventCounts.find(&pFound, &nKey);
        if (*ppFound == mEventCounts.end())
            return 0;
        if ((*ppFound)->mValue > 1)
            return 0;
    }
    tHashNode** ppHit = mHintStrings.find(&pHit, &nKey);
    if (*ppHit != mHintStrings.end())
        return (*ppHit)->mValue.c_str();
    return 0;
}

// @ 0x00fe46a0
bool cSPBadgeManager::FUN_00fe46a0(uint32_t nBadge) const
{
    uint32_t nKey = nBadge;
    tPairNode* pFound;
    tPairNode** ppFound = mEventCounts.find(&pFound, &nKey);
    if (*ppFound != mEventCounts.end() && (*ppFound)->mValue <= 1) {
        tHashNode* pHit;
        tHashNode** ppHit = mHintStrings.find(&pHit, &nKey);
        if (*ppHit != mHintStrings.end())
            return (*ppHit)->mValue.mpBegin == (*ppHit)->mValue.mpEnd;
    }
    return false;
}

// @ 0x00fe4710
void cSPBadgeManager::GetBadgeName(uint32_t nBadge, eastlWString& strOut) const
{
    uint32_t nKey = nBadge;
    tPairNode* pFound;
    tPairNode** ppFound = mBadgeMap.find(&pFound, &nKey);
    if (*ppFound == mBadgeMap.end())
        return;
    cPropertyList* pList = (cPropertyList*)(*ppFound)->mValue;
    if (pList == 0)
        return;
    cString text;
    GetPropertyAsText(pList, (const char*)0x043b3dc0, &text);
    const wchar_t* pszText = text.GetText();
    strOut.assign(pszText, pszText + WStrLen(pszText));
}

// @ 0x00fe47a0
void cSPBadgeManager::GetBadgeDescription(uint32_t nBadge, eastlWString& strOut) const
{
    tPairNode* pFound;
    tPairNode** ppFound = mBadgeMap.find(&pFound, &nBadge);
    if (*ppFound == mBadgeMap.end())
        return;
    cPropertyList* pList = (cPropertyList*)(*ppFound)->mValue;
    if (pList == 0)
        return;
    cString text;
    GetPropertyAsText(pList, (const char*)0x066e4315, &text);
    const wchar_t* pszText = text.GetText();
    strOut.assign(pszText, pszText + WStrLen(pszText));
}

// @ 0x00fe4830
void cSPBadgeManager::GetBadgeHintActionString(uint32_t nBadge, eastlWString& strOut) const
{
    tPairNode* pBadge;
    tPairNode** ppBadge = mBadgeMap.find(&pBadge, &nBadge);
    if (*ppBadge == mBadgeMap.end())
        return;
    cPropertyList* pList = (cPropertyList*)(*ppBadge)->mValue;
    if (pList == 0)
        return;
    *(uint32_t*)((char*)g_pSpaceTokenTranslator + 0x44) = nBadge;
    cString text;
    tPairNode* pEvent;
    tPairNode** ppEvent = mEventCounts.find(&pEvent, &nBadge);
    const char* pszName = (*ppEvent != mEventCounts.end() && (*ppEvent)->mValue <= 1)
                        ? g_badgePropNames + 0 : g_badgePropNames + 1;
    GetPropertyAsText(pList, pszName, &text);
    const wchar_t* pszText = text.GetText();
    strOut.assign(pszText, pszText + WStrLen(pszText));
}

// @ 0x00fe4900
void cSPBadgeManager::FUN_00fe4900(uint32_t nBadge, eastlWString& strOut) const
{
    tPairNode* pFound;
    tPairNode** ppFound = mBadgeMap.find(&pFound, &nBadge);
    if (*ppFound == mBadgeMap.end())
        return;
    cPropertyList* pList = (cPropertyList*)(*ppFound)->mValue;
    if (pList == 0)
        return;
    *(uint32_t*)((char*)g_pSpaceTokenTranslator + 0x44) = nBadge;
    cString text;
    GetPropertyAsText(pList, (const char*)0x063c233b, &text);
    const wchar_t* pszText = text.GetText();
    strOut.assign(pszText, pszText + WStrLen(pszText));
}

// @ 0x00fe49a0
void cSPBadgeManager::FUN_00fe49a0(uint32_t nBadge, eastlWString& strOut) const
{
    *(uint32_t*)((char*)g_pSpaceTokenTranslator + 0x44) = nBadge;
    const wchar_t* pszText = mHintText.GetText();
    strOut.assign(pszText, pszText + WStrLen(pszText));
}

// @ 0x00fe49e0
cSPBadgeManager::~cSPBadgeManager()
{
}

// @ 0x00fe4aa0
uint8_t FUN_00fe4aa0(cOutStream* pStream, const char* pszName, tU32Tree* pMap)
{
    bool bOk = true;
    if (pMap->mnSize != 0) {
        eastlWString text;
        pStream->v00();
        if (pszName != 0)
            FUN_0093c5a0(&text, pszName, -1);
        else
            FUN_00579a90(&text, 0);
        eastlWString name;
        FUN_0056e2d0(&name, &text);
        FUN_00f47380(text.mpBegin);
        pStream->v01();
        for (tPairNode* p = pMap->begin(); p != pMap->end(); p = (tPairNode*)RBTreeIncrement(&p->mBase))
            bOk = bOk;
        pStream->v02();
        FUN_00f47380(name.mpBegin);
    }
    return bOk;
}

// @ 0x00fe4be0
void __cdecl FUN_00fe4be0()
{
}

// @ 0x00fe4d60
void __cdecl FUN_00fe4d60()
{
}

// @ 0x00fe4e80
void __cdecl FUN_00fe4e80()
{
}

// @ 0x00fe4fa0
void __fastcall cSPBadgeManagerCtor(void* this_, int unused)
{
    (void)this_;
}

// @ 0x00fe5430
void* __fastcall FUN_00e39fb0(void* pTree, void* unused, uint32_t* ppOut, const uint32_t* pKey); // 0x00e39fb0 (map lower_bound)
uint32_t* __fastcall FUN_00de7630(void* pTree, void* unused, const uint32_t* pKey);             // 0x00de7630 (map operator[])
void* __cdecl    FUN_00883860();                                      // 0x00883860 (message server)
struct cSelf {
    void FUN_01017270(int a, int b, int c);              // 0x01017270
    void FUN_00e17470(void* pArg);                       // 0x00e17470
};
struct V14Obj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(int a, int b, int c);   // +0x14
};
namespace SP {
void __thiscall cSPBadgeManager_s00fe_4be0::FUN_00fe5430(uint32_t nBadge, int nCount)
{
    tEventNode* pFound;
    if (*((tEventTree*)((char*)this + 0x64))->find(&pFound, &nBadge) ==
            (tEventNode*)&((tEventTree*)((char*)this + 0x64))->mAnchor)
        ((tEventTree*)((char*)this + 0x64))->operator[](&nBadge)[0] = (uint32_t)nCount;
    else
        ((tEventTree*)((char*)this + 0x64))->operator[](&nBadge)[0] += (uint32_t)nCount;
    ((V14Obj*)FUN_00883860())->v14(0x38cf2fb, 0, 0);
    cUIMissionCardPanel* pUI = FUN_00b3d400();
    if (mpCurrentCard != 0 && pUI != 0) {
        if (((cSPBadgeManager*)this)->FUN_00fe43c0(mpCurrentCard, nBadge))
            pUI->RemoveBadgeCard(mpCurrentCard);
    }
}
}  // namespace SP

// @ 0x00fe54d0
namespace SP {
uint32_t __thiscall cSPBadgeManager_s00fe_4be0::FUN_00fe54d0(Property* pProperty)
{
    cBadgeObject** ppSlot = mBadgeMap.FUN_00dd85c0(&pProperty);
    cBadgeObject* pBadge = *ppSlot;
    if (pBadge && pBadge->ResolveProperty(0x60b5892u, &pProperty) && pProperty->mType == 0xa)
        return *pProperty->GetUInt();
    return 0;
}
}  // namespace SP

// @ 0x00fe5520
namespace SP {
ResourceKey* __thiscall cSPBadgeManager_s00fe_4be0::GetBadgeImageKey(ResourceKey* pOut, uint32_t nBadge)
{
    pOut->instanceID = 0;
    pOut->typeID = 0;
    pOut->groupID = 0;

    switch (*mStatus[&nBadge]) {
    case 0:
    case 1:
        GetPropertyAsKey(*mBadgeMap.FUN_00dd85c0((Property**)&nBadge), 0x02cb228a, pOut);
        break;
    case 2:
    case 3:
    case 4:
        GetPropertyAsKey(*mBadgeMap.FUN_00dd85c0((Property**)&nBadge), 0x02cb2286, pOut);
        break;
    }
    if (pOut->typeID == 0x0252408e)
        pOut->typeID = 0x2f7d0004;
    return pOut;
}
}  // namespace SP

// @ 0x00fe55b0
namespace SP {
void __thiscall cSPBadgeManager_s00fe_4be0::TestRequirement()
{
}
}  // namespace SP

// @ 0x00fe5a20
void cSPBadgeManager_s00fe_5a20::UnlockBadge(uint32 badge)
{
    GetGMgr()->OnBadgeUnlocked(badge);
    TerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
    mStatus[badge] = 1;
    if (!IsMasterBadgePart(badge))
        mStage[badge] = GetMasterBadgeCount() + 1;
    IPropList* list = mBadges[badge];
    SpaceGame* game = SpaceGameGet();
    SubSystem* sub = game->GetSubSystem(8);
    sub->Activate(8);
    sub->data->badge = badge;
    if (list) {
        uint32 prereq = 0;
        GetPropertyAsKeyInstance(list, 0x36c4148, &prereq);
        if (prereq) mStatus[prereq] = 0;
    }
    bool isCurrent = (badge == mCurrentBadgeCard);
    if (isCurrent && mCurrentBadgeCard != 0) {
        MissionCardPanel* panel = GetCardPanel();
        if (mCurrentBadgeCard != 0 && panel)
            panel->RemoveBadgeCard(mCurrentBadgeCard);
        mCurrentBadgeCard = 0;
    }
    for (RBNode* it = mStatus.anchor.mpNodeLeft; it != &mStatus.anchor; it = RBTreeIncrement(it)) {
        uint32 childKey = it->key;
        RBNode* found = mBadges.find(childKey);
        if (found != mBadges.end() && found->value != 0) {
            uint32 prereq = 0;
            GetPropertyAsKeyInstance((IPropList*)found->value, 0x36c4148, &prereq);
            if (prereq == badge) {
                mStatus[childKey] = 2;
                if (isCurrent) ShowBadgeCard(childKey);
            }
        }
    }
    Inventory* inv = SpaceGameGet()->GetPlayerInventory();
    ToolManager* toolMgr = GetToolManager();
    if (list) {
        if (list->Has(0x43333dd)) {
            Property_s00fe_5a20* p;
            int v = (int)sphere;
            if (list->GetProperty(0x43333dd, &p) && p->type == 9) v = *PropData(p);
            AddToBadgeProgress(0xc, v);
        }
        if (list->Has(0x2cb2281)) {
            Property_s00fe_5a20* p = list->GetPropertyRef(0x2cb2281);
            int n = PropArrayCount(p);
            ResourceKey* keys = PropArrayData(p);
            if (n > 0) {
                for (int i = 0; i < n; i++, keys++) {
                    ResourceKey key;
                    key.instanceID = keys->instanceID;
                    key.typeID = 0;
                    key.groupID = 0;
                    if (key.instanceID != kNullKey.instanceID || kNullKey.typeID != 0 || kNullKey.groupID != 0) {
                        if (!inv->HasTool(&key)) {
                            Tool* tool = 0;
                            if (toolMgr->CreateToolFromToolID(&key, &tool))
                                inv->AddTool(tool, 0, 1);
                            if (tool) tool->Release();
                        }
                    }
                }
            }
        }
        Property_s00fe_5a20* p;
        if (list->GetProperty(0x5d25642, &p) && p->type == 1) {
            char* b = (char*)((p->flags & 0x30) ? *(char**)p : (char*)p);
            if (*b) {
                sphere->Unlock(0);
                EventLog()->PostFeedbackEvent(0x544d10b3, 0x131a9f54, 0, 0, 1, 0);
            }
        }
        if (list->GetProperty(0x3570ad0, &p) && p->type == 9) {
            int v = *PropData(p);
            if (v != 0) inv->GrantReward(v);
        }
        cString_s00fe_5a20 text;
        GetPropertyAsText(list, 0x2cb2284, &text);
        uint32 evt = EventLog()->PostFeedbackEvent(0x6da7f9a3, 0x131a9f54, 0, 0, 1, 0);
        EventLog()->ModifyEventText(evt, text.GetText());
    }
    GetUFOSimulator()->CalcMaxTravelDistance();

    StackMsg msg(badge);
    GetMessagingServer()->MessageSend(0x38cf2fc, &msg, 0);

    int index = 0;
    switch (badge) {
    case 0x58b78701: index = 1; break;
    case 0x58b78702: index = 2; break;
    case 0x58b78703: index = 3; break;
    case 0x58b78704: index = 4; break;
    case 0x58b78705: index = 5; break;
    case 0x58b78706: index = 6; break;
    case 0x58b78707: index = 7; break;
    case 0x58b78708: index = 8; break;
    case 0x58b78709: index = 9; break;
    case 0xa9e986a3: index = 10; break;
    }
    if (index != 0) {
        GetGMgr()->SetMasterBadgeFlag(1);
        Z12 a = {0, 0, 0}, b = {0, 0, 0}, c = {0, 0, 0}, d = {0, 0, 0};
        FUN_00e39ab0(0x687b36a1, 0, &c, &b, 0, badge, &a, &d);
        FUN_00fe3d30(index, GetGNamed()->Lookup("SPG_MasterBadge", 1, 0, 0, 0, 0));
    } else {
        GetGMgr()->SetMasterBadgeFlag(0);
    }
    AchievementsController()->AutoTest(0xb379fbce, 1);

    if (badge == 0x4dc4aacb) {
        void** vt = (void**)0x13eb844;
        HeapMsg* m = (HeapMsg*)OperatorNew(0x40, "Simulator", 0, 0, 0, 0);
        if (m) {
            m->id30 = 0;
            *(void**)m = (void*)0x13eb90c;
            _InterlockedExchange((long*)&m->refcount, 0);
            *(void**)m = vt;
            m->mask38 = 0;
            ((VFn)vt[1])(m);
        }
        m->id30 = 0x64e43b9;
        m->slot0 = 0x4dc4aacb;
        MessageServer()->Post(m->id30, m, 0, 0);
        m->Release();
    } else if (badge == 0xa9e986a3) {
        uint32 id = 0;
        switch (GetPlayerEmpire()->archetype) {
        case 9: id = 0x33f68284; break;
        case 10: id = 0x39b4e19a; break;
        case 11: id = 0x13ebce3c; break;
        case 12: id = 0x278f32d4; break;
        case 13: id = 0xa9afd0df; break;
        case 14: id = 0xad1f3843; break;
        case 15: id = 0xdc2042dc; break;
        case 16: id = 0x53f9ee27; break;
        case 17: id = 0xf48bdca4; break;
        case 18: id = 0x7dca8049; break;
        }
        AchievementsController()->AwardAchievement(id);
        if (AchievementsController()->IsAwarded(0xa9afd0df) &&
            AchievementsController()->IsAwarded(0x53f9ee27) &&
            AchievementsController()->IsAwarded(0xad1f3843) &&
            AchievementsController()->IsAwarded(0xdc2042dc) &&
            AchievementsController()->IsAwarded(0x13ebce3c) &&
            AchievementsController()->IsAwarded(0x39b4e19a) &&
            AchievementsController()->IsAwarded(0x278f32d4) &&
            AchievementsController()->IsAwarded(0x33f68284) &&
            AchievementsController()->IsAwarded(0xf48bdca4) &&
            AchievementsController()->IsAwarded(0x7dca8049))
            AchievementsController()->AwardAchievement(0xbc6a0553);
    }
}

// @ 0x00fe6210
long double cSPBadgeManager_s00fe_5a20::GetProgressScore(uint32 id, int mode, void* buf, uint32 len)
{
    uint32 key = id;
    void* slot = 0;
    void** found = MapFind((void*)&mBadges, &slot, &key);
    ReqVec* reqs = (*found != (void*)&mBadges.anchor) ? (ReqVec*)((uint32*)*found)[5] : 0;

    ReqVec* replReqs = 0;
    int replacement = GetReplacement(this, id);
    if (replacement != 0) {
        uint32 key2 = (uint32)replacement;
        void* slot2 = 0;
        void** found2 = MapFind((void*)&mBadges, &slot2, &key2);
        if (*found2 != (void*)&mBadges.anchor)
            replReqs = (ReqVec*)((uint32*)*found2)[5];
    }

    int count = 0;
    int data = 0;
    EnumRequirements(reqs, 0x2cc641b, &count, &data);
    float total = 0.0f;
    for (int i = 0; i < count; ++i) {
        uint32 reqId = (uint32)((int*)data)[i * 3];
        int have = reqs ? reqs->Amount(reqId) : 0;
        int repl = replReqs ? replReqs->Amount(reqId) : 0;
        if (have <= 0)
            continue;
        if (mode == 0) {
            int test = TestRequirement(reqId);
            int span = have - repl;
            if (span == 0)
                span = 1;
            float frac = (float)(test - repl) / (float)span;
            if (frac <= 1.0f)
                total += (frac < 0.0f) ? 0.0f : frac;
            else
                total += 1.0f;
        } else if (mode == 1) {
            int test = TestRequirement(reqId);
            int amount = (test <= have) ? test : have;
            total += (float)((amount < 0) ? 0 : amount);
        } else if (mode == 2) {
            total += (float)have;
        }
    }
    if (mode == 0 && count != 0)
        total = total / (float)count;
    return (long double)total;
}

// @ 0x00fe6490
void cSPBadgeManager_s00fe_5a20::OnTick(int delta)
{
    TickProbe0();                                         // 0xb3d4a0
    if (TickProbe1() != 0)                                // 0xae9390
        return;
    SpaceGameGet();
    if (TickProbe2() != 0)                                // 0x1075500
        return;
    void* world = GetWorldMode();                         // 0xb3d4d0
    if (*(int*)((char*)world + 0x2c) == 1 || *(int*)((char*)world + 0x2c) == 2)
        return;
    SpaceGameGet();
    if (TickProbe3() != 0)                                // 0xb18e40
        return;
    void* sg = SpaceGameGet();
    if (*(int*)((char*)sg + 0x20) != 0) {
        SpaceGameGet();
        if (TickProbe4() != 0)                            // 0xd09660
            return;
    }
    if ((*(unsigned char*)((char*)GetGameTimeManager() + 0x48) & 1) != 0)
        return;
    SpaceGame* game = SpaceGameGet();
    if (game->GetAvatar() != 0) {
        SpaceGameGet();
        game->GetAvatar();
        if (TickProbe5() != 0)                            // 0xff6550
            return;
    }

    mTickAccum += delta;

    EventNode* node = (EventNode*)mStatus.anchor.mpNodeLeft;
    while (node != (EventNode*)&mStatus.anchor) {
        if (node->mState18 == 2 || node->mState18 == 3) {
            bool allDone = true;
            bool spaceOnly = false;
            PropsObj* props = (PropsObj*)BadgeProps(node->mId);   // 0x642c10
            if (props != 0) {
                props->GetKey(0x2cc641b);                 // requirement list key
                int left = RequirementCount(props);       // 0x571ef0
                int* list = RequirementList();            // 0x446ff0
                if (left < 1) {
                    if (mSuppressUnlock == 0)
                        UnlockBadge(node->mId);
                } else {
                    for (; left != 0; --left, list += 3) {
                        int reqId = list[0];
                        int need = 0;
                        GetPropertyAsInt(props, (uint32)reqId, &need);
                        if (TestRequirement((uint32)reqId) < need)
                            allDone = false;
                        if (reqId == 0x6f7f0ed || reqId == 0x3dce555d)
                            spaceOnly = true;
                    }
                    if (allDone && mSuppressUnlock == 0)
                        UnlockBadge(node->mId);
                }
                if (spaceOnly && node == (EventNode*)mLastEvent)
                    ReportBadgeProgress(node->mId);       // 0xe17470
            }
        }
        node = (EventNode*)RBTreeIncrement((RBNode*)node);
    }
}

// @ 0x00fe6690
long double EventMap::GetScore(uint32 id)
{
    uint32 key = id;
    void* slot = 0;
    void** found = MapFind((void*)&mEvents, &slot, &key);
    EventNode* node = (EventNode*)*found;
    if (node != (EventNode*)&mEvents.anchor && node->mCount14 < 2)
        return 1.0;
    return mOwner->GetProgressScore(id, 0, 0, 0);
}

// @ 0x00fe66f0
int EventMap::GetScoreRounded(uint32 id)
{
    uint32 key = id;
    void* slot = 0;
    void** found = MapFind((void*)&mEvents, &slot, &key);
    EventNode* node = (EventNode*)*found;
    bool counted = node != (EventNode*)&mEvents.anchor && node->mCount14 <= 1;
    return (int)mOwner->GetProgressScore(id, counted ? 2 : 1, 0, 0);
}

// @ 0x00fe6770
int FeedbackScoreForMode2(uint32 id)
{
    extern long double BadgeScoreFree(uint32 id, int mode);       // 0xfe6210 (free-call form)
    return (int)BadgeScoreFree(id, 2);
}

// @ 0x00fe67b0
long double EventMap::GetWeightedScore()
{
    uint32 step = (uint32)GetEventIndex();
    float base = (float)step;
    if (step < 10)
        return (GetScore(g_eventSteps[step]) + (long double)base) * (long double)0.1f;
    return (long double)base * (long double)0.1f;
}

// @ 0x00fe6800
void EventMap::FormatScore(uint32 id, void* text)
{
    wchar_t buf[64];
    SetNumberString((int)mOwner->GetProgressScore(id, 1, 0, 0), 0, buf, 0x40);
    WStr_Format(text, (const wchar_t*)0x13f5c04, buf);
    SetNumberString((int)mOwner->GetProgressScore(id, 2, 0, 0), 0, buf, 0x40);
    AppendFormatted(text, (const wchar_t*)0x149431c, buf);
}
