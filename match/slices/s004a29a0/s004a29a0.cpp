// Slice s004a29a0: SP editor block snap (PDB candidate SP::EditorUtils::SnapBlockToSocket).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

// rw::math::fpu::Vector3Template<float,0>: copy ctor is out of line (0x004098a0)
struct rwVec3 {
    float x, y, z;
    rwVec3() {}
    rwVec3(const rwVec3& v);                      // 0x004098a0
};
// cSPVector3: inline copy ctor that forwards to the out-of-line rw copy ctor
struct cSPVector3 : rwVec3 {
    cSPVector3() {}
    cSPVector3(const cSPVector3& v) : rwVec3(v) {}
};
rwVec3 operator-(const rwVec3& a, const rwVec3& b);   // 0x0041db10
// plain vector with inline member-wise copy
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
    Vec3(const rwVec3& v) : x(v.x), y(v.y), z(v.z) {}
};

// rw::math::fpu::Matrix33Template<float,0>: copy ctor is out of line (0x0041cb40)
struct cSPMatrix3 {
    rwVec3 r[3];
    cSPMatrix3(const cSPMatrix3& m);              // 0x0041cb40
    rwVec3& operator[](int i) { return r[i]; }
};

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vec3 mTranslation;
    float mScale;
    cSPMatrix3 mRotation;
    cSPTransform();                                          // 0x00409930
    const cSPMatrix3& GetRotation() const { return mRotation; }
    void SetRotation(const cSPMatrix3& m) { mRotation = m; mFlags |= 2; mModificationCount++; }
    void PreRotate(const Vec3& axis, float angle);     // 0x006baba0
};

struct Bitset60 {                                 // eastl::bitset<60>
    uint32_t w[2];
    bool test(uint32_t i) const
    {
        if (i < 60) {
            uint32_t word = w[i / 32];
            return (word & (1u << (i % 32))) != 0;
        }
        return false;
    }
};

template<class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

// cMWModel-like object at block+0x3f0: non-virtual refcount at +0x40
struct cCounted {
    uint32_t pad0[3];
    rwVec3 mPosition;                             // +0x0c
    uint32_t pad18[(0x40 - 0x18) / 4];
    int mRefCount;                                // +0x40
    void AddRef() { mRefCount = mRefCount + 1; }
    void Release();                               // 0x0040f360
};
template<class T> struct CountedRef {
    T* mpObject;
    CountedRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~CountedRef() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    const rwVec3& GetPosition() const { return mpObject->mPosition; }
};

// block render model (+0x3ec)
struct cSPEditorBlockModel {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3();
    virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7();
    virtual void _v8();
    virtual rwVec3 GetPosition();             // +0x24
    virtual void _v10(); virtual void _v11();
    virtual void SetState(int a, int b);          // +0x30
};
void UpdateModelPaint(cSPEditorBlockModel* m, float delta);   // 0x00496b60

struct cSPEditorModel {
    bool IsUsingSymmetry();                       // 0x004adc40
};

struct cSPEditorBlock;
struct BlockVec {
    AutoRefCount<cSPEditorBlock>* mpBegin;
    AutoRefCount<cSPEditorBlock>* mpEnd;
    AutoRefCount<cSPEditorBlock>& operator[](int i) { return mpBegin[i]; }
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cSPEditorBlock {
    virtual void _v0();
    uint32_t pad04[(0x28 - 4) / 4];
    cSPEditorModel* mpEditorModel;                // +0x28
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    cSPVector3 mPosition;                         // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];
    cSPMatrix3 mOrientation;                      // +0x60
    uint32_t pad84[(0xa8 - 0x84) / 4];
    cSPMatrix3 mBaseOrientation;                  // +0xa8
    uint32_t padcc[(0x33c - 0xcc) / 4];
    AutoRefCount<cSPEditorBlock> mParent;         // +0x33c
    BlockVec mChildren;                           // +0x340
    uint32_t pad348[(0x3e0 - 0x348) / 4];
    AutoRefCount<cSPEditorBlock> mPinTarget;      // +0x3e0
    uint32_t pad3e4[2];
    AutoRefCount<cSPEditorBlockModel> mModel;     // +0x3ec
    AutoRefCount<cCounted> mSocket;               // +0x3f0
    uint32_t pad3f4[(0xdc8 - 0x3f4) / 4];
    Bitset60 mFlags;                              // +0xdc8
    cSPEditorBlockModel* GetModel() const { return mModel; }
    bool GetBooleanAttribute(uint32_t id) const { return mFlags.test(id); }
    void SetBooleanAttribute(int id, bool v);     // 0x00435a10
    float GetSnapScale();                         // 0x0043eed0
    void SetVec194(cSPVector3 v);                     // 0x00451330
    void FUN_44ba20(int a, int b);                // 0x0044ba20
    void PinBlock(cSPEditorBlock* b);             // 0x00438700
    void RecursiveFlagA();                        // 0x0044ede0
    bool FUN_448c10();                            // 0x00448c10
    int GetSymmetryIndex();                       // 0x0044f220
    int CalculateSymmetrySign();                  // 0x0044f240
    void SetModelBasedOnSymmetrySign(int sign, bool mirror, bool recurse, int a, int b);  // 0x00439110
    bool FUN_435c80();                            // 0x00435c80
};

struct cSPEditorLimbStructure {
    uint32_t pad[0x58 / 4];
    cSPEditorLimbStructure();                     // 0x00488850
    ~cSPEditorLimbStructure();                    // 0x00488900
    void Init(cSPEditorBlock* root, int a, int b);   // 0x004891a0
    void FUN_48c030();                            // 0x0048c030
    void FixAllJoints();                          // 0x00489ae0
    void Rebuild();                               // 0x0048a4c0
    void FUN_488980();                            // 0x00488980
};

struct MsgArg { union { void* p; float f; }; uint32_t pad; };
struct BlockSnapMessage {
    MsgArg mArgs[3];
    int mFlags;
    MsgArg& operator[](int i) { return mArgs[i]; }
};
struct IMessageServer {
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void Send(uint32_t id, void* data, int b);   // +0x14
};
struct IMessageManager { void Post(uint32_t id, int a, void* data, int b); };   // 0x0045ae40

IMessageServer* MessageServer();                  // 0x0067dcc0
IMessageManager* MessageManager();                // 0x00401050
int CountSnapBlocks(cSPEditorBlock* b, int flag); // 0x00491350
cSPMatrix3 BuildSymmetricOrientation(cSPMatrix3 m, int mode);   // 0x004a25f0
void RepinBlockToTorso(cSPEditorBlock* b, Vec3 pos, cSPMatrix3 m, int flag);   // 0x0049fbd0
void SetSymmetricBlocksUIState(cSPEditorBlock* b, int a, int c);   // 0x004a7f30
bool FUN_4a7e60(cSPEditorBlock* b);               // 0x004a7e60
bool FUN_4a7dd0(cSPEditorBlock* b);               // 0x004a7dd0
extern const float kNegHalfPi;                    // 0x013ef57c (-pi/2)

// @ 0x4a29a0
void SnapBlockToSocket(cSPEditorBlock* block, int unused, cSPEditorBlock* target)
{
    cSPEditorModel* model = block->mpEditorModel;
    cSPEditorBlockModel* blockModel = block->GetModel();
    bool unusedFlag = false;
    bool anyPaintable = false;
    float scale = 1.0f;
    if (target && target->mSocket) {
        BlockVec& children = target->mChildren;
        int count = 0;
        bool notify = false;
        for (int i = 0, n = children.size(); i < n; i++) {
            if (children[i]->mModel) {
                scale = children[i]->GetSnapScale();
                children[i]->SetVec194(children[i]->mPosition);
            }
            if (children[i]->GetBooleanAttribute(0xc)) {
                children[i]->mModel->SetState(1, 0);
                if (!children[i]->GetBooleanAttribute(0xb)) {
                    children[i]->FUN_44ba20(1, 1);
                    if (children[i]->GetBooleanAttribute(0x2d))
                        anyPaintable = true;
                    if (!children[i]->GetBooleanAttribute(0x14))
                        notify = true;
                    count += CountSnapBlocks(children[i], 1);
                }
            }
        }
        if (notify) {
            BlockSnapMessage msg;
            msg.mFlags = 0;
            msg[0].p = block;
            msg[1].p = target;
            msg[2].f = (float)count;
            MessageServer()->Send(0x48e5911, &msg, 0);
        }
        CountedRef<cCounted> socket(target->mSocket);
        target->PinBlock(block);
        block->RecursiveFlagA();
        block->SetBooleanAttribute(0xc, true);
        float delta = scale - block->GetSnapScale();
        if (block->mModel)
            UpdateModelPaint(block->mModel, delta);
        Vec3 offset = socket->mPosition - blockModel->GetPosition();
        Vec3 pos = socket.GetPosition();
        cSPMatrix3 orient(block->mBaseOrientation);
        bool mirror = false;
        if (block->GetBooleanAttribute(4)) {
            if (block->GetBooleanAttribute(0xb)) {
                if (!block->FUN_448c10()) {
                    cSPMatrix3 m(target->mOrientation);
                    if (target->GetBooleanAttribute(8)) {
                        cSPTransform xf;
                        xf.SetRotation(m);
                        Vec3 axis;
                        axis.x = m.r[0].x;
                        axis.y = m.r[0].y;
                        axis.z = m.r[0].z;
                        xf.PreRotate(axis, kNegHalfPi);
                        m = xf.GetRotation();
                    }
                    orient = m;
                } else {
                    orient = block->mBaseOrientation;
                    mirror = true;
                }
            } else if (block->GetBooleanAttribute(0x2c)) {
                orient = BuildSymmetricOrientation(target->mOrientation, target->GetSymmetryIndex());
            } else {
                orient = target->mOrientation;
            }
        } else if (!block->GetBooleanAttribute(0xb)) {
            mirror = true;
            orient = block->mBaseOrientation;
        } else {
            mirror = true;
            orient = block->mBaseOrientation;
        }
        RepinBlockToTorso(block, pos, orient, 0);
        if (model->IsUsingSymmetry()) {
            int sign = block->CalculateSymmetrySign();
            if (sign != block->GetSymmetryIndex()) {
                bool mirrorOrientation = mirror;
                block->SetModelBasedOnSymmetrySign(sign, mirrorOrientation, true, 0, 0);
                blockModel = block->GetModel();
            }
        }
        MessageManager()->Post(0x3f1bf58, 0, block, 0);
        blockModel->SetState(1, 0);
        if (model->IsUsingSymmetry()) {
            cSPEditorBlock* pin = block->mPinTarget;
            if (pin && pin->mModel)
                pin->mModel->SetState(1, 0);
        }
        SetSymmetricBlocksUIState(block, 0, 0);
        if (target->GetBooleanAttribute(0xb) && FUN_4a7e60(target) && !FUN_4a7dd0(target)) {
            cSPEditorLimbStructure limb;
            cSPEditorLimbStructure pinLimb;
            limb.Init(block, 0, 0);
            limb.FUN_48c030();
            if (!block->FUN_435c80()) {
                pinLimb.Init(block->mPinTarget, 0, 0);
                pinLimb.FUN_48c030();
            }
            limb.FixAllJoints();
            limb.Rebuild();
            if (!block->FUN_435c80()) {
                pinLimb.FixAllJoints();
                pinLimb.Rebuild();
                pinLimb.FUN_488980();
            }
            limb.FUN_488980();
        }
        if (block->GetBooleanAttribute(10))
            block->SetBooleanAttribute(9, true);
        if (block->mParent && block->mParent->GetBooleanAttribute(10))
            block->mParent->SetBooleanAttribute(10, true);
    }
}
