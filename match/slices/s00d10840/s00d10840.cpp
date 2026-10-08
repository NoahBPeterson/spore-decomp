// Slice s00d10840 -- SP::cCommunityEditor::UpdateObjectPlacement (0x00d10840) and
// SP::cCommunityEditor::EndObjectPlacement (0x00d10f90), called from the editor's mouse handler
// (stdcall-like `ret 8`: two window/message arguments that neither function reads).
//
// UpdateObjectPlacement: while a building/turret/tool is dragged around, find the closest snap
// point of the active snap layout, move the object there (or onto the planet surface under the
// cursor), play the snap / unsnap effects and orient the object towards the city centre.
// EndObjectPlacement: drop the object (buy or sell it, play the plunk effect, wire it to the snap
// slot, update the budget, fire the placement messages) and reset the drag state.
//
// Layouts are the retail ones (the 2008 PDB layout is shifted); members are named from the PDB /
// ModAPI where the role is clear and by offset otherwise.
// Compile flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "types.h"
#include <math.h>

#define VS1(n) virtual void n();
#define VS4(n) VS1(n##0) VS1(n##1) VS1(n##2) VS1(n##3)

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3 operator-(const Vector3& a, const Vector3& b) { Vector3 r; r.x = a.x - b.x; r.y = a.y - b.y; r.z = a.z - b.z; return r; }
inline Vector3 operator+(const Vector3& a, const Vector3& b) { Vector3 r; r.x = a.x + b.x; r.y = a.y + b.y; r.z = a.z + b.z; return r; }
inline Vector3 operator*(const Vector3& a, float f) { Vector3 r; r.x = a.x * f; r.y = a.y * f; r.z = a.z * f; return r; }
inline Vector3 Cross(const Vector3& a, const Vector3& b) { Vector3 r; r.x = a.y * b.z - a.z * b.y; r.y = a.z * b.x - a.x * b.z; r.z = a.x * b.y - a.y * b.x; return r; }
struct Quaternion {
    float x, y, z, w;
};
struct BoundingBox {
    Vector3 lower;
    Vector3 upper;
};

namespace SP {

class cCity;
class cBuilding;
class cPlaceable;
class cBuildingSet;
class cSnapEntry;

// ---------------------------------------------------------------------------------------------
// Engine objects (only the virtual slots / members these functions touch)
// ---------------------------------------------------------------------------------------------
class cSpatialObject {
public:
    VS4(a) VS4(b) VS1(c0) VS1(c1) VS1(c2)                       // 0x00 .. 0x28
    virtual const Vector3& GetPosition();                        // +0x2c
    VS1(d0) VS1(d1)                                              // +0x30, +0x34
    virtual void SetPosition(const Vector3& position);           // +0x38
    virtual void SetOrientation(const Quaternion& q);            // +0x3c
    VS4(e) VS1(f0) VS1(f1) VS1(f2)                               // +0x40 .. +0x58
    virtual Vector3 GetDirection();                              // +0x5c
    VS1(g0) VS1(g1)                                              // +0x60, +0x64
    virtual const BoundingBox& GetLocalExtents();                // +0x68
    VS4(h) VS4(i) VS4(j) VS4(k) VS1(l0) VS1(l1) VS1(l2)          // +0x6c .. +0xb4
    virtual void* Cast(uint32_t type);                           // +0xb8
    uint32_t pad04[(0x6e - 4) / 4];                              // up to +0x6c
    uint16_t pad6c;
    bool mbIsInvalid;                                            // +0x6e
};

class cCommunity {
public:
    VS1(a0) VS1(a1) VS1(a2)
    virtual void* Cast(uint32_t type);                           // +0x0c
    VS4(b) VS4(c) VS4(d) VS4(e) VS1(f0) VS1(f1)                  // +0x10 .. +0x54
    virtual Vector3 GetCenter();                                 // +0x58 (hidden out pointer)
};

class cCity {
public:
    VS4(a) VS4(b) VS4(c) VS4(d) VS4(e) VS1(f0) VS1(f1)           // +0x00 .. +0x57
    virtual Vector3 GetPosition();                               // +0x58 (hidden out pointer)
    void RefreshAfterEdit();                                     // 0x00bd7f30
    bool FUN_00bdfb00(cPlaceable* pPlaceable, Quaternion* pOut); // 0x00bdfb00
};

class ICameraManager {
public:
    VS4(a) VS4(b) VS4(c) VS1(d0) VS1(d1)
    virtual Vector3 Pick(int mode, Vector3 screen);              // +0x38
    VS4(e) VS4(f)                                                // +0x3c .. +0x58
    virtual void PlayEffect(uint32_t effectID, const Vector3& position, const Vector3& direction, int a, int cost, float f);   // +0x5c
};

class cPlanetModel {
public:
    Vector3 ToSurface(const Vector3& pos);                                     // 0x00b81630
    Quaternion BuildSurfaceOrientation(const Vector3& pos, const Vector3& dir); // 0x00b7f250
};

class IAudioSystem {
public:
    VS4(a) VS4(b)
    virtual uint32_t GetState();                                 // +0x20
};

// One entry of the snap layout (0x18 bytes): in-use flag, the placed object, the world position.
struct cSnapEntry {
    uint8_t mbUsed;       // +0x00
    uint8_t pad01[3];
    void* mpObject;       // +0x04
    uint32_t pad08;
    Vector3 mPosition;    // +0x0c
    void Clear();                       // 0x00afa0a0
    void Occupy(void* pObject);         // 0x00afa030
};
class cSnapLayout {
public:
    uint32_t pad[0x50 / 4];
    cSnapEntry* mpEntries;              // +0x50
};

class cSellBackRollover {
public:
    uint32_t pad[0x9e / 4];
    void HideWin();                     // 0x005cc690
    void Show(const wchar_t* text, int cost, int arg);   // 0x005cc750
};
class cSellBackRolloverBase {
public:
    VS1(a0) VS1(a1)
    virtual void Hide();                                        // +0x08
};
class cString {
public:
    uint32_t mData[9];
    cString();                                          // 0x006b5060
    ~cString();                                         // 0x006b5240
    void Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006b54b0
    const wchar_t* GetText();                           // 0x006b55c0
};
class cCursorAttachment {
public:
    void SetWindow(void* pWindow);                      // 0x008017f0
};

// Value type of the animated-object map: copies member by member (movss pairs).
struct cSPVector3 {
    float x, y, z;
    cSPVector3& operator=(const Vector3& v) { x = v.x; y = v.y; z = v.z; return *this; }
};
// Map<cSpatialObject*, cSPVector3>::operator[]
class cAnimatedObjectMap {
public:
    cSPVector3& operator[](cSpatialObject* const& key);    // 0x00d0fee0
};

// Free helpers
ICameraManager* CameraManager();                         // 0x00b3d240
cPlanetModel* PlanetModel();                             // 0x00b3d350
IAudioSystem* GetSystemAT();                             // 0x00a206f0
uint32_t GetAudioState();                                // 0x00435e90 (GetSystemAT() ? ->GetState() : 0)
void KillSetiEffects(uint32_t id, uint32_t state);      // 0x00435ed0 (cdecl)
uint32_t SPIDFromName(const char* name);                 // 0x00571cf0
float GetPropertyT_float(uint32_t listID, uint32_t groupID, uint32_t propID, float defaultValue);  // 0x00bcea30
Vector3 normalized_safe(const Vector3& v);               // 0x00449c20
Vector3 Vector3_Normalize(const Vector3& v);             // 0x00436ce0
void* GetObjectSnapInterface(cSpatialObject* pObject);  // 0x00ae66d0 (Cast(0x17f243b))
cCursorAttachment* CursorAttachment();                   // 0x0067cab0
cBuilding* interface_cast_building(cSpatialObject* p);   // 0x00cf10b0
void FUN_00be2440(cCity* pCity, int a, int b);           // 0x00be2440 (cdecl)


// ---- additional stubs for EndObjectPlacement ------------------------------------------------------
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

class IWindow {
public:
    VS4(a) VS1(b0) VS1(b1)
    virtual void SetFlag(int flag, int value);                   // +0x18
};

class cCombatant {
public:
    int GetDamageState();                                        // 0x008e7f80
};
class cPlaceable {                                               // Cast(0xe9cb8ba)
public:
    uint32_t pad04[12];
    cSpatialObject mSpatial;                                     // +0x34 (embedded spatial interface)
    bool FUN_00c3f540();                                         // 0x00c3f540
};
class cBuildingSet;                                              // Cast(0x436f315)
class cSellEffect {                                              // Cast(0xe89adf71)
public:
    VS1(a0) VS1(a1) VS1(a2)
    virtual uint32_t GetEffectID();                              // +0x0c
};
class cTool {                                                    // Cast(0x116d858)
public:
    VS4(a) VS4(b) VS4(c) VS4(d) VS4(e) VS1(f0) VS1(f1)           // +0x00 .. +0x57
    virtual int GetToolType();                                   // +0x58
};
class cTribe {
public:
    uint32_t pad[0x234 / 4];
    uint32_t mField234;                                          // +0x234
    void FUN_00c947d0(float amount, const Vector3* pPosition);   // 0x00c947d0
    bool FUN_00c8ec00(int toolType);                             // 0x00c8ec00
    char* FUN_00c8e820(int toolType);                            // 0x00c8e820
    void FUN_00c8ebe0(int toolType);                             // 0x00c8ebe0
};
class cTerrainSphere {
public:
    void FUN_00c78420(const ResourceKey* pKey);                  // 0x00c78420
    int FUN_00c75420();                                          // 0x00c75420
};
class cGameNounManager {
public:
    cTerrainSphere* GetCurrentTerrainSphere();                   // 0x00f67d90
};
cGameNounManager* NounManager();                                 // 0x00b3d300

class IMessageServer {
public:
    VS4(a) VS1(b0)
    virtual void PostMessage(uint32_t messageID, void* pMessage, int flags);   // +0x14
};
IMessageServer* MessageServer();                                 // 0x0067dcc0

// kMsgSetCreation message (two vptrs: 0x013ff7f0 / 0x013f6c9c), 0x20 bytes
struct cMsgBase { virtual void Base0(); };
struct cMsgData { virtual void Data0(); int mField8; int mFieldC; cMsgData() : mField8(0) {} };
struct cSetCreationMsg : cMsgBase, cMsgData {
    ResourceKey mKey;
    int         mToolType;
    explicit cSetCreationMsg(int toolType) : mToolType(toolType) {}
    virtual void Base0();
};

void Start3dSoundByName(uint32_t soundID, uint32_t state, Vector3 position);   // 0x00571f80 (cdecl)
int FUN_00c9cec0(int toolType);                                  // 0x00c9cec0 (cdecl)
void FUN_00e398e0(uint32_t id, char* pKey, const Vector3* pPos, int a, uint32_t b, int c, int d);   // 0x00e398e0 (cdecl)
int FUN_00d08f00(cSpatialObject* pObject);                       // 0x00d08f00 (cdecl)

class cCommunityEditor {
public:
    uint32_t pad00[0x40 / 4];
    cCommunity* mpCommunity;                // +0x40
    uint32_t pad44[(0x68 - 0x44) / 4];
    IWindow* mpWinBudget;                   // +0x68
    uint32_t pad6c[(0x7c - 0x6c) / 4];
    cSellBackRolloverBase* mpSellbackRollover;  // +0x7c
    uint32_t pad80;
    cSellBackRollover* mpSellbackLayout;    // +0x84
    uint32_t pad88[(0xc0 - 0x88) / 4];
    cSpatialObject* mpManipulatedObject;    // +0xc0
    uint32_t padc4;
    cSpatialObject* mpSwapObject;           // +0xc8
    uint32_t padcc[(0xe8 - 0xcc) / 4];
    Vector3 mCursorScreenPos;               // +0xe8
    cSnapLayout* mpCurrentSnapLayout;       // +0xf4
    int mOriginalSnapPointIndex;            // +0xf8
    int mCurrentSnapPointIndex;             // +0xfc
    int mLastSnapPointIndex;                // +0x100
    int mLastSwapPointIndex;                // +0x104
    uint32_t pad108[(0x110 - 0x108) / 4];
    cAnimatedObjectMap mAnimatedObjectMap;  // +0x110 (the map's anchor sits at +0x114)
    uint32_t pad114[(0x27c - 0x114) / 4];
    uint32_t mAttractorEffectID;            // +0x27c
    uint32_t mSnapEffectID;                 // +0x280
    uint32_t mUnsnapEffectID;               // +0x284
    uint32_t mPlunkEffectID;                // +0x288
    uint32_t mRipEffectID;                  // +0x28c

    bool UpdateObjectPlacement(void* pWindow, void* pMessage);
    bool EndObjectPlacement(void* pWindow, void* pMessage);

    int GetIndexOfClosestSnapPoint(cSnapLayout* pLayout, Vector3 position, int arg, cSpatialObject** ppSwapObject); // 0x00d0b710
    Vector3* SnapPointToPlanetIfNecessary(Vector3* pOut, Vector3 position, cSpatialObject* pObject); // 0x00d09f00
    void CreateOneShotEffect(uint32_t effectID, Vector3 position);   // 0x00d0ba80
    void HandleSwapObject();                                         // 0x00d10720
    int GetObjectCost(cSpatialObject* pObject, int a, int b);        // 0x00d0abd0
    void RemoveObjectFromCommunity(cSpatialObject* pObject);         // 0x00d09d30
    void SetManipulatedObject(cSpatialObject* pObject);              // 0x00d09f60
    void FUN_00d0bcf0(cSpatialObject* pObject);                      // 0x00d0bcf0
    void FUN_00d0dea0();                                             // 0x00d0dea0
    void FUN_00d0a390();                                             // 0x00d0a390
    void FUN_00d0a5b0();                                             // 0x00d0a5b0
    bool FUN_00d096e0(cBuildingSet* pSet);                           // 0x00d096e0
};

// @ 0x00d10840
bool cCommunityEditor::UpdateObjectPlacement(void* pWindow, void* pMessage)
{
    cCity* pCity = mpCommunity ? (cCity*)mpCommunity->Cast(0xee9b2232) : 0;
    if (!mpManipulatedObject)
        return false;
    if (!mpCurrentSnapLayout)
        return false;

    cSpatialObject* pNewSwap = 0;
    Vector3 surface = PlanetModel()->ToSurface(CameraManager()->Pick(1, mCursorScreenPos));
    Vector3 position(surface);
    mpManipulatedObject->mbIsInvalid = true;

    bool bChanged = false;
    mCurrentSnapPointIndex = GetIndexOfClosestSnapPoint(mpCurrentSnapLayout, position, 0, &pNewSwap);

    if (mCurrentSnapPointIndex != -1)
    {
        Vector3 snapTemp;
        position = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].mPosition, mpManipulatedObject);
        mpManipulatedObject->mbIsInvalid = false;
        if (mLastSnapPointIndex != mCurrentSnapPointIndex)
        {
            if (mLastSnapPointIndex != -1)
            {
                mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].Clear();
                HandleSwapObject();
                KillSetiEffects(0x63e4b4f4, GetAudioState());
                CreateOneShotEffect(mUnsnapEffectID, mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].mPosition);
            }
            IAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0x60bad155, pAudio ? pAudio->GetState() : 0);
            CreateOneShotEffect(mSnapEffectID, position);
            HandleSwapObject();
            if (pNewSwap && pNewSwap != mpManipulatedObject)
            {
                mpSwapObject = pNewSwap;
                mLastSwapPointIndex = mCurrentSnapPointIndex;
                float lift = GetPropertyT_float(SPIDFromName("CommunityEditor"), 0, SPIDFromName("DisplacementLiftFactor"), 1.2f);
                const BoundingBox& extents = mpManipulatedObject->GetLocalExtents();
                float height = extents.upper.z - extents.lower.z;
                Vector3 offset = Vector3_Normalize(mpSwapObject->GetPosition()) * height * lift;
                Vector3 base = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].mPosition, mpSwapObject);
                mAnimatedObjectMap[mpSwapObject] = base + offset;
                mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].Clear();
            }
            mpCurrentSnapLayout->mpEntries[mCurrentSnapPointIndex].Occupy(GetObjectSnapInterface(mpManipulatedObject));
            bChanged = true;
        }
    }
    else
    {
        if (mLastSnapPointIndex != -1)
        {
            mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].Clear();
            HandleSwapObject();
            IAudioSystem* pAudioNoSnap = GetSystemAT();
            KillSetiEffects(0x63e4b4f4, pAudioNoSnap ? pAudioNoSnap->GetState() : 0);
            CreateOneShotEffect(mUnsnapEffectID, mpCurrentSnapLayout->mpEntries[mLastSnapPointIndex].mPosition);
            bChanged = true;
        }
    }

    mLastSnapPointIndex = mCurrentSnapPointIndex;

    if (mpSellbackLayout)
    {
        if (mpManipulatedObject->mbIsInvalid)
        {
            cString text;
            text.Load(0xdc351566, 0x40000010, L"Sell For ");
            cSellBackRollover* pRollover = mpSellbackLayout;
            pRollover->Show(text.GetText(), GetObjectCost(mpManipulatedObject, 1, -1), 1);
            CursorAttachment()->SetWindow(mpSellbackLayout ? (char*)mpSellbackLayout + 0x78 : 0);
        }
        else
            mpSellbackLayout->HideWin();
    }

    if (bChanged && pCity)
    {
        pCity->RefreshAfterEdit();
        if (interface_cast_building(mpManipulatedObject))
            FUN_00be2440(pCity, 0, 0);
    }

    mpManipulatedObject->SetPosition(position);

    Quaternion orientation;
    if (mpManipulatedObject && mpManipulatedObject->Cast(0x436f315))
    {
        Vector3 dir = normalized_safe(position - pCity->GetPosition());
        orientation = PlanetModel()->BuildSurfaceOrientation(position, dir);
    }
    else if (mpManipulatedObject && mpManipulatedObject->Cast(0x116d858))
    {
        Vector3 toCenter = normalized_safe(mpCommunity->GetCenter() - position);
        Vector3 up = normalized_safe(position);
        orientation = PlanetModel()->BuildSurfaceOrientation(position, Cross(up, toCenter));
    }
    else
        orientation = PlanetModel()->BuildSurfaceOrientation(position, mpManipulatedObject->GetDirection());
    mpManipulatedObject->SetOrientation(orientation);
    return false;
}

// @ 0x00d10f90
bool cCommunityEditor::EndObjectPlacement(void* pWindow, void* pMessage)
{
    cCity* pCity = mpCommunity ? (cCity*)mpCommunity->Cast(0xee9b2232) : 0;
    cTribe* pTribe = mpCommunity ? (cTribe*)mpCommunity->Cast(0x4f396a66) : 0;
    cPlaceable* pSwapPlaceable = mpSwapObject ? (cPlaceable*)mpSwapObject->Cast(0xe9cb8ba) : 0;

    if (mpManipulatedObject)
    {
        if (mpManipulatedObject->mbIsInvalid)
        {
            // Dropped on nothing: sell the object back.
            RemoveObjectFromCommunity(mpManipulatedObject);
            int cost = GetObjectCost(mpManipulatedObject, 1, -1);
            mpWinBudget->SetFlag(0, cost);
            const BoundingBox& extents = mpManipulatedObject->GetLocalExtents();
            const Vector3& p = mpManipulatedObject->GetPosition();
            float invLen = 1.0f / sqrtf(p.x * p.x + p.y * p.y + p.z * p.z + 1e-08f);
            float height = extents.upper.z;
            Vector3 offset;
            offset.x = (invLen * p.x) * height;
            offset.y = (p.y * invLen) * height;
            offset.z = (p.z * invLen) * height;
            const Vector3& p2 = mpManipulatedObject->GetPosition();
            Vector3 effectPos;
            effectPos.x = offset.x + p2.x;
            effectPos.y = p2.y + offset.y;
            effectPos.z = p2.z + offset.z;
            IAudioSystem* pAudio = GetSystemAT();
            KillSetiEffects(0x275cdfce, pAudio ? pAudio->GetState() : 0);
            if (mpManipulatedObject)
            {
                cSellEffect* pSellEffect = (cSellEffect*)mpManipulatedObject->Cast(0xe89adf71);
                if (pSellEffect)
                {
                    uint32_t effectID = pSellEffect->GetEffectID();
                    if (effectID)
                        CreateOneShotEffect(effectID, effectPos);
                }
            }
            if (pTribe)
                pTribe->FUN_00c947d0((float)cost, &effectPos);
            else
                CameraManager()->PlayEffect(pSwapPlaceable ? 0x64d02d1 : 0x64d03a2, mpManipulatedObject->GetPosition(),
                                            mpManipulatedObject->GetDirection(), -1, cost, 1.0f);
        }
        else
        {
            if (mpSwapObject)
            {
                cCombatant* pCombatant = (cCombatant*)mpSwapObject->Cast(0x13f94d4);
                cBuildingSet* pBuildingSet = mpSwapObject ? (cBuildingSet*)mpSwapObject->Cast(0x436f315) : 0;
                bool bBlocked = pSwapPlaceable && pSwapPlaceable->FUN_00c3f540();
                bool bCannotSnap = (pSwapPlaceable && pSwapPlaceable->FUN_00c3f540()) || (pBuildingSet && FUN_00d096e0(pBuildingSet));
                if (pCombatant && pCombatant->GetDamageState() == 2 && !bBlocked)
                    RemoveObjectFromCommunity(mpSwapObject);
                else if (mOriginalSnapPointIndex != -1 && !bCannotSnap)
                {
                    mpCurrentSnapLayout->mpEntries[mOriginalSnapPointIndex].Occupy(GetObjectSnapInterface(mpSwapObject));
                    Vector3 snapTemp;
                    Vector3 p = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[mOriginalSnapPointIndex].mPosition, mpSwapObject);
                    mAnimatedObjectMap[mpSwapObject] = p;
                }
                else
                {
                    int snapIndex = GetIndexOfClosestSnapPoint(mpCurrentSnapLayout, mpManipulatedObject->GetPosition(), 1, 0);
                    if (snapIndex != -1 && !bCannotSnap)
                    {
                        mpCurrentSnapLayout->mpEntries[snapIndex].Occupy(GetObjectSnapInterface(mpSwapObject));
                        Vector3 snapTemp;
                        Vector3 p = *SnapPointToPlanetIfNecessary(&snapTemp, mpCurrentSnapLayout->mpEntries[snapIndex].mPosition, mpSwapObject);
                        mAnimatedObjectMap[mpSwapObject] = p;
                    }
                    else
                    {
                        mpWinBudget->SetFlag(0, GetObjectCost(mpSwapObject, 1, -1));
                        IAudioSystem* pAudio = GetSystemAT();
                        KillSetiEffects(0x275cdfce, pAudio ? pAudio->GetState() : 0);
                        RemoveObjectFromCommunity(mpSwapObject);
                    }
                }
                mpSwapObject = 0;
                mLastSwapPointIndex = -1;
            }
            if (pCity)
            {
                pCity->RefreshAfterEdit();
                if (mpManipulatedObject)
                {
                    cPlaceable* pPlaceable = (cPlaceable*)mpManipulatedObject->Cast(0xe9cb8ba);
                    if (pPlaceable)
                    {
                        FUN_00be2440(pCity, 0, 0);
                        Quaternion q;
                        if (pCity->FUN_00bdfb00(pPlaceable, &q))
                            pPlaceable->mSpatial.SetOrientation(q);
                        if (NounManager()->GetCurrentTerrainSphere()->FUN_00c75420() >= 1 && FUN_00d08f00(mpManipulatedObject))
                        {
                            ResourceKey key;
                            key.instanceID = 0x521f703;
                            key.typeID = 0;
                            key.groupID = 0xaa9a8ed7;
                            cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
                            if (pSphere)
                                pSphere->FUN_00c78420(&key);
                        }
                    }
                }
            }
            FUN_00d0bcf0(mpManipulatedObject);
            const Vector3& pos = mpManipulatedObject->GetPosition();
            IAudioSystem* pAudio = GetSystemAT();
            Start3dSoundByName(0xe9c2e06e, pAudio ? pAudio->GetState() : 0, pos);
            CreateOneShotEffect(mPlunkEffectID, pos);
            if (mpManipulatedObject)
            {
                cTool* pTool = (cTool*)mpManipulatedObject->Cast(0x116d858);
                if (pTool && pTribe)
                {
                    if (!pTribe->FUN_00c8ec00(pTool->GetToolType()))
                    {
                        Vector3 zero(0.0f, 0.0f, 0.0f);
                        FUN_00e398e0(0x25c8b21a, pTribe->FUN_00c8e820(0) + 0x504, &zero, FUN_00c9cec0(pTool->GetToolType()), pTribe->mField234, 0, 0);
                        pTribe->FUN_00c8ebe0(pTool->GetToolType());
                    }
                    cSetCreationMsg msg(pTool->GetToolType());
                    int toolType = msg.mToolType;
                    char* pRecord = pTribe->FUN_00c8e820(pTribe->FUN_00c8e820(toolType) ? toolType : 0);
                    msg.mKey = *(ResourceKey*)(pRecord + 0x504);
                    MessageServer()->PostMessage(0x53850baf, &msg, 0);
                }
            }
        }
    }

    SetManipulatedObject(0);
    if (mpSellbackLayout)
        mpSellbackLayout->HideWin();
    mpCurrentSnapLayout = 0;
    mAttractorEffectID = 0;
    mSnapEffectID = 0;
    mUnsnapEffectID = 0;
    mPlunkEffectID = 0;
    mRipEffectID = 0;
    FUN_00d0dea0();
    if (mpSellbackRollover)
        mpSellbackRollover->Hide();
    FUN_00d0a390();
    FUN_00d0a5b0();
    return false;
}

} // namespace SP
