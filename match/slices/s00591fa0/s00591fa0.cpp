// slice s00591fa0 -- SP::cAppModeEditorBase::HandleMessage (6297 B, EA::Messaging::IHandler override).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (no /EHsc: string/AutoRefCount locals get no EH frame).
//
// The override lives in the IHandlerRC sub-object at +0x10, so the original sees `this` as this+0x10
// (every `lea ecx,[esi-0x10]` is a call on the full object). Field offsets below are full-object
// offsets taken from the retail disassembly (the 2008 PDB layout is shifted by 4..0x40 bytes here;
// names follow the PDB / ModAPI where the role matches).
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------- basic types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};
struct Flags128 {            // eastl::bitset<128> passed by value (validity masks)
    uint32_t mWord[4];
};
// bitset<128>().set(bit) for a bit in the first word, as the inline set() expands it.
inline Flags128 MakeFlags128(uint32_t mask) {
    Flags128 f;
    uint32_t w = 0;
    f.mWord[0] = w | mask;
    f.mWord[1] = w;
    f.mWord[2] = w;
    f.mWord[3] = w;
    return f;
}
struct BoundingBox {
    Vector3 mMin, mMax;
};
struct Plane {
    Vector3 n;
    float d;
};
struct Rect {
    float x1, y1, x2, y2;
};

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0

extern char gEmptyString[];   // 0x01667bac, shared empty buffer of eastl strings

namespace eastl {
// basic_string<char>: ctor inline, dtor out of line (0x00530670).
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    string() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~string();                                              // 0x00530670
    int sprintf(const char* fmt, ...);                      // 0x00472fe0
};
// basic_string<wchar_t>: ctor inline, dtor = inline DeallocateSelf() call.
struct wstring {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wstring()
        : mpBegin((wchar_t*)gEmptyString), mpEnd((wchar_t*)gEmptyString),
          mpCapacity((wchar_t*)gEmptyString + 1) {}
    ~wstring() { DeallocateSelf(); }
    void DeallocateSelf();                                  // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};
}

int WStr_Format(eastl::wstring* out, const wchar_t* fmt, ...);   // 0x0041e050

namespace EA {
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(T* p);                                     // 0x0061df40 / 0x00572660 (out of line)
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    AutoRefCount& operator=(T* p);                          // 0x00572620 (out of line)
    T** AsPPTypeParam();                                    // 0x00a16f40
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    // inline `= NULL`
    __forceinline void Clear() {
        T* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
    }
};
}
using EA::AutoRefCount;

// ---------------------------------------------------------------- engine stubs
namespace SP {

class cString {
public:
    uint32_t mData[8];
    cString(uint32_t tableID, int instanceID, const wchar_t* defaultText);   // 0x006b5770
    ~cString();                                                             // 0x006b5240
    const wchar_t* GetText(int count, bool pluralize);                      // 0x006b55c0
};

class cPropertyList;
bool GetPropertyAsKeyInstance(cPropertyList* prop, uint32_t id, uint32_t* out);   // 0x006a12a0
bool GetFloatProperty(cPropertyList* prop, uint32_t id, float* out);              // 0x0040cf10

// global flag table at 0x015fd918 (bounds-checked lookup, or direct index for compile-time ids)
struct cFlagTable {
    uint32_t pad0[0x38 / 4];
    uint32_t mCount;          // +0x38
    int* mpFlags;             // +0x3c
    bool IsSet(uint32_t id) const;                          // 0x006a25a0
};
extern cFlagTable* gFlagTable;                              // 0x015fd918

class IMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t messageID, void* data, int flags);          // +0x14
    virtual void MessageSend(uint32_t messageID, void* data, int a, int b);   // +0x18
};
IMessageServer* MessageServer();                            // 0x0067dcc0

class cViewer {
public:
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, int a, int b);   // 0x007c3d30
    void GetCameraRayOrigin(Vector3* origin, Vector3* dir);                 // 0x007c4900
};

class IApp {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual uint32_t GetActiveModeID();                     // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54();
    virtual cViewer* GetViewer();                           // +0x58
};
IApp* App();                                                // 0x0067dd10

class IAppSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void ToggleFullScreenWindowed();                // +0x30
    virtual bool IsFullScreen();                            // +0x34
};
IAppSystem* AppSystem();                                    // 0x0067dd00

class IWindow {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual const Rect& GetArea();                          // +0x34
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78();
    virtual void SetFlag(int flag, bool value);             // +0x7c
};
class cSPUIMainWinBase { public: virtual void v00(); };
class cSPUIMainWin : public cSPUIMainWinBase, public IWindow {
public:
    uint64_t GetMouseRefs();                                // 0x008130a0
};
class IWindowManager {
public:
    virtual void v00();
    virtual IWindow* GetMainWindow();                       // +0x04
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void v58(); virtual void v5c(); virtual void v60(); virtual void v64();
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80();
    virtual int GetModalWindow();                           // +0x84
};
IWindowManager* WindowManager();                            // 0x0067caa0

class cUIHints {
public:
    void SetEnabled(bool enabled, bool save);               // 0x0067c420
    void ShowHint(uint32_t hintID);                         // 0x0067c830
};
cUIHints* UIHints();                                        // 0x0067cac0

void ToggleDebugDraw(int arg);
class cAssetBrowser {
public:
    uint32_t pad0[0x1c / 4];
    bool mbVisible;                                         // +0x1c
};
cAssetBrowser* AssetBrowser();                              // 0x00401030                              // 0x008098f0 (__cdecl)

class ISaveArea {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual const wchar_t* GetPath();                       // +0x28
};
ISaveArea* GetSaveArea(uint32_t directoryID);               // 0x006b1f90

// ---- resources
class Resource {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
};
class cEditorResource : public Resource {
public:
    uint32_t pad4[(0x18 - 4) / 4];
    uint32_t mTypeID;                                       // +0x18
    void GetRequiredValidity(Flags128* out, Flags128 available, bool b);   // 0x004bac30
};
class IResourceManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey& key, Resource** out, int a, int b, int c, int d);   // +0x0c
};
IResourceManager* GetManager();                             // 0x0067dcd0
cEditorResource* interface_cast_cEditorResource(AutoRefCount<Resource>* res);   // 0x00421eb0
uint32_t RemapTypeId(uint32_t typeID);                      // 0x00432f10
bool IsValiditySatisfied(Flags128 required, Flags128 available);           // 0x004f3d60

// ---- editor model / blocks
class cSPEditorModel {
public:
    uint32_t pad0[0xc / 4];
    ResourceKey mKey;                                       // +0x0c
    const wchar_t* GetFileName();                           // 0x004ae000
    void SetRegionColor(int region, Vector3 color);         // 0x004add30
};
class cSPEditorBlock {
public:
    virtual void v00(); virtual void v04();
    virtual void Release();                                 // +0x08
    uint32_t pad4[(0x144 - 4) / 4];
    Vector3 mPosition;                                      // +0x144
    BoundingBox* GetBBox(BoundingBox* out, int a, int b, int c);   // 0x0044ae00
};
class cSPEditorSkinManager {
public:
    void* GetSkin(int which);                               // 0x004c49e0
    bool IsBusy();                                          // 0x004c58b0
    void RepaintModel(cSPEditorModel* model);               // 0x004c5200
};
class cSPEditorPaintTheme {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
    uint32_t mData[(0x1a0 - 4) / 4];
    cSPEditorPaintTheme();                                  // 0x004b24c0
    void SetSource(uint32_t source);                        // 0x004b26e0
    void ReadFromProp(uint32_t propID);                     // 0x004b2bb0
    void WriteToProp(cSPEditorModel* model, int region);    // 0x004b2f80
    void SetRegionColor(Vector3 color, int region);         // 0x004b3c70
};

// ---- UI
class cSPEditorUI {
public:
    IWindow* FindWindowByID(uint32_t id);                   // 0x005dc310
    void ShowGeneralMessage(const wchar_t* text);           // 0x005dc460
    bool IsPartsPaletteActive();                            // 0x005dc2e0
    bool IsPaintPaletteActive();                            // 0x005dc2f0
    bool IsEditorUIVisible();                               // 0x005dc450
    void HandleFileDrop(ResourceKey key);                   // 0x005df8f0
    void UpdateUIBasedOnModelSaveability();                 // 0x005dd7a0
    void ShowCreatureNameEdit();                            // 0x005dc560
    void HideCreatureNameEdit();                            // 0x005dc580
    void ModeHelper();                                      // 0x005de9e0
    void CreateNewCreature(uint32_t layoutID, bool fromPaint);   // 0x00635810
};
struct cPaletteCategory {
    uint32_t pad0[0x74 / 4];
    uint32_t mCategoryID;                                   // +0x74
};
struct cPaletteCategoryUI {
    uint32_t pad0[0x6c / 4];
    cPaletteCategory* mpCategory;                           // +0x6c
};
struct cCategoryInfo {
    uint32_t mPropID;
    uint32_t mData[7];
};
class cSPPaletteUI {
public:
    uint32_t pad0[0x34 / 4];
    cPaletteCategoryUI** mCategoriesBegin;                  // +0x34
    cPaletteCategoryUI** mCategoriesEnd;                    // +0x38
    int GetCategoryCount() { return (int)(mCategoriesEnd - mCategoriesBegin); }
    cPaletteCategoryUI* GetCategory(int index);             // 0x005cae30
    void SetCurrentCategoryIndex(int index);                // 0x005cb240
    bool IsPaintByNumber();                                 // 0x005ca920
    void GetCategoryInfo(cCategoryInfo* out);               // 0x005cb1b0
};
class cDetachedRollover {
public:
    void HideWin();                                         // 0x005cc0e0
    void Show(const wchar_t* text);                         // 0x005cc120
    void SetPositionAndOffset(float x, float y, float offsetX, float offsetY);   // 0x008283a0
};
void WorldToScreen(const Vector3* pos, float* x, float* y);    // 0x004a3760

class cSPPlayMode {
public:
    uint32_t pad0[0xc / 4];
    cSPEditorUI* mpUI;                                      // +0x0c
    int GetCurrentBabyIndex();                              // 0x00628500
    int GetBabyIndex(uint32_t creatureID);                  // 0x00628720
    void SelectBaby(int index);                             // 0x0062ba10
    bool RunSkinPaintOnEditorModel(int index, const ResourceKey* key);   // 0x0062c7e0
    void ShowPaintDisabled();                               // 0x00628910
};

struct cAnimatedBaby {
    uint32_t mCreatureID;
    uint32_t mData[11];
};

class cSPEditorAnimatedEventInfo {
public:
    virtual void v00(); virtual void AddRef();
    virtual void Release();                                 // +0x08
    uint32_t mData[(0x30 - 4) / 4];
    cSPEditorAnimatedEventInfo();                           // 0x0059d960
    void MessageSend(uint32_t messageID, int a, cSPEditorModel* model, uint32_t brainLevel, int b,
                     float delay, int c, uint32_t animID, float speed);   // 0x0059d8b0
};

// verb-tray ability (0x4aca143 message)
class cAbility {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual eastl::wstring GetName(int index);              // +0x20
    uint32_t pad4[(0x28 - 4) / 4];
    uint32_t mAnimationID;                                  // +0x28
};
void* GetVerbTrayCollection(void* object);                  // 0x00572730 (interface cast)

class cEditorLaunchData {
public:
    virtual void AddRef();
    virtual void Release();
    uint32_t pad4[(0x10 - 4) / 4];
    ResourceKey mKey;                                       // +0x10
    uint32_t pad1c[(0x64 - 0x1c) / 4];
    bool mbHasBrain;                                        // +0x64
};
class cEditorAnimEvent {
public:
    virtual void AddRef();
    virtual void Release();
};
int GetModelValidityState(const ResourceKey* key);          // 0x00552300

class IEditorLimits {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void AddCost(int a, uint32_t amount);           // +0x20
    virtual void SetBrainLevel(int a, uint32_t level);      // +0x24
    virtual void v28(); virtual void v2c();
    virtual void SetBudget(uint32_t budget);                // +0x30
};

class ICastable {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint32_t typeID);                    // +0x0c
};

// ---- effects
struct XformMsg {
    uint16_t mFlags;
    uint16_t mChangeCount;
    Vector3 mPosition;                                      // +0x04
    float mScale;                                           // +0x10
    float mRotation[9];
    XformMsg();                                             // 0x00434040
    void SetPosition(const Vector3& v) { mFlags |= 4; mChangeCount++; mPosition = v; }
    void SetScale(float s) { mChangeCount++; mScale = s; }
};
class cEffectText {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
    uint32_t pad4[(0xc - 4) / 4];
    eastl::wstring mText;                                   // +0x0c
    cEffectText();                                          // 0x0057a6d0
};
class IVisualEffect {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
    virtual bool Start(int flags);                          // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void SetTransform(const XformMsg& xform);       // +0x18
    virtual void v1c(); virtual void v20(); virtual void v24(); virtual void v28();
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void SetParam(int param, cEffectText* value);   // +0x4c
};
class IEffectsManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(uint32_t id, int flags, IVisualEffect** out);   // +0x2c
};
IEffectsManager* EffectsManager();                          // 0x0067ddd0

class cEffectsWorld {
public:
    void SetEffectTransform(uint32_t effectID, int flags, const XformMsg* xform, cSPEditorBlock* block);  // 0x0045ac20
    void StopEffect(uint32_t effectID, int flags);          // 0x0045ae10
};
cEffectsWorld* GetEditorEffectsWorld();                     // 0x00401050

bool IntersectRayPlane(const Vector3* origin, const Vector3* dir, const Plane* plane, float* t);  // 0x0044e640
Vector3* Vector3_Normalize(Vector3* out, const Vector3* v);  // 0x00436ce0
void PlayEditorSound(uint32_t soundID, uint32_t group, float pitch, int flags);   // 0x00435f40
void PlayUISound(uint32_t soundID);                         // 0x004a88d0
void ColorFromRGB(Vector3* out, uint32_t rgb);              // 0x00576ab0
void SplitPath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext, int flags);  // 0x00930180
void ExportBakedModelToXMF(cSPEditorModel* model, const wchar_t* dir, const ResourceKey* key);  // 0x00466690
void SetMoneyString(double amount, wchar_t* buf, int bufSize, const wchar_t* fmt, const wchar_t* currency); // 0x008822e0
bool KeysEqual(const ResourceKey* a, const ResourceKey* b);  // 0x004eb930
void UpdateModelValidity(uint32_t value, Flags128* validity);   // 0x004edf40

class cBakeManager { public: void Invalidate(uint32_t value); };   // 0x005d60c0
extern cBakeManager* gBakeManager;                          // 0x015eebec

extern Flags128 gAllValidity;                               // 0x015dac10
extern Vector3 gRolloverDefaultPos;                         // 0x015e4f18

// message whose payload is an object (0x24ce123)
class cConfigMessage {
public:
    void* GetConfig();                                      // 0x008d3ac0
    uint32_t GetConfigID(int index);                        // 0x00688ed0
};

// ---------------------------------------------------------------- the editor mode
class cIAppMode { public: virtual void v00(); };
class cILayer { public: virtual void v00(); };
class cIHintProcessor { public: virtual void v00(); };
class cISPEditorNameProvider { public: virtual void v00(); };
}  // namespace SP

namespace EA { namespace Messaging {
class IHandlerRC {
public:
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};
}
template <class T> class RefCountVTemplate {
public:
    virtual void v00();
    T mRefCount;
};
}

namespace SP {

// message posted for model-changed notifications
struct cEditorModelMessage {
    cISPEditorNameProvider* mpSender;
    uint32_t pad4;
    uint32_t mValue;
    uint32_t padc;
    uint32_t mFlags;
};

class cAppModeEditorBase : public cIAppMode, public cILayer, public cIHintProcessor,
                           public cISPEditorNameProvider, public EA::Messaging::IHandlerRC,
                           public EA::RefCountVTemplate<int> {
public:
    uint32_t pad1c[(0x24 - 0x1c) / 4];
    cPropertyList* mCurrentConfigProperties;                // +0x24
    uint32_t pad28[(0x48 - 0x28) / 4];
    Flags128 mModelValidity;                                // +0x48
    uint32_t pad58[(0x78 - 0x58) / 4];
    cSPEditorUI* mUI;                                       // +0x78
    cSPPlayMode* mPlayMode;                                 // +0x7c
    uint32_t pad80[(0x98 - 0x80) / 4];
    cSPEditorModel* mEditorModel;                           // +0x98
    uint32_t pad9c[(0xcc - 0x9c) / 4];
    cSPEditorBlock* mRolloverBlock;                         // +0xcc
    uint32_t padd0;
    cSPEditorBlock* mSelectedBlock;                         // +0xd4
    uint32_t padd8;
    AutoRefCount<cSPEditorBlock> mToBeSelectedBlock;        // +0xdc
    uint32_t pade0[(0x150 - 0xe0) / 4];
    cSPEditorSkinManager* mSkinManager;                     // +0x150
    cSPEditorSkinManager* mSaveSkinManager;                 // +0x154
    uint32_t pad158[(0x1a0 - 0x158) / 4];
    int mTransitionAnimation;                               // +0x1a0
    uint32_t pad1a4;
    int mTransitionState;                                   // +0x1a8
    uint32_t pad1ac[(0x1cc - 0x1ac) / 4];
    AutoRefCount<cEditorLaunchData> mLaunchData;            // +0x1cc
    ResourceKey mParentModelKey;                            // +0x1d0
    uint32_t pad1dc[(0x20c - 0x1dc) / 4];
    wchar_t mCurrencyChar;                                  // +0x20c
    uint16_t pad20e;
    uint32_t pad210[(0x2a0 - 0x210) / 4];
    cSPEditorPaintTheme* mCurrentPaintTheme;                // +0x2a0
    void* mVerbIconTray;                                    // +0x2a4
    uint32_t mSaveExtension;                                // +0x2a8
    uint32_t mSaveDirectory;                                // +0x2ac
    bool mIsActive;                                         // +0x2b0
    uint8_t pad2b1[3];
    uint32_t pad2b4[(0x310 - 0x2b4) / 4];
    bool mbPreserveLineage;                                 // +0x310
    uint8_t pad311[3];
    uint32_t pad314[(0x31c - 0x314) / 4];
    int mMode;                                              // +0x31c
    uint32_t pad320[(0x364 - 0x320) / 4];
    uint32_t mBrainLevel;                                   // +0x364
    uint32_t pad368;
    cAnimatedBaby* mAnimatedBabiesBegin;                    // +0x36c
    cAnimatedBaby* mAnimatedBabiesEnd;                      // +0x370
    uint32_t pad374[(0x380 - 0x374) / 4];
    AutoRefCount<cEditorAnimEvent> mpAnimEvent;             // +0x380
    uint32_t pad384;
    int mPendingSaveAction;                                 // +0x388
    int mSaveState;                                         // +0x38c
    uint32_t pad390;
    bool mbLeftMouseDragged;                                // +0x394
    bool mbRightMouseDragged;                               // +0x395
    uint8_t pad396[3];
    bool mbShowModelSaved;                                  // +0x399
    uint8_t pad39a[2];
    uint32_t pad39c[(0x3bc - 0x39c) / 4];
    cSPPaletteUI* mpPartsPaletteUI;                         // +0x3bc
    uint32_t pad3c0;
    cSPPaletteUI* mpPaintPaletteUI;                         // +0x3c4
    uint32_t pad3c8[(0x430 - 0x3c8) / 4];
    bool mbNeedsBudgetUpdate;                               // +0x430
    uint8_t pad431[3];
    IEditorLimits* mpEditorLimits;                          // +0x434
    uint32_t pad438[2];
    uint64_t mnModelStartTime;                              // +0x440
    uint32_t pad448[(0x4a0 - 0x448) / 4];
    cDetachedRollover* mReplaceBlockRollover;               // +0x4a0
    uint32_t pad4a4[(0x4b0 - 0x4a4) / 4];
    bool mbIsCreatureModel;                                 // +0x4b0
    bool pad4b1;
    bool mbModelPainted;                                    // +0x4b2
    bool pad4b3;
    bool mbModelChanged;                                    // +0x4b4

    virtual bool HandleMessage(uint32_t messageID, void* pMessage);   // 0x00591fa0

    void SaveStateChanged(void* msg, bool b);               // 0x0057c530
    void SetCurrentConfig(uint32_t config, ResourceKey key);   // 0x00579720
    void SwitchConfigFromMessage(uint32_t configID);        // 0x00589ce0
    void EnterPaintMode(bool b);                            // 0x005744b0
    void SetRolloverBlock(cSPEditorBlock* block, int region);   // 0x00573c00
    void SetMode(int mode, bool b);                         // 0x00587270
    void LoadModel(const ResourceKey* key, Flags128 validity, bool b);   // 0x0058cee0
    bool IsPaintDisabled();                                 // 0x00573950
    Flags128 GetModelValidity();                            // 0x00572160
    void SetValidityFlags(Flags128 set, Flags128 mask);     // 0x005721b0
    bool IsResourceOfOtherEditor(cEditorResource* res);     // 0x00573070
    void InitBrain(uint32_t level);                         // 0x005722f0
    void SetupBrainFromLaunchData();                        // 0x0057bfb0
    void InitializeUndoList();                              // 0x00586690
    void SetSelectedBlock(cSPEditorBlock* block, bool b);   // 0x0057e790
    void AddUndoState(bool a, bool b);                      // 0x00586410
    void UpdateNameEditFromModel();                         // 0x00575120
    bool HandleAnimEvent(uint32_t id);                      // 0x00574460
    void PlayAnimEvent(cEditorAnimEvent* ev);               // 0x00585330
    bool HandlePaletteItemTriggerMessage(void* item, uint32_t id);   // 0x00591690
};

// ---------------------------------------------------------------- message payloads
struct MsgBoolOut { uint32_t pad0[2]; bool* mpResult; };
struct MsgConfig { uint32_t pad0[2]; uint32_t mConfigID; };
struct MsgReplaceRollover { uint32_t pad0[2]; cSPEditorBlock* mpBlock; uint32_t padc; float mCost; };
struct MsgFileDrop { ResourceKey** mppKey; };
struct MsgAbility { cAbility* mpAbility; uint32_t pad4; void* mpSource; };
struct MsgCategory { uint32_t pad0[2]; uint32_t mCategoryID; };
struct MsgInt8 { uint32_t pad0[2]; uint32_t mValue; };
struct MsgNameEdit { bool mbShow; ResourceKey mKey; };
struct MsgBudget { uint32_t mBudget; };
struct MsgBlock { cSPEditorBlock* mpBlock; };
struct MsgModel { cSPEditorModel* mpModel; uint32_t pad4; uint32_t mValue; };
struct MsgBrain { uint32_t pad0[2]; uint32_t mBrainLevel; uint32_t padc; uint32_t mInitLevel; };
struct MsgPaint { uint32_t pad0[2]; uint32_t mColor; uint32_t padc[3]; int mRegion; uint32_t pad1c; int mbTheme; };
struct MsgPaletteItem { uint32_t pad0[4]; uint32_t mID; uint32_t pad14[3]; ICastable* mpItem; };
struct MsgAnimEvent { uint32_t pad0[3]; uint32_t mID; uint32_t pad10; cSPEditorModel* mpModel; };
struct MsgMoney { uint32_t mAmount; uint32_t pad4; float x; uint32_t padc; float y; uint32_t pad14; float z; };
struct MsgKeyReplace { ResourceKey mKey; bool mbReplace; uint8_t padd[3]; ResourceKey mNewKey; };

// @ 0x00591fa0
bool cAppModeEditorBase::HandleMessage(uint32_t messageID, void* pMessage) {
    switch (messageID) {
    case 0x0052f180:
        SaveStateChanged(pMessage, true);
        return true;

    case 0x01c94703:
        mbLeftMouseDragged = true;
        return false;

    case 0x01c94708:
        mbRightMouseDragged = true;
        return false;

    case 0x01ee1009:
        *((MsgBoolOut*)pMessage)->mpResult = false;
        goto finishSave;

    case 0x022d308b: {
        ResourceKey key;
        key.instanceID = 0;
        key.typeID = 0;
        key.groupID = 0;
        SetCurrentConfig(((MsgConfig*)pMessage)->mConfigID, key);
        return true;
    }

    case 0x024ce123: {
        if (!gFlagTable->IsSet(0x594a0fb)) return false;
        cConfigMessage* msg = (cConfigMessage*)pMessage;
        if (!msg->GetConfig()) return false;
        SwitchConfigFromMessage(msg->GetConfigID(0));
        return false;
    }

    case 0x029d57f4:
        mbShowModelSaved = false;
        return true;

    case 0x03fc3f13: {
        // "export baked model": write <save dir>/<model name>.xsf and report it
        const wchar_t* dir = GetSaveArea(mSaveDirectory)->GetPath();
        wchar_t fileName[0x100];
        SplitPath(mEditorModel->GetFileName(), 0, 0, fileName, 0, 4);
        eastl::wstring path;
        WStr_Format(&path, L"%ls/%ls.xsf", dir, fileName);
        ResourceKey key = mEditorModel->mKey;
        ExportBakedModelToXMF(mEditorModel, dir, &key);
        if (mUI) {
            eastl::wstring text;
            WStr_Format(&text, L"Model saved to %ls", path);
            mUI->ShowGeneralMessage(text.c_str());
        }
        MessageServer()->PostMSG(0x29d57f4, 0, 0);
        return true;
    }

    case 0x044ef2b8:
        if (mMode == 1) {
            EnterPaintMode(true);
            cSPPaletteUI* paletteUI = mpPaintPaletteUI;
            if (paletteUI && paletteUI->IsPaintByNumber()) SetRolloverBlock(0, -1);
        }
        return false;

    case 0x0462c656:
        mTransitionAnimation = 0;
        return true;

    case 0x04519b5f:
        if (App()->GetActiveModeID() == 0xdbdba1) {
            cSPEditorUI* ui = mUI;
            if (ui) ui->FindWindowByID(0xffffffff)->SetFlag(1, true);
            if (gFlagTable->mpFlags[0x46] != 0) ToggleDebugDraw(0);
        }
        return false;

    case 0x047d7cc6: {
        if (AppSystem()->IsFullScreen()) AppSystem()->ToggleFullScreenWindowed();
        cSPEditorUI* ui = mUI;
        ui->FindWindowByID(0xffffffff)->SetFlag(1, true);
        UIHints()->SetEnabled(true, true);
        return false;
    }

    case 0x048e5911: {
        MsgReplaceRollover* msg = (MsgReplaceRollover*)pMessage;
        float cost = msg->mCost;
        cSPEditorBlock* block = msg->mpBlock;
        if (mReplaceBlockRollover) {
            cString text(0x496bfb26, 7, L"Replace for ");
            mReplaceBlockRollover->Show(text.GetText((int)cost, true));
            const Rect& area = WindowManager()->GetMainWindow()->GetArea();
            float offsetX = (area.x2 - area.x1) * 0.0125f;
            Vector3 pos = gRolloverDefaultPos;
            float offsetY = (area.y2 - area.y1) * -0.016666668f;
            if (block) {
                BoundingBox bbox;
                const BoundingBox* bb = block->GetBBox(&bbox, 0, 0, 0);
                pos.x = block->mPosition.x + (bb->mMin.x + bb->mMax.x) * 0.5f;
                pos.y = block->mPosition.y + (bb->mMax.y + bb->mMin.y) * 0.5f;
                pos.z = block->mPosition.z + (bb->mMax.z + bb->mMin.z) * 0.5f;
            }
            float screenX, screenY;
            WorldToScreen(&pos, &screenX, &screenY);
            mReplaceBlockRollover->SetPositionAndOffset(screenX, screenY, offsetX, offsetY);
        }
        return true;
    }

    case 0x048e5912:
        if (mReplaceBlockRollover) mReplaceBlockRollover->HideWin();
        return true;

    case 0x04aca143: {
        MsgAbility* msg = (MsgAbility*)pMessage;
        cAbility* ability = msg->mpAbility;
        if (mVerbIconTray == GetVerbTrayCollection(msg->mpSource) && ability && ability->mAnimationID) {
            AutoRefCount<cSPEditorAnimatedEventInfo> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo());
            info->MessageSend(0x248dca26, 0, mEditorModel, mBrainLevel, 0, 0.0f, 0, ability->mAnimationID, 1.0f);
        } else if (ability && !ability->mAnimationID) {
            // debug report (the assert that consumed it is compiled out)
            eastl::string text;
            text.sprintf("Ability %ls does not have an animation.\n", ability->GetName(0).c_str());
        }
        return false;
    }

    case 0x05132389: {
        // a model file was dropped on the editor window
        ResourceKey** ppKey = ((MsgFileDrop*)pMessage)->mppKey;
        ResourceKey key;
        key.instanceID = 0;
        key.typeID = 0;
        key.groupID = 0;
        if (ppKey) key = **ppKey;
        if (!mIsActive) return false;
        bool browserOpen;
        if (AssetBrowser() && AssetBrowser()->mbVisible) browserOpen = true;
        else browserOpen = false;
        bool paletteActive = false;
        if (mUI->IsPartsPaletteActive() || mUI->IsPaintPaletteActive() || gFlagTable->IsSet(0x678f3f1)) paletteActive = true;
        if (browserOpen || !paletteActive) return false;

        if (mMode == 2) {
            if (!gFlagTable || !gFlagTable->IsSet(0xd7f24dcf) || IsPaintDisabled()) {
                mPlayMode->ShowPaintDisabled();
                return false;
            }
            IResourceManager* resMgr = GetManager();
            AutoRefCount<Resource> res;
            if (!resMgr) return false;
            if (resMgr->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
                cEditorResource* edRes = interface_cast_cEditorResource(&res);
                if (edRes) {
                    Flags128 required;
                    edRes->GetRequiredValidity(&required, GetModelValidity(), true);
                    if (!IsValiditySatisfied(required, GetModelValidity())) {
                        SetValidityFlags(MakeFlags128(0x4000000), MakeFlags128(0x4000000));
                        return true;
                    }
                    RemapTypeId(edRes->mTypeID);
                    if (IsResourceOfOtherEditor(edRes)) {
                        UIHints()->ShowHint(0xffc453c6);
                        return true;
                    }
                    uint32_t layouts[3];
                    layouts[0] = 0x3e44efc;
                    layouts[1] = 0x445d380;
                    layouts[2] = 0x445d3c0;
                    int index = mPlayMode->GetCurrentBabyIndex();
                    bool selected = false;
                    if (index < 0 || index > 3) {
                        uint32_t oldest = 0xffffffff;
                        for (int n = (int)(mAnimatedBabiesEnd - mAnimatedBabiesBegin), i = 0; i < n; ++i) {
                            uint32_t id = mAnimatedBabiesBegin[i].mCreatureID;
                            if (id < oldest) oldest = id;
                        }
                        index = mPlayMode->GetBabyIndex(oldest);
                        mPlayMode->SelectBaby(index);
                        selected = true;
                    }
                    if (mPlayMode->RunSkinPaintOnEditorModel(index, &key)) {
                        if (mPlayMode->mpUI && index >= 0 && index < 3) mPlayMode->mpUI->CreateNewCreature(layouts[index], true);
                    } else if (selected) {
                        if (mPlayMode->mpUI && index >= 0 && index < 3) mPlayMode->mpUI->CreateNewCreature(layouts[index], false);
                    }
                }
            }
            return false;
        }
        if (mUI->IsEditorUIVisible() && WindowManager()->GetModalWindow() == 0 && ppKey) mUI->HandleFileDrop(key);
        return false;
    }

    case 0x051cc0b8: {
        SetMode(0, true);
        cSPEditorUI* ui = mUI;
        if (ui) ui->FindWindowByID(0xffffffff)->SetFlag(1, true);
        mbIsCreatureModel = GetModelValidityState(&mLaunchData->mKey) == 1;
        LoadModel(&mLaunchData->mKey, gAllValidity, true);
        return false;
    }

    case 0x056d39e9:
        mUI->ModeHelper();
        return false;

    case 0x05d02a72: {
        uint32_t categoryID = ((MsgCategory*)pMessage)->mCategoryID;
        cSPPaletteUI* paletteUI = mpPartsPaletteUI;
        if (!paletteUI) return false;
        int count = paletteUI->GetCategoryCount();
        for (int i = 0; i < count; ++i) {
            cPaletteCategoryUI* cat = mpPartsPaletteUI->GetCategory(i);
            if (cat && cat->mpCategory && cat->mpCategory->mCategoryID == categoryID) {
                mpPartsPaletteUI->SetCurrentCategoryIndex(i);
                return false;
            }
        }
        return false;
    }

    case 0x060b3d03:
        SetValidityFlags(MakeFlags128(0x4000000), MakeFlags128(0x4000000));
        return false;

    case 0x062628f0:
        mbNeedsBudgetUpdate = false;
        return false;

    case 0x0657abe5:
        ((MsgInt8*)pMessage)->mValue = 0;
    finishSave: {
        int state = mSaveState;
        if (state != 0 && state != 6) {
            mPendingSaveAction = 3;
            return false;
        }
        MessageServer()->MessageSend(0x153c326, 0, 0, 0);
        return false;
    }

    case 0x068cd252: {
        MsgNameEdit* msg = (MsgNameEdit*)pMessage;
        if (!KeysEqual(&msg->mKey, &mEditorModel->mKey)) return false;
        UpdateNameEditFromModel();
        if (msg->mbShow) mUI->ShowCreatureNameEdit();
        else mUI->HideCreatureNameEdit();
        return false;
    }

    case 0x685309be:
        mpEditorLimits->SetBudget(((MsgBudget*)pMessage)->mBudget);
        return false;

    case 0x33a87f7e: {
        // spawn the "block placed" effect sized to the block's bounding box
        cSPEditorBlock* block = ((MsgBlock*)pMessage)->mpBlock;
        uint32_t effectID = 0;
        GetPropertyAsKeyInstance(mCurrentConfigProperties, 0xd3a86352, &effectID);
        if (!block || !effectID) return false;
        BoundingBox bb;
        block->GetBBox(&bb, 0, 0, 0);
        Vector3 center;
        center.x = (bb.mMin.x + bb.mMax.x) * 0.5f;
        center.y = (bb.mMax.y + bb.mMin.y) * 0.5f;
        float cz = (bb.mMax.z + bb.mMin.z) * 0.5f;
        float scale = sqrtf((bb.mMax.x - bb.mMin.x) * (bb.mMax.x - bb.mMin.x) +
                            (bb.mMax.y - bb.mMin.y) * (bb.mMax.y - bb.mMin.y) +
                            (bb.mMax.z - bb.mMin.z) * (bb.mMax.z - bb.mMin.z)) * 0.1f;
        center.z = cz - scale * 2.0f;
        XformMsg xform;
        xform.SetPosition(center);
        xform.SetScale(scale);
        GetEditorEffectsWorld()->SetEffectTransform(effectID, 1, &xform, block);
        return false;
    }

    case 0x14418c3f: {
        MsgModel* msg = (MsgModel*)pMessage;
        if (msg->mpModel != mEditorModel) return false;
        mbModelChanged = true;
        mUI->UpdateUIBasedOnModelSaveability();
        cEditorModelMessage out;
        out.mFlags = 0;
        out.mpSender = this;
        out.mValue = msg->mValue;
        MessageServer()->PostMSG(0x14418c3f, &out, 0);
        return true;
    }

    case 0x7aa519dc: {
        MsgModel* msg = (MsgModel*)pMessage;
        if (msg->mpModel != mEditorModel) return false;
        uint32_t value = msg->mValue;
        gBakeManager->Invalidate(value);
        UpdateModelValidity(value, &mModelValidity);
        mbModelChanged = true;
        if (mUI) mUI->UpdateUIBasedOnModelSaveability();
        cEditorModelMessage out;
        out.mFlags = 0;
        out.mpSender = this;
        out.mValue = value;
        MessageServer()->PostMSG(0x7aa519dc, &out, 0);
        return true;
    }

    case 0x90a03fdf: {
        MsgBrain* msg = (MsgBrain*)pMessage;
        mpEditorLimits->SetBrainLevel(0, msg->mBrainLevel);
        InitBrain(msg->mInitLevel);
        cEditorLaunchData* launch = mLaunchData;
        if (launch && launch->mbHasBrain) SetupBrainFromLaunchData();
        InitializeUndoList();
        return false;
    }

    case 0x7f18f481: {
        // a block is being removed: drop every reference to it
        cSPEditorBlock* block = ((MsgBlock*)pMessage)->mpBlock;
        if (block == mRolloverBlock) SetRolloverBlock(0, -1);
        if (block == mToBeSelectedBlock) mToBeSelectedBlock.Clear();
        if (block == mSelectedBlock) SetSelectedBlock(0, true);
        return false;
    }

    case 0x90e08f60: {
        // paint a region with a color (or a whole paint theme)
        MsgPaint* msg = (MsgPaint*)pMessage;
        Vector3 color;
        ColorFromRGB(&color, msg->mColor);
        cSPEditorSkinManager* skinMgr = mSkinManager;
        if (skinMgr && skinMgr->GetSkin(1) && mEditorModel) {
            int region = msg->mRegion;
            if (region == -1) region = 0;
            else if (region < 0 || region > 2) goto playSound;
            mEditorModel->SetRegionColor(region, color);
            mbModelPainted = true;
            AddUndoState(false, false);
            cSPEditorModel* model = mEditorModel;
            if (!(mSaveSkinManager && mSaveSkinManager->IsBusy()) && model && mSkinManager)
                mSkinManager->RepaintModel(model);
        } else if (mCurrentPaintTheme && mEditorModel && msg->mRegion != -1) {
            int region = msg->mRegion;
            bool useTheme = msg->mbTheme != 0;
            if (useTheme) {
                cCategoryInfo info;
                mpPaintPaletteUI->GetCategoryInfo(&info);
                if (info.mPropID) {
                    AutoRefCount<cSPEditorPaintTheme> theme(new ("Editor", 0, 0, 0, 0) cSPEditorPaintTheme());
                    theme->SetSource(mSaveExtension);
                    theme->ReadFromProp(info.mPropID);
                    theme->WriteToProp(mEditorModel, region);
                    mbModelPainted = true;
                }
            } else {
                mCurrentPaintTheme->SetRegionColor(color, region);
                mCurrentPaintTheme->WriteToProp(mEditorModel, region);
                mbModelPainted = true;
            }
            AddUndoState(true, false);
        }
    playSound:
        PlayEditorSound(0x1d6253c0, 0x717e837a, color.y * 2.0f + color.x + color.z * 4.0f, 0);
        PlayUISound(0x2570ae6d);
        return false;
    }

    case 0xb03bc30c: {
        mLaunchData = (cEditorLaunchData*)pMessage;
        if (mbPreserveLineage) {
            mParentModelKey = mLaunchData->mKey;
        } else {
            mParentModelKey.instanceID = 0;
            mParentModelKey.typeID = 0;
            mParentModelKey.groupID = 0;
        }
        IWindow* mainWin = WindowManager()->GetMainWindow();
        mnModelStartTime = static_cast<cSPUIMainWin*>(mainWin)->GetMouseRefs();
        return false;
    }

    case 0xb2e18705: {
        MsgPaletteItem* msg = (MsgPaletteItem*)pMessage;
        if (msg->mpItem) return HandlePaletteItemTriggerMessage(msg->mpItem->Cast(0x72d44e3a), msg->mID);
        return HandlePaletteItemTriggerMessage(0, msg->mID);
    }

    case 0xd1511790: {
        MsgAnimEvent* msg = (MsgAnimEvent*)pMessage;
        if (mTransitionState == 1) return false;
        if (!mIsActive) return false;
        if (msg->mpModel && msg->mpModel != mEditorModel) return false;
        if (HandleAnimEvent(msg->mID)) {
            PlayAnimEvent((cEditorAnimEvent*)msg);
            return true;
        }
        mpAnimEvent = (cEditorAnimEvent*)msg;
        return true;
    }

    case 0xf058b0f2: {
        // money earned/spent: float a "+<amount>" effect at the given world point
        MsgMoney* msg = (MsgMoney*)pMessage;
        Vector3 pos;
        pos.x = msg->x;
        pos.y = msg->y;
        pos.z = msg->z;
        uint32_t amount = msg->mAmount;
        float height = 0.5f;
        uint32_t effectID = 0;
        GetFloatProperty(mCurrentConfigProperties, 0xb3a88b0b, &height);
        if (amount == 0) return false;
        if (!GetPropertyAsKeyInstance(mCurrentConfigProperties, 0xd3a86351, &effectID)) return false;
        GetEditorEffectsWorld()->StopEffect(0x3f1bf52, 0);

        Vector3 camPos, camDir;
        App()->GetViewer()->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
        Plane plane;
        plane.n.x = -camDir.x;
        plane.n.y = -camDir.y;
        plane.n.z = -camDir.z;
        Vector3 p;
        p.x = camPos.x + height * camDir.x;
        p.y = camPos.y + camDir.y * height;
        p.z = camPos.z + camDir.z * height;
        plane.d = -(p.x * plane.n.x + p.z * plane.n.z + p.y * plane.n.y);

        Vector3 rayOrigin, rayDir;
        App()->GetViewer()->GetCameraRayOrigin(&rayOrigin, &rayDir);
        Vector3 toPoint;
        toPoint.x = pos.x - rayOrigin.x;
        toPoint.y = pos.y - rayOrigin.y;
        toPoint.z = pos.z - rayOrigin.z;
        Vector3 normalized;
        rayDir = *Vector3_Normalize(&normalized, &toPoint);
        float t;
        if (IntersectRayPlane(&rayOrigin, &rayDir, &plane, &t)) {
            AutoRefCount<IVisualEffect> effect;
            EffectsManager()->CreateVisualEffect(0xa0b518b8, 0, effect.AsPPTypeParam());
            if (effect) {
                XformMsg xform;
                xform.SetPosition(pos);
                effect->SetTransform(xform);
                wchar_t moneyText[40];
                wchar_t currency[2];
                moneyText[0] = 0;
                currency[1] = 0;
                currency[0] = mCurrencyChar;
                SetMoneyString((double)amount, moneyText, 40, L"%-F%-p", currency);
                moneyText[39] = 0;
                AutoRefCount<cEffectText> text(new ("Editor", 0, 0, 0, 0) cEffectText());
                cEffectText* t2 = text;
                WStr_Format(&t2->mText, L"%lc%ls", L'+', moneyText);
                effect->SetParam(8, t2);
                effect->Start(0);
            }
        }
        mpEditorLimits->AddCost(0, amount);
        return false;
    }

    case 0xf1ff568b: {
        MsgKeyReplace* msg = (MsgKeyReplace*)pMessage;
        if (!msg->mbReplace) return false;
        if (!KeysEqual(&msg->mKey, &mEditorModel->mKey)) return false;
        msg->mNewKey.instanceID = 0xa6c97621;
        msg->mNewKey.typeID = 0xb1b104;
        msg->mNewKey.groupID = 0x490f6945;
        msg->mbReplace = false;
        return false;
    }
    }
    return false;
}

}  // namespace SP
