// src/game/UTFSpore_Win32/Button.cpp -- migrated from slice(s) s00966b20, s00965230, s009656d0, s00964190, s00962ff0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/Button.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/LineLayout.h"
#include "EA/UTFWin/RenderContext.h"
#include "EA/Text/Typesetter.h"
#include "EA/UTFWin/Window.h"
#include "EA/UTFWin/Image.h"
#include "EA/Stopwatch.h"

// ---- items of slice s00962ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct WinButtonX {
    int   GetSlot(uint32_t i);                          // 0x964020
    void  SetSlot(uint32_t i, int v);                   // 0x963fd0
    int   GetCaptionColor();                            // 0x964000
};
struct FlexFlag {
    int  GetEffectFlag();                       // 0x963f60
    void SetEffectFlag(uint32_t m, bool on);    // 0x963f70
};
struct Cap { void SelectCaptionColor(); };
// ---- items of slice s00962ff0 end

// ---- items of slice s00964190 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define F(T, o) (*(T*)((char*)this + (o)))
template <class T> inline const T& eastl_max(const T& a, const T& b) { return b < a ? a : b; }
struct Msg {
    uint32_t src, dst, id;
    uint32_t p0, p1, p2, p3;
};
struct DropShadow {
    void SetMode1(uint32_t);               // 0x00830280
    void SetMode2(uint32_t);               // 0x00830150
    void F96e740(uint32_t h, uint32_t a, uint32_t b, int r, uint32_t c, uint32_t ch, bool flag);  // 0x0096e740
};
struct LineLayout {
    void Clear(int all);  // 0x0089cbc0
};
struct Typesetter {
    int  F89dc00(const uint16_t* text, int len, float l, float t, float r, float b, void* style, void* layout, int flags);  // 0x0089dc00
    void LayoutLine(const uint16_t* text, int len, float x, float y, void* style);  // 0x0089db20
};
struct StyleManager {
    void* GetStyle(uint32_t id, int arg);  // 0x00894670
};
StyleManager* __cdecl GetStyleManager(bool create);                              // 0x00885bd0
struct RenderContext { uint32_t Begin2D(int arg); };                              // 0x0095bc10
struct RenderContext;
struct IObjVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void* V10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
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
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual bool V8c();
};
struct IWinVt;
struct IFocusMgr {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void* GetFocus(int);
    virtual void SetFocus(int, IWinVt*);
    virtual void ReleaseFocus(int, IWinVt*);
};
struct IWinVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual IObjVt* GetObj();
    virtual void s18();
    virtual void s1c();
    virtual uint32_t V20();
    virtual void s24();
    virtual uint32_t GetFlags();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void SetFlags(uint32_t);
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void SetFlag(uint32_t, bool);
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void V90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void Vb0(void*);
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void Send(Msg*);
};
struct IBtnVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void SetFlag(uint32_t, bool);
};
struct IPrimVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void V4c(int, void*);
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void V88(uint32_t);
    virtual void s8c();
    virtual void s90();
    virtual void V94(uint32_t);
    virtual void V98();
    virtual void V9c();
};
struct IPainterVt {
    virtual void s0();
    virtual void s4();
    virtual void s8();
    virtual void sc();
    virtual void Paint(void*, void*, void*);
    virtual void s14();
    virtual void GetSize(float*, int, int);
};
struct WB {
    IWinVt* W() { return (IWinVt*)((char*)this + 4); }
    IBtnVt* Btn() { return (IBtnVt*)((char*)this + 0x20c); }
    IPrimVt* P() { return (IPrimVt*)this; }
    IFocusMgr* Mgr() { return *(IFocusMgr**)((char*)this + 0x34); }
    bool OnButtonClicked(int a);
    bool OnKeyDown(int a, int b, int c);
    bool OnKeyUp(int a, int b, int c);
    bool OnMouseDown(int a, int b, int c, uint32_t f);
    bool OnMouseUp(int a, int b, int c, uint32_t f);
    bool OnFocusChange(int a, void* w);
    bool OnTick();
    void SerUpdate();
    bool OnRebuild(RenderContext* rc);
    bool CalcSize(int a, float* out);
    void WindowSerUpdate();                       // 0x009614a0
    void WindowOnPaint(RenderContext* rc);        // 0x00960310
};
// ---- items of slice s00964190 end

// ---- items of slice s009656d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const float kOne;                // 0x01485720 = 1.0f
namespace EA {
namespace UTFWin {
struct Image_s0096_56d0 { uint32_t pad[8]; };
}
}
namespace EA {
namespace UTFWin {
struct Point2 { float x, y; };
}
}
namespace EA {
namespace UTFWin {
struct Graphics2D {
    virtual void v0();
    virtual void SetColor(uint32_t color);
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14();
    virtual void FillQuad(Point2& tl, Point2& tr, Point2& br, Point2& bl);
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual void DrawImageScaled(const float* area, const Image_s0096_56d0* image, const float* texCoords);
};
}
}
namespace EA {
namespace UTFWin {
struct RenderContext_s0096_56d0 {
    Graphics2D* __thiscall Begin2D(int flags);   // 0x95bc10
};
}
}
namespace EA {
namespace UTFWin {
namespace Drawing {
void __cdecl BltEdgeStretch(Graphics2D* g, const float* rect, const float* src, const Image_s0096_56d0* image,
                            const float* uv, float sx, float sy);   // 0x95d000
}
}
}
struct Rect4 { float x1, y1, x2, y2; Rect4(float a, float b, float c, float d) : x1(a), y1(b), x2(c), y2(d) {} };
static __forceinline void FillRectR(EA::UTFWin::Graphics2D* g, const Rect4& r) {
    EA::UTFWin::Point2 tl = { r.x1, r.y1 };
    EA::UTFWin::Point2 tr = { r.x2, r.y1 };
    EA::UTFWin::Point2 br = { r.x2, r.y2 };
    EA::UTFWin::Point2 bl = { r.x1, r.y2 };
    g->FillQuad(tl, tr, br, bl);
}
static __forceinline void FillRect(EA::UTFWin::Graphics2D* g, float l, float t, float r, float b) {
    Rect4 rc(l, t, r, b);
    FillRectR(g, rc);
}
namespace EA {
namespace UTFWinControls {
struct DrawState { uint32_t flags; };
}
}
namespace EA {
namespace UTFWinControls {
class ButtonDrawable { public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool GetSourceRect(uint32_t flags, float* out);   // +0x20
    uint32_t pad[3];                    // +0x04 (second base, refcount ...)
    UTFWin::Image_s0096_56d0* mpImage;             // +0x10
    bool mbTileable;                    // +0x14
    void __thiscall Paint(UTFWin::RenderContext_s0096_56d0* ctx, const float* rc, const DrawState* st);
};
}
}
// ---- items of slice s009656d0 end

// ---- items of slice s00965230 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma pack(push, 4)
#pragma pack(pop)
namespace EA {
namespace Text {
struct TextStyle_s0096_5230;
}
}
namespace EA {
namespace Text {
class LineLayout_s0096_5230;
}
}
namespace EA {
namespace Text {
class StyleManager_s0096_5230;
}
}
namespace EA {
namespace Text {
class Typesetter_s0096_5230;
}
}
namespace EA {
namespace Text {
StyleManager_s0096_5230* GetStyleManager_s0096_5230(bool);
}
}
namespace EA {
namespace Text {
class StyleManager_s0096_5230 {
 public:
  TextStyle_s0096_5230 const* GetStyle(unsigned int id, TextStyle_s0096_5230* p) const;  // +0x0 0x00894670
};
}
}
namespace EA {
namespace Text {
class LineLayout_s0096_5230 {
 public:
  void Clear(bool b);  // +0x0 0x0089cbc0
};
}
}
namespace EA {
namespace Text {
class Typesetter_s0096_5230 {
 public:
  int   LayoutLine(wchar_t const* text, unsigned int len, float x, float y,
                   TextStyle_s0096_5230 const* style);  // +0x0
  int   LayoutParagraph(wchar_t const* text, unsigned int len, float x, float y, float maxW,
                        float maxH, TextStyle_s0096_5230 const* style, LineLayout_s0096_5230* pLine, int flag);
  void* GetLineLayout();  // 0x008976a0 (EA::Text::Typesetter::GetLineLayout)
};
}
}
struct RectF {
  RectF() {}
  RectF(float l, float t, float r, float b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
  float Width() const { return mRight - mLeft; }
  float Height() const { return mBottom - mTop; }
  float mLeft, mTop, mRight, mBottom;
};
struct LayoutResult {
  char  mPad0[8];
  float mF08;  // +0x08
  char  mPad1[4];
  float mF10;  // +0x10
  float mF14;  // +0x14
};
struct Vec2f {
  float x, y;
};
struct IDrawable {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6(Vec2f* pSize, int a, int b);  // +0x18
};
struct IWinButtonBase {
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
virtual void v14();
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
virtual void v25();
virtual void v26();
  virtual void SetLayoutRect(RectF const* pRect);  // +0x6c
};
class WinButton {
 public:
  void EmbeddedCalcSize(char flag);  // 0x00965230
  void Refresh();                    // 0x009653f0

 private:
  void*         mVT0;                       // 0x000
  void*         mVT1;                       // 0x004
  void*         mUnk08;                     // 0x008
  void*         mVT2;                       // 0x00c
  void*         mObj10;                     // 0x010
  char          mPad14[0x88 - 0x14];
  RectF         mWindowRect;                // 0x088
  char          mPad98[0xb0 - 0x98];
  wchar_t*      mTextBegin;                 // 0x0b0
  wchar_t*      mTextEnd;                   // 0x0b4
  char          mPadB8[0xc0 - 0xb8];
  unsigned int  mStyleId;                   // 0x0c0
  char          mPadC4[0x1e0 - 0xc4];
  IDrawable*    mDrawable;                  // 0x1e0
  char          mPad1E4[0x218 - 0x1e4];
  unsigned int  mFlags;                     // 0x218
  int           mAlignment;                 // 0x21c
  char          mPad220[0x228 - 0x220];
  RectF         mDrawableRect;              // 0x228
  RectF         mCaptionRect;               // 0x238
  float         mCaptionOffsets[4];         // 0x248
  char          mPad258[0x280 - 0x258];
  char          mTypesetter[0x7b0 - 0x280]; // 0x280 opaque Typesetter
  char          mLineLayout[0x840 - 0x7b0]; // 0x7b0 opaque LineLayout
  char          mPad840[0x858 - 0x840];
  unsigned int  mLineHeight;                // 0x858
};
// ---- items of slice s00965230 end

// ---- items of slice s00966b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl FUN_009512c0();                                  // 0x9512c0
extern "C" void  __cdecl FUN_00951330(void* p);                            // 0x951330
extern float    g_13eb8a0;
#define F_s0096_6b20(o, off)  (*(uint32_t*)((uint8_t*)(o) + (off)))
#define FB(o, off) (*(uint8_t*)((uint8_t*)(o) + (off)))
#define FF(o, off) (*(float*)((uint8_t*)(o) + (off)))
extern "C" void* __cdecl FUN_009512d0(uint32_t size, uint32_t align,
                                      const char* name, void* heap);       // 0x9512d0
struct S_962740 { void __thiscall m(); };                                  // 0x962740
struct S_962a10 { void* __thiscall m(); };                                  // 0x962a10
struct S_830150 { void __thiscall m(uint32_t); };                          // 0x830150 SetMode2
struct S_8323d0 { void __thiscall m(); };                                  // 0x8323d0
struct S_89c540 { void __thiscall m(); };                                  // 0x89c540
struct S_89d820 { void __thiscall m(int); };                               // 0x89d820
struct S_898bd0 { void __thiscall m(int); };                               // 0x898bd0
static inline void VCALL0(void* o, int off) {
    ((void (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline uint32_t VCALL0R(void* o, int off) {
    return ((uint32_t (__thiscall*)(void*))(*(void***)o)[off / 4])(o);
}
static inline void VCALL1(void* o, int off, uint32_t a) {
    ((void (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline void* VCALL1P(void* o, int off, uint32_t a) {
    return ((void* (__thiscall*)(void*, uint32_t))(*(void***)o)[off / 4])(o, a);
}
static inline void VCALL2(void* o, int off, uint32_t a, uint32_t b) {
    ((void (__thiscall*)(void*, uint32_t, uint32_t))(*(void***)o)[off / 4])(o, a, b);
}
struct S_966b20 { uint8_t __thiscall m(uint32_t, float*); };
struct S_966bb0 { uint8_t __thiscall m(uint32_t, float*); };
struct S_966c70 { void     __thiscall m(); };
struct S_966dc0 { void*    __thiscall m(); };
struct S_966df0 { void*    __thiscall m(uint8_t); };
struct S_966e40 { void     __thiscall m(); };
struct S_966f90 { void*    __thiscall m(); };
struct S_967120 { void*    __thiscall m(uint8_t); };
extern uint32_t g_1440f84;
extern uint32_t g_1485720;
struct DrawableStd {
    uint32_t v00, v04, v08, v0c, v10;
    uint8_t  v14, pad[3];
};
struct BasicFactoryStd  { DrawableStd* __thiscall CreateInstance(uint32_t, void*); };
struct BasicFactoryRadio{ DrawableStd* __thiscall CreateInstance(uint32_t, void*); };
// ---- items of slice s00966b20 end

// @ 0x00963f60
int FlexFlag::GetEffectFlag()
{
    return *(int*)((char*)this - 0x160);
}

// @ 0x00963f70
void FlexFlag::SetEffectFlag(uint32_t m, bool on)
{
    int v = *(int*)((char*)this - 0x160);
    if (on) {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v | m);
    } else {
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)this + 0x24))(this, (uint32_t)v & ~m);
    }
}

// @ 0x00963fd0
void WinButtonX::SetSlot(uint32_t i, int v)
{
    if (i < 8 && *(int*)((char*)this + 0x54 + i * 4) != v) {
        *(int*)((char*)this + 0x54 + i * 4) = v;
        int* base = (int*)((char*)this - 0x20c);
        (*(void(__thiscall**)(int*))((char*)*base + 0xa0))(base);
    }
}

// @ 0x00964000
int WinButtonX::GetCaptionColor()
{
    if (*(char*)((char*)this + 0x210) != 0)
        (*(void(__thiscall**)(void*))((char*)*(void**)this + 0xa0))(this);
    return *(int*)((char*)this + 0x224);
}

// @ 0x00964020
int WinButtonX::GetSlot(uint32_t i)
{
    if (i < 8)
        return *(int*)((char*)this + 0x54 + i * 4);
    return 0;
}

// @ 0x00964040
void Cap::SelectCaptionColor()
{
    void* self = this;
    uint32_t v = (*(uint32_t(__thiscall**)(void*))((char*)*(void**)self + 0x28))(self);
    uint32_t xf = *(uint32_t*)((char*)self + 0x3c);
    char c2 = (char)((xf >> 4) | (v >> 1)) & 1;
    (void)c2;
}

// @ 0x009643c0
bool WB::OnMouseDown(int a, int b, int c, uint32_t f)
{
    if (!(f & 8) || (f & 0x30))
        return false;
    void* w = this ? (char*)this + 4 : 0;
    if (Mgr()->GetFocus(1) != w)
        {
            IFocusMgr* m = Mgr();
            void** vt = *(void***)m;
            ((void(__thiscall*)(void*, int, void*))vt[0x58 / 4])(m, 1, W());
        }
    uint32_t fl = F(uint32_t, 0xac);
    if (!(fl & 2) && (fl & 8)) {
        Btn()->SetFlag(2, 1);
        if (F(uint8_t, 0x218) & 1)
            P()->V94(f);
    }
    return true;
}

// @ 0x00964450
bool WB::OnMouseUp(int a, int b, int c, uint32_t f)
{
    if (!(f & 8)) {
        void* w = this ? (char*)this + 4 : 0;
        if (Mgr()->GetFocus(1) == w)
            {
            IFocusMgr* m = Mgr();
            void** vt = *(void***)m;
            ((void(__thiscall*)(void*, int, void*))vt[0x5c / 4])(m, 1, W());
        }
        if (F(uint32_t, 0xac) & 2) {
            Btn()->SetFlag(2, 0);
            if (!(F(uint8_t, 0x218) & 1))
                P()->V94(f);
        }
        return true;
    }
    return false;
}

// @ 0x00964c90
bool WB::OnRebuild(RenderContext* rc)
{
    P()->V9c();
    void* painter = F(void*, 0x1e0);
    if (painter == 0) {
        WindowOnPaint(rc);
    } else {
        uint32_t f = F(uint32_t, 0xac);
        bool b2 = (f >> 2) & 1;
        bool b1 = (f >> 1) & 1;
        bool b3 = (f >> 3) & 1;
        uint32_t wf = W()->GetFlags();
        uint32_t st[4];
        st[0] = 0;
        st[1] = 0;
        st[2] = F(uint32_t, 0x1dc);
        st[3] = F(uint32_t, 0x1d8);
        if (!((wf >> 1) & 1))
            st[0] = 1;
        int type = F(int, 0x214);
        if (type == 2 || type == 3) {
            if (b3) st[0] = 2;
            if (b2) st[0] |= 8;
            if (b1) st[0] |= 3;
        } else if (b1) {
            st[0] = 3;
        } else if (b3) {
            st[0] = 2;
        }
        ((IPainterVt*)painter)->Paint(rc, (char*)this + 0x228, st);
    }
    if (F(uint16_t*, 0xb0) != F(uint16_t*, 0xb4)) {
        StyleManager* sm = GetStyleManager(true);
        if (sm) {
            char* style = (char*)sm->GetStyle(F(uint32_t, 0xc0), 0);
            if (style) {
                uint32_t oldv = *(uint32_t*)(style + 0x224);
                *(uint32_t*)(style + 0x224) = F(uint32_t, 0x224);
                float l = F(float, 0x258) + F(float, 0x238);
                float t = F(float, 0x25c) + F(float, 0x23c);
                float r = F(float, 0x258) + F(float, 0x240);
                float b = F(float, 0x25c) + F(float, 0x244);
                LineLayout* ll = (LineLayout*)((char*)this + 0x7b0);
                ll->Clear(1);
                Typesetter* ts = (Typesetter*)((char*)this + 0x280);
                int res = ts->F89dc00(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, l, t, r, b, style, ll, 0x14);
                uint32_t h = rc->Begin2D(0);
                bool flag = W()->GetObj()->V8c();
                ((DropShadow*)((char*)this + 0x860))->F96e740(h, F(uint32_t, 0x7dc), F(uint32_t, 0x804), res,
                                                             F(uint32_t, 0x224), *F(uint16_t*, 0xb0), flag);
                *(uint32_t*)(style + 0x224) = oldv;
            }
        }
    }
    return true;
}

// @ 0x00964f10
bool WB::CalcSize(int a, float* out)
{
    if (a != 0)
        return false;
    out[0] = eastl_max(F(float, 0x90) - F(float, 0x88), 14.0f);
    out[1] = eastl_max(F(float, 0x94) - F(float, 0x8c), 14.0f);
    float lxy[2];
    lxy[0] = 0.0f;
    lxy[1] = 0.0f;
    void* obj = F(void*, 0x1e0);
    if (obj)
        ((IPainterVt*)obj)->GetSize(lxy, 0, 0);
    if ((obj == 0 || (lxy[0] == 0.0f && lxy[1] == 0.0f)) && F(uint16_t*, 0xb0) == F(uint16_t*, 0xb4))
        return false;
    float pw = out[0];
    float tx = 0.0f, ty = 0.0f;
    float fv7 = 0.0f, fv8 = 0.0f;
    if (F(uint16_t*, 0xb0) != F(uint16_t*, 0xb4)) {
        StyleManager* sm = GetStyleManager(true);
        if (sm) {
            char* style = (char*)sm->GetStyle(F(uint32_t, 0xc0), 0);
            if (style) {
                float bh = F(float, 0x240) - F(float, 0x238);
                if (bh < 1.0f)
                    bh = 100.0f;
                LineLayout* ll = (LineLayout*)((char*)this + 0x7b0);
                Typesetter* ts = (Typesetter*)((char*)this + 0x280);
                ll->Clear(1);
                ts->F89dc00(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, 0.0f, 0.0f, bh, 10000.0f, style, ll, 0);
                if (F(uint32_t, 0x858) < 2) {
                    ll->Clear(1);
                    ts->LayoutLine(F(uint16_t*, 0xb0), (F(int, 0xb4) - F(int, 0xb0)) >> 1, 0.0f, 0.0f, style);
                }
                float cnt = (float)F(uint32_t, 0x858);
                tx = (F(float, 0x848) + F(float, 0x254)) + F(float, 0x24c);
                ty = ((F(float, 0x850) - F(float, 0x854)) * cnt + F(float, 0x250)) + F(float, 0x248);
                fv7 = tx;
                fv8 = ty;
            }
        }
    }
    if (!(F(uint8_t, 0x218) & 2)) {
        pw = eastl_max(lxy[0], fv8);
    } else {
        uint32_t m = F(uint32_t, 0x21c);
        if (m != 0) {
            if (m > 2) {
                if (m == 3)
                    pw = lxy[0];
            } else {
                pw = fv8 + lxy[0];
            }
        }
    }
    float ph = eastl_max(lxy[1], fv7);
    out[0] = eastl_max(pw, 14.0f);
    out[1] = eastl_max(ph, 14.0f);
    return true;
}

// @ 0x00965230
void WinButton::EmbeddedCalcSize(char flag)
{
  if (mTextBegin == mTextEnd) return;
  EA::Text::StyleManager_s0096_5230* pStyleManager = EA::Text::GetStyleManager_s0096_5230(true);
  if (pStyleManager == 0) return;
  EA::Text::TextStyle_s0096_5230 const* pStyle = pStyleManager->GetStyle(mStyleId, 0);
  if (pStyle == 0) return;

  float scale = 1.0f;
  LayoutResult* pInfo;

  if (flag != 0) {
    EA::Text::LineLayout_s0096_5230* pLine = (EA::Text::LineLayout_s0096_5230*)mLineLayout;
    pLine->Clear(true);
    ((EA::Text::Typesetter_s0096_5230*)((char*)this + 0x280))
        ->LayoutParagraph(mTextBegin, (unsigned int)(mTextEnd - mTextBegin), mCaptionRect.mLeft,
                          mCaptionRect.mTop, mCaptionRect.mRight, 100000.0f, pStyle, pLine, 0);
    scale = (float)mLineHeight;
    pInfo = (LayoutResult*)((char*)this + 0x840);
  } else {
    EA::Text::Typesetter_s0096_5230* pTypesetter = (EA::Text::Typesetter_s0096_5230*)((char*)this + 0x280);
    pTypesetter->LayoutLine(mTextBegin, (unsigned int)(mTextEnd - mTextBegin), mCaptionRect.mLeft,
                            mCaptionRect.mTop, pStyle);
    pInfo = (LayoutResult*)((char*)pTypesetter->GetLineLayout() + 0x90);
  }

  RectF r;
  r.mLeft = mWindowRect.mLeft;
  r.mTop = mWindowRect.mTop;
  r.mBottom = (pInfo->mF10 - pInfo->mF14) * scale + mWindowRect.Height() + mCaptionRect.mTop -
              mCaptionRect.mBottom + mWindowRect.mTop;
  r.mRight = mWindowRect.Width() + pInfo->mF08 + mCaptionRect.mLeft - mCaptionRect.mRight +
             mWindowRect.mLeft;
  IWinButtonBase* pBase = (IWinButtonBase*)((char*)this + 4);
  pBase->SetLayoutRect(&r);
}

// @ 0x009653f0
void WinButton::Refresh()
{
  mDrawableRect.mLeft = 0.0f;
  mDrawableRect.mTop = 0.0f;
  mDrawableRect.mRight = mWindowRect.Width();
  mDrawableRect.mBottom = mWindowRect.Height();

  mCaptionRect.mLeft = 0.0f;
  mCaptionRect.mTop = 0.0f;
  mCaptionRect.mRight = mWindowRect.Width();
  mCaptionRect.mBottom = mWindowRect.Height();

  float w = mWindowRect.Width();
  float h = mWindowRect.Height();

  if ((mFlags & 6) != 0) {
    Vec2f size;
    size.x = 0.0f;
    size.y = 0.0f;
    IDrawable* pDrawable = mDrawable;
    if (pDrawable != 0) pDrawable->v6(&size, 0, 0);
    if ((mFlags & 2) != 0 && w > size.x) {
      switch (mAlignment) {
        case 1:
          mDrawableRect.mLeft = 0.0f;
          mDrawableRect.mRight = size.x;
          mCaptionRect.mLeft = size.x;
          mCaptionRect.mRight = w;
          break;
        case 2:
          mDrawableRect.mLeft = w - size.x;
          mDrawableRect.mRight = w;
          mCaptionRect.mLeft = 0.0f;
          mCaptionRect.mRight = w - size.x;
          break;
        case 3: {
          float l = (w - size.x) * 0.5f;
          mDrawableRect.mLeft = l;
          mDrawableRect.mRight = l + size.x;
          mCaptionRect.mLeft = l;
          mCaptionRect.mRight = l + size.x;
          break;
        }
      }
    }
    if ((mFlags & 4) != 0 && h > size.y) {
      float t = (h - size.y) * 0.5f;
      mDrawableRect.mTop = t;
      mDrawableRect.mBottom = t + size.y;
    }
  }

  mCaptionRect.mLeft += mCaptionOffsets[0];
  mCaptionRect.mTop += mCaptionOffsets[1];
  mCaptionRect.mRight -= mCaptionOffsets[2];
  mCaptionRect.mBottom -= mCaptionOffsets[3];
}

// @ 0x009656d0
namespace EA { namespace UTFWinControls {
void __thiscall ButtonDrawable::Paint(UTFWin::RenderContext_s0096_56d0* ctx, const float* rc, const DrawState* st)
{
    using namespace UTFWin;
    if (mpImage) {
        float src[4];
        if (GetSourceRect(st->flags, src)) {
            Graphics2D* g = ctx->Begin2D(0);
            g->SetColor(0xffffffff);
            if (mbTileable) {
                float edge[4];
                edge[0] = 0.33333334f;
                edge[1] = 0.33333334f;
                edge[2] = 0.6666667f;
                edge[3] = 0.6666667f;
                Drawing::BltEdgeStretch(g, rc, src, mpImage, edge, kOne, kOne);
            } else {
                g->DrawImageScaled(rc, mpImage, src);
            }
            return;
        }
    }
    Graphics2D* g = ctx->Begin2D(0);
    g->SetColor(0xffffffff);
    uint32_t flags = st->flags;
    uint32_t state = flags & 7;
    if (flags & 8)
        state = 3;
    switch (state) {
    case 0:
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xffffffff);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        g->SetColor(0xfff1efe2);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff716f64);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        break;
    case 1:
    case 3:
    case 8:
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff000000);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        break;
    case 2:
        g->SetColor(0xffece9d8);
        FillRect(g, rc[0] + 3.0f, rc[1] + 3.0f, rc[2] - 3.0f, rc[3] - 3.0f);
        g->SetColor(0xffffffff);
        FillRect(g, rc[0] + 1.0f, rc[1] + 1.0f, rc[2] - 2.0f, rc[1] + 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[1] + 2.0f, rc[0] + 2.0f, rc[3] - 2.0f);
        g->SetColor(0xfff1efe2);
        FillRect(g, rc[0] + 2.0f, rc[1] + 2.0f, rc[2] - 3.0f, rc[1] + 3.0f);
        FillRect(g, rc[0] + 2.0f, rc[1] + 3.0f, rc[0] + 3.0f, rc[3] - 3.0f);
        g->SetColor(0xff716f64);
        FillRect(g, rc[2] - 2.0f, rc[1] + 1.0f, rc[2] - 1.0f, rc[3] - 2.0f);
        FillRect(g, rc[0] + 1.0f, rc[3] - 2.0f, rc[2] - 1.0f, rc[3] - 1.0f);
        g->SetColor(0xffaca899);
        FillRect(g, rc[2] - 3.0f, rc[1] + 2.0f, rc[2] - 2.0f, rc[3] - 3.0f);
        FillRect(g, rc[0] + 2.0f, rc[3] - 3.0f, rc[2] - 2.0f, rc[3] - 2.0f);
        g->SetColor(0xff000000);
        FillRect(g, rc[0], rc[1], rc[2] - 1.0f, rc[1] + 1.0f);
        FillRect(g, rc[0], rc[1] + 1.0f, rc[0] + 1.0f, rc[3] - 1.0f);
        FillRect(g, rc[2] - 1.0f, rc[1], rc[2], rc[3] - 1.0f);
        FillRect(g, rc[0], rc[3] - 1.0f, rc[2], rc[3]);
        break;
    default:
        break;
    }
}
}}  // namespace EA::UTFWinControls

// @ 0x00966b20
uint8_t S_966b20::m(uint32_t param_2, float* param_3)
{
    if (F_s0096_6b20(this, 0x10) != 0) {
        uint32_t v = 0;
        switch (param_2 & 7) {
        case 0: v = (((uint8_t)param_2 & 8) | 4) >> 2; break;
        case 1: v = 0; break;
        case 2: v = 2; break;
        case 3: v = 3; break;
        }
        param_3[0] = (float)v * g_13eb8a0;
        param_3[1] = 0.0f;
        param_3[2] = (float)(v + 1) * g_13eb8a0;
        param_3[3] = *(float*)&g_1485720;
        return 1;
    }
    return 0;
}

// @ 0x00966bb0
uint8_t S_966bb0::m(uint32_t param_2, float* param_3)
{
    if (F_s0096_6b20(this, 0x10) != 0) {
        uint32_t v = 0;
        switch (param_2 & 7) {
        case 0:
        case 1: v = (uint32_t)(-(int)(((uint8_t)(param_2 & 8)) != 0)) & 3; break;
        case 2: v = ((uint32_t)(-(int)(((uint8_t)(param_2 & 8)) != 0)) & 3) + 1; break;
        case 3: v = ((uint32_t)(-(int)(((uint8_t)(param_2 & 8)) != 0)) & 3) + 2; break;
        }
        param_3[0] = (float)v * *(float*)&g_1440f84;
        param_3[1] = 0.0f;
        param_3[2] = (float)(v + 1) * *(float*)&g_1440f84;
        param_3[3] = *(float*)&g_1485720;
        return 1;
    }
    return 0;
}

// @ 0x00966c70
void S_966c70::m()
{
    uint8_t* this_ = (uint8_t*)this;
    if (FB(this_, 0x210) == 0)
        return;

    void* sub4 = this_ + 4;
    void** vt = *(void***)sub4;
    uint32_t fn = ((uint32_t*)vt)[0x7c / 4];
    FB(this_, 0x210) = 0;
    ((void (__thiscall*)(void*, int, int))fn)(sub4, 8, 0);

    VCALL0(this_, 0x9c);
    VCALL0(this_, 0xa0);

    uint8_t* child = *(uint8_t**)(this_ + 0x38);
    if (child != 0 && F_s0096_6b20(this_, 0x214) == 3 &&
        (FB(this_, 0xac) & 4) != 0 && F_s0096_6b20(this_, 0x220) != 0) {
        void* begin;
        VCALL1(child + 4, 0xcc, (uint32_t)&begin);
        void* end;
        uint32_t* endp = (uint32_t*)VCALL1P(child + 4, 0xd0, (uint32_t)&end);
        while (begin != (void*)*endp) {
            uint8_t* node = (uint8_t*)begin;
            uint8_t* obj = node - 4;
            if (obj != 0) {
                void* cast = VCALL1P(obj, 0x0c, 0x8ed27e7a);
                if (cast != 0 && cast != (void*)(this_ + 0x20c)) {
                    if (VCALL0R(cast, 0x40) == F_s0096_6b20(this_, 0x220) &&
                        (VCALL0R(cast, 0x20) & 0x20) == 0) {
                        VCALL2(cast, 0x28, 4, 0);
                    }
                }
            }
            begin = *(void**)node;
            endp = (uint32_t*)VCALL1P(child + 4, 0xd0, (uint32_t)&end);
        }
    }

    VCALL2(this_ + 0x20c, 0x28, 0x20, 0);
    VCALL0(this_ + 4, 0x90);
}

// @ 0x00966dc0
void* S_966dc0::m()
{
    void* this_ = this;
    F_s0096_6b20(this_, 0x04) = 0x13fa72c;
    F_s0096_6b20(this_, 0x08) = 0;
    F_s0096_6b20(this_, 0x0c) = 0x13fa72c;
    F_s0096_6b20(this_, 0x00) = 0x1441088;
    F_s0096_6b20(this_, 0x04) = 0x1441070;
    F_s0096_6b20(this_, 0x0c) = 0x1441058;
    F_s0096_6b20(this_, 0x10) = 0;
    FB(this_, 0x14) = 0;
    return this_;
}

// @ 0x00966df0
void* S_966df0::m(uint8_t param_2)
{
    void* this_ = this;
    void* img = (void*)F_s0096_6b20(this_, 0x10);
    F_s0096_6b20(this_, 0x00) = 0x1441088;
    F_s0096_6b20(this_, 0x04) = 0x1441070;
    F_s0096_6b20(this_, 0x0c) = 0x1441058;
    if (img != 0)
        VCALL0(img, 0x04);
    F_s0096_6b20(this_, 0x0c) = 0x13eb938;
    F_s0096_6b20(this_, 0x04) = 0x13eb938;
    F_s0096_6b20(this_, 0x00) = 0x13eb938;
    if ((param_2 & 1) != 0)
        FUN_00951330(this_);
    return this_;
}

// @ 0x00966e40
void S_966e40::m()
{
    void* this_ = this;
    S_8323d0* ll = (S_8323d0*)((uint8_t*)this_ + 0x7b0);
    F_s0096_6b20(this_, 0x00) = 0x1441240;
    F_s0096_6b20(this_, 0x04) = 0x1441120;
    F_s0096_6b20(this_, 0x20c) = 0x14410b0;
    ll->m();
    ((S_89c540*)((uint8_t*)this_ + 0x280))->m();
    F_s0096_6b20(this_, 0x20c) = 0x13eb938;
    ((S_962740*)this_)->m();
}

// @ 0x00966ed0
DrawableStd* BasicFactoryStd::CreateInstance(uint32_t, void* heap)
{
    if (heap == 0)
        heap = FUN_009512c0();
    DrawableStd* p = (DrawableStd*)FUN_009512d0(
        0x18, 4, "UTFWin/EA::UTFWinControls::ButtonDrawableStandard", heap);
    if (p != 0) {
        p->v04 = 0x13fa72c;
        p->v08 = 0;
        p->v0c = 0x13fa72c;
        p->v10 = 0;
        p->v14 = 0;
        p->v00 = 0x141788c;
        p->v04 = 0x1417874;
        p->v0c = 0x141785c;
    }
    return p;
}

// @ 0x00966f30
DrawableStd* BasicFactoryRadio::CreateInstance(uint32_t, void* heap)
{
    if (heap == 0)
        heap = FUN_009512c0();
    DrawableStd* p = (DrawableStd*)FUN_009512d0(
        0x18, 4, "UTFWin/EA::UTFWinControls::ButtonDrawableRadio", heap);
    if (p != 0) {
        p->v04 = 0x13fa72c;
        p->v08 = 0;
        p->v0c = 0x13fa72c;
        p->v10 = 0;
        p->v14 = 0;
        p->v00 = 0x14178b0;
        p->v04 = 0x1417874;
        p->v0c = 0x141785c;
    }
    return p;
}

// @ 0x00966f90
void* S_966f90::m()
{
    void* this_ = this;
    ((S_962a10*)this_)->m();
    F_s0096_6b20(this_, 0x20c) = 0x1440fe8;
    F_s0096_6b20(this_, 0x00) = 0x1441240;
    F_s0096_6b20(this_, 0x04) = 0x1441120;
    F_s0096_6b20(this_, 0x20c) = 0x14410b0;
    F_s0096_6b20(this_, 0x214) = 1;
    F_s0096_6b20(this_, 0x21c) = 1;
    FB(this_, 0x210) = 0;
    F_s0096_6b20(this_, 0x218) = 0;
    F_s0096_6b20(this_, 0x220) = 0;
    F_s0096_6b20(this_, 0x224) = 0;
    FF(this_, 0x228) = 0.0f;
    FF(this_, 0x22c) = 0.0f;
    FF(this_, 0x230) = 1.0f;
    FF(this_, 0x234) = 1.0f;
    FF(this_, 0x238) = 0.0f;
    FF(this_, 0x23c) = 0.0f;
    FF(this_, 0x240) = 1.0f;
    FF(this_, 0x244) = 1.0f;
    FF(this_, 0x248) = 1.0f;
    FF(this_, 0x24c) = 1.0f;
    FF(this_, 0x250) = 1.0f;
    FF(this_, 0x254) = 1.0f;
    FF(this_, 0x258) = 1.0f;
    FF(this_, 0x25c) = 1.0f;
    ((S_89d820*)((uint8_t*)this_ + 0x280))->m(0);
    ((S_898bd0*)((uint8_t*)this_ + 0x7b0))->m(0);
    {
        uint8_t* l = (uint8_t*)this_ + 0x860;
        F_s0096_6b20(l, 0x00) = 0;
        F_s0096_6b20(l, 0x04) = 2;
        F_s0096_6b20(l, 0x08) = 3;
        FF(l, 0x14) = 0.0f;
        FF(l, 0x18) = 0.0f;
        FF(l, 0x0c) = 0.0f;
        FF(l, 0x10) = 0.0f;
        F_s0096_6b20(l, 0x24) = 0;
    }
    ((S_830150*)((uint8_t*)this_ + 0x860))->m(2);
    F_s0096_6b20(this_, 0x260) = 0;
    F_s0096_6b20(this_, 0x264) = 0;
    F_s0096_6b20(this_, 0x268) = 0;
    F_s0096_6b20(this_, 0x26c) = 0;
    F_s0096_6b20(this_, 0x270) = 0;
    F_s0096_6b20(this_, 0x274) = 0;
    F_s0096_6b20(this_, 0x278) = 0;
    F_s0096_6b20(this_, 0x27c) = 0;
    F_s0096_6b20(this_, 0xac) |= (F_s0096_6b20(this_, 0x2c) >> 1) & 1;
    if (FB(this_, 0x210) == 0) {
        void* s4 = (uint8_t*)this_ + 4;
        void** vt = *(void***)s4;
        void (__thiscall* fn)(void*, int, int) =
            (void (__thiscall*)(void*, int, int))vt[0x7c / 4];
        FB(this_, 0x210) = 1;
        fn(s4, 8, 1);
    }
    return this_;
}

// @ 0x00967120
void* S_967120::m(uint8_t param_2)
{
    void* this_ = this;
    S_8323d0* ll = (S_8323d0*)((uint8_t*)this_ + 0x7b0);
    F_s0096_6b20(this_, 0x00) = 0x1441240;
    F_s0096_6b20(this_, 0x04) = 0x1441120;
    F_s0096_6b20(this_, 0x20c) = 0x14410b0;
    ll->m();
    ((S_89c540*)((uint8_t*)this_ + 0x280))->m();
    F_s0096_6b20(this_, 0x20c) = 0x13eb938;
    ((S_962740*)this_)->m();
    if ((param_2 & 1) != 0)
        FUN_00951330(this_);
    return this_;
}

// @ 0x009671c0
extern "C" void* __cdecl FUN_009671c0(uint32_t param_1, uint32_t param_2, uint32_t param_3)
{
    void* heap = FUN_009512c0();
    void* p = FUN_009512d0(0x888, 4, "UTFWin/WinButton", heap);
    if (p == 0)
        return 0;
    uint8_t* obj = (uint8_t*)((S_966f90*)p)->m();
    if (obj == 0)
        return 0;
    uint8_t* sub = obj + 0x20c;
    if (sub != 0) {
        VCALL1(sub, 0x1c, param_1);
        VCALL1(sub, 0x30, param_2);
        VCALL1(sub, 0x44, param_3);

        void* heap2 = FUN_009512c0();
        DrawableStd* d = (DrawableStd*)FUN_009512d0(
            0x18, 4, "UTFWin/ButtonDrawableStandard", heap2);
        uint8_t* dp;
        if (d == 0) {
            dp = 0;
        } else {
            dp = (uint8_t*)d + 0x0c;
            d->v04 = 0x13fa72c;
            d->v08 = 0;
            d->v0c = 0x13fa72c;
            d->v10 = 0;
            d->v14 = 0;
            d->v00 = 0x141788c;
            d->v04 = 0x1417874;
            d->v0c = 0x141785c;
        }
        VCALL1(sub, 0x60, (uint32_t)dp);
        VCALL2(sub, 0x4c, 0, 0xff00044a);
        VCALL2(sub, 0x4c, 3, 0xff0055e6);
    }
    return sub;
}
