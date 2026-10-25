// src/game/SPGonzago/SPBadgeManager.cpp -- migrated from slice(s) s00fe4be0, s00fe3b10 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPBadgeManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cISerializableObject.h"
#include "SP/cIObjectDatabaseOStream.h"
#include "SP/cPropertyList.h"
#include "SP/cString.h"
#include "SP/cVarListSerializer.h"
#include "EA/Variant.h"

// unnamed retail callees and globals (address in the comment)
extern const uint32_t g_badgeEventIds[];        // 0x01494214 (the ten tracked badge event ids)
extern const char g_statStrings[];              // 0x063bb6d0 (GetStatString texts, laid end to end)
extern const char g_badgePropNames[];           // 0x04a37dfb (two adjacent property names)
extern const char g_serializedFieldName[];      // 0x015b42f8 (name handed to cVarListSerializer)
extern void* g_pSpaceTokenTranslator;           // 0x016e0d08 (its +0x44 holds the badge being named)

// ---- items of slice s00fe3b10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t g_badgeEventIds[];        // 0x01494214 (the ten tracked badge event ids)
extern const char g_statStrings[];              // 0x063bb6d0 (GetStatString texts, laid end to end)
extern const char g_badgePropNames[];           // 0x04a37dfb (two adjacent property names)
extern const char g_serializedFieldName[];      // 0x015b42f8 (name handed to cVarListSerializer)
extern void* g_pSpaceTokenTranslator;           // 0x016e0d08 (its +0x44 holds the badge being named)
static inline size_t WStrLen(const wchar_t* pszText)
{
    const wchar_t* pszEnd = pszText;
    while (*pszEnd != 0)
        ++pszEnd;
    return (size_t)(pszEnd - pszText);
}
void        __cdecl FUN_00f47380(void* pBlock);            // 0x00f47380 operator delete[]
void        __cdecl FUN_01068400(void** ppItems, uint32_t nCount);   // 0x01068400
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
namespace EA {
namespace IO {
 class IStream_s00fe_3b10; 
}
}
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
namespace SP {
class cSPBadgeManager_s00fe_4be0 {
public:
    uint32_t FUN_00fe54d0(Property* pProperty);
    void     GetBadgeImageKey();  // 0x00fe5520 (SP::cSPBadgeManager::GetBadgeImageKey)
    void     TestRequirement();  // 0x00fe55b0 (SP::cSPBadgeManager::TestRequirement)

    uint8_t             pad000[0x10];                    // +0x00 .. +0x0f
    cBadgePropertyMap   mBadgeMap;                       // +0x10
};  // namespace SP
}
// ---- items of slice s00fe4be0 end

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
void __cdecl FUN_00fe5430()
{
}

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
void __thiscall cSPBadgeManager_s00fe_4be0::GetBadgeImageKey()
{
}
}  // namespace SP

// @ 0x00fe55b0
namespace SP {
void __thiscall cSPBadgeManager_s00fe_4be0::TestRequirement()
{
}
}  // namespace SP
