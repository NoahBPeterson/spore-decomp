// Slice s00e13b50 -- SP::cUICard layout pass (the PDB-derived name "interface_cast<cSPMission*>" is a
// mislabel): after the card text changed, resize the description/background windows to fit, either
// instantly (SetSize) or through cSPUIAnimator size animations, then tell the "0x5397388" button child
// to switch state.  Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

struct Rect {
    float x1, y1, x2, y2;
    Rect() {}
    Rect(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {}
};

struct IWinText {                                       // result of Cast(0xf15f4bd) on a text window
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void SetFlagOn(int v);                      // +0x14
};
struct IWinButton {                                     // result of Cast(0x8ed27e7a)
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3(); virtual void w4();
    virtual void w5(); virtual void w6(); virtual void w7(); virtual void w8(); virtual void w9();
    virtual void SetButtonState(int state, int arg);    // +0x28
};
struct IWindow {
    virtual void w0(); virtual void Release(); virtual void w2();
    virtual void* Cast(uint32_t id);                    // +0x0c
    virtual void w4(); virtual void w5(); virtual void w6();
    virtual uint32_t GetID();                           // +0x1c
    virtual void w8();
    virtual void w9(); virtual void w10(); virtual void w11();
    virtual uint32_t GetColor();                        // +0x30
    virtual void w13();
    virtual const Rect& GetArea();                      // +0x38
    virtual const char* GetCaption();                   // +0x3c
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19(); virtual void w20();
    virtual void w21(); virtual void w22();
    virtual void SetColor(uint32_t color);              // +0x5c
    virtual void w24();
    virtual bool IsChecked();                           // +0x64
    virtual void SetSize(float w, float h);             // +0x68
    virtual void w27();
    virtual void SetLocation(float x, float y);         // +0x70
    virtual void w29(); virtual void w30();
    virtual void SetVisible(int a, bool b);             // +0x7c
    virtual void SetText(const void* text);             // +0x80
    virtual void w33(); virtual void w34();
    virtual void w35(); virtual void w36(); virtual void w37(); virtual void w38(); virtual void w39();
    virtual void w40(); virtual void w41(); virtual void w42(); virtual void w43(); virtual void w44();
    virtual void w45(); virtual void w46(); virtual void w47(); virtual void w48(); virtual void w49();
    virtual void w50(); virtual void w51(); virtual void w52(); virtual void w53(); virtual void w54();
    virtual void w55(); virtual void w56(); virtual void w57(); virtual void w58(); virtual void w59();
    virtual IWindow* FindWindowByID(uint32_t id, bool recursive);   // +0xf0
    virtual void w61(); virtual void w62(); virtual void w63(); virtual void w64(); virtual void w65();
    virtual void SetOwner(void* owner);                 // +0x108
};
// FUN_00e12f80 etc: if (w) w->vslot7c(1, v)
void __cdecl SetWindowFlag1(IWindow* w, bool v);                    // 0x00e12f80
IWinText* __cdecl CastToText(IWindow** pw);                        // 0x005e1fd0 (*pw)->Cast(0xf15f4bd)
IWinButton* __cdecl CastToButton(IWindow* w);                      // 0x005ca960 w->Cast(0x8ed27e7a)
float __cdecl GetElapsedSeconds();                                 // 0x00805080
void __cdecl AutoSizeWindowForText(IWindow* w, int a, int b);      // 0x00806e40
int __cdecl GetCurrentGameMode();                                  // 0x00b5b800

struct AnimBuf {
    uint32_t d[0x80 / 4];
    void Destroy();                                     // 0x0059a1e0
};
struct cAnimator {
    void AddAnimation(AnimBuf* anim, IWindow* win, int flags);     // 0x007f8d10
    void Clear();                                                  // 0x007f8f00
};
AnimBuf* __cdecl SPUICreateWindowAnimationTargetSize(AnimBuf* out, IWindow* win, const float* size,
                                                     float now, float duration, int type);   // 0x007f8230

static const int kModeX = 0x1654c10;

struct cUICard {
    void*      vtbl0;
    void*      vtbl4;
    char       pad08[0x24 - 0x08];
    IWindow*   mpMainWin;       // +0x24
    cAnimator* mpAnimator;      // +0x28
    IWindow*   mpDescWin;       // +0x2c
    IWindow*   mpTextWin;       // +0x30
    IWindow*   pad34;
    IWindow*   mpWinA;          // +0x38
    IWindow*   mpWinB;          // +0x3c
    IWindow*   pad40;
    IWindow*   mpWinC;          // +0x44
    uint32_t   pad48[(0x68 - 0x48) / 4];
    Rect       mAreaA;          // +0x68 initial area of mpWinA
    Rect       mAreaB;          // +0x78 initial area of mpWinB
    Rect       mAreaC;          // +0x88 initial area of mpWinC

    IWindow* FindWindowByID(uint32_t id);               // 0x00e13390
    void UpdateLayout();                                // 0x00e132c0
    void ResizeToContent(bool animate, int style);      // @ 0x00e13b50
};

// @ 0x00e13b50
void cUICard::ResizeToContent(bool animate, int style) {
    if (!mpTextWin) return;
    if (!mpWinA) return;
    if (!mpWinB) return;
    if (!mpWinC) return;

    float now = GetElapsedSeconds();
    mpAnimator->Clear();
    const Rect* areaA = &mpWinA->GetArea();
    const Rect* areaB = &mpWinB->GetArea();
    const Rect* areaC = &mpWinC->GetArea();
    AutoSizeWindowForText(mpTextWin, 0, 1);
    const Rect* r = &mpTextWin->GetArea();
    float top = r->y1;
    float bottom = r->y2;

    if (GetCurrentGameMode() == kModeX) {
        IWindow* c1 = FindWindowByID(0x7f453b8);
        IWindow* c2 = FindWindowByID(0x7f5abd0);
        c2->GetArea();
        const Rect* t = &mpTextWin->GetArea();
        float textH = t->y2 - t->y1;
        const Rect* ca = &c1->GetArea();
        bool bigger = textH > (ca->y2 - ca->y1);
        SetWindowFlag1(c1, bigger);
        SetWindowFlag1(mpTextWin, !bigger);
        if (bigger) {
            const Rect* ra = &c1->GetArea();
            top = ra->y1;
            bottom = ra->y2;
        }
    }

    float y = (bottom - top) + top;
    IWindow* d0 = mpDescWin;
    if (d0 && d0->GetCaption()) {
        IWindow* d = mpDescWin;
        const Rect* da = &d->GetArea();
        d->SetLocation(da->x1, y);
        CastToText(&mpDescWin)->SetFlagOn(1);
        const Rect* da2 = &mpDescWin->GetArea();
        y = (da2->y2 - da2->y1) + y;
    }

    uint32_t extraId = 0;
    switch (style) {
    case 1: extraId = 0x574efda; break;
    case 2: extraId = 0xf5a74bec; break;
    default: break;
    }
    IWindow* extra = extraId ? FindWindowByID(extraId) : 0;
    if (extra) {
        const Rect* ea = &extra->GetArea();
        float eh = ea->y2 - ea->y1;
        if (eh > (y - top))
            y = (eh - (y - top)) + y;
        extra->SetLocation(ea->x1, ((y - top) * 0.5f + top) - eh * 0.5f);
    }

    Rect rA(mAreaA.x1, mAreaA.y1, (mAreaA.x2 - mAreaA.x1) + mAreaA.x1,
            (float)fabs((y + 8.0f) - mAreaA.y1) + mAreaA.y1);
    Rect rC(mAreaC.x1, mAreaC.y1, (mAreaC.x2 - mAreaC.x1) + mAreaC.x1,
            ((rA.y2 - mAreaA.y2) + (mAreaC.y2 - mAreaC.y1)) + mAreaC.y1);

    IWindow* child = mpMainWin->FindWindowByID(0x35b08191, true);
    bool notX = GetCurrentGameMode() != kModeX;
    float hA = rA.y2 - rA.y1;

    if (animate) {
        AnimBuf anim;
        float size[2];
        size[0] = rA.x2 - rA.x1;
        size[1] = hA;
        mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, mpWinA, size, now,
                                     (float)fabs(hA - (areaA->y2 - areaA->y1)) * 0.002f, 1), mpWinA, 0);
        anim.Destroy();
        if (notX) {
            size[0] = mAreaB.x2 - mAreaB.x1;
            float hB = mAreaB.y2 - mAreaB.y1;
            size[1] = hB;
            mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, mpWinB, size, now,
                                         (float)fabs(hB - (areaB->y2 - areaB->y1)) * 0.002f, 1), mpWinB, 0);
            anim.Destroy();
        }
        float hC = rC.y2 - rC.y1;
        float wC = rC.x2 - rC.x1;
        size[0] = wC;
        size[1] = hC;
        mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, mpWinC, size, now,
                                     (float)fabs(hC - (areaC->y2 - areaC->y1)) * 0.002f, 1), mpWinC, 0);
        anim.Destroy();
        if (child) {
            size[0] = wC;
            size[1] = hC;
            mpAnimator->AddAnimation(SPUICreateWindowAnimationTargetSize(&anim, child, size, now,
                                         (float)fabs(hC - (areaC->y2 - areaC->y1)) * 0.002f, 1), child, 0);
            anim.Destroy();
        }
    } else {
        mpWinA->SetSize(rA.x2 - rA.x1, hA);
        if (notX)
            mpWinB->SetSize(mAreaB.x2 - mAreaB.x1, mAreaB.y2 - mAreaB.y1);
        float hC = rC.y2 - rC.y1;
        float wC = rC.x2 - rC.x1;
        mpWinC->SetSize(wC, hC);
        if (child)
            child->SetSize(wC, hC);
    }

    IWindow* btnWin = mpMainWin->FindWindowByID(0x5397388, true);
    if (btnWin) {
        IWinButton* btn = CastToButton(btnWin);
        if (btn)
            btn->SetButtonState(4, 0);
    }
}

// ===========================================================================
// Card helpers 0x00e14180 .. 0x00e149e0
// ===========================================================================

struct Vec3 { float x, y, z; };

struct IMissionBase;

struct IUIMission {                                     // object at card +0x9c
    virtual void u00(); virtual void u01(); virtual void u02();
    virtual IMissionBase* Cast(uint32_t id);            // +0x0c
    virtual void u04(); virtual void u05(); virtual void u06(); virtual void u07();
    virtual void u08(); virtual void u09(); virtual void u10(); virtual void u11();
    virtual void u12(); virtual void u13(); virtual void u14(); virtual void u15();
    virtual void u16(); virtual void u17(); virtual void u18(); virtual void u19();
    virtual void u20(); virtual void u21(); virtual void u22(); virtual void u23();
    virtual void u24(); virtual void u25(); virtual void u26(); virtual void u27();
    virtual void u28();
    virtual uint32_t GetContentWinID();                 // +0x74
};

struct IMissionBase {                                   // result of IUIMission::Cast
    virtual void m00(); virtual void m01(); virtual void m02();
    virtual IMissionBase* Cast(uint32_t id);            // +0x0c
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61();
    virtual bool IsComplete();                          // +0xf8
    virtual bool IsFailed();                            // +0xfc
    virtual void m64(); virtual void m65(); virtual void m66(); virtual void m67();
    virtual void m68(); virtual void m69(); virtual void m70(); virtual void m71();
    virtual void m72(); virtual void m73(); virtual void m74(); virtual void m75();
    virtual void m76(); virtual void m77(); virtual void m78(); virtual void m79();
    virtual void m80(); virtual void m81(); virtual void m82(); virtual void m83();
    virtual void m84(); virtual void m85();
    virtual bool IsHighlighted();                       // +0x158
    void SetFlag(bool v);                               // 0x00c44ed0 (declared only)
};

struct IMissionMultiStep : IMissionBase {
    IMissionBase* GetCurrSubMission();                  // 0x00c59d90 (declared only)
};

struct CMissionView {                                   // object returned by q->GetView()
    char mPad[0x504];
    Vec3 mPoint;                                        // +0x504
};
struct CMissionTarget {
    virtual void q00(); virtual void q01(); virtual void q02(); virtual void q03();
    virtual void q04(); virtual void q05(); virtual void q06(); virtual void q07();
    virtual void q08(); virtual void q09(); virtual void q10(); virtual void q11();
    virtual void q12(); virtual void q13(); virtual void q14(); virtual void q15();
    virtual void q16(); virtual void q17(); virtual void q18(); virtual void q19();
    virtual void q20(); virtual void q21(); virtual void q22(); virtual void q23();
    virtual void q24(); virtual void q25(); virtual void q26(); virtual void q27();
    virtual void q28(); virtual void q29(); virtual void q30(); virtual void q31();
    virtual void q32(); virtual void q33(); virtual void q34(); virtual void q35();
    virtual void q36(); virtual void q37(); virtual void q38(); virtual void q39();
    virtual void q40(); virtual void q41(); virtual void q42(); virtual void q43();
    virtual void q44(); virtual void q45(); virtual void q46(); virtual void q47();
    virtual void q48(); virtual void q49(); virtual void q50(); virtual void q51();
    virtual void q52(); virtual void q53(); virtual void q54(); virtual void q55();
    virtual void q56(); virtual void q57(); virtual void q58(); virtual void q59();
    virtual void q60(); virtual void q61(); virtual void q62(); virtual void q63();
    virtual void q64(); virtual void q65(); virtual void q66(); virtual void q67();
    virtual void q68(); virtual void q69(); virtual void q70(); virtual void q71();
    virtual void q72(); virtual void q73(); virtual void q74(); virtual void q75();
    virtual void q76(); virtual void q77(); virtual void q78(); virtual void q79();
    virtual void q80(); virtual void q81(); virtual void q82(); virtual void q83();
    virtual void q84(); virtual void q85(); virtual void q86(); virtual void q87();
    virtual void q88(); virtual void q89(); virtual void q90(); virtual void q91();
    virtual void q92(); virtual void q93(); virtual void q94(); virtual void q95();
    virtual void q96(); virtual void q97(); virtual void q98(); virtual void q99();
    virtual void q100(); virtual void q101(); virtual void q102(); virtual void q103();
    virtual void q104(); virtual void q105(); virtual void q106(); virtual void q107();
    virtual void q108(); virtual void q109(); virtual void q110(); virtual void q111();
    virtual void q112(); virtual void q113(); virtual void q114(); virtual void q115();
    virtual void q116(); virtual void q117(); virtual void q118(); virtual void q119();
    virtual void q120(); virtual void q121(); virtual void q122(); virtual void q123();
    virtual void q124(); virtual void q125(); virtual void q126(); virtual void q127();
    virtual void q128(); virtual void q129(); virtual void q130(); virtual void q131();
    virtual void q132(); virtual void q133(); virtual void q134(); virtual void q135();
    virtual void q136(); virtual void q137(); virtual void q138(); virtual void q139();
    virtual void q140(); virtual void q141(); virtual void q142(); virtual void q143();
    virtual void q144(); virtual void q145(); virtual void q146(); virtual void q147();
    virtual void q148(); virtual void q149(); virtual void q150(); virtual void q151();
    virtual void q152(); virtual void q153(); virtual void q154(); virtual void q155();
    virtual void q156(); virtual void q157(); virtual void q158(); virtual void q159();
    virtual void q160(); virtual void q161(); virtual void q162(); virtual void q163();
    virtual void q164(); virtual void q165(); virtual void q166(); virtual void q167();
    virtual void q168(); virtual void q169(); virtual void q170(); virtual void q171();
    virtual void q172(); virtual void q173(); virtual void q174(); virtual void q175();
    virtual void q176(); virtual void q177(); virtual void q178(); virtual void q179();
    virtual void q180(); virtual void q181(); virtual void q182(); virtual void q183();
    virtual void q184(); virtual void q185(); virtual void q186(); virtual void q187();
    virtual void q188(); virtual void q189(); virtual void q190(); virtual void q191();
    virtual void q192(); virtual void q193(); virtual void q194(); virtual void q195();
    virtual void q196(); virtual void q197(); virtual void q198(); virtual void q199();
    virtual void q200(); virtual void q201(); virtual void q202(); virtual void q203();
    virtual void q204(); virtual void q205(); virtual void q206(); virtual void q207();
    virtual void q208(); virtual void q209(); virtual void q210(); virtual void q211();
    virtual void q212(); virtual void q213(); virtual void q214(); virtual void q215();
    virtual void q216(); virtual void q217(); virtual void q218(); virtual void q219();
    virtual void q220(); virtual void q221(); virtual void q222(); virtual void q223();
    virtual void q224(); virtual void q225(); virtual void q226(); virtual void q227();
    virtual void q228(); virtual void q229(); virtual void q230(); virtual void q231();
    virtual void q232(); virtual void q233(); virtual void q234(); virtual void q235();
    virtual void q236(); virtual void q237(); virtual void q238(); virtual void q239();
    virtual void q240(); virtual void q241(); virtual void q242(); virtual void q243();
    virtual void q244(); virtual void q245(); virtual void q246(); virtual void q247();
    virtual void q248(); virtual void q249(); virtual void q250(); virtual void q251();
    virtual void q252(); virtual void q253(); virtual void q254(); virtual void q255();
    virtual void q256(); virtual void q257(); virtual void q258(); virtual void q259();
    virtual void q260(); virtual void q261(); virtual void q262(); virtual void q263();
    virtual void q264(); virtual void q265(); virtual void q266(); virtual void q267();
    virtual void q268(); virtual void q269(); virtual void q270(); virtual void q271();
    virtual void q272(); virtual void q273(); virtual void q274(); virtual void q275();
    virtual void q276(); virtual void q277(); virtual void q278(); virtual void q279();
    virtual void q280(); virtual void q281(); virtual void q282(); virtual void q283();
    virtual void q284(); virtual void q285(); virtual void q286(); virtual void q287();
    virtual void q288(); virtual void q289(); virtual void q290(); virtual void q291();
    virtual void q292(); virtual void q293(); virtual void q294(); virtual void q295();
    virtual void q296(); virtual void q297(); virtual void q298(); virtual void q299();
    virtual void q300(); virtual void q301(); virtual void q302(); virtual void q303();
    virtual void q304(); virtual void q305(); virtual void q306(); virtual void q307();
    virtual void q308(); virtual void q309(); virtual void q310(); virtual void q311();
    virtual void q312(); virtual void q313(); virtual void q314(); virtual void q315();
    virtual void q316(); virtual void q317(); virtual void q318(); virtual void q319();
    virtual void q320(); virtual void q321(); virtual void q322(); virtual void q323();
    virtual void q324(); virtual void q325(); virtual void q326(); virtual void q327();
    virtual void q328(); virtual void q329(); virtual void q330(); virtual void q331();
    virtual void q332(); virtual void q333(); virtual void q334(); virtual void q335();
    virtual void q336(); virtual void q337(); virtual void q338(); virtual void q339();
    virtual void q340(); virtual void q341(); virtual void q342(); virtual void q343();
    virtual void q344(); virtual void q345(); virtual void q346(); virtual void q347();
    virtual void q348(); virtual void q349(); virtual void q350(); virtual void q351();
    virtual void q352(); virtual void q353(); virtual void q354(); virtual void q355();
    virtual void q356(); virtual void q357(); virtual void q358(); virtual void q359();
    virtual void q360(); virtual void q361(); virtual void q362(); virtual void q363();
    virtual void q364(); virtual void q365(); virtual void q366(); virtual void q367();
    virtual void q368(); virtual void q369(); virtual void q370(); virtual void q371();
    virtual void q372(); virtual void q373(); virtual void q374(); virtual void q375();
    virtual void q376(); virtual void q377(); virtual void q378(); virtual void q379();
    virtual void q380(); virtual void q381(); virtual void q382(); virtual void q383();
    virtual void q384(); virtual void q385(); virtual void q386(); virtual void q387();
    virtual void q388(); virtual void q389(); virtual void q390(); virtual void q391();
    virtual void q392(); virtual void q393(); virtual void q394(); virtual void q395();
    virtual void q396(); virtual void q397(); virtual void q398(); virtual void q399();
    virtual void q400(); virtual void q401(); virtual void q402(); virtual void q403();
    virtual void q404(); virtual void q405(); virtual void q406(); virtual void q407();
    virtual void q408(); virtual void q409(); virtual void q410(); virtual void q411();
    virtual void q412(); virtual void q413(); virtual void q414(); virtual void q415();
    virtual void q416(); virtual void q417(); virtual void q418(); virtual void q419();
    virtual void q420(); virtual void q421(); virtual void q422(); virtual void q423();
    virtual void q424(); virtual void q425(); virtual void q426(); virtual void q427();
    virtual void q428(); virtual void q429(); virtual void q430(); virtual void q431();
    virtual void q432(); virtual void q433(); virtual void q434(); virtual void q435();
    virtual void q436(); virtual void q437(); virtual void q438(); virtual void q439();
    virtual void q440(); virtual void q441(); virtual void q442(); virtual void q443();
    virtual void q444(); virtual void q445(); virtual void q446(); virtual void q447();
    virtual void q448(); virtual void q449(); virtual void q450(); virtual void q451();
    virtual void q452(); virtual void q453(); virtual void q454(); virtual void q455();
    virtual void q456(); virtual void q457(); virtual void q458(); virtual void q459();
    virtual void q460(); virtual void q461(); virtual void q462(); virtual void q463();
    virtual void q464(); virtual void q465(); virtual void q466(); virtual void q467();
    virtual void q468(); virtual void q469(); virtual void q470(); virtual void q471();
    virtual void q472(); virtual void q473(); virtual void q474(); virtual void q475();
    virtual void q476(); virtual void q477(); virtual void q478(); virtual void q479();
    virtual void q480(); virtual void q481(); virtual void q482(); virtual void q483();
    virtual void q484(); virtual void q485(); virtual void q486(); virtual void q487();
    virtual void q488(); virtual void q489(); virtual void q490(); virtual void q491();
    virtual void q492(); virtual void q493(); virtual void q494(); virtual void q495();
    virtual void q496(); virtual void q497(); virtual void q498(); virtual void q499();
    virtual void q500();
    virtual CMissionView* GetView();                    // 0x00c2e780
};

struct CardVtblView {                                   // primary vtable of the card
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08();                                 // +0x20
    virtual void v09();                                 // +0x24
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13();                                 // +0x34
};

struct ISelectable {                                    // source item of UpdateButtonStateB
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25();
    virtual bool IsSelected();                          // +0x68
};

struct Stopwatch {                                      // EA::LimitStopwatch, 0x20 bytes
    uint32_t mData[8];
    void Init(int type, bool b);                        // 0x0093a560
    void SetTimeLimit(uint32_t limit, bool b);          // 0x0093a480
};

struct CardEvent {
    uint32_t m00;                                       // +0x00
    uint32_t m04;                                       // +0x04
    uint32_t mType;                                     // +0x08
    uint32_t mId;                                       // +0x0c
    uint32_t m10;                                       // +0x10
    uint32_t m14;                                       // +0x14
    void*    mpSender;                                  // +0x18
};

struct EventCtx {                                       // 0x40-byte draw context
    uint32_t mColor;                                    // +0x00
    uint32_t mPad04[3];                                 // +0x04
    uint8_t  mFlag10;                                   // +0x10
    uint16_t mPad11;                                    // +0x11
    uint8_t  mFlag13;                                   // +0x13
    uint32_t mPad14;                                    // +0x14
    Vec3     mPos;                                      // +0x18
    uint8_t  mFlag24;                                   // +0x24
    uint8_t  mPad25[0x40 - 0x25];                       // +0x25
    void Init();                                        // 0x00644b10
    void Destroy();                                     // 0x00644b60
};
void __cdecl sub_64a990(void* ctx);                      // 0x0064a990

struct CStr {                                           // SP::cString temporary, 0x14 bytes
    uint32_t mData[5];
    void Init(uint32_t a, uint32_t b, const wchar_t* text);   // 0x006b5770
    const wchar_t* GetText();                                 // 0x006b55c0
    void Destroy();                                           // 0x006b5240
};

struct CPanel {
    void OpenPanel();                                    // 0x00e18dd0
};
CPanel* __stdcall GetMissionPanel(int id, void* mission);        // 0x00b3d3f0

struct CivStrategy {
    char mPad[0x148];
    uint8_t mFlag148;                                   // +0x148
};
CivStrategy* __cdecl GetCivStrategy();                   // 0x00cf74c0

struct TribeStrategy { bool TerrainNotHasKey(); };       // 0x00cd44a0
TribeStrategy* __cdecl GetTribeStrategy();               // 0x00cd40b0

struct SpaceUi { bool IsSomething(); };                  // 0x01065e20
SpaceUi* __cdecl GetSpaceUi();                           // 0x010666a0

struct ScrollHost { char mPad[0xb8]; int mCount; };      // +0xb8
struct ScrollSource { int GetScrollPos(); };             // 0x00f3be30
struct ScrollGlobals {
    char mPad74[0x74];
    ScrollSource* mpSource;                             // +0x74
    ScrollHost*   mpHost;                               // +0x78
};

struct CSPUILayout { void SetVisibility(bool on); };     // 0x00810590

union F32Bits { float f; uint32_t u; };

struct CardLayout {                                     // retail cards, 0xf8 bytes
    void*    mpVtbl0;                                   // +0x00
    void* volatile mpVtbl1;                             // +0x04
    uint32_t m08;                                       // +0x08
    uint32_t m0C;                                       // +0x0c
    uint8_t  m10;                                       // +0x10
    uint8_t  m11;                                       // +0x11
    uint16_t mPad12;                                    // +0x12
    float    m14;                                       // +0x14
    float    m18;                                       // +0x18
    CSPUILayout* m1C;                                   // +0x1c
    uint32_t m20;                                       // +0x20
    IWindow* mpMainWin;                                 // +0x24
    IWindow* mpAnimator;                                // +0x28
    IWindow* mpDescWin;                                 // +0x2c
    IWindow* mpTextWin;                                 // +0x30
    IWindow* mp34;                                      // +0x34
    IWindow* mpWinA;                                    // +0x38
    IWindow* mpWinB;                                    // +0x3c
    IWindow* mp40;                                      // +0x40
    IWindow* mpWinC;                                    // +0x44
    uint32_t mPad48[0x50 / 4];                          // +0x48
    F32Bits  m98;                                       // +0x98
    IUIMission* mpMission;                              // +0x9c
    uint32_t mPadA0[0x10 / 4];                          // +0xa0
    Stopwatch mWatch0;                                  // +0xb0
    Stopwatch mWatch1;                                  // +0xd0
    int      mF0;                                       // +0xf0
    int      mF4;                                       // +0xf4

    void ResizeToStyle0(bool animate);
    CardLayout* InitA();
    void RefreshChildWindows();
    uint32_t GetCardColor();
    bool HandleEvent(void* sender, CardEvent* ev);
    uint32_t GetContentWinID();
    void UpdateButtonStateA(IWindow* src);
    void UpdateButtonStateB(ISelectable* src);
    CardLayout* InitB();
    CardLayout* InitC();
    void ShowCard();
    void UpdateScrollButtons();
    void HideButtons();
};

// @ 0x00e14180
void CardLayout::ResizeToStyle0(bool animate)
{
    ((cUICard*)this)->ResizeToContent(animate, 0);
    ((CardVtblView*)this)->v13();
}

// @ 0x00e141a0
CardLayout* CardLayout::InitA()
{
    mpVtbl1 = (void*)0x013ec458;
    m08 = 0;
    m0C = 0;
    m10 = 0;
    m11 = 0;
    m14 = 0.0f;
    m18 = 0.0f;
    m1C = 0;
    m20 = 0;
    mpMainWin = 0;
    mpAnimator = 0;
    mpDescWin = 0;
    mpTextWin = 0;
    mp34 = 0;
    mpWinA = 0;
    mpWinB = 0;
    mp40 = 0;
    mpWinC = 0;
    mpVtbl0 = (void*)0x0147fe14;
    mpVtbl1 = (void*)0x0147fe04;
    m98.f = 0.0f;
    mpMission = 0;
    return this;
}

// @ 0x00e14220
void CardLayout::RefreshChildWindows()
{
    IUIMission* mi = mpMission;
    if (mi) {
        IMissionBase* m = mi->Cast(0x2aa5ada);
        if (m)
            m->SetFlag(false);
    }
    IWindow* w = mpMainWin->FindWindowByID(0x94a4a6ea, true);
    if (w)
        w->SetOwner(this);
    w = mpMainWin->FindWindowByID(0x54bf5692, true);
    if (w)
        w->SetOwner(this);
    w = mpMainWin->FindWindowByID(0x5397388, true);
    if (w)
        w->SetOwner(this);
    ((cUICard*)this)->UpdateLayout();
}

// @ 0x00e142c0
uint32_t CardLayout::GetCardColor()
{
    if (mpMission == 0)
        return 0;
    IUIMission* mi = mpMission;
    if (mi == 0)
        return 0;
    IMissionBase* c = mi->Cast(0x2aa5ada);
    if (!c)
        return 0;
    if (c->IsHighlighted()) {
        IMissionBase* m = c->Cast(0x422227c);
        if (!m)
            return 0;
        c = ((IMissionMultiStep*)m)->GetCurrSubMission();
        if (!c)
            return 0;
    }
    if (c->IsComplete())
        return 0xff93bfa6;
    return (c->IsFailed() ? 0x3e2e7 : 0) + 0xffbbadbf;
}

// @ 0x00e14360
bool CardLayout::HandleEvent(void* sender, CardEvent* ev)
{
    if (ev->mType == 0xc)
        ((CardVtblView*)this)->v09();

    if (ev->mType == 0xa && ev->mId == 1) {
        IWindow* w = (IWindow*)sender;
        if (w->GetID() == 0x54bf5692 || w->GetID() == 0x5397388) {
            if (mpMission) {
                IMissionBase* m = mpMission->Cast(0x2aa5ada);
                if (m)
                    m->SetFlag(w == (IWindow*)ev->mpSender);
            }
        }
    }

    switch (ev->mId) {
    case 0x5235aa8:
        if (ev->mType == 0x287259f6)
            ((CardVtblView*)this)->v08();
        return true;
    case 0x5235138:
        if (ev->mType == 0x287259f6) {
            if (GetCurrentGameMode() == 0x1654c04 && GetCivStrategy()->mFlag148)
                return true;
            if (GetCurrentGameMode() == 0x1654c02 && GetTribeStrategy()->TerrainNotHasKey())
                return true;
            if (GetCurrentGameMode() == 0x1654c05 && GetSpaceUi()->IsSomething())
                return true;
            GetMissionPanel(-14, mpMission)->OpenPanel();
        }
        return true;
    case 0xf4e6882f:
        if (ev->mType == 0x287259f6 && mpMission) {
            CMissionTarget* q = (CMissionTarget*)mpMission->Cast(0x7406a570);
            if (q) {
                EventCtx ctx;
                ctx.Init();
                switch (GetCurrentGameMode() - 0x1654c00) {
                case 0: ctx.mColor = 0x817d7b6d; break;
                case 1: ctx.mColor = 0x710c185a; break;
                case 2: ctx.mColor = 0x8799ddcb; break;
                case 4: ctx.mColor = 0x5126162d; break;
                case 5: ctx.mColor = 0xfeb98c35; break;
                default: break;
                }
                ctx.mFlag13 = 0;
                ctx.mFlag24 = 1;
                Vec3* p = &q->GetView()->mPoint;
                ctx.mPos = *p;
                sub_64a990(&ctx);
                ctx.Destroy();
            }
        }
        return true;
    default:
        return false;
    }
}

// @ 0x00e14590
uint32_t CardLayout::GetContentWinID()
{
    IUIMission* m = mpMission;
    if (m)
        return m->GetContentWinID();
    return 0x74bf58cb;
}

// @ 0x00e145b0
void CardLayout::UpdateButtonStateA(IWindow* src)
{
    IWindow* w1 = mpMainWin->FindWindowByID(0x574efda, true);
    IWindow* w2 = mpMainWin->FindWindowByID(0x7591f955, true);
    if (!w1 || !w2)
        return;
    if (src->IsChecked()) {
        w1->SetVisible(1, 1);
        w2->SetColor(0x55ffffff);
        IWindow* c = mpWinC;
        if (!c)
            return;
        c->SetVisible(1, 1);
        IWindow* d = mpWinC;
        d->SetColor(d->GetColor() | 0x99000000);
    } else {
        w1->SetVisible(1, 0);
        w2->SetColor(0xffffffff);
        IWindow* c = mpWinC;
        if (!c)
            return;
        c->SetVisible(1, 1);
        IWindow* d = mpWinC;
        d->SetColor(d->GetColor() & 0xffffff);
    }
}

// @ 0x00e14690
void CardLayout::UpdateButtonStateB(ISelectable* src)
{
    IWindow* w1 = mpMainWin->FindWindowByID(0xf5a74bec, true);
    IWindow* w2 = mpMainWin->FindWindowByID(0x7591f955, true);
    if (!w1 || !w2)
        return;
    if (src->IsSelected()) {
        w1->SetVisible(1, 1);
        w2->SetColor(0x55ffffff);
        IWindow* c = mpMainWin->FindWindowByID(0x35b08191, true);
        if (!c)
            return;
        c->SetVisible(1, 1);
        c->SetColor(c->GetColor() | 0x99000000);
    } else {
        w1->SetVisible(1, 0);
        w2->SetColor(0xffffffff);
        IWindow* c = mpMainWin->FindWindowByID(0x35b08191, true);
        if (!c)
            return;
        c->SetVisible(1, 1);
        c->SetColor(c->GetColor() & 0xffffff);
    }
}

// @ 0x00e147a0
CardLayout* CardLayout::InitB()
{
    mpVtbl1 = (void*)0x013ec458;
    m08 = 0;
    m0C = 0;
    m10 = 0;
    m11 = 0;
    m14 = 0.0f;
    m18 = 0.0f;
    m1C = 0;
    m20 = 0;
    mpMainWin = 0;
    mpAnimator = 0;
    mpDescWin = 0;
    mpTextWin = 0;
    mp34 = 0;
    mpWinA = 0;
    mpWinB = 0;
    mp40 = 0;
    mpWinC = 0;
    mpVtbl0 = (void*)0x0147fe60;
    mpVtbl1 = (void*)0x0147fe50;
    m98.u = 0;
    return this;
}

// @ 0x00e14810
CardLayout* CardLayout::InitC()
{
    mpVtbl1 = (void*)0x013ec458;
    m08 = 0;
    m0C = 0;
    m10 = 0;
    m11 = 0;
    m14 = 0.0f;
    m18 = 0.0f;
    m1C = 0;
    m20 = 0;
    mpMainWin = 0;
    mpAnimator = 0;
    mpDescWin = 0;
    mpTextWin = 0;
    mp34 = 0;
    mpWinA = 0;
    mpWinB = 0;
    mp40 = 0;
    mpWinC = 0;
    mpVtbl0 = (void*)0x0147feac;
    mpVtbl1 = (void*)0x0147fe9c;
    m98.f = 0.0f;
    mWatch0.Init(5, false);
    mWatch0.SetTimeLimit(0, false);
    mWatch1.Init(4, false);
    mWatch1.SetTimeLimit(0, false);
    mF0 = 0;
    mF4 = 0;
    return this;
}

// @ 0x00e148d0
void CardLayout::ShowCard()
{
    if (m1C) {
        m1C->SetVisibility(true);
        if (mpMainWin)
            mpMainWin->SetVisible(1, 1);
    }
    mF0 = 1;
}

// @ 0x00e14900
void CardLayout::UpdateScrollButtons()
{
    if (mF0 == 1)
        return;
    ScrollGlobals* g = *(ScrollGlobals**)0x016c7aa4;
    int total = g->mpHost->mCount;
    int cur = g->mpSource->GetScrollPos();
    IWindow* w = mpMainWin->FindWindowByID(0x74b5328, true);
    if (w)
        w->SetVisible(2, total > 0);
    w = mpMainWin->FindWindowByID(0x74b5329, true);
    if (w)
        w->SetVisible(2, total < cur - 1);
    CStr text;
    text.Init(0x21851ebe, 0x74bb7ec, 0);
    w = mpMainWin->FindWindowByID(0x74b6990, true);
    const wchar_t* str = text.GetText();
    if (w)
        w->SetText(str);
    text.Destroy();
}

// @ 0x00e149e0
void CardLayout::HideButtons()
{
    IWindow* w = mpMainWin->FindWindowByID(0x7a15028, true);
    w->SetVisible(1, 0);
    w = mpMainWin->FindWindowByID(0x7a15027, true);
    w->SetVisible(1, 0);
}
