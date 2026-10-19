// src/game/SPEditors/SPVerbIconRollover.cpp -- migrated from slice(s) s00604890 by tools/migrate/rewrite.py
// Object file: SPEditors/SPVerbIconRollover.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"
#include "cSPUILayoutManager.h"
#include "cSPUIPropertyLayout.h"
#include "cSPVerbIconRollover.h"
#include "SP/cString.h"

// ---- items of slice s00604890 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define PV(n) virtual void pv##n();
struct ResourceKey {
  uint32_t mInstance;  // +0x0
  uint32_t mType;      // +0x4
  uint32_t mGroup;     // +0x8
  ResourceKey() : mInstance(0), mType(0), mGroup(0) {}
  ResourceKey(uint32_t i, uint32_t t, uint32_t g) : mInstance(i), mType(t), mGroup(g) {}
};
namespace EA {
template <typename T>
class RefCountVTemplate_s0060_4890 {
 public:
  RefCountVTemplate_s0060_4890() : mRefCount(0) {}
  virtual ~RefCountVTemplate_s0060_4890() {}
  T mRefCount;
};
}
namespace EA {
namespace UTFWin {
class IWinProc_s0060_4890 {
 public:
  virtual ~IWinProc_s0060_4890() {}
  virtual void p0();
  virtual void p1();
};
}
}
namespace EA {
namespace UTFWin {
class IWindow_s0060_4890 {
 public:
  virtual int AddRef();                  // +0x00 0
  virtual int Release();                 // +0x04 1
  PV(2)                                  // +0x08 2
  virtual void* Cast(uint32_t);          // +0x0c 3
  virtual IWindow_s0060_4890* GetParent10();        // +0x10 4
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
  virtual void AddChild(IWindow_s0060_4890* w);     // +0xd8 54
  virtual void RemoveChild(IWindow_s0060_4890* w);  // +0xdc 55
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63) PV(64)
  virtual void AddWinProc(IWinProc_s0060_4890* p);  // +0x104 65
  PV(66) PV(67)
};
}
}
using EA::UTFWin::IWinProc_s0060_4890;
using EA::UTFWin::IWindow_s0060_4890;
struct cSPUILayout_s0060_4890 {
  cSPUILayout_s0060_4890();  // 0x810000
  bool Init(const ResourceKey* pKey, int, uint32_t);   // 0x8120d0
  void GetObjects();                                   // 0x8100c0
  IWindow_s0060_4890* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x8105b0
  void Shutdown(int);                                  // 0x811ad0
  ~cSPUILayout_s0060_4890();                                      // 0x811fe0
  char pad[0x18];
};
namespace SPUIHelpers {
void* __stdcall GetLayoutManager(uint32_t id);  // 0x805070
}
struct cSPUILayoutManager_s0060_4890 {
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
  IWindow_s0060_4890* GetWorldMainWindow();  // 0x810620
};
class cSPUIPropertyLayout_s0060_4890 : public EA::UTFWin::IWinProc_s0060_4890, public EA::RefCountVTemplate_s0060_4890<int> {
 public:
  cSPUIPropertyLayout_s0060_4890();                              // 0x8286d0
  bool Init();                                        // 0x828250
  void Shutdown();                                    // 0x828be0
  void SetLayoutName(const wchar_t* name, uint32_t group);  // 0x827fc0
  void SetCargoKey(uint32_t a, uint32_t b);           // 0x827fa0
  void SetAutoUpdateInterval(float f);                // 0x828010
  void SetRootWinID(uint32_t id);                     // 0xc87bc0
  void SetBaseFlag(uint32_t v);                       // 0x828020

  cSPUILayout_s0060_4890 mLayout;   // +0x0c
};
class cSPVerbIconRollover_s0060_4890 : public cSPUIPropertyLayout_s0060_4890 {
 public:
  cSPVerbIconRollover_s0060_4890();
  explicit cSPVerbIconRollover_s0060_4890(uint32_t a);
  void Shutdown();  // 0x00605270 (cSPVerbIconRollover::Shutdown)
  void SetVisibility(uint32_t windowID, uint32_t arg2);  // 0x006052c0 (cSPVerbIconRollover::SetVisibility)
  bool Init();  // 0x00605340 (cSPVerbIconRollover::Init)

  uint32_t mVec24;       // +0x24 begin
  uint32_t mVec28;       // +0x28 end
  uint32_t mVec2c;       // +0x2c cap
  char pad30[0x58 - 0x30];
  float mF58;            // +0x58
  char pad5c[0x9c - 0x5c];
  uint32_t m9c;          // +0x9c
};
// ---- items of slice s00604890 end

// @ 0x006051d0
cSPVerbIconRollover_s0060_4890::cSPVerbIconRollover_s0060_4890()
{
  SetLayoutName(L"RolloverVerbIcon", 0x40464100u);
  SetRootWinID(0x6bacc30u);
  SetAutoUpdateInterval(0.1f);
}

// @ 0x00605220
cSPVerbIconRollover_s0060_4890::cSPVerbIconRollover_s0060_4890(uint32_t a)
{
  SetCargoKey(a, 0x40464100u);
  SetRootWinID(0x6bacc30u);
  SetAutoUpdateInterval(0.1f);
}

// @ 0x00605270
void cSPVerbIconRollover_s0060_4890::Shutdown()
{
  IWindow_s0060_4890* const w = mLayout.FindWindowByID(0x6bacc30u, 1);
  if (w) {
    if (w->GetParent10()) w->GetParent10()->RemoveChild(w);
  }
  cSPUIPropertyLayout_s0060_4890::Shutdown();
}

// @ 0x006052c0
void cSPVerbIconRollover_s0060_4890::SetVisibility(uint32_t windowID, uint32_t arg2)
{
  IWindow_s0060_4890* const w = mLayout.FindWindowByID(windowID, 1);
  if (w) w->SetFlag(1, arg2);
}

// @ 0x00605340
bool cSPVerbIconRollover_s0060_4890::Init()
{
  const bool result = cSPUIPropertyLayout_s0060_4890::Init();
  if (result) {
    IWindow_s0060_4890* const w = mLayout.FindWindowByID(0x6bacc30u, 1);
    if (w) {
      SetBaseFlag(0);
      cSPUILayoutManager_s0060_4890* const mgr = (cSPUILayoutManager_s0060_4890*)SPUIHelpers::GetLayoutManager(0x5b598f6u);
      mgr->GetWorldMainWindow()->AddChild(w);
    }
  }
  return result;
}

// @ 0x006053a0
void SP_cSPVerbIconRollover_Layout(int self)
{
  cSPUILayout_s0060_4890* const layout = (cSPUILayout_s0060_4890*)(self + 0xc);
  IWindow_s0060_4890* const root = layout->FindWindowByID(0x6bacc30u, 1);
  if (!root) return;
  IWindow_s0060_4890* const icon = layout->FindWindowByID(0x4d982f8u, 1);
  if (!icon || !(icon->GetFlag28() & 1)) return;
  IWindow_s0060_4890* const w3 = layout->FindWindowByID(0x331cc0eu, 1);
  IWindow_s0060_4890* const w4 = layout->FindWindowByID(0x4d97708u, 1);
  float area[4];
  float* r = (float*)icon->GetRect();
  area[0] = r[0]; area[1] = r[1]; area[2] = r[2]; area[3] = r[3];
  (void)w3;
  (void)w4;
  icon->SetArea(area);
}
