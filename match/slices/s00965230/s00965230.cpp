// Spore SporeApp.exe 0x00965230..0x009656a3
//   EA::UTFWinControls::WinButton::EmbeddedCalcSize / Refresh and a
//   UI::ButtonDrawableRadio teardown helper.
//
// 0x00965230  EA::UTFWinControls::WinButton::EmbeddedCalcSize(char)
// 0x009653f0  EA::UTFWinControls::WinButton::Refresh()
// 0x00965670  FUN_00965670  (drawable vtable reset + release)
//
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

namespace EA {
namespace Text {

struct TextStyle;
class LineLayout;
class StyleManager;
class Typesetter;

StyleManager* GetStyleManager(bool);

class StyleManager {
 public:
  TextStyle const* GetStyle(unsigned int id, TextStyle* p) const;  // +0x0
};

class LineLayout {
 public:
  void Clear(bool b);  // +0x0
};

class Typesetter {
 public:
  int   LayoutLine(wchar_t const* text, unsigned int len, float x, float y,
                   TextStyle const* style);  // +0x0
  int   LayoutParagraph(wchar_t const* text, unsigned int len, float x, float y, float maxW,
                        float maxH, TextStyle const* style, LineLayout* pLine, int flag);
  void* GetLineLayout();
};

}  // namespace Text
}  // namespace EA

// Rect in float space used all over the text/window code.
struct RectF {
  RectF() {}
  RectF(float l, float t, float r, float b) : mLeft(l), mTop(t), mRight(r), mBottom(b) {}
  float Width() const { return mRight - mLeft; }
  float Height() const { return mBottom - mTop; }
  float mLeft, mTop, mRight, mBottom;
};

// Result block read after a text layout pass: three floats at +0x08/+0x10/+0x14.
struct LayoutResult {
  char  mPad0[8];
  float mF08;  // +0x08
  char  mPad1[4];
  float mF10;  // +0x10
  float mF14;  // +0x14
};

// Small float pair written by a text/drawable query.
struct Vec2f {
  float x, y;
};

// The drawable object stored at WinButton+0x1e0; slot 6 fills in an extent pair.
struct IDrawable {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual void v6(Vec2f* pSize, int a, int b);  // +0x18
};

// Second base sub-object of WinButton (vptr at +0x04); slot 0x6c takes a rect.
struct IWinButtonBase {
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26();
  virtual void SetLayoutRect(RectF const* pRect);  // +0x6c
};

#pragma pack(push, 4)
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
#pragma pack(pop)

// @ 0x00965230
void WinButton::EmbeddedCalcSize(char flag) {
  if (mTextBegin == mTextEnd) return;
  EA::Text::StyleManager* pStyleManager = EA::Text::GetStyleManager(true);
  if (pStyleManager == 0) return;
  EA::Text::TextStyle const* pStyle = pStyleManager->GetStyle(mStyleId, 0);
  if (pStyle == 0) return;

  float scale = 1.0f;
  LayoutResult* pInfo;

  if (flag != 0) {
    EA::Text::LineLayout* pLine = (EA::Text::LineLayout*)mLineLayout;
    pLine->Clear(true);
    ((EA::Text::Typesetter*)((char*)this + 0x280))
        ->LayoutParagraph(mTextBegin, (unsigned int)(mTextEnd - mTextBegin), mCaptionRect.mLeft,
                          mCaptionRect.mTop, mCaptionRect.mRight, 100000.0f, pStyle, pLine, 0);
    scale = (float)mLineHeight;
    pInfo = (LayoutResult*)((char*)this + 0x840);
  } else {
    EA::Text::Typesetter* pTypesetter = (EA::Text::Typesetter*)((char*)this + 0x280);
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
void WinButton::Refresh() {
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

// ---------------------------------------------------------------------------
// UI::ButtonDrawableRadio teardown helper (three vptrs at +0x00/+0x04/+0x0c).
// ---------------------------------------------------------------------------
extern "C" char vtbl_ButtonDrawableRadio[];  // 0x1441088
extern "C" char ptr_01441070[];              // 0x1441070
extern "C" char ptr_01441058[];              // 0x1441058
extern "C" char vtbl_GmeEditorResBase[];     // 0x13eb938

struct RefCounted {
  virtual int v0();
  virtual int v1();
};

struct ButtonDrawableRadio {
  void* mVT0;      // 0x00
  void* mVT1;      // 0x04
  void* mUnk08;    // 0x08
  void* mVT2;      // 0x0c
  void* mObj10;    // 0x10
  void  FUN_00965670();
};

// @ 0x00965670
void ButtonDrawableRadio::FUN_00965670() {
  RefCounted* pObj = (RefCounted*)mObj10;
  mVT0 = vtbl_ButtonDrawableRadio;
  mVT1 = ptr_01441070;
  mVT2 = ptr_01441058;
  if (pObj != 0) pObj->v1();
  mVT2 = vtbl_GmeEditorResBase;
  mVT1 = vtbl_GmeEditorResBase;
  mVT0 = vtbl_GmeEditorResBase;
}
