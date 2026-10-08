// Slice s004c3230: SP::cSPEditorSkinManager::UpdateTorso (1702 bytes, /Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
//
// Rebuilds the cached torso state when the set of torso blocks (blocks with attribute 7 that
// pass IsValid) changed: snapshots their pointers and transforms (scale, translation,
// rotation) into the manager, refreshes the torso skin mesh and scene object, then sets the
// torso skin's visibility / draw material from the two paint flags.
#include "types.h"
#include <new>

#pragma pack(push, 4)

template <int N> inline void ScratchSlots() { uint32_t s[N]; }

namespace SP {

struct Vector3 {
    float x, y, z;
    Vector3() {}
};
struct Matrix3 {
    float m[9];
};
bool Vector3_NotEqual(const Vector3& a, const Vector3& b);   // 0x0041dd30 (cdecl)
bool Matrix3_NotEqual(const Matrix3& a, const Matrix3& b);   // 0x0041dd90 (cdecl, operator!=<>)

template <uint32_t N> struct bitset {
    uint32_t mWord[(N + 31) / 32];
    uint32_t DoGetWord(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const
    {
        if (i < N)
            return (DoGetWord(i) & (1u << (i % 32))) != 0;
        return false;
    }
};

class cSPEditorBlock {
public:
    char pad0[0x48];
    Vector3 mPosition;       // +0x48
    char pad54[0x60 - 0x54];
    Matrix3 mOrientation;    // +0x60
    char pad84[0x1d8 - 0x84];
    float mScale;            // +0x1d8
    char pad1dc[0xdc8 - 0x1dc];
    bitset<60> mFlags;      // +0xdc8

    bool IsValid();          // 0x0044c030
    const Vector3& GetPosition() { return mPosition; }
    const Matrix3& GetOrientation() { return mOrientation; }
    float GetScale() { return mScale; }
};

template <class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct BlockRef {
    cSPEditorBlock* mpObject;
    operator cSPEditorBlock*() const { return mpObject; }
};

struct BlockList {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** begin() { return mpBegin; }
};

class cSPEditorModel {
public:
    char pad0[0x18];
    BlockList mBlockList;    // +0x18
    int GetBlockCount();     // 0x004accf0
    cSPEditorBlock** begin() { return mBlockList.begin(); }
};

class cIModelWorld;

class cSPEditorSkinPart {
public:
    struct BlockVec;
    void Update(BlockVec& blocks, bool forceHighQuality);   // 0x004cc540
    void UpdateSceneObject(cIModelWorld* world);            // 0x004cc7d0
    void SetVisible(bool visible);                          // 0x004cca40
    void SetDrawMaterial(uint32_t id);                      // 0x004cd020
};

struct Alloc {
    Alloc() {}
};
struct TagFalse {
    TagFalse() {}
};

// eastl::fixed_vector<cSPEditorBlock*, 40>
struct __declspec(align(4)) cSPEditorSkinPart::BlockVec {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** mpEnd;
    cSPEditorBlock** mpCapacity;
    uint32_t mFixedPad[2];
    uint32_t mOverflow;
    cSPEditorBlock* mBuffer[40];
    void Init(const Alloc& tag);                       // 0x00540470
    BlockVec()
    {
        Init(Alloc());
        InitFixed();
    }
    void InitFixed();                                  // 0x004c5df0
    void FreeOverflow();                               // 0x00425990 (VectorBase dtor)
    ~BlockVec()
    {
        for (cSPEditorBlock** p = mpBegin; p < mpEnd; ++p) {
        }
        FreeOverflow();
        ScratchSlots<3>();
    }
    void PushBackOutOfLine(cSPEditorBlock* const& v);  // 0x00454860
    void push_back(cSPEditorBlock* const& v)
    {
        PushBackOutOfLine(v);
        ScratchSlots<2>();
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock** begin() { return mpBegin; }
    cSPEditorBlock** end() { return mpEnd; }
    cSPEditorBlock*& operator[](int n)
    {
        cSPEditorBlock** p = mpBegin + n;
        return *p;
    }
};
typedef cSPEditorSkinPart::BlockVec BlockVec;

struct cSPTransform {  // size 0x38
    unsigned short mFlags;              // +0x0
    unsigned short mModificationCount;  // +0x2
    Vector3 mTranslation;               // +0x4
    float mScale;                       // +0x10
    Matrix3 mRotation;                  // +0x14

    float GetScale() { return mScale; }
    void SetScale(float s) { mScale = s; mModificationCount++; }
    void SetTranslation(const Vector3& v)
    {
        mTranslation = v;
        mFlags |= 4;
        mModificationCount++;
    }
    void SetRotation(const Matrix3& m)
    {
        mRotation = m;
        mFlags |= 2;
        mModificationCount++;
    }
};

struct TransformVec {
    cSPTransform* mpBegin;
    cSPTransform* mpEnd;
    cSPTransform* mpCapacity;
    uint32_t mAlloc;
    void erase(cSPTransform* first, cSPTransform* last);   // 0x004238c0
    void clear() { erase(mpBegin, mpEnd); }
    void EmplaceBack();                                    // 0x004c5eb0 (out of line)
    void push_back_default()
    {
        EmplaceBack();
        ScratchSlots<16>();
    }
    cSPTransform& operator[](int i) { return mpBegin[i]; }
    cSPTransform& back() { return mpEnd[-1]; }
};

struct PtrVec {
    cSPEditorBlock** mpBegin;
    cSPEditorBlock** mpEnd;
    cSPEditorBlock** mpCapacity;
    uint32_t mAlloc;
    void DoAssignFromIterator(cSPEditorBlock** first, cSPEditorBlock** last, TagFalse tag);   // 0x004d04f0
    // eastl::vector::assign(first, last) -> DoAssign(..., is_integral) -> DoAssignFromIterator(...):
    // the two declined inline levels leave two dead empty-tag temporaries in the caller's frame.
    void assign(cSPEditorBlock** first, cSPEditorBlock** last)
    {
        TagFalse unusedIntegralTag;
        TagFalse unusedCategoryTag;
        DoAssignFromIterator(first, last, TagFalse());
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    cSPEditorBlock*& operator[](int n)
    {
        cSPEditorBlock** p = mpBegin + n;
        return *p;
    }
};

struct TorsoFlags {
    bool a;
    bool b;
};

class cSPEditorSkinManager {
public:
    char pad0[0xc];
    void* mApp;                       // +0xc
    cSPEditorModel* mModel;           // +0x10
    cIModelWorld* mSceneObjectModelWorld;  // +0x14
    AutoRefCount<cSPEditorSkinPart> mTorsoSkin;   // +0x18
    void* mCompleteSkin;              // +0x1c
    TransformVec mPreviousTorsoBlockTransforms;   // +0x20
    uint32_t pad30;                   // +0x30
    PtrVec mPreviousTorsoBlockPointers;           // +0x34 (retail layout)

    void UpdateTorso(TorsoFlags flags, int x);
};

// @ 0x004c3230
void cSPEditorSkinManager::UpdateTorso(TorsoFlags flags, int x)
{
    if (mModel == 0 || mTorsoSkin == 0 || mSceneObjectModelWorld == 0)
        return;
    {
        BlockVec torsoList;
        int modelBlockCount = mModel->GetBlockCount();
        cSPEditorBlock** modelBlockList = mModel->begin();
        for (int iBlock = 0; iBlock < modelBlockCount; iBlock++) {
            cSPEditorBlock* pBlock = modelBlockList[iBlock];
            if (pBlock->IsValid() && pBlock->mFlags.test(7))
                torsoList.push_back(pBlock);
        }

        bool dirty = false;
        if (torsoList.size() == mPreviousTorsoBlockPointers.size()) {
            for (int index = 0, cnt = torsoList.size(); index < cnt; index++) {
                if (mPreviousTorsoBlockPointers[index] != torsoList.mpBegin[index]) {
                    dirty = true;
                    break;
                }
                cSPTransform* transform = mPreviousTorsoBlockTransforms.mpBegin + index;
                if (transform->GetScale() != torsoList[index]->GetScale() ||
                    Vector3_NotEqual(transform->mTranslation, torsoList[index]->GetPosition()) ||
                    Matrix3_NotEqual(transform->mRotation, torsoList[index]->GetOrientation())) {
                    dirty = true;
                    break;
                }
            }
        } else {
            dirty = true;
        }

        if (dirty) {
            mPreviousTorsoBlockPointers.assign(torsoList.begin(), torsoList.end());
            mPreviousTorsoBlockTransforms.clear();
            for (int q = 0, num = torsoList.size(); q < num; q++) {
                mPreviousTorsoBlockTransforms.push_back_default();
                mPreviousTorsoBlockTransforms.back().SetScale(torsoList[q]->GetScale());
                mPreviousTorsoBlockTransforms.back().SetTranslation(torsoList[q]->GetPosition());
                mPreviousTorsoBlockTransforms.back().SetRotation(torsoList[q]->GetOrientation());
            }
            mTorsoSkin->Update(torsoList, false);
            mTorsoSkin->UpdateSceneObject(mSceneObjectModelWorld);
        }

        uint32_t materialId = 0xca9bb36f;
        mTorsoSkin->SetVisible(flags.b || flags.a);
        if (flags.b && flags.a)
            materialId = 0xc276b918;
        else if (flags.b)
            materialId = 0x5097cfd3;
        else if (flags.a)
            materialId = 0x154a1133;
        mTorsoSkin->SetDrawMaterial(materialId);
    }
}

} // namespace SP

#pragma pack(pop)
