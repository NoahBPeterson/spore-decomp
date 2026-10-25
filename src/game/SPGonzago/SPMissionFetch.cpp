// src/game/SPGonzago/SPMissionFetch.cpp -- migrated from slice(s) s0133ed00, s00c53180, s00c52080 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionFetch.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanet.h"
#include "SP/cPropertyList.h"
#include "SP/cDataSerializationInfo.h"
#include "EA/Variant.h"
#include "SP/cPropertyManager.h"
#include "SP/cSPMission.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00c52080 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef unsigned int  u32;
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
struct cCommManager {
    void RemoveMatching();         // 0x00aea720
};
cCommManager* __stdcall GetCommManager(int a, int b, void* owner);   // 0x00b3d4a0
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
struct cFlagState {
    bool mEnabled;                 // 0x00
    u8   mPad0001[3];
};
void __cdecl SP_SetMissionFlag(void* a, void* b, cFlagState state);   // 0x00c52d80
// ---- items of slice s00c52080 end

// ---- items of slice s00c53180 begin (TODO(rewrite): local stubs, replace by canonical classes)
class Key {
public:
    uint32_t mInstance;   // +0x00
    uint32_t mType;       // +0x04
    uint32_t mGroup;      // +0x08
};
struct cFetchSample {
    bool mIsAnimal;       // +0x00
    Key mSpeciesKey;      // +0x04
};
struct Quad16;
Quad16* copy(const Quad16* first, const Quad16* last, Quad16* dest);
class cFetchSampleVector {
public:
    cFetchSample* mpBegin;     // +0x00
    cFetchSample* mpEnd;       // +0x04
    cFetchSample* mpCapacity;  // +0x08
    cFetchSample* DoInsertValue(cFetchSample* pos, const cFetchSample& value); // 0x00c19d10
    void Reserve(uint32_t nCount);                                             // 0x00c53690
    void push_back(const cFetchSample& value);                                 // 0x00c53a50
    void clear();                                                              // 0x00c53a90
};
// ---- items of slice s00c53180 end

// ---- items of slice s0133ed00 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (*AttrFn)();
struct Attribute {
    const char* mpName;    // +0x00  attribute name ("mHealth", ...)
    u32         mKey;      // +0x04  hashed property key
    u32         mOffset;   // +0x08  byte offset of the member in the owner
    u32         mUnk0c;    // +0x0c  uninitialised in the original
    u32         mUnk10;    // +0x10  uninitialised in the original
    u32         mUnk14;    // +0x14  uninitialised in the original
    u32         mFlags18;  // +0x18  always 0
    u32         mFlags1c;  // +0x1c  always 0
    AttrFn      mpfn20;    // +0x20  default/offset accessor (0x692ca0)
    AttrFn      mpfn24;    // +0x24  writer/reader A
    AttrFn      mpfn28;    // +0x28  writer A
    AttrFn      mpfn2c;    // +0x2c  parser/reader A
    AttrFn      mpfn30;    // +0x30  parser A
    AttrFn      mpfn34;    // +0x34  init hook (0xb1fbf0)
    AttrFn      mpfn38;    // +0x38  serialiser
};
Attribute s_fetchAttrs[9];            // 0x01575bd8
#define ATTR(dst, nm, k, off, f0, f1, f2, f3, f4, f5, f6)          \
    do {                                                           \
        Attribute t;                                               \
        t.mpName = (nm);                                           \
        t.mKey = (k);                                              \
        t.mFlags18 = 0;                                            \
        t.mFlags1c = 0;                                            \
        t.mpfn20 = (AttrFn)(f0);                                   \
        t.mpfn24 = (AttrFn)(f1);                                   \
        t.mpfn28 = (AttrFn)(f2);                                   \
        t.mpfn2c = (AttrFn)(f3);                                   \
        t.mpfn30 = (AttrFn)(f4);                                   \
        t.mpfn34 = (AttrFn)(f5);                                   \
        t.mpfn38 = (AttrFn)(f6);                                   \
        t.mOffset = (off);                                         \
        (dst) = t;                                                 \
    } while (0)
// ---- items of slice s0133ed00 end

// @ 0x00c52080
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

// @ 0x00c52d30
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

// @ 0x00c52e30
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

// @ 0x00c52f20
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

// @ 0x00c52f80
void SP_SetMissionFlagDefault(void* a, void* b)
{
    cFlagState state;
    state.mEnabled = false;
    SP_SetMissionFlag(a, b, state);
}

// @ 0x00c53120
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

// @ 0x00c53a90
void cFetchSampleVector::clear()
{
    cFetchSample* pEnd = mpEnd;
    cFetchSample* pBegin = mpBegin;
    copy((const Quad16*)pEnd, (const Quad16*)pEnd, (Quad16*)pBegin);
    mpEnd -= pEnd - pBegin;
}

// @ 0x01342770
void FUN_01342770()
{
    ATTR(s_fetchAttrs[0], "mFetchMissionState", 0x385389d, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_fetchAttrs[1], "mTypeOfFetch", 0x385389e, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_fetchAttrs[2], "mFetchArtifactCargoItemID", 0x385389f, 0x1f8,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[3], "mFetchPlantSpeciesKey", 0x3f69492, 0x210,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[4], "mFetchAnimalSpeciesKey", 0x3f69497, 0x21c,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[5], "mFetchCommodityKey", 0x3f69498, 0x228,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[6], "mSamplerPlate", 0x38538a3, 0x234,
         0x692ca0, 0xc53ac0, 0xc52c60, 0xc2e4e0, 0x692fb0, 0xc52cf0, 0xca8710);
    ATTR(s_fetchAttrs[7], "mDropOffRequired", 0x3f69499, 0x248,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_fetchAttrs[8], "mDropOffDistance", 0x3f69500, 0x24c,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
}
