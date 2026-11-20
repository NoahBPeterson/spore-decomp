// Slice s00d39670
// match/slices/s00d39670/s00d39670.cpp
// SP::cCreatureModeStrategy::AddStat (PDB name for 0x00d39670, callee-scored).
// Object file: SPGonzago/SPCreatureModeStrategy.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
//
// Builds a telemetry stat item for the avatar: it takes the first noun manager,
// the avatar, reads the avatar's world position (sub-object at +0xc0, vtable
// slot 0x2c), collects the current "property key" from the property object at
// (0x00b3d350 -> +0x24), asks the telemetry system (0x0067de90) for an item,
// gives it the metric id (sub + 0x0b, 0x007eb820) and fills the 0x2c-byte
// payload with the 64-bit game time scaled by 0x00b316c0/0x011e0970, the
// avatar noun id (avatar vtable +0xd8), the two float timestamps
// (0x00d2e360 / 0x00d2e350), the noun count (0x00b1f9c0) and the avatar
// identity colour (profile +0xb20 -> +0x4ec through 0x00458a40).
//
// TODO(unknowns): the virtual slot used for the guard call (vtable +0x08, no
// arguments, returns a value tested for zero) and the call that fills `msg`
// (also +0x08, two arguments) cannot both be slot 2 of one class; the guard is
// spelled here as +0x08 and the query as the next slot.  The string literal at
// 0x03d03f84 (pushed to that call) is not in the image dump.

#include "game/types.h"

namespace SP {

struct Vector3 {
    float x, y, z;
};

// The three zeroed words at [esp+0x10..0x18].
struct cStatMessage {
    uint32_t m00;      // +0x00  stored into the payload at +0x24
    uint32_t m04;
    uint32_t m08;      // +0x08  stored into the payload at +0x20
};

// First 0x2c bytes of the record hanging off the telemetry item at +0x0c.
struct cStatData {
    int32_t  mTicks;       // +0x00  0x011e0970(now, 1000, 0)
    int32_t  mNounId;      // +0x04  avatar vtable slot 0xd8
    float    mTimeA;       // +0x08  0x00d2e360
    float    mTimeB;       // +0x0c  0x00d2e350
    int32_t  mNounCount;   // +0x10  noun list end - begin, in dwords
    Vector3  mPosition;    // +0x14
    uint32_t mMsg08;       // +0x20
    uint32_t mMsg00;       // +0x24
    uint32_t mColor;       // +0x28
};

struct cTelemetryItem {
    char mPad00[0x0c];
    cStatData* mpData;                     // +0x0c
    void SetMetric(int metricId);          // 0x007eb820
};

// Sub-object of the avatar at +0xc0; the position getter is vtable slot 0x2c.
struct cSpatialObject {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual const Vector3& GetPosition();                 // slot 0x2c
};

struct cSpeciesProfile {
    char  mPad0000[0x4ec];
    float mColor[3];                                      // +0x4ec
};

struct cCreatureBase {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
    virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
    virtual void v52(); virtual void v53();
    virtual int GetNounID();                              // slot 0xd8

    char mPad0004[0xc0 - 4];
    cSpatialObject mSpatial;                               // +0xc0
    char mPad00c4[0xb20 - 0xc4];
    cSpeciesProfile* mpProfile;                            // +0xb20
};

// Noun list reachable through 0x00b1f9c0 (begin/end pointers, counted in ints).
struct cNounList {
    int* mpBegin;                                          // +0x00
    int* mpEnd;                                            // +0x04
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cGameNounManager {
    cCreatureBase* GetAvatar();                            // 0x00b1fdb0
    cNounList* GetNounList();                              // 0x00b1f9c0
};

cGameNounManager* NounManager();                          // 0x00b3d300

// 0x00b3d350 -> +0x24 : the object whose property string is turned into a key.
struct cPropertyQuery {
    virtual void v00();
    virtual void v01();
    // Retail calls this zero-argument slot twice: once as the guard and once
    // for the value handed to GetPropertyAsKey (whose other two arguments are
    // pushed first, right-to-left, hence `add esp,0xc` after that call).
    virtual int GetKey();                                  // vtable +0x08
};

struct cPropertyHolder {
    char mPad00[0x24];
    cPropertyQuery* mpQuery;                               // +0x24
};

cPropertyHolder* PropertyManager();                        // 0x00b3d350

// (value, key, out): the key and out arguments are pushed first, before the
// value expression (the virtual call) is evaluated.  The key is the literal
// 0x03d03f84 the retail code pushes as an immediate (no relocation there).
void __cdecl GetPropertyAsKey(int32_t value, uint32_t key, cStatMessage* out); // 0x006a1250

// Telemetry front end: 0x0067de90(flag, kind) returns the collector, whose
// 0x007ec160 returns the freshly created item.
struct cTelemetry {
    cTelemetryItem* BeginItem();                           // 0x007ec160
};

// Caller does not clean the two arguments (no `add esp` follows the call).
cTelemetry* __stdcall GetTelemetry(int flag, unsigned int kind);   // 0x0067de90

// Game clock: 0x00b3d380() returns the manager, 0x00b316c0 its 64-bit tick count.
struct cGameTimeManager {
    int64_t GetTicks();                                    // 0x00b316c0
};

cGameTimeManager* GameTimeManager();                       // 0x00b3d380

// 0x011e0970(int64 ticks, scale, flags) -> scaled 32-bit value; callee-cleaned
// (no `add esp` follows the call).
int32_t __stdcall ScaleTicks(int64_t ticks, int32_t scale, int32_t flags); // 0x011e0970

float FUN_d2e360();                                        // 0x00d2e360
float FUN_d2e350();                                        // 0x00d2e350
uint32_t __cdecl ColorRGBToU32(const float* rgb);          // 0x00458a40

class cCreatureModeStrategy {
public:
    cTelemetryItem* AddStat(unsigned int kind, unsigned int sub);   // 0x00d39670
};

// @ 0x00d39670 SP::cCreatureModeStrategy::AddStat
cTelemetryItem* cCreatureModeStrategy::AddStat(unsigned int kind, unsigned int sub)
{
    cGameNounManager* pNouns = NounManager();
    cCreatureBase* pAvatar = pNouns->GetAvatar();
    const Vector3& position = pAvatar->mSpatial.GetPosition();

    cStatMessage msg;
    msg.m00 = 0;
    msg.m04 = 0;
    msg.m08 = 0;

    cPropertyQuery* pQuery = PropertyManager()->mpQuery;
    if (pQuery != 0 && pQuery->GetKey() != 0)
        GetPropertyAsKey(pQuery->GetKey(), 0x3D03F84, &msg);

    cTelemetryItem* pItem = GetTelemetry(1, kind)->BeginItem();
    pItem->SetMetric((int)sub + 0x0b);

    int64_t ticks = GameTimeManager()->GetTicks();
    pItem->mpData->mTicks = ScaleTicks(ticks, 1000, 0);
    pItem->mpData->mNounId = pAvatar->GetNounID();
    pItem->mpData->mTimeA = FUN_d2e360();
    pItem->mpData->mTimeB = FUN_d2e350();
    pItem->mpData->mNounCount = pNouns->GetNounList()->size();
    // Retail copies the three floats separately, reloading the payload pointer
    // after each store.
    pItem->mpData->mPosition.x = position.x;
    pItem->mpData->mPosition.y = position.y;
    pItem->mpData->mPosition.z = position.z;
    pItem->mpData->mMsg08 = msg.m08;
    pItem->mpData->mMsg00 = msg.m00;
    pItem->mpData->mColor = ColorRGBToU32(pAvatar->mpProfile->mColor);
    return pItem;
}

}  // namespace SP
