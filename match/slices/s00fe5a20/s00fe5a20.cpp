// Slice s00fe5a20: SP::cSPBadgeManager::UnlockBadge (2032 B, __thiscall, 1 arg, ret 4).
// Marks a badge unlocked (status 1), records its stage, clears the card shown for it, reveals badges
// whose prerequisite is this badge, then applies the badge's reward properties (terrain sphere progress,
// tool grants, feedback events, event-log text), posts message 0x38cf2fc, updates the master-badge
// feedback and the achievement controller, and (for two special badges) posts a UI message or awards
// species achievements.
// Names follow ModAPI cBadgeManager and the 2008 PDB; layout is the retail one (status map at +0x2c).
// Flags: /O2 /MD /Gy /TP (no /EHsc: the cString local has no EH frame).
#include "types.h"
#include <intrin.h>

typedef uint32_t uint32;

struct ResourceKey {
    uint32 instanceID, typeID, groupID;
};
extern ResourceKey kNullKey;   // 0x016d9fb4

// ---- property lists ---------------------------------------------------------------------------
struct Property {
    char pad0[8];
    int count;          // +8 (indirect arrays)
    unsigned short flags;   // +0x10, bits 0x30 = indirect
    unsigned short type;    // +0x12
};
// Inline accessors used by the retail code (not the out-of-line Property::GetInt).
static __forceinline int* PropData(Property* p) { return (p->flags & 0x30) ? *(int**)p : (int*)p; }
static __forceinline int PropArrayCount(Property* p) { return (p->flags & 0x30) ? p->count : (p->type != 0); }
static __forceinline ResourceKey* PropArrayData(Property* p)
{
    return (ResourceKey*)((p->flags & 0x30) ? *(void**)p : (p->type ? (void*)p : (void*)0));
}

struct IPropList {
    virtual void v00();
    virtual void Release();                                  // +4
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool Has(uint32 id);                             // +0x1c
    virtual void v20();
    virtual bool GetProperty(uint32 id, Property** pp);      // +0x24
    virtual Property* GetPropertyRef(uint32 id);             // +0x28
};
bool GetPropertyAsKeyInstance(IPropList* list, uint32 id, uint32* value);   // 0x6a12a0 cdecl
struct cString {
    uint32 mData[5];
    cString();                          // 0x6b5060
    ~cString();                         // 0x6b5240
    const wchar_t* GetText();           // 0x6b55c0
};
bool GetPropertyAsText(IPropList* list, uint32 id, cString* out);           // 0x6a1360 cdecl

// ---- red-black tree nodes (retail EASTL layout) -----------------------------------------------
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

// ---- other game objects -------------------------------------------------------------------------
struct IRef { virtual void v0(); virtual void Release(); };

struct Tool { virtual void v0(); virtual void v1(); virtual void Release(); };   // release at +8
struct ToolManager { bool CreateToolFromToolID(ResourceKey* id, Tool** out); };    // 0x104e340 ret 8
struct Inventory {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
    virtual bool HasTool(ResourceKey* id);                       // +0x74
    virtual void v78(); virtual void v7c();
    virtual void AddTool(Tool* t, int a, int b);                 // +0x80
    virtual void v84(); virtual void v88(); virtual void v8c(); virtual void v90();
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
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
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

// ---- messages ---------------------------------------------------------------------------------
typedef void (__thiscall *VFn)(void*);
struct HeapMsg {
    virtual void v0(); virtual void AddRef(); virtual void Release();
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

// ---- the badge manager --------------------------------------------------------------------------
struct cSPBadgeManager {
    char pad0[0x10];
    PropMap mBadges;            // +0x10 (anchor +0x14)
    StatusMap mStatus;          // +0x2c (anchor +0x30)
    StageMap mStage;            // +0x48
    char pad64[0xa4 - 0x64];
    uint32 mCurrentBadgeCard;   // +0xa4

    bool IsMasterBadgePart(uint32 badge);         // 0xfe3df0 ret 4
    int GetMasterBadgeCount();                    // 0xfe42a0
    void ShowBadgeCard(uint32 badge);             // 0xfe3cc0 ret 4
    void AddToBadgeProgress(int ev, int value);   // 0xfe5430 ret 8
    void UnlockBadge(uint32 badge);               // 0xfe5a20
};

// @ 0x00fe5a20
void cSPBadgeManager::UnlockBadge(uint32 badge)
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
            Property* p;
            int v = (int)sphere;
            if (list->GetProperty(0x43333dd, &p) && p->type == 9) v = *PropData(p);
            AddToBadgeProgress(0xc, v);
        }
        if (list->Has(0x2cb2281)) {
            Property* p = list->GetPropertyRef(0x2cb2281);
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
        Property* p;
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
        cString text;
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
