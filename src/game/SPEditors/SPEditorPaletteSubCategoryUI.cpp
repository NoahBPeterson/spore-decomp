// src/game/SPEditors/SPEditorPaletteSubCategoryUI.cpp -- migrated from slice(s) s005ca070, s005c9230 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPaletteSubCategoryUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <new>
#include "SP/cSPPaletteSubCategoryUI.h"
#include "EA/UTFWinControls/IButtonDrawable.h"
#include "EA/UTFWin/IDrawable.h"
#include "EA/UTFWinControls/IWinButton.h"
#include "EA/UTFWin/IWinProc.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPaletteCategory.h"
#include "SP/cSPPaletteCategoryUI.h"
#include "SP/cSPPaletteUI.h"
#include "cSPUILayout.h"
#include "SP/cString.h"

// ---- items of slice s005ca070 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line); // 0x00f473a0
#define PV(n) virtual void pv##n();
namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
}
}
namespace EA {
namespace UTFWin {
struct Rect {  // EA::RectT<float>: user copy ctor (movss) and operator= (fld/fstp), as in the original
  float mLeft, mTop, mRight, mBottom;
  Rect() {}
  Rect(const Rect& r) : mLeft(r.mLeft), mTop(r.mTop), mRight(r.mRight), mBottom(r.mBottom) {}
  Rect& operator=(const Rect& r) {
    mLeft = r.mLeft;
    mTop = r.mTop;
    mRight = r.mRight;
    mBottom = r.mBottom;
    return *this;
  }
};
}
}
namespace EA {
namespace UTFWin {
class IButtonDrawable {  // what IDrawable::Cast(0x103c1908) returns
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
  PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual void SetImageIndex(int index);  // +0x1c
};
}
}
namespace EA {
namespace UTFWin {
class IDrawable_s005c_a070 : public IUnknown32 {
 public:
  PV(2)
  virtual IButtonDrawable* Cast(unsigned int typeID);  // +0xc
};
}
}
namespace EA {
namespace UTFWin {
class IWinProc_s005c_a070 {
 public:
  virtual int AddRef();
  virtual int Release();
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s005c_a070 : public IUnknown32 {
 public:
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const Rect& GetArea();      // +0x34
  virtual const Rect& GetRealArea();  // +0x38
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  virtual void SetArea(const Rect& area);        // +0x60
  virtual void SetLocation(float x, float y);    // +0x64
  virtual void SetSize(float w, float h);        // +0x68
  PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);    // +0x7c
  virtual void SetCaption(const wchar_t* text);  // +0x80
  virtual void SetTextFontID(unsigned int id);   // +0x84
  PV(34) PV(35)
  virtual void Invalidate();                     // +0x90
  PV(37) PV(38) PV(39) PV(40) PV(41)
  virtual IDrawable_s005c_a070* GetDrawable();              // +0xa8
  PV(43) PV(44) PV(45) PV(46) PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s005c_a070* proc);       // +0x104
};
}
}
namespace EA {
namespace UTFWin {
class IWinButton : public IUnknown32 {
 public:
  PV(2) PV(3)
  virtual IWindow_s005c_a070* ToWindow();  // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
  PV(11) PV(12) PV(13) PV(14) PV(15) PV(16)
  virtual void SetButtonGroupID(unsigned int id);         // +0x44
};
}
}
using EA::UTFWin::IWindow_s005c_a070;
using EA::UTFWin::IWinButton;
using EA::UTFWin::IWinProc_s005c_a070;
using EA::UTFWin::Rect;
class cSPPaletteCategory;
class cSPPaletteCategoryUI {
 public:
  virtual int pvIHandler0();
  virtual int pvIHandler1();
  virtual int AddRef();   // +8
  virtual int Release();  // +0xc
  cSPPaletteCategoryUI();                                                   // 0x005c3e00
  void Init(cSPPaletteCategory* data, IWindow_s005c_a070* parent, unsigned int arg3);  // 0x005c53c0
  void SetVisibility(bool visible);                                         // 0x005c2960
  void Update(int deltaTime);    // 0x005c28b0
  void Shutdown();               // 0x005c4e40
  bool IsPaintByNumber();        // 0x005c2cd0
};
struct Key {
  unsigned int mInstance, mType, mGroup;
  Key() {}
  Key(unsigned int instance, unsigned int type, unsigned int group)
      : mInstance(instance), mType(type), mGroup(group) {}
};
struct Vector2 {
  float x, y;
  Vector2(float x_, float y_) : x(x_), y(y_) {}
  Vector2(const Vector2& v) : x(v.x), y(v.y) {}
};
namespace eastl {
template <typename T>
class sp_vec {  // vector<T, sp_vector_allocator>: begin/end/capacity + 2-word allocator
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
  void DoInsertValue(T* position, const T& value);
  void push_back(const T& value) {
    if (mpEnd < mpCapacity)
      ::new (mpEnd++) T(value);
    else
      DoInsertValue(mpEnd, value);
  }
};  // namespace eastl
}
template <typename T>
class ARC {
 public:
  T* mpObject;
  ARC() : mpObject(0) {}
  ARC(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ARC(const ARC& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~ARC() { if (mpObject) mpObject->Release(); }
  ARC& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};
class cString {
 public:
  const wchar_t* GetText();  // 0x006b55c0
};
class cSPPaletteCategory {  // retail layout (RefCountVTemplate + IUnknown32 bases)
 public:
  char pad0[0x34];
  eastl::sp_vec<cSPPaletteCategory*> mSubCategories;  // +0x34 (really AutoRefCount elements)
  char pad48[0x5c - 0x48];
  cString mCategoryName;                              // +0x5c
  char pad6c[0x7c - 0x5c - 0x14];
  Key mButtonImageKey;                                // +0x7c
  cSPPaletteCategory* GetSubCategory(int index);      // 0x005cae30
};
IWinButton* CreateButtonFromKeys(Key* keys, int state, int index, Vector2 offset, IWindow_s005c_a070* parent);  // 0x00808930
IWindow_s005c_a070* CreateChildImageWindow(IWindow_s005c_a070* parent);                         // 0x00806370
IWindow_s005c_a070* CreateTextWindow(IWindow_s005c_a070* parent);                               // 0x008064c0
IWindow_s005c_a070* CreateImageWindow(Key* key, Vector2 offset, IWindow_s005c_a070* parent);    // 0x00807880
class cSPPaletteSubCategoryUI : public IWinProc_s005c_a070 {
 public:
  char pad04[0xc];                                       // IHandler + RefCountVTemplate bases
  ARC<IWindow_s005c_a070> mWinRoot;                                 // +0x10
  int mCurrentOpenCategory;                              // +0x14
  float mButtonHeight;                                   // +0x18
  float mSubCategoryHeight;                              // +0x1c
  Rect mRootArea;                                        // +0x20
  eastl::sp_vec<IWinButton*> mButtons;                   // +0x30
  eastl::sp_vec<IWindow_s005c_a070*> mArrows;                       // +0x44
  eastl::sp_vec<IWindow_s005c_a070*> mSubWindows;                   // +0x58
  eastl::sp_vec<ARC<cSPPaletteCategoryUI> > mCategoryUIs;  // +0x6c
  eastl::sp_vec<float> mTargetAlphas;                    // +0x80

  void Init(IWindow_s005c_a070* parent, cSPPaletteCategory* data, unsigned int arg3);  // 0x005ca070
  void Shutdown();
};
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s005ca070 end

// @ 0x005c9dd0
bool cUIMissionCardDoMessageStub(int param_2, void* message)
{
  (void)param_2;
  (void)message;
  return false;
}

// @ 0x005ca070
void cSPPaletteSubCategoryUI::Init(IWindow_s005c_a070* parent, cSPPaletteCategory* data, unsigned int arg3)
{
  if (!parent)
    return;
  Key keys[9] = {
      Key(0x85cb8ed9, 0x2f7d0004, 0x100d976e), Key(0x24d4b70a, 0x2f7d0004, 0x100d976e),
      Key(0xea53b64f, 0x2f7d0004, 0x100d976e), Key(0x31d94965, 0x2f7d0004, 0x100d976e),
      Key(0x917b2e8b, 0x2f7d0004, 0x100d976e), Key(0x24d4b70a, 0x2f7d0004, 0x100d976e),
      Key(0xbf128935, 0x2f7d0004, 0x100d976e), Key(0x0c3f5c73, 0x2f7d0004, 0x100d976e),
      Key(0x85cb8ed9, 0x2f7d0004, 0x100d976e)};
  mWinRoot = parent;
  mWinRoot->AddWinProc(this);
  mRootArea = mWinRoot->GetRealArea();
  int count = (int)data->mSubCategories.size();
  for (int i = 0; i < count; i++) {
    IWinButton* btn = CreateButtonFromKeys(keys, 3, i, Vector2(0.0f, 0.0f), mWinRoot);
    if (!btn)
      continue;
    IWindow_s005c_a070* btnWin = btn->ToWindow();
    EA::UTFWin::IDrawable_s005c_a070* drawable = btnWin->GetDrawable();
    if (drawable) {
      EA::UTFWin::IButtonDrawable* bd = drawable->Cast(0x103c1908);
      if (bd)
        bd->SetImageIndex(2);
    }
    if (i == 0) {
      const Rect& r = btnWin->GetArea();
      mButtonHeight = r.mBottom - r.mTop;
      mSubCategoryHeight = (mRootArea.mBottom - mRootArea.mTop) - (float)count * mButtonHeight;
      btn->SetButtonStateFlag(4, true);
    }
    btn->SetButtonGroupID((unsigned int)&mWinRoot);
    Rect cell;
    cell.mLeft = 0.0f;
    cell.mTop = 0.0f;
    cell.mRight = mRootArea.mRight - mRootArea.mLeft;
    cell.mBottom = mButtonHeight;
    btnWin->SetArea(cell);
    float y;
    if (i > mCurrentOpenCategory)
      y = (mRootArea.mBottom - mRootArea.mTop) - (float)((int)mButtons.size() - i) * mButtonHeight;
    else
      y = (float)i * mButtonHeight;
    btnWin->SetLocation(0.0f, y);
    mButtons.push_back(btn);

    IWindow_s005c_a070* subWin = CreateChildImageWindow(mWinRoot);
    if (!subWin)
      continue;
    subWin->SetFlag(2, false);
    subWin->SetFlag(0x10, true);
    subWin->SetSize(mRootArea.mRight - mRootArea.mLeft, mSubCategoryHeight);
    mSubWindows.push_back(subWin);
    float alpha = (i == 0) ? 1.0f : 0.0f;
    mTargetAlphas.push_back(alpha);

    ARC<cSPPaletteCategoryUI> cat(new ("Editor", 0, 0, 0, 0) cSPPaletteCategoryUI());
    cat->Init(data->GetSubCategory(i), subWin, arg3);
    cat->SetVisibility(true);
    mCategoryUIs.push_back(cat);

    IWindow_s005c_a070* label = CreateTextWindow(btnWin);
    if (label) {
      label->SetTextFontID(0x535e94ca);
      const wchar_t* caption = data->GetSubCategory(i)->mCategoryName.GetText();
      label->SetCaption(caption);
      label->SetFlag(2, false);
      label->SetFlag(0x10, true);
      label->Invalidate();
    }

    IWindow_s005c_a070* arrow = CreateImageWindow((Key*)0x1516838, Vector2(0.0f, 0.0f), btnWin);
    if (arrow) {
      Rect a = arrow->GetArea();
      arrow->SetSize(a.mRight - a.mLeft, a.mBottom - a.mTop);
      Rect b = arrow->GetArea();
      float inset = (mButtonHeight - (b.mBottom - b.mTop)) * 0.5f;
      b.mTop = b.mTop + inset;
      b.mBottom = b.mBottom + inset;
      arrow->SetArea(b);
      arrow->SetFlag(2, false);
      arrow->SetFlag(0x10, true);
      mArrows.push_back(arrow);
      float btnRight = btnWin->GetArea().mRight;
      const Rect& ar = arrow->GetArea();
      float arrowW = ar.mRight - ar.mLeft;
      Rect c = arrow->GetArea();
      c.mLeft = btnRight - arrowW;
      c.mRight = btnRight;
      arrow->SetArea(c);
    }

    if (data->GetSubCategory(i)->mButtonImageKey.mInstance != 0) {
      IWindow_s005c_a070* icon = CreateImageWindow(&data->GetSubCategory(i)->mButtonImageKey, Vector2(0.0f, 0.0f), btnWin);
      if (icon) {
        const Rect& ir = icon->GetArea();
        float h = ir.mBottom - ir.mTop;
        float scale = mButtonHeight / h;
        icon->SetSize((ir.mRight - ir.mLeft) * scale, h * scale);
        icon->SetFlag(2, false);
        icon->SetFlag(0x10, true);
      }
    }
  }
}
