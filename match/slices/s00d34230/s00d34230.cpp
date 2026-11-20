// @ 0x00d34230  SP::cCreatureModeInputStrategy::CleanUpCreatureHitBoxes
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Drops every creature hit box: for the box at the front of mCreatureHitBoxes the
// owner is released, the model's "attached" bit is cleared and the world is told to
// update it with no owner; the front element is then erased (the remaining elements
// shift down through eastl's out-of-line copy for AutoRefCount elements) and the
// duplicated tail element is destroyed, dropping its reference.
#include "types.h"
#include <stddef.h>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
#define PV16 PV8 PV8
#define PV32 PV16 PV16
#define VSLOT(p, off) (*(void***)(p))[(off) / 4]

struct Vector3 { float x, y, z; };
struct Matrix3 { float m[9]; };

struct Transform {
    uint16_t mFlags;      // 0x00
    uint16_t mnChanges;   // 0x02
    Vector3  mOffset;     // 0x04
    float    mScale;      // 0x10
    Matrix3  mRotation;   // 0x14
};

// Game data object a model can be owned by (Graphics::Model::mpOwner).
class cGameData {
public:
    virtual int AddRef();     // 0x00
    virtual int Release();    // 0x04
};

// EA::AutoRefCount<cGameData>
struct cGameDataPtr {
    cGameData* mpObject;
    cGameDataPtr& operator=(cGameData* pObject)
    {
        if (pObject != mpObject) {
            cGameData* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

struct cMWModel;

// Graphics::IModelWorld, the slots used here.
class IModelWorld {
public:
    PV32 PV16 PV8            // 0x000 - 0x160
    virtual void UpdateModel(cMWModel* model, bool b);          // 0x16c
    virtual void ReleaseModel(cMWModel* model, uint8_t b);      // 0x170
};

// Graphics::Model (cMWModel).
struct cMWModel {
    IModelWorld* mpWorld;      // 0x00
    uint32_t     mFlags;       // 0x04
    Transform    mTransform;   // 0x08
    int32_t      mRefCount;    // 0x40
    uint8_t      mPad44[0x60 - 0x44];
    uint32_t     mType;        // 0x60
    cGameDataPtr mpOwner;      // 0x64
    uint8_t      mPad68[0x6c - 0x68];
    float        mDefaultBoundingRadius;   // 0x6c

    void Release()
    {
        if (mRefCount > 1)
            --mRefCount;
        else
            ((void(__thiscall*)(IModelWorld*, cMWModel*, uint8_t))VSLOT(mpWorld, 0x170))(
                mpWorld, this, (uint8_t)((mFlags >> 31) & 1));
    }
};

// EA::AutoRefCount<cMWModel>
struct cMWModelPtr {
    cMWModel* mpObject;
    cMWModel* get() const { return mpObject; }
    ~cMWModelPtr()
    {
        if (mpObject)
            mpObject->Release();
    }
};

// eastl::vector<cMWModelPtr, sp_vector_allocator>
struct MWModelVector {
    cMWModelPtr* mpBegin;      // 0x58
    cMWModelPtr* mpEnd;        // 0x5c
    cMWModelPtr* mpCapacity;   // 0x60
};

// eastl::copy_impl::do_copy for this element type.
cMWModelPtr* do_copy(cMWModelPtr* first, cMWModelPtr* last, cMWModelPtr* result);   // 0x005f4e10

namespace SP {
class cCreatureModeInputStrategy;
}

class SP::cCreatureModeInputStrategy {
public:
    uint8_t       mPad00[0x58];
    MWModelVector mCreatureHitBoxes;    // 0x58

    void CleanUpCreatureHitBoxes();      // 0x00d34230
};

namespace SP {

void cCreatureModeInputStrategy::CleanUpCreatureHitBoxes()
{
    cMWModelPtr* it = mCreatureHitBoxes.mpBegin;

    while (it != mCreatureHitBoxes.mpEnd) {
        cMWModel* model = it->get();
        if (model) {
            model->mpOwner = 0;
            model->mFlags &= ~1u;
            ((void(__thiscall*)(IModelWorld*, cMWModel*, int))VSLOT(model->mpWorld, 0x16c))(
                model->mpWorld, model, 0);
        }

        // eastl::vector<cMWModelPtr>::erase(it)
        if (it + 1 < mCreatureHitBoxes.mpEnd)
            do_copy(it + 1, mCreatureHitBoxes.mpEnd, it);
        mCreatureHitBoxes.mpEnd -= 1;
        mCreatureHitBoxes.mpEnd->~cMWModelPtr();
    }
}

}  // namespace SP
