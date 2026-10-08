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

struct cSPUILayout {
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
struct cSPUIAnimator {
    void AddAnimation(const cSPUIWindowAnimation& anim, Object* owner, uint32_t id);  // 0x007f8d10
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
    EventSlot& operator[](const uint32_t& key);                   // 0x00dd85c0
};

struct EASystemAT { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
                    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
                    virtual int GetHandle(); };                    // +0x20
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
};

#pragma pack(pop)

// @ 0x00dd8640
uint32_t cSPUIEventLog::PostFeedbackEvent(uint32_t instanceID, uint32_t groupID, const float* pPosition,
                                          bool bAlways, int unused, void* userData)
{
    ListRef list;
    PropertyManager()->GetPropertyList(groupID, instanceID, list.Reset());
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
    mEvents[mLastEventEntered].Assign(ev.mpObject);
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
