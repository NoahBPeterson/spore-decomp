// Slice s00f65070 (batch gold3, slice 128) -- SP::cDistGrid / SP::cTerrainDistributeEffect
//   0x00F65070  SP::cTerrainDistributeEffect::cTerrainDistributeEffect
//   0x00F65150  SP::cTerrainDistributeEffect::SetTransforms
//   0x00F65180  SP::cTerrainDistributeEffect::SetIntParams
//   0x00F651E0  SP::cTerrainDistributeEffect::SetUnknownParam
//   0x00F65260  SP::cActiveCellInfo::cActiveCellInfo (copy ctor)
//   0x00F652C0  spstl::slot_vector_base<...>::next
//   0x00F65360  SP::cDistGrid::Stop
//   0x00F65430  SP::cDistGrid::RefreshCell
//   0x00F65640  SP::cDistGrid::UpdateTypesUp
//   0x00F658A0  SP::cTerrainDistributeEffect::Stop
//   0x00F658C0  SP::cTerrainDistributeEffect::SetFloatParams
//   0x00F65920  spstl::slot_vector_base<...>::destroy
//   0x00F659A0  spstl::simple_deque<...>::pop_back
//   0x00F65A10  SP::cDistGrid::DeactivateCell
//   0x00F65A90  SP::cDistGrid::UpdateTypes
//   0x00F65EC0  SP::cDistGrid::UpdateTypesWithDebugValues
//   0x00F65FA0  SP::cTerrainDistributeEffect::Start
// Object file: SPTerrainDistributeEffect.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
#include "game/types.h"

namespace rw { namespace math {
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix3 {
    float m[3][3];
    Matrix3() {}
    Matrix3(const Matrix3& other);   // 0x0041CB40 (out of line)
};
extern Vector3 ZERO;                 // 0x016C9638 (Vector3::ZERO)
extern Matrix3 IDENTITY;             // 0x016C9614 (Matrix3::IDENTITY)
}}
using rw::math::Vector3;
using rw::math::Matrix3;

void* __cdecl operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                           const char* file, int line);   // 0x00F473A0

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
    AutoRefCount() {}
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
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
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
    cTransform(const cTransform& src)
        : mFlags(src.mFlags), mModificationCount(src.mModificationCount),
          mTranslation(src.mTranslation), mScale(src.mScale), mRotation(src.mRotation) {}
};
class cIComponent { public:
    cIComponent() {}
    virtual ~cIComponent() {}
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct RefCountBase : public RefCountTemplate<int> {
    RefCountBase() { mRefCount = 0; }
    virtual ~RefCountBase() {}
};
class cComponentBase : public cIComponent, public RefCountBase { public:
    cComponentBase() {}
    virtual ~cComponentBase() {}
};
class cIVisualEffect {
public:
    virtual int AddRef() = 0;                     // 0x00
    virtual int Release() = 0;                    // 0x04
    virtual void Start(int hardStart) = 0;        // 0x08
    virtual int Stop(int hardStop) = 0;           // 0x0c
};
struct cEffectParams {
    cEffectParams();                              // 0x007D55E0
    bool IntStore(int param, int a, int b);       // 0x00A84040
    bool FloatStore(int param, int a, int b);     // 0x00A83FD0
    uint32_t mPad00[0xa8 / 4];
    EA::AutoRefCount<EA::COM::IUnknown32> mUnknownParams[12];   // +0xa8
};
}  // namespace Swarm
}  // namespace EA

namespace SP {
using EA::Swarm::cIVisualEffect;
using EA::Swarm::cEffectParams;
using EA::AutoRefCount;

struct cTerrainDistributeDescription {
    uint32_t mPad00[2];
    uint32_t mFlags;                 // +0x08
};

struct cCellEffectInfo {             // 0x10
    int   mEffectIndex;
    float mMinHeight;
    float mMaxHeight;
    char  mDistributeType;           // +0x0c
    char  mResourceType;             // +0x0d
    unsigned char mOverrideSet;      // +0x0e
};

struct cCell {                       // 0x18
    unsigned short mMinHeight;
    unsigned short mMaxHeight;       // +0x02
    unsigned short mTypeMask;        // +0x04
    short mActiveSlot;               // +0x06
    short mActiveChildren;           // +0x08
    Vector3 mDirection;              // +0x0c
};

struct cLevelInfo {                  // 0x28 in retail
    uint32_t mPad00[5];
    cCellEffectInfo* mpBegin;        // +0x14
    cCellEffectInfo* mpEnd;          // +0x18
    cCellEffectInfo* mpCapacity;     // +0x1c
    uint32_t mPad20[2];
};

struct cActiveCellInfo {             // 0x58
    EA::Swarm::cTransform mSourceTransform;                       // +0x00
    AutoRefCount<cIVisualEffect> mEffects[8];                     // +0x38
    cActiveCellInfo() {}
    cActiveCellInfo(const cActiveCellInfo& src);
};

struct slot_vector_entry {
    uint32_t mSlotInfo;              // +0x00
    cActiveCellInfo mData;           // +0x04
};

struct eastl_vector_ptrs {           // 0x14
    slot_vector_entry** mpBegin;
    slot_vector_entry** mpEnd;
    slot_vector_entry** mpCapacity;
    uint32_t mAlloc[2];
};

struct simple_deque {
    eastl_vector_ptrs mBlocks;       // +0x00
    uint32_t mBlockPos;              // +0x14
};

class slot_deque {
public:
    slot_vector_entry* at(uint32_t i) const {
        uint32_t off = (i & 0x7f) * 0x5c;
        return (slot_vector_entry*)((char*)mBlocks.mBlocks.mpBegin[i >> 7] + off);
    }
    uint32_t size() const {
        int d = (int)mBlocks.mBlocks.mpEnd - (int)mBlocks.mBlocks.mpBegin;
        return (uint32_t)((d >> 2) * 0x80 + (int)mBlocks.mBlockPos - 0x7f);
    }
    uint32_t next(uint32_t i);
    void destroy(uint32_t i);
    void pop_back();

    simple_deque mBlocks;            // +0x00
    uint32_t mBegin;                 // +0x18
    uint32_t mFreeChain;             // +0x1c
};

// 0x00F473A0 operator new body.
struct BindPool {
    void Free(void* p);              // 0x009276C0
};
extern BindPool* g_pBindPool;        // 0x016C8B44

extern const uint8_t g_swizzle[16];  // 0x01491464

typedef void (__thiscall* TCopyCtor)(void* dst, const void* src);
extern "C" void __stdcall CopyArray(void* dst, const void* src, int elemSize, int count,
                                    TCopyCtor ctor);           // 0x00406540
extern "C" void CopyCtor_00ac8980();                       // 0x00AC8980
extern "C" cIVisualEffect* __stdcall CreateVisualEffect(int effectIndex, int collectionIndex,
                                                        int flags);   // 0x00A71410
struct cWorld {
    cIVisualEffect* CreateVisualEffect(int effectIndex, int collectionIndex, int flags);
};

struct cTypeMap {                    // tail of cTerrainDistributeInfo
    uint32_t mPad00[0x250 / 4];
    uint16_t* mpTypes;               // +0x250
    int mLevelSize;                  // +0x254
    int mModCount;                   // +0x258
};

struct cTerrainDistributeInfo {
    uint32_t mPad00[0x250 / 4];
    uint16_t* mpTypes;               // +0x250
    int mLevelSize;                  // +0x254
    int mModCount;                   // +0x258
};

class cDistGrid {
public:
    void Stop();
    void RefreshCell(cCell* cell, int level, int face, int x, int y, int z);
    __declspec(noinline) void UpdateTypesUp(int level, int face, int x0, int y0, int x1, int y1);
    void DeactivateCell(cCell* cell);
    cDistGrid* UpdateTypes();
    void UpdateTypesWithDebugValues();
    void SetupEffect(const cCellEffectInfo& info, cIVisualEffect* effect, const cCell& cell,
                     int level, int face, int x, int y);

    void* mWorld;                                        // +0x00
    int mCollectionIndex;                                // +0x04
    int mFaceSize;                                       // +0x08
    cLevelInfo* mLevelInfo;                              // +0x0c
    int mLevelOffsets[5];                                // +0x10
    cCell* mCellData;                                    // +0x24
    void* mTerrainMapSet;                                // +0x28
    float mHeightBase;                                   // +0x2c
    float mHeightRange16;                                // +0x30
    slot_deque mActiveCellSlots;                         // +0x34
    uint32_t mPad54[(0xa0 - 0x54) / 4];
    cTerrainDistributeInfo* mDistInfo;                   // +0xa0
    uint32_t mPadA4;
    EA::Swarm::cTransform mSourceTransform;              // +0xa8
    uint32_t mTypeMods[9];                               // +0xe0
};

class cTerrainDistributeEffect : public EA::Swarm::cComponentBase {
public:
    cTerrainDistributeEffect(cTerrainDistributeDescription* desc, int collectionIndex);
    void SetTransforms(const void* src, const void* rigid);
    bool SetIntParams(int a, int b, int c);
    bool SetUnknownParam(int index, EA::COM::IUnknown32* p);
    void Stop(int immediate);
    bool SetFloatParams(int a, int b, int c);
    void Start(int hardStart);
    uint32_t& Flags() { return mFlags; }

    cTerrainDistributeDescription* mDesc;    // +0x0c
    int mCollectionIndex;                    // +0x10
    cEffectParams* mGlobalParams;            // +0x14
    cEffectParams* mChildParams;             // +0x18
    cDistGrid* mDistGrid;                    // +0x1c
    uint32_t mFlags;                         // +0x20
    EA::Swarm::cTransform mSourceTransform;  // +0x24
    EA::Swarm::cTransform mRigidTransform;   // +0x5c
};

struct cSPTransformOps {
    void* Assign(const void* src);           // 0x00537DC0
};

}  // namespace SP

using namespace SP;

// @ 0x00f65070
SP::cTerrainDistributeEffect::cTerrainDistributeEffect(cTerrainDistributeDescription* desc,
                                                       int collectionIndex)
    : mDesc(desc), mCollectionIndex(collectionIndex), mGlobalParams(0), mChildParams(0),
      mDistGrid(0), mFlags(0)
{
}

// @ 0x00f65150
void SP::cTerrainDistributeEffect::SetTransforms(const void* src, const void* rigid)
{
    ((cSPTransformOps*)&mRigidTransform)->Assign(rigid);
    ((cSPTransformOps*)&mSourceTransform)->Assign(src);
}

// @ 0x00f65180
bool SP::cTerrainDistributeEffect::SetIntParams(int a, int b, int c)
{
    if (!mChildParams)
        mChildParams = new ("Swarm", 0, 0, 0, 0) EA::Swarm::cEffectParams();
    mChildParams->IntStore(a, b, c);
    return true;
}

// @ 0x00f651e0
bool SP::cTerrainDistributeEffect::SetUnknownParam(int index, EA::COM::IUnknown32* p)
{
    if (!mChildParams)
        mChildParams = new ("Swarm", 0, 0, 0, 0) EA::Swarm::cEffectParams();
    EA::Swarm::cEffectParams* params = mChildParams;
    params->mUnknownParams[index + 3] = p;
    return true;
}

// @ 0x00f65260
SP::cActiveCellInfo::cActiveCellInfo(const cActiveCellInfo& src)
    : mSourceTransform(src.mSourceTransform)
{
    CopyArray(mEffects, src.mEffects, 4, 8, (TCopyCtor)CopyCtor_00ac8980);
}

// @ 0x00f652c0
uint32_t SP::slot_deque::next(uint32_t i)
{
    uint32_t info = at(i)->mSlotInfo;
    for (;;) {
        bool stop = ((info >> 30) & 1) != 0;
        if (stop)
            return 0x3fffffff;
        ++i;
        info = at(i)->mSlotInfo;
        bool used = ((info >> 31) & 1) != 0;
        if (!used)
            return i;
    }
}

// @ 0x00f65360
void SP::cDistGrid::Stop()
{
    int n = (int)mActiveCellSlots.size();
    for (int i = 0; i < n; i++) {
        if ((uint32_t)i < mActiveCellSlots.size()) {
            bool used = ((mActiveCellSlots.at(i)->mSlotInfo >> 31) & 1) != 0;
            if (!used) {
                for (int k = 0; k < 8; k++) {
                    cIVisualEffect* p = mActiveCellSlots.at(i)->mData.mEffects[k].mpObject;
                    if (p) {
                        p->Stop(1);
                        mActiveCellSlots.at(i)->mData.mEffects[k] = 0;
                    }
                }
            }
        }
    }
}

// @ 0x00f65430
void SP::cDistGrid::RefreshCell(cCell* cell, int level, int face, int x, int y, int z)
{
    cLevelInfo* pLevel = mLevelInfo + level;
    float minHeight = (float)cell->mMinHeight * mHeightRange16 + mHeightBase;
    float maxHeight = (float)cell->mMaxHeight * mHeightRange16 + mHeightBase;
    cActiveCellInfo& info = mActiveCellSlots.at(cell->mActiveSlot)->mData;

    int count = (int)((pLevel->mpEnd - pLevel->mpBegin) >> 4);
    if (count <= 0)
        return;

    cCellEffectInfo* pInfo = pLevel->mpBegin;
    AutoRefCount<cIVisualEffect>* pSlot = info.mEffects;
    for (int i = 0; i < count; i++, pInfo++, pSlot++) {
        AutoRefCount<cIVisualEffect>& slot = *pSlot;
        char type = pInfo->mDistributeType;
        bool keep = true;
        if (pInfo->mEffectIndex < 0)
            keep = false;
        else if (maxHeight <= pInfo->mMinHeight)
            keep = false;
        else if (pInfo->mMaxHeight <= minHeight)
            keep = false;
        else if (type >= 0) {
            if (type < 9 || (cell->mTypeMask & 0x7fff) == 0) {
                if ((cell->mTypeMask & (1 << type)) == 0)
                    keep = false;
            }
        }

        if (keep) {
            if (slot.mpObject != 0) {
                if (z != 0) {
                    slot->Stop(1);
                    slot = 0;
                    slot = ((cWorld*)mWorld)->CreateVisualEffect(pInfo->mEffectIndex,
                                                                mCollectionIndex, 0);
                }
            } else {
                slot = ((cWorld*)mWorld)->CreateVisualEffect(pInfo->mEffectIndex,
                                                             mCollectionIndex, 0);
            }
            if (slot.mpObject != 0) {
                SetupEffect(*pInfo, slot.mpObject, *cell, level, face, x, y);
                slot->Start(0);
            }
        } else if (slot.mpObject != 0) {
            slot->Stop(1);
            slot = 0;
        }
    }
}

// @ 0x00f65640
void SP::cDistGrid::UpdateTypesUp(int level, int face, int x0, int y0, int x1, int y1)
{
    int hx0 = x0 / 2;
    int hy0 = y0 / 2;
    int hx1 = x1 / 2;
    int hy1 = y1 / 2;
    if (hx0 == hx1)
        return;

    int* pLevelOffset = &mLevelOffsets[level + 1];
    for (;;) {
        if (hy0 == hy1)
            return;

        cCell* pLevelCells = mCellData + (pLevelOffset[-1] + mFaceSize * face);
        cCell* pNextCells = mCellData + (pLevelOffset[0] + mFaceSize * face);
        int changed = 0;

        if (hy0 < hy1) {
            int y = hy0;
            do {
                int x = hx0;
                if (x < hx1) {
                    const uint8_t* high = &g_swizzle[y >> 4];
                    const uint8_t* low = &g_swizzle[y & 0xf];
                    do {
                        unsigned idx = (((g_swizzle[(x & 0xff) >> 4] |
                                          (unsigned)high[0] * 2) << 7 | low[0]) * 2 |
                                        g_swizzle[x & 0xf]);
                        cCell* pHigh = pNextCells + idx * 4;
                        cCell* pCell = pLevelCells + idx;
                        unsigned short m0 = pHigh[0].mTypeMask & 0x7fff;
                        unsigned short m1 = pHigh[1].mTypeMask & 0x7fff;
                        unsigned short m2 = pHigh[2].mTypeMask & 0x7fff;
                        unsigned short m3 = pHigh[3].mTypeMask & 0x7fff;
                        pHigh[0].mTypeMask = m0;
                        pHigh[1].mTypeMask = m1;
                        pHigh[2].mTypeMask = m2;
                        pHigh[3].mTypeMask = m3;
                        unsigned short mask = m0 | m1 | m2 | m3;
                        if (pCell->mTypeMask != mask) {
                            pCell->mTypeMask = mask;
                            if (pCell->mActiveSlot >= 0)
                                RefreshCell(pCell, level, face, x, y, 1);
                            changed++;
                        }
                    } while (++x < hx1);
                }
            } while (++y < hy1);

            if (changed != 0 && level > 0) {
                hx0 /= 2;
                level--;
                pLevelOffset--;
                hy0 /= 2;
                hx1 /= 2;
                hy1 /= 2;
                if (hx0 != hx1)
                    continue;
                return;
            }
        }
        pLevelCells->mTypeMask &= 0x7fff;
        return;
    }
}

// @ 0x00f658a0
void SP::cTerrainDistributeEffect::Stop(int immediate)
{
    if ((Flags() & 1) != 0) {
        Flags() &= ~1u;
        mDistGrid->Stop();
    }
}

// @ 0x00f658c0
bool SP::cTerrainDistributeEffect::SetFloatParams(int a, int b, int c)
{
    if (!mChildParams)
        mChildParams = new ("Swarm", 0, 0, 0, 0) EA::Swarm::cEffectParams();
    mChildParams->FloatStore(a, b, c);
    return true;
}

// @ 0x00f65920
void SP::slot_deque::destroy(uint32_t i)
{
    uint32_t index = i;
    slot_vector_entry* e = at(index);
    AutoRefCount<cIVisualEffect>* p = e->mData.mEffects + 8;
    for (int k = 7; k >= 0; --k) {
        cIVisualEffect* obj = p[-1].mpObject;
        if (obj)
            obj->Release();
        --p;
    }
    e->mSlotInfo = (e->mSlotInfo & 0xc0000000) | (mFreeChain & 0x3fffffff) | 0x80000000;
    mFreeChain = index;
    if (mBegin == index)
        mBegin = next(index);
}

// @ 0x00f659a0
void SP::slot_deque::pop_back()
{
    uint32_t pos = mBlocks.mBlockPos;
    slot_vector_entry* e = (slot_vector_entry*)((char*)mBlocks.mBlocks.mpEnd[-1] + pos * 0x5c);
    bool used = ((e->mSlotInfo >> 31) & 1) != 0;
    if (!used) {
        AutoRefCount<cIVisualEffect>* p = e->mData.mEffects + 8;
        for (int k = 7; k >= 0; --k) {
            cIVisualEffect* obj = p[-1].mpObject;
            if (obj)
                obj->Release();
            --p;
        }
    }
    if (mBlocks.mBlockPos != 0) {
        --mBlocks.mBlockPos;
        return;
    }
    g_pBindPool->Free(mBlocks.mBlocks.mpEnd[-1]);
    --mBlocks.mBlocks.mpEnd;
    mBlocks.mBlockPos = 0x7f;
}

// @ 0x00f65a10
void SP::cDistGrid::DeactivateCell(cCell* cell)
{
    cActiveCellInfo& info = mActiveCellSlots.at(cell->mActiveSlot)->mData;
    for (int k = 0; k < 8; k++) {
        cIVisualEffect* p = info.mEffects[k].mpObject;
        if (p) {
            p->Stop(1);
            info.mEffects[k] = 0;
        }
    }
    mActiveCellSlots.destroy(cell->mActiveSlot);
    cell->mActiveSlot = (short)-1;
}

// @ 0x00f65a90
cDistGrid* SP::cDistGrid::UpdateTypes()
{
    cTerrainDistributeInfo* pInfo = mDistInfo;
    if (!pInfo)
        return 0;
    int n = pInfo->mLevelSize;
    if (n == 0)
        return (cDistGrid*)pInfo;

    int blocks = (n + ((n >> 31) & 0xf)) >> 4;
    uint32_t changed = 0;
    int offset = 0;
    int k = 0;
    uint32_t bit = 0;
    do {
        int v = *(int*)((char*)mDistInfo + offset + 0x48);
        if (mTypeMods[k] != v) {
            mTypeMods[k] = v;
            changed |= 1u << bit;
        }
        v = *(int*)((char*)mDistInfo + offset + 0x88);
        if (mTypeMods[k + 1] != v) {
            mTypeMods[k + 1] = v;
            changed |= 1u << (bit + 1);
        }
        v = *(int*)((char*)mDistInfo + offset + 0xc8);
        if (mTypeMods[k + 2] != v) {
            mTypeMods[k + 2] = v;
            changed |= 1u << (bit + 2);
        }
        offset += 0xc0;
        bit += 3;
        k += 3;
    } while (offset < 0x240);

    if (blocks < 1) {
        int per = 0x10 / n;
        int faceOffset = 0;
        int face = 0;
        do {
            cCell* pCells = mCellData + (mFaceSize * face + mLevelOffsets[4]);
            const uint16_t* pTypes = mDistInfo->mpTypes + faceOffset / 2;
            int y = 0;
            do {
                int x = 0;
                do {
                    for (int i = 0; i < per; i++) {
                        for (int j = 0; j < per; j++) {
                            uint32_t a = (uint32_t)(uint8_t)(per * x + j);
                            uint32_t b = (uint32_t)(uint8_t)(per * y + i);
                            unsigned idx = (((g_swizzle[a >> 4] | (unsigned)g_swizzle[b >> 4] * 2)
                                             << 7 | g_swizzle[b & 0xf]) * 2 | g_swizzle[a & 0xf]);
                            cCell* pCell = pCells + idx;
                            uint16_t v = *pTypes;
                            pCell->mTypeMask = v;
                            if ((v & (uint16_t)changed) != 0)
                                pCell->mTypeMask = v | 0x8000;
                        }
                    }
                    *(uint16_t*)pTypes &= 0x7fff;
                    pTypes++;
                } while (++x < n);
            } while (++y < n);
            UpdateTypesUp(3, face, 0, 0, 0x10, 0x10);
            faceOffset += n * n * 2;
            face++;
        } while (face < 6);
    } else {
        int face = 0;
        int faceOffset = 0;
        do {
            const uint16_t* pFace = mDistInfo->mpTypes + faceOffset / 2;
            cCell* pCells = mCellData + (mFaceSize * face + mLevelOffsets[4]);
            int y = 0;
            do {
                const uint16_t* pRow = pFace;
                int x = 0;
                do {
                    unsigned idx = (((g_swizzle[x >> 4] | (unsigned)g_swizzle[y >> 4] * 2)
                                     << 7 | g_swizzle[y & 0xf]) * 2 | g_swizzle[x & 0xf]);
                    cCell* pCell = pCells + idx;
                    pCell->mTypeMask = 0;
                    const uint16_t* p = pRow;
                    for (int r = 0; r < blocks; r++) {
                        for (int c = 0; c < blocks; c++) {
                            pCell->mTypeMask |= p[c];
                            ((uint16_t*)p)[c] &= 0x7fff;
                        }
                        p += n;
                    }
                    if ((pCell->mTypeMask & changed) != 0)
                        pCell->mTypeMask |= 0x8000;
                    pRow += blocks;
                    x++;
                } while (x < 0x10);
                pFace += n * blocks;
                y++;
            } while (y < 0x10);
            UpdateTypesUp(3, face, 0, 0, 0x10, 0x10);
            faceOffset += n * n * 2;
            face++;
        } while (face < 6);
    }
    mPadA4 = mDistInfo->mModCount;
    return this;
}

// @ 0x00f65ec0
void SP::cDistGrid::UpdateTypesWithDebugValues()
{
    for (int face = 0; face < 6; face++) {
        cCell* pCells = mCellData + (mFaceSize * face + mLevelOffsets[4]);
        int y = 0;
        do {
            const uint8_t* high = &g_swizzle[y >> 4];
            const uint8_t* low = &g_swizzle[y & 0xf];
            int x = 0;
            do {
                unsigned idx = (((g_swizzle[x >> 4] | (unsigned)high[0] * 2) << 7 | low[0]) * 2 |
                                g_swizzle[x & 0xf]);
                pCells[idx].mTypeMask = (unsigned short)(1 << ((x + y) & 0x1f));
                ++x;
            } while (x < 0x10);
            ++y;
        } while (y < 0x10);
        UpdateTypesUp(3, face, 0, 0, 0x10, 0x10);
    }
}

// @ 0x00f65fa0
void SP::cTerrainDistributeEffect::Start(int hardStart)
{
    if ((Flags() & 1) == 0 && mDistGrid != 0) {
        Flags() |= 1;
        bool debugValues = ((mDesc->mFlags >> 1) & 1) != 0;
        if (debugValues)
            mDistGrid->UpdateTypesWithDebugValues();
        else
            mDistGrid->UpdateTypes();
    }
}
