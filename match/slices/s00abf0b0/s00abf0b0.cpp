// Slice s00abf0b0: SP::cInteraction (one interaction: the target and agent slot lists, the
// variable map and the behaviour callbacks) and the interaction stack that owns the list of
// live interactions (two block allocated vectors, the top-of-stack queries and the trace dump).
//
// The 8-byte-entry slot vector of cInteraction stores {flags, payload} pairs, 128 entries per
// block; the stack's two vectors are eastl style block vectors (0x100-byte blocks) with a
// 16-byte-element name list and a 4-byte-element interaction list.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------------------------
extern "C" void* __cdecl operator_new(uint32_t nSize, const char* pTag, int nA, int nB, const char* pFile, int nLine); // 0x00f473a0
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380

extern char g_szSimulator[];        // 0x013f09b4 "Simulator"
extern char g_szEastlFile[];        // 0x013ebb38 ".../EASTL/allocator.h"
extern bool g_bStackReady;          // 0x0167a1b5
extern char g_szStackHeader[];      // 0x01459b54 "Interaction Stack:\n"
extern char g_szEmptyText[];        // 0x01459b67 ""
extern char g_szPtrLine[];          // 0x01459b40 "%s (ptr 0x%08x)\n"
extern char g_szDots[];             // 0x01459b38 "... \n"

void* __cdecl SP_BehaviorManager();                              // 0x00b3d260
bool  __cdecl FUN_00abece0(void* pVector, void* ppObject);       // 0x00abece0 slot vector contains
bool  __cdecl FUN_00abea90(void* pAgent);                        // 0x00abea90 IsAgentActive::evaluate
void  __cdecl FUN_00ca09f0(void* pVector, uint32_t nCount);      // 0x00ca09f0 4-byte slot vector init

// eastl::string8: assign/append used by the stack trace
void __cdecl FUN_005f9450(void* pString, const char* pFormat, ...);  // 0x005f9450 append_sprintf
void __cdecl FUN_00454cb0(void* pString, const char* pBegin, const char* pEnd); // 0x00454cb0 assign

struct AgentFilterRange;

// ---------------------------------------------------------------------------------------------
// 8-byte-entry slot vector (128 entries per block) used for the target and agent lists
// ---------------------------------------------------------------------------------------------
const uint32_t kFreeSentinel   = 0x3fffffff;
const uint32_t kInUseFlag      = 0x40000000;
const uint32_t kEndFlag        = 0x80000000;
const uint32_t kClearMask      = 0xbfffffff;
const uint32_t kLinkMask       = 0x3fffffff;
const uint32_t kKeepFlag       = 0x7fffffff;

template <typename T>
struct tSlotEntry {
    uint32_t mnFlags;      // +0x00 link / state flags
    T*       mpPayload;    // +0x04
};

template <typename T>
class tSlotVector {
public:
    tSlotEntry<T>** mpDir;          // +0x00 block pointer array
    tSlotEntry<T>** mpDirEnd;       // +0x04
    tSlotEntry<T>** mpCapacity;     // +0x08
    uint32_t        mPad0c;         // +0x0c
    uint32_t        mPad10;         // +0x10
    uint32_t        mnAppendIndex;  // +0x14 index of the last appended entry (biased by 0x7f)
    uint32_t        mnLowWater;     // +0x18 smallest entry index in use
    uint32_t        mnFreeHead;     // +0x1c head of the free list

    void Init()
    {
        mpDir = 0;
        mpDirEnd = 0;
        mpCapacity = 0;
        mnAppendIndex = 0x7f;
        mnLowWater = kFreeSentinel;
        mnFreeHead = kFreeSentinel;
    }
    uint32_t Size() const
    {
        return ((uint32_t)(mpDirEnd - mpDir) << 7) + mnAppendIndex - 0x7f;
    }
    tSlotEntry<T>* At(uint32_t nIndex) const
    {
        return mpDir[nIndex >> 7] + (nIndex & 0x7f);
    }
    void Grow();                    // 0x00abf2b0
    void Destroy(void* pOwner);     // 0x00abec70 (agents) / 0x00abec00 (targets)
    uint32_t Insert(T* const& pObject);
};

template <typename T>
uint32_t tSlotVector<T>::Insert(T* const& pObject)
{
    uint32_t nIndex = mnFreeHead;
    if (nIndex != kFreeSentinel)
    {
        mnFreeHead = At(nIndex)->mnFlags & kLinkMask;
        At(nIndex)->mnFlags &= kKeepFlag;
        At(nIndex)->mpPayload = pObject;
        if (pObject != 0)
            pObject->AddRef();
    }
    else
    {
        T* pData = pObject;
        if (pData != 0)
            pData->AddRef();
        nIndex = Size();
        Grow();
        tSlotEntry<T>* pEndEntry = &mpDirEnd[-1][mnAppendIndex];
        if (pEndEntry != 0)
            pEndEntry->mnFlags = kEndFlag;
        if (nIndex != 0)
            At(nIndex - 1)->mnFlags &= kClearMask;
        At(nIndex)->mnFlags |= kInUseFlag;
        At(nIndex)->mnFlags &= kKeepFlag;
        At(nIndex)->mpPayload = pData;
        if (pData != 0)
            pData->AddRef();
        if (pData != 0)
            pData->Release();
    }
    if (mnLowWater > nIndex)
        mnLowWater = nIndex;
    return nIndex;
}

// ---------------------------------------------------------------------------------------------
// agent filtering
// ---------------------------------------------------------------------------------------------
struct cInteractionAgent;

struct IsAgentActive {
    void* m_pInteraction;   // +0x00
    bool  m_bFlag;          // +0x04

    IsAgentActive(void* pInteraction = 0, bool bFlag = false)
        : m_pInteraction(pInteraction), m_bFlag(bFlag) {}
};

struct SlotIterator {
    tSlotVector<cInteractionAgent>* mpVector;   // +0x00
    uint32_t mnIndex;                           // +0x04

    bool operator!=(const SlotIterator& other) const
    {
        return (uint32_t)mpVector + mnIndex != (uint32_t)other.mpVector + other.mnIndex;
    }
    tSlotEntry<cInteractionAgent>* At(uint32_t nIndex) const
    {
        return mpVector->At(nIndex);
    }
};

struct AgentFilterRange {
    SlotIterator  mBegin;       // +0x00
    SlotIterator  mEnd;         // +0x08
    void*         mpOwner;      // +0x10
    bool          mbOwnerFlag;  // +0x14

    void Init(tSlotVector<cInteractionAgent>* pVector, const IsAgentActive* pFilter); // 0x00abf010
    void Advance();                                                                   // 0x00abeb20
};

// ---------------------------------------------------------------------------------------------
// interaction object interface (offsets come from the retail vtables)
// ---------------------------------------------------------------------------------------------
struct tAgentInterface {
    virtual void v00();                                         // 0x00
    virtual void v04();                                         // 0x04
    virtual void v08();                                         // 0x08
    virtual void v0c();                                         // 0x0c
    virtual void v10();                                         // 0x10
    virtual void v14();                                         // 0x14
    virtual void v18();                                         // 0x18
    virtual void v1c();                                         // 0x1c
    virtual void* v20();                                        // 0x20
    virtual void v24();                                         // 0x24
    virtual void* v28();                                        // 0x28
    virtual void v2c();                                         // 0x2c
    virtual void v30();                                         // 0x30
    virtual void v34();                                         // 0x34
    virtual int32_t v38();                                      // 0x38
    virtual void v3c(void* pOwner, int32_t nFlags);             // 0x3c
    virtual void v40(void* pOwner);                             // 0x40
    virtual void v44(AgentFilterRange range);                   // 0x44
    virtual void v48();                                         // 0x48
    virtual void v4c(bool bFlag);                               // 0x4c
    virtual void v50();                                         // 0x50
    virtual void v54();                                         // 0x54
    virtual void v58();                                         // 0x58
    virtual void v5c();                                         // 0x5c
    virtual void v60();                                         // 0x60
};

struct cInteractionAgent : tAgentInterface {
};

struct cInteractionTarget {
    virtual void v00();                                         // 0x00
    virtual void v04();                                         // 0x04
    virtual void v08();                                         // 0x08
    virtual void Attach(void* pOwner);                          // 0x0c
    virtual void v10();                                         // 0x10
    virtual void Release();                                     // 0x14
    virtual void AddRef();                                      // 0x18
};

// ---------------------------------------------------------------------------------------------
// eastl style block vectors used by the interaction stack
// ---------------------------------------------------------------------------------------------
struct tWideStringSlot {                // 16-byte element of the stack name list
    wchar_t* mpBegin;                   // +0x00
    wchar_t* mpEnd;                     // +0x04
    wchar_t* mpCapacity;                // +0x08
    uint32_t mPad0c;                    // +0x0c
};

class cInteraction;

class tBlockVector16 {
public:
    tWideStringSlot** mpDir;            // +0x00
    uint32_t          mnBlockCount;     // +0x04
    tWideStringSlot*  mpBegin;          // +0x08
    tWideStringSlot*  mpFirstBlock;     // +0x0c
    tWideStringSlot*  mpFirstBlockEnd;  // +0x10
    tWideStringSlot** mpFirstBlockSlot; // +0x14
    tWideStringSlot*  mpEnd;            // +0x18
    tWideStringSlot*  mpLastBlock;      // +0x1c
    tWideStringSlot*  mpLastBlockEnd;   // +0x20
    tWideStringSlot** mpLastBlockSlot;  // +0x24

    tBlockVector16(uint32_t nCount)
        : mpDir(0), mnBlockCount(0), mpBegin(0), mpFirstBlock(0), mpFirstBlockEnd(0),
          mpFirstBlockSlot(0), mpEnd(0), mpLastBlock(0), mpLastBlockEnd(0), mpLastBlockSlot(0)
    {
        init(nCount);
    }
    void init(uint32_t nCount);         // 0x00abf9e0
    void clear();                       // 0x00abfd40
    void destroy();                     // 0x00abfcb0
};

class tBlockVector4 {
public:
    cInteraction*** mpDir;              // +0x00
    uint32_t        mnBlockCount;       // +0x04
    cInteraction**  mpBegin;            // +0x08
    cInteraction**  mpFirstBlock;       // +0x0c
    cInteraction**  mpFirstBlockEnd;    // +0x10
    cInteraction*** mpFirstBlockSlot;   // +0x14
    cInteraction**  mpEnd;              // +0x18
    cInteraction**  mpLastBlock;        // +0x1c
    cInteraction**  mpLastBlockEnd;     // +0x20
    cInteraction*** mpLastBlockSlot;    // +0x24

    tBlockVector4(uint32_t nCount)
        : mpDir(0), mnBlockCount(0), mpBegin(0), mpFirstBlock(0), mpFirstBlockEnd(0),
          mpFirstBlockSlot(0), mpEnd(0), mpLastBlock(0), mpLastBlockEnd(0), mpLastBlockSlot(0)
    {
        init(nCount);
    }
    void init(uint32_t nCount);         // 0x00ca09f0
    void destroy();                     // 0x00abf900
    void pop_back();                    // 0x00abf980
    int32_t size() const
    {
        return ((int32_t)(mpLastBlockSlot - mpFirstBlockSlot) - 1) * 64
             + (int32_t)(mpEnd - mpLastBlock)
             + (int32_t)(mpFirstBlockEnd - mpBegin);
    }
    cInteraction* back() const
    {
        cInteraction** ppSlot = mpEnd;
        cInteraction** ppLastBlock = mpLastBlock;
        cInteraction*** ppLastSlot = mpLastBlockSlot;
        if (ppSlot == ppLastBlock)
            ppSlot = ppLastSlot[-1] + 64;
        return ppSlot[-1];
    }
};

// ---------------------------------------------------------------------------------------------
// the interaction stack (vtable 0x01459b68)
// ---------------------------------------------------------------------------------------------
class cInteractionStack {
public:
    virtual ~cInteractionStack();                               // 0x00
    virtual void v04();                                         // 0x04
    virtual void v08();                                         // 0x08
    virtual void v0c();                                         // 0x0c
    virtual void v10();                                         // 0x10
    virtual void v14();                                         // 0x14
    virtual void v18();                                         // 0x18
    virtual void v1c();                                         // 0x1c
    virtual cInteraction* v20();                                // 0x20
    virtual void v24();                                         // 0x24
    virtual cInteraction* v28();                                // 0x28
    virtual void v2c();                                         // 0x2c
    virtual void v30();                                         // 0x30
    virtual void v34();                                         // 0x34
    virtual int32_t v38();                                      // 0x38
    virtual void v3c();                                         // 0x3c
    virtual void v40(void* pOwner);                             // 0x40
    virtual void v44(AgentFilterRange range);                   // 0x44
    virtual void v48();                                         // 0x48
    virtual void v4c(bool bFlag);                               // 0x4c
    virtual void v50();                                         // 0x50
    virtual void v54();                                         // 0x54
    virtual void v58();                                         // 0x58
    virtual void v5c();                                         // 0x5c
    virtual void v60();                                         // 0x60

    bool  mb04;                     // +0x04
    tBlockVector16 mNames;          // +0x08
    uint32_t mPad30;                // +0x30
    tBlockVector4 mObjects;         // +0x34
    uint32_t mPad5c;                // +0x5c
    uint32_t mPad60;                // +0x60
    bool  mb64;                     // +0x64
    bool  mb65;                     // +0x65

    cInteractionStack();
    void SetFlag(bool bFlag);               // 0x00abfee0
    void SetUnknownFlag();                  // 0x00abf6f0
    void NotifyBehaviorManager();           // 0x00abf710
    void v20Call(void* pA1, void* pA2, void* pA3);  // 0x00abf760
    void v24Call(void* pA1, void* pA2, void* pA3);  // 0x00abf790
    void Forward(void* pObject);            // 0x00abf7c0
    void* GetInner1c();                     // 0x00abf7e0
    void* GetInner1cFrom28();               // 0x00abf800
    bool  HasPositive38();                  // 0x00abf820
    bool  SwapFlag(bool bFlag);             // 0x00abf850
    cInteraction* FindActive();             // 0x00abf890
    cInteraction* GetTop();                 // 0x00abfbb0
    void  AppendTrace(void* pString);       // 0x00abfbe0
    void  NotifyAll();                      // 0x00abfac0
    void  Remove(cInteraction* pInteraction); // 0x00ac00a0
    int32_t Count();                        // 0x00abf860
};

// ---------------------------------------------------------------------------------------------
// cInteraction: the two ref-counted bases (vtables 0x01459ad8 / 0x01459ac4), the target and
// agent slot lists, the variable map and the behaviour state
// ---------------------------------------------------------------------------------------------
struct tRBNode {
    tRBNode* mpNodeRight;   // +0x00
    tRBNode* mpNodeLeft;    // +0x04
    tRBNode* mpNodeParent;  // +0x08
    uint32_t mColor;        // +0x0c
};

struct tPairNode : tRBNode {
    uint32_t mKey;          // +0x10
    uint32_t mValue;        // +0x14
};

class tVarMap {                         // eastl::map<unsigned, unsigned>: 0x1c bytes
public:
    uint32_t mPad00;                    // +0x00 (never written by the constructor)
    tRBNode  mAnchor;                   // +0x04 (right +0x04, left +0x08, parent +0x0c, color +0x10)
    uint32_t mnSize;                    // +0x14
    uint8_t  mAllocator;                // +0x18

    void Init()
    {
        mAnchor.mpNodeLeft = 0;
        mAnchor.mpNodeParent = 0;
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
    void DoNukeSubtree(tRBNode* pNode);                 // 0x009a9600
    tPairNode* Lookup(const uint32_t* pKey);            // 0x00ac0010
    tRBNode* InsertValue(const void* pValue, tRBNode* pPosition, void* pArg, bool bFlag); // 0x00abff10
};

struct tIUnknown {
    virtual ~tIUnknown() {}                                     // 0x00 (vtable 0x013eb938)
    virtual void v04();                                         // 0x04
    virtual void v08();                                         // 0x08
    virtual void v0c();                                         // 0x0c
    virtual void v10();                                         // 0x10
    virtual const char* GetName();                              // 0x14
    virtual void v18();                                         // 0x18
    virtual void* v1c();                                        // 0x1c
    virtual tAgentInterface* v20();                             // 0x20
    virtual void v24();                                         // 0x24
    virtual tAgentInterface* v28();                             // 0x28
    virtual void v2c();                                         // 0x2c
    virtual void v30();                                         // 0x30
    virtual void v34();                                         // 0x34
    virtual int32_t v38();                                      // 0x38
    virtual void v3c();                                         // 0x3c
    virtual void v40(void* pOwner);                             // 0x40
    virtual void v44(AgentFilterRange range);                   // 0x44
    virtual void v48();                                         // 0x48
    virtual void v4c(bool bFlag);                               // 0x4c
    virtual void v50();                                         // 0x50
    virtual void v54();                                         // 0x54
    virtual void v58();                                         // 0x58
    virtual void v5c();                                         // 0x5c
    virtual void v60();                                         // 0x60
};

struct tRefCount {                                              // vtable 0x013ec458
    tRefCount() : mnRefCount(0) {}
    virtual ~tRefCount() {}                                     // 0x00
    virtual void AddRef();                                      // 0x04
    int32_t mnRefCount;                                         // +0x04 (absolute +0x08)
};

class cInteraction : public tIUnknown, public tRefCount {
public:
    tSlotVector<cInteractionTarget> mTargets;   // +0x0c
    tSlotVector<cInteractionAgent>  mAgents;    // +0x2c
    tVarMap        mVarMap;                     // +0x4c
    int32_t        mn68;                        // +0x68
    int32_t        mn6c;                        // +0x6c
    int32_t        mn70;                        // +0x70

    cInteraction();
    virtual ~cInteraction();
    void* GetFirstAgent();                                          // 0x00abf0b0
    AgentFilterRange* FindAgent(AgentFilterRange* pRange, cInteractionAgent* pAgent); // 0x00abf110
    cInteractionAgent* GetAgent();                                  // 0x00abf210
    void  AgentBackFromInterruption(cInteractionAgent* pAgent, int32_t nFlags); // 0x00abf240
    bool  AddAgent(cInteractionAgent* pAgent);                      // 0x00abf640
    bool  AddTarget(cInteractionTarget* pTarget);                   // 0x00abf6a0
};

struct tBehaviorManager {
    virtual void v00();                                         // 0x00
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20(void* pA1, void* pThis, void* pA2, void* pA3);   // 0x20
    virtual void v24(void* pA1, void* pThis, void* pA2, void* pA3);   // 0x24
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c(void* pAgent);                             // 0x3c
};

// @ 0x00abf0b0
void* cInteraction::GetFirstAgent()
{
    IsAgentActive filter(this, false);
    AgentFilterRange range;
    range.Init(&mAgents, &filter);
    if (range.mBegin != range.mEnd)
        return range.mBegin.At(range.mBegin.mnIndex)->mpPayload;
    return 0;
}

// @ 0x00abf110
AgentFilterRange* cInteraction::FindAgent(AgentFilterRange* pRange, cInteractionAgent* pAgent)
{
    IsAgentActive filter(0, false);
    pRange->Init(&mAgents, &filter);
    while (pRange->mBegin != pRange->mEnd)
    {
        if (pRange->mBegin.At(pRange->mBegin.mnIndex)->mpPayload == pAgent)
            break;
        pRange->Advance();
    }
    return pRange;
}

// @ 0x00abf190
cInteraction::~cInteraction()
{
    mVarMap.DoNukeSubtree(mVarMap.mAnchor.mpNodeParent);
    mAgents.Destroy(this);
    if (mAgents.mpDir != 0)
        operator_delete_array(mAgents.mpDir);
    mTargets.Destroy(this);
    if (mTargets.mpDir != 0)
        operator_delete_array(mTargets.mpDir);
}

// @ 0x00abf210
cInteractionAgent* cInteraction::GetAgent()
{
    return mAgents.mnLowWater != kFreeSentinel
         ? mAgents.At(mAgents.mnLowWater)->mpPayload
         : 0;
}

// @ 0x00abf240
void cInteraction::AgentBackFromInterruption(cInteractionAgent* pAgent, int32_t nFlags)
{
    if (pAgent != 0)
    {
        AgentFilterRange range;
        FindAgent(&range, pAgent);
        uint32_t nEnd = (uint32_t)range.mEnd.mpVector + range.mEnd.mnIndex;
        uint32_t nBegin = (uint32_t)range.mBegin.mpVector + range.mBegin.mnIndex;
        if (nBegin != nEnd)
            v44(range);
    }
}

// @ 0x00abf320
cInteraction::cInteraction()
{
    mTargets.Init();
    mAgents.Init();
    mVarMap.Init();
    mn68 = 0;
    mn6c = 0;
    mn70 = 1;
}

// @ 0x00abf3c0
template <>
uint32_t tSlotVector<cInteractionTarget>::Insert(cInteractionTarget* const& pObject_t)
{
    uint32_t nIndex = mnFreeHead;
    if (nIndex == kFreeSentinel)
    {
        cInteractionTarget* pData = pObject_t;
        if (pData != 0)
            pData->AddRef();
        nIndex = Size();
        Grow();
        At(nIndex - 1)->mnFlags &= kClearMask;
        At(nIndex)->mnFlags |= kInUseFlag;
        At(nIndex)->mnFlags &= kKeepFlag;
        At(nIndex)->mpPayload = pData;
        if (pData != 0)
            pData->AddRef();
        if (pData != 0)
            pData->Release();
    }
    else
    {
        mnFreeHead = At(nIndex)->mnFlags & kLinkMask;
        At(nIndex)->mnFlags &= kKeepFlag;
        At(nIndex)->mpPayload = pObject_t;
        if (pObject_t != 0)
            pObject_t->AddRef();
    }
    if (mnLowWater > nIndex)
        mnLowWater = nIndex;
    return nIndex;
}

// @ 0x00abf500
template <>
uint32_t tSlotVector<cInteractionAgent>::Insert(cInteractionAgent* const& pObject_t)
{
    uint32_t nIndex = mnFreeHead;
    if (nIndex == kFreeSentinel)
    {
        cInteractionAgent* pData = pObject_t;
        if (pData != 0)
            pData->v60();
        nIndex = Size();
        Grow();
        At(nIndex - 1)->mnFlags &= kClearMask;
        At(nIndex)->mnFlags |= kInUseFlag;
        At(nIndex)->mnFlags &= kKeepFlag;
        At(nIndex)->mpPayload = pData;
        if (pData != 0)
            pData->v60();
        if (pData != 0)
            pData->v5c();
    }
    else
    {
        mnFreeHead = At(nIndex)->mnFlags & kLinkMask;
        At(nIndex)->mnFlags &= kKeepFlag;
        At(nIndex)->mpPayload = pObject_t;
        if (pObject_t != 0)
            pObject_t->v60();
    }
    if (mnLowWater > nIndex)
        mnLowWater = nIndex;
    return nIndex;
}

// @ 0x00abf640
bool cInteraction::AddAgent(cInteractionAgent* pAgent)
{
    if (pAgent != 0)
    {
        if (!FUN_00abece0(&mAgents, &pAgent))
        {
            pAgent->v60();
            mAgents.Insert(pAgent);
            pAgent->v5c();
            pAgent->v3c(this, 0);
        }
        return true;
    }
    return false;
}

// @ 0x00abf6a0
bool cInteraction::AddTarget(cInteractionTarget* pTarget)
{
    if (pTarget != 0)
    {
        pTarget->AddRef();
        mTargets.Insert(pTarget);
        pTarget->Release();
        pTarget->Attach(this);
        return true;
    }
    return false;
}

// @ 0x00abf6f0
void cInteractionStack::SetUnknownFlag()
{
    v4c(!mb04);
}

// @ 0x00abf710
void cInteractionStack::NotifyBehaviorManager()
{
    v34();
    if (SP_BehaviorManager() != 0)
        ((tBehaviorManager*)SP_BehaviorManager())->v3c(this);
}

// @ 0x00abf760
void cInteractionStack::v20Call(void* pA1, void* pA2, void* pA3)
{
    ((tBehaviorManager*)SP_BehaviorManager())->v20(pA1, this, pA2, pA3);
}

// @ 0x00abf790
void cInteractionStack::v24Call(void* pA1, void* pA2, void* pA3)
{
    ((tBehaviorManager*)SP_BehaviorManager())->v24(pA1, this, pA2, pA3);
}

// @ 0x00abf7c0
void cInteractionStack::Forward(void* pObject)
{
    ((tAgentInterface*)pObject)->v40(this);
}

// @ 0x00abf7e0
void* cInteractionStack::GetInner1c()
{
    cInteraction* pObject = v20();
    if (pObject != 0)
        return pObject->v1c();
    return 0;
}

// @ 0x00abf800
void* cInteractionStack::GetInner1cFrom28()
{
    cInteraction* pObject = v28();
    if (pObject != 0)
        return pObject->v1c();
    return 0;
}

// @ 0x00abf820
bool cInteractionStack::HasPositive38()
{
    return v38() > 0;
}

// @ 0x00abf850
bool cInteractionStack::SwapFlag(bool bFlag)
{
    bool bOld = mb64;
    mb64 = bFlag;
    return bOld;
}

// @ 0x00abf860
int32_t cInteractionStack::Count()
{
    return mObjects.size();
}

// @ 0x00abf890
cInteraction* cInteractionStack::FindActive()
{
    tBlockVector4& vec = mObjects;
    cInteraction** pSlot = vec.mpEnd;
    while (pSlot != vec.mpBegin)
    {
        cInteraction** pBlockEnd = vec.mpLastBlockEnd;
        cInteraction*** ppLastSlot = vec.mpLastBlockSlot;
        cInteraction** pCur = pSlot;
        if (pCur == vec.mpLastBlock)
            pCur = ppLastSlot[-1] + 64;
        cInteraction* pObject = pCur[-1];
        if (pObject->mn6c != 0)
            return pObject;
        if (pSlot == vec.mpLastBlock)
        {
            vec.mpLastBlock = ppLastSlot[-1];
            vec.mpLastBlockSlot = ppLastSlot - 1;
            vec.mpLastBlockEnd = vec.mpLastBlock + 64;
            pSlot = vec.mpLastBlockEnd;
        }
        --pSlot;
    }
    return 0;
}

// @ 0x00abf900
void tBlockVector4::destroy()
{
    cInteraction** ppSlot = mpBegin;
    cInteraction** ppBlockEnd = mpFirstBlockEnd;
    cInteraction*** ppBlockSlot;
    ppBlockSlot = mpFirstBlockSlot;
    while (ppSlot != mpEnd)
    {
        if (*ppSlot != 0)
            (*ppSlot)->v04();
        ++ppSlot;
        if (ppSlot == ppBlockEnd)
        {
            ++ppBlockSlot;
            ppSlot = *ppBlockSlot;
            ppBlockEnd = ppSlot + 64;
        }
    }
    if (mpDir != 0)
    {
        cInteraction*** ppEndSlot = mpLastBlockSlot + 1;
        for (ppBlockSlot = mpFirstBlockSlot; ppBlockSlot < ppEndSlot; ++ppBlockSlot)
        {
            cInteraction** ppBlock = *ppBlockSlot;
            if (ppBlock != 0)
                operator_delete_array(ppBlock);
        }
        cInteraction*** ppDir = mpDir;
        if (ppDir != 0)
            operator_delete_array(ppDir);
    }
}

// @ 0x00abf980
void tBlockVector4::pop_back()
{
    if (mpEnd != mpLastBlock)
    {
        cInteraction** ppSlot = mpEnd - 1;
        mpEnd = ppSlot;
        if (*ppSlot != 0)
            (*ppSlot)->v04();
        return;
    }
    if (mpLastBlock != 0)
        operator_delete_array(mpLastBlock);
    cInteraction*** ppLastSlot = mpLastBlockSlot - 1;
    mpLastBlockSlot = ppLastSlot;
    mpLastBlock = *ppLastSlot;
    mpLastBlockEnd = mpLastBlock + 64;
    cInteraction** ppSlot = mpLastBlockEnd - 1;
    mpEnd = ppSlot;
    if (*ppSlot != 0)
        (*ppSlot)->v04();
}

// @ 0x00abf9e0
void tBlockVector16::init(uint32_t nCount)
{
    uint32_t nBlocks = (nCount >> 4) + 1;
    uint32_t nBlockCount = nBlocks + 2;
    if (nBlockCount <= 8)
        nBlockCount = 8;
    mnBlockCount = nBlockCount;
    mpDir = (tWideStringSlot**)operator_new(nBlockCount * 4, g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
    tWideStringSlot** ppFirst = mpDir + ((mnBlockCount - nBlocks) >> 1);
    tWideStringSlot** ppLast = ppFirst + nBlocks;
    for (tWideStringSlot** ppSlot = ppFirst; ppSlot < ppLast; ++ppSlot)
        *ppSlot = (tWideStringSlot*)operator_new(0x100, g_szSimulator, 0, 0, g_szEastlFile, 0xd1);
    mpFirstBlockSlot = ppFirst;
    mpFirstBlock = *ppFirst;
    mpFirstBlockEnd = mpFirstBlock + 16;
    mpBegin = mpFirstBlock;
    mpLastBlockSlot = ppLast - 1;
    mpLastBlock = *mpLastBlockSlot;
    mpLastBlockEnd = mpLastBlock + 16;
    mpEnd = mpLastBlock + (nCount & 0xf);
}

// @ 0x00abfac0
void cInteractionStack::NotifyAll()
{
    cInteraction* pCurrent = 0;
    while (mObjects.size() != 0)
    {
        cInteraction* pObject = v20();
        if (pObject != pCurrent)
        {
            if (pObject != 0)
                pObject->v04();
            cInteraction* pOld = pCurrent;
            pCurrent = pObject;
            if (pOld != 0)
                pOld->v04();
        }
        AgentFilterRange range;
        pCurrent->FindAgent(&range, (cInteractionAgent*)this);
        if (range.mBegin != range.mEnd)
            pCurrent->v44(range);
    }
    if (pCurrent != 0)
        pCurrent->v04();
}

// @ 0x00abfbb0
cInteraction* cInteractionStack::GetTop()
{
    if (v38() > 0)
        return mObjects.back();
    return 0;
}

// @ 0x00abfbe0
void cInteractionStack::AppendTrace(void* pString)
{
    FUN_00454cb0(pString, g_szStackHeader, g_szEmptyText);
    tBlockVector4& vec = mObjects;
    cInteraction** pSlot = vec.mpEnd;
    cInteraction** pBlockEnd = vec.mpLastBlockEnd;
    cInteraction** pLastBlock = vec.mpLastBlock;
    cInteraction*** ppLastSlot = vec.mpLastBlockSlot;
    cInteraction** pFirst = vec.mpBegin;
    uint32_t nShown = 0;
    while (pSlot != pFirst)
    {
        cInteraction** pCur = pSlot;
        if (pCur == pLastBlock)
            pCur = ppLastSlot[-1] + 64;
        const char* pszName = pCur[-1]->GetName();
        FUN_005f9450(pString, g_szPtrLine, pszName);
        if (++nShown >= 3)
        {
            FUN_005f9450(pString, g_szDots);
            return;
        }
        if (pSlot == pLastBlock)
        {
            pLastBlock = ppLastSlot[-1];
            --ppLastSlot;
            pBlockEnd = pLastBlock + 64;
            pSlot = pBlockEnd;
        }
        --pSlot;
    }
}

// @ 0x00abfcb0
void tBlockVector16::destroy()
{
    tWideStringSlot* pSlot = mpBegin;
    tWideStringSlot* pBlockEnd = mpFirstBlockEnd;
    tWideStringSlot** ppBlockSlot = mpFirstBlockSlot;
    while (pSlot != mpEnd)
    {
        if (pSlot->mpCapacity - pSlot->mpBegin > 1 && pSlot->mpBegin != 0)
            operator_delete_array(pSlot->mpBegin);
        ++pSlot;
        if (pSlot == pBlockEnd)
        {
            ++ppBlockSlot;
            pSlot = *ppBlockSlot;
            pBlockEnd = pSlot + 16;
        }
    }
    if (mpDir != 0)
    {
        for (ppBlockSlot = mpFirstBlockSlot; ppBlockSlot < mpLastBlockSlot + 1; ++ppBlockSlot)
        {
            if (*ppBlockSlot != 0)
                operator_delete_array(*ppBlockSlot);
        }
        operator_delete_array(mpDir);
    }
}

// @ 0x00abfd40
void tBlockVector16::clear()
{
    if (mpFirstBlockSlot == mpLastBlockSlot)
    {
        for (tWideStringSlot* pSlot = mpBegin; pSlot < mpEnd; ++pSlot)
        {
            if (pSlot->mpCapacity - pSlot->mpBegin > 1 && pSlot->mpBegin != 0)
                operator_delete_array(pSlot->mpBegin);
        }
    }
    else
    {
        for (tWideStringSlot* pSlot = mpBegin; pSlot < mpFirstBlockEnd; ++pSlot)
        {
            if (pSlot->mpCapacity - pSlot->mpBegin > 1 && pSlot->mpBegin != 0)
                operator_delete_array(pSlot->mpBegin);
        }
        for (tWideStringSlot* pSlot = mpLastBlock; pSlot < mpEnd; ++pSlot)
        {
            if (pSlot->mpCapacity - pSlot->mpBegin > 1 && pSlot->mpBegin != 0)
                operator_delete_array(pSlot->mpBegin);
        }
        if (mpLastBlock != 0)
            operator_delete_array(mpLastBlock);
    }
    for (tWideStringSlot** ppBlockSlot = mpFirstBlockSlot + 1; ppBlockSlot < mpLastBlockSlot; ++ppBlockSlot)
    {
        tWideStringSlot* pBlock = *ppBlockSlot;
        for (tWideStringSlot* pSlot = pBlock; pSlot < pBlock + 16; ++pSlot)
        {
            if (pSlot->mpCapacity - pSlot->mpBegin > 1 && pSlot->mpBegin != 0)
                operator_delete_array(pSlot->mpBegin);
        }
        if (pBlock != 0)
            operator_delete_array(pBlock);
    }
    mpEnd = mpBegin;
    mpLastBlock = mpFirstBlock;
    mpLastBlockEnd = mpFirstBlockEnd;
    mpLastBlockSlot = mpFirstBlockSlot;
}

// @ 0x00abfe50
cInteractionStack::cInteractionStack()
    : mb04(false), mNames(0), mObjects(0), mb64(false), mb65(true)
{
}

// @ 0x00abfec0
cInteractionStack::~cInteractionStack()
{
    mObjects.destroy();
    mNames.destroy();
}

// @ 0x00abfee0
void cInteractionStack::SetFlag(bool bFlag)
{
    if (!g_bStackReady)
        g_bStackReady = false;
    mb04 = bFlag;
    if (!bFlag)
        mNames.clear();
}

// @ 0x00ac0010
tPairNode* tVarMap::Lookup(const uint32_t* pKey)
{
    tPairNode* pNode = (tPairNode*)mAnchor.mpNodeParent;
    tPairNode* pPosition = (tPairNode*)&mAnchor;
    while (pNode != 0)
    {
        if (pNode->mKey >= *pKey)
        {
            pPosition = pNode;
            pNode = (tPairNode*)pNode->mpNodeLeft;
        }
        else
        {
            pNode = (tPairNode*)pNode->mpNodeRight;
        }
    }
    if (pPosition != (tPairNode*)&mAnchor && *pKey >= pPosition->mKey)
        return (tPairNode*)pPosition;
    uint32_t pair[3];
    pair[0] = *pKey;
    pair[1] = 0;
    pair[2] = 0;
    return (tPairNode*)InsertValue(pair, pPosition, 0, false);
}

// @ 0x00ac00a0
void cInteractionStack::Remove(cInteraction* pInteraction)
{
    if (v20() != pInteraction)
        return;
    cInteraction* pTop = mObjects.back();
    if (pTop != 0)
        pTop->v04();
    mObjects.pop_back();
    if (mObjects.size() != 0)
    {
        cInteraction* pNext = mObjects.back();
        if (pNext != 0)
            pNext->v04();
        uint32_t nKey = (uint32_t)this;
        pNext->mVarMap.Lookup(&nKey)->mValue = 0;
        pNext->v38();
        pNext->v04();
    }
    if (pTop != 0)
        pTop->v04();
}
