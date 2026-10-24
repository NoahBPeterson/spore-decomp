// Slice s00ea9dd0 (gold7): three functions of one unnamed retail class that derives from
// Skinner::PaintSystem (vtable 0x013eb394) and Simulator::cContentValidationSummarizer
// (vtable 0x013ec458) and owns two eastl hashtables plus one EA::Messaging handler id:
//
//   0x00eaa7c0  ctor                     (125 bytes, ret)
//   0x00eaa850  dtor                     (145 bytes, ret)
//   0x00eaa910  KeyModeMap::operator[]   (134 bytes, thiscall ret 4)
//
// 0x00eaa910 is the sorted-vector subscript used by the static initialiser at 0x00eaa9a0 to
// fill the message -> mix-mode tables; its callees are the shared 8-byte-stride binary search
// 0x005701b0 and the vector insert 0x00c72d00.
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#pragma warning(disable: 4100)

void operator delete[](void* pBlock);

namespace EA { namespace Messaging {

// Removes a handler registration (five dwords pushed right to left, cdecl).
void RemoveHandler(uint32_t nHandlerId, uint32_t nOwner, uint32_t nFlags,
                   uint32_t nExtra, uint32_t nReserved);            // 0x00571db0

} }

namespace SP {

class cSPToolStrategy;

// ---------------------------------------------------------------------------
// eastl::hashtable instantiations, 0x20 bytes each.  Only the fields this
// slice touches are named; the untouched words keep the retail offsets.
// ---------------------------------------------------------------------------

// hashtable<unsigned int, pair<unsigned int const, EA::AutoRefCount<cSPToolStrategy> > >
struct StrategyHashMap {
    uint32_t mHashCode;                        // +0x00
    void**   mpBucketArray;                    // +0x04
    uint32_t mnBucketCount;                    // +0x08
    uint32_t mnElementCount;                   // +0x0c
    float    mfMaxLoadFactor;                  // +0x10
    float    mfGrowthFactor;                   // +0x14
    uint32_t mnResizeCount;                    // +0x18
    uint32_t mPad1c;                           // +0x1c

    StrategyHashMap();
    ~StrategyHashMap();

    void DoFreeNodes(void** pBucketArray, uint32_t nBucketCount);    // 0x00961d60
};

// hashtable<EA::ResourceMan::Key, pair<EA::ResourceMan::Key const, int> >
struct KeyCountHashMap {
    uint32_t mHashCode;                        // +0x00
    void**   mpBucketArray;                    // +0x04
    uint32_t mnBucketCount;                    // +0x08
    uint32_t mnElementCount;                   // +0x0c
    float    mfMaxLoadFactor;                  // +0x10
    float    mfGrowthFactor;                   // +0x14
    uint32_t mnResizeCount;                    // +0x18
    uint32_t mPad1c;                           // +0x1c

    KeyCountHashMap();
    ~KeyCountHashMap();

    void DoFreeNodes(void** pBucketArray, uint32_t nBucketCount);    // 0x007611f0
};

// The hashtables' shared static empty bucket (mnBucketCount == 1 points here).
extern void* gEmptyBucketArray[];              // 0x0154df28

// ---------------------------------------------------------------------------
// polymorphic bases
// ---------------------------------------------------------------------------
class cPaintSystem {                           // vtable 0x013eb394
public:
    virtual void Paint();                      // slot 0
    virtual ~cPaintSystem() {}
};

class cValidationSummarizer {                  // vtable 0x013ec458
public:
    cValidationSummarizer() : mpObject(0) {}
    virtual void Summarize();                  // slot 0
    virtual ~cValidationSummarizer() {}
    void* mpObject;                            // +0x04 of the base (object +0x08)
};

// ---------------------------------------------------------------------------
// owner: 0x6c bytes
// ---------------------------------------------------------------------------
class cSummaryHandler : public cPaintSystem, public cValidationSummarizer {
public:
    cSummaryHandler();
    ~cSummaryHandler();                        // reached through 0x00eaa8f0 (scalar deleting dtor)
    void Destroy();                            // 0x00eaa850

    StrategyHashMap mStrategies;               // +0x0c
    KeyCountHashMap mCounts;                   // +0x2c
    uint32_t mHandlerId;                       // +0x4c
    uint32_t mHandlerOwner;                    // +0x50
    uint32_t mHandlerFlags;                    // +0x54
    uint32_t mHandlerExtra;                    // +0x58
    uint32_t mHandlerReserved;                 // +0x5c
    uint32_t mField60;                         // +0x60
    uint32_t mField64;                         // +0x64
    bool     mbFlag68;                         // +0x68
};

// ---------------------------------------------------------------------------
// sorted vector_map<unsigned int, unsigned int>: 8-byte pairs, 0x20-byte object
// ---------------------------------------------------------------------------
struct KeyModePair {
    uint32_t first;                            // +0x00
    uint32_t second;                           // +0x04
};

struct KeyModeMap {
    KeyModePair* mpBegin;                      // +0x00
    KeyModePair* mpEnd;                        // +0x04
    KeyModePair* mpCapacity;                   // +0x08
    uint32_t     mPad0c;                       // +0x0c
    uint32_t     mPad10;                       // +0x10
    uint8_t      mbFlag14;                     // +0x14
    uint8_t      mPad15[3];                    // +0x15
    uint32_t     mPad18;                       // +0x18
    uint32_t     mPad1c;                       // +0x1c

    uint32_t* operator[](const uint32_t& nKey);
    KeyModePair* InsertAt(KeyModePair* pPosition, const KeyModePair* pValue);  // 0x00c72d00
};

// Shared binary search over 8-byte pairs comparing the first dword (unsigned <).
KeyModePair* __cdecl LowerBound(KeyModePair* pFirst, KeyModePair* pLast,
                                const uint32_t* pKey, uint8_t nFlag);     // 0x005701b0

// ---------------------------------------------------------------------------
// hashtable construction / destruction (inlined into the owner ctor / dtor)
// ---------------------------------------------------------------------------
StrategyHashMap::StrategyHashMap()
{
    mfMaxLoadFactor = 1.0f;
    mfGrowthFactor = 2.0f;
    mnBucketCount = 1;
    mnElementCount = 0;
    mnResizeCount = 0;
    mpBucketArray = gEmptyBucketArray;
}

StrategyHashMap::~StrategyHashMap()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        operator delete[](mpBucketArray);
}

KeyCountHashMap::KeyCountHashMap()
{
    mfMaxLoadFactor = 1.0f;
    mfGrowthFactor = 2.0f;
    mnBucketCount = 1;
    mpBucketArray = gEmptyBucketArray;
    mnElementCount = 0;
    mnResizeCount = 0;
}

KeyCountHashMap::~KeyCountHashMap()
{
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
    if (mnBucketCount > 1)
        operator delete[](mpBucketArray);
}

// ---------------------------------------------------------------------------
// ctor
// ---------------------------------------------------------------------------
// @ 0x00eaa7c0
cSummaryHandler::cSummaryHandler()
{
    mHandlerId = 0;
    mHandlerOwner = 0;
    mHandlerFlags = 0;
    mHandlerExtra = 0;
    mHandlerReserved = 0;
    mField60 = 0;
    mField64 = 0;
    mbFlag68 = false;
}

// ---------------------------------------------------------------------------
// teardown.  Retail runs this code from the scalar deleting destructor at
// 0x00eaa8f0.  cl emits the derived-vtable stores at the entry of a destructor
// whose body performs calls, but 0x00eaa850 has none, so the same sequence is
// written as an explicit teardown that runs the member destructors (map order
// 0x2c then 0x0c) and then the two base destructors, which restore the base
// vtables (0x013eb394 at +0x00, 0x013ec458 at +0x04).
// ---------------------------------------------------------------------------
// @ 0x00eaa850
void cSummaryHandler::Destroy()
{
    if (mHandlerId != 0) {
        uint32_t nHandlerId = mHandlerId;
        mHandlerId = 0;
        EA::Messaging::RemoveHandler(nHandlerId, mHandlerOwner, mHandlerFlags,
                                     mHandlerExtra, mHandlerReserved);
    }

    mCounts.~KeyCountHashMap();
    mStrategies.~StrategyHashMap();

    this->cValidationSummarizer::~cValidationSummarizer();
    this->cPaintSystem::~cPaintSystem();
}

// ---------------------------------------------------------------------------
// subscript / find-or-insert of the sorted vector map
// ---------------------------------------------------------------------------
// @ 0x00eaa910
uint32_t* KeyModeMap::operator[](const uint32_t& nKey)
{
    KeyModePair* pBegin = mpBegin;
    KeyModePair* pEnd = mpEnd;
    KeyModePair* pIt = LowerBound(pBegin, pEnd, &nKey, mbFlag14);
    if (pIt == pEnd || nKey < pIt->first) {
        const uint32_t nKeyValue = nKey;
        KeyModePair pair;
        pair.first = nKeyValue;
        pair.second = 0;
        if (pIt != pEnd && nKeyValue < pIt->first)
            pIt = LowerBound(pBegin, pIt, &pair.first, mbFlag14);
        else
            pIt = LowerBound(pIt, pEnd, &pair.first, mbFlag14);
        if (pIt == pEnd || nKeyValue < pIt->first)
            pIt = InsertAt(pIt, &pair);
    }
    return &pIt->second;
}

} // namespace SP
