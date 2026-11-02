// src/game/SPGonzago/_at_00de0000.cpp -- migrated from slice(s) s00de81b0, s00de7200, s00de6170, s00ddf990 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00de0000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern float gInterfaceBlend;
extern float gInterfaceAlpha;
extern float gInterfaceStep;
extern float gInterfaceSpeed;

// ---- items of slice s00ddf990 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cMethodTable {
    void* mSlots[0x40];
};
struct cDispatchObject {
    cMethodTable* mpMethods;                    // 0x00

    void* Call(int nSlot) {
        return ((void* (*)(void*))mpMethods->mSlots[nSlot >> 2])(this);
    }
    void* Call(int nSlot, uint32_t nArg1) {
        return ((void* (*)(void*, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1);
    }
    void* Call(int nSlot, uint32_t nArg1, uint32_t nArg2) {
        return ((void* (*)(void*, uint32_t, uint32_t))mpMethods->mSlots[nSlot >> 2])(this, nArg1, nArg2);
    }
    void* Call(int nSlot, void* pArg1) {
        return ((void* (*)(void*, void*))mpMethods->mSlots[nSlot >> 2])(this, pArg1);
    }
    void* Call(int nSlot, void* pArg1, int nArg2) {
        return ((void* (*)(void*, void*, int))mpMethods->mSlots[nSlot >> 2])(this, pArg1, nArg2);
    }
};
class cInterfaceState {
public:
    cInterfaceState(cDispatchObject* pTarget);
    ~cInterfaceState();
    bool ResetDefaults();
    void PushMatrix(uint32_t nKey);
    void UpdateTransition(unsigned int nElapsed, uint32_t nFlags);
    void UpdateFade(float fDelta);
    void UpdateSequence(int nDelta);
    void UpdateAlpha(int nDelta);
    void BeginSequence(uint8_t bFirst, uint8_t bSecond);
    void ResetSequence();
    void NotifySequence();
    bool IsIdle();

    uint32_t mpVftable;                         // 0x00
    int mnTimer;                                // 0x04
    uint8_t mPad08[0x18];                       // 0x08
    float mfValue20;                            // 0x20
    float mfValue24;                            // 0x24
    float mfValue28;                            // 0x28
    float mfValue2c;                            // 0x2c
    float mfValue30;                            // 0x30
    float mfTolerance;                          // 0x34
    float mfStart38;                            // 0x38
    float mfStart3c;                            // 0x3c
    uint8_t mbFlag40;                           // 0x40
    uint8_t mPad41[0x03];                       // 0x41
    float mfTo44;                               // 0x44
    float mfTo48;                               // 0x48
    float mfTo4c;                               // 0x4c
    float mfFrom50;                             // 0x50
    float mfFrom54;                             // 0x54
};
extern float gInterfaceBlend;
extern float gInterfaceAlpha;
extern float gInterfaceStep;
extern float gInterfaceSpeed;
extern uint8_t gInterfaceStarted;
void PostInterfaceMessage(uint32_t nId, int nValue);
// ---- items of slice s00ddf990 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern uint8_t gInterfaceStarted;

// ---- items of slice s00de6170 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned char DAT_016a0e08;
extern unsigned char DAT_016a140c;
extern unsigned char DAT_016a0e18;
extern unsigned int  DAT_016a1408;
class CFind70 {
public:
    void* find(void* out, void* key);
};
class CFind1c {
public:
    void* find(void* out, void* key);
};
class CInsert {
public:
    void* insert(void* out, void* key, unsigned int v);
};
void* __cdecl RBTreeIncrement(void* node);
void __cdecl RBTreeErase(void* a, void* b);
void __cdecl freeNode(void* p);
struct S00de6e80 {
    void FUN_00de6e80(int param_2);
};
struct ERBTree {
    void*         mpNode;    // +0x00
    void*         mpLeft;    // +0x04  (begin(); self-linked while empty)
    void*         mpRight;   // +0x08  (== &mpLeft while empty)
    void*         mpRoot;    // +0x0c  (root passed to DoNukeSubtree)
    union {
        unsigned char mFlag;     // +0x10  red/black flag byte
        unsigned int  mFlagWord; // +0x10  the whole word, zeroed by init passes
    };
    unsigned int  mCount;    // +0x14
    void*         mpPad18;   // +0x18
    void DoNukeSubtree(void* root);   // 0x9a9600
    void* find(void* out, void* key);                  // 0xe5c780
    void  insert(void* out, void* key, unsigned int);  // 0xa17a70
};
struct CRefCounted {
    virtual void V00();      // +0x00
    virtual void Release();  // +0x04
    virtual void Destroy();  // +0x08
};
struct CFindMixin {
    void* find(void* out, void* key);                 // 0xe5c780
    void  insert(void* out, void* key, unsigned int);  // 0xa17a70
};
struct CRecordStream {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
    virtual void* GetStream();   // +0x18
};
struct CRecordSource {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
    virtual void* GetStream();   // +0x18
    virtual void  Next();        // +0x1c
    virtual CRecordStream* GetSource();  // +0x20
    virtual void  V24();
};
void EA_IO_ReadInt32(void* stream, void* dst, int count, int separator);  // 0x93a780
struct CSimMinimapSink {
virtual void V00();
virtual void V04();
virtual void V08();
virtual void V0c();
virtual void V10();
virtual void V14();
virtual void V18();
virtual void V1c();
virtual void V20();
virtual void V24();
virtual void V28();
virtual void V2c();
virtual void V30();
virtual void V34();
virtual void V38();
    virtual void SetMinimap(int x, int y);      // +0x3c
};
struct CListNode {
    CListNode* mpNext;      // +0x00
};
struct CSimState {
    void*           mpVtbl00;   // +0x00
    CSimMinimapSink mSink;      // +0x04
    unsigned int    mPad08[6];  // +0x08 .. +0x1f
    CListNode       mListHead;  // +0x20 (self-linked circular list)
    unsigned int    mPad24[4];  // +0x24 .. +0x33
    unsigned int    mCount34;   // +0x34
    bool IsWorldActive(unsigned int* pKey);   // 0xb7d4f0
    void AttachPlanet(void* planet);          // 0xb7daf0
};
struct CPlanetModel {
    void UpdateMinimap(int x, int y, int z);    // 0xb8c330
};
struct CBigEditorObject {
    void Activate(char, const char* tag, char); // 0xe3e350
};
CSimState*       __cdecl FUN_00b3d360();        // 0xb3d360
CPlanetModel*    __cdecl SP_PlanetModel();      // 0xb3d350
CBigEditorObject* __cdecl FUN_00b3d410();       // 0xb3d410
struct CWString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
};
struct CSPUILayout {
    unsigned int mData[6];      // +0x00 .. +0x17
    void Construct();           // 0x810000
    void Destroy();             // 0x811fe0
};
struct CDe1d8Block {
    unsigned int mBegin;        // +0x00
    unsigned int mEnd;          // +0x04
    unsigned int mCap;          // +0x08
    void Destroy();             // 0x4b5440
};
void __cdecl EA_OperatorDelete(void* p);      // 0xf47380
__forceinline void FreeStringBuffer(wchar_t* begin, wchar_t* cap) {
    long bytes = (long)((char*)cap - (char*)begin);
    if (((bytes & ~1L) > 2) && begin != 0)
        EA_OperatorDelete(begin);
}
struct CGGEUserData {
    void*           mpVtbl00;      // +0x000
    void*           mpVtbl04;      // +0x004
    void*           mpVtbl08;      // +0x008
    void*           mpVtbl0c;      // +0x00c
    void*           mpHandler;     // +0x010 (EA::Messaging handler)
    void*           mHandlerArg0;  // +0x014
    void*           mHandlerArg1;  // +0x018
    void*           mHandlerArg2;  // +0x01c
    void*           mHandlerArg3;  // +0x020
    void*           mpHeap24;      // +0x024
    unsigned int    mZero28;       // +0x028
    unsigned int    mZero2c;       // +0x02c
    unsigned int    mPad30;        // +0x030
    unsigned int    mPad34;        // +0x034
    unsigned int    mZero38;       // +0x038
    ERBTree         mTree3c;       // +0x03c
    ERBTree         mTree58;       // +0x058
    ERBTree         mTree74;       // +0x074
    ERBTree         mTree90;       // +0x090
    ERBTree         mTreeAc;       // +0x0ac
    unsigned char   mFlagC8;       // +0x0c8
    unsigned char   mFlagC9;       // +0x0c9
    unsigned char   mPadCa[2];     // +0x0ca
    unsigned int    mZeroCc;       // +0x0cc
    CWString        mPath;         // +0x0d0
    unsigned int    mPadDc;        // +0x0dc
    unsigned int    mZeroE0;       // +0x0e0
    unsigned char   mFlagE4;       // +0x0e4
    unsigned char   mPadE5[3];     // +0x0e5
    unsigned int    mZeroE8;       // +0x0e8
    unsigned char   mByteEc;       // +0x0ec
    unsigned char   mByteEd;       // +0x0ed
    unsigned char   mByteEe;       // +0x0ee
    unsigned char   mByteEf;       // +0x0ef
    unsigned int    mZeroF0;       // +0x0f0
    unsigned char   mByteF4;       // +0x0f4
    unsigned char   mPadF5[3];     // +0x0f5
    unsigned int    mZeroF8;       // +0x0f8
    unsigned int    mZeroFc;       // +0x0fc
    unsigned char   mByte100;      // +0x100
    unsigned char   mByte101;      // +0x101
    unsigned char   mByte102;      // +0x102
    unsigned char   mFlag103;      // +0x103
    unsigned char   mByte104;      // +0x104
    unsigned char   mPad105[3];    // +0x105
    unsigned int    mZero108;      // +0x108
    unsigned int    mConst10c;     // +0x10c (initialised to 9)
    void*           mpHeap110;     // +0x110
    unsigned int    mZero114;      // +0x114
    unsigned int    mZero118;      // +0x118
    unsigned int    mPad11c;       // +0x11c
    unsigned int    mPad120;       // +0x120
    ERBTree         mTree124;      // +0x124
    unsigned int    mPad140;       // +0x140
    CSPUILayout     mLayout144;    // +0x144
    CRefCounted*    mpRef15c;      // +0x15c
    CRefCounted*    mpRef160;      // +0x160
    CRefCounted*    mpRef164;      // +0x164
    CRefCounted*    mpRef168;      // +0x168
    CRefCounted*    mpRef16c;      // +0x16c
    CRefCounted*    mpRef170;      // +0x170
    CRefCounted*    mpRef174;      // +0x174
    unsigned int    mZero178;      // +0x178
    unsigned char   mByte17c;      // +0x17c
    unsigned char   mPad17d[3];    // +0x17d
    unsigned int    mPad180;       // +0x180
    unsigned int    mZero184;      // +0x184
    unsigned int    mZero188;      // +0x188
    unsigned int    mZero18c;      // +0x18c
    unsigned int    mZero190;      // +0x190
    float           mZero194;      // +0x194
    CRefCounted*    mpRef198;      // +0x198
    CRefCounted*    mpRef19c;      // +0x19c
    CRefCounted*    mpRef1a0;      // +0x1a0
    CRefCounted*    mpRef1a4;      // +0x1a4
    CRefCounted*    mpRef1a8;      // +0x1a8
    CRefCounted*    mpRef1ac;      // +0x1ac
    CRefCounted*    mpRef1b0;      // +0x1b0
    CRefCounted*    mpRef1b4;      // +0x1b4
    CRefCounted*    mpRef1b8;      // +0x1b8
    CRefCounted*    mpRef1bc;      // +0x1bc
    CRefCounted*    mpRef1c0;      // +0x1c0
    CRefCounted*    mpRef1c4;      // +0x1c4
    CRefCounted*    mpRef1c8;      // +0x1c8
    CRefCounted*    mpRef1cc;      // +0x1cc
    CRefCounted*    mpRef1d0;      // +0x1d0
    CRefCounted*    mpRef1d4;      // +0x1d4
    CDe1d8Block     mBlock1d8;     // +0x1d8
    unsigned int    mPad1e4;       // +0x1e4
    unsigned int    mPad1e8;       // +0x1e8
    unsigned int    mZero1ec;      // +0x1ec
    unsigned char   mByte1f0;      // +0x1f0
    unsigned char   mByte1f1;      // +0x1f1
    unsigned char   mPad1f2[3];    // +0x1f2
    unsigned char   mByte1f5;      // +0x1f5
    unsigned char   mByte1f6;      // +0x1f6
    unsigned char   mPad1f7;       // +0x1f7
    unsigned int    mZero1f8;      // +0x1f8
    unsigned int    mZero1fc;      // +0x1fc
    unsigned int    mPad200[19];   // +0x200 .. +0x24b
    unsigned char   mByte24c;      // +0x24c
    unsigned char   mByte24d;      // +0x24d
    unsigned char   mPad24e[2];    // +0x24e
    void*           mpPtr250;      // +0x250
    ERBTree         mTree254;      // +0x254
    unsigned char   mByte270;      // +0x270
    unsigned char   mByte271;      // +0x271

    void FUN_00de6650(float x, float y);
};
struct CWorldEntry {          // node of the world tree at +0x3c
    void*        mpNode;      // +0x00
    void*        mpLeft;      // +0x04
    void*        mpRight;     // +0x08
    void*        mpPad0c;     // +0x0c
    unsigned int mId;         // +0x10 (property-list id)
    unsigned int mPad14;      // +0x14
    unsigned int mPad18;      // +0x18
    unsigned int mKey;        // +0x1c (rbtree key)
};
struct CPropertyList;
struct CGGEPlanet;
struct CBannerGroup;
struct CStarManager;
struct CPropertyList {
    void Construct();                           // 0xb8e180
    void AssignCopy(CPropertyList* src);        // 0xb8f030
    void SetKey(unsigned int* pKey, int flag);  // 0xb8dde0
    void SetId(unsigned int* pId);              // 0xb8da30
};
struct CGGEPlanet {
    void Construct();                           // 0xc725a0
    void SetProperties(CPropertyList* list);    // 0xc71750
};
struct CBannerGroup {
    CPropertyList* GetList(int index);          // 0xbbaa60
};
struct CStarManager {
    CBannerGroup* GetBannerGroup();             // 0xba6d80
};
CStarManager* __cdecl FUN_00b3d2a0(int);        // 0xb3d2a0
void* __cdecl EA_ZoneObjectNew(int size, const char* zone, int, int, int, int);        // 0xf473a0
void* __cdecl EA_ZoneObjectNewSim(int size, const char* zone, int, int, int, int);     // 0x926020
struct CFeedbackStore {
    ERBTree      mTree00;      // +0x00
    ERBTree      mTree1c;      // +0x1c
    unsigned int mPad38;       // +0x38
    ERBTree      mTree3c;      // +0x3c

    void FUN_00de6f20(unsigned int* pId, unsigned int* pKey);
    void FUN_00de7010();
};
struct CWorldNode {
    CWorldNode*  mpParent;   // +0x00
    CWorldNode*  mpLeft;     // +0x04
    CWorldNode*  mpRight;    // +0x08
    CWorldNode*  mpPad0c;    // +0x0c
    unsigned int mId;        // +0x10
    unsigned int mPartB;     // +0x14
    unsigned int mPartC;     // +0x18
};
struct CWorldKey {
    unsigned int mId;        // +0x00
    unsigned int mPartB;     // +0x04
    unsigned int mPartC;     // +0x08
};
inline bool WorldKeyLess(const CWorldNode* node, const CWorldKey* key) {
    if (node->mId != key->mId)
        return node->mId < key->mId;
    if (node->mPartC != key->mPartC)
        return node->mPartC < key->mPartC;
    return node->mPartB < key->mPartB;
}
inline bool WorldKeyLess(const CWorldKey* key, const CWorldNode* node) {
    if (key->mId != node->mId)
        return key->mId < node->mId;
    if (key->mPartC != node->mPartC)
        return key->mPartC < node->mPartC;
    return key->mPartB < node->mPartB;
}
void __cdecl RBTreeInsert(void* node, void* parent, void* anchor, int side); // 0x9216a0
struct CWorldContainer {
    ERBTree tree;       // +0x00

    void* NewNode(CWorldKey* key);                                        // 0xde4e20
    void* InsertAfter(void** out, CWorldNode* pos, CWorldKey* key, int);  // 0xde5740
    void* InsertUnique(void** out, CWorldKey* key, int);                  // 0xde5f60
    void* Insert(void** out, CWorldNode* pos, CWorldKey* key, unsigned int reserved);
};
struct CEastlString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08

    void RangeInitialize(const wchar_t* text);                 // 0x579a90
    void AllocateSelf(int capacity);                           // 0x429760
    void assign(const wchar_t* begin, const wchar_t* end);     // 0x423650
    void AssignFrom(const CEastlString* other);
};
void __cdecl EA_Memcpy(void* dst, const void* src, unsigned int size);  // 0x11e0744
CEastlString* __cdecl PathPick(CEastlString* out, CEastlString* in, CEastlString* dir); // 0x688f00
void CEastlString::AssignFrom(const CEastlString* other) {
    assign(other->mpBegin, other->mpEnd);
}
struct ISaveArea {
    virtual void  V00();
    virtual void  V04();
    virtual void  V08();
    virtual void  V0c();
    virtual void  V10();
    virtual void  V14();
    virtual void  V18();
    virtual void  V1c();
    virtual void  V20();
    virtual void  V24();
    virtual wchar_t* GetSavePath();    // +0x28
};
ISaveArea* __cdecl SP_GetSaveArea(int tag);      // 0x6b1f90
struct CFileSink {
    virtual void AddRef();                     // +0x00
    virtual void Release();                    // +0x04
};
struct CDatabasePackedFile {
    void*     mPad00;                          // +0x00
    CFileSink mSink;                           // +0x04
    void Construct(const wchar_t* path, void* alloc, void* alloc2);   // 0x8d9f80
};
struct CDbBase {
    virtual void B00();                        // +0x00
    virtual void B04();                        // +0x04
virtual void B08();
virtual void B0c();
virtual void B10();
virtual void B14();
virtual void B18();
virtual void B1c();
virtual void B20();
virtual void B24();
virtual void B28();
virtual void B2c();
virtual void B30();
virtual void B34();
virtual void B38();
    virtual bool Init(int flags, int arg);     // +0x3c
};
struct CDbStream {
    virtual void S00();                        // +0x00
    virtual void S04();                        // +0x04
    virtual void S08();                        // +0x08
virtual void S0c();
virtual void S10();
virtual void S14();
virtual void S18();
    virtual void Advance();                    // +0x1c
virtual void S20();
virtual void S24();
virtual void S28();
    virtual void SetPath(const wchar_t* path); // +0x2c
};
struct CObjectDatabase {
    CDbBase   mBase;                           // +0x00
    CDbStream mStream;                         // +0x04
    void Construct(CDatabasePackedFile* file); // 0x69fa60
};
struct C3Record {
    void*       mpField00;   // +0x00
    void*       mpField04;   // +0x04
    void*       mpPayload;   // +0x08
    void*       mpField0c;   // +0x0c
    C3Record* Ctor(void* db, void* a, void* b, void* c);   // 0x693cd0
    void      Destroy();                                   // 0x693900
};
struct CVarListSerializer {
    unsigned char mStorage[0x48];                            // +0x00..+0x47
    void Construct(void* area, const void* name, int tag);   // 0x692f90
    void Read(void* arg);                                    // 0x693e10
};
// ---- items of slice s00de6170 end

// ---- items of slice s00de7200 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char* kGUI_PanelIDs;                        // 0x016a1344
typedef unsigned int  uint;
typedef unsigned char uchar;
typedef unsigned long long u64;
void* operator new(unsigned int, const char*, int, int, int, int);  // 0x00F473A0 (EA allocator)
struct Handler {
    virtual int  AddRef();
    virtual int  Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual void Init();   // 0x2c
};
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
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
                  virtual void v8();
                  virtual bool Get(uint id, Prop** out); };   // 0x24
extern PropList* sAppProperties;                  // 0x015fd918
struct MsgServer { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3();
virtual void m4();
virtual void m5();
virtual void m6();
virtual void m7();
                   virtual void m8();
                   virtual void AddListener(void* target, uint msg); };   // 0x24
struct LayerMgr  { virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3();
virtual void l4();
virtual void l5();
virtual void l6();
virtual void l7();
virtual void l8();
virtual void l9();
virtual void l10();
                   virtual void Set(uint id, int v); };                   // 0x2c
MsgServer* SP_MessageServer();                    // 0x0067dcc0
LayerMgr*  SP_LayerManager();                     // 0x0067cb20
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
namespace __equiv_ann1 {
struct H0 {
    H0();   // 0x00dea500 (equiv t3)
};
}
namespace __equiv_ann1 {
struct H11 {
    H11();   // 0x00de3370 (equiv t3)
};
}
namespace __equiv_ann1 {
struct H12 {
    H12();   // 0x00deb670 (equiv t3)
};
}
namespace __equiv_ann1 {
struct H13 {
    H13();   // 0x00dfb9c0 (equiv t3)
};
}
namespace __equiv_ann1 {
struct H2 {
    H2();   // 0x00e008e0 (equiv t3)
};
}
namespace __equiv_ann1 {
struct H3 {
    H3();   // 0x00de2d00 (equiv t3)
};
}
namespace __equiv_ann1 {
struct H4 {
    H4();   // 0x00dee320 (equiv t3)
};
}
namespace __equiv_ann1 {
struct HMap {
    void Slot();   // 0x00de7630 (equiv t3)
};
}
namespace __equiv_ann1 {
struct HandlerBase {
    HandlerBase();   // 0x00e00630 (equiv t3)
};
}
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
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
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
    void* Find(void** ppOut, void* pKey);           // 0x00a21dc0
};
struct FeedbackMap {
    uint32_t  mPad00;                               // +0x00
    RbNode    mAnchor;                              // +0x04  (begin = mpRight, end = &mAnchor)
    uint32_t  mCount;                               // +0x14
    uint8_t   mPad18[0x70 - 0x18];
    KeyRbTree mKeyTree;                             // +0x70
    void  FindUintKey(FeedbackNode** ppNode, const uint32_t* pKey);  // 0x00e5c780 (eastl rbtree find)
    void  FindKey(FeedbackNode** ppNode, const Key* pKey);           // 0x00c7f560
    void* FindOrInsertKey(const Key* pKey);                          // 0x00de7590
    void  EraseUintKey(const uint32_t* pKey);                        // 0x00de74c0
    void  RemoveKeyEntry(uint32_t nKey, void* pValue);               // 0x00de6f20
    void  InsertKey(FeedbackNode** ppNode, RbNode* pWhere, const Key* pKey, RbNode* pWhere2);  // 0x00de6900
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
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
    virtual void* GetStream();                      // +0x18
};
struct Reader {
virtual void s00();
virtual void s01();
virtual void s02();
virtual void s03();
virtual void s04();
virtual void s05();
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
// ---- items of slice s00de7200 end

// ---- items of slice s00de81b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_0067cac0();   // 0x67cac0  SP::UIHints
extern "C" void* __cdecl FUN_0067cad0();   // 0x67cad0  bounding-box manager
extern "C" void* __cdecl FUN_0067cb10();   // 0x67cb10  SP::MovieSystem
extern "C" void* __cdecl FUN_0067dcc0();   // 0x67dcc0  SP::MessageServer
extern "C" void* __cdecl FUN_0067dd10();   // 0x67dd10  SP::App
extern "C" void* __cdecl FUN_0067dd50();   // 0x67dd50
extern "C" void* __cdecl FUN_0067ddd0();   // 0x67ddd0  SP::EffectsManager
extern "C" void* __cdecl FUN_00b3d2a0();   // 0xb3d2a0  SP::StarManager
extern "C" void* __cdecl FUN_00b3d340();   // 0xb3d340  galaxy save/state object
extern "C" void* __cdecl FUN_00dd9190();   // 0xdd9190  CB object
extern "C" int   __cdecl FUN_00401030();                          // 0x401030  ?GetSetting3@@YAHXZ
extern "C" void* __cdecl FUN_0042f530(void* a, void* b, void* c); // 0x42f530  copy/erase helper
extern "C" void  __cdecl FUN_00804ed0(void* a, void* b);          // 0x804ed0
extern "C" void  __cdecl FUN_00809db0(void* target, void* msg);   // 0x809db0  UI::CalloutMessageBox
extern "C" bool  __cdecl FUN_008d3200(int a, int b);              // 0x8d3200
extern "C" void* __cdecl FUN_00921580(void* node);                // 0x921580  RBTreeIncrement
extern "C" void  __cdecl FUN_00ddc8d0();                          // 0xddc8d0  final teardown
extern "C" void  __fastcall FUN_0067c3b0(void* self, int, int hint, char flag);      // 0x67c3b0  UIHints::Next
extern "C" void  __fastcall FUN_007c4010(void* self, int, uint32_t* out);            // 0x7c4010  cViewer::GetRect
extern "C" void  __fastcall FUN_0080dc50(void* self, int, void* arg);                // 0x80dc50
extern "C" void* __fastcall FUN_008105b0(void* self, int, uint32_t id, int flag);    // 0x8105b0  cSPUILayout::FindWindowByID
extern "C" void  __fastcall FUN_00811ad0(void* self, int, int flag);                 // 0x811ad0  cSPUILayout::Shutdown
extern "C" void  __fastcall FUN_00b96600(void* self, int, void* pos, const void* key); // 0xb96600  SPVector::DoInsertKey4
extern "C" void  __fastcall FUN_00bb7620(void* self, int);                          // 0xbb7620
extern "C" void  __fastcall FUN_00dda3b0(void* self, int, char v);                  // 0xdda3b0  CB::m3b0
extern "C" void  __fastcall FUN_00ddc6d0(void* self, int, int ms);                  // 0xddc6d0
extern "C" float __fastcall FUN_00dde5c0(void* self, int);                          // 0xdde5c0
extern "C" void  __fastcall FUN_00de44f0(void* self, int, float a, float b, int c); // 0xde44f0
extern "C" void  __fastcall FUN_00de4910(void* self, int);                          // 0xde4910
extern "C" void  __fastcall FUN_00de5470(void* self, int, bool flag);               // 0xde5470  ShowGalaxy
extern "C" void  __fastcall FUN_00de6650(void* self, int, float a, float b);        // 0xde6650
extern "C" void* __fastcall FUN_00de7630(void* self, int, int* key);                // 0xde7630  IntMap::Slot
extern "C" void  __fastcall FUN_00df6db0(void* self, int, int state);               // 0xdf6db0  cGameUIData::SetUIState
extern "C" void  __fastcall FUN_00df9510(void* self, int);                          // 0xdf9510
extern "C" void* __fastcall FUN_00e012b0(void* self, int, uint32_t id);             // 0xe012b0  cSPUIGlobalUI::FindWindowByID
extern uint8_t  g_CBEnabled;      // 0x16a1348
extern uint8_t  g_CBIndex;        // 0x16a0fa8
extern float    g_fAbsThreshold;  // 0x16a0f68
extern uint8_t  g_bSomeFlag;      // 0x16a0e78
extern void*    kGUI_PanelIDs_s00de_81b0;    // 0x16a1344
static const float kfMsScale = 1000.0f;   // 0x13ec5b4
static const float kfHalf    = 0.5f;      // 0x1471064
typedef void (__thiscall* VFn0)(void*);
typedef void (__thiscall* VFn1)(void*, int);
typedef char (__thiscall* VFnC)(void*);
typedef void* (__thiscall* VFnP)(void*);
static inline void** VT(void* o) { return *(void***)o; }
static inline void  VCall0(void* o, int slot) { ((VFn0)VT(o)[slot])(o); }
static inline void  VCall1(void* o, int slot, int a) { ((VFn1)VT(o)[slot])(o, a); }
static inline char  VCallC(void* o, int slot) { return ((VFnC)VT(o)[slot])(o); }
static inline void* VCallP(void* o, int slot) { return ((VFnP)VT(o)[slot])(o); }
static inline void ReleaseSlot_s00de_81b0(void** slot)
{
    void* p = *slot;
    if (p) {
        *slot = 0;
        VCall0(p, 1);                 // vt +0x04
    }
}
static inline void ReleaseSlotChecked(void** slot)
{
    void* p = *slot;
    if (p && VCallC(p, 4))            // vt +0x10
        VCall1(p, 3, 1);              // vt +0x0c(1)
    p = *slot;
    if (p) {
        *slot = 0;
        VCall0(p, 1);                 // vt +0x04
    }
}
struct GalaxyEntry
{
    void**    vtable;             // 0x000
    uint8_t   pad004[4];          // 0x004
    void*     mpMessageTarget;    // 0x008  opaque handle broadcast to
    void*     mpCalloutTarget;    // 0x00c  opaque handle used by CalloutMessageBox
    uint8_t   pad010[0x28];       // 0x010..0x037
    void*     mpModeTarget;       // 0x038  refcounted current mode/effects world
    uint8_t   pad03c[0x8c];       // 0x03c..0x0c7
    uint8_t   mbC8;               // 0x0c8
    uint8_t   mbC9;               // 0x0c9
    uint8_t   pad0ca[2];          // 0x0ca..0x0cb
    void*     mpBoundingBox;      // 0x0cc
    uint8_t   pad0d0[0x2c];       // 0x0d0..0x0fb
    void*     mpUIData;           // 0x0fc  (UI data object; +0xb8 holds the state owner)
    uint8_t   mb100;              // 0x100
    uint8_t   pad101[2];          // 0x101..0x102
    uint8_t   mb103;              // 0x103  "refresh icons" request
    uint8_t   pad104[4];          // 0x104..0x107
    int32_t   mn108;              // 0x108  current mode
    int32_t   mn10c;              // 0x10c  requested mode
    uint32_t* mpVecBegin;         // 0x110  mode history vector
    uint32_t* mpVecEnd;           // 0x114
    uint32_t* mpVecCap;           // 0x118
    uint8_t   pad11c[8];          // 0x11c..0x123
    void*     mpMapRoot;          // 0x124  int -> object map (root)
    void*     mpMapSentinel;      // 0x128  map sentinel / head link
    void*     mpMapFirst;         // 0x12c  first map node
    void*     mpMapLast;          // 0x130
    uint8_t   pad134[0x0c];       // 0x134..0x13f
    uint8_t   mb140;              // 0x140
    uint8_t   pad141[3];          // 0x141..0x143
    uint8_t   mLayout[0x18];      // 0x144  embedded cSPUILayout
    void*     mpEffectsWorld;     // 0x15c
    void*     mp160;              // 0x160
    void*     mp164;              // 0x164
    void*     mp168;              // 0x168
    void*     mp16c;              // 0x16c
    void*     mp170;              // 0x170
    uint8_t   pad174[0x10];       // 0x174..0x183
    void*     mp184;              // 0x184  window host
    uint8_t   pad188[0x10];       // 0x188..0x197
    void*     mp198;              // 0x198
    void*     mp19c;              // 0x19c
    void*     mp1a0;              // 0x1a0
    void*     mp1a4;              // 0x1a4
    void*     mp1a8;              // 0x1a8
    uint8_t   pad1ac[4];          // 0x1ac..0x1af
    void*     mp1b0;              // 0x1b0
    uint8_t   pad1b4[0x24];       // 0x1b4..0x1d7
    void**    mpEffectVecBegin;   // 0x1d8  AutoRefCount<cIVisualEffect> vector
    void**    mpEffectVecEnd;     // 0x1dc
    uint8_t   pad1e0[0x0c];       // 0x1e0..0x1eb
    int32_t   mn1ec;              // 0x1ec  number of selectable modes
    uint8_t   pad1f0[6];          // 0x1f0..0x1f5
    uint8_t   mb1f6;              // 0x1f6  "drop star manager overlay" request
};
// ---- items of slice s00de81b0 end

// @ 0x00de00e0
void cInterfaceState::UpdateSequence(int nDelta)
{
    mnTimer = mnTimer + nDelta;
    float fElapsed = (float)mnTimer;
    if (mnTimer < 0)
        fElapsed = fElapsed + 4294967296.0f;
    float fDuration = gInterfaceStep + gInterfaceStep;
    fElapsed = fElapsed / (fDuration * 1000.0f);

    if (mfValue24 == 0.0f && 1.0f < fElapsed) {
        mfValue24 = 1.0f;
        PostInterfaceMessage(0x7be7df5, 2);
        fElapsed = 1.0f;
    }
    if (mfValue24 == 1.0f)
        fElapsed = 1.0f;
    if (mfValue24 == 2.0f) {
        if (1.0f < fElapsed) {
            PostInterfaceMessage(0x7be7df5, 4);
            gInterfaceStarted = 0;
            fElapsed = 1.0f;
        }
        fElapsed = 1.0f - fElapsed;
    }

    float fScaled = fElapsed * 2.0f;
    float fCurve;
    if (1.0f <= fScaled) {
        float fInverse = (2.0f - fScaled) * gInterfaceStep;
        fCurve = 1.0f - (fInverse * (gInterfaceStep * fInverse)) * 0.5f;
    } else {
        float fInverse = gInterfaceStep * fScaled;
        fCurve = (fInverse * (gInterfaceStep * fInverse)) * 0.5f;
    }

    if (mfValue24 == 2.0f) {
        if (gInterfaceBlend <= 1.0f - fCurve) {
            if (mbFlag40 == 0) {
                mbFlag40 = 1;
                PostInterfaceMessage(0x7be7df5, 5);
            }
        } else {
            mbFlag40 = 0;
        }
    }
    if (mfValue24 == 0.0f) {
        if (gInterfaceBlend <= fCurve) {
            if (mbFlag40 == 0) {
                mbFlag40 = 1;
                PostInterfaceMessage(0x7be7df5, 1);
            }
        } else {
            mbFlag40 = 0;
        }
    }

    if (mfValue24 != 1.0f) {
        float fRamp = fCurve * 3.0f;
        if (fRamp <= 0.0f)
            fRamp = 0.0f;
        if (1.0f <= fRamp)
            fRamp = 1.0f;
        mfValue20 = (mfValue28 - mfValue24) * fCurve + mfValue24;
        mfValue30 = (-gInterfaceAlpha - mfTolerance) * fRamp + mfTolerance;
        mfStart38 = (1.0f - fCurve) * mfValue30;
    }
}

// @ 0x00de0450
void cInterfaceState::UpdateAlpha(int nDelta)
{
    mnTimer = mnTimer + nDelta;
    float fElapsed = (float)mnTimer;
    if (mnTimer < 0)
        fElapsed = fElapsed + 4294967296.0f;
    float fDuration = gInterfaceSpeed + gInterfaceSpeed;
    fElapsed = fElapsed / (fDuration * 1000.0f);

    if (mfValue24 == 0.0f && 1.0f < fElapsed) {
        mfValue24 = 1.0f;
        PostInterfaceMessage(0x7c3cd3d, 2);
        fElapsed = 1.0f;
    }
    if (mfValue24 == 1.0f)
        fElapsed = 1.0f;
    if (mfValue24 == 2.0f) {
        if (1.0f < fElapsed) {
            PostInterfaceMessage(0x7c3cd3d, 4);
            gInterfaceStarted = 0;
            fElapsed = 1.0f;
        }
        fElapsed = 1.0f - fElapsed;
    }

    float fScaled = fElapsed * 2.0f;
    float fCurve;
    if (1.0f <= fScaled) {
        float fInverse = (2.0f - fScaled) * gInterfaceSpeed;
        fCurve = 1.0f - (fInverse * (gInterfaceSpeed * fInverse)) * 0.5f;
    } else {
        float fInverse = gInterfaceSpeed * fScaled;
        fCurve = (fInverse * (gInterfaceSpeed * fInverse)) * 0.5f;
    }

    mfValue20 = (mfValue28 - mfValue24) * fCurve + mfValue24;
    mfValue30 = (gInterfaceAlpha - mfTolerance) * fCurve + mfTolerance;
    mfStart38 = (mfValue2c - mfValue30) * fCurve + mfValue30;
}

// @ 0x00de63e0
void __fastcall FUN_00de63e0(void* owner)
{
    CEastlString fileName;
    CEastlString savePath;
    CEastlString fullPath;

    fileName.mpBegin = 0;
    fileName.mpEnd = 0;
    fileName.mpCap = 0;
    fileName.RangeInitialize(L"GGEUserData.dat");

    ISaveArea* area = SP_GetSaveArea(0x4729a47);
    const wchar_t* rawSavePath = area->GetSavePath();

    savePath.mpBegin = 0;
    savePath.mpEnd = 0;
    savePath.mpCap = 0;
    savePath.RangeInitialize(rawSavePath);

    const wchar_t* saveBegin = savePath.mpBegin;
    int saveLen = (int)((char*)savePath.mpEnd - (char*)saveBegin) >> 1;

    fullPath.mpBegin = 0;
    fullPath.mpEnd = 0;
    fullPath.mpCap = 0;
    fullPath.AllocateSelf(saveLen + 1);
    wchar_t* fullBegin = fullPath.mpBegin;
    EA_Memcpy(fullBegin, saveBegin, (unsigned int)saveLen * 2);
    fullPath.mpEnd = fullBegin + saveLen;
    *fullPath.mpEnd = 0;

    // One frame slot serves two purposes in the original: PathPick's result
    // string, then the C3 record built inside the "initialised" branch.
    union {
        CEastlString mPicked;    // +0x00, 12 bytes
        C3Record     mRecord;    // +0x00, 16 bytes
    } scratch;

    CEastlString* picked = PathPick(&scratch.mPicked, &fullPath, &fileName);
    if (picked != &fullPath)
        fullPath.AssignFrom(picked);

    FreeStringBuffer(scratch.mPicked.mpBegin, scratch.mPicked.mpCap);

    CDatabasePackedFile* file = 0;
    void* fileMem = EA_ZoneObjectNewSim(0x388, "Simulator", 0, 0, 0, 0);
    if (fileMem != 0) {
        ((CDatabasePackedFile*)fileMem)->Construct(fullPath.mpBegin, 0, 0);
        file = (CDatabasePackedFile*)fileMem;
        if (file != 0)
            file->mSink.AddRef();
    }

    CObjectDatabase* db = 0;
    void* dbMem = EA_ZoneObjectNewSim(0x24, "Simulator", 0, 0, 0, 0);
    if (dbMem != 0) {
        ((CObjectDatabase*)dbMem)->Construct(file);
        db = (CObjectDatabase*)dbMem;
        if (db != 0)
            db->mBase.B00();
    }

    db->mStream.S04();
    db->mStream.SetPath(fullPath.mpBegin);

    if (db->mBase.Init(1, 0)) {
        CVarListSerializer serializer;
        scratch.mRecord.Ctor(db, (void*)0x1897c18, (void*)0x1897c18, (void*)0x1897c18);
        serializer.Construct(owner, (const void*)0x15a38b8, 0x1a80d26);
        serializer.Read(scratch.mRecord.mpPayload);
        db->mStream.Advance();
        scratch.mRecord.Destroy();
    }

    db->mStream.S08();
    db->mBase.B04();

    if (file != 0)
        file->mSink.Release();

    FreeStringBuffer(fullPath.mpBegin, fullPath.mpCap);
    FreeStringBuffer(savePath.mpBegin, savePath.mpCap);
    FreeStringBuffer(fileName.mpBegin, fileName.mpCap);
}

// @ 0x00de6650
void CGGEUserData::FUN_00de6650(float x, float y)
{
    int roundedY = (int)(y * 1000.0f);
    int roundedX = (int)(x * 1000.0f);
    CSimState* sim = FUN_00b3d360();
    if (sim->mListHead.mpNext == &sim->mListHead && sim->mCount34 == 0) {
        if (DAT_016a140c == 0) {
            mTree58.DoNukeSubtree(mTree58.mpRoot);
            mTree58.mpLeft = &mTree58.mpLeft;
            mTree58.mpRight = &mTree58.mpLeft;
            mTree58.mpRoot = 0;
            mTree58.mFlag = 0;
            mTree58.mCount = 0;
        } else {
            mTree58.DoNukeSubtree(mTree58.mpRoot);
            mTree58.mpLeft = &mTree58.mpLeft;
            mTree58.mpRight = &mTree58.mpLeft;
            mTree58.mpRoot = 0;
            mTree58.mFlag = 0;
            mTree58.mCount = 0;
            DAT_016a140c = 0;
            if (DAT_016a0e18 != 0)
                FUN_00b3d410()->Activate(0, (const char*)0x1654c05, 0);
        }
    } else if (DAT_016a0e08 == 0) {
        if (DAT_016a140c != 0) {
            DAT_016a140c = 0;
            if (DAT_016a0e18 != 0)
                FUN_00b3d410()->Activate(0, (const char*)0x2ccd1d2, 0);
        }
    } else {
        DAT_016a140c = 1;
        CSimState* counted = FUN_00b3d360();
        unsigned int count = 0;
        for (CListNode* n = counted->mListHead.mpNext; n != &counted->mListHead; n = n->mpNext)
            count++;
        CSimState* target = FUN_00b3d360();
        target->mSink.SetMinimap(roundedY, roundedX);
        SP_PlanetModel()->UpdateMinimap(roundedY, 0, 0);
        if (count != DAT_016a1408)
            DAT_016a1408 = count;
    }
}

// @ 0x00de67b0
int* __fastcall FUN_00de67b0(int param_1)
{
    int zero = 0;
    int* p = (int*)param_1;
    p[2] = zero;
    p[3] = zero;
    p[4] = zero;
    p[3] = zero;
    *(char*)(param_1 + 0x10) = (char)zero;
    p[5] = zero;
    int* iVar1 = (int*)(param_1 + 4);
    *iVar1 = (int)iVar1;
    p[2] = (int)iVar1;
    p[9] = zero;
    p[10] = zero;
    p[0xb] = zero;
    p[10] = zero;
    *(char*)(param_1 + 0x2c) = (char)zero;
    p[0xc] = zero;
    iVar1 = (int*)(param_1 + 0x20);
    *iVar1 = (int)iVar1;
    p[9] = (int)iVar1;
    p[0x10] = zero;
    p[0x11] = zero;
    p[0x12] = zero;
    p[0x11] = zero;
    *(char*)(param_1 + 0x48) = (char)zero;
    p[0x13] = zero;
    iVar1 = (int*)(param_1 + 0x3c);
    *iVar1 = (int)iVar1;
    p[0x10] = (int)iVar1;
    p[0x17] = zero;
    p[0x18] = zero;
    p[0x19] = zero;
    iVar1 = (int*)(param_1 + 0x58);
    *iVar1 = (int)iVar1;
    p[0x17] = (int)iVar1;
    p[0x18] = zero;
    *(char*)(param_1 + 0x64) = (char)zero;
    p[0x1a] = zero;
    iVar1 = (int*)(param_1 + 0x74);
    iVar1[1] = zero;
    iVar1[2] = zero;
    iVar1[3] = zero;
    *iVar1 = (int)iVar1;
    p[0x1e] = (int)iVar1;
    p[0x1f] = zero;
    *(char*)(param_1 + 0x80) = (char)zero;
    p[0x21] = zero;
    return p;
}

// @ 0x00de6840
void __cdecl FUN_00de6840(CRecordSource* reader, ERBTree* tree)
{
    unsigned int count = 0;
    unsigned int value;
    void* iter[2];
    unsigned int i;
    union { unsigned int mDword; unsigned char mByte; } flag;

    tree->DoNukeSubtree(tree->mpRoot);
    tree->mpLeft = &tree->mpLeft;
    tree->mpRight = &tree->mpLeft;
    tree->mpRoot = 0;
    tree->mFlag = 0;
    tree->mCount = 0;
    void* stream = reader->GetSource()->GetStream();
    EA_IO_ReadInt32(stream, &count, 1, 0);
    i = 0;
    while (i < count) {
        stream = reader->GetSource()->GetStream();
        EA_IO_ReadInt32(stream, &value, 1, 0);
        reader->Next();
        flag.mByte = 0;
        ((CFindMixin*)tree)->insert(iter, &value, flag.mDword);
        i++;
    }
    reader->Next();
}

// @ 0x00de6900
void* CWorldContainer::Insert(void** out, CWorldNode* pos, CWorldKey* key, unsigned int)
{
    if (pos == (CWorldNode*)tree.mpLeft || pos == (CWorldNode*)&tree.mpLeft) {
        if (tree.mCount != 0) {
            CWorldNode* root = (CWorldNode*)tree.mpLeft;
            if (WorldKeyLess(root, key)) {
                InsertAfter(out, root, key, 0);
                return out;
            }
        }
        void* iter[2];
        union { unsigned int mDword; unsigned char mByte; } flag;
        flag.mByte = 0;
        InsertUnique(iter, key, flag.mDword);
        *out = iter[0];
        return out;
    }

    CWorldNode* next = (CWorldNode*)RBTreeIncrement(pos);
    if (WorldKeyLess(pos, key) && WorldKeyLess(key, next)) {
        if (pos->mpParent != 0) {
            void* node = NewNode(key);
            RBTreeInsert(node, next, &tree.mpLeft, 0);
            tree.mCount++;
            *out = node;
            return out;
        }
        InsertAfter(out, pos, key, 0);
        return out;
    }

    void* iter[2];
    union { unsigned int mDword; unsigned char mByte; } flag;
    flag.mByte = 0;
    InsertUnique(iter, key, flag.mDword);
    *out = iter[0];
    return out;
}

// @ 0x00de6be0
CGGEUserData* __fastcall FUN_00de6be0(CGGEUserData* p)
{
    // Known vtables/labels installed by the original sequence.
    p->mpVtbl04 = (void*)0x14426a0;
    p->mpVtbl08 = (void*)0x13eb384;
    p->mpVtbl00 = (void*)0x147e0fc;
    p->mpVtbl04 = (void*)0x147e0e0;
    p->mpVtbl08 = (void*)0x147e0d0;
    p->mpVtbl0c = (void*)0x147e0c4;

    p->mpHandler = 0;
    p->mHandlerArg0 = 0;
    p->mHandlerArg1 = 0;
    p->mHandlerArg2 = 0;
    p->mHandlerArg3 = 0;
    p->mpHeap24 = 0;
    p->mZero28 = 0;
    p->mZero2c = 0;
    p->mZero38 = 0;

    FUN_00de67b0((int)(unsigned long)&p->mTree3c);

    p->mFlagC9 = 0;
    p->mZeroCc = 0;
    p->mFlagC8 = 1;
    p->mPath.mpCap = (wchar_t*)0x1667bae;
    p->mPath.mpBegin = (wchar_t*)0x1667bac;   // eastl::gEmptyString16
    p->mPath.mpEnd = (wchar_t*)0x1667bac;
    p->mFlagE4 = 1;
    p->mFlag103 = 1;
    p->mZeroE0 = 0;
    p->mZeroE8 = 0;
    p->mByteEc = 0;
    p->mByteEd = 0;
    p->mByteEe = 0;
    p->mByteEf = 0;
    p->mZeroF0 = 0;
    p->mByteF4 = 0;
    p->mZeroF8 = 0;
    p->mZeroFc = 0;
    p->mByte100 = 0;
    p->mByte101 = 0;
    p->mByte102 = 0;
    p->mByte104 = 0;
    p->mZero108 = 0;
    p->mConst10c = 9;
    p->mpHeap110 = 0;
    p->mZero114 = 0;
    p->mZero118 = 0;

    // Control block at +0x124: cleared and then self-linked (both phases kept).
    // The leading word is left untouched by the original; the clear pass zeroes
    // the flag word as a whole, the link pass only its low byte.
    p->mTree124.mpRight = 0;
    p->mTree124.mpRoot = 0;
    p->mTree124.mFlagWord = 0;
    p->mTree124.mpRight = &p->mTree124.mpLeft;
    p->mTree124.mpRoot = 0;
    p->mTree124.mFlag = 0;
    p->mTree124.mCount = 0;
    p->mTree124.mpLeft = &p->mTree124.mpLeft;

    p->mLayout144.Construct();

    p->mpRef15c = 0;
    p->mpRef160 = 0;
    p->mpRef164 = 0;
    p->mpRef168 = 0;
    p->mpRef16c = 0;
    p->mpRef170 = 0;
    p->mpRef174 = 0;
    p->mZero178 = 0;
    p->mByte17c = 0;
    p->mZero184 = 0;
    p->mZero188 = 0;
    p->mZero18c = 0;
    p->mZero190 = 0;
    p->mZero194 = 0.0f;
    p->mpRef198 = 0;
    p->mpRef19c = 0;
    p->mpRef1a0 = 0;
    p->mpRef1a4 = 0;
    p->mpRef1a8 = 0;
    p->mpRef1ac = 0;
    p->mpRef1b0 = 0;
    p->mpRef1b4 = 0;
    p->mpRef1b8 = 0;
    p->mpRef1bc = 0;
    p->mpRef1c0 = 0;
    p->mpRef1c4 = 0;
    p->mpRef1c8 = 0;
    p->mpRef1cc = 0;
    p->mpRef1d0 = 0;
    p->mpRef1d4 = 0;
    p->mBlock1d8.mBegin = 0;
    p->mBlock1d8.mEnd = 0;
    p->mBlock1d8.mCap = 0;
    p->mZero1ec = 0;
    p->mByte1f0 = 0;
    p->mByte1f1 = 0;
    p->mByte1f5 = 0;
    p->mByte1f6 = 0;
    p->mZero1f8 = 0;
    p->mZero1fc = 0;
    p->mByte24c = 0;
    p->mByte24d = 0;
    p->mpPtr250 = 0;

    // Control block at +0x254: same cleared-then-self-linked shape.
    p->mTree254.mpRight = 0;
    p->mTree254.mpRoot = 0;
    p->mTree254.mFlagWord = 0;
    p->mTree254.mpRight = &p->mTree254.mpLeft;
    p->mTree254.mpRoot = 0;
    p->mTree254.mFlag = 0;
    p->mTree254.mCount = 0;
    p->mTree254.mpLeft = &p->mTree254.mpLeft;

    p->mByte270 = 0;
    p->mByte271 = 0;
    return p;
}

// @ 0x00de6e80
void S00de6e80::FUN_00de6e80(int param_2)
{
    void* out[2];
    struct Key {
        unsigned int id;
        unsigned int h;
        unsigned int f;
    } key;
    key.id = (unsigned int)param_2;
    key.h = 0x011989b7u;
    key.f = 0x4084a100u;
    int* p = (int*)((CFind70*)((char*)this + 0x70))->find(out, &key);
    if (*p != (int)((char*)this + 0x74)) {
        *(unsigned char*)&out[0] = 0;
        ((CInsert*)this)->insert(out, &param_2, (unsigned int)(unsigned long)out[0]);
    }
    CFind1c* t = (CFind1c*)((char*)this + 0x1c);
    t->find(out, &param_2);
    unsigned int node = (unsigned int)(unsigned long)out[0];
    if (node != (unsigned int)(unsigned long)((char*)t + 4)) {
        *(int*)((char*)t + 0x14) -= 1;
        RBTreeIncrement((void*)(unsigned long)node);
        RBTreeErase((void*)(unsigned long)node, (void*)((char*)t + 4));
        freeNode((void*)(unsigned long)node);
    }
}

// @ 0x00de6f20
void CFeedbackStore::FUN_00de6f20(unsigned int* pId, unsigned int* pKey)
{
    void* it[2];
    union { unsigned int mDword; unsigned char mByte; } flag;

    if (*(void**)mTree00.find(it, pKey) != (void*)&mTree00.mpLeft)
        return;

    CStarManager* manager = FUN_00b3d2a0(0);
    CBannerGroup* group = manager->GetBannerGroup();
    CPropertyList* source = group->GetList(0);

    CPropertyList* list = 0;
    void* mem = EA_ZoneObjectNew(0x1b0, "Simulator/GGE", 0, 0, 0, 0);
    if (mem != 0) {
        ((CPropertyList*)mem)->Construct();
        list = (CPropertyList*)mem;
    }
    list->AssignCopy(source);
    list->SetKey(pKey, 0);
    list->SetId(pId);
    flag.mByte = 0;
    mTree1c.insert(it, pKey, flag.mDword);

    CGGEPlanet* planet = 0;
    void* memPlanet = EA_ZoneObjectNew(0x1c8, "Simulator/GGE", 0, 0, 0, 0);
    if (memPlanet != 0) {
        ((CGGEPlanet*)memPlanet)->Construct();
        planet = (CGGEPlanet*)memPlanet;
    }
    planet->SetProperties(list);
    FUN_00b3d360()->AttachPlanet(planet);
}

// @ 0x00de7010
void CFeedbackStore::FUN_00de7010()
{
    CSimState* sim = FUN_00b3d360();
    if (sim->mListHead.mpNext != &sim->mListHead || sim->mCount34 != 0)
        return;

    CWorldEntry* node = (CWorldEntry*)mTree3c.mpLeft;
    void* end = (void*)&mTree3c.mpNode;
    void* iter[2];
    unsigned int n = 0;
    if ((void*)node == end)
        return;
    do {
        if (n >= 10)
            return;
        unsigned int* pKey = &node->mKey;
        unsigned int* pId = &node->mId;
        bool skip = false;
        if (FUN_00b3d360()->IsWorldActive(pKey)) {
            if (*(void**)mTree00.find(iter, pKey) != (void*)&mTree00.mpLeft)
                skip = true;
            else if (*(void**)mTree1c.find(iter, pKey) != (void*)&mTree1c.mpLeft)
                skip = true;
        }
        if (!skip) {
            n++;
            FUN_00de6f20(pId, pKey);
        }
        node = (CWorldEntry*)RBTreeIncrement(node);
    } while ((void*)node != end);
}

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
void FeedbackMap::EraseUintKey(const uint32_t* pKey)
{
    FeedbackNode* pNode = 0;
    FindUintKey(&pNode, pKey);
    if (pNode != (FeedbackNode*)&mAnchor) {
        --mCount;
        RbNode* pNext = RBTreeIncrement(pNode);
        (void)pNext;
        RBTreeErase(pNode, &mAnchor);
        operator_delete__(pNode);
    }

    FeedbackNode* pFound = 0;
    mKeyTree.Find((void**)&pFound, (void*)pKey);
    if ((void*)pFound == (void*)&mKeyTree.mAnchor)
        return;
    RemoveKeyEntry(*pKey, &pFound->mpValue);
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
        Key keyCopy = *pKey;
        FeedbackNode* pOut = 0;
        InsertKey(&pOut, pNode, &keyCopy, pNode);
        pNode = pOut;
    }
    return &pNode->mpValue;
}

// @ 0x00de7630
Handler** IntMap::Slot(int* pKey)
{
    RbNode* pHeader = &mAnchor;
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

    InsertResult res;
    res.mpNode = 0;
    res.mFlag = 0;
    Insert(&res.mpNode, pCandidate, &nKey, (char*)((uint32_t)pKey & 0xffffff00u));
    return &((IntNode*)res.mpNode)->mpValue;
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

// @ 0x00de81b0
void __fastcall FUN_00de81b0(GalaxyEntry* self, int /*edx*/)
{
    uint8_t* base = (uint8_t*)self;

    self->mbC8 = 0;

    {
        void* hints = FUN_0067cac0();
        FUN_0067c3b0(hints, 0, 0x2e25815e, 0);   // UIHints::Next(0x2e25815e, 0)
    }

    // Release every handler stored in the map at +0x124.
    for (void* node = self->mpMapFirst; node != &self->mpMapSentinel; node = FUN_00921580(node)) {
        void* handler = *(void**)((char*)node + 0x14);
        VCall0(handler, 0xf);                    // vt +0x3c
    }

    {
        void* win = FUN_008105b0(base + 0x144, 0, 0x615a5ff, 1);
        if (win)
            VCall1(win, 0x1f, 1);                // vt +0x7c(1, 0)
        FUN_00811ad0(base + 0x144, 0, 1);
    }

    if (self->mn108 == 3) {
        self->mn108 = 5;
        self->mn10c = 5;
    }

    self->mb100 = 0;

    // Release the window host (+0x184) and the optional host at +0x1b0.
    {
        void* p = self->mp184;
        VCall0(p, 3);                            // vt +0x0c
        p = self->mp184;
        if (p)
            VCall1(p, 0, 1);                     // vt +0x00(1)
        self->mb103 = 1;
        self->mp184 = 0;
    }
    {
        void* p = self->mp1b0;
        if (p) {
            VCall1(p, 3, 0);                     // vt +0x0c(0)
            p = self->mp1b0;
            if (p) {
                self->mp1b0 = 0;
                VCall0(p, 1);                    // vt +0x04
            }
        }
    }

    // Scene / effects / movie subsystems.
    {
        void* scene = FUN_00df5f40();
        VCall1(scene, 0x17, 0);                  // vt +0x5c(0)
    }
    {
        void* obj = FUN_0067dd50();
        VCall1(obj, 0x14, 0xd);                  // vt +0x50(0xd)
    }
    {
        void* fx = FUN_0067ddd0();
        void* world = self->mpEffectsWorld;
        void* arg = VCallP(fx, 7);               // vt +0x1c
        VCall1(world, 7, (int)arg);              // vt +0x1c(world's world)
    }

    ReleaseSlot_s00de_81b0((void**)&self->mp160);
    ReleaseSlot_s00de_81b0((void**)&self->mp1a0);
    ReleaseSlot_s00de_81b0((void**)&self->mp164);
    ReleaseSlot_s00de_81b0((void**)&self->mp168);
    ReleaseSlot_s00de_81b0((void**)&self->mp16c);
    ReleaseSlot_s00de_81b0((void**)&self->mp170);

    ReleaseSlotChecked((void**)&self->mp1a4);
    ReleaseSlotChecked((void**)&self->mp1a8);
    ReleaseSlotChecked((void**)&self->mp19c);

    if (self->mn108 != 4) {
        void* ui = self->mpUIData;
        if (ui && *(void**)((char*)ui + 0xb8))
            FUN_00df6db0(*(void**)((char*)ui + 0xb8), 0, 1);   // SetUIState(1)

        // Two-phase release of the effects vector, then empty it.
        void** first = self->mpEffectVecBegin;
        void** last = self->mpEffectVecEnd;
        for (void** it = first; it != last; ++it) {
            if (*it)
                VCall1(*it, 3, 1);               // vt +0x0c(1)
        }
        void** newEnd = (void**)FUN_0042f530(last, last, first);
        for (void** it = newEnd; it < self->mpEffectVecEnd; ++it) {
            if (*it)
                VCall0(*it, 1);                  // vt +0x04
        }
        self->mpEffectVecEnd = newEnd;
    }

    {
        uint8_t* panels = (uint8_t*)kGUI_PanelIDs_s00de_81b0;
        if (panels[0x104] != 0 || *(int32_t*)(panels + 0x108) != 4) {
            void* scene = FUN_00df5f40();
            VCall1(scene, 0x18, 0);              // vt +0x60(0, 0)
            scene = FUN_00df5f40();
            VCall1(scene, 0x17, 0);              // vt +0x5c(0)
            scene = FUN_00df5f40();
            FUN_00df9510(scene, 0);
        }
    }

    self->mb140 = 0;

    // Broadcast the mode-change messages.
    {
        static const uint32_t kModeMsgs[] = {
            0x4360e14, 0x56bbd7f, 0x44db12e, 0x5bd6378, 0x5dd52c7, 0x6203fdc,
            0x4519b5f, 0x625d27d, 0x67c75bd6, 0x634297ad, 0x275a9c8c, 0xeda117de,
            0x8085c4c,
        };
        for (int i = 0; i < 13; ++i) {
            void* server = FUN_0067dcc0();
            ((void (__thiscall*)(void*, void*, uint32_t, int))VT(server)[0xb])(
                server, base + 8, kModeMsgs[i], 0xffffd8f1);
        }
    }

    {
        void* fx = FUN_0067ddd0();
        VCall1(fx, 0x26, 0);                     // vt +0x98(10, 0)
    }
    {
        void* world = self->mpEffectsWorld;
        VCall0(world, 0xd);                      // vt +0x34
    }
    {
        void* fx = FUN_0067ddd0();
        VCall1(fx, 0x14, 0x2dda976);             // vt +0x50(0x2dda976)
    }

    ReleaseSlot_s00de_81b0((void**)&self->mpEffectsWorld);

    self->mbC9 = 0;

    {
        void* movie = FUN_0067cb10();
        if (movie)
            VCall1(movie, 0x10, 1);              // vt +0x40(1)
    }

    FUN_0080dc50(FUN_0067cad0(), 0, self->mpBoundingBox);

    FUN_00ddc8d0();
}

// @ 0x00de86d0
void __fastcall FUN_00de86d0(GalaxyEntry* self, int /*edx*/, int value, char flag)
{
    if (!flag) {
        self->mn10c = value;
        return;
    }

    int32_t& state = self->mn108;
    if (state == 1 || state == 0 || state == 8 || state == 9)
        state = 2;

    if (self->mpVecEnd < self->mpVecCap) {
        uint32_t* pos = self->mpVecEnd;
        self->mpVecEnd = pos + 1;
        if (pos)
            *pos = (uint32_t)state;
    } else {
        FUN_00b96600(&self->mpVecBegin, 0, self->mpVecEnd, &state);
    }

    self->mn10c = value;
}

// @ 0x00de8760
void __fastcall FUN_00de8760(GalaxyEntry* self, int /*edx*/, float dt, float total)
{
    if (g_CBEnabled != 0) {
        FUN_00dda3b0(FUN_00dd9190(), 0, 0);
        FUN_00dda3b0(FUN_00dd9190(), 0, 1);
        g_CBEnabled = 0;
    }
    FUN_00dda3b0(FUN_00dd9190(), 0, (char)g_CBIndex);

    if (self->mb1f6) {
        FUN_00bb7620(FUN_00b3d2a0(), 0);
        self->mb1f6 = 0;
    }

    if (self->mpModeTarget)
        ((void (__thiscall*)(void*, float))VT(self->mpModeTarget)[5])(self->mpModeTarget, dt);

    {
        int ms = (int)(total * kfMsScale);
        FUN_00ddc6d0(FUN_00dd9190(), 0, ms);
    }

    if (self->mb103) {
        self->mb103 = 0;

        uint32_t rect[4] = { 0, 0, 0, 0 };
        void* app = FUN_0067dd10();
        void* viewer = VCallP(app, 0x16);                    // vt +0x58
        FUN_007c4010(viewer, 0, rect);

        float cx = (float)((int)(rect[2] - rect[0]) / 2);
        float cy = (float)((int)(rect[3] - rect[1]) / 2);

        void* win = FUN_00e012b0(&self->mp184, 0, 0x3685038);
        if (win) {
            float* r = (float*)VCallP(win, 0xe);             // vt +0x38
            ((void (__thiscall*)(void*, float, float))VT(win)[0x19])(
                win,
                cx - (r[2] - r[0]) * kfHalf,
                cy - (r[3] - r[1]) * kfHalf);
        }
    }

    {
        int setting = FUN_00401030();
        void* world = self->mpEffectsWorld;
        int on = *(char*)(setting + 0x1c) != 0;
        VCall1(world, 3, on);                                // vt +0x0c(enabled)
    }

    FUN_00de6650(self, 0, dt, total);

    {
        float v = FUN_00dde5c0(self->mp198, 0);
        float av = v < 0 ? -v : v;
        void* p;
        if (FUN_008d3200(0x11, 0x3ff) && FUN_008d3200(0x10, 0x3ff)) {
            p = self->mp170;
            if (p && g_fAbsThreshold < av && !VCallC(p, 4))  // vt +0x10
                VCall1(p, 2, 0);                            // vt +0x08(0)
        } else {
            p = self->mp16c;
            if (p && g_fAbsThreshold < av && !VCallC(p, 4))
                VCall1(p, 2, 0);
        }
    }

    // Mode machine.
    if (self->mn108 != self->mn10c) {
        if (self->mn108 == 0) {
            if (self->mn1ec == 6) {
                void* galaxy = FUN_00b3d340();
                if (*(uint8_t*)((char*)galaxy + 0x47) != 0 || g_bSomeFlag != 0) {
                    int msg[3] = { 0x7fa5e584, 0xb1b104, 0xf5f6fde8 };
                    FUN_00809db0(&self->mpCalloutTarget, msg);
                    self->mn10c = 0;
                    self->mn108 = 0;
                    ((uint8_t*)FUN_00b3d340())[0x47] = 0;
                    goto mode_target;
                }
                self->mn108 = self->mn10c;
                FUN_00de5470(self, 0, true);
            }
        } else if (self->mn108 == 1) {
            self->mn108 = self->mn10c;
            FUN_00de5470(self, 0, true);
        } else {
            self->mn108 = self->mn10c;
        }
    }

mode_target:
    {
        int* sel = (int*)FUN_00de7630(&self->mpMapRoot, 0, &self->mn108);
        int selected = *sel;
        if ((uint32_t)(self->mn1ec - 1) <= 4) {
            int key = 1;
            sel = (int*)FUN_00de7630(&self->mpMapRoot, 0, &key);
            selected = *sel;
        }

        int* old = (int*)self->mpModeTarget;
        if (selected != (int)old) {
            if (old)
                VCallC(old, 4);                             // vt +0x10
            self->mpModeTarget = (void*)selected;
            if (selected)
                VCall0((void*)selected, 3);                 // vt +0x0c
            FUN_00804ed0(&dt, &total);
            FUN_00de44f0(self, 0, dt, total, 0);
            FUN_00de4910(self, 0);
        }
    }
}
