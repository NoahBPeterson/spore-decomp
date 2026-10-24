// Slice s00e39ab0 -- SporeApp.exe 0x00e39ab0..0x00e3a98b.
//
//  00e39ab0  cBigEditorObject::BuildEditorData   (game-mode / empire / time payload)
//  00e39de0  KeyValue::ApplyTo                   (write a keyed value triple into a change msg)
//  00e39e60  IntPropertyBinding::SetValue        (property int -> cached member)
//  00e39ec0  ColorPropertyBinding::SetValue      (property vec4 -> cached member)
//  00e39fb0  IntRbTree::find                     (eastl::map<int,...> lower_bound)
//  00e3a000  EvalCatmullRom2D                    (2 component Catmull-Rom evaluation)
//  00e3a230  cBigEditorObject::GetDrawPriority
//  00e3a270  cBigEditorObject::OnChange
//  00e3a570  ClampToCirclePair
//  00e3a6b0  CreateAndBindEditorImage
//  00e3a730  cBigEditorObject::GetTerrainImage
//  00e3a8f0  cBigEditorObject::RefreshTerrainImages
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>
#include <new>

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------------------------------
// EA::Variant / property list
// ---------------------------------------------------------------------------------------------------

struct Variant {
    union {
        uint32_t  mData[4];
        uint32_t* mpData;      // payload when mFlags holds kFlagByReference (0x30)
    };
    uint16_t mFlags;           // +0x10
    uint16_t mTypeId;          // +0x12
};

class IPropertyList {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Variant** ppValue);   // +0x24
};

extern uint32_t g_variantIntDefault;   // 0x015d9c68

float* GetDefaultColor();              // 0x006bb610

// A property binding object: { vtbl, property id, ?, value }.
struct IntPropertyBinding {
    void*    mpVtbl;           // +0x00
    uint32_t mPropertyId;      // +0x04
    uint32_t mField08;         // +0x08
    int32_t  mValue;           // +0x0c
    bool SetValue(IPropertyList* pList);
};

struct ColorPropertyBinding {
    void*    mpVtbl;           // +0x00
    uint32_t mPropertyId;      // +0x04
    uint32_t mField08;         // +0x08
    float    mValue[4];        // +0x0c
    bool SetValue(IPropertyList* pList);
};

// ---------------------------------------------------------------------------------------------------
// Value-change messages
//
// mpPayload points at an int array; [2] is a scalar and [3..5] / [6..8] are two component triples
// (the windows overlap: a triple starting at index n occupies n, n+1, n+2).
// ---------------------------------------------------------------------------------------------------

struct ValueTriple {
    uint32_t m0, m1, m2;
};

struct ChangePayload {
    uint32_t     mReserved0;   // +0x00
    uint32_t     mReserved1;   // +0x04
    uint32_t     mValue;       // +0x08
    ValueTriple  mFirst;       // +0x0c
    ValueTriple  mSecond;      // +0x18
};

struct ChangeMessage {
    uint32_t        mId;        // +0x00
    uint32_t        mReserved[2];// +0x04
    ChangePayload*  mpPayload;  // +0x0c
};

// A 6 dword key/value pair applied to the triples in a change payload (components 0 and 1 swap).
struct KeyValue {
    uint32_t mKey0;            // +0x00   compared against triple component 1
    uint32_t mKey1;            // +0x04   compared against triple component 0
    uint32_t mKey2;            // +0x08   compared against triple component 2
    uint32_t mVal0;            // +0x0c   stored to component 1
    uint32_t mVal1;            // +0x10   stored to component 0
    uint32_t mVal2;            // +0x14   stored to component 2
    void ApplyTo(ChangeMessage* msg);
};

// ---------------------------------------------------------------------------------------------------
// eastl red-black tree (only the node fields find() needs)
// ---------------------------------------------------------------------------------------------------

struct IntRbNode {
    IntRbNode* mpLeft;         // +0x00
    IntRbNode* mpRight;        // +0x04
    IntRbNode* mpParent;       // +0x08
    uint32_t   mColor;         // +0x0c
    int32_t    mKey;           // +0x10
};

struct IntRbTree {
    uint32_t  mnSize;          // +0x00
    IntRbNode mAnchor;         // +0x04
    void find(IntRbNode** ppResult, const int32_t* pKey);
};

// ---------------------------------------------------------------------------------------------------
// UI / image interfaces
// ---------------------------------------------------------------------------------------------------

struct cSPUILayout {
    bool  IsVisible();                              // 0x00810070
    void* FindWindowByID(uint32_t id, int flags);   // 0x008105b0
};

struct Image {
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    Image* Init();                                                  // 0x006775f0 (construct in place)
    void Setup(void* pWindow, int a, int b);                        // 0x00677220
    void SetFlags(int a, const int* pColors, int b);                // 0x00677700
    void BindA(void* pWindow, void* pVector, int index);            // 0x00677df0
    void BindB(void* pWindow, void* pVector, uint32_t key, int index); // 0x00677d90
};

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

struct IEditorData {
    PV2 PV                         // slots 0..2
    virtual void* FindService(uint32_t id);         // slot 3  (+0x0c)
};

struct IImageOwner {
    PV4 PV                         // slots 0..4
    virtual void SetImage(void* pImage);           // slot 5  (+0x14)
};

struct IEditorHost {
    PV8 PV8 PV8 PV8 PV8 PV2        // slots 0..41
    virtual IEditorData* GetEditorData();          // slot 42 (+0xa8)
};

void* CreateImageFromResource2(void* pKey, void** ppImage, int a, int b, int c);   // 0x00806230

// ---------------------------------------------------------------------------------------------------
// terrain editor access
// ---------------------------------------------------------------------------------------------------

struct cCellRecord {
    uint8_t  mPad000[0xe4];
    uint32_t mTerrainKey;      // +0x0e4
    uint8_t  mPad0e8[0x08];
    uint32_t mTerrainKind;     // +0x0f0
};

struct cTerrainSphere {
    uint8_t  mPad0000[0x10fc];
    uint32_t mField10fc;       // +0x10fc
    uint32_t mField1100;       // +0x1100
    uint32_t mField1104;       // +0x1104
    uint32_t mField1108;       // +0x1108
    uint32_t GetTerrainIndex(uint32_t key);        // 0x00c756e0
};

struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
};

cTerrainEditor* NounManager();                     // 0x00b3d300
uint32_t FUN_00556440(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00556440
int32_t  TerrainKeyToIndex(uint32_t key);           // 0x00e36f50
void     FUN_00e39420(ChangeMessage* msg, int index, void* pOut);        // 0x00e39420

template<class T>
struct Vec {
    T*       mpBegin;          // +0x00
    T*       mpEnd;            // +0x04
    uint32_t mPad08[2];        // +0x08
    T*       mpCapacity;       // +0x10
};

struct RefPtrImage {
    Image* mpObject;           // +0x00
};

struct UIVec3 {
    uint32_t m0, m1, m2;
};

struct EA_ResourceKey {
    uint32_t mInstanceID;      // +0x00
    uint32_t mGroupID;         // +0x04
    uint32_t mTypeID;          // +0x08
};

struct SubObject24 {
    void*        mpVtbl;       // +0x00  (object +0x24)
    uint32_t     mField04;     // +0x04  (object +0x28)
    cSPUILayout* mpLayout;     // +0x08  (object +0x2c)
};

// ---------------------------------------------------------------------------------------------------
// cBigEditorObject -- only the members this slice touches.
// ---------------------------------------------------------------------------------------------------

struct cBigEditorObject {
    void*        mpVtbl00;     // +0x000
    void*        mpVtbl04;     // +0x004
    void*        mpVtbl08;     // +0x008
    void*        mpVtbl0c;     // +0x00c
    uint8_t      mPad010[0x14];// +0x010
    SubObject24  mSub24;       // +0x024
    cSPUILayout* mpLayout30;   // +0x030
    uint8_t      mPad034[0x150];// +0x034
    Vec<cCellRecord*> mCells;  // +0x184
    Vec<RefPtrImage>  mImages; // +0x198
    uint8_t      mPad1ac[0x1c];// +0x1ac
    void*        mpRef1c8;     // +0x1c8
    void*        mpRef1cc;     // +0x1cc
    void*        mpRef1d0;     // +0x1d0
    void*        mpRef1d4;     // +0x1d4
    void*        mpRef1d8;     // +0x1d8
    EA_ResourceKey mTerrainKey;// +0x1dc
    uint8_t      mPad1e8[0xb4];// +0x1e8
    UIVec3       mVecs[5];     // +0x29c..0x2d7
    uint8_t      mPad2d8[0x30];// +0x2d8
    uint32_t     m308;         // +0x308
    uint32_t     m30c;         // +0x30c
    uint32_t     m310;         // +0x310
    uint32_t     m314;         // +0x314
    uint32_t     m318;         // +0x318
    uint32_t     m31c;         // +0x31c
    uint32_t     m320;         // +0x320
    uint32_t     m324;         // +0x324
    uint32_t     m328;         // +0x328
    int32_t      mGameMode;    // +0x32c
    uint8_t      mPad330[0x3c];// +0x330
    bool         mFlag36c;     // +0x36c

    int GetDrawPriority();
    void OnChange(uint32_t messageId, ChangeMessage* msg);
    Image* GetTerrainImage(uint32_t key, bool bRecompute);
    void RefreshTerrainImages();
};

// ---------------------------------------------------------------------------------------------------
// editor data record construction
// ---------------------------------------------------------------------------------------------------

struct IntVector {
    uint8_t   mPad00[0x0c];
    uint32_t* mpData;              // +0x0c
    void resize(uint32_t count);                            // 0x007eb820
};

struct cVectorAllocator {
    IntVector* AllocVector(int kind, int flags);            // 0x007ec160
};

struct cGalaxyOriginProvider {
    void* GetGalaxyOrigin();                               // 0x00c30c80
};

struct cLivingUniverse {
    uint8_t mPad000[0x84];
    uint32_t mEmpireID;            // +0x84
};

struct cGameTimeManager {
    uint64_t GetTime();                                    // 0x00b316c0
};

struct cStarManager {
    void* GetEmpireByID();                                 // 0x00ba9370
};

struct cHomePlanet {
    uint32_t GetPlanetID();                                // 0x00ce6950
};

uint32_t GetCurrentGameMode();                             // 0x00b5b800
cLivingUniverse* GetLivingUniverse();                      // 0x01021300
cLivingUniverse* GetHomeUniverse();                        // 0x01021370
cVectorAllocator* GetVectorAllocator();                    // 0x0067de90
cGameTimeManager* GameTimeManager();                       // 0x00b3d380
void* __stdcall StarManagerForEmpire(uint32_t empireID);   // 0x00b3d2a0
float RandomFloatRange(float lo, float hi);                // 0x00572a10
void FUN_00e39450(IntVector* pVector, const void* pOrigin, const void* pPosition); // 0x00e39450

// ===================================================================================================
// 0x00e39ab0
// ===================================================================================================
// @ 0x00e39ab0
IntVector* FUN_00e39ab0(uint32_t objectID, void* pOwner, int* pPosition, uint32_t* pRotation,
                        int planetID, uint32_t terrainKey, uint32_t* pRotation2,
                        int* pPosition2)
{
    IntVector* pResult = 0;

    bool bHomeMode = false;
    if (GetCurrentGameMode() == 0x1654c05 || GetCurrentGameMode() == 0xdbdba1)
        bHomeMode = true;

    uint32_t* pPlayerOrigin = (uint32_t*)((char*)((cGalaxyOriginProvider*)GetLivingUniverse())
                                              ->GetGalaxyOrigin() + 0x504);
    uint32_t playerEmpireID = GetLivingUniverse()->mEmpireID;
    uint32_t ownerEmpireID = 0;
    if (pOwner != 0)
        ownerEmpireID = *(uint32_t*)((char*)pOwner + 0x84);

    int pos[3];
    pos[0] = pPosition[0];
    pos[1] = pPosition[1];
    pos[2] = pPosition[2];
    if (pPosition[0] == 0 && pPosition[1] == 0 && pos[2] == 0 && pOwner != 0) {
        uint32_t* pOwnerOrigin = (uint32_t*)((char*)((cGalaxyOriginProvider*)pOwner)
                                                 ->GetGalaxyOrigin() + 0x504);
        pos[0] = (int)pOwnerOrigin[0];
        pos[1] = (int)pOwnerOrigin[1];
        pos[2] = (int)pOwnerOrigin[2];
    }

    if (planetID == 0)
        planetID = (int)((cHomePlanet*)GetHomeUniverse())->GetPlanetID();

    cVectorAllocator* pAlloc = GetVectorAllocator();
    if (pAlloc != 0) {
        pResult = pAlloc->AllocVector(0xc, 0);
        pResult->resize(0x1b);
        pResult->mpData[0] = objectID;
        pResult->mpData[1] = 0;
        pResult->mpData[2] = (uint32_t)(GameTimeManager()->GetTime() / 1000);
        if (pPosition2[0] == 0 && pPosition2[1] == 0 && pPosition2[2] == 0) {
            pResult->mpData[3] = pPlayerOrigin[1];
            pResult->mpData[4] = pPlayerOrigin[0];
            pResult->mpData[5] = pPlayerOrigin[2];
        } else {
            pResult->mpData[3] = (uint32_t)pPosition2[1];
            pResult->mpData[4] = (uint32_t)pPosition2[0];
            pResult->mpData[5] = (uint32_t)pPosition2[2];
        }
        pResult->mpData[6]  = (uint32_t)pos[1];
        pResult->mpData[7]  = (uint32_t)pos[0];
        pResult->mpData[8]  = (uint32_t)pos[2];
        pResult->mpData[0x16] = pRotation[1];
        pResult->mpData[0x17] = pRotation[0];
        pResult->mpData[0x18] = pRotation[2];
        pResult->mpData[9]  = playerEmpireID;
        pResult->mpData[0x0a] = ownerEmpireID;
        pResult->mpData[0x19] = (uint32_t)planetID;
        pResult->mpData[0x1a] = terrainKey;

        void* pEmpire1 = ((cStarManager*)StarManagerForEmpire(playerEmpireID))->GetEmpireByID();
        if (pEmpire1 != 0)
            pResult->mpData[0x0b] = *(uint32_t*)((char*)pEmpire1 + 0x10);
        void* pEmpire2 = ((cStarManager*)StarManagerForEmpire(ownerEmpireID))->GetEmpireByID();
        uint32_t empire2ID = 0x53dbcf2;
        if (pEmpire2 != 0)
            empire2ID = *(uint32_t*)((char*)pEmpire2 + 0x10);
        pResult->mpData[0x0c] = empire2ID;
        pResult->mpData[0x0d] = pRotation2[1];
        pResult->mpData[0x0e] = pRotation2[0];
        pResult->mpData[0x0f] = pRotation2[2];

        IntVector* pRec2 = pAlloc->AllocVector(6, 0);
        pRec2->resize(0x18);
        pRec2->mpData[0] = objectID;
        float angle;
        if (bHomeMode)
            angle = 0.0f;
        else
            angle = RandomFloatRange(-0.15f, 0.15f);
        *(float*)&pRec2->mpData[1] = angle;
        pRec2->mpData[2] = (uint32_t)(GameTimeManager()->GetTime() / 1000);
        FUN_00e39450(pRec2, pPlayerOrigin, pos);
        pRec2->mpData[0x14] = pRotation[1];
        pRec2->mpData[0x15] = pRotation[0];
        pRec2->mpData[0x16] = pRotation[2];
        pRec2->mpData[7]  = playerEmpireID;
        pRec2->mpData[8]  = ownerEmpireID;
        pRec2->mpData[0x17] = terrainKey;
        if (pEmpire1 != 0)
            pRec2->mpData[9] = *(uint32_t*)((char*)pEmpire1 + 0x10);
        pRec2->mpData[0x0a] = empire2ID;
        pResult->mpData[0x0d] = pRotation2[1];
        pResult->mpData[0x0e] = pRotation2[0];
        pResult->mpData[0x0f] = pRotation2[2];
    }
    return pResult;
}

// ===================================================================================================
// 0x00e39de0
// ===================================================================================================
// @ 0x00e39de0
void KeyValue::ApplyTo(ChangeMessage* msg)
{
    if (msg->mpPayload->mFirst.m1 == mKey0
        && msg->mpPayload->mFirst.m0 == mKey1
        && msg->mpPayload->mFirst.m2 == mKey2) {
        msg->mpPayload->mFirst.m0 = mVal1;
        msg->mpPayload->mFirst.m1 = mVal0;
        msg->mpPayload->mFirst.m2 = mVal2;
    }
    if (msg->mpPayload->mSecond.m1 == mKey0
        && msg->mpPayload->mSecond.m0 == mKey1
        && msg->mpPayload->mSecond.m2 == mKey2) {
        msg->mpPayload->mSecond.m0 = mVal1;
        msg->mpPayload->mSecond.m1 = mVal0;
        msg->mpPayload->mSecond.m2 = mVal2;
    }
}


// ===================================================================================================
// 0x00e39e60
// ===================================================================================================
// @ 0x00e39e60
bool IntPropertyBinding::SetValue(IPropertyList* pList)
{
    Variant* pValue;
    if (!pList->GetProperty(mPropertyId, &pValue))
        return false;
    uint16_t type = pValue->mTypeId;
    uint32_t* pData;
    if (type == 9 || type == 0x10)
        pData = (pValue->mFlags & 0x30) ? pValue->mpData
              : (uint32_t*)((type != 0 ? -1 : 0) & (int32_t)pValue);
    else
        pData = &g_variantIntDefault;
    int32_t value = (int32_t)*pData;
    if (mValue != value) {
        mValue = value;
        return true;
    }
    return false;
}

// ===================================================================================================
// 0x00e39ec0
// ===================================================================================================
// @ 0x00e39ec0
bool ColorPropertyBinding::SetValue(IPropertyList* pList)
{
    Variant* pValue;
    if (!pList->GetProperty(mPropertyId, &pValue))
        return false;
    uint16_t type = pValue->mTypeId;
    float* pData;
    if (type == 0x34 || type == 0x10)
        pData = (pValue->mFlags & 0x30) ? (float*)pValue->mpData
              : (float*)((type != 0 ? -1 : 0) & (int32_t)pValue);
    else
        pData = GetDefaultColor();
    float value[4] = { pData[0], pData[1], pData[2], pData[3] };
    if (mValue[0] == value[0] && mValue[1] == value[1]
        && mValue[2] == value[2] && mValue[3] == value[3])
        return false;
    mValue[0] = value[0];
    mValue[1] = value[1];
    mValue[2] = value[2];
    mValue[3] = value[3];
    return true;
}

// ===================================================================================================
// 0x00e39fb0
// ===================================================================================================
// @ 0x00e39fb0
void IntRbTree::find(IntRbNode** ppResult, const int32_t* pKey)
{
    IntRbNode* pNode = mAnchor.mpParent;
    IntRbNode* pEnd = &mAnchor;
    IntRbNode* pResult = pEnd;
    while (pNode) {
        if (pNode->mKey < *pKey) {
            pNode = pNode->mpLeft;
        } else {
            pResult = pNode;
            pNode = pNode->mpRight;
        }
    }
    if (pResult != pEnd && !(*pKey < pResult->mKey)) {
        *ppResult = pResult;
        return;
    }
    *ppResult = pEnd;
}

// ===================================================================================================
// 0x00e3a000
// ===================================================================================================
// @ 0x00e3a000
void EvalCatmullRom2D(float* pOut, const float* p0, const float* p1, const float* p2,
                      const float* p3, float t)
{
    pOut[0] = (2.0f * p1[0] + (p2[0] - p0[0]) * t
               + (2.0f * p0[0] - 5.0f * p1[0] + 4.0f * p2[0] - p3[0]) * t * t
               + (p3[0] - p0[0] + 3.0f * p1[0] - 3.0f * p2[0]) * t * t * t) * 0.5f;
    pOut[1] = (2.0f * p1[1] + (p2[1] - p0[1]) * t
               + (2.0f * p0[1] - 5.0f * p1[1] + 4.0f * p2[1] - p3[1]) * t * t
               + (p3[1] - p0[1] + 3.0f * p1[1] - 3.0f * p2[1]) * t * t * t) * 0.5f;
}

// ===================================================================================================
// 0x00e3a230
// ===================================================================================================
// @ 0x00e3a230
int cBigEditorObject::GetDrawPriority()
{
    bool bVisible = mFlag36c || (mSub24.mpLayout && mSub24.mpLayout->IsVisible());
    return bVisible ? 0x87 : 0;
}

// ===================================================================================================
// 0x00e3a270
// ===================================================================================================
// @ 0x00e3a270
void cBigEditorObject::OnChange(uint32_t messageId, ChangeMessage* msg)
{
    switch (messageId) {
    case 0xaaf6aaac:
    case 0xdca976d0:
    case 0x99f0d1da:
        m324 = msg->mpPayload->mValue;
        FUN_00e39420(msg, 3, &mVecs[3]);
        return;

    case 0x9f792b4c:
        if (mGameMode == -1)
            mGameMode = 0x1654c05;
        if (m324 == 0)
            m324 = msg->mpPayload->mValue;
        m328 = msg->mpPayload->mValue;
        return;

    case 0xade76cce:
        if (mGameMode == -1)
            mGameMode = 0x1654c01;
        m310 = msg->mpPayload->mValue;
        return;

    case 0x279c4e55:
        if (mGameMode == -1)
            mGameMode = 0x1654c02;
        if (m314 == 0)
            m314 = msg->mpPayload->mValue;
        m318 = msg->mpPayload->mValue;
        return;

    case 0xf278934a:
    case 0x25ca9233:
    case 0x5c51063f:
        m314 = msg->mpPayload->mValue;
        mVecs[1].m1 = msg->mpPayload->mFirst.m0;
        mVecs[1].m0 = msg->mpPayload->mFirst.m1;
        mVecs[1].m2 = msg->mpPayload->mFirst.m2;
        return;

    case 0x8133fb2e:
    case 0x2cfa39dd:
    case 0x6a9f2620:
        m31c = msg->mpPayload->mValue;
        FUN_00e39420(msg, 3, &mVecs[2]);
        return;

    case 0xf967827c:
    case 0x13df9c1c:
    case 0x7115ede5:
        m30c = msg->mpPayload->mValue;
        FUN_00e39420(msg, 3, &mVecs[0]);
        return;

    case 0x980e43f2:
    case 0xa0973374:
    case 0xa6cb4c9f:
    case 0xd832b059:
    case 0xcdb3696f:
    case 0xd536c91d:
    case 0xe0bc9d45:
    case 0x6cd9ec7b:
    case 0x5fcf28d0:
    case 0x7bceaa86:
        if (msg) {
            mVecs[4].m1 = msg->mpPayload->mFirst.m0;
            mVecs[4].m0 = msg->mpPayload->mFirst.m1;
            mVecs[4].m2 = msg->mpPayload->mFirst.m2;
        }
        return;

    case 0x3e2a3040:
        mGameMode = 0x1654c00;
        m308 = msg->mpPayload->mValue;
        return;

    case 0x3b38f92a:
        if (mGameMode == -1)
            mGameMode = 0x1654c04;
        if (m31c == 0)
            m31c = msg->mpPayload->mValue;
        m320 = msg->mpPayload->mValue;
        return;
    }
}

// ===================================================================================================
// 0x00e3a570
// ===================================================================================================
// @ 0x00e3a570
void ClampToCirclePair(float* pOut, float x, float y, const float* c, float r1,
                       const float* d, float r2, float sgn)
{
    float yA = y;
    float dxA = x - c[0];
    float dyA = y - c[1];
    if (r1 * r1 >= dxA * dxA + dyA * dyA)
        yA = c[1] + sgn * sqrtf(r1 * r1 - dxA * dxA);

    float yB = y;
    float dxB = x - d[0];
    float dyB = y - d[1];
    if (r2 * r2 >= dxB * dxB + dyB * dyB)
        yB = d[1] + sgn * sqrtf(r2 * r2 - dxB * dxB);

    float ptA[2] = { x, yA };
    float ptB[2] = { x, yB };

    const float* pSrc;
    if (sgn >= 0.0f)
        pSrc = (yA > yB) ? ptA : ptB;
    else
        pSrc = (yB > yA) ? ptA : ptB;

    pOut[0] = pSrc[0];
    pOut[1] = pSrc[1];
}

// ===================================================================================================
// 0x00e3a6b0
// ===================================================================================================
// @ 0x00e3a6b0
bool CreateAndBindEditorImage(void* pHost, void* pKey)
{
    if (pHost != 0) {
        IEditorData* pData = ((IEditorHost*)pHost)->GetEditorData();
        if (pData != 0) {
            IImageOwner* pOwner = (IImageOwner*)pData->FindService(0xef3c47cf);
            if (pOwner != 0) {
                void* pImage = 0;
                CreateImageFromResource2(pKey, &pImage, 0, -1, -1);
                if (pImage != 0) {
                    pOwner->SetImage(pImage);
                    if (pImage)
                        ((Image*)pImage)->Release();
                    return true;
                }
            }
        }
    }
    return false;
}

// ===================================================================================================
// 0x00e3a730
// ===================================================================================================
// @ 0x00e3a730
Image* cBigEditorObject::GetTerrainImage(uint32_t key, bool bRecompute)
{
    Image* pImage = 0;
    cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
    uint32_t index = 0;
    if (mTerrainKey.mGroupID == 0x2b978c46) {
        index = pSphere->GetTerrainIndex(key);
    } else {
        cCellRecord* pCell = mCells.mpEnd[-1];
        if (pCell)
            index = pCell->mTerrainKind;
    }
    if (bRecompute) {
        if (pSphere->mField1108)
            index = FUN_00556440(pSphere->mField10fc, pSphere->mField1100,
                                 pSphere->mField1104, pSphere->mField1108);
    }
    if (index) {
        int32_t n = TerrainKeyToIndex(key);
        if (void* pMem = operator new(0xa0, "UI", 0, 0, 0, 0)) {
            Image* pNewImage = ((Image*)pMem)->Init();
            if (pNewImage)
                pNewImage->AddRef();
            pImage = pNewImage;
        }
        void* pWindow = mpLayout30->FindWindowByID(n + 0x6299720, 1);
        UIVec3* pVec = &mVecs[n];
        if (pVec->m0 == 0) {
            pImage->Setup(pWindow, 1, 1);
            int colors[3] = { (int)index, 0xb1b104, 0xf865c777 };
            pImage->SetFlags(1, colors, 0);
        } else if (key == 0xa426730b) {
            pImage->BindA(pWindow, pVec, (int)index);
        } else {
            pImage->BindB(pWindow, pVec, key, (int)index);
        }
        if (bRecompute) {
            int colors[3] = { (int)index, 0xb1b104, 0xf865c777 };
            pImage->SetFlags(1, colors, 0);
        }
        RefPtrImage* pSlot = &mImages.mpBegin[n];
        Image* pOld = pSlot->mpObject;
        if (pImage != pOld) {
            if (pImage)
                pImage->AddRef();
            pSlot->mpObject = pImage;
            if (pOld)
                pOld->Release();
        }
        if (pImage)
            pImage->Release();
    }
    return pImage;
}

// ===================================================================================================
// 0x00e3a8f0
// ===================================================================================================
// @ 0x00e3a8f0
void cBigEditorObject::RefreshTerrainImages()
{
    if (mTerrainKey.mGroupID != 0x2b978c46)
        return;

    cCellRecord* pCell = mCells.mpEnd[-1];
    uint32_t key;
    if (pCell != 0 && pCell->mTerrainKind != 0)
        key = pCell->mTerrainKey;
    else
        key = 0;

    if (key != 0xa426730b)
        GetTerrainImage(0xa426730b, false);
    if (key != 0xad56080c)
        GetTerrainImage(0xad56080c, false);
    if (key != 0xf71fa311)
        GetTerrainImage(0xf71fa311, false);
    if (key != 0xbeb528cb)
        GetTerrainImage(0xbeb528cb, false);
    GetTerrainImage(0x2db6dad3, false);
}

// layout checks
#include <stddef.h>
template<int A,int B> struct Eq; template<int A> struct Eq<A,A>{};
#define CHK(f, o) Eq<offsetof(cBigEditorObject, f), (o)> chk_##f
CHK(mSub24, 0x24); CHK(mpLayout30, 0x30); CHK(mCells, 0x184); CHK(mImages, 0x198);
CHK(mTerrainKey, 0x1dc); CHK(mVecs, 0x29c); CHK(m308, 0x308); CHK(mGameMode, 0x32c);
CHK(mFlag36c, 0x36c);
Eq<offsetof(cBigEditorObject, mTerrainKey) + 4, 0x1e0> chk_key_group;
Eq<offsetof(cBigEditorObject, mVecs) + 0xc, 0x2a8> chk_vec1;
