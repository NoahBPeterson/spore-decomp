// s00c58920.cpp - reconstructed slice
// Compiler: MSVC 2008 SP1 (x86)
// Flags: /O2 /Ob1 /MD /Gy /EHsc /TP /arch:SSE /GS-
// ---------------------------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------------------------
#include <math.h>
#pragma intrinsic(sqrt)

typedef unsigned char      u8;
typedef unsigned int       u32;
typedef int                i32;
typedef float              f32;
typedef unsigned short     wchar_t_;

static inline float InlineSqrt(float x) { return (float)sqrt((double)x); }

// One dummy virtual per level, used to lay out the slots of the retail vtables.
template <int N, class B> struct VPad : VPad<N - 1, B> { virtual void vpad(VPad<N, B>*) {} };
template <class B> struct VPad<0, B> : B {};
struct IEmpty {};

// EASTL 16-bit string: {begin, end, cap}.  The static empty string has
// begin == end == gEmptyString16 and cap == gEmptyString16 + 2 bytes.
extern u8 gEmptyString16[];                     // 0x01667bac

void __cdecl WFree(void* block);                // 0x00f47380  operator delete
extern "C" float __cdecl sqrtf(float);

struct Vec3 {
    f32 x;
    f32 y;
    f32 z;
};

struct cWString {
    void* mpBegin;                      // 0x00
    void* mpEnd;                        // 0x04
    void* mpCap;                        // 0x08
    u32   mPad0c;                       // 0x0c (sizeof == 0x10 in retail)

    cWString()
        : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCap(gEmptyString16 + 2) {}

    // Release the heap buffer unless this is the shared static empty string.
    void Release()
    {
        u32 bytes = (u32)((char*)mpCap - (char*)mpBegin) & 0xfffffffeu;
        if (bytes > 2 && mpBegin != 0)
            WFree(mpBegin);
    }

    void assign(const void* first, const void* last);  // 0x00423650
};

// Ref-counted mission object: AddRef in slot 47 (+0xbc), Release in slot 48 (+0xc0).
struct IRefCounted : VPad<47, IEmpty> {
    virtual int AddRef();               // +0xbc
    virtual int Release();              // +0xc0
};

// hdr->mCount is the number of live bytes kept in front of an sp_vector_allocator block.
struct SpAllocHeader {
    u32 mCount;
};

inline bool SpIsOwned(const void* p)
{
    if (p == 0)
        return false;
    return ((const SpAllocHeader*)p)[-1].mCount != 0;
}

struct cPlanetVector {
    struct cPlanet** mpBegin;           // 0x00
    struct cPlanet** mpEnd;             // 0x04
    struct cPlanet** mpCap;             // 0x08
};

// ---------------------------------------------------------------------------------------------
// Star records / planets
// ---------------------------------------------------------------------------------------------
struct cStarRecord {
    virtual int AddRef();               // +0x00
    virtual int Release();              // +0x04
    u8          mPad004[0x38];
    Vec3        mPosition;              // +0x3c
    u8          mPad048[0x14];
    u32         mFlags;                 // +0x5c
    cWString    mName;                  // +0x60
    u32         mField70;               // +0x70

    const Vec3& GetPosition();           // 0x005c65e0
    cWString*   GetName();               // 0x00bb9de0
    bool        TestFlag(u32 mask);      // 0x00bb9af0
    cPlanetVector* GetPlanets();         // 0x00bba790
};

struct cPlanetModel {
    u8          mPad000[0x18];
    u8          mPad018[0x16c];
    u32         mStarRecordID;           // +0x184
    cStarRecord* SortBanners();          // 0x00b8de30
};

struct cPlanet {
    u8           mPad000[0x28];
    u32          mField28;               // +0x28
    u8           mPad02c[0x110];
    cPlanetModel* mpModel;               // +0x13c

    cWString* GetName();                 // 0x00c707e0
    i32       FUN_00b8d9b0();            // 0x00b8d9b0
};

// ---------------------------------------------------------------------------------------------
// Serialized delivery records and their EASTL vectors
// ---------------------------------------------------------------------------------------------
struct tBuyerInfo {
    IRefCounted* mpObject;              // +0x00
    u32          mField4;               // +0x04
    u32          mField8;               // +0x08
};

struct tItemInfo {
    IRefCounted* mpObject;              // +0x00
    Vec3         mPosition;             // +0x04
    bool         mFlag;                 // +0x10
    u8           mPad011[3];

    tItemInfo* FUN_00c57a80(void* target, i32 flag, Vec3 position);  // 0x00c57a80
};

struct cBuyerVector {
    tBuyerInfo* mpBegin;                // 0x00
    tBuyerInfo* mpEnd;                  // 0x04
    tBuyerInfo* mpCap;                  // 0x08

    void erase(tBuyerInfo* first, tBuyerInfo* last);            // 0x00c58590
    void reserve(u32 count);                                    // 0x00c583b0
    void DoInsertValue(tBuyerInfo* end, const tBuyerInfo* value); // 0x00c58600

    void push_back(const tBuyerInfo& value)
    {
        if (mpEnd < mpCap) {
            tBuyerInfo* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot) {
                slot->mpObject = value.mpObject;
                if (slot->mpObject)
                    slot->mpObject->AddRef();
                slot->mField4 = value.mField4;
                slot->mField8 = value.mField8;
            }
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};

struct cItemVector {
    tItemInfo* mpBegin;                 // 0x00
    tItemInfo* mpEnd;                   // 0x04
    tItemInfo* mpCap;                   // 0x08

    void erase(tItemInfo* first, tItemInfo* last);              // 0x00c58770
    void reserve(u32 count);                                    // 0x00c58470
    void DoInsertValue(tItemInfo* end, const tItemInfo* value);  // 0x00c587e0
    void Add(tItemInfo* value);                                 // 0x00c58ee0

    i32 size() const { return (i32)((u8*)mpEnd - (u8*)mpBegin) / 0x14; }

    void push_back(const tItemInfo& value)
    {
        if (mpEnd < mpCap) {
            tItemInfo* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot) {
                slot->mpObject = value.mpObject;
                if (slot->mpObject)
                    slot->mpObject->AddRef();
                slot->mPosition.x = value.mPosition.x;
                slot->mPosition.y = value.mPosition.y;
                slot->mPosition.z = value.mPosition.z;
                slot->mFlag = value.mFlag;
            }
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};

// eastl::vector<void*> (star-map visual handles)
struct cPointerVector {
    void** mpBegin;                     // 0x00
    void** mpEnd;                       // 0x04
    void** mpCap;                       // 0x08

    void DoInsertValue(void** end, void* const* value);          // 0x004558a0

    void push_back(void* const& value)
    {
        if (mpEnd < mpCap) {
            void** slot = mpEnd;
            mpEnd = slot + 1;
            if (slot)
                *slot = value;
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};

// eastl::vector<float> (the destination-indicator point stream)
struct cFloatVector {
    f32* mpBegin;                       // 0x00
    f32* mpEnd;                         // 0x04
    f32* mpCap;                         // 0x08

    void reserve(u32 count);                                    // 0x004e0880
    void DoInsertValue(f32* end, const f32* value);              // 0x00455660

    void push_back(const f32& value)
    {
        if (mpEnd < mpCap) {
            f32* slot = mpEnd;
            mpEnd = slot + 1;
            if (slot)
                *slot = value;
        } else {
            DoInsertValue(mpEnd, &value);
        }
    }
};

// ---------------------------------------------------------------------------------------------
// Archiver interface (save-game reader)
// ---------------------------------------------------------------------------------------------
struct IArchiveWriter : VPad<6, IEmpty> {
    virtual void* GetStream();                                   // +0x18
};

struct IArchiver : VPad<7, IEmpty> {
    virtual IArchiver& EndRead();                                // +0x1c
    virtual IArchiveWriter* GetWriter();                         // +0x20
    virtual void* FUN_0024();                                    // +0x24
    virtual void* SerializeItem(u32 typeID, void* item, i32 flag); // +0x28
};

bool __cdecl ReadInt32(void* pStream, void* pOut, i32 count, i32 flag);  // 0x0093a780
bool __cdecl ReadBool(void* pStream, bool* pOut);                        // 0x0093ac80

// Shared sequence element deserializer.
IArchiver& __cdecl operator>>(IArchiver& ar, tBuyerInfo& info);          // 0x00c56de0

// ---------------------------------------------------------------------------------------------
// Star map, effect, game systems
// ---------------------------------------------------------------------------------------------
struct VEffect : VPad<16, IEmpty> {
    virtual void FUN_0040(i32 id, const Vec3* values, i32 count);    // +0x40
    virtual void FUN_0044(i32 id, const f32* values, i32 count);     // +0x44
};

struct cStarMap {
    VEffect* CreateStarRecordVisual(cStarRecord* record, u32 type, u32 param); // 0x010458f0
    void     AddVisual(VEffect* visual, i32 flag);                            // 0x01044d70
    VEffect* FUN_01045120(u32 starID, VEffect* visual);                      // 0x01045120
    void     RemoveVisual(i32 handle, i32 flag);                             // 0x01045a60
};

cStarMap* __cdecl GetStarMap();                     // 0x01046fc0

struct cStarManager {
    void GetStarRecords(const Vec3& position, const struct tStarSearchCriteria& criteria,
                        struct cRefVector& out);                 // 0x00bb1080
    void ActivatePlanetRecordsForQuery(cStarRecord* record, i32 flag); // 0x00bb4af0
    void GetOrActivatePlanet(cPlanet* planet, void** out);           // 0x00bb59b0
};

cStarManager* __cdecl StarManager();                // 0x00b3d2a0
cPlanet* __cdecl GetPlayerHomePlanet();             // 0x01021370

struct cSPSimulatorPlayerUFO {
    f32 GetMaxTravelDistance();                     // 0x00ffbfc0
};

cSPSimulatorPlayerUFO* __cdecl GetUFOSimulator();   // 0x00ffbe50

struct cMissionManager {
    i32 FUN_00febf80(void* p);                      // 0x00febf80 (ret 4)
};

cMissionManager* __cdecl GetMissionManager();       // 0x00feb9f0

struct RandomLinearCongruential {
    u32 RandomUint32Uniform(u32 range);             // 0x00a68fb0
};

RandomLinearCongruential gRandom;                   // 0x01601760
extern Vec3 gDefaultPosition;                       // 0x016919b8
extern f32  gNegTen;                                // 0x013f561c

// ---------------------------------------------------------------------------------------------
// Star search criteria (0x1c bytes)
// ---------------------------------------------------------------------------------------------
struct tStarSearchCriteria {
    u32   mAcceptableStarTypes;         // +0x00  0x1ff1
    u32   mAcceptableSolarTech;         // +0x04  0x3e
    u32   mMiscFilters;                 // +0x08
    f32   mMinRange;                    // +0x0c
    f32   mMaxRange;                    // +0x10
    f32   mMaxTravel;                   // +0x14
    u32   mNumJumps;                    // +0x18
};

struct cRefVector {
    cStarRecord** mpBegin;              // 0x00
    cStarRecord** mpEnd;                // 0x04
    cStarRecord** mpCap;                // 0x08

    cRefVector() : mpBegin(0), mpEnd(0), mpCap(0) {}
};

// ---------------------------------------------------------------------------------------------
// cSPMissionMultiDelivery
// ---------------------------------------------------------------------------------------------
struct cSPMissionMultiDelivery {
    u8               mPad0000[0x9c];
    cPlanet*         mpActivePlanet;    // 0x09c
    u8               mPad0a0[0x68];
    cPointerVector   mVisualVec;        // 0x108
    u8               mPad114[0xe0];
    cBuyerVector     mBuyerVec;         // 0x1f4
    u8               mPad200[8];
    cItemVector      mItemVec;          // 0x208
    u8               mPad214[8];
    i32*             mpHandleVecBegin;  // 0x21c
    i32*             mpHandleVecEnd;    // 0x220
    i32*             mpHandleVecCap;    // 0x224

    i32 GetFetchItemName(cWString* out);                    // 0x00c58260
    i32 GetItemPlanetNameList(cWString* out);               // 0x00c58920
    i32 GetNumItemsNotDeliveredToBuyer(cPlanet* p);         // 0x00c572c0
    u8  GetTagString(u32 tag, cWString* out);               // 0x00c58ad0
    void GetText(u32 textId, cWString* out);                // 0x00c487d0
    void Cleanup();                                         // 0x00c59190
    void Reset();                                           // 0x00c49f90
    bool IsInBuyerPlanetList(void* target);                 // 0x00c570e0
    bool PickItemPlanets(u32 minCount, u32 maxCount);       // 0x00c59240
    i32  CreateStarMapDestinationIndicator(cStarRecord* from, cStarRecord* to, u32 param); // 0x00c58b70
    f32  ReadMinRange();                                    // 0x00c45b80
    f32  ReadMaxRange();                                    // 0x00c45bd0
    u32  ReadNumJumps();                                    // 0x00c45c20
};

// Base mission class method (tail-called from the dispatch chain).
struct cSPMissionBase {
    i32 GetTagString(u32 tag, cWString* out);       // 0x00c491c0
};

// ---------------------------------------------------------------------------------------------
// Opaque extern callees referenced by absolute address.
// ---------------------------------------------------------------------------------------------
void __cdecl WStr_Assign(cWString* dst, const void* src);          // 0x00423650
void __cdecl WStr_Format(cWString* dst, const wchar_t_* fmt, ...); // 0x0041e050
void __cdecl WStr_AppendFormat(cWString* dst, const wchar_t_* fmt, ...); // 0x004e0850
extern u8           gItemSeparator[];                              // 0x0146f368

void __cdecl MemCopy(void* dst, const void* src, u32 bytes);       // 0x011e0744

// ---------------------------------------------------------------------------------------------
// Definitions
// ---------------------------------------------------------------------------------------------
// @ 0x00c58ad0
// Tag-dispatch returning localized mission strings.
u8 cSPMissionMultiDelivery::GetTagString(u32 tag, cWString* out)
{
    if (tag == 0x97cc2aa3) {
        cPlanet* planet = (cPlanet*)mBuyerVec.mpBegin[0].mpObject;
        if (planet != 0) {
            cWString* name = (cWString*)planet->GetName();
            if (name != out)
                out->assign(name->mpBegin, name->mpEnd);
        }
        return 1;
    }
    if (tag == 0x659ef0ac) {
        GetFetchItemName(out);
        return 1;
    }
    if (tag == 0xaa6cdbb8) {
        GetItemPlanetNameList(out);
        return 1;
    }
    if (tag == 0x8aad4d34) {
        i32 n = GetNumItemsNotDeliveredToBuyer((cPlanet*)mBuyerVec.mpBegin[0].mpObject);
        WStr_Format(out, (const wchar_t_*)0x013f01bc, n);
        return 1;
    }
    return ((struct cSPMissionBase*)this)->GetTagString(tag, out);
}

// @ 0x00c58920
// Builds the localized "item : planet / species" list for the delivery mission.
i32 cSPMissionMultiDelivery::GetItemPlanetNameList(cWString* out)
{
    cWString text;
    GetText(0x4bb21f92, &text);

    i32 count = (i32)((u8*)mItemVec.mpEnd - (u8*)mItemVec.mpBegin) / 0x14;
    for (i32 i = 0, offset = 0; i < count; ++i, offset += 0x14) {
        cPlanet* planet = (cPlanet*)*(void**)((u8*)mItemVec.mpBegin + offset);

        cWString name;
        cWString sortName;

        if (planet != 0) {
            cWString* pName = planet->GetName();
            if (pName != &name)
                name.assign(pName->mpBegin, pName->mpEnd);
        }
        if (*(cPlanet**)((u8*)mItemVec.mpBegin + offset) != 0) {
            cPlanet* p = *(cPlanet**)((u8*)mItemVec.mpBegin + offset);
            cStarRecord* source = p->mpModel->SortBanners();
            if (source != 0) {
                cWString* pSortName = source->GetName();
                if (pSortName != &sortName)
                    sortName.assign(pSortName->mpBegin, pSortName->mpEnd);
            }
        }

        WStr_AppendFormat(out, (const wchar_t_*)text.mpBegin,
                          name.mpBegin, sortName.mpBegin);
        if (i != count - 1)
            WStr_AppendFormat(out, (const wchar_t_*)gItemSeparator);

        sortName.Release();
        name.Release();
    }
    text.Release();
    return 0;
}

// @ 0x00c58b70
// Creates the star-map visual + point stream that shows the route between two stars.
i32 cSPMissionMultiDelivery::CreateStarMapDestinationIndicator(cStarRecord* from,
                                                              cStarRecord* to, u32 param)
{
    if (from == 0 || to == 0)
        return -1;

    VEffect* visual = GetStarMap()->CreateStarRecordVisual(from, 0x166521a5u, param);
    GetStarMap()->AddVisual(visual, 0);
    mVisualVec.push_back(visual);

    Vec3 fromPos;
    {
        const Vec3& ref = from->GetPosition();
        fromPos.x = ref.x;
        fromPos.y = ref.y;
        fromPos.z = ref.z;
    }
    const Vec3& toRef = to->GetPosition();
    Vec3 delta;
    delta.x = toRef.x - fromPos.x;
    delta.y = toRef.y - fromPos.y;
    delta.z = toRef.z - fromPos.z;

    f32 distanceSq = delta.x * delta.x + (delta.y * delta.y + delta.z * delta.z);
    u32 n = 1 - (u32)(InlineSqrt(distanceSq) * gNegTen);
    u32 count = n + 1;

    cFloatVector points;
    points.reserve(count * 3 * 4);

    f32 inv = 1.0f / (f32)n;
    Vec3 step;
    step.x = delta.x * inv;
    step.y = delta.y * inv;
    step.z = delta.z * inv;

    for (u32 i = 0; i < count; ++i) {
        points.push_back(fromPos.x);
        points.push_back(fromPos.y);
        points.push_back(fromPos.z);
        fromPos.x += step.x;
        fromPos.y += step.y;
        fromPos.z += step.z;
    }

    VEffect* effect = GetStarMap()->FUN_01045120(from->mField70, visual);
    if (effect == 0) {
        if (SpIsOwned(points.mpBegin))
            WFree(points.mpBegin);
        return -1;
    }

    effect->FUN_0044(13, points.mpBegin, (i32)(count * 3));

    u32 argb = GetMissionManager()->FUN_00febf80(this);
    Vec3 rgb;
    rgb.x = (f32)((argb >> 16) & 0xff) * (1.0f / 255.0f);
    rgb.y = (f32)((argb >> 8) & 0xff) * (1.0f / 255.0f);
    rgb.z = (f32)(argb & 0xff) * (1.0f / 255.0f);
    effect->FUN_0040(5, &rgb, 1);

    if (SpIsOwned(points.mpBegin))
        WFree(points.mpBegin);
    return (i32)visual;
}

// @ 0x00c58f10
// Deserializes the buyer list of the delivery mission.
IArchiver& ReadBuyerSequence(IArchiver& ar, cBuyerVector& vec)
{
    vec.erase(vec.mpBegin, vec.mpEnd);

    u32 count = 0;
    IArchiveWriter* writer = ar.GetWriter();
    void* stream = writer->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec.reserve(count);

    for (u32 i = 0; i < count; ++i) {
        tBuyerInfo info;
        info.mpObject = 0;
        info.mField4 = 0;
        info.mField8 = 0;
        operator>>(ar, info);
        vec.push_back(info);
        if (info.mpObject)
            info.mpObject->Release();
    }
    return ar.EndRead();
}

// @ 0x00c59010
// Deserializes the item list of the delivery mission.
IArchiver& ReadItemSequence(IArchiver& ar, cItemVector& vec)
{
    vec.erase(vec.mpBegin, vec.mpEnd);

    u32 count = 0;
    IArchiveWriter* writer = ar.GetWriter();
    void* stream = writer->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec.reserve(count);

    for (u32 i = 0; i < count; ++i) {
        tItemInfo item;
        item.mpObject = 0;
        item.mPosition.x = gDefaultPosition.x;
        item.mPosition.y = gDefaultPosition.y;
        item.mPosition.z = gDefaultPosition.z;
        item.mFlag = false;

        IArchiveWriter* flagWriter = ar.GetWriter();
        ReadBool(flagWriter->GetStream(), &item.mFlag);
        if (item.mpObject) {
            IRefCounted* old = item.mpObject;
            item.mpObject = 0;
            old->Release();
        }
        ar.SerializeItem(0x3275872u, &item.mpObject, 0);
        vec.push_back(item);
        if (item.mpObject)
            item.mpObject->Release();
    }
    return ar.EndRead();
}

// @ 0x00c59190
// Releases mission vectors and star-map visuals, then trims the handle list.
void cSPMissionMultiDelivery::Cleanup()
{
    // Release the buyer-info and item-info vectors.
    cBuyerVector* buyerVec = &mBuyerVec;
    buyerVec->erase(buyerVec->mpBegin, buyerVec->mpEnd);
    cItemVector* itemVec = &mItemVec;
    itemVec->erase(itemVec->mpBegin, itemVec->mpEnd);

    i32 count = (i32)(mpHandleVecEnd - mpHandleVecBegin);
    for (i32 i = 0; i < count; ++i) {
        i32 handle = mpHandleVecBegin[i];
        if (handle != -1)
            GetStarMap()->RemoveVisual(handle, 0);
    }

    // Trim the handle list back to empty.
    i32* first = mpHandleVecBegin;
    i32* last = mpHandleVecEnd;
    MemCopy(first, last, (i32)((char*)last - (char*)mpHandleVecEnd));
    mpHandleVecEnd -= last - first;

    Reset();
}

// @ 0x00c59240
// Picks a random set of reachable planets and fills the item list with them.
bool cSPMissionMultiDelivery::PickItemPlanets(u32 minCount, u32 maxCount)
{
    u32 target = minCount + gRandom.RandomUint32Uniform(maxCount - minCount);
    cStarRecord* targetStar = mpActivePlanet->mpModel->SortBanners();
    cPlanet* home = GetPlayerHomePlanet();

    cRefVector records;
    records.mpBegin = 0;
    records.mpEnd = 0;
    records.mpCap = 0;

    f32 minRange = ReadMinRange();
    f32 maxRange = ReadMaxRange();
    u32 numJumps = ReadNumJumps();

    mItemVec.erase(mItemVec.mpBegin, mItemVec.mpEnd);

    tStarSearchCriteria criteria;
    criteria.mMiscFilters = 0;
    criteria.mMinRange = 0.0f;
    criteria.mMaxRange = 0.0f;
    criteria.mMaxTravel = 0.0f;
    criteria.mNumJumps = 0;
    if (0.0f <= minRange)
        criteria.mMinRange = minRange;
    if (0.0f < maxRange)
        criteria.mMaxRange = maxRange;
    criteria.mAcceptableStarTypes = 0x1ff1;
    criteria.mAcceptableSolarTech = 0x3e;
    criteria.mMaxTravel = GetUFOSimulator()->GetMaxTravelDistance();
    criteria.mNumJumps = numJumps;

    StarManager()->GetStarRecords(targetStar->GetPosition(), criteria, records);

    i32 count = (i32)((u8*)records.mpEnd - (u8*)records.mpBegin) / 4;
    i32 index = (i32)gRandom.RandomUint32Uniform(count);

    for (i32 tries = 0; tries < count; ++tries) {
        cStarRecord* record = records.mpBegin[index];
        if (record->TestFlag(1))
            goto advance;
        if (record == targetStar)
            goto advance;

        StarManager()->ActivatePlanetRecordsForQuery(record, 0);
        {
            cPlanetVector* planets = record->GetPlanets();
            if (planets->mpBegin == planets->mpEnd)
                goto advance;
            cPlanet* planet = planets->mpBegin[0];
            if (planet == home)
                goto advance;
            if (((1 << (planet->mField28 & 0x1f)) & 0x3c) == 0)
                goto advance;
            if (planet->FUN_00b8d9b0() != 0)
                goto advance;

            void* activated = 0;
            StarManager()->GetOrActivatePlanet(planet, &activated);
            if (!IsInBuyerPlanetList(activated)) {
                tItemInfo item;
                mItemVec.Add(item.FUN_00c57a80(activated, 0, gDefaultPosition));
                if (item.mpObject)
                    item.mpObject->Release();
                if (mItemVec.size() >= (i32)target) {
                    if (activated)
                        ((IRefCounted*)activated)->Release();
                    break;
                }
            }
            if (activated)
                ((IRefCounted*)activated)->Release();
        }
advance:
        index = (index + 1) % count;
    }

    bool complete = mItemVec.size() >= (i32)numJumps;

    for (cStarRecord** p = records.mpBegin; p < records.mpEnd; ++p) {
        cStarRecord* record = *p;
        if (record != 0)
            record->Release();
    }
    if (SpIsOwned(records.mpBegin))
        WFree(records.mpBegin);

    return complete;
}
