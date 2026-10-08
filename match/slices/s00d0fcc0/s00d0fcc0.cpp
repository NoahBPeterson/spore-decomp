// Slice s00d0fcc0 -- SP::cCommunityEditor::Deactivate (retail layout; offsets from the disassembly).
// /O2 /MD /Gy /TP /arch:SSE region (UI editor code, no /EHsc).
#include "types.h"

void __cdecl operator_delete_array(void* p);   // 0x00f47380 (operator delete[])

// eastl::basic_string<wchar_t> temporary (3 words used by the compiler-visible part)
struct WStr {
  wchar_t* mb;
  wchar_t* me;
  wchar_t* mc;
  int mAlloc;
  void RangeInit(const wchar_t* p);   // 0x00579A90 basic_string::RangeInitialize
  WStr(const wchar_t* p) { mb = 0; me = 0; mc = 0; RangeInit(p); }
  ~WStr() {
    if ((((char*)mc - (char*)mb) & ~1) > 2) {
      if (mb) operator_delete_array(mb);
    }
  }
};

struct V3 { float x, y, z; };

// Calls through a vtable slot at byte offset `off` (thiscall).
#define VT(o, off) ((*(void***)(o))[(off) / 4])
#define VCALL0(R, o, off) (((R(__thiscall*)(void*))VT(o, off))(o))
#define VCALL1(R, T, o, off, a) (((R(__thiscall*)(void*, T))VT(o, off))(o, a))

struct Any;
struct PtrVec { Any** b; Any** e; };

// Generic object stub: only the methods Deactivate calls (all thiscall, addresses in comments).
struct Any {
  char pad0[0x34];
  char sub34[4];                      // embedded sub-object at +0x34 (has its own vtable)
  char pad38[0x192 - 0x38];
  char b192;
  Any* Bce470();                      // 0x00bce470
  void C3f160(void* a);               // 0x00c3f160
  Any* Bd81f0();                      // 0x00bd81f0
  void Ff14f0(WStr* s);               // 0x00ff14f0
  void Ff1510(WStr* s);               // 0x00ff1510
  void Be5700(void* vec);             // 0x00be5700
  Any* C71040(int a);                 // 0x00c71040
  void Ff3190(void* a);               // 0x00ff3190
  PtrVec* Bef6c0();                   // 0x00bef6c0
  void Bd9e50();                      // 0x00bd9e50
  void Hints_Update();                // 0x0067c350
  void Hints_SetEnabled();            // 0x0067c420
  void E14c10(int a);                 // 0x00e14c10
  void Cd6e90();                      // 0x00cd6e90
  void Shutdown5bfb90();              // 0x005bfb90 (cSPEditorNaming::Shutdown)
  void CityMusicShutdown();           // 0x00ea13e0
  void CityMusicSetVisibility(int v); // 0x00ea0010
  int FindCategoryIndex();            // 0x005ca9c0
  void PaletteShutdown();             // 0x005cba90
  void F5c5c20();                     // 0x005c5c20
  void LayoutSetVisibility(int v);    // 0x00810590
  Any* FindWindowByID(unsigned id, int a);   // 0x008105b0
  void DecPauseGate(unsigned id);     // 0x00b32250
  void SetBoolProperty(unsigned key, int v); // 0x006a17e0
  void RemoveNoun(unsigned id);       // 0x00b225d0
  Any* GetPlayerCivilization();       // 0x00b25fb0
  void F80dc50();                     // 0x0080dc50
};

struct Cam {
  char pad0[0x10];
  char b10;
  char pad11;
  char b12;
  void F11870(void* a);               // 0x00b11870
  void F0f700(float a, float b);      // 0x00b0f700 (ret 8)
  void SetYaw(float y);               // 0x00b10470
  void F13bb0(V3* v, int a);          // 0x00b13bb0
  void F10340(float x, float y, float z);   // 0x00b10340 (ret 0xc)
};

struct Vec4 { void* b; void* e; };
void __stdcall VecErase(Vec4* v, void* first, void* last);   // placeholder (member below)
struct VecStub {
  void* b;
  void* e;
  void* c;
  void Erase(void* first, void* last);   // 0x00e25bd0 (vector<AutoRefCount<..>>::erase, ret 8)
};

// fixed_vector<Any*, 32> with an inline buffer
struct Fixed32 {
  Any** mpBegin;
  Any** mpEnd;
  Any** mpCap;
  void* mName;
  Any** mpPool;
  void* mPad;
  Any* mBuf[32];
  Fixed32() {
    mpBegin = mBuf; mpEnd = mBuf; mpPool = mBuf; mpCap = mBuf + 32;
  }
};

unsigned __cdecl GetCurrentGameMode();                  // 0x00b5b800
Any* NounManager();                                     // 0x00b3d300
Any* GetActivePlanet();                                 // 0x01021260
void __cdecl FUN_00d49450();                            // 0x00d49450
void __cdecl RemoveHandler(void* server, void* handler, void* ids, int count, int prio);  // 0x00571db0
Any* FUN_00b3d230();                                    // 0x00b3d230
Any* __stdcall GetHints(int a, int b);                  // 0x0067cac0 (ret 8)
Any* __stdcall AddBoundingBox(void* w);                 // 0x0067cad0 (ret 4)
Any* FUN_00b3d400();                                    // 0x00b3d400
Any* TribeModeInstance();                               // 0x00cd40b0
Any* GameTimeManager();                                 // 0x00b3d380
Any* EffectsManager();                                  // 0x0067ddd0
Any* MessageServer();                                   // 0x0067dcc0
Any* GameInputManager();                                // 0x00b3d250
Cam* FUN_00b3d280();                                    // 0x00b3d280
extern Any* g_PropList;                                 // 0x015fd918
extern int g_169d580;                                   // 0x0169d580

struct CE {
  char pad0[0x14];
  void* ahServer;         // +0x14 AutoHandler
  void* ahHandler;
  void* ahIds;
  int ahCount;
  int ahPrio;
  char pad28[0x40 - 0x28];
  Any* community;         // +0x40
  int lastShop;           // +0x44
  int recentlyEdited;     // +0x48
  char pad4c[0x78 - 0x4c];
  Any* limit;             // +0x78
  Any* sellback;          // +0x7c
  void* editorUIvft;      // +0x80
  char pad84[4];
  char editorUI[0x18];    // +0x88 (cSPUILayout)
  Any* paletteData;       // +0xa0
  Any* paletteUI;         // +0xa4
  void* winRoot;          // +0xa8
  Any* ring;              // +0xac
  Any* manip;             // +0xb0
  Any* selected;          // +0xb4
  char padb8[4];
  unsigned nounId;        // +0xbc
  char padc0[4];
  int fieldC4;            // +0xc4
  char padc8[0x130 - 0xc8];
  VecStub vA;             // +0x130
  char pad13c[0x144 - 0x13c];
  VecStub vB;             // +0x144
  char pad150[0x1dc - 0x150];
  VecStub vC;             // +0x1dc
  char pad1e8[0x1f0 - 0x1e8];
  VecStub vD;             // +0x1f0
  char pad1fc[0x204 - 0x1fc];
  int reason;             // +0x204
  char pad208;
  unsigned char effByte;           // +0x209
  char pad20a[0x2c4 - 0x20a];
  void* camArg;           // +0x2c4
  char pad2c8[0x2d8 - 0x2c8];
  V3 camPos;              // +0x2d8
  float camX, camY, camZ; // +0x2e4
  Any* camCommunity;      // +0x2f0
  int categoryIndex;      // +0x2f4

  void D0dea0();          // 0x00d0dea0
  void D0c760();          // 0x00d0c760
  void D0cec0();          // 0x00d0cec0
  void D0bf80();          // 0x00d0bf80
  void __thiscall Deactivate(int reasonArg, bool flag);   // 0x00d100b0 (ret 8)
};

// @ 0x00d100b0
void CE::Deactivate(int reasonArg, bool flag) {
  int i;
  if (community != 0) {
  if (GetCurrentGameMode() == 0x1654c05) {
    if (NounManager() != 0) {
      Any* civ = NounManager()->GetPlayerCivilization();
      if (civ != 0 && GetActivePlanet() != 0) {
        int id = VCALL0(int, civ, 0x4c);
        Any* x = GetActivePlanet()->C71040(id);
        if (x != 0)
          x->Ff3190((char*)civ + 0x6c);
        PtrVec* pv = civ->Bef6c0();
        int n = (int)(pv->e - pv->b);
        for (i = 0; i < n; i++) {
          Any* e = civ->Bef6c0()->b[i];
          if (e != 0)
            e->Bd9e50();
        }
      }
    }
  } else {
    if (GetCurrentGameMode() == 0x1654c02)
      FUN_00d49450();
  }
  reason = reasonArg;
  if (ahServer != 0) {
    void* srv = ahServer;
    ahServer = 0;
    RemoveHandler(srv, ahHandler, ahIds, ahCount, ahPrio);
  }
  if (lastShop != 0) {
    Any* o = FUN_00b3d230();
    VCALL1(void, int, o, 0x40, lastShop);
  }
  GetHints(0, 1)->Hints_Update();
  GetHints(effByte, 1)->Hints_SetEnabled();
  if (paletteUI != 0) {
    paletteUI->Shutdown5bfb90();
    Any* p = paletteUI;
    if (p != 0) {
      paletteUI = 0;
      VCALL0(void, p, 4);
    }
  }
  if (sellback != 0) {
    VCALL0(void, sellback, 4);
    operator_delete_array(sellback);
    sellback = 0;
    editorUIvft = 0;
  }
  if (ring != 0) {
    ring->CityMusicShutdown();
    Any* p = ring;
    if (p != 0) {
      ring = 0;
      VCALL0(void, p, 4);
    }
  }
  D0dea0();
  if (community != 0) {
    Any* q = (Any*)VCALL1(void*, unsigned, community, 0xc, 0xee9b2232);
    if (q != 0) {
      Fixed32 vec;
      q->b192 = 0;
      q->Be5700(&vec);
      int n = (int)(vec.mpEnd - vec.mpBegin);
      for (int k = 0; k < n; k++) {
        Any* e = vec.mpBegin[k];
        if (e != 0 && e->Bce470() != 0) {
          Any* e2 = vec.mpBegin[k];
          void* r = VCALL1(void*, float, e2->sub34, 0x2c, 6.0f);
          e2->Bce470()->C3f160(r);
        }
      }
      Any* w = q->Bd81f0();
      if (w != 0) {
        void* sub = q->sub34;
        {
          WStr s((const wchar_t*)VCALL0(void*, sub, 4));
          w->Ff14f0(&s);
        }
        {
          WStr s((const wchar_t*)VCALL0(void*, sub, 0xc));
          w->Ff1510(&s);
        }
      }
      if (reasonArg == 0 && FUN_00b3d400() != 0)
        FUN_00b3d400()->E14c10(1);
      {
        Any** pc = vec.mpBegin;
        Any** pe = vec.mpEnd;
        for (; pc < pe; ++pc)
          if (*pc) VCALL0(void, *pc, 4);
        Any** pb = vec.mpBegin;
        if (pb && pb != vec.mpPool) operator_delete_array(pb);
      }
    }
  }
  if (community != 0) {
    Any* q = (Any*)VCALL1(void*, unsigned, community, 0xc, 0x4f396a66);
    if (q != 0) {
      q->b192 = 0;
      Any* win = ((Any*)(editorUI))->FindWindowByID(0x563fa08, 1);
      if (win != 0)
        ((void(__thiscall*)(void*, int, int))VT(win, 0x7c))(win, 1, 0);
      TribeModeInstance()->Cd6e90();
    }
  }
  if (community != 0) {
    D0c760();
    if (reason == 0) {
      recentlyEdited = -1;
      g_PropList->SetBoolProperty(0x387d0a8, 1);
      GameTimeManager()->DecPauseGate(0x4bf38a6);
    }
    Cam* cam = FUN_00b3d280();
    if (cam != 0) {
      if (camArg != 0)
        cam->F11870(camArg);
      cam->b10 = 1;
      cam->F0f700(0.0f, 0.0f);
      if (cam->b12 != 0)
        cam->SetYaw(0.0f);
      if (community == camCommunity) {
        V3 v = camPos;
        if (FUN_00b3d280() != 0)
          FUN_00b3d280()->F13bb0(&v, 0);
      }
      cam->F10340(camX, camY, camZ);
    }
    if (ring != 0)
      ring->CityMusicSetVisibility(0);
    D0cec0();
    if (selected != 0) {
      categoryIndex = selected->FindCategoryIndex();
      selected->PaletteShutdown();
      Any* p = selected;
      if (p != 0) {
        selected = 0;
        VCALL0(void, p, 4);
      }
    }
    if (limit != 0) {
      Any* p = limit;
      limit = 0;
      VCALL0(void, p, 4);
    }
    if (manip != 0) {
      manip->F5c5c20();
      Any* p = manip;
      if (p != 0) {
        manip = 0;
        VCALL0(void, p, 8);
      }
    }
    if (paletteData != 0) {
      VCALL0(void, paletteData, 0x24);
      Any* p = paletteData;
      if (p != 0) {
        paletteData = 0;
        VCALL0(void, p, 4);
      }
    }
    ((Any*)editorUI)->LayoutSetVisibility(0);
    Any* fx = 0;
    Any* mgr = EffectsManager();
    char ok = ((char(__thiscall*)(void*, unsigned, int, Any**))VT(mgr, 0x2c))(mgr, 0xb2540a24, 0, &fx);
    if (ok != 0)
      ((void(__thiscall*)(void*, int))VT(fx, 8))(fx, 0);
    Any* ms = MessageServer();
    ((void(__thiscall*)(void*, unsigned, void*, int))VT(ms, 0x14))(ms, 0x3e9a625, this, 0);
    if (flag) {
      Any* gi = GameInputManager();
      ((void(__thiscall*)(void*, int, int))VT(gi, 0x64))(gi, 0x3e86, 1);
    }
  }
  unsigned noun = nounId;
  fieldC4 = 0;
  if (noun != 0) {
    NounManager()->RemoveNoun(noun);
    nounId = 0;
  }
  vA.Erase(vA.b, vA.e);
  vB.Erase(vB.b, vB.e);
  vC.Erase(vC.b, vC.e);
  vD.Erase(vD.b, vD.e);
  D0bf80();
  AddBoundingBox(winRoot)->F80dc50();
  g_169d580 = 0;
  }
}
