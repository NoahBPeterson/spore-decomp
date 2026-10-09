// Slice s005c4500 -- SP::cSPPaletteCategoryUI methods (Spore UI)
// Flags for this region: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// Virtual-call helpers: call slot byte offset `off` of the object's vtable (thiscall).
typedef int(__thiscall* VF0)(void*);
typedef int(__thiscall* VF1)(void*, int);
typedef int(__thiscall* VF2)(void*, int, int);
#define VSLOT(o, off) ((*(void***)(o))[(off) / 4])
static inline int vc0(void* o, int off) { return ((VF0)VSLOT(o, off))(o); }
static inline int vc1(void* o, int off, int a) { return ((VF1)VSLOT(o, off))(o, a); }
static inline int vc2(void* o, int off, int a, int b) { return ((VF2)VSLOT(o, off))(o, a, b); }

// Assign null to an AutoRefCount field and release the old object through vtable slot `off`.
static inline void ResetRef(void** field, int off) {
  void* p = *field;
  if (p) {
    *field = 0;
    vc0(p, off);
  }
}

void* operator new(unsigned int, const char*, int, int, int, int);   // 0x00f473a0
void operator delete(void* p);   // 0x00f47380
inline void* operator new(unsigned int, void* p) { return p; }

struct Rect4 {
  float x1, y1, x2, y2;
};

struct Vec2 {
  float x, y;
};

// EA fixed-capacity wide string used for the tooltip text (begin, end, capacity ends at an inline buffer).
extern wchar_t g_EmptyString[2];  // 0x1667bac
struct TipString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  TipString() : mpBegin(g_EmptyString), mpEnd(g_EmptyString), mpCapacity(g_EmptyString + 1) {}
  ~TipString() {
    if ((((int)mpCapacity - (int)mpBegin) & ~1) > 2 && mpBegin)
      delete[] mpBegin;
  }
  void append(const wchar_t* s);  // lib_eatext basic_string::append (0x5c3d90)
};

struct cSPUILayout {
  char pad[0x18];
  cSPUILayout();  // 0x810000
  ~cSPUILayout();  // 0x811fe0
  bool Init(const uint32_t* key, int a, uint32_t b);  // 0x8120d0
  void SetParentWin(void* win, int a, uint32_t b);  // 0x8121b0
  void* FindWindowByID(uint32_t id, int recursive);  // 0x8105b0
  void Shutdown(int a);  // 0x811ad0
};

struct cString {
  const wchar_t* GetText();  // 0x6b55c0
};

// One expansion pack record from the pack manager (only the fields used here).
struct PackInfo {
  int id;  // +0
  int pad4;
  uint32_t layoutInstance;  // +8
  char iconKey[0xc];  // +0xc image key (first word non-zero when present)
  char iconKey2[0xc];  // +0x18 second image key
  cString name;  // +0x24
};

struct PackVec {
  PackInfo** mpBegin;
  PackInfo** mpEnd;
};

struct cSPUIStdDrawable {
  void SetImageIcon(int a, void* image);  // 0x831760
};

struct cSPUITooltipWinProc {
  cSPUITooltipWinProc(const wchar_t* name, uint32_t id, const wchar_t* text, const Vec2* offset, int a, const void* b,
                      int c);  // 0x835e30
};

struct ImageRef {
  void* mpObject;
  void** AsPPType() { return &mpObject; }  // 0xa16f40
};

namespace SPUIHelpers {
bool __cdecl CreateImageFromResource(const void* key, void** image, int a, int b, int c);  // 0x806230
void __cdecl SetWindowAreaToParent(void* win);  // 0x806bf0
}  // namespace SPUIHelpers

void* __cdecl TooltipAlloc(unsigned int size, int align, const char* name, void* heap);  // 0x9512d0
void* __cdecl TooltipHeap();  // 0x9512c0

struct AppProps {
  char pad[0x118];
  int mFlag118;
};
struct AppPropsHolder {
  char pad[0x3c];
  AppProps* mpProps;
};
extern AppPropsHolder* g_AppProps;  // 0x15fd918
extern float g_PackPaneGap;  // 0x1486110 (5.0f)
extern float g_TooltipOffsetY;  // 0x1473c70 (10.0f)
extern const char g_TooltipFlag[];  // 0x13f7f24

struct SwatchHelper {
  void Release();  // 0x5f0a60
};
SwatchHelper* __stdcall SwatchOwner(void* swatch);  // 0x401020

namespace EA {
namespace Messaging {
void __cdecl RemoveHandler(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e);  // 0x571db0
}
}  // namespace EA

namespace SP {

struct PaintLikeVec {
  void** mpBegin;
  void** mpEnd;
  void Erase(void** first, void** last);  // FUN_005c41b0 (vector erase, this = the vector at +0xe8)
};
class cSPSubCategoryUI {
 public:
  void Shutdown();  // FUN_005ca7b0
};

class cSPPalettePageUI {
 public:
  void Shutdown();  // 0x5c8cc0
  void Detach();  // 0x5c8cc0
  void SetSwatchFlag(int flag);  // 0x5c8bf0
  cSPPalettePageUI();  // 0x5c9010
  void Init(void* page, void* win, int a2, int index, bool isSubCategory);  // 0x5c9230
  static void* operator new(unsigned int sz, const char* n, int a, int b, int c, int d) {
    return ::operator new(sz, n, a, b, c, d);
  }
};

class cSPPalettePage {
 public:
  char pad[0x5c];
  uint32_t mPaintId;  // +0x5c
};

class cSPPaletteCategory {
 public:
  char pad[0xc];
  cSPPalettePage** mPagesBegin;  // +0xc
  cSPPalettePage** mPagesEnd;  // +0x10
  char pad14[0x6c - 0x14];
  uint32_t mCategoryId;  // +0x6c
  char pad70[0x8c - 0x70];
  bool mIsSubCategory;  // +0x8c
  cSPPalettePage* GetPage(int i);  // 0x5c1ce0
  int CountFor(int packId);  // 0x5c1d10
};

class cSPEditorColorPicker {
 public:
  void Clear();  // 0x5a6390
};
class cSPEditorPageControls {
 public:
  void Shutdown();  // 0x5c0990
};

// An element of the palette page-UI vector: a counted pointer plus three flag bytes (8 bytes).
struct PaletteRef {
  cSPPalettePageUI* p;
  bool a;
  bool b;
  bool c;
};

struct PaletteVec {
  PaletteRef* mpBegin;
  PaletteRef* mpEnd;
  PaletteRef* mpCapacity;
  void erase(PaletteRef* first, PaletteRef* last);  // FUN_005c4330
  void DoPushBack(PaletteRef* where, PaletteRef* value);  // FUN_005c4390 (grow + insert)
};

PaletteRef* __cdecl MoveRange(PaletteRef* last, PaletteRef* end, PaletteRef* first);  // FUN_005c3610

// vector<AutoRefCount<IWinButton>> (+0x74) push_back helper
struct ButtonVec {
  void push_back(void** value);  // FUN_005c42f0
};

class cSPPaletteCategoryUI {
 public:
  char pad0[0x10];
  cSPUILayout* mLayout;  // +0x10
  cSPUILayout* mExpansionPackLayout;  // +0x14
  void* mWinCategory;  // +0x18
  void* mWinPageButtons;  // +0x1c
  void* mWinEPUIHolder;  // +0x20
  void* pad24;
  void* mWinPalettePage;  // +0x28
  void* pad2c;
  cSPEditorColorPicker* mColorPicker1;  // +0x30
  cSPEditorColorPicker* mColorPicker2;  // +0x34
  char pad38[0x68 - 0x38];
  void* mPreviewSwatch;  // +0x68
  cSPPaletteCategory* mData;  // +0x6c
  cSPEditorPageControls* mPageControls;  // +0x70
  ButtonVec mPackButtons;  // +0x74
  char pad78[0x88 - 0x78];
  PaletteVec mPalettes;  // +0x88
  char pad94[0x9c - 0x94];
  void* mSubCategoryUI;  // +0x9c
  int mUnkA0;  // +0xa0
  char pada4[0xac - 0xa4];
  uint32_t mCurrentPackId;  // +0xac
  int mExpansionPacksPerPage;  // +0xb0
  uint32_t mMsgIds;  // +0xb4
  uint32_t mMsgCount;  // +0xb8
  uint32_t mMsgPriority;  // +0xbc
  uint32_t mMsgC0;  // +0xc0
  uint32_t mMsgC4;  // +0xc4
  char padc8[0xe8 - 0xc8];
  void** mPaintLikeBegin;  // +0xe8
  void** mPaintLikeEnd;  // +0xec

  int GetPageCount();  // 0x5c2aa0
  bool IsPackVisible(int index);  // 0x5c2bc0
  void SetButtonPositions();  // 0x5c2660
  void SetWindowPositions();  // 0x5c3000
  void ShowPage(uint32_t paintId);  // 0x5c3cb0

  void PopulateExpansionPackPane(cSPPaletteCategory* unused);
  void ClearPalettes();
  void Shutdown();
  bool SelectPalette(int index);
  void SetCategory(cSPPaletteCategory* cat, int a2);
};

struct PackMgr {
  PackVec* GetPacks();  // FUN_00572590
};
PackMgr* __cdecl GetPackManager();  // FUN_0067dea0

// @ 0x005c4df0
void cSPPaletteCategoryUI::ClearPalettes() {
  PaletteVec& v = mPalettes;
  int count = (int)(v.mpEnd - v.mpBegin);
  for (int i = 0; i < count; i++)
    v.mpBegin[i].p->Detach();
  v.erase(v.mpBegin, v.mpEnd);
  mUnkA0 = 0;
}


static inline void AssignLayout(cSPUILayout** field, cSPUILayout* nv) {
  cSPUILayout* old = *field;
  if (nv != old) {
    if (nv) vc0(nv, 4);
    *field = nv;
    if (old) vc0(old, 8);
  }
}

// Build one expansion-pack button from the layout and hook it into the container window.
static void AddPackButton(cSPPaletteCategoryUI* ui, void* container, PackInfo* p) {
  void* btn = 0;
  {
    cSPUILayout lay;
    uint32_t key[3] = {p->layoutInstance, 0x510a95b, 0x40464100};
    lay.Init(key, 0, 0x5b598fa);
    void* w = lay.FindWindowByID(0x5dffa47, 1);
    if (w) {
      vc0(w, 0);
      btn = w;
    }
  }
  if (vc0(btn, 0x10)) {
    void* parent = (void*)vc0(btn, 0x10);
    vc1(parent, 0xdc, (int)btn);
  }
  vc1(container, 0xd8, (int)btn);
  void* a = btn ? (void*)vc1(btn, 0x0c, 0x8ed27e7a) : 0;
  void* b = (void*)vc0(btn, 0xa8);
  void* c = b ? (void*)vc1(b, 0x0c, 0x53eb526) : 0;
  if (a && c) {
    vc1(btn, 0x54, p->id);
    vc1((void*)vc0(a, 0x10), 0x104, (int)ui + 4);
    TipString str;
    str.append(p->name.GetText());
    cSPUITooltipWinProc* tip = 0;
    void* mem = TooltipAlloc(0x68, 4, "UI/Tooltip", TooltipHeap());
    if (mem) {
      Vec2 off;
      off.x = 0.0f;
      off.y = g_TooltipOffsetY;
      tip = new (mem) cSPUITooltipWinProc(L"Tooltips", 0x3754e6c, str.mpBegin, &off, 1, g_TooltipFlag, 0);
      if (tip) vc0(tip, 0);
    }
    vc1((void*)vc0(a, 0x10), 0x104, (int)tip);
    if (*(int*)p->iconKey) {
      ImageRef img;
      img.mpObject = 0;
      if (SPUIHelpers::CreateImageFromResource(p->iconKey, img.AsPPType(), 0, -1, -1))
        ((cSPUIStdDrawable*)c)->SetImageIcon(0, img.mpObject);
      if (img.mpObject) vc0(img.mpObject, 4);
    }
    if (*(int*)p->iconKey2) {
      ImageRef img;
      img.mpObject = 0;
      if (SPUIHelpers::CreateImageFromResource(p->iconKey2, img.AsPPType(), 0, -1, -1))
        vc2((char*)c + 0xc, 0x14, 0, (int)img.mpObject);
      if (img.mpObject) vc0(img.mpObject, 4);
    }
    vc0(btn, 0);
    void* ref = btn;
    ui->mPackButtons.push_back(&ref);
    if (ref) vc0(ref, 4);
    if (tip) vc0(tip, 4);
  }
  vc0(btn, 4);
}

// @ 0x005c4500
void cSPPaletteCategoryUI::PopulateExpansionPackPane(cSPPaletteCategory*) {
  PackVec* packs = GetPackManager()->GetPacks();
  int n = (int)(packs->mpEnd - packs->mpBegin);
  bool noPacks = false;
  if (g_AppProps->mpProps->mFlag118 != 0 && GetPageCount() < 1) noPacks = true;
  bool any = false;
  for (int i = 0; i < n; i++) {
    PackInfo* p = packs->mpBegin[i];
    if (IsPackVisible(i) && p->id != 1 && mData->CountFor(p->id) > 0) {
      any = !noPacks;
      break;
    }
  }
  if (!any) {
    if (mWinEPUIHolder) {
      if (mWinPalettePage) {
        Rect4 r = *(Rect4*)vc0(mWinPalettePage, 0x38);
        r.y1 = g_PackPaneGap;
        vc1(mWinPalettePage, 0x6c, (int)&r);
      }
      vc2(mWinEPUIHolder, 0x7c, 1, 0);
    }
    ResetRef((void**)&mExpansionPackLayout, 8);
    return;
  }
  if (!mWinEPUIHolder) return;
  if (mWinPalettePage) {
    Rect4 r = *(Rect4*)vc0(mWinPalettePage, 0x38);
    Rect4* hr = (Rect4*)vc0(mWinEPUIHolder, 0x38);
    r.y1 = hr->y2 + g_PackPaneGap;
    vc1(mWinPalettePage, 0x6c, (int)&r);
  }
  vc2(mWinEPUIHolder, 0x7c, 1, 1);
  AssignLayout(&mExpansionPackLayout, new ("Editor", 0, 0, 0, 0) cSPUILayout());
  uint32_t layoutKey[3] = {0x9ec201c3, 0x510a95b, 0x40464100};
  if (mExpansionPackLayout->Init(layoutKey, 1, 0x5b598fa)) {
    mExpansionPackLayout->SetParentWin(mWinEPUIHolder, 1, 0x5b598fa);
    void* w = mExpansionPackLayout->FindWindowByID(0x5d29758, 1);
    if (w) SPUIHelpers::SetWindowAreaToParent(w);
  }
  void* container = mExpansionPackLayout->FindWindowByID(0x5d1ad4a, 1);
  if (!container) return;
  bool filtered = g_AppProps->mpProps->mFlag118 != 0;
  for (int i = 0; i < n; i++) {
    PackInfo* p = packs->mpBegin[i];
    if (filtered && !IsPackVisible(i)) continue;
    if (mData->CountFor(p->id) > 0) AddPackButton(this, container, p);
  }
  SetButtonPositions();
  if (n <= mExpansionPacksPerPage) return;
  void* w1 = mExpansionPackLayout->FindWindowByID(0x5d1ad44, 1);
  void* w2 = mExpansionPackLayout->FindWindowByID(0x5d1ad3f, 1);
  if (w1) vc1(w1, 0x104, (int)this + 4);
  if (w2) vc1(w2, 0x104, (int)this + 4);
}

// @ 0x005c4e40
void cSPPaletteCategoryUI::Shutdown() {
  if (mMsgIds) {
    uint32_t ids = mMsgIds;
    mMsgIds = 0;
    EA::Messaging::RemoveHandler(ids, mMsgCount, mMsgPriority, mMsgC0, mMsgC4);
  }
  if (mColorPicker1) {
    mColorPicker1->Clear();
    cSPEditorColorPicker* p = mColorPicker1;
    if (p) {
      mColorPicker1 = 0;
      vc0(p, 8);
    }
  }
  if (mColorPicker2) {
    mColorPicker2->Clear();
    cSPEditorColorPicker* p = mColorPicker2;
    if (p) {
      mColorPicker2 = 0;
      vc0(p, 8);
    }
  }
  if (mPreviewSwatch) {
    SwatchOwner(mPreviewSwatch)->Release();
    ResetRef(&mPreviewSwatch, 4);
  }
  if (mWinPageButtons) ResetRef(&mWinPageButtons, 4);
  if (mPageControls) {
    mPageControls->Shutdown();
    ResetRef((void**)&mPageControls, 4);
  }
  int nw = (int)(mPaintLikeEnd - mPaintLikeBegin);
  for (int i = 0; i < nw; i++)
    vc0(mPaintLikeBegin[i], 8);
  ((PaintLikeVec*)&mPaintLikeBegin)->Erase(mPaintLikeBegin, mPaintLikeEnd);
  if (mSubCategoryUI) {
    ((cSPSubCategoryUI*)mSubCategoryUI)->Shutdown();
    ResetRef(&mSubCategoryUI, 4);
  }
  if (mLayout) {
    void* w1 = mLayout->FindWindowByID(0x5d1ad44, 1);
    void* w2 = mLayout->FindWindowByID(0x5d1ad3f, 1);
    if (w1) vc1(w1, 0x108, (int)this + 4);
    if (w2) vc1(w2, 0x108, (int)this + 4);
  }
  int np = (int)(mPalettes.mpEnd - mPalettes.mpBegin);
  for (int i = 0; i < np; i++)
    mPalettes.mpBegin[i].p->Shutdown();
  {
    PaletteRef* first = mPalettes.mpBegin;
    PaletteRef* last = mPalettes.mpEnd;
    PaletteRef* dest = MoveRange(last, last, first);
    for (PaletteRef* q = dest; q < mPalettes.mpEnd; q++)
      if (q->p) vc0(q->p, 4);
    mPalettes.mpEnd -= (last - first);
  }
  mUnkA0 = 0;
  if (mExpansionPackLayout) {
    mExpansionPackLayout->Shutdown(1);
    ResetRef((void**)&mExpansionPackLayout, 8);
  }
  if (mLayout) {
    mLayout->Shutdown(1);
    ResetRef((void**)&mLayout, 8);
  }
}

// @ 0x005c50b0
bool cSPPaletteCategoryUI::SelectPalette(int index) {
  PaletteVec& v = mPalettes;
  if ((int)(v.mpEnd - v.mpBegin) == 0) return false;
  if (index == -1) {
    int n = (int)(mData->mPagesEnd - mData->mPagesBegin);
    for (int i = 0; i < n; i++) {
      if (mData->GetPage(i)->mPaintId == mCurrentPackId) {
        index = i;
        break;
      }
    }
  }
  cSPPalettePageUI* page = v.mpBegin[index].p;
  if (page) vc0(page, 0);
  PaletteRef e;
  e.p = page;
  e.a = true;
  e.b = true;
  e.c = true;
  if (v.mpEnd < v.mpCapacity) {
    PaletteRef* dst = v.mpEnd++;
    if (dst) {
      dst->p = page;
      if (page) vc0(page, 0);
      dst->a = true;
      dst->b = true;
      dst->c = true;
    }
  } else {
    v.DoPushBack(v.mpEnd, &e);
  }
  if (page) vc0(page, 4);
  if (mWinPageButtons && (int)(v.mpEnd - v.mpBegin) > 1 && !(vc0(mWinPageButtons, 0x28) & 1)) {
    vc2(mWinPageButtons, 0x7c, 1, 1);
    SetWindowPositions();
  }
  return true;
}

// @ 0x005c51e0
void cSPPaletteCategoryUI::SetCategory(cSPPaletteCategory* cat, int a2) {
  ClearPalettes();
  cSPPaletteCategory* old = mData;
  if (cat != old) {
    if (cat) vc0(cat, 4);
    mData = cat;
    if (old) vc0(old, 8);
  }
  PopulateExpansionPackPane(cat);
  SetWindowPositions();
  int n = (int)(mData->mPagesEnd - mData->mPagesBegin);
  for (int i = 0; i < n; i++) {
    cSPPalettePage* page = mData->GetPage(i);
    cSPPalettePageUI* ui = new ("Editor", 0, 0, 0, 0) cSPPalettePageUI();
    if (ui) vc0(ui, 0);
    void** winp = mWinPalettePage ? &mWinPalettePage : &mWinCategory;
    ui->Init(page, *winp, a2, i, mData->mIsSubCategory);
    cSPPalettePageUI* tmp = ui;
    if (tmp) vc0(tmp, 0);
    PaletteRef e;
    e.p = ui;
    e.a = true;
    e.b = true;
    e.c = false;
    if (mPalettes.mpEnd < mPalettes.mpCapacity) {
      PaletteRef* dst = mPalettes.mpEnd++;
      if (dst) {
        dst->p = ui;
        if (ui) vc0(ui, 0);
        dst->a = true;
        dst->b = true;
        dst->c = false;
      }
    } else {
      mPalettes.DoPushBack(mPalettes.mpEnd, &e);
    }
    if (tmp) vc0(tmp, 4);
    if (i == 0) {
      mPalettes.mpBegin->a = true;
      if (mPalettes.mpBegin->a) {
        mPalettes.mpBegin->p->SetSwatchFlag(1);
        mPalettes.mpBegin->b = true;
      }
    }
    ShowPage(page->mPaintId);
    if (ui) vc0(ui, 4);
  }
  if (mWinPageButtons) {
    int cnt = (int)(mData->mPagesEnd - mData->mPagesBegin);
    vc2(mWinPageButtons, 0x7c, 1, cnt > 1);
  }
}

}  // namespace SP
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
    void operator delete(void*); // 0x00f47380

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
