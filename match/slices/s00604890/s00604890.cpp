// SP::cSPVerbIconRollover (rollover verb-icon layout) and the tail of the editor UI
// verb-icon / settings module.
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int uint32_t;

#define PV(n) virtual void pv##n();

// EA allocator entry points (0x00F473A0 / 0x00F47380)
void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(size_t, void* p) { return p; }

struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* pObject) {
    if (pObject != mpObject) {
      T* const pTemp = mpObject;
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
  AutoRefCount& operator=(const AutoRefCount& x) { return operator=(x.mpObject); }
  T*& AsOutParam() {
    if (mpObject) {
      T* const p = mpObject;
      mpObject = 0;
      p->Release();
    }
    return mpObject;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};

template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  T mRefCount;
};

namespace UTFWin {
class IWinProc {
 public:
  virtual ~IWinProc() {}
  virtual void p0();
  virtual void p1();
};

class IWindow {
 public:
  virtual int AddRef();                  // +0x00 0
  virtual int Release();                 // +0x04 1
  PV(2)                                  // +0x08 2
  virtual void* Cast(uint32_t);          // +0x0c 3
  virtual IWindow* GetParent10();        // +0x10 4
  PV(5) PV(6)                            // +0x14 5, +0x18 6
  virtual uint32_t GetControlID();       // +0x1c 7
  virtual int GetState20();              // +0x20 8
  virtual void SetState24(int v);        // +0x24 9
  virtual int GetFlag28();               // +0x28 10
  PV(11) PV(12) PV(13)                   // +0x2c 11, +0x30 12, +0x34 13
  virtual float* GetRect();               // +0x38 14
  PV(15) PV(16)                          // +0x3c 15, +0x40 16
  virtual void SetState44(uint32_t v);   // +0x44 17
  PV(18) PV(19) PV(20) PV(21)            // +0x48..0x54
  PV(22) PV(23) PV(24) PV(25)            // +0x58..0x64
  PV(26)                                 // +0x68
  virtual void SetArea(float* rect);     // +0x6c 27
  PV(28) PV(29) PV(30)                   // +0x70..0x78
  virtual void SetFlag(int v, uint32_t a);  // +0x7c 31
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41)
  virtual void* GetDrawableA8();         // +0xa8 42
  PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50)
  virtual void FirstChildCC(void** out); // +0xcc 51
  virtual IWindow* NextChildD0(void** out); // +0xd0 52
  PV(53)
  virtual void AddChild(IWindow* w);     // +0xd8 54
  virtual void RemoveChild(IWindow* w);  // +0xdc 55
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc* p);  // +0x104 65
  PV(66) PV(67)
};
}  // namespace UTFWin

namespace COM {
class IUnknown32 {
 public:
  ~IUnknown32() {}
  virtual int AddRef();
  virtual int Release();
  PV(2)
  virtual void* Cast(uint32_t typeID);  // +0xc
};
}  // namespace COM
}  // namespace EA

using EA::AutoRefCount;
using EA::UTFWin::IWinProc;
using EA::UTFWin::IWindow;

class cSPUILayout { public:
  cSPUILayout();  // 0x810000
  bool Init(const ResourceKey* pKey, int, uint32_t);   // 0x8120d0
  void GetObjects();                                   // 0x8100c0
  IWindow* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x8105b0
  void Shutdown(int);                                  // 0x811ad0
  ~cSPUILayout();                                      // 0x811fe0
  char pad[0x18];
};

namespace SP {
class cString {
 public:
  cString();                                                                   // 0x6b5060
  cString(uint32_t instanceID, uint32_t groupID, const wchar_t* defaultText);  // 0x6b5770
  ~cString();                                                                  // 0x6b5240
  const wchar_t* GetText();                                                    // 0x6b55c0
  uint32_t mData[6];                                                           // +0x00, size 0x18
};

class cPropertyList;
// Credit row.  Retail size 0x58; layout taken from the byte-exact s005fe1d0 slice.
class cSPUICredits {
 public:
  cSPUICredits();                                            // 0x5fe470
  ~cSPUICredits();                                           // 0x5fe4b0
  cSPUICredits(const cSPUICredits&);                         // 0x601a70
  cSPUICredits& operator=(const cSPUICredits&);              // 0x601c50
  void LoadNamesFromProp();                                  // 0x5fe340
  void SetPropertyID(uint32_t id);                           // 0x5fe4f0

  EA::AutoRefCount<cPropertyList> mCreditNamesProperties;    // +0x00
  int mNumCreditNames;                                       // +0x04
  void* mCreditNames;                                        // +0x08
  uint32_t mReturnString[4];                                 // +0x0c (eastl::string16)
  uint32_t mScrollSpeed;                                     // +0x1c
  uint32_t mPropertyID;                                      // +0x20
  ResourceKey mBackgroundKey;                                // +0x24
  ResourceKey mMusicKey;                                     // +0x30
  cString mTitle;                                            // +0x3c
  uint32_t mLineSpacing;                                     // +0x50
  uint32_t mFadeTime;                                        // +0x54
};
}  // namespace SP

namespace SPUIHelpers {
void* __stdcall GetLayoutManager(uint32_t id);  // 0x805070
}

class cSPUILayoutManager { public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
  virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
  virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
  virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
  virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
  virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
  virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
  virtual void v48(); virtual void v49(); virtual void v50();
  IWindow* GetWorldMainWindow();  // 0x810620
};

// ---------------------------------------------------------------------------
// Base of the verb-icon rollover. Most methods live outside this slice; only the
// constructor / member helpers this slice calls are declared.
class cSPUIPropertyLayout : public EA::UTFWin::IWinProc, public EA::RefCountVTemplate<int> {
 public:
  cSPUIPropertyLayout();                              // 0x8286d0
  bool Init();                                        // 0x828250
  void Shutdown();                                    // 0x828be0
  void SetLayoutName(const wchar_t* name, uint32_t group);  // 0x827fc0
  void SetCargoKey(uint32_t a, uint32_t b);           // 0x827fa0
  void SetAutoUpdateInterval(float f);                // 0x828010
  void SetRootWinID(uint32_t id);                     // 0xc87bc0
  void SetBaseFlag(uint32_t v);                       // 0x828020

  cSPUILayout mLayout;   // +0x0c
};

class cSPVerbIconRollover : public cSPUIPropertyLayout {
 public:
  cSPVerbIconRollover();
  explicit cSPVerbIconRollover(uint32_t a);
  void Shutdown();
  void SetVisibility(uint32_t windowID, uint32_t arg2);
  bool Init();
  void Layout();

  uint32_t mVec24;       // +0x24 begin
  uint32_t mVec28;       // +0x28 end
  uint32_t mVec2c;       // +0x2c cap
  char pad30[0x58 - 0x30];
  float mF58;            // +0x58
  char pad5c[0x9c - 0x5c];
  uint32_t m9c;          // +0x9c
};

// ---------------------------------------------------------------------------
// @ 0x6051d0
cSPVerbIconRollover::cSPVerbIconRollover() {
  SetLayoutName(L"RolloverVerbIcon", 0x40464100u);
  SetRootWinID(0x6bacc30u);
  SetAutoUpdateInterval(0.1f);
}

// @ 0x605220
cSPVerbIconRollover::cSPVerbIconRollover(uint32_t a) {
  SetCargoKey(a, 0x40464100u);
  SetRootWinID(0x6bacc30u);
  SetAutoUpdateInterval(0.1f);
}

// @ 0x605270
void cSPVerbIconRollover::Shutdown() {
  IWindow* const w = mLayout.FindWindowByID(0x6bacc30u, 1);
  if (w) {
    if (w->GetParent10()) w->GetParent10()->RemoveChild(w);
  }
  cSPUIPropertyLayout::Shutdown();
}

// @ 0x6052c0
void cSPVerbIconRollover::SetVisibility(uint32_t windowID, uint32_t arg2) {
  IWindow* const w = mLayout.FindWindowByID(windowID, 1);
  if (w) w->SetFlag(1, arg2);
}

// @ 0x605340
bool cSPVerbIconRollover::Init() {
  const bool result = cSPUIPropertyLayout::Init();
  if (result) {
    IWindow* const w = mLayout.FindWindowByID(0x6bacc30u, 1);
    if (w) {
      SetBaseFlag(0);
      cSPUILayoutManager* const mgr = (cSPUILayoutManager*)SPUIHelpers::GetLayoutManager(0x5b598f6u);
      mgr->GetWorldMainWindow()->AddChild(w);
    }
  }
  return result;
}

// ---------------------------------------------------------------------------
// @ 0x605830  (iterates a vector of icon pointers and sets their state)
struct cVerbIconOwner {
  char pad0c[0xc];
  IWindow** mpBegin;  // +0x0c
  IWindow** mpEnd;    // +0x10
  void SetStateOnAll(int v);
};

void cVerbIconOwner::SetStateOnAll(int v) {
  const int n = (int)(mpEnd - mpBegin);
  for (int i = 0; i < n; ++i) mpBegin[i]->SetState24(v);
}

// ---------------------------------------------------------------------------
// Shared interfaces used by the three large functions below.

namespace EA { namespace UTFWin {
struct Message {
  IWindow* mpSource;   // +0x00
  uint32_t mFlags;     // +0x04
  uint32_t mType;      // +0x08
  uint32_t mPad0c;     // +0x0c
  uint32_t mData;      // +0x10
};

// Text interface returned by IWindow::Cast(0xf15f4bd).
class IText {
 public:
  virtual int AddRef();                // +0x00
  virtual int Release();               // +0x04
  virtual void v2();                   // +0x08
  virtual void* Cast(uint32_t);        // +0x0c
  virtual void v4();                   // +0x10
  virtual void v5();                   // +0x14
  virtual void v6();                   // +0x18
  virtual void func1Ch(int textType);  // +0x1c
};
}}  // namespace EA::UTFWin

using EA::UTFWin::IText;
using EA::UTFWin::Message;

namespace SP {
class cSettingsTab {
 public:
  virtual void Init(const ResourceKey&, IWinProc*, uint32_t);  // +0x00
  virtual void Shutdown();                                     // +0x04
  virtual bool DoMessageTab(IWindow* pWindow, Message* pMsg);  // +0x08
  virtual void RestoreSettingsFromEntry();                     // +0x0c
  virtual void v4();                                           // +0x10
};
}  // namespace SP

// Out-of-line window -> text cast helper (0x5994b0).
IText* __cdecl CastToText(IWindow* p);

// Drawable interface produced by a control's render plumbing.
class IDrawable {
 public:
  virtual int AddRef();                     // +0x00
  virtual int Release();                    // +0x04
  virtual void v2();                        // +0x08
  virtual void* Cast(uint32_t);             // +0x0c
  virtual void v4();                        // +0x10
  virtual void SetImage(int a, void* img);  // +0x14
  void SetImageIcon(int a, int b);          // 0x831760 (non-virtual)
};

class cSPUITooltipWinProc : public IWinProc {
 public:
  virtual int AddRef();   // +0x00
  virtual int Release();  // +0x04
  // Placement-style construction (0x835e30); returns the object.
  cSPUITooltipWinProc* Construct(const wchar_t* kind, uint32_t id, const wchar_t* text,
                                 float* f2, int a, void* vtable, int b);
};

void* __cdecl FUN_009512c0();                                                          // 0x9512c0
void* __cdecl FUN_009512d0(uint32_t size, int align, const char* name, void* arena);   // 0x9512d0
extern void* gTooltipVtable;                                                           // 0x013fa328

// Control object returned by FUN_00806780; only the slots this slice calls.
class cCreditControl {
 public:
  virtual int AddRef();                    // +0x00
  virtual int Release();                   // +0x04
  virtual void v2();                       // +0x08
  virtual void* Cast(uint32_t);            // +0x0c
  virtual IWindow* GetParent10();          // +0x10
  virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
  virtual void SetState28(int a, int b);   // +0x28
  virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16();
  virtual void SetState44(uint32_t v);     // +0x44
};

void* __cdecl FUN_00806780(void* pDrawable, int a, uint32_t id, float x, float y, void* pParent);
bool __cdecl CreateImageFromResource2(const ResourceKey* pKey, void** ppImage, char a, int b, int c);

// Resource-manager plumbing for the credit property list (0x67dcd0 / slot 0x38).
struct PropEntry12 { uint32_t mPropertyID; uint32_t m4; uint32_t m8; };
struct PropVec { PropEntry12* mpBegin; PropEntry12* mpEnd; PropEntry12* mpCap; };
struct CreditsQuery {
  void* mVtable;        // +0x00
  uint32_t mUnused;     // +0x04
  uint32_t mNameGroup;  // +0x08
  uint32_t mPropSet;    // +0x0c
  uint32_t mTail;       // +0x10
};
extern void* gCreditsQueryVtable;  // 0x013eb898

namespace EA { namespace ResourceMan {
class cResourceManager {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13();
  virtual void GetPropertyEntries(PropVec* pOutVec, CreditsQuery* pQuery, int zero);  // +0x38
};
cResourceManager* GetManager();  // 0x67dcd0
}}  // namespace EA::ResourceMan

using EA::ResourceMan::GetManager;

// Render manager used for the rollover highlight (0x67cad0 / 0x80d710).
class cRenderManager {
 public:
  void SetHighlight(IWindow* pWindow, bool a, bool b);  // 0x80d710
};
cRenderManager* __cdecl RenderManager();  // 0x67cad0

// EASTL-style vector of credit rows (+0x24 in the credits-tab object).
struct CreditsVec {
  SP::cSPUICredits* mpBegin;  // +0x00
  SP::cSPUICredits* mpEnd;    // +0x04
  SP::cSPUICredits* mpCap;    // +0x08
  void Insert(SP::cSPUICredits* pos, const SP::cSPUICredits* val);  // 0x6040b0
};

// ---------------------------------------------------------------------------
// Credits-list UI object.  Retail layout: vtable +0, mWinProc +4, a cSPUILayout
// at +8, the target window id at +0x20 and the row vector at +0x24.
class cCreditsTab_s0060_4890 {
 public:
  void Init(const ResourceKey* pKey, IWinProc* pWinProc, uint32_t winID);  // 0x604890

  char pad00[4];            // +0x00 vtable
  IWinProc* mWinProc;       // +0x04
  cSPUILayout mLayout;      // +0x08
  char pad1c[0x20 - 0x1c];  // +0x1c
  uint32_t mWinID;          // +0x20
  CreditsVec mRows;         // +0x24
  char pad30[0x58 - 0x30];  // +0x30
  float mOffset58;          // +0x58
  char pad5c[0x9c - 0x5c];
  int mLastIndex;           // +0x9c
};

// ---------------------------------------------------------------------------
// @ 0x604890
void cCreditsTab_s0060_4890::Init(const ResourceKey* pKey, IWinProc* pWinProc, uint32_t winID) {
  mWinProc = pWinProc;
  mWinID = winID;
  mLayout.Init(pKey, 0, 0x5b598fau);
  mLayout.GetObjects();
  IWindow* const w = mLayout.FindWindowByID(mWinID, 1);
  if (w) w->AddWinProc(mWinProc);
  mOffset58 = 0.0f;

  // Build one credit row per entry of the ResourceManager's credit property list.
  PropVec entries;
  entries.mpBegin = 0;
  entries.mpEnd = 0;
  entries.mpCap = 0;
  CreditsQuery query;
  query.mVtable = gCreditsQueryVtable;
  query.mUnused = 0xffffffffu;
  query.mNameGroup = 0x9a76ea1au;
  query.mPropSet = 0xb1b104u;
  query.mTail = 0xffffffffu;
  GetManager()->GetPropertyEntries(&entries, &query, 0);

  const int numEntries = (int)(entries.mpEnd - entries.mpBegin);
  for (int i = 0; i < numEntries; ++i) {
    SP::cSPUICredits row;
    row.SetPropertyID(entries.mpBegin[i].mPropertyID);
    // Sorted insert by mScrollSpeed (matches the original's inline fast path).
    SP::cSPUICredits* pos = mRows.mpBegin;
    while (pos != mRows.mpEnd && !(pos->mScrollSpeed > row.mScrollSpeed)) ++pos;
    if (pos == mRows.mpEnd && mRows.mpEnd != mRows.mpCap) {
      new (mRows.mpEnd) SP::cSPUICredits(row);
      ++mRows.mpEnd;
    } else {
      mRows.Insert(pos, &row);
    }
  }

  IWindow* const container = mLayout.FindWindowByID(0x79037d1u, 1);
  const int count = (int)(mRows.mpEnd - mRows.mpBegin);
  int y = 0x14;
  for (int i = 0; i < count; ++i) {
    cSPUILayout sub;
    const ResourceKey subKey(0x98f661c7u, 0x510a95bu, 0x40464100u);
    sub.Init(&subKey, 0, 0x5b598fau);
    IWindow* icon = sub.FindWindowByID(0x5dffa47u, 1);
    IWindow* rowWin = 0;
    if (icon) {
      icon->AddRef();
      IWindow* const parent = icon->GetParent10();
      if (parent) icon->GetParent10()->RemoveChild(icon);
      icon->Cast(0x8ed27e7au);
      rowWin = icon;
    }
    IDrawable* drawable = 0;
    if (rowWin) {
      IDrawable* const holder = (IDrawable*)rowWin->GetDrawableA8();
      if (holder) drawable = (IDrawable*)holder->Cast(0x53eb526u);
    }
    if (drawable) {
      SP::cSPUICredits* const row = mRows.mpBegin + i;
      ResourceKey bgKey = row->mBackgroundKey;
      void* bgImage = 0;
      if (CreateImageFromResource2(&bgKey, &bgImage, 0, -1, -1)) {
        drawable->SetImageIcon(0, 0);
      }
      ResourceKey musicKey = row->mMusicKey;
      void* musicImage = 0;
      if (CreateImageFromResource2(&musicKey, &musicImage, 0, -1, -1)) {
        drawable->SetImage(0, musicImage);
      }
      cCreditControl* const ctl =
          (cCreditControl*)FUN_00806780(drawable, 3, row->mPropertyID, (float)y, 4.0f, container);
      if (ctl) ctl->SetState44(0x7a55323u);

      cSPUITooltipWinProc* tooltip = 0;
      void* const arena = FUN_009512c0();
      void* const mem = FUN_009512d0(0x68, 4, "UI/Tooltip", arena);
      if (mem) {
        float f2[2];
        f2[0] = 0.0f;
        f2[1] = 10.0f;
        tooltip = ((cSPUITooltipWinProc*)mem)
                      ->Construct(L"Tooltips", 0x3754e6cu, row->mTitle.GetText(), f2, 1,
                                  &gTooltipVtable, 0);
        if (tooltip) tooltip->AddRef();
      }
      if (ctl) {
        IWindow* const ctlParent = ctl->GetParent10();
        ctlParent->AddWinProc(tooltip);
        if (i == count - 1) {
          mLastIndex = count - 1;
          ctl->SetState28(4, 1);
        }
      }
      if (tooltip) tooltip->Release();
      if (musicImage) ((IDrawable*)musicImage)->Release();
    }
    sub.Shutdown(1);
    if (rowWin) rowWin->Release();
    y += 0x1e;
  }
}

// ---------------------------------------------------------------------------
// Settings window.  Only the retail members this slice touches are named.
class cTimedObject {
 public:
  void RestartTimer();  // 0x5ff230
  char mPad[0x189];
};

class LimitStopwatch {
 public:
  bool IsTimeUp();    // 0x5ff1c0
  uint32_t mStart;    // +0x00
  uint32_t mEnd;      // +0x04
};

class IConfigManager {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10();
  virtual void SetConfigUInt32(uint32_t id, char value);  // +0x2c
  virtual uint32_t GetConfigUInt32(uint32_t id);          // +0x30
};

class IMessageServer {
 public:
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4();
  virtual void SendMessage(uint32_t id, int a, int b);  // +0x14
};

class cUIHints {
 public:
  void UpdateHints(int a, int b);  // 0x67c350
};

IConfigManager* __cdecl ConfigManager();     // 0x67dd30
IMessageServer* __cdecl MessageServer();     // 0x67dcc0
cUIHints* __cdecl FUN_0067cac0();            // 0x67cac0
bool __cdecl CalloutMessageBox(void* pParent, uint32_t id);  // 0x809db0
int __cdecl FUN_00435e90();                                   // 0x435e90
void __cdecl KillSetiEffects(uint32_t id, int state);        // 0x435ed0

namespace SP {
class cSPUISettings {
 public:
  bool DoMessage(IWindow* pWindow, Message* pMsg);  // 0x604d40
  void SaveAllSettings();                           // 0x604860
  void BeginClose();                                // 0x5ff700
  void CloseWindow();                               // 0x601f00

  char pad00[4];               // +0x00 vtable
  char mCallback[0x10];        // +0x04 IModalWindowCallback sub-object
  cSPUILayout* mpLayout;       // +0x14
  bool mbPausedOnExit;         // +0x18
  char pad19[0x20 - 0x19];     // +0x19
  cTimedObject mTimer;         // +0x20
  bool mbInitialYouTubeLogin;  // +0x1a9
  char pad1aa[0x20c - 0x1aa];
  cSettingsTab** mTabBegin;    // +0x20c
  cSettingsTab** mTabEnd;      // +0x210
  char pad214[0x228 - 0x214];
  LimitStopwatch mLimitStopwatch;  // +0x228
};
}  // namespace SP

// ---------------------------------------------------------------------------
// @ 0x604d40
bool SP::cSPUISettings::DoMessage(IWindow* pWindow, Message* pMsg) {
  const uint32_t type = pMsg->mType;
  if (type == 0x287259f6u || type == 0xaf0b6441u) {
    const uint32_t controlID = pWindow->GetControlID();
    if (controlID != 0xaded51d5u && controlID != 0x8bdd39ecu && controlID != 0x3af239c4u &&
        controlID != 0x9a0474au) {
      KillSetiEffects(0xa03e74b2u, FUN_00435e90());
    }
  }

  // The original walks the tab array with a byte-wide index and an unsigned
  // element-count bound; a wrapped (negative) count still enters the loop.
  const int tabCount = (int)(mTabEnd - mTabBegin);
  if (tabCount != 0) {
    unsigned char i = 0;
    do {
      if (mTabBegin[i]->DoMessageTab(pWindow, pMsg)) return true;
      ++i;
    } while ((unsigned)i < (unsigned)(int)(mTabEnd - mTabBegin));
  }

  if (type == 0x287259f6u) {
    const uint32_t controlID = pMsg->mpSource->GetControlID();
    if (controlID > 0x4ea67b3u) {
      if (controlID == 0x5b591a8u) {
        IWindow* const w = mpLayout->FindWindowByID(0x5b591a8u, 1);
        if (w) {
          IWindow* const cast = (IWindow*)w->Cast(0x8ed27e7au);
          if (cast) {
            const int v = (cast->GetState20() >> 2) & 1;
            if (v == 0) FUN_0067cac0()->UpdateHints(0, 1);
            ConfigManager()->SetConfigUInt32(0x5b5bb5eu, (char)v);
          }
        }
        return true;
      }
      if (controlID == 0x5b591d8u) {
        IWindow* const w = mpLayout->FindWindowByID(0x5b591d8u, 1);
        if (w) {
          IWindow* const cast = (IWindow*)w->Cast(0x8ed27e7au);
          if (cast) {
            const int v = (cast->GetState20() >> 2) & 1;
            ConfigManager()->SetConfigUInt32(0x636ec26u, (char)v);
          }
        }
        return true;
      }
      return false;
    }
    if (controlID == 0x4ea67b3u) {
      IWindow* const w = mpLayout->FindWindowByID(0x4ea67b3u, 1);
      if (w) {
        IWindow* const cast = (IWindow*)w->Cast(0x8ed27e7au);
        if (cast) {
          const int v = (cast->GetState20() >> 2) & 1;
          ConfigManager()->SetConfigUInt32(0x4ea96cbu, (char)v);
          MessageServer()->SendMessage(0x670eccdu, 0, 0);
        }
      }
      return true;
    }
    if (controlID == 0x43b7a18u) {
      const uint32_t setting = ConfigManager()->GetConfigUInt32(0x5de7b4au);
      if ((uint32_t)mbInitialYouTubeLogin != setting) {
        return CalloutMessageBox(mCallback, 0x151d9b4u);
      }
      mbPausedOnExit = true;
      BeginClose();
      return true;
    }
    if (controlID == 0x43c8fd8u) {
      {
        int count = (int)(mTabEnd - mTabBegin);
        unsigned char i = 0;
        if (count != 0) {
          do {
            mTabBegin[i]->RestoreSettingsFromEntry();
            ++i;
          } while ((unsigned)i < (unsigned)(int)(mTabEnd - mTabBegin));
        }
      }
      BeginClose();
      return true;
    }
    return false;
  }

  if (type == 0x18u) {
    pMsg->mpSource->GetControlID();
    IWindow* const listWin = pMsg->mpSource->GetParent10();
    if (!listWin) return false;
    if (listWin->GetControlID() != 0x43de590u) return false;
    mTimer.RestartTimer();
    // Walk the settings-list children: the row whose window is the message
    // source is selected (flag 1), every other row is cleared.
    void* cursor = 0;
    listWin->FirstChildCC(&cursor);
    void* endCursor = 0;
    listWin->NextChildD0(&endCursor);
    for (IWindow* entry = listWin->NextChildD0(&cursor); entry != 0;
         entry = listWin->NextChildD0(&cursor)) {
      if (((IWindow*)entry->Cast(0x8ed27e7au)) == 0) continue;
      const int on = (entry == pMsg->mpSource) ? 1 : 0;
      IWindow* const target = mpLayout->FindWindowByID(entry->GetControlID(), 1);
      if (!target) continue;
      target->SetFlag(1, on);
      target->SetFlag(2, on);
    }
    return false;
  }

  if (type == 0x1u) {
    const uint32_t data = pMsg->mData;
    if (data == 0xdu) {
      mbPausedOnExit = true;
      BeginClose();
      return true;
    }
    if (data == 0x1bu) {
      {
        int count = (int)(mTabEnd - mTabBegin);
        unsigned char i = 0;
        if (count != 0) {
          do {
            mTabBegin[i]->RestoreSettingsFromEntry();
            ++i;
          } while ((unsigned)i < (unsigned)(int)(mTabEnd - mTabBegin));
        }
      }
      BeginClose();
      return true;
    }
    return true;
  }

  if (type == 0xcu) {
    if (mLimitStopwatch.mStart == 0 && mLimitStopwatch.mEnd == 0) return false;
    if (!mLimitStopwatch.IsTimeUp()) return false;
    if (mbPausedOnExit) SaveAllSettings();
    CloseWindow();
    return false;
  }
  return false;
}

// ---------------------------------------------------------------------------
// @ 0x6053a0
void cSPVerbIconRollover::Layout() {
  IWindow* const root = mLayout.FindWindowByID(0x6bacc30u, 1);
  if (!root) return;

  float offset = 0.0f;
  IWindow* const header = mLayout.FindWindowByID(0x4d982f8u, 1);
  if (header && (header->GetFlag28() & 1)) {
    IWindow* name = mLayout.FindWindowByID(0x331cc0eu, 1);
    IWindow* const level = mLayout.FindWindowByID(0x4d97708u, 1);
    float nameBottom = 0.0f;
    float maxBottom = 0.0f;
    float levelWidth = 0.0f;
    float nameWidthBefore = 0.0f;
    float nameWidthAfter = 0.0f;
    float levelLeft = 0.0f;
    float* hr = (float*)header->GetRect();
    const float hLeft = hr[0];
    const float hTop = hr[1];
    const float hRight = hr[2];

    if (name && (name->GetFlag28() & 1)) {
      float* r = (float*)name->GetRect();
      nameWidthBefore = r[2] - r[0];
      CastToText(name)->func1Ch(0);
      r = (float*)name->GetRect();
      nameBottom = r[3];
      nameWidthAfter = r[2] - r[0];
    }
    if (level && (level->GetFlag28() & 1)) {
      float* r = (float*)level->GetRect();
      levelWidth = r[2] - r[0];
      CastToText(level)->func1Ch(0);
      r = (float*)level->GetRect();
      const float lTop = r[1];
      maxBottom = r[3];
      const float lWidthAfter = r[2] - r[0];
      levelLeft = r[0];
      float area[4];
      area[0] = levelLeft;
      area[1] = lTop;
      area[2] = r[2];
      area[3] = maxBottom;
      level->SetArea(area);
    }
    if (maxBottom <= nameBottom) maxBottom = nameBottom;
    float hArea[4];
    hArea[0] = hLeft;
    hArea[1] = hTop;
    hArea[2] = hRight;
    hArea[3] = (maxBottom + 5.0f) + hTop;
    header->SetArea(hArea);
    float* const after = (float*)header->GetRect();
    offset = after[3] + 5.0f;

    const float net = ((nameWidthAfter - nameWidthBefore) + levelLeft) - levelWidth;
    if (0.0f < net) {
      float* r = (float*)root->GetRect();
      float rArea[4];
      rArea[0] = r[0];
      rArea[1] = r[1];
      rArea[2] = r[2] + net;
      rArea[3] = r[3];
      root->SetArea(rArea);
    }
  }

  IWindow* const hotkey = mLayout.FindWindowByID(0x4d97710u, 1);
  if (hotkey && (hotkey->GetFlag28() & 1)) {
    float* r = (float*)hotkey->GetRect();
    const float bottom = (r[3] - r[1]) + offset;
    float area[4];
    area[0] = r[0];
    area[1] = offset;
    area[2] = r[2];
    area[3] = bottom;
    hotkey->SetArea(area);
    offset = bottom + 5.0f;
  }

  IWindow* const desc = mLayout.FindWindowByID(0x331cc0fu, 1);
  if (desc && (desc->GetFlag28() & 1)) {
    CastToText(desc)->func1Ch(1);
    float* r = (float*)desc->GetRect();
    const float bottom = (r[3] - r[1]) + offset;
    float area[4];
    area[0] = r[0];
    area[1] = offset;
    area[2] = r[2];
    area[3] = bottom;
    desc->SetArea(area);
    offset = bottom + 5.0f;
  }

  float* r = (float*)root->GetRect();
  float rootArea[4];
  rootArea[0] = r[0];
  rootArea[1] = r[1];
  rootArea[2] = r[2];
  rootArea[3] = r[1] + offset;
  root->SetArea(rootArea);

  if (RenderManager()) RenderManager()->SetHighlight(root, 1, 1);
}
