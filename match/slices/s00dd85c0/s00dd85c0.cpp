// Slice s00dd85c0 -- SP::cSPUIEventLog::PostFeedbackEvent (retail 0x00dd8640, thiscall, ret 0x18).
//
// PostFeedbackEvent(instanceID, groupID, pPosition, bNoDedupe..., unused, userData):
//   looks up the tuning property list (groupID, instanceID); bails out unless it is enabled (0x2c08dc2),
//   reuses an existing live event of the same type (unless flagged "always new") or builds a new
//   cFeedbackEvent, wires up its layout windows (item/icon/shade, WinProc = the log), fills its category,
//   scale, time-to-live, remove time, universe binding, position, optional close callback and sound, then
//   stores it in the map under its instance ID, drops the old history entry for it and refreshes its UI.
// Returns the instance ID of the last event entered (0 when nothing was posted).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (UI module, no /EHsc).
#include <string.h>
#include <math.h>
#include "types.h"

#pragma pack(push, 4)

void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* pFile, int line);   // 0x00f473a0

struct Object {
    virtual int AddRef();
    virtual int Release();
};

struct Point {
    float x, y;
};

// UTFWin::IWindow slots used here (as in the Spore ModAPI header)
struct IWinProc;
struct IWindow : Object {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(); virtual void v3c(); virtual void v40(); virtual void v44();
    virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void SetCommandID(uint32_t id);                       // +0x54
    virtual void v58();
    virtual void SetShadeColor(uint32_t color);                   // +0x5c
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(uint32_t flag, bool value);              // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual void vc0(); virtual void vc4(); virtual void vc8(); virtual void vcc();
    virtual void vd0(); virtual void vd4(); virtual void vd8(); virtual void vdc();
    virtual void ve0(); virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive); // +0xf0
    virtual void vf4(); virtual void vf8(); virtual void vfc(); virtual void v100();
    virtual void AddWinProc(void* pWinProc);                      // +0x104
};

class cSPUILayout { public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);         // 0x008105b0
};

struct cSPUIAnimBase0 { virtual void f0(); uint32_t field_4; };
struct cSPUIAnimBase1 { virtual void f1(); };
struct cSPUIWindowAnimation : cSPUIAnimBase0, cSPUIAnimBase1 {
    Object* mpTarget;                                             // +0x0c
    virtual void f0();
    virtual void f1();
    ~cSPUIWindowAnimation() { if (mpTarget) mpTarget->Release(); }
};
cSPUIWindowAnimation SPUICreateWindowAnimationTargetShadeAlpha(IWindow* window, uint32_t alpha, float startTime,
                                                              float duration, int interpolation);  // 0x007f8290
class cSPUIAnimator { public:
    void AddAnimation(const cSPUIWindowAnimation& anim, Object* owner, uint32_t id);  // 0x007f8d10
    void Update();                                                    // 0x007f63b0 AnimatorS::Update
};
namespace SPUIHelpers {
float GetElapsedSeconds();                                        // 0x00805080
}

extern float g_016a09ac;       // animation duration
extern uint32_t g_016a0a7c;    // sound ids per category
extern uint32_t g_016a0a8c;
extern uint32_t g_016a0a9c;
extern uint32_t g_016a0aac;
extern uint32_t g_016a0abc;
extern uint32_t g_015a2b3c[7];  // category property keys
extern uint32_t g_015a2b5c[];   // scale property keys
extern int g_015a2b88;          // number of scale keys
extern const char g_013ec47c[]; // string compared with the "close callback" property

// ---------------------------------------------------------------- property lists
struct Property {
    uint32_t pad0[4];
    uint16_t mnFlags;     // +0x10 (low byte holds the 0x30 "indirect" bits)
    uint16_t mnType;      // +0x12
    bool* GetBool();      // 0x0041e920
};
struct Key {
    uint32_t mInstance, mType, mGroup;
};
struct cPropertyList {
    virtual int AddRef();
    virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6();
    virtual bool HasProperty(uint32_t id);                         // +0x1c
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);         // +0x24
};
struct cPropertyManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool GetPropertyList(uint32_t a, uint32_t b, cPropertyList** out);   // +0x2c
};
cPropertyManager* PropertyManager();                               // 0x0067de30
void GetBoolProperty(cPropertyList* p, uint32_t id, bool* out);    // 0x00407190
bool GetPropertyAsKey(cPropertyList* p, uint32_t id, Key* out);    // 0x006a1250
struct cString {
    cString();                                                     // 0x006b5060
    ~cString();                                                    // 0x006b5240
    const wchar_t* GetText();                                      // 0x006b55c0
    char data[16];
};
void GetPropertyAsText(cPropertyList* p, uint32_t id, cString* out);   // 0x006a1360
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
};
extern char g_01667bac[2];     // eastl empty-string storage
bool GetPropertyAsString8(cPropertyList* p, uint32_t id, String8* out);   // 0x006a13b0
void operator_delete_array_00f47380(void* p);                      // 0x00f47380 operator delete[]

inline Property* GetPropertyOfType(cPropertyList* list, uint32_t id, uint32_t type)
{
    Property* prop;
    if (list && list->GetProperty(id, &prop) && prop->mnType == type)
        return prop;
    return 0;
}
// property payload: inline, or behind a pointer when the 0x30 bits of the flags are set
inline void* PropertyData(Property* prop)
{
    void* p = prop;
    if (prop->mnFlags & 0x30)
        p = *(void**)prop;
    return p;
}

// ---------------------------------------------------------------- cFeedbackEvent (retail layout)
struct WString {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; uint32_t mAllocator;
    void assign(const wchar_t* first, const wchar_t* last);       // 0x00423650
};
typedef void (*EventCallback)(uint32_t instanceID, void* arg);
void FUN_00ae0b80(uint32_t instanceID, void* arg);

enum { kfInvalid = 8, kfHistory = 9, kfPermanent = 11 };

struct cFeedbackEvent : Object {
    uint32_t pad04[2];
    uint32_t mFlags;                 // +0x0c eastl::bitset<12>
    uint32_t mCategory;              // +0x10
    uint32_t mScaleIndex;            // +0x14
    uint32_t pad18[2];
    float mPosition[3];              // +0x20
    float mTimeAnimStarted;          // +0x2c
    float mTimeCreated;              // +0x30
    float mTimeToLive;               // +0x34
    float mRemoveTime;               // +0x38
    uint32_t pad3c;
    bool mbUniverseBound;            // +0x40
    void* mpUniverseContext;         // +0x44
    uint32_t mInstanceID;            // +0x48
    uint32_t mTypeID;                // +0x4c
    uint32_t mGroupID;               // +0x50
    uint32_t mData;                  // +0x54
    uint32_t pad58;
    void* mpCallbackArg;             // +0x5c
    EventCallback mpCallback;        // +0x60
    EventCallback mpCloseCallback;   // +0x64
    WString mEventString;            // +0x68
    cSPUILayout* mpItemLayout;       // +0x78
    uint32_t pad7c[6];

    cFeedbackEvent();                // 0x00dd5e90
    bool test(int n) const { return ((mFlags >> n) & 1) != 0; }
    void set(int n) { mFlags |= 1u << n; }
};

// out-of-line AutoRefCount<> assignment (shared by identical-code folding)
struct EventRef {
    cFeedbackEvent* mpObject;
    EventRef() : mpObject(0) {}
    ~EventRef() { if (mpObject) mpObject->Release(); }
    EventRef& operator=(cFeedbackEvent* p);                       // 0x00b5f950
};
struct ListRef {
    cPropertyList* mpObject;
    ListRef() : mpObject(0) {}
    ~ListRef() { if (mpObject) mpObject->Release(); }
    cPropertyList** Reset()
    {
        cPropertyList* old = mpObject;
        if (old) {
            mpObject = 0;
            old->Release();
        }
        return &mpObject;
    }
};
struct EventSlot {                // AutoRefCount<cFeedbackEvent> stored in the map
    cFeedbackEvent* mpObject;
    void Assign(cFeedbackEvent* p)
    {
        cFeedbackEvent* old = mpObject;
        if (p != old) {
            p->AddRef();
            mpObject = p;
            if (old)
                old->Release();
        }
    }
};

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
struct EventNode : rbtree_node_base {
    uint32_t mKey;          // +0x10
    EventSlot mValue;       // +0x14
};
rbtree_node_base* RBTreeIncrement_00921580(const rbtree_node_base* pNode);

struct EventMap {
    uint32_t mCompare;
    rbtree_node_base mAnchor;   // +0x04
    uint32_t mnSize;
    uint32_t mAllocator;
    EventSlot& GetOrInsert(const uint32_t& key);                  // 0x00dd85c0 (map operator[])
    void* FUN_00dd6f50(const uint32_t* pKey, rbtree_node_base* pHint, bool bInsert);  // 0x00dd6f50
};

struct EASystemAT {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual int GetHandle();                                        // +0x20
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13();                                             // +0x24 .. +0x34
    virtual void PlaySoundEvent(uint32_t eventID);                   // +0x38
    virtual void v15();                                             // +0x3c
    virtual void SetSoundParam(uint32_t paramID, uint32_t value);    // +0x40
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
    virtual void v21();                                             // +0x44 .. +0x54
    virtual void StopSoundEvent();                                   // +0x58
};
EASystemAT* GetSystemAT();                                         // 0x00a206f0
void PlayEventSound(uint32_t soundId, int system);                 // 0x00435ed0
void* GetUniverseContext_01021080();

struct cSPUIEventLog {
    uint32_t pad00[8];
    uint32_t mGlobalAlpha;          // +0x20
    bool mbVisible;                 // +0x24
    EventMap mEvents;               // +0x28
    uint32_t mLastEventEntered;     // +0x44
    float mLastUpdateTime;          // +0x48
    char pad4c[0x68 - 0x4c];
    cSPUIAnimator* mpAnimator;      // +0x68

    void ModifyEventText(uint32_t instanceID, const wchar_t* text);   // 0x00dd6df0
    cFeedbackEvent* find_in_history(cFeedbackEvent* ev);              // 0x00dd5dd0
    void remove_event(uint32_t instanceID);                           // 0x00dd6bc0
    void update_event_ui_state(cFeedbackEvent* ev);                   // 0x00dd60c0
    uint32_t PostFeedbackEvent(uint32_t instanceID, uint32_t groupID, const float* pPosition, bool bAlways,
                               int unused, void* userData);
    void Update(int param);                                           // 0x00dd8d80
    void SetVisibility(bool bVisible);                                // 0x00dd8da0
    void FUN_00dd7970(int param);                                     // 0x00dd7970
};

// ---------------------------------------------------------------- window manager (0x0067caa0)
class cWindowManager {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48();
    virtual void SetVisible(bool bShow, int flags);                   // +0x4c
};
cWindowManager* WindowManager();                                      // 0x0067caa0

// ---------------------------------------------------------------- stopwatch (EA::Stopwatch, 8 bytes of ticks)
union LargeInteger {                                                  // LARGE_INTEGER
    int64_t mQuadPart;
    struct { uint32_t mLowPart; uint32_t mHighPart; };
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(uint64_t* pCounter);
inline int64_t rdtsc64()
{
    __asm { rdtsc }
}

struct EAStopwatch {
    uint32_t mLow;                      // +0x00  start tick (low)
    uint32_t mHigh;                     // +0x04  start tick (high)
    uint32_t mElapsedLow;               // +0x08
    uint32_t mElapsedHigh;              // +0x0c
    int32_t  mnMode;                    // +0x10  1 = rdtsc, otherwise QueryPerformanceCounter
    float    mPeriod;                   // +0x14  ticks -> seconds factor
    int64_t GetElapsedTimeFloat();                                // 0x0093a3a0
    void SetBoolProperty();                                       // 0x0093a2e0
};

struct Vec3 { float x, y, z; };
struct Quaternion { float x, y, z, w; };
struct Matrix33 { float m[3][3]; };

// ---------------------------------------------------------------- timer driven UI element ("throbber")
struct cSPUIThrobber {
    uint32_t pad00[3];                  // +0x00
    Vec3 mPosition;                     // +0x0c  design position
    uint32_t pad18[9];                  // +0x18
    Vec3 mSoundPosition;                // +0x3c  position the 3d sound is started at
    uint32_t pad48[0x14];               // +0x48
    float mf98;                         // +0x98  offset applied to the window
    uint32_t pad9c[3];                  // +0x9c
    float mfA8;                         // +0xa8  amplitude
    uint32_t padAC;                     // +0xac
    EAStopwatch mStopwatch;             // +0xb0
    uint32_t padC8[2];                  // +0xc8
    uint32_t mSoundId;                  // +0xd0
    bool mbFinished;                    // +0xd4
    bool mbReverse;                     // +0xd5

    void FUN_00dd9080();                                          // 0x00dd9080
};

struct cThrobberAnimator {              // drives one cSPUIThrobber
    uint32_t mnKind;                    // +0x00
    bool mbReverse;                     // +0x04
    bool FUN_00dd8ea0(cSPUIThrobber* pTarget, float unused);       // 0x00dd8ea0
};

void __cdecl FUN_00572020(uint32_t soundId, int action);              // 0x00572020
void __cdecl Start3dSoundByName(uint32_t soundName, uint32_t soundId, float x, float y, float z);  // 0x00571f80
void __stdcall FUN_00dd8e30(cSPUIThrobber* pTarget);                  // 0x00dd8e30
void __stdcall FUN_00dd8f50(cSPUIThrobber* pTarget);                  // 0x00dd8f50
void __stdcall FUN_00dd8ff0(cSPUIThrobber* pTarget);                  // 0x00dd8ff0
void __stdcall FUN_00dd9040(cSPUIThrobber* pTarget);                  // 0x00dd9040
bool __stdcall FUN_00dd9050(cSPUIThrobber* pTarget, int unused);      // 0x00dd9050
void FUN_00dd9130(const float* pDirection, Vec3* pOutA, Vec3* pOutB); // 0x00dd9130
Quaternion* FUN_00dd91b0(const Vec3* pA, const Vec3* pB, Quaternion* pOut);   // 0x00dd91b0
Vec3* FUN_00dd93d0(Vec3* pOut);                                       // 0x00dd93d0

void* FUN_00b3d360(const float* pVector);                             // 0x00b3d360
bool FUN_00b7d4f0(void* pVector);                                     // 0x00b7d4f0
void FUN_00b7d440(uint32_t x, uint32_t y, uint32_t z, int a, int b, int c, int d,
                  Vec3* pOutA, Vec3* pOutB);                          // 0x00b7d440
Quaternion* QuaternionFromMatrix33_00472b80(Quaternion* pOut, const Matrix33* pMatrix,
                                            float w);                 // 0x00472b80

struct cRandomGlobal {
    double RandomDouble(double low, double high);                     // 0x009360d0
};
extern cRandomGlobal gRandomGlobal_01601760;                          // 0x01601760

extern float g_01485720;        // 1.0f
extern float g_016a0b58;        // sine frequency of the throbber animation
extern float g_01471064;        // 0.5f
extern float g_015a2de0;        // period divisor of the 0x00dd9080 variant
extern float g_013f561c;        // "finished" threshold of 0x00dd9050
extern float g_013ec4b8;        // 1e-8f, added to the squared lengths before normalising
extern uint32_t g_016a0c5c;     // scratch direction table init flags
extern float g_016a0c58;        // 50.0f
extern float g_016a0c54;        // 35.0f

#pragma pack(pop)

// @ 0x00dd8640
uint32_t cSPUIEventLog::PostFeedbackEvent(uint32_t instanceID, uint32_t groupID, const float* pPosition,
                                          bool bAlways, int unused, void* userData)
{
    ListRef list;
    PropertyManager()->GetPropertyList(instanceID, groupID, list.Reset());
    if (!list.mpObject)
        return 0;

    Property* prop;
    if (!list.mpObject->GetProperty(0x2c08dc2, &prop) || prop->mnType != 1 || !*prop->GetBool())
        return 0;

    EventRef ev;
    bool flag = !bAlways;
    if (list.mpObject->HasProperty(0x46a6e76))
        GetBoolProperty(list.mpObject, 0x46a6e76, &flag);

    bool reuse = false;
    if (!flag) {
        for (rbtree_node_base* it = mEvents.mAnchor.mpNodeLeft; it != &mEvents.mAnchor;
             it = RBTreeIncrement_00921580(it)) {
            cFeedbackEvent* e = ((EventNode*)it)->mValue.mpObject;
            if (e->mTypeID == instanceID && !e->test(kfHistory)) {
                ModifyEventText(e->mInstanceID, e->mEventString.mpBegin);
                ev = e;
                if (ev.mpObject) {
                    if (ev.mpObject->mpCloseCallback)
                        ev.mpObject->mpCloseCallback(ev.mpObject->mInstanceID, ev.mpObject->mpCallbackArg);
                    ev.mpObject->mpCallbackArg = 0;
                    ev.mpObject->mpCallback = 0;
                    ev.mpObject->mpCloseCallback = 0;
                    reuse = true;
                }
                break;
            }
        }
    }
    if (!reuse) {
        cFeedbackEvent* pNew = new ("Simulator/cFeedbackEvent", 0, 0, 0, 0) cFeedbackEvent;
        if (pNew) {
            pNew->AddRef();
            ev.mpObject = pNew;
        }
    }

    IWindow* window;
    if (ev.mpObject->test(kfInvalid) ||
        !(window = ev.mpObject->mpItemLayout->FindWindowByID(0x035ee914, true)))
        return 0;

    window->AddWinProc(this);
    window->FindWindowByID(0x035eef1c, true)->SetCommandID(ev.mpObject->mInstanceID);
    window->SetFlag(1, mbVisible);
    window->FindWindowByID(0x03fffadc, true)->AddWinProc(this);
    IWindow* shade = window->FindWindowByID(0x02b7a911, true);
    shade->SetShadeColor(0xffffff);
    mpAnimator->AddAnimation(
        SPUICreateWindowAnimationTargetShadeAlpha(shade, mGlobalAlpha, SPUIHelpers::GetElapsedSeconds(),
                                                  g_016a09ac, 0),
        ev.mpObject, ((uint32_t)shade << 8) ^ 0x02b7a911);
    ev.mpObject->mTimeCreated = SPUIHelpers::GetElapsedSeconds();
    ev.mpObject->mTypeID = instanceID;
    ev.mpObject->mGroupID = groupID;
    ev.mpObject->mData = (uint32_t)userData;

    cString text;
    GetPropertyAsText(list.mpObject, 0x2bb8697, &text);
    const wchar_t* begin = text.GetText();
    const wchar_t* end = begin;
    while (*end)
        ++end;
    ev.mpObject->mEventString.assign(begin, begin + (end - begin));

    Key key;
    key.mInstance = key.mType = key.mGroup = 0;
    if (GetPropertyAsKey(list.mpObject, 0x402cc7d, &key)) {
        for (uint32_t i = 0; i < 7; ++i)
            if (g_015a2b3c[i] == key.mInstance)
                ev.mpObject->mCategory = i;
    }
    if (ev.mpObject->mCategory == 6) {
        Key key2;
        key2.mInstance = key2.mType = key2.mGroup = 0;
        if (GetPropertyAsKey(list.mpObject, 0x65fded2, &key2)) {
            for (int i = 0; i < g_015a2b88; ++i)
                if (g_015a2b5c[i] == key2.mInstance)
                    ev.mpObject->mScaleIndex = i;
        }
    }

    if (Property* p = GetPropertyOfType(list.mpObject, 0x2bb870e, 0xd))
        ev.mpObject->mTimeToLive = *(float*)PropertyData(p);
    if (ev.mpObject->mTimeToLive < 0.0f || ev.mpObject->mCategory == 3) {
        ev.mpObject->mTimeToLive = -1.0f;
        ev.mpObject->mFlags |= 0x800;
    }
    if (Property* p = GetPropertyOfType(list.mpObject, 0x4b2df7c, 0xd))
        ev.mpObject->mRemoveTime = *(float*)PropertyData(p);

    ev.mpObject->mbUniverseBound = false;
    if (Property* p = GetPropertyOfType(list.mpObject, 0x680959a, 1))
        ev.mpObject->mbUniverseBound = *(bool*)PropertyData(p);
    if (ev.mpObject->mbUniverseBound)
        ev.mpObject->mpUniverseContext = GetUniverseContext_01021080();

    window->FindWindowByID(ev.mpObject->mCategory + 0x3ffb8f0, true)->AddWinProc(this);
    window->FindWindowByID(ev.mpObject->mCategory + 0x3fe9970, true)->AddWinProc(this);
    if (pPosition) {
        ev.mpObject->mPosition[0] = pPosition[0];
        ev.mpObject->mPosition[1] = pPosition[1];
        ev.mpObject->mPosition[2] = pPosition[2];
    }

    String8 str;
    str.mpBegin = g_01667bac;
    str.mpEnd = g_01667bac;
    str.mpCapacity = g_01667bac + 1;
    if (GetPropertyAsString8(list.mpObject, 0x4498e8a, &str) && strcmp(str.mpBegin, g_013ec47c) != 0) {
        flag = true;
        ev.mpObject->mpCallback = FUN_00ae0b80;
    } else {
        flag = false;
    }

    if (list.mpObject->HasProperty(0x3a788a6)) {
        Key snd;
        snd.mInstance = snd.mType = snd.mGroup = 0;
        GetPropertyAsKey(list.mpObject, 0x3a788a6, &snd);
        EASystemAT* at = GetSystemAT();
        PlayEventSound(snd.mInstance, at ? at->GetHandle() : 0);
    } else {
        uint32_t sound;
        switch (ev.mpObject->mCategory) {
            case 0: case 5: sound = g_016a0a9c; break;
            case 1: sound = g_016a0a7c; break;
            case 4: sound = g_016a0a8c; break;
            case 2: sound = g_016a0aac; break;
            case 3: sound = g_016a0abc; break;
            default: sound = 0; break;
        }
        if (sound) {
            EASystemAT* at = GetSystemAT();
            PlayEventSound(sound, at ? at->GetHandle() : 0);
        }
    }

    mLastEventEntered = ev.mpObject->mInstanceID;
    mEvents.GetOrInsert(mLastEventEntered).Assign(ev.mpObject);
    if (cFeedbackEvent* old = find_in_history(ev.mpObject))
        remove_event(old->mInstanceID);
    update_event_ui_state(ev.mpObject);
    if (flag) {
        Property* p = GetPropertyOfType(list.mpObject, 0x4d7f317, 1);
        if (p && *p->GetBool())
            ev.mpObject->mpCallback(ev.mpObject->mInstanceID, ev.mpObject->mpCallbackArg);
    }
    uint32_t result = mLastEventEntered;
    if (str.mpCapacity - str.mpBegin > 1 && str.mpBegin)
        operator_delete_array_00f47380(str.mpBegin);
    return result;
}

// ---------------------------------------------------------------- event map
// @ 0x00dd85c0
EventSlot& EventMap::GetOrInsert(const uint32_t& key)
{
    EventNode* y = (EventNode*)&mAnchor;
    rbtree_node_base* x = mAnchor.mpNodeParent;
    while (x != 0) {
        EventNode* node = (EventNode*)x;
        if (node->mKey < key) {
            x = node->mpNodeRight;
        } else {
            y = node;
            x = node->mpNodeLeft;
        }
    }
    if (y != (EventNode*)&mAnchor && !(key < y->mKey))
        return y->mValue;
    EventNode* inserted = (EventNode*)FUN_00dd6f50(&key, y, false);
    return inserted->mValue;
}

// ---------------------------------------------------------------- cSPUIEventLog
// @ 0x00dd8d80
void cSPUIEventLog::Update(int param)
{
    if (mpAnimator) {
        mpAnimator->Update();
        FUN_00dd7970(param);
    }
}

// @ 0x00dd8da0
void cSPUIEventLog::SetVisibility(bool bVisible)
{
    if (mbVisible != bVisible) {
        mbVisible = bVisible;
        if (!bVisible) {
            cWindowManager* pManager = WindowManager();
            pManager->SetVisible(1, 0);
        }
        for (rbtree_node_base* it = mEvents.mAnchor.mpNodeLeft; it != &mEvents.mAnchor;
             it = RBTreeIncrement_00921580(it)) {
            cFeedbackEvent* pEvent = ((EventNode*)it)->mValue.mpObject;
            IWindow* pWindow = pEvent->mpItemLayout->FindWindowByID(0x35ee914, true);
            if (pWindow)
                pWindow->SetFlag(1, mbVisible);
        }
    }
    if (mpAnimator) {
        mpAnimator->Update();
        FUN_00dd7970(1);
    }
}

// ---------------------------------------------------------------- stopwatch driven throbber
// @ 0x00dd8e30
void __stdcall FUN_00dd8e30(cSPUIThrobber* pTarget)
{
    uint64_t ticks;
    EAStopwatch* pStopwatch = &pTarget->mStopwatch;
    if (pStopwatch->mnMode == 1) {
        ticks = (uint64_t)rdtsc64();
        pStopwatch->mLow = (uint32_t)ticks;
    } else {
        uint64_t counter;
        QueryPerformanceCounter(&counter);
        ticks = counter;
        pStopwatch->mLow = (uint32_t)ticks;
    }
    pStopwatch->mHigh = (uint32_t)(ticks >> 32);
    pStopwatch->mElapsedLow = 0;
    pStopwatch->mElapsedHigh = 0;
    uint32_t soundId = pTarget->mSoundId;
    if (soundId != 0)
        FUN_00572020(soundId, 1);
}

// @ 0x00dd8f50
void __stdcall FUN_00dd8f50(cSPUIThrobber* pTarget)
{
    uint64_t ticks;
    EAStopwatch* pStopwatch = &pTarget->mStopwatch;
    if (pStopwatch->mnMode == 1) {
        ticks = (uint64_t)rdtsc64();
        pStopwatch->mLow = (uint32_t)ticks;
    } else {
        uint64_t counter;
        QueryPerformanceCounter(&counter);
        ticks = counter;
        pStopwatch->mLow = (uint32_t)ticks;
    }
    pStopwatch->mHigh = (uint32_t)(ticks >> 32);
    pStopwatch->mElapsedLow = 0;
    pStopwatch->mElapsedHigh = 0;
    uint32_t soundId = pTarget->mSoundId;
    EASystemAT* pAudio = GetSystemAT();
    if (pAudio) {
        pAudio->PlaySoundEvent(0x347536b);
        pAudio->SetSoundParam(0x3475385, soundId);
        pAudio->SetSoundParam(0x34753a0, 1);
        pAudio->StopSoundEvent();
    }
}

// @ 0x00dd8ff0
void __stdcall FUN_00dd8ff0(cSPUIThrobber* pTarget)
{
    pTarget->mSoundPosition = pTarget->mPosition;
    uint32_t soundId = pTarget->mSoundId;
    Start3dSoundByName(0x44f21a5d, soundId, pTarget->mPosition.x, pTarget->mPosition.y,
                       pTarget->mPosition.z);
}

// @ 0x00dd9040
void __stdcall FUN_00dd9040(cSPUIThrobber* pTarget)
{
    pTarget->mbFinished = 1;
}

// @ 0x00dd9050
bool __stdcall FUN_00dd9050(cSPUIThrobber* pTarget, int unused)
{
    if (pTarget->mPosition.y >= g_013f561c)
        return true;
    pTarget->mbFinished = 0;
    return false;
}

// @ 0x00dd8ea0
bool cThrobberAnimator::FUN_00dd8ea0(cSPUIThrobber* pTarget, float unused)
{
    EAStopwatch* pStopwatch = &pTarget->mStopwatch;
    bool bFinished = true;
    float t = (float)pStopwatch->GetElapsedTimeFloat() * pStopwatch->mPeriod;
    if (t > 1.0f) {
        pStopwatch->SetBoolProperty();
        t = 1.0f;
        bFinished = false;
    }
    if (!mbReverse)
        t = 1.0f - t;
    float wobble = sinf(-g_016a0b58 * t) * pTarget->mfA8 * 0.5f;
    pTarget->mf98 = pTarget->mfA8 * t + wobble;
    return bFinished;
}

// The original takes the element in EDI, so this is a __usercall in the retail build.
// @ 0x00dd9080
void cSPUIThrobber::FUN_00dd9080()
{
    EAStopwatch* pStopwatch = &mStopwatch;
    if (pStopwatch->mLow != 0 || pStopwatch->mHigh != 0) {
        float t = (float)pStopwatch->GetElapsedTimeFloat() * pStopwatch->mPeriod;
        t = t / g_015a2de0;
        if (t > 1.0f) {
            pStopwatch->SetBoolProperty();
            t = 1.0f;
        }
        if (mbReverse)
            mf98 = (1.0f - t) * mfA8;
        else
            mf98 = mfA8 * t;
    }
}

// ---------------------------------------------------------------- orientation helpers
// The retail build passes the direction in EBX and returns the two basis vectors through
// EDI/ESI, so this is a __usercall; the natural form takes them as ordinary out parameters.
// @ 0x00dd9130
void FUN_00dd9130(const float* pDirection, Vec3* pOutA, Vec3* pOutB)
{
    if (FUN_00b7d4f0(FUN_00b3d360(pDirection))) {
        FUN_00b7d440(pDirection[0], pDirection[1], pDirection[2], 0, 0, 0, 0, pOutA, pOutB);
    } else {
        pOutA->x = 0.0f;
        pOutA->y = 0.0f;
        pOutA->z = 0.0f;
        pOutB->x = 0.0f;
        pOutB->y = 0.0f;
        pOutB->z = 0.0f;
    }
}

// Retail takes the two directions in EAX/ECX and returns the quaternion in ESI (__usercall).
// @ 0x00dd91b0
Quaternion* FUN_00dd91b0(const Vec3* pA, const Vec3* pB, Quaternion* pOut)
{
    Vec3 cross1, cross2, normal;
    float scale;

    cross1.x = pA->z * pB->y - pA->y * pB->z;
    cross1.y = pA->x * pB->z - pA->z * pB->x;
    cross1.z = pA->y * pB->x - pA->x * pB->y;
    scale = 1.0f / sqrtf(cross1.x * cross1.x + cross1.y * cross1.y + cross1.z * cross1.z + g_013ec4b8);
    cross1.x = cross1.x * scale;
    cross1.y = cross1.y * scale;
    cross1.z = cross1.z * scale;

    cross2.x = cross1.y * pA->z - cross1.z * pA->y;
    cross2.y = cross1.z * pA->x - cross1.x * pA->z;
    cross2.z = cross1.x * pA->y - cross1.y * pA->x;
    scale = 1.0f / sqrtf(cross2.x * cross2.x + cross2.y * cross2.y + cross2.z * cross2.z + g_013ec4b8);
    cross2.x = cross2.x * scale;
    cross2.y = cross2.y * scale;
    cross2.z = cross2.z * scale;

    normal = *pA;
    scale = 1.0f / sqrtf(pA->x * pA->x + pA->y * pA->y + pA->z * pA->z + g_013ec4b8);
    normal.x = normal.x * scale;
    normal.y = normal.y * scale;
    normal.z = normal.z * scale;

    Matrix33 matrix;
    matrix.m[0][0] = cross2.x;
    matrix.m[0][1] = cross2.y;
    matrix.m[0][2] = cross2.z;
    matrix.m[1][0] = cross1.x;
    matrix.m[1][1] = cross1.y;
    matrix.m[1][2] = cross1.z;
    matrix.m[2][0] = normal.x;
    matrix.m[2][1] = normal.y;
    matrix.m[2][2] = normal.z;

    Quaternion temp;
    Quaternion* pQuat = QuaternionFromMatrix33_00472b80(&temp, &matrix, 0.0f);
    pOut->x = pQuat->x;
    pOut->y = pQuat->y;
    pOut->z = pQuat->z;
    pOut->w = pQuat->w;
    return pOut;
}

// Retail builds the result in ESI and returns that register (__usercall), so the natural form
// takes the output vector as a parameter.
// @ 0x00dd93d0
Vec3* FUN_00dd93d0(Vec3* pOut)
{
    if (!(g_016a0c5c & 1)) {
        g_016a0c5c |= 1;
        g_016a0c58 = 50.0f;
    }
    if (!(g_016a0c5c & 2)) {
        g_016a0c5c |= 2;
        g_016a0c54 = 35.0f;
    }

    float half = g_016a0c58;
    float length;
    int attempt = 0;
    for (;;) {
        double low = -(double)half;
        double high = (double)half;
        double value = gRandomGlobal_01601760.RandomDouble(low, high);
        if (value < low)
            value = low;
        if (value > high)
            value = high;
        pOut->x = (float)value;

        low = -(double)half;
        high = (double)half;
        value = gRandomGlobal_01601760.RandomDouble(low, high);
        if (value < low)
            value = low;
        if (value > high)
            value = high;
        pOut->y = (float)value;

        pOut->z = 0.0f;
        length = sqrtf(pOut->x * pOut->x + pOut->y * pOut->y + pOut->z * pOut->z);
        if (g_016a0c54 <= length && length <= g_016a0c58)
            break;
        int current = attempt;
        ++attempt;
        if (current >= 1000)
            break;
    }
    return pOut;
}
