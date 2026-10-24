// =============================================================================================
// SporeApp.exe slice s00c77380  (batch gold7, worker 5)
//
// 21 routines hanging off the retail Simulator::cPlayer object:
//
//   0x00c77380  cPlayer flag-hashtable (+0x698) lookup returning the stored int
//   0x00c773d0  cPlayer flag-hashtable (+0x698) key presence test
//   0x00c77410  SP::cPlayer::IsSpace - constant-key presence in the +0x111c set
//   0x00c77450  SP::cPlayer::RemoveEmbassyFromPlanet
//   0x00c774b0  SP::cPlayer::UpdateEmbassyEffects
//   0x00c77700  eastl::hashtable<key3,value>::insert
//   0x00c777e0  Read_00c777e0  - deserialise the +0x111c set
//   0x00c77890  Write_00c77890 - serialise a vector of 8-byte keyed entries
//   0x00c77a00  reserve(n) for the 20-byte entry vector
//   0x00c77ab0  destroy a range of 20-byte vector-of-pointer entries
//   0x00c77b10  recursive delete of the embassy-list nodes
//   0x00c77bf0  SP::cPlayer::HasFlagOrInsert - presence-or-insert in the +0x111c set
//   0x00c77c50  cPlayer::HasEntryInSet - presence test in the +0x38 set
//   0x00c77c90  cPlayer cheat-detection latch (badge disqualification)
//   0x00c77d30  SP::cPlayer::ProcessCommand - the command/event dispatcher
//   0x00c78020  Read_00c78020  - deserialise the +0x698 flag hashtable
//   0x00c78130  Read_00c78130  - deserialise the +0x38 set
//   0x00c781e0  destroy a range of 0xb0-byte PlayerPlanetData records
//   0x00c78280  eastl::vector<8-byte entry>::insert
//   0x00c78420  SP::cPlayer::AddToSet - insert a key into the +0x38 set
//   0x00c78450  SP::cPlayer::NoteWarEndedWithPlayer
//
// Layout: offsets are taken from the disassembly of this build. Every touched field is named.
// Flags: /O2 /Ob2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
// =============================================================================================
#include "types.h"

// ---------------------------------------------------------------------------------------------
// image data / string constants
// ---------------------------------------------------------------------------------------------
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
extern void*   g_vtblPlayerPlanetDataPtr;       // 0x01465d64  ___7PlayerPlanetData_SP__6B_
extern void*   g_vtblSpacePlayerWarDataPtr;     // 0x01472cc8  ___7cSpacePlayerWarData_SP__6B_
extern uint8_t g_vtblPlayerPlanetData[];        // 0x01465d64  vtable object
extern uint8_t g_vtblSpacePlayerWarData[];      // 0x01472cc8  vtable object
extern wchar_t g_wstrCheatWarning[];            // 0x01472cd8  L"Hey, you just cheated! ..."
extern wchar_t g_wstrEmpty16[];                 // 0x01667bac  eastl::gEmptyString16

// ---------------------------------------------------------------------------------------------
// external helpers (retail addresses; not defined here)
// ---------------------------------------------------------------------------------------------
void    __cdecl operator_delete(void* pBlock);                                  // 0x00f47380
void*   __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                 // 0x00f473a0
void*   __cdecl memcpy(void* pDst, const void* pSrc, uint32_t nBytes);          // 0x011e0744
void*   __cdecl eastlMoveRange(void* pDst, const void* pSrc, uint32_t nBytes);  // 0x0099efa0

void*   __cdecl RBTreeIncrement(void* pNode);                                   // 0x00921580
void    __cdecl RBTreeErase(void* pNode, void* pAnchor);                        // 0x00921880
void    __cdecl TreeFind(void* ppOut, void* pKey);                              // 0x00e5c780

bool    __cdecl ReadInt32(void* pStream, void* pDst, uint32_t nCount, int32_t nEndian);   // 0x0093a780
bool    __cdecl WriteUint32(void* pStream, void* pSrc, uint32_t nCount, int32_t nEndian); // 0x0093aa70

// +0x698 flag hashtable / +0x38 set operations

void    __cdecl ReadKey3(void* pStream, void* pKey3);                           // 0x00ae2ed0
void    __cdecl WriteBits6(void* pStream, const uint32_t* pBits);               // 0x00c766b0

// cPlayer support
void*   __cdecl StarManager(void* pAvatarHandle);                               // 0x00b3d2a0
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

// command-dispatcher helpers
void*   __cdecl GetCurrentGameMode();                                           // 0x00b5b800
void*   __cdecl SpaceGameGet();                                                 // 0x01002bd0
void*   __cdecl GetPlayerTribe(void* pGame);                                    // 0x00bfc5f0
void    __cdecl TribeCheatDisable(uint32_t nA, uint32_t nB);                    // 0x00fe5430
void*   __cdecl EffectsManager();                                               // 0x0067ddd0
void*   __cdecl MessageServer();                                                // 0x0067dcc0
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
void*   __cdecl AutoRefCountAsParam(void* pOut);                                // 0x00a16f40
void    __cdecl SetCheatWarningText(const void* pDst, const void* pSrc);        // 0x00454cb0

// ---------------------------------------------------------------------------------------------
// small shared types
// ---------------------------------------------------------------------------------------------
class cGonzagoTimer {
public:
    uint64_t mPad00[4];                             // +0x00 0x20 bytes, 8-byte aligned
    ~cGonzagoTimer();                               // 0x00b638b0
};

// a node of the +0x698 flag hashtable (key at +0x00, value at +0x04, chain at +0x08)
struct cFlagNode {
    uint32_t   mKey;                                // +0x00
    int32_t    mValue;                              // +0x04
    cFlagNode* mpNext;                              // +0x08
};

// a node of the +0x111c key set (key at +0x00, chain at +0x04)
struct cU32Node {
    uint32_t   mKey;                                // +0x00
    cU32Node*  mpNext;                              // +0x04
};

// a node of the +0x38 key3 set (three key words at +0x00..+0x08, chain at +0x0c)
struct cKey3Node {
    uint32_t   mKey0;                               // +0x00
    uint32_t   mKey1;                               // +0x04
    uint32_t   mKey2;                               // +0x08
    cKey3Node* mpNext;                              // +0x0c
};

// an eastl hashtable header as consumed here (buckets +0x04, count +0x08, size +0x0c)
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

// eastl rbtree node base
struct cTreeNode {
    cTreeNode* mpLeft;                              // +0x00
    cTreeNode* mpRight;                             // +0x04
    cTreeNode* mpParent;                            // +0x08
    uint8_t    mPad0c[0x04];                        // +0x0c
};

// the rbtree as laid out inside cPlayer (anchor at +0x04, leftmost at +0x08, count at +0x14)
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

// one embassy record node
struct cEmbassyNode {
    cTreeNode  mNode;                               // +0x00
    void*      mStarRecord;                         // +0x10
    int32_t    mnEmbassyTimer;                      // +0x18 int accumulator
};

// a 0x2c-stride entry of a star record's embassy array
struct cEmbassyEntry {
    uint32_t mFlag;                                 // +0x00
    uint8_t  mPad04[0x10];                          // +0x04
    float    mfTimer;                               // +0x14
};

// star record as touched by UpdateEmbassyEffects
class cStarRecordView {
public:
    uint8_t        mPad00[0x134];                   // +0x000
    cEmbassyEntry* mpEmbassyBegin;                  // +0x134
    cEmbassyEntry* mpEmbassyEnd;                    // +0x138
};

// a 0x14-byte vector-of-pointers entry (released by vtable slot +0xc0)
struct cPtrVecEntry {
    void** mpBegin;                                 // +0x00
    void** mpEnd;                                   // +0x04
    uint8_t mPad08[0x0c];                           // +0x08
};

// a 20-byte eastl::pair entry of the ban/embassy vector
struct cEntry20 {
    uint32_t mKey;                                  // +0x00
    uint8_t  mPad04[0x10];                          // +0x04
};

// an 8-byte keyed entry serialised by Write_00c77890 (key + 6-bit field)
struct cEntry8 {
    uint32_t mKey;                                  // +0x00
    uint32_t mBits;                                 // +0x04
};

// the 12-byte insert-result tuple returned by the hashtable insert helpers
struct cInsertResult {
    void*   mpNode;                                 // +0x00
    void**  mpBucket;                               // +0x04
    uint8_t mbInserted;                             // +0x08
};

// eastl::vector storage header
template <typename T>
class cVector {
public:
    T* mpBegin;                                     // +0x00
    T* mpEnd;                                       // +0x04
    T* mpCap;                                       // +0x08
    uint32_t Count() const { return (uint32_t)(mpEnd - mpBegin); }
    uint32_t Capacity() const { return (uint32_t)(mpCap - mpBegin); }
    void Reserve(uint32_t nCount);                  // 0x00c77a00
    void Insert(T* pPos, const T* pValue);          // 0x00c78280
};

// one embassy-list node deleted by 0x00c77b10
struct cEmbassyList {
    cEmbassyList* mpChild;                          // +0x00
    cEmbassyList* mpNext;                           // +0x04
    uint8_t       mPad08[0x10];                     // +0x08
    void*         mpVtbl18;                         // +0x18
    uint8_t       mPad1c[0x0c];                     // +0x1c
    uint8_t       mTimer28[0x20];                   // +0x28 cGonzagoTimer
    void Destroy(cEmbassyList* pHead);              // 0x00c77b10
};

// one 0xb0-byte PlayerPlanetData record destroyed by 0x00c781e0
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

// ---------------------------------------------------------------------------------------------
// the serialisation stream and the provider it hands out
// ---------------------------------------------------------------------------------------------
class ISerializerStream {
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

static void* GetIOStream(ISerializerStream* pStream)
{
    return ((IIOProvider*)pStream->v20())->v18();
}

// ---------------------------------------------------------------------------------------------
// SP::cPlayer
// ---------------------------------------------------------------------------------------------
namespace SP {

class cPlayer {
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
    void RemoveEmbassyFromPlanet(void* pStarRecordRef);
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
    void NoteWarEndedWithPlayer(void* pEmpire);
    // 0x00c772c0 - presence of an arbitrary key in the +0x111c set
    bool HasCheatFlagEx(const uint32_t* pKey);
};

// The command sink is the interface sub-object embedded at cPlayer+0x34; the dispatcher is entered with
// that sub-object's address in `this`, so it walks back 0x34 to reach the owning cPlayer.
class cPlayerCommand {
public:
    void* mpVtbl00;                                 // +0x0000 (cPlayer+0x0034)
    uint8_t mPad04[0x34 - 0x04];                    // +0x0004
    // 0x00c77d30
    bool ProcessCommand(uint32_t nCommand, int32_t* pArg);
};

} // namespace SP

// ---------------------------------------------------------------------------------------------
// 0x00c77380 - look up nKey in the flag hashtable and return the stored int
// ---------------------------------------------------------------------------------------------
// @ 0x00c77380
bool SP::cPlayer::GetFlagValue(uint32_t nKey, int32_t* pnOut)
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

// ---------------------------------------------------------------------------------------------
// 0x00c773d0 - key presence test in the flag hashtable
// ---------------------------------------------------------------------------------------------
// @ 0x00c773d0
bool SP::cPlayer::HasFlag(uint32_t nKey)
{
    cHashtableHeader* pMap = &mFlagMap698;
    void* aIter[2];
    pMap->FindFlag(aIter, &nKey);
    return (cFlagNode*)aIter[0] != (cFlagNode*)pMap->mpBuckets[pMap->mnBucketCount];
}

// ---------------------------------------------------------------------------------------------
// 0x00c77410 - presence of the constant space flag in the +0x111c set
// ---------------------------------------------------------------------------------------------
// @ 0x00c77410
bool SP::cPlayer::IsSpace()
{
    const uint32_t nKey = 0x05f1f0ca;
    int32_t nFound = 0;
    for (cU32Node* pNode = (cU32Node*)mKeySet111c.mpBuckets[nKey % mKeySet111c.mnBucketCount];
         pNode != 0; pNode = pNode->mpNext) {
        if (pNode->mKey == nKey)
            ++nFound;
    }
    return nFound != 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c772c0 - presence of an arbitrary key in the +0x111c set (the cheat-flag test)
// ---------------------------------------------------------------------------------------------
bool SP::cPlayer::HasCheatFlagEx(const uint32_t* pKey)
{
    uint32_t nKey = *pKey;
    int32_t nFound = 0;
    for (cU32Node* pNode = (cU32Node*)mKeySet111c.mpBuckets[nKey % mKeySet111c.mnBucketCount];
         pNode != 0; pNode = pNode->mpNext) {
        if (pNode->mKey == nKey)
            ++nFound;
    }
    return nFound != 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c77450 - remove the embassy record for a star from the embassy rbtree
// ---------------------------------------------------------------------------------------------
// @ 0x00c77450
void SP::cPlayer::RemoveEmbassyFromPlanet(void* pStarRecordRef)
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

// ---------------------------------------------------------------------------------------------
// 0x00c774b0 - advance every embassy timer and expire / escalate as needed
// ---------------------------------------------------------------------------------------------
// @ 0x00c774b0
void SP::cPlayer::UpdateEmbassyEffects(int32_t nElapsedMs)
{
    cPlayerTree* pTree = &mEmbassyTree;
    for (cTreeNode* pNode = pTree->mpHead; pNode != (cTreeNode*)&pTree->mpEnd; ) {
        cEmbassyNode* pEmbassy = (cEmbassyNode*)pNode;
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

// ---------------------------------------------------------------------------------------------
// 0x00c77700 - eastl::hashtable<key3,value>::insert
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// 0x00c777e0 - deserialise the +0x111c set
// ---------------------------------------------------------------------------------------------
// @ 0x00c777e0
void __cdecl Read_00c777e0(ISerializerStream* pStream, cHashtableHeader* pData)
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

// ---------------------------------------------------------------------------------------------
// 0x00c77890 - serialise a vector of 8-byte keyed entries
// ---------------------------------------------------------------------------------------------
// @ 0x00c77890
bool __cdecl Write_00c77890(ISerializerStream* pStream, cVector<cEntry8>* pData)
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

// ---------------------------------------------------------------------------------------------
// 0x00c77a00 - reserve(n) for the 20-byte entry vector
// ---------------------------------------------------------------------------------------------
// @ 0x00c77a00
template <>
void cVector<cEntry20>::Reserve(uint32_t nCount)
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

// ---------------------------------------------------------------------------------------------
// 0x00c77ab0 - destroy a range of 20-byte vector-of-pointer entries
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// 0x00c77b10 - recursively delete the embassy-list nodes
// ---------------------------------------------------------------------------------------------
// @ 0x00c77b10
void cEmbassyList::Destroy(cEmbassyList* pHead)
{
    while (pHead != 0) {
        Destroy(pHead->mpChild);
        cEmbassyList* pNext = pHead->mpNext;
        pHead->mpVtbl18 = (void*)g_vtblSpacePlayerWarData;
        ((cGonzagoTimer*)pHead->mTimer28)->~cGonzagoTimer();
        operator_delete(pHead);
        pHead = pNext;
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c77bf0 - presence-or-insert in the +0x111c set
// ---------------------------------------------------------------------------------------------
// @ 0x00c77bf0
bool SP::cPlayer::HasFlagOrInsert(uint32_t nKey)
{
    cHashtableHeader* pSet = &mKeySet111c;
    int32_t nFound = 0;
    for (cU32Node* pNode = (cU32Node*)pSet->mpBuckets[nKey % pSet->mnBucketCount];
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

// ---------------------------------------------------------------------------------------------
// 0x00c77c50 - presence test in the +0x38 key3 set
// ---------------------------------------------------------------------------------------------
// @ 0x00c77c50
bool SP::cPlayer::HasEntryInSet(const uint32_t* pKey)
{
    cHashtableHeader* pSet = &mSet38;
    void* aIter[2];
    pSet->Find3(aIter, pKey);
    return (cKey3Node*)aIter[0] != (cKey3Node*)pSet->mpBuckets[pSet->mnBucketCount];
}

// ---------------------------------------------------------------------------------------------
// 0x00c77c90 - latch the cheat-detected state and disqualify the player from badges
// ---------------------------------------------------------------------------------------------
// @ 0x00c77c90
void SP::cPlayer::LatchCheatDetected()
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

// ---------------------------------------------------------------------------------------------
// 0x00c77d30 - the command/event dispatcher
// ---------------------------------------------------------------------------------------------
// @ 0x00c77d30
bool SP::cPlayerCommand::ProcessCommand(uint32_t nCommand, int32_t* pArg)
{
    SP::cPlayer* pPlayer = (SP::cPlayer*)((uint8_t*)this - 0x34);

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

// ---------------------------------------------------------------------------------------------
// 0x00c78020 - deserialise the +0x698 flag hashtable
// ---------------------------------------------------------------------------------------------
// @ 0x00c78020
bool __cdecl Read_00c78020(ISerializerStream* pStream, cHashtableHeader* pData)
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

// ---------------------------------------------------------------------------------------------
// 0x00c78130 - deserialise the +0x38 key3 set
// ---------------------------------------------------------------------------------------------
// @ 0x00c78130
bool __cdecl Read_00c78130(ISerializerStream* pStream, cHashtableHeader* pData)
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

// ---------------------------------------------------------------------------------------------
// 0x00c781e0 - destroy a range of 0xb0-byte PlayerPlanetData records
// ---------------------------------------------------------------------------------------------
// @ 0x00c781e0
void __stdcall DestroyPlayerPlanetDataRange(cPlayerPlanetData* pBegin, cPlayerPlanetData* pEnd)
{
    if (pBegin >= pEnd)
        return;
    uint32_t nCount = ((uint32_t)((uint8_t*)pEnd - (uint8_t*)pBegin) - 1) / 0xb0 + 1;
    for (uint32_t nLeft = nCount; nLeft != 0; --nLeft) {
        cPlayerPlanetData* p = pBegin;
        p->mpVtbl08 = (void*)g_vtblPlayerPlanetData;
        ((cGonzagoTimer*)p->mTimer88)->~cGonzagoTimer();
        if (p->mpBlock70) operator_delete(p->mpBlock70);
        if (p->mpBlock58) operator_delete(p->mpBlock58);
        if (p->mpBlock40) operator_delete(p->mpBlock40);
        if (p->mpBlock28) operator_delete(p->mpBlock28);
        if (p->mpBlock10) operator_delete(p->mpBlock10);
        pBegin = (cPlayerPlanetData*)((uint8_t*)pBegin + 0xb0);
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c78280 - eastl::vector<8-byte entry>::insert
// ---------------------------------------------------------------------------------------------
// @ 0x00c78280
template <>
void cVector<cEntry8>::Insert(cEntry8* pPos, const cEntry8* pValue)
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

// ---------------------------------------------------------------------------------------------
// 0x00c78420 - insert a 3-word key into the +0x38 set
// ---------------------------------------------------------------------------------------------
// @ 0x00c78420
void SP::cPlayer::AddToSet(const uint32_t* pKey)
{
    bool bFlag = false;
    cInsertResult res;
    mSet38.Insert3((void**)&res, pKey, bFlag);
}

// ---------------------------------------------------------------------------------------------
// 0x00c78450 - drop the war-event record for the given empire
// ---------------------------------------------------------------------------------------------
// @ 0x00c78450
void SP::cPlayer::NoteWarEndedWithPlayer(void* pEmpire)
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
    ((cGonzagoTimer*)((uint8_t*)pNode + 0x28))->~cGonzagoTimer();
    operator_delete(pNode);
}
