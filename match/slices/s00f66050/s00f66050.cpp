// Slice s00f66050 (batch gold7, worker 4) -- SP::cDistGrid / SP::cTerrainDistributeEffect
//   0x00F66050  SP::cDistGrid::~cDistGrid
//   0x00F662C0  SP::cTerrainDistributeEffect::Init
//   0x00F66440  spstl::slot_vector_base<...>::create
//   0x00F66560  SP::cDistGrid::ActivateCell
//   0x00F66770  SP::cTerrainDistributeEffect::Shutdown
//   0x00F667E0  SP::cDistGrid::UpdateCell
//   0x00F66BA0  SP::cDistGrid::Update
//   0x00F66CB0  SP::cTerrainDistributeEffect::ApplyEffect
//   0x00F66D20  cDistCellMesh::Init             (unnamed in the PDB)
//   0x00F66E70  cDistCellMesh::~cDistCellMesh   (unnamed in the PDB)
//   0x00F66EF0  cDistCellMesh::LockItems        (unnamed in the PDB)
// Object file: SPTerrainDistributeEffect.obj (VS2008 SP1).
// Retail cDistGrid is 0x104 bytes (PDB 0xd0): the slot deque is 0x20 bytes (so the camera
// members sit 4 bytes later than the PDB) and a normalised camera position follows
// mCameraH; mDistInfo/mTypeMapModCount are at +0xa0/+0xa4 and mTypeMods[9] at +0xe0.
// Retail cLevelInfo is 0x28 bytes (PDB 0x20) and retail cActiveCellInfo is 0x58.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
#include "game/types.h"
#include <new>
#include <math.h>

namespace rw { namespace math {
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3 operator*(const Vector3& v, float s) {
    Vector3 r;
    r.x = v.x * s;
    r.y = v.y * s;
    r.z = v.z * s;
    return r;
}
struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    Matrix3(const Matrix3& other);   // 0x0041CB40 (out of line)
    const Vector3& operator[](int row) const { return *(const Vector3*)&m[row][0]; }
};
extern Vector3 ZERO;                 // 0x016C9638 (Vector3::ZERO)
extern Matrix3 IDENTITY;             // 0x016C9614 (Matrix3::IDENTITY)
}}
using rw::math::Vector3;
using rw::math::Matrix3;

void* __cdecl operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);   // 0x00F473A0
void __cdecl EASTL_allocator_deallocate(void* p);         // 0x00F47380
void __cdecl FreeArrayMemory(void* p);                    // 0x00F47410

namespace EA {

namespace COM {
class __declspec(novtable) IUnknown32 { public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual void* AsInterface(uint32_t id) = 0;
};
}

template <class T> class RefCountTemplate { public:
    RefCountTemplate() {}
    virtual ~RefCountTemplate() {}
    T mRefCount;
};

template <class T> class AutoRefCount { public:
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p) : mpObject(p) { if (p) p->AddRef(); }
    AutoRefCount& operator=(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

namespace Swarm {

struct cTransform {                  // 0x38
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3  mTranslation;
    float    mScale;
    Matrix3  mRotation;

    cTransform() : mFlags(0), mModificationCount(0), mTranslation(rw::math::ZERO), mScale(1.0f),
                   mRotation(rw::math::IDENTITY) {}
    float GetScale() const { return mScale; }
};

class cComponentBase : public EA::RefCountTemplate<int> { public:
    cComponentBase() { mRefCount = 0; }
    virtual ~cComponentBase() {}
};

class cIVisualEffect {
public:
    virtual int AddRef() = 0;                    // +0x00
    virtual int Release() = 0;                   // +0x04
    virtual void Start(int hardStart) = 0;       // +0x08
    virtual int Stop(int hardStop) = 0;          // +0x0c
};

// Per-effect parameter block (camera pose lives at +0x5c / +0x80).
struct cEffectParams {
    cEffectParams();
    ~cEffectParams();                        // 0x007D4AE0
    uint32_t mPad00[0x5c / 4];
    Matrix3  mCameraOrient;                  // +0x5c
    Vector3  mCameraPos;                     // +0x80
    uint32_t mPad8c[0x18 / 4];               // +0x8c
    uint32_t mPadA4;
    AutoRefCount<EA::COM::IUnknown32> mUnknownParams[12];   // +0xa8
};

}  // namespace Swarm
}  // namespace EA

namespace SP {

using EA::AutoRefCount;
using EA::Swarm::cIVisualEffect;
using EA::Swarm::cEffectParams;

extern const uint8_t g_swizzle[16];      // 0x01491464
extern const float   g_quarterPi;        // 0x015B0CC4  (pi/4, float)
extern const double  g_two;              // 0x013F1298  2.0 as a double
extern const float   g_angleEpsilon;     // 0x013F11C8  (1e-6)
extern const float   g_angleHalf;        // 0x01471064  (0.5)
extern const float   g_realOne;          // 0x01485720  (1.0)

// ---------------------------------------------------------------- small value types
struct cCellEffectInfo {                 // 0x10
    int   mEffectIndex;                  // +0x00
    float mMinHeight;                    // +0x04
    float mMaxHeight;                    // +0x08
    char  mDistributeType;               // +0x0c
    char  mResourceType;                 // +0x0d
    unsigned char mOverrideSet;          // +0x0e
};

struct cCell {                           // 0x18
    unsigned short mMinHeight;           // +0x00
    unsigned short mMaxHeight;           // +0x02
    unsigned short mTypeMask;            // +0x04
    short mActiveSlot;                   // +0x06
    short mActiveChildren;               // +0x08
    Vector3 mDirection;                  // +0x0c
};

struct cHeightCell {                     // 0x04 (min/max only)
    unsigned short mMinHeight;           // +0x00
    unsigned short mMaxHeight;           // +0x02
};

struct cHeightRanges {                   // 0x1c
    int mFaceSize;                       // +0x00
    int mLevelOffsets[5];                // +0x04
    cHeightCell* mCellData;              // +0x18
};

struct cEffectVector {                   // eastl::vector<cCellEffectInfo> (0x14)
    cCellEffectInfo* mpBegin;            // +0x00
    cCellEffectInfo* mpEnd;              // +0x04
    cCellEffectInfo* mpCapacity;         // +0x08
    uint32_t mAllocator[2];              // +0x0c
};

struct cLevelInfo {                      // 0x28 in retail (0x20 in the PDB)
    float mActiveDist;                   // +0x00
    float mChildActiveDist;              // +0x04
    float mActiveFacing;                 // +0x08
    float mChildActiveFacing;            // +0x0c
    float mExtra;                        // +0x10
    cEffectVector mEffectInfo;           // +0x14
};

struct cTerrainDistributeDescription {   // 0xd4 in retail (0xb4 in the PDB)
    uint32_t mPad00[3];                  // +0x00
    cLevelInfo* mLevelInfo;              // +0x0c (cLevelInfo[5], stride 0x28)
};

struct cTerrainMapSet {                  // refcounted (refcount at +4, vtable slot 0 = dtor)
    uint32_t mVtbl;                      // +0x00
    int mRefCount;                       // +0x04
    uint32_t mPad08[0x50 / 4];           // +0x08
    cHeightRanges* mHeightRanges;        // +0x58

    void AddRef() { ++mRefCount; }
    void Release()
    {
        if (--mRefCount == 0) {
            mRefCount = 1;
            (*(void(__thiscall**)(cTerrainMapSet*, int))mVtbl)(this, 1);
        }
    }
};

struct cResourceID {                     // 64-bit resource id
    uint32_t mLow;                       // +0x00
    uint32_t mHigh;                      // +0x04
};

class cTerrainDistributeInfo : public EA::COM::IUnknown32 {   // distributed terrain resource
public:
    struct cTypeInfo {                   // 0x40
        uint32_t mProps;                 // +0x00
        float    mMinEmitMap;            // +0x04
        float    mMaxEmitMap;            // +0x08
        float    mSpriteScale;           // +0x0c
        cResourceID mResourceIDs[5];     // +0x10
        uint32_t mPad38[2];              // +0x38
    };
public:
    int       mRefCount;                 // +0x04
    uint32_t  mPad08[2];                 // +0x08
    cTypeInfo mTypeInfo[9];              // +0x10 .. +0x24f
    unsigned short* mpTypes;             // +0x250
    int       mLevelSize;                // +0x254
    int       mModCount;                 // +0x258
};

// Key handed to the resource loader: the 64-bit resource id plus the id's type set.
struct cResourceKey {                    // 12 bytes
    uint32_t mLow;                       // +0x00
    uint32_t mSet;                       // +0x04
    uint32_t mHigh;                      // +0x08
};

struct cActiveCellInfo {                 // 0x58
    EA::Swarm::cTransform mSourceTransform;      // +0x00
    AutoRefCount<cIVisualEffect> mEffects[8];    // +0x38

    cActiveCellInfo() {}
    cActiveCellInfo(const cActiveCellInfo& src); // 0x00F65260
    ~cActiveCellInfo()
    {
        for (int i = 7; i >= 0; --i) {
            cIVisualEffect* p = mEffects[i].mpObject;
            if (p)
                p->Release();
        }
    }
};

struct slot_vector_entry {
    uint32_t mSlotInfo;                  // +0x00 (used:1, last:1, next-free:30)
    cActiveCellInfo mData;               // +0x04
};

struct eastl_vector_ptrs {               // 0x14
    slot_vector_entry** mpBegin;
    slot_vector_entry** mpEnd;
    slot_vector_entry** mpCapacity;
    uint32_t mAlloc[2];
};

struct simple_deque {
    eastl_vector_ptrs mBlocks;           // +0x00
    uint32_t mBlockPos;                  // +0x14
};

enum {
    kSlotsPerBlock = 128,
    kSlotUsed      = 0x80000000,
    kSlotLast      = 0x40000000,
    kSlotIndexMask = 0x3fffffff
};

class slot_deque {                       // 0x20 (SP::cDistGrid::mActiveCellSlots)
public:
    slot_vector_entry* at(uint32_t i) const
    {
        uint32_t off = (i & (kSlotsPerBlock - 1)) * sizeof(slot_vector_entry);
        return (slot_vector_entry*)((char*)mBlocks.mBlocks.mpBegin[i >> 7] + off);
    }
    uint32_t size() const
    {
        int d = (int)mBlocks.mBlocks.mpEnd - (int)mBlocks.mBlocks.mpBegin;
        return (uint32_t)((d >> 2) * kSlotsPerBlock + (int)mBlocks.mBlockPos -
                          (kSlotsPerBlock - 1));
    }
    void createBlock();                                  // 0x00F65FE0
    uint32_t create(const cActiveCellInfo& value);       // 0x00F66440
    void pop_back();                                     // 0x00F659A0

    simple_deque mBlocks;                // +0x00
    uint32_t mBegin;                     // +0x18
    uint32_t mFreeChain;                 // +0x1c
};

class cEffectsWorld {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

class cDistGrid {
public:
    cDistGrid();
    ~cDistGrid();
    void Init(cLevelInfo* level, int collectionIndex);           // 0x00F63EB0
    void SetTerrainMapSet(cTerrainMapSet* set);                  // 0x00F64180
    void SetDistributeInfo(cTerrainDistributeInfo* info);        // 0x00F641F0
    void SetupEffect(const cCellEffectInfo& info, cIVisualEffect* effect, const cCell& cell,
                     int level, int face, int x, int y);         // 0x00F64290
    void Stop();                                                 // 0x00F65360
    void RefreshCell(cCell* cell, int level, int face, int x, int y, int z);  // 0x00F65430
    void DeactivateCell(cCell* cell);                            // 0x00F65A10
    cDistGrid* UpdateTypes();                                    // 0x00F65A90
    void ActivateCell(cCell* cell, int level, float minHeight, float maxHeight,
                      int face, unsigned x, unsigned y);
    int UpdateCell(int level, int face, unsigned x, unsigned y);
    void Update(const Vector3& pos, const Matrix3& orient);

    int CellIndex(int level, int face, unsigned char a, unsigned char b) const
    {
        unsigned t = (unsigned)g_swizzle[b >> 4] * 2 | (unsigned)g_swizzle[a >> 4];
        t = t << 7 | (unsigned)g_swizzle[b & 0xf];
        t = t * 2 | (unsigned)g_swizzle[a & 0xf];
        return (int)t + mLevelOffsets[level] + mFaceSize * face;
    }
    cCell* Cell(int level, int face, unsigned char a, unsigned char b) const
    {
        return mCellData + CellIndex(level, face, a, b);
    }

    AutoRefCount<cEffectsWorld> mWorld;      // +0x00
    int mCollectionIndex;                    // +0x04
    int mFaceSize;                           // +0x08
    cLevelInfo* mLevelInfo;                  // +0x0c
    int mLevelOffsets[5];                    // +0x10
    cCell* mCellData;                        // +0x24
    AutoRefCount<cTerrainMapSet> mTerrainMapSet;   // +0x28
    float mHeightBase;                       // +0x2c
    float mHeightRange16;                    // +0x30
    slot_deque mActiveCellSlots;             // +0x34
    Vector3 mCameraPos;                      // +0x54
    Matrix3 mCameraOrient;                   // +0x60
    Vector3 mCameraForward;                  // +0x84
    float   mCameraH;                        // +0x90
    Vector3 mCameraDir;                      // +0x94
    AutoRefCount<cTerrainDistributeInfo> mDistInfo;  // +0xa0
    int mTypeMapModCount;                    // +0xa4
    EA::Swarm::cTransform mSourceTransform;  // +0xa8
    uint32_t mTypeMods[9];                   // +0xe0
};

// Effect-side objects ------------------------------------------------------------
class cTerrainSphere {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual cTerrainMapSet* GetTerrainMapSet() = 0;          // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual cTerrainDistributeInfo* GetDistributeInfo() = 0; // +0x28
};

// Object handed to Init; vtable slot 40 (+0xa0) yields the effect's global parameter block.
class cEffectParamsHost {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual EA::Swarm::cEffectParams* GetGlobalParams();    // slot 40 (+0xa0)
};

class cEffectResource {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

class cResourceManager {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void* GetResource(const cResourceKey* key, void** ppOut, int a, int b,
                              int c, int d, int e, int f);   // slot 4 (+0x10)
};

// Texture / buffer / mesh owner used by the distribute cell renderer (no PDB name).
struct cFormatInfo {
    uint8_t  mPad00[0xf];                    // +0x00
    uint8_t  mIndexStride;                   // +0x0f
};

class cMeshBuffer {                          // 0x10 (vertex/index buffer interface)
public:
    void* Lock(unsigned int type, unsigned int first, unsigned int count);  // 0x011F3620
    cFormatInfo* mpFormat;                   // +0x00
    uint32_t mPad04;                         // +0x04
    int mBaseIndex;                          // +0x08
    int mCapacity;                           // +0x0c
};

class cIndexBuffer {
public:
    unsigned int Lock(unsigned int type, void** ppData);     // 0x011F4F20
    void* Unlock(void** ppData);                             // 0x011F4FD0
};

class cDistCellMesh {                        // 0x34
public:
    void Init(const void* desc, int indexCount, int numCells);
    ~cDistCellMesh();
    bool LockItems(int* pOut, void* unused, int count, int param);

    uint32_t mPad00;                         // +0x00
    void*    mTexture;                       // +0x04
    cMeshBuffer* mBuffer;                    // +0x08
    void*    mDynamicBuffer;                 // +0x0c
    void*    mMesh;                          // +0x10
    int      mIndexCount;                    // +0x14 (capacity in entries)
    int      mBaseOffset;                    // +0x18 (next free entry)
    int      mNumCells;                      // +0x1c
    uint32_t mPad20;                         // +0x20
    int      mItemCount;                     // +0x24
    uint32_t mPad28;                         // +0x28
    int      mParam;                         // +0x2c
    int      mFlag;                          // +0x30
};

class cTerrainDistributeEffect : public EA::Swarm::cComponentBase {
public:
    void Init(cEffectParamsHost* host, int a, int b);
    void Shutdown();
    void ApplyEffect(int a, int b, int c);

    void* mPad08;                            // +0x08
    cTerrainDistributeDescription* mDesc;    // +0x0c
    int   mCollectionIndex;                  // +0x10
    cEffectParams* mGlobalParams;            // +0x14
    cEffectParams* mChildParams;             // +0x18
    cDistGrid* mDistGrid;                    // +0x1c
    uint32_t mFlags;                         // +0x20
    EA::Swarm::cTransform mSourceTransform;  // +0x24
    EA::Swarm::cTransform mRigidTransform;   // +0x5c
};

}  // namespace SP

using namespace SP;

// ---- external helpers (addresses in comments) ----
cTerrainSphere* __cdecl SP_GetActiveTerrainSphere();          // 0x00F48AA0
double __cdecl SP_AngleToCos(float a);                        // 0x00F63E10
cIVisualEffect* __stdcall CreateVisualEffect(int effectIndex, int collectionIndex, int flags);
                                                              // 0x00A71410
cResourceManager* __cdecl ResourceMan_GetManager();           // 0x0067DCD0

// ---- renderer helpers (unknown classes, named by role) ----
struct cRenderDevice { uint32_t mPad00; };
extern cRenderDevice g_renderDevice;                  // 0x015D07B0
extern cIndexBuffer* g_indexBufferLarge;              // 0x016C9698
extern cIndexBuffer* g_indexBufferSmall;              // 0x016C969C
extern int   g_meshRefCount;                          // 0x016C96A0

void* __cdecl CreateRenderBuffer(cRenderDevice* device, int width, int height, int format,
                                 int usage, int flags);          // 0x00762C60
void* __cdecl CreateMeshBuffers(void* texture, int count, int a, int b);  // 0x00762B70
void  __cdecl ReleaseRenderBuffer(void* buffer);                 // 0x00762A30
void  __cdecl ReleaseMeshBuffer(void* buffer);                   // 0x00762A00
void* __cdecl LoadTexture(const void* desc);                     // 0x007C3AF0
void* __cdecl SP_CreateMesh(int a);                              // 0x00761840

// Minimum/maximum that compile to minss/maxss under /fp:fast.
static __forceinline float MinF(float a, float b) { return a < b ? a : b; }
static __forceinline float MaxF(float a, float b) { return a < b ? b : a; }

// @ 0x00f66050
SP::cDistGrid::~cDistGrid()
{
    if (mDistInfo)
        mDistInfo->Release();
    while (mActiveCellSlots.mBlocks.mBlocks.mpBegin != mActiveCellSlots.mBlocks.mBlocks.mpEnd)
        mActiveCellSlots.pop_back();
    if (mActiveCellSlots.mBlocks.mBlocks.mpBegin)
        EASTL_allocator_deallocate(mActiveCellSlots.mBlocks.mBlocks.mpBegin);
    if (mTerrainMapSet)
        mTerrainMapSet->Release();
    EASTL_allocator_deallocate(mCellData);
    if (mWorld)
        mWorld->Release();
}

// @ 0x00f662c0
void SP::cTerrainDistributeEffect::Init(cEffectParamsHost* host, int a, int b)
{
    mGlobalParams = host->GetGlobalParams();

    cTerrainSphere* sphere = SP_GetActiveTerrainSphere();
    if (!sphere)
        return;
    if (!sphere->GetTerrainMapSet())
        return;
    if (!sphere->GetDistributeInfo())
        return;

    cDistGrid* grid = new ("Terrain/DistGrid/cDistGrid", 0, 0, 0, 0) cDistGrid;
    mDistGrid = grid;

    grid->SetTerrainMapSet(sphere->GetTerrainMapSet());
    grid->Init(mDesc->mLevelInfo, mCollectionIndex);
    cTerrainDistributeInfo* info = sphere->GetDistributeInfo();
    grid->SetDistributeInfo(info);

    cResourceManager* manager = ResourceMan_GetManager();
    cEffectResource* resource = 0;
    const cTerrainDistributeInfo::cTypeInfo* typeInfo = info->mTypeInfo;
    for (int row = 0; row < 9; row++, typeInfo++) {
        for (int i = 0; i < 5; i++) {
            const cResourceID& id = typeInfo->mResourceIDs[i];
            if ((id.mLow & id.mHigh) == 0xffffffff)
                continue;
            cResourceKey key;
            key.mLow = id.mLow;
            key.mSet = (i < 2) ? 0x2f4e681c : 0x00e6bce5;
            key.mHigh = id.mHigh;
            if (resource) {
                resource = 0;
                resource->Release();
            }
            manager->GetResource(&key, (void**)&resource, 0, 0, 0, 0, 0, 0);
        }
    }

    if (resource)
        resource->Release();
}

// @ 0x00f66440
uint32_t SP::slot_deque::create(const cActiveCellInfo& value)
{
    uint32_t index = mFreeChain;
    if (index == kSlotIndexMask) {
        cActiveCellInfo temp(value);
        index = size();
        createBlock();

        slot_vector_entry* last = mBlocks.mBlocks.mpEnd[-1] + mBlocks.mBlockPos;
        last->mSlotInfo = kSlotUsed;
        if (index != 0)
            at(index - 1)->mSlotInfo &= ~kSlotLast;

        slot_vector_entry* entry = at(index);
        entry->mSlotInfo |= kSlotLast;
        entry->mSlotInfo &= ~kSlotUsed;
        ::new ((void*)&entry->mData) cActiveCellInfo(temp);
    } else {
        slot_vector_entry* entry = at(index);
        mFreeChain = entry->mSlotInfo & kSlotIndexMask;
        entry->mSlotInfo &= ~kSlotUsed;
        ::new ((void*)&entry->mData) cActiveCellInfo(value);
    }
    if (index < mBegin)
        mBegin = index;
    return index;
}

// @ 0x00f66560
void SP::cDistGrid::ActivateCell(cCell* cell, int level, float minHeight, float maxHeight,
                                 int face, unsigned x, unsigned y)
{
    cActiveCellInfo info;
    cell->mActiveSlot = (short)mActiveCellSlots.create(info);

    cLevelInfo* pLevel = mLevelInfo + level;
    int count = (int)(pLevel->mEffectInfo.mpEnd - pLevel->mEffectInfo.mpBegin);
    if (count <= 0)
        return;

    AutoRefCount<cIVisualEffect>* pSlot = mActiveCellSlots.at(cell->mActiveSlot)->mData.mEffects;
    cCellEffectInfo* pInfo = pLevel->mEffectInfo.mpBegin;
    for (int i = 0; i < count; i++, pInfo++, pSlot++) {
        char type = pInfo->mDistributeType;
        if (pInfo->mEffectIndex < 0)
            continue;
        if (maxHeight < pInfo->mMinHeight)
            continue;
        if (pInfo->mMaxHeight < minHeight)
            continue;
        if (type >= 0) {
            if (type < 9 || (cell->mTypeMask & 0x7fff) == 0) {
                if ((cell->mTypeMask & (1 << type)) == 0)
                    continue;
            }
        }

        AutoRefCount<cIVisualEffect>& slot = *pSlot;
        cIVisualEffect* effect =
            CreateVisualEffect(pInfo->mEffectIndex, mCollectionIndex, 0);
        slot = effect;
        if (slot.mpObject) {
            SetupEffect(*pInfo, slot.mpObject, *cell, level, face, x, y);
            slot.mpObject->Start(0);
        }
    }
}

// @ 0x00f66770
void SP::cTerrainDistributeEffect::Shutdown()
{
    cEffectParams* params = mChildParams;
    if (params) {
        params->~cEffectParams();
        EASTL_allocator_deallocate(params);
        mChildParams = 0;
    }
    cDistGrid* grid = mDistGrid;
    if (grid) {
        grid->Stop();
        grid->mDistInfo = 0;
        if (mDistGrid) {
            mDistGrid->~cDistGrid();
            EASTL_allocator_deallocate(mDistGrid);
        }
        mDistGrid = 0;
    }
}

// @ 0x00f667e0
int SP::cDistGrid::UpdateCell(int level, int face, unsigned x, unsigned y)
{
    cLevelInfo* pLevel = mLevelInfo + level;
    int index = CellIndex(level, face, (unsigned char)x, (unsigned char)y);
    cCell* cell = mCellData + index;
    cHeightCell* range = mTerrainMapSet->mHeightRanges->mCellData + index;

    bool changed;
    if (cell->mMinHeight == range->mMinHeight && cell->mMaxHeight == range->mMaxHeight) {
        changed = false;
    } else {
        cell->mMinHeight = range->mMinHeight;
        changed = true;
        cell->mMaxHeight = range->mMaxHeight;
    }

    float minHeight = (float)cell->mMinHeight * mHeightRange16 + mHeightBase;
    float maxHeight = (float)cell->mMaxHeight * mHeightRange16 + mHeightBase;
    float height = MaxF(mCameraH, minHeight);
    height = MinF(height, maxHeight);

    float dx = mCameraPos.x - cell->mDirection.x * height;
    float dy = mCameraPos.y - cell->mDirection.y * height;
    float dz = mCameraPos.z - cell->mDirection.z * height;
    float distSq = dz * dz + dy * dy + dx * dx;
    float facingDist = (mCameraH - height) * pLevel->mActiveFacing;

    float dot = cell->mDirection.z * mCameraDir.z +
                cell->mDirection.y * mCameraDir.y +
                cell->mDirection.x * mCameraDir.x;

    // Angular tolerance: the level's cone angle shrinks as the level size grows.
    double angle = SP_AngleToCos(dot);
    float cone = (float)(angle - g_two * (1.0 / (double)(1 << level)) * g_quarterPi);
    if (cone < 0.0f)
        cone = 0.0f;
    float facing = g_angleHalf - dot / (float)(sqrt(distSq) + g_angleEpsilon) * g_angleHalf;

    bool active;
    bool slotActive = cell->mActiveSlot >= 0;
    if (pLevel->mActiveDist * pLevel->mActiveDist < distSq ||
        pLevel->mChildActiveFacing < facing) {
        active = false;
        if (slotActive)
            DeactivateCell(cell);
    } else {
        active = true;
        if (!slotActive)
            ActivateCell(cell, level, minHeight, maxHeight, face, x, y);
        else if (changed)
            RefreshCell(cell, level, face, x, y, 2);
    }

    float width = height * cone;
    float childDist = (float)sqrt(width * width + facingDist * facingDist);

    if (cell->mActiveChildren > 0 ||
        (pLevel->mChildActiveDist >= childDist && pLevel->mExtra >= facing)) {
        if (level + 1 < 5) {
            unsigned x2 = x * 2;
            unsigned y2 = y * 2;
            cell->mActiveChildren = 0;
            cell->mActiveChildren += (short)UpdateCell(level + 1, face, x2, y2);
            cell->mActiveChildren += (short)UpdateCell(level + 1, face, x2 + 1, y2);
            cell->mActiveChildren += (short)UpdateCell(level + 1, face, x2, y2 + 1);
            cell->mActiveChildren += (short)UpdateCell(level + 1, face, x2 + 1, y2 + 1);
        }
    }
    return cell->mActiveChildren + (active ? 1 : 0);
}

// @ 0x00f66ba0
void SP::cDistGrid::Update(const Vector3& pos, const Matrix3& orient)
{
    if (mDistInfo && mDistInfo->mpTypes && mTypeMapModCount != mDistInfo->mModCount)
        UpdateTypes();

    mCameraPos = pos;
    mCameraOrient = orient;
    mCameraForward = orient[1];

    mCameraH = (float)sqrt(pos.y * pos.y + (pos.z * pos.z + pos.x * pos.x));
    float invH = g_realOne / mCameraH;
    mCameraDir.x = mCameraPos.x * invH;
    mCameraDir.y = mCameraPos.y * invH;
    mCameraDir.z = mCameraPos.z * invH;

    for (int i = 0; i < 6; i++)
        UpdateCell(0, i, 0, 0);
}

// @ 0x00f66cb0
void SP::cTerrainDistributeEffect::ApplyEffect(int a, int b, int c)
{
    cTerrainSphere* sphere = SP_GetActiveTerrainSphere();
    if (sphere)
        mDistGrid->mDistInfo = sphere->GetDistributeInfo();

    mDistGrid->Update(mGlobalParams->mCameraPos, mGlobalParams->mCameraOrient);
}

// @ 0x00f66d20
void SP::cDistCellMesh::Init(const void* desc, int indexCount, int numCells)
{
    mIndexCount = indexCount;
    mNumCells = numCells;

    if (g_meshRefCount++ == 0) {
        g_indexBufferLarge = (cIndexBuffer*)CreateRenderBuffer(&g_renderDevice, 0xc00, 0xc00,
                                                              8, 4, 0);
        void* data = 0;
        g_indexBufferLarge->Lock(2, &data);
        {
            uint16_t* p = (uint16_t*)data;
            for (int i = 0; i < 0x400; i++, p += 3) {
                p[0] = (uint16_t)i;
                p[1] = (uint16_t)(i + 1);
                p[2] = (uint16_t)(i + 2);
            }
        }
        g_indexBufferLarge->Unlock(&data);

        g_indexBufferSmall = (cIndexBuffer*)CreateRenderBuffer(&g_renderDevice, 0x100, 0x100,
                                                              8, 5, 0);
        data = 0;
        g_indexBufferSmall->Lock(2, &data);
        {
            uint16_t* q = (uint16_t*)data;
            for (int i = 0; i < 0x100; i++)
                q[i] = (uint16_t)i;
        }
        g_indexBufferSmall->Unlock(&data);
    }

    mTexture = LoadTexture(desc);
    mBuffer = (cMeshBuffer*)CreateMeshBuffers(mTexture, mIndexCount, 1, 0);
    mDynamicBuffer = numCells ? CreateRenderBuffer(&g_renderDevice, numCells, numCells,
                                                   0x208, 4, 0) : 0;
    mMesh = SP_CreateMesh(1);
}

// @ 0x00f66e70
SP::cDistCellMesh::~cDistCellMesh()
{
    if (mMesh) {
        FreeArrayMemory(mMesh);
        mMesh = 0;
    }
    if (mDynamicBuffer) {
        ReleaseRenderBuffer(mDynamicBuffer);
        mDynamicBuffer = 0;
    }
    if (mBuffer) {
        ReleaseMeshBuffer(mBuffer);
        mBuffer = 0;
    }
    mTexture = 0;
    if (--g_meshRefCount == 0) {
        ReleaseRenderBuffer(g_indexBufferSmall);
        g_indexBufferSmall = 0;
        ReleaseRenderBuffer(g_indexBufferLarge);
        g_indexBufferLarge = 0;
    }
}

// @ 0x00f66ef0
bool SP::cDistCellMesh::LockItems(int* pOut, void* unused, int count, int param)
{
    int offset = mBaseOffset;
    int type = 10;
    if (count > mIndexCount - offset) {
        type = 6;
        offset = 0;
    }
    *pOut = 0;

    cMeshBuffer* buffer = mBuffer;
    int num = count;
    if (!num)
        num = buffer->mCapacity;
    unsigned char stride = buffer->mpFormat->mIndexStride;
    void* p = buffer->Lock(type, (buffer->mBaseIndex + offset) * stride, stride * num);
    if (!p)
        return false;

    mBaseOffset = offset;
    mItemCount = count;
    mParam = param;
    mFlag = 1;
    *pOut = (int)p;
    return true;
}
