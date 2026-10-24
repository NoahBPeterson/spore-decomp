// Slice s00d34f90 -- SP::cCreatureModeInputStrategy substate setup helpers.
//
// 0x00d35030  cCreatureModeInputStrategy::InitSubstate()
//               cleans the old pick boxes, gets the creature model world from the model
//               manager, resizes the hit-box pool to 5 and (re)creates/normalises every
//               empty hit-box model, then releases the world.
// 0x00d34f90  cCreatureModeInputStrategy::FUN_00d34f90(int)
//               per-frame substate refresh: when the strategy is active, rebuild the pick
//               boxes and hand the input manager + argument to FUN_00d32df0.
// 0x00d34fc0  FUN_00d34fc0(first, last, Compare7)
//               thunk that forwards an eastl sort call (and its by-value compare functor)
//               straight to FUN_00d340d0.
//
// The whole 0x00d34xxx/0x00d35xxx block belongs to the creature-mode input strategy; the
// cMWModel / Transform layout is shared with the sibling slice s00d342d0
// (UpdateCreaturePickBoxes).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// vtable plumbing
// ---------------------------------------------------------------------------
struct Vtbl { void* mSlots[0x200 / 4]; };

typedef void* (__thiscall *VFn_pi)(void*, int);
typedef void* (__thiscall *VFn_piii)(void*, int, int, int);
typedef void  (__thiscall *VFn_v)(void*);
typedef void  (__thiscall *VFn_vi)(void*, int);
typedef void  (__thiscall *VFn_vpi)(void*, void*, int);
typedef void  (__thiscall *VFn_vvc)(void*, void*, uint8_t);

#define VSLOT(o, n) (((Vtbl*)*(void**)(o))->mSlots[(n) / 4])

// ---------------------------------------------------------------------------
// math types + engine singletons (addresses are relocation-masked by the checker)
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) { x = v.x; y = v.y; z = v.z; }
};
struct Matrix3 { float m[9]; };
struct Quaternion {
    float x, y, z, w;
    Quaternion() {}
    Quaternion(const Quaternion& q) { x = q.x; y = q.y; z = q.z; w = q.w; }
};

extern Vector3 sZeroVector;       // 0x0169e17c  Vector3::ZERO
extern Matrix3 sIdentityMatrix3;  // 0x0169e1cc  Matrix3::IDENTITY
extern int     g_modelCreateArg;  // 0x0169e1c8  third model-create argument

struct IGameInputManager;
IGameInputManager* __cdecl GameInputManager();     // 0x00b3d250
void*              __cdecl ModelManager();         // 0x0067dd80

struct IModelWorld;

// Transform embedded at cMWModel + 0x08.
struct Transform {
    uint16_t mFlags;      // 0x00
    uint16_t mnChanges;   // 0x02
    Vector3  mOffset;     // 0x04
    float    mScale;      // 0x10
    Matrix3  mRotation;   // 0x14
};

// Graphics::Model (cMWModel).
struct cMWModel {
    IModelWorld* mpWorld;     // 0x00
    uint32_t     mFlags;      // 0x04
    Transform    mTransform;  // 0x08
    int32_t      mRefCount;   // 0x40
    uint8_t      mPad44[0x60 - 0x44];
    uint32_t     mType;       // 0x60
    uint8_t      mPad64[0x6c - 0x64];
    float        mDefaultBoundingRadius;   // 0x6c

    void AddRef() { mRefCount++; }
    void Release()
    {
        if (mRefCount > 1)
            --mRefCount;
        else
            ((VFn_vvc)VSLOT(mpWorld, 0x170))(mpWorld, this, (uint8_t)((mFlags >> 31) & 1));
    }
};

// EA::AutoRefCount<Graphics::Model>
struct cMWModelPtr {
    cMWModel* mpObject;
    cMWModel* get() const { return mpObject; }
    cMWModelPtr& operator=(cMWModel* pObject)
    {
        if (pObject != mpObject) {
            cMWModel* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

// eastl::vector<cMWModelPtr, sp_vector_allocator>
struct MWModelVector {
    cMWModelPtr* mpBegin;     // 0x00
    cMWModelPtr* mpEnd;       // 0x04
    cMWModelPtr* mpCapacity;  // 0x08
    void resize(size_t n);    // 0x00473270
};

class cCreatureModeInputStrategy {
public:
    uint8_t        mPad00[0x54];            // 0x000
    uint8_t        mbActive;                // 0x054  substate active flag
    uint8_t        mPad55[0x58 - 0x55];     // 0x055
    MWModelVector  mCreatureHitBoxes;       // 0x058

    void UpdateCreaturePickBoxes();                        // 0x00d342d0
    void CleanUpCreatureHitBoxes();                        // 0x00d34230
    void FUN_00d32df0(IGameInputManager* pInput, int arg); // 0x00d32df0

    void FUN_00d34f90(int arg);
    void InitSubstate();
};

// ---------------------------------------------------------------------------
// eastl sort compare functor (a Vector3 + a Quaternion = 7 floats, 0x1c bytes)
// and the helper entry points that forward it by value.
// ---------------------------------------------------------------------------
struct Compare7 {
    Vector3    mPosition;
    Quaternion mOrientation;
};

void FUN_00d340d0(void* first, void* last, Compare7 compare);   // 0x00d340d0

// ---------------------------------------------------------------------------
// @ 0x00d34f90  cCreatureModeInputStrategy::FUN_00d34f90
// ---------------------------------------------------------------------------
void cCreatureModeInputStrategy::FUN_00d34f90(int arg)
{
    IGameInputManager* pInput = GameInputManager();
    if (pInput) {
        if (mbActive)
            UpdateCreaturePickBoxes();
        FUN_00d32df0(pInput, arg);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00d34fc0  FUN_00d34fc0
// ---------------------------------------------------------------------------
void FUN_00d34fc0(void* first, void* last, Compare7 compare)
{
    FUN_00d340d0(first, last, compare);
}

// ---------------------------------------------------------------------------
// @ 0x00d35030  cCreatureModeInputStrategy::InitSubstate
// ---------------------------------------------------------------------------
void cCreatureModeInputStrategy::InitSubstate()
{
    MWModelVector& hitBoxes = mCreatureHitBoxes;

    if (hitBoxes.mpEnd - hitBoxes.mpBegin)
        CleanUpCreatureHitBoxes();

    void* mm = ModelManager();
    void* pWorld = ((VFn_pi)VSLOT(mm, 0x1c))(mm, 0xeb9968);
    if (pWorld)
        ((VFn_v)VSLOT(pWorld, 0))(pWorld);

    hitBoxes.resize(5);

    size_t count = hitBoxes.mpEnd - hitBoxes.mpBegin;
    for (size_t i = 0; i < count; i++) {
        if (hitBoxes.mpBegin[i].get() == 0) {
            hitBoxes.mpBegin[i] =
                (cMWModel*)((VFn_piii)VSLOT(pWorld, 0xc))(pWorld, 0x2e81370,
                                                          g_modelCreateArg, 0x10);
            cMWModel* model = hitBoxes.mpBegin[i].get();
            model->mTransform.mRotation = sIdentityMatrix3;
            model->mTransform.mScale = 1.0f;
            model->mTransform.mOffset = sZeroVector;
            model->mTransform.mFlags = 0;
            model->mTransform.mnChanges = 0;
            model->mFlags &= ~1;
            ((VFn_vpi)VSLOT(model->mpWorld, 0x16c))(model->mpWorld, model, 0);
        }
    }

    if (pWorld)
        ((VFn_v)VSLOT(pWorld, 4))(pWorld);
}