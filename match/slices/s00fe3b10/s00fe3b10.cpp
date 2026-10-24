// Slice s00fe3b10: SP::cSPBadgeManager (badge database: serialisation, badge/card lookups, the
// hint-badge strings and the property-list driven statistics) plus the two living-universe badge
// context predicates at the front of the unit.
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc: none of these bodies installs an EH frame).
// Out-of-line callees are only declared; their original addresses are in the trailing comments.
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------------------------------------
// data globals touched by this slice
// ---------------------------------------------------------------------------------------------
extern const uint32_t g_badgeEventIds[];        // 0x01494214 (the ten tracked badge event ids)
extern const char g_statStrings[];              // 0x063bb6d0 (GetStatString texts, laid end to end)
extern const char g_badgePropNames[];           // 0x04a37dfb (two adjacent property names)
extern const char g_serializedFieldName[];      // 0x015b42f8 (name handed to cVarListSerializer)
extern void* g_pSpaceTokenTranslator;           // 0x016e0d08 (its +0x44 holds the badge being named)

// wcslen as the compiler inlines it at every call site in this unit
static inline size_t WStrLen(const wchar_t* pszText)
{
    const wchar_t* pszEnd = pszText;
    while (*pszEnd != 0)
        ++pszEnd;
    return (size_t)(pszEnd - pszText);
}

// ---------------------------------------------------------------------------------------------
// out-of-line engine entries
// ---------------------------------------------------------------------------------------------
int32_t     __cdecl GetUniverseContext();                  // 0x01021080
void*       __cdecl GetActivePlanet();                     // 0x01021260
void*       __cdecl SpaceGameGet();                        // 0x01002bd0
void        __cdecl FUN_00f47380(void* pBlock);            // 0x00f47380 operator delete[]
void        __cdecl FUN_01068400(void** ppItems, uint32_t nCount);   // 0x01068400
void        __cdecl FUN_00aea5d0(void** ppEnd, const void* pValue);  // 0x00aea5d0 eastl vector grow
void        __cdecl FUN_0093c5a0(void* pOut, const char* pszText, int nLength); // 0x0093c5a0
void        __cdecl FUN_00579a90(void* pString, uint32_t nCount);    // 0x00579a90
void        __cdecl FUN_0056e2d0(void* pString, const void* pOther); // 0x0056e2d0

struct tRBNode;

tRBNode*    __cdecl RBTreeIncrement(tRBNode* pNode);       // 0x00921580
void        __cdecl GetPropertyAsText(void* pObject, const char* pszName, void* pOut); // 0x006a1360
void        __cdecl GetPropertyAsKeyInstance(void* pObject, uint32_t id, void* pOut);   // 0x006a12a0

namespace EA { namespace IO {
class IStream;
bool __cdecl WriteUint32(IStream* pStream, const uint32_t* pData, int nCount, int nFlags); // 0x0093aa70
bool __cdecl ReadInt32(IStream* pStream, uint32_t* pData, int nCount, int nFlags);         // 0x0093a780
} }

// ---------------------------------------------------------------------------------------------
// small engine types
// ---------------------------------------------------------------------------------------------
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

// eastl::map<unsigned, X>: 0x1c bytes (rb_base, anchor, size, allocator)
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

// eastl::map<unsigned, cPropertyList*>: same shape, different node destructor instantiation
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

// eastl::basic_string<wchar_t>: begin/end/capacity
class eastlWString {
public:
    wchar_t* mpBegin;                   // +0x00
    wchar_t* mpEnd;                     // +0x04
    wchar_t* mpCapacity;                // +0x08
    void assign(const wchar_t* pFirst, const wchar_t* pLast);        // 0x00423650
    const wchar_t* c_str() const { return mpBegin; }
};

// SP::cString: a wide string that knows how to fetch C strings out of property lists
class cString {
public:
    eastlWString mText;                 // +0x00
    cString();                                                     // 0x006b5060
    ~cString();                                                    // 0x006b5240
    const wchar_t* GetText() const;                                // 0x006b55c0
};

// one bucket of the hint-string table: the mapped string lives right behind the next pointer
struct tHashNode {
    tHashNode*   mpNext;                // +0x00
    eastlWString mValue;                // +0x04
};

// eastl::hashtable<unsigned, eastl::wstring>
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

// SP::cVarListSerializer: opaque 0xa14-byte driver around the saved-game variable list
class cVarListSerializer {
public:
    cVarListSerializer(const void* pOwner, const char* pszName, uint32_t nVersion);  // 0x00692f90
    bool Serialize(class cOutStream* pStream);                                      // 0x00692900
    bool Serialize(class cInStream* pStream);                                       // 0x00693e10
    uint32_t mPad00[0xa14 / 4];         // +0x0000
};

namespace EA { namespace IO { class IStream; } }

class cSaveStream {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual EA::IO::IStream* GetIStream();                           // +0x18
};

class cOutStream {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual void EndElement();                                       // +0x1c
    virtual cSaveStream* GetStream();                                // +0x20
};

// a property list entry as handed back by the "array of records" accessor
struct tBadgeRecord {
    uint32_t mId;                       // +0x00
    uint32_t mValue04;                  // +0x04
    uint32_t mValue08;                  // +0x08
};

// the record array returned by cPropertyList::GetRecords
struct tRecordArray {
    tBadgeRecord* mpData;               // +0x00
    uint32_t      mPad04;               // +0x04
    uint32_t      mnCount;              // +0x08
    uint32_t      mPad0c;               // +0x0c
    uint32_t      mFlags;               // +0x10
    uint16_t      mPad14;               // +0x14
    uint16_t      mType;                // +0x16
};

// a numeric property value handed back by cPropertyList::GetProperty
struct tVariant {
    uint32_t mPad00[4];                 // +0x00
    uint16_t mPad10;                    // +0x10
    uint16_t mType;                     // +0x12
    int32_t* GetInt();                                               // 0x0041e990
};

// SP::cPropertyList (only the entries this slice reaches)
class cPropertyList {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual bool HasProperty(uint32_t nId);                          // +0x1c
    virtual void v08();                                              // +0x20
    virtual bool GetProperty(uint32_t nId, tVariant** ppOut);        // +0x24
    virtual tRecordArray* GetRecords(uint32_t nId);                  // +0x28
};

// SP::cUIMissionCardPanel (the owning panel of the badge card that is currently shown)
class cUIMissionCardPanel {
public:
    void RemoveBadgeCard(void* pCard);                               // 0x00e15d30
    void AddBadgeCard(void* pCard);                                  // 0x00e18150
};

cUIMissionCardPanel* __cdecl FUN_00b3d400();                         // 0x00b3d400

// object behind the trigger-manager lookup in GetStatString
class cStringContext {
public:
    const wchar_t* GetStatText();                                    // 0x00adde90
};

cStringContext* __cdecl FUN_00b3d4d0(uint32_t nId, const void* pDesc, int nFlags); // 0x00b3d4d0

// living-universe / galaxy objects the two predicates at the head of the unit inspect
class cStarContext;
cStarContext* __cdecl FUN_01021230();                                 // 0x01021230

class cGalaxyPlanet {
public:
    uint32_t       mPad00[0x13c / 4];   // +0x000
    cGalaxyPlanet* mpOwner13c;          // +0x13c
    int32_t        GetSystemId();                                    // 0x00b8de30
};

class cStarContext {
public:
    uint32_t mPad00[0x48 / 4];          // +0x00
    int32_t  mnSystemId;                // +0x48
};

// badge entry looked up by the star-manager sweep
class cBadgeEntry {
public:
    virtual void AddRef();                                           // +0x00
    virtual void Release();                                          // +0x04
};

cBadgeEntry* __fastcall FUN_00c30c60(uint32_t nId);                   // 0x00c30c60

class tStarManager;
tStarManager* __cdecl StarManager();                                  // 0x00b3d2a0

class tStarManager {
public:
    tU32Tree* GetBadgeTree();                                        // 0x00ba6430
};

// eastl::vector<EA::AutoRefCount<cBadgeEntry>>
class tBadgeVec {
public:
    cBadgeEntry** mpBegin;              // +0x00
    cBadgeEntry** mpEnd;                // +0x04
    cBadgeEntry** mpCapacity;           // +0x08
    uint32_t      mPad0c;               // +0x0c
    uint32_t      mPad10;               // +0x10
    void push_back(const class tBadgeRef& r);                        // inline in the original
};

// EA::AutoRefCount<cBadgeEntry>
class tBadgeRef {
public:
    cBadgeEntry* mpObject;              // +0x00
    explicit tBadgeRef(cBadgeEntry* pObject) : mpObject(pObject)
    {
        if (mpObject != 0)
            mpObject->AddRef();
    }
    tBadgeRef(const tBadgeRef& r) : mpObject(r.mpObject)
    {
        if (mpObject != 0)
            mpObject->AddRef();
    }
    ~tBadgeRef()
    {
        if (mpObject != 0)
            mpObject->Release();
    }
};

void tBadgeVec::push_back(const tBadgeRef& r)
{
    if (mpEnd < mpCapacity) {
        cBadgeEntry* pObject = r.mpObject;
        *mpEnd++ = pObject;
        if (pObject != 0)
            pObject->AddRef();
    } else {
        FUN_00aea5d0((void**)mpEnd, &r);
    }
}

// ---------------------------------------------------------------------------------------------
// SP::cContentValidationSummarizer: first base (vptr + one data word) -> serialisable sub-object
// sits at +0x08, badge maps start at +0x10.
// ---------------------------------------------------------------------------------------------
class cContentValidationSummarizer {
public:
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06();
    virtual ~cContentValidationSummarizer() {}
    uint32_t mPad04;                    // +0x04
};

class cISerializableObject {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
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

// ---------------------------------------------------------------------------------------------
// living-universe badge predicates
// ---------------------------------------------------------------------------------------------

// @ 0x00fe3b10
bool FUN_00fe3b10(cGalaxyPlanet* pPlanet)
{
    if (GetUniverseContext() == 0) {
        void* pActive = GetActivePlanet();
        if (pPlanet != 0 && pActive == pPlanet)
            return true;
    }
    return false;
}

// @ 0x00fe3b30
bool FUN_00fe3b30(cGalaxyPlanet* pPlanet)
{
    if (SpaceGameGet() == 0)
        return false;
    if (pPlanet == 0)
        return false;
    switch (GetUniverseContext()) {
    case 2:
        return true;
    case 0:
        if (((cGalaxyPlanet*)GetActivePlanet())->mpOwner13c == pPlanet)
            return true;
        return false;
    case 1: {
        int32_t nSystem = ((cStarContext*)FUN_01021230())->mnSystemId;
        if (nSystem == pPlanet->GetSystemId())
            return true;
        return false;
    }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------
// badge manager
// ---------------------------------------------------------------------------------------------

// @ 0x00fe3b90
bool FUN_00fe3b90(tBadgeVec* pBadges)
{
    tU32Tree* pTree = StarManager()->GetBadgeTree();
    for (tPairNode* p = pTree->begin(); p != pTree->end(); p = (tPairNode*)RBTreeIncrement(&p->mBase)) {
        cBadgeEntry* pEntry = FUN_00c30c60(p->mValue);
        if (pEntry != 0) {
            tBadgeRef ref(pEntry);
            pBadges->push_back(ref);
        }
    }
    return true;
}

// @ 0x00fe3c40
void cISerializableObject::Write(cOutStream* pStream)
{
    uint32_t nVersion;
    cSaveStream* pSaveStream = pStream->GetStream();
    EA::IO::IStream* pIStream = pSaveStream->GetIStream();
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

struct tStatStringDesc {
    const char* mpText;                 // +0x00
    uint32_t    mPad04;                 // +0x04
    uint32_t    mId;                    // +0x08
};

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

// ---------------------------------------------------------------------------------------------
// map serialisers (map<uint,X> written through a stream object)
// ---------------------------------------------------------------------------------------------

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
