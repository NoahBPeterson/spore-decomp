// Slice s00b71a60 — 0x00b71a60 .. 0x00b72890.
//
// Sporepedia feedback-event subsystem co-located with SP::cGameNounManager, plus a tail group of
// unrelated helpers in the same address window (Euler-rotation wrapper, float comparators,
// hier-grid entry toggle, cGameModeManager property reader, flag setters, segment closest-point).
//
// Module flags: /O2 /MD /Gy /TP (no /EHsc — no EH frames in this TU).
//
// Types absent from the PDB (the feedback map internals, cObjectPool, ...) are reconstructed from
// the code shape; every field touched is named at its offset.

typedef unsigned int   size_t;
typedef unsigned int   uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char  uint8_t;
typedef unsigned __int64 uint64_t;

void* operator new(size_t size, const char* pName, int flags, unsigned dbg, const char* file, int line);
void  operator delete(void* p, const char* pName, int flags, unsigned dbg, const char* file, int line);
inline void* operator new(size_t, void* p) throw() { return p; }
inline void  operator delete(void*, void*) throw() {}
#define SP_NEW(name) new(name, 0, 0, 0, 0)

int   __cdecl SP_ReadInt32(void* pStream, void* pDest, int nCount, int nStride);   // 0x0093a780
void* __cdecl memset(void* pDst, int c, size_t n);                                // 0x011e073e
void* Fn_00c696a0(void* pObj, float fSeconds, double dElapsed);                    // 0x00c696a0
void  __cdecl Fn_00c69760(void* pParam, uint32_t arg);                             // 0x00c69760

#include <math.h>

struct IStream;
struct FeedbackTree;
struct FeedbackNode;
struct cGameDataVector;
struct cFeedbackEvent;

// =======================================================================================
// EASTL red-black tree primitives (shared layout; see match/synth/eastl_rbtree_*.cpp).
//   Tree : [0x00] mCompare  [0x04] mAnchor(0x10)  [0x14] mnSize
//   nb   : [0x00] mpNodeRight [0x04] mpNodeLeft [0x08] mpNodeParent [0x0c] mColor
namespace eastl {

struct true_type {};

struct nb {
    nb*      mpNodeRight;    // +0x00
    nb*      mpNodeLeft;     // +0x04
    nb*      mpNodeParent;   // +0x08
    uint32_t mColor;         // +0x0c
};

struct node_u32 : nb {
    uint32_t mValue;         // +0x10
};

}  // namespace eastl

// Feedback-event map node: rb node + uint32 key + AutoRefCount (one pointer) at +0x14.
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

// =======================================================================================
// Ref-counted objects.  vtable slot offsets are given per use in the comments.
struct cDevice {
    virtual void  Slot0(); virtual void  Slot1(); virtual void  Slot2(); virtual void  Slot3();
    virtual void  Slot4(); virtual void  Slot5();
    virtual void* GetStream();       // 6 (0x18)
};

struct IStream {
    virtual void  Slot0(); virtual void  Slot1(); virtual void  Slot2();
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
    virtual void  Slot17(); virtual void  Slot18(); virtual void  Slot19();
    virtual void  Slot20(); virtual void  Slot21();
    virtual void* Slot22(uint32_t);  // 22 (0x58)
    virtual void  Slot23(); virtual void  Slot24(); virtual void  Slot25();
    virtual void  Slot26(); virtual void  Slot27(); virtual void  Slot28();
    virtual void  Slot29(); virtual void  Slot30(); virtual void  Slot31();
    virtual void  Slot32(); virtual void  Slot33(); virtual void  Slot34();
    virtual void  Slot35(); virtual void  Slot36(); virtual void  Slot37();
    virtual void  Slot38(); virtual void  Slot39(); virtual void  Slot40();
    virtual void  Slot41(); virtual void  Slot42(); virtual void  Slot43();
    virtual void  Slot44(); virtual void  Slot45();
    virtual void* Slot46(uint32_t);  // 46 (0xb8)
    virtual void  AddRefSlot();      // 47 (0xbc)
    virtual void  ReleaseSlot();     // 48 (0xc0)
    virtual void  Slot49();          // 49 (0xc4)
    virtual void  Slot50();          // 50 (0xc8)
    virtual void  Slot51();          // 51 (0xcc)
    virtual void  Slot52();          // 52 (0xd0)
    virtual void  Slot53();          // 53 (0xd4)
};

// ---------------------------------------------------------------------------------------
// The owner object: a cGonzagoSubsystem-derived class whose feedback map sits at +0x1c.
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

// cVarListSerializer is huge; only the ctor and the IStream Serialize overload matter here.
struct cVarListSerializer {
    char mData[0xa14];
    cVarListSerializer(void const*, void*, unsigned);
    bool Serialize(IStream&);
};

extern void* DAT_0156b308;           // cDataSerializerGeneric* list

// cGameNounManager statics reached through SP::NounManager().
struct cNoun { char mPad04[0x04 - 0x00]; };
struct cGameNounManager {
    void RemoveNoun(void* pNoun);    // 0x00b225d0
    void* CreateNoun(uint32_t id);   // 0x00b20c60
    cGameDataVector* GetGameDataVector(void*, void*, void*, void*, uint32_t);  // 0x00b21340
};
cGameNounManager* __cdecl SP_NounManager();                              // 0x00b3d300

// cGameModeManager: only the mode field at +0x88 is read here.
struct cGameModeManager {
    char     mPad00[0x88];
    uint32_t mField88;               // +0x88
    uint32_t GetScriptId();          // 0x00b72320
};

// =======================================================================================
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

    cVarListSerializer serializer(this, &DAT_0156b308, 0x1a80d26);
    serializer.Serialize(*pStream);
}

// =======================================================================================
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

// =======================================================================================
// @ 0x00b71b90
// Fills the feedback map from the stream: reads a count, then for each entry reads an object
// under interface id 0x1186577, releases it, reads the actual feedback event under 0x6ef0ec9
// and inserts it into the map.
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

// =======================================================================================
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

// cOwner::~cOwner():
// This is the plain destructor body; the slice VA for the scalar deleting destructor (??_G) is
// the compiler-generated code that inlines it, which chk.py binds by the similar-size fallback
// (there is no source definition to name there).
cOwner::~cOwner()
{
    FeedbackTree& rTree = mFeedback;
    rTree.Purge((FeedbackNode*)rTree.mAnchor.mpNodeParent);
}

// =======================================================================================
// @ 0x00b71e00 is the compiler-generated scalar deleting destructor (??_G)

// =======================================================================================
// @ 0x00b71e40
// rbtree::insert(value): lower_bound, then insert iff strictly new; returns the value slot.
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

// =======================================================================================
// cObjectPool: a fixed-stride pool of handles.  Layout (from 0x00b72080..0x00b72260):
//   +0x00 data   +0x04 freeHead   +0x08 nextHandle   +0x0c used   +0x10 highWater
//   +0x14 stride +0x18 capacity
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

extern int gPoolCounter;             // 0x0156b380
extern const char kPoolName[];       // 0x01464f9c "Simulator/cObjectPool"

// =======================================================================================
// @ 0x00b71ee0
// Advances the feedback timers for every game object of a given type over a time step.
struct cGameDataVector {
    char   pad0[4];
    void** mpBegin;                  // +0x04
    void** mpEnd;                    // +0x08
};

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

// =======================================================================================
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

// =======================================================================================
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

// =======================================================================================
// @ 0x00b720e0
void cObjectPool::Destroy()
{
    if (mpData && mpData != (char*)0xbaad) {
        operator delete(mpData);
        mpData = (char*)0xbaad;
    }
}

// =======================================================================================
// @ 0x00b72110
void cObjectPool::Reset()
{
    mUsed = 0;
    mHighWater = 0;
    mFreeHead = -1;
}

// =======================================================================================
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

// =======================================================================================
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

// =======================================================================================
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

// =======================================================================================
// @ 0x00b72210
void* cObjectPool::At(uint32_t index)
{
    return &mpData[mStride * (index & 0xffff)];
}

// =======================================================================================
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

// =======================================================================================
// @ 0x00b72260
void cObjectPool::Free(uint32_t handle)
{
    uint32_t* pSlot = (uint32_t*)&mpData[mStride * (handle & 0xffff)];
    *pSlot = (uint32_t)mFreeHead;
    --mUsed;
    mFreeHead = (int)(handle & 0xffff);
}

// =======================================================================================
// @ 0x00b72290
// True when the squared length of pA is less than that of pB.
bool __cdecl Fn_00b72290(const float* pA, const float* pB)
{
    return (pA[0] * pA[0] + pA[1] * pA[1] + pA[2] * pA[2]) <
           (pB[0] * pB[0] + pB[1] * pB[1] + pB[2] * pB[2]);
}

// =======================================================================================
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

// =======================================================================================
// @ 0x00b72370
// Registers a listener with the EA messaging server for 8 handler slots.
struct cMessagingServer {
    virtual void  Slot0(); virtual void  Slot1(); virtual void  Slot2(); virtual void  Slot3();
    virtual void  Slot4(); virtual void  Slot5(); virtual void  Slot6(); virtual void  Slot7();
    virtual void  Slot8(); virtual void  Slot9(/* hListener, id */ unsigned hListener, unsigned id); // 9 (0x24)
};
cMessagingServer* __cdecl EA_Messaging_GetServer();      // 0x00883860
extern unsigned gMessageIds[8];                          // 0x01465004

struct cMessageListener {
    char mPad00[0x20];
    cMessagingServer* mpServer;  // +0x20
    void*             mpOwner;   // +0x24
    unsigned*         mpIds;     // +0x28
    int               mCount;    // +0x2c
    int               mState;    // +0x30

    void Register(void);         // 0x00b72370
};

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

// =======================================================================================
// @ 0x00b72410
// A no-op register-pair pass-through: returns arg0 in EDX and arg1 in EAX.
uint64_t __stdcall Fn_00b72410(uint32_t a, uint32_t b)
{
    return ((uint64_t)a << 32) | b;
}

// =======================================================================================
// @ 0x00b72430
// Linear search over 12-byte records using a user predicate; returns the matching address
// or `last`.
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

// =======================================================================================
// @ 0x00b72520
// Applies a Y-pre-rotation, an X-pre-rotation and a Y-rotation to a transform.
struct cXform {
    virtual void Slot0();            // +0x00 vtable
    void PreRotateY(float a);        // 0x004099b0
    void PreRotateX(float a);        // 0x005a2d90
    void RotateY(float a);           // 0x006b9050
    void PreRotateXYZ(float a, float b, float c);   // 0x00b72520
};

void cXform::PreRotateXYZ(float a, float b, float c)
{
    this->PreRotateY(a);
    this->PreRotateX(b);
    this->RotateY(c);
}

// =======================================================================================
// @ 0x00b72560
bool __cdecl Fn_00b72560(const float* pA, const float* pB)
{
    return *pB > *pA;
}

// =======================================================================================
// @ 0x00b72580
bool __cdecl Fn_00b72580(const float* pA, const float* pB)
{
    return pB[1] > pA[1];
}

// =======================================================================================
// @ 0x00b725a0
bool __cdecl Fn_00b725a0(const float* pA, const float* pB)
{
    return fabsf(pA[0] - pB[0]) < 0.001f && fabsf(pA[1] - pB[1]) < 0.001f;
}

// =======================================================================================
// @ 0x00b725e0
// Adds or removes a hier-grid entry depending on the flag.
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

// =======================================================================================
// @ 0x00b72640
// Reads nine tuning floats from the game-mode data object into the mode-tuning block.
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

extern float gTune_0156b390, gTune_0156b394, gTune_0156b398;
extern float gVec_016880d4, gVec_016880d8, gVec_016880dc;
extern float gTune_0156b39c, gTune_0156b3a0, gTune_0156b3a4, gTune_0156b3a8;

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

// =======================================================================================
// @ 0x00b72870
// Sets the "grid entry active" flag bit at +0x20.
struct cFlagObject {
    char     mPad00[0x20];
    uint32_t mFlags;                 // +0x20

    void SetFlag2();                 // 0x00b72870
    void ClearFlag2();               // 0x00b72880
};

void cFlagObject::SetFlag2()
{
    mFlags |= 2;
}

// =======================================================================================
// @ 0x00b72880
void cFlagObject::ClearFlag2()
{
    mFlags &= ~2u;
}


// =======================================================================================
// @ 0x00b72890
// Closest points between two segments with a thickness band (Havok-style).  param4/param5 are
// the segment end points, param1/param2 the direction vectors, param9 the output amount.
bool __cdecl ClosestPointsOnSegments(const float* pA0, const float* pA1,
                                     const float* pB0, const float* pB1,
                                     float fa, float fb, float* pOutA, float* pOutB); // 0x00698fa0

extern float gEps13ec4b8;    // 0x013ec4b8  (1e-8f)
extern float gThick1464fdc;  // 0x01464fdc
extern float gOne1485720;    // 0x01485720  (HK_REAL_ONE)

bool __cdecl Fn_00b72890(const float* pA0, float fA1, const float* pDirA, const float* pB0,
                         const float* pDirB, float fThickness, float fMaxDist, char bClamp,
                         float* pOut)
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


// ---------------------------------------------------------------------------------------
// Helper that forces MSVC to emit the scalar deleting destructor (??_G) for cOwner, so the
// compiler-generated code for slice VA 0x00b71e00 exists in this object. Not a slice VA.
void Fn_forceOwnerDeletingDtor(cOwner* pOwner)
{
    delete pOwner;
}
