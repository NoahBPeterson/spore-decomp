// Slice s00489530: SP::cSPEditorLimbStructure mirror/collect/refresh helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct Vector3T {
    float x, y, z;
    Vector3T() {}
    Vector3T(const Vector3T& v) : x(v.x), y(v.y), z(v.z) {}
    float& operator[](int i) { return (&x)[i]; }
    const float& operator[](int i) const { return (&x)[i]; }
};
struct Matrix33T { Vector3T xAxis, yAxis, zAxis; };
struct RwVec3 : Vector3T {
    RwVec3(const Vector3T& v);                                // @ 0x4098a0 (out-of-line copy ctor)
};
struct RwMat33 { Vector3T m[3];
    RwMat33() {}
    RwMat33(const RwMat33& o);                                // @ 0x41cb40 (out-of-line copy ctor)
    Vector3T& operator[](int i) { return m[i]; }
};
struct cSPVector3 : Vector3T {
    cSPVector3() {}
    cSPVector3(const Vector3T& v) : Vector3T(v) {}
    cSPVector3& operator=(const Vector3T& v) { x = v.x; y = v.y; z = v.z; return *this; }
};

Vector3T operator-(const Vector3T& a, const Vector3T& b);    // @ 0x41db10
Vector3T operator+(const Vector3T& a, const Vector3T& b);    // @ 0x41dc10
Vector3T operator-(const Vector3T& v);                       // @ 0x422020
float VectorLength(const Vector3T& v);                       // @ 0x40ae50
cSPVector3 Mirror(const Vector3T& v);                        // @ 0x4a8f40
cSPVector3 Normalize(const Vector3T& v);                     // @ 0x436ce0
cSPVector3 Cross(const Vector3T& a, const Vector3T& b);      // @ 0x44e460
cSPVector3 MatrixFromAxes(const Vector3T& f, const Vector3T& s); // @ 0x4a89e0
cSPVector3 normalized_safe(const Vector3T& v);               // @ 0x449c20

template<class T> struct vector {
    T* mpBegin; T* mpEnd; T* mpCapacity; uint32_t mAllocator[2];
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T& operator[](uint32_t i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    bool empty() const;                          // @ 0x526430
    void clear();                                // @ 0x454280 (erase(first,last))
};

template<int N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bool test(uint32_t i) const {
        if (i < N) return (mWord[i >> 5] & (1u << (i % 32))) != 0;
        return false;
    }
};

namespace SP {

struct cSPEditorBlock;
struct cSPEditorLimbJoint;

struct cSPEditorBlock {
    virtual void _v0();
    virtual int Release();
    char pad0[0x28 - 4];
    void* mEditorModel;                         // +0x28
    char pad1[0x48 - 0x2c];
    cSPVector3 mPosition;                       // +0x48
    char pad2[0x60 - 0x54];
    Matrix33T mOrientation;                     // +0x60
    char pad3[0xa8 - 0x84];
    RwMat33 mTorsoOrientation;                  // +0xa8
    char pad3b[0x33c - 0xcc];
    cSPEditorBlock* mLink33c;                   // +0x33c
    char pad4[0x3f0 - 0x340];
    struct LinkData { char pad[0xc]; cSPVector3 mPos; cSPVector3& GetPos() { return mPos; } }* mLinkData;  // +0x3f0
    char pad4b[0xc0c - 0x3f4];
    vector<void*> mVec0c0c;                     // +0xc0c
    char pad5[0xdc8 - 0xc20];
    bitset<60> mFlags;                          // +0xdc8

    cSPVector3& GetPosition() { return mPosition; }
    RwMat33& GetTorsoOrientation() { return mTorsoOrientation; }
    cSPEditorBlock* GetLink() { return mLink33c; }
    LinkData* GetLinkData() { return mLinkData; }
    bool IsLimbPart();                          // @ 0x435c80
    int CalculateSymmetrySign();                // @ 0x44f240
};

struct cSPEditorLimbJoint {
    cSPEditorBlock* mJointBlock;                // +0x00
    cSPEditorLimbJoint* mUpperJoint;            // +0x04
    vector<cSPEditorLimbJoint*> mLowerJoints;   // +0x08
    cSPVector3 mTargetPosition;                 // +0x1c
    cSPVector3 mOriginalPosition;               // +0x28
    cSPVector3 mPositionAtCreation;             // +0x34

    int Sign(bool recurse);                     // @ 0x4874c0
    RwMat33 GetBasis(int mode);                 // @ 0x488600
    cSPEditorLimbJoint* FindFirstLimbLowerJoint();  // @ 0x487850
};

struct cSPEditorLimbStructure {
    vector<cSPEditorBlock*> mPileList;          // +0x00
    cSPEditorBlock* mBaseBlock;                 // +0x14
    cSPEditorLimbJoint* mBaseJoint;             // +0x18
    cSPEditorBlock* mLastBone;                  // +0x1c
    cSPEditorBlock* mEndBlock;                  // +0x20
    float mLimbOriginalScale;                   // +0x24
    float mSymmetrySign;                        // +0x28
    vector<cSPEditorLimbJoint*> mFeet;          // +0x2c
    vector<cSPEditorLimbJoint*> mHands;         // +0x40

    void MirrorTargets(cSPEditorLimbJoint* joint, vector<cSPEditorLimbJoint*>* list);  // @ 0x489530
    void MirrorTargetsOffset(cSPEditorLimbJoint* joint, float f);                      // @ 0x489640
    void RefreshTargets(vector<cSPEditorLimbJoint*>* list, bool b);                    // @ 0x489710
    void RefreshBlockTargets(cSPEditorBlock* block, bool b);                           // @ 0x4897b0
    void Rebuild(cSPEditorBlock* block);                                               // @ 0x4898a0
    void CollectBlocks(cSPEditorBlock* block);                                         // @ 0x489900
    void FixAllJoints();                                                               // @ 0x489ae0
    void UpdateLimbScale();                                                            // @ 0x489bc0
    void FinalizeJoints(cSPEditorLimbJoint* joint, bool b);                            // @ 0x489c60
    void RepinJoint(cSPEditorLimbJoint* joint);                                        // @ 0x489cf0
};

// external helpers
void RepinBlockToTorso(cSPEditorBlock* b, cSPVector3 pos, RwMat33 orient, int flag); // @ 0x49fbd0
float FUN_00496760(cSPEditorBlock* b, float f, int flag);               // @ 0x496760
RwMat33 FUN_004a25f0(RwMat33 m, int sign);                              // @ 0x4a25f0
RwMat33 MatrixFromAxes2(const Vector3T& a, const Vector3T& b);          // @ 0x4a89e0
cSPVector3 GetLimbOriginalPosition(cSPEditorLimbStructure* self);       // @ 0x48c610
void FUN_0049d1f0(cSPEditorBlock* block, float x, int a, int b);        // @ 0x49d1f0
void FUN_004961d0(cSPEditorBlock* block, cSPEditorLimbStructure* self); // @ 0x4961d0
void BuildPileList(cSPEditorBlock* block, cSPEditorLimbStructure* limb, int depth); // @ 0x48c790
void Refresh(cSPEditorLimbStructure* self, bool relative);              // @ 0x4890e0
void MirrorOriginal(cSPEditorLimbJoint* joint, float f);                // @ 0x4893f0
void MirrorCreation(cSPEditorLimbJoint* joint, float f);                // @ 0x489490
void UpdateSymmetry(cSPEditorLimbStructure* self);                      // @ 0x488a50
bool FixJoint(cSPEditorLimbJoint* joint);                               // @ 0x48afc0
void SetUIStateBlock(cSPEditorLimbStructure* self, void* arg);          // @ 0x48a560
cSPEditorBlock* FUN_004a9a00(cSPEditorBlock* block, bool b);            // @ 0x4a9a00
cSPEditorBlock* GetFirstFootBlock(cSPEditorBlock* block);               // @ 0x4a9840
cSPEditorBlock* FUN_004a9920(cSPEditorBlock* block);                    // @ 0x4a9920
void FUN_0048bdd0(cSPEditorLimbStructure* self);                        // @ 0x48bdd0
void FUN_0048bf70(cSPEditorLimbJoint* joint, int i);                    // @ 0x48bf70
void FUN_0048bae0(cSPEditorLimbStructure* self, int i);                 // @ 0x48bae0

// @ 0x489530
void cSPEditorLimbStructure::MirrorTargets(cSPEditorLimbJoint* joint, vector<cSPEditorLimbJoint*>* list)
{
    bool skip;
    if (list == 0) {
        skip = (joint == mBaseJoint);
    } else {
        cSPEditorLimbJoint** it = list->begin();
        while (it != list->end() && *it != joint) ++it;
        skip = (it != list->end());
    }
    if (!skip) {
        if (!joint->mJointBlock->IsLimbPart()) {
            cSPVector3 m = Mirror(joint->mTargetPosition);
            joint->mTargetPosition = m;
        }
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        MirrorTargets(joint->mLowerJoints[i], list);
}

// @ 0x489640
void cSPEditorLimbStructure::MirrorTargetsOffset(cSPEditorLimbJoint* joint, float f)
{
    if (!joint->mJointBlock->IsLimbPart()) {
        cSPVector3 m = Mirror(joint->mTargetPosition);
        m.x = f * 2.0f + m.x;
        joint->mTargetPosition = m;
        for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
            MirrorTargetsOffset(joint->mLowerJoints[i], f);
    }
}

// @ 0x489710
void cSPEditorLimbStructure::RefreshTargets(vector<cSPEditorLimbJoint*>* list, bool b)
{
    if (!b) FUN_0049d1f0(mBaseBlock, mBaseJoint->mOriginalPosition.x, 0, 0);
    MirrorTargets(mBaseJoint, list);
    MirrorOriginal(mBaseJoint, mBaseJoint->mOriginalPosition.x);
    MirrorCreation(mBaseJoint, mBaseJoint->mPositionAtCreation.x);
    UpdateSymmetry(this);
}

// @ 0x4897b0
void cSPEditorLimbStructure::RefreshBlockTargets(cSPEditorBlock* block, bool b)
{
    if (block) {
        if (!b) FUN_0049d1f0(mBaseBlock, block->mPosition.x, 0, 0);
        MirrorTargetsOffset(mBaseJoint, mBaseJoint->mTargetPosition.x);
        MirrorOriginal(mBaseJoint, mBaseJoint->mOriginalPosition.x);
        MirrorCreation(mBaseJoint, mBaseJoint->mPositionAtCreation.x);
        FUN_004961d0(mBaseBlock, this);
    }
}

// @ 0x4898a0
void cSPEditorLimbStructure::Rebuild(cSPEditorBlock* block)
{
    CollectBlocks(block);
    UpdateLimbScale();
    mPileList.clear();
    BuildPileList(mBaseBlock, this, 0);
    Refresh(this, true);
}

// @ 0x489900
void cSPEditorLimbStructure::CollectBlocks(cSPEditorBlock* block)
{
    if (block == 0) return;
    bool done = false;
    if (block != 0 && !block->mVec0c0c.empty()) {
        if (block->mFlags.test(0x2d)) {
            mEndBlock = block;
            done = true;
        } else if (block->mFlags.test(0x2c)) {
            mEndBlock = block;
            done = true;
        }
    }
    if (!done) {
        bool b = (block->mLink33c == 0 || block->mLink33c->mFlags.test(0xb));
        mLastBone = FUN_004a9a00(mBaseBlock, b);
        mEndBlock = GetFirstFootBlock(mBaseBlock);
        if (mEndBlock == 0) mEndBlock = FUN_004a9920(mBaseBlock);
    }
}

// @ 0x489ae0
void cSPEditorLimbStructure::FixAllJoints()
{
    if (mEndBlock) {
        for (int i = 0, n = mBaseJoint->mLowerJoints.size(); i < n; i++)
            FixJoint(mBaseJoint->mLowerJoints[i]);
        FUN_0048bdd0(this);
        for (int i = 0, n = mBaseJoint->mLowerJoints.size(); i < n; i++)
            FixJoint(mBaseJoint->mLowerJoints[i]);
        FinalizeJoints(mBaseJoint, true);
    }
}

// @ 0x489bc0
void cSPEditorLimbStructure::UpdateLimbScale()
{
    cSPVector3 p = GetLimbOriginalPosition(this);
    cSPVector3 d = mBaseBlock->mPosition - p;
    mLimbOriginalScale = VectorLength(d);
}

// @ 0x489c60
void cSPEditorLimbStructure::FinalizeJoints(cSPEditorLimbJoint* joint, bool b)
{
    if (joint == 0) joint = mBaseJoint;
    if (b) FUN_0048bf70(joint, 0);
    FUN_0048bae0(this, 0);
    RepinJoint(mBaseJoint);
    SetUIStateBlock(this, joint->mJointBlock);
    UpdateSymmetry(this);
}

// @ 0x489cf0
void cSPEditorLimbStructure::RepinJoint(cSPEditorLimbJoint* joint)
{
    if (!joint->mLowerJoints.empty()) {
        cSPEditorLimbJoint* lower = joint->FindFirstLimbLowerJoint();
        if (lower) {
            const Vector3T* src = (joint->mUpperJoint == 0)
                ? &joint->mTargetPosition : &joint->mJointBlock->GetPosition();
            RwVec3 base(*src);
            int mode = (joint->mUpperJoint != 0) ? 2 : 0;
            RwMat33 basis = joint->GetBasis(mode);
            cSPVector3 d = lower->mTargetPosition - base;
            float len = VectorLength(d);
            if (joint->Sign(false) == 0) base[0] = 0.0f;
            RepinBlockToTorso(joint->mJointBlock, RwVec3(base), basis, 0);
            FUN_00496760(joint->mJointBlock, len, 0);
            FUN_004961d0(mBaseBlock, this);
        }
    } else if (joint->mJointBlock->mFlags.test(0x2c)) {
        RwVec3 pos(joint->mJointBlock->GetPosition());
        RwVec3 pos2(pos);
        if (joint->mJointBlock->GetLink()) {
            cSPVector3 linkPos;
            linkPos = joint->mJointBlock->GetLink()->GetLinkData()->GetPos();
        }
        RwMat33 basis = joint->GetBasis(2);
        RwMat33 orient = FUN_004a25f0(basis, joint->Sign(false));
        if (joint->Sign(false) == 0) pos[0] = 0.0f;
        RepinBlockToTorso(joint->mJointBlock, pos, orient, 0);
    } else {
        cSPVector3 pos(joint->mJointBlock->GetPosition());
        RwMat33 orient(joint->mJointBlock->GetTorsoOrientation());
        if (joint->Sign(false) == 0) pos[0] = 0.0f;
        RepinBlockToTorso(joint->mJointBlock, pos, orient, 0);
    }

    int jointSign = joint->Sign(true);
    int blockSign = joint->mJointBlock->CalculateSymmetrySign();
    if (blockSign != jointSign) {
        int unused = joint->mJointBlock->CalculateSymmetrySign();
        if (jointSign == 0) {
            RwMat33 m(joint->mJointBlock->GetTorsoOrientation());
            cSPVector3 a(joint->mJointBlock->GetPosition());
            cSPVector3 b(m[1]);
            cSPVector3 c(m[2]);
            a[0] = 0.0f;
            b[0] = 0.0f;
            c[0] = 0.0f;
            b = normalized_safe(b);
            c = normalized_safe(c);
            cSPVector3 nb(-b);
            m = MatrixFromAxes2(nb, c);
            FUN_004961d0(mBaseBlock, this);
            RepinBlockToTorso(joint->mJointBlock, a, m, 0);
        }
    }
    for (int i = 0, n = joint->mLowerJoints.size(); i < n; i++)
        RepinJoint(joint->mLowerJoints[i]);
}

}  // namespace SP
