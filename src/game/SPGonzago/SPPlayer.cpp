// src/game/SPGonzago/SPPlayer.cpp -- migrated from slice(s) s00c7b120, s00c7a1f0, s00c77380, s00c75e70, s00ba2590, s01351ae0, s01350ca0, s00c7c0c0, s00c793e0, s00c784c0, s00c74d30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPPlayer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cEmpire.h"
#include "SP/cGameNounManager.h"
#include "SP/cStarManager.h"
#include "SP/cPlayer.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cGonzagoTimer.h"
#include "SP/cTribe.h"
#include "SP/PlayerPlanetData.h"
#include "SP/cCollectableItems.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyManager.h"
#include "SP/cSpatialObject.h"
#include "SP/cVarListSerializer.h"
#include <math.h>
#include <string.h>
#include <new>
#include <intrin.h>
#include "SP/cEmbassyData.h"
#include "SP/cSpacePlayerWarData.h"
#include "SP/cSPTimer.h"
#include "EA/ResourceMan/Key.h"

// ---- items of slice s00c74d30 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char u8;
typedef int i32;
struct cGameNounManager {
    i32   GetKind();                               // 0x00bb9ae0
    void* GetAvatar();                             // 0x00b1fdb0
};
struct cStarManager {                              // returned by SP::StarManager(avatar)
    void* GetEmpireByID();                         // 0x00ba9370
};
struct cEmpire {
    void  SetValue(i32 v);                         // 0x00c322f0
};
void* __stdcall FUN_00b3d2a0(void*);                // 0x00b3d2a0 (SP::StarManager; one stack arg, caller pops)
struct cDepthCounter {
    u8   mPad0000[0x124c];
    i32  mDepth;                                   // 0x124c
    i32  mTotal;                                   // 0x1250

    void Increment(bool countIt);                  // 0x00c755c0
    void Decrement(bool countIt);                  // 0x00c755f0
};
// ---- items of slice s00c74d30 end

// ---- items of slice s00c784c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
void __cdecl operator_delete_array(void* pBlock);           // 0x00f47380
struct StarVector {
    int32_t* mpBegin;           // +0x00
    int32_t* mpEnd;             // +0x04
    int32_t* mpCapacity;        // +0x08
};
class cEmpire_s00c7_84c0 {
public:
    StarVector* GetStars();                         // 0x00c308d0
};
class cStarManager_s00c7_84c0 {
public:
    cEmpire_s00c7_84c0* GetEmpireByID(int32_t nEmpireId);      // 0x00ba9370
    void*    FUN_00baf700(cEmpire_s00c7_84c0* pEmpire);        // 0x00baf700
};
cStarManager_s00c7_84c0* __cdecl StarManager();                // 0x00b3d2a0
class cSPSpaceCombatTuning {
public:
    float GetWarSurrenderThreshold();               // 0x01029c30
};
cSPSpaceCombatTuning* __cdecl GetSpaceCombatTuning();   // 0x01029940
class cRandom {
public:
    double RandomDoubleUniform();                   // 0x009360d0
};
extern cRandom gRandom;                             // 0x01601760
template <typename T>
void __cdecl GetPropertyT(void* pObject, uint32_t nPropertyId, T* pValue);   // 0x0040cf10
struct WarEventRecord {
    uint8_t mPad00[0x4c];       // +0x000
    int32_t mnLimit;            // +0x04c  clamped denominator of the war score
    int32_t mnProgress;         // +0x050
    int32_t mnBaseline;         // +0x054
};
class cWarEventSet {
public:
    uint32_t mPad00;            // +0x00
    WarEventRecord* mpEnd;      // +0x04  address of this word is the end() sentinel
    void Find(WarEventRecord** ppResult, const int32_t* pnKey);     // 0x00e5c780
    WarEventRecord* End() const { return (WarEventRecord*)&mpEnd; }
};
namespace SP {
class cPlayer_s00c7_84c0 {
public:
    bool TestPlayerWarVictory(int32_t nEmpireId);       // 0x00c784c0
    void NoteWarEndedWithPlayer(cEmpire_s00c7_84c0* pEmpire);      // 0x00c78450

private:
    uint8_t mPad00[0x11f8];         // +0x0000
    cWarEventSet mWarEvents;        // +0x11f8
};  // namespace SP
}
class FixedPoolBase {
public:
    void* mpHead;               // +0x00
    void* mpTail;               // +0x04
    void* mpEnd;                // +0x08
    int32_t mnSize;             // +0x0c
    void Init(void* pPoolBegin, int32_t nPoolSize, int32_t nNodeSize,
              int32_t nNodeAlignment, int32_t nAlignmentOffset);     // 0x00921260
};
struct FixedHashtableAlloc {
    void* mpPoolHead;           // +0x00
    float mfLoadFactor;         // +0x04
    void* mpPoolBegin;          // +0x08
    void* mpPoolEnd;            // +0x0c
    int32_t mnNodeSize;         // +0x10
    void* mpBuckets;            // +0x14
};
uint32_t __cdecl GetBucketCountFor(uint32_t nRequested);        // 0x00921340
uint32_t __cdecl GetRehashBucketCount(uint32_t nElementCount);  // 0x009213c0
class cFixedHashtableBase {
public:
    void Construct(uint32_t nBucketCount, uint32_t nArg1, const FixedHashtableAlloc& rAlloc);   // 0x00c76a80
    void ConstructKeyed(uint32_t nBucketCount, uint32_t nArg1, const FixedHashtableAlloc& rAlloc);  // 0x00c76b30
    void ConstructMap(uint32_t nBucketCount, uint32_t nArg1, const FixedHashtableAlloc& rAlloc);    // 0x00c76e60

    void DoFreeNodes(uint32_t nBucketCount);        // 0x00c76440
    void DoFreeNodesKeyed(uint32_t nBucketCount);   // 0x00b5d220
    void DoFreeNodesMap(uint32_t nBucketCount);     // 0x00c76610

    uint8_t mPad00[0x08];       // +0x00
    uint32_t mnBucketCapacity;  // +0x08
    uint32_t mnBucketCount;     // +0x0c
    float mfLoadFactor;         // +0x10
    float mfGrowthFactor;       // +0x14
    uint32_t mnElementCount;    // +0x18
    uint8_t mPad1c[0x34 - 0x1c];        // +0x1c
    void* mpBuckets;            // +0x34
};
class cResourceKeySet {
public:
    cResourceKeySet* Construct(uint32_t nArg1, uint32_t nArg2);     // 0x00c785e0
private:
    cFixedHashtableBase mHashtable;     // +0x00
    uint8_t mPad38[0x13c - 0x38];       // +0x38
    uint8_t mPool[0x400];               // +0x13c
};
class cResourceKeyTable {
public:
    cResourceKeyTable* Construct(uint32_t nArg1, uint32_t nArg2);   // 0x00c786b0
private:
    cFixedHashtableBase mHashtable;     // +0x00
    uint8_t mPad38[0x23c - 0x38];       // +0x38
    uint8_t mPool[0x600];               // +0x23c
};
class cUInt32Map {
public:
    cUInt32Map* Construct(uint32_t nArg1, uint32_t nArg2);          // 0x00c78790
private:
    cFixedHashtableBase mHashtable;     // +0x00
    uint8_t mPad38[0xbc - 0x38];        // +0x38
    uint8_t mPool[0x300];               // +0xbc
};
class WString {
public:
    wchar_t* mpBegin;           // +0x00
    wchar_t* mpEnd;             // +0x04
    wchar_t* mpCapacity;        // +0x08

    WString();                                  // 0x00579a90  (RangeInitialize(0))
    WString(const WString& rOther);             // 0x0056e2d0
    ~WString()
    {
        if (mpEnd - mpBegin > 1 && mpBegin != nullptr)
            operator_delete_array(mpBegin);
    }

    bool empty() const { return mpBegin == mpEnd; }
    const wchar_t* c_str() const { return mpBegin; }
};
WString __cdecl EAConvertToString16(const char* pText, int32_t nLength);    // 0x0093c5a0
class cSerializer {
public:
    virtual void BeginContainer(const wchar_t* pszName);    // +0x00
    virtual void EndContainer(const wchar_t* pszName);      // +0x04
};
bool __cdecl WriteTypedValue32(cSerializer* pSerializer, int32_t nFlags,
                               const void* pValue, const wchar_t* pszType);     // 0x0057c770
bool __cdecl WriteTypedValueBool(cSerializer* pSerializer, int32_t nFlags,
                                 const void* pValue, const wchar_t* pszType);   // 0x0057c940
bool __cdecl WriteTypedValuePair(cSerializer* pSerializer, int32_t nFlags,
                                 const void* pValue);                           // 0x00ac8050
struct Int32List {
    int32_t* mpBegin;           // +0x00
    int32_t* mpEnd;             // +0x04
    int32_t* mpCapacity;        // +0x08
};
struct KeyPair8 {
    int32_t mnKey;              // +0x00
    int32_t mnValue;            // +0x04
};
struct KeyPair16 {
    uint8_t mPad00[0x0c];       // +0x00
    int32_t mnValue;            // +0x0c
};
struct PairList8 {
    KeyPair8* mpBegin;          // +0x00
    KeyPair8* mpEnd;            // +0x04
    KeyPair8* mpCapacity;       // +0x08
};
struct PairList16 {
    KeyPair16* mpBegin;         // +0x00
    KeyPair16* mpEnd;           // +0x04
    KeyPair16* mpCapacity;      // +0x08
};
struct WidePair {
    uint8_t mPad00[0x08];       // +0x00
    uint8_t mValue[0xb0 - 0x08];    // +0x08
};
struct WidePairList {
    WidePair* mpBegin;          // +0x00
    WidePair* mpEnd;            // +0x04
    WidePair* mpCapacity;       // +0x08
};
class cInt32SetNode {
public:
    int32_t mnValue;            // +0x00
    cInt32SetNode* mpNext;      // +0x04
};
class cInt32Set {
public:
    uint8_t mPad00[0x04];       // +0x00
    cInt32SetNode** mpBuckets;  // +0x04  bucket[nBucketCount] holds the end node
    int32_t mnBucketCount;      // +0x08
    int32_t mnElementCount;     // +0x0c
};
// ---- items of slice s00c784c0 end

// ---- items of slice s00c793e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_vtbl_01472d48;       // 0x01472d48  Simulator::cPlayer vtable (+0x00)
extern void* g_vtbl_01472d34;       // 0x01472d34  Simulator::cPlayer interface vtable (+0x04)
extern void* g_vtbl_01472d24;       // 0x01472d24  Simulator::cPlayer interface vtable (+0x34)
extern void* g_vtbl_013eb394;       // 0x013eb394  ??_7PaintSystem@@6B@ (+0x34, base dtor)
extern uint8_t g_gameModeEntry;     // 0x01654c02  game-mode table entry (DAT_01654c02)
extern wchar_t g_wstrEmpty[];       // 0x013f6254  shared empty wstring buffer
extern wchar_t g_wstrBool[];        // 0x013f58a0  L"bool"
void*  __cdecl FUN_00c771e0(void* pLast, void* pEnd, void* pFirst);            // 0x00c771e0 eastl copy_impl::do_copy
void*  __cdecl FUN_00c75b60(void* pDst, uint32_t n, void* pValue, void* pPos); // 0x00c75b60 eastl uninitialized_fill_n
void*  __cdecl FUN_00c76740(void* pDst, void* pSrc, uint32_t nBytes);          // 0x00c76740 eastl uninitialized_move
uint32_t __cdecl FUN_00c227e0();                                               // 0x00c227e0 get the ban-pick mode
void   __cdecl FUN_00c227d0(uint32_t nMode);                                   // 0x00c227d0 set the ban-pick mode
void   __cdecl FUN_00ba5bc0(void* pEmpire, uint32_t nArg);                     // 0x00ba5bc0
void*  __cdecl SP_GetCurrentGameMode();                                         // 0x00b5b800
void*  __cdecl SP_NounManager();                                                // 0x00b3d300
void*  __cdecl SP_SpaceGameGet();                                               // 0x01002bd0
void*  __cdecl SP_MessageServer();                                              // 0x0067dcc0
uint32_t __cdecl SP_GetPlayerEmpireOrMinus1();                                  // 0x00b1f9d0
uint32_t __cdecl SP_GetPlayerEmpireID();                                        // 0x01021090
void*  __cdecl EA_ConvertToString16(void* pOut, const char* pStr, int32_t nLen);  // 0x0093c5a0
bool   __cdecl WriteTypedValue(void* pStream, int32_t nA, void* pElem, const wchar_t* pType);  // 0x0057c940
class cGonzagoTimer {
public:
    uint64_t mPad00[4];                         // +0x00, 0x20 bytes, 8-byte aligned
    ~cGonzagoTimer();                           // 0x00b638b0
};
struct tPair28 {
    uint32_t      mKey;                         // +0x00
    cGonzagoTimer mTimer;                       // +0x08
};
class tPairVec {
public:
    tPair28* mpBegin;                           // +0x00
    tPair28* mpEnd;                             // +0x04
    tPair28* mpCap;                             // +0x08
    tPair28* erase(tPair28* pFirst, tPair28* pLast);    // 0x00c798a0
};
class tUintVec {
public:
    uint32_t* mpBegin;                          // +0x00
    uint32_t* mpEnd;                            // +0x04
    uint32_t* mpCap;                            // +0x08
    uint32_t  mnAlloc;                          // +0x0c
    uint32_t* insert(uint32_t* pPos, uint32_t n, const uint32_t& rValue);  // 0x00c79900
    void      DoInsertValue(uint32_t* pPos, const uint32_t& rValue);       // 0x004558a0
};
struct tAutoRef {
    void* mpObj;                                // +0x00
};
class tRefVec {
public:
    tAutoRef* mpBegin;                          // +0x00
    tAutoRef* mpEnd;                            // +0x04
    tAutoRef* mpCap;                            // +0x08
    void insert(tAutoRef* pPos, uint32_t n, tAutoRef* pValue);    // 0x00c795f0
};
class cRefObj_s00c7_93e0 {
public:
    virtual int AddRef();                       // +0x00
    virtual int Release();                      // +0x04
};
class cPlayerInner {
public:
    void** mpVtbl00;                            // +0x00
    uint8_t mPad04[0x70 - 0x04];
    uint32_t mn70;                              // +0x70  the handle stored in the state lists
    int  FUN_00bb9ae0();                        // 0x00bb9ae0
    bool FUN_00bb9bd0();                        // 0x00bb9bd0
    bool FUN_00bb9c00();                        // 0x00bb9c00
    void FUN_00bb9bb0(uint32_t nArg);           // 0x00bb9bb0
    void FUN_00bb9be0(uint32_t nArg);           // 0x00bb9be0
    void FUN_00bb9b00(uint32_t nA, uint32_t nB); // 0x00bb9b00
    void* GetAvatar();                          // 0x00b1fdb0 SP::cGameNounManager::GetAvatar
    int  AddRef();                              // 0x00801920
};
class cStarManager_s00c7_93e0 {
public:
    void* GetEmpireByID();                      // 0x00ba9370
};
class cEmpire_s00c7_93e0 {
public:
    uint8_t mPad00[0x84];                       // +0x00
    uint32_t mn84;                              // +0x84
    void FUN_00c322f0(uint32_t nArg);           // 0x00c322f0
    void FUN_00c313a0(uint32_t nArg);           // 0x00c313a0
};
class cMessageServer {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14(uint32_t nKey, uint32_t nA, uint32_t nB);   // +0x14
};
class cNounMgr {
public:
    void** mpVtbl00;                            // +0x00
    void* GetPlayerTribe();                     // 0x00bfc5f0
};
class cTribe {
public:
    void** mpVtbl00;                            // +0x00
    void FUN_00fe5430(uint32_t nA, uint32_t nB); // 0x00fe5430
};
class cBanModeEntry {
public:
    void FUN_00db5b30(void* pVec);              // 0x00db5b30
};
class cSerialStream {
public:
    virtual void v00(const wchar_t* pName);     // +0x00
    virtual void v04(const wchar_t* pName);     // +0x04
};
class tWString {
public:
    wchar_t* mpBegin;                           // +0x00
    wchar_t* mpEnd;                             // +0x04
    wchar_t* mpCap;                             // +0x08
    void RangeInitialize(uint32_t nCount);                      // 0x00579a90
    tWString() : mpBegin(0), mpEnd(0), mpCap(0) {}              // inlined by cl
    tWString(const tWString& rOther);                           // 0x0056e2d0
    ~tWString() {
        if (mpCap - mpBegin > 1 && mpBegin != 0)
            operator_delete_array(mpBegin);
    }
};
class cPool38 {                                 // cPlayer+0x38, pool freed by 0x00a42fe0
public:
    uint8_t   mPad00[4];
    uint32_t* mpPool;                           // +0x04 (cPlayer+0x03c)
    uint32_t  mnCount;                          // +0x08 (cPlayer+0x040)
    uint32_t  mnNext;                           // +0x0c (cPlayer+0x044)
    uint8_t   mPad10[8];
    uint32_t* mpFreeHead;                       // +0x18 (cPlayer+0x054)
    uint8_t   mPad1c[8];
    uint32_t* mpPoolBegin;                      // +0x24 (cPlayer+0x05c)
    uint32_t* mpPoolEnd;                        // +0x28 (cPlayer+0x060)
    uint8_t   mPad2c[4];
    uint32_t* mpStatic;                         // +0x30 (cPlayer+0x068)
    void FUN_00a42fe0(void* pPool, uint32_t nCount);   // 0x00a42fe0
};
class cHash69c {                                // cPlayer+0x698, eastl hashtable
public:
    uint8_t   mPad00[4];
    uint32_t* mpBuckets;                        // +0x04 (cPlayer+0x69c)
    uint32_t  mnCount;                          // +0x08 (cPlayer+0x6a0)
    uint32_t  mnNext;                           // +0x0c (cPlayer+0x6a4)
    uint8_t   mPad10[8];
    uint32_t* mpFreeHead;                       // +0x18 (cPlayer+0x6b4)
    uint8_t   mPad1c[8];
    uint32_t* mpPoolBegin;                      // +0x24 (cPlayer+0x6bc)
    uint32_t* mpPoolEnd;                        // +0x28 (cPlayer+0x6c0)
    uint8_t   mPad2c[4];
    uint32_t* mpStatic;                         // +0x30 (cPlayer+0x6c8)
    void DoFreeNodes(uint32_t* pBuckets, uint32_t nCount);   // 0x00a1b6c0
};
class cHash1120 {                               // cPlayer+0x111c, eastl hashtable
public:
    uint8_t   mPad00[4];
    uint32_t* mpBuckets;                        // +0x04 (cPlayer+0x1120)
    uint32_t  mnCount;                          // +0x08 (cPlayer+0x1124)
    uint32_t  mnNext;                           // +0x0c (cPlayer+0x1128)
    void DoFreeNodes(uint32_t* pBuckets, uint32_t nCount);   // 0x006b6570
};
class cBanModeArray {                           // cPlayer+0x113c, 20-byte ban-mode entries
public:
    void*   mpBegin;                            // +0x00 (cPlayer+0x113c)
    void*   mpEnd;                              // +0x04 (cPlayer+0x1140)
    void FUN_00c77ab0(void* pBegin, void* pEnd);   // 0x00c77ab0
};
class cList11c0 {                               // cPlayer+0x11c0, pointer list
public:
    void* mpBegin;                              // +0x00 (cPlayer+0x11c0)
    void* mpEnd;                                // +0x04 (cPlayer+0x11c4)
    void FUN_00c781e0(void* pBegin, void* pEnd);   // 0x00c781e0
};
class cList11f8 {                               // cPlayer+0x11f8, container with a +0x0c head
public:
    uint8_t mPad00[0x0c];
    void*   mpHead;                             // +0x0c (cPlayer+0x1204)
    void FUN_00c77b10(void* pHead);             // 0x00c77b10
};
class cRbTree1228 {                             // cPlayer+0x1228, eastl rbtree
public:
    uint32_t  mUnk00;                           // +0x00
    void*     mpEndNode;                        // +0x04
    void*     mpEndNodeSelf;                    // +0x08
    void*     mpRoot;                           // +0x0c (cPlayer+0x1234)
    uint32_t  mb10;                             // +0x10
    uint32_t  mn14;                             // +0x14
    void DoNukeSubtree(void* pRoot);            // 0x009a9600
};
class cPlayer {
public:
    void* mpVtbl00;                             // +0x0000
    void* mpVtbl04;                             // +0x0004
    uint8_t mPad08[0x34 - 0x08];
    void* mpVtbl34;                             // +0x0034
    cPool38 mPool38;                            // +0x0038 .. +0x006b
    uint8_t mPad6c[0x698 - 0x6c];
    cHash69c mHash69c;                          // +0x0698 .. +0x06cb
    uint8_t mPad6cc[0x10e8 - 0x6cc];
    void* mpRef10e8;                            // +0x10e8
    uint8_t mPad10ec[0x111c - 0x10ec];
    cHash1120 mHash1120;                        // +0x111c .. +0x112b
    uint8_t mPad112c[0x113c - 0x112c];
    cBanModeArray mBanModeTable;                // +0x113c .. +0x1143
    uint8_t mPad1144[0x1184 - 0x1144];
    tUintVec mVec1184;                          // +0x1184 .. +0x1193
    uint8_t mPad1194[0x1198 - 0x1194];
    tUintVec mVec1198;                          // +0x1198 .. +0x11a7
    uint8_t mPad11a8[0x11ac - 0x11a8];
    tUintVec mVec11ac;                          // +0x11ac .. +0x11bb
    uint8_t mPad11bc[0x11c0 - 0x11bc];
    cList11c0 mList11c0;                        // +0x11c0 .. +0x11c7
    uint8_t mPad11c8[0x11d8 - 0x11c8];
    void* mpBlock11d8;                          // +0x11d8
    uint8_t mPad11dc[0x11f4 - 0x11dc];
    void* mpRef11f4;                            // +0x11f4
    cList11f8 mList11f8;                        // +0x11f8 .. +0x1207
    uint8_t mPad1208[0x1214 - 0x1208];
    tPair28* mpPairBegin1214;                   // +0x1214
    tPair28* mpPairEnd1218;                     // +0x1218
    uint8_t mPad121c[0x1228 - 0x121c];
    cRbTree1228 mRbTree;                        // +0x1228 .. +0x123f
    uint8_t mPad1240c[0x1258 - 0x1240];
    cGonzagoTimer mTimer1258;                   // +0x1258
    uint8_t mPad1278[0x129c - 0x1278];
    void* mpBlock129c;                          // +0x129c
    uint8_t mPad12a0[0x12ac - 0x12a0];
    void* mpBlock12ac;                          // +0x12ac

    bool  FUN_00c772c0(uint32_t nKey);                          // 0x00c772c0
    void  FUN_00c754e0(cPlayerInner* pObj);                     // 0x00c754e0
    void  FUN_00c79f20(cPlayerInner* pObj);                     // 0x00c79f20
    void  FUN_00c79fa0(cPlayerInner* pObj);                     // 0x00c79fa0
    void  FUN_00c7a160(cPlayerInner* pObj);                     // 0x00c7a160
    void  SetBanModePickPriorities(uint32_t nMode, tUintVec* pVec);  // 0x00c79e20
    void  FUN_00c79b60();                                       // 0x00c79b60  destructor body
};
// ---- items of slice s00c793e0 end

// ---- items of slice s00c7c0c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* g_0150d6dc;                    // 0x0150d6dc
extern uint32_t g_01687968;                 // 0x01687968
extern void* g_01578d18;                    // 0x01578d18
struct Vec3 { float x, y, z; };
class  cRefObj;
class  cCollectableItems;
class  cPlayer_s00c7_c0c0;
class  cStream;
void* __cdecl FUN_00f473a0(uint32_t size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl FUN_00f47380(void* p);                                                                    // 0x00f47380
void* __cdecl FUN_00c79ae0(void* first, void* last, void* out);                                         // 0x00c79ae0
void  __cdecl FUN_00c79b20(void* first, void* last, void* out);                                         // 0x00c79b20
void* __cdecl FUN_00c7aca0(void* first, void* last, void* out);                                         // 0x00c7aca0
void  __cdecl FUN_00c7bea0(void* pos, uint32_t n, void* value);                                         // 0x00c7bea0
void  __cdecl FUN_00c7be50(void* first, void* last);                                                    // 0x00c7be50
void  __cdecl FUN_00c7b670(void* stream, void* out);                                                    // 0x00c7b670
void  __cdecl FUN_00bdaa40(void* out, void* first, void* last, void* dst, void* alloc);                 // 0x00bdaa40
void  __cdecl FUN_00ba3ca0(void* p);                                                                    // 0x00ba3ca0
void* __cdecl FUN_00ba4430(void* self, void* arg);                                                      // 0x00ba4430
void  __cdecl FUN_00b6f140(float x, float y, float z);                                                  // 0x00b6f140
void  __cdecl ReadInt32(void* io, void* dst, int count, int ver);                                       // 0x0093a780
void  __cdecl FUN_0091ff50(void* p);                                                                     // 0x0091ff50
void* __cdecl FUN_00c72540(void* first, void* last, void* key, int flag);                                // 0x00c72540
void* __cdecl PropertyManager();                                          // 0x0067de30
void* __cdecl ObjectTemplateDB();                                         // 0x0067cb40
void* __cdecl MessageServer();                                            // 0x0067dcc0
class cRefObj {
public:
    virtual void v00();                     // +0x00  (AutoRefCount AddRef)
    virtual void Release();                 // +0x04  (AutoRefCount Release)
};
class cCollectableItems : public cRefObj {
public:
    cCollectableItems* ctor();                                          // 0x00597e00
    void Configure(uint32_t a, uint32_t b, void* c);                    // 0x00599440
};
class cIOObj {
public:
virtual void i00();
virtual void i04();
virtual void i08();
virtual void i0c();
virtual void i10();
virtual void i14();
    virtual void* v18();                                                // +0x18
};
class cStream {
public:
virtual void c00();
virtual void c04();
virtual void c08();
virtual void c0c();
virtual void c10();
virtual void c14();
virtual void c18();
virtual void c1c();
    virtual void* v20();                                                // +0x20
virtual void c24();
virtual void c28();
virtual void c2c();
virtual void c30();
virtual void c34();
virtual void c38();
    virtual uint32_t v3c();                                             // +0x3c
};
class cMessageServerObj {
public:
    virtual void m00();
virtual void m04();
virtual void m08();
virtual void m0c();
virtual void m10();
virtual void m14();
virtual void m18();
virtual void m1c();
virtual void m20();
virtual void m24();
virtual void m28();
    virtual void Broadcast(void* obj, uint32_t id, int32_t code);        // +0x2c
};
class cPropertyManager {
public:
    virtual void p00();
virtual void p04();
virtual void p08();
virtual void p0c();
virtual void p10();
virtual void p14();
virtual void p18();
virtual void p1c();
virtual void p20();
virtual void p24();
virtual void p28();
    virtual void GetProperty(uint32_t a, uint32_t b, void* out);         // +0x2c
};
class cObjectTemplateDB {
public:
    virtual void d00();
virtual void d04();
virtual void d08();
virtual void d0c();
virtual void d10();
virtual void d14();
virtual void d18();
virtual void d1c();
virtual void d20();
virtual void d24();
virtual void d28();
virtual void d2c();
virtual void d30();
virtual void d34();
virtual void d38();
virtual void d3c();
virtual void d40();
virtual void d44();
virtual void d48();
virtual void d4c();
    virtual void Register(void* owner);                                 // +0x50
    virtual void Unregister();                                          // +0x54
};
class cVarListSerializer {
public:
    void ctor(void* owner, void* varList, int id);                       // 0x00692f90
    bool Read(void* stream);                                             // 0x00693e10
};
struct cGonzagoTimer_s00c7_c0c0 {
    void* mpBegin; void* mpEnd; void* mpCap;
    void* mExtra[5];
    void  ctor();                                                        // 0x00b63890
    void  dtor();                                                        // 0x00b638b0
};
struct cInnerVec {
    void* mpBegin; void* mpEnd; void* mpCap;
    void  dtor();                                                        // 0x00ad92d0
};
struct cBanModeEntry_s00c7_c0c0 {
    void*    mpBegin;                        // +0x00  inner vector begin
    void*    mpEnd;                          // +0x04
    void*    mpCap;                          // +0x08
    uint32_t mField0C;                       // +0x0c
    uint32_t mField10;                       // +0x10
    cBanModeEntry_s00c7_c0c0() { mpBegin = 0; mpEnd = 0; mpCap = 0; }
    cBanModeEntry_s00c7_c0c0(const cBanModeEntry_s00c7_c0c0& other);                // 0x00c76fd0
    cBanModeEntry_s00c7_c0c0& operator=(const cBanModeEntry_s00c7_c0c0& other);     // 0x00db5b30
};
class cBanModeVec {
public:
    void* mpBegin;                           // +0x00
    void* mpEnd;                             // +0x04
    void* mpCap;                             // +0x08
    void* DoInsertValue(cBanModeEntry_s00c7_c0c0* position, const cBanModeEntry_s00c7_c0c0& value);  // 0x00c7c0c0
    void  resize(uint32_t n);                                                  // 0x00c7c4a0
    void  FUN_00c77ab0(void* first, void* last);                               // 0x00c77ab0
    void  FUN_00c77a00(uint32_t n);                                            // 0x00c77a00
};
struct tUintVec_s00c7_c0c0 {
    uint32_t* mpBegin;                       // +0x00
    uint32_t* mpEnd;                         // +0x04
    uint32_t* mpCap;                         // +0x08
};
class cPlanetVec {
public:
    void* mpBegin;                           // +0x00
    void* mpEnd;                             // +0x04
    void* mpCap;                             // +0x08
    void  FUN_00c781e0(void* first, void* last);   // 0x00c781e0
    void  FUN_00ba4de0(void* iter, void* key);     // 0x00ba4de0
};
struct PlayerPlanetData {
    void* mpVtbl;                            // +0x00
    void* pv08b; void* pv08e; void* pv08c;   // +0x08
    void* pv20b; void* pv20e; void* pv20c;   // +0x20
    void* pv38b; void* pv38e; void* pv38c;   // +0x38
    void* pv50b; void* pv50e; void* pv50c;   // +0x50
    void* pv68b; void* pv68e; void* pv68c;   // +0x68
    uint8_t mTimer[0x20];                    // +0x80
    uint8_t mA0; uint8_t mA1; uint8_t mA2; uint8_t mPad[0xd];  // +0xa0
};
class cPlayer_s00c7_c0c0 {
public:
    void*    mpVtbl00;                       // +0x0000
    void*    mpVtbl04;                       // +0x0004
    uint8_t  mPad08[0x28 - 0x08];            // +0x0008
    uint32_t mField28;                       // +0x0028
    cRefObj* mpOwner2C;                      // +0x002c  AutoRefCount owner
    uint8_t  mPad30[0x34 - 0x30];            // +0x0030
    void*    mpVtbl34;                       // +0x0034  IHandlerRC interface vtable
    uint8_t  mPad38[0x84 - 0x38];            // +0x0038
    uint32_t mFlags84;                       // +0x0084
    int      mField88;                       // +0x0088
    uint8_t  mPad8C[0xa5 - 0x8c];            // +0x008c
    bool     mBoolA5;                        // +0x00a5
    uint8_t  mPadA6[0x10e8 - 0xa6];          // +0x00a6
    cRefObj* mpRef10E8;                      // +0x10e8  AutoRefCount<cCollectableItems>
    int      mField10EC;                     // +0x10ec
    uint8_t  mPad10F0[0x10f8 - 0x10f0];      // +0x10f0
    int      mField10F8;                     // +0x10f8
    uint8_t  mPad10FC[0x113c - 0x10fc];      // +0x10fc
    cBanModeVec mBanModeTable;               // +0x113c
    uint8_t  mPad1148[0x1184 - 0x1148];      // +0x1148
    tUintVec_s00c7_c0c0 mVec1184;                       // +0x1184
    tUintVec_s00c7_c0c0 mVec1198;                       // +0x1198
    tUintVec_s00c7_c0c0 mVec11AC;                       // +0x11ac
    uint8_t  mPad11B8[0x11f4 - 0x11b8];      // +0x11b8
    cRefObj* mpRef11F4;                      // +0x11f4
    uint8_t  mPad11F8[0x1244 - 0x11f8];      // +0x11f8
    void*    mp1244;                         // +0x1244

    void RemoveOwner();                                                  // 0x00c7c220
    void SetGameDataOwner(int owner);                                    // 0x00c7c6d0
    bool Read(void* stream);                                             // 0x00c7c7c0
    void FUN_00c751e0();                                                 // 0x00c751e0
    void FUN_00b18550_base(int owner);                                   // 0x00b18550
    bool FUN_00b18600_read(void* stream);                                // 0x00b18600
};
static inline cCollectableItems* AllocCollectableItems()
{
    cCollectableItems* p = (cCollectableItems*)FUN_00f473a0(
        0x6dac, "Simulator/cCollectableItems", 0, 0, 0, 0);
    if (p)
        p = p->ctor();
    return p;
}
static inline void AssignAutoRef(cRefObj** slot, cRefObj* p)
{
    cRefObj* old = *slot;
    if (p != old) {
        if (p)
            p->v00();
        *slot = p;
        if (old)
            old->Release();
    }
}
static inline void StreamReadInt32(void* stream, void* dst)
{
    void* obj = ((cStream*)stream)->v20();
    void* io  = ((cIOObj*)obj)->v18();
    ReadInt32(io, dst, 1, 0);
}
static inline void DestroyBanTemp(cBanModeEntry_s00c7_c0c0& temp)
{
    for (void** p = (void**)temp.mpBegin; p != (void**)temp.mpEnd; ++p) {
        if (*p != 0) {
            typedef void (__thiscall *PFN)(void*);
            ((PFN)(((void**)*p)[0xc0 / 4]))(*p);
        }
    }
    if (temp.mpBegin != 0 && ((int*)temp.mpBegin)[-1] != 0)
        FUN_00f47380(temp.mpBegin);
}
// ---- items of slice s00c7c0c0 end

// ---- items of slice s01350ca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct string8_s0135_0ca0; 
}
typedef eastl::string8_s0135_0ca0 string8_s0135_0ca0;
namespace Simulator {
class ISerializerReadStream;
}
namespace Simulator {
class ISerializerWriteStream;
}
namespace Simulator {
struct Attribute;
}
namespace Simulator {
typedef bool  (*ReadFunction_t)(ISerializerReadStream*, void*);
}
namespace Simulator {
typedef bool  (*WriteFunction_t)(ISerializerWriteStream*, void*);
}
namespace Simulator {
typedef void  (*ReadTextFunction_t)(const string8_s0135_0ca0&, void*);
}
namespace Simulator {
typedef void  (*WriteTextFunction_t)(char*, void*);
}
namespace Simulator {
typedef bool  (*ValidateFunction_t)();
}
namespace Simulator {
typedef bool  (*ToXmlFunction_t)(void*, const char*, int);
}
namespace Simulator {
typedef void* (*OffsetFunction_t)(Attribute*);
}
namespace Simulator {
typedef void  (*SetDefaultFunction_t)(Attribute*);
}
namespace Simulator {
void* DefaultOffset(Attribute* pAttr);   // 0x00692ca0: pAttr->pCurrentObject + pAttr->offset
}
namespace Simulator {
struct Attribute
{
    Attribute(const char* pName, uint32_t nID, uint32_t nOffset,
              ReadFunction_t pRead, WriteFunction_t pWrite,
              ReadTextFunction_t pReadText, WriteTextFunction_t pWriteText,
              ValidateFunction_t pValidate, ToXmlFunction_t pToXml,
              SetDefaultFunction_t pSetDefault = 0)
    {
        name = pName;
        id = nID;
        pCurrentObject = 0;
        setDefaultFunction = pSetDefault;
        offsetFunction = DefaultOffset;
        readFunction = pRead;
        writeFunction = pWrite;
        readTextFunction = pReadText;
        writeTextFunction = pWriteText;
        validateFunction = pValidate;
        toXmlFunction = pToXml;
        offset = nOffset;
    }

    /* 00h */ const char* name;
    /* 04h */ uint32_t id;
    /* 08h */ uint32_t offset;
    /* 0Ch */ int field_0C;   // not initialized
    /* 10h */ int field_10;   // not initialized
    /* 14h */ int field_14;   // not initialized
    /* 18h */ void* pCurrentObject;
    /* 1Ch */ SetDefaultFunction_t setDefaultFunction;
    /* 20h */ OffsetFunction_t offsetFunction;
    /* 24h */ ReadFunction_t readFunction;
    /* 28h */ WriteFunction_t writeFunction;
    /* 2Ch */ ReadTextFunction_t readTextFunction;
    /* 30h */ WriteTextFunction_t writeTextFunction;
    /* 34h */ ValidateFunction_t validateFunction;
    /* 38h */ ToXmlFunction_t toXmlFunction;
};
}
namespace Simulator {
extern int sTotalTimeInCVGDefault;   // 0x01694560
}
namespace Simulator {
void SetDefault_00c75a80(Attribute* pAttr);  // 0x00c75a80
}
namespace Simulator {
bool Read_00572810(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ac8750(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3430(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ae3470(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b04e00(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00b6e3a0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00ba8250(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c777e0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c78020(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c78130(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c78d50(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c7a970(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c7aef0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c7b120(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c7b240(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c7c530(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Read_00c7c9b0(ISerializerReadStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00572840(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00675790(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac8780(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac88f0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ac9f70(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3450(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00ae3490(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00bca960(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c75e70(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c75f10(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c76010(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c76100(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c761c0(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c76c70(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c76d60(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
bool Write_00c77890(ISerializerWriteStream* pStream, void* pData);
}
namespace Simulator {
void ReadText_00692ff0(const string8_s0135_0ca0& text, void* pData);
}
namespace Simulator {
void ReadText_00693090(const string8_s0135_0ca0& text, void* pData);
}
namespace Simulator {
void ReadText_006930b0(const string8_s0135_0ca0& text, void* pData);
}
namespace Simulator {
void ReadText_006930f0(const string8_s0135_0ca0& text, void* pData);
}
namespace Simulator {
void ReadText_00693150(const string8_s0135_0ca0& text, void* pData);
}
namespace Simulator {
void ReadText_00c2e4e0(const string8_s0135_0ca0& text, void* pData);
}
namespace Simulator {
void WriteText_00692fb0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694ee0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694f00(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fa0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00694fc0(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695010(char* pBuffer, void* pData);
}
namespace Simulator {
void WriteText_00695080(char* pBuffer, void* pData);
}
namespace Simulator {
bool Validate_00675850();
}
namespace Simulator {
bool Validate_00ae3310();
}
namespace Simulator {
bool Validate_00b1fbf0();
}
namespace Simulator {
bool Validate_00b6f550();
}
namespace Simulator {
bool Validate_00c760c0();
}
namespace Simulator {
bool Validate_00c76170();
}
namespace Simulator {
bool Validate_00c76d10();
}
namespace Simulator {
bool Validate_00c76e10();
}
namespace Simulator {
bool Validate_00cd6630();
}
namespace Simulator {
bool Validate_00d011e0();
}
namespace Simulator {
bool ToXml_0057cde0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_0057ce00(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00675ca0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ac8050(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbb80(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00acbba0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00ae5720(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00baa2b0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c51440(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c788d0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c78a50(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c78bd0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c78ea0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c78ff0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00c79140(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00d022e0(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_00eafe40(void* pData, const char* pName, int depth);
}
namespace Simulator {
bool ToXml_01011db0(void* pData, const char* pName, int depth);
}
namespace Simulator {
struct AttrStorage { char data[sizeof(Attribute)]; };
}
namespace Simulator {
AttrStorage cPlayer_sAttributes[37];   // 0x01578d18
}
// ---- items of slice s01350ca0 end

// ---- items of slice s01351ae0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void SAE0_F2CB();   // 0x00c2e4e0
extern void SAE0_F30B();   // 0x00692fb0
extern void SAE0_F34A();   // 0x00b1fbf0
extern void SAE0_F38A();   // 0x00b8e840
extern void SE60_F34();   // 0x00b1fbf0
extern void SE60_F38();   // 0x0057cde0
extern void U_01351ae0_0_24();   // 0x00bb9cd0
extern void U_01351ae0_0_28();   // 0x00bb9d00
extern void U_01351ae0_0_34();   // 0x00b1fbf0
extern void U_01351ae0_1_24();   // 0x00bb9cd0
extern void U_01351ae0_1_28();   // 0x00bb9d00
extern void U_01351ae0_1_2c();   // 0x00693050
extern void U_01351ae0_1_30();   // 0x00694f60
extern void U_01351ae0_2_24();   // 0x00bb9cd0
extern void U_01351ae0_2_28();   // 0x00bb9d00
extern void U_01351ae0_2_2c();   // 0x00693050
extern void U_01351ae0_2_30();   // 0x00694f60
extern void U_01351ae0_3_24();   // 0x00c7b390
extern void U_01351ae0_3_28();   // 0x00c76250
extern void U_01351ae0_3_34();   // 0x00b1fbf0
extern void U_01351ae0_3_38();   // 0x00c79290
extern void U_01351ae0_4_24();   // 0x00c7b390
extern void U_01351ae0_4_28();   // 0x00c76250
extern void U_01351ae0_4_34();   // 0x00b1fbf0
extern void U_01351ae0_4_38();   // 0x00c79290
extern void U_01351ae0_5_24();   // 0x00c7b390
extern void U_01351ae0_5_28();   // 0x00c76250
extern void U_01351ae0_5_34();   // 0x00b1fbf0
extern void U_01351ae0_5_38();   // 0x00c79290
extern void U_01351ae0_6_24();   // 0x00c7b390
extern void U_01351ae0_6_28();   // 0x00c76250
extern void U_01351ae0_6_34();   // 0x00b1fbf0
extern void U_01351ae0_6_38();   // 0x00c79290
extern void U_01351ae0_7_34();   // 0x00b1fbf0
extern void U_01351e60_0_24();   // 0x00572810
extern void U_01351e60_0_28();   // 0x00572840
extern void U_01351e60_0_34();   // 0x00b1fbf0
extern void U_01351e60_2_24();   // 0x00572810
extern void U_01351e60_2_28();   // 0x00572840
extern void U_01351e60_2_2c();   // 0x00692ff0
extern void U_01351e60_2_30();   // 0x00694ee0
extern void U_01351e60_3_24();   // 0x00572810
extern void U_01351e60_3_28();   // 0x00572840
extern void U_01351e60_3_2c();   // 0x00692ff0
extern void U_01351e60_3_30();   // 0x00694ee0
extern void U_01351e60_4_24();   // 0x00572810
extern void U_01351e60_4_28();   // 0x00572840
extern void U_01351e60_4_2c();   // 0x00692ff0
extern void U_01351e60_4_30();   // 0x00694ee0
extern void U_01351e60_5_24();   // 0x00572810
extern void U_01351e60_5_28();   // 0x00572840
extern void U_01351e60_5_2c();   // 0x00692ff0
extern void U_01351e60_5_30();   // 0x00694ee0
typedef unsigned int u32;
struct PropDesc {
    const char* mName;   // +0x00
    u32 mHash;   // +0x04
    u32 mType;   // +0x08
    u32 mPad0C;   // +0x0c
    u32 mPad10;   // +0x10
    u32 mPad14;   // +0x14
    u32 mZero18;   // +0x18
    u32 mZero1C;   // +0x1c
    void* mDefault;   // +0x20
    void* mFn24;   // +0x24
    void* mFn28;   // +0x28
    void* mFn2C;   // +0x2c
    void* mFn30;   // +0x30
    void* mFn34;   // +0x34
    void* mFn38;   // +0x38
};
// ---- items of slice s01351ae0 end

// ---- items of slice s00ba2590 begin (TODO(rewrite): local stubs, replace by canonical classes)
void  __cdecl operator_delete__(void*);                    // 0xf47380
void* __cdecl SP_PropertyManager();                        // 0x67de30
void  __cdecl EA_IO_WriteUint32(void*, void*, int, int);   // 0x93aa70
struct VecHdr {
  int pad0; void* data; unsigned size; int fieldC;
  void __thiscall FreeInts(int* arr, unsigned n);          // 0xba2980
  __declspec(noinline) void FreeNodes(void* arr, unsigned n);   // 0xba2e00
};
struct CGZTimer { void __thiscall Dtor(); };
static inline void Release(void* p) { if (p) (*(void(__thiscall*)(void*))((*(void***)p)[1]))(p); }
struct W {
  void __thiscall Run_00ba2590(void* obj);
  void __thiscall Run_00ba2670(void* p);
  void __thiscall Run_00ba2750();
  void __thiscall Run_00ba2ca0(void* p2);
  char __thiscall Run_00ba2d80(void* p2);
  void __thiscall Run_00ba2f20();
  void* __thiscall Run_00ba2f90();
  void __thiscall Run_00ba3010();
  void* __thiscall Run_00ba30c0(void* out, uint32_t* key, int);
  void* __thiscall Run_00ba31d0(void* out, void* node, void** head);
  void __thiscall Run_00ba3310();
  void __thiscall Run_00ba3350();
  void* __thiscall Run_00ba3550(void* src);
  void* __thiscall Run_00ba3620(void* src);
  void __thiscall Run_00ba37a0();
};
// ---- items of slice s00ba2590 end

// ---- items of slice s00c75e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const char  g_szAllocator[];        // 0x013ebb38 eastl allocator.h path
extern float       g_f0p001;               // 0x013f9428, 0.001f
typedef unsigned int   U32;
typedef unsigned char  U8;
typedef unsigned __int64 U64;
struct EA_IO_Stream;                                                       // opaque IO stream
void __cdecl IO_WriteUint32(EA_IO_Stream* s, const U32* p, U32 n, U32 flags);   // 0x0093aa70
bool __cdecl IO_WriteBool8(EA_IO_Stream* s, const bool* p, U32 n);              // 0x0093a9a0
struct ISerializerStream {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
    virtual EA_IO_Stream* GetStream();              // +0x18
};
struct ISerializer {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual void EndItem();                         // +0x1c
    virtual ISerializerStream* GetStreamHolder();   // +0x20
};
template <typename T>
struct cVector {
    T* mpBegin;     // +0x00
    T* mpEnd;       // +0x04
    T* mpCap;       // +0x08
};
struct cRBNodeBase {
    cRBNodeBase* mpNodeRight;   // +0x00
    cRBNodeBase* mpNodeLeft;    // +0x04
    cRBNodeBase* mpNodeParent;  // +0x08
    U8           mbColor;       // +0x0c
};
cRBNodeBase* __cdecl RBTreeIncrement(const cRBNodeBase* pNode);            // 0x00921580
struct IRegisterHost {
    void __thiscall Register(void* pValue, U32* pData, const wchar_t* pName);  // 0x00695b40
};
void* __cdecl operator_new(U32 size, const char* pName, int a, int b, const char* pAlloc, U32 line); // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                  // 0x00f47380
extern const char  g_szSimulator_s00c7_5e70[];        // 0x013f09b4 "Simulator"
extern U32         g_1579600;              // 0x01579600
extern U32         g_1579858;              // 0x01579858
extern U32         g_vtblTimerBase;        // 0x01465d54
extern U32         g_vtblTimer;            // 0x01464450
extern U32         g_vtblWarData;          // 0x01472cc8
void __cdecl FUN_00ae2e40(ISerializer* pWriter, void* pElem);            // 0x00ae2e40
void __cdecl FUN_00c75ba0(ISerializer* pWriter, void* pElem);            // 0x00c75ba0
struct cSPTimer {
    U32 mpVftblBase;    // +0x00
    U32 mRefCount;      // +0x04
    U64 mElapsed;       // +0x08
    U64 mBase;          // +0x10
    U8  mbRunning;      // +0x18
    U8  pad19[3];       // +0x19
    U32 mpFn;           // +0x1c
    U64 __thiscall GetElapsedTime();                 // 0x00bc3190
    void __thiscall Write(ISerializer* pWriter);     // 0x00b638d0
};
struct cTimerPair {
    U32        mId;         // +0x00
    U32        pad04;       // +0x04
    cSPTimer   mTimer;      // +0x08
};
struct cGonzagoTimerC {
    U32 mdVtbl;     // +0x00
    U32 mnRef;      // +0x04
    U64 mElapsed;   // +0x08
    U64 mBase;      // +0x10
    U8  mbRunning;  // +0x18
    U8  pad19[3];   // +0x19
    U32 mpFn;       // +0x1c
};
struct CElemTimer {
    U32            mId;     // +0x00
    U32            pad04;   // +0x04
    cGonzagoTimerC mTimer;  // +0x08
};
struct cEmbassyData {
    U32 mInt00;     // +0x00
    U32 mInt04;     // +0x04
};
struct cEmbassyNode {
    cRBNodeBase  mBase;     // +0x00
    U32          mKey;      // +0x10
    cEmbassyData mData;     // +0x14
};
struct cEmbassyMap {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
};
struct IWritable {
    virtual void Write(ISerializer* pWriter);       // +0x00
};
struct cKeyBoolPair {
    U32        mKey;        // +0x00
    U32        pad04;       // +0x04
    IWritable  mValue;      // +0x08
    U8         pad00c[0xa4];
};
struct CElem20 {
    U32 md000[5];
};
struct IWritable7 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
    virtual void Write(ISerializer* pWriter);       // +0x1c
};
struct CObjectList {
    IWritable7** mpBegin;   // +0x00
    IWritable7** mpEnd;     // +0x04
    U32*         mpCap;     // +0x08
    U32          mInt0c;    // +0x0c
    U32          mInt10;    // +0x10
};
struct CElem16 {
    U32 mId;        // +0x00
    U32 md004;      // +0x04
    U32 md008;      // +0x08
    U8  mb00c;      // +0x0c
    U8  pad00d[3];  // +0x0d
};
struct CElem8 {
    U32 mId;        // +0x00
    U8  mb004;      // +0x04
    U8  pad005[3];  // +0x05
};
struct cHashNodeA {
    U32 mKey;           // +0x00
    U32 mInt04;         // +0x04
    U32 mInt08;         // +0x08 (xor-ed with the key to form the bucket index)
    U32 mpNext0c;       // +0x0c
};
struct cHashTableA {
    U32          md000;       // +0x00
    cHashNodeA** mpBuckets;   // +0x04
    U32          mnBuckets;   // +0x08
    U32          pad00c;      // +0x0c
    U32          pad010[3];   // +0x10
    U32          mpFreeList;  // +0x1c
    U32          pad020;      // +0x20
    U32          mpAllocBegin;// +0x24
    U32          mpAllocEnd;  // +0x28
    U32          pad02c;      // +0x2c
    U32          mpSentinel;  // +0x30

    cHashNodeA** __thiscall AllocBucketArray(U32 nBuckets);  // 0x00c763d0
    void __thiscall Rehash(U32 nBuckets);   // 0x00c76440
};
struct cWarNode {
    cRBNodeBase mBase;      // +0x00
    U32         mKey;       // +0x10
    U32         mInt14;     // +0x14
    U32         pad018[4];  // +0x18
    cSPTimer    mTimer;     // +0x28
    U32         pad048;     // +0x48
    U32         mInt4c;     // +0x4c
    U32         mInt50;     // +0x50
    U32         mInt54;     // +0x54
};
struct cWarMap {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
    void __thiscall Find(cRBNodeBase** ppResult, const U32* pKey);   // 0x00e5c780
};
struct cPlayer_s00c7_5e70 {
    U32     md000[0x84 / 4];    // +0x000
    U32     mEmpireId;          // +0x084
    U32     pad088[0x1170 / 4]; // +0x088 .. +0x11f7
    cWarMap mWars;              // +0x11f8

    void  __thiscall AddWarCaptureIncrement(U32 a, U32 b);      // 0x00c76790
    int   __thiscall GetPeacePriceForPlayer(cPlayer_s00c7_5e70* pEnemy);   // 0x00c76800
    float __thiscall GetPlayerWarElapsedSeconds(cPlayer_s00c7_5e70* pOther); // 0x00c769b0
    int   __thiscall GetPlayerWarCaptureDelta(cPlayer_s00c7_5e70* pOther);   // 0x00c76a30
};
U32   __cdecl GetPlayerEmpireID();                          // 0x01021090
void* __cdecl FUN_01021300();                               // 0x01021300
void* __cdecl EconomyTuning();                              // 0x0102f810
int   __cdecl RoundFloat(float f);                          // 0x011e0810
void* __fastcall FUN_00c308d0_s00c7_5e70(void* pEmpire);               // 0x00c308d0 (cEmpire::GetStars)
void* __fastcall FUN_00c308d0(void* pEmpire);               // 0x00c308d0 (cEmpire::GetStars)
void* __cdecl RelationshipManager();                        // 0x00b3d2c0
void* __cdecl StarManager(void* p);                         // 0x00b3d2a0
void* __fastcall FUN_00baf700(void* pThis);                 // 0x00baf700
float __cdecl FUN_010307a0(void* p, U32 a, U32 b);          // 0x010307a0
struct IEconTuning {
virtual void e0();
virtual void e1();
virtual void e2();
virtual void e3();
    virtual float GetPeacePriceElapsedSecondsFactor();  // +0x10
    virtual float GetPeacePricePlayerSizeFactor();      // +0x14
    virtual float GetPeacePriceEnemySizeFactor();       // +0x18
    virtual float GetPeacePriceCaptureFactor();         // +0x1c
    virtual float GetPeacePriceRelationshipFactor();    // +0x20
};
struct IRelationshipManager {
virtual void r0();
virtual void r1();
virtual void r2();
    virtual float GetRelationship(void* pOther, U32 nEmpireId, int nFlag);   // +0x0c
};
struct cStarList {
    U32* mpBegin;   // +0x00
    U32* mpEnd;     // +0x04
    U32* mpCap;     // +0x08
};
struct cHashNodeB {
    U32 mKey;       // +0x00
    U32 mInt04;     // +0x04
    U32 mpNext08;   // +0x08
};
struct cHashTableB {
    U32          md000;       // +0x00
    cHashNodeB** mpBuckets;   // +0x04
    U32          mnBuckets;   // +0x08
    U32          mnElements;  // +0x0c
    U32          pad010[3];   // +0x10
    U32          mpFreeList;  // +0x1c
    U32          pad020;      // +0x20
    U32          mpAllocBegin;// +0x24
    U32          mpAllocEnd;  // +0x28
    U32          pad02c;      // +0x2c
    U32          mpSentinel;  // +0x30

    int __thiscall Erase(const U32* pKey);   // 0x00c76be0
};
struct cHashNodeC {
    U32 mKey;       // +0x00
    U32 mInt04;     // +0x04
    U32 mInt08;     // +0x08
    U32 mpNext0c;   // +0x0c
};
struct cHashTableC {
    U32          md000;       // +0x00
    cHashNodeC** mpBuckets;   // +0x04
    U32          mnBuckets;   // +0x08
    U32          mnElements;  // +0x0c
};
struct IWritable2 {
virtual void v0();
virtual void v1();
    virtual void Write(ISerializer* pWriter);        // +0x08
};
struct cU32Node {
    cRBNodeBase mBase;      // +0x00
    U32         mKey;       // +0x10
    U32         pad014;     // +0x14
    IWritable2  mValue;     // +0x18
};
struct cU32Map {
    U32          mCompare;  // +0x00
    cRBNodeBase  mAnchor;   // +0x04
    U32          mnSize;    // +0x14
};
struct cWarDataNode {
    cRBNodeBase        mBase;      // +0x00
    U32                mKey;       // +0x10
    U32                pad014;     // +0x14
    struct cWarDataRec* mpValue;   // +0x18 -> value object at +0x18
};
void* __cdecl FUN_00bdaa40_s00c7_5e70(void* pDst, void* pSrcBegin, void* pSrcEnd, void* pNew, void* pExtra); // 0x00bdaa40
struct CSubList {
    U32* mpBegin;   // +0x00
    U32* mpEnd;     // +0x04
    U32* mpCap;     // +0x08
    U32  mInt0c;    // +0x0c
    U32  mInt10;    // +0x10
};
struct cWarRec {
    U32        mInt00;      // +0x00
    U32        mInt04;      // +0x04
    cSPTimer   mTimer;      // +0x08

    cWarRec* __thiscall CopyFrom(const cWarRec& src);   // 0x00c76f10
};
struct cSpacePlayerWarData {
    U32        mpVftbl00;         // +0x00
    U32        mInt04;            // +0x04
    U32        mEnemyEmpireID;    // +0x08
    U32        mInt0c;            // +0x0c
    cSPTimer   mTimer;            // +0x10
    U32        mPlayerStartStars; // +0x30
    U32        mEnemyStartStars;  // +0x34
    U32        mPlayerCaptured;   // +0x38
    U32        mEnemyCaptured;    // +0x3c

    cSpacePlayerWarData* __thiscall ctor(const cSpacePlayerWarData& src);   // 0x00c76f60
};
struct cHashSubD {
    U32 mDummy;   // +0x00 (sub-object state, not touched by the thunks below)

    void __thiscall FUN_006b6740(U32* pKey);   // 0x006b6740
};
struct cHashTableD {
    U32       md000[0x111c / 4];   // +0x000
    cHashSubD mSub;                // +0x111c
    U32       mpBuckets;           // +0x1120
    U32       mnBuckets;           // +0x1124

    bool __thiscall Contains(U32 nKey);       // 0x00c772c0
    void __thiscall FUN_00c77300(U32 nKey);   // 0x00c77300
};
struct cHashNodeD {
    U32 mKey;       // +0x00
    U32 mpNext04;   // +0x04
};
// ---- items of slice s00c75e70 end

// ---- items of slice s00c77380 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char    g_szSimulator[];                 // 0x013f09b4  "Simulator"
extern char    g_szAllocatorH[];                // 0x013ebb38  "...EASTL/allocator.h"
extern float   g_fMilliToSeconds;               // 0x013f9428  0.001f
extern float   g_fTwoTo32;                      // 0x013f4fd0  4.2949673e+09f
extern float   g_fUFOSpeedSlow;                 // 0x01465544
extern float   g_fUFOSpeedFast;                 // 0x013ec4d0
extern uint32_t g_nEmbassyEvent;                // 0x01694884  k_placeembassy
extern uint32_t g_bCheatWarningLatch;           // 0x01694570
extern uint32_t g_cheatEventKey;                // 0x01694564
extern uint32_t g_cheatEventA;                  // 0x01694568
extern uint32_t g_cheatEventB;                  // 0x0169456c
extern uint32_t g_nUFOInventoryArg;             // 0x0150d6dc
extern uint32_t g_nCheatFlagKey;                // 0x061f1454
extern uint8_t g_vtblPlayerPlanetData[];        // 0x01465d64  vtable object
extern uint8_t g_vtblSpacePlayerWarData[];      // 0x01472cc8  vtable object
extern wchar_t g_wstrCheatWarning[];            // 0x01472cd8  L"Hey, you just cheated! ..."
extern wchar_t g_wstrEmpty16[];                 // 0x01667bac  eastl::gEmptyString16
void*   __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                 // 0x00f473a0
void*   __cdecl memcpy(void* pDst, const void* pSrc, uint32_t nBytes);          // 0x011e0744
void*   __cdecl eastlMoveRange(void* pDst, const void* pSrc, uint32_t nBytes);  // 0x0099efa0
void*   __cdecl RBTreeIncrement(void* pNode);                                   // 0x00921580
void    __cdecl RBTreeErase(void* pNode, void* pAnchor);                        // 0x00921880
bool    __cdecl ReadInt32(void* pStream, void* pDst, uint32_t nCount, int32_t nEndian);   // 0x0093a780
bool    __cdecl WriteUint32(void* pStream, void* pSrc, uint32_t nCount, int32_t nEndian); // 0x0093aa70
void    __cdecl ReadKey3(void* pStream, void* pKey3);                           // 0x00ae2ed0
void    __cdecl WriteBits6(void* pStream, const uint32_t* pBits);               // 0x00c766b0
void*   __cdecl GetStarRecord(void* pStarManager);                              // 0x00ba6dc0
void*   __cdecl SortBanners(void* pStarRecord, uint32_t nHandle);               // 0x00b8de30
int32_t __cdecl GetAvatar(void* pList);                                         // 0x00b1fdb0
void*   __cdecl GetEmpireByID(void* pStarManager, uint32_t nEmpireId);          // 0x00ba9370
bool    __cdecl IsHostileToPlayer(void* pEmpire);                               // 0x00c309e0
void*   __cdecl GetUniverseContext();                                           // 0x01021080
void*   __cdecl GetActivePlanetRecord();                                        // 0x010212a0
float   __cdecl GetBackgroundFighterDPS(void* pEmpire);                         // 0x00c31890
uint32_t __cdecl GetPlayerEmpireID(uint32_t nA, uint32_t nB);                   // 0x01021090
void*   __cdecl GetSpaceRelationshipTuning();                                   // 0x010407c0
uint32_t __cdecl GetEmbassyTuningValue(void* pTuning);                          // 0x01040870
bool    __cdecl StarHasEmbassyFlag(void* pStarRecord, uint32_t nFlag);          // 0x00b8e040
void    __cdecl StarClearEmbassyFlag(void* pStarRecord, uint32_t nFlag);        // 0x00b8e7d0
void*   __cdecl RelationshipManager(uint32_t nA, uint32_t nB);                  // 0x00b3d2c0
void    __cdecl RecordRelationshipEvent(void* pMgr, uint32_t nA, uint32_t nB,
                                        uint32_t nEvent, float fValue);         // 0x00d06240
uint32_t __cdecl GetCommContext(void* pStarRecordRef);                          // 0x00ce6950
class cStarRecordRef {
public:
    uint32_t GetCommContext();                      // 0x00ce6950
};
void*   __cdecl GetCurrentGameMode();                                           // 0x00b5b800
void*   __cdecl SpaceGameGet();                                                 // 0x01002bd0
void*   __cdecl GetPlayerTribe(void* pGame);                                    // 0x00bfc5f0
void    __cdecl TribeCheatDisable(uint32_t nA, uint32_t nB);                    // 0x00fe5430
void*   __cdecl EffectsManager();                                               // 0x0067ddd0
void*   __cdecl GetSolarSystem(void* pStar);                                    // 0x00c8b770
void    __cdecl ActivateSolarSystemGraphics(void* pSolarSystem);                // 0x00c86c70
void*   __cdecl GetActiveStar();                                                // 0x01021230
void*   __cdecl AspectManager();                                                // 0x00b3d470
void*   __cdecl GetUFOSimulator();                                              // 0x00ffbe50
void*   __cdecl GetPlayerInventory(void* pSim);                                 // 0x00a1ad60
void    __cdecl SetUFODestination(void* pInventory, const void* pVec);          // 0x00c3bfe0
void    __cdecl ResetInventoryFlags(void* pInventory);                          // 0x00ff3df0
void*   __cdecl GetRelationshipTable(void* pKey);                               // 0x00b3d3d0
void    __cdecl RecordRelationshipEntry(void* pTable, uint32_t nFlag);          // 0x0103fba0
void*   __cdecl EventLog(uint32_t a, uint32_t b, uint32_t c, uint32_t d,
                         uint32_t e, uint32_t f);                               // 0x00b3d3e0
void    __cdecl PostFeedbackEvent(void* pLog, uint32_t a, uint32_t b, uint32_t c,
                                  uint32_t d, uint32_t e, uint32_t f);          // 0x00dd8640
void    __cdecl ConfigureInventory(uint32_t a, uint32_t b, uint32_t c);         // 0x00599440
void*   __cdecl StartUFOCheat();                                                // 0x00fd9c60
void    __cdecl FinishUFOCheat(void* p);                                        // 0x00fda5e0
void    __cdecl SetCheatWarningText(const void* pDst, const void* pSrc);        // 0x00454cb0
class cGonzagoTimer_s00c7_7380 {
public:
    uint64_t mPad00[4];                             // +0x00 0x20 bytes, 8-byte aligned
    ~cGonzagoTimer_s00c7_7380();                               // 0x00b638b0
};
struct cFlagNode {
    uint32_t   mKey;                                // +0x00
    int32_t    mValue;                              // +0x04
    cFlagNode* mpNext;                              // +0x08
};
struct cU32Node_s00c7_7380 {
    uint32_t   mKey;                                // +0x00
    cU32Node_s00c7_7380*  mpNext;                              // +0x04
};
struct cKey3Node {
    uint32_t   mKey0;                               // +0x00
    uint32_t   mKey1;                               // +0x04
    uint32_t   mKey2;                               // +0x08
    cKey3Node* mpNext;                              // +0x0c
};
class cRehashPolicy {
public:
    uint8_t mPad00[0x1c];                           // +0x00 (the eastl prime_rehash_policy block)
    void GetRehashRequired(void* pOut, uint32_t nBuckets, uint32_t nCount, int32_t bForce); // 0x00921440
};
class cHashtableHeader {
public:
    uint8_t   mPad00[0x04];                         // +0x00
    void**    mpBuckets;                            // +0x04
    uint32_t  mnBucketCount;                        // +0x08
    uint32_t  mnElementCount;                       // +0x0c
    cRehashPolicy mRehash10;                        // +0x10
    uint32_t  mnNodeSize;                           // +0x2c

    void InsertU32(void* ppOut, const uint32_t* pKey, bool bFlag);  // 0x00de5df0
    void DoFreeNodes(void* pBuckets, uint32_t nCount);             // 0x006b6570
    void* AllocNode(const void* pKey);                             // 0x00b576d0
    void Rehash(uint32_t nNewBuckets);                             // 0x00c76440
    void** Insert3(void** ppOut, const uint32_t* pKey, bool bFlag); // 0x00c77700
    void Find3(void** ppOut, const uint32_t* pKey);                // 0x00c77680
    void DoFreeNodes3(void* pBuckets, uint32_t nCount);            // 0x00a42fe0
    void DoFreeNodesFlag(void* pBuckets, uint32_t nCount);         // 0x00a1b6c0
    void FindFlag(void** ppOut, const uint32_t* pKey);             // 0x00645ed0
    void InsertFlag(void** ppOut, const uint32_t* pKey, uint32_t nValue); // 0x00c15fd0
};
struct cTreeNode {
    cTreeNode* mpLeft;                              // +0x00
    cTreeNode* mpRight;                             // +0x04
    cTreeNode* mpParent;                            // +0x08
    uint8_t    mPad0c[0x04];                        // +0x0c
};
class cPlayerTree {
public:
    uint32_t   mUnk00;                              // +0x00
    cTreeNode* mpEnd;                               // +0x04
    cTreeNode* mpHead;                              // +0x08
    cTreeNode* mpRoot;                              // +0x0c
    uint32_t   mb10;                                // +0x10
    uint32_t   mnCount;                             // +0x14
    cTreeNode* End() const { return mpEnd; }
    void Find(cTreeNode** ppOut, const uint32_t* pKey);             // 0x00e5c780
};
struct cEmbassyNode_s00c7_7380 {
    cTreeNode  mNode;                               // +0x00
    void*      mStarRecord;                         // +0x10
    int32_t    mnEmbassyTimer;                      // +0x18 int accumulator
};
struct cEmbassyEntry {
    uint32_t mFlag;                                 // +0x00
    uint8_t  mPad04[0x10];                          // +0x04
    float    mfTimer;                               // +0x14
};
class cStarRecordView {
public:
    uint8_t        mPad00[0x134];                   // +0x000
    cEmbassyEntry* mpEmbassyBegin;                  // +0x134
    cEmbassyEntry* mpEmbassyEnd;                    // +0x138
};
struct cPtrVecEntry {
    void** mpBegin;                                 // +0x00
    void** mpEnd;                                   // +0x04
    uint8_t mPad08[0x0c];                           // +0x08
};
struct cEntry20 {
    uint32_t mKey;                                  // +0x00
    uint8_t  mPad04[0x10];                          // +0x04
};
struct cEntry8 {
    uint32_t mKey;                                  // +0x00
    uint32_t mBits;                                 // +0x04
};
struct cInsertResult {
    void*   mpNode;                                 // +0x00
    void**  mpBucket;                               // +0x04
    uint8_t mbInserted;                             // +0x08
};
template <typename T>
class cVector_s00c7_7380 {
public:
    T* mpBegin;                                     // +0x00
    T* mpEnd;                                       // +0x04
    T* mpCap;                                       // +0x08
    uint32_t Count() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t Capacity() const { return (uint32_t)(mpCap - mpBegin); }
    void Reserve(uint32_t nCount);                  // 0x00c77a00
    void Insert(T* pPos, const T* pValue);          // 0x00c78280
};
struct cEmbassyList {
    cEmbassyList* mpChild;                          // +0x00
    cEmbassyList* mpNext;                           // +0x04
    uint8_t       mPad08[0x10];                     // +0x08
    void*         mpVtbl18;                         // +0x18
    uint8_t       mPad1c[0x0c];                     // +0x1c
    uint8_t       mTimer28[0x20];                   // +0x28 cGonzagoTimer
    void Destroy(cEmbassyList* pHead);              // 0x00c77b10
};
struct cPlayerPlanetData {
    uint8_t mPad00[0x08];                           // +0x00
    void*   mpVtbl08;                               // +0x08
    uint8_t mPad0c[0x04];                           // +0x0c
    void*   mpBlock10;                              // +0x10
    uint8_t mPad14[0x14];                           // +0x14
    void*   mpBlock28;                              // +0x28
    uint8_t mPad2c[0x14];                           // +0x2c
    void*   mpBlock40;                              // +0x40
    uint8_t mPad44[0x14];                           // +0x44
    void*   mpBlock58;                              // +0x58
    uint8_t mPad5c[0x14];                           // +0x5c
    void*   mpBlock70;                              // +0x70
    uint8_t mPad74[0x14];                           // +0x74
    uint8_t mTimer88[0x20];                         // +0x88 cGonzagoTimer
};
class ISerializerStream_s00c7_7380 {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();                            // +0x1c element marker
    virtual void* v20();                            // +0x20 returns the active IO provider
};
class IIOProvider {
public:
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void* v18();                            // +0x18 EA::IO stream
};
static void* GetIOStream(ISerializerStream_s00c7_7380* pStream)
{
    return ((IIOProvider*)pStream->v20())->v18();
}
namespace SP {
class cPlayer_s00c7_7380 {
public:
    void* mpVtbl00;                                 // +0x0000
    void* mpVtbl04;                                 // +0x0004
    uint8_t mPad08[0x38 - 0x08];                    // +0x0008
    cHashtableHeader mSet38;                        // +0x0038  key3 member set (0x38..0x67)

    uint8_t mPad68[0x698 - 0x68];                   // +0x0068
    cHashtableHeader mFlagMap698;                   // +0x0698  flag hashtable (0x698..0x6c7)

    uint8_t mPad6c8[0x10b4 - 0x6c8];                // +0x06c8
    void*   mpBlock10b4;                            // +0x10b4

    uint8_t mPad10b8[0x111c - 0x10b8];              // +0x10b8
    cHashtableHeader mKeySet111c;                   // +0x111c  single-word key set (0x111c..0x114b)

    uint8_t mPad114c[0x11f0 - 0x114c];              // +0x114c
    uint8_t mbCheatLatched;                         // +0x11f0

    uint8_t mPad11f1[0x11f8 - 0x11f1];              // +0x11f1
    cPlayerTree mWarEvents11f8;                     // +0x11f8  war-event rbtree

    uint8_t mPad1210[0x1228 - 0x1210];              // +0x1210
    cPlayerTree mEmbassyTree;                       // +0x1228  embassy rbtree

    // 0x00c77380
    bool GetFlagValue(uint32_t nKey, int32_t* pnOut);
    // 0x00c773d0
    bool HasFlag(uint32_t nKey);
    // 0x00c77410
    bool IsSpace();
    // 0x00c77450
    void RemoveEmbassyFromPlanet(void* pStarRecordRef);  // 0x00c77450 (SP::cPlayer::RemoveEmbassyFromPlanet)
    // 0x00c774b0
    void UpdateEmbassyEffects(int32_t nElapsedMs);
    // 0x00c77bf0
    bool HasFlagOrInsert(uint32_t nKey);
    // 0x00c77c50
    bool HasEntryInSet(const uint32_t* pKey);
    // 0x00c77c90
    void LatchCheatDetected();
    // 0x00c78420
    void AddToSet(const uint32_t* pKey);
    // 0x00c78450
    void NoteWarEndedWithPlayer(void* pEmpire);  // 0x00c78450 (SP::cPlayer::NoteWarEndedWithPlayer)
    // 0x00c772c0 - presence of an arbitrary key in the +0x111c set
    bool HasCheatFlagEx(const uint32_t* pKey);
};
}
namespace SP {
class cPlayerCommand {
public:
    void* mpVtbl00;                                 // +0x0000 (cPlayer+0x0034)
    uint8_t mPad04[0x34 - 0x04];                    // +0x0004
    // 0x00c77d30
    bool ProcessCommand(uint32_t nCommand, int32_t* pArg);
};
}
bool SP::cPlayer_s00c7_7380::HasCheatFlagEx(const uint32_t* pKey)
{
    uint32_t nKey = *pKey;
    int32_t nFound = 0;
    for (cU32Node_s00c7_7380* pNode = (cU32Node_s00c7_7380*)mKeySet111c.mpBuckets[nKey % mKeySet111c.mnBucketCount];
         pNode != 0; pNode = pNode->mpNext) {
        if (pNode->mKey == nKey)
            ++nFound;
    }
    return nFound != 0;
}
// ---- items of slice s00c77380 end

// ---- items of slice s00c7a1f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTimerElem {                    // eastl::pair<unsigned, SP::cGonzagoTimer>, stride 0x28
    uint32_t mKey;                     // +0x00
    uint32_t mPad04;                   // +0x04
    uint32_t mTimerVtable;             // +0x08
    uint32_t mRefCount;                // +0x0c
    uint32_t mElapsedLo;               // +0x10
    uint32_t mElapsedHi;               // +0x14
    uint32_t mBaseLo;                  // +0x18
    uint32_t mBaseHi;                  // +0x1c
    uint8_t  mbRunning;                // +0x20
    uint8_t  mPad21[0x03];             // +0x21
    uint32_t mFn;                      // +0x24

    // cGonzagoTimer copy constructor (constructs this from src); __thiscall.
    void Construct(const cTimerElem* src);                              // 0x00c76f10
};
void ReadInt32(void* reader, int* out, int count, int flags);          // 0x0093a780
class IStreamNode {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void* GetReader();           // +0x18
    virtual void EndChunk();             // +0x1c
    virtual IStreamNode* GetSubNode();   // +0x20
};
struct U32Vector {
    uint32_t* mpBegin;                   // +0x0
    uint32_t* mpEnd;                     // +0x4
    uint32_t* mpCapacity;                // +0x8

    void Clear();                        // inlined clear()
    void Reserve(uint32_t n);            // 0x00c77b60
    void PushBack(const uint32_t& value); // fast path + slow DoInsertValue
    void DoInsertValue(uint32_t* position, const uint32_t& value);  // 0x00cd0550
};
void EastlMove(void* dst, const void* src, unsigned bytes);            // 0x011e0744
void U32Vector::Clear()
{
    EastlMove(mpBegin, mpEnd, 0);
    mpEnd -= (mpEnd - mpBegin);
}
void U32Vector::PushBack(const uint32_t& value)
{
    if (mpEnd < mpCapacity) {
        uint32_t* p = mpEnd;
        mpEnd = p + 1;
        if (p)
            *p = value;
    } else {
        DoInsertValue(mpEnd, value);
    }
}
cTimerElem* TimerConstructRange(cTimerElem* first, cTimerElem* last, cTimerElem* dst); // 0x00c77160
cTimerElem* TimerCopyBackward(cTimerElem* first, cTimerElem* last, cTimerElem* dst);  // 0x00c77250
void TimerDestroyRange(cTimerElem* first, cTimerElem* last, cTimerElem* dst);         // 0x0100daa0
void* EastlAllocate(unsigned size, const char* name, int flags, unsigned debugFlags,
                    const char* file, int line);                        // 0x00f473a0
void  EastlFree(void* p);                                               // 0x00f47380
struct cTimerVector {
    cTimerElem* mpBegin;                 // +0x0
    cTimerElem* mpEnd;                   // +0x4
    cTimerElem* mpCapacity;              // +0x8

    void Insert(cTimerElem* position, const cTimerElem& value);          // 0x00c7aa40
};
// ---- items of slice s00c7a1f0 end

// ---- items of slice s00c7b120 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cSPTimer_s00c7_b120 {
    uint32_t mpVftblBase;                           // 0x00
    uint32_t mRefCount;                             // 0x04
    uint32_t mElapsedLo;                            // 0x08
    uint32_t mElapsedHi;                            // 0x0c
    uint32_t mBaseLo;                               // 0x10
    uint32_t mBaseHi;                               // 0x14
    bool     mbRunning;                             // 0x18
    uint32_t pad_19[3];                             // 0x19..0x1c
    void*    mpFn;                                  // 0x1c
    void Start();                                   // 0x00BC30F0
    void Restart();                                 // 0x00BC3130
};
}
namespace SP {
struct cGonzagoTimer_s00c7_b120 {
    cSPTimer_s00c7_b120 mTimer;                                // 0x00 (filled by the ctor)
    uint32_t pad_20[2];                             // 0x20
    cGonzagoTimer_s00c7_b120();                                // 0x00B63890
    ~cGonzagoTimer_s00c7_b120();                               // 0x00B638B0
};
}
namespace SP {
struct cSpacePlayerWarData_s00c7_b120 {
    uint32_t mpVftbl00;                             // 0x00
    uint32_t mInt04;                                // 0x04
    uint32_t mEnemyEmpireID;                        // 0x08
    uint32_t mInt0c;                                // 0x0c
    cSPTimer_s00c7_b120 mTimer;                                // 0x10
    uint32_t mPlayerStartStars;                     // 0x30
    uint32_t mEnemyStartStars;                      // 0x34
    uint32_t mPlayerCaptured;                       // 0x38
    uint32_t mEnemyCaptured;                        // 0x3c
};
}
namespace SP {
struct WarFlagMap {
    uint32_t* __thiscall operator[](const uint32_t* key);   // 0x00F41AA0
};
}
namespace SP {
struct WarDataMap {
    cSpacePlayerWarData_s00c7_b120* __thiscall operator[](const uint32_t* key); // 0x00C7BC50
};
}
namespace SP {
class cPlayer_s00c7_b120 {
public:
    uint32_t  pad_000[0x84/4];                      // 0x000..0x084
    int       mEmpireID;                            // 0x084
    uint32_t  pad_088[0x11d8/4 - 0x088/4];          // 0x088..0x11d8
    WarFlagMap mWarFlags;                           // 0x11d8
    uint32_t  pad_11dc[0x11f8/4 - 0x11dc/4];        // 0x11dc..0x11f8
    WarDataMap mWarData;                            // 0x11f8
    uint32_t  pad_11fc[0x1214/4 - 0x11fc/4];        // 0x11fc..0x1214
    // a 0x1214-based vector of 0x28-byte elements (the war timers); 0x08 = capacity ptr, 0x04 = end
    uint32_t  mTimerBegin;                          // 0x1214
    uint32_t  mTimerEnd;                            // 0x1218
    uint32_t  mTimerCapEnd;                         // 0x121c

    void NoteWarStartedWithPlayer(int otherPlayer);         // 0x00C7BD40
    void NoteWarEndedWithPlayer(int otherPlayer);           // 0x00C78450
    void ResetWarDataWithPlayer(int otherPlayer);           // 0x00C7BE30
    void FUN_00c7ba90(int starRecord);                      // 0x00C7BA90

    void SetWarFlag1(int key);                              // 0x00C7BB60
    void SetWarFlag2(int key);                              // 0x00C7BB80
    void SetWarFlag4(int key);                              // 0x00C7BBA0
    void SetWarFlag8(int key, char value);                  // 0x00C7BBC0
    void SetWarFlag10(int key, char value);                 // 0x00C7BBF0
    void SetWarFlag20(int key, char value);                 // 0x00C7BC20
    cSpacePlayerWarData_s00c7_b120* WarDataAt(const uint32_t* key);    // 0x00C7BC50
};
}
namespace SP {
void FUN_00c7b120();                                // 0x00C7B120
}
namespace SP {
void FUN_00c7b390();                                // 0x00C7B390
}
namespace SP {
void FUN_00c7b510();                                // 0x00C7B510
}
namespace SP {
void FUN_00c7b670();                                // 0x00C7B670
}
namespace SP {
void FUN_00c7b790();                                // 0x00C7B790
}
namespace SP {
void FUN_00c7bea0();                                // 0x00C7BEA0
}
namespace SP {
void FUN_00c76f10(void* timer);                     // 0x00C76F10
}
namespace SP {
void FUN_00c7aa40(void* end, void* key);            // 0x00C7AA40
}
namespace SP {
void FUN_00c7ad40(void* player, int starRecord);    // 0x00C7AD40
}
namespace SP {
int* FUN_00c308d0(void* empire);                    // 0x00C308D0 (cEmpire::GetStars)
}
namespace SP {
void FUN_00c77bf0(int a);                           // 0x00C77BF0
}
namespace SP {
void*  FUN_01021300();                                                          // 0x01021300 GetPlayerEmpire
}
namespace SP {
void   FUN_00c7aa40(void* end, const void* key);                                // 0x00C7AA40
}
// ---- items of slice s00c7b120 end

// @ 0x00ba2af0
void __cdecl FUN_00ba2af0()
{
  void* local = 0;
  void* pm = SP_PropertyManager();
  (*(bool(__thiscall*)(void*, int, int, void**))((*(void***)pm)[0x2c / 4]))(pm, 0x48f5d7cd, 0xad56080c, &local);
  if (local) Release(local);
}

// @ 0x00ba2c70
uint8_t __stdcall FUN_00ba2c70(int key, void* p)
{
  if (key == 0xf62def && *(int*)((char*)p + 0x10) == (int)0xad56080c &&
      *(int*)((char*)p + 0x18) == 0x48f5d7cd)
    FUN_00ba2af0();
  return 0;
}

// @ 0x00ba2ca0
void __thiscall W::Run_00ba2ca0(void* p2)
{
  uint32_t v = *(uint32_t*)((char*)p2 + 0xc);
  void* io = (*(void*(__thiscall*)(void*))((*(void***)this)[0x20 / 4]))(this);
  void* wr = (*(void*(__thiscall*)(void*))((*(void***)io)[0x18 / 4]))(io);
  EA_IO_WriteUint32(wr, &v, 1, 0);
  (*(void(__thiscall*)(void*))((*(void***)this)[0x1c / 4]))(this);
}

// @ 0x00ba2d80
char __thiscall W::Run_00ba2d80(void* p2)
{ (void)p2; return 1; }

// @ 0x00ba2e00
void __thiscall VecHdr::FreeNodes(void* arr, unsigned n)
{
  for (unsigned i = 0; i < n; ++i) {
    void* p = *((void**)arr + i);
    while (p != 0) {
      void* cur = p;
      p = *(void**)((char*)p + 8);
      if (*(void**)cur) Release(*(void**)cur);
      operator_delete__(cur);
    }
    *((void**)arr + i) = 0;
  }
}

// @ 0x00ba2e50
void* __cdecl FUN_00ba2e50(int lo, int hi, uint32_t* key)
{
  int n = (hi - lo) >> 4;
  int left = n;
  if (left > 0) {
    do {
      int mid = left >> 1;
      uint32_t* e = (uint32_t*)(mid * 0x10 + lo);
      bool less;
      if (e[0] != key[0]) less = e[0] < key[0];
      else if (e[2] != key[2]) less = e[2] < key[2];
      else less = e[1] < key[1];
      if (less) { lo = (int)e + 0x10; left += -1 - mid; }
      else left = mid;
    } while (left > 0);
  }
  return (void*)lo;
}

// @ 0x00ba2f20
void __thiscall W::Run_00ba2f20()
{
  char* s = (char*)this;
  *(void**)s = (void*)0x1465dc8;
  ((CGZTimer*)(s + 0x80))->Dtor();
  if (*(void**)(s + 0x68)) operator_delete__(*(void**)(s + 0x68));
  if (*(void**)(s + 0x50)) operator_delete__(*(void**)(s + 0x50));
  if (*(void**)(s + 0x38)) operator_delete__(*(void**)(s + 0x38));
  if (*(void**)(s + 0x20)) operator_delete__(*(void**)(s + 0x20));
  if (*(void**)(s + 0x08)) operator_delete__(*(void**)(s + 0x08));
}

// @ 0x00ba2f90
void* __thiscall W::Run_00ba2f90()
{
  char* s = (char*)this;
  *(void**)s = (void*)0x1465d64;
  for (int off = 0x08; off <= 0x70; off += 0x18) {
    *(void**)(s + off) = 0; *(void**)(s + off + 4) = 0; *(void**)(s + off + 8) = 0;
  }
  *(void**)(s + 0x68) = 0; *(void**)(s + 0x6c) = 0; *(void**)(s + 0x70) = 0;
  ((CGZTimer*)(s + 0x80))->Dtor();
  uint8_t v = 0xff;
  *(uint8_t*)(s + 0xa0) = v; *(uint8_t*)(s + 0xa1) = v; *(uint8_t*)(s + 0xa2) = 0;
  return s;
}

// @ 0x00c754e0
void __stdcall FUN_00c754e0(cGameNounManager* self)
{
    if (self->GetKind() == 5) {
        void* avatar = self->GetAvatar();
        cStarManager* stars = (cStarManager*)FUN_00b3d2a0(avatar);
        cEmpire* empire = (cEmpire*)stars->GetEmpireByID();
        if (empire)
            empire->SetValue(0);
    }
}

// @ 0x00c755c0
void cDepthCounter::Increment(bool countIt)
{
    if (mDepth < 5) {
        mDepth = mDepth + 1;
        if (countIt)
            mTotal = mTotal + 1;
    }
}

// @ 0x00c755f0
void cDepthCounter::Decrement(bool countIt)
{
    if (0 < mDepth) {
        mDepth = mDepth - 1;
        if (countIt)
            mTotal = mTotal - 1;
    }
}

// @ 0x00c75e70
void __cdecl WriteTimerSequence(ISerializer* pWriter, cVector<cTimerPair>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (cTimerPair* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nId = pItem->mId;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nId, 1, 0);
        pItem->mTimer.Write(pWriter);
    }
    pWriter->EndItem();
}

// @ 0x00c75f10
void __cdecl WriteEmbassyMap(ISerializer* pWriter, cEmbassyMap& map)
{
    U32 nCount = map.mnSize;
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    cEmbassyNode* pEnd = (cEmbassyNode*)&map.mAnchor;
    for (cEmbassyNode* pNode = (cEmbassyNode*)map.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = (cEmbassyNode*)RBTreeIncrement(&pNode->mBase)) {
        U32 nKey = pNode->mKey;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nKey, 1, 0);
        pWriter->EndItem();
        U32 nInt04 = pNode->mData.mInt04;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nInt04, 1, 0);
        U32 nInt00 = pNode->mData.mInt00;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nInt00, 1, 0);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// @ 0x00c76010
void __cdecl WriteKeyBoolMap(ISerializer* pWriter, cVector<cKeyBoolPair>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (cKeyBoolPair* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nKey = pItem->mKey;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nKey, 1, 0);
        pWriter->EndItem();
        pItem->mValue.Write(pWriter);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// @ 0x00c760c0
bool __cdecl FixupPlayerPlanetData(void* pCtx, cVector<cKeyBoolPair>& items)
{
    for (cKeyBoolPair* pItem = items.mpBegin; pItem != items.mpEnd; ++pItem) {
        if (&pItem->mValue != 0)
            ((IRegisterHost*)pCtx)->Register(&pItem->mValue, &g_1579600, L"PlayerPlanetData");
    }
    return true;
}

// @ 0x00c76100
void __cdecl WriteElem20Vector(ISerializer* pWriter, cVector<CElem20>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (CElem20* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem)
        FUN_00c75ba0(pWriter, pItem);
    pWriter->EndItem();
}

// @ 0x00c76170
bool __cdecl WriteObjectLists(ISerializer* pWriter, cVector<CObjectList>& items)
{
    for (CObjectList* pList = items.mpBegin; pList != items.mpEnd; ++pList) {
        for (U32 i = 0; i < (U32)(pList->mpEnd - pList->mpBegin); ++i)
            pList->mpBegin[i]->Write(pWriter);
    }
    return true;
}

// @ 0x00c761c0
void __cdecl WriteU32Vector(ISerializer* pWriter, cVector<U32>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (U32* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nValue = *pItem;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nValue, 1, 0);
    }
    pWriter->EndItem();
}

// @ 0x00c76250
void __cdecl WriteElem16Vector(ISerializer* pWriter, cVector<CElem16>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (CElem16* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        FUN_00ae2e40(pWriter, pItem);
        pWriter->EndItem();
        bool bValue = pItem->mb00c != 0;
        IO_WriteBool8(pWriter->GetStreamHolder()->GetStream(), &bValue, 1);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// @ 0x00c76300
void __cdecl WriteElem8Vector(ISerializer* pWriter, cVector<CElem8>& items)
{
    U32 nCount = (U32)(items.mpEnd - items.mpBegin);
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    for (CElem8* pItem = items.mpBegin, *pEnd = items.mpEnd; pItem != pEnd; ++pItem) {
        U32 nId = pItem->mId;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nId, 1, 0);
        pWriter->EndItem();
        bool bValue = pItem->mb004 != 0;
        IO_WriteBool8(pWriter->GetStreamHolder()->GetStream(), &bValue, 1);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// @ 0x00c76440
void __thiscall cHashTableA::Rehash(U32 nBuckets)
{
    cHashNodeA** pNewBuckets = AllocBucketArray(nBuckets);
    for (U32 i = 0; i < mnBuckets; ++i) {
        cHashNodeA* pNode = mpBuckets[i];
        while (pNode != 0) {
            U32 nIndex = (pNode->mInt08 ^ pNode->mKey) % nBuckets;
            mpBuckets[i] = (cHashNodeA*)pNode->mpNext0c;
            pNode->mpNext0c = (U32)pNewBuckets[nIndex];
            pNewBuckets[nIndex] = pNode;
            pNode = mpBuckets[i];
        }
    }
    cHashNodeA** pOldBuckets = mpBuckets;
    if (mnBuckets > 1 && pOldBuckets != (cHashNodeA**)mpSentinel) {
        if ((U32)pOldBuckets >= mpAllocBegin && (U32)pOldBuckets < mpAllocEnd) {
            *pOldBuckets = (cHashNodeA*)mpFreeList;
            mpFreeList = (U32)pOldBuckets;
            mpBuckets = pNewBuckets;
            mnBuckets = nBuckets;
            return;
        }
        operator_delete(pOldBuckets);
    }
    mpBuckets = pNewBuckets;
    mnBuckets = nBuckets;
}

// @ 0x00c76790
void __thiscall cPlayer_s00c7_5e70::AddWarCaptureIncrement(U32 nAttacker, U32 nDefender)
{
    U32 nPlayer = GetPlayerEmpireID();
    if (nAttacker == nPlayer || nDefender == nPlayer) {
        U32 nOther = nAttacker;
        if (nAttacker == nPlayer)
            nOther = nDefender;
        cRBNodeBase* pFound;
        mWars.Find(&pFound, &nOther);
        if (pFound != (cRBNodeBase*)&mWars.mAnchor) {
            cWarNode* pNode = (cWarNode*)pFound;
            if (nAttacker == nPlayer)
                ++pNode->mInt50;
            else
                ++pNode->mInt4c;
        }
    }
}

// @ 0x00c76800
int __thiscall cPlayer_s00c7_5e70::GetPeacePriceForPlayer(cPlayer_s00c7_5e70* pEnemy)
{
    cRBNodeBase* pFound;
    U32 nEnemyId = pEnemy->mEmpireId;
    mWars.Find(&pFound, &nEnemyId);
    if (pFound == (cRBNodeBase*)&mWars.mAnchor)
        return -1;

    cWarNode* pNode = (cWarNode*)pFound;
    cPlayer_s00c7_5e70* pMe = (cPlayer_s00c7_5e70*)FUN_01021300();

    U64 nElapsed = pNode->mTimer.GetElapsedTime();
    float fElapsed = (float)nElapsed * g_f0p001;
    int nElapsedPrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceElapsedSecondsFactor() * fElapsed);

    cStarList* pMyStars = (cStarList*)FUN_00c308d0_s00c7_5e70(pMe);
    int nMyStarCount = (int)(pMyStars->mpEnd - pMyStars->mpBegin);
    int nMySizePrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePricePlayerSizeFactor() * (float)nMyStarCount);

    cStarList* pEnemyStars = (cStarList*)FUN_00c308d0_s00c7_5e70(pEnemy);
    int nEnemyStarCount = (int)(pEnemyStars->mpEnd - pEnemyStars->mpBegin);
    int nEnemySizePrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceEnemySizeFactor() * (float)nEnemyStarCount);

    int nCaptureDelta = (int)pNode->mInt50 - (int)pNode->mInt54;
    int nCapturePrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceCaptureFactor() * nCaptureDelta);

    float fRelationship = ((IRelationshipManager*)RelationshipManager())->GetRelationship(pEnemy, pMe->mEmpireId, 0);
    int nRelationshipPrice = RoundFloat(((IEconTuning*)EconomyTuning())->GetPeacePriceRelationshipFactor() * fRelationship);

    int nTotal = nRelationshipPrice + nCapturePrice + nEnemySizePrice + nMySizePrice + nElapsedPrice;

    void* pStarRec = FUN_00baf700(StarManager(pEnemy));
    float fScale = FUN_010307a0(pStarRec, 0x686e2a4, 0x686e2a8) * nTotal;
    return RoundFloat(fScale);
}

// @ 0x00c769b0
float __thiscall cPlayer_s00c7_5e70::GetPlayerWarElapsedSeconds(cPlayer_s00c7_5e70* pOther)
{
    cRBNodeBase* pFound;
    U32 nEnemyId = pOther->mEmpireId;
    mWars.Find(&pFound, &nEnemyId);
    if (pFound != (cRBNodeBase*)&mWars.mAnchor) {
        cWarNode* pNode = (cWarNode*)pFound;
        U64 nElapsed = pNode->mTimer.GetElapsedTime();
        return (float)nElapsed * g_f0p001;
    }
    return 0.0f;
}

// @ 0x00c76a30
int __thiscall cPlayer_s00c7_5e70::GetPlayerWarCaptureDelta(cPlayer_s00c7_5e70* pOther)
{
    cRBNodeBase* pFound;
    U32 nEnemyId = pOther->mEmpireId;
    mWars.Find(&pFound, &nEnemyId);
    if (pFound != (cRBNodeBase*)&mWars.mAnchor) {
        cWarNode* pNode = (cWarNode*)pFound;
        return (int)pNode->mInt50 - (int)pNode->mInt54;
    }
    return 0;
}

// @ 0x00c76be0
int __thiscall cHashTableB::Erase(const U32* pKey)
{
    int nOldCount = (int)mnElements;
    U32 nIndex = *pKey % mnBuckets;
    cHashNodeB** pSlot = &mpBuckets[nIndex];

    if (*pSlot != 0) {
        cHashNodeB* pNode;
        do {
            pNode = *pSlot;
            if (*pKey == pNode->mKey)
                break;
            pSlot = (cHashNodeB**)&pNode->mpNext08;
        } while (pNode->mpNext08 != 0);

        while (*pSlot != 0) {
            pNode = *pSlot;
            if (*pKey != pNode->mKey)
                break;
            *pSlot = (cHashNodeB*)pNode->mpNext08;
            if (pNode != (cHashNodeB*)mpSentinel) {
                if ((U32)pNode >= mpAllocBegin && (U32)pNode < mpAllocEnd) {
                    pNode->mKey = mpFreeList;
                    mpFreeList = (U32)pNode;
                } else {
                    operator_delete(pNode);
                }
            }
            --mnElements;
        }
    }
    return nOldCount - (int)mnElements;
}

// @ 0x00c76c70
void __cdecl WriteHashMap(ISerializer* pWriter, cHashTableC& table)
{
    U32 nCount = table.mnElements;
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);

    cHashNodeC** pBucket = table.mpBuckets;
    cHashNodeC* pNode = *pBucket;
    if (pNode == 0) {
        do {
            ++pBucket;
        } while (*pBucket == 0);
        pNode = *pBucket;
    }
    cHashNodeC* pEnd = table.mpBuckets[table.mnBuckets];
    while (pNode != pEnd) {
        FUN_00ae2e40(pWriter, pNode);
        pWriter->EndItem();
        pNode = (cHashNodeC*)pNode->mpNext0c;
        if (pNode == 0) {
            do {
                ++pBucket;
                pNode = *pBucket;
            } while (pNode == 0);
        }
    }
    pWriter->EndItem();
}

// @ 0x00c76d60
void __cdecl WriteU32Map(ISerializer* pWriter, cU32Map& map)
{
    U32 nCount = map.mnSize;
    IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nCount, 1, 0);
    cU32Node* pEnd = (cU32Node*)&map.mAnchor;
    for (cU32Node* pNode = (cU32Node*)map.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = (cU32Node*)RBTreeIncrement(&pNode->mBase)) {
        U32 nKey = pNode->mKey;
        IO_WriteUint32(pWriter->GetStreamHolder()->GetStream(), &nKey, 1, 0);
        pWriter->EndItem();
        pNode->mValue.Write(pWriter);
        pWriter->EndItem();
    }
    pWriter->EndItem();
}

// @ 0x00c76e10
bool __cdecl FixupWarData(void* pCtx, cWarMap& map)
{
    cWarDataNode* pEnd = (cWarDataNode*)&map.mAnchor;
    for (cWarDataNode* pNode = (cWarDataNode*)map.mAnchor.mpNodeLeft; pNode != pEnd;
         pNode = (cWarDataNode*)RBTreeIncrement(&pNode->mBase)) {
        if (&pNode->mpValue != 0)
            ((IRegisterHost*)pCtx)->Register(&pNode->mpValue, &g_1579858, L"cSpacePlayerWarData");
    }
    return true;
}

// @ 0x00c76f10
cWarRec* __thiscall cWarRec::CopyFrom(const cWarRec& src)
{
    mInt00 = src.mInt00;
    _ReadWriteBarrier();
    mTimer.mpVftblBase = (U32)&g_vtblTimerBase;
    mTimer.mRefCount = 0;
    mTimer.mElapsed = src.mTimer.mElapsed;
    mTimer.mBase = src.mTimer.mBase;
    mTimer.mbRunning = src.mTimer.mbRunning;
    mTimer.mpFn = src.mTimer.mpFn;
    mTimer.mpVftblBase = (U32)&g_vtblTimer;
    return this;
}

// @ 0x00c76f60
cSpacePlayerWarData* __thiscall cSpacePlayerWarData::ctor(const cSpacePlayerWarData& src)
{
    mpVftbl00 = (U32)&g_vtblWarData;
    mEnemyEmpireID = src.mEnemyEmpireID;
    _ReadWriteBarrier();
    mTimer.mpVftblBase = (U32)&g_vtblTimerBase;
    mTimer.mRefCount = 0;
    mTimer.mElapsed = src.mTimer.mElapsed;
    mTimer.mBase = src.mTimer.mBase;
    mTimer.mbRunning = src.mTimer.mbRunning;
    mTimer.mpFn = src.mTimer.mpFn;
    mTimer.mpVftblBase = (U32)&g_vtblTimer;
    mPlayerStartStars = src.mPlayerStartStars;
    mEnemyStartStars = src.mEnemyStartStars;
    mPlayerCaptured = src.mPlayerCaptured;
    mEnemyCaptured = src.mEnemyCaptured;
    return this;
}

// @ 0x00c770d0
void __cdecl FUN_00c770d0(CSubList* pDst, U32 nCount, CSubList* pSrc)
{
    // cl colors the copy helper's out-param onto the nCount argument slot, so every call
    // overwrites the count the next call passes as its fifth argument; the loop bound is
    // the register copy in nRemaining.
    U32 nRemaining = nCount;
    if (nCount <= 0)
        return;
    do {
        if (pDst != 0) {
            U32 nSub = (U32)(pSrc->mpEnd - pSrc->mpBegin);
            U32* pNew;
            if (nSub != 0)
                pNew = (U32*)operator_new(nSub * 4, g_szSimulator_s00c7_5e70, 0, 0, g_szAllocator, 0xd1);
            else
                pNew = 0;
            pDst->mpBegin = pNew;
            pDst->mpEnd = pNew;
            pDst->mpCap = pNew + nSub;
            U32* pNewEnd;
            FUN_00bdaa40_s00c7_5e70(&nCount, pSrc->mpBegin, pSrc->mpEnd, pNew, (void*)nCount);
            pNewEnd = (U32*)nCount;
            pDst->mpEnd = pNewEnd;
        }
        --nRemaining;
        ++pDst;
    } while (nRemaining > 0);
}

// @ 0x00c77160
CElemTimer* __cdecl FUN_00c77160(const CElemTimer* pSrcBegin, const CElemTimer* pSrcEnd, CElemTimer* pDst)
{
    if (pSrcBegin == pSrcEnd)
        return pDst;
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin, ++pDst) {
        if (pDst != 0) {
            pDst->mId = pSrcBegin->mId;
            pDst->mTimer.mdVtbl = (U32)&g_vtblTimerBase;
            pDst->mTimer.mnRef = 0;
            pDst->mTimer.mElapsed = pSrcBegin->mTimer.mElapsed;
            pDst->mTimer.mBase = pSrcBegin->mTimer.mBase;
            pDst->mTimer.mbRunning = pSrcBegin->mTimer.mbRunning;
            pDst->mTimer.mpFn = pSrcBegin->mTimer.mpFn;
            pDst->mTimer.mdVtbl = (U32)&g_vtblTimer;
        }
    }
    return pDst;
}

// @ 0x00c771e0
CElemTimer* __cdecl FUN_00c771e0(const CElemTimer* pSrcBegin, const CElemTimer* pSrcEnd, CElemTimer* pDst)
{
    if (pSrcBegin == pSrcEnd)
        return pDst;
    for (; pSrcBegin != pSrcEnd; ++pSrcBegin, ++pDst) {
        pDst->mId = pSrcBegin->mId;
        pDst->mTimer.mElapsed = pSrcBegin->mTimer.mElapsed;
        pDst->mTimer.mBase = pSrcBegin->mTimer.mBase;
        pDst->mTimer.mbRunning = pSrcBegin->mTimer.mbRunning;
        pDst->mTimer.mpFn = pSrcBegin->mTimer.mpFn;
    }
    return pDst;
}

// @ 0x00c77250
CElemTimer* __cdecl FUN_00c77250(const CElemTimer* pFirst, const CElemTimer* pLast, CElemTimer* pResult)
{
    if (pFirst == pLast)
        return pResult;
    do {
        --pLast;
        --pResult;
        pResult->mId = pLast->mId;
        pResult->mTimer.mElapsed = pLast->mTimer.mElapsed;
        pResult->mTimer.mBase = pLast->mTimer.mBase;
        pResult->mTimer.mbRunning = pLast->mTimer.mbRunning;
        pResult->mTimer.mpFn = pLast->mTimer.mpFn;
    } while (pLast != pFirst);
    return pResult;
}

// @ 0x00c772c0
bool __thiscall cHashTableD::Contains(U32 nKey)
{
    int nCount = 0;
    cHashNodeD* pNode = (cHashNodeD*)(*(U32*)(mpBuckets + (nKey % mnBuckets) * 4));
    while (pNode != 0) {
        if (nKey == pNode->mKey)
            ++nCount;
        pNode = (cHashNodeD*)pNode->mpNext04;
    }
    return nCount != 0;
}

// @ 0x00c77300
void __thiscall cHashTableD::FUN_00c77300(U32 nKey)
{
    mSub.FUN_006b6740(&nKey);
}

// @ 0x00c77380
bool SP::cPlayer_s00c7_7380::GetFlagValue(uint32_t nKey, int32_t* pnOut)
{
    cHashtableHeader* pMap = &mFlagMap698;
    void* aIter[2];
    pMap->FindFlag(aIter, &nKey);
    cFlagNode* pNode = (cFlagNode*)aIter[0];
    if (pNode != (cFlagNode*)pMap->mpBuckets[pMap->mnBucketCount]) {
        *pnOut = pNode->mValue;
        return true;
    }
    return false;
}

// @ 0x00c773d0
bool SP::cPlayer_s00c7_7380::HasFlag(uint32_t nKey)
{
    cHashtableHeader* pMap = &mFlagMap698;
    void* aIter[2];
    pMap->FindFlag(aIter, &nKey);
    return (cFlagNode*)aIter[0] != (cFlagNode*)pMap->mpBuckets[pMap->mnBucketCount];
}

// @ 0x00c77410
bool SP::cPlayer_s00c7_7380::IsSpace()
{
    const uint32_t nKey = 0x05f1f0ca;
    int32_t nFound = 0;
    for (cU32Node_s00c7_7380* pNode = (cU32Node_s00c7_7380*)mKeySet111c.mpBuckets[nKey % mKeySet111c.mnBucketCount];
         pNode != 0; pNode = pNode->mpNext) {
        if (pNode->mKey == nKey)
            ++nFound;
    }
    return nFound != 0;
}

// @ 0x00c77450
void SP::cPlayer_s00c7_7380::RemoveEmbassyFromPlanet(void* pStarRecordRef)
{
    uint32_t nKey = ((cStarRecordRef*)pStarRecordRef)->GetCommContext();
    cPlayerTree* pTree = &mEmbassyTree;
    cTreeNode* pNode;
    pTree->Find(&pNode, &nKey);
    cTreeNode* pEnd = (cTreeNode*)&pTree->mpEnd;
    if (pEnd == pNode)
        return;
    --pTree->mnCount;
    RBTreeIncrement(pNode);
    RBTreeErase(pNode, &pTree->mpEnd);
    operator_delete(pNode);
}

// @ 0x00c774b0
void SP::cPlayer_s00c7_7380::UpdateEmbassyEffects(int32_t nElapsedMs)
{
    cPlayerTree* pTree = &mEmbassyTree;
    for (cTreeNode* pNode = pTree->mpHead; pNode != (cTreeNode*)&pTree->mpEnd; ) {
        cEmbassyNode_s00c7_7380* pEmbassy = (cEmbassyNode_s00c7_7380*)pNode;
        void* pStar = pEmbassy->mStarRecord;
        pEmbassy->mnEmbassyTimer += nElapsedMs;

        cStarRecordView* pStarRec = (cStarRecordView*)GetStarRecord(StarManager(pStar));
        void* pList = SortBanners(pStarRec, 0);
        int32_t nAvatar = GetAvatar(pList);
        void* pEmpire = GetEmpireByID(StarManager((void*)nAvatar), (uint32_t)nAvatar);

        bool bExpired = false;
        if (pEmpire == 0 || !IsHostileToPlayer(pEmpire)) {
            // non-hostile: threshold gate, then decay + relationship event
            if ((uint32_t)pEmbassy->mnEmbassyTimer <= GetEmbassyTuningValue(GetSpaceRelationshipTuning()))
                goto next;
            if (!StarHasEmbassyFlag(pStarRec, g_nEmbassyEvent)) {
                bExpired = true;
            } else {
                pEmbassy->mnEmbassyTimer -= (int32_t)GetEmbassyTuningValue(GetSpaceRelationshipTuning());
                if (nAvatar != -1) {
                    uint32_t nPlayer = GetPlayerEmpireID(0x0580e23b, 0x3f800000);
                    RecordRelationshipEvent(RelationshipManager((uint32_t)nAvatar, nPlayer),
                                            (uint32_t)nAvatar, nPlayer, 0x0580e23b, 1.0f);
                }
                goto next;
            }
        } else {
            // hostile: decay every embassy flag attached to the star
            if (GetUniverseContext() == 0 && GetActivePlanetRecord() == pStarRec)
                goto next;

            float fDelta = (float)nElapsedMs;
            if (nElapsedMs < 0)
                fDelta += g_fTwoTo32;
            fDelta *= g_fMilliToSeconds;
            fDelta *= GetBackgroundFighterDPS(pEmpire);

            int32_t nCount = (int32_t)((pStarRec->mpEmbassyEnd - pStarRec->mpEmbassyBegin) / 0x2c);
            for (int32_t i = 0; i < nCount; ++i) {
                cEmbassyEntry* pEntry = &pStarRec->mpEmbassyBegin[i];
                if (pEntry->mFlag != g_nEmbassyEvent)
                    continue;
                float fLeft = pEntry->mfTimer - fDelta;
                pEntry->mfTimer = fLeft;
                if (fLeft <= 0.0f) {
                    StarClearEmbassyFlag(pStarRec, g_nEmbassyEvent);
                    bExpired = true;
                    break;
                }
            }
        }

        if (bExpired) {
            --pTree->mnCount;
            cTreeNode* pNext = (cTreeNode*)RBTreeIncrement(pNode);
            RBTreeErase(pNode, &pTree->mpEnd);
            operator_delete(pNode);
            pNode = pNext;
            continue;
        }

    next:
        pNode = (cTreeNode*)RBTreeIncrement(pNode);
    }
}

// @ 0x00c77700
void** cHashtableHeader::Insert3(void** ppOut, const uint32_t* pKey, bool bFlag)
{
    uint32_t nHash = pKey[0] ^ pKey[2];
    uint32_t nBucket = nHash % mnBucketCount;

    void** ppBucket = &mpBuckets[nBucket];
    cKey3Node* pNode = (cKey3Node*)*ppBucket;
    while (pNode != 0) {
        if (pKey[0] == pNode->mKey0 && pKey[1] == pNode->mKey1 && pKey[2] == pNode->mKey2)
            break;
        pNode = pNode->mpNext;
    }

    if (pNode != 0) {
        ppOut[1] = ppBucket;
        ppOut[0] = pNode;
        *((uint8_t*)(ppOut + 2)) = 0;
        return ppOut;
    }

    uint8_t nRehash[8];
    mRehash10.GetRehashRequired(nRehash, mnBucketCount, mnElementCount, 1);
    cKey3Node* pNew = (cKey3Node*)AllocNode(pKey);
    if (nRehash[0] != 0) {
        uint32_t nNewBuckets = *(uint32_t*)&nRehash[4];
        nBucket = nHash % nNewBuckets;
        Rehash(nNewBuckets);
    }
    pNew->mpNext = (cKey3Node*)mpBuckets[nBucket];
    mpBuckets[nBucket] = pNew;
    ++mnElementCount;
    ppOut[1] = &mpBuckets[nBucket];
    ppOut[0] = pNew;
    *((uint8_t*)(ppOut + 2)) = 1;
    return ppOut;
}

// @ 0x00c777e0
void __cdecl Read_00c777e0(ISerializerStream_s00c7_7380* pStream, cHashtableHeader* pData)
{
    pData->DoFreeNodes(pData->mpBuckets, pData->mnBucketCount);
    pData->mnElementCount = 0;

    uint32_t nCount = 0;
    ReadInt32(GetIOStream(pStream), &nCount, 1, 0);
    for (uint32_t i = 0; i < nCount; ++i) {
        uint32_t nKey = 0;
        ReadInt32(GetIOStream(pStream), &nKey, 1, 0);
        pStream->v1c();
        cInsertResult res;
        pData->InsertU32(&res, &nKey, 0);
    }
    pStream->v1c();
}

// @ 0x00c77890
bool __cdecl Write_00c77890(ISerializerStream_s00c7_7380* pStream, cVector_s00c7_7380<cEntry8>* pData)
{
    uint32_t nCount = pData->Count();
    WriteUint32(GetIOStream(pStream), &nCount, 1, 0);
    for (cEntry8* p = pData->mpBegin; p != pData->mpEnd; ++p) {
        WriteUint32(GetIOStream(pStream), &p->mKey, 1, 0);
        pStream->v1c();
        WriteBits6(pStream, &p->mBits);
        pStream->v1c();
    }
    pStream->v1c();
    return false;
}

// @ 0x00c77a00
template <> void cVector_s00c7_7380<cEntry20>::Reserve(uint32_t nCount)
{
    if (Capacity() >= nCount)
        return;

    cEntry20* pNew = 0;
    if (nCount != 0)
        pNew = (cEntry20*)operator_new(nCount * 20, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);

    memcpy(pNew, mpBegin, (uint32_t)((uint8_t*)mpEnd - (uint8_t*)mpBegin));
    if (mpBegin != 0 && *((int32_t*)mpBegin - 1) != 0)
        operator_delete(mpBegin);

    uint32_t nUsed = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / 20;
    mpBegin = pNew;
    mpEnd = pNew + nUsed;
    mpCap = pNew + nCount;
}

// @ 0x00c77ab0
void __stdcall DestroyVec20Range(cPtrVecEntry* pBegin, cPtrVecEntry* pEnd)
{
    for (cPtrVecEntry* pEntry = pBegin; pEntry < pEnd; ++pEntry) {
        void** pLast = pEntry->mpEnd;
        void** pIt = pEntry->mpBegin;
        for (; pIt < pLast; ++pIt) {
            void* pObj = *pIt;
            if (pObj != 0)
                (*(void(__thiscall**)(void*))(*(uint8_t**)pObj + 0xc0))(pObj);
        }
        void** pBlock = pEntry->mpBegin;
        if (pBlock != 0 && *((int32_t*)pBlock - 1) != 0)
            operator_delete(pBlock);
    }
}

// @ 0x00c77b10
void cEmbassyList::Destroy(cEmbassyList* pHead)
{
    while (pHead != 0) {
        Destroy(pHead->mpChild);
        cEmbassyList* pNext = pHead->mpNext;
        pHead->mpVtbl18 = (void*)g_vtblSpacePlayerWarData;
        ((cGonzagoTimer_s00c7_7380*)pHead->mTimer28)->~cGonzagoTimer_s00c7_7380();
        operator_delete(pHead);
        pHead = pNext;
    }
}

// @ 0x00c77bf0
bool SP::cPlayer_s00c7_7380::HasFlagOrInsert(uint32_t nKey)
{
    cHashtableHeader* pSet = &mKeySet111c;
    int32_t nFound = 0;
    for (cU32Node_s00c7_7380* pNode = (cU32Node_s00c7_7380*)pSet->mpBuckets[nKey % pSet->mnBucketCount];
         pNode != 0; pNode = pNode->mpNext) {
        if (nKey == pNode->mKey)
            ++nFound;
    }
    bool bPresent = nFound != 0;
    if (!bPresent) {
        cInsertResult res;
        pSet->InsertU32(&res, &nKey, bPresent);
    }
    return bPresent;
}

// @ 0x00c77c50
bool SP::cPlayer_s00c7_7380::HasEntryInSet(const uint32_t* pKey)
{
    cHashtableHeader* pSet = &mSet38;
    void* aIter[2];
    pSet->Find3(aIter, pKey);
    return (cKey3Node*)aIter[0] != (cKey3Node*)pSet->mpBuckets[pSet->mnBucketCount];
}

// @ 0x00c77c90
void SP::cPlayer_s00c7_7380::LatchCheatDetected()
{
    if (GetCurrentGameMode() != (void*)0x01654c05)
        return;
    if (mbCheatLatched != 0)
        return;

    void* pGame = SpaceGameGet();
    if (pGame != 0) {
        void* pTribe = GetPlayerTribe(pGame);
        if (pTribe != 0) {
            TribeCheatDisable(0x1d, 1);
            (*(void(__thiscall**)(void*, uint32_t, uint32_t))(*(uint8_t**)pTribe + 0x10))(pTribe, 1, 0);
        }
    }

    mbCheatLatched = 1;
    uint32_t nBanner = 0;
    wchar_t* pText = g_wstrCheatWarning;
    SetCheatWarningText(&nBanner, pText);
    if ((int32_t)((uint8_t*)nBanner - (uint8_t*)g_wstrEmpty16) > 1 && nBanner != 0)
        operator_delete((void*)nBanner);
}

// @ 0x00c77d30
bool SP::cPlayerCommand::ProcessCommand(uint32_t nCommand, int32_t* pArg)
{
    SP::cPlayer_s00c7_7380* pPlayer = (SP::cPlayer_s00c7_7380*)((uint8_t*)this - 0x34);

    if (nCommand == 0x04bef1e3) {
        pPlayer->LatchCheatDetected();
        return true;
    }

    if (nCommand == 0x06524498) {
        void* pEffect = 0;
        void* pMgr = EffectsManager();
        if (pEffect != 0) {
            pEffect = 0;
            (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)pEffect + 0x04))(pEffect, 0);
        }
        void* pOut = 0;
        (*(void(__thiscall**)(void*, uint32_t, uint32_t, void**))(*(uint8_t**)pMgr + 0x2c))(
            pMgr, 0xc04acc27, 0, &pOut);
        if (pOut != 0) {
            (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)pOut + 0x08))(pOut, 0);
            ActivateSolarSystemGraphics(GetSolarSystem(GetActiveStar()));
            void* pAspect = AspectManager();
            (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)*(void**)((uint8_t*)pAspect + 0x7c) + 0x0c))(
                *(void**)((uint8_t*)pAspect + 0x7c), 1);
            pAspect = AspectManager();
            (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)*(void**)((uint8_t*)pAspect + 0x6c) + 0x0c))(
                *(void**)((uint8_t*)pAspect + 0x6c), 1);
            pAspect = AspectManager();
            (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)*(void**)((uint8_t*)pAspect + 0x80) + 0x0c))(
                *(void**)((uint8_t*)pAspect + 0x80), 1);
            if (pOut != 0)
                (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)pOut + 0x04))(pOut, 0);
        }
        return true;
    }

    if (nCommand == 0x05e902d3) {
        void* pServer = MessageServer();
        (*(void(__thiscall**)(void*, uint32_t, uint32_t, uint32_t))(*(uint8_t**)pServer + 0x14))(
            pServer, 0x0445f729, 0, 0);
        return true;
    }

    if (nCommand == 0x06667038 || nCommand == 0x06666683) {
        float fSpeed = (nCommand == 0x06667038) ? g_fUFOSpeedSlow : g_fUFOSpeedFast;
        struct { float x, y, z; } vec;
        vec.x = fSpeed;
        vec.y = 0.0f;
        vec.z = 0.0f;
        SetUFODestination(GetPlayerInventory(GetUFOSimulator()), &vec);
        return true;
    }

    if (nCommand == 0x06526395) {
        if (pPlayer->HasCheatFlagEx(&g_nCheatFlagKey))
            return true;

        ResetInventoryFlags(GetPlayerInventory(SpaceGameGet()));
        if ((g_bCheatWarningLatch & 1) == 0) {
            g_bCheatWarningLatch |= 1;
            g_cheatEventKey = 0xa9e151e4;
            g_cheatEventA = 0;
            g_cheatEventB = 0;
        }
        RecordRelationshipEntry(GetRelationshipTable(&g_cheatEventKey), 1);
        PostFeedbackEvent(EventLog(0xde5edde2, 0x131a9f54, 0, 0, 1, 0),
                          0xde5edde2, 0x131a9f54, 0, 0, 1, 0);
        pPlayer->HasFlagOrInsert(g_nCheatFlagKey);
        return true;
    }

    if (nCommand == 0x06527231) {
        void* pOut = 0;
        void* pMgr = EffectsManager();
        (*(void(__thiscall**)(void*, uint32_t, uint32_t, void**))(*(uint8_t**)pMgr + 0x2c))(
            pMgr, 0xaf4031ad, 0, &pOut);
        if (pOut != 0) {
            (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)pOut + 0x08))(pOut, 0);
            ActivateSolarSystemGraphics(GetSolarSystem(GetActiveStar()));
            if (pOut != 0)
                (*(void(__thiscall**)(void*, uint32_t))(*(uint8_t**)pOut + 0x04))(pOut, 0);
        }
        return true;
    }

    if (nCommand == 0x06527eaf) {
        FinishUFOCheat(StartUFOCheat());
        return true;
    }

    if (nCommand == 0x01a0219e) {
        if (pArg[2] == 5 && pPlayer->mpBlock10b4 != 0)
            ConfigureInventory(0xad56080c, 0x4a5c4493, g_nUFOInventoryArg);
        return true;
    }

    return false;
}

// @ 0x00c78020
bool __cdecl Read_00c78020(ISerializerStream_s00c7_7380* pStream, cHashtableHeader* pData)
{
    pData->DoFreeNodesFlag(pData->mpBuckets, pData->mnBucketCount);
    pData->mnElementCount = 0;

    uint32_t nCount = 0;
    ReadInt32(GetIOStream(pStream), &nCount, 1, 0);
    for (uint32_t i = 0; i < nCount; ++i) {
        uint32_t nKey = 0;
        ReadInt32(GetIOStream(pStream), &nKey, 1, 0);
        pStream->v1c();
        uint32_t nValue = 0;
        ReadInt32(GetIOStream(pStream), &nValue, 1, 0);
        pStream->v1c();
        cInsertResult res;
        pData->InsertFlag((void**)&res, &nKey, nValue);
        if (!res.mbInserted)
            *(uint32_t*)((uint8_t*)res.mpNode + 4) = nValue;
    }
    pStream->v1c();
    return false;
}

// @ 0x00c78130
bool __cdecl Read_00c78130(ISerializerStream_s00c7_7380* pStream, cHashtableHeader* pData)
{
    pData->DoFreeNodes3(pData->mpBuckets, pData->mnBucketCount);
    pData->mnElementCount = 0;

    uint32_t nCount = 0;
    ReadInt32(GetIOStream(pStream), &nCount, 1, 0);
    for (uint32_t i = 0; i < nCount; ++i) {
        uint32_t nKey[3] = { 0, 0, 0 };
        ReadKey3(pStream, nKey);
        pStream->v1c();
        cInsertResult res;
        bool bFlag = false;
        pData->Insert3((void**)&res, nKey, bFlag);
    }
    pStream->v1c();
    return false;
}

// @ 0x00c781e0
void __stdcall DestroyPlayerPlanetDataRange(cPlayerPlanetData* pBegin, cPlayerPlanetData* pEnd)
{
    if (pBegin >= pEnd)
        return;
    uint32_t nCount = ((uint32_t)((uint8_t*)pEnd - (uint8_t*)pBegin) - 1) / 0xb0 + 1;
    for (uint32_t nLeft = nCount; nLeft != 0; --nLeft) {
        cPlayerPlanetData* p = pBegin;
        p->mpVtbl08 = (void*)g_vtblPlayerPlanetData;
        ((cGonzagoTimer_s00c7_7380*)p->mTimer88)->~cGonzagoTimer_s00c7_7380();
        if (p->mpBlock70) operator_delete(p->mpBlock70);
        if (p->mpBlock58) operator_delete(p->mpBlock58);
        if (p->mpBlock40) operator_delete(p->mpBlock40);
        if (p->mpBlock28) operator_delete(p->mpBlock28);
        if (p->mpBlock10) operator_delete(p->mpBlock10);
        pBegin = (cPlayerPlanetData*)((uint8_t*)pBegin + 0xb0);
    }
}

// @ 0x00c78280
template <> void cVector_s00c7_7380<cEntry8>::Insert(cEntry8* pPos, const cEntry8* pValue)
{
    if (mpEnd != mpCap) {
        const cEntry8* pSrc = pValue;
        if (pPos <= pValue && pValue < mpEnd)
            pSrc = pValue + 1;
        if (mpEnd != 0)
            *mpEnd = mpEnd[-1];
        cEntry8* p = mpEnd;
        for (cEntry8* q = mpEnd - 1; q != pPos; ) {
            --p; --q;
            *p = *q;
        }
        *pPos = *pSrc;
        ++mpEnd;
        return;
    }

    uint32_t nOld = (uint32_t)(mpEnd - mpBegin);
    uint32_t nNew = (nOld != 0) ? nOld * 2 : 1;
    cEntry8* pNew = 0;
    if (nNew != 0)
        pNew = (cEntry8*)operator_new(nNew * 8, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);

    cEntry8* pSlot = (cEntry8*)eastlMoveRange(pNew, mpBegin, (uint32_t)((uint8_t*)pPos - (uint8_t*)mpBegin));
    if (pSlot != 0)
        *pSlot = *pValue;
    cEntry8* pNewEnd = (cEntry8*)eastlMoveRange(pSlot + 1, pPos, (uint32_t)((uint8_t*)mpEnd - (uint8_t*)pPos));
    if (mpBegin != 0)
        operator_delete(mpBegin);
    mpBegin = pNew;
    mpEnd = pNewEnd;
    mpCap = pNew + nNew;
}

// @ 0x00c78420
void SP::cPlayer_s00c7_7380::AddToSet(const uint32_t* pKey)
{
    bool bFlag = false;
    cInsertResult res;
    mSet38.Insert3((void**)&res, pKey, bFlag);
}

// @ 0x00c78450
void SP::cPlayer_s00c7_7380::NoteWarEndedWithPlayer(void* pEmpire)
{
    cPlayerTree* pTree = &mWarEvents11f8;
    uint32_t nKey = *(uint32_t*)((uint8_t*)pEmpire + 0x84);
    cTreeNode* pNode;
    pTree->Find(&pNode, &nKey);
    if (pNode == (cTreeNode*)&pTree->mpEnd)
        return;
    --pTree->mnCount;
    RBTreeIncrement(pNode);
    RBTreeErase(pNode, &pTree->mpEnd);
    *(void**)((uint8_t*)pNode + 0x18) = (void*)g_vtblSpacePlayerWarData;
    ((cGonzagoTimer_s00c7_7380*)((uint8_t*)pNode + 0x28))->~cGonzagoTimer_s00c7_7380();
    operator_delete(pNode);
}

// @ 0x00c784c0
bool SP::cPlayer_s00c7_84c0::TestPlayerWarVictory(int32_t nEmpireId)
{
    WarEventRecord* pRecord;
    mWarEvents.Find(&pRecord, &nEmpireId);
    if (pRecord == mWarEvents.End())
        return false;

    cEmpire_s00c7_84c0* pEmpire = StarManager()->GetEmpireByID(nEmpireId);
    StarVector* pStars = pEmpire->GetStars();
    int32_t nStarCount = (int32_t)(pStars->mpEnd - pStars->mpBegin);
    if (nStarCount == 0) {
        NoteWarEndedWithPlayer(pEmpire);
        return false;
    }

    int32_t nProgress = pRecord->mnProgress - pRecord->mnBaseline;
    if (nProgress <= 0)
        return false;

    int32_t nCombined = nProgress + nStarCount;
    if (pRecord->mnLimit > nCombined)
        pRecord->mnLimit = nCombined;

    int32_t nLimit = pRecord->mnLimit;
    float fFraction = 1.0f - (float)nProgress / (float)nLimit;

    float fChance = 1.0f;
    if (nLimit == 1 || nStarCount != 1) {
        if (!(fFraction < GetSpaceCombatTuning()->GetWarSurrenderThreshold()))
            return false;
        GetPropertyT<float>(StarManager()->FUN_00baf700(pEmpire), 0x682ede3, &fChance);
    } else {
        GetPropertyT<float>(StarManager()->FUN_00baf700(pEmpire), 0x682f155, &fChance);
    }

    double fRoll = gRandom.RandomDoubleUniform();
    return fChance > fRoll;
}

// @ 0x00c785e0
cResourceKeySet* cResourceKeySet::Construct(uint32_t nArg1, uint32_t nArg2)
{
    FixedPoolBase pool;
    pool.mpHead = nullptr;
    pool.Init(mPool, 0x400, 0x10, 4, 0);

    FixedHashtableAlloc alloc;
    alloc.mpPoolHead = mPool;
    alloc.mpPoolBegin = mPool;
    alloc.mpPoolEnd = mPool + 0x400;
    alloc.mnNodeSize = 0x10;
    alloc.mpBuckets = &mHashtable.mpBuckets;

    uint32_t nBucketCount = GetBucketCountFor(0x41);
    mHashtable.Construct(nBucketCount, nArg1, alloc);

    mHashtable.mfLoadFactor = 12390.0f;
    mHashtable.mfGrowthFactor = 2.0f;
    mHashtable.mnElementCount = 0;

    uint32_t nWanted = GetRehashBucketCount(mHashtable.mnBucketCount);
    if (mHashtable.mnBucketCapacity < nWanted)
        mHashtable.DoFreeNodes(nWanted);
    (void)nArg2;
    return this;
}

// @ 0x00c786b0
cResourceKeyTable* cResourceKeyTable::Construct(uint32_t nArg1, uint32_t nArg2)
{
    FixedPoolBase pool;
    pool.mpHead = nullptr;
    pool.Init(mPool, 0x600, 0xc, 4, 0);

    FixedHashtableAlloc alloc;
    alloc.mpPoolHead = mPool;
    alloc.mpPoolBegin = mPool;
    alloc.mpPoolEnd = mPool + 0x600;
    alloc.mnNodeSize = 0xc;
    alloc.mpBuckets = &mHashtable.mpBuckets;

    uint32_t nBucketCount = GetBucketCountFor(0x81);
    mHashtable.ConstructKeyed(nBucketCount, nArg1, alloc);

    mHashtable.mfLoadFactor = 12390.0f;
    mHashtable.mfGrowthFactor = 2.0f;
    mHashtable.mnElementCount = 0;

    uint32_t nWanted = GetRehashBucketCount(mHashtable.mnBucketCount);
    if (mHashtable.mnBucketCapacity < nWanted)
        mHashtable.DoFreeNodesKeyed(nWanted);
    (void)nArg2;
    return this;
}

// @ 0x00c78790
cUInt32Map* cUInt32Map::Construct(uint32_t nArg1, uint32_t nArg2)
{
    FixedPoolBase pool;
    pool.mpHead = nullptr;
    pool.Init(mPool, 0x300, 0x18, 8, 0);

    FixedHashtableAlloc alloc;
    alloc.mpPoolHead = mPool;
    alloc.mpPoolBegin = mPool;
    alloc.mpPoolEnd = mPool + 0x300;
    alloc.mnNodeSize = 0x18;
    alloc.mpBuckets = &mHashtable.mpBuckets;

    uint32_t nBucketCount = GetBucketCountFor(0x21);
    mHashtable.ConstructMap(nBucketCount, nArg1, alloc);

    mHashtable.mfLoadFactor = 12390.0f;
    mHashtable.mfGrowthFactor = 2.0f;
    mHashtable.mnElementCount = 0;

    uint32_t nWanted = GetRehashBucketCount(mHashtable.mnBucketCount);
    if (mHashtable.mnBucketCapacity < nWanted)
        mHashtable.DoFreeNodesMap(nWanted);
    (void)nArg2;
    return this;
}

// @ 0x00c788d0
bool __cdecl FUN_00c788d0(cSerializer* pSerializer, const char* pName, const cInt32Set* pSet)
{
    bool bOk = true;
    if (pSet->mnElementCount == 0)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"set" : sName.c_str();
    pSerializer->BeginContainer(pszName);

    cInt32SetNode** pBucket = pSet->mpBuckets;
    cInt32SetNode* pNode = *pBucket;
    if (pNode == nullptr) {
        do {
            ++pBucket;
        } while (*pBucket == nullptr);
        pNode = *pBucket;
    }
    cInt32SetNode* pEnd = pSet->mpBuckets[pSet->mnBucketCount];
    while (pNode != pEnd) {
        if (bOk && !WriteTypedValue32(pSerializer, 0, &pNode->mnValue, L"int32_t"))
            bOk = false;
        pNode = pNode->mpNext;
        if (pNode == nullptr) {
            do {
                ++pBucket;
            } while (*pBucket == nullptr);
            pNode = *pBucket;
        }
    }

    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c78ea0
bool __cdecl FUN_00c78ea0(cSerializer* pSerializer, const char* pName, const WidePairList* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"map" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const WidePair* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValuePair(pSerializer, 0, p->mValue))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c78ff0
bool __cdecl FUN_00c78ff0(cSerializer* pSerializer, const char* pName, const PairList8* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"map" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const KeyPair8* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValuePair(pSerializer, 0, &p->mnValue))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c79140
bool __cdecl FUN_00c79140(cSerializer* pSerializer, const char* pName, const Int32List* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"list" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const int32_t* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValue32(pSerializer, 0, p, L"int32_t"))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c79290
bool __cdecl FUN_00c79290(cSerializer* pSerializer, const char* pName, const PairList16* pList)
{
    bool bOk = true;
    if (pList->mpBegin == pList->mpEnd)
        return bOk;

    WString sName(pName != nullptr ? EAConvertToString16(pName, -1) : WString());
    const wchar_t* pszName = sName.empty() ? L"map" : sName.c_str();
    pSerializer->BeginContainer(pszName);
    for (const KeyPair16* p = pList->mpBegin; p != pList->mpEnd; ++p) {
        if (bOk && !WriteTypedValueBool(pSerializer, 0, &p->mnValue, L"bool"))
            bOk = false;
    }
    pSerializer->EndContainer(pszName);
    return bOk;
}

// @ 0x00c793e0
uint8_t FUN_00c793e0(cSerialStream* pStream, const char* pName, tUintVec* pVec)
{
    uint8_t nOk = 1;
    if (pVec->mpBegin == pVec->mpEnd)
        return nOk;

    tWString wTemp;
    if (pName == 0)
        wTemp.RangeInitialize(0);
    else
        EA_ConvertToString16(&wTemp, pName, -1);

    tWString wName(wTemp);

    const wchar_t* pszOpen = (wName.mpBegin == wName.mpEnd) ? g_wstrEmpty : wName.mpBegin;
    pStream->v00(pszOpen);

    for (uint32_t* p = pVec->mpBegin; p != pVec->mpEnd; p += 2)
        nOk = nOk && (WriteTypedValue(pStream, 0, p + 1, g_wstrBool) != 0);

    const wchar_t* pszClose = (wName.mpBegin == wName.mpEnd) ? g_wstrEmpty : wName.mpBegin;
    pStream->v04(pszClose);

    return nOk;
}

// @ 0x00c795f0
void tRefVec::insert(tAutoRef* pPos, uint32_t n, tAutoRef* pValue)
{
    if ((uint32_t)(mpCap - mpEnd) < n) {
        uint32_t nOld  = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrow = nOld * 2;
        if (nOld == 0)
            nGrow = 1;
        uint32_t nCap = nOld + n;
        if (nCap < nGrow)
            nCap = nGrow;

        tAutoRef* pNew = (nCap == 0)
            ? 0
            : (tAutoRef*)operator_new(nCap * 4, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);

        uint32_t nPrefix = (uint32_t)((uint8_t*)pPos - (uint8_t*)mpBegin);
        tAutoRef* pMid = (tAutoRef*)FUN_00c76740(pNew, mpBegin, nPrefix);
        tAutoRef* pFill = (tAutoRef*)((uint8_t*)pMid + nPrefix);
        FUN_00c75b60(pFill, n, pValue, pPos);

        uint32_t nTail = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)pPos);
        tAutoRef* pNewEnd = (tAutoRef*)FUN_00c76740((uint8_t*)pFill + n * 4, pPos, nTail);

        if (mpBegin != 0 && *((int32_t*)mpBegin - 1) != 0)
            operator_delete_array(mpBegin);

        mpBegin = pNew;
        mpEnd   = pNewEnd;
        mpCap   = (tAutoRef*)((uint8_t*)pNew + nCap * 4);
    } else if (n != 0) {
        void* pObj = pValue->mpObj;
        if (pObj != 0)
            ((cRefObj_s00c7_93e0*)pObj)->AddRef();

        uint32_t nRest = (uint32_t)(mpEnd - pPos);
        if (n < nRest) {
            for (uint32_t i = nRest; i > n; --i)
                pPos[i + n - 1] = pPos[i - 1];
            for (uint32_t i = 0; i < n; ++i)
                pPos[i] = *pValue;
        } else {
            for (uint32_t i = nRest; i < n; ++i)
                pPos[i] = *pValue;
        }
        mpEnd += n;
    }
}

// @ 0x00c798a0
tPair28* tPairVec::erase(tPair28* pFirst, tPair28* pLast)
{
    tPair28* pNewEnd = (tPair28*)FUN_00c771e0(pLast, mpEnd, pFirst);
    tPair28* pEnd = mpEnd;
    while (pNewEnd < pEnd) {
        pNewEnd->mTimer.~cGonzagoTimer();
        ++pNewEnd;
    }
    mpEnd -= pLast - pFirst;
    return pFirst;
}

// @ 0x00c79900
uint32_t* tUintVec::insert(uint32_t* pPos, uint32_t n, const uint32_t& rValue)
{
    if ((uint32_t)(mpCap - mpEnd) < n) {
        uint32_t nOld  = (uint32_t)(mpEnd - mpBegin);
        uint32_t nGrow = nOld * 2;
        if (nOld == 0)
            nGrow = 1;
        uint32_t nCap = nOld + n;
        if (nCap < nGrow)
            nCap = nGrow;

        uint32_t* pNew = (nCap == 0)
            ? 0
            : (uint32_t*)operator_new(nCap * 4, g_szSimulator, 0, 0, g_szAllocatorH, 0xd1);

        uint32_t nPrefix = (uint32_t)((uint8_t*)pPos - (uint8_t*)mpBegin);
        uint32_t* pMid = (uint32_t*)FUN_00c76740(pNew, mpBegin, nPrefix);
        uint32_t* pFill = (uint32_t*)((uint8_t*)pMid + nPrefix);

        uint32_t v = rValue;
        for (uint32_t i = 0; i < n; ++i)
            pFill[i] = v;

        uint32_t nTail = (uint32_t)((uint8_t*)mpEnd - (uint8_t*)pPos);
        uint32_t* pNewEnd = (uint32_t*)FUN_00c76740((uint8_t*)pFill + n * 4, pPos, nTail);

        if (mpBegin != 0 && *((int32_t*)mpBegin - 1) != 0)
            operator_delete_array(mpBegin);

        mpBegin = pNew;
        mpEnd   = pNewEnd;
        mpCap   = (uint32_t*)((uint8_t*)pNew + nCap * 4);
    } else if (n != 0) {
        uint32_t nTail = (uint32_t)(mpEnd - pPos);
        uint32_t v = rValue;
        if (n < nTail) {
            FUN_00c75b60(pPos, n, &v, (uint8_t*)mpEnd - n * 4);
        } else {
            for (uint32_t i = nTail; i > 0; --i)
                pPos[n - nTail + i - 1] = pPos[i - 1];
            for (uint32_t i = 0; i < n - nTail; ++i)
                pPos[i] = v;
        }
        mpEnd += n;
    }
    return pPos;
}

// @ 0x00c79b60
void cPlayer::FUN_00c79b60()
{
    mpVtbl00 = (void*)&g_vtbl_01472d48;
    mpVtbl04 = (void*)&g_vtbl_01472d34;
    mpVtbl34 = (void*)&g_vtbl_01472d24;

    if (mpRef11f4 != 0) {
        void* p = mpRef11f4;
        mpRef11f4 = 0;
        ((cRefObj_s00c7_93e0*)p)->Release();
    }
    if (mpBlock129c != 0 && mpBlock129c != mpBlock12ac)
        operator_delete_array(mpBlock129c);

    mTimer1258.~cGonzagoTimer();
    mRbTree.DoNukeSubtree(mRbTree.mpRoot);

    for (uint32_t i = (uint32_t)mpPairBegin1214; i < (uint32_t)mpPairEnd1218; i += 0x28)
        ((cGonzagoTimer*)(i + 8))->~cGonzagoTimer();
    if (mpPairBegin1214 != 0 && *((int32_t*)mpPairBegin1214 - 1) != 0)
        operator_delete_array(mpPairBegin1214);

    mList11f8.FUN_00c77b10(mList11f8.mpHead);
    if (mpRef11f4 != 0)
        ((cRefObj_s00c7_93e0*)mpRef11f4)->Release();

    if (mpBlock11d8 != 0)
        operator_delete_array(mpBlock11d8);
    mList11c0.FUN_00c781e0(mList11c0.mpBegin, mList11c0.mpEnd);
    if (mList11c0.mpBegin != 0)
        operator_delete_array(mList11c0.mpBegin);

    if (mVec11ac.mpBegin != 0 && *((int32_t*)mVec11ac.mpBegin - 1) != 0)
        operator_delete_array(mVec11ac.mpBegin);
    if (mVec1198.mpBegin != 0 && *((int32_t*)mVec1198.mpBegin - 1) != 0)
        operator_delete_array(mVec1198.mpBegin);
    if (mVec1184.mpBegin != 0 && *((int32_t*)mVec1184.mpBegin - 1) != 0)
        operator_delete_array(mVec1184.mpBegin);

    mBanModeTable.FUN_00c77ab0(mBanModeTable.mpBegin, mBanModeTable.mpEnd);
    if (mBanModeTable.mpBegin != 0 && *((int32_t*)mBanModeTable.mpBegin - 1) != 0)
        operator_delete_array(mBanModeTable.mpBegin);

    mHash1120.DoFreeNodes(mHash1120.mpBuckets, mHash1120.mnCount);
    mHash1120.mnNext = 0;
    if (mHash1120.mnCount > 1)
        operator_delete_array(mHash1120.mpBuckets);
    if (mpRef10e8 != 0)
        ((cRefObj_s00c7_93e0*)mpRef10e8)->Release();

    mHash69c.DoFreeNodes(mHash69c.mpBuckets, mHash69c.mnCount);
    {
        uint32_t* p = mHash69c.mpBuckets;
        mHash69c.mnNext = 0;
        if (mHash69c.mnCount > 1 && p != mHash69c.mpStatic) {
            if (p < mHash69c.mpPoolBegin || mHash69c.mpPoolEnd <= p) {
                operator_delete_array(p);
            } else {
                *p = (uint32_t)mHash69c.mpFreeHead;
                mHash69c.mpFreeHead = p;
            }
        }
    }

    mPool38.FUN_00a42fe0(mPool38.mpPool, mPool38.mnCount);
    {
        uint32_t* p = mPool38.mpPool;
        mPool38.mnNext = 0;
        if (mPool38.mnCount > 1 && p != mPool38.mpStatic) {
            if (mPool38.mpPoolBegin <= p && p < mPool38.mpPoolEnd) {
                *p = (uint32_t)mPool38.mpFreeHead;
                mPool38.mpFreeHead = p;
                mpVtbl34 = (void*)&g_vtbl_013eb394;
                return;
            }
            operator_delete_array(p);
        }
    }
    mpVtbl34 = (void*)&g_vtbl_013eb394;
}

// @ 0x00c79e20
void cPlayer::SetBanModePickPriorities(uint32_t nMode, tUintVec* pVec)
{
    if (nMode >= 10)
        return;

    cBanModeEntry* pEntry = (cBanModeEntry*)((uint8_t*)mBanModeTable.mpBegin + nMode * 20);
    pEntry->FUN_00db5b30(pVec);

    uint32_t* pBegin = pVec->mpBegin;
    uint32_t* pEnd = pVec->mpEnd;

    if (SP_GetCurrentGameMode() == (void*)&g_gameModeEntry) {
        cNounMgr* pNM = (cNounMgr*)SP_NounManager();
        cTribe* pTribe = (cTribe*)pNM->GetPlayerTribe();
        if (pTribe != 0) {
            tUintVec* pList = ((tUintVec*(__thiscall*)(void*))pTribe->mpVtbl00[0x90 / 4])(pTribe);
            for (uint32_t* p = pList->mpBegin; p != pList->mpEnd; ++p) {
                void* pObj = (void*)*p;
                if (pObj != 0) {
                    void** pVtbl = *(void***)pObj;
                    if (((uint32_t(__thiscall*)(void*, uint32_t))pVtbl[0x0c / 4])(pObj, 0x4f176642) != 0
                        && FUN_00c227e0() == nMode)
                        FUN_00c227d0(0xffffffff);
                }
            }
        }
    }

    for (uint32_t* p = pBegin; p != pEnd; ++p) {
        void* pObj = (void*)*p;
        if (pObj != 0) {
            void** pVtbl = *(void***)pObj;
            if (((uint32_t(__thiscall*)(void*, uint32_t))pVtbl[0xb8 / 4])(pObj, 0x4f176642) != 0)
                FUN_00c227d0(nMode);
        }
    }
}

// @ 0x00c79f20
void cPlayer::FUN_00c79f20(cPlayerInner* pObj)
{
    if (pObj == 0)
        return;
    if (pObj->FUN_00bb9c00())
        return;
    pObj->FUN_00bb9be0(1);
    if (!pObj->FUN_00bb9bd0()) {
        tUintVec* pVec = &mVec1198;
        uint32_t v = pObj->mn70;
        if (pVec->mpEnd < pVec->mpCap) {
            uint32_t* p = pVec->mpEnd;
            pVec->mpEnd = p + 1;
            if (p != 0) {
                *p = v;
                FUN_00c754e0(pObj);
                return;
            }
        } else {
            pVec->DoInsertValue(pVec->mpEnd, v);
        }
    }
    FUN_00c754e0(pObj);
}

// @ 0x00c79fa0
void cPlayer::FUN_00c79fa0(cPlayerInner* pObj)
{
    if (pObj == 0)
        return;
    uint32_t v = pObj->mn70;

    if (pObj->FUN_00bb9ae0() == 5) {
        void* pAvatar = pObj->GetAvatar();
        if (pAvatar != (void*)SP_GetPlayerEmpireID()) {
            void* pAvatar2 = pObj->GetAvatar();
            cStarManager_s00c7_93e0* pSM = (cStarManager_s00c7_93e0*)FUN_00b3d2a0(pAvatar2);
            cEmpire_s00c7_93e0* pEmpire = (cEmpire_s00c7_93e0*)pSM->GetEmpireByID();
            if (pEmpire != 0 && !FUN_00c772c0(0x5f1f0ca))
                pEmpire->FUN_00c313a0(1);
        }
    }

    if (pObj->FUN_00bb9bd0())
        return;

    if (pObj->FUN_00bb9c00()) {
        for (uint32_t* p = mVec1198.mpBegin; p != mVec1198.mpEnd; ++p) {
            if (*p == v) {
                *p = mVec1198.mpEnd[-1];
                mVec1198.mpEnd -= 1;
                break;
            }
        }
    }

    if (mVec1184.mpEnd < mVec1184.mpCap) {
        uint32_t* q = mVec1184.mpEnd;
        mVec1184.mpEnd = q + 1;
        if (q != 0)
            *q = v;
    } else {
        mVec1184.DoInsertValue(mVec1184.mpEnd, v);
    }

    pObj->FUN_00bb9bb0(1);
    pObj->FUN_00bb9be0(1);

    if (pObj->FUN_00bb9ae0() == 5) {
        void* pAvatar = pObj->GetAvatar();
        cStarManager_s00c7_93e0* pSM = (cStarManager_s00c7_93e0*)FUN_00b3d2a0(pAvatar);
        cEmpire_s00c7_93e0* pEmpire = (cEmpire_s00c7_93e0*)pSM->GetEmpireByID();
        if (pEmpire != 0)
            pEmpire->FUN_00c322f0(0);
    }

    if (SP_SpaceGameGet() != 0) {
        cNounMgr* pSG = (cNounMgr*)SP_SpaceGameGet();
        if (pSG->GetPlayerTribe() != 0) {
            cNounMgr* pSG2 = (cNounMgr*)SP_SpaceGameGet();
            cTribe* pTribe = (cTribe*)pSG2->GetPlayerTribe();
            pTribe->FUN_00fe5430(2, 1);
        }
    }

    if ((uint32_t)(pObj->AddRef() - 1) <= 2) {
        cMessageServer* pMS = (cMessageServer*)SP_MessageServer();
        pMS->v14(0xf46092d8, 0, 0);
    }

    if (pObj->FUN_00bb9ae0() == 5) {
        void* pAvatar = pObj->GetAvatar();
        cStarManager_s00c7_93e0* pSM = (cStarManager_s00c7_93e0*)FUN_00b3d2a0(pAvatar);
        cEmpire_s00c7_93e0* pEmpire = (cEmpire_s00c7_93e0*)pSM->GetEmpireByID();
        if (pEmpire != 0) {
            uint32_t n84 = pEmpire->mn84;
            SP_NounManager();
            uint32_t nCur = SP_GetPlayerEmpireOrMinus1();
            if (n84 != nCur)
                FUN_00ba5bc0(pEmpire, 0);
        }
    }
}

// @ 0x00c7a160
void cPlayer::FUN_00c7a160(cPlayerInner* pObj)
{
    if (pObj == 0)
        return;
    if (pObj->AddRef() != 2)
        return;

    tUintVec* pVec = &mVec11ac;
    uint32_t* p = pVec->mpBegin;
    uint32_t* pEnd = pVec->mpEnd;
    uint32_t v = pObj->mn70;
    while (p != pEnd && *p != v)
        ++p;
    if (p == pEnd) {
        if (pVec->mpEnd < pVec->mpCap) {
            uint32_t* q = pVec->mpEnd;
            pVec->mpEnd = q + 1;
            if (q != 0) {
                *q = v;
                pObj->FUN_00bb9b00(0x10000, 1);
                return;
            }
        } else {
            pVec->DoInsertValue(pVec->mpEnd, v);
        }
    }
    pObj->FUN_00bb9b00(0x10000, 1);
}

// @ 0x00c7a970
void FUN_00c7a970(IStreamNode* stream, U32Vector* vec)
{
    vec->Clear();

    uint32_t count = 0;
    IStreamNode* node = stream->GetSubNode();
    void* reader = node->GetReader();
    ReadInt32(reader, (int*)&count, 1, 0);
    vec->Reserve(count);

    for (uint32_t i = 0; i < count; ++i) {
        IStreamNode* itemNode = stream->GetSubNode();
        void* itemReader = itemNode->GetReader();
        uint32_t value;
        ReadInt32(itemReader, (int*)&value, 1, 0);
        vec->PushBack(value);
    }
    stream->EndChunk();
}

// @ 0x00c7aa40
void cTimerVector::Insert(cTimerElem* position, const cTimerElem& value)
{
    if (mpEnd != mpCapacity) {
        const cTimerElem* source = &value;
        // Self-insertion fixup (EASTL adjusts a value that lives in the vector).
        if ((const char*)source >= (const char*)position && source < mpEnd)
            source = (const cTimerElem*)((const char*)source + 0x28);

        if (mpEnd != 0)
            mpEnd->Construct(mpEnd - 1);
        TimerCopyBackward(position, mpEnd - 1, mpEnd);

        position->mKey       = source->mKey;
        position->mElapsedLo = source->mElapsedLo;
        position->mElapsedHi = source->mElapsedHi;
        position->mBaseLo    = source->mBaseLo;
        position->mBaseHi    = source->mBaseHi;
        position->mbRunning  = source->mbRunning;
        position->mFn        = source->mFn;
        mpEnd = mpEnd + 1;
        return;
    }

    int count = (int)(mpEnd - mpBegin);
    int newCapacity;
    cTimerElem* buffer;
    if (count == 0) {
        newCapacity = 1;
    } else {
        newCapacity = count * 2;
        if (newCapacity == 0) {
            buffer = 0;
            goto haveBuffer;
        }
    }
    buffer = (cTimerElem*)EastlAllocate(newCapacity * 0x28, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
haveBuffer:
    cTimerElem* mid = TimerConstructRange(mpBegin, position, buffer);
    TimerDestroyRange(mpBegin, position, buffer);
    if (mid)
        mid->Construct(&value);

    cTimerElem* newEnd = TimerConstructRange(position, mpEnd, mid + 1);
    TimerDestroyRange(position, mpEnd, mid + 1);

    if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
        EastlFree(mpBegin);

    mpEnd = newEnd;
    mpBegin = buffer;
    mpCapacity = (cTimerElem*)((char*)buffer + newCapacity * 0x28);
}

// @ 0x00c7b120
namespace SP {
void FUN_00c7b120()
{
}
}  // namespace SP

// @ 0x00c7b390
namespace SP {
void FUN_00c7b390()
{
}
}  // namespace SP

// @ 0x00c7b510
namespace SP {
void FUN_00c7b510()
{
}
}  // namespace SP

// @ 0x00c7b670
namespace SP {
void FUN_00c7b670()
{
}
}  // namespace SP

// @ 0x00c7b790
namespace SP {
void FUN_00c7b790()
{
}
}  // namespace SP

// @ 0x00c7ba90
namespace SP {
void cPlayer_s00c7_b120::FUN_00c7ba90(int starRecord)
{
    FUN_00c7ad40(this, starRecord);
    int enemyEmpire = *(int*)(starRecord + 0x70);

    // Build a cGonzagoTimer, copy its timer state into a standalone cSPTimer, then start it
    // and push the record (key = enemyEmpire, timer) onto the war-timer vector at 0x1214.
    cGonzagoTimer_s00c7_b120 gonzago;                                  // local_48
    cSPTimer_s00c7_b120 local;
    local.mpVftblBase = 0;
    local.mRefCount = 0;
    local.mElapsedLo = gonzago.mTimer.mElapsedLo;
    local.mElapsedHi = gonzago.mTimer.mElapsedHi;
    local.mBaseLo = gonzago.mTimer.mBaseLo;
    local.mBaseHi = gonzago.mTimer.mBaseHi;
    local.mbRunning = gonzago.mTimer.mbRunning;
    local.mpFn = gonzago.mTimer.mpFn;
    uint32_t key = (uint32_t)enemyEmpire;
    (void)key;
    local.Start();

    uint32_t end = mTimerEnd;
    if (end < mTimerCapEnd) {
        mTimerEnd = end + 0x28;
        if (end != 0) {
            FUN_00c76f10(&key);
        }
    } else {
        FUN_00c7aa40((void*)end, &key);
    }
}
}  // namespace SP

// @ 0x00c7bb60
namespace SP {
void cPlayer_s00c7_b120::SetWarFlag1(int key)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    *p |= 1u;
}
}  // namespace SP

// @ 0x00c7bb80
namespace SP {
void cPlayer_s00c7_b120::SetWarFlag2(int key)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    *p |= 2u;
}
}  // namespace SP

// @ 0x00c7bba0
namespace SP {
void cPlayer_s00c7_b120::SetWarFlag4(int key)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    *p |= 4u;
}
}  // namespace SP

// @ 0x00c7bbc0
namespace SP {
void cPlayer_s00c7_b120::SetWarFlag8(int key, char value)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    if (value != 0)
        *p |= 8u;
    else
        *p &= 0xfffffff7u;
}
}  // namespace SP

// @ 0x00c7bbf0
namespace SP {
void cPlayer_s00c7_b120::SetWarFlag10(int key, char value)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    if (value != 0)
        *p |= 0x10u;
    else
        *p &= 0xffffffefu;
}
}  // namespace SP

// @ 0x00c7bc20
namespace SP {
void cPlayer_s00c7_b120::SetWarFlag20(int key, char value)
{
    uint32_t* p = mWarFlags.operator[]((const uint32_t*)&key);
    if (value != 0)
        *p |= 0x20u;
    else
        *p &= 0xffffffdfu;
}
}  // namespace SP

// @ 0x00c7bc50
namespace SP {
cSpacePlayerWarData_s00c7_b120* cPlayer_s00c7_b120::WarDataAt(const uint32_t* key)
{
    (void)key;
    return 0;
}
}  // namespace SP

// @ 0x00c7bd40
namespace SP {
void cPlayer_s00c7_b120::NoteWarStartedWithPlayer(int otherPlayer)
{
    int enemyEmpire = *(int*)(otherPlayer + 0x84);
    uint32_t key = (uint32_t)enemyEmpire;
    cSpacePlayerWarData_s00c7_b120* rec = mWarData.operator[](&key);
    rec->mEnemyEmpireID = (uint32_t)enemyEmpire;
    rec->mEnemyCaptured = 0;
    rec->mPlayerCaptured = 0;
    int* stars = FUN_00c308d0((void*)otherPlayer);
    rec->mEnemyStartStars = (uint32_t)((stars[1] - stars[0]) >> 2);
    void* me = FUN_01021300();
    int* myStars = FUN_00c308d0(me);
    rec->mPlayerStartStars = (uint32_t)((myStars[1] - myStars[0]) >> 2);
    rec->mTimer.Restart();
    FUN_00c77bf0(0x5763207);
}
}  // namespace SP

// @ 0x00c7be30
namespace SP {
void cPlayer_s00c7_b120::ResetWarDataWithPlayer(int otherPlayer)
{
    NoteWarEndedWithPlayer(otherPlayer);
    NoteWarStartedWithPlayer(otherPlayer);
}
}  // namespace SP

// @ 0x00c7bea0
namespace SP {
void FUN_00c7bea0()
{
}
}  // namespace SP

// @ 0x00c7c0c0
void* cBanModeVec::DoInsertValue(cBanModeEntry_s00c7_c0c0* position, const cBanModeEntry_s00c7_c0c0& value)
{
    cBanModeEntry_s00c7_c0c0* pBegin = (cBanModeEntry_s00c7_c0c0*)mpBegin;
    cBanModeEntry_s00c7_c0c0* pEnd   = (cBanModeEntry_s00c7_c0c0*)mpEnd;
    cBanModeEntry_s00c7_c0c0* pCap   = (cBanModeEntry_s00c7_c0c0*)mpCap;

    if (pEnd != pCap) {
        const cBanModeEntry_s00c7_c0c0* pValue = &value;
        if (pValue >= position && pValue < pEnd)
            ++pValue;
        if (pEnd != 0)
            new (pEnd) cBanModeEntry_s00c7_c0c0(*(pEnd - 1));
        FUN_00c79b20(position, pEnd - 1, pEnd);
        *position = *pValue;
        mpEnd = pEnd + 1;
        return position;
    }

    uint32_t nPrevSize = (uint32_t)((uint32_t)((char*)pEnd - (char*)pBegin) / 0x14);
    uint32_t nNewSize  = nPrevSize ? nPrevSize * 2 : 1;
    cBanModeEntry_s00c7_c0c0* pNewData = 0;
    if (nNewSize)
        pNewData = (cBanModeEntry_s00c7_c0c0*)FUN_00f473a0(
            nNewSize * 0x14, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);

    uint32_t nPrefixBytes = (uint32_t)((char*)position - (char*)pBegin);
    memcpy(pNewData, pBegin, nPrefixBytes);
    uint32_t nPrefixCount = nPrefixBytes / 0x14;

    cBanModeEntry_s00c7_c0c0* pNewEnd = (cBanModeEntry_s00c7_c0c0*)((char*)pNewData + nPrefixCount * 0x14);
    if (pNewEnd != 0)
        new (pNewEnd) cBanModeEntry_s00c7_c0c0(value);

    uint32_t nSuffixBytes = (uint32_t)((char*)pEnd - (char*)position);
    memcpy((char*)pNewEnd + 0x14, position, nSuffixBytes);
    uint32_t nSuffixCount = nSuffixBytes / 0x14;

    cBanModeEntry_s00c7_c0c0* pNewMpEnd = (cBanModeEntry_s00c7_c0c0*)((char*)pNewEnd + 0x14 + nSuffixCount * 0x14);

    if (pBegin != 0 && ((int*)pBegin)[-1] != 0)
        FUN_00f47380(pBegin);

    mpEnd   = pNewMpEnd;
    mpBegin = pNewData;
    mpCap   = (cBanModeEntry_s00c7_c0c0*)((char*)pNewData + nNewSize * 0x14);
    return position;
}

// @ 0x00c7c220
void cPlayer_s00c7_c0c0::RemoveOwner()
{
    if (mpOwner2C != 0) {
        cRefObj* p = mpOwner2C;
        mpOwner2C = 0;
        p->Release();
    }
    if (mpRef10E8 != 0) {
        cRefObj* p = mpRef10E8;
        mpRef10E8 = 0;
        p->Release();
    }

    // clear the ban-mode table
    {
        void* b = mBanModeTable.mpBegin;
        void* e = mBanModeTable.mpEnd;
        void* r = FUN_00c79ae0(e, e, b);
        mBanModeTable.FUN_00c77ab0(r, e);
        mBanModeTable.mpEnd = (char*)mBanModeTable.mpEnd -
                              ((uint32_t)(((char*)e - (char*)b) / 0x14) * 0x14);
    }

    // clear the three member-id vectors (memcpy(begin,end,0); end -= size)
    {
        uint32_t* e = mVec1184.mpEnd;
        uint32_t* b = mVec1184.mpBegin;
        memcpy(b, e, 0);
        mVec1184.mpEnd = (uint32_t*)((char*)mVec1184.mpEnd + ((((char*)e - (char*)b) >> 2) * -4));
    }
    {
        uint32_t* e = mVec1198.mpEnd;
        uint32_t* b = mVec1198.mpBegin;
        memcpy(b, e, 0);
        mVec1198.mpEnd = (uint32_t*)((char*)mVec1198.mpEnd + ((((char*)e - (char*)b) >> 2) * -4));
    }
    {
        uint32_t* e = mVec11AC.mpEnd;
        uint32_t* b = mVec11AC.mpBegin;
        memcpy(b, e, 0);
        mVec11AC.mpEnd = (uint32_t*)((char*)mVec11AC.mpEnd + ((((char*)e - (char*)b) >> 2) * -4));
    }

    if (mpRef11F4 != 0) {
        cRefObj* p = mpRef11F4;
        mpRef11F4 = 0;
        p->Release();
    }

    static const uint32_t kIds[10] = {
        0x4bef1e3, 0x44f1189, 0x5e902d3, 0x6524498, 0x6526395,
        0x6667038, 0x6666683, 0x6527231, 0x6527eaf, 0x1a0219e
    };
    for (int i = 0; i < 10; ++i) {
        cMessageServerObj* ms = (cMessageServerObj*)MessageServer();
        ms->Broadcast((char*)this + 0x34, kIds[i], -9999);
    }
}

// @ 0x00c7c4a0
void cBanModeVec::resize(uint32_t n)
{
    uint32_t size = (uint32_t)((uint32_t)((char*)mpEnd - (char*)mpBegin) / 0x14);
    if (size < n) {
        cInnerVec value;
        value.mpBegin = 0; value.mpEnd = 0; value.mpCap = 0;
        FUN_00c7bea0(mpEnd, n - size, &value);
        value.dtor();
        return;
    }
    FUN_00c7be50((char*)mpBegin + n * 0x14, mpEnd);
}

// @ 0x00c7c530
void __cdecl FUN_00c7c530(void* stream, cBanModeVec* vec)
{
    void* b = vec->mpBegin;
    void* e = vec->mpEnd;
    void* r = FUN_00c79ae0(e, e, b);
    vec->FUN_00c77ab0(r, e);
    vec->mpEnd = (char*)vec->mpEnd - ((uint32_t)(((char*)e - (char*)b) / 0x14) * 0x14);

    uint32_t count = 0;
    StreamReadInt32(stream, &count);
    vec->FUN_00c77a00(count);

    uint32_t i = 0;
    if (count != 0) {
        do {
            cBanModeEntry_s00c7_c0c0 temp;
            temp.mpBegin = 0; temp.mpEnd = 0; temp.mpCap = 0;
            FUN_00c7b670(stream, &temp);

            cBanModeEntry_s00c7_c0c0* pos = (cBanModeEntry_s00c7_c0c0*)vec->mpEnd;
            if (pos < (cBanModeEntry_s00c7_c0c0*)vec->mpCap) {
                vec->mpEnd = (char*)pos + 0x14;
                if (pos != 0) {
                    uint32_t n = (uint32_t)((char*)temp.mpEnd - (char*)temp.mpBegin) >> 2;
                    uint32_t* data = 0;
                    if (n != 0)
                        data = (uint32_t*)FUN_00f473a0(
                            n * 4, "Simulator", 0, 0,
                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                            0xd1);
                    pos->mpBegin = data;
                    pos->mpEnd   = data;
                    pos->mpCap   = data + n;
                    uint32_t out = 0;
                    FUN_00bdaa40(&out, temp.mpBegin, temp.mpEnd, data, stream);
                    pos->mpEnd = (void*)out;
                }
            } else {
                vec->DoInsertValue(pos, temp);
            }

            DestroyBanTemp(temp);
            ++i;
        } while (i < count);
    }

    ((cStream*)stream)->c1c();
}

// @ 0x00c7c6d0
void cPlayer_s00c7_c0c0::SetGameDataOwner(int owner)
{
    FUN_00b18550_base(owner);
    FUN_0091ff50(&mField10F8);
    mBanModeTable.resize(10);
    AssignAutoRef(&mpRef10E8, (cRefObj*)AllocCollectableItems());
    if (mpRef10E8 != 0)
        ((cCollectableItems*)mpRef10E8)->Configure(0xad56080c, 0x4a5c4493, g_0150d6dc);
    mField10EC = 0;
    FUN_00c751e0();
    cPropertyManager* pm = (cPropertyManager*)PropertyManager();
    if (mpRef11F4 != 0) {
        cRefObj* p = mpRef11F4;
        mpRef11F4 = 0;
        p->Release();
    }
    pm->GetProperty(0x2ca2581, 0x2ae0c7e, &mpRef11F4);
}

// @ 0x00c7c7c0
bool cPlayer_s00c7_c0c0::Read(void* stream)
{
    int local = 0;
    StreamReadInt32(stream, &local);

    uint32_t ver = ((cStream*)stream)->v3c();
    if (ver > 0x210010) {
        uint32_t tmp = 0;
        StreamReadInt32(stream, &tmp);
        g_01687968 = tmp;
    }

    ver = ((cStream*)stream)->v3c();
    if (ver > 0x1c0013) {
        Vec3 v;
        StreamReadInt32(stream, &v);
        FUN_00b6f140(v.x, v.y, v.z);
    }

    bool ok = FUN_00b18600_read(stream);
    cVarListSerializer ser;
    ser.ctor(this, &g_01578d18, 0x1a80d26);
    bool bl = false;
    if (ok) {
        if (ser.Read(stream))
            bl = true;
    }

    mBanModeTable.resize(10);

    if (mpRef10E8 == 0)
        AssignAutoRef(&mpRef10E8, (cRefObj*)AllocCollectableItems());

    cObjectTemplateDB* db = (cObjectTemplateDB*)ObjectTemplateDB();
    if (db != 0) {
        if (mp1244 == 0)
            db->Unregister();
        else
            db->Register(mp1244);
    }

    cPropertyManager* pm = (cPropertyManager*)PropertyManager();
    if (mpRef11F4 != 0) {
        cRefObj* p = mpRef11F4;
        mpRef11F4 = 0;
        p->Release();
    }
    pm->GetProperty(0x2ca2581, 0x2ae0c7e, &mpRef11F4);

    FUN_00c751e0();
    return bl;
}

// @ 0x00c7c9b0
void __cdecl FUN_00c7c9b0(void* stream, cPlanetVec* vec)
{
    void* b = vec->mpBegin;
    void* e = vec->mpEnd;
    void* r = FUN_00c7aca0(e, e, b);
    vec->FUN_00c781e0(r, e);
    vec->mpEnd = (char*)vec->mpEnd - ((uint32_t)(((char*)e - (char*)b) / 0xb0) * 0xb0);

    int32_t count = 0;
    StreamReadInt32(stream, &count);

    int32_t i = 0;
    if (count != 0) {
        do {
            PlayerPlanetData temp;
            temp.mpVtbl = (void*)0x1465d64;
            temp.pv08b = temp.pv08e = temp.pv08c = 0;
            temp.pv20b = temp.pv20e = temp.pv20c = 0;
            temp.pv38b = temp.pv38e = temp.pv38c = 0;
            temp.pv50b = temp.pv50e = temp.pv50c = 0;
            temp.pv68b = temp.pv68e = temp.pv68c = 0;
            ((cGonzagoTimer_s00c7_c0c0*)temp.mTimer)->ctor();
            temp.mA0 = 0xff; temp.mA1 = 0xff; temp.mA2 = 0;

            int32_t key = 0;
            StreamReadInt32(stream, &key);
            ((cStream*)stream)->c1c();
            {
                typedef void (__thiscall *PFN)(void*, void*);
                ((PFN)((void**)temp.mpVtbl)[1])(&temp, stream);
            }
            ((cStream*)stream)->c1c();

            int32_t keyCopy = key;
            FUN_00ba3ca0(&temp);
            void* iter = FUN_00c72540(vec->mpBegin, vec->mpEnd, &keyCopy, ((char*)vec)[0x14]);
            bool inserted;
            if (iter == vec->mpEnd || keyCopy < *(int32_t*)iter) {
                vec->FUN_00ba4de0(iter, &keyCopy);
                inserted = true;
            } else {
                inserted = false;
            }

            ((cGonzagoTimer_s00c7_c0c0*)temp.mTimer)->dtor();
            if (temp.pv68b) FUN_00f47380(temp.pv68b);
            if (temp.pv50b) FUN_00f47380(temp.pv50b);
            if (temp.pv38b) FUN_00f47380(temp.pv38b);
            if (temp.pv20b) FUN_00f47380(temp.pv20b);
            if (temp.pv08b) FUN_00f47380(temp.pv08b);
            if (!inserted)
                FUN_00ba4430((char*)iter + 8, &temp);

            ++i;
        } while (i < count);
    }

    ((cStream*)stream)->c1c();
}

// @ 0x01350ca0
namespace Simulator {
void InitPlayerAttributes()
{
    {
        Attribute a("mGameEventRecord", 0x03b1e966, 0x111c,
                  Read_00c777e0, Write_00675790, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00675850, ToXml_00c788d0);
        *(Attribute*)&cPlayer_sAttributes[0] = a;
    }
    {
        Attribute a("mpCRGItems", 0x03a3a4b4, 0x10e8,
                  Read_00ba8250, Write_00bca960, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b6f550, ToXml_00ac8050);
        *(Attribute*)&cPlayer_sAttributes[1] = a;
    }
    {
        Attribute a("mFlags", 0x03a8d5ca, 0x698,
                  Read_00c78020, Write_00ac9f70, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00cd6630, ToXml_00c78a50);
        *(Attribute*)&cPlayer_sAttributes[2] = a;
    }
    {
        Attribute a("mOneTimeEventFlags", 0x044f3d49, 0x38,
                  Read_00c78130, Write_00c76c70, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c76d10, ToXml_00c78bd0);
        *(Attribute*)&cPlayer_sAttributes[3] = a;
    }
    {
        Attribute a("mSelectedCityHallKey", 0x047696c3, 0x1150,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[4] = a;
    }
    {
        Attribute a("mSelectedVehicleKey", 0x064e5ca6, 0x115c,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[5] = a;
    }
    {
        Attribute a("mSelectedUFOKey", 0x047696e9, 0x1168,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[6] = a;
    }
    {
        Attribute a("mCapitalCityPos", 0x047696ec, 0x1178,
                  Read_00b6e3a0, Write_00ac88c0, ReadText_006930f0, WriteText_00695010,
                  Validate_00b1fbf0, ToXml_00acbba0);
        *(Attribute*)&cPlayer_sAttributes[7] = a;
    }
    {
        Attribute a("mHasCheated", 0x04bc7c77, 0x11f0,
                  Read_00ac8750, Write_00ac8780, ReadText_00693090, WriteText_00694fa0,
                  Validate_00b1fbf0, ToXml_0057ce00);
        *(Attribute*)&cPlayer_sAttributes[8] = a;
    }
    {
        Attribute a("mCurrentGoalProgress", 0x055a9786, 0x10f0,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[9] = a;
    }
    {
        Attribute a("mGoalProgressTotal", 0x055a97a7, 0x10f4,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[10] = a;
    }
    {
        Attribute a("mThemeID", 0x058b5e0e, 0x1244,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cPlayer_sAttributes[11] = a;
    }
    {
        Attribute a("mMaxPosseSize", 0x05d2ac6b, 0x124c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[12] = a;
    }
    {
        Attribute a("mTempPosseCount", 0x066e3237, 0x1250,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[13] = a;
    }
    {
        Attribute a("mUniqueGameID", 0x05ee017b, 0x10f8,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0);
        *(Attribute*)&cPlayer_sAttributes[14] = a;
    }
    {
        Attribute a("mDifficultyLevel", 0x058b5e0f, 0x1248,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[15] = a;
    }
    {
        Attribute a("mStarsVisited", 0x047696ea, 0x1184,
                  Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00eafe40);
        *(Attribute*)&cPlayer_sAttributes[16] = a;
    }
    {
        Attribute a("mStarsKnown", 0x047696eb, 0x1198,
                  Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00eafe40);
        *(Attribute*)&cPlayer_sAttributes[17] = a;
    }
    {
        Attribute a("mWormholesUsed", 0x0674b0b0, 0x11ac,
                  Read_00b04e00, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00eafe40);
        *(Attribute*)&cPlayer_sAttributes[18] = a;
    }
    {
        Attribute a("mSpacePlayerWarData", 0x05626f25, 0x11f8,
                  Read_00c7aef0, Write_00c76d60, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c76e10, ToXml_00d022e0);
        *(Attribute*)&cPlayer_sAttributes[19] = a;
    }
    {
        Attribute a("mPlayerCaptureProgressStars", 0x057a1100, 0x1214,
                  Read_00c7b120, Write_00c75e70, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_01011db0);
        *(Attribute*)&cPlayer_sAttributes[20] = a;
    }
    {
        Attribute a("mEmbassies", 0x0580dbb7, 0x1228,
                  Read_00c78d50, Write_00c75f10, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00d011e0, ToXml_00baa2b0);
        *(Attribute*)&cPlayer_sAttributes[21] = a;
    }
    {
        Attribute a("mPlanetData", 0x0580dbbf, 0x11c0,
                  Read_00c7c9b0, Write_00c76010, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c760c0, ToXml_00c78ea0);
        *(Attribute*)&cPlayer_sAttributes[22] = a;
    }
    {
        Attribute a("mSoothingSongTimer", 0x0600bacf, 0x1258,
                  Read_00ae3470, Write_00ae3490, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00ae3310, ToXml_00ac8050);
        *(Attribute*)&cPlayer_sAttributes[23] = a;
    }
    {
        Attribute a("mSocialTraitProgress", 0x06132c98, 0x1278,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[24] = a;
    }
    {
        Attribute a("mCombatTraitProgress", 0x06132ca7, 0x127c,
                  Read_00572810, Write_00ac88f0, ReadText_006930b0, WriteText_00694fc0,
                  Validate_00b1fbf0, ToXml_00acbb80);
        *(Attribute*)&cPlayer_sAttributes[25] = a;
    }
    {
        Attribute a("mPirateUFOModelKey", 0x062fdfef, 0x1280,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[26] = a;
    }
    {
        Attribute a("mSelectionGroups", 0x064909c8, 0x113c,
                  Read_00c7c530, Write_00c76100, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00c76170, ToXml_00c51440);
        *(Attribute*)&cPlayer_sAttributes[27] = a;
    }
    {
        Attribute a("mCellConsequenceTrait", 0x0679fb51, 0x10fc,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[28] = a;
    }
    {
        Attribute a("mCreatureConsequenceTrait", 0x0679fb52, 0x1100,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[29] = a;
    }
    {
        Attribute a("mTribeConsequenceTrait", 0x0679fb53, 0x1104,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[30] = a;
    }
    {
        Attribute a("mCivConsequenceTrait", 0x0679fb54, 0x1108,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[31] = a;
    }
    {
        Attribute a("mSpaceConsequenceTrait", 0x0679fb55, 0x110c,
                  Read_00572810, Write_00572840, ReadText_00692ff0, WriteText_00694ee0,
                  Validate_00b1fbf0, ToXml_0057cde0);
        *(Attribute*)&cPlayer_sAttributes[32] = a;
    }
    {
        Attribute a("mInitCaptainKey", 0x07be547b, 0x1290,
                  Read_00ae3430, Write_00ae3450, ReadText_00693150, WriteText_00695080,
                  Validate_00b1fbf0, ToXml_00ae5720);
        *(Attribute*)&cPlayer_sAttributes[33] = a;
    }
    {
        Attribute a("mPlayerSpecificEmpireData", 0x0679fb56, 0x11d8,
                  Read_00c7b240, Write_00c77890, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c78ff0);
        *(Attribute*)&cPlayer_sAttributes[34] = a;
    }
    {
        sTotalTimeInCVGDefault = 0x7fffffff;
        Attribute a("mTotalTimeInCVG", 0x06cfb746, 0x128c,
                  Read_00572810, Write_00572840, ReadText_00693090, WriteText_00694f00,
                  Validate_00b1fbf0, ToXml_00675ca0,
                  SetDefault_00c75a80);
        *(Attribute*)&cPlayer_sAttributes[35] = a;
    }
    {
        Attribute a("mAdventuresCompleted", 0x07673918, 0x129c,
                  Read_00c7a970, Write_00c761c0, ReadText_00c2e4e0, WriteText_00692fb0,
                  Validate_00b1fbf0, ToXml_00c79140);
        *(Attribute*)&cPlayer_sAttributes[36] = a;
    }
}
}  // namespace Simulator

// @ 0x01351ae0
void FUN_01351ae0(void)
{
    PropDesc d;
    d.mName = (const char*)0x1473124;
    d.mHash = 0x5626ed3;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_0_24;
    d.mFn28 = (void*)U_01351ae0_0_28;
    d.mFn2C = (void*)0x693070;
    d.mFn30 = (void*)0x694f80;
    d.mFn34 = (void*)U_01351ae0_0_34;
    d.mFn38 = (void*)0x595a50;
    d.mType = 0xa2;
    *(PropDesc*)0x1579600 = d;

    d.mName = (const char*)0x1473110;
    d.mHash = 0x6282444;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_1_24;
    d.mFn28 = (void*)U_01351ae0_1_28;
    d.mFn2C = (void*)U_01351ae0_1_2c;
    d.mFn30 = (void*)U_01351ae0_1_30;
    d.mFn34 = (void*)SAE0_F34A;
    d.mFn38 = (void*)SAE0_F38A;
    d.mType = 0xa1;
    *(PropDesc*)0x157963c = d;

    d.mName = (const char*)0x1473104;
    d.mHash = 0x6282445;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_2_24;
    d.mFn28 = (void*)U_01351ae0_2_28;
    d.mFn2C = (void*)U_01351ae0_2_2c;
    d.mFn30 = (void*)U_01351ae0_2_30;
    d.mFn34 = (void*)SAE0_F34A;
    d.mFn38 = (void*)SAE0_F38A;
    d.mType = 0xa0;
    *(PropDesc*)0x1579678 = d;

    d.mName = (const char*)0x14730f0;
    d.mHash = 0x5d2741e;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_3_24;
    d.mFn28 = (void*)U_01351ae0_3_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_3_34;
    d.mFn38 = (void*)U_01351ae0_3_38;
    d.mType = 0x8;
    *(PropDesc*)0x15796b4 = d;

    d.mName = (const char*)0x14730dc;
    d.mHash = 0x5d27422;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_4_24;
    d.mFn28 = (void*)U_01351ae0_4_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_4_34;
    d.mFn38 = (void*)U_01351ae0_4_38;
    d.mType = 0x20;
    *(PropDesc*)0x15796f0 = d;

    d.mName = (const char*)0x14730c8;
    d.mHash = 0x5d27426;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_5_24;
    d.mFn28 = (void*)U_01351ae0_5_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_5_34;
    d.mFn38 = (void*)U_01351ae0_5_38;
    d.mType = 0x38;
    *(PropDesc*)0x157972c = d;

    d.mName = (const char*)0x14730b8;
    d.mHash = 0x5d2742a;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351ae0_6_24;
    d.mFn28 = (void*)U_01351ae0_6_28;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_6_34;
    d.mFn38 = (void*)U_01351ae0_6_38;
    d.mType = 0x50;
    *(PropDesc*)0x1579768 = d;

    d.mName = (const char*)0x147309c;
    d.mHash = 0x5f0de1b;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xc7b510;
    d.mFn28 = (void*)0xc76300;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)U_01351ae0_7_34;
    d.mFn38 = (void*)0xc793e0;
    d.mType = 0x68;
    *(PropDesc*)0x15797a4 = d;

    d.mName = (const char*)0x1473080;
    d.mHash = 0x689821d;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xae3470;
    d.mFn28 = (void*)0xae3490;
    d.mFn2C = (void*)SAE0_F2CB;
    d.mFn30 = (void*)SAE0_F30B;
    d.mFn34 = (void*)0xae3310;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x80;
    *(PropDesc*)0x15797e0 = d;
}

// @ 0x01351e60
void FUN_01351e60(void)
{
    PropDesc d;
    d.mName = (const char*)0x14731a0;
    d.mHash = 0x5626da6;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_0_24;
    d.mFn28 = (void*)U_01351e60_0_28;
    d.mFn2C = (void*)0x693090;
    d.mFn30 = (void*)0x694f00;
    d.mFn34 = (void*)U_01351e60_0_34;
    d.mFn38 = (void*)0x675ca0;
    d.mType = 0x8;
    *(PropDesc*)0x1579858 = d;

    d.mName = (const char*)0x147318c;
    d.mHash = 0x57a0b60;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)0xae3470;
    d.mFn28 = (void*)0xae3490;
    d.mFn2C = (void*)0xc2e4e0;
    d.mFn30 = (void*)0x692fb0;
    d.mFn34 = (void*)0xae3310;
    d.mFn38 = (void*)0xac8050;
    d.mType = 0x10;
    *(PropDesc*)0x1579894 = d;

    d.mName = (const char*)0x1473174;
    d.mHash = 0x5626dae;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_2_24;
    d.mFn28 = (void*)U_01351e60_2_28;
    d.mFn2C = (void*)U_01351e60_2_2c;
    d.mFn30 = (void*)U_01351e60_2_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x30;
    *(PropDesc*)0x15798d0 = d;

    d.mName = (const char*)0x147315c;
    d.mHash = 0x5626ec6;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_3_24;
    d.mFn28 = (void*)U_01351e60_3_28;
    d.mFn2C = (void*)U_01351e60_3_2c;
    d.mFn30 = (void*)U_01351e60_3_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x34;
    *(PropDesc*)0x157990c = d;

    d.mName = (const char*)0x1473144;
    d.mHash = 0x5626eca;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_4_24;
    d.mFn28 = (void*)U_01351e60_4_28;
    d.mFn2C = (void*)U_01351e60_4_2c;
    d.mFn30 = (void*)U_01351e60_4_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x38;
    *(PropDesc*)0x1579948 = d;

    d.mName = (const char*)0x1473130;
    d.mHash = 0x5626ece;
    d.mZero18 = 0x0;
    d.mZero1C = 0x0;
    d.mDefault = (void*)0x692ca0;
    d.mFn24 = (void*)U_01351e60_5_24;
    d.mFn28 = (void*)U_01351e60_5_28;
    d.mFn2C = (void*)U_01351e60_5_2c;
    d.mFn30 = (void*)U_01351e60_5_30;
    d.mFn34 = (void*)SE60_F34;
    d.mFn38 = (void*)SE60_F38;
    d.mType = 0x3c;
    *(PropDesc*)0x1579984 = d;
}
