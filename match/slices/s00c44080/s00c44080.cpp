// Slice s00c44080 - SporeApp 0x00c44080..0x00c45760
// SP::cSPMission empire/planet accessors and small mission helpers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
struct cStarRecord {
    u32 GetStarID();        // 0x00b8de30
    int GetCommContext();   // 0x00ce6950
};

struct cPlanet {
    u8            mPad0000[0x13c];
    cStarRecord*  mpStarRecord13c;   // 0x13c
};

struct cEmpire {
    u8   mPad0000[0x84];
    u32  mEmpireID84;                // 0x84
};

struct cStarManager {
    cEmpire* GetEmpireByID();        // 0x00ba9370
};

struct cUFO {
    int   ComputeCost(u32 starID);   // 0x00ffc4e0
    float ComputeCostFloat(u32 starID);  // 0x00ffc490
};

cStarManager* __stdcall GetStarManager(u32 empireID);  // 0x00b3d2a0
cUFO*         __stdcall GetUFOSimulator(u32 starID);   // 0x00ffbe50

void __cdecl SP_GetPropertyAsString16(void* prop, int key, int value);  // 0x006a1400

struct cProperty {
    u8    mPad0000[0x12];
    u16   mType12;                   // 0x12  property data type (1 = bool)
    bool* GetBool();                 // 0x0041e920
};

struct cPropertyList {
    // vtable slot 9 (offset 0x24), returns whether the key was found
    bool GetProperty(int key, cProperty** out);
};

inline bool cPropertyList::GetProperty(int key, cProperty** out)
{
    return ((bool (__thiscall*)(cPropertyList*, int, cProperty**))
            (*(void***)this)[9])(this, key, out);
}

// vtable slot dispatch helpers (slots 0/1 are AddRef/Release)
static inline void VT_00_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[0])(p); }
static inline void VT_04_0(void* p) { ((void (__thiscall*)(void*))(*(void***)p)[1])(p); }
static inline int  VT_60_0(void* p) { return ((int (__thiscall*)(void*))(*(void***)p)[0x18])(p); }

// ---------------------------------------------------------------------------------------------
// SP::cSPMission
// ---------------------------------------------------------------------------------------------
struct cSPMission {
    u8            mPad0000[0x7c];
    int           mUsed7c;                 // 0x7c
    int           mTotal80;                // 0x80
    u8            mPad0084[0x8c - 0x84];
    int           mEmpireID8c;             // 0x8c
    u8            mPad0090[0x94 - 0x90];
    int           mCachedEmpireID94;       // 0x94  (-1 when unset)
    cEmpire*      mpEmpire98;              // 0x98  ref-counted, cached
    cPlanet*      mpOriginPlanet9c;        // 0x9c
    u8            mPad00a0[0x130 - 0xa0];
    u8            mFlags130;               // 0x130
    u8            mPad0131[0x180 - 0x131];
    cPropertyList* mpPropertyList180;      // 0x180
    u8            mPad0184[0x1e8 - 0x184];
    cPlanet*      mpTargetPlanet1e8;       // 0x1e8

    void        SetEmpire(cEmpire* p);                    // 0x00c45250
    cEmpire*    GetEmpire();                              // 0x00c452a0
    int         SetUITextValue(int value);                // 0x00c45310
    bool        IsVisibleInUI();                          // 0x00c45340
    int         GetNumAvailable();                        // 0x00c45380
    int         GetTotalTravelCost();                     // 0x00c45510
    float       GetTotalTravelCostFloat();                // 0x00c45560
    bool        IsAtStar(int empireID, int commContext);  // 0x00c455b0
    int         GetDynamicResponseID(int a, int b);       // 0x00c45740
};

// @ 0x00c45250
// Sets the cached empire: the id is remembered separately so that the empire
// pointer can be re-fetched lazily; the previous empire is released.
void cSPMission::SetEmpire(cEmpire* p)
{
    mCachedEmpireID94 = (p != 0) ? (int)p->mEmpireID84 : -1;
    cEmpire* old = mpEmpire98;
    if (p != old) {
        if (p != 0)
            VT_00_0(p);
        mpEmpire98 = p;
        if (old != 0)
            VT_04_0(old);
    }
}

// @ 0x00c452a0
// Lazily resolves mpEmpire98 from the cached empire id.
cEmpire* cSPMission::GetEmpire()
{
    if (mpEmpire98 != 0)
        return mpEmpire98;
    int id = mCachedEmpireID94;
    if (id == -1)
        return mpEmpire98;
    cStarManager* mgr = GetStarManager((u32)id);
    cEmpire* e = mgr->GetEmpireByID();
    cEmpire* old = mpEmpire98;
    if (e == old)
        return old;
    if (e != 0)
        VT_00_0(e);
    mpEmpire98 = e;
    if (old != 0) {
        VT_04_0(old);
        return mpEmpire98;
    }
    return e;
}

// @ 0x00c45310
// Writes `value` into the mission's UI text property, returning it.
int cSPMission::SetUITextValue(int value)
{
    if (value != 0 && mpPropertyList180 != 0)
        SP_GetPropertyAsString16(mpPropertyList180, 0x00b2ccca, value);
    return value;
}

// @ 0x00c45340
// Whether the mission shows up in the UI: true unless its UI title property
// says otherwise.
bool cSPMission::IsVisibleInUI()
{
    bool visible = true;
    if (mpPropertyList180 != 0) {
        cProperty* prop = 0;
        if (mpPropertyList180->GetProperty(0x05590946, &prop)) {
            if (prop->mType12 == 1)
                visible = *prop->GetBool();
        }
    }
    return visible;
}

static inline const int& max_ref(const int& a, const int& b) { return (a < b) ? b : a; }

// @ 0x00c45380
// Number of unused entries in the 0x7c/0x80 counter pair.
int cSPMission::GetNumAvailable()
{
    u32 total = mTotal80;
    if (total > 0) {
        int zero = 0;
        int d = (int)(total - (u32)mUsed7c);
        return max_ref(d, zero);
    }
    return 0;
}

// @ 0x00c45510
// Round-trip travel cost between the origin and the target planet.
int cSPMission::GetTotalTravelCost()
{
    cPlanet* origin = mpOriginPlanet9c;
    if (origin == 0)
        return 0;
    cPlanet* target = mpTargetPlanet1e8;
    if (target == 0)
        return 0;
    cStarRecord* targetRec = target->mpStarRecord13c;
    cStarRecord* originRec = origin->mpStarRecord13c;
    u32 targetID = targetRec->GetStarID();
    u32 originID = originRec->GetStarID();
    return 2 * GetUFOSimulator(originID)->ComputeCost(targetID);
}

// @ 0x00c45560
float cSPMission::GetTotalTravelCostFloat()
{
    cPlanet* origin = mpOriginPlanet9c;
    if (origin == 0)
        return 0.0f;
    cPlanet* target = mpTargetPlanet1e8;
    if (target == 0)
        return 0.0f;
    cStarRecord* targetRec = target->mpStarRecord13c;
    cStarRecord* originRec = origin->mpStarRecord13c;
    u32 targetID = targetRec->GetStarID();
    u32 originID = originRec->GetStarID();
    return GetUFOSimulator(originID)->ComputeCostFloat(targetID) * 2.0f;
}

// @ 0x00c455b0
// True when the mission's empire is the given one and the mission sits in the
// given comm context, and the mission is in a state that allows a comm call.
bool cSPMission::IsAtStar(int empireID, int commContext)
{
    int state = VT_60_0(this);
    if (state != 3) {
        if (VT_60_0(this) != 5)
            return false;
    }
    if (mpOriginPlanet9c->mpStarRecord13c->GetCommContext() != commContext)
        return 0;
    if (empireID != mEmpireID8c)
        return 0;
    return 1;
}

// @ 0x00c45740
// Reaction id selected by the low flag bit of the mission: -1 when the flag is
// set, otherwise the mission's default reaction.
int cSPMission::GetDynamicResponseID(int a, int b)
{
    (void)a;
    (void)b;
    return (mFlags130 & 1) ? -1 : 0xb6a7851e;
}
