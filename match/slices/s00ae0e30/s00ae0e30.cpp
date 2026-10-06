// Slice s00ae0e30: the single function in this slice is
//   0x00AE0E30  SP::cCinematicManager::HandleMessage  (8164 bytes, __thiscall, ret 8)
//
// Identification: the function sits in slot 1 of the primary vtable 0x0145B8D0 of the
// object whose constructor/destructor (0x00ADE680) also installs 0x0145B880/0x0145B87C;
// the RTTI-less class-name string right after that vtable is L"cCinematicManager".
// The dev-build PDB (SP::cCinematicManager, size 0x398) and its member names match the
// retail offsets used here with a +4 shift after mActionDataList (retail is 0x3C8 bytes).
// The dev body (0x004A28C0, 7709 bytes) is SecuROM-encrypted, so the source below was
// reconstructed from the retail disassembly alone.
//
// Module flags: SSE scalar math without cvtss2sd and no EH frame although locals have
// destructors -> /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define VP(n) virtual void vpad_##n();

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

// ---------------------------------------------------------------------------
// Math types (PODs: copies are plain dword moves in the original)
// ---------------------------------------------------------------------------
struct Vector3 {
    float x, y, z;

    Vector3() {}
    Vector3(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vector3 operator-(const Vector3& b) const { return Vector3(x - b.x, y - b.y, z - b.z); }
    float SquaredLength() const { return x * x + y * y + z * z; }
};
struct Quaternion {
    float x, y, z, w;
};
struct Matrix3 {
    float m[9];
};

extern Vector3 g_Vector3Zero;      // 0x0167A548
extern Vector3 g_Vector3Up;        // 0x0167A600
extern float g_DegToRad;           // 0x0167A5FC
extern uint32_t g_InvalidModeID;   // 0x015663EC

bool Vector3_NotEqual(const Vector3* a, const Vector3* b);              // 0x0041DD30
bool Vector3Equal(const Vector3* a, const Vector3* b);                  // 0x004232C0
Matrix3 Matrix3FromQuaternion(const Quaternion& q);                     // 0x004A9B40
Quaternion QuaternionFromMatrix33(const Matrix3& m, float eps);         // 0x00472B80
Vector3 RotateVectorByQuaternion(const Vector3& v, const Quaternion& q);// 0x0059AED0
uint32_t SPIDFromName(const char* name);                                // 0x00571CF0
void SetGlobalProperty(int id, float value);                            // 0x005CA880
void StopAudioInstance(uint32_t instanceID, int flags);                 // 0x00572020
uint32_t NewAudioInstanceID();                                          // 0x00A34E90
void PlayCinematicSound(uint32_t soundID, uint32_t instanceID);         // 0x00435ED0
void EndModal(void* window, int a, int b);                              // 0x00809C50
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d); // 0x00F473A0

// Out-of-line copy (0x00572600, an ICF alias of RectT<float>::operator=) used when the
// quaternion returned by QuaternionFromMatrix33 is passed on by value.
struct QuaternionArg {
    float x, y, z, w;
    QuaternionArg(const Quaternion& q);                              // 0x00572600
};

// The engine transform (cTransform / Swarm transform message): flags, change count,
// offset, scale, rotation.
struct cTransform {
    uint16_t mFlags;       // +0x00
    uint16_t mChanges;     // +0x02
    Vector3 mOffset;       // +0x04
    float mScale;          // +0x10
    Matrix3 mRotation;     // +0x14

    cTransform();                                    // 0x00434040
    void SetOffset(const Vector3& v);                // 0x00571D40 (out of line here)
    void PreRotateX(float radians);                  // 0x005A2D90
    void RotateZ(float radians);                     // 0x007D1AC0
    void RotateY(float radians);                     // 0x006B9050

    void SetOffsetInline(const Vector3& v) { mOffset = v; mFlags |= 4; mChanges++; }
    void SetRotation(const Matrix3& m) { mRotation = m; mFlags |= 2; mChanges++; }
    void AddOffset(const Vector3& v)
    {
        mFlags |= 4;
        mChanges++;
        mOffset.x += v.x;
        mOffset.y += v.y;
        mOffset.z += v.z;
    }
};

// A second transform type with the same layout (constructor 0x00409930).
struct Transform {
    uint16_t mFlags;
    uint16_t mChanges;
    Vector3 mOffset;       // +0x04
    float mScale;          // +0x10
    Matrix3 mRotation;     // +0x14 (row 1 at +0x20)

    Transform();                                     // 0x00409930
    void SetRotation(const Matrix3& m) { mRotation = m; }
    Vector3 GetRow1() const
    {
        Vector3 r;
        r.x = mRotation.m[3];
        r.y = mRotation.m[4];
        r.z = mRotation.m[5];
        return r;
    }
};

// ---------------------------------------------------------------------------
// Simulator objects
// ---------------------------------------------------------------------------
struct cModelInfo {
    uint32_t pad0;
    uint32_t mFlags;       // +0x04
};

class cSpatialObject {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4) VP(5) VP(6) VP(7) VP(8) VP(9) VP(10)
    virtual const Vector3* GetPosition();                            // +0x2C
    VP(12) VP(13) VP(14) VP(15) VP(16)
    virtual void SetPositionOrientation(const Vector3& p, const Quaternion& q); // +0x44
    VP(18) VP(19) VP(20) VP(21) VP(22) VP(23) VP(24) VP(25) VP(26) VP(27) VP(28)
    VP(29) VP(30) VP(31) VP(32) VP(33) VP(34) VP(35) VP(36) VP(37) VP(38) VP(39)
    VP(40) VP(41) VP(42)
    virtual cModelInfo* GetModelInfo();                              // +0xAC
    VP(44) VP(45) VP(46)
    virtual int AddRef();                                            // +0xBC
    virtual int Release();                                           // +0xC0
    VP(49) VP(50) VP(51) VP(52) VP(53) VP(54) VP(55) VP(56) VP(57) VP(58)
    virtual void UpdateModelTransform();                             // +0xEC
};

// AutoRefCount<cSpatialObject>: constructor out of line (0x00AD72E0), release inline.
struct SpatialObjectPtr {
    cSpatialObject* mpObject;
    SpatialObjectPtr(cSpatialObject* p);                             // 0x00AD72E0
    ~SpatialObjectPtr()
    {
        if (mpObject)
            mpObject->Release();
    }
};

struct SpatialObjectPtrVector {
    void push_back(const SpatialObjectPtr& p);                       // 0x00AFC470
};

// Behaviour slot returned by the creature's action list (0x00BC97F0).
struct cCreatureAction {
    uint32_t pad[3];
    float mRadius;         // +0x0C
    float mCenterX;        // +0x10
    float mCenterY;        // +0x14
    float mCenterZ;        // +0x18
    uint32_t mFlags;       // +0x1C
};

struct cCreatureActionList {
    cCreatureAction* Add(int a, uint32_t type, float maxDist, int b); // 0x00BC97F0
};

struct cCreatureMotive {
    uint32_t pad[2];
    cCreatureActionList mActions;    // +0x08
};

class cCreatureBase {
public:
    char pad0[0xC0];
    cSpatialObject mSpatial;         // +0xC0 (secondary base)
    char padC4[0x135 - 0xC4];
    bool mbIsAlive;                  // +0x135
    char pad136[0xB4C - 0x136];
    cCreatureMotive* mpMotive;       // +0xB4C

    void MoveToPointAtSpeed(int mode, const Vector3& p, float speed, float accel); // 0x00C1C1D0
};

struct CreatureVector {
    cCreatureBase** mpBegin;
    cCreatureBase** mpEnd;
    int size() const { return (int)(mpEnd - mpBegin); }
};

struct cGameObject {
    char pad0[0x34];
    cSpatialObject mSpatial;         // +0x34
};

struct GameObjectVector {
    cGameObject** mpBegin;
    cGameObject** mpEnd;
    cGameObject** mpCapacity;
    uint32_t mAllocator;
    GameObjectVector(const GameObjectVector& other);                 // 0x00BA95A0
    ~GameObjectVector();                                             // 0x00AE6970
    int size() const { return (int)(mpEnd - mpBegin); }
};

class cNounManager {
public:
    CreatureVector& GetCreatures();                                  // 0x00ACE2F0
    CreatureVector& GetAnimals();                                    // 0x00ACD9A0
    GameObjectVector& GetGameObjects();                              // 0x00AE0DD0
    GameObjectVector& GetObjectsOfType(uint32_t type);               // 0x00AE0E00
};

class cPlanetModel {
public:
    char pad0[0x24];
    void* mpTerrain;                                                 // +0x24
    Quaternion BuildSurfaceOrientation(const Vector3& p);            // 0x00B7F190
    Quaternion GetOrientation(const Vector3& p, const Quaternion& q);// 0x00B7F1F0
    Vector3 ProjectToSurface(const Vector3& p);                      // 0x00B81630
    Vector3 GetSurfacePoint(const Vector3& p, int flags);            // 0x00B82B40
};

class cGameTimeManager {
public:
    void IncPauseGate(uint32_t id);                                  // 0x00B32220
    void DecPauseGate(uint32_t id);                                  // 0x00B32250
};

class cMessageServer {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4)
    virtual void PostMessage(uint32_t id, void* msg, void* p);       // +0x14
};

namespace Swarm {
class cIVisualEffect {
public:
    VP(0) VP(1)
    virtual void Start(int flags);                                   // +0x08
    virtual void Stop(int hardStop);                                 // +0x0C
    VP(4) VP(5)
    virtual void SetTransform(const cTransform& t);                  // +0x18
};
}

struct VisualEffectPtr {
    Swarm::cIVisualEffect* mpObject;
    Swarm::cIVisualEffect** AsPPTypeParam();                         // 0x00A16F40
};

class cEffectsManager {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4) VP(5) VP(6) VP(7) VP(8) VP(9) VP(10)
    virtual bool CreateVisualEffect(uint32_t id, int flags, Swarm::cIVisualEffect** out); // +0x2C
    VP(12) VP(13) VP(14) VP(15) VP(16) VP(17) VP(18) VP(19) VP(20) VP(21) VP(22)
    VP(23) VP(24) VP(25) VP(26) VP(27) VP(28) VP(29) VP(30) VP(31) VP(32) VP(33)
    VP(34) VP(35) VP(36) VP(37)
    virtual void SetOption(int option, bool value);                  // +0x98
};

class cLocaleManager {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4)
    virtual const wchar_t* GetLocale();                              // +0x14
};

class cAppSystem {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4) VP(5) VP(6) VP(7) VP(8) VP(9) VP(10) VP(11)
    VP(12) VP(13) VP(14) VP(15) VP(16) VP(17) VP(18) VP(19)
    virtual bool IsDemoMode();                                       // +0x50
};

class cAudioSystem {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4) VP(5) VP(6) VP(7) VP(8) VP(9) VP(10)
    virtual void StopInstance(uint32_t instanceID);                  // +0x2C
};

namespace SP {
cMessageServer* MessageServer();                                     // 0x0067DCC0
cEffectsManager* EffectsManager();                                   // 0x0067DDD0
cLocaleManager* LocaleManager();                                     // 0x0067DE40
cAppSystem* AppSystem();                                             // 0x0067DD00
cNounManager* NounManager();                                         // 0x00B3D300
cPlanetModel* PlanetModel();                                         // 0x00B3D350
cGameTimeManager* GameTimeManager();                                 // 0x00B3D380
}
namespace EA { namespace Audio { cAudioSystem* GetSystemAT(); } }   // 0x00A206F0

// eastl::fixed_string<wchar_t,16>
struct LocaleString {
    uint32_t mData[0x34 / 4];
    LocaleString(const wchar_t* s);                                  // 0x00696230
    void DeallocateSelf();                                           // 0x0057CB80
    ~LocaleString() { DeallocateSelf(); }
};
bool operator==(const LocaleString& a, const wchar_t* b);            // 0x006AB760

// SP::cString (localized text)
struct cString {
    uint32_t mData[0x20 / 4];
    cString(uint32_t tableID, uint32_t instanceID, const wchar_t* fallback); // 0x006B5770
    ~cString();                                                      // 0x006B5240
    const wchar_t* GetText();                                        // 0x006B55C0
};

// UI window used by the tutorial text panel.
class IWindow {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4) VP(5) VP(6) VP(7) VP(8) VP(9) VP(10) VP(11)
    VP(12) VP(13) VP(14) VP(15) VP(16) VP(17) VP(18) VP(19) VP(20) VP(21) VP(22)
    VP(23) VP(24) VP(25) VP(26) VP(27) VP(28) VP(29) VP(30)
    virtual void SetFlag(int flag, bool value);                      // +0x7C
    virtual void SetCaption(const wchar_t* text);                    // +0x80
};

struct cSPUILayout {
    void SetVisibility(bool visible);                                // 0x00810590
};

class cSPTutorialText {
public:
    char pad0[0x10];
    cSPUILayout* mpLayout;   // +0x10
    IWindow* mpTextWindow;   // +0x14
    uint32_t pad18;
    IWindow* mpButtonWindow; // +0x1C
    char pad20[0x48 - 0x20];
    IWindow* mpContinueWindow; // +0x48
    void* mpModalWindow;     // +0x4C
    uint32_t pad50;
    bool mbModal;            // +0x54

    void SetText(const wchar_t* text);                               // 0x00AD7610
    void Show(bool show);                                            // 0x00AD7640
    void ShowTimed(const wchar_t* text, float duration, int a, int b, float fade); // 0x00AD7670
    void Reset();                                                    // 0x00AD76C0
    void SetMode0(bool b);                                           // 0x00AD7790
    void SetMode1(bool b);                                           // 0x00AD77C0
    void SetMode2(bool b);                                           // 0x00AD7810
    void SetMode3(bool b);                                           // 0x00AD7860
    void SetMode4(bool b);                                           // 0x00AD78B0
    void Hide(bool b);                                               // 0x00AD7900
    void SetModal(bool b);                                           // 0x00AD87D0

    __forceinline void EndModalIfNeeded()
    {
        if (mbModal) {
            EndModal(mpModalWindow, 0, 0);
            mbModal = false;
        }
    }
};

class cSPUISpace {
public:
    static cSPUISpace* Get();                                        // 0x010666A0
    void ShowForTutorial(uint32_t id);                               // 0x01066E30
};

// Camera controller used by the cinematics.
class cGameCinematicsCameraController {
public:
    char pad0[0x108];
    bool mb108;            // +0x108
    bool mb109;            // +0x109
    bool mb10a;            // +0x10A
    bool mb10b;            // +0x10B

    void Stop();                                                     // 0x00EB2F50
    void SetDistance(float d);                                       // 0x00EB30A0
    void SetOrientation(Quaternion q);                               // 0x00EB30D0
    void SetOrientationArg(QuaternionArg q);                         // 0x00EB30D0
    void SetUp(Vector3 v);                                           // 0x00EB3160
    void Apply();                                                    // 0x00EB3190
    void SetFOV(float f);                                            // 0x00EB31D0
    void SetMode(uint32_t mode);                                     // 0x00EB3C70
    void SetPath(const Vector3* points, int count, Vector3 offset);  // 0x00EB7040
    void SetFollowTerrain(bool b);                                   // 0x0080D7D0
};

class cViewer {
public:
    void GetCameraTransform(Transform& t);                           // 0x007C40F0
    float GetFOV();                                                  // 0x007C4050
};

// The camera description of a cinematic state (RefCountTemplate + IRefCount at +8).
struct cCameraData {
    char pad0[0x0C];
    float mDistance;       // +0x0C
    char pad10[0x2D - 0x10];
    bool mbUseRadius;      // +0x2D
    bool mbUseHeight;      // +0x2E
    bool mbUseScale;       // +0x2F
    bool mbScaleByRadius;  // +0x30
    bool mbScaleByHeight;  // +0x31
    char pad32[0x3C - 0x32];
    bool mb3c;             // +0x3C
    bool mbFollow;         // +0x3D
    bool mbAllowZoom;      // +0x3E
    char pad3f;
    uint32_t mMode;        // +0x40
    bool mbUseViewer;      // +0x44
    char pad45[3];
    float mYaw;            // +0x48
    float mPitch;          // +0x4C
    float mRoll;           // +0x50
    float mFOV;            // +0x54
    float mDistanceScale;  // +0x58
    bool mbApplied;        // +0x5C
    bool mbFollowTerrain;  // +0x5D
    char pad5e[2];
    float mNear;           // +0x60
    float mFar;            // +0x64
    uint16_t mTransformFlags; // +0x68
    char pad6a[2];
    Vector3* mPathBegin;   // +0x6C
    Vector3* mPathEnd;     // +0x70
};

struct CameraDataPtr {
    cCameraData* mpObject;
    CameraDataPtr& operator=(cCameraData* p);                        // 0x00AD7320
    cCameraData* operator->() const { return mpObject; }
};

class cPropertyTarget {
public:
    VP(0)
    virtual void SetFloat(uint32_t id, const float* value);          // +0x04
};

class cCameraManager {
public:
    VP(0) VP(1) VP(2) VP(3) VP(4) VP(5) VP(6) VP(7) VP(8) VP(9) VP(10) VP(11)
    VP(12) VP(13)
    virtual uint32_t GetStateID(const char* name);                   // +0x38
};

// Data of the referenced object of a cinematic (constructor 0x00AD7940).
struct cReferencedObjectData {
    Vector3 mPosition;           // +0x00
    Quaternion mOrientation;     // +0x0C
    float mScale;                // +0x1C
    float mRadius;               // +0x20
    float mHeightMin;            // +0x24
    float mHeightMax;            // +0x28
    cSpatialObject* mpObject;    // +0x2C

    cReferencedObjectData();                                         // 0x00AD7940
    __forceinline ~cReferencedObjectData()
    {
        if (mpObject)
            mpObject->Release();
    }
    const Vector3& GetPosition()
    {
        if (mpObject)
            return *mpObject->GetPosition();
        return mPosition;
    }
    const Quaternion& GetOrientation();                              // 0x00AD7B70
    float GetRadius();                                               // 0x00AD7B10
    float GetHeight();                                               // 0x00AD7AF0
};

// Message payloads: EA::Messaging::MessageBasicRC<N>, params of 8 bytes from +8.
struct cNamedData {
    uint32_t pad[3];
    const char* mpName;          // +0x0C
};

struct MessageParam {
    union {
        uint32_t u;
        float f;
        void* p;
        cNamedData* named;
    };
    uint32_t pad;
};

struct Message {
    void* vtbl;
    int mRefCount;
    MessageParam mParams[5];     // +0x08
};

class MessageBasicRC {
public:
    VP(0)
    virtual int AddRef();
    virtual int Release();
    int mRefCount;               // +0x04
    MessageParam mParams[5];     // +0x08
    uint32_t mExtra[4];          // +0x30 (size 0x40)

    MessageBasicRC(int flags);                                       // 0x00421C80
    ~MessageBasicRC();                                               // 0x00421CF0
};

struct MessagePtr {
    MessageBasicRC* mpObject;
    MessagePtr(MessageBasicRC* p);                                   // 0x0061DF40
};

// Cinematic action (RefCountTemplate + IRefCount at +8).
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
typedef int (*ActionFunction)(void* data, bool start);
struct cActionData {
    void* vtbl;
    int mRefCount;
    IRefCount mRef;              // +0x08
    void* mpData;                // +0x0C
    ActionFunction mpExecute;    // +0x10
};
struct ActionDataPtr {
    cActionData* mpObject;
    ActionDataPtr(cActionData* p);                                   // 0x00AD7300
    ~ActionDataPtr()
    {
        if (mpObject)
            mpObject->mRef.Release();
    }
};
struct ActionDataVector {
    ActionDataPtr* mpBegin;
    ActionDataPtr* mpEnd;
    ActionDataPtr* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const ActionDataPtr& p);                          // 0x00ADE190
    void erase(ActionDataPtr* first, ActionDataPtr* last);           // 0x0103C4F0
};
bool IsActionDone(const ActionDataPtr& p);                           // 0x00AD71F0
ActionDataPtr* RemoveActions(ActionDataPtr* first, ActionDataPtr* last, bool (*pred)(const ActionDataPtr&)); // 0x00AD9470

// Effect data (RefCountTemplate + IRefCount at +8).
struct cEffectData {
    void* vtbl;
    int mRefCount;
    IRefCount mRef;              // +0x08
    VisualEffectPtr mEffect;     // +0x0C
    Vector3 mOffset;             // +0x10
    Vector3 mExtraOffset;        // +0x1C
    bool mbAttached;             // +0x28
    bool mbWait;                 // +0x29
    bool mbHardStop;             // +0x2A
    bool mbPinToSurface;         // +0x2B
    bool mbPersist;              // +0x2C
    bool mbUseRadius;            // +0x2D
    bool mbUseHeight;            // +0x2E
    char pad2f;
    uint32_t mTargetID;          // +0x30
};
struct EffectDataPtr {
    cEffectData* mpObject;
    EffectDataPtr& operator=(cEffectData* p);                        // 0x00AD8E80
};
struct EffectMap {
    uint32_t mData[0x20 / 4];
    EffectDataPtr& operator[](const uint32_t& key);                  // 0x00ADDFA0
};

// hash_multimap<uint32_t, tSoundData>
struct tSoundData {
    uint32_t instanceId;
    uint32_t stopType;
};
struct SoundNode {
    uint32_t key;
    tSoundData value;
    SoundNode* mpNext;
};
struct SoundEntry {
    uint32_t key;
    tSoundData value;
};
struct SoundIterator {
    SoundNode* mpNode;
    SoundNode** mpBucket;
};
struct SoundMap {
    uint32_t pad0;
    SoundNode** mpBucketArray;   // +0x04
    uint32_t mnBucketCount;      // +0x08
    uint32_t mnElementCount;
    uint32_t mData[4];
    SoundIterator find(const uint32_t& key);                         // 0x00685F30
    SoundIterator erase(SoundIterator it);                           // 0x006859B0
    SoundIterator insert(const SoundEntry& v);                       // 0x00ADB470
    SoundNode* end_node() const { return mpBucketArray[mnBucketCount]; }
};

struct UIntVector {
    uint32_t mData[0x2C / 4];
    void clear();                                                    // 0x005810A0
    void push_back(const uint32_t& v);                               // 0x00422380
};

struct cStringKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
};

class cAppStateManager;

namespace SP {

class cCinematicManager {
public:
    virtual void vdtor();
    virtual bool HandleMessage(uint32_t messageID, void* pMessage);

    char pad04[0x28 - 0x04];
    bool mLetAIRun;                  // +0x28
    bool mLetAvatarAIRun;            // +0x29
    bool mCameraInited;              // +0x2A
    bool mEscExitDisabled;           // +0x2B
    int mStatus;                     // +0x2C
    float mDuration;                 // +0x30
    float mWaitSecs;                 // +0x34
    bool mWaiting;                   // +0x38
    bool mUseRealTime;               // +0x39
    bool mWaitingForContinue;        // +0x3A
    bool mWaitingForButton;          // +0x3B
    bool mForceStateSwitch;          // +0x3C
    bool mSkipRequested;             // +0x3D
    char pad3e[2];
    cViewer* mViewerCopy;            // +0x40
    cSPTutorialText* mTextPanel;     // +0x44
    char pad48[0x7C - 0x48];
    ActionDataVector mActionDataList;   // +0x7C
    EffectMap mWaitEffects;          // +0x90
    EffectMap mNoWaitEffects;        // +0xB0
    EffectMap mPersistingEffects;    // +0xD0
    SoundMap mSounds;                // +0xF0
    char pad110[0x13C - 0x110];
    cPropertyTarget* mCameraProperties; // +0x13C
    cCameraManager* mCameraManager;  // +0x140
    char pad144[0x14C - 0x144];
    uint32_t mNextState;             // +0x14C
    uint32_t mExitState;             // +0x150
    uint32_t mCurrentModeID;         // +0x154
    char pad158[0x15C - 0x158];
    bool mInDemoMode;                // +0x15C
    bool mHasNextState;              // +0x15D
    bool mModal;                     // +0x15E
    char pad15f;
    int mGamePausedStatus;           // +0x160
    char pad164[4];
    cGameCinematicsCameraController* mController; // +0x168
    CameraDataPtr mCameraData;       // +0x16C
    char pad170;
    bool mb171;                      // +0x171
    char pad172[2];
    uint32_t mHighlightID;           // +0x174
    float mHighlightTime;            // +0x178
    bool mbHighlight;                // +0x17C
    char pad17d[3];
    UIntVector mHighlightIDs;        // +0x180
    SpatialObjectPtrVector mCapturedObjects; // +0x1AC
    char pad1b0[0x3C4 - 0x1B0];
    uint32_t mStateNameParam;        // +0x3C4

    void CleanUpCinematic();                                         // 0x00ADAD70
    bool GetReferencedObjectData(uint32_t id, cReferencedObjectData* out); // 0x00ADB2A0
    bool FindEffectByLabelID(uint32_t id, Swarm::cIVisualEffect** out);   // 0x00ADB1B0
    bool IsReferencedObject(cSpatialObject* obj);                    // 0x00ADB360
    bool GetReferencedStringData(uint32_t id, cStringKey* out);      // 0x00ADB3D0
    void GetCameraOffsets(Vector3* offset, Quaternion* orientation,
                          float* scale, float* radius, float* height); // 0x00ADBCA0
    void SetCameraTransform(const cTransform& t, uint16_t flags);    // 0x00AD89B0
    void StartPauseEffect(uint32_t effectID);                        // 0x00AD8F20
    void StopPauseEffect();                                          // 0x00AD7D60
    void Skip();                                                     // 0x00ADFFD0
    void SkipAll();                                                  // 0x00AE0080

    __forceinline void SkipToCurrentMode()
    {
        if (mCurrentModeID != 0xffffffff) {
            mExitState = mCurrentModeID;
            mHasNextState = true;
            if (mCameraData.mpObject)
                mCameraData->mb3c = false;
            mSkipRequested = true;
        }
    }
};

// @ 0x00AE0E30
bool cCinematicManager::HandleMessage(uint32_t messageID, void* pMessage)
{
    Message* msg = (Message*)pMessage;

    switch (messageID) {
    case 0x2319915: {
        uint32_t state = msg->mParams[1].u;
        uint32_t controller = msg->mParams[2].u;
        if (state == 0xc51a136a)
            return false;
        if (mNextState != 0 && state != mNextState) {
            if (controller == (uint32_t)mCameraManager)
                mStatus = 2;
            return true;
        }
        if (controller == (uint32_t)mCameraManager) {
            mStatus = 0;
            SP::MessageServer()->PostMessage(0x604c6f4, 0, 0);
        }
        return true;
    }

    case 0x2800a7f: {
        LocaleString locale(SP::LocaleManager()->GetLocale());
        if (locale == L"en-us" || locale == L"en-gb")
            SP::EffectsManager()->SetOption(4, true);
        else
            SP::EffectsManager()->SetOption(4, false);
        return true;
    }

    case 0xe11331:
        return true;

    case 0x440377c: {
        const char* labelName = msg->mParams[0].named->mpName;
        const char* effectName = msg->mParams[1].named->mpName;
        cEffectData* effectData = msg->mParams[2].p ? (cEffectData*)((char*)msg->mParams[2].p - 8) : 0;
        const char* targetName = msg->mParams[3].named->mpName;

        Vector3 position;
        position.x = 0.0f;
        position.y = 0.0f;
        position.z = 0.0f;
        Quaternion orientation;
        orientation.x = 0.0f;
        orientation.y = 0.0f;
        orientation.z = 0.0f;
        orientation.w = 1.0f;
        float radius = 1.0f;
        float height = 1.0f;

        cReferencedObjectData objectData;
        bool found = GetReferencedObjectData(SPIDFromName(targetName), &objectData);
        effectData->mTargetID = 0;
        if (found) {
            effectData->mTargetID = SPIDFromName(targetName);
            position = objectData.GetPosition();
            orientation = objectData.GetOrientation();
            radius = objectData.GetRadius();
            height = objectData.GetHeight();
        }

        cEffectsManager* effects = SP::EffectsManager();
        if (labelName && effectName && effects) {
            uint32_t labelID = SPIDFromName(labelName);
            uint32_t effectID = SPIDFromName(effectName);
            if (effects->CreateVisualEffect(effectID, 0, effectData->mEffect.AsPPTypeParam())) {
                cTransform xform;
                Matrix3 rotation;
                rotation = Matrix3FromQuaternion(orientation);

                float ox = effectData->mOffset.x;
                float oy = effectData->mOffset.y;
                float oz = effectData->mOffset.z;
                if (effectData->mbUseRadius && mCameraData->mbScaleByHeight)
                    oz *= (radius > height) ? radius : height;
                else if (effectData->mbUseRadius)
                    oz *= radius;
                else if (effectData->mbUseHeight)
                    oz *= height;

                ox += effectData->mExtraOffset.x;
                oy += effectData->mExtraOffset.y;
                oz += effectData->mExtraOffset.z;

                Vector3 p;
                p.x = ox * rotation.m[0] + oy * rotation.m[3] + oz * rotation.m[6] + position.x;
                p.y = ox * rotation.m[1] + oy * rotation.m[4] + oz * rotation.m[7] + position.y;
                p.z = ox * rotation.m[2] + oy * rotation.m[5] + oz * rotation.m[8] + position.z;
                xform.SetOffsetInline(p);
                xform.SetRotation(rotation);

                if (effectData->mbPinToSurface) {
                    xform.SetOffset(SP::PlanetModel()->GetSurfacePoint(p, 0));
                    Vector3 surface = xform.mOffset;
                    xform.SetRotation(Matrix3FromQuaternion(SP::PlanetModel()->BuildSurfaceOrientation(surface)));
                }

                effectData->mEffect.mpObject->SetTransform(xform);
                effectData->mEffect.mpObject->Start(0);

                Swarm::cIVisualEffect* oldEffect;
                FindEffectByLabelID(labelID, &oldEffect);
                if (effectData->mbWait)
                    mWaitEffects[labelID] = effectData;
                else
                    mNoWaitEffects[labelID] = effectData;
            }
        }
        return true;
    }

    case 0x4448b7a:
        switch (msg->mParams[0].u) {
        case 0:
            mTextPanel->SetMode0(true);
            return true;
        case 1:
            mTextPanel->SetMode1(true);
            mTextPanel->Show(true);
            break;
        case 2:
            mTextPanel->SetMode2(true);
            mTextPanel->Show(true);
            break;
        case 3:
            mTextPanel->SetMode3(true);
            mTextPanel->Show(true);
            break;
        case 4:
            mTextPanel->SetMode4(true);
            mTextPanel->Show(true);
            break;
        }
        return true;

    case 0x4448b81: {
        CleanUpCinematic();
        mCameraData = msg->mParams[0].p ? (cCameraData*)((char*)msg->mParams[0].p - 8) : 0;
        mController->mb10b = true;
        mController->SetFollowTerrain(SP::PlanetModel()->mpTerrain != 0 && mCameraData->mbFollowTerrain);
        mController->mb10a = mCameraData->mbFollow;
        mController->mb108 = mCameraData->mbAllowZoom;
        mController->SetMode(mCameraData->mMode);
        mController->SetFOV(mCameraData->mDistanceScale);
        float nearPlane = mCameraData->mNear;
        mCameraProperties->SetFloat(0x109d372, &nearPlane);
        float farPlane = mCameraData->mFar;
        mCameraProperties->SetFloat(0x109d375, &farPlane);

        Vector3 offset;
        offset.x = 0.0f;
        offset.y = 0.0f;
        offset.z = 0.0f;
        Quaternion orientation;
        orientation.x = 0.0f;
        orientation.y = 0.0f;
        orientation.z = 0.0f;
        orientation.w = 1.0f;
        float scale = 1.0f;
        float radius = 1.0f;
        float height = 1.0f;
        GetCameraOffsets(&offset, &orientation, &scale, &radius, &height);

        cTransform xform;
        switch (mCameraData->mMode) {
        case 0:
        case 1:
        case 2:
        case 4: {
            if (mCameraData->mbUseViewer) {
                Transform viewer;
                mViewerCopy->GetCameraTransform(viewer);
                xform.SetOffset(viewer.mOffset);
                mController->SetOrientationArg(QuaternionFromMatrix33(viewer.mRotation, 0.0f));
                mController->SetDistance(0.0f);
                mController->Apply();
                mCameraData->mFOV = mViewerCopy->GetFOV() * 0.017453292f;
                break;
            }

            xform.AddOffset(offset);
            uint32_t mode = mCameraData->mMode;
            if (mCameraData->mbUseRadius && (mode == 4 || mode == 1)) {
                mController->mb109 = true;
                mController->SetOrientation(orientation);
            } else if (mCameraData->mbUseHeight && (mode == 4 || mode == 1)) {
                mController->mb109 = true;
                orientation = SP::PlanetModel()->GetOrientation(offset, orientation);
                mController->SetOrientation(orientation);
            } else {
                mController->mb109 = false;
                if (mCameraData->mMode == 1) {
                    Transform t;
                    t.SetRotation(Matrix3FromQuaternion(orientation));
                    mController->SetUp(t.GetRow1());
                }
            }

            cCameraData* data = mCameraData.mpObject;
            bool rotated = false;
            if (data->mPitch != 0.0f) {
                xform.PreRotateX(data->mPitch * g_DegToRad);
                rotated = true;
            }
            if (data->mYaw != 0.0f) {
                xform.RotateZ(data->mYaw * g_DegToRad);
                rotated = true;
            }
            if (data->mRoll != 0.0f) {
                xform.RotateY(data->mRoll * g_DegToRad);
                rotated = true;
            }
            data->mTransformFlags = 0;
            if (rotated)
                mCameraData->mTransformFlags |= 2;

            float distance = mCameraData->mDistance;
            if (mCameraData->mbScaleByRadius && mCameraData->mbScaleByHeight)
                distance = ((radius > height) ? radius : height) * distance;
            else if (mCameraData->mbScaleByRadius)
                distance *= radius;
            else if (mCameraData->mbScaleByHeight) {
                float one = 1.0f;
                const float& m = (height > one) ? height : one;
                distance = m * distance;
            } else if (mCameraData->mbUseScale)
                distance *= scale;
            mController->SetDistance(distance);
            break;
        }

        case 3: {
            mCameraData->mTransformFlags = 0;
            Transform t;
            t.SetRotation(Matrix3FromQuaternion(orientation));
            mController->SetUp(t.GetRow1());
            mController->SetPath(mCameraData->mPathBegin,
                                 (int)(mCameraData->mPathEnd - mCameraData->mPathBegin),
                                 g_Vector3Zero);
            mController->mb109 = false;
            xform.AddOffset(offset);
            break;
        }
        }

        float fov = mCameraData->mFOV;
        if (fov != 0.0f) {
            float value = fov;
            if (mCameraData->mbFollow)
                mCameraProperties->SetFloat(0x109d352, &value);
            else
                mCameraProperties->SetFloat(0x109d174, &value);
        }
        if (mCameraData->mbFollow)
            mCameraData->mTransformFlags |= 0x10;
        SetCameraTransform(xform, mCameraData->mTransformFlags);
        mCameraData->mbApplied = true;
        return true;
    }

    case 0x4448b85: {
        cString text(msg->mParams[0].u, msg->mParams[1].u, 0);
        cSPTutorialText* panel = mTextPanel;
        panel->mpTextWindow->SetFlag(1, true);
        panel->mpButtonWindow->SetFlag(1, false);
        mTextPanel->mpTextWindow->SetCaption(text.GetText());
        return true;
    }

    case 0x4448b88: {
        uint32_t id = msg->mParams[0].u;
        MessagePtr forward(new ("Simulator", 0, 0, 0, 0) MessageBasicRC(0));
        MessageBasicRC* m = forward.mpObject;
        m->mParams[0].u = msg->mParams[1].u;
        m->mParams[1].u = msg->mParams[2].u;
        m->mParams[2].u = msg->mParams[3].u;
        m->mParams[3].u = msg->mParams[4].u;
        SP::MessageServer()->PostMessage(id, m, 0);
        m->Release();
        return true;
    }

    case 0x4448cb4:
        switch (msg->mParams[0].u) {
        case 0:
            mTextPanel->SetMode0(false);
            return true;
        case 1:
            mTextPanel->SetMode1(false);
            mTextPanel->Show(false);
            break;
        case 2:
            mTextPanel->SetMode2(false);
            mTextPanel->Show(false);
            break;
        case 3:
            mTextPanel->SetMode3(false);
            mTextPanel->Show(false);
            break;
        case 4:
            mTextPanel->SetMode4(false);
            mTextPanel->Show(false);
            break;
        }
        return true;

    case 0x445f6e8: {
        uint32_t waitType = msg->mParams[0].u;
        mWaiting = true;
        mWaitSecs = msg->mParams[1].f;
        if (waitType == 1 || waitType == 2 || waitType == 3) {
            mWaitingForContinue = true;
            mWaitingForButton = false;
            mForceStateSwitch = false;
            if (waitType == 2) {
                mWaitingForButton = true;
                return true;
            }
            if (waitType == 3)
                mForceStateSwitch = true;
        }
        return true;
    }

    case 0x445f729:
        if (mWaitingForContinue) {
            mWaiting = false;
            mWaitingForContinue = false;
            mWaitingForButton = false;
            mForceStateSwitch = false;
            mTextPanel->Hide(mModal);
            mTextPanel->mpLayout->SetVisibility(true);
        }
        return true;

    case 0x4470a41: {
        cActionData* action = msg->mParams[0].p ? (cActionData*)((char*)msg->mParams[0].p - 8) : 0;
        if (action->mpExecute(action->mpData, true) != 1) {
            ActionDataPtr ref(action);
            mActionDataList.push_back(ref);
        }
        return true;
    }

    case 0x4485c77:
        if (mInDemoMode)
            SkipToCurrentMode();
        else
            mExitState = mCameraManager->GetStateID(msg->mParams[0].named->mpName);
        mHasNextState = true;
        return true;

    case 0x449c44e: {
        uint32_t labelID = SPIDFromName(msg->mParams[0].named->mpName);
        int hardStop = 1;
        if (msg->mParams[1].u == 1)
            hardStop = 0;
        Swarm::cIVisualEffect* effect;
        if (FindEffectByLabelID(labelID, &effect))
            effect->Stop(hardStop);
        return true;
    }

    case 0x44ee075:
        Skip();
        return true;

    case 0x44ee076:
        SkipAll();
        return true;

    case 0x4518de0:
        mDuration = msg->mParams[0].f;
        return true;

    case 0x46ac986:
        if (mGamePausedStatus != 0) {
            if (mGamePausedStatus == 2)
                SP::GameTimeManager()->DecPauseGate(0x600c4ae);
            else
                SP::GameTimeManager()->DecPauseGate(0x4bf38a5);
            mGamePausedStatus = 0;
            StopPauseEffect();
        }
        return true;

    case 0x46ac0ac: {
        int status = (msg->mParams[0].u != 0) + 1;
        if (status != mGamePausedStatus) {
            if (mGamePausedStatus == 2)
                SP::GameTimeManager()->DecPauseGate(0x600c4ae);
            else if (mGamePausedStatus == 1)
                SP::GameTimeManager()->DecPauseGate(0x4bf38a5);
            mGamePausedStatus = status;
            cGameTimeManager* time = SP::GameTimeManager();
            if (status == 2)
                time->IncPauseGate(0x600c4ae);
            else
                time->IncPauseGate(0x4bf38a5);
            if (msg->mParams[1].u != 0)
                StartPauseEffect(msg->mParams[2].u);
            else
                StopPauseEffect();
        }
        return true;
    }

    case 0x46d28ea: {
        uint32_t avatar = msg->mParams[1].u;
        mLetAIRun = (msg->mParams[0].u != 0 && avatar == 0) ? true : false;
        mLetAvatarAIRun = avatar != 0;
        return true;
    }

    case 0x473eb8d: {
        uint32_t stopType = msg->mParams[2].u;
        uint32_t soundID = msg->mParams[0].u;
        uint32_t audioID = msg->mParams[1].u;
        uint32_t instanceID = NewAudioInstanceID();
        PlayCinematicSound(audioID, instanceID);
        SoundEntry entry;
        entry.key = soundID;
        entry.value.instanceId = instanceID;
        entry.value.stopType = stopType;
        mSounds.insert(entry);
        return true;
    }

    case 0x473eb91: {
        uint32_t soundID = msg->mParams[0].u;
        SoundIterator it = mSounds.find(soundID);
        if (it.mpNode == mSounds.end_node())
            return true;
        tSoundData data = it.mpNode->value;
        mSounds.erase(it);
        StopAudioInstance(data.instanceId, 0);
        cAudioSystem* audio = EA::Audio::GetSystemAT();
        if (audio)
            audio->StopInstance(data.instanceId);
        return true;
    }

    case 0x47691c0:
        mEscExitDisabled = true;
        return true;

    case 0x4740862:
        SetGlobalProperty((int)msg->mParams[0].u, msg->mParams[1].f);
        return true;

    case 0x476ad30: {
        uint32_t modeID = msg->mParams[0].u;
        if (modeID == g_InvalidModeID)
            mCurrentModeID = 0xffffffff;
        else
            mCurrentModeID = modeID;
        return true;
    }

    case 0x47feba4:
        mb171 = true;
        return true;

    case 0x47b92d6: {
        cStringKey key;
        key.instanceID = 0;
        key.groupID = 0;
        GetReferencedStringData(msg->mParams[0].u, &key);
        cString text(key.groupID, key.instanceID, L"ERROR");
        cSPTutorialText* panel = mTextPanel;
        panel->mpTextWindow->SetFlag(1, true);
        panel->mpButtonWindow->SetFlag(1, false);
        mTextPanel->mpTextWindow->SetCaption(text.GetText());
        return true;
    }

    case 0x490cec8:
        mActionDataList.erase(
            RemoveActions(mActionDataList.mpBegin, mActionDataList.mpEnd, IsActionDone),
            mActionDataList.mpEnd);
        return true;

    case 0x493440d:
        cSPUISpace::Get()->ShowForTutorial(msg->mParams[0].u);
        return true;

    case 0x4cea5ff: {
        uint32_t targetID = msg->mParams[0].u;
        float radius = msg->mParams[1].f;
        float radiusSq = radius * radius;
        uint32_t flags = msg->mParams[2].u;
        if (targetID == 0)
            return true;
        if (1.17549435e-38f >= radiusSq)
            return true;
        if (flags == 0)
            return true;

        cReferencedObjectData objectData;
        if (GetReferencedObjectData(targetID, &objectData)) {
            const Vector3& center = objectData.GetPosition();
            if (Vector3_NotEqual(&center, &g_Vector3Zero)) {
                if (flags & 2) {
                    CreatureVector& creatures = SP::NounManager()->GetCreatures();
                    int count = creatures.size();
                    for (int i = 0; i < count; i++) {
                        cCreatureBase* creature = creatures.mpBegin[i];
                        if (!creature->mbIsAlive)
                            continue;
                        cSpatialObject* spatial = &creature->mSpatial;
                        if (IsReferencedObject(spatial))
                            continue;
                        if ((*spatial->GetPosition() - center).SquaredLength() <= radiusSq) {
                            cCreatureAction* action =
                                creature->mpMotive->mActions.Add(0, 0x2000000, 3.402823466e+38F, 0);
                            if (action) {
                                action->mRadius = radius;
                                action->mCenterX = center.x;
                                action->mCenterY = center.y;
                                action->mCenterZ = center.z;
                                action->mFlags = flags & 4;
                            }
                        }
                    }
                }

                if (flags & 8) {
                    cPlanetModel* planet = SP::PlanetModel();
                    bool teleport = (flags >> 2) & 1;
                    Quaternion surface = planet->BuildSurfaceOrientation(center);
                    Vector3 up = RotateVectorByQuaternion(g_Vector3Up, surface);
                    CreatureVector& animals = SP::NounManager()->GetAnimals();
                    int count = animals.size();
                    for (int i = 0; i < count; i++) {
                        cCreatureBase* creature = animals.mpBegin[i];
                        if (!creature->mbIsAlive)
                            continue;
                        cSpatialObject* spatial = &creature->mSpatial;
                        if (IsReferencedObject(spatial))
                            continue;
                        float cx = center.x;
                        float cy = center.y;
                        float cz = center.z;
                        Vector3 dir = *spatial->GetPosition() - center;
                        float distSq = dir.SquaredLength();
                        if (distSq <= radiusSq) {
                            float inv = 1.0f / ((float)sqrt(distSq) + 1.5258789e-05f);
                            dir.x *= inv;
                            dir.y *= inv;
                            dir.z *= inv;
                            Vector3 target;
                            if (Vector3Equal(&dir, &g_Vector3Zero)) {
                                target.x = radius * up.x + cx;
                                target.y = cy + radius * up.y;
                                target.z = cz + radius * up.z;
                            } else {
                                target.x = radius * dir.x + cx;
                                target.y = cy + radius * dir.y;
                                target.z = cz + radius * dir.z;
                            }
                            Vector3 ground = planet->ProjectToSurface(target);
                            if (teleport) {
                                spatial->SetPositionOrientation(ground, planet->BuildSurfaceOrientation(ground));
                                spatial->UpdateModelTransform();
                            } else {
                                creature->MoveToPointAtSpeed(2, ground, 1.0f, 2.0f);
                            }
                        }
                    }
                }

                if (flags & 1) {
                    GameObjectVector objects(SP::NounManager()->GetGameObjects());
                    int count = objects.size();
                    for (int i = 0; i < count; i++) {
                        cSpatialObject* spatial = &objects.mpBegin[i]->mSpatial;
                        if (!spatial->GetModelInfo())
                            continue;
                        if ((*spatial->GetPosition() - center).SquaredLength() <= radiusSq) {
                            spatial->GetModelInfo()->mFlags &= ~1u;
                            SpatialObjectPtr ref(spatial);
                            mCapturedObjects.push_back(ref);
                        }
                    }

                    GameObjectVector others(SP::NounManager()->GetObjectsOfType(0x398420d));
                    int otherCount = others.size();
                    for (int i = 0; i < otherCount; i++) {
                        cSpatialObject* spatial = &others.mpBegin[i]->mSpatial;
                        if (!spatial->GetModelInfo())
                            continue;
                        if ((*spatial->GetPosition() - center).SquaredLength() <= radiusSq) {
                            spatial->GetModelInfo()->mFlags &= ~1u;
                            SpatialObjectPtr ref(spatial);
                            mCapturedObjects.push_back(ref);
                        }
                    }
                }
            }
        }
        return true;
    }

    case 0x4dd9f67:
        mInDemoMode = SP::AppSystem()->IsDemoMode();
        return true;

    case 0x5b70e8b:
        mTextPanel->mpTextWindow->SetFlag(1, false);
        return true;

    case 0x5caabce:
        if (mCameraInited)
            mController->Stop();
        return true;

    case 0x5d6b782:
        mEscExitDisabled = false;
        return true;

    case 0x5dbc9c4:
        mTextPanel->mpContinueWindow->SetFlag(1, true);
        return true;

    case 0x5dbc9c8:
        mTextPanel->mpContinueWindow->SetFlag(1, false);
        return true;

    case 0x6133baa: {
        uint32_t p0 = msg->mParams[0].u;
        uint32_t p1 = msg->mParams[1].u;
        cSPTutorialText* panel = mTextPanel;
        mWaiting = true;
        mWaitingForContinue = true;
        panel->EndModalIfNeeded();
        mTextPanel->SetModal(false);
        MessageBasicRC button(0);
        button.mParams[0].u = p0;
        button.mParams[1].u = p1;
        SP::MessageServer()->PostMessage(0x5120262, &button, 0);
        return true;
    }

    case 0x636bf2d:
        if (msg->mParams[0].u != 0) {
            mHighlightID = msg->mParams[0].u;
            mHighlightTime = msg->mParams[1].f;
            mbHighlight = msg->mParams[2].u != 0;
            mHighlightIDs.clear();
            uint32_t id = msg->mParams[3].u;
            if (id)
                mHighlightIDs.push_back(id);
            id = msg->mParams[4].u;
            if (id)
                mHighlightIDs.push_back(id);
        } else {
            mHighlightTime = 0.0f;
            mHighlightID = 0;
            mbHighlight = false;
            mHighlightIDs.clear();
        }
        return true;

    case 0x67a195b: {
        cString text(msg->mParams[0].u, msg->mParams[1].u, 0);
        float duration = msg->mParams[2].f;
        mTextPanel->Reset();
        mTextPanel->ShowTimed(text.GetText(), duration, 0, 1, 0.25f);
        return true;
    }

    case 0x750d599:
        if (mInDemoMode)
            SkipToCurrentMode();
        else {
            uint32_t index = mStateNameParam;
            const char* name;
            if (index < 5)
                name = msg->mParams[index].named->mpName;
            mExitState = mCameraManager->GetStateID(name);
        }
        mHasNextState = true;
        return true;

    case 0x798207d: {
        cString text(msg->mParams[0].u, msg->mParams[1].u, 0);
        mTextPanel->Show(true);
        mTextPanel->SetText(text.GetText());
        return true;
    }

    case 0x7982226:
        mTextPanel->Show(false);
        return true;
    }
    return false;
}

}  // namespace SP
