// Slice s00dd5a30 -- SP::cSPUIEventLog event/feedback UI helpers (retail 0x00dd5a30..0x00dd6a60).
// UI module: /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc (scalar SSE floats).
#include "types.h"

#pragma pack(push, 4)

// ------------------------------------------------------------------ basic interfaces
struct Object {
    virtual int AddRef();          // +0x00 slot 0
    virtual int Release();         // +0x04 slot 1
    virtual ~Object() {}           // +0x08 slot 2
};

struct IUnknown32 : Object {
    virtual void* QueryInterface(uint32_t id);   // +0x0c slot 3
};

// Result of mpUserData->QueryInterface(0x1186577): a flag byte at +0x75.
struct IRigHost : Object {
    virtual void* QueryInterface(uint32_t id);
    char pad0c[0x75 - 0x0c];
    uint8_t mByte75;   // +0x75
};

// UTFWin::IWindow slot map (indexes from the retail vtable, as used by this module).
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
    virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48();
    virtual void s4c(); virtual void s50(); virtual void s54(); virtual void s58();
    virtual void s5c(); virtual void s60(); virtual void s64(); virtual void s68();
    virtual void SetArea(float x, float y, float w, float h);  // +0x6c
    virtual void s70();                              // +0x70
    virtual void SetSize(float w, float h);          // +0x74
    virtual void s78();                              // +0x78
    virtual void SetFlag(int flag, bool value);      // +0x7c
    virtual void SetPosition(float x, float y);      // +0x80
    virtual void s84(); virtual void s88(); virtual void s8c();
    virtual void Invalidate();                       // +0x90
    virtual void s94(); virtual void s98(); virtual void s9c();
    virtual void sa0(); virtual void sa4();
    virtual void* GetDrawable();                     // +0xa8
    virtual void SetShadeColor(uint32_t color);      // +0xac
    virtual void sb0(); virtual void sb4(); virtual void sb8(); virtual void sbc();
    virtual void sc0(); virtual void sc4(); virtual void sc8();
    virtual void* ChildrenBegin(void* it);           // +0xcc
    virtual void* ChildrenNext(void* it);            // +0xd0
    virtual void sd4(); virtual void sd8(); virtual void sdc();
    virtual void se0(); virtual void se4(); virtual void se8(); virtual void sec();
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

class cSPUILayout {
 public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);        // 0x008105b0
};

// Animation objects created by the SPUI helpers (two vtables + a ref-counted target).
struct AnimBase0 { virtual void a0(); uint32_t field4; };
struct AnimBase1 { virtual void a1(); };
struct Anim : AnimBase0, AnimBase1 {
    Object* mpTarget;                                            // +0x0c
    void* mpAux;                                                 // +0x10
    virtual void a0();
    virtual void a1();
    ~Anim() { if (mpTarget) mpTarget->Release(); }
};
// Out-buffer of SPUICreateWindowAnimationTargetShadeAlphaW / AddAnimation: 0x88 bytes.
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

// Animation target helpers.
AnimRaw* SPUICreateWindowAnimationTargetShadeAlphaW(AnimRaw* out, IWindow* window, int alpha,
                                                    float start, float duration, int interp,
                                                    void* owner, uint32_t id);        // 0x007f8290
void* SPUICreateWindowAnimationTargetSize(AnimRaw* out, void* window, float* pos, float* size,
                                          void* owner, uint32_t id);                 // 0x007f73e0
void* FUN_007f9340(AnimRaw* out, void** pOut);                                         // 0x007f9340
void FUN_007f60d0(void* out, float a, float b, float c, float d, int e);              // 0x007f60d0
void* FUN_007f8fd0(void* anim, void* owner, uint32_t id);                             // 0x007f8fd0

class cSPUIAnimator {
 public:
    void* Append(void* anim, void* owner, uint32_t id);          // 0x007f8fd0
    void AddAnimation(void* anim, void* owner, uint32_t id);     // 0x007f8d10
};

namespace SPUIHelpers {
float GetElapsedSeconds();                                       // 0x00805080
void AnchorWindowToWindow(IWindow* a, IWindow* b, int c, int d); // 0x00807340
void* GetImageFromLayout(uint32_t id, int a);                    // 0x008061c0
}

struct Drawable : Object {
    virtual void d08();
    virtual void* QueryInterface(uint32_t id);                   // slot 3, +0x0c
    void SetImageIcon(int a, void* image);                       // 0x00831760 (non-virtual)
};

// Tuning globals of the event-log module.
extern uint32_t g_016a0958;      // next instance id
extern uint32_t g_016a095c;      // iconic-mode image layout id
extern float g_016a0960;         // default position x
extern float g_016a0964;         // default position y
extern float g_016a0968;         // default position z
extern float g_016a09ac;         // animation duration
extern float g_016a0a5c;         // iconic-mode lead time
extern float g_016a0adc;         // iconic-mode threshold
extern float g_016a0afc;         // fade-in delay
extern float g_01471064;
extern float g_0143c70;          // 10.0f (time to live)
extern float g_013eb1bc;         // -1.0f
extern float g_013eb8b0;         // sign mask
extern float g_01486110;         // +5.0 area padding
extern float g_01485720;         // 1.0f
extern float g_01477fbc;         // 100.0f
extern wchar_t g_01667bac[];     // eastl empty string storage
extern const char g_015d9c70;
extern float g_01440aec;         // 0 (offset applied to children)

bool CompareEventStrings(const void* a, const void* b);           // 0x0087d9a0
void Pollinator(void* child, float* rect);                       // 0x00806d10
void FUN_00f473a0_dummy();                                       // allocation (ctor tail)
cSPUILayout* create_event_layout();                              // 0x00dd5990

// ------------------------------------------------------------------ cFeedbackEvent (retail layout)
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
    cSPUILayout* mpItemLayout;    // +0x78
    uint32_t mBackGroundId;       // +0x7c
    uint32_t m80; uint32_t m84;
    float mIconPosX; uint32_t m8c;
    float m90;                    // +0x90

    cFeedbackEvent();
    virtual ~cFeedbackEvent() {}

    bool test(int n) const { return ((mFlags >> n) & 1) != 0; }
    void set(int n) { mFlags |= 1u << n; }
};

// ------------------------------------------------------------------ event map (eastl::map<uint32_t, AutoRefCount<cFeedbackEvent>>)
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

// ------------------------------------------------------------------ cSPUIEventLog
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
    cSPUIAnimator* mpAnimator;    // +0x68
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

// Cached-byte property observer (0xdd5e30).
struct Property {
    uint32_t pad00[4];
    uint16_t mnFlags;    // +0x10
    uint16_t mnType;     // +0x12
};

struct IPropertyHost {
    virtual int AddRef(); virtual int Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(void* context, void** out);   // slot 9, +0x24
};

struct BytePropertyCache {
    void* mOwner;        // +0x00
    void* mContext;      // +0x04
    uint32_t mPad8;      // +0x08
    char mCached;        // +0x0c
    bool Update(void* property);   // 0x00dd5e30
};

// ------------------------------------------------------------------ implementations
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

// @ 0x00dd60c0
void cSPUIEventLog::update_event_ui_state(cFeedbackEvent* ev)
{
    IWindow* win = ev->mpItemLayout->FindWindowByID(0x47d4388, 1);
    if (!win)
        return;
    IWindow* ctl = (IWindow*)win->QueryInterface(0xf15f4bd);
    if (!ctl)
        return;
    if (((ev->mEventString.mpEnd - ev->mEventString.mpBegin) >> 1) == 0)
        return;
    IWindow* item = ev->mpItemLayout->FindWindowByID(0x35ee914, 1);

    bool flag;
    if (ev->m60 != 0 ||
        ev->mPosition[0] != g_016a0960 ||
        ev->mPosition[1] != g_016a0964 ||
        ev->mPosition[2] != g_016a0968) {
        flag = true;
    } else if (ev->mpUserData) {
        IRigHost* q = (IRigHost*)ev->mpUserData->QueryInterface(0x1186577);
        flag = (q && q->mByte75 != 0);
    } else {
        flag = false;
    }
    (void)flag;

    IWindow* owner = ctl->GetOwner();
    owner->SetPosition(mLogPosition[0], 0.0f);
    IWindow* inner = owner->GetOwner();
    const float* r = inner->GetRealArea();
    float area[4] = { r[0], r[1], r[2], r[3] };
    if ((ev->mFlags >> 3) & 1) {
        ctl->SetShadeColor(0);
        inner->SetSize(area[2] - area[0], area[3] - area[1]);
    }
    ev->mBackGroundId = 0x3fffadc;
    if (ev->mFlags & 1) {
        ctl->s18();
        const float* ir = inner->GetRealArea();
        float size[4] = { 0.0f, 0.0f, (ir[2] - ir[0]) + g_01486110, ir[3] - ir[1] };
        inner->SetArea(size[0], size[1], size[2], size[3]);
        const float* ir2 = inner->GetRealArea();
        float w = ir2[2] - ir2[0];
        float h = ir2[3] - ir2[1];
        inner->GetOwner()->SetSize(w, h);
        ev->m90 = w;
    }
    IWindow* target = inner->GetOwner();
    IWindow* hit = target->FindWindowByID(0x3fffadc, 1);
    bool isTarget = (ev->mBackGroundId == 0x3fffadc);
    hit->SetFlag(1, isTarget);
    target->GetRealArea();
    IWindow* iconWnd = hit->FindWindowByID(0x35f06c8, 1);
    iconWnd->SetShadeColor(0xffffff);
    IWindow* anchor = ev->mpItemLayout->FindWindowByID(0x40005d8, 1);
    anchor->SetShadeColor(0xffffff);
    SPUIHelpers::AnchorWindowToWindow(iconWnd, anchor, 0x300, 0);
    IWindow* root = ev->mpItemLayout->FindWindowByID(0x35f06c8, 1);
    root->SetShadeColor(0xffffff);
    void* it;
    root->ChildrenBegin(&it);
    for (IWindow* ch = (IWindow*)root->ChildrenNext(&it); ch;
         ch = (IWindow*)root->ChildrenNext(&it)) {
        void* draw = ch->GetDrawable();
        int id = ch->GetControlID();
        bool want;
        if (draw) {
            want = (ev->m60b == 1) && (id - 0x3ffb8f0 == (int)ev->mCategory);
        } else {
            want = (ev->m60b != 0) ? false : (id - 0x3fe9970 == (int)ev->mCategory);
        }
        ch->SetFlag(1, want);
        if (ev->mCategory == 6 && ch->IsFlagSet() && g_016a095c) {
            void* img = SPUIHelpers::GetImageFromLayout(g_016a095c, ev->mScaleIndex);
            if (img)
                ((Drawable*)img)->AddRef();
            void* d = ch->GetDrawable();
            if (d)
                d = ((Drawable*)d)->QueryInterface(0x53eb526);
            if (img) {
                if (d)
                    ((Drawable*)d)->SetImageIcon(0, img);
                ((Drawable*)img)->Release();
            }
        }
        if ((ev->mFlags >> 3) & 1) {
            ch->AddWinProc(it);
            ev->mFlags &= ~8u;
        }
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
