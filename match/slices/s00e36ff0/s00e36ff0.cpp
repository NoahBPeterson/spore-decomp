// Slice s00e36ff0 (batch gold6) -- SP::cSPUITimeline timeline-time helpers.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The retail object keeps its cSPUILayout* at +0x30, its window handles at
// +0x38/+0x3c/+0x4c/+0x54/+0x58/+0x60 and the timeline-node vector between
// +0x184 (begin) and +0x188 (end).  Members are named at their retail offsets.

#include "../../include/types.h"
#include <math.h>

typedef unsigned int uintptr_t;

// ------------------------------------------------------------------ UTFWin model
struct Object {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual void ScalarDeletingDtor();     // +0x08
};

struct Rect  { float left, top, right, bottom; };
struct Vector2 { float x, y; };
struct Point { float x; float y; };

struct IWindow : Object {
    virtual void pad0c();
    virtual IWindow* GetParent();
    virtual void pad14();
    virtual void pad18();
    virtual void pad1c();
    virtual void pad20();
    virtual void pad24();
    virtual void pad28();
    virtual void pad2c();
    virtual void pad30();
    virtual const Rect* GetArea();                     // +0x34
    virtual const Rect* GetRealArea();                 // +0x38
    virtual void pad3c();
    virtual void pad40();
    virtual void pad44();
    virtual void pad48();
    virtual void pad4c();
    virtual void pad50();
    virtual void pad54();
    virtual void pad58();
    virtual void pad5c();
    virtual void pad60();
    virtual void pad64();
    virtual void pad68();
    virtual void pad6c();
    virtual void SetLayoutLocation(float x, float y);  // +0x70
    virtual void pad74();
    virtual void pad78();
    virtual void SetVisible(bool visible, bool recursive);  // +0x7c
    virtual void SetText(const wchar_t* s);            // +0x80
    virtual void pad84();
    virtual void pad88();
    virtual void pad8c();
    virtual void pad90();
    virtual void pad94();
    virtual void pad98();
    virtual void pad9c();
    virtual void padA0();
    virtual void padA4();
    virtual void padA8();
    virtual void padAc();
    virtual void padB0();
    virtual void padB4();
    virtual void padB8();
    virtual void padBc();
    virtual Point ToGlobalCoordinates(Point p);        // +0xc0
    virtual Point ToLocalCoordinates(Point p);         // +0xc4
    virtual void padC8();
    virtual void padCc();
    virtual void padD0();
    virtual void padD4();
    virtual void padD8();
    virtual void padDc();
    virtual void padE0();
    virtual void padE4();
    virtual void padE8();
    virtual void padEc();
    virtual void padF0();
    virtual void padF4();
    virtual void padF8();
    virtual void padFc();
    virtual void pad100();
    virtual void SetParent(IWindow* parent);           // +0x104
};

class cSPUILayout : public Object { public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};

// ------------------------------------------------------------------ misc types
struct LimitStopwatch {
    uint8_t pad[0x1c];
    void SetTimeLimit(uint32_t ms, bool start);             // 0x0093a480
};

// EA::Audio::GetSystemAT() result (vtable slot indices used by BeginCloseTimeline).
struct IAudioSystem {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  GetRecorderState();                        // +0x20
    virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
    virtual void v34();
    virtual void PlayRoutedSound(uint32_t id);              // +0x38
    virtual void v3c();
    virtual void SetSoundParam(uint32_t id, int value);     // +0x40
    virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
    virtual void v54();
    virtual void StopAllSounds();                           // +0x58
};
IAudioSystem* SP_GetAudioSystemAT();                        // 0x00a206f0 (EA::Audio::GetSystemAT)

// A "visible node" wrapper (0x00e46020 SetVisibleRecursive).
struct VisNode {
    void SetVisibleRecursive(char on);                      // 0x00e46020
};

// The "Timeline" object a timeline node derives from (vtable at +0x0).
struct Timeline {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    void FUN_00e46d80(Vector2 a, int b, Vector2 d, bool f);  // 0x00e46d80
};

// A timeline node (mirrors the [this+0x184..0x188] vector elements).
union FloatBits { float f; uint32_t u; };
struct TimelineNode {
    uint8_t   pad00[0x1c];
    IWindow*  p1c;                                          // +0x1c (window)
    uint32_t  pad20[0x14];                                  // +0x20 .. +0x6f
    float     mf70;                                         // +0x70
    FloatBits m74;                                          // +0x74
    uint32_t  pad78[0x1e];                                  // +0x78 .. +0xef
    uint32_t  fF0;                                          // +0xf0
    uint32_t  padF4;                                        // +0xf4
    float     fF8;                                          // +0xf8
    float     fFC;                                          // +0xfc
};

// ------------------------------------------------------------------ callees
extern "C" {
void*  __cdecl SP_WindowManager();                          // 0x0067caa0
void*  __cdecl SP_GetGameModeData(int opt);                 // 0x00b5b800
}

void _CIpow();                                              // 0x011e08f0
extern "C" long long __stdcall allmul(long long a, long long b);     // 0x011e0a90
extern "C" unsigned long long __stdcall aulldiv(unsigned long long a,
                                                unsigned long long b); // 0x011e0970

extern "C" int __cdecl Snprintf16(wchar_t* buf, unsigned int count, const wchar_t* fmt, ...); // 0x00939a30
extern "C" int __cdecl Sprintf16(wchar_t* buf, const wchar_t* fmt, ...);                     // 0x009399c0

struct cCameraManager {
    void* ActiveControllerIndex();                          // 0x0098f940
};

// ------------------------------------------------------------------ globals
extern char gStageKeys[];                                   // DAT_01654c00 .. +5
extern int  gStageTime0[];                                  // DAT_016accf0
extern int  gStageTime1[];                                  // DAT_016acd00
extern int  gStageTime2[];                                  // DAT_016acd10
extern int  gStageTime3[];                                  // DAT_016acd20
extern int  gStageTime4[];                                  // DAT_016acd30
extern int  gStageT40;                                      // DAT_016acd40
extern int  gStageT50;                                      // DAT_016acd50
extern int  gStageT60;                                      // DAT_016acd60
extern int  gStageT70;                                      // DAT_016acd70
extern int  DAT_016acf2c;                                   // 0x016acf2c stage limit
extern uint8_t DAT_016acc48;                                // 0x016acc48 init guard
extern float   DAT_016acc44;                                // 0x016acc44 cached width
extern float   DAT_016ace10f;                               // 0x016ace10 pow constant
extern float   DAT_016ace20f;                               // 0x016ace20 pow exponent

extern Vector2 gVacc90;                                     // 0x016acc90

// ------------------------------------------------------------------ cString
struct cString {
    uint8_t data[0x14];
    cString(uint32_t ns, uint32_t id, const wchar_t* s);     // 0x006b5770
    const wchar_t* GetText();                                // 0x006b55c0
    ~cString();                                              // 0x006b5240
};

// ------------------------------------------------------------------ helpers
static inline int ClampLoHi(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

struct VecContainer { bool IsMember(int id); };             // 0x00e45fe0

// ------------------------------------------------------------------ cSPUITimeline
struct cSPUITimeline {
    void*         mvpVtbl;                                    // +0x00
    uint32_t      mEmbedded[0x0b];                            // +0x04 embedded window subobject
    cSPUILayout*  mpLayout;                                   // +0x30
    uint32_t      pad34;                                      // +0x34
    IWindow*      mpWin38;                                    // +0x38
    IWindow*      mpWin3c;                                    // +0x3c
    uint32_t      pad40[3];                                   // +0x40
    IWindow*      mpWin4c;                                    // +0x4c
    uint32_t      pad50;                                      // +0x50
    IWindow*      mpWin54;                                    // +0x54
    IWindow*      mpWin58;                                    // +0x58
    uint32_t      pad5c;                                      // +0x5c
    IWindow*      mpWin60;                                    // +0x60
    int           mSelectedIdx;                               // +0x64
    uint32_t      pad68[3];                                   // +0x68
    FloatBits     m74;                                        // +0x74
    float         mf78;                                       // +0x78
    uint32_t      pad7c;                                      // +0x7c
    float         mf80;                                       // +0x80
    float         mf84;                                       // +0x84
    uint32_t      pad88[0x3f];                                // +0x88 .. +0x183
    TimelineNode** mpNodesBegin;                              // +0x184
    TimelineNode** mpNodesEnd;                                // +0x188
    uint32_t      pad18c[0x0f];                               // +0x18c .. +0x1c7
    int           mnState1c8;                                 // +0x1c8
    uint32_t      pad1cc[0x1f];                               // +0x1cc .. +0x247
    uint8_t       mb248;                                      // +0x248
    uint8_t       pad249[0x37];                               // +0x249 .. +0x27f
    int           mn280;                                      // +0x280
    unsigned      mn284;                                      // +0x284
    uint32_t      pad288[0x17];                               // +0x288 .. +0x2e3
    wchar_t       mText[12];                                  // +0x2e4
    uint32_t      pad2fc;                                     // +0x2fc
    uint32_t      mTimeLo;                                    // +0x300
    uint32_t      mTimeHi;                                    // +0x304
    uint32_t      mT308;                                      // +0x308
    uint32_t      mT30c;                                      // +0x30c
    uint32_t      mT310;                                      // +0x310
    uint32_t      mT314;                                      // +0x314
    uint32_t      mT318;                                      // +0x318
    uint32_t      mT31c;                                      // +0x31c
    uint32_t      mT320;                                      // +0x320
    uint32_t      mT324;                                      // +0x324
    uint32_t      mT328;                                      // +0x328
    uint32_t      mT32c;                                      // +0x32c
    uint32_t      pad330[8];                                  // +0x330 .. +0x34f
    LimitStopwatch mStopwatch;                                // +0x350
    uint8_t       pad36c[5];                                  // +0x36c .. +0x370
    uint8_t       mb371;                                      // +0x371
    uint32_t      pad372[0x63];                               // +0x372 .. +0x4ff

    int64_t       GetTimelineTime(void* controller);          // 0x00e36ff0
    void          SetTimelineTime(uint32_t lo, uint32_t hi);  // 0x00e372b0
    bool          FUN_00e37750();                             // 0x00e37750
    int           FUN_00e37780(void* node);                   // 0x00e37780
    void          FUN_00e37840(IWindow* target, float a, float b,
                               float c, float d, float e, float f,
                               float g, float h);             // 0x00e37840
    void          FUN_00e37910();                             // 0x00e37910
    IWindow*      Self() { return (IWindow*)mEmbedded; }      // +0x04 embedded window
    void          BeginCloseTimeline();                       // 0x00e37970
    double        FUN_00e37b40(TimelineNode* n, float a, int b);// 0x00e37b40
    void          FUN_00e37be0();                             // 0x00e37be0
    double        FUN_00e37d70(float v);                      // 0x00e37d70
    TimelineNode* FUN_00e37e50(int idx, int which);           // 0x00e37e50
    double        FUN_00e37f30(int idx);                      // 0x00e37f30
};

// ================================================================== 0x00e36ff0
struct Controller {
    uint32_t pad00[0x39];                                     // +0x00 .. +0xe3
    uint32_t mModeE4;                                         // +0xe4
};

// @ 0x00e36ff0
int64_t cSPUITimeline::GetTimelineTime(void* controller)
{
    int64_t total = 0;

    if (controller != 0) {
        int* cm = (int*)((cCameraManager*)controller)->ActiveControllerIndex();
        if (cm != 0) {
            int nodeIdx = *(int*)(cm[3] + 8);

            uint32_t mode = ((Controller*)controller)->mModeE4;
            char* scale = (char*)-1;
            bool accum = false;
            if ((int)mode < (int)0xbeb528cb) {
                if (mode == 0xa426730b)
                    scale = gStageKeys + 0;
                else if (mode == 0xad56080c) {
                    scale = gStageKeys + 1;
                    accum = true;
                }
            } else {
                if (mode == 0xbeb528cb) {
                    scale = gStageKeys + 4;
                    accum = true;
                } else if (mode == 0xf71fa311) {
                    scale = gStageKeys + 2;
                    accum = true;
                } else if (mode == 0x2db6dad3) {
                    scale = gStageKeys + 5;
                    accum = true;
                }
            }

            uint32_t m32c = 0;

            if (accum) {
                m32c = mT32c;
                if ((int)m32c > (int)(intptr_t)(gStageKeys + 0)) {
                    total = allmul((int64_t)gStageTime0[0], (int64_t)gStageT40);
                } else if (mT310 != 0) {
                    total = allmul((int64_t)(int)(mT30c - mT308), (int64_t)gStageTime0[0]);
                }

                if (scale > gStageKeys + 1) {
                    if ((int)m32c > (int)(intptr_t)(gStageKeys + 1))
                        total += allmul((int64_t)(int)(gStageT50 - gStageT40), (int64_t)gStageTime1[0]);
                    else if (mT318 != 0)
                        total += allmul((int64_t)(int)(mT314 - mT310), (int64_t)gStageTime1[0]);
                }

                if (scale > gStageKeys + 2) {
                    if ((int)m32c > (int)(intptr_t)(gStageKeys + 2))
                        total += allmul((int64_t)(int)(gStageT60 - gStageT50), (int64_t)gStageTime2[0]);
                    else if (mT320 != 0)
                        total += allmul((int64_t)(int)(mT31c - mT318), (int64_t)gStageTime2[0]);
                }

                if (scale > gStageKeys + 4) {
                    if ((int)m32c > (int)(intptr_t)(gStageKeys + 4))
                        total += allmul((int64_t)(int)(gStageT70 - gStageT60), (int64_t)gStageTime3[0]);
                    else if (mT328 != 0)
                        total += allmul((int64_t)(int)(mT324 - mT320), (int64_t)gStageTime3[0]);
                }
            }

            uint32_t sel = (uint32_t)(scale - gStageKeys);
            if (sel > 5)
                return total;

            uint32_t unit;
            switch (sel) {
            case 0:
                total += allmul((int64_t)(int)(nodeIdx - mT308), (int64_t)gStageTime0[0]);
                unit = 100000000;
                break;
            case 1:
                total += allmul((int64_t)(int)(nodeIdx - mT310), (int64_t)gStageTime1[0]);
                unit = 1000000;
                break;
            case 2:
                total += allmul((int64_t)(int)(nodeIdx - mT318), (int64_t)gStageTime2[0]);
                unit = 10000;
                break;
            case 3:
                return total;
            case 4:
                total += allmul((int64_t)(int)(nodeIdx - mT320), (int64_t)gStageTime3[0]);
                unit = 100;
                break;
            default:
                total += allmul((int64_t)(int)(nodeIdx - mT328), (int64_t)gStageTime4[0]);
                unit = 100;
                break;
            }
            unsigned long long q = aulldiv((unsigned long long)total, (unsigned long long)unit);
            total = allmul((int64_t)q, (int64_t)unit);
        }
    }
    return total;
}

// ================================================================== 0x00e372b0
// @ 0x00e372b0
void cSPUITimeline::SetTimelineTime(uint32_t lo, uint32_t hi)
{
    if (hi > 0xe8 || (hi == 0xe8 && lo > 0xd4a50fff)) {
        lo = 0xd4a50fff;
        hi = 0xe8;
    }
    if (lo == mTimeLo && hi == mTimeHi)
        return;

    mTimeLo = lo;
    mTimeHi = hi;
    Snprintf16(mText, 0xd, L"%012I64u", mTimeLo, mTimeHi);

    cSPUILayout* layout = mpLayout;

    uint64_t V = ((uint64_t)mTimeHi << 32) | mTimeLo;
    uint64_t A = V / 1000000000ULL;

    {
        IWindow* w = layout->FindWindowByID(0x55496b13, true);
        if (w != 0) {
            wchar_t buf[16];
            short c0 = *(short*)(mText + 0);
            if (c0 == 0x30) {
                if (*(short*)(mText + 1) == 0x30)
                    Sprintf16(buf, (const wchar_t*)0x1446144, *(uint16_t*)(mText + 2));
                else
                    Sprintf16(buf, L"%c%c", *(uint16_t*)(mText + 1), *(uint16_t*)(mText + 2));
            } else {
                Sprintf16(buf, L"%c%c%c", (uint16_t)c0, *(uint16_t*)(mText + 1),
                          *(uint16_t*)(mText + 2));
            }
            w->SetText(buf);

            IWindow* w2 = layout->FindWindowByID(0x6942910, true);
            if (w2 != 0) {
                uint32_t sid = 0x694179e;
                if (A == 0) sid = 0x6941dc0;
                else if (A == 1) sid = 0x55496321;
                cString c(0x9a5acf10, sid, 0);
                w2->SetText(c.GetText());
                c.~cString();
            }
        }
    }

    uint64_t B = A * 1000;
    uint64_t C = V / 1000000ULL;

    {
        IWindow* w = layout->FindWindowByID(0x55496b14, true);
        if (w != 0) {
            wchar_t buf[16];
            Sprintf16(buf, L"%c%c%c", *(uint16_t*)(mText + 3), *(uint16_t*)(mText + 4),
                      *(uint16_t*)(mText + 5));
            w->SetText(buf);

            IWindow* w2 = layout->FindWindowByID(0x6942911, true);
            if (w2 != 0) {
                uint32_t sid = 0x694179f;
                uint64_t d = C - B;
                if (d == 0) sid = 0x6941dc1;
                else if (d == 1) sid = 0x55496322;
                cString c(0x9a5acf10, sid, 0);
                w2->SetText(c.GetText());
                c.~cString();
            }
        }
    }

    uint64_t D = (B + (C - B)) * 1000;
    uint64_t E = V / 1000ULL;

    {
        IWindow* w = layout->FindWindowByID(0x55496b15, true);
        if (w != 0) {
            wchar_t buf[16];
            Sprintf16(buf, L"%c%c%c", *(uint16_t*)(mText + 6), *(uint16_t*)(mText + 7),
                      *(uint16_t*)(mText + 8));
            w->SetText(buf);

            IWindow* w2 = layout->FindWindowByID(0x6942912, true);
            if (w2 != 0) {
                uint32_t sid = 0x69417a0;
                uint64_t d = E - D;
                if (d == 0) sid = 0x6941dc2;
                else if (d == 1) sid = 0x55496323;
                cString c(0x9a5acf10, sid, 0);
                w2->SetText(c.GetText());
                c.~cString();
            }
        }
    }

    uint64_t F = (D + (E - D)) * 1000;

    {
        IWindow* w = layout->FindWindowByID(0x55496b16, true);
        if (w != 0) {
            wchar_t buf[16];
            Sprintf16(buf, L"%c%c%c", *(uint16_t*)(mText + 9), *(uint16_t*)(mText + 10),
                      *(uint16_t*)(mText + 11));
            w->SetText(buf);

            IWindow* w2 = layout->FindWindowByID(0x6942913, true);
            if (w2 != 0) {
                uint32_t sid = 0x69417a1;
                uint64_t d = V - F;
                if (d == 0) sid = 0x6941dc3;
                else if (d == 1) sid = 0x55496324;
                cString c(0x9a5acf10, sid, 0);
                w2->SetText(c.GetText());
                c.~cString();
            }
        }
    }
}

// ================================================================== 0x00e37750
// @ 0x00e37750
bool cSPUITimeline::FUN_00e37750()
{
    if (mn280 < DAT_016acf2c)
        return true;
    unsigned v = mn284;
    return v != 0 && v != 8;
}

// ================================================================== 0x00e37780
static inline bool TimelineKeyValid(int k)
{
    switch (k) {
    case 0x3e2a3040:
    case 0xade76cce:
    case 0xdbd1b537:
    case 0x6701aff5:
        return true;
    default:
        return false;
    }
}

// @ 0x00e37780
int cSPUITimeline::FUN_00e37780(void* p)
{
    int result = 0;
    if (p != 0 && TimelineKeyValid(*(int*)((char*)p + 0x68))) {
        int n = (int)(mpNodesEnd - mpNodesBegin);
        result = 1;
        for (int i = 0; i < n; ++i) {
            VecContainer* node = (VecContainer*)mpNodesBegin[i];
            if ((void*)node == p)
                break;
            if (node->IsMember((int)p))
                break;
            VecContainer* cur = (VecContainer*)mpNodesBegin[i];
            if (cur != 0 && TimelineKeyValid(*(int*)((char*)cur + 0x68)))
                ++result;
        }
    }
    return result;
}

// ================================================================== 0x00e37840
// @ 0x00e37840
void cSPUITimeline::FUN_00e37840(IWindow* target, float a, float b, float c, float d,
                                 float e, float f, float g, float h)
{
    struct Style {
        float f0, f1;
        int   i2;
        float f3, f4, f5, f6;
        int   i7;
        float f8, f9, f10, f11;
        int   i12;
        float f13, f14, f15, f16;
        int   i17;
        float f18, f19;
    } st;
    extern float _HK_REAL_ONE;
    st.f0  = a;
    st.f1  = b;
    st.i2  = -1;
    st.f3  = 0.0f;
    st.f4  = 0.0f;
    st.f5  = e;
    st.f6  = f;
    st.i7  = -1;
    st.f8  = _HK_REAL_ONE;
    st.f9  = 0.0f;
    st.f10 = g;
    st.f11 = h;
    st.i12 = -1;
    st.f13 = _HK_REAL_ONE;
    st.f14 = _HK_REAL_ONE;
    st.f15 = c;
    st.f16 = d;
    st.i17 = -1;
    st.f18 = 0.0f;
    st.f19 = _HK_REAL_ONE;
    typedef void (__thiscall* Fn)(void*, void*, int, uint32_t);
    ((Fn)(*(void***)target)[0x54 / 4])(target, &st, 1, m74.u);
}

// ================================================================== 0x00e37910
// @ 0x00e37910
void cSPUITimeline::FUN_00e37910()
{
    if (IWindow* w = mpWin3c)
        w->SetParent(Self());
    if (IWindow* w = mpWin4c)
        w->SetParent(Self());
    if (IWindow* w = mpWin54)
        w->SetParent(Self());
    if (IWindow* w = mpWin38)
        w->SetParent(Self());
}

// ================================================================== 0x00e37970
// @ 0x00e37970
void cSPUITimeline::BeginCloseTimeline()
{
    int v;
    if (IAudioSystem* at = SP_GetAudioSystemAT())
        v = at->GetRecorderState();
    else
        v = 0;

    if (IAudioSystem* at2 = SP_GetAudioSystemAT()) {
        at2->PlayRoutedSound(0x3475365);
        at2->SetSoundParam(0x3475381, 0x9694e9ca);
        at2->SetSoundParam(0x3475385, v);
        at2->StopAllSounds();
    }

    mb371 = 1;
    mStopwatch.SetTimeLimit(500, true);

    if (IWindow* w = mpWin58)
        w->SetVisible(1, 0);
    if (IWindow* w = mpWin60)
        w->SetVisible(1, 0);

    if (IWindow* w = mpLayout->FindWindowByID(0x4486ae8, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0x4486b30, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0x54e53d9d, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0xf54a5ddc, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0x61388da, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0x61388db, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0x694d94c, true))
        w->SetVisible(1, 0);
    if (IWindow* w = mpLayout->FindWindowByID(0x694d94b, true))
        w->SetVisible(1, 0);

    int n = (int)(mpNodesEnd - mpNodesBegin);
    for (int i = 0; i < n; ++i)
        ((VisNode*)mpNodesBegin[i])->SetVisibleRecursive(0);
}

// ================================================================== 0x00e37b40
// @ 0x00e37b40
double cSPUITimeline::FUN_00e37b40(TimelineNode* n, float a, int b)
{
    float f74 = n->m74.f;
    float f70 = n->mf70;
    if (n->p1c != 0) {
        Rect* r = (Rect*)((const Rect* (__thiscall*)(void*))(*(void***)n->p1c)[0x38 / 4])(n->p1c);
        Vector2 p;
        p.x = a;
        p.y = ((r->bottom - r->top) - f70) * 0.5f;
        ((Timeline*)n)->FUN_00e46d80(p, b, gVacc90, false);
    }
    return f74 + a + 5.0f;
}

// ================================================================== 0x00e37be0
// @ 0x00e37be0
void cSPUITimeline::FUN_00e37be0()
{
    IWindow* w3c = mpWin3c;
    float lx = 0.0f, lz = 0.0f;
    if (w3c != 0) {
        Rect* r = (Rect*)((const Rect* (__thiscall*)(void*))(*(void***)w3c)[0x38 / 4])(w3c);
        lx = r->left;
        lz = r->right;
    }

    IWindow* w60 = mpWin60;
    if (w60 == 0 || mnState1c8 == 0 || mb371 != 0)
        return;

    Rect* r60 = (Rect*)((const Rect* (__thiscall*)(void*))(*(void***)w60)[0x38 / 4])(w60);
    float f1 = r60->right;
    float f2 = r60->left;

    int n = (int)(mpNodesEnd - mpNodesBegin);
    TimelineNode* found = 0;
    if (n >= 2) {
        for (int i = n - 2; i >= 0; --i) {
            TimelineNode* node = mpNodesBegin[i];
            if (node->fF0 != 0) {
                found = node;
                break;
            }
        }
    }

    float f9 = 0.0f;
    if (found != 0 && found->p1c != 0) {
        Point pt;
        pt.x = found->fF8 + found->m74.f;
        pt.y = found->fFC;
        typedef Point (__thiscall* PFn)(void*, Point);
        Point res = ((PFn)(*(void***)found->p1c)[0xc0 / 4])(found->p1c, pt);
        f9 = res.x;
    }

    float f84 = mf84;
    float f78 = mf78;
    float f80 = mf80;
    mb248 = 0;

    typedef void (__thiscall* Fn)(void*, float, float);
    Fn fn = (Fn)(*(void***)w60)[0x70 / 4];

    if (f9 < f78) {
        fn(w60, f80, f84);
        mb248 = 1;
        return;
    }
    if ((lz - lx) <= f9) {
        fn(w60, f80 + (f1 - f2), f84);
        return;
    }
    fn(w60, f80 + (f9 - f78), f84);
}

// ================================================================== 0x00e37d70
// @ 0x00e37d70
double cSPUITimeline::FUN_00e37d70(float v)
{
    float x = v;
    if (x < -1.0f) x = -1.0f;
    if (1.0f < x) x = 1.0f;

    if (0.33333334f < x) {
        double p = pow((double)((x - 0.33333334f) * 1.5f), (double)DAT_016ace20f);
        return p * (double)DAT_016ace10f * 0.6666666 + 0.33333334;
    }
    if (x < -0.33333334f) {
        double p = pow((double)((x + 0.33333334f) * -1.5f), (double)DAT_016ace20f);
        return -0.33333334 - (p * (double)DAT_016ace10f) * 0.6666666;
    }
    return (double)x;
}

// ================================================================== 0x00e37e50
// @ 0x00e37e50
TimelineNode* cSPUITimeline::FUN_00e37e50(int idx, int which)
{
    int last = (int)(mpNodesEnd - mpNodesBegin) - 1;
    int index = ClampLoHi(idx, 0, last);
    int step = (which > 0) ? 1 : -1;
    int prev;
    int cur = index;
    void* r;
    do {
        prev = cur;
        cur = prev + step;
        int m = ClampLoHi(cur, 0, last);
        void* node = mpNodesBegin[m];
        r = ((cCameraManager*)node)->ActiveControllerIndex();
    } while (r != 0 && prev != index + which);

    last = (int)(mpNodesEnd - mpNodesBegin) - 1;
    if (prev < 0)
        return mpNodesBegin[0];
    if (prev > last)
        return mpNodesBegin[last];
    return mpNodesBegin[prev];
}

// ================================================================== 0x00e37f30
// @ 0x00e37f30
static float cSPUITimeline_GetScreenWidth();
double cSPUITimeline::FUN_00e37f30(int idx)
{
    static float s_width = cSPUITimeline_GetScreenWidth();
    if (idx == mSelectedIdx)
        return (double)s_width;
    return 0.0;
}

static float cSPUITimeline_GetScreenWidth()
{
    int* p = (int*)SP_WindowManager();
    p = (int*)((int (__thiscall*)(int*))(*(void**)(*p + 4)))(p);
    float* r = (float*)((float* (__thiscall*)(int*))(*(void**)(*p + 0x38)))(p);
    return r[2] - r[0];
}
