// slice s005744b0 -- SP::cAppModeEditorBase: budget / camera / thumbnail / sound helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (scalar movss/comiss, x87 float args).
// Retail cAppModeEditorBase layout differs from the 2008 PDB past +0x1c, so most members are
// placed by the offsets the disassembly uses; PDB names are kept where the use agrees.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};

struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};

struct BoundingBox { Vector3 lower; Vector3 upper; };

namespace eastl {
template <size_t N>
struct bitset {
    uint32_t mWord[(N + 31) / 32];
    bitset() { for (size_t i = 0; i < (N + 31) / 32; ++i) mWord[i] = 0; }
    bitset& set(size_t i) { if (i < N) mWord[i >> 5] |= (uint32_t)1 << (i & 31); return *this; }
};
template <typename T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}

namespace EA {
template <typename T>
struct AutoRefCount {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}

namespace EA { namespace Random {
struct RandomLinearCongruential { uint32_t RandomUint32Uniform(uint32_t limit); };
} }
extern EA::Random::RandomLinearCongruential sMathRandom;   // 0x01601760

// EA::Variant-style property value: value storage, then flags/type words.
class Property {
public:
    uint32_t mValue[4];
    uint8_t  mnFlags;       // +0x10 (0x30 = value stored out of line)
    uint8_t  pad11;
    uint16_t mnType;        // +0x12 (0x0d = float)
    const float* GetFloat() const;                          // 0x0041ea70
    const float* GetValueFloat() const { return (mnFlags & 0x30) ? *(const float* const*)this : (const float*)this; }
    const float* GetFloatValue() const;                     // 0x005727e0
    const uint32_t* GetUInt32Value() const;                 // 0x005727b0
};

namespace SP {

class cPropertyList {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool GetPropertyAlloc(uint32_t id, Property*& out);          // +0x20
    virtual bool GetProperty(uint32_t id, Property*& out);               // +0x24
    bool GetBool(uint32_t id);                                           // 0x006a25a0
};
extern cPropertyList* sAppProperties;                                    // 0x015fd918

inline float GetPropertyFloat(cPropertyList* list, uint32_t id, float defaultValue)
{
    float value = defaultValue;
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd)
        value = *prop->GetFloat();
    return value;
}
inline float GetPropertyValueFloat(cPropertyList* list, uint32_t id, float defaultValue)
{
    float value = defaultValue;
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd)
        value = *prop->GetValueFloat();
    return value;
}

bool GetPropertyAsKeyInstance(cPropertyList* list, uint32_t id, uint32_t* out);                   // 0x006a12a0
bool GetPropertyArrayKey(cPropertyList* list, uint32_t id, int* count, ResourceKey** keys);       // 0x006a0ae0

class cPropertyListManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cPropertyList* GetPropertyList(uint32_t instanceID, uint32_t groupID);   // +0x58
};
cPropertyListManager* PropManager();                                     // 0x00401010

struct cSPEditorBlock {
    char pad0[0xc];
    cPropertyList* mpPropList;      // +0x0c
    char pad10[0xc];
    uint32_t mInstanceID;           // +0x1c
    uint32_t mGroupID;              // +0x20
    char pad24[0x1d8 - 0x24];
    float mCost;                    // +0x1d8
    char pad1dc[4];
    float mMinScale;                // +0x1e0
    float mMaxScale;                // +0x1e4
    char pad1e8[0x33c - 0x1e8];
    uint32_t mSoundData;            // +0x33c
    char pad340[0x5e4 - 0x340];
    uint32_t mPrice;                // +0x5e4
    char pad5e8[0xdc8 - 0x5e8];
    uint32_t mFlags;                // +0xdc8 (bit 7: paint, bit 11: limb)
    bool IsFlagSet(int bit) const { return (mFlags >> bit) & 1; }
    float GetPartScale();                                               // 0x0043f250
    float GetPartScaleFactor();                                         // 0x0043f4d0
};
float GetPaintScore(cSPEditorBlock* block);                             // 0x004a5c40

struct cSPEditorModel {
    char pad0[0xc];
    ResourceKey mKey;               // +0x0c
    int GetBlockCount();                                                // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                                    // 0x004accb0
    void GetComplexity(int* blocks, int* legs, int* colors, float* cost, int* bones);   // 0x004acd20
    void GetBoundingBox(BoundingBox* box, int flags);                   // 0x004ad550
};

namespace EditorUtils { bool GetCreatorType(const ResourceKey* key); }  // 0x00641900

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, int a, int b);   // 0x007c3d30
    void GetCameraTransform(Vector3* a, Vector3* b);                         // 0x007c4900
};

class cCameraManager;
class cCameraList {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual class cCreatureCameraBase* GetCamera(uint32_t id);              // +0x0c
    void GetCameraValues(float* a, float* b, float* c, Vector3* v);        // 0x005a2260
};

class cCreatureCameraBase {
public:
    void SetCreature(void* creature);                                       // 0x00627060
    void SetInitialCameraValues(float a, float b, float c, const Vector3& v); // 0x00626b50
    void SetCallback(void (*cb)(void*), void* data);                         // 0x00625350
};

class cCameraManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual void SetActiveCameraID(uint32_t id);                            // +0x34
    virtual cCameraList* GetCameras();                                      // +0x38
};

class cIApp {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual cCameraManager* GetCameraManager();                             // +0x50
    virtual void v54();
    virtual cViewer* GetViewer();                                           // +0x58
};
cIApp* App();                                                               // 0x0067dd10

class cIModelWorld {
public:
    virtual void v00();
    // slots 1..0x46 are placeholders
#define PH(n) virtual void ph##n();
    PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14)
    PH(15) PH(16) PH(17) PH(18) PH(19) PH(20) PH(21) PH(22) PH(23) PH(24) PH(25) PH(26) PH(27)
    PH(28) PH(29) PH(30) PH(31) PH(32) PH(33) PH(34) PH(35) PH(36) PH(37) PH(38) PH(39) PH(40)
    PH(41) PH(42) PH(43) PH(44) PH(45) PH(46) PH(47) PH(48) PH(49) PH(50) PH(51) PH(52) PH(53)
    PH(54) PH(55) PH(56) PH(57) PH(58) PH(59) PH(60) PH(61) PH(62) PH(63) PH(64) PH(65) PH(66)
    PH(67) PH(68) PH(69) PH(70)
    virtual void SetModelGroups(eastl::bitset<64>* include, eastl::bitset<64>* exclude, int flags);  // +0x11c
    PH(72) PH(73) PH(74) PH(75) PH(76) PH(77) PH(78) PH(79)
    virtual void SetLightingWorld(void* lighting);                           // +0x140
    virtual void* CreateLightingWorld(int a, int b, int c);                  // +0x144
#undef PH
};

class cModelManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual uint32_t GetModelGroup(uint32_t id, int create);                 // +0x28
};
cModelManager* ModelManager();                                              // 0x0067dd80

class cSPEditorResourceFactory { public: int Flush(bool b); };              // 0x004c49e0

class cSPEditorAnimatedCreatureManager { public: void* GetCreature(cViewer* viewer); };   // 0x0059ca70

class cEditorLaunchData { public: char pad[0x1c]; int mSelectedIndex; };

class cSPEditorBudget {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void SetRemaining(int type, int amount);                         // +0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void PurchaseBlock(cSPEditorBlock* block, int flags);            // +0x38
};

class cSPEditorUIPanel { public: bool IsActive(); };                         // 0x005ca920

class cSPEditorUI {
public:
    char GetMode();                                                          // 0x005dc450
    void SetModeEnabled(int b);                                              // 0x005dd090
    void Refresh(int a, int b);                                              // 0x005de690
};

class cWindowManager {
public:
    void HideWindow(uint32_t id);                                            // 0x0045b000
    int  IsWindowOpen(uint32_t id);                                          // 0x0045b210
    void OpenWindow(uint32_t id, int b);                                     // 0x0045ae10
    void CloseWindow(uint32_t id);                                           // 0x0045afc0
};
cWindowManager* WindowManager();                                             // 0x00401050

class cGameView {
public:
    void SetFlags(int a, int b);                                             // 0x0067c420
    void AddLayer(ResourceKey key, void* handler, int a, float x, float y, float z, int b, int c);  // 0x0067aaf0
};
cGameView* GameViewA();                                                      // 0x0067cac0
cGameView* GameViewB();                                                      // 0x0067caf0

struct cLocalObject {
    uint32_t mData[4];
    void Release();                                                          // 0x0093a2e0
    void Close() { Release(); mData[0] = 0; mData[1] = 0; mData[2] = 0; mData[3] = 0; }
};

class cAppModeEditorBase {
public:
    char pad0[0x20];
    cIApp* mApp;                                    // +0x20
    EA::AutoRefCount<cPropertyList> mCurrentConfigProperties;   // +0x24
    char pad28[0x78 - 0x28];
    EA::AutoRefCount<cSPEditorUI> mUI;              // +0x78
    char pad7c[0x98 - 0x7c];
    EA::AutoRefCount<cSPEditorModel> mEditorSaveModel;   // +0x98
    char pad9c[0x150 - 0x9c];
    cSPEditorResourceFactory* mSaveLoadFactory;     // +0x150
    char pad154[0x1cc - 0x154];
    cEditorLaunchData* mLaunchData;                 // +0x1cc
    char pad1d0[0x2d8 - 0x1d0];
    uint32_t mBudgetFlags;                          // +0x2d8
    int mBlockLimit;                                // +0x2dc
    int mLimbLimit;                                 // +0x2e0
    int mPaintLimit;                                // +0x2e4
    int mBoneLimit;                                 // +0x2e8
    float mCostLimit;                               // +0x2ec
    bool mUnk2f0;
    bool mIsCreatureEditor;                         // +0x2f1
    char pad2f2[0x31c - 0x2f2];
    int mEditorMode;                                // +0x31c
    char pad320[0x360 - 0x320];
    cSPEditorAnimatedCreatureManager* mAnimCreatureManager;   // +0x360
    cViewer* mShadowViewer;                         // +0x364
    char pad368[0x3c4 - 0x368];
    cSPEditorUIPanel* mPanel;                       // +0x3c4
    char pad3c8[0x434 - 0x3c8];
    EA::AutoRefCount<cSPEditorBudget> mBudget;      // +0x434
    char pad438[0x4b0 - 0x438];
    bool mUnk4b0;                                   // +0x4b0
    char pad4b1[6];
    bool mUnk4b7;                                   // +0x4b7
    char pad4b8[8];
    uint32_t mCurrentSoundId;                       // +0x4c0
    uint32_t mCurrentInstanceId;                    // +0x4c4
    char pad4c8[4];
    int mRandomBackground;                          // +0x4cc
    char pad4d0[0x5a8 - 0x4d0];
    cLocalObject mLocal;                            // +0x5a8
    char pad5b8[0x5e8 - 0x5b8];
    uint32_t mHandler[5];                           // +0x5e8 (AutoHandler)

    void ShowBudgetWindows(int keepClosed);
    int GetLaunchSelectedIndex();
    void* GetCurrentCameraContext();
    float GetBudgetFraction();
    void PurchaseBlock(cSPEditorBlock* block);
    ResourceKey GetRandomBackground();
    ResourceKey GetNextBackground();
    int FlushFactory(cSPEditorResourceFactory* factory);
    void SwitchToPlayModeCamera();
    int ScoreCreatureForZCorp();
    int CanPublish();
    void SetupThumbnailModelWorld(cIModelWorld* world, bool isAnimated);
    void UpdateModelSounds(float deltaTime);
    void ExitEditorUI();
    static void SetupGameViewLayers();
};

void PlayModeCameraCallback(void* editor);                                   // 0x00572f00

}  // namespace SP

namespace EA { namespace Messaging {
void RemoveHandler(uint32_t h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0
} }

namespace EA { namespace Audio {
class IAudioSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual uint32_t CreateInstance();                                       // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void BeginMessage(uint32_t id);                                  // +0x38
    virtual void v3c();
    virtual void AddParam(uint32_t id, uint32_t value);                      // +0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void SendMessage();                                              // +0x58
};
IAudioSystem* GetSystemAT();                                                 // 0x00a206f0
} }

void Start3dSoundByName(uint32_t soundId, uint32_t instanceId, float x, float y, float z);   // 0x00571f80

using namespace SP;

// @ 0x005744b0
void cAppModeEditorBase::ShowBudgetWindows(int keepClosed)
{
    WindowManager()->HideWindow(0x3f1eaf1);
    WindowManager()->HideWindow(0x3f1eaf3);
    if (mPanel && mPanel->IsActive()) {
        if (WindowManager()->IsWindowOpen(0x3f1eaf3) == 0)
            WindowManager()->OpenWindow(0x3f1eaf3, 1);
        else
            WindowManager()->CloseWindow(0x3f1eaf3);
    }
    if (keepClosed == 0) {
        if (WindowManager()->IsWindowOpen(0x3f1eaf1) == 0)
            WindowManager()->OpenWindow(0x3f1eaf1, 1);
        else
            WindowManager()->CloseWindow(0x3f1eaf1);
    }
}

// @ 0x00574570
int cAppModeEditorBase::GetLaunchSelectedIndex()
{
    if (mLaunchData)
        return mLaunchData->mSelectedIndex;
    return -1;
}

// @ 0x00574590
void* cAppModeEditorBase::GetCurrentCameraContext()
{
    cCameraList* cams = mApp->GetCameraManager()->GetCameras();
    if (cams)
        return cams->GetCamera(0x29da727);
    return 0;
}

#pragma warning(disable:4035)
// EA math FloorToInt: hand-written SSE asm (round, then step down if the rounded value is above f).
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// @ 0x005745c0
float cAppModeEditorBase::GetBudgetFraction()
{
    // Local names matter: /O2 frame slots for address-taken locals follow a name hash.
    if (mEditorSaveModel) {
        bool isCreature = !sAppProperties->GetBool(0x677d3ea);
        int blocks, legs, colors, bones;
        float cost;
        mEditorSaveModel->GetComplexity(&blocks, &legs, &colors, &cost, &bones);

        float blockFrac = 0.0f, limbFrac = 0.0f, paintFrac = 0.0f, costFrac = 0.0f;
        float boneFrac = 0.0f;
        if (isCreature) {
            if (mBlockLimit != -1 && (mBudgetFlags & 1))
                blockFrac = (float)blocks / (float)mBlockLimit;
            if (mLimbLimit != -1 && (mBudgetFlags & 2))
                limbFrac = (float)legs / (float)mLimbLimit;
        }
        if (mPaintLimit != -1 && (mBudgetFlags & 4))
            paintFrac = (float)colors / (float)mPaintLimit;
        if (isCreature && mCostLimit > 0.0f && (mBudgetFlags & 8))
            costFrac = cost / mCostLimit;
        if (mBoneLimit != -1)
            boneFrac = (float)bones / (float)mBoneLimit;

        if (mBudget) {
            if (isCreature) {
                if (mBlockLimit != -1)
                    mBudget->SetRemaining(1, mBlockLimit - blocks);
                if (mLimbLimit != -1)
                    mBudget->SetRemaining(2, mLimbLimit - legs);
            }
            if (mPaintLimit != -1)
                mBudget->SetRemaining(3, mPaintLimit - colors);
            if (isCreature && mCostLimit > 0.0f)
                mBudget->SetRemaining(4, FloorToInt(mCostLimit - cost));
            if (mBoneLimit != -1)
                mBudget->SetRemaining(5, mBoneLimit - bones);
        }

        float fracs[4] = { blockFrac, limbFrac, paintFrac, costFrac };
        float m = eastl::max(eastl::max(eastl::max(fracs[0], fracs[1]), fracs[2]), fracs[3]);
        return eastl::max(m, boneFrac);
    }
    return 0.0f;
}

// @ 0x00574850
void cAppModeEditorBase::PurchaseBlock(cSPEditorBlock* block)
{
    if (!block)
        return;
    if (block->mPrice > 0) {
        Property* prop;
        if (mCurrentConfigProperties)
            mCurrentConfigProperties->GetProperty(0xb3a88b0b, prop);
        uint32_t instance = 0;
        if (GetPropertyAsKeyInstance(mCurrentConfigProperties, 0xd3a86350, &instance)) {
            Vector3 pos, dir;
            App()->GetViewer()->GetCameraLocationInfo(&pos, &dir, 0, 0);
            Vector3 a, b;
            App()->GetViewer()->GetCameraTransform(&a, &b);
        }
    }
    mBudget->PurchaseBlock(block, 0);
}

// @ 0x00574900
ResourceKey cAppModeEditorBase::GetRandomBackground()
{
    int count = 0;
    ResourceKey* keys = 0;
    cPropertyList* props = mCurrentConfigProperties;
    if (GetPropertyArrayKey(props, 0x503d2f60, &count, &keys) && count > 0) {
        mRandomBackground = sMathRandom.RandomUint32Uniform(count);
        return keys[mRandomBackground];
    }
    return ResourceKey();
}

// @ 0x00574990
ResourceKey cAppModeEditorBase::GetNextBackground()
{
    int count = 0;
    ResourceKey* keys = 0;
    cPropertyList* props = mCurrentConfigProperties;
    if (GetPropertyArrayKey(props, 0x503d2f60, &count, &keys) && count > 0) {
        mRandomBackground = (mRandomBackground + 1) % count;
        return keys[mRandomBackground];
    }
    return ResourceKey();
}

// @ 0x00574a20
int cAppModeEditorBase::FlushFactory(cSPEditorResourceFactory* factory)
{
    if (!factory)
        factory = mSaveLoadFactory;
    if (factory)
        return factory->Flush(true);
    return 0;
}

// @ 0x00574a60
void cAppModeEditorBase::SwitchToPlayModeCamera()
{
    float a, b, c;
    Vector3 v;
    cCameraList* cams = App()->GetCameraManager()->GetCameras();
    cams->GetCameraValues(&a, &b, &c, &v);
    App()->GetCameraManager()->SetActiveCameraID(0x3d437f9);
    cCreatureCameraBase* cam = App()->GetCameraManager()->GetCameras()->GetCamera(0x6771a60);
    if (cam) {
        cSPEditorAnimatedCreatureManager* mgr = mAnimCreatureManager;
        cam->SetCreature(mgr->GetCreature(mShadowViewer));
        cam->SetInitialCameraValues(a, b, c, v);
        cam->SetCallback(PlayModeCameraCallback, this);
    }
}

// @ 0x00574b40
int cAppModeEditorBase::ScoreCreatureForZCorp()
{
    int count = mEditorSaveModel->GetBlockCount();
    float minScore = 100.0f;
    float scale = GetPropertyFloat(mCurrentConfigProperties, 0x542ed1b, 1.0f);
    BoundingBox box;
    mEditorSaveModel->GetBoundingBox(&box, 0);
    float dx = box.upper.x - box.lower.x;
    float dy = box.upper.y - box.lower.y;
    float dz = box.upper.z - box.lower.z;
    float size = (dx < dy) ? dy : dx;
    if (size < dz)
        size = dz;
    float sizeScale = 2.0f / size;
    float scaledSize = sizeScale / scale;
    for (int i = 0; i < count; i++) {
        float score;
        if (mEditorSaveModel->GetBlock(i)->IsFlagSet(7)) {
            score = GetPaintScore(mEditorSaveModel->GetBlock(i)) * scaledSize;
        } else if (mEditorSaveModel->GetBlock(i)->IsFlagSet(11)) {
            mEditorSaveModel->GetBlock(i)->GetPartScale();
            score = mEditorSaveModel->GetBlock(i)->GetPartScaleFactor() * scaledSize;
        } else {
            float divisor = GetPropertyValueFloat(mEditorSaveModel->GetBlock(i)->mpPropList, 0xfba614, 1.0f);
            score = mEditorSaveModel->GetBlock(i)->mCost / divisor * sizeScale;
        }
        if (score < minScore)
            minScore = score;
    }
    int result = (int)(minScore * 100.0f);
    if (result > 255)
        result = 255;
    return result;
}

// @ 0x00574d60
int cAppModeEditorBase::CanPublish()
{
    if (mUnk4b0 && (mUnk4b7 || !EditorUtils::GetCreatorType(&mEditorSaveModel->mKey)))
        return 1;
    return 0;
}

// @ 0x00574da0
void cAppModeEditorBase::SetupThumbnailModelWorld(cIModelWorld* world, bool isAnimated)
{
    cModelManager* mm = ModelManager();
    eastl::bitset<64> include;
    eastl::bitset<64> exclude;
    if (mIsCreatureEditor) {
        if (isAnimated)
            include.set(mm->GetModelGroup(0x509991e7, 0));
        else
            include.set(mm->GetModelGroup(0x509991e6, 0));
        exclude.set(mm->GetModelGroup(0xfe39de0, 0));
        exclude.set(mm->GetModelGroup(0x26f3933, 0));
    } else {
        include.set(mm->GetModelGroup(0x9138fd8d, 0));
        include.set(mm->GetModelGroup(0x4fe3913, 0));
        include.set(mm->GetModelGroup(0xfeb8df2, 0));
        exclude.set(mm->GetModelGroup(0xfe39de0, 0));
    }
    world->SetModelGroups(&include, &exclude, 4);
    void* lighting = world->CreateLightingWorld(0, 4, 1);
    world->SetLightingWorld(lighting);
}

// @ 0x00574f30
void cAppModeEditorBase::UpdateModelSounds(float deltaTime)
{
    uint32_t soundId = 0;
    float maxValue = 0.0f;
    bool isPlayMode = mEditorMode == 2;
    if (isPlayMode && mEditorSaveModel) {
        int count = mEditorSaveModel->GetBlockCount();
        for (int i = 0; i < count; i++) {
            cSPEditorBlock* block = mEditorSaveModel->GetBlock(i);
            if (block->mSoundData) {
                cPropertyList* list = PropManager()->GetPropertyList(block->mInstanceID, block->mGroupID);
                if (list) {
                    Property* soundProp = 0;
                    Property* scaleProp = 0;
                    if (list->GetPropertyAlloc(0x46d0560, soundProp) && list->GetPropertyAlloc(0x46d0572, scaleProp)) {
                        float value = block->mCost / (block->mMaxScale - block->mMinScale) * *scaleProp->GetFloatValue();
                        if (value > maxValue) {
                            soundId = *soundProp->GetUInt32Value();
                            maxValue = value;
                        }
                    }
                }
            }
        }
    }

    uint32_t instance = mCurrentInstanceId;
    if (instance && (!isPlayMode || soundId != mCurrentSoundId)) {
        EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
        if (audio) {
            audio->BeginMessage(0x347536b);
            audio->AddParam(0x3475385, instance);
            audio->AddParam(0x34753a0, 0);
            audio->SendMessage();
        }
        mCurrentInstanceId = 0;
        mCurrentSoundId = 0;
    }
    if (mCurrentInstanceId == 0 && soundId) {
        EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT();
        uint32_t inst = audio ? audio->CreateInstance() : 0;
        mCurrentInstanceId = inst;
        mCurrentSoundId = soundId;
        Start3dSoundByName(soundId, inst, 0.0f, 0.0f, 0.0f);
    }
}

// @ 0x00575120
void cAppModeEditorBase::ExitEditorUI()
{
    mLocal.Close();
    if (mHandler[0]) {
        uint32_t h = mHandler[0];
        mHandler[0] = 0;
        EA::Messaging::RemoveHandler(h, mHandler[1], mHandler[2], mHandler[3], mHandler[4]);
    }
    if (mUI->GetMode() != 1) {
        mUI->SetModeEnabled(1);
        mUI->Refresh(1, 1);
    }
    GameViewA()->SetFlags(1, 1);
}

struct cDefaultLayerHandler {
    virtual void Handle();
};
extern ResourceKey kLayerKeyA;   // 0x0150d090
extern ResourceKey kLayerKeyB;   // 0x0150d09c

// @ 0x005751b0
void cAppModeEditorBase::SetupGameViewLayers()
{
    static cDefaultLayerHandler sHandler;
    GameViewB()->AddLayer(kLayerKeyA, 0, 0, -1.0f, -1.0f, 0.0f, 0, 0);
    GameViewB()->AddLayer(kLayerKeyB, &sHandler, 0, -1.0f, -1.0f, 0.0f, 0, 0);
}
