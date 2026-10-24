// Slice s00b230b0: the Simulator game-noun manager's posse/herd bookkeeping, the two city-order
// classes and the listener constructor next to them, the planet-event handler that wakes nearby
// objects, and the small eastl container helpers the surrounding code is built from.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------------------------
// externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------------------------
void* __cdecl EASTL_allocate(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                     // 0x00f473a0
void* __cdecl operator new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                           const char* pFile, int32_t nLine);                       // 0x00f473a0
void* __cdecl operator new(uint32_t nSize, void* pWhere);                           // placement new
void  __cdecl operator_delete(void* pBlock);                                        // 0x00f47380
void* __cdecl SP_memcpy(void* pDst, const void* pSrc, uint32_t nSize);              // 0x011e0744

uint8_t g_vtableMACOrderPrimary;        // 0x0145ef78 Simulator::cMilitaryAttackCityOrder
uint8_t g_vtableMACOrderSecondary;      // 0x0145ef64 Simulator::cMilitaryAttackCityOrder
uint8_t g_vtableConvertOrderPrimary;    // 0x0145efe8 Simulator::cCulturalConvertCityOrder
uint8_t g_vtableConvertOrderSecondary;  // 0x0145efd8 Simulator::cCulturalConvertCityOrder
uint8_t g_vtableListenerA;              // 0x013eb384 cListenerBase
uint8_t g_vtableListenerPrimary;        // 0x0145ef10 cListenerBase
uint8_t g_vtableListenerGonzago;        // 0x0145eec0 SP::cGonzagoSubsystem
uint8_t g_vtableListenerTail;           // 0x0145eeb8 cListenerBase

uint32_t g_listenerNameTable;           // 0x0154df28 the listener's event-name table
uint8_t  g_emptyString[];               // 0x01667bac ?gEmptyString16@eastl@@3PA_WA

uint8_t  g_funB21080;                   // 0x00b21080 game-data vector callback
uint8_t  g_funB22E80;                   // 0x00b22e80 ClearHolderVec
uint8_t  g_funB22EA0;                   // 0x00b22ea0 PushBackCast
uint8_t  g_funB1E520;                   // 0x00b1e520 game-data vector callback
uint8_t  g_funCD7D10;                   // 0x00cd7d10 game-data vector callback
uint8_t  g_funD3D420;                   // 0x00d3d420 game-data vector callback
uint8_t  g_funACCBB0;                   // 0x00accbb0 game-data vector callback
uint8_t  g_funB1E500;                   // 0x00b1e500 game-data vector callback
uint8_t  g_classKey18c6d19;             // 0x018c6d19 the class the noun lookup walks

uint8_t  g_gameModeAssembling;          // 0x01654c01
uint8_t  g_gameModeAdventuring;         // 0x01654c02

// the engine singletons and free functions
void*    __cdecl PlanetModel();                                     // 0x00b3d350
void*    __cdecl GetCurrentGameMode();                              // 0x00b5b800
void     __cdecl FUN_00b215a0();                                    // 0x00b215a0
void     __cdecl FUN_00c6ace0(void* pNoun, int32_t nMode);          // 0x00c6ace0
void     __stdcall FUN_00aea5d0(void* pEnd, const void* pValue);    // 0x00aea5d0
int32_t  __cdecl ClassifyA(void* pObject);                          // 0x00b1fe40
void     __cdecl FUN_00b206d0();                                    // 0x00b206d0
void     __cdecl rbtree_node_dtor(void* pNode);                     // 0x00d0c930
void     __cdecl EA_Messaging_RemoveHandler(uint32_t nHandler, uint32_t nA, uint32_t nB,
                                            uint32_t nC, uint32_t nD);  // 0x0571db0
void*    __stdcall GetGameDataVector(void* pF1, void* pF2, void* pF3, void* pF4,
                                     void* pKey);                   // 0x00b21340

// ---------------------------------------------------------------------------------------------
// small container models
// ---------------------------------------------------------------------------------------------
class cRefObj {
public:
    virtual void* v00();                        // +0x00 AddRef
    virtual void  v04();                        // +0x04 Release
};

// a noun: the objects the game-noun manager hands out
class cNoun {
public:
    virtual void* v00();                        // +0x000 AddRef
    virtual void  v04();                        // +0x004 Release
    virtual void* v08();                        // +0x008
    virtual void* v0c();                        // +0x00c
    virtual void* v10();                        // +0x010
    virtual void* v14();                        // +0x014
    virtual void* v18();                        // +0x018
    virtual void* v1c();                        // +0x01c
    virtual void* v20();                        // +0x020
    virtual void* v24();                        // +0x024
    virtual void* v28();                        // +0x028
    virtual void* v2c();                        // +0x02c
    virtual void* v30();                        // +0x030
    virtual void* v34();                        // +0x034
    virtual void* v38();                        // +0x038
    virtual void* v3c();                        // +0x03c
    virtual void* v40();                        // +0x040
    virtual void* v44();                        // +0x044
    virtual void* v48();                        // +0x048
    virtual void* v4c();                        // +0x04c
    virtual void* v50();                        // +0x050
    virtual void  v54();                        // +0x054

    uint32_t  mPad004[12];                      // +0x004 .. +0x033
    float     mf34;                             // +0x034 position
    float     mf38;                             // +0x038
    float     mf3c;                             // +0x03c
    uint32_t  mPad040[0x11];                    // +0x040 .. +0x083
    uint8_t   mb084;                            // +0x084
    uint8_t   mPad085[0x1f];                    // +0x085 .. +0x0a3
    uint32_t  mn0a4;                            // +0x0a4
    uint32_t  mPad0a8[0x2ac];                   // +0x0a8 .. +0x0b57
    uint32_t  mn0b58;                           // +0x0b58 flags
    uint32_t  mPad0b5c[0x66];                   // +0x0b5c .. +0x0f3
    uint32_t  mn0f4;                            // +0x0f4
    uint32_t  mPad0f8[0x19];                    // +0x0f8 .. +0x15b
    uint32_t  mn15c;                            // +0x15c
    void*     mp160;                            // +0x160
};

// a counted noun handle
class cAutoRef {
public:
    cNoun* mpObject;                            // +0x00

    cAutoRef(cNoun* pObject);
    ~cAutoRef();
    cAutoRef& operator=(cNoun* pObject);
    cAutoRef& Set(cNoun* pObject);              // 0x00b5f950 the out-of-line assignment
};

cAutoRef::cAutoRef(cNoun* pObject)
{
    mpObject = pObject;
    pObject->v00();
}

cAutoRef::~cAutoRef()
{
    if (mpObject != 0)
        mpObject->v04();
}

cAutoRef& cAutoRef::operator=(cNoun* pObject)
{
    cNoun* pOld = mpObject;
    if (pObject != pOld)
    {
        if (pObject != 0)
            pObject->v00();
        mpObject = pObject;
        if (pOld != 0)
            pOld->v04();
    }
    return *this;
}

typedef cAutoRef cAutoRefSlot;

// a begin/end/capacity vector of counted handles
class cRefVector {
public:
    cAutoRef* mpBegin;                          // +0x00
    cAutoRef* mpEnd;                            // +0x04
    cAutoRef* mpEndAlloc;                       // +0x08

    void erase(void* pFirst, void* pLast);      // 0x00e25bd0
    void push_back(cAutoRef& ref);
};

void cRefVector::push_back(cAutoRef& ref)
{
    if (mpEnd < mpEndAlloc)
    {
        cAutoRef* pSlot = mpEnd;
        mpEnd = pSlot + 1;
        if (pSlot != 0)
        {
            pSlot->mpObject = ref.mpObject;
            ref.mpObject->v00();
        }
    }
    else
    {
        FUN_00aea5d0(mpEnd, &ref);
    }
}

// an intrusive list head whose nodes are the payloads themselves
class cListHead;

class cListNode {
public:
    cListNode* mpNext;                          // +0x00
    cListNode* mpPrev;                          // +0x04
};

class cListHead {
public:
    cListNode* mpNext;                          // +0x00
    cListNode* mpPrev;                          // +0x04

    void Init()
    {
        mpNext = (cListNode*)this;
        mpPrev = (cListNode*)this;
    }
    void InitReversed()
    {
        mpPrev = (cListNode*)this;
        mpNext = (cListNode*)this;
    }
    void ClearNodes()
    {
        for (cListNode* pNode = mpNext; pNode != (cListNode*)this; )
        {
            cListNode* pNext = pNode->mpNext;
            pNode->mpPrev = 0;
            pNode->mpNext = 0;
            pNode = pNext;
        }
        mpPrev = (cListNode*)this;
        mpNext = (cListNode*)this;
    }
};

// the eastl red-black tree shape the manager's set maps use
class cRBTree {
public:
    void* volatile    mp00;                     // +0x00
    void* volatile    mp04;                     // +0x04 anchor/end node
    void* volatile    mp08;                     // +0x08
    void* volatile    mp0c;                     // +0x0c root node
    union {
        struct {
            uint8_t  volatile mb10;             // +0x10 the root node's colour
            uint8_t  mPad11[3];                 // +0x11 .. +0x13
        };
        uint32_t volatile mn10Word;             // +0x10 the same four bytes as one word
    };
    uint32_t volatile mn14;                     // +0x14

    void** find(void** ppOut, const void* pKey);            // 0x00e5c780
    cAutoRef* insert(const void* pKey);                     // 0x00dd85c0
    void clear();
};

void cRBTree::clear()
{
    rbtree_node_dtor(mp0c);
    mp08 = (void*)&mp04;
    mp0c = 0;
    mb10 = 0;
    mn14 = 0;
    mp04 = (void*)&mp04;
}

// a node of the counted-handle trees
class cRefNode {
public:
    cAutoRef  mObject;                          // +0x00 the counted handle
    uint32_t  mPad04[4];                        // +0x04 .. +0x13
    cNoun*    mp14;                             // +0x14 the node's key payload
};

// the bucket map of class sets
class cBucketMap {
public:
    uint32_t mPad00;                            // +0x00
    void*    mp04;                              // +0x04
    void*    mp08;                              // +0x08
    uint32_t mn0c;                              // +0x0c

    void FreeBucketNodes(void* pBegin, void* pEnd);         // 0x00b20a50
};

// the flush list at manager+0x98
class cFlushList {
public:
    uint32_t mPad00[5];                         // +0x00 .. +0x13

    void FUN_00b21da0(void* pArg);                          // 0x00b21da0
};

// ---------------------------------------------------------------------------------------------
// the game-noun manager: its listener part starts four bytes in, so the manager is a plain word
// followed by the part
// ---------------------------------------------------------------------------------------------
class cGameNounManager;
struct tPlanetEventMsg;

class cGNMPart {
public:
    uint32_t   mPad000[7];                      // +0x000 .. +0x01b
    cBucketMap mBucket1c;                       // +0x01c the class-set buckets
    uint32_t   mPad02c[4];                      // +0x02c .. +0x03b
    uint32_t   mn03c;                           // +0x03c message handler
    uint32_t   mn040;                           // +0x040
    uint32_t   mn044;                           // +0x044
    uint32_t   mn048;                           // +0x048
    uint32_t   mn04c;                           // +0x04c
    cAutoRef   mRef050;                         // +0x050
    cAutoRef   mRef054;                         // +0x054 the avatar's herd
    cRefVector mPosse058;                       // +0x058
    uint32_t   mPad064[2];                      // +0x064 .. +0x06b
    cAutoRef   mRef06c;                         // +0x06c
    cAutoRef   mRef070;                         // +0x070
    cListHead  mHead074;                        // +0x074
    cRefVector mVec07c;                         // +0x07c
    uint32_t   mPad088[2];                      // +0x088 .. +0x08f
    uint32_t   mn090;                           // +0x090
    cFlushList mFlush094;                       // +0x094
    uint32_t   mPad0a8[2];                      // +0x0a8 .. +0x0af
    uint32_t   mn0b0;                           // +0x0b0 flush list body
    uint32_t   mPad0b4[6];                      // +0x0b4 .. +0x0cb
    cRBTree    mTree0cc;                        // +0x0cc
    uint32_t   mPad0e4;                         // +0x0e4
    cRBTree    mTree0e8;                        // +0x0e8
    uint32_t   mPad100[2];                      // +0x100 .. +0x107
    cListHead  mHead108;                        // +0x108

    void FUN_00b237d0();                                    // 0x00b237d0
};

class cGameNounManager {
public:
    uint32_t  mn000;                            // +0x000
    cGNMPart  mPart;                            // +0x004

    void      RemoveNoun(cNoun* pNoun);                     // 0x00b225d0
    void      ProcessPending();                             // 0x00b22960
    cNoun*    CreateAndInit(void* pDesc, void* pA, void* pB, void* pC); // 0x00b22cc0
    cNoun*    CreateNoun(uint32_t nClassId);                // 0x00b20c60
    cNoun*    CreateDebugNoun(void* pPosition, cNoun* pOwner);          // 0x00b20e40
    void*     FUN_00b21000(void* pA, void* pB);             // 0x00b21000
    void      ClearPosseMembers();                          // 0x00b234c0
    void      ValidateClassSets();                          // 0x00b222a0
    void      Flush();                                      // 0x00b206d0

    void      FUN_00b23450(cNoun* pObject);                 // 0x00b23450
    void      FUN_00b23510();                               // 0x00b23510
    void      FUN_00b23610();                               // 0x00b23610
    cNoun*    FUN_00b23650(void* pDesc, void* pB, void* pC, void* pD, void* pE); // 0x00b23650
    void*     FUN_00b23690(uint32_t nArg);                  // 0x00b23690
    cNoun*    FUN_00b23940(float* pPosition, uint32_t nSpecies, uint32_t nGeneration,
                            uint8_t bOwner, float fHitpoint, uint8_t bDebug);     // 0x00b23940
    cNoun*    FUN_00b23a40(uint32_t nID);                   // 0x00b23a40
    uint8_t   FUN_00b23ab0(uint32_t nMsgId, tPlanetEventMsg* pMsg);          // 0x00b23ab0
};

// the manager part's teardown needs the manager out of a part pointer
inline cGameNounManager* ManagerOfPart(cGNMPart* pPart)
{
    return (cGameNounManager*)((uint8_t*)pPart - 4);
}

// the object vector FUN_00b23690 hands out (the vector itself starts four bytes in)
class cObjectVector {
public:
    cRefObj** mpBegin;                          // +0x00
    cRefObj** mpEnd;                            // +0x04
    cRefObj** mpEndAlloc;                       // +0x08
};

// the four bytes the manager keeps in front of that vector
class cVectorHolder {
public:
    uint32_t      mn000;                        // +0x00
    cObjectVector mVec;                         // +0x04
};

// ---------------------------------------------------------------------------------------------
// the vehicle group orders
// ---------------------------------------------------------------------------------------------
class cOrderVtblA {
public:
    virtual void* o00();                        // +0x00
};

class cOrderVtblB {
public:
    virtual void* o04();                        // +0x00 of the second base, at +0x04
};

class cVehicleGroupOrder : public cOrderVtblA, public cOrderVtblB {
public:
    uint32_t mPad008[0x23];                     // +0x008 .. +0x093

    cVehicleGroupOrder();                       // 0x00b22100
    void DtorBody();                            // 0x00b22180
};

// a begin/end/capacity vector of raw pointers
//
// The members are qualified volatile because the two order constructors below set their vtable
// pointers and then the pointers of these vectors: structured that way the compiler schedules the
// stores in source order, which is how retail lays the constructors out.
class cOrderVector {
public:
    void* volatile mpBegin;                     // +0x00
    void* volatile mpEnd;                       // +0x04
    void* volatile mpEndAlloc;                  // +0x08

    ~cOrderVector();                            // 0x00ae6930
};

class cCulturalConvertCityOrder;
class cMilitaryAttackCityOrder;

// The two order classes lay the vehicle-group order down at offset zero and then keep the
// simulator's own pair of vtable pointers over it, so the two pointers are plain members here
// and the group order's constructor/teardown body are reached by name.
class cMilitaryAttackCityOrder {
public:
    void* volatile mpVtable00;                  // +0x000
    void* volatile mpVtable04;                  // +0x004
    uint32_t      mPad008[0x23];                // +0x008 .. +0x093
    void* volatile mp094;                       // +0x094
    uint32_t      mPad098;                      // +0x098
    cOrderVector  mVec09c;                      // +0x09c
    uint32_t      mPad0a8[2];                   // +0x0a8 .. +0x0af
    cOrderVector  mVec0b0;                      // +0x0b0

    void BaseCtor();                            // 0x00b22100 cVehicleGroupOrder::cVehicleGroupOrder
    void DtorBody();                            // 0x00b22180 its teardown body

    cMilitaryAttackCityOrder();                             // 0x00b231b0
    cMilitaryAttackCityOrder* FUN_00b23260(uint8_t nFlags); // 0x00b23260
};

class cCulturalConvertCityOrder {
public:
    void* volatile mpVtable00;                  // +0x000
    void* volatile mpVtable04;                  // +0x004
    uint32_t      mPad008[0x23];                // +0x008 .. +0x093
    void* volatile mp094;                       // +0x094
    uint32_t      mPad098;                      // +0x098
    cOrderVector  mVec09c;                      // +0x09c
    uint32_t      mPad0a8[2];                   // +0x0a8 .. +0x0af

    void BaseCtor();                            // 0x00b22100 cVehicleGroupOrder::cVehicleGroupOrder

    cCulturalConvertCityOrder()
    {
        BaseCtor();
        void* pNull = 0;
        mpVtable00 = &g_vtableConvertOrderPrimary;
        mpVtable04 = &g_vtableConvertOrderSecondary;
        mp094 = pNull;
        mVec09c.mpBegin = pNull;
        mVec09c.mpEnd = pNull;
        mVec09c.mpEndAlloc = pNull;
    }
};

cCulturalConvertCityOrder* FUN_00b23770();      // 0x00b23770

// ---------------------------------------------------------------------------------------------
// the listener the simulator attaches to the game-noun manager
// ---------------------------------------------------------------------------------------------
class cInteractable;

class cGonzagoSubsystem {
public:
    uint32_t mPad00[8];                         // +0x00 .. +0x1f

    void BaseCtor();                            // 0x00b5b960
};

// a listener list head: the unit that owns it also clears the head's second word as a dword before
// the head is initialised, so the two words are reachable both ways
union cListUnit {
    cListHead          mHead;                   // both words
    uint32_t volatile  mWords[2];               // the same two words seen as dwords
};

// a flag word the constructor clears once as a dword and once as a byte
union cFlagWord {
    uint32_t volatile mnDword;
    uint8_t  volatile mnByte;
};

class cListenerBase {
public:
    void*     volatile mpVtable00;              // +0x000
    void*     volatile mpVtable04;              // +0x004
    void*     volatile mpVtable08;              // +0x008
    uint32_t  volatile mPad00c[6];              // +0x00c .. +0x023
    uint32_t  volatile mp024;                   // +0x024 the listener's name table
    uint32_t  volatile mn028;                   // +0x028
    uint32_t  volatile mn02c;                   // +0x02c
    float     volatile mf030;                   // +0x030
    float     volatile mf034;                   // +0x034
    uint32_t  volatile mn038;                   // +0x038
    uint32_t  volatile mPad03c;                 // +0x03c
    uint32_t  volatile mPad040[10];             // +0x040 .. +0x067
    uint32_t  volatile mPad068[2];              // +0x068 .. +0x06f
    uint32_t  volatile mn070;                   // +0x070
    uint32_t  volatile mn074;                   // +0x074
    cListUnit          mUnit078;                // +0x078
    uint32_t  volatile mn080;                   // +0x080
    uint32_t  volatile mn084;                   // +0x084
    uint32_t  volatile mn088;                   // +0x088
    uint32_t  volatile mPad08c[2];              // +0x08c .. +0x093
    uint32_t  volatile mn094;                   // +0x094
    uint32_t  volatile mPad098;                 // +0x098
    cListUnit          mUnit09c;                // +0x09c
    cFlagWord          mFlag0a4;                // +0x0a4
    cFlagWord          mFlag0a8;                // +0x0a8
    uint32_t  volatile mn0ac;                   // +0x0ac
    uint32_t  volatile mPad0b0[2];              // +0x0b0 .. +0x0b7
    cListUnit          mUnit0b8;                // +0x0b8
    uint32_t  volatile mn0c0;                   // +0x0c0
    cFlagWord          mFlag0c4;                // +0x0c4
    uint32_t  volatile mn0c8;                   // +0x0c8
    uint32_t  volatile mPad0cc;                 // +0x0cc .. +0x0cf
    cRBTree            mTree0d0;                // +0x0d0 .. +0x0e7
    uint32_t  volatile mPad0e8[2];              // +0x0e8 .. +0x0ef
    cListUnit          mUnit0f0;                // +0x0f0
    uint32_t  volatile mn0f8;                   // +0x0f8
    cFlagWord          mFlag0fc;                // +0x0fc
    uint32_t  volatile mn100;                   // +0x100
    uint32_t  volatile mPad104;                 // +0x104
    uint32_t  volatile mn108;                   // +0x108
    cListUnit          mUnit10c;                // +0x10c
    uint32_t  volatile mPad114;                 // +0x114
    uint32_t  volatile mn118;                   // +0x118

    cListenerBase();                                        // 0x00b232b0
    void FUN_00b23560(cInteractable* pObject);              // 0x00b23560
};

// ---------------------------------------------------------------------------------------------
// the planet-event handling: the model and the objects it wakes
// ---------------------------------------------------------------------------------------------
struct tVec3 {
    float x;                                    // +0x00
    float y;                                    // +0x04
    float z;                                    // +0x08
};

class cPlanetModel {
public:
    uint32_t mPad00[9];                         // +0x000 .. +0x023
    void*    mp024;                             // +0x024 the terrain sphere

    tVec3* DirectionToSurfacePosition(tVec3* pOut, const tVec3& vDir);  // 0x00b815a0
};

class cInteractable {
public:
    virtual void* v00();                        // +0x000
    virtual void* v04();                        // +0x004
    virtual void* v08();                        // +0x008
    virtual void* v0c();                        // +0x00c
    virtual void* v10();                        // +0x010
    virtual void* v14();                        // +0x014
    virtual void* v18();                        // +0x018
    virtual void* v1c();                        // +0x01c
    virtual void* v20();                        // +0x020
    virtual void* v24();                        // +0x024
    virtual void* v28();                        // +0x028
    virtual void* v2c();                        // +0x02c the object's position
    virtual void* v30();                        // +0x030
    virtual void* v34();                        // +0x034
    virtual void* v38();                        // +0x038
    virtual void* v3c();                        // +0x03c
    virtual void* v40();                        // +0x040
    virtual void* v44();                        // +0x044
    virtual void* v48();                        // +0x048
    virtual void* v4c();                        // +0x04c the object's id
    virtual void* v50();                        // +0x050
    virtual void* v54();                        // +0x054
    virtual void* v58();                        // +0x058
    virtual void* v5c();                        // +0x05c
    virtual void* v60();                        // +0x060
    virtual void* v64();                        // +0x064
    virtual void* v68();                        // +0x068
    virtual void* v6c();                        // +0x06c
    virtual void* v70();                        // +0x070
    virtual void* v74();                        // +0x074
    virtual void* v78();                        // +0x078
    virtual void* v7c();                        // +0x07c
    virtual void  v80();                        // +0x080 wake the object
    virtual void* v84();                        // +0x084
    virtual void* v88();                        // +0x088
    virtual void* v8c();                        // +0x08c
    virtual void* v90();                        // +0x090
    virtual void* v94();                        // +0x094
    virtual void* v98();                        // +0x098
    virtual void* v9c();                        // +0x09c
    virtual void* va0();                        // +0x0a0
    virtual void* va4();                        // +0x0a4
    virtual void* va8();                        // +0x0a8
    virtual void* vac();                        // +0x0ac
    virtual void* vb0();                        // +0x0b0
    virtual void* vb4();                        // +0x0b4
    virtual void* vb8(uint32_t nKey);           // +0x0b8
};

// the planet-event message the handler is called with
struct tPlanetEventMsg {
    uint32_t mn00;                              // +0x00
    uint32_t mn04;                              // +0x04
    float    mf08;                              // +0x08
    uint32_t mn0c;                              // +0x0c
    float    mf10;                              // +0x10
    uint32_t mn14;                              // +0x14
    float    mf18;                              // +0x18
    uint32_t mn1c;                              // +0x1c
    float    mf20;                              // +0x20
    uint32_t mn24;                              // +0x24
    uint32_t mn28;                              // +0x28
};

// ---------------------------------------------------------------------------------------------
// the strings the order-name helpers are built on
// ---------------------------------------------------------------------------------------------
// a counted string with inline storage
class cEAString {
public:
    uint8_t* mpBegin;                           // +0x00
    uint8_t* mpEnd;                             // +0x04
    uint8_t* mpEndAlloc;                        // +0x08
    uint32_t mPad0c;                            // +0x0c
    uint8_t* mpInline;                          // +0x10

    void resize(uint32_t nSize);                // 0x00b20610
    void Assign(const cEAString& pOther);       // 0x00b20c00
    void swap(cEAString& pOther);               // 0x00b22060
    void FUN_00b230b0(uint32_t nSize);          // 0x00b230b0
};

// the string the name lookups are handed to
class cNamedString {
public:
    uint8_t* mpBegin;                           // +0x00
    uint8_t* mpEnd;                             // +0x04
    uint8_t* mpEndAlloc;                        // +0x08
    uint32_t mPad0c;                            // +0x0c
    uint8_t* mpInline;                          // +0x10

    void* ctor(void* pSrc, void* pEnd);         // 0x00b209f0
};

// the registries the order names are looked up in
class cOrderRegistry {
public:
    void FUN_00b1aba0(void* pName, const void* pValue, uint32_t nId);   // 0x00b1aba0
    void FUN_00b23020(void* pName, void* pValue, uint32_t nId);         // 0x00b23020
    void FUN_00b23c60(uint32_t nId, const char* pName);                 // 0x00b23c60
};

cOrderRegistry g_orderRegistryA;                // 0x01568530
cOrderRegistry g_orderRegistryB;                // 0x01568568

// ---------------------------------------------------------------------------------------------
// @ 0x00b230b0
// ---------------------------------------------------------------------------------------------
void cEAString::FUN_00b230b0(uint32_t nSize)
{
    if (nSize != 0xffffffff && nSize > (uint32_t)(mpEnd - mpBegin))
    {
        uint8_t* pNew = (uint8_t*)EASTL_allocate(nSize, "Simulator", 0, 0,
                                                 "EASTL/allocator.h", 0xd1);
        uint32_t nOld = (uint32_t)(mpEnd - mpBegin);
        SP_memcpy(pNew, mpBegin, nOld);
        uint8_t* pNewEnd = pNew + nOld;
        *pNewEnd = 0;
        if ((int32_t)(mpEndAlloc - mpBegin) > 1 && mpBegin != 0 && mpBegin != mpInline)
            operator_delete(mpBegin);
        mpBegin = pNew;
        mpEnd = pNewEnd;
        mpEndAlloc = pNew + nSize;
        return;
    }
    if (nSize < (uint32_t)(mpEnd - mpBegin))
        resize(nSize);
    cEAString tmp;
    tmp.Assign(*this);
    swap(tmp);
    if ((int32_t)(tmp.mpEndAlloc - tmp.mpBegin) > 1 && tmp.mpBegin != 0
        && tmp.mpBegin != tmp.mpInline)
        operator_delete(tmp.mpBegin);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b231b0
// ---------------------------------------------------------------------------------------------
cMilitaryAttackCityOrder::cMilitaryAttackCityOrder()
{
    BaseCtor();
    mpVtable00 = &g_vtableMACOrderPrimary;
    mpVtable04 = &g_vtableMACOrderSecondary;
    mp094 = 0;
    mVec09c.mpBegin = 0;
    mVec09c.mpEnd = 0;
    mVec09c.mpEndAlloc = 0;
    mVec0b0.mpBegin = 0;
    mVec0b0.mpEnd = 0;
    mVec0b0.mpEndAlloc = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23260
// ---------------------------------------------------------------------------------------------
cMilitaryAttackCityOrder* cMilitaryAttackCityOrder::FUN_00b23260(uint8_t nFlags)
{
    mVec0b0.~cOrderVector();
    mVec09c.~cOrderVector();
    cRefObj* pRef = (cRefObj*)mp094;
    if (pRef != 0)
        pRef->v04();
    DtorBody();
    if ((nFlags & 1) != 0)
        operator_delete(this);
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b232b0
// ---------------------------------------------------------------------------------------------
cListenerBase::cListenerBase()
{
    cGonzagoSubsystem* pSubsystem = (cGonzagoSubsystem*)((uint8_t*)this + 4);
    mpVtable00 = &g_vtableListenerA;
    pSubsystem->BaseCtor();

    mpVtable04 = &g_vtableListenerGonzago;
    mpVtable00 = &g_vtableListenerPrimary;
    mpVtable08 = &g_vtableListenerTail;

    mf030 = 1.0f;
    mf034 = 2.0f;
    mn02c = 0;
    mn038 = 0;
    mn028 = 1;
    mp024 = (uint32_t)&g_listenerNameTable;

    mPad040[0] = 0;
    mPad040[1] = 0;
    mPad040[2] = 0;
    mPad040[3] = 0;
    mPad040[4] = 0;
    mPad040[5] = 0;
    mPad040[6] = 0;
    mPad040[7] = 0;
    mPad040[8] = 0;
    mPad040[9] = 0;
    mn070 = 0;
    mn074 = 0;

    mUnit078.mHead.InitReversed();
    mn080 = 0;
    mn084 = 0;
    mn088 = 0;
    mn094 = 0;

    mUnit09c.mWords[1] = 0;
    mFlag0a4.mnDword = 0;
    mFlag0a8.mnDword = 0;
    mFlag0a4.mnDword = 0;
    mFlag0a8.mnByte = 0;
    mn0ac = 0;
    mUnit09c.mWords[0] = (uint32_t)&mUnit09c.mHead;
    mUnit09c.mWords[1] = (uint32_t)&mUnit09c.mHead;

    mUnit0b8.mWords[1] = 0;
    mn0c0 = 0;
    mFlag0c4.mnDword = 0;
    mn0c0 = 0;
    mFlag0c4.mnByte = 0;
    mn0c8 = 0;
    mUnit0b8.mWords[0] = (uint32_t)&mUnit0b8.mHead;
    mUnit0b8.mWords[1] = (uint32_t)&mUnit0b8.mHead;

    mTree0d0.mp08 = 0;
    mTree0d0.mp0c = 0;
    mTree0d0.mn10Word = 0;
    mTree0d0.mp04 = (void*)&mTree0d0.mp04;
    mTree0d0.mp08 = (void*)&mTree0d0.mp04;
    mTree0d0.mp0c = 0;
    mTree0d0.mb10 = 0;
    mTree0d0.mn14 = 0;

    mUnit0f0.mWords[1] = 0;
    mn0f8 = 0;
    mFlag0fc.mnDword = 0;
    mUnit0f0.mWords[0] = (uint32_t)&mUnit0f0.mHead;
    mUnit0f0.mWords[1] = (uint32_t)&mUnit0f0.mHead;
    mn0f8 = 0;
    mFlag0fc.mnByte = 0;
    mn100 = 0;

    mn108 = 0;
    mUnit10c.mHead.Init();
    mn118 = 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23450
// ---------------------------------------------------------------------------------------------
void cGameNounManager::FUN_00b23450(cNoun* pObject)
{
    if (pObject == 0)
        return;
    pObject->mn0b58 |= 0x100;
    cAutoRef ref(pObject);
    mPart.mPosse058.push_back(ref);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b234c0
// ---------------------------------------------------------------------------------------------
void cGameNounManager::ClearPosseMembers()
{
    cRefVector* pPosse = &mPart.mPosse058;
    int32_t nCount = (int32_t)(pPosse->mpEnd - pPosse->mpBegin);
    int32_t i = 0;
    while (i < nCount)
    {
        cNoun* pMember = pPosse->mpBegin[i].mpObject;
        pMember->mn0b58 &= 0xfffffeff;
        ++i;
    }
    pPosse->erase(pPosse->mpBegin, pPosse->mpEnd);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23510
// ---------------------------------------------------------------------------------------------
void cGameNounManager::FUN_00b23510()
{
    cNoun* pOld = mPart.mRef054.mpObject;
    if (pOld == 0)
        return;
    RemoveNoun(pOld);
    if (mPart.mRef054.mpObject == pOld)
        mPart.mRef054 = (cNoun*)0;
    mPart.mRef054 = (cNoun*)0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23560
// ---------------------------------------------------------------------------------------------
void cListenerBase::FUN_00b23560(cInteractable* pObject)
{
    uint32_t nKey = (uint32_t)pObject->v4c();
    if (nKey == 0xffffffff)
        return;

    cRefNode* pNode;
    mTree0d0.find((void**)&pNode, &nKey);
    if (pNode != (cRefNode*)&mTree0d0.mp04)
    {
        if (ClassifyA(pObject) > ClassifyA(pNode->mp14))
            mTree0d0.insert(&nKey)->Set((cNoun*)pObject);
    }
    else
    {
        cRefNode* pNew = (cRefNode*)mTree0d0.insert(&nKey);
        pNew->mObject = (cNoun*)pObject;
    }
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23610
// ---------------------------------------------------------------------------------------------
void cGameNounManager::FUN_00b23610()
{
    cNoun* pOld = mPart.mRef070.mpObject;
    if (pOld == 0)
        return;
    RemoveNoun(pOld);
    ProcessPending();
    mPart.mRef070 = (cNoun*)0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23640
// ---------------------------------------------------------------------------------------------
// the manager part's second-base thunk: the manager itself sits four bytes before it
class cGNMThunk {
public:
    uint32_t mPad00;                            // +0x00

    void FUN_00b23640(uint32_t nA, uint32_t nB);            // 0x00b23640
};

void cGNMThunk::FUN_00b23640(uint32_t nA, uint32_t nB)
{
    cGameNounManager* pManager = (cGameNounManager*)((uint8_t*)this - 4);
    pManager->ProcessPending();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23650
// ---------------------------------------------------------------------------------------------
cNoun* cGameNounManager::FUN_00b23650(void* pDesc, void* pB, void* pC, void* pD, void* pE)
{
    void* pFound = FUN_00b21000(pDesc, pB);
    return pFound != 0 ? CreateAndInit(pFound, pC, pD, pE) : 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23690
// ---------------------------------------------------------------------------------------------
void* cGameNounManager::FUN_00b23690(uint32_t nArg)
{
    cVectorHolder* pHolder = (cVectorHolder*)GetGameDataVector(
        &g_funB21080, &g_funB22E80, &g_funB22EA0, &g_funB1E520, (void*)nArg);
    return &pHolder->mVec;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23770
// ---------------------------------------------------------------------------------------------
cCulturalConvertCityOrder* FUN_00b23770()
{
    return new ("Simulator/cCulturalConvertCityOrder", 0, 0, 0, 0) cCulturalConvertCityOrder;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b237d0
// ---------------------------------------------------------------------------------------------
void cGNMPart::FUN_00b237d0()
{
    cGameNounManager* pManager = ManagerOfPart(this);

    if (mn03c != 0)
    {
        uint32_t nHandler = mn03c;
        mn03c = 0;
        EA_Messaging_RemoveHandler(nHandler, mn040, mn044, mn048, mn04c);
    }
    mRef050 = (cNoun*)0;
    mRef054 = (cNoun*)0;
    pManager->ClearPosseMembers();
    mRef06c = (cNoun*)0;

    cNoun* pOld = mRef070.mpObject;
    if (pOld != 0)
    {
        pManager->RemoveNoun(pOld);
        pManager->ProcessPending();
        mRef070 = (cNoun*)0;
    }

    mTree0cc.clear();
    mTree0e8.clear();

    mBucket1c.FreeBucketNodes(mBucket1c.mp04, mBucket1c.mp08);
    mBucket1c.mn0c = 0;
    pManager->ValidateClassSets();

    mHead074.ClearNodes();
    mVec07c.erase(mVec07c.mpBegin, mVec07c.mpEnd);
    pManager->Flush();
    mFlush094.FUN_00b21da0(&mn0b0);
    pManager->Flush();
    mFlush094.FUN_00b21da0(&mn0b0);
    mHead108.ClearNodes();
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23940
// ---------------------------------------------------------------------------------------------
cNoun* cGameNounManager::FUN_00b23940(float* pPosition, uint32_t nSpecies, uint32_t nGeneration,
                                      uint8_t bOwner, float fHitpoint, uint8_t bDebug)
{
    if (nSpecies == 0)
        return 0;

    cNoun* pNoun = CreateNoun(0x1be418e);
    pNoun->mn0f4 = nGeneration;
    pNoun->mn15c = *(uint32_t*)&fHitpoint;
    pNoun->mn0a4 = nSpecies;
    pNoun->mf34 = pPosition[0];
    pNoun->mf38 = pPosition[1];
    pNoun->mf3c = pPosition[2];
    pNoun->mb084 = bOwner;

    if (bDebug != 0)
    {
        cNoun* pDebug = CreateDebugNoun(pPosition, pNoun);
        if (pDebug != (cNoun*)pNoun->mp160)
        {
            if (pDebug != 0)
                pDebug->v00();
            ((cAutoRef*)&pNoun->mp160)->mpObject = pDebug;
            if (pNoun->mp160 != 0)
                ((cNoun*)pNoun->mp160)->v04();
        }
    }

    pNoun->v54();

    if (bOwner != 0)
    {
        if (mPart.mRef054.mpObject != 0)
            FUN_00b23510();
        mPart.mRef054 = pNoun;
    }

    void* pMode = GetCurrentGameMode();
    if (pMode == &g_gameModeAssembling || pMode == &g_gameModeAdventuring)
        FUN_00c6ace0(pNoun, 0);

    return pNoun;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23a40
// ---------------------------------------------------------------------------------------------
cNoun* cGameNounManager::FUN_00b23a40(uint32_t nID)
{
    cVectorHolder* pHolder = (cVectorHolder*)GetGameDataVector(
        &g_funCD7D10, &g_funD3D420, &g_funACCBB0, &g_funB1E500, &g_classKey18c6d19);
    cObjectVector* pVector = &pHolder->mVec;
    uint32_t nCount = (uint32_t)(pVector->mpEnd - pVector->mpBegin);
    for (uint32_t i = 0; i < nCount; ++i)
    {
        cNoun* pNoun = (cNoun*)pVector->mpBegin[i];
        if ((uint32_t)pNoun->v4c() == nID)
            return pNoun;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23ab0
// ---------------------------------------------------------------------------------------------
uint8_t cGameNounManager::FUN_00b23ab0(uint32_t nMsgId, tPlanetEventMsg* pMsg)
{
    if (nMsgId == 0xf62def)
    {
        if (*(const uint32_t*)&pMsg->mf10 == 0x2e9c426)
            FUN_00b215a0();
        return 0;
    }
    if (nMsgId != 0x182c582)
        return 0;

    cPlanetModel* pModel = (cPlanetModel*)PlanetModel();
    if (pModel == 0 || pModel->mp024 == 0)
        return 0;

    tVec3 vPosition;
    vPosition.x = pMsg->mf08;
    vPosition.y = pMsg->mf10;
    vPosition.z = pMsg->mf18;
    if (vPosition.x * vPosition.x + vPosition.z * vPosition.z + vPosition.y * vPosition.y > 0.001f)
    {
        tVec3 vSurface;
        tVec3* pSurface = pModel->DirectionToSurfacePosition(&vSurface, vPosition);
        vPosition.x = pSurface->x;
        vPosition.y = pSurface->y;
        vPosition.z = pSurface->z;
    }

    float fRadius = pMsg->mf20;
    float fRadiusSq = fRadius * fRadius;
    uint32_t nValue = pMsg->mn28;

    cObjectVector* pVector = (cObjectVector*)this->FUN_00b23690(0x1186577);
    for (cRefObj** ppObject = pVector->mpBegin; ppObject != pVector->mpEnd; ++ppObject)
    {
        cInteractable* pObject = (cInteractable*)*ppObject;
        if (pObject == 0)
            continue;
        if (pObject->vb8(0x17f243b) != 0)
        {
            if (pObject->v2c())
                continue;
        }
        tVec3* pObjectPos = (tVec3*)pObject->v2c();
        float dx = pObjectPos->x - vPosition.x;
        float dy = pObjectPos->y - vPosition.y;
        float dz = pObjectPos->z - vPosition.z;
        if (fRadiusSq > dz * dz + dy * dy + dx * dx)
            pObject->v80();
    }

    this->mPart.mn090 = nValue;
    return 0;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00b23c60
// ---------------------------------------------------------------------------------------------
void cOrderRegistry::FUN_00b23c60(uint32_t nId, const char* pName)
{
    cNamedString nameA;
    nameA.mpBegin = 0;
    nameA.mpEnd = 0;
    nameA.mpEndAlloc = 0;
    nameA.mpInline = (uint8_t*)&nameA.mPad0c;

    uint32_t nLen = 0;
    while (pName[nLen] != 0)
        ++nLen;
    uint8_t* pEndAlloc;
    if (nLen + 1 > 1)
    {
        nameA.mpBegin = (uint8_t*)EASTL_allocate(nLen + 1, "Simulator", 0, 0,
                                                 "EASTL/allocator.h", 0xd1);
        pEndAlloc = nameA.mpBegin + nLen + 1;
    }
    else
    {
        nameA.mpBegin = g_emptyString;
        pEndAlloc = g_emptyString + 1;
    }
    SP_memcpy(nameA.mpBegin, pName, nLen);
    nameA.mpEnd = nameA.mpBegin + nLen;
    *nameA.mpEnd = 0;
    nameA.mpEndAlloc = pEndAlloc;

    cNamedString nameB;
    nameB.mpBegin = 0;
    nameB.mpEnd = 0;
    nameB.mpEndAlloc = 0;
    nameB.mpInline = (uint8_t*)&nameB.mPad0c;
    uint32_t nCopyLen = (uint32_t)(nameA.mpEnd - nameA.mpBegin);
    if (nCopyLen + 1 > 1)
    {
        nameB.mpBegin = (uint8_t*)EASTL_allocate(nCopyLen + 1, "Simulator", 0, 0,
                                                 "EASTL/allocator.h", 0xd1);
        nameB.mpEndAlloc = nameB.mpBegin + nCopyLen + 1;
    }
    else
    {
        nameB.mpBegin = g_emptyString;
        nameB.mpEndAlloc = g_emptyString + 1;
    }
    SP_memcpy(nameB.mpBegin, nameA.mpBegin, nCopyLen);
    nameB.mpEnd = nameB.mpBegin + nCopyLen;
    *nameB.mpEnd = 0;

    g_orderRegistryA.FUN_00b1aba0(&nameB, nameB.mpEnd, nId);
    if ((uint32_t)(nameB.mpEndAlloc - nameB.mpBegin) > 1 && nameB.mpBegin != g_emptyString)
        operator_delete(nameB.mpBegin);
    if ((uint32_t)(nameA.mpEndAlloc - nameA.mpBegin) > 1 && nameA.mpBegin != g_emptyString)
        operator_delete(nameA.mpBegin);

    cNamedString nameC;
    nameC.mpBegin = 0;
    nameC.mpEnd = 0;
    nameC.mpEndAlloc = 0;
    nameC.mpInline = (uint8_t*)&nameC.mPad0c;
    if (nLen + 1 > 1)
    {
        nameC.mpBegin = (uint8_t*)EASTL_allocate(nLen + 1, "Simulator", 0, 0,
                                                 "EASTL/allocator.h", 0xd1);
        nameC.mpEndAlloc = nameC.mpBegin + nLen + 1;
    }
    else
    {
        nameC.mpBegin = g_emptyString;
        nameC.mpEndAlloc = g_emptyString + 1;
    }
    SP_memcpy(nameC.mpBegin, pName, nLen);
    nameC.mpEnd = nameC.mpBegin + nLen;
    *nameC.mpEnd = 0;

    void* pValue = nameC.ctor(&nameC, &nameA);
    g_orderRegistryB.FUN_00b23020(&nameC, pValue, nId);
    if ((uint32_t)(nameC.mpEndAlloc - nameC.mpBegin) > 1 && nameC.mpBegin != g_emptyString)
        operator_delete(nameC.mpBegin);
}
