// Slice s004ab690 — SP::cSPEditorModel: ctor, teardown and block-search helpers.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (editor /Od module, no /EHsc).
#include "types.h"

// ------------------------------------------------------------------ math types
struct Vector3T {                                                        // rw::math::fpu::Vector3Template<float,0>
    float x, y, z;
    Vector3T() {}
    Vector3T(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
};

struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : Vector3T(ax, ay, az) {}
    cSPVector3& operator=(const Vector3T& v) { Vector3T::operator=(v); return *this; }
};

cSPVector3 operator-(const Vector3T& a, const Vector3T& b);              // 0x0041db10
cSPVector3 operator*(const Vector3T& a, const float& s);                 // 0x0041dca0
cSPVector3 operator/(const Vector3T& a, const float& s);                 // 0x00453880
cSPVector3& operator+=(cSPVector3& a, const cSPVector3& b);             // 0x0041ddb0
float VectorLength(const Vector3T& v);                                   // 0x0040ae50
// Removes the component of v along n: v - (v.n) n   (cdecl, sret)
Vector3T ProjectOffAxis(const Vector3T& v, const Vector3T& n);          // 0x004909d0
cSPVector3 ProjectOffAxis(const cSPVector3& v, const cSPVector3& n);

extern const cSPVector3 kZeroVec;                                        // 0x015d6a28

struct cSPBoundingBox {
    cSPVector3 mMin;
    cSPVector3 mMax;
    cSPVector3 GetCorner(uint32_t mask) const;                           // 0x0043f290
};

struct cSPColorRGB : Vector3T {                                          // user-provided empty ctor
    cSPColorRGB() {}
};

// eastl::gEmptyString16 (0x01667bac) and the default skin colour (three floats at 0x015d68e8).
extern wchar_t gEmptyString16[];                                         // 0x01667bac
extern cSPColorRGB gDefaultSkinColor;                                    // 0x015d68e8

// ------------------------------------------------------------------ eastl subset
namespace eastl {

// eastl::sp_vector_allocator is an empty tag; only its out-of-line copy ctor survives (0x00429360).
struct sp_vector_allocator {
    sp_vector_allocator() {}
    sp_vector_allocator(const sp_vector_allocator&);                     // 0x00429360
};

// eastl::basic_string<wchar_t> in the retail 0x10 layout (begin/end/capacity + 1-byte allocator).
template <typename T, typename A = sp_vector_allocator>
struct basic_string {
    T* mpBegin;                                                          // +0x00
    T* mpEnd;                                                            // +0x04
    T* mpCapacity;                                                       // +0x08
    A mAllocator;                                                        // +0x0c
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0)
    {
        mpBegin = gEmptyString16;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};

// eastl::vector in the retail 0x14 layout: begin/end/capacity + an 8-byte allocator slot.
template <typename T, typename A = sp_vector_allocator>
struct vector {
    T* mpBegin;                                                          // +0x00
    T* mpEnd;                                                            // +0x04
    T* mpCapacity;                                                       // +0x08
    A mAllocator;                                                        // +0x0c
    unsigned char mAllocatorPad[8 - sizeof(A)];
    vector(const A& a = A()) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int n) { return mpBegin[n]; }
};

}  // namespace eastl

// The bbox-override container: only its three pointers are zeroed by the ctor (no allocator copy).
struct BBoxVector {
    void* mpBegin;                                                       // +0x00
    void* mpEnd;                                                         // +0x04
    void* mpCapacity;                                                    // +0x08
    unsigned char mAllocatorPad[8];
    BBoxVector() { mpBegin = 0; mpEnd = 0; mpCapacity = 0; }
};

// ------------------------------------------------------------------ EA base types
namespace EA { namespace ResourceMan {
struct Key {
    unsigned int mInstance;                                              // +0x00
    unsigned int mType;                                                  // +0x04
    unsigned int mGroup;                                                 // +0x08
    Key() { mInstance = 0; mType = 0; mGroup = 0; }
};
}}

namespace EA {

// The intrusive reference-count base (vtable at this+0x04, count at +0x08).
template <typename T>
class RefCountTemplate {
 public:
    T mCount;
    RefCountTemplate() : mCount(0) {}
    virtual ~RefCountTemplate();
};

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() { mpObject = 0; if (mpObject != 0) mpObject->AddRef(); }
    operator T*() const { return mpObject; }
};

}  // namespace EA

// ------------------------------------------------------------------ SP types
namespace SP {

class cSPEditorModel;

class cSPEditorPhysicsWorld {
 public:
    void* mpVtbl;                                                        // +0x00
    int mRefCount;                                                       // +0x04
    void AddRef() { int c = mRefCount + 1; mRefCount = mRefCount + 1; (void)c; }
};

class cSPEditorBlock {
 public:
    char pad0[0x48];
    Vector3T mPosition;                                                  // +0x48
    char pad1[0x33c - 0x54];
    cSPEditorBlock* mLink33c;                                            // +0x33c
    char pad2[0x3e0 - 0x340];
    cSPEditorBlock* mPartner;                                            // +0x3e0
    char pad3[0xdc8 - 0x3e4];
    uint32_t mFlags[4];                                                  // +0xdc8

    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
    const Vector3T& GetPosition() { return mPosition; }
    cSPEditorBlock* GetPartner() { return mPartner; }
    void sub_435be0(cSPEditorModel* model);                              // 0x00435be0 (thiscall on the block, one stack arg)
    void sub_449ed0();                                                   // 0x00449ed0
    bool IsInChain(cSPEditorBlock* other);                               // 0x0044a9a0
    cSPBoundingBox GetBBox(int type, bool a, bool b);                    // 0x0044ae00
};

// The list at model+0x18 stores refcounted wrappers: *it converts to the block pointer.
template <class T> struct BlockRef {
    T* mpObject;
    BlockRef() {}
    BlockRef(T* p) : mpObject(p) {}
    operator T*() const { return mpObject; }
};

struct EditorBlockList {                                                 // the block vector object embedded at model+0x18
    void sub_4541f0(void* slot);                                         // 0x004541f0 (thiscall on the vector, one stack arg)
};

// Only the vtable prefix is needed: the code dispatches slots +4 and +8 on the block.
struct cSPEditorBlockVtbl {
    virtual void vfn0();
    virtual void vfn1();                                                 // +0x04
    virtual void vfn2();                                                 // +0x08
};

// base 0: the name-provider interface (this+0x00)
class cISPEditorNameProvider {
 public:
    cISPEditorNameProvider() {}
    virtual void SetName(wchar_t const*);
    virtual wchar_t const* GetName() const;
    virtual void SetDescription(wchar_t const*);
    virtual wchar_t const* GetDescription() const;
    virtual void slot4();
    virtual void slot5();
    virtual ~cISPEditorNameProvider();
};

// ---- externals the teardown / search helpers call (thiscall = __fastcall on the first arg)
extern void* g_vtbl_model_a;                                             // 0x013ef624
extern void* g_vtbl_model_b;                                             // 0x013ef620
extern void* g_vtbl_ability;                                             // 0x013ef094

extern void __fastcall FUN_004ad330(void* self);                         // 0x004ad330
extern void __fastcall FUN_004fd940(void* self);                         // 0x004fd940
extern void __fastcall WString_FreeBuffer(void* str);                    // 0x004237d0
extern void __fastcall FUN_453540_Release(void* obj);                    // 0x00453540
extern void __fastcall FUN_004453eb0_vector_dtor(void* vec);             // 0x004453eb0
extern double FUN_004a5bd0(cSPEditorBlock* b);                           // 0x004a5bd0
extern void* FUN_0041db10(void* out, void* p, void* arg);                // 0x0041db10
extern double FUN_0040ae50(void* v);                                     // 0x0040ae50
extern float g_floatMax;                                                 // 0x013ef5c8

class cSPEditorModel : public cISPEditorNameProvider, public EA::RefCountTemplate<int> {
 public:
    cSPEditorModel();                                                    // 0x004ab690
    void ModelTeardown();                                                // 0x004aba00
    void AddBlock(cSPEditorBlock* block, bool flag);                     // 0x004abaf0
    cSPVector3 GetNearestBlockPointToPoint(cSPVector3 point, cSPEditorBlock* ignoreBlock,
                                           bool usePositions, bool flatten, cSPVector3 axis); // 0x004abbc0
    cSPVector3 GetBestBlockPointBasedOnDistance(cSPVector3 point, cSPEditorBlock* ignoreBlock, cSPVector3 axis,
                                                bool findNearest, bool usePositions, bool flatten, bool useChain); // 0x004abc50
    cSPEditorBlock* FindNearestFlag7Block(cSPVector3 point);              // 0x004ac480
    void sub_4adfc0(int v);                                             // 0x004adfc0 (thiscall on the model, one stack arg)

    EA::ResourceMan::Key mKey;                                           // +0x0c
    eastl::vector<EA::AutoRefCount<cSPEditorBlock>, eastl::sp_vector_allocator> mBlockList; // +0x18
    bool mbAllBlocksLoaded;                                              // +0x2c
    EA::AutoRefCount<cSPEditorPhysicsWorld> mPhysicsWorld;               // +0x30
    bool mUseDynamics;                                                   // +0x34
    float mBounds;                                                       // +0x38
    float mFeetBounds;                                                   // +0x3c
    float mMinHeight;                                                    // +0x40
    float mMaxHeight;                                                    // +0x44
    float mMinimumLeglessCreatureHeight;                                 // +0x48
    bool mShowHiddenHandles;                                             // +0x4c
    bool mShowBoneLengthHandles;                                         // +0x4d
    bool mUseBoundsForDelete;                                            // +0x4e
    bool mUsingSymmetry;                                                 // +0x4f
    bool mSkinNeedsUpdating;                                             // +0x50
    bool mChanged;                                                       // +0x51
    unsigned int mModelTranslationOptions;                               // +0x54
    int mModelType;                                                      // +0x58
    eastl::basic_string<wchar_t> mName;                                  // +0x5c
    eastl::basic_string<wchar_t> mDescription;                           // +0x6c
    eastl::basic_string<wchar_t> mCleanName;                             // +0x7c
    unsigned int mSkinEffects[3];                                        // +0x8c
    unsigned int mSkinEffectSeeds[3];                                    // +0x98
    cSPColorRGB mSkinColors[3];                                          // +0xa4
    BBoxVector mBBoxesOverride;                                          // +0xc8
};

// @ 0x004ab690
cSPEditorModel::cSPEditorModel()
    : mbAllBlocksLoaded(false),
      mUseDynamics(false),
      mBounds(0.0f),
      mFeetBounds(0.0f),
      mMinHeight(-2.0f),
      mMaxHeight(2.0f),
      mMinimumLeglessCreatureHeight(0.0f),
      mShowHiddenHandles(false),
      mShowBoneLengthHandles(false),
      mUseBoundsForDelete(true),
      mUsingSymmetry(false),
      mSkinNeedsUpdating(false),
      mChanged(false),
      mModelTranslationOptions(0),
      mModelType(0)
{
    mName.clear();
    mDescription.clear();
    for (int i = 0; i < 3; ++i) {
        mSkinColors[i] = gDefaultSkinColor;
        mSkinEffects[i] = 0;
        mSkinEffectSeeds[i] = 0x4d2;
    }
}

// @ 0x004aba00
void cSPEditorModel::ModelTeardown()
{
    *(void**)this = &g_vtbl_model_a;
    *(void**)((char*)this + 4) = &g_vtbl_model_b;
    FUN_004ad330(this);
    char* v = (char*)this + 0xc8;
    for (uint32_t i = *(uint32_t*)v; i < *(uint32_t*)(v + 4); i += 0x18) {
    }
    FUN_004fd940(v);
    WString_FreeBuffer((char*)this + 0x7c);
    WString_FreeBuffer((char*)this + 0x6c);
    WString_FreeBuffer((char*)this + 0x5c);
    void** rc = (void**)((char*)this + 0x30);
    if (*rc != 0) {
        FUN_453540_Release(*rc);
    }
    FUN_004453eb0_vector_dtor((char*)this + 0x18);
    *(void**)((char*)this + 4) = &g_vtbl_ability;
}

// @ 0x004abaf0
void cSPEditorModel::AddBlock(cSPEditorBlock* block, bool flag)
{
    (void)flag;
    if (block == 0)
        return;
    BlockRef<cSPEditorBlock>* last = *(BlockRef<cSPEditorBlock>**)((char*)this + 0x1c);
    BlockRef<cSPEditorBlock>* first = *(BlockRef<cSPEditorBlock>**)((char*)this + 0x18);
    BlockRef<cSPEditorBlock>* it = first;
    while (it != last && *it != block)
        ++it;
    if (it != *(BlockRef<cSPEditorBlock>**)((char*)this + 0x1c))
        return;
    block->sub_435be0(this);
    block->sub_449ed0();
    cSPEditorBlock* raw = block;
    BlockRef<cSPEditorBlock> local = raw;
    if (local.mpObject != 0)
        ((cSPEditorBlockVtbl*)local.mpObject)->vfn1();
    ((EditorBlockList*)((char*)this + 0x18))->sub_4541f0(&local);
    if (local.mpObject != 0)
        ((cSPEditorBlockVtbl*)local.mpObject)->vfn2();
    this->sub_4adfc0(1);
}

// @ 0x004abbc0
cSPVector3 cSPEditorModel::GetNearestBlockPointToPoint(cSPVector3 point, cSPEditorBlock* ignoreBlock,
                                                      bool usePositions, bool flatten, cSPVector3 axis)
{
    return GetBestBlockPointBasedOnDistance(point, ignoreBlock, axis, true, usePositions, flatten, true);
}

// @ 0x004abc50
// Scans every block (skipping ignoreBlock, its partner and, optionally, everything reachable through
// ignoreBlock's chain) and returns the block position (point mode) or the bbox-weighted contact point
// (box mode) that is closest to / farthest from `point`.
cSPVector3 cSPEditorModel::GetBestBlockPointBasedOnDistance(cSPVector3 point, cSPEditorBlock* ignoreBlock,
                                                            cSPVector3 axis, bool findNearest, bool usePositions,
                                                            bool flatten, bool useChain)
{
    cSPVector3 target(flatten ? ProjectOffAxis(point, axis) : point);
    float best = findNearest ? 1000000.0f : -1000000.0f;
    cSPVector3 bestPos(-1.0f, -1.0f, -1.0f);

    for (int i = 0, count = mBlockList.size(); i < count; i++) {
        cSPEditorBlock* blk = mBlockList[i];
        bool skip = false;
        if (useChain) {
            skip = ignoreBlock ? ignoreBlock->IsInChain(blk) : false;
            if (!skip) {
                if (ignoreBlock->GetPartner())
                    skip = ignoreBlock->GetPartner()->IsInChain(blk);
            }
        } else {
            skip = ignoreBlock == blk;
            if (!skip) {
                if (ignoreBlock->GetPartner())
                    skip = ignoreBlock->GetPartner() == blk;
            }
        }
        if (!skip) {
            if (usePositions) {
                Vector3T pos(blk->GetPosition());
                Vector3T posT(flatten ? ProjectOffAxis(pos, axis) : pos);
                float dist = VectorLength(posT - target);
                if (findNearest) {
                    if (best > dist) { best = dist; bestPos = pos; }
                } else {
                    if (dist > best) { best = dist; bestPos = pos; }
                }
            } else {
                cSPBoundingBox box = blk->GetBBox(0, true, false);
                float totalWeight = 0.0f;
                Vector3T center(blk->GetPosition());
                if (flatten)
                    center = ProjectOffAxis(center, axis);
                Vector3T toCenter(target - center);
                Vector3T extent(box.mMin - box.mMax);
                float reach = VectorLength(toCenter) + VectorLength(extent);
                float weights[8];
                for (int k = 0; k < 8; k++) {
                    cSPVector3 corner = box.GetCorner(k);
                    cSPVector3 cornerT(flatten ? ProjectOffAxis(corner, axis) : corner);
                    Vector3T rel(corner - center);
                    float w = -1.0f;
                    if (rel.x * toCenter.x + rel.y * toCenter.y + rel.z * toCenter.z > 0.0f) {
                        w = reach - VectorLength(cornerT - target);
                        totalWeight += w;
                    }
                    weights[k] = w;
                }
                cSPVector3 acc(kZeroVec);
                for (int k = 0; k < 8; k++) {
                    if (weights[k] > 0.0f) {
                        acc += box.GetCorner(k) * weights[k] / totalWeight;
                    }
                }
                cSPVector3 off = target - acc;
                float dist = VectorLength(off);
                if (findNearest) {
                    if (best > dist) { best = dist; bestPos = acc; }
                } else {
                    if (dist > best) { best = dist; bestPos = acc; }
                }
            }
        }
    }
    return bestPos;
}

// @ 0x004ac480
cSPEditorBlock* cSPEditorModel::FindNearestFlag7Block(cSPVector3 point)
{
    float best = g_floatMax;
    cSPEditorBlock* result = 0;
    int count = (int)(*(uint32_t*)((char*)this + 0x1c) - *(uint32_t*)((char*)this + 0x18)) >> 2;
    for (int i = 0; i < count; ++i) {
        cSPEditorBlock* b = *(cSPEditorBlock**)(*(uint32_t*)((char*)this + 0x18) + i * 4);
        if (b->IsFlagSet(7)) {
            float d = (float)FUN_004a5bd0(b);
            cSPVector3 rel = b->GetPosition() - point;
            float len = (float)FUN_0040ae50(&rel);
            float delta = len - d;
            if (delta < best) {
                result = b;
                best = delta;
            }
        }
    }
    return result;
}

}  // namespace SP
