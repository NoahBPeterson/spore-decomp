// src/game/SPGonzago/_at_00ac0000.cpp -- migrated from slice(s) s00acc140, s00acb1b0, s00ac9f70, s00ac8d00, s00ac7ab0, s00ac0180, s00abf0b0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00ac0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cInteraction.h"
#include "SP/cInteractionTarget.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cGameNounManager.h"
#include <string.h>
#include <xmmintrin.h>

// ---- items of slice s00abf0b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct AgentFilterRange;
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
// ---- items of slice s00abf0b0 end

// ---- items of slice s00ac0180 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  __cdecl FUN_00401090(void*);              // 0x401090 GetSetting9
typedef unsigned int  u32;
typedef unsigned char u8;
typedef float* (__fastcall* GetVecFn)(void*);
extern "C" void* __cdecl operator_new(u32, const char*, int, int, int, int); // 0xf473a0
#define VTBL_01459c04  ((void*)0x1459c04)
#define VTBL_01459c20  ((void*)0x1459c20)
#define VTBL_01459c30  ((void*)0x1459c30)
#define VTBL_01459c6c  ((void*)0x1459c6c)
#define VTBL_01459c90  ((void*)0x1459c90)
#define VTBL_01459c98  ((void*)0x1459c98)
#define VBASE_01459be5 ((void*)0x1459be5)   // "Interaction History:\n"
#define VBASE_01459bd0 ((void*)0x1459bd0)
#define G_013eb960  (*(float*)0x13eb960)    // +0.01
#define G_0140ced4  (*(float*)0x140ced4)    // -0.01
#define G_01459c48  (*(float*)0x1459c48)    // +1.5258789e-05
#define G_013f89b8  (*(float*)0x13f89b8)    // -1.5258789e-05
#define G_1459c44   (*(float*)0x1459c44)    // FLT_MAX
#define STR_1459d0c ((const char*)0x1459d0c) // "Simulator/cAnimalCargoInfo"
struct SlotDeque {
    u8   mPad00[0x18];                              // +0x00
    int* mpBegin;                                   // +0x18
    int* mpEnd;                                     // +0x1c
    int* mpCapacity;                                // +0x20
    int* mpBlockBase;                               // +0x24
};
struct EntityArg;
struct InterObj {
    void*     mpVftable;                            // +0x00
    u8        mPad04[0x30];                         // +0x04
    SlotDeque mDeque;                               // +0x34

    bool FUN_00ac0180(EntityArg* arg, int unused);  // 0xac0180
};
struct EntityArg {
    u8  mPad00[0x6c];                               // +0x00
    int mf6c;                                       // +0x6c
};
struct SpeciesProfile {
    u8  mPad000[0x608];                             // +0x000
    int mf608;                                      // +0x608
    int mf60c;                                      // +0x60c
};
struct CargoItem {
    void*           mpVftable;                      // +0x00
    int             mnRefCount;                     // +0x04
    void*           mpHandlerVftable;               // +0x08
    void*           mpSerializableVftable;          // +0x0c
    int             mnItemCount;                    // +0x10
    int             mnItemType;                     // +0x14
    u8              mPad18[0x64];                   // +0x18
    SpeciesProfile* mpSpeciesProfile;               // +0x7c
};
struct ThiscallStub {
    void Object_Cast(int* entity);                  // 0xac0570
    int  FUN_00ac05d0(int classId);                 // 0xac05d0
    int* FUN_00ac06c0(float* pos, float a, float b); // 0xac06c0
    int  FUN_00ac0730(void* a, void* b);            // 0xac0730
    int  FUN_00ac0810(void* a, void* b);            // 0xac0810
    void FUN_00ac0bb0(void** out);                  // 0xac0bb0
    void FUN_00ac0e50(float* out);                  // 0xac0e50
    bool FUN_00ac0f40(void* stream);                // 0xac0f40
    bool FUN_00ac0fd0(void* stream);                // 0xac0fd0
    int* FUN_00ac1060(int arg2, int arg3);          // 0xac1060
    void* FUN_00ac10a0(void* arg1);                 // 0xac10a0
    void FUN_00c870b0(void* src);                   // 0xc870b0 operator=
};
struct InteractionTargetCtor {
    InterObj* ctor();                               // 0xac03d0
};
struct SlotMap {
    int* FUN_00ac0010(int** out);                   // 0xac0010
    void FUN_00c92bd0(int** out);                   // 0xc92bd0
};
// ---- items of slice s00ac0180 end

// ---- items of slice s00ac7ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  ReadBool(void* stream, int value);                       // 0x93ac80
extern "C" void  WriteBool3(void* stream, void* pValue, int one);         // 0x93a9a0
extern "C" void  WriteUint32(void* stream, void* pValue, int one, int zero); // 0x93aa70
extern "C" void  FUN_00693890(void* a, int b);                            // 0x693890
extern "C" void  FUN_00692e50(void* a, int b);                            // 0x692e50
struct Stream {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
    virtual void* s18();                       // +0x18
};
struct SerObj {
virtual void a00();
virtual void a04();
virtual void a08();
virtual void a0c();
virtual void a10();
virtual void a14();
virtual void a18();
virtual void a1c();
    virtual Stream* a20();                     // +0x20
};
struct IObj {                                  // +0x00 arg char, +0x18 ret ptr, +0x20 ret int
    virtual char  b00(void* v);
    virtual char  b04(void* v);
    virtual char  b08();
    virtual char  b0c(wchar_t* v);
    virtual void  b10();
    virtual void  b14();
    virtual void* b18();
    virtual void  b1c();
    virtual int   b20();
};
inline void* vs(void* p, int off) { return *(void**)((char*)*(void**)p + off); }
struct CVis {
    char  pad0[0xa4];
    void* mpA4;                 // +0xa4
    char  pad1[0xbc - 0xa8];
    void* mpBC;                 // +0xbc
    char  pad1b[0x12c - 0xc0];
    int   m12c;                 // +0x12c
    char  pad2[0x160 - 0x130];
    int   m160;                 // +0x160
    int*  FUN_00ac84d0(int which);
    void  FUN_00ac86b0(int v);
    void  FUN_00ac8130();
    void  FUN_00ac84f0(IObj* p);
    void  FUN_00ac8cd0(int a, int b);
};
struct RefPtr {
    void* mp;
    RefPtr* assign(void** src);
};
struct CAnim {
    void AddRef();     // 0xa02c30
    void Release();    // 0xa05270
};
// ---- items of slice s00ac7ab0 end

// ---- items of slice s00ac8d00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void operator_delete(void* p);                                    // 0xf47380
extern "C" void* FUN_006bb5d0(void);                          // 0x6bb5d0
extern int DAT_0164dc58;
extern "C" void SP_cVarListSerializer_ctor(void* self, void* a, void* b, int c);  // 0x692f90
extern "C" char SP_cVarListSerializer_Serialize(void* self, void* p);              // 0x692900
extern "C" void FUN_00695b40(void* a, void* b, const wchar_t* c);   // 0x695b40
extern "C" char FUN_00ac0730(void* a, void* b);               // 0xac0730
extern float DAT_0167a390, DAT_0167a394, DAT_0167a398;
extern int   DAT_01565ce0, DAT_01565ce4, DAT_01565ce8;
extern int   DAT_01565cec, DAT_01565cf0, DAT_01565cf8;
extern int   DAT_01565d54, DAT_01565d58, DAT_01565d5c, DAT_01565d60;
extern int   DAT_01565d00, DAT_01565d04, DAT_01565d08;
extern int   DAT_015d9c6c, DAT_015d9c68;
extern "C" void FUN_00ac9310(int a, int b, bool c);            // 0xac9310
typedef unsigned char  byte;
static inline void** VT(void* p) { return *(void***)p; }
struct RCObj {                       // refcounted, vtable slot0 AddRef, slot1 Release
    virtual void AddRef();
    virtual void Release();
};
struct NRef {                        // refcounted with *non-virtual* AddRef/Release (direct calls)
    void AddRef();                   // 0x00a02c30
    void Release();                  // 0x00a05270
};
struct Pair {                        // 0xc-byte element (vtable, byte, refcounted ptr)
    void* mpVtbl;                    // +0x00  (0x145a158)
    byte  mb4;                       // +0x04
    char  pad5[3];
    RCObj* mp8;                      // +0x08
};
struct CGVis { void SetCity(int c); };
struct CT {
    char  pad0[0x20];
    float* mpSphereBegin;     // +0x20
    float* mpSphereEnd;       // +0x24
    char  pad1[0xa4 - 0x28];
    void* mpA4;               // +0xa4
    char  pad2[0xbc - 0xa8];
    void* mpBC;               // +0xbc
    void  FUN_00ac8d00(int city, int a);
    void  FUN_00ac8d40(int a);
    bool  FUN_00ac8d60(int a);
    bool  FUN_00ac8d80(float* p);
    bool  FUN_00ac8df0(float* p);
    void  FUN_00ac8e90();
};
struct CSC { void FUN_00695b40(void* a, void* b, const wchar_t* c); };  // 0x695b40
struct S28 {
    int   a;          // +0x00
    float b;          // +0x04
    float c;          // +0x08
    float d;          // +0x0c
    short e;          // +0x10
    byte  f;          // +0x12
    char  pad13;      // +0x13
    float g;          // +0x14
    int   h;          // +0x18
    int   i;          // +0x1c
    int   j;          // +0x20
    int   k;          // +0x24
    byte  l;          // +0x28
    void assign(const S28* s);
    void* FUN_00ac9200(S28* s);
};
void S28::assign(const S28* s)
{
    a = s->a;
    b = s->b;
    c = s->c;
    d = s->d;
    e = s->e;
    f = s->f;
    g = s->g;
    h = s->h;
    i = s->i;
    j = s->j;
    k = s->k;
    l = s->l;
}
struct RefPtr_s00ac_8d00 {
    RCObj* mp;
    RefPtr_s00ac_8d00* assign(RefPtr_s00ac_8d00* src);  // 0x00ac8980 (RefPtr::assign)
};
struct S2c { char data[0x2c]; };
struct cLocomotionRequest {
    char data[0x74];
    cLocomotionRequest();
};
extern byte  DAT_01565cfc;
static int FUN_00ac98e0_readfloat(int* p, int id, int def)
{
    int v;
    if (!p) return def;
    if (!(*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, id, (void**)&p)) return def;
    short t = *(short*)((char*)p + 0x12);
    if (t != 0xd && t != 0x10) { v = DAT_015d9c6c; return v; }
    if (*(byte*)((char*)p + 0x10) & 0x30) return *(int*)*(int*)p;
    return *(int*)((t != 0 ? -1 : 0) & (int)p);
}
struct CAnim2 { void Release(); };
struct Vec {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void FUN_00ac9d90();
};
// ---- items of slice s00ac8d00 end

// ---- items of slice s00ac9f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" float DAT_0140f334;                                    // 0x0140f334
extern "C" char  DAT_015d8b54;
extern "C" char  DAT_015d8b56;
extern "C" char  DAT_015d8b59;
extern "C" unsigned short DAT_01667bac[];                              // 0x01667bac L""
extern "C" unsigned short DAT_013f36bc[];                              // 0x013f36bc L"type"
#define FSQRT(v) _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(v)))
typedef unsigned int uint;
typedef unsigned char uchar;
static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }
void  __cdecl FUN_00f47380(void* p);            // 0x00f47380 free
void  __cdecl FUN_00829110(void* a, void* b, void* c, void* d, void* e);
struct VecObj {                       // EASTL vector header {begin, end, capacity}
  void FUN_00b93c60(uint n, void* p); // 0x00b93c60
};
struct SortValue {                       // 3-float heap sort key
    float x, y, z;
    char FUN_00ac0730(void* a, void* b); // 0x00ac0730 distance compare (thiscall, ret 8)
};
void  __cdecl FUN_00ac93c0(void* arr, void* arg2, int holeIndex, void* arg5, SortValue value); // 0x00ac93c0
void  __fastcall FUN_00d5ccf0(void* self, int, void* p);          // 0x00d5ccf0 (thiscall, ret 4)
void  __cdecl FUN_00d576d0(void* p);
void  __fastcall FUN_00d5f780(void* self, int, void* p);          // 0x00d5f780 (thiscall, ret 4)
void* __fastcall FUN_00c8e820(void* self, int, void* p);          // 0x00c8e820 (thiscall, ret 4)
void  __fastcall FUN_00c96e80(void* self, int, void* p);          // 0x00c96e80 (thiscall, ret 4)
unsigned __cdecl FUN_00b5b800(void);                              // 0x00b5b800 current game mode
void* __fastcall FUN_00c0bbd0(void* self, int);                   // 0x00c0bbd0
void  __fastcall FUN_00645ed0(void* self, int, void* out, void* in);  // 0x00645ed0 (thiscall, ret 8)
void  __fastcall FUN_01068380(void* self, int, void* a, void* b);     // 0x01068380 (thiscall, ret 8)
void  __cdecl FUN_0093aa70(void* a, void* b, int c, int d);
void  __cdecl FUN_0093a780(void* a, void* b, int c, int d);
void  __fastcall FUN_00ae6970(void* p);
struct cWideString {
    unsigned short* mpBegin;
    unsigned short* mpEnd;
    unsigned short* mpCapacityEnd;
    cWideString* FUN_0056e2d0(const cWideString* src); // 0x0056e2d0 copy-ctor (thiscall, ret 4)
};
cWideString* FUN_0093c5a0(cWideString* out, const char* src, int len); // 0x0093c5a0
cWideString* FUN_0093c6d0(cWideString* out, const cWideString* src);   // 0x0093c6d0
void  __cdecl FUN_00694fc0(cWideString* out, const void* value);       // 0x00694fc0
void  __cdecl FUN_00695010(cWideString* out, const void* value);       // 0x00695010
void  __cdecl FUN_00694c10(cWideString* out, const void* value);       // 0x00694c10
#define WSTR_FREE(s) do { \
    if ((((unsigned)((char*)(s).mpCapacityEnd - (char*)(s).mpBegin) & ~1u) > 2) && (s).mpBegin) \
        FUN_00f47380((s).mpBegin); \
} while (0)
#define WSTR_FREE_CMDLINE(s) do { \
    if (((char*)(s).mpCapacityEnd - (char*)(s).mpBegin) > 1 && (s).mpBegin) \
        FUN_00f47380((s).mpBegin); \
} while (0)
#define WSTR_SET_EMPTY_ODD(s) do { \
    (s).mpBegin = DAT_01667bac; (s).mpEnd = DAT_01667bac; \
    (s).mpCapacityEnd = (unsigned short*)0x01667bad; \
} while (0)
struct HTNode { int mKey; int mValue; HTNode* mpNext; };
struct HTPair { int mKey; int mValue; };
struct HTIter { HTNode* mpNode; void* mpBucket; char mbInserted; };
struct HashTable {
    int         mPad00;        // +0x00
    HTNode**    mpBuckets;     // +0x04
    int         mBucketCount;  // +0x08
    int         mCount;        // +0x0c
    void FUN_00693230(HTNode** buckets, int count);          // 0x00693230 (thiscall, ret 8)
    void FUN_007c3990(HTIter* out, const HTPair* pair, int hint); // 0x007c3990 (thiscall, ret 0xc)
};
struct GameCreature { void FUN_00aca360(void* other); };       // 0x00aca360 (thiscall, ret 4)
struct VecCopyStub { int* FUN_00aca970(int* src); };
struct FourVecDtorStub { void* FUN_00acb150(uchar flags); };
// ---- items of slice s00ac9f70 end

// ---- items of slice s00acb1b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00ac9740(void* a, void* b, void* c);
void* __cdecl FUN_00ac89e0(void* a, void* b, void* c);
void* __cdecl FUN_00ac94c0(void* outIter, void* begin, void* initVal, void* end, void* extra);
void __cdecl FUN_00a02c30(void* obj);   // addref  (thiscall-style, ecx = obj)
void __cdecl FUN_00a05270(void* obj);   // release (thiscall-style, ecx = obj)
struct XC {
    void  FUN_00aca9d0(void*);
    void  FUN_00b93c60(uint, void*);
    void  FUN_00a05270();
    void  FUN_00a02c30();
};
struct VO {
    int* v;                       // +0 begin
    void* FUN_00acb490(int* src); // 00acb490
    void  FUN_00acb680(uchar* pos, uchar* val);
    void  FUN_00acb7c0(void* a2, void* a3);
    void  FUN_00acb810(uchar* pos, uchar* val);
    void  FUN_00acb930(int a2, int a3, int a4);
    void* FUN_00acbaf0(int* src);
    int*  FUN_00acbd90(int* other);
    int   FUN_00acbed0(int a2, int a3);
    void  FUN_00acbf30(int a2, uint a3, int a4);
    void* FUN_00acaa50(uint n, void* a, void* b);
    void  FUN_00ac8930(void* a, void* b);
};
void* FUN_00acbb20(uchar* p, uchar* end, uchar* out); // 00acbb20
// ---- items of slice s00acb1b0 end

// ---- items of slice s00acc140 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* DAT_01654c04;
struct Vec3 { float x, y, z; };
struct Key3 { int a, b, c; };
struct KeyVec {                         // vector header passed to LoadSelector
    Key3* mpBegin;                      // +0x00
    Key3* mpEnd;                        // +0x04
    Key3* mpCap;                        // +0x08
    void reserve(int n);                // 0x0041e4d0
    void pushSlow(void* end, void* value); // 0x004e3e10
};
struct RareEntry {                      // 0x2c record appended to planet+0x134
    uint          mUnk00;               // +0x00 (not written by sGetClosestRare)
    Vec3          mPos;                 // +0x04
    unsigned short mUnk10;              // +0x10 (not written)
    uchar         mUnk12;               // +0x12 (not written)
    uchar         mUnk13;               // +0x13
    uint          mUnk14;               // +0x14 (not written)
    int           mZero18;              // +0x18
    Vec3          mOther;               // +0x1c
    uchar         mKind28;              // +0x28
    uchar         mPad29[3];
};
struct Planet {
    uchar      mPad00[0xd0];            // +0x000
    Key3*      mpKeyBegin;              // +0x0d0
    Key3*      mpKeyEnd;                // +0x0d4
    uchar      mPadD8[0x5c];            // +0x0d8
    RareEntry* mpRareBegin;             // +0x134
    RareEntry* mpRareEnd;               // +0x138
    RareEntry* mpRareCap;               // +0x13c
};
struct LivingUniverse {
    uchar  mPad00[0x13c];               // +0x000
    Planet* mpPlanet;                   // +0x13c
};
struct StageRec {                       // 0x0c record in a sorted map node
    int   mPad0;                        // +0x00
    uchar mActive;                      // +0x04
    uchar mPad5[3];
    void* mpStage;                      // +0x08
};
struct MapNode {                        // 0x20 sorted key node at this+0x88
    int        mKey;                    // +0x00
    uchar      mPad04[4];               // +0x04
    uchar      mFlag8;                  // +0x08
    uchar      mFlag9;                  // +0x09
    uchar      mPad0a[2];
    StageRec*  mpRecordsBegin;          // +0x0c
    StageRec*  mpRecordsEnd;            // +0x10
    StageRec*  mpRecordsCap;            // +0x14
    uchar      mPad18[8];               // +0x18
};
struct StageGroup {                     // list of stage objects under one hash node
    uchar  mPad00[0x40];                // +0x00
    void** mpStagesBegin;               // +0x40
    void** mpStagesEnd;                 // +0x44
};
struct HashNode {                       // 0x6c bucket-chain node at this+0xc4
    uchar       mPad00[0x54];           // +0x00
    void**      mpBegin;                // +0x54
    void**      mpEnd;                  // +0x58
    void**      mpCap;                  // +0x5c
    uchar       mPad60[8];              // +0x60
    HashNode*   mpNext;                 // +0x68
};
struct StageList {                      // 0x18 block in the vector at this+0xa8
    void*   mpOwner;                    // +0x00
    void**  mpBegin;                    // +0x04
    void**  mpEnd;                      // +0x08
    void**  mpCap;                      // +0x0c
    uchar   mPad10[8];                  // +0x10
};
struct CountMap {
    uchar mOpaque[4];                   // map at this+0xe0; only its address is used
    int*  slot(int* key);               // 0x007c3a90
    void  erase(int* key);              // 0x00a460d0
};
typedef void  (__thiscall *VoidFn)(void*);
typedef void* (__thiscall *PtrFn)(void*);
typedef int   (__thiscall *IntFn)(void*);
typedef void  (__thiscall *Void2IntFn)(void*, void*, int);
static int   objType(void* o)                 { return ((IntFn)vc(o, 0x20))(o); }
static void  objRelease(void* o)              { ((VoidFn)vc(o, 0x04))(o); }
static void* vcall0p(void* o, int slot)       { return ((PtrFn)vc(o, slot))(o); }
static void  vcall2i(void* o, int slot, void* a, int b)  { ((Void2IntFn)vc(o, slot))(o, a, b); }
void  __cdecl FUN_00ac97f0(void* a, void* b, void* c);
void  __cdecl FUN_00ac89a0(void* a, void* b, void* c);
void* __cdecl FUN_00ac95a0(void* a, void* b, void* c);
void* __cdecl FUN_00b33f40();
void* __cdecl FUN_00b5b800_s00ac_c140();
void* __cdecl FUN_01021260();
struct CStage {
    uchar mPad00[0x24];               // +0x000 (vtable pointer and unknown fields)
    int   mKey24;                     // +0x024
    uchar mPad28[0x49];               // +0x028..+0x070
    uchar mFlag71;                    // +0x071
    uchar mPad72[3];                  // +0x072..+0x074
    uchar mFlag75;                    // +0x075
    uchar mPad76[0x4a];               // +0x076..+0x0bf
    uchar mSubC0[4];                  // +0x0c0 subobject with its own vtable
    uchar mPadC4[0xa90];              // +0x0c4..+0xb53
    void* mpFieldB54;                 // +0xb54
    uchar mPadB58[0x2fc];             // +0xb58..+0xe53
    uint  mCountE54;                  // +0xe54

    char  canDo();                    // 0x00c0c0e0
    void* getFrame();                 // 0x00c0bc00
    char  hasA();                     // 0x00c232b0
    char  hasB();                     // 0x00c232c0
    void* getHerd();                  // 0x00c04590
    void  setHerd(void* p);           // 0x00c045a0
};
struct RareVec {
    RareEntry* mpBegin;
    RareEntry* mpEnd;
    RareEntry* mpCap;
    void grow(RareEntry* end, RareEntry* value);          // 0x00acb810
};
struct XC_s00ac_c140 {
    void  FUN_00acbd90();
    void  FUN_01011cc0(void*);
    void  FUN_00ac97f0(void*, void*);
    void  FUN_00ac89a0(void*, void*);
    void* FUN_00ac95a0(void*);
    void  FUN_00acb680(void*, void*);
    void  FUN_00acb810(void*);
    void  FUN_00acb930(void*, int, void*);
    void  FUN_00acb7c0(void*, void*);
    void  FUN_00c232b0();
    void  FUN_00c232c0();
    int   FUN_00c0c0e0();
    void* FUN_00c0bc00();
    void  FUN_00a05270();
};
struct VO_s00ac_c140 {
    int* v;                        // +0x00
    uchar  mPad04[0x84];           // +0x04
    MapNode* mpMapBegin;           // +0x88
    MapNode* mpMapEnd;             // +0x8c
    uchar  mPad90[0x0c];           // +0x90
    uchar  mMapMode;               // +0x9c
    uchar  mPad9d[0x0b];           // +0x9d
    StageList* mpListsBegin;       // +0xa8
    StageList* mpListsEnd;         // +0xac
    uchar  mPadB0[0x14];           // +0xb0
    HashNode** mpBuckets;          // +0xc4
    uint   mBucketEnd;             // +0xc8
    uchar  mPadCC[0x14];           // +0xcc
    CountMap mCountMap;            // +0xe0

    void  FUN_00acc140(uchar* pos, uchar* val);
    void  FUN_00acc610(void* p);
    void  FUN_00acc700(void* p, float a, float b);
    void  FUN_00acc770();
    void  FUN_00acc9b0(uint n);
    void  FUN_00acc390();
    bool  FUN_00accf80(void* p);
    void  FUN_00acd210();
    void  FUN_00acd2d0(void* p);
    void  FUN_00acd410(void* p);
    void  FUN_00ac84f0(void* p);   // 0x00ac84f0, defined in another slice
};
void  __stdcall FUN_00acc800(KeyVec* v);
void  FUN_00accd70(int arr, uint n);
int*  FUN_00acc2d0(int* p, int* end, int* out);
int*  FUN_00acc330(int end, int begin, int* out);
// ---- items of slice s00acc140 end

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

// @ 0x00ac0180
bool InterObj::FUN_00ac0180(EntityArg* arg, int unused)
{
    (void)unused;
    if (arg->mf6c == 0) {
        ((void(__fastcall*)(void*))(*(void***)this)[0x34 / 4])(this);
        ((void(__fastcall*)(void*))(*(void***)this)[0x38 / 4])(this);
    }
    int count = ((int(__fastcall*)(void*))(*(void***)this)[0x38 / 4])(this);
    if (count > 0) {
        int*  at   = mDeque.mpBegin;
        int*  end  = mDeque.mpEnd;
        int*  base = mDeque.mpBlockBase;
        if (at == end) {
            base = base - 1;
            at   = (int*)(*base + 0x100);
        }
        int* item = *(int**)(at - 1);
        if (item != 0)
            ((void(__fastcall*)(void*))(*(void***)item)[0])(item);
        int* slot = (int*)this;
        int* dst = ((SlotMap*)((char*)item + 0x4c))->FUN_00ac0010(&slot);
        *dst = 1;
        if (item != 0)
            ((void(__fastcall*)(void*))(*(void***)item)[1])(item);
    }

    int* slot2 = (int*)this;
    int* dst2 = ((SlotMap*)((char*)arg + 0x4c))->FUN_00ac0010(&slot2);
    *dst2 = 0;

    int* entity = (int*)arg;
    ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);

    SlotDeque* dq = &mDeque;
    int** pos = (int**)dq->mpBegin;
    if ((int*)((char*)pos + 4) != dq->mpCapacity) {
        dq->mpBegin = (int*)((char*)pos + 4);
        if (pos != 0) {
            *pos = entity;
            ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);
            ((void(__fastcall*)(void*))(*(void***)entity)[1])(entity);
            return true;
        }
    } else {
        ((SlotMap*)dq)->FUN_00c92bd0(&slot2);
    }
    ((void(__fastcall*)(void*))(*(void***)entity)[1])(entity);
    return true;
}

// @ 0x00ac0270
void __fastcall FUN_00ac0270(int self, void* str)
{
    extern void __cdecl ebg_string_assign(void*, const char*, const char*); // 0x454cb0
    ebg_string_assign(str, (const char*)VBASE_01459be5, (const char*)VBASE_01459bd0);
    int cur    = *(int*)(self + 0x20);
    int last   = *(int*)(self + 0x24);
    int capEnd = *(int*)(self + 0x2c);
    int limit  = *(int*)(self + 0x10);
    int n = 0;
    extern void __fastcall ebg_string_append(void*, int, int);   // 0x455d60
    extern void __fastcall ebg_string_push_back(void*, int);     // 0x5306c0
    while (cur != limit) {
        int e = cur;
        if (cur == last)
            e = *(int*)(capEnd - 4) + 0x100;
        ebg_string_append(str, *(int*)(e - 0x10), *(int*)(e - 0xc));
        ebg_string_push_back(str, 10);
        if (++n >= 4)
            break;
        if (cur == last) {
            last = *(int*)(capEnd - 4);
            capEnd -= 4;
            cur = last + 0x100;
        }
        cur -= 0x10;
    }
}

// @ 0x00ac0570
void ThiscallStub::Object_Cast(int* entity)
{
    int** self = (int**)this;
    if (entity != 0)
        ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);
    int* begin = self[2];
    int* end   = self[3];
    if (begin < end) {
        self[2] = (int*)((char*)begin + 4);
        if (begin != 0) {
            *begin = (int)entity;
            if (entity != 0)
                ((void(__fastcall*)(void*))(*(void***)entity)[0])(entity);
        }
    } else {
        extern void __cdecl FUN_00aea5d0(int, void*, int*); // 0xaea5d0 DoInsertPtr
        FUN_00aea5d0((int)begin, (void*)(self + 1), (int*)&entity);
    }
    if (entity != 0)
        ((void(__fastcall*)(void*))(*(void***)entity)[1])(entity);
}

// @ 0x00ac05d0
int ThiscallStub::FUN_00ac05d0(int classId)
{
    int self = (int)this;
    if (classId != (int)0xee3f516e) {
        if (classId == 0xe69e1e)
            return self;
        return self & (((classId != 0x102a041a) ? 1 : 0) - 1);
    }
    if (self != 0)
        return self + 0x18;
    return 0;
}

// @ 0x00ac06c0
int* ThiscallStub::FUN_00ac06c0(float* pos, float a, float b)
{
    int* self = (int*)this;
    ((InteractionTargetCtor*)self)->ctor();
    self[6] = (int)0x13f1ab0;
    self[7] = (int)0x13ec458;
    self[8] = 0;
    self[0] = (int)VTBL_01459c04;
    self[6] = (int)VTBL_01459c30;
    self[7] = (int)VTBL_01459c20;
    *(float*)(self + 9)  = pos[0];
    *(float*)(self + 10) = pos[1];
    *(float*)(self + 11) = pos[2];
    *(float*)(self + 0xc) = a;
    *(float*)(self + 0xd) = b;
    return self;
}

// @ 0x00ac0730
int ThiscallStub::FUN_00ac0730(void* a, void* b)
{
    float* self = (float*)this;
    float* pa = ((GetVecFn)((*(void***)a)[0x2c / 4]))(a);
    float dxa = self[0] - pa[0];
    float dya = self[1] - pa[1];
    float dza = self[2] - pa[2];
    float da  = dya * dya + dxa * dxa + dza * dza;

    float* pb = ((GetVecFn)((*(void***)b)[0x2c / 4]))(b);
    float dxb = self[0] - pb[0];
    float dyb = self[1] - pb[1];
    float dzb = self[2] - pb[2];
    float db  = dzb * dzb + dyb * dyb + dxb * dxb;

    float diff = db - da;
    if (diff < G_013eb960 && G_0140ced4 < diff)
        return (int)(a < b);
    if (da < db)
        return 1;
    return 0;
}

// @ 0x00ac0810
int ThiscallStub::FUN_00ac0810(void* a, void* b)
{
    float* self = (float*)this;
    extern float* __fastcall cCivData_GetCities(void*); // 0x5c65e0
    float* pa = cCivData_GetCities(a);
    float dxa = self[0] - pa[0];
    float dya = self[1] - pa[1];
    float dza = self[2] - pa[2];
    float da  = dya * dya + dxa * dxa + dza * dza;

    float* pb = cCivData_GetCities(b);
    float dxb = self[0] - pb[0];
    float dyb = self[1] - pb[1];
    float dzb = self[2] - pb[2];
    float db  = dzb * dzb + dyb * dyb + dxb * dxb;

    float diff = db - da;
    if (diff < G_01459c48 && G_013f89b8 < diff)
        return (int)(a < b);
    if (da < db)
        return 1;
    return 0;
}

// @ 0x00ac08f0
int __cdecl FUN_00ac08f0(int* range, float* query)
{
    float best = G_1459c44;
    float qx = query[0];
    float qy = query[1];
    float qz = query[2];
    int n = (range[1] - range[0]) / 12;
    int idx = 0;
    int bestIdx = -1;
    float* p = (float*)range[0];
    for (; idx < n - 3; idx += 4, p += 12) {
        float d0 = (p[0] - qx) * (p[0] - qx) + (p[1] - qy) * (p[1] - qy)
                 + (p[2] - qz) * (p[2] - qz);
        if (d0 < best) { best = d0; bestIdx = idx; }
        float d1 = (p[3] - qx) * (p[3] - qx) + (p[4] - qy) * (p[4] - qy)
                 + (p[5] - qz) * (p[5] - qz);
        if (d1 < best) { best = d1; bestIdx = idx + 1; }
        float d2 = (p[6] - qx) * (p[6] - qx) + (p[7] - qy) * (p[7] - qy)
                 + (p[8] - qz) * (p[8] - qz);
        if (d2 < best) { best = d2; bestIdx = idx + 2; }
        float d3 = (p[9] - qx) * (p[9] - qx) + (p[10] - qy) * (p[10] - qy)
                 + (p[11] - qz) * (p[11] - qz);
        if (d3 < best) { best = d3; bestIdx = idx + 3; }
    }
    for (; idx < n; idx += 1, p += 3) {
        float d = (p[0] - qx) * (p[0] - qx) + (p[1] - qy) * (p[1] - qy)
                + (p[2] - qz) * (p[2] - qz);
        if (d < best) { best = d; bestIdx = idx; }
    }
    return bestIdx;
}

// @ 0x00ac0b00
CargoItem* __fastcall FUN_00ac0b00(CargoItem* self)
{
    extern void __fastcall cSPSpaceInventoryItem_ctor(void*); // 0xc87660
    cSPSpaceInventoryItem_ctor(self);
    self->mpVftable             = VTBL_01459c98;
    self->mpHandlerVftable      = VTBL_01459c90;
    self->mpSerializableVftable = VTBL_01459c6c;
    self->mpSpeciesProfile      = 0;
    return self;
}

// @ 0x00ac0bb0
void ThiscallStub::FUN_00ac0bb0(void** out)
{
    CargoItem* src = (CargoItem*)this;
    CargoItem* p = (CargoItem*)operator_new(0x80, STR_1459d0c, 0, 0, 0, 0);
    CargoItem* result = 0;
    if (p != 0) {
        FUN_00ac0b00(p);
        ((ThiscallStub*)p)->FUN_00c870b0(src);
        if (p != src)
            p->mpSpeciesProfile = src->mpSpeciesProfile;
        ((void(__fastcall*)(void*))(*(void***)p)[1])(p);
        result = p;
    }
    *out = result;
}

// @ 0x00ac0c30
bool __fastcall FUN_00ac0c30(CargoItem* self)
{
    SpeciesProfile* obj = self->mpSpeciesProfile;
    if (obj != 0)
        return *(u32*)&obj->mf60c > 0u;
    return true;
}

// @ 0x00ac0c50
bool __fastcall FUN_00ac0c50(CargoItem* self)
{
    SpeciesProfile* obj = self->mpSpeciesProfile;
    if (obj != 0)
        return *(u32*)&obj->mf608 > 0u;
    return true;
}

// @ 0x00ac0cb0
void __fastcall FUN_00ac0cb0(int self, int speciesKey, int count, void** out)
{
    (void)self;
    int n = count;
    if (n < 1)
        n = 1;
    FUN_00401090((void*)speciesKey);
    extern void* __fastcall FUN_004df550_(void*);    // 0x4df550 GetProfile
    int profile = (int)FUN_004df550_((void*)speciesKey);
    if (profile == 0)
        return;
    CargoItem* p = (CargoItem*)operator_new(0x80, STR_1459d0c, 0, 0, 0, 0);
    if (p == 0)
        p = 0;
    else
        FUN_00ac0b00(p);
    ((void(__fastcall*)(void*))(*(void***)p)[1])(p);
    ((void(__fastcall*)(void*, int))(*(void***)p)[0x14 / 4])(p, profile + 0x504);
    p->mpSpeciesProfile = (SpeciesProfile*)profile;
    p->mnItemType  = ((count != 0) ? 5 : 0) + 1;
    extern void __fastcall cSPSpaceInventoryItem_SetPropertyList(void*, int); // 0xc877f0
    cSPSpaceInventoryItem_SetPropertyList(p, 0);
    p->mnItemCount = n;
    *out = p;
}

// @ 0x00ac86b0
void CVis::FUN_00ac86b0(int v)
{
    void* g = mpA4;
    if (g) *(int*)((char*)g + 0xa4c) = v;
}

// @ 0x00ac8750
bool FUN_00ac8750(SerObj* p, int value)
{
    Stream* s = p->a20();
    ReadBool(s->s18(), value);
    return true;
}

// @ 0x00ac8780
bool FUN_00ac8780(SerObj* p, char* pValue)
{
    Stream* s = p->a20();
    char c = *pValue;
    void* st = s->s18();
    bool b = (c != 0);
    WriteBool3(st, &b, 1);
    return true;
}

// @ 0x00ac87c0
bool FUN_00ac87c0(SerObj* p, int value)
{
    Stream* s = p->a20();
    FUN_00693890(s->s18(), value);
    return true;
}

// @ 0x00ac87f0
bool FUN_00ac87f0(SerObj* p, int value)
{
    Stream* s = p->a20();
    FUN_00692e50(s->s18(), value);
    return true;
}

// @ 0x00ac88f0
bool FUN_00ac88f0(SerObj* p, float* pValue)
{
    Stream* s = p->a20();
    float f = *pValue;
    void* st = s->s18();
    WriteUint32(st, &f, 1, 0);
    return true;
}

// @ 0x00ac8930
void __stdcall FUN_00ac8930(char* first, char* last)
{
    for (; first < last; first += 0xc) {
        IObj* p = (IObj*)first;
        p->b00(0);
    }
}

// @ 0x00ac8980
RefPtr* RefPtr::assign(void** src)
{
    void* p = *src;
    mp = p;
    if (p) ((void (__thiscall*)(void*))vs(p, 0))(p);
    return this;
}

// @ 0x00ac89e0
void** FUN_00ac89e0(void** first, void** last, void** out)
{
    while (first != last) {
        void* a = *first;
        void* b = *out;
        if (a != b) {
            if (a) ((CAnim*)a)->AddRef();
            *out = a;
            if (b) ((CAnim*)b)->Release();
        }
        ++first;
        ++out;
    }
    return out;
}

// @ 0x00ac8a30
void** FUN_00ac8a30(void* last_, void* first_, void** out)
{
    char* last = (char*)last_;
    char* first = (char*)first_;
    while (first != last) {
        void* a = *(void**)(first - 4);
        void* b = out[-1];
        first -= 4;
        --out;
        if (a != b) {
            if (a) ((CAnim*)a)->AddRef();
            *out = a;
            if (b) ((CAnim*)b)->Release();
        }
    }
    return out;
}

// @ 0x00ac8df0
bool CT::FUN_00ac8df0(float* p)
{
    float* pf = mpSphereBegin;
    float* end = mpSphereEnd;
    if (pf != end) {
        float x = p[0], y = p[1], z = p[2];
        do {
            float dx = x - pf[0];
            float dy = y - pf[1];
            float dz = z - pf[2];
            float sum = dx * dx + dy * dy + dz * dz;
            if (pf[3] >= sum) return true;
            pf += 5;
        } while (pf != end);
    }
    return false;
}

// @ 0x00ac8e90
void CT::FUN_00ac8e90()
{
    int saved = *(int*)((char*)mpA4 + 0xaf0);
    ((CGVis*)mpA4)->SetCity(0);
    ((CGVis*)mpA4)->SetCity(saved);
}

// @ 0x00ac8f00
float* FUN_00ac8f00(float* out, int* p, int a, float p4, float p5)
{
    if (p) {
        char ok = (*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, a, (void**)&p);
        if (ok) {
            short t = *(short*)((char*)p + 0x12);
            if (t != 0x30 && t != 0x10) {
                float* q = (float*)FUN_006bb5d0();
                out[0] = q[0];
                out[1] = q[1];
                return out;
            }
            if (*(byte*)((char*)p + 0x10) & 0x30) {
                float* q = (float*)*(int*)p;
                out[0] = q[0];
                out[1] = q[1];
                return out;
            }
            float* q = (float*)((t != 0 ? -1 : 0) & (int)p);
            out[0] = q[0];
            out[1] = q[1];
            return out;
        }
    }
    out[0] = p4;
    out[1] = p5;
    return out;
}

// @ 0x00ac8fa0
int FUN_00ac8fa0(int* p, int a, int b)
{
    if (p) {
        char ok = (*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, a, (void**)&p);
        if (ok) {
            short t = *(short*)((char*)p + 0x12);
            if (t != 10 && t != 0x10) {
                return DAT_0164dc58;
            }
            if (*(byte*)((char*)p + 0x10) & 0x30) {
                return *(int*)*(int*)p;
            }
            int m = (t != 0 ? -1 : 0);
            return *(int*)(m & (int)p);
        }
    }
    return b;
}

// @ 0x00ac9040
void FUN_00ac9040(int* self, int* arr)
{
    int count = (arr[1] - arr[0]) >> 5;
    int* q = (int*)(*(void* (__thiscall**)(int*))((char*)VT(self) + 0x20))(self);
    WriteUint32((void*)(*(void* (__thiscall**)(int*))((char*)VT(q) + 0x18))(q), &count, 1, 0);
    int* end = (int*)arr[1];
    for (int* it = (int*)arr[0]; it != end; it += 8) {
        int v = *it;
        q = (int*)(*(void* (__thiscall**)(int*))((char*)VT(self) + 0x20))(self);
        WriteUint32((void*)(*(void* (__thiscall**)(int*))((char*)VT(q) + 0x18))(q), &v, 1, 0);
        (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
        char srl[0xa14];
        SP_cVarListSerializer_ctor(srl, it + 1, (void*)0x1566000, 0x1a80d26);
        SP_cVarListSerializer_Serialize(srl, self);
        (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
    }
    (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
}

// @ 0x00ac9110
bool FUN_00ac9110(void* a, int* arr)
{
    int end = arr[1];
    for (int it = arr[0]; it != end; it += 0x20) {
        if (it != -4) {
            ((CSC*)a)->FUN_00695b40((void*)(it + 4), (void*)0x1566000, L"cCastInfo");
        }
    }
    return 1;
}

// @ 0x00ac9150
void FUN_00ac9150(int* self, int* arr)
{
    int count = (arr[1] - arr[0]) / 0xc;
    int* q = (int*)(*(void* (__thiscall**)(int*))((char*)VT(self) + 0x20))(self);
    WriteUint32((void*)(*(void* (__thiscall**)(int*))((char*)VT(q) + 0x18))(q), &count, 1, 0);
    int* end = (int*)arr[1];
    for (int* it = (int*)arr[0]; it != end; it += 3) {
        (*(void (__thiscall**)(int*, int*))((char*)VT(it) + 4))(it, self);
    }
    (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
}

// @ 0x00ac9200
void* S28::FUN_00ac9200(S28* s)
{
    assign(s);
    return this;
}

// @ 0x00ac93c0
void FUN_00ac93c0(int base, int start, int idx, int* value)
{
    int i = idx;
    while (start < i) {
        int parent = (i - 1) >> 1;
        void* b;
        if (value == 0) b = 0;
        else b = (char*)value + 0x120;
        int e = *(int*)(base + parent * 4);
        void* a;
        if (e == 0) a = 0;
        else a = (char*)e + 0x120;
        if (!FUN_00ac0730(a, b)) break;
        RCObj* pv = *(RCObj**)(base + parent * 4);
        RCObj* pi = *(RCObj**)(base + i * 4);
        if (pv != pi) {
            if (pv) pv->AddRef();
            *(RCObj**)(base + i * 4) = pv;
            if (pi) pi->Release();
        }
        i = parent;
    }
    RCObj* pv = *(RCObj**)(base + i * 4);
    if (value != (int*)pv) {
        if (value) ((RCObj*)value)->AddRef();
        *(int**)(base + i * 4) = value;
        if (pv) pv->Release();
    }
    if (value) ((RCObj*)value)->Release();
}

// @ 0x00ac9480
RefPtr_s00ac_8d00* RefPtr_s00ac_8d00::assign(RefPtr_s00ac_8d00* src)
{
    RCObj* p = src->mp;
    RCObj* old = mp;
    if (p != old) {
        if (p) p->AddRef();
        mp = p;
        if (old) old->Release();
    }
    return this;
}

// @ 0x00ac94c0
void* FUN_00ac94c0(void** out, Pair* src, Pair* end, void* base)
{
    *out = base;
    for (; src != end; src = (Pair*)((char*)src + 0xc)) {
        Pair* d = (Pair*)*out;
        if (d) {
            d->mpVtbl = (void*)0x145a158;
            d->mb4 = src->mb4;
            RCObj* p = (RCObj*)src->mp8;
            d->mp8 = p;
            if (p) p->AddRef();
        }
        *out = (char*)*out + 0xc;
    }
    return out;
}

// @ 0x00ac9510
void FUN_00ac9510(char* d, char* end, char* s)
{
    for (; d != end; d += 0xc) {
        d[4] = s[4];
        RCObj* p = *(RCObj**)(s + 8);
        RCObj* old = *(RCObj**)(d + 8);
        if (p != old) {
            if (p) p->AddRef();
            *(RCObj**)(d + 8) = p;
            if (old) old->Release();
        }
    }
}

// @ 0x00ac9560
void FUN_00ac9560(char* d, int n, char* s)
{
    for (; n != 0; --n) {
        if (d) {
            *(void**)d = (void*)0x145a158;
            d[4] = s[4];
            RCObj* p = *(RCObj**)(s + 8);
            *(RCObj**)(d + 8) = p;
            if (p) p->AddRef();
        }
        d += 0xc;
    }
}

// @ 0x00ac95a0
char* FUN_00ac95a0(char* s, char* end, char* d)
{
    while (s != end) {
        if (d) {
            *(void**)d = (void*)0x145a158;
            d[4] = s[4];
            RCObj* p = *(RCObj**)(s + 8);
            *(RCObj**)(d + 8) = p;
            if (p) p->AddRef();
        }
        s += 0xc;
        d += 0xc;
    }
    return d;
}

// @ 0x00ac95f0
void** FUN_00ac95f0(void** out, NRef*** src, NRef*** end, void* base)
{
    *out = base;
    for (; src != end; ++src) {
        NRef** d = (NRef**)*out;
        if (d) {
            NRef* p = (NRef*)*src;
            *d = p;
            if (p) p->AddRef();
        }
        *out = (char*)*out + 4;
    }
    return out;
}

// @ 0x00ac9630
void FUN_00ac9630(NRef** p, NRef** end, NRef*** src)
{
    for (; p != end; ++p) {
        NRef* s = (NRef*)*src;
        NRef* old = *p;
        if (s != old) {
            if (s) s->AddRef();
            *p = s;
            if (old) old->Release();
        }
    }
}

// @ 0x00ac9680
void FUN_00ac9680(NRef** p, unsigned int n, NRef*** src)
{
    while (n > 0) {
        if (p) {
            NRef* s = (NRef*)*src;
            *p = s;
            if (s) s->AddRef();
        }
        --n;
        ++p;
    }
}

// @ 0x00ac96b0
char* FUN_00ac96b0(char* p, char* end, char* d)
{
    if (p != end) {
        do {
            if (d) {
                S2c* s = (S2c*)p;
                S2c* t = (S2c*)d;
                *(int*)t = *(int*)s;
                *(float*)((char*)t + 4) = *(float*)((char*)s + 4);
                *(float*)((char*)t + 8) = *(float*)((char*)s + 8);
                *(float*)((char*)t + 0xc) = *(float*)((char*)s + 0xc);
                *(short*)((char*)t + 0x10) = *(short*)((char*)s + 0x10);
                *(byte*)((char*)t + 0x12) = *(byte*)((char*)s + 0x12);
                *(float*)((char*)t + 0x14) = *(float*)((char*)s + 0x14);
                *(int*)((char*)t + 0x18) = *(int*)((char*)s + 0x18);
                *(int*)((char*)t + 0x1c) = *(int*)((char*)s + 0x1c);
                *(int*)((char*)t + 0x20) = *(int*)((char*)s + 0x20);
                *(int*)((char*)t + 0x24) = *(int*)((char*)s + 0x24);
                *(byte*)((char*)t + 0x28) = *(byte*)((char*)s + 0x28);
            }
            p += 0x2c;
            d += 0x2c;
        } while (p != end);
        return d;
    }
    return d;
}

// @ 0x00ac9740
char* FUN_00ac9740(char* p, char* end, char* d)
{
    while (p != end) {
        d[4] = p[4];
        RCObj* s = *(RCObj**)(p + 8);
        RCObj* old = *(RCObj**)(d + 8);
        if (s != old) {
            if (s) s->AddRef();
            *(RCObj**)(d + 8) = s;
            if (old) old->Release();
        }
        p += 0xc;
        d += 0xc;
    }
    return d;
}

// @ 0x00ac97a0
RCObj** FUN_00ac97a0(RCObj** last, RCObj** first, RCObj** d)
{
    while (first != last) {
        RCObj* s = *(RCObj**)(first - 1);
        RCObj* old = d[-1];
        --first;
        --d;
        if (s != old) {
            if (s) s->AddRef();
            *d = s;
            if (old) old->Release();
        }
    }
    return d;
}

// @ 0x00ac97f0
char* FUN_00ac97f0(char* first, char* last, char* d)
{
    while (last != first) {
        char v = last[-8];
        last -= 0xc;
        d -= 0xc;
        d[4] = v;
        RCObj* s = *(RCObj**)(last + 8);
        RCObj* old = *(RCObj**)(d + 8);
        if (s != old) {
            if (s) s->AddRef();
            *(RCObj**)(d + 8) = s;
            if (old) old->Release();
        }
    }
    return d;
}

// @ 0x00ac9850
cLocomotionRequest::cLocomotionRequest()
{
    *(int*)this = 0;
    *(int*)((char*)this + 4) = 0;
    *(int*)((char*)this + 8) = 0;
    *(float*)((char*)this + 0x14) = DAT_0167a390;
    *(float*)((char*)this + 0x18) = DAT_0167a394;
    *(float*)((char*)this + 0x1c) = DAT_0167a398;
    *(float*)((char*)this + 0x20) = 1.0f;
    *(int*)((char*)this + 0x24) = 0;
    *(byte*)((char*)this + 0x4c) = 0;
    *(float*)((char*)this + 0x50) = 0.0f;
    *(float*)((char*)this + 0x54) = 0.0f;
    *(float*)((char*)this + 0x58) = 0.0f;
    *(float*)((char*)this + 0x60) = 2.0f;
    *(float*)((char*)this + 0x64) = 0.9f;
    *(int*)((char*)this + 0x5c) = 0;
    *(float*)((char*)this + 0x68) = 3.402823466e38f;
    *(float*)((char*)this + 0x6c) = 0.0f;
    *(int*)((char*)this + 0x70) = 0;
}

// @ 0x00ac98e0
void FUN_00ac98e0(int* p)
{
    DAT_01565cfc = 1;
    DAT_01565ce0 = FUN_00ac98e0_readfloat(p, 0x54ba6b0, 0x40a00000);
    DAT_01565ce4 = FUN_00ac98e0_readfloat(p, 0x4ff9582, 0x41200000);
    DAT_01565ce8 = FUN_00ac98e0_readfloat(p, 0x4ffccf5, 0x41f00000);
    {
        float a = 0.5f;
        int out[2];
        FUN_00ac8f00((float*)out, p, 0x5008313, 0.0f, a);
        DAT_01565d54 = out[0];
        DAT_01565d58 = out[1];
    }
    DAT_01565cec = FUN_00ac98e0_readfloat(p, 0x5008412, 0x42c80000);
    {
        int v;
        if (!p) v = 5;
        else if (!(*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, 0x500849f, (void**)&p)) v = 5;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 10 && t != 0x10) v = DAT_0164dc58;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)((t != 0 ? -1 : 0) & (int)p);
        }
        DAT_01565cf0 = v;
    }
    DAT_01565cf8 = FUN_00ac98e0_readfloat(p, 0x508af89, 0x41f00000);
    {
        float a = 100.0f, b = 150.0f;
        int out[2];
        FUN_00ac8f00((float*)out, p, 0x509beb7, a, b);
        DAT_01565d5c = out[0];
        DAT_01565d60 = out[1];
    }
    {
        int v;
        if (!p) v = 100;
        else if (!(*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, 0x5c8390d, (void**)&p)) v = 100;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 9 && t != 0x10) v = DAT_015d9c68;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)((t != 0 ? -1 : 0) & (int)p);
        }
        DAT_01565d00 = v;
    }
    {
        int v;
        if (!p) v = 10;
        else if (!(*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, 0x68dc104, (void**)&p)) v = 10;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 9 && t != 0x10) v = DAT_015d9c68;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)((t != 0 ? -1 : 0) & (int)p);
        }
        DAT_01565d04 = v;
    }
    {
        int v;
        if (!p) v = 4;
        else if (!(*(char (__thiscall**)(void*, int, void**))((char*)VT(p) + 0x24))(p, 0x511f4a9, (void**)&p)) v = 4;
        else {
            short t = *(short*)((char*)p + 0x12);
            if (t != 10 && t != 0x10) v = DAT_0164dc58;
            else if (*(byte*)((char*)p + 0x10) & 0x30) v = *(int*)*(int*)p;
            else v = *(int*)((t != 0 ? -1 : 0) & (int)p);
        }
        DAT_01565d08 = v;
    }
}

// @ 0x00ac9d90
void Vec::FUN_00ac9d90()
{
    for (void** p = mpBegin; p < mpEnd; ++p) {
        if (*p) ((CAnim2*)*p)->Release();
    }
    void* base = mpBegin;
    if (base && *(int*)((char*)base - 4) != 0) {
        operator_delete(base);
    }
}

// @ 0x00ac9dd0
void FUN_00ac9dd0(int a, int b)
{
    FUN_00ac9310(a, b, false);
}

// @ 0x00ac9df0
void FUN_00ac9df0(int* self, int* p)
{
    int v = *(int*)((char*)p + 0xc);
    int* q = (int*)(*(void* (__thiscall**)(int*))((char*)VT(self) + 0x20))(self);
    WriteUint32((void*)(*(void* (__thiscall**)(int*))((char*)VT(q) + 0x18))(q), &v, 1, 0);
    int* root = *(int**)((char*)p + 4);
    int* node = (int*)*root;
    int* slot = root;
    if (!node) {
        slot = root + 1;
        while (*slot == 0) ++slot;
        node = (int*)*slot;
    }
    int* end = (int*)root[*(int*)((char*)p + 8)];
    while (node != end) {
        q = (int*)(*(void* (__thiscall**)(int*))((char*)VT(self) + 0x20))(self);
        int nv = *node;
        WriteUint32((void*)(*(void* (__thiscall**)(int*))((char*)VT(q) + 0x18))(q), &nv, 1, 0);
        (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
        char srl[0xa14];
        SP_cVarListSerializer_ctor(srl, node + 1, (void*)0x15661a8, 0x1a80d26);
        SP_cVarListSerializer_Serialize(srl, self);
        (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
        node = (int*)node[0x1a];
        while (!node) {
            node = (int*)slot[1];
            ++slot;
        }
    }
    (*(void (__thiscall**)(int*))((char*)VT(self) + 0x1c))(self);
}

// @ 0x00ac9ef0
bool FUN_00ac9ef0(void* a, int* p)
{
    int* root = *(int**)((char*)p + 4);
    int node = *root;
    int* slot = root;
    if (!node) {
        slot = root + 1;
        while (*slot == 0) ++slot;
        node = *slot;
    }
    int end = root[*(int*)((char*)p + 8)];
    while (node != end) {
        if (node + 4 != 0) {
            ((CSC*)a)->FUN_00695b40((void*)(node + 4), (void*)0x15661a8, L"tAnimalStage");
        }
        node = *(int*)(node + 0x68);
        while (!node) {
            node = slot[1];
            ++slot;
        }
    }
    return 1;
}

// @ 0x00ac9f70
void FUN_00ac9f70(void* obj, int param)
{
    int base = param;
    int v = *(int*)(param + 0xc);
    void* r = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    int val = v;
    void* w = ((void* (__thiscall*)(void*))vc(r, 0x18))(r);
    FUN_0093aa70(w, &val, 1, 0);
    int* buckets = *(int**)(base + 4);
    void* node = (void*)*buckets;
    int* pp = buckets;
    if (!node) {
        pp = buckets + 1;
        int t = buckets[1];
        while (t == 0) { pp++; t = *pp; }
        node = (void*)*pp;
    }
    void* end = (void*)buckets[*(int*)(base + 8)];
    while (node != end) {
        void* r2 = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        int k = *(int*)node;
        int tmp = k;
        void* w2 = ((void* (__thiscall*)(void*))vc(r2, 0x18))(r2);
        FUN_0093aa70(w2, &tmp, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
        void* r3 = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        tmp = *(int*)((char*)node + 4);
        void* w3 = ((void* (__thiscall*)(void*))vc(r3, 0x18))(r3);
        FUN_0093aa70(w3, &tmp, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
        node = (void*)*((int*)node + 2);
        while (node == 0) {
            pp = pp + 1;
            node = (void*)*pp;
        }
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca0c0
void __cdecl FUN_00aca0c0(void** arr, void* arg2, int n, int holeIndex, void* arg5, SortValue value)
{
    int child = 2 * holeIndex + 2;
    if (child < n) {
        do {
            void* left  = arr[child - 1] ? (void*)((char*)arr[child - 1] + 0x120) : 0;
            void* right = arr[child]     ? (void*)((char*)arr[child]     + 0x120) : 0;
            if (value.FUN_00ac0730(right, left)) --child;
            void* moved = arr[child];
            void* old   = arr[holeIndex];
            if (moved != old) {
                if (moved) ((void (__thiscall*)(void*))vc(moved, 0))(moved);
                arr[holeIndex] = moved;
                if (old) ((void (__thiscall*)(void*))vc(old, 4))(old);
            }
            holeIndex = child;
            child = 2 * child + 2;
        } while (child < n);
        if (child == n) {                       // lone left child
            void* moved = arr[child - 1];
            void* old   = arr[holeIndex];
            if (moved != old) {
                if (moved) ((void (__thiscall*)(void*))vc(moved, 0))(moved);
                arr[holeIndex] = moved;
                if (old) ((void (__thiscall*)(void*))vc(old, 4))(old);
            }
            holeIndex = child - 1;
        }
    }
    if (arg5) ((void (__thiscall*)(void*))vc(arg5, 0))(arg5);
    FUN_00ac93c0(arr, arg2, holeIndex, arg5, value);
    if (arg5) ((void (__thiscall*)(void*))vc(arg5, 4))(arg5);
}

// @ 0x00aca1f0
int* FUN_00aca1f0(int* begin, int* end, int* key)
{
    int n = (int)((char*)end - (char*)begin) >> 5;
    if (n > 0) {
        do {
            int h = n >> 1;
            if (begin[h * 8] < *key) {
                begin = begin + h * 8 + 8;
                h = n + (-1 - h);
            }
            n = h;
        } while (n > 0);
    }
    return begin;
}

// @ 0x00aca2f0
int FUN_00aca2f0(uchar* p, uchar* end, int out)
{
    for (; p != end; p += 0x20) {
        *(void**)(p + 4) = (void*)0x145a164;
        uchar* b = *(uchar**)(p + 0xc);
        uchar* e2 = *(uchar**)(p + 0x10);
        for (; b < e2; b += 0xc) {
            void* o = *(void**)b;
            ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
        }
        uchar* base = *(uchar**)(p + 0xc);
        if (base && *(int*)(base - 4) != 0)
            operator_delete(base);
        out += 0x20;
    }
    return out;
}

// @ 0x00aca360
void GameCreature::FUN_00aca360(void* other)
{
    uchar* self = (uchar*)this;
    unsigned tag = ((unsigned (__thiscall*)(void*))vc(other, 0x20))(other);

    if (tag == 0x18eb45e) {
        // ---- path A (0xaca52e): release other's handle from the list at this+0xe0 ----
        uchar* list = self + 0xe0;
        int handle = *(int*)((uchar*)other + 0x24);
        void* at = 0;
        FUN_00645ed0(list, 0, &at, &handle);
        if (at) {
            void** begin = *(void***)(list + 4);
            int size = *(int*)(list + 8);
            if (at != begin[size]) {
                if (--*(int*)((uchar*)at + 4) <= 0)
                    FUN_01068380(list, 0, at, at);
            }
        }
    } else if (tag == 0x18eb4b7) {
        if (FUN_00b5b800() == 0x1654c02) return;

        uchar* mgr = *(uchar**)(self + 0xa4);
        uchar* c = mgr ? *(uchar**)(mgr + 0xaf0) : 0;
        if (c) {
            float* p1 = (float*)((void* (__thiscall*)(void*))vc(c + 0x120, 0x2c))(c + 0x120);
            float* p2 = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
            float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
            float d = FSQRT(dx * dx + dy * dy + dz * dz);
            uchar* rf = (uchar*)((void* (__thiscall*)(void*))vc(c, 0x6c))(c);
            if (d > *(float*)(rf + 0x25c) + DAT_0140f334) {
                FUN_00d5ccf0(mgr, 0, other);
                return;
            }
        }

        uchar* it  = *(uchar**)(self + 0xa8);
        uchar* end = *(uchar**)(self + 0xac);
        while (it != end) {
            void* o = *(void**)it;
            if (o) {
                void* a = FUN_00c8e820(o, 0, 0);
                void* b = FUN_00c0bbd0(other, 0);
                if (a == b) {
                    float* p1 = (float*)((void* (__thiscall*)(void*))vc((uchar*)o + 0x120, 0x2c))((uchar*)o + 0x120);
                    float* p2 = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
                    float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
                    float d = FSQRT(dx * dx + dy * dy + dz * dz);
                    float r = ((float (__thiscall*)(void*))vc(o, 0x60))(o);
                    if (2.0f * r >= d) {
                        float* p = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
                        ((void (__thiscall*)(void*, int, void*, int, void*))*(void**)((uchar*)other + 0xe8))(other, 0, o, 1, p);
                        FUN_00c96e80(o, 0, other);
                        return;
                    }
                }
            }
            it += 0x18;
        }
        FUN_00d576d0(other);
        return;
    } else {
        return;
    }

    // ---- common range check reached from path A (0xaca57e) ----
    uchar* mgr = *(uchar**)(self + 0xa4);
    uchar* c = mgr ? *(uchar**)(mgr + 0xaf0) : 0;
    if (!c) return;
    if (((char (__thiscall*)(void*))vc(c, 0x2c))(c)) return;
    float* p1 = (float*)((void* (__thiscall*)(void*))vc(c + 0x120, 0x2c))(c + 0x120);
    float* p2 = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
    float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
    float d = FSQRT(dx * dx + dy * dy + dz * dz);
    uchar* rf = (uchar*)((void* (__thiscall*)(void*))vc(c, 0x6c))(c);
    if (d > *(float*)(rf + 0x25c))
        FUN_00d5f780(mgr, 0, other);
}

// @ 0x00aca620
void __cdecl FUN_00aca620(void* obj, HashTable* ht)
{
    ht->FUN_00693230(ht->mpBuckets, ht->mBucketCount);
    ht->mCount = 0;
    int count = 0;
    void* sub = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    void* rdr = ((void* (__thiscall*)(void*))vc(sub, 0x18))(sub);
    FUN_0093a780(rdr, &count, 1, 0);
    for (int i = 0; i < count; ++i) {
        int key = 0;
        void* ks = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        void* kr = ((void* (__thiscall*)(void*))vc(ks, 0x18))(ks);
        FUN_0093a780(kr, &key, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);

        int value = 0;
        void* vs = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        void* vr = ((void* (__thiscall*)(void*))vc(vs, 0x18))(vs);
        FUN_0093a780(vr, &value, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);

        HTPair pair;
        pair.mKey = key;
        pair.mValue = value;
        HTIter out;
        ht->FUN_007c3990(&out, &pair, 0);
        if (!out.mbInserted) out.mpNode->mValue = value;
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca730
void FUN_00aca730(void* obj, int* vec)
{
    void* r = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    int n = (vec[1] - vec[0]) >> 2;
    void* w = ((void* (__thiscall*)(void*))vc(r, 0x18))(r);
    FUN_0093aa70(w, &n, 1, 0);
    int* b = (int*)vec[0];
    int* e = (int*)vec[1];
    for (; b != e; b++) {
        uint v = 0;
        if (*b) v = ((uint (__thiscall*)(void*, int))vc((void*)*b, 0xc))((void*)*b, 0x179c807);
        ((void (__thiscall*)(void*, uint))vc(obj, 0x2c))(obj, v);
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca7b0
void __stdcall FUN_00aca7b0(uchar* p, uchar* end)
{
    if (p < end) {
        uint n = (((uint)(end - p) - 1) >> 5) + 1;
        do {
            *(void**)(p + 4) = (void*)0x145a164;
            uchar* b = *(uchar**)(p + 0xc);
            uchar* e2 = *(uchar**)(p + 0x10);
            for (; b < e2; b += 0xc) {
                void* o = *(void**)b;
                ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
            }
            uchar* base = *(uchar**)(p + 0xc);
            if (base && *(int*)(base - 4) != 0)
                operator_delete(base);
            p += 0x20;
        } while (--n);
    }
}

// @ 0x00aca820
void __stdcall FUN_00aca820(int* p, int* end)
{
    for (; p < end; p += 6) {
        int* e2 = (int*)p[2];
        for (int* it = (int*)p[1]; it < e2; it++) {
            void* o = (void*)*it;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
        int b = p[1];
        if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
}

// @ 0x00aca970
int* VecCopyStub::FUN_00aca970(int* src)
{
    int* obj = (int*)this;
    void* o = *(void**)src;
    *obj = (int)o;
    if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
    ((VecObj*)((char*)this + 4))->FUN_00b93c60((src[2] - src[1]) >> 2, src + 4);
    int* ret = 0;
    FUN_00829110(&ret, (void*)src[1], (void*)src[2], (void*)obj[1], (void*)src);
    obj[2] = (int)ret;
    return obj;
}

// @ 0x00acab70
int FUN_00acab70(int* p, int* end, int out)
{
    for (; p != end; p += 6) {
        int* e2 = (int*)p[2];
        for (int* it = (int*)p[1]; it < e2; it++) {
            void* o = (void*)*it;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
        int b = p[1];
        if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        out += 0x18;
    }
    return out;
}

// @ 0x00acabe0
char FUN_00acabe0(void* pSave, const char* pFileName, const void* pValue, const void* pArg)
{
    cWideString cmdLine;
    WSTR_SET_EMPTY_ODD(cmdLine);
    FUN_00694fc0(&cmdLine, pValue);

    char result = 1;
    if (cmdLine.mpBegin != cmdLine.mpEnd) {
        cWideString fileName;
        if (pFileName) {
            FUN_0093c5a0(&fileName, pFileName, -1);
        } else {
            fileName.mpBegin = DAT_01667bac;
            fileName.mpEnd = DAT_01667bac;
            fileName.mpCapacityEnd = DAT_01667bac + 1;
        }
        cWideString name;
        name.FUN_0056e2d0(&fileName);
        WSTR_FREE(fileName);

        cWideString typedName;
        FUN_0093c6d0(&typedName, &cmdLine);

        char ok;
        if (name.mpBegin == name.mpEnd) {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, pArg);
        } else {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, name.mpBegin);
            if (DAT_015d8b54 && ok)
                ok = ((char (__thiscall*)(void*, const void*, const void*))vc(pSave, 8))(pSave, DAT_013f36bc, pArg);
        }
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0xc))(pSave, typedName.mpBegin);
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 4))(pSave,
                     name.mpBegin == name.mpEnd ? pArg : (const void*)name.mpBegin);
        result = ok ? 1 : 0;
        WSTR_FREE(typedName);
        WSTR_FREE(name);
    }
    WSTR_FREE_CMDLINE(cmdLine);
    return result;
}

// @ 0x00acadb0
char FUN_00acadb0(void* pSave, const char* pFileName, const void* pValue, const void* pArg)
{
    cWideString cmdLine;
    WSTR_SET_EMPTY_ODD(cmdLine);
    FUN_00695010(&cmdLine, pValue);

    char result = 1;
    if (cmdLine.mpBegin != cmdLine.mpEnd) {
        cWideString fileName;
        if (pFileName) {
            FUN_0093c5a0(&fileName, pFileName, -1);
        } else {
            fileName.mpBegin = DAT_01667bac;
            fileName.mpEnd = DAT_01667bac;
            fileName.mpCapacityEnd = DAT_01667bac + 1;
        }
        cWideString name;
        name.FUN_0056e2d0(&fileName);
        WSTR_FREE(fileName);

        cWideString typedName;
        FUN_0093c6d0(&typedName, &cmdLine);

        char ok;
        if (name.mpBegin == name.mpEnd) {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, pArg);
        } else {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, name.mpBegin);
            if (DAT_015d8b56 && ok)
                ok = ((char (__thiscall*)(void*, const void*, const void*))vc(pSave, 8))(pSave, DAT_013f36bc, pArg);
        }
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0xc))(pSave, typedName.mpBegin);
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 4))(pSave,
                     name.mpBegin == name.mpEnd ? pArg : (const void*)name.mpBegin);
        result = ok ? 1 : 0;
        WSTR_FREE(typedName);
        WSTR_FREE(name);
    }
    WSTR_FREE_CMDLINE(cmdLine);
    return result;
}

// @ 0x00acaf80
char FUN_00acaf80(void* pSave, const char* pFileName, const void* pValue, const void* pArg)
{
    cWideString cmdLine;
    WSTR_SET_EMPTY_ODD(cmdLine);
    FUN_00694c10(&cmdLine, pValue);

    char result = 1;
    if (cmdLine.mpBegin != cmdLine.mpEnd) {
        cWideString fileName;
        if (pFileName) {
            FUN_0093c5a0(&fileName, pFileName, -1);
        } else {
            fileName.mpBegin = DAT_01667bac;
            fileName.mpEnd = DAT_01667bac;
            fileName.mpCapacityEnd = DAT_01667bac + 1;
        }
        cWideString name;
        name.FUN_0056e2d0(&fileName);
        WSTR_FREE(fileName);

        cWideString typedName;
        FUN_0093c6d0(&typedName, &cmdLine);

        char ok;
        if (name.mpBegin == name.mpEnd) {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, pArg);
        } else {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, name.mpBegin);
            if (DAT_015d8b59 && ok)
                ok = ((char (__thiscall*)(void*, const void*, const void*))vc(pSave, 8))(pSave, DAT_013f36bc, pArg);
        }
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0xc))(pSave, typedName.mpBegin);
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 4))(pSave,
                     name.mpBegin == name.mpEnd ? pArg : (const void*)name.mpBegin);
        result = ok ? 1 : 0;
        WSTR_FREE(typedName);
        WSTR_FREE(name);
    }
    WSTR_FREE_CMDLINE(cmdLine);
    return result;
}

// @ 0x00acb150
void* FourVecDtorStub::FUN_00acb150(uchar flags)
{
    void* self = this;
    *(void**)self = (void*)0x145a184;
    FUN_00ae6970((uchar*)self + 0x50);
    FUN_00ae6970((uchar*)self + 0x3c);
    FUN_00ae6970((uchar*)self + 0x28);
    FUN_00ae6970((uchar*)self + 0x14);
    if (flags & 1) operator_delete(self);
    return self;
}

// @ 0x00acb190
void __fastcall FUN_00acb190(void* self)
{
    *(int*)((uchar*)self + 4) -= 0x18;
    uchar* v = *(uchar**)((uchar*)self + 4);
    FUN_00ae6970(v + 4);
    void* o = *(void**)v;
    if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
}

// @ 0x00acb490
void* VO::FUN_00acb490(int* src)
{
    int* p = (int*)this;
    int tmp = (int)src;
    p[0] = 0x145a184;
    p[1] = src[1];
    p[2] = src[2];
    p[3] = src[3];
    p[4] = src[4];
    ((XC*)((uchar*)p + 0x14))->FUN_00b93c60((src[6] - src[5]) >> 2, (uchar*)src + 0x20);
    FUN_00829110(&tmp, (void*)src[5], (void*)src[6], (void*)p[5], (void*)tmp);
    p[6] = tmp;
    ((XC*)((uchar*)p + 0x28))->FUN_00b93c60((src[11] - src[10]) >> 2, (uchar*)src + 0x34);
    FUN_00829110(&tmp, (void*)src[10], (void*)src[11], (void*)p[10], (void*)tmp);
    p[0xb] = tmp;
    ((XC*)((uchar*)p + 0x3c))->FUN_00b93c60((src[0x10] - src[0xf]) >> 2, (uchar*)src + 0x48);
    FUN_00829110(&tmp, (void*)src[0xf], (void*)src[0x10], (void*)p[0xf], (void*)tmp);
    p[0x10] = tmp;
    ((XC*)((uchar*)p + 0x50))->FUN_00b93c60((src[0x15] - src[0x14]) >> 2, (uchar*)src + 0x5c);
    FUN_00829110(&tmp, (void*)src[0x14], (void*)src[0x15], (void*)p[0x14], (void*)tmp);
    p[0x15] = tmp;
    return p;
}

// @ 0x00acb7c0
void VO::FUN_00acb7c0(void* a2, void* a3)
{
    int* p = (int*)this;
    int* it = (int*)FUN_00ac89e0(a3, *(void**)((uchar*)p + 4), a2);
    int* end = *(int**)((uchar*)p + 4);
    for (; it < end; it++) {
        if (*it) ((XC*)*it)->FUN_00a05270();
    }
    int n = (int)((char*)a3 - (char*)a2) >> 2;
    *(int*)((uchar*)p + 4) -= n * 4;
}

// @ 0x00acbaf0
void* VO::FUN_00acbaf0(int* src)
{
    uchar* d = (uchar*)this;
    *(int*)d = *src;
    *(void**)(d + 4) = (void*)0x145a164;
    *(d + 8) = *(uchar*)((uchar*)src + 8);
    *(d + 9) = *(uchar*)((uchar*)src + 9);
    ((XC*)(d + 0xc))->FUN_00aca9d0((uchar*)src + 0xc);
    return d;
}

// @ 0x00acbb20
void* FUN_00acbb20(uchar* p, uchar* end, uchar* out)
{
    if (p != end) {
        uchar* o = out;
        do {
            if (o) {
                *(int*)o = *(int*)p;
                *(void**)(o + 4) = (void*)0x145a164;
                *(o + 8) = *(p + 8);
                *(o + 9) = *(p + 9);
                ((XC*)(o + 0xc))->FUN_00aca9d0(p + 0xc);
            }
            p += 0x20; o += 0x20;
        } while (p != end);
        return o;
    }
    return out;
}

// @ 0x00acbd90
int* VO::FUN_00acbd90(int* other)
{
    int* v = (int*)this;
    if (other != v) {
        int src0 = *other;
        uint n2 = (other[1] - src0) / 0xc;
        int dst0 = *v;
        if ((uint)((v[2] - dst0) / 0xc) < n2) {
            int mem = (int)FUN_00acaa50(n2, (void*)src0, (void*)other[1]);
            FUN_00ac8930((void*)*v, (void*)v[1]);
            int old = *v;
            if (old && *(int*)(old - 4) != 0) operator_delete((void*)old);
            v[2] = mem + n2 * 0xc;
            *v = mem;
            v[1] = mem + n2 * 0xc;
            return v;
        }
        uint u3 = (v[1] - dst0) / 0xc;
        if (u3 < n2) {
            FUN_00ac9740((void*)src0, (void*)(src0 + u3 * 0xc), (void*)dst0);
            int p = other[1];
            int tmp = p;
            FUN_00ac94c0(&tmp, (void*)(*other + ((v[1] - *v) / 0xc) * 0xc), (void*)p, (void*)v[1], (void*)p);
            v[1] = *v + n2 * 0xc;
            return v;
        }
        int r = (int)FUN_00ac9740((void*)src0, (void*)other[1], (void*)dst0);
        FUN_00ac8930((void*)r, (void*)v[1]);
        v[1] = *v + n2 * 0xc;
    }
    return v;
}

// @ 0x00acbed0
int VO::FUN_00acbed0(int a2, int a3)
{
    int* p = (int*)this;
    int* it = (int*)FUN_00ac9740((void*)a3, *(void**)((uchar*)p + 4), (void*)a2);
    int* end = *(int**)((uchar*)p + 4);
    for (; it < end; it += 3) {
        void*** obj = (void***)it;
        ((void (__thiscall*)(void*, int))((*obj)[0]))(obj, 0);
    }
    int n = (a2 - a3) / 0xc;
    *(int*)((uchar*)p + 4) += n * 0xc;
    return a2;
}

// @ 0x00acc2d0
int* FUN_00acc2d0(int* p, int* end, int* out)
{
    if (p == end) return out;
    do {
        int* a = (int*)*p;
        int* b = (int*)*out;
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *out = (int)a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        ((XC_s00ac_c140*)(p + 1))->FUN_01011cc0(out + 1);
        p += 6; out += 6;
    } while (p != end);
    return out;
}

// @ 0x00acc330
int* FUN_00acc330(int end, int begin, int* out)
{
    if (begin == end) return out;
    int nxt;
    do {
        int* a = *(int**)(end - 0x18);
        int* b = (int*)out[-6];
        int nxt = end - 0x18;
        out -= 6;
        if (a != b) {
            if (a) ((void (__thiscall*)(void*))vc(a, 0))(a);
            *out = (int)a;
            if (b) ((void (__thiscall*)(void*))vc(b, 4))(b);
        }
        ((XC_s00ac_c140*)(end - 0x14))->FUN_01011cc0(out + 1);
        end = nxt;
    } while (nxt != begin);
    return out;
}

// @ 0x00acc390
void VO_s00ac_c140::FUN_00acc390()
{
    LivingUniverse* lu = (LivingUniverse*)FUN_01021260();
    Planet* planet = lu->mpPlanet;

    // Stable compaction: drop entries whose +0x28 byte has bit 2 set.
    uint kept = 0;
    while (kept < (uint)(planet->mpRareEnd - planet->mpRareBegin)) {
        RareEntry* cur = planet->mpRareBegin + kept;
        if ((cur->mKind28 & 4) == 0) {
            kept++;
        } else {
            *cur = *(planet->mpRareEnd - 1);
            planet->mpRareEnd--;
        }
    }

    HashNode** slot = mpBuckets;
    HashNode* node = *slot;
    if (!node) {
        do {
            slot++;
            node = *slot;
        } while (!node);
    }
    HashNode* stop = mpBuckets[mBucketEnd];

    while (node != stop) {
        int n = (int)(node->mpEnd - node->mpBegin);
        for (int i = 0; i < n; i++) {
            StageGroup* g = (StageGroup*)node->mpBegin[i];
            for (void** it = g->mpStagesBegin; it != g->mpStagesEnd; it++) {
                void* stage = *it;
                if (!stage || !((CStage*)stage)->canDo()) continue;

                Vec3* a = (Vec3*)vcall0p(&((CStage*)stage)->mSubC0, 0x2c);
                Vec3* b = (Vec3*)((CStage*)stage)->getFrame();

                RareEntry e;
                e.mPos = *a;
                e.mZero18 = 0;
                e.mOther = *b;
                e.mKind28 = 0x24;

                if (planet->mpRareEnd < planet->mpRareCap)
                    *planet->mpRareEnd++ = e;
                else
                    ((RareVec*)&planet->mpRareBegin)->grow(planet->mpRareEnd, &e);
            }
        }

        node = node->mpNext;
        while (!node) {
            slot++;
            node = *slot;
        }
    }
}

// @ 0x00acc610
void VO_s00ac_c140::FUN_00acc610(void* p)
{
    if (!p) return;
    if (objType(p) != 0x18eb4b7) return;
    int n = (int)(mpListsEnd - mpListsBegin);
    if (n <= 0) return;

    StageList* b = mpListsBegin;
    for (int i = 0; i < n; i++, b++) {
        void** a = b->mpBegin;
        void** e = b->mpEnd;
        while (a != e && *a != p) a++;
        if (a == e) continue;

        // remove every occurrence of p; the tail is then released
        void** out = a;
        for (void** s = a + 1; s != e; s++) {
            if (*s != p) {
                *out = *s;
                out++;
            }
        }
        for (void** s = out; s != e; s++)
            if (*s) objRelease(*s);
        b->mpEnd = out;
        vcall2i(b->mpOwner, 0x9c, p, 1);
        return;
    }
}

// @ 0x00acc700
void VO_s00ac_c140::FUN_00acc700(void* p, float a, float b)
{
    int* v = (int*)this;
    uchar* cur = (uchar*)v[9];
    if (cur < (uchar*)v[10]) {
        v[9] = (int)(cur + 0x14);
    } else {
        uchar local[0x14];
        ((XC_s00ac_c140*)(v + 8))->FUN_00acb680(cur, local);
    }
    uchar* e = (uchar*)(*(int*)((uchar*)this + 0x24) - 0x14);
    *(int*)e = *(int*)p;
    *(int*)(e + 4) = *(int*)((uchar*)p + 4);
    *(int*)(e + 8) = *(int*)((uchar*)p + 8);
    *(float*)(e + 0xc) = a * a;
    *(float*)(e + 0x10) = b * b;
}

// @ 0x00acc770
void VO_s00ac_c140::FUN_00acc770()
{
    uchar* p = (uchar*)this;
    int n = (*(int*)(p + 0x11c) - *(int*)(p + 0x118)) >> 2;
    for (int i = 0; i < n; i++) {
        int* o = (int*)FUN_00b33f40();
        ((void (__thiscall*)(void*, int))vc(o, 0x3c))(o, *(int*)(*(int*)(p + 0x118) + i * 4));
    }
    int b = *(int*)(p + 0x118);
    int e = *(int*)(p + 0x11c);
    int* it = (int*)FUN_00ac89e0((void*)e, (void*)e, (void*)b);
    int* end = *(int**)(p + 0x11c);
    for (; it < end; it++) if (*it) ((XC_s00ac_c140*)*it)->FUN_00a05270();
    *(int*)(p + 0x11c) -= (e - b) >> 2 << 2;
}

// @ 0x00acc800
void __stdcall FUN_00acc800(KeyVec* v)
{
    LivingUniverse* lu = (LivingUniverse*)FUN_01021260();
    if (!lu) return;

    Planet* planet = lu->mpPlanet;
    int n = (int)(planet->mpKeyEnd - planet->mpKeyBegin);
    void* mode = FUN_00b5b800_s00ac_c140();
    if (mode == DAT_01654c04) n = 5;

    v->reserve((int)(v->mpEnd - v->mpBegin) + n);
    if (n <= 0) return;

    Key3* src = planet->mpKeyBegin;
    for (int i = 0; i < n; i++, src++) {
        if (v->mpEnd < v->mpCap)
            *v->mpEnd++ = *src;
        else
            v->pushSlow(v->mpEnd, src);
    }
}

// @ 0x00acc9b0
void VO_s00ac_c140::FUN_00acc9b0(uint n)
{
    int* v = (int*)this;
    int* b = (int*)v[0];
    int* e = (int*)v[1];
    if ((uint)(e - b) < n) {
        int add = n - (int)(e - b);
        int z = 0;
        ((XC_s00ac_c140*)v)->FUN_00acb930(e, add, &z);
        return;
    }
    ((XC_s00ac_c140*)v)->FUN_00acb7c0(b + n, e);
}

// @ 0x00accd70
void FUN_00accd70(int arr, uint n)
{
    for (uint i = 0; i < n; i++) {
        int node = *(int*)(arr + i * 4);
        while (node != 0) {
            int next = *(int*)(node + 0x68);
            *(void**)(node + 4) = (void*)0x145a184;
            int* e = *(int**)(node + 0x58);
            for (int* it = *(int**)(node + 0x54); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            int b = *(int*)(node + 0x54);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x44);
            for (int* it = *(int**)(node + 0x40); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x40);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x30);
            for (int* it = *(int**)(node + 0x2c); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x2c);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            e = *(int**)(node + 0x1c);
            for (int* it = *(int**)(node + 0x18); it < e; it++) {
                void* o = (void*)*it;
                if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
            }
            b = *(int*)(node + 0x18);
            if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
            operator_delete((void*)node);
            node = next;
        }
        *(int*)(arr + i * 4) = 0;
    }
}
