// Slice s00c453b0 - SP::cSPMission::GetRewardProfit.
// __thiscall, `this` in ecx.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- /fp:fast
//
// Reconstruction notes (from retail 0x00c453b0, 345 bytes):
//   * the owner empire's relation (+0x54) selects one of three relation
//     specific property keys, else the generic reward-profit key;
//   * the mission property list (this+0x180, an AutoRefCount-style handle: every
//     test/use goes through an inlined raw-pointer getter, which is why retail
//     emits `mov ecx,[this+0x180]; test ecx,ecx` and then reuses ecx for the
//     virtual call) is asked with HasProperty (vtbl+0x1c) and GetProperty
//     (vtbl+0x24); the value counts only when the property's type word (+0x12)
//     is 0xd (float);
//   * the profit itself is the terrain-sphere value keyed 0x95250982, replaced
//     by an entry of the 0x5efb832 float array indexed by the owner empire's
//     weaponry level (Min with count-1) when the mission's owner is not the
//     player empire;
//   * the result is that profit times the property multiplier (the retail
//     epilogue loads the profit, pops edi - which shifts esp by 4 - and only
//     then multiplies by the stack slot holding the property value).

#include "game/types.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int i32;
typedef float f32;

// ---------------------------------------------------------------------------
// External callees (addresses in comments).
// ---------------------------------------------------------------------------
u32  __cdecl GetPlayerEmpireID();                                        // 0x01021090
void* __cdecl NounManager();                                             // 0x00b3d300
void __cdecl GetPropertyAsFloatArray(void* list, u32 key, i32* count, void** out); // 0x006a08b0

struct cProperty {
    void* mpValue;      // 0x00
    u32   pad04;        // 0x04
    i32   mCount;       // 0x08
    u32   pad0c;        // 0x0c
    u16   mFlags;       // 0x10
    u16   mType;        // 0x12
    f32*  GetFloat();   // 0x0041ea70
};

// The mission property bag: HasProperty / GetProperty are vtable slots.
struct cMissionPropList {
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void vf0c(); virtual void vf10(); virtual void vf14();
    virtual void vf18();
    virtual bool HasProperty(u32 key);                  // slot +0x1c
    virtual void vf20();
    virtual bool GetProperty(u32 key, cProperty** out);  // slot +0x24
};

// EA::AutoRefCount<SP::cPropertyList>-shaped handle (one raw pointer).
struct PropListRef {
    cMissionPropList* mpObject;
    cMissionPropList* Get() const { return mpObject; }
    cMissionPropList* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};

struct cTerrainSphere {
    f32 GetValue(u32 key);                              // 0x00c75c30
};

struct cNounManager {
    cTerrainSphere* GetCurrentTerrainSphere();          // 0x00f67d90
};

struct cEmpire {
    u32 pad000[0x15];   // 0x00
    u32 mRelation;      // 0x54
    u32 GetWeaponryLevel();                             // 0x00c317a0
};

// Retail's clamp helper compares a < b and returns a reference to the smaller
// operand (hence the two stack temporaries and the lea pair at 0x00c454e0).
template <class T>
inline const T& Min(const T& a, const T& b)
{
    return a < b ? a : b;
}

// ---------------------------------------------------------------------------
// SP::cSPMission, fields touched here (retail offsets).
// ---------------------------------------------------------------------------
class cSPMission {
 public:
    u32   pad000[0x23];        // 0x000
    u32   mOwnerEmpireID;      // 0x08c
    u32   pad090[0x3c];        // 0x090
    PropListRef mMissionPropList;  // 0x180

    cEmpire* GetOwnerEmpire() const;                    // 0x00c451e0
    f32 GetRewardProfit() const;                        // 0x00c453b0
};

// ---------------------------------------------------------------------------
// 0x00c453b0 - SP::cSPMission::GetRewardProfit
// ---------------------------------------------------------------------------
// @ 0x00c453b0
f32 cSPMission::GetRewardProfit() const
{
    u32 relation = 0;
    cEmpire* owner = GetOwnerEmpire();
    if (owner != 0)
        relation = owner->mRelation;

    f32 multiplier = 0.0f;
    if (mMissionPropList) {
        u32 key = 0x24b0e0e4;
        u32 relationKey = 0;
        switch (relation) {
        case 1: relationKey = 0xc7a32320; break;
        case 2: relationKey = 0x665f8a72; break;
        case 3: relationKey = 0xf7b6a107; break;
        default: break;
        }
        if (relationKey != 0 && mMissionPropList->HasProperty(relationKey))
            key = relationKey;
        if (mMissionPropList->HasProperty(key) && mMissionPropList.Get() != 0) {
            cProperty* prop;
            if (mMissionPropList->GetProperty(key, &prop) && prop->mType == 0xd)
                multiplier = *prop->GetFloat();
        }
    }

    f32 profit = ((cNounManager*)NounManager())->GetCurrentTerrainSphere()->GetValue(0x95250982);

    if (mOwnerEmpireID != 0xffffffff && mOwnerEmpireID != GetPlayerEmpireID()) {
        void* array = 0;
        i32 count = 0;
        GetPropertyAsFloatArray(mMissionPropList.Get(), 0x5efb832, &count, &array);
        if (count > 0) {
            cEmpire* empire = GetOwnerEmpire();
            i32 level = (i32)empire->GetWeaponryLevel();
            profit = ((f32*)array)[Min(level, count - 1)];
        }
    }

    return profit * multiplier;
}
