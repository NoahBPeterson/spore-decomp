// slice s0057af00 -- SP::cAppModeEditorBase::Pick (complete, not byte-exact)
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
//
// Mouse picking for the creature-style editors. Casts a camera ray through the
// cursor and picks, in order of preference:
//   1. an overdraw handle (morph/deform handles drawn on top of the model),
//   2. otherwise a rigblock or handle model, preferring a handle in front of
//      the rigblock (ball connectors only when they belong to that rigblock),
//   3. a block: vertebra first, then the closest of rigblock hit and skin hit.
// The model pick and the block pick are then arbitrated by distance from the
// ray start. Layouts follow the retail binary (ModAPI cEditor / EditorRigblock).
#include "types.h"

#define FLT_MAX_VALUE 3.402823466e+38F

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

inline Vector3 operator-(const Vector3& a, const Vector3& b) { return Vector3(a.x - b.x, a.y - b.y, a.z - b.z); }

// a + (b - a) * t
inline Vector3 Lerp(const Vector3& a, const Vector3& b, float t)
{
    return Vector3((b.x - a.x) * t + a.x, (b.y - a.y) * t + a.y, (b.z - a.z) * t + a.z);
}

namespace SP { Vector3 normalized_safe(const Vector3& v); }   // 0x00449c20

// ---- EASTL bits --------------------------------------------------------------
struct bitset64 {                          // eastl::bitset<64>
    uint32_t mWord[2];
    __forceinline void set(uint32_t i)
    {
        if (i < 64)
            mWord[i >> 5] |= (1u << (i & 31));
    }
    __forceinline bool test(uint32_t i) const
    {
        if (i < 64)
            return (mWord[i >> 5] & (1u << (i & 31))) != 0;
        return false;
    }
};

struct UIntVector {                        // eastl::vector<uint32_t>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator;
};

inline uint32_t* find(uint32_t* first, uint32_t* last, const uint32_t& value)
{
    while ((first != last) && !(*first == value))
        ++first;
    return first;
}

// ---- COM-ish objects -----------------------------------------------------------
struct IUnknown32 {
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void* Cast(uint32_t iid);      // +0x0c
};

template <class T> struct AutoRefCount {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};

struct cSPEditorBlock;
struct cMWModel;

struct cSPEditorHandle {                   // obtained from cMWModel::mpOwner (IID 0x50a1fe5)
    enum { kIID = 0x50a1fe5 };
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual uint32_t GetHandleType();      // +0x10
    cSPEditorBlock* GetRigblock();         // 0x0047e6c0
    cMWModel* GetModel();                  // 0x0047e680
    int GetHandleState();                  // 0x0047ec20
};
enum { kHandleTypeBallConnector = 0x50e8e23 };

template <class T> __forceinline T* interface_cast_inline(const AutoRefCount<IUnknown32>& p)
{
    return p ? (T*)p->Cast(T::kIID) : 0;
}

namespace SP { namespace EditorUtils {
cSPEditorHandle* GetBoneForHandle(const AutoRefCount<IUnknown32>& owner);   // 0x004aa030 (interface_cast<cSPEditorHandle*>)
cSPEditorBlock* GetBlockForBallConnector(cMWModel* model, Vector3 pos);     // 0x00496bb0
bool IsBlockLocked(cSPEditorBlock* block);                                   // 0x004a6120
} }
cSPEditorBlock* interface_cast_block(const AutoRefCount<IUnknown32>& p);     // 0x004aa2a0 (interface_cast<cSPEditorBlock*>)

enum {
    kAttrIsVertebra = 7,
    kAttrIsPlantRoot = 8,
    kAttr0B = 0xb,
    kAttrIsNullBlock = 0x14,
};

struct cSPEditorBlock {
    char pad0[0x33c];
    cSPEditorBlock* mpParent;              // +0x33c
    cSPEditorBlock** mChildrenBegin;       // +0x340 (fixed_vector<AutoRefCount<cSPEditorBlock>, 8>)
    cSPEditorBlock** mChildrenEnd;         // +0x344
    char pad348[0x3ec - 0x348];
    cSPEditorHandle* mpBallConnectorHandle;   // +0x3ec
    char pad3f0[0xdc8 - 0x3f0];
    bitset64 mBooleanAttributes;           // +0xdc8
    bool TestAttribute(int i) const { return ((mBooleanAttributes.mWord[0] >> i) & 1) != 0; }
};

struct cMWModel {
    char pad0[0x44];
    bitset64 mGroupFlags;                  // +0x44
    char pad4c[0x64 - 0x4c];
    AutoRefCount<IUnknown32> mpOwner;      // +0x64
};

// ---- model world --------------------------------------------------------------
enum {
    kGroupDeformHandle = 0x1ba53ea,
    kGroupOverdraw = 0x22fff11,
    kGroupRotationRing = 0x31390732,
    kGroupRotationBall = 0x31390733,
    kGroupRotationHandle3 = 0x31390734,
    kGroupVertebra = 0x513cdfc1,
    kGroupBallConnector = 0x900c6cdd,
    kGroupRigblock = 0x9138fd8d,
};

struct FilterSettings {
    bitset64 requiredGroupFlags;           // +0x00
    bitset64 excludedGroupFlags;           // +0x08
    void* filterFunction;                  // +0x10
    uint8_t collisionMode;                 // +0x14
    uint8_t flags;                         // +0x15
    FilterSettings() : filterFunction(0), collisionMode(4), flags(1)
    {
        requiredGroupFlags.mWord[0] = 0; requiredGroupFlags.mWord[1] = 0;
        excludedGroupFlags.mWord[0] = 0; excludedGroupFlags.mWord[1] = 0;
    }
};

struct IModelManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual uint32_t GetGroupFlag(uint32_t groupID, int unk);   // +0x28
};

struct IModelWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual cMWModel* FindFirstModelAlongLine(const Vector3& p1, const Vector3& p2, float* pFactor,
                                              Vector3* pIntersection, Vector3* pUnk, FilterSettings& settings,
                                              int* pHitIndex, int* pUnk2);           // +0x24
};

struct cViewer {
    void GetCameraRay(float x, float y, Vector3* pStart, Vector3* pEnd);   // 0x007c4510
};

struct cIApp {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cViewer* GetViewer();          // +0x58
};

struct cSPEditorSkinManager {
    void* GetSkin(int index);              // 0x004c49e0
    bool PickSkin(int lod, Vector3 start, Vector3 dir, Vector3* pPos, Vector3* pNormal,
                  float* pDistance, bool bUnk);                              // 0x004c4a30
    cSPEditorBlock* GetBlockAtSkinPoint(int lod, Vector3 pos);              // 0x004c4d30
};

namespace SP {
IModelManager* ModelManager();             // 0x0067dd80
cIApp* App();                              // 0x0067dd10
}

// Result of an editor pick (0x1c bytes, returned by value).
struct EditorPickResult {
    cSPEditorBlock* mpBlock;               // +0x00
    cMWModel* mpModel;                     // +0x04
    Vector3 mPosition;                     // +0x08
    bool mbSkin;                           // +0x14
    int mHitIndex;                         // +0x18
    EditorPickResult() : mpBlock(0), mpModel(0), mPosition(0.0f, 0.0f, 0.0f), mbSkin(false), mHitIndex(-1) {}
};

__forceinline bool ModelInGroup(cMWModel* model, uint32_t flag) { return model->mGroupFlags.test(flag); }

namespace SP {

class cAppModeEditorBase {
public:
    char pad0[0x84];
    IModelWorld* mpMainModelWorld;         // +0x84
    char pad88[0xe9 - 0x88];
    bool mbPickVertebrae;                  // +0xe9 (ModAPI field_E9)
    char padea[0x150 - 0xea];
    cSPEditorSkinManager* mpSkinManager;   // +0x150
    char pad154[0x2f6 - 0x154];
    bool mbOnlyEditFromPalette;            // +0x2f6
    char pad2f7[0x320 - 0x2f7];
    UIntVector mEnabledManipulators;       // +0x320
    char pad330[0x3b8 - 0x330];
    void* mpPartsPalette;                  // +0x3b8

    bool IsBlockInPalette(cSPEditorBlock* block);   // 0x00577c40
    EditorPickResult Pick(float x, float y, bool bBlocksOnly);
};

// @ 0x0057af00
EditorPickResult cAppModeEditorBase::Pick(float x, float y, bool bBlocksOnly)
{
    EditorPickResult result;
    EditorPickResult blockPick;
    EditorPickResult modelPick;
    float modelDistSq = FLT_MAX_VALUE;
    float blockDistSq = FLT_MAX_VALUE;

    IModelManager* pModelManager = ModelManager();
    if (!pModelManager)
        return result;

    float t = 0.0f;
    int hitIndex = -1;
    Vector3 rayStart;
    Vector3 rayEnd;
    App()->GetViewer()->GetCameraRay(x, y, &rayStart, &rayEnd);

    if (!bBlocksOnly) {
        FilterSettings overdrawSettings;
        overdrawSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupOverdraw, 0));
        modelPick.mpModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &t, 0, 0, overdrawSettings, &hitIndex, 0);

        cSPEditorHandle* pOverdrawHandle;
        if (modelPick.mpModel
            && (pOverdrawHandle = interface_cast_inline<cSPEditorHandle>(modelPick.mpModel->mpOwner)) != 0
            && pOverdrawHandle->GetHandleState() != 1) {
            modelPick.mPosition = Lerp(rayStart, rayEnd, t);
            cSPEditorHandle* pHandle = interface_cast_inline<cSPEditorHandle>(modelPick.mpModel->mpOwner);
            if (pHandle->GetHandleType() == kHandleTypeBallConnector) {
                cSPEditorBlock* pBlock = EditorUtils::GetBlockForBallConnector(modelPick.mpModel, rayStart);
                if (pBlock && pBlock != pHandle->GetRigblock() && pBlock->mpBallConnectorHandle)
                    modelPick.mpModel = pBlock->mpBallConnectorHandle->GetModel();
            }
        } else {
            modelPick.mpModel = 0;

            FilterSettings rigblockSettings;
            rigblockSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupRigblock, 0));
            FilterSettings handleSettings;
            handleSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupDeformHandle, 0));
            handleSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupBallConnector, 0));
            handleSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupRotationBall, 0));
            handleSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupRotationRing, 0));
            handleSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupRotationHandle3, 0));

            float rigblockT = 0.0f;
            cMWModel* pRigblockModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &rigblockT, 0, 0, rigblockSettings, &hitIndex, 0);
            float handleT = 0.0f;
            cMWModel* pHandleModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &handleT, 0, 0, handleSettings, &hitIndex, 0);

            if (pHandleModel) {
                cSPEditorHandle* pBone;
                if (!pHandleModel->mpOwner
                    || ((pBone = EditorUtils::GetBoneForHandle(pHandleModel->mpOwner)) != 0 && pBone->GetHandleState() != 1)) {
                    if (!pRigblockModel || rigblockT > handleT) {
                        modelPick.mpModel = pHandleModel;
                        t = handleT;
                    } else if (ModelInGroup(pHandleModel, pModelManager->GetGroupFlag(kGroupBallConnector, 0))) {
                        // A ball connector behind its rigblock still wins when it belongs to that rigblock.
                        cSPEditorBlock* pConnectorBlock = EditorUtils::GetBoneForHandle(pHandleModel->mpOwner)->GetRigblock();
                        cSPEditorBlock* pRigblock = interface_cast_block(pRigblockModel->mpOwner);
                        if (pConnectorBlock->TestAttribute(kAttrIsNullBlock)
                            || pRigblock->TestAttribute(kAttrIsPlantRoot)
                            || pRigblock->TestAttribute(kAttr0B)) {
                            if (pConnectorBlock->mpParent == pRigblock
                                || (pRigblock && pRigblock->mpParent == pConnectorBlock->mpParent)) {
                                modelPick.mpModel = pHandleModel;
                                t = handleT;
                            }
                        } else if (pHandleModel->mpOwner.mpObject == pRigblockModel->mpOwner.mpObject) {
                            modelPick.mpModel = pHandleModel;
                            t = handleT;
                        }
                    }
                }
            }

            if (modelPick.mpModel && modelPick.mpModel->mpOwner) {
                if (ModelInGroup(modelPick.mpModel, pModelManager->GetGroupFlag(kGroupDeformHandle, 0))
                    || ModelInGroup(modelPick.mpModel, pModelManager->GetGroupFlag(kGroupRotationRing, 0))
                    || ModelInGroup(modelPick.mpModel, pModelManager->GetGroupFlag(kGroupRotationBall, 0))
                    || ModelInGroup(modelPick.mpModel, pModelManager->GetGroupFlag(kGroupBallConnector, 0))
                    || ModelInGroup(modelPick.mpModel, pModelManager->GetGroupFlag(kGroupRotationHandle3, 0)))
                    modelPick.mPosition = Lerp(rayStart, rayEnd, t);
            }
        }

        if (modelPick.mpModel)
            modelDistSq = (modelPick.mPosition.x - rayStart.x) * (modelPick.mPosition.x - rayStart.x)
                        + (modelPick.mPosition.y - rayStart.y) * (modelPick.mPosition.y - rayStart.y)
                        + (modelPick.mPosition.z - rayStart.z) * (modelPick.mPosition.z - rayStart.z);
    }

    bool bBallConnectorPicked = false;
    if (modelPick.mpModel)
        bBallConnectorPicked = interface_cast_inline<cSPEditorHandle>(modelPick.mpModel->mpOwner)->GetHandleType() == kHandleTypeBallConnector;

    if (!modelPick.mpModel || bBallConnectorPicked) {
        bool bBlockFound = false;
        if (mpSkinManager && mpSkinManager->GetSkin(1) && mbPickVertebrae) {
            FilterSettings vertebraSettings;
            vertebraSettings.requiredGroupFlags.set(ModelManager()->GetGroupFlag(kGroupVertebra, 0));
            cMWModel* pVertebra = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &t, 0, 0, vertebraSettings, &blockPick.mHitIndex, 0);
            if (pVertebra && pVertebra->mpOwner) {
                blockPick.mpBlock = interface_cast_block(pVertebra->mpOwner);
                blockPick.mPosition = Lerp(rayStart, rayEnd, t);
                bBlockFound = true;
            }
        }

        if (!blockPick.mpBlock) {
            FilterSettings blockSettings;
            blockSettings.requiredGroupFlags.set(ModelManager()->GetGroupFlag(kGroupRigblock, 0));
            if (mbPickVertebrae)
                blockSettings.requiredGroupFlags.set(ModelManager()->GetGroupFlag(kGroupVertebra, 0));
            Vector3 rigblockHit;
            cMWModel* pRigblockModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &t, &rigblockHit, 0, blockSettings, &blockPick.mHitIndex, 0);

            bool bSkinHitLod1 = false;
            bool bSkinHit = false;
            float skinDistance = -1.0f;
            Vector3 skinPos;
            Vector3 skinNormal;
            if (mpSkinManager && !bBallConnectorPicked) {
                Vector3 dir = SP::normalized_safe(rayEnd - rayStart);
                bSkinHitLod1 = mpSkinManager->PickSkin(1, rayStart, dir, &skinPos, &skinNormal, &skinDistance, true);
                bSkinHit = bSkinHitLod1;
                if (!bSkinHitLod1)
                    bSkinHit = mpSkinManager->PickSkin(2, rayStart, dir, &skinPos, &skinNormal, &skinDistance, true);
                blockPick.mbSkin = bSkinHit;
            }

            float skinDistSq = -1.0f;
            float rigblockDistSq = (rayStart.z - rigblockHit.z) * (rayStart.z - rigblockHit.z)
                                 + (rayStart.x - rigblockHit.x) * (rayStart.x - rigblockHit.x)
                                 + (rayStart.y - rigblockHit.y) * (rayStart.y - rigblockHit.y);
            int skinLod = bSkinHitLod1 ? 1 : 2;
            if (bSkinHit)
                skinDistSq = skinDistance * skinDistance;

            if (pRigblockModel && pRigblockModel->mpOwner) {
                if (!bSkinHit) {
                    blockPick.mPosition = rigblockHit;
                    blockPick.mbSkin = false;
                    blockPick.mpBlock = interface_cast_block(pRigblockModel->mpOwner);
                    blockDistSq = rigblockDistSq;
                } else {
                    cSPEditorBlock* pRigblock = interface_cast_block(pRigblockModel->mpOwner);
                    if (pRigblock->TestAttribute(kAttrIsVertebra)) {
                        cSPEditorBlock* pSkinBlock = mpSkinManager->GetBlockAtSkinPoint(skinLod, skinPos);
                        if (pSkinBlock && pSkinBlock->TestAttribute(kAttrIsVertebra)) {
                            // Vertebra under the skin: keep the vertebra.
                            blockPick.mPosition = rigblockHit;
                            blockPick.mbSkin = false;
                            blockPick.mpBlock = pRigblock;
                            bBlockFound = true;
                            goto filterBlock;
                        }
                    }
                    if (!bBlockFound) {
                        if (rigblockDistSq > skinDistSq) {
                            blockPick.mPosition = skinPos;
                            blockPick.mbSkin = true;
                            blockPick.mpBlock = mpSkinManager->GetBlockAtSkinPoint(skinLod, skinPos);
                            blockDistSq = skinDistSq;
                        } else {
                            blockPick.mPosition = rigblockHit;
                            blockPick.mbSkin = false;
                            blockPick.mpBlock = interface_cast_block(pRigblockModel->mpOwner);
                            blockDistSq = rigblockDistSq;
                        }
                    }
                }
            } else if (bSkinHit) {
                blockPick.mPosition = skinPos;
                blockPick.mbSkin = true;
                blockPick.mpBlock = mpSkinManager->GetBlockAtSkinPoint(skinLod, skinPos);
                blockDistSq = skinDistSq;
            }
        }

    filterBlock:
        if (mbOnlyEditFromPalette && blockPick.mpBlock && mpPartsPalette) {
            if (!IsBlockInPalette(blockPick.mpBlock))
                blockPick.mpBlock = 0;
        }
        if (!bBlockFound && blockPick.mpBlock && blockPick.mpBlock->TestAttribute(kAttrIsVertebra))
            blockPick.mpBlock = 0;
    }

    bool bHaveBlock = blockPick.mpBlock || blockPick.mbSkin;

    if (!modelPick.mpModel) {
        if (bHaveBlock) {
            result = blockPick;
        } else {
            result.mpBlock = 0;
            result.mpModel = 0;
        }
    } else if (!bHaveBlock) {
        result = modelPick;
    } else {
        cSPEditorHandle* pHandle = interface_cast_inline<cSPEditorHandle>(modelPick.mpModel->mpOwner);
        if (blockDistSq > modelDistSq) {
            if (blockPick.mpBlock && blockPick.mpBlock->TestAttribute(kAttrIsVertebra) && mbPickVertebrae)
                result = blockPick;
            else
                result = modelPick;
        } else {
            // The block is in front: still prefer the handle when it belongs to that block.
            bool bPreferHandle = false;
            if (blockPick.mpBlock->mpBallConnectorHandle == pHandle) {
                bPreferHandle = true;
            } else if (pHandle->GetRigblock()->mpParent) {
                cSPEditorBlock* pHandleBlock = pHandle->GetRigblock();
                if (blockPick.mpBlock) {
                    bPreferHandle = true;
                } else {
                    // Only reached with a null block: the original scans the null block's
                    // children here (a null dereference at +0x340), kept for equivalence.
                    int count = (int)(blockPick.mpBlock->mChildrenEnd - blockPick.mpBlock->mChildrenBegin);
                    for (int i = 0; i < count; i++)
                        if (blockPick.mpBlock->mChildrenBegin[i] == pHandleBlock) {
                            bPreferHandle = true;
                            break;
                        }
                }
            }
            if (blockPick.mpBlock && blockPick.mpBlock->mpBallConnectorHandle && bPreferHandle)
                result = modelPick;
            else
                result = blockPick;
        }
    }

    // Manipulators that pick on their own disable the lock filtering below.
    if (find(mEnabledManipulators.mpBegin, mEnabledManipulators.mpEnd, 0x8665f54d) != mEnabledManipulators.mpEnd)
        return result;
    if (find(mEnabledManipulators.mpBegin, mEnabledManipulators.mpEnd, 0xe931544d) != mEnabledManipulators.mpEnd)
        return result;

    if (result.mpBlock && EditorUtils::IsBlockLocked(result.mpBlock)) {
        result.mpBlock = 0;
        result.mpModel = 0;
    }
    if (result.mpModel && result.mpModel->mpOwner
        && EditorUtils::IsBlockLocked(interface_cast_block(result.mpModel->mpOwner))) {
        result.mpBlock = 0;
        result.mpModel = 0;
    }
    return result;
}

} // namespace SP
