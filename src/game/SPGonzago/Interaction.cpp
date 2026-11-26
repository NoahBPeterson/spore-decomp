// src/game/SPGonzago/Interaction.cpp -- migrated from slice(s) s00abf0b0, s00abe110 by tools/migrate/rewrite.py
// Object file: SPGonzago/Interaction.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteraction.h"
#include "SP/cInteractionAgent.h"
#include "SP/cInteractionTarget.h"
#include <math.h>

// ---- items of slice s00abe110 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
#pragma pack(push, 4)
typedef unsigned int u32;
typedef unsigned char u8;
#define NOINLINE __declspec(noinline)
struct SlotEntry {
  u32 mMeta;   // bit31 = free, bit30 = end sentinel, bits0..29 = next free slot
  void* mpData;
};
struct SlotBlock {
  SlotEntry mEntries[128];
};
struct SlotVector_s00ab_e110;
struct SlotIter_s00ab_e110 {
  SlotVector_s00ab_e110* mpOwner;
  u32 mIndex;
  void increment();  // 0x00abe9b0 (SlotIter::increment)
};
struct SlotVector;
struct SlotIter {
  SlotVector* mpOwner;
  u32 mIndex;
  SlotIter& increment();
};
static const u32 kSlotEmpty = 0x3fffffff;
int __cdecl SlotDistance(SlotIter_s00ab_e110 first, SlotIter_s00ab_e110 last);
struct SlotVector_s00ab_e110 {
  SlotBlock** mpBegin;   // +0x00
  SlotBlock** mpEnd;     // +0x04
  void* mpField08;       // +0x08
  void* mpField0c;       // +0x0c
  void* mpField10;       // +0x10
  u32 mEndSlot;          // +0x14
  u32 mBeginIndex;       // +0x18
  u32 mFreeHead;         // +0x1c

  SlotEntry* entry(u32 i) { return &mpBegin[i >> 7]->mEntries[i & 0x7f]; }
  u32 endIndex() {
    return (u32)((mpEnd - mpBegin) * 128) + mEndSlot - 0x7f;
  }
  u32 nextAllocated(u32 i);
  void freeTarget(u32 i);  // 0x00abe8f0 (SlotVector::freeTarget)
  void freeAgent(u32 i);  // 0x00abe950 (SlotVector::freeAgent)
  SlotIter_s00ab_e110 begin();  // 0x00abeaf0 (SlotVector::begin)
  SlotIter_s00ab_e110 end() {
    SlotIter_s00ab_e110 it;
    it.mpOwner = this;
    it.mIndex = endIndex();
    return it;
  }
  void destroyTargets(int freeMem);  // 0x00abec00 (SlotVector::destroyTargets)
  void destroyAgents(int freeMem);  // 0x00abec70 (SlotVector::destroyAgents)
  int size();  // 0x00abefd0 (SlotVector::size)
};
struct SlotVector {
  SlotBlock** mpBegin;   // +0x00
  SlotBlock** mpEnd;     // +0x04
  void* mpField08;       // +0x08
  void* mpField0c;       // +0x0c
  void* mpField10;       // +0x10
  u32 mEndSlot;          // +0x14
  u32 mBeginIndex;       // +0x18
  u32 mFreeHead;         // +0x1c

  SlotEntry* entry(u32 i) { return &mpBegin[i >> 7]->mEntries[i & 0x7f]; }
  u32 endIndex() {
    return (u32)((mpEnd - mpBegin) * 128) + mEndSlot - 0x7f;
  }
  u32 nextAllocated(u32 i);
  void freeTarget(u32 i);
  void freeAgent(u32 i);
  SlotIter begin();
  SlotIter end() {
    SlotIter it;
    it.mpOwner = this;
    it.mIndex = endIndex();
    return it;
  }
  void destroyTargets(int freeMem);
  void destroyAgents(int freeMem);
  int size();
};
struct BlockAllocator {
  void release(SlotBlock* block);
};
struct cInteractionTarget {
  virtual void t00();
  virtual void t04();
  virtual void t08(void*);
  virtual void t0c();
  virtual void t10();
  virtual void t14();
  virtual void t18();
};
struct cInteractionAgent {
  virtual void a00();
  virtual void a04();
  virtual void a08();
  virtual void a0c();
  virtual void a10();
  virtual void a14();
  virtual void a18();
  virtual void a1c();
  virtual void* a20();
  virtual void a24();
  virtual void a28();
  virtual void a2c();
  virtual void a30(void*);
  virtual void a34();
  virtual void a38();
  virtual void a3c();
  virtual void a40();
  virtual void a44();
  virtual void a48();
  virtual void a4c();
  virtual void a50();
  virtual void a54();
  virtual void a58();
  virtual void a5c();
};
struct cInteraction_s00ab_e110;
struct cInteraction;
struct cInteractionAgent;
struct cAgentData {
  int mState;           // +0x00
  u32 mSleepTimeout;    // +0x04
};
struct AgentNode {
  AgentNode* mpLeft;        // +0x00
  AgentNode* mpRight;       // +0x04
  AgentNode* mpParent;      // +0x08
  u32 mColor;               // +0x0c
  cInteractionAgent* mpKey; // +0x10
  cAgentData mData;         // +0x14
};
struct AgentMap {
  void* mpField00;      // +0x00
  AgentNode* mpLeft;    // +0x04 (anchor)
  AgentNode* mpRight;   // +0x08
  AgentNode* mpRoot;    // +0x0c (anchor.parent)
  u32 mColor;           // +0x10
  u32 mSize;            // +0x14

  AgentNode* sentinel() { return (AgentNode*)&mpLeft; }
  AgentNode* lower_bound(cInteractionAgent* key) {
    AgentNode* node = mpRoot;
    AgentNode* candidate = sentinel();
    while (node) {
      if (node->mpKey < key) {
        node = node->mpLeft;
      } else {
        candidate = node;
        node = node->mpRight;
      }
    }
    if (candidate != sentinel() && key < candidate->mpKey) candidate = sentinel();
    return candidate;
  }
  AgentNode** find(AgentNode** out, cInteractionAgent* const& key);
  void erase(cInteractionAgent** key);
};
struct IsAgentActive_s00ab_e110 {
  cInteraction_s00ab_e110* mpOwner;  // +0x00
  u8 mCheckMap;           // +0x04
  u8 mPad05[3];
  bool evaluate(cInteractionAgent* agent);  // 0x00abea90 (IsAgentActive::evaluate)
};
struct AgentFilterRange {
  SlotIter_s00ab_e110 mBegin;        // +0x00
  SlotIter_s00ab_e110 mEnd;          // +0x08
  IsAgentActive_s00ab_e110 mPred;    // +0x10
  AgentFilterRange(SlotVector_s00ab_e110* v, IsAgentActive_s00ab_e110* pred);
  void advance();
};
struct IsAgentActive {
  cInteraction* mpOwner;  // +0x00
  u8 mCheckMap;           // +0x04
  u8 mPad05[3];
  int evaluate(cInteractionAgent* agent);
};
struct cInteractionVtbl {
  void* mSlots[24];
};
typedef bool (__thiscall* AddTargetFn)(cInteraction_s00ab_e110*, cInteractionTarget*);
typedef cInteractionTarget* (__thiscall* RemoveTargetFn)(cInteraction_s00ab_e110*, SlotIter_s00ab_e110*, SlotVector_s00ab_e110*, u32);
struct cInteraction_s00ab_e110 {
  cInteractionVtbl* mpVtbl;   // +0x00
  void* mpRefCount;           // +0x04
  u32 mPad08;                 // +0x08
  SlotVector_s00ab_e110 mTargetList;     // +0x0c
  SlotVector_s00ab_e110 mAgentList;      // +0x2c
  AgentMap mAgentData;        // +0x4c
  u32 mPad64;                 // +0x64
  int mInteractionType;       // +0x68
  int mInteractionDependency; // +0x6c
  int mInteractionState;      // +0x70

  bool IsAgentDefault(cInteractionAgent* agent);  // 0x00abea40 (cInteraction::IsAgentDefault)
  void SetTarget(cInteractionTarget* target);  // 0x00abed40 (cInteraction::SetTarget)
  void RemoveAgent(AgentFilterRange range);  // 0x00abedb0 (cInteraction::RemoveAgent)
  bool HasAgent(cInteractionAgent* agent);  // 0x00abee20 (cInteraction::HasAgent)
  bool HasTarget(cInteractionTarget* target);  // 0x00abeeb0 (cInteraction::HasTarget)
  SlotIter_s00ab_e110* RemoveTarget(SlotIter_s00ab_e110* out, SlotVector_s00ab_e110* vec, u32 index);  // 0x00abef40 (cInteraction::RemoveTarget)
};
struct cInteraction {
  cInteractionVtbl* mpVtbl;   // +0x00
  void* mpRefCount;           // +0x04
  u32 mPad08;                 // +0x08
  SlotVector mTargetList;     // +0x0c
  SlotVector mAgentList;      // +0x2c
  AgentMap mAgentData;        // +0x4c
  u32 mPad64;                 // +0x64
  int mInteractionType;       // +0x68
  int mInteractionDependency; // +0x6c
  int mInteractionState;      // +0x70

  bool IsAgentDefault(cInteractionAgent* agent);
  void SetTarget(cInteractionTarget* target);
  void RemoveAgent(AgentFilterRange range);
  bool HasAgent(cInteractionAgent* agent);
  bool HasTarget(cInteractionTarget* target);
  SlotIter* RemoveTarget(SlotIter* out, SlotVector* vec, u32 index);
};
struct cInteractionTarget;
SlotIter_s00ab_e110* __cdecl FUN_00ac03f0(SlotIter_s00ab_e110* out, SlotVector_s00ab_e110* a, u32 ai, SlotVector_s00ab_e110* b, u32 bi, void* value);
// ---- items of slice s00abe110 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern BlockAllocator* g_pAllocator_16c8b44;

// ---- items of slice s00abf0b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl operator_delete_array(void* pBlock);                                                          // 0x00f47380
bool  __cdecl FUN_00abece0(void* pVector, void* ppObject);       // 0x00abece0 slot vector contains
struct AgentFilterRange_s00ab_f0b0;
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
struct cInteractionAgent_s00ab_f0b0;
struct IsAgentActive_s00ab_f0b0 {
    void* m_pInteraction;   // +0x00
    bool  m_bFlag;          // +0x04

    IsAgentActive_s00ab_f0b0(void* pInteraction = 0, bool bFlag = false)
        : m_pInteraction(pInteraction), m_bFlag(bFlag) {}
};
struct SlotIterator {
    tSlotVector<cInteractionAgent_s00ab_f0b0>* mpVector;   // +0x00
    uint32_t mnIndex;                           // +0x04

    bool operator!=(const SlotIterator& other) const
    {
        return (uint32_t)mpVector + mnIndex != (uint32_t)other.mpVector + other.mnIndex;
    }
    tSlotEntry<cInteractionAgent_s00ab_f0b0>* At(uint32_t nIndex) const
    {
        return mpVector->At(nIndex);
    }
};
struct AgentFilterRange_s00ab_f0b0 {
    SlotIterator  mBegin;       // +0x00
    SlotIterator  mEnd;         // +0x08
    void*         mpOwner;      // +0x10
    bool          mbOwnerFlag;  // +0x14

    void Init(tSlotVector<cInteractionAgent_s00ab_f0b0>* pVector, const IsAgentActive_s00ab_f0b0* pFilter); // 0x00abf010
    void Advance();                                                                   // 0x00abeb20
};
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
    virtual void v44(AgentFilterRange_s00ab_f0b0 range);                   // 0x44
    virtual void v48();                                         // 0x48
    virtual void v4c(bool bFlag);                               // 0x4c
    virtual void v50();                                         // 0x50
    virtual void v54();                                         // 0x54
    virtual void v58();                                         // 0x58
    virtual void v5c();                                         // 0x5c
    virtual void v60();                                         // 0x60
};
struct cInteractionAgent_s00ab_f0b0 : tAgentInterface {
};
struct cInteractionTarget_s00ab_f0b0 {
    virtual void v00();                                         // 0x00
    virtual void v04();                                         // 0x04
    virtual void v08();                                         // 0x08
    virtual void Attach(void* pOwner);                          // 0x0c
    virtual void v10();                                         // 0x10
    virtual void Release();                                     // 0x14
    virtual void AddRef();                                      // 0x18
};
struct tWideStringSlot {                // 16-byte element of the stack name list
    wchar_t* mpBegin;                   // +0x00
    wchar_t* mpEnd;                     // +0x04
    wchar_t* mpCapacity;                // +0x08
    uint32_t mPad0c;                    // +0x0c
};
class cInteraction_s00ab_f0b0;
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
    cInteraction_s00ab_f0b0*** mpDir;              // +0x00
    uint32_t        mnBlockCount;       // +0x04
    cInteraction_s00ab_f0b0**  mpBegin;            // +0x08
    cInteraction_s00ab_f0b0**  mpFirstBlock;       // +0x0c
    cInteraction_s00ab_f0b0**  mpFirstBlockEnd;    // +0x10
    cInteraction_s00ab_f0b0*** mpFirstBlockSlot;   // +0x14
    cInteraction_s00ab_f0b0**  mpEnd;              // +0x18
    cInteraction_s00ab_f0b0**  mpLastBlock;        // +0x1c
    cInteraction_s00ab_f0b0**  mpLastBlockEnd;     // +0x20
    cInteraction_s00ab_f0b0*** mpLastBlockSlot;    // +0x24

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
    cInteraction_s00ab_f0b0* back() const
    {
        cInteraction_s00ab_f0b0** ppSlot = mpEnd;
        cInteraction_s00ab_f0b0** ppLastBlock = mpLastBlock;
        cInteraction_s00ab_f0b0*** ppLastSlot = mpLastBlockSlot;
        if (ppSlot == ppLastBlock)
            ppSlot = ppLastSlot[-1] + 64;
        return ppSlot[-1];
    }
};
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
    virtual cInteraction_s00ab_f0b0* v20();                                // 0x20
    virtual void v24();                                         // 0x24
    virtual cInteraction_s00ab_f0b0* v28();                                // 0x28
    virtual void v2c();                                         // 0x2c
    virtual void v30();                                         // 0x30
    virtual void v34();                                         // 0x34
    virtual int32_t v38();                                      // 0x38
    virtual void v3c();                                         // 0x3c
    virtual void v40(void* pOwner);                             // 0x40
    virtual void v44(AgentFilterRange_s00ab_f0b0 range);                   // 0x44
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
    cInteraction_s00ab_f0b0* FindActive();             // 0x00abf890
    cInteraction_s00ab_f0b0* GetTop();                 // 0x00abfbb0
    void  AppendTrace(void* pString);       // 0x00abfbe0
    void  NotifyAll();                      // 0x00abfac0
    void  Remove(cInteraction_s00ab_f0b0* pInteraction); // 0x00ac00a0
    int32_t Count();                        // 0x00abf860
};
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
    virtual void v44(AgentFilterRange_s00ab_f0b0 range);                   // 0x44
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
class cInteraction_s00ab_f0b0 : public tIUnknown, public tRefCount {
public:
    tSlotVector<cInteractionTarget_s00ab_f0b0> mTargets;   // +0x0c
    tSlotVector<cInteractionAgent_s00ab_f0b0>  mAgents;    // +0x2c
    tVarMap        mVarMap;                     // +0x4c
    int32_t        mn68;                        // +0x68
    int32_t        mn6c;                        // +0x6c
    int32_t        mn70;                        // +0x70

    cInteraction_s00ab_f0b0();  // 0x00abf320 (cInteraction::cInteraction_s00ab_f0b0)
    virtual ~cInteraction_s00ab_f0b0();  // 0x00abf320 (cInteraction::cInteraction_s00ab_f0b0)
    void* GetFirstAgent();                                          // 0x00abf0b0
    AgentFilterRange_s00ab_f0b0* FindAgent(AgentFilterRange_s00ab_f0b0* pRange, cInteractionAgent_s00ab_f0b0* pAgent); // 0x00abf110
    cInteractionAgent_s00ab_f0b0* GetAgent();                                  // 0x00abf210
    void  AgentBackFromInterruption(cInteractionAgent_s00ab_f0b0* pAgent, int32_t nFlags); // 0x00abf240
    bool  AddAgent(cInteractionAgent_s00ab_f0b0* pAgent);                      // 0x00abf640
    bool  AddTarget(cInteractionTarget_s00ab_f0b0* pTarget);                   // 0x00abf6a0
};
// ---- items of slice s00abf0b0 end

// @ 0x00abe8a0
u32 SlotVector_s00ab_e110::nextAllocated(u32 i)
{
  u32 m = entry(i)->mMeta;
  do {
    if ((m >> 30) & 1) return kSlotEmpty;
    ++i;
    m = entry(i)->mMeta;
  } while ((int)m < 0);
  return i;
}

// @ 0x00abe8f0
void SlotVector_s00ab_e110::freeTarget(u32 i)
{
  SlotEntry* e = entry(i);
  cInteractionTarget* p = (cInteractionTarget*)e->mpData;
  if (p) p->t14();
  e->mMeta = (mFreeHead & 0x3fffffff) | (e->mMeta & 0xc0000000) | 0x80000000;
  mFreeHead = i;
  if (mBeginIndex == i) mBeginIndex = nextAllocated(i);
}

// @ 0x00abe950
void SlotVector_s00ab_e110::freeAgent(u32 i)
{
  SlotEntry* e = entry(i);
  cInteractionAgent* p = (cInteractionAgent*)e->mpData;
  if (p) p->a5c();
  e->mMeta = (mFreeHead & 0x3fffffff) | (e->mMeta & 0xc0000000) | 0x80000000;
  mFreeHead = i;
  if (mBeginIndex == i) mBeginIndex = nextAllocated(i);
}

// @ 0x00abe9b0
NOINLINE SlotIter& SlotIter::increment()
{
  bool busy;
  do {
    u32 cur = mIndex++;
    bool done = ((mpOwner->entry(cur)->mMeta >> 30) & 1) != 0;
    if (done) return *this;
    busy = ((mpOwner->entry(mIndex)->mMeta >> 31) & 1) != 0;
  } while (busy);
  return *this;
}

// @ 0x00abea00
NOINLINE int __cdecl SlotDistance(SlotIter_s00ab_e110 first, SlotIter_s00ab_e110 last)
{  u32 end = last.mIndex + (u32)last.mpOwner;
  int n = 0;
  while (end != first.mIndex + (u32)first.mpOwner) {
    first.increment();
    ++n;
  }
  return n;
}

// @ 0x00abea40
bool cInteraction::IsAgentDefault(cInteractionAgent* agent)
{
  AgentNode* it;
  AgentNode* node = *mAgentData.find(&it, agent);
  if (node != mAgentData.sentinel())
    return node->mData.mState == 0 && node->mData.mSleepTimeout == 0;
  return false;
}

// @ 0x00abea90
int IsAgentActive::evaluate(cInteractionAgent* agent)
{
  cInteraction* owner = mpOwner;
  if (owner) {
    if (mCheckMap) {
      cInteractionAgent* key = agent;
      AgentNode* it;
      AgentNode* node = *owner->mAgentData.find(&it, key);
      if (node == owner->mAgentData.sentinel()) return true;
      if (node->mData.mState == 0) return true;
    }
    if (!owner->IsAgentDefault(agent)) return false;
  }
  return true;
}

// @ 0x00abeaf0
SlotIter SlotVector::begin()
{
  u32 i = mBeginIndex;
  if (i >= kSlotEmpty) i = endIndex();
  SlotIter it;
  it.mpOwner = this;
  it.mIndex = i;
  return it;
}

// @ 0x00abeb20
void AgentFilterRange::advance()
{
  for (;;) {
    mBegin.increment();
    if ((u32)mEnd.mpOwner + mEnd.mIndex == (u32)mBegin.mpOwner + mBegin.mIndex) return;
    cInteractionAgent* agent = (cInteractionAgent*)mBegin.mpOwner->entry(mBegin.mIndex)->mpData;
    cInteraction_s00ab_e110* owner = mPred.mpOwner;
    if (!owner) return;
    if (mPred.mCheckMap) {
      AgentNode* node = owner->mAgentData.lower_bound(agent);
      if (node == owner->mAgentData.sentinel()) return;
      if (node->mData.mState == 0) return;
    }
    AgentNode* node = owner->mAgentData.lower_bound(agent);
    if (node == owner->mAgentData.sentinel()) continue;
    if (node->mData.mState != 0) continue;
    if (node->mData.mSleepTimeout != 0) continue;
    return;
  }
}

// @ 0x00abec00
void SlotVector::destroyTargets(int freeMem)
{
  while (mpBegin != mpEnd) {
    SlotEntry* e = &mpEnd[-1]->mEntries[mEndSlot];
    u32 meta = e->mMeta;
    u8 free = (u8)(meta >> 31);
    if ((free & 1) == 0) {
      void* data = e->mpData;
      if (data) ((cInteractionTarget*)data)->t14();
    }
    if (mEndSlot == 0) {
      g_pAllocator_16c8b44->release(mpEnd[-1]);
      --mpEnd;
      mEndSlot = 0x7f;
    } else {
      --mEndSlot;
    }
  }
  (void)freeMem;
}

// @ 0x00abec70
void SlotVector::destroyAgents(int freeMem)
{
  while (mpBegin != mpEnd) {
    SlotEntry* e = &mpEnd[-1]->mEntries[mEndSlot];
    u32 meta = e->mMeta;
    u8 free = (u8)(meta >> 31);
    if ((free & 1) == 0) {
      void* data = e->mpData;
      if (data) ((cInteractionAgent*)data)->a5c();
    }
    if (mEndSlot == 0) {
      g_pAllocator_16c8b44->release(mpEnd[-1]);
      --mpEnd;
      mEndSlot = 0x7f;
    } else {
      --mEndSlot;
    }
  }
  (void)freeMem;
}

// @ 0x00abece0
bool __cdecl SlotVectorInsert(SlotVector_s00ab_e110* v, void* value)
{
  u32 end = v->endIndex();
  u32 begin = v->mBeginIndex;
  if (begin >= kSlotEmpty) begin = end;
  SlotIter_s00ab_e110 buf;
  SlotIter_s00ab_e110* it = FUN_00ac03f0(&buf, v, begin, v, end, value);
  return (u32)v + end != (u32)it->mpOwner + it->mIndex;
}

// @ 0x00abed40
void cInteraction_s00ab_e110::SetTarget(cInteractionTarget* target)
{
  if (mTargetList.mBeginIndex != kSlotEmpty) {
    do {
      u32 i = mTargetList.mBeginIndex;
      if (i >= kSlotEmpty) i = mTargetList.endIndex();
      SlotIter_s00ab_e110 out;
      ((RemoveTargetFn)mpVtbl->mSlots[20])(this, &out, &mTargetList, i);
    } while (mTargetList.mBeginIndex != kSlotEmpty);
  }
  ((AddTargetFn)mpVtbl->mSlots[19])(this, target);
}

// @ 0x00abedb0
void cInteraction_s00ab_e110::RemoveAgent(AgentFilterRange range)
{
  cInteractionAgent* p = (cInteractionAgent*)range.mBegin.mpOwner->entry(range.mBegin.mIndex)->mpData;
  if (p) {
    if ((cInteraction_s00ab_e110*)p->a20() == this) {
      mAgentList.freeAgent(range.mBegin.mIndex);
      mAgentData.erase(&p);
      p->a30(this);
    }
  }
}

// @ 0x00abee20
bool cInteraction_s00ab_e110::HasAgent(cInteractionAgent* agent)
{
  SlotVector_s00ab_e110* v = &mAgentList;
  SlotIter_s00ab_e110 it = v->begin();
  SlotIter_s00ab_e110 last = v->end();
  if ((u32)v + it.mIndex != (u32)v + last.mIndex) {
    do {
      if (v->entry(it.mIndex)->mpData == agent) return true;
      it.increment();
    } while ((u32)v + it.mIndex != (u32)v + last.mIndex);
  }
  return false;
}

// @ 0x00abeeb0
bool cInteraction_s00ab_e110::HasTarget(cInteractionTarget* target)
{
  SlotVector_s00ab_e110* v = &mTargetList;
  SlotIter_s00ab_e110 it = v->begin();
  SlotIter_s00ab_e110 last = v->end();
  if ((u32)v + it.mIndex != (u32)v + last.mIndex) {
    do {
      if (v->entry(it.mIndex)->mpData == target) return true;
      it.increment();
    } while ((u32)v + it.mIndex != (u32)v + last.mIndex);
  }
  return false;
}

// @ 0x00abef40
SlotIter_s00ab_e110* cInteraction_s00ab_e110::RemoveTarget(SlotIter_s00ab_e110* out, SlotVector_s00ab_e110* vec, u32 index)
{
  cInteractionTarget* p = (cInteractionTarget*)vec->entry(index)->mpData;
  if (p) {
    p->t18();
    mTargetList.freeTarget(index);
    SlotIter_s00ab_e110 it;
    it.mpOwner = vec;
    it.mIndex = index;
    it.increment();
    out->mpOwner = it.mpOwner;
    out->mIndex = it.mIndex;
    p->t08(this);
  } else {
    out->mpOwner = vec;
    out->mIndex = index;
  }
  if (p) p->t14();
  return out;
}

// @ 0x00abefd0
int SlotVector_s00ab_e110::size()
{
  u32 end = endIndex();
  u32 begin = mBeginIndex;
  if (begin >= kSlotEmpty) begin = end;
  typedef int(__cdecl * Distance5)(SlotVector_s00ab_e110*, u32, SlotVector_s00ab_e110*, u32, SlotVector_s00ab_e110*);
  return ((Distance5)SlotDistance)(this, begin, this, end, this);
}

// @ 0x00abf010
AgentFilterRange::AgentFilterRange(SlotVector_s00ab_e110* v, IsAgentActive_s00ab_e110* pred)
{
  mBegin.mIndex = v->mBeginIndex;
  if (mBegin.mIndex >= kSlotEmpty) mBegin.mIndex = v->endIndex();
  mBegin.mpOwner = v;
  mEnd.mIndex = v->endIndex();
  mEnd.mpOwner = v;
  mPred = *pred;
  if ((u32)mEnd.mpOwner + mEnd.mIndex != (u32)mBegin.mpOwner + mBegin.mIndex) {
    cInteractionAgent* agent = (cInteractionAgent*)mBegin.mpOwner->entry(mBegin.mIndex)->mpData;
    if (!mPred.evaluate(agent)) advance();
  }
}

// @ 0x00abf0b0
void* cInteraction_s00ab_f0b0::GetFirstAgent()
{
    IsAgentActive_s00ab_f0b0 filter(this, false);
    AgentFilterRange_s00ab_f0b0 range;
    range.Init(&mAgents, &filter);
    if (range.mBegin != range.mEnd)
        return range.mBegin.At(range.mBegin.mnIndex)->mpPayload;
    return 0;
}

// @ 0x00abf110
AgentFilterRange_s00ab_f0b0* cInteraction_s00ab_f0b0::FindAgent(AgentFilterRange_s00ab_f0b0* pRange, cInteractionAgent_s00ab_f0b0* pAgent)
{
    IsAgentActive_s00ab_f0b0 filter(0, false);
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
cInteraction_s00ab_f0b0::~cInteraction_s00ab_f0b0()
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
cInteractionAgent_s00ab_f0b0* cInteraction_s00ab_f0b0::GetAgent()
{
    return mAgents.mnLowWater != kFreeSentinel
         ? mAgents.At(mAgents.mnLowWater)->mpPayload
         : 0;
}

// @ 0x00abf240
void cInteraction_s00ab_f0b0::AgentBackFromInterruption(cInteractionAgent_s00ab_f0b0* pAgent, int32_t nFlags)
{
    if (pAgent != 0)
    {
        AgentFilterRange_s00ab_f0b0 range;
        FindAgent(&range, pAgent);
        uint32_t nEnd = (uint32_t)range.mEnd.mpVector + range.mEnd.mnIndex;
        uint32_t nBegin = (uint32_t)range.mBegin.mpVector + range.mBegin.mnIndex;
        if (nBegin != nEnd)
            v44(range);
    }
}

// @ 0x00abf320
cInteraction_s00ab_f0b0::cInteraction_s00ab_f0b0()
{
    mTargets.Init();
    mAgents.Init();
    mVarMap.Init();
    mn68 = 0;
    mn6c = 0;
    mn70 = 1;
}

// @ 0x00abf3c0
template <> uint32_t tSlotVector<cInteractionTarget_s00ab_f0b0>::Insert(cInteractionTarget_s00ab_f0b0* const& pObject_t)
{
    uint32_t nIndex = mnFreeHead;
    if (nIndex == kFreeSentinel)
    {
        cInteractionTarget_s00ab_f0b0* pData = pObject_t;
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
template <> uint32_t tSlotVector<cInteractionAgent_s00ab_f0b0>::Insert(cInteractionAgent_s00ab_f0b0* const& pObject_t)
{
    uint32_t nIndex = mnFreeHead;
    if (nIndex == kFreeSentinel)
    {
        cInteractionAgent_s00ab_f0b0* pData = pObject_t;
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
bool cInteraction_s00ab_f0b0::AddAgent(cInteractionAgent_s00ab_f0b0* pAgent)
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
bool cInteraction_s00ab_f0b0::AddTarget(cInteractionTarget_s00ab_f0b0* pTarget)
{
    if (pTarget != 0)
    {
        cInteractionTarget_s00ab_f0b0* pRef = pTarget;
        pRef->AddRef();
        mTargets.Insert(pRef);
        pTarget->Release();
        pTarget->Attach(this);
        return true;
    }
    return false;
}

// @ 0x00abfac0
void cInteractionStack::NotifyAll()
{
    cInteraction_s00ab_f0b0* pCurrent = 0;
    while (mObjects.size() != 0)
    {
        cInteraction_s00ab_f0b0* pObject = v20();
        if (pObject != pCurrent)
        {
            if (pObject != 0)
                pObject->v04();
            cInteraction_s00ab_f0b0* pOld = pCurrent;
            pCurrent = pObject;
            if (pOld != 0)
                pOld->v04();
        }
        AgentFilterRange_s00ab_f0b0 range;
        pCurrent->FindAgent(&range, (cInteractionAgent_s00ab_f0b0*)this);
        if (range.mBegin != range.mEnd)
            pCurrent->v44(range);
    }
    if (pCurrent != 0)
        pCurrent->v04();
}
