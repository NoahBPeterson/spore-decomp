// Slice s004c38e0: SP::cSPEditorSkinManager::Update / UpdatePaintedSkin and
// cSPEditorSkinManager::CreateSkinObject (/Od).
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
#include "types.h"

#pragma pack(push, 4)

// The editor's six-argument operator new (0x00f473a0).
void* __cdecl operator new(unsigned int size, const char* name, int, int, int, int);
extern "C" const char kEditorAllocName[];   // 0x013eb430 ?kEditorAllocName@@3QBDB

namespace eastl {
template <int N> class bitset {
public:
    uint32_t mWord[(N + 31) / 32];
    uint32_t& DoGetWord(uint32_t i) { return mWord[i >> 5]; }
    uint32_t DoGetWordValue(uint32_t i) const { return mWord[i >> 5]; }
    bool test(uint32_t i) const {
        if (i < N)
            return (DoGetWordValue(i) & (1 << (i % 32))) != 0;
        return false;
    }
};
} // namespace eastl

namespace SP {

struct AllocTag { AllocTag() {} };

class cSPEditorBlock;
class cSPEditorModel;
class cSPEditorSkinPart;
class cIModelWorld;
class cPaintRequest;

struct SkinElem;
struct SkinModel;
struct MatInfo;

// Helper entry points (defined in other translation units; addresses from the map).
bool CollectPartsRec(cSPEditorBlock* block, void* parts);        // 0x0048ccf0
uint32_t HashModelType(uint32_t modelType);                      // 0x004bb860
void FUN_00425990();                                             // free (vector teardown)
void FUN_004c64d0();                                             // fixed-vector teardown

// ---------------------------------------------------------------------------
// Small containers modelled after the retail stack objects.
// ---------------------------------------------------------------------------

// eastl::fixed_vector<uint8_t,16> (0x28 bytes, inline buffer at +0x18)
class FixedVec16 {
public:
    FixedVec16();                                                // 0x004ce9d0
    void Init(int count, uint8_t* value);                        // 0x004c60e0
    ~FixedVec16() { for (uint8_t* p = mpBegin; p < mpEnd; ++p) {} FUN_004c64d0(); }
    void FUN_004c64d0();                                         // 0x004c64d0
    uint8_t* mpBegin;                                            // +0x00
    uint8_t* mpEnd;                                              // +0x04
    uint8_t* mpCapacity;                                         // +0x08
    uint32_t mAlloc0;                                            // +0x0c
    uint32_t mAlloc4;                                            // +0x10
    uint32_t mAlloc8;                                            // +0x14
    uint8_t  mBuffer[16];                                        // +0x18
};

// eastl::fixed_vector<cSPEditorBlock*,128> (0x218 bytes, inline buffer at +0x18)
class VSet128 {
public:
    VSet128(const AllocTag& a);                                  // 0x00540470
    void Init();                                                 // 0x004c5e30
    void push_back(const uint32_t& v);                           // 0x00454860
    ~VSet128() { for (uint32_t* p = mpBegin; p < mpEnd; ++p) {} FUN_00425990(); }
    void FUN_00425990();                                         // 0x00425990
    uint32_t* mpBegin;                                           // +0x00
    uint32_t* mpEnd;                                             // +0x04
    uint32_t* mpCapacity;                                        // +0x08
    uint32_t mAlloc0;                                            // +0x0c
    uint32_t mAlloc4;                                            // +0x10
    uint32_t mAlloc8;                                            // +0x14
    uint32_t mBuffer[128];                                       // +0x18
};

// eastl::fixed_vector<cSPEditorBlock*,64> (0x118 bytes, inline buffer at +0x18)
class VSet64 {
public:
    VSet64(const AllocTag& a);                                   // 0x00540470
    void Init();                                                 // 0x004c5e70
    void push_back(const uint32_t& v);                           // 0x00454860
    ~VSet64();                                                   // 0x004e1bf0
    uint32_t* mpBegin;                                           // +0x00
    uint32_t* mpEnd;                                             // +0x04
    uint32_t* mpCapacity;                                        // +0x08
    uint32_t mAlloc0;                                            // +0x0c
    uint32_t mAlloc4;                                            // +0x10
    uint32_t mAlloc8;                                            // +0x14
    uint32_t mBuffer[64];                                        // +0x18
};

// SP::SimpleVector<uint32_t>: three pointers only (0x0c bytes)
class SimpleVec {
public:
    void push_back(const uint32_t& v);                           // 0x00454860
    ~SimpleVec() { for (uint32_t* p = mpBegin; p < mpEnd; ++p) {} FUN_00425990(); }
    void FUN_00425990();                                         // 0x00425990
    uint32_t* mpBegin;                                           // +0x00
    uint32_t* mpEnd;                                             // +0x04
    uint32_t* mpCapacity;                                        // +0x08
};

// ---------------------------------------------------------------------------
// Editor objects touched by these functions.
// ---------------------------------------------------------------------------

// cMWModel-ish container behind cSkinObject::+0xb8.
struct SkinElem {
    uint32_t mPad0;                                              // +0x00
    uint16_t mType;                                              // +0x04 (0x210 = texture slot)
    uint16_t mPad6;                                              // +0x06
    void*    mData;                                              // +0x08
};

struct SkinElemVector {
    SkinElem** mpBegin;                                          // +0x00
    SkinElem** mpEnd;                                            // +0x04
    SkinElem** mpCapacity;                                       // +0x08
    bool empty();                                                // 0x00526430
};

struct SkinModel {
    uint32_t mPad0;                                              // +0x00
    uint32_t mPad4;                                              // +0x04
    SkinElemVector mElems;                                       // +0x08
};

struct MatInfo {
    uint32_t mPad0;                                              // +0x00
    uint32_t mPad4;                                              // +0x04
    SkinElemVector mElems;                                       // +0x08
};

struct SkinResource {
    uint32_t mPad0[6];                                           // +0x00
    uint32_t mModelType;                                         // +0x18
};

struct PaintData {
    uint8_t mTag;                                                // +0x00
    uint8_t mPad[3];
    float   mA;                                                  // +0x04
    float   mB;                                                  // +0x08
    uint32_t mPadC;                                              // +0x0c
    float   mC;                                                  // +0x10
};

class cPaintRequest {
public:
    uint8_t mPad0[0x70];
    float   mA;                                                  // +0x70
    float   mB;                                                  // +0x74
    float   mC;                                                  // +0x78
};

class cSPEditorSkinPart {
public:
    cSPEditorSkinPart();                                         // 0x004cc190
    // The second (dynamic-draw) vtable lives at +0xbc; ref-counting goes through it.
    struct DrawBase {
        virtual int AddRef();
        virtual int Release();
    };

    void SetDrawMaterial(uint32_t id);                           // 0x004cd020
    void SetModel(uint32_t instance, uint32_t group, bool allowHighQuality); // 0x004cc470
    void SetSkinResolution(float realtime, float highQuality);   // 0x004cd060
    void Update(uint32_t* blocks, bool forceHighQuality);        // 0x004cc540
    void UpdateSceneObject(cIModelWorld* world);                 // 0x004cc7d0
    bool IsHighQualityPending();                                 // 0x004cc760
    void RestartQualityTimer();                                  // 0x004cc6f0
    void SetVisible(bool visible);                               // 0x004cca40
    void* GetSceneObject() { return mModel; }
    void AddDrawRef() { mDraw.AddRef(); }
    void DrawRelease() { mDraw.Release(); }

    uint8_t mPad0[8];
    SkinResource* mResource;                                     // +0x08
    uint8_t mPad1[0xb8 - 0x0c];
    SkinModel* mSkinModel;                                       // +0xb8
    DrawBase mDraw;                                              // +0xbc (vptr)
    uint8_t mPadDraw[0xe0 - 0xc0];
    void* mModel;                                                // +0xe0
    void* mMatBegin;                                             // +0xe4
    void* mMatEnd;                                               // +0xe8
    void* mMatCapacity;                                          // +0xec
    uint8_t mPadEnd[0x130 - 0xf0];
};

template <class T> class AutoRefCount {
public:
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* const& p) : mpObject(p) { if (mpObject) mpObject->AddDrawRef(); }
    AutoRefCount(const AutoRefCount& o) : mpObject(o.mpObject) {
        if (mpObject) mpObject->AddDrawRef();
    }
    ~AutoRefCount() { if (mpObject) mpObject->DrawRelease(); }
    AutoRefCount& operator=(T* const& p) {
        if (p != mpObject) {
            T* old = mpObject;
            if (p) p->AddDrawRef();
            mpObject = p;
            if (old) old->DrawRelease();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    T* mpObject;
};

// Paint request holder (only mpObject is ever read here).
struct PaintRequestSlot {
    cPaintRequest* mpObject;
    cPaintRequest* operator->() const { return mpObject; }
};

struct LimbPair {
    cSPEditorBlock* first;                                       // +0x00
    AutoRefCount<cSPEditorSkinPart> second;                      // +0x04
};

struct LimbVector {
    LimbPair* mpBegin;                                           // +0x00
    LimbPair* mpEnd;                                             // +0x04
    LimbPair* mpCapacity;                                        // +0x08
    uint32_t  mAllocName;                                        // +0x0c
    uint32_t  mAllocFlags;                                       // +0x10
    void push_back(const LimbPair& v);                           // 0x004c5fc0
    int size() const { return (int)(mpEnd - mpBegin); }
    LimbPair& operator[](int i) { return mpBegin[i]; }
};

class cSPEditorBlock {
public:
    bool Paint();                                                // 0x0044c030
    bool HasAnyBlockFlag();                                      // 0x00435d40
    void SetFlag(int flag, bool value);                          // 0x00435a10
    uint8_t mPad0[0x33c];
    void*   mField33c;                                           // +0x33c
    uint8_t mPad1[0xdc8 - 0x340];
    eastl::bitset<60> mFlags;                                    // +0xdc8
};

class cSPEditorModel {
public:
    uint32_t GetBlockCount() const;                              // 0x004accf0
    uint8_t mPad0[0x18];
    cSPEditorBlock** mpBlockList;                                // +0x18
    uint8_t mPad1[0x50 - 0x1c];
    bool mFlag50;                                                // +0x50
    uint8_t mPad2[0x58 - 0x51];
    uint32_t mName58;                                            // +0x58
};

class cSPEditorSkinManager {
public:
    void UpdateTorso(uint32_t flags, int value);                 // 0x004c3230
    void Update(uint32_t unused, bool paintAll, uint32_t p4, uint32_t p5); // 0x004c38e0
    void UpdatePaintedSkin();                                    // 0x004c4290
    cSPEditorSkinPart* CreateSkinObject(cSPEditorBlock* block, uint32_t instance); // 0x004c44c0
    void* GetSceneObject(uint32_t which);                        // 0x004c45d0

    uint8_t mPad0[0x10];
    cSPEditorModel* mModel;                                      // +0x10
    cIModelWorld*   mSceneObjectModelWorld;                      // +0x14
    AutoRefCount<cSPEditorSkinPart> mTorsoSkin;                  // +0x18
    AutoRefCount<cSPEditorSkinPart> mCompleteSkin;               // +0x1c
    uint8_t mPad20[0x48 - 0x20];                                 // +0x20 transforms/pointers
    LimbVector mLimbSkins;                                       // +0x48
    PaintRequestSlot mPaintRequest;                              // +0x5c
    uint32_t mDefaultMaterial;                                   // +0x60
    uint8_t  mTextureKey[0x70 - 0x64];                           // +0x64
    void*    mDiffuseTex;                                        // +0x70
    void*    mNormalTex;                                         // +0x74
    float    mPaintResolution;                                   // +0x78
    float    mRealtimeResolution;                                // +0x7c
    float    mHighQualityResolution;                             // +0x80
    bool     mPaintEnabled;                                      // +0x84
    bool     mHairEnabled;                                       // +0x85
};

// @ 0x004c45d0
void* cSPEditorSkinManager::GetSceneObject(uint32_t which)
{
    switch (which) {
    case 0:
        return mTorsoSkin->GetSceneObject();
        break;
    case 1:
        return mCompleteSkin->GetSceneObject();
        break;
    }
    return 0;
}

// @ 0x004c38e0
void cSPEditorSkinManager::Update(uint32_t unused, bool paintAll, uint32_t p4, uint32_t p5)
{
    (void)unused;
    UpdateTorso(p4, p5);
    if (mModel != 0) {
        uint32_t nBlocks = mModel->GetBlockCount();
        cSPEditorBlock** blockList = mModel->mpBlockList;
        uint8_t anyFlag = 0;
        AllocTag alloc;
        VSet128 blocks(alloc);
        blocks.Init();
        FixedVec16 counts;
        uint8_t countInit = 0;
        counts.Init(mLimbSkins.size(), &countInit);

        for (uint32_t i = 0; i < nBlocks; i++) {
            cSPEditorBlock* block = blockList[i];
            if (!block->Paint())
                continue;

            if (block->HasAnyBlockFlag()) {
                uint8_t flag = 0;
                if (block->mFlags.test(10))
                    flag = block->mFlags.test(9) ? 1 : 0;
                anyFlag |= flag;
                blocks.push_back((uint32_t&)block);
                continue;
            }

            if (block->mField33c != 0)
                continue;
            if (!block->mFlags.test(11))
                continue;
            if (!block->mFlags.test(10))
                continue;

            int found = -1;
            int freeSlot = -1;
            int nSkins = mLimbSkins.size();
            for (int j = 0; found == -1 && j < nSkins; j++) {
                if (mLimbSkins[j].first == block)
                    found = j;
                else if (mLimbSkins[j].first == 0)
                    freeSlot = j;
            }

            if (found == -1) {
                if (freeSlot == -1) {
                    freeSlot = mLimbSkins.size();
                    mLimbSkins.push_back(LimbPair());
                    mLimbSkins[freeSlot].second = new (kEditorAllocName, 0, 0, 0, 0) cSPEditorSkinPart;
                    mLimbSkins[freeSlot].second->SetDrawMaterial(mDefaultMaterial);
                    mLimbSkins[freeSlot].second->SetModel(
                        (uint32_t)freeSlot - 0x70020768, 0xefeb80ec, true);
                    mLimbSkins[freeSlot].second->UpdateSceneObject(mSceneObjectModelWorld);
                    mLimbSkins[freeSlot].second->SetVisible(false);
                }
                mLimbSkins[freeSlot].first = block;
                mLimbSkins[freeSlot].second->SetVisible(true);
                found = freeSlot;
            }

            counts.mpBegin[found] = 1;

            AllocTag alloc2;
            VSet64 parts(alloc2);
            parts.Init();
            parts.push_back((uint32_t&)block);
            if (CollectPartsRec(block, &parts) ||
                mLimbSkins[found].second->IsHighQualityPending())
                mLimbSkins[found].second->Update((uint32_t*)&parts, false);
        }

        if (anyFlag)
            mCompleteSkin->RestartQualityTimer();
        if (mCompleteSkin->IsHighQualityPending() || mModel->mFlag50 || paintAll)
            anyFlag = 1;
        if (anyFlag) {
            mCompleteSkin->Update((uint32_t*)&blocks, paintAll);
            mCompleteSkin->UpdateSceneObject(mSceneObjectModelWorld);
            mCompleteSkin->mResource->mModelType = mModel->mName58;
        }

        int nSkins = mLimbSkins.size();
        for (int i = 0; i < nSkins; i++) {
            if (mLimbSkins[i].first != 0 && counts.mpBegin[i] == 0) {
                mLimbSkins[i].first = 0;
                mLimbSkins[i].second->SetVisible(false);
            }
        }
        for (uint32_t i = 0; i < nBlocks; i++)
            blockList[i]->SetFlag(9, false);
        mModel->mFlag50 = 0;
    }
    UpdatePaintedSkin();
}

// @ 0x004c4290
void cSPEditorSkinManager::UpdatePaintedSkin()
{
    if (!mPaintEnabled)
        return;
    if (mPaintRequest.mpObject == 0)
        return;
    if (mCompleteSkin.mpObject == 0)
        return;

    uint32_t type = HashModelType(mCompleteSkin->mResource->mModelType);
    uint8_t tag;
    if (type == 0x438f6347)
        tag = 5;
    else if (type == 0x3d97a8e4)
        tag = 4;
    else
        tag = 7;

    SkinModel* model = mCompleteSkin->mSkinModel;
    if (model != 0) {
        if (!model->mElems.empty()) {
            SkinElem* elem = model->mElems.mpBegin[0];
            if (elem->mType == 0x210) {
                PaintData* data = (PaintData*)elem->mData;
                data->mTag = tag;
                data->mA = mPaintRequest->mA;
                data->mB = mPaintRequest->mB;
                data->mC = mPaintRequest->mC;
            }
        }
    }

    int count = (int)((char*)mCompleteSkin->mMatEnd - (char*)mCompleteSkin->mMatBegin) >> 2;
    for (int i = 0; i < count; i++) {
        MatInfo* info = ((MatInfo**)mCompleteSkin->mMatBegin)[i];
        if (info == 0)
            continue;
        if (info->mElems.empty())
            continue;
        SkinElem* elem = info->mElems.mpBegin[0];
        if (elem->mType != 0x210)
            continue;
        PaintData* data = (PaintData*)elem->mData;
        data->mTag = tag;
        data->mA = mPaintRequest->mA;
        data->mB = mPaintRequest->mB;
        data->mC = mPaintRequest->mC;
    }
}

// @ 0x004c44c0
cSPEditorSkinPart* cSPEditorSkinManager::CreateSkinObject(cSPEditorBlock* block, uint32_t instance)
{
    cSPEditorSkinPart* part = new (kEditorAllocName, 0, 0, 0, 0) cSPEditorSkinPart;
    part->SetDrawMaterial(0xca9bb36f);
    part->SetModel(instance, 0xefeb80ec, false);
    part->SetSkinResolution(mRealtimeResolution, mHighQualityResolution);

    SimpleVec blocks;
    blocks.mpBegin = 0;
    blocks.mpEnd = 0;
    blocks.mpCapacity = 0;
    blocks.push_back((uint32_t&)block);
    CollectPartsRec(block, &blocks);
    part->Update((uint32_t*)&blocks, false);
    cIModelWorld* world = *(cIModelWorld**)((char*)block + 0x18);
    part->UpdateSceneObject(world);
    return part;
}

} // namespace SP

#pragma pack(pop)
