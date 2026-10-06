// slice s00588570 -- SP::cAppModeEditorBase::OnMouseDown (5989 B).
// The editor's mouse-down handler: forwards to play mode, applies paint in paint mode, and in
// build mode picks a part/handle and creates the matching manipulator (cSPEditorManipulation*).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
// Field names follow the Spore ModAPI headers (Editor.h / EditorRigblock.h / EditorBaseHandle.h)
// where they exist; offsets are from the retail disassembly.
#include "types.h"

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
inline Vector3 operator-(const Vector3& a, const Vector3& b)
{
    return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

extern const Vector3 kColorWhite;   // 0x0150ce00

namespace EA {
class Stopwatch {
public:
    uint32_t mData[6];
    Stopwatch(int units, bool bStart);   // 0x0093a560
    void Restart();                      // 0x00571e80
};
}  // namespace EA

namespace SP {

class cSPEditorBlock;
class cSPEditorHandle;
class cSPEditorHandleDeform;
class cSPEditorSkin;
class cSPEditorManipulator;
class cEditorModel;

// --- intrusive pointers (out-of-line instances in the original) ---
struct BlockPtr {
    cSPEditorBlock* mpObject;
    BlockPtr() : mpObject(0) {}
    explicit BlockPtr(cSPEditorBlock* p);              // 0x0061df40 (AddRef = vtbl+4)
    ~BlockPtr();
    BlockPtr& operator=(cSPEditorBlock* p);             // 0x004b09b0
    BlockPtr& operator=(const BlockPtr& o);             // 0x005766e0
    cSPEditorBlock* get() const { return mpObject; }
    cSPEditorBlock* operator->() const { return mpObject; }
    operator cSPEditorBlock*() const { return mpObject; }
};

struct HandlePtr {
    cSPEditorHandle* mpObject;
    HandlePtr() : mpObject(0) {}
    ~HandlePtr();
    HandlePtr& operator=(const HandlePtr& o);           // 0x00ac9480 (AddRef = vtbl+0)
    inline void reset();
    cSPEditorHandle* get() const { return mpObject; }
};

struct SkinPtr {
    cSPEditorSkin* mpObject;
    SkinPtr(cSPEditorSkin* const& p);                   // 0x00ac8980 (copy from the raw member)
};

struct ManipulatorPtr {
    cSPEditorManipulator* mpObject;
    ManipulatorPtr& operator=(cSPEditorManipulator* p); // 0x00b5f950
    cSPEditorManipulator* operator->() const { return mpObject; }
    operator cSPEditorManipulator*() const { return mpObject; }
};

// --- model / handle / block ---
struct cModel {
    uint32_t pad0[3];
    Vector3 mPosition;          // 0x0C
    uint32_t pad18[19];
    uint32_t mHandleKey;        // 0x64
};

class cSPEditorHandle {
public:
    virtual int AddRef();                       // 0x00
    virtual int Release();                      // 0x04
    virtual void v08();
    virtual void v0C();
    virtual uint32_t GetTypeID();               // 0x10
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2C();
    virtual void SetState(int state, bool b);   // 0x30
    cModel* GetModel();                         // 0x0047e680
    cSPEditorBlock* GetRigblock();              // 0x0047e6c0
};

enum {
    kHandleTypeBallConnector = 0x050e8e23,
    kHandleTypeDeform        = 0x050a993c,
    kHandleTypeSpineResize   = 0x050a205b,
    kHandleTypeScaleA        = 0x050a510e,
    kHandleTypeScaleB        = 0x050a2ed2,
};

struct cPaintInfo {             // 0x1c bytes
    int mRegion;
    Vector3 mColor1;
    Vector3 mColor2;
    cPaintInfo();                               // 0x00440f60
};

struct cPaletteCategoryInfo {
    int mCategoryID;
    uint32_t pad4[6];
};

class cSPEditorBlock {
public:
    virtual void v00();
    virtual int AddRef();                       // 0x04
    virtual int Release();                      // 0x08

    uint32_t pad4[17];
    Vector3 mPosition;                          // 0x48
    uint32_t pad54[186];
    cSPEditorBlock* mpParent;                   // 0x33C
    uint32_t pad340[40];
    cSPEditorBlock* mpSymmetricRigblock;        // 0x3E0
    cSPEditorBlock* mpAsymmetricRigblock;       // 0x3E4
    uint32_t pad3E8[1];
    cSPEditorHandle* mpBallConnectorHandle;     // 0x3EC
    uint32_t pad3F0[630];
    uint32_t mBooleanAttributes[2];             // 0xDC8 (eastl::bitset<64>)

    bool HasAttribute(int i) const { return ((mBooleanAttributes[i >> 5] >> (i & 31)) & 1) != 0; }

    void SetBooleanAttribute(int attr, bool value);            // 0x00435a10
    void OnChildPicked(cSPEditorBlock* child);                  // 0x00438a40
    bool CanSplit();                                            // 0x0043ca10
    void PrepareSplit(int a, int b);                            // 0x0043cfc0
    void ApplyPaint(cPaletteCategoryInfo* info, int region);    // 0x00440c40
    bool GetPaintInfo(cPaintInfo* info, int region);            // 0x00440d80
    void ResetLimbPose();                                       // 0x00448d60
    Vector3 GetModelDefaultMouseOffset();                       // 0x0044b550
    void SnapToAsymmetric(int a, int b);                        // 0x0044bcf0
    void RecursiveFlagB();                                      // 0x0044eea0
    int GetSymmetryIndex();                                     // 0x0044f220
    cSPEditorBlock* Split(int mode);                            // 0x0044f420
};

// Bits of cSPEditorBlock::mBooleanAttributes tested here.
enum {
    kAttrSnapsToBone       = 0,
    kAttrFromPalette       = 3,
    kAttrSpine             = 7,
    kAttrLimb              = 11,
    kAttrNoSymmetricParent = 15,
    kAttrIsTorso           = 31,
    kAttrNoInterpenetrate  = 32 + 9,
    kAttrNoBoneDrag        = 32 + 12,
    kAttrNoSymmetry        = 32 + 25,
};

class cEditorModel {
public:
    void BeginPaintChange();                    // 0x004ae250 (called before and after)
    bool IsSymmetryEnabled();                   // 0x004adc40
    void SetLimbsDirty(bool b);                 // 0x004adfc0
};

class cSPEditorPaintTheme {
public:
    void ReadFromAsset(cEditorModel* model);    // 0x004b2800
};

class cSPPaletteUI {
public:
    void SetPaintInfo(cPaintInfo* info);                   // 0x005ca950
    void GetCategoryInfo(cPaletteCategoryInfo* info);      // 0x005cb1b0
};

class cEditorLimits {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30();
    virtual bool CanAddBlock(void* blockInfo);            // 0x34
    virtual void OnBlockAdded(cSPEditorBlock* b, int n);  // 0x38
};

class cEditorPlayMode {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual bool OnMouseDown(int button, float x, float y, int state);   // 0x10
};

class cSPEditorManipulator {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void v08(); virtual void v0C(); virtual void v10();
    virtual bool OnMouseDown(int button, float x, float y, int state);  // 0x14
    virtual bool OnMouseUp(int button, float x, float y, int state);    // 0x18
    virtual bool OnMouseMove(float x, float y, int state);              // 0x1C
    virtual void v20();
    virtual void Update(float delta);                                   // 0x24
};

// Concrete manipulators: ctor + setup method (all out of line).
class cSPEditorManipulationLimb : public cSPEditorManipulator {            // 0x39c4 bytes
public:
    cSPEditorManipulationLimb();                                         // 0x005ae610
    void Setup(cSPEditorHandle* handle, cSPEditorBlock* block, cSPEditorSkin* skin,
               Vector3 offset, int mouseState);                          // 0x005ae870
};
class cSPEditorManipulationInterpenetration : public cSPEditorManipulator {  // 0x48
public:
    cSPEditorManipulationInterpenetration();                             // 0x005ad9a0
    void SetBlock(const BlockPtr& block, Vector3 offset, bool alt);      // 0x005ad930
};
class cSPEditorManipulationPlanarInterpenetration : public cSPEditorManipulator {  // 0x48
public:
    cSPEditorManipulationPlanarInterpenetration();                       // 0x005b4b40
    void SetBlock(const BlockPtr& block, Vector3 offset, bool alt, bool keep);  // 0x005b4ad0
};
class cSPEditorManipulationTorso : public cSPEditorManipulator {         // 0x7c
public:
    cSPEditorManipulationTorso();                                        // 0x005bdca0
    void Setup(cEditorModel* model, void* skeleton);                     // 0x005bd750
};
class cSPEditorManipulationSkin : public cSPEditorManipulator {          // 0x1c
public:
    cSPEditorManipulationSkin();                                         // 0x005ac980
    void Init();                                                         // 0x00c2e4e0
};
class cSPEditorManipulationSpine : public cSPEditorManipulator {         // 0x34
public:
    cSPEditorManipulationSpine();                                        // 0x005b7490
    void Init(cSPEditorBlock* block, Vector3 offset, void* skeleton);    // 0x005b7460
};
class cSPEditorManipulationBoneSnap : public cSPEditorManipulator {      // 0xec
public:
    cSPEditorManipulationBoneSnap();                                     // 0x005b23d0
    void Setup(const BlockPtr& block, Vector3 offset, SkinPtr skin, bool b);   // 0x005b2180
};
class cSPEditorManipulationBone : public cSPEditorManipulator {          // 0x14c
public:
    cSPEditorManipulationBone();                                         // 0x005aac30
    void Setup(const BlockPtr& block, Vector3 offset, SkinPtr skin,
               bool cellPinning, bool notFromPalette);                   // 0x005aab00
};
class cSPEditorManipulation74 : public cSPEditorManipulator {            // 0x74
public:
    cSPEditorManipulation74();                                           // 0x005bc860
    void Setup(const BlockPtr& block, Vector3 offset);                   // 0x005bc7f0
};
class cSPEditorManipulation8C : public cSPEditorManipulator {            // 0x8c
public:
    cSPEditorManipulation8C();                                           // 0x005ba060
    void Setup(cSPEditorBlock* block, Vector3 offset, bool b);           // 0x005b9840
};
class cSPEditorManipulationObject40 : public cSPEditorManipulator {      // 0x40
public:
    cSPEditorManipulationObject40();                                     // 0x005aa420
    void Set(const BlockPtr& block, Vector3 offset);                     // 0x005aa3d0
};
class cSPEditorManipulationDeform : public cSPEditorManipulator {        // 0x5c
public:
    cSPEditorManipulationDeform();                                       // 0x005ac9f0
    void Setup(cSPEditorHandleDeform* h, Vector3 offset, cSPEditorSkin* skin);  // 0x005accc0
};
class cSPEditorManipulationSpineResize : public cSPEditorManipulator {   // 0x90
public:
    cSPEditorManipulationSpineResize();                                  // 0x005b85d0
    void Init(cSPEditorBlock* block, Vector3 offset, void* skeleton,
              cSPEditorSkin* skin, cEditorLimits* limits);               // 0x005b7a70
};
class cSPEditorManipulationScale : public cSPEditorManipulator {         // 0x158
public:
    cSPEditorManipulationScale();                                        // 0x005b53c0
    void Setup(cSPEditorHandle* h, Vector3 offset, Vector3 pickPos);     // 0x005b5110
};

// --- globals / free functions ---
class cMessageManager {
public:
    void PostMSG(uint32_t id, void* data);                               // 0x0045ae10
    void MessageSend(uint32_t id, void* data, void* sender, int flags);  // 0x0045ae40
};
cMessageManager* MessageManager();      // 0x00401050

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, Vector3* up, Vector3* right);  // 0x007c3d30
};
class cApp {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3C();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4C();
    virtual void v50(); virtual void v54();
    virtual cViewer* GetViewer();       // 0x58
};
cApp* App();                            // 0x0067dd10
void* ModelManager();                   // 0x0067dd80

class cCursorManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30();
    virtual void GetCursorPosition(int* x, int* y);   // 0x34
};
cCursorManager* CursorManager();        // 0x0067cab0

namespace EditorUtils {
void PlayEditorSound(uint32_t a, uint32_t b, float value, int c);              // 0x00435f40
cSPEditorHandle* GetBoneForHandle(uint32_t* key);                             // 0x004aa030
void SetSymmetricBlocksUIState(cSPEditorBlock* b, int state, bool torso);     // 0x004a7f30
}
void UpdateSymmetryRec(cSPEditorBlock* b, int index);                         // 0x0048f790
cSPEditorBlock* FindBlockForModel(cModel* model, Vector3 cameraPos);          // 0x00496bb0
cSPEditorBlock* GetSymmetricPartner(cSPEditorBlock* b);                       // 0x004a5e10
void LinkSelection(cSPEditorBlock* prev, cSPEditorBlock* b);                  // 0x004a60a0
bool HasSymmetricPartner(cSPEditorBlock* b);                                  // 0x004a6120
void UpdateBlockState(cSPEditorBlock* b, int, int, int, int, int, int, int);  // 0x004a6d20
void PlayAudio(uint32_t id);                                                  // 0x004a88d0
cSPEditorHandleDeform* interface_cast_Deform(cSPEditorHandle* h);             // 0x00572750

// --- the editor mode ---
struct cPickResult {            // 0x1c bytes, returned by value from Pick
    cSPEditorBlock* mpBlock;    // 0x00
    cModel* mpModel;            // 0x04
    Vector3 mPosition;          // 0x08
    bool mbTorso;               // 0x14
    uint32_t pad18;
    cPickResult() : mpBlock(0), mPosition(0.0f, 0.0f, 0.0f) {}
};

enum { kMouseButtonLeft = 1000, kMouseButtonRight = 1001, kMouseButtonMiddle = 1002 };
enum { kModeBuild = 0, kModePaint = 1, kModePlay = 2 };

class cAppModeEditorBase {
public:
    uint32_t pad0[13];
    int mMouseButtonDown;                    // 0x34
    uint32_t pad38[1];
    int mPaintModifierFlags;                 // 0x3C
    uint32_t pad40[10];
    float mIdleTime;                         // 0x68
    uint32_t pad6C[4];
    cEditorPlayMode* mpPlayMode;             // 0x7C
    uint32_t pad80[1];
    void* mpMainModelWorld;                  // 0x84
    uint32_t pad88[4];
    cEditorModel* mpEditorModel;             // 0x98
    uint32_t pad9C[9];
    int mMouseDownX;                         // 0xC0
    int mMouseDownY;                         // 0xC4
    uint32_t padC8[1];
    BlockPtr mpActivePart;                   // 0xCC
    BlockPtr mpMovingPart;                   // 0xD0
    BlockPtr mpSelectedPart;                 // 0xD4
    BlockPtr mPreviousSelectedBlock;         // 0xD8
    uint32_t padDC[2];
    HandlePtr mpActiveHandle;                // 0xE4
    bool mbMouseIsInSkin;                    // 0xE8
    bool mbTorsoInEffectsMask;               // 0xE9
    uint8_t padEA[10];
    cSPEditorHandle* mpLastActiveHandle;     // 0xF4
    uint32_t padF8[18];
    bool mbHandleRollover;                   // 0x140
    uint8_t pad141[1];
    bool mbLimitPartCount;                   // 0x142
    bool mbSymmetricLimbs;                   // 0x143
    uint32_t pad144[1];
    ManipulatorPtr mpActiveManipulator;      // 0x148
    void* mpSkeleton;                        // 0x14C
    cSPEditorSkin* mpEditorSkin;             // 0x150
    uint32_t pad154[83];
    cSPEditorPaintTheme* mpCurrentPaintTheme; // 0x2A0
    uint8_t pad2A4[13];
    bool mManipulatedBlockFromPalette;       // 0x2B1
    uint8_t pad2B2[2];
    bool mUnselectCurrentBlock;              // 0x2B4
    uint8_t pad2B5[59];
    bool mbCellPinningToRigBlocks;           // 0x2F0
    uint8_t pad2F1[43];
    int mMode;                               // 0x31C
    uint8_t pad320[101];
    bool mbIdleOnModelClick;                 // 0x385
    uint8_t pad386[17];
    bool mbInputDisabled;                    // 0x397
    uint32_t pad398[1];
    cSPEditorBlock** mPaintTargetsBegin;     // 0x39C (eastl::vector<cSPEditorBlock*>)
    cSPEditorBlock** mPaintTargetsEnd;       // 0x3A0
    uint32_t pad3A4[3];
    int mHoveredPaintRegion;                 // 0x3B0
    uint32_t pad3B4[4];
    cSPPaletteUI* mpPaintPaletteUI;          // 0x3C4
    uint32_t pad3C8[27];
    cEditorLimits* mpEditorLimits;           // 0x434
    uint8_t pad438[58];
    bool mbScaleOnMouseDown;                 // 0x472
    uint8_t pad473[63];
    bool mbPaintDirty;                       // 0x4B2
    uint8_t pad4B3[33];
    bool mbForwardToTorsoTool;               // 0x4D4
    uint8_t pad4D5[299];

    bool OnMouseDown(int button, float x, float y, int mouseState);   // 0x00588570

    void ForwardMouseDownToTorsoTool();                  // 0x005724a0
    void ResetIdle();                                    // 0x00573970
    void* GetBlockToAdd();                               // 0x00573a10
    bool IsMousedOverModel(float x, float y);            // 0x00573a60
    void SetRolloverBlock(cSPEditorBlock* b, int n);     // 0x00573c00
    void SetRolloverHandle(cSPEditorHandle* h, bool b);  // 0x00573d70
    bool IsManipulatorEnabled(uint32_t id);              // 0x005740e0
    void SetupCameraUI();                                // 0x00575f20
    void RemoveTorsoFromEffectsMask();                   // 0x005772b0
    void SetTorsoBlock(cSPEditorBlock* b, bool torso);   // 0x00577580
    void SomeLoader();                                   // 0x00577dd0
    cPickResult Pick(float x, float y, int flags);       // 0x0057af00
    void TriggerTutorialEvent(int id, int n);            // 0x0057c530
    void SetSelectedBlock(cSPEditorBlock* b, bool b2);   // 0x0057e790
    void AddUndoState(int a, int b);                     // 0x00586410
    void ScaleBlock();                                   // 0x00586960

    bool OnPaintModeMouseDown(int button);
};

__forceinline void HandlePtr::reset()
{
    cSPEditorHandle* p = mpObject;
    if (p) {
        mpObject = 0;
        p->Release();
    }
}
inline HandlePtr::~HandlePtr()
{
    if (mpObject)
        mpObject->Release();
}
inline BlockPtr::~BlockPtr()
{
    if (mpObject)
        mpObject->Release();
}

}  // namespace SP

using namespace SP;

// Paint mode (mMode == 1), inlined into OnMouseDown in the original.
__forceinline bool cAppModeEditorBase::OnPaintModeMouseDown(int button)
{
    if (!mpActivePart || button != kMouseButtonLeft)
        return false;

    int flags = mPaintModifierFlags;
    if (flags & 0x10) {
        // Pick up the paint under the cursor ("paint like this").
        cPaintInfo info;
        if (!mpActivePart->GetPaintInfo(&info, mHoveredPaintRegion))
            return false;
        if (!mpPaintPaletteUI)
            return false;
        flags = mPaintModifierFlags;
        if (!(flags & 0x40))
            info.mRegion = 0;
        if (!(flags & 0x20)) {
            info.mColor1 = kColorWhite;
            info.mColor2 = kColorWhite;
        }
        mpPaintPaletteUI->SetPaintInfo(&info);
        PlayAudio(0xa7373ab4);
        TriggerTutorialEvent(0x15, 1);
        return false;
    }
    if (!(flags & 1))
        return false;

    cPaletteCategoryInfo info;
    mpPaintPaletteUI->GetCategoryInfo(&info);
    if (!info.mCategoryID)
        return false;

    mpEditorModel->BeginPaintChange();
    int count = (int)(mPaintTargetsEnd - mPaintTargetsBegin);
    for (int i = 0; i < count; ++i)
        mPaintTargetsBegin[i]->ApplyPaint(&info, mHoveredPaintRegion);
    mpEditorModel->BeginPaintChange();
    if (mpCurrentPaintTheme)
        mpCurrentPaintTheme->ReadFromAsset(mpEditorModel);
    mbPaintDirty = true;
    AddUndoState(1, 0);
    PlayAudio(0xd2c7f386);
    EditorUtils::PlayEditorSound(0x1d6253c0, 0xa1ddfeb0, (float)mHoveredPaintRegion, 0);
    return false;
}

// @ 0x00588570
bool cAppModeEditorBase::OnMouseDown(int button, float x, float y, int mouseState)
{
    mIdleTime = 0.0f;
    if (mbInputDisabled)
        return false;
    if (mpActiveManipulator || mMouseButtonDown)
        return true;

    mMouseButtonDown = button;
    if (mbScaleOnMouseDown)
        ScaleBlock();
    if (mbForwardToTorsoTool) {
        ForwardMouseDownToTorsoTool();
        return true;
    }
    CursorManager()->GetCursorPosition(&mMouseDownX, &mMouseDownY);

    if (button == kMouseButtonRight || button == kMouseButtonMiddle ||
        (button == kMouseButtonLeft && !mpActivePart && !mpActiveHandle.get() && !mbMouseIsInSkin &&
         mMode != kModePlay && !mpMovingPart)) {
        // Clicked on nothing: drop the selection.
        SetRolloverBlock(0, -1);
        SetRolloverHandle(0, true);
        mUnselectCurrentBlock = true;
        TriggerTutorialEvent(7, 1);
        return false;
    }

    if (!ModelManager())
        return false;
    if (!mpMainModelWorld)
        return false;

    switch (mMode) {
    case kModeBuild:
        break;
    case kModePaint:
        return OnPaintModeMouseDown(button);
    case kModePlay:
        if (button == kMouseButtonLeft)
            mpPlayMode->OnMouseDown(button, x, y, mouseState);
        // fall through
    default:
        goto finish;
    }

    if (mbIdleOnModelClick && button == kMouseButtonLeft && IsMousedOverModel(x, y)) {
        mIdleTime = 0.0f;
        SomeLoader();
        ResetIdle();
    }

    {
        BlockPtr& moving = mpMovingPart;
        mManipulatedBlockFromPalette = false;
        if (moving && moving->HasAttribute(kAttrFromPalette)) {
            mManipulatedBlockFromPalette = true;
            moving->SetBooleanAttribute(kAttrFromPalette, false);
        }

        if (mbLimitPartCount && !mManipulatedBlockFromPalette) {
            void* blockInfo = GetBlockToAdd();
            if (!blockInfo)
                return false;
            if (!mpEditorLimits->CanAddBlock(blockInfo)) {
                MessageManager()->PostMSG(0x03f1bf51, 0);
                return false;
            }
        }

        bool pickedTorso = false;
        bool pickedHandle = false;
        bool didSplit = false;
        bool found = false;
        bool dragLimb = false;
        Vector3 offset(0.0f, 0.0f, 0.0f);
        Vector3 pickPos(0.0f, 0.0f, 0.0f);
        cSPEditorHandle* handle = 0;

        Vector3 cameraPos, cameraDir, cameraUp, cameraRight;
        App()->GetViewer()->GetCameraLocationInfo(&cameraPos, &cameraDir, &cameraUp, &cameraRight);
        EA::Stopwatch stopwatch(5, false);
        stopwatch.Restart();

        if (mManipulatedBlockFromPalette)
            offset = moving->GetModelDefaultMouseOffset();

        cPickResult pick;
        if (!mManipulatedBlockFromPalette) {
            pick = Pick(x, y, 0);
            pickPos = pick.mPosition;
            pickedTorso = pick.mbTorso;
            if (pick.mpModel) {
                pickedHandle = true;
                handle = EditorUtils::GetBoneForHandle(&pick.mpModel->mHandleKey);
                cModel* model = handle->GetModel();
                offset = model->mPosition - pick.mPosition;
                if (handle) {
                    if (handle->GetTypeID() == kHandleTypeBallConnector) {
                        found = true;
                        cSPEditorBlock* b = FindBlockForModel(handle->GetModel(), cameraPos);
                        if (b)
                            handle = b->mpBallConnectorHandle;
                        moving = b;
                    }
                    if (handle)
                        goto have_pick;
                }
            }
        }
        if (!moving) {
            moving = pick.mpBlock;
            found = true;
        } else {
            pickPos = moving->mPosition;
            found = true;
        }
have_pick:

        if (moving && found) {
            if (mbLimitPartCount && !mManipulatedBlockFromPalette && moving->CanSplit()) {
                // Ctrl-drag copy: split a copy off the clicked part.
                moving->PrepareSplit(0, 1);
                mpEditorLimits->OnBlockAdded(moving, 2);
                cSPEditorBlock* copy = moving->Split(2);
                if (mpEditorModel->IsSymmetryEnabled() && !moving->HasAttribute(kAttrNoSymmetry)) {
                    int symIndex = -1;
                    int idx = copy->GetSymmetryIndex();
                    if (idx)
                        symIndex = idx;
                    if (HasSymmetricPartner(copy))
                        GetSymmetricPartner(copy);
                    UpdateSymmetryRec(copy, symIndex);
                }
                moving = copy;
                if (moving->mpParent)
                    moving->mpParent->OnChildPicked(moving);
                if (moving->mpBallConnectorHandle)
                    moving->SetBooleanAttribute(12, false);
                mpActiveHandle.reset();
                if (handle && handle->GetTypeID() == kHandleTypeBallConnector) {
                    handle->SetState(1, false);
                    handle = moving->mpBallConnectorHandle;
                }
                didSplit = true;
                MessageManager()->MessageSend(0x1fe593bc, 0, moving, 0);
            }

            cSPEditorBlock* target = moving;
            if (!didSplit && mpEditorModel->IsSymmetryEnabled() && !moving->HasAttribute(kAttrSpine)) {
                cSPEditorBlock* sym = target;
                if (HasSymmetricPartner(moving)) {
                    sym = GetSymmetricPartner(moving);
                    if (mbSymmetricLimbs && !pickedTorso && moving.get() != sym &&
                        !moving->HasAttribute(kAttrNoSymmetricParent))
                        sym = moving->mpParent;
                }
                if (!moving->HasAttribute(kAttrNoSymmetry) || !sym->HasAttribute(kAttrNoSymmetry)) {
                    target = sym;
                    int symIndex = -1;
                    int idx = moving->GetSymmetryIndex();
                    if (idx)
                        symIndex = idx;
                    if (!mbSymmetricLimbs || sym->mpSymmetricRigblock) {
                        UpdateSymmetryRec(sym, symIndex);
                        cSPEditorBlock* other = sym->mpSymmetricRigblock;
                        if (other)
                            UpdateSymmetryRec(other, -symIndex);
                    }
                }
            }

            if (mbSymmetricLimbs && !moving->HasAttribute(kAttrSpine)) {
                if (target && !target->HasAttribute(kAttrNoSymmetry)) {
                    target->ResetLimbPose();
                    mpEditorModel->SetLimbsDirty(true);
                }
                if (!target->GetSymmetryIndex() && target->mpAsymmetricRigblock)
                    target->mpAsymmetricRigblock->SnapToAsymmetric(0, 0);
            }
            target->RecursiveFlagB();
            EditorUtils::SetSymmetricBlocksUIState(target, 0, moving->HasAttribute(kAttrIsTorso));
        }

        if (moving) {
            UpdateBlockState(moving, 0, 0, 0, 0, 0, 1, 1);
            if (mManipulatedBlockFromPalette)
                offset = moving->GetModelDefaultMouseOffset();
            else
                offset = moving->mPosition - pickPos;
        }

        if (moving && moving->mpBallConnectorHandle && HasSymmetricPartner(moving))
            dragLimb = true;

        mPreviousSelectedBlock = mpSelectedPart;

        if (IsManipulatorEnabled(0x8665f54d) && moving && moving->HasAttribute(kAttrLimb)) {
            if (dragLimb) {
                LinkSelection(mpSelectedPart, moving);
                SetTorsoBlock(0, false);
                SetSelectedBlock(0, true);
                cSPEditorManipulationLimb* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationLimb();
                m->Setup(handle, moving, mpEditorSkin, offset, mouseState);
                mpActiveManipulator = m;
            }
            goto deselect;
        }
        if (button != kMouseButtonLeft)
            goto deselect;

        if (mouseState & 1) {   // shift
            SetTorsoBlock(moving, false);
            SetSelectedBlock(0, true);
            cSPEditorBlock* b = moving;
            if (b) {
                if (IsManipulatorEnabled(0x6125ee88)) {
                    cSPEditorManipulationInterpenetration* m =
                        new("Editor", 0, 0, 0, 0) cSPEditorManipulationInterpenetration();
                    m->SetBlock(moving, offset, false);
                    mpActiveManipulator = m;
                    TriggerTutorialEvent(0xf, 1);
                } else if (b && IsManipulatorEnabled(0xf48ab41c) && !mbLimitPartCount) {
                    cSPEditorManipulationPlanarInterpenetration* m =
                        new("Editor", 0, 0, 0, 0) cSPEditorManipulationPlanarInterpenetration();
                    m->SetBlock(moving, offset, true, false);
                    mpActiveManipulator = m;
                    TriggerTutorialEvent(0x11, 1);
                }
            }
        }
        if (mpActiveManipulator)
            goto deselect;

        if ((mouseState & 2) && moving && IsManipulatorEnabled(0x6125ee88)) {   // ctrl
            SetTorsoBlock(moving, false);
            SetSelectedBlock(0, true);
            cSPEditorManipulationInterpenetration* m =
                new("Editor", 0, 0, 0, 0) cSPEditorManipulationInterpenetration();
            m->SetBlock(moving, offset, true);
            mpActiveManipulator = m;
            TriggerTutorialEvent(0x10, 1);
        }
        if (mpActiveManipulator)
            goto deselect;

        if (IsManipulatorEnabled(0x9ed74a02) && !moving && pickedTorso) {
            SetTorsoBlock(0, true);
            SetSelectedBlock(0, true);
            cSPEditorManipulationTorso* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationTorso();
            m->Setup(mpEditorModel, mpSkeleton);
            mpActiveManipulator = m;
            TriggerTutorialEvent(8, 1);
        }

        if (IsManipulatorEnabled(0x2d35af62) &&
            ((!moving && pickedTorso) || (moving && moving->HasAttribute(kAttrSpine)))) {
            SetTorsoBlock(0, true);
            SetSelectedBlock(0, true);
            cSPEditorManipulationSkin* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationSkin();
            m->Init();
            mpActiveManipulator = m;
            goto finish;
        }

        if (!pickedHandle && moving) {
            cSPEditorBlock* b = moving;
            if (IsManipulatorEnabled(0x5fde642e) && b->HasAttribute(kAttrSpine)) {
                SetTorsoBlock(0, true);
                SetSelectedBlock(0, true);
                cSPEditorManipulationSpine* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationSpine();
                m->Init(moving, offset, mpSkeleton);
                mpActiveManipulator = m;
                TriggerTutorialEvent(10, 1);
                goto finish;
            }

            SetTorsoBlock(b, false);
            SetSelectedBlock(0, true);
            if (IsManipulatorEnabled(0xa9910288) && moving->HasAttribute(kAttrSnapsToBone) &&
                !moving->HasAttribute(kAttrNoBoneDrag)) {
                cSPEditorManipulationBoneSnap* m =
                    new("Editor", 0, 0, 0, 0) cSPEditorManipulationBoneSnap();
                bool b2;
                if (!mManipulatedBlockFromPalette && moving->HasAttribute(kAttrNoInterpenetrate))
                    b2 = true;
                else
                    b2 = false;
                m->Setup(moving, offset, SkinPtr(mpEditorSkin), b2);
                mpActiveManipulator = m;
            } else if (IsManipulatorEnabled(0x1b73114c) && moving->HasAttribute(kAttrSnapsToBone)) {
                SetTorsoBlock(moving, false);
                SetSelectedBlock(0, true);
                cSPEditorManipulationBone* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationBone();
                bool notFromPalette = !mManipulatedBlockFromPalette;
                m->Setup(moving, offset, SkinPtr(mpEditorSkin), mbCellPinningToRigBlocks, notFromPalette);
                mpActiveManipulator = m;
            } else if (IsManipulatorEnabled(0x889cdbff)) {
                SetTorsoBlock(moving, false);
                SetSelectedBlock(0, true);
                cSPEditorManipulation74* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulation74();
                m->Setup(moving, offset);
                mpActiveManipulator = m;
            } else if (IsManipulatorEnabled(0x67b68e4d)) {
                SetTorsoBlock(moving, false);
                SetSelectedBlock(0, true);
                cSPEditorManipulation8C* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulation8C();
                m->Setup(moving, offset, mManipulatedBlockFromPalette || didSplit);
                mpActiveManipulator = m;
            } else if (IsManipulatorEnabled(0xf48ab41c)) {
                SetTorsoBlock(moving, false);
                SetSelectedBlock(0, true);
                cSPEditorManipulationPlanarInterpenetration* m =
                    new("Editor", 0, 0, 0, 0) cSPEditorManipulationPlanarInterpenetration();
                m->SetBlock(moving, offset, false, mManipulatedBlockFromPalette || didSplit);
                mpActiveManipulator = m;
            }
            goto finish;
        }

        if (handle && pickedHandle) {
            // A handle (ball connector, deform, scale...) was clicked.
            HandlePtr previous;
            previous = mpActiveHandle;
            mbHandleRollover = false;
            SetRolloverHandle(0, false);
            mpLastActiveHandle = previous.get();
            handle->GetTypeID();
            moving = handle->GetRigblock();

            if (IsManipulatorEnabled(0x8665f54d) && handle->GetTypeID() == kHandleTypeBallConnector &&
                !mManipulatedBlockFromPalette) {
                SetTorsoBlock(0, false);
                SetSelectedBlock(0, true);
                cSPEditorManipulationLimb* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationLimb();
                m->Setup(handle, 0, mpEditorSkin, offset, mouseState);
                mpActiveManipulator = m;
            } else if (IsManipulatorEnabled(0xe931544d) &&
                       handle->GetTypeID() == kHandleTypeBallConnector &&
                       !mManipulatedBlockFromPalette) {
                SetTorsoBlock(0, false);
                cSPEditorBlock* parent = moving->mpParent;
                if (parent && parent->HasAttribute(kAttrLimb)) {
                    cSPEditorManipulationObject40* m =
                        new("Editor", 0, 0, 0, 0) cSPEditorManipulationObject40();
                    m->Set(BlockPtr(parent), offset);
                    mpActiveManipulator = m;
                }
            } else if (IsManipulatorEnabled(0x9f48c094) && handle->GetTypeID() == kHandleTypeDeform) {
                SetTorsoBlock(moving, false);
                cSPEditorManipulationDeform* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationDeform();
                m->Setup(interface_cast_Deform(handle), offset, mpEditorSkin);
                mpActiveManipulator = m;
                TriggerTutorialEvent(3, 1);
            } else if (IsManipulatorEnabled(0xbb46d99a) &&
                       handle->GetTypeID() == kHandleTypeSpineResize) {
                SetTorsoBlock(0, true);
                cSPEditorManipulationSpineResize* m =
                    new("Editor", 0, 0, 0, 0) cSPEditorManipulationSpineResize();
                m->Init(moving, offset, mpSkeleton, mpEditorSkin, mpEditorLimits);
                mpActiveManipulator = m;
                TriggerTutorialEvent(9, 1);
            } else if (IsManipulatorEnabled(0x855de44d) &&
                       (handle->GetTypeID() == kHandleTypeScaleA ||
                        handle->GetTypeID() == kHandleTypeScaleB)) {
                if (mpEditorModel->IsSymmetryEnabled()) {
                    UpdateSymmetryRec(moving, -1);
                    if (moving->mpSymmetricRigblock)
                        UpdateSymmetryRec(moving->mpSymmetricRigblock, 1);
                    EditorUtils::SetSymmetricBlocksUIState(moving, 0, false);
                }
                SetTorsoBlock(moving, false);
                cSPEditorManipulationScale* m = new("Editor", 0, 0, 0, 0) cSPEditorManipulationScale();
                m->Setup(handle, offset, pick.mPosition);
                mpActiveManipulator = m;
            }
        }
        goto finish;

deselect:
        if (moving)
            SetRolloverBlock(0, -1);
    }

finish:
    if (mpMovingPart && HasSymmetricPartner(mpMovingPart))
        GetSymmetricPartner(mpMovingPart);

    if (!mpActiveManipulator) {
        SetTorsoBlock(0, false);
        return false;
    }
    if (mbTorsoInEffectsMask) {
        RemoveTorsoFromEffectsMask();
        mbTorsoInEffectsMask = false;
    }
    bool handled = mpActiveManipulator->OnMouseDown(button, x, y, mouseState);
    if (mManipulatedBlockFromPalette) {
        mpActiveManipulator->OnMouseMove(x, y, mouseState);
        mpActiveManipulator->Update(0.0f);
        return handled;
    }
    SetupCameraUI();
    return handled;
}
