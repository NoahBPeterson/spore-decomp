// src/game/SPGonzago/SPUITimeline.cpp -- migrated from slice(s) s00e44200, s00e43270, s00e3eca0, s00e3cf60, s00e423a0, s00e42100, s00e40700, s00e3b9e0, s00e3a990, s00e39ab0, s00e38ce0, s00e37f90, s00e36ff0, s00e36150 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPUITimeline.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "cSPUIAnimator.h"
#include "cSPUILayout.h"
#include "EA/LimitStopwatch.h"
#include "SP/cCameraManager.h"
#include "SP/cString.h"
#include <math.h>
#include "SP/cPropertyList.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include <new>
#include <stddef.h>
#include <intrin.h>
#include "SP/cEmpire.h"
#include "SP/cPlanetRecord.h"
#include "cSPUILayoutManager.h"
#include "EA/ResourceMan/Key.h"
#include "SP/cCivilization.h"
#include "SP/cGameNounManager.h"
#include "SP/cIGonzagoSubsystem.h"
#include "SP/cSPEditorSpeciesManager.h"
#include "SP/cSPPalettePageUI.h"
#include "SP/cSpeciesProfile.h"
#include "SP/cConfigManager.h"
#include "SP/cSPPaletteItem.h"

// ---- items of slice s00e36150 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct RectF {
    float x0;
    float y0;
    float x1;
    float y1;
};
struct cTooltipSlot {
    float m_fX;
    float m_fY;
    float m_fW;
};
class IBase {
public:
    virtual void* Slot00() = 0;
    virtual void* Slot04() = 0;
    virtual void* Slot08() = 0;
    virtual void* Slot0c() = 0;
    virtual void* Slot10() = 0;
    virtual void* Slot14() = 0;
    virtual void* Slot18() = 0;
    virtual void* Slot1c() = 0;
    virtual void* Slot20() = 0;
    virtual void* Slot24() = 0;
    virtual void* Slot28() = 0;
    virtual void* Slot2c() = 0;
    virtual void* Slot30() = 0;
    virtual void* Slot34() = 0;
    virtual void* Slot38() = 0;
    virtual void* Slot3c() = 0;
    virtual void* Slot40() = 0;
    virtual void* Slot44() = 0;
    virtual void* Slot48() = 0;
    virtual void* Slot4c() = 0;
    virtual void* Slot50() = 0;
    virtual void* Slot54() = 0;
    virtual void* Slot58() = 0;
    virtual void* Slot5c() = 0;
    virtual ~IBase() {}
};
namespace EA {
class Stopwatch_s00e3_6150 {
public:
    Stopwatch_s00e3_6150() {}
    Stopwatch_s00e3_6150(int32_t nSource, bool bStart);     // 0x0093a560
    void Restart();                              // 0x00571e80
    int64_t GetElapsedTime();                    // 0x0093a5e0
    int64_t GetElapsedTimeFloat();               // 0x0093a3a0
    void SetBoolProperty();                      // 0x0093a2e0

    int64_t m_nStart;                            // +0x00
    int64_t m_nStop;                             // +0x08
    int32_t m_nSource;                           // +0x10
    float m_fRate;                               // +0x14
};
}
class cSPUILayout_s00e3_6150 {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void Release2();                     // +0x08
    void Shutdown(uint32_t nFlags);              // 0x00811ad0
    void SetVisibility(bool bVisible);           // 0x00810590
    bool IsVisible();                            // 0x00810070
    void* FindWindowByID(uint32_t nId, bool bFlag);            // 0x008105b0
    bool SetParentWin(void* pWin, bool bFlag, uint32_t nId);   // 0x008121b0
    bool Init(const void* pKey, bool bFlag, uint32_t nId);     // 0x008120d0
    void SetReloadCallback(void (__cdecl* pCallback)(void*, cSPUILayout_s00e3_6150*,
                                                     bool),
                           void* pUser);                       // 0x00810090
    void* GetWindow();                                         // 0x00810570
    cSPUILayout_s00e3_6150* InitDocument();                               // 0x00810000
};
class IWin {
public:
    virtual void AddRef0();                      // +0x00
    virtual void Release1();                     // +0x04
    virtual void SetVisible2(bool bVisible);     // +0x08
virtual void W0c();
virtual void W10();
virtual void W14();
virtual void W18();
virtual void W1c();
virtual void W20();
virtual void W24();
virtual void W28();
virtual void W2c();
virtual void W30();
virtual void W34();
virtual void W38();
virtual void W3c();
virtual void W40();
virtual void W44();
virtual void W48();
virtual void W4c();
virtual void W50();
virtual void W54();
virtual void W58();
virtual void W5c();
virtual void W60();
virtual void W64();
virtual void W68();
    virtual void SetRect6c(RectF* pRect);        // +0x6c
virtual void W70();
virtual void W74();
virtual void W78();
    virtual void SetFlags7c(bool bFlag, bool bOther);          // +0x7c
virtual void W80();
virtual void W84();
virtual void W88();
virtual void W8c();
virtual void W90();
virtual void W94();
virtual void W98();
virtual void W9c();
virtual void Wa0();
virtual void Wa4();
virtual void Wa8();
virtual void Wac();
virtual void Wb0();
virtual void Wb4();
virtual void Wb8();
virtual void Wbc();
virtual void Wc0();
virtual void Wc4();
virtual void Wc8();
virtual void Wcc();
virtual void Wd0();
virtual void Wd4();
    virtual void SetParentd8(IWin* pParent);     // +0xd8
};
class cSPUIAnimator_s00e3_6150 : public IBase {
public:
    bool Empty();                                // 0x007f6340
};
class cEditor {
public:
    uint8_t mPad000[0x284];                      // +0x000
    int32_t m_nState;                            // +0x284
};
uint32_t __cdecl SP_GetCurrentGameMode();        // 0x00b5b800
void* __cdecl FUN_00b3d410();                    // 0x00b3d410
uint32_t __cdecl GetGameModeHash();              // 0x00e36c80
class cUITimedTooltip : public IBase {
public:
    cUITimedTooltip();                                          // 0x00e36480
    ~cUITimedTooltip();                                         // 0x00e364d0
    void Shutdown();                                            // 0x00e36500
    void UpdateTimeoutA();                                      // 0x00e36540
    void UpdateTimeoutB(IWin* pWindow);                         // 0x00e365a0
    void Hide();                                                // 0x00e36620
    void* FindWindow(uint32_t nId, bool bFlag);                 // 0x00e36650
    void* DestroyDeleting(bool bDelete);                        // 0x00e36890
    void UpdateLayout();                                        // 0x00e369f0
    bool Init(const uint32_t& nKey, uint32_t nId, uint32_t nWidth,
              uint32_t nHeight, uint32_t a5, uint32_t a6);      // 0x00e36b30
    void ResetState();                                          // 0x00e36de0
    bool UpdateA();                                             // 0x00e36cd0
    bool UpdateB();                                             // 0x00e36d30
    bool UpdateC();                                             // 0x00e36d80
    bool UpdateD();                                             // 0x00e36e20
    bool UpdateE();                                             // 0x00e36e80
    cTooltipSlot* GetSlot(int32_t nIndex);                      // 0x00e36fb0

    uint32_t m_nPad04;                           // +0x004
    uint32_t m_nKey08;                           // +0x008
    cSPUILayout_s00e3_6150* m_pLayout;                      // +0x00c
    IWin* m_pWindow;                             // +0x010
    uint8_t mPad14[0x4];                         // +0x014
    EA::Stopwatch_s00e3_6150 m_swA;                         // +0x018
    EA::Stopwatch_s00e3_6150 m_swB;                         // +0x030
    uint32_t m_nTimeoutA;                        // +0x048
    uint32_t m_nTimeoutB;                        // +0x04c
    float m_f50;                                 // +0x050
    float m_f54;                                 // +0x054
    float m_f58;                                 // +0x058
    float m_f5c;                                 // +0x05c
    uint8_t mPad60[0x390];                       // +0x060
    uint32_t m_nMode3f0;                         // +0x3f0
    uint8_t mPad3f4[0x4];                        // +0x3f4
    EA::Stopwatch_s00e3_6150 m_sw3f8;                       // +0x3f8
    float m_fThreshold410;                       // +0x410
    uint8_t mPad414[0x4];                        // +0x414
    EA::Stopwatch_s00e3_6150 m_sw418;                       // +0x418
    float m_fThreshold430;                       // +0x430
    uint8_t mPad434[0x4];                        // +0x434
    EA::Stopwatch_s00e3_6150 m_sw438;                       // +0x438
    float m_fThreshold450;                       // +0x450
    bool m_bFlag454;                             // +0x454
    uint8_t mPad455[0x3];                        // +0x455
    cSPUIAnimator_s00e3_6150* m_pAnimator458;               // +0x458
    uint8_t mPad45c[0x4c];                       // +0x45c
    EA::Stopwatch_s00e3_6150 m_sw4a8;                       // +0x4a8
    float m_fThreshold4c0;                       // +0x4c0
    uint8_t mPad4c4[0x4];                        // +0x4c4
    EA::Stopwatch_s00e3_6150 m_sw4c8;                       // +0x4c8
    float m_fThreshold4e0;                       // +0x4e0
    uint8_t mPad4e4[0x9c];                       // +0x4e4
    cTooltipSlot m_slots[4];                     // +0x580
};
// ---- items of slice s00e36150 end

// ---- items of slice s00e36ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void*  __cdecl SP_WindowManager();                          // 0x0067caa0
extern "C" long long __stdcall allmul(long long a, long long b);     // 0x011e0a90
extern "C" unsigned long long __stdcall aulldiv(unsigned long long a,
                                                unsigned long long b); // 0x011e0970
extern "C" int __cdecl Snprintf16(wchar_t* buf, unsigned int count, const wchar_t* fmt, ...); // 0x00939a30
extern "C" int __cdecl Sprintf16(wchar_t* buf, const wchar_t* fmt, ...);                     // 0x009399c0
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
extern float   DAT_016ace10f;                               // 0x016ace10 pow constant
extern float   DAT_016ace20f;                               // 0x016ace20 pow exponent
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
class cSPUILayout_s00e3_6ff0 : public Object { public:
    IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
};
struct LimitStopwatch {
    uint8_t pad[0x1c];
    void SetTimeLimit(uint32_t ms, bool start);             // 0x0093a480
};
struct IAudioSystem {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual int  GetRecorderState();                        // +0x20
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
    virtual void v34();
    virtual void PlayRoutedSound(uint32_t id);              // +0x38
    virtual void v3c();
    virtual void SetSoundParam(uint32_t id, int value);     // +0x40
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
    virtual void v54();
    virtual void StopAllSounds();                           // +0x58
};
IAudioSystem* SP_GetAudioSystemAT();                        // 0x00a206f0 (EA::Audio::GetSystemAT)
struct VisNode {
    void SetVisibleRecursive(char on);                      // 0x00e46020
};
struct Timeline {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    void FUN_00e46d80(Vector2 a, int b, Vector2 d, bool f);  // 0x00e46d80
};
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
struct cCameraManager {
    void* ActiveControllerIndex();                          // 0x0098f940
};
extern Vector2 gVacc90;                                     // 0x016acc90
struct cString {
    uint8_t data[0x14];
    cString(uint32_t ns, uint32_t id, const wchar_t* s);     // 0x006b5770
    const wchar_t* GetText();                                // 0x006b55c0
    ~cString();                                              // 0x006b5240
};
static inline int ClampLoHi(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}
struct VecContainer { bool IsMember(int id); };             // 0x00e45fe0
struct cSPUITimeline {
    void*         mvpVtbl;                                    // +0x00
    uint32_t      mEmbedded[0x0b];                            // +0x04 embedded window subobject
    cSPUILayout_s00e3_6ff0*  mpLayout;                                   // +0x30
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
struct Controller {
    uint32_t pad00[0x39];                                     // +0x00 .. +0xe3
    uint32_t mModeE4;                                         // +0xe4
};
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
static float cSPUITimeline_GetScreenWidth();
static float cSPUITimeline_GetScreenWidth()
{
    int* p = (int*)SP_WindowManager();
    p = (int*)((int (__thiscall*)(int*))(*(void**)(*p + 4)))(p);
    float* r = (float*)((float* (__thiscall*)(int*))(*(void**)(*p + 0x38)))(p);
    return r[2] - r[0];
}
// ---- items of slice s00e36ff0 end

// ---- items of slice s00e37f90 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool gbCardInitialised;                   // 0x016acc58
extern bool gbBackgroundLayoutSeeded;            // 0x016acc5c
extern const float gkfIdleDelay;                 // 0x015a5890
#define nullptr 0
struct Vector2_s00e3_7f90 {
    float x;
    float y;
};
struct Vec4 {
    float x;
    float y;
    float z;
    float w;
};
struct Key_s00e3_7f90 {
    uint32_t m_nGroup;
    uint32_t m_nType;
    uint32_t m_nInstance;
};
namespace EA {
class Stopwatch_s00e3_7f90 {
public:
    Stopwatch_s00e3_7f90() {}
    Stopwatch_s00e3_7f90(int32_t nSource, bool bStart);     // 0x0093a560
    void Restart();                              // 0x00571e80

    int64_t m_nStart;                            // +0x00
    int64_t m_nStop;                             // +0x08
    int32_t m_nSource;                           // +0x10
    float m_fRate;                               // +0x14
};
}
class IWindow_s00e3_7f90 {
public:
virtual void T00();
virtual void T04();
virtual void T08();
virtual void T0c();
virtual void T10();
virtual void T14();
virtual void T18();
    virtual void SetContent1c(void* pItem, void* pData, uint32_t a, uint32_t b);  // +0x1c
    virtual void Reset20();                      // +0x20
    virtual void T24();
    virtual void SetFlag28(bool bFlag);          // +0x28
    virtual void T2c();
    virtual void SetFlag30(bool a, bool b);      // +0x30
    virtual RectF* GetRect34();                  // +0x34
    virtual RectF* GetRect38();                  // +0x38
virtual void T3c();
virtual void T40();
virtual void T44();
virtual void T48();
virtual void T4c();
virtual void T50();
virtual void T54();
virtual void T58();
    virtual void T5c();
    virtual void SetRect60(const RectF* pRect);  // +0x60
    virtual void SetPos64(float fX, float fY);   // +0x64
    virtual void SetSize68(float fWidth, float fHeight);          // +0x68
virtual void T6c();
virtual void T70();
virtual void T74();
virtual void T78();
    virtual void SetFlags7c(bool a, bool b);     // +0x7c
};
class cSPUILayout_s00e3_7f90 {
public:
virtual void L00();
virtual void L04();
virtual void L08();
    void* FindWindowByID(uint32_t nId, bool bFlag);            // 0x008105b0
};
struct AnimRaw {
    float m_fa;
    float m_fb;
    float m_fc;
    float m_fd;
    float m_fe;
};
class cSPUIAnimator_s00e3_7f90 {
public:
    void AddAnimation(void* pAnim, void* pRef, int32_t nFlag);   // 0x007f8d10
};
class cAutoRef {
public:
    void* m_pObject;                             // +0x00
};
class cTrackNode {
public:
    Vector2_s00e3_7f90* LookupKey(Vector2_s00e3_7f90* pKey);           // 0x00e470a0

    uint8_t mPad000[0xf0];                       // +0x000
    uint32_t m_nKeyCount;                        // +0x0f0
};
class cSporepediaCardData {
public:
    virtual void D00();                          // +0x00
    virtual void Get(void* pOut);                // +0x04
    virtual void Release();                      // +0x08
    void* Construct();                           // 0x00642100
};
class cSporepediaCardView {
public:
    void* Construct();                           // 0x00657f70
};
float __cdecl SPUIHelpers_GetElapsedSeconds(float fTime, int32_t nMode,
                                            IWindow_s00e3_7f90* pWindow, int32_t nFlag);
void* __stdcall SPUICreateWindowAnimationTargetPosition(
    Vector2_s00e3_7f90* pOut, IWindow_s00e3_7f90* pWindow, const Vector2_s00e3_7f90* pOffset, float fTime,
    float fDelay);                               // 0x007f80d0
AnimRaw* __stdcall SPUICreateWindowAnimationRotation(
    AnimRaw* pOut, IWindow_s00e3_7f90* pWindow, float fA, float fB, float fC, float fD,
    float fE);                                   // 0x007f8140
Vec4* __cdecl SPUIHelpers_GetMainWindowArea(Vec4* pOut);               // 0x00805ea0
void __stdcall SetWindowImage(void* pImage, const Key_s00e3_7f90* pKey,
                              int32_t nFlag);   // 0x00807bb0
bool __cdecl IsWorldLayoutFlagSet(int32_t nFlag);                      // 0x00685520
void* __cdecl FUN_00401010();                    // 0x00401010
void* __cdecl FUN_00401090();                    // 0x00401090
void* __cdecl FUN_004df400();                    // 0x004df400
bool __cdecl ResourceKeyNotEqual(const Key_s00e3_7f90* pKey, const Key_s00e3_7f90* pOther);  // 0x005f78f0
void __stdcall FUN_006428c0(void* pData);        // 0x006428c0
void __stdcall AssignCardView(cAutoRef* pRef, void* pView);            // 0x00b5f950
class cPropertyList {
public:
    bool GetDescription(uint32_t nKey);          // 0x006a25a0
};
void* __stdcall operator_new(uint32_t nSize, const char* pType,
                             uint32_t a, uint32_t b, uint32_t c,
                             uint32_t d);        // 0x00f473a0
extern cPropertyList* gspAppProperties;          // 0x015fd918
extern Key_s00e3_7f90 gKeyCardData;                         // 0x016acc4c
class Timeline_s00e3_7f90 {
public:
    Vector2_s00e3_7f90 GetKeyPair(uint32_t nX, int32_t nOffset);           // 0x00e37f90
    bool ClipTracks(Vector2_s00e3_7f90* pFirst, Vector2_s00e3_7f90* pSecond, Vector2_s00e3_7f90* pThird,
                    Vector2_s00e3_7f90* pFourth, bool bFlip);              // 0x00e38020
    bool StepBack();                                            // 0x00e38bb0
    bool Step();                                                // 0x00e38c90
    void PlayIconAnimation();                                   // 0x00e389e0

    cTrackNode* FindNode(uint32_t nX, int32_t nOffset);         // 0x00e37e50

    uint8_t mPad000[0x3c];                       // +0x000
    IWindow_s00e3_7f90* m_pHolder;                          // +0x03c
    uint8_t mPad040[0x144];                      // +0x040
    cTrackNode** m_apNodes;                      // +0x184
    uint8_t mPad188[0x1c0];                      // +0x188
    cSPUILayout_s00e3_7f90* m_pLayout;                      // +0x348
    uint8_t mPad34c[0x28];                       // +0x34c
    IWindow_s00e3_7f90* m_apTracks[39];                     // +0x374
    float m_fDelay410;                           // +0x410
    uint8_t mPad414[0x24];                       // +0x414
    EA::Stopwatch_s00e3_7f90 m_sw438;                       // +0x438
    float m_f450;                                // +0x450
    uint8_t mPad454[0x4];                        // +0x454
    cSPUIAnimator_s00e3_7f90* m_pAnimator;                  // +0x458
    uint8_t mPad45c[0x2c];                       // +0x45c
    uint32_t m_nTrackCount;                      // +0x488
    uint8_t mPad48c[0x4];                        // +0x48c
    uint32_t m_nIndex;                           // +0x490
    uint8_t mPad494[0x8];                        // +0x494
    bool m_bLast;                                // +0x49c
};
class TimelineCards {
public:
    void UpdateCard();                           // 0x00e38240
    void Layout();                               // 0x00e38450
    void AnimateIcon();                          // 0x00e389e0

    cSPUILayout_s00e3_7f90* m_pLayout;                      // +0x348
    cSPUILayout_s00e3_7f90* m_pOverlayLayout;               // +0x34c
    IWindow_s00e3_7f90* m_apTracks[10];                     // +0x374
    void* m_apImages[10];                        // +0x39c
    cAutoRef m_cardData;                         // +0x3c4
    cAutoRef m_apCardViews[10];                  // +0x3c8
    EA::Stopwatch_s00e3_7f90 m_sw3f8;                       // +0x3f8
    float m_fDelay410;                           // +0x410
    EA::Stopwatch_s00e3_7f90 m_sw418;                       // +0x418
    EA::Stopwatch_s00e3_7f90 m_sw438;                       // +0x438
    float m_f450;                                // +0x450
    cSPUIAnimator_s00e3_7f90* m_pAnimator;                  // +0x458
    uint8_t mPad45c[0x2c];                       // +0x45c
    uint32_t m_nTrackCount;                      // +0x488
    uint32_t m_nIndex;                           // +0x490
    float m_fScroll;                             // +0x494
    float m_fCell;                               // +0x498
};
__declspec(noinline) void Timeline_s00e3_7f90::PlayIconAnimation()
{
    ((TimelineCards*)this)->AnimateIcon();
}
// ---- items of slice s00e37f90 end

// ---- items of slice s00e38ce0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;
typedef          int   s32;
typedef unsigned long long u64_s00e3_8ce0;
struct cSPUILayout_s00e3_8ce0;
struct cSPUIAnimator_s00e3_8ce0;
struct AnimRaw_s00e3_8ce0;
struct AssetDir;
struct Pool;
cSPUILayout_s00e3_8ce0* __cdecl FUN_0067de90_s00e3_8ce0();          // 0x0067de90 - active layout
void*        __cdecl FUN_0067cb30();          // 0x0067cb30
void*        __cdecl SP_GetCurrentGameMode_s00e3_8ce0(); // 0x00b5b800
void*        __cdecl SP_GameTimeManager();    // 0x00b3d380
void*        __cdecl SPUIHelpers_GetMainWindowArea(void* out); // 0x00805ea0
float        __cdecl SPUIHelpers_GetElapsedSeconds(float a, s32 b, void* c, s32 d); // 0x00805080
float        __cdecl RandomFloatRange(float lo, float hi);     // 0x00572a10
AnimRaw_s00e3_8ce0*     __cdecl SPUICreateWindowAnimationTargetPosition(AnimRaw_s00e3_8ce0* buf, void* wnd,
                                                             float a, float b, float c,
                                                             float d, s32 e); // 0x007f80d0
void         __cdecl FUN_00571e80(void* stopwatch);            // 0x00571e80
s32   __cdecl Time_Current();        // 0x00e5c520
float __cdecl Time_SourceLevel();    // 0x00e5c530
float __cdecl Time_TimelineForest(); // 0x00d386a0
float __cdecl Time_TimelineSpace();  // 0x00cdb8b0
struct Vec3 { float x, y, z; };
struct Vec4_s00e3_8ce0 { float x, y, z, w; };
struct AnimRaw_s00e3_8ce0 { u32 w[0x1a]; };
struct Wnd {
  void* GetRect();                       // 0x38
  void  SetRect(float a, float b);       // 0x64
  void  SetText(const u16* s);           // 0x80
  bool  IsVisible();                     // 0x00810070
};
struct WndVt {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
  virtual void* GetRect();               // 0x38
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
  virtual void SetRect(float a, float b); // 0x64
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
  virtual void v30();
  virtual void SetVisible(s32 a, s32 b);  // 0x7c
  virtual void SetText(const u16* s);     // 0x80
};
struct cSPUILayout_s00e3_8ce0 {
  Wnd* FindWindowByID(u32 id, s32 flag); // 0x008105b0
};
struct cSPUIAnimator_s00e3_8ce0 {
  u8   RemoveAnimation(void* wnd, s32 id);            // 0x007f6210
  void AddAnimation(void* target, void* ref, s32 a);  // 0x007f8d10
};
struct Stopwatch { u8 pad[0x08]; };
struct IVec {
  u8    pad00[0x0c];
  u32*  data;                            // +0x0c
  void  resize(u32 n);                   // 0x007eb820
};
struct Pool {
  IVec* New(u32 size, u32 flags);        // 0x007ec160
};
struct AssetDir {
  u8 GetServerId(void* key, u64_s00e3_8ce0* out, u8 flag); // 0x0054e530
};
struct AssetOwner {
  u8        pad00[0x58];
  AssetDir* dir;                         // +0x58
};
struct GameTimeMgr {
  u64_s00e3_8ce0 GetTicks();                        // 0x00b316c0
};
struct Timeline_s00e3_8ce0 {
  u8          pad00[0x30];
  Wnd*        p30;                       // +0x030
  u8          pad34[0x348 - 0x34];
  cSPUILayout_s00e3_8ce0* p348;                     // +0x348
  cSPUILayout_s00e3_8ce0* p34c;                     // +0x34c
  u8          pad350[0x370 - 0x350];
  u8          b370;                      // +0x370
  u8          pad371[0x458 - 0x371];
  cSPUIAnimator_s00e3_8ce0* anim;                   // +0x458
  u8          pad45c[0x488 - 0x45c];
  u32         n488;                      // +0x488
  u8          pad48c[0x4a8 - 0x48c];
  Stopwatch   sw4a8;                     // +0x4a8
  float       f4c0;                      // +0x4c0
  u8          pad4c4[0x4e8 - 0x4c4];
  u8          b4e8;                      // +0x4e8
  u8          pad4e9[0x530 - 0x4e9];
  Stopwatch   sw530;                     // +0x530
};
struct CString {
  u8          mData[0x24];
  void        ctor();                    // 0x006b5060
  void        dtor();                    // 0x006b5240
  u8          Load(u32 id, u32 value, s32 a); // 0x006b54b0
  const u16*  GetText();                 // 0x006b55c0
};
struct Rand {
  u32 RandomUint32Uniform(u32 n);        // 0x00a68fb0
};
#define G_RAND          ((Rand*)0x01601760)
#define G_LAST_RANDOM   (*(u32*)0x016acc60)
static u32 NowMs(void)
{
  GameTimeMgr* m = (GameTimeMgr*)SP_GameTimeManager();
  u64_s00e3_8ce0 t = m->GetTicks();
  return (u32)(t / 1000);
}
// ---- items of slice s00e38ce0 end

// ---- items of slice s00e39ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_variantIntDefault;   // 0x015d9c68
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4
struct Variant {
    union {
        uint32_t  mData[4];
        uint32_t* mpData;      // payload when mFlags holds kFlagByReference (0x30)
    };
    uint16_t mFlags;           // +0x10
    uint16_t mTypeId;          // +0x12
};
class IPropertyList {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual bool GetProperty(uint32_t id, Variant** ppValue);   // +0x24
};
struct IntPropertyBinding {
    void*    mpVtbl;           // +0x00
    uint32_t mPropertyId;      // +0x04
    uint32_t mField08;         // +0x08
    int32_t  mValue;           // +0x0c
    bool SetValue(IPropertyList* pList);
};
struct ValueTriple {
    uint32_t m0, m1, m2;
};
struct ChangePayload {
    uint32_t     mReserved0;   // +0x00
    uint32_t     mReserved1;   // +0x04
    uint32_t     mValue;       // +0x08
    ValueTriple  mFirst;       // +0x0c
    ValueTriple  mSecond;      // +0x18
};
struct ChangeMessage {
    uint32_t        mId;        // +0x00
    uint32_t        mReserved[2];// +0x04
    ChangePayload*  mpPayload;  // +0x0c
};
struct KeyValue {
    uint32_t mKey0;            // +0x00   compared against triple component 1
    uint32_t mKey1;            // +0x04   compared against triple component 0
    uint32_t mKey2;            // +0x08   compared against triple component 2
    uint32_t mVal0;            // +0x0c   stored to component 1
    uint32_t mVal1;            // +0x10   stored to component 0
    uint32_t mVal2;            // +0x14   stored to component 2
    void ApplyTo(ChangeMessage* msg);
};
struct cSPUILayout_s00e3_9ab0 {
    bool  IsVisible();                              // 0x00810070
    void* FindWindowByID(uint32_t id, int flags);   // 0x008105b0
};
struct Image {
    virtual void AddRef();                          // +0x00
    virtual void Release();                         // +0x04
    virtual void v2();
    virtual void v3();
    virtual void v4();
    Image* Init();                                                  // 0x006775f0 (construct in place)
    void Setup(void* pWindow, int a, int b);                        // 0x00677220
    void SetFlags(int a, const int* pColors, int b);                // 0x00677700
    void BindA(void* pWindow, void* pVector, int index);            // 0x00677df0
    void BindB(void* pWindow, void* pVector, uint32_t key, int index); // 0x00677d90
};
void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
struct IEditorData {
    PV2 PV                         // slots 0..2
    virtual void* FindService(uint32_t id);         // slot 3  (+0x0c)
};
struct IImageOwner {
    PV4 PV                         // slots 0..4
    virtual void SetImage(void* pImage);           // slot 5  (+0x14)
};
struct IEditorHost {
    PV8 PV8 PV8 PV8 PV8 PV2        // slots 0..41
    virtual IEditorData* GetEditorData();          // slot 42 (+0xa8)
};
void* CreateImageFromResource2(void* pKey, void** ppImage, int a, int b, int c);   // 0x00806230
struct cCellRecord {
    uint8_t  mPad000[0xe4];
    uint32_t mTerrainKey;      // +0x0e4
    uint8_t  mPad0e8[0x08];
    uint32_t mTerrainKind;     // +0x0f0
};
struct cTerrainSphere {
    uint8_t  mPad0000[0x10fc];
    uint32_t mField10fc;       // +0x10fc
    uint32_t mField1100;       // +0x1100
    uint32_t mField1104;       // +0x1104
    uint32_t mField1108;       // +0x1108
    uint32_t GetTerrainIndex(uint32_t key);        // 0x00c756e0
};
struct cTerrainEditor {
    cTerrainSphere* GetCurrentTerrainSphere();     // 0x00f67d90
};
cTerrainEditor* NounManager();                     // 0x00b3d300
uint32_t FUN_00556440(uint32_t a, uint32_t b, uint32_t c, uint32_t d);   // 0x00556440
int32_t  TerrainKeyToIndex(uint32_t key);           // 0x00e36f50
void     FUN_00e39420(ChangeMessage* msg, int index, void* pOut);        // 0x00e39420
template<class T>
struct Vec {
    T*       mpBegin;          // +0x00
    T*       mpEnd;            // +0x04
    uint32_t mPad08[2];        // +0x08
    T*       mpCapacity;       // +0x10
};
struct RefPtrImage {
    Image* mpObject;           // +0x00
};
struct UIVec3 {
    uint32_t m0, m1, m2;
};
struct EA_ResourceKey {
    uint32_t mInstanceID;      // +0x00
    uint32_t mGroupID;         // +0x04
    uint32_t mTypeID;          // +0x08
};
struct SubObject24 {
    void*        mpVtbl;       // +0x00  (object +0x24)
    uint32_t     mField04;     // +0x04  (object +0x28)
    cSPUILayout_s00e3_9ab0* mpLayout;     // +0x08  (object +0x2c)
};
struct cBigEditorObject {
    void*        mpVtbl00;     // +0x000
    void*        mpVtbl04;     // +0x004
    void*        mpVtbl08;     // +0x008
    void*        mpVtbl0c;     // +0x00c
    uint8_t      mPad010[0x14];// +0x010
    SubObject24  mSub24;       // +0x024
    cSPUILayout_s00e3_9ab0* mpLayout30;   // +0x030
    uint8_t      mPad034[0x150];// +0x034
    Vec<cCellRecord*> mCells;  // +0x184
    Vec<RefPtrImage>  mImages; // +0x198
    uint8_t      mPad1ac[0x1c];// +0x1ac
    void*        mpRef1c8;     // +0x1c8
    void*        mpRef1cc;     // +0x1cc
    void*        mpRef1d0;     // +0x1d0
    void*        mpRef1d4;     // +0x1d4
    void*        mpRef1d8;     // +0x1d8
    EA_ResourceKey mTerrainKey;// +0x1dc
    uint8_t      mPad1e8[0xb4];// +0x1e8
    UIVec3       mVecs[5];     // +0x29c..0x2d7
    uint8_t      mPad2d8[0x30];// +0x2d8
    uint32_t     m308;         // +0x308
    uint32_t     m30c;         // +0x30c
    uint32_t     m310;         // +0x310
    uint32_t     m314;         // +0x314
    uint32_t     m318;         // +0x318
    uint32_t     m31c;         // +0x31c
    uint32_t     m320;         // +0x320
    uint32_t     m324;         // +0x324
    uint32_t     m328;         // +0x328
    int32_t      mGameMode;    // +0x32c
    uint8_t      mPad330[0x3c];// +0x330
    bool         mFlag36c;     // +0x36c

    int GetDrawPriority();
    void OnChange(uint32_t messageId, ChangeMessage* msg);
    Image* GetTerrainImage(uint32_t key, bool bRecompute);
    void RefreshTerrainImages();
};
// ---- items of slice s00e39ab0 end

// ---- items of slice s00e3a990 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define VSLOT(n) virtual void _v##n();
namespace EA {
class Stopwatch_s00e3_a990 {
public:
    uint8_t mnPad00[0x18];              // +0x00
    void Restart();                     // 0x00571e80
    float GetElapsedTimeFloat() const;  // 0x005ff1a0
};  // namespace EA
}
class cUIWindow {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void SetVisible(int32_t nState, int32_t nFlags); // +0x7c
};
class cSPUILayout_s00e3_a990 {
public:
    cUIWindow* FindWindowByID(uint32_t nId, int32_t nParam); // 0x008105b0
};
class cSPUIAnimator_s00e3_a990 {
public:
    void ClearAll();                    // 0x007f8f00
};
class cTimelinePlayItem {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    VSLOT(8) VSLOT(9) VSLOT(10) VSLOT(11) VSLOT(12) VSLOT(13) VSLOT(14)
    VSLOT(15) VSLOT(16) VSLOT(17) VSLOT(18) VSLOT(19) VSLOT(20) VSLOT(21)
    VSLOT(22) VSLOT(23) VSLOT(24) VSLOT(25) VSLOT(26) VSLOT(27) VSLOT(28)
    VSLOT(29) VSLOT(30)
    virtual void SetVisible(int32_t nState, int32_t nFlags); // +0x7c
};
class cTimelineTrack;
bool IsTimelineWindowReady();           // 0x00e36e80
bool IsTimelinePlaybackDone();          // 0x00e36e20
class cSPUITimeline_s00e3_a990 {
public:
    VSLOT(0) VSLOT(1) VSLOT(2) VSLOT(3) VSLOT(4) VSLOT(5) VSLOT(6) VSLOT(7)
    uint8_t mnPad04[0x30];              // +0x004
    void* mpSourceLayout;               // +0x034
    uint8_t mnPad38[4];                 // +0x038
    void* mpSelectedTrack;              // +0x03c
    uint8_t mnPad40[0xa8];              // +0x040
    void* mpTracksSentinel;             // +0x0e8
    cTimelineTrack* mpTracksRoot;       // +0x0ec
    uint8_t mnPadF0[0x1a8];             // +0x0f0
    uint32_t mnCachedPaletteId;         // +0x298
    uint8_t mnPad29c[0xac];             // +0x29c
    cSPUILayout_s00e3_a990* mpLeftLayout;          // +0x348
    cSPUILayout_s00e3_a990* mpRightLayout;         // +0x34c
    uint8_t mnPad350[0x24];             // +0x350
    cTimelinePlayItem* mPlayItems[31];  // +0x374
    uint32_t mnMode;                    // +0x3f0
    uint8_t mnPad3f4[0x64];             // +0x3f4
    cSPUIAnimator_s00e3_a990* mpAnimator;          // +0x458
    void* mpClip;                       // +0x45c
    uint8_t mnPad460[0x28];             // +0x460
    uint32_t mnPlayItemCount;           // +0x488
    uint8_t mnPad48c[4];                // +0x48c
    uint32_t mnPlayIndex;               // +0x490
    uint8_t mnPad494[0x0c];             // +0x494
    uint32_t mnState;                   // +0x4a0
    uint8_t mnPad4a4[0x24];             // +0x4a4
    EA::Stopwatch_s00e3_a990 mStopwatch;           // +0x4c8
    float mFadeDelay;                   // +0x4e0
    float mFadeTime;                    // +0x4e4
    bool mbFadeActive;                  // +0x4e8
    uint8_t mnPad4e9[7];                // +0x4e9
    uint32_t mnTimerStartLow;           // +0x4f0
    uint32_t mnTimerStartHigh;          // +0x4f4
    uint32_t mnTimerEndLow;             // +0x4f8
    uint32_t mnTimerEndHigh;            // +0x4fc
    uint32_t mnTimerMode;               // +0x500
    uint8_t mnPad504[4];                // +0x504
    bool mbTimerReset;                  // +0x508
    uint8_t mnPad509[7];                // +0x509
    uint32_t mnExtraStartLow;           // +0x510
    uint32_t mnExtraStartHigh;          // +0x514
    uint32_t mnExtraEndLow;             // +0x518
    uint32_t mnExtraEndHigh;            // +0x51c
    uint32_t mnExtraMode;               // +0x520
    uint8_t mnPad524[4];                // +0x524
    bool mbExtraReset;                  // +0x528

    // out-of-slice members
    void UpdateTransition(float fTime);                 // 0x00e3abf0
    void UpdatePlayback();                              // 0x00e389e0
    void ResetClip();                                   // 0x00e38450
    void FinishTransition();                            // 0x00e38fd0
    void SetRunning(int32_t nRunning);                  // 0x00e39300
    void InitGonzagoSubsystem(int32_t nFlag);           // 0x00e39350
    void PlayClip(void* pClip);                         // 0x00e38ce0

    cTimelineTrack* FindNextTrack(uint32_t nFlags, float* pProgress);
    cTimelineTrack* FindPreviousTrack(uint32_t nFlags, float* pProgress);
    bool ShowNextPlayItem();  // 0x00e3b0b0 (cSPUITimeline::ShowNextPlayItem)
    void StartPlayback();
    void RestorePlayback();  // 0x00e3b180 (cSPUITimeline::RestorePlayback)
    void HidePanels();
    void ShowPanels();
    bool LoadImage(cUIWindow* pWindow, void* pResource);
    bool HandleMessage(void* pMessage);
    uint32_t GetSelectedPaletteId();
    void UpdateState();  // 0x00e3afb0 (cSPUITimeline::UpdateState)
};
class cTimelineTrack {
public:
    bool IsEnabled();                   // vtable +0x28
    float* GetRange();                  // vtable +0x38
    float* GetTime(void* pOut, void* pParam, int32_t nExtra); // vtable +0xc4
};
// ---- items of slice s00e3a990 end

// ---- items of slice s00e3b9e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned int  g_16acc84;                          // 0x016acc84  one-time-init bitmask
extern "C" float         g_16acc7c, g_16acc80;               // 0x016acc7c
extern "C" float         g_16acc74, g_16acc78;               // 0x016acc74
extern "C" float         g_16acc6c, g_16acc70;               // 0x016acc6c
extern "C" float         g_16acc64, g_16acc68;               // 0x016acc64
extern "C" unsigned int  DAT_016acd90, DAT_016acda0, DAT_016acdb0, DAT_016acdc0, DAT_016acdd0;
extern "C" int           DAT_016acf2c;                       // 0x016acf2c
extern "C" float         DAT_016acecc;                       // 0x016acecc
extern "C" float         DAT_016acde0;                       // 0x016acde0
extern "C" float         DAT_016acf0c;                       // 0x016acf0c
extern "C" float         DAT_015a5890;                       // 0x015a5890
extern "C" unsigned int  g_15a5984[12];                      // 0x015a5984..0x015a59b3 (mode colours)
extern "C" unsigned int  PTR_PTR_015a59b4;                   // 0x015a59b4
extern "C" unsigned int  DAT_013eb844;                       // 0x013eb844  vtable
struct U3 { u32 x, y, z; };                                 // 12-byte uint triple (by value)
struct V3 { float x, y, z; };                               // 12-byte float triple (by value)
struct cSPHintMgr                                          // object returned by the argless getter
{
    void FUN_0067aaf0(U3 col, void* p, int a, V3 v, int b, int c);  // 0x0067aaf0 (__thiscall, ret 0x28)
};
int   SP_GetCurrentGameMode_s00e3_b9e0();                              // 0x00b5b800
void* FUN_0067caf0();                                       // 0x0067caf0 (argless getter; args belong to FUN_0067aaf0)
void  FUN_00677360(int);                                    // 0x00677360
void* FUN_00e3a730(unsigned int, int);                      // 0x00e3a730
int   FUN_00e36f50(unsigned int);                           // 0x00e36f50
float* FUN_00e3a000(void*, Vector2*, Vector2*, Vector2*, Vector2*, float); // 0x00e3a000
float* FUN_00e3a570(void*, float, float, Vector2*, float, Vector2*, float, float); // 0x00e3a570
void* SP_MessageServer();                                   // 0x0067dcc0
void* FUN_0067de90();                                       // 0x0067de90
void  SP_cTelemetry_Reset(void*);                           // 0x007ebb60
void  eastl_rbtree_DoNukeSubtree(unsigned int);             // 0x009a9600
void  FUN_00e37840(unsigned int, ...);                      // 0x00e37840
void  SlotMessage_Destruct(void*);                          // 0x00421cf0
#define MEM(T, o) (*(T*)((char*)this + (o)))
struct cUIManager
{
    int   FUN_00e3b5d0();   // @0x00e3b5d0 helper (defined in the binary; declaration only here)
    void  FUN_00e3b9e0(int dt);
    void  FUN_00e3be20(unsigned int p2, float a, float b, float c, float d, float e,
                       float f, float g, float h, float i, char p8);
    void  FUN_00e3c000();
    float FUN_00e3c100(float x);
    char  FUN_00e3c1a0(unsigned int* p2, float* p3, unsigned int* p4, float* p5,
                       unsigned int p6, unsigned int p7, char p8, float p9);
    char  FUN_00e38020(Vector2* a, Vector2* b, Vector2* c, Vector2* d, int flag);  // 0x00e38020 (__thiscall Timeline::ClipTracks)
};
// ---- items of slice s00e3b9e0 end

// ---- items of slice s00e40700 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* EA_Alloc(uint32_t size, const char* tag, int a, int b, int c, int d);
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* count);
extern "C" const char g_key_timeline[];               // DAT_015a59b8
extern "C" const char g_key_atlased[];                // DAT_015a59c4
extern "C" int* g_appProperties;                      // _sAppProperties
struct Object_s00e4_0700 {
    virtual int  AddRef();                 // +0x00
    virtual int  Release();                // +0x04
    virtual void scalarDeletingDtor();     // +0x08
};
struct Rect_s00e4_0700  { float x, y, z, w; };
struct Point_s00e4_0700 { float x, y; };
struct IWindow_s00e4_0700 : Object_s00e4_0700 {
    virtual void pad0c();                              // +0x0c
    virtual IWindow_s00e4_0700* GetParent();                      // +0x10
    virtual void pad14();                              // +0x14
    virtual void pad18();                              // +0x18
    virtual void pad1c();                              // +0x1c
    virtual void pad20();                              // +0x20
    virtual void pad24();                              // +0x24
    virtual void pad28();                              // +0x28
    virtual void pad2c();                              // +0x2c
    virtual void pad30();                              // +0x30
    virtual const Rect_s00e4_0700* GetArea();                     // +0x34
    virtual const Rect_s00e4_0700* GetRealArea();                 // +0x38
    virtual void pad3c();                              // +0x3c
    virtual void pad40();                              // +0x40
    virtual void pad44();                              // +0x44
    virtual void pad48();                              // +0x48
    virtual void pad4c();                              // +0x4c
    virtual void pad50();                              // +0x50
    virtual void pad54();                              // +0x54
    virtual void pad58();                              // +0x58
    virtual void SetShadeColor(uint32_t c);            // +0x5c
    virtual void pad60();                              // +0x60
    virtual void pad64();                              // +0x64
    virtual void pad68();                              // +0x68
    virtual void SetLayoutArea(const Rect_s00e4_0700& r);         // +0x6c
    virtual void SetLayoutLocation(float x, float y);  // +0x70
    virtual void pad74();                              // +0x74
    virtual void pad78();                              // +0x78
    virtual void pad7c();                              // +0x7c
    virtual void pad80();                              // +0x80
    virtual void pad84();                              // +0x84
    virtual void pad88();                              // +0x88
    virtual void pad8c();                              // +0x8c
    virtual void pad90();                              // +0x90
    virtual void pad94();                              // +0x94
    virtual void pad98();                              // +0x98
    virtual void pad9c();                              // +0x9c
    virtual void padA0();                              // +0xa0
    virtual void padA4();                              // +0xa4
    virtual void padA8();                              // +0xa8
    virtual void padAc();                              // +0xac
    virtual void padB0();                              // +0xb0
    virtual void padB4();                              // +0xb4
    virtual void padB8();                              // +0xb8
    virtual void padBc();                              // +0xbc
    virtual Point_s00e4_0700 ToGlobalCoordinates(Point_s00e4_0700 p);         // +0xc0
    virtual void padC4();                              // +0xc4
    virtual void padC8();                              // +0xc8
    virtual void padCc();                              // +0xcc
    virtual void padD0();                              // +0xd0
    virtual void padD4();                              // +0xd4
    virtual void AddWindow(IWindow_s00e4_0700* w);                // +0xd8
    virtual void RemoveWindow(IWindow_s00e4_0700* w);             // +0xdc
};
class cSPUILayout_s00e4_0700 : public Object_s00e4_0700 { public:
    IWindow_s00e4_0700* FindWindowByID(uint32_t id, bool recursive);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void     Init(const void* key, int a, uint32_t b);  // 0x008120d0 (cSPUILayout::Init)
    void     SetVisibility(int visible);  // 0x00810590 (cSPUILayout::SetVisibility)
};
struct RefVec { Object_s00e4_0700** begin; Object_s00e4_0700** end; Object_s00e4_0700** cap; };
static void* EANew(uint32_t size, const char* tag) {
    return EA_Alloc(size, tag, 0, 0, 0, 0);
}
template <class T>
static void Assign(T*& slot, T* p) {
    if (slot != p) {
        if (p)    p->AddRef();
        T* old = slot;
        slot = p;
        if (old)  old->Release();
    }
}
static void RefVecPush(RefVec* v, Object_s00e4_0700* p) {
    if (p) p->AddRef();
    if (v->end < v->cap) { *v->end++ = p; return; }
    uint32_t n = (uint32_t)(v->end - v->begin);
    uint32_t newCap = n ? n * 2 : 1;
    Object_s00e4_0700** ncap = (Object_s00e4_0700**)EANew(newCap * sizeof(Object_s00e4_0700*), "eastl vector");
    for (uint32_t i = 0; i < n; ++i) ncap[i] = v->begin[i];
    v->begin = ncap;
    v->end = ncap + n;
    v->cap = ncap + newCap;
    *v->end++ = p;
}
void     FUN_00ddddf0(uint32_t a, int b);
void     FUN_00e3f010();
uint32_t SP_ColorRGBAToU32(const void* color);        // SP::ColorRGBAToU32
void*    SP_GetPropertyAsKeyArray();                  // SP::GetPropertyAsKeyArray
float*   SPUI_GetMainWindowArea(float* out);          // SPUIHelpers::GetMainWindowArea
void*    SPUI_CenterWindowInRect(void* mem);          // ctor used for cSPUILayout
Object_s00e4_0700*  sGetWindowImage(IWindow_s00e4_0700* w);                 // anonymous-namespace helper
void*    cSPUIAnimator_ctor(void* mem);               // cSPUIAnimator::cSPUIAnimator
Object_s00e4_0700** MapFindByHash(uint32_t hash);                // FUN_00e3ec20
Object_s00e4_0700** MapFindByRef(Object_s00e4_0700* obj);                   // FUN_00ceb2b0
uint32_t* MapFindIndex(uint32_t key);                 // FUN_00de7630
void     CopyRange(int* first, int* last);            // eastl copy do_copy
struct AppPropertyList {
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual void pad7();
virtual void pad8();
    virtual bool GetProperty(uint32_t id, void* out); // +0x24
};
struct TimelineView {
virtual void Setup();
static void Dummy();

    char pad00[0x24];
    Object_s00e4_0700*       mAnimatorA;         // +0x24
    cSPUILayout_s00e4_0700*  mLayout;            // +0x28
    cSPUILayout_s00e4_0700*  mAtlasedLayout;     // +0x2c
    IWindow_s00e4_0700*      mWin30;             // +0x30
    IWindow_s00e4_0700*      mWin34;             // +0x34
    IWindow_s00e4_0700*      mWin38;             // +0x38
    IWindow_s00e4_0700*      mWin3c;             // +0x3c
    IWindow_s00e4_0700*      mWin40;             // +0x40
    IWindow_s00e4_0700*      mWin44;             // +0x44
    IWindow_s00e4_0700*      mWin48;             // +0x48
    IWindow_s00e4_0700*      mWin4c;             // +0x4c
    IWindow_s00e4_0700*      mWin50;             // +0x50
    IWindow_s00e4_0700*      mWin54;             // +0x54
    IWindow_s00e4_0700*      mWin58;             // +0x58
    char pad5c[0x10];
    Object_s00e4_0700*       mImage6c;           // +0x6c
    float mF70, mF74, mF78, mF7c;     // +0x70
    float mF80, mF84, mF88, mF8c, mF90, mF94; // +0x80
    char pad98[0x10];
    uint32_t mTimeLo, mTimeHi;        // +0xa8
    uint32_t mB0, mB4;                // +0xb0
    uint32_t mMode;                   // +0xb8
    char padbc[0xb0];                 // ..+0x16c
    RefVec   mPropVec;                // +0x16c
    char pad174[0x50];                // ..+0x1c4
    Object_s00e4_0700*  mPaletteItem;            // +0x1c4
    Object_s00e4_0700*  mPaletteInfo;            // +0x1c8
    Object_s00e4_0700*  mPaletteRollover;        // +0x1cc
    Object_s00e4_0700*  mEventRollover;          // +0x1d0
    char pad1d4[0x0c];
    char     mColor1e0[0x20];         // +0x1e0
    char     mColor200[0x20];         // +0x200
    char     mColor220[0x20];         // +0x220
    char pad240[0xec];                // ..+0x32c
    void*    mMsgServer;              // +0x32c
    void*    mMsgHandler;             // +0x330
    const uint32_t* mMsgIDs;          // +0x334
    uint32_t mMsgCount;               // +0x338
    uint32_t mMsgState;               // +0x33c
    cSPUILayout_s00e4_0700* mTransitionLayout;   // +0x340
    cSPUILayout_s00e4_0700* mTransitionLayout2;  // +0x344
    char pad348[0x24];
    IWindow_s00e4_0700* mWin36C[10];             // +0x36c
    IWindow_s00e4_0700* mWin394[10];             // +0x394
    char pad3bc[4];
    IWindow_s00e4_0700* mWin3C0[10];             // +0x3c0
    char pad3e8[0x68];
    Object_s00e4_0700*  mAnimatorB;              // +0x450
    char pad454[4];
    RefVec   mVec458;                 // +0x458
    char pad460[0xc];
    RefVec   mVec46c;                 // +0x46c
    char pad474[0xc];
    uint32_t mTileCount;              // +0x480
    bool     mFlag484;                // +0x484

    void SetupIconStrip();
    void SetupColorWindows();
    void SetupIconPairs();
    void SetupPalette();
    void SetupTrackRows();
    void RegisterMessages();
};
void TimelineView::Dummy() {}
void TimelineView::SetupIconStrip() {
    IWindow_s00e4_0700* a = mLayout->FindWindowByID(0x61388da, true);
    IWindow_s00e4_0700* b = mLayout->FindWindowByID(0x61388db, true);
    if (!a || !b) return;

    IWindow_s00e4_0700* parent = a->GetParent();
    if (!parent) return;
    int ph = (int)(parent->GetRealArea()->w - parent->GetRealArea()->y);

    const Rect_s00e4_0700* ar = a->GetRealArea();
    float ay0 = (float)ph * 0.33333334f - (ar->w - ar->y) * 0.5f;
    Rect_s00e4_0700 ao = { ar->x, ay0, ar->z, ay0 + (ar->w - ar->y) };
    a->SetLayoutArea(ao);

    const Rect_s00e4_0700* br = b->GetRealArea();
    float by0 = (float)ph * 0.6666667f - (br->w - br->y) * 0.5f;
    Rect_s00e4_0700 bo = { br->x, by0, br->z, by0 + (br->w - br->y) };
    b->SetLayoutArea(bo);
}
void TimelineView::SetupColorWindows() {
    IWindow_s00e4_0700* a = mLayout->FindWindowByID(0xf537d890, true);
    IWindow_s00e4_0700* b = mLayout->FindWindowByID(0xf537d891, true);
    IWindow_s00e4_0700* c = mLayout->FindWindowByID(0xf537d892, true);
    if (!a || !b || !c) return;

    const Rect_s00e4_0700* ar = a->GetRealArea();
    Rect_s00e4_0700 ao = { ar->x, ar->y, ar->z, (ar->w + ar->y) * 0.5f };
    a->SetLayoutArea(ao);
    a->SetShadeColor(SP_ColorRGBAToU32(mColor1e0));

    const Rect_s00e4_0700* br = b->GetRealArea();
    Rect_s00e4_0700 bo = { br->x, br->y, br->z, (br->w + br->y) * 0.5f };
    b->SetLayoutArea(bo);
    b->SetShadeColor(SP_ColorRGBAToU32(mColor200));

    const Rect_s00e4_0700* cr = c->GetRealArea();
    Rect_s00e4_0700 co = { cr->x, cr->y, cr->z, cr->w };
    c->SetLayoutArea(co);
    c->SetShadeColor(SP_ColorRGBAToU32(mColor220));
}
// ---- items of slice s00e40700 end

// ---- items of slice s00e42100 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma warning(disable : 4100)
#pragma warning(disable : 4244)
typedef unsigned __int64 u64;
class IRangeObj {
public:
virtual void   r00();
virtual void r04();
virtual void r08();
virtual void r0C();
virtual void   r10();
virtual void r14();
virtual void r18();
virtual void r1C();
virtual void   r20();
virtual void r24();
virtual void r28();
virtual void r2C();
virtual void   r30();
virtual void r34();
virtual float* r38();
virtual void   r3C();
virtual void r40();
virtual void r44();
virtual void r48();
virtual void r4C();
virtual void   r50();
virtual void r54();
virtual void r58();
virtual void r5C();
    virtual void   r60(void* buf);
virtual void   r64();
virtual void r68();
    virtual void   r6C(void* buf);
virtual void   r70();
virtual void r74();
virtual void r78();
    virtual void   r7C(u32 mode, bool flag);
};
class CKeyMap {
public:
    IRangeObj** Find(u32* key);     // 0x00e3ec20
    u32         m00;                // +0x0
};
struct Sub184 {
    u8          pad00[0x1c];
    IRangeObj*  m1c;                // +0x1c
    u8          pad20[0xe4 - 0x20];
    u32         mE4;                // +0xe4
    u8          padE8[0xf0 - 0xe8];
    u32         mF0;                // +0xf0
};
struct Holder184 {
    Sub184* m00;                    // +0x0
};
class cRangePanel {
public:
    void Update();                                  // 0x00e42100

    void Refresh();                                 // 0x00e3f970
    u64  Step(void* p);                             // 0x00e36ff0
    void Apply(u32 lo, u32 hi);                     // 0x00e372b0

    u8          pad000[0x3c];
    IRangeObj*  mpSource3c;                         // +0x3c
    IRangeObj*  mpTarget40;                         // +0x40
    u8          pad044[0x58 - 0x44];
    IRangeObj*  mpSlider58;                         // +0x58
    u8          pad05c[0x60 - 0x5c];
    IRangeObj*  mpRange60;                          // +0x60
    u8          pad064[0xa8 - 0x64];
    void*       mpStepArg;                          // +0xa8
    u8          pad0ac[0xc8 - 0xac];
    CKeyMap     mKeyMap;                            // +0xc8
    u8          pad0cc[0x184 - 0xcc];
    Holder184*  mpHolder184;                        // +0x184
    Sub184**    mppOwner188;                        // +0x188
    u8          pad18c[0x270 - 0x18c];
    float       m270;                               // +0x270
    float       m274;                               // +0x274
    float       m278;                               // +0x278
};
extern u8*  GetCurrentGameMode();       // 0x00b5b800
extern u8   g_1654c05;                  // 0x01654c05  "no game mode" sentinel
// ---- items of slice s00e42100 end

// ---- items of slice s00e423a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float    gColorAlpha_016acf1c;
extern int      gTimelineMaxTime_016acf2c;
extern float    gScrollMargin_016acf3c;
extern int      gShowDelayMs_016acf4c;
extern float    gAnimTime_016ace00;
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
struct Point_s00e4_23a0 {
    float x, y;
    Point_s00e4_23a0() {}
    Point_s00e4_23a0(float a, float b) : x(a), y(b) {}
};
struct Rect_s00e4_23a0 {
    float x1, y1, x2, y2;
    Rect_s00e4_23a0() {}
};
inline float Width(const Rect_s00e4_23a0& r) { return r.x2 - r.x1; }
struct ColorRGB { float r, g, b; };
struct ColorRGBA {
    float r, g, b, a;
    ColorRGBA() {}
    ColorRGBA(const ColorRGB& c, float alpha) : r(c.r), g(c.g), b(c.b), a(alpha) {}
    ColorRGBA(float r_, float g_, float b_, float a_) : r(r_), g(g_), b(b_), a(a_) {}
};
uint32_t ColorRGBAToU32(const ColorRGBA& c);    // SP::ColorRGBAToU32 0x004580c0
struct Object_s00e4_23a0 {
    virtual int AddRef();
    virtual int Release();
};
struct IWindow_s00e4_23a0 : Object_s00e4_23a0 {
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
virtual void v20();
virtual void v24();
    virtual uint32_t GetFlags();                         // +0x28
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual const Rect_s00e4_23a0& GetRealArea();                   // +0x38
virtual void v3c();
virtual void v40();
virtual void v44();
virtual void v48();
virtual void v4c();
virtual void v50();
virtual void v54();
virtual void v58();
    virtual void SetShadeColor(uint32_t c);              // +0x5c
virtual void v60();
virtual void v64();
virtual void v68();
    virtual void SetLayoutArea(const Rect_s00e4_23a0& r);           // +0x6c
virtual void v70();
virtual void v74();
virtual void v78();
    virtual void SetFlag(uint32_t flag, bool value);     // +0x7c
virtual void v80();
virtual void v84();
virtual void v88();
virtual void v8c();
    virtual int Invalidate();                            // +0x90
virtual void v94();
virtual void v98();
virtual void v9c();
virtual void va0();
virtual void va4();
virtual void va8();
virtual void vac();
virtual void vb0();
virtual void vb4();
virtual void vb8();
virtual void vbc();
    virtual Point_s00e4_23a0 ToGlobalCoordinates(Point_s00e4_23a0 p);          // +0xc0
    virtual Point_s00e4_23a0 ToLocalCoordinates(Point_s00e4_23a0 p);           // +0xc4
};
struct IWindowManager {
    virtual void v00();
    virtual IWindow_s00e4_23a0* GetMainWindow();                    // +0x04
};
IWindowManager* WindowManager_0067caa0();
class cSPUILayout_s00e4_23a0 { public:
    bool IsVisible_00810070();
    IWindow_s00e4_23a0* FindWindowByID_008105b0(uint32_t id, bool recursive);
};
struct cSPUIAnimBase0 { virtual void f0(); uint32_t field_4; };
struct cSPUIAnimBase1 { virtual void f1(); };
struct __declspec(align(16)) cSPUIWindowAnimation : cSPUIAnimBase0, cSPUIAnimBase1 {
    Object_s00e4_23a0* mpTarget;                                    // +0x0c
    virtual void f0();
    virtual void f1();
    ~cSPUIWindowAnimation() { if (mpTarget) mpTarget->Release(); }
};
cSPUIWindowAnimation SPUICreateWindowAnimationTargetPosition_007f80d0(IWindow_s00e4_23a0* w, Point_s00e4_23a0 target, float seconds);
float GetElapsedSeconds_00805080(float base, int a, IWindow_s00e4_23a0* w, int b);   // SPUIHelpers::GetElapsedSeconds
class cSPUIAnimator_s00e4_23a0 { public:
    void AddAnimation_007f8d10(const cSPUIWindowAnimation& anim);
    void Update_007f63b0();
};
void GetWindowBounds_00805fe0(Rect_s00e4_23a0* out, IWindow_s00e4_23a0* w);
struct Stopwatch_s00e4_23a0 {
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
    IWindow_s00e4_23a0* mpIcon;                 // +0x1c
    IWindow_s00e4_23a0* mpBoundsWindow;         // +0x20
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
struct WindowPairNode { void* links[4]; IWindow_s00e4_23a0* first; IWindow_s00e4_23a0* second; };
WindowPairNode* RBTreeIncrement_00921580(WindowPairNode* n);
struct cTimelinePanel {
    char pad0[0x2c];
    cSPUIAnimator_s00e4_23a0* mpAnimator;       // +0x2c
    cSPUILayout_s00e4_23a0*   mpLayout;         // +0x30
    char pad34[0x3c - 0x34];
    IWindow_s00e4_23a0* mpClipWindow;           // +0x3c
    IWindow_s00e4_23a0* mpScrollWindow;         // +0x40
    IWindow_s00e4_23a0* mpMirrorWindow;         // +0x44
    char pad48[0x54 - 0x48];
    IWindow_s00e4_23a0* mpInvalidateWindow;     // +0x54
    IWindow_s00e4_23a0* mpSlider;               // +0x58
    IWindow_s00e4_23a0* mpSliderHandle;         // +0x5c
    char pad60[4];
    IWindow_s00e4_23a0* mpFirstVisible;         // +0x64
    IWindow_s00e4_23a0* mpLastVisible;          // +0x68
    char pad6c[0x88 - 0x6c];
    float mMouseX;                   // +0x88
    char pad8c[4];
    Point_s00e4_23a0 mSliderMin;                // +0x90
    float mMaxScroll;                // +0x98
    char pad9c[4];
    Point_s00e4_23a0 mSliderMax;                // +0xa0
    char pada8[0xb0 - 0xa8];
    Stopwatch_s00e4_23a0 mHoverTimer;           // +0xb0
    char padc4[0x100 - 0xc4];
    char mWindowMapHeader[4];        // +0x100
    WindowPairNode mWindowMapAnchor; // +0x104
    char pad11c[0x170 - 0x11c];
    IWindow_s00e4_23a0** mWindowsBegin;         // +0x170
    IWindow_s00e4_23a0** mWindowsEnd;           // +0x174
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
inline void AssignRef(IWindow_s00e4_23a0*& dst, IWindow_s00e4_23a0* src)
{
    if (src != dst) {
        if (src) src->AddRef();
        IWindow_s00e4_23a0* old = dst;
        dst = src;
        if (old) old->Release();
    }
}
// ---- items of slice s00e423a0 end

// ---- items of slice s00e3cf60 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ResourceKey {
    uint32_t instanceID;
    uint32_t typeID;
    uint32_t groupID;
    __forceinline ResourceKey() {}
    __forceinline ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};
namespace ImageCursorProvider {
struct CursorData;
}
namespace ImageCursorProvider {
struct CursorNodeValue {
    uint32_t mID;                       // +0x00
    uint32_t mPad04;                    // +0x04
    uint32_t mPad08;                    // +0x08
    CursorData* mpData;                 // +0x0c
};
}
namespace ImageCursorProvider {
struct CursorListNode {
    CursorListNode* mpNext;             // +0x00
    CursorListNode* mpPrev;             // +0x04
    CursorNodeValue mValue;             // +0x08
};
}
namespace ImageCursorProvider {
struct CursorBucket {
    uint32_t mKey;                      // +0x00
    CursorListNode mAnchor;             // +0x04 (anchor.mpNext is the first record)
};
}
namespace ImageCursorProvider {
struct CursorKey {                      // resource key as stored on a cursor object
    uint32_t typeID;                    // +0x00
    uint32_t instanceID;                // +0x04
    uint32_t groupID;                   // +0x08
};
}
namespace ImageCursorProvider {
struct CursorData {
    uint32_t mPad00[3];                 // +0x00
    CursorKey mKeyA;                    // +0x0c
    CursorKey mKeyB;                    // +0x18
};
}
namespace ImageCursorProvider {
struct CursorKeys {
    ResourceKey mSearch;                // +0x00
    ResourceKey mReplace;               // +0x0c
    void Apply(CursorNodeValue* value); // 0x00e39de0
};
}
namespace ImageCursorProvider {
class CursorMap {
public:
    struct Iterator {
        CursorBucket* mpNode;           // +0x00
        CursorBucket** mpBucket;        // +0x04
    };
    void find(Iterator& out, const uint32_t& key);   // 0x00db4780

    uint32_t mPad00;                    // +0x00
    CursorBucket** mpBuckets;           // +0x04
    uint32_t mnBucketCount;             // +0x08
};
}
namespace ImageCursorProvider {
class CursorProvider {
public:
    void RemapCursorKeys(uint32_t key, CursorKeys keys);

    uint32_t mPad00[3];                 // +0x00
    CursorMap mCursorMap;               // +0x0c
};
}
// ---- items of slice s00e3cf60 end

// ---- items of slice s00e3eca0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_01021260();                                   // GetActivePlanet
struct RBNodeBase {
    RBNodeBase* mpGreater;    // +0x00
    RBNodeBase* mpLess;       // +0x04
    RBNodeBase* mpParent;     // +0x08
    uint8_t     mColor;       // +0x0c
    uint8_t     mPad0d[3];    // +0x0d
};
struct RBAnchor {
    RBNodeBase* mpLeft;       // +0x00  anchor address == end()
    RBNodeBase* mpRight;      // +0x04
    RBNodeBase* mpParent;     // +0x08  root
    uint8_t     mColor;       // +0x0c
    uint8_t     mPad0d[3];    // +0x0d
    uint32_t    mLength;      // +0x10
};
struct ModelTree {
    void*       mpAllocator;  // +0x00
    RBAnchor    mAnchor;      // +0x04
    uint32_t    mPad18;       // +0x18

    float* WorldAt(const uint32_t* pKey);      // 0x00e3eca0
    float* BoundsAt(const uint32_t* pKey);     // 0x00e3ed30
};
struct WorldNode : RBNodeBase {
    uint32_t mKey;            // +0x10
    float    mWidth;          // +0x14
    float    mHeight;         // +0x18
    uint32_t mPad1c;          // +0x1c
};
struct BoundsNode : RBNodeBase {
    uint32_t mKey;            // +0x10
    float    mLeft;           // +0x14
    float    mTop;            // +0x18
    float    mRight;          // +0x1c
    float    mBottom;         // +0x20
};
struct WorldPair {
    union { uint32_t mKey; float mKeyValue; };       // +0x00
    union { float mWidth; uint32_t mWidthBits; };    // +0x04
    union { float mHeight; uint32_t mHeightBits; };  // +0x08
};
struct BoundsPair {
    union { uint32_t mKey; float mKeyValue; };       // +0x00
    union { float mLeft;   uint32_t mLeftBits;   };  // +0x04
    union { float mTop;    uint32_t mTopBits;    };  // +0x08
    union { float mRight;  uint32_t mRightBits;  };  // +0x0c
    union { float mBottom; uint32_t mBottomBits; };  // +0x10
};
struct InsertPos {
    RBNodeBase* mpNode;       // +0x00
};
void __stdcall InsertWorldPair(WorldNode** ppResult, InsertPos pos,
                               const WorldPair* pValue, bool bMulti);      // 0x00e3db00
void __stdcall InsertBoundsPair(BoundsNode** ppResult, InsertPos pos,
                                const BoundsPair* pValue, bool bMulti);    // 0x00e3dbd0
void __stdcall DoNukeSubtree(void* pTree, RBNodeBase* pRoot);              // 0x009a9600
RBNodeBase* FindInWorldTree(ModelTree* pTree, const uint32_t* pKey);       // 0x00e5c780
struct KeyVector {
    uint32_t* mpBegin;        // +0x00
    uint32_t* mpEnd;          // +0x04
    uint32_t* mpCapacity;     // +0x08
    uint32_t* begin() { return mpBegin; }
    uint32_t* end()   { return mpEnd; }
    uint32_t* erase(uint32_t* pFirst, uint32_t* pLast);            // 0x0050f740
};
struct ModelSelector { void __thiscall Select(KeyVector* pKeys); };// 0x00acc800 (thiscall)
void* FUN_00b3d480();                                              // model selector owner
void  FUN_004f6b70(uint32_t* pFirst, uint32_t* pLast);             // eastl::sort
uint32_t* FUN_004f6830(uint32_t* pFirst, uint32_t* pLast);         // eastl::unique
struct ResourceKey_s00e3_eca0 {
    uint32_t mType;           // +0x00
    uint32_t mInstance;       // +0x04
    uint32_t mGroup;          // +0x08
};
struct KeyInstance {
    uint32_t mId;             // +0x00
    float    mValue;          // +0x04
    uint32_t mExtra;          // +0x08
};
struct Property {
    virtual void v00();            // +0x00
    virtual void Release();        // +0x04
    uint8_t  mPad08[0x0a];         // +0x08
    uint16_t mValueType;           // +0x12
    bool*    GetBool();            // 0x0041e920
    int*     GetInt();             // 0x0041e990
};
struct PropertyManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
    virtual void v08();
    virtual bool GetPropertyByKey(uint32_t key, uint32_t prop, Property** ppOut);   // +0x24
    virtual void v0a();                                                              // +0x28
    virtual bool GetProperty(uint32_t key, uint32_t prop, Property** ppOut);          // +0x2c
};
struct KeyVector12 {
    ResourceKey_s00e3_eca0* mpBegin;             // +0x00
    ResourceKey_s00e3_eca0* mpEnd;               // +0x04
    ResourceKey_s00e3_eca0* mpCapacity;          // +0x08
};
struct ModelManager {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual void GetModels(KeyVector12* pOut, const ResourceKey_s00e3_eca0* pKey, int bFlag);  // +0x38
};
struct IWin_s00e3_eca0 {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
    virtual float* GetRect();                                                      // +0x38
};
struct cSPUILayout_s00e3_eca0 {
    cSPUILayout_s00e3_eca0();                                                // 0x00810000
    bool Init(const ResourceKey_s00e3_eca0& key, bool bFlag, uint32_t id);   // 0x008120d0
    IWin_s00e3_eca0* FindWindowByID(uint32_t id, int bFlag);                 // 0x008105b0
    void Shutdown(uint32_t flags);                                // 0x00811ad0
    ~cSPUILayout_s00e3_eca0();                                               // 0x00811fe0
};
struct ModelKeySet {
    uint32_t   mPad00[2];           // +0x00
    void**     mppBuckets;          // +0x08
    uint32_t   mBucketCount;        // +0x0c
};
struct BoundsStringTree {
    void*    mpAllocator;         // +0x00
    RBAnchor mAnchor;             // +0x04
    uint32_t mPad18;              // +0x18
};
struct cSPUILayoutManager_s00e3_eca0 {
    uint32_t         mPad000[0x10];       // +0x000
    IWin_s00e3_eca0*            mpSelectionTarget;   // +0x040
    uint32_t         mPad044[0x3D];       // +0x044
    ModelTree        m_worlds;            // +0x138
    ModelTree        m_bounds;            // +0x154
    uint32_t         mPad170[0x38];       // +0x170
    BoundsStringTree m_boundsTree;        // +0x250
    uint32_t         mPad26c[0xBD];       // +0x26c
    ModelKeySet      m_keySet;            // +0x560
    uint32_t         mPad570[0x04];       // +0x570

    void ResetTree(ModelTree& tree);
    void PreloadModelBounds();
};
struct ModelHash;
void*    EA_ResourceMan_GetManager();                             // 0x0067dcd0
PropertyManager* SP_PropertyManager();                            // 0x0067de30
bool     SP_GetPropertyAsKeyInstance(Property* pProp, uint32_t prop,
                                     uint32_t* pOut);             // 0x006a12a0
float*   SPUIHelpers_GetBoundingScreenRect(float* pRect, IWin_s00e3_eca0* pWin,
                                           char bFlag);           // 0x00808d20
void     operator_delete(void* p);                                // 0x00f47380
uint32_t g_layoutKeyGroup;                                        // 0x015a5930
void cSPUILayoutManager_s00e3_eca0::ResetTree(ModelTree& tree)
{
    DoNukeSubtree(&tree, tree.mAnchor.mpParent);
    RBNodeBase* pAnchor = (RBNodeBase*)&tree.mAnchor;
    tree.mAnchor.mpLeft   = pAnchor;
    tree.mAnchor.mpRight  = pAnchor;
    tree.mAnchor.mpParent = 0;
    tree.mAnchor.mColor   = 0;
    tree.mAnchor.mLength  = 0;
}
struct cMWModel {
    uint32_t     mPad00;            // +0x00
    cMWModel*    mpNext;            // +0x04
    uint32_t     mPad08[3];         // +0x08
    KeyInstance* mpKeyInstance;     // +0x14
    uint32_t     mPad18[0x16];      // +0x18
    uint32_t     mSizeBudget;       // +0x70
};
struct ModelHash {
    cMWModel* mpFirst;              // +0x00
    uint32_t  mPad04;               // +0x04
    uint32_t  mPad08;               // +0x08
};
struct SizeKeyVector {
    uint32_t* mpBegin;              // +0x00
    uint32_t* mpEnd;                // +0x04
    uint32_t* mpCapacity;           // +0x08
    void DoInsertKey4(uint32_t* pWhere, const uint32_t& value);   // 0x00b96600
};
struct ModelSelectionSource {
    uint32_t  mKey;                 // +0x00
    uint32_t* mpOwner;              // +0x04
    uint32_t  mPad08;               // +0x08
    uint32_t  mPad0c[0x17];         // +0x0c
    uint32_t  mSizeBudget;          // +0x68
};
void FUN_00b41b90(void* pSet, void* pOut, const cMWModel* pModel, int bFlag);   // 0x00b41b90
void FUN_00e48f30(void* pThis, const uint32_t* pBudget,
                  uint32_t iChosen, uint32_t iTotal);                            // 0x00e48f30
void FUN_00e47700(void* pThis, const void* pVec);                                // 0x00e47700
void  FUN_007eb100(ModelHash* pThis);                                            // 0x007eb100
void  SP_GetPropertyVector(Property* pProp, uint32_t id,
                           void* pOutA, void* pOutB);                            // 0x006a0ae0
float  FUN_00e37d70(void* pThis, float fValue);                    // 0x00e37d70
float* FUN_00be0790(const uint32_t* pKey);                        // 0x00be0790
void*  FUN_0067de90(int nSize);                                   // pool alloc (sized)
uint32_t* FindInBoundsTree(BoundsStringTree* pTree, const uint32_t* pKey);  // 0x00e39fb0
float  g_flHeightLimit;                                           // 0x016ace30
// ---- items of slice s00e3eca0 end

// ---- items of slice s00e43270 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kTimelineF_0_5;           // 0x01471064 = 0.5
extern const float kTimelineF_8;             // 0x013eeda0 = 8.0
extern const float kTimelineF_0_25;          // 0x013eb8a0 = 0.25
extern const float kTimelineF_5;             // 0x01481c9c = 5.0
extern const float kTimelineF_0_3;           // 0x01481cd0 = 0.3
extern const float kTimelineF_1;             // 0x01485720 = 1.0
extern const float kTimelineF_2;             // 0x01470f1c = 2.0
namespace EA {
class Stopwatch_s00e4_3270 { public:
    uint64_t mnStartTime;                  // +0x00
    uint64_t mnTotalElapsedTime;           // +0x08
    int mnUnits;                           // +0x10
    float mfStopwatchCyclesToUnitsCoefficient;  // +0x14
    Stopwatch_s00e4_3270(int units, bool bStartImmediately);  // 0x0093a560
};
}
namespace EA {
class LimitStopwatch_s00e4_3270 : public Stopwatch_s00e4_3270 { public:
    uint64_t mnEndTime;                    // +0x18
    LimitStopwatch_s00e4_3270(int units, uint32_t nLimit = 0, bool bStartImmediately = false)
        : Stopwatch_s00e4_3270(units, false) { SetTimeLimit(nLimit, bStartImmediately); }
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);  // 0x0093a480
};
}
namespace eastl {
template <typename T> struct less_s00e4_3270 { less_s00e4_3270() {} };
}
namespace eastl {
struct rbtree_node_base_s00e4_3270 {
    rbtree_node_base_s00e4_3270* mpNodeRight;
    rbtree_node_base_s00e4_3270* mpNodeLeft;
    rbtree_node_base_s00e4_3270* mpNodeParent;
    char mColor;
};
}
namespace eastl {
template <typename K>
class rbtree_s00e4_3270 { public:
    less_s00e4_3270<K> mCompare;                      // +0x00
    rbtree_node_base_s00e4_3270 mAnchor;              // +0x04
    uint32_t mnSize;                       // +0x14
    uint32_t mAllocator;                   // +0x18 (EASTL allocator; nothing to construct)

    rbtree_s00e4_3270() : mAnchor(), mnSize(0) { reset(); }
    void reset() {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};
}
namespace eastl {
extern wchar_t gEmptyString[];             // 0x01667bac
}
namespace eastl {
struct string16_s00e4_3270 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16_s00e4_3270() : mpBegin(&gEmptyString[0]), mpEnd(&gEmptyString[0]), mpCapacity(&gEmptyString[1]) {}
};
}
struct RefObject {
    virtual void Slot00();                 // +0x00
    virtual void Release();                // +0x04
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();                 // +0x24
};
struct cTimelineTrack_s00e4_3270 {
    virtual void Slot00();                 // +0x00
    virtual void Release();                // +0x04
    void Flush();                          // 0x00e48f60 (thiscall, no arguments)
};
struct TraceVector {
    cTimelineTrack_s00e4_3270** mpBegin;              // +0x00
    cTimelineTrack_s00e4_3270** mpEnd;                // +0x04
    cTimelineTrack_s00e4_3270** mpCapacity;           // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    void erase(cTimelineTrack_s00e4_3270** first, cTimelineTrack_s00e4_3270** last);   // 0x00e25bd0 (thiscall, pops 8)
};
RefObject** DoCopyRefPtrs(RefObject** srcFirst, RefObject** srcLast, RefObject** dest);
struct fixed_vector_allocator {
    uint32_t mOverflowAllocator;           // +0x00
    void* mpPoolBegin;                     // +0x04
    fixed_vector_allocator(void* pNodeBuffer) : mpPoolBegin(pNodeBuffer) {}
};
struct RefPtrFixedVector6 {
    RefObject** mpBegin;                   // +0x00
    RefObject** mpEnd;                     // +0x04
    RefObject** mpCapacity;                // +0x08
    fixed_vector_allocator mAllocator;     // +0x0c
    uint32_t mPad14;                       // +0x14
    RefObject* mBuffer[6];                 // +0x18

    // vector::DoInsertValues(position, n, value) instance @ 0x00cbc200
    void DoInsertValues(RefObject** position, uint32_t n, RefObject* const& value);
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void resize(uint32_t n) {
        RefObject* value = 0;
        if (n > size())
            DoInsertValues(mpEnd, n - size(), value);
        else
            mpEnd = mpBegin + n;
    }
    // eastl::vector::erase(first, last): shift the tail down, release the tail slots, fix the end.
    void erase(RefObject** first, RefObject** last) {
        RefObject** pCursor = DoCopyRefPtrs(last, mpEnd, first);
        while (pCursor < mpEnd) {
            RefObject* pOld = *pCursor;
            if (pOld != 0)
                pOld->Release();
            ++pCursor;
        }
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }

    explicit RefPtrFixedVector6(uint32_t n) : mAllocator(&mBuffer[0]) {
        mpBegin = mpEnd = &mBuffer[0];
        mpCapacity = mpBegin + 6;
        resize(n);
    }
};
struct Vector4 {
    float x, y, z, w;
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};
extern const Vector4 kTimelineColorDefault;  // 0x015a5880 = (1, 1, 1, 0)
struct TimelineStaticInfo;                   // 0x0154df28 (static object)
extern TimelineStaticInfo gTimelineStaticInfo;
struct TimelineSub560 {
    uint32_t m00;                            // +0x00
    TimelineStaticInfo* mpInfo;              // +0x04
    uint32_t mCount;                         // +0x08
    uint32_t m0c;                            // +0x0c
    float mf10, mf14;                        // +0x10
    TimelineSub560() : mf10(kTimelineF_1), mf14(kTimelineF_2) {
        mCount = 1;
        mpInfo = &gTimelineStaticInfo;
        m0c = 0;
    }
};
struct ITimelineIfc0 {                       // vptr at +0
    virtual void Ifc0Slot0();
    virtual void Ifc0Slot1() = 0;
};
struct ITimelineIfc1 {                       // vptr at +4
    virtual void Ifc1Slot0() = 0;
    virtual void Ifc1Slot1() = 0;
    virtual void Ifc1Slot2();
};
namespace SP {
class cIGonzagoSubsystem_s00e4_3270 { public: virtual void GonzagoSlot0(); };
}
namespace SP {
struct RefCountTemplateInt { virtual void RefSlot0(); int mnRefCount; };
}
namespace SP {
class cGonzagoSubsystem_s00e4_3270 : public cIGonzagoSubsystem_s00e4_3270, public RefCountTemplateInt { public:
    int mPreModeTransitionState;
    int mPostModeTransitionState;
    int mCurrentTransition;
    int mCurrentTransitionPhase;
    cGonzagoSubsystem_s00e4_3270();                     // 0x00b5b960
};
}
namespace SP {
class cStringTokenTranslator_s00e4_3270 { public:
    virtual void TokenSlot0();
    int mnRefCount;
    cStringTokenTranslator_s00e4_3270();                // 0x006b5870
};
}
class cUITimelineSubsystem
    : public ITimelineIfc0, public ITimelineIfc1, public SP::cGonzagoSubsystem_s00e4_3270,
      public SP::cStringTokenTranslator_s00e4_3270 {
public:
    cUITimelineSubsystem();
    void Reset();                            // 0x00e43280
    virtual void Ifc0Slot0();
    virtual void Ifc0Slot1();
    virtual void Ifc1Slot0();
    virtual void Ifc1Slot1();
    virtual void Ifc1Slot2();
    virtual void GonzagoSlot0();
    virtual void RefSlot0();
    virtual void TokenSlot0();

    uint32_t m02c, m030, m034, m038, m03c, m040, m044, m048, m04c, m050, m054, m058, m05c,
        m060, m064;                          // +0x02c
    uint32_t m068, m06c, m070, m074;         // +0x068
    uint32_t m078[4];                        // +0x078 (not initialised)
    float m088, m08c, m090, m094, m098, m09c, m0a0, m0a4;  // +0x088
    uint32_t m0a8;                           // +0x0a8
    EA::Stopwatch_s00e4_3270 mStopwatch0b0;             // +0x0b0
    eastl::rbtree_s00e4_3270<uint32_t> mMap0c8;         // +0x0c8
    eastl::rbtree_s00e4_3270<uint32_t> mMap0e4;         // +0x0e4
    eastl::rbtree_s00e4_3270<uint32_t> mMap100;         // +0x100
    eastl::rbtree_s00e4_3270<uint32_t> mMap11c;         // +0x11c
    eastl::rbtree_s00e4_3270<uint32_t> mMap138;         // +0x138
    eastl::rbtree_s00e4_3270<uint32_t> mMap154;         // +0x154
    uint32_t m170, m174, m178;               // +0x170
    uint32_t m17c, m180;                     // +0x17c (not initialised)
    uint32_t m184, m188, m18c;               // +0x184
    uint32_t m190, m194;                     // +0x190 (not initialised)
    RefPtrFixedVector6 mRefVec198;           // +0x198
    uint32_t m1c8, m1cc, m1d0, m1d4, m1d8, m1dc, m1e0, m1e4;  // +0x1c8
    Vector4 mColor1e8, mColor1f8, mColor208, mColor218, mColor228, mColor238;  // +0x1e8
    bool m248, m249;                         // +0x248
    float m24c;                              // +0x24c
    eastl::rbtree_s00e4_3270<uint32_t> mMap250;         // +0x250
    bool m26c, m26d;                         // +0x26c
    float m270, m274, m278;                  // +0x270
    bool m27c;                               // +0x27c
    uint32_t m280, m284, m288;               // +0x280
    float m28c, m290;                        // +0x28c
    uint32_t m294, m298, m29c, m2a0, m2a4, m2a8, m2ac, m2b0, m2b4, m2b8, m2bc, m2c0, m2c4,
        m2c8, m2cc, m2d0, m2d4, m2d8, m2dc, m2e0;  // +0x294
    uint32_t m2e4[7];                        // +0x2e4 (not initialised)
    int m300, m304;                          // +0x300
    uint32_t m308, m30c, m310, m314, m318, m31c, m320, m324, m328;  // +0x308
    int m32c;                                // +0x32c
    uint32_t m330, m334, m338, m33c, m340, m344, m348, m34c;  // +0x330
    EA::LimitStopwatch_s00e4_3270 mLimitStopwatch350;   // +0x350
    bool m370, m371;                         // +0x370
    uint32_t m374, m378, m37c, m380, m384, m388, m38c, m390, m394, m398, m39c, m3a0, m3a4,
        m3a8, m3ac, m3b0, m3b4, m3b8, m3bc, m3c0, m3c4, m3c8, m3cc, m3d0, m3d4, m3d8, m3dc,
        m3e0, m3e4, m3e8, m3ec, m3f0;        // +0x374
    EA::Stopwatch_s00e4_3270 mStopwatch3f8;             // +0x3f8
    float m410;                              // +0x410
    EA::Stopwatch_s00e4_3270 mStopwatch418;             // +0x418
    float m430;                              // +0x430
    EA::Stopwatch_s00e4_3270 mStopwatch438;             // +0x438
    float m450;                              // +0x450
    bool m454;                               // +0x454
    uint32_t m458;                           // +0x458
    int m45c;                                // +0x45c
    uint32_t m460, m464, m468;               // +0x460
    uint32_t m46c, m470;                     // +0x46c (not initialised)
    uint32_t m474, m478, m47c;               // +0x474
    uint32_t m480, m484;                     // +0x480 (not initialised)
    uint32_t m488;                           // +0x488
    bool m48c;                               // +0x48c
    uint32_t m490;                           // +0x490
    float m494, m498;                        // +0x494
    bool m49c;                               // +0x49c
    uint32_t m4a0;                           // +0x4a0
    EA::Stopwatch_s00e4_3270 mStopwatch4a8;             // +0x4a8
    float m4c0;                              // +0x4c0
    EA::Stopwatch_s00e4_3270 mStopwatch4c8;             // +0x4c8
    float m4e0, m4e4;                        // +0x4e0
    bool m4e8;                               // +0x4e8
    EA::Stopwatch_s00e4_3270 mStopwatch4f0;             // +0x4f0
    bool m508;                               // +0x508
    EA::Stopwatch_s00e4_3270 mStopwatch510;             // +0x510
    bool m528;                               // +0x528
    EA::Stopwatch_s00e4_3270 mStopwatch530;             // +0x530
    EA::Stopwatch_s00e4_3270 mStopwatch548;             // +0x548
    TimelineSub560 mSub560;                  // +0x560
    uint32_t m578;                           // +0x578
    uint32_t m57c;                           // +0x57c (not initialised)
    uint32_t m580, m584, m588, m58c, m590, m594, m598, m59c, m5a0, m5a4, m5a8, m5ac, m5b0,
        m5b4, m5b8, m5bc, m5c0, m5c4, m5c8, m5cc, m5d0;  // +0x580
    eastl::string16_s00e4_3270 mStr5d4, mStr5e4, mStr5f4, mStr604, mStr614, mStr624, mStr634, mStr644,
        mStr654, mStr664, mStr674, mStr684, mStr694, mStr6a4, mStr6b4, mStr6c4, mStr6d4,
        mStr6e4, mStr6f4;                    // +0x5d4
};
cUITimelineSubsystem::cUITimelineSubsystem()
    : m02c(0), m030(0), m034(0), m038(0), m03c(0), m040(0), m044(0), m048(0), m04c(0),
      m050(0), m054(0), m058(0), m05c(0), m060(0), m064(0),
      m068(0), m06c(0), m070(0), m074(0),
      m088(0.0f), m08c(0.0f), m090(0.0f), m094(0.0f), m098(0.0f), m09c(0.0f), m0a0(0.0f),
      m0a4(0.0f), m0a8(0),
      mStopwatch0b0(4, false),
      m170(0), m174(0), m178(0), m184(0), m188(0), m18c(0),
      mRefVec198(6),
      m1c8(0), m1cc(0), m1d0(0), m1d4(0), m1d8(0), m1dc(0), m1e0(0), m1e4(0),
      mColor1e8(kTimelineColorDefault), mColor1f8(kTimelineColorDefault),
      mColor208(kTimelineColorDefault), mColor218(kTimelineColorDefault),
      mColor228(kTimelineColorDefault), mColor238(kTimelineColorDefault),
      m248(false), m249(false), m24c(0.0f),
      m26c(false), m26d(false), m270(0.0f), m274(0.0f), m278(0.0f), m27c(false),
      m280(0), m284(0), m288(0), m28c(0.0f), m290(0.0f),
      m294(0), m298(0), m29c(0), m2a0(0), m2a4(0), m2a8(0), m2ac(0), m2b0(0), m2b4(0),
      m2b8(0), m2bc(0), m2c0(0), m2c4(0), m2c8(0), m2cc(0), m2d0(0), m2d4(0), m2d8(0),
      m2dc(0), m2e0(0),
      m300(-1), m304(-1),
      m308(0), m30c(0), m310(0), m314(0), m318(0), m31c(0), m320(0), m324(0), m328(0),
      m32c(-1),
      m330(0), m334(0), m338(0), m33c(0), m340(0), m344(0), m348(0), m34c(0),
      mLimitStopwatch350(4),
      m370(false), m371(false),
      m374(0), m378(0), m37c(0), m380(0), m384(0), m388(0), m38c(0), m390(0), m394(0),
      m398(0), m39c(0), m3a0(0), m3a4(0), m3a8(0), m3ac(0), m3b0(0), m3b4(0), m3b8(0),
      m3bc(0), m3c0(0), m3c4(0), m3c8(0), m3cc(0), m3d0(0), m3d4(0), m3d8(0), m3dc(0),
      m3e0(0), m3e4(0), m3e8(0), m3ec(0), m3f0(0),
      mStopwatch3f8(5, false), m410(kTimelineF_0_5),
      mStopwatch418(5, false), m430(kTimelineF_8),
      mStopwatch438(5, false), m450(kTimelineF_0_25),
      m454(false), m458(0), m45c(-1), m460(0), m464(0), m468(0),
      m474(0), m478(0), m47c(0), m488(0), m48c(false), m490(0),
      m494(0.0f), m498(0.0f), m49c(false), m4a0(0),
      mStopwatch4a8(5, false), m4c0(0.0f),
      mStopwatch4c8(5, false), m4e0(kTimelineF_5), m4e4(kTimelineF_0_3), m4e8(false),
      mStopwatch4f0(5, false), m508(false),
      mStopwatch510(5, false), m528(false),
      mStopwatch530(5, false),
      mStopwatch548(5, false),
      m578(0),
      m580(0), m584(0), m588(0), m58c(0), m590(0), m594(0), m598(0), m59c(0), m5a0(0),
      m5a4(0), m5a8(0), m5ac(0), m5b0(0), m5b4(0), m5b8(0), m5bc(0), m5c0(0), m5c4(0),
      m5c8(0), m5cc(0), m5d0(0) {
}
struct cSPPalettePageUI_s00e4_3270 {
    void Update(uint32_t deltaMs);         // 0x00e423a0 (thiscall, pops 4)
};
struct cTimelinePageHost {
    void Update(uint32_t arg0, uint32_t arg1);
};
struct TimelineHintSink {
    void Notify(int a, int b) {
        uint32_t* pVtable = *(uint32_t**)this;
        typedef void (__thiscall* Fn)(TimelineHintSink*, int, int);
        ((Fn)pVtable[0x7c / 4])(this, a, b);
    }
};
struct TimelineEntry {
    uint32_t m00, m04, m08;
};
struct ResourceKey_s00e4_3270 {
    uint32_t mTypeID;                      // +0x00
    uint32_t mInstanceID;                  // +0x04
    uint32_t mGroupID;                     // +0x08
};
void SortKeys(ResourceKey_s00e4_3270* first, ResourceKey_s00e4_3270* last);              // 0x004f6b70 (eastl::sort)
ResourceKey_s00e4_3270* UniqueKeys(ResourceKey_s00e4_3270* first, ResourceKey_s00e4_3270* last);    // 0x004f6830 (eastl::unique)
struct KeyVector_s00e4_3270 {
    ResourceKey_s00e4_3270* mpBegin;                  // +0x00
    ResourceKey_s00e4_3270* mpEnd;                    // +0x04
    ResourceKey_s00e4_3270* mpCapacity;               // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    ResourceKey_s00e4_3270* end() const { return mpEnd; }
    void reserve(int n);                   // 0x0041e4d0 (thiscall, pops 4)
    void DoInsertKey(ResourceKey_s00e4_3270* position, const ResourceKey_s00e4_3270& key);   // 0x004e3e10
    void push_back(const ResourceKey_s00e4_3270& key) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) ResourceKey_s00e4_3270(key);
        else
            DoInsertKey(mpEnd, key);
    }
    void erase(ResourceKey_s00e4_3270* first, ResourceKey_s00e4_3270* last);
};
void KeyVector_s00e4_3270::erase(ResourceKey_s00e4_3270* first, ResourceKey_s00e4_3270* last)
{
    ResourceKey_s00e4_3270* pOldEnd = mpEnd;
    ResourceKey_s00e4_3270* pTarget = first;
    for (ResourceKey_s00e4_3270* pSource = last; pSource != pOldEnd; ++pSource)
        *pTarget++ = *pSource;
    ResourceKey_s00e4_3270* pNewEnd = pTarget;
    for (ResourceKey_s00e4_3270* pIt = pNewEnd; pIt != mpEnd; ++pIt) {
        // ResourceKey is a POD: nothing to destroy.
    }
    mpEnd -= (last - first);
}
struct cSpeciesProfile_s00e4_3270 {
    uint8_t mPad00[0x504];                 // +0x000
    ResourceKey_s00e4_3270 mModelKey;                 // +0x504
};
struct cGameNoun {
    uint8_t mPad00[0xa4];                  // +0x000
    cSpeciesProfile_s00e4_3270* mpProfile;            // +0x0a4
    bool HasProperty(uint32_t propertyID);              // 0x00bf2cb0 (thiscall, pops 4)
    ResourceKey_s00e4_3270* GetModelTypeKey(uint32_t propertyID);  // 0x00bf9770 (thiscall, pops 4)
};
struct SpVectorAllocatorBase {
    void* mpAllocator;                     // +0x00
};
struct GameDataVector : SpVectorAllocatorBase {
    cGameNoun** mpBegin;                   // +0x04
    cGameNoun** mpEnd;                     // +0x08
    cGameNoun** mpCapacity;                // +0x0c
    int count() const { return (int)(mpEnd - mpBegin); }
};
struct cTerrainSphere_s00e4_3270 {
    uint8_t mPad00[0x1168];                // +0x0000
    ResourceKey_s00e4_3270 mKey1168;                  // +0x1168
};
class cGameNounManager_s00e4_3270 {
public:
    SpVectorAllocatorBase* GetGameDataVector(void* p0, void* p1, void* p2, void* p3, void* p4);  // 0x00b21340
    cTerrainSphere_s00e4_3270* GetCurrentTerrainSphere();             // 0x00f67d90 (thiscall)
};
cGameNounManager_s00e4_3270* NounManager_s00e4_3270();                           // 0x00b3d300
struct cKeyCollector { void FUN_00acc800(); };             // 0x00acc800 (thiscall, no arguments)
cKeyCollector* __stdcall FUN_00b3d480(KeyVector_s00e4_3270* keys);    // 0x00b3d480 (callee pops its argument)
class cSPEditorSpeciesManager_s00e4_3270 {
public:
    cSpeciesProfile_s00e4_3270* GetAvatarProfile();                   // 0x004df420 (thiscall)
};
cSPEditorSpeciesManager_s00e4_3270* GetSpeciesManager();              // 0x00401090 (cdecl)
void* GetActivePlanet();
class cSimSingleton {
public:
    uint8_t mData[0x100];                  // +0x000 (0x100-byte singleton)
    cSimSingleton();                       // 0x00cc5a70
    void FUN_00cc5bc0(KeyVector_s00e4_3270* keys);    // 0x00cc5bc0 (thiscall, pops 4)
};
extern cSimSingleton* gSimSingleton;       // 0x0169b054
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
const uint32_t gCreaturePropertyIDs[7] = {
    0x99e92f05, 0x4e3f7777, 0x47c10953, 0x72c49181, 0x2090a11b, 0xbc1041e6, 0xc15695da
};
// ---- items of slice s00e43270 end

// ---- items of slice s00e44200 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector4_s00e4_4200 { float x, y, z, w; };
struct Object_s00e4_4200 {
    virtual int  AddRef();                                 // +0x00 0x00432a50
    virtual int  Release();                                // +0x04
    virtual void Delete();                                 // +0x08
};
#define IOFF(n) virtual void v##n();
struct IWindow_s00e4_4200 : Object_s00e4_4200 {
    IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void BeforeRelease();                          // +0x20
    virtual void Unload();                                 // +0x24
    IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c) IOFF(40)
    IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void SetShadeColor(uint32_t color);            // +0x5c
    virtual void SetLayoutData(const Vector4_s00e4_4200* data);       // +0x60
    IOFF(64) IOFF(68) IOFF(6c) IOFF(70) IOFF(74) IOFF(78)
    virtual void SetVisible(int visible, int recursive);   // +0x7c
    IOFF(80) IOFF(84) IOFF(88) IOFF(8c) IOFF(90) IOFF(94) IOFF(98) IOFF(9c)
    IOFF(a0) IOFF(a4) IOFF(a8) IOFF(ac) IOFF(b0) IOFF(b4) IOFF(b8) IOFF(bc)
    IOFF(c0) IOFF(c4) IOFF(c8) IOFF(cc) IOFF(d0) IOFF(d4) IOFF(d8) IOFF(dc)
    IOFF(e0) IOFF(e4) IOFF(e8) IOFF(ec) IOFF(f0) IOFF(f4) IOFF(f8) IOFF(fc)
    IOFF(100) IOFF(104)
    virtual void SetParent(void* parent);                  // +0x108
};
class cSPUILayout_s00e4_4200 : public IWindow_s00e4_4200 {
public:
    bool      IsVisible();                                 // 0x00810070
    void      SetVisibility(int visible);                  // 0x00810590
    IWindow_s00e4_4200*  FindWindowByID(uint32_t id, bool recursive); // 0x008105b0
    void      Shutdown(int everything);                    // 0x00811ad0
};
struct cSPPaletteItem : Object_s00e4_4200 {
    void Shutdown();                                       // 0x005c6710
};
struct RefCountBase {
    virtual int AddRef();                                  // +0x00
    virtual int Release();                                 // +0x04
};
struct cTwoBaseObj {
    virtual int  AddRef();                                 // +0x00
    virtual int  Release();                                // +0x04
    virtual void Delete();                                 // +0x08
    uint32_t     mPad04[3];                                // +0x04 .. +0x0f
    RefCountBase mSecond;                                  // +0x10
};
struct IFlaggedRelease {
    virtual void Release(int keep);                        // +0x00
};
struct IEffectsHandler {
    virtual void pad00();                                  // +0x00
    virtual void Release();                                // +0x04
    virtual void Delete(int unused);                       // +0x08
    virtual void SetEnabled(int enabled);                  // +0x0c
};
struct KeyVec {
    void* mpBegin;                                         // +0x00
    void* mpEnd;                                           // +0x04
    void* mpCap;                                           // +0x08
    void  DoCopy(void* first, void* last);                 // 0x0050f740
};
struct cSPUILayoutManager_s00e4_4200 {
    void SetAllWorldsVisibility(bool visible);             // 0x008106a0
    void SetLayerVisible(uint32_t id, bool visible);       // 0x00810660
};
struct IMessageServer {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10)
    virtual void BeginModal(uint32_t id, int a, int b);    // +0x14
    virtual void SendMessage(uint32_t id, int a, int b, int c); // +0x18
};
struct cEffectsManager {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18)
    IOFF(1c) IOFF(20) IOFF(24) IOFF(28)
    virtual bool AddMessageHandler(uint32_t id, int priority,
                                   IEffectsHandler** handlerOut); // +0x2c
};
struct cNotifier67dd50 {
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c)
    IOFF(40) IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void SetNotificationA(uint32_t id, int value); // +0x5c
    virtual void SetNotificationB(uint32_t id, int value); // +0x60
};
struct cWindowManager {                                    // 0x0067caa0
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    IOFF(20) IOFF(24) IOFF(28) IOFF(2c) IOFF(30) IOFF(34) IOFF(38) IOFF(3c)
    IOFF(40) IOFF(44) IOFF(48) IOFF(4c) IOFF(50) IOFF(54) IOFF(58)
    virtual void ShowWindow(int show, IWindow_s00e4_4200* window);    // +0x5c
};
struct cUIHints {
    int  SetFlag(char flag, int value);                    // 0x0067c420
};
struct IAudioSystem_s00e4_4200 {                                      // EA::Audio::GetSystemAT result
    IOFF(00) IOFF(04) IOFF(08) IOFF(0c) IOFF(10) IOFF(14) IOFF(18) IOFF(1c)
    virtual void* GetListener();                           // +0x20
};
cSPUILayoutManager_s00e4_4200* SPUIHelpers_GetLayoutManager();        // 0x00805070
void SPUIHelpers_BeginModal(IWindow_s00e4_4200* owner, int a, int b);  // 0x008099a0
void SPUIHelpers_EndModal(IWindow_s00e4_4200* owner, int a, int b);    // 0x00809c50
void SP_KillSetiEffects(uint32_t id, void* system);        // 0x00435ed0
IMessageServer* SP_MessageServer_s00e4_4200();                        // 0x0067dcc0
cEffectsManager* SP_EffectsManager();                      // 0x0067ddd0
cWindowManager* SP_WindowManager_s00e4_4200();                        // 0x0067caa0
IAudioSystem_s00e4_4200* EA_Audio_GetSystemAT();                      // 0x00a206f0
extern "C" cNotifier67dd50* FUN_0067dd50();                // 0x0067dd50
extern "C" cUIHints*        FUN_0067cac0();                // 0x0067cac0
struct cSPUITimeline_s00e4_4200 {
    uint32_t         mVtbl;                                // +0x00
    uint32_t         mSelfWindow;                          // +0x04 head of the embedded window subobject
    uint32_t         mPad08[3];                            // +0x08 .. +0x13
    void*            mpCallbackTarget;                     // +0x14 handed to the render targets
    uint32_t         mPad18;                               // +0x18
    IFlaggedRelease* mpAnimatorA;                          // +0x1c
    cSPUILayout_s00e4_4200*     mpLayoutA;                            // +0x20
    cSPUILayout_s00e4_4200*     mpLayoutB;                            // +0x24
    IWindow_s00e4_4200*         mpWindowA;                            // +0x28
    IWindow_s00e4_4200*         mpWindowB;                            // +0x2c
    cSPUILayout_s00e4_4200*     mpLayout;                             // +0x30 the timeline layout Show() drives
    uint32_t         mPad34;                               // +0x34
    IWindow_s00e4_4200*         mpModalOwner;                         // +0x38
    IWindow_s00e4_4200*         mpCreatureWindow;                     // +0x3c
    uint32_t         mPad40;                               // +0x40
    IWindow_s00e4_4200*         mpTribeWindow;                        // +0x44
    uint32_t         mPad48;                               // +0x48
    IWindow_s00e4_4200*         mpCivWindow;                          // +0x4c
    uint32_t         mPad50[2];                            // +0x50 .. +0x57
    IWindow_s00e4_4200*         mpCreatureButton;                     // +0x58
    uint32_t         mPad5c;                               // +0x5c
    IWindow_s00e4_4200*         mpTribeButton;                        // +0x60
    uint32_t         mPad64[0x56];                         // +0x64 .. +0x1bb
    cSPPaletteItem*  mpPaletteItem;                        // +0x1bc
    Object_s00e4_4200*          mpPaletteInfo;                        // +0x1c0
    IWindow_s00e4_4200*         mpPaletteRollover;                    // +0x1c4
    IWindow_s00e4_4200*         mpEventRollover;                      // +0x1c8
    uint32_t         mPad1cc[0x28];                        // +0x1cc .. +0x26b
    bool             mbCreatureWindowShown;                // +0x26c
    bool             mbTribeWindowShown;                   // +0x26d
    uint8_t          mPad26e[0x0e];                        // +0x26e .. +0x27b
    bool             mbPanelReady;                         // +0x27c
    uint8_t          mPad27d[3];                           // +0x27d .. +0x27f
    int              mnPanelState;                         // +0x280
    int              mnShowMode;                           // +0x284
    uint32_t         mPad288[3];                           // +0x288 .. +0x293
    int              mnGameLevel;                          // +0x294
    uint32_t         mPad298[0x23];                        // +0x298 .. +0x323
    void*            mpMsgServer;                          // +0x324
    void*            mpMsgOwner;                           // +0x328
    void*            mpMsgIDs;                             // +0x32c
    IEffectsHandler* mpEffectsHandler;                     // +0x330
    unsigned         mMsgFlags;                            // +0x334
    cSPUILayout_s00e4_4200*     mpLayoutC;                            // +0x338
    cSPUILayout_s00e4_4200*     mpLayoutD;                            // +0x33c
    uint32_t         mPad340[9];                           // +0x340 .. +0x363
    IWindow_s00e4_4200*         mpRowWindows[10];                     // +0x364
    IWindow_s00e4_4200*         mpRowIcons[10];                       // +0x38c
    cTwoBaseObj*     mpRowData;                            // +0x3b4
    IWindow_s00e4_4200*         mpRowExtras[10];                      // +0x3b8
    uint32_t         mPad3e0[26];                          // +0x3e0 .. +0x447
    IFlaggedRelease* mpAnimatorB;                          // +0x448
    uint32_t         mPad44c;                              // +0x44c
    KeyVec           mCellKeys;                            // +0x450
    uint32_t         mPad45c[2];                           // +0x45c .. +0x463
    KeyVec           mCreatureKeys;                        // +0x464

    IWindow_s00e4_4200* Self() { return (IWindow_s00e4_4200*)&mSelfWindow; }     // the embedded window at +0x04

    void Show(int show);                                   // 0x00e44200
    bool HandleTimelineMessage(uint32_t msgID, void* payload); // 0x00e449b0
    void FUN_00e37910();                                   // 0x00e37910
    void FUN_00e3e7f0();                                   // 0x00e3e7f0
    void FUN_00e42100();                                   // 0x00e42100
    void FUN_00e43280();                                   // 0x00e43280
};
static __forceinline void HideLevelWindow(cSPUILayout_s00e4_4200* layout, uint32_t id)
{
    if (layout->FindWindowByID(id, 1))
        layout->FindWindowByID(id, 1)->SetVisible(1, 0);
}
static __forceinline void ShowWindowByID(cSPUILayout_s00e4_4200* layout, uint32_t id, int visible)
{
    layout->FindWindowByID(id, 1)->SetVisible(1, visible);
}
static __forceinline void ClearWindowRect(cSPUILayout_s00e4_4200* layout, uint32_t id)
{
    IWindow_s00e4_4200* hidden = layout->FindWindowByID(id, 1);
    hidden->SetVisible(1, 0);
    IWindow_s00e4_4200* cleared = layout->FindWindowByID(id, 1);
    Vector4_s00e4_4200 empty = { 0.0f, 0.0f, 0.0f, 0.0f };
    cleared->SetLayoutData(&empty);
}
static __forceinline void TintWindow(cSPUILayout_s00e4_4200* layout, uint32_t id)
{
    layout->FindWindowByID(id, 1)->SetShadeColor(0xff4b4b4b);
}
// ---- items of slice s00e44200 end

// @ 0x00e36c80
uint32_t __cdecl GetGameModeHash()
{
    switch (SP_GetCurrentGameMode()) {
    case 0x1654c00:
        return 0xa426730b;
    case 0x1654c01:
        return 0xad56080c;
    case 0x1654c02:
        return 0xf71fa311;
    case 0x1654c04:
        return 0xbeb528cb;
    case 0x1654c05:
        return 0x2db6dad3;
    default:
        return 0;
    }
}

// @ 0x00e36e20
bool cUITimedTooltip::UpdateD()
{
    EA::Stopwatch_s00e3_6150& sw = m_sw4c8;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold4e0) {
        if (m_pAnimator458->Empty()) {
            sw.SetBoolProperty();
            return true;
        }
    }
    return false;
}

// @ 0x00e36e80
bool cUITimedTooltip::UpdateE()
{
    EA::Stopwatch_s00e3_6150& sw = m_sw4a8;
    if ((double)sw.GetElapsedTimeFloat() * sw.m_fRate > m_fThreshold4c0) {
        sw.SetBoolProperty();
        return true;
    }
    return false;
}

// @ 0x00e36ed0
int32_t __cdecl GetGameLevel(int32_t nGameMode)
{
    int32_t nMode = nGameMode;
    if (nGameMode == -1)
        nMode = (int32_t)SP_GetCurrentGameMode();
    switch (nMode) {
    case 0x1654c00:
        return 0;
    case 0x1654c01:
        return 1;
    case 0x1654c02:
        return 2;
    case 0x1654c04:
        return 3;
    case 0x1654c05:
        return 4;
    case 0x1654c10:
        return 5;
    default:
        return nGameMode;
    }
}

// @ 0x00e36f50
uint32_t __cdecl GetGameModeIndex(uint32_t nHash)
{
    switch (nHash) {
    case 0xa426730b:
        return 0;
    case 0xad56080c:
        return 1;
    case 0xf71fa311:
        return 2;
    case 0xbeb528cb:
        return 3;
    case 0x2db6dad3:
        return 4;
    default:
        return 0;
    }
}

// @ 0x00e36fb0
cTooltipSlot* cUITimedTooltip::GetSlot(int32_t nIndex)
{
    return &m_slots[nIndex];
}

// @ 0x00e36fd0
void __cdecl SetEditorState()
{
    cEditor* pEditor = (cEditor*)FUN_00b3d410();
    if (pEditor->m_nState == 1)
        pEditor->m_nState = 2;
}

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

    cSPUILayout_s00e3_6ff0* layout = mpLayout;

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

// @ 0x00e37750
bool cSPUITimeline::FUN_00e37750()
{
    if (mn280 < DAT_016acf2c)
        return true;
    unsigned v = mn284;
    return v != 0 && v != 8;
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

// @ 0x00e37840
void cSPUITimeline::FUN_00e37840(IWindow* target, float a, float b, float c, float d, float e, float f, float g, float h)
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

// @ 0x00e37f30
double cSPUITimeline::FUN_00e37f30(int idx)
{
    static float s_width = cSPUITimeline_GetScreenWidth();
    if (idx == mSelectedIdx)
        return (double)s_width;
    return 0.0;
}

// @ 0x00e37f90
Vector2_s00e3_7f90 Timeline_s00e3_7f90::GetKeyPair(uint32_t nX, int32_t nOffset)
{
    Vector2_s00e3_7f90 result;
    result.x = 0.0f;
    result.y = 0.0f;

    cTrackNode* pNode = FindNode(nX, nOffset);
    if (pNode != nullptr) {
        Vector2_s00e3_7f90 key;
        if (pNode->m_nKeyCount != 0) {
            Vector2_s00e3_7f90* pKey = pNode->LookupKey(&key);
            result.x = pKey->x;
            result.y = FindNode(nX, nOffset - 1)->LookupKey(&key)->y;
            return result;
        }
        result = *pNode->LookupKey(&key);
    }
    return result;
}

// @ 0x00e38020
bool Timeline_s00e3_7f90::ClipTracks(Vector2_s00e3_7f90* pFirst, Vector2_s00e3_7f90* pSecond, Vector2_s00e3_7f90* pThird, Vector2_s00e3_7f90* pFourth, bool bFlip)
{
    if (m_pHolder == nullptr)
        return false;

    RectF* pHolderRect = m_pHolder->GetRect38();
    float fHeight = pHolderRect->y1 - pHolderRect->y0;

    Vector2_s00e3_7f90 origin;
    origin.x = 0.0f;
    origin.y = 0.0f;
    m_pHolder->SetPos64(origin.x, origin.y);
    const float* pBounds = (const float*)m_pHolder->GetRect34();
    float fTop = pBounds[1];

    Vector2_s00e3_7f90 offset;
    offset.x = 0.0f;
    offset.y = fHeight;
    m_pHolder->SetPos64(offset.x, offset.y);
    const float* pInner = (const float*)m_pHolder->GetRect34();
    float fBottom = pInner[1];

    float fLow = (fBottom - fTop) * 0.375f + fTop;
    float fHigh = (fBottom - fTop) * 0.625f + fTop;
    bool bResult = false;

    if (fLow <= pThird->y && pFourth->y < fHigh) {
        float fMid = (pFourth->x - pThird->x) * 0.5f + pThird->x;
        pFourth->y = fTop;
        pFourth->x = (pFourth->x - pThird->x) * 0.5f + pThird->x;
        (void)fMid;
        bResult = true;
    } else if (fHigh < pThird->y && pThird->y <= fLow) {
        pThird->y = fBottom;
        pThird->x = (pThird->x - pThird->x) * 0.5f + pThird->x;
        *pFirst = *pThird;
        bResult = true;
    }

    if (fLow <= pSecond->y && pFourth->y < fHigh) {
        pFourth->x = (pSecond->x - pFourth->x) * 0.5f + pFourth->x;
        pFourth->y = fTop;
        pFourth->x = (pFourth->x - pThird->x) * 0.5f + pThird->x;
    } else if (fHigh < pSecond->y && pSecond->y <= fLow) {
        pFirst->x = (pSecond->x - pFirst->x) * 0.5f + pFirst->x;
        pFirst->y = fBottom;
        (void)bFlip;
    }
    return bResult;
}

// @ 0x00e38240
void TimelineCards::UpdateCard()
{
    if (gspAppProperties->GetDescription(0x6dd5a65c))
        return;
    if (m_nIndex >= m_nTrackCount)
        return;
    if (m_apTracks[m_nIndex] == nullptr)
        return;

    Key_s00e3_7f90 key;
    key.m_nGroup = 0;
    key.m_nType = 0;
    key.m_nInstance = 0;
    if (!FUN_00401010())
        return;

    if (!gbCardInitialised) {
        gbCardInitialised = true;
        gKeyCardData.m_nGroup = 0;
        gKeyCardData.m_nType = 0;
        gKeyCardData.m_nInstance = 0;
    }

    if (!ResourceKeyNotEqual(&key, &gKeyCardData))
        return;
    if (key.m_nType == 0x476a98c7)
        return;

    FUN_00401090();
    Key_s00e3_7f90 other = *(const Key_s00e3_7f90*)FUN_004df400();
    if (!ResourceKeyNotEqual(&key, &other))
        return;

    gKeyCardData = key;

    cSporepediaCardData* pData = (cSporepediaCardData*)m_cardData.m_pObject;
    if (pData != nullptr)
        pData->Release();
    if (pData == nullptr) {
        pData = (cSporepediaCardData*)operator_new(
            0x78, "UI/TimelineSporepediaCardData", 0, 0, 0, 0);
        if (pData != nullptr)
            FUN_006428c0(pData->Construct());
    }
    pData = (cSporepediaCardData*)m_cardData.m_pObject;
    uint32_t aInfo[2];
    aInfo[0] = 0;
    aInfo[1] = 0;
    pData->Get(aInfo);

    IWindow_s00e3_7f90* pTrack = m_apTracks[m_nIndex];
    if (m_apCardViews[m_nIndex].m_pObject != nullptr)
        ((IWindow_s00e3_7f90*)m_apCardViews[m_nIndex].m_pObject)->Reset20();
    if (m_apCardViews[m_nIndex].m_pObject == nullptr) {
        cSporepediaCardView* pView = (cSporepediaCardView*)operator_new(
            0x108, "UI/TimelineSporepediaCardView", 0, 0, 0, 0);
        if (pView != nullptr)
            AssignCardView(&m_apCardViews[m_nIndex], pView->Construct());
    }

    IWindow_s00e3_7f90* pView = (IWindow_s00e3_7f90*)m_apCardViews[m_nIndex].m_pObject;
    pView->SetContent1c(pTrack, m_cardData.m_pObject, 0, 0);
    pView->SetFlag30(false, false);
    pView->SetFlag28(true);
}

// @ 0x00e38450
void TimelineCards::Layout()
{
    Vec4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    float fHeight = area.w - area.y;

    Vec4 area2;
    SPUIHelpers_GetMainWindowArea(&area2);
    float fWidth = area2.z - area2.x;

    IWindow_s00e3_7f90* pBar = (IWindow_s00e3_7f90*)m_pLayout->FindWindowByID(0x64d0819, true);
    RectF* pBarRect = pBar->GetRect38();
    float fBarHeight = pBarRect->y1 - pBarRect->y0;

    RectF* pTrackRect = m_apTracks[0]->GetRect34();
    float fAspect = (pTrackRect->x1 - pTrackRect->x0)
                    / (pTrackRect->y1 - pTrackRect->y0);
    float fCell = fAspect * fBarHeight;

    float fStep = fWidth / (float)m_nTrackCount;
    float fGap = fStep - fCell;
    m_fCell = fGap;
    if (0.0f < fGap) {
        m_fCell = (fGap * 0.33333334f) * 2.0f;
    } else {
        fCell = fStep / fAspect;
        fGap = fStep;
    }

    for (uint32_t i = 0; i < m_nTrackCount; ++i)
        m_apTracks[i]->SetSize68(fGap, fCell);

    IWindow_s00e3_7f90* pLine = (IWindow_s00e3_7f90*)m_pLayout->FindWindowByID(0x64d0818, true);
    RectF* pLineRect = pLine->GetRect38();
    float fLineY0 = pLineRect->y0;
    float fLineY1 = pLineRect->y1;

    IWindow_s00e3_7f90* pFrame = (IWindow_s00e3_7f90*)m_pLayout->FindWindowByID(0x6456c48, true);
    RectF* pFrameRect = pFrame->GetRect38();
    RectF frame = *pFrameRect;
    frame.y1 = (fLineY1 - fLineY0) * 0.8f;

    IWindow_s00e3_7f90* pFrame2 = (IWindow_s00e3_7f90*)m_pLayout->FindWindowByID(0x6456c48, true);
    pFrame2->SetRect60(&frame);

    if (!IsWorldLayoutFlagSet(2))
        return;

    IWindow_s00e3_7f90* pBackground = (IWindow_s00e3_7f90*)m_pOverlayLayout->FindWindowByID(0x762350f,
                                                                      true);
    if (pBackground == nullptr || gbBackgroundLayoutSeeded)
        return;
    gbBackgroundLayoutSeeded = true;

    float fScaleX = fHeight * 0.00125f;
    float fScaleY = fStep * 0.0016666667f;

    RectF* pBackRect = pBackground->GetRect34();
    RectF back = *pBackRect;
    back.x1 = (pBackRect->x1 - pBackRect->x0) * fScaleX + pBackRect->x0;
    back.y0 = pBackRect->y0 * fScaleY;
    back.y1 = back.y0 + (pBackRect->y1 - pBackRect->y0);
    pBackground->SetRect60(&back);

    IWindow_s00e3_7f90* pInner = (IWindow_s00e3_7f90*)m_pOverlayLayout->FindWindowByID(0x765e17a, true);
    RectF inner = { 0.0f, 0.0f, 0.0f, 0.0f };
    if (pInner != nullptr) {
        RectF* pInnerRect = pInner->GetRect34();
        inner.x0 = pInnerRect->x0;
        inner.y0 = pInnerRect->y0;
        inner.x1 = (pInnerRect->x1 - pInnerRect->x0) * fScaleX;
        inner.y1 = (pInnerRect->y1 - pInnerRect->y0) * fScaleX;
        pInner->SetRect60(&inner);

        IWindow_s00e3_7f90* pHandle = (IWindow_s00e3_7f90*)m_pOverlayLayout->FindWindowByID(0x76236bd,
                                                                      true);
        if (pHandle != nullptr) {
            RectF* pHandleRect = pHandle->GetRect34();
            RectF handle = *pHandleRect;
            handle.x0 = pHandleRect->x0 * fScaleY;
            handle.y0 = pHandleRect->y0 * fScaleY;
            handle.x1 = (pHandleRect->x1 - pHandleRect->x0) * fScaleY + handle.x0;
            handle.y1 = (pHandleRect->y1 - pHandleRect->y0) * fScaleY + handle.y0;
            pHandle->SetRect60(&handle);
        }
    }

    IWindow_s00e3_7f90* pMarker = (IWindow_s00e3_7f90*)m_pOverlayLayout->FindWindowByID(0x765e179,
                                                                  true);
    if (pMarker != nullptr) {
        RectF* pMarkerRect = pMarker->GetRect34();
        RectF marker = *pMarkerRect;
        marker.y0 = pMarkerRect->y0;
        marker.x1 = marker.x0 + fScaleY;
        marker.y1 = marker.y0 + inner.y1;
        pMarker->SetRect60(&marker);

        IWindow_s00e3_7f90* pTick = (IWindow_s00e3_7f90*)m_pOverlayLayout->FindWindowByID(0x76236be,
                                                                    true);
        if (pTick != nullptr) {
            RectF* pTickRect = pTick->GetRect34();
            RectF tick = *pTickRect;
            tick.x0 = pTickRect->x0 * fScaleY;
            tick.y0 = pTickRect->y0 * fScaleY;
            tick.x1 = (pTickRect->x1 - pTickRect->x0) * fScaleY + tick.x0;
            tick.y1 = (pTickRect->y1 - pTickRect->y0) * fScaleY + tick.y0;
            pTick->SetRect60(&tick);
        }
    }

    IWindow_s00e3_7f90* pEnd = (IWindow_s00e3_7f90*)m_pOverlayLayout->FindWindowByID(0x76236bc, true);
    if (pEnd != nullptr) {
        RectF* pEndRect = pEnd->GetRect34();
        RectF end = *pEndRect;
        end.x0 = pEndRect->x0 * fScaleY;
        end.x1 = (pEndRect->x1 - pEndRect->x0) * fScaleY + end.x0;
        pEnd->SetRect60(&end);
    }
}

// @ 0x00e389e0
void TimelineCards::AnimateIcon()
{
    if (m_pAnimator == nullptr)
        return;
    if (m_apTracks[m_nIndex] == nullptr)
        return;

    Key_s00e3_7f90 image;
    image.m_nGroup = 0xfada8c70;
    image.m_nType = 0x2f7d0004;
    image.m_nInstance = 0x02e9a2ca;
    SetWindowImage(m_apImages[m_nIndex], &image, -1);

    Vec4 area;
    SPUIHelpers_GetMainWindowArea(&area);
    float fAreaW = area.z - area.x;
    float fAreaH = area.w - area.y;

    RectF* pRect = m_apTracks[m_nIndex]->GetRect38();
    float fW = pRect->x1 - pRect->x0;
    float fH = pRect->y1 - pRect->y0;
    m_apTracks[m_nIndex]->SetPos64(fAreaW, fAreaH - fH);

    float fDelay = m_fScroll + m_fCell;
    m_fScroll = (fW + m_fScroll) + m_fCell;

    float fTime = SPUIHelpers_GetElapsedSeconds(m_fDelay410, 2,
                                                m_apTracks[m_nIndex], 0);
    Vector2_s00e3_7f90 target;
    target.x = fDelay;
    target.y = fAreaH;
    void* pAnim = SPUICreateWindowAnimationTargetPosition(
        &target, m_apTracks[m_nIndex], &target, fTime, fDelay);
    m_pAnimator->AddAnimation(pAnim, nullptr, 0);
    m_sw3f8.Restart();
    m_sw418.Restart();
}

// @ 0x00e38bb0
bool Timeline_s00e3_7f90::StepBack()
{
    uint32_t nIndex = m_nIndex - 1;
    bool bResult = false;
    if (nIndex < m_nTrackCount) {
        if (nIndex == m_nTrackCount - 1)
            m_bLast = true;
        IWindow_s00e3_7f90* pTrack = m_apTracks[nIndex];
        if (m_pAnimator != nullptr && pTrack != nullptr) {
            float fTime = SPUIHelpers_GetElapsedSeconds(m_f450, 0, pTrack, 1);
            AnimRaw anim;
            void* pAnim = SPUICreateWindowAnimationRotation(
                &anim, pTrack, 0.0f, 1.0f, 0.0f, gkfIdleDelay, fTime);
            m_pAnimator->AddAnimation(pAnim, nullptr, 1);
            m_sw438.Restart();
        }
        bResult = true;
    }
    return bResult;
}

// @ 0x00e38c90
bool Timeline_s00e3_7f90::Step()
{
    uint32_t nIndex = m_nIndex;
    bool bResult = false;
    if (nIndex < m_nTrackCount) {
        m_fDelay410 = 0.2f;
        m_apTracks[nIndex]->SetFlags7c(true, true);
        PlayIconAnimation();
        m_nIndex++;
        bResult = true;
    }
    return bResult;
}

// @ 0x00e38ce0
void __fastcall FUN_00e38ce0(Timeline_s00e3_8ce0* self, void* dummy, u32 mode)
{
  (void)dummy;
  Wnd* w1 = self->p348->FindWindowByID(0x06456c48u, 1);
  Wnd* w2 = (self->p34c != 0) ? self->p34c->FindWindowByID(0x06456c48u, 1) : 0;
  ((WndVt*)w1)->SetVisible(1, 1);
  if (self->anim == 0) return;

  self->anim->RemoveAnimation(w1, -1);
  if (w2 != 0) self->anim->RemoveAnimation(w2, -1);

  const u32* table;
  u32 n;
  if (mode == 0x01654c02u) { table = (const u32*)0x01481d04; n = 9; }
  else if (mode == 0x01654c04u) { table = (const u32*)0x01481d28; n = 0x0b; }
  else if (mode == 0x01654c05u) { table = (const u32*)0x01481d54; n = 0x0c; }
  else { table = (const u32*)0x01481cd4; n = 0x0c; }

  CString str;
  str.ctor();
  u32 idx;
  do {
    idx = G_RAND->RandomUint32Uniform(n);
  } while (idx == G_LAST_RANDOM);
  G_LAST_RANDOM = idx;
  str.Load(0x8c509d6cu, table[idx], 0);

  ((WndVt*)w1)->SetText(str.GetText());
  if (w2 != 0) ((WndVt*)w2)->SetText(str.GetText());

  Vec4_s00e3_8ce0 area;
  SPUIHelpers_GetMainWindowArea(&area);
  float h = area.w - area.y;

  float* r1 = (float*)((WndVt*)w1)->GetRect();
  float ry = r1[1];
  float rx = r1[0];
  float rz = r1[2];
  ((WndVt*)w1)->SetRect(h, ry);
  if (w2 != 0) ((WndVt*)w2)->SetRect(h, ry);

  float off = ((area.x - rz) - (rx - h)) * 0.5f;

  float t1 = SPUIHelpers_GetElapsedSeconds(self->f4c0, 2, w1, 0);
  AnimRaw_s00e3_8ce0 buf1;
  AnimRaw_s00e3_8ce0* a1 = SPUICreateWindowAnimationTargetPosition(&buf1, w1, off, ry, t1, 0.0f, 0);
  self->anim->AddAnimation(a1, w1, 0);

  if (w2 != 0) {
    AnimRaw_s00e3_8ce0 buf2;
    float t2 = SPUIHelpers_GetElapsedSeconds(self->f4c0, 2, w2, 0);
    AnimRaw_s00e3_8ce0* a2 = SPUICreateWindowAnimationTargetPosition(&buf2, w2, off, ry, t2, 0.0f, 0);
    self->anim->AddAnimation(a2, w2, 0);
  }

  FUN_00571e80(&self->sw4a8);
  ((WndVt*)w1)->SetVisible(1, 2);
  if (w2 != 0) ((WndVt*)w2)->SetVisible(1, 2);
  self->b4e8 = 1;
  str.dtor();
}

// @ 0x00e38fd0
void __fastcall FUN_00e38fd0(Timeline_s00e3_8ce0* self, void* dummy)
{
  (void)dummy;
  Wnd* w = self->p348->FindWindowByID(0x06456c48u, 1);
  if (self->anim == 0 || w == 0) return;

  self->anim->RemoveAnimation(w, -1);

  float* r = (float*)((WndVt*)w)->GetRect();
  float ry = r[1];
  float rx = r[0];
  float rz = r[2];
  ((WndVt*)w)->SetRect(-(rz - rx), ry);

  float t = SPUIHelpers_GetElapsedSeconds(self->f4c0, 1, w, 0);
  AnimRaw_s00e3_8ce0 buf;
  AnimRaw_s00e3_8ce0* a = SPUICreateWindowAnimationTargetPosition(&buf, w, -(rz - rx), ry, t, 0.0f, 0);
  self->anim->AddAnimation(a, w, 0);

  FUN_00571e80(&self->sw4a8);
}

// @ 0x00e390d0
void __fastcall FUN_00e390d0(Timeline_s00e3_8ce0* self, void* dummy)
{
  (void)dummy;
  Wnd* w = self->p348->FindWindowByID(0x064db520u, 1);
  ((WndVt*)w)->SetVisible(1, 1);
  if (self->anim == 0) return;

  self->anim->RemoveAnimation(w, -1);

  Vec4_s00e3_8ce0 area;
  SPUIHelpers_GetMainWindowArea(&area);
  Wnd* ref = self->p348->FindWindowByID(0x064d0819u, 1);
  float* rr = (float*)((WndVt*)ref)->GetRect();
  float ry = rr[1];
  float* r = (float*)((WndVt*)w)->GetRect();
  float rx = r[0];
  float rz = r[2];
  ((WndVt*)w)->SetRect(-(rz - rx), ry);

  float t = SPUIHelpers_GetElapsedSeconds(10.0f, 2, w, 0);
  AnimRaw_s00e3_8ce0 buf;
  AnimRaw_s00e3_8ce0* a = SPUICreateWindowAnimationTargetPosition(&buf, w, 10.0f, ry, t, 0.0f, 0);
  self->anim->AddAnimation(a, w, 0);

  FUN_00571e80(&self->sw530);
}

// @ 0x00e39200
void __fastcall FUN_00e39200(Timeline_s00e3_8ce0* self, void* dummy)
{
  (void)dummy;
  Wnd* w = self->p348->FindWindowByID(0x064db520u, 1);
  if (self->anim == 0 || w == 0) return;

  self->anim->RemoveAnimation(w, -1);

  Vec4_s00e3_8ce0 area;
  SPUIHelpers_GetMainWindowArea(&area);
  float* r = (float*)((WndVt*)w)->GetRect();
  float ry = r[1];
  float dx = -(area.z - area.x);
  ((WndVt*)w)->SetRect(dx, ry);

  float t = SPUIHelpers_GetElapsedSeconds(10.0f, 1, w, 0);
  AnimRaw_s00e3_8ce0 buf;
  AnimRaw_s00e3_8ce0* a = SPUICreateWindowAnimationTargetPosition(&buf, w, dx, ry, t, 0.0f, 0);
  self->anim->AddAnimation(a, w, 0);

  FUN_00571e80(&self->sw530);
}

// @ 0x00e39300
void __fastcall FUN_00e39300(Timeline_s00e3_8ce0* self, void* dummy, s32 v)
{
  (void)dummy;
  for (s32 addr = 0x015a5a54; addr < 0x015a5a68; addr += 4) {
    Wnd* w = (Wnd*)self->p348->FindWindowByID(*(u32*)addr, 1);
    if (w != 0) ((WndVt*)w)->SetVisible(1, v);
  }
}

// @ 0x00e39350
void __fastcall FUN_00e39350(Timeline_s00e3_8ce0* self, void* dummy, s32 v)
{
  (void)dummy;
  for (u32 i = 0; i < self->n488; ++i) {
    Wnd* w = (Wnd*)self->p348->FindWindowByID(0x05db9a70u + i, 1);
    if (w != 0) ((WndVt*)w)->SetVisible(1, v);
  }
}

// @ 0x00e393b0
s32 __fastcall FUN_00e393b0(Timeline_s00e3_8ce0* self, void* dummy)
{
  (void)dummy;
  if (self->b370 != 0) goto ret1;
  if (self->p30 != 0 && self->p30->IsVisible() != 0) goto ret1;
  return 0;
ret1:
  return 1;
}

// @ 0x00e393e0
void FUN_00e393e0(void* node, s32 idx, Vec3* v)
{
  if (node == 0) return;
  ((IVec*)node)->data[idx]     = *(u32*)&v->y;
  ((IVec*)node)->data[idx + 1] = *(u32*)&v->x;
  ((IVec*)node)->data[idx + 2] = *(u32*)&v->z;
}

// @ 0x00e39420
void FUN_00e39420(void* node, s32 idx, Vec3* v)
{
  if (node == 0) return;
  *(u32*)&v->y = ((IVec*)node)->data[idx];
  *(u32*)&v->x = ((IVec*)node)->data[idx + 1];
  *(u32*)&v->z = ((IVec*)node)->data[idx + 2];
}

// @ 0x00e39450
void FUN_00e39450(void* node, void* key1, void* key2)
{
  AssetOwner* owner = (AssetOwner*)FUN_0067cb30();
  AssetDir* dir = owner->dir;
  if (dir == 0) return;

  u64_s00e3_8ce0 id = (u64_s00e3_8ce0)-1;
  if (dir->GetServerId(key1, &id, 0) && id != (u64_s00e3_8ce0)-1) {
    ((IVec*)node)->data[3] = ((u32*)&id)[1];
    ((IVec*)node)->data[4] = ((u32*)&id)[0];
  }
  if (dir->GetServerId(key2, &id, 0) && id != (u64_s00e3_8ce0)-1) {
    ((IVec*)node)->data[5] = ((u32*)&id)[1];
    ((IVec*)node)->data[6] = ((u32*)&id)[0];
  }
}

// @ 0x00e394f0
IVec* FUN_00e394f0(u32 id, Vec3* p2, Vec3* p3, Vec3* p4, Vec3* p5)
{
  IVec* first = 0;
  u8 b1 = (SP_GetCurrentGameMode_s00e3_8ce0() == (void*)0x01654c00) ||
          (SP_GetCurrentGameMode_s00e3_8ce0() == (void*)0x00dbdba1);

  Pool* pool = (Pool*)FUN_0067de90_s00e3_8ce0();
  if (pool == 0) goto done;

  first = pool->New(0x0c, 0);
  first->resize(0x1b);

  ((IVec*)first)->data[0] = id;
  float t = b1 ? Time_SourceLevel() : RandomFloatRange(-0.15f, 0.15f);
  *(float*)&((IVec*)first)->data[1] = t;
  ((IVec*)first)->data[2] = b1 ? (u32)(Time_Current() / 1000) : NowMs();

  ((IVec*)first)->data[3] = *(u32*)&p2->y;
  ((IVec*)first)->data[4] = *(u32*)&p2->x;
  ((IVec*)first)->data[5] = *(u32*)&p2->z;
  ((IVec*)first)->data[6] = *(u32*)&p3->y;
  ((IVec*)first)->data[7] = *(u32*)&p3->x;
  ((IVec*)first)->data[8] = *(u32*)&p3->z;
  ((IVec*)first)->data[0x10] = *(u32*)&p4->y;
  ((IVec*)first)->data[0x11] = *(u32*)&p4->x;
  ((IVec*)first)->data[0x12] = *(u32*)&p4->z;
  ((IVec*)first)->data[0x0d] = *(u32*)&p5->y;
  ((IVec*)first)->data[0x0e] = *(u32*)&p5->x;
  ((IVec*)first)->data[0x0f] = *(u32*)&p5->z;

  IVec* second = pool->New(6, 0);
  second->resize(0x18);
  ((IVec*)second)->data[0] = id;
  *(float*)&((IVec*)second)->data[1] = t;
  ((IVec*)second)->data[2] = b1 ? (u32)(Time_Current() / 1000) : NowMs();

  FUN_00e39450(second, p2, p3);
  ((IVec*)second)->data[0x0e] = *(u32*)&p4->y;
  ((IVec*)second)->data[0x0f] = *(u32*)&p4->x;
  ((IVec*)second)->data[0x10] = *(u32*)&p4->z;
  ((IVec*)second)->data[0x0b] = *(u32*)&p5->y;
  ((IVec*)second)->data[0x0c] = *(u32*)&p5->x;
  ((IVec*)second)->data[0x0d] = *(u32*)&p5->z;

done:
  return first;
}

// @ 0x00e39710
IVec* FUN_00e39710(u32 id, Vec3* p2, Vec3* p3, Vec3* p4, Vec3* p5)
{
  IVec* first = 0;
  u8 b1 = (SP_GetCurrentGameMode_s00e3_8ce0() == (void*)0x01654c01) ||
          (SP_GetCurrentGameMode_s00e3_8ce0() == (void*)0x00dbdba1);

  Pool* pool = (Pool*)FUN_0067de90_s00e3_8ce0();
  if (pool == 0) goto done;

  first = pool->New(0x0c, 0);
  first->resize(0x1b);

  ((IVec*)first)->data[0] = id;
  float t = b1 ? Time_TimelineForest() : RandomFloatRange(-0.15f, 0.15f);
  *(float*)&((IVec*)first)->data[1] = t;
  ((IVec*)first)->data[2] = NowMs();

  ((IVec*)first)->data[3] = *(u32*)&p2->y;
  ((IVec*)first)->data[4] = *(u32*)&p2->x;
  ((IVec*)first)->data[5] = *(u32*)&p2->z;
  ((IVec*)first)->data[6] = *(u32*)&p3->y;
  ((IVec*)first)->data[7] = *(u32*)&p3->x;
  ((IVec*)first)->data[8] = *(u32*)&p3->z;
  ((IVec*)first)->data[0x10] = *(u32*)&p4->y;
  ((IVec*)first)->data[0x11] = *(u32*)&p4->x;
  ((IVec*)first)->data[0x12] = *(u32*)&p4->z;
  ((IVec*)first)->data[0x0d] = *(u32*)&p5->y;
  ((IVec*)first)->data[0x0e] = *(u32*)&p5->x;
  ((IVec*)first)->data[0x0f] = *(u32*)&p5->z;

  IVec* second = pool->New(6, 0);
  second->resize(0x18);
  ((IVec*)second)->data[0] = id;
  *(float*)&((IVec*)second)->data[1] = t;
  ((IVec*)second)->data[2] = NowMs();

  FUN_00e39450(second, p2, p3);
  ((IVec*)second)->data[0x0e] = *(u32*)&p4->y;
  ((IVec*)second)->data[0x0f] = *(u32*)&p4->x;
  ((IVec*)second)->data[0x10] = *(u32*)&p4->z;
  ((IVec*)second)->data[0x0b] = *(u32*)&p5->y;
  ((IVec*)second)->data[0x0c] = *(u32*)&p5->x;
  ((IVec*)second)->data[0x0d] = *(u32*)&p5->z;

done:
  return first;
}

// @ 0x00e398e0
IVec* FUN_00e398e0(u32 id, Vec3* p2, Vec3* p3, Vec3* p4, u32 v1, u32 v2, u32 v3)
{
  IVec* first = 0;
  u8 b1 = (SP_GetCurrentGameMode_s00e3_8ce0() == (void*)0x01654c02) ||
          (SP_GetCurrentGameMode_s00e3_8ce0() == (void*)0x00dbdba1);

  Pool* pool = (Pool*)FUN_0067de90_s00e3_8ce0();
  if (pool == 0) goto done;

  first = pool->New(0x0c, 0);
  first->resize(0x1b);

  ((IVec*)first)->data[0] = id;
  float t = b1 ? Time_TimelineSpace() : RandomFloatRange(-0.15f, 0.15f);
  *(float*)&((IVec*)first)->data[1] = t;
  ((IVec*)first)->data[2] = NowMs();

  ((IVec*)first)->data[3] = *(u32*)&p2->y;
  ((IVec*)first)->data[4] = *(u32*)&p2->x;
  ((IVec*)first)->data[5] = *(u32*)&p2->z;
  ((IVec*)first)->data[6] = *(u32*)&p3->y;
  ((IVec*)first)->data[7] = *(u32*)&p3->x;
  ((IVec*)first)->data[8] = *(u32*)&p3->z;
  ((IVec*)first)->data[0x10] = *(u32*)&p4->y;
  ((IVec*)first)->data[0x11] = *(u32*)&p4->x;
  ((IVec*)first)->data[0x12] = *(u32*)&p4->z;
  ((IVec*)first)->data[0x0b] = v1;
  ((IVec*)first)->data[0x0c] = v2;
  ((IVec*)first)->data[0x1a] = v3;

  IVec* second = pool->New(6, 0);
  second->resize(0x18);
  ((IVec*)second)->data[0] = id;
  *(float*)&((IVec*)second)->data[1] = t;
  ((IVec*)second)->data[2] = NowMs();

  FUN_00e39450(second, p2, p3);
  ((IVec*)second)->data[0x0e] = *(u32*)&p4->y;
  ((IVec*)second)->data[0x0f] = *(u32*)&p4->x;
  ((IVec*)second)->data[0x10] = *(u32*)&p4->z;
  ((IVec*)second)->data[9]  = v1;
  ((IVec*)second)->data[0x0a] = v2;
  ((IVec*)second)->data[0x17] = v3;

done:
  return first;
}

// @ 0x00e39de0
void KeyValue::ApplyTo(ChangeMessage* msg)
{
    if (msg->mpPayload->mFirst.m1 == mKey0
        && msg->mpPayload->mFirst.m0 == mKey1
        && msg->mpPayload->mFirst.m2 == mKey2) {
        msg->mpPayload->mFirst.m0 = mVal1;
        msg->mpPayload->mFirst.m1 = mVal0;
        msg->mpPayload->mFirst.m2 = mVal2;
    }
    if (msg->mpPayload->mSecond.m1 == mKey0
        && msg->mpPayload->mSecond.m0 == mKey1
        && msg->mpPayload->mSecond.m2 == mKey2) {
        msg->mpPayload->mSecond.m0 = mVal1;
        msg->mpPayload->mSecond.m1 = mVal0;
        msg->mpPayload->mSecond.m2 = mVal2;
    }
}

// @ 0x00e39e60
bool IntPropertyBinding::SetValue(IPropertyList* pList)
{
    Variant* pValue;
    if (!pList->GetProperty(mPropertyId, &pValue))
        return false;
    uint16_t type = pValue->mTypeId;
    uint32_t* pData;
    if (type == 9 || type == 0x10)
        pData = (pValue->mFlags & 0x30) ? pValue->mpData
              : (uint32_t*)((type != 0 ? -1 : 0) & (int32_t)pValue);
    else
        pData = &g_variantIntDefault;
    int32_t value = (int32_t)*pData;
    if (mValue != value) {
        mValue = value;
        return true;
    }
    return false;
}

// @ 0x00e3a000
void EvalCatmullRom2D(float* pOut, const float* p0, const float* p1, const float* p2, const float* p3, float t)
{
    pOut[0] = (2.0f * p1[0] + (p2[0] - p0[0]) * t
               + (2.0f * p0[0] - 5.0f * p1[0] + 4.0f * p2[0] - p3[0]) * t * t
               + (p3[0] - p0[0] + 3.0f * p1[0] - 3.0f * p2[0]) * t * t * t) * 0.5f;
    pOut[1] = (2.0f * p1[1] + (p2[1] - p0[1]) * t
               + (2.0f * p0[1] - 5.0f * p1[1] + 4.0f * p2[1] - p3[1]) * t * t
               + (p3[1] - p0[1] + 3.0f * p1[1] - 3.0f * p2[1]) * t * t * t) * 0.5f;
}

// @ 0x00e3a230
int cBigEditorObject::GetDrawPriority()
{
    bool bVisible = mFlag36c || (mSub24.mpLayout && mSub24.mpLayout->IsVisible());
    return bVisible ? 0x87 : 0;
}

// @ 0x00e3a270
void cBigEditorObject::OnChange(uint32_t messageId, ChangeMessage* msg)
{
    switch (messageId) {
    case 0xaaf6aaac:
    case 0xdca976d0:
    case 0x99f0d1da:
        m324 = msg->mpPayload->mValue;
        FUN_00e39420(msg, 3, &mVecs[3]);
        return;

    case 0x9f792b4c:
        if (mGameMode == -1)
            mGameMode = 0x1654c05;
        if (m324 == 0)
            m324 = msg->mpPayload->mValue;
        m328 = msg->mpPayload->mValue;
        return;

    case 0xade76cce:
        if (mGameMode == -1)
            mGameMode = 0x1654c01;
        m310 = msg->mpPayload->mValue;
        return;

    case 0x279c4e55:
        if (mGameMode == -1)
            mGameMode = 0x1654c02;
        if (m314 == 0)
            m314 = msg->mpPayload->mValue;
        m318 = msg->mpPayload->mValue;
        return;

    case 0xf278934a:
    case 0x25ca9233:
    case 0x5c51063f:
        m314 = msg->mpPayload->mValue;
        mVecs[1].m1 = msg->mpPayload->mFirst.m0;
        mVecs[1].m0 = msg->mpPayload->mFirst.m1;
        mVecs[1].m2 = msg->mpPayload->mFirst.m2;
        return;

    case 0x8133fb2e:
    case 0x2cfa39dd:
    case 0x6a9f2620:
        m31c = msg->mpPayload->mValue;
        FUN_00e39420(msg, 3, &mVecs[2]);
        return;

    case 0xf967827c:
    case 0x13df9c1c:
    case 0x7115ede5:
        m30c = msg->mpPayload->mValue;
        FUN_00e39420(msg, 3, &mVecs[0]);
        return;

    case 0x980e43f2:
    case 0xa0973374:
    case 0xa6cb4c9f:
    case 0xd832b059:
    case 0xcdb3696f:
    case 0xd536c91d:
    case 0xe0bc9d45:
    case 0x6cd9ec7b:
    case 0x5fcf28d0:
    case 0x7bceaa86:
        if (msg) {
            mVecs[4].m1 = msg->mpPayload->mFirst.m0;
            mVecs[4].m0 = msg->mpPayload->mFirst.m1;
            mVecs[4].m2 = msg->mpPayload->mFirst.m2;
        }
        return;

    case 0x3e2a3040:
        mGameMode = 0x1654c00;
        m308 = msg->mpPayload->mValue;
        return;

    case 0x3b38f92a:
        if (mGameMode == -1)
            mGameMode = 0x1654c04;
        if (m31c == 0)
            m31c = msg->mpPayload->mValue;
        m320 = msg->mpPayload->mValue;
        return;
    }
}

// @ 0x00e3a570
void ClampToCirclePair(float* pOut, float x, float y, const float* c, float r1, const float* d, float r2, float sgn)
{
    float yA = y;
    float dxA = x - c[0];
    float dyA = y - c[1];
    if (r1 * r1 >= dxA * dxA + dyA * dyA)
        yA = c[1] + sgn * sqrtf(r1 * r1 - dxA * dxA);

    float yB = y;
    float dxB = x - d[0];
    float dyB = y - d[1];
    if (r2 * r2 >= dxB * dxB + dyB * dyB)
        yB = d[1] + sgn * sqrtf(r2 * r2 - dxB * dxB);

    float ptA[2] = { x, yA };
    float ptB[2] = { x, yB };

    const float* pSrc;
    if (sgn >= 0.0f)
        pSrc = (yA > yB) ? ptA : ptB;
    else
        pSrc = (yB > yA) ? ptA : ptB;

    pOut[0] = pSrc[0];
    pOut[1] = pSrc[1];
}

// @ 0x00e3a6b0
bool CreateAndBindEditorImage(void* pHost, void* pKey)
{
    if (pHost != 0) {
        IEditorData* pData = ((IEditorHost*)pHost)->GetEditorData();
        if (pData != 0) {
            IImageOwner* pOwner = (IImageOwner*)pData->FindService(0xef3c47cf);
            if (pOwner != 0) {
                void* pImage = 0;
                CreateImageFromResource2(pKey, &pImage, 0, -1, -1);
                if (pImage != 0) {
                    pOwner->SetImage(pImage);
                    if (pImage)
                        ((Image*)pImage)->Release();
                    return true;
                }
            }
        }
    }
    return false;
}

// @ 0x00e3a730
Image* cBigEditorObject::GetTerrainImage(uint32_t key, bool bRecompute)
{
    Image* pImage = 0;
    cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
    uint32_t index = 0;
    if (mTerrainKey.mGroupID == 0x2b978c46) {
        index = pSphere->GetTerrainIndex(key);
    } else {
        cCellRecord* pCell = mCells.mpEnd[-1];
        if (pCell)
            index = pCell->mTerrainKind;
    }
    if (bRecompute) {
        if (pSphere->mField1108)
            index = FUN_00556440(pSphere->mField10fc, pSphere->mField1100,
                                 pSphere->mField1104, pSphere->mField1108);
    }
    if (index) {
        int32_t n = TerrainKeyToIndex(key);
        if (void* pMem = operator new(0xa0, "UI", 0, 0, 0, 0)) {
            Image* pNewImage = ((Image*)pMem)->Init();
            if (pNewImage)
                pNewImage->AddRef();
            pImage = pNewImage;
        }
        void* pWindow = mpLayout30->FindWindowByID(n + 0x6299720, 1);
        UIVec3* pVec = &mVecs[n];
        if (pVec->m0 == 0) {
            pImage->Setup(pWindow, 1, 1);
            int colors[3] = { (int)index, 0xb1b104, 0xf865c777 };
            pImage->SetFlags(1, colors, 0);
        } else if (key == 0xa426730b) {
            pImage->BindA(pWindow, pVec, (int)index);
        } else {
            pImage->BindB(pWindow, pVec, key, (int)index);
        }
        if (bRecompute) {
            int colors[3] = { (int)index, 0xb1b104, 0xf865c777 };
            pImage->SetFlags(1, colors, 0);
        }
        RefPtrImage* pSlot = &mImages.mpBegin[n];
        Image* pOld = pSlot->mpObject;
        if (pImage != pOld) {
            if (pImage)
                pImage->AddRef();
            pSlot->mpObject = pImage;
            if (pOld)
                pOld->Release();
        }
        if (pImage)
            pImage->Release();
    }
    return pImage;
}

// @ 0x00e3a990
cTimelineTrack* cSPUITimeline_s00e3_a990::FindNextTrack(uint32_t nFlags, float* pProgress)
{
    (void)nFlags;
    (void)pProgress;
    return 0;
}

// @ 0x00e3aac0
cTimelineTrack* cSPUITimeline_s00e3_a990::FindPreviousTrack(uint32_t nFlags, float* pProgress)
{
    (void)nFlags;
    (void)pProgress;
    return 0;
}

// @ 0x00e3abf0
void cSPUITimeline_s00e3_a990::UpdateTransition(float fTime)
{
    (void)fTime;
}

// @ 0x00e3afb0
void cSPUITimeline_s00e3_a990::UpdateState()
{
    switch (mnState) {
    case 1:
        PlayClip(mpClip);
        mnState = 3;
        break;
    case 2:
        if (IsTimelineWindowReady()) {
            PlayClip(mpClip);
            mnState = 3;
        }
        break;
    case 3:
        if (IsTimelineWindowReady()) {
            mStopwatch.Restart();
            mnState = 4;
        }
        break;
    case 4:
        if (IsTimelinePlaybackDone()) {
            FinishTransition();
            mnState = 2;
        } else if (mbFadeActive) {
            if (mFadeDelay - mStopwatch.GetElapsedTimeFloat() <= mFadeTime) {
                cUIWindow* pWindow =
                    mpLeftLayout->FindWindowByID(0x6456c48, 1);
                pWindow->SetVisible(2, 0);
                mbFadeActive = false;
            }
        }
        break;
    default:
        break;
    }
}

// @ 0x00e3b0b0
bool cSPUITimeline_s00e3_a990::ShowNextPlayItem()
{
    bool bResult = false;

    if (mnPlayIndex < mnPlayItemCount) {
        mPlayItems[mnPlayIndex]->SetVisible(1, 1);
        UpdatePlayback();
        ++mnPlayIndex;
        bResult = true;
    }
    return bResult;
}

// @ 0x00e3b0f0
void cSPUITimeline_s00e3_a990::StartPlayback()
{
    mnPlayIndex = 0;
    ResetClip();
    SetRunning(1);
    InitGonzagoSubsystem(1);
    if (mpClip != (void*)0x1654c10)
        mnMode = 1;
    mbTimerReset = false;
    if (mnTimerMode == 1) {
        mnTimerStartLow = 0;
        mnTimerStartHigh = 0;
    } else {
        mnTimerStartLow = 0;
        mnTimerStartHigh = 0;
    }
    mnTimerEndLow = 0;
    mnTimerEndHigh = 0;
    mnState = 1;
}

// @ 0x00e3b180
void cSPUITimeline_s00e3_a990::RestorePlayback()
{
    SetRunning(0);
    cUIWindow* pWindow = mpLeftLayout->FindWindowByID(0x64d29c0, 1);
    if (pWindow != 0)
        pWindow->SetVisible(1, 0);
    if (IsWorldLayoutFlagSet(2)) {
        pWindow = mpRightLayout->FindWindowByID(0x64d29c0, 1);
        if (pWindow != 0)
            pWindow->SetVisible(1, 0);
    }
    mpAnimator->ClearAll();
}

// @ 0x00e3b1f0
void cSPUITimeline_s00e3_a990::HidePanels()
{
    SetRunning(0);
    mpAnimator->ClearAll();
    mnMode = 12;
    cUIWindow* pWindow = mpLeftLayout->FindWindowByID(0x64d29c0, 1);
    pWindow->SetVisible(1, 1);
    InitGonzagoSubsystem(0);
    mbExtraReset = false;
    if (mnExtraMode == 1) {
        mnExtraStartLow = 0;
        mnExtraStartHigh = 0;
        mnExtraEndLow = 0;
        mnExtraEndHigh = 0;
    } else {
        mnExtraStartLow = 0;
        mnExtraStartHigh = 0;
        mnExtraEndLow = 0;
        mnExtraEndHigh = 0;
    }
}

// @ 0x00e3b2a0
bool cSPUITimeline_s00e3_a990::LoadImage(cUIWindow* pWindow, void* pResource)
{
    (void)pWindow;
    (void)pResource;
    return false;
}

// @ 0x00e3b390
bool cSPUITimeline_s00e3_a990::HandleMessage(void* pMessage)
{
    (void)pMessage;
    return false;
}

// @ 0x00e3b5d0
uint32_t cSPUITimeline_s00e3_a990::GetSelectedPaletteId()
{
    return mnCachedPaletteId;
}

// @ 0x00e3b630
bool IsPaletteIdPresent(uint32_t nId)
{
    (void)nId;
    return false;
}

// @ 0x00e3b670
void InsertTrackRef(void* pResult, void* pParent, const void* pValue, bool bLeft)
{
    (void)pResult;
    (void)pParent;
    (void)pValue;
    (void)bLeft;
}

// @ 0x00e3b700
void InsertTrackPoint(void* pResult, void* pParent, const void* pValue, bool bLeft)
{
    (void)pResult;
    (void)pParent;
    (void)pValue;
    (void)bLeft;
}

// @ 0x00e3b790
void InsertTrackRect(void* pResult, void* pParent, const void* pValue, bool bLeft)
{
    (void)pResult;
    (void)pParent;
    (void)pValue;
    (void)bLeft;
}

// @ 0x00e3b9e0
void cUIManager::FUN_00e3b9e0(int dt)
{
    MEM(int, 0x288) -= dt;
    int iVar5 = MEM(int, 0x288);

    float scratch;
    switch (MEM(int, 0x284))
    {
    case 1:
    {
        int iVar5b = *(int*)(MEM(unsigned int, 0x188) - 4);
        if (iVar5b != 0 && *(int*)(iVar5b + 0xf0) != 0)
        {
            if (MEM(char, 0x27c) != 0)
                return;

            U3 col;
            switch (SP_GetCurrentGameMode_s00e3_b9e0())
            {
            case 0x1654c00: col.x = g_15a5984[0]; col.y = g_15a5984[1]; col.z = g_15a5984[2]; break;
            case 0x1654c01: col.x = g_15a5984[3]; col.y = g_15a5984[4]; col.z = g_15a5984[5]; break;
            case 0x1654c02: col.x = g_15a5984[6]; col.y = g_15a5984[7]; col.z = g_15a5984[8]; break;
            case 0x1654c04: col.x = g_15a5984[9]; col.y = g_15a5984[10]; col.z = g_15a5984[11]; break;
            default: goto label_1654c03;
            }
            V3 v3;
            v3.x = -1.0f; v3.y = -1.0f; v3.z = 0.0f;
            ((cSPHintMgr*)FUN_0067caf0())->FUN_0067aaf0(col, &PTR_PTR_015a59b4, 0, v3, 0, 0);
            MEM(char, 0x27c) = 1;
        }
    label_1654c03:
        if (MEM(char, 0x27c) == 0)
        {
            MEM(int, 0x284) = 2;
            return;
        }
        break;
    }
    case 2:
        if (MEM(unsigned int, 0x5c) != 0)
            ((void(__thiscall*)(void*, int, int))(*(unsigned int**)(char*)MEM(void*, 0x5c))[0x7c / 4])((void*)MEM(unsigned int, 0x5c), 2, 1);
        {
            float v = MEM(float, 0x28c) - (MEM(float, 0x98) + 1.0f);
            scratch = 0.0f;
            float* picked = &scratch;
            if (v > 0.0f) picked = &v;
            MEM(float, 0x28c) = *picked;
        }
        if (MEM(unsigned int, 0x3c) != 0)
        {
            void* o = (void*)MEM(unsigned int, 0x3c);
            float* pf = (float*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)o)[0x38 / 4])(o);
            float v = MEM(float, 0x28c) - (pf[2] - pf[0]) * DAT_016acde0;
            scratch = 0.0f;
            float* picked = &scratch;
            if (v > 0.0f) picked = &v;
            MEM(float, 0x270) = *picked;
            MEM(float, 0x290) = *picked;
        }
        MEM(unsigned int, 0x288) = DAT_016acd90;
        MEM(int, 0x284) = 3;
        return;
    case 3:
        if (iVar5 < 1)
        {
            MEM(unsigned int, 0x288) = DAT_016acda0;
            MEM(int, 0x284) = 4;
            return;
        }
        break;
    case 4:
        MEM(float, 0x270) = ((float)(DAT_016acda0 - iVar5) / (float)DAT_016acda0) *
                            (MEM(float, 0x28c) - MEM(float, 0x290)) + MEM(float, 0x290);
        if (iVar5 < 1)
        {
            if (MEM(unsigned int, 0x5c) != 0)
                ((void(__thiscall*)(void*, int, int))(*(unsigned int**)(char*)MEM(void*, 0x5c))[0x7c / 4])((void*)MEM(unsigned int, 0x5c), 2, 0);
            MEM(unsigned int, 0x288) = DAT_016acdb0;
            MEM(int, 0x284) = 5;
            return;
        }
        break;
    case 5:
        if (0 < iVar5)
            return;
        {
            int i = *(int*)(MEM(unsigned int, 0x188) - 4);
            if (i != 0 && *(int*)(i + 0xf0) != 0)
            {
                void* r = FUN_00e3a730(*(unsigned int*)(i + 0xe4), 0);
                if (r != 0)
                    FUN_00677360(1);
                MEM(unsigned int, 0x288) = DAT_016acdc0;
                MEM(int, 0x284) = 6;
                return;
            }
        }
        goto label_00e3bddf;
    case 6:
        if (0 < iVar5)
            return;
        {
            int i = *(int*)(MEM(unsigned int, 0x188) - 4);
            unsigned int id = (i != 0) ? *(unsigned int*)(i + 0xe4) : 0xa426730bu;
            int idx = FUN_00e36f50(id);
            if (*(int*)(MEM(unsigned int, 0x198) + idx * 4) != 0)
                FUN_00677360(0);
            if (i != 0 && *(unsigned int*)(i + 0xe4) == 0xbeb528cbu)
            {
                void* r = FUN_00e3a730(0x2db6dad3u, 1);
                if (r != 0)
                    FUN_00677360(1);
                MEM(unsigned int, 0x288) = DAT_016acdd0;
                MEM(int, 0x284) = 7;
                return;
            }
        }
        goto label_00e3bddf;
    case 7:
        if (0 < iVar5)
            return;
        if (*(int*)(MEM(unsigned int, 0x198) + 0x10) != 0)
            FUN_00677360(0);
    label_00e3bddf:
        MEM(int, 0x284) = 8;
        break;
    default:
        break;
    }
}

// @ 0x00e3be20
void cUIManager::FUN_00e3be20(unsigned int p2, float a, float b, float c, float d, float e, float f, float g, float h, float i, char p8)
{
    if ((g_16acc84 & 1) == 0) g_16acc84 |= 1;
    if ((g_16acc84 & 2) == 0) g_16acc84 |= 2;
    if ((g_16acc84 & 4) == 0) g_16acc84 |= 4;
    if ((g_16acc84 & 8) == 0) g_16acc84 |= 8;

    void* o = (void*)MEM(unsigned int, 0x54);
    unsigned int vt = *(unsigned int*)o;
    void* (__thiscall* f1)(void*, float, float) =
        (void*(__thiscall*)(void*, float, float))(*(unsigned int**)(char*)o)[0xc4 / 4];

    float* r1 = (float*)f1(o, a, b);
    g_16acc7c = r1[0]; g_16acc80 = r1[1];
    float* r2 = (float*)f1(o, c, d);
    g_16acc74 = r2[0]; g_16acc78 = r2[1];
    float* r3 = (float*)f1(o, e, f);
    g_16acc6c = r3[0]; g_16acc70 = r3[1];
    float* r4 = (float*)f1(o, g, h);
    g_16acc64 = r4[0]; g_16acc68 = r4[1];

    FUN_00e37840(p2, g_16acc74, g_16acc78, g_16acc7c, g_16acc80, g_16acc6c, g_16acc70,
                 g_16acc64, g_16acc68);
    (void)i; (void)p8; (void)vt;
}

// @ 0x00e3c100
float cUIManager::FUN_00e3c100(float x)
{
    float local_4 = x;
    int iVar1 = FUN_00e3b5d0();
    if (iVar1 == (int)0xa7a9e952)
    {
        if (0.33333334f < x)
            return x - 1.3333334f;
        local_4 = x + 0.6666667f;
    }
    else if (iVar1 == 0x2500e82c)
    {
        if (x < -0.33333334f)
            return x + 1.3333334f;
        return x - 0.6666667f;
    }
    return local_4;
}

// @ 0x00e3c1a0
char cUIManager::FUN_00e3c1a0(unsigned int* p2, float* p3, unsigned int* p4, float* p5, unsigned int p6, unsigned int p7, char p8, float p9)
{
    Vector2 p2c, p3c, p4c, p5c;
    p2c.x = ((float*)p2)[0]; p2c.y = ((float*)p2)[1];
    p3c.x = p3[0];           p3c.y = p3[1];
    p4c.x = ((float*)p4)[0]; p4c.y = ((float*)p4)[1];
    p5c.x = p5[0];           p5c.y = p5[1];

    int iVar8 = 0x1e;
    float local_54 = (float)MEM(int, 0x280) / (float)DAT_016acf2c;
    int local_90 = 0x1e;
    char cVar4 = 0;

    if (p8 != 0)
    {
        cVar4 = FUN_00e38020(&p2c, &p3c, &p4c, &p5c, p7);
        if (cVar4 != 0)
        {
            local_90 = 0xf;
            iVar8 = 0xf;
        }
    }
    float local_a8 = p3c.x, local_a4 = p3c.y;
    int local_8c = 1;

    if (iVar8 != 0)
    {
        float local_60 = (float)iVar8;
        do
        {
            Vector2 obuf;
            float* pf = FUN_00e3a000(&obuf, &p2c, &p3c, &p4c, &p5c,
                                     (float)((double)local_8c / (double)local_60));
            float fVar1 = pf[0];
            float fVar2 = pf[1];
            if (MEM(unsigned int, 0x58) != 0 && MEM(unsigned int, 0x5c) != 0)
            {
                float fVar10;
                if (fVar1 == local_a8)
                    fVar10 = 0.0f;
                else
                    fVar10 = (MEM(float, 0x88) - local_a8) / (fVar1 - local_a8);
                float local_7c = (fVar1 - local_a8) * fVar10 + local_a8;
                float local_50 = (fVar2 - local_a4) * fVar10 + local_a4;

                void* o = (void*)MEM(unsigned int, 0x58);
                void* (__thiscall* vc4)(void*, float, float) =
                    (void*(__thiscall*)(void*, float, float))(*(unsigned int**)(char*)o)[0xc4 / 4];
                unsigned int tmp[2];
                vc4(o, local_7c, local_50);
                vc4(o, fVar1, fVar2);

                MEM(unsigned int, 0x24c) = tmp[0];
                if (local_a8 <= local_7c && local_7c <= fVar1)
                {
                    void* o2 = (void*)MEM(unsigned int, 0x5c);
                    unsigned int vtf = *(unsigned int*)o2;
                    float* puV = (float*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)o2)[0x38 / 4])(o2);
                    ((void(__thiscall*)(void*, float, unsigned int))(*(unsigned int**)(char*)vtf)[0x70 / 4])(o2, puV[0], tmp[1]);
                    MEM(float, 0x88) = local_7c;
                    MEM(float, 0x8c) = local_50;
                    MEM(char, 0x249) = 1;
                    iVar8 = local_90;
                }
            }

            float fVar10b = DAT_016acecc * p9;
            if (fVar1 != local_a8)
            {
                double ang = DAT_015a5890 - atan(fabs((fVar2 - local_a4) / (fVar1 - local_a8)));
                fVar10b = fVar10b / (float)sin(ang);
            }
            float fStack_80 = local_a4 + fVar10b;
            float fStack_74 = fVar2 - fVar10b;
            float fStack_6c = fVar2 + fVar10b;

            Vector2 t1, t2, t3, t4;
            float* r;
            r = FUN_00e3a570(&t1, local_a8, local_a4 - fVar10b, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, -1.0f);
            float fStack_48 = r[0], fStack_44 = r[1];
            r = FUN_00e3a570(&t2, local_a8, fStack_80, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, 1.0f);
            float uStack_84 = r[0], fStack_80b = r[1];
            r = FUN_00e3a570(&t3, fVar1, fStack_74, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, -1.0f);
            float uStack_78 = r[0], fStack_74b = r[1];
            r = FUN_00e3a570(&t4, fVar1, fStack_6c, &p3c, DAT_016acf0c, &p4c, DAT_016acf0c, 1.0f);
            float uStack_70 = r[0], fStack_6cb = r[1];
            float fStack_4c = fVar10b / DAT_016acecc;

            void* wm = SP_WindowManager();
            wm = (void*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)wm)[4 / 4])(wm);
            float* pf2 = (float*)((void*(__thiscall*)(void*))(*(unsigned int**)(char*)wm)[0x38 / 4])(wm);
            if (fStack_48 < (pf2[2] - pf2[0]) * local_54)
            {
                FUN_00e3be20(p6, fStack_48, fStack_44, uStack_84, fStack_80b, uStack_78,
                             fStack_74b, uStack_70, fStack_6cb, fStack_4c, p8);
            }
            local_8c = local_8c + 1;
            local_a8 = fVar1;
            local_a4 = fVar2;
        } while (local_8c <= iVar8);
    }
    return cVar4;
}

// @ 0x00e3c6f0
void FUN_00e3c6f0(char param_1, unsigned int param_2)
{
    void* iVar1 = FUN_00b3d410();
    if (iVar1 != 0)
    {
        unsigned char local_40_data[0x40];
        (void)local_40_data;
        *(unsigned int*)(local_40_data + 0x00) = 0;   // local_10
        *(unsigned int*)(local_40_data + 0x04) = 0;   // local_3c[0] xchg
        *(unsigned int*)(local_40_data + 0x08) = DAT_013eb844;
        *(unsigned int*)(local_40_data + 0x0c) = (param_1 != 0) ? 1u : 0u;
        *(unsigned int*)(local_40_data + 0x10) = 0;
        *(unsigned int*)(local_40_data + 0x14) = param_2;

        void* server = SP_MessageServer();
        // vcall slot 0x14: PostMessage(0x6256b62, &local, iVar1)
        struct { unsigned int vt; unsigned int data[0x40 / 4]; } msg;
        msg.vt = (unsigned int)(local_40_data + 4);
        ((void(__thiscall*)(void*, unsigned int, void*, void*))(*(unsigned int**)(char*)server)[0x14 / 4])
            (server, 0x06256b62u, &msg, iVar1);
        SlotMessage_Destruct(local_40_data);
    }
}

// @ 0x00e3c760
void FUN_00e3c760(void)
{
    void* p0 = FUN_0067de90();
    if (p0 != 0)
    {
        void* t = ((void*(__stdcall*)(int))FUN_0067de90)(0xc);
        ((void(__thiscall*)(void*))SP_cTelemetry_Reset)(t);
    }
    void* q = FUN_00b3d410();
    if (q != 0)
    {
        char* p = (char*)FUN_00b3d410();
        char* esi = p + 0x250;
        unsigned int v = *(unsigned int*)(p + 0x25c);
        ((void(__thiscall*)(void*, unsigned int))eastl_rbtree_DoNukeSubtree)(esi, v);
        *(int*)(esi + 8) = (int)(esi + 4);
        *(int*)(esi + 4) = (int)(esi + 4);
        *(int*)(esi + 0xc) = 0;
        *(char*)(esi + 0x10) = 0;
        *(int*)(esi + 0x14) = 0;
        *(int*)(p + 0x298) = 0;
    }
}

// @ 0x00e3d9e0
namespace ImageCursorProvider {
void CursorProvider::RemapCursorKeys(uint32_t key, CursorKeys keys)
{
    CursorMap& map = mCursorMap;
    CursorMap::Iterator it;
    map.find(it, key);

    if (it.mpNode == map.mpBuckets[map.mnBucketCount])
        return;

    CursorBucket* bucket = it.mpNode;
    for (CursorListNode* p = bucket->mAnchor.mpNext; p != &bucket->mAnchor; p = p->mpNext)
        keys.Apply(&p->mValue);
}
}  // namespace ImageCursorProvider

// @ 0x00e3eca0
float* ModelTree::WorldAt(const uint32_t* pKey)
{
    RBNodeBase* pAnchor = (RBNodeBase*)&mAnchor;
    RBNodeBase* pPos = pAnchor;
    RBNodeBase* pNode = mAnchor.mpParent;

    while (pNode != 0) {
        if (!(((WorldNode*)pNode)->mKey < *pKey)) {
            pPos = pNode;
            pNode = pNode->mpLess;
        } else {
            pNode = pNode->mpGreater;
        }
    }
    if (pPos != pAnchor && !(*pKey < ((WorldNode*)pPos)->mKey)) {
        return &((WorldNode*)pPos)->mWidth;
    }

    WorldPair value;
    value.mKey    = *pKey;
    value.mWidth  = value.mKeyValue;
    value.mHeight = value.mWidth;

    InsertPos pos = { pPos };
    WorldNode* pNew;
    InsertWorldPair(&pNew, pos, &value, false);
    return &pNew->mWidth;
}

// @ 0x00e3ed30
float* ModelTree::BoundsAt(const uint32_t* pKey)
{
    RBNodeBase* pAnchor = (RBNodeBase*)&mAnchor;
    RBNodeBase* pPos = pAnchor;
    RBNodeBase* pNode = mAnchor.mpParent;

    while (pNode != 0) {
        if (!(((BoundsNode*)pNode)->mKey < *pKey)) {
            pPos = pNode;
            pNode = pNode->mpLess;
        } else {
            pNode = pNode->mpGreater;
        }
    }
    if (pPos != pAnchor && !(*pKey < ((BoundsNode*)pPos)->mKey)) {
        return &((BoundsNode*)pPos)->mLeft;
    }

    BoundsPair value;
    value.mKey     = *pKey;
    value.mLeft    = value.mKeyValue;
    value.mTop     = value.mLeft;
    value.mRight   = value.mTop;
    value.mBottom  = value.mRight;

    InsertPos pos = { pPos };
    BoundsNode* pNew;
    InsertBoundsPair(&pNew, pos, &value, false);
    return &pNew->mLeft;
}

// @ 0x00e3ede0
void FUN_00e3ede0(KeyVector* pKeys)
{
    if (FUN_01021260() != 0) {
        ((ModelSelector*)FUN_00b3d480())->Select(pKeys);
        FUN_004f6b70(pKeys->begin(), pKeys->end());
        uint32_t* pLast = FUN_004f6830(pKeys->begin(), pKeys->end());
        pKeys->erase(pLast, pKeys->end());
    }
}

// @ 0x00e3f010
void cSPUILayoutManager_s00e3_eca0::PreloadModelBounds()
{
    KeyVector12  models  = { 0, 0, 0 };
    ResourceKey_s00e3_eca0  listKey = { 0x013f662c, 0x00b1b104, 0xe1d7164f };

    ((ModelManager*)EA_ResourceMan_GetManager())->GetModels(&models, &listKey, 0);

    ResetTree(m_worlds);
    ResetTree(m_bounds);

    cSPUILayout_s00e3_eca0 layout;

    int count = models.mpEnd - models.mpBegin;
    for (int i = 0; i < count; ++i) {
        ResourceKey_s00e3_eca0* pEntry = &models.mpBegin[i];
        Property*    pProp  = 0;
        if (!SP_PropertyManager()->GetProperty(pEntry->mType, pEntry->mGroup, &pProp))
            continue;

        uint32_t iKeyInstance = 0;
        if (!SP_GetPropertyAsKeyInstance(pProp, 0x34e3b684, &iKeyInstance))
            continue;

        if (FindInWorldTree(&m_worlds, &iKeyInstance) == (RBNodeBase*)&m_worlds.mAnchor)
            continue;

        ResourceKey_s00e3_eca0 layoutKey = { iKeyInstance, 0x0510a95b, g_layoutKeyGroup };
        layout.Init(layoutKey, true, 0x05b598fa);

        IWin_s00e3_eca0* pWindow = layout.FindWindowByID(0x94e2c6d2, 1);
        if (pWindow != 0) {
            float* pRect   = pWindow->GetRect();
            float  fWidth  = pRect[2] - pRect[0];
            float  fHeight = pRect[3] - pRect[1];

            float* pWorld = m_worlds.WorldAt(&iKeyInstance);
            pWorld[0] = fWidth;
            pWorld[1] = fHeight;

            float screenRect[4];
            SPUIHelpers_GetBoundingScreenRect(screenRect, pWindow, 1);

            float* pBounds = m_bounds.BoundsAt(&iKeyInstance);
            pBounds[0] = screenRect[0];
            pBounds[1] = screenRect[1];
            pBounds[2] = screenRect[2];
            pBounds[3] = screenRect[3];
        }
        layout.Shutdown(1);
    }
    layout.~cSPUILayout_s00e3_eca0();

    if (models.mpBegin != 0 && ((uint32_t*)models.mpBegin)[-1] != 0)
        operator_delete(models.mpBegin);
}

// @ 0x00e3f2a0
bool __fastcall FUN_00e3f2a0(cSPUILayoutManager_s00e3_eca0* pThis, int, ModelSelectionSource* pSource, cMWModel* pStart)
{
    uint32_t* pBudget = pSource->mpOwner + 2;
    if (pBudget == 0)
        return false;

    bool      bEnabled  = false;
    int       iLimit    = 0;
    int       iChosen   = 1;
    int       iIndex    = 2;
    int       iCountA   = 0;
    int       iCountB   = 0;
    uint32_t  iKey      = pSource->mKey;
    uint32_t  iTotal    = 0;
    Property* pProp     = 0;
    uint32_t  iEntryA   = 0;
    uint32_t  iEntryB   = 0;
    uint32_t  iKeyInst  = 0;
    float     fOther    = 0.0f;
    float     fHeight   = 0.0f;
    SizeKeyVector modelsA = { 0, 0, 0 };
    SizeKeyVector modelsB = { 0, 0, 0 };
    SizeKeyVector modelsC = { 0, 0, 0 };

    PropertyManager* pProps = SP_PropertyManager();
    pProps->GetProperty(iKey, 0xe1d7164f, &pProp);

    if (pProp != 0) {
        Property* pB = 0;
        pProps->GetPropertyByKey(iKey, 0x94f79745, (Property**)&iEntryA);
        if (pProp != 0 && pProps->GetPropertyByKey(iKey, 0xd53426dd, &pB)) {
            if (pB != 0 && pB->mValueType == 1)
                bEnabled = *pB->GetBool();
        }
        if (pProp != 0 && pProps->GetPropertyByKey(iKey, 0xd52d9182, &pB)) {
            if (pB != 0 && pB->mValueType == 9)
                iLimit = *pB->GetInt();
        }
    }

    SP_GetPropertyVector(pProp, 0xd52d9183, &iCountA, &modelsA);
    SP_GetPropertyVector(pProp, 0x066f843b, &iCountB, &modelsB);
    SP_GetPropertyAsKeyInstance(pProp, 0x34e3b684, &iKeyInst);

    fOther  = 0.0f;
    fHeight = 0.0f;
    if (bEnabled) {
        if (FindInWorldTree(&pThis->m_worlds, &iKeyInst) != (RBNodeBase*)&pThis->m_worlds.mAnchor)
            fHeight = pThis->m_worlds.WorldAt(&iKeyInst)[1];
        if (pThis->mpSelectionTarget != 0) {
            float* pRect = pThis->mpSelectionTarget->GetRect();
            fOther = pRect[3] - pRect[1];
        }
    }

    bool bAny = (iCountA > 0 || iLimit > 0 || iCountB > 0);

    ModelHash* pHash = (ModelHash*)FUN_0067de90();
    FUN_007eb100(pHash);
    cMWModel* pEnd = pHash->mpFirst;

    if (pStart != pEnd) {
        for (cMWModel* pNode = pStart; pNode != pEnd; pNode = pNode->mpNext) {
            KeyInstance* pInst     = pNode->mpKeyInstance;
            uint32_t     iModelKey = pInst->mId;
            uint32_t     iModelSize = pInst->mExtra;
            bool         bFlag     = false;
            bool         bFound    = false;

            if (bAny) {
                if (iLimit > 0 && *pBudget - iModelSize > (uint32_t)iLimit)
                    bFlag = true;
                for (int i = 0; i < iCountA; ++i) {
                    if (modelsA.mpBegin[i] == iModelKey) { bFlag = true; break; }
                }
                for (int i = 0; i < iCountB; ++i) {
                    if (modelsB.mpBegin[i] == iModelKey) { bFound = true; break; }
                }
                if (iCountB > 0 && !bFound)
                    bFlag = true;
            }
            if (bEnabled && iCountB == 0 && (float)iIndex * fHeight < fOther)
                goto Select;
            if (bFlag)
                goto Select;
            if (iModelKey != iKey && !bFound)
                continue;

        Select:
            ++iChosen;
            ++iIndex;
            iTotal += pNode->mSizeBudget;
            {
                uint32_t   iBucket = (uint32_t)pNode % pThis->m_keySet.mBucketCount;
                cMWModel** ppSlot  = (cMWModel**)&((cMWModel**)pThis->m_keySet.mppBuckets)[iBucket];
                cMWModel*  pCur    = *ppSlot;
                bool       bInSet  = false;
                for (; pCur != 0; pCur = pCur->mpNext) {
                    if (pCur == pNode) { bInSet = true; break; }
                }
                if (!bInSet)
                    FUN_00b41b90(&pThis->m_keySet, ppSlot, pNode, 0);
            }
            {
                uint32_t iModel = (uint32_t)pNode;
                modelsC.DoInsertKey4(modelsC.mpEnd, iModel);
            }
        }
    }

    FUN_00e48f30(pStart, pBudget, (uint32_t)iChosen, iTotal);
    FUN_00e47700(pThis, &modelsC);
    if (pProp != 0)
        pProp->Release();
    if (modelsC.mpBegin != 0 && ((uint32_t*)modelsC.mpBegin)[-1] != 0)
        operator_delete(modelsC.mpBegin);
    return true;
}

// @ 0x00e3f7a0
float __fastcall FUN_00e3f7a0(cSPUILayoutManager_s00e3_eca0* pThis, int, uint32_t iKey)
{
    if (iKey != 0xa426730b && iKey != 0xad56080c)
        return 0.0f;

    if (FindInBoundsTree(&pThis->m_boundsTree, &iKey) != (uint32_t*)&pThis->m_boundsTree.mAnchor)
        return *FUN_00be0790(&iKey);

    if (FUN_0067de90() == 0)
        return 0.0f;

    ModelHash* pHash = (ModelHash*)FUN_0067de90(0x0c);
    if (pHash == 0) {
        *FUN_00be0790(&iKey) = 0.0f;
        return 0.0f;
    }
    FUN_007eb100(pHash);

    cMWModel* pEnd = pHash->mpFirst;
    if (pEnd != 0) {
        for (cMWModel* pNode = pHash->mpFirst; pNode != pEnd; pNode = pNode->mpNext) {
            KeyInstance* pInst     = pNode->mpKeyInstance;
            uint32_t     iModelKey = pInst->mId;
            Property*    pProp     = 0;

            SP_PropertyManager()->GetProperty(iModelKey, 0xe1d7164f, &pProp);

            if (pProp != 0) {
                uint32_t iOtherKey = 0;
                SP_GetPropertyAsKeyInstance(pProp, 0x91ad064, &iOtherKey);
                if (iOtherKey == iKey) {
                    float fValue = FUN_00e37d70(pThis, pInst->mValue);
                    if (fValue < -g_flHeightLimit) fValue = -g_flHeightLimit;
                    if (fValue >  g_flHeightLimit) fValue =  g_flHeightLimit;
                    *FUN_00be0790(&iKey) = fValue;
                    pProp->Release();
                    return fValue;
                }
                pProp->Release();
            }
        }
    }
    *FUN_00be0790(&iKey) = 0.0f;
    return 0.0f;
}

// @ 0x00e40700
void TimelineView::Setup()
{
    FUN_00ddddf0(0x8c509d6c, 0);

    mAnimatorA = (Object_s00e4_0700*)cSPUIAnimator_ctor(EANew(0x20, "UI/cUITimeline/Animator"));

    if (g_appProperties != 0) {
        int64_t tmp = 0;
        char ok = ((AppPropertyList*)g_appProperties)->GetProperty(0x064a44a8, &tmp);
        if (ok && *(int16_t*)((int)tmp + 0x12) == 1)
            mFlag484 = *(uint8_t*)SP_GetPropertyAsKeyArray() != 0;
    }

    mAnimatorB = (Object_s00e4_0700*)cSPUIAnimator_ctor(EANew(0x20, "UI/cUITimeline/Animator"));

    CopyRange((int*)mVec458.begin, (int*)mVec458.end);
    CopyRange((int*)mVec46c.begin, (int*)mVec46c.end);

    if (!mFlag484) {
        mTileCount = 1;
    } else {
        float a[8];
        SPUI_GetMainWindowArea(a);
        int height = (int)(a[3] - a[1]);
        float b[8];
        SPUI_GetMainWindowArea(b);
        mTileCount = (b[2] - b[0] <= (float)height * 1.3333334f) ? 8 : 10;
    }

    FUN_00e3f010();
    if (*(int*)((char*)this + 0xb8) == 1) {
        uint64_t t = __rdtsc();
        mTimeLo = (uint32_t)t;
        mTimeHi = (uint32_t)(t >> 32);
    } else {
        int64_t qpc = 0;
        QueryPerformanceCounter(&qpc);
        mTimeLo = (uint32_t)qpc;
        mTimeHi = (uint32_t)(qpc >> 32);
    }
    mB0 = 0;
    mB4 = 0;

    Assign(mLayout, (cSPUILayout_s00e4_0700*)SPUI_CenterWindowInRect(
                        EANew(0x18, "UI/cUITimeline/mTimelineLayout")));
    mLayout->Init(g_key_timeline, 1, 0x8c509d6c);

    Assign(mAtlasedLayout, (cSPUILayout_s00e4_0700*)SPUI_CenterWindowInRect(
                               EANew(0x18, "UI/cUITimeline/mAtlasedIconsLayout")));
    mAtlasedLayout->Init(g_key_atlased, 1, 0x8c509d6c);
    mAtlasedLayout->SetVisibility(0);

    Assign(mWin30, mLayout->FindWindowByID(0xffffffff, true));
    Assign(mWin34, mLayout->FindWindowByID(0x54e504cd, true));
    Assign(mWin38, mLayout->FindWindowByID(0x54e53d9d, true));
    Assign(mWin3c, mLayout->FindWindowByID(0xf54a5ddc, true));
    Assign(mWin40, mLayout->FindWindowByID(0xd5543432, true));
    Assign(mWin4c, mLayout->FindWindowByID(0x06134392, true));
    Assign(mWin50, mLayout->FindWindowByID(0x75120794, true));
    Assign(mWin54, mLayout->FindWindowByID(0x061f0640, true));
    Assign(mWin58, mLayout->FindWindowByID(0x06119986, true));

    if (mWin58) {
        Point_s00e4_0700 org; org.x = 0.0f; org.y = 0.0f;
        Point_s00e4_0700 p = mWin58->ToGlobalCoordinates(org);
        mF70 = p.x;
        mF74 = p.y;
        const Rect_s00e4_0700* r = mWin58->GetRealArea();
        mF78 = r->x;
        mF7c = r->y;
    }
    if (mWin54) {
        Point_s00e4_0700 org; org.x = 0.0f; org.y = 0.0f;
        Point_s00e4_0700 p = mWin54->ToGlobalCoordinates(org);
        mF80 = p.x;
        mF84 = p.y;
    }

    IWindow_s00e4_0700* w = mLayout->FindWindowByID(0x064178c8, true);
    if (w) {
        const Rect_s00e4_0700* r = w->GetRealArea();
        mF88 = r->x;
        mF8c = r->y;
    }
    w = mLayout->FindWindowByID(0x064178d0, true);
    if (w) {
        const Rect_s00e4_0700* r = w->GetRealArea();
        mF90 = r->x;
        mF94 = r->y;
    }

    w = mLayout->FindWindowByID(0x75581f48, true);
    if (w)
        Assign(mImage6c, sGetWindowImage(w));

    SetupIconStrip();
    SetupColorWindows();
    SetupIconPairs();

    // register "find window by hash" slots (cell/creature/tribe/civ/space image sets)
    {
        static const uint32_t kHashes[5] = {
            0xa426730b, 0xad56080c, 0xf71fa311, 0xbeb528cb, 0x2db6dad3 };
        static const uint32_t kWindowIDs[5] = {
            0x74ed2970, 0x74ed2971, 0x74ed2972, 0x74ed2973, 0x74ed2974 };
        for (int i = 0; i < 5; ++i)
            Assign(*MapFindByHash(kHashes[i]),
                   (Object_s00e4_0700*)mLayout->FindWindowByID(kWindowIDs[i], true));
        uint32_t* z = MapFindIndex(0);
        *z = 0;
        for (int i = 0; i < 5; ++i)
            *MapFindIndex(kHashes[i]) = (uint32_t)(i + 1);
    }

    // icon strip: pair a control window with its detail window in a lookup
    {
        static const uint32_t kKey[5]   = { 0x74ed2970, 0x74ed2971, 0x74ed2972, 0x74ed2973, 0x74ed2974 };
        static const uint32_t kIconA[5] = { 0xb54a5880, 0xb54a5881, 0xb54a5882, 0xb54a5883, 0xb54a5884 };
        static const uint32_t kIconB[5] = { 0x60be2e0, 0x60be2e1, 0x60be2e2, 0x60be2e3, 0x60be2e4 };
        for (int i = 0; i < 5; ++i) {
            Object_s00e4_0700* key = (Object_s00e4_0700*)mLayout->FindWindowByID(kKey[i], true);
            if (key) key->AddRef();
            Assign(*MapFindByRef(key), (Object_s00e4_0700*)mLayout->FindWindowByID(kIconA[i], true));
            if (key) key->Release();
        }
        for (int i = 0; i < 5; ++i) {
            Object_s00e4_0700* img = (Object_s00e4_0700*)mLayout->FindWindowByID(kIconA[i], true);
            RefVecPush(&mPropVec, img);
            if (img) img->Release();
        }
        for (int i = 0; i < 5; ++i) {
            Object_s00e4_0700* key = (Object_s00e4_0700*)mLayout->FindWindowByID(kKey[i], true);
            if (key) key->AddRef();
            Assign(*MapFindByRef(key), (Object_s00e4_0700*)mLayout->FindWindowByID(kIconB[i], true));
            if (key) key->Release();
        }
        for (int i = 0; i < 5; ++i) {
            Object_s00e4_0700* key = (Object_s00e4_0700*)mLayout->FindWindowByID(kIconB[i], true);
            if (key) key->AddRef();
            Assign(*MapFindByRef(key), (Object_s00e4_0700*)mLayout->FindWindowByID(kKey[i], true));
            if (key) key->Release();
        }
    }

    // place the five event windows along the strip
    for (uint32_t id = 0x60be2e0; id < 0x60be2e5; ++id) {
        IWindow_s00e4_0700* win = mLayout->FindWindowByID(id, true);
        if (!win) continue;
        IWindow_s00e4_0700* parent = win->GetParent();
        if (!parent) continue;
        const Rect_s00e4_0700* pr = parent->GetRealArea();
        const Rect_s00e4_0700* r  = win->GetRealArea();
        float width = r->z - r->x;
        float slot = (float)(int)(id - 0x60be2e0) * 0.2f;
        float x = slot * width + 3.0f;
        if (id == 0x60be2e0) x += 3.0f;
        float y = (slot + 0.2f) * width - 3.0f;
        if (id == 0x60be2e4) y -= 3.0f;
        (void)pr;
        win->SetLayoutLocation(x, y);
    }

    SetupPalette();
    SetupTrackRows();
    RegisterMessages();
}

// @ 0x00e42100
void cRangePanel::Update()
{
    if (mpTarget40 == 0 || mpSource3c == 0)
        return;

    u32   key;
    float fMin;
    float fSpan;
    float fExtra;
    float fSlot;
    float fRange[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float msg[4];

    mpTarget40->r60(fRange);

    Refresh();

    Sub184* owner = mpHolder184->m00;
    fMin = 0.0f;
    if (owner != 0) {
        IRangeObj* p = owner->m1c;
        if (p != 0) {
            fRange[0] = p->r38()[0];
            fRange[0] = (fRange[0] < fMin) ? fRange[0] : fMin;
            fMin = fRange[0];
        }
    }

    float* t = mpTarget40->r38();
    fSpan = t[2] - t[0];

    Sub184* owner2 = mppOwner188[-1];
    if (owner2 != 0) {
        IRangeObj* p = owner2->m1c;
        if (p != 0) {
            fRange[0] = p->r38()[2];
            fRange[0] = (fRange[0] > fSpan) ? fRange[0] : fSpan;
            fSpan = fRange[0];
        }
    }

    fExtra = 0.0f;
    if (owner2 != 0 && owner2->mF0 == 0 && owner2->mE4 != 0x2db6dad3 && mpRange60 != 0) {
        key = owner2->mE4;
        fSlot = 0.0f;
        IRangeObj** slot = mKeyMap.Find(&key);
        if (*slot != 0)
            fSlot = (*slot)->r38()[2];
        float* q = mpRange60->r38();
        if (fSlot < q[2]) {
            if (fSlot > q[0])
                fExtra = fSlot - q[0];
        } else {
            fExtra = q[2] - q[0];
        }
    }

    float* t2 = mpTarget40->r38();
    msg[0] = t2[0];
    msg[1] = t2[1];
    msg[2] = t2[2];
    msg[3] = t2[3];
    msg[0] = fMin;
    msg[2] = (fSpan - fMin) + fExtra;
    mpTarget40->r6C(msg);

    float* sel = mpSource3c->r38();
    if (mpSlider58 != 0) {
        bool flag = (msg[2] - msg[0]) > (sel[2] - sel[0]) && GetCurrentGameMode() != &g_1654c05;
        mpSlider58->r7C(1, flag);
        if (mpStepArg != 0) {
            u64 r = Step(mpStepArg);
            Apply((u32)r, (u32)(r >> 32));
        }
    }

    float* t3 = mpTarget40->r38();
    float d = (t3[2] - t3[0]) - (sel[2] - sel[0]);
    m270 = d;
    m278 = d;
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
            Rect_s00e4_23a0 bounds;
            GetWindowBounds_00805fe0(&bounds, e->mpBoundsWindow);
            if (bSliderVisible && mMode != 3 && mMouseX >= bounds.x1 && bounds.x2 >= mMouseX &&
                e->ActiveControllerIndex_0098f940())
                f_00e372b0(f_00e36ff0(e));
        }
        if (e->mpIcon) {
            float left = e->mpIcon->ToGlobalCoordinates(Point_s00e4_23a0(e->mX, e->mY)).x;
            float right = e->mpIcon->ToGlobalCoordinates(Point_s00e4_23a0(e->mX + e->mWidth, e->mY + e->mHeight)).x;
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

    Rect_s00e4_23a0 clip = mpClipWindow ? mpClipWindow->GetRealArea() : Rect_s00e4_23a0();
    Rect_s00e4_23a0 area = mpScrollWindow ? mpScrollWindow->GetRealArea() : Rect_s00e4_23a0();

    if (mpSlider) {
        float overflow = (area.x2 - area.x1) - (clip.x2 - clip.x1);
        float limit = Min(mMaxScroll, overflow);
        float scroll = mScroll;
        Point_s00e4_23a0 pos;
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
            IWindow_s00e4_23a0* src = n->first;
            IWindow_s00e4_23a0* dst = n->second;
            if (src && dst) {
                dst->SetLayoutArea(src->GetRealArea());
                dst->SetFlag(1, (src->GetFlags() & 1) != 0);
            }
        }

        if (IWindow_s00e4_23a0* old = mpFirstVisible) { mpFirstVisible = 0; old->Release(); }
        if (IWindow_s00e4_23a0* old = mpLastVisible) { mpLastVisible = 0; old->Release(); }
        IWindow_s00e4_23a0* lastVisible = 0;
        for (IWindow_s00e4_23a0** it = mWindowsBegin; it != mWindowsEnd; ++it) {
            IWindow_s00e4_23a0* w = *it;
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
            Rect_s00e4_23a0 r = mpFirstVisible->GetRealArea();
            r.x1 = r.x1 - sScreenWidth;
            mpFirstVisible->SetLayoutArea(r);
            r = mpLastVisible->GetRealArea();
            r.x2 = r.x2 + sScreenWidth;
            mpLastVisible->SetLayoutArea(r);
        }
    }

    IWindow_s00e4_23a0* w0 = mpLayout->FindWindowByID_008105b0(0xf537d890, true);
    IWindow_s00e4_23a0* w1 = mpLayout->FindWindowByID_008105b0(0xf537d891, true);
    IWindow_s00e4_23a0* w2 = mpLayout->FindWindowByID_008105b0(0xf537d892, true);
    if (w0 && w1 && w2 && mpColorPicker) {
        mTargetColor[0][0] = ColorRGBA(mTargetColor[0][1].r, mTargetColor[0][1].g, mTargetColor[0][1].b, 0.0f);
        mTargetColor[1][0] = ColorRGBA(mTargetColor[1][1].r, mTargetColor[1][1].g, mTargetColor[1][1].b, 0.0f);
        mTargetColor[2][0] = ColorRGBA(mTargetColor[2][1].r, mTargetColor[2][1].g, mTargetColor[2][1].b, 0.0f);
        mpColorPicker->SetSelected_00e46210(0, 0);
        mpColorPicker->SetSelected_00e46210(1, 0);
        mpColorPicker->SetSelected_00e46210(2, 0);
        if ((mpSlider->GetFlags() & 1) && mbColorTracking) {
            Point_s00e4_23a0 g = mpSliderHandle->ToGlobalCoordinates(Point_s00e4_23a0(0.0f, 0.0f));
            Point_s00e4_23a0 l = mpClipWindow->ToLocalCoordinates(g);
            const Rect_s00e4_23a0& r = mpClipWindow->GetRealArea();
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

// @ 0x00e43270
void cTimelinePageHost::Update(uint32_t arg0, uint32_t)
{
    cSPPalettePageUI_s00e4_3270* page = (cSPPalettePageUI_s00e4_3270*)((char*)this - 8);
    page->Update(arg0);
}

// @ 0x00e43280
void cUITimelineSubsystem::Reset()
{
    m284 = 0;
    m28c = 0.0f;
    m290 = 0.0f;
    m294 = 0;

    if (m0a8 != 0) {
        cTimelineTrack_s00e4_3270* pOld = (cTimelineTrack_s00e4_3270*)(void*)m0a8;
        m0a8 = 0;
        pOld->Release();
    }
    if (m1c8 != 0)
        ((cTimelineTrack_s00e4_3270*)(void*)m1c8)->Flush();
    if (m1c8 != 0) {
        cTimelineTrack_s00e4_3270* pOld = (cTimelineTrack_s00e4_3270*)(void*)m1c8;
        m1c8 = 0;
        pOld->Release();
    }

    TraceVector* tracks = (TraceVector*)&m184;
    int nTracks = tracks->size();
    for (int i = 0; i < nTracks; ++i)
        tracks->mpBegin[i]->Flush();
    tracks->erase(tracks->mpBegin, tracks->mpEnd);

    TimelineEntry* entries = (TimelineEntry*)&m29c;
    for (int i = 0; i < 6; ++i) {
        entries[i].m00 = 0;
        entries[i].m04 = 0;
        entries[i].m08 = 0;
    }

    for (int i = 0; i < 6; ++i) {
        RefObject* pSlot = mRefVec198.mpBegin[i];
        if (pSlot != 0)
            pSlot->Slot24();
    }

    // fixed_vector::clear() followed by fixed_vector::resize(6), both inlined.
    mRefVec198.clear();
    if (mRefVec198.size() < 6) {
        RefObject* value = 0;
        mRefVec198.DoInsertValues(mRefVec198.mpEnd, 6 - mRefVec198.size(), value);
    } else {
        mRefVec198.erase(mRefVec198.mpBegin + 6, mRefVec198.mpEnd);
    }

    if (m05c != 0)
        ((TimelineHintSink*)(void*)m05c)->Notify(2, 0);

    if (m030 != 0) {
        m300 = -1;
        m304 = -1;
        m308 = 0;
        m30c = 0;
        m310 = 0;
        m314 = 0;
        m318 = 0;
        m31c = 0;
        m320 = 0;
        m324 = 0;
        m328 = 0;
        m32c = -1;
    }
}

// @ 0x00e434a0
void CollectSpeciesModelKeys(KeyVector_s00e4_3270* keys)
{
    cGameNounManager_s00e4_3270* pManager = NounManager_s00e4_3270();
    GameDataVector* nouns = static_cast<GameDataVector*>(pManager->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00accc30, (void*)0x00b1e500, (void*)0x01be418e));
    keys->reserve(nouns->count() + keys->size());
    cSpeciesProfile_s00e4_3270* avatarProfile = GetSpeciesManager()->GetAvatarProfile();
    for (cGameNoun** pNoun = nouns->mpBegin, ** pNounEnd = nouns->mpEnd; pNoun != pNounEnd;
         ++pNoun) {
        cSpeciesProfile_s00e4_3270* profile = (*pNoun)->mpProfile;
        if (profile != 0 && profile != avatarProfile)
            keys->push_back(profile->mModelKey);
    }
    SortKeys(keys->mpBegin, keys->mpEnd);
    ResourceKey_s00e4_3270* pNewEnd = UniqueKeys(keys->mpBegin, keys->mpEnd);
    keys->erase(pNewEnd, keys->mpEnd);
}

// @ 0x00e435c0
void CollectAllSpeciesModelKeys(KeyVector_s00e4_3270* keys)
{
    cGameNounManager_s00e4_3270* pManager = NounManager_s00e4_3270();
    GameDataVector* nouns = static_cast<GameDataVector*>(pManager->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00accc30, (void*)0x00b1e500, (void*)0x01be418e));
    keys->reserve(nouns->count() + keys->size());
    for (cGameNoun** pNoun = nouns->mpBegin, ** pNounEnd = nouns->mpEnd; pNoun != pNounEnd;
         ++pNoun) {
        cSpeciesProfile_s00e4_3270* profile = (*pNoun)->mpProfile;
        if (profile != 0)
            keys->push_back(profile->mModelKey);
    }
    if (gSimSingleton == 0)
        gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimSingleton();
    gSimSingleton->FUN_00cc5bc0(keys);
    SortKeys(keys->mpBegin, keys->mpEnd);
    ResourceKey_s00e4_3270* pNewEnd = UniqueKeys(keys->mpBegin, keys->mpEnd);
    keys->erase(pNewEnd, keys->mpEnd);
}

// @ 0x00e43710
void CollectCivilizationModelKeys(KeyVector_s00e4_3270* keys)
{
    if (GetActivePlanet() == 0)
        return;
    FUN_00b3d480(keys)->FUN_00acc800();
    cGameNounManager_s00e4_3270* pManager = NounManager_s00e4_3270();
    GameDataVector* nouns = static_cast<GameDataVector*>(pManager->GetGameDataVector(
        (void*)0x00b21080, (void*)0x00d3d420, (void*)0x00b236c0, (void*)0x00b1e500, (void*)0x018c816a));
    if (nouns->mpBegin != nouns->mpEnd) {
        cGameNoun* pCiv = *nouns->mpBegin;
        for (uint32_t i = 0; i < 7; ++i) {
            if (pCiv->HasProperty(gCreaturePropertyIDs[i]))
                keys->push_back(*pCiv->GetModelTypeKey(gCreaturePropertyIDs[i]));
        }
    }
    cTerrainSphere_s00e4_3270* pSphere = NounManager_s00e4_3270()->GetCurrentTerrainSphere();
    keys->push_back(pSphere->mKey1168);
    SortKeys(keys->mpBegin, keys->mpEnd);
    ResourceKey_s00e4_3270* pNewEnd = UniqueKeys(keys->mpBegin, keys->mpEnd);
    keys->erase(pNewEnd, keys->mpEnd);
}

// @ 0x00e44200
void cSPUITimeline_s00e4_4200::Show(int show)
{
    if (!show && !mpLayout->IsVisible())
        return;

    if (show != mpLayout->IsVisible()) {
        cSPUILayoutManager_s00e4_4200* mgr = SPUIHelpers_GetLayoutManager();
        if (show) {
            mgr->SetAllWorldsVisibility(false);
            mgr->SetLayerVisible(0x8c509d6c, true);
            mgr->SetLayerVisible(0x5b598f6, true);
            mgr->SetLayerVisible(0x5b598f7, true);
        } else {
            mgr->SetLayerVisible(0x8c509d6c, false);
            mgr->SetLayerVisible(0x5b598f6, false);
            mgr->SetLayerVisible(0x5b598f7, false);
            mgr->SetAllWorldsVisibility(true);
        }
    }
    mpLayout->SetVisibility(show);

    if (show) {
        IAudioSystem_s00e4_4200* audio = EA_Audio_GetSystemAT();
        SP_KillSetiEffects(0x6d093bee, audio ? audio->GetListener() : 0);
        SPUIHelpers_BeginModal(mpModalOwner, 0, 0);
        SP_MessageServer_s00e4_4200()->BeginModal(0x4a07018, 0, 0);
        mbPanelReady = false;
        mnPanelState = 0;
    } else {
        SPUIHelpers_EndModal(mpModalOwner, 0, 0);
        if (mbCreatureWindowShown) {
            SP_WindowManager_s00e4_4200()->ShowWindow(1, mpCreatureWindow);
            mbCreatureWindowShown = false;
        }
        if (mbTribeWindowShown) {
            SP_WindowManager_s00e4_4200()->ShowWindow(1, mpTribeWindow);
            mbTribeWindowShown = false;
        }
    }

    FUN_0067cac0()->SetFlag(show == 0, 1);

    if (mpCreatureButton)
        mpCreatureButton->SetVisible(1, show);
    if (mpTribeButton)
        mpTribeButton->SetVisible(1, show);

    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x4486ae8, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x4486b30, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x54e53d9d, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0xf54a5ddc, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x61388da, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x61388db, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x694d94c, 1))
        w->SetVisible(1, show);
    if (IWindow_s00e4_4200* w = mpLayout->FindWindowByID(0x694d94b, 1))
        w->SetVisible(1, show);

    if (show) {
        int level;
        switch (SP_GetCurrentGameMode()) {
        case 0x1654c00: level = 0; break;
        case 0x1654c01: level = 1; break;
        case 0x1654c02: level = 2; break;
        case 0x1654c04: level = 3; break;
        case 0x1654c05: level = 4; break;
        case 0x1654c10: level = 5; break;
        default:        level = show; break;
        }

        HideLevelWindow(mpLayout, 0x15503770);
        HideLevelWindow(mpLayout, 0x15503771);
        HideLevelWindow(mpLayout, 0x15503772);
        HideLevelWindow(mpLayout, 0x15503773);
        HideLevelWindow(mpLayout, 0x15503774);

        if (mpLayout->FindWindowByID(0x15503770 + level, 1)) {
            int shown;
            switch (SP_GetCurrentGameMode()) {
            case 0x1654c00: shown = 0; break;
            case 0x1654c01: shown = 1; break;
            case 0x1654c02: shown = 2; break;
            case 0x1654c04: shown = 3; break;
            case 0x1654c05: shown = 4; break;
            case 0x1654c10: shown = 5; break;
            default:        shown = show; break;
            }
            ShowWindowByID(mpLayout, 0x15503770 + shown, 1);
        }

        if (cEffectsManager* effects = SP_EffectsManager()) {
            if (IEffectsHandler* old = mpEffectsHandler) {
                mpEffectsHandler = 0;
                old->Release();
            }
            if (effects->AddMessageHandler(0x4c4ba0a9, 0, &mpEffectsHandler))
                mpEffectsHandler->Delete(0);
        }

        SP_MessageServer_s00e4_4200()->SendMessage(0x6123dbe, 0, 0, 0);

        ClearWindowRect(mpLayout, 0x74ed2970);
        ClearWindowRect(mpLayout, 0x74ed2971);
        ClearWindowRect(mpLayout, 0x74ed2972);
        ClearWindowRect(mpLayout, 0x74ed2973);
        ClearWindowRect(mpLayout, 0x74ed2974);

        TintWindow(mpLayout, 0x60be2e0);
        TintWindow(mpLayout, 0x60be2e1);
        TintWindow(mpLayout, 0x60be2e2);
        TintWindow(mpLayout, 0x60be2e3);
        TintWindow(mpLayout, 0x60be2e4);

        FUN_00e42100();
        FUN_00e3e7f0();
        FUN_00e37910();
    } else {
        if (IEffectsHandler* old = mpEffectsHandler) {
            old->SetEnabled(0);
            if (IEffectsHandler* released = mpEffectsHandler) {
                mpEffectsHandler = 0;
                released->Release();
            }
        }
        FUN_0067dd50()->SetNotificationB(0x16, 2);
        FUN_00e43280();
        FUN_00e37910();
    }
}
