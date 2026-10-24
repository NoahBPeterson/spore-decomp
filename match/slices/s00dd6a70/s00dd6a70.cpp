// Slice s00dd6a70 -- SP::cSPUIEventLog (SporeApp.exe 0x00dd6a70..0x00dd7928).
// Every function here is a __thiscall member of the SPUI event-log object.
//
// Frozen batch gold6.  32-bit x86, MSVC 2008 SP1, flags
// /O2 /MD /Gy /TP /arch:SSE /GS- (no /EHsc).

#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

// ---------------------------------------------------------------------------
// eastl::rbtree<unsigned, AutoRefCount<cFeedbackEvent>>
// ---------------------------------------------------------------------------
struct EventNodeBase {
    EventNodeBase* mpNodeLeft;    // +0x00
    EventNodeBase* mpNodeRight;   // +0x04
    EventNodeBase* mpNodeParent;  // +0x08
    unsigned       mColor;        // +0x0c
};

struct EventNode : EventNodeBase {
    unsigned mKey;                // +0x10
    void*    mValue;              // +0x14  AutoRefCount<cFeedbackEvent>::mpObject
};

struct EventIter {                // non-POD, returned through a hidden pointer
    EventNode* mpNode;
    EventIter() {}
};

struct EventTree {
    unsigned      mPad00;         // +0x00
    EventNodeBase mAnchor;        // +0x04  (left +0x04, right +0x08, parent +0x0c)
    unsigned      mnSize;         // +0x14
    // 0x00e5c780  __thiscall find(const unsigned& k) -> EventIter (hidden ret)
    EventIter find(const unsigned& k);
};

// ---------------------------------------------------------------------------
// cSPUIWindow / cSPUILayout / animator
// ---------------------------------------------------------------------------
struct IWindow {                          // a cSPUIWindow
    PV2 PV
    virtual void*    Slot0C(unsigned id);         // +0x0c
    PV2 PV
    virtual unsigned Slot1C();                    // +0x1c  window id
    PV8 PV4 PV2 PV
    virtual void     Slot5C(unsigned alpha);      // +0x5c
    PV4 PV2 PV
    virtual void     Slot7C(int a, int b);        // +0x7c
    PV8 PV8 PV8 PV4
    virtual IWindow* SlotF0(unsigned a, int b);   // +0xf0
};

struct cSPUILayout {
    IWindow* FindWindowByID(unsigned id, int flag);  // 0x008105b0
    void     SetVisibility(int v);                   // 0x00810590
    void     Shutdown(unsigned);                     // 0x00811ad0
    bool     Init(void* key, int a, int b);          // 0x008120d0
};

struct cSPUIAnimator {
    void RemoveAnimation(void* p, int z);            // 0x007f6210
};

// ---------------------------------------------------------------------------
// cFeedbackEvent
// ---------------------------------------------------------------------------
struct EventString {                  // eastl::basic_string<wchar_t>
    wchar_t* mpBegin;                 // +0x00
    wchar_t* mpEnd;                   // +0x04
    wchar_t* mpCap;                   // +0x08
    void append(const wchar_t* s);    // 0x005c3d90
};

struct cFeedbackEvent {
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
    cSPUILayout* mpLayout;            // +0x78
};

struct IRefCount {                    // AutoRefCount<...>::mpObject points here
    virtual void AddRef();            // slot 0
    virtual void Release();           // slot 1
};

float SPUIHelpers_GetElapsedSeconds();   // 0x00805080

EventNodeBase* eastl_RBTreeIncrement(EventNodeBase*);          // 0x00921580
void           eastl_RBTreeErase(EventNodeBase*, EventNodeBase*);  // 0x00921880

extern cSPUILayout* DAT_016a095c;        // global award-icon layout
extern float        DAT_016a0a0c;        // float global

// ---------------------------------------------------------------------------
// The event-log object.
// ---------------------------------------------------------------------------
struct cSPUIEventLog {
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
    cSPUIAnimator* mpAnimator;            // +0x68
    void*          mTuningProps;          // +0x6c

    void update_event_ui_state(cFeedbackEvent* ev);       // 0x00dd60c0
    cFeedbackEvent* find_in_history(cFeedbackEvent* ev);  // 0x00dd5dd0
    void FUN_00dd6570(cFeedbackEvent* ev, int z);         // 0x00dd6570

    bool RestartTimer(unsigned id);                   // 0x00dd6a70
    void SetEventDuration(unsigned id, float dur);    // 0x00dd6ac0
    int  RegisterCallback(unsigned id);               // 0x00dd6b20
    bool RegisterCloseCallback(unsigned id, int cb);  // 0x00dd6b70
    void remove_event(unsigned id);                   // 0x00dd6bc0
    void RemoveEvent(unsigned id, char immediate);    // 0x00dd6d10
    void clear_events();                              // 0x00dd6d70
    bool ModifyEventText(unsigned id, const wchar_t* text);  // 0x00dd6df0
    void add_to_history(cFeedbackEvent* ev);          // 0x00dd6ec0
};

// 0x00dd6a70 -- if the event exists and is live, stamp its restart time.
// @ 0x00dd6a70
bool cSPUIEventLog::RestartTimer(unsigned id)
{
    unsigned key = id;
    EventNode* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode*)&this->mEvents.mAnchor) {
        cFeedbackEvent* ev = (cFeedbackEvent*)it->mValue;
        if (ev != 0) {
            ev->mRestartTime = SPUIHelpers_GetElapsedSeconds();
            return true;
        }
    }
    return false;
}

// 0x00dd6ac0 -- set the duration; a negative duration with the paused bit clear
// marks the event paused and refreshes its UI.
// @ 0x00dd6ac0
void cSPUIEventLog::SetEventDuration(unsigned id, float dur)
{
    unsigned key = id;
    EventNode* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode*)&this->mEvents.mAnchor) {
        cFeedbackEvent* ev = (cFeedbackEvent*)it->mValue;
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

// 0x00dd6b20 -- true when the event exists, is live and is not already in the
// history list.
// @ 0x00dd6b20
int cSPUIEventLog::RegisterCallback(unsigned id)
{
    unsigned key = id;
    EventNode* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode*)&this->mEvents.mAnchor) {
        cFeedbackEvent* ev = (cFeedbackEvent*)it->mValue;
        if (ev != 0) {
            bool inHistory = (ev->mFlags >> 9) & 1;
            if (!inHistory)
                return 1;
        }
    }
    return 0;
}

// 0x00dd6b70 -- store the close callback and refresh the event UI.
// @ 0x00dd6b70
bool cSPUIEventLog::RegisterCloseCallback(unsigned id, int cb)
{
    unsigned key = id;
    EventNode* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode*)&this->mEvents.mAnchor) {
        cFeedbackEvent* ev = (cFeedbackEvent*)it->mValue;
        if (ev != 0) {
            ev->mCloseCallback = cb;
            this->update_event_ui_state(ev);
            return true;
        }
    }
    return false;
}

// @ 0x00dd6bc0
void cSPUIEventLog::remove_event(unsigned id)
{
    unsigned key = id;
    EventNode* node = this->mEvents.find(key).mpNode;
    if (node == (EventNode*)&this->mEvents.mAnchor)
        return;
    cFeedbackEvent* ev = (cFeedbackEvent*)node->mValue;
    if ((ev->mFlags >> 9) & 1)
        this->mHistorySize--;
    if (this->mpAnimator != 0)
        this->mpAnimator->RemoveAnimation(ev, -1);
    if (ev->mCallback != 0)
        ev->mCallback(ev->m48, ev->m5c);

    cSPUILayout* layout = ev->mpLayout;
    IWindow* wins[4];
    wins[0] = layout->FindWindowByID(0x2b7a911, 1);
    wins[1] = layout->FindWindowByID(0x47d4388, 1);
    wins[2] = layout->FindWindowByID(0x4000548, 1);
    wins[3] = 0;
    IWindow* w = layout->FindWindowByID(0x35ee914, 1);
    for (int i = 0; i < 4 && w != 0; ++i) {
        w->Slot7C(1, 1);
        unsigned wid = w->Slot1C();
        w->Slot5C(wid == 0x4000548 ? 0xffffffffu : 0x00ffffffu);
        this->mpAnimator->RemoveAnimation(w, -1);
        w = wins[i];
    }

    this->mEvents.mnSize--;
    EventNode* next = (EventNode*)eastl_RBTreeIncrement(node);
    eastl_RBTreeErase(next, &this->mEvents.mAnchor);
    if (next->mValue != 0)
        ((IRefCount*)next->mValue)->Release();
    operator delete[](next);
}

// 0x00dd6d10 -- remove an event; when `immediate` is clear it is unregistered
// straight away, otherwise it is only flagged for removal (duration -> 0).
// @ 0x00dd6d10
void cSPUIEventLog::RemoveEvent(unsigned id, char immediate)
{
    if (immediate == 0) {
        this->remove_event(id);
        return;
    }
    unsigned key = id;
    EventNode* it = this->mEvents.find(key).mpNode;
    if (it != (EventNode*)&this->mEvents.mAnchor) {
        cFeedbackEvent* ev = (cFeedbackEvent*)it->mValue;
        if (ev != 0) {
            ev->mB2 = false;
            ev->mDuration = 0.0f;
        }
    }
}

// 0x00dd6d70 -- drop every event from the log.
// @ 0x00dd6d70
void cSPUIEventLog::clear_events()
{
    while (this->mEvents.mnSize != 0)
        this->remove_event(((EventNode*)this->mEvents.mAnchor.mpNodeRight)->mKey);
}

// 0x00dd6df0 -- replace an event's text (only when the target UI window exists)
// and, if it is in the history list, unregister it.
// @ 0x00dd6df0
bool cSPUIEventLog::ModifyEventText(unsigned id, const wchar_t* text)
{
    bool r = false;
    if (text != 0) {
        unsigned key = id;
        EventNode* it = this->mEvents.find(key).mpNode;
        if (it != (EventNode*)&this->mEvents.mAnchor) {
            cFeedbackEvent* ev = (cFeedbackEvent*)it->mValue;
            if (ev != 0) {
                IWindow* w = ev->mpLayout->FindWindowByID(0x35ee914, 1);
                if (w != 0) {
                    IWindow* w2 = w->SlotF0(0x47d4388, 1);
                    if (w2 != 0) {
                        void* w3 = w2->Slot0C(0xf15f4bd);
                        if (w3 != 0 && (ev->mText.mpEnd != ev->mText.mpBegin)) {
                            ev->mText.append(text);
                            ev->mB6 = false;
                            ev->mTextDirty = true;
                            this->update_event_ui_state(ev);
                            cFeedbackEvent* h = this->find_in_history(ev);
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

// 0x00dd6ec0 -- PDB candidate SP::cSPUIEventLog::add_to_history.
// @ 0x00dd6ec0
void cSPUIEventLog::add_to_history(cFeedbackEvent* ev)
{
    cFeedbackEvent* h = this->find_in_history(ev);
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