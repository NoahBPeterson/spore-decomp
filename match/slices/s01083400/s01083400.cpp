// Slice s01083400: Havok world bookkeeping from SPORE's hkWorld translation unit -- phantom removal
// (and its deferred-operation path), the two hkArray appenders used by the world listeners, the
// statistics collector, the world destructor and the region activation query.  Field offsets are the
// retail ones.
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;

struct hkWorld;

// ---- pending operations ---------------------------------------------------------------------
// The operation queue at +0x84 receives 8-byte records: an opcode byte, three pad bytes and a
// payload pointer (a phantom, or a heap copy of an Aabb when the world is mid-update).  The queue
// itself owns a 20-byte-stride operation table.
struct hkPendingOp {
    uchar mOpcode;                                            // +0x00
    uchar mPad01[3];                                          // +0x01
    void* mpPayload;                                          // +0x04
};
struct hkOpQueue {
    void* mpOps;                                              // +0x00
    int   mOpCount;                                           // +0x04
    uint  mOpCapacityAndFlags;                                // +0x08
    char  mPad0c[0x20 - 0x0c];                                // +0x0c
    void* mpChunk;                                            // +0x20
    void push(hkPendingOp* pOp);                              // 0x0109afe0
};

// ---- reference counted base ----------------------------------------------------------------
struct hkReferencedObject {
    virtual void vfDestroy(int bDeallocate);                  // +0x00  (delete this)
    ushort mMemSizeAndFlags;                                  // +0x04
    short  mReferenceCount;                                   // +0x06
    void removeReference()
    {
        if (mMemSizeAndFlags != 0 && --mReferenceCount == 0) {
            vfDestroy(1);
        }
    }
};

// ---- objects --------------------------------------------------------------------------------
struct hkPhantom {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void vf11();                                      // +0x2c
    ushort mFlags;                                            // +0x04
    char  mPad06[2];                                          // +0x06
    int   m08;                                                // +0x08
    void  firePhantomRemoved();                               // 0x0108e300
    void  removeReference();                                  // 0x0109ae60
};

// A simulation island keeps its entities in an hkArray at +0x3c.
struct hkSimulationIsland : hkReferencedObject {
    char  mPad08[0x3c - 0x08];                                // +0x08
    void* mpEntities;                                         // +0x3c
    int   mEntityCount;                                       // +0x40
};

// Collision input owns one 8-byte chunk handed back with alignment 0x1c.
struct hkCollisionInput {
    char  mPad00[0x20];                                       // +0x00
    void* mpOwnedChunk;                                       // +0x20
};

struct hkEntity {
    char  mPad00[0x10];                                       // +0x00
    int   mActivateOffset;                                    // +0x10  offset of the activatable part
    char  mPad14[0x18 - 0x14];                                // +0x14
    char  mState;                                             // +0x18  1 == can be activated
    char  mPad1c[0x3c - 0x1c];                                // +0x1c
    void* mpEntities;                                         // +0x3c  (hkArray data of the owning island)
    int   mEntityCount;                                       // +0x40
    void  activate();                                         // 0x0108ae0
    void  removeReference();                                  // 0x0109ae60
};

struct hkAabb {
    float mMinX, mMinY, mMinZ, mPad0c;                        // +0x00
    float mMaxX, mMaxY, mMaxZ, mPad1c;                        // +0x10
};

void hkArrayUtil_reserveMore(void* pArray, int elementSize);  // 0x0107f530

// The hkArray<T> layout: data, size and the capacity with the top two bits as flags.
template <class T>
struct hkArray {
    T*    mpData;                                             // +0x00
    int   mSize;                                              // +0x04
    uint  mCapacityAndFlags;                                  // +0x08
    void pushBack(T value)
    {
        if (mSize == (int)(mCapacityAndFlags & 0x3fffffff)) {
            hkArrayUtil_reserveMore(this, sizeof(T));
        }
        mpData[mSize] = value;
        ++mSize;
    }
    int indexOf(T value) const
    {
        for (int i = 0; i < mSize; ++i) {
            if (mpData[i] == value)
                return i;
        }
        return -1;
    }
    bool isDeallocatable() const
    {
        return !(mCapacityAndFlags & 0x80000000);
    }
    static bool isDeallocatable(uint capacityAndFlags)
    {
        return !(capacityAndFlags & 0x80000000);
    }
};

struct hkMemory {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void* allocate(int size, int align);              // +0x10
    virtual void  deallocate(void* p, int size, int align);   // +0x14
    virtual void  vf5();
    virtual void  deallocateBlock(void* p, int size, int align);   // +0x1c
};
extern hkMemory* g_hkMemory;                                  // 0x016e4178

void hkString_memCpy(void* dst, const void* src, int len);    // 0x0107f440

struct hkBroadPhaseQuery {
    virtual void vf0();
    virtual void vf1();
    virtual void vf2();
    virtual void vf3();
    virtual void vf4();
    virtual void vf5();
    virtual void vf6();
    virtual void vf7();
    virtual void vf8();
    virtual void vf9();
    virtual void vf10();
    virtual void query(const hkAabb* pAabb, void* pArray);    // +0x2c
};

struct hkThreadMemory {
    char  mPad00[0x34];                                       // +0x00
    int   mMaxChunks;                                         // +0x34
    char  mPad38[0x4c - 0x38];                                // +0x38
    void* mpFreeList;                                         // +0x4c
    char  mPad50[0x90 - 0x50];                                // +0x50
    int   mNumChunks;                                         // +0x90
    void deallocateChunk(void* p, int bytes, int align);      // 0x0107db10
};
extern uint  g_hkThreadMemoryTls;                             // 0x016e4174
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(uint dwTlsIndex);   // kernel32

// ---- broadphase hit records ----------------------------------------------------------------
// The broadphase hands back {owner, record} pairs.  The record stores the byte offset of the entity
// it belongs to; the entity itself carries the offset of its activatable sub-object.
struct hkBroadPhaseEntry {
    void* mpOwner;                                            // +0x00
    uchar* mpRecord;                                          // +0x04
};
struct hkBpRecord {
    char  mPad00[0x05];                                       // +0x00
    signed char mEntityOffset;                                // +0x05
};

// ---- statistics ----------------------------------------------------------------------------
struct hkStatisticsCollector {
    virtual void vf0();
    virtual void beginObject(const char* pType, int indent, const void* pObject);        // +0x04
    virtual void addArray(const char* pName, int elemSize, const void* pData,
                          int usedBytes, int reservedBytes);                             // +0x08
    virtual void addValue(const char* pName, int size, const void* pValue);              // +0x0c
    virtual void beginSection(const char* pName);                                        // +0x10
    virtual void endSection();                                                           // +0x14
    virtual void endObject();                                                            // +0x18
};

struct hkWorld : hkReferencedObject {
    hkReferencedObject* mpSimulation;                         // +0x08  "Simulation"
    char  mPad0c[0x30 - 0x0c];                                // +0x0c
    hkSimulationIsland* mpFixedIsland;                        // +0x30  "Fixed"
    hkEntity* mpFixedRigidBody;                               // +0x34
    hkArray<hkSimulationIsland*> mActive;                     // +0x38  "Active"
    hkArray<hkSimulationIsland*> mInactive;                   // +0x44  "Inactive"
    hkArray<void*> mDirtyIslands;                             // +0x50  "DirtyIslPtr"
    hkReferencedObject* mpMaintenanceMgr;                     // +0x5c  "MaintnceMgr"
    hkReferencedObject* mpBroadPhaseDispatchBase;             // +0x60
    hkBroadPhaseQuery* mpBroadPhase;                          // +0x64  "Broadphase"
    void* mpBpDispatch68;                                     // +0x68  0x104 bytes
    void* mpBpDispatch6c;                                     // +0x6c
    void* mpBpDispatch70;                                     // +0x70
    void* mpBpDispatch74;                                     // +0x74
    hkCollisionInput* mpCollisionInput;                       // +0x78  "CollInput", 0x2c bytes
    hkReferencedObject* mpCollisionFilter;                    // +0x7c  "Filter"
    hkReferencedObject* mpDispatcher;                         // +0x80  "Dispatcher"
    hkOpQueue* mpOpQueue;                                     // +0x84  "OpQueue", 0x40 bytes
    int   m88;                                                // +0x88
    int   m8c;                                                // +0x8c  world-lock counter
    int   m90;                                                // +0x90
    bool  m94;                                                // +0x94
    char  mPad95[0xac - 0x95];                                // +0x95
    void* mpCriticalSectionA;                                 // +0xac
    void* mpCriticalSectionB;                                 // +0xb0
    bool  mB4;                                                // +0xb4
    char  mPadB5[0xcc - 0xb5];                                // +0xb5
    hkArray<hkPhantom*> mPhantoms;                            // +0xcc  "PhantomPtrs"
    char  mPadD8[0xe4 - 0xd8];                                // +0xd8
    hkArray<void*> mEntityListeners;                          // +0xe4  "EntLisPtr"
    hkArray<void*> mPhantomListeners;                         // +0xf0  "PhantLisPtr"
    hkArray<void*> mConstraintListeners;                      // +0xfc  "ConstrLisPtr"
    hkArray<void*> mWorldDeletionListeners;                   // +0x108 "WldDelLisPtr"
    hkArray<void*> mIslandActivationListeners;                // +0x114 "IslActLisPtr"
    hkArray<void*> mPostSimulationListeners;                  // +0x120 "PstSimLisPtr"
    hkArray<void*> mPostIntegrateListeners;                   // +0x12c "PstIntLisPtr"
    hkArray<void*> mPostCollideListeners;                     // +0x138 "PstColLisPtr"
    hkArray<void*> mListeners144;                             // +0x144
    hkArray<void*> mListeners150;                             // +0x150
    hkArray<void*> mCollisionListeners;                       // +0x15c "CollLisPtr"
    hkReferencedObject* mp168;                                // +0x168

    void removePhantom(hkPhantom* pPhantom);                  // 0x01083400
    void addCollisionListener(void* p);                       // 0x010834f0
    void addWorldDeletionListener(void* p);                   // 0x01083530
    virtual void calcStatistics(hkStatisticsCollector* pCollector) const;   // 0x01083570
    virtual ~hkWorld();                                       // 0x010839e0
    void activateRegion(const hkAabb& aabb);                  // 0x01083ff0
    void executePendingOperations();                          // 0x01082bf0
    void removeEntity(hkEntity* pEntity);                     // 0x01083110
};

void hkWorldCallbackUtil_firePhantomRemoved(hkWorld* pWorld, hkPhantom* pPhantom);   // 0x0109ee00
void hkWorldOperationUtil_removePhantomBP(hkWorld* pWorld, hkPhantom* pPhantom);     // 0x010a0f20
void hkWorldOperationUtil_removeIslandFromDirtyList(hkWorld* pWorld,
                                                    hkSimulationIsland* pIsland);    // 0x0109fb40
void hkWorldFUN_0109f280(hkWorld* pWorld);                                           // 0x0109f280
void hkWorldFUN_0109b420();                                                          // 0x0109b420
void hkWorldFUN_010cc3f0();                                                          // 0x010cc3f0
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void* pCriticalSection);   // kernel32

// ===========================================================================================
// @ 0x01083400
void hkWorld::removePhantom(hkPhantom* pPhantom)
{
    if (m8c + m90 != 0) {
        hkPendingOp op;
        op.mOpcode = 0xe;
        op.mpPayload = pPhantom;
        mpOpQueue->push(&op);
        return;
    }
    ++m8c;
    hkWorldCallbackUtil_firePhantomRemoved(this, pPhantom);
    pPhantom->firePhantomRemoved();
    hkWorldOperationUtil_removePhantomBP(this, pPhantom);
    int nIndex = mPhantoms.indexOf(pPhantom);
    int nLast = mPhantoms.mSize - 1;
    mPhantoms.mSize = nLast;
    mPhantoms.mpData[nIndex] = mPhantoms.mpData[nLast];
    pPhantom->m08 = 0;
    if (pPhantom->mFlags == 0)
        pPhantom->vf11();
    pPhantom->removeReference();
    --m8c;
    if (m8c == 0) {
        if (m88 != 0 && !m94)
            executePendingOperations();
    }
}

// ===========================================================================================
// @ 0x010834f0
void hkWorld::addCollisionListener(void* p)
{
    mCollisionListeners.pushBack(p);
}

// ===========================================================================================
// @ 0x01083530
void hkWorld::addWorldDeletionListener(void* p)
{
    mWorldDeletionListeners.pushBack(p);
}

// ===========================================================================================
// @ 0x01083570
void hkWorld::calcStatistics(hkStatisticsCollector* pCollector) const
{
    pCollector->beginObject("hkWorld", 2, this);
    for (int i = mActive.mSize - 1; i >= 0; --i)
        pCollector->addValue("Active", 8, mActive.mpData[i]);
    for (int i = mInactive.mSize - 1; i >= 0; --i)
        pCollector->addValue("Inactive", 8, mInactive.mpData[i]);
    pCollector->addValue("Fixed", 8, mpFixedIsland);
    if (!(mPhantoms.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PhantomPtrs", 4, mPhantoms.mpData, mPhantoms.mSize << 2,
                             (int)(mPhantoms.mCapacityAndFlags & 0x3fffffff) << 2);
    for (int i = 0; i < mPhantoms.mSize; ++i)
        pCollector->addValue("Phantoms", 2, mPhantoms.mpData[i]);
    pCollector->beginSection("Internal");
    pCollector->addValue("Simulation", 4, mpSimulation);
    if (!(mDirtyIslands.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("DirtyIslPtr", 8, mDirtyIslands.mpData, mDirtyIslands.mSize << 2,
                             (int)(mDirtyIslands.mCapacityAndFlags & 0x3fffffff) << 2);
    pCollector->addValue("MaintnceMgr", 4, mpMaintenanceMgr);
    pCollector->addArray("OpQueue", 4, mpOpQueue, 0x40, 0);
    pCollector->beginSection("OpQueue");
    if ((mpOpQueue->mOpCapacityAndFlags & 0x80000000) == 0)
        pCollector->addArray("Operations", 8, mpOpQueue->mpOps, mpOpQueue->mOpCount * 0x14,
                             (int)(mpOpQueue->mOpCapacityAndFlags & 0x3fffffff) * 0x14);
    pCollector->endSection();
    pCollector->beginSection("Collide");
    pCollector->addValue("Broadphase", 4, mpBroadPhase);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch68, 0x104, 0);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch6c, 0xc, 0);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch70, 8, 0);
    pCollector->addArray("BpDispatch", 4, mpBpDispatch74, 8, 0);
    pCollector->addArray("CollInput", 4, mpCollisionInput, 0x2c, 0);
    pCollector->addValue("Filter", 1, mpCollisionFilter);
    pCollector->addValue("Dispatcher", 4, mpDispatcher);
    pCollector->endSection();
    pCollector->endSection();
    pCollector->beginSection("Listeners");
    if (!(mEntityListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("EntLisPtr", 4, mEntityListeners.mpData, mEntityListeners.mSize << 2,
                             (int)(mEntityListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPhantomListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PhantLisPtr", 4, mPhantomListeners.mpData, mPhantomListeners.mSize << 2,
                             (int)(mPhantomListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mConstraintListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("ConstrLisPtr", 4, mConstraintListeners.mpData,
                             mConstraintListeners.mSize << 2,
                             (int)(mConstraintListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mWorldDeletionListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("WldDelLisPtr", 4, mWorldDeletionListeners.mpData,
                             mWorldDeletionListeners.mSize << 2,
                             (int)(mWorldDeletionListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mIslandActivationListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("IslActLisPtr", 4, mIslandActivationListeners.mpData,
                             mIslandActivationListeners.mSize << 2,
                             (int)(mIslandActivationListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPostSimulationListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstSimLisPtr", 4, mPostSimulationListeners.mpData,
                             mPostSimulationListeners.mSize << 2,
                             (int)(mPostSimulationListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPostIntegrateListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstIntLisPtr", 4, mPostIntegrateListeners.mpData,
                             mPostIntegrateListeners.mSize << 2,
                             (int)(mPostIntegrateListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mPostCollideListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstColLisPtr", 4, mPostCollideListeners.mpData,
                             mPostCollideListeners.mSize << 2,
                             (int)(mPostCollideListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mListeners144.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("PstIntLisPtr", 4, mListeners144.mpData, mListeners144.mSize << 2,
                             (int)(mListeners144.mCapacityAndFlags & 0x3fffffff) << 2);
    if (!(mCollisionListeners.mCapacityAndFlags & 0x80000000))
        pCollector->addArray("CollLisPtr", 4, mCollisionListeners.mpData,
                             mCollisionListeners.mSize << 2,
                             (int)(mCollisionListeners.mCapacityAndFlags & 0x3fffffff) << 2);
    pCollector->endSection();
    pCollector->endObject();
}

// Releases one listener/pointer array the way ~hkArray does: only when it owns its storage.
static __forceinline void releaseArray(void* pData, int sizeInBytes, uint capacityAndFlags)
{
    if ((capacityAndFlags & 0x80000000) == 0) {
        hkThreadMemory* pThreadMemory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        pThreadMemory->deallocateChunk(pData, sizeInBytes, 0x14);
    }
}

// Gives the operation queue back to the thread memory free list when possible.
static __forceinline void releaseOpQueue(hkOpQueue* pQueue)
{
    if (pQueue == 0)
        return;
    hkWorldFUN_0109b420();
    hkThreadMemory* pThreadMemory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
    if (pThreadMemory->mNumChunks < pThreadMemory->mMaxChunks) {
        ++pThreadMemory->mNumChunks;
        pQueue->mpOps = pThreadMemory->mpFreeList;            // freed block links as the next entry
        pThreadMemory->mpFreeList = pQueue;
    } else {
        g_hkMemory->deallocateBlock(pQueue, 5, 0x2c);
    }
}

// ===========================================================================================
// @ 0x010839e0
hkWorld::~hkWorld()
{
    mpMaintenanceMgr->removeReference();
    if (mpCriticalSectionA != 0) {
        DeleteCriticalSection(mpCriticalSectionA);
        g_hkMemory->deallocate(mpCriticalSectionA, 0x20, 0x12);
        mpCriticalSectionA = 0;
    }
    mpMaintenanceMgr = 0;
    if (mpCriticalSectionB != 0) {
        DeleteCriticalSection(mpCriticalSectionB);
        g_hkMemory->deallocate(mpCriticalSectionB, 0x20, 0x12);
        mpCriticalSectionB = 0;
    }
    if (mpBroadPhaseDispatchBase != 0) {
        mpBroadPhaseDispatchBase->removeReference();
        mpBroadPhaseDispatchBase = 0;
    }
    while (mPhantoms.mSize > 0)
        removePhantom(mPhantoms.mpData[0]);
    while (mActive.mSize > 0 && mActive.mpData[0]->mEntityCount != 0)
        removeEntity((hkEntity*)mActive.mpData[0]->mpEntities);
    while (mInactive.mSize > 0)
        removeEntity((hkEntity*)mInactive.mpData[0]->mpEntities);
    if (!mB4) {
        hkSimulationIsland* pLastIsland = mActive.mpData[mActive.mSize - 1];
        hkWorldOperationUtil_removeIslandFromDirtyList(this, pLastIsland);
        if (pLastIsland != 0)
            pLastIsland->vfDestroy(1);
        --mActive.mSize;
    }
    removeEntity(mpFixedRigidBody);
    mpFixedRigidBody = 0;
    while (mpFixedIsland->mEntityCount > 0)
        removeEntity((hkEntity*)mpFixedIsland->mpEntities);
    hkWorldOperationUtil_removeIslandFromDirtyList(this, mpFixedIsland);
    if (mpFixedIsland != 0)
        mpFixedIsland->vfDestroy(1);
    mpFixedIsland = 0;
    hkWorldFUN_0109f280(this);
    ((hkReferencedObject*)mpBroadPhase)->removeReference();
    mpBroadPhase = 0;
    mpDispatcher->removeReference();
    mpDispatcher = 0;
    if (mpBpDispatch68 != 0) {
        hkWorldFUN_010cc3f0();
        g_hkMemory->deallocate(mpBpDispatch68, 0x104, 0x24);
    }
    if (mp168 != 0)
        mp168->removeReference();
    if (mpBpDispatch6c != 0)
        ((hkReferencedObject*)mpBpDispatch6c)->vfDestroy(1);
    if (mpBpDispatch70 != 0)
        ((hkReferencedObject*)mpBpDispatch70)->vfDestroy(1);
    if (mpBpDispatch74 != 0)
        ((hkReferencedObject*)mpBpDispatch74)->vfDestroy(1);
    mpCollisionFilter->removeReference();
    g_hkMemory->deallocate(mpCollisionInput->mpOwnedChunk, 8, 0x1c);
    g_hkMemory->deallocate(mpCollisionInput, 0x2c, 0x1c);
    mpSimulation->removeReference();
    releaseOpQueue(mpOpQueue);
    releaseArray(mCollisionListeners.mpData, mCollisionListeners.mSize << 2,
                 mCollisionListeners.mCapacityAndFlags);
    releaseArray(mListeners150.mpData, mListeners150.mSize << 2, mListeners150.mCapacityAndFlags);
    releaseArray(mListeners144.mpData, mListeners144.mSize << 2, mListeners144.mCapacityAndFlags);
    releaseArray(mPostCollideListeners.mpData, mPostCollideListeners.mSize << 2,
                 mPostCollideListeners.mCapacityAndFlags);
    releaseArray(mPostIntegrateListeners.mpData, mPostIntegrateListeners.mSize << 2,
                 mPostIntegrateListeners.mCapacityAndFlags);
    releaseArray(mPostSimulationListeners.mpData, mPostSimulationListeners.mSize << 2,
                 mPostSimulationListeners.mCapacityAndFlags);
    releaseArray(mIslandActivationListeners.mpData, mIslandActivationListeners.mSize << 2,
                 mIslandActivationListeners.mCapacityAndFlags);
    releaseArray(mWorldDeletionListeners.mpData, mWorldDeletionListeners.mSize << 2,
                 mWorldDeletionListeners.mCapacityAndFlags);
    releaseArray(mConstraintListeners.mpData, mConstraintListeners.mSize << 2,
                 mConstraintListeners.mCapacityAndFlags);
    releaseArray(mPhantomListeners.mpData, mPhantomListeners.mSize << 2,
                 mPhantomListeners.mCapacityAndFlags);
    releaseArray(mEntityListeners.mpData, mEntityListeners.mSize << 2,
                 mEntityListeners.mCapacityAndFlags);
    releaseArray(mPhantoms.mpData, mPhantoms.mSize << 2, mPhantoms.mCapacityAndFlags);
    releaseArray(mDirtyIslands.mpData, mDirtyIslands.mSize << 2, mDirtyIslands.mCapacityAndFlags);
    releaseArray(mInactive.mpData, mInactive.mSize << 2, mInactive.mCapacityAndFlags);
    releaseArray(mActive.mpData, mActive.mSize << 2, mActive.mCapacityAndFlags);
}

// ===========================================================================================
// @ 0x01083ff0
void hkWorld::activateRegion(const hkAabb& aabb)
{
    if (m8c != 0) {
        hkPendingOp op;
        op.mOpcode = 0x1f;
        op.mpPayload = g_hkMemory->allocate(0x20, 4);
        hkString_memCpy(op.mpPayload, &aabb, 0x20);
        mpOpQueue->push(&op);
        return;
    }
    hkArray<hkBroadPhaseEntry> result;
    result.mpData = 0;
    result.mSize = 0;
    result.mCapacityAndFlags = 0x80000000;
    mpBroadPhase->query(&aabb, &result);
    if (result.mSize > 0) {
        int i = 0;
        do {
            uchar* pRecord = result.mpData[i].mpRecord;
            hkEntity* pEntity = (hkEntity*)(pRecord + ((hkBpRecord*)pRecord)->mEntityOffset);
            if (pEntity->mState == 1) {
                hkEntity* pActivated = (hkEntity*)((char*)pEntity + pEntity->mActivateOffset);
                if (pActivated)
                    pActivated->activate();
            }
        } while (++i < result.mSize);
    }
    if (result.mCapacityAndFlags >= 0) {
        hkThreadMemory* pThreadMemory = (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
        pThreadMemory->deallocateChunk(result.mpData, (result.mCapacityAndFlags & 0x3fffffff) * 8, 0x14);
    }
}
