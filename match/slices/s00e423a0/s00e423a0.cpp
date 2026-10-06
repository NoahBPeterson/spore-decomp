// Slice s00e423a0: timeline/event-strip UI panel update (retail 0x00e423a0, thiscall, ret 4).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast. The original frame is 16-byte aligned (and esp,-16).
// IWindow slots follow the Spore ModAPI UTFWin::IWindow header.
#include "types.h"
#include <intrin.h>

// ------------------------------------------------------------------ helpers
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

inline float Saturate(float v)
{
    float one = 1.0f;
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, v
        minss xmm0, one
        movss v, xmm0
    }
    return v;
}

template <class T> inline const T& Min(const T& a, const T& b) { return (b < a) ? b : a; }
template <class T> inline const T& Max(const T& a, const T& b) { return (a < b) ? b : a; }

struct Point {
    float x, y;
    Point() {}
    Point(float a, float b) : x(a), y(b) {}
};
struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
};
inline float Width(const Rect& r) { return r.x2 - r.x1; }
struct ColorRGB { float r, g, b; };
struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA() {}
    ColorRGBA(const ColorRGB& c, float alpha) : r(c.r), g(c.g), b(c.b), a(alpha) {}
    ColorRGBA(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
};
uint32_t ColorRGBAToU32(const ColorRGBA& c);    // SP::ColorRGBAToU32 0x004580c0

struct Object {
    virtual int AddRef();
    virtual int Release();
};

struct IWindow : Object {
    virtual void v08(); virtual void v0c(); virtual void v10(); virtual void v14();
    virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual uint32_t GetFlags();                         // +0x28
    virtual void v2c(); virtual void v30(); virtual void v34();
    virtual const Rect& GetRealArea();                   // +0x38
    virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48();
    virtual void v4c(); virtual void v50(); virtual void v54(); virtual void v58();
    virtual void SetShadeColor(uint32_t c);              // +0x5c
    virtual void v60(); virtual void v64(); virtual void v68();
    virtual void SetLayoutArea(const Rect& r);           // +0x6c
    virtual void v70(); virtual void v74(); virtual void v78();
    virtual void SetFlag(uint32_t flag, bool value);     // +0x7c
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual int Invalidate();                            // +0x90
    virtual void v94(); virtual void v98(); virtual void v9c(); virtual void va0();
    virtual void va4(); virtual void va8(); virtual void vac(); virtual void vb0();
    virtual void vb4(); virtual void vb8(); virtual void vbc();
    virtual Point ToGlobalCoordinates(Point p);          // +0xc0
    virtual Point ToLocalCoordinates(Point p);           // +0xc4
};

struct IWindowManager {
    virtual void v00();
    virtual IWindow* GetMainWindow();                    // +0x04
};
IWindowManager* WindowManager_0067caa0();

struct cSPUILayout {
    bool IsVisible_00810070();
    IWindow* FindWindowByID_008105b0(uint32_t id, bool recursive);
};

// Animation value returned by SPUICreateWindowAnimationTargetPosition (two vtables, ref-counted payload).
struct cSPUIAnimBase0 { virtual void f0(); uint32_t field_4; };
struct cSPUIAnimBase1 { virtual void f1(); };
struct __declspec(align(16)) cSPUIWindowAnimation : cSPUIAnimBase0, cSPUIAnimBase1 {
    Object* mpTarget;                                    // +0x0c
    virtual void f0();
    virtual void f1();
    ~cSPUIWindowAnimation() { if (mpTarget) mpTarget->Release(); }
};
cSPUIWindowAnimation SPUICreateWindowAnimationTargetPosition_007f80d0(IWindow* w, Point target, float seconds);
float GetElapsedSeconds_00805080(float base, int a, IWindow* w, int b);   // SPUIHelpers::GetElapsedSeconds
struct cSPUIAnimator {
    void AddAnimation_007f8d10(const cSPUIWindowAnimation& anim);
    void Update_007f63b0();
};

void GetWindowBounds_00805fe0(Rect* out, IWindow* w);

// EA::Stopwatch (only what the inlined Restart/GetElapsedTime need).
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* count);
struct Stopwatch {
    uint32_t mStartLo, mStartHi;     // +0x00
    uint32_t mTotalLo, mTotalHi;     // +0x08
    int      mCounterType;           // +0x10
    uint64_t GetElapsedTime_0093a5e0();
    void Restart()
    {
        uint32_t lo, hi;
        if (mCounterType == 1) {
            uint64_t t = __rdtsc();
            lo = (uint32_t)t;
            hi = (uint32_t)(t >> 32);
        } else {
            int64_t t;
            QueryPerformanceCounter(&t);
            lo = (uint32_t)t;
            hi = (uint32_t)((uint64_t)t >> 32);
        }
        mStartHi = hi;
        mStartLo = lo;
        mTotalLo = 0;
        mTotalHi = 0;
    }
};

struct cTimelineEntry {
    char pad0[0x1c];
    IWindow* mpIcon;                 // +0x1c
    IWindow* mpBoundsWindow;         // +0x20
    char pad24[0x6d - 0x24];
    bool  mbShown;                   // +0x6d
    char pad6e[0x70 - 0x6e];
    float mHeight;                   // +0x70
    float mWidth;                    // +0x74
    char pad78[0xf8 - 0x78];
    float mX;                        // +0xf8
    float mY;                        // +0xfc
    int  ActiveControllerIndex_0098f940();
    void Show_00e48dc0();
    void Hide_00e48bb0();
    void Update_00e46880(uint32_t dt);
};

struct cColorPicker {
    ColorRGB GetColor_00e461c0(int index);
    void SetSelected_00e46210(int index, int selected);
};

// eastl rbtree node: value pair at +0x10.
struct WindowPairNode { void* links[4]; IWindow* first; IWindow* second; };
WindowPairNode* RBTreeIncrement_00921580(WindowPairNode* n);

extern float    gColorAlpha_016acf1c;
extern int      gTimelineMaxTime_016acf2c;
extern float    gScrollMargin_016acf3c;
extern int      gShowDelayMs_016acf4c;
extern float    gAnimTime_016ace00;

struct cTimelinePanel {
    char pad0[0x2c];
    cSPUIAnimator* mpAnimator;       // +0x2c
    cSPUILayout*   mpLayout;         // +0x30
    char pad34[0x3c - 0x34];
    IWindow* mpClipWindow;           // +0x3c
    IWindow* mpScrollWindow;         // +0x40
    IWindow* mpMirrorWindow;         // +0x44
    char pad48[0x54 - 0x48];
    IWindow* mpInvalidateWindow;     // +0x54
    IWindow* mpSlider;               // +0x58
    IWindow* mpSliderHandle;         // +0x5c
    char pad60[4];
    IWindow* mpFirstVisible;         // +0x64
    IWindow* mpLastVisible;          // +0x68
    char pad6c[0x88 - 0x6c];
    float mMouseX;                   // +0x88
    char pad8c[4];
    Point mSliderMin;                // +0x90
    float mMaxScroll;                // +0x98
    char pad9c[4];
    Point mSliderMax;                // +0xa0
    char pada8[0xb0 - 0xa8];
    Stopwatch mHoverTimer;           // +0xb0
    char padc4[0x100 - 0xc4];
    char mWindowMapHeader[4];        // +0x100
    WindowPairNode mWindowMapAnchor; // +0x104
    char pad11c[0x170 - 0x11c];
    IWindow** mWindowsBegin;         // +0x170
    IWindow** mWindowsEnd;           // +0x174
    char pad178[0x184 - 0x178];
    cTimelineEntry** mEntriesBegin;  // +0x184
    cTimelineEntry** mEntriesEnd;    // +0x188
    char pad18c[0x1c8 - 0x18c];
    cColorPicker* mpColorPicker;     // +0x1c8
    char pad1cc[0x1e8 - 0x1cc];
    ColorRGBA mTargetColor[3][2];    // +0x1e8: {target, current} x 3 (0x1e8/0x1f8, 0x208/0x218, 0x228/0x238)
    bool  mbColorTracking;           // +0x248
    char pad249[0x270 - 0x249];
    float mScroll;                   // +0x270
    char pad274[4];
    float mScrollSmoothed;           // +0x278
    char pad27c[4];
    int   mTime;                     // +0x280
    int   mMode;                     // +0x284

    __forceinline bool DelayElapsed() { return mHoverTimer.GetElapsedTime_0093a5e0() > (uint64_t)(int64_t)gShowDelayMs_016acf4c; }
    void f_00e3b9e0(uint32_t dt);
    uint64_t f_00e36ff0(cTimelineEntry* e);
    void f_00e372b0(uint64_t v);
    void f_00e40250();
    void f_00e37be0();
    void Update(uint32_t dt);
};

inline void AssignRef(IWindow*& dst, IWindow* src)
{
    if (src != dst) {
        if (src) src->AddRef();
        IWindow* old = dst;
        dst = src;
        if (old) old->Release();
    }
}

// @ 0x00e423a0
void cTimelinePanel::Update(uint32_t dt)
{
    if (!mpLayout || !mpLayout->IsVisible_00810070())
        return;

    static float sScreenWidth = Width(WindowManager_0067caa0()->GetMainWindow()->GetRealArea());

    float progress = (float)mTime / (float)gTimelineMaxTime_016acf2c;
    f_00e3b9e0(dt);

    bool bShowed = false;
    bool bHid = false;
    bool bSliderVisible = mpSlider && (mpSlider->GetFlags() & 1);
    int count = (int)(mEntriesEnd - mEntriesBegin);
    cTimelineEntry* pending = 0;
    for (int i = 0; i < count; i++) {
        cTimelineEntry* e = mEntriesBegin[i];
        if (e->mpBoundsWindow) {
            Rect bounds;
            GetWindowBounds_00805fe0(&bounds, e->mpBoundsWindow);
            if (bSliderVisible && mMode != 3 && mMouseX >= bounds.x1 && bounds.x2 >= mMouseX &&
                e->ActiveControllerIndex_0098f940())
                f_00e372b0(f_00e36ff0(e));
        }
        if (e->mpIcon) {
            float left = e->mpIcon->ToGlobalCoordinates(Point(e->mX, e->mY)).x;
            float right = e->mpIcon->ToGlobalCoordinates(Point(e->mX + e->mWidth, e->mY + e->mHeight)).x;
            int what;   // 0: on screen, 1: off screen, 2: just outside the view
            if (progress >= 1.0f) {
                bool inView = right >= 0.0f && sScreenWidth > left;
                bool nearView = right >= -(gScrollMargin_016acf3c * sScreenWidth) &&
                                (gScrollMargin_016acf3c + 1.0f) * sScreenWidth > left;
                what = inView ? 0 : nearView ? 2 : 1;
            } else {
                what = (right >= 0.0f && sScreenWidth * progress > left) ? 0 : 1;
            }
            if (what == 0) {
                if (!e->mbShown && DelayElapsed() && !bShowed) {
                    e->Show_00e48dc0();
                    bShowed = true;
                }
            } else if (what == 1) {
                if (e->mbShown && DelayElapsed() && !bHid) {
                    e->Hide_00e48bb0();
                    bHid = true;
                }
            } else if (!e->mbShown) {
                pending = e;
            }
        }
        e->Update_00e46880(dt);
    }
    if (!bShowed) {
        if (pending && DelayElapsed()) {
            pending->Show_00e48dc0();
            pending->Update_00e46880(dt);
        } else if (!bHid) {
            goto skipRestart;
        }
    }
    mHoverTimer.Restart();
skipRestart:

    Rect clip = mpClipWindow ? mpClipWindow->GetRealArea() : Rect();
    Rect area = mpScrollWindow ? mpScrollWindow->GetRealArea() : Rect();

    if (mpSlider) {
        float overflow = (area.x2 - area.x1) - (clip.x2 - clip.x1);
        float limit = Min(mMaxScroll, overflow);
        float scroll = mScroll;
        Point pos;
        if (!(0.0f < scroll)) {
            pos.x = mSliderMin.x;
            pos.y = mSliderMin.y;
        } else if (scroll >= limit) {
            pos.x = mSliderMax.x;
            pos.y = mSliderMax.y;
        } else {
            float t = (limit == mSliderMin.x) ? 0.0f : (scroll - mSliderMin.x) / (limit - mSliderMin.x);
            t = Max(0.0f, t);
            pos.x = (mSliderMax.x - mSliderMin.x) * t + mSliderMin.x;
            pos.y = (mSliderMax.y - mSliderMin.y) * t + mSliderMin.y;
        }
        float seconds = GetElapsedSeconds_00805080(gAnimTime_016ace00, 0, mpSlider, 2);
        mpAnimator->AddAnimation_007f8d10(SPUICreateWindowAnimationTargetPosition_007f80d0(mpSlider, pos, seconds));
    }

    if (mpScrollWindow) {
        float t = Saturate((float)dt * 0.008f);
        if (0.0f > mScroll)
            mScroll = (-mScroll * t) * 3.0f + mScroll;
        float overflow = (area.x2 - area.x1) - (clip.x2 - clip.x1);
        if (mScroll > overflow)
            mScroll = ((overflow - mScroll) * t) * 3.0f + mScroll;
        mScrollSmoothed = (mScroll - mScrollSmoothed) * t + mScrollSmoothed;
        float d = -area.x1 - (float)RoundToInt(mScrollSmoothed);
        area.x1 = d + area.x1;
        area.x2 = area.x2 + d;
        mpScrollWindow->SetLayoutArea(area);
    }

    f_00e40250();
    f_00e37be0();
    if (mpInvalidateWindow)
        mpInvalidateWindow->Invalidate();

    if (mpMirrorWindow) {
        mpMirrorWindow->SetLayoutArea(mpScrollWindow->GetRealArea());
        for (WindowPairNode* n = (WindowPairNode*)mWindowMapAnchor.links[1]; n != &mWindowMapAnchor;
             n = RBTreeIncrement_00921580(n)) {
            IWindow* src = n->first;
            IWindow* dst = n->second;
            if (src && dst) {
                dst->SetLayoutArea(src->GetRealArea());
                dst->SetFlag(1, (src->GetFlags() & 1) != 0);
            }
        }

        if (IWindow* old = mpFirstVisible) { mpFirstVisible = 0; old->Release(); }
        if (IWindow* old = mpLastVisible) { mpLastVisible = 0; old->Release(); }
        IWindow* lastVisible = 0;
        for (IWindow** it = mWindowsBegin; it != mWindowsEnd; ++it) {
            IWindow* w = *it;
            if (w) {
                if (w->GetFlags() & 1) {
                    lastVisible = w;
                    if (!mpFirstVisible)
                        AssignRef(mpFirstVisible, w);
                } else if (!mpLastVisible) {
                    AssignRef(mpLastVisible, lastVisible);
                }
            }
        }
        if (!mpLastVisible)
            AssignRef(mpLastVisible, lastVisible);

        if (mpFirstVisible && mpLastVisible) {
            Rect r = mpFirstVisible->GetRealArea();
            r.x1 = r.x1 - sScreenWidth;
            mpFirstVisible->SetLayoutArea(r);
            r = mpLastVisible->GetRealArea();
            r.x2 = r.x2 + sScreenWidth;
            mpLastVisible->SetLayoutArea(r);
        }
    }

    IWindow* w0 = mpLayout->FindWindowByID_008105b0(0xf537d890, true);
    IWindow* w1 = mpLayout->FindWindowByID_008105b0(0xf537d891, true);
    IWindow* w2 = mpLayout->FindWindowByID_008105b0(0xf537d892, true);
    if (w0 && w1 && w2 && mpColorPicker) {
        mTargetColor[0][0] = ColorRGBA(mTargetColor[0][1].r, mTargetColor[0][1].g, mTargetColor[0][1].b, 0.0f);
        mTargetColor[1][0] = ColorRGBA(mTargetColor[1][1].r, mTargetColor[1][1].g, mTargetColor[1][1].b, 0.0f);
        mTargetColor[2][0] = ColorRGBA(mTargetColor[2][1].r, mTargetColor[2][1].g, mTargetColor[2][1].b, 0.0f);
        mpColorPicker->SetSelected_00e46210(0, 0);
        mpColorPicker->SetSelected_00e46210(1, 0);
        mpColorPicker->SetSelected_00e46210(2, 0);
        if ((mpSlider->GetFlags() & 1) && mbColorTracking) {
            Point g = mpSliderHandle->ToGlobalCoordinates(Point(0.0f, 0.0f));
            Point l = mpClipWindow->ToLocalCoordinates(g);
            const Rect& r = mpClipWindow->GetRealArea();
            float f = l.y / (r.y2 - r.y1);
            int index;
            if (0.333f > f) {
                mTargetColor[0][0] = ColorRGBA(mpColorPicker->GetColor_00e461c0(0), gColorAlpha_016acf1c);
                index = 0;
            } else if (0.666f > f) {
                mTargetColor[1][0] = ColorRGBA(mpColorPicker->GetColor_00e461c0(1), gColorAlpha_016acf1c);
                index = 1;
            } else {
                mTargetColor[2][0] = ColorRGBA(mpColorPicker->GetColor_00e461c0(2), gColorAlpha_016acf1c);
                index = 2;
            }
            mpColorPicker->SetSelected_00e46210(index, 1);
        }

        float t = Saturate((float)dt * 0.008f);
        for (int k = 0; k < 3; k++) {
            ColorRGBA& cur = mTargetColor[k][1];
            const ColorRGBA& tgt = mTargetColor[k][0];
            cur.r = (tgt.r - cur.r) * t + cur.r;
            cur.g = (tgt.g - cur.g) * t + cur.g;
            cur.b = (tgt.b - cur.b) * t + cur.b;
            cur.a = (tgt.a - cur.a) * t + cur.a;
        }
        w0->SetShadeColor(ColorRGBAToU32(mTargetColor[0][1]));
        w1->SetShadeColor(ColorRGBAToU32(mTargetColor[1][1]));
        w2->SetShadeColor(ColorRGBAToU32(mTargetColor[2][1]));
    }

    int time = mTime + (int)dt;
    if (time < 0)
        time = 0;
    else if (time > gTimelineMaxTime_016acf2c)
        time = gTimelineMaxTime_016acf2c;
    mTime = time;
    mpAnimator->Update_007f63b0();
}
