// SP::cSPEditorBlock::SetModelBasedOnSymmetrySign (0x439110, 4931 bytes).
// Unoptimized editor module: /Od /Ob1 /arch:SSE /fp:fast, no /EHsc (the local
// vectors have destructors but there is no EH frame).
//
// Layout: retail cSPEditorBlock follows the ModAPI EditorRigblock layout
// (mpSymmetricRigblock at +0x3e0, mChildren at +0x340, mBooleanAttributes at
// +0xdc8), not the 2008 PDB one.
// Local names: parameter and local names come from the 2008 dev PDB's S_BPREL32
// records for this function (symmetrySign, needNewModel, originalTransform, ...);
// /Od orders a scope's locals by a hash of their names, so these reproduce the
// original frame. Locals that did not exist in 2008 got names chosen by search.
// ScratchSlots<N>() stand in for the reserved frames of inline helpers that the
// original compiler declined to inline (see docs/matching.md, /Od frame layout).
#include "types.h"

inline void* operator new(size_t, void* p) { return p; }

namespace SP {

struct cSPEditorBlock;

// ---------------------------------------------------------------- math types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& other) { Assign(other); }
    void Assign(const Matrix3& other);             // 0041CB40
};

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};

// Transform: flags, change counter, offset, scale, rotation (0x38 bytes).
struct Transform {
    uint16_t mFlags;        // +0x00
    uint16_t mChangeCount;  // +0x02
    Vector3  mOffset;       // +0x04
    float    mScale;        // +0x10
    Matrix3  mRotation;     // +0x14

    Transform();                                   // 00409930
    Transform(const Transform& other);             // 0040CE80

    void SetOffset(const Vector3& v) {
        mOffset = v;
        mFlags |= 4;
        mChangeCount++;
    }
    void SetRotation(const Matrix3& m) {
        mRotation = m;
        mFlags |= 2;
        mChangeCount++;
    }
};

// ------------------------------------------------------------- smart pointers
template <class T> struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};

struct cPropertyList {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HasProperty(uint32_t propertyID) const;   // +0x1C
};

struct cMorphHandle {
    uint32_t pad0[0x8c / 4];
    uint32_t mChannel;                 // +0x8C
    uint32_t pad90[(0x180 - 0x90) / 4];
    float    mWeight;                  // +0x180
};

struct cSPEditorModel {
    bool F4adc40();                    // 004ADC40 (returns byte +0x4f)
};

// ------------------------------------------------------------------- EASTL bits
struct sp_vector_allocator {
    sp_vector_allocator() {}
    sp_vector_allocator(const sp_vector_allocator& x);   // 00429360 (out of line)
};

template <class T> struct SimpleVector {   // vector<T> with out-of-line helpers
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    T* erase(T* first, T* last);           // 004769B0
    void DoInsertValue(T* position, const T& value);   // 00455660
    void push_back(const T& value) {       // 004547F0 / 00454860 (declined inline)
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void clear() { erase(mpBegin, mpEnd); }
};

template <class T> struct FixedVectorRef {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    bool empty() const;                    // 00526430
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};

// Reserves N dwords of /Od frame at the point of the call (a declined inline's frame).
template <int N> inline void ScratchSlots() { uint32_t s[N]; }

template <int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t DoGetWord(uint32_t i) const { return mWord[i / 32]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
};

// Saved handle/deformation state of a block (0x3c bytes each).
struct HandleState {
    uint32_t data[15];
};

struct alloc_tag { alloc_tag() {} };

struct state_allocator {
    const char* mpName;
    uint32_t mFlags;
    state_allocator(const alloc_tag& tag);       // 00429360 (out of line)
};

struct HandleStateVectorBase {
    HandleState* mpBegin;
    HandleState* mpEnd;
    HandleState* mpCapacity;
    state_allocator mAllocator;

    HandleStateVectorBase(const alloc_tag& a)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~HandleStateVectorBase();              // 00455BA0 (frees the buffer)
};

struct HandleStateVector : HandleStateVectorBase {
    HandleStateVector(const alloc_tag& a = alloc_tag())
        : HandleStateVectorBase(a) {}
    __forceinline ~HandleStateVector() {
        for (HandleState* p = mpBegin; p < mpEnd; ++p)
            p->~HandleState();
    }
};

struct empty_allocator {
    const char* mpName;
    uint32_t mFlags;
    empty_allocator() {}
    void deallocate(void* p, size_t n) {
        if (((int*)p)[-1] != 0)
            delete[] (char*)p;
    }
};

struct IRefCounted {
    virtual void v00();
    virtual int AddRef();
    virtual int Release();                  // +0x08
};

// Element of the pile list: an intrusive pointer that releases through slot 2.
struct BlockRef {
    cSPEditorBlock* mpObject;
    ~BlockRef() {
        if (mpObject)
            ((IRefCounted*)mpObject)->Release();
    }
    operator cSPEditorBlock*() const { return mpObject; }
};

template <class T> inline void destruct(T* first, T* last) {
    for (; first < last; ++first)
        first->~T();
}

struct BlockVectorBase {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    empty_allocator mAllocator;
    BlockVectorBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~BlockVectorBase() {                    // 00425990 (declined inline)
        if (mpBegin)
            DoFree(mpBegin, mpCapacity - mpBegin);
    }
    void DoFree(BlockRef* p, size_t n) { mAllocator.deallocate(p, n * sizeof(BlockRef)); }
};

struct BlockVector : BlockVectorBase {
    ~BlockVector() { destruct(mpBegin, mpEnd); }   // 00453EB0 (declined inline)
    int size() const { return (int)(mpEnd - mpBegin); }
    BlockRef& operator[](int i) { return mpBegin[i]; }
};

// ------------------------------------------------------------------ the block
struct cSPEditorBlock {
    uint32_t pad0[3];
    AutoRefCount<cPropertyList> mpPropList;        // +0x00C
    uint32_t pad10[3];
    uint32_t mInstanceID;                          // +0x01C
    uint32_t pad20[2];
    cSPEditorModel* mpEditorModel;                 // +0x028
    uint32_t pad2c;
    float    field_30;                             // +0x030
    uint32_t pad34;
    uint32_t mUIState;                             // +0x038
    int      mUIStateValue;                        // +0x03C
    uint32_t pad40[2];
    Vector3  mPosition;                            // +0x048
    uint32_t pad54[3];
    Matrix3  mTotalOrientation;                    // +0x060
    Matrix3  mHistoryTotalOrientation;             // +0x084
    Matrix3  mOrientation;                         // +0x0A8
    Matrix3  mHistoryBaseOrientation;              // +0x0CC
    Matrix3  mUserOrientation;                     // +0x0F0
    uint32_t pad114[(0x1c0 - 0x114) / 4];
    int      mSymmetrySign;                        // +0x1C0
    int      mModelSignModifier;                   // +0x1C4
    uint32_t pad1c8[4];
    float    mScale;                               // +0x1D8
    uint32_t pad1dc[(0x340 - 0x1dc) / 4];
    FixedVectorRef<cSPEditorBlock*> mChildren;     // +0x340
    uint32_t pad354[(0x3a0 - 0x354) / 4];
    Vector3  mTriangleDirection;                   // +0x3A0
    uint32_t pad3ac[(0x3e0 - 0x3ac) / 4];
    AutoRefCount<cSPEditorBlock> mpSymmetricRigblock;   // +0x3E0
    uint32_t pad3e4[2];
    AutoRefCount<cSPEditorBlock> mpBallConnectorHandle; // +0x3EC
    uint32_t pad3f0[(0x6cc - 0x3f0) / 4];
    FixedVectorRef<AutoRefCount<cMorphHandle> > mMorphHandles;   // +0x6CC
    uint32_t pad6e0[(0x704 - 0x6e0) / 4];
    SimpleVector<float> mMorphHandleWeights;       // +0x704
    uint32_t pad714[(0x73c - 0x714) / 4];
    SimpleVector<uint32_t> mMorphHandleChannels;   // +0x73C
    uint32_t pad74c[(0xdc8 - 0x74c) / 4];
    bitset<60> mBooleanAttributes;                 // +0xDC8

    bool IsFrozen();                                                    // 00435C80
    void SetBooleanAttribute(int index, bool value);                    // 00435A10
    ResourceKey GetModelKey(int sign, int flags);                       // 00438F20
    void BuildBlock(uint32_t instanceID, uint32_t groupID, int a, int b,
                    float f, bool c, bool d, bool e);                   // 00441440
    void SetUIState(int state, bool a, bool b, bool c);                 // 0043A5E0
    void ApplyScale(float scale, int flags);                            // 00440090
    void CopyStateFrom(cSPEditorBlock* other);                          // 00440E00
    void UpdateEffects();                                               // 00449ED0
    void Select(int a, int b);                                          // 0044BCF0
    void Deselect(int a, int b);                                        // 0044BA20
    bool IsSelected();                                                  // 0044C030
    void Invalidate(bool all);                                          // 00447030
    void RebuildPhysics();                                              // 00452040
    void SetUserOrientation(Matrix3 m);                                 // 0043FFA0
    void SetOrientation(const Matrix3* m, int flags);                   // 00449420
    void GetOffsetA(Vector3* out, int flags);                           // 00438120
    void GetOffsetB(Vector3* out, int flags);                           // 004381E0
    void Place(Vector3 a, Vector3 b);                                   // 00437B00
    int  GetBlockType(uint32_t instanceID);                             // 0044E830
    bool CanUseSymmetrySign(int sign);                                  // 0044C5A0
    int  CalculateSymmetrySign();                                       // 0044F240
    void SetSymmetryFlip(int dir);                                      // 0044C480
    uint32_t GetInstanceID() const { return mInstanceID; }
    cSPEditorBlock* GetSymmetricBlock() const { return mpSymmetricRigblock; }
    int GetUIStateValue() const { return mUIStateValue; }
    bool GetBooleanAttribute(uint32_t i) const { return mBooleanAttributes.test(i); }

    void SetModelBasedOnSymmetrySign(int sign, bool mirrorOrientation, bool recurse,
                                     bool skipPinned, int depth);
};

bool __cdecl SignsDiffer(int oldSign, int newSign, int flags);                  // 004A7EA0
void __cdecl SaveHandleState(cSPEditorBlock* block, HandleStateVector* out, bool all); // 0049C8F0
void __cdecl RestoreHandleState(HandleStateVector* state);                     // 0049CB90
Matrix3 __cdecl MirrorMatrix(const Matrix3& m, int axis);                      // 004A8E10
void __cdecl BuildPileList(cSPEditorBlock* block, BlockVector* out, int flags); // 0048C790
void __cdecl MirrorChildTransformA(cSPEditorBlock* child, Transform oldT, Transform newT, bool flag); // 0049D390
void __cdecl MirrorChildTransformB(cSPEditorBlock* child, Transform oldT, Transform newT, bool flag); // 0049D550

// @ 0x00439110
void cSPEditorBlock::SetModelBasedOnSymmetrySign(int symmetrySign, bool flipThisBlockOrientation, bool flipChildren,
                                                 bool ignoreBallJoints, int depth)
{
    ScratchSlots<1>();
    if (IsFrozen())
        return;

    HandleStateVector oldHandles;
    HandleStateVector deformState;
    if (depth == 0) {
        SaveHandleState(this, &oldHandles, true);
        SaveHandleState(mpSymmetricRigblock, &deformState, true);
    }

    int desiredModelSign = mModelSignModifier * symmetrySign;
    int oldSymmetrySign = mSymmetrySign;
    if (mpPropList == 0)
        return;
    ScratchSlots<1>();

    ResourceKey key;
    bool needNewModel = false;
    key = GetModelKey(desiredModelSign, 0);
    if (key.instanceID != mInstanceID)
        needNewModel = true;

    Transform originalTransform;
    originalTransform.SetOffset(mPosition);
    originalTransform.SetRotation(mTotalOrientation);

    cSPEditorBlock* symmetricBlock = GetSymmetricBlock();
    bool needFlip = SignsDiffer(mSymmetrySign, symmetrySign, 0);
    mSymmetrySign = symmetrySign;

    if (needNewModel) {
        if (!mMorphHandles.empty()) {
            mMorphHandleWeights.clear();
            mMorphHandleChannels.clear();
            for (int i = 0, listSize = mMorphHandles.size(); i < listSize; ++i) {
                mMorphHandleWeights.push_back(mMorphHandles[i]->mWeight);
                mMorphHandleChannels.push_back(mMorphHandles[i]->mChannel);
            }
        }
        bool isCurrentVisible = IsSelected();
        int uiState = mUIStateValue;
        bool wasFlag23 = GetBooleanAttribute(0x23);
        bool oldFlag33 = GetBooleanAttribute(0x33);
        BuildBlock(key.instanceID, key.groupID, 0, 0, field_30, true, true, true);
        SetBooleanAttribute(0x23, wasFlag23);
        SetBooleanAttribute(0x33, oldFlag33);
        SetUIState(uiState, true, true, true);
        float uniformScale = mScale;
        mScale = 1.0f;
        ApplyScale(uniformScale, 0);
        SetUIState(uiState, true, false, true);
        CopyStateFrom(this);
        UpdateEffects();
        if (isCurrentVisible)
            Select(0, 0);
        else
            Deselect(0, 0);
    }

    bool didFlipMainModel = false;
    if (needFlip && flipThisBlockOrientation) {
        mOrientation = MirrorMatrix(mOrientation, 0);
        mUserOrientation = MirrorMatrix(mUserOrientation, 0);
        didFlipMainModel = true;
    }
    if (needFlip)
        mTriangleDirection[0] *= -1.0f;

    if (mpEditorModel->F4adc40() && symmetricBlock != 0) {
        int symModelSign = -desiredModelSign;
        if (symModelSign == 0) {
            if (!mpPropList->HasProperty(0x3a3b9d21))
                symModelSign = 1;
        }
        key = GetModelKey(symModelSign, 0);
        needNewModel = false;
        symmetricBlock->mSymmetrySign = mSymmetrySign * -1;
        if (key.instanceID != symmetricBlock->mInstanceID)
            needNewModel = true;
        if (needFlip)
            mpSymmetricRigblock->mTriangleDirection[0] *= -1.0f;
        if (needNewModel) {
            bool isCurrentVisible = mpSymmetricRigblock ? mpSymmetricRigblock->IsSelected() : false;
            if (!symmetricBlock->mMorphHandles.empty()) {
                symmetricBlock->mMorphHandleWeights.clear();
                symmetricBlock->mMorphHandleChannels.clear();
                for (int i = 0, listSize = symmetricBlock->mMorphHandles.size(); i < listSize; ++i) {
                    symmetricBlock->mMorphHandleWeights.push_back(symmetricBlock->mMorphHandles[i]->mWeight);
                    symmetricBlock->mMorphHandleChannels.push_back(symmetricBlock->mMorphHandles[i]->mChannel);
                }
            }
            int uiState = symmetricBlock->mUIStateValue;
            bool wasFlag23 = symmetricBlock->GetBooleanAttribute(0x23);
            bool oldFlag33 = symmetricBlock->GetBooleanAttribute(0x33);
            symmetricBlock->BuildBlock(key.instanceID, key.groupID, 0, 0, field_30, true, true, true);
            symmetricBlock->SetBooleanAttribute(0x23, wasFlag23);
            symmetricBlock->SetBooleanAttribute(0x33, oldFlag33);
            symmetricBlock->SetUIState(symmetricBlock->GetUIStateValue(), true, false, true);
            float uniformScale = symmetricBlock->mScale;
            symmetricBlock->mScale = 1.0f;
            symmetricBlock->ApplyScale(uniformScale, 0);
            symmetricBlock->SetUIState(uiState, true, true, true);
            symmetricBlock->CopyStateFrom(this);
            symmetricBlock->UpdateEffects();
            if (isCurrentVisible)
                symmetricBlock->Select(0, 0);
            else
                symmetricBlock->Deselect(0, 0);
        }
    }

    if (needNewModel || oldSymmetrySign != symmetrySign) {
        Invalidate(true);
        RebuildPhysics();
    }

    if (mpSymmetricRigblock != 0) {
        int oldSymSign = mpSymmetricRigblock->mSymmetrySign;
        mpSymmetricRigblock->mSymmetrySign = -symmetrySign;
        if (needNewModel || oldSymSign != -symmetrySign) {
            mpSymmetricRigblock->Invalidate(true);
            mpSymmetricRigblock->RebuildPhysics();
        }
    }

    SetUserOrientation(mUserOrientation);
    ScratchSlots<2>();
    SetOrientation(&mOrientation, 0);

    Transform currentTransform;
    currentTransform.SetOffset(mPosition);
    currentTransform.SetRotation(mTotalOrientation);

    if (!mChildren.empty() && flipChildren) {
        bool keepSymmetric = GetBooleanAttribute(0x13);
        BlockVector pileList;
        BuildPileList(this, &pileList, 0);
        for (int i = 0, pileSize = pileList.size(); i < pileSize; ++i) {
            cSPEditorBlock* child = pileList[i];
            if (child->IsFrozen()) {
                if (didFlipMainModel || needNewModel || needFlip) {
                    Vector3 offsetA, offsetB;
                    child->GetOffsetA(&offsetA, 1);
                    child->GetOffsetB(&offsetB, 1);
                    child->Place(offsetA, offsetB);
                }
            } else if (!ignoreBallJoints || !child->GetBooleanAttribute(0x1f)) {
                int childType = child->GetBlockType(child->GetInstanceID());
                ScratchSlots<12>();
                int signToUse = childType;
                if (needFlip) {
                    MirrorChildTransformA(child, originalTransform, currentTransform, keepSymmetric);
                    MirrorChildTransformB(child, originalTransform, currentTransform, keepSymmetric);
                    signToUse = childType * -1;
                }
                if (!child->CanUseSymmetrySign(signToUse))
                    signToUse = mSymmetrySign;
                int calculatedSign = child->CalculateSymmetrySign();
                if (calculatedSign != 0 && signToUse != 0) {
                    if (calculatedSign != signToUse)
                        child->SetSymmetryFlip(-1);
                    else
                        child->SetSymmetryFlip(1);
                }
                child->SetModelBasedOnSymmetrySign(calculatedSign, false, false, false, depth + 1);
                if (didFlipMainModel || needNewModel || needFlip) {
                    Vector3 offsetA, offsetB;
                    child->GetOffsetA(&offsetA, 1);
                    child->GetOffsetB(&offsetB, 1);
                    child->Place(offsetA, offsetB);
                    if (child->mpSymmetricRigblock != 0) {
                        Vector3 offsetA, offsetB;
                        child->mpSymmetricRigblock->GetOffsetA(&offsetA, 1);
                        child->mpSymmetricRigblock->GetOffsetB(&offsetB, 1);
                        child->mpSymmetricRigblock->Place(offsetA, offsetB);
                    }
                }
            }
        }
    }

    if (mpSymmetricRigblock != 0 && needFlip && depth == 0 && mpBallConnectorHandle == 0) {
        RestoreHandleState(&oldHandles);
        RestoreHandleState(&deformState);
    }
}

} // namespace SP
