// Slice s00448380: SP::cSPEditorBlock effects-mask, symmetry and deform-handle helpers.
// Object: SPBake/SPEditorBlock.obj
// Flags: /Od /Ob1 /Oi /MD /EHsc /TP /arch:SSE /fp:fast /Gy /GS-
#include "types.h"

namespace eastl {
template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
};
}

namespace EA {
// Intrusive refcounted pointer; refcount/Release live on the pointee (cMWModel::mRefCount
// at +0x40, out-of-line Release 0x0040f360) or are virtual (cSPTransformOps/cSPEditorBlock
// expose AddRef/Release in their vtables).
template <class T>
struct AutoRefCount {
    T* mpObject;
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount& operator=(T* p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (old) old->Release();
        }
        return *this;
    }
};
}

namespace SP {

struct cSPEditorBlock;
struct cMWModel;
struct cIModelWorld;
struct cPropertyList;
struct cSPEditorHandleDeform;
struct cSPEditorModel;
struct cSPTransformOps;
struct cModelManager;

using EA::AutoRefCount;
using eastl::bitset;

// ---- small value type (user copy ctor -> x87 component copies at /Od)
struct cSPVector3 {
    float x, y, z;
    cSPVector3() {}
    cSPVector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    cSPVector3(const cSPVector3& v) { x = v.x; y = v.y; z = v.z; }
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};

struct Key3 { int a, b, c; };

// ---- transform record subobject carried at +0x08 of a model and a block
struct cSPTransformOps {
    virtual void AddRef();                      // vtable +0x00 (slot 0)
    virtual void Release();                     // vtable +0x04 (slot 1)
    cSPTransformOps* Assign(const void* p);     // 0x00537dc0
};

// ---- the model created by the effects mask (no vptr: +0x00 is its world back-pointer)
struct cMWModel {
    cIModelWorld* mpWorld;                      // +0x00
    char pad04[4];
    cSPTransformOps mXformOps;                  // +0x08
    char pad0c[0x40 - 0x0c];
    int mRefCount;                              // +0x40
    uint32_t mGroups[2];                        // +0x44
    cSPVector3 mOffset;                         // +0x4c
    char pad58[0x64 - 0x58];
    AutoRefCount<cSPTransformOps> mOwner;       // +0x64
    void AddRef() { mRefCount++; }
    void Release();                             // 0x0040f360
};

// ---- model/group index manager
struct cModelManager {
    virtual void mm0();  virtual void mm1();  virtual void mm2();  virtual void mm3();
    virtual void mm4();  virtual void mm5();  virtual void mm6();  virtual void mm7();
    virtual void mm8();  virtual void mm9();
    virtual uint32_t GetGroupIndex(uint32_t key, int flag);   // vtable +0x28 (slot 10)
};
cModelManager* GetModelManager();               // 0x0067dd80

// ---- editor model (symmetry + scale queries)
struct cSPEditorModel {
    float GetScale();                           // 0x004adaa0
    bool UsingSymmetry() const;                 // 0x004adc40
};

// ---- deform handle owned by the block
struct cSPEditorHandleDeform {
    char pad0[0x8c];
    void* mHandleID;                            // +0x8c
    char pad90[0x180 - 0x90];
    float mDelta;                               // +0x180
    bool RecordHandlePosition(char flag);       // 0x00480e90
    void Update();                              // 0x00482670
};

// ---- child-block list at +0x340
struct BlockList {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>* mpCapacity;
    int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorBlock>& operator[](int i) { return mpBegin[i]; }
    bool empty();                               // 0x00526430
};

// ---- deform-handle list at +0x6cc
struct HandleList {
    AutoRefCount<cSPEditorHandleDeform>* mpBegin;
    AutoRefCount<cSPEditorHandleDeform>* mpEnd;
    AutoRefCount<cSPEditorHandleDeform>* mpCapacity;
    int mAllocator;
    int size() const { return (int)(mpEnd - mpBegin); }
    AutoRefCount<cSPEditorHandleDeform>& operator[](int i) { return mpBegin[i]; }
};

void sub_458f60(void* a, void* b, Key3 key, int c);   // 0x00458f60

// ---- model world interface (only the slots this slice calls are named)
struct cIModelWorld {
    virtual void w0();  virtual void w1();  virtual void w2();
    virtual cMWModel* CreateEffectsMask(unsigned instance, unsigned group, int kind);   // +0x0c (slot 3)
    virtual void w4();  virtual void w5();  virtual void w6();  virtual void w7();
    virtual void w8();  virtual void w9();  virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21();
    virtual void SetEffectsModel(cMWModel* model);                                      // +0x58 (slot 22)
    virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26();
    virtual void w27(); virtual void w28();
    virtual void SetModelHandleValue(cMWModel* model, void* id, float value, int flag); // +0x74 (slot 29)
    virtual void w30(); virtual void w31();
    virtual void GetModelHandleRange(cMWModel* model, void* id, float* lo, float* hi, int flag);   // +0x80 (slot 32)
    virtual void w33(); virtual void w34(); virtual void w35(); virtual void w36();
    virtual void w37(); virtual void w38(); virtual void w39(); virtual void w40();
    virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44();
    virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48();
    virtual void w49(); virtual void w50(); virtual void w51(); virtual void w52();
    virtual void w53(); virtual void w54(); virtual void w55(); virtual void w56();
    virtual void w57(); virtual void w58(); virtual void w59(); virtual void w60();
    virtual void w61(); virtual void w62(); virtual void w63(); virtual void w64();
    virtual void w65(); virtual void w66(); virtual void w67(); virtual void w68();
    virtual void w69(); virtual void w70(); virtual void w71(); virtual void w72();
    virtual void w73(); virtual void w74(); virtual void w75(); virtual void w76();
    virtual void w77(); virtual void w78(); virtual void w79(); virtual void w80();
    virtual void w81(); virtual void w82(); virtual void w83(); virtual void w84();
    virtual void w85(); virtual void w86(); virtual void w87(); virtual void w88();
    virtual void w89(); virtual void w90();
    virtual void SetInWorld(cMWModel* model, int flag);                                  // +0x16c (slot 91)
};

// ---- SP::cSPEditorBlock (retail layout; see slice s0043bbc0 for the neighbouring fields)
struct cSPEditorBlock {
    virtual void v0();                          // vtable +0x00 (slot 0)
    virtual void AddRef();                      // vtable +0x04 (slot 1)
    virtual void Release();                     // vtable +0x08 (slot 2)
    char pad04[4];
    cSPTransformOps mXformOps;                  // +0x08
    AutoRefCount<cPropertyList> mPropList;      // +0x0c
    AutoRefCount<cMWModel> mModel;              // +0x10
    AutoRefCount<cMWModel> mEffectsMaskObject;  // +0x14
    AutoRefCount<cIModelWorld> mModelWorld;     // +0x18
    unsigned mInstance;                         // +0x1c
    unsigned mGroup;                            // +0x20
    char pad24[0x28 - 0x24];
    cSPEditorModel* mEditorModel;               // +0x28
    char pad2c[0x48 - 0x2c];
    cSPVector3 mPosition;                       // +0x48
    char pad54[0x33c - 0x54];
    void* mField33c;                            // +0x33c
    BlockList mChildBlockList;                  // +0x340
    char pad350[0x3e0 - 0x350];
    AutoRefCount<cSPEditorBlock> mSymmetricBlock;   // +0x3e0
    char pad3e4[0x438 - 0x3e4];
    bool mField438;                             // +0x438
    char pad439[0x6cc - 0x439];
    HandleList mItems;                          // +0x6cc
    char pad6dc[0xdc8 - 0x6dc];
    bitset<60> mFlags;                          // +0xdc8
    char paddd0[0xde0 - 0xdd0];
    bool mFieldde0;                             // +0xde0

    enum eBlockFlags { kBlockFlagMax = 60 };

    // this slice
    float GetEffectsMaskScale();                        // 0x00448380
    bool RecordHandlePositionAt(int index, char flag);  // 0x00448480
    bool RecordAllHandlePositions();                    // 0x004484f0
    void UpdateAllHandles();                            // 0x004485d0
    void AddToEffectsMask(cSPVector3 pos, bool flag);   // 0x00448690
    void UpdateEffectsMask();                           // 0x004488c0
    void RemoveFromEffectsMask();                       // 0x00448a80
    void InitDeformAnimationsA();                       // 0x00448b10
    void InitDeformAnimationsB(bool flag);              // 0x00448b80
    bool HasChildWithFlag();                            // 0x00448c10
    void ResetSymmetryBlocks();                         // 0x00448d60
    void ClearSymmetryRecursive();                      // 0x00448dd0
    void SetPosition(const cSPVector3& pos, bool flag); // 0x00448e90

    // neighbours (defined in other slices)
    void SetFlag(eBlockFlags flag, bool value);         // 0x00435a10
    void A48fa0(cSPVector3 pos, bool updatePhysics);    // 0x00448fa0
};

// @ 0x00448380
float cSPEditorBlock::GetEffectsMaskScale()
{
    float result;
    float a = mField33c != 0 ? 1.0f : 0.6f;
    float b = mEditorModel ? mEditorModel->GetScale() : 1.0f;
    if (mFlags.test(0x22))
        result = 0.04f * a * b * 2.0f;
    else
        result = 0.04f * a * b;
    return result;
}

// @ 0x00448480
bool cSPEditorBlock::RecordHandlePositionAt(int index, char flag)
{
    bool result = false;
    if (0 <= index) {
        if (index < mItems.size())
            result = mItems[index]->RecordHandlePosition(flag);
    }
    return result;
}

// @ 0x004484f0
bool cSPEditorBlock::RecordAllHandlePositions()
{
    bool result = true;
    if (!mFlags.test(0xb)) {
        int i = 0;
        int count = mItems.size();
        for (; i < count; i++) {
            bool r = RecordHandlePositionAt(i, 1);
            result = (result && r);
        }
    }
    return result;
}

// @ 0x004485d0
void cSPEditorBlock::UpdateAllHandles()
{
    bool bDone = true;
    if (!mFlags.test(0xb)) {
        int i = 0;
        int count = mItems.size();
        for (; i < count; i++)
            mItems[i]->Update();
    }
}

// @ 0x00448690
void cSPEditorBlock::AddToEffectsMask(cSPVector3 pos, bool /*flag*/)
{
    if (mField438)
        return;
    RemoveFromEffectsMask();
    cMWModel* model = mModelWorld->CreateEffectsMask(mInstance, mGroup, 6);
    mEffectsMaskObject = model;
    if (mEffectsMaskObject) {
        mEffectsMaskObject->mOffset = pos;
        uint32_t index = GetModelManager()->GetGroupIndex(0x23008d4, 0);
        if (index < 0x40)
            mEffectsMaskObject->mGroups[index >> 5] |= 1u << (index % 32);
        mEffectsMaskObject->mOwner = &mXformOps;
        UpdateEffectsMask();
    }
}

// @ 0x004488c0
void cSPEditorBlock::UpdateEffectsMask()
{
    if (!mEffectsMaskObject)
        return;
    mEffectsMaskObject->mXformOps.Assign(&mModel->mXformOps);
    mModelWorld->SetEffectsModel(mEffectsMaskObject);
    InitDeformAnimationsB(1);
    int i = 0;
    int count = mItems.size();
    for (; i < count; i++) {
        float lo = 0.0f;
        float hi = 0.0f;
        mModelWorld->GetModelHandleRange(mEffectsMaskObject, mItems[i]->mHandleID, &lo, &hi, 0);
        float value = (hi - lo) * mItems[i]->mDelta + lo;
        mModelWorld->SetModelHandleValue(mEffectsMaskObject, mItems[i]->mHandleID, value, 0);
    }
}

// @ 0x00448a80
void cSPEditorBlock::RemoveFromEffectsMask()
{
    if (mEffectsMaskObject != 0) {
        cMWModel* pModel = mEffectsMaskObject;
        pModel->mpWorld->SetInWorld(pModel, 0);
        mEffectsMaskObject = 0;
        mFieldde0 = 0;
    }
}

// @ 0x00448b10
void cSPEditorBlock::InitDeformAnimationsA()
{
    void* pModel = mModel;
    Key3 key = { 0, 0, 0 };
    key.a = (int)mInstance;
    key.c = (int)mGroup;
    sub_458f60(pModel, mModelWorld, key, 1);
}

// @ 0x00448b80
void cSPEditorBlock::InitDeformAnimationsB(bool flag)
{
    void* pTarget = mModel;
    if (flag)
        pTarget = mEffectsMaskObject;
    Key3 key = { 0, 0, 0 };
    key.a = (int)mInstance;
    key.c = (int)mGroup;
    sub_458f60(pTarget, mModelWorld, key, 0);
}

// @ 0x00448c10
bool cSPEditorBlock::HasChildWithFlag()
{
    if (mChildBlockList.empty() == false) {
        int i = 0;
        int count = mChildBlockList.size();
        for (; i < count; i++) {
            cSPEditorBlock* child = mChildBlockList[i];
            if (child->mFlags.test(0xc) && !mChildBlockList[i]->mFlags.test(0x14))
                return true;
        }
    }
    return false;
}

// @ 0x00448d60
void cSPEditorBlock::ResetSymmetryBlocks()
{
    cSPEditorBlock* p = mSymmetricBlock;
    if (p)
        p->AddRef();
    ClearSymmetryRecursive();
    if (mEditorModel && mEditorModel->UsingSymmetry() && p)
        p->ClearSymmetryRecursive();
    if (p)
        p->Release();
}

// @ 0x00448dd0
void cSPEditorBlock::ClearSymmetryRecursive()
{
    SetFlag((eBlockFlags)0x39, true);
    mSymmetricBlock = 0;
    int i = 0;
    int count = mChildBlockList.size();
    for (; i < count; i++)
        mChildBlockList[i]->ClearSymmetryRecursive();
}

// @ 0x00448e90
void cSPEditorBlock::SetPosition(const cSPVector3& pos, bool flag)
{
    A48fa0(pos, flag);
    if (mEditorModel && mEditorModel->UsingSymmetry()) {
        if (mSymmetricBlock)
            mSymmetricBlock->A48fa0(cSPVector3(-mPosition[0], mPosition[1], mPosition[2]), flag);
    }
}

}  // namespace SP
