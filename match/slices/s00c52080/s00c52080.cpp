// Slice s00c52080 - SporeApp 0x00c52080..0x00c53120
// SP::cSPMissionFetch text/tag accessors and field readers.
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
//
// NOTE: the remaining slice VAs were not reconstructed in this pass and are
// recorded as unreconstructed in partial.txt.
#include "types.h"

typedef unsigned char u8;
typedef unsigned int  u32;

// ---------------------------------------------------------------------------------------------
// Support types
// ---------------------------------------------------------------------------------------------
void __cdecl operator_delete_array(void* p);      // 0x00f47380

struct cProperty {
    u8    mPad0000[0x12];
    unsigned short mType12;        // 0x12  property data type (1 = bool, 0xd = float)
    bool* GetBool();               // 0x0041e920
    float* GetFloat();             // 0x0041ea70
};

struct cPropertyList {
    // vtable slot 9 (offset 0x24), true when the key exists
    bool GetProperty(int key, cProperty** out);
};

inline bool cPropertyList::GetProperty(int key, cProperty** out)
{
    return ((bool (__thiscall*)(cPropertyList*, int, cProperty**))
            (*(void***)this)[9])(this, key, out);
}

// eastl sp-vector allocations carry their size just before the payload.
struct cAllocHeader {
    int mSize;                     // -0x04 from the payload
};

static inline int AllocSize(void* payload)
{
    return ((cAllocHeader*)payload)[-1].mSize;
}

struct cVec3 {
    float x;                       // 0x00
    float y;                       // 0x04
    float z;                       // 0x08
};

struct cVec3Vector {
    cVec3* mpBegin;                // 0x00
    cVec3* mpEnd;                  // 0x04
};

// vtable dispatch helpers
static inline int VT_60_0(void* p)
{
    return ((int (__thiscall*)(void*))(*(void***)p)[0x18])(p);
}
static inline void VT_1A4_1(void* p, int a)
{
    ((void (__thiscall*)(void*, int))(*(void***)p)[0x69])(p, a);
}
static inline void VT_6C_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0x1b])(p);
}
static inline void VT_70_0(void* p)
{
    ((void (__thiscall*)(void*))(*(void***)p)[0x1c])(p);
}

// Command dispatch singleton accessor and the space-tool object it returns.
struct cCommManager {
    void RemoveMatching();         // 0x00aea720
};

cCommManager* __stdcall GetCommManager(int a, int b, void* owner);   // 0x00b3d4a0

// Planet record the missions point at.
struct cPlanetCounts {
    u8  mPad00bc[0xbc];
    int mBc;                       // 0xbc
    int mC0;                       // 0xc0
    u8  mPad00c4[0xd0 - 0xc4];
    int mD0;                       // 0xd0
    int mD4;                       // 0xd4
};

struct cPlanet {
    u8             mPad0000[0x13c];
    cPlanetCounts* mpCounts13c;    // 0x13c
};

// Player inventory; the item list lives at 0x718.
struct cPlayerInventory {
    u8           mPad0000[0x718];
    cVec3Vector  mItems718;        // 0x718
};

struct cSPSimulatorSpaceGame {
    cPlayerInventory* GetPlayerInventory();   // 0x00a1ad60
};

cSPSimulatorSpaceGame* __cdecl GetUFOSimulator();    // 0x00ffbe50

cVec3* __cdecl FindInventoryItem(cVec3* out, cVec3Vector* list,
                                 cVec3Vector* inventory);  // 0x00c4bdc0

// ---------------------------------------------------------------------------------------------
// SP::cSPMissionFetch
// ---------------------------------------------------------------------------------------------
// Mission flag word at 0x130: bit 5 clear/hidden marker, bit 6 highlighted.

struct cSPMissionFetch {
    u8              mPad0000[0x78];
    u32             mField78;               // 0x78
    u8              mPad007c[0x80 - 0x7c];
    int             mField80;               // 0x80
    u8              mPad0084[0x130 - 0x84];
    u32             mFlags130;              // 0x130
    u8              mPad0134[0x17c - 0x134];
    void*           mpField17c;             // 0x17c
    cPropertyList*  mpPropertyList180;      // 0x180
    u8              mPad0184[0x1f0 - 0x184];
    int             mState1f0;              // 0x1f0
    u32             mTag1f4;                // 0x1f4
    u8              mPad01f8[0x234 - 0x1f8];
    void*           mpData234;              // 0x234
    u8              mPad0238[0x248 - 0x238];
    bool            mFlag248;               // 0x248
    float           mValue24c;              // 0x24c
    void*           mpData250;              // 0x250

    bool  IsActive();                       // 0x00c44c80
    void  GetText(int key, void* out);      // 0x00c487d0
    bool  GetTagString(int tag, void* out); // 0x00c491c0
    void  ProcessTagOut(int out);           // 0x00c49140
    int   GetResponseValue();               // 0x00c44cb0
    int   CalculateDuration();              // 0x00c45a10
    cPlanet* GetTargetPlanet();             // 0x00970b30
    void  ValidateProgressEvent();          // 0x00c44f20
    void  TriggerUIUpdate();                // 0x00c47d80
    void  AfterUpdate();                    // 0x00c472e0
    void  FinishUpdate();                   // 0x00c471c0
    ~cSPMissionFetch();                     // (destructor under test)

    bool  GetTagValue(int tag, void* out);          // 0x00c52080
    int   GetConversationGroupID();                 // 0x00c520d0
    int   GetProgressTextID();                      // 0x00c52130
    void  GetUIMediumDescription(void* out);        // 0x00c52160
    void  GetUILongDescription(void* out);          // 0x00c521c0
    void  ReadDropOffFields();                      // 0x00c52580
    bool  IsHighlighted();                          // 0x00c52600
    int   UpdateDuration();                         // 0x00c528a0
    void  EnterConversationState();                 // 0x00c52e30
    void  EnterStateTwo();                          // 0x00c52ea0
    cSPMissionFetch* Destroy(char flags);           // 0x00c53120
};

// @ 0x00c52080
// Tag dispatcher: two special tags are handled here, everything else goes to
// the base tag-string reader.
bool cSPMissionFetch::GetTagValue(int tag, void* out)
{
    if (tag == 0x26eaaa15) {
        VT_1A4_1(this, (int)out);
        return true;
    }
    if (tag == 0x68e2e9c6 && mTag1f4 == 0x69412983) {
        ProcessTagOut((int)out);
        return true;
    }
    return GetTagString(tag, out);
}

// @ 0x00c520d0
// Conversation group id for the current fetch state, 0 when not in a
// conversation.
int cSPMissionFetch::GetConversationGroupID()
{
    if (VT_60_0(this) == 3) {
        switch (mState1f0) {
        case 0: return (int)0x1a2b6f64;
        case 1: return (int)0x0edce0cd;
        case 2: return (int)0x11965a4d;
        case 3: return (int)0x11fd3bf3;
        }
    }
    return GetResponseValue();
}

// @ 0x00c52130
int cSPMissionFetch::GetProgressTextID()
{
    switch (mState1f0) {
    case 1: return (int)0x96254aee;
    case 2: return (int)0xa2b7bfa8;
    case 3: return (int)0xa2c33a6e;
    }
    return 0;
}

// @ 0x00c52160
void cSPMissionFetch::GetUIMediumDescription(void* out)
{
    if (IsActive()) {
        switch (mState1f0) {
        case 0: GetText(0xd79a86a8, out); break;
        case 2: GetText(0x81128ae1, out); break;
        case 3: GetText(0xa6f2b74a, out); break;
        }
    }
}

// @ 0x00c521c0
void cSPMissionFetch::GetUILongDescription(void* out)
{
    if (IsActive()) {
        switch (mState1f0) {
        case 0: GetText(0x247d8d51, out); break;
        case 2: GetText(0xba93258e, out); break;
        case 3: GetText(0x1ec90679, out); break;
        }
    }
}

// @ 0x00c52580
// Reads the drop-off flag and value properties.
void cSPMissionFetch::ReadDropOffFields()
{
    mFlag248 = false;
    if (mpPropertyList180 != 0) {
        cProperty* prop;
        if (mpPropertyList180->GetProperty(0x056242c6, &prop)) {
            if (prop->mType12 == 1)
                mFlag248 = *prop->GetBool();
        }
    }
    if (mpPropertyList180 != 0) {
        cProperty* prop;
        if (mpPropertyList180->GetProperty(0x056242c7, &prop)) {
            if (prop->mType12 == 0x0d)
                mValue24c = *prop->GetFloat();
        }
    }
}

// @ 0x00c52600
// True unless the two flag bits mark the mission as not highlighted.
bool cSPMissionFetch::IsHighlighted()
{
    u32 flags = mFlags130;
    bool b5 = ((flags >> 5) & 1) != 0;
    bool b6 = ((flags >> 6) & 1) != 0;
    if (b5 && !b6)
        return false;
    return true;
}

// @ 0x00c528a0
// Mission duration, scaled by the target planet's cell counts for one tag.
int cSPMissionFetch::UpdateDuration()
{
    int value = CalculateDuration();
    mField80 = value;
    if (mTag1f4 == 0x23da98ff) {
        cPlanet* planet = GetTargetPlanet();
        if (planet != 0) {
            planet = GetTargetPlanet();
            cPlanetCounts* counts = planet->mpCounts13c;
            int cells = (counts->mC0 - counts->mBc) / 12;
            cells += (counts->mD4 - counts->mD0) / 12;
            mField80 *= cells;
        }
        value = mField80;
    }
    return value;
}

// @ 0x00c52e30
// Leaves the running state, cancelling the pending conversation.
void cSPMissionFetch::EnterConversationState()
{
    if (mState1f0 == 2) {
        void* owner;
        if (mpField17c)
            owner = mpField17c;
        else
            owner = this;
        GetCommManager(-1, -1, owner)->RemoveMatching();
        ValidateProgressEvent();
    }
    VT_70_0(this);
    if (mState1f0 != 3) {
        mState1f0 = 3;
        TriggerUIUpdate();
    }
    AfterUpdate();
    FinishUpdate();
}

// @ 0x00c52ea0
// Enters state two when the mission is still pending, cancelling any pending
// conversation for the reward tool.
void cSPMissionFetch::EnterStateTwo()
{
    if (mState1f0 != 0 && mState1f0 != 1)
        return;
    VT_6C_0(this);
    if (mState1f0 != 2) {
        mState1f0 = 2;
        TriggerUIUpdate();
    }
    if (mFlag248 && mField78 == 0xbb448992) {
        void* owner;
        if (mpField17c)
            owner = mpField17c;
        else
            owner = this;
        GetCommManager(-1, -1, owner)->RemoveMatching();
    }
    AfterUpdate();
    FinishUpdate();
}

// @ 0x00c52d30
// Finds the three-float record equal to `value` in [first, last).
float* FindVec3(float* first, float* last, const float* value)
{
    if (first != last) {
        do {
            if (*first == *value && first[1] == value[1] && first[2] == value[2])
                break;
            first += 3;
        } while (first != last);
    }
    return first;
}

// @ 0x00c52f20
// Looks the first party item up in the player inventory and copies it out.
bool FindPlayerItem(cVec3Vector* list, cVec3* out)
{
    if (list->mpBegin != list->mpEnd) {
        cSPSimulatorSpaceGame* sim = GetUFOSimulator();
        cPlayerInventory* inventory = sim->GetPlayerInventory();
        cVec3 local;
        cVec3* item = FindInventoryItem(&local, list, &inventory->mItems718);
        *out = *item;
        return true;
    }
    return false;
}


// @ 0x00c53120
// Releases the two owned arrays, runs the base destructor and optionally
// frees the object itself.
cSPMissionFetch* cSPMissionFetch::Destroy(char flags)
{
    if (mpData250 != 0 && AllocSize(mpData250) != 0)
        operator_delete_array(mpData250);
    if (mpData234 != 0 && AllocSize(mpData234) != 0)
        operator_delete_array(mpData234);
    this->~cSPMissionFetch();
    if ((flags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// Free helper
// ---------------------------------------------------------------------------------------------
struct cFlagState {
    bool mEnabled;                 // 0x00
    u8   mPad0001[3];
};

void __cdecl SP_SetMissionFlag(void* a, void* b, cFlagState state);   // 0x00c52d80

// @ 0x00c52f80
void SP_SetMissionFlagDefault(void* a, void* b)
{
    cFlagState state;
    state.mEnabled = false;
    SP_SetMissionFlag(a, b, state);
}
