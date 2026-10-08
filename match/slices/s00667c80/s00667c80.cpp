// Slice s00667c80: SP::cSPUIFeedListItem - DoMessage (feed-item messages), SetName,
// QueryNumItems (number/icon refresh) and Update (per-frame animation).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS- (Update, 0x668550, additionally needs /fp:fast for its x87 fabs/sin).
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void  (__thiscall *FnVoidII)(void*, int, int);
typedef void  (__thiscall *FnVoidIII)(void*, int, int, int);
typedef void  (__thiscall *FnVoidIPI)(void*, unsigned, void*, int);
typedef int   (__thiscall *FnIntV)(void*);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl SP_AssetBrowser();
void* __cdecl SP_WindowManager();                 // 0x0067caa0
void* __cdecl SP_MessageServer();                 // 0x0067dcc0
void* __cdecl FUN_0067cb30();                      // 0x0067cb30
void* __cdecl FUN_00666b20(void* out, void* a, unsigned key);
void  __cdecl FUN_00667ac0(void* self);
void  __cdecl FUN_00667ae0(void* self);
void  __cdecl FUN_00668070(void* self);
void  __cdecl FUN_00667b00(void* self);            // OnLeftMouseDown
void  __cdecl FUN_0066b00_dummy();
void  __cdecl WString_Assign(void* dest, const wchar_t* first, const wchar_t* last);
bool  __cdecl FUN_0087da10(const wchar_t* a, void* b);
bool  __cdecl FUN_00805150(void* a, void* b);
unsigned char __cdecl StartBanMode(int id);        // 0x008d2fb0
int   __cdecl GetRecorderState();                  // 0x00435e90
void  __cdecl KillSetiEffects(int state, unsigned id);
void* __cdecl FUN_0054ea20(void* self, int a, int b);
void* __cdecl FUN_0054eac0(void* self, int a);

struct cSPUILayout {
    virtual void s0(); virtual void s1(); virtual int Release();
    void Shutdown(bool);
    void* FindWindowByID(unsigned id, int flag);   // 0x008105b0
};
struct Sub54 { unsigned char FUN_0054eac0(int v); void FUN_0054ea20(int a, int b); };

struct Vec4 {
    float x, y, z, w;
    Vec4() {}
    Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
    Vec4(const Vec4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
};
inline Vec4 operator-(const Vec4& a, const Vec4& b) { return Vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
inline Vec4 operator+(const Vec4& a, const Vec4& b) { return Vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
inline Vec4 operator*(const Vec4& a, float k) { return Vec4(a.x * k, a.y * k, a.z * k, a.w * k); }

#pragma warning(disable: 4100)
extern "C" double __cdecl sin(double);
#pragma intrinsic(sin)
extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

// Window with an area setter (vtable slot 27).
struct AreaWin {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26();
    virtual void SetArea(const Vec4* area);          // slot 27 (+0x6c)
};
// Interface obtained by Cast(0xf15f4bd); slot 10 (+0x28) sets the colour.
struct ColorIface {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void SetColor(unsigned rgba);            // slot 10 (+0x28)
};
struct CastWin {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual ColorIface* Cast(unsigned id);           // slot 3 (+0xc)
};
// Image-like window; slot 23 (+0x5c) sets the colour.
struct ImageWin {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void SetColor(unsigned rgba);            // slot 23 (+0x5c)
};
struct TailObj { void Tick(); };                     // 0x008297b0 (thiscall)
struct AssetBrowserG { char pad[0x18]; void* mProps; };

AssetBrowserG* __cdecl SP_AssetBrowserG();           // 0x00401030
void  __cdecl GetWindowArea(Vec4* out, void* win);   // 0x00805ef0
float __cdecl GetWindowAlpha(void* win);             // 0x00805040
float __cdecl GetElapsedSeconds();                   // 0x00805080
void  __cdecl SetWindowRotation(void* win, const Vec4* q);   // 0x00808230
unsigned __cdecl ColorRGBAToU32(const Vec4* c);      // 0x004580c0
Vec4* __cdecl GetPropertyColor(Vec4* out, void* props, unsigned key, Vec4 def);   // 0x00666b20
float __cdecl GetPropertyFloat(void* props, unsigned key, float def);             // 0x004e1c70

// maxss/minss clamp of the /arch:SSE module: max(0, x) then min(.., hi).
__forceinline float ClampMax(float x, float hi)
{
    __asm {
        xorps xmm0, xmm0
        maxss xmm0, x
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// c += (t - c) * k, component-wise, in place.
static inline void Lerp4(Vec4& c, const Vec4& t, float k)
{
    c.x = c.x + (t.x - c.x) * k;
    c.y = (t.y - c.y) * k + c.y;
    c.z = (t.z - c.z) * k + c.z;
    c.w = (t.w - c.w) * k + c.w;
}

static inline ColorIface* CastColor(CastWin* p) { return p ? p->Cast(0xf15f4bd) : 0; }

struct FeedItem {
    char pad0[0x68];
    Vec4 mTargetArea;           // 0x68
    char pad1[0xc];
    bool mActiveA;              // 0x84
    bool mActiveB;              // 0x85
    bool mRefreshNumbers;       // 0x86
    char pad2;
    float mTimerB;              // 0x88  (clears mActiveB when it expires)
    float mTimerA;              // 0x8c  (clears mActiveA)
    char pad3[0x10];
    AreaWin* mAreaWin;          // 0xa0
    CastWin* mWinC;             // 0xa4
    CastWin* mWinD;             // 0xa8
    ImageWin* mImage;           // 0xac
    void* mSpinWin;             // 0xb0
    char pad4[4];
    CastWin* mWinE;             // 0xb8
    CastWin* mWinF;             // 0xbc
    char pad5[0x14];
    Vec4 mTargetA;              // 0xd4
    Vec4 mColorA;               // 0xe4
    Vec4 mTargetB;              // 0xf4
    Vec4 mColorB;               // 0x104
    char pad6[0x2d];
    bool mFlag141;              // 0x141
    bool mFlag142;              // 0x142
    char pad7[0x41];
    TailObj* mTail;             // 0x184

    bool FUN_00667c80(void* a1, void* msg);
    void FUN_00668000(const wchar_t* s);
    __declspec(noinline) void FUN_00668070();
    void FUN_00668550(unsigned dt);
};

// -----------------------------------------------------------------------------
// @ 0x00667c80  SP::cSPUIFeedListItem::DoMessage
// -----------------------------------------------------------------------------
bool FeedItem::FUN_00667c80(void* a1, void* msg) {
    (void)a1;
    void* self = this;
    if (*(uint8_t*)((char*)self + 0xc3) && *(int*)((char*)msg + 8) != 0x1c &&
        *(int*)((char*)msg + 8) != 9)
        return false;

    uint32_t t = *(uint32_t*)((char*)msg + 8);
    if (t > 0x1b) {
        if (t == 0x1c) {
            // ---- case 0x1c
            if (*(int*)((char*)msg + 0xc) != 1) return false;
            if (*(uint8_t*)((char*)self + 0xc1)) {
                void* wm = SP_WindowManager();
                void* r = ((FnPtrV)VT(wm)[18])(wm);
                if (!FUN_00805150(*(void**)((char*)self + 0xa0), r)) {
                    *(uint8_t*)((char*)self + 0xc1) = 0;
                    FUN_00667ae0(self);
                }
            }
            if (*(void**)((char*)msg + 0x18) == *(void**)((char*)self + 0xa0)) return false;
            void* p = *(void**)((char*)msg + 0x18);
            ((FnVoid)VT(p)[0x42])(p);
            return false;
        }
        if (t != 0x287259f6) return false;

        // ---- case 0x287259f6 : window-id sub-dispatch
        switch (*(int*)((char*)msg + 0xc)) {
        case 0xd48f0e8a: {
            KillSetiEffects(GetRecorderState(), 0x6e2ce16d);
            void* ms = SP_MessageServer();
            ((FnVoidIPI)VT(ms)[5])(ms, 0x6134914, self, 0);
            return true;
        }
        case 0xb48e8be4: {
            KillSetiEffects(GetRecorderState(), 0x7bb89a55);
            if (!*(uint8_t*)((char*)self + 0x140)) {
                if (*(uint32_t*)((char*)self + 0x38) | *(uint32_t*)((char*)self + 0x3c)) {
                    void* ms = SP_MessageServer();
                    ((FnVoidIPI)VT(ms)[5])(ms, 0x6299932, (char*)self + 0x38, 0);
                }
            }
            return true;
        }
        case 0x948f0e66: {
            KillSetiEffects(GetRecorderState(), 0x32120868);
            void* ms = SP_MessageServer();
            ((FnVoidIPI)VT(ms)[5])(ms, 0x148f5c9d, 0, 0);
            return true;
        }
        case 0x748e61d2: {
            KillSetiEffects(GetRecorderState(), 0xabceb434);
            void* ms = SP_MessageServer();
            ((FnVoidIPI)VT(ms)[5])(ms, 0x5a86fa1, 0, 0);
            return true;
        }
        case 0x7c64df0:
        case 0x7c64218: {
            if (!*(void**)((char*)self + 0x94)) return true;
            if (!*(uint8_t*)((char*)self + 0xc2)) return true;
            KillSetiEffects(GetRecorderState(), 0xabceb434);
            bool bl = (*(int*)((char*)msg + 0xc) == 0x7c64218);
            void* eax = FUN_0067cb30();
            void* sub = *(void**)((char*)eax + 0x58);
            ((Sub54*)sub)->FUN_0054ea20(*(int*)((char*)self + 0x134), bl ? 1 : 0);
            void* layout = *(void**)((char*)self + 0x94);
            void* w = ((cSPUILayout*)layout)->FindWindowByID(0x7c64218, 1);
            if (w) {
                bool f = *(uint8_t*)((char*)self + 0xc2) && !bl;
                ((FnVoidII)VT(w)[31])(w, 1, f ? 1 : 0);
            }
            void* layout2 = *(void**)((char*)self + 0x94);
            void* w2 = ((cSPUILayout*)layout2)->FindWindowByID(0x7c64df0, 1);
            if (w2) {
                bool f = *(uint8_t*)((char*)self + 0xc2) && bl;
                ((FnVoidII)VT(w2)[31])(w2, 1, f ? 1 : 0);
            }
            return true;
        }
        default:
            return false;
        }
    }

    if (t == 0x1b) {
        // ---- case 0x1b
        if (*(int*)((char*)msg + 0xc) != 1) return false;
        if (!*(uint8_t*)((char*)self + 0xc1)) {
            unsigned char b1 = StartBanMode(0x3e8);
            unsigned char b2 = StartBanMode(0x3ea);
            unsigned char b3 = StartBanMode(0x3e9);
            if (!b1 && !b2 && !b3) {
                *(uint8_t*)((char*)self + 0xc1) = 1;
                FUN_00667ac0(self);
            }
        }
        if (*(void**)((char*)msg + 0x18) == *(void**)((char*)self + 0xa0)) return false;
        void* p = *(void**)((char*)msg + 0x18);
        ((FnVoid)VT(p)[0x41])(p);
        return false;
    }

    switch (t) {
    case 6: {
        if (*(void**)((char*)msg + 4) != *(void**)((char*)self + 0xa0)) return false;
        if (*(int*)((char*)msg + 0x18) != 0x3e8) return false;
        FUN_00667b00(self);
        return false;
    }
    case 9: {
        void* wm = SP_WindowManager();
        ((FnVoidIII)VT(wm)[4])(wm, (int)*(void**)((char*)self + 0xa0),
                               *(int*)((char*)self + 0x98), (int)msg);
        return false;
    }
    default:
        return false;
    }
}

// -----------------------------------------------------------------------------
// @ 0x00668000  SetName / assign the display string
// -----------------------------------------------------------------------------
void FeedItem::FUN_00668000(const wchar_t* s) {
    if (s && !FUN_0087da10(s, (char*)this + 0x18)) {
        const wchar_t* p = s;
        while (*p) ++p;
        WString_Assign((char*)this + 0x18, s, p);
        void* q = *(void**)((char*)this + 0xa4);
        if (q) {
            void* v = *(void**)((char*)this + 0x18);
            ((FnVoid)VT(q)[0x20])(q);
            (void)v;
        }
    }
}

// -----------------------------------------------------------------------------
// @ 0x00668070  SP::cSPUIFeedListItem::QueryNumItems  (PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void FeedItem::FUN_00668070() {
    // Skeleton: the real body builds a large set of SPUI window-shade/scale animations
    // via the animator (cSPUIAnimator::AddAnimation/RemoveAnimation, SPUICreateWindowAnimation*,
    // SP::ColorRGBAToU32, Locale::SetNumberString, WStr_Format) - reconstructed only in outline.
    if (*(int*)((char*)this + 0x64) != -1 && *(void**)((char*)this + 0xb0) != 0) {
        void* browser = SP_AssetBrowser();
        if (browser) {
            browser = SP_AssetBrowser();
            if (browser && *(void**)((char*)browser + 0x18)) {
                // animation blocks omitted (partial)
            }
        }
    }
    if (!*(uint8_t*)((char*)this + 0xc2)) *(uint8_t*)((char*)this + 0x142) = 1;
    *(uint32_t*)((char*)this + 0x64) = *(uint32_t*)((char*)this + 0x60);
}

// -----------------------------------------------------------------------------
// @ 0x00668550  SP::cSPUIFeedListItem::Update  (per-frame animation, dt in ms)
// -----------------------------------------------------------------------------
void FeedItem::FUN_00668550(unsigned dt) {
    if (mRefreshNumbers) {
        FUN_00668070();
        mRefreshNumbers = false;
    }
    float f = (float)dt;
    float rectK = ClampMax(f * 0.012f, 1.0f);
    float colorK = ClampMax(f * 0.0065f, 1.0f);
    float step = f * 0.001f;

    if (mTimerA > 0.0f) {
        float v = mTimerA - step;
        mTimerA = v;
        if (v <= 0.0f) {
            mTimerA = 0.0f;
            mActiveA = false;
        }
    }
    if (mTimerB > 0.0f) {
        float v = mTimerB - step;
        mTimerB = v;
        if (v <= 0.0f) {
            mTimerB = 0.0f;
            mActiveB = false;
        }
    }

    // Slide the root window's area toward the target area.
    if (mAreaWin) {
        Vec4 cur;
        GetWindowArea(&cur, mAreaWin);
        if (cur.x != mTargetArea.x || cur.y != mTargetArea.y ||
            cur.z != mTargetArea.z || cur.w != mTargetArea.w) {
            cur.w = (mTargetArea.w - cur.w) * rectK + cur.w;
            cur.y = (mTargetArea.y - cur.y) * rectK + cur.y;
            cur.z = (mTargetArea.z - cur.z) * rectK + cur.z;
            cur.x = (mTargetArea.x - cur.x) * rectK + cur.x;
            if (fabs(cur.w - mTargetArea.w) < 1.5f && fabs(cur.y - mTargetArea.y) < 1.5f &&
                fabs(cur.z - mTargetArea.z) < 1.5f && fabs(cur.x - mTargetArea.x) < 1.5f) {
                cur.x = mTargetArea.x;
                cur.y = mTargetArea.y;
                cur.z = mTargetArea.z;
                cur.w = mTargetArea.w;
            }
            mAreaWin->SetArea(&cur);
        }
    }

    // Spinner (rotation about Z while its alpha is above zero).
    if (mSpinWin) {
        if (GetWindowAlpha(mSpinWin) > 0.0f) {
            float ang = GetElapsedSeconds() * -2.0f;
            Vec4 q;
            q.x = 0.0f;
            q.y = 0.0f;
            q.z = 1.0f;
            q.w = ang;
            SetWindowRotation(mSpinWin, &q);
        }
    }

    // Fade both colours toward their targets.
    Lerp4(mColorA, mTargetA, colorK);
    Lerp4(mColorB, mTargetB, colorK);

    if (mWinC) CastColor(mWinC)->SetColor(ColorRGBAToU32(&mColorB));
    if (mWinD) CastColor(mWinD)->SetColor(ColorRGBAToU32(&mColorB));
    if (mWinE) CastColor(mWinE)->SetColor(ColorRGBAToU32(&mColorB));
    if (mWinF) CastColor(mWinF)->SetColor(ColorRGBAToU32(&mColorB));

    if (mImage) {
        mImage->SetColor(ColorRGBAToU32(&mColorA));
        if (!mActiveB && mFlag141 && mFlag142 && SP_AssetBrowserG() && SP_AssetBrowserG()->mProps) {
            Vec4 pulse;
            Vec4 white(1.0f, 1.0f, 1.0f, 0.0f);
            GetPropertyColor(&pulse, SP_AssetBrowserG()->mProps, 0x94ab9c0f, white);
            float speed = GetPropertyFloat(SP_AssetBrowserG()->mProps, 0x7cb53b5, 1.0f);
            Vec4 base = mColorA;
            float k = ((float)sin(GetElapsedSeconds() * speed) + 1.0f) * 0.5f;
            Vec4 res;
            res.x = (pulse.x - base.x) * k + base.x;
            res.y = (pulse.y - base.y) * k + base.y;
            res.z = (pulse.z - base.z) * k + base.z;
            res.w = (pulse.w - base.w) * k + base.w;
            mImage->SetColor(ColorRGBAToU32(&res));
        }
    }
    if (mTail) mTail->Tick();
}
