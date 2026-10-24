// Slice s00c47a10 -- SP::cSPMission (the space-stage mission object): the mission state machine
// (SetState / TriggerUIUpdate / DataExportOnInit), the accept/validate helpers, the planet-clue
// picker and the UI text helpers.
//
// Subject object:
//   * SP::cSPMission: vtable at +0, the mission state at +0x84, the target planet at +0x9c, the
//     reward/beacon window at +0x78, two eastl::wstring labels at +0x14c/+0x15c, the give-on-accept
//     key at +0x170..+0x178, the property list at +0x180 and the export planet at +0x1e8.
//
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

#define PV(n) virtual void pv##n();

// --------------------------------------------------------------------------- opaque services
#include <intrin.h>
extern "C" long __cdecl _InterlockedExchange(volatile long* target, long value);
#pragma intrinsic(_InterlockedExchange)

struct cSPUIEventLog {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    void PostFeedbackEvent();                           // 0x00dd8640
};

struct MessageServer;
struct cSPMission;
namespace SP {
    void* GetMissionManager();                          // 0x00feb9f0
    void* SpaceGameGet();                               // 0x01002bd0
    cSPUIEventLog* __stdcall EventLog(uint32_t a, uint32_t b, uint32_t c,
                                      uint32_t d, uint32_t e, uint32_t f); // 0x00b3d3e0
    void  GetPropertyAsKeyInstance(void* props, uint32_t id, void* out); // 0x006a12a0
}
MessageServer* GetMessageServer();                      // 0x0067dcc0
void* __stdcall FUN_01046fc0(void* a, void* b);         // 0x01046fc0
extern const float g_Inv255;                            // 0x013eecd4  1.0f / 255.0f

struct cMeshNode {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
    virtual void v16(int kind, float* rgb, int flag);   // +0x40
};

struct MeshHandle {
    void        FUN_01044db0();                         // 0x01044db0
    cMeshNode*  FUN_01045120();                         // 0x01045120
};
void  SortPlanetsByRadius(void* range);                 // 0x01022530
void* FUN_01021260();                                   // 0x01021260
void* FUN_01021300();                                   // 0x01021300
void* FUN_00aed4d0();                                   // 0x00aed4d0

// --------------------------------------------------------------------------- interfaces
struct WString {                                        // eastl::wstring (0x10 bytes)
    wchar_t* mBegin;                                    // +0x00
    wchar_t* mEnd;                                      // +0x04
    uint32_t mCapacity;                                 // +0x08
    uint32_t mPad0C;                                    // +0x0c
    void assign(const wchar_t* first, const wchar_t* last);     // 0x00423650
    void clear() {
        if (mBegin != mEnd) {
            *mBegin = 0;
            mEnd = mBegin;
        }
    }
};

struct cString_s006b_47a0 {                             // SP::cString (0x18 bytes)
    uint32_t mPad00[6];
    void Construct();                                   // 0x006b5060
    void Destruct();                                    // 0x006b5240
    const wchar_t* GetText();                           // 0x006b55c0
};

struct cTextFormatter {                                 // localized text builder
    PV(0) PV(1) PV(2)
    virtual void* v3(void* a, void* b, void* c, void* d);           // +0x0c
    PV(4) PV(5) PV(6) PV(7) PV(8)
    virtual void* v9(void* a, void* b, void* c, void* d, void* e, void* f); // +0x24
};

// SP::IntVector, the guild's fixed record store.
namespace SP {
struct IntVector {
    int32_t* mBegin;                                    // +0x00
    int32_t* mEnd;                                      // +0x04
    int32_t* mCapacity;                                 // +0x08
    uint8_t* mData;                                     // +0x0c
    void resize(uint32_t count);                        // 0x007eb820
};
}

struct SimGame {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
    void* f5180(int a);                                 // 0x01005180
};

struct GuildRecord {                                    // record behind SP::IntVector::mData
    uint8_t mPad00[0x1c];
    int32_t mField1C;                                   // +0x1c
    float   mField20;                                   // +0x20
    int32_t mField24;                                   // +0x24
    float   mField28;                                   // +0x28
};

// --------------------------------------------------------------------------- messages
struct cMessageHeader {                                 // non-polymorphic message header
    uint32_t mParam0;                                   // +0x08
    uint32_t mParam1;                                   // +0x0c
    uint32_t mField10[8];                               // +0x10
    uint32_t mMessageID;                                // +0x30
    uint32_t mField34;                                  // +0x34
    cMessageHeader(uint32_t id) : mMessageID(id) {}
};

class RefBaseA22 {                                      // ??_7RefBaseA22@@6B@ (+0)
public:
    virtual void _v00();
    volatile long mnRefCount;                           // +0x04
    RefBaseA22() { _InterlockedExchange(&mnRefCount, 0); }
};

class cMissionUpdateMessage : public cMessageHeader, public RefBaseA22 {
public:
    void* mpData;                                       // +0x38
    uint32_t mField3C;                                  // +0x3c
    cMissionUpdateMessage() : cMessageHeader(0x38cf2fd), mpData(0) {}
    virtual void _v00();
    void Destruct();                                    // 0x00421cf0
};

struct MessageServer {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void PostMessage(uint32_t id, void* msg, uint32_t flags);   // +0x14
};

// --------------------------------------------------------------------------- cSPMission
struct cSPMission {
    // ---- vtable ----
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
    PV(10) PV(11) PV(12) PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19)
    PV(20) PV(21) PV(22) PV(23) PV(24) PV(25) PV(26) PV(27) PV(28) PV(29)
    PV(30) PV(31) PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
    PV(40)
    virtual void* pv41();                               // +0xa4  current mission context object
    PV(42) PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49)
    PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59)
    virtual float pv60();                               // +0xf0  reward timer base
    PV(61) PV(62) PV(63) PV(64) PV(65) PV(66) PV(67) PV(68) PV(69)
    PV(70) PV(71) PV(72) PV(73) PV(74) PV(75) PV(76) PV(77) PV(78) PV(79)
    PV(80)
    virtual void pv81();                                // +0x144
    PV(82) PV(83) PV(84) PV(85) PV(86) PV(87)
    virtual bool pv88();                                // +0x160
    virtual bool pv89();                                // +0x164
    PV(90) PV(91) PV(92) PV(93) PV(94) PV(95) PV(96) PV(97) PV(98)
    virtual bool pv99();                                // +0x18c
    PV(100)
    virtual void pv101();                               // +0x194

    // ---- data ----
    uint8_t  mPad04[0x78 - 0x04];                       // +0x04
    int32_t  mField78;                                  // +0x78  beacon/reward window id
    uint8_t  mPad7C[0x84 - 0x7c];                       // +0x7c
    uint32_t mState84;                                  // +0x84  mission state
    uint8_t  mPad88[0x8c - 0x88];                       // +0x88
    int32_t  mField8C;                                  // +0x8c
    uint8_t  mPad90[0x94 - 0x90];                       // +0x90
    int32_t  mField94;                                  // +0x94
    uint8_t  mPad98[0x9c - 0x98];                       // +0x98
    void*    mPlanet9C;                                 // +0x9c  target planet
    float    mFieldA0;                                  // +0xa0
    int32_t  mFieldA4;                                  // +0xa4
    uint8_t  mPadA8[0xf4 - 0xa8];                       // +0xa8
    int32_t  mFieldF4;                                  // +0xf4  clue kind
    int32_t  mFieldF8;                                  // +0xf8
    int32_t  mFieldFC;                                  // +0xfc  clue planet index
    void*    mField100;                                 // +0x100
    void*    mField104;                                 // +0x104
    void**   mVec108;                                   // +0x108
    void**   mVec10C;                                   // +0x10c
    uint8_t  mPad110[0x130 - 0x110];                    // +0x110
    uint32_t mFlags130;                                 // +0x130
    uint8_t  mPad134[0x14c - 0x134];                    // +0x134
    WString  mStr14C;                                   // +0x14c
    WString  mStr15C;                                   // +0x15c
    void*    mField16C;                                 // +0x16c
    void*    mKey170;                                   // +0x170
    void*    mKey174;                                   // +0x174
    void*    mKey178;                                   // +0x178
    void*    mField17C;                                 // +0x17c
    void*    mProps180;                                 // +0x180  mission property list
    int32_t  mField184;                                 // +0x184
    uint8_t  mPad188[0x1e8 - 0x188];                    // +0x188
    void*    mField1E8;                                 // +0x1e8  export planet

    // ---- recovered methods ----
    void   OnAccept();                                  // 0x00c47a10
    void   FUN_00c47b10(int32_t flag);                  // 0x00c47b10
    void   SetState(uint32_t state);                    // 0x00c47cc0
    void   TriggerUIUpdate();                           // 0x00c47d80
    void   DataExportOnInit();                          // 0x00c483d0
    void   FUN_00c48470(int32_t* key);                  // 0x00c48470
    bool   Validate();                                  // 0x00c484e0
    bool   PickPlanetClue();                            // 0x00c48600
    void   FUN_00c486f0(WString* out);                  // 0x00c486f0
    void   FUN_00c48740(WString* out);                  // 0x00c48740
    void   FUN_00c48790(WString* out);                  // 0x00c48790
    void   GetText(WString* out, int a);                // 0x00c487d0
    void   FUN_00c48900(WString* out);                  // 0x00c48900
    void   FUN_00c48940(WString* out);                  // 0x00c48940
    void*  FUN_00c452a0();                              // 0x00c452a0
    void*  GetOwnerEmpire();                            // 0x00c451e0
    void   GiveOnAcceptItems(bool on);                  // 0x00c46e20
    void   ExportPlanet(void* planet, uint32_t key);    // 0x00c47350
    void   ExportSpecies(void* species, uint32_t key);  // 0x00c473f0
};

// --------------------------------------------------------------------------- other subjects
struct TokenTranslator {                                // *0x016e0d08
    uint8_t  mPad00[0x18];
    void*    mField18;                                  // +0x18  current mission context
    int32_t  mField1C;                                  // +0x1c
    uint8_t  mPad20[0x48 - 0x20];
    void*    mField48;                                  // +0x48
};

extern TokenTranslator* g_pTokenTranslator;             // 0x016e0d08
extern cString_s006b_47a0 g_MissionLabel010030;         // 0x0168f010
extern cString_s006b_47a0 g_MissionLabel01002F;         // 0x0168ef34

struct RandomLinearCongruential {
    uint32_t RandomUint32Uniform(uint32_t range);       // 0x00a68fb0
};
extern RandomLinearCongruential g_Random;               // 0x01601760
extern const float g_FloatOne;                          // 0x0146d130  1.0f

struct cPlanetList;                                     // raw planet record range

struct PlanetNameHolder {                               // *(*cPlanet+0x13c)
    WString* FUN_00bb9de0();                            // 0x00bb9de0
    cPlanetList* FUN_00bba790();                        // 0x00bba790
    void     FUN_00bb9c10(int a);                       // 0x00bb9c10
};

struct cStarRecord {                                    // *(*cPlanet+0x13c)
    bool              FUN_00b8d970();                   // 0x00b8d970
    PlanetNameHolder* FUN_00b8de30();                   // 0x00b8de30
};

struct cPlanet {
    uint8_t      mPad00[0x13c];
    cStarRecord* mField13C;                             // +0x13c
    WString*     GetName();                             // 0x00c707e0
    int32_t      FUN_00c70880();                        // 0x00c70880
};

struct Empire {
    void* FUN_00c30c60();                               // 0x00c30c60
};

struct Species {
    WString* FUN_00bb9de0();                            // 0x00bb9de0
};

struct cPlanetList {                                    // raw planet record range
    void** mBegin;                                      // +0x00
    void** mEnd;                                        // +0x04
};

struct cPlanetRange {                                   // radius-sorted planet vector (0x14 bytes)
    void** mBegin;                                      // +0x00
    void** mEnd;                                        // +0x04
    void*  mCapacity;                                   // +0x08
    void*  mAllocator;                                  // +0x0c
    void*  mField10;                                    // +0x10
    void Construct(cPlanetList* src);                   // 0x00ba95a0
    void Destroy();                                     // 0x00ae6970
};

struct MissionManager {
    uint8_t  mPad00[0x1c];
    int32_t  mField1C;                                  // +0x1c
    void     FUN_00fede40(int32_t a);                   // 0x00fede40
    void     FUN_00feba10();                            // 0x00feba10
    void     FUN_00feca20(void* mission);               // 0x00feca20
    uint32_t FUN_00febf80(int32_t a);                   // 0x00febf80
    void     FUN_00bb9c10();                            // 0x00bb9c10
    void     FUN_00c31a00(int32_t a);                   // 0x00c31a00
};

struct PropertyList {
    PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
    virtual bool v7(uint32_t key);                      // +0x1c  HasKey
};

// --------------------------------------------------------------------------- helpers
static uint32_t WcsLen(const wchar_t* p)
{
    const wchar_t* start = p;
    while (*p != 0) {
        ++p;
    }
    return (uint32_t)(p - start);
}

// --------------------------------------------------------------------------- 0x00c47a10
// Accept the mission: refresh the mission manager, resize the guild reward record from the mission
// beacon and hand the reward timer to the item pass.
// @ 0x00c47a10
void cSPMission::OnAccept()
{
    if (((uint8_t)(mFlags130 >> 3) & 1) != 0) {
        ((MissionManager*)SP::GetMissionManager())->FUN_00fede40(mField78);
        ((MissionManager*)SP::GetMissionManager())->FUN_00feba10();
    }
    ((MissionManager*)SP::GetMissionManager())->FUN_00feca20(this);
    pv101();
    SP::IntVector* guild = (SP::IntVector*)((SimGame*)SP::SpaceGameGet())->f5180(5);
    guild->resize(0xc);
    float timer = pv60();
    ((GuildRecord*)guild->mData)->mField1C = mField78;
    ((GuildRecord*)guild->mData)->mField20 = mFieldA0;
    ((GuildRecord*)guild->mData)->mField24 = mFieldA4;
    ((GuildRecord*)guild->mData)->mField28 = timer;
    ((GuildRecord*)guild->mData)->mField28 = timer + g_FloatOne;
    GiveOnAcceptItems(true);
    pv81();
    if (mField1E8 != 0) {
        cStarRecord* record = ((cPlanet*)mField1E8)->mField13C;
        record->FUN_00b8de30()->FUN_00bb9c10(1);
    }
    int32_t count = mField184;
    if (count > 0) {
        void* player = FUN_01021300();
        if (player != 0) {
            ((MissionManager*)player)->FUN_00c31a00(-count);
        }
    }
}

// --------------------------------------------------------------------------- 0x00c47b10
// Show or hide the mission's mesh markers (beacon, target, and each listed object).
// @ 0x00c47b10
void cSPMission::FUN_00c47b10(int32_t flag)
{
    ((MeshHandle*)FUN_01046fc0(mField104, (void*)flag))->FUN_01044db0();
    ((MeshHandle*)FUN_01046fc0(mField100, (void*)flag))->FUN_01044db0();
    for (uint32_t i = 0; i < (uint32_t)(mVec10C - mVec108); ++i) {
        ((MeshHandle*)FUN_01046fc0(mVec108[i], (void*)flag))->FUN_01044db0();
    }
    if ((int8_t)flag == 0) {
        return;
    }
    void* owner = (mField17C != 0) ? mField17C : (void*)this;
    uint32_t color = ((MissionManager*)SP::GetMissionManager())->FUN_00febf80((int32_t)owner);
    float rgb[3];
    rgb[0] = (float)((color >> 16) & 0xff) * g_Inv255;
    rgb[1] = (float)((color >> 8) & 0xff) * g_Inv255;
    rgb[2] = (float)(color & 0xff) * g_Inv255;
    cMeshNode* node = ((MeshHandle*)FUN_01046fc0(0, mField104))->FUN_01045120();
    if (node != 0) {
        node->v16(5, rgb, 1);
    }
    node = ((MeshHandle*)FUN_01046fc0(0, mField100))->FUN_01045120();
    if (node != 0) {
        node->v16(5, rgb, 1);
    }
    for (uint32_t j = 0; j < (uint32_t)(mVec10C - mVec108); ++j) {
        node = ((MeshHandle*)FUN_01046fc0(0, mVec108[j]))->FUN_01045120();
        if (node != 0) {
            node->v16(5, rgb, 1);
        }
    }
}

// --------------------------------------------------------------------------- 0x00c47cc0
// Change the mission state: clear the two label strings, then broadcast the state message.
// @ 0x00c47cc0
void cSPMission::SetState(uint32_t state)
{
    if (mState84 == state) {
        return;
    }
    mState84 = state;
    mStr14C.clear();
    mStr15C.clear();
    if (mState84 == 3) {
        cMissionUpdateMessage msg;
        msg.mParam0 = (uint32_t)this;
        GetMessageServer()->PostMessage(msg.mMessageID, &msg, 0);
        msg.Destruct();
    }
}

// --------------------------------------------------------------------------- 0x00c47d80
// Clear the two label strings and broadcast the state message to the UI.
// @ 0x00c47d80
void cSPMission::TriggerUIUpdate()
{
    mStr14C.clear();
    mStr15C.clear();
    cMissionUpdateMessage msg;
    msg.mParam0 = (uint32_t)this;
    GetMessageServer()->PostMessage(msg.mMessageID, &msg, 0);
    msg.Destruct();
}

// --------------------------------------------------------------------------- 0x00c483d0
// Export the mission's planet and species property keys through the mission data exporter.
// @ 0x00c483d0
void cSPMission::DataExportOnInit()
{
    if (((PropertyList*)mProps180)->v7(0xf924ecff)) {
        uint32_t key = 0;
        SP::GetPropertyAsKeyInstance(mProps180, 0xf924ecff, &key);
        ExportPlanet(mField1E8, key);
    }
    if (((PropertyList*)mProps180)->v7(0xf924ed00)) {
        uint32_t key = 0;
        SP::GetPropertyAsKeyInstance(mProps180, 0xf924ed00, &key);
        ExportSpecies(mField16C, key);
    }
}

// --------------------------------------------------------------------------- 0x00c48470
// Re-arm the mission when the give-on-accept key becomes valid or the caller's key matches it.
// @ 0x00c48470
void cSPMission::FUN_00c48470(int32_t* key)
{
    if ((mKey170 != 0 && mField16C == 0)
        || (key != 0 && (void*)key[0] == mKey170 && (void*)key[1] == mKey174
            && (void*)key[2] == mKey178)) {
        if (!pv99()) {
            mField16C = 0;
            SetState(1);
        }
    }
}

// --------------------------------------------------------------------------- 0x00c484e0
// Validate the mission's planet, species and clue targets; posts a feedback event when invalid.
// @ 0x00c484e0
bool cSPMission::Validate()
{
    Empire* empire = (Empire*)GetOwnerEmpire();
    if (mField8C != -1 && empire == 0) {
        goto fail;
    }
    if (!pv88()) {
        goto fail;
    }
    if (mField94 != -1 && FUN_00c452a0() == 0) {
        goto fail;
    }
    if (((cPlanet*)mPlanet9C)->mField13C->FUN_00b8d970()) {
        goto fail;
    }
    if (mField1E8 != 0 && ((cPlanet*)mField1E8)->mField13C->FUN_00b8d970()) {
        goto fail;
    }
    empire = (Empire*)GetOwnerEmpire();
    if (!pv89()) {
        g_pTokenTranslator->mField1C = (int32_t)empire;
        SP::EventLog(0x7bac9736, 0x131a9f54, 0, 0, 1, 0)->PostFeedbackEvent();
        goto fail;
    }
    return true;
fail:
    SetState(1);
    return false;
}

// --------------------------------------------------------------------------- 0x00c48600
// Pick the planet the clue points at: a random clue kind, then either the export planet handle or
// an index into the radius-sorted planet list.
// @ 0x00c48600
bool cSPMission::PickPlanetClue()
{
    if (mField1E8 == 0) {
        return false;
    }
    PlanetNameHolder* holder = ((cPlanet*)mField1E8)->mField13C->FUN_00b8de30();
    if (holder == 0) {
        return false;
    }
    uint32_t kind = g_Random.RandomUint32Uniform(2);
    mFieldF4 = (int32_t)kind;
    switch (kind) {
    case 0: {
        cPlanetList* src = holder->FUN_00bba790();
        if (src->mBegin == src->mEnd) {
            return false;
        }
        cPlanetRange vec;
        vec.Construct(src);
        SortPlanetsByRadius(&vec);
        int32_t index = 1;
        for (void** it = vec.mBegin; it != vec.mEnd; ++it, ++index) {
            if (*it == ((cPlanet*)mField1E8)->mField13C) {
                mFieldFC = index;
                vec.Destroy();
                return true;
            }
        }
        vec.Destroy();
        return true;
    }
    case 1:
        mFieldF8 = ((cPlanet*)mField1E8)->FUN_00c70880();
        return true;
    default:
        return true;
    }
}

// --------------------------------------------------------------------------- 0x00c486f0
// Copy the species display name of the player's empire into the caller's string.
// @ 0x00c486f0
void cSPMission::FUN_00c486f0(WString* out)
{
    Empire* empire = (Empire*)FUN_00c452a0();
    if (empire == 0) {
        return;
    }
    Species* species = (Species*)empire->FUN_00c30c60();
    if (species == 0) {
        return;
    }
    WString* name = species->FUN_00bb9de0();
    const wchar_t* text = name->mBegin;
    out->assign(text, text + WcsLen(text));
}

// --------------------------------------------------------------------------- 0x00c48740
// Copy the player empire's home planet name into the caller's string.
// @ 0x00c48740
void cSPMission::FUN_00c48740(WString* out)
{
    Empire* empire = (Empire*)GetOwnerEmpire();
    if (empire == 0) {
        return;
    }
    Species* species = (Species*)empire->FUN_00c30c60();
    if (species == 0) {
        return;
    }
    WString* name = species->FUN_00bb9de0();
    const wchar_t* text = name->mBegin;
    out->assign(text, text + WcsLen(text));
}

// --------------------------------------------------------------------------- 0x00c48790
// Copy one of the two mission kind labels into the caller's string.
// @ 0x00c48790
void cSPMission::FUN_00c48790(WString* out)
{
    cString_s006b_47a0* label;
    if ((mFlags130 & 1) != 0) {
        label = &g_MissionLabel010030;
    } else {
        label = &g_MissionLabel01002F;
    }
    const wchar_t* text = label->GetText();
    out->assign(text, text + WcsLen(text));
}

// --------------------------------------------------------------------------- 0x00c487d0
// Build the mission's display text: install the mission token context, format the
// localized string, copy it into the caller's string, then restore the context.
// @ 0x00c487d0
void cSPMission::GetText(WString* out, int32_t textStyle)
{
    void* context = pv41();
    void* savedContext = g_pTokenTranslator->mField18;
    void* savedOwner = g_pTokenTranslator->mField48;
    g_pTokenTranslator->mField18 = this;
    g_pTokenTranslator->mField48 = context;

    void* activePlanet = FUN_01021260();
    void* starRecord = activePlanet != 0 ? ((cPlanet*)activePlanet)->mField13C : 0;
    FUN_00c452a0();
    void* empire = GetOwnerEmpire();

    cString_s006b_47a0 text;
    text.Construct();

    void* mission = mField17C;
    if (mission == 0) {
        mission = this;
    }
    cTextFormatter* formatterA = (cTextFormatter*)FUN_00aed4d0();
    cTextFormatter* formatterB = (cTextFormatter*)FUN_00aed4d0();
    void* game = FUN_01021300();
    void* formatted = formatterA->v9(&text, mission, starRecord, game, empire, out);
    formatterB->v3(formatted, out, (void*)(intptr_t)textStyle, game);

    const wchar_t* str = text.GetText();
    out->assign(str, str + WcsLen(str));

    g_pTokenTranslator->mField18 = savedContext;
    g_pTokenTranslator->mField48 = savedOwner;
    text.Destruct();
}

// --------------------------------------------------------------------------- 0x00c48900
// Copy the target planet's name into the caller's string.
// @ 0x00c48900
void cSPMission::FUN_00c48900(WString* out)
{
    if (mPlanet9C == 0) {
        return;
    }
    PlanetNameHolder* holder = ((cPlanet*)mPlanet9C)->mField13C->FUN_00b8de30();
    if (holder == 0) {
        return;
    }
    WString* name = holder->FUN_00bb9de0();
    out->assign(name->mBegin, name->mEnd);
}

// --------------------------------------------------------------------------- 0x00c48940
// Copy the target planet's name into the caller's string unless it is already that string.
// @ 0x00c48940
void cSPMission::FUN_00c48940(WString* out)
{
    if (mPlanet9C == 0) {
        return;
    }
    WString* name = ((cPlanet*)mPlanet9C)->GetName();
    if (name == out) {
        return;
    }
    out->assign(name->mBegin, name->mEnd);
}
