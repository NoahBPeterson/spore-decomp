// Slice s00dd7970 -- SP::cSPUIEventLog per-frame update of the feedback event log (retail 0x00dd7970,
// thiscall, ret 4).
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (UI module: SSE scalar floats, no /EHsc).
//
// The log keeps its events in a map<id, AutoRefCount<cFeedbackEvent>>. Each frame it sorts them into three
// fixed_vector<AutoRefCount<cFeedbackEvent>, 64> bins (permanent, normal, history), lays them out bottom-up
// from the log position (animating moves and alpha changes when the log is visible), queues expired or
// invalid events for removal, then runs the per-event timers (fade in/out, iconic mode, expiry) and finally
// removes the queued events.
#include "types.h"

inline void* operator new(size_t, void* p) { return p; }

#pragma pack(push, 4)

// ------------------------------------------------------------------ basic types
struct Point {
    float x, y;
    Point() {}
    Point(float a, float b) : x(a), y(b) {}
};
struct Rect {
    float x1, y1, x2, y2;
};

struct Object {
    virtual int AddRef();
    virtual int Release();
};

// UTFWin::IWindow (slots as in the Spore ModAPI header).
struct IWindow : Object {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual uint32_t GetFlags();                                 // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual const Rect& GetRealArea();                           // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void SetShadeColor(uint32_t color);                  // +0x5c
    virtual void v60();
    virtual void SetLocation(float x, float y);                  // +0x64
    virtual void v68(); virtual void v6c(); virtual void v70(); virtual void v74();
    virtual void v78(); virtual void v7c(); virtual void v80(); virtual void v84();
    virtual void v88(); virtual void v8c(); virtual void v90(); virtual void v94();
    virtual void v98(); virtual void v9c(); virtual void va0(); virtual void va4();
    virtual void va8(); virtual void vac(); virtual void vb0(); virtual void vb4();
    virtual void vb8(); virtual void vbc();
    virtual Point ToGlobalCoordinates(Point p);                  // +0xc0
    virtual void vc4(); virtual void vc8(); virtual void vcc(); virtual void vd0();
    virtual void vd4(); virtual void vd8(); virtual void vdc(); virtual void ve0();
    virtual void ve4(); virtual void ve8(); virtual void vec();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive); // +0xf0
};

enum { kWinFlagVisible = 1 };

struct cSPUILayout {
    IWindow* FindWindowByID(uint32_t id, bool recursive);       // 0x008105b0
};

// Animation value returned by the SPUICreateWindowAnimationTarget* helpers (two vtables, ref-counted
// target); only its destructor is inlined here.
struct cSPUIAnimBase0 { virtual void f0(); uint32_t field_4; };
struct cSPUIAnimBase1 { virtual void f1(); };
struct cSPUIWindowAnimation : cSPUIAnimBase0, cSPUIAnimBase1 {
    Object* mpTarget;                                            // +0x0c
    virtual void f0();
    virtual void f1();
    ~cSPUIWindowAnimation() { if (mpTarget) mpTarget->Release(); }
};
cSPUIWindowAnimation SPUICreateWindowAnimationTargetShadeAlpha(IWindow* window, uint32_t alpha, float startTime,
                                                              float duration, int interpolation);  // 0x007f8290
cSPUIWindowAnimation SPUICreateWindowAnimationTargetPosition(IWindow* window, Point target, float startTime,
                                                            float duration, int interpolation);    // 0x007f80d0
struct cSPUIAnimator {
    void AddAnimation(const cSPUIWindowAnimation& anim, Object* owner, uint32_t id);  // 0x007f8d10
};

namespace SPUIHelpers {
float GetElapsedSeconds();                                       // 0x00805080
}
bool FUN_00809970();                                             // event log enabled check
void* GetUniverseContext_01021080();                             // SP::cSPLivingUniverse::GetUniverseContext

// Tuning values (statics of the event log module).
extern float g_016a099c;     // vertical spacing between events
extern uint32_t g_016a0a6c;  // event alpha while the log is active
extern bool g_016a0a1c;      // animate layout changes
extern float g_016a09ac;     // animation duration
extern float g_016a0a3c;     // gap after the permanent events
extern float g_016a0a4c;     // gap after the normal events
extern float g_016a0a5c;     // iconic-mode lead time
extern float g_016a0aec;     // fade-out delay

// ------------------------------------------------------------------ cFeedbackEvent (retail layout)
struct cFeedbackEvent : Object {
    uint32_t pad04[2];
    uint32_t mFlags;                    // +0x0c eastl::bitset<12>
    uint32_t mCategory;                 // +0x10
    uint32_t pad14[6];
    float mTimeAnimStarted;             // +0x2c
    float mTimeCreated;                 // +0x30
    float mTimeToLive;                  // +0x34 (-1: until replaced)
    float mRemoveTime;                  // +0x38 (-1: never)
    uint32_t pad3c;
    bool mbUniverseBound;               // +0x40
    void* mpUniverseContext;            // +0x44
    uint32_t mInstanceID;               // +0x48
    uint32_t pad4c[11];
    cSPUILayout* mpItemLayout;          // +0x78
    uint32_t mBackGroundId;             // +0x7c
    Point mTargetBackPos;               // +0x80
    Point mTargetIconPos;               // +0x88

    bool test(int n) const { return ((mFlags >> n) & 1) != 0; }
    void set(int n) { mFlags |= 1u << n; }
};

enum {
    kfNew = 0, kfDoNotAddToHistory = 1, kfTextDirty = 2, kfFadingIn = 4, kfFadingOut = 5, kfExpired = 6,
    kfRemove = 7, kfInvalid = 8, kfHistory = 9, kfIconicMode = 10, kfPermanent = 11
};

// ------------------------------------------------------------------ EA::AutoRefCount
template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T& object) : mpObject(&object) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T& operator*() const { return *mpObject; }
};
typedef AutoRefCount<cFeedbackEvent> EventPtr;

// eastl::copy for AutoRefCount ranges (out of line in the original, shared through identical-code folding).
EventPtr* copy_006782c0(EventPtr* first, EventPtr* last, EventPtr* dest);

void operator_delete_array_00f47380(void* p);    // operator delete[]

// ------------------------------------------------------------------ eastl::fixed_vector<EventPtr, 64>
struct EventVector {
    EventPtr* mpBegin;
    EventPtr* mpEnd;
    EventPtr* mpCapacity;
    uint32_t mOverflowAllocator;
    void* mpPoolBegin;
    uint32_t mPad;
    uint32_t mBuffer[64];

    EventVector() {
        mpBegin = mpEnd = (EventPtr*)mBuffer;
        mpCapacity = (EventPtr*)mBuffer + 64;
        mpPoolBegin = mBuffer;
    }
    ~EventVector() {
        for (EventPtr* p = mpBegin; p < mpEnd; ++p)
            p->~EventPtr();
        if (mpBegin && mpBegin != mpPoolBegin)
            operator_delete_array_00f47380(mpBegin);
    }
    bool empty() const { return mpBegin == mpEnd; }
    EventPtr& back() { return mpEnd[-1]; }
    void DoInsertValue(EventPtr* position, const EventPtr& value);   // 0x00edafd0
    void push_back(const EventPtr& value) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) EventPtr(value);
        else
            DoInsertValue(mpEnd, value);
    }
    void pop_back() {
        --mpEnd;
        mpEnd->~EventPtr();
    }
    EventPtr* erase(EventPtr* first, EventPtr* last) {
        EventPtr* const position = copy_006782c0(last, mpEnd, first);
        for (EventPtr* p = position; p < mpEnd; ++p)
            p->~EventPtr();
        mpEnd -= (last - first);
        return first;
    }
    void clear() { erase(mpBegin, mpEnd); }
};

// ------------------------------------------------------------------ eastl::map<uint32_t, EventPtr>
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};
struct EventNode : rbtree_node_base {
    uint32_t mKey;          // +0x10
    EventPtr mValue;        // +0x14
};
rbtree_node_base* RBTreeIncrement_00921580(const rbtree_node_base* pNode);

struct EventMap {
    uint32_t mCompare;
    rbtree_node_base mAnchor;   // +0x04
    uint32_t mnSize;
    uint32_t mAllocator;

    EventNode* find(uint32_t key) {
        EventNode* pCurrent = (EventNode*)mAnchor.mpNodeParent;
        rbtree_node_base* pRangeEnd = &mAnchor;
        while (pCurrent) {
            if (!(pCurrent->mKey < key)) {
                pRangeEnd = pCurrent;
                pCurrent = (EventNode*)pCurrent->mpNodeLeft;
            } else
                pCurrent = (EventNode*)pCurrent->mpNodeRight;
        }
        if (pRangeEnd != &mAnchor && !(key < ((EventNode*)pRangeEnd)->mKey))
            return (EventNode*)pRangeEnd;
        return (EventNode*)&mAnchor;
    }
};

// ------------------------------------------------------------------ cSPUIEventLog
struct cSPUIEventLog {
    uint32_t pad00[8];
    uint32_t mGlobalAlpha;          // +0x20
    bool mbVisible;                 // +0x24
    EventMap mEvents;               // +0x28
    uint32_t mLastEventEntered;     // +0x44
    float mLastUpdateTime;          // +0x48
    Point mLogPosition;             // +0x4c
    Point mLogOffset;               // +0x54
    float mLogTop;                  // +0x5c
    float mLogTopCurrent;           // +0x60
    int mHistorySize;               // +0x64
    cSPUIAnimator* mpAnimator;      // +0x68

    void FUN_00dd5a30(cFeedbackEvent* ev, bool b);
    void FUN_00dd5bb0(cFeedbackEvent* ev, bool b);
    void update_event_ui_state(cFeedbackEvent* ev);     // 0x00dd60c0
    void FUN_00dd6570(cFeedbackEvent* ev, bool b);
    void remove_event(uint32_t instanceID);              // 0x00dd6bc0
    void FUN_00dd6ec0(cFeedbackEvent* ev);
    void Update(bool bForceLayout);
};

#pragma pack(pop)

// @ 0x00dd7970
void cSPUIEventLog::Update(bool bForceLayout)
{
    float spacing = g_016a099c;
    float now = SPUIHelpers::GetElapsedSeconds();
    mLastUpdateTime = now;

    uint32_t alpha;
    if (FUN_00809970())
        alpha = g_016a0a6c;
    else
        alpha = 0xff;
    bool bAnimate = g_016a0a1c && mbVisible;

    Point pos(mLogOffset.x + mLogPosition.x, mLogOffset.y + mLogPosition.y);
    Point top = pos;

    EventVector removeList;
    EventVector history;
    EventVector normal;
    EventVector permanent;

    for (rbtree_node_base* it = mEvents.mAnchor.mpNodeLeft; it != &mEvents.mAnchor; it = RBTreeIncrement_00921580(it)) {
        cFeedbackEvent* pEvent = ((EventNode*)it)->mValue.mpObject;
        if (pEvent->test(kfHistory)) {
            EventPtr ev(*pEvent);
            history.push_back(ev);
        } else if (pEvent->test(kfPermanent)) {
            EventPtr ev(*pEvent);
            permanent.push_back(ev);
        } else {
            EventPtr ev(*pEvent);
            normal.push_back(ev);
        }
    }

    // Layout, bottom-up: permanent events, then normal ones, then the history.
    EventVector* bins[4] = { &permanent, &normal, &history, 0 };
    for (EventVector** pBin = bins; *pBin; ++pBin) {
        EventVector* bin = *pBin;
        for (EventPtr* it = bin->mpEnd; it != bin->mpBegin; --it) {
            cFeedbackEvent* ev = it[-1].mpObject;
            IWindow* window = ev->mpItemLayout->FindWindowByID(0x035ee914, true);

            if (alpha != mGlobalAlpha && !ev->test(kfIconicMode)) {
                IWindow* shade = window->FindWindowByID(0x02b7a911, false);
                if (shade->GetFlags() & kWinFlagVisible) {
                    if (mbVisible) {
                        uint32_t id = ((uint32_t)shade << 8) ^ 0x02b7a911;
                        mpAnimator->AddAnimation(
                            SPUICreateWindowAnimationTargetShadeAlpha(shade, alpha, SPUIHelpers::GetElapsedSeconds(),
                                                                      g_016a09ac, 0),
                            ev, id);
                    } else {
                        shade->SetShadeColor((alpha << 24) + 0x00ffffff);
                    }
                }
            }

            if (ev->mRemoveTime != -1.0f && now > ev->mTimeCreated + ev->mRemoveTime)
                ev->set(kfRemove);
            if (ev->mbUniverseBound && ev->mpUniverseContext != GetUniverseContext_01021080())
                ev->set(kfRemove);

            if (!ev->test(kfInvalid) && !ev->test(kfRemove)) {
                if (ev->test(kfNew)) {
                    window->SetLocation(pos.x, pos.y);
                    FUN_00dd5bb0(ev, true);
                    FUN_00dd5a30(ev, false);
                }
                if (bForceLayout || ev->mTargetIconPos.x != top.x || ev->mTargetIconPos.y != top.y ||
                    ev->mTargetBackPos.x != pos.x || ev->mTargetBackPos.y != pos.y) {
                    if (!bAnimate) {
                        window->SetLocation(pos.x, pos.y);
                    } else {
                        uint32_t id = ((uint32_t)window << 8) ^ 0x035eef1c;
                        mpAnimator->AddAnimation(
                            SPUICreateWindowAnimationTargetPosition(window, Point(pos.x, pos.y),
                                                                    SPUIHelpers::GetElapsedSeconds(), g_016a09ac, 0),
                            ev, id);
                        ev->mTargetBackPos.x = pos.x;
                        ev->mTargetBackPos.y = pos.y;
                        ev->mTargetIconPos.x = top.x;
                        ev->mTargetIconPos.y = top.y;
                    }
                }

                // Measure the event at its target position, then put it back.
                const Rect& area = window->GetRealArea();
                Point oldLocation(area.x1, area.y1);
                window->SetLocation(pos.x, pos.y);
                IWindow* back = window->FindWindowByID(ev->mBackGroundId, true);
                Point backTop = back->ToGlobalCoordinates(Point(0.0f, 0.0f));
                pos.y = backTop.y - spacing;
                IWindow* text = ev->mpItemLayout->FindWindowByID(ev->mCategory + 0x03ffb8f0, true);
                if (!(text->GetFlags() & kWinFlagVisible))
                    ev->mpItemLayout->FindWindowByID(ev->mCategory + 0x03fe9970, true);
                text->GetRealArea();
                text->ToGlobalCoordinates(Point(0.0f, 0.0f));
                top.y = pos.y - spacing;
                window->SetLocation(oldLocation.x, oldLocation.y);
            } else {
                EventPtr ref(*ev);
                removeList.push_back(ref);
            }
        }

        if (!bin->empty()) {
            if (bin == &permanent && !permanent.empty()) {
                pos.y -= g_016a0a3c;
                top.y -= g_016a0a3c;
            } else if (bin == &normal && !normal.empty()) {
                pos.y -= g_016a0a4c;
                top.y -= g_016a0a4c;
            }
        }
    }

    mGlobalAlpha = alpha;
    mLogTopCurrent = top.y;

    // Timers.
    for (EventVector** pBin = bins; *pBin; ++pBin) {
        EventVector* bin = *pBin;
        for (EventPtr* it = bin->mpEnd; it != bin->mpBegin; --it) {
            cFeedbackEvent* ev = it[-1].mpObject;
            if (!ev->test(kfExpired)) {
                if (ev->test(kfNew) || ev->test(kfTextDirty)) {
                    ev->mFlags &= ~((1u << kfNew) | (1u << kfTextDirty));
                    update_event_ui_state(ev);
                }
                float timeToLive = ev->mTimeToLive;
                if (timeToLive != -1.0f) {
                    float endTime = ev->mTimeCreated + timeToLive;
                    if (now > endTime) {
                        ev->set(kfExpired);
                    } else if (!ev->test(kfIconicMode) && now > endTime + g_016a0a5c) {
                        ev->set(kfIconicMode);
                        update_event_ui_state(ev);
                        FUN_00dd6570(ev, false);
                    }
                } else if (ev->test(kfHistory)) {
                    if (!ev->test(kfIconicMode) && now > ev->mTimeCreated + timeToLive + g_016a0a5c) {
                        ev->set(kfIconicMode);
                        update_event_ui_state(ev);
                        FUN_00dd6570(ev, false);
                    }
                    IWindow* window = ev->mpItemLayout->FindWindowByID(0x035ee914, true);
                    if (mLogTop > window->ToGlobalCoordinates(Point(0.0f, 0.0f)).y) {
                        EventNode* node = mEvents.find(ev->mInstanceID);
                        if (node != (EventNode*)&mEvents.mAnchor) {
                            cFeedbackEvent* other = node->mValue.mpObject;
                            if (other) {
                                other->mFlags &= ~(1u << kfTextDirty);
                                other->mTimeToLive = 0.0f;
                            }
                        }
                    }
                }
            } else if (!ev->test(kfHistory) && !ev->test(kfDoNotAddToHistory)) {
                FUN_00dd6ec0(ev);
            } else {
                ev->set(kfRemove);
            }

            if (ev->mTimeAnimStarted > 0.0f && now > ev->mTimeAnimStarted + g_016a0aec)
                FUN_00dd5bb0(ev, false);
        }
    }

    while (!removeList.empty()) {
        remove_event(removeList.back()->mInstanceID);
        removeList.pop_back();
    }
    removeList.clear();
    history.clear();
    normal.clear();
    permanent.clear();
}
