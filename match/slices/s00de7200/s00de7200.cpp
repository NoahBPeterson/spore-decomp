// Slice s00de7200 -- 0x00de76b0: constructor body of a Simulator UI/editor controller. It builds a
// std::map<int, Handler*> of per-mode handlers (key -> handler, each handler's vtable slot 11 is an
// init hook), clears a 3x3 table of collectable-item refs, creates six cCollectableItems inventories,
// reads a byte option and registers a message-id table with the MessageServer.
// Built /O2 /MD /Gy /EHsc /TP.
#include "types.h"
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long long u64;

void* operator new(unsigned int, const char*, int, int, int, int);  // 0x00F473A0 (EA allocator)

struct Handler {
    virtual int  AddRef();
    virtual int  Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Init();   // 0x2c
};

// 8-byte handlers: base ctor 0x00e00630, then derived vtable.
struct HandlerBase : Handler { int f; HandlerBase(); };
struct HandlerA : HandlerBase { virtual void Init(); };   // vtable 0x147dec8
struct HandlerB : HandlerBase { virtual void Init(); };   // vtable 0x147df38
struct HandlerC : HandlerBase { virtual void Init(); };   // vtable 0x147dfc0

struct H0  : Handler { char pad[0x28]; H0(); };           // 0x2c, ctor 0x00dea500
struct H2  : Handler { char pad[0xa4]; H2(); };           // 0xa8, ctor 0x00e008e0 (cSPUIGlobalUIRootWinProc)
struct H3  : Handler { char pad[0xe4]; H3(); };           // 0xe8, ctor 0x00de2d00
struct H11 : Handler { char pad[0x4c]; H11(); };          // 0x50, ctor 0x00de3370
struct H12 : Handler { char pad[0xc]; H12(); };           // 0x10, ctor 0x00deb670
struct H4  : Handler { char pad[0x14]; H4(); };           // 0x18, ctor 0x00dee320
struct H13 : Handler { char pad[0x174]; H13(); };         // 0x178, ctor 0x00dfb9c0

// Simulator::cCollectableItems (0x6dac bytes, ctor 0x00597e00); also SP::cSpaceInventory
struct Items {
    virtual int  AddRef();
    virtual int  Release();
    char pad[0x6da4 + 4];
    Items();
    void Configure(uint a, uint b, uint c);      // 0x00599440 ret 0xc
    void SetPair(u64 v);                         // 0x00596d70 ret 8
};
u64  FUN_00593980(uint a, uint b);               // cdecl, returns edx:eax
void FUN_00de4f50(Items* it, int n);             // cdecl
bool FUN_00685520(int n);                        // cdecl

struct HMap { Handler** Slot(int* key); };       // 0x00de7630 ret 4 (std::map<int,Handler*>::operator[])

struct Prop {
    void* data;       // +0
    char  pad[0xc];
    uchar flags;      // +0x10
    uchar pad2;
    short type;       // +0x12
};
struct PropList { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                  virtual void v8();
                  virtual bool Get(uint id, Prop** out); };   // 0x24
extern PropList* sAppProperties;                  // 0x015fd918

struct MsgServer { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
                   virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
                   virtual void m8();
                   virtual void AddListener(void* target, uint msg); };   // 0x24
struct LayerMgr  { virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3();
                   virtual void l4(); virtual void l5(); virtual void l6(); virtual void l7();
                   virtual void l8(); virtual void l9(); virtual void l10();
                   virtual void Set(uint id, int v); };                   // 0x2c
MsgServer* SP_MessageServer();                    // 0x0067dcc0
LayerMgr*  SP_LayerManager();                     // 0x0067cb20
extern char* kGUI_PanelIDs;                        // 0x016a1344
extern uint DAT_015a3b90[0x25];

struct Ctl {
    char   pad0[0x10];
    MsgServer* mServer;      // +0x10
    void*      mTarget;      // +0x14
    uint*      mTable;       // +0x18
    uint       mCount;       // +0x1c
    uint       mZero;        // +0x20
    char   pad1[0xd0];
    uchar  mOpt;             // +0xf4
    char   pad2[0x2f];
    HMap   mHandlers;        // +0x124
    char   pad3[0x8c];
    Items* mGrid[9];         // +0x1b4 .. +0x1d4
    char   pad4[0x14];
    int    m1ec;             // +0x1ec

    void Base();             // 0x00de63e0
    void Ctor();             // 0x00de76b0
};

static inline void Assign(Items*& slot, Items* p)
{
    Items* old = slot;
    if (p != old) {
        if (p) p->AddRef();
        slot = p;
        if (old) old->Release();
    }
}

// @ 0x00de76b0
void Ctl::Ctor()
{
    union { int key; Prop* p; } u;
    Base();
    m1ec = 0;

    H0* h0 = new ("Simulator", 0, 0, 0, 0) H0();
    h0->Init();
    u.key = 0;  *mHandlers.Slot(&u.key) = h0;
    u.key = 1;  *mHandlers.Slot(&u.key) = h0;
    u.key = 8;  *mHandlers.Slot(&u.key) = h0;
    u.key = 9;  *mHandlers.Slot(&u.key) = h0;

    H2* h2 = new ("Simulator", 0, 0, 0, 0) H2();
    h2->Init();
    u.key = 2;  *mHandlers.Slot(&u.key) = h2;

    H3* h3 = new ("Simulator", 0, 0, 0, 0) H3();
    h3->Init();
    u.key = 3;  *mHandlers.Slot(&u.key) = h3;
    u.key = 5;  *mHandlers.Slot(&u.key) = h3;

    HandlerA* ha = new ("Simulator", 0, 0, 0, 0) HandlerA();
    ha->Init();
    u.key = 6;  *mHandlers.Slot(&u.key) = ha;

    HandlerB* hb = new ("Simulator", 0, 0, 0, 0) HandlerB();
    hb->Init();
    u.key = 7;  *mHandlers.Slot(&u.key) = hb;

    HandlerC* hc = new ("Simulator", 0, 0, 0, 0) HandlerC();
    hc->Init();
    u.key = 10; *mHandlers.Slot(&u.key) = hc;

    H11* h11 = new ("Simulator", 0, 0, 0, 0) H11();
    h11->Init();
    u.key = 11; *mHandlers.Slot(&u.key) = h11;

    H12* h12 = new ("Simulator", 0, 0, 0, 0) H12();
    h12->Init();
    u.key = 12; *mHandlers.Slot(&u.key) = h12;

    H4* h4 = new ("Simulator", 0, 0, 0, 0) H4();
    h4->Init();
    u.key = 4;  *mHandlers.Slot(&u.key) = h4;

    if (FUN_00685520(2)) {
        H13* h13 = new ("Simulator", 0, 0, 0, 0) H13();
        h13->Init();
        u.key = 13; *mHandlers.Slot(&u.key) = h13;
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            Items* it = mGrid[i * 3 + j];
            if (it) {
                mGrid[i * 3 + j] = 0;
                it->Release();
            }
        }
    }

    Assign(mGrid[6], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[6]->Configure(0xad56080c, 0x4a5c4493, 0x40626000);
    FUN_00de4f50(mGrid[6], 3);

    Assign(mGrid[7], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[7]->Configure(0xad56080c, 0x4a5c4493, 0x40626000);
    FUN_00de4f50(mGrid[7], 6);

    Assign(mGrid[8], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[8]->Configure(0xad56080c, 0x4a5c4493, 0x40626000);
    FUN_00de4f50(mGrid[8], 5);

    Assign(mGrid[3], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[3]->Configure(0, 0, 0x40616000);

    Assign(mGrid[3], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[3]->Configure(0, 0, 0x40616000);
    { Items* t = mGrid[3]; t->SetPair(FUN_00593980(0x40626000, 0x32ac9620)); }
    { Items* t = mGrid[3]; t->SetPair(FUN_00593980(0x40626000, 0x3a3c49a5)); }

    Assign(mGrid[4], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[4]->Configure(0, 0, 0x40616000);
    { Items* t = mGrid[4]; t->SetPair(FUN_00593980(0x40626000, 0x32ac9620)); }
    { Items* t = mGrid[4]; t->SetPair(FUN_00593980(0x40626000, 0xfe534766)); }

    Assign(mGrid[5], new ("Simulator", 0, 0, 0, 0) Items());
    mGrid[5]->Configure(0, 0, 0x40616000);
    { Items* t = mGrid[5]; t->SetPair(FUN_00593980(0x40626000, 0xfe534766)); }
    { Items* t = mGrid[5]; t->SetPair(FUN_00593980(0x40626000, 0x3a3c49a5)); }

    if (sAppProperties) {
        if (sAppProperties->Get(0x64a44a8, &u.p) && u.p->type == 1) {
            Prop* p = u.p;
            uchar* d = (uchar*)p;
            if (p->flags & 0x30) d = *(uchar**)p;
            mOpt = *d;
        }
    }

    void* panel = kGUI_PanelIDs ? kGUI_PanelIDs + 8 : 0;
    MsgServer* ms = SP_MessageServer();
    mServer = ms;
    mTarget = panel;
    mTable  = DAT_015a3b90;
    mCount  = 0x25;
    mZero   = 0;
    if (ms && panel) {
        uint off = 0;
        do {
            ms->AddListener(panel, *(uint*)((char*)DAT_015a3b90 + off));
            off += 4;
        } while (off < 0x94);
    }

    SP_LayerManager()->Set(0x5807346, 0);
    SP_LayerManager()->Set(0x5807345, 0);
}
// --- equivalence checker address annotations

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}

namespace __equiv_ann1 {   // address annotations for the equivalence checker; never referenced
struct H0 {
    H0();   // 0x00dea500 (equiv t3)
};
struct H11 {
    H11();   // 0x00de3370 (equiv t3)
};
struct H12 {
    H12();   // 0x00deb670 (equiv t3)
};
struct H13 {
    H13();   // 0x00dfb9c0 (equiv t3)
};
struct H2 {
    H2();   // 0x00e008e0 (equiv t3)
};
struct H3 {
    H3();   // 0x00de2d00 (equiv t3)
};
struct H4 {
    H4();   // 0x00dee320 (equiv t3)
};
struct HMap {
    void Slot();   // 0x00de7630 (equiv t3)
};
struct HandlerBase {
    HandlerBase();   // 0x00e00630 (equiv t3)
};
}

// ---------------------------------------------------------------------------------------------
// Layout-manager maps and Simulator teardown (0x00de7200, 0x00de7330, 0x00de74c0, 0x00de7530,
// 0x00de7590, 0x00de7630, 0x00de7eb0). All of these walk eastl rbtree anchors whose sentinel is
// the anchor itself; keys live at +0x10 of a node and the payload right after them.
struct RbNode {                                     // eastl::rbtree_node_base
    RbNode*  mpLeft;                                // +0x00
    RbNode*  mpRight;                               // +0x04
    RbNode*  mpParent;                              // +0x08
    uint32_t mColor;                                // +0x0c
};
struct Key { uint32_t a, b, c; };                   // EA::ResourceMan::Key

struct RefObj {                                     // an IAutoRefCount target
    virtual void s00();                             // +0x00
    virtual int  Release();                         // +0x04
    virtual void s08(int nFlag);                    // +0x08
    virtual void s0c(); virtual void s10(); virtual void s14(); virtual void s18();
    virtual void s1c(); virtual void s20(); virtual void s24(); virtual void s28();
    virtual void s2c();
    virtual void Stop();                            // +0x30
};

struct FeedbackNode : RbNode {                      // node of map<ResourceMan::Key, AutoRefCount>
    Key   mKey;                                     // +0x10
    void* mpValue;                                  // +0x1c
};
struct KeyRbTree {                                  // RbTree_00a21dc0 at +0x70
    void*  mpRoot;                                  // +0x00
    RbNode mAnchor;                                 // +0x04  (end = &mAnchor)
    void* Find(const void* pKey, void** ppOut);     // 0x00a21dc0
};
struct FeedbackMap {
    uint32_t  mPad00;                               // +0x00
    RbNode    mAnchor;                              // +0x04  (begin = mpRight, end = &mAnchor)
    uint32_t  mCount;                               // +0x14
    uint8_t   mPad18[0x70 - 0x18];
    KeyRbTree mKeyTree;                             // +0x70
    void  FindUintKey(FeedbackNode** ppNode, uint32_t nKey);         // 0x00e5c780 (eastl rbtree find)
    void  FindKey(FeedbackNode** ppNode, const Key* pKey);           // 0x00c7f560
    void* FindOrInsertKey(const Key* pKey);                          // 0x00de7590
    void  EraseUintKey(uint32_t nKey);                               // 0x00de74c0
    void  RemoveKeyEntry(uint32_t nKey, void* pValue);               // 0x00de6f20
    void  InsertKey(FeedbackNode** ppNode, RbNode* pWhere, const Key* pKey, char bFlag);  // 0x00de6900
};
struct FeedbackWriter {
    virtual void Begin(const wchar_t* pName);       // +0x00
    virtual void End(const wchar_t* pName);         // +0x04
};
bool WriteKeyValue(void* pWriter, int nZero, const void* pKey, const wchar_t* pTypeName);
bool SerializeFeedback(FeedbackWriter* pWriter, const wchar_t* pName, FeedbackMap* pMap);

struct WorldNode : RbNode {                         // node of map<Key, cSPUILayoutManager::cWorld>
    Key      mKey;                                  // +0x10
    uint32_t mValueA;                               // +0x1c
    uint32_t mValueB;                               // +0x20
    uint32_t mValueC;                               // +0x24
};
struct WorldMap {
    uint32_t mPad00;                                // +0x00
    RbNode   mAnchor;                               // +0x04
    uint32_t mPad14;                                // +0x14
    void NukeSubtree(RbNode* pRoot);                // 0x009a9600
    void Insert(WorldNode** ppNode, const void* pKey, char bFlag);   // 0x00de5f60
};
struct ReaderHost {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05();
    virtual void* GetStream();                      // +0x18
};
struct Reader {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05();
    virtual void  ReadKey(void* pOut);              // +0x18
    virtual void  NextKey();                        // +0x1c
    virtual ReaderHost* GetHost();                  // +0x20
};
void ReadInt32(void* pStream, void* pOut, int nCount, void* pZero);  // 0x0093a780 EA::IO::ReadInt32
void ReadKeyData(void* pReader, void* pOut);        // 0x00ae2ed0
void ReadWorldMap(Reader* pReader, WorldMap* pMap); // 0x00de7200

struct KeyVector {                                  // eastl::sp_vector<EA::ResourceMan::Key>
    uint32_t mPad00;                                // +0x00
    Key*     mpEnd;                                 // +0x04
    Key*     mpCap;                                 // +0x08
    void DoInsertKey(Key* pPos, const Key* pKey);   // 0x004e3e10
};
struct KeyListNode : RbNode {
    uint32_t mPad10;                                // +0x10
    uint32_t mPad14;                                // +0x14
    uint32_t mPad18;                                // +0x18
    Key      mKey;                                  // +0x1c
};
struct KeyCollector {
    uint8_t mPad00[0x3c];
    RbNode  mAnchor;                                // +0x3c
    void CollectKeys(KeyVector* pOut);              // 0x00de7530
};

struct IntNode : RbNode {
    int      mKey;                                  // +0x10
    Handler* mpValue;                               // +0x14
};
struct IntMap {
    uint32_t mPad00;                                // +0x00
    RbNode   mAnchor;                               // +0x04
    uint32_t mPad14;                                // +0x14
    Handler** Slot(int* pKey);                      // 0x00de7630
    void      Insert(RbNode** ppNode, RbNode* pWhere, const int* pKey, char* pFlag);   // 0x00de6a60
};
struct InsertResult {                               // the locals of 0x00de7630
    RbNode*  mpNode;                                // +0x00
    uint32_t mPad04;                                // +0x04
    uint32_t mPad08;                                // +0x08
    uint32_t mPad0c;                                // +0x0c
    char     mFlag;                                 // +0x10
    uint8_t  mPad11[3];
    uint32_t mPad12;                                // +0x14
};

struct EffectNode : RbNode {
    int       mKey;                                 // +0x10
    RefObj*   mpEffect;                             // +0x14
};
struct GlobalMgr {
    void Shutdown();                                // 0x00df9510
};
void  FUN_00de4850(void* pThis);                    // 0x00de4850
void* FUN_00df5f40();                               // 0x00df5f40
void  RemoveHandler(void* pServer, void* pTarget, uint* pTable, uint nCount, uint nZero);   // 0x00571db0
void  FUN_00de5df0(void* pSet, void* pValue, char bFlag);  // 0x00de5df0

struct SimTeardown {
    uint8_t    mPad00[0x10];
    void*      mpServer;                            // +0x10
    void*      mpTarget;                            // +0x14
    uint*      mpTable;                             // +0x18
    uint       mCount;                              // +0x1c
    uint       mZero;                               // +0x20
    uint8_t    mPad24[0x124 - 0x24];
    IntMap     mHandlers;                           // +0x124
    uint8_t    mPad13c[0x160 - 0x13c];
    RefObj*    mpC160;                              // +0x160
    RefObj*    mpC164;                              // +0x164
    RefObj*    mpC168;                              // +0x168
    RefObj*    mpC16c;                              // +0x16c
    RefObj*    mpC170;                              // +0x170
    RefObj*    mpC174;                              // +0x174
    uint8_t    mPad178[0x198 - 0x178];
    RefObj*    mpC198;                              // +0x198
    RefObj*    mpC19c;                              // +0x19c
    RefObj*    mpC1a0;                              // +0x1a0
    RefObj*    mpC1a4;                              // +0x1a4
    RefObj*    mpC1a8;                              // +0x1a8
    uint32_t   mPad1ac;                             // +0x1ac
    RefObj*    mpC1b0;                              // +0x1b0
    RefObj*    mGrid[9];                            // +0x1b4
    RefObj**   mpVecBegin;                          // +0x1d8
    RefObj**   mpVecEnd;                            // +0x1dc
    uint8_t    mPad1e0[0x250 - 0x1e0];
    RefObj*    mpC250;                              // +0x250
    void Teardown();                                // 0x00de7eb0
};

static void ReleaseSlot(RefObj*& pSlot, int nVTableSlot)
{
    if (pSlot) {
        RefObj* pOld = pSlot;
        pSlot = 0;
        if (nVTableSlot == 8)
            pOld->s08(1);
        else
            pOld->Release();
    }
}

RbNode* RBTreeIncrement(RbNode* pNode);             // 0x00921580
void    RBTreeErase(RbNode* pNode, RbNode* pHeader); // 0x00921880
void    operator_delete__(void* p);                 // 0x00f47380

// @ 0x00de7200
void ReadWorldMap(Reader* pReader, WorldMap* pMap)
{
    pMap->NukeSubtree(pMap->mAnchor.mpParent);
    pMap->mAnchor.mpLeft = &pMap->mAnchor;
    pMap->mAnchor.mpRight = &pMap->mAnchor;
    pMap->mAnchor.mpParent = 0;
    pMap->mAnchor.mColor = 0;
    pMap->mPad14 = 0;

    uint32_t nCount = 0;
    void* pStream = pReader->GetHost()->GetStream();
    ReadInt32(pStream, &nCount, 1, 0);

    for (uint32_t i = 0; i < nCount; ++i) {
        Key key;
        Key value;
        ReadKeyData(pReader, &key);
        pReader->NextKey();
        ReadKeyData(pReader, &value);
        pReader->NextKey();

        WorldNode* pNode = 0;
        pMap->Insert(&pNode, &key, 0);
        pNode->mValueA = value.a;
        pNode->mValueB = value.b;
        pNode->mValueC = value.c;
    }
    pReader->NextKey();
}

// @ 0x00de7330
bool SerializeFeedback(FeedbackWriter* pWriter, const wchar_t* pName, FeedbackMap* pMap)
{
    if (pMap->mCount == 0)
        return true;

    const wchar_t* pKeyName = pName ? pName : L"";
    pWriter->Begin(pKeyName);

    bool bOk = true;
    for (RbNode* pNode = pMap->mAnchor.mpRight; pNode != &pMap->mAnchor;
         pNode = RBTreeIncrement(pNode)) {
        if (bOk)
            bOk = WriteKeyValue(pWriter, 0, &((FeedbackNode*)pNode)->mpValue,
                                L"EA::ResourceMan::Key");
        else
            bOk = false;
    }

    pWriter->End(pKeyName);
    return bOk;
}

// @ 0x00de74c0
void FeedbackMap::EraseUintKey(uint32_t nKey)
{
    FeedbackNode* pNode = 0;
    FindUintKey(&pNode, nKey);
    if (pNode != (FeedbackNode*)&mAnchor) {
        --mCount;
        RbNode* pNext = RBTreeIncrement(pNode);
        (void)pNext;
        RBTreeErase(pNode, &mAnchor);
        operator_delete__(pNode);
    }

    void* pFound = mKeyTree.Find(&nKey, 0);
    if (pFound && pFound != &mKeyTree.mAnchor)
        RemoveKeyEntry(nKey, &((FeedbackNode*)pFound)->mpValue);
}

// @ 0x00de7530
void KeyCollector::CollectKeys(KeyVector* pOut)
{
    for (RbNode* pNode = mAnchor.mpRight; pNode != &mAnchor;
         pNode = RBTreeIncrement(pNode)) {
        Key* pKey = &((KeyListNode*)pNode)->mKey;
        Key* pDst = pOut->mpEnd;
        if (pDst < pOut->mpCap) {
            pOut->mpEnd = pDst + 1;
            if (pDst)
                *pDst = *pKey;
        } else {
            pOut->DoInsertKey(pOut->mpEnd, pKey);
        }
    }
}

// @ 0x00de7590
void* FeedbackMap::FindOrInsertKey(const Key* pKey)
{
    FeedbackNode* pNode = 0;
    FindKey(&pNode, pKey);

    bool bInsert = false;
    if (pNode == (FeedbackNode*)&mAnchor) {
        bInsert = true;
    } else if (pKey->a != pNode->mKey.a) {
        bInsert = pKey->a < pNode->mKey.a;
    } else if (pKey->c != pNode->mKey.c) {
        bInsert = pKey->c < pNode->mKey.c;
    } else {
        bInsert = pKey->b < pNode->mKey.b;
    }

    if (bInsert) {
        FeedbackNode* pNew = 0;
        InsertKey(&pNew, pNode, pKey, 0);
        pNode = pNew;
    }
    return &pNode->mpValue;
}

// @ 0x00de7630
Handler** IntMap::Slot(int* pKey)
{
    RbNode* pHeader = &mAnchor;
    InsertResult res;
    RbNode* pCandidate = pHeader;
    RbNode* pNode = mAnchor.mpParent;
    int nKey = *pKey;

    while (pNode) {
        if (((IntNode*)pNode)->mKey < nKey) {
            pNode = pNode->mpLeft;
        } else {
            pCandidate = pNode;
            pNode = pNode->mpRight;
        }
    }

    if (pCandidate != pHeader && nKey >= ((IntNode*)pCandidate)->mKey)
        return &((IntNode*)pCandidate)->mpValue;

    res.mpNode = pNode;
    res.mFlag = 0;
    Insert(&res.mpNode, pCandidate, &nKey, &res.mFlag);
    return &((IntNode*)res.mpNode)->mpValue;
}

// @ 0x00de7eb0
void SimTeardown::Teardown()
{
    FUN_00de4850(this);
    ReleaseSlot(mpC174, 4);
    if (FUN_00df5f40())
        ((GlobalMgr*)FUN_00df5f40())->Shutdown();
    if (mpServer) {
        void* pServer = mpServer;
        mpServer = 0;
        RemoveHandler(pServer, mpTarget, mpTable, mCount, mZero);
    }
    ReleaseSlot(mpC160, 4);
    ReleaseSlot(mpC164, 4);
    ReleaseSlot(mpC168, 4);
    ReleaseSlot(mpC16c, 4);
    ReleaseSlot(mpC170, 4);
    ReleaseSlot(mpC250, 8);
    for (RbNode* p = mHandlers.mAnchor.mpRight; p != &mHandlers.mAnchor;
         p = RBTreeIncrement(p)) {
        RefObj* pEffect = ((EffectNode*)p)->mpEffect;
        if (!pEffect) continue;
        pEffect->Stop();
        pEffect->s08(1);
    }
    ReleaseSlot(mpC198, 4);
    ReleaseSlot(mpC19c, 4);
    ReleaseSlot(mpC1a0, 4);
    ReleaseSlot(mpC1a4, 4);
    ReleaseSlot(mpC1a8, 4);
    for (RefObj** pp = mpVecBegin; pp != mpVecEnd; ++pp)
        if (*pp) (*pp)->Release();
    mpVecEnd = mpVecBegin;
    ReleaseSlot(mpC1b0, 4);
    for (int i = 0; i < 9; ++i)
        ReleaseSlot(mGrid[i], 4);
}
