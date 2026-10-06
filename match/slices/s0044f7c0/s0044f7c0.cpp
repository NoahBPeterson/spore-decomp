// slice s0044f7c0 -- SP::cSPEditorBlock clone/mirror builder (6057 bytes, /Od editor module).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: the local fixed_vector has no EH frame).
//
// The function has no PDB name; the PDB's BuildBlock is 0x00441440 (the 8-arg model loader
// this function calls).  "CloneBlock" is a descriptive name, not a recovered one.
//
//   type 0  plain copy of this block           (called by type 2)
//   type 1  mirrored copy (x flipped)          (called by type 3)
//   type 2  copy of this block and its children
//   type 3  mirrored copy of this block and its children, linked as symmetric partners
// For types 2/3 every source block is appended to `originals` and its clone to `copies`
// (same index), then symmetric/asymmetric partner links are re-created between the clones.
//
// Retail layout (0xe08 bytes) from the ModAPI EditorRigblock header, confirmed by the asm.
#include "types.h"

// ---------------------------------------------------------------- math
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
};

struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& other);              // 0x0041cb40 (out of line)
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

Matrix3 MirrorMatrix(const Matrix3& m, int flags);   // 0x004a8e10
Vector3 MirrorVector(const Vector3& v);              // 0x004a8f40

static const float kNegOne = -1.0f;                  // 0x013eb1bc

// ---------------------------------------------------------------- EA / EASTL stubs
template <class T>
struct AutoRefCount {
    T* mpObject;

    AutoRefCount(T* pObject) : mpObject(pObject) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~AutoRefCount() {
        if (mpObject)
            mpObject->Release();
    }
    AutoRefCount& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

template <unsigned N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];

    bool test(size_t i) const {
        if (i < N) {
            const uint32_t word = mWord[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

struct allocator_tag { allocator_tag() {} };

// eastl::fixed_vector<EA::AutoRefCount<T>, 8> (0x38 bytes: begin/end/capacity,
// fixed allocator, 8-entry buffer at +0x18).
template <class T>
struct fixed_ref_vector {
    typedef AutoRefCount<T> value_type;
    value_type* mpBegin;
    value_type* mpEnd;
    value_type* mpCapacity;
    char        mAllocator[0xc];
    value_type* mBuffer[8];

    fixed_ref_vector(const allocator_tag& a) { BaseInit(a); FixedInit(); }
    ~fixed_ref_vector();                                       // 0x00453eb0

    void BaseInit(const allocator_tag& a);                     // 0x00540470
    void FixedInit();                                          // 0x00453770
    fixed_ref_vector& operator=(const fixed_ref_vector& x);    // 0x00453f20
    void push_back(const value_type& v);                       // 0x004541f0

    int size() const { return mpEnd - mpBegin; }
    value_type& operator[](int i) { return mpBegin[i]; }
};

// ---------------------------------------------------------------- Spore stubs
struct cIModelWorld;
struct cSPEditorBlock;

struct cSPEditorHandle {                     // morph/deform handle
    char  pad0[0x180];
    float mDelta;                            // +0x180
    void Update();                           // 0x00482670
};

struct cSPEditorPinTarget {                  // refcounted interface: AddRef slot 0, Release slot 1
    virtual int AddRef();
    virtual int Release();
};

struct cSPEditorPinningInfo {                // pointed to by cSPEditorBlock +0x378
    int                              field_0;
    AutoRefCount<cSPEditorPinTarget> mTarget;            // +0x04
    Vector3                          mOffset;            // +0x08
    Vector3                          mNormal;            // +0x14
    Matrix3                          mOrientation;       // +0x20
    int                              mIndex;             // +0x44
    bool                             mFlag;              // +0x48

    void Attach(cSPEditorBlock* parent, int index, bool flag);   // 0x004e9500
};

struct cSPEditorModel {
    void AddBlock(cSPEditorBlock* block, int notify);            // 0x004abaf0
};

typedef fixed_ref_vector<cSPEditorBlock>  BlockRefVector;
typedef fixed_ref_vector<cSPEditorHandle> HandleRefVector;

bool IsBlockMirrorable(cSPEditorBlock* block);                  // 0x004a6270

struct cSPEditorBlock {
    virtual ~cSPEditorBlock();
    virtual int AddRef();
    virtual int Release();

    char                         pad4[0x18 - 0x4];
    AutoRefCount<cIModelWorld>   mpModelWorld;            // +0x18
    uint32_t                     mInstanceID;             // +0x1c
    uint32_t                     mGroupID;                // +0x20
    int                          mBlockPack;              // +0x24
    cSPEditorModel*              mpEditorModel;           // +0x28
    int                          field_2C;                // +0x2c
    float                        field_30;                // +0x30
    bool                         mIsVisible;              // +0x34
    char                         pad35[0x48 - 0x35];
    Vector3                      mPosition;               // +0x48
    char                         pad54[0xa8 - 0x54];
    Matrix3                      mOrientation;            // +0xa8
    char                         padcc[0xf0 - 0xcc];
    Matrix3                      mUserOrientation;        // +0xf0
    char                         pad114[0x188 - 0x114];
    int                          field_188;               // +0x188
    char                         pad18c[0x1c4 - 0x18c];
    int                          field_1C4;               // +0x1c4
    int                          field_1C8;               // +0x1c8
    int                          mLimbType;               // +0x1cc
    float                        mMuscleScale;            // +0x1d0
    float                        mBaseMuscleScale;        // +0x1d4
    float                        mScale;                  // +0x1d8
    float                        mScale2;                 // +0x1dc
    char                         pad1e0[0x340 - 0x1e0];
    BlockRefVector               mChildren;               // +0x340
    cSPEditorPinningInfo*        mpPinningInfo;           // +0x378
    char                         pad37c[0x3a0 - 0x37c];
    Vector3                      mTriangleDirection;      // +0x3a0
    Vector3                      mTrianglePickOrigin;     // +0x3ac
    char                         pad3b8[0x3e0 - 0x3b8];
    AutoRefCount<cSPEditorBlock> mpSymmetricRigblock;     // +0x3e0
    AutoRefCount<cSPEditorBlock> mpAsymmetricRigblock;    // +0x3e4
    bool                         mIsClone;                // +0x3e8
    char                         pad3e9[0x6cc - 0x3e9];
    HandleRefVector              mMorphHandles;           // +0x6cc
    char                         pad704[0xdc8 - 0x704];
    bitset<60>                   mBooleanAttributes;      // +0xdc8
    char                         padDD0[0xe08 - 0xdd0];

    cSPEditorBlock();                                                   // 0x004346b0
    static void* operator new(size_t n, const char* name, int, int, int, int);

    int  GetLimbType() const { return mLimbType; }

    void SetBooleanAttribute(int index, bool value);                   // 0x00435a10
    bool IsSymmetricChildCandidate();                                   // 0x00435c80
    void SetSymmetricBlock(cSPEditorBlock* block);                      // 0x00438cc0
    void SetAsymmetricBlock(cSPEditorBlock* block);                     // 0x00438df0
    void AddChild(cSPEditorBlock* block);                               // 0x004388b0
    ResourceKey GetMirroredKey(int sign, int flags);                    // 0x00438f20
    void BuildBlock(uint32_t instance, uint32_t group, cIModelWorld* world, int a4,
                    float a5, bool a6, bool a7, bool a8);               // 0x00441440
    void SetModelScaleA(float v, int flag);                             // 0x00440020
    void SetModelScaleB(float v, int flag);                             // 0x00440090
    void SetBaseMuscleScale(float v);                                   // 0x0043eb50
    void Sub_447030(int v);                                             // 0x00447030
    void SetMuscleScale(float v);                                       // 0x0043eae0
    void SetMorphHandleDelta(int index, float delta, bool a, bool b, bool c);  // 0x0043d690
    void UpdateAfterClone();                                            // 0x0044a070
    void RebuildPhysics();                                              // 0x00452040
    void CopyPaintFrom(cSPEditorBlock* src);                            // 0x00440e00
    void SetUserOrientation(Matrix3 m);                                 // 0x0043ffa0
    void SetPosition(const Vector3& pos, bool flag);                    // 0x00448e90
    void SetOrientation(const Matrix3& m, bool flag);                   // 0x00449420
    void SetBaseJointScale(int v);                                      // 0x0044e980
    void SetScaleType(int type);                                        // 0x0044f130
    int  GetSymmetrySign();                                             // 0x0044f220
    int  GetB();                                                        // 0x00451210
    Vector3 GetOffsetA(bool flag);                                      // 0x00438120
    Vector3 GetOffsetB(bool flag);                                      // 0x004381e0
    void Place(Vector3 a, Vector3 b);                                   // 0x00437b00
    void FinishClone();                                                 // 0x00449ed0

    // @ 0x0044f7c0
    cSPEditorBlock* CloneBlock(int type, cSPEditorBlock* root,
                               BlockRefVector& originals, BlockRefVector& copies);
};

// @ 0x0044f7c0
cSPEditorBlock* cSPEditorBlock::CloneBlock(int type, cSPEditorBlock* root,
                                           BlockRefVector& originals, BlockRefVector& copies) {
    if (type == 0 || type == 1) {
        cSPEditorBlock* block = new("Editor", 0, 0, 0, 0) cSPEditorBlock();

        block->SetBooleanAttribute(0xb, mBooleanAttributes.test(0xb));
        block->SetBooleanAttribute(0xa, mBooleanAttributes.test(0xa));
        if (mBooleanAttributes.test(0x39) && !mpAsymmetricRigblock.get()) {
            SetAsymmetricBlock(block);
            block->SetAsymmetricBlock(this);
        }
        block->SetBooleanAttribute(0x39, mBooleanAttributes.test(0x39));
        block->SetBooleanAttribute(0x3a, mBooleanAttributes.test(0x3a));

        if (type == 1) {
            block->SetUserOrientation(MirrorMatrix(mUserOrientation, 0));
            block->SetOrientation(MirrorMatrix(mOrientation, 0), 0);
            block->SetPosition(MirrorVector(mPosition), 0);
        } else {
            block->SetUserOrientation(mUserOrientation);
            block->SetOrientation(mOrientation, 0);
            block->SetPosition(mPosition, 0);
        }
        block->SetBaseJointScale(-2);

        if (type == 1 && mBooleanAttributes.test(0xd)) {
            int sign = GetSymmetrySign() * -1;
            block->SetBaseJointScale(sign);
            const ResourceKey& key = GetMirroredKey(sign, 0);
            block->BuildBlock(key.instanceID, key.groupID, mpModelWorld.get(), field_188,
                              field_30, 1, 1, 1);
        } else {
            block->BuildBlock(mInstanceID, mGroupID, mpModelWorld.get(), field_188,
                              field_30, 1, 1, 1);
        }
        block->mIsClone = 1;

        block->SetBooleanAttribute(0x33, mBooleanAttributes.test(0x33));
        block->SetBooleanAttribute(0x23, mBooleanAttributes.test(0x23));
        block->mIsVisible = mIsVisible;
        block->SetPosition(mPosition, 0);
        block->mTriangleDirection = mTriangleDirection;
        block->mTrianglePickOrigin = mTrianglePickOrigin;
        if (type == 1) {
            block->mTriangleDirection[0] *= kNegOne;
            block->mTrianglePickOrigin[0] *= kNegOne;
        }
        block->field_1C4 = field_1C4;
        block->field_1C8 = field_1C8;

        block->mpPinningInfo->mNormal = mpPinningInfo->mNormal;
        block->mpPinningInfo->mOrientation = mpPinningInfo->mOrientation;
        block->mpPinningInfo->mOffset = mpPinningInfo->mOffset;
        if (type == 0) {
            block->mpPinningInfo->mIndex = mpPinningInfo->mIndex;
            block->mpPinningInfo->mFlag = mpPinningInfo->mFlag;
        } else {
            block->mpPinningInfo->mIndex = -1;
            block->mpPinningInfo->mFlag = 0;
        }
        block->mpPinningInfo->mTarget = 0;

        if (!mBooleanAttributes.test(3) || IsBlockMirrorable(this)) {
            block->SetModelScaleA(mScale2, 1);
            block->SetModelScaleB(mScale, 0);
            block->SetBaseMuscleScale(mBaseMuscleScale);
        }
        block->Sub_447030(1);
        block->SetMuscleScale(mMuscleScale);

        block->SetBooleanAttribute(0, mBooleanAttributes.test(0));
        block->SetBooleanAttribute(5, mBooleanAttributes.test(5));
        block->SetBooleanAttribute(0xf, mBooleanAttributes.test(0xf));
        block->SetBooleanAttribute(0x14, mBooleanAttributes.test(0x14));
        block->SetBooleanAttribute(0x15, mBooleanAttributes.test(0x15));
        block->SetBooleanAttribute(0xc, mBooleanAttributes.test(0xc));
        block->SetScaleType(GetLimbType());
        block->SetBooleanAttribute(1, mBooleanAttributes.test(1));
        if (mBooleanAttributes.test(0xd)) {
            block->SetBooleanAttribute(0xd, 1);
            block->SetBooleanAttribute(0xe, !mBooleanAttributes.test(0xe));
        }

        int numHandles = block->mMorphHandles.size();
        if (numHandles == mMorphHandles.size()) {
            for (int i = 0; i < numHandles; ++i)
                block->SetMorphHandleDelta(i, mMorphHandles[i]->mDelta, 0, 0, 1);
        }
        for (int j = 0; j < numHandles; ++j)
            block->mMorphHandles[j]->Update();

        block->UpdateAfterClone();
        block->RebuildPhysics();
        block->SetBooleanAttribute(9, 1);
        block->CopyPaintFrom(this);
        return block;
    } else if (mpEditorModel) {
        cSPEditorBlock* result = 0;
        if (type == 3) {
            result = CloneBlock(1, root, originals, copies);
            mpEditorModel->AddBlock(result, 1);
            result->SetSymmetricBlock(this);
            result->SetAsymmetricBlock(this);
        } else {
            result = CloneBlock(0, root, originals, copies);
            mpEditorModel->AddBlock(result, 1);
        }
        originals.push_back(AutoRefCount<cSPEditorBlock>(this));
        copies.push_back(AutoRefCount<cSPEditorBlock>(result));

        BlockRefVector children((allocator_tag()));
        children = mChildren;
        if (root->mpSymmetricRigblock.get() && mpSymmetricRigblock.get()) {
            cSPEditorBlock* symmetric = mpSymmetricRigblock.get();
            BlockRefVector symChildren((allocator_tag()));
            symChildren = symmetric->mChildren;
            for (size_t i = 0, n = symChildren.size(); i < n; ++i) {
                if (symChildren[i]->IsSymmetricChildCandidate())
                    children.push_back(symChildren[i]);
            }
        }

        int numChildren = children.size();
        for (int i = 0; i < numChildren; ++i) {
            cSPEditorBlock* copy = children[i]->CloneBlock(type, root, originals, copies);
            originals.push_back(children[i]);
            copies.push_back(AutoRefCount<cSPEditorBlock>(copy));
            result->AddChild(copy);
            copy->SetBooleanAttribute(0xc, children[i]->mBooleanAttributes.test(0xc));
            children[i]->SetPosition(children[i]->mPosition, 1);
            children[i]->SetUserOrientation(children[i]->mUserOrientation);
            children[i]->SetOrientation(children[i]->mOrientation, 1);
            copy->SetBaseJointScale(-2);
            if (copy->GetB() == -1) {
                if (type == 3) {
                    Vector3 offsetA = children[i]->GetOffsetA(1);
                    offsetA[0] *= kNegOne;
                    Vector3 offsetB = children[i]->GetOffsetB(1);
                    offsetB[0] *= kNegOne;
                    copy->Place(offsetA, offsetB);
                } else {
                    copy->Place(copy->GetOffsetA(1), copy->GetOffsetB(1));
                }
            } else {
                copy->mpPinningInfo->Attach(result, copy->mpPinningInfo->mIndex,
                                            copy->mpPinningInfo->mFlag);
            }
        }

        int numOriginals = originals.size();
        int numCopies = copies.size();
        for (int k = 0; k < numOriginals; ++k) {
            cSPEditorBlock* original = originals[k];
            cSPEditorBlock* clone = copies[k];
            if (!clone->mpSymmetricRigblock.get() && original->mpSymmetricRigblock.get()) {
                int found = -1;
                for (int m = 0; m < numOriginals; ++m) {
                    if (originals[m].get() == original->mpSymmetricRigblock.get()) {
                        found = m;
                        break;
                    }
                }
                if (found != -1)
                    clone->SetSymmetricBlock(copies[found]);
            }
            if (!clone->mpAsymmetricRigblock.get() && original->mpAsymmetricRigblock.get()) {
                int found = -1;
                for (int m = 0; m < numOriginals; ++m) {
                    if (originals[m].get() == original->mpAsymmetricRigblock.get()) {
                        found = m;
                        break;
                    }
                }
                if (found != -1)
                    clone->SetAsymmetricBlock(copies[found]);
            }
        }
        result->FinishClone();
        return result;
    }
    return 0;
}
