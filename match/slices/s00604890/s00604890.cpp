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
  PV(8)                                  // +0x20 8
  virtual void SetState24(int v);        // +0x24 9
  virtual int GetFlag28();               // +0x28 10
  PV(11) PV(12) PV(13)                   // +0x2c 11, +0x30 12, +0x34 13
  virtual void* GetRect();               // +0x38 14
  PV(15) PV(16)                          // +0x3c 15, +0x40 16
  PV(17)                                 // +0x44 17
  PV(18) PV(19) PV(20) PV(21)            // +0x48..0x54
  PV(22) PV(23) PV(24) PV(25)            // +0x58..0x64
  PV(26)                                 // +0x68
  virtual void SetArea(float* rect);     // +0x6c 27
  PV(28) PV(29) PV(30)                   // +0x70..0x78
  virtual void SetFlag(int v, uint32_t a);  // +0x7c 31
  PV(32) PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53)
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

struct cSPUILayout {
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
  cString(uint32_t instanceID, uint32_t groupID, const wchar_t* defaultText);  // 0x6b5770
  ~cString();                                                                  // 0x6b5240
  const wchar_t* GetText();                                                    // 0x6b55c0
  uint32_t pad[5];
};
}  // namespace SP

namespace SPUIHelpers {
void* __stdcall GetLayoutManager(uint32_t id);  // 0x805070
}

struct cSPUILayoutManager {
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
// Outline ports of the three large functions of this slice. They are listed in
// partial.txt; matching them byte-for-byte is left for a dedicated pass.

// @ 0x604890  (cSPEditorVerbIcon::Shutdown candidate)
void FUN_00604890(int self, uint32_t resKey, uint32_t arg3, uint32_t winId) {
  cSPUILayout* const layout = (cSPUILayout*)(self + 8);
  *(uint32_t*)(self + 4) = arg3;
  *(uint32_t*)(self + 0x20) = winId;
  layout->Init((const ResourceKey*)resKey, 0, 0x5b598fau);
  layout->GetObjects();
  IWindow* const w = layout->FindWindowByID(winId, 1);
  if (w) w->AddWinProc((IWinProc*)(*(uint32_t*)(self + 4)));
  *(uint32_t*)(self + 0x58) = 0;
  // The original walks the per-slot vector at +0x24 (element size 0x58), builds a
  // credits property list, then creates one icon/tooltip per element and finally
  // tears the sub-layout down.
  const int count = (*(int*)(self + 0x28) - *(int*)(self + 0x24)) / 0x58;
  for (int i = 0; i < count; ++i) {
    cSPUILayout sub;
    sub.Init((const ResourceKey*)0, 0, 0x5b598fau);
    IWindow* const icon = sub.FindWindowByID(0x5dffa47u, 1);
    (void)icon;
    sub.Shutdown(1);
  }
  layout->Shutdown(1);
}

// @ 0x604d40  (SP::cSPUISettings::DoMessage candidate)
uint32_t SP_cSPUISettings_DoMessage(int* self, int* param_2, int* param_3) {
  // Only the message-dispatch skeleton is reproduced here.
  if (param_3 && ((param_3[2] == 0x287259f6) || (param_3[2] == (int)0xaf0b6441u))) {
    (void)self;
    return 1;
  }
  return 0;
}

// @ 0x6053a0  (cSPVerbIconRollover::Layout candidate)
void SP_cSPVerbIconRollover_Layout(int self) {
  cSPUILayout* const layout = (cSPUILayout*)(self + 0xc);
  IWindow* const root = layout->FindWindowByID(0x6bacc30u, 1);
  if (!root) return;
  IWindow* const icon = layout->FindWindowByID(0x4d982f8u, 1);
  if (!icon || !(icon->GetFlag28() & 1)) return;
  IWindow* const w3 = layout->FindWindowByID(0x331cc0eu, 1);
  IWindow* const w4 = layout->FindWindowByID(0x4d97708u, 1);
  float area[4];
  float* r = (float*)icon->GetRect();
  area[0] = r[0]; area[1] = r[1]; area[2] = r[2]; area[3] = r[3];
  (void)w3;
  (void)w4;
  icon->SetArea(area);
}
