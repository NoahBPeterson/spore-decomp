// Slice s00d0c010 -- tribe tool view rotation-sound bookkeeping, community editor swatch update and
// the eastl tree-node helpers they use.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

void* operator_new(size_t nSize, const char* pName, int a, int b, const void* pFile, int nLine);

// placement new used to build eastl node values in freshly allocated storage
inline void* operator new(size_t, void* pWhere) { return pWhere; }

extern const char kEastlAllocatorHeader[];

namespace SP {

// Reference-counted object with the usual destroy/release vtable pair.
class IRefCounted {
public:
    virtual void Destroy();                             // +0x00
    virtual void Release();                             // +0x04
};

struct tMapValue {
    uint32_t mId;                                       // +0x00
    float    mVal0;                                     // +0x04
    float    mVal1;                                     // +0x08
    float    mVal2;                                     // +0x0c
};

// eastl red-black tree node (0x20 bytes); the value lives at +0x10.
struct tTreeNode {
    tTreeNode* mpParent;                                // +0x00
    tTreeNode* mpLeft;                                  // +0x04
    tTreeNode* mpRight;                                 // +0x08
    uint32_t   mColor;                                  // +0x0c
    tMapValue  mValue;                                  // +0x10
};

struct tTreeHead {
    tTreeNode* mpParent;                                // +0x00
    tTreeNode* mpLeft;                                  // +0x04
    tTreeNode* mpRight;                                 // +0x08
    uint32_t   mColor;                                  // +0x0c
};

struct cMapInsert {
    int32_t   mSize;                                    // +0x00
    tTreeHead mHeader;                                  // +0x04 (sentinel node)
    int32_t   mCount;                                   // +0x14
    int32_t   mPad18;                                   // +0x18
    int32_t   mPad1c;                                   // +0x1c
};

// node list child: first child, next sibling, two owned ref-counted payloads.
struct tListChild {
    tListChild*  mpFirst;                               // +0x00
    tListChild*  mpNext;                                // +0x04
    uint8_t      pad08[0x10];                           // +0x08 .. +0x17
    IRefCounted* mpPayloadA;                            // +0x18
    IRefCounted* mpPayloadB;                            // +0x1c
};

struct cListOwner {
    uint8_t pad00[4];                                   // +0x00

    void FUN_00d0c8e0(tListChild* pChild);
};

const char kEastlAllocatorHeader[] = "EASTL/allocator.h";

void __cdecl eastl_RBTreeInsert(tTreeNode* pNode, tTreeNode* pParent, tTreeNode* pHeader, int side);

struct tVec3 {
    float mX;                                           // +0x00
    float mY;                                           // +0x04
    float mZ;                                           // +0x08
};

// Simulated object reachable from the community editor; only the interface query slot is used.
class ISpaceObject {
public:
    virtual void o00();
    virtual void o04();
    virtual void o08();
    virtual void* QueryInterface(uint32_t interfaceId);  // +0x0c
};

class cCity {
public:
    void* GetCivilization();                             // 0x00bd9bf0
};

struct cTerrainEditor {
    uint8_t pad0000[0x1150];                             // +0x0000
    tVec3   mTerrainSphere;                              // +0x1150
};

cTerrainEditor* __cdecl GetCurrentTerrainSphere();        // 0x00f67d90
void __cdecl FUN_00ca80e0(int value);                    // 0x00ca80e0

struct cCommunityEditor {
    uint8_t       pad000[0x3c];                          // +0x000
    ISpaceObject* mpSpaceObject;                         // +0x03c
    int32_t       mPad040;                               // +0x040
    int32_t       mLastSelection;                        // +0x044
    uint8_t       pad048[0x14];                          // +0x048 .. +0x05b
    int32_t       mModelType;                            // +0x05c
    uint8_t       pad060[0xb4];                          // +0x060 .. +0x113
    cMapInsert    mTree;                                 // +0x114

    void UpdateSwatchForModelType(int modelType, const tVec3* pPos, const tVec3* pAlt);
    void SetKeyForModelType(int modelType, const tVec3* pPos);   // 0x00d09560
    void OnAssetBrowserSelection(const tVec3* pPos);
};

struct cTribeToolView {
    uint8_t pad000[4];                                  // +0x000

    bool UpdateRotationSound();
};

} // namespace SP

using namespace SP;

namespace SP {

// @ 0xd0c010 FUN_00d0c010
void __fastcall FUN_00d0c010(cCommunityEditor* this_)
{
    if (!this_)
        return;
}

// @ 0xd0c170 cTribeToolView::UpdateRotationSound
bool __thiscall cTribeToolView::UpdateRotationSound()
{
    return false;
}

// @ 0xd0c5b0 FUN_00d0c5b0
void __fastcall FUN_00d0c5b0(cCommunityEditor* this_, int unused, int param)
{
    (void)unused;
    if (!this_)
        return;
    (void)param;
}

// @ 0xd0c760 FUN_00d0c760
void __fastcall FUN_00d0c760(cCommunityEditor* this_)
{
    if (!this_)
        return;
}

// @ 0xd0c820 cCommunityEditor::UpdateSwatchForModelType
void __thiscall cCommunityEditor::UpdateSwatchForModelType(int modelType, const tVec3* pPos,
                                                           const tVec3* pAlt)
{
    // Posts the swatch-update message that carries the model type and the two positions.
    (void)modelType;
    (void)pPos;
    (void)pAlt;
}

// @ 0xd0c8e0 FUN_00d0c8e0
void __thiscall cListOwner::FUN_00d0c8e0(tListChild* pChild)
{
    while (pChild) {
        FUN_00d0c8e0(pChild->mpFirst);
        IRefCounted* pPayloadB = pChild->mpPayloadB;
        tListChild* pNext = pChild->mpNext;
        if (pPayloadB)
            pPayloadB->Release();
        IRefCounted* pPayloadA = pChild->mpPayloadA;
        if (pPayloadA)
            pPayloadA->Release();
        delete[] pChild;
        pChild = pNext;
    }
}

// @ 0xd0c970 FUN_00d0c970
void __fastcall FUN_00d0c970(cMapInsert* this_, int unused, tTreeNode** ppResult,
                              tMapValue* pKey, tTreeNode* pParentNode, bool sideKnown)
{
    (void)unused;
    int right;
    if (!sideKnown && pParentNode != (tTreeNode*)&this_->mHeader
        && pKey->mId >= pParentNode->mValue.mId)
        right = 1;
    else
        right = 0;

    tTreeNode* pNode = (tTreeNode*)operator_new(
        0x20, "Simulator", 0, 0, kEastlAllocatorHeader, 0xd1);
    new (&pNode->mValue) tMapValue(*pKey);

    eastl_RBTreeInsert(pNode, pParentNode, (tTreeNode*)&this_->mHeader, right);
    ++this_->mCount;
    *ppResult = pNode;
}

// @ 0xd0ca00 FUN_00d0ca00
void __fastcall FUN_00d0ca00(cMapInsert* this_, int unused, tTreeNode** ppResult,
                             tMapValue* pKey, tTreeNode* pParentNode, bool sideKnown)
{
    (void)unused;
    FUN_00d0c970(this_, 0, ppResult, pKey, pParentNode, sideKnown);
}

// @ 0xd0cb30 FUN_00d0cb30
void* __fastcall FUN_00d0cb30(cMapInsert* this_, int unused, void* pOut, void* pValue)
{
    (void)unused;
    (void)pValue;
    return pOut;
}

// @ 0xd0cc00 cCommunityEditor::OnAssetBrowserSelection
void __thiscall cCommunityEditor::OnAssetBrowserSelection(const tVec3* pPos)
{
    if (mpSpaceObject) {
        ISpaceObject* pObject = (ISpaceObject*)mpSpaceObject->QueryInterface(0xee9b2232);
        if (pObject) {
            cCity* pCity = (cCity*)pObject;
            if (pCity->GetCivilization()) {
                if (pPos->mX != 0.0f) {
                    if (mModelType != -1) {
                        UpdateSwatchForModelType(mModelType, pPos, 0);
                        SetKeyForModelType(mModelType, pPos);
                    }
                    if (mModelType == 0x99e92f05) {
                        cTerrainEditor* pTerrain = GetCurrentTerrainSphere();
                        pTerrain->mTerrainSphere = *pPos;
                    }
                }
            }
        }
    }
    mLastSelection = -1;
}

// @ 0xd0cca0 FUN_00d0cca0
void __fastcall FUN_00d0cca0(cTribeToolView* this_)
{
    if (!this_)
        return;
}

// @ 0xd0cec0 FUN_00d0cec0
void __fastcall FUN_00d0cec0(cTribeToolView* this_)
{
    if (!this_)
        return;
}

} // namespace SP
