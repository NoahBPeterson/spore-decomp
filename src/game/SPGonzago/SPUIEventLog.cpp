// src/game/SPGonzago/SPUIEventLog.cpp -- migrated from slice(s) s00dd7970, s00dd6a70, s00dd5a30 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUIEventLog.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUIAnimator.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern uint32_t g_016a0958;      // next instance id
extern float g_016a0960;         // default position x
extern float g_016a0964;         // default position y
extern float g_016a0968;         // default position z
extern float g_016a09ac;         // animation duration
extern float g_016a0a5c;         // iconic-mode lead time
extern float g_016a0adc;         // iconic-mode threshold
extern float g_016a0afc;         // fade-in delay
extern float g_0143c70;          // 10.0f (time to live)
extern float g_013eb1bc;         // -1.0f
extern float g_01477fbc;         // 100.0f
extern wchar_t g_01667bac[];     // eastl empty string storage
extern const char g_015d9c70;
#pragma pack(push, 4)

// ---- items of slice s00dd5a30 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Object {
    virtual int AddRef();          // +0x00 slot 0
    virtual int Release();         // +0x04 slot 1
    virtual ~Object() {}           // +0x08 slot 2
};
struct IUnknown32 : Object {
    virtual void* QueryInterface(uint32_t id);   // +0x0c slot 3
};
struct IWindow : Object {
    virtual void* QueryInterface(uint32_t id);       // +0x0c
    virtual IWindow* GetOwner();                     // +0x10
    virtual void s14();                              // +0x14
    virtual void s18();                              // +0x18
    virtual int GetControlID();                      // +0x1c
    virtual void s20();                              // +0x20
    virtual void s24();                              // +0x24
    virtual bool IsFlagSet();                        // +0x28
    virtual float* GetPosition();                    // +0x2c
    virtual void s30();                              // +0x30
    virtual void s34();                              // +0x34
    virtual const float* GetRealArea();              // +0x38
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
    virtual void SetArea(float x, float y, float w, float h);  // +0x6c
    virtual void s70();                              // +0x70
    virtual void SetSize(float w, float h);          // +0x74
    virtual void s78();                              // +0x78
    virtual void SetFlag(int flag, bool value);      // +0x7c
    virtual void SetPosition(float x, float y);      // +0x80
virtual void s84();
virtual void s88();
virtual void s8c();
    virtual void Invalidate();                       // +0x90
virtual void s94();
virtual void s98();
virtual void s9c();
virtual void sa0();
virtual void sa4();
    virtual void* GetDrawable();                     // +0xa8
    virtual void SetShadeColor(uint32_t color);      // +0xac
virtual void sb0();
virtual void sb4();
virtual void sb8();
virtual void sbc();
virtual void sc0();
virtual void sc4();
virtual void sc8();
    virtual void* ChildrenBegin(void* it);           // +0xcc
    virtual void* ChildrenNext(void* it);            // +0xd0
virtual void sd4();
virtual void sd8();
virtual void sdc();
virtual void se0();
virtual void se4();
virtual void se8();
virtual void sec();
    virtual void Anchor(int mode);                   // +0xe4
    virtual void se8b();                             // +0xe8
    virtual void secb();                             // +0xec
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);  // +0xf0
    virtual void sf4();                              // +0xf4
    virtual void sf8();                              // +0xf8
    virtual void sfc();                              // +0xfc
    virtual void s100();                             // +0x100
    virtual void AddWinProc(void* proc);             // +0x104
};
class cSPUILayout_s00dd_5a30 {
 public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);        // 0x008105b0
};
struct AnimRaw {
    void* mpVtbl0;        // +0x00
    void* mpVtbl1;        // +0x04
    uint32_t m08;         // +0x08
    void* mpVtbl2;        // +0x0c
    Object* mpTarget;     // +0x10
    uint32_t raw70[0x70 / 4];   // +0x14..+0x83
    Object* mpTarget2;    // +0x84
    ~AnimRaw() {
        if (mpTarget) mpTarget->Release();
        if (mpTarget2) mpTarget2->Release();
    }
};
AnimRaw* SPUICreateWindowAnimationTargetShadeAlphaW(AnimRaw* out, IWindow* window, int alpha,
                                                    float start, float duration, int interp,
                                                    void* owner, uint32_t id);        // 0x007f8290
void* SPUICreateWindowAnimationTargetSize(AnimRaw* out, void* window, float* pos, float* size,
                                          void* owner, uint32_t id);                 // 0x007f73e0
void* FUN_007f9340(AnimRaw* out, void** pOut);                                         // 0x007f9340
void FUN_007f60d0(void* out, float a, float b, float c, float d, int e);              // 0x007f60d0
class cSPUIAnimator_s00dd_5a30 {
 public:
    void* Append(void* anim, void* owner, uint32_t id);          // 0x007f8fd0
    void AddAnimation(void* anim, void* owner, uint32_t id);     // 0x007f8d10
};
namespace SPUIHelpers {
float GetElapsedSeconds();                                       // 0x00805080
}
extern uint32_t g_016a0958;      // next instance id
extern float g_016a0960;         // default position x
extern float g_016a0964;         // default position y
extern float g_016a0968;         // default position z
extern float g_016a09ac;         // animation duration
extern float g_016a0a5c;         // iconic-mode lead time
extern float g_016a0adc;         // iconic-mode threshold
extern float g_016a0afc;         // fade-in delay
extern float g_0143c70;          // 10.0f (time to live)
extern float g_013eb1bc;         // -1.0f
extern float g_01477fbc;         // 100.0f
extern wchar_t g_01667bac[];     // eastl empty string storage
extern const char g_015d9c70;
bool CompareEventStrings(const void* a, const void* b);           // 0x0087d9a0
void Pollinator(void* child, float* rect);                       // 0x00806d10
cSPUILayout_s00dd_5a30* create_event_layout();                              // 0x00dd5990
struct WString {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    uint32_t mAllocator; // +0x0c
};
struct Vector3 { float x, y, z; };
class RefCountBase {
 public:
    virtual ~RefCountBase() {}
    virtual int AddRef();
    virtual int Release();
    virtual int GetRefCount() const;
    int mRefCount;       // +0x04
};
class IRefBase {
 public:
    virtual int AddRef();
    virtual int Release();
    virtual ~IRefBase() {}
};
enum {
    kfNew = 0, kfDoNotAddToHistory = 1, kfTextDirty = 2, kfFadingIn = 4, kfFadingOut = 5,
    kfExpired = 6, kfRemove = 7, kfInvalid = 8, kfHistory = 9, kfIconicMode = 10, kfPermanent = 11
};
class cFeedbackEvent : public IRefBase, public RefCountBase {
 public:
    uint32_t mFlags;              // +0x0c eastl::bitset<12>
    uint32_t mCategory;           // +0x10
    uint32_t mScaleIndex;         // +0x14
    float mScale;                 // +0x18 (1.0f)
    uint32_t mAlphaByte;          // +0x1c (0xff)
    float mPosition[3];           // +0x20
    float mTimeAnimStarted;       // +0x2c
    float mTimeCreated;           // +0x30
    float mTimeToLive;            // +0x34
    float mRemoveTime;            // +0x38
    uint32_t m3c;                 // +0x3c
    uint32_t m40;                 // +0x40
    uint32_t m44;                 // +0x44
    uint32_t mInstanceID;         // +0x48
    uint32_t mTypeID;             // +0x4c
    uint32_t mGroupID;            // +0x50
    uint32_t mData;               // +0x54
    IUnknown32* mpUserData;       // +0x58
    uint32_t mData3;              // +0x5c
    union { uint32_t m60; uint8_t m60b; };   // +0x60
    uint32_t m64;                 // +0x64
    WString mEventString;         // +0x68
    cSPUILayout_s00dd_5a30* mpItemLayout;    // +0x78
    uint32_t mBackGroundId;       // +0x7c
    uint32_t m80; uint32_t m84;
    float mIconPosX; uint32_t m8c;
    float m90;                    // +0x90

    cFeedbackEvent();
    virtual ~cFeedbackEvent() {}

    bool test(int n) const { return ((mFlags >> n) & 1) != 0; }
    void set(int n) { mFlags |= 1u << n; }
};
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;   // +0x00
    rbtree_node_base* mpNodeLeft;    // +0x04
    rbtree_node_base* mpNodeParent;  // +0x08
    char mColor;                     // +0x0c
};
struct EventNode : rbtree_node_base {
    uint32_t mKey;        // +0x10
    cFeedbackEvent* mValue;  // +0x14
};
rbtree_node_base* RBTreeIncrement_00921580(const rbtree_node_base* pNode);   // 0x00921580
struct EventMap {
    uint32_t mCompare;            // +0x00
    rbtree_node_base mAnchor;     // +0x04
    uint32_t mnSize;              // +0x18
    uint32_t mAllocator;          // +0x1c

    rbtree_node_base** find(rbtree_node_base** pResult, const uint32_t* key);   // 0x00e5c780
};
class cSPUIEventLog {
 public:
    char pad00[0x20];
    uint32_t mGlobalAlpha;        // +0x20
    bool mbVisible;               // +0x24
    char pad25[3];
    EventMap mEvents;             // +0x28
    uint32_t mLastEventEntered;   // +0x44
    float mLastUpdateTime;        // +0x48
    float mLogPosition[2];        // +0x4c
    float mLogOffset[2];          // +0x54
    float mLogTop;                // +0x5c
    float mLogTopCurrent;         // +0x60
    int mHistorySize;             // +0x64
    cSPUIAnimator_s00dd_5a30* mpAnimator;    // +0x68
    void* mTuningProps;           // +0x6c

    cFeedbackEvent* GetEventInstanceID(uint32_t typeID, uint32_t data3);   // 0x00dd5d80
    cFeedbackEvent* find_in_history(cFeedbackEvent* ev);                   // 0x00dd5dd0
    cFeedbackEvent* find_event(uint32_t id);                               // 0x00dd6710
    bool EventDoNotAddToHistory(uint32_t id, uint32_t unused);             // 0x00dd67d0
    bool GetPositionOfLastEvent(float* out);                               // 0x00dd6810
    void* GetEventText(int unused);                                        // 0x00dd68e0
    bool ModifyData(uint32_t id, uint32_t data);                           // 0x00dd6930
    bool ModifyUserData(uint32_t id, IUnknown32* p);                       // 0x00dd6980
    bool GetEventData(uint32_t id, uint32_t* a, uint32_t* b, uint32_t* c, IUnknown32** d); // 0x00dd69f0
    void update_event_ui_state(cFeedbackEvent* ev);                        // 0x00dd60c0
    void show_iconic_text(cFeedbackEvent* ev, bool iconic);                // 0x00dd5a30
    void show_text(cFeedbackEvent* ev, bool b);                            // 0x00dd6570
    void update_ui(cFeedbackEvent* ev, bool b);                            // 0x00dd5bb0
};
struct Property {
    uint32_t pad00[4];
    uint16_t mnFlags;    // +0x10
    uint16_t mnType;     // +0x12
};
struct IPropertyHost {
virtual int AddRef();
virtual int Release();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
    virtual bool GetProperty(void* context, void** out);   // slot 9, +0x24
};
struct BytePropertyCache {
    void* mOwner;        // +0x00
    void* mContext;      // +0x04
    uint32_t mPad8;      // +0x08
    char mCached;        // +0x0c
    bool Update(void* property);   // 0x00dd5e30
};
// ---- items of slice s00dd5a30 end

// ---- items of slice s00dd6a70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float        DAT_016a0a0c;        // float global
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct EventNodeBase {
    EventNodeBase* mpNodeLeft;    // +0x00
    EventNodeBase* mpNodeRight;   // +0x04
    EventNodeBase* mpNodeParent;  // +0x08
    unsigned       mColor;        // +0x0c
};
struct EventNode_s00dd_6a70 : EventNodeBase {
    unsigned mKey;                // +0x10
    void*    mValue;              // +0x14  AutoRefCount<cFeedbackEvent>::mpObject
};
struct EventIter {                // non-POD, returned through a hidden pointer
    EventNode_s00dd_6a70* mpNode;
    EventIter() {}
};
struct EventTree {
    unsigned      mPad00;         // +0x00
    EventNodeBase mAnchor;        // +0x04  (left +0x04, right +0x08, parent +0x0c)
    unsigned      mnSize;         // +0x14
    // 0x00e5c780  __thiscall find(const unsigned& k) -> EventIter (hidden ret)
    EventIter find(const unsigned& k);
};
struct IWindow_s00dd_6a70 {                          // a cSPUIWindow
    PV2 PV
    virtual void*    Slot0C(unsigned id);         // +0x0c
    PV2 PV
    virtual unsigned Slot1C();                    // +0x1c  window id
    PV8 PV4 PV2 PV
    virtual void     Slot5C(unsigned alpha);      // +0x5c
    PV4 PV2 PV
    virtual void     Slot7C(int a, int b);        // +0x7c
    PV8 PV8 PV8 PV4
    virtual IWindow_s00dd_6a70* SlotF0(unsigned a, int b);   // +0xf0
};
struct cSPUILayout_s00dd_6a70 {
    IWindow_s00dd_6a70* FindWindowByID(unsigned id, int flag);  // 0x008105b0
    void     SetVisibility(int v);                   // 0x00810590
    void     Shutdown(unsigned);                     // 0x00811ad0
    bool     Init(void* key, int a, int b);          // 0x008120d0
};
struct cSPUIAnimator_s00dd_6a70 {
    void RemoveAnimation(void* p, int z);            // 0x007f6210
};
struct EventString {                  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;                 // +0x00
    wchar_t* mpEnd;                   // +0x04
    wchar_t* mpCap;                   // +0x08
    void append(const wchar_t* s);    // 0x005c3d90
};
struct cFeedbackEvent_s00dd_6a70 {
    void*    mpVtbl;                  // +0x00
    char     pad004[0x08];            // +0x04..+0x0b
    union {
        unsigned mFlags;              // +0x0c  bit0(0x1) bit2(0x4) bit6(0x40) bit9(0x200) bit10(0x400) bit11(0x800)
        struct {
            unsigned mTextDirty : 1;  // bit 0
            unsigned mB1        : 1;
            unsigned mB2        : 1;  // bit 2
            unsigned            : 3;
            unsigned mB6        : 1;  // bit 6
            unsigned            : 2;
            unsigned mInHistory : 1;  // bit 9
            unsigned mB10       : 1;  // bit 10
            unsigned mPaused    : 1;  // bit 11
            unsigned            : 20;
        };
    };
    char     pad010[0x0c];            // +0x10..+0x1b
    int      m1c;                     // +0x1c
    char     pad020[0x10];            // +0x20..+0x2f
    float    mRestartTime;            // +0x30
    float    mDuration;               // +0x34
    char     pad038[0x10];            // +0x38..+0x47
    int      m48;                     // +0x48
    char     pad04c[0x0c];            // +0x4c..+0x57
    void*    m58;                     // +0x58
    int      m5c;                     // +0x5c
    int      mCloseCallback;          // +0x60
    void (*mCallback)(int, int);      // +0x64
    EventString mText;                // +0x68
    char     pad074[0x04];            // +0x74
    cSPUILayout_s00dd_6a70* mpLayout;            // +0x78
};
struct IRefCount {                    // AutoRefCount<...>::mpObject points here
    virtual void AddRef();            // slot 0
    virtual void Release();           // slot 1
};
float SPUIHelpers_GetElapsedSeconds();   // 0x00805080
EventNodeBase* eastl_RBTreeIncrement(EventNodeBase*);          // 0x00921580
void           eastl_RBTreeErase(EventNodeBase*, EventNodeBase*);  // 0x00921880
struct cSPUIEventLog_s00dd_6a70 {
    void*          mpVtbl;                // +0x00
    char           pad004[0x1c];          // +0x04..+0x1f
    unsigned       mGlobalAlpha;          // +0x20
    unsigned char  mbVisible;             // +0x24
    char           pad025[3];
    EventTree      mEvents;               // +0x28..+0x3f
    char           pad040[4];             // +0x40..+0x43
    int            m44;                   // +0x44
    float          mMainWindowArea[4];    // +0x48..+0x57
    char           pad058[4];             // +0x58..+0x5b
    float          m5c;                   // +0x5c
    float          m60;                   // +0x60
    int            mHistorySize;          // +0x64
    cSPUIAnimator_s00dd_6a70* mpAnimator;            // +0x68
    void*          mTuningProps;          // +0x6c

    void update_event_ui_state(cFeedbackEvent_s00dd_6a70* ev);       // 0x00dd60c0
    cFeedbackEvent_s00dd_6a70* find_in_history(cFeedbackEvent_s00dd_6a70* ev);  // 0x00dd5dd0
    void FUN_00dd6570(cFeedbackEvent_s00dd_6a70* ev, int z);         // 0x00dd6570

    bool RestartTimer(unsigned id);                   // 0x00dd6a70
    void SetEventDuration(unsigned id, float dur);    // 0x00dd6ac0
    int  RegisterCallback(unsigned id);               // 0x00dd6b20
    bool RegisterCloseCallback(unsigned id, int cb);  // 0x00dd6b70
    void remove_event(unsigned id);                   // 0x00dd6bc0
    void RemoveEvent(unsigned id, char immediate);    // 0x00dd6d10
    void clear_events();                              // 0x00dd6d70
    bool ModifyEventText(unsigned id, const wchar_t* text);  // 0x00dd6df0
    void add_to_history(cFeedbackEvent_s00dd_6a70* ev);          // 0x00dd6ec0
};
// ---- items of slice s00dd6a70 end


// @ 0x00dd5a30
void cSPUIEventLog::show_iconic_text(cFeedbackEvent* ev, bool iconic)
{
    IWindow* win = ev->mpItemLayout->FindWindowByID(0x4000548, 1);
    void* helper;
    AnimRaw anim;
    FUN_007f9340(&anim, &helper);
    float now = SPUIHelpers::GetElapsedSeconds();
    float dur = (ev->mFlags & 1) ? 0.0f : g_016a09ac;
    uint32_t key = ((uint32_t)win << 8) ^ 0x2b7a911;

    AnimRaw tmp;
    SPUICreateWindowAnimationTargetShadeAlphaW(&tmp, win, iconic ? 0xff : 0, now, dur, 0, ev, key);
    mpAnimator->Append(&tmp, ev, key);
    if (iconic) {
        float start = g_016a0a5c + now;
        SPUICreateWindowAnimationTargetShadeAlphaW(&tmp, win, 0, start, now, 0, ev, key);
        mpAnimator->Append(&tmp, ev, key);
        }
    mpAnimator->AddAnimation(&anim, ev, key);
}

// @ 0x00dd5bb0
void cSPUIEventLog::update_ui(cFeedbackEvent* ev, bool b)
{
    if (ev->m90 > g_016a0adc) {
        char helper[0x20];
        FUN_007f60d0(helper, g_016a0afc, 0.5f, 0.5f, 0.0f, 0.0f);
        IWindow* win = ev->mpItemLayout->FindWindowByID(0x35ee914, 1);
        IWindow* a = win->FindWindowByID(0x2b7a911, 1);
        IWindow* c = win->FindWindowByID(0x47d4388, 1);
        if (b)
            ev->mTimeAnimStarted = g_016a0afc + SPUIHelpers::GetElapsedSeconds();
        else
            ev->mTimeAnimStarted = 0.0f;
        float h = c->GetRealArea()[3] - c->GetRealArea()[1];
        float w = c->GetRealArea()[2] - c->GetRealArea()[0];
        uint32_t ka = ((uint32_t)a << 8) ^ 0x35eef1d;
        float pos[2] = { 0.0f, 0.0f };
        float size[2] = { w, h };
        AnimRaw anim;
        SPUICreateWindowAnimationTargetSize(&anim, a, pos, size, c, ka);
        mpAnimator->AddAnimation(&anim, c, ka);
        float w2 = c->GetRealArea()[2] - c->GetRealArea()[0];
        float h2 = c->GetRealArea()[3] - c->GetRealArea()[1];
        uint32_t kb = ((uint32_t)c << 8) ^ 0x35eef1d;
        float pos2[2] = { 0.0f, 0.0f };
        float size2[2] = { w2, h2 };
        SPUICreateWindowAnimationTargetSize(&anim, c, pos2, size2, c, kb);
        mpAnimator->AddAnimation(&anim, c, kb);
    }
}

// @ 0x00dd5d80
cFeedbackEvent* cSPUIEventLog::GetEventInstanceID(uint32_t typeID, uint32_t data3)
{
    rbtree_node_base* end = &mEvents.mAnchor;
    for (rbtree_node_base* it = mEvents.mAnchor.mpNodeLeft; it != end;
         it = RBTreeIncrement_00921580(it)) {
        cFeedbackEvent* ev = ((EventNode*)it)->mValue;
        if ((data3 == 0 || data3 == ev->mData3) && ev->mTypeID == typeID)
            return (cFeedbackEvent*)ev->mInstanceID;
    }
    return 0;
}

// @ 0x00dd5dd0
cFeedbackEvent* cSPUIEventLog::find_in_history(cFeedbackEvent* p)
{
    rbtree_node_base* end = &mEvents.mAnchor;
    for (rbtree_node_base* it = mEvents.mAnchor.mpNodeLeft; it != end;
         it = RBTreeIncrement_00921580(it)) {
        cFeedbackEvent* ev = ((EventNode*)it)->mValue;
        if (ev->test(kfHistory) &&
            CompareEventStrings(&p->mEventString, &ev->mEventString))
            return ev;
    }
    return 0;
}

// @ 0x00dd5e30
bool BytePropertyCache::Update(void* property)
{
    IPropertyHost* host = (IPropertyHost*)property;
    if (host->GetProperty(mContext, &property)) {
        Property* p = (Property*)property;
        uint16_t type = p->mnType;
        const char* data;
        if (type == 1 || type == 0x10) {
            if (p->mnFlags & 0x30)
                data = *(const char**)p;
            else
                data = type ? (const char*)p : 0;
        } else {
            data = &g_015d9c70;
        }
        char v = *data;
        if (mCached != v) {
            mCached = v;
            return true;
        }
    }
    return false;
}

// @ 0x00dd5e90
cFeedbackEvent::cFeedbackEvent()
{
    mFlags = 0;
    mScale = 1.0f;
    mCategory = 0;
    mScaleIndex = 0;
    mAlphaByte = 0xff;
    mPosition[0] = g_016a0960;
    mPosition[1] = g_016a0964;
    mPosition[2] = g_016a0968;
    mTimeAnimStarted = 0.0f;
    mTimeToLive = g_0143c70;
    mRemoveTime = g_013eb1bc;
    mInstanceID = ++g_016a0958;
    mTypeID = 0;
    mGroupID = 0;
    mpUserData = 0;
    mData3 = 0;
    m60 = 0;
    m64 = 0;
    mEventString.mpBegin = g_01667bac;
    mEventString.mpEnd = g_01667bac;
    mEventString.mpCapacity = g_01667bac + 1;
    mpItemLayout = create_event_layout();
    mBackGroundId = 0;
    m90 = g_01477fbc;
    mFlags |= 9;
    if (mpItemLayout->FindWindowByID(0x35ee914, 1) == 0)
        mFlags |= 0x100;
    else
        mFlags &= ~0x100u;
    if ((mFlags >> 8) & 1)
        return;
    IWindow* w = mpItemLayout->FindWindowByID(0x35f06c8, 1);
    const float* r = w->GetRealArea();
    float rect[4];
    rect[0] = 0.0f;
    rect[1] = 0.0f;
    rect[2] = r[2] - r[0];
    rect[3] = r[3] - r[1];
    void* it;
    w->ChildrenBegin(&it);
    void* cur = w->ChildrenNext(&it);
    while (cur) {
        Pollinator(cur, rect);
        ((IWindow*)cur)->SetShadeColor(0);
        cur = w->ChildrenNext(&it);
    }
}

// @ 0x00dd6570
void cSPUIEventLog::show_text(cFeedbackEvent* ev, bool b)
{
    IWindow* icon = ev->mpItemLayout->FindWindowByID(0x35ee914, 1);
    IWindow* item = ev->mpItemLayout->FindWindowByID(0x2b7a911, 1);
    IWindow* text = ev->mpItemLayout->FindWindowByID(0x4000548, 1);
    item->SetFlag(1, b);
    text->SetFlag(1, 1);
    uint32_t alpha;
    float duration;
    if (b) {
        alpha = 0xff;
        duration = 0.0f;
    } else {
        alpha = ev->mAlphaByte;
        duration = g_016a0a5c;
    }
    uint32_t key = ((uint32_t)item << 8) ^ 0x2b7a911;
    AnimRaw tmp;
    float start = g_016a09ac + SPUIHelpers::GetElapsedSeconds();
    SPUICreateWindowAnimationTargetShadeAlphaW(&tmp, item, alpha, start, duration, 0, ev, key);
    mpAnimator->AddAnimation(&tmp, ev, key);
    uint32_t key2 = ((uint32_t)item << 8) ^ 0x2b7a911;
    float start2 = SPUIHelpers::GetElapsedSeconds();
    SPUICreateWindowAnimationTargetShadeAlphaW(&tmp, item, b ? 0 : 0xff, start2, g_016a09ac, 0, ev, key2);
    mpAnimator->AddAnimation(&tmp, ev, key2);
    if (b) {
        ev->mFlags &= ~0x400u;
        ev->mTimeCreated = SPUIHelpers::GetElapsedSeconds();
        update_event_ui_state(ev);
    }
}

// @ 0x00dd6710
cFeedbackEvent* cSPUIEventLog::find_event(uint32_t id)
{
    rbtree_node_base* slot;
    rbtree_node_base* node = *mEvents.find(&slot, &id);
    if (node != &mEvents.mAnchor)
        return ((EventNode*)node)->mValue;
    return 0;
}

// @ 0x00dd67d0
bool cSPUIEventLog::EventDoNotAddToHistory(uint32_t id, uint32_t unused)
{
    rbtree_node_base* slot;
    uint32_t key = id;
    rbtree_node_base* node = *mEvents.find(&slot, &key);
    if (node != &mEvents.mAnchor) {
        cFeedbackEvent* ev = ((EventNode*)node)->mValue;
        if (ev)
            ev->mFlags |= 2;
    }
    (void)unused;
    return false;
}

// @ 0x00dd6810
bool cSPUIEventLog::GetPositionOfLastEvent(float* out)
{
    uint32_t key = mLastEventEntered;
    rbtree_node_base* slot;
    rbtree_node_base* node = *mEvents.find(&slot, &key);
    if (node != &mEvents.mAnchor) {
        cFeedbackEvent* ev = ((EventNode*)node)->mValue;
        if (ev) {
            IUnknown32* ud = ev->mpUserData;
            if (ud) {
                void* q = ud->QueryInterface(0x1186577);
                if (q && *(char*)((char*)q + 0x75) != 0) {
                    float* p = (float*)((IWindow*)q)->GetPosition();
                    *(Vector3*)out = *(const Vector3*)p;
                    return true;
                }
            }
            *(Vector3*)out = *(const Vector3*)ev->mPosition;
            if (out[0] != g_016a0960) return true;
            if (out[1] != g_016a0964) return true;
            if (out[2] != g_016a0968) return true;
        }
    }
    return false;
}

// @ 0x00dd68e0
void* cSPUIEventLog::GetEventText(int unused)
{
    uint32_t key = mLastEventEntered;
    rbtree_node_base* slot;
    rbtree_node_base* node = *mEvents.find(&slot, &key);
    (void)unused;
    if (node != &mEvents.mAnchor) {
        cFeedbackEvent* ev = ((EventNode*)node)->mValue;
        if (ev)
            return &ev->mEventString;
    }
    return 0;
}

// @ 0x00dd6930
bool cSPUIEventLog::ModifyData(uint32_t id, uint32_t data)
{
    rbtree_node_base* slot;
    uint32_t key = id;
    rbtree_node_base* node = *mEvents.find(&slot, &key);
    if (node != &mEvents.mAnchor) {
        cFeedbackEvent* ev = ((EventNode*)node)->mValue;
        if (ev) {
            ev->mData3 = data;
            return true;
        }
    }
    return false;
}

// @ 0x00dd6980
bool cSPUIEventLog::ModifyUserData(uint32_t id, IUnknown32* p)
{
    rbtree_node_base* slot;
    uint32_t key = id;
    rbtree_node_base* node = *mEvents.find(&slot, &key);
    if (node != &mEvents.mAnchor) {
        cFeedbackEvent* ev = ((EventNode*)node)->mValue;
        if (ev) {
            IUnknown32* old = ev->mpUserData;
            if (p != old) {
                if (p)
                    p->AddRef();
                ev->mpUserData = p;
                if (old)
                    old->Release();
            }
            return true;
        }
    }
    return false;
}

// @ 0x00dd69f0
bool cSPUIEventLog::GetEventData(uint32_t id, uint32_t* a, uint32_t* b, uint32_t* c, IUnknown32** d)
{
    rbtree_node_base* slot;
    uint32_t key = id;
    rbtree_node_base* node = *mEvents.find(&slot, &key);
    if (node != &mEvents.mAnchor) {
        cFeedbackEvent* ev = ((EventNode*)node)->mValue;
        if (ev) {
            if (a) *a = ev->mTypeID;
            if (b) *b = ev->mGroupID;
            if (c) *c = ev->mData3;
            if (d) {
                IUnknown32* p = ev->mpUserData;
                if (p) {
                    *d = p;
                    p->AddRef();
                }
            }
            return true;
        }
    }
    return false;
}
#pragma pack(pop)

// @ 0x00dd6a70
bool cSPUIEventLog_s00dd_6a70::RestartTimer(unsigned id)
{
    unsigned key = id;
    EventNode_s00dd_6a70* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode_s00dd_6a70*)&this->mEvents.mAnchor) {
        cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)it->mValue;
        if (ev != 0) {
            ev->mRestartTime = SPUIHelpers_GetElapsedSeconds();
            return true;
        }
    }
    return false;
}

// @ 0x00dd6ac0
void cSPUIEventLog_s00dd_6a70::SetEventDuration(unsigned id, float dur)
{
    unsigned key = id;
    EventNode_s00dd_6a70* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode_s00dd_6a70*)&this->mEvents.mAnchor) {
        cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)it->mValue;
        if (ev != 0) {
            ev->mDuration = dur;
            bool paused = (ev->mFlags >> 0xb) & 1;
            if (dur < 0.0f && !paused) {
                ev->mFlags |= 0x800;
                this->update_event_ui_state(ev);
            }
        }
    }
}

// @ 0x00dd6b20
int cSPUIEventLog_s00dd_6a70::RegisterCallback(unsigned id)
{
    unsigned key = id;
    EventNode_s00dd_6a70* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode_s00dd_6a70*)&this->mEvents.mAnchor) {
        cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)it->mValue;
        if (ev != 0) {
            bool inHistory = (ev->mFlags >> 9) & 1;
            if (!inHistory)
                return 1;
        }
    }
    return 0;
}

// @ 0x00dd6b70
bool cSPUIEventLog_s00dd_6a70::RegisterCloseCallback(unsigned id, int cb)
{
    unsigned key = id;
    EventNode_s00dd_6a70* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode_s00dd_6a70*)&this->mEvents.mAnchor) {
        cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)it->mValue;
        if (ev != 0) {
            ev->mCloseCallback = cb;
            this->update_event_ui_state(ev);
            return true;
        }
    }
    return false;
}

// @ 0x00dd6bc0
void cSPUIEventLog_s00dd_6a70::remove_event(unsigned id)
{
    unsigned key = id;
    EventNode_s00dd_6a70* node = this->mEvents.find(key).mpNode;
    if (node == (EventNode_s00dd_6a70*)&this->mEvents.mAnchor)
        return;
    cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)node->mValue;
    if ((ev->mFlags >> 9) & 1)
        this->mHistorySize--;
    if (this->mpAnimator != 0)
        this->mpAnimator->RemoveAnimation(ev, -1);
    if (ev->mCallback != 0)
        ev->mCallback(ev->m48, ev->m5c);

    cSPUILayout_s00dd_6a70* layout = ev->mpLayout;
    IWindow_s00dd_6a70* wins[4];
    wins[0] = layout->FindWindowByID(0x2b7a911, 1);
    wins[1] = layout->FindWindowByID(0x47d4388, 1);
    wins[2] = layout->FindWindowByID(0x4000548, 1);
    wins[3] = 0;
    IWindow_s00dd_6a70* w = layout->FindWindowByID(0x35ee914, 1);
    for (int i = 0; i < 4 && w != 0; ++i) {
        w->Slot7C(1, 1);
        unsigned wid = w->Slot1C();
        w->Slot5C(wid == 0x4000548 ? 0xffffffffu : 0x00ffffffu);
        this->mpAnimator->RemoveAnimation(w, -1);
        w = wins[i];
    }

    this->mEvents.mnSize--;
    EventNode_s00dd_6a70* next = (EventNode_s00dd_6a70*)eastl_RBTreeIncrement(node);
    eastl_RBTreeErase(next, &this->mEvents.mAnchor);
    if (next->mValue != 0)
        ((IRefCount*)next->mValue)->Release();
    operator delete[](next);
}

// @ 0x00dd6d10
void cSPUIEventLog_s00dd_6a70::RemoveEvent(unsigned id, char immediate)
{
    if (immediate == 0) {
        this->remove_event(id);
        return;
    }
    unsigned key = id;
    EventNode_s00dd_6a70* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode_s00dd_6a70*)&this->mEvents.mAnchor) {
        cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)it->mValue;
        if (ev != 0) {
            ev->mB2 = false;
            ev->mDuration = 0.0f;
        }
    }
}

// @ 0x00dd6d70
void cSPUIEventLog_s00dd_6a70::clear_events()
{
    while (this->mEvents.mnSize != 0)
        this->remove_event(((EventNode_s00dd_6a70*)this->mEvents.mAnchor.mpNodeRight)->mKey);
}

// @ 0x00dd6df0
bool cSPUIEventLog_s00dd_6a70::ModifyEventText(unsigned id, const wchar_t* text)
{
    bool r = false;
    if (text != 0) {
        unsigned key = id;
        EventNode_s00dd_6a70* it = this->mEvents.find(key).mpNode;
        if (it != (EventNode_s00dd_6a70*)&this->mEvents.mAnchor) {
            cFeedbackEvent_s00dd_6a70* ev = (cFeedbackEvent_s00dd_6a70*)it->mValue;
            if (ev != 0) {
                IWindow_s00dd_6a70* w = ev->mpLayout->FindWindowByID(0x35ee914, 1);
                if (w != 0) {
                    IWindow_s00dd_6a70* w2 = w->SlotF0(0x47d4388, 1);
                    if (w2 != 0) {
                        void* w3 = w2->Slot0C(0xf15f4bd);
                        if (w3 != 0 && (ev->mText.mpEnd != ev->mText.mpBegin)) {
                            ev->mText.append(text);
                            ev->mB6 = false;
                            ev->mTextDirty = true;
                            this->update_event_ui_state(ev);
                            cFeedbackEvent_s00dd_6a70* h = this->find_in_history(ev);
                            if (h != 0)
                                this->remove_event(h->m48);
                            r = true;
                        }
                    }
                }
            }
        }
    }
    return r;
}

// @ 0x00dd6ec0
void cSPUIEventLog_s00dd_6a70::add_to_history(cFeedbackEvent_s00dd_6a70* ev)
{
    cFeedbackEvent_s00dd_6a70* h = this->find_in_history(ev);
    if (h != 0)
        this->remove_event(h->m48);
    this->mHistorySize++;
    ev->mInHistory = true;
    ev->mB6 = false;
    ev->mPaused = false;
    ev->mB10 = true;
    ev->mDuration = -1.0f;
    ev->m1c = (int)(DAT_016a0a0c * 255.0f);
    this->update_event_ui_state(ev);
    this->FUN_00dd6570(ev, 0);
}

