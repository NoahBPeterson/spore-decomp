// slice s004582b0 -- SP::cSPEditorBudget::Update and small editor/ui helpers.
// /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast module.
#include "types.h"

struct Float3 { float x, y, z; };
struct Float4 { float x, y, z, w; };

// @ 0x00458a40 -- RGB -> U32 with opaque alpha
unsigned int ColorRGBToU32(const float* c) {
    float r = c[0] > 0.0f ? c[0] : 0.0f;
    r = r * 255.0f;
    if (r > 255.0f) r = 255.0f;
    float g = c[1] > 0.0f ? c[1] : 0.0f;
    g = g * 255.0f;
    if (g > 255.0f) g = 255.0f;
    float b = c[2] > 0.0f ? c[2] : 0.0f;
    b = b * 255.0f;
    if (b > 255.0f) b = 255.0f;
    unsigned char ri = (unsigned char)(int)r;
    unsigned char gi = (unsigned char)(int)g;
    unsigned char bi = (unsigned char)(int)b;
    return ((unsigned int)ri << 0x10) | ((unsigned int)gi << 8) | (unsigned int)bi | 0xff000000u;
}

struct cSPUITooltipWinProc {
    void SetText(void* text, int a, int b);   // 0x00835ed0
};

struct Budget2 {
    char pad0[0x40];
    cSPUITooltipWinProc* mTooltip;   // +0x40

    void SetTooltip(void* p);        // 0x00458b50
    void* InitLayoutWidget();       // 0x00458c00
};

// @ 0x00458b50
void Budget2::SetTooltip(void* p) {
    if (p != 0) {
        cSPUITooltipWinProc* t = mTooltip;
        t->SetText(p, -1, 1);
    }
}

extern void* g_layout;   // 0x015d2dbc

// @ 0x00458c00
extern void FUN_00422c80(void* out);
void* Budget2::InitLayoutWidget() {
    int* p = (int*)((char*)this + 0x14);
    char local[4];
    FUN_00422c80(local);
    ((int*)this)[1] = (int)p;
    ((int*)this)[0] = ((int*)this)[1];
    ((int*)this)[2] = ((int*)this)[0] + 0x20;
    *(unsigned short*)((int*)((int*)this)[0]) = 0;
    return this;
}

// @ 0x00458d80
extern void FUN_00811ad0(void* layout, int one);
void FUN_00458d80() {
    if (g_layout != 0) {
        FUN_00811ad0(g_layout, 1);
        if (g_layout != 0) {
            void* old = g_layout;
            g_layout = 0;
            if (old != 0)
                ((void(__thiscall*)(void*))(*(void***)old)[2])(old);
        }
    }
}

// @ 0x00458de0
extern void SPUIHelpers_GetImageFromLayout(void* layout, unsigned int param);
void FUN_00458de0(unsigned int param) {
    void* p = g_layout;
    SPUIHelpers_GetImageFromLayout(p, param);
}

// @ 0x00458e00
int FUN_00458e00(int id) {
    int r = 0x157aa4e5;
    switch (id) {
        case 0x8f963dcb:
        case 0x441cd3e6:
        case 0x7d433fad:
            r = 0xfd503a02; break;
        case 0xf670aa43:
        case 0x1a4e0708:
        case 0x2a5147a9:
            r = 0x0f615124; break;
        case 0x1f2a25b6:
        case 0x9ad7d4aa:
        case 0x449c040f:
            r = 0x10c8a72e; break;
        default:
            break;
    }
    return r;
}

// @ 0x00458eb0
int FUN_00458eb0(int id) {
    int r = 0x11b78a72;
    switch (id) {
        case 0x8f963dcb:
        case 0x441cd3e6:
        case 0x7d433fad:
            r = 0x06329468; break;
        case 0xf670aa43:
        case 0x1a4e0708:
        case 0x2a5147a9:
            r = 0x0632946a; break;
        case 0x1f2a25b6:
        case 0x9ad7d4aa:
        case 0x449c040f:
            r = 0x06329469; break;
        default:
            break;
    }
    return r;
}

// ---------------------------------------------------------------------------
// (0x004582b0) cSPEditorBudget::Update(uint dt): animates the displayed wealth towards the actual
// wealth (count up/down, tinting green/red), lerps the colour, refreshes the five window captions
// and runs the blink/flash timer.
// ---------------------------------------------------------------------------
#include <xmmintrin.h>
struct V3 { float x, y, z; V3() {} V3(float ax, float ay, float az) { x = ax; y = ay; z = az; } };
// Out-of-line vector helpers of the original (0x0041db10 / 0x0041dca0 / 0x0041ddb0), plain cdecl.
V3 operator-(const V3& a, const V3& b);                       // 0x0041db10
V3 operator*(const V3& a, const float& s);                    // 0x0041dca0
V3& Vector3_Add(V3& a, const V3& b);                          // 0x0041ddb0
unsigned int ColorRGBAToU32(const float* c);                  // 0x004580c0
void SetMoneyString(double v, wchar_t* buf, int size, const wchar_t* fmt, const wchar_t* sym); // 0x008822e0
extern int g_period;                                           // 0x0150c498
extern V3 g_white;                                             // 0x015d2998

struct IWin {
    virtual void s00();
    virtual void s01();
    virtual void s02();
    virtual void s03();
    virtual void s04();
    virtual void s05();
    virtual void s06();
    virtual void s07();
    virtual void s08();
    virtual void s09();
    virtual void s0a();
    virtual void s0b();
    virtual void s0c();
    virtual void s0d();
    virtual void s0e();
    virtual void s0f();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void SetFillColor(unsigned int c);   // +0x5c
    virtual void s18();
    virtual void s19();
    virtual void s1a();
    virtual void s1b();
    virtual void s1c();
    virtual void s1d();
    virtual void s1e();
    virtual void s1f();
    virtual void SetCaption(const wchar_t* text); // +0x80
};

struct WinRef {                                   // AutoRefCount<IWindow>
    IWin* mp;
    operator IWin*() const { return mp; }
    IWin* operator->() const { return mp; }
};
struct WinVec {
    WinRef* mpBegin;
    WinRef& operator[](int i) { return mpBegin[i]; }
};
struct IntVec {
    int* mpBegin;
    int& operator[](int i) { return mpBegin[i]; }
};

inline float MinF(float x, float hi)
{
    __asm {
        movss xmm0, x
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
inline float MaxF(float x, float lo)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        movss x, xmm0
    }
    return x;
}
inline float Sat(float x, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}
template <class T> inline const T& MaxT(const T& a, const T& b) { return a < b ? b : a; }

struct Budget {
    char pad0[0x10];
    float mMoneyPerSecond;      // +0x10
    wchar_t mCurrencyChar;      // +0x14
    int mActualWealth;          // +0x18
    V3 mTargetColor;            // +0x1c
    V3 mActualColor;            // +0x28
    char pad1[0x44 - 0x34];
    WinVec mWindows;            // +0x44
    char pad2[0x58 - 0x48];
    IntVec mWealths;            // +0x58
    char pad3[0x6c - 0x5c];
    int mFlashTime;             // +0x6c
    bool mFlashing;             // +0x70
    bool mFlashActive;          // +0x71

    void Update(unsigned int dt);
};

// @ 0x004582b0
void Budget::Update(unsigned int dt) {
    for (int i = 4; i > 0; --i) {
        mWealths[i] = mWealths[i - 1];
    }
    if (mWealths[0] < mActualWealth) {
        int stepUp = MaxT((int)((float)dt / 1000.0f * mMoneyPerSecond), 1);
        mWealths[0] = (int)MinF((float)(mWealths[0] + stepUp), (float)mActualWealth);
        mTargetColor = V3(0.4f, 1.0f, 0.4f);
        mActualColor = mTargetColor;
    } else if (mWealths[0] > mActualWealth) {
        int stepDown = MaxT((int)((float)dt / 1000.0f * mMoneyPerSecond), 1);
        mWealths[0] = (int)MaxF((float)(mWealths[0] - stepDown), (float)mActualWealth);
        mTargetColor = V3(1.0f, 0.4f, 0.4f);
        mActualColor = mTargetColor;
    } else {
        mTargetColor = g_white;
    }
    float blend = Sat((float)dt * 0.0015f, 1.0f);
    Vector3_Add(mActualColor, (mTargetColor - mActualColor) * blend);
    mWindows[0]->SetFillColor(ColorRGBToU32(&mActualColor.x));
    for (int j = 0; j < 5; ++j) {
        if (mWindows[j]) {
            wchar_t cur[2];
            cur[0] = mCurrencyChar;
            cur[1] = 0;
            wchar_t text[40];
            SetMoneyString((double)mWealths[j], text, 40, L"%-F%-p", cur);
            mWindows[j]->SetCaption(text);
        }
    }
    if (mFlashing && !mFlashActive && mActualWealth == mWealths[0]) {
        mFlashTime = 0;
        mFlashActive = true;
    }
    if (mFlashActive) {
        float fade;
        if (mFlashTime < g_period / 2)
            fade = (float)(g_period / 2 - mFlashTime) / (float)(g_period / 2);
        else
            fade = (float)(mFlashTime - g_period / 2) / (float)(g_period / 2);
        float col[4];
        col[0] = g_white.x; col[1] = g_white.y; col[2] = g_white.z; col[3] = fade;
        mWindows[0]->SetFillColor(ColorRGBAToU32(col));
        mFlashTime += dt;
        if (mFlashTime > g_period) {
            if (!mFlashing || mActualWealth != mWealths[0]) {
                mWindows[0]->SetFillColor(ColorRGBToU32(&g_white.x));
                mFlashActive = false;
            } else {
                mFlashTime = mFlashTime % g_period;
            }
        }
    }
}

// @ 0x00458c60 -- PreloadLayout (only outlined)
char FUN_00458c60(unsigned int param) {
    (void)param;
    return 0;
}
