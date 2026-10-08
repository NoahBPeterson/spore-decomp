// Slice s00601fd0 - SP::cGameTab::Init (0x00601fd0, thiscall, ret 0xc) and cTerrainUI::LoadScriptFromGrid (stub).
//
// cGameTab::Init(layoutID, winProc, tabID): inlined cSettingsTab::Init, then reads the game options from the
// ConfigManager (tutorials 0x4ea96cb, show hints 0x5b5bb5e, movie res 0x636ec26, photo res 0x473b8cc, game
// difficulty 0x473b8cb), checks the matching buttons, fixes up the fullscreen-dependent controls, and fills the
// description caption from either a localized string or a string built from the save-area path (path with the
// last two components removed).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

#define PV(n) virtual void pv##n();

namespace EA {
namespace UTFWin {
class IWinProc;
class IWindow;
struct Rect { float x1, y1, x2, y2; };
class IWindow {
 public:
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);                  // +0xc
  PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual const Rect* GetArea();                        // +0x34
  PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24)
  virtual void SetLocation(float x, float y);           // +0x64
  PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);           // +0x7c
  virtual void SetCaption(const wchar_t* caption);      // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39) PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46)
  PV(47) PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55) PV(56) PV(57) PV(58) PV(59) PV(60) PV(61)
  PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* proc);              // +0x104
};
// Control interfaces reached through IWindow::Cast.
class IButton {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetButtonStateFlag(int flag, bool value);  // +0x28
};
class IColorable {
 public:
  PV(0) PV(1) PV(2) PV(3)
  virtual IWindow* ToWindow();                          // +0x10
  PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual void SetColor(uint32_t color);                // +0x28
};
}  // namespace UTFWin
}  // namespace EA

using EA::UTFWin::IWindow;
using EA::UTFWin::IWinProc;
using EA::UTFWin::IButton;
using EA::UTFWin::IColorable;

class cSPUILayout {
 public:
  PV(0)
  virtual int AddRef();
  virtual int Release();
  IWindow* FindWindowByID(uint32_t id, bool recursive);   // 0x008105b0
  bool Init(uint32_t instanceID, uint32_t typeID, uint32_t groupID);   // 0x008120d0
  void GetObjects();                                      // 0x008100c0
  char pad[0x18 - 4];
};

// eastl::basic_string<wchar_t> (three pointers, empty allocator)
struct WString {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  WString() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  void RangeInitialize(const wchar_t* pBegin);            // 0x00579a90
  void erase(uint32_t position, uint32_t n);              // 0x004228e0
};
// reverse range search used by basic_string::rfind
const wchar_t* FindEnd(const wchar_t* a, const wchar_t* b, const wchar_t* c, const wchar_t* d);   // 0x005728f0
void operator_delete_array_00f47380(void* p);             // operator delete[]

namespace SP {
class cString {
 public:
  cString();                                                            // 0x006b5060
  ~cString();                                                           // 0x006b5240
  bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);   // 0x006b54b0
  const wchar_t* GetText();                                             // 0x006b55c0
 private:
  uint32_t mData[6];
};

class IConfigManager {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10)
  virtual void SetValue(uint32_t id, int value);  // +0x2c
  virtual int GetValue(uint32_t id);              // +0x30
};
IConfigManager* ConfigManager();                  // 0x0067dd30

class ICanvas {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14)
  PV(15) PV(16) PV(17) PV(18) PV(19) PV(20)
  virtual bool IsFullscreen();  // +0x54
};
ICanvas* Canvas();                                // 0x0067dcf0

class ISaveArea {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9)
  virtual const wchar_t* GetPath();               // +0x28
};
ISaveArea* GetSaveArea(uint32_t id);              // 0x006b1f90

class IPathTarget {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  virtual void SetPath(const wchar_t* path, int flags);   // +0x34
};
class IPathProvider {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
  virtual IPathTarget* GetTarget();               // +0x20
};
IPathProvider* FUN_0067de40();                    // 0x0067de40

struct cPropertyListData { char pad[0x118]; int mField118; };
class cPropertyList {
 public:
  bool GetDescription(uint32_t id);               // 0x006a25a0
  char pad[0x3c];
  cPropertyListData* mpData;                      // +0x3c
};
extern cPropertyList* gAppProperties;             // 0x015fd918

class cSettingsTab {
 public:
  virtual ~cSettingsTab();
  virtual void Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID);
  IWinProc* mWinProc;     // +0x4
  cSPUILayout mLayout;    // +0x8
  uint32_t mTabID;        // +0x20
};

class cGameTab : public cSettingsTab {
 public:
  void Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID);
  bool mInitialTutorialsSettings;   // +0x24
  bool mInitialShowHints;           // +0x25
  bool mInitialMovieRes;            // +0x26
  bool mInitialPhotoRes;            // +0x27
  bool mInitialGameDifficulty;      // +0x28
};
}  // namespace SP

using namespace SP;

static __forceinline IButton* ButtonOf(IWindow* w) { return w ? (IButton*)w->Cast(0x8ed27e7a) : 0; }

// index of the last occurrence of the one-character string lit in s, or -1 (eastl::basic_string::rfind)
static __forceinline uint32_t RFind(WString& s, const wchar_t* lit) {
  const wchar_t* pEnd = lit;
  while (*pEnd) ++pEnd;
  uint32_t length = (uint32_t)(s.mpEnd - s.mpBegin);
  if (length) {
    const wchar_t* pSearchEnd = s.mpBegin + (length - 1) + 1;
    const wchar_t* r = FindEnd(pSearchEnd, s.mpBegin, lit, pEnd);
    if (r != s.mpBegin) return (uint32_t)(r - s.mpBegin) - 1;
  }
  return (uint32_t)-1;
}

// @ 0x00601fd0
void cGameTab::Init(uint32_t layoutID, IWinProc* winProc, uint32_t tabID) {
  mTabID = tabID;
  mWinProc = winProc;
  mLayout.Init(layoutID, 0, 0x5b598fa);
  mLayout.GetObjects();
  mLayout.FindWindowByID(mTabID, true)->AddWinProc(mWinProc);

  bool tutorials = ConfigManager()->GetValue(0x4ea96cb) != 0;
  mInitialTutorialsSettings = tutorials;
  mInitialShowHints = ConfigManager()->GetValue(0x5b5bb5e) != 0;
  mInitialMovieRes = ConfigManager()->GetValue(0x636ec26) != 0;

  if (IButton* b = ButtonOf(mLayout.FindWindowByID(0x4ea67b3, true)))
    b->SetButtonStateFlag(4, tutorials);
  if (IButton* b = ButtonOf(mLayout.FindWindowByID(0x5b591a8, true)))
    b->SetButtonStateFlag(4, mInitialShowHints);
  IWindow* movie = mLayout.FindWindowByID(0x5b591d8, true);
  if (movie) {
    if (IButton* b = ButtonOf(movie)) {
      b->SetButtonStateFlag(4, mInitialMovieRes);
      if (!Canvas()->IsFullscreen()) {
        movie->SetFlag(2, false);
        movie->SetFlag(0x10, true);
      }
      IWindow* label = mLayout.FindWindowByID(0x669ea05, true);
      if (label) {
        IColorable* c = (IColorable*)label->Cast(0xf15f4bd);
        if (c) c->SetColor(Canvas()->IsFullscreen() ? 0xd6ffffff : 0x99999999);
      }
    }
  }

  if (gAppProperties->mpData->mField118 != 0) {
    IWindow* w = mLayout.FindWindowByID(0x5b591d8, true);
    if (w) w->SetFlag(2, false);
    w = mLayout.FindWindowByID(0x4ea67b3, true);
    if (w) w->SetFlag(2, false);
    w = mLayout.FindWindowByID(0x5b75578, true);
    if (w) w->SetFlag(1, false);
    w = mLayout.FindWindowByID(0x5b757b0, true);
    if (w) {
      const EA::UTFWin::Rect* area = w->GetArea();
      w->SetLocation(area->x1, area->y1 - 190.0f);
    }
    w = mLayout.FindWindowByID(0x5b75950, true);
    if (w) w->SetFlag(1, false);
    w = mLayout.FindWindowByID(0x5b75b28, true);
    if (w) w->SetFlag(1, true);
  }

  uint8_t photoRes = (uint8_t)ConfigManager()->GetValue(0x473b8cc);
  mInitialPhotoRes = photoRes;
  mLayout.FindWindowByID(0x462c820, true);
  ButtonOf(mLayout.FindWindowByID(0x462c820, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cb58, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cb78, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cba0, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cbb0, true))->SetButtonStateFlag(4, false);
  ButtonOf(mLayout.FindWindowByID(0x462cbb8, true))->SetButtonStateFlag(4, false);

  uint32_t photoID;
  switch (photoRes) {
    case 1: photoID = 0x462c820; break;
    case 2: photoID = 0x462cb58; break;
    case 3: photoID = 0x462cb78; break;
    default:
      photoID = 0x462c820;
      ConfigManager()->SetValue(0x473b8cc, 1);
      break;
  }
  if (IButton* b = ButtonOf(mLayout.FindWindowByID(photoID, true)))
    b->SetButtonStateFlag(4, true);

  uint8_t difficulty = (uint8_t)ConfigManager()->GetValue(0x473b8cb);
  mInitialGameDifficulty = difficulty;
  uint32_t diffID;
  switch (difficulty) {
    case 1: diffID = 0x462cba0; break;
    case 2: diffID = 0x462cbb0; break;
    case 3: diffID = 0x462cbb8; break;
    default:
      diffID = 0x462cba0;
      ConfigManager()->SetValue(0x473b8cb, 1);
      break;
  }
  if (IButton* b = ButtonOf(mLayout.FindWindowByID(diffID, true)))
    b->SetButtonStateFlag(4, true);

  cString text;
  if (gAppProperties->GetDescription(0x61b67b6)) {
    text.Load(0xad7b2086, 0x6318d68, 0);
  } else {
    WString path;
    path.RangeInitialize(GetSaveArea(0x11ac197)->GetPath());
    for (int i = 0; i < 2; ++i) {
      uint32_t length = (uint32_t)(path.mpEnd - path.mpBegin);
      uint32_t pos = RFind(path, L"\\");
      if (pos == (uint32_t)-1) pos = RFind(path, L"/");
      if (pos != (uint32_t)-1) {
        uint32_t count = length - pos;
        if (i) {
          --count;
          ++pos;
        }
        path.erase(pos, count);
      }
    }
    FUN_0067de40()->GetTarget()->SetPath(path.mpBegin, 0);
    text.Load(0xad7b2086, 0x631825f, 0);
    if (((((uint32_t)path.mpCapacity) - ((uint32_t)path.mpBegin)) & ~1u) > 2 && path.mpBegin)
      operator_delete_array_00f47380(path.mpBegin);
  }

  IWindow* w = mLayout.FindWindowByID(0x6317e08, true);
  if (w) {
    IColorable* c = (IColorable*)w->Cast(0xf15f4bd);
    if (c) c->ToWindow()->SetCaption(text.GetText());
  }
}

// @ 0x006026f0
bool cTerrainUILoadScriptFromGrid()
{
  return false;
}
