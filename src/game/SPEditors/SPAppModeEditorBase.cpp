// src/game/SPEditors/SPAppModeEditorBase.cpp -- migrated from slice(s) s0058cee0, s0058ba60, s0058ac10, s005816f0, s005810d0, s0057f420, s005b94b0, s00591fa0, s0058d430, s0058be50, s00589ce0, s00587a20, s00586b00, s00585d40, s00585330, s00583c50, s00582fe0, s00582250, s005802f0, s0057f6c0, s0057e480, s0057d710, s0057bfb0, s0057af00, s0057ae10, s00579e20, s005794b0, s00577130, s00576140, s00575270, s005744b0, s00573520, s00572580, s005718f0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAppModeEditorBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_renderStateDirty;   // rw::graphics::GlobalState::m_renderStateDirty[0]
extern uint32_t g_cullMode;           // 0x16f923c
extern uint32_t g_value74, g_value78, g_value7c, g_value80, g_value84, g_value88;
#include <new>
#include <string.h>
#include <math.h>
#include <intrin.h>
// Retail computes this sqrt with an inline x87 fsqrt, not a _CIsqrt call.
#pragma intrinsic(sqrt)
static inline float InlineSqrt(float x) { return (float)sqrt((double)x); }
#include "EA/Audio/FactoryBinarySampleData.h"
#include <ctype.h>
#include "SP/cIModelWorld.h"
#include "SP/cILightingWorld.h"
#include "SP/cAppModeEditorBase.h"
#include "SP/cSPEditorBlock.h"
#include "SP/cSPEditorAnimatedEventInfo.h"
#include "SP/cSPEditorHandle.h"
#include "SP/cViewer.h"
#include "SP/cSPEditorHandleDeform.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Variant.h"
#include "SP/cCameraManager.h"
#include "SP/cCreatureCameraBase.h"
#include "SP/cIApp.h"
#include "SP/cDirectPropertyList.h"
#include "SP/cModelManager.h"
#include "SP/cPropertyList.h"
#include "SP/cSPEditorAnimatedCreatureManager.h"
#include "SP/cSPEditorBudget.h"
#include "SP/cSPEditorModel.h"
#include "SP/cSPEditorResourceFactory.h"
#include "SP/cSPEditorUI.h"
#include "SP/cSPPaletteUI.h"
#include "SP/cSPPlayMode.h"
#include "SP/cSPPlayModeUI.h"
#include "cIHintProcessor.h"
#include "EA/ArgScript/cCommandBase.h"
#include "EA/ArgScript/cArguments.h"
#include "cSPTransform.h"
#include "EA/Audio/IPrimitive.h"
#include "SP/cMWModel.h"
#include "SP/cSPEditorSkinManager.h"
#include "EA/ArgScript/cIParser.h"
#include "SP/cEditorResource.h"
#include "SP/cEditorsTokenTranslator.h"
#include "SP/cISPEditorNameProvider.h"
#include "EA/ResourceMan/Database.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cCity.h"
#include "SP/cSkinObject.h"
#include "nSPSkinner/cVertexWeights.h"
#include "SP/cString.h"
#include "SP/cSPEditorLimbStructure.h"
#include "SP/cLocalInputState.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/Audio/cSystem.h"
#include "SP/cIAppMode.h"
#include "EA/Audio/Sound.h"
#include "SP/cSPEditorComplexityMeter.h"
#include "SP/cSPEditorNaming.h"
#include "SP/cSPEditorPaintTheme.h"
#include "SP/cSPEditorSpine.h"
#include "SP/cSPPalette.h"
#include "SP/cSPVerbTrayCollection.h"
#include "EA/IO/FileStream.h"
#include "EA/Stopwatch.h"
#include "cSPVector3.h"
#include "SP/cIPropertyManager.h"
#include "SP/cLightingWorld.h"
#include "SP/cRenderer.h"
#include "cSPBoundingBox.h"
#include "EA/Trace/ILogFilter.h"
#include "SP/cSPEditorPhysicsWorld.h"
#include "SP/cSPEditorSellBackDetachedRollover.h"
#include "SP/cSPEditorSellBackRollover.h"
#include "SP/cShadowWorld.h"
#include "SP/cSpeciesProfile.h"
#include "EA/Swarm/cIVisualEffect.h"
#include "EA/ResourceMan/Resource.h"
#include "EA/Swarm/cTransform.h"
#include "SP/cILayer.h"
#include "EA/Messaging/IHandlerRC.h"
#include "SP/cTexturePreload.h"

// ---- items of slice s005718f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
namespace EA {
namespace Audio {
struct SystemAT {
    PV8 PV4 PV2
    virtual void BeginMessage(uint32_t id);                 // +0x38
    virtual void SetFloat(uint32_t id, float v);            // +0x3c
    virtual void SetInt(uint32_t id, uint32_t v);           // +0x40
    virtual void pv41();
    virtual void pv42();
    virtual void SetString(uint32_t id, const char* s, uint32_t len);   // +0x4c
    virtual void pv44();
    virtual void pv45();
    virtual void SendMessage();                             // +0x58
};
}
}
namespace EA {
namespace Audio {
SystemAT* __cdecl GetSystemAT();
}
}
extern uint32_t g_renderStateDirty;   // rw::graphics::GlobalState::m_renderStateDirty[0]
extern uint32_t g_cullMode;           // 0x16f923c
extern uint32_t g_value74, g_value78, g_value7c, g_value80, g_value84, g_value88;
struct Vec4 { float x, y, z, w; };
extern Vec4 g_defaultColor;   // 0x15dac10
struct ColorSource {
    char pad0[0x48];
    Vec4 mColor;     // +0x48
    Vec4 GetDefaultColor() const;
    Vec4 GetColor() const;
};
struct Rect16 { uint32_t d[4]; };
int __cdecl ClassifyRects(Rect16 a, Rect16 b);    // 0x4f3b40
uint32_t __cdecl RectResultToId(int r);           // 0x4f3c40
struct cUIManager {
    void Show(uint32_t id);                       // 0x67c830
    void SetMode(int a, int b);                   // 0x67c420
};
cUIManager* __cdecl UIManager();                  // 0x67cac0
struct cItem { void Update(); };                  // 0x436060
struct cItemList {
    int GetCount();                               // 0x4accf0
    cItem* GetAt(int i);                          // 0x4accb0
};
namespace SP {
struct cCursor { void SetState(int); };         // 0x43ea40
}
namespace SP {
struct cAppModeEditorBase_s0057_18f0 {
    char pad0[0x28];
    float mX;                    // +0x28
    float mY;                    // +0x2c
    char pad30[0x20e - 0x30];
    bool mbPlaySounds;           // +0x20e
    char pad20f[0x214 - 0x20f];
    uint32_t mTutorialPartMode;  // +0x214
    uint32_t mTutorialPlayMode;  // +0x218
    uint32_t mTutorialPaintMode; // +0x21c
    char pad220[0x260 - 0x220];
    uint64_t mRange1;            // +0x260
    uint64_t mRange2;            // +0x268
    uint64_t mRange0;            // +0x270
    char pad278[0x31c - 0x278];
    int mEditorMode;             // +0x31c
    char pad320[0x34c - 0x320];
    uint32_t mCurrentBlockRegion;   // +0x34c
    char pad350[0x385 - 0x350];
    bool mbCursorSet;            // +0x385
    char pad386[0x480 - 0x386];
    float mSavedX;               // +0x480
    float mSavedY;               // +0x484
    char pad488[0x4d4 - 0x488];
    bool mbFading;               // +0x4d4

    void ShowTutorial();  // 0x00572260 (SP::cAppModeEditorBase::ShowTutorial)
    void InitBrain(uint32_t region);  // 0x005722f0 (SP::cAppModeEditorBase::InitBrain)
    void OnCursor(cCursor* c);
    void PostDone(void* data);
    void SetRanges(const uint64_t& r0, const uint64_t& r1, const uint64_t& r2);
    void StopFade();
};
}
namespace SP {
namespace EditorUtils {
 void PlayEditorSound(uint32_t a, uint32_t b, float v, int c); 
}
}
// ---- items of slice s005718f0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vec4 g_defaultColor;   // 0x15dac10

// ---- items of slice s00572580 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV16 PV8 PV8
struct IStream_s0057_2580;
namespace EA {
namespace IO {
uint32_t __cdecl WriteUint32(IStream_s0057_2580* s, const uint32_t* p, uint32_t n, int endian);
}
}
struct IStreamHolder {
    PV4 PV2
    virtual IStream_s0057_2580* GetStream();     // +0x18
};
struct ISerializer {
    PV8
    virtual IStreamHolder* GetHolder();   // +0x20
};
inline uint32_t WriteUint32(IStream_s0057_2580* st, uint32_t v) { return EA::IO::WriteUint32(st, &v, 1, 0); }
inline wchar_t ToLower16(wchar_t c)
{
    if (c <= 0xff)
        return (wchar_t)tolower((uint8_t)c);
    return c;
}
struct Vec3 { float x, y, z; };
struct VecPair {
    Vec3 mA;
    Vec3 mB;
    inline VecPair& operator=(const VecPair& o) {
        mB = o.mB;
        mA = o.mA;
        return *this;
    }
};
namespace EA {
namespace Random {
class RandomLinearCongruential_s0057_2580 {
public:
    uint32_t mnSeed;
    double RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
extern EA::Random::RandomLinearCongruential_s0057_2580 sMathRandom;
inline float RandomRangeInline(float a, float b)
{
    const double lo = a;
    const double hi = b;
    const double r = sMathRandom.RandomDoubleUniform();
    const double d = lo + (hi - lo) * r;
    if (d >= hi)
        return (float)hi;
    if (d < lo)
        return (float)lo;
    return (float)d;
}
namespace EA {
namespace Messaging {
struct IHandler_s0057_2580;
}
}
namespace EA {
namespace Messaging {
struct IServer;
}
}
namespace EA {
namespace Messaging {
bool RemoveHandler(IServer* server, IHandler_s0057_2580* handler, const uint32_t* ids, uint32_t count, int priority);
}
}
namespace EA {
namespace Messaging {
struct HandlerRegistration {
    IServer* mpServer;
    IHandler_s0057_2580* mpHandler;
    const uint32_t* mpIds;
    uint32_t mnCount;
    int mnPriority;
    void Unregister();
};
}
}
namespace Simulator {
class cThemeMusicManagerBase {
public:
    cThemeMusicManagerBase() : mField04(0) {}
    virtual ~cThemeMusicManagerBase();
    uint32_t mField04;
};
}
namespace Simulator {
class cThemeMusicManager : public cThemeMusicManagerBase {
public:
    cThemeMusicManager();
    virtual ~cThemeMusicManager();
    uint32_t mField08;
    uint32_t mField0C;
    uint32_t mField10;
    bool mbField14;
    bool mbField15;
    uint32_t mField18;
    uint32_t mField1C;
    uint32_t mField20;
    uint32_t mField24;
    uint32_t mField28;
};
}
struct ComplexityEntry {      // 0x8c bytes
    int mCost;                // +0x00
    uint32_t pad04[3];
    int mBakeCost;            // +0x10
    uint32_t pad14[(0x8c - 0x14) / 4];
};
struct EntryVector {
    ComplexityEntry* mpBegin;
    ComplexityEntry* mpEnd;
    int size() const { return mpEnd - mpBegin; }
    const ComplexityEntry& operator[](int i) const { return mpBegin[i]; }
};
struct ComplexityBlock {
    char pad0[0x1c];
    EntryVector mEntries;         // +0x1c
    int GetEntryCount();
};
struct BlockPtrVector {
    ComplexityBlock** mpBegin;
    ComplexityBlock** mpEnd;
    ComplexityBlock** mpCapacity;
    int size() const { return mpEnd - mpBegin; }
    ComplexityBlock* operator[](int i) const { return mpBegin[i]; }
    int GetSize();
};
template <typename T> inline const T& max_alt(const T& a, const T& b) { return (a < b) ? b : a; }
namespace EA {
namespace Hash {
 uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int lowercase); 
}
}
struct cEditorLimitsCheat {
    const char* GetDescription(int mode) const;
};
struct Vector2 { float x, y; };
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Point3 { float x, y, z; };
extern const Vector3 kDefaultNormal;   // 0x15e5024
struct CollisionFilter {
    uint32_t mTypes[2];
    uint32_t mA, mB, mC;
    uint8_t mMode;
    bool mbFlag;
    CollisionFilter() { mTypes[0] = 0; mTypes[1] = 0; mA = 0; mB = 0; mC = 0; mbFlag = false; }
    void SetType(uint32_t i) { if (i < 64) mTypes[i >> 5] |= 1u << (i & 31); }
};
struct ICollider {
    PV8 PV
    virtual int Raycast(const Vector3* start, const Vector3* end, int a, Vector3* hit, Vector3* normal,
                        CollisionFilter* filter, int b, int c);   // +0x24
};
struct IModelManager {
    PV8 PV2
    virtual uint32_t GetTypeIndex(uint32_t id, int flags);   // +0x28
};
struct cCreature { void SetVisible(int); };      // 0xa04a90
namespace SP {
IModelManager* ModelManager();
}
namespace SP {
struct cSPPlayMode_s0057_2580 { float GetHeightOffset(); };
}
namespace SP {
struct cCreatureStructure { char pad0[0x2c]; Point3 mOffset; };
}
namespace SP {
struct cSPEditorAnimatedCreatureManager_s0057_2580 {
    cCreatureStructure* GetCreatureStructure(uint32_t id);  // 0x0059cac0 (SP::cSPEditorAnimatedCreatureManager::GetCreatureStructure)
    ::cCreature* GetCreature(uint32_t id);  // 0x0059ca70 (SP::cSPEditorAnimatedCreatureManager::GetCreature)
};
}
struct cEditorGround {
    char pad0[0x7c];
    SP::cSPPlayMode_s0057_2580* mpPlayMode;     // +0x7c
    char pad80[4];
    ICollider* mpCollider84;         // +0x84
    char pad88[4];
    ICollider* mpCollider8C;         // +0x8c
    char pad90[0x31c - 0x90];
    int mEditorMode;                 // +0x31c
    char pad320[0x360 - 0x320];
    SP::cSPEditorAnimatedCreatureManager_s0057_2580* mpCreatureMgr;   // +0x360
    uint32_t mCreatureId;            // +0x364
};
struct cLimitsData { char pad0[0x34]; bool mbAllow; char pad35[0x6f - 0x35]; bool mbCheckLimits; };
struct cEditorModel { char pad0[0xc]; uint32_t mKey; };
struct cPropertyList_s0057_2580 { bool GetBool(uint32_t id); };
extern cPropertyList_s0057_2580* sAppProperties;
bool __cdecl IsKeyDown(int a, int b);            // 0x8d3200
bool __cdecl IsSpecialKey(const void* key);      // 0x5bf0a0
bool __cdecl IsModelLocked(void* model);         // 0x4a0ac0
uint32_t __cdecl RemapTypeId(uint32_t type);     // 0x432f10
struct ResourceKeyRec { uint32_t pad0[2]; uint32_t mKey8; uint32_t mGroupC; uint32_t pad10[2]; uint32_t mModelType; };
bool __cdecl HasProperty(const ResourceKeyRec* rec, uint32_t id, int flags);   // 0x5580e0
struct IWindowManager {
    PV16 PV16 PV
    virtual int IsModal();                        // +0x84
};
namespace SP {
 IWindowManager* WindowManager(); 
}
struct cCursorMgr {
    uint32_t GetCursor();        // 0x8013c0
    void SetCursor(uint32_t id); // 0x801bb0
};
cCursorMgr* __cdecl CursorManager();   // 0x67cab0
struct cUIManager_s0057_2580 { void Show(uint32_t id); };
cUIManager_s0057_2580* __cdecl UIManager_s0057_2580();       // 0x67cac0
struct cPaletteUI { bool IsActive(); };    // 0x5dc450
struct cUndoMgr { bool HasPending(); };    // 0x4c58b0
struct cSymmetry { bool IsReady(); };      // 0x5ca920
struct IRelease {
    PV
    virtual void Release();      // +0x04
};
struct cEditor {
    virtual void v00();
    char pad04[0x3c - 4];
    uint32_t mStateFlags;            // +0x3c
    char pad40[4];
    int mSymmetryMode;               // +0x44
    char pad48[0x78 - 0x48];
    cPaletteUI* mpPalette;           // +0x78
    char pad7c[0x98 - 0x7c];
    cEditorModel* mpModel;           // +0x98
    char pad9c[0x150 - 0x9c];
    cUndoMgr* mpUndo;                // +0x150
    char pad154[0x1cc - 0x154];
    cLimitsData* mpLimits;           // +0x1cc
    char pad1d0[0x2a8 - 0x1d0];
    uint32_t mGroup;                 // +0x2a8
    char pad2ac[0x2f6 - 0x2ac];
    bool mbLimitsDisabled;           // +0x2f6
    char pad2f7[0x308 - 0x2f7];
    IRelease* mpRef308;              // +0x308
    IRelease* mpRef30C;              // +0x30c
    char pad310[0x360 - 0x310];
    SP::cSPEditorAnimatedCreatureManager_s0057_2580* mpCreatureMgr;   // +0x360
    uint32_t mCreatureId;            // +0x364
    char pad368[0x3c4 - 0x368];
    cSymmetry* mpSymmetry;           // +0x3c4
    char pad3c8[0x4d4 - 0x3c8];
    bool mbFading;                   // +0x4d4

    virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16();
    virtual int GetEditorConfig();   // +0x44

    bool IsLimitAllowed();
    bool CanUseModel(const ResourceKeyRec* rec);
    void ReleaseRefs();
    void HideCreature();
    void ShowCreature();
    void UpdateCursor();
    void SetSymmetryMode(int mode);
};
// ---- items of slice s00572580 end

// ---- items of slice s00573520 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);
namespace EA {
namespace Random {
class RandomLinearCongruential_s0057_3520 {
public:
    uint32_t mnSeed;
    uint32_t RandomUint32Uniform(uint32_t n);  // 0x00a68fb0 (EA::Random::RandomLinearCongruential::RandomUint32Uniform)
    double RandomDoubleUniform();  // 0x009360d0 (EA::Random::RandomLinearCongruential::RandomDoubleUniform)
};
}
}
namespace EA {
class Stopwatch_s0057_3520 {
public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    void Restart();  // 0x00571e80 (EA::Stopwatch::Restart)
};
}
extern EA::Random::RandomLinearCongruential_s0057_3520 sMathRandom_s0057_3520;
template <typename It, typename T> inline It find_u(It first, It last, const T& v) { for (; first != last; ++first) if (*first == v) break; return first; }
inline float RandomRangeClamped(float a, float b)
{
    const double lo = a;
    const double hi = b;
    double d = lo + (hi - lo) * sMathRandom_s0057_3520.RandomDoubleUniform();
    if (d >= hi)
        d = hi;
    else if (d < lo)
        d = lo;
    return (float)d;
}
struct Vector3_s0057_3520 {
    float x, y, z;
    Vector3_s0057_3520() {}
    Vector3_s0057_3520(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s0057_3520(const Vector3_s0057_3520& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3_s0057_3520 operator+(const Vector3_s0057_3520& o) const { return Vector3_s0057_3520(x + o.x, y + o.y, z + o.z); }
    Vector3_s0057_3520 operator-(const Vector3_s0057_3520& o) const { return Vector3_s0057_3520(x - o.x, y - o.y, z - o.z); }
    Vector3_s0057_3520 operator*(float s) const { return Vector3_s0057_3520(x * s, y * s, z * s); }
};
inline Vector3_s0057_3520 operator*(float s, const Vector3_s0057_3520& v) { return Vector3_s0057_3520(s * v.x, s * v.y, s * v.z); }
struct BoundingBox { Vector3_s0057_3520 mMin; Vector3_s0057_3520 mMax; };
struct RectF {
    float mLeft, mTop, mRight, mBottom;
    RectF(const RectF& r) : mLeft(r.mLeft), mTop(r.mTop), mRight(r.mRight), mBottom(r.mBottom) {}
};
struct ICollider_s0057_3520 {
    PV8 PV
    virtual int Raycast(const Vector3_s0057_3520* start, const Vector3_s0057_3520* end, int a, Vector3_s0057_3520* hit, Vector3_s0057_3520* normal,
                        CollisionFilter* filter, int b, int c);   // +0x24
};
struct IObject {
    virtual void* Cast(uint32_t id);   // +0x00
    virtual int AddRef();              // +0x04
    virtual int Release();             // +0x08
};
struct IRefCount {
    virtual int AddRef();     // +0x00
    virtual int Release();    // +0x04
};
template <typename T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
namespace SP {
struct cEditorBlock;
}
namespace SP {
struct cSPEditorAnimatedEventInfo_s0057_3520 : IObject {
    uint32_t mData[11];
    cSPEditorAnimatedEventInfo_s0057_3520();     // 0x59d960
    void MessagePost(uint32_t id, int a, int b, uint32_t target, int c, float scale, int d, int e, float f);  // 0x0059d840 (SP::cSPEditorAnimatedEventInfo::MessagePost)
};
}
namespace SP {
class cSPEditorVehicleAbilities : public IObject { public:
    struct Key { uint32_t a, b, c; };
    uint32_t mData[24];
    cSPEditorVehicleAbilities(Key key, uint32_t type, uint32_t id, int a, int b);
};
}
namespace SP {
struct cBlockFlags {
    uint32_t mValue;
    inline bool Get(int n) const { return ((mValue >> n) & 1) != 0; }
};
}
namespace SP {
struct cEditorBlock : IObject {
    char pad4[0x3ec - 4];
    struct cSPEditorHandle_s0057_3520* mpHandle;     // +0x3ec
    char pad3f0[0xdc8 - 0x3f0];
    cBlockFlags mFlags;                    // +0xdc8

    bool CanShowAbilities();               // 0x44c030
    void GetKey(cSPEditorVehicleAbilities::Key* key, int a, int b);   // 0x438f20
    const BoundingBox& GetBBox(BoundingBox* tmp, int a, int b, int c); // 0x44ae00
    void SetSelected(int);                 // 0x43a830
    void OnDeselect();                     // 0x43e2b0
    uint32_t GetHandleIndex(struct cSPEditorHandle_s0057_3520* h);   // 0x43c3d0
    void SetHandleState(uint32_t idx, int a);             // 0x43e7e0
    void SetActiveHandle(uint32_t idx);                   // 0x43e760
};
}
namespace SP {
struct cSPEditorHandle_s0057_3520 {
    virtual int AddRef();                         // +0x00
    virtual int Release();                        // +0x04 0x0051e380
    PV
    virtual cSPEditorHandle_s0057_3520* Cast(uint32_t id);   // +0x0c
    virtual uint32_t GetType();                   // +0x10
    PV4 PV2 PV
    virtual void SetState(int state, int b);      // +0x30
    cEditorBlock* GetBlock();                     // 0x47e6c0
    int IsLocked();                               // 0x47ec20
};
}
namespace SP {
struct cSPEditorHandleDeform_s0057_3520 : cSPEditorHandle_s0057_3520 {};
}
namespace SP {
struct cSPUIPropertyLayout {
    void Setup(cSPEditorVehicleAbilities::Key* key, IObject* abilities, struct IOwner* owner, int a, int b, int c);   // 0x5ed750
    void SetMode(int m);                          // 0x5ed320
    void SetPositionAndOffset(float x, float y, float w, float h);
    void Hide();                                  // 0x5ed6c0
};
}
namespace SP {
struct cPropertyLayoutMgr { cSPUIPropertyLayout* GetLayout(); };   // 0x801920
}
namespace SP {
cPropertyLayoutMgr* PropertyLayoutMgr();                          // 0x401020
}
namespace SP {
struct IWindow {
    PV8 PV4 PV
    virtual const RectF& GetArea();               // +0x34
};
}
namespace SP {
struct IWindowManager_s0057_3520 {
    PV
    virtual IWindow* GetMainWindow();             // +0x04
};
}
namespace SP {
IWindowManager_s0057_3520* WindowManager_s0057_3520();
}
namespace SP {
struct cViewer_s0057_3520 { void ScreenToWorld(float x, float y, Vector3_s0057_3520* nearPt, Vector3_s0057_3520* farPt); };   // 0x7c4510
}
namespace SP {
struct IApp {
    PV16 PV4 PV2
    virtual cViewer_s0057_3520* GetViewer();                 // +0x58
};
}
namespace SP {
IApp* App();
}
namespace SP {
struct IMessageServer;
}
namespace SP {
struct IMessageListener { virtual bool HandleMessage(uint32_t id, void* msg); };
}
namespace SP {
struct IMessageServer {
    PV4 PV
    virtual void PostMSG(uint32_t id, void* data, int flags);   // +0x14
    PV2 PV
    virtual void AddHandler(IMessageListener* h, uint32_t id);   // +0x24
};
}
namespace SP {
IMessageServer* MessageServer();
}
namespace SP {
struct HandlerRegistration_s0057_3520 {
    IMessageServer* mpServer;
    IMessageListener* mpHandler;
    const uint32_t* mpIds;
    uint32_t mnCount;
    int mnPriority;
    inline void Register(IMessageServer* server, IMessageListener* handler, const uint32_t* ids, uint32_t count) {
        mpServer = server;
        mpHandler = handler;
        mpIds = ids;
        mnCount = count;
        mnPriority = 0;
        if (server && handler)
            for (uint32_t i = 0; i < count; ++i)
                server->AddHandler(handler, ids[i]);
    }
};
}
namespace SP {
struct IPlayMode {
    PV4 PV2
    virtual bool OnMouseMove(float x, float y, uint32_t state);   // +0x18
};
}
namespace SP {
struct ISkinManager {
    PV4 PV2 PV
    virtual bool OnMouseMove(float x, float y, uint32_t state);   // +0x1c
    PV2
    virtual cEditorBlock* GetBlock();                             // +0x28
};
}
namespace SP {
struct IOwner {
    PV
    virtual uint32_t GetId(int);                                  // +0x04
    virtual void SetKey(cSPEditorVehicleAbilities::Key* key);     // +0x08
};
}
namespace SP {
struct IAppModeCheck {
    PV8 PV
    virtual bool IsActive();                                      // +0x24
};
}
namespace SP {
IAppModeCheck* GameModeCheck();                                   // 0x607a60
}
namespace SP {
struct cPaletteUI_s0057_3520 {
    bool IsActive();                 // 0x5dc450
    void SetVisible(bool b);         // 0x5dd090
    void Refresh(bool b, int c);     // 0x5de690
};
}
namespace SP {
struct cUIManager_s0057_3520 { void SetMode(bool a, int b); };   // 0x67c420
}
namespace SP {
cUIManager_s0057_3520* UIManager_s0057_3520();                             // 0x67cac0
}
namespace SP {
struct cModel { char pad0[0xc]; uint32_t mKey[3]; char pad18[0x58 - 0x18]; uint32_t mType; void SetLocked(bool); void SetDirty(int); };   // 0x4adba0 / 0x4adfc0
}
namespace SP {
struct cPartsPalette { void Refresh(int a, int b); void Update(); };   // 0x43cfc0 / 0x43cad0
}
namespace SP {
struct cBlockRef {
    cEditorBlock* mpObject;
    cBlockRef& operator=(cEditorBlock* p);    // 0x4b09b0
};
}
namespace SP {
struct cHint { void Show(); };              // 0x5cc690
}
namespace SP {
struct cSymmetry_s0057_3520 { bool IsReady(); };       // 0x5ca920
}
namespace SP {
struct cUndo { bool Raycast(int a, Vector3_s0057_3520 origin, Vector3_s0057_3520 dir, Vector3_s0057_3520* hitPos, Vector3_s0057_3520* hitNormal, int b, int c); };   // 0x4c4a30
}
namespace SP {
struct cLimitsData_s0057_3520 { char pad0[0x6d]; bool mbOverLimit; };
}
namespace SP {
struct cAssetMgr { IObject* Find(uint32_t key, int flags); };   // 0x45ae10
}
namespace SP {
cAssetMgr* AssetManager();                                     // 0x401050
}
namespace SP {
struct cRolloverInfo { char pad0[0x144]; uint32_t mId; };
}
namespace SP {
struct cEditorState {
    char pad0[8];
    uint32_t mOwnerId;      // +0x08
    int mEditorMode;        // +0x0c
    uint32_t mRolloverId;   // +0x10
    bool mbFlagA;           // +0x14
    bool mbFlagB;           // +0x15
};
}
namespace SP {
struct EffectEntry;
}
namespace SP {
struct EffectEntry {        // 0x30 bytes
    uint32_t mId;
    float mDelay;           // +0x04
    float mSize;            // +0x08
    char pad0c[0x1a - 0x0c];
    bool mbActive;          // +0x1a
    bool mbScaleA;          // +0x1b
    bool mbScaleB;          // +0x1c
    char pad1d[0x20 - 0x1d];
    float mBaseSize;        // +0x20
    float mScale;           // +0x24
    char pad28[8];
};
}
namespace SP {
bool __cdecl IsSameAssembly(cEditorBlock* a, cEditorBlock* b);   // 0x4a60a0
}
namespace SP {
bool __cdecl IsRootBlock(cEditorBlock* b);                       // 0x4a2060
}
namespace SP {
void __cdecl PlayEditorEvent(uint32_t id);                       // 0x4a88d0
}
namespace SP {
void __cdecl ProjectToScreen(const Vector3_s0057_3520& pt, float& x, float& y);   // 0x4a3760
}
namespace SP {
namespace cSPUISpace {
 void KillSetiEffects(uint32_t id, void* owner); 
}
}
namespace SP {
cSPEditorHandleDeform_s0057_3520* __cdecl interface_cast_deform(AutoRefCount<cSPEditorHandle_s0057_3520>* p);   // 0x572770
}
void __cdecl PostSoundMessage(const void* obj, uint32_t value);   // 0x572020
namespace SP {
struct cAppModeBase0 {
    virtual ~cAppModeBase0();
    char pad04[0xc];
};
}
namespace SP {
class cAppModeEditorBase_s0057_3520 : public cAppModeBase0, public IMessageListener {
public:
    char pad14[0x28 - 0x14];
    float mMouseX;                   // +0x28
    float mMouseY;                   // +0x2c
    uint32_t mMouseState;            // +0x30
    int mMouseButton;                // +0x34
    bool mbMouseMoved;               // +0x38
    char pad39[3];
    uint32_t mStateFlags;            // +0x3c
    char pad40[0x70 - 0x40];
    float mHintTimer;                // +0x70
    char pad74[4];
    cPaletteUI_s0057_3520* mpPalette;           // +0x78
    IPlayMode* mpPlayMode;           // +0x7c
    char pad80[4];
    ICollider_s0057_3520* mpCollider;           // +0x84
    char pad88[0x98 - 0x88];
    cModel* mpModel;                 // +0x98
    char pad9c[0xc0 - 0x9c];
    int mMouseDownX;                 // +0xc0
    int mMouseDownY;                 // +0xc4
    char padc8[4];
    cBlockRef mActiveBlock;          // +0xcc
    cBlockRef mBlockRefD0;           // +0xd0
    cPartsPalette* mpPartsPalette;   // +0xd4
    char padd8[0xe4 - 0xd8];
    cSPEditorHandle_s0057_3520* mpRolloverHandle;   // +0xe4
    char pade8[0xf4 - 0xe8];
    cSPEditorHandle_s0057_3520* mpPendingHandle;    // +0xf4
    char padf8[0x140 - 0xf8];
    bool mbHandleSnap;               // +0x140
    bool mbDeformActive;             // +0x141
    char pad142[0x148 - 0x142];
    ISkinManager* mpSkinManager;     // +0x148
    char pad14c[4];
    cUndo* mpUndo;                   // +0x150
    char pad154[0x1a0 - 0x154];
    int mbHasAsset;                  // +0x1a0
    char pad1a4[0x1cc - 0x1a4];
    cLimitsData_s0057_3520* mpLimits;           // +0x1cc
    char pad1d0[0x20c - 0x1d0];
    uint16_t mLayoutFlags;           // +0x20c
    char pad20e[0x2a0 - 0x20e];
    cRolloverInfo* mpRolloverInfo;   // +0x2a0
    char pad2a4[0x2b3 - 0x2a4];
    bool mbSkipMouseMove;            // +0x2b3
    bool mbClickCandidate;           // +0x2b4
    char pad2b5[0x2f1 - 0x2b5];
    bool mbHideRollover;             // +0x2f1
    char pad2f2[0x31c - 0x2f2];
    int mEditorMode;                 // +0x31c
    uint32_t* mIdsBegin;             // +0x320
    uint32_t* mIdsEnd;               // +0x324
    char pad328[0x36c - 0x328];
    EffectEntry* mEffectsBegin;      // +0x36c
    EffectEntry* mEffectsEnd;        // +0x370
    char pad374[0x385 - 0x374];
    bool mbCursorSet;                // +0x385
    char pad386[0x397 - 0x386];
    bool mbInputLocked;              // +0x397
    bool mbHasActiveBlock;           // +0x398
    char pad399[0x3b0 - 0x399];
    int mActiveHandle;               // +0x3b0
    int mLastHandle;                 // +0x3b4
    char pad3b8[0x3c4 - 0x3b8];
    cSymmetry_s0057_3520* mpSymmetry;           // +0x3c4
    char pad3c8[0x434 - 0x3c8];
    IOwner* mpOwner;                 // +0x434
    char pad438[0x470 - 0x438];
    bool mbModelLocked;              // +0x470
    char pad471[0x498 - 0x471];
    cHint* mpHint;                   // +0x498
    char pad49c[0x4b2 - 0x49c];
    bool mbFlag4B2;                  // +0x4b2
    bool mbFlag4B3;                  // +0x4b3
    char pad4b4[0x5a8 - 0x4b4];
    EA::Stopwatch_s0057_3520 mStopwatch;        // +0x5a8
    char pad5c0[0x5e8 - 0x5c0];
    HandlerRegistration_s0057_3520 mRegistration;   // +0x5e8

    inline void PostDone(void* data) { MessageServer()->PostMSG(0x73e46f6, data, 0); }
    inline void PostModelChanged(cModel* model) { MessageServer()->PostMSG(0x73e46f6, model->mKey, 0); }
    void ShowBlockAbilities(cEditorBlock* block);
    void SetModelLocked(bool locked);
    bool OnMouseMove(float x, float y, uint32_t state);  // 0x005737d0 (SP::cAppModeEditorBase::OnMouseMove)
    bool IsOverLimit();
    void UpdateHint();
    cEditorBlock* GetSelectableBlock();
    bool IsMousedOverModel(float x, float y);  // 0x00573a60 (SP::cAppModeEditorBase::IsMousedOverModel)
    void SetActiveBlock(cEditorBlock* block, int handle);
    void SetRolloverHandle(cSPEditorHandle_s0057_3520* handle, int unused);  // 0x00573d70 (SP::cAppModeEditorBase::SetRolloverHandle)
    void SetAsset(uint32_t key);
    void SetPaletteVisible(bool visible);
    void OnEnter();
    void GetState(cEditorState* state);
    bool HasId(uint32_t id);
    void CreateEffects(uint32_t type, int param, float scale, float bonus);
    bool HasEffect(uint32_t id);
};
}
namespace SP {
static const uint32_t kEditorMessageIds[] = { 0x68cd252 };
}
// ---- items of slice s00573520 end

// ---- items of slice s005744b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable:4035)
struct Vector3_s0057_44b0 {
    float x, y, z;
    Vector3_s0057_44b0() {}
    Vector3_s0057_44b0(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    ResourceKey() : instanceID(0), typeID(0), groupID(0) {}
};
struct BoundingBox_s0057_44b0 { Vector3_s0057_44b0 lower; Vector3_s0057_44b0 upper; };
namespace eastl {
template <size_t N>
class bitset { public:
    uint32_t mWord[(N + 31) / 32];
    bitset() { for (size_t i = 0; i < (N + 31) / 32; ++i) mWord[i] = 0; }
    bitset& set(size_t i) { if (i < N) mWord[i >> 5] |= (uint32_t)1 << (i & 31); return *this; }
};
}
namespace eastl {
template <typename T> inline const T& max(const T& a, const T& b) { return (a < b) ? b : a; }
}
namespace EA {
template <typename T>
struct AutoRefCount_s0057_44b0 {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
namespace Random {
struct RandomLinearCongruential_s0057_44b0 { uint32_t RandomUint32Uniform(uint32_t limit); };
}
}
extern EA::Random::RandomLinearCongruential_s0057_44b0 sMathRandom_s0057_44b0;   // 0x01601760
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
class cPropertyList_s0057_44b0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool GetPropertyAlloc(uint32_t id, Property*& out);          // +0x20
    virtual bool GetProperty(uint32_t id, Property*& out);               // +0x24
    bool GetBool(uint32_t id);                                           // 0x006a25a0
};
}
namespace SP {
extern cPropertyList_s0057_44b0* sAppProperties_s0057_44b0;                                    // 0x015fd918
}
namespace SP {
inline float GetPropertyFloat(cPropertyList_s0057_44b0* list, uint32_t id, float defaultValue)
{
    float value = defaultValue;
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd)
        value = *prop->GetFloat();
    return value;
}
}
namespace SP {
inline float GetPropertyValueFloat(cPropertyList_s0057_44b0* list, uint32_t id, float defaultValue)
{
    float value = defaultValue;
    Property* prop;
    if (list && list->GetProperty(id, prop) && prop->mnType == 0xd)
        value = *prop->GetValueFloat();
    return value;
}
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s0057_44b0* list, uint32_t id, uint32_t* out);                   // 0x006a12a0
}
namespace SP {
bool GetPropertyArrayKey(cPropertyList_s0057_44b0* list, uint32_t id, int* count, ResourceKey** keys);       // 0x006a0ae0
}
namespace SP {
class cPropertyListManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cPropertyList_s0057_44b0* GetPropertyList(uint32_t instanceID, uint32_t groupID);   // +0x58
};
}
namespace SP {
cPropertyListManager* PropManager();                                     // 0x00401010
}
namespace SP {
struct cSPEditorBlock_s0057_44b0 {
    char pad0[0xc];
    cPropertyList_s0057_44b0* mpPropList;      // +0x0c
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
}
namespace SP {
float GetPaintScore(cSPEditorBlock_s0057_44b0* block);                             // 0x004a5c40
}
namespace SP {
struct cSPEditorModel_s0057_44b0 {
    char pad0[0xc];
    ResourceKey mKey;               // +0x0c
    int GetBlockCount();                                                // 0x004accf0
    cSPEditorBlock_s0057_44b0* GetBlock(int i);                                    // 0x004accb0
    void GetComplexity(int* blocks, int* legs, int* colors, float* cost, int* bones);   // 0x004acd20
    void GetBoundingBox(BoundingBox_s0057_44b0* box, int flags);                   // 0x004ad550
};
}
namespace SP {
namespace EditorUtils {
 bool GetCreatorType(const ResourceKey* key);   // 0x00641900
}
}
namespace SP {
class cViewer_s0057_44b0 {
public:
    void GetCameraLocationInfo(Vector3_s0057_44b0* pos, Vector3_s0057_44b0* dir, int a, int b);   // 0x007c3d30
    void GetCameraTransform(Vector3_s0057_44b0* a, Vector3_s0057_44b0* b);                         // 0x007c4900
};
}
namespace SP {
class cCameraManager_s0057_44b0;
}
namespace SP {
class cCameraList {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual class cCreatureCameraBase_s0057_44b0* GetCamera(uint32_t id);              // +0x0c
    void GetCameraValues(float* a, float* b, float* c, Vector3_s0057_44b0* v);        // 0x005a2260
};
}
namespace SP {
class cCreatureCameraBase_s0057_44b0 {
public:
    void SetCreature(void* creature);                                       // 0x00627060
    void SetInitialCameraValues(float a, float b, float c, const Vector3_s0057_44b0& v); // 0x00626b50
    void SetCallback(void (*cb)(void*), void* data);                         // 0x00625350
};
}
namespace SP {
class cCameraManager_s0057_44b0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual void SetActiveCameraID(uint32_t id);                            // +0x34
    virtual cCameraList* GetCameras();                                      // +0x38
};
}
namespace SP {
class cIApp_s0057_44b0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual cCameraManager_s0057_44b0* GetCameraManager();                             // +0x50
    virtual void v54();
    virtual cViewer_s0057_44b0* GetViewer();                                           // +0x58
};
}
namespace SP {
cIApp_s0057_44b0* App_s0057_44b0();                                                               // 0x0067dd10
}
namespace SP {
class cIModelWorld_s0057_44b0 {
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
}
namespace SP {
class cModelManager_s0057_44b0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual uint32_t GetModelGroup(uint32_t id, int create);                 // +0x28
};
}
namespace SP {
cModelManager_s0057_44b0* ModelManager_s0057_44b0();                                              // 0x0067dd80
}
namespace SP {
class cSPEditorResourceFactory_s0057_44b0 { public: int Flush(bool b); };              // 0x004c49e0
}
namespace SP {
class cSPEditorAnimatedCreatureManager_s0057_44b0 { public: void* GetCreature(cViewer_s0057_44b0* viewer); };   // 0x0059ca70
}
namespace SP {
class cEditorLaunchData { public: char pad[0x1c]; int mSelectedIndex; };
}
namespace SP {
class cSPEditorBudget_s0057_44b0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual void SetRemaining(int type, int amount);                         // +0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void PurchaseBlock(cSPEditorBlock_s0057_44b0* block, int flags);            // +0x38
};
}
namespace SP {
class cSPEditorUIPanel { public: bool IsActive(); };                         // 0x005ca920
}
namespace SP {
class cSPEditorUI_s0057_44b0 {
public:
    char GetMode();                                                          // 0x005dc450
    void SetModeEnabled(int b);                                              // 0x005dd090
    void Refresh(int a, int b);                                              // 0x005de690
};
}
namespace SP {
class cWindowManager {
public:
    void HideWindow(uint32_t id);                                            // 0x0045b000
    int  IsWindowOpen(uint32_t id);                                          // 0x0045b210
    void OpenWindow(uint32_t id, int b);                                     // 0x0045ae10
    void CloseWindow(uint32_t id);                                           // 0x0045afc0
};
}
namespace SP {
cWindowManager* WindowManager_s0057_44b0();                                             // 0x00401050
}
namespace SP {
class cGameView {
public:
    void SetFlags(int a, int b);                                             // 0x0067c420
    void AddLayer(ResourceKey key, void* handler, int a, float x, float y, float z, int b, int c);  // 0x0067aaf0
};
}
namespace SP {
cGameView* GameViewA();                                                      // 0x0067cac0
}
namespace SP {
cGameView* GameViewB();                                                      // 0x0067caf0
}
namespace SP {
struct cLocalObject {
    uint32_t mData[4];
    void Release();                                                          // 0x0093a2e0
    void Close() { Release(); mData[0] = 0; mData[1] = 0; mData[2] = 0; mData[3] = 0; }
};
}
namespace SP {
class cAppModeEditorBase_s0057_44b0 {
public:
    char pad0[0x20];
    cIApp_s0057_44b0* mApp;                                    // +0x20
    EA::AutoRefCount_s0057_44b0<cPropertyList_s0057_44b0> mCurrentConfigProperties;   // +0x24
    char pad28[0x78 - 0x28];
    EA::AutoRefCount_s0057_44b0<cSPEditorUI_s0057_44b0> mUI;              // +0x78
    char pad7c[0x98 - 0x7c];
    EA::AutoRefCount_s0057_44b0<cSPEditorModel_s0057_44b0> mEditorSaveModel;   // +0x98
    char pad9c[0x150 - 0x9c];
    cSPEditorResourceFactory_s0057_44b0* mSaveLoadFactory;     // +0x150
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
    cSPEditorAnimatedCreatureManager_s0057_44b0* mAnimCreatureManager;   // +0x360
    cViewer_s0057_44b0* mShadowViewer;                         // +0x364
    char pad368[0x3c4 - 0x368];
    cSPEditorUIPanel* mPanel;                       // +0x3c4
    char pad3c8[0x434 - 0x3c8];
    EA::AutoRefCount_s0057_44b0<cSPEditorBudget_s0057_44b0> mBudget;      // +0x434
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
    void PurchaseBlock(cSPEditorBlock_s0057_44b0* block);  // 0x00574850 (SP::cAppModeEditorBase::PurchaseBlock)
    ResourceKey GetRandomBackground();
    ResourceKey GetNextBackground();
    int FlushFactory(cSPEditorResourceFactory_s0057_44b0* factory);
    void SwitchToPlayModeCamera();  // 0x00574a60 (SP::cAppModeEditorBase::SwitchToPlayModeCamera)
    int ScoreCreatureForZCorp();  // 0x00574b40 (SP::cAppModeEditorBase::ScoreCreatureForZCorp)
    int CanPublish();
    void SetupThumbnailModelWorld(cIModelWorld_s0057_44b0* world, bool isAnimated);
    void UpdateModelSounds(float deltaTime);  // 0x00574f30 (SP::cAppModeEditorBase::UpdateModelSounds)
    void ExitEditorUI();
    static void SetupGameViewLayers();
};
}
namespace SP {
void PlayModeCameraCallback(void* editor);                                   // 0x00572f00
}
namespace EA {
namespace Messaging {
void RemoveHandler(uint32_t h, uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00571db0
}
}
namespace EA {
namespace Audio {
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
}
}
namespace EA {
namespace Audio {
IAudioSystem* GetSystemAT_s0057_44b0();                                                 // 0x00a206f0
}
}
void Start3dSoundByName(uint32_t soundId, uint32_t instanceId, float x, float y, float z);   // 0x00571f80
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
struct cDefaultLayerHandler {
    virtual void Handle();
};
extern ResourceKey kLayerKeyA;   // 0x0150d090
extern ResourceKey kLayerKeyB;   // 0x0150d09c
// ---- items of slice s005744b0 end

// ---- items of slice s00576140 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedIncrement, _InterlockedDecrement)
void operator delete(void* p);                                              // 0x00f47380
struct Vector3_s0057_6140 {
    float x, y, z;
    Vector3_s0057_6140() {}
    Vector3_s0057_6140(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
};
inline Vector3_s0057_6140 operator-(const Vector3_s0057_6140& a, const Vector3_s0057_6140& b) { return Vector3_s0057_6140(a.x - b.x, a.y - b.y, a.z - b.z); }
struct ResourceKey_s0057_6140 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
namespace EA {
template <typename T>
struct AutoRefCount_s0057_6140 {
    T* mpObject;
    AutoRefCount_s0057_6140() : mpObject(0) {}
    AutoRefCount_s0057_6140(const AutoRefCount_s0057_6140& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    AutoRefCount_s0057_6140& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p)
                p->AddRef();
            mpObject = p;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s0057_6140& operator=(const AutoRefCount_s0057_6140& x);
};
}
namespace EA {
struct RefCountTemplate_s0057_6140 {
    virtual ~RefCountTemplate_s0057_6140();
    int mnRefCount;
    int Release()
    {
        int n = mnRefCount - 1;
        mnRefCount = n;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
        return n;
    }
};
}
namespace eastl {
template <typename T> inline const T& min(const T& a, const T& b) { return (b < a) ? b : a; }
}
namespace eastl {
struct allocator_s0057_6140 {
    allocator_s0057_6140(const char* = 0) {}
};
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0057_6140>
class basic_string_s0057_6140 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    explicit basic_string_s0057_6140(const Allocator& a);
    static int compare(const T* pBegin1, const T* pEnd1, const T* pBegin2, const T* pEnd2);
};
}
namespace eastl {
template <typename T> int Compare(const T* p1, const T* p2, size_t n);       // 0x00572930
}
class IRefCounted {
public:
    virtual void Destroy();
    virtual int AddRef();
    virtual int Release();
};
class IReleasable {
public:
    virtual void v00();
    virtual int Release();
};
class cObjectOwner;
struct cOwnedObject {
    cObjectOwner* mpOwner;      // +0x00
    uint32_t mFlags;            // +0x04 (bit 31: owner-allocated)
    char pad8[0x40 - 8];
    int mRefCount;              // +0x40
    inline void RemoveReference();
};
class cObjectOwner {
public:
#define PH(n) virtual void ph##n();
    PH(0) PH(1) PH(2) PH(3) PH(4) PH(5) PH(6) PH(7) PH(8) PH(9) PH(10) PH(11) PH(12) PH(13) PH(14)
    PH(15) PH(16) PH(17) PH(18) PH(19) PH(20) PH(21) PH(22) PH(23) PH(24) PH(25) PH(26) PH(27)
    PH(28) PH(29) PH(30) PH(31) PH(32) PH(33) PH(34) PH(35) PH(36) PH(37) PH(38) PH(39) PH(40)
    PH(41) PH(42) PH(43) PH(44) PH(45) PH(46) PH(47) PH(48) PH(49) PH(50) PH(51) PH(52) PH(53)
    PH(54) PH(55) PH(56) PH(57) PH(58) PH(59) PH(60) PH(61) PH(62) PH(63) PH(64) PH(65) PH(66)
    PH(67) PH(68) PH(69) PH(70) PH(71) PH(72) PH(73) PH(74) PH(75) PH(76) PH(77) PH(78) PH(79)
    PH(80) PH(81) PH(82) PH(83) PH(84) PH(85) PH(86) PH(87) PH(88) PH(89) PH(90) PH(91)
#undef PH
    virtual void FreeObject(cOwnedObject* obj, bool ownerAllocated);        // +0x170
};
inline void cOwnedObject::RemoveReference()
{
    if (mRefCount > 1)
        --mRefCount;
    else
        mpOwner->FreeObject(this, (mFlags >> 31) & 1);
}
struct cOwnedObjectPtr {
    cOwnedObject* mpObject;
    ~cOwnedObjectPtr();
    cOwnedObjectPtr& operator=(cOwnedObject* p)
    {
        if (mpObject) {
            cOwnedObject* old = mpObject;
            mpObject = p;
            old->RemoveReference();
        }
        return *this;
    }
};
struct cRefBase0 { virtual void Base0Fn(); };
struct cRefCountedModel : cRefBase0, EA::RefCountTemplate_s0057_6140 {};
struct cRefCountedModelPtr {
    cRefCountedModel* mpObject;
    cRefCountedModelPtr& Reset();
    void operator=(int)
    {
        if (mpObject) {
            cRefCountedModel* p = mpObject;
            mpObject = 0;
            p->Release();
        }
    }
};
namespace EA {
namespace IO {
class IStream_s0057_6140;
}
}
namespace EA {
namespace IO {
bool WriteUint32(IStream_s0057_6140* s, const uint32_t* p, size_t n, int endian);     // 0x0093aa70
}
}
namespace EA {
namespace IO {
bool ReadInt32(IStream_s0057_6140* s, int32_t* p, size_t n, int endian);              // 0x0093a780
}
}
namespace EA {
namespace IO {
bool WriteBool8(IStream_s0057_6140* s, const bool* p, size_t n);                       // 0x0093a9a0
}
}
class cStreamProvider {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual EA::IO::IStream_s0057_6140* GetStream();                                   // +0x18
};
class cSerializer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void EndBlock();                                                // +0x1c
    virtual cStreamProvider* GetProvider();                                 // +0x20
};
struct cEditorSnapshot {
    int mId;
    float mValues[5];
    bool mFlags[5];
    float mExtra[3];
    int mLast;

    cEditorSnapshot(const cEditorSnapshot& x) { Copy(x); }
    cEditorSnapshot& operator=(const cEditorSnapshot& x);
    __forceinline void Copy(const cEditorSnapshot& x)
    {
        mId = x.mId;
        mValues[0] = x.mValues[0]; mValues[1] = x.mValues[1]; mValues[2] = x.mValues[2];
        mValues[3] = x.mValues[3]; mValues[4] = x.mValues[4];
        mFlags[0] = x.mFlags[0]; mFlags[1] = x.mFlags[1]; mFlags[2] = x.mFlags[2];
        mFlags[3] = x.mFlags[3]; mFlags[4] = x.mFlags[4];
        mExtra[0] = x.mExtra[0]; mExtra[1] = x.mExtra[1]; mExtra[2] = x.mExtra[2];
        mLast = x.mLast;
    }
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& x);                                              // 0x0041cb40
};
Matrix3& MakeRotation(Matrix3& out, const Vector3_s0057_6140& axis, float angle);    // 0x00453b20
struct BoundingBox_s0057_6140 {
    Vector3_s0057_6140 lower;
    Vector3_s0057_6140 upper;
    BoundingBox_s0057_6140();
};
namespace SP {
class cCheatManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void RemoveCheat(const char* name);                              // +0x1c
};
}
namespace SP {
cCheatManager* CheatManager();                                               // 0x0067de20
}
namespace SP {
class cMessageServer {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual void RemoveListener(void* listener, uint32_t messageID, int priority);   // +0x2c
};
}
namespace SP {
cMessageServer* MessageServer_s0057_6140();                                             // 0x0067dcc0
}
namespace SP {
class cModelManager_s0057_6140 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void ReleaseModels(uint32_t groupID);                            // +0x18
};
}
namespace SP {
cModelManager_s0057_6140* ModelManager_s0057_6140();                                               // 0x0067dd80
}
namespace SP {
class cEffectsManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void ReleaseEffects(uint32_t groupID);                           // +0x50
};
}
namespace SP {
cEffectsManager* EffectsManager();                                           // 0x0067ddd0
}
namespace SP {
class cSaveRecord {
public:
    virtual void v00(); virtual void v04();
    virtual int Release();                                                   // +0x08
    virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual class cSaveStream* GetStream();                                  // +0x18
    virtual void v1c(); virtual void v20();
    virtual void Close();                                                    // +0x24
};
}
namespace SP {
class cSaveStream {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Write(const void* data, uint32_t size);                     // +0x38
};
}
namespace SP {
class cSaveArea {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual bool OpenRecord(const ResourceKey_s0057_6140& key, EA::AutoRefCount_s0057_6140<cSaveRecord>* record, int access, int disposition, int a, int b);   // +0x34
};
}
namespace SP {
cSaveArea* GetSaveArea(const char* name);                                    // 0x006b1f90
}
namespace SP {
class cSPEditorModel_s0057_6140 {
public:
    char pad0[0x58];
    int mModelType;                                                          // +0x58
    void ClearModel();                                                       // 0x004ad330
};
}
namespace SP {
struct cSPEditorModelRef : cRefCountedModel {};
}
namespace SP {
class cSPEditorPhysicsWorld_s0057_6140 : public EA::RefCountTemplate_s0057_6140 {
public:
    void Clear();                                                            // 0x004b9140
};
}
namespace SP {
class cViewer_s0057_6140 {
public:
    ~cViewer_s0057_6140();                                                              // 0x007c4000
    void Shutdown();                                                         // 0x007c3ba0
};
}
namespace SP {
class cEditorLaunchData_s0057_6140 {
public:
    char pad0[0xc];
    int mEditorID;                                                           // +0x0c
    char pad10[0x6e - 0x10];
    bool mbShowBackground;                                                   // +0x6e
};
}
namespace SP {
class cSPEditorBudget_s0057_6140 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void AddDNA(int a, int amount);                                  // +0x20
};
}
namespace SP {
class cIAppMode_s0057_6140 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Deactivate();                                               // +0x1c
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();
    virtual uint32_t GetEditorID();                                          // +0x44
};
}
namespace SP {
class cAppModeEditorBase_s0057_6140 : public cIAppMode_s0057_6140 {
public:
    char pad4[0x10 - 4];
    uint32_t mMessageListener;                                               // +0x10 (listener base)
    char pad14[0x1c - 0x14];
    uint32_t mLayerHandler;                                                  // +0x1c (layer base)
    void* mApp;                                                              // +0x20
    char pad24[0x84 - 0x24];
    IReleasable* mSaveModelWorld;                                            // +0x84
    IReleasable* mBackgroundModelWorld;                                      // +0x88
    IReleasable* mModelWorld;                                                // +0x8c
    cSPEditorPhysicsWorld_s0057_6140* mPhysicsWorld;                                    // +0x90
    IReleasable* mEffectsWorld;                                              // +0x94
    cRefCountedModelPtr mEditorSaveModel;                                    // +0x98
    cSPEditorModelRef* mEditorModel;                                         // +0x9c
    cOwnedObjectPtr mPedestalModel;                                          // +0xa0
    char pada4[4];
    cOwnedObjectPtr mTestEnvironmentModel;                                   // +0xa8
    cOwnedObjectPtr mBackgroundModel;                                        // +0xac
    char padb0[0x15c - 0xb0];
    EA::AutoRefCount_s0057_6140<IRefCounted> mTextureFactory;                           // +0x15c
    char pad160[0x1cc - 0x160];
    cEditorLaunchData_s0057_6140* mLaunchData;                                          // +0x1cc
    char pad1d0[0x2b0 - 0x1d0];
    bool mbActive;                                                           // +0x2b0
    char pad2b1[0x31c - 0x2b1];
    int mEditorMode;                                                         // +0x31c
    char pad320[0x3cc - 0x320];
    cViewer_s0057_6140* mViewers[5];                                                    // +0x3cc
    char pad3e0[0x434 - 0x3e0];
    cSPEditorBudget_s0057_6140* mBudget;                                                // +0x434
    char pad438[0x448 - 0x438];
    uint32_t mSaveData[2];                                                   // +0x448
    char pad450[0x4f0 - 0x450];
    int mBackgroundEnabled[6];                                               // +0x4f0
    char pad508[0x59c - 0x508];
    uint32_t mHoverResult;                                                   // +0x59c
    float mHoverRadius;                                                      // +0x5a0
    char pad5a4[0x5c0 - 0x5a4];
    uint32_t mHandler[5];                                                    // +0x5c0 (AutoHandler)

    cSPEditorModel_s0057_6140* SaveModel() { return (cSPEditorModel_s0057_6140*)mEditorSaveModel.mpObject; }
    int GetEditorCategory();
    void UpdateBackgroundLayer();
    uint32_t PickHover(const Vector3_s0057_6140& pos);
    bool Shutdown();
    void AddDNA();                                                           // 0x00575f70
};
}
namespace SP {
extern const char kEditorSaveArea[];                                         // 0x011ac19c
}
namespace SP {
extern ResourceKey_s0057_6140 kEditorSaveKey;                                           // 0x0150cfa0
}
namespace SP {
extern EA::AutoRefCount_s0057_6140<IRefCounted> sEditorResource;                       // 0x015eebec
}
namespace SP {
void ShutdownEditorSubsystem();                                              // 0x00563de0
}
namespace SP {
void ShutdownEditorUI();                                                     // 0x005a98f0
}
namespace EA {
namespace ArgScript {
class cArguments_s0057_6140 { public: const char** MainArguments(size_t* numArgs, int minArgs, int maxArgs) const; };  // 0x00838020
}
}
namespace EA {
namespace ArgScript {
typedef cArguments_s0057_6140 Line;
}
}
namespace EA {
namespace ArgScript {
class ICommand {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual int AddRef();                                                    // +0x0c
    virtual int Release();                                                   // +0x10
};
}
}
namespace EA {
namespace Audio {
class IAudioSystem_s0057_6140 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void BeginMessage(uint32_t id);                                  // +0x38
    virtual void v3c();
    virtual void AddParam(uint32_t id, uint32_t value);                      // +0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50(); virtual void v54();
    virtual void SendMessage();                                              // +0x58
};
}
}
namespace EA {
namespace Audio {
IAudioSystem_s0057_6140* GetSystemAT_s0057_6140();                                                 // 0x00a206f0
}
}
struct BoolVector { uint8_t* mpBegin; uint8_t* mpEnd; };
namespace {
class cEditorCheatBase : public EA::ArgScript::ICommand {
public:
    char pad4[0x10 - 4];
    SP::cAppModeEditorBase_s0057_6140* mpEditor;                                            // +0x10
};
class cEditorBudgetCheat : public cEditorCheatBase {
public:
    void ParseLine(const EA::ArgScript::Line& line);
};
class cEditorAddDNACheat : public cEditorCheatBase {
public:
    void Execute(const EA::ArgScript::Line& line);
};
}
static inline void DeleteViewer(SP::cViewer_s0057_6140*& viewer)
{
    if (viewer) {
        viewer->Shutdown();
        delete viewer;
        viewer = 0;
    }
}
// ---- items of slice s00576140 end

// ---- items of slice s00577130 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_preloadGroup;                   // 0x0150cdd4
#undef META
namespace SP {
namespace EditorUtils {
    float __cdecl CalculateModelSize(void* model);                                      // 0x48ca10
}
}
namespace SP {
namespace EditorUtils {
    int   __cdecl CountModelParts(void* model);                                         // 0x48cc20
}
}
void   __stdcall SomeGuardCall(void* p);          // 0x440b90
struct cBlockF40b90 { void* F40b90(void* out); };  // 0x440b90 (copies 12 bytes at +0x5f8)
void   __cdecl PlayEditorEvent(uint32_t id);      // 0x4a88d0
int    __cdecl g_soundBlockCounter;               // 0x15e4eec
struct IObject_s0057_7130 {
    virtual void slot0();
    virtual void AddRef();                        // +0x4
    virtual void Release();                       // +0x8
};
struct ISkinManager_s0057_7130 {
    void* GetSkin(int);                           // 0x4c49e0
};
struct ObjF8 {
    void SomeMethod(int);                         // 0x697a10
};
struct ObjE4 {
    void* SomeCall();                             // 0x47e6c0
};
template <typename T> static inline T* Field(void* self, uint32_t off) {
    return *(T**)((char*)self + off);
}
template <typename T> static inline T& Ref(void* self, uint32_t off) {
    return *(T*)((char*)self + off);
}
struct ResKey3 { uint32_t a, b, c; };
struct IRC {                                      // COM-style refcounted: AddRef +0, Release +4
    virtual void AddRef();
    virtual void Release();
};
struct IRCptr {                                   // raw ref slot with the AsPointer() idiom (no dtor: orig has no EH)
    IRC* mp;
    IRCptr() : mp(0) {}
    void Drop() { if (mp) mp->Release(); }
    IRC** AsPointer()
    {
        if (mp) {
            IRC* t = mp;
            mp = 0;
            t->Release();
        }
        return &mp;
    }
};
struct cTexturePreload_s0057_7130 {                          // size 0x34
    cTexturePreload_s0057_7130(int mode);                    // 0x007b07e0
    virtual void AddRef();                        // vtable +0
    virtual void Release();                       // vtable +4
    void PreloadTextureList(ResKey3* key);        // 0x007b1e90 (thiscall, ret 4)
    uint32_t pad[12];                             // object size 0x34
};
struct cPropMgr {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, IRC** ppList);   // 0x2c
};
cPropMgr* PropertyManager_s0057_7130();                      // 0x0067de30
bool GetPropertyAsKeyInstance(IRC* list, uint32_t id, uint32_t* out);   // 0x006a12a0 (cdecl)
bool GetPropertyAsKey(IRC* list, uint32_t id, ResKey3* out);            // 0x006a1250 (cdecl)
struct cSPEditorBlock_s0057_7130 {
    ResKey3 GetMirroredKey(int type, int sub);    // 0x00438f20 (thiscall, hidden return, ret 0xc)
};
struct Block_s0057_7130 {                                    // creature part, 0x1d8 bytes
    uint32_t pad0;
    uint32_t id;                                  // +4
    char pad[0x1d0];
};
struct IModelRes : IRC {
    virtual void v08();
    virtual struct ModelParts* Query(uint32_t typeId);   // +0xc
};
struct ModelParts {
    char pad[0x98];
    Block_s0057_7130* mpBegin;                               // +0x98
    Block_s0057_7130* mpEnd;                                 // +0x9c
};
struct IResMan_s0057_7130 {
virtual void v0();
virtual void v1();
virtual void v2();
    virtual bool GetResource(ResKey3* key, IRC** out, int a, int b, int c, int d);   // +0xc
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual bool WriteResource(void* res, void* factoryData, void* db, void* factory, ResKey3* nameKey);   // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
virtual void v38();
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
virtual void v5c();
virtual void v60();
virtual void v64();
virtual void v68();
    virtual bool Slot6c(void* res, int flag);     // +0x6c
};
IResMan_s0057_7130* GetManager_s0057_7130();                            // 0x0067dcd0
struct cSPPaletteCursor {                         // size 0x20
    cSPPaletteCursor();                           // 0x005c7b80
    virtual void v0();
    virtual void AddRef();                        // +4
    virtual void Release();                       // +8
    void SetPalette(void* palette);               // 0x005c7bc0 (ret 4)
    struct PRec* First(void*, void*, void*, void*);   // 0x005c7e80 (ret 0x10)
    struct PRec* Next(void*, void*, void*, void*);    // 0x005c7e20 (ret 0x10)
    void Close();                                 // 0x00c2e4e0
    uint32_t pad[7];                              // object size 0x20 (vptr + 7 dwords)
};
struct PRec {
    char pad0[0xc];
    uint32_t f0c;
    char pad10[4];
    uint32_t f14;
    char pad18[0xc];
    uint32_t f24;
};
struct ModelObj_s0057_7130 {
    void Reset();                                 // 0x004ad110
};
bool __cdecl HasAnyResource(cSPEditorBlock_s0057_7130* block, ResKey3* key);   // 0x577b20
struct ModelRes {                                 // cSPEditorModelResource, 0xac bytes
    virtual void AddRef();                        // +0
    virtual void Release();                       // +4
    uint32_t mRefCount;                           // +4
    ResKey3 mKey;                                 // +8
    uint32_t pad14[(0xac - 0x14) / 4];
    ModelRes();                                   // 0x004b9c70
};
struct ThumbRes {                                 // 0x128 bytes
    virtual void AddRef();
    virtual void Release();
    uint32_t mRefCount;
    ResKey3 mKey;                                 // +8
    uint32_t pad14[(0x128 - 0x14) / 4];
    ThumbRes();                                   // 0x004b9da0
};
struct MetaObj_s0057_7130 {                                  // Pollinator::cAssetMetadata, 0xd8 bytes
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[(0xd8 - 4) / 4];
    MetaObj_s0057_7130();                                    // 0x00550450
    char Set(ResKey3* assetKey, const wchar_t* name, const wchar_t* description, const wchar_t* tags,
             ResKey3* parentKey, bool isPollinated);   // 0x00551240 (ret 0x18)
};
struct ResRef {                                   // holder whose out-of-line ctor stores + AddRefs
    void* mpObject;
    explicit ResRef(void* p);                     // 0x00572660
};
struct cMWModel_s0057_7130 {
    virtual void s0();
    virtual const wchar_t* Slot1();               // +4
    virtual void s2();
    virtual const wchar_t* Slot3();               // +0xc
    char pad[0xc - 4];
    ResKey3 mKey;                                 // +0xc
    bool SaveResource(ModelRes* res);             // 0x004af260 (ret 4)
};
struct SubObj5 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
    virtual const wchar_t* Slot5();               // +0x14
};
struct TexSvc {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
virtual void s18();
virtual void s19();
virtual void s20();
virtual void s21();
virtual void s22();
virtual void s23();
virtual void s24();
    virtual void s25();
    virtual void Slot68(void* arg);               // +0x68
};
TexSvc* __cdecl GetTexSvc();                      // 0x0067dd60
void* __cdecl GetSaveArea_s0057_7130(uint32_t id);           // 0x006b1f90
void __cdecl Fn46d840(ModelRes* model, ThumbRes* thumb);   // 0x0046d840 (cdecl)
struct ImgObj { void* GetPixels(); };             // 0x0046f260
struct cImportExport {
    bool CreateExportThumb(ModelRes* model, void* pixels, void* saveDb, int zero, bool flag);   // 0x005fa8d0 (ret 0x14)
};
cImportExport* __cdecl GetImportExport();         // 0x005f7930
struct IAuth { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
               virtual bool Slot24(); };          // +0x24
IAuth* __cdecl AuthManager();                     // 0x00607a60
bool __cdecl MarkDirty(void* res);                // 0x006ad010
struct Bits128_s0057_7130 { uint32_t w[4]; };
bool __cdecl Fn4f3d60(Bits128_s0057_7130 a, Bits128_s0057_7130 b);      // 0x004f3d60
extern Bits128_s0057_7130 g_validBits;                       // 0x015dab94
int  __cdecl GetModelCategory(ResKey3* key);      // 0x00552300
int  __cdecl FindModelPart(ResKey3* key, uint32_t hash);   // 0x00556140
void __cdecl SummarizeVehiclePart(ResKey3* newKey, int part);   // 0x00555f70
static __forceinline void SummarizePart(ResKey3* key, ResKey3* newKey, uint32_t hash)
{
    if (FindModelPart(key, hash))
        SummarizeVehiclePart(newKey, FindModelPart(key, hash));
}
namespace SP {
class cAppModeEditorBase_s0057_7130 {
public:
    char pad[0x458];

    void SetSoundBlockAdded(int);                 // 0x577130
    void SetSoundBlockRemoved(int);               // 0x5771f0
    void RemoveTorsoFromEffectsMask();            // 0x5772b0
    void PreloadResources(int key);               // 0x577310
    void SetSomeBlock(int);                       // 0x5774f0
    void UpdateBlockState();                      // 0x577520
    void SetTorsoBlock(void*, char);              // 0x577580
    bool HasSkin();                               // 0x577620
    void SaveSomething();                         // 0x577650
    bool LoadSomething(void* block);              // 0x577c40
    int  FlushFactory(void* factory);             // 0x574a20 (ret 4)
    void Sub572430(ResKey3* key);                 // 0x572430 (ret 4)
    void SomeLoader();                            // 0x577dd0

    void SetRolloverHandle(int, int);             // 0x573d70
    void DoSomeOther(int, int);                   // 0x573c00
};
}
using SP::cAppModeEditorBase_s0057_7130;
// ---- items of slice s00577130 end

// ---- items of slice s005794b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern unsigned g_mask[4];                        // 0x15da7c4
namespace SP {
class cAppModeEditorBase_s0057_94b0 {
public:
    char pad[0x458];
    void UpdateRenderSettings();                  // 0x5794b0
    void SetCurrentConfig(int);                   // 0x579720
    void SwitchToEditorCamera();                  // 0x5798f0
    void SavePreferenceSomething();               // 0x5799a0
    bool HasSameMask();                           // 0x579a20
    bool SomeFinder();                            // 0x579af0
    void CheatCommand(void* args);                // 0x579d40
};
}
using SP::cAppModeEditorBase_s0057_94b0;
struct cWString {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    void AllocateSelf(uint32_t n);                // 0x429760
    void RangeInitialize(const wchar_t* s);       // 0x579a90
};
struct cString8 {
    char* mpBegin;
    char* mpEnd;
    void assign(const char* first, const char* last);   // 0x454cb0
    cString8& operator=(const cString8& other);          // 0x579c60
};
void cAppModeEditorBase_s0057_94b0::UpdateRenderSettings() {}
void cAppModeEditorBase_s0057_94b0::SetCurrentConfig(int) {}
void cAppModeEditorBase_s0057_94b0::SwitchToEditorCamera() {}
void cAppModeEditorBase_s0057_94b0::SavePreferenceSomething() {}
bool cAppModeEditorBase_s0057_94b0::SomeFinder() { return false; }
void cAppModeEditorBase_s0057_94b0::CheatCommand(void*) {}
// ---- items of slice s005794b0 end

// ---- items of slice s00579e20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char vtbl_BehaviorMessage[];                // 0x013eb90c vtbl_UI::BehaviorMessage
extern char vtbl_13eb844[];                        // 0x013eb844
extern unsigned g_mec;                           // 0x015da7ec
    extern unsigned int g_mf0; // 0x015da7f0
    extern unsigned int g_mf4; // 0x015da7f4
    extern unsigned int g_mf8; // 0x015da7f8
extern unsigned g_d40;                           // 0x015daa40
    extern unsigned int g_d44; // 0x015daa44
    extern unsigned int g_d48; // 0x015daa48
    extern unsigned int g_d4c; // 0x015daa4c
extern char vtbl_RefObj[];           // 0x013ef094 ??_7RefObj@@6B@
extern char vtbl_13f585c[], vtbl_13f5858[], g_01667bac[], g_01667bae[];
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)
void operator_delete__(void* p);                  // 0x00f47380
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0 (EA)
struct Bits128 {
    unsigned w[4];
    Bits128() { w[0] = 0; w[1] = 0; w[2] = 0; w[3] = 0; }
    struct Uninit {};
    Bits128(Uninit) {}
    Bits128(unsigned a, unsigned b, unsigned c, unsigned d) { w[0] = a; w[1] = b; w[2] = c; w[3] = d; }
};
struct V {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
};
struct RcObj {
    virtual void* Destroy(int flags);
    int rc;
};
struct TagMgr;
struct TagObj {
    TagMgr* mgr;
    unsigned f4;
    char pad[0x40 - 8];
    int cnt;
};
struct TagMgr {
    virtual void m0();
    virtual void m1();
    virtual void m2();
    virtual void m3();
    virtual void m4();
    virtual void m5();
    virtual void m6();
    virtual void m7();
    virtual void m8();
    virtual void m9();
    virtual void m10();
    virtual void m11();
    virtual void m12();
    virtual void m13();
    virtual void m14();
    virtual void m15();
    virtual void m16();
    virtual void m17();
    virtual void m18();
    virtual void m19();
    virtual void m20();
    virtual void m21();
    virtual void m22();
    virtual void m23();
    virtual void m24();
    virtual void m25();
    virtual void m26();
    virtual void m27();
    virtual void m28();
    virtual void m29();
    virtual void m30();
    virtual void m31();
    virtual void m32();
    virtual void m33();
    virtual void m34();
    virtual void m35();
    virtual void m36();
    virtual void m37();
    virtual void m38();
    virtual void m39();
    virtual void m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual void m44();
    virtual void m45();
    virtual void m46();
    virtual void m47();
    virtual void m48();
    virtual void m49();
    virtual void m50();
    virtual void m51();
    virtual void m52();
    virtual void m53();
    virtual void m54();
    virtual void m55();
    virtual void m56();
    virtual void m57();
    virtual void m58();
    virtual void m59();
    virtual void m60();
    virtual void m61();
    virtual void m62();
    virtual void m63();
    virtual void m64();
    virtual void m65();
    virtual void m66();
    virtual void m67();
    virtual void m68();
    virtual void m69();
    virtual void m70();
    virtual void m71();
    virtual void m72();
    virtual void m73();
    virtual void m74();
    virtual void m75();
    virtual void m76();
    virtual void m77();
    virtual void m78();
    virtual void m79();
    virtual void m80();
    virtual void m81();
    virtual void m82();
    virtual void m83();
    virtual void m84();
    virtual void m85();
    virtual void m86();
    virtual void m87();
    virtual void m88();
    virtual void m89();
    virtual void m90();
    virtual void m91();
    virtual void Free(TagObj* o, unsigned flag);   // vtbl+0x170
};
struct VecStub {
    void DtorStarRecordVec();                     // 0x00ae6970 ~vector<AutoRefCount<cStarRecord>>
    void DtorSharedLibVec();                      // 0x005c7f10 ~vector<AutoRefCount<SharedLibrary>>
    void Fn5942e0();                              // 0x005942e0 (thiscall, no args)
};
struct RbTreeStub { void DoNukeSubtree(void* root); };     // 0x009a9600
void RemoveHandler(int h, int a, int b, int c, int d);    // 0x00571db0 EA::Messaging::RemoveHandler (cdecl)
struct PropList {                                  // SP::cPropertyList
    bool GetDescription(unsigned id);              // 0x006a25a0
    char pad[0x3c];
};
extern PropList* g_sAppProperties;                 // 0x015fd918
struct PropRoot { char pad[0x3c]; struct PropSub* sub; };
struct PropSub { char pad[0x118]; int flag118; };
struct __declspec(novtable) BMsgBase {             // UI::BehaviorMessage base
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    long rc;                                       // +4
    unsigned data;                                 // +8
    char pad0c[0x30 - 0xc];
    unsigned id;                                   // +0x30
    unsigned pad34;
    __forceinline BMsgBase() : id(0) { *(void**)this = vtbl_BehaviorMessage; _InterlockedExchange(&rc, 0); }
};
struct __declspec(novtable) BMsg : BMsgBase {
    unsigned f38;                                  // +0x38
    unsigned pad3c;
    __forceinline BMsg() : f38(0) { *(void**)this = vtbl_13eb844; }
};
struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Post(unsigned id, BMsg* m, int a, int b);     // vtbl+0x18
};
MsgServer* MessageServer_s0057_9e20();                        // 0x0067dcc0 (cdecl)
struct LayoutMgr {
    bool IsWorldVisible(unsigned id);              // 0x00810760
    void Method10660(unsigned id, int v);          // 0x00810660
};
LayoutMgr* GetLayoutManager();                     // 0x00805070 (cdecl)
struct ModelMgr { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
                  virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
                  virtual unsigned GetIndex(unsigned id, int v); };  // vtbl+0x28
ModelMgr* ModelManager_s0057_9e20();                          // 0x0067dd80 (cdecl)
bool FUN_004f3d60(Bits128 a, Bits128 b);           // 0x004f3d60 (cdecl, by-value masks)
struct TorsoHolder { void* p;
    void Set(void* x);                                        // 0x00478db0
};
struct SceneObjA {
    void* GetSceneObject(int i);                              // 0x004c45d0
};
struct XformStub {
    void Assign(void* src);                                   // 0x00537dc0 cSPTransform::operator=
};
namespace SP {
class cAppModeEditorBase_s0057_9e20 {
public:
    char pad[0x600];
    ~cAppModeEditorBase_s0057_9e20();                       // 0x579e20
    void RemoveTorsoFromEffectsMask();           // 0x5772b0
    void AddTorsoToEffectsMask(float x, float y, float z, int);   // 0x57a610
    void SendBehaviorMessage(BMsg*);             // 0x57a710
    __declspec(noinline) Bits128 GetMask();   // 0x57a960
    Bits128 GetDefaultMask();                    // 0x57a9e0
    int GetEditorSaveability();                  // 0x57aaa0
    void BuildPartMask(Bits128* out, void* p3, void* p4, int unused);   // 0x57ac00
};
}
using SP::cAppModeEditorBase_s0057_9e20;
extern unsigned g_mf0;                           // 0x015da7f0
extern unsigned g_mf4;                           // 0x015da7f4
extern unsigned g_mf8;                           // 0x015da7f8
extern unsigned g_d44;                           // 0x015daa44
extern unsigned g_d48;                           // 0x015daa48
extern unsigned g_d4c;                           // 0x015daa4c
#define F(T, off) (*(T**)((char*)this + (off)))
#define REL(off, slot) { V* p_ = F(V, off); if (p_) p_->s##slot(); }
#define ARRDEL(off) { void* a_ = F(void, off); if (a_ && ((int*)a_)[-1]) operator_delete__(a_); }
#define RCDEC(off) { RcObj* p_ = F(RcObj, off); if (p_) { int n_ = p_->rc - 1; p_->rc = n_; if (n_ == 0) { p_->rc = 1; p_->Destroy(1); } } }
#define RCDEC8(off) { char* b_ = F(char, off); if (b_) { RcObj* q_ = (RcObj*)(b_ + 4); int n_ = ((int*)q_)[1] - 1; ((int*)q_)[1] = n_; if (n_ == 0) { ((int*)q_)[1] = 1; q_->Destroy(1); } } }
#define TAGDEC(off) { TagObj* t_ = F(TagObj, off); if (t_) { if (t_->cnt < 2) t_->mgr->Free(t_, (t_->f4 >> 31) & 1); else t_->cnt--; } }
#define ATOMDEC(off) { char* b_ = F(char, off); if (b_) { volatile long* r_ = (volatile long*)(b_ + 8); \
    _InterlockedExchangeAdd(r_, -1); long v_ = _InterlockedExchangeAdd(r_, 0); \
    if (v_ < 1) _InterlockedExchangeAdd(r_, 1); else _InterlockedExchangeAdd(r_, 0); } }
#define STRDEL(boff, eoff) { char* b_ = F(char, boff); int d_ = (int)((char*)F(char, eoff) - b_) & ~1; if (d_ > 2 && b_) operator_delete__(b_); }
#define HANDLER(off) { int h_ = *(int*)((char*)this + (off)); if (h_) { int a_ = *(int*)((char*)this + (off) + 4); int b_ = *(int*)((char*)this + (off) + 8); \
    int c_ = *(int*)((char*)this + (off) + 12); int d_ = *(int*)((char*)this + (off) + 16); *(int*)((char*)this + (off)) = 0; RemoveHandler(h_, a_, b_, c_, d_); } }
struct __declspec(novtable) CheatBase2 {   // RefObj base at +4
    virtual void f0();
    unsigned f8;
    CheatBase2() { *(void**)this = vtbl_RefObj; f8 = 0; }
};
struct CheatObject2 {
    void* vt0;
    CheatBase2 b;
    char* s0c;
    char* s10;
    char* s14;
    CheatObject2();
};
static inline Bits128 BitsOr(const Bits128& a, const Bits128& b)
{
    return Bits128(a.w[0] | b.w[0], a.w[1] | b.w[1], a.w[2] | b.w[2], a.w[3] | b.w[3]);
}
struct PartObj { void FUN_004bac30(Bits128* out, Bits128 mask, int v); };    // 0x004bac30
struct CritList { int FUN_004accf0(); void* FUN_004accb0(int i); };         // 0x004accf0, 0x004accb0
struct CritItem { int FUN_00435b60(unsigned key); };                         // 0x00435b60
struct Key3 { unsigned a, b, c; };
bool GetPropertyAsKey(void* props, unsigned id, Key3* out);                  // 0x006a1250 (cdecl)
bool FUN_004efb20(void* p3, unsigned k, void* m48);                          // 0x004efb20 (cdecl)
bool FUN_004ef880(void* p3, unsigned k, void* m48);                          // 0x004ef880 (cdecl)
void FUN_004edf40(void* p4, Bits128* mask);                                  // 0x004edf40 (cdecl)
extern void* g_015e4ef0;                         // 0x015e4ef0
extern char vtbl_cAppModeEditorBase[], vtbl_13f57e4[], vtbl_13f57e0[], vtbl_13f57c8[], vtbl_13f57b8[], vtbl_13f57a8[], vtbl_13f57a4[];
extern char vtbl_cEditorResource[];             // 0x013eb938
extern char vtbl_PaintSystem[];                 // 0x013eb394
extern char vtbl_cContentValidationSummarizer[]; // 0x013ec458
// ---- items of slice s00579e20 end

// ---- items of slice s0057ae10 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0057_ae10 {
    float x, y, z;
    Vector3_s0057_ae10() {}
    Vector3_s0057_ae10(const Vector3_s0057_ae10& o) { x = o.x; y = o.y; z = o.z; }
    Vector3_s0057_ae10& operator=(const Vector3_s0057_ae10& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct cCreature_s0057_ae10 {
    char pad0[0x74];
    Vector3_s0057_ae10 mOffset;              // +0x74
    char pad1[0x180 - 0x80];
    void* mpFlagsObj;             // +0x180
};
struct cCreatureFlags {
    char pad0[4];
    uint32_t mFlags;              // +4
};
struct cEditorModel_s0057_ae10 {
    Vector3_s0057_ae10* GetVector(Vector3_s0057_ae10* out, int index);   // 0x004adca0 (thiscall, ret 8)
};
struct cAnimatedCreatureManager {
    cCreature_s0057_ae10* GetCreature(void* viewer);          // 0x0059ca70 (thiscall, ret 4)
};
struct cAppModeEditorBase {
    char pad0[0x98];
    cEditorModel_s0057_ae10* mEditorSaveModel;                // +0x98
    char pad1[0x31c - 0x9c];
    int32_t mQueuedAnim;                           // +0x31c
    char pad2[0x360 - 0x320];
    cAnimatedCreatureManager* mAnimCreatureManager; // +0x360
    void* mShadowViewer;                           // +0x364
    char pad3[0x384 - 0x368];
    bool mAnimatingCreatureVisible;                // +0x384
    bool mAnimatingCreatureActive;                 // +0x385

    void UpdateRenderSettings();                   // 0x005794b0
    void FUN_00575790();                           // 0x00575790
    void FUN_005757b0();                           // 0x005757b0

    void UpdateAnimatedCreature();
};
extern Vector3_s0057_ae10 gConst;   // 0x0150cc08
// ---- items of slice s0057ae10 end

// ---- items of slice s0057af00 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define FLT_MAX_VALUE 3.402823466e+38F
struct Vector3_s0057_af00 {
    float x, y, z;
    Vector3_s0057_af00() {}
    Vector3_s0057_af00(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s0057_af00(const Vector3_s0057_af00& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3_s0057_af00 operator-(const Vector3_s0057_af00& a, const Vector3_s0057_af00& b) { return Vector3_s0057_af00(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vector3_s0057_af00 Lerp(const Vector3_s0057_af00& a, const Vector3_s0057_af00& b, float t)
{
    return Vector3_s0057_af00((b.x - a.x) * t + a.x, (b.y - a.y) * t + a.y, (b.z - a.z) * t + a.z);
}
namespace SP {
 Vector3_s0057_af00 normalized_safe(const Vector3_s0057_af00& v);   // 0x00449c20
}
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
struct IUnknown32 {
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void* Cast(uint32_t iid);      // +0x0c
};
template <class T> struct AutoRefCount_s0057_af00 {
    T* mpObject;
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
};
struct cSPEditorBlock_s0057_af00;
struct cMWModel_s0057_af00;
struct cSPEditorHandle_s0057_af00 {                   // obtained from cMWModel::mpOwner (IID 0x50a1fe5)
    enum { kIID = 0x50a1fe5 };
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual uint32_t GetHandleType();      // +0x10
    cSPEditorBlock_s0057_af00* GetRigblock();         // 0x0047e6c0
    cMWModel_s0057_af00* GetModel();                  // 0x0047e680
    int GetHandleState();                  // 0x0047ec20
};
enum { kHandleTypeBallConnector = 0x50e8e23 };
template <class T> __forceinline T* interface_cast_inline(const AutoRefCount_s0057_af00<IUnknown32>& p)
{
    return p ? (T*)p->Cast(T::kIID) : 0;
}
namespace SP {
namespace EditorUtils {
cSPEditorHandle_s0057_af00* GetBoneForHandle(const AutoRefCount_s0057_af00<IUnknown32>& owner);   // 0x004aa030 (interface_cast<cSPEditorHandle*>)
}
}
namespace SP {
namespace EditorUtils {
cSPEditorBlock_s0057_af00* GetBlockForBallConnector(cMWModel_s0057_af00* model, Vector3_s0057_af00 pos);     // 0x00496bb0
}
}
namespace SP {
namespace EditorUtils {
bool IsBlockLocked(cSPEditorBlock_s0057_af00* block);                                   // 0x004a6120
}
}
cSPEditorBlock_s0057_af00* interface_cast_block(const AutoRefCount_s0057_af00<IUnknown32>& p);     // 0x004aa2a0 (interface_cast<cSPEditorBlock*>)
enum {
    kAttrIsVertebra = 7,
    kAttrIsPlantRoot = 8,
    kAttr0B = 0xb,
    kAttrIsNullBlock = 0x14,
};
struct cSPEditorBlock_s0057_af00 {
    char pad0[0x33c];
    cSPEditorBlock_s0057_af00* mpParent;              // +0x33c
    cSPEditorBlock_s0057_af00** mChildrenBegin;       // +0x340 (fixed_vector<AutoRefCount<cSPEditorBlock>, 8>)
    cSPEditorBlock_s0057_af00** mChildrenEnd;         // +0x344
    char pad348[0x3ec - 0x348];
    cSPEditorHandle_s0057_af00* mpBallConnectorHandle;   // +0x3ec
    char pad3f0[0xdc8 - 0x3f0];
    bitset64 mBooleanAttributes;           // +0xdc8
    bool TestAttribute(int i) const { return ((mBooleanAttributes.mWord[0] >> i) & 1) != 0; }
};
struct cMWModel_s0057_af00 {
    char pad0[0x44];
    bitset64 mGroupFlags;                  // +0x44
    char pad4c[0x64 - 0x4c];
    AutoRefCount_s0057_af00<IUnknown32> mpOwner;      // +0x64
};
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
struct IModelManager_s0057_af00 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual uint32_t GetGroupFlag(uint32_t groupID, int unk);   // +0x28
};
struct IModelWorld {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual cMWModel_s0057_af00* FindFirstModelAlongLine(const Vector3_s0057_af00& p1, const Vector3_s0057_af00& p2, float* pFactor,
                                              Vector3_s0057_af00* pIntersection, Vector3_s0057_af00* pUnk, FilterSettings& settings,
                                              int* pHitIndex, int* pUnk2);           // +0x24
};
struct cViewer_s0057_af00 {
    void GetCameraRay(float x, float y, Vector3_s0057_af00* pStart, Vector3_s0057_af00* pEnd);   // 0x007c4510
};
struct cIApp_s0057_af00 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual cViewer_s0057_af00* GetViewer();          // +0x58
};
struct cSPEditorSkinManager_s0057_af00 {
    void* GetSkin(int index);              // 0x004c49e0
    bool PickSkin(int lod, Vector3_s0057_af00 start, Vector3_s0057_af00 dir, Vector3_s0057_af00* pPos, Vector3_s0057_af00* pNormal,
                  float* pDistance, bool bUnk);                              // 0x004c4a30
    cSPEditorBlock_s0057_af00* GetBlockAtSkinPoint(int lod, Vector3_s0057_af00 pos);              // 0x004c4d30
};
namespace SP {
IModelManager_s0057_af00* ModelManager_s0057_af00();             // 0x0067dd80
}
namespace SP {
cIApp_s0057_af00* App_s0057_af00();                              // 0x0067dd10
}
struct EditorPickResult {
    cSPEditorBlock_s0057_af00* mpBlock;               // +0x00
    cMWModel_s0057_af00* mpModel;                     // +0x04
    Vector3_s0057_af00 mPosition;                     // +0x08
    bool mbSkin;                           // +0x14
    int mHitIndex;                         // +0x18
    EditorPickResult() : mpBlock(0), mpModel(0), mPosition(0.0f, 0.0f, 0.0f), mbSkin(false), mHitIndex(-1) {}
};
__forceinline bool ModelInGroup(cMWModel_s0057_af00* model, uint32_t flag) { return model->mGroupFlags.test(flag); }
namespace SP {
class cAppModeEditorBase_s0057_af00 {
public:
    char pad0[0x84];
    IModelWorld* mpMainModelWorld;         // +0x84
    char pad88[0xe9 - 0x88];
    bool mbPickVertebrae;                  // +0xe9 (ModAPI field_E9)
    char padea[0x150 - 0xea];
    cSPEditorSkinManager_s0057_af00* mpSkinManager;   // +0x150
    char pad154[0x2f6 - 0x154];
    bool mbOnlyEditFromPalette;            // +0x2f6
    char pad2f7[0x320 - 0x2f7];
    UIntVector mEnabledManipulators;       // +0x320
    char pad330[0x3b8 - 0x330];
    void* mpPartsPalette;                  // +0x3b8

    bool IsBlockInPalette(cSPEditorBlock_s0057_af00* block);   // 0x00577c40
    EditorPickResult Pick(float x, float y, bool bBlocksOnly);  // 0x0057af00 (SP::cAppModeEditorBase::Pick)
};  // namespace SP
}
// ---- items of slice s0057af00 end

// ---- items of slice s0057bfb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void  operator delete[](void* p);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
namespace eastl {
struct allocator_s0057_bfb0 {
    void* allocate(size_t n) { return operator new[](n, "Editor", 0, 0, 0, 0); }
    void deallocate(void* p) { operator delete[](p); }
};
}
namespace eastl {
extern wchar_t gEmptyString16[2];   // 0x01667BAC
}
namespace eastl {
template <typename T> struct EmptyStr;
}
namespace eastl {
template <> struct EmptyStr<wchar_t> { static wchar_t* Get() { return gEmptyString16; } };
}
namespace eastl {
template <> struct EmptyStr<char>    { static char*    Get() { return (char*)gEmptyString16; } };
}
namespace eastl {
template <typename T>
inline T* CharStringUninitializedCopy(const T* pSource, const T* pEnd, T* pDest)
{
    memcpy(pDest, pSource, (size_t)(pEnd - pSource) * sizeof(T));
    return pDest + (pEnd - pSource);
}
}
namespace eastl {
template <typename T, typename Allocator = allocator_s0057_bfb0>
class basic_string_s0057_bfb0 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Allocator mAllocator;

    basic_string_s0057_bfb0() : mpBegin(EmptyStr<T>::Get()), mpEnd(EmptyStr<T>::Get()), mpCapacity(EmptyStr<T>::Get() + 1) {}
    basic_string_s0057_bfb0(const basic_string_s0057_bfb0& x);
    struct CtorDoNotInitialize {};
    basic_string_s0057_bfb0(CtorDoNotInitialize, size_t n) : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(n + 1); *mpEnd = 0; }
    basic_string_s0057_bfb0(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(p); }
    ~basic_string_s0057_bfb0() { DeallocateSelf(); }

    basic_string_s0057_bfb0& operator=(const basic_string_s0057_bfb0& x);

    bool empty() const { return mpBegin == mpEnd; }
    const T* c_str() const { return mpBegin; }
    T* data() { return mpBegin; }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }

    void AllocateSelf(size_t n);
    void RangeInitialize(const T* pBegin, const T* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
        *mpEnd = 0;
    }
    void RangeInitialize(const T* pBegin);
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    void DoFree(T* p) { if (p) mAllocator.deallocate(p); }
    basic_string_s0057_bfb0& assign(const T* pBegin, const T* pEnd);
    basic_string_s0057_bfb0& append(const T* pBegin, const T* pEnd);
    int sprintf(const char* fmt, ...);
};
}
namespace eastl {
typedef basic_string_s0057_bfb0<wchar_t> string16_s0057_bfb0;
}
namespace EA {
namespace Thread {
inline long AtomicFetchAdd(volatile long* p, long v) { return _InterlockedExchangeAdd(p, v); }
}
}
namespace EA {
namespace Thread {
template <typename T>
struct AtomicInt_s0057_bfb0 {
    volatile long mValue;
    T GetValue() { return (T)AtomicFetchAdd(&mValue, 0); }
    void SetValue(T v) { _InterlockedExchange(&mValue, v); }
    T Increment() { return (T)AtomicFetchAdd(&mValue, 1) + 1; }
    T Decrement() { return (T)AtomicFetchAdd(&mValue, -1) - 1; }
};
}
}
namespace EA {
template <typename T>
class AutoRefCount_s0057_bfb0 {
public:
    T* mpObject;
    AutoRefCount_s0057_bfb0() : mpObject(0) {}
    AutoRefCount_s0057_bfb0(const AutoRefCount_s0057_bfb0& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0057_bfb0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0057_bfb0& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    AutoRefCount_s0057_bfb0& operator=(const AutoRefCount_s0057_bfb0& x) { return operator=(x.mpObject); }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
template <typename T>
class AutoRefCountX {
public:
    T* mpObject;
    AutoRefCountX(const AutoRefCountX& x);
    ~AutoRefCountX() { if (mpObject) mpObject->Release(); }
    AutoRefCountX& operator=(const AutoRefCountX& x);
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace EA {
namespace ResourceMan {
struct Key_s0057_bfb0 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
}
}
namespace EA {
namespace Messaging {
template <int N>
class MessageData {
public:
    union Data {
        uint32_t mUint32;
        int32_t  mInt32;
        float    mFloat;
        uint64_t mUint64;
    };
    Data mData[N];
    uint32_t mId;
};
}
}
namespace EA {
namespace Messaging {
template <int N>
class MessageBasic_s0057_bfb0 : public MessageData<N> {
public:
    MessageBasic_s0057_bfb0() { this->mId = 0; }
};
}
}
namespace EA {
namespace Messaging {
class IMessageRC_s0057_bfb0 {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};
}
}
namespace EA {
namespace Messaging {
class MessageRC_s0057_bfb0 : public IMessageRC_s0057_bfb0 {
public:
    Thread::AtomicInt_s0057_bfb0<int> mRefCount;
    MessageRC_s0057_bfb0() { mRefCount.SetValue(0); }
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
namespace Messaging {
template <int N>
class MessageBasicRC_s0057_bfb0 : public MessageBasic_s0057_bfb0<N>, public MessageRC_s0057_bfb0 {
public:
};
}
}
namespace EA {
namespace Messaging {
class IMessageServer_s0057_bfb0 {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual bool MessageSend(uint32_t id, void* pMessage, int flags);
};
}
}
namespace UI {
class BehaviorMessage : public EA::Messaging::MessageBasicRC_s0057_bfb0<5> {
public:
    uint32_t mFlags;   // +0x38
    BehaviorMessage(uint32_t id) : mFlags(0)
    {
        mId = id;
        mData[0].mUint32 = 0;
        mData[1].mUint32 = 0xFFFFFFFF;
        mData[2].mUint32 = 0;
    }
    ~BehaviorMessage();
};
}
namespace SP {
EA::Messaging::IMessageServer_s0057_bfb0* MessageServer_s0057_bfb0();
}
namespace SP {
struct Property_s0057_bfb0 {
    char pad_0[0x12];
    short mType;           // +0x12
    int* GetInt();         // 0x0041E990
};
}
namespace SP {
class cPropertyList_s0057_bfb0 {
public:
    virtual void _v0(); virtual void _v1(); virtual void _v2(); virtual void _v3(); virtual void _v4();
    virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8();
    virtual bool GetProperty(uint32_t propertyID, Property_s0057_bfb0*& result);
};
}
namespace SP {
class cSPEditorBlock_s0057_bfb0 {
public:
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
class cBlockTray {   // +0x434 of the editor
public:
    virtual void _v0();
    virtual int GetCount(int tray);
    virtual void _v2(); virtual void _v3(); virtual void _v4(); virtual void _v5(); virtual void _v6(); virtual void _v7(); virtual void _v8();
    virtual void SetCount(int tray, int count);
    virtual void _v10(); virtual void _v11();
    virtual void AddBlock(cSPEditorBlock_s0057_bfb0* block);
};
}
namespace SP {
class cSPEditorUI_s0057_bfb0 {
public:
    void SetMode(int mode);                                    // 0x005DDA30
    void SetSelected(uint32_t controlID, bool a, bool b);      // 0x005DCF20
    void ShowPaintThemeExport();                               // 0x005DD4A0
};
}
namespace SP {
class cRefObject {
public:
    virtual int AddRef();
    virtual int Release();
};
}
namespace SP {
namespace Editor {
struct cEditorLaunchData_s0057_bfb0 {
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x8];
    int mConfig;                          // +0xc
    EA::ResourceMan::Key_s0057_bfb0 mModelKey;       // +0x10
    char pad_1c[0x65 - 0x1c];
    bool m65;                             // +0x65
    char pad_66[0x6e - 0x66];
    bool m6e;                             // +0x6e
    char pad_6f[0x90 - 0x6f];
    uint32_t m90;                         // +0x90
    cRefObject* m94;                      // +0x94
    EA::AutoRefCountX<cEditorLaunchData_s0057_bfb0> mParent;   // +0x98
};
}
}
namespace SP {
class cEditorLaunchState {   // 0x48 bytes, ctor 0x00579C80
public:
    virtual void _v0();
    virtual int AddRef();
    virtual int Release();
    char pad_4[0x8];
    uint32_t m0c;                         // +0xc
    EA::AutoRefCount_s0057_bfb0<cRefObject> m10;     // +0x10
    uint32_t m14;                         // +0x14
    EA::ResourceMan::Key_s0057_bfb0 mKey;            // +0x18
    char pad_24[0x44 - 0x24];
    bool mbActive;                        // +0x44
    bool m45;                             // +0x45
    char pad_46[2];
    cEditorLaunchState();
};
}
namespace SP {
struct cSPEditorModel_s0057_bfb0 {
    char pad_0[0x18];
    char mBlocks[0x58 - 0x18];            // +0x18
    uint32_t m58;                         // +0x58
    const wchar_t* GetFilePath();         // 0x004AE000
};
}
namespace SP {
struct cSkinMeshData { char pad_0[8]; char* mpBegin; char* mpEnd; };   // 12-byte elements
}
namespace SP {
struct cSPEditorSkin {
    char pad_0[0x34];
    cSkinMeshData* mpMesh;                // +0x34
    char pad_38[0x7c - 0x38];
    char* mVertsBegin;                    // +0x7c (20-byte elements)
    char* mVertsEnd;                      // +0x80
    void Rebuild0();                      // 0x004CA6E0
    void Rebuild1();                      // 0x004CB340
    void Rebuild2();                      // 0x004CB820
};
}
namespace SP {
struct UpdateFlags { bool a; bool b; int c; UpdateFlags() : a(false), b(false), c(0) {} };
}
namespace SP {
class cSPEditorSkinManager_s0057_bfb0 {
public:
    cSPEditorSkin* GetSkin(bool create);  // 0x004C49E0
    bool HasPaintData();                  // 0x004C4630
    void ApplyPaintTheme(const wchar_t* path, const wchar_t* dir);   // 0x004C5980
    void Update(int a, int b, UpdateFlags flags);                    // 0x004C38E0
};
}
namespace SP {
struct cPaintThemeSource { void GetPath(uint32_t id, eastl::string16_s0057_bfb0* out); };   // 0x005F9230
}
namespace SP {
cPaintThemeSource* GetPaintThemeSource();                                        // 0x005F7930
}
namespace SP {
namespace EditorUtils {
 bool ExportToXMFAndBlocks(cSPEditorModel_s0057_bfb0* model, cSPEditorSkin* skin, const wchar_t* path); 
}
}
namespace SP {
struct cBakeManager { void Bake(uint32_t themeID); };   // 0x004B2BB0
}
namespace SP {
struct cTrayRow { bool* mpStates; char pad_4[0x10]; };   // 0x14 bytes
}
namespace SP {
class cAppModeEditorBase_s0057_bfb0 {
public:
    struct cSPEditorLocalState {
        char pad_0[8];
        int mBudget;                       // +0x8
        int mState;                        // +0xc
        uint32_t mThemeID;                 // +0x10
        bool mIsPainted;                   // +0x14
        bool mIsModelDirty;                // +0x15
        EA::ResourceMan::Key_s0057_bfb0 mPaintLikeThisKey;   // +0x18
        uint32_t mPaintLikeThisGroupId;    // +0x24
        uint32_t mPaintLikeThisItemId;     // +0x28
    };
    char pad_0[0x24];
    cPropertyList_s0057_bfb0* mpPropList;  // +0x24
    char pad_28[0x50];
    cSPEditorUI_s0057_bfb0* mDevUI;  // +0x78
    char pad_7c[0x1c];
    cSPEditorModel_s0057_bfb0* mEditorSaveModel;  // +0x98
    char pad_9c[0xb4];
    cSPEditorSkinManager_s0057_bfb0* mSaveLoadFactory;  // +0x150
    char pad_154[0x44];
    int mTransitionState;  // +0x198
    char pad_19c[0x4];
    int m1a0;  // +0x1a0
    int m1a4;  // +0x1a4
    int mPendingLaunch;  // +0x1a8
    char pad_1ac[0x20];
    EA::AutoRefCountX<Editor::cEditorLaunchData_s0057_bfb0> mLaunchData;  // +0x1cc
    char pad_1d0[0xd0];
    cBakeManager* mpBakeManager;  // +0x2a0
    char pad_2a4[0x4d];
    bool m2f1;  // +0x2f1
    char pad_2f2[0x4];
    bool m2f6;  // +0x2f6
    char pad_2f7[0x13d];
    cBlockTray* mpBlockTray;  // +0x434
    char pad_438[0x7a];
    bool mIsPainted;  // +0x4b2
    bool mIsModelDirty;  // +0x4b3
    char pad_4b4[0x8];
    EA::AutoRefCount_s0057_bfb0<cEditorLaunchState> mLaunchState;  // +0x4bc
    char pad_4c0[0x18];
    bool* mpTrayStates;  // +0x4d8
    char pad_4dc[0x2c];
    cTrayRow mTrayRows[6];  // +0x508
    bool mTrayActive[6];  // +0x580

    void RefreshBlockTray();                                     // 0x0057BFB0
    void ProcessPendingLaunch();                                 // 0x0057C0E0
    void CreateLaunchState();                                    // 0x0057C1E0
    void SetLocalState(cSPEditorLocalState* state);              // 0x0057C2F0
    void SetTrayState(int index, bool value);                    // 0x0057C530
    bool ExportPaintTheme(bool showDialog);                      // 0x0057C590
    bool IsBlockAllowed(cSPEditorBlock_s0057_bfb0* block);                  // 0x00577C40
    void SetCurrentConfig(int config, EA::ResourceMan::Key_s0057_bfb0 key); // 0x00579720
    void RelaunchFrom(cEditorLaunchState* state);                // 0x0057A710
    int GetCurrentTrayRow();                                     // 0x00576140
};
}
namespace SP {
struct sp_vector_allocator {
    const char* mpName;
    int mFlags;
    void deallocate(void* p) { if (((int*)p)[-1] != 0) operator delete[](p); }
};
}
namespace SP {
template <typename T>
inline void destruct(T* first, T* last)
{
    for (; first < last; ++first)
        first->~T();
}
}
namespace SP {
template <typename T>
class sp_vector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;
    sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector()
    {
        destruct(mpBegin, mpEnd);
        if (mpBegin)
            mAllocator.deallocate(mpBegin);
    }
    size_t size() const { return (size_t)(mpEnd - mpBegin); }
    T& operator[](size_t i) { return mpBegin[i]; }
};
}
namespace SP {
void GetEditorBlocks(void* blockList, sp_vector<EA::AutoRefCount_s0057_bfb0<cSPEditorBlock_s0057_bfb0> >& out);   // 0x00491900
}
namespace EA {
namespace IO {
 int SplitPath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext, int flags); 
}
}
namespace SP {
class cRefCountedBase {
public:
    virtual ~cRefCountedBase() {}
};
}
namespace SP {
struct cSharedPayload {
    char pad_0[8];
    EA::Thread::AtomicInt_s0057_bfb0<int> mRefCount;   // +0x8
    void Destroy() {}
    int Release()
    {
        mRefCount.Decrement();
        if (mRefCount.GetValue() < 1) {
            mRefCount.Increment();
            Destroy();
            return 0;
        }
        return mRefCount.GetValue();
    }
};
}
namespace SP {
template <typename T>
struct IntrusivePtr {
    T* mpObject;
    ~IntrusivePtr() { if (mpObject) mpObject->Release(); }
};
}
namespace SP {
class cPaletteCategory {
public:
    cRefCountedBase mBase;                   // +0x0 (embedded, vtable 0x013EF094)
    char pad_4[0x10];
    IntrusivePtr<cSharedPayload> mpShared;   // +0x14
    char pad_18[0x10];
    sp_vector<char> mItems;                  // +0x28
    ~cPaletteCategory();
};
}
// ---- items of slice s0057bfb0 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
namespace SP { __forceinline void SendEditorStateChanged(); }   // defined at 0x0057c440, called earlier in the TU

// ---- items of slice s0057d710 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cVector4 {
    float x, y, z, w;
    cVector4() {}
    cVector4(const cVector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; }
};
extern cVector4 gTorsoColor;   // 0x0150ce40 (x,y,z,w)
struct ResourceKey_s0057_d710 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
struct Matrix3_s0057_d710 {
    float m[9];
    Matrix3_s0057_d710() {}
    Matrix3_s0057_d710(const Matrix3_s0057_d710& o);
};
struct Matrix3Data { float m[9]; };
struct cMWModel {
    char pad0[4];
    uint32_t mFlags;                    // +0x04
};
struct cSPEditorBlock {
    virtual void Dtor();
    virtual int AddRef();
    virtual int Release();
    char pad4[0x10 - 4];
    cMWModel* mModel;                   // +0x10
    char pad14[0x48 - 0x14];
    float mPositionZ;                   // +0x48
    char pad4c[0xa8 - 0x4c];
    Matrix3Data mBaseOrientation;       // +0xa8
    char padcc[0xdc8 - 0xcc];
    uint32_t mFlagsDC8;                 // +0xdc8
    uint32_t mFlagsDCC;                 // +0xdcc
    char padDD0[0xe08 - 0xdd0];

    cSPEditorBlock();                                             // 0x004346b0
    void SetSymmetrySign(int side);                               // 0x0044e980
    void BuildBlock(uint32_t instance, uint32_t group, void* modelWorld, void* physicsWorld,
                    float scale, bool a, bool b, bool c);         // 0x00441440
    void SetBooleanAttribute(int attr, bool value);               // 0x00435a10
    Matrix3_s0057_d710 GetOrientation();                                     // 0x0044b590
    void SetOrientation(Matrix3_s0057_d710 m);                               // 0x0043ffa0
    float GetDefaultScale(bool b);                                // 0x0044b5c0
    void SetScaleA(float s);                                      // 0x00440020
    void SetScaleB(float s);                                      // 0x00440090
    void Rebuild(void* modelWorld, void* physicsWorld, float scale, bool a, bool b);  // 0x00450f70
    int GetSymmetryIndex();                                       // 0x0044f220
    void FUN_0043e2b0();                                          // 0x0043e2b0
    bool TestFlagDC8(int bit) const { return ((mFlagsDC8 >> bit) & 1) != 0; }
    bool TestFlagDCC(int bit) const { return ((mFlagsDCC >> bit) & 1) != 0; }
};
struct cEditorPhysics {
    void* World();                                                // 0x004b91c0
};
struct cRefCountBase {
    virtual ~cRefCountBase();
    int mnRefCount;
    void AddRef() { ++mnRefCount; }
    void Release() {
        int n = (*(volatile int*)&mnRefCount += -1);
        if (n == 0) {
            mnRefCount = 1;
            delete this;
        }
    }
};
struct cEditorModelBase { virtual void v0(); };
struct cEditorModel_s0057_d710 : cEditorModelBase, cRefCountBase {
    void FUN_004ad110();       // 0x004ad110
    float GetScale();                                             // 0x004adaa0
    cEditorPhysics* GetPhysics();                                 // 0x004ad450
    void AddBlock(cSPEditorBlock* block, bool b);                 // 0x004abaf0
    int GetBlockCount();                                          // 0x004accf0
    cSPEditorBlock* GetBlock(int i);                              // 0x004accb0
    void RemoveBlock(cSPEditorBlock* block, int a, int b);        // 0x004ac8b0
    void FUN_004ad330();                                          // 0x004ad330
};
struct cPaintTheme {
    void ApplyToAsset(cSPEditorBlock* block, int flags);          // 0x004b3190
};
struct cSkinManager {
    void* GetSkin(bool create);          // 0x004c49e0
    void* GetSceneObject(int flags);     // 0x004c45d0
    void  FUN_005d1600(int a, int b);    // 0x005d1600
};
struct cAnimCreatureManager {
    void* GetCreature(void* viewer);     // 0x0059ca70
};
struct cTrayRow_s0057_d710 { bool* mpStates; char pad0[0x10]; };   // 0x14 bytes
struct cAppModeEditorBase_s0057_d710 {
    char pad0[0x70];
    float m70;                          // +0x70
    char pad74[0x84 - 0x74];
    void* mSaveModelWorld;              // +0x84
    char pad88[0x90 - 0x88];
    cEditorPhysics* mPhysics;           // +0x90
    char pad94[0x98 - 0x94];
    cEditorModel_s0057_d710* mEditorSaveModel;     // +0x98
    char pad9c[0xd4 - 0x9c];
    void* mD4;                          // +0xd4
    char padD8[0xe9 - 0xd8];
    bool mTorsoSelected;                // +0xe9
    char padEA[0x14c - 0xea];
    cSkinManager* mSaveSkinManager;     // +0x14c
    cSkinManager* mSaveLoadFactory;     // +0x150
    char pad154[0x1cc - 0x154];
    void* mLaunchData;                  // +0x1cc
    char pad1d0[0x2a0 - 0x1d0];
    cPaintTheme* mPaintTheme;           // +0x2a0
    char pad2a4[0x360 - 0x2a4];
    cAnimCreatureManager* mAnimCreatureManager;  // +0x360
    void* mShadowViewer;                // +0x364
    char pad368[0x385 - 0x368];
    bool mAnimatingCreatureActive;      // +0x385
    char pad386[0x472 - 0x386];
    bool m472;
    char pad473[1];
    float m474;
    char pad478[0x480 - 0x478];
    float m480;
    float m484;
    char pad488[0x48c - 0x488];
    int m48c;
    int m490;
    char pad494[0x4d4 - 0x494];
    bool m4d4;
    char pad4d5[3];
    void* m4d8;                         // +0x4d8
    char pad4dc[0x508 - 0x4dc];
    cTrayRow_s0057_d710 mTrayRows[6];              // +0x508

    void RemoveTorsoFromEffectsMask();                    // 0x005772b0
    void AddTorsoToEffectsMask(cVector4 v);              // 0x0057a610
    void SetTorsoIsSelected(bool);  // 0x0057e160 (cAppModeEditorBase::SetTorsoIsSelected)
    void FUN_00573970();                                  // 0x00573970
    int  GetCurrentTrayRow();                             // 0x00576140
    void UpdateAnimatedCreature();                        // 0x0057ae10
    void FUN_0057e220(float, float, void*, int);
    void FUN_0057e340(bool);
    bool FUN_0057d710(const ResourceKey_s0057_d710& key, cSPEditorBlock** ppBlock, float screenX, float screenY,
                      bool bAssembly);
};
// ---- items of slice s0057d710 end

// ---- items of slice s0057e480 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
void __cdecl operator_delete_array(void* p);                                                    // 0x00F47380
struct cUnkEd80 {
    void* m0;
    void* m4;
    void* m8;
    void FUN_0057cc10(void* p);
    void* Init(void* p, void* unused);
};
void DoInsertValue(void* dst, void* src, int n);   // 0x011e0744 (cdecl)
struct cVec16 {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    void* EraseAfter(void* pos);
};
namespace eastl {
struct allocator_s0057_e480 {};
}
namespace eastl {
template <typename T, typename Alloc = allocator_s0057_e480>
class basic_string_s0057_e480 {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Alloc mAlloc;

    basic_string_s0057_e480() : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(0); }
    basic_string_s0057_e480(const basic_string_s0057_e480& x);                // 0x0056e2d0
    ~basic_string_s0057_e480()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_array(mpBegin);
        }
    }
    void RangeInitialize(const T* p);                   // 0x00579a90
    size_t find_first_not_of(const T* s, size_t pos);   // 0x00579af0
    basic_string_s0057_e480& erase(size_t pos, size_t n);          // 0x004228e0
    void rtrim();                                       // 0x005541e0

    // @ 0x0057eda0
    void trim()
    {
        {
            T ws[3] = { (T)0x20, (T)9, (T)0 };
            erase(0, find_first_not_of(ws, 0));
        }
        return rtrim();
    }
};
}
namespace eastl {
template class basic_string_s0057_e480<wchar_t, allocator_s0057_e480>;
}
void* __cdecl operator new(unsigned int, const char*, int, unsigned int, const char*, int);   // 0x00F473A0
template <class T> inline T& At(void* base, int off) { return *(T*)((char*)base + off); }
struct RC0 { virtual int AddRef(); virtual int Release(); };                        // slots at +0 / +4
struct RC1 { virtual void s0(); virtual int AddRef(); virtual int Release(); };     // slots at +4 / +8
namespace eastl {
struct false_type {};
}
namespace eastl {
struct EASTLAllocator { const char* mpName; EASTLAllocator() {} };
}
namespace eastl {
template <class T> class generic_iterator { public:
    T mIterator;
    explicit generic_iterator(const T& x) : mIterator(x) {}
    const T& base() const { return mIterator; }
};
}
namespace eastl {
template <class T> struct value_of;
}
namespace eastl {
template <class T> struct value_of<T*> { typedef T type; };
}
namespace eastl {
template <class T> struct value_of<const T*> { typedef T type; };
}
namespace eastl {
template <class T> struct has_trivial_relocate : public false_type {};
}
namespace eastl {
template <class In, class Out>
generic_iterator<Out> uninitialized_copy_impl(generic_iterator<In> first, generic_iterator<In> last,
                                              generic_iterator<Out> dest, false_type);
}
namespace eastl {
template <class It, class T>
void uninitialized_fill_n_impl(generic_iterator<It> first, uint32_t n, const T& value, false_type);
}
namespace eastl {
template <class First, class Last, class Result>
inline Result uninitialized_copy_ptr(First first, Last last, Result result)
{
    const generic_iterator<Result> i(uninitialized_copy_impl(generic_iterator<First>(first),
                                                             generic_iterator<Last>(last),
                                                             generic_iterator<Result>(result),
                                                             has_trivial_relocate<typename value_of<Result>::type>()));
    return i.base();
}
}
namespace eastl {
template <class T>
inline void uninitialized_fill_n_ptr(T* first, uint32_t n, const T& value)
{
    uninitialized_fill_n_impl(generic_iterator<T*>(first), n, value, has_trivial_relocate<T>());
}
}
namespace eastl {
template <class Bi1, class Bi2>
inline Bi2 copy_backward_impl(Bi1 first, Bi1 last, Bi2 resultEnd)
{
    while (last != first)
        *--resultEnd = *--last;
    return resultEnd;
}
}
namespace eastl {
template <class T> struct vector_s0057_e480 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    EASTLAllocator mAllocator;

    inline uint32_t GetNewCapacity(uint32_t currentCapacity) { return (currentCapacity > 0) ? (2 * currentCapacity) : 1; }
    inline T* DoAllocate(uint32_t n)
    {
        return n ? (T*)::operator new(n * sizeof(T), "Editor", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL\\allocator.h", 0xd1)
                 : 0;
    }
    inline void DoFree(T* p, uint32_t)
    {
        if (p) {
            if (*((uint32_t*)p - 1))
                operator_delete_array(p);
        }
    }
    T* DoRealloc(uint32_t n, const T* first, const T* last);
    void DoInsertValue(T* position, const T& value);
    void DoInsertValues(T* position, uint32_t n, const T& value);
    vector_s0057_e480& operator=(const vector_s0057_e480& x);
};
}
struct Rec30 {                                   // 0x30-byte element: user copy ctor, trivial assignment
    uint32_t d[12];
    Rec30(const Rec30& o);                       // 0x00576900
};
struct Rec18 { uint32_t d[6]; };                 // 0x18-byte POD element
namespace eastl {
template <class T> T* copy_ool(const T* first, const T* last, T* dest);        // out of line
}
namespace eastl {
template <class T> T* uninitialized_copy_ool(T* first, T* last, T* dest);      // out of line (0x00576A10)
}
namespace eastl {
template <> Rec18* vector_s0057_e480<Rec18>::DoRealloc(uint32_t n, const Rec18* first, const Rec18* last);   // 0x0050E750
}
struct RefElem {                                 // intrusive pointer, AddRef at vtbl+4, Release at vtbl+8
    RC1* p;
    RefElem(const RefElem& o) : p(o.p) { if (p) p->AddRef(); }
    ~RefElem() { if (p) p->Release(); }
};
void* __cdecl MoveMem(void* dst, const void* src, uint32_t n);                  // 0x011E0744
namespace eastl {
template <class T> void fill_ool(T* first, T* last, const T& v);               // 0x00657F20
}
namespace eastl {
template <class T> void copy_backward_ool(T* first, T* last, T* resultEnd);    // 0x005C1DC0
}
struct Block;
struct EditorUI {
    void UpdateUIBasedOnModelSaveability();                       // 0x005DD7A0
    char F5dc450();                                                // 0x005DC450
    void F5dd090(int);                                             // 0x005DD090
    void EnableBasicEditorButtons(int, int);                       // 0x005DE690
    void* F5dc2b0();                                               // 0x005DC2B0
    void* F5dc2c0();                                               // 0x005DC2C0
};
struct MsgServer_s0057_e480 { virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
                   virtual void PostMessage(uint32_t id, void* data, int flags);   // +0x14
                   virtual void PostMessage4(uint32_t id, int a, int b, int c); };  // +0x18
MsgServer_s0057_e480* __cdecl GetMessageServer();                             // 0x0067DCC0
struct SetNameMsg { void* src; uint32_t pad4; const wchar_t* name; uint32_t pad2; uint32_t zero; uint32_t pad3;
                  SetNameMsg(void* s, const wchar_t* n) { zero = 0; src = s; name = n; } };
struct Block : RC1 {                             // cSPEditorBlock
    uint32_t pad[0x371];
    uint32_t mFlags;                             // +0xDC8
    bool FlagBit(int n) const { return ((mFlags >> n) & 1) != 0; }
    void F43ce40();                              // 0x0043CE40
    void F43a9a0(int, uint32_t);                 // 0x0043A9A0
    char HasAnyBlockFlag();                      // 0x00435D40
    void F43c710();                              // 0x0043C710
    void F43cad0();                              // 0x0043CAD0
};
struct BlockRef {                                // AutoRefCount<Block>
    Block* p;
    void Set(Block* b);                          // 0x004B09B0
};
struct Handle { Block* GetRigblock(); };         // 0x0047E6C0
struct SkinMgr { void* GetSkin(int); };          // 0x004C49E0
struct PaletteUI { char IsPaintByNumber(); };    // 0x005CA920
struct AnimMgr { char IsPlayingAnimation(int); };   // 0x0059CD20
struct Flagged { uint32_t pad[7]; char mFlag; }; // byte at +0x1c
Flagged* __cdecl AssetBrowser();                 // 0x00401030
Flagged* __cdecl SporeGuide();                   // 0x00401040
struct EventInfo : RC1 {                         // cSPEditorAnimatedEventInfo, 0x30 bytes
    uint32_t pad[11];
    EventInfo();                                 // 0x0059D960
    void MessagePost(uint32_t id, int a, void* model, int b, int c, float f0, int d, int e, float f1);   // 0x0059D840
};
struct EventRef {                                // AutoRefCount<EventInfo> built from a raw pointer
    EventInfo* p;
    EventRef(EventInfo* e);                      // 0x0061DF40
};
struct Mask16 { uint32_t d[4]; Mask16() {} };
struct cEditorBase {
    char IsMousedOverModel(float x, float y);    // 0x00573A60
    char HasSkin();                              // 0x00577620
    void F57e340(int);                           // 0x0057E340
    void F573970();                              // 0x00573970
    void SomeLoader();                           // 0x00577DD0
    void F5724a0();                              // 0x005724A0
    void RemoveTorsoFromEffectsMask();           // 0x005772B0
    void SetRolloverHandle(int, int);            // 0x00573D70
    void UpdateBaker();                          // 0x0057E8A0
    void UpdateIdleAnimations(float x, float y, uint32_t dt);   // 0x0057E480
    void SetSelectedBlock(Block* b, uint32_t p);                // 0x0057E790
    void SaveMetadata();                         // 0x0057EA30
    void BakerInit();                            // 0x0057EBF0
    void SetModelName(const wchar_t* name);      // 0x0057ED00
    Mask16 BuildPartMask(int, int, int);         // 0x0057AC00
};
struct IModel { virtual void v0(); virtual uint32_t V1(); virtual void v2(); virtual uint32_t V3(); };
struct IMeta : RC0 { void Fill(uint32_t, uint32_t, const wchar_t*); };   // 0x005519D0
struct IRes : RC0 { virtual void v2(); virtual IMeta* QueryMeta(uint32_t type); };
inline IMeta* QueryAddRef(IRes* r)
{
    IMeta* m = r->QueryMeta(0x30bdee3);
    if (m)
        m->AddRef();
    return m;
}
struct IResMan { virtual void m0(); virtual void m1(); virtual void m2();
                 virtual bool GetResource(void* key, IRes** out, int, int, int, int);   // +0x0c
                 virtual void m4(); virtual void m5(); virtual void m6(); virtual void m7();
                 virtual void SaveResource(IMeta*, int, int, int, int); };              // +0x20
IResMan* __cdecl GetManager();                                      // 0x0067DCD0
int __cdecl GetSaveArea(int);                                       // 0x006B1F90
struct Thumb {
    void UpdateExportThumb(void* key);                              // 0x005FB430
};
Thumb* __cdecl GetThumb();                                          // 0x005F7930
struct TokTrans {
    void SetOldModelName(const wchar_t*);                           // 0x005D6090
};
extern TokTrans* gTokTrans;                                         // 0x015EEBEC
struct Hints {
    void F67c420();                                                 // 0x0067C420
};
Hints* __stdcall GetHints(int, int);                                // 0x0067CAC0
struct INameProv { virtual void v0(); virtual const wchar_t* GetName(); virtual void v2(); virtual void v3(); virtual void v4();
                   virtual const wchar_t* GetName5(); };
struct WStr16 { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t a;
                void Assign(const wchar_t* b, const wchar_t* e); };   // 0x00423650
struct IUnk { virtual void* v0(); virtual void* V1(int); };
struct ResKey { uint32_t instance, type, group;
                ResKey() {}
                ResKey(const ResKey& o) : instance(o.instance), type(o.type), group(o.group) {} };
struct ResHolder { IRes* p; ResHolder() : p(0) {} ~ResHolder() { if (p) p->Release(); } };
struct EditorModel {                             // cSPEditorModel
    virtual void v0(); virtual uint32_t V1(); virtual void v2(); virtual uint32_t V3();
    uint32_t pad[2];
    ResKey mKey;                                 // +0x0C
    uint32_t pad2[16];
    uint32_t m58;                                // +0x58
    char F4acfd0();                              // 0x004ACFD0
    void F4ad1a0();                              // 0x004AD1A0
};
struct LaunchData { uint32_t pad[0x19]; char pad1[1]; char m65; char pad2[2]; uint32_t pad3[0x24 - 0x1a]; uint32_t m90; RC0* m94; };
struct BakerData : RC1 {                         // 0x48 bytes
    uint32_t pad[2];
    uint32_t mField0c;                           // +0x0C
    RC0* mRef10;                                 // +0x10
    uint32_t mField14;
    ResKey mKey;                                 // +0x18
    WStr16 mName;                                // +0x24
    uint32_t mField34, mField38, mField3c, mField40;
    char mByte44, mByte45;
    BakerData();                                 // 0x00579C80
    void SetField34(uint32_t v) { mField34 = v; }
    void SetField3c(uint32_t v) { mField3c = v; }
    void SetField40(uint32_t v) { mField40 = v; }
};
struct BakerMsg { uint32_t id; short a; short b; BakerMsg() {} };
struct BakerSvc { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void Post(void* key, void* msg); };   // +0x4c
BakerSvc* __cdecl GetBakerSvc();                                   // 0x00401010
struct cEditorBase;
void __cdecl InvalidEditorModelKey(ResKey* k, int);                 // 0x0068C700
struct GAppProps { uint32_t pad[15]; void* p3c; };
extern GAppProps* gAppProperties;                                   // 0x015FD918
namespace EA {
 eastl::basic_string_s0057_e480<wchar_t> ConvertToString16(const char* s, int len);   // 0x0093C5A0
}
struct ListUI { virtual void BeginList(const wchar_t*); virtual void EndList(const wchar_t*); };
bool __cdecl UpdateEffectsAndObjectsStats(ListUI* ui, int, char* entry, const wchar_t* type);   // 0x0057C940
struct CharVec { char* mpBegin; char* mpEnd; };
// ---- items of slice s0057e480 end

// ---- items of slice s0057f6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString[];   // 0x01667bac
extern const float kPainterRangeMin;   // 0x013ec478
extern const float kPainterRangeMax;   // 0x013f0318
struct ResourceKey_s0057_f6c0 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
template <class T> inline void intrusive_ptr_add_ref(T* p) { p->AddRef(); }
template <class T> inline void intrusive_ptr_release(T* p) { p->Release(); }
template <class T> class intrusive_ptr {
public:
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    intrusive_ptr(T* p) : mpObject(p) { if (mpObject) intrusive_ptr_add_ref(mpObject); }
    ~intrusive_ptr() { if (mpObject) intrusive_ptr_release(mpObject); }
    intrusive_ptr& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                intrusive_ptr_add_ref(pObject);
            mpObject = pObject;
            if (pTemp)
                intrusive_ptr_release(pTemp);
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
namespace eastl {
template <class T> struct basic_string_s0057_f6c0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    basic_string_s0057_f6c0() : mpBegin(gEmptyString), mpEnd(gEmptyString), mpCapacity(gEmptyString + 1) {}
    ~basic_string_s0057_f6c0() { DeallocateSelf(); }
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator delete[](mpBegin);
        }
    }
    const T* c_str() const { return mpBegin; }
    basic_string_s0057_f6c0& sprintf(const T* pFormat, ...);   // 0x0041e050
};
}
namespace eastl {
typedef basic_string_s0057_f6c0<wchar_t> wstring;
}
namespace eastl {
template <class T> struct sp_vector_s0057_f6c0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator[2];
    sp_vector_s0057_f6c0() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~sp_vector_s0057_f6c0()
    {
        if (mpBegin && ((uint32_t*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
};
}
namespace eastl {
template <unsigned int N> struct bitset_s0057_f6c0 {
    uint32_t mWord[(N + 31) / 32];
};
}
namespace Resource {
class IKeyFilter {
public:
    virtual ~IKeyFilter() {}
    virtual bool IsValid(const ResourceKey_s0057_f6c0& name) = 0;
};
}
namespace Resource {
class StandardFileFilter : public IKeyFilter {
public:
    StandardFileFilter(uint32_t instance, uint32_t group, uint32_t type, uint32_t mask)
        : instanceID(instance), groupID(group), typeID(type), groupMask(mask) {}
    virtual ~StandardFileFilter() {}
    virtual bool IsValid(const ResourceKey_s0057_f6c0& name);
    uint32_t instanceID;   // +0x04
    uint32_t groupID;      // +0x08
    uint32_t typeID;       // +0x0c
    uint32_t groupMask;    // +0x10
};
}
namespace Resource {
class Database {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual const wchar_t* GetLocation();               // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual bool DeleteRecord(const ResourceKey_s0057_f6c0& name);  // +0x40
};
}
namespace Resource {
class IResourceManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual int GetRecordKeyList(eastl::sp_vector_s0057_f6c0<ResourceKey_s0057_f6c0>& dst, IKeyFilter* filter,
                                 eastl::sp_vector_s0057_f6c0<Database*>* pDstDatabases);          // +0x38
    virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void FlushCache(void* pCache, IKeyFilter* pFilter);                        // +0x70
    virtual void v74(); virtual void v78(); virtual void v7c();
    virtual bool SetKeyName(const ResourceKey_s0057_f6c0& key, const wchar_t* fileName);         // +0x80
};
}
namespace Resource {
IResourceManager* GetManager_s0057_f6c0();   // 0x0067dcd0
}
namespace Resource {
extern void (*CreateNameFromKey)(ResourceKey_s0057_f6c0* key, eastl::wstring* dst, IResourceManager* pManager,
                                 Database* pDatabase, const wchar_t* name);   // [0x0154c468]
}
class cPropertyList_s0057_f6c0;
bool GetFloatProperty(cPropertyList_s0057_f6c0* pList, uint32_t propertyID, float& dst);   // 0x0040cf10
class cEditorModelStream {
public:
    cEditorModelStream();   // 0x004b9c70
    virtual int AddRef();   // +0
    virtual int Release();  // +4
    uint32_t mData[(0xac - 4) / 4];
};
class DefaultRefCounted {
public:
    virtual ~DefaultRefCounted();
    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = mnRefCount - 1;
        mnRefCount = n;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return mnRefCount;
    }
    int mnRefCount;   // +0x08 of the model
};
class cISPEditorNameProvider_s0057_f6c0 {
public:
    virtual void SetName(const wchar_t* name);             // +0x0
    virtual const wchar_t* GetName();                      // +0x4
    virtual void SetDescription(const wchar_t* desc);      // +0x8
    virtual const wchar_t* GetDescription();               // +0xc
};
class cSPEditorModel_s0057_f6c0 : public cISPEditorNameProvider_s0057_f6c0, public DefaultRefCounted {
public:
    cSPEditorModel_s0057_f6c0();   // 0x004ab690 (0xe0 bytes)
    ResourceKey_s0057_f6c0 mKey;   // +0x0c
    uint32_t mData[(0xe0 - 0x18) / 4];
    void FUN_004ad330();                                                        // 0x004ad330
    bool LoadFromBinary(cEditorModelStream* pStream);                           // 0x004ae3b0
    bool SaveResource(cEditorModelStream* pStream);                             // 0x004af260
    bool FUN_004ae260(void* pModelWorld, int a, int b, bool c);                 // 0x004ae260
    void FUN_004ad6f0(eastl::sp_vector_s0057_f6c0<uint32_t>& dst);                         // 0x004ad6f0
    void FUN_004ada40(eastl::sp_vector_s0057_f6c0<uint32_t>& src);                         // 0x004ada40
    const wchar_t* GetFileName();                                               // 0x004ae000
};
class cSPEditorUI_s0057_f6c0 {
public:
    void UpdateUIBasedOnModelSaveability();           // 0x005dd7a0
    void ShowGeneralMessage(const wchar_t* message);  // 0x005dc460
};
struct cSkinMesh {
    uint32_t pad0[2];
    ResourceKey_s0057_f6c0* mpBegin;   // +0x08
    ResourceKey_s0057_f6c0* mpEnd;     // +0x0c
};
struct cSkinVertex { uint32_t mData[5]; };
class cSkinObject_s0057_f6c0 {
public:
    uint32_t pad0[0x34 / 4];
    cSkinMesh* mpMesh;           // +0x34
    uint32_t pad38[(0x7c - 0x38) / 4];
    cSkinVertex* mpVertsBegin;   // +0x7c
    cSkinVertex* mpVertsEnd;     // +0x80
    void BuildSkeleton();        // 0x004ca6e0
    void FUN_004cb340();         // 0x004cb340
    void FUN_004cb820();         // 0x004cb820
    __forceinline bool IsMeshValid() { return mpMesh && (mpMesh->mpEnd - mpMesh->mpBegin) == (mpVertsEnd - mpVertsBegin); }
};
struct cSkinUpdateFlags {
    bool mbA;
    bool mbB;
    cSkinUpdateFlags() : mbA(false), mbB(false) {}
};
class cSPEditorSkinManager_s0057_f6c0 {
public:
    cSkinObject_s0057_f6c0* GetSkin(int index);                                  // 0x004c49e0
    bool IsSkinUpToDate();                                            // 0x004c4630
    void Update(int a, int b, cSkinUpdateFlags flags, int c);         // 0x004c38e0
    void ExportSkin(const wchar_t* pDir, const wchar_t* pName);       // 0x004c5980
};
class cEditorPainter {   // 0x88 bytes
public:
    cEditorPainter();                                                 // 0x004c2bc0
    virtual int AddRef();   // +0
    virtual int Release();  // +4
    void Shutdown();                                                  // 0x004c4eb0
    void Init(void* pEditor, cSPEditorModel_s0057_f6c0* pModel, void* pModelWorld);   // 0x004c3070
    void SetRange(float a, float b);                                  // 0x004c5100
    void SetUpToDate(bool b);                                         // 0x004c4650
    uint32_t mData[(0x88 - 4) / 4];
};
class cSPEditorBlock_s0057_f6c0 {
public:
    virtual void v00();
    virtual int AddRef();    // +4
    virtual int Release();   // +8
    void FUN_0043a9a0(int a, int b);   // 0x0043a9a0
    uint32_t pad[(0xdc8 - 4) / 4];
    uint32_t mFlags;                   // +0xdc8
    bool IsLocked() const { return (mFlags >> 1) & 1; }
};
class cSPEditorHandle_s0057_f6c0 {
public:
    cSPEditorBlock_s0057_f6c0* GetRigblock();     // 0x0047e6c0
};
namespace UI {
class BehaviorMessage_s0057_f6c0 {
public:
    BehaviorMessage_s0057_f6c0() : mID(0) { _InterlockedExchange(&mnRefCount, 0); }
    virtual void v00();
    virtual int AddRef();    // +4
    virtual int Release();   // +8
    long mnRefCount;         // +0x04
    uint32_t pad08[10];
    uint32_t mID;            // +0x30
    uint32_t pad34;
};
}
class cEditorSavedMessage : public UI::BehaviorMessage_s0057_f6c0 {   // 0x40 bytes
public:
    cEditorSavedMessage() : m38(0) {}
    uint32_t m38;            // +0x38
    uint32_t pad3c;
};
void SetMessageString(UI::BehaviorMessage_s0057_f6c0* pMsg, int index, const wchar_t* text);   // 0x0057cd40
class IMessageManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t messageID, void* pMessage, void* pSource);   // +0x14
};
struct cEditorRequest {
    uint32_t mID;
    uint16_t mA;
    uint16_t mB;
};
class cEditorRequestHandler {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void Request(const ResourceKey_s0057_f6c0& key, cEditorRequest* pRequest);   // +0x4c
};
cEditorRequestHandler* GetEditorRequestHandler();   // 0x00401010
namespace SP {
Resource::Database* GetSaveArea(uint32_t id);   // 0x006b1f90
}
namespace SP {
bool IsSaveArea(Resource::Database* pDatabase);   // 0x006b1f60
}
namespace SP {
IMessageManager* MessageServer_s0057_f6c0();               // 0x0067dcc0
}
namespace SP {
namespace EditorUtils {
void ExportToXMFAndBlocks(cSPEditorModel_s0057_f6c0* pModel, cSkinObject_s0057_f6c0* pSkin, const wchar_t* pDir);   // 0x004629e0
}
}
void FUN_004b7660(cSPEditorModel_s0057_f6c0* pModel);                                       // 0x004b7660
void FUN_006ad030(const ResourceKey_s0057_f6c0& key);                                       // 0x006ad030
void FUN_004647b0(cSPEditorModel_s0057_f6c0* pModel, cSkinObject_s0057_f6c0* pSkin, const wchar_t* pDir);   // 0x004647b0
void FUN_0046eae0(cSkinObject_s0057_f6c0* pSkin, const wchar_t* pPath);                     // 0x0046eae0
namespace SP {
class cAppModeEditorBase_s0057_f6c0 {
public:
    uint32_t pad00[0x24 / 4];
    cPropertyList_s0057_f6c0* mpConfigProperties;                       // +0x24
    uint32_t pad28[(0x48 - 0x28) / 4];
    eastl::bitset_s0057_f6c0<128> mModelValidity;                       // +0x48
    eastl::bitset_s0057_f6c0<128> mModelSaveValidity;                   // +0x58
    uint32_t pad68[(0x78 - 0x68) / 4];
    cSPEditorUI_s0057_f6c0* mpUI;                                       // +0x78
    uint32_t pad7c[(0x88 - 0x7c) / 4];
    void* mpSaveModelWorld;                                  // +0x88
    uint32_t pad8c[(0x98 - 0x8c) / 4];
    cSPEditorModel_s0057_f6c0* mpEditorSaveModel;                       // +0x98
    intrusive_ptr<cSPEditorModel_s0057_f6c0> mpEditorModel;             // +0x9c
    uint32_t padA0[(0xd4 - 0xa0) / 4];
    intrusive_ptr<cSPEditorBlock_s0057_f6c0> mpSelectedBlock;           // +0xd4
    uint32_t padD8[(0xe4 - 0xd8) / 4];
    cSPEditorHandle_s0057_f6c0* mpRolloverHandle;                       // +0xe4
    bool mbE8;                                               // +0xe8
    bool mbTorsoInEffectsMask;                               // +0xe9
    uint16_t padEA;
    int mnEC;                                                // +0xec
    uint32_t padF0[(0x150 - 0xf0) / 4];
    cSPEditorSkinManager_s0057_f6c0* mpSkinManager;                     // +0x150
    intrusive_ptr<cEditorPainter> mpPainter;                 // +0x154
    uint32_t pad158[(0x2ac - 0x158) / 4];
    uint32_t mSaveAreaID;                                    // +0x2ac
    uint32_t pad2b0[(0x2f0 - 0x2b0) / 4];
    bool mb2f0;
    bool mIsCreatureEditor;                                  // +0x2f1
    uint16_t pad2f2;
    uint32_t pad2f4[(0x31c - 0x2f4) / 4];
    int mEditorMode;                                         // +0x31c
    uint32_t pad320[(0x38c - 0x320) / 4];
    int mn38C;                                               // +0x38c
    uint32_t pad390[(0x4b0 - 0x390) / 4];
    bool mb4b0;
    bool mb4b1;
    bool mb4b2;                                              // +0x4b2
    bool mb4b3;                                              // +0x4b3
    bool mb4b4;                                              // +0x4b4

    eastl::bitset_s0057_f6c0<128> BuildPartMask(cEditorModelStream* pStream, const wchar_t* pName, bool bSave);   // 0x0057ac00
    void RemoveTorsoFromEffectsMask();                                   // 0x005772b0
    void SetRolloverHandle(cSPEditorHandle_s0057_f6c0* pHandle, bool b);            // 0x00573d70
    void FUN_00573c00(int a, int b);                                     // 0x00573c00

    __forceinline void RebuildSkin(cSkinObject_s0057_f6c0* pSkin)
    {
        mpSkinManager->Update(0, 1, cSkinUpdateFlags(), 0);
        pSkin->BuildSkeleton();
        pSkin->FUN_004cb340();
        pSkin->FUN_004cb820();
    }
    __forceinline cSkinObject_s0057_f6c0* GetSkin() { return mpSkinManager ? mpSkinManager->GetSkin(1) : 0; }

    void SaveModel(const ResourceKey_s0057_f6c0& key, int saveMode);  // 0x0057f6c0 (SP::cAppModeEditorBase::SaveModel)
};  // namespace SP
}
// ---- items of slice s0057f6c0 end

// ---- items of slice s005802f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void WStr_Format(void* out, const wchar_t* fmt, int value);   // 0x0041e050
void GetPropertyAsText(void* list, uint32_t id, void* out);  // 0x006a1360
void* FUN_00607a60();                              // AuthManager
void  EA_IO_MakeFileNameValid(const wchar_t* src, wchar_t* dst, int flags);  // 0x00931250
void  eastl_deallocate(void* p);                   // 0x00f47380
extern "C" wchar_t* wcsncpy(wchar_t* dst, const wchar_t* src, size_t n);
namespace eastl {
struct allocator_s0058_02f0 {};
}
namespace eastl {
template <typename T, typename A = allocator_s0058_02f0>
struct basic_string_s0058_02f0 {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAlloc;
};
}
typedef eastl::basic_string_s0058_02f0<wchar_t> string16_s0058_02f0;
struct cString {
    char mData[20];
    void Init();                 // 0x006b5060
    const wchar_t* c_str();      // 0x006b5240
    int GetValue();              // 0x006b55c0
};
struct cAppModeEditorBase_s0058_02f0 {
    char pad0[0x24];
    void* mPropList;             // +0x24

    bool GetEditorName(string16_s0058_02f0* out);  // 0x005805e0 (cAppModeEditorBase::GetEditorName)
    bool GetDefaultModelName(string16_s0058_02f0* out);  // 0x00580670 (cAppModeEditorBase::GetDefaultModelName)
};
struct cBoolVec {
    void* mpBegin;
    void* mpEnd;
    void EraseAll();
};
// ---- items of slice s005802f0 end

// ---- items of slice s00582250 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* memcpy(void* dst, const void* src, size_t n);
extern "C" size_t strlen(const char* s);
#pragma intrinsic(strlen)
namespace SP {
struct Vector3_s0058_2250 {
    float x, y, z;
    Vector3_s0058_2250() {}
    Vector3_s0058_2250(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s0058_2250(const Vector3_s0058_2250& v) : x(v.x), y(v.y), z(v.z) {}
};
}
namespace SP {
extern char gEmptyString_s0058_2250[1];                          // 0x01667bac
extern char sz_13ec47c[];                                        // 0x013ec47c (shared empty string)
}
namespace SP {
template<class T> struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~vector()
    {
        if (mpBegin && ((int*)mpBegin)[-1] != 0)
            operator delete[](mpBegin);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    void DoInsertValue(T* position, const T& value);  // 0x004558a0
    void push_back(const T& value)
    {
        if (mpEnd < mpCapacity)
            ::new(mpEnd++) T(value);
        else
            DoInsertValue(mpEnd, value);
    }
};
}
namespace SP {
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    char* DoAllocate(size_t n) { return new("Editor", 0, 0, "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) char[n]; }
    void DoFree(char* p) { if (p) operator delete[](p); }
    void AllocateSelf(size_t n)
    {
        if (n > 1) {
            mpBegin = DoAllocate(n);
            mpCapacity = mpBegin + n;
        } else {
            mpBegin = gEmptyString_s0058_2250;
            mpCapacity = gEmptyString_s0058_2250 + 1;
        }
    }
    void RangeInitialize(const char* pBegin, const char* pEnd)
    {
        const size_t n = (size_t)(pEnd - pBegin);
        AllocateSelf(n + 1);
        memcpy(mpBegin, pBegin, n);
        mpEnd = mpBegin + (pEnd - pBegin);
        *mpEnd = 0;
    }
    string(const char* p) { RangeInitialize(p, p + strlen(p)); }
    ~string()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin);
    }
    const char* c_str() const { return mpBegin; }
};
}
namespace SP {
bool operator==(const string& a, const char* b);      // 0x00555020
}
namespace SP {
struct cSPEditorBlock_s0058_2250;
}
namespace SP {
struct cBlockState {                                  // returned by 0x0043c240
    uint32_t pad0[0x180 / 4];
    float mValue;                                     // +0x180
};
}
namespace SP {
struct cBlockModelLink {                              // block +0x28
    bool Get4adc40();                                 // 0x004adc40
    void Set4adc20(bool b);                           // 0x004adc20
};
}
namespace SP {
struct cSPEditorBlock_s0058_2250 {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[(0x28 - 0x04) / 4];
    cBlockModelLink* mpLink;                          // +0x28
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    Vector3_s0058_2250 mPosition;                                // +0x48
    uint32_t pad54[(0x1d0 - 0x54) / 4];
    float mTwist;                                     // +0x1d0
    float pad1d4;
    float mScale;                                     // +0x1d8
    float mScaleTarget;                               // +0x1dc
    float mMinScale;                                  // +0x1e0
    float mMaxScale;                                  // +0x1e4
    uint32_t pad1e8[(0x218 - 0x1e8) / 4];
    float mHandleMin;                                 // +0x218
    float mHandleMax;                                 // +0x21c
    uint32_t pad220[(0x33c - 0x220) / 4];
    cSPEditorBlock_s0058_2250* mpParent;                         // +0x33c
    vector<cSPEditorBlock_s0058_2250*> mChildren;                // +0x340
    uint32_t pad350[(0x460 - 0x350) / 4];
    const char* mpName;                               // +0x460
    uint32_t pad464[(0xdc8 - 0x464) / 4];
    uint32_t mFlags;                                  // +0xdc8

    bool IsLocked() const      { return (mFlags >> 3) & 1; }
    bool IsScalable() const    { return (mFlags >> 7) & 1; }
    bool HasTwist() const      { return (mFlags >> 10) & 1; }
    bool HasState() const      { return (mFlags >> 11) & 1; }

    void SetTwist(float v);                           // 0x0043eae0
    cBlockState* GetState();                          // 0x0043c240
    void SetState(cBlockState* s, float v, int a, int b);  // 0x0043c450
    void StateChanged();                              // 0x00449ce0
    void SetScaleTarget(float v, int b);              // 0x00440020
    float GetHandleValue();                           // 0x0043eed0
};
}
namespace SP {
template<class T> struct intrusive_ptr_s0058_2250 {
    T* mpObject;
    intrusive_ptr_s0058_2250(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~intrusive_ptr_s0058_2250() { if (mpObject) mpObject->Release(); }
    intrusive_ptr_s0058_2250& operator=(T* pObject);             // out of line: 0x004b09b0
    __forceinline void reset(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};
}
namespace SP {
struct cSPEditorHandle_s0058_2250 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual int GetType();                            // +0x10
    cSPEditorBlock_s0058_2250* GetRigblock();                    // 0x0047e6c0
};
}
namespace SP {
struct cSPEditorModel_s0058_2250 {
    uint32_t pad0[0x58 / 4];
    uint32_t mModelType;                              // +0x58
};
}
namespace SP {
struct cSPEditorSkeleton {                            // editor +0x14c
    uint32_t pad0[0xe8 / 4];
    cSPEditorBlock_s0058_2250* mpSymmetryRoot;                   // +0xe8
    cSPEditorBlock_s0058_2250* mpFirstBlock;                     // +0xec
    void Update5d2790();                              // 0x005d2790
};
}
namespace SP {
struct TorsoFlags {
    bool a;
    bool b;
};
}
namespace SP {
struct cSPEditorSkinManager_s0058_2250 {
    void UpdateTorso(TorsoFlags flags, int x);        // 0x004c3230
};
}
namespace SP {
struct cSPEditorLimbStructure_s0058_2250 {
    uint32_t data[0x44 / 4];
    cSPEditorLimbStructure_s0058_2250();                         // 0x00488850
    ~cSPEditorLimbStructure_s0058_2250();                        // 0x00488900
    void Build(cSPEditorBlock_s0058_2250* limb, int a, int b);   // 0x004891a0
    void FixAllJoints();                              // 0x00489ae0
    void Apply();                                     // 0x00488980
};
}
namespace SP {
void ScaleBlock(cSPEditorBlock_s0058_2250* block, float amount);                 // 0x004a5b30
}
namespace SP {
Vector3_s0058_2250 GetBlockCenter(cSPEditorBlock_s0058_2250* block);                        // 0x004a5d10
}
namespace SP {
float GetBlockRadius(cSPEditorBlock_s0058_2250* block);                          // 0x004a5c40
}
namespace SP {
cSPEditorBlock_s0058_2250* GetScaleParent(cSPEditorBlock_s0058_2250* block);                // 0x004a5970
}
namespace SP {
void MoveHandle(cSPEditorHandle_s0058_2250* handle, float amount);               // 0x00496b60
}
namespace SP {
void ApplyBlockScale(cSPEditorBlock_s0058_2250* block, float scale, int a, int b); // 0x0049e6a0
}
namespace SP {
void SnapBlock(cSPEditorBlock_s0058_2250* b, int, int, int, int, int, int, int); // 0x004a6d20
}
namespace SP {
cSPEditorBlock_s0058_2250* FindClosestSymmetry(Vector3_s0058_2250 point, cSPEditorBlock_s0058_2250* block);  // 0x0049c570
}
namespace SP {
void PlaceSymmetric(cSPEditorBlock_s0058_2250* block, Vector3_s0058_2250 pos, Vector3_s0058_2250 dir,
                    cSPEditorSkinManager_s0058_2250* skin, bool keepZ, float eps);  // 0x0049d6b0
}
namespace SP {
void GetAllLimbs(cSPEditorBlock_s0058_2250* block, vector<cSPEditorBlock_s0058_2250*>* out, bool unique);  // 0x004a0020
}
namespace SP {
void SetSoundSymbol(uint32_t a, uint32_t b, const char* name);       // 0x00572070
}
namespace SP {
void PlayEditorSound(uint32_t a, uint32_t b, float v, int c);         // 0x00435f40
}
namespace SP {
float CalculateModelSize(cSPEditorModel_s0058_2250* model);                      // 0x0048ca10
}
namespace SP {
class cAppModeEditorBase_s0058_2250 {
public:
    uint32_t pad0[0x98 / 4];
    cSPEditorModel_s0058_2250* mpEditorModel;                    // +0x98
    uint32_t pad9c[(0x14c - 0x9c) / 4];
    cSPEditorSkeleton* mpSkeleton;                    // +0x14c
    cSPEditorSkinManager_s0058_2250* mpSkinManager;              // +0x150
    uint32_t pad154[(0x20c - 0x154) / 4];
    uint8_t pad20c[2];
    bool mbPlayModelSizeSound;                        // +0x20e

    bool IsManipulatorEnabled(uint32_t id);           // 0x005740e0
    bool OnBlockWheel(cSPEditorBlock_s0058_2250* block, cSPEditorHandle_s0058_2250* handle, int wheelDelta);
};
}
// ---- items of slice s00582250 end

// ---- items of slice s00582fe0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kAngleScale;                                  // 0x015e50a0
extern const float kCreatureSpeed;                               // 0x015e4f9c
struct Vector3_s0058_2fe0 {
    float x, y, z;
    Vector3_s0058_2fe0() {}
    Vector3_s0058_2fe0(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
    Vector3_s0058_2fe0(const Vector3_s0058_2fe0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Matrix3_s0058_2fe0 {
    Vector3_s0058_2fe0 row[3];
    Matrix3_s0058_2fe0(const Matrix3_s0058_2fe0& m);                                   // 0x0041cb40
};
extern const Vector3_s0058_2fe0 kVecDefault;                                // 0x015e4f18
extern const Vector3_s0058_2fe0 kAxisUp;                                    // 0x015e5024
extern const Vector3_s0058_2fe0 kApproachDir;                               // 0x015e50a4
float RandomFloatRange(float lo, float hi);                      // 0x00572a10
float RandomFloat(float range);                                  // 0x00572a60
Matrix3_s0058_2fe0 MakeRotation(const Vector3_s0058_2fe0& axis, float angle);          // 0x00453b20
float SignedAngle(const Vector3_s0058_2fe0& a, const Vector3_s0058_2fe0& b, const Vector3_s0058_2fe0& axis, bool c);  // 0x0069b760
Vector3_s0058_2fe0 GetModelCenter(struct cSPEditorModel_s0058_2fe0* pModel);           // 0x0046bfd0
bool FUN_004a0ac0(struct cSPEditorModel_s0058_2fe0* pModel);                // 0x004a0ac0
struct cSPEditorModel_s0058_2fe0 {
    uint32_t pad00[0x10 / 4];
    uint32_t mTypeID;                                            // +0x10
    uint32_t pad14[(0x58 - 0x14) / 4];
    uint32_t mModelType;                                         // +0x58
};
struct cSkinMesh_s0058_2fe0 {
    uint32_t pad0[2];
    char* mpBegin;                                               // +0x08 (12-byte entries)
    char* mpEnd;                                                 // +0x0c
};
struct cSkinObject_s0058_2fe0 {
    uint32_t pad0[0x34 / 4];
    cSkinMesh_s0058_2fe0* mpMesh;                                           // +0x34
    uint32_t pad38[(0x7c - 0x38) / 4];
    char* mpVertsBegin;                                          // +0x7c (20-byte entries)
    char* mpVertsEnd;                                            // +0x80
    void BuildSkeleton();                                        // 0x004ca6e0
    void FUN_004cb340();                                         // 0x004cb340
    void FUN_004cb820();                                         // 0x004cb820
    __forceinline bool IsMeshValid()
    {
        return mpMesh && (mpMesh->mpEnd - mpMesh->mpBegin) / 12 == (mpVertsEnd - mpVertsBegin) / 20;
    }
};
struct cSkinHolder {
    cSkinObject_s0058_2fe0* GetSkin(int index);                             // 0x004c49e0
    bool IsSkinUpToDate();                                       // 0x004c4630
    void Update(int a, int b, cSkinUpdateFlags flags, int c);    // 0x004c38e0
};
struct cCreatureStructure_s0058_2fe0 {
    void FUN_0059b390();                                         // 0x0059b390
};
struct cCreatureExtra {                                          // creature +0x180
    uint32_t pad00[0x6c / 4];
    float mSize;                                                 // +0x6c
};
struct cCreatureEffects {
    void FUN_009cb4f0();                                         // 0x009cb4f0
};
struct cEditorCreature {
    virtual void SetModelResource(void* pResource);              // +0x00
    uint32_t pad04[(0x3c - 0x04) / 4];
    float m3c;                                                   // +0x3c
    uint32_t pad40[(0x154 - 0x40) / 4];
    int m154;                                                    // +0x154
    uint32_t pad158[(0x17c - 0x158) / 4];
    cCreatureEffects* mp17c;                                                 // +0x17c
    cCreatureExtra* mpExtra;                                     // +0x180
    void FUN_00a04a90(int a);                                    // 0x00a04a90
    void FUN_00a04ab0(int a);                                    // 0x00a04ab0
    void FUN_00a04d00(int a);                                    // 0x00a04d00
    void FUN_00a04ce0(uint32_t a);                               // 0x00a04ce0
};
struct cSPEditorAnimatedCreatureManager_s0058_2fe0 {
    uint32_t AddCreature(void* pCreature);                                    // 0x0059c9c0
    uint32_t CreateCreature(cSPEditorModel_s0058_2fe0* pModel, cSkinObject_s0058_2fe0* pSkin, bool a, bool b);   // 0x0059c830
    cEditorCreature* GetCreature(uint32_t id);                                // 0x0059ca70
    void SetCreatureVisible(uint32_t id, bool b);                             // 0x0059ce30
    void ResetCreature(uint32_t id);                                          // 0x0059d240
    void FUN_0059d180(uint32_t id, int v);                                    // 0x0059d180
    cCreatureStructure_s0058_2fe0* GetCreatureStructure(uint32_t id);                    // 0x0059cac0
    void FUN_0059d1e0(uint32_t id, bool b);                                   // 0x0059d1e0
    bool GetCreaturePosition(uint32_t id, Vector3_s0058_2fe0* pOut);                     // 0x0059d110
    void FUN_0059d060(uint32_t id, bool b);                                   // 0x0059d060
    void SetCreatureTargetPosition(uint32_t id, Vector3_s0058_2fe0 pos, bool a, bool b); // 0x0059cf00
    void SetCreatureTargetAngle(uint32_t id, float angle, bool a);            // 0x0059cea0
    void SetCreatureSpeeds(uint32_t id, float a, float b);                    // 0x0059d0b0
    void PlayAnimation(uint32_t id, uint32_t anim);                           // 0x0059cb10
    void SetCreaturePreserveHeight(uint32_t id, bool b);                      // 0x0059cf60
};
struct IModelManager_s0058_2fe0 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual void* GetModelResource(uint32_t id, int a, int b);                // +0x28
};
IModelManager_s0058_2fe0* ModelManager_s0058_2fe0();                                                // 0x0067dd80
struct IMessageManager_s0058_2fe0 {
    void Post(uint32_t messageID, int a, void* pPayload);                     // 0x0045af60
};
IMessageManager_s0058_2fe0* MessageManager();                                            // 0x00401050
struct cCreatureLayout {
    void FUN_0062ad70(const Vector3_s0058_2fe0* pTarget, uint32_t id, int index, float size, Vector3_s0058_2fe0 offset);  // 0x0062ad70
};
struct cPaintCreatureRec {
    uint32_t mCreatureId;                                        // +0x00
    float m04;                                                   // +0x04
    float mApproachDistance;                                     // +0x08
    Vector3_s0058_2fe0 mOffset;                                             // +0x0c
    bool mb18, mb19, mb1a, mb1b, mb1c;                           // +0x18
    float m20, m24, m28;                                         // +0x20
    int m2c;                                                     // +0x2c
    cPaintCreatureRec()
        : mCreatureId(0), m04(0.0f), mApproachDistance(0.0f), mOffset(kVecDefault),
          mb18(false), mb19(false), mb1a(false), m20(0.0f) {}
    cPaintCreatureRec(const cPaintCreatureRec& r);               // 0x00576900
};
struct cRecVector {
    cPaintCreatureRec* mpBegin;                                  // +0x00
    cPaintCreatureRec* mpEnd;                                    // +0x04
    cPaintCreatureRec* mpCapacity;                               // +0x08
    uint32_t mAllocator[2];
    void DoInsertValue(cPaintCreatureRec* position, const cPaintCreatureRec& value);   // 0x0057f0f0
    void push_back(const cPaintCreatureRec& value)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) cPaintCreatureRec(value);
        else
            DoInsertValue(mpEnd, value);
    }
    int size() const { return (int)(mpEnd - mpBegin); }
};
namespace SP {
class cAppModeEditorBase_s0058_2fe0 {
public:
    uint32_t pad00[0x7c / 4];
    cCreatureLayout* mpLayout;                                   // +0x7c
    uint32_t pad80[(0x98 - 0x80) / 4];
    cSPEditorModel_s0058_2fe0* mpEditorSaveModel;                           // +0x98
    uint32_t pad9c[(0x150 - 0x9c) / 4];
    cSkinHolder* mpSkinManager;                                  // +0x150
    cSkinHolder* mpPainter;                                      // +0x154
    uint32_t pad158[(0x2b5 - 0x158) / 4];
    uint8_t pad2b4[1];
    bool mb2b5;                                                  // +0x2b5
    uint8_t pad2b6[(0x31c - 0x2b6)];
    int mEditorMode;                                             // +0x31c
    uint32_t pad320[(0x34c - 0x320) / 4];
    int m34c;                                                    // +0x34c
    uint32_t pad350[(0x360 - 0x350) / 4];
    cSPEditorAnimatedCreatureManager_s0058_2fe0* mpCreatureMgr;             // +0x360
    uint32_t mTorsoCreatureId;                                   // +0x364
    uint32_t mPainterCreatureId;                                 // +0x368
    cRecVector mRecs;                                            // +0x36c

    bool RunSkinPaintOnEditorModel(int kind, void* pExisting);

    __forceinline void RebuildSkin(cSkinHolder* pHolder, cSkinObject_s0058_2fe0* pSkin)
    {
        pHolder->Update(0, 1, cSkinUpdateFlags(), 0);
        pSkin->BuildSkeleton();
        pSkin->FUN_004cb340();
        pSkin->FUN_004cb820();
    }
};  // namespace SP
}
// ---- items of slice s00582fe0 end

// ---- items of slice s00583c50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cIntVec {
    int* mpBegin;
    int* mpEnd;
    int* mpCapacity;
    void Resize(uint32_t n);
    int* Insert(int* at, uint32_t count, const int* value);   // @ 0x0057f220
    int* Erase(int* first, int* last);                       // @ 0x005c2170
};
// ---- items of slice s00583c50 end

// ---- items of slice s00585330 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cLocalInputState {
    void OnKeyDown(int a, int b);   // 0x00697a50
    void OnKeyUp(int a, int b);     // 0x00697a80
};
struct cAppModeEditorBase_s0058_5330 {
    char pad0[0x30];
    int mCurrentMouseDown;    // +0x30
    char pad34[0x7c - 0x34];
    void* mLightingWorld;     // +0x7c
    char pad80[0x31c - 0x80];
    int mQueuedAnim;          // +0x31c

    cLocalInputState* Input() { return (cLocalInputState*)((char*)this + 0xf8); }
    uint32_t SetModeModifiers();               // 0x005855b0
    void FUN_00585830(int a, int b);  // 0x00585830 (cAppModeEditorBase::FUN_00585830)
    void FUN_00585860(int a, int b);  // 0x00585860 (cAppModeEditorBase::FUN_00585860)
    bool OnKeyUp(uint32_t key, uint32_t mods);  // 0x00585890 (cAppModeEditorBase::OnKeyUp)
};
// ---- items of slice s00585330 end

// ---- items of slice s00585d40 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VP1(p, n) virtual void p##n() = 0;
#define VP4(p, n) VP1(p, n##0) VP1(p, n##1) VP1(p, n##2) VP1(p, n##3)
#define VP16(p, n) VP4(p, n##0) VP4(p, n##1) VP4(p, n##2) VP4(p, n##3)
namespace SP {
class cSPEditorUI_s0058_5d40 {
public:
    void EnableUndoButton(bool b);  // 0x005dceb0 (SP::cSPEditorUI::EnableUndoButton)
    void EnableRedoButton(bool b);  // 0x005dce40 (SP::cSPEditorUI::EnableRedoButton)
    void UpdateUIBasedOnModelSaveability();  // 0x005dd7a0 (SP::cSPEditorUI::UpdateUIBasedOnModelSaveability)
};
}
namespace SP {
struct UndoVector {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    uint32_t mPad0c;    // +0x0c
    uint32_t mPad10;    // +0x10
    void erase(void* first, void* last);
};
}
namespace SP {
struct cImageRef {
    uint32_t mHandle;       // +0
    uint32_t mFlags;        // +4 (bit 0: already registered)
    long mnRefCount;        // +8
};
}
namespace SP {
struct cImagePtr {
    cImageRef* p;
    void Assign(void* res);                                 // 0x00576650
};
}
namespace SP {
struct Vec3U { uint32_t x, y, z; };
}
namespace SP {
struct cPedestalModel {
    char pad0[0xc];
    Vec3U mPos;                 // +0x0c
    char pad18[0xdc - 0x18];
    uint32_t mScore;            // +0xdc
};
}
namespace SP {
struct cEditorModelStub {
    char pad0[0x58];
    uint32_t mNameHash;         // +0x58
};
}
namespace SP {
struct cEditorLaunchData_s0058_5d40 {
    char pad0[0xc];
    uint32_t mConfig;           // +0x0c
    char pad10[0x60 - 0x10];
    float mShaderParam;         // +0x60
};
}
namespace SP {
struct cSkinFactoryStub {
    char pad0[0x5c];
    void* mpSub;                // +0x5c
    bool IsBusy();                          // 0x004c58b0
    char pad1[1];
    bool GetFlag84();                       // 0x004c4630 (reads byte +0x84)
    void* GetSub();                         // 0x004adfe0 (returns +0x5c)
    void UpdatePaintedSkin();               // 0x004c4290
    void Begin(char b);                     // 0x004c4650
    void Apply(cEditorModelStub* m);        // 0x004c5200
};
}
namespace SP {
struct cPaletteSub { VP16(a, 0) VP4(b, 0) virtual void vfn50(int a) = 0; };
}
namespace SP {
struct cPaletteUI_s0058_5d40 { char pad0[0x38]; cPaletteSub* mpSub; };
}
namespace SP {
class cAppModeEditorBase_s0058_5d40;
}
namespace SP {
struct EmptyStr_s0058_5d40 { const char* mpBegin; const char* mpEnd; const char* mpCap; };
}
namespace SP {
class cAppModeEditorBase_s0058_5d40 {
public:
    char pad0[0x78];
    cSPEditorUI_s0058_5d40* mDevUI;                 // +0x78
    char pad7c[0x84 - 0x7c];
    void* mSaveModelWorld;               // +0x84
    char pad88[0x98 - 0x88];
    cEditorModelStub* mEditorSaveModel;  // +0x98
    cPedestalModel* mPedastalModel;      // +0x9c
    char padA0[0x150 - 0xa0];
    cSkinFactoryStub* mSaveLoadFactory;  // +0x150
    cSkinFactoryStub* mTextureFactory;   // +0x154
    char pad158[0x15c - 0x158];
    uint32_t mUndoStateRef;              // +0x15c
    UndoVector mUndoLocalStateList;      // +0x160
    UndoVector mUndoList;                // +0x174
    int mUndosLeft;                      // +0x188
    char pad18c[0x1a4 - 0x18c];
    int mAnimCaptureState;               // +0x1a4
    int mCurrentCreatureMode;            // +0x1a8
    char pad1ac[0x1cc - 0x1ac];
    cEditorLaunchData_s0058_5d40* mLaunchData;      // +0x1cc
    Vec3U mParentModelKey;               // +0x1d0
    char pad1dc[0x1f8 - 0x1dc];
    uint32_t mCurrencyIconGroup;         // +0x1f8
    char pad1fc[0x28c - 0x1fc];
    cImagePtr mSmallImage;               // +0x28c
    cImagePtr mLargeImage;               // +0x290
    char pad294[0x2ac - 0x294];
    uint32_t mSaveAreaId;                // +0x2ac
    char pad2b0[0x2f1 - 0x2b0];
    bool mPaintedSkinSave;               // +0x2f1
    char pad2f2[0x310 - 0x2f2];
    bool mTranslateModelOnSave;          // +0x310
    char pad311[3];
    float mShaderParam;                  // +0x314
    char pad318[0x360 - 0x318];
    cPaletteUI_s0058_5d40* mPaletteUILoaded;        // +0x360
    char pad364[4];
    void* mEffectsMaskViewer;            // +0x368
    char pad36c[0x38c - 0x36c];
    int mSaveState;                      // +0x38c
    char pad390[4];
    bool mLargeImageReady;               // +0x394
    bool mSmallImageReady;               // +0x395
    char pad396[0x3f0 - 0x396];
    uint32_t mDeleteValueFadeTime;       // +0x3f0 (frame count)
    char pad3f4[0x408 - 0x3f4];
    uint32_t mCurrentInstanceId;         // +0x408
    char pad40c[0x430 - 0x40c];
    bool mCaptureBusy;                   // +0x430
    char pad431[0x4d8 - 0x431];

    void InitializeUndoList();                              // 0x00586690
    __declspec(noinline) void FUN_00586410(char a, void* b); // 0x00586410
    void FUN_00586700();                                    // 0x00586700
    uint8_t FUN_00586800(void* a);                          // 0x00586800
    void FUN_00586960();                                    // 0x00586960
    void ContinueSaveInProgress();                          // 0x00585d40

    int ScoreCreatureForZCorp();                            // 0x00574b40
    void SetAnimCaptureOn(char on);                         // 0x00583c50
    void CaptureGIF(EmptyStr_s0058_5d40* s);                           // 0x005809a0
    void FUN_00584070();
    void FUN_00580700(cPedestalModel* m, void* world, int size, uint32_t grp, uint32_t id, cImageRef* img);
    void RunSkinPaintOnEditorModel(int a, int b);           // 0x00582fe0
    void SaveSomething();                                   // 0x00577650
    void FUN_00585c10();
    void FUN_00573f70(char a);
};
}
// ---- items of slice s00585d40 end

// ---- items of slice s00586b00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_011e0744(void* dst, const void* src, unsigned n);   // memcpy/memmove thunk
extern wchar_t gEmptyString16[2];     // 0x01667BAC
extern float gFloatThreshold;    // 0x01485378
extern float gDefaultA;          // 0x013EC478
extern float gDefaultB;          // 0x013F0318
typedef unsigned int uint;
void* __cdecl operator_new(unsigned, const char*, int, int, int, int);           // 0x00F473A0
struct WStrE {   // eastl::basic_string<wchar_t> (default constructed)
    wchar_t* mb;
    wchar_t* me;
    wchar_t* mc;
    WStrE() { mb = gEmptyString16; me = gEmptyString16; mc = gEmptyString16 + 1; }
    ~WStrE() {
        if ((((char*)mc - (char*)mb) & ~1) > 2) {
            if (mb) operator_delete_array(mb);
        }
    }
};
inline void RcRelease(void* obj) {
    void** sub = (void**)((char*)obj + 4);
    int c = ((int*)sub)[1] - 1;
    ((int*)sub)[1] = c;
    if (c == 0) {
        ((int*)sub)[1] = 1;
        ((void(__thiscall*)(void*, int))(*(void***)sub)[0])(sub, 1);
    }
}
struct IRef {   // AddRef/Release in slots 1/2 (RefCountVTemplate)
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct IRef4 {   // Release in slot 1
    virtual void v0();
    virtual void Release();
};
struct NameProvider {   // cISPEditorNameProvider at this+0xC
    virtual void SetA(const wchar_t* s);        // +0
    virtual const wchar_t* GetA();              // +4
    virtual void SetB(const wchar_t* s);        // +8
    virtual const wchar_t* GetB();              // +0xC
    virtual void SetC(const wchar_t* s);        // +0x10
};
struct Key { uint inst, type, group; };
struct Property_s0058_6b00 {
    char pad[0x12];
    uint16_t type;
    uint* GetUInt();     // 0x0041EA00
    float* GetFloat();   // 0x0041EA70
};
struct PropList_s0058_6b00 {   // vtable slot 9 (+0x24): lookup
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool Get(uint id, Property_s0058_6b00** out);
};
struct AssetMeta { void GetTagsString(WStrE* out); };   // 0x00550CF0
struct MetaObj { virtual void v0(); virtual void v1(); virtual void v2(); virtual AssetMeta* Cast(uint id); };
struct ResManager {   // vslot 3 (+0xC) gets a resource
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(Key* key, MetaObj** out, int a, int b, int c, int d);
};
ResManager* __cdecl GetManager_s0058_6b00();          // 0x0067DCD0
struct Naming { void SetDataProvider(NameProvider* np); };       // 0x005BFCC0
struct TokenTranslator {
    void SetOldModelName(const wchar_t* n);   // 0x005D6090
    void FUN_005d60c0(const wchar_t* n);      // 0x005D60C0
};
extern TokenTranslator* gTokenTranslator;     // 0x015EEBEC
struct CreatureMgr {   // cSPEditorAnimatedCreatureManager
    void RemoveCreature(uint id);                                    // 0x0059C6E0
    void SetCreaturePreserveHeight(uint id, int v);                  // 0x0059CF60
    void SetCreatureTargetPosition(uint id, float x, float y, float z, int a, int b);   // 0x0059CF00 (vec3 by value)
    void* GetCreatureStructure(uint id);                             // 0x0059CAC0
    void* GetCreatureStructure2(uint id, int a);                     // 0x0059CAC0 (2 arg)
    void SetCreatureTargetAngle(uint id, float a, int b);            // 0x0059CEA0
};
struct FVec { FVec& operator=(const FVec& o); };   // 0x0050D4E0
struct Flagged_s0058_6b00 {
    void SetFlag();   // 0x0059AEA0
};
struct Sink { void FUN_00a04550(int i, Vec3* v); };   // 0x00A04550
struct SPModel {   // cSPEditorModel
    char pad[0x8];
    int mRefCount;     // +8
    uint kInst;        // +0xC
    uint kType;        // +0x10
    uint kGroup;       // +0x14
    char pad2[0x40];
    uint f58;
    void FUN_004ad330();                                  // 0x004AD330
    void FUN_004ada80(float v);                           // 0x004ADA80
    void FUN_004adac0(float v);                           // 0x004ADAC0
    void FUN_004adae0(float v);                           // 0x004ADAE0
    void FUN_004adb20(float v);                           // 0x004ADB20
    void FUN_004adc00(float v);                           // 0x004ADC00
    void FUN_004ae260(uint a, uint b, int c, int d);      // 0x004AE260
    void FUN_004adba0(uint v);                            // 0x004ADBA0
    void FUN_004adbe0(uint v);                            // 0x004ADBE0
    void FUN_004adb60(uint v);                            // 0x004ADB60
    void FUN_004abad0(uint v);                            // 0x004ABAD0
    float FUN_004adb40();                                 // 0x004ADB40
    void FUN_004ad550(float* out, int a);                 // 0x004AD550
    void FUN_004adc20(int v);                             // 0x004ADC20
    void FUN_004adfc0(int v);                             // 0x004ADFC0
    int  FUN_004accf0();                                  // 0x004ACCF0
    struct SubObj* FUN_004accb0(int i, int a, int b, int c, int d);   // 0x004ACCB0 (5 arg)
    struct SubObj* FUN_004accb0b(int i, int a);                       // 0x004ACCB0 (2 arg)
    float* FUN_004adca0(float* out, int i);               // 0x004ADCA0
};
struct SubObj {
    void FUN_0043a5e0();   // 0x0043A5E0
    void FUN_0043a830();   // 0x0043A830
    void FUN_0043a9a0(int a, int b);   // 0x0043A9A0
};
struct SkinMgr_s0058_6b00 {
    bool FUN_004c4630();                  // 0x004C4630
    void FUN_004c4eb0();                  // 0x004C4EB0
    void FUN_004c3070(void* app, SPModel* m, void* x);   // 0x004C3070
    void FUN_004c5100(float a, float b);  // 0x004C5100
    void FUN_004c4650(int v);             // 0x004C4650
    bool FUN_004c58b0();                  // 0x004C58B0
    void FUN_004c5200(SPModel* m);        // 0x004C5200
    void* GetSkin(int v);                 // 0x004C49E0
};
struct DecoMgr {   // this+0x14C
    void FUN_005d31b0();                  // 0x005D31B0
    void FUN_005d3f10(SPModel* m, void* x);                  // 0x005D3F10
    void FUN_005d36e0(SPModel* m, void* x, int v);           // 0x005D36E0
};
struct Handle_s0058_6b00 { void* FUN_0047e6c0(); };    // 0x0047E6C0
struct PlayMode {
    void Stop();                  // 0x0062C340
    void HandleMessages(int v);   // 0x0062BF10
};
struct VProbe { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
                virtual void v5(); virtual void v6(); virtual void v7();
                virtual void SlotX(int a);   // +0x1c
};
struct CamHolder {   // object at creatureMgr+0x38
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void SlotX(int a);   // +0x50
};
struct AnimEventInfo {   // cSPEditorAnimatedEventInfo, 0x30
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    AnimEventInfo* Init();    // 0x0059D960
    void MessageSend(uint msg, int a, void* model, int b, int c, float d, int e, int f, float g);   // 0x0059D8B0
};
struct MessageServer_s0058_6b00 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void Post(uint msg, int a, int b);   // +0x14
};
MessageServer_s0058_6b00* __cdecl GetMessageServer_s0058_6b00();   // 0x0067DCC0
struct Obj401050 {
    bool FUN_0045b210();    // 0x0045B210
    void FUN_0045b150();    // 0x0045B150
    void FUN_0045ae10();    // 0x0045AE10
};
Obj401050* __stdcall FUN_00401050(int a);                 // 0x00401050
Obj401050* __stdcall FUN_00401050_2(int a, int b);        // 0x00401050 (2 arg)
float __cdecl GetModelMinZ(SPModel* m);                   // 0x0048CF00
bool  __cdecl FUN_004a0ac0(SPModel* m);                   // 0x004A0AC0
void  __cdecl FUN_004934d0(SPModel* m, Vec3 v, int z);    // 0x004934D0
void* __cdecl FUN_0046b8e0(float* out, SPModel* m, uint v);   // 0x0046B8E0
void  __cdecl FUN_004b7660(SPModel* m);                   // 0x004B7660
void  __cdecl FUN_0046bfd0(float* out, SPModel* m);       // 0x0046BFD0
void  __cdecl PlayEditorSound(uint a, uint b, float v, int z);   // 0x00435F40
extern uint  gDefaultBlock[9];   // 0x015E505C
namespace SP {
class cAppModeEditorBase_s0058_6b00 {
public:
    virtual void v0();
    char pad[0x1000];

    void PrepareAppForNewModel(SPModel* model);   // 0x00586b00
    bool SetMode(int mode, char force);           // 0x00587270

    // callees (other slices)
    void ScaleBlock();                  // 0x00586960
    void FUN_0057e340(int a);           // 0x0057E340
    void FUN_00582fe0(int a, int b);    // 0x00582FE0
    void FUN_0057c440();                // 0x0057C440
    int  FUN_00576140();                // 0x00576140
    void CreateWidget2(int a);          // 0x005DBB60
    void FUN_00573c00(int a, int b);    // 0x00573C00
    void SetRolloverHandle(int a, int b);   // 0x00573D70
    void RemoveTorsoFromEffectsMask();  // 0x005772B0
    void FUN_005744b0(int mode);        // 0x005744B0
    void UpdateRenderSettings();        // 0x005794B0
    void FUN_00573390();                // 0x00573390
    void FUN_00573330();                // 0x00573330
};  // namespace SP
}
#define M(T, off) (*(T*)((char*)this + (off)))
// ---- items of slice s00586b00 end

// ---- items of slice s00587a20 begin (TODO(rewrite): local stubs, replace by canonical classes)
#undef VS
struct ResourceKey_s0058_7a20 {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};
template <class T>
class AutoRefCount_s0058_7a20 {
public:
    T* mpObject;

    AutoRefCount_s0058_7a20& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
class RefCountTemplate_s0058_7a20 {
public:
    virtual ~RefCountTemplate_s0058_7a20();
    int mnRefCount;

    int AddRef() { return ++mnRefCount; }
    int Release()
    {
        int n = --*(volatile int*)&mnRefCount;
        if (n == 0) {
            mnRefCount = 1;
            delete this;
            return 0;
        }
        return n;
    }
};
class IRefCounted0 {   // AddRef +0, Release +4
public:
    virtual int AddRef();
    virtual int Release();
};
class IRefCounted4 {   // AddRef +4, Release +8
public:
    virtual void _v00();
    virtual int AddRef();
    virtual int Release();
};
class IModelWorld_s0058_7a20;
class cMWModel_s0058_7a20 {   // Graphics::Model
public:
    IModelWorld_s0058_7a20* mpWorld;   // +00
    uint32_t mFlags;        // +04
    uint32_t mTransform[14];
    int mnRefCount;         // +40

    int AddRef() { return ++mnRefCount; }
    int Release();
};
class ILightingWorld : public IRefCounted0 {};
class IModelWorld_s0058_7a20 {
public:
#define VS(n) virtual void _v##n();
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C) VS(50) VS(54) VS(58) VS(5C) VS(60) VS(64) VS(68) VS(6C) VS(70) VS(74) VS(78) VS(7C)
    VS(80) VS(84) VS(88) VS(8C) VS(90) VS(94) VS(98) VS(9C) VS(A0) VS(A4) VS(A8) VS(AC) VS(B0) VS(B4) VS(B8) VS(BC)
    VS(C0) VS(C4) VS(C8) VS(CC) VS(D0) VS(D4) VS(D8) VS(DC) VS(E0) VS(E4) VS(E8) VS(EC) VS(F0) VS(F4) VS(F8) VS(FC)
    VS(100) VS(104) VS(108) VS(10C) VS(110) VS(114) VS(118) VS(11C) VS(120) VS(124) VS(128) VS(12C) VS(130)
    virtual void SetActive(bool active);                                              // 134h
    VS(138) VS(13C)
    virtual int SetLightingWorld(ILightingWorld* pWorld, int indexDrawSet, bool drawShadows);  // 140h
    VS(144) VS(148) VS(14C) VS(150) VS(154) VS(158) VS(15C) VS(160) VS(164) VS(168)
    virtual void SetInWorld(cMWModel_s0058_7a20* model, bool inWorld);                          // 16Ch
    virtual void DestroyModel(cMWModel_s0058_7a20* model, bool flag);                            // 170h
};
inline int cMWModel_s0058_7a20::Release()
{
    if (mnRefCount > 1) {
        mnRefCount = mnRefCount - 1;
        return mnRefCount;
    }
    mpWorld->DestroyModel(this, (bool)((mFlags >> 31) & 1));
    return 0;
}
class IEffectsWorld {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08();
    virtual void SetState(int state);   // 0Ch
    virtual void _v10(); virtual void _v14(); virtual void _v18(); virtual void _v1C();
    virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C(); virtual void _v30();
    virtual void Deactivate();          // 34h
};
class IShadowWorld : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1C(); virtual void _v20();
    virtual void Clear();               // 24h
    virtual void SetActive(bool active);   // 28h
};
class cEffectsManager_s0058_7a20 {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C) VS(50) VS(54)
    virtual void SetActiveWorld(IEffectsWorld* world);   // 58h
    VS(5C) VS(60) VS(64) VS(68) VS(6C) VS(70) VS(74) VS(78) VS(7C) VS(80) VS(84) VS(88) VS(8C) VS(90) VS(94)
    virtual void SetFlags(int flags, int value);   // 98h
};
class cModelManager_s0058_7a20 {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20)
    virtual void SetSaveModelWorld(IModelWorld_s0058_7a20* world);   // 24h
};
class cRenderTarget {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C)
    virtual void ClearValue(uint32_t value);   // 20h
};
class cRenderTargets {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C)
    virtual cRenderTarget* GetTarget();   // 20h
};
class cRenderManager {
public:
    IModelWorld_s0058_7a20* GetUILayerModelWorld();   // 0x006c10e0
};
class cViewer_s0058_7a20 {
public:
    void SetViewAngleY(float angle);   // 0x007c53d0
};
class cApp {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C) VS(50) VS(54)
    virtual cViewer_s0058_7a20* GetViewer();   // 58h
};
class cCheatManager_s0058_7a20 {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18)
    virtual void RemoveCheats(const char* tag);   // 1Ch
};
class cInputManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34) VS(38) VS(3C)
    VS(40) VS(44) VS(48) VS(4C)
    virtual void ClearState(int state);   // 50h
};
class cGameInputManager {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28)
    virtual void Reset();   // 2Ch
};
class IAudioSystem_s0058_7a20 {
public:
    VS(00) VS(04) VS(08) VS(0C) VS(10) VS(14) VS(18) VS(1C) VS(20) VS(24) VS(28) VS(2C) VS(30) VS(34)
    virtual void SetGroup(uint32_t id);                    // 38h
    VS(3C)
    virtual void SetValue(uint32_t id, uint32_t value);    // 40h
    VS(44) VS(48) VS(4C) VS(50) VS(54)
    virtual void Commit();                                 // 58h
};
class cHintManager {
public:
    void ClearHints();                        // 0x0067ca40
    void SetEnabled(bool enabled, bool b);    // 0x0067c420
};
class cPropertyUI {
public:
    void DestroyAllElems();   // 0x0067a120
};
class cDisplayObject {
public:
    char pad[0xb9];
    bool mbFlagB9;   // +b9
};
class cDisplayManager {
public:
    cDisplayObject* GetPrimary();     // 0x0113ae10
    cDisplayObject* GetSecondary();   // 0x00801920
};
class cSwarmManager {
public:
    void ClearEditorEffects();   // 0x0045ab30
};
class cCursorManager {
public:
    void SetLocalCursor(uint32_t id);   // 0x00801bb0
};
class IWindow_s0058_7a20 {
public:
    virtual void _v00();
};
class IWindowManager_s0058_7a20 {
public:
    virtual void _v00();
    virtual IWindow_s0058_7a20* GetMainWindow();   // 04h
};
class cMainWinBase {
public:
    virtual void _v00();
};
class cSPUIMainWin : public cMainWinBase, public IWindow_s0058_7a20 {
public:
    uint64_t GetTimeStamp();   // 0x008130a0
};
class cDirectPropertyList_s0058_7a20 {
public:
    char pad[0x3c];
    struct cConfig { char pad[0x118]; int mnValue118; }* mpConfig;   // +3c
    void SetIntProperty(uint32_t id, int value);   // 0x006a1880
};
class IHandler_s0058_7a20;
class IMessageServer_s0058_7a20 {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10();
    virtual void PostMSG(uint32_t messageID, void* msg, int arg);                  // 14h
    virtual void PostMessage(uint32_t messageID, IRefCounted4* msg, int a, int b);  // 18h
};
class cBehaviorMessage {
public:
    virtual void _v00();
    volatile long mnRefCount;   // +04
    cBehaviorMessage() { _InterlockedExchange(&mnRefCount, 0); }
};
struct cMessageHeader {
    uint32_t mModeID;        // +08
    uint32_t field_C[9];
    uint32_t mMessageID;     // +30
    uint32_t field_34;
    cMessageHeader(uint32_t id) : mMessageID(id) {}
};
class cEditorDeactivatedMessage : public cMessageHeader, public cBehaviorMessage {
public:
    void* mpData;            // +38
    uint32_t field_3C;

    cEditorDeactivatedMessage() : cMessageHeader(0x60c874f), mpData(0) {}
    virtual void _v00();
    ~cEditorDeactivatedMessage();   // 0x00421cf0
};
class cEditorLaunchData_s0058_7a20 : public IRefCounted4 {
public:
    uint32_t pad04[3];
    ResourceKey_s0058_7a20 mModelKey;           // +10
    uint32_t pad1C[29];
    uint32_t mCallerID;              // +90
    IRefCounted0* mpCallerData;      // +94
};
class cEditorResultsMessage : public IRefCounted4 {
public:
    uint32_t pad04[2];
    uint32_t mCallerID;                     // +0c
    AutoRefCount_s0058_7a20<IRefCounted0> mpCallerData;  // +10
    uint32_t mModelID;                      // +14
    ResourceKey_s0058_7a20 mModelKey;                  // +18
    uint32_t pad24[8];
    bool mbAccepted;                        // +44

    cEditorResultsMessage();   // 0x00579c80
};
namespace SP {
class cSPEditorBlock_s0058_7a20 : public IRefCounted4 {
public:
    char pad04[0xdc8 - 4];
    uint32_t mBlockFlags;   // +dc8
    bool IsFlagSet1() const { return ((mBlockFlags >> 1) & 1) != 0; }
    void SetUIState(int state, bool b);   // 0x0043a9a0
};
}
namespace SP {
class cSPEditorHandle_s0058_7a20 : public IRefCounted0 {
public:
    cSPEditorBlock_s0058_7a20* GetRigblock();   // 0x0047e6c0
};
}
namespace SP {
class cSPEditorModel_s0058_7a20 : public IRefCounted4, public RefCountTemplate_s0058_7a20 {
public:
    uint32_t pad0C[19];
    uint32_t mModelID;   // +58
    using RefCountTemplate_s0058_7a20::AddRef;
    using RefCountTemplate_s0058_7a20::Release;
    void ClearSelection();   // 0x004ad280
    void ClearBlocks();      // 0x004ad330
};
}
namespace SP {
class cSPEditorSpine_s0058_7a20 : public IRefCounted4 {
public:
    void ClearVertebrae();   // 0x005d31b0
};
}
namespace SP {
class cSPResourceFactory : public IRefCounted0 {
public:
    void Shutdown();   // 0x004c4eb0
};
}
namespace SP {
class cRollover : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1C(); virtual void _v20();
    virtual void Shutdown();   // 24h
};
}
namespace SP {
class cSPVerbTrayCollection_s0058_7a20 : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void Shutdown();   // 18h
};
}
namespace SP {
class cSPEditorBudget_s0058_7a20 {
public:
    virtual void _v00(); virtual void _v04();
    virtual int AddRef();    // 08h
    virtual int Release();   // 0Ch
    void Shutdown();         // 0x004581d0
};
}
namespace SP {
class cSPEditorComplexityMeter_s0058_7a20 : public IRefCounted0 {
public:
    void Shutdown();   // 0x00ed0660
};
}
namespace SP {
class cSPEditorStatsPanel : public IRefCounted0 {
public:
    void Shutdown();   // 0x0059a3b0
};
}
namespace SP {
class cSPEditorNaming_s0058_7a20 : public IRefCounted0 {
public:
    void Shutdown();   // 0x005bfb90
};
}
namespace SP {
class cSPPlayMode_s0058_7a20 : public IRefCounted4 {
public:
    void Shutdown();   // 0x0062c910
};
}
namespace SP {
class cSPEditorPaintTheme_s0058_7a20 : public IRefCounted0 {
public:
    void Reset();   // 0x004b27c0
};
}
namespace SP {
class cSPPaletteUI_s0058_7a20 : public IRefCounted0 {
public:
    void Shutdown();   // 0x005cba90
};
}
namespace SP {
class cSPPalette_s0058_7a20 : public IRefCounted4 {
public:
    void Shutdown();   // 0x005c5c20
};
}
namespace SP {
class cSPEditorUIBase {
public:
    virtual void _v00();
};
}
namespace SP {
class cSPEditorUI_s0058_7a20 : public cSPEditorUIBase, public IRefCounted0 {
public:
    void Shutdown();   // 0x005de870
};
}
namespace SP {
class cSPEditorAnimatedCreatureManager_s0058_7a20 : public RefCountTemplate_s0058_7a20 {
public:
    void Shutdown();   // 0x0059c640
};
}
namespace SP {
class cEditorTool : public IRefCounted0 {
public:
    virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14(); virtual void _v18();
    virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void Shutdown();   // 30h
};
}
namespace SP {
cApp* App_s0058_7a20();                          // 0x0067dd10
}
namespace SP {
IMessageServer_s0058_7a20* MessageServer_s0058_7a20();      // 0x0067dcc0
}
namespace SP {
cCheatManager_s0058_7a20* CheatManager_s0058_7a20();        // 0x0067de20
}
namespace SP {
cRenderTargets* RenderTargets();      // 0x0067de40
}
namespace SP {
cHintManager* HintManager();          // 0x0067cac0
}
namespace SP {
cPropertyUI* PropertyUI();            // 0x0067caf0
}
namespace SP {
cRenderManager* RenderManager();      // 0x0067cad0
}
namespace SP {
cDisplayManager* DisplayManager();    // 0x00401020
}
namespace SP {
cSwarmManager* SwarmManager();        // 0x00401050
}
namespace SP {
cEffectsManager_s0058_7a20* EffectsManager_s0058_7a20();    // 0x0067ddd0
}
namespace SP {
cModelManager_s0058_7a20* ModelManager_s0058_7a20();        // 0x0067dd80
}
namespace SP {
cInputManager* InputManager();        // 0x0067dd50
}
namespace SP {
cGameInputManager* GameInputManager();  // 0x0067dd40
}
namespace SP {
IWindowManager_s0058_7a20* WindowManager_s0058_7a20();      // 0x0067caa0
}
namespace SP {
cCursorManager* CursorManager_s0058_7a20();      // 0x0067cab0
}
namespace SP {
void SetShaderParam(int id, void* pValue, int arg);   // 0x00777ae0
}
namespace SP {
extern cDirectPropertyList_s0058_7a20* g_pAppProperties;   // 0x015fd918
}
namespace SP {
extern uint32_t* g_pRenderFlags;                // 0x016f6ee0
}
namespace SP {
extern uint32_t g_RenderTargetValue;            // 0x015eebec
}
namespace EA {
namespace Audio {
 IAudioSystem_s0058_7a20* GetSystemAT_s0058_7a20();   // 0x00a206f0
}
}
namespace EA {
namespace Messaging {
void RemoveHandler(IMessageServer_s0058_7a20* pServer, IHandler_s0058_7a20* pHandler, const uint32_t* pIDs, int count, int flags);  // 0x00571db0
}
}
struct cMessageListenerRegistration {
    IMessageServer_s0058_7a20* mpServer;
    IHandler_s0058_7a20* mpHandler;
    const uint32_t* mpMessageIDs;
    int mnCount;
    int mnFlags;

    void Unregister()
    {
        if (mpServer) {
            IMessageServer_s0058_7a20* pServer = mpServer;
            mpServer = 0;
            EA::Messaging::RemoveHandler(pServer, mpHandler, mpMessageIDs, mnCount, mnFlags);
        }
    }
};
class cIAppMode_s0058_7a20 {
public:
    virtual void _v00(); virtual void _v04(); virtual void _v08(); virtual void _v0C(); virtual void _v10(); virtual void _v14();
    virtual void _v18(); virtual void _v1C(); virtual void _v20(); virtual void _v24(); virtual void _v28(); virtual void _v2C();
    virtual void _v30(); virtual void _v34(); virtual void _v38(); virtual void _v3C(); virtual void _v40();
    virtual uint32_t GetModeID();        // 44h
    virtual void _v48();
    virtual void ClearUndoRedo();        // 4Ch
};
namespace SP {
class cAppModeEditorBase_s0058_7a20 : public cIAppMode_s0058_7a20 {
public:
    uint32_t pad004[29];
    /* 078h */ AutoRefCount_s0058_7a20<cSPEditorUI_s0058_7a20> mpEditorUI;
    /* 07Ch */ AutoRefCount_s0058_7a20<cSPPlayMode_s0058_7a20> mpPlayMode;
    /* 080h */ ILightingWorld* mpLightingWorld;
    /* 084h */ IModelWorld_s0058_7a20* mpMainModelWorld;
    /* 088h */ IModelWorld_s0058_7a20* mSaveModelWorld;
    /* 08Ch */ IModelWorld_s0058_7a20* mpBackgroundModelWorld;
    /* 090h */ void* mpPhysicsWorld;
    /* 094h */ IEffectsWorld* mpEffectWorld;
    /* 098h */ AutoRefCount_s0058_7a20<cSPEditorModel_s0058_7a20> mpEditorModel;
    /* 09Ch */ AutoRefCount_s0058_7a20<cSPEditorModel_s0058_7a20> mpEditorSaveModel;
    /* 0A0h */ AutoRefCount_s0058_7a20<cMWModel_s0058_7a20> mpPedestalModel;
    /* 0A4h */ AutoRefCount_s0058_7a20<cMWModel_s0058_7a20> mpTestEnvironmentModel;
    /* 0A8h */ AutoRefCount_s0058_7a20<cMWModel_s0058_7a20> mpBackgroundModel;
    /* 0ACh */ AutoRefCount_s0058_7a20<cMWModel_s0058_7a20> mpPlayModeBackgroundModel;
    uint32_t pad0B0[8];
    /* 0D0h */ AutoRefCount_s0058_7a20<IRefCounted4> mpUndoQueue;
    /* 0D4h */ AutoRefCount_s0058_7a20<cSPEditorBlock_s0058_7a20> mpPreviousSelectedBlock;
    uint32_t pad0D8[3];
    /* 0E4h */ AutoRefCount_s0058_7a20<cSPEditorHandle_s0058_7a20> mpRolloverHandle;
    /* 0E8h */ bool mTorsoUIState;
    /* 0E9h */ bool mbTorsoInEffectsMask;
    uint8_t pad0EA[2];
    uint32_t pad0EC[22];
    /* 144h */ bool field_144;
    uint8_t pad145[3];
    /* 148h */ AutoRefCount_s0058_7a20<cEditorTool> mpTool;
    /* 14Ch */ AutoRefCount_s0058_7a20<cSPEditorSpine_s0058_7a20> mpSpine;
    /* 150h */ AutoRefCount_s0058_7a20<cSPResourceFactory> mpSaveLoadFactory;
    /* 154h */ AutoRefCount_s0058_7a20<cSPResourceFactory> mpTextureFactory;
    uint32_t pad158[21];
    /* 1ACh */ AutoRefCount_s0058_7a20<ILightingWorld> mpUILayerOldLightingWorld;
    uint32_t pad1B0[7];
    /* 1CCh */ AutoRefCount_s0058_7a20<cEditorLaunchData_s0058_7a20> mpLaunchData;
    uint32_t pad1D0[15];
    uint8_t pad20C[2];
    /* 20Eh */ bool mbBackgroundMusic;
    uint8_t pad20F[1];
    uint32_t pad210[33];
    /* 294h */ AutoRefCount_s0058_7a20<IShadowWorld> mpShadowWorld;
    uint32_t pad298[1];
    /* 29Ch */ AutoRefCount_s0058_7a20<cSPEditorPaintTheme_s0058_7a20> mDefaultPaintTheme;
    /* 2A0h */ AutoRefCount_s0058_7a20<cSPEditorPaintTheme_s0058_7a20> mCurrentPaintTheme;
    /* 2A4h */ AutoRefCount_s0058_7a20<cSPVerbTrayCollection_s0058_7a20> mVerbIconTray;
    uint32_t pad2A8[2];
    /* 2B0h */ bool mIsActive;
    uint8_t pad2B1[3];
    uint32_t pad2B4[39];
    /* 350h */ AutoRefCount_s0058_7a20<cSPEditorBudget_s0058_7a20> mpBudget;
    /* 354h */ AutoRefCount_s0058_7a20<cSPEditorComplexityMeter_s0058_7a20> mpComplexityMeter;
    /* 358h */ AutoRefCount_s0058_7a20<cSPEditorNaming_s0058_7a20> mpNaming;
    /* 35Ch */ AutoRefCount_s0058_7a20<cSPEditorStatsPanel> mpStatsPanel;
    /* 360h */ AutoRefCount_s0058_7a20<cSPEditorAnimatedCreatureManager_s0058_7a20> mpAnimCreatureManager;
    /* 364h */ int field_364;
    /* 368h */ int field_368;
    uint32_t pad36C[5];
    /* 380h */ AutoRefCount_s0058_7a20<IRefCounted4> mpCreationController;
    /* 384h */ bool field_384;
    /* 385h */ bool field_385;
    uint8_t pad386[2];
    uint32_t pad388[12];
    /* 3B8h */ AutoRefCount_s0058_7a20<cSPPalette_s0058_7a20> mpPaintPalette;
    /* 3BCh */ AutoRefCount_s0058_7a20<cSPPaletteUI_s0058_7a20> mpPaintPaletteUI;
    /* 3C0h */ AutoRefCount_s0058_7a20<cSPPalette_s0058_7a20> mpPartsPalette;
    /* 3C4h */ AutoRefCount_s0058_7a20<cSPPaletteUI_s0058_7a20> mpPartsPaletteUI;
    uint32_t pad3C8[28];
    /* 438h */ uint64_t mnActivateTime;
    /* 440h */ uint64_t mnModelStartTime;
    /* 448h */ uint64_t mnTotalActiveTime;
    /* 450h */ int field_450;
    uint32_t pad454[16];
    /* 494h */ AutoRefCount_s0058_7a20<cRollover> mpSellBackRollover;
    /* 498h */ AutoRefCount_s0058_7a20<cRollover> mpSellBackRollover2;
    /* 49Ch */ AutoRefCount_s0058_7a20<cRollover> mpMessageRollover;
    /* 4A0h */ AutoRefCount_s0058_7a20<cRollover> mpDetachedRollover;
    /* 4A4h */ AutoRefCount_s0058_7a20<cRollover> mpDetachedRollover2;
    uint32_t pad4A8[3];
    uint8_t pad4B4[2];
    /* 4B6h */ bool field_4B6;
    uint8_t pad4B7[1];
    uint32_t pad4B8[1];
    /* 4BCh */ AutoRefCount_s0058_7a20<IRefCounted4> mpCameraController;
    uint32_t pad4C0[4];
    /* 4D0h */ float field_4D0;
    uint32_t pad4D4[64];
    /* 5D4h */ cMessageListenerRegistration mMessageRegistration;

    bool SetMode(int mode, bool bForce);            // 0x00587270
    void RemoveTorsoFromEffectsMask();              // 0x005772b0
    void SetSelection(int a, int b);                // 0x00573c00
    void SetRolloverHandle(int handle, bool b);     // 0x00573d70
    void DestroyEditorWidgets(bool b);              // 0x005dbb60
    void HideDebugUI();                             // 0x005dbb50

    void Deactivate();   // 0x00587a20
};  // namespace SP
}
// ---- items of slice s00587a20 end

// ---- items of slice s00589ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct UIHints { void SetEnabled(); };               // 0x0067C420
extern wchar_t gDelimiters[];          // 0x013F5CA8
struct Key16 { uint a, b, c, d; };
struct Key12 { uint inst, type, group; };
struct RcSub { void** vt; int cnt; };
inline void RcRelease_s0058_9ce0(void* obj) {
    RcSub* sub = (RcSub*)((char*)obj + 4);
    int c = sub->cnt - 1;
    sub->cnt = c;
    if (c == 0) {
        _ReadWriteBarrier();
        sub->cnt = 1;
        _ReadWriteBarrier();
        ((void(__thiscall*)(void*, int))sub->vt[0])(sub, 1);
    }
}
struct WStr {
    wchar_t* mb;
    wchar_t* me;
    wchar_t* mc;
    int mAlloc;
    void RangeInit(const wchar_t* p);   // 0x00579A90 basic_string::RangeInitialize
    void Erase(int first, int last);    // 0x004228E0
    WStr(const wchar_t* p) { mb = 0; me = 0; mc = 0; RangeInit(p); }
    ~WStr() {
        if ((((char*)mc - (char*)mb) & ~1) > 2) {
            if (mb) operator_delete_array(mb);
        }
    }
};
struct IRefObj {   // vtable: AddRef(+4) Release(+8) style objects (RefCountVTemplate)
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
};
struct FileStream {
    virtual void v0();
    virtual void AddRef();     // +4
    virtual void Release();    // +8
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void Close();      // +0x18
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
    virtual void SetPath(const wchar_t* path);   // +0x3c
virtual void v16();
virtual void v17();
virtual void v18();
    virtual bool Open(int access, int mode, int share, int flags);   // +0x4c
    FileStream* Init(int path);   // 0x00931DA0 (PFRecordWrite/FileStream ctor)
};
struct EditorResHeader {   // result of cast(0x3c609f8): holds the model type at +0x18
    char pad[0x18];
    int mModelType;
    void ReadKey(Key16* out, Key16 inKey, int zero);                        // 0x004BAC30
};
struct RawResource {       // 0xAC, ctor 0x004B9C70; vtable: AddRef(+0) Release(+4) x(+8) Cast(+0xC)
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual EditorResHeader* Cast(uint typeId);
    RawResource* Init();                                                    // 0x004B9C70
};
struct EditorResource {
    virtual void v0();
    virtual int  GetThing();   // +4 (slot 1)
    char pad4[0x4];
    int  mRefCount;                   // +8
    Key12 mKey;                       // +0xC
    EditorResource* Init();                         // 0x004AB690
    bool CopyFrom(void* src);                       // 0x004AE3B0
};
struct UndoEntry {
    virtual void AddRef();
    virtual void Release();
};
struct LocalState : IRefObj {};
struct AnimEventInfo_s0058_9ce0 {   // cSPEditorAnimatedEventInfo, 0x30
    virtual void v0();
    virtual void AddRef();
    virtual void Release();
    char pad[0x8];
    uint f0c;     // +0xC
    uint f10;     // +0x10
    void* f14;    // +0x14
    uint f18;     // +0x18
    uint8_t f1c;  // +0x1C
    float f20;    // +0x20
    uint8_t f24;  // +0x24
    uint f28;     // +0x28
    AnimEventInfo_s0058_9ce0* Init();    // 0x0059D960
    void MessagePost(uint msg, int a, void* model, int b, int c, float d, int e, int f, float g);   // 0x0059D840
};
struct EditorUI_s0058_9ce0 {
    void UpdateUIBasedOnModelSaveability();   // 0x005DD7A0
    void EnableUndoButton(bool b);            // 0x005DCEB0
    void EnableRedoButton(bool b);            // 0x005DCE40
};
struct ModelObj {   // cSPEditorModel
    virtual void v0();
    virtual uint GetModelThing();   // +4
    char pad[0xA];
    uint mKeyInstance;   // +0xC (declared via offsets below)
};
struct NameProvider_s0058_9ce0 {
    virtual void SetA(const wchar_t* s);       // +0
    virtual const wchar_t* GetA();             // +4
    virtual void SetB(const wchar_t* s);       // +8
    virtual const wchar_t* GetB();             // +0xC
    virtual void SetC(const wchar_t* s);       // +0x10
    virtual const wchar_t* GetC();             // +0x14
};
struct IDGen {
    virtual void v0();
    virtual void v1();
    virtual void Generate(uint* out, uint hi, uint lo);   // +8
};
struct TokenTranslator_s0058_9ce0 { void SetOldModelName(const wchar_t* n); };   // 0x005D6090
struct Out16 { uint w[4]; };
extern Key16 gNullKey;                 // 0x015DAC10
extern TokenTranslator_s0058_9ce0* gTokenTranslator_s0058_9ce0;   // 0x015EEBEC
struct PropList_s0058_9ce0 {
    bool GetDescription(uint id);   // 0x006A25A0
};
extern PropList_s0058_9ce0* sAppProperties_s0058_9ce0;   // 0x015FD918
const wchar_t* __cdecl GetTypeExtension(uint typeId);                                      // 0x004BB490
int  __cdecl WStrNCompare(const wchar_t* a, const wchar_t* b, int n);                      // 0x00572930
const wchar_t* __cdecl FindFirstOfRev(const wchar_t* pEnd, const wchar_t* pBegin,
                                      const wchar_t* dBegin, const wchar_t* dEnd);         // 0x005728F0
bool __cdecl ReadResourceFromStream(FileStream* fs, RawResource* res, int flags);          // 0x004BC6D0
bool __cdecl KeyEquals(Key16 a, Key16 b);                                                  // 0x004F3D60
int  __cdecl RemapTypeId(int typeId);                                                      // 0x00432F10
uint64_t __cdecl MapModeToId(uint v);                                                      // 0x00572110
IDGen* __cdecl GetIDGenerator();                                                           // 0x0067DE60
void* __cdecl RBTreeIncrement(void* node);                                                 // 0x00921580
bool __cdecl FUN_004edf40(int a, int b);
struct SkinManager { SkinManager* GetSkin(int a); };       // 0x004C49E0
struct AnimCreatureMgr { bool HandleAnimatedEvent(AnimEventInfo_s0058_9ce0* e); };   // 0x0059D300
struct UIHints_s0058_9ce0 { void SetEnabled(); };               // 0x0067C420
struct AuthMgr { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
                 virtual void v8(); virtual bool IsX(); };   // +0x24
AuthMgr* __cdecl GetAuthManager();                   // 0x00607A60
UIHints_s0058_9ce0* __stdcall GetUIHints(int a, int b);         // 0x0067CAC0
int  __cdecl FUN_00552300(void* key);
bool __cdecl GetCreatorType(void* key);              // 0x00641900
struct CamController { void SetCenterCameraOffset(); };   // 0x005A2370
struct IFace3 { virtual void v0(); virtual void v1(); virtual void v2(); virtual CamController* Cast(uint id); };
struct IFace2 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
                virtual void v12(); virtual void v13(); virtual IFace3* GetCtl(); };   // +0x38
struct IFace1 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
                virtual IFace2* GetCam(); };   // +0x50
struct EditorUIEx : EditorUI_s0058_9ce0 {
    bool FUN_005dc450();                       // 0x005DC450
    void FUN_005dd090(int a);                  // 0x005DD090
    void EnableBasicEditorButtons(int a, int b);   // 0x005DE690
    void FUN_005dd1d0();                       // 0x005DD1D0
    void Hide();                               // 0x005DD050
};
struct UndoListVec {
    UndoEntry** mpBegin;
    void Resize(int n);   // 0x005E77E0
};
struct LocalStateVec {
    void Resize(int n);   // 0x00584160
};
struct ModelMem { char pad0[0xC]; Key12 key; char pad1[0x40]; uint f58; };
namespace SP {
class cAppModeEditorBase_s0058_9ce0 {
public:
    // The real class begins with the cIAppMode vtable; the name provider sub-object is at +0xC.
    virtual void v0();
    char pad[0x1000];

    void FUN_00589ce0(const wchar_t* path);              // 0x00589ce0
    void LoadModelInternal(void* model);                  // 0x0058a1e0
    void LoadModel(int mode, int a, int b);               // 0x0058a350
    void Undo(char postMsg, char isRedoFlag);             // 0x0058a5a0
    void Redo();                                          // 0x0058a950

    // callees (other slices)
    void PrepareAppForNewModel(void* res);                // 0x00586B00
    void SetCurrentConfig(int cfg, int z0, int z1, int z2);   // 0x00579720
    void InitializeUndoList();                            // 0x00586690
    void ResetEconomy();                                  // 0x005754C0
    void ShowError(Key16 a, Key16 b);                     // 0x005721B0
    Out16* GetMask(Out16* out);                           // 0x0057A960
    void SetLocalState(LocalState* ls);                   // 0x0057C2F0
    Out16* SomeSetup(Out16* out, void* entry, uint v, int one);   // 0x0057AC00
    int  FUN_00576140();                                  // 0x00576140
    void FUN_00572220(void* m);                           // 0x00572220
    void FUN_0057bfb0();                                  // 0x0057BFB0
    void FUN_005802f0(int a, int b);                      // 0x005802F0
    void FUN_0057e8a0();                                  // 0x0057E8A0
    void FUN_0057c1e0();                                  // 0x0057C1E0
    void FUN_00572430(void* key);                         // 0x00572430
    void SetMode(int a, int b);                           // 0x00587270
    void FUN_00573f20(int v);                             // 0x00573F20
    void FUN_00582fe0(int a, int b);                      // 0x00582FE0
    void FUN_0057e340(int a);                             // 0x0057E340
    void FUN_0057c0e0();                                  // 0x0057C0E0
};  // namespace SP
}
// ---- items of slice s00589ce0 end

// ---- items of slice s0058be50 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kInvalidAbilityValue;   // @ 0x150cea8
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }
#define PV_s0058_be50(n) virtual void _v##n();
struct Vector3_s0058_be50 {
    float x, y, z;
    Vector3_s0058_be50() {}
    Vector3_s0058_be50(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3_s0058_be50(const Vector3_s0058_be50& v) : x(v.x), y(v.y), z(v.z) {}
};
inline Vector3_s0058_be50 operator+(const Vector3_s0058_be50& a, const Vector3_s0058_be50& b) { return Vector3_s0058_be50(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vector3_s0058_be50 operator*(const Vector3_s0058_be50& a, float s) { return Vector3_s0058_be50(a.x * s, a.y * s, a.z * s); }
extern const Vector3_s0058_be50 kTransformZero;       // @ 0x15e4fd4
extern const Vector3_s0058_be50 kCameraFocusDefault;  // @ 0x15e4f18
extern const Vector3_s0058_be50 kShadowDirection;     // @ 0x150cd50
struct Matrix3_s0058_be50 {
    float m[9];
    Matrix3_s0058_be50(const Matrix3_s0058_be50& o);             // @ 0x41cb40 (out of line)
};
extern const Matrix3_s0058_be50 kTransformIdentity;   // @ 0x15e5114
struct cSPTransform_s0058_be50 {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vector3_s0058_be50 mTranslation;
    float mScale;
    Matrix3_s0058_be50 mRotation;
    __forceinline cSPTransform_s0058_be50()
        : mFlags(0), mModificationCount(0), mTranslation(kTransformZero), mScale(1.0f),
          mRotation(kTransformIdentity) {}
    void SetTranslation(const Vector3_s0058_be50& v) { mTranslation = v; mFlags |= 4; mModificationCount++; }
};
struct cSPBoundingBox_s0058_be50 {
    Vector3_s0058_be50 mMin, mMax;
    Vector3_s0058_be50 GetCenter() const { return (mMin + mMax) * 0.5f; }
};
namespace EA {
class Stopwatch_s0058_be50 {
public:
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfStopwatchCyclesToUnitsCoefficient;
    bool IsRunning() const { return mnStartTime != 0; }
    uint64_t GetElapsedTime() const;                                  // @ 0x93a5e0
};
}
namespace SP {
class cPropertyList_s0058_be50 {
public:
    virtual int AddRef();
    virtual int Release();                                            // 0x04
};
}
namespace SP {
template<class T> struct AutoRefCount_s0058_be50 {
    T* mpObject;
    AutoRefCount_s0058_be50() : mpObject(0) {}
    AutoRefCount_s0058_be50(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount_s0058_be50() { if (mpObject) mpObject->Release(); }
    operator T*() const { return mpObject; }
    T* operator->() const { return mpObject; }
    AutoRefCount_s0058_be50& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
    T** ReleaseAndGetAddressOf()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};
}
namespace SP {
typedef AutoRefCount_s0058_be50<cPropertyList_s0058_be50> PropertyListPtr;
}
namespace SP {
template<class T> struct RefPtr {           // intrusive pointer member (only read here)
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
};
}
namespace SP {
class cIPropertyManager_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10)
    virtual bool GetPropertyListRaw(uint32_t instanceID, uint32_t groupID, cPropertyList_s0058_be50** ppList);  // 0x2c
    bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyListPtr& list)
    {
        return GetPropertyListRaw(instanceID, groupID, list.ReleaseAndGetAddressOf());
    }
};
}
namespace SP {
cIPropertyManager_s0058_be50* PropertyManager();                                // @ 0x67de30
}
namespace SP {
bool GetPropertyAsInt(const cPropertyList_s0058_be50* list, uint32_t id, int* value);               // @ 0x410370
}
namespace SP {
bool GetPropertyAsKeyInstance(const cPropertyList_s0058_be50* list, uint32_t id, uint32_t* value);  // @ 0x6a12a0
}
namespace SP {
bool GetPropertyAsVector3(const cPropertyList_s0058_be50* list, uint32_t id, Vector3_s0058_be50* value);       // @ 0x6a1110
}
namespace SP {
class cDirectPropertyList_s0058_be50 {
public:
    char pad0[0x3c];
    int* mpDirectValues;                    // +0x3c
    int GetIntProperty(uint32_t id) const;                            // @ 0x6a2660
    bool GetBoolProperty(uint32_t id) const;                          // @ 0x6a25a0
    bool GetDirectBool(int index) const { return mpDirectValues[index] != 0; }
};
}
namespace SP {
extern cDirectPropertyList_s0058_be50* sAppProperties_s0058_be50;                           // @ 0x15fd918
}
namespace SP {
class cTestSystem { public:
    char pad0[0x70];
    struct ListNode { ListNode* mpNext; ListNode* mpPrev; } mTests;  // +0x70
    bool IsTestingInProgress() const { return mTests.mpNext != &mTests; }
};
}
namespace SP {
extern cTestSystem* sTestSystem;                                      // @ 0x15fd928
}
namespace SP {
class cString_s0058_be50 {
public:
    uint32_t mData[5];
    cString_s0058_be50(uint32_t tableID, uint32_t instanceID, const wchar_t* source);  // @ 0x6b5770
    ~cString_s0058_be50();                                                       // @ 0x6b5240
    const wchar_t* GetText();                                         // @ 0x6b55c0
};
}
namespace SP {
class cSPEditorBlock_s0058_be50;
}
namespace SP {
class cSPEditorHandle_s0058_be50 {
public:
    cSPEditorBlock_s0058_be50* GetEditorBlock();                                 // @ 0x47e6c0
};
}
namespace SP {
class cSPEditorHandleBase {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2)
    virtual void* Cast(uint32_t typeID);                              // 0x0c
};
}
namespace SP {
template<class T> struct RefPtr;
}
namespace SP {
template<class T, class U> inline T* object_cast(const RefPtr<U>& p)
{
    return p.mpObject ? (T*)p.mpObject->Cast(T::kType) : 0;
}
}
namespace SP {
class cSPEditorHandleDeform_s0058_be50 : public cSPEditorHandle_s0058_be50 {
public:
    enum { kType = 0x050a993c };
};
}
namespace SP {
class cSPEditorBlock_s0058_be50 {
public:
    char pad0[0xdc8];
    uint32_t mBooleanAttributes[2];         // +0xdc8 (eastl::bitset<64>)
    bool HasAttribute(int i) const { bool b = ((mBooleanAttributes[i >> 5] >> (i & 31)) & 1) != 0; return b; }
    int GetIndexForHandle(cSPEditorHandle_s0058_be50* handle);                   // @ 0x43c3d0
    void UpdateHandlePreviewDeform(float delta, int index);           // @ 0x43e3f0
    void UpdateEffectsMask();                                         // @ 0x4488c0
    cSPBoundingBox_s0058_be50 GetBBox(int type, bool a, bool b);                 // @ 0x44ae00
};
}
namespace SP {
enum { kAttrSellable = 1, kAttrHasSellValue = 32 + 5 };
}
namespace SP {
int GetBlockSellValue(cSPEditorBlock_s0058_be50* block, int flags);              // @ 0x491350
}
namespace SP {
class cSPEditorModel_s0058_be50 {
public:
    char pad0[0x58];
    void* mpResource;                       // +0x58
    bool IsModelBalanced();                                           // @ 0x4ad070
    uint32_t GetBlockCount();                                         // @ 0x4accf0
    cSPEditorBlock_s0058_be50* GetBlock(uint32_t index);                         // @ 0x4accb0
    void Update(int deltaMS);                                         // @ 0x4ad210
};
}
namespace SP {
class cSPEditorEffect {
public:
    virtual void AddRef();                                            // 0x00
    virtual void Release();                                           // 0x04
    PV_s0058_be50(2) PV_s0058_be50(3)
    virtual bool IsRunning();                                         // 0x10
    PV_s0058_be50(5)
    virtual void SetTransform(cSPTransform_s0058_be50* t);                       // 0x18
    PV_s0058_be50(7)
    virtual void GetTransform(cSPTransform_s0058_be50* t);                       // 0x20
    PV_s0058_be50(9) PV_s0058_be50(10)
    virtual void Stop(bool hardStop);                                 // 0x2c
};
}
namespace SP {
class cSPEditorEffects {
public:
    cSPEditorEffect* Get(uint32_t id);                                // @ 0x45b210
    cSPEditorEffect* GetForBlock(cSPEditorBlock_s0058_be50* block);              // @ 0x45b210
    void Destroy(cSPEditorBlock_s0058_be50* block);                              // @ 0x45b150
};
}
namespace SP {
cSPEditorEffects* EditorEffects();                                    // @ 0x401050
}
namespace SP {
class cSPEditorSellBackDetachedRollover_s0058_be50 {
public:
    bool IsVisible();                                                 // @ 0x5cc100
    void Hide();                                                      // @ 0x5cc0e0
};
}
namespace SP {
class cSPEditorSellBackRollover_s0058_be50 {
public:
    char pad0[0x78];
    char mCursorAttachment[0x28];           // +0x78 (cursor-attachment window base)
    int mValue;                             // +0xa0
    bool IsVisible();                                                 // @ 0x5cc6c0
    void Hide();                                                      // @ 0x5cc690
    void Show(const wchar_t* text, int value, bool canAfford);        // @ 0x5cc750
};
}
namespace SP {
class cSPEditorAsymmetryRollover {
public:
    char pad0[0x78];
    char mCursorAttachment[4];              // +0x78
    bool IsVisible();                                                 // @ 0x5beeb0
    void Hide();                                                      // @ 0x5bee80
    void Show(const wchar_t* text);                                   // @ 0x5bef50
};
}
namespace SP {
class cSPUICursorManager {
public:
    void SetCursorAttachment(void* window);                           // @ 0x8017f0
};
}
namespace SP {
cSPUICursorManager* CursorManager_s0058_be50();                                  // @ 0x67cab0
}
namespace SP {
class cSPEditorManipulator {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8)
    virtual void Update(float delta);                                 // 0x24
};
}
namespace SP {
class cEditorLimits {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12)
    virtual bool CanAfford(cSPEditorBlock_s0058_be50* block);                    // 0x34
};
}
namespace SP {
class cIModelWorld_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3)
    virtual int GetPendingLoadCount();                                // 0x10
};
}
namespace SP {
class cSPEditorPhysicsWorld_s0058_be50 {
public:
    void UpdatePhysics(int deltaMS);                                  // @ 0x4b95c0
};
}
namespace SP {
class cSPEditorSkinManager_s0058_be50 {
public:
    struct cSkin { char pad0[8]; void* mpResource; };
    cSkin* GetSkin(int index);                                        // @ 0x4c49e0
    struct cEditorUIState { uint32_t mState[2]; };
    void Update(cSPEditorBlock_s0058_be50* active, bool b, cEditorUIState torsoState);  // @ 0x4c38e0
    void UpdatePaintedSkin();                                         // @ 0x4c4290
};
}
namespace SP {
class cSPEditorSpine_s0058_be50 {
public:
    void Update(int deltaMS, cSPEditorModel_s0058_be50* model);                  // @ 0x5d07f0
    void DrawPathDebug();                                             // @ 0xc2e4e0
};
}
namespace SP {
class cSPEditorUI_s0058_be50 {
public:
    void UpdateIdleTimeout();                                         // @ 0x5dc580
    void Update(int deltaMS);                                         // @ 0x5de450
    class IWindow_s0058_be50* FindWindowByID(uint32_t id);                       // @ 0x5dc310
};
}
namespace SP {
class IWindow_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12) PV_s0058_be50(13)
    virtual const float* GetArea();                                   // 0x38
    PV_s0058_be50(15) PV_s0058_be50(16) PV_s0058_be50(17) PV_s0058_be50(18) PV_s0058_be50(19) PV_s0058_be50(20) PV_s0058_be50(21) PV_s0058_be50(22) PV_s0058_be50(23) PV_s0058_be50(24) PV_s0058_be50(25) PV_s0058_be50(26)
    virtual void SetArea(const float* area);                          // 0x6c
    PV_s0058_be50(28) PV_s0058_be50(29) PV_s0058_be50(30)
    virtual void SetFlag(int flag, bool value);                       // 0x7c
};
}
namespace SP {
namespace SPUIHelpers {
void AnchorWindowToWindow(IWindow_s0058_be50* window, IWindow_s0058_be50* anchor, int flags, IWindow_s0058_be50* parent);  // @ 0x807340
}
}
namespace SP {
class cSPPlayMode_s0058_be50 {
public:
    void Update(int deltaMS);                                         // @ 0x62c550
};
}
namespace SP {
class cSPEditorBudget_s0058_be50 {
public:
    void Update(int deltaMS);                                         // @ 0x4582b0
};
}
namespace SP {
class cSPEditorComplexityMeter_s0058_be50 {
public:
    void SetComplexityMeterPercentage(float percent);                 // @ 0x5a7410
    void Update(int deltaMS);                                         // @ 0x5a7220
};
}
namespace SP {
class cSPPaletteUI_s0058_be50 {
public:
    void UpdateCategories(int deltaMS);                               // @ 0x5ca980
};
}
namespace SP {
class cSpeciesProfile_s0058_be50 {
public:
    uint32_t mData[0xa08 / 4];
    struct cInit { void* mpBegin; void* mpEnd; void* mpCapacity; cInit() : mpBegin(0), mpEnd(0), mpCapacity(0) {} };
    cSpeciesProfile_s0058_be50(const cInit& init, int flags);                    // @ 0x4d3dd0
    ~cSpeciesProfile_s0058_be50();                                               // @ 0x4d44e0
    bool Update(void* resource);                                      // @ 0x4d5020
};
}
namespace SP {
class cSPPaintPaletteUI {
public:
    void Update(int deltaMS, cSpeciesProfile_s0058_be50* profile, int region);   // @ 0x59a980
};
}
namespace SP {
class cSPEditorVerbIconTray_s0058_be50 {
public:
    uint32_t GetSoundKey();                                           // @ 0x1137690
    float GetTotal();                                                 // @ 0x885d10
};
}
namespace SP {
struct VerbIconList {                       // eastl::vector<AutoRefCount<cSPEditorVerbIconData>>
    void* mpBegin; void* mpEnd; void* mpCapacity;
    VerbIconList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VerbIconList();                                                  // @ 0x4b5440
};
}
namespace SP {
struct cAbilityValue { int mAbility; float mValue; };
}
extern "C" void EASTL_allocator_deallocate(void* p);                 // @ 0xf47380
namespace SP {
struct AbilityValueList {                   // a plain array buffer released through the EA allocator
    cAbilityValue* mpBegin; cAbilityValue* mpEnd; cAbilityValue* mpCapacity;
    AbilityValueList() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~AbilityValueList() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
    int size() const { return (int)(mpEnd - mpBegin); }
};
}
namespace SP {
class cSPVerbTrayCollection_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4)
    virtual void SetIcons(VerbIconList* icons);                       // 0x14
    PV_s0058_be50(6)
    virtual void Update(int deltaMS);                                 // 0x1c
    int GetTrayCount();                                               // @ 0x605930
    float GetTotalHeight();                                           // @ 0x6058b0
    cSPEditorVerbIconTray_s0058_be50* GetTray(int index);                        // @ 0x5c1ce0
};
}
namespace SP {
namespace EditorUtils {
void ComputeCellVerbIcons(void* resource, cSPVerbTrayCollection_s0058_be50* trays, int region, float value);  // @ 0x4e87f0
}
}
namespace SP {
namespace EditorUtils {
void ComputeCreatureVerbIcons(cSPEditorModel_s0058_be50* model, cSPVerbTrayCollection_s0058_be50* trays);               // @ 0x4e6bc0
}
}
namespace SP {
namespace EditorUtils {
void ComputeVehicleVerbIcons(VerbIconList* icons, void* resource);                                 // @ 0x4e7990
}
}
namespace SP {
namespace EditorUtils {
void ComputeVehicleAbilityValues(cSPEditorModel_s0058_be50* model, AbilityValueList* values);                 // @ 0x4333c0
}
}
namespace SP {
namespace EditorUtils {
void ComputeVehicleAbilities(AbilityValueList* values, VerbIconList* icons, void* resource);       // @ 0x4e7610
}
}
namespace SP {
class cEditorTactilityManager {
public:
    PV_s0058_be50(0) PV_s0058_be50(1)
    virtual void Update(int deltaMS);                                 // 0x08
};
}
namespace SP {
cEditorTactilityManager* EditorTactilityManager();                    // @ 0x401060
}
namespace SP {
class cEditorCameraController {
public:
    void SetCameraOffsetPosition(Vector3_s0058_be50 position, bool instant);     // @ 0x5a2010
    void DoAutoZoom(cSPEditorModel_s0058_be50* model, int deltaMS);              // @ 0x5a33c0
};
}
namespace SP {
class cCameraManager_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2)
    virtual cEditorCameraController* GetCamera(uint32_t id);          // 0x0c
};
}
namespace SP {
class cGameModeManager {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12) PV_s0058_be50(13)
    virtual cCameraManager_s0058_be50* GetCameraManager();                       // 0x38
};
}
namespace SP {
class cIGameModeOwner {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12) PV_s0058_be50(13) PV_s0058_be50(14)
    PV_s0058_be50(15) PV_s0058_be50(16) PV_s0058_be50(17) PV_s0058_be50(18) PV_s0058_be50(19)
    virtual cGameModeManager* GetGameModeManager();                   // 0x50
};
}
namespace SP {
class cSPEditorAnimatedCreatureManager_s0058_be50 {
public:
    bool GetCreaturePosition(uint32_t creatureID, Vector3_s0058_be50* position);  // @ 0x59d110
    void Update(int deltaMS);                                         // @ 0x59d610
    bool IsAnimationPlaying(uint32_t creatureID, uint32_t animID);    // @ 0x59cc40
};
}
namespace SP {
class cUIHints {
public:
    void Update();                                                    // @ 0x67c960
};
}
namespace SP {
cUIHints* UIHints();                                                  // @ 0x67cac0
}
namespace SP {
class cAchievementNotifier {
public:
    void Update();                                                    // @ 0x5fdf40
};
}
namespace SP {
cAchievementNotifier* AchievementNotifier();                          // @ 0x67cae0
}
namespace SP {
class cViewer_s0058_be50 {
public:
    void GetCameraLocationInfo(Vector3_s0058_be50* position, Vector3_s0058_be50* direction, Vector3_s0058_be50* up, Vector3_s0058_be50* right) const;  // @ 0x7c3d30
};
}
namespace SP {
class cRenderer_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6)
    virtual cViewer_s0058_be50* GetMainViewer();                                 // 0x1c
};
}
namespace SP {
class cIApp_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12) PV_s0058_be50(13) PV_s0058_be50(14)
    PV_s0058_be50(15) PV_s0058_be50(16) PV_s0058_be50(17) PV_s0058_be50(18) PV_s0058_be50(19)
    virtual cRenderer_s0058_be50* GetRenderer();                                 // 0x50
};
}
namespace SP {
cIApp_s0058_be50* App_s0058_be50();                                                         // @ 0x67dd10
}
namespace SP {
class cShadowWorld_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2)
    virtual void Update();                                            // 0x0c
    PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11)
    virtual void SetDirection(const Vector3_s0058_be50* direction);              // 0x30
    PV_s0058_be50(13)
    virtual void SetCentreOfInterest(const Vector3_s0058_be50* centre, const Vector3_s0058_be50* direction);  // 0x38
    virtual void SetEffectiveViewer(const Vector3_s0058_be50* cameraPosition);   // 0x3c
    PV_s0058_be50(16) PV_s0058_be50(17) PV_s0058_be50(18)
    virtual uint32_t GetType();                                       // 0x4c
};
}
namespace SP {
class cLightingWorld_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12) PV_s0058_be50(13)
    virtual cPropertyList_s0058_be50* GetPropertyList();                         // 0x38
};
}
namespace SP {
class cSPEditorAnimatedEventInfo_s0058_be50 {
public:
    PV_s0058_be50(0)
    virtual int AddRef();                                             // 0x04
    virtual int Release();                                            // 0x08
};
}
namespace SP {
struct TutorialShownMap {
    struct iterator { void* mpNode; };
    uint32_t mCompare;                      // +0x00 (+0x454 in the editor)
    char mAnchor[0x10];                     // +0x04 (+0x458)
    iterator find(const uint32_t& key);                               // @ 0xe5c780
    bool& operator[](const uint32_t& key);                            // @ 0x5841b0
    bool IsEnd(const iterator& it) { return it.mpNode == (void*)mAnchor; }
};
}
namespace SP {
enum { kModeBuild = 0, kModePaint = 1, kModePlay = 2 };
}
namespace SP {
enum { kSaveStateNone = 0, kSaveStateDone = 6 };
}
namespace SP {
enum { kTransitionWaiting = 1, kTransitionDone = 0 };
}
namespace SP {
class cAppModeEditorBase_s0058_be50 {
public:
    PV_s0058_be50(0) PV_s0058_be50(1) PV_s0058_be50(2) PV_s0058_be50(3) PV_s0058_be50(4) PV_s0058_be50(5) PV_s0058_be50(6) PV_s0058_be50(7) PV_s0058_be50(8) PV_s0058_be50(9) PV_s0058_be50(10) PV_s0058_be50(11) PV_s0058_be50(12) PV_s0058_be50(13) PV_s0058_be50(14)
    PV_s0058_be50(15) PV_s0058_be50(16)
    virtual int GetEditorID();                                        // 0x44
    virtual void HandleSimulationUpdate(float delta1, float delta2);  // 0x0058be50 (SP::cAppModeEditorBase::HandleSimulationUpdate)

    uint32_t pad04[7];
    RefPtr<cIGameModeOwner> mpGameModeOwner;               // +0x20
    RefPtr<cPropertyList_s0058_be50> mpPropList;                      // +0x24
    float mMouseX;                                  // +0x28
    float mMouseY;                                  // +0x2c
    uint32_t mMouseState;                           // +0x30
    uint32_t pad34[2];
    uint32_t mModifierFlags;                        // +0x3c
    uint32_t pad40[14];
    RefPtr<cSPEditorUI_s0058_be50> mpEditorUI;                        // +0x78
    RefPtr<cSPPlayMode_s0058_be50> mpPlayMode;                        // +0x7c
    RefPtr<cLightingWorld_s0058_be50> mpLightingWorld;                // +0x80
    RefPtr<cIModelWorld_s0058_be50> mpMainModelWorld;                 // +0x84
    uint32_t pad88[2];
    RefPtr<cSPEditorPhysicsWorld_s0058_be50> mpPhysicsWorld;          // +0x90
    uint32_t pad94;
    RefPtr<cSPEditorModel_s0058_be50> mpEditorModel;                  // +0x98
    uint32_t pad9c[12];
    RefPtr<cSPEditorBlock_s0058_be50> mpActivePart;                   // +0xcc
    RefPtr<cSPEditorBlock_s0058_be50> mpMovingPart;                   // +0xd0
    RefPtr<cSPEditorBlock_s0058_be50> mpSelectedPart;                 // +0xd4
    uint32_t padd8[3];
    RefPtr<cSPEditorHandleBase> mpActiveHandle;            // +0xe4
    cSPEditorSkinManager_s0058_be50::cEditorUIState mTorsoUIState;  // +0xe8
    uint32_t padf0[20];
    uint8_t pad140;
    bool mbPreviewDeformHandle;                     // +0x141
    bool mbShowCloningRollover;                     // +0x142
    bool mbShowAsymmetryRollover;                   // +0x143
    uint32_t pad144;
    RefPtr<cSPEditorManipulator> mpActiveManipulator;      // +0x148
    RefPtr<cSPEditorSpine_s0058_be50> mpSpine;                        // +0x14c
    RefPtr<cSPEditorSkinManager_s0058_be50> mpSkinManager;            // +0x150
    uint32_t pad154[16];
    uint32_t mTransitionAnimationID;                // +0x194
    int mTransitionState;                           // +0x198
    uint32_t pad19c[3];
    int mTransitionMode;                            // +0x1a8
    uint32_t pad1ac[8];
    RefPtr<void> mpEditorRequest;                          // +0x1cc
    uint32_t pad1d0[43];
    uint32_t mDeleteEffectID;                       // +0x27c
    uint32_t pad280[5];
    RefPtr<cShadowWorld_s0058_be50> mpShadowWorld;                    // +0x294
    uint32_t pad298[3];
    RefPtr<cSPVerbTrayCollection_s0058_be50> mpVerbIconTray;          // +0x2a4
    uint32_t mTutorialKey;                          // +0x2a8
    uint32_t pad2ac;
    bool mIsActive;                                 // +0x2b0
    uint8_t pad2b1[0x41];
    bool mbUseSpine;                                // +0x2f2
    uint8_t pad2f3[0x29];
    int mMode;                                      // +0x31c
    uint32_t pad320[11];
    int mCurrentBlockRegion;                        // +0x34c
    RefPtr<cSPEditorBudget_s0058_be50> mpBudget;                      // +0x350
    RefPtr<cSPEditorComplexityMeter_s0058_be50> mpComplexityMeter;    // +0x354
    uint32_t pad358;
    RefPtr<cSPPaintPaletteUI> mpPaintPaletteUI;            // +0x35c
    RefPtr<cSPEditorAnimatedCreatureManager_s0058_be50> mpAnimCreatureManager;  // +0x360
    uint32_t mAnimatingCreatureID;                  // +0x364
    uint32_t pad368[6];
    AutoRefCount_s0058_be50<cSPEditorAnimatedEventInfo_s0058_be50> mpAnimEvent;  // +0x380
    uint8_t pad384;
    bool mbModelBalanced;                           // +0x385
    uint8_t pad386[2];
    int mPostSaveAction;                            // +0x388
    int mSaveInProgress;                            // +0x38c
    uint32_t pad390[11];
    RefPtr<cSPPaletteUI_s0058_be50> mpPartsPaletteUI;                 // +0x3bc
    uint32_t pad3c0;
    RefPtr<cSPPaletteUI_s0058_be50> mpPaintCategoriesUI;              // +0x3c4
    uint32_t pad3c8[6];
    bool mIsRecordingGIF;                           // +0x3e0
    bool mbCountGIFFrames;                          // +0x3e1
    uint8_t pad3e2[2];
    int mGIFFrameCount;                             // +0x3e4
    uint32_t pad3e8[19];
    RefPtr<cEditorLimits> mpEditorLimits;                  // +0x434
    uint32_t pad438[7];
    TutorialShownMap mTutorialShown;                // +0x454
    uint32_t pad468[11];
    RefPtr<cSPEditorSellBackRollover_s0058_be50> mpSellBackRollover;  // +0x494
    RefPtr<cSPEditorSellBackRollover_s0058_be50> mpCloningRollover;   // +0x498
    RefPtr<cSPEditorAsymmetryRollover> mpAsymmetryRollover;  // +0x49c
    uint32_t pad4a0;
    RefPtr<cSPEditorSellBackDetachedRollover_s0058_be50> mpDeleteValueRollover;  // +0x4a4
    float mDeleteValueFadeTime;                     // +0x4a8
    uint32_t pad4ac[7];
    bool mbStopDeleteEffects;                       // +0x4c8
    bool mbDrawSpineDebug;                          // +0x4c9
    uint8_t pad4ca[0x5a8 - 0x4ca];
    EA::Stopwatch_s0058_be50 mIdleStopwatch;                   // +0x5a8

    cSPEditorModel_s0058_be50* GetEditorModel() const { return mpEditorModel; }
    cSPEditorSkinManager_s0058_be50::cSkin* GetSkin() { return mpSkinManager ? mpSkinManager->GetSkin(1) : 0; }

    void OnIdleTimeout();                                             // @ 0x575120
    void StopFade();                                                  // @ 0x5724a0
    cSPEditorBlock_s0058_be50* GetCloningBlock();                                // @ 0x573a10
    float UpdateCurrentComplexityPercent();                           // @ 0x5745c0
    void UpdateSpineVertebra(int deltaMS);                            // @ 0x575520
    void HandleAnimatedEvent(cSPEditorAnimatedEventInfo_s0058_be50* info);       // @ 0x585330
    void UpdateBabyCreatures(int deltaMS);                            // @ 0x577e10
    void UpdateAnimatedCreature();                                    // @ 0x57ae10
    void UpdateIdleAnimations(float x, float y, int deltaMS);         // @ 0x57e480
    bool OnMouseMoveUpdate(float x, float y, uint32_t state, int deltaMS);  // @ 0x58ba60
    void ShowTutorial();                                              // @ 0x572260
    void ContinueSaveInProgress();                                    // @ 0x585d40
    void HandleRequestedPostSaveAction();                             // @ 0x57ebf0
    void SendAppSwitchMessage();                                      // @ 0x57c0e0
    void UpdateModelSounds(int deltaMS);                              // @ 0x574f30
    void SetCursorBasedOnModeModifiers();                             // @ 0x5733d0
};
}
// ---- items of slice s0058be50 end

// ---- items of slice s0058d430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t kGroupCreature;                                  // 0x0150ce74
extern uint32_t kGroupBuilding;                                  // 0x0150ce78
extern uint32_t kGroupVehicle;                                   // 0x0150ce7c
extern uint32_t kGroupUFO;                                       // 0x0150ce80
extern uint32_t kGroupFlora;                                     // 0x0150ce84
extern uint32_t kGroupCell;                                      // 0x0150ce88
extern bool sTimingEnabled;                                      // 0x015deff8
extern bool sValidityInitialized;                                // 0x015da6e4
struct ResourceKey_s0058_d430 {
    uint32_t instance, type, group;
};
extern char gEmptyString_s0058_d430[];                                      // 0x01667bac
struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    string8() : mpBegin(gEmptyString_s0058_d430), mpEnd(gEmptyString_s0058_d430), mpCapacity(gEmptyString_s0058_d430 + 1) {}
    __forceinline ~string8() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] mpBegin;
    }
    const char* c_str() const { return mpBegin; }
};
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin((wchar_t*)gEmptyString_s0058_d430), mpEnd((wchar_t*)gEmptyString_s0058_d430),
                 mpCapacity((wchar_t*)gEmptyString_s0058_d430 + 1) {}
    __forceinline ~string16() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin)
            delete[] (char*)mpBegin;
    }
    const wchar_t* c_str() const { return mpBegin; }
};
struct sp_vector_allocator_s0058_d430 {
    uint32_t mFlags;
    sp_vector_allocator_s0058_d430() {}
};
struct ResourceKeyVector {                                       // eastl::vector<ResourceKey, sp_vector_allocator>
    ResourceKey_s0058_d430* mpBegin;
    ResourceKey_s0058_d430* mpEnd;
    ResourceKey_s0058_d430* mpCapacity;
    sp_vector_allocator_s0058_d430 mAllocator;
    ResourceKeyVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~ResourceKeyVector() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            delete[] (char*)mpBegin;
    }
    bool empty() const { return mpBegin == mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    ResourceKey_s0058_d430& operator[](int i) { return mpBegin[i]; }
    void push_back(const ResourceKey_s0058_d430& key);                      // 0x004e19a0
};
struct FloatVector {                                             // eastl::vector<float, sp_vector_allocator>
    float* mpBegin;
    float* mpEnd;
    float* mpCapacity;
    sp_vector_allocator_s0058_d430 mAllocator;
    __forceinline explicit FloatVector(int n) {
        mpBegin = n ? (float*)new("Editor", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1) char[n * sizeof(float)] : 0;
        mpCapacity = mpBegin + n;
        for (float* p = mpBegin; p != mpCapacity; ++p)
            *(uint32_t*)p = 0;
        mpEnd = mpCapacity;
    }
    __forceinline ~FloatVector() {
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            delete[] (char*)mpBegin;
    }
    int size() const { return (int)(mpEnd - mpBegin); }
    float& operator[](int i) { return mpBegin[i]; }
};
struct MeshVertex;
struct VertexVector {                                            // vector of geometry records
    MeshVertex* mpBegin;
    MeshVertex* mpEnd;
    MeshVertex* mpCapacity;
    sp_vector_allocator_s0058_d430 mAllocator;
    VertexVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    __forceinline ~VertexVector() {
        DestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((uint32_t*)mpBegin)[-1])
            delete[] (char*)mpBegin;
    }
    void DestroyValues(MeshVertex* first, MeshVertex* last);    // 0x004243e0
};
struct IResource {
    virtual int AddRef();
    virtual int Release();
    virtual void v08();
    virtual void* Cast(uint32_t typeID);                         // +0x0c
};
template<class T> struct AutoRefCount_s0058_d430 {
    T* mpObject;
    AutoRefCount_s0058_d430() : mpObject(0) {}
    explicit AutoRefCount_s0058_d430(T* p) : mpObject(p) { if (p) p->AddRef(); }
    ~AutoRefCount_s0058_d430() { if (mpObject) mpObject->Release(); }
    __forceinline T** AsPointer() {
        if (mpObject) {
            T* p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator bool() const { return mpObject != 0; }
};
struct IResourceFilter {
    virtual ~IResourceFilter() {}
};
struct ResourceKeyFilter : IResourceFilter {                     // vtable 0x013eb898
    uint32_t mInstance;
    uint32_t mGroup;
    uint32_t mType;
    uint32_t mMask;
    ResourceKeyFilter() : mInstance(0xffffffff), mGroup(0xffffffff), mType(0xffffffff), mMask(0xffffffff) {}
    virtual bool IsValid(const ResourceKey_s0058_d430& key);
};
struct IResourceManager_s0058_d430 {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey_s0058_d430* key, IResource** ppResource,
                             int a, int b, int c, int d);         // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool WriteResource(IResource* res, int a, void* saveArea, int b,
                               const ResourceKey_s0058_d430* key);          // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual int GetResourceKeyList(ResourceKeyVector* keys, IResourceFilter* filter, int flags);   // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
    virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78();
    virtual bool GetFileName(const ResourceKey_s0058_d430* key, string16* name);   // +0x7c
};
struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    ResourceKey_s0058_d430 mResourceKey;                                    // +0x08
    cPropertyList();                                             // 0x006a1c40
};
struct IPropertyManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** ppList);   // +0x2c
};
struct cEditorModelResource {                                    // 0x3c609f8
    uint32_t pad0[2];
    ResourceKey_s0058_d430 mKey;                                            // +0x08
    uint32_t pad14;
    uint32_t mModelType;                                         // +0x18
};
struct cLocalizedName {                                          // 0x30bdee3
    const wchar_t* GetText();                                    // 0x00414e10
};
struct cSPEditorModelResource {                                  // 0xac bytes
    virtual int AddRef();
    virtual int Release();
    uint32_t mRefCount;                                          // +0x04
    ResourceKey_s0058_d430 mKey;                                            // +0x08
    uint32_t pad14[(0xac - 0x14) / 4];
    cSPEditorModelResource();                                    // 0x004b9c70
};
struct ModelResourceRef {
    cSPEditorModelResource* mpObject;
    explicit ModelResourceRef(cSPEditorModelResource* p);        // 0x00572660
};
struct cSPEditorModel {
    virtual void SetName(const wchar_t* name);                   // +0x00
    uint32_t GetCreationID();                                    // 0x004ae000
    void SaveResource(cSPEditorModelResource* res);              // 0x004af260
};
struct IMessageListener_s0058_d430 {
    virtual void v00();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);   // +0x04
};
struct ValidityBits {                                            // eastl::bitset<128>
    uint32_t mWord[4];
    bool test(uint32_t i) const {
        if (i < 128)
            return (mWord[i >> 5] & (1u << (i & 31))) != 0;
        return false;
    }
};
struct LoadParams { uint32_t v[4]; };
struct cAppModeEditorBase_s0058_d430 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34(); virtual void v38();
    virtual void v3c();
    virtual cSPEditorModel* GetModel();                          // +0x40
    virtual uint32_t GetEditorConfig();                          // +0x44
    uint32_t pad04[3];
    IMessageListener_s0058_d430 mMessageListener;                           // +0x10
    uint32_t pad14[(0x2a8 - 0x14) / 4];
    uint32_t mModelType;                                         // +0x2a8
    uint32_t mSaveAreaID;                                        // +0x2ac

    void LoadModel(const ResourceKey_s0058_d430& key, LoadParams params, int flags);   // 0x0058cee0
    int ScoreCreatureForZCorp();                                 // 0x00574b40
    void SaveModel(const ResourceKey_s0058_d430* key, int flags);           // 0x0057f6c0
};
struct MessageBasicRC5 {
    uint32_t mHeader[2];
    uint32_t mData[5];
    explicit MessageBasicRC5(int a);                             // 0x00421c80
    ~MessageBasicRC5();                                          // 0x00421cf0
};
struct cUIHint {
    uint32_t pad0[0x78 / 4];
    struct cString { const wchar_t* GetString(); } mText;        // +0x78, GetString 0x006b55c0
};
struct cUIHints_s0058_d430 {
    cUIHint* FindByID(uint32_t id);                              // 0x0067aee0
};
namespace EA {
namespace ArgScript {
struct cIParser_s0058_d430;
}
}
namespace EA {
namespace ArgScript {
struct cArguments_s0058_d430 {
    const char** MainArguments(int& count, int start, int max); // 0x00838020
};
}
}
namespace EA {
namespace ArgScript {
void Output(cIParser_s0058_d430* parser, const char* fmt, ...);             // 0x00841000
}
}
IResourceManager_s0058_d430* GetManager_s0058_d430();                                  // 0x0067dcd0
IPropertyManager* PropertyManager_s0058_d430();                             // 0x0067de30
cUIHints_s0058_d430* UIHints_s0058_d430();                                             // 0x0067cac0
bool SPKeyFromName(ResourceKey_s0058_d430* key, const char* name, uint32_t defType, uint32_t defGroup);   // 0x0068d5a0
void SPNameFromKey(const ResourceKey_s0058_d430* key, string8* name, int flags);   // 0x0068d290
uint32_t EditorEntityToResourceType(uint32_t entity, int flags); // 0x004bbd20
uint32_t GetConfigFromModelType(uint32_t modelType);             // 0x00432f10
string16 ConvertToString16_s0058_d430(const char* text, int length);        // 0x0093c5a0
uint32_t CreationIDFromModel(uint32_t id);                       // 0x00572c50
void* GetSaveArea_s0058_d430(uint32_t id);                                  // 0x006b1f90
bool SavePropertyList(cPropertyList* props, void* saveArea, int flags);   // 0x006b1d50
void InitializeValidityData();                                   // 0x004ebe20
void DumpPalettes();                                             // 0x004eb980
void GetResourceDisplayName(const ResourceKey_s0058_d430* key, string16* name, int flags);   // 0x00b1e4d0
ValidityBits CalculateValidity(cEditorModelResource* model, ValidityBits mask, int flags);   // 0x004f3de0
bool IsValid(ValidityBits result, ValidityBits mask);            // 0x004f3d60
uint32_t GetValidityHintID(uint32_t bit);                        // 0x004f3c40
bool GetPropertyAsKey(cPropertyList* props, uint32_t id, ResourceKey_s0058_d430* key);   // 0x006a1250
void ReadGeometry(void* model, VertexVector* out);               // 0x0072fff0
float ComputeGeometryMetric(VertexVector* geom);                 // 0x00572b30
void SetPropertyKeys(cPropertyList* props, uint32_t id, int count, const ResourceKey_s0058_d430* keys);   // 0x006a0ee0
void SetPropertyFloats(cPropertyList* props, uint32_t id, int count, const float* values);    // 0x006a0dc0
extern LoadParams kDefaultLoadParams;                            // 0x015dac10
extern ValidityBits kValidityAll;                                // 0x015da860
extern ValidityBits kValidityLoadable;                           // 0x015da9c8
extern ValidityBits kValidityEditable;                           // 0x015da784
extern ValidityBits kValidityPlayable;                           // 0x015da7c4
extern ValidityBits kValidityPollinatable;                       // 0x015dab94
extern ValidityBits kValidityWarning;                            // 0x015daa40
uint32_t GetModelGroup(uint32_t type);                           // 0x00572110
__declspec(noinline) uint32_t GetModelGroup(uint32_t type) {
    switch (type) {
    case 0x3d97a8e4: return kGroupCreature;
    case 0x2399be55: return kGroupVehicle;
    case 0x24682294: return kGroupUFO;
    case 0x438f6347: return kGroupCell;
    case 0x476a98c7: return kGroupFlora;
    default:         return kGroupBuilding;
    }
}
__forceinline void FixupModelKey(ResourceKey_s0058_d430& key) {
    if (key.group == 0xffffffff) {
        switch (key.type) {
        case 0x3d97a8e4: key.group = kGroupCreature; break;
        case 0x2399be55: key.group = kGroupVehicle; break;
        case 0x24682294: key.group = kGroupUFO; break;
        case 0x2b978c46: key.group = kGroupBuilding; break;
        case 0x438f6347: key.group = kGroupCell; break;
        case 0x476a98c7: key.group = kGroupFlora; break;
        }
    }
    if (key.type == 0x1a99b06b && (key.group & 0xc0000000) == 0x40000000)
        key.type = EditorEntityToResourceType((key.group >> 16) & 0xff, 0);
}
namespace {

class cEditorCheat {
public:
    virtual void Execute(EA::ArgScript::cArguments_s0058_d430* args);       // +0x00
    virtual const char* GetDescription(int mode);                // +0x04
    virtual void v08();
    virtual int AddRef();                                        // +0x0c
    virtual int Release();                                       // +0x10

    EA::ArgScript::cIParser_s0058_d430* mParser;                            // +0x04
    int mRefCount;                                               // +0x08
    void* mState;                                                // +0x0c
    cAppModeEditorBase_s0058_d430* mEditorApp;                              // +0x10

    __forceinline void ReportFailures(const ValidityBits& mask, const ValidityBits& result);
};

__forceinline void cEditorCheat::ReportFailures(const ValidityBits& mask, const ValidityBits& result) {
    for (uint32_t i = 0; i < 0x1c; ++i) {
        if (mask.test(i) && result.test(i)) {
            uint32_t hintID = GetValidityHintID(i);
            cUIHint* hint = UIHints_s0058_d430()->FindByID(hintID);
            if (hint)
                EA::ArgScript::Output(mParser, "   * %ls\n", hint->mText.GetString());
        }
    }
}

}  // namespace
// ---- items of slice s0058d430 end

// ---- items of slice s005b94b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cSPVector3_s005b_94b0 { float x, y, z; cSPVector3_s005b_94b0() {} cSPVector3_s005b_94b0(float a, float b, float c) : x(a), y(b), z(c) {} };
namespace EA {
template <typename T>
class RefCountVTemplate_s005b_94b0 {
 public:
  RefCountVTemplate_s005b_94b0() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s005b_94b0() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}
namespace eastl {
template <typename T>
class sp_vector_s005b_94b0 {
 public:
  T* mpBegin; T* mpEnd; T* mpCapacity; int mAllocator[2];
  ~sp_vector_s005b_94b0() { if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin); }
  int size() const { return (int)(mpEnd - mpBegin); }
  T& operator[](int i) { return mpBegin[i]; }
};
}
namespace SP {
class cSPEditorBlock_s005b_94b0;
}
namespace SP {
class cSPEditorManipulationObject_s005b_94b0 {
 public:
  __declspec(noinline) cSPEditorManipulationObject_s005b_94b0();
  virtual ~cSPEditorManipulationObject_s005b_94b0() {}
  bool mChangedObject;         // +0x4
  bool mUseDeadZone;           // +0x5
  bool mMovedOutsideDeadZone;  // +0x6
  float mDeadZoneSize;         // +0x8
  float mInitialX;             // +0xc
  float mInitialY;             // +0x10
};
}
namespace SP {
class cSPEditorManipulation56 : public cSPEditorManipulationObject_s005b_94b0, public EA::RefCountVTemplate_s005b_94b0<int> {
 public:
  void* m1c;                                  // +0x1c
  char pad20[0x24 - 0x20];
  cSPEditorBlock_s005b_94b0* mBlock;                     // +0x24
  eastl::sp_vector_s005b_94b0<cSPEditorBlock_s005b_94b0*> mVec;     // +0x28
  cSPVector3_s005b_94b0 mV3c;                            // +0x3c
  cSPVector3_s005b_94b0 mV48;                            // +0x48
  float m54;                                  // +0x54
  float m58;                                  // +0x58
  char pad5c[0x60 - 0x5c];
  cSPVector3_s005b_94b0 mV60;                            // +0x60
  cSPVector3_s005b_94b0 mV6c;                            // +0x6c
  cSPVector3_s005b_94b0 mV78;                            // +0x78
  cSPEditorBlock_s005b_94b0* m84;                        // +0x84
  char pad88[0x89 - 0x88];
  bool m89;                                   // +0x89
  bool m8a;                                   // +0x8a

  cSPEditorManipulation56();
  bool DoOnMouseDown();
  void Update(float dt);
  void SetBlock(cSPEditorBlock_s005b_94b0* b, int a, int c, int d, unsigned char e);
  void Other1();
  void* CopyOut(void* dst);
  void Other2();
};
}
namespace SP {
volatile int g_s56_sink;
}
namespace SP {
__declspec(noinline) cSPEditorManipulationObject_s005b_94b0::cSPEditorManipulationObject_s005b_94b0() { g_s56_sink = 1; }
}
// ---- items of slice s005b94b0 end

// ---- items of slice s00591fa0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3_s0059_1fa0 {
    float x, y, z;
    Vector3_s0059_1fa0() {}
    Vector3_s0059_1fa0(const Vector3_s0059_1fa0& v) : x(v.x), y(v.y), z(v.z) {}
};
struct ResourceKey_s0059_1fa0 {
    uint32_t instanceID, typeID, groupID;
};
struct Flags128 {            // eastl::bitset<128> passed by value (validity masks)
    uint32_t mWord[4];
};
inline Flags128 MakeFlags128(uint32_t mask) {
    Flags128 f;
    uint32_t w = 0;
    f.mWord[0] = w | mask;
    f.mWord[1] = w;
    f.mWord[2] = w;
    f.mWord[3] = w;
    return f;
}
struct BoundingBox_s0059_1fa0 {
    Vector3_s0059_1fa0 mMin, mMax;
};
struct Plane {
    Vector3_s0059_1fa0 n;
    float d;
};
struct Rect {
    float x1, y1, x2, y2;
};
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
extern char gEmptyString_s0059_1fa0[];   // 0x01667bac, shared empty buffer of eastl strings
namespace eastl {
struct string_s0059_1fa0 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    uint32_t mAllocator;
    string_s0059_1fa0() : mpBegin(gEmptyString_s0059_1fa0), mpEnd(gEmptyString_s0059_1fa0), mpCapacity(gEmptyString_s0059_1fa0 + 1) {}
    ~string_s0059_1fa0();                                              // 0x00530670
    int sprintf(const char* fmt, ...);                      // 0x00472fe0
};
}
namespace eastl {
struct wstring_s0059_1fa0 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    wstring_s0059_1fa0()
        : mpBegin((wchar_t*)gEmptyString_s0059_1fa0), mpEnd((wchar_t*)gEmptyString_s0059_1fa0),
          mpCapacity((wchar_t*)gEmptyString_s0059_1fa0 + 1) {}
    ~wstring_s0059_1fa0() { DeallocateSelf(); }
    void DeallocateSelf();                                  // 0x00933960
    const wchar_t* c_str() const { return mpBegin; }
};
}
int WStr_Format(eastl::wstring_s0059_1fa0* out, const wchar_t* fmt, ...);   // 0x0041e050
namespace EA {
template <class T> struct AutoRefCount_s0059_1fa0 {
    T* mpObject;
    AutoRefCount_s0059_1fa0() : mpObject(0) {}
    AutoRefCount_s0059_1fa0(T* p);                                     // 0x0061df40 / 0x00572660 (out of line)
    ~AutoRefCount_s0059_1fa0() { if (mpObject) mpObject->Release(); }
    AutoRefCount_s0059_1fa0& operator=(T* p);                          // 0x00572620 (out of line)
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
using EA::AutoRefCount_s0059_1fa0;
namespace SP {
class cString_s0059_1fa0 {
public:
    uint32_t mData[8];
    cString_s0059_1fa0(uint32_t tableID, int instanceID, const wchar_t* defaultText);   // 0x006b5770
    ~cString_s0059_1fa0();                                                             // 0x006b5240
    const wchar_t* GetText(int count, bool pluralize);                      // 0x006b55c0
};
}
namespace SP {
class cPropertyList_s0059_1fa0;
}
namespace SP {
bool GetPropertyAsKeyInstance(cPropertyList_s0059_1fa0* prop, uint32_t id, uint32_t* out);   // 0x006a12a0
}
namespace SP {
bool GetFloatProperty(cPropertyList_s0059_1fa0* prop, uint32_t id, float* out);              // 0x0040cf10
}
namespace SP {
struct cFlagTable {
    uint32_t pad0[0x38 / 4];
    uint32_t mCount;          // +0x38
    int* mpFlags;             // +0x3c
    bool IsSet(uint32_t id) const;                          // 0x006a25a0
};
}
namespace SP {
extern cFlagTable* gFlagTable;                              // 0x015fd918
}
namespace SP {
class IMessageServer_s0059_1fa0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void PostMSG(uint32_t messageID, void* data, int flags);          // +0x14
    virtual void MessageSend(uint32_t messageID, void* data, int a, int b);   // +0x18
};
}
namespace SP {
IMessageServer_s0059_1fa0* MessageServer_s0059_1fa0();                            // 0x0067dcc0
}
namespace SP {
class cViewer_s0059_1fa0 {
public:
    void GetCameraLocationInfo(Vector3_s0059_1fa0* pos, Vector3_s0059_1fa0* dir, int a, int b);   // 0x007c3d30
    void GetCameraRayOrigin(Vector3_s0059_1fa0* origin, Vector3_s0059_1fa0* dir);                 // 0x007c4900
};
}
namespace SP {
class IApp_s0059_1fa0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual uint32_t GetActiveModeID();                     // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54();
    virtual cViewer_s0059_1fa0* GetViewer();                           // +0x58
};
}
namespace SP {
IApp_s0059_1fa0* App_s0059_1fa0();                                                // 0x0067dd10
}
namespace SP {
class IAppSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void ToggleFullScreenWindowed();                // +0x30
    virtual bool IsFullScreen();                            // +0x34
};
}
namespace SP {
IAppSystem* AppSystem();                                    // 0x0067dd00
}
namespace SP {
class IWindow_s0059_1fa0 {
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
}
namespace SP {
class cSPUIMainWinBase { public: virtual void v00(); };
}
namespace SP {
class cSPUIMainWin_s0059_1fa0 : public cSPUIMainWinBase, public IWindow_s0059_1fa0 {
public:
    uint64_t GetMouseRefs();                                // 0x008130a0
};
}
namespace SP {
class IWindowManager_s0059_1fa0 {
public:
    virtual void v00();
    virtual IWindow_s0059_1fa0* GetMainWindow();                       // +0x04
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
}
namespace SP {
IWindowManager_s0059_1fa0* WindowManager_s0059_1fa0();                            // 0x0067caa0
}
namespace SP {
class cUIHints_s0059_1fa0 {
public:
    void SetEnabled(bool enabled, bool save);               // 0x0067c420
    void ShowHint(uint32_t hintID);                         // 0x0067c830
};
}
namespace SP {
cUIHints_s0059_1fa0* UIHints_s0059_1fa0();                                        // 0x0067cac0
}
namespace SP {
void ToggleDebugDraw(int arg);
}
namespace SP {
class cAssetBrowser {
public:
    uint32_t pad0[0x1c / 4];
    bool mbVisible;                                         // +0x1c
};
}
namespace SP {
cAssetBrowser* AssetBrowser_s0059_1fa0();                              // 0x00401030                              // 0x008098f0 (__cdecl)
}
namespace SP {
class ISaveArea {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24();
    virtual const wchar_t* GetPath();                       // +0x28
};
}
namespace SP {
ISaveArea* GetSaveArea_s0059_1fa0(uint32_t directoryID);               // 0x006b1f90
}
namespace SP {
class Resource_s0059_1fa0 {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
};
}
namespace SP {
class cEditorResource_s0059_1fa0 : public Resource_s0059_1fa0 {
public:
    uint32_t pad4[(0x18 - 4) / 4];
    uint32_t mTypeID;                                       // +0x18
    void GetRequiredValidity(Flags128* out, Flags128 available, bool b);   // 0x004bac30
};
}
namespace SP {
class IResourceManager_s0059_1fa0 {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual bool GetResource(const ResourceKey_s0059_1fa0& key, Resource_s0059_1fa0** out, int a, int b, int c, int d);   // +0x0c
};
}
namespace SP {
IResourceManager_s0059_1fa0* GetManager_s0059_1fa0();                             // 0x0067dcd0
}
namespace SP {
cEditorResource_s0059_1fa0* interface_cast_cEditorResource(AutoRefCount_s0059_1fa0<Resource_s0059_1fa0>* res);   // 0x00421eb0
}
namespace SP {
uint32_t RemapTypeId(uint32_t typeID);                      // 0x00432f10
}
namespace SP {
bool IsValiditySatisfied(Flags128 required, Flags128 available);           // 0x004f3d60
}
namespace SP {
class cSPEditorModel_s0059_1fa0 {
public:
    uint32_t pad0[0xc / 4];
    ResourceKey_s0059_1fa0 mKey;                                       // +0x0c
    const wchar_t* GetFileName();                           // 0x004ae000
    void SetRegionColor(int region, Vector3_s0059_1fa0 color);         // 0x004add30
};
}
namespace SP {
class cSPEditorBlock_s0059_1fa0 {
public:
    virtual void v00(); virtual void v04();
    virtual void Release();                                 // +0x08
    uint32_t pad4[(0x144 - 4) / 4];
    Vector3_s0059_1fa0 mPosition;                                      // +0x144
    BoundingBox_s0059_1fa0* GetBBox(BoundingBox_s0059_1fa0* out, int a, int b, int c);   // 0x0044ae00
};
}
namespace SP {
class cSPEditorSkinManager_s0059_1fa0 {
public:
    void* GetSkin(int which);                               // 0x004c49e0
    bool IsBusy();                                          // 0x004c58b0
    void RepaintModel(cSPEditorModel_s0059_1fa0* model);               // 0x004c5200
};
}
namespace SP {
class cSPEditorPaintTheme_s0059_1fa0 {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
    uint32_t mData[(0x1a0 - 4) / 4];
    cSPEditorPaintTheme_s0059_1fa0();                                  // 0x004b24c0
    void SetSource(uint32_t source);                        // 0x004b26e0
    void ReadFromProp(uint32_t propID);                     // 0x004b2bb0
    void WriteToProp(cSPEditorModel_s0059_1fa0* model, int region);    // 0x004b2f80
    void SetRegionColor(Vector3_s0059_1fa0 color, int region);         // 0x004b3c70
};
}
namespace SP {
class cSPEditorUI_s0059_1fa0 {
public:
    IWindow_s0059_1fa0* FindWindowByID(uint32_t id);                   // 0x005dc310
    void ShowGeneralMessage(const wchar_t* text);           // 0x005dc460
    bool IsPartsPaletteActive();                            // 0x005dc2e0
    bool IsPaintPaletteActive();                            // 0x005dc2f0
    bool IsEditorUIVisible();                               // 0x005dc450
    void HandleFileDrop(ResourceKey_s0059_1fa0 key);                   // 0x005df8f0
    void UpdateUIBasedOnModelSaveability();                 // 0x005dd7a0
    void ShowCreatureNameEdit();                            // 0x005dc560
    void HideCreatureNameEdit();                            // 0x005dc580
    void ModeHelper();                                      // 0x005de9e0
    void CreateNewCreature(uint32_t layoutID, bool fromPaint);   // 0x00635810
};
}
namespace SP {
struct cPaletteCategory_s0059_1fa0 {
    uint32_t pad0[0x74 / 4];
    uint32_t mCategoryID;                                   // +0x74
};
}
namespace SP {
struct cPaletteCategoryUI {
    uint32_t pad0[0x6c / 4];
    cPaletteCategory_s0059_1fa0* mpCategory;                           // +0x6c
};
}
namespace SP {
struct cCategoryInfo {
    uint32_t mPropID;
    uint32_t mData[7];
};
}
namespace SP {
class cSPPaletteUI_s0059_1fa0 {
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
}
namespace SP {
class cDetachedRollover {
public:
    void HideWin();                                         // 0x005cc0e0
    void Show(const wchar_t* text);                         // 0x005cc120
    void SetPositionAndOffset(float x, float y, float offsetX, float offsetY);   // 0x008283a0
};
}
namespace SP {
void WorldToScreen(const Vector3_s0059_1fa0* pos, float* x, float* y);    // 0x004a3760
}
namespace SP {
class cSPPlayMode_s0059_1fa0 {
public:
    uint32_t pad0[0xc / 4];
    cSPEditorUI_s0059_1fa0* mpUI;                                      // +0x0c
    int GetCurrentBabyIndex();                              // 0x00628500
    int GetBabyIndex(uint32_t creatureID);                  // 0x00628720
    void SelectBaby(int index);                             // 0x0062ba10
    bool RunSkinPaintOnEditorModel(int index, const ResourceKey_s0059_1fa0* key);   // 0x0062c7e0
    void ShowPaintDisabled();                               // 0x00628910
};
}
namespace SP {
struct cAnimatedBaby_s0059_1fa0 {
    uint32_t mCreatureID;
    uint32_t mData[11];
};
}
namespace SP {
class cSPEditorAnimatedEventInfo_s0059_1fa0 {
public:
    virtual void v00(); virtual void AddRef();
    virtual void Release();                                 // +0x08
    uint32_t mData[(0x30 - 4) / 4];
    cSPEditorAnimatedEventInfo_s0059_1fa0();                           // 0x0059d960
    void MessageSend(uint32_t messageID, int a, cSPEditorModel_s0059_1fa0* model, uint32_t brainLevel, int b,
                     float delay, int c, uint32_t animID, float speed);   // 0x0059d8b0
};
}
namespace SP {
class cAbility {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual eastl::wstring_s0059_1fa0 GetName(int index);              // +0x20
    uint32_t pad4[(0x28 - 4) / 4];
    uint32_t mAnimationID;                                  // +0x28
};
}
namespace SP {
void* GetVerbTrayCollection(void* object);                  // 0x00572730 (interface cast)
}
namespace SP {
class cEditorLaunchData_s0059_1fa0 {
public:
    virtual void AddRef();
    virtual void Release();
    uint32_t pad4[(0x10 - 4) / 4];
    ResourceKey_s0059_1fa0 mKey;                                       // +0x10
    uint32_t pad1c[(0x64 - 0x1c) / 4];
    bool mbHasBrain;                                        // +0x64
};
}
namespace SP {
class cEditorAnimEvent {
public:
    virtual void AddRef();
    virtual void Release();
};
}
namespace SP {
int GetModelValidityState(const ResourceKey_s0059_1fa0* key);          // 0x00552300
}
namespace SP {
class IEditorLimits {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void AddCost(int a, uint32_t amount);           // +0x20
    virtual void SetBrainLevel(int a, uint32_t level);      // +0x24
    virtual void v28(); virtual void v2c();
    virtual void SetBudget(uint32_t budget);                // +0x30
};
}
namespace SP {
class ICastable {
public:
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* Cast(uint32_t typeID);                    // +0x0c
};
}
namespace SP {
struct XformMsg {
    uint16_t mFlags;
    uint16_t mChangeCount;
    Vector3_s0059_1fa0 mPosition;                                      // +0x04
    float mScale;                                           // +0x10
    float mRotation[9];
    XformMsg();                                             // 0x00434040
    void SetPosition(const Vector3_s0059_1fa0& v) { mFlags |= 4; mChangeCount++; mPosition = v; }
    void SetScale(float s) { mChangeCount++; mScale = s; }
};
}
namespace SP {
class cEffectText {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
    uint32_t pad4[(0xc - 4) / 4];
    eastl::wstring_s0059_1fa0 mText;                                   // +0x0c
    cEffectText();                                          // 0x0057a6d0
};
}
namespace SP {
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
}
namespace SP {
class IEffectsManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateVisualEffect(uint32_t id, int flags, IVisualEffect** out);   // +0x2c
};
}
namespace SP {
IEffectsManager* EffectsManager_s0059_1fa0();                          // 0x0067ddd0
}
namespace SP {
class cEffectsWorld_s0059_1fa0 {
public:
    void SetEffectTransform(uint32_t effectID, int flags, const XformMsg* xform, cSPEditorBlock_s0059_1fa0* block);  // 0x0045ac20
    void StopEffect(uint32_t effectID, int flags);          // 0x0045ae10
};
}
namespace SP {
cEffectsWorld_s0059_1fa0* GetEditorEffectsWorld();                     // 0x00401050
}
namespace SP {
bool IntersectRayPlane(const Vector3_s0059_1fa0* origin, const Vector3_s0059_1fa0* dir, const Plane* plane, float* t);  // 0x0044e640
}
namespace SP {
Vector3_s0059_1fa0* Vector3_Normalize(Vector3_s0059_1fa0* out, const Vector3_s0059_1fa0* v);  // 0x00436ce0
}
namespace SP {
void PlayUISound(uint32_t soundID);                         // 0x004a88d0
}
namespace SP {
void ColorFromRGB(Vector3_s0059_1fa0* out, uint32_t rgb);              // 0x00576ab0
}
namespace SP {
void SplitPath(const wchar_t* path, wchar_t* drive, wchar_t* dir, wchar_t* fname, wchar_t* ext, int flags);  // 0x00930180
}
namespace SP {
void ExportBakedModelToXMF(cSPEditorModel_s0059_1fa0* model, const wchar_t* dir, const ResourceKey_s0059_1fa0* key);  // 0x00466690
}
namespace SP {
void SetMoneyString(double amount, wchar_t* buf, int bufSize, const wchar_t* fmt, const wchar_t* currency); // 0x008822e0
}
namespace SP {
bool KeysEqual(const ResourceKey_s0059_1fa0* a, const ResourceKey_s0059_1fa0* b);  // 0x004eb930
}
namespace SP {
void UpdateModelValidity(uint32_t value, Flags128* validity);   // 0x004edf40
}
namespace SP {
class cBakeManager_s0059_1fa0 { public: void Invalidate(uint32_t value); };   // 0x005d60c0
}
namespace SP {
extern cBakeManager_s0059_1fa0* gBakeManager;                          // 0x015eebec
}
namespace SP {
extern Flags128 gAllValidity;                               // 0x015dac10
}
namespace SP {
extern Vector3_s0059_1fa0 gRolloverDefaultPos;                         // 0x015e4f18
}
namespace SP {
class cConfigMessage {
public:
    void* GetConfig();                                      // 0x008d3ac0
    uint32_t GetConfigID(int index);                        // 0x00688ed0
};
}
namespace SP {
class cIAppMode_s0059_1fa0 { public: virtual void v00(); };
}
namespace SP {
class cILayer_s0059_1fa0 { public: virtual void v00(); };
}
namespace SP {
class cIHintProcessor { public: virtual void v00(); };
}
namespace SP {
class cISPEditorNameProvider_s0059_1fa0 { public: virtual void v00(); };
}
namespace EA {
namespace Messaging {
class IHandlerRC_s0059_1fa0 {
public:
    virtual bool HandleMessage(uint32_t messageID, void* pMessage) = 0;
};
}
}
namespace EA {
template <class T> class RefCountVTemplate_s0059_1fa0 {
public:
    virtual void v00();
    T mRefCount;
};
}
namespace SP {
struct cEditorModelMessage {
    cISPEditorNameProvider_s0059_1fa0* mpSender;
    uint32_t pad4;
    uint32_t mValue;
    uint32_t padc;
    uint32_t mFlags;
};
}
namespace SP {
class cAppModeEditorBase_s0059_1fa0 : public cIAppMode_s0059_1fa0, public cILayer_s0059_1fa0, public cIHintProcessor,
                           public cISPEditorNameProvider_s0059_1fa0, public EA::Messaging::IHandlerRC_s0059_1fa0,
                           public EA::RefCountVTemplate_s0059_1fa0<int> {
public:
    uint32_t pad1c[(0x24 - 0x1c) / 4];
    cPropertyList_s0059_1fa0* mCurrentConfigProperties;                // +0x24
    uint32_t pad28[(0x48 - 0x28) / 4];
    Flags128 mModelValidity;                                // +0x48
    uint32_t pad58[(0x78 - 0x58) / 4];
    cSPEditorUI_s0059_1fa0* mUI;                                       // +0x78
    cSPPlayMode_s0059_1fa0* mPlayMode;                                 // +0x7c
    uint32_t pad80[(0x98 - 0x80) / 4];
    cSPEditorModel_s0059_1fa0* mEditorModel;                           // +0x98
    uint32_t pad9c[(0xcc - 0x9c) / 4];
    cSPEditorBlock_s0059_1fa0* mRolloverBlock;                         // +0xcc
    uint32_t padd0;
    cSPEditorBlock_s0059_1fa0* mSelectedBlock;                         // +0xd4
    uint32_t padd8;
    AutoRefCount_s0059_1fa0<cSPEditorBlock_s0059_1fa0> mToBeSelectedBlock;        // +0xdc
    uint32_t pade0[(0x150 - 0xe0) / 4];
    cSPEditorSkinManager_s0059_1fa0* mSkinManager;                     // +0x150
    cSPEditorSkinManager_s0059_1fa0* mSaveSkinManager;                 // +0x154
    uint32_t pad158[(0x1a0 - 0x158) / 4];
    int mTransitionAnimation;                               // +0x1a0
    uint32_t pad1a4;
    int mTransitionState;                                   // +0x1a8
    uint32_t pad1ac[(0x1cc - 0x1ac) / 4];
    AutoRefCount_s0059_1fa0<cEditorLaunchData_s0059_1fa0> mLaunchData;            // +0x1cc
    ResourceKey_s0059_1fa0 mParentModelKey;                            // +0x1d0
    uint32_t pad1dc[(0x20c - 0x1dc) / 4];
    wchar_t mCurrencyChar;                                  // +0x20c
    uint16_t pad20e;
    uint32_t pad210[(0x2a0 - 0x210) / 4];
    cSPEditorPaintTheme_s0059_1fa0* mCurrentPaintTheme;                // +0x2a0
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
    cAnimatedBaby_s0059_1fa0* mAnimatedBabiesBegin;                    // +0x36c
    cAnimatedBaby_s0059_1fa0* mAnimatedBabiesEnd;                      // +0x370
    uint32_t pad374[(0x380 - 0x374) / 4];
    AutoRefCount_s0059_1fa0<cEditorAnimEvent> mpAnimEvent;             // +0x380
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
    cSPPaletteUI_s0059_1fa0* mpPartsPaletteUI;                         // +0x3bc
    uint32_t pad3c0;
    cSPPaletteUI_s0059_1fa0* mpPaintPaletteUI;                         // +0x3c4
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
    void SetCurrentConfig(uint32_t config, ResourceKey_s0059_1fa0 key);   // 0x00579720
    void SwitchConfigFromMessage(uint32_t configID);        // 0x00589ce0
    void EnterPaintMode(bool b);                            // 0x005744b0
    void SetRolloverBlock(cSPEditorBlock_s0059_1fa0* block, int region);   // 0x00573c00
    void SetMode(int mode, bool b);                         // 0x00587270
    void LoadModel(const ResourceKey_s0059_1fa0* key, Flags128 validity, bool b);   // 0x0058cee0
    bool IsPaintDisabled();                                 // 0x00573950
    Flags128 GetModelValidity();                            // 0x00572160
    void SetValidityFlags(Flags128 set, Flags128 mask);     // 0x005721b0
    bool IsResourceOfOtherEditor(cEditorResource_s0059_1fa0* res);     // 0x00573070
    void InitBrain(uint32_t level);                         // 0x005722f0
    void SetupBrainFromLaunchData();                        // 0x0057bfb0
    void InitializeUndoList();                              // 0x00586690
    void SetSelectedBlock(cSPEditorBlock_s0059_1fa0* block, bool b);   // 0x0057e790
    void AddUndoState(bool a, bool b);                      // 0x00586410
    void UpdateNameEditFromModel();                         // 0x00575120
    bool HandleAnimEvent(uint32_t id);                      // 0x00574460
    void PlayAnimEvent(cEditorAnimEvent* ev);               // 0x00585330
    bool HandlePaletteItemTriggerMessage(void* item, uint32_t id);   // 0x00591690
};
}
namespace SP {
struct MsgBoolOut { uint32_t pad0[2]; bool* mpResult; };
}
namespace SP {
struct MsgConfig { uint32_t pad0[2]; uint32_t mConfigID; };
}
namespace SP {
struct MsgReplaceRollover { uint32_t pad0[2]; cSPEditorBlock_s0059_1fa0* mpBlock; uint32_t padc; float mCost; };
}
namespace SP {
struct MsgFileDrop { ResourceKey_s0059_1fa0** mppKey; };
}
namespace SP {
struct MsgAbility { cAbility* mpAbility; uint32_t pad4; void* mpSource; };
}
namespace SP {
struct MsgCategory { uint32_t pad0[2]; uint32_t mCategoryID; };
}
namespace SP {
struct MsgInt8 { uint32_t pad0[2]; uint32_t mValue; };
}
namespace SP {
struct MsgNameEdit { bool mbShow; ResourceKey_s0059_1fa0 mKey; };
}
namespace SP {
struct MsgBudget { uint32_t mBudget; };
}
namespace SP {
struct MsgBlock { cSPEditorBlock_s0059_1fa0* mpBlock; };
}
namespace SP {
struct MsgModel { cSPEditorModel_s0059_1fa0* mpModel; uint32_t pad4; uint32_t mValue; };
}
namespace SP {
struct MsgBrain { uint32_t pad0[2]; uint32_t mBrainLevel; uint32_t padc; uint32_t mInitLevel; };
}
namespace SP {
struct MsgPaint { uint32_t pad0[2]; uint32_t mColor; uint32_t padc[3]; int mRegion; uint32_t pad1c; int mbTheme; };
}
namespace SP {
struct MsgPaletteItem { uint32_t pad0[4]; uint32_t mID; uint32_t pad14[3]; ICastable* mpItem; };
}
namespace SP {
struct MsgAnimEvent { uint32_t pad0[3]; uint32_t mID; uint32_t pad10; cSPEditorModel_s0059_1fa0* mpModel; };
}
namespace SP {
struct MsgMoney { uint32_t mAmount; uint32_t pad4; float x; uint32_t padc; float y; uint32_t pad14; float z; };
}
namespace SP {
struct MsgKeyReplace { ResourceKey_s0059_1fa0 mKey; bool mbReplace; uint8_t padd[3]; ResourceKey_s0059_1fa0 mNewKey; };
}
// ---- items of slice s00591fa0 end

// ---- items of slice s00575270 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct VObj {                       // object at cAppModeEditorBase+0x8c
    virtual void slot0(int);
    virtual int  slot1();
};
void*           __cdecl FXManager();
struct IConfigManager {             // ConfigManager() 0x67dd30
    PV8 PV4
    virtual int Query(uint32_t id);               // +0x30
};
IConfigManager* __cdecl ConfigManager();
struct cEffectsWorld {              // object at cAppModeEditorBase+0x90
    char pad0[0x58];
    int  mMode;                                   // +0x58 (current tool/mode id)
};
struct cSPPlayModeUI_s0057_5270 {              // object at *[self+0x74]+0xc
    bool IsUIGroupEnabled(uint32_t group);        // 0x635890
};
struct cSPPlayMode_s0057_5270 {                // object at cAppModeEditorBase+0x74
    char pad0[0xc];
    cSPPlayModeUI_s0057_5270* mpUI;                          // +0x0c
};
struct cSPPaletteUI_s0057_5270 {               // object at cAppModeEditorBase+0x3bc
    bool IsPaintByNumber();                       // 0x5ca920
};
struct cDevFlags {                  // object at cAppModeEditorBase+0x4d0: one bool per debug/editor option
    bool f[0x22];
};
struct IEditorEntries {             // object at cAppModeEditorBase+0x42c
    PV
    virtual int Query(int);                       // +0x04
};
struct cPartsPalette_s0057_5270 {
    void Reset(int, int);                         // 0x43cfc0
    void SomeA();                                 // 0x43cad0
    void SomeB();                                 // 0x43c710
};
namespace SP {
class cAppModeEditorBase_s0057_5270 {
public:
    char pad[0x458];
    // --- observed offsets ---
    void  SetEconomyValue(int, int);              // 0x575270 (renamed)
    void  ResetEconomy();                         // 0x5754c0
    void  DoSomePaletteThing();                   // 0x575790
    void  StopSomething();                        // 0x5757b0
    bool  TestCondition(uint32_t);                // 0x575810
    void  GetSomething1(int);                     // 0x575e20
    int   GetSomething2();                        // 0x575e50
    bool  SomeBool(char);                         // 0x575eb0
    void  SetupCameraUI();                        // 0x575f20
    void  ToggleCameraMode();                     // 0x575f70
    void  UpdateSpineVertebra(float);             // 0x575520
};
}
using SP::cAppModeEditorBase_s0057_5270;

template <typename T> static inline T Value(void* self, uint32_t off) {
    return *(T*)((char*)self + off);
}
static inline char& ByteRef(void* self, uint32_t off) {
    return *(char*)((char*)self + off);
}
void cAppModeEditorBase_s0057_5270::SetEconomyValue(int, int) {}
void cAppModeEditorBase_s0057_5270::ResetEconomy() {}
void cAppModeEditorBase_s0057_5270::ToggleCameraMode() {}
void cAppModeEditorBase_s0057_5270::UpdateSpineVertebra(float) {}
// ---- items of slice s00575270 end

// ---- items of slice s0057f420 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cUnkF420 {
    void FUN_0057f420(void* args);
};
// ---- items of slice s0057f420 end

// ---- items of slice s0058cee0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
class cAppModeEditorBase_s0058_cee0 {
public:
    char pad0[0x600];
    int LoadModel(int a, int b, int c, int d, int e, int f);   // 0x0058cee0
    void NewModel(char a);                                     // 0x0058d1c0
};
}
// ---- items of slice s0058cee0 end

// @ 0x00572070
void __cdecl SetSoundSymbol(uint32_t objectId, uint32_t symbolId, const char* value)
{
    EA::Audio::SystemAT* sys = EA::Audio::GetSystemAT();
    if (sys && value) {
        sys->BeginMessage(0x347537a);
        sys->SetInt(0x3475385, objectId);
        sys->SetInt(0x34753a7, symbolId);
        sys->SetString(0x34753b0, value, strlen(value) + 1);
        sys->SendMessage();
    }
}

// @ 0x005720f0
void __cdecl SetCullBackfaces(int enable)
{
    g_renderStateDirty |= 0x10000;
    g_cullMode = enable ? 4 : 8;
}

// @ 0x00572110
uint32_t __cdecl LookupByHash(uint32_t hash)
{
    switch (hash) {
    case 0x3d97a8e4: return g_value74;
    case 0x2399be55: return g_value7c;
    case 0x24682294: return g_value80;
    case 0x476a98c7: return g_value84;
    case 0x438f6347: return g_value88;
    }
    return g_value78;
}

// @ 0x00572160
Vec4 ColorSource::GetDefaultColor() const
{
    return g_defaultColor;
}

// @ 0x00572190
Vec4 ColorSource::GetColor() const
{
    return mColor;
}

// @ 0x005721b0
void __stdcall HandleRects(Rect16 a, Rect16 b)
{
    int r = ClassifyRects(a, b);
    if (r != 0x1c)
        UIManager()->Show(RectResultToId(r));
}

// @ 0x00572220
void __stdcall UpdateAllItems(cItemList* list)
{
    if (list) {
        int i = 0;
        int n = list->GetCount();
        for (; i < n; ++i)
            list->GetAt(i)->Update();
    }
}

// @ 0x005722f0
namespace SP {
void cAppModeEditorBase_s0057_18f0::InitBrain(uint32_t region)
{
    mCurrentBlockRegion = region;
    if (mbPlaySounds)
        EditorUtils::PlayEditorSound(0x1d6253c0, 0xac23893f, (float)region, 0);
}
}  // namespace SP

// @ 0x00572840
bool __cdecl WriteUint32Value(ISerializer* s, const uint32_t* v)
{
    WriteUint32(s->GetHolder()->GetStream(), *v);
    return true;
}

// @ 0x00572880
bool __cdecl WriteUint32Array6(ISerializer* s, const uint32_t* v)
{
    const int count = 6;
    WriteUint32(s->GetHolder()->GetStream(), count);
    for (int i = 0; i < count; ++i) {
        WriteUint32(s->GetHolder()->GetStream(), *v);
        ++v;
    }
    return true;
}

// @ 0x005728f0
const wchar_t* __cdecl FindLastOf(const wchar_t* pEnd, const wchar_t* pBegin, const wchar_t* p2Begin, const wchar_t* p2End)
{
    for (; pEnd != pBegin; --pEnd) {
        for (const wchar_t* p = p2Begin; p != p2End; ++p) {
            if (pEnd[-1] == *p)
                return pEnd;
        }
    }
    return pBegin;
}

// @ 0x00572930
int __cdecl CompareI16(const wchar_t* a, const wchar_t* b, uint32_t n)
{
    for (; n > 0; ++a, ++b, --n) {
        const wchar_t c1 = ToLower16(*a);
        const wchar_t c2 = ToLower16(*b);
        if (c1 != c2)
            return (c1 < c2) ? -1 : 1;
    }
    return 0;
}

// @ 0x005729b0
VecPair* __cdecl CopyVecPairs(VecPair* first, VecPair* last, VecPair* dest)
{
    for (; first != last; ++dest, ++first)
        *dest = *first;
    return dest;
}

// @ 0x00572a10
float __cdecl RandomRange(float a, float b)
{
    return RandomRangeInline(a, b);
}

// @ 0x00572a60
float __cdecl RandomSigned(float x)
{
    return RandomRangeInline(-x, x);
}

// @ 0x00572ab0
namespace EA { namespace Messaging {
void HandlerRegistration::Unregister()
{
    if (mpServer) {
        IServer* const server = mpServer;
        mpServer = 0;
        RemoveHandler(server, mpHandler, mpIds, mnCount, mnPriority);
    }
}
}}  // namespace EA::Messaging

// @ 0x00572ae0
namespace Simulator {
cThemeMusicManager::cThemeMusicManager()
: mField08(0), mField0C(0), mField10(0), mbField14(false), mbField15(false),
      mField18(0), mField1C(0), mField20(0), mField24(0), mField28(0)
{
}
}  // namespace Simulator

// @ 0x00572b10
int ComplexityBlock::GetEntryCount()
{
    return mEntries.mpEnd - mEntries.mpBegin;
}

// @ 0x00572b30
float __cdecl GetComplexityFraction(const BlockPtrVector& blocks)
{
    int bake = 0, cost = 0;
    for (int i = 0; i < blocks.size(); ++i) {
        const EntryVector& entries = blocks[i]->mEntries;
        for (int j = 0; j < entries.size(); ++j) {
            bake += blocks[i]->mEntries[j].mBakeCost;
            cost += blocks[i]->mEntries[j].mCost;
        }
    }
    const float fBake = (float)bake * 0.001f;
    const float fCost = (float)cost * 0.0002f;
    return max_alt(fBake, fCost);
}

// @ 0x00572c50
uint32_t __cdecl IDFromName16(const wchar_t* name)
{
    return EA::Hash::FNV1_String16(name, 0x811c9dc5, 1);
}

// @ 0x00572c90
int BlockPtrVector::GetSize()
{
    return mpEnd - mpBegin;
}

// @ 0x00572cd0
const char* cEditorLimitsCheat::GetDescription(int mode) const
{
    return mode ? 0 : "[on | off], toggles, disables (on) or re-enables (off) editor complexity limits. Creations that break the limits will not be pollinated!";
}

// @ 0x00572cf0
float __cdecl EditorGroundSampler(cEditorGround* editor, uint32_t unused, const Vector2& pos, Vector3* pNormal)
{
    float height = 0.0f;
    Vector3 normal = kDefaultNormal;
    if (editor) {
        ICollider* collider = editor->mpCollider84;
        if (collider) {
            Vector3 hit;
            CollisionFilter filter;
            Vector3 start(pos.x, pos.y, 500.0f);
            Vector3 end(pos.x, pos.y, -10.0f);
            filter.mMode = 4;
            if (editor->mEditorMode == 2) {
                filter.SetType(SP::ModelManager()->GetTypeIndex(0x26f3933, 0));
                float offset = editor->mpPlayMode->GetHeightOffset();
                if (collider->Raycast(&start, &end, 0, &hit, &normal, &filter, 0, 0))
                    height = hit.z + offset;
            } else {
                if (pNormal)
                    *pNormal = kDefaultNormal;
                SP::cCreatureStructure* cs = editor->mpCreatureMgr->GetCreatureStructure(editor->mCreatureId);
                if (cs) {
                    Point3 v = cs->mOffset;
                    return v.z;
                }
                return 0.0f;
            }
        }
        const float inv = 1.0f / InlineSqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
        normal.x *= inv;
        normal.y *= inv;
        normal.z *= inv;
        if (pNormal)
            *pNormal = normal;
    }
    return height;
}

// @ 0x00572f00
float __cdecl EditorGroundHeight(cEditorGround* editor, const Vector2& pos)
{
    float height = 0.0f;
    Vector3 normal = kDefaultNormal;
    if (editor) {
        ICollider* collider = editor->mpCollider8C;
        if (collider) {
            CollisionFilter filter;
            Vector3 start(pos.x, pos.y, 500.0f);
            Vector3 end(pos.x, pos.y, -10.0f);
            float offset = 0.0f;
            filter.mMode = 4;
            if (editor->mEditorMode == 2) {
                filter.SetType(SP::ModelManager()->GetTypeIndex(0x223e8e0, 0));
                offset = editor->mpPlayMode->GetHeightOffset();
            }
            Vector3 hit;
            if (collider->Raycast(&start, &end, 0, &hit, &normal, &filter, 0, 0))
                height = hit.z + offset;
        }
    }
    return height;
}

// @ 0x00573050
bool cEditor::IsLimitAllowed()
{
    if (mpLimits)
        return mpLimits->mbAllow;
    return true;
}

// @ 0x00573070
bool cEditor::CanUseModel(const ResourceKeyRec* rec)
{
    const uint32_t modelType = rec->mModelType;
    bool result = false;
    const uint32_t config = RemapTypeId(modelType);
    if (config != (uint32_t)GetEditorConfig()) {
        result = true;
        switch (GetEditorConfig()) {
        case (int)0xa56567f7:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04 || modelType == 0xccc35c46 ||
                modelType == 0x65672ade || modelType == 0x4178b8e8)
                result = false;
            break;
        case (int)0x9adf00a9:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04 || modelType == 0xccc35c46)
                result = false;
            break;
        case (int)0xbc1041e6:
            if (modelType == 0x7d433fad || modelType == 0xf670aa43 || modelType == 0x9ad7d4aa ||
                modelType == 0xbc1041e6)
                result = false;
            break;
        case (int)0xc15695da:
            if (modelType == 0x8f963dcb || modelType == 0x2a5147a9 || modelType == 0x1f2a25b6 ||
                modelType == 0xc15695da)
                result = false;
            break;
        case (int)0xe46c381e:
        case (int)0xfd4902bd:
            if (modelType == 0x9ea3031a && HasProperty(rec, 0xe46c381e, 0))
                result = false;
            break;
        case 0x2090a11b:
            if (modelType == 0x441cd3e6 || modelType == 0x1a4e0708 || modelType == 0x449c040f ||
                modelType == 0x2090a11b)
                result = false;
            break;
        case 0x156276d1:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04)
                result = false;
            break;
        case 0x37e82da1:
            if (modelType == 0x9ea3031a || modelType == 0x372e2c04 || modelType == 0xccc35c46 ||
                modelType == 0x65672ade)
                result = false;
            break;
        }
    }
    bool bypass = false;
    if (mpLimits && mpLimits->mbCheckLimits && sAppProperties->GetBool(0x677d3ea) && IsKeyDown(0x10, 0x3ff)) {
        const uint32_t group = rec->mGroupC;
        const uint32_t current = mGroup;
        bool same = (group == current);
        if (current == 0x476a98c7 && group == 0x24682294)
            same = true;
        else if (current == 0x24682294 && group == 0x476a98c7)
            same = true;
        if (!mbLimitsDisabled && same)
            bypass = true;
    }
    if (!bypass && result)
        return true;
    if (IsSpecialKey(&mpModel->mKey) || IsSpecialKey(&rec->mKey8))
        return true;
    return false;
}

// @ 0x005732f0
void cEditor::ReleaseRefs()
{
    if (mpRef308) {
        IRelease* p = mpRef308;
        mpRef308 = 0;
        p->Release();
    }
    if (mpRef30C) {
        IRelease* p = mpRef30C;
        mpRef30C = 0;
        p->Release();
    }
}

// @ 0x00573330
void cEditor::HideCreature()
{
    if (mpModel && !IsModelLocked(mpModel) && mpCreatureMgr) {
        if (mpCreatureMgr->GetCreature(mCreatureId)) {
            SP::cSPEditorAnimatedCreatureManager_s0057_2580* mgr = mpCreatureMgr;
            mgr->GetCreature(mCreatureId)->SetVisible(0);
        }
    }
}

// @ 0x00573390
void cEditor::ShowCreature()
{
    if (mpCreatureMgr) {
        if (mpCreatureMgr->GetCreature(mCreatureId)) {
            SP::cSPEditorAnimatedCreatureManager_s0057_2580* mgr = mpCreatureMgr;
            mgr->GetCreature(mCreatureId)->SetVisible(1);
        }
    }
}

// @ 0x005733d0
void cEditor::UpdateCursor()
{
    const uint32_t current = CursorManager()->GetCursor();
    if (current == 0x1001 || (current > 0x1011 && current <= 0x101a))
        return;
    uint32_t cursor;
    if (!mpPalette->IsActive())
        cursor = 0x1003;
    else if (SP::WindowManager()->IsModal())
        cursor = 0x1002;
    else if (mStateFlags & 0x10)
        cursor = 0x1010;
    else if (mStateFlags & 1)
        cursor = 0x100f;
    else if (mpUndo && mpUndo->HasPending())
        cursor = 0x1024;
    else
        cursor = 0x1002;
    if (cursor != current)
        CursorManager()->SetCursor(cursor);
    mbFading = false;
}

// @ 0x00573480
void cEditor::SetSymmetryMode(int mode)
{
    if (mpSymmetry && mpSymmetry->IsReady()) {
        if (mpPalette && mode != mSymmetryMode)
            mSymmetryMode = mode;
        switch (mode) {
        case 0:
            UIManager_s0057_2580()->Show(0x2671afcc);
            mStateFlags += 0x60;
            break;
        case 1:
            UIManager_s0057_2580()->Show(0x7f4de3ba);
            mStateFlags = (mStateFlags & ~0x40) + 0x20;
            break;
        case 2:
            UIManager_s0057_2580()->Show(0x33c35a06);
            mStateFlags = (mStateFlags & ~0x20) + 0x40;
            break;
        }
    }
}

// @ 0x00573520
namespace SP {
void cAppModeEditorBase_s0057_3520::ShowBlockAbilities(cEditorBlock* block)
{
    if (block && mpOwner && !block->mFlags.Get(7) && !block->mFlags.Get(11) && !block->mFlags.Get(1) &&
        block->CanShowAbilities()) {
        cSPEditorVehicleAbilities::Key key;
        mActiveBlock.mpObject->GetKey(&key, -1, 0);
        mpOwner->SetKey(&key);
        cSPUIPropertyLayout* layout = PropertyLayoutMgr()->GetLayout();
        if (layout) {
            IObject* abilities = new("Editor", 0, 0, 0, 0) cSPEditorVehicleAbilities(key, mpModel->mType, 0x14880158, 0, 1);
            if (abilities)
                abilities->AddRef();
            layout->Setup(&key, abilities, mpOwner, mLayoutFlags, 0, 1);
            layout->SetMode(2);
            RectF area = WindowManager_s0057_3520()->GetMainWindow()->GetArea();
            cEditorBlock* active = mActiveBlock.mpObject;
            BoundingBox tmp;
            const BoundingBox& bbox = active->GetBBox(&tmp, 0, 0, 0);
            Vector3_s0057_3520 center = (bbox.mMax + bbox.mMin) * 0.5f;
            float screenX, screenY;
            ProjectToScreen(center, screenX, screenY);
            layout->SetPositionAndOffset(screenX, screenY, (area.mRight - area.mLeft) * 0.025f, (area.mBottom - area.mTop) * 0.0f);
            if (abilities)
                abilities->Release();
        }
    } else {
        cSPUIPropertyLayout* layout = PropertyLayoutMgr()->GetLayout();
        if (layout)
            layout->Hide();
    }
}
}  // namespace SP

// @ 0x00573780
namespace SP {
void cAppModeEditorBase_s0057_3520::SetModelLocked(bool locked)
{
    if (locked != mbModelLocked) {
        mbModelLocked = locked;
        if (mpModel)
            mpModel->SetLocked(locked);
        if (!mpSkinManager && mpPartsPalette) {
            mpPartsPalette->Refresh(0, 1);
            mpPartsPalette->Update();
        }
    }
}
}  // namespace SP

// @ 0x005737d0
namespace SP {
bool cAppModeEditorBase_s0057_3520::OnMouseMove(float x, float y, uint32_t state)
{
    if (mbInputLocked)
        return false;
    mMouseX = x;
    mMouseY = y;
    mMouseState = state;
    mbMouseMoved = true;
    if (mbSkipMouseMove) {
        mbSkipMouseMove = false;
        return true;
    }
    if (mEditorMode == 2 && (state & 0x38)) {
        mpPlayMode->OnMouseMove(x, y, state);
        return false;
    }
    if (mMouseButton == 0x3e9 || mMouseButton == 0x3ea || (mMouseButton == 0x3e8 && !mpSkinManager)) {
        if (fabs(x - mMouseDownX) > 3.0f || fabs(y - mMouseDownY) > 3.0f)
            mbClickCandidate = false;
        return false;
    }
    switch (mEditorMode) {
    case 0:
        if (mpSkinManager) {
            bool result = mpSkinManager->OnMouseMove(x, y, state);
            mBlockRefD0 = mpSkinManager->GetBlock();
            mpModel->SetDirty(1);
            return result;
        }
        break;
    case 2:
        mpPlayMode->OnMouseMove(x, y, state);
        return true;
    }
    return true;
}
}  // namespace SP

// @ 0x00573950
namespace SP {
bool cAppModeEditorBase_s0057_3520::IsOverLimit()
{
    if (mpLimits)
        return mpLimits->mbOverLimit;
    return false;
}
}  // namespace SP

// @ 0x00573970
namespace SP {
void cAppModeEditorBase_s0057_3520::UpdateHint()
{
    if (mbCursorSet && mHintTimer == 0.0f) {
        cSPEditorAnimatedEventInfo_s0057_3520* msg = new("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s0057_3520();
        if (msg)
            msg->AddRef();
        msg->MessagePost(0x6581b78e, 0, 0, 0, 0, 0.0f, 0, -1, 1.0f);
        mHintTimer = 250.0f;
        if (msg)
            msg->Release();
    }
}
}  // namespace SP

// @ 0x00573a10
namespace SP {
cEditorBlock* cAppModeEditorBase_s0057_3520::GetSelectableBlock()
{
    cEditorBlock* b = mActiveBlock.mpObject;
    if (!b) {
        if (!mpRolloverHandle)
            return 0;
        cEditorBlock* r = mpRolloverHandle->GetBlock();
        if (!r || r->mpHandle != mpRolloverHandle)
            return 0;
        b = r;
    }
    return b->mFlags.Get(7) ? 0 : b;
}
}  // namespace SP

// @ 0x00573a60
namespace SP {
bool cAppModeEditorBase_s0057_3520::IsMousedOverModel(float x, float y)
{
    Vector3_s0057_3520 nearPt, farPt;
    App()->GetViewer()->ScreenToWorld(x, y, &nearPt, &farPt);
    cUndo* undo = mpUndo;
    if (undo) {
        Vector3_s0057_3520 dir = farPt - nearPt;
        const float len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z + 1e-8f);
        const float inv = 1.0f / len;
        Vector3_s0057_3520 hitPos, hitNormal;
        if (undo->Raycast(1, nearPt, inv * dir, &hitPos, &hitNormal, 0, 1))
            return true;
    }
    {
        CollisionFilter filter;
        filter.mMode = 4;
        filter.mbFlag = true;
        filter.SetType(ModelManager()->GetTypeIndex(0x9138fd8d, 0));
        if (mpCollider->Raycast(&nearPt, &farPt, 0, 0, 0, &filter, 0, 0))
            return true;
        return false;
    }
}
}  // namespace SP

// @ 0x00573c00
namespace SP {
void cAppModeEditorBase_s0057_3520::SetActiveBlock(cEditorBlock* block, int handle)
{
    cEditorBlock* const old = mActiveBlock.mpObject;
    if (block != old || (block && handle != mActiveHandle)) {
        mActiveHandle = handle;
        mLastHandle = handle;
        if (old != block) {
            if (old) {
                const bool differs = !IsSameAssembly(block, old);
                if (mpRolloverHandle && differs)
                    IsSameAssembly(mpRolloverHandle->GetBlock(), mActiveBlock.mpObject);
                mActiveBlock.mpObject->SetSelected(0);
            }
            if (!block) {
                if (mActiveBlock.mpObject->mFlags.Get(3))
                    mActiveBlock.mpObject->OnDeselect();
                if (mActiveBlock.mpObject) {
                    cEditorBlock* p = mActiveBlock.mpObject;
                    mActiveBlock.mpObject = 0;
                    p->Release();
                }
                if (mpHint)
                    mpHint->Show();
            } else if (!block->mFlags.Get(1)) {
                mActiveBlock = block;
                if (!IsRootBlock(block) && mpHint)
                    mpHint->Show();
                bool activate;
                if (mEditorMode == 1)
                    activate = mpSymmetry && mpSymmetry->IsReady();
                else
                    activate = !mActiveBlock.mpObject->mFlags.Get(11) || !mActiveBlock.mpObject->mFlags.Get(10);
                if (activate) {
                    PlayEditorEvent(0xbb58117e);
                    mActiveBlock.mpObject->SetSelected(1);
                }
            }
            if (mEditorMode == 0 && (mStateFlags & 0x100))
                ShowBlockAbilities(mActiveBlock.mpObject);
        }
    }
    mbHasActiveBlock = mActiveBlock.mpObject != 0;
}
}  // namespace SP

// @ 0x00573d70
namespace SP {
void cAppModeEditorBase_s0057_3520::SetRolloverHandle(cSPEditorHandle_s0057_3520* handle, int unused)
{
    if (!handle && !mbHandleSnap)
        mbHandleSnap = true;
    if (handle == mpRolloverHandle && (!mpRolloverHandle || !mpRolloverHandle->IsLocked()))
        return;
    if (mpPendingHandle && mpPendingHandle != handle) {
        if (!mbHandleSnap)
            mbHandleSnap = true;
        mpPendingHandle = 0;
    }
    if (mpRolloverHandle == handle)
        return;
    if (handle) {
        cEditorBlock* b = handle->GetBlock();
        if (b && b->mFlags.Get(11))
            mbHandleSnap = false;
    }
    if (mpRolloverHandle) {
        mpRolloverHandle->SetState(3, 1);
        if (mbDeformActive) {
            if (mpRolloverHandle) {
                cSPEditorHandle_s0057_3520* deform = mpRolloverHandle->Cast(0x50a993c);
                if (deform && deform->GetBlock()) {
                    cEditorBlock* b = deform->GetBlock();
                    b->SetHandleState(b->GetHandleIndex(deform), 1);
                }
            }
            mbDeformActive = false;
        }
    }
    cSPEditorHandle_s0057_3520* const old = mpRolloverHandle;
    if (handle != old) {
        if (handle)
            handle->AddRef();
        mpRolloverHandle = handle;
        if (old)
            old->Release();
    }
    if (mpRolloverHandle) {
        cSPUISpace::KillSetiEffects(0xd2cfe2ad, this);
        SetActiveBlock(0, -1);
        mpRolloverHandle->SetState(0, 1);
        if (mpRolloverHandle->GetType() == 0x50a993c && mbHandleSnap) {
            cSPEditorHandleDeform_s0057_3520* deform = interface_cast_deform((AutoRefCount<cSPEditorHandle_s0057_3520>*)&mpRolloverHandle);
            cEditorBlock* deformBlock = deform->GetBlock();
            cSPEditorHandle_s0057_3520* rollover = mpRolloverHandle;
            rollover->GetBlock()->SetActiveHandle(deformBlock->GetHandleIndex(deform));
            mbDeformActive = true;
        }
    } else {
        PostSoundMessage(this, 0);
    }
}
}  // namespace SP

// @ 0x00573f20
namespace SP {
void cAppModeEditorBase_s0057_3520::SetAsset(uint32_t key)
{
    if (key) {
        IRefCount* asset = (IRefCount*)AssetManager()->Find(key, 1);
        if (asset) {
            asset->AddRef();
            mbHasAsset = 1;
            asset->Release();
            return;
        }
    }
    mbHasAsset = 0;
}
}  // namespace SP

// @ 0x00573f70
namespace SP {
void cAppModeEditorBase_s0057_3520::SetPaletteVisible(bool visible)
{
    if (mpPalette->IsActive() != visible) {
        mpPalette->SetVisible(visible);
        mpPalette->Refresh(visible, 1);
    }
    UIManager_s0057_3520()->SetMode(visible, 1);
}
}  // namespace SP

// @ 0x00573fb0
namespace SP {
void cAppModeEditorBase_s0057_3520::OnEnter()
{
    if (GameModeCheck()->IsActive())
        return;
    mRegistration.Register(MessageServer(), this, kEditorMessageIds, 1);
    PostModelChanged(mpModel);
    SetPaletteVisible(false);
    mStopwatch.Restart();
}
}  // namespace SP

// @ 0x00574080
namespace SP {
void cAppModeEditorBase_s0057_3520::GetState(cEditorState* state)
{
    if (state) {
        state->mOwnerId = mpOwner->GetId(0);
        state->mEditorMode = mEditorMode;
        state->mRolloverId = (mpRolloverInfo && !mbHideRollover) ? mpRolloverInfo->mId : 0;
        state->mbFlagA = mbFlag4B2;
        state->mbFlagB = mbFlag4B3;
    }
}
}  // namespace SP

// @ 0x005740e0
namespace SP {
bool cAppModeEditorBase_s0057_3520::HasId(uint32_t id)
{ uint32_t* end = mIdsEnd; return find_u(mIdsBegin, end, id) != end; }
}  // namespace SP

// @ 0x00574110
namespace SP {
void cAppModeEditorBase_s0057_3520::CreateEffects(uint32_t type, int param, float scale, float bonus)
{
    const int count = mEffectsEnd - mEffectsBegin;
    const int special = sMathRandom_s0057_3520.RandomUint32Uniform(count - 1);
    float bigSize = 0.0f;
    uint32_t lastType = 0xffffffff;
    const uint32_t requestedType = type;
    for (int i = 0; i < count; ++i) {
        cSPEditorAnimatedEventInfo_s0057_3520* msg = new("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s0057_3520();
        if (msg)
            msg->AddRef();
        float size;
        if (count >= 3 && i == special) {
            size = RandomRangeClamped(4.0f, 5.5f);
            bigSize = size;
        } else
            size = RandomRangeClamped(1.75f, 2.3f);
        switch (type) {
        case 0x43773b7b:
        case 0x6035c10:
        case 0x22b31636:
        case 0x622c20c4:
        case 0xe646113d:
        case 0xe7782027:
            size += 0.5f;
            break;
        case 0x4878ee8:
            size += bonus;
            break;
        }
        if (requestedType == 0x70842ef6) {
            do {
                switch (sMathRandom_s0057_3520.RandomUint32Uniform(6)) {
                case 0: type = 0x70842ef6; break;
                case 1: type = 0x6820bfd9; break;
                case 2: type = 0xeef6cd0; break;
                case 3: type = 0x4f21fc3b; break;
                case 4: type = 0xb3a731ca; break;
                case 5: type = 0xf10ff9fd; break;
                }
            } while (type == lastType);
            lastType = type;
        }
        if (type == 0x8b2f58fe) {
            mEffectsBegin[i].mbScaleA = true;
            mEffectsBegin[i].mScale = size;
        } else if (type == 0x5c4d694c) {
            mEffectsBegin[i].mbScaleB = true;
            mEffectsBegin[i].mScale = size;
        } else
            msg->MessagePost(type, 0, 0, mEffectsBegin[i].mId, 1, size, 0, param, scale);
        mEffectsBegin[i].mDelay = 0.0f;
        mEffectsBegin[i].mSize = size;
        mEffectsBegin[i].mBaseSize = size;
        if (count >= 3)
            mEffectsBegin[i].mSize = bigSize;
        float& sizeRef = mEffectsBegin[i].mSize;
        sizeRef += RandomRangeClamped(1.0f, 4.0f);
        mEffectsBegin[i].mbActive = true;
        if (msg)
            msg->Release();
    }
}
}  // namespace SP

// @ 0x00574460
namespace SP {
bool cAppModeEditorBase_s0057_3520::HasEffect(uint32_t id)
{
    const int count = mEffectsEnd - mEffectsBegin;
    for (int i = 0; i < count; ++i) {
        if (mEffectsBegin[i].mId == id)
            return true;
    }
    return false;
}
}  // namespace SP

// @ 0x005744b0
void SP::cAppModeEditorBase_s0057_44b0::ShowBudgetWindows(int keepClosed)
{
    SP::WindowManager_s0057_44b0()->HideWindow(0x3f1eaf1);
    SP::WindowManager_s0057_44b0()->HideWindow(0x3f1eaf3);
    if (mPanel && mPanel->IsActive()) {
        if (SP::WindowManager_s0057_44b0()->IsWindowOpen(0x3f1eaf3) == 0)
            SP::WindowManager_s0057_44b0()->OpenWindow(0x3f1eaf3, 1);
        else
            SP::WindowManager_s0057_44b0()->CloseWindow(0x3f1eaf3);
    }
    if (keepClosed == 0) {
        if (SP::WindowManager_s0057_44b0()->IsWindowOpen(0x3f1eaf1) == 0)
            SP::WindowManager_s0057_44b0()->OpenWindow(0x3f1eaf1, 1);
        else
            SP::WindowManager_s0057_44b0()->CloseWindow(0x3f1eaf1);
    }
}

// @ 0x00574570
int SP::cAppModeEditorBase_s0057_44b0::GetLaunchSelectedIndex()
{
    if (mLaunchData)
        return mLaunchData->mSelectedIndex;
    return -1;
}

// @ 0x00574590
void* SP::cAppModeEditorBase_s0057_44b0::GetCurrentCameraContext()
{
    SP::cCameraList* cams = mApp->GetCameraManager()->GetCameras();
    if (cams)
        return cams->GetCamera(0x29da727);
    return 0;
}

// @ 0x005745c0
float SP::cAppModeEditorBase_s0057_44b0::GetBudgetFraction()
{
    // Local names matter: /O2 frame slots for address-taken locals follow a name hash.
    if (mEditorSaveModel) {
        bool isCreature = !SP::sAppProperties_s0057_44b0->GetBool(0x677d3ea);
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
void SP::cAppModeEditorBase_s0057_44b0::PurchaseBlock(cSPEditorBlock_s0057_44b0* block)
{
    if (!block)
        return;
    if (block->mPrice > 0) {
        Property* prop;
        if (mCurrentConfigProperties)
            mCurrentConfigProperties->GetProperty(0xb3a88b0b, prop);
        uint32_t instance = 0;
        if (SP::GetPropertyAsKeyInstance(mCurrentConfigProperties, 0xd3a86350, &instance)) {
            Vector3_s0057_44b0 pos, dir;
            SP::App_s0057_44b0()->GetViewer()->GetCameraLocationInfo(&pos, &dir, 0, 0);
            Vector3_s0057_44b0 a, b;
            SP::App_s0057_44b0()->GetViewer()->GetCameraTransform(&a, &b);
        }
    }
    mBudget->PurchaseBlock(block, 0);
}

// @ 0x00574900
ResourceKey SP::cAppModeEditorBase_s0057_44b0::GetRandomBackground()
{
    int count = 0;
    ResourceKey* keys = 0;
    SP::cPropertyList_s0057_44b0* props = mCurrentConfigProperties;
    if (SP::GetPropertyArrayKey(props, 0x503d2f60, &count, &keys) && count > 0) {
        mRandomBackground = sMathRandom_s0057_44b0.RandomUint32Uniform(count);
        return keys[mRandomBackground];
    }
    return ResourceKey();
}

// @ 0x00574990
ResourceKey SP::cAppModeEditorBase_s0057_44b0::GetNextBackground()
{
    int count = 0;
    ResourceKey* keys = 0;
    SP::cPropertyList_s0057_44b0* props = mCurrentConfigProperties;
    if (SP::GetPropertyArrayKey(props, 0x503d2f60, &count, &keys) && count > 0) {
        mRandomBackground = (mRandomBackground + 1) % count;
        return keys[mRandomBackground];
    }
    return ResourceKey();
}

// @ 0x00574a20
int SP::cAppModeEditorBase_s0057_44b0::FlushFactory(cSPEditorResourceFactory_s0057_44b0* factory)
{
    if (!factory)
        factory = mSaveLoadFactory;
    if (factory)
        return factory->Flush(true);
    return 0;
}

// @ 0x00574a60
void SP::cAppModeEditorBase_s0057_44b0::SwitchToPlayModeCamera()
{
    float a, b, c;
    Vector3_s0057_44b0 v;
    SP::cCameraList* cams = SP::App_s0057_44b0()->GetCameraManager()->GetCameras();
    cams->GetCameraValues(&a, &b, &c, &v);
    SP::App_s0057_44b0()->GetCameraManager()->SetActiveCameraID(0x3d437f9);
    SP::cCreatureCameraBase_s0057_44b0* cam = SP::App_s0057_44b0()->GetCameraManager()->GetCameras()->GetCamera(0x6771a60);
    if (cam) {
        SP::cSPEditorAnimatedCreatureManager_s0057_44b0* mgr = mAnimCreatureManager;
        cam->SetCreature(mgr->GetCreature(mShadowViewer));
        cam->SetInitialCameraValues(a, b, c, v);
        cam->SetCallback(SP::PlayModeCameraCallback, this);
    }
}

// @ 0x00574b40
int SP::cAppModeEditorBase_s0057_44b0::ScoreCreatureForZCorp()
{
    int count = mEditorSaveModel->GetBlockCount();
    float minScore = 100.0f;
    float scale = SP::GetPropertyFloat(mCurrentConfigProperties, 0x542ed1b, 1.0f);
    BoundingBox_s0057_44b0 box;
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
            score = SP::GetPaintScore(mEditorSaveModel->GetBlock(i)) * scaledSize;
        } else if (mEditorSaveModel->GetBlock(i)->IsFlagSet(11)) {
            mEditorSaveModel->GetBlock(i)->GetPartScale();
            score = mEditorSaveModel->GetBlock(i)->GetPartScaleFactor() * scaledSize;
        } else {
            float divisor = SP::GetPropertyValueFloat(mEditorSaveModel->GetBlock(i)->mpPropList, 0xfba614, 1.0f);
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
int SP::cAppModeEditorBase_s0057_44b0::CanPublish()
{
    if (mUnk4b0 && (mUnk4b7 || !EditorUtils::GetCreatorType(&mEditorSaveModel->mKey)))
        return 1;
    return 0;
}

// @ 0x00574da0
void SP::cAppModeEditorBase_s0057_44b0::SetupThumbnailModelWorld(cIModelWorld_s0057_44b0* world, bool isAnimated)
{
    SP::cModelManager_s0057_44b0* mm = SP::ModelManager_s0057_44b0();
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
void SP::cAppModeEditorBase_s0057_44b0::UpdateModelSounds(float deltaTime)
{
    uint32_t soundId = 0;
    float maxValue = 0.0f;
    bool isPlayMode = mEditorMode == 2;
    if (isPlayMode && mEditorSaveModel) {
        int count = mEditorSaveModel->GetBlockCount();
        for (int i = 0; i < count; i++) {
            SP::cSPEditorBlock_s0057_44b0* block = mEditorSaveModel->GetBlock(i);
            if (block->mSoundData) {
                SP::cPropertyList_s0057_44b0* list = SP::PropManager()->GetPropertyList(block->mInstanceID, block->mGroupID);
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
        EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT_s0057_44b0();
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
        EA::Audio::IAudioSystem* audio = EA::Audio::GetSystemAT_s0057_44b0();
        uint32_t inst = audio ? audio->CreateInstance() : 0;
        mCurrentInstanceId = inst;
        mCurrentSoundId = soundId;
        Start3dSoundByName(soundId, inst, 0.0f, 0.0f, 0.0f);
    }
}

// @ 0x00575120
void SP::cAppModeEditorBase_s0057_44b0::ExitEditorUI()
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
    SP::GameViewA()->SetFlags(1, 1);
}

// @ 0x005751b0
void SP::cAppModeEditorBase_s0057_44b0::SetupGameViewLayers()
{
    static cDefaultLayerHandler sHandler;
    SP::GameViewB()->AddLayer(kLayerKeyA, 0, 0, -1.0f, -1.0f, 0.0f, 0, 0);
    SP::GameViewB()->AddLayer(kLayerKeyB, &sHandler, 0, -1.0f, -1.0f, 0.0f, 0, 0);
}

// @ 0x00575790
void SP::cAppModeEditorBase_s0057_5270::DoSomePaletteThing()
{
    cPartsPalette_s0057_5270* p = Field<cPartsPalette_s0057_5270>(this, 0xd4);
    if (p)
        p->Reset(0, 1);
}

// @ 0x005757b0
void SP::cAppModeEditorBase_s0057_5270::StopSomething()
{
    if (Field<cPartsPalette_s0057_5270>(this, 0xd4)) {
        Field<cPartsPalette_s0057_5270>(this, 0xd4)->SomeA();
        Field<cPartsPalette_s0057_5270>(this, 0xd4)->SomeB();
    }
    if (Value<char>(this, 0x4d4) != 0) {
        void* fx = FXManager();
        if (fx) {
            // fx->Fade(0x1002, 0.0f, 0.0f, 1)
            typedef void (__thiscall *FadeFn)(void*, uint32_t, float, float, int);
            FadeFn f = *(FadeFn*)(*(void***)fx + 7);
            f(fx, 0x1002, 0.0f, 0.0f, 1);
        }
        ByteRef(this, 0x4d4) = 0;
    }
}

// @ 0x00575810
bool SP::cAppModeEditorBase_s0057_5270::TestCondition(uint32_t id)
{
    if (id == 0x29930bb7)
        return true;
    if (id == 0xb7b7acea)
        return ConfigManager()->Query(0x4ea96cb) != 0;
    cEffectsWorld* world = Field<cEffectsWorld>(this, 0x90);
    int mode = -1;
    if (world)
        mode = world->mMode;
    if (id == 0x32d61d9f)
        return mode == 0xdfad9f51;
    if (id == 0xaa9b2bd0)
        return mode == 0x9ea3031a;
    if (id == 0x7579b23b)
        return mode == 0xdfad9f51 || mode == 0x9ea3031a;
    if (id == 0xbb107abd) {
        switch (mode) {
        case 0x1a4e0708: case 0xbc1041e6: case 0x8f963dcb: case 0x98e03c0d: case 0x9ad7d4aa:
        case 0xc0b74287: case 0xc15695da: case 0xf670aa43: case 0x441cd3e6: case 0x1f2a25b6:
        case 0x2090a11b: case 0x2a5147a9: case 0x449c040f: case 0x7d433fad:
            return true;
        }
        return false;
    }
    if (id == 0x5caf038c) {
        switch (mode) {
        case 0x1a4e0708: case 0xbc1041e6: case 0x99e92f05: case 0x8f963dcb: case 0x98e03c0d:
        case 0x9ad7d4aa: case 0xc15695da: case 0xbdd15f3d: case 0xc0b74287: case 0xf670aa43:
        case 0x449c040f: case 0x2a5147a9: case 0x1f2a25b6: case 0x2090a11b: case 0x441cd3e6:
        case 0x72c49181: case 0x47c10953: case 0x4e3f7777: case 0x7d433fad:
            return true;
        }
        return false;
    }
    if (id == 0xeef0ea70)
        return Value<int>(this, 0x314) == 0;
    if (id == 0x724eb5a)
        return Value<int>(this, 0x314) == 1;
    if (id == 0xe3e13884)
        return Value<int>(this, 0x314) == 2;
    if (id == 0xb801a2e9) {
        int state = Value<int>(this, 0x314);
        return state == 0 || state == 1;
    }
    if (id == 0x2ad85c42) {
        if (Value<int>(this, 0x314) != 1)
            return false;
        return Field<cSPPaletteUI_s0057_5270>(this, 0x3bc)->IsPaintByNumber();
    }
    if (id == 0x8c8e374f) {
        cSPPlayMode_s0057_5270* pm = Field<cSPPlayMode_s0057_5270>(this, 0x74);
        if (!pm || !pm->mpUI)
            return false;
        return pm->mpUI->IsUIGroupEnabled(0x3e831e4);
    }
    if (id == 0xbb8adf33) {
        cSPPlayMode_s0057_5270* pm = Field<cSPPlayMode_s0057_5270>(this, 0x74);
        if (!pm || !pm->mpUI)
            return false;
        return !pm->mpUI->IsUIGroupEnabled(0x3e831e4);
    }
    if (id == 0x1b31085a) {
        cSPPlayMode_s0057_5270* pm = Field<cSPPlayMode_s0057_5270>(this, 0x74);
        if (!pm || !pm->mpUI)
            return false;
        return pm->mpUI->IsUIGroupEnabled(0x445ea18);
    }
    if (id == 0x014d1e0f) return Field<cDevFlags>(this, 0x4d0)->f[0x00];
    if (id == 0x161221ce) return Field<cDevFlags>(this, 0x4d0)->f[0x01];
    if (id == 0x2430a336) return Field<cDevFlags>(this, 0x4d0)->f[0x02];
    if (id == 0x6048fb3d) return Field<cDevFlags>(this, 0x4d0)->f[0x03];
    if (id == 0x0b4ca6a9) return Field<cDevFlags>(this, 0x4d0)->f[0x04];
    if (id == 0xf69266e2) return Field<cDevFlags>(this, 0x4d0)->f[0x05];
    if (id == 0x9b2b681c) return Field<cDevFlags>(this, 0x4d0)->f[0x06];
    if (id == 0x6d7524f9) return Field<cDevFlags>(this, 0x4d0)->f[0x07];
    if (id == 0x7fed6bf3) return Field<cDevFlags>(this, 0x4d0)->f[0x08];
    if (id == 0x7a0819fb) return Field<cDevFlags>(this, 0x4d0)->f[0x0a];
    if (id == 0xfb1889ca) return Field<cDevFlags>(this, 0x4d0)->f[0x09];
    if (id == 0x60a3fd04) return Field<cDevFlags>(this, 0x4d0)->f[0x0b];
    if (id == 0x4ade2e01) return Field<cDevFlags>(this, 0x4d0)->f[0x0d];
    if (id == 0xde0b3ea5) return Field<cDevFlags>(this, 0x4d0)->f[0x0e];
    if (id == 0xb10dafec) return Field<cDevFlags>(this, 0x4d0)->f[0x0f];
    if (id == 0x017d4661) return Field<cDevFlags>(this, 0x4d0)->f[0x10];
    if (id == 0xd0092be3) return Field<cDevFlags>(this, 0x4d0)->f[0x11];
    if (id == 0x1c06bc61) return Field<cDevFlags>(this, 0x4d0)->f[0x13];
    if (id == 0xe433bdff) return Field<cDevFlags>(this, 0x4d0)->f[0x14];
    if (id == 0xfd0e3743) return Field<cDevFlags>(this, 0x4d0)->f[0x15];
    if (id == 0xf4e08da8) return Field<cDevFlags>(this, 0x4d0)->f[0x16];
    if (id == 0xf15525c4) return Field<cDevFlags>(this, 0x4d0)->f[0x17];
    if (id == 0xf7d20932) return Field<cDevFlags>(this, 0x4d0)->f[0x18];
    if (id == 0x23f2b3a5) return Field<cDevFlags>(this, 0x4d0)->f[0x19];
    if (id == 0xeca69bad) return Field<cDevFlags>(this, 0x4d0)->f[0x1a];
    if (id == 0x7069b614) return Field<cDevFlags>(this, 0x4d0)->f[0x1b];
    if (id == 0xf665cf0c) return Field<cDevFlags>(this, 0x4d0)->f[0x1c];
    if (id == 0x33b98f05) return Field<cDevFlags>(this, 0x4d0)->f[0x1d];
    if (id == 0x6e1efa9d) return Field<cDevFlags>(this, 0x4d0)->f[0x1e];
    if (id == 0x51b1fcf8) return Field<cDevFlags>(this, 0x4d0)->f[0x1f];
    if (id == 0x10378cc2) return Field<cDevFlags>(this, 0x4d0)->f[0x20];
    if (id == 0xb6ce8f75) return Field<cDevFlags>(this, 0x4d0)->f[0x21];
    if (id == 0x1fadf1ce) return Value<int>(this, 0x4e4) >= 2;
    if (id == 0x3929810f) return Value<int>(this, 0x4e4) >= 3;
    if (id == 0xe6bc4398) return Value<int>(this, 0x4e4) >= 4;
    if (id == 0x0417cce9) return Value<int>(this, 0x4e4) >= 5;
    if (id == 0x9040ba0a) return Value<int>(this, 0x4e4) >= 6;
    if (id == 0x2546df79) {
        cDevFlags* flags = Field<cDevFlags>(this, 0x4d0);
        return flags->f[9] || flags->f[0xa] || flags->f[0xc];
    }
    if (id == 0x83bf2549) {
        IEditorEntries* entries = Field<IEditorEntries>(this, 0x42c);
        if (!entries)
            return false;
        return entries->Query(0) < 0;
    }
    return false;
}

// @ 0x00575e20
void SP::cAppModeEditorBase_s0057_5270::GetSomething1(int arg)
{
    if (Value<int>(this, 0x1d0) == Value<int>(this, 0x1d4)) {
        void* p = Field<void>(this, 0x1c0);
        if (p == 0 || Value<char>(p, 0x35) == 0) {
            Field<VObj>(this, 0x8c)->slot0(arg);
        }
    }
}

// @ 0x00575e50
int SP::cAppModeEditorBase_s0057_5270::GetSomething2()
{
    int v = Value<int>(this, 0x1d0);
    if (v == Value<int>(this, 0x1d4)) {
        void* p = Field<void>(this, 0x1c0);
        if (p != 0 && Value<char>(p, 0x35) != 0)
            return Value<int>(p, 0x40);
        int r = Field<VObj>(this, 0x8c)->slot1();
        return r;
    }
    return v;
}

// @ 0x005767f0
void WriteBoolVector(cSerializer* s, const BoolVector& v)
{
    uint32_t count = (uint32_t)(v.mpEnd - v.mpBegin);
    EA::IO::WriteUint32(s->GetProvider()->GetStream(), &count, 1, 0);
    for (const uint8_t* it = v.mpBegin; it != v.mpEnd; ++it) {
        bool b = *it != 0;
        EA::IO::WriteBool8(s->GetProvider()->GetStream(), &b, 1);
    }
    s->EndBlock();
}

// @ 0x00576880
bool ReadIntArray6(cSerializer* s, int32_t* values)
{
    int32_t count;
    EA::IO::ReadInt32(s->GetProvider()->GetStream(), &count, 1, 0);
    int n = eastl::min(count, 6);
    for (int i = 0; i < n; i++)
        EA::IO::ReadInt32(s->GetProvider()->GetStream(), &values[i], 1, 0);
    return true;
}

// @ 0x00576900
cEditorSnapshot& cEditorSnapshot::operator=(const cEditorSnapshot& x)
{
    Copy(x);
    return *this;
}

// @ 0x00576970
template <> int eastl::basic_string_s0057_6140<wchar_t>::compare(const wchar_t* pBegin1, const wchar_t* pEnd1, const wchar_t* pBegin2, const wchar_t* pEnd2)
{
    const int n1 = (int)(pEnd1 - pBegin1);
    const int n2 = (int)(pEnd2 - pBegin2);
    const int cmp = Compare(pBegin1, pBegin2, (size_t)eastl::min(n1, n2));
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
}

// @ 0x005769d0
void uninitialized_fill_n_ref(EA::AutoRefCount_s0057_6140<IRefCounted>* dest, size_t n, const EA::AutoRefCount_s0057_6140<IRefCounted>& value)
{
    EA::AutoRefCount_s0057_6140<IRefCounted>* cur = dest;
    for (; n > 0; --n, ++cur)
        ::new(cur) EA::AutoRefCount_s0057_6140<IRefCounted>(value);
}

// @ 0x00576a10
cEditorSnapshot* uninitialized_copy_snapshot(const cEditorSnapshot* first, const cEditorSnapshot* last, cEditorSnapshot* dest)
{
    for (; first != last; ++first, ++dest)
        ::new(dest) cEditorSnapshot(*first);
    return dest;
}

// @ 0x00576ab0
Vector3_s0057_6140* ColorToVector3(Vector3_s0057_6140* out, uint32_t color)
{
    out->x = (float)((color >> 16) & 0xff) * (1.0f / 255.0f);
    out->y = (float)((color >> 8) & 0xff) * (1.0f / 255.0f);
    out->z = (float)(color & 0xff) * (1.0f / 255.0f);
    return out;
}

// @ 0x00576b00
Matrix3 RotationMatrix(const Vector3_s0057_6140& axis, float angle)
{
    Matrix3 m;
    return MakeRotation(m, axis, angle);
}

// @ 0x00576b40
BoundingBox_s0057_6140::BoundingBox_s0057_6140()
{
    lower = Vector3_s0057_6140(3.402823466e+38f, 3.402823466e+38f, 3.402823466e+38f);
    upper = Vector3_s0057_6140(-3.402823466e+38f, -3.402823466e+38f, -3.402823466e+38f);
}

// @ 0x00576bb0
void cEditorBudgetCheat::ParseLine(const EA::ArgScript::Line& line)
{
    if (this)
        AddRef();
    size_t numArgs;
    line.MainArguments(&numArgs, 0, 0x7fffffff);
    SP::cAppModeEditorBase_s0057_6140* editor = mpEditor;
    if (editor->mbActive)
        editor->mBudget->AddDNA(0, 150);
    Release();
}

// @ 0x00576c10
void cEditorAddDNACheat::Execute(const EA::ArgScript::Line& line)
{
    if (this)
        AddRef();
    size_t numArgs;
    line.MainArguments(&numArgs, 0, 0x7fffffff);
    mpEditor->AddDNA();
    Release();
}

// @ 0x00576c50
bool SP::cAppModeEditorBase_s0057_6140::Shutdown()
{
    if (mbActive)
        Deactivate();
    SP::CheatManager()->RemoveCheat("addDNA");
    SP::CheatManager()->RemoveCheat("toggleeditorbackground");
    SP::CheatManager()->RemoveCheat("colladaexport");
    mApp = 0;

    SP::cMessageServer* server = SP::MessageServer_s0057_6140();
    if (server) {
        if (mHandler[0]) {
            uint32_t h = mHandler[0];
            mHandler[0] = 0;
            EA::Messaging::RemoveHandler(h, mHandler[1], mHandler[2], mHandler[3], mHandler[4]);
        }
        server->RemoveListener(&mMessageListener, 0x29d57f4, -9999);
        server->RemoveListener(&mMessageListener, 0x3fc3f13, -9999);
        server->RemoveListener(&mMessageListener, 0x62628f0, -9999);
    }
    SP::ShutdownEditorSubsystem();
    SP::ShutdownEditorSubsystem();

    if (mEditorSaveModel.mpObject) {
        SaveModel()->ClearModel();
        mEditorSaveModel = 0;
    }
    if (mEditorModel) {
        ((SP::cSPEditorModel_s0057_6140*)mEditorModel)->ClearModel();
        mEditorSaveModel = 0;
    }
    mPedestalModel = 0;
    mTestEnvironmentModel = 0;
    mBackgroundModel = 0;

    if (mSaveModelWorld) {
        IReleasable* p = mSaveModelWorld;
        mSaveModelWorld = 0;
        p->Release();
    }
    if (mModelWorld) {
        IReleasable* p = mModelWorld;
        mModelWorld = 0;
        p->Release();
    }
    if (mBackgroundModelWorld) {
        IReleasable* p = mBackgroundModelWorld;
        mBackgroundModelWorld = 0;
        p->Release();
    }
    SP::ModelManager_s0057_6140()->ReleaseModels(0xe4c6e4);
    SP::ModelManager_s0057_6140()->ReleaseModels(0x21b37d6);
    SP::ModelManager_s0057_6140()->ReleaseModels(0x5557b15);
    if (mEffectsWorld) {
        IReleasable* p = mEffectsWorld;
        mEffectsWorld = 0;
        p->Release();
    }
    SP::EffectsManager()->ReleaseEffects(0xe4c6e4);
    if (mTextureFactory)
        mTextureFactory = 0;
    if (mPhysicsWorld) {
        mPhysicsWorld->Clear();
        if (mPhysicsWorld) {
            SP::cSPEditorPhysicsWorld_s0057_6140* p = mPhysicsWorld;
            mPhysicsWorld = 0;
            p->Release();
        }
    }
    DeleteViewer(mViewers[1]);
    DeleteViewer(mViewers[2]);
    DeleteViewer(mViewers[0]);
    DeleteViewer(mViewers[3]);
    DeleteViewer(mViewers[4]);

    EA::Audio::IAudioSystem_s0057_6140* audio = EA::Audio::GetSystemAT_s0057_6140();
    if (audio) {
        audio->BeginMessage(0x347536b);
        audio->AddParam(0x3475385, 0xb07c3bbf);
        audio->AddParam(0x34753a0, 1);
        audio->SendMessage();
    }

    SP::cSaveArea* area = SP::GetSaveArea(SP::kEditorSaveArea);
    if (area) {
        EA::AutoRefCount_s0057_6140<SP::cSaveRecord> record;
        if (area->OpenRecord(SP::kEditorSaveKey, &record, 2, 2, 1, 0)) {
            record->GetStream()->Write(mSaveData, 8);
            record->Close();
        }
        if (record.mpObject)
            record.mpObject->Release();
    }
    SP::ShutdownEditorUI();
    SP::sEditorResource = 0;
    return true;
}

// @ 0x00577130
void SP::cAppModeEditorBase::SetSoundBlockAdded(SP::cSPEditorBlock * param)
{
    int param_v = (int)param;
    int p = param_v;
    if (Ref<char>(this, 0x20e) != 0) {
        if (p != 0) {
            int local[3];
            ((cBlockF40b90*)param)->F40b90(local);
            int n = g_soundBlockCounter + 1;
            g_soundBlockCounter = n;
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xc8b0416e, (float)n, 0);
        }
        if (Ref<char>(this, 0x20e) != 0) {
            float sz = SP::EditorUtils::CalculateModelSize(Field<void>(this, 0x98));
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (Ref<char>(this, 0x20e) != 0) {
                int cnt = SP::EditorUtils::CountModelParts(Field<void>(this, 0x98));
                SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
    }
}

// @ 0x005771f0
void SP::cAppModeEditorBase::SetSoundBlockRemoved(SP::cSPEditorBlock * param)
{
    int param_v = (int)param;
    int p = param_v;
    if (Ref<char>(this, 0x20e) != 0) {
        if (p != 0) {
            int local[3];
            ((cBlockF40b90*)param)->F40b90(local);
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xbb98bc04, (float)g_soundBlockCounter, 0);
        }
        if (Ref<char>(this, 0x20e) != 0) {
            float sz = SP::EditorUtils::CalculateModelSize(Field<void>(this, 0x98));
            SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0xdef22b96, sz, 0);
            if (Ref<char>(this, 0x20e) != 0) {
                int cnt = SP::EditorUtils::CountModelParts(Field<void>(this, 0x98));
                SP::EditorUtils::PlayEditorSound(0x1d6253c0, 0x5ee38119, (float)cnt, 0);
            }
        }
    }
}

// @ 0x005772b0
void SP::cAppModeEditorBase::RemoveTorsoFromEffectsMask()
{
    void* p = Ref<void*>(this, 0xf0);
    if (p) {
        void** vt = *(void***)(*(void**)p);
        ((void(__stdcall*)(void*, int))vt[91])(p, 0);
        p = Ref<void*>(this, 0xf0);
        if (p) {
            Ref<void*>(this, 0xf0) = 0;
            int c = Ref<int>(p, 0x40);
            if (c > 1) {
                Ref<int>(p, 0x40) = c - 1;
                return;
            }
            unsigned r = Ref<unsigned>(p, 4);
            int b = (r >> 31) & 1;
            void** vt2 = *(void***)(*(void**)p);
            ((void(__stdcall*)(void*, int))vt2[92])(p, b);
        }
    }
}

// @ 0x00577310
void SP::cAppModeEditorBase_s0057_7130::PreloadResources(int key)
{
    if (Ref<cTexturePreload_s0057_7130*>(this, 0x308) == 0) {
        cTexturePreload_s0057_7130* p = new ("Editor", 0, 0, 0, 0) cTexturePreload_s0057_7130(-1);
        cTexturePreload_s0057_7130* old = Ref<cTexturePreload_s0057_7130*>(this, 0x308);
        if (p != old) {
            if (p)
                p->AddRef();
            Ref<cTexturePreload_s0057_7130*>(this, 0x308) = p;
            if (old)
                old->Release();
        }
        ResKey3 k0 = { 0x8104e4b0, 0x510a95b, 0x40464100 };
        Ref<cTexturePreload_s0057_7130*>(this, 0x308)->PreloadTextureList(&k0);
        ResKey3 k1 = { 0x9d1fcc2f, 0x510a95b, 0x40464100 };
        Ref<cTexturePreload_s0057_7130*>(this, 0x308)->PreloadTextureList(&k1);
        ResKey3 k2 = { 0x7d708f46, 0x510a95b, 0x40464100 };
        Ref<cTexturePreload_s0057_7130*>(this, 0x308)->PreloadTextureList(&k2);
    }
    if (key != -1) {
        IRCptr props;
        if (PropertyManager_s0057_7130()->GetPropertyList(key, g_preloadGroup, props.AsPointer())) {
            cTexturePreload_s0057_7130* p = new ("Editor", 0, 0, 0, 0) cTexturePreload_s0057_7130(-1);
            cTexturePreload_s0057_7130* old = Ref<cTexturePreload_s0057_7130*>(this, 0x30c);
            if (p != old) {
                if (p)
                    p->AddRef();
                Ref<cTexturePreload_s0057_7130*>(this, 0x30c) = p;
                if (old)
                    old->Release();
            }
            uint32_t inst = 0;
            GetPropertyAsKeyInstance(props.mp, 0x700ed5e1, &inst);
            if (inst != 0) {
                ResKey3 k3 = { inst, 0x510a95b, 0x40464100 };
                Ref<cTexturePreload_s0057_7130*>(this, 0x30c)->PreloadTextureList(&k3);
            }
        }
        props.Drop();
    }
}

// @ 0x005774f0
void SP::cAppModeEditorBase_s0057_7130::SetSomeBlock(int param)
{
    ((ObjF8*)((char*)this + 0xf8))->SomeMethod(param);
    if ((unsigned char)param == 0)
        DoSomeOther(0, -1);
}

// @ 0x00577520
void SP::cAppModeEditorBase_s0057_7130::UpdateBlockState()
{
    void* p = Ref<void*>(this, 0xcc);
    if (p != 0) {
        unsigned bits = Ref<unsigned>(p, 0xdc8);
        unsigned flag = (bits >> 1) & 1;
        if (flag != 0)
            DoSomeOther(0, -1);
    }

    if (Ref<void*>(this, 0xe4) != 0) {
        void* r = ((ObjE4*)Ref<void*>(this, 0xe4))->SomeCall();
        if (r == 0 ||
            ((Ref<unsigned>(((ObjE4*)Ref<void*>(this, 0xe4))->SomeCall(), 0xdc8) >> 1) & 1) != 0)
            SetRolloverHandle(0, 1);
    }
}

// @ 0x00577580
void SP::cAppModeEditorBase_s0057_7130::SetTorsoBlock(void* block, char param)
{
    if (block != 0) {
        if (param != 0)
            param = 0;
        PlayEditorEvent(0xe5469985);
    } else {
        if (param != 0)
            PlayEditorEvent(0xe5469985);
    }
    void* prev = Ref<void*>(this, 0xdc);
    if (block != prev) {
        if (block)
            ((IObject_s0057_7130*)block)->AddRef();
        Ref<void*>(this, 0xdc) = block;
        if (prev)
            ((IObject_s0057_7130*)prev)->Release();
    }
    void* a = Ref<void*>(this, 0xd4);
    Ref<char>(this, 0xe0) = param;
    void* b = Ref<void*>(this, 0xd8);
    if (a != b) {
        if (a)
            ((IObject_s0057_7130*)a)->AddRef();
        Ref<void*>(this, 0xd8) = a;
        if (b)
            ((IObject_s0057_7130*)b)->Release();
    }
}

// @ 0x00577620
bool SP::cAppModeEditorBase_s0057_7130::HasSkin()
{
    if (Ref<int>(this, 0x360) != 0 && Ref<int>(this, 0x150) != 0) {
        if (Field<ISkinManager_s0057_7130>(this, 0x150)->GetSkin(1) != 0)
            return true;
    }
    return false;
}

// @ 0x00577650
void SP::cAppModeEditorBase_s0057_7130::SaveSomething()
{
    IResMan_s0057_7130* mgr = GetManager_s0057_7130();
    void* saveArea = GetSaveArea_s0057_7130(Ref<uint32_t>(this, 0x2ac));
    GetTexSvc()->Slot68(Ref<void*>(this, 0x28c));
    ModelRes* model = new ("Editor", 0, 0, 0, 0) ModelRes();
    if (model)
        model->AddRef();
    if (!Field<cMWModel_s0057_7130>(this, 0x9c)->SaveResource(model)) {
        if (model)
            model->Release();
        return;
    }
    ResKey3* newKey = &model->mKey;
    ResKey3 nameKey = *newKey;
    nameKey.b = 0x1a99b06b;
    bool w1 = mgr->WriteResource(model, 0, saveArea, 0, &nameKey);
    bool w2 = mgr->Slot6c(model, 1);
    if (!w1 || !w2) {
        model->Release();
        return;
    }
    if (FlushFactory(Ref<void*>(this, 0x154))) {
        ThumbRes* t = new ("Editor", 0, 0, 0, 0) ThumbRes();
        ResRef tr(t);
        ThumbRes* th = (ThumbRes*)tr.mpObject;
        Fn46d840(model, th);
        ResKey3 tk = *newKey;
        tk.b = 0xf43029a;
        th->mKey = tk;
        bool t1 = mgr->WriteResource(th, 0, saveArea, 0, 0);
        bool t2 = mgr->Slot6c(th, 1);
        if (!t1 || !t2) {
            th->Release();
            model->Release();
            return;
        }
        th->Release();
    }
    bool pollen = false;
    int mode = Ref<int>(this, 0x388);
    if (((mode == 2 && Ref<char>(this, 0x4b5) != 0 && Field<cMWModel_s0057_7130>(this, 0x9c)->mKey.b != 0x3d97a8e4) || mode == 1) &&
        Fn4f3d60(Ref<Bits128_s0057_7130>(this, 0x58), g_validBits))
        pollen = true;
    MetaObj_s0057_7130* mo = new ("Pollinator", 0, 0, 0, 0) MetaObj_s0057_7130();
    ResRef mr(mo);
MetaObj_s0057_7130* meta = (MetaObj_s0057_7130*)mr.mpObject;
#define META meta
    cMWModel_s0057_7130* ped = Field<cMWModel_s0057_7130>(this, 0x9c);
    ResKey3* parentKey = (ResKey3*)((char*)this + 0x1d0);
    META->Set(newKey, ped->Slot1(), ped->Slot3(), ((SubObj5*)((char*)this + 0xc))->Slot5(), parentKey, pollen);
    bool w3 = mgr->WriteResource(META, 0, saveArea, 0, 0);
    bool w4 = MarkDirty(META);
    if (w3 && w4) {
        cImportExport* ie = GetImportExport();
        if (ie)
            ie->CreateExportThumb(model, Field<ImgObj>(this, 0x28c)->GetPixels(), saveArea, 0, 0);
        if (!pollen) {
            Ref<char>(this, 0x4b0) = 1;
        } else if (!AuthManager()->Slot24()) {
            Sub572430(&Field<cMWModel_s0057_7130>(this, 0x9c)->mKey);
        }
        if (model->mKey.b == 0x2b978c46) {
            int* vb = Ref<int*>(this, 0x588);
            int* ve = Ref<int*>(this, 0x58c);
            if (vb == ve) {
                if (Ref<char>(this, 0x4b8) != 0 && GetModelCategory(parentKey) == 1) {
                    SummarizePart(parentKey, newKey, 0xa426730b);
                    SummarizePart(parentKey, newKey, 0xad56080c);
                    SummarizePart(parentKey, newKey, 0xf71fa311);
                    SummarizePart(parentKey, newKey, 0xbeb528cb);
                    SummarizePart(parentKey, newKey, 0x2db6dad3);
                }
            } else {
                int n = ve - vb;
                for (int i = 0; i < n; i++) {
                    int part = Ref<int*>(this, 0x588)[i];
                    if (part)
                        SummarizeVehiclePart(newKey, part);
                }
            }
        }
    }
    if (META)
        META->Release();
    model->Release();
}

// @ 0x00577b20
bool __cdecl HasAnyResource(cSPEditorBlock_s0057_7130* block, ResKey3* key)
{
    IResMan_s0057_7130* mgr = GetManager_s0057_7130();
    IRCptr ref;
    ResKey3 k0 = block->GetMirroredKey(-1, 0);
    ResKey3 k1 = block->GetMirroredKey(0, 0);
    ResKey3 k2 = block->GetMirroredKey(1, 0);
    if (mgr) {
        if (mgr->GetResource(key, ref.AsPointer(), 0, 0, 0, 0)) {
            if (!ref.mp)
                return false;
            ModelParts* m = ((IModelRes*)ref.mp)->Query(0x3c609f8);
            if (!m) {
                ref.Drop();
                return false;
            }
            Block_s0057_7130* base = m->mpBegin;
            int n = m->mpEnd - base;
            for (int i = 0; i < n; i++) {
                if (base[i].id == k0.a || base[i].id == k1.a || base[i].id == k2.a) {
                    ref.Drop();
                    return true;
                }
            }
        }
    }
    ref.Drop();
    return false;
}

// @ 0x00577c40
bool SP::cAppModeEditorBase_s0057_7130::LoadSomething(void* param)
{
    ResKey3 k0 = ((cSPEditorBlock_s0057_7130*)param)->GetMirroredKey(-1, 0);
    ResKey3 k1 = ((cSPEditorBlock_s0057_7130*)param)->GetMirroredKey(0, 0);
    ResKey3 k2 = ((cSPEditorBlock_s0057_7130*)param)->GetMirroredKey(1, 0);
    cSPPaletteCursor* cur = new ("Editor", 0, 0, 0, 0) cSPPaletteCursor();
    if (cur)
        cur->AddRef();
    cur->SetPalette(Ref<void*>(this, 0x3b8));
    PRec* rec = cur->First(0, 0, 0, 0);
    bool found = false;
    while (rec && !found) {
        if (rec->f24 == 0xc9db779b) {
            IRCptr props;
            if (PropertyManager_s0057_7130()->GetPropertyList(rec->f0c, rec->f14, props.AsPointer())) {
                ResKey3 key = { 0, 0, 0 };
                if (GetPropertyAsKey(props.mp, 0x22e8410, &key))
                    found = HasAnyResource((cSPEditorBlock_s0057_7130*)param, &key);
            }
            props.Drop();
        } else {
            uint32_t id = rec->f0c;
            if (id == k0.a || id == k1.a || id == k2.a)
                found = true;
        }
        rec = cur->Next(0, 0, 0, 0);
    }
    cur->Close();
    if (cur)
        cur->Release();
    return found;
}

// @ 0x00577dd0
void SP::cAppModeEditorBase_s0057_7130::SomeLoader()
{
    if (Ref<int>(this, 0x360) != 0 && Field<ISkinManager_s0057_7130>(this, 0x150) != 0 &&
        Field<ISkinManager_s0057_7130>(this, 0x150)->GetSkin(1) != 0)
        return;
    Field<ModelObj_s0057_7130>(this, 0x98)->Reset();
    Ref<char>(this, 0x385) = 0;
}

// @ 0x00579a20
bool SP::cAppModeEditorBase_s0057_94b0::HasSameMask()
{
    void* p = *(void**)((char*)this + 0x1cc);
    if (p == 0)
        return false;
    unsigned local[4];
    local[0] = *(unsigned*)((char*)p + 0x24) & g_mask[0];
    local[1] = *(unsigned*)((char*)p + 0x28) & g_mask[1];
    local[2] = *(unsigned*)((char*)p + 0x2c) & g_mask[2];
    local[3] = *(unsigned*)((char*)p + 0x30) & g_mask[3];
    for (unsigned i = 0; i < 16; i += 4) {
        if (*(unsigned*)((char*)local + i) != *(unsigned*)((char*)g_mask + i))
            return false;
    }
    return true;
}

// @ 0x00579a90
void cWString::RangeInitialize(const wchar_t* s)
{
    const wchar_t* e = s;
    while (*e != 0)
        ++e;
    uint32_t len = (uint32_t)(e - s);
    uint32_t nSize = len * 2;
    AllocateSelf(len + 1);
    memcpy(mpBegin, s, nSize);
    mpEnd = (wchar_t*)((char*)mpBegin + nSize);
    *mpEnd = 0;
}

// @ 0x00579c60
cString8& cString8::operator=(const cString8& other)
{
    if (&other != this)
        assign(other.mpBegin, other.mpEnd);
    return *this;
}

// @ 0x00579e20
SP::cAppModeEditorBase::~cAppModeEditorBase()
{
    *(void**)((char*)this + 0x00) = vtbl_cAppModeEditorBase;
    *(void**)((char*)this + 0x04) = vtbl_13f57e4;
    *(void**)((char*)this + 0x08) = vtbl_13f57e0;
    *(void**)((char*)this + 0x0c) = vtbl_13f57c8;
    *(void**)((char*)this + 0x10) = vtbl_13f57b8;
    *(void**)((char*)this + 0x14) = vtbl_13f57a8;
    *(void**)((char*)this + 0x1c) = vtbl_13f57a4;
    g_015e4ef0 = 0;
    HANDLER(0x5e8)
    HANDLER(0x5d4)
    HANDLER(0x5c0)
    ARRDEL(0x588)
    {
        char* e = (char*)this + 0x580;
        int i = 5;
        do {
            void* a = *(void**)(e - 0x14);
            e -= 0x14;
            if (a && ((int*)a)[-1]) operator_delete__(a);
            i--;
        } while (i >= 0);
    }
    ARRDEL(0x4d8)
    REL(0x4bc, 2)
    REL(0x4a4, 1)
    REL(0x4a0, 1)
    REL(0x49c, 1)
    REL(0x498, 1)
    REL(0x494, 1)
    ((RbTreeStub*)((char*)this + 0x454))->DoNukeSubtree(*(void**)((char*)this + 0x460));
    RCDEC(0x434)
    ARRDEL(0x41c)
    ARRDEL(0x408)
    REL(0x3c4, 1)
    REL(0x3c0, 2)
    REL(0x3bc, 1)
    REL(0x3b8, 2)
    ARRDEL(0x39c)
    REL(0x380, 2)
    ARRDEL(0x36c)
    RCDEC(0x360)
    REL(0x35c, 1)
    REL(0x358, 1)
    REL(0x354, 1)
    REL(0x350, 3)
    ARRDEL(0x334)
    ARRDEL(0x320)
    REL(0x30c, 1)
    REL(0x308, 1)
    REL(0x2a4, 1)
    REL(0x2a0, 1)
    REL(0x29c, 1)
    REL(0x294, 1)
    ATOMDEC(0x290)
    ATOMDEC(0x28c)
    STRDEL(0x1dc, 0x1e4)
    REL(0x1cc, 2)
    ((RbTreeStub*)((char*)this + 0x1b0))->DoNukeSubtree(*(void**)((char*)this + 0x1bc));
    REL(0x1ac, 1)
    ((VecStub*)((char*)this + 0x174))->DtorStarRecordVec();
    ((VecStub*)((char*)this + 0x160))->DtorSharedLibVec();
    REL(0x15c, 2)
    REL(0x158, 2)
    REL(0x154, 1)
    REL(0x150, 1)
    REL(0x14c, 2)
    REL(0x148, 1)
    TAGDEC(0xf0)
    REL(0xe4, 1)
    REL(0xdc, 2)
    REL(0xd8, 2)
    REL(0xd4, 2)
    REL(0xd0, 2)
    REL(0xcc, 2)
    STRDEL(0xb0, 0xb8)
    TAGDEC(0xac)
    TAGDEC(0xa8)
    TAGDEC(0xa4)
    TAGDEC(0xa0)
    RCDEC8(0x9c)
    RCDEC8(0x98)
    REL(0x94, 1)
    RCDEC(0x90)
    REL(0x8c, 1)
    REL(0x88, 1)
    REL(0x84, 1)
    REL(0x80, 1)
    REL(0x7c, 2)
    {
        char* p = F(char, 0x78);
        if (p) ((V*)(p + 4))->s1();
    }
    REL(0x24, 1)
    *(void**)((char*)this + 0x14) = vtbl_cContentValidationSummarizer;
    *(void**)((char*)this + 0x10) = vtbl_PaintSystem;
    *(void**)((char*)this + 0x04) = vtbl_cEditorResource;
    *(void**)((char*)this + 0x00) = vtbl_cEditorResource;
}

// @ 0x0057a610
void SP::cAppModeEditorBase_s0057_9e20::AddTorsoToEffectsMask(float x, float y, float z, int)
{
    if (*(int*)((char*)this + 0x150) != 0) {
        RemoveTorsoFromEffectsMask();
        TorsoHolder* h = (TorsoHolder*)((char*)this + 0xf0);
        void* r = (*(void*(__thiscall**)(void*, unsigned, unsigned, int))(**(int**)((char*)this + 0x84) + 0xc))(
            *(void**)((char*)this + 0x84), 0xfeb8102, 0xefeb80ec, 0);
        h->Set(r);
        if (h->p) {
            SceneObjA* so = *(SceneObjA**)((char*)this + 0x150);
            void* scene = so->GetSceneObject(0);
            ((XformStub*)((char*)h->p + 8))->Assign((char*)scene + 8);
            float* dst = (float*)((char*)h->p + 0x4c);   // Vector3 position passed by value
            dst[0] = x;
            dst[1] = y;
            dst[2] = z;
            ModelMgr* mm = ModelManager_s0057_9e20();
            char* obj = (char*)h->p;
            unsigned idx = mm->GetIndex(0x23008d4, 0);
            if (idx < 0x40)
                ((unsigned*)(obj + 0x44))[idx >> 5] |= 1u << (idx & 0x1f);
        }
    }
}

// @ 0x0057a6d0
CheatObject2::CheatObject2()
: b()
{
    vt0 = vtbl_13f585c;
    *(void**)&b = vtbl_13f5858;
    s0c = g_01667bac;
    s10 = g_01667bac;
    s14 = g_01667bae;
}

// @ 0x0057a710
void SP::cAppModeEditorBase_s0057_9e20::SendBehaviorMessage(BMsg* msg)
{
    char* self = (char*)this;
    if (msg != 0) {
        MessageServer_s0057_9e20()->Post(0x30c11c7, msg, 0, 0);
        if (((PropSub*)((PropRoot*)g_sAppProperties)->sub)->flag118 != 0) {
            BMsg* m = new ("Casual", 0, 0, 0, 0) BMsg();
            if (m) m->AddRef();
            char* src = *(char**)(self + 0x98);
            unsigned* dst = (unsigned*)(self + 0x1ec);
            dst[0] = *(unsigned*)(src + 0xc);
            dst[1] = *(unsigned*)(src + 0x10);
            dst[2] = *(unsigned*)(src + 0x14);
            m->data = (unsigned)dst;
            MessageServer_s0057_9e20()->Post(0x4a34c11, m, 0, 0);
            m->Release();
        } else {
            LayoutMgr* lm = GetLayoutManager();
            if (!lm->IsWorldVisible(0x614de4c))
                lm->Method10660(0x614de4c, 1);
        }
        BMsg* m2 = new ("App", 0, 0, 0, 0) BMsg();
        if (m2) m2->AddRef();
        m2->id = 0xe11332;
        m2->data = *(unsigned*)(*(char**)(self + 0x1cc) + 0x1c);
        MessageServer_s0057_9e20()->Post(m2->id, m2, 0, 0);
        char* cur = *(char**)(self + 0x1cc);
        if (cur && *(char**)(cur + 0x94)) {
            V* sub = *(V**)(cur + 0x94);
            if (sub) {
                void* r = (*(void*(__thiscall**)(void*, unsigned))(*(char**)sub + 0xc))(sub, 0x3a3aa3a);
                if (r) ((VecStub*)r)->Fn5942e0();
            }
        }
        m2->Release();
    } else {
        BMsg* m = new ("App", 0, 0, 0, 0) BMsg();
        if (m) m->AddRef();
        m->id = 0xe11332;
        m->data = 0x2ccd1d2;
        MessageServer_s0057_9e20()->Post(m->id, m, 0, 0);
        m->Release();
    }
    *(unsigned*)(self + 0x1d0) = 0;
    *(unsigned*)(self + 0x1d4) = 0;
    *(unsigned*)(self + 0x1d8) = 0;
    V* a = *(V**)(self + 0x1cc);
    if (a) { *(V**)(self + 0x1cc) = 0; a->s2(); }
    V* b = *(V**)(self + 0x4bc);
    if (b) { *(V**)(self + 0x4bc) = 0; b->s2(); }
}

// @ 0x0057a960
Bits128 SP::cAppModeEditorBase_s0057_9e20::GetMask()
{
    Bits128 out;
    int p = *(int*)((char*)this + 0x1cc);
    if (p != 0) {
        out.w[0] = *(unsigned*)((char*)p + 0x24) & ~g_mec;
        out.w[1] = *(unsigned*)((char*)p + 0x28) & ~g_mf0;
        out.w[2] = *(unsigned*)((char*)p + 0x2c) & ~g_mf4;
        out.w[3] = *(unsigned*)((char*)p + 0x30) & ~g_mf8;
    } else {
        out.w[0] = 0;
        out.w[1] = 0;
        out.w[2] = 0;
        out.w[3] = 0;
    }
    return out;
}

// @ 0x0057a9e0
Bits128 SP::cAppModeEditorBase_s0057_9e20::GetDefaultMask()
{
    Bits128 t(g_d40, g_d44, g_d48, g_d4c);
    Bits128 out;
    out = t;
    out.w[0] &= ~g_mec;
    out.w[1] &= ~g_mf0;
    out.w[2] &= ~g_mf4;
    out.w[3] &= ~g_mf8;
    if (*(int*)((char*)this + 0x1cc) != 0) {
        Bits128 m = GetMask();
        out.w[0] &= ~m.w[0];
        out.w[1] &= ~m.w[1];
        out.w[2] &= ~m.w[2];
        out.w[3] &= ~m.w[3];
    }
    return out;
}

// @ 0x0057aaa0
int SP::cAppModeEditorBase_s0057_9e20::GetEditorSaveability()
{
    bool enabled = !g_sAppProperties->GetDescription(0x55d7ca1);
    if (*((char*)this + 0x4b3) == 0 && *((char*)this + 0x4b4) == 0) {
        if (enabled) {
            if (!FUN_004f3d60(*(Bits128*)((char*)this + 0x48), GetMask()))
                return 4;
        }
        return 3;
    }
    if (enabled) {
        if (!FUN_004f3d60(*(Bits128*)((char*)this + 0x48), GetMask()))
            return 2;
        if (!FUN_004f3d60(*(Bits128*)((char*)this + 0x48), GetDefaultMask()))
            return 1;
    }
    return 0;
}

// @ 0x0057ac00
void SP::cAppModeEditorBase_s0057_9e20::BuildPartMask(Bits128* out, void* p3, void* p4, int)
{
    char* self = (char*)this;
    if (g_sAppProperties->GetDescription(0x55d7ca1)) {
        out->w[0] = 0; out->w[1] = 0; out->w[2] = 0; out->w[3] = 0;
        return;
    }
    Bits128 mk = GetMask();
    Bits128 u = BitsOr(mk, GetDefaultMask());
    Bits128 res((Bits128::Uninit()));
    ((PartObj*)p3)->FUN_004bac30(&res, u, 0);
    unsigned kind = *(unsigned*)(self + 0x2a8);
    if (kind == 0x2b978c46 || kind == 0x3d97a8e4) {
        CritList* list = *(CritList**)(self + 0x98);
        int i = 0;
        int n = list->FUN_004accf0();
        bool found = false;
        if (n > 0) {
            do {
                if (((CritItem*)list->FUN_004accb0(i))->FUN_00435b60(0xb00f0fec)) { found = true; break; }
                if (((CritItem*)list->FUN_004accb0(i))->FUN_00435b60(0x11b79301)) { found = true; break; }
                i++;
            } while (i < n);
        }
        if (found)
            res.w[0] &= 0xfffffbff;
        else
            res.w[0] |= 0x400;
    }
    void* props = *(void**)(self + 0x24);
    Key3 k1 = {0, 0, 0};
    if (props != 0 && GetPropertyAsKey(props, 0x7a926123, &k1) && !FUN_004efb20(p3, k1.a, self + 0x48))
        res.w[0] |= 0x40000;
    else
        res.w[0] &= 0xfffbffff;
    props = *(void**)(self + 0x24);
    Key3 k2 = {0, 0, 0};
    if (props != 0 && GetPropertyAsKey(props, 0xf5cbe065, &k2) && !FUN_004ef880(p3, k2.a, self + 0x48))
        res.w[0] |= 0x20;
    else
        res.w[0] &= 0xffffffdf;
    if (*(char*)(self + 0x4b1) != 0 && *(char*)(self + 0x4b2) == 0)
        res.w[0] |= 0x800;
    else
        res.w[0] &= 0xfffff7ff;
    FUN_004edf40(p4, &res);
    out->w[0] = res.w[0];
    out->w[1] = res.w[1];
    out->w[2] = res.w[2];
    out->w[3] = res.w[3];
}

// @ 0x0057ae10
void cAppModeEditorBase::UpdateAnimatedCreature()
{
    if (mAnimCreatureManager != 0) {
        cCreature_s0057_ae10* creature = mAnimCreatureManager->GetCreature(mShadowViewer);
        if (creature != 0) {
            Vector3_s0057_ae10 v;
            Vector3_s0057_ae10* p;
            if (mQueuedAnim == 0) {
                cEditorModel_s0057_ae10* model = mEditorSaveModel;
                p = model->GetVector(&v, 0);
            } else {
                p = &gConst;
            }
            creature->mOffset = Vector3_s0057_ae10(*p);
        }
        if (mAnimatingCreatureActive) {
            if (!mAnimatingCreatureVisible && creature != 0) {
                cCreatureFlags* ff = (cCreatureFlags*)creature->mpFlagsObj;
                uint32_t flags = ff->mFlags;
                bool b14 = (flags >> 14) & 1;
                bool b0 = flags & 1;
                bool b15 = (flags >> 15) & 1;
                bool b18 = (flags >> 18) & 1;
                if (b14 && b0 && b15 && !b18) {
                    mAnimatingCreatureVisible = true;
                    UpdateRenderSettings();
                    FUN_00575790();
                }
            }
        }
        if (!mAnimatingCreatureActive) {
            if (mAnimatingCreatureVisible) {
                mAnimatingCreatureVisible = false;
                UpdateRenderSettings();
                FUN_005757b0();
            }
        }
    }
}

// @ 0x0057af00
namespace SP {
EditorPickResult cAppModeEditorBase_s0057_af00::Pick(float x, float y, bool bBlocksOnly)
{
    EditorPickResult result;
    EditorPickResult blockPick;
    EditorPickResult modelPick;
    float modelDistSq = FLT_MAX_VALUE;
    float blockDistSq = FLT_MAX_VALUE;

    IModelManager_s0057_af00* pModelManager = ModelManager_s0057_af00();
    if (!pModelManager)
        return result;

    float t = 0.0f;
    int hitIndex = -1;
    Vector3_s0057_af00 rayStart;
    Vector3_s0057_af00 rayEnd;
    App_s0057_af00()->GetViewer()->GetCameraRay(x, y, &rayStart, &rayEnd);

    if (!bBlocksOnly) {
        FilterSettings overdrawSettings;
        overdrawSettings.requiredGroupFlags.set(pModelManager->GetGroupFlag(kGroupOverdraw, 0));
        modelPick.mpModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &t, 0, 0, overdrawSettings, &hitIndex, 0);

        cSPEditorHandle_s0057_af00* pOverdrawHandle;
        if (modelPick.mpModel
            && (pOverdrawHandle = interface_cast_inline<cSPEditorHandle_s0057_af00>(modelPick.mpModel->mpOwner)) != 0
            && pOverdrawHandle->GetHandleState() != 1) {
            modelPick.mPosition = Lerp(rayStart, rayEnd, t);
            cSPEditorHandle_s0057_af00* pHandle = interface_cast_inline<cSPEditorHandle_s0057_af00>(modelPick.mpModel->mpOwner);
            if (pHandle->GetHandleType() == kHandleTypeBallConnector) {
                cSPEditorBlock_s0057_af00* pBlock = EditorUtils::GetBlockForBallConnector(modelPick.mpModel, rayStart);
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
            cMWModel_s0057_af00* pRigblockModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &rigblockT, 0, 0, rigblockSettings, &hitIndex, 0);
            float handleT = 0.0f;
            cMWModel_s0057_af00* pHandleModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &handleT, 0, 0, handleSettings, &hitIndex, 0);

            if (pHandleModel) {
                cSPEditorHandle_s0057_af00* pBone;
                if (!pHandleModel->mpOwner
                    || ((pBone = EditorUtils::GetBoneForHandle(pHandleModel->mpOwner)) != 0 && pBone->GetHandleState() != 1)) {
                    if (!pRigblockModel || rigblockT > handleT) {
                        modelPick.mpModel = pHandleModel;
                        t = handleT;
                    } else if (ModelInGroup(pHandleModel, pModelManager->GetGroupFlag(kGroupBallConnector, 0))) {
                        // A ball connector behind its rigblock still wins when it belongs to that rigblock.
                        cSPEditorBlock_s0057_af00* pConnectorBlock = EditorUtils::GetBoneForHandle(pHandleModel->mpOwner)->GetRigblock();
                        cSPEditorBlock_s0057_af00* pRigblock = interface_cast_block(pRigblockModel->mpOwner);
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
        bBallConnectorPicked = interface_cast_inline<cSPEditorHandle_s0057_af00>(modelPick.mpModel->mpOwner)->GetHandleType() == kHandleTypeBallConnector;

    if (!modelPick.mpModel || bBallConnectorPicked) {
        bool bBlockFound = false;
        if (mpSkinManager && mpSkinManager->GetSkin(1) && mbPickVertebrae) {
            FilterSettings vertebraSettings;
            vertebraSettings.requiredGroupFlags.set(ModelManager_s0057_af00()->GetGroupFlag(kGroupVertebra, 0));
            cMWModel_s0057_af00* pVertebra = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &t, 0, 0, vertebraSettings, &blockPick.mHitIndex, 0);
            if (pVertebra && pVertebra->mpOwner) {
                blockPick.mpBlock = interface_cast_block(pVertebra->mpOwner);
                blockPick.mPosition = Lerp(rayStart, rayEnd, t);
                bBlockFound = true;
            }
        }

        if (!blockPick.mpBlock) {
            FilterSettings blockSettings;
            blockSettings.requiredGroupFlags.set(ModelManager_s0057_af00()->GetGroupFlag(kGroupRigblock, 0));
            if (mbPickVertebrae)
                blockSettings.requiredGroupFlags.set(ModelManager_s0057_af00()->GetGroupFlag(kGroupVertebra, 0));
            Vector3_s0057_af00 rigblockHit;
            cMWModel_s0057_af00* pRigblockModel = mpMainModelWorld->FindFirstModelAlongLine(rayStart, rayEnd, &t, &rigblockHit, 0, blockSettings, &blockPick.mHitIndex, 0);

            bool bSkinHitLod1 = false;
            bool bSkinHit = false;
            float skinDistance = -1.0f;
            Vector3_s0057_af00 skinPos;
            Vector3_s0057_af00 skinNormal;
            if (mpSkinManager && !bBallConnectorPicked) {
                Vector3_s0057_af00 dir = SP::normalized_safe(rayEnd - rayStart);
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
                    cSPEditorBlock_s0057_af00* pRigblock = interface_cast_block(pRigblockModel->mpOwner);
                    if (pRigblock->TestAttribute(kAttrIsVertebra)) {
                        cSPEditorBlock_s0057_af00* pSkinBlock = mpSkinManager->GetBlockAtSkinPoint(skinLod, skinPos);
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
        cSPEditorHandle_s0057_af00* pHandle = interface_cast_inline<cSPEditorHandle_s0057_af00>(modelPick.mpModel->mpOwner);
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
                cSPEditorBlock_s0057_af00* pHandleBlock = pHandle->GetRigblock();
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
}  // namespace SP

// @ 0x0057bfb0
namespace SP {
void cAppModeEditorBase_s0057_bfb0::RefreshBlockTray()
{
    sp_vector<EA::AutoRefCount_s0057_bfb0<cSPEditorBlock_s0057_bfb0> > blocks;
    GetEditorBlocks(mEditorSaveModel->mBlocks, blocks);

    int maxCount = 0;
    cPropertyList_s0057_bfb0* propList = mpPropList;
    Property_s0057_bfb0* prop;
    if (propList && propList->GetProperty(0x0664EA09, prop) && prop->mType == 9)
        maxCount = *prop->GetInt();

    size_t count = blocks.size();
    for (size_t i = 0; i < count; ++i) {
        EA::AutoRefCount_s0057_bfb0<cSPEditorBlock_s0057_bfb0> block = blocks[i];
        if (!m2f6 || IsBlockAllowed(block))
            mpBlockTray->AddBlock(block);
    }

    if (mpBlockTray->GetCount(0) < maxCount)
        mpBlockTray->SetCount(0, maxCount);
}
}  // namespace SP

// @ 0x0057c0e0
namespace SP {
void cAppModeEditorBase_s0057_bfb0::ProcessPendingLaunch()
{
    if (mPendingLaunch != 1 || m1a0 != 0 || m1a4 != 0 || mTransitionState != 0 || !mLaunchState)
        return;

    if (!mLaunchState->mbActive && mLaunchData && mLaunchData->mParent) {
        EA::AutoRefCountX<Editor::cEditorLaunchData_s0057_bfb0> parent(mLaunchData->mParent);
        mLaunchData = parent;
        if (mLaunchData->mModelKey.instanceID == 0)
            mLaunchData->mModelKey = mLaunchState->mKey;
        SetCurrentConfig(mLaunchData->mConfig, mLaunchData->mModelKey);
    } else {
        RelaunchFrom(mLaunchState);
    }
    mPendingLaunch = 0;
}
}  // namespace SP

// @ 0x0057c1e0
namespace SP {
void cAppModeEditorBase_s0057_bfb0::CreateLaunchState()
{
    if (mLaunchData) {
        mLaunchState = new ("Editor", 0, 0, 0, 0) cEditorLaunchState();
        mLaunchState->m0c = mLaunchData->m90;
        mLaunchState->m10 = mLaunchData->m94;
        mLaunchState->mKey = mLaunchData->mModelKey;
        mLaunchState->m14 = mEditorSaveModel->m58;
        mLaunchState->mbActive = true;
        mLaunchState->m45 = mLaunchData->m65;
    }
}
}  // namespace SP

// @ 0x0057c2f0
namespace SP {
void cAppModeEditorBase_s0057_bfb0::SetLocalState(cSPEditorLocalState* state)
{
    EA::Messaging::MessageData<6> msg;
    if (!state)
        return;

    mpBlockTray->SetCount(0, state->mBudget);
    if (mDevUI) {
        mDevUI->SetMode(state->mState);
        switch (state->mState) {
        case 0: mDevUI->SetSelected(0xF019C2E7, true, true); break;
        case 1: mDevUI->SetSelected(0xF019C2F3, true, true); break;
        case 2: mDevUI->SetSelected(0x70218642, true, true); break;
        }
    }
    if (mpBakeManager && !m2f1 && state->mThemeID)
        mpBakeManager->Bake(state->mThemeID);

    mIsPainted = state->mIsPainted;
    mIsModelDirty = state->mIsModelDirty;

    if (state->mPaintLikeThisKey.instanceID) {
        msg.mId = 0;
        msg.mData[0].mUint32 = state->mPaintLikeThisKey.groupID;
        msg.mData[1].mUint32 = state->mPaintLikeThisKey.instanceID;
        msg.mData[2].mUint32 = state->mPaintLikeThisKey.typeID;
        msg.mData[3].mUint32 = state->mPaintLikeThisGroupId;
        msg.mData[4].mUint32 = state->mPaintLikeThisItemId;
        MessageServer_s0057_bfb0()->MessageSend(0x057A4BC9, &msg, 0);
    }
    SendEditorStateChanged();
}
}  // namespace SP

// @ 0x0057c440
namespace SP {
__forceinline void SendEditorStateChanged()
{
    UI::BehaviorMessage msg(0x05090434);
    MessageServer_s0057_bfb0()->MessageSend(msg.mId, &msg, 0);
}
}  // namespace SP

// @ 0x0057c4b0
namespace SP {
cPaletteCategory::~cPaletteCategory()
{
}
}  // namespace SP

// @ 0x0057c530
namespace SP {
void cAppModeEditorBase_s0057_bfb0::SetTrayState(int index, bool value)
{
    mpTrayStates[index] = value;
    int row = GetCurrentTrayRow();
    if (row < 6 && mLaunchData && mLaunchData->m6e) {
        if (index == 6)
            mTrayActive[row] = mTrayRows[row].mpStates[6];
        mTrayRows[row].mpStates[index] = value;
    }
}
}  // namespace SP

// @ 0x0057c590
namespace SP {
bool cAppModeEditorBase_s0057_bfb0::ExportPaintTheme(bool showDialog)
{
    if (showDialog) {
        if (mDevUI)
            mDevUI->ShowPaintThemeExport();
        return true;
    }

    cSPEditorSkin* skin = mSaveLoadFactory ? mSaveLoadFactory->GetSkin(true) : 0;
    if (!mEditorSaveModel || !skin)
        return false;

    eastl::string16_s0057_bfb0 path;
    cPaintThemeSource* source = GetPaintThemeSource();
    if (source) {
        source->GetPath(0x2B978C46, &path);
        if (path.empty())
            return false;

        wchar_t fileName[260];
        EA::IO::SplitPath(mEditorSaveModel->GetFilePath(), 0, 0, fileName, 0, 4);
        const wchar_t* pathStr = path.c_str();

        bool sameTopology;
        if (skin->mpMesh &&
            (int)(skin->mVertsEnd - skin->mVertsBegin) / 20 == (int)(skin->mpMesh->mpEnd - skin->mpMesh->mpBegin) / 12)
            sameTopology = true;
        else
            sameTopology = false;

        if (mSaveLoadFactory->HasPaintData() && sameTopology) {
            mSaveLoadFactory->ApplyPaintTheme(pathStr, fileName);
        } else {
            mSaveLoadFactory->Update(0, 1, UpdateFlags());
            skin->Rebuild0();
            skin->Rebuild1();
            skin->Rebuild2();
        }

        return EditorUtils::ExportToXMFAndBlocks(mEditorSaveModel, mSaveLoadFactory ? mSaveLoadFactory->GetSkin(true) : 0, pathStr);
    }
    return false;
}
}  // namespace SP

// @ 0x0057e160
void cAppModeEditorBase_s0057_d710::SetTorsoIsSelected(bool selected)
{
    if (selected == mTorsoSelected)
        return;
    if (selected)
        AddTorsoToEffectsMask(gTorsoColor);
    else
        RemoveTorsoFromEffectsMask();
    mTorsoSelected = selected;
}

// @ 0x0057e480
void cEditorBase::UpdateIdleAnimations(float x, float y, uint32_t dt)
{
    if (At<int>(At<void*>(gAppProperties, 0x3c), 0xdc) == 0)
        return;
    bool bHasSkin = false;
    if (At<int>(this, 0x360) && At<SkinMgr*>(this, 0x150) && At<SkinMgr*>(this, 0x150)->GetSkin(1))
        bHasSkin = true;
    if (AssetBrowser()->mFlag)
        return;
    if (SporeGuide()->mFlag)
        return;
    int queued = At<int>(this, 0x31c);
    if (queued != 0 && queued != 1)
        return;
    bool bAnyState = false;
    bool bIdle = false;
    if (bHasSkin) {
        if (At<char>(this, 0xe9) != 0 || At<char>(this, 0xe8) != 0)
            bAnyState = true;
    }
    if (At<int>(this, 0x148) == 0 && At<int>(this, 0xcc) == 0 && At<int>(this, 0xe4) == 0 &&
        At<int>(this, 0xd4) == 0 && !bAnyState && (queued != 0 || !IsMousedOverModel(x, y)))
        bIdle = true;
    if (At<int>(this, 0x31c) == 1 && At<PaletteUI*>(this, 0x3c4) && At<PaletteUI*>(this, 0x3c4)->IsPaintByNumber())
        bIdle = false;
    if (At<char>(this, 0x385) == 0) {
        if (!bIdle)
            return;
        float t = (float)dt + At<float>(this, 0x68);
        At<float>(this, 0x68) = t;
        if (!(At<float>(this, 0x6c) < t))
            return;
        EventInfo* raw = new ("Editor", 0, 0, 0, 0) EventInfo();
        EventRef info(raw);
        EventInfo* ev = info.p;
        ev->MessagePost(0x65d3b051, 0, At<void*>(this, 0x98), 0, 0, 0.0f, 1, -1, 1.0f);
        if (!HasSkin() && !At<EditorModel*>(this, 0x98)->F4acfd0() && At<EditorModel*>(this, 0x98)) {
            At<EditorModel*>(this, 0x98)->F4ad1a0();
            At<char>(this, 0x385) = 1;
        }
        if (ev)
            ev->Release();
        return;
    }
    if (HasSkin()) {
        if (At<AnimMgr*>(this, 0x360)->IsPlayingAnimation(At<int>(this, 0x364)))
            return;
        if (At<int>(this, 0x380) != 0)
            return;
        float cur = At<float>(this, 0x70);
        if (cur > 0.0f) {
            float t = cur - (float)dt;
            At<float>(this, 0x70) = t;
            if (t > 0.0f)
                return;
            At<float>(this, 0x70) = 0.0f;
            F57e340(0);
            return;
        }
        if (!bIdle) {
            F573970();
            return;
        }
        EventInfo* raw = new ("Editor", 0, 0, 0, 0) EventInfo();
        EventRef info(raw);
        EventInfo* ev = info.p;
        ev->MessagePost(0x65d3b051, 0, At<void*>(this, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
        if (ev)
            ev->Release();
        return;
    }
    if (bIdle)
        return;
    if (At<EditorModel*>(this, 0x98)->F4acfd0()) {
        SomeLoader();
        F5724a0();
    }
}

// @ 0x0057e790
void cEditorBase::SetSelectedBlock(Block* b, uint32_t p)
{
    if (b) {
        if (At<char>(this, 0xe8))
            At<char>(this, 0xe8) = 0;
        if (At<char>(this, 0xe9)) {
            RemoveTorsoFromEffectsMask();
            At<char>(this, 0xe9) = 0;
        }
        if (At<char>(this, 0x470) == 0)
            b->F43ce40();
    }
    BlockRef& ref = At<BlockRef>(this, 0xd4);
    Block* old = ref.p;
    if (b != old) {
        if (old && !old->FlagBit(1)) {
            if (At<Handle*>(this, 0xe4) && At<Handle*>(this, 0xe4)->GetRigblock() == old)
                SetRolloverHandle(0, 1);
            ref.p->F43a9a0(0, p);
        }
        if (b) {
            if (b->FlagBit(10) && b->HasAnyBlockFlag())
                return;
            ref.Set(b);
            if (!ref.p)
                return;
            ref.p->F43a9a0(1, 1);
            if (ref.p != At<Block*>(this, 0xd8)) {
                ref.p->F43c710();
                return;
            }
            ref.p->F43cad0();
            return;
        } else {
            Block* cur = ref.p;
            if (!cur)
                return;
            ref.p = 0;
            cur->Release();
            return;
        }
    }
    if (old)
        old->F43cad0();
}

// @ 0x0057e8a0
void cEditorBase::UpdateBaker()
{
    if (!At<void*>(this, 0x1cc))
        return;
    BakerData* o = new ("Editor", 0, 0, 0, 0) BakerData();
    BakerData* old = At<BakerData*>(this, 0x4bc);
    if (o != old) {
        if (o) o->AddRef();
        At<BakerData*>(this, 0x4bc) = o;
        if (old) old->Release();
    }
    At<BakerData*>(this, 0x4bc)->mField0c = At<LaunchData*>(this, 0x1cc)->m90;
    BakerData* b = At<BakerData*>(this, 0x4bc);
    RC0* src = At<LaunchData*>(this, 0x1cc)->m94;
    RC0*& ref = b->mRef10;
    RC0* cur = ref;
    if (src != cur) {
        if (src) src->AddRef();
        ref = src;
        if (cur) cur->Release();
    }
    At<BakerData*>(this, 0x4bc)->mByte45 = At<LaunchData*>(this, 0x1cc)->m65;
    EditorModel* m = At<EditorModel*>(this, 0x98);
    BakerData* d = At<BakerData*>(this, 0x4bc);
    d->mKey = m->mKey;
    At<BakerData*>(this, 0x4bc)->mField14 = At<EditorModel*>(this, 0x98)->m58;
    At<BakerData*>(this, 0x4bc)->mByte44 = 0;
    BakerData* d1 = At<BakerData*>(this, 0x4bc);
    const wchar_t* n = At<INameProv>(this, 0xc).GetName();
    const wchar_t* e = n;
    while (*e) ++e;
    d1->mName.Assign(n, n + (e - n));
    BakerData* d2 = At<BakerData*>(this, 0x4bc);
    d2->mField34 = (uint32_t)At<IUnk*>(this, 0x434)->V1(0);
    At<BakerData*>(this, 0x4bc)->mField38 = At<uint32_t>(this, 0x34c);
    BakerData* d3 = At<BakerData*>(this, 0x4bc);
    d3->mField3c = (uint32_t)At<EditorUI*>(this, 0x78)->F5dc2b0();
    BakerData* d4 = At<BakerData*>(this, 0x4bc);
    d4->mField40 = (uint32_t)At<EditorUI*>(this, 0x78)->F5dc2c0();
}

// @ 0x0057ea30
void cEditorBase::SaveMetadata()
{
    IResMan* rm = GetManager();
    EditorModel* model = At<EditorModel*>(this, 0x98);
    ResKey key;
    key = model->mKey;
    key.type = 0x30bdee3;
    ResHolder out;
    if (rm->GetResource(&key, &out.p, 0, 0, 0, 0)) {
        IMeta* meta;
        if (out.p == 0)
            meta = 0;
        else
            meta = QueryAddRef(out.p);
        IModel* mdl = At<IModel*>(this, 0x98);
        const wchar_t* nm = At<INameProv>(this, 0xc).GetName5();
        meta->Fill(mdl->V1(), mdl->V3(), nm);
        int area = GetSaveArea(At<int>(this, 0x2ac));
        GetManager()->SaveResource(meta, 0, area, 0, 0);
        Thumb* t = GetThumb();
        if (t)
            t->UpdateExportThumb(&At<EditorModel*>(this, 0x98)->mKey);
        if (meta)
            meta->Release();
    }
    gTokTrans->SetOldModelName(At<INameProv>(this, 0xc).GetName());
    UpdateBaker();
    At<char>(this, 0x4b4) = 0;
    At<char>(this, 0x4b2) = 1;
    IModel* mdl2 = At<IModel*>(this, 0x98);
    int undoCount = At<int*>(this, 0x178)[-1];
    int modelType = (int)mdl2->V1();
    At<Mask16>(this, 0x48) = BuildPartMask(undoCount, modelType, 1);
    At<EditorUI*>(this, 0x78)->UpdateUIBasedOnModelSaveability();
    if (At<EditorUI*>(this, 0x78)->F5dc450() != 1) {
        At<EditorUI*>(this, 0x78)->F5dd090(1);
        At<EditorUI*>(this, 0x78)->EnableBasicEditorButtons(1, 1);
    }
    GetHints(1, 1)->F67c420();
}

// @ 0x0057ebf0
void cEditorBase::BakerInit()
{
    BakerMsg msg1;
    BakerMsg msg2;
    ResKey k;
    switch (At<int>(this, 0x388)) {
    case 3:
        At<int>(this, 0x1a8) = 2;
        GetMessageServer()->PostMessage4(0x153c326, 0, 0, 0);
        return;
    case 2:
        if (At<void*>(this, 0x1cc)) {
            UpdateBaker();
            EditorModel* m = At<EditorModel*>(this, 0x98);
            if (m->mKey.type == 0x3d97a8e4) {
                msg1.id = 0x2ea8fb98;
                msg1.a = 1;
                msg1.b = 4;
                GetBakerSvc()->Post(&At<EditorModel*>(this, 0x98)->mKey, &msg1);
                return;
            }
            if (m->mKey.type == 0x2b978c46) {
                k.instance = m->mKey.instance;
                k.type = m->mKey.type;
                k.group = m->mKey.group;
                InvalidEditorModelKey(&k, 0);
                msg2.id = 0x2ea8fb98;
                msg2.a = 1;
                msg2.b = 4;
                GetBakerSvc()->Post(&k, &msg2);
            }
        }
        break;
    }
}

// @ 0x0057ed00
void SP::cAppModeEditorBase::SetName(wchar_t const * name)
{
    const wchar_t* e = name;
    while (*e) ++e;
    At<WStr16>(static_cast<SP::cISPEditorNameProvider *>(this), 0xa4).Assign(name, name + (e - name));
    At<char>(static_cast<SP::cISPEditorNameProvider *>(this), 0x4a8) = 1;
    At<SP::cSPEditorUI*>(static_cast<SP::cISPEditorNameProvider *>(this), 0x6c)->UpdateUIBasedOnModelSaveability();
    SetNameMsg m(((char*)static_cast<SP::cISPEditorNameProvider *>(this) - 0xc) ? (void*)static_cast<SP::cISPEditorNameProvider *>(this) : 0, At<WStr16>(static_cast<SP::cISPEditorNameProvider *>(this), 0xa4).mpBegin);
    GetMessageServer()->PostMessage(0x73127e6, &m, 0);
}

// @ 0x0057ed80
void* cUnkEd80::Init(void* p, void* unused)
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    FUN_0057cc10(p);
    return this;
}

// @ 0x0057edf0
void* cVec16::EraseAfter(void* pos)
{
    char* src = (char*)pos + 4;
    if (src < (char*)mpEnd)
        DoInsertValue(pos, src, (int)((char*)mpEnd - src));
    mpEnd = (char*)mpEnd - 4;
    return pos;
}

// @ 0x0057ee20
namespace eastl {
template <> vector_s0057_e480<Rec18>& vector_s0057_e480<Rec18>::operator=(const vector_s0057_e480<Rec18>& x)
{
    if (&x != this) {
        const uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
        if (n > (uint32_t)(mpCapacity - mpBegin)) {
            Rec18* const pNewData = DoRealloc(n, x.mpBegin, x.mpEnd);
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
            mpCapacity = pNewData + n;
            mpBegin = pNewData;
            mpEnd = mpBegin + n;
        } else if (n > (uint32_t)(mpEnd - mpBegin)) {
            const uint32_t nSize = (uint32_t)(mpEnd - mpBegin);
            copy_ool(x.mpBegin, x.mpBegin + nSize, mpBegin);
            uninitialized_copy_ptr((const Rec18*)(x.mpBegin + (uint32_t)(mpEnd - mpBegin)), (const Rec18*)x.mpEnd, mpEnd);
            mpEnd = mpBegin + n;
        } else {
            copy_ool(x.mpBegin, x.mpEnd, mpBegin);
            mpEnd = mpBegin + n;
        }
    }
    return *this;
}
}  // namespace eastl

// @ 0x0057efa0
bool __cdecl PopulateScriptList(ListUI* ui, const char* name, CharVec* v)
{
    bool ok = true;
    if (v->mpBegin == v->mpEnd)
        return ok;
    const eastl::basic_string_s0057_e480<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string_s0057_e480<wchar_t>());
    ui->BeginList(s.mpBegin == s.mpEnd ? L"list" : s.mpBegin);
    char* const end = v->mpEnd;
    for (char* it = v->mpBegin; it != end; ++it)
        ok = ok && UpdateEffectsAndObjectsStats(ui, 0, it, L"bool");
    ui->EndList(s.mpBegin == s.mpEnd ? L"list" : s.mpBegin);
    return ok;
}

// @ 0x0057f0f0
namespace eastl {
template <> void vector_s0057_e480<Rec30>::DoInsertValue(Rec30* position, const Rec30& value)
{
    if (mpEnd != mpCapacity) {
        const Rec30* pValue = &value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        ::new (mpEnd) Rec30(*(mpEnd - 1));
        copy_backward_impl(position, mpEnd - 1, mpEnd);
        *position = *pValue;
        ++mpEnd;
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nNewSize = GetNewCapacity(nPrevSize);
        Rec30* const pNewData = DoAllocate(nNewSize);
        Rec30* pNewEnd = uninitialized_copy_ool(mpBegin, position, pNewData);
        ::new (pNewEnd) Rec30(value);
        pNewEnd = uninitialized_copy_ool(position, mpEnd, pNewEnd + 1);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
}  // namespace eastl

// @ 0x0057f220
namespace eastl {
template <> void vector_s0057_e480<RefElem>::DoInsertValues(RefElem* position, uint32_t n, const RefElem& value)
{
    if (n <= (uint32_t)(mpCapacity - mpEnd)) {
        if (n > 0) {
            const RefElem temp(value);
            const uint32_t nExtra = (uint32_t)(mpEnd - position);
            RefElem* const pEnd = mpEnd;
            if (n < nExtra) {
                uninitialized_copy_ptr(mpEnd - n, mpEnd, mpEnd);
                mpEnd += n;
                copy_backward_ool(position, pEnd - n, pEnd);
                fill_ool(position, position + n, temp);
            } else {
                uninitialized_fill_n_ptr(mpEnd, n - nExtra, temp);
                mpEnd += n - nExtra;
                uninitialized_copy_ptr(position, pEnd, mpEnd);
                mpEnd += nExtra;
                fill_ool(position, pEnd, temp);
            }
        }
    } else {
        const uint32_t nPrevSize = (uint32_t)(mpEnd - mpBegin);
        const uint32_t nGrowSize = GetNewCapacity(nPrevSize);
        const uint32_t nNewSize = nGrowSize > (nPrevSize + n) ? nGrowSize : (nPrevSize + n);
        RefElem* const pNewData = DoAllocate(nNewSize);
        RefElem* pNewEnd = (RefElem*)MoveMem(pNewData, mpBegin, (uint32_t)((char*)position - (char*)mpBegin)) + (position - mpBegin);
        uninitialized_fill_n_ptr(pNewEnd, n, value);
        pNewEnd = (RefElem*)MoveMem(pNewEnd + n, position, (uint32_t)((char*)mpEnd - (char*)position)) + (mpEnd - position);
        DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
}
}  // namespace eastl

// @ 0x0057f420
void cUnkF420::FUN_0057f420(void* args)
{
}

// @ 0x0057f6c0
namespace SP {
void cAppModeEditorBase_s0057_f6c0::SaveModel(const ResourceKey_s0057_f6c0& key, int saveMode)
{
    if (mpEditorModel) {
        mpEditorModel->FUN_004ad330();
        mpEditorModel = 0;
    }

    intrusive_ptr<cEditorModelStream> pStream = new ("Editor", 0, 0, 0, 0) cEditorModelStream();
    if (!mpEditorSaveModel->SaveResource(pStream))
        return;

    mb4b3 = false;
    mb4b4 = false;
    mb4b2 = true;
    mModelValidity = BuildPartMask(pStream, mpEditorSaveModel->GetName(), true);
    mpUI->UpdateUIBasedOnModelSaveability();
    mModelSaveValidity = BuildPartMask(pStream, mpEditorSaveModel->GetName(), false);

    mpEditorModel = new ("Editor", 0, 0, 0, 0) cSPEditorModel_s0057_f6c0();
    mpEditorModel->LoadFromBinary(pStream);
    mpEditorModel->FUN_004ae260(mpSaveModelWorld, 0, 0, true);
    mpEditorModel->SetName(mpEditorSaveModel->GetName());
    mpEditorModel->SetDescription(mpEditorSaveModel->GetDescription());
    mpEditorModel->mKey = key;
    mpEditorSaveModel->mKey = key;

    eastl::sp_vector_s0057_f6c0<uint32_t> blockData;
    mpEditorSaveModel->FUN_004ad6f0(blockData);
    mpEditorModel->FUN_004ada40(blockData);

    if (mIsCreatureEditor) {
        if (mpPainter) {
            mpPainter->Shutdown();
            mpPainter = 0;
        }
        mpPainter = new ("Editor", 0, 0, 0, 0) cEditorPainter();
        if (mpSkinManager) {
            bool bUpToDate = mpSkinManager->IsSkinUpToDate();
            mpPainter->Init(this, mpEditorModel, mpSaveModelWorld);
            float rangeMin = kPainterRangeMin;
            float rangeMax = kPainterRangeMax;
            GetFloatProperty(mpConfigProperties, 0x711306cd, rangeMin);
            GetFloatProperty(mpConfigProperties, 0x711306ce, rangeMax);
            mpPainter->SetRange(rangeMin, rangeMax);
            mpPainter->SetUpToDate(bUpToDate);
        }
    } else {
        FUN_004b7660(mpEditorModel);
    }

    const wchar_t* pName = mpEditorSaveModel->GetFileName();
    Resource::IResourceManager* pResourceManager = Resource::GetManager_s0057_f6c0();
    Resource::Database* pSaveArea = SP::GetSaveArea(mSaveAreaID);
    const wchar_t* pDir = pSaveArea->GetLocation();

    if (saveMode == 0) {
        Resource::StandardFileFilter filter(key.instanceID, key.groupID, 0xffffffff, 0xdfff0000);
        pResourceManager->FlushCache(0, &filter);
        eastl::sp_vector_s0057_f6c0<ResourceKey_s0057_f6c0> keys;
        eastl::sp_vector_s0057_f6c0<Resource::Database*> databases;
        pResourceManager->GetRecordKeyList(keys, &filter, &databases);
        int count = keys.size();
        for (int i = 0; i < count; ++i) {
            Resource::Database* pDatabase = databases[i];
            if (SP::IsSaveArea(pDatabase))
                pDatabase->DeleteRecord(keys[i]);
            FUN_006ad030(keys[i]);
        }
    }

    ResourceKey_s0057_f6c0 nameKey = key;
    const uint32_t groupID = key.groupID;
    eastl::wstring fileName;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x1a99b06b;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x0f43029a;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x2f7d0004;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.typeID = 0x030bdee3;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.groupID = (groupID & 0xffffff01) | 1;
    nameKey.typeID = 0x2f7d0004;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());
    nameKey.groupID = (groupID & 0xffffe5ff) | 0xe500;
    nameKey.typeID = 0x00b1b104;
    Resource::CreateNameFromKey(&nameKey, &fileName, pResourceManager, pSaveArea, pName);
    pResourceManager->SetKeyName(nameKey, fileName.c_str());

    wchar_t name[256];
    switch (saveMode) {
    case 2:
        if (mpSkinManager && mpUI) {
            if (mEditorMode != 1) {
                mpUI->ShowGeneralMessage(L"You must switch to paint mode before exporting Z");
                break;
            }
            cSkinObject_s0057_f6c0* pSkin = mpSkinManager->GetSkin(1);
            bool bMeshValid = pSkin->IsMeshValid();
            if (!mpSkinManager->IsSkinUpToDate() || !bMeshValid)
                RebuildSkin(pSkin);
            EA::IO::SplitPath(mpEditorModel->GetName(), 0, 0, name, 0, 4);
            {
                eastl::wstring path;
                path.sprintf(L"%ls/%ls.zpr", pDir, name);
                FUN_0046eae0(pSkin, path.c_str());
            }
        } else {
            cEditorRequestHandler* pHandler = GetEditorRequestHandler();
            if (!pHandler)
                break;
            cEditorRequest request;
            request.mB = 4;
            request.mA = 0x24;
            request.mID = 0x2ea8fb98;
            pHandler->Request(key, &request);
        }
        if (mpUI)
            mpUI->ShowGeneralMessage(L"Model exported");
        break;

    case 1: {
        EA::IO::SplitPath(mpEditorModel->GetFileName(), 0, 0, name, 0, 4);
        eastl::wstring path;
        path.sprintf(L"%ls/%ls.xsf", pDir, name);
        cSkinObject_s0057_f6c0* pSkin = GetSkin();
        if (pSkin) {
            bool bMeshValid = pSkin->IsMeshValid();
            if (mpSkinManager->IsSkinUpToDate() && bMeshValid)
                mpSkinManager->ExportSkin(pDir, name);
            else
                RebuildSkin(pSkin);
            FUN_004647b0(mpEditorModel, GetSkin(), pDir);
            SP::EditorUtils::ExportToXMFAndBlocks(mpEditorModel, GetSkin(), pDir);
            if (mpUI) {
                eastl::wstring message;
                message.sprintf(L"Model saved to %ls", path);
                mpUI->ShowGeneralMessage(message.c_str());
            }
            cEditorSavedMessage* pMsg = new ("cAppModeEditorBase::Save", 0, 0, 0, 0) cEditorSavedMessage();
            if (pMsg)
                pMsg->AddRef();
            pMsg->mID = 0x5b053b5;
            SetMessageString(pMsg, 0, pDir);
            SetMessageString(pMsg, 1, name);
            SP::MessageServer_s0057_f6c0()->PostMSG(pMsg->mID, pMsg, 0);
            pMsg->Release();
        } else {
            cEditorRequestHandler* pHandler = GetEditorRequestHandler();
            if (pHandler) {
                cEditorRequest request;
                request.mA = 0x28;
                request.mB = 4;
                request.mID = 0x2ea8fb98;
                pHandler->Request(key, &request);
            }
        }
        break;
    }

    case 0: {
        mnEC = 0;
        if (mbE8)
            mbE8 = false;
        if (mbTorsoInEffectsMask) {
            RemoveTorsoFromEffectsMask();
            mbTorsoInEffectsMask = false;
        }
        cSPEditorBlock_s0057_f6c0* pBlock = mpSelectedBlock;
        if (pBlock) {
            if (!pBlock->IsLocked()) {
                if (mpRolloverHandle && mpRolloverHandle->GetRigblock() == pBlock)
                    SetRolloverHandle(0, true);
                mpSelectedBlock->FUN_0043a9a0(0, 1);
            }
            mpSelectedBlock = 0;
        }
        FUN_00573c00(0, -1);
        mn38C = 1;
        break;
    }
    }
}
}  // namespace SP

// @ 0x005802f0
void FUN_005802f0()
{}

// @ 0x005805e0
bool cAppModeEditorBase_s0058_02f0::GetEditorName(string16_s0058_02f0* out)
{
    if (mPropList) {
        typedef bool (__thiscall *HasFn)(void*, uint32_t);
        HasFn has = *(HasFn*)(*(char**)mPropList + 0x1c);
        if (has(mPropList, 0x703e542f)) {
            cString s;
            s.Init();
            GetPropertyAsText(mPropList, 0x703e542f, &s);
            WStr_Format(out, L"", s.GetValue());
            s.c_str();
            return true;
        }
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    return false;
}

// @ 0x00580670
bool cAppModeEditorBase_s0058_02f0::GetDefaultModelName(string16_s0058_02f0* out)
{
    if (mPropList) {
        typedef bool (__thiscall *HasFn)(void*, uint32_t);
        HasFn has = *(HasFn*)(*(char**)mPropList + 0x1c);
        if (has(mPropList, 0x4d92f82)) {
            cString s;
            s.Init();
            GetPropertyAsText(mPropList, 0x4d92f82, &s);
            WStr_Format(out, L"", s.GetValue());
            void TrimString(string16_s0058_02f0*);   // not used; placeholder
            out->mpBegin; // keep layout
            s.c_str();
            return true;
        }
    }
    if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    return false;
}

// @ 0x00580700
void FUN_00580700()
{}

// @ 0x005809a0
void FUN_005809a0()
{}

// @ 0x00580c10
void FUN_00580c10(wchar_t* out)
{
    void* auth = FUN_00607a60();
    typedef bool (__thiscall *IsOfflineFn)(void*);
    IsOfflineFn isOffline = *(IsOfflineFn*)(*(char**)auth + 0x24);
    if (isOffline(auth)) {
        wcsncpy(out, L"EditorOfflineUser", 0x100);
        return;
    }
    string16_s0058_02f0 name;
    name.mpBegin = (wchar_t*)0x01667bac; name.mpEnd = (wchar_t*)0x01667bac; name.mpCapacity = (wchar_t*)0x01667bae;
    typedef void* (__thiscall *GetNameFn)(void*);
    GetNameFn getName = *(GetNameFn*)(*(char**)auth + 0x30);
    WStr_Format(&name, L"EditorUser_%hs", *(int*)getName(auth));
    EA_IO_MakeFileNameValid(name.mpBegin, out, 4);
    if (((name.mpCapacity - name.mpBegin) & ~1) > 2 && name.mpBegin)
        eastl_deallocate(name.mpBegin);
}

// @ 0x00580cb0
void FUN_00580cb0()
{}

// @ 0x00580df0
void FUN_00580df0()
{}

// @ 0x005810a0
void cBoolVec::EraseAll()
{
    void* begin = mpBegin;
    void* end = mpEnd;
    DoInsertValue(begin, end, 0);
    mpEnd = (char*)mpEnd + (((int)end - (int)begin) >> 2) * -4;
}

// @ 0x005810d0
void FUN_005810d0()
{}

// @ 0x005812b0
void FUN_005812b0()
{}

// @ 0x005820a0
void FUN_005820a0()
{}

// @ 0x00582250
namespace SP {
bool cAppModeEditorBase_s0058_2250::OnBlockWheel(cSPEditorBlock_s0058_2250* block, cSPEditorHandle_s0058_2250* handle, int wheelDelta)
{
    float delta = (float)wheelDelta * (1.0f / 120.0f);
    bool handled = false;
    float soundValue = 0.0f;

    if (block && !block->IsLocked()) {
        float amount = delta * 0.1f;
        handled = true;
        if (block->IsScalable()) {
            if (!IsManipulatorEnabled(0x7ad67439))
                return false;
            amount *= 0.5f;
            ScaleBlock(block, amount);
            Vector3_s0058_2250 center = GetBlockCenter(block);
            float radius = GetBlockRadius(block);

            intrusive_ptr_s0058_2250<cSPEditorBlock_s0058_2250> p = GetScaleParent(block);
            float falloff = 1.0f;
            for (int i = 0; p && i < 5; ++i) {
                float dx = p->mPosition.x - center.x;
                float dy = p->mPosition.y - center.y;
                float dz = p->mPosition.z - center.z;
                float distSq = dy * dy + dz * dz + dx * dx;
                float dist = sqrtf(distSq);
                float f;
                if (radius > dist)
                    f = dist / radius * (0.3f - 1.0f) + 1.0f;
                else
                    f = radius / dist * 0.3f;
                if ((amount > 0.0f) != (block->mScale > p->mScale))
                    f *= 0.4f;
                falloff *= 0.7f;
                if (f > falloff)
                    f = falloff;
                if (f < 0.1f)
                    break;
                ScaleBlock(p.get(), f * amount);
                falloff = f;
                p.reset(GetScaleParent(p.get()));
            }

            p = block->mpParent;
            falloff = 1.0f;
            for (int i = 0; p && i < 5; ++i) {
                float dx = p->mPosition.x - center.x;
                float dy = p->mPosition.y - center.y;
                float dz = p->mPosition.z - center.z;
                float distSq = dx * dx + dy * dy + dz * dz;
                float dist = sqrtf(distSq);
                float f;
                if (radius > dist)
                    f = dist / radius * (0.3f - 1.0f) + 1.0f;
                else
                    f = radius / dist * 0.3f;
                if ((amount > 0.0f) != (block->mScale > p->mScale))
                    f *= 0.4f;
                falloff *= 0.7f;
                if (f > falloff)
                    f = falloff;
                if (f < 0.1f)
                    break;
                ScaleBlock(p.get(), f * amount);
                falloff = f;
                p.reset(p->mpParent);
            }

            TorsoFlags torso;
            torso.a = false;
            torso.b = false;
            mpSkinManager->UpdateTorso(torso, 0);

            vector<cSPEditorBlock_s0058_2250*> blocks;
            for (cSPEditorBlock_s0058_2250* b = mpSkeleton->mpFirstBlock; b; b = b->mpParent) {
                int n = b->mChildren.size();
                for (int j = 0; j < n; ++j) {
                    cSPEditorBlock_s0058_2250* child = b->mChildren[j];
                    if (!child->IsScalable())
                        blocks.push_back(child);
                }
            }

            bool keepZ = mpEditorModel->mModelType != 0xdfad9f51;
            bool flat = mpEditorModel->mModelType == 0xdfad9f51;
            int count = blocks.size();
            for (int i = 0; i < count; ++i) {
                cSPEditorBlock_s0058_2250* sym = FindClosestSymmetry(blocks[i]->mPosition, mpSkeleton->mpSymmetryRoot);
                Vector3_s0058_2250 symPos = GetBlockCenter(sym);
                cSPEditorBlock_s0058_2250* cur = blocks[i];
                float dx = cur->mPosition.x - symPos.x;
                float dy = cur->mPosition.y - symPos.y;
                float dz = cur->mPosition.z - symPos.z;
                if (flat)
                    dz = 0.0f;
                float len = sqrtf(dx * dx + dy * dy + dz * dz + 1e-8f);
                float invLen = 1.0f / len;
                PlaceSymmetric(cur, symPos, Vector3_s0058_2250(invLen * dx, invLen * dy, dz * invLen),
                               mpSkinManager, keepZ, 0.1f);
            }

            bool linked = block->mpLink->Get4adc40();
            block->mpLink->Set4adc20(false);
            vector<cSPEditorBlock_s0058_2250*> limbs;
            GetAllLimbs(block, &limbs, linked);
            {
                cSPEditorLimbStructure_s0058_2250 limb;
                int nLimbs = limbs.size();
                for (int i = 0; i < nLimbs; ++i) {
                    limb.Build(limbs[i], 0, 0);
                    limb.FixAllJoints();
                    limb.Apply();
                }
                block->mpLink->Set4adc20(linked);
                if (mpSkeleton)
                    mpSkeleton->Update5d2790();
                soundValue = (block->mScale - block->mMinScale) / (block->mMaxScale - block->mMinScale);
            }
        } else if (block->HasState()) {
            if (block->HasTwist()) {
                if (!IsManipulatorEnabled(0x8665f54d) && !IsManipulatorEnabled(0xe931544d))
                    return false;
                block->SetTwist(amount * 0.25f + block->mTwist);
                soundValue = block->mTwist;
            } else if (block->GetState()) {
                cBlockState* state = block->GetState();
                float v = amount * 0.25f + state->mValue;
                if (v > 1.0f)
                    v = 1.0f;
                else if (0.0f > v)
                    v = 0.0f;
                if (state->mValue != v) {
                    block->SetState(state, v, 0, 1);
                    block->StateChanged();
                }
                soundValue = state->mValue;
            }
        } else {
            block->SetScaleTarget(expf(amount * 0.75f) * block->mScaleTarget, 1);
            ApplyBlockScale(block, block->mScaleTarget, 1, 1);
            soundValue = (block->mScale - block->mMinScale) / (block->mMaxScale - block->mMinScale);
        }
    } else {
        if (!handle || handle->GetType() != 0x50e8e23)
            return handled;
        handled = true;
        MoveHandle(handle, delta * 0.05f);
        block = handle->GetRigblock();
        if (!block)
            return handled;
        block->GetHandleValue();
        float lo = block->mHandleMin;
        float hi = block->mHandleMax;
        soundValue = (block->GetHandleValue() - lo) / (hi - lo);
    }

    if (block) {
        SnapBlock(block, 0, 0, 0, 0, 0, 1, 1);
        string name(block->mpName);
        if (!(name == sz_13ec47c)) {
            SetSoundSymbol(0xb07c3bbf, 0x1e8bda2a, name.c_str());
            PlayEditorSound(0xb07c3bbf, 0xfdedb725, soundValue, 0);
        }
        if (mbPlayModelSizeSound)
            PlayEditorSound(0x1d6253c0, 0xdef22b96, CalculateModelSize(mpEditorModel), 0);
    }
    return handled;
}
}  // namespace SP

// @ 0x00582d00
void FUN_00582d00()
{}

// @ 0x00582d70
void FUN_00582d70()
{}

// @ 0x00582fe0
namespace SP {
bool cAppModeEditorBase_s0058_2fe0::RunSkinPaintOnEditorModel(int kind, void* pExisting)
{
    cSkinHolder* pHolder = 0;
    uint32_t* pId = 0;
    int count = 0;
    int idx = 0;

    if (kind == 0) {
        pHolder = mpSkinManager;
        pId = &mTorsoCreatureId;
    } else if (kind == 1) {
        cPaintCreatureRec rec;
        mRecs.push_back(rec);
        pHolder = mpSkinManager;
        count = mRecs.size();
        idx = count - 1;
        pId = &mRecs.mpBegin[idx].mCreatureId;
    } else if (kind == 2) {
        pHolder = mpPainter;
        pId = &mPainterCreatureId;
    }

    if (mpCreatureMgr) {
        if (!pId)
            return false;
        if (pHolder) {
            cSkinObject_s0058_2fe0* pSkin = pHolder->GetSkin(1);
            if (!*pId && pSkin) {
                bool bMeshValid = pSkin->IsMeshValid();
                pHolder->IsSkinUpToDate();
                if (!pHolder->IsSkinUpToDate() || !bMeshValid)
                    RebuildSkin(pHolder, pSkin);

                bool bFlag = true;
                if (kind == 0 && mEditorMode == 0)
                    bFlag = false;

                uint32_t id;
                if (pExisting)
                    id = mpCreatureMgr->AddCreature(pExisting);
                else
                    id = mpCreatureMgr->CreateCreature(mpEditorSaveModel, pSkin, bFlag, kind == 1);
                *pId = id;

                if (id) {
                    cEditorCreature* pCreature = mpCreatureMgr->GetCreature(id);
                    if (pCreature) {
                        IModelManager_s0058_2fe0* pModels = ModelManager_s0058_2fe0();
                        pCreature->SetModelResource(
                            pModels->GetModelResource(kind == 2 ? 0x509991e7 : 0x509991e6, 0, 1));
                        if (pCreature->mp17c)
                            pCreature->mp17c->FUN_009cb4f0();
                        if (!FUN_004a0ac0(mpEditorSaveModel) && mb2b5) {
                            pCreature->FUN_00a04a90(0);
                            if (mpEditorSaveModel->mModelType == 0xdfad9f51)
                                pCreature->FUN_00a04ab0(0);
                        }
                        mpCreatureMgr->SetCreatureVisible(*pId, true);
                        mpCreatureMgr->ResetCreature(*pId);
                        mpCreatureMgr->FUN_0059d180(*pId, m34c);
                        mpCreatureMgr->GetCreature(*pId)->m154 = 1;
                        mpCreatureMgr->GetCreatureStructure(*pId)->FUN_0059b390();
                        mpCreatureMgr->FUN_0059d1e0(*pId, kind != 1);

                        if (kind == 1) {
                            if (!pExisting)
                                pCreature->m3c = 0.45f;
                            Vector3_s0058_2fe0 target = kVecDefault;
                            Vector3_s0058_2fe0 pos;
                            if (mpCreatureMgr->GetCreaturePosition(mTorsoCreatureId, &pos)) {
                                cEditorCreature* pTorso = mpCreatureMgr->GetCreature(mTorsoCreatureId);
                                float size = pTorso->mpExtra->mSize * 1.5f;
                                if (size < 2.0f)
                                    size = 2.0f;
                                else if (size > 3.75f)
                                    size = 3.75f;

                                mRecs.mpBegin[idx].mApproachDistance = RandomFloatRange(3.7f, 5.5f);
                                mRecs.mpBegin[idx].mOffset.x = RandomFloat(0.3f);
                                mRecs.mpBegin[idx].mOffset.y = RandomFloat(0.3f);

                                pos.z = 0.0f;
                                Matrix3_s0058_2fe0 rot = Matrix3_s0058_2fe0(MakeRotation(kAxisUp, (float)(count - 1) / count * kAngleScale));
                                float dx = kApproachDir.x * size;
                                float dy = kApproachDir.y * size;
                                float dz = kApproachDir.z * size;
                                target.x = ((rot.row[1].x * dy + rot.row[2].x * dz) + rot.row[0].x * dx) + pos.x;
                                target.y = pos.y + ((rot.row[0].y * dx + rot.row[1].y * dy) + rot.row[2].y * dz);
                                target.z = pos.z + ((rot.row[0].z * dx + rot.row[1].z * dy) + rot.row[2].z * dz);
                                const cPaintCreatureRec& r = mRecs.mpBegin[idx];
                                target.x = target.x + r.mOffset.x;
                                target.y = r.mOffset.y + target.y;
                                target.z = r.mOffset.z + target.z;

                                mpCreatureMgr->FUN_0059d060(*pId, true);
                                mpLayout->FUN_0062ad70(&target, *pId, count - 1, size,
                                                       mRecs.mpBegin[idx].mOffset);
                                mpCreatureMgr->SetCreatureTargetPosition(*pId, target, true, true);

                                Vector3_s0058_2fe0 negDir(-kApproachDir.x, -kApproachDir.y, -kApproachDir.z);
                                Vector3_s0058_2fe0 diff(pos.x - target.x, pos.y - target.y, pos.z - target.z);
                                mpCreatureMgr->SetCreatureTargetAngle(
                                    *pId, -SignedAngle(diff, negDir, kAxisUp, true), true);
                                mpCreatureMgr->SetCreatureSpeeds(*pId, 0.75f, kCreatureSpeed * 0.75f);
                            }
                            MessageManager()->Post(0x3f1bf57, 0, &target);
                            mpCreatureMgr->PlayAnimation(*pId, 0x43736bf);
                            mRecs.mpBegin[idx].mb18 = false;
                            mRecs.mpBegin[idx].mb19 = true;
                            mRecs.mpBegin[idx].mb1a = false;
                            mRecs.mpBegin[idx].mb1b = false;
                            mRecs.mpBegin[idx].mb1c = false;
                            mRecs.mpBegin[idx].m20 = 0.0f;
                            mRecs.mpBegin[idx].m24 = 0.0f;
                            mRecs.mpBegin[idx].m28 = 0.0f;
                            mRecs.mpBegin[idx].m2c = -1;
                        }

                        if (mpEditorSaveModel && mpEditorSaveModel->mTypeID == 0x3d97a8e4) {
                            pCreature->FUN_00a04d00(1);
                            pCreature->FUN_00a04ce0(0xcbcd1287);
                        }

                        if (kind == 0) {
                            Vector3_s0058_2fe0 c = GetModelCenter(mpEditorSaveModel);
                            mpCreatureMgr->SetCreatureTargetPosition(*pId, Vector3_s0058_2fe0(-c.x, -c.y, -c.z), true, false);
                            if (mEditorMode == 0 || mEditorMode == 1)
                                mpCreatureMgr->SetCreaturePreserveHeight(*pId, true);
                        } else if (kind == 2) {
                            Vector3_s0058_2fe0 c = GetModelCenter(mpEditorSaveModel);
                            mpCreatureMgr->SetCreatureTargetPosition(*pId, Vector3_s0058_2fe0(-c.x, -c.y, -c.z), true, false);
                            mpCreatureMgr->SetCreaturePreserveHeight(*pId, true);
                        }
                    }
                }
            }
        }
    }
    return pId && *pId != 0;
}
}  // namespace SP

// @ 0x00583900
void FUN_00583900()
{}

// @ 0x00583c50
void FUN_00583c50()
{}

// @ 0x00584070
void FUN_00584070()
{}

// @ 0x00584160
void cIntVec::Resize(uint32_t n)
{
    int* begin = mpBegin;
    int* end = mpEnd;
    uint32_t cur = (uint32_t)(end - begin);
    if (n > cur) {
        int zero = 0;
        Insert(end, n - cur, &zero);
        return;
    }
    Erase(begin + n, end);
}

// @ 0x005841b0
void FUN_005841b0()
{}

// @ 0x00584230
void FUN_00584230()
{}

// @ 0x00585330
void FUN_00585330()
{}

// @ 0x005855b0
void FUN_005855b0()
{}

// @ 0x005857c0
void FUN_005857c0()
{}

// @ 0x00585830
void cAppModeEditorBase_s0058_5330::FUN_00585830(int a, int b)
{
    Input()->OnKeyDown(a, b);
    SetModeModifiers();
}

// @ 0x00585860
void cAppModeEditorBase_s0058_5330::FUN_00585860(int a, int b)
{
    Input()->OnKeyUp(a, b);
    SetModeModifiers();
}

// @ 0x005858f0
void FUN_005858f0()
{}

// @ 0x00585c10
void FUN_00585c10()
{}

// @ 0x00585d10
void FUN_00585d10()
{}

// @ 0x00586410
void SP::cAppModeEditorBase_s0058_5d40::FUN_00586410(char a, void* b)
{
    (void)a;
    (void)b;
    mUndoLocalStateList.erase(mUndoLocalStateList.mpBegin, mUndoLocalStateList.mpEnd);
    mUndoList.erase(mUndoList.mpBegin, mUndoList.mpEnd);
}

// @ 0x00586690
void SP::cAppModeEditorBase_s0058_5d40::InitializeUndoList()
{
    mUndosLeft = 0;
    SP::UndoVector& undo = mUndoList;
    undo.erase(undo.mpBegin, undo.mpEnd);
    mUndoLocalStateList.erase(mUndoLocalStateList.mpBegin, mUndoLocalStateList.mpEnd);
    FUN_00586410(0, 0);
    mDevUI->EnableUndoButton(0);
    mDevUI->EnableRedoButton(0);
    *(bool*)((char*)this + 0x4b3) = 0;
    *(bool*)((char*)this + 0x4b4) = 0;
    mDevUI->UpdateUIBasedOnModelSaveability();
}

// @ 0x00586700
void SP::cAppModeEditorBase_s0058_5d40::FUN_00586700()
{
    uint8_t* bitsA = (uint8_t*)this + 0x4d8;
    for (int i = 0; i < 0x23; ++i)
        bitsA[i] = 0;
    for (int s = 0; s < 6; ++s) {
        *(int*)((char*)this + 0x4f0 + s * 4) = 0;
        uint8_t* slot = (uint8_t*)this + 0x50c + s * 0x14;
        for (int i = 0; i < 0x23; ++i)
            slot[i] = 0;
    }
}

// @ 0x00586800
uint8_t SP::cAppModeEditorBase_s0058_5d40::FUN_00586800(void* a)
{
    (void)a;
    for (int s = 0; s < 6; ++s) {
        *(int*)((char*)this + 0x4f0 + s * 4) = 0;
        uint8_t* slot = (uint8_t*)this + 0x50c + s * 0x14;
        for (int i = 0; i < 0x23; ++i)
            slot[i] = 0;
    }
    return 0;
}

// @ 0x00586960
void SP::cAppModeEditorBase_s0058_5d40::FUN_00586960()
{
    *(bool*)((char*)this + 0x472) = 0;
    *(void**)((char*)this + 0x48c) = 0;
    *(void**)((char*)this + 0x490) = 0;
    FUN_00586410(1, 0);
}

// @ 0x00586b00
void SP::cAppModeEditorBase_s0058_6b00::PrepareAppForNewModel(SPModel* model)
{
    if (M(uint8_t, 0x472)) ScaleBlock();

    if (M(void*, 0x380)) {
        IRef* p = M(IRef*, 0x380);
        if (p) {
            M(void*, 0x380) = 0;
            p->Release();
        }
    }

    // M(0x39c).clear()  (vector erase(begin, end))
    {
        uint* e = M(uint*, 0x3a0);
        uint* b = M(uint*, 0x39c);
        FUN_011e0744(b, e, (char*)e - (char*)e);
        M(uint*, 0x3a0) = M(uint*, 0x3a0) + (-(e - b));
    }

    {
        IRef* p = M(IRef*, 0xd0);
        if (p) { M(void*, 0xd0) = 0; p->Release(); }
    }
    {
        IRef4* p = M(IRef4*, 0x148);
        if (p) { M(void*, 0x148) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xd4);
        if (p) { M(void*, 0xd4) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xd8);
        if (p) { M(void*, 0xd8) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xdc);
        if (p) { M(void*, 0xdc) = 0; p->Release(); }
    }
    {
        IRef* p = M(IRef*, 0xcc);
        if (p) { M(void*, 0xcc) = 0; p->Release(); }
    }

    if (M(SPModel*, 0x98)) M(SPModel*, 0x98)->FUN_004ad330();

    NameProvider* np = (NameProvider*)((char*)this + 0xc);
    if (M(char*, 0x1cc)) np->SetC(*(const wchar_t**)(M(char*, 0x1cc) + 0x50));

    SPModel* newModel = model;
    if (newModel) {
        SPModel* cur = M(SPModel*, 0x98);
        if (newModel != cur) {
            newModel->mRefCount++;
            M(SPModel*, 0x98) = newModel;
            if (cur) RcRelease(cur);
        }
        Key key;
        SPModel* m = M(SPModel*, 0x98);
        key.inst = m->kInst;
        key.type = m->kType;
        key.group = m->kGroup;
        key.type = 0x30bdee3;
        MetaObj* meta = 0;
        ResManager* mgr = GetManager_s0058_6b00();
        if (meta) {
            IRef4* t = (IRef4*)meta;
            meta = 0;
            t->Release();
        }
        if (mgr->GetResource(&key, &meta, 0, 0, 0, 0)) {
            AssetMeta* am = meta ? meta->Cast(0x30bdee3) : 0;
            WStrE tags;
            am->GetTagsString(&tags);
            np->SetC(tags.mb);
        }
        ((Naming*)M(void*, 0x358))->SetDataProvider(np);
        gTokenTranslator->SetOldModelName(np->GetA());
        TokenTranslator* tt = gTokenTranslator;
        tt->FUN_005d60c0(np->GetA());
        if (meta) ((IRef4*)meta)->Release();
        newModel = model;
    }

    if (M(void*, 0x360) && M(uint, 0x364)) {
        if (M(uint8_t, 0x385)) FUN_0057e340(0);
        ((CreatureMgr*)M(void*, 0x360))->RemoveCreature(M(uint, 0x364));
        M(uint, 0x364) = 0;
    }

    SPModel* m = M(SPModel*, 0x98);
    M(uint8_t, 0x4b2) = 0;
    M(uint8_t, 0x39a) = 1;
    m->FUN_004ada80(M(float, 0x2b8));
    M(SPModel*, 0x98)->FUN_004adac0(M(float, 0x2bc));
    M(SPModel*, 0x98)->FUN_004adae0(M(float, 0x2c0));
    M(SPModel*, 0x98)->FUN_004adb20(M(float, 0x2c4));
    M(SPModel*, 0x98)->FUN_004adc00(M(float, 0x2d4));
    M(SPModel*, 0x98)->FUN_004ae260(M(uint, 0x84), M(uint, 0x90), 1, 1);
    M(SPModel*, 0x98)->FUN_004adba0(M(uint8_t, 0x470));
    M(SPModel*, 0x98)->FUN_004adbe0(M(uint8_t, 0x471));
    M(SPModel*, 0x98)->FUN_004adb60(M(uint8_t, 0x2f9));
    M(SPModel*, 0x98)->FUN_004abad0(M(uint, 0x304));

    if (M(float, 0x2d4) > gFloatThreshold) {
        if (!FUN_004a0ac0(M(SPModel*, 0x98))) {
            float minZ = GetModelMinZ(M(SPModel*, 0x98));
            if (M(float, 0x2d4) > minZ) {
                float d = M(float, 0x2d4) - minZ;
                float bbox[6];
                M(SPModel*, 0x98)->FUN_004ad550(bbox, 0);
                float top = bbox[5] + d;
                if (M(SPModel*, 0x98)->FUN_004adb40() > top) {
                    Vec3 v = { 0.0f, 0.0f, d };
                    FUN_004934d0(M(SPModel*, 0x98), v, 0);
                }
            }
        }
    }

    if (M(PropList_s0058_6b00*, 0x24)) {
        Property_s0058_6b00* prop;
        if (M(PropList_s0058_6b00*, 0x24)->Get(0x600c6b8, &prop) && prop->type == 0xa) {
            uint v = *prop->GetUInt();
            if (v) {
                float out[4];
                FUN_0046b8e0(out, M(SPModel*, 0x98), v);
                Vec3 t = { out[3], out[1], out[2] };
                FUN_004934d0(M(SPModel*, 0x98), t, 0);
            }
        }
    }

    if (M(uint8_t, 0x2f2)) {
        if (M(DecoMgr*, 0x14c)) M(DecoMgr*, 0x14c)->FUN_005d31b0();
        if (M(uint8_t, 0x2f3)) {
            if (newModel)
                M(DecoMgr*, 0x14c)->FUN_005d3f10(M(SPModel*, 0x98), M(void*, 0x84));
            else
                M(DecoMgr*, 0x14c)->FUN_005d36e0(M(SPModel*, 0x98), M(void*, 0x84), 8);
        }
    }

    if (M(uint8_t, 0x2f1)) {
        SkinMgr_s0058_6b00* sk = M(SkinMgr_s0058_6b00*, 0x150);
        if (sk) {
            bool r = sk->FUN_004c4630();
            M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c4eb0();
            M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c3070(this, M(SPModel*, 0x98), M(void*, 0x84));
            float a = gDefaultA;
            float b = gDefaultB;
            if (M(PropList_s0058_6b00*, 0x24)) {
                Property_s0058_6b00* prop;
                if (M(PropList_s0058_6b00*, 0x24)->Get(0x711306cd, &prop) && prop->type == 0xd)
                    a = *prop->GetFloat();
            }
            if (M(PropList_s0058_6b00*, 0x24)) {
                Property_s0058_6b00* prop;
                if (M(PropList_s0058_6b00*, 0x24)->Get(0x711306ce, &prop) && prop->type == 0xd)
                    b = *prop->GetFloat();
            }
            M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c5100(a, b);
            M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c4650(r);
        }
        if (M(int, 0x31c) == 1) {
            FUN_00582fe0(0, 0);
            FUN_0057e340(1);
            SPModel* mm = M(SPModel*, 0x98);
            bool skip = false;
            if (M(SkinMgr_s0058_6b00*, 0x154)) skip = M(SkinMgr_s0058_6b00*, 0x154)->FUN_004c58b0();
            if (!skip && mm && M(SkinMgr_s0058_6b00*, 0x150)) M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c5200(mm);
        }
    } else {
        FUN_004b7660(M(SPModel*, 0x98));
        if (M(int, 0x31c) == 1) {
            SPModel* mm = M(SPModel*, 0x98);
            int n = mm->FUN_004accf0();
            for (int i = 0; i < n; i++) {
                M(SPModel*, 0x98)->FUN_004accb0(i, 3, 1, 0, 1)->FUN_0043a5e0();
                M(SPModel*, 0x98)->FUN_004accb0b(i, 0)->FUN_0043a830();
            }
        }
    }

    FUN_0057c440();
    {
        SPModel* mm = M(SPModel*, 0x98);
        if (mm->f58 == 0) mm->f58 = *M(uint*, 0x334);
    }
    if (M(uint8_t, 0x2f4)) M(SPModel*, 0x98)->FUN_004adc20(1);

    if (M(char*, 0x1cc) && M(SPModel*, 0x98)->kType == 0x2b978c46) {
        // M(0x588) = ld->vec at +0x70  (eastl::vector<float>::operator=)
        *(FVec*)((char*)this + 0x588) = *(FVec*)(M(char*, 0x1cc) + 0x70);
    } else {
        uint* e = M(uint*, 0x58c);
        uint* b = M(uint*, 0x588);
        FUN_011e0744(b, e, (char*)e - (char*)e);
        M(uint*, 0x58c) = M(uint*, 0x58c) + (-(e - b));
    }
    M(SPModel*, 0x98)->FUN_004adfc0(0);
}

// @ 0x00587270
bool SP::cAppModeEditorBase_s0058_6b00::SetMode(int mode, char force)
{
    int* pMode = &M(int, 0x31c);
    int old = *pMode;
    if (old == mode && !force) return false;
    int busy = M(int, 0x38c);
    if (busy != 0 && busy != 6) return false;
    M(float, 0x68) = 0.0f;

    if (old == 0) {
        if (M(uint8_t, 0x472)) ScaleBlock();
    } else if (old == 1) {
        int n = M(SPModel*, 0x98)->FUN_004accf0();
        for (int i = 0; i < n; i++) {
            M(SPModel*, 0x98)->FUN_004accb0(i, 0, 1, 0, 1)->FUN_0043a5e0();
            M(SPModel*, 0x98)->FUN_004accb0b(i, 0)->FUN_0043a830();
        }
        M(uint, 0x3c) &= ~1u;
    } else if (old == 2) {
        if (FUN_00401050(M(int, 0x278))->FUN_0045b210())
            FUN_00401050(M(int, 0x278))->FUN_0045b150();
        if (M(int, 0x27c)) FUN_00401050_2(M(int, 0x27c), 1)->FUN_0045ae10();
        char* a = M(char*, 0xa4);
        if (a) {
            FUN_011e0744(a + 0x1c, gDefaultBlock, 36);
            *(uint16_t*)(a + 8) |= 2;
            (*(uint16_t*)(a + 0xa))++;
        }
        M(PlayMode*, 0x7c)->Stop();
        char* b = M(char*, 0xa8);
        if (b) *(uint*)(b + 4) |= 1;
        CreateWidget2(3);
        CreatureMgr* cm = M(CreatureMgr*, 0x360);
        cm->SetCreaturePreserveHeight(M(uint, 0x364), 1);
        float bb[8];
        FUN_0046bfd0(bb, M(SPModel*, 0x98));
        cm = M(CreatureMgr*, 0x360);
        cm->SetCreatureTargetPosition(M(uint, 0x364), -bb[2], -bb[3], -bb[4], 1, 0);
        if (M(CreatureMgr*, 0x360)->GetCreatureStructure(M(uint, 0x364))) {
            ((Flagged_s0058_6b00*)M(CreatureMgr*, 0x360)->GetCreatureStructure2(M(uint, 0x364), 1))->SetFlag();
        }
    }

    FUN_00573c00(0, -1);
    {
        char* h = M(char*, 0xd4);
        if (h) {
            if (!((*(uint*)(h + 0xdc8) >> 1) & 1)) {
                Handle_s0058_6b00* hd = M(Handle_s0058_6b00*, 0xe4);
                if (hd && hd->FUN_0047e6c0() == h) SetRolloverHandle(0, 1);
                ((SubObj*)M(void*, 0xd4))->FUN_0043a9a0(0, 1);
            }
            IRef* r = M(IRef*, 0xd4);
            if (r) {
                M(void*, 0xd4) = 0;
                r->Release();
            }
        }
    }
    if (M(uint8_t, 0xe8)) M(uint8_t, 0xe8) = 0;
    if (M(uint8_t, 0xe9)) {
        RemoveTorsoFromEffectsMask();
        M(uint8_t, 0xe9) = 0;
    }

    bool wasPainted = M(SkinMgr_s0058_6b00*, 0x150) && M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c4630();
    bool nowPainted = M(SkinMgr_s0058_6b00*, 0x150) && mode != 0;
    if (wasPainted) {
        if (!nowPainted) M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c4650(0);
    } else if (nowPainted) {
        M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c4650(1);
        SPModel* mm = M(SPModel*, 0x98);
        bool skip = false;
        if (M(SkinMgr_s0058_6b00*, 0x154)) skip = M(SkinMgr_s0058_6b00*, 0x154)->FUN_004c58b0();
        if (!skip && mm && M(SkinMgr_s0058_6b00*, 0x150)) M(SkinMgr_s0058_6b00*, 0x150)->FUN_004c5200(mm);
    }
    FUN_005744b0(mode);

    if (M(void*, 0x360) && M(SkinMgr_s0058_6b00*, 0x150) && M(SkinMgr_s0058_6b00*, 0x150)->GetSkin(1) && old == 0) {
        if (M(void*, 0x360) && M(uint, 0x364)) {
            if (M(uint8_t, 0x385)) FUN_0057e340(0);
            M(CreatureMgr*, 0x360)->RemoveCreature(M(uint, 0x364));
            M(uint, 0x364) = 0;
        }
    }
    *pMode = mode;

    if (!M(void*, 0x360)) goto angle_step;
    if (M(SkinMgr_s0058_6b00*, 0x150) && M(SkinMgr_s0058_6b00*, 0x150)->GetSkin(1) && mode == 0) {
        if (!M(void*, 0x360)) goto angle_step;
        if (M(uint, 0x364)) {
            if (M(uint8_t, 0x385)) FUN_0057e340(0);
            M(CreatureMgr*, 0x360)->RemoveCreature(M(uint, 0x364));
            M(uint, 0x364) = 0;
        }
    }
    if (!M(void*, 0x360) || !M(SkinMgr_s0058_6b00*, 0x150) || !M(SkinMgr_s0058_6b00*, 0x150)->GetSkin(1)) goto angle_step;
    if (M(uint8_t, 0x385) == 0) {
        FUN_00582fe0(0, 0);
        FUN_0057e340(1);
        goto render_step;
    }
angle_step:
    if (M(uint8_t, 0x385) && old == 2)
        M(CreatureMgr*, 0x360)->SetCreatureTargetAngle(M(uint, 0x364), 0.0f, 1);
render_step:
    UpdateRenderSettings();
    {
        char* cm = M(char*, 0x360);
        if (cm) {
            CamHolder* ch = *(CamHolder**)(cm + 0x38);
            if (ch) ch->SlotX(0);
        }
    }

    if (mode == 0) {
        if (M(void*, 0x360) && M(SkinMgr_s0058_6b00*, 0x150) && M(SkinMgr_s0058_6b00*, 0x150)->GetSkin(1) && M(uint8_t, 0x2b5))
            FUN_00573330();
        void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
        AnimEventInfo* ev = rawEv ? ((AnimEventInfo*)rawEv)->Init() : 0;
        if (ev) ev->AddRef();
        ev->MessageSend(0xcb52be29, 0, M(void*, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
        if (ev) ev->Release();
    } else if (mode == 1) {
        M(char*, 0x4d8)[5] = 1;
        int r = FUN_00576140();
        if (r < 6 && M(char*, 0x1cc) && M(char*, 0x1cc)[0x6e]) {
            (*(char**)((char*)this + r * 20 + 0x508))[5] = 1;
        }
        if (M(void*, 0x360) && M(SkinMgr_s0058_6b00*, 0x150) && M(SkinMgr_s0058_6b00*, 0x150)->GetSkin(1) && M(uint8_t, 0x2b5))
            FUN_00573330();
        int n = M(SPModel*, 0x98)->FUN_004accf0();
        for (int i = 0; i < n; i++) {
            M(SPModel*, 0x98)->FUN_004accb0(i, 3, 1, 0, 1)->FUN_0043a5e0();
            M(SPModel*, 0x98)->FUN_004accb0b(i, 0)->FUN_0043a830();
        }
        void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
        AnimEventInfo* ev = rawEv ? ((AnimEventInfo*)rawEv)->Init() : 0;
        if (ev) ev->AddRef();
        ev->MessageSend(0x565d8223, 0, M(void*, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
        GetMessageServer_s0058_6b00()->Post(0x578dedb, 0, 0);
        if (ev) ev->Release();
    } else if (mode == 2) {
        M(char*, 0x4d8)[6] = 1;
        int r = FUN_00576140();
        if (r < 6 && M(char*, 0x1cc) && M(char*, 0x1cc)[0x6e]) {
            char** c = (char**)((char*)this + r * 20 + 0x508);
            M(char*, 0x580)[r] = (*c)[6];
            (*c)[6] = 1;
        }
        CreateWidget2(2);
        if (M(VProbe*, 0x358)) M(VProbe*, 0x358)->SlotX(0);
        if (M(void*, 0x360) && M(SkinMgr_s0058_6b00*, 0x150) && M(SkinMgr_s0058_6b00*, 0x150)->GetSkin(1)) FUN_00573390();
        {
            char* cm = M(char*, 0x360);
            if (cm) {
                CamHolder* ch = *(CamHolder**)(cm + 0x38);
                if (ch) {
                    ch->SlotX(1);
                    char* s = (char*)M(CreatureMgr*, 0x360)->GetCreatureStructure(M(uint, 0x364));
                    if (s && *(void**)(s + 8)) {
                        for (int i = 0; i < 3; i++) {
                            float tmp[3];
                            float* p = M(SPModel*, 0x98)->FUN_004adca0(tmp, i);
                            Vec3 v = { p[0], p[1], p[2] };
                            ((Sink*)*(void**)(s + 8))->FUN_00a04550(i, &v);
                        }
                    }
                }
            }
        }
        if (FUN_00401050(M(int, 0x27c))->FUN_0045b210())
            FUN_00401050(M(int, 0x27c))->FUN_0045b150();
        if (M(int, 0x278)) FUN_00401050_2(M(int, 0x278), 1)->FUN_0045ae10();
        char* b = M(char*, 0xa8);
        if (b) *(uint*)(b + 4) &= ~1u;
        M(PlayMode*, 0x7c)->HandleMessages(M(int, 0x278));
        M(CreatureMgr*, 0x360)->SetCreaturePreserveHeight(M(uint, 0x364), 0);
    }

    if (M(uint8_t, 0x20e)) PlayEditorSound(0x1d6253c0, 0xbd5385c8, (float)*pMode, 0);
    return true;
}

// @ 0x00587a20
namespace SP {
void cAppModeEditorBase_s0058_7a20::Deactivate()
{
    if (mpEffectWorld)
        mpEffectWorld->Deactivate();
    g_pAppProperties->SetIntProperty(0xb, field_450);
    mIsActive = false;
    if (PropertyUI())
        PropertyUI()->DestroyAllElems();

    cEditorDeactivatedMessage msg;
    msg.mModeID = GetModeID();
    MessageServer_s0058_7a20()->PostMSG(msg.mMessageID, &msg, 0);

    *g_pRenderFlags &= ~1u;
    ClearUndoRedo();
    mpCreationController = 0;
    HintManager()->ClearHints();
    HintManager()->SetEnabled(field_144, true);
    if (App_s0058_7a20())
        App_s0058_7a20()->GetViewer()->SetViewAngleY(field_4D0);
    mpCameraController = 0;
    DestroyEditorWidgets(true);
    if (g_pAppProperties->mpConfig->mnValue118)
        HideDebugUI();
    CheatManager_s0058_7a20()->RemoveCheats("editor");
    RenderTargets()->GetTarget()->ClearValue(g_RenderTargetValue);

    if (mpLaunchData) {
        cEditorResultsMessage* pResults = new ("Editor", 0, 0, 0, 0) cEditorResultsMessage();
        if (pResults)
            pResults->AddRef();
        pResults->mCallerID = mpLaunchData->mCallerID;
        pResults->mpCallerData = mpLaunchData->mpCallerData;
        pResults->mModelKey = mpLaunchData->mModelKey;
        pResults->mModelID = mpEditorModel->mModelID;
        pResults->mbAccepted = true;
        MessageServer_s0058_7a20()->PostMessage(0x30c11c7, pResults, 0, 0);
        mpLaunchData = 0;
        pResults->Release();
    }

    if (App_s0058_7a20())
        SetMode(0, true);
    if (RenderManager()->GetUILayerModelWorld() && mpUILayerOldLightingWorld)
        RenderManager()->GetUILayerModelWorld()->SetLightingWorld(mpUILayerOldLightingWorld, 0, true);
    RemoveTorsoFromEffectsMask();
    SetSelection(0, -1);

    if (cSPEditorBlock_s0058_7a20* pBlock = mpPreviousSelectedBlock) {
        if (!pBlock->IsFlagSet1()) {
            if (mpRolloverHandle && mpRolloverHandle->GetRigblock() == pBlock)
                SetRolloverHandle(0, true);
            mpPreviousSelectedBlock->SetUIState(0, true);
        }
        mpPreviousSelectedBlock = 0;
    }
    if (mTorsoUIState)
        mTorsoUIState = false;
    if (mbTorsoInEffectsMask) {
        RemoveTorsoFromEffectsMask();
        mbTorsoInEffectsMask = false;
    }

    if (IAudioSystem_s0058_7a20* pAudio = EA::Audio::GetSystemAT_s0058_7a20()) {
        pAudio->SetGroup(0x347536b);
        pAudio->SetValue(0x3475385, 0x1d6253c0);
        pAudio->SetValue(0x34753a0, 0);
        pAudio->Commit();
    }
    if (IAudioSystem_s0058_7a20* pAudio = EA::Audio::GetSystemAT_s0058_7a20()) {
        pAudio->SetGroup(0x347536b);
        pAudio->SetValue(0x3475385, 0xb07c3bbf);
        pAudio->SetValue(0x34753a0, 0);
        pAudio->Commit();
    }
    mbBackgroundMusic = false;
    SwarmManager()->ClearEditorEffects();
    EffectsManager_s0058_7a20()->SetFlags(0x10, 0);

    if (mpEditorModel) {
        mpEditorModel->ClearSelection();
        mpEditorModel->ClearBlocks();
        mpEditorModel = 0;
    }
    if (mpEditorSaveModel) {
        mpEditorSaveModel->ClearSelection();
        mpEditorSaveModel->ClearBlocks();
        mpEditorSaveModel = 0;
    }
    if (mpSpine) {
        mpSpine->ClearVertebrae();
        mpSpine = 0;
    }
    if (mpSaveLoadFactory) {
        mpSaveLoadFactory->Shutdown();
        mpSaveLoadFactory = 0;
    }
    if (mpTextureFactory) {
        mpTextureFactory->Shutdown();
        mpTextureFactory = 0;
    }
    if (cDisplayObject* p = DisplayManager()->GetPrimary())
        p->mbFlagB9 = field_4B6;
    if (cDisplayObject* p = DisplayManager()->GetSecondary())
        p->mbFlagB9 = field_4B6;
    if (mpSellBackRollover) {
        mpSellBackRollover->Shutdown();
        mpSellBackRollover = 0;
    }
    if (mpSellBackRollover2) {
        mpSellBackRollover2->Shutdown();
        mpSellBackRollover2 = 0;
    }
    if (mpMessageRollover) {
        mpMessageRollover->Shutdown();
        mpMessageRollover = 0;
    }
    if (mpDetachedRollover) {
        mpDetachedRollover->Shutdown();
        mpDetachedRollover = 0;
    }
    if (mpDetachedRollover2) {
        mpDetachedRollover2->Shutdown();
        mpDetachedRollover2 = 0;
    }
    if (mVerbIconTray) {
        mVerbIconTray->Shutdown();
        mVerbIconTray = 0;
    }
    if (mpBudget) {
        mpBudget->Shutdown();
        mpBudget = 0;
    }
    if (mpComplexityMeter) {
        mpComplexityMeter->Shutdown();
        mpComplexityMeter = 0;
    }
    if (mpStatsPanel) {
        mpStatsPanel->Shutdown();
        mpStatsPanel = 0;
    }
    if (mpNaming) {
        mpNaming->Shutdown();
        mpNaming = 0;
    }
    if (mpPlayMode) {
        mpPlayMode->Shutdown();
        mpPlayMode = 0;
    }
    if (mDefaultPaintTheme) {
        mDefaultPaintTheme->Reset();
        mDefaultPaintTheme = 0;
    }
    if (mCurrentPaintTheme) {
        mCurrentPaintTheme->Reset();
        mCurrentPaintTheme = 0;
    }
    if (mpPaintPaletteUI) {
        mpPaintPaletteUI->Shutdown();
        mpPaintPaletteUI = 0;
    }
    if (mpPaintPalette) {
        mpPaintPalette->Shutdown();
        mpPaintPalette = 0;
    }
    if (mpPartsPaletteUI) {
        mpPartsPaletteUI->Shutdown();
        mpPartsPaletteUI = 0;
    }
    if (mpPartsPalette) {
        mpPartsPalette->Shutdown();
        mpPartsPalette = 0;
    }
    if (mpEditorUI) {
        mpEditorUI->Shutdown();
        mpEditorUI = 0;
    }
    mpRolloverHandle = 0;
    if (mpPedestalModel) {
        mpPedestalModel->mpWorld->SetInWorld(mpPedestalModel, false);
        mpPedestalModel = 0;
    }
    if (mpTestEnvironmentModel) {
        mpTestEnvironmentModel->mpWorld->SetInWorld(mpTestEnvironmentModel, false);
        mpTestEnvironmentModel = 0;
    }
    if (mpBackgroundModel) {
        mpBackgroundModel->mpWorld->SetInWorld(mpBackgroundModel, false);
        mpBackgroundModel = 0;
    }
    if (mpPlayModeBackgroundModel) {
        mpPlayModeBackgroundModel->mpWorld->SetInWorld(mpPlayModeBackgroundModel, false);
        mpPlayModeBackgroundModel = 0;
    }
    if (mpAnimCreatureManager) {
        mpAnimCreatureManager->Shutdown();
        mpAnimCreatureManager = 0;
    }
    field_385 = false;
    field_384 = false;
    field_364 = 0;
    field_368 = 0;
    if (mpTool) {
        mpTool->Shutdown();
        mpTool = 0;
    }
    mpUndoQueue = 0;
    if (mpShadowWorld) {
        mpShadowWorld->SetActive(false);
        mpShadowWorld->Clear();
        mpShadowWorld = 0;
    }
    if (mpMainModelWorld)
        mpMainModelWorld->SetActive(false);
    if (mpBackgroundModelWorld)
        mpBackgroundModelWorld->SetActive(false);
    ModelManager_s0058_7a20()->SetSaveModelWorld(0);
    InputManager()->ClearState(0xf);
    InputManager()->ClearState(0xc);
    InputManager()->ClearState(0xd);
    InputManager()->ClearState(0x1a);
    InputManager()->ClearState(0x11);
    InputManager()->ClearState(0x14);
    if (mpEffectWorld) {
        mpEffectWorld->SetState(2);
        EffectsManager_s0058_7a20()->SetActiveWorld(0);
    }
    GameInputManager()->Reset();
    mMessageRegistration.Unregister();

    IWindow_s0058_7a20* pWindow = WindowManager_s0058_7a20()->GetMainWindow();
    cSPUIMainWin* pMainWin = static_cast<cSPUIMainWin*>(pWindow);
    mnTotalActiveTime += pMainWin->GetTimeStamp() - mnActivateTime;
    CursorManager_s0058_7a20()->SetLocalCursor(0x1002);
    SetShaderParam(0x238, 0, 1);
    SetShaderParam(0x236, 0, 1);
}
}  // namespace SP

// @ 0x00589ce0
void SP::cAppModeEditorBase_s0058_9ce0::FUN_00589ce0(const wchar_t* path)
{
    if (M(uint8_t, 0x2b0) == 0) return;

    WStr s(path);
    // find the last '.' and keep only the extension: s.erase(0, pos + 1)
    const wchar_t* dEnd = gDelimiters;
    while (*dEnd) dEnd++;
    int n = ((char*)s.me - (char*)s.mb) >> 1;
    int pos = -1;
    if (n != 0) {
        int last = n - 1;
        const wchar_t* r = FindFirstOfRev(s.mb + last + 1, s.mb, gDelimiters, dEnd);
        if (r != s.mb) pos = (((char*)r - (char*)s.mb) - 2) >> 1;
    }
    s.Erase(0, pos + 1);

    if ((((char*)s.me - (char*)s.mb) & ~1) == 6) {
        // iterate the (type id -> config) map; node layout: +0x10 key
        char* anchor = (char*)this + 0x1b4;
        char* node = M(char*, 0x1b8);
        while (node != anchor) {
            uint typeId = *(uint*)(node + 0x10);
            if (typeId == 0) typeId = M(uint, 0x2a8);
            const wchar_t* ext = GetTypeExtension(typeId);
            const wchar_t* e = ext;
            while (*e) e++;
            int len = (e - ext);
            int cmpN = len < 3 ? len : 3;
            if (WStrNCompare(s.mb, ext, cmpN) == 0 && len == 3) {
                FileStream* fs = (FileStream*)operator_new(0x22c, "Editor", 0, 0, 0, 0);
                if (fs) fs = fs->Init(0);
                if (fs) fs->AddRef();
                fs->SetPath(path);
                if (fs->Open(1, 6, 1, 0)) {
                    RawResource* res = (RawResource*)operator_new(0xac, "Editor", 0, 0, 0, 0);
                    if (res) res = res->Init();
                    if (res) res->AddRef();
                    EditorResource* out = (EditorResource*)operator_new(0xe0, "Editor", 0, 0, 0, 0);
                    if (out) out = out->Init();
                    if (out) out->mRefCount++;
                    if (!ReadResourceFromStream(fs, res, -1) || !out->CopyFrom(res)) {
                        Key16 e1 = { 0x4000000, 0, 0, 0 };
                        Key16 e2 = { 0x4000000, 0, 0, 0 };
                        ShowError(e1, e2);
                    } else {
                        EditorResHeader* hdr = res ? res->Cast(0x3c609f8) : 0;
                        Key16 got;
                        hdr->ReadKey(&got, gNullKey, 0);
                        if (KeyEquals(got, gNullKey)) {
                            int cfg = RemapTypeId(hdr->mModelType);
                            if (cfg != ((int (__thiscall*)(void*))(*(void***)this)[0x44 / 4])(this))
                                SetCurrentConfig(cfg, 0, 0, 0);
                            uint genOut[3] = { 0, 0, 0 };
                            IDGen* gen = GetIDGenerator();
                            uint64_t id = MapModeToId(M(uint, 0x2a8));
                            gen->Generate(genOut, (uint)(id >> 32), (uint)id);
                            out->mKey.inst = genOut[0];
                            out->mKey.type = genOut[1];
                            out->mKey.group = genOut[2];
                            PrepareAppForNewModel(out);
                            M(uint8_t, 0x4b0) = 1;
                            M(uint8_t, 0x4b1) = 0;
                            ((EditorUIEx*)M(void*, 0x78))->FUN_005dd1d0();
                            InitializeUndoList();
                            NameProvider_s0058_9ce0* np = (NameProvider_s0058_9ce0*)((char*)this + 0xc);
                            gTokenTranslator_s0058_9ce0->SetOldModelName(np->GetA());
                            ResetEconomy();
                            fs->Close();
                        } else {
                            Out16 mask;
                            Out16* m = GetMask(&mask);
                            Key16 mk = { m->w[0], m->w[1], m->w[2], m->w[3] };
                            ShowError(mk, got);
                            fs->Close();
                        }
                    }
                    if (out) {
                        RcRelease_s0058_9ce0(out);
                    }
                    if (res) ((RawResource*)res)->Release();
                }
                fs->Release();
                break;
            }
            node = (char*)RBTreeIncrement(node);
        }
    }
}

// @ 0x0058a350
void SP::cAppModeEditorBase_s0058_9ce0::LoadModel(int mode, int a, int b)
{
    M(uint, 0x1a8) = 1;
    switch (mode) {
    case 0:
        M(uint, 0x1a4) = 1;
        FUN_005802f0(b, a);
        break;
    case 1:
        if (M(uint8_t, 0x4b5)) {
            AuthMgr* auth = GetAuthManager();
            if (!auth->IsX()) {
                void* key = (char*)M(void*, 0x98) + 0xc;
                if (FUN_00552300(key) == 1) {
                    if (!GetCreatorType(key)) FUN_00572430(key);
                }
            }
        }
        M(uint, 0x1a4) = 0;
        FUN_0057e8a0();
        break;
    case 2:
        M(uint, 0x1a4) = 0;
        FUN_0057c1e0();
        break;
    }

    if (((EditorUIEx*)M(void*, 0x78))->FUN_005dc450()) {
        ((EditorUIEx*)M(void*, 0x78))->FUN_005dd090(0);
        ((EditorUIEx*)M(void*, 0x78))->EnableBasicEditorButtons(0, 1);
    }
    GetUIHints(0, 1)->SetEnabled();
    if (M(int, 0x31c) == 2) SetMode(0, 1);
    FUN_00573f20(M(int, 0x19c));

    if (M(uint8_t, 0x191)) {
        IFace1* f1 = M(IFace1*, 0x20);
        IFace3* f3 = f1->GetCam()->GetCtl();
        if (f3) {
            CamController* cc = f3->Cast(0x29da727);
            if (cc) cc->SetCenterCameraOffset();
        }
    }
    if (M(uint8_t, 0x190)) ((EditorUIEx*)M(void*, 0x78))->Hide();
    M(uint, 0x198) = 0;

    if (M(uint, 0x194) && M(void*, 0x360) && M(void*, 0x150)) {
        SkinManager* skin = ((SkinManager*)M(void*, 0x150))->GetSkin(1);
        if (skin && mode != 2) {
            if (M(uint, 0x364) == 0) {
                FUN_00582fe0(0, 0);
                if (M(uint, 0x364) == 0) { FUN_0057c0e0(); return; }
            }
            FUN_0057e340(1);
            IRefObj* old = M(IRefObj*, 0x380);
            if (old) {
                M(IRefObj*, 0x380) = 0;
                old->Release();
            }
            void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
            AnimEventInfo_s0058_9ce0* ev = rawEv ? ((AnimEventInfo_s0058_9ce0*)rawEv)->Init() : 0;
            if (ev) ev->AddRef();
            ev->f0c = M(uint, 0x364);
            ev->f28 = M(uint, 0x194);
            ev->f18 = 0x248dca26;
            ev->f10 = 0;
            ev->f14 = M(void*, 0x98);
            ev->f1c = 0;
            ev->f20 = 0.0f;
            ev->f24 = 0;
            if (((AnimCreatureMgr*)M(void*, 0x360))->HandleAnimatedEvent(ev)) M(uint, 0x198) = 1;
            ev->Release();
        }
    }
    FUN_0057c0e0();
}

// @ 0x0058a5a0
void SP::cAppModeEditorBase_s0058_9ce0::Undo(char postMsg, char isRedoFlag)
{
    if (M(int, 0x188) > 1) {
        ((char*)M(void*, 0x4d8))[0xb] = 1;
        int idx = FUN_00576140();
        if (idx < 6) {
            char* ld = M(char*, 0x1cc);
            if (ld && ld[0x6e]) {
                char* o = *(char**)((char*)this + idx * 20 + 0x508);
                o[0xb] = 1;
            }
        }
        M(int, 0x188)--;
        LocalState* ls = ((LocalState**)M(void*, 0x160))[M(int, 0x188) - 1];
        if (ls) ls->AddRef();

        {
        NameProvider_s0058_9ce0* np = (NameProvider_s0058_9ce0*)((char*)this + 0xc);
        WStr s1(np->GetA());
        WStr s2(np->GetB());
        WStr s3(np->GetC());
        UndoListVec* ul = (UndoListVec*)((char*)this + 0x174);
        uint8_t savedFlag = M(uint8_t, 0x4b4);
        UndoEntry* entry = ((UndoEntry**)M(void*, 0x174))[M(int, 0x188) - 1];
        if (entry) entry->AddRef();

        void* rawRes = operator_new(0xe0, "Editor", 0, 0, 0, 0);
        EditorResource* res = rawRes ? ((EditorResource*)rawRes)->Init() : 0;
        if (res) res->mRefCount++;
        res->CopyFrom(entry);
        ModelMem* mm = M(ModelMem*, 0x98);
        res->mKey = mm->key;
        PrepareAppForNewModel(res);

        np->SetA(s1.mb);
        np->SetB(s2.mb);
        np->SetC(s3.mb);
        M(uint8_t, 0x4b4) = savedFlag;
        SetLocalState(ls);

        UndoEntry* e2 = ul->mpBegin[M(int, 0x188) - 1];
        if (e2) e2->AddRef();
        Out16 tmp;
        uint mt = ((ModelObj*)M(void*, 0x98))->GetModelThing();
        Out16* r = SomeSetup(&tmp, e2, mt, 1);
        M(uint, 0x48) = r->w[0];
        M(uint, 0x4c) = r->w[1];
        M(uint, 0x50) = r->w[2];
        M(uint, 0x54) = r->w[3];
        ((EditorUI_s0058_9ce0*)M(void*, 0x78))->UpdateUIBasedOnModelSaveability();

        if (!sAppProperties_s0058_9ce0->GetDescription(0x55d7ca1)) {
            if (!FUN_004edf40(res->GetThing(), 0)) M(uint, 0x48) |= 0x10;
            else M(uint, 0x48) &= ~0x10u;
        }
        if (M(void*, 0x78)) ((EditorUI_s0058_9ce0*)M(void*, 0x78))->UpdateUIBasedOnModelSaveability();

        if (!isRedoFlag) {
            ul->Resize(M(int, 0x188));
            ((LocalStateVec*)((char*)this + 0x160))->Resize(M(int, 0x188));
        }
        if (postMsg) {
            void* rawEv = operator_new(0x30, "Editor", 0, 0, 0, 0);
            AnimEventInfo_s0058_9ce0* ev = rawEv ? ((AnimEventInfo_s0058_9ce0*)rawEv)->Init() : 0;
            if (ev) ev->AddRef();
            ev->MessagePost(0xb23938bc, 0, M(void*, 0x98), 0, 0, 0.0f, 0, -1, 1.0f);
            if (ev) ev->Release();
        }
        if (isRedoFlag && M(void*, 0x78)) ((EditorUI_s0058_9ce0*)M(void*, 0x78))->EnableRedoButton(true);
        if (e2) e2->Release();
        RcRelease_s0058_9ce0(res);
        if (entry) entry->Release();
        }   // s3, s2, s1 destruct here
        if (ls) ls->Release();
    }
    if (M(void*, 0x78)) ((EditorUI_s0058_9ce0*)M(void*, 0x78))->EnableUndoButton(M(int, 0x188) != 1);
}

// @ 0x0058ac10
bool SP::cAppModeEditorBase::OnKeyDown(unsigned int a, unsigned int b)
{ (void)a; (void)b; return 0; }

// @ 0x0058b650
bool SP::cAppModeEditorBase::OnMouseUp(unsigned int x, float y, float button, unsigned int flags)
{ (void)x; (void)y; (void)button; (void)flags; return 0; }

// @ 0x0058ba60
bool SP::cAppModeEditorBase::OnMouseMoveUpdate(float x, float y, unsigned int a, unsigned int b)
{ (void)x; (void)y; (void)a; (void)b; return 0; }

// @ 0x0058be50
namespace SP {
void cAppModeEditorBase_s0058_be50::HandleSimulationUpdate(float delta1, float delta2)
{
    if (!mIsActive)
        return;

    if (mIdleStopwatch.IsRunning()) {
        int idleTimeout = 2000;
        PropertyListPtr propList;
        if (PropertyManager()->GetPropertyList(0xb55619c2, 0x851d4139, propList))
            GetPropertyAsInt(propList, 0x091756c5, &idleTimeout);
        if (mIdleStopwatch.GetElapsedTime() > idleTimeout) {
            OnIdleTimeout();
            mpEditorUI->UpdateIdleTimeout();
        }
    }

    if (mbStopDeleteEffects) {
        if (mpMainModelWorld && mpMainModelWorld->GetPendingLoadCount() > 0)
            return;
        AutoRefCount_s0058_be50<cSPEditorEffect> effect(EditorEffects()->Get(0xb8deeb8b));
        if (effect)
            effect->Stop(false);
        AutoRefCount_s0058_be50<cSPEditorEffect> deleteEffect(EditorEffects()->Get(mDeleteEffectID));
        if (deleteEffect)
            deleteEffect->Stop(false);
        mbStopDeleteEffects = false;
    }

    float deltaMS = delta2 * 1000.0f;
    int deltaTime = RoundToInt(delta2 * 1000.0f);

    cSPEditorSkinManager_s0058_be50::cSkin* skin;
    if (!(mpAnimCreatureManager && mpSkinManager && (skin = mpSkinManager->GetSkin(1)) != 0)) {
        bool balanced = mpEditorModel->IsModelBalanced();
        if (balanced != mbModelBalanced) {
            mbModelBalanced = balanced;
            if (!balanced)
                StopFade();
        }
    }

    if (mpDeleteValueRollover && mpDeleteValueRollover->IsVisible()) {
        mDeleteValueFadeTime -= delta2;
        if (mDeleteValueFadeTime <= 0.0f)
            mpDeleteValueRollover->Hide();
    }

    if (mpActiveManipulator)
        mpActiveManipulator->Update(deltaMS);

    mbShowCloningRollover = false;
    if (!mpActiveManipulator && (mMouseState & 4) && mMode == kModeBuild)
        mbShowCloningRollover = true;
    if (mpCloningRollover) {
        if (!mbShowCloningRollover && mpCloningRollover->IsVisible()) {
            mpCloningRollover->Hide();
        } else if (mbShowCloningRollover) {
            cSPEditorBlock_s0058_be50* block = GetCloningBlock();
            if (block) {
                int value = GetBlockSellValue(block, 2);
                if (!mpCloningRollover->IsVisible() || value != mpCloningRollover->mValue) {
                    bool canAfford = mpEditorLimits->CanAfford(block);
                    cString_s0058_be50 text(0x496bfb26, 1, L"Copy For ");
                    mpCloningRollover->Show(text.GetText(), value, canAfford);
                    CursorManager_s0058_be50()->SetCursorAttachment(
                        mpCloningRollover ? mpCloningRollover->mCursorAttachment : 0);
                }
            }
        }
    }

    mbShowAsymmetryRollover = false;
    if (!mpActiveManipulator && (mModifierFlags & 0x200) && mMode == kModeBuild)
        mbShowAsymmetryRollover = true;
    if (mpAsymmetryRollover) {
        if (!mbShowAsymmetryRollover && mpAsymmetryRollover->IsVisible()) {
            mpAsymmetryRollover->Hide();
        } else if (mbShowAsymmetryRollover) {
            cSPEditorBlock_s0058_be50* block = GetCloningBlock();
            if (block) {
                if (!mpAsymmetryRollover->IsVisible()) {
                    cString_s0058_be50 text(0x496bfb26, 8, L"Make Asymmetric");
                    mpAsymmetryRollover->Show(L"Make Asymmetric");
                    CursorManager_s0058_be50()->SetCursorAttachment(
                        mpAsymmetryRollover ? mpAsymmetryRollover->mCursorAttachment : 0);
                }
            } else {
                mpAsymmetryRollover->Hide();
            }
        }
    }

    if (mpPhysicsWorld)
        mpPhysicsWorld->UpdatePhysics(deltaTime);

    if (mpActiveHandle && mbPreviewDeformHandle) {
        cSPEditorHandleDeform_s0058_be50* deform = object_cast<cSPEditorHandleDeform_s0058_be50>(mpActiveHandle);
        if (deform && deform->GetEditorBlock()) {
            cSPEditorBlock_s0058_be50* block = deform->GetEditorBlock();
            block->UpdateHandlePreviewDeform(delta2, block->GetIndexForHandle(deform));
        }
    }

    if (mpSelectedPart)
        mpSelectedPart->UpdateEffectsMask();

    uint32_t sellMode = 0;
    GetPropertyAsKeyInstance(mpPropList, 0xd3a86352, &sellMode);
    if (sellMode) {
        bool sellable = false;
        for (uint32_t i = 0; i < mpEditorModel->GetBlockCount(); i++) {
            cSPEditorBlock_s0058_be50* block = mpEditorModel->GetBlock(i);
            if (block->HasAttribute(kAttrHasSellValue) && block->HasAttribute(kAttrSellable)) {
                sellable = true;
                break;
            }
        }
        if (!sellable) {
            if (mpSellBackRollover->IsVisible())
                mpSellBackRollover->Hide();
        } else if (!mpSellBackRollover->IsVisible()) {
            int value = 0;
            if (mpMovingPart)
                value = GetBlockSellValue(mpMovingPart, 1);
            cString_s0058_be50 text(0x496bfb26, 2, L"Sell For ");
            mpSellBackRollover->Show(text.GetText(), value, true);
            CursorManager_s0058_be50()->SetCursorAttachment(
                mpSellBackRollover ? mpSellBackRollover->mCursorAttachment : 0);
        }
    }

    cSPEditorBlock_s0058_be50* movingPart = mpMovingPart;
    if (movingPart && EditorEffects()->GetForBlock(movingPart)) {
        cSPEditorEffect* effect = EditorEffects()->GetForBlock(movingPart);
        if (!effect->IsRunning()) {
            EditorEffects()->Destroy(movingPart);
        } else {
            cSPTransform_s0058_be50 transform;
            effect->GetTransform(&transform);
            transform.SetTranslation(mpMovingPart->GetBBox(0, false, false).GetCenter());
            effect->SetTransform(&transform);
        }
    }

    if (mpVerbIconTray)
        mpVerbIconTray->Update(deltaTime);
    if (mpComplexityMeter) {
        mpComplexityMeter->SetComplexityMeterPercentage(UpdateCurrentComplexityPercent());
        mpComplexityMeter->Update(deltaTime);
    }
    if (mpPaintPaletteUI) {
        cSpeciesProfile_s0058_be50::cInit init;
        cSpeciesProfile_s0058_be50 profile(init, 0);
        if (GetSkin()->mpResource && profile.Update(GetSkin()->mpResource))
            mpPaintPaletteUI->Update(deltaTime, &profile, mCurrentBlockRegion);
        else
            mpPaintPaletteUI->Update(deltaTime, 0, 0);
    }
    if (mpBudget)
        mpBudget->Update(deltaTime);
    if (mpPartsPaletteUI)
        mpPartsPaletteUI->UpdateCategories(deltaTime);
    if (mpPaintCategoriesUI)
        mpPaintCategoriesUI->UpdateCategories(deltaTime);
    if (mpEditorUI)
        mpEditorUI->Update(deltaTime);

    if (mMode == kModeBuild && mbUseSpine && mpSpine) {
        mpSpine->Update(deltaTime, mpEditorModel);
        UpdateSpineVertebra(deltaTime);
    }
    if (mpEditorModel)
        mpEditorModel->Update(deltaTime);
    if (mbDrawSpineDebug && mpSpine)
        mpSpine->DrawPathDebug();

    if (mpSkinManager) {
        if (mMode == kModeBuild)
            mpSkinManager->Update(mpActivePart, false, mTorsoUIState);
        else
            mpSkinManager->UpdatePaintedSkin();
    }

    if (mpAnimEvent) {
        HandleAnimatedEvent(mpAnimEvent);
        mpAnimEvent = 0;
    }

    switch (mMode) {
    case kModeBuild: {
        switch (GetEditorID()) {
        case (int)0xe46c381e: case (int)0x9adf00a9: case (int)0xa56567f7: case (int)0xb7af8ff8: case 0x156276d1:
        case (int)0xfd4902bd: case 0x290adace: case 0x247e2615: case 0x281f5960: case 0x312e9d6a:
        case 0x465c50ba: case 0x37e82da1: case 0x5bf8f774:
        {
            cSPEditorSkinManager_s0058_be50::cSkin* skin;
            if (!(sTestSystem && sTestSystem->IsTestingInProgress()) && (skin = GetSkin()) != 0 &&
                mpVerbIconTray)
                EditorUtils::ComputeCellVerbIcons(skin->mpResource, mpVerbIconTray, mCurrentBlockRegion, -1.0f);
            break;
        }
        case 0x1d2ec0a0: case 0x1d2ec0a4: case 0x1d2ec0a5: case 0x1d2ec0a6: case 0x1d2ec0a7:
        case (int)0xef18a560: case 0x3615a30b:
            if (mpVerbIconTray)
                EditorUtils::ComputeCreatureVerbIcons(mpEditorModel, mpVerbIconTray);
            break;
        case (int)0x8f963dcb: case (int)0x99f87089: case (int)0x9ad7d4aa: case (int)0xc0b74287: case (int)0xf670aa43:
        case 0x1a4e0708: case 0x1f2a25b6: case 0x2a5147a9: case 0x441cd3e6: case 0x449c040f:
        case 0x7d433fad:
            if (mpVerbIconTray) {
                AbilityValueList abilities;
                EditorUtils::ComputeVehicleAbilityValues(mpEditorModel, &abilities);
                VerbIconList icons;
                EditorUtils::ComputeVehicleAbilities(&abilities, &icons, mpEditorModel->mpResource);
                mpVerbIconTray->SetIcons(&icons);
                int count = abilities.size();
                for (int i = 0; i < count; i++) {
                    if (abilities.mpBegin[i].mValue != kInvalidAbilityValue) {
                        EditorUtils::PlayEditorSound(0x1d6253c0, 0x766d2f71, (float)i, 0);
                        EditorUtils::PlayEditorSound(0x1d6253c0, 0x447e8ae5, abilities.mpBegin[i].mValue, 0);
                    }
                }
            }
            break;
        default:
            if (mpVerbIconTray) {
                VerbIconList icons;
                EditorUtils::ComputeVehicleVerbIcons(&icons, mpEditorModel->mpResource);
                mpVerbIconTray->SetIcons(&icons);
            }
            break;
        }

        IWindow_s0058_be50* trayWindow = mpEditorUI->FindWindowByID(0x0630c829);
        if (trayWindow) {
            if (mpVerbIconTray && mpVerbIconTray->GetTrayCount() > 0) {
                const float* src = trayWindow->GetArea();
                struct Area { float left, top, right, bottom; } area;
                area.left = src[0];
                area.top = src[1];
                area.right = src[2];
                area.bottom = src[3];
                float height = mpVerbIconTray->GetTotalHeight();
                area.bottom = area.top + height + 45.0f;
                trayWindow->SetArea(&area.left);
            } else {
                trayWindow->SetFlag(1, false);
            }
            IWindow_s0058_be50* anchor = mpEditorUI->FindWindowByID(0x0760a5d8);
            if (anchor)
                SPUIHelpers::AnchorWindowToWindow(trayWindow, anchor, 0x84, 0);
        }
        break;
    }
    case kModePlay:
        UpdateBabyCreatures(deltaTime);
        mpPlayMode->Update(deltaTime);
        break;
    }

    if (mpVerbIconTray) {
        int trayCount = mpVerbIconTray->GetTrayCount();
        for (int i = 0; i < trayCount; i++) {
            if (mpVerbIconTray->GetTray(i)->GetSoundKey() > 0)
                EditorUtils::PlayEditorSound(0x1d6253c0, mpVerbIconTray->GetTray(i)->GetSoundKey(),
                                             mpVerbIconTray->GetTray(i)->GetTotal(), 0);
        }
    }

    cEditorTactilityManager* tactility = EditorTactilityManager();
    if (tactility)
        tactility->Update(deltaTime);

    cCameraManager_s0058_be50* cameraManager = mpGameModeOwner->GetGameModeManager()->GetCameraManager();
    if (cameraManager) {
        cEditorCameraController* camera = cameraManager->GetCamera(0x029da727);
        if (camera) {
            if (mMode == kModePlay) {
                Vector3_s0058_be50 position;
                if (mpAnimCreatureManager->GetCreaturePosition(mAnimatingCreatureID, &position))
                    camera->SetCameraOffsetPosition(position, false);
            } else {
                camera->SetCameraOffsetPosition(kCameraFocusDefault, true);
                if (sAppProperties_s0058_be50->GetDirectBool(0x31) && !mpActiveManipulator)
                    camera->DoAutoZoom(mpEditorModel, deltaTime);
            }
        }
    }

    if (mpAnimCreatureManager) {
        UpdateAnimatedCreature();
        if (mIsRecordingGIF) {
            uint32_t frameRate = sAppProperties_s0058_be50->GetIntProperty(0x05893ee8);
            uint32_t frameTime = sAppProperties_s0058_be50->GetIntProperty(0x05893ef5);
            mpAnimCreatureManager->Update(frameTime * 1000 / (frameRate * frameRate));
            if (mbCountGIFFrames)
                mGIFFrameCount++;
        } else {
            mpAnimCreatureManager->Update(deltaTime);
        }
    }

    UpdateIdleAnimations(mMouseX, mMouseY, deltaTime);
    OnMouseMoveUpdate(mMouseX, mMouseY, mMouseState, deltaTime);
    UIHints()->Update();
    if (AchievementNotifier())
        AchievementNotifier()->Update();

    if (mpEditorRequest && sAppProperties_s0058_be50->GetBoolProperty(0x05949bf1)) {
        if (mTutorialShown.IsEnd(mTutorialShown.find(mTutorialKey))) {
            mTutorialShown[mTutorialKey] = true;
            ShowTutorial();
        }
    }

    if (mSaveInProgress != kSaveStateNone && mSaveInProgress != kSaveStateDone) {
        ContinueSaveInProgress();
        if (mSaveInProgress == kSaveStateDone) {
            HandleRequestedPostSaveAction();
            mPostSaveAction = 0;
        }
    }

    if (mTransitionMode == kTransitionWaiting) {
        if (mTransitionState == kTransitionWaiting &&
            !mpAnimCreatureManager->IsAnimationPlaying(mAnimatingCreatureID, mTransitionAnimationID))
            mTransitionState = kTransitionDone;
        SendAppSwitchMessage();
    }

    UpdateModelSounds(deltaTime);

    if (mpShadowWorld && mpShadowWorld->GetType() == 0x05e51c99) {
        if (mMode == kModePlay) {
            Vector3_s0058_be50 position;
            if (mpAnimCreatureManager->GetCreaturePosition(mAnimatingCreatureID, &position))
                mpShadowWorld->SetCentreOfInterest(&position, &kShadowDirection);
        } else {
            mpShadowWorld->SetCentreOfInterest(&kCameraFocusDefault, &kShadowDirection);
        }
        Vector3_s0058_be50 cameraPosition;
        App_s0058_be50()->GetRenderer()->GetMainViewer()->GetCameraLocationInfo(&cameraPosition, 0, 0, 0);
        mpShadowWorld->SetEffectiveViewer(&cameraPosition);
        Vector3_s0058_be50 direction = kShadowDirection;
        GetPropertyAsVector3(mpLightingWorld->GetPropertyList(), 0x0100eab8, &direction);
        mpShadowWorld->SetDirection(&direction);
        mpShadowWorld->Update();
    }

    SetCursorBasedOnModeModifiers();
}
}  // namespace SP

// @ 0x0058cee0
int SP::cAppModeEditorBase_s0058_cee0::LoadModel(int a, int b, int c, int d, int e, int f)
{ (void)a; (void)b; (void)c; (void)d; (void)e; (void)f; return 0; }

// @ 0x0058d1c0
void SP::cAppModeEditorBase::NewModel(bool a)
{ (void)a; }

// @ 0x0058d430
void cEditorCheat::Execute(EA::ArgScript::cArguments_s0058_d430* args)
{
    AutoRefCount_s0058_d430<cEditorCheat> self(this);
    int count;
    const char** argv = args->MainArguments(count, 0, 0x7fffffff);

    if (count == 2 && !_stricmp(argv[0], "load")) {
        ResourceKey_s0058_d430 key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (!SPKeyFromName(&key, argv[1], mEditorApp->mModelType, 0xffffffff)) {
            EA::ArgScript::Output(mParser, "unable to get resource key from filename\n");
            return;
        }
        FixupModelKey(key);
        AutoRefCount_s0058_d430<IResource> res;
        cEditorModelResource* model;
        if (!GetManager_s0058_d430()->GetResource(&key, res.AsPointer(), 0, 0, 0, 0) || !res ||
            !(model = (cEditorModelResource*)res->Cast(0x3c609f8))) {
            EA::ArgScript::Output(mParser, "unable to load model resource\n");
        } else {
            uint32_t config = GetConfigFromModelType(model->mModelType);
            if (mEditorApp->GetEditorConfig() != config) {
                EA::ArgScript::Output(mParser, "switching editor config...\n");
                MessageBasicRC5 msg(0);
                msg.mData[0] = config;
                mEditorApp->mMessageListener.HandleMessage(0x22d308b, &msg);
            }
            string8 name;
            SPNameFromKey(&key, &name, 0);
            EA::ArgScript::Output(mParser, "loading model '%s'\n", name.c_str());
            mEditorApp->LoadModel(key, kDefaultLoadParams, 0);
        }
    } else if (count >= 1 && count <= 2 && !_stricmp(argv[0], "timing")) {
        if (count == 1)
            sTimingEnabled = !sTimingEnabled;
        else if (count == 2 && !_stricmp(argv[1], "on"))
            sTimingEnabled = true;
        else if (count == 2 && !_stricmp(argv[1], "off"))
            sTimingEnabled = false;
        EA::ArgScript::Output(mParser, sTimingEnabled ? "Timing: ON\n" : "Timing: OFF\n");
    } else if (count == 1 && !_stricmp(argv[0], "zcorp")) {
        EA::ArgScript::Output(mParser, "ZCorp Score: %d\n", mEditorApp->ScoreCreatureForZCorp());
    } else if (count == 2 && !_stricmp(argv[0], "rename")) {
        mEditorApp->GetModel()->SetName(ConvertToString16_s0058_d430(argv[1], -1).c_str());
        EA::ArgScript::Output(mParser, "model renamed to '%s'\n", argv[1]);
    } else if (count >= 1 && count <= 2 && !_stricmp(argv[0], "save")) {
        ResourceKey_s0058_d430 key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (count > 1)
            SPKeyFromName(&key, argv[1], 0, 0);
        else
            key.instance = CreationIDFromModel(mEditorApp->GetModel()->GetCreationID());
        key.type = mEditorApp->mModelType;
        key.group = GetModelGroup(key.type);
        mEditorApp->SaveModel(&key, 0);
    } else if (count >= 1 && count <= 2 && !_stricmp(argv[0], "savebinary")) {
        ResourceKey_s0058_d430 key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        if (count > 1)
            SPKeyFromName(&key, argv[1], 0, 0);
        else
            key.instance = CreationIDFromModel(mEditorApp->GetModel()->GetCreationID());
        key.type = mEditorApp->mModelType;
        key.group = GetModelGroup(key.type);
        ModelResourceRef ref(new("Editor", 0, 0, 0, 0) cSPEditorModelResource());
        cSPEditorModelResource* res = ref.mpObject;
        mEditorApp->GetModel()->SaveResource(res);
        res->mKey = key;
        key.type = 0x1a99b06b;
        GetManager_s0058_d430()->WriteResource((IResource*)res, 0, GetSaveArea_s0058_d430(mEditorApp->mSaveAreaID), 0, &key);
        res->Release();
    } else if (count == 1 && !_stricmp(argv[0], "dumpPalettes")) {
        if (!sValidityInitialized)
            InitializeValidityData();
        DumpPalettes();
    } else if (count == 2 && !_stricmp(argv[0], "validate")) {
        ResourceKeyFilter filter;
        ResourceKeyVector keys;
        ResourceKey_s0058_d430 key;
        key.instance = 0;
        key.type = 0;
        key.group = 0;
        SPKeyFromName(&key, argv[1], 0xffffffff, 0xffffffff);
        filter.mInstance = key.instance;
        filter.mGroup = key.group;
        filter.mType = key.type;
        GetManager_s0058_d430()->GetResourceKeyList(&keys, &filter, 0);
        if (keys.empty())
            keys.push_back(key);
        int numKeys = keys.size();
        string16 fileName;
        for (int i = 0; i < numKeys; ++i) {
            ResourceKey_s0058_d430& modelKey = keys[i];
            GetManager_s0058_d430()->GetFileName(&modelKey, &fileName);
            GetResourceDisplayName(&modelKey, &fileName, 0);
            FixupModelKey(modelKey);
            AutoRefCount_s0058_d430<IResource> res;
            cEditorModelResource* model;
            if (!GetManager_s0058_d430()->GetResource(&modelKey, res.AsPointer(), 0, 0, 0, 0) || !res ||
                !(model = (cEditorModelResource*)res->Cast(0x3c609f8))) {
                EA::ArgScript::Output(mParser, "unable to load model resource\n");
                return;
            }
            ResourceKey_s0058_d430 nameKey = model->mKey;
            nameKey.type = 0x30bdee3;
            cLocalizedName* name = 0;
            AutoRefCount_s0058_d430<IResource> nameRes;
            if (GetManager_s0058_d430()->GetResource(&nameKey, nameRes.AsPointer(), 0, 0, 0, 0))
                name = nameRes ? (cLocalizedName*)nameRes->Cast(0x30bdee3) : 0;
            EA::ArgScript::Output(mParser, "Validating filename: '%ls', resource name: ", fileName.c_str());
            if (name)
                EA::ArgScript::Output(mParser, "'%ls'\n", name->GetText());
            else
                EA::ArgScript::Output(mParser, "<No Name>\n");

            ValidityBits result = CalculateValidity(model, kValidityAll, 0);
            if (!IsValid(result, kValidityLoadable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Loadable test for the following reasons:\n");
                ReportFailures(kValidityLoadable, result);
            }
            if (!IsValid(result, kValidityEditable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Editable test for the following reasons:\n");
                ReportFailures(kValidityEditable, result);
            }
            if (!IsValid(result, kValidityPlayable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Playable test for the following reasons:\n");
                ReportFailures(kValidityPlayable, result);
            }
            if (!IsValid(result, kValidityPollinatable)) {
                EA::ArgScript::Output(mParser, "  Model failed the Pollinatable test for the following reasons:\n");
                ReportFailures(kValidityPollinatable, result);
            }
            if (!IsValid(result, kValidityWarning)) {
                EA::ArgScript::Output(mParser, "  Model failed the Warning test for the following reasons:\n");
                ReportFailures(kValidityWarning, result);
            }
            if (IsValid(result, kValidityAll))
                EA::ArgScript::Output(mParser, "  Model is valid.\n");
        }
    } else if (count == 1 && !_stricmp(argv[0], "dumpGeomInfo")) {
        for (int index = 0x61; index < 0x67; ++index) {
            AutoRefCount_s0058_d430<cPropertyList> props(new("Editor", 0, 0, 0, 0) cPropertyList());
            uint32_t groupBits = (uint32_t)(uint8_t)index << 16;
            props->mResourceKey.instance = 0x6cc3c0c9;
            props->mResourceKey.type = 0xb1b104;
            props->mResourceKey.group = groupBits | 0x40000100;
            ResourceKeyFilter filter;
            filter.mGroup = groupBits | 0x40006000;
            filter.mType = 0xb1b104;
            ResourceKeyVector keys;
            GetManager_s0058_d430()->GetResourceKeyList(&keys, &filter, 0);
            FloatVector values(keys.size());
            AutoRefCount_s0058_d430<cPropertyList> geomProps;
            int numKeys = keys.size();
            for (int i = 0; i < numKeys; ++i) {
                if (!PropertyManager_s0058_d430()->GetPropertyList(keys[i].instance, keys[i].group, geomProps.AsPointer()))
                    continue;
                ResourceKey_s0058_d430 modelKey;
                modelKey.instance = 0;
                modelKey.type = 0;
                modelKey.group = 0;
                if (!GetPropertyAsKey(geomProps.get(), 0xf9efbb, &modelKey))
                    continue;
                AutoRefCount_s0058_d430<IResource> res;
                if (GetManager_s0058_d430()->GetResource(&modelKey, res.AsPointer(), 0, 0, 0, 0)) {
                    VertexVector geometry;
                    ReadGeometry(res ? res->Cast(0x2f4e681b) : 0, &geometry);
                    values[i] = ComputeGeometryMetric(&geometry);
                }
            }
            SetPropertyKeys(props.get(), 0x66f235b, keys.size(), keys.mpBegin);
            SetPropertyFloats(props.get(), 0x66f235c, values.size(), values.mpBegin);
            SavePropertyList(props.get(), GetSaveArea_s0058_d430(0x11ac19e), 0);
        }
        EA::ArgScript::Output(mParser, GetDescription(1));
    }
}

// @ 0x00591fa0
namespace SP {
bool cAppModeEditorBase_s0059_1fa0::HandleMessage(uint32_t messageID, void* pMessage)
{
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
        ResourceKey_s0059_1fa0 key;
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
        const wchar_t* dir = GetSaveArea_s0059_1fa0(mSaveDirectory)->GetPath();
        wchar_t fileName[0x100];
        SplitPath(mEditorModel->GetFileName(), 0, 0, fileName, 0, 4);
        eastl::wstring_s0059_1fa0 path;
        WStr_Format(&path, L"%ls/%ls.xsf", dir, fileName);
        ResourceKey_s0059_1fa0 key = mEditorModel->mKey;
        ExportBakedModelToXMF(mEditorModel, dir, &key);
        if (mUI) {
            eastl::wstring_s0059_1fa0 text;
            WStr_Format(&text, L"Model saved to %ls", path);
            mUI->ShowGeneralMessage(text.c_str());
        }
        MessageServer_s0059_1fa0()->PostMSG(0x29d57f4, 0, 0);
        return true;
    }

    case 0x044ef2b8:
        if (mMode == 1) {
            EnterPaintMode(true);
            cSPPaletteUI_s0059_1fa0* paletteUI = mpPaintPaletteUI;
            if (paletteUI && paletteUI->IsPaintByNumber()) SetRolloverBlock(0, -1);
        }
        return false;

    case 0x0462c656:
        mTransitionAnimation = 0;
        return true;

    case 0x04519b5f:
        if (App_s0059_1fa0()->GetActiveModeID() == 0xdbdba1) {
            cSPEditorUI_s0059_1fa0* ui = mUI;
            if (ui) ui->FindWindowByID(0xffffffff)->SetFlag(1, true);
            if (gFlagTable->mpFlags[0x46] != 0) ToggleDebugDraw(0);
        }
        return false;

    case 0x047d7cc6: {
        if (AppSystem()->IsFullScreen()) AppSystem()->ToggleFullScreenWindowed();
        cSPEditorUI_s0059_1fa0* ui = mUI;
        ui->FindWindowByID(0xffffffff)->SetFlag(1, true);
        UIHints_s0059_1fa0()->SetEnabled(true, true);
        return false;
    }

    case 0x048e5911: {
        MsgReplaceRollover* msg = (MsgReplaceRollover*)pMessage;
        float cost = msg->mCost;
        cSPEditorBlock_s0059_1fa0* block = msg->mpBlock;
        if (mReplaceBlockRollover) {
            cString_s0059_1fa0 text(0x496bfb26, 7, L"Replace for ");
            mReplaceBlockRollover->Show(text.GetText((int)cost, true));
            const Rect& area = WindowManager_s0059_1fa0()->GetMainWindow()->GetArea();
            float offsetX = (area.x2 - area.x1) * 0.0125f;
            Vector3_s0059_1fa0 pos = gRolloverDefaultPos;
            float offsetY = (area.y2 - area.y1) * -0.016666668f;
            if (block) {
                BoundingBox_s0059_1fa0 bbox;
                const BoundingBox_s0059_1fa0* bb = block->GetBBox(&bbox, 0, 0, 0);
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
            AutoRefCount_s0059_1fa0<cSPEditorAnimatedEventInfo_s0059_1fa0> info(new ("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo_s0059_1fa0());
            info->MessageSend(0x248dca26, 0, mEditorModel, mBrainLevel, 0, 0.0f, 0, ability->mAnimationID, 1.0f);
        } else if (ability && !ability->mAnimationID) {
            // debug report (the assert that consumed it is compiled out)
            eastl::string_s0059_1fa0 text;
            text.sprintf("Ability %ls does not have an animation.\n", ability->GetName(0).c_str());
        }
        return false;
    }

    case 0x05132389: {
        // a model file was dropped on the editor window
        ResourceKey_s0059_1fa0** ppKey = ((MsgFileDrop*)pMessage)->mppKey;
        ResourceKey_s0059_1fa0 key;
        key.instanceID = 0;
        key.typeID = 0;
        key.groupID = 0;
        if (ppKey) key = **ppKey;
        if (!mIsActive) return false;
        bool browserOpen;
        if (AssetBrowser_s0059_1fa0() && AssetBrowser_s0059_1fa0()->mbVisible) browserOpen = true;
        else browserOpen = false;
        bool paletteActive = false;
        if (mUI->IsPartsPaletteActive() || mUI->IsPaintPaletteActive() || gFlagTable->IsSet(0x678f3f1)) paletteActive = true;
        if (browserOpen || !paletteActive) return false;

        if (mMode == 2) {
            if (!gFlagTable || !gFlagTable->IsSet(0xd7f24dcf) || IsPaintDisabled()) {
                mPlayMode->ShowPaintDisabled();
                return false;
            }
            IResourceManager_s0059_1fa0* resMgr = GetManager_s0059_1fa0();
            AutoRefCount_s0059_1fa0<Resource_s0059_1fa0> res;
            if (!resMgr) return false;
            if (resMgr->GetResource(key, res.AsPPTypeParam(), 0, 0, 0, 0)) {
                cEditorResource_s0059_1fa0* edRes = interface_cast_cEditorResource(&res);
                if (edRes) {
                    Flags128 required;
                    edRes->GetRequiredValidity(&required, GetModelValidity(), true);
                    if (!IsValiditySatisfied(required, GetModelValidity())) {
                        SetValidityFlags(MakeFlags128(0x4000000), MakeFlags128(0x4000000));
                        return true;
                    }
                    RemapTypeId(edRes->mTypeID);
                    if (IsResourceOfOtherEditor(edRes)) {
                        UIHints_s0059_1fa0()->ShowHint(0xffc453c6);
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
        if (mUI->IsEditorUIVisible() && WindowManager_s0059_1fa0()->GetModalWindow() == 0 && ppKey) mUI->HandleFileDrop(key);
        return false;
    }

    case 0x051cc0b8: {
        SetMode(0, true);
        cSPEditorUI_s0059_1fa0* ui = mUI;
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
        cSPPaletteUI_s0059_1fa0* paletteUI = mpPartsPaletteUI;
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
        MessageServer_s0059_1fa0()->MessageSend(0x153c326, 0, 0, 0);
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
        cSPEditorBlock_s0059_1fa0* block = ((MsgBlock*)pMessage)->mpBlock;
        uint32_t effectID = 0;
        GetPropertyAsKeyInstance(mCurrentConfigProperties, 0xd3a86352, &effectID);
        if (!block || !effectID) return false;
        BoundingBox_s0059_1fa0 bb;
        block->GetBBox(&bb, 0, 0, 0);
        Vector3_s0059_1fa0 center;
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
        MessageServer_s0059_1fa0()->PostMSG(0x14418c3f, &out, 0);
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
        MessageServer_s0059_1fa0()->PostMSG(0x7aa519dc, &out, 0);
        return true;
    }

    case 0x90a03fdf: {
        MsgBrain* msg = (MsgBrain*)pMessage;
        mpEditorLimits->SetBrainLevel(0, msg->mBrainLevel);
        InitBrain(msg->mInitLevel);
        cEditorLaunchData_s0059_1fa0* launch = mLaunchData;
        if (launch && launch->mbHasBrain) SetupBrainFromLaunchData();
        InitializeUndoList();
        return false;
    }

    case 0x7f18f481: {
        // a block is being removed: drop every reference to it
        cSPEditorBlock_s0059_1fa0* block = ((MsgBlock*)pMessage)->mpBlock;
        if (block == mRolloverBlock) SetRolloverBlock(0, -1);
        if (block == mToBeSelectedBlock) mToBeSelectedBlock.Clear();
        if (block == mSelectedBlock) SetSelectedBlock(0, true);
        return false;
    }

    case 0x90e08f60: {
        // paint a region with a color (or a whole paint theme)
        MsgPaint* msg = (MsgPaint*)pMessage;
        Vector3_s0059_1fa0 color;
        ColorFromRGB(&color, msg->mColor);
        cSPEditorSkinManager_s0059_1fa0* skinMgr = mSkinManager;
        if (skinMgr && skinMgr->GetSkin(1) && mEditorModel) {
            int region = msg->mRegion;
            if (region == -1) region = 0;
            else if (region < 0 || region > 2) goto playSound;
            mEditorModel->SetRegionColor(region, color);
            mbModelPainted = true;
            AddUndoState(false, false);
            cSPEditorModel_s0059_1fa0* model = mEditorModel;
            if (!(mSaveSkinManager && mSaveSkinManager->IsBusy()) && model && mSkinManager)
                mSkinManager->RepaintModel(model);
        } else if (mCurrentPaintTheme && mEditorModel && msg->mRegion != -1) {
            int region = msg->mRegion;
            bool useTheme = msg->mbTheme != 0;
            if (useTheme) {
                cCategoryInfo info;
                mpPaintPaletteUI->GetCategoryInfo(&info);
                if (info.mPropID) {
                    AutoRefCount_s0059_1fa0<cSPEditorPaintTheme_s0059_1fa0> theme(new ("Editor", 0, 0, 0, 0) cSPEditorPaintTheme_s0059_1fa0());
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
        mLaunchData = (cEditorLaunchData_s0059_1fa0*)pMessage;
        if (mbPreserveLineage) {
            mParentModelKey = mLaunchData->mKey;
        } else {
            mParentModelKey.instanceID = 0;
            mParentModelKey.typeID = 0;
            mParentModelKey.groupID = 0;
        }
        IWindow_s0059_1fa0* mainWin = WindowManager_s0059_1fa0()->GetMainWindow();
        mnModelStartTime = static_cast<cSPUIMainWin_s0059_1fa0*>(mainWin)->GetMouseRefs();
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
        Vector3_s0059_1fa0 pos;
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

        Vector3_s0059_1fa0 camPos, camDir;
        App_s0059_1fa0()->GetViewer()->GetCameraLocationInfo(&camPos, &camDir, 0, 0);
        Plane plane;
        plane.n.x = -camDir.x;
        plane.n.y = -camDir.y;
        plane.n.z = -camDir.z;
        Vector3_s0059_1fa0 p;
        p.x = camPos.x + height * camDir.x;
        p.y = camPos.y + camDir.y * height;
        p.z = camPos.z + camDir.z * height;
        plane.d = -(p.x * plane.n.x + p.z * plane.n.z + p.y * plane.n.y);

        Vector3_s0059_1fa0 rayOrigin, rayDir;
        App_s0059_1fa0()->GetViewer()->GetCameraRayOrigin(&rayOrigin, &rayDir);
        Vector3_s0059_1fa0 toPoint;
        toPoint.x = pos.x - rayOrigin.x;
        toPoint.y = pos.y - rayOrigin.y;
        toPoint.z = pos.z - rayOrigin.z;
        Vector3_s0059_1fa0 normalized;
        rayDir = *Vector3_Normalize(&normalized, &toPoint);
        float t;
        if (IntersectRayPlane(&rayOrigin, &rayDir, &plane, &t)) {
            AutoRefCount_s0059_1fa0<IVisualEffect> effect;
            EffectsManager_s0059_1fa0()->CreateVisualEffect(0xa0b518b8, 0, effect.AsPPTypeParam());
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
                AutoRefCount_s0059_1fa0<cEffectText> text(new ("Editor", 0, 0, 0, 0) cEffectText());
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

// @ 0x005ba060
namespace SP {
cSPEditorManipulation56::cSPEditorManipulation56()
: m1c(0) {
  mBlock = 0;
  mVec.mpBegin = 0;
  mVec.mpEnd = 0;
  mVec.mpCapacity = 0;
  mV3c.x = 0.0f;
  mV3c.y = 0.0f;
  mV3c.z = 0.0f;
  m89 = false;
  m8a = false;
  mChangedObject = false;
}
}  // namespace SP
