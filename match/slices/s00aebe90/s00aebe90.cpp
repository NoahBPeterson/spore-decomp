// Slice s00aebe90 (cl1_new #38): one 4337-byte function.
//
// CommDialogHost::ShowDialog(CommDlg*): shows a comm-screen dialog (the
// space/creature "speaker text + response list" screen). Sets this->current
// (refcounted) to the new dialog, queries the UI controller (vt[2]) for the
// speaker text/responses, fills the cSPUICommScreen layout, posts a
// behaviour message, swaps the space token translator's fields around the
// text lookups and finally tears everything down.
//
// Stack-argument counts for the unnamed callees were derived by simulating
// the pending pushes (callee-pop thiscall), see the per-call comments.
#include "types.h"
#include <string.h>
#include <intrin.h>

typedef unsigned int u32;

static const char kEastlAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// ---- raw allocator / eastl wstring helpers ---------------------------------
void* ea_new(unsigned size, const char* name, int flags, int a, const char* file, int line);  // 0xf473a0 cdecl
void  ea_delete(void* p);                                                                    // 0xf47380 cdecl
extern wchar_t gEmptyW[2];                                                                   // 0x1667bac

struct Vec3 { float x, y, z; };
struct TerrainSphere;
struct Obj3d400;

struct WStr {            // eastl::basic_string<wchar_t,allocator>, 16 bytes
  wchar_t* b;
  wchar_t* e;
  wchar_t* c;
  u32 alloc;
  void RangeInitialize(const wchar_t* s);   // 0x579a90 (out of line at the W0 site)
};

static inline void ws_init(WStr* s, const wchar_t* src, int n) {
  s->b = 0; s->e = 0; s->c = 0;
  int cap = n + 1;
  if ((unsigned)cap < 2) {
    s->b = gEmptyW; s->e = gEmptyW; s->c = gEmptyW + 1;
  } else {
    wchar_t* p = (wchar_t*)ea_new(cap * 2, "Simulator", 0, 0, kEastlAllocFile, 0xd1);
    s->b = p; s->e = p; s->c = p + cap;
  }
  memcpy(s->b, src, n * 2);
  s->e = s->b + n;
  *s->e = 0;
}

static inline void ws_free(WStr* s) {
  int bytes = (int)((char*)s->c - (char*)s->b) & ~1;
  if (bytes > 2 && s->b)
    ea_delete(s->b);
}

struct WStrVec {         // eastl::vector<wstring,sp_vector_allocator>
  WStr* b;
  WStr* e;
  WStr* c;
  void DoInsertValue(WStr* pos, WStr* val);   // 0x554c30
};

static inline void wsvec_push(WStrVec* v, const wchar_t* text) {
  const wchar_t* p = text;
  while (*p) ++p;
  int n = (int)(p - text);
  WStr tmp;
  ws_init(&tmp, text, n);
  if (v->e < v->c) {
    WStr* pe = v->e;
    v->e = pe + 1;
    if (pe)
      ws_init(pe, tmp.b, (int)(tmp.e - tmp.b));
  } else {
    v->DoInsertValue(v->e, &tmp);
  }
  ws_free(&tmp);
}

struct cString {         // SP::cString, 0x14 bytes
  u32 d[5];
  cString();                       // 0x6b5060
  ~cString();                      // 0x6b5240
  const wchar_t* GetText();        // 0x6b55c0
};

struct CStrVec { cString* b; cString* e; cString* c; };

struct Entry16 { u32 w[4]; };
struct Item12  { u32 a, b, c; };
struct Rec5    { u32 w[5]; };

struct Entry16Vec {
  Entry16* b; Entry16* e; Entry16* c;
  void DoInsertValue(Entry16* pos, Entry16* val);   // 0xc19d10
};

// ---- game objects (stubs) ---------------------------------------------------
struct Civ { u32 pad[0x10]; u32 f40; };
struct City { Civ* GetCivilization(); };            // 0xbd9bf0
struct Profile { u32 pad[0x147]; u32 f51c; };       // +0x51c, +0x504 is an embedded sub-object

struct Obj {                                        // refcounted/castable
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void* Cast(u32 type);                     // vt[3]
};

struct Empire {
  Vec3* GetColor(Vec3* out);                        // 0xc32cd0
  Profile* GetProfile();                            // 0xc30c80
  u32 Fn_c30f90();                                  // 0xc30f90
  void OnWinProcAdd(Empire* other);                 // 0x10829f0
};

struct StarMgr {
  void* ba6dc0(u32 id);                             // 0xba6dc0
  Empire* GetEmpireByID(u32 id);                    // 0xba9370
};
struct NounMgr {
  void* b20750(u32 id);                             // 0xb20750
  Obj* GetPlayerCivilization();                     // 0xb25fb0
  struct TerrainSphere* f67d90(u32 type);           // 0xf67d90 (GetCurrentTerrainSphere)
};
struct GameTimeMgr { void IncPauseGate(u32 id); };  // 0xb32220

struct HomePlanet { void* ce6950(); };              // 0xce6950
struct SpeciesMgr {
  Profile* GetProfile(u32 x);                       // 0x4df550
  Profile* GetAvatarProfile();                      // 0x4df420
};

struct CommScreen {                                 // 0xdd1ca0 singleton (cSPUICommScreen/layout)
  void Show();                                      // 0xdd2e80
  void* GetMainCreatureScreen();                    // 0xdd2cf0
  void* dd1e30(void* a, void* b);                   // 0xdd1e30
  void* dd1f70(void* buf, void* a, void* b);        // 0xdd1f70
  int   dd22f0();                                   // 0xdd22f0
  void  dd3a00(void* a, void* b);                   // 0xdd3a00
  void  UpdateSpaceInfo(u32 id, u32 f34, bool a, bool isZero, bool b50, bool b14, bool b2c, bool b18);  // 0xdd4b20
  void  SetSpeakerText(const wchar_t* t);           // 0xdd2ad0
  void  SetResponseCount(int n);                    // 0xdd3ed0
  void  dd2c60(int i, const wchar_t* t, bool f);    // 0xdd2c60
  void  dd32a0();                                   // 0xdd32a0
  void  dd2d00();                                   // 0xdd2d00
};

struct UiCtl {                                      // 0xb3d490 result
  u32 pad[0x24];
  unsigned char f90;
  unsigned char f91;
  void* ae7ce0(void* a, void* b, u32 c);                                        // 0xae7ce0 (3 stack args)
  void  ae8d00(void* p, void* r, Vec3* v, u32 i1, u32 i2, u32 i3);              // 0xae8d00 (6)
  void  ae8820(void* buf, Vec3 col, u32 i, void* r);                            // 0xae8820 (6)
  void  ae7e10(u32 a, u32 b, u32 c, u32 d);                                     // 0xae7e10 (4)
  void  c2e4e0();                                                               // 0xc2e4e0
};

struct VtA {                                        // 0xaed4d0 result; vtable slots by index
  virtual void s0();
  virtual void s1();
  virtual void s2(void* out, u32 f38, u32 f3c, Rec5* rec, int* o88, int* o8c,
                  cString* speaker, CStrVec* v1, void* d64, void* d8c, Empire* emp);   // 11 args
  virtual void s3();
  virtual void s4(u32 f38, u32 f3c, unsigned char* b14, unsigned char* b50,
                  unsigned char* b2c, unsigned char* b18);                              // 6 args
  virtual bool s5(u32 f38, u32 f3c);
  virtual void s6();
  virtual void s7(Entry16* out, u32 a, u32 b, Rec5* rec, int zero, cString* cs);        // 6 args
  virtual u32* s8(u32* sret, void* civ, void* f20, void* f24);
  virtual u32* s9(u32* sret, Empire* emp, Empire* pe, void* p34, u32 f40);
};

struct MsgServer {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
  virtual void s5(u32 id, void* msg, int flag);     // vt[5]
};

struct Msg {                                        // MessageBasicRC<5>-like, 0x40 bytes
  u32 w[16];                                        // w[0]=vt w[1]=rc, slot i at w[2+2i], w[12]=id, w[14]=mask
  void Destruct();                                  // 0x421cf0 (SlotMessage::Destruct)
};
extern char vtbl_BehaviorMessage[];                 // 0x13eb90c
extern char vtbl_MessageBasicRC5[];                 // 0x13eb844
extern char vtbl_LocaleChangeMessage[];             // 0x13eb918

struct TokenTr {
  u32 f00[6];
  u32 f18, f1c;
  u32 f20[4];
  u32 f30;
  u32 f34[5];
  u32 f48;
};
extern TokenTr* gpTokenTr;                          // 0x16e0d08

struct GObj {                                       // *0x169d3c8
  u32 cfe780(u32 a);                                // 0xcfe780
  u32 cfe790(u32 a);                                // 0xcfe790
};
extern GObj* gGObj;                                 // 0x169d3c8

struct Sim { u32 GetPlayerInventory(); };
struct TerrainSphere { void c77bf0(); };               // 0xc77bf0
struct Obj3d400 { void e14c10(u32 x); };              // 0xe14c10           // 0xa1ad60

struct HostBase;
struct CommDlg {                                    // refcounted dialog description
  virtual void AddRef();
  virtual void Release();
  bool Fn_ae9d40(CommDlg* d);        // 0xae9d40 (this = old dialog)
  u32 pad04[2];
  u32 f0c;
  u32 pad10[2];
  u32 f18;
  u32 pad1c;
  City* f20;
  City* f24;
  Civ*  f28;
  u32 pad2c[2];
  u32 f34;
  u32 f38;
  u32 f3c;
  u32 f40;
  u32 pad44[3];
  Item12* f50;
  Item12* f54;
  u32 pad58[3];
  u32 f64;
  u32 pad68[5];
  Entry16Vec vec78;
  u32 pad84[3];
  unsigned char* f8c_b;
  unsigned char* f8c_e;
};

// ---- free functions (all cdecl unless noted) --------------------------------
void      Fn_ae9590(CommDlg* d);                    // 0xae9590 (cdecl)
UiCtl*    GetUiCtl();                               // 0xb3d490
CommScreen* GetCommScreen();                        // 0xdd1ca0
u32       GetCurrentGameMode();                     // 0xb5b800
void      HideUTFMenu(int x);                       // 0xb7c810
StarMgr*  StarManager();                            // 0xb3d2a0
NounMgr*  NounManager();                            // 0xb3d300
GameTimeMgr* GameTimeManager();                     // 0xb3d380
Empire*   GetPlayerEmpire();                        // 0x1021300
HomePlanet* GetPlayerHomePlanet();                  // 0x1021370
VtA*      Fn_aed4d0();                              // 0xaed4d0
MsgServer* MessageServer();                         // 0x67dcc0
MsgServer* EAMessagingGetServer();                  // 0x883860
SpeciesMgr* Fn_401090();                            // 0x401090
Obj3d400* Fn_b3d400();                               // 0xb3d400
Sim*      GetUFOSimulator();                        // 0xffbe50
Vec3*     Fn_b6f0c0(u32 v);                         // 0xb6f0c0
void*     Fn_b6e270(void* p);                       // 0xb6e270
void*     Fn_b6e290(void* p);                       // 0xb6e290
void*     Fn_b6e2b0(void* p);                       // 0xb6e2b0

struct HostCls {
  u32 pad[8];
  CommDlg* mCurrent;     // +0x20
  void Fn_aeb7b0(void* out, u32 id, u32 f34, u32 f40);      // 0xaeb7b0
  void Fn_aeb890(void* out, void* civ, void* f20, void* f24);  // 0xaeb890
  void ShowDialog(CommDlg* d);
};

// Replacement for the by-name dialog-civ lookup, repeated all over the original.
static inline Civ* DlgCiv(CommDlg* d) {
  NounManager()->b20750(d->f18);
  Civ* c = d->f28;
  if (!c)
    c = d->f20->GetCivilization();
  return c;
}

// @ 0x00aebe90
void HostCls::ShowDialog(CommDlg* d) {
  Fn_ae9590(d);
  UiCtl* ui = GetUiCtl();
  CommScreen* lay = GetCommScreen();
  u32 mode = GetCurrentGameMode();
  bool isMode05 = (mode == 0x1654c05);
  bool isMode04 = (mode == 0x1654c04);
  HideUTFMenu(1);

  int out88 = 0, out8c = 0;
  cString speaker;
  CStrVec v1 = { 0, 0, 0 };
  void* planet = StarManager()->ba6dc0(d->f34);

  Empire* emp;
  u32* srp;
  u32 sret[8];
  Rec5 rec;
  if (isMode05) {
    emp = StarManager()->GetEmpireByID(d->f18);
    if (emp && emp != GetPlayerEmpire())
      GetPlayerEmpire()->OnWinProcAdd(emp);
    VtA* a = Fn_aed4d0();
    srp = a->s9(sret, emp, GetPlayerEmpire(), planet, d->f40);
  } else {
    emp = 0;
    VtA* a = Fn_aed4d0();
    NounManager()->b20750(d->f18);
    Civ* civ = d->f28;
    if (!civ)
      civ = d->f20->GetCivilization();
    srp = a->s8(sret, civ, d->f20, d->f24);
  }
  rec.w[0] = srp[0]; rec.w[1] = srp[1]; rec.w[2] = srp[2]; rec.w[3] = srp[3]; rec.w[4] = srp[4];

  // Ask the controller for the dialog contents.
  int out[4];
  unsigned char* vec8c = (unsigned char*)&d->f8c_b;   // &d->vec8c (begin,end)
  Fn_aed4d0()->s2(out, d->f38, d->f3c, &rec, &out88, &out8c, &speaker, &v1,
                  &d->f64, vec8c, emp);

  CommDlg* old = mCurrent;
  if (d != old) {
    d->AddRef();
    mCurrent = d;
    if (old)
      old->Release();
  }

  if (out[0] != -1) {
    if (d->f0c == 0) {
      Fn_aeb7b0(out, d->f18, d->f34, d->f40);
    } else if (d->f0c == 1) {
      Civ* civ = DlgCiv(d);
      Fn_aeb890(out, civ, d->f20, d->f24);
    }
  }

  // ---- block A: first show of this dialog -------------------------------
  if (old == 0 || old->Fn_ae9d40(d) != 0) {
    // (old here is the previous dialog pointer)
    GetCommScreen()->Show();
    bool b = isMode05;
    Empire* emp2 = 0;
    if (b)
      emp2 = StarManager()->GetEmpireByID(d->f18);
    if (old == 0)
      GameTimeManager()->IncPauseGate(0x4d02e35);

    Msg m1;
    m1.w[12] = 0x3ac86ad;
    m1.w[0] = (u32)vtbl_BehaviorMessage;
    _InterlockedExchange((volatile long*)&m1.w[1], 0);
    m1.w[0] = (u32)vtbl_MessageBasicRC5;
    m1.w[14] = 0;
    m1.w[2] = d->f0c;
    if (d->f0c == 0) {
      m1.w[4] = (u32)emp2;
    } else {
      m1.w[4] = (u32)DlgCiv(d);
    }
    m1.w[6] = b ? 0 : (u32)d->f20;
    m1.w[8] = b ? 0 : (u32)d->f24;
    MessageServer()->s5(m1.w[12], &m1, 0);
    Fn_401090();

    if (b && d->f0c == 0) {
      if (!emp2)
        emp2 = GetPlayerEmpire();
      Profile* prof = emp2->GetProfile();
      if (prof) {
        u32 f51c = prof->f51c;
        void* scr = lay->GetMainCreatureScreen();
        Vec3 col;
        Vec3* cp = emp2->GetColor(&col);
        void* r = ui->ae7ce0(emp2, 0, d->f34);
        ui->ae8d00((char*)prof + 0x504, r, cp, f51c, 0, (u32)scr);
        void* r1 = lay->dd1e30(emp2, 0);
        Vec3 tmp;
        emp2->GetColor(&tmp);
        u32 buf[6];
        void* rb = lay->dd1f70(buf, emp2, 0);
        ui->ae8820(rb, tmp, 0, r1);
      }
      Profile* prof2 = Fn_401090()->GetProfile(GetPlayerEmpire()->Fn_c30f90());
      if (prof2 && lay->dd22f0()) {
        u32 f51c2 = prof2->f51c;
        int t = GetCommScreen()->dd22f0();
        Vec3 col2;
        Vec3* cp2 = GetPlayerEmpire()->GetColor(&col2);
        void* hp = GetPlayerHomePlanet()->ce6950();
        void* r = ui->ae7ce0(GetPlayerEmpire(), 0, (u32)hp);
        ui->ae8d00((char*)prof2 + 0x504, r, cp2, f51c2, 1, (u32)t);
        void* r1 = lay->dd1e30(GetPlayerEmpire(), 0);
        Vec3 tmp2;
        GetPlayerEmpire()->GetColor(&tmp2);
        u32 buf[6];
        void* rb = lay->dd1f70(buf, GetPlayerEmpire(), 0);
        ui->ae8820(rb, tmp2, 1, r1);
        ui->f91 = 1;
      }
    } else if (isMode04) {
      Profile* ap = Fn_401090()->GetAvatarProfile();
      if (ap) {
        u32 apf = ap->f51c;
        Civ* civ1 = DlgCiv(d);
        Vec3* v1p = Fn_b6f0c0(civ1->f40);
        Civ* civ2 = DlgCiv(d);
        void* apsub = (char*)ap + 0x504;
        void* scr = lay->GetMainCreatureScreen();
        void* r = ui->ae7ce0(0, civ2, 0);
        ui->ae8d00(apsub, r, v1p, apf, 0, (u32)scr);

        Civ* civ3 = DlgCiv(d);
        Civ* civ4 = DlgCiv(d);
        Vec3* v2p = Fn_b6f0c0(civ4->f40);
        void* r1 = lay->dd1e30(0, civ3);
        Vec3 col3 = *v2p;
        Civ* civ5 = DlgCiv(d);
        u32 buf[6];
        void* rb = lay->dd1f70(buf, 0, civ5);
        ui->ae8820(rb, col3, 0, r1);
        if (lay->dd22f0()) {
          u32 apf2 = ap->f51c;
          Civ* ca = 0;
          if (d->f24)
            ca = d->f24->GetCivilization();
          Vec3* v3p = Fn_b6f0c0(ca->f40);
          Civ* cb = 0;
          if (d->f24)
            cb = d->f24->GetCivilization();
          int t = lay->dd22f0();
          void* r2 = ui->ae7ce0(0, cb, 0);
          ui->ae8d00(apsub, r2, v3p, apf2, 1, (u32)t);
        }
      }
    }
    m1.Destruct();
  }

  // ---- block B: avatar-mode civilization casts ----------------------------
  u32 castPlayer = 0, castCiv1 = 0, castCiv3 = 0;
  void* L30 = 0;
  if (isMode04) {
    Civ* civ1 = DlgCiv(d);
    Civ* civ3 = 0;
    if (d->f24)
      civ3 = d->f24->GetCivilization();
    L30 = d->f20;
    if (!L30)
      L30 = civ1;
    lay->dd3a00(L30, d->f24);
    Obj* pc = (Obj*)NounManager()->GetPlayerCivilization();
    if (pc)
      castPlayer = (u32)pc->Cast(0x5593a1a);
    else
      castPlayer = 0;
    if (civ1)
      castCiv1 = (u32)((Obj*)civ1)->Cast(0x5593a1a);
    else
      castCiv1 = 0;
    if (civ3)
      castCiv3 = (u32)((Obj*)civ3)->Cast(0x5593a1a);
    else
      castCiv3 = 0;
  }

  ui->c2e4e0();
  if (Fn_aed4d0()->s5(d->f38, d->f3c)) {
    ui->ae7e10(0, 0, 0, 0);
    ui->f90 = 1;
  } else {
    ui->ae7e10(out88, out8c, 0, 0);
  }
  ui->ae7e10(0, 0, 1, 0);

  // ---- swap the space token translator's fields around the text lookups -----
  u32 sv18 = 0, sv1c = 0, sv48 = 0, sv30 = 0;
  if (isMode05) {
    TokenTr* tr = gpTokenTr;
    sv18 = tr->f18;
    tr->f18 = d->f40;
    tr = gpTokenTr;
    sv1c = tr->f1c;
    tr->f1c = (u32)emp;
    tr = gpTokenTr;
    sv48 = tr->f48;
    tr->f48 = d->f38;
    u32 inv = GetUFOSimulator()->GetPlayerInventory();
    tr = gpTokenTr;
    sv30 = tr->f30;
    tr->f30 = inv;
  }

  GObj* g = gGObj;
  u32 g780 = 0, g790 = 0;
  if (isMode04) {
    g780 = g->cfe780((u32)L30);
    g790 = g->cfe790((u32)d->f24);
  }
  void* ra = Fn_b6e270((void*)castPlayer);
  void* rbv = Fn_b6e290((void*)castCiv1);
  void* rc = Fn_b6e2b0((void*)castCiv3);

  // speaker text -> wstring W0
  WStr w0;
  w0.b = 0; w0.e = 0; w0.c = 0;
  w0.RangeInitialize(speaker.GetText());

  WStrVec v2 = { 0, 0, 0 };
  {
    int n = (int)(v1.e - v1.b);
    for (int i = 0; i < n; ++i) {
      const wchar_t* t = v1.b[i].GetText();
      wsvec_push(&v2, t);
    }
  }

  if (isMode05) {
    gpTokenTr->f18 = sv18;
    gpTokenTr->f1c = sv1c;
    gpTokenTr->f48 = sv48;
    gpTokenTr->f30 = sv30;
  } else if (isMode04) {
    g->cfe780(g780);
    g->cfe790(g790);
  }
  Fn_b6e270(ra);
  Fn_b6e290(rbv);
  Fn_b6e290(rc);

  // behaviour message 2
  Msg m2;
  m2.w[12] = 0;
  m2.w[0] = (u32)vtbl_BehaviorMessage;
  _InterlockedExchange((volatile long*)&m2.w[1], 0);
  m2.w[0] = (u32)vtbl_MessageBasicRC5;
  m2.w[14] = 0;
  m2.w[2] = (u32)d;
  EAMessagingGetServer()->s5(0x35ec3de, &m2, 0);

  // ---- per-response entries (vec at d+0x50, 12 bytes each) ---------------
  int cnt = (int)(d->f54 - d->f50);
  for (int i = 0; i < cnt; ++i) {
    Item12* item = (Item12*)((char*)d->f50 + i * 12);
    cString cs;
    Entry16 entry;
    Fn_aed4d0()->s7(&entry, item->a, item->b, &rec, 0, &cs);
    u32 o18 = gpTokenTr->f18;
    gpTokenTr->f18 = item->c;
    u32 o48 = gpTokenTr->f48;
    gpTokenTr->f48 = item->a;
    wsvec_push(&v2, cs.GetText());
    Entry16Vec* pv = &d->vec78;
    if (pv->e < pv->c) {
      Entry16* pe = pv->e;
      pv->e = pe + 1;
      if (pe)
        *pe = entry;
    } else {
      pv->DoInsertValue(pv->e, &entry);
    }
    gpTokenTr->f18 = o18;
    gpTokenTr->f48 = o48;
  }

  // ---- space info update ------------------------------------------------
  if (isMode05) {
    bool bl = (d->f38 == 0xc8fbf7d7 && d->f3c == 0x2ea8fb98);
    u32 mask[5] = { 2, 0, 0, 0, 0 };
    u32 mrec[5];
    for (int k = 0; k < 5; ++k)
      mrec[k] = rec.w[k];
    for (u32 k = 0; k < 20; k += 4)
      *(u32*)((char*)mrec + k) &= *(u32*)((char*)mask + k);
    bool any = false;
    for (u32 k = 0; k < 5; ++k) {
      if (mrec[k] != 0) { any = true; break; }
    }
    bool isZero = !any;
    unsigned char b50 = 0, b14 = 0, b2c = 0, b18 = 0;
    Fn_aed4d0()->s4(d->f38, d->f3c, &b14, &b50, &b2c, &b18);
    if (v2.b == v2.e && !bl)
      b14 = 1;
    lay->UpdateSpaceInfo(d->f18, d->f34, bl, isZero, b50 != 0, b14 != 0, b2c != 0, b18 != 0);
  }

  // ---- fill the layout ---------------------------------------------------
  int len8c = (int)(d->f8c_e - d->f8c_b);
  int nResp = (int)(v2.e - v2.b);
  lay->SetSpeakerText(w0.b);
  lay->SetResponseCount(nResp);
  {
    WStr* pw = v2.b;
    for (int i = 0; i < nResp; ++i) {
      bool flag;
      if (i >= len8c || d->f8c_b[i] != 0)
        flag = true;
      else
        flag = false;
      lay->dd2c60(i, pw->b, flag);
      ++pw;
    }
  }
  lay->dd32a0();
  lay->dd2d00();
  NounManager()->f67d90(0x56d1872)->c77bf0();
  Fn_b3d400()->e14c10(0);

  // inlined message destructor: release slots flagged in the mask
  m2.w[0] = (u32)vtbl_MessageBasicRC5;
  for (int i = 0; i < 32; ++i) {
    if ((m2.w[14] & (1u << (i & 31))) != 0) {
      Obj* s = ((Obj**)&m2)[2 + 2 * i];
      if (s)
        s->v1();
    }
  }
  m2.w[0] = (u32)vtbl_LocaleChangeMessage;

  // destroy V2 (wstring vector)
  for (WStr* p = v2.b; p < v2.e; ++p)
    ws_free(p);
  if (v2.b && ((int*)v2.b)[-1] != 0)
    ea_delete(v2.b);
  ws_free(&w0);
  // destroy V1 (cString vector)
  {
    cString* p = v1.b;
    for (; p < v1.e; ++p)
      p->~cString();
    if (v1.b && ((int*)v1.b)[-1] != 0)
      ea_delete(v1.b);
  }
}
