// src/game/SPGonzago/_at_00b70000.cpp -- migrated from slice(s) s00b7cc60, s00b7bd50, s00b7b070, s00b7a4a0, s00b794e0, s00b77db0, s00b76f10, s00b75f70, s00b73e70, s00b72b60, s00b71a60, s00b70820, s00b6f4f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/_at_00b70000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cHierGrid.h"
#include "SP/cIGonzagoSubsystem.h"
#include "EA/Variant.h"
#include "SP/cPropertyList.h"
#include "EA/Swarm/cTransform.h"
#include <math.h>
#include "SP/cGameData.h"
#include "SP/cEmpire.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "SP/cPlanetModel.h"
#include <string.h>
#include "SP/cDefaultBeamProjectile.h"
#include "SP/cSPSpaceToolData.h"
#include "SP/cViewer.h"
#include "SP/cIModelWorld.h"
#include "SP/cModelManager.h"
#include "SP/cSpatialObject.h"
#include <emmintrin.h>

// ---- items of slice s00b6f4f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefLite {
    virtual int  AddRef();                 // 0x00
    virtual int  Release();                // 0x04
    virtual void g2();                     // 0x08
    virtual void* Cast(unsigned id);       // 0x0c
virtual void g4();
virtual void g5();
    virtual void g6();                     // 0x18
    virtual void Notify(unsigned a);       // 0x1c
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
virtual void f12();
virtual void f13();
virtual void f14();
virtual void f15();
virtual void f16();
virtual void f17();
virtual void f18();
virtual void f19();
virtual void f20();
virtual void f21();
virtual void f22();
virtual void f23();
virtual void f24();
virtual void f25();
virtual void f26();
virtual void f27();
virtual void f28();
virtual void f29();
virtual void f30();
virtual void f31();
virtual void f32();
virtual void f33();
virtual void f34();
virtual void f35();
virtual void f36();
virtual void f37();
virtual void f38();
virtual void f39();
virtual void f40();
virtual void f41();
virtual void f42();
virtual void f43();
virtual void f44();
virtual void f45();
    virtual void NotifyB8();               // 0xb8
};
struct NodeUIntARC {              // node of the +0x28 hashtable
    unsigned  key;                // +0x00
    IRefLite* value;              // +0x04  (AutoRefCount payload)
    NodeUIntARC* next;            // +0x08
};
struct NodeTripleARC {            // node of the +0x48 hashtable
    unsigned  k0, k1, k2;         // +0x00..+0x08
    IRefLite* value;              // +0x0c
    NodeTripleARC* next;          // +0x10
};
struct HashUIntARC {              // +0x28 hashtable header
    void*         mAlloc;         // +0x00
    NodeUIntARC** mpBucket;       // +0x04
    unsigned      mnBucketCount;  // +0x08
    unsigned      mnElementCount; // +0x0c
    void*         mHashPolicy;    // +0x10
};
struct HashTripleARC {
    void*           mAlloc;         // +0x00
    NodeTripleARC** mpBucket;       // +0x04
    unsigned        mnBucketCount;  // +0x08
    unsigned        mnElementCount; // +0x0c
    void*           mHashPolicy;    // +0x10
};
struct HashIt { void* node; void* bucket; };
struct IStreamHandle;             // EA::IO stream (opaque, passed to the Read/Write helpers)
struct ISerializerStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual IStreamHandle* GetStream();               // slot 6 (+0x18)
};
struct ISerializer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void EndItem();                           // slot 7  (+0x1c)
    virtual ISerializerStream* GetStreamHolder();     // slot 8  (+0x20)
    virtual void v9();                                // slot 9  (+0x24)
    virtual IRefLite* ReadObject(unsigned classid, IRefLite** out, int flags); // slot 10 (+0x28)
    virtual void WriteObject(IRefLite* obj);          // slot 11 (+0x2c)
};
struct HashFind {
    HashIt* find(HashIt* out, const unsigned* key);                                  // 0x00645ed0
};
struct MissionStrategy {              // AutoRefCount payload of the +0x28 map
    virtual int  AddRef();            // +0x00
    virtual void Release();           // +0x04
    virtual void g08();               // +0x08
    virtual void* Cast(unsigned id);  // +0x0c
virtual void g10();
virtual void g14();
virtual void g18();
    virtual void Notify(unsigned a);  // +0x1c
virtual void g20();
virtual void g24();
virtual void g28();
virtual void g2c();
virtual void g30();
virtual void g34();
virtual void g38();
virtual void g3c();
virtual void g40();
virtual void g44();
virtual void g48();
virtual void g4c();
virtual void g50();
virtual void g54();
virtual void g58();
virtual void g5c();
virtual void g60();
virtual void g64();
virtual void g68();
virtual void g6c();
virtual void g70();
virtual void g74();
    virtual void Step();              // +0x78
};
struct TutorialMission {
    virtual int  AddRef();            // +0x00
    virtual void Release();           // +0x04
    virtual void g08();               // +0x08
    virtual void* Cast(unsigned id);  // +0x0c
virtual void g10();
virtual void g14();
virtual void g18();
virtual void g1c();
virtual void g20();
virtual void g24();
virtual void g28();
virtual void g2c();
virtual void g30();
virtual void g34();
virtual void g38();
virtual void g3c();
virtual void g40();
virtual void g44();
virtual void g48();
virtual void g4c();
virtual void g50();
virtual void g54();
virtual void g58();
virtual void g5c();
virtual void g60();
virtual void g64();
virtual void g68();
virtual void g6c();
virtual void g70();
virtual void g74();
    virtual void* GetNextMission();   // +0x78
};
struct MissionMgr {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
    virtual unsigned g28(int a);                   // slot 10 (+0x28)
    virtual void g2c();                            // slot 11 (+0x2c)

    char            mPad00[0x14 - 4];               // vptr at 0, so four bytes are consumed
    IRefLite**      mObjectsBegin;                 // +0x14
    IRefLite**      mObjectsEnd;                   // +0x18
    IRefLite**      mObjectsCapacity;              // +0x1c
    char            mPad20[0x28 - 0x20];
    HashUIntARC     mStrategyMap;                  // +0x28
    char            mPad3c[0x48 - 0x28 - sizeof(HashUIntARC)];
    HashTripleARC   mTripleMap;                    // +0x48
    char            mPad5c[0x68 - 0x48 - sizeof(HashTripleARC)];
    IRefLite*       mCard68;                       // +0x68
    IRefLite*       mCard6c;                       // +0x6c
    unsigned char   mFlag70;                       // +0x70

    void __thiscall Write(ISerializer* s);              // 0x00b6f570
    void __thiscall RefreshAll(int a, int b);           // 0x00b6f650
    void __thiscall RefreshCards();                     // 0x00b6f760
    IRefLite* __thiscall LookupStrategy(unsigned key);  // 0x00b6fa60
    void __thiscall Shutdown();                         // 0x00b70070
    void __thiscall OnStrategyGone(unsigned id);        // 0x00b700f0
    void __thiscall Dtor();                             // 0x00b705a0
    IRefLite* __thiscall Hint(unsigned key);            // 0x00b706a0
    unsigned __thiscall HintClear(unsigned id);         // 0x00b707a0
};
// ---- items of slice s00b6f4f0 end

// ---- items of slice s00b70820 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const uint32_t g_TerrainPropIDs[];                // 0x01464f04
struct Property {
    uint32_t pad0[4];
    uint16_t pad10;
    uint16_t mnType;            // +0x12 (10 uint32, 13 float)
    uint32_t* GetUInt();        // 0x0041ea00
    float*    GetFloat();       // 0x0041ea70
};
struct PropertyList {
    virtual void AddRef();
    virtual void Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(uint32_t id, Property*& out);   // +0x24
};
struct cPropertyManager {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList*& out);  // +0x2c
};
cPropertyManager* PropertyManager();                     // 0x0067de30
struct cTerrainSphere { int GetIndex(); };               // 0x00c75420
struct cNounManager { cTerrainSphere* GetCurrentTerrainSphere(); };  // 0x00f67d90
cNounManager* NounManager();                             // 0x00b3d300
extern PropertyList* g_TuningList;                       // 0x016879f8 (intrusive_ptr<PropertyList>)
static inline void ResetList(PropertyList*& sp)
{
    // eastl::intrusive_ptr::operator=(NULL)
    PropertyList* const pTemp = sp;
    if (pTemp) {
        sp = 0;
        pTemp->Release();
    }
}
static inline bool GetFloatProp(PropertyList* list, uint32_t id, float& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd) {
        dst = *prop->GetFloat();
        return true;
    }
    return false;
}
static inline bool GetUIntProp(PropertyList* list, uint32_t id, uint32_t& dst)
{
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xa) {
        dst = *prop->GetUInt();
        return true;
    }
    return false;
}
#define TF(id, dst) GetFloatProp(g_TuningList, id, dst)
#define TU(id, dst) GetUIntProp(g_TuningList, id, dst)
struct cTuning_b708d0 {
    float f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;
    uint32_t u68;
    float f6c;
    uint32_t u70;
    float f74;
    uint32_t u78;
    float f7c;
    uint32_t u80;
    float f84;
    uint32_t u88;
    float f8c, f90, f94, f98, f9c, fa0, fa4, fa8, fac, fb0, fb4, fb8, fbc, fc0, fc4, fc8;

    void Load(uint32_t instanceID);
    void Init(uint32_t instanceID);
    void SerializeObject(void* object);
};
void __fastcall FUN_00b5b6c0(void* self);                 // SP::cGonzagoSimulator ctor
void* __cdecl FUN_00f473a0(int size, const char* file, int line,
                           int flags, const char* name, int allocatorFlags);
void __cdecl FUN_00f47380(void* node);
void* __cdecl FUN_00921580(void* node);                   // RBTreeIncrement
void __cdecl FUN_00921880(void* node, void* anchor);      // RBTreeErase
#define VTFN(obj, slot) (*(void***)(obj))[slot]
struct MotiveObject
{
    void*  m_vtable0;            // +0x00
    int    m_pad4;
    void*  m_vtable8;            // +0x08
    int    m_pad0c;
    void*  m_vtable10;           // +0x10
    int    m_field14;            // +0x14
    int    m_field18;            // +0x18
    int    m_field1c;            // +0x1c
    int    m_pad20[3];           // +0x20
    void*  m_field2c;            // +0x2c
    int    m_field30;            // +0x30
    int    m_field34;            // +0x34
    float  m_field38;            // +0x38
    float  m_field3c;            // +0x3c
    int    m_field40;            // +0x40
    int    m_pad44[2];           // +0x44
    void*  m_field4c;            // +0x4c
    int    m_field50;            // +0x50
    int    m_field54;            // +0x54
    float  m_field58;            // +0x58
    float  m_field5c;            // +0x5c
    int    m_field60;            // +0x60
    int    m_pad64;              // +0x64
    int    m_field68;            // +0x68
    int    m_field6c;            // +0x6c
    unsigned char m_field70;     // +0x70
};
struct TreeNode
{
    TreeNode* m_left;            // +0x00
    TreeNode* m_right;           // +0x04
    int       m_pad8[2];         // +0x08
    void*     m_ref10;           // +0x10
    void*     m_ref14;           // +0x14
};
struct MapView
{
    int       m_pad0;            // +0x00
    TreeNode* m_end;             // +0x04 (sentinel address)
    TreeNode* m_begin;           // +0x08
};
struct MotiveMap
{
    int    m_pad0;               // +0x00
    void*  m_end;                // +0x04 (sentinel address = this+4)
    void*  m_begin;              // +0x08
    void*  m_root;               // +0x0c
    unsigned char m_flag10;      // +0x10
    unsigned char m_pad11[3];    // +0x11
    int    m_size;               // +0x14

    void  erase(void** out, TreeNode* node);      // 0x00b71730
    void  deleteTree(TreeNode* node);             // 0x00b71790
};
struct MotiveObjectTree
{
    unsigned char m_pad0[0x1c];  // +0x00
    MotiveMap     m_map;         // +0x1c

    bool findEvent(void* event);                  // 0x00b71510
};
struct RefPair;
struct NodeFactory
{
    void* newNode(RefPair* pair);                 // 0x00b715c0
};
struct RefPair
{
    void* m_first;
    void* m_second;
};
struct NewNode
{
    int   m_pad0[4];             // +0x00..+0x0f
    void* m_ref10;               // +0x10
    void* m_ref14;               // +0x14
};
void __cdecl WriteUint32(void* stream, const void* value, int count, int flags);   // 0x0093aa70
struct cVarListSerializer
{
    char m_data[0xa14];
    void ctor(void* owner, void* name, int line);        // 0x00692f90
    void Serialize(void* object);                        // 0x00692900
};
struct RBTreeFind
{
    void** find(void** out, void** key);                 // 0x00e5c780
};
// ---- items of slice s00b70820 end

// ---- items of slice s00b71a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* DAT_0156b308;           // cDataSerializerGeneric* list
extern int gPoolCounter;             // 0x0156b380
extern const char kPoolName[];       // 0x01464f9c "Simulator/cObjectPool"
extern unsigned gMessageIds[8];                          // 0x01465004
extern float gTune_0156b390, gTune_0156b394, gTune_0156b398;
extern float gVec_016880d4, gVec_016880d8, gVec_016880dc;
extern float gTune_0156b39c, gTune_0156b3a0, gTune_0156b3a4, gTune_0156b3a8;
extern float gEps13ec4b8;    // 0x013ec4b8  (1e-8f)
void* operator new(size_t size, const char* pName, int flags, unsigned dbg, const char* file, int line);
void  operator delete(void* p, const char* pName, int flags, unsigned dbg, const char* file, int line);
inline void* operator new(size_t, void* p) throw() { return p; }
inline void  operator delete(void*, void*) throw() {}
int   __cdecl SP_ReadInt32(void* pStream, void* pDest, int nCount, int nStride);   // 0x0093a780
void* __cdecl memset(void* pDst, int c, size_t n);                                // 0x011e073e
void* Fn_00c696a0(void* pObj, float fSeconds, double dElapsed);                    // 0x00c696a0
void  __cdecl Fn_00c69760(void* pParam, uint32_t arg);                             // 0x00c69760
struct IStream;
struct FeedbackTree;
struct FeedbackNode;
struct cGameDataVector;
struct cFeedbackEvent;
namespace eastl {
struct nb {
    nb*      mpNodeRight;    // +0x00
    nb*      mpNodeLeft;     // +0x04
    nb*      mpNodeParent;   // +0x08
    uint32_t mColor;         // +0x0c
};
}
struct FeedbackNode {
    eastl::nb  mBase;                // +0x00
    uint32_t   mKey;                 // +0x10
    void*      mpEvent;              // +0x14
};
struct FeedbackTree {
    int         mCompare;            // +0x00
    eastl::nb   mAnchor;             // +0x04
    uint32_t    mnSize;              // +0x14

    void Purge(FeedbackNode* pNode);                     // 0x00b71790
};
void  __cdecl   TreeErase(FeedbackNode** ppOut, FeedbackNode*);
void* __cdecl   TreeFind(FeedbackNode** ppOut, FeedbackTree*, const uint32_t* pKey);
void  __cdecl   TreeInsertUnique(void* pRet, FeedbackNode* pParent,
                                 const void** ppValue, int bFlag);
void  __cdecl   TreeHintInsert(FeedbackNode** ppOut, FeedbackTree*, uint32_t* pKey);   // 0x00b71e40 (in-slice)
struct cDevice {
virtual void  Slot0();
virtual void  Slot1();
virtual void  Slot2();
virtual void  Slot3();
virtual void  Slot4();
virtual void  Slot5();
    virtual void* GetStream();       // 6 (0x18)
};
struct IStream {
virtual void  Slot0();
virtual void  Slot1();
virtual void  Slot2();
    virtual void* Cast(uint32_t);    // 3 (0x0c)
    virtual void  Slot4();
    virtual void  Slot5();           // 5 (0x14)
    virtual void  Slot6();           // 6 (0x18)
    virtual void  Slot7();           // 7 (0x1c)
    virtual void* Slot8();           // 8 (0x20)
    virtual void* Slot9();           // 9 (0x24)
    virtual void  Slot10();          // 10 (0x28)
    virtual void* Slot11();          // 11 (0x2c)
    virtual void* Slot12();          // 12 (0x30)
    virtual void  Slot13();          // 13 (0x34)
    virtual void  Slot14(void*);     // 14 (0x38)
    virtual void  Slot15();          // 15 (0x3c)
    virtual void  Slot16();          // 16 (0x40)
virtual void  Slot17();
virtual void  Slot18();
virtual void  Slot19();
virtual void  Slot20();
virtual void  Slot21();
    virtual void* Slot22(uint32_t);  // 22 (0x58)
virtual void  Slot23();
virtual void  Slot24();
virtual void  Slot25();
virtual void  Slot26();
virtual void  Slot27();
virtual void  Slot28();
virtual void  Slot29();
virtual void  Slot30();
virtual void  Slot31();
virtual void  Slot32();
virtual void  Slot33();
virtual void  Slot34();
virtual void  Slot35();
virtual void  Slot36();
virtual void  Slot37();
virtual void  Slot38();
virtual void  Slot39();
virtual void  Slot40();
virtual void  Slot41();
virtual void  Slot42();
virtual void  Slot43();
virtual void  Slot44();
virtual void  Slot45();
    virtual void* Slot46(uint32_t);  // 46 (0xb8)
    virtual void  AddRefSlot();      // 47 (0xbc)
    virtual void  ReleaseSlot();     // 48 (0xc0)
    virtual void  Slot49();          // 49 (0xc4)
    virtual void  Slot50();          // 50 (0xc8)
    virtual void  Slot51();          // 51 (0xcc)
    virtual void  Slot52();          // 52 (0xd0)
    virtual void  Slot53();          // 53 (0xd4)
};
struct cIGonzagoSubsystem {
    virtual void SubsystemSlot0();
};
struct cRefCountBase {
    virtual void AddRef();           // slot 0
    virtual void Release();          // slot 1
};
struct cGonzagoBase : cIGonzagoSubsystem, cRefCountBase {
    char  mData08[0x1c - 0x08];      // +0x08 .. +0x1b
    cGonzagoBase();                  // 0x00b5b960
    ~cGonzagoBase();                 // 0x00b5b9a0
};
struct cOwner : cGonzagoBase {
    FeedbackTree mFeedback;          // +0x1c

    cOwner();                                // 0x00b71dc0
    ~cOwner();                               // 0x00b71e00 (deleting)

    void ReadFeedback(IStream* pStream);      // 0x00b71a60
    void RemoveFeedback(IStream* pStream);    // 0x00b71af0
};
struct cVarListSerializer_s00b7_1a60 {
    char mData[0xa14];
    cVarListSerializer_s00b7_1a60(void const*, void*, unsigned);
    bool Serialize(IStream&);
};
struct cGameNounManager {
    void RemoveNoun(void* pNoun);    // 0x00b225d0
    void* CreateNoun(uint32_t id);   // 0x00b20c60
    cGameDataVector* GetGameDataVector(void*, void*, void*, void*, uint32_t);  // 0x00b21340
};
cGameNounManager* __cdecl SP_NounManager();                              // 0x00b3d300
struct cGameModeManager {
    char     mPad00[0x88];
    uint32_t mField88;               // +0x88
    uint32_t GetScriptId();          // 0x00b72320
};
cOwner::~cOwner()
{
    FeedbackTree& rTree = mFeedback;
    rTree.Purge((FeedbackNode*)rTree.mAnchor.mpNodeParent);
}
struct cObjectPool {
    char*     mpData;                // +0x00  (byte-addressed storage; mStride is in bytes)
    int       mFreeHead;             // +0x04
    uint32_t  mNextHandle;           // +0x08
    int       mUsed;                 // +0x0c
    int       mHighWater;            // +0x10
    int       mStride;               // +0x14
    int       mCapacity;             // +0x18

    void        Init(int nStride, int nCapacity);   // 0x00b72080
    void        Destroy();                          // 0x00b720e0
    void        Reset();                            // 0x00b72110
    static __declspec(noinline) void __fastcall Advance(int* pIndex, cObjectPool* pPool);  // 0x00b72120
    uint32_t    Alloc();                            // 0x00b72160
    void*       Get(uint32_t handle);               // 0x00b721d0
    void*       At(uint32_t index);                 // 0x00b72210
    void*       Next(int* pIndex);                  // 0x00b72230
    void        Free(uint32_t handle);              // 0x00b72260
};
struct cGameDataVector {
    char   pad0[4];
    void** mpBegin;                  // +0x04
    void** mpEnd;                    // +0x08
};
struct cMessagingServer {
virtual void  Slot0();
virtual void  Slot1();
virtual void  Slot2();
virtual void  Slot3();
virtual void  Slot4();
virtual void  Slot5();
virtual void  Slot6();
virtual void  Slot7();
virtual void  Slot8();
virtual void  Slot9(/* hListener, id */ unsigned hListener, unsigned id);
};
cMessagingServer* __cdecl EA_Messaging_GetServer();      // 0x00883860
struct cMessageListener {
    char mPad00[0x20];
    cMessagingServer* mpServer;  // +0x20
    void*             mpOwner;   // +0x24
    unsigned*         mpIds;     // +0x28
    int               mCount;    // +0x2c
    int               mState;    // +0x30

    void Register(void);         // 0x00b72370
};
struct cXform {
    virtual void Slot0();            // +0x00 vtable
    void PreRotateY(float a);        // 0x004099b0
    void PreRotateX(float a);        // 0x005a2d90
    void RotateY(float a);           // 0x006b9050
    void PreRotateXYZ(float a, float b, float c);   // 0x00b72520
};
struct cHierGrid {
    char mPad00[0x24];
    void* mpBegin;                   // +0x24
    void* mpEnd;                     // +0x28
    unsigned CreateEntry(float c, unsigned b, unsigned a);                 // 0x00703d50
    void     Remove(unsigned handle);                                      // 0x00702da0
};
struct cHierGridHost {
    char      mPad00[0x55a4];
    cHierGrid* mpGrid;               // +0x55a4
};
cHierGridHost* __cdecl Fn_00b3d3c0();    // 0x00b3d3c0
struct cGridEntryOwner {
    char     mPad00[0x38];
    char     mKey[0x10];             // +0x38
    float    mField48;               // +0x48
    char     mPad4c[0x18];
    int      mHandle;                // +0x64 (index into the grid)

    void SetActive(bool bActive);    // 0x00b725e0
};
struct cProp {
    char     mPad00[0x12];
    uint16_t mType;                  // +0x12
};
struct cModeTuning {
    char  mPad00[0x5480];
    float mField5480;                // +0x5480
    float mField5484;                // +0x5484
    float mField5488;                // +0x5488
    float mField548c;                // +0x548c
    float mField5490;                // +0x5490
    float mField5494;                // +0x5494
    float mField5498;                // +0x5498
    float mField549c;                // +0x549c
    float mField54a0;                // +0x54a0
    float mField54a4;                // +0x54a4
    void UpdateFromGameMode(void* pArg);   // 0x00b72640
};
struct cPropertyList {
    virtual void  Slot0();
    virtual void  Slot1();
    virtual void  Slot2();
    virtual void  Slot3();
    virtual void  Slot4();
    virtual void  Slot5();
    virtual void  Slot6();
    virtual void  Slot7();
    virtual void  Slot8();
    virtual bool  GetProperty(uint32_t id, cProp** ppOut);   // 9 (0x24)
    virtual void  Release();                                 // 1 (0x04)
};
float* __cdecl Property_GetFloat(void* pProp);               // 0x0041ea70
bool   __cdecl SP_GetPropertyAsVector3(cPropertyList* pList, uint32_t id, void* pOut); // 0x006a1110
cPropertyList* __cdecl GameModeMgr_GetPropertyList(void* pArg);  // 0x00b1daf0 (via 0x00b3d320)
struct cFlagObject {
    char     mPad00[0x20];
    uint32_t mFlags;                 // +0x20

    void SetFlag2();                 // 0x00b72870
    void ClearFlag2();               // 0x00b72880
};
bool __cdecl ClosestPointsOnSegments(const float* pA0, const float* pA1,
                                     const float* pB0, const float* pB1,
                                     float fa, float fb, float* pOutA, float* pOutB); // 0x00698fa0
// ---- items of slice s00b71a60 end

// ---- items of slice s00b72b60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_one;    // 0x01485720 = 1.0f
extern const float g_eps;    // 0x013ec4b8 = 1e-8
extern const float g_fb4;    // 0x0156b3b4
extern const float g_fb8;    // 0x0156b3b8
extern const float g_fbc;    // 0x0156b3bc
extern const float g_fc0;    // 0x0156b3c0
extern int         g_cnt;    // 0x0156b3b0
extern const float g_px;     // 0x01687ad4
extern const float g_py;     // 0x01687ad8
extern const float g_pz;     // 0x01687adc
extern const int   g_i0;     // 0x01687af0
extern const int   g_i1;     // 0x01687af4
extern const int   g_i2;     // 0x01687af8
#undef VS
typedef unsigned int uint;
void* __cdecl EAAllocate(uint size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
struct V3 { float x, y, z; };
struct Op {
    char  pad[0x38];
    float x, y, z;                           // +0x38, +0x3c, +0x40
    float mDistMin;                          // +0x44
    float mDistMax;                          // +0x48
    float mRadius;                           // +0x4c
    char  pad2[0x88 - 0x50];
    int   mType;                             // +0x88
};
uint __cdecl FUN_00b72890(const V3* origin, float len, const V3* dir, const V3* pos,
                          const V3* normal, float dist, float lim, char flag, float* outDist);
struct Sim {
    char  pad[0x548c];
    float mScale[4];                         // +0x548c
    float m5498;                             // +0x5498
    uint FUN_00b72b60(V3* a, V3* b, float c, Op* obj, char flag, float* outDist, bool* outFlag);
};
struct HashNode { char pad[0x10]; HashNode* mpNext; };
struct HIt {
    HashNode*  mpNode;     // +0
    HashNode** mpBucket;   // +4
    HIt* advance(HIt* out, int);  // 0x00b72d80
};
struct K12 { uint a, b, c; };
typedef bool (*Pred12)(const K12*, const K12*);
K12* FUN_00b72430(K12*, K12*, Pred12);   // adjacent_find
struct LNode {
    uint k0, k1, k2;                 // +0x00
    char pad[0xc70 - 0x0c];
    LNode* mpNext;                   // +0xc70
};
struct Key24 { uint v[6]; };
struct Node1c { Key24 key; uint f18; };
struct E18 {
    float a, b, c, d;                // +0x00
    bool  f;                         // +0x10
    uint  v;                         // +0x14
    E18& operator=(const E18& o) {
        a = o.a; b = o.b; c = o.c; d = o.d; f = o.f; v = o.v;
        return *this;
    }
};
typedef bool (*Cmp0c)(const void*, const void*);
struct T0c { float a, b, c; };
void __cdecl FUN_00ba6800b(T0c* first, int top, int pos, float a, float b, float c, Cmp0c cmp);
struct E10 {
    float x, y, z;                   // +0x00
    bool  f;                         // +0x0c
    E10& operator=(const E10& o) {
        x = o.x; y = o.y; z = o.z; f = o.f;
        return *this;
    }
};
struct cGD0 { virtual void v0(); };
struct cGD1 { virtual void v1(); };
struct cGameData : cGD0, cGD1 {
    cGameData();                         // 0x00b18660
    void SetGameDataOwner(int);          // 0x00b18550
    ~cGameData();                        // 0x00b184c0
    int   m08;                           // +0x08
    void* m0c;                           // +0x0c
    void* m10;                           // +0x10
    bool  m14;                           // +0x14
    int   m18;                           // +0x18
    int   m1c;                           // +0x1c
    char  m20, m21;                      // +0x20
    int   m24;                           // +0x24
    int   m28, m2c, m30;                 // +0x28
};
#define VS(n) virtual void vs##n();
struct IV {
    VS(0)  VS(1)  VS(2)  VS(3)  VS(4)  VS(5)  VS(6)  VS(7)
    VS(8)  VS(9)  VS(10) VS(11) VS(12) VS(13) VS(14) VS(15)
    VS(16) VS(17) VS(18) VS(19) VS(20) VS(21) VS(22) VS(23)
    VS(24) VS(25) VS(26) VS(27) VS(28) VS(29) VS(30) VS(31)
    VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47)
    VS(48) VS(49) VS(50) VS(51) VS(52) VS(53) VS(54) VS(55)
    VS(56) VS(57) VS(58) VS(59) VS(60) VS(61) VS(62) VS(63)
    VS(64) VS(65) VS(66) VS(67) VS(68) VS(69) VS(70) VS(71)
    VS(72) VS(73) VS(74) VS(75) VS(76) VS(77) VS(78) VS(79)
    VS(80) VS(81) VS(82) VS(83) VS(84) VS(85) VS(86) VS(87)
    VS(88) VS(89) VS(90) VS(91) VS(92) VS(93) VS(94) VS(95)
};
struct cRc54 : IV {
    void SetValue(int idx, float value);   // 0x00a887b0
};
struct cObstacle : cGameData {
    int    m34;                          // +0x34
    float  m38, m3c, m40;                // +0x38
    float  m44, m48, m4c;                // +0x44
    int    m50;                          // +0x50
    void*  m54;                          // +0x54
    int    m58;                          // +0x58
    int    m5c;                          // +0x5c
    int    m60;                          // +0x60
    int    m64;                          // +0x64
    float  m68;                          // +0x68
    int    m6c;                          // +0x6c
    void*  m70;                          // +0x70
    int    m74;                          // +0x74
    void*  m78;                          // +0x78
    int    m7c, m80, m84;                // +0x7c
    int    m88;                          // +0x88

    cObstacle();                                   // 0x00b73a30
    virtual ~cObstacle();                          // 0x00b73b30
    void  Reset0();                                // 0x00b73bc0
    void  Reset1();                                // 0x00b73cd0
    void  SetFlag(bool);                           // 0x00b73de0
};
struct RcTbl { void* fn[0x100]; };
struct RcVt { RcTbl* tbl; };
struct Rc { RcVt* vt; int f4; char pad[0x40 - 8]; int rc; };
typedef void (__fastcall* RcFn)(void* vt, int junk, void* obj, unsigned arg);
static inline void RcCall(void* p, int off, unsigned arg) {
    Rc* o = (Rc*)p;
    ((RcFn)o->vt->tbl->fn[off / 4])((void*)o->vt, 0, p, arg);
}
static inline void ReleaseRc(void* p) {
    if (!p)
        return;
    Rc* o = (Rc*)p;
    if (o->rc <= 1) {
        unsigned a = ((unsigned)o->f4 >> 31) & 1u;
        RcCall(p, 0x170, a);
    } else {
        --o->rc;
    }
}
// ---- items of slice s00b72b60 end

// ---- items of slice s00b73e70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned long long __allshl(unsigned lo, unsigned hi, int sh); // 0x011e06e0
extern int g_156b470;
extern int g_156b424;
extern unsigned int g_168814c;   // init flag (bit 0)
extern float g_1687ad4, g_1687ad8, g_1687adc;
extern char g_1687ad0;
extern float g_1485720;
extern char g_matrix_src[];      // 0x16880f0
void FUN_00a887b0();                              // 0xa887b0  (thiscall: this, int, float)
void* SP_NounManager(int id);                      // 0xb3d300
void* SP_cGameNounManager_CreateNoun(void* m, int id);  // 0xb20c60
void* __cdecl EAAllocate(int a, const char* b, int c, int d, int e, int f); // 0xf473a0
void FUN_00c3e240();                               // 0xc3e240  (thiscall: this, float)
void* SP_GonzagoModelWorld();                      // 0xb3d520
void* __fastcall FUN_00b90410(void* self);         // 0xb90410  (GetSpeciesFromID)
void* __fastcall FUN_00b8f860(void* self);         // 0xb8f860
void* __fastcall FUN_00b03320(void* self);         // 0xb03320
struct Vec3 { float x, y, z; };
void __cdecl FUN_00b737d0(int begin, int i, int n, int idx, Vec3 v, void* cmp);
void __cdecl FUN_00b73920(int a, void* b, int c, void* d, Vec3 v);
bool __cdecl WriteUint32_s00b7_3e70(void* stream, const void* p, int n, int flag);     // 0x93aa70
void __cdecl FUN_00ae2e40(void* a, int b);                                  // 0xae2e40
void* __stdcall FUN_00b3d420_p(void* a);                                    // 0xb3d420
void* __stdcall FUN_00b3d440_0();                                            // 0xb3d440 (0 args)
void __stdcall FUN_00b3d440_2(void* out, void* a);                          // 0xb3d440 (2 args)
void* __stdcall FUN_00b3d440_3(void* a, void* b, void* c);                  // 0xb3d440 (3 args)
void* __fastcall FUN_00b04c20_3(void* a, void* b, void* c);                 // 0xb04c20
void* __fastcall FUN_00e5c780(void* self);                                  // 0xe5c780
unsigned int __fastcall FUN_00b058f0(void* self);                           // 0xb058f0
void* SP_ModelManager();                                                    // 0x67dd80
void __stdcall FUN_00571d40(void* a);                                       // 0x571d40
void __stdcall FUN_00571d20(void* a);                                       // 0x571d20
void __stdcall FUN_00478db0(void* a);                                       // 0x478db0
struct Vec3f { float x, y, z; };
struct HierGrid {
    char pad0[0x24];
    void* mBegin;      // +0x24
    void* mEnd;        // +0x28
    bool Shutdown();                                        // 0x704060
    bool Init(const Vec3f& v, float f, int a, int b);        // 0x704260
};
void* SP_GetActiveTerrainSphere();                          // 0xf48aa0
struct Simulator_cObstacle;
struct Node3View {
    int f0;                  // +0x00 (doubles as the free-list link)
    int f4;                  // +0x04
    int f8;                  // +0x08 (sub-object with a vtable)
    int fC;                  // +0x0c
    int f10;                 // +0x10
};
struct Node2View {
    int f0;                  // +0x00 (doubles as the free-list link)
    int f4;                  // +0x04 (sub-object with a vtable)
    int f8;                  // +0x08
};
struct Simulator_cObstacle {
    void* AllocNode3(int* src);   // 0xb74b60
    void* AllocNode2(int* src);   // 0xb74bc0
    void FUN_00b73f30(float f, int arg);   // 0xb73f30
};
struct Hashtable2 {
    int mPad;                 // +0x00
    int* mBegin;              // +0x04
    int mCount;               // +0x08
    int* Find(int* out, unsigned int* key);   // 0xb746a0
};
struct Hashtable3 {
    int* Find(int* out, unsigned int* key);   // 0xb74740
    void* FindNode(void* node, int* key, unsigned int hash);  // 0xb72f10
};
struct Inner { void** vptr; };            // first word is the vtable pointer
struct Wrapper { Inner* impl; };          // what +0x78 points at
typedef void (__thiscall *Fn16c)(void* self, void* owner, int a);
typedef void (__thiscall *Fn170)(void* self, void* owner, bool a);
typedef void (__thiscall *Fn_vif)(void* self, int a, float f);
typedef void (__thiscall *Fn_vf)(void* self, float f);
struct Mat3 { void Assign(const void* src); };  // 0x41cb40 __thiscall
struct DescBlock {
    short f0;            // +0x00
    short f2;            // +0x02
    float f4;            // +0x04  (0x1688118)
    float f8;            // +0x08  (0x168811c)
    float fc;            // +0x0c  (0x1688120)
    float f10;           // +0x10  (0x1688124)
};
extern DescBlock g_desc;         // 0x1688114
extern Mat3 g_mtx;               // 0x1688128
struct ObstacleMgr {
    int Lookup(unsigned int* key);   // 0xb74f40
    int FindById(unsigned int* a, int b, int id);  // 0xb74e90
};
struct Iter2 {
    int* cur;        // +0x00
    int* bucket;     // +0x04
    int* end;        // +0x08
    int* endBucket;  // +0x0c
};
// ---- items of slice s00b73e70 end

// ---- items of slice s00b75f70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_14650a4;
extern char g_1601760;                                          // +0x1601760 RNG global object
extern const float g_16880e0, g_16880e4, g_16880e8;
extern int g_13f6254;
extern const float g_1464fdc;
struct Vec3_s00b7_5f70 {
    float x, y, z;
    Vec3_s00b7_5f70() {}
    Vec3_s00b7_5f70(const Vec3_s00b7_5f70& o) : x(o.x), y(o.y), z(o.z) {}
};
void  __cdecl FUN_00b75750(void* base, void* cur, Vec3_s00b7_5f70 p);      // 0xb75750
void  __cdecl FUN_00b757b0(void* base, void* cur, Vec3_s00b7_5f70 p);      // 0xb757b0
void  __cdecl FUN_00b74d60(void* base, int a, int b, int c, void* o, Vec3_s00b7_5f70 p); // 0xb74d60
void  __cdecl FUN_00b75c60(void* first, void* last, void* buf, void* a4);     // 0xb75c60
void  __cdecl FUN_00b74c20(void* buf, void* end, void* uninit); // 0xb74c20
void  __cdecl FUN_00b754d0(void* first, void* last, void* last2, void* comp); // 0xb754d0
void* __cdecl FUN_00b75620(void* first, void* last, void* pivot);             // 0xb75620
void* __cdecl FUN_00b734e0(void* first, void* mid, void* last, Vec3_s00b7_5f70 a, Vec3_s00b7_5f70 b); // 0xb734e0
void* __cdecl FUN_00b749c0(void* begin, void* end, float x, float y, float z); // 0xb749c0
void* __cdecl EAAllocate(unsigned int sz, const char* name, int a, int b, int c, int d); // 0xf473a0
void  __cdecl opdel(void* p);                                   // 0xf47380  ??3@YAXPAX@Z
void  __cdecl FUN_0102c7f0(void* a, int b);                     // 0x102c7f0
char  __cdecl FUN_00ae5530(void* a, int b, void* c, const wchar_t* d); // 0xae5530
void* __cdecl FUN_00401010();                                   // 0x401010
void  __cdecl FUN_00407190(void* comp, unsigned key, void* out); // 0x407190
void* __cdecl FUN_00b3d2a0();                                   // 0xb3d2a0
void* __cdecl FUN_00b3d520();                                   // 0xb3d520
void* __cdecl FUN_00b3d350();                                   // 0xb3d350
void  __cdecl FUN_0093c5a0(void* out, const char* s, int n);    // 0x93c5a0
struct C579a90 {
    void __thiscall RangeInitialize(int n);                     // 0x579a90
};
struct C56e2d0 {
    void __thiscall Copy(const void* src);                      // 0x56e2d0
};
struct Var {
    char pad_0[0x10];                                           // +0x00
    unsigned short mFlags;                                      // +0x10
    unsigned short mTypeId;                                     // +0x12
};
struct C5dd750 {
    Var* __thiscall SetBool(const unsigned char* src);          // 0x5dd750
};
struct CVariant {
    void __thiscall Destruct(bool b);                           // 0x93db80
};
struct C5765e0 {
    void __thiscall Release();                                  // 0x5765e0
};
struct C478db0 {
    void* __thiscall Assign(void* p);                           // 0x478db0
};
struct C537dc0 {
    void* __thiscall Assign(const void* src);                   // 0x537dc0
};
struct C72520 {
    void __thiscall Rotate(float x, float y, float z);          // 0xb72520
};
struct CRandomGlob {
    double __thiscall RandomDoubleUniform();                    // 0x9360d0
};
struct CStarManager {
    void* __thiscall GetUFO();                                  // 0xba93b0
};
struct CEmpire {
    int* __thiscall GetUFOKey();                                // 0xc326b0
};
struct CSubObj {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
    virtual void v10();
    virtual void v14(unsigned key, void* val);
};
struct C74860 {
    void __thiscall Find(int* out, int* key);                   // 0xb74860
};
struct C75890 {
    int* __thiscall InsertKey(const void* k);                   // 0xb75890
};
struct C74f80 {
    void __thiscall Notify(void* o, float a, float b);          // 0xb74f80
};
struct C75c00 {
    void __thiscall DoFreeNodes(void* buckets, int nb);         // 0xa1b6c0
};
struct C82060 {
    void __thiscall Run(const Vec3_s00b7_5f70* d, const Vec3_s00b7_5f70* a, const Vec3_s00b7_5f70* dir); // 0xb82060
};
struct CXForm {
    void __thiscall BackTransform(Vec3_s00b7_5f70* p);                     // 0x4ff6d0
};
struct CVec3v {
    void** begin;                                               // +0x00
    void** end;                                                 // +0x04
    void** cap;                                                 // +0x08
    void  __thiscall DoInsertValue(void* at, const Vec3_s00b7_5f70* v);    // 0x4b5ad0
};
extern const float g_1687ad4_s00b7_5f70, g_1687ad8_s00b7_5f70, g_1687adc_s00b7_5f70;
struct Blob { char pad[0x38]; float x, y, z; };                 // x@0x38 y@0x3c z@0x40
struct NodeF { int key; float val; };
struct ItF { NodeF* n; NodeF** b; };
struct VTF { int key; float val; };
struct PF { ItF it; bool b; };
struct ZF { bool b; };
struct MF {
    int pad;              // +0x00
    NodeF** buckets;      // +0x04
    unsigned nb;          // +0x08
    ItF find(const int& k);              // 0x645ed0
    PF insertz(const VTF& v, ZF z);      // 0xc15fd0
};
struct RefVal { virtual void AddRef(); virtual void Release(); };
struct NRef { int key; RefVal* val; };
struct ItR { NRef* n; NRef** b; };
struct VTR { int key; RefVal* val; };
struct PR { ItR it; bool b; };
struct MR {
    int pad;
    NRef** buckets;
    unsigned nb;
    ItR find(const int& k);              // 0x645ed0
    PR insertr(const VTR& v, ZF z);     // 0xb752f0
};
struct It8 { void* n; void* b; };
struct C764e0 {
    It8 __thiscall Next(It8 i);                                   // 0xb75910
    It8 __thiscall Advance(It8 first, It8 last);
};
struct El18 { float a, b, c, d; char e; int f; };                  // 0x18
struct C76530 {
    char pad[4];
    El18* mEnd;                                                    // +0x04
    El18* mCap;                                                    // +0x08
    void __thiscall Grow(El18* end, const El18* v);                // 0xb75a30
    void __thiscall Push(const El18& v);
};
struct HTN70 { char pad[0xc70]; HTN70* mpNext; };
struct HT70 {
    struct iterator { HTN70* mpNode; HTN70** mpBucket; };
    int pad0[3];                                         // +0x00..0x08
    unsigned mnElementCount;                             // +0x0c
    iterator erase(iterator i);
};
struct HTN68 { unsigned key; char pad[0xc68 - 4]; HTN68* mpNext; };
struct HT68 {
    int pad0;
    HTN68** buckets;                                     // +0x04
    unsigned nb;                                         // +0x08
    unsigned mnElementCount;                             // +0x0c
    int eraseKey(const unsigned* k);
};
struct HTN68b { char pad[0xc68]; HTN68b* mpNext; };
struct HT68b {
    struct iterator { HTN68b* mpNode; HTN68b** mpBucket; };
    int pad0[3];
    unsigned mnElementCount;
    iterator erase(iterator i);
};
typedef bool (__cdecl* Cmp3)(const Vec3_s00b7_5f70*, const Vec3_s00b7_5f70*);
struct VObj24 {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual bool Slot24(unsigned key, void* out);
};
struct PropId {
    char pad0[0x12];
    unsigned short kind;                                 // +0x12
    char pad1[2];
    unsigned* GetUInt();                                 // 0x41ea00
};
struct CGonzago {
virtual void g00();
virtual void g04();
virtual void g08();
    virtual int  g0c(int a, int b, int c);
};
struct CSink4c {
virtual void s00();
virtual void s04();
virtual void s08();
virtual void s0c();
virtual void s10();
virtual void s14();
virtual void s18();
virtual void s1c();
virtual void s20();
virtual void s24();
virtual void s28();
virtual void s2c();
virtual void s30();
virtual void s34();
virtual void s38();
virtual void s3c();
virtual void s40();
virtual void s44();
virtual void s48();
    virtual void s4c(void* a, void* b);
};
struct WStr { wchar_t* begin; wchar_t* end; wchar_t* cap; };
struct ResTable {
    uint32_t pad_0;                                          // +0x00
    void**   mpBuckets;                                      // +0x04
    uint32_t mnBucketCount;                                  // +0x08
    uint32_t mnElementCount;                                 // +0x0c
};
struct ResTableNode {
    char pad_0[0xc];                                         // +0x00
    char mKey[0xc];                                          // +0x0c (payload)
    ResTableNode* mpNext;                                    // +0x18
};
struct ResSink {
    virtual void v00(const void* t);
    virtual void v04(const void* t);
};
// ---- items of slice s00b75f70 end

// ---- items of slice s00b76f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float g_TableMaxLoadFactor;    // 0x013f0620
extern const float g_TableGrowthFactor;     // 0x01470f1c
#pragma intrinsic(sqrt)
typedef uint32_t u32;
typedef uint64_t u64;
typedef uint8_t u8;
#define VCALL0(p, off) ((void(__thiscall*)(void*))(*(void***)(p))[(off) / 4])(p)
#define VCALL2(p, off, a, b) ((void(__thiscall*)(void*, void*, int))(*(void***)(p))[(off) / 4])(p, a, b)
struct Vec3C {           // user copy constructor: loads/stores through xmm0
    float x, y, z;
    Vec3C() {}
    Vec3C(const Vec3C& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Vec3A {           // user operator=: x87 fld/fstp copies
    float x, y, z;
    Vec3A& operator=(const Vec3A& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Model {
    u32 vt;
    u32 pad[0xa8 / 4 - 1];
    void SetAlpha(int idx, float a);  // 0x00a887b0
    void AddRef()  { VCALL0(this, 0x34); }
    void Release() { VCALL0(this, 0x38); }
};
struct Shared {
    void* mpOwner;     // +0x00 (polymorphic)
    u32   mFlags;      // +0x04
    u32   pad[0x40 / 4 - 2];
    int   mRefCount;   // +0x40
};
static __forceinline void ReleaseShared(Shared*& slot) {
    Shared* old = slot;
    if (old) {
        slot = 0;
        if (old->mRefCount > 1) {
            --old->mRefCount;
        } else {
            VCALL2(old->mpOwner, 0x170, old, (u8)((old->mFlags >> 31) & 1));
        }
    }
}
struct Obj {
    void** vt;          // +0x00
    u32    pad04[0x34 / 4 - 1];
    u32    mFlags;      // +0x34
    Vec3   mPos;        // +0x38
    float  mSize[3];    // +0x44
    u32    mExtra;      // +0x50
    Model* mpModel;     // +0x54
    void*  mpSource;    // +0x58
    int    mIndex;      // +0x5c
    u32    pad60;
    int    mGridSlot;   // +0x64
    float  mScale;      // +0x68
    u32    mId;         // +0x6c
    Shared* mpA;        // +0x70
    u32    mValue;      // +0x74
    Shared* mpB;        // +0x78
    Vec3   mDefPos;     // +0x7c
    u32    mKind;       // +0x88

    void AddRef()  { VCALL0(this, 0x00); }
    void Release() { VCALL0(this, 0x04); }
    void Reset()   { VCALL0(this, 0x54); }
};
struct Elem {            // 0x4c bytes
    u32   pad0;
    Vec3  pos;           // +0x04
    float scale;         // +0x10
    u32   pad[0x4c / 4 - 5];
};
struct SpawnReq {
    u32    count;        // +0x00
    u32    pad04;
    Elem*  elems;        // +0x08
    u32    pad0c;
    Model* ref;          // +0x10
    u32    pad14;
    u32    id;           // +0x18
    u32    pad1c;
    u32    extra;        // +0x20
};
struct Species {
    u32   pad0[0x8c / 4];
    u32   mValue;        // +0x8c
    u32   pad90;
    float mSize0;        // +0x94
    float mSize1;        // +0x98
    float mSize2;        // +0x9c
    u32 GetKind();       // 0x00b8f860
};
struct SpeciesMgr { Species* GetSpecies(float* pos); };   // 0x00b90410 (thiscall, ret 4)
struct PlantMgr   { float* Find(SpawnReq* r); };          // 0x00b2b1e0 (thiscall, ret 4)
struct TableEntry {      // 0x24 bytes
    u32 pad0;
    u32 idA;             // +0x04
    u32 idB;             // +0x08
    u32 pad0c;
    float s0, s1, s2;    // +0x10..
    u32 val;             // +0x1c
    u32 flags;           // +0x20
};
struct RbTree {          // eastl::rbtree<u32, pair<u32, RecA*>>
    u32 mCompare;
    u32 mAnchor;         // +4: header/end node
    void Find(void** out, u32* key);   // 0x00e5c780 thiscall ret 8
};
struct TableMgr {
    u32 pad[0x17c / 4];
    TableEntry* tabBegin;   // +0x17c
    TableEntry* tabEnd;     // +0x180
    u32 pad2[(0x190 - 0x184) / 4];
    RbTree mTree;           // +0x190
};
struct HtNode { u32 lo; u32 hi; Obj* obj; u32 pad; HtNode* next; };
struct HtIter {
    HtNode* node; HtNode** bucket;
    HtIter() {}
    HtIter(const HtIter& o) : node(o.node), bucket(o.bucket) {}
};
struct HtRange { HtIter first; HtIter last; };
struct HtEntry { u32 lo; u32 hi; Obj* obj; };
struct HtResult { HtIter it; };
struct TrueTag {};      // eastl::true_type: no user ctor, so it is stored as a zero byte
struct HashTable {      // eastl fixed hashtable header (full object is 0x43c bytes, see SpawnTable)
    u32      mUnk00;             // +0x00
    HtNode** mpBucketArray;      // +0x04  mBucketCount + 1 slots, the spare one is the end sentinel
    u32      mBucketCount;       // +0x08
    u32      mElementCount;      // +0x0c
    void Insert(HtResult* out, HtEntry* e, TrueTag t);       // 0x00b75240 thiscall ret 0xc
    void Erase(HtResult* out, HtIter first, HtIter last); // 0x00b764e0 thiscall ret 0x14
    HtRange* Find(HtRange* out, const u32* pKey);           // 0x00b746a0 thiscall ret 8
    void clear(HtNode** pBuckets, u32 bucketCount);         // 0x00b759b0 thiscall ret 8
    void Rehash(u32 bucketCount);                           // 0x00b5d220 thiscall ret 4
    // eastl::hashtable<...>::hashtable(...) as instantiated for the fixed-pool table
    void CtorBase(void* pPoolBlock, const void* pHasher, const void* pEq1, const void* pEq2,
                  const void* pEq3, const void* pEq4, const void* pAlloc);  // 0x00c14400
};
struct Grid {
    u32 pad[0x24 / 4];
    void* mBegin;        // +0x24
    void* mEnd;          // +0x28
    int Add(float r, Vec3* pos, Obj* o);   // 0x00703d50
    void Remove(int slot);                 // 0x00702da0
};
struct RecA { u32 pad[3]; u32* arr; };    // value of the rbtree (array at +0xc)
struct PlanetModel {
    void Mark(Vec3* v, float r, u32 mask, int zero);   // 0x00b83c40 (4 args)
};
struct PropList { bool Has(u32 id); };                 // 0x006a25a0 thiscall ret 4
extern Vec3 g_DefaultPos;     // 0x01687af0
extern PropList* g_pProps;    // 0x015fd918
PlantMgr*   GetPlantMgr();    // 0x00b3d3b0
SpeciesMgr* GetSpeciesMgr();  // 0x00b3d420
TableMgr*   GetTableMgr();    // 0x00b3d3b0 (same global)
struct Global2 { u32 pad[0x55a4 / 4]; Grid* pGrid; };
Global2*    GetGlobal2();     // 0x00b3d3c0
PlanetModel* GetPlanet();     // 0x00b3d350
struct AutoRef;      // AutoRefCount<Obj>: 4-byte handle that AddRefs on construction
struct RefModel;     // refcounted cMWModel held by Spawner::mModels
struct ObjPtrVec {                   // SPVector<AutoRefCount<cMWModel>> at Spawner +0x40f0
    Obj** mpBegin;                   // +0x00
    Obj** mpEnd;                     // +0x04
    Obj** mpCap;                     // +0x08
    void DoInsertPtr(Obj** pPos, const AutoRef& value);   // 0x00aea5d0 thiscall ret 8
};
struct RefModelVec {                 // vector<AutoRefCount<cMWModel>> at Spawner +0x5508
    RefModel** mpBegin;              // +0x00
    RefModel** mpEnd;                // +0x04
};
extern u32 g_MaxModelRefs;           // 0x0156b3ac: cap of the live-noun list
struct Spawner {
    u32 pad0[0x38 / 4];
    HashTable mAlt;           // +0x38
    u32 pad1[(0x2094 - (0x38 + 0x10)) / 4];
    HashTable mMain;          // +0x2094
    u32 pad2[(0x40f0 - (0x2094 + 0x10)) / 4];
    ObjPtrVec mModelRefs;     // +0x40f0
    u32 pad3[(0x5508 - (0x40f0 + 0x0c)) / 4];
    RefModelVec mModels;      // +0x5508
    u32 pad4[(0x55a4 - (0x5508 + 0x08)) / 4];
    Grid* mpGrid;             // +0x55a4

    bool Find(HtRange* out, u32 lo, u32 hi, u32 count, bool alt);  // 0x00b751b0 ret 0x14
    Obj* AllocObj();                                               // 0x00b74370
    void InitGrid();                                               // 0x00b74130

    bool Spawn(SpawnReq* p, u32 hash);                             // 0x00b76f10 ret 8
    void ClearTable(HashTable* pTable, u32 keyLo, u32 keyHi);      // @ 0x00b77b60 ret 0xc
    void ClearModels();                                            // @ 0x00b77aa0
};
typedef uint16_t u16;
struct Quad16 { float x, y, z, w; };   // 16-byte element, see copy_705250<Quad16>
Quad16* copy_705250(const Quad16* first, const Quad16* last, Quad16* dst);   // 0x00705250 cdecl
struct QuadVec {
    Quad16* mpBegin;    // +0x00
    Quad16* mpEnd;      // +0x04
    Quad16* mpCap;      // +0x08
    void insert(Quad16* pPos, u32 count, const Quad16& value);   // 0x00b75dc0 thiscall ret 0xc
    void resize(u32 n);                                          // @ 0x00b77850 ret 4
    __forceinline void erase(Quad16* first, Quad16* last)
    {
        copy_705250(last, last, first);
        mpEnd += first - last;
    }
};
void FUN_00b76950(Vec3* first, Vec3* last, int depth,
                  bool (__cdecl* less)(const Vec3*, const Vec3*));   // 0x00b76950 cdecl ret 0x10
void FUN_00b73200(Vec3* first, Vec3* last,
                  bool (__cdecl* less)(const Vec3*, const Vec3*));   // 0x00b73200 cdecl ret 0xc
void FUN_00b732a0(Vec3* first, Vec3* last,
                  bool (__cdecl* less)(const Vec3*, const Vec3*));   // 0x00b732a0 cdecl ret 0xc
struct cSPMatrix3_s00b7_6f10 {                    // rw::math::Matrix33Template<float,0>
    float m[9];                        // +0x00 3x3
    cSPMatrix3_s00b7_6f10() {}
    cSPMatrix3_s00b7_6f10(const cSPMatrix3_s00b7_6f10& o);   // 0x0041cb40 out of line
};
struct Vec20 { u32 v[5]; };            // 20-byte element of the record's inline vector
struct Vec20B {                        // vector with 0xc00 bytes of inline storage
    Vec20* mpBegin;                     // +0x00
    Vec20* mpEnd;                       // +0x04
    Vec20* mpCap;                       // +0x08
    u32    mAlloc[2];                   // +0x0c
    u32    mCount;                      // +0x14
    u8     mStorage[0xc00];             // +0x18
    __forceinline void reset()          // point the vector at its own storage
    {
        mpBegin = (Vec20*)mStorage;
        mpEnd   = mpBegin;
        mCount  = 0;
        mpCap   = (Vec20*)((char*)mpBegin + 0xc00);
    }
    Vec20B& operator=(const Vec20B& o);// 0x00473500 thiscall ret 4
};
struct SwarmRecord {                    // 0xc64-byte record (name not in the symbol map)
    u16        mA;                      // +0x00
    u16        mB;                      // +0x02
    float      mC;                      // +0x04
    float      mD;                      // +0x08
    float      mE;                      // +0x0c
    float      mF;                      // +0x10
    cSPMatrix3_s00b7_6f10 mMat;                    // +0x14
    float      mG;                      // +0x38
    float      mH;                      // +0x3c
    float      mI;                      // +0x40
    float      mJ;                      // +0x44
    float      mK;                      // +0x48
    Vec20B     mVec;                    // +0x4c
    SwarmRecord(const SwarmRecord& src);// @ 0x00b778b0 ret 4
};
struct FixedHashtableAllocator {        // eastl::fixed_hashtable_allocator<6,12,4,4,0,1>
    void*    mpHead;                    // +0x00 free-list head
    void*    mpNext;                    // +0x04
    u8*      mpNodeBegin;               // +0x08 inline node pool
    u8*      mpNodeEnd;                 // +0x0c
    u32      mnNodeSize;                // +0x10
    HtNode** mpBucketArray;             // +0x14 inline bucket array
    void init(void* pNodes, u32 bytes, u32 nodeSize, u32 align, u32 flags);  // 0x00921260 ret 0x14
};
struct PrimeRehashPolicy {              // eastl::prime_rehash_policy
    float mMaxLoadFactor;               // +0x00
    float mGrowthFactor;                // +0x04
    u32   mNextResize;                  // +0x08
    u32 get_next_bucket_count(u32 elementCount);   // 0x009213c0 thiscall ret 4
};
void* AllocPoolBlock(u32 bytes);            // 0x00921340 cdecl
struct SpawnTable {                     // eastl::hashtable<u32, pair<u32 const,
                                        //   AutoRefCount<EA::Swarm::cIVisualEffect> >,
                                        //   fixed_hashtable_allocator<6,12,4,4,0,1> >
    HashTable mHeader;                  // +0x000
    float     mMaxLoadFactor;           // +0x010
    float     mGrowthFactor;            // +0x014
    u32       mNextResize;              // +0x018
    u8        pad01c[0x034 - 0x01c];
    HtNode*   mBuckets[6];              // +0x034 inline bucket array
    u8        pad04c[0x13c - 0x04c];
    u8        mNodePool[0x300];         // +0x13c inline node pool (64 * 0xc bytes)

    SpawnTable(const void* pHasher, const void* pEqual);   // @ 0x00b77780 ret 8
};
struct AutoRef {                        // AutoRefCount<Obj>: 4-byte refcounted handle
    Obj* mpObject;                      // +0x00
    AutoRef(Obj* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
struct RefModel : Shared {              // refcounted spawned noun (AutoRefCount<cMWModel>)
    u32       pad044[0x64 / 4 - 0x44 / 4];
    RefModel* mpSub;                    // +0x64 sub-object released through its vtable
};
static __forceinline void ReleaseModelRef(RefModel* m)
{
    if (m) {
        if (m->mRefCount > 1) {
            --m->mRefCount;
        } else {
            VCALL2(m->mpOwner, 0x170, m, (u8)((m->mFlags >> 31) & 1));
        }
    }
}
void copy_5f4e10(RefModel** first, RefModel** last, RefModel** dst);   // 0x005f4e10 cdecl
struct cGameNounManager_s00b7_6f10 {
    void RemoveNoun(Obj* pNoun);        // 0x00b225d0 thiscall ret 4
};
cGameNounManager_s00b7_6f10* GetNounManager();     // 0x00b3d300 cdecl
// ---- items of slice s00b76f10 end

// ---- items of slice s00b77db0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PI(p, off) (*(int*)((char*)(p) + (off)))
#define PU(p, off) (*(u32*)((char*)(p) + (off)))
#define PF_s00b7_7db0(p, off) (*(float*)((char*)(p) + (off)))
#define PP(p, off) ((void**)((char*)(p) + (off)))
#define PS(p, off) ((char*)(p) + (off))
void* EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line); // 0xf473a0
void  FUN_00b746a0(void* out, void* src);        // 0x00b746a0
void  FUN_00b75240(void* out, void* val, u32 flags);  // 0x00b75240
void  FUN_00b764e0(void* a, int b, int c, int d, int e);  // 0x00b764e0
void  FUN_00b77b60(void* self, int a, int b);    // 0x00b77b60
void  FUN_00b759b0(void* a, void* b);            // 0x00b759b0
void  FUN_00b75b80(void* a, void* b);            // 0x00b75b80
void  FUN_00b75bf0(void* a, void* b);            // 0x00b75bf0
void  FUN_00b73070(void* a, void* b);            // 0x00b73070
void  FUN_00a24480(void* a, void* b);            // 0x00a24480
void  FUN_00b72290();                            // 0x00b72290
void  FUN_00b725a0();                            // 0x00b725a0
void  FUN_00b72560();                            // 0x00b72560
void  FUN_00b72580();                            // 0x00b72580
void* FUN_00b77940(void* a, void* b, void* cmp); // 0x00b77940
void* FUN_00b72dc0(void* a, void* b, void* cmp); // 0x00b72dc0
void* FUN_00921240(void* fn);                    // 0x00921240
void  FUN_00b768d0(void* a, void* b, void* fn);  // 0x00b768d0
int   FUN_00699a10(const float* pts, int n, float* out);  // 0x00699a10  ConvexHull2D
void  FUN_00b72d80(void* a, int b);              // 0x00b72d80
void  FUN_00b72640(u32 mode);                    // 0x00b72640
void  FUN_00b76f10(void* p, u32 hash);           // 0x00b76f10
void  FUN_00b83c40(const float* v, float r, u32 mask, int zero);  // 0x00b83c40
float FUN_00c9eb60();                            // 0x00c9eb60
void* FUN_00b3d3b0();                            // 0x00b3d3b0  SP_PlantManager / table mgr
void* FUN_00b3d420(void* x);                     // 0x00b3d420  species mgr
void* FUN_00b3d320();                            // 0x00b3d320
void* FUN_00b2b1e0(void* x);                     // 0x00b2b1e0
int   FUN_00b8f860();                            // 0x00b8f860
void* FUN_00b1de80();                            // 0x00b1de80
u32   FUN_00b5b800();                            // 0x00b5b800  SP::GetCurrentGameMode
void* FUN_00b3d300(u32 id);                      // 0x00b3d300  SP::NounManager
void  FUN_00b225d0(void* mgr, u32 id);           // 0x00b225d0  cGameNounManager::RemoveNoun
u8    SP_cPropertyList_GetDescription(void* self, u32 id);  // 0x006a25a0 thiscall ret 4
void* FUN_00b77aa0();                                    // 0x00b77aa0 (base update / clear)
struct ThSub { void FUN_00b778b0(void* src); };
struct SpVec {
  void* mpBegin;            // +0
  void* mpEnd;              // +4
  void* FUN_0050f740(void* a, void* b);   // 0x0050f740  SpVector<UVector3>::erase
  void  FUN_00473810(int n);              // 0x00473810  SpVector<UVector3>::resize
};
void FUN_006782c0(void* a, void* b, void* c);   // 0x006782c0 eastl copy_impl (ILogReporter)
void FUN_00720250(void* a, void* b, void* c);   // 0x00720250 CopyVertex3D
struct Cnt {
  u32   mUnk;               // +0
  void* mBeg;               // +4
  void* mEnd;               // +8
  u32   mCount;             // +0xc
  void FUN_00b759b0(void* end, void* beg);  // 0x00b759b0
  void FUN_00b75b80(void* end, void* beg);  // 0x00b75b80
  void FUN_00b75bf0(void* end, void* beg);  // 0x00b75bf0
  void FUN_00b73070(void* end, void* beg);  // 0x00b73070
  void FUN_00a1b6c0(void* end, void* beg);  // 0x00a1b6c0 hashtable DoFreeNodes
  void FUN_00a24480(void* end, void* beg);  // 0x00a24480 PHTable::FreeBuckets
  void FUN_00704060();                      // 0x00704060 cHierGrid::Shutdown
};
struct EaVec {
  u32   mUnk;               // +0
  void* mBeg;               // +4
  void* mEnd;               // +8
  void* mCap;               // +0xc
  void* FUN_005f4e10(void* a, void* b, void* c);  // 0x005f4e10 copy_impl::do_copy
  void  FUN_005f3680(void* a, void* b);           // 0x005f3680 vector::DoDestroyValues
};
struct GameNounMgr { void FUN_00b225d0(void* noun); };  // 0x00b225d0 RemoveNoun
struct Sim_s00b7_7db0 {
  u32   pad0[0x20 / 4];
  u32   mFlags;                 // +0x20
  u32   pad24[(0x38 - 0x24) / 4];
  void* mAltBeg;                // +0x38   (hash table A begin)
  void* mAltEnd;                // +0x3c
  void* mAltCap;                // +0x40
  void* mAltCount;              // +0x44
  u32   pad48[(0x2094 - 0x48) / 4];
  void* mMainBeg;               // +0x2094 (hash table B begin)
  void* mMainEnd;               // +0x2098
  void* mMainCap;               // +0x209c
  void* mMainCount;             // +0x20a0
  u32   padA4[(0x40f0 - 0x20a4) / 4];
  void* mObjBegin;              // +0x40f0 (vector<AutoRefCount>)
  void* mObjEnd;                // +0x40f4
  u32   padF8[(0x4908 - 0x40f8) / 4];
  void* mVec4908;               // +0x4908 (vector<Vertex3D>)
  void* mVec490c;               // +0x490c
  u32   pad10[(0x49e4 - 0x4910) / 4];
  void* mHash49e4;              // +0x49e4
  void* mHash49e8;              // +0x49e8
  void* mHash49ec;              // +0x49ec
  u32   padF0[(0x4f34 - 0x49f0) / 4];
  void* mVec4f34;               // +0x4f34
  void* mVec4f38;               // +0x4f38
  void* mVec4f3c;               // +0x4f3c
  u32   pad40[(0x54a8 - 0x4f40) / 4];
  void* mV54a8beg;              // +0x54a8
  void* mV54a8end;              // +0x54ac
  void* mV54a8cap;              // +0x54b0
  void* mV54a8cnt;              // +0x54b4
  u32   padB8[(0x54cc - 0x54b8) / 4];
  void* mV54ccbeg;              // +0x54cc
  void* mV54ccend;              // +0x54d0
  void* mV54cccap;              // +0x54d4
  void* mV54ccc;
  void* mV54ecbeg;              // +0x54ec
  void* mV54ecend;              // +0x54f0
  void* mV54eccap;              // +0x54f4
  u32   padF8b[(0x55a0 - 0x54f8) / 4];
  u32   m55a0;                  // +0x55a0
  void* mpGrid;                 // +0x55a4
  void* mV55a8beg;              // +0x55a8
  void* mV55a8end;              // +0x55ac
  u32   padB0[(0x56c4 - 0x55b0) / 4];
  void* mV56c4beg;              // +0x56c4
  void* mV56c4end;              // +0x56c8
  void* mV56c4cap;              // +0x56cc
  // member methods (ecx = this Sim*), declared here so the compiler emits thiscall
  int FUN_00b780d0(int* param_1, int* param_2);
  u8  FUN_00b783b0(u32 param_2, float* param_3);
  void* FUN_00b78020(void* param_1);   // 0xc74-byte ctor copy
  void* FUN_00b78080(void* param_1);   // 0xc6c-byte ctor copy
};
u8  FUN_00b77db0(void* param_1, u32 param_2);
// ---- items of slice s00b77db0 end

// ---- items of slice s00b794e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_156b390, g_156b394, g_156b398, g_156b39c;
extern float g_156b3a0, g_156b3a4, g_156b3a8;
extern float g_16880d4, g_16880d8, g_16880dc;
extern float g_1470f1c;                // 2.0f
extern int   g_154df28;
extern unsigned g_156b3ac;             // noun count cap
struct BufferedVec {
    void* begin;
    void* end;
    void* cap;
    int   pad0;
    int   pad1;
    int   pad2;
    void Init(void* buf, unsigned n, int* zero);      // 0xb97280
    void Resize(int n);                               // 0xb98ea0
};
struct PointerVec {
    int* begin;
    int* end;
    int* cap;
    void Reserve(int n);                              // 0xd01790
    void Resize(int n);                               // 0x473270
    void Grow(int* pos, int** value);                 // 0xaea5d0
    void Push(int* pos, int* value);                   // 0xb96600
};
struct Grid_s00b7_94e0 {
    int QuerySphereResult(float radius, float* dir, int maxN, void** out);   // 0x702760
    Grid_s00b7_94e0* Construct();                                                       // 0x703ce0
};
struct PlanetModel_s00b7_94e0 {
    void DirectionToSurfacePosition(V3* out, V3* dir);  // 0xb815a0
};
struct FixedPoolBase {
    void Init(void* buf, unsigned size, unsigned elem, int a, int b);  // 0x921260
};
struct PoolDesc {
    void* head;
    int   pad;
    void* begin;
    void* end;
    int   elem;
    void* alloc;
};
struct PoolBase {
    int SizeFor(int n);                                // 0x9213c0
};
struct BucketAlloc {
    void Find(void* out, int a, int b, int c);         // 0x921440
};
struct FindRes {
    char found;
    char p0, p1, p2;
    int  value;
};
struct F2 { float a, b; F2() {} F2(float x, float y) { a = x; b = y; } };
struct Gonzago {
    void Ctor();                                       // 0xb5b960
};
struct Sub;
struct Sim_s00b7_94e0 {
    void Teardown();                                   // 0xb781d0
};
struct Sub {
    void Detach();                                     // 0xb79a60
};
struct ObMgr {
    void* Construct();                                 // 0xb79740
    void* Init(int* a, int* b);                        // 0xb794e0
    int*  Insert(int* out, int* key, int unused);      // 0xb795c0
    int*  FindNode(int* bucket, int* key, unsigned h); // 0xb72f10
    void  Destroy();                                   // 0xb79aa0
    void  Query(V3* dir, PointerVec* out, unsigned mask, float radius,
                char flag, V3* p);                     // 0xb79c30
    int   Count(V3* dir, float radius, char filter);   // 0xb79e50
    void  QueryNear(V3* dir, float radius, unsigned mask,
                    PointerVec* out);                  // 0xb7a1d0
    void* NewNode(int* key);                           // 0xb78020
    void  FreeNode(int node);                          // 0xb72e50
    void  DoFreeNodes(int n);                          // 0xc76610
};
typedef void (__thiscall *FnV)(void* self);
typedef void (__thiscall *FnV2)(void* self, int a, int b);
typedef int  (__thiscall *FnCount)(void* self, void* out);
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b,
                         const char* file, int line);                     // 0xf473a0
void __cdecl operator delete(void*);                                      // 0xf47380
void* __cdecl FUN_00921340(int n);                                        // 0x921340
void __stdcall FUN_00b745f0(int h, void* a, void** pb, void** pb2, void* bv,
                            void** pb3, void* desc);                      // 0xb745f0
void __cdecl RemoveHandler(int h, int a, int b, int c, int d);             // 0x571db0
void __cdecl FUN_00b779c0(int* begin, int* end, float x, float y, float z); // 0xb779c0
void* __cdecl PlanetModelGet();                                           // 0xb3d350
void* __stdcall NounManager(unsigned key);                                // 0xb3d300
void* __fastcall CreateNoun(void* self);                                  // 0xb20c60
void __cdecl CopyPtrs(void* first, void* last, void* dst);                // 0x5f4e10
float __cdecl QuatDist(V3* a, V3* b, V3* c);                              // 0x698b30
void __fastcall FUN_00b74130(ObMgr* self);                                // 0xb74130
void __fastcall FUN_00b76160(ObMgr* self);                                // 0xb76160
struct HashtableOps {
    void FreeTable(int* buckets, unsigned n);                              // 0xb759b0
    void Free70(int* buckets, unsigned n);                                 // 0xb75b80
    void Free68(int* buckets, unsigned n);                                 // 0xb75bf0
};
struct PoolCtor2 {
    void Init(int* a, int* b);                                             // 0xb77780
};
#define OB_COUNT_TEST(q)                                                      \
    {                                                                         \
        int o_ = (q);                                                         \
        if (!(filter != 0 && *(int*)(o_ + 0x88) > 2)) {                       \
            int w_ = *(int*)(o_ + 0x70);                                      \
            if (!(w_ != 0 && ((*(unsigned*)(w_ + 4) >> 15) & 1) == 0)) {      \
                float dx_ = dir->x - *(float*)(o_ + 0x38);                    \
                float dy_ = dir->y - *(float*)(o_ + 0x3c);                    \
                float dz_ = dir->z - *(float*)(o_ + 0x40);                    \
                float r_ = *(float*)(o_ + 0x44) + radius;                     \
                if (dx_ * dx_ + dy_ * dy_ + dz_ * dz_ < r_ * r_)              \
                    ++count;                                                  \
            }                                                                 \
        }                                                                     \
    }
// ---- items of slice s00b794e0 end

// ---- items of slice s00b7a4a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_lightModel;    // 0x01687b30
struct Vec3_s00b7_a4a0 {
    float x, y, z;
    Vec3_s00b7_a4a0() {}
    Vec3_s00b7_a4a0(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
struct FVec3 : Vec3_s00b7_a4a0 {
    FVec3() {}
    FVec3(const FVec3& o) { x = o.x; y = o.y; z = o.z; }
    FVec3& operator=(const FVec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3_s00b7_a4a0 { float m[9]; };
extern FVec3 g_zeroVec;     // 0x01687ad4
extern Mat3_s00b7_a4a0 g_identity;    // 0x016880f0
#define VPAD10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
    virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
virtual void p##8();
void __cdecl operator_delete_array(void* p);                          // 0x00f47380 (operator delete[])
struct cBeamLight;
struct cHierGrid_s00b7_a4a0;
struct cQueryAux {
    uint32_t mPad000;        // +0x000
    uint32_t mFlags;         // +0x004
};
struct cQueryObj {
    uint32_t mPad000[0x38 / 4];   // +0x000
    Vec3_s00b7_a4a0 mPosition;               // +0x038
    float mRadius;                // +0x044
    uint32_t mPad048[0x28 / 4];   // +0x048
    cQueryAux* mAux;              // +0x070
};
struct IntVector {
    uint32_t* mpBegin;       // +0x000
    uint32_t* mpEnd;         // +0x004
    uint32_t* mpCapacity;    // +0x008

    int count() const { return (int)(mpEnd - mpBegin); }
    void insert(uint32_t* pos, int n, const uint32_t* value);      // 0x00b97280
    void resize(int n);                                            // 0x00b98ea0
    void DoInsertKey4(uint32_t* pos, const uint32_t& value);       // 0x00b96600
    IntVector& operator=(const IntVector& other);                  // 0x00ebf480
    void push_back(uint32_t value)
    {
        if (mpEnd < mpCapacity) {
            *mpEnd++ = value;
        } else {
            DoInsertKey4(mpEnd, value);
        }
    }
    // eastl's erase: shift the tail down over [first,last) and drop it.  The only
    // call site is clear(), where the shifted range is empty.
    void erase(uint32_t* first, uint32_t* last)
    {
        memcpy(first, last, (size_t)(mpEnd - last) * sizeof(uint32_t));
        mpEnd -= last - first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};
struct cFixedIntVector : IntVector {
    uint32_t mPad00c[2];             // +0x00c
    uint32_t mStorageCookie;         // +0x014 (also mBuffer[-1]: 0 = inline storage)
    uint32_t mBuffer[0x100];         // +0x018

    cFixedIntVector()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 0x100;
        mStorageCookie = 0;
    }
    ~cFixedIntVector()
    {
        if (mpBegin != 0 && mpBegin[-1] != 0)
            operator_delete_array(mpBegin);
    }
};
struct cHierGrid_s00b7_a4a0 {
    uint32_t mPad000[0x24 / 4];      // +0x000
    IntVector mEntities;             // +0x024
    int Query3Result(float* from, float* to, float radius, int maxResults, void** results);  // 0x00702860
};
struct cLightOwner {
    VPAD10(b0) VPAD10(b1) VPAD10(b2) VPAD10(b3) VPAD10(b4) VPAD10(b5) VPAD10(b6)
    VPAD10(b7) VPAD10(b8)
    virtual void pad90();
    virtual void Update(cBeamLight* pLight, int flag);       // +0x16c
    virtual void Destroy(cBeamLight* pLight, int flag);      // +0x170
};
struct cBeamLight {
    cLightOwner* mOwner;     // +0x000
    uint32_t mFlags;         // +0x004
    uint16_t mDirty;         // +0x008
    uint16_t mDirtyCount;    // +0x00a
    Vec3_s00b7_a4a0 mPosition;          // +0x00c
    float mScale;            // +0x018
    Mat3_s00b7_a4a0 mMatrix;            // +0x01c
    int mRefCount;           // +0x040
    uint32_t mPad044[8];     // +0x044

    void Release() { mOwner->Destroy(this, (mFlags >> 31) & 1); }
};
struct cModelFactory {
    virtual void AddRef();                   // +0x00
    virtual void Release();                  // +0x04
    virtual void pad08();                    // +0x08
    virtual cBeamLight* CreateInstance(const void* typeId, uint32_t modelId, int size);   // +0x0c
};
struct cModelManager {
virtual void pad00();
virtual void pad04();
virtual void pad08();
virtual void pad0c();
virtual void pad10();
virtual void pad14();
virtual void pad18();
    virtual cModelFactory* GetModel(uint32_t modelId);       // +0x1c
};
struct cLightVector {            // eastl vector of light pointers
    cBeamLight** mpBegin;        // +0x00
    cBeamLight** mpEnd;          // +0x04
    cBeamLight** mpCapacity;     // +0x08
    void resize(uint32_t n);     // 0x00473270
};
cModelManager* ModelManager();   // 0x0067dd80
struct cSpawner {
    uint32_t mPad000[0x5508 / 4];                       // +0x000
    cLightVector mLights;                               // +0x5508
    uint32_t mPad514[(0x55a0 - 0x5514) / 4];            // +0x5514
    uint32_t mObjMask;                                  // +0x55a0
    cHierGrid_s00b7_a4a0* mpGrid;                                  // +0x55a4

    void ClearModels();                                 // 0x00b77aa0
    int CollectLights(float* from, float* to, float radius, IntVector* out, char mode);  // 0x00b7a4a0
    void ResetLights();                                 // 0x00b7a710
};
// ---- items of slice s00b7a4a0 end

// ---- items of slice s00b7b070 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float  DAT_01485720;                                   // 1.0f
extern float  DAT_013ec4b8;                                   // 1e-08f
extern float  DAT_01687ad4, DAT_01687ad8, DAT_01687adc;       // origin
extern float  DAT_013f9428;                                   // 0.001f seconds-per-millisecond
extern char   DAT_0156b478[];                                 // cVarListSerializer name
extern char   DAT_013eb394[];                                 // base vtable
extern char   DAT_014650cc[], DAT_014650e8[], DAT_014650c8[]; // manager vtables
#pragma pack(push, 1)
typedef unsigned int  uint32;
typedef unsigned char uint8;
extern uint8  DAT_01687ad0;                                   // force-ambience flag
void* __cdecl FUN_00b3d4d0(void);                                     // 0x00b3d4d0  current game context
void* __cdecl FUN_0067dd10(void);                                     // 0x0067dd10  SP::App
void* __cdecl FUN_00720250_s00b7_b070(void* first, void* last, void* result);    // 0x00720250  eastl do_copy
void  __cdecl FUN_00571db0(int h, int a, int b, int c, int d);        // 0x00571db0  EA::Messaging::RemoveHandler
struct Ext {
    float* FUN_00b81630(float* out, const float* in);      // 0x00b81630  planet-space transform
    void   FUN_007c3d30(float* a, float* b, float* c, float* d);  // 0x007c3d30  cViewer::GetCameraLocationInfo
    void   FUN_00b7a4a0(float* a, float* b, float r, void* vec, int flag);   // 0x00b7a4a0
    char   FUN_00b72b60(void* a, float* b, float c, void* d, uint32 e, float* f, char* g);  // 0x00b72b60
    void*  FUN_00645ed0(void** out, const void* key);      // 0x00645ed0  hashtable::find
    float* FUN_00b76400(const void* key);                  // 0x00b76400  hashtable insert
    void   FUN_00b76e00(int a, float b);                   // 0x00b76e00
    void   FUN_00b7a710();                                 // 0x00b7a710
    void   FUN_00b77aa0();                                 // 0x00b77aa0
    void   FUN_00692f90(void* obj, const void* name, int hash);  // 0x00692f90  cVarListSerializer ctor
    char   FUN_00693e10(void* arg);                        // 0x00693e10  cVarListSerializer::Serialize
    void   FUN_00750310();                                 // 0x00750310
    void   FUN_00b73070(uint32 a, uint32 b);               // 0x00b73070
    void   FUN_005f3680(uint32 a, uint32 b);               // 0x005f3680  eastl DoDestroyValues
    void   FUN_00b75bf0(uint32 a, uint32 b);               // 0x00b75bf0
    void   FUN_00b75b80(uint32 a, uint32 b);               // 0x00b75b80
    void   FUN_00b759b0(uint32 a, uint32 b);               // 0x00b759b0
    void   FUN_00a24480(uint32 a, uint32 b);               // 0x00a24480
    void   FUN_00a1b6c0(uint32 a, uint32 b);               // 0x00a1b6c0  hashtable::DoFreeNodes
    void   FUN_00ae6970();                                 // 0x00ae6970  ~vector<AutoRefCount<cStarRecord>>
    void   FUN_00b5b9a0();                                 // 0x00b5b9a0  ~cGonzagoSubsystem
    void   FUN_00b77780(const void* hasher, const void* equal);  // 0x00b77780  SpawnTable ctor
    void   FUN_00b74f80(void* node, float a, float b);     // 0x00b74f80  per-node effect update
    void   FUN_00b74590(void* node);                       // 0x00b74590  per-node effect release
    void   FUN_00a887b0(uint32 index, float alpha);        // 0x00a887b0  Model::SetAlpha
};
struct VtApp {                       // SP::App
virtual void p0();
virtual void p1();
virtual void p2();
virtual void p3();
virtual void p4();
virtual void p5();
virtual void p6();
virtual void p7();
virtual void p8();
virtual void p9();
virtual void q0();
virtual void q1();
virtual void q2();
virtual void q3();
virtual void q4();
virtual void q5();
virtual void q6();
virtual void q7();
virtual void q8();
virtual void q9();
    virtual void* FUN_00000050();    // slot 20 (+0x50)
};
struct VtHost {                      // SP::App::something
virtual void r0();
virtual void r1();
virtual void r2();
virtual void r3();
virtual void r4();
virtual void r5();
virtual void r6();
    virtual void* FUN_0000001c();    // slot 7 (+0x1c)
};
struct Vec18 { float v[6]; };
struct SampleVec {
    void**  begin;
    void**  end;
    void**  cap;
    void*   spare0;
    void*   spare1;
    void*   buf[0x100];
};
struct Mgr {
    void  Sample(float* camPos, float* entry);
    void  Update(int a, float b);
    char  SerializeIt(void* arg);
    void  Destroy();
    void  UpdatePooled(int a, int b);
};
#define RELEASE(C, FN) \
    do { \
        uint32* blk_; \
        ((Ext*)(C))->FN(*(uint32*)((char*)(C) + 4), *(uint32*)((char*)(C) + 8)); \
        blk_ = *(uint32**)((char*)(C) + 4); \
        *(uint32*)((char*)(C) + 0xc) = 0; \
        if (*(uint32*)((char*)(C) + 8) > 1 && blk_ != *(uint32**)((char*)(C) + 0x30)) { \
            if (blk_ < *(uint32**)((char*)(C) + 0x24) || *(uint32**)((char*)(C) + 0x28) <= blk_) { \
                FUN_00f47380(blk_); \
            } else { \
                *blk_ = *(uint32*)((char*)(C) + 0x1c); \
                *(uint32*)((char*)(C) + 0x1c) = (uint32)blk_; \
            } \
        } \
    } while (0)
struct Serializer {
    char body[0xa14];
};
#define VCALL2_s00b7_b070(p, off, a, b) \
    ((void(__thiscall*)(void*, void*, int))(*(void***)(p))[(off) / 4])(p, a, b)
#define VCALLR0(p, off) ((char(__thiscall*)(void*))(*(void***)(p))[(off) / 4])(p)
struct HtNode_s00b7_b070 {
    uint32  mKey;      // +0x00
    uint32  mValue;    // +0x04  AutoRefCount<T>: 4-byte handle
    HtNode_s00b7_b070* mpNext;    // +0x08
};
struct HtIter_s00b7_b070 {
    HtNode_s00b7_b070*  mpNode;   // +0x00
    HtNode_s00b7_b070** mpBucket; // +0x04
};
inline bool operator==(const HtIter_s00b7_b070& l, const HtIter_s00b7_b070& r) { return l.mpNode == r.mpNode; }
struct SpawnTable_s00b7_b070 {
    uint32   mUnk00;            // +0x000
    HtNode_s00b7_b070** mpBucketArray;     // +0x004
    uint32   mBucketCount;      // +0x008
    uint32   mElementCount;     // +0x00c
    uint32   mMaxLoadFactor;    // +0x010
    uint32   mGrowthFactor;     // +0x014
    uint32   mNextResize;       // +0x018
    uint32   mFreeHead;         // +0x01c
    uint32   mUnk20;            // +0x020
    void*    mpAllocBegin;      // +0x024
    void*    mpAllocEnd;        // +0x028
    uint32   mUnk2c;            // +0x02c
    void*    mpInlineBuckets;   // +0x030
    HtNode_s00b7_b070*  mpBuckets[6];      // +0x034
    uint8    mPad04c[0x13c - 0x04c];
    uint8    mNodePool[0x300];  // +0x13c
    // The compiler gives the type a 0x550-byte footprint even though the constructor only
    // initialises up to the end of the node pool at +0x43c (frames of both SpawnTable
    // locals in the image are sized from 0x550).
    uint8    mTail[0x114];      // +0x43c
    HtIter_s00b7_b070 Find(uint32 key) const;
    HtIter_s00b7_b070 End() const;
};
__forceinline HtIter_s00b7_b070 SpawnTable_s00b7_b070::End() const
{
    HtIter_s00b7_b070 it = { mpBucketArray[mBucketCount], &mpBucketArray[mBucketCount] };
    return it;
}
__forceinline HtIter_s00b7_b070 SpawnTable_s00b7_b070::Find(uint32 key) const
{
    uint32  h = key % mBucketCount;
    HtNode_s00b7_b070* p = mpBucketArray[h];
    while (p != 0 && p->mKey != key) p = p->mpNext;
    if (p != 0) {
        HtIter_s00b7_b070 it = { p, &mpBucketArray[h] };
        return it;
    }
    return End();
}
struct PoolList {
    uint32   mUnk00;            // +0x00
    HtNode_s00b7_b070** mpBucketArray;     // +0x04
    uint32   mBucketCount;      // +0x08
    uint32   mElementCount;     // +0x0c
    uint32   mPad10[3];         // +0x10
    uint32   mFreeHead;         // +0x1c
    uint32   mUnk20;            // +0x20
    void*    mpAllocBegin;      // +0x24
    void*    mpAllocEnd;        // +0x28
    uint32   mUnk2c;            // +0x2c
    void*    mpInlineBuckets;   // +0x30
    HtIter_s00b7_b070*  Erase(HtIter_s00b7_b070* out, HtNode_s00b7_b070* node, HtNode_s00b7_b070** bucket);  // 0x00d2c9f0 ret 0xc
    uint32*  FindOrInsert(const uint32* key);                    // 0x00b76460 ret 4
};
struct MgrPoolView {
    uint8    mPad[0x4f2c];
    PoolList mPool;             // +0x4f2c
};
struct Model;
struct Shared_s00b7_b070 { void* mpOwner; uint32 mFlags; };            // +0x00 / +0x04
struct PoolObj {
    void**   vt;                // +0x00
    uint32   mPad04[0x34 / 4 - 1];
    uint32   mFlags;            // +0x34
    Vec3f    mPos;              // +0x38
    float    mSize[3];          // +0x44
    uint32   mExtra;            // +0x50
    Model*   mpModel;           // +0x54
    void*    mpSource;          // +0x58
    int      mIndex;            // +0x5c
    uint32   mPad60;            // +0x60
    int      mGridSlot;         // +0x64
    float    mScale;            // +0x68
    uint32   mId;               // +0x6c
    Shared_s00b7_b070*  mpA;               // +0x70
    uint32   mValue;            // +0x74
    Shared_s00b7_b070*  mpB;               // +0x78
    Vec3f    mDefPos;           // +0x7c
    uint32   mKind;             // +0x88
    void AddRef()  { VCALL0(this, 0x00); }
    void Release() { VCALL0(this, 0x04); }
};
struct SgEntry;
struct SgEntryList {
    SgEntry* FUN_00b2a690(uint32 id, uint32 extra, uint32 index);  // 0x00b2a690 thiscall
};
SgEntryList* FUN_00b3d3b0_s00b7_b070(void);   // 0x00b3d3b0  plant-entry list accessor
struct UpdatePooledLocals {
    Mgr*      mgr;
    PoolList* pool;
    float     sec;
    HtIter_s00b7_b070    found;
    HtIter_s00b7_b070    end;
    HtNode_s00b7_b070*   endNode;
    PoolObj*  obj;
    HtIter_s00b7_b070    erased;
};
// ---- items of slice s00b7b070 end

// ---- items of slice s00b7bd50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" double sqrt(double);
extern "C" void* __cdecl SP_GameInputManager();
extern "C" void* __cdecl SP_App();
extern "C" void __cdecl sub_805ea0(float* out);                        // 0x00805ea0
extern "C" bool __cdecl sub_41dd30(const void* a, const void* b);   // 0x0041dd30
extern "C" bool __cdecl sub_41dd90(const void* a, const void* b);   // 0x0041dd90
extern "C" bool __cdecl sub_b78880(void* a, void* b, void* c, int d); // 0x00b78880
extern "C" void __cdecl sub_5f4e10(void* src, void* end, void* dst); // 0x005f4e10
extern "C" void __cdecl FUN_f47380(void* p);                        // 0x00f47380 operator delete
extern "C" void __cdecl sub_b75240(void* a, void* b, int c);        // 0x00b75240
extern "C" int g_01687af0;      // 0x01687af0
extern "C" int g_01687af4;      // 0x01687af4
extern "C" int g_01687af8;      // 0x01687af8
extern "C" void* __cdecl sub_67dd80();      // 0x0067dd80 SP::ModelManager
extern "C" void __cdecl cSPUIPieMenu_SetItemTextColor(int id, int color);
extern "C" void* __cdecl SP_PlanetModel();
typedef unsigned char  u8_s00b7_bd50;
typedef unsigned short u16_s00b7_bd50;
typedef unsigned int   u32_s00b7_bd50;
static inline void Vv0(void* p, int slot) {
    ((void(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline void Vv1(void* p, int slot, int a) {
    ((void(__thiscall*)(void*, int))(*(void***)p)[slot / 4])(p, a);
}
static inline void Vv2(void* p, int slot, int a, int b) {
    ((void(__thiscall*)(void*, int, int))(*(void***)p)[slot / 4])(p, a, b);
}
class cSPUIPieMenuItemWinProc { public:
    void** vftable;             // +0x00
    char   pad_04[0xc - 0x04];
    int    mButtonId;           // +0x0c
    int    mItemId;             // +0x10
    bool   bButtonClicked;      // +0x14
    void*  mpHighlightCallback; // +0x18

    void Hide();                // 0x00818330
    bool ContainsWindow(void* hwnd); // 0x00818370
};
union Vec3_s00b7_bd50 { float f[3]; int i[3]; u32_s00b7_bd50 u[3]; };
struct SpTransform {            // cSPTransform, 0x20 bytes
    char  mPad00[4];            // +0x00
    Vec3_s00b7_bd50  mVec04;               // +0x04
    float mF10;                 // +0x10
    Vec3_s00b7_bd50  mVec14;               // +0x14
};
struct cSpatialObject {
    void** vftable;             // +0x00
    u32_s00b7_bd50    mFlags;              // +0x04
    SpTransform mXf;            // +0x08
    char   pad_28[0x90 - 0x28];
    void*  mpPropertyList;      // +0x90
};
extern cSPUIPieMenuItemWinProc* g_pPieWinProc;  // 0x0168817c
extern u8_s00b7_bd50  g_bPieMenuVisible;                   // 0x01688154
struct Property_s00b7_bd50 {
    char  pad_00[0x10];
    u16_s00b7_bd50   mFlags;               // +0x10
    u16_s00b7_bd50   mType;                // +0x12
    char  pad_14[0x40 - 0x14];

    u8_s00b7_bd50*    sub_41e920();        // 0x0041e920 value accessor (bool/enum)
    float* sub_41ea70();        // 0x0041ea70 value accessor (float)
};
struct PropertyList_s00b7_bd50 {
    bool GetProperty(u32_s00b7_bd50 key, Property_s00b7_bd50** out) {
        return ((bool(__thiscall*)(void*, u32_s00b7_bd50, Property_s00b7_bd50**))(*(void***)this)[0x24 / 4])(this, key, out);
    }
    bool HasProperty(u32_s00b7_bd50 key) {
        Property_s00b7_bd50* p;
        return GetProperty(key, &p) != 0;
    }
    float GetFloatProperty(u32_s00b7_bd50 key) {
        Property_s00b7_bd50* p;
        if (GetProperty(key, &p) && p->mType == 0xd) return *p->sub_41ea70();
        return 0.0f;
    }
    bool GetBoolProperty(u32_s00b7_bd50 key) {
        Property_s00b7_bd50* p;
        if (GetProperty(key, &p) && p->mType == 1) return *p->sub_41e920() != 0;
        return false;
    }
};
struct PlanetModel_s00b7_bd50 {
    float GetRadius();              // 0x00b7e4d0
};
struct Viewer {
    void GetCameraLocationInfo(float* out, int a, int b, int c);   // 0x007c3d30
};
struct OtherObj {
    float SomeFloat();              // 0x00c887c0
};
static inline void* VRet(void* p, int slot) {
    return ((void*(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline float VRetF(void* p, int slot) {
    return ((float(__thiscall*)(void*))(*(void***)p)[slot / 4])(p);
}
static inline void* VRet1(void* p, int slot, void* a) {
    return ((void*(__thiscall*)(void*, void*))(*(void***)p)[slot / 4])(p, a);
}
static inline void* VRet3(void* p, int slot, void* a, void* b, void* c) {
    return ((void*(__thiscall*)(void*, void*, void*, void*))(*(void***)p)[slot / 4])(p, a, b, c);
}
struct S7c4180 { void sub_7c4180(float* dest, const float* center); };  // 0x007c4180
static inline float SqrtF(float x) {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(x)));
}
static inline float AbsF(float x) {
    Vec3_s00b7_bd50 v;
    v.f[0] = x;
    v.u[0] &= 0x7fffffffu;
    return v.f[0];
}
struct RefObject {
    void* mpIface;              // +0x00
    u32_s00b7_bd50   mFlags;               // +0x04
    char  pad_08[0x40 - 0x08];
    int   mnRefCount;           // +0x40
};
static inline void RefIfaceCall(RefObject* o, int slot, int arg) {
    void*  iface = o->mpIface;
    void** vt = *(void***)iface;
    ((void(__thiscall*)(void*, RefObject*, int))vt[slot / 4])(iface, o, arg);
}
static inline void RefRelease(RefObject* o) {
    if (o->mnRefCount > 1) {
        o->mnRefCount -= 1;
    } else {
        RefIfaceCall(o, 0x170, (int)(o->mFlags >> 31));
    }
}
struct MenuItemValue {          // 0xc64 bytes
    SpTransform mXf;            // +0x00 (cached transform of the source object)
    char  pad_20[0x38 - 0x20];
    float mRadius;              // +0x38
    char  pad_3c[0x4c - 0x3c];
    void* mpVecBegin;           // +0x4c
    void* mpVecEnd;             // +0x50
    void* mpVecCap;             // +0x54
    char  pad_58[0xc64 - 0x58];

    MenuItemValue* sub_b75820();                    // 0x00b75820 default ctor
    void sub_b778b0(const MenuItemValue* src);      // 0x00b778b0 copy ctor
};
static inline MenuItemValue* NodeValue(void* node) { return (MenuItemValue*)((char*)node + 4); }
struct ScreenValue {            // the value_type inserted into the map
    u32_s00b7_bd50          mKey;          // +0x00
    MenuItemValue mValue;       // +0x04
};
struct ModelKey { u32_s00b7_bd50 k0, k1, k2; };
struct ModelValue {
    ModelKey     mKey;          // +0x00
    MenuItemValue mValue;       // +0x0c
};
struct HashIter  { void* node; void* bucket; };
struct HashIter4 { void* node; void* bucket; void* last; void* lastBucket; };
struct HashTable_s00b7_bd50 {
    char   pad_00[4];
    void** ppBuckets;           // +0x04
    u32_s00b7_bd50    nBucketCount;        // +0x08
    void*  End() { return ppBuckets[nBucketCount]; }

    void  sub_b74800(HashIter* out, const void* key);        // 0x00b74800 find
    void  sub_b74740(HashIter4* out, const void* key);       // 0x00b74740 lower_bound
    void  sub_b79680(HashIter* out, const void* value, int flag);  // 0x00b79680 insert
    void  sub_b795c0(HashIter* out, const void* value, int flag);  // 0x00b795c0 insert (3-dword key)
    void  sub_b766b0(HashIter* out, HashIter it);            // 0x00b766b0 erase
    void  sub_b76580(HashIter* out, HashIter it);            // 0x00b76580 erase (3-dword key)
    void  sub_b76620(const void* key);                       // 0x00b76620 erase by key
    __declspec(noinline) void* sub_b7c1b0(const void* key);  // 0x00b7c1b0 find-or-insert
    char   pad_0c[0x14];        // +0x0c  (each map header is 0x20 bytes)
};
struct CTransformAssign { void Assign(const void* src); };            // 0x00537dc0
extern "C" u32_s00b7_bd50 g_0156b430;      // 0x0156b430 = 0x40842000
static inline void FreeValueBuffer(MenuItemValue* v) {
    void* p = v->mpVecBegin;
    if (p) {
        if (((int*)p)[-1] != 0) FUN_f47380(p);
    }
}
struct PieItem;
struct PieMgr;
struct PieRoot;
struct PieNotifier {
    char mUnused[0x205c];
    void sub_b75240(void* out, void* msg, int flag);    // 0x00b75240
};
struct PieTable2090 {
    char mUnused[0x3418];
};
struct ItemVec {
    void** mpBegin;             // +0x00
    void** mpEnd;               // +0x04
    void** mpCap;               // +0x08
    void** sub_b05d80(void** it);   // 0x00b05d80 erase
};
struct cSPPieMenu {
    char pad_00[0x1c];
    u8_s00b7_bd50   mFlags1c;              // +0x1c
    char pad_1d[0x20 - 0x1d];
    unsigned b0 : 1;            // +0x20 bit 0
    unsigned b1 : 1;
    unsigned b2 : 1;            // +0x20 bit 2
    unsigned b3 : 1;
    unsigned    : 28;
    char pad_24[0x34 - 0x24];
    PieNotifier  mNotifier34;   // +0x34
    PieTable2090 mTable2090;    // +0x2090
    HashTable_s00b7_bd50 mMap54a8;         // +0x54a8
    HashTable_s00b7_bd50 mMap54c8;         // +0x54c8
    HashTable_s00b7_bd50 mMap54e8;         // +0x54e8
    char pad_5508[0x55a0 - 0x5508];
    int  mField55a0;            // +0x55a0
    ItemVec mItems;             // +0x55a4

    void sub_b77aa0();                                  // 0x00b77aa0
    void sub_b7a710();                                  // 0x00b7a710
    int  sub_b7c290(cSpatialObject* obj, void* res);    // 0x00b7c290
    void* sub_b7c360(cSpatialObject* obj, void* res);   // 0x00b7c360
    void* sub_b7c480(void* model);                      // 0x00b7c480
    void sub_b7bd50(int a, int b);                      // 0x00b7bd50
    bool sub_b78880(void* value, void* obj, void* res, int flag); // 0x00b78880
    void SetSomething(int value);                       // 0x00b7c160
};
struct PieMgr {
    char  mPad00[0x24];
    void* mpBegin24;            // +0x24
    void* mpEnd28;              // +0x28
    int   sub_703d50(float f, void* pos, void* item);   // 0x00703d50
};
struct PieRoot {
    char    mPad[0x55a4];
    PieMgr* mpPieMgr55a4;       // +0x55a4
};
struct RefSlot {
    void* mpObject;             // +0x00
    void  sub_478db0(void* obj);    // 0x00478db0
};
struct PieItem {
    void** mpVtbl;              // +0x00
    char   pad_04[0x38 - 0x04];
    Vec3_s00b7_bd50   mIds;                // +0x38
    float  mRadius;             // +0x44
    float  mF48;                // +0x48
    float  mF4c;                // +0x4c
    int    mF50;                // +0x50
    void*  mpF54;               // +0x54
    int    mF58;                // +0x58
    int    mF5c;                // +0x5c
    int    mF60;                // +0x60
    int    mF64;                // +0x64
    float  mF68;                // +0x68
    int    mF6c;                // +0x6c
    RefSlot mSlot70;            // +0x70
    int    mF74;                // +0x74
    void*  mpF78;               // +0x78
    int    mF7c;                // +0x7c
    int    mF80;                // +0x80
    int    mF84;                // +0x84
    int    mF88;                // +0x88
};
struct PieNotifyMsg {
    int   mType;                // +0x00
    void* mpUnk;                // +0x04
    void* mpItem;               // +0x08
};
struct SpawnerBase {            // the object owning `this - 4`
    void sub_b77b60(void* table, u32_s00b7_bd50 a, u32_s00b7_bd50 b);   // 0x00b77b60
    void sub_b7a880();                            // 0x00b7a880
    PieItem* sub_b74370();                        // 0x00b74370
};
struct PieObject {
    void*  mpIface;             // +0x00
    u32_s00b7_bd50    mFlags;              // +0x04
    char   pad_08[0x0c - 0x08];
    Vec3_s00b7_bd50   mVecA;               // +0x0c
    char   pad_18[0x34 - 0x18];
    u32_s00b7_bd50    mFlags34;            // +0x34
    char   pad_38[0x40 - 0x38];
    int    mnRefCount;          // +0x40
    char   pad_44[0x58 - 0x44];
    float  mF58;                // +0x58
    char   pad_5c[0x60 - 0x5c];
    int    mF60;                // +0x60
    char   pad_64[0x6c - 0x64];
    u32_s00b7_bd50    mKey6c;              // +0x6c
    union {
        void* mpTarget70;       // +0x70 (kind 4: the spatial object)
        float mPosA[3];         // +0x70
    };
    float  mPosB[3];            // +0x7c
    int    mKind88;             // +0x88
    char   pad_8c[0x90 - 0x8c];
    void*  mpPropertyList;      // +0x90
    void*  sub_b73e70();        // 0x00b73e70
};
extern "C" PieRoot* __cdecl sub_b3d3c0();   // 0x00b3d3c0
struct PieButton {
    char pad_00[0x10];
    int  mId;                    // +0x10
    int  mColor;                 // +0x14
};
struct ButtonVec {
    PieButton* mpBegin;          // +0x00
    PieButton* mpEnd;            // +0x04
    void SetItemTextColor(int id, int color);   // 0x00b7c890
};
struct cPieMenuScreenPosition {
    void** vftable;              // +0x00
    void** vftable2;             // +0x04
    int    mField8;              // +0x08
    cSpatialObject* mpObject;    // +0x0c
    float  mBaseDistance;        // +0x10

    cPieMenuScreenPosition(cSpatialObject* pObject);
    bool GetPosition(float* outX, float* outY);   // 0x00b7cb00
    bool ShouldBeVisible();                        // 0x00b7cb20
};
extern "C" __declspec(noinline) bool __cdecl PieMenu_ScreenPosition_GetPosition(
    cSpatialObject* obj, float* outX, float* outY);
// ---- items of slice s00b7bd50 end

// ---- items of slice s00b7cc60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char uchar;
struct IV_s00b7_cc60 {
    VS(0)  VS(1)  VS(2)  VS(3)  VS(4)  VS(5)  VS(6)  VS(7)
    VS(8)  VS(9)  VS(10) VS(11) VS(12) VS(13) VS(14) VS(15)
    VS(16) VS(17) VS(18) VS(19) VS(20) VS(21) VS(22) VS(23)
    VS(24) VS(25) VS(26) VS(27) VS(28) VS(29) VS(30) VS(31)
    VS(32) VS(33) VS(34) VS(35) VS(36) VS(37) VS(38) VS(39)
    VS(40) VS(41) VS(42) VS(43) VS(44) VS(45) VS(46) VS(47)
    VS(48) VS(49) VS(50) VS(51) VS(52) VS(53) VS(54) VS(55)
    VS(56) VS(57) VS(58) VS(59) VS(60) VS(61) VS(62) VS(63)
    VS(64) VS(65) VS(66) VS(67)
};
#define VT(p, off) (*(void**)((char*)(*(void**)(p)) + (off)))
struct WStr_s00b7_cc60 {
    void* mpBegin;   // +0x00
    void* mpEnd;     // +0x04
    void* mpCap;     // +0x08
    int   f0c;       // +0x0c
    int   f10;       // +0x10
    int   f14;       // +0x14
    void  AllocateSelf(int n);                                  // 0x00429760
    void  assign(const void* begin, const void* end);           // 0x00423650
    WStr_s00b7_cc60* copy(const WStr_s00b7_cc60* src);                                // 0x00b7cfa0
};
void DoInsertValue(void* dst, const void* src, unsigned size);  // 0x011e0744 (memcpy)
struct WVec {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCap;      // +0x08
    void destroy_range(int* begin, int* end);                   // 0x00b7cf10
};
struct AllocHeader { int mSize; };  // eastl allocation header (at mem-4)
void  operator_delete__(void* p);                               // 0x00f47380
void* operator_new(int size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
struct ListNode { ListNode* mpPrev; ListNode* mpNext; void* mpPayload; };
struct ServerObj { char pad[0x2c]; int mMode; bool OnPieMsg(int msg, int arg); };
struct LookupResult {
    int   mField00;          // +0x00
    int   mField04;          // +0x04
    int   mField08;          // +0x08
    uchar mPad0c[4];         // +0x0c
    int   mField10;          // +0x10
};
struct EditorTarget {        // node payload / field30 object
    uchar mPad00[0x13c];     // +0x000
    void* mpField13c;        // +0x13c
};
struct PieVec {              // vector<0x18-byte entry>
    int* mpBegin;            // +0x00
    int* mpEnd;              // +0x04
    int* mpCap;              // +0x08
};
struct PieEntry {            // one 0x18-byte pie entry
    int   mField00;          // +0x00
    uchar mPad04[0x0c];      // +0x04
    int   mField10;          // +0x10
    int   mField14;          // +0x14
};
struct Rect4f { float mLeft, mTop, mWidth, mHeight; };
struct Rect6f { float f0, f1, f2, f3, f4, f5; };
struct Obj188 { void* mpField00; };
struct PieEditor {
    uchar   mPad00[0x1c];    // +0x00
    ListNode mList;          // +0x1c (embedded sentinel)
    uint    mState28;        // +0x28
    uchar   mByte2c;         // +0x2c
    uchar   mFlag2d;         // +0x2d
    uchar   mPad2e[2];       // +0x2e..+0x2f
    void*   mpField30;       // +0x30
};
struct cPlanetModel {
    uchar mPad00[0x24];      // +0x00
    void* mpPlanet24;        // +0x24
    bool  FUN_00b8d8a0(unsigned a, bool refresh, unsigned c);   // 0x00b8d8a0
};
struct cPlanet {
    void SetRampEnabled(bool on);                               // 0x00fbd6b0
};
void* DAT_0168817c;
void* DAT_01688150;
unsigned char DAT_01688154;
void* __cdecl SP_MessageServer();                               // 0x0067dcc0
void* __cdecl SP_PropertyManager();                             // 0x0067de30
int   __cdecl SP_TerrainEditor(int on);
void* __fastcall FUN_00c713e0(void* self);   // 0x00c713e0 (ecx receiver, no stack args)
void* __cdecl FUN_00b3d240();
void* __cdecl FUN_00b8da60();
void  __cdecl FUN_00b8d8a0(void* a, void* b, void* c);
void  __cdecl FUN_00b8c0f0();
void  __cdecl FUN_00f67890(void* p);
void  __cdecl FUN_00f678b0(void* p);
void  __cdecl FUN_00c70110(void* p);
void  __cdecl FUN_00f355b0(void* p);
void* __cdecl FUN_0067dd50();
void  __cdecl FUN_01037a20(void* p);
void  __cdecl FUN_00818330();
void  __cdecl FUN_00817eb0(void* fn, void* arg);
void  __cdecl FUN_008182c0(void* fn, void* arg);
void  __cdecl FUN_0081a940(int a, int b, int c, int d);
void  __cdecl FUN_00819ad0(void* a, void* b, void* c, int d);
void  __cdecl FUN_00804ed0(void* a, void* b);
void  __cdecl FUN_007c4180(void* a, void* b);
void  __cdecl FUN_00805ea0(void* out);
void  __cdecl FUN_00b7c790();
void  __cdecl FUN_00b7c750();
void* __cdecl SPUIPieMenu_ctor(void* mem);
void* __cdecl SPUIPieMenuScreenPos_ctor(void* mem, int* arg);
int  __cdecl FUN_00b7cf50(int* begin, int* end, int dest);
int* __cdecl FUN_00b7d000(int* src, int* end, int* dst);
int* __cdecl FUN_00b7d120(int* first, int* last, int* outLast);
void __fastcall FUN_00b7d180(int* vec, int /*edx unused*/, int* pos, int* value);
void __fastcall FUN_00b7d7b0(ListNode** p);
// ---- items of slice s00b7cc60 end

// @ 0x00b707a0
unsigned __thiscall MissionMgr::HintClear(unsigned id)
{
    HashIt it;
    ((HashFind*)&mStrategyMap)->find(&it, &id);
    unsigned val = (unsigned)it.node;
    if (it.node != mStrategyMap.mpBucket[mStrategyMap.mnBucketCount]) {
        MissionStrategy* s = *(MissionStrategy**)((char*)it.node + 4);
        if (s) {
            s->Step();
            TutorialMission* t = (TutorialMission*)s->Cast(0xd4066db3);
            if (t) {
                void* next = t->GetNextMission();
                if (next) Hint((unsigned)next);
            }
            val = this->g28(0);
        }
    }
    return val & 0xffffff00u;
}

// @ 0x00b70820
void* __fastcall FUN_00b70820(MotiveObject* self)
{
    FUN_00b5b6c0(self);

    self->m_vtable10 = (void*)0x013eb384;
    self->m_vtable0  = (void*)0x01464e18;
    self->m_vtable8  = (void*)0x01464df4;
    self->m_vtable10 = (void*)0x01464de4;

    self->m_field14 = 0;
    self->m_field18 = 0;
    self->m_field1c = 0;
    self->m_field38 = 1.0f;
    self->m_field3c = 2.0f;
    self->m_field34 = 0;
    self->m_field40 = 0;
    self->m_field30 = 1;
    self->m_field2c = (void*)0x0154df28;

    self->m_field58 = 1.0f;
    self->m_field5c = 2.0f;
    self->m_field54 = 0;
    self->m_field60 = 0;
    self->m_field50 = 1;
    self->m_field4c = (void*)0x0154df28;

    self->m_field68 = 0;
    self->m_field6c = 0;
    self->m_field70 = 1;
    return self;
}

// @ 0x00b708d0
void cTuning_b708d0::Load(uint32_t instanceID)
{
    int index = 1;
    if (NounManager()) {
        cTerrainSphere* sphere = NounManager()->GetCurrentTerrainSphere();
        if (sphere)
            index = sphere->GetIndex();
    }
    cPropertyManager* pm = PropertyManager();
    ResetList(g_TuningList);
    if (!pm->GetPropertyList(g_TerrainPropIDs[index], instanceID, g_TuningList))
        return;

    TF(0x015a2e6a, f04);
    TF(0x015a2e78, f00);
    TF(0x015a2e80, f08);
    TF(0x015a2e81, f0c);
    TF(0x015a2e82, f10);
    TF(0x015a2e83, f14);
    TF(0x046dc07f, f18);
    TF(0x046dc080, f1c);
    TF(0x046dc081, f20);
    TF(0x046dc082, f24);
    TF(0x046dc088, f28);
    TF(0x046dbf25, f34);
    TF(0x046dbf26, f38);
    TF(0x046dbf27, f3c);
    TF(0x015a2ea2, f2c);
    TF(0x046dc280, f30);
    TF(0x7105cce0, f40);
    TF(0xb1cb9c62, f44);
    TF(0x71dbb4ba, f48);
    TF(0x046dd2d0, f54);
    TF(0x046dd2d1, f58);
    TF(0x046dd2d2, f4c);
    TF(0x046dd2d3, f50);
    TF(0x7063d568, f5c);
    TF(0x70627ff6, f64);
    TU(0x90627ffa, u68);
    TF(0xd0627ffd, f6c);
    TU(0xd0628000, u70);
    TF(0x307b704e, f74);
    TU(0x907b7054, u78);
    TF(0x307b705a, f7c);
    TU(0x907b705e, u80);
    TF(0x30628002, f84);
    TU(0xd0628004, u88);
    TF(0x3063d320, f8c);
    TF(0xd063d3fb, f90);
    TF(0xf063d415, f94);
    TF(0xb063d44d, f98);
    TF(0xb063d417, f9c);
    TF(0xf063d418, fa0);
    TF(0xd063d44c, fa4);
    TF(0xb063d44d, fa8);
    TF(0xf063d44e, fac);
    TF(0x7063d44f, fb0);
    TF(0x3063d451, fb4);
    TF(0x7063d452, fb8);
    TF(0x1063d453, fbc);
    TF(0x1063d480, fc0);
    TF(0x1063d481, fc4);
    TF(0xd063d482, fc8);
    TF(0x9064f465, f60);
}

// @ 0x00b714a0
void cTuning_b708d0::SerializeObject(void* object)
{
    void* writer = ((void* (__thiscall*)(void*))VTFN(object, 0x20 / 4))(object);
    void* stream = ((void* (__thiscall*)(void*))VTFN(writer, 0x18 / 4))(writer);
    uint32_t id = 0x6ef3ce7;
    WriteUint32(stream, &id, 1, 0);
    cVarListSerializer serializer;
    serializer.ctor(this, (void*)0x0156b308, 0x01a80d26);
    serializer.Serialize(object);
}

// @ 0x00b71510
bool MotiveObjectTree::findEvent(void* event)
{
    if (event)
        ((void (__thiscall*)(void*))VTFN(event, 0xbc / 4))(event);

    void* it = 0;
    void** slot = ((RBTreeFind*)&m_map)->find(&it, &event);
    bool found = *slot != (void*)&m_map.m_end;

    if (event)
        ((void (__thiscall*)(void*))VTFN(event, 0xc0 / 4))(event);
    return found;
}

// @ 0x00b71570
bool __cdecl FUN_00b71570(void* arg, MapView* map)
{
    TreeNode* const end = (TreeNode*)&map->m_end;
    for (TreeNode* node = map->m_begin; node != end;
         node = (TreeNode*)FUN_00921580(node)) {
        if (node->m_ref10 != 0)
            ((void (__thiscall*)(void*, void*))VTFN(node->m_ref10, 0x1c / 4))(node->m_ref10, arg);
        if (node->m_ref14 != 0)
            ((void (__thiscall*)(void*, void*))VTFN(node->m_ref14, 0x1c / 4))(node->m_ref14, arg);
    }
    return true;
}

// @ 0x00b715c0
void* NodeFactory::newNode(RefPair* pair)
{
    NewNode* node = (NewNode*)FUN_00f473a0(
        0x18, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
        0xd1);
    if (node != 0) {
        node->m_ref10 = pair->m_first;
        if (node->m_ref10 != 0)
            ((void (__thiscall*)(void*))VTFN(node->m_ref10, 0xbc / 4))(node->m_ref10);

        node->m_ref14 = pair->m_second;
        if (node->m_ref14 != 0)
            ((void (__thiscall*)(void*))VTFN(node->m_ref14, 0))(node->m_ref14);
    }
    return node;
}

// @ 0x00b71680
void FUN_00b71680(void* serial, MotiveMap* map)
{
    uint32_t count = (uint32_t)map->m_size;
    void* writer = ((void* (__thiscall*)(void*))VTFN(serial, 0x20 / 4))(serial);
    void* stream = ((void* (__thiscall*)(void*))VTFN(writer, 0x18 / 4))(writer);
    WriteUint32(stream, &count, 1, 0);

    void* const end = (char*)map + 4;
    for (void* node = map->m_begin; node != end;
         node = FUN_00921580(node)) {
        void* value = 0;
        void* ref = *(void**)((char*)node + 0x10);
        if (ref)
            value = ((void* (__thiscall*)(void*, int))VTFN(ref, 0xb8 / 4))(ref, 0x179c807);
        ((void (__thiscall*)(void*, void*))VTFN(serial, 0x2c / 4))(serial, value);
        ((void (__thiscall*)(void*))VTFN(serial, 0x1c / 4))(serial);

        value = 0;
        ref = *(void**)((char*)node + 0x14);
        if (ref)
            value = ((void* (__thiscall*)(void*, int))VTFN(ref, 0x0c / 4))(ref, 0x179c807);
        ((void (__thiscall*)(void*, void*))VTFN(serial, 0x2c / 4))(serial, value);
        ((void (__thiscall*)(void*))VTFN(serial, 0x1c / 4))(serial);
    }
    ((void (__thiscall*)(void*))VTFN(serial, 0x1c / 4))(serial);
}

// @ 0x00b71730
void MotiveMap::erase(void** out, TreeNode* node)
{
    m_size--;
    TreeNode* next = (TreeNode*)FUN_00921580(node);
    FUN_00921880(node, &m_end);

    if (node->m_ref14 != 0)
        ((void (__thiscall*)(void*))VTFN(node->m_ref14, 4 / 4))(node->m_ref14);
    if (node->m_ref10 != 0)
        ((void (__thiscall*)(void*))VTFN(node->m_ref10, 0xc0 / 4))(node->m_ref10);

    FUN_00f47380(node);
    *out = next;
}

// @ 0x00b71790
void MotiveMap::deleteTree(TreeNode* node)
{
    while (node != 0) {
        deleteTree(node->m_left);
        TreeNode* next = node->m_right;

        void* ref14 = node->m_ref14;
        if (ref14 != 0)
            ((void (__thiscall*)(void*))VTFN(ref14, 4 / 4))(ref14);
        void* ref10 = node->m_ref10;
        if (ref10 != 0)
            ((void (__thiscall*)(void*))VTFN(ref10, 0xc0 / 4))(ref10);

        FUN_00f47380(node);
        node = next;
    }
}

// @ 0x00b71a30
void __fastcall FUN_00b71a30(MotiveObjectTree* self)
{
    MotiveMap* map = &self->m_map;
    map->deleteTree((TreeNode*)map->m_root);
    map->m_begin = &map->m_end;
    map->m_end = &map->m_end;
    map->m_root = 0;
    map->m_flag10 = 0;
    map->m_size = 0;
}

// @ 0x00b71a60
void cOwner::ReadFeedback(IStream* pStream)
{
    mFeedback.Purge((FeedbackNode*)mFeedback.mAnchor.mpNodeParent);

    eastl::nb* pAnchor = &mFeedback.mAnchor;
    pAnchor->mpNodeRight  = pAnchor;
    pAnchor->mpNodeLeft   = pAnchor;
    pAnchor->mpNodeParent = 0;
    pAnchor->mColor       = 0;
    mFeedback.mnSize = 0;

    int count;
    cDevice* pDevice = (cDevice*)pStream->Slot8();
    void* pRaw = pDevice->GetStream();
    SP_ReadInt32(pRaw, &count, 1, 0);

    cVarListSerializer_s00b7_1a60 serializer(this, &DAT_0156b308, 0x1a80d26);
    serializer.Serialize(*pStream);
}

// @ 0x00b71af0
void cOwner::RemoveFeedback(IStream* pStream)
{
    void* pObj = pStream->Slot12();           // 0x30/4 = 12
    void* pKey = pObj ? ((IStream*)pObj)->Cast(0x1186577) : 0;
    if (pKey)
        ((IStream*)pKey)->AddRefSlot();        // 0xbc/4 = 47

    uint32_t key = (uint32_t)pKey;
    FeedbackNode* it;
    TreeFind(&it, &mFeedback, &key);

    if (pKey)
        ((IStream*)pKey)->ReleaseSlot();       // 0xc0/4 = 48

    if (it != (FeedbackNode*)&mFeedback.mAnchor) {
        void* pNoun = it->mpEvent;
        SP_NounManager()->RemoveNoun(pNoun);
        TreeErase(&it, it);
    }
}

// @ 0x00b71b90
void __cdecl Fn_00b71b90(IStream* pStream, FeedbackTree* pTree)
{
    pTree->Purge((FeedbackNode*)pTree->mAnchor.mpNodeParent);

    eastl::nb* pAnchor = &pTree->mAnchor;
    pAnchor->mpNodeRight  = pAnchor;
    pAnchor->mpNodeLeft   = pAnchor;
    pAnchor->mpNodeParent = 0;
    pAnchor->mColor       = 0;
    pTree->mnSize = 0;

    uint32_t count = 0;
    cDevice* pDevice = (cDevice*)pStream->Slot8();
    void* pRaw = pDevice->GetStream();
    SP_ReadInt32(pRaw, &count, 1, 0);

    uint32_t i = 0;
    if (count != 0) {
        do {
            void* pTemp = 0;
            pStream->Slot10();                       // read entry under 0x1186577
            pStream->Slot7();                        // release scratch
            pTemp = 0;

            void* pEvent = 0;
            pStream->Slot10();                       // read entry under 0x6ef0ec9
            pStream->Slot7();
            pEvent = 0;

            if (pEvent)
                ((IStream*)pEvent)->Slot11();        // AddRef

            // insert into the tree (0x00b717f0)
            void* pResult[3];
            TreeHintInsert((FeedbackNode**)pResult, pTree, (uint32_t*)&pEvent);
            if (!*(bool*)((char*)pResult + 8)) {
                FeedbackNode* pNode = *(FeedbackNode**)pResult;
                void* pOld = pNode->mpEvent;
                if (pEvent != pOld) {
                    if (pEvent)
                        ((IStream*)pEvent)->Slot0();
                    pNode->mpEvent = pEvent;
                    if (pOld) ((IStream*)pOld)->Slot1();
                }
            }

            if (pEvent)
                ((IStream*)pEvent)->Slot12();        // Release
            ++i;
        } while (i < count);
    }
    pStream->Slot7();
}

// @ 0x00b71dc0
cOwner::cOwner()
{
    eastl::nb* pAnchor = &mFeedback.mAnchor;
    pAnchor->mpNodeLeft   = 0;
    pAnchor->mpNodeParent = 0;
    pAnchor->mColor       = 0;
    pAnchor->mpNodeLeft   = pAnchor;
    pAnchor->mpNodeRight  = pAnchor;
    pAnchor->mpNodeParent = 0;
    pAnchor->mColor       = 0;
    mFeedback.mnSize      = 0;
}

// @ 0x00b71e40
FeedbackNode* __cdecl Fn_00b71e40(FeedbackTree* pTree, uint32_t* pKey)
{
    eastl::nb* pAnchor = &pTree->mAnchor;
    eastl::nb* pLower = pAnchor;
    eastl::nb* pCurrent = pTree->mAnchor.mpNodeParent;
    while (pCurrent) {
        if (((FeedbackNode*)pCurrent)->mKey < *pKey)
            pCurrent = pCurrent->mpNodeRight;
        else {
            pLower = pCurrent;
            pCurrent = pCurrent->mpNodeLeft;
        }
    }
    if (pLower == pAnchor || *pKey < ((FeedbackNode*)pLower)->mKey) {
        void** ppValue = (void**)pKey;
        if (*ppValue)
            ((IStream*)*ppValue)->AddRefSlot();      // 0xbc
        void* pResult[3];
        TreeInsertUnique(pResult, (FeedbackNode*)pLower, (const void**)ppValue, 0);
        if (*ppValue)
            ((IStream*)*ppValue)->ReleaseSlot();     // 0xc0
        pLower = *(eastl::nb**)pResult;
    }
    return (FeedbackNode*)((char*)pLower + 0x14);
}

// @ 0x00b71ee0
void __cdecl Fn_00b71ee0(int nMilliseconds)
{
    float fSeconds = (float)nMilliseconds * 0.001f;
    // (the original scale constants are read from globals)

    double dElapsed = 0.0;           // filled from the game-time clock below
    cGameDataVector* pVec =
        SP_NounManager()->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                            (void*)0x00b71d40, (void*)0x00b1e500, 0x6ef0f11);
    for (void** it = pVec->mpBegin; it != pVec->mpEnd; ++it)
        Fn_00c696a0(*it, fSeconds, dElapsed);
}

// @ 0x00b71fb0
void* __cdecl Fn_00b71fb0(cFeedbackEvent* pSource, uint32_t arg)
{
    void* pNoun = SP_NounManager()->CreateNoun(0x6ef0f11);
    cFeedbackEvent* pEvent = pNoun ? (cFeedbackEvent*)((IStream*)pNoun)->Cast(0x6ef0ec9) : 0;

    void* pParam = pSource ? ((IStream*)pSource)->Slot46(0x17f243b) : 0;
    Fn_00c69760(pParam, arg);

    void* pSlot = (void*)((char*)pEvent + 0x34);
    ((IStream*)pSlot)->Slot14(((IStream*)pSource)->Slot11());  // set object id (slot 0x38)

    ((IStream*)pSource)->AddRefSlot();                         // vtable+0xbc

    FeedbackNode* pNode = Fn_00b71e40(&((cOwner*)pSource)->mFeedback, (uint32_t*)&pEvent);
    if (pEvent != (cFeedbackEvent*)pNode->mpEvent) {
        ((IStream*)pEvent)->Slot0();
        void* pOld = pNode->mpEvent;
        pNode->mpEvent = pEvent;
        if (pOld) ((IStream*)pOld)->Slot1();
    }
    ((IStream*)pSource)->ReleaseSlot();                         // vtable+0xc0
    return pEvent;
}

// @ 0x00b72080
void cObjectPool::Init(int nStride, int nCapacity)
{
    mpData     = (char*)operator new(nStride * nCapacity, kPoolName, 0, 0, 0, 0);
    mCapacity  = nCapacity;
    mStride    = nStride;
    mUsed      = 0;
    mHighWater = 0;
    mNextHandle = (uint32_t)gPoolCounter << 8;
    ++gPoolCounter;
    mFreeHead  = -1;
}

// @ 0x00b720e0
void cObjectPool::Destroy()
{
    if (mpData && mpData != (char*)0xbaad) {
        operator delete(mpData);
        mpData = (char*)0xbaad;
    }
}

// @ 0x00b72110
void cObjectPool::Reset()
{
    mUsed = 0;
    mHighWater = 0;
    mFreeHead = -1;
}

// @ 0x00b72120
__declspec(noinline) void __fastcall cObjectPool::Advance(int* pIndex, cObjectPool* pPool)
{
    if (*pIndex != -1) {
        if (*pIndex < pPool->mHighWater) {
            do {
                uint32_t* pSlot = (uint32_t*)&pPool->mpData[pPool->mStride * *pIndex];
                if ((int)(*pSlot & 0xffff) == *pIndex)
                    return;
                *pIndex = *pIndex + 1;
            } while (*pIndex < pPool->mHighWater);
        }
        *pIndex = -1;
    }
}

// @ 0x00b72160
uint32_t cObjectPool::Alloc()
{
    int used = mUsed;
    int high = mHighWater;
    uint32_t index;
    uint32_t* pSlot;
    if (used == high) {
        if (used == mCapacity)
            return 0;
        index = (uint32_t)used;
        pSlot = (uint32_t*)&mpData[(size_t)mStride * (size_t)used];
        mHighWater = high + 1;
    } else {
        index = (uint32_t)mFreeHead;
        pSlot = (uint32_t*)&mpData[(size_t)mStride * (size_t)index];
        mFreeHead = (int)*pSlot;
    }
    ++mNextHandle;
    mUsed = used + 1;
    uint32_t handle = (mNextHandle << 16) | index;
    memset(pSlot, 0, (size_t)mStride);
    *pSlot = handle;
    return handle;
}

// @ 0x00b721d0
void* cObjectPool::Get(uint32_t handle)
{
    if (handle == 0)
        return 0;
    if ((int)(handle & 0xffff) > mHighWater)
        return 0;
    uint32_t* pSlot = (uint32_t*)&mpData[mStride * (handle & 0xffff)];
    return (*pSlot != handle) ? 0 : pSlot;
}

// @ 0x00b72210
void* cObjectPool::At(uint32_t index)
{
    return &mpData[mStride * (index & 0xffff)];
}

// @ 0x00b72230
void* cObjectPool::Next(int* pIndex)
{
    Advance(pIndex, this);
    uint32_t i = (uint32_t)*pIndex;
    if (i == (uint32_t)-1)
        return 0;
    void* pResult = &mpData[mStride * i];
    *pIndex = (int)(i + 1);
    return pResult;
}

// @ 0x00b72260
void cObjectPool::Free(uint32_t handle)
{
    uint32_t* pSlot = (uint32_t*)&mpData[mStride * (handle & 0xffff)];
    *pSlot = (uint32_t)mFreeHead;
    --mUsed;
    mFreeHead = (int)(handle & 0xffff);
}

// @ 0x00b72290
bool __cdecl Fn_00b72290(const float* pA, const float* pB)
{
    return (pA[0] * pA[0] + pA[1] * pA[1] + pA[2] * pA[2]) <
           (pB[0] * pB[0] + pB[1] * pB[1] + pB[2] * pB[2]);
}

// @ 0x00b72320
uint32_t cGameModeManager::GetScriptId()
{
    switch (mField88) {
    case 0:  return 0x3a8be428;
    case 1:  return 0x029c388a;
    case 2:  return 0x6d60a1cc;
    default: return 0;
    }
}

// @ 0x00b72370
void cMessageListener::Register(void)
{
    cMessagingServer* pServer = EA_Messaging_GetServer();
    void* pOwner = (char*)this - 4;
    mpServer = pServer;
    mpOwner  = pOwner;
    mpIds    = gMessageIds;
    mCount   = 8;
    mState   = 0;
    if (pServer && pOwner) {
        unsigned uOffset = 0;
        do {
            pServer->Slot9((unsigned)pOwner, *(unsigned*)((char*)gMessageIds + uOffset));
            uOffset += 4;
        } while (uOffset < 0x20);
    }
}

// @ 0x00b72410
uint64_t __stdcall Fn_00b72410(uint32_t a, uint32_t b)
{
    return ((uint64_t)a << 32) | b;
}

// @ 0x00b72430
char* __cdecl Fn_00b72430(char* first, char* last, char (*pPred)(char*, char*))
{
    if (first != last) {
        char* p = first + 0xc;
        if (p != last) {
            do {
                if (pPred(first, p))
                    return first;
                first = p;
                p += 0xc;
            } while (p != last);
        }
    }
    return last;
}

// @ 0x00b72520
void cXform::PreRotateXYZ(float a, float b, float c)
{
    this->PreRotateY(a);
    this->PreRotateX(b);
    this->RotateY(c);
}

// @ 0x00b72560
bool __cdecl Fn_00b72560(const float* pA, const float* pB)
{
    return *pB > *pA;
}

// @ 0x00b72580
bool __cdecl Fn_00b72580(const float* pA, const float* pB)
{
    return pB[1] > pA[1];
}

// @ 0x00b725a0
bool __cdecl Fn_00b725a0(const float* pA, const float* pB)
{
    return fabsf(pA[0] - pB[0]) < 0.001f && fabsf(pA[1] - pB[1]) < 0.001f;
}

// @ 0x00b725e0
void cGridEntryOwner::SetActive(bool bActive)
{
    cHierGrid* pGrid = Fn_00b3d3c0()->mpGrid;
    if (!pGrid)
        return;
    if (bActive) {
        if (mHandle >= 0 || pGrid->mpBegin == pGrid->mpEnd)
            return;
        unsigned owner = (unsigned)this;
        unsigned key   = (unsigned)mKey;
        float    radius = mField48;
        mHandle = (int)pGrid->CreateEntry(radius, key, owner);
    } else {
        if (mHandle < 0)
            return;
        if (pGrid->mpBegin != pGrid->mpEnd)
            pGrid->Remove((unsigned)mHandle);
        mHandle = -1;
    }
}

// @ 0x00b72640
void cModeTuning::UpdateFromGameMode(void* pArg)
{
    cPropertyList* pList = GameModeMgr_GetPropertyList(pArg);
    if (!pList)
        return;
    pList->Slot0();

    mField5480 = gTune_0156b390;
    mField5484 = gTune_0156b394;
    mField5488 = gTune_0156b398;
    mField548c = gVec_016880d4;
    mField5490 = gVec_016880d8;
    mField5494 = gVec_016880dc;
    mField5498 = gTune_0156b39c;
    mField549c = gTune_0156b3a0;
    mField54a0 = gTune_0156b3a4;
    mField54a4 = gTune_0156b3a8;

    cProp* pProp = 0;
    if (pList->GetProperty(0x4d04a47, &pProp) && pProp->mType == 0xd)
        mField5480 = *Property_GetFloat(pProp);
    if (pList->GetProperty(0x27b6c6e, &pProp) && pProp->mType == 0xd)
        mField5484 = *Property_GetFloat(pProp);
    if (pList->GetProperty(0x27b6d2a, &pProp) && pProp->mType == 0xd)
        mField5488 = *Property_GetFloat(pProp);

    SP_GetPropertyAsVector3(pList, 0x27b6d44, &mField548c);

    if (pList->GetProperty(0x55c1350, &pProp) && pProp->mType == 0xd)
        mField5498 = *Property_GetFloat(pProp);
    if (pList->GetProperty(0x55c1357, &pProp) && pProp->mType == 0xd)
        mField549c = *Property_GetFloat(pProp);
    if (pList->GetProperty(0x56bf073, &pProp) && pProp->mType == 0xd)
        mField54a0 = *Property_GetFloat(pProp);
    if (pList->GetProperty(0x5b59e03, &pProp) && pProp->mType == 0xd)
        mField54a4 = *Property_GetFloat(pProp);

    pList->Release();
}

// @ 0x00b72870
void cFlagObject::SetFlag2()
{
    mFlags |= 2;
}

// @ 0x00b72880
void cFlagObject::ClearFlag2()
{
    mFlags &= ~2u;
}

// @ 0x00b72890
bool __cdecl Fn_00b72890(const float* pA0, float fA1, const float* pDirA, const float* pB0, const float* pDirB, float fThickness, float fMaxDist, char bClamp, float* pOut)
{
    float a0[3];
    float a1[3];
    if (!ClosestPointsOnSegments(pA0, pDirA, pB0, pDirB, fThickness, fMaxDist, a0, a1))
        return false;

    *pOut = 0.0f;
    if (a0[0] > fA1)
        return false;
    if (bClamp) {
        float dot = pDirA[0] * (pB0[0] - pA0[0]) + pDirA[1] * (pB0[1] - pA0[1]) +
                    pDirA[2] * (pB0[2] - pA0[2]);
        if (dot > fA1)
            return false;
    }

    float ax = pA0[0] + pDirA[0] * a0[0];
    float ay = pA0[1] + pDirA[1] * a0[0];
    float az = pA0[2] + pDirA[2] * a0[0];

    float dx = ax - pB0[0];
    float dy = ay - pB0[1];
    float dz = az - pB0[2];
    float inv = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz + gEps13ec4b8);

    float ux = dx * inv, uy = dy * inv, uz = dz * inv;
    float proj = pDirB[0] * ux + pDirB[1] * uy + pDirB[2] * uz;
    float px = ux - pDirB[0] * proj;
    float py = uy - pDirB[1] * proj;
    float pz = uz - pDirB[2] * proj;

    float s = pDirA[0] * px + pDirA[1] * py + pDirA[2] * pz;
    px -= pDirA[0] * s;
    py -= pDirA[1] * s;
    pz -= pDirA[2] * s;

    float len = sqrtf(px * px + py * py + pz * pz);
    float t = (len - fThickness * 0.5f) / (fThickness - fThickness * 0.5f);
    if (t < 0.0f)
        t = 0.0f;
    if (t > 1.0f)
        t = 1.0f;
    *pOut = 1.0f - t;
    return true;
}

// @ 0x00b72b60
uint Sim::FUN_00b72b60(V3* a, V3* b, float c, Op* obj, char flag, float* outDist, bool* outFlag)
{
    int   n    = obj->mType;
    float len  = sqrtf(obj->x * obj->x + obj->y * obj->y + obj->z * obj->z) + g_eps;
    float ninv = 1.0f / len;
    V3    nrm;                               // normalized obstacle position
    nrm.x = obj->x * ninv;
    nrm.y = obj->y * ninv;
    nrm.z = obj->z * ninv;

    float bl   = sqrtf(b->x * b->x + b->y * b->y + b->z * b->z);
    float binv = 1.0f / (bl + g_eps);
    V3    dir;                               // normalized query direction
    dir.x = b->x * binv;
    dir.y = b->y * binv;
    dir.z = b->z * binv;

    float al = sqrtf(a->x * a->x + a->y * a->y + a->z * a->z);

    bool  near;                              // the obstacle reaches the query ray
    float pad;
    if (n != 0 || al < obj->mRadius * g_fb4 + len) {
        near = false; pad = g_fc0;
    } else {
        near = true;  pad = g_fbc;
    }

    float scale;
    if (n < 3)
        scale = near ? g_fb8 : mScale[n];
    else
        scale = 0.0f;

    char u8 = (near || flag == 0) ? 0 : 1;

    float dist = ((((obj->mDistMax - obj->mDistMin) * scale) + obj->mDistMin) + pad) + c;
    float lim  = obj->mRadius + pad;

    // the obstacle position doubles as the segment point handed to the test
    uint r = FUN_00b72890(a, bl, &dir, (const V3*)&obj->x, &nrm, dist, lim, u8, outDist);
    if ((char)r == 0) {
        *outDist = 0.0f;
        return r & 0xffffff00u;              // retail only clears al here
    }
    if (al < m5498 * obj->mRadius + len) {
        *outFlag = false;
        return 1;
    }
    *outFlag = true;
    return 1;
}

// @ 0x00b72d80
HIt* HIt::advance(HIt* out, int)
{
    out->mpNode = mpNode;
    out->mpBucket = mpBucket;
    mpNode = mpNode->mpNext;
    while (!mpNode) {
        ++mpBucket;
        mpNode = *mpBucket;
    }
    return out;
}

// @ 0x00b72dc0
K12* FUN_00b72dc0(K12* first, K12* last, Pred12 pred)
{
    K12* r = FUN_00b72430(first, last, pred);
    if (r != last) {
        K12* result = r;
        while (++r != last) {
            if (!pred(result, r)) {
                ++result;
                *result = *r;
            }
        }
        return ++result;
    }
    return last;
}

// @ 0x00b72f10
LNode* __stdcall FUN_00b72f10(LNode* p, const uint* key, uint)
{
    if (p) {
        do {
            if (key[0] == p->k0 && key[1] == p->k1 && key[2] == p->k2) return p;
            p = p->mpNext;
        } while (p);
    }
    return 0;
}

// @ 0x00b73010
Node1c* __stdcall FUN_00b73010(const Key24* src)
{
    Node1c* n = (Node1c*)EAAllocate(0x1c, "Simulator", 0, 0, "allocator.h", 0xd1);
    if (n)
        n->key = *src;
    n->f18 = 0;
    return n;
}

// @ 0x00b73200
void FUN_00b73200(K12* first, K12* last, Pred12 pred)
{
    if (first == last)
        return;
    K12* iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        K12 temp = *iSorted;
        K12* iNext = iSorted;
        if (iSorted != first) {
            do {
                if (!pred(&temp, iNext - 1))
                    break;
                *iNext = *(iNext - 1);
                --iNext;
            } while (iNext != first);
        }
        *iNext = temp;
        ++iSorted;
    } while (iSorted != last);
}

// @ 0x00b732a0
void FUN_00b732a0(K12* first, K12* last, Pred12 pred)
{
    for (K12* current = first; current != last; ++current) {
        K12* end = current;
        K12* prev = current - 1;
        K12 value = *current;
        while (pred(&value, prev)) {
            *end = *prev;
            --end;
            --prev;
        }
        *end = value;
    }
}

// @ 0x00b73350
void FUN_00b73350(Op** first, Op** last, float x, float y, float z)
{
    if (first == last)
        return;
    Op** iSorted = first + 1;
    if (iSorted == last)
        return;
    do {
        Op* value = *iSorted;
        Op** iNext = iSorted;
        if (iSorted != first) {
            float dx = x - value->x;
            float dx2 = dx * dx;
            float dy = y - value->y;
            float dy2 = dy * dy;
            float dz = z - value->z;
            float dv = dy2 + dx2 + dz * dz;
            do {
                Op* prev = *(iNext - 1);
                float ex = x - prev->x;
                float ey = y - prev->y;
                float ez = z - prev->z;
                float ep = ez * ez + ey * ey + ex * ex;
                if (!(ep > dv))
                    break;
                *iNext = prev;
                --iNext;
            } while (iNext != first);
        }
        *iNext = value;
        ++iSorted;
    } while (iSorted != last);
}

// @ 0x00b73420
void FUN_00b73420(Op** first, Op** last, float x, float y, float z)
{
    for (Op** i = first; i != last; ++i) {
        Op* value = *i;
        Op** end = i;
        Op** prev = i - 1;
        float dx = x - value->x, dy = y - value->y, dz = z - value->z;
        float dv = dy * dy + dx * dx + dz * dz;
        while (1) {
            Op* p = *prev;
            float ex = x - p->x, ey = y - p->y, ez = z - p->z;
            if (ez * ez + ey * ey + ex * ex <= dv)
                break;
            *end = p;
            --end;
            --prev;
        }
        *end = value;
    }
}

// @ 0x00b734e0
Op** FUN_00b734e0(Op** a, Op** b, Op** c, float x, float y, float z)
{
    Op* o1 = *a;
    Op* o2 = *b;
    float d1 = (y - o1->y) * (y - o1->y) + (x - o1->x) * (x - o1->x) + (z - o1->z) * (z - o1->z);
    float d2 = (y - o2->y) * (y - o2->y) + (x - o2->x) * (x - o2->x) + (z - o2->z) * (z - o2->z);
    if (d2 <= d1) {
        Op* o3 = *c;
        float d3 = (y - o3->y) * (y - o3->y) + (x - o3->x) * (x - o3->x) + (z - o3->z) * (z - o3->z);
        if (d1 < d3)
            return a;
        if (d2 < d3)
            return c;
    } else {
        Op* o3 = *c;
        float d3 = (y - o3->y) * (y - o3->y) + (x - o3->x) * (x - o3->x) + (z - o3->z) * (z - o3->z);
        if (d3 <= d2) {
            if (d3 <= d1)
                return a;
            return c;
        }
    }
    return b;
}

// @ 0x00b73780
E18* FUN_00b73780(E18* first, E18* last, E18* dst)
{
    for (; first != last; ++first, ++dst)
        if (dst)
            *dst = *first;
    return dst;
}

// @ 0x00b737d0
void FUN_00b737d0(T0c* first, int top, int len, int pos, T0c value, Cmp0c cmp)
{
    int child = pos * 2 + 2;
    while (child < len) {
        if (cmp(&first[child], &first[child - 1]))
            --child;
        first[pos] = first[child];
        pos = child;
        child = pos * 2 + 2;
    }
    if (child == len) {
        first[pos] = first[child - 1];
        pos = child - 1;
    }
    FUN_00ba6800b(first, top, pos, value.a, value.b, value.c, cmp);
}

// @ 0x00b73890
E10** FUN_00b73890(E10** out, E10* first, E10* last, E10* dst)
{
    *out = dst;
    if (first != last) {
        do {
            if (dst)
                *dst = *first;
            ++first;
            ++dst;
        } while (first != last);
        *out = dst;
    }
    return out;
}

// @ 0x00b738e0
void FUN_00b738e0(E10* dst, uint n, const E10* src)
{
    for (; n; --n, ++dst)
        if (dst)
            *dst = *src;
}

// @ 0x00b73920
void FUN_00b73920(Op** first, int top, int pos, Op* value, float x, float y, float z)
{
    if (pos <= top) {
        first[pos] = value;
        return;
    }
    float dx = x - value->x, dy = y - value->y, dz = z - value->z;
    float dv = (dz * dz + dy * dy) + dx * dx;
    for (int parent = (pos - 1) >> 1; pos > top; parent = (pos - 1) >> 1) {
        Op* pv = first[parent];
        float ex = x - pv->x, ey = y - pv->y, ez = z - pv->z;
        if (!(dv > (ey * ey + ex * ex) + ez * ez))
            break;
        first[pos] = pv;
        pos = parent;
    }
    first[pos] = value;
}

// @ 0x00b739f0
E10* FUN_00b739f0(E10* first, E10* last, E10* dst)
{
    for (; first != last; ++first, ++dst)
        if (dst)
            *dst = *first;
    return dst;
}

// @ 0x00b73a30
cObstacle::cObstacle()
: cGameData() {
    m34 = 0;
    m38 = g_px; m3c = g_py; m40 = g_pz;
    m44 = 0.0f; m48 = 0.0f; m4c = 0.0f;
    m50 = -1;
    m54 = 0;
    m58 = 0;
    m60 = 0;
    m6c = 0;
    m5c = -1;
    m64 = -1;
    m68 = g_one;
    m70 = 0;
    m74 = 0;
    m78 = 0;
    m7c = g_i0; m80 = g_i1; m84 = g_i2;
    m88 = 0;
}

// @ 0x00b73b30
cObstacle::~cObstacle()
{
    ReleaseRc(m78);
    ReleaseRc(m70);
    if (m54)
        ((IV*)m54)->vs14();
}

// @ 0x00b73bc0
void cObstacle::Reset0()
{
    SetGameDataOwner(0);
    m60 = g_cnt;
    ++g_cnt;
    m38 = g_px; m3c = g_py; m40 = g_pz;
    m44 = 0.0f; m48 = 0.0f; m4c = 0.0f;
    m68 = g_one;
    m6c = 0;
    m74 = 0;
    if (m70) { void* t = m70; m70 = 0; ReleaseRc(t); }
    if (m78) { void* t = m78; m78 = 0; ReleaseRc(t); }
    m7c = g_i0; m80 = g_i1; m84 = g_i2;
    m50 = -1;
    m5c = -1;
    m58 = 0;
    if (m54) { void* t = m54; m54 = 0; ((IV*)t)->vs14(); }
    m88 = 0;
    m64 = -1;
}

// @ 0x00b73cd0
void cObstacle::Reset1()
{
    if (m2c) { IV* t = (IV*)m2c; m2c = 0; t->vs1(); }
    m60 = 0;
    m38 = g_px; m3c = g_py; m40 = g_pz;
    m44 = 0.0f; m48 = 0.0f; m4c = 0.0f;
    m68 = g_one;
    m6c = 0;
    m74 = 0;
    if (m70) { void* t = m70; m70 = 0; ReleaseRc(t); }
    if (m78) { void* t = m78; m78 = 0; ReleaseRc(t); }
    m7c = g_i0; m80 = g_i1; m84 = g_i2;
    m50 = -1;
    m5c = -1;
    m58 = 0;
    if (m54) { void* t = m54; m54 = 0; ((IV*)t)->vs14(); }
    m88 = 0;
    m64 = -1;
}

// @ 0x00b73de0
void cObstacle::SetFlag(bool b)
{
    if (b)
        m34 |= 1;
    else
        m34 &= ~1u;
    if (m54) {
        float f = b ? 0.0f : g_one;
        ((cRc54*)m54)->SetValue(m5c, f);
        return;
    }
    if (m70) {
        if (b) {
            *(int*)((char*)m70 + 4) &= ~1u;
            RcCall(m70, 0x16c, 0);
        } else {
            *(int*)((char*)m70 + 4) |= 1;
            RcCall(m70, 0x16c, 1);
        }
    }
}

// @ 0x00b73e70
void* __fastcall FUN_00b73e70(int self)
{
    int mode = *(int*)(self + 0x88);
    if (mode >= 0 && (mode <= 3 || mode == 4)) {
        if (mode <= 3 && *(int*)(self + 0x58) != 0)
            return (void*)(*(int*)(self + 0x5c) * 0x4c + *(int*)(self + 0x58));
        if (*(int*)(self + 0x70) != 0)
            return (void*)(*(int*)(self + 0x70) + 8);
    }
    if ((g_168814c & 1) == 0) {
        g_168814c |= 1;
        g_desc.f4 = g_1687ad4;
        g_desc.f8 = g_1687ad8;
        g_desc.fc = g_1687adc;
        g_desc.f2 = 0;
        g_desc.f0 = 0;
        g_desc.f10 = g_1485720;
        g_mtx.Assign(g_matrix_src);
    }
    return &g_desc;
}

// @ 0x00b73f30
void Simulator_cObstacle::FUN_00b73f30(float f, int arg)
{
    int self = (int)this;
    *(float*)(self + 0x68) = f;
    if (arg == 0) {
        if (*(int*)(self + 0x78) != 0 && g_1687ad0 == 0) {
            *(float*)(*(int*)(self + 0x78) + 0x58) = f;
            *(unsigned int*)(*(int*)(self + 0x78) + 4) |= 2;
        }
    } else if (*(int*)(arg + 0x10) != 0) {
        if (g_1687ad0 == 0) {
            ((Fn_vf)FUN_00c3e240)(*(void**)(arg + 0x10), f);
        } else if (f == 1.0f) {
            ((Fn_vf)FUN_00c3e240)(*(void**)(arg + 0x10), 1.0f);
        } else {
            ((Fn_vf)FUN_00c3e240)(*(void**)(arg + 0x10), 0.0f);
        }
    }
    if ((*(unsigned char*)(self + 0x34) & 1) == 0 && *(int*)(self + 0x54) != 0)
        ((Fn_vif)FUN_00a887b0)((void*)*(int*)(self + 0x54), *(int*)(self + 0x5c), 1.0f);

    if (*(int*)(self + 0x88) != 3 && *(int*)(self + 0x88) != 4) {
        void* p = FUN_00b3d420_p((void*)(self + 0x7c));
        void* sp = FUN_00b90410(p);
        if (sp != 0) sp = FUN_00b8f860(sp);
        else sp = 0;
        void* obj = FUN_00b3d440_3(sp, *(void**)(self + 0x50), *(void**)(self + 0x5c));
        void* esi = FUN_00b03320(obj);
        if (esi != 0) {
            void* pa;
            FUN_00b3d440_2(&pa, (char*)esi + 0x1c8);
            FUN_00e5c780((char*)FUN_00b3d440_0() + 0x8080);
            if (pa != (void*)((char*)FUN_00b3d440_0() + 0x8084)) {
                void* ebx = FUN_00b04c20_3(*(void**)((char*)esi + 0x4c),
                                           *(void**)((char*)esi + 0x50),
                                           *(void**)((char*)esi + 0x54));
                unsigned int i = 0;
                unsigned int n = FUN_00b058f0(esi);
                if ((char*)pa + 0x18 != 0) {
                    for (; ebx != 0 && i < n; i++) {
                        if (*(int*)((char*)pa + 0x18 + 0x14) != 0) {
                            unsigned long long m = __allshl(1, 0, (int)i);
                            if (((unsigned int)m & *(unsigned int*)((char*)ebx + 0x48)) ||
                                ((unsigned int)(m >> 32) & *(unsigned int*)((char*)ebx + 0x4c))) {
                                float v;
                                if (g_1687ad0 == 0) v = *(float*)(self + 0x68);
                                else { v = 1.0f; if (*(float*)(self + 0x68) != 1.0f) v = 0.0f; }
                                ((Fn_vif)FUN_00a887b0)(
                                    *(void**)((char*)pa + 0x2c),
                                    *(int*)(*(int*)((char*)esi + 0x19c) + i * 4), v);
                            }
                        }
                    }
                }
            }
        }
    }
}

// @ 0x00b74130
void __fastcall FUN_00b74130(int self)
{
    int* s1 = (int*)SP_GetActiveTerrainSphere();
    if (s1 == 0) return;
    int* s2 = (int*)(*(int*(__thiscall**)(int*))(*(int*)s1 + 0xc))(s1);
    if (s2 == 0) return;
    int* s3 = (int*)(*(int*(__thiscall**)(int*))(*(int*)s1 + 0xc))(s1);
    float size = *(float*)((char*)s3 + 0x38) * *(float*)((char*)s3 + 0x54)
               + *(float*)((char*)s3 + 0x34) + 50.0f;

    float x0 = g_1687ad4 - size, x1 = g_1687ad4 + size;
    float y0 = g_1687ad8 - size, y1 = g_1687ad8 + size;
    float z0 = g_1687adc - size, z1 = g_1687adc + size;

    float a0 = x1 - x0, a1 = y1 - y0, a2 = z1 - z0;
    float* p = &a1;
    if (a1 <= a0) p = &a0;
    if (*p <= a2 && a2 != *p) p = &a2;
    float fv = *p;

    HierGrid* g = *(HierGrid**)(self + 0x55a4);
    if (g->mBegin != g->mEnd) g->Shutdown();

    if (x0 <= x1) {
        float t = fv * 2.0f;
        float hi = t * 9.999999f;
        float lo = t * 0.01f;
        int i1 = (int)lo; if ((float)i1 < lo) i1++;
        int b1 = 0; for (int v = i1; v != 0; v >>= 1) b1++;
        int i2 = (int)hi; if ((float)i2 < hi) i2++;
        int b2 = 0; for (int v = i2; v != 0; v >>= 1) b2++;
        int iVar2 = 0;
        if (0 < b1 - 1) iVar2 = b1 - 1;
        int iVar5 = 7;
        if (b2 - 1 < 7) iVar5 = b2 - 1;
        if (iVar5 < iVar2) iVar5 = iVar2;
        Vec3f v; v.x = x0; v.y = y0; v.z = z0;
        g->Init(v, fv, iVar2, iVar5);
    }
}

// @ 0x00b74370
void* __fastcall FUN_00b74370(int self)
{
    void* result;
    if (((*(int*)(self + 0x40f4) - *(int*)(self + 0x40f0)) >> 2) != 0) {
        int* top = *(int**)(*(int*)(self + 0x40f4) - 4);
        result = 0;
        if (top != 0) {
            (*(void(__thiscall**)(int*))*top)(top);
            result = top;
        }
        *(int*)(self + 0x40f4) -= 4;
        int* obj = *(int**)(*(int*)(self + 0x40f4));
        if (obj != 0)
            (*(void(__thiscall**)(int*))(*(int*)obj + 4))(obj);
    } else {
        void* m = SP_NounManager(0x3ed8573);
        result = SP_cGameNounManager_CreateNoun(m, 0x3ed8573);
        if (result == 0) return 0;
        (*(void(__thiscall**)(void*))*(int*)result)(result);
    }
    if (result != 0)
        (*(void(__thiscall**)(void*))(*(int*)result + 4))(result);
    return result;
}

// @ 0x00b74400
unsigned char __stdcall FUN_00b74400(int self)
{
    int* world = (int*)SP_GonzagoModelWorld();
    unsigned char result = 0;
    if (world != 0) (*(void(__thiscall**)(int*))*world)(world);
    int id = *(int*)(self + 0x74);
    if (id == 0 || id == 0x2ebcd6a6) id = *(int*)(self + 0x6c);
    if (world != 0) {
        result = 0;
        if (id != 0 && id != 0x2ebcd6a6 && *(int*)(self + 0x58) != 0 &&
            *(int*)(self + 0x88) != 3 && *(int*)(self + 0x88) != 4 &&
            *(int*)(self + 0x78) == 0) {
            void* a = g_1687ad0 == 0 ? (void*)g_156b424 : (void*)g_156b470;
            int* obj = (int*)(*(int*(__thiscall**)(int*, int, void*, int))(*(int*)world + 0xc))(world, id, a, 0);
            if (obj != 0) {
                *(int*)((char*)obj + 0x58) = *(int*)(self + 0x68);
                *(unsigned int*)((char*)obj + 4) |= 2;
                *(int*)((char*)obj + 0x44) = 0;
                *(int*)((char*)obj + 0x48) = 0;
                int* mm = (int*)SP_ModelManager();
                unsigned int bit = (*(unsigned int(__thiscall**)(int*, int, int))(*(int*)mm + 0x28))(mm, 0x420b420, 0);
                if (bit < 0x40) {
                    *(unsigned int*)((char*)obj + 0x44 + (bit >> 5) * 4) |= 1u << (bit & 0x1f);
                }
                int* d = (int*)FUN_00b73e70(self);
                FUN_00571d40((char*)d + 4);
                FUN_00571d20((char*)d + 0x14);
                result = 1;
                *(int*)((char*)obj + 0x18) = *(int*)((char*)d + 0x10);
                *(short*)((char*)obj + 10) += 1;
                if ((*(unsigned char*)(self + 0x34) & 4) != 0) {
                    *(short*)((char*)obj + 10) += 1;
                    *(int*)((char*)obj + 0x18) = 0x3f800000;
                }
                FUN_00478db0(obj);
                *(unsigned int*)(self + 0x34) |= 1;
                if (*(int*)(self + 0x54) == 0) {
                    if (*(int*)(self + 0x70) != 0) {
                        *(unsigned int*)(*(int*)(self + 0x70) + 4) &= 0xfffffffe;
                        int* w2 = *(int**)(self + 0x70);
                        int* in = (int*)*w2;
                        ((Fn16c)((void**)in)[0x16c / 4])(in, w2, 0);
                    }
                } else {
                    ((Fn_vif)FUN_00a887b0)((void*)*(int*)(self + 0x54), *(int*)(self + 0x5c), 0.0f);
                }
            }
        }
        (*(void(__thiscall**)(int*))(*(int*)world + 4))(world);
    }
    return result;
}

// @ 0x00b74590
void __stdcall FUN_00b74590(int self)
{
    Wrapper* pw = *(Wrapper**)(self + 0x78);
    if (pw != 0) {
        Inner* in = pw->impl;
        ((Fn16c)in->vptr[0x16c / 4])(in, pw, 0);
        pw = *(Wrapper**)(self + 0x78);
        if (pw != 0) {
            *(int*)(self + 0x78) = 0;
            if (*(int*)((char*)pw + 0x40) > 1) {
                *(int*)((char*)pw + 0x40) -= 1;
                return;
            }
            in = pw->impl;
            ((Fn170)in->vptr[0x170 / 4])(in, pw,
                ((unsigned int)*(int*)((char*)pw + 4) >> 0x1f) != 0);
        }
    }
}

// @ 0x00b746a0
int* Hashtable2::Find(int* out, unsigned int* key)
{
    int* bucket = (int*)(*(int*)((char*)this + 4) + (*key % *(unsigned int*)((char*)this + 8)) * 4);
    unsigned int* node = (unsigned int*)*bucket;
    if (node != 0) {
        do {
            if (key[0] == node[0] && key[1] == node[1]) {
                unsigned int* nx = (unsigned int*)node[4];
                while (nx != 0 && key[0] == nx[0] && key[1] == nx[1])
                    nx = (unsigned int*)nx[4];
                int* slot = bucket;
                if (nx == 0) {
                    slot = bucket + 1;
                    while (*slot == 0) slot++;
                    nx = (unsigned int*)*slot;
                }
                out[1] = (int)bucket;
                out[0] = (int)node;
                out[2] = (int)nx;
                out[3] = (int)slot;
                return out;
            }
            node = (unsigned int*)node[4];
        } while (node != 0);
    }
    int* endb = (int*)(*(int*)((char*)this + 4) + *(int*)((char*)this + 8) * 4);
    int v = *endb;
    out[0] = v;
    out[1] = (int)endb;
    out[2] = v;
    out[3] = (int)endb;
    return out;
}

// @ 0x00b74740
int* Hashtable3::Find(int* out, unsigned int* key)
{
    unsigned int k2 = key[2];
    unsigned int h = key[0] ^ k2;
    unsigned int bi = h % *(unsigned int*)((char*)this + 8);
    int* bucket = (int*)(*(int*)((char*)this + 4) + bi * 4);
    void* node = FindNode((void*)*bucket, (int*)key, h);
    if (node != 0) {
        unsigned int* p = *(unsigned int**)((char*)node + 0xc70);
        while (p != 0 && *key == p[0] && key[1] == p[1] && k2 == p[2])
            p = *(unsigned int**)((char*)p + 0x31c);
        int* slot = bucket;
        if (p == 0) {
            slot = bucket + 1;
            while (*slot == 0) slot++;
            p = (unsigned int*)*slot;
        }
        out[0] = (int)node;
        out[1] = (int)bucket;
        out[2] = (int)p;
        out[3] = (int)slot;
        return out;
    }
    int* endb = (int*)(*(int*)((char*)this + 4) + *(int*)((char*)this + 8) * 4);
    int v = *endb;
    out[0] = v;
    out[1] = (int)endb;
    out[2] = v;
    out[3] = (int)endb;
    return out;
}

// @ 0x00b749c0
void FUN_00b749c0(float* a, float* b, float x, float y, float z)
{
    while (a != b) {
        float dx = a[0] - x;
        float s = dx * dx;
        float dy = a[1] - y;
        s += dy * dy;
        float dz = a[2] - z;
        s += dz * dz;
        if (0.01f > s) break;
        a += 6;
    }
}

// @ 0x00b74a60
void FUN_00b74a60(int* m, int* it)
{
    int* a = (*(int*(__thiscall**)(int*))(*(int*)m + 0x20))(m);
    unsigned int k3 = (unsigned int)it[3];
    int* ser = (int*)(*(int*(__thiscall**)(int*))(*(int*)a + 0x18))(a);
    WriteUint32_s00b7_3e70(ser, &k3, 1, 0);
    int* bucket = (int*)it[1];
    int* node = (int*)*bucket;
    int* slot = bucket;
    if (node == 0) {
        slot = bucket + 1;
        while (*slot == 0) slot++;
        node = (int*)*slot;
    }
    int* end = (int*)(bucket[it[2]]);
    while (node != end) {
        FUN_00ae2e40(m, (int)node);
        (*(void(__thiscall**)(int*))(*(int*)m + 0x1c))(m);
        FUN_00ae2e40(m, (int)node + 0xc);
        (*(void(__thiscall**)(int*))(*(int*)m + 0x1c))(m);
        node = *(int**)((char*)node + 0x18);
        if (node == 0) {
            do { slot++; node = (int*)*slot; } while (node == 0);
        }
    }
    (*(void(__thiscall**)(int*))(*(int*)m + 0x1c))(m);
}

// @ 0x00b74b60
void* Simulator_cObstacle::AllocNode3(int* src)
{
    Node3View* node = *(Node3View**)((char*)this + 0x1c);
    if (node != 0) {
        *(int**)((char*)this + 0x1c) = (int*)node->f0;
    } else {
        node = (Node3View*)EAAllocate(*(int*)((char*)this + 0x2c), "Simulator", 0, 0, 0x13ebb38, 0xd1);
    }
    if (node != 0) {
        node->f0 = src[0];
        node->f4 = src[1];
        node->f8 = src[2];
        int* p = (int*)node->f8;
        if (p != 0) {
            (*(void(__thiscall**)(int*))*p)(p);
        }
    }
    node->f10 = 0;
    return node;
}

// @ 0x00b74bc0
void* Simulator_cObstacle::AllocNode2(int* src)
{
    Node2View* node = *(Node2View**)((char*)this + 0x1c);
    if (node != 0) {
        *(int**)((char*)this + 0x1c) = (int*)node->f0;
    } else {
        node = (Node2View*)EAAllocate(*(int*)((char*)this + 0x2c), "Simulator", 0, 0, 0x13ebb38, 0xd1);
    }
    if (node != 0) {
        node->f0 = src[0];
        node->f4 = src[1];
        int* p = (int*)node->f4;
        if (p != 0) {
            (*(void(__thiscall**)(int*))*p)(p);
        }
    }
    node->f8 = 0;
    return node;
}

// @ 0x00b74c20
void FUN_00b74c20(float* a, float* b, float* c)
{
    for (; a != b; a += 3) {
        if (a != 0) {
            a[0] = c[0];
            a[1] = c[1];
            a[2] = c[2];
        }
    }
}

// @ 0x00b74c50
void FUN_00b74c50(char* begin, char* end, void* cmp)
{
    int n = (int)(end - begin) / 0xc;
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        int* p = (int*)(begin + 8 + i * 0xc);
        do {
            i--;
            FUN_00b737d0((int)begin, i, n, i, *(Vec3*)&p[-5], cmp);
            p -= 3;
        } while (i != 0);
    }
}

// @ 0x00b74cc0
void FUN_00b74cc0(char* begin, char* end, void* cmp)
{
    int n = (int)(end - begin) / 0xc;
    if (n > 1) {
        int* p = (int*)(end - 0xc);
        do {
            int a = p[0], b = p[1], c = p[2];
            p[0] = *(int*)begin;
            p[1] = *(int*)(begin + 4);
            p[2] = *(int*)(begin + 8);
            FUN_00b737d0((int)begin, 0, n - 1, 0, *(Vec3*)&a, cmp);
            p -= 3;
            n = (int)((char*)p - begin) / 0xc;
        } while (n > 1);
    }
}

// @ 0x00b74d60
void FUN_00b74d60(int* base, void* b, int n, int i, void* cmp, float x, float y, float z)
{
    int c = i * 2 + 2;
    if (c < n) {
        do {
            int* n1 = (int*)(base[c]);
            float dz1 = z - *(float*)((char*)n1 + 0x40);
            float dx1 = x - *(float*)((char*)n1 + 0x38);
            float dy1 = y - *(float*)((char*)n1 + 0x3c);
            int* n2 = (int*)(base[c - 1]);
            float dy2 = y - *(float*)((char*)n2 + 0x3c);
            float dx2 = x - *(float*)((char*)n2 + 0x38);
            float dz2 = z - *(float*)((char*)n2 + 0x40);
            float d1 = dz1 * dz1 + dx1 * dx1 + dy1 * dy1;
            float d2 = dz2 * dz2 + dy2 * dy2 + dx2 * dx2;
            c = (d2 > d1) ? (i * 2 + 1) : c;
            base[i] = base[c];
            i = c;
            c = i * 2 + 2;
        } while (c < n);
    }
    if (c == n) {
        base[i] = base[c - 1];
        i = c - 1;
    }
    Vec3 v; v.x = x; v.y = y; v.z = z;
    FUN_00b73920((int)base, b, i, cmp, v);
}

// @ 0x00b74e90
int ObstacleMgr::FindById(unsigned int* a, int b, int id)
{
    Iter2 it;
    Hashtable2* ht = (Hashtable2*)((char*)this + 0x38);
    ht->Find((int*)&it, (unsigned int*)&a);
    int* cur = it.cur;
    int* end = it.end;
    int* bucket = it.bucket;
    while (cur != end) {
        if (*(int*)(*(int*)((char*)cur + 8) + 0x5c) == id)
            return *(int*)((char*)cur + 8);
        cur = *(int**)((char*)cur + 0x10);
        while (cur == 0) {
            bucket++;
            cur = (int*)*bucket;
        }
    }
    return 0;
}

// @ 0x00b74ef0
void __stdcall FUN_00b74ef0(int self)
{
    FUN_00b74590(self);
    *(volatile unsigned int*)(self + 0x34) &= 0xfffffffe;
    int c = *(int*)(self + 0x54);
    if (c != 0) {
        ((Fn_vif)FUN_00a887b0)((void*)c, *(int*)(self + 0x5c), 1.0f);
        return;
    }
    Wrapper* pw = *(Wrapper**)(self + 0x70);
    if (pw != 0) {
        *(unsigned int*)((char*)pw + 4) |= 1;
        pw = *(Wrapper**)(self + 0x70);
        Inner* in = pw->impl;
        ((Fn16c)in->vptr[0x16c / 4])(in, pw, 1);
    }
}

// @ 0x00b74f40
int ObstacleMgr::Lookup(unsigned int* key)
{
    int local[2];
    Hashtable2* ht = (Hashtable2*)((char*)this + 0x56c0);
    ht->Find(&local[0], key);
    if (local[0] != ht->mBegin[ht->mCount])
        return local[0] + 0xc;
    return 0;
}

// @ 0x00b75f70
Vec3_s00b7_5f70* __cdecl FUN_00b75f70(Vec3_s00b7_5f70* first, Vec3_s00b7_5f70* last, Vec3_s00b7_5f70 pivot, bool (__cdecl* comp)(const Vec3_s00b7_5f70*, const Vec3_s00b7_5f70*))
{
    for (;;) {
        while (comp(first, &pivot)) ++first;
        do { --last; } while (comp(&pivot, last));
        if (first >= last) return first;
        Vec3_s00b7_5f70 tmp = *first;
        *first = *last;
        *last = tmp;
        ++first;
    }
}

// @ 0x00b76020
void __cdecl FUN_00b76020(void** base, void** cur, void** end, Vec3_s00b7_5f70 p)
{
    FUN_00b75750(base, cur, p);
    for (void** i = cur; i < end; ++i) {
        Blob* o = (Blob*)*i;
        Blob* b = (Blob*)*base;
        float dz = p.z - o->z;
        float az = p.z - b->z;
        float dx = p.x - o->x;
        float dy = p.y - o->y;
        float ay = p.y - b->y;
        float ax = p.x - b->x;
        if ((dz * dz + dx * dx) + dy * dy < (az * az + ay * ay) + ax * ax) {
            *i = b;
            FUN_00b74d60(base, 0, (int)(cur - base), 0, o, p);
        }
    }
    FUN_00b757b0(base, cur, p);
}

// @ 0x00b76160
void __fastcall FUN_00b76160(char* self)
{
    int n = (*(int*)(self + 0x55ac) - *(int*)(self + 0x55a8)) >> 2;
    for (int i = 0; i < n; ++i) {
        int e = ((int*)*(int*)(self + 0x55a8))[i];
        if (!e) continue;
        int comp = *(int*)(e + 0x90);
        if (!comp) continue;
        if (!((*(unsigned*)(e + 4) >> 0xf) & 1)) continue;
        int local40 = 0;
        if (!((VObj24*)comp)->Slot24(0x4ce873a, &local40)) continue;
        if (*(unsigned short*)(local40 + 0x12) != 0xa) continue;
        if (*((PropId*)local40)->GetUInt() != 0x153f84a3) continue;

        int* piVar3 = (int*)(comp + 8);
        int s28 = piVar3[0], s24 = piVar3[1], s20 = piVar3[2];
        int ai30[2];
        ((C74860*)(self + 0x56c0))->Find(ai30, piVar3);
        if (ai30[0] == *(int*)(*(int*)(self + 0x56c4) + *(int*)(self + 0x56c8) * 4)) {
            if (((CRandomGlob*)&g_1601760)->RandomDoubleUniform() <= (double)g_1464fdc) {
                FUN_0102c7f0(&s28, 0);
            } else {
                void* sm = FUN_00b3d2a0();
                void* emp = ((CStarManager*)sm)->GetUFO();
                int* key = ((CEmpire*)emp)->GetUFOKey();
                s28 = key[0]; s24 = key[1]; s20 = key[2];
            }
            int* dst = ((C75890*)(self + 0x56c0))->InsertKey(piVar3);
            dst[0] = s28; dst[1] = s24; dst[2] = s20;
        } else {
            s28 = *(int*)(ai30[0] + 0xc);
            s24 = *(int*)(ai30[0] + 0x10);
            s20 = *(int*)(ai30[0] + 0x14);
        }
        if (s28 != piVar3[0] || s24 != piVar3[1] || s20 != piVar3[2]) {
            CSink4c* obj = (CSink4c*)FUN_00401010();
            unsigned param[2];
            param[0] = 0x2ea8fb98;
            param[1] = 0x40000;
            obj->s4c(&s28, param);
            CGonzago* gw = (CGonzago*)FUN_00b3d520();
            int created = gw->g0c(ai30[0], s28, 4);
            if (created) {
                ++*(int*)(created + 0x40);
                *(unsigned*)(e + 4) &= ~1u;
                unsigned char flag = 0;
                FUN_00407190(*(void**)(e + 0x90), 0x3eb2e21, &flag);
                ((C537dc0*)(created + 8))->Assign((void*)(e + 8));
                ((C72520*)(created + 8))->Rotate(0.0f, g_14650a4, 0.0f);
                ((C478db0*)&((int*)*(int*)(self + 0x55a8))[i])->Assign((void*)created);
                int* sub = (int*)*(int*)(created + 0x90);
                Var v;
                Var* vp = ((C5dd750*)&v)->SetBool(&flag);
                ((CSubObj*)sub)->v14(0x3eb2e21, vp);
                if (v.mFlags & 4) ((CVariant*)&v)->Destruct(false);
            }
            ((C5765e0*)&created)->Release();
        }
    }
}

// @ 0x00b76400
float* __fastcall FUN_00b76400(MF* m, int, const int& k)
{
    NodeF* n;
    { ItF it = m->find(k); n = it.n; }
    if (n == m->buckets[m->nb]) {
        VTF v = { k, 0 };
        ZF z; z.b = false;
        PF r = m->insertz(v, z);
        return &r.it.n->val;
    }
    return &n->val;
}

// @ 0x00b76460
RefVal** __fastcall FUN_00b76460(MR* m, int, const int& k)
{
    NRef* n;
    { ItR it = m->find(k); n = it.n; }
    if (n != m->buckets[m->nb]) return &n->val;
    VTR v; v.key = k; v.val = 0;
    ZF z; z.b = false;
    PR r = m->insertr(v, z);
    if (v.val) v.val->Release();
    return &r.it.n->val;
}

// @ 0x00b764e0
It8 C764e0::Advance(It8 first, It8 last)
{
    while (first.n != last.n) first = Next(first);
    return first;
}

// @ 0x00b76530
void C76530::Push(const El18& v)
{
    El18* p = mEnd;
    if (p < mCap) {
        mEnd = p + 1;
        if (p) {
            p->a = v.a; p->b = v.b; p->c = v.c; p->d = v.d;
            p->e = v.e; p->f = v.f;
        }
        return;
    }
    Grow(p, &v);
}

// @ 0x00b76580
HT70::iterator HT70::erase(iterator i)
{
    HTN70* const n = i.mpNode;
    HTN70** const b = i.mpBucket;
    iterator next;
    next.mpBucket = b;
    next.mpNode = n->mpNext;
    while (next.mpNode == 0) { ++next.mpBucket; next.mpNode = *next.mpBucket; }
    HTN70* pNode = *b;
    if (pNode == n) {
        *b = pNode->mpNext;
    } else {
        HTN70* pNext = pNode->mpNext;
        while (pNext != n) { pNode = pNext; pNext = pNext->mpNext; }
        pNode->mpNext = pNext->mpNext;
    }
    void* buf = *(void**)((char*)n + 0x58);
    if (buf != 0 && *(int*)((char*)buf - 4) != 0) opdel(buf);
    opdel(n);
    --mnElementCount;
    return next;
}

// @ 0x00b76620
int HT68::eraseKey(const unsigned* kp)
{
    unsigned key = *kp;
    int old = mnElementCount;
    HTN68** b = &buckets[key % nb];
    HTN68* p;
    while ((p = *b) != 0) {
        if (p->key == key) break;
        b = &p->mpNext;
    }
    if (*b) {
        do {
            p = *b;
            if (p->key != key) break;
            *b = p->mpNext;
            void* buf = *(void**)((char*)p + 0x50);
            if (buf != 0 && *(int*)((char*)buf - 4) != 0) opdel(buf);
            opdel(p);
            --mnElementCount;
        } while (*b);
    }
    return old - (int)mnElementCount;
}

// @ 0x00b766b0
HT68b::iterator HT68b::erase(iterator i)
{
    HTN68b* const n = i.mpNode;
    HTN68b** const b = i.mpBucket;
    iterator next;
    next.mpBucket = b;
    next.mpNode = n->mpNext;
    while (next.mpNode == 0) { ++next.mpBucket; next.mpNode = *next.mpBucket; }
    HTN68b* pNode = *b;
    if (pNode == n) {
        *b = pNode->mpNext;
    } else {
        HTN68b* pNext = pNode->mpNext;
        while (pNext != n) { pNode = pNext; pNext = pNext->mpNext; }
        pNode->mpNext = pNext->mpNext;
    }
    void* buf = *(void**)((char*)n + 0x50);
    if (buf != 0 && *(int*)((char*)buf - 4) != 0) opdel(buf);
    opdel(n);
    --mnElementCount;
    return next;
}

// @ 0x00b76750
bool __cdecl FUN_00b76750(int* sink, const char* name, ResTable* table)
{
    bool result = true;
    if (table->mnElementCount == 0) return result;
    WStr s;
    if (name != 0) {
        WStr t;
        FUN_0093c5a0(&t, name, -1);
        ((C56e2d0*)&s)->Copy(&t);
        if (t.begin != 0 && (((int)((char*)t.cap - (char*)t.begin)) & 0xfffffffe) > 2)
            opdel(t.begin);
    } else {
        WStr t;
        t.begin = 0; t.end = 0; t.cap = 0;
        ((C579a90*)&t)->RangeInitialize(0);
        ((C56e2d0*)&s)->Copy(&t);
        if (t.begin != 0 && (((int)((char*)t.cap - (char*)t.begin)) & 0xfffffffe) > 2)
            opdel(t.begin);
    }
    void** buckets = table->mpBuckets;
    void** bucket = buckets;
    ResTableNode* node = (ResTableNode*)*bucket;
    if (node == 0) {
        ++bucket;
        while (*bucket == 0) ++bucket;
        node = (ResTableNode*)*bucket;
    }
    const void* text = (s.begin == s.end) ? (const void*)&g_13f6254 : (const void*)s.begin;
    ((ResSink*)sink)->v00(text);
    ResTableNode* end = (ResTableNode*)buckets[table->mnBucketCount];
    while (node != end) {
        result = result && (FUN_00ae5530(sink, 0, node->mKey, L"EA::ResourceMan::Key") != 0);
        node = node->mpNext;
        while (node == 0) { ++bucket; node = (ResTableNode*)*bucket; }
    }
    const void* text2 = (s.begin == s.end) ? (const void*)&g_13f6254 : (const void*)s.begin;
    ((ResSink*)sink)->v04(text2);
    if (s.begin != 0 && (((int)((char*)s.cap - (char*)s.begin)) & 0xfffffffe) > 2)
        opdel(s.begin);
    return result;
}

// @ 0x00b768d0
void __cdecl FUN_00b768d0(void* first, void* last, void* a3, void* a4)
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    if (n > 1) {
        char* buf = (char*)EAAllocate(n * 0xc, "Simulator", 0, 0, 0x13ebb38, 0xd1);
        char uninit[12];
        FUN_00b74c20(buf, buf + n * 0xc, uninit);
        FUN_00b75c60(first, last, buf, a4);
        opdel(buf);
    }
}

// @ 0x00b76950
void __cdecl FUN_00b76950(Vec3_s00b7_5f70* first, Vec3_s00b7_5f70* last, int depth, Cmp3 comp)
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    for (;;) {
        if (n <= 0x1c || depth <= 0) {
            if (depth == 0) FUN_00b754d0(first, last, last, (void*)comp);
            return;
        }
        Vec3_s00b7_5f70* mid = (Vec3_s00b7_5f70*)((char*)first + (n / 2) * 0xc);
        Vec3_s00b7_5f70* pv;
        if (comp(first, mid)) {
            if (comp(mid, last - 1)) pv = mid;
            else if (comp(first, last - 1)) pv = last - 1;
            else pv = first;
        } else {
            if (comp(first, last - 1)) pv = first;
            else if (comp(mid, last - 1)) pv = last - 1;
            else pv = mid;
        }
        Vec3_s00b7_5f70 pivot = *pv;
        Vec3_s00b7_5f70* cut = FUN_00b75f70(first, last, pivot, comp);
        --depth;
        FUN_00b76950(cut, last, depth, comp);
        last = cut;
        n = (int)((char*)cut - (char*)first) / 0xc;
    }
}

// @ 0x00b76a60
void __cdecl FUN_00b76a60(void** first, void** last, int depth, Vec3_s00b7_5f70 p)
{
    int n = (int)((char*)last - (char*)first);
    if ((n & ~3) > 0x70) {
        do {
            if (depth <= 0) break;
            void** mid = first + n / 8;
            void** pv = (void**)FUN_00b734e0(first, mid, last - 1, p, p);
            void** cut = (void**)FUN_00b75620(first, last, *pv);
            --depth;
            FUN_00b76a60(cut, last, depth, p);
            last = cut;
            n = (int)((char*)last - (char*)first);
        } while ((n & ~3) > 0x70);
    }
    if (depth == 0) FUN_00b76020(first, last, last, p);
}

// @ 0x00b76b80
void __cdecl FUN_00b76b80(const Vec3_s00b7_5f70* a, const Vec3_s00b7_5f70* b, void* vec, void* xf)
{
    Vec3_s00b7_5f70 d;
    d.x = b->x - a->x;
    d.y = b->y - a->y;
    d.z = b->z - a->z;
    float len = (d.y * d.y + (d.x * d.x + d.z * d.z)) + 1e-08f;
    float inv = 1.0f / sqrtf(len);
    Vec3_s00b7_5f70 dir;
    dir.x = inv * d.x;
    dir.y = inv * d.y;
    dir.z = inv * d.z;
    C82060* pm = (C82060*)FUN_00b3d350();
    pm->Run(&d, a, &dir);
    if (d.x != g_1687ad4_s00b7_5f70 || d.y != g_1687ad8_s00b7_5f70 || d.z != g_1687adc_s00b7_5f70) {
        ((CXForm*)xf)->BackTransform(&d);
        CVec3v* v = (CVec3v*)vec;
        void** e = v->end;
        if (e < v->cap) {
            v->end = e + 3;
        } else {
            v->DoInsertValue(e, &d);
        }
        float* last3 = (float*)((char*)v->end - 0xc);
        float dot = (d.y * g_16880e4 + d.z * g_16880e8) + d.x * g_16880e0;
        last3[0] = d.x - dot * g_16880e0;
        last3[1] = d.y - dot * g_16880e4;
        last3[2] = d.z - dot * g_16880e8;
    }
}

// @ 0x00b76d20
void __fastcall FUN_00b76d20(char* self, int, float* p, float a3, int a4, char a5, char a6)
{
    if (p[0] == g_1687ad4_s00b7_5f70 && p[1] == g_1687ad8_s00b7_5f70 && p[2] == g_1687adc_s00b7_5f70) return;
    char* vv = self + 0x4908;
    if (FUN_00b749c0(*(void**)(self + 0x4908), *(void**)(self + 0x490c), p[0], p[1], p[2])
            != *(void**)(self + 0x490c))
        return;
    if (a6) a3 = *(float*)(self + 0x54a4);
    El18 local;
    local.a = p[0];
    local.b = p[1];
    local.c = p[2];
    local.d = a3;
    local.e = a5;
    local.f = a4;
    ((C76530*)vv)->Push(local);
}

// @ 0x00b76e00
void __fastcall FUN_00b76e00(char* self, int, float k1, float k2)
{
    int ht = (int)(self + 0x49e0);
    int** buckets = *(int***)(self + 0x49e4);
    int nb = *(int*)(self + 0x49e8);
    int* node = *buckets;
    int** bp = buckets;
    if (!node) { ++bp; while (!*bp) ++bp; node = *bp; }
    if (node != buckets[nb]) {
        do {
            void* o = (void*)*node;
            ((C74f80*)self)->Notify(o, *(float*)((char*)node + 4), k2);
            int local = *(int*)((char*)o + 0x24);
            RefVal** p = FUN_00b76460((MR*)ht, 0, (const int&)local);
            RefVal* old = (RefVal*)*p;
            if ((void*)o != (void*)old) {
                ((RefVal*)o)->AddRef();
                *p = (RefVal*)o;
                if (old) old->Release();
            }
            node = *(int**)((char*)node + 8);
            if (!node) { ++bp; while (!*bp) ++bp; node = *bp; }
        } while (node != buckets[nb]);
    }
    ((C75c00*)ht)->DoFreeNodes(buckets, nb);
    *(int*)(self + 0x49ec) = 0;
}

// @ 0x00b76f10
bool Spawner::Spawn(SpawnReq* p, u32 hash)
{
    bool result = false;
    Elem* arr = p->elems;
    Model* ref = p->ref;
    u32 extra = p->extra;
    u32 id = p->id;
    u32 count = p->count;
    bool isPlant = (hash == 0x25630b7 || hash == 0x477c00d || hash == 0x2e9977e);
    bool isOther = (hash == 0x31018b9);
    Vec3 defPos = g_DefaultPos;
    u32 kind = 0;
    if (id == 0) goto done;
    if (id == 0x2ebcd6a6) goto done;

    float sx, sy, sz;
    u32 value;
    u64 key;
    if (isPlant) {
        float* e = GetPlantMgr()->Find(p);
        if (!e) goto done;
        Species* sp = GetSpeciesMgr()->GetSpecies(e);
        if (!sp) goto done;
        defPos.x = e[0]; defPos.y = e[1]; defPos.z = e[2];
        u32 hi = sp->GetKind();
        sx = sp->mSize0;
        value = sp->mValue;
        sy = sp->mSize1;
        key = ((u64)hi << 32) | (u64)extra;
        sz = sp->mSize2;
        switch (sp->GetKind()) {
        case 0x29c388a: kind = 1; break;
        case 0x3a8be428: kind = 0; break;
        case 0x6d60a1cc: kind = 2; break;
        }
    } else {
        if (!isOther) goto done;
        TableMgr* tm = GetTableMgr();
        TableEntry* t = tm->tabBegin;
        u32 n = (u32)(tm->tabEnd - tm->tabBegin);
        u32 i = 0;
        if (n == 0) goto done;
        do {
            if (t->idA == id || t->idB == id) goto foundEntry;
            i++;
            t++;
        } while (i < n);
        goto done;
foundEntry:
        if (!((u8)t->flags & 1)) goto done;
        sx = t->s0;
        sy = t->s1;
        key = (u64)(int)(u32)ref;
        sz = t->s2;
        value = t->val;
        kind = 3;
    }
    if (key == 0) goto done;

    HtRange res;
    res.first.node = 0; res.first.bucket = 0; res.last.node = 0; res.last.bucket = 0;
    bool bMain = true;
    result = true;
    bool found = Find(&res, (u32)key, (u32)(key >> 32), count, false);
    if (!found && hash == 0x2e9977e) {
        bMain = false;
        found = Find(&res, (u32)key, (u32)(key >> 32), count, true);
    }
    if (found)
    {
        HtNode* node = res.first.node;
        HtNode** bucket = res.first.bucket;
        if (node != res.last.node) {
            Elem* e = arr;
            do {
                Obj* o = node->obj;
                if (o) o->AddRef();
                float a = (o->mFlags & 1) ? 0.0f : 1.0f;
                ref->SetAlpha(o->mIndex, a);
                if (bMain) {
                    Model* old = o->mpModel;
                    if (ref != old) {
                        if (ref) ref->AddRef();
                        o->mpModel = ref;
                        if (old) old->Release();
                    }
                    o->mpSource = arr;
                    if (hash == 0x2e9977e) o->mFlags |= 4; else o->mFlags &= ~4u;
                    float scale = e->scale;
                    if (hash == 0x2e9977e) scale = 1.0f;
                    *(Vec3A*)&o->mPos = *(Vec3A*)&e->pos;
                    o->mSize[0] = scale * sx;
                    o->mSize[1] = scale * sy;
                    o->mSize[2] = scale * sz;
                    HtEntry ent;
                    ent.lo = (u32)key; ent.hi = (u32)(key >> 32); ent.obj = o;
                    o->AddRef();
                    HtResult r;
                    mAlt.Insert(&r, &ent, TrueTag());
                    if (ent.obj) ent.obj->Release();
                }
                e++;
                o->Release();
                node = node->next;
                while (!node) node = *++bucket;
            } while (node != res.last.node);
        }
        if (bMain) {
            HtResult r;
            mMain.Erase(&r, res.first, res.last);
        }
    }
    else
    {
        RecA* rec = 0;
        if (isOther) {
            TableMgr* tm = GetTableMgr();
            u32 k = (u32)ref;
            void* it;
            tm->mTree.Find(&it, &k);
            if (it != (void*)&tm->mTree.mAnchor) rec = *(RecA**)((char*)it + 0x14);
        }
        PlanetModel* planet = GetPlanet();
        for (u32 i = 0; i < count; i++) {
            Vec3C pos = *(Vec3C*)&arr[i].pos;
            float scale = arr[i].scale;
            if (hash == 0x2e9977e) scale = 1.0f;
            Obj* o = AllocObj();
            if (o) o->AddRef();
            o->Reset();
            o->mPos = *(Vec3*)&pos;
            o->mSize[0] = scale * sx;
            o->mSize[2] = scale * sz;
            o->mSize[1] = scale * sy;
            o->mScale = 1.0f;
            o->mId = id;
            ReleaseShared(o->mpA);
            o->mValue = value;
            ReleaseShared(o->mpB);
            o->mDefPos = defPos;
            o->mpSource = arr;
            o->mIndex = i;
            o->mExtra = extra;
            {
                Model* old = o->mpModel;
                if (ref != old) {
                    if (ref) ref->AddRef();
                    o->mpModel = ref;
                    if (old) old->Release();
                }
            }
            o->mKind = kind;
            if (hash == 0x2e9977e) o->mFlags |= 4; else o->mFlags &= ~4u;
            if (mpGrid->mBegin == mpGrid->mEnd) InitGrid();
            {
                Grid* g = GetGlobal2()->pGrid;
                if (g && o->mGridSlot < 0 && g->mBegin != g->mEnd)
                    o->mGridSlot = g->Add(o->mSize[1], &o->mPos, o);
            }
            if (rec && rec->arr[i]) {
                o->mFlags |= 1;
                if (o->mpModel) {
                    o->mpModel->SetAlpha(o->mIndex, 0.0f);
                } else if (o->mpA) {
                    o->mpA->mFlags &= ~1u;
                    VCALL2(o->mpA->mpOwner, 0x16c, o->mpA, 0);
                }
                Grid* g = GetGlobal2()->pGrid;
                if (g && o->mGridSlot >= 0) {
                    if (g->mBegin != g->mEnd) g->Remove(o->mGridSlot);
                    o->mGridSlot = -1;
                }
            }
            if (kind == 3 && !rec && g_pProps->Has(0x4233e37)) {
                planet->Mark((Vec3*)&pos, (float)sqrt(pos.x * pos.x + pos.z * pos.z + pos.y * pos.y) * 0.00390625f + o->mSize[0], 0x10000000, 0);
            }
            HtEntry ent;
            ent.lo = (u32)key; ent.hi = (u32)(key >> 32); ent.obj = o;
            o->AddRef();
            HtResult r;
            mAlt.Insert(&r, &ent, TrueTag());
            if (ent.obj) ent.obj->Release();
            o->Release();
        }
    }
done:
    return result;
}

// @ 0x00b77780
SpawnTable::SpawnTable(const void* pHasher, const void* pEqual)
{
    {   // the allocator temporary only lives until the base constructor has read it
        FixedHashtableAllocator alloc;
        alloc.mpHead = 0;
        alloc.init(mNodePool, sizeof(mNodePool), 0xc, 4, 0);
        alloc.mpNodeBegin   = mNodePool;
        alloc.mpNodeEnd     = mNodePool + sizeof(mNodePool);
        alloc.mnNodeSize    = 0xc;
        alloc.mpBucketArray = mBuckets;

        // eastl hashtable base constructor: (pool block, hasher, equal, equal, equal, equal,
        // allocator). The empty policy objects travel both by value and by address; the order
        // below is the one the compiler produced for this instantiation.
        mHeader.CtorBase(AllocPoolBlock(0x41), pHasher,
                         (const void*)&pEqual, (const void*)&pEqual, pEqual,
                         (const void*)&pEqual, &alloc);
    }

    PrimeRehashPolicy policy;
    policy.mMaxLoadFactor = g_TableMaxLoadFactor;
    policy.mGrowthFactor  = g_TableGrowthFactor;
    policy.mNextResize    = 0;
    mMaxLoadFactor = policy.mMaxLoadFactor;
    mGrowthFactor  = policy.mGrowthFactor;
    mNextResize    = policy.mNextResize;

    u32 bucketCount = policy.get_next_bucket_count(mHeader.mElementCount);
    if (mHeader.mBucketCount < bucketCount) mHeader.Rehash(bucketCount);
}

// @ 0x00b77850
void QuadVec::resize(u32 n)
{
    if (n > (u32)(mpEnd - mpBegin)) {
        Quad16 value;                     // uninitialised fill value, as in the original
        insert(mpEnd, n - (u32)(mpEnd - mpBegin), value);
    } else {
        erase(mpBegin + n, mpEnd);
    }
}

// @ 0x00b778b0
SwarmRecord::SwarmRecord(const SwarmRecord& src)
: mA(src.mA), mB(src.mB), mC(src.mC), mD(src.mD), mE(src.mE), mF(src.mF),
      mMat(src.mMat), mG(src.mG), mH(src.mH), mI(src.mI), mJ(src.mJ), mK(src.mK)
{
    mVec.reset();
    mVec = src.mVec;
}

// @ 0x00b77940
void SortVec3Array(Vec3* pBegin, Vec3* pEnd, bool (__cdecl* less)(const Vec3*, const Vec3*))
{
    if (pBegin == pEnd) return;
    int n = (int)(pEnd - pBegin);
    int v = n;
    int bits = 0;
    while (v != 0) {
        v >>= 1;
        ++bits;
    }
    FUN_00b76950(pBegin, pEnd, bits * 2 - 2, less);
    if (n > 0x1c) {
        Vec3* mid = pBegin + 0x1c;        // 28 elements = 0x150 bytes
        FUN_00b73200(pBegin, mid, less);
        FUN_00b732a0(mid, pEnd, less);
    } else {
        FUN_00b73200(pBegin, pEnd, less);
    }
}

// @ 0x00b77aa0
void Spawner::ClearModels()
{
    RefModel** it = mModels.mpBegin;
    while (it != mModels.mpEnd) {
        RefModel* m = *it;
        if (m) {
            if (m->mpSub) {
                RefModel* pSub = m->mpSub;
                m->mpSub = 0;
                VCALL0(pSub, 4);
            }
            m->mFlags &= ~1u;
            VCALL2(m->mpOwner, 0x16c, m, 0);
        }
        // erase(it): shift the tail down, then release the duplicated element
        RefModel** end = mModels.mpEnd;
        if (it + 1 < end) copy_5f4e10(it + 1, end, it);
        --mModels.mpEnd;
        ReleaseModelRef(*mModels.mpEnd);
    }
}

// @ 0x00b77b60
void Spawner::ClearTable(HashTable* pTable, u32 keyLo, u32 keyHi)
{
    HtIter last;
    last.bucket = pTable->mpBucketArray + pTable->mBucketCount;
    last.node   = *last.bucket;

    HtNode** pSlot = pTable->mpBucketArray;
    HtNode*  pNode = *pSlot;
    if (!pNode) {
        do {
            ++pSlot;
            pNode = *pSlot;
        } while (!pNode);
    }

    HtRange range;
    range.first.node   = pNode;
    range.first.bucket = pSlot;
    range.last         = last;

    if (keyLo | keyHi) {
        HtRange found;
        pTable->Find(&found, &keyLo);
        range = found;
    }

    for (HtIter it = range.first; it.node != range.last.node; ) {
        AutoRef ref(it.node->obj);
        Obj* o = it.node->obj;

        Grid* g = GetGlobal2()->pGrid;
        if (g && o->mGridSlot >= 0) {
            if (g->mBegin != g->mEnd) g->Remove(o->mGridSlot);
            o->mGridSlot = -1;
        }
        if (o->mpB) {
            VCALL2(o->mpB->mpOwner, 0x16c, o->mpB, 0);
        }
        ReleaseShared(o->mpB);
        o->mFlags &= ~1u;
        if (o->mpModel) {
            o->mpModel->SetAlpha(o->mIndex, 1.0f);
        } else if (o->mpA) {
            o->mpA->mFlags |= 1;
            VCALL2(o->mpA->mpOwner, 0x16c, o->mpA, 1);
        }

        ObjPtrVec& refs = mModelRefs;
        if ((u32)(refs.mpEnd - refs.mpBegin) < g_MaxModelRefs) {
            VCALL0(o, 0x44);
            if (refs.mpEnd < refs.mpCap) {
                Obj** p = refs.mpEnd++;
                if (p) {
                    *p = o;
                    o->AddRef();
                }
            } else {
                refs.DoInsertPtr(refs.mpEnd, ref);
            }
        } else {
            GetNounManager()->RemoveNoun(o);
        }

        it.node = it.node->next;
        while (!it.node) it.node = *++it.bucket;
    }

    if (keyLo | keyHi) {
        HtResult res;
        pTable->Erase(&res, range.first, range.last);
    } else {
        pTable->clear(pTable->mpBucketArray, pTable->mBucketCount);
        pTable->mElementCount = 0;
    }
}

// @ 0x00b77db0
u8 FUN_00b77db0(void* param_1, u32 param_2)
{
  int iVar4 = PI(param_1, 0x10);
  u32 local_2c = PU(param_1, 0x30);
  int iVar8 = PI(param_1, 0x18);
  int iVar6 = PI(param_1, 0x20);
  u8 local_35 = 0;
  bool bVar3 = (param_2 == 0x25630b7) || (param_2 == 0x477c00d) || (param_2 == 0x2e9977e);
  u8 cl = (param_2 == 0x31018b9);
  if (iVar8 == 0) return 0;
  if (iVar8 == (int)0x2ebcd6a6) return 0;
  int local_28;
  int local_24;
  if (bVar3) {
    void* pm = FUN_00b3d3b0();
    int x = (int)FUN_00b2b1e0(pm);
    if (x == 0) return 0;
    void* s = FUN_00b3d420((void*)x);
    void* sp = FUN_00b90410(s);
    if (sp == 0) return 0;
    local_24 = FUN_00b8f860();
    iVar4 = iVar6;
  } else {
    if (!cl) return 0;
    void* tm = FUN_00b3d3b0();
    int iVar5 = PI(tm, 0x17c);
    u32 uVar9 = (PI(tm, 0x180) - iVar5) / 0x24;
    u32 uVar7 = 0;
    if (uVar9 == 0) return 0;
    while ((PI(iVar5, 4) != iVar8) && (PI(iVar5, 8) != iVar8)) {
      ++uVar7;
      iVar5 += 0x24;
      if (uVar9 <= uVar7) return 0;
    }
    if ((PU(iVar5, 0x20) & 1) == 0) return 0;
    local_24 = iVar4 >> 0x1f;
  }
  int local_34[2];
  if (iVar4 != 0 || local_24 != 0) {
    local_35 = 1;
    local_28 = iVar4;
    if ((local_2c & 1) == 0) {
      local_34[0] = PI(PP(param_1, 0x18), 0);  // (reconstructed placeholder for the spilled base)
      local_2c = local_34[0] + 0x38;
      FUN_00b746a0(PS(param_1, 0x14), &local_28);
      int iVar6b = PI(param_1, 0x1c);
      int iVar8b = PI(param_1, 0x20);
      if (iVar8b != PI(param_1, 0x24)) {
        do {
          int* piVar1 = *(int**)(iVar8b + 8);
          if (piVar1 != 0) ((void(__thiscall*)(void*))(*(void***)piVar1)[0])(piVar1);
          int* piVar2 = (int*)piVar1[0x15];
          if (piVar2 != 0) {
            piVar1[0x15] = 0;
            ((void(__thiscall*)(void*))(*(void***)piVar2)[0x38 / 4])(piVar2);
          }
          piVar1[0x16] = 0;
          int stk[3];
          stk[0] = local_24;
          stk[1] = iVar4;
          stk[2] = (int)piVar1;
          ((void(__thiscall*)(void*))(*(void***)piVar1)[0])(piVar1);
          FUN_00b75240(local_34, stk, param_2 & 0xffffff00);
          if (stk[2] != 0) ((void(__thiscall*)(void*))(*(void***)stk[2])[1])((void*)stk[2]);
          ((void(__thiscall*)(void*))(*(void***)piVar1)[1])(piVar1);
          iVar8b = PI(iVar8b, 0x10);
          while (iVar8b == 0) {
            iVar6b += 4;
            iVar8b = PI(iVar6b, 0);
          }
        } while (iVar8b != PI(param_1, 0x24));
      }
      FUN_00b764e0(PS(param_1, 0x14), iVar8b, PI(param_1, 0x1c), PI(param_1, 0x24), PI(param_1, 0x18));
      return 1;
    }
    FUN_00b77b60((void*)(local_34[0] + 0x38), iVar4, local_24);
  }
  return local_35;
}

// @ 0x00b78020
void* Sim_s00b7_7db0::FUN_00b78020(void* param_1)
{
  void* r = EAAllocate(0xc74, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (r != 0) {
    PU(r, 0) = PU(param_1, 0);
    PU(r, 4) = PU(param_1, 4);
    PU(r, 8) = PU(param_1, 8);
    ((ThSub*)((char*)r + 0xc))->FUN_00b778b0(PS(param_1, 0xc));
  }
  PU(r, 0xc70) = 0;
  return r;
}

// @ 0x00b78080
void* Sim_s00b7_7db0::FUN_00b78080(void* param_1)
{
  void* r = EAAllocate(0xc6c, "Simulator", 0, 0,
      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
      0xd1);
  if (r != 0) {
    PU(r, 0) = PU(param_1, 0);
    ((ThSub*)((char*)r + 4))->FUN_00b778b0(PS(param_1, 4));
  }
  PU(r, 0xc68) = 0;
  return r;
}

// @ 0x00b780d0
int Sim_s00b7_7db0::FUN_00b780d0(int* param_1, int* param_2)
{
  int iVar5 = (param_1[1] - *param_1) / 0xc;
  if (0 < iVar5) {
    FUN_00b77940((void*)*param_1, (void*)param_1[1], (void*)FUN_00b72290);
    void* uVar4 = FUN_00b72dc0((void*)*param_1, (void*)param_1[1], (void*)FUN_00b725a0);
    ((SpVec*)param_1)->FUN_0050f740(uVar4, (void*)param_1[1]);
    int iVar5b = param_1[1];
    int iVar1 = *param_1;
    void* f1 = FUN_00921240((void*)FUN_00b72560);
    FUN_00b768d0((void*)iVar1, (void*)iVar5b, f1);
    int iVar2 = param_1[1];
    int iVar3 = *param_1;
    void* f2 = FUN_00921240((void*)FUN_00b72580);
    FUN_00b768d0((void*)iVar3, (void*)iVar2, f2);
    ((SpVec*)param_2)->FUN_00473810((iVar5b - iVar1) / 0xc + 1);
    iVar5 = FUN_00699a10((const float*)*param_1, (param_1[1] - *param_1) / 0xc, (float*)*param_2);
  }
  ((SpVec*)param_2)->FUN_00473810(iVar5);
  return (param_2[1] - *param_2) / 0xc;
}

// @ 0x00b781d0
void __fastcall FUN_00b781d0(void* param_1)
{
  // two hashtable-like containers at +0x38 / +0x2094, cleared via FUN_00b77b60 then FUN_00b759b0
  FUN_00b77b60(PS(param_1, 0x38), 0, 0);
  FUN_00b77b60(PS(param_1, 0x2094), 0, 0);
  ((Cnt*)((char*)param_1 + 0x38))->FUN_00b759b0(((Cnt*)((char*)param_1 + 0x38))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x38))->mBeg);
  *(int*)((char*)param_1 + 0x44) = 0;
  ((Cnt*)((char*)param_1 + 0x2094))->FUN_00b759b0(((Cnt*)((char*)param_1 + 0x2094))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x2094))->mBeg);
  *(int*)((char*)param_1 + 0x20a0) = 0;
  ((Cnt*)((char*)param_1 + 0x54a8))->FUN_00b75b80(((Cnt*)((char*)param_1 + 0x54a8))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x54a8))->mBeg);
  *(int*)((char*)param_1 + 0x54b4) = 0;
  ((Cnt*)((char*)param_1 + 0x54c8))->FUN_00b75bf0(((Cnt*)((char*)param_1 + 0x54c8))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x54c8))->mBeg);
  *(int*)((char*)param_1 + 0x54d4) = 0;
  ((Cnt*)((char*)param_1 + 0x54e8))->FUN_00b75bf0(((Cnt*)((char*)param_1 + 0x54e8))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x54e8))->mBeg);
  *(int*)((char*)param_1 + 0x54f4) = 0;
  // eastl vector<AutoRefCount<cMWModel>> at +0x55a8: do_copy + DoDestroyValues
  {
    int beg = PI(param_1, 0x55a8);
    int end = PI(param_1, 0x55ac);
    ((EaVec*)PS(param_1, 0x55a8))->FUN_005f4e10((void*)end, (void*)end, (void*)beg);
    ((EaVec*)PS(param_1, 0x55a8))->FUN_005f3680(((EaVec*)PS(param_1, 0x55a8))->mEnd,
                                                 ((EaVec*)PS(param_1, 0x55a8))->mEnd);
    *(int*)((char*)param_1 + 0x55ac) += ((end - beg) >> 2) * -4;
  }
  ((Cnt*)((char*)param_1 + 0x56c0))->FUN_00b73070(((Cnt*)((char*)param_1 + 0x56c0))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x56c0))->mBeg);
  *(int*)((char*)param_1 + 0x56cc) = 0;
  // eastl vector<Vertex3D> at +0x4908 (stride 0x18): CopyVertex3D + shrink
  {
    int beg = PI(param_1, 0x4908);
    int end = PI(param_1, 0x490c);
    FUN_00720250((void*)end, (void*)end, (void*)beg);
    int d = (end - beg) / 0x18;                     // element count (stride 0x18)
    *(int*)((char*)param_1 + 0x490c) -= d * 0x18;   // end -= count * stride
  }
  ((Cnt*)((char*)param_1 + 0x49e0))->FUN_00a1b6c0(((Cnt*)((char*)param_1 + 0x49e0))->mEnd,
                                                    ((Cnt*)((char*)param_1 + 0x49e0))->mBeg);
  *(int*)((char*)param_1 + 0x49ec) = 0;
  ((Cnt*)((char*)param_1 + 0x4f30))->FUN_00a24480(((Cnt*)((char*)param_1 + 0x4f30))->mEnd,
                                                   ((Cnt*)((char*)param_1 + 0x4f30))->mBeg);
  *(int*)((char*)param_1 + 0x4f3c) = 0;
  ((Cnt*)((char*)param_1 + 0x55a4))->FUN_00704060();
  {
    int* p = (int*)PI(param_1, 0x40f0);
    int* e = (int*)PI(param_1, 0x40f4);
    if (p != e) {
      do {
        u32 id = (u32)*p;
        ((GameNounMgr*)FUN_00b3d300(id))->FUN_00b225d0((void*)id);
        if (p + 1 < (int*)PI(param_1, 0x40f4))
          FUN_006782c0((void*)(p + 1), (void*)PI(param_1, 0x40f4), (void*)p);
        *(int*)((char*)param_1 + 0x40f4) -= 4;
        int* last = *(int**)PI(param_1, 0x40f4);
        if (*last != 0)
          ((void(__thiscall*)(void*))(*(void***)*last)[1])((void*)*last);
      } while (p != (int*)PI(param_1, 0x40f4));
    }
  }
}

// @ 0x00b783b0
u8 Sim_s00b7_7db0::FUN_00b783b0(u32 param_2, float* param_3)
{
  void* pwVar3 = (void*)param_2;
  if ((u32)param_2 < 0x31018ba) {
    if (param_2 != 0x31018b9) {
      if ((u32)param_2 < 0x25630b8) {
        if (param_2 != 0x25630b7) {
          if (param_2 == 0xf62def) {
            float fVar9 = param_3[4];
            float fVar1 = param_3[6];
            void* iVar5 = FUN_00b3d320();
            if (iVar5 != 0) {
              u32 gm = FUN_00b5b800();
              switch (gm) {
                case 0x1654c01: case 0x1654c02: case 0x1654c04:
                case 0x1654c05: case 0x1654c06: case 0x1654c08: {
                  FUN_00b3d320();
                  void* p = FUN_00b1de80();
                  if (p != 0 && PF_s00b7_7db0(p, 8) == fVar1 && PF_s00b7_7db0(p, 0x10) == fVar9) {
                    u32 m = FUN_00b5b800();
                    FUN_00b72640(m);
                    return 0;
                  }
                }
              }
            }
          } else if (param_2 == 0x0182c582) {
            float local[4];
            FUN_00b746a0(&local[0], (void*)0x01464fe0);
            float* local_8 = &local[0];
            if (local[0] != local[2]) {
              do {
                int iVar5 = *(int*)(local_8 + 2);
                if (iVar5 != 0) {
                  int iVar7 = PI((void*)iVar5, 0x70);
                  if (iVar7 != 0) {
                    PI((void*)iVar5, 0x38) = PI((void*)iVar7, 0xc);
                    PI((void*)iVar5, 0x3c) = PI((void*)iVar7, 0x10);
                    PI((void*)iVar5, 0x40) = PI((void*)iVar7, 0x14);
                  }
                }
                FUN_00b72d80(&local[0], 0);
              } while (local_8 != &local[2]);
              return 0;
            }
          }
          return 0;
        }
      } else if (param_2 != 0x2e9977e) {
        return 0;
      }
    }
LAB_00b78500:
    if (((PU(this, 0x20) & 1) != 0) &&
        ((param_2 != 0x2e9977e) || (((PU(this, 0x20) >> 1) & 1) != 0))) {
      if (param_3[2] != 0.0f) {
        FUN_00b76f10(param_3, param_2);
        return 1;
      }
      FUN_00b77db0(this, param_2);
    }
    return 1;
  }
  if (param_2 != 0x32f76e7) {
    if (param_2 == 0x477c00d) goto LAB_00b78500;
    if (param_2 != 0x4d80d9e) return 0;
  }
  float local_8 = param_3[2];
  if (local_8 == 0.0f) return 0;
  float fVar9 = param_3[6];
  float local_18 = param_3[0];
  u8 cVar4 = SP_cPropertyList_GetDescription((void*)0x015fd918, 0x4233e37);
  if (cVar4 == 0) return 0;
  float* param_3b = 0;
  float local_24 = 0.0f;
  void* param_2b = 0;
  void* tm = FUN_00b3d3b0();
  int iVar5 = PI(tm, 0x17c);
  u32 uVar2 = (PI(tm, 0x180) - iVar5) / 0x24;
  u32 uVar11 = 0;
  if (3 < (int)uVar2) {
    int iVar7 = ((uVar2 - 4) >> 2) + 1;
    float* pfVar10 = (float*)(iVar5 + 0xc);
    float* pfVar8 = (float*)(iVar5 + 0x30);
    uVar11 = iVar7 * 4;
    do {
      if (pwVar3 == (void*)0x32f76e7) {
        if (pfVar10[-1] == fVar9) {
LAB_00b78630:
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar10[1];
          local_24 = pfVar10[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar10[3];
LAB_00b78651:
          if (pwVar3 == (void*)0x32f76e7) goto LAB_00b78659;
          if (pwVar3 == (void*)0x4d80d9e) goto LAB_00b78668;
          goto LAB_00b7868d;
        }
LAB_00b78659:
        if (pfVar8[-1] == fVar9) goto LAB_00b7866c;
LAB_00b78695:
        if (pfVar8[8] != fVar9) {
LAB_00b786d2: {
          float fVar1 = pfVar8[0x11];
          if (fVar1 == fVar9) {
            param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[0x13];
            local_24 = pfVar8[0x14];
            param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0x15];
          }
          goto done;
        }
        }
LAB_00b786a9:
        param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[10];
        local_24 = pfVar8[0xb];
        param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0xc];
LAB_00b786ca:
        if (pwVar3 == (void*)0x32f76e7) goto LAB_00b786d2;
        if (pwVar3 == (void*)0x4d80d9e) {
          float fVar1 = pfVar8[0x12];
          if (fVar1 == fVar9) {
            param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[0x13];
            local_24 = pfVar8[0x14];
            param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0x15];
          }
        }
      } else {
        if (pwVar3 != (void*)0x4d80d9e) goto LAB_00b78651;
        if (*pfVar10 == fVar9) goto LAB_00b78630;
LAB_00b78668:
        if (*pfVar8 == fVar9) {
LAB_00b7866c:
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[1];
          local_24 = pfVar8[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[3];
LAB_00b7868d:
          if (pwVar3 == (void*)0x32f76e7) goto LAB_00b78695;
          if (pwVar3 == (void*)0x4d80d9e) goto LAB_00b786a4;
          goto LAB_00b786ca;
        }
LAB_00b786a4:
        if (pfVar8[9] == fVar9) goto LAB_00b786a9;
        {
          float fVar1 = pfVar8[0x12];
          if (fVar1 == fVar9) {
            param_3b = (float*)(uintptr_t)*(u32*)&pfVar8[0x13];
            local_24 = pfVar8[0x14];
            param_2b = (void*)(uintptr_t)*(u32*)&pfVar8[0x15];
          }
        }
      }
done:
      pfVar10 += 0x24;
      pfVar8 += 0x24;
      iVar7 = iVar7 - 1;
    } while (iVar7 != 0);
  }
  if (uVar11 < uVar2) {
    float* pfVar10 = (float*)(iVar5 + 0xc + uVar11 * 0x24);
    int iVar5b = uVar2 - uVar11;
    do {
      if (pwVar3 == (void*)0x32f76e7) {
        float fVar1 = pfVar10[-1];
        if (fVar1 == fVar9) {
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar10[1];
          local_24 = pfVar10[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar10[3];
        }
      } else if (pwVar3 == (void*)0x4d80d9e) {
        float fVar1 = *pfVar10;
        if (fVar1 == fVar9) {
          param_3b = (float*)(uintptr_t)*(u32*)&pfVar10[1];
          local_24 = pfVar10[2];
          param_2b = (void*)(uintptr_t)*(u32*)&pfVar10[3];
        }
      }
      pfVar10 += 9;
      iVar5b = iVar5b - 1;
    } while (iVar5b != 0);
  }
  FUN_00b3d350();
  if ((float)(uintptr_t)param_3b <= 0.0f) return 0;
  if (local_18 == 0.0f) return 0;
  float* pfVar10 = (float*)((int)local_8 + 0xc);
  float fVar9b = local_18;
  do {
    float l18 = pfVar10[-2];
    float l14 = pfVar10[-1];
    float l10 = pfVar10[0];
    float l8 = pfVar10[1];
    FUN_00b83c40(&l18,
                 l8 * (float)(uintptr_t)param_3b +
                 (float)sqrt((double)((l10 * l10 + l14 * l14) + l18 * l18)) * 0.00390625f,
                 0x10000000, 0);
    float fVar12 = FUN_00c9eb60();
    if (fVar12 <= (float)(uintptr_t)param_2b) {
      FUN_00b83c40(&l18, l8 * local_24, 0x20000000, 0);
    }
    pfVar10 += 0x13;
    fVar9b = (float)((int)fVar9b - 1);
  } while (fVar9b != 0.0f);
  return 0;
}

// @ 0x00b78860
void __fastcall FUN_00b78860(void* param_1)
{
  PU(param_1, 0x20) = PU(param_1, 0x20) & 0xfffffffb;
  PU(param_1, 0x55a0) = 0;
  FUN_00b77aa0();
}

// @ 0x00b794e0
void* ObMgr::Init(int* a, int* b)
{
    PoolDesc d;
    char* base = (char*)this + 0x43c;

    d.head = 0;
    ((FixedPoolBase*)&d)->Init(base, 0x1800, 0x18, 8, 0);
    d.begin = base;
    d.end = base + 0x1800;
    d.elem = 0x18;
    d.alloc = (char*)this + 0x34;

    int h = (int)FUN_00921340(0x101);
    FUN_00b745f0(h, a, (void**)&b, (void**)&b, b, (void**)&b, &d);

    *(F2*)((char*)this + 0x10) = F2(10000.0f, 2.0f);
    *(int*)((char*)this + 0x18) = 0;

    unsigned n = (unsigned)((PoolBase*)&d)->SizeFor(*(int*)((char*)this + 0xc));
    if (n > *(unsigned*)((char*)this + 8))
        DoFreeNodes((int)n);
    return this;
}

// @ 0x00b795c0
int* ObMgr::Insert(int* out, int* key, int unused)
{
    FindRes fr;
    ((BucketAlloc*)((char*)this + 0x10))->Find(&fr, *(int*)((char*)this + 8),
                                               *(int*)((char*)this + 0xc), 1);
    if (fr.found)
        FreeNode(fr.value);

    unsigned h = (unsigned)(key[2] ^ key[0]);
    unsigned idx = h % (unsigned)*(int*)((char*)this + 8);
    int* node = (int*)NewNode(key);
    idx *= 4;
    int bucket = *(int*)(*(int*)((char*)this + 4) + idx);
    int* e = FindNode((int*)bucket, key, h);

    if (e == 0) {
        *(int*)((char*)node + 0xc70) = bucket;
        *(int*)(*(int*)((char*)this + 4) + idx) = (int)node;
    } else {
        *(int*)((char*)node + 0xc70) = *(int*)((char*)e + 0xc70);
        *(int*)((char*)e + 0xc70) = (int)node;
    }

    ++*(int*)((char*)this + 0xc);
    out[0] = (int)node;
    out[1] = *(int*)((char*)this + 4) + idx;
    (void)unused;
    return out;
}

// @ 0x00b79740
void* ObMgr::Construct()
{
    int one;

    *(void**)this = (void*)0x13eb384;
    ((Gonzago*)((char*)this + 4))->Ctor();
    *(void**)((char*)this + 4) = (void*)0x14650e8;
    *(void**)this = (void*)0x14650cc;
    *(void**)((char*)this + 8) = (void*)0x14650c8;

    *(int*)((char*)this + 0x20) = 0;
    *(int*)((char*)this + 0x24) = 0;
    *(int*)((char*)this + 0x28) = 0;
    *(int*)((char*)this + 0x2c) = 0;
    *(int*)((char*)this + 0x30) = 0;
    *(int*)((char*)this + 0x34) = 0;

    ((ObMgr*)((char*)this + 0x38))->Init(&one, &one);
    ((ObMgr*)((char*)this + 0x2094))->Init(&one, &one);

    *(void**)((char*)this + 0x40f0) = (char*)this + 0x4108;
    *(void**)((char*)this + 0x40f4) = (char*)this + 0x4108;
    *(void**)((char*)this + 0x40f8) = (char*)this + 0x4908;
    *(int*)((char*)this + 0x4104) = 0;

    *(void**)((char*)this + 0x4908) = (char*)this + 0x4920;
    *(void**)((char*)this + 0x490c) = (char*)this + 0x4920;
    *(int*)((char*)this + 0x491c) = 0;
    *(void**)((char*)this + 0x4910) = (char*)this + 0x49e0;

    ((PoolCtor2*)((char*)this + 0x49e0))->Init(&one, &one);
    ((PoolCtor2*)((char*)this + 0x4f30))->Init(&one, &one);

    *(float*)((char*)this + 0x5480) = g_156b390;
    *(float*)((char*)this + 0x5484) = g_156b394;
    *(float*)((char*)this + 0x5488) = g_156b398;
    *(float*)((char*)this + 0x548c) = g_16880d4;
    *(float*)((char*)this + 0x5490) = g_16880d8;
    *(float*)((char*)this + 0x5494) = g_16880dc;
    *(float*)((char*)this + 0x5498) = g_156b39c;
    *(float*)((char*)this + 0x549c) = g_156b3a0;
    *(float*)((char*)this + 0x54a0) = g_156b3a4;
    *(float*)((char*)this + 0x54a4) = g_156b3a8;

    *(float*)((char*)this + 0x54b8) = g_1485720;
    *(float*)((char*)this + 0x54bc) = g_1470f1c;
    *(int*)((char*)this + 0x54b0) = 1;
    *(int*)((char*)this + 0x54ac) = (int)&g_154df28;
    *(int*)((char*)this + 0x54b4) = 0;
    *(int*)((char*)this + 0x54c0) = 0;

    *(float*)((char*)this + 0x54d8) = g_1485720;
    *(float*)((char*)this + 0x54dc) = g_1470f1c;
    *(int*)((char*)this + 0x54d0) = 1;
    *(int*)((char*)this + 0x54cc) = (int)&g_154df28;
    *(int*)((char*)this + 0x54d4) = 0;
    *(int*)((char*)this + 0x54e0) = 0;

    *(float*)((char*)this + 0x54f8) = g_1485720;
    *(float*)((char*)this + 0x54fc) = g_1470f1c;
    *(int*)((char*)this + 0x54f0) = 1;
    *(int*)((char*)this + 0x54ec) = (int)&g_154df28;
    *(int*)((char*)this + 0x54f4) = 0;
    *(int*)((char*)this + 0x5500) = 0;

    *(int*)((char*)this + 0x551c) = 0;
    *(void**)((char*)this + 0x5508) = (char*)this + 0x5520;
    *(void**)((char*)this + 0x550c) = (char*)this + 0x5520;
    *(void**)((char*)this + 0x5510) = (char*)this + 0x55a0;
    *(int*)((char*)this + 0x55a0) = 0;

    *(int*)((char*)this + 0x55bc) = 0;
    *(void**)((char*)this + 0x55a8) = (char*)this + 0x55c0;
    *(void**)((char*)this + 0x55ac) = (char*)this + 0x55c0;
    *(void**)((char*)this + 0x55b0) = (char*)this + 0x56c0;
    *(float*)((char*)this + 0x56d0) = g_1485720;
    *(float*)((char*)this + 0x56d4) = g_1470f1c;
    *(int*)((char*)this + 0x56c8) = 1;
    *(int*)((char*)this + 0x56c4) = (int)&g_154df28;
    *(int*)((char*)this + 0x56cc) = 0;
    *(int*)((char*)this + 0x56d8) = 0;

    *(int*)((char*)this + 0x20) |= 1;

    void* p = EAAllocate(0x84, "Simulator/cObstacleManager", 0, 0, 0, 0);
    if (p != 0)
        *(void**)((char*)this + 0x55a4) = ((Grid_s00b7_94e0*)p)->Construct();
    else
        *(void**)((char*)this + 0x55a4) = 0;
    return this;
}

// @ 0x00b79a60
void Sub::Detach()
{
    int h = *(int*)((char*)this + 0x20);
    if (h != 0) {
        *(int*)((char*)this + 0x20) = 0;
        RemoveHandler(h, *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28),
                      *(int*)((char*)this + 0x2c), *(int*)((char*)this + 0x30));
    }
    ((Sim_s00b7_94e0*)((char*)this - 4))->Teardown();
}

// @ 0x00b79aa0
void ObMgr::Destroy()
{
    char* p = (char*)this + 0x38;
    char* q = (char*)this + 0x2094;

    FUN_00b77b60(p, 0, 0);
    FUN_00b77b60(q, 0, 0);

    ((HashtableOps*)p)->FreeTable(*(int**)(p + 4), *(unsigned*)(p + 8));
    *(int*)(p + 0xc) = 0;

    ((HashtableOps*)q)->FreeTable(*(int**)(q + 4), *(unsigned*)(q + 8));
    *(int*)(q + 0xc) = 0;

    char* r = (char*)this + 0x54a8;
    ((HashtableOps*)r)->Free70(*(int**)(r + 4), *(unsigned*)(r + 8));
    *(int*)(r + 0xc) = 0;

    r = (char*)this + 0x54c8;
    ((HashtableOps*)r)->Free68(*(int**)(r + 4), *(unsigned*)(r + 8));
    *(int*)(r + 0xc) = 0;

    r = (char*)this + 0x54e8;
    ((HashtableOps*)r)->Free68(*(int**)(r + 4), *(unsigned*)(r + 8));
    *(int*)(r + 0xc) = 0;

    FUN_00b74130(this);

    void* pm = PlanetModelGet();
    void* sub = *(void**)((char*)pm + 0x24);
    void** vt = *(void***)sub;
    int* arr;
    int cnt = ((FnCount)vt[0xb0 / 4])(sub, &arr);

    ((PointerVec*)((char*)this + 0x55a8))->Resize(cnt);
    CopyPtrs(arr, (char*)arr + cnt * 4, *(void**)((char*)this + 0x55a8));

    FUN_00b76160(this);

    int n = (*(int*)((char*)this + 0x40f4) - *(int*)((char*)this + 0x40f0)) >> 2;
    while (n < g_156b3ac) {
        void* nm = NounManager(0x3ed8573);
        int* noun = (int*)CreateNoun(nm);
        if (noun != 0) {
            void** nvt = *(void***)noun;
            ((FnV)nvt[0])(noun);
        }
        {
            void** nvt = *(void***)noun;
            ((FnV)nvt[0x44 / 4])(noun);
        }
        int* end = *(int**)((char*)this + 0x40f4);
        if (end != *(int**)((char*)this + 0x40f8)) {
            *(int**)((char*)this + 0x40f4) = end + 1;
            if (end != 0) {
                *end = (int)noun;
                if (noun != 0) {
                    void** nvt = *(void***)noun;
                    ((FnV)nvt[0])(noun);
                }
            }
        } else {
            ((PointerVec*)((char*)this + 0x40f0))->Grow(end, &noun);
        }
        if (noun != 0) {
            void** nvt = *(void***)noun;
            ((FnV)nvt[1])(noun);
        }
        ++n;
    }

    void* self = (char*)this + 4;
    void** svt = *(void***)self;
    ((FnV2)svt[0x38 / 4])(self, 0, 0);
}

// @ 0x00b79c30
void ObMgr::Query(V3* dir, PointerVec* out, unsigned mask, float radius, char flag, V3* p7)
{
    if (*(int*)(*(int*)((char*)this + 0x55a4) + 0x24) ==
        *(int*)(*(int*)((char*)this + 0x55a4) + 0x28))
        return;

    V3 pos;
    ((PlanetModel_s00b7_94e0*)PlanetModelGet())->DirectionToSurfacePosition(&pos, dir);

    int zero = 0;
    int mem[0x100];
    BufferedVec buf;
    buf.begin = mem;
    buf.end = mem;
    buf.cap = (char*)mem + 0x400;
    buf.pad0 = 0;
    buf.pad1 = 0;
    buf.pad2 = 0;
    buf.Init(mem, 0x100, &zero);

    int n = (*(Grid_s00b7_94e0**)((char*)this + 0x55a4))->QuerySphereResult(
        radius, (float*)&pos, 0x100, (void**)&buf);
    buf.Resize(n);

    memcpy(out->begin, out->end, 0);
    out->end -= out->end - out->begin;
    out->Reserve(n);

    for (int i = 0; i < n; ++i) {
        int o = ((int*)buf.begin)[i];
        if ((mask & (1u << *(int*)(o + 0x88))) == 0)
            continue;
        int w = *(int*)(o + 0x70);
        if (w != 0 && ((*(unsigned*)(w + 4) >> 15) & 1) == 0)
            continue;
        float dx = dir->x - *(float*)(o + 0x38);
        float dy = dir->y - *(float*)(o + 0x3c);
        float dz = dir->z - *(float*)(o + 0x40);
        float r = *(float*)(o + 0x44) + radius;
        if (dx * dx + dy * dy + dz * dz < r * r) {
            int* end = out->end;
            if (end < out->cap) {
                out->end = end + 1;
                if (end != 0)
                    *end = o;
            } else {
                out->Push(end, &o);
            }
        }
    }

    if (flag != 0) {
        V3* v = p7;
        if (v == 0)
            v = &pos;
        FUN_00b779c0(out->begin, out->end, v->x, v->y, v->z);
    }

    if (buf.begin != 0 && *(int*)((char*)buf.begin - 4) != 0)
        operator delete(buf.begin);
}

// @ 0x00b79e50
int ObMgr::Count(V3* dir, float radius, char filter)
{
    int count = 0;
    int i = 0;
    if (*(int*)(*(int*)((char*)this + 0x55a4) + 0x24) ==
        *(int*)(*(int*)((char*)this + 0x55a4) + 0x28))
        return count;

    V3 pos;
    ((PlanetModel_s00b7_94e0*)PlanetModelGet())->DirectionToSurfacePosition(&pos, dir);

    int zero = 0;
    int mem[0x100];
    BufferedVec buf;
    buf.begin = mem;
    buf.end = mem;
    buf.cap = (char*)mem + 0x400;
    buf.pad0 = 0;
    buf.pad1 = 0;
    buf.pad2 = 0;
    buf.Init(mem, 0x100, &zero);

    int n = (*(Grid_s00b7_94e0**)((char*)this + 0x55a4))->QuerySphereResult(
        radius, (float*)&pos, 0x100, (void**)&buf);
    buf.Resize(n);

    if (n > 3) {
        int* p = (int*)buf.begin + 2;
        int blocks = (int)(((unsigned)(n - 4) >> 2) + 1);
        i = blocks * 4;
        do {
            OB_COUNT_TEST(p[-2]);
            OB_COUNT_TEST(p[-1]);
            OB_COUNT_TEST(p[0]);
            OB_COUNT_TEST(p[1]);
            p += 4;
        } while (--blocks != 0);
    }
    if (i < n) {
        do {
            OB_COUNT_TEST(((int*)buf.begin)[i]);
            ++i;
        } while (i < n);
    }
    if (buf.begin != 0 && *(int*)((char*)buf.begin - 4) != 0)
        operator delete(buf.begin);

    return count;
}

// @ 0x00b7a1d0
void ObMgr::QueryNear(V3* dir, float radius, unsigned mask, PointerVec* out)
{
    if (*(int*)(*(int*)((char*)this + 0x55a4) + 0x24) ==
        *(int*)(*(int*)((char*)this + 0x55a4) + 0x28))
        return;

    V3 pos;
    ((PlanetModel_s00b7_94e0*)PlanetModelGet())->DirectionToSurfacePosition(&pos, dir);

    int zero = 0;
    int mem[0x100];
    BufferedVec buf;
    buf.begin = mem;
    buf.end = mem;
    buf.cap = (char*)mem + 0x400;
    buf.pad0 = 0;
    buf.pad1 = 0;
    buf.pad2 = 0;
    buf.Init(mem, 0x100, &zero);

    int n = (*(Grid_s00b7_94e0**)((char*)this + 0x55a4))->QuerySphereResult(
        radius, (float*)&pos, 0x100, (void**)&buf);
    buf.Resize(n);

    memcpy(out->begin, out->end, 0);
    out->end -= out->end - out->begin;
    out->Reserve(n);

    for (int i = 0; i < n; ++i) {
        int o = ((int*)buf.begin)[i];
        if ((mask & (1u << *(int*)(o + 0x88))) == 0)
            continue;
        int w = *(int*)(o + 0x70);
        if (w != 0 && ((*(unsigned*)(w + 4) >> 15) & 1) == 0)
            continue;

        float ox = *(float*)(o + 0x38);
        float oy = *(float*)(o + 0x3c);
        float oz = *(float*)(o + 0x40);
        float dx = dir->x - ox;
        float dy = dir->y - oy;
        float dz = dir->z - oz;
        if (sqrtf(dz * dz + (dx * dx + dy * dy)) <
            *(float*)(o + 0x4c) + *(float*)(o + 0x48)) {
            float len = sqrtf(oy * oy + oz * oz + ox * ox) + *(float*)(o + 0x4c);
            float inv = 1.0f / sqrtf(oy * oy + oz * oz + ox * ox);
            V3 qP;
            qP.x = (ox * inv) * len;
            qP.y = (inv * oy) * len;
            qP.z = (inv * oz) * len;
            V3 qB;
            qB.x = (ox + qP.x) * 0.5f;
            qB.y = (oy + qP.y) * 0.5f;
            qB.z = (oz + qP.z) * 0.5f;

            if (QuatDist(dir, &qB, &qP) < *(float*)(o + 0x48) + radius ||
                QuatDist(dir, (V3*)(o + 0x38), &qB) < *(float*)(o + 0x44) + radius) {
                int* end = out->end;
                if (end < out->cap) {
                    out->end = end + 1;
                    if (end != 0)
                        *end = o;
                } else {
                    out->Push(end, &o);
                }
            }
        }
    }

    if (buf.begin != 0 && *(int*)((char*)buf.begin - 4) != 0)
        operator delete(buf.begin);
}

// @ 0x00b7a4a0
int cSpawner::CollectLights(float* from, float* to, float radius, IntVector* out, char mode)
{
    if (mpGrid->mEntities.mpBegin == mpGrid->mEntities.mpEnd)
        return out->count();

    uint32_t empty = 0;
    cFixedIntVector results;
    results.insert(results.mpBegin, 0x100, &empty);
    int count = mpGrid->Query3Result(from, to, radius, 0x100, (void**)results.mpBegin);
    if (mode == 0) {
        results.resize(count);
        *out = results;
    } else {
        out->clear();
        for (int i = 0; i < count; ++i) {
            cQueryObj* pObj = (cQueryObj*)results.mpBegin[i];
            // an object that has an aux record is only visible while bit 15 of its
            // flags is set (00b7a586..00b7a58c jumps to the skip block when it is clear)
            if (pObj->mAux != 0 && (pObj->mAux->mFlags & 0x8000) == 0)
                continue;
            float r = pObj->mRadius + radius;
            Vec3_s00b7_a4a0 dir(to[0] - from[0], to[1] - from[1], to[2] - from[2]);
            Vec3_s00b7_a4a0 off(from[0] - pObj->mPosition.x, from[1] - pObj->mPosition.y,
                     from[2] - pObj->mPosition.z);
            float aa = dir.z * dir.z + dir.y * dir.y + dir.x * dir.x;
            float bb = dir.z * off.z + dir.x * off.x + dir.y * off.y;
            float cc = off.z * off.z + off.x * off.x + off.y * off.y - r * r;
            float disc = bb * bb - aa * cc;
            if (disc < 0.0f)
                continue;
            float t = sqrtf(disc);
            if (t - bb < 0.0f)          // entry point beyond the segment start
                continue;
            if (-bb - t > aa)           // exit point beyond the segment end
                continue;
            out->push_back((uint32_t)pObj);
        }
    }
    return out->count();
}

// @ 0x00b7a710
void cSpawner::ResetLights()
{
    cLightVector& lights = mLights;
    uint32_t count = (uint32_t)(lights.mpEnd - lights.mpBegin);
    if (count != 0)
        ClearModels();

    cModelFactory* pModel = ModelManager()->GetModel(0x00EB9968);
    if (pModel)
        pModel->AddRef();

    lights.resize(0x14);

    count = (uint32_t)(lights.mpEnd - lights.mpBegin);
    for (uint32_t i = 0; i < count; ++i) {
        cBeamLight** pSlot = &lights.mpBegin[i];
        if (*pSlot == 0) {
            cBeamLight* pNew = pModel->CreateInstance((const void*)0x02E81370, g_lightModel, 0x10);
            cBeamLight* pOld = *pSlot;
            if (pNew != pOld) {
                if (pNew)
                    ++pNew->mRefCount;
                *pSlot = pNew;
                if (pOld != 0) {
                    if (pOld->mRefCount > 1)
                        --pOld->mRefCount;
                    else
                        pOld->Release();
                }
            }
            cBeamLight* pLight = *pSlot;
            pLight->mMatrix = g_identity;
            pLight->mScale = 1.0f;
            pLight->mPosition = g_zeroVec;
            pLight->mDirty = 0;
            pLight->mDirtyCount = 0;
            pLight->mFlags &= ~1u;
            pLight->mOwner->Update(pLight, 0);
        }
    }
    if (pModel)
        pModel->Release();
}

// @ 0x00b7b070
void Mgr::Sample(float* camPos, float* entry)
{
    char* self = (char*)this;
    float tmp[3], tgt[3], startP[3], camP[3], endP[3];
    float dx, dy, dz, scale, radius2, len, inv, f8;
    float value, curValue;
    float* p;
    void*  pm;
    uint32 flags, mask;
    char   forced, adjust;
    SampleVec v;

    v.spare0 = 0;   // allocator bookkeeping above the inline storage
    v.spare1 = 0;   // ... and the ownership word the teardown reads as begin[-1]
    pm = FUN_00b3d350();
    p = entry;
    if (pm != 0) {
        p = ((Ext*)pm)->FUN_00b81630(tmp, entry);
    }
    endP[0] = p[0];
    endP[1] = p[1];
    endP[2] = p[2];
    scale   = entry[3];
    mask    = *(uint32*)((char*)entry + 0x14);
    dx = endP[0] - camPos[0];
    dy = endP[1] - camPos[1];
    dz = endP[2] - camPos[2];
    flags = ((uint8*)entry)[0x10];
    startP[0] = dx;
    startP[1] = dy;
    startP[2] = dz;
    p = camPos;
    if (pm != 0) {
        p = ((Ext*)pm)->FUN_00b81630(camP, camPos);
    }
    tgt[0] = p[0];
    tgt[1] = p[1];
    tgt[2] = p[2];
    {
        float f9 = endP[0] - tgt[0];
        float f6 = endP[1] - tgt[1];
        float f7 = endP[2] - tgt[2];
        radius2 = *(float*)(self + 0x54a0) * *(float*)(self + 0x54a0);
        v.begin = v.buf;
        inv = 1.0f / sqrtf((f6 * f6 + (f7 * f7 + f9 * f9)) + DAT_013ec4b8);
        f8 = *(float*)(self + 0x5480);
        len = sqrtf((dy + DAT_013ec4b8) * (dy + DAT_013ec4b8) +
                    ((dx + DAT_013ec4b8) * (dx + DAT_013ec4b8) +
                     (dz + DAT_013ec4b8) * (dz + DAT_013ec4b8)));
        dx = endP[0];
        dy = endP[1];
        dz = endP[2];
        if (0.0f < f8) {
            dx = ((inv * f9) * scale) * f8 + endP[0];
            dz = ((f7 * inv) * scale) * f8 + endP[2];
            dy = ((f6 * inv) * scale) * f8 + endP[1];
        }
        f8 = f8 * scale + len;
        camP[0] = dx;
        camP[1] = dy;
        camP[2] = dz;
        v.end = v.begin;
        p = ((Ext*)pm)->FUN_00b81630(startP, endP);
        endP[0] = p[0];
        endP[1] = p[1];
        endP[2] = p[2];
        ((Ext*)this)->FUN_00b7a4a0(endP, camP, *(float*)(self + 0x5480) * scale, &v, 0);
        {
            void* ctx = FUN_00b3d4d0();
            forced = 0;
            if (*(int*)((char*)ctx + 0x2c) == 1 || *(int*)((char*)ctx + 0x2c) == 2) {
                ctx = FUN_00b3d4d0();
                forced = 1;
                if (*(char*)((char*)ctx + 0x2a) == 0) {
                    forced = 0;
                }
            }
        }
        {
            float** it = (float**)v.begin;
            while (it != (float**)v.end) {
                float* obj = *it;
                if ((mask & (1u << (*(uint32*)((char*)obj + 0x88) & 0x1f))) != 0) {
                    float cur = *obj;
                    value = 1.0f;
                    curValue = 0.0f;
                    adjust = 0;
                    if (((Ext*)this)->FUN_00b72b60(entry, startP, *(float*)(self + 0x5480) * scale,
                                                   obj, flags, &curValue, &adjust) != 0) {
                        if (forced == 0) {
                            float a, b;
                            if (adjust == 0) {
                                float ddx = tgt[0] - *(float*)((char*)obj + 0x38);
                                float ddy = tgt[1] - *(float*)((char*)obj + 0x3c);
                                float ddz = tgt[2] - *(float*)((char*)obj + 0x40);
                                if (((ddz * ddz + ddy * ddy) + ddx * ddx) <= radius2) {
                                    a = *(float*)(self + 0x549c) * *(float*)(self + 0x5484);
                                    b = 1.0f;
                                } else {
                                    a = *(float*)(self + 0x5484);
                                    b = curValue;
                                }
                            } else {
                                a = *(float*)(self + 0x5484);
                                b = curValue;
                            }
                            value = (a - 1.0f) * b + 1.0f;
                        } else {
                            value = 0.0f;
                        }
                        if (DAT_01687ad0 != 0) {
                            value = 0.99f;
                        }
                    }
                    if (*(float*)((char*)obj + 0x7c) != 0.0f && *(int*)((char*)obj + 0x78) != 0) {
                        void*  node = 0;
                        void*  key  = (void*)obj;
                        float* slot;
                        node = ((Ext*)(self + 0x49e0))->FUN_00645ed0(&node, &key);
                        if (node == *(void**)(*(int*)(self + 0x49e4) + *(int*)(self + 0x49e8) * 4)) {
                            slot = ((Ext*)(self + 0x49e0))->FUN_00b76400(&key);
                            *slot = value;
                        } else {
                            float* nv = &value;
                            float* ex = (float*)((char*)node + 4);
                            if (!(value < *ex)) {
                                nv = ex;
                            }
                            *ex = *nv;
                        }
                    }
                    (void)cur;
                }
                it = it + 1;
            }
        }
    }
    if (v.begin != 0 && *(int*)((char*)v.begin - 4) != 0) {
        FUN_00f47380(v.begin);
    }
}

// @ 0x00b7b590
void Mgr::Update(int a, float b)
{
    char* self = (char*)this;
    if (*(int*)(self + 0x4908) != *(int*)(self + 0x490c)) {
        void* app  = FUN_0067dd10();
        void* host = ((VtApp*)app)->FUN_00000050();
        void* view = ((VtHost*)host)->FUN_0000001c();
        if (view != 0) {
            float cam[3] = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float v1[3]  = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float v2[3]  = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float v3[3]  = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float* p;
            float* e;
            ((Ext*)view)->FUN_007c3d30(cam, v1, v2, v3);
            p = *(float**)(self + 0x4908);
            e = *(float**)(self + 0x490c);
            if (p != e) {
                do {
                    if (((p[0] != DAT_01687ad4) || (p[1] != DAT_01687ad8) || (p[2] != DAT_01687adc))
                        && (p[3] != 0.0f)) {
                        ((Mgr*)this)->Sample(cam, p);
                    }
                    p += 6;
                } while (p != *(float**)(self + 0x490c));
            }
            ((Ext*)self)->FUN_00b76e00(a, b);
        }
        {
            Vec18* begin = (Vec18*)*(uint32*)(self + 0x4908);
            Vec18* end   = (Vec18*)*(uint32*)(self + 0x490c);
            FUN_00720250_s00b7_b070(end, end, begin);
            *(Vec18**)(self + 0x490c) += -(end - begin);
        }
    }
}

// @ 0x00b7b710
char Mgr::SerializeIt(void* arg)
{
    char* mgr = (char*)this - 4;
    Serializer ser;
    char  r;
    ((Ext*)&ser)->FUN_00692f90(mgr, DAT_0156b478, 0x1a80d26);
    r = ((Ext*)&ser)->FUN_00693e10(arg);
    if ((*(uint8*)((char*)this + 0x1c) & 4) != 0) {
        ((Ext*)mgr)->FUN_00b7a710();
    } else {
        ((Ext*)mgr)->FUN_00b77aa0();
    }
    return r;
}

// @ 0x00b7b780
void Mgr::Destroy()
{
    char* self = (char*)this;
    uint32 v;
    uint32 bv;

    v = *(uint32*)(self + 0x55a4);
    *(void**)self        = (void*)DAT_014650cc;
    *(void**)(self + 4)  = (void*)DAT_014650e8;
    *(void**)(self + 8)  = (void*)DAT_014650c8;
    if (v != 0) {
        ((Ext*)v)->FUN_00750310();
        FUN_00f47380((void*)v);
    }
    RELEASE(self + 0x56c0, FUN_00b73070);

    ((Ext*)(self + 0x55a8))->FUN_005f3680(*(uint32*)(self + 0x55a8), *(uint32*)(self + 0x55ac));
    bv = *(uint32*)(self + 0x55a8);
    if (bv != 0 && *(int*)(bv - 4) != 0) {
        FUN_00f47380((void*)bv);
    }
    ((Ext*)(self + 0x5508))->FUN_005f3680(*(uint32*)(self + 0x5508), *(uint32*)(self + 0x550c));
    bv = *(uint32*)(self + 0x5508);
    if (bv != 0 && *(int*)(bv - 4) != 0) {
        FUN_00f47380((void*)bv);
    }
    RELEASE(self + 0x54e8, FUN_00b75bf0);
    RELEASE(self + 0x54c8, FUN_00b75bf0);
    RELEASE(self + 0x54a8, FUN_00b75b80);
    RELEASE(self + 0x4f30, FUN_00a24480);
    RELEASE(self + 0x49e0, FUN_00a1b6c0);

    bv = *(uint32*)(self + 0x4908);
    if (bv != 0 && *(int*)(bv - 4) != 0) {
        FUN_00f47380((void*)bv);
    }
    ((Ext*)(self + 0x40f0))->FUN_00ae6970();
    RELEASE(self + 0x2094, FUN_00b759b0);
    RELEASE(self + 0x38, FUN_00b759b0);

    v = *(uint32*)(self + 0x24);
    if (v != 0) {
        *(uint32*)(self + 0x24) = 0;
        FUN_00571db0(v, *(int*)(self + 0x28), *(int*)(self + 0x2c), *(int*)(self + 0x30),
                     *(int*)(self + 0x34));
    }
    ((Ext*)(self + 4))->FUN_00b5b9a0();
    *(void**)self = (void*)DAT_013eb394;
}

// @ 0x00b7ba50
#pragma pack(pop)
void Mgr::UpdatePooled(int a, int b)
{
    char      dummy;
    UpdatePooledLocals loc;
    SpawnTable_s00b7_b070 spawn;
    HtNode_s00b7_b070*   node;
    HtNode_s00b7_b070**  slot;

    (void)b;
    loc.sec = (float)(uint32)a * DAT_013f9428;

    ((Ext*)&spawn)->FUN_00b77780(&dummy, &dummy);
    loc.mgr = (Mgr*)((char*)this - 4);
    loc.mgr->Update((int)&spawn, loc.sec);

    // Retire every live pool entry that the ambience pass did not claim.
    loc.pool = &((MgrPoolView*)(void*)this)->mPool;
    slot = loc.pool->mpBucketArray;
    node = *slot;
    if (node == 0) {
        do {
            ++slot;
            node = *slot;
        } while (node == 0);
    }
    if (node != loc.pool->mpBucketArray[loc.pool->mBucketCount]) {
        do {
            loc.end = spawn.End();
            loc.endNode = loc.end.mpNode;
            loc.found = spawn.Find(node->mKey);
            if (loc.found.mpNode == loc.endNode
                || (loc.obj = (PoolObj*)node->mValue) == 0
                || VCALLR0(loc.obj, 0x2c) != 0
                || (((Ext*)loc.mgr)->FUN_00b74f80(loc.obj, 1.0f, loc.sec),
                    loc.obj->mScale < DAT_01485720)) {
                node = node->mpNext;
                if (node == 0) {
                    do {
                        ++slot;
                        node = *slot;
                    } while (node == 0);
                }
            } else {
                uint32 id;
                SgEntry* entry;

                ((Ext*)loc.mgr)->FUN_00b74590(loc.obj);
                switch (loc.obj->mKind) {
                case 0:  id = 0x3a8be428; break;
                case 1:  id = 0x029c388a; break;
                case 2:  id = 0x6d60a1cc; break;
                default: id = 0;          break;
                }
                entry = FUN_00b3d3b0_s00b7_b070()->FUN_00b2a690(id, loc.obj->mExtra, loc.obj->mIndex);
                if (entry == 0) {
                    loc.obj->mFlags &= ~1u;
                    if (loc.obj->mpModel != 0) {
                        ((Ext*)loc.obj->mpModel)->FUN_00a887b0(loc.obj->mIndex, 1.0f);
                    } else if (loc.obj->mpA != 0) {
                        loc.obj->mpA->mFlags |= 1u;
                        VCALL2_s00b7_b070(loc.obj->mpA->mpOwner, 0x16c, loc.obj->mpA, 1);
                    }
                }
                HtIter_s00b7_b070* next = loc.pool->Erase(&loc.erased, node, slot);
                node = next->mpNode;
                slot = next->mpBucket;
            }
        } while (node != loc.pool->mpBucketArray[loc.pool->mBucketCount]);
    }

    // Re-seed the pool from the spawn table built by the ambience pass.
    slot = spawn.mpBucketArray;
    node = *slot;
    if (node == 0) {
        do {
            ++slot;
            node = *slot;
        } while (node == 0);
    }
    if (node != spawn.mpBucketArray[spawn.mBucketCount]) {
        do {
            uint32  key = node->mKey;
            PoolObj* value = (PoolObj*)node->mValue;
            uint32* dst = loc.pool->FindOrInsert(&key);
            uint32  old = *dst;

            if ((uint32)value != old) {
                if (value != 0) value->AddRef();
                *dst = (uint32)value;
                if (old != 0) ((PoolObj*)old)->Release();
            }
            node = node->mpNext;
            if (node == 0) {
                do {
                    ++slot;
                    node = *slot;
                } while (node == 0);
            }
        } while (node != spawn.mpBucketArray[spawn.mBucketCount]);
    }

    RELEASE(&spawn, FUN_00a24480);
}

// @ 0x00b7bd50
void cSPPieMenu::sub_b7bd50(int a, int b)
{
    (void)a; (void)b;
    SpawnerBase* base = (SpawnerBase*)((char*)this - 4);
    base->sub_b77b60(&mTable2090, 0, 0);
    if (mFlags1c & 4) base->sub_b7a880();

    void** it = mItems.mpBegin;
    if (it == mItems.mpEnd) return;
    do {
        PieObject* m = (PieObject*)*it;
        if (!m) {
            void** end = mItems.mpEnd;
            if (it + 1 < end) sub_5f4e10(it + 1, end, it);
            end -= 1;
            mItems.mpEnd = end;
            RefObject* tail = (RefObject*)*end;
            if (tail) RefRelease(tail);
        } else if (!(m->mFlags & 0x4000) || (m->mFlags & 0x40000)) {
            it += 1;
        } else {
            PropertyList_s00b7_bd50* pl = (PropertyList_s00b7_bd50*)m->mpPropertyList;
            bool bErase = false;
            if (pl) {
                bool bFirst = pl->GetBoolProperty(0x3f6d22a);
                bool bSecond = pl->GetBoolProperty(0x37575e5);
                bErase = !bSecond || bFirst;
            }
            if (!bErase) {
                Vec3_s00b7_bd50 delta;
                delta.f[0] = m->mPosB[0] - m->mPosA[0];
                delta.f[1] = m->mPosB[1] - m->mPosA[1];
                delta.f[2] = m->mPosB[2] - m->mPosA[2];
                float radius = 3.4028234663852886e+38f;
                Property_s00b7_bd50* p;
                if (m->mpPropertyList &&
                    pl->GetProperty(0x254cf89, &p) && p->mType == 0xd) {
                    radius = *p->sub_41ea70();
                }
                float halfDiag = SqrtF(delta.f[0] * delta.f[0] +
                                       delta.f[1] * delta.f[1]) * 0.5f;
                if (radius > halfDiag) radius = halfDiag;
                float f48 = radius;
                if (m->mpPropertyList &&
                    pl->GetProperty(0x254cf8f, &p) && p->mType == 0xd) {
                    f48 = *p->sub_41ea70();
                }
                float f4c = delta.f[2];
                if (m->mpPropertyList &&
                    pl->GetProperty(0x254cf97, &p) && p->mType == 0xd) {
                    f4c = *p->sub_41ea70();
                }
                PieItem* item = base->sub_b74370();
                if (item) Vv0(item, 0);
                Vv0(item, 0x54);
                item->mIds = m->mVecA;
                item->mRadius = radius;
                item->mF48 = f48;
                item->mF4c = f4c;
                item->mF68 = m->mF58;
                item->mSlot70.sub_478db0(m);
                item->mF6c = m->mF60;
                item->mF74 = 0;
                RefObject* old = (RefObject*)item->mpF78;
                if (old) {
                    item->mpF78 = 0;
                    RefRelease(old);
                }
                item->mF7c = g_01687af0;
                item->mF80 = g_01687af4;
                item->mF84 = g_01687af8;
                item->mF5c = 0;
                item->mF50 = 0;
                item->mF58 = 0;
                void* p54 = item->mpF54;
                if (p54) {
                    item->mpF54 = 0;
                    Vv0(p54, 0x38);
                }
                item->mF88 = 4;
                PieMgr* mgr = sub_b3d3c0()->mpPieMgr55a4;
                if (mgr && item->mF64 < 0 && mgr->mpBegin24 != mgr->mpEnd28) {
                    item->mF64 = mgr->sub_703d50(item->mF48, &item->mIds, item);
                }
                PieNotifyMsg msg;
                msg.mType = 1;
                msg.mpUnk = 0;
                msg.mpItem = item;
                Vv0(item, 0);
                void* out = 0;
                mNotifier34.sub_b75240(&out, &msg, 0);
                if (msg.mpItem) Vv0(msg.mpItem, 4);
                Vv0(item, 4);
            }
            it = mItems.sub_b05d80(it);
            continue;
        }
    } while (it != mItems.mpEnd);
}

// @ 0x00b7c160
void cSPPieMenu::SetSomething(int value)
{
    if (b2) {
        b2 = 0;
        mField55a0 = 0;
        sub_b77aa0();
    }
    if (b0) b2 = 1;
    else    b2 = 0;
    if (b2) {
        mField55a0 = value;
        sub_b7a710();
    }
}

// @ 0x00b7c1b0
void* HashTable_s00b7_bd50::sub_b7c1b0(const void* key)
{
    HashIter it;
    sub_b74800(&it, key);
    if (it.node != End()) {
        return (char*)it.node + 4;
    }
    MenuItemValue tmp;
    tmp.sub_b75820();
    ScreenValue value;
    value.mKey = *(const u32_s00b7_bd50*)key;
    value.mValue.sub_b778b0(&tmp);
    HashIter ins;
    // EASTL insert(&out, &value, bool): the original materialises the bool into a byte slot
    // and the compiler passes that dword slot including its stale upper bytes, so equiv sees
    // the stack residue there; the source-level flag is simply false.
    sub_b79680(&ins, &value, 0);
    FreeValueBuffer(&value.mValue);
    FreeValueBuffer(&tmp);
    return (char*)ins.node + 4;
}

// @ 0x00b7c290
int cSPPieMenu::sub_b7c290(cSpatialObject* obj, void* res)
{
    if (!obj || !obj->mpPropertyList) return 0;
    HashTable_s00b7_bd50* map = &mMap54c8;
    HashIter it;
    map->sub_b74800(&it, &obj);
    if (it.node != map->End()) {
        return (int)((char*)it.node + 4);
    }
    MenuItemValue* value = (MenuItemValue*)map->sub_b7c1b0(&obj);
    value->mRadius = obj->mXf.mF10;
    if (!sub_b78880(value, obj, res, 1)) {
        HashIter it2;
        map->sub_b74800(&it2, &obj);
        HashIter dummy;
        map->sub_b766b0(&dummy, it2);
        return 0;
    }
    return (int)value;
}

// @ 0x00b7c360
void* cSPPieMenu::sub_b7c360(cSpatialObject* obj, void* res)
{
    if (!obj || !(obj->mFlags & 0x4000) || !obj->mpPropertyList || !res) return 0;
    float x = obj->mXf.mF10;
    HashTable_s00b7_bd50* map = &mMap54e8;
    HashIter it;
    map->sub_b74800(&it, &obj);
    if (it.node != map->End()) {
        void* node = it.node;
        if (!sub_41dd30((char*)node + 8, &obj->mXf.mVec04) &&
            NodeValue(node)->mXf.mF10 == x &&
            !sub_41dd90((char*)node + 0x18, &obj->mXf.mVec14)) {
            return NodeValue(node);
        }
    }
    MenuItemValue* value = (MenuItemValue*)map->sub_b7c1b0(&obj);
    value->mRadius = x * 1.05f;
    ((CTransformAssign*)value)->Assign(&obj->mXf);
    if (!sub_b78880(value, obj, res, 1)) {
        map->sub_b76620(&obj);
    }
    return value;
}

// @ 0x00b7c480
void* cSPPieMenu::sub_b7c480(void* model_)
{
    PieObject* model = (PieObject*)model_;
    if (!model) return 0;
    if (model->mKind88 == 4) {
        void* mm = sub_67dd80();
        void* resource = VRet1(mm, 0x1c, (void*)0x3fbae24);
        return (void*)sub_b7c290((cSpatialObject*)model->mpTarget70, resource);
    }
    float height = *(float*)((char*)model->sub_b73e70() + 0x10);
    if (model->mFlags34 & 4) height = 1.0f;
    ModelKey key;
    key.k0 = model->mKey6c;
    key.k1 = 0;
    key.k2 = g_0156b430;
    HashTable_s00b7_bd50* map = &mMap54a8;
    HashIter4 it;
    map->sub_b74740(&it, &key);
    void* node = it.node;
    char** bucket = (char**)it.bucket;
    void* last = it.last;
    while (node != last) {
        if (AbsF(((MenuItemValue*)((char*)node + 4))->mRadius - height)
            <= 1.52587890625e-05f) {
            return (char*)node + 0xc;
        }
        node = *(void**)((char*)node + 0xc70);
        while (!node) {
            node = *++bucket;
        }
    }
    void* mm = sub_67dd80();
    void* factory = VRet1(mm, 0x1c, (void*)0xeb9968);
    if (factory) Vv0(factory, 0);
    RefObject* m2 = (RefObject*)VRet3(factory, 0xc, (void*)(size_t)key.k0,
                                      (void*)(size_t)key.k2, 0);
    MenuItemValue* val = 0;
    if (m2) {
        m2->mnRefCount += 1;
        MenuItemValue tmp;
        ModelValue pv;
        tmp.sub_b75820();
        pv.mKey = key;
        pv.mValue.sub_b778b0(&tmp);
        HashIter ins;
        map->sub_b795c0(&ins, &pv, 0);
        FreeValueBuffer(&pv.mValue);
        FreeValueBuffer(&tmp);
        val = (MenuItemValue*)((char*)ins.node + 0xc);
        val->mRadius = height;
        if (!sub_b78880(val, m2, factory, 0)) {
            HashIter dummy;
            map->sub_b76580(&dummy, ins);
            val = 0;
        }
        RefIfaceCall(m2, 0x16c, 0);
        RefRelease(m2);
    }
    Vv0(factory, 4);
    return val;
}

// @ 0x00b7c750
void __cdecl PieMenuAcceptCallback(int param, int unused, char condition)
{
    if (condition) {
        void* p = SP_GameInputManager();
        Vv1(p, 0x68, param);
    }
}

// @ 0x00b7c790
void __cdecl cSPPieMenu_ReleaseAndInput(int param)
{
    cSPUIPieMenuItemWinProc* p = g_pPieWinProc;
    if (p) Vv0(p, 0x00);
    void* gm = SP_GameInputManager();
    Vv2(gm, 0x64, param, 1);
    if (g_pPieWinProc && p == g_pPieWinProc) {
        p->Hide();
        Vv0(g_pPieWinProc, 0x24);
        cSPUIPieMenuItemWinProc* q = g_pPieWinProc;
        if (q) {
            g_pPieWinProc = 0;
            Vv0(q, 0x04);
        }
        g_bPieMenuVisible = 0;
    }
    if (p) Vv0(p, 0x04);
}

// @ 0x00b7c870
bool __cdecl cSPPieMenu_ContainsWindow(void* hwnd)
{
    if (g_bPieMenuVisible) {
        return g_pPieWinProc->ContainsWindow(hwnd);
    }
    return false;
}

// @ 0x00b7c890
void ButtonVec::SetItemTextColor(int id, int color)
{
    PieButton* it = mpBegin;
    if (it != mpEnd) {
        do {
            if (it->mId == id) {
                it->mColor = color;
                if (g_pPieWinProc) {
                    cSPUIPieMenu_SetItemTextColor(id, color);
                }
                return;
            }
            it = (PieButton*)((char*)it + 0x18);
        } while (it != mpEnd);
    }
}

// @ 0x00b7c8e0
bool __cdecl PieMenu_ScreenPosition_GetPosition(cSpatialObject* obj, float* outX, float* outY)
{
    if (obj) {
        float bounds[6];
        float* r = (float*)VRet1(obj, 0x6c, bounds);
        float center[3];
        center[0] = (r[0] + r[3]) * 0.5f;
        center[1] = (r[4] + r[1]) * 0.5f;
        center[2] = (r[5] + r[2]) * 0.5f;
        void* app = SP_App();
        float proj[3];
        void* camera = VRet(app, 0x58);
        ((S7c4180*)camera)->sub_7c4180(proj, center);
        float area[4];
        sub_805ea0(area);
        float cx = ((proj[0] + 1.0f) * area[2]) * 0.5f;
        float cy = ((1.0f - proj[1]) * area[3]) * 0.5f;
        *outX = cx;
        *outY = cy;
        return true;
    }
    return false;
}

// @ 0x00b7c9c0
cPieMenuScreenPosition::cPieMenuScreenPosition(cSpatialObject* pObject)
{
    vftable2 = (void**)0x13ec458;
    mField8 = 0;
    vftable = (void**)0x14651bc;
    vftable2 = (void**)0x14651ac;
    mpObject = pObject;
    if (mpObject) Vv0(mpObject, 0xbc);
    mBaseDistance = 0.0f;
    if (mpObject) {
        float* pos = (float*)VRet(mpObject, 0x2c);
        float px = pos[0], py = pos[1], pz = pos[2];
        void* app = SP_App();
        Viewer* viewer = (Viewer*)VRet(app, 0x58);
        float cam[3];
        viewer->GetCameraLocationInfo(cam, 0, 0, 0);
        float dx = cam[0] - px, dy = cam[1] - py, dz = cam[2] - pz;
        double sum = (double)dx * dx + (double)dy * dy + (double)dz * dz;
        __m128d sv = _mm_sqrt_pd(_mm_load_sd(&sum));
        mBaseDistance = (float)_mm_cvtsd_f64(sv);
    }
}

// @ 0x00b7cb00
bool cPieMenuScreenPosition::GetPosition(float* outX, float* outY)
{
    cSpatialObject* obj = mpObject;
    return PieMenu_ScreenPosition_GetPosition(obj, outX, outY);
}

// @ 0x00b7cb20
bool cPieMenuScreenPosition::ShouldBeVisible()
{
    PlanetModel_s00b7_bd50* planet = (PlanetModel_s00b7_bd50*)SP_PlanetModel();
    if (!mpObject || !planet) return false;
    float* pos = (float*)VRet(mpObject, 0x2c);
    float px = pos[0], py = pos[1], pz = pos[2];
    VRetF(mpObject, 0x70);
    float f8 = planet->GetRadius();
    ((OtherObj*)mpObject)->SomeFloat();
    void* app = SP_App();
    Viewer* viewer = (Viewer*)VRet(app, 0x58);
    float cam[3];
    viewer->GetCameraLocationInfo(cam, 0, 0, 0);
    float dx = cam[0] - px, dy = cam[1] - py, dz = cam[2] - pz;
    float dist = (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
    if (dist < mBaseDistance) mBaseDistance = dist;
    if (dist < mBaseDistance * 6.0f && dist < f8 * 2.0f) return true;
    return false;
}

// @ 0x00b7cc60
void __fastcall FUN_00b7cc60(int* vec, int /*edx unused*/, int* screen, int flag)
{
    IV_s00b7_cc60* pie = 0;
    if (DAT_0168817c != 0) {
        FUN_00818330();
        ((void(__thiscall*)(void*))VT(DAT_0168817c, 0x24))(DAT_0168817c);
        void* old = DAT_0168817c;
        if (old) {
            DAT_0168817c = 0;
            ((void(__thiscall*)(void*))VT(old, 4))(old);
        }
        void* gim = SP_GameInputManager();
        ((void(__thiscall*)(void*, int, int))VT(gim, 0x64))(gim, 0x4518450, 1);
    }
    DAT_01688150 = screen;
    DAT_01688154 = 1;
    void* mem = operator_new(200, "Simulator/Pie Menu", 0, 0, 0, 0);
    if (mem)
        pie = (IV_s00b7_cc60*)((void*(__fastcall*)(void*))SPUIPieMenu_ctor)(mem);
    IV_s00b7_cc60* old = (IV_s00b7_cc60*)DAT_0168817c;
    if (pie != old) {
        if (pie) ((void(__thiscall*)(void*))VT(pie, 0))((void*)pie);
        DAT_0168817c = pie;
        if (old) ((void(__thiscall*)(void*))VT(old, 4))((void*)old);
    }
    char ok = ((char(__thiscall*)(IV_s00b7_cc60*, const wchar_t*, const wchar_t*, int, int, int, int))VT(DAT_0168817c, 0x1c))
                  ((IV_s00b7_cc60*)DAT_0168817c, L"PieMenuBase", L"PieMenuIcons", 0x40464100, 0, 0, 0);
    if (ok) {
        PieVec* pv = (PieVec*)vec;
        void* gp = DAT_0168817c;
        ((void(__fastcall*)(void*, int, void*, void*))FUN_00817eb0)(gp, 0, (void*)FUN_00b7c790, vec);
        int count = (int)((char*)pv->mpEnd - (char*)pv->mpBegin) / 0x18;
        for (int i = 0; i < count; i++) {
            PieEntry* e = (PieEntry*)((char*)pv->mpBegin + i * 0x18);
            ((void(__fastcall*)(void*, int, int, int, int, int))FUN_0081a940)
                (gp, 0, e->mField10, e->mField00, e->mField14, 1);
        }
        gp = DAT_0168817c;
        ((void(__fastcall*)(void*, int, void*, void*))FUN_008182c0)(gp, 0, (void*)FUN_00b7c750, vec);
    }

    float f1, f2;
    if (flag != 0 && screen != 0) {
        Rect6f rect;
        Vec3f pt;
        Vec3f out;
        Rect4f wa;
        Rect6f* r = (Rect6f*)((void*(__thiscall*)(int*, void*))VT(screen, 0x6c))(screen, &rect);
        pt.x = (r->f0 + r->f3) * 0.5f;
        pt.y = (r->f4 + r->f1) * 0.5f;
        pt.z = (r->f5 + r->f2) * 0.5f;
        void* app = SP_App();
        void* app2 = ((void*(__thiscall*)(void*, void*, void*))VT(app, 0x58))(app, &out, &pt);
        ((void(__fastcall*)(void*, int, void*, void*))FUN_007c4180)(app2, 0, &out, &pt);
        FUN_00805ea0(&wa);
        f1 = ((out.x + 1.0f) * wa.mWidth) * 0.5f;
        f2 = ((1.0f - out.y) * wa.mHeight) * 0.5f;
    } else {
        FUN_00804ed0(&f1, &f2);
    }

    void* srv = FUN_00b3d240();
    ((void(__thiscall*)(void*, int))VT(srv, 0x64))(srv, 0x303d8d78);
    void* sp = operator_new(0x14, "Simulator/cPieMenuScreenPosition", 0, 0, 0, 0);
    void* scr = sp ? ((void*(__fastcall*)(void*, int, int*))SPUIPieMenuScreenPos_ctor)(sp, 0, screen) : 0;
    ((void(__fastcall*)(void*, int, float, float, void*, int))FUN_00819ad0)
        (DAT_0168817c, 0, f1, f2, scr, 7);
}

// @ 0x00b7cfa0
WStr_s00b7_cc60* WStr_s00b7_cc60::copy(const WStr_s00b7_cc60* src)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCap = 0;
    int count = (int)((const char*)src->mpEnd - (const char*)src->mpBegin) >> 1;
    AllocateSelf(count + 1);
    void* dst = mpBegin;
    DoInsertValue(dst, src->mpBegin, count * 2);
    void* e = (char*)dst + count * 2;
    mpEnd = e;
    *(unsigned short*)e = 0;
    f10 = src->f10;
    f14 = src->f14;
    return this;
}

// @ 0x00b7d000
int* FUN_00b7d000(int* src, int* end, int* dst)
{
    if (src == end)
        return dst;
    do {
        if (dst) {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
            int s = src[0];
            int count = (src[1] - s) >> 1;
            unsigned n = (unsigned)count + 1;
            if (n < 2) {
                dst[0] = (int)0x1667bac;
                dst[1] = (int)0x1667bac;
                dst[2] = (int)0x1667bae;
            } else {
                int size = (int)n * 2;
                int m = (int)operator_new(size, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                dst[0] = m;
                dst[1] = m;
                dst[2] = m + size;
            }
            int base = dst[0];
            DoInsertValue((void*)base, (const void*)s, (unsigned)(count * 2));
            int e = base + count * 2;
            dst[1] = e;
            *(unsigned short*)e = 0;
            dst[4] = src[4];
            dst[5] = src[5];
        }
        src += 6;
        dst += 6;
    } while (src != end);
    return dst;
}

// @ 0x00b7d180
void __fastcall FUN_00b7d180(int* vec, int /*edx unused*/, int* pos, int* value)
{
    WVec* v = (WVec*)vec;
    WStr_s00b7_cc60* end = (WStr_s00b7_cc60*)v->mpEnd;
    if (end != (WStr_s00b7_cc60*)v->mpCap) {
        if (pos <= value && value < (int*)end)
            value = (int*)((char*)value + 0x18);
        if (end)
            end->copy(end - 1);
        FUN_00b7d120(pos, (int*)(end - 1), (int*)end);
        if (value != pos)
            ((WStr_s00b7_cc60*)pos)->assign(((WStr_s00b7_cc60*)value)->mpBegin, ((WStr_s00b7_cc60*)value)->mpEnd);
        ((WStr_s00b7_cc60*)pos)->f10 = ((WStr_s00b7_cc60*)value)->f10;
        ((WStr_s00b7_cc60*)pos)->f14 = ((WStr_s00b7_cc60*)value)->f14;
        v->mpEnd = (int*)(end + 1);
        return;
    }
    int count = (int)(end - (WStr_s00b7_cc60*)v->mpBegin);
    int cap;
    if (count == 0)
        cap = 1;
    else {
        cap = count * 2;
        if (cap == 0)
            cap = 0;
    }
    WStr_s00b7_cc60* n;
    if (cap == 0)
        n = 0;
    else
        n = (WStr_s00b7_cc60*)operator_new(cap * 0x18, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    WStr_s00b7_cc60* mid = (WStr_s00b7_cc60*)FUN_00b7d000((int*)v->mpBegin, pos, (int*)n);
    FUN_00b7cf50((int*)v->mpBegin, pos, (int)n);
    if (mid)
        mid->copy((WStr_s00b7_cc60*)value);
    WStr_s00b7_cc60* newEnd = (WStr_s00b7_cc60*)FUN_00b7d000(pos, (int*)end, (int*)(mid + 1));
    FUN_00b7cf50(pos, (int*)end, (int)(mid + 1));
    if (v->mpBegin && ((AllocHeader*)v->mpBegin)[-1].mSize != 0)
        operator_delete__((void*)v->mpBegin);
    v->mpEnd = (int*)newEnd;
    v->mpBegin = (int*)n;
    v->mpCap = (int*)((char*)n + cap * 0x18);
}

// @ 0x00b7d420
bool ServerObj::OnPieMsg(int msg, int arg)
{
    bool r = true;
    if (msg == 0x29ffa8d && mMode == 3)
        mMode = 4;
    return r;
}

// @ 0x00b7d440
void __stdcall FUN_00b7d440(int value, int a2, unsigned flags, int* p4, int* p5, int* p6, int a7, int* p8, int* p9)
{
    int val = value;
    int zero = 0;
    if (p4) { p4[0] = val; p4[1] = zero; p4[2] = (flags & 0xe0ff28ff) | 0x2800; }
    if (p5) { p5[0] = val; p5[1] = zero; p5[2] = (flags & 0xe4ff28ff) | 0x4002800; }
    if (p6) { p6[0] = val; p6[1] = zero; p6[2] = (flags & 0xe5ff28ff) | 0x5002800; }
    if (p8) { p8[0] = val; p8[1] = zero; p8[2] = (flags & 0xe0ff28ff) | 0x2800; }
    if (p9) { p9[0] = val; p9[1] = zero; p9[2] = (flags & 0xe7ff28ff) | 0x7002800; }
}

// @ 0x00b7d4f0
int __stdcall FUN_00b7d4f0(int* p)
{
    int u1 = p[0];
    unsigned u2 = (unsigned)p[2];
    IV_s00b7_cc60* pm = (IV_s00b7_cc60*)SP_PropertyManager();
    char c = ((char(__thiscall*)(IV_s00b7_cc60*, int, unsigned))VT(pm, 0x28))(pm, u1, (u2 & 0xe0ff28ff) | 0x2800);
    if (c) {
        pm = (IV_s00b7_cc60*)SP_PropertyManager();
        c = ((char(__thiscall*)(IV_s00b7_cc60*, int, unsigned))VT(pm, 0x28))(pm, u1, (u2 & 0xe7ff28ff) | 0x7002800);
        if (c)
            return 1;
    }
    return 0;
}

// @ 0x00b7d580
void __stdcall FUN_00b7d580(int p)
{
    int* a = (int*)FUN_00c713e0((void*)p);
    if (*a == 0)
        return;
    int* b = (int*)FUN_00c713e0((void*)p);
    if (*(int*)((char*)b + 8) == 0)
        return;
    int* e = (int*)FUN_00c713e0((void*)p);
    int v1 = e[0];
    unsigned fl = (unsigned)e[2];
    IV_s00b7_cc60* pm = (IV_s00b7_cc60*)SP_PropertyManager();
    if (!((char(__thiscall*)(IV_s00b7_cc60*, int, unsigned))VT(pm, 0x28))(pm, v1, (fl & 0xe0ff28ff) | 0x2800))
        return;
    pm = (IV_s00b7_cc60*)SP_PropertyManager();
    if (!((char(__thiscall*)(IV_s00b7_cc60*, int, unsigned))VT(pm, 0x28))(pm, v1, (fl & 0xe7ff28ff) | 0x7002800))
        return;
    void* h1 = 0;
    pm = (IV_s00b7_cc60*)SP_PropertyManager();
    ((void(__thiscall*)(IV_s00b7_cc60*, int, unsigned, void**))VT(pm, 0x2c))(pm, v1, (fl & 0xe0ff28ff) | 0x2800, &h1);
    pm = (IV_s00b7_cc60*)SP_PropertyManager();
    ((void(__thiscall*)(IV_s00b7_cc60*, void*))VT(pm, 0x38))(pm, h1);
    if (h1) ((void(__thiscall*)(void*))VT(h1, 4))(h1);
    void* h2 = 0;
    pm = (IV_s00b7_cc60*)SP_PropertyManager();
    ((void(__thiscall*)(IV_s00b7_cc60*, int, unsigned, void**))VT(pm, 0x2c))(pm, v1, (fl & 0xe7ff28ff) | 0x7002800, &h2);
    pm = (IV_s00b7_cc60*)SP_PropertyManager();
    ((void(__thiscall*)(IV_s00b7_cc60*, void*))VT(pm, 0x38))(pm, h2);
    if (h2) { ((void(__thiscall*)(void*))VT(h2, 4))(h2); ((void(__thiscall*)(void*))VT(h2, 4))(h2); }
}

// @ 0x00b7d810
void __fastcall FUN_00b7d810(PieEditor* self, int /*edx unused*/, int /*a2*/, int /*a3*/)
{
    switch (self->mState28) {
    case 0: {
        if (self->mList.mpPrev != &self->mList && self->mpField30 == 0) {
            cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
            void* planet = pm->mpPlanet24;
            EditorTarget* target = (EditorTarget*)self->mList.mpPrev->mpPayload;
            if (target->mpField13c == 0) {
                FUN_00b7d7b0((ListNode**)&self->mList);
                return;
            }
            if (planet == 0) {
                ((void(__fastcall*)(void*, int, void*))FUN_00c70110)(&self->mpField30, 0, target);
                FUN_00b7d7b0((ListNode**)&self->mList);
                void* te = ((void*(__cdecl*)())SP_TerrainEditor)();
                ((void(__fastcall*)(void*, int, int))FUN_00f67890)(te, 0, 1);
                EditorTarget* o30 = (EditorTarget*)self->mpField30;
                Obj188* g = (Obj188*)((void*(__fastcall*)(void*))FUN_00b8da60)(o30->mpField13c);
                if (g->mpField00 == 0) {
                    void* x = ((void*(__fastcall*)(void*, int, void*, void*))FUN_00c713e0)(o30, 0, 0, 0);
                    pm->FUN_00b8d8a0((unsigned)x, false, 0);
                    void* planet2 = pm->mpPlanet24;
                    void* key = FUN_0067dd50();
                    ((void(__thiscall*)(void*, void*))VT(planet2, 0x8c))(planet2, key);
                    self->mFlag2d = 1;
                    self->mState28 = 1;
                    return;
                }
                FUN_00f355b0(o30->mpField13c);
                self->mFlag2d = 1;
                self->mState28 = 1;
                return;
            }
            LookupResult* a = (LookupResult*)((void*(__thiscall*)(void*))VT(planet, 8))(planet);
            LookupResult* b = (LookupResult*)((void*(__fastcall*)(void*))FUN_00c713e0)(target);
            if (a->mField10 == b->mField08) {
                a = (LookupResult*)((void*(__thiscall*)(void*))VT(planet, 8))(planet);
                b = (LookupResult*)((void*(__fastcall*)(void*))FUN_00c713e0)(target);
                if (a->mField08 == b->mField00 &&
                    ((char(__thiscall*)(void*))VT(planet, 0xd8))(planet) != 0) {
                    void* r = ((void*(__thiscall*)(void*))VT(planet, 0x10))(planet);
                    ((cPlanet*)r)->SetRampEnabled(false);
                    void* te = ((void*(__cdecl*)())SP_TerrainEditor)();
                    ((void(__fastcall*)(void*, int, int))FUN_00f678b0)(te, 0, 1);
                    ((void(__fastcall*)(void*, int, void*))FUN_00c70110)(&self->mpField30, 0, target);
                    FUN_00b7d7b0((ListNode**)&self->mList);
                    void* key = FUN_0067dd50();
                    if (!((char(__thiscall*)(void*, void*))VT(planet, 0x94))(planet, key)) {
                        key = FUN_0067dd50();
                        ((void(__thiscall*)(void*, void*))VT(planet, 0x8c))(planet, key);
                    }
                    self->mFlag2d = 0;
                    self->mState28 = 2;
                    return;
                }
            }
        }
        break;
    }
    case 1: {
        cPlanetModel* pm = (cPlanetModel*)SP_PlanetModel();
        void* planet = pm->mpPlanet24;
        void* key = FUN_0067dd50();
        if (!((char(__thiscall*)(void*, void*))VT(planet, 0x94))(planet, key)) {
            planet = pm->mpPlanet24;
            key = FUN_0067dd50();
            ((void(__thiscall*)(void*, void*))VT(planet, 0x8c))(planet, key);
        }
        planet = pm->mpPlanet24;
        if (planet != 0 &&
            ((char(__thiscall*)(void*))VT(planet, 0x50))(planet) != 0) {
            self->mState28 = 2;
            return;
        }
        break;
    }
    case 2:
        FUN_01037a20(self->mpField30);
        self->mState28 = 3;
        return;
    case 3:
        break;
    case 4: {
        if (self->mFlag2d != 0) {
            void* pm = SP_PlanetModel();
            ((void(__fastcall*)(void*))FUN_00b8c0f0)(pm);
        }
        LookupResult* e = (LookupResult*)((void*(__fastcall*)(void*))FUN_00c713e0)(self->mpField30);
        int v = e->mField00;
        void* te = ((void*(__cdecl*)())SP_TerrainEditor)();
        ((void(__fastcall*)(void*, int, int))FUN_00f67890)(te, 0, 0);
        te = ((void*(__cdecl*)())SP_TerrainEditor)();
        ((void(__fastcall*)(void*, int, int))FUN_00f678b0)(te, 0, 0);
        self->mState28 = 0;
        EditorTarget* o30 = (EditorTarget*)self->mpField30;
        if (o30 != 0) {
            self->mpField30 = 0;
            ((void(__thiscall*)(void*))VT(o30, 0xc0))(o30);
        }
        self->mFlag2d = 0;
        IV_s00b7_cc60* srv = (IV_s00b7_cc60*)SP_MessageServer();
        ((void(__thiscall*)(IV_s00b7_cc60*, unsigned, int, int))VT(srv, 0x14))(srv, 0x99eda4cd, v, 0);
        break;
    }
    }
}
