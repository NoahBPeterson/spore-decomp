// slice s00d49b60 -- UI screen wiring: find existing windows, create three
// sub-layouts and attach them to the per-index window family.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_0147aeb8[];

// ---------------------------------------------------------------------------
// stub types (offsets read from the retail disassembly)
// ---------------------------------------------------------------------------

#define CAT2_s00d49b60(a, b) a##b
#define CAT_s00d49b60(a, b) CAT2_s00d49b60(a, b)
#define PVN_s00d49b60(p) virtual void CAT_s00d49b60(pad_, p)();
#define PV4N_s00d49b60(a) \
  PVN_s00d49b60(a##0) PVN_s00d49b60(a##1) PVN_s00d49b60(a##2) PVN_s00d49b60(a##3)

// three-word descriptor handed to cSPUILayout::Init
struct cLayoutInitData_s00d49b60 {
  cLayoutInitData_s00d49b60(unsigned int a, unsigned int b, unsigned int c)
      : mnA(a), mnB(b), mnC(c) {}
  unsigned int mnA;  // +0x00
  unsigned int mnB;  // +0x04
  unsigned int mnC;  // +0x08
};

// Ref-counted UI layout: AddRef at vtable +4, Release at +8, AddWinProc at
// +0x104 (all confirmed by the modeled class in SPUICommScreen.cpp).
class cSPUILayout_s00d49b60 {
 public:
  virtual void v0();     // +0x00
  virtual int AddRef();  // +0x04
  virtual int Release();  // +0x08
  PV4N_s00d49b60(0) PV4N_s00d49b60(1) PV4N_s00d49b60(2)  // slots 3..14
  PV4N_s00d49b60(3) PV4N_s00d49b60(4) PV4N_s00d49b60(5)  // slots 15..26
  PV4N_s00d49b60(6) PV4N_s00d49b60(7) PV4N_s00d49b60(8)  // slots 27..38
  PV4N_s00d49b60(9) PV4N_s00d49b60(a) PV4N_s00d49b60(b)  // slots 39..50
  PV4N_s00d49b60(c) PV4N_s00d49b60(d) PV4N_s00d49b60(e)  // slots 51..62
  PVN_s00d49b60(f0) PVN_s00d49b60(f1)                     // slots 63..64
  virtual void AddWinProc(unsigned int proc);              // +0x104
  char mData[0x14];

  cSPUILayout_s00d49b60* FUN_00810000();  // 0x00810000 (constructor, returns this)
  void Init(const cLayoutInitData_s00d49b60& key, bool visible,
            unsigned int parentID);  // 0x008120d0
  cSPUILayout_s00d49b60* FindWindowByID(unsigned int id, bool recursive);  // 0x008105b0
};

// NOTE: the created layouts are held by raw pointers with an explicit AddRef.
// The three trailing releases are written out by hand in reverse creation
// order. The last release is a tail call (`add esp, 0x30; jmp eax`, duplicated
// epilogue), which cl 15.00.30729.01 only emits when the frame holds no
// address-exposed local: Init therefore takes its key by const reference and
// each call site passes a three-word temporary, not the address of a named
// local (that spelling compiles to call eax plus a single epilogue).

// window-family descriptor read from the global at 0x0169e3ec
struct cUIWindowFamily_s00d49b60 {
  char pad00[0xcc];
  int mnCount;             // +0xcc
  unsigned int mnFirstID;  // +0xd0
  unsigned int mnSecondID; // +0xd4
};

struct cGlobalUI_s00d49b60 {
  cSPUILayout_s00d49b60* FUN_00ef0dc0();  // 0x00ef0dc0 (thiscall)
};

// ---------------------------------------------------------------------------
// externs (callees/globals are masked relocations; the note gives the address)
// ---------------------------------------------------------------------------
void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void* SP_GetCurrentGameMode();                                                    // 0x00b5b800
cSPUILayout_s00d49b60* FUN_00d39000();                                            // 0x00d39000
cSPUILayout_s00d49b60* FUN_00cc8990();                                            // 0x00cc8990
cSPUILayout_s00d49b60* FUN_00d48b50(const void* key);                             // 0x00d48b50
void FUN_00d49950(cSPUILayout_s00d49b60* layout, cSPUILayout_s00d49b60* window);  // 0x00d49950

extern cUIWindowFamily_s00d49b60* g_pUIWindowFamily;  // 0x0169e3ec
extern cGlobalUI_s00d49b60* g_pGlobalUI;              // 0x016c7aa4

// ---------------------------------------------------------------------------
// @ 0x00D49B60
// ---------------------------------------------------------------------------
void FUN_00d49b60(unsigned int nWinProc) {
  cSPUILayout_s00d49b60* root;
  switch ((unsigned int)SP_GetCurrentGameMode()) {
    case 0x01654c01u:
      root = FUN_00d39000();
      break;
    case 0x01654c02u:
      root = FUN_00cc8990();
      break;
    case 0x01654c10u:
      root = g_pGlobalUI->FUN_00ef0dc0();
      break;
    default:
      root = 0;
      break;
  }

  // existing windows of the screen that take the new win-proc directly
  if (cSPUILayout_s00d49b60* w = root->FindWindowByID(0x04c61dd9u, true)) {
    w->AddWinProc(nWinProc);
  }
  if (cSPUILayout_s00d49b60* w = root->FindWindowByID(0x04c61b50u, true)) {
    w->AddWinProc(nWinProc);
  }
  if (cSPUILayout_s00d49b60* w = FUN_00d48b50((const void*)0x07e495e0)) {
    w->AddWinProc(nWinProc);
  }

  // the window family this screen drives
  unsigned int nFirstID = g_pUIWindowFamily->mnFirstID;
  unsigned int nSecondID = g_pUIWindowFamily->mnSecondID;

  void* pMem0 = operator new(0x18, (const char*)g_0147aeb8, 0, 0, 0, 0);
  cSPUILayout_s00d49b60* layout0 =
      pMem0 ? ((cSPUILayout_s00d49b60*)pMem0)->FUN_00810000() : 0;
  if (layout0) layout0->AddRef();
  layout0->Init(cLayoutInitData_s00d49b60(0xa5c3f949u, 0x0510a95bu, 0x40464100u), true,
                0x05b598fau);

  void* pMem1 = operator new(0x18, (const char*)g_0147aeb8, 0, 0, 0, 0);
  cSPUILayout_s00d49b60* layout1 =
      pMem1 ? ((cSPUILayout_s00d49b60*)pMem1)->FUN_00810000() : 0;
  if (layout1) layout1->AddRef();
  layout1->Init(cLayoutInitData_s00d49b60(0xae2cbb58u, 0x0510a95bu, 0x40464100u), true,
                0x05b598fau);

  void* pMem2 = operator new(0x18, (const char*)g_0147aeb8, 0, 0, 0, 0);
  cSPUILayout_s00d49b60* layout2 =
      pMem2 ? ((cSPUILayout_s00d49b60*)pMem2)->FUN_00810000() : 0;
  if (layout2) layout2->AddRef();
  layout2->Init(cLayoutInitData_s00d49b60(0xe7405caau, 0x0510a95bu, 0x40464100u), true,
                0x05b598fau);

  for (int i = 0; i < g_pUIWindowFamily->mnCount; ++i) {
    cSPUILayout_s00d49b60* p0 = root->FindWindowByID(nFirstID + i, true);
    cSPUILayout_s00d49b60* p1 = root->FindWindowByID(nSecondID + i, true);
    cSPUILayout_s00d49b60* p2 = root->FindWindowByID(0x01012030u + i, true);
    cSPUILayout_s00d49b60* p3 = root->FindWindowByID(0x01012040u + i, true);

    if (p0) {
      FUN_00d49950(layout0, p0);
      p0->AddWinProc(nWinProc);
    }
    if (p1) {
      FUN_00d49950(layout1, p1);
      p1->AddWinProc(nWinProc);
    }
    if (p2) {
      FUN_00d49950(layout2, p2);
      p2->AddWinProc(nWinProc);
    }
    if (p3) {
      p3->AddWinProc(nWinProc);
    }
  }

  if (layout2) layout2->Release();
  if (layout1) layout1->Release();
  if (layout0) layout0->Release();
}
