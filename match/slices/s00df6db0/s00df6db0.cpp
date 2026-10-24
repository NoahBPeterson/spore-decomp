// Slice s00df6db0: cGameUIData::SetUIState (UI layout state switch for the Space-game planet/creature UI).
#include "types.h"

typedef unsigned int u32;

struct cVec3 { float x, y, z; };
struct cRect4 {
  float x, y, w, h;
  cRect4() {}
  cRect4(const cRect4& r) : x(r.x), y(r.y), w(r.w), h(r.h) {}
};
struct cColorRGBA { float r, g, b, a; };
struct cZero3 { u32 a, b, c; };

// eastl::basic_string<wchar_t> stand-in: begin/end/capacity pointers
struct cWStr {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  void DeallocateSelf();   // 0x933960
};
extern wchar_t g_EmptyWStr[];   // 0x1667bac

// UI window object; slot numbers are vtable byte offsets / 4
class cWin {
public:
  virtual void AddRef();                               // 0x00
  virtual void Release();                              // 0x04
  virtual void s02(); virtual void* GetProperty(u32 id); virtual void s04(); virtual void s05();
  virtual void s06(); virtual u32 GetWindowID(); virtual void s08(); virtual void s09();
  virtual void s10(); virtual void s11(); virtual void s12();
  virtual u32  GetThing();                             // 0x34
  virtual float* GetArea();                            // 0x38
  virtual void s15(); virtual int GetIndex(); virtual void s17(); virtual void s18();
  virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
  virtual void SetColor(u32 c);                        // 0x5c
  virtual void SetThing(u32 v);                        // 0x60
  virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
  virtual void s29(); virtual void s30();
  virtual void SetVisible(int a, int b);               // 0x7c
  virtual void SetText(const void* p);                 // 0x80
  virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36();
  virtual void s37(); virtual void s38(); virtual void s39(); virtual void s40();
  virtual void s41(); virtual void s42(); virtual void s43(); virtual void s44();
  virtual void* FindHandler(u32 id);                   // 0xb4
  virtual void SetHandler(u32 id, void* p);            // 0xb8
  virtual void s47(); virtual void s48(); virtual void s49(); virtual void s50();
  virtual void s51(); virtual void s52(); virtual void s53(); virtual void s54();
  virtual void s55(); virtual void s56(); virtual void s57(); virtual void s58();
  virtual void s59(); virtual void s60(); virtual void s61(); virtual void s62();
  virtual void s63(); virtual void s64();
  virtual void SetWindowArg(void* p);                  // 0x104
};

class cWindowManager {
public:
  virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
  virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
  virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18();
  virtual void SetFocus(int a, cWin* w);               // 0x4c
};

class cSpeciesProfile {
public:
  void GetUiName(cWStr* out);                          // 0x4da330
};

class cAudioMgr {
public:
  bool Query(const cVec3* v);                          // 0xb7d4f0
  void Fill(cVec3 v, int a, int b, int c, int d, cZero3* o1, cZero3* o2);   // 0xb7d440
};

class cModelObj {
public:
  cVec3* GetPos();                                     // 0xb8d8e0
};

class cPlanetModel {
public:
  u32 pad[3];
  void Query(cZero3* a, cZero3* b, void* c);          // 0xe21260
  void SetA(const void* p);                            // 0xe20d60
  void SetB(float f);                                  // 0xe20d30
};

class cInfo {
public:
  u32 mFirst;                  // 0x00
  char pad04[0x2c];
  u32 m30;                     // 0x30
  char pad34[8];
  u32 m3c;                     // 0x3c
  char pad40[8];
  cSpeciesProfile* mpSpecies;  // 0x48
  char pad4c[0x5c];
  u32 mA8;                     // 0xa8
  unsigned char mFlagAC;       // 0xac
  char padAD[0xb];
  u32 mB8;                     // 0xb8
  cInfo* Resolve();            // 0xde4610
  cModelObj* Get(int i);       // 0xbbaa60
};

class cMgr8c {
public:
  virtual void v00();
  virtual void AddRef();                               // 0x04
  virtual void Release();                              // 0x08
  void Attach(cWin* w, int flag);                      // 0x80dda0
};

class cSPBoundingBoxMgr {
public:
  cMgr8c* GetCollection();                             // 0x80f730
};

class cSPUILayout {
public:
  char pad0[0x20];
  cWin* FindWindowByID(u32 id, int flag);              // 0x8105b0
  void  Shutdown(u32 flag);                            // 0x811ad0
  bool  Init(const wchar_t* pName, int a, bool b, u32 c);   // 0x812160
};

extern "C" {
  void*   __cdecl GetRecorderState();                  // 0x435e90
  void    __cdecl KillSetiEffects(u32 id, void* rec);  // 0x435ed0
  void    __cdecl Pollinator(cWin* w, cRect4* r);      // 0x806d10
  void    __cdecl FUN_00de3f00(cWin* w, void* p, void* q);
  void    __cdecl FUN_00de3fa0(cWStr* out, u32 v);
  void    __cdecl FUN_00de40e0(cWStr* out, void* p);
  cWin*   __cdecl FUN_00de3e00(cWin* w);               // sGetWindowImage
  cAudioMgr* __cdecl FUN_00b3d360();
  u32     __cdecl ColorRGBAToU32(const cColorRGBA* c); // 0x4580c0
  void    __cdecl operator_delete_arr(void* p);        // 0xf47380
  cWindowManager* __cdecl WindowManager();             // 0x67caa0
}
extern float g_PlanetScale;   // 0x16a0da0
extern char g_PlanetKey[];    // 0x16a0dd0
extern float g_ColorK;        // 0x1485720

namespace {

class cGameUIData : public cSPUILayout {
public:
  cPlanetModel mPlanet;        // 0x20
  int    mUIState;             // 0x2c
  cInfo* mpInfo;               // 0x30
  char pad34[0x58];
  cMgr8c* mpMgr;               // 0x8c
  bool SetUIState(int newState);
  bool SetLayout(const wchar_t* pName, void* pArg);
};

// @ 0x00df6db0
bool cGameUIData::SetUIState(int newState) {
  if (mUIState == newState) return true;
  switch (newState) {
  case 2:
    KillSetiEffects(0xd06d9182, GetRecorderState());
    FindWindowByID(0x46a9ca7, 1)->SetVisible(1, 0);
    FindWindowByID(0x4656452, 1)->SetVisible(1, 1);
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 1);
    mUIState = newState;
    return true;
  case 3:
    KillSetiEffects(0xd06d9182, GetRecorderState());
    FindWindowByID(0x46a9ca7, 1)->SetVisible(1, 1);
    WindowManager()->SetFocus(1, FindWindowByID(0x46a9ca7, 1));
    mUIState = newState;
    FindWindowByID(0x2e712e4, 1)->SetText((const void*)mpInfo->mFirst);
    FindWindowByID(0x46ea550, 1)->SetText((const void*)mpInfo->mFirst);
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 1);
    return true;
  case 4:
    KillSetiEffects(0xd2fc3ad5, GetRecorderState());
    FindWindowByID(0x4656452, 1)->SetVisible(1, 0);
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 0);
    return true;
  case 5: {
    KillSetiEffects(0x6c6da889, GetRecorderState());
    FindWindowByID(0x4656452, 1)->SetVisible(1, 0);
    FindWindowByID(0x46a9ca7, 1)->SetVisible(1, 0);
    FindWindowByID(0x3753f40, 1)->SetVisible(1, 1);
    cWin* w = FindWindowByID(0x5b31710, 1);
    if (w) {
      w->SetThing(FindWindowByID(0x5b34d93, 1)->GetThing());
      w->SetVisible(1, 1);
    }
    break;
  }
  case 1: {
    cWStr str;
    cZero3 z1, z2, z3, z4;
    cWin* w = FindWindowByID(0x2e5a4a8, 1);
    if (!w) break;
    w->SetVisible(1, 1);
    cRect4 R(*(const cRect4*)w->GetArea());
    float nl = -R.x, nt = -R.y;
    R.x = nl + R.x;
    R.y = nt + R.y;
    R.w = R.w + nl;
    R.h = R.h + nt;
    u32 ids[3];
    ids[0] = 0x3753f40; ids[1] = 0x4656452; ids[2] = 0x46a9ca7;
    FindWindowByID(0x5b31710, 1)->SetVisible(1, 0);
    for (u32 i = 0; i < 3; ++i) {
      cWin* c = FindWindowByID(ids[i], 1);
      c->SetVisible(1, 0);
      Pollinator(c, &R);
    }
    if (mpInfo->m3c != 0) {
      cWin* c1 = FindWindowByID(0x2e71340, 1);
      FUN_00de3f00(c1, &mpInfo->m3c, 0);
      c1 = FindWindowByID(0x46ea568, 1);
      FUN_00de3f00(c1, &mpInfo->m3c, 0);
    } else {
      cWin* c = FindWindowByID(0x2e71340, 1);
      if (c) c->SetVisible(1, 0);
      c = FindWindowByID(0x46ea568, 1);
      if (c) c->SetVisible(1, 0);
      c = FindWindowByID(0x68dac20, 1);
      if (c) c->SetVisible(1, 1);
      c = FindWindowByID(0x68dac21, 1);
      if (c) c->SetVisible(1, 1);
    }
    cWin* c = FindWindowByID(0x46a9a21, 1);
    FUN_00de3f00(c, &mpInfo->m30, 0);
    c = FindWindowByID(0x46ea4b6, 1);
    FUN_00de3f00(c, &mpInfo->m30, 0);
    c->SetHandler(0x37ac490, (void*)(mpInfo->mB8 + 0x18));
    FUN_00de3fa0(&str, mpInfo->mA8);
    c = FindWindowByID(0x594a640, 1);
    if (c) c->SetText(str.mpBegin);
    c = FindWindowByID(0x5ff9352, 1);
    if (c) c->SetText(str.mpBegin);
    if (mpInfo->mpSpecies) {
      cWStr name;
      name.mpBegin = g_EmptyWStr;
      name.mpEnd = g_EmptyWStr;
      name.mpCapacity = g_EmptyWStr + 1;
      c = FindWindowByID(0x5ff9ad2, 1);
      if (c) {
        mpInfo->mpSpecies->GetUiName(&name);
        c->SetText(name.mpBegin);
      }
      c = FindWindowByID(0x5ff9d44, 1);
      if (c) {
        mpInfo->mpSpecies->GetUiName(&name);
        c->SetText(name.mpBegin);
      }
      name.DeallocateSelf();
    }
    u32 id = (mpInfo->mFlagAC ? 0x14de36a : 0) + 0x4656452;
    cWin* w5 = FindWindowByID(0x5b31710, 1);
    mpMgr->Attach(w5, 1);
    w5->SetThing(FindWindowByID(id, 1)->GetThing());
    if (mpInfo->Resolve()->mFlagAC) {
      cVec3 v = *mpInfo->Resolve()->Get(0)->GetPos();
      cZero3 a = {0, 0, 0};
      cZero3 b = {0, 0, 0};
      if (FUN_00b3d360()->Query(&v)) {
        FUN_00b3d360()->Fill(v, 0, 0, 0, 0, &a, &b);
        if (a.a != 0) {
          mPlanet.Query(&a, &b, mpMgr);
          mPlanet.SetA(g_PlanetKey);
          mPlanet.SetB(g_PlanetScale);
        }
      }
    }
    cWin* img = FUN_00de3e00(FindWindowByID(mpInfo->mA8 + 0x3744ff0, 1));
    if (img) img->AddRef();
    z1.a = 0; z1.b = 0; z1.c = 0;
    FUN_00de3f00(FindWindowByID(0x2e713a8, 1), &z1, img);
    z2.a = 0; z2.b = 0; z2.c = 0;
    FUN_00de3f00(FindWindowByID(0x46ea523, 1), &z2, img);
    z3.a = 0; z3.b = 0; z3.c = 0;
    FUN_00de3f00(FindWindowByID(0x26e0001, 1), &z3, img);
    z4.a = 0; z4.b = 0; z4.c = 0;
    FUN_00de3f00(FindWindowByID(0x26e0002, 1), &z4, img);
    c = FindWindowByID(0x2e712e4, 1);
    if (c) c->SetText((const void*)mpInfo->mFirst);
    c = FindWindowByID(0x46ea550, 1);
    if (c) c->SetText((const void*)mpInfo->mFirst);
    if (mpInfo && mpInfo->Resolve()) {
      cWStr s2;
      FUN_00de40e0(&s2, (char*)mpInfo->Resolve() + 0x18);
      FindWindowByID(0x46a9a9b, 1)->SetText(s2.mpBegin);
      FindWindowByID(0x46ea507, 1)->SetText(s2.mpBegin);
      cWin* cc = FindWindowByID(0x47e3cd3, 1);
      cColorRGBA col;
      col.r = 0.0f; col.g = g_ColorK; col.b = 0.0f; col.a = g_ColorK;
      cc->SetColor(ColorRGBAToU32(&col));
      s2.DeallocateSelf();
    }
    if (img) img->Release();
    if ((int)((str.mpCapacity - str.mpBegin) * 2 & ~1) > 2 && str.mpBegin)
      operator_delete_arr(str.mpBegin);
    mUIState = newState;
    return true;
  }
  default:
    return true;
  }
  mUIState = newState;
  return true;
}

// =====================================================================================
// Slice s00df6db0 -- cGameUIData::SetLayout (0x00DF76C0): called with a layout name and a
// window argument, it tears the old screen down, builds the new one and hands the argument
// to the four panels that own a per-layout window.
// =====================================================================================
extern unsigned char g_16a0f88;                        // 0x016a0f88  "layout already built" flag

// 0x0067CAD0 returns the bounding-box singleton, whose 0x0080F730 member yields the
// object stored in cGameUIData::mpMgr (refcounted, vtable +0x04 AddRef / +0x08 Release).
extern "C" cSPBoundingBoxMgr* __cdecl AddBoundingBox(); // 0x0067cad0

// @ 0x00df76c0
bool cGameUIData::SetLayout(const wchar_t* pName, void* pArg) {
  mUIState = 0;
  cWin* w = FindWindowByID(0x46ea4b6, 1);
  if (w)
    w->SetHandler(0x37ac490, 0);
  Shutdown(1);
  if (pName) {
    bool ok = Init(pName, 0x40464100, 1, 0x5b598fa);
    cMgr8c* pNew = AddBoundingBox()->GetCollection();
    cMgr8c* pOld = mpMgr;
    if (pNew != pOld) {
      if (pNew)
        pNew->AddRef();
      mpMgr = pNew;
      if (pOld)
        pOld->Release();
    }
    if (ok && SetUIState(1)) {
      FindWindowByID(0x3753f40, 1)->SetWindowArg(pArg);
      FindWindowByID(0x4656452, 1)->SetWindowArg(pArg);
      FindWindowByID(0x46a9ca7, 1)->SetWindowArg(pArg);
      FindWindowByID(0x638491d, 1)->SetWindowArg(pArg);
      if (mpInfo && mpInfo->mA8 == 5 && !g_16a0f88) {
        cWin* c = FindWindowByID(0x3c4925e, 1);
        if (c)
          c->SetVisible(2, 0);
      }
    }
    return ok;
  }
  return false;
}

}  // namespace

// force emission
bool Instantiate_SetUIState(void* p, int s) { return ((cGameUIData*)p)->SetUIState(s); }
bool Instantiate_SetLayout(void* p, const wchar_t* n, void* a) { return ((cGameUIData*)p)->SetLayout(n, a); }

// =====================================================================================
// Slice s00df6db0 -- the Space-game galaxy entry callbacks at 0x00DF7830 .. 0x00DF7C20.
// The whole screen setup is reachable through the interface singleton at 0x016A1344.
// =====================================================================================

class cGalaxyGameEntry;
class cStarManager;

// one interface message (see cSPUIMessage): object + window payloads and the message ids
struct cMessage {
  cWin* mpObject;              // 0x00
  cWin* mpWindow;              // 0x04
  u32   mId;                   // 0x08
  u32   mSub;                  // 0x0c
  char  pad10[8];
  cWin* mpWindow2;             // 0x18
};

// 4-byte id -> entry table, the pieces the interface keeps for the galaxy screen
class cEntryTable {
public:
  cGalaxyGameEntry* GetEntry(int index) {
    return *(cGalaxyGameEntry**)((char*)this + index * 4);
  }
};

class cGalaxyGameEntry {
public:
  char pad00[0x80];
  char mSub80[0x2c];           // 0x80
  unsigned char mEntryKind;    // 0xac
  char padAD[0xb];
  cGameUIData* mpLayout;       // 0xb8
  cStarManager* Resolve(void* key, int flag);          // 0x00de4610
};

class cUIHints {
public:
  void Next(int id, char flag);                        // 0x0067c3b0
};

class cPushMatrixOwner {
public:
  void PushMatrix(const void* p);                      // 0x00ddfb50
};

class cAudioSystemAT {
public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual u32  GetHandle();                            // 0x20
};

// the interface singleton
struct cSpaceGame {
  char pad00[0x24];
  cEntryTable* mpArray24;      // 0x24  id -> entry table
  char pad28[0xa0];
  unsigned char mC8;           // 0xc8
  char padC9[0x2f];
  cGalaxyGameEntry* mpDisplayed;   // 0xf8
  cGalaxyGameEntry* mpPending;     // 0xfc
  char pad100[8];
  int   m108;                  // 0x108
  char pad10c[0x8c];
  cPushMatrixOwner* mp198;     // 0x198
  char pad19c[0xd5];
  unsigned char m271;          // 0x271
  cUIHints* GetUIHints();                              // 0x0067cac0
  void FUN_00de86d0(int a, int b);                     // 0x00de86d0
  void FUN_00de9ec0();                                 // 0x00de9ec0
  void FUN_00de53d0(int a);                            // 0x00de53d0
};

struct cUISingleton48 {
  char pad00[0x48];
  cGalaxyGameEntry* mp48;      // 0x48
};

class cFont {
public:
  void SetUserData(void* p);                           // 0x00fd9450
};

class cGalaxyGameEntryImpl {
public:
  virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
  virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
  virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
  virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
  virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
  virtual void v20(); virtual void v21(); virtual void v22();
  virtual void v5c(int a);                             // 0x5c
  virtual void v60(void* p, int b);                    // 0x60
  virtual void v64(cGalaxyGameEntry* p, float f1, float f2);   // 0x64

  bool DoMessage(u32 msg, cMessage* pMsg);             // 0x00df7830
  void SetPendingGame(cGalaxyGameEntry* pGame, char flag);     // 0x00df7af0
  void SetDisplayedEntry(cGalaxyGameEntry* pEntry);    // 0x00df7c20
};

extern cSpaceGame* g_16a1344;                          // 0x016a1344
extern cGalaxyGameEntryImpl* g_16a1484;                // 0x016a1484
extern cFont* g_16a1570;                               // 0x016a1570
extern cGalaxyGameEntryImpl* g_16a15fc;                // 0x016a15fc
extern cUISingleton48* g_16a11b4;                      // 0x016a11b4

class cHintOwner {
public:
  void ResetHints();                                   // 0x00dda0d0
};

extern "C" {
  cHintOwner* __stdcall FUN_00dd9190(int a);           // 0x00dd9190
  void*     __cdecl FUN_00a206f0();                    // 0x00a206f0
  void      __cdecl FUN_00de3c70(void* p, float* f1, float* f2);   // 0x00de3c70
}

class cStarManager {
public:
  void SetStar();                                      // 0x00bbac80
};

// @ 0x00df7830
bool cGalaxyGameEntryImpl::DoMessage(u32 msg, cMessage* pMsg) {
  if (pMsg->mId == 0x4f5527e8) {
    cWin* w = g_16a1344->mpPending->mpLayout->FindWindowByID(0x3f56d9e, 1);
    if (w) {
      cWin* p = (cWin*)w->GetProperty(0x2f5528d9);
      if (p) {
        int idx = p->GetIndex();
        g_16a1344->mpPending->Resolve(
            g_16a1344->mpArray24->GetEntry(idx), 1)->SetStar();
      }
    }
  }
  if (pMsg->mId == 10 && pMsg->mSub == 1 && pMsg->mpWindow != 0 &&
      pMsg->mpWindow->GetWindowID() == 0x4656452) {
    cWin* p = (cWin*)pMsg->mpWindow->FindHandler(0x37ac490);
    cWin* q;
    void* v = (p != 0 && (q = (cWin*)p->GetProperty(0x37ac490)) != 0)
                  ? *(void**)((char*)q + 4)
                  : 0;
    if (pMsg->mpWindow != pMsg->mpWindow2 && v == (void*)g_16a1344->mpDisplayed)
      v5c(0);
  }
  if (pMsg->mId == 7 && g_16a1344->mpDisplayed != 0) {
    cWin* a = g_16a1344->mpDisplayed->mpLayout->FindWindowByID(0x4656452, 1);
    cWin* b = g_16a1344->mpDisplayed->mpLayout->FindWindowByID(0x638491d, 1);
    if (pMsg->mpWindow == a || pMsg->mpWindow == b) {
      if (g_16a1344->mpDisplayed->mEntryKind == 0) {
        g_16a1570->SetUserData(g_16a1344->mpDisplayed);
        g_16a1344->FUN_00de86d0(4, 0);
      } else {
        g_16a1344->mp198->PushMatrix(&g_16a1344->mpDisplayed->mSub80[0]);
      }
      g_16a15fc->v60(g_16a1344->mpDisplayed, 1);
    }
  }
  if (pMsg->mId == 0x287259f6) {
    u32 id = pMsg->mpObject->GetWindowID();
    if (id == 0x3c4925e) {
      if (g_16a1344->mpPending) {
        cAudioSystemAT* pAudio = (cAudioSystemAT*)FUN_00a206f0();
        u32 handle = pAudio ? pAudio->GetHandle() : 0;
        KillSetiEffects(0x4e53ef11, (void*)handle);
        g_16a11b4->mp48 = g_16a1344->mpPending;
        g_16a1344->FUN_00de86d0(0xb, 0);
        return true;
      }
    } else if (id == 0x375408c) {
      cAudioSystemAT* pAudio = (cAudioSystemAT*)FUN_00a206f0();
      u32 handle = pAudio ? pAudio->GetHandle() : 0;
      KillSetiEffects(0x4e53ef11, (void*)handle);
      g_16a1344->mpPending->mpLayout->SetUIState(1);
      g_16a1484->v5c((int)g_16a1344->mpPending);
      g_16a1344->FUN_00de86d0(0xc, 0);
      return true;
    } else if (id == 0x3754098 || id == 0x3743e9c) {
      v60(0, 1);
    }
  }
  return true;
}

// @ 0x00df7af0
void cGalaxyGameEntryImpl::SetPendingGame(cGalaxyGameEntry* pGame, char flag) {
  if (g_16a1344->mpPending == pGame)
    return;
  if (pGame) {
    v5c(0);
    FUN_00dd9190(2)->ResetHints();
    g_16a1344->m271 = 0;
    cSpaceGame* pSingleton = g_16a1344;
    pSingleton->mC8 = 0;
    pSingleton->GetUIHints()->Next(0x2e25815e, 0);
  } else if (g_16a1344->m108 == 2) {
    g_16a1344->FUN_00de9ec0();
    if (g_16a1344->mpPending) {
      cGameUIData* pLayout = g_16a1344->mpPending->mpLayout;
      if (pLayout) {
        cWin* w = pLayout->FindWindowByID(0x46ad82d, 1);
        if (w)
          w->SetVisible(1, 0);
        g_16a1344->FUN_00de53d0(0);
      }
    }
  }
  if (g_16a1344->mpPending && flag)
    g_16a1344->mpPending->mpLayout->SetUIState(1);
  g_16a1344->mpPending = 0;
  if (pGame) {
    g_16a1344->mpPending = pGame;
    if (flag) {
      if (pGame->mEntryKind)
        pGame->mpLayout->SetUIState(5);
      else
        pGame->mpLayout->SetUIState(4);
    }
  }
}

// @ 0x00df7c20
void cGalaxyGameEntryImpl::SetDisplayedEntry(cGalaxyGameEntry* pEntry) {
  if (g_16a1344->mpPending)
    return;
  cGalaxyGameEntry* pOld = g_16a1344->mpDisplayed;
  if (pOld == pEntry)
    return;
  if (pOld)
    pOld->mpLayout->SetUIState(1);
  g_16a1344->mpDisplayed = 0;
  if (!pEntry || !pEntry->mpLayout)
    return;
  if (pEntry->mEntryKind)
    pEntry->mpLayout->SetUIState(3);
  else
    pEntry->mpLayout->SetUIState(2);
  v60(0, 1);
  float f1, f2;
  FUN_00de3c70(&pEntry->mSub80[0], &f1, &f2);
  v64(pEntry, f2, f1);
  g_16a1344->mpDisplayed = pEntry;
}
