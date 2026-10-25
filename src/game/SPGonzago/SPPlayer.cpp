// src/game/SPGonzago/SPPlayer.cpp -- migrated from slice(s) s01351ae0, s01350ca0, s00c7c0c0, s00c793e0, s00c784c0, s00c74d30 by tools/migrate/rewrite.py
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
void* __cdecl FUN_00b3d2a0(void* avatar);          // 0x00b3d2a0 (SP::StarManager)
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
extern uint8_t g_gameModeEntry;     // 0x01654c02  game-mode table entry (DAT_01654c02)
void*  __cdecl FUN_00c771e0(void* pLast, void* pEnd, void* pFirst);            // 0x00c771e0 eastl copy_impl::do_copy
uint32_t __cdecl FUN_00c227e0();                                               // 0x00c227e0 get the ban-pick mode
void   __cdecl FUN_00c227d0(uint32_t nMode);                                   // 0x00c227d0 set the ban-pick mode
void   __cdecl FUN_00ba5bc0(void* pEmpire, uint32_t nArg);                     // 0x00ba5bc0
void*  __cdecl SP_GetCurrentGameMode();                                         // 0x00b5b800
void*  __cdecl SP_NounManager();                                                // 0x00b3d300
void*  __cdecl SP_SpaceGameGet();                                               // 0x01002bd0
void*  __cdecl SP_MessageServer();                                              // 0x0067dcc0
uint32_t __cdecl SP_GetPlayerEmpireOrMinus1();                                  // 0x00b1f9d0
uint32_t __cdecl SP_GetPlayerEmpireID();                                        // 0x01021090
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
void* __cdecl FUN_00c79ae0(void* first, void* last, void* out);                                         // 0x00c79ae0
void  __cdecl FUN_00b6f140(float x, float y, float z);                                                  // 0x00b6f140
void  __cdecl ReadInt32(void* io, void* dst, int count, int ver);                                       // 0x0093a780
void  __cdecl FUN_0091ff50(void* p);                                                                     // 0x0091ff50
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

// @ 0x00c754e0
void __stdcall FUN_00c754e0(cGameNounManager* self)
{
    if (self->GetKind() == 5) {
        void* avatar = self->GetAvatar();
        cStarManager* stars = (cStarManager*)FUN_00b3d2a0(avatar);
        void* empire = stars->GetEmpireByID();
        if (empire)
            ((cEmpire*)empire)->SetValue(0);
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
