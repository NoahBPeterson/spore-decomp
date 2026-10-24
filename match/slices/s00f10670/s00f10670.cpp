// Slice s00f10670: 0x00F10BD0 (2249 bytes), per-frame update of the creature-stage "target" HUD
// controller (a UTFWin::InteractiveWinProc subclass, ret 8; it ends with the base-class call
// InteractiveWinProc::OnWinProcAdd(arg1) at 0x010829f0, so arg1 is passed straight through).
//
// What it does, read off the asm: converts the millisecond tick (arg2) to seconds, feeds the avatar
// (cGameNounManager::GetAvatar), updates the ability/timer bars and percent/number read-outs
// (UI ids 0x685a85e/0x4d039a8 and 0x73a95e0/0x73a9570: flag 2 = "low" when value*100 < threshold,
// number text = ceil(value)), picks the current camera-selection target (Cast() chain), highlights
// and un-highlights combatants, and keeps an effect instance (mpEffect) following the target
// (position, orientation from the planet surface normal, scale).
//
// NAMING NOTE: no symbol is known for 0x00F10BD0 (a caller-scored PDB candidate was
// cCommunityEditor::UpdateBuildingEffectivenessEffects, which does not fit); the class name
// cHudTargetController and every FUN_ name are Claude-coined placeholders from the addresses.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (x87 float args, no EH, no cookie).
#include "types.h"
#include <math.h>

#pragma warning(disable:4035)
__forceinline int CeilToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        add      ecx, 1
        ucomiss  xmm1, xmm0
        cmovb    eax, ecx
    }
}

namespace EA { namespace Locale {
int SetNumberString(int64_t value, wchar_t* buffer, int bufferSize);   // 0x00881ae0
} }

struct Vector3
{
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};

struct Matrix3 { float m[9]; };

// transform message for the effect instance (ctor 0x00434040 clears it); mFlags bit 2 = rotation set,
// bit 4 = position set, mCount counts the updates
struct XformMsg
{
    uint16_t mFlags;                  // +0x00
    uint16_t mCount;                  // +0x02
    Vector3 mPos;                     // +0x04
    float mScale;                     // +0x10
    Matrix3 mRot;                     // +0x14
    uint32_t pad38[2];
    XformMsg();                       // 0x00434040
};

class IWindow
{
public:
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual void* Cast(uint32_t typeID);                      // +0x0c
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual uint32_t GetFlags();                              // +0x20
    virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
    virtual void s34(); virtual void s38(); virtual void s3c(); virtual void s40();
    virtual void s44(); virtual void s48(); virtual void s4c(); virtual void s50();
    virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60();
    virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70();
    virtual void s74(); virtual void s78();
    virtual void SetFlag(int flag, bool value);                // +0x7c
    virtual void SetText(const wchar_t* pText);               // +0x80
};

class cSPUILayout
{
public:
    IWindow* FindWindowByID(uint32_t controlID, bool recursive);   // 0x008105b0 (ret 8)
};

// holder at [this+0x5c]; its layout pointer sits at +8 (0x0093b6c0 is the out-of-line getter)
class cUIHolder
{
public:
    cSPUILayout* GetLayout();                                  // 0x0093b6c0
    void SetValue(uint32_t id, float value);                   // 0x00e012d0 (ret 8)
};

class IOwner {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual bool IsFlagged();  // +0x2c
};

class IBody {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual Vector3* GetPosition();  // +0x2c
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual bool IsFlagged();  // +0x48
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual float* GetBounds(Vector3* pTemp);  // +0x6c
    virtual void s70();
    virtual float GetRadius();  // +0x74
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sA0();
    virtual void sA4();
    virtual void sA8();
    virtual void sAc();
    virtual void sB0();
    virtual void sB4();
    virtual void* Cast(uint32_t typeID);  // +0xb8
    virtual void sBc();
    virtual void ReleaseVector();  // +0xc0
};

class IObject {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void* Cast(uint32_t typeID);  // +0xc
};

// eastl::fixed_vector<IBody*, 8> as built by the camera query at 0x00F10670.
struct FixedVector
{
    IBody** mpBegin;        // +0x00
    IBody** mpEnd;          // +0x04
    IBody** mpCapacity;     // +0x08
    uint32_t mPad0c;        // +0x0c
    uint32_t mPad10;        // +0x10
    uint32_t mFlag14;       // +0x14
    IBody* mBuffer[8];      // +0x18

    FixedVector()
        : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 8),
          mPad0c(0), mPad10(0), mFlag14(0) {}
};

class ICameraSource {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual IObject* GetSelection();  // +0x34
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual bool Query(const Vector3* pPos, float radius, FixedVector* pOut,
                       int a, void* pCallback, void* pUser);  // +0x48
};

class IEffect {
public:
    virtual void s00();
    virtual void Release();  // +0x4
    virtual void Stop(int a);  // +0x8
    virtual void SetVisible(int a);  // +0xc
    virtual void s10();
    virtual void s14();
    virtual void SetTransform(XformMsg* pMsg);  // +0x18
    virtual void s1c();
    virtual void GetTransform(XformMsg* pMsg);  // +0x20
};

class IEffectsManager {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual bool CreateEffect(uint32_t handle, int a, IEffect** ppEffect);  // +0x2c
};

class ICombatantBase {
public:
    virtual void s00();
    virtual void s04();
    virtual IBody* GetBody();  // +0x8
    virtual IOwner* GetOwner();  // +0xc
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void AddRef();  // +0x60
    virtual void Release();  // +0x64
};

class IAvatarVtbl {
public:
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void sb0();
    virtual void* FindAbility(int id);  // +0xb4
};

// ---------------------------------------------------------------------------------------
// Combatants, avatar, effects (stubs: only the slots/fields used here)
// ---------------------------------------------------------------------------------------
class cCombatant : public ICombatantBase
{
public:
    int GetDamageState();                                      // 0x008e7f80 (field +0x34)
    bool FUN_00bfc480();                                       // 0x00bfc480
    float FUN_00bfc490();                                      // 0x00bfc490
};

class cAvatar : public IAvatarVtbl
{
public:
    uint32_t pad04[(0x5e0 - 4) / 4];
    float mSomeValue;                                          // +0x5e0
    uint32_t pad5e4[(0xe58 - 0x5e4) / 4];
    float mValueA;                                             // +0xe58
    float mValueB;                                             // +0xe5c
    uint8_t pade60[2];
    uint8_t mModeA;                                            // +0xe62
    uint8_t mModeB;                                            // +0xe63

    cCombatant* GetCombatant() { return (cCombatant*)((char*)this + 0x5a8); }

    int FUN_00c0c080(int kind);                                // 0x00c0c080
    void FUN_00c04590();                                       // 0x00c04590
    cCombatant* FUN_00c0ee60();                                // 0x00c0ee60
    int FUN_00c0c1b0();                                        // 0x00c0c1b0
    struct cAvatarState* FUN_00c0ee90();                       // 0x00c0ee90
    void FUN_00c0eec0(uint32_t time, bool flag);               // 0x00c0eec0 (ret 8)
    void FUN_00c18740(uint32_t time, bool flag);               // 0x00c18740 (ret 8)
};
struct cAvatarState { uint32_t pad[0x137 / 4]; uint8_t pad134[3]; uint8_t mFlag; };   // flag byte at +0x137

class cGameNounManager
{
public:
    cAvatar* GetAvatar();                                      // 0x00b1fdb0
};

struct cTargetInfo { uint32_t pad[0x120 / 4]; };               // combatant at +0x120

class cTimerBar
{
public:
    void Update(uint32_t time, cAvatar* pAvatar);              // 0x00d2bd00 (ret 8)
};

struct cPickResult { uint32_t mKey; };

class cResourceObjA
{
public:
    cPickResult* FUN_00f3dc70(uint32_t id);                    // 0x00f3dc70 (ret 4)
    void* FUN_00f3e900(uint32_t id);                           // 0x00f3e900 (ret 4)
};
struct cRecord { uint32_t pad00[0x28 / 4]; uint32_t mKeyA; uint32_t mKeyB; uint32_t pad30[(0x1ac - 0x30) / 4]; };
struct cRecordVec { cRecord* mpBegin; cRecord* mpEnd; };
class cResourceObjB
{
public:
    cRecordVec* FUN_00f191d0();                                // 0x00f191d0
    float FUN_00f19d10();                                      // 0x00f19d10
};
struct cResourceHub { uint32_t pad00[0x74 / 4]; cResourceObjA* mpA; cResourceObjB* mpB; };
extern cResourceHub* gResourceHub;                             // 0x016c7aa4

struct cModeInfo { uint32_t pad00[0x2c / 4]; int mMode; };     // mode at +0x2c

class cThingF
{
public:
    void FUN_00f18a00(float v);                                // 0x00f18a00 (ret 4)
    void FUN_00f18dc0(uint32_t time);                          // 0x00f18dc0 (ret 4)
};

cGameNounManager* NounManager();                               // 0x00b3d300
cModeInfo* GetModeInfo();                                      // 0x00b3d4d0
ICameraSource* GetCameraSource();                              // 0x00b3d240
IEffectsManager* EffectsManager();                             // 0x0067ddd0
int FUN_00d48cb0(int id);                                      // 0x00d48cb0 (cdecl)
void* FUN_00d49ee0(void* p);                                   // 0x00d49ee0 (cdecl)
bool FUN_00b18f70(void* p, int mask);                          // 0x00b18f70 (cdecl)
void VerbTray_Update(float dt);                                // 0x00d4a930 (cdecl)
int FUN_00d2e490();                                            // 0x00d2e490
void FUN_00b69930(IOwner* p, float v, int a);                  // 0x00b69930 (cdecl)
void FUN_00b69990(IOwner* p);                                  // 0x00b69990 (cdecl)
uint32_t ResourceKeyToIcon(void* p);                           // 0x00eece20 (cdecl)
uint32_t FUN_00f0e2a0(float v, int sel, int flag);             // 0x00f0e2a0 (cdecl)
void OrthogonalVector(Vector3* pOut, const Vector3* pIn);      // 0x006985b0
void Matrix3FromFacingAndUp(Matrix3* pOut, const Vector3* pFacing, const Vector3* pUp);   // 0x0069b440

class cPlanetModel
{
public:
    void GetUpVector(Vector3* pOut, const Vector3* pPos);      // 0x00b7e3b0
};
cPlanetModel* PlanetModel();                                   // 0x00b3d350

extern float kLowThreshold;                                    // 0x01687a0c

// ---------------------------------------------------------------------------------------
// Containers / interfaces used by 0x00F10670
// ---------------------------------------------------------------------------------------

// EA::UTFWinControls::IWinText - only the alpha value at +0x80 is touched here.
struct IWinText
{
    uint8_t mPad00[0x80];
    float mAlpha;                                           // +0x80
};

// The object returned by IBody::Cast(0xd0036e08): target HUD data.
class CCastObject
{
public:
    virtual void AddRef();                                  // +0x00
    virtual void Release();                                 // +0x04
    uint8_t mPad04[0x24 - 0x04];
    uint32_t mKey;                                          // +0x24
    uint8_t mPad28[0xb54 - 0x28];
    IWinText* mpText;                                       // +0xb54
    uint32_t mFlags;                                        // +0xb58
};

// eastl::AutoRefCount<T> value stored in the hash map.
struct AutoRefCountSlot
{
    void* mpObject;                                         // +0x00
    void __thiscall Assign(void* pObject);                  // 0x00b5f950
};

struct HashNode
{
    uint32_t mKey;                                          // +0x00
    AutoRefCountSlot mValue;                                // +0x04
    HashNode* mpNext;                                       // +0x08
};

struct MapIterator
{
    HashNode* mpNode;                                       // +0x00
    HashNode** mpBucket;                                    // +0x04
};

// eastl::hashtable<...> base fields that 0x00F10670 reads.
struct HashBase
{
    uint8_t mExtract;                                       // +0x00
    uint8_t mEqual;                                         // +0x01
    uint8_t mHash;                                          // +0x02
    uint8_t mModRange;                                      // +0x03
    HashNode** mpBucketArray;                               // +0x04
    uint32_t mnBucketCount;                                 // +0x08
    uint32_t mnElementCount;                                // +0x0c
    uint8_t mRehashPolicy[0x0c];                            // +0x10
    uint8_t mAllocator[0x18];                               // +0x1c
};

// fixed_hash_map<uint32_t, AutoRefCount<T>, 16 nodes, 17 buckets>:
// buckets at +0x34 (18 slots), fixed node pool at +0x7c (16 * 0x0c bytes).
class FixedMap : public HashBase
{
public:
    HashNode* mBucketBuffer[18];                            // +0x34
    uint8_t mNodeBuffer[0xc0];                              // +0x7c

    void __thiscall Construct(const void* pHash, const void* pEqual);      // 0x00d2d5c0
    AutoRefCountSlot* __thiscall FindOrInsert(const uint32_t* pKey);        // 0x00b76460
    MapIterator* __thiscall Erase(MapIterator* pOut, HashNode* pNode,
                                  HashNode** ppBucket);                     // 0x00d2c9f0
    void __thiscall Clear(HashNode** ppBuckets, uint32_t nBuckets);         // 0x00a24480
};

class IViewer
{
public:
    void GetCameraLocationInfo(Vector3* pPos, int a, int b, int c);  // 0x007c3d30
};

class IAppSub
{
public:
    virtual void a00();
    virtual void a04();
    virtual void a08();
    virtual void a0c();
    virtual void a10();
    virtual void a14();
    virtual void a18();
    virtual IViewer* GetViewer();                           // +0x1c
};

class IApp
{
public:
    virtual void b00();
    virtual void b04();
    virtual void b08();
    virtual void b0c();
    virtual void b10();
    virtual void b14();
    virtual void b18();
    virtual void b1c();
    virtual void b20();
    virtual void b24();
    virtual void b28();
    virtual void b2c();
    virtual void b30();
    virtual void b34();
    virtual void b38();
    virtual void b3c();
    virtual void b40();
    virtual void b44();
    virtual void b48();
    virtual void b4c();
    virtual IAppSub* GetSub();                              // +0x50
};

IApp* App();                                                // 0x0067dd10
void __cdecl EASTL_allocator_deallocate(void* p);           // 0x00f47380
extern "C" void FUN_00d9a9c0();                             // 0x00d9a9c0
extern Vector3 gCameraLocation;                             // 0x016c8004

// ---------------------------------------------------------------------------------------
// The controller
// ---------------------------------------------------------------------------------------
class cHudTargetController
{
public:
    uint32_t pad00[0x4c / 4];
    cCombatant* mpTarget;                                      // +0x4c (refcounted: +0x60/+0x64)
    IEffect* mpEffect;                                         // +0x50
    int mSelection;                                            // +0x54
    uint8_t mSelFlag;                                          // +0x58
    uint8_t mActive;                                           // +0x59
    uint8_t pad5a[2];
    cUIHolder* mpUI;                                           // +0x5c
    uint32_t pad60[2];
    cThingF* mpThing;                                          // +0x68
    uint32_t pad6c[(0xb0 - 0x6c) / 4];
    cTimerBar mTimerBar;                                       // +0xb0
    uint32_t padb4[(0x14c - 0xb4) / 4];
    FixedMap mSub14c;                                          // +0x14c

    void FUN_00f0e520(cAvatar* pAvatar);                       // 0x00f0e520 (ret 4)
    void FUN_00f10670(FixedMap* pSub, float dt);               // 0x00f10670 (ret 8)
    void FUN_00f0e6e0();                                       // 0x00f0e6e0
    void FUN_00f0efa0();                                       // 0x00f0efa0
    void OnWinProcAdd(uint32_t arg);                           // 0x010829f0 (base class, ret 4)

    void Update(uint32_t arg1, uint32_t timeMs);
};

// @ 0x00F10BD0
void cHudTargetController::Update(uint32_t arg1, uint32_t timeMs)
{
    cAvatar* pAvatar = NounManager()->GetAvatar();
    FUN_00f0e520(pAvatar);
    float dt = (float)timeMs * 0.0001f;
    FUN_00f10670(&mSub14c, dt);

    if (pAvatar->mModeA || pAvatar->mModeB) {
        bool found = false;
        int id = pAvatar->FUN_00c0c080(pAvatar->mModeA ? 0x53 : 0x11);
        int windowID = FUN_00d48cb0(id);
        if (windowID) {
            IWindow* pWin = mpUI->GetLayout()->FindWindowByID(windowID, true);
            if (pWin) {
                IWindow* pCast = (IWindow*)pWin->Cast(0x8ed27e7a);
                if (pCast && (pCast->GetFlags() & 2))
                    found = true;
            }
        }
        if (!found) {
            void* pAbility = pAvatar->FindAbility(id);
            if (pAbility) {
                void* pData = FUN_00d49ee0(pAbility);
                if (FUN_00b18f70(pData, 0x3ff))
                    found = true;
            }
        }
        if (pAvatar->mModeA)
            pAvatar->FUN_00c18740(timeMs, found);
        else
            pAvatar->FUN_00c0eec0(timeMs, found);
    }

    if (mActive) {
        pAvatar->FUN_00c04590();
        VerbTray_Update(dt);
        FUN_00f0e6e0();

        cCombatant* pAvatarCombatant = pAvatar->GetCombatant();
        if (!pAvatarCombatant->FUN_00bfc480()) {
            float v = pAvatarCombatant->FUN_00bfc490();
            mpUI->SetValue(0x18ac46e, v);
            IWindow* pBar = mpUI->GetLayout()->FindWindowByID(0x685a85e, true);
            if (pBar)
                pBar->SetFlag(2, v * 100.0f < kLowThreshold);
            int n = CeilToInt(pAvatar->mSomeValue);
            IWindow* pText = mpUI->GetLayout()->FindWindowByID(0x4d039a8, true);
            if (pText) {
                wchar_t buffer[16];
                EA::Locale::SetNumberString(n, buffer, 32);
                pText->SetText(buffer);
            }
        }

        float ratio = pAvatar->mValueA / pAvatar->mValueB;
        mpUI->SetValue(0x73a95a0, ratio);
        IWindow* pBar2 = mpUI->GetLayout()->FindWindowByID(0x73a95e0, true);
        if (pBar2)
            pBar2->SetFlag(2, ratio * 100.0f < kLowThreshold);
        int n2 = CeilToInt(pAvatar->mValueA);
        IWindow* pText2 = mpUI->GetLayout()->FindWindowByID(0x73a9570, true);
        if (pText2) {
            wchar_t buffer[16];
            EA::Locale::SetNumberString(n2, buffer, 32);
            pText2->SetText(buffer);
        }
        FUN_00f0efa0();

        if (mActive) {
            cCombatant* pCurrent = pAvatar->FUN_00c0ee60();
            if (pCurrent && pCurrent->GetDamageState() == 2)
                pCurrent = 0;
            mTimerBar.Update(timeMs, pAvatar);

            IObject* pSelection = GetCameraSource()->GetSelection();
            void* pAsA;
            cCombatant* pTarget;
            void* pAsC;
            void* pAsD;
            void* pAsE;
            if (!pSelection) {
                pAsA = 0;
                pTarget = 0;
            } else {
                pAsA = pSelection->Cast(0x17f243b);
                pTarget = (cCombatant*)pSelection->Cast(0x13f94d4);
                pAsC = pSelection->Cast(0xd0036e08);
                pAsD = pSelection->Cast(0x137e8e0);
                pAsE = pSelection->Cast(0xe9cb8ba);
                if (!pAsC && !pAsD && (!pAsE || ((cCombatant*)((char*)pAsE + 0x120))->FUN_00bfc480()))
                    pTarget = 0;
            }

            bool skipRest = false;
            if (pCurrent) {
                if (pCurrent == pTarget) {
                    FUN_00b69990(pTarget->GetOwner());
                    skipRest = true;
                } else if (pCurrent->GetBody()->IsFlagged() && FUN_00d2e490() == 1) {
                    FUN_00b69930(pCurrent->GetOwner(), pCurrent->FUN_00bfc490(), 0);
                }
            }
            if (!skipRest) {
                if (pTarget && pTarget != pAvatar->GetCombatant() && pTarget->GetDamageState() != 2)
                    FUN_00b69990(pTarget->GetOwner());
                if (pAsA) {
                    cPickResult* pPick = gResourceHub->mpA->FUN_00f3dc70((uint32_t)pAsA);
                    void* pIconSource = gResourceHub->mpA->FUN_00f3e900((uint32_t)pAsA);
                    if (pPick && pIconSource) {
                        uint32_t icon = ResourceKeyToIcon(pIconSource);
                        if (icon == 0x6031c03a || icon == 0xcf56099a) {
                            cRecordVec* pVec = gResourceHub->mpB->FUN_00f191d0();
                            int count = (int)(pVec->mpEnd - pVec->mpBegin);
                            for (uint32_t i = 0; i < (uint32_t)count; ++i) {
                                cRecord* pRec = &pVec->mpBegin[i];
                                if (pRec->mKeyA == pPick->mKey || pRec->mKeyB == pPick->mKey) {
                                    FUN_00b69990((IOwner*)pAsA);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }

        cCombatant* pNewTarget = pAvatar->FUN_00c0ee60();
        int newSel = pAvatar->FUN_00c0c1b0();
        uint8_t newFlag = 0;
        cAvatarState* pState = pAvatar->FUN_00c0ee90();
        if (pState)
            newFlag = pState->mFlag;

        if (pNewTarget != mpTarget || newSel != mSelection || newFlag != mSelFlag) {
            if (mpTarget && mpEffect) {
                mpEffect->SetVisible(1);
                if (mpEffect) {
                    IEffect* p = mpEffect;
                    mpEffect = 0;
                    p->Release();
                }
            }
            cCombatant* pOld = mpTarget;
            if (pNewTarget != pOld) {
                if (pNewTarget)
                    pNewTarget->AddRef();
                mpTarget = pNewTarget;
                if (pOld)
                    pOld->Release();
            }
            mSelection = newSel;
            mSelFlag = newFlag;
            if (mpTarget) {
                float scale = mpTarget->GetBody()->GetRadius();
                if (!pState)
                    scale = 3.0f;
                uint32_t handle = FUN_00f0e2a0(scale, newSel, newFlag);
                if (handle) {
                    IEffectsManager* pEffects = EffectsManager();
                    IEffect** ppEffect = &mpEffect;
                    if (*ppEffect) {
                        IEffect* p = *ppEffect;
                        *ppEffect = 0;
                        p->Release();
                    }
                    if (pEffects->CreateEffect(handle, 0, ppEffect)) {
                        XformMsg msg;
                        (*ppEffect)->GetTransform(&msg);
                        ++msg.mCount;
                        msg.mScale = scale;
                        (*ppEffect)->SetTransform(&msg);
                        (*ppEffect)->Stop(0);
                    }
                }
            }
        }

        if (mpTarget) {
            if (mpTarget->GetOwner()->IsFlagged() || mpTarget->GetDamageState() == 2) {
                if (mpEffect) {
                    mpEffect->SetVisible(0);
                    if (mpEffect) {
                        IEffect* p = mpEffect;
                        mpEffect = 0;
                        p->Release();
                    }
                }
                if (mpTarget) {
                    cCombatant* p = mpTarget;
                    mpTarget = 0;
                    p->Release();
                }
            }
        }

        if (mpTarget && mpEffect) {
            XformMsg msg;
            mpEffect->GetTransform(&msg);
            Vector3 pos;
            if (newFlag) {
                pos = *mpTarget->GetBody()->GetPosition();
            } else {
                Vector3 temp;
                float* b = mpTarget->GetBody()->GetBounds(&temp);
                pos = Vector3((b[0] + b[3]) * 0.5f, (b[4] + b[1]) * 0.5f, (b[5] + b[2]) * 0.5f);
            }
            msg.mPos = pos;
            ++msg.mCount;
            msg.mFlags |= 4;

            Vector3 here(msg.mPos);
            Vector3 up;
            PlanetModel()->GetUpVector(&up, &here);
            Vector3 facing;
            OrthogonalVector(&facing, &up);
            Matrix3FromFacingAndUp(&msg.mRot, &facing, &up);
            msg.mFlags |= 2;
            ++msg.mCount;

            msg.mPos = *mpTarget->GetBody()->GetPosition();
            msg.mFlags |= 4;
            ++msg.mCount;
            mpEffect->SetTransform(&msg);
        }

        int mode = GetModeInfo()->mMode;
        if (mode != 1 && mode != 2) {
            cThingF* pThing = mpThing;
            pThing->FUN_00f18a00(gResourceHub->mpB->FUN_00f19d10());
            mpThing->FUN_00f18dc0(timeMs);
        }
    }
    OnWinProcAdd(arg1);
}

// @ 0x00F10670
void cHudTargetController::FUN_00f10670(FixedMap* pMap, float dt)
{
    uint8_t hashStub = 0;
    uint8_t equalStub = 0;
    FixedMap localMap;
    localMap.Construct(&hashStub, &equalStub);

    IViewer* pViewer = App()->GetSub()->GetViewer();
    if (pViewer)
    {
        Vector3 camPos = gCameraLocation;
        pViewer->GetCameraLocationInfo(&camPos, 0, 0, 0);

        FixedVector results;
        const float kSelectRadius = 3.0f;
        float queryRadius = kSelectRadius * kSelectRadius;
        bool queryOk = GetCameraSource()->Query(&camPos, queryRadius, &results, 0,
                                                (void*)&FUN_00d9a9c0, 0);

        float cullRadius2 = kSelectRadius * kSelectRadius;
        if (queryOk && results.mpBegin != results.mpEnd)
        for (IBody** ppBody = results.mpBegin; ppBody < results.mpEnd; ++ppBody)
        {
            IBody* pBody = *ppBody;
            if (!pBody)
                continue;

            float bodyRadius = pBody->GetRadius();
            Vector3 temp;
            float* pBounds = pBody->GetBounds(&temp);

            float dx = camPos.x - (pBounds[0] + pBounds[3]) * 0.5f;
            float dy = camPos.y - (pBounds[4] + pBounds[1]) * 0.5f;
            float dz = camPos.z - (pBounds[5] + pBounds[2]) * 0.5f;

            float dist2 = ((dx * dx + dz * dz) + dy * dy) - bodyRadius * bodyRadius;
            if (dist2 < 0.0f)
                dist2 = 0.0f;

            if (dist2 <= cullRadius2)
            {
                CCastObject* pCast = (CCastObject*)pBody->Cast(0xd0036e08);
                if (pCast && pCast->mpText)
                {
                    float target = (pCast->mFlags & 0x200) ? 0.0f : 0.1f;
                    double p = pow(0.1, (double)dt * 15.0);
                    IWinText* pText = pCast->mpText;
                    pText->mAlpha = (float)((1.0 - p) * (double)target +
                                            (double)pText->mAlpha * p);
                    pCast->mFlags |= 0x800;

                    uint32_t key = pCast->mKey;
                    AutoRefCountSlot* pSlot = localMap.FindOrInsert(&key);
                    pSlot->Assign(pCast);
                }
            }
        }

        for (IBody** ppBody = results.mpBegin; ppBody < results.mpEnd; ++ppBody)
        {
            IBody* pBody = *ppBody;
            if (pBody)
                pBody->ReleaseVector();
        }
        if (results.mpBegin && *(uint32_t*)(results.mpBegin - 1) != 0)
            EASTL_allocator_deallocate(results.mpBegin);
    }

    // Walk the persistent map; entries that were not seen this frame fade out.
    HashNode* pNode = pMap->mpBucketArray[0];
    HashNode** ppBucket = pMap->mpBucketArray;
    if (!pNode)
    {
        ++ppBucket;
        while (!*ppBucket)
            ++ppBucket;
        pNode = *ppBucket;
    }

    HashNode* pEnd = pMap->mpBucketArray[pMap->mnBucketCount];
    while (pNode != pEnd)
    {
        uint32_t key = pNode->mKey;
        uint32_t bucketIndex = key % localMap.mnBucketCount;
        HashNode* pLocal = localMap.mpBucketArray[bucketIndex];
        while (pLocal && pLocal->mKey != key)
            pLocal = pLocal->mpNext;

        if (!pLocal)
        {
            CCastObject* pCast = (CCastObject*)pNode->mValue.mpObject;
            if (pCast && pCast->mpText)
            {
                IWinText* pText = pCast->mpText;
                double p = pow(0.1, (double)dt * 15.0);
                float alpha = (float)((1.0 - p) * 1.0 + (double)pText->mAlpha * p);
                pText->mAlpha = alpha;
                pCast->mFlags |= 0x800;

                if (!(fabsf(alpha - 1.0f) < 0.01f))
                {
                    pNode = pNode->mpNext;
                    while (!pNode)
                    {
                        ++ppBucket;
                        pNode = *ppBucket;
                    }
                    continue;
                }

                pText->mAlpha = 1.0f;
                pCast->mFlags &= ~0x800u;
            }

            MapIterator next;
            pMap->Erase(&next, pNode, ppBucket);
            pNode = next.mpNode;
            ppBucket = next.mpBucket;
        }
        else
        {
            pNode = pNode->mpNext;
            while (!pNode)
            {
                ++ppBucket;
                pNode = *ppBucket;
            }
        }
    }

    // Merge the entries seen this frame back into the persistent map.
    pNode = localMap.mpBucketArray[0];
    ppBucket = localMap.mpBucketArray;
    if (!pNode)
    {
        ++ppBucket;
        while (!*ppBucket)
            ++ppBucket;
        pNode = *ppBucket;
    }

    pEnd = localMap.mpBucketArray[localMap.mnBucketCount];
    while (pNode != pEnd)
    {
        uint32_t key = pNode->mKey;
        CCastObject* pValue = (CCastObject*)pNode->mValue.mpObject;
        AutoRefCountSlot* pSlot = pMap->FindOrInsert(&key);
        CCastObject* pOld = (CCastObject*)pSlot->mpObject;
        if (pValue != pOld)
        {
            if (pValue)
                pValue->AddRef();
            pSlot->mpObject = pValue;
            if (pOld)
                pOld->Release();
        }

        pNode = pNode->mpNext;
        while (!pNode)
        {
            ++ppBucket;
            pNode = *ppBucket;
        }
    }

    localMap.Clear(localMap.mpBucketArray, localMap.mnBucketCount);
    if (localMap.mnBucketCount > 1 && localMap.mpBucketArray != localMap.mBucketBuffer)
        EASTL_allocator_deallocate(localMap.mpBucketArray);
}
