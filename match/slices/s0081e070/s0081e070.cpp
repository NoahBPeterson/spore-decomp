// Slice s0081e070 -- Spore UI: UI::PropertyEditor / SP::cPropertyUI.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

extern void Mark1();
extern void Mark2();
extern void Mark3();

// ===========================================================================
// 0081e2b0  UI::PropertyEditor::PropertyEditor  (MATCH)
//   The two writes to +4 are a base-subobject vptr then the derived vptr; the
//   volatile qualifier stops cl from coalescing them.
// ===========================================================================
struct PE {
  void* v0;    // +0
  void* v4;    // +4
  int f8;      // +8
  int fc;      // +0xc
  char b10;    // +0x10
  PE();
};

PE::PE() {
  int z = 0;
  *(void* volatile*)((char*)this + 4) = (void*)&Mark1;
  *(int*)((char*)this + 8) = z;
  *(void* volatile*)this = (void*)&Mark2;
  *(void* volatile*)((char*)this + 4) = (void*)&Mark3;
  *(int*)((char*)this + 0xc) = z;
  *(char*)((char*)this + 0x10) = (char)z;
}

// ===========================================================================
// cPropertyUI (retail layout; the dev-PDB offsets are 0x30 lower from +0xf8 on)
//
// These functions are compiled WITHOUT /EHsc in the original (no unwind frames and
// no cookie around the AutoRefCount temporaries): flags /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Calls through windows, property lists and grids are made through placeholder-slot
// classes (virtual functions padded to the right vtable index); the byte offset of the
// slot is in the comment of each used entry.
// ===========================================================================

#define VT(p, off) ((*(void***)(p))[(off) / 4])
#define VC0(R, p, off) ((R(__thiscall*)(void*))VT(p, off))(p)

extern int g_nodeOfs;                         // 0x01440aec  offset from an intrusive list node to its element
struct PropMgr;
PropMgr* __cdecl GetPropMgr();                // 0x0067de30  SP::PropertyManager
void* __cdecl GetMsgServer();                 // 0x0067dcc0  SP::MessageServer
struct Svc;
Svc* __cdecl GetObjSvc();                     // 0x008de1a0
void* __cdecl Alloc(uint32_t sz, const char* name, int, int, int, int);   // 0x00f473a0  operator new
void __cdecl Dealloc(void* p);                // 0x00f47380  operator delete[] / eastl deallocate

extern wchar_t gEmptyW[];                     // 0x01667bac  eastl empty-string storage
struct WStr {                                 // eastl::basic_string<char16_t> (begin, end, capacity end)
  wchar_t* b;
  wchar_t* e;
  wchar_t* cap;
};
struct WStrE : WStr {
  WStrE() { b = gEmptyW; e = gEmptyW; cap = gEmptyW + 1; }
};
WStr* __cdecl ConvertToString16(WStr* out, const char* s, int n);   // 0x0093c5a0  EA::ConvertToString16Impl

struct IW {
  virtual void AddRef();   // +0x0
  virtual void Release();   // +0x4
  virtual void s8();
  virtual IW* QI(uint32_t iid);   // +0xc
  virtual IW* Slot4();   // +0x10
  virtual void s14(); virtual void s18();
  virtual uint32_t GetID();   // +0x1c
  virtual uint32_t GetFlags();   // +0x20
  virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
  virtual void s34();
  virtual int GetN();   // +0x38
  virtual void SetN(int a, int b);   // +0x3c
  virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
  virtual void s50(); virtual void s54(); virtual void s58(); virtual void s5c();
  virtual void s60(); virtual void s64(); virtual void s68(); virtual void s6c();
  virtual void s70();
  virtual void S74(int a, int b, int c);   // +0x74
  virtual void s78();
  virtual void S7c(int a, int b);   // +0x7c
  virtual void s80(); virtual void s84(); virtual void s88(); virtual void s8c();
  virtual void s90(); virtual void s94(); virtual void s98(); virtual void s9c();
  virtual void sa0(); virtual void sa4(); virtual void sa8(); virtual void sac();
  virtual void sb0(); virtual void sb4(); virtual void sb8(); virtual void sbc();
  virtual void sc0(); virtual void sc4(); virtual void sc8();
  virtual char** Begin(void* t);   // +0xcc
  virtual char** End(void* t);   // +0xd0
  virtual void sd4(); virtual void sd8(); virtual void sdc(); virtual void se0();
  virtual void se4(); virtual void se8(); virtual void sec(); virtual void sf0();
  virtual void sf4(); virtual void sf8(); virtual void sfc(); virtual void s100();
  virtual void AddProc(void* p);   // +0x104
};

struct PL {
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc(); virtual void s10();
  virtual void SetValue(uint32_t id, void* v);   // +0x14
  virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
  virtual void* GetItem(uint32_t id);   // +0x28
};

struct Svc {
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc(); virtual void s10();
  virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20();
  virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
  virtual void s34();
  virtual int Query(void* outVec, void* filter, int z);   // +0x38
  virtual void s3c(); virtual void s40(); virtual void s44(); virtual void s48();
  virtual void s4c(); virtual void s50(); virtual void s54(); virtual void s58();
  virtual void s5c(); virtual void s60(); virtual void s64(); virtual void s68();
  virtual void s6c(); virtual void s70(); virtual void s74(); virtual void s78();
  virtual void GetName(void* item, void* outStr);   // +0x7c
};

struct PropMgr {
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc(); virtual void s10();
  virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20();
  virtual const char* GroupName(uint32_t id);   // +0x24
  virtual void s28();
  virtual void GetPropList(uint32_t inst, uint32_t grp, void** out);   // +0x2c
  virtual void s30(); virtual void s34(); virtual void s38(); virtual void s3c();
  virtual void s40(); virtual void s44(); virtual void s48(); virtual void s4c();
  virtual void s50();
  virtual int GroupCount();   // +0x54
  virtual void GroupIdAt(int i, uint32_t* out);   // +0x58
};

struct Grid {
  virtual void s0(); virtual void s4(); virtual void s8(); virtual void sc(); virtual void s10();
  virtual void s14(); virtual void s18(); virtual void s1c(); virtual void s20();
  virtual void s24(); virtual void s28(); virtual void s2c(); virtual void s30();
  virtual void s34(); virtual void s38(); virtual void s3c(); virtual void s40();
  virtual void s44(); virtual void s48(); virtual void s4c(); virtual void s50();
  virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60();
  virtual void s64(); virtual void s68(); virtual void s6c(); virtual void s70();
  virtual void s74(); virtual void s78(); virtual void s7c(); virtual void s80();
  virtual void s84(); virtual void s88(); virtual void s8c(); virtual void s90();
  virtual void s94(); virtual void s98(); virtual void s9c(); virtual void sa0();
  virtual void sa4(); virtual void sa8(); virtual void sac(); virtual void sb0();
  virtual void sb4(); virtual void sb8(); virtual void sbc(); virtual void sc0();
  virtual void sc4(); virtual void sc8(); virtual void scc(); virtual void sd0();
  virtual void sd4(); virtual void sd8(); virtual void sdc(); virtual void se0();
  virtual void se4(); virtual void se8(); virtual void sec(); virtual void sf0();
  virtual void sf4(); virtual void sf8(); virtual void sfc(); virtual void s100();
  virtual void s104(); virtual void s108(); virtual void s10c(); virtual void s110();
  virtual void s114(); virtual void s118(); virtual void s11c(); virtual void s120();
  virtual void s124(); virtual void s128(); virtual void s12c(); virtual void s130();
  virtual void s134(); virtual void s138(); virtual void s13c(); virtual void s140();
  virtual void s144(); virtual void s148(); virtual void s14c(); virtual void s150();
  virtual void s154(); virtual void s158(); virtual void s15c(); virtual void s160();
  virtual void s164(); virtual void s168();
  virtual void Clear();   // +0x16c
  virtual void s170(); virtual void s174(); virtual void s178(); virtual void s17c();
  virtual void s180(); virtual void s184(); virtual void s188(); virtual void s18c();
  virtual void s190(); virtual void s194(); virtual void s198(); virtual void s19c();
  virtual void s1a0();
  virtual void SetCell(int col, int row, wchar_t* s, int a, int b, int c);   // +0x1a4
  virtual void s1a8(); virtual void s1ac(); virtual void s1b0(); virtual void s1b4();
  virtual void s1b8(); virtual void s1bc();
  virtual void SetCellData(int col, int row, uint32_t v);   // +0x1c0
};

struct ARC {                                  // EA::AutoRefCount<IW>
  IW* p;
  ARC() { p = 0; }
  ~ARC() { if (p) p->Release(); }
  ARC& operator=(IW* n) {
    IW* old = p;
    if (n != old) {
      if (n) n->AddRef();
      p = n;
      if (old) old->Release();
    }
    return *this;
  }
  ARC& operator=(const ARC& o) { return *this = o.p; }
  IW** Out() { if (p) { IW* t = p; p = 0; t->Release(); } return &p; }   // release and hand out the slot
};

struct Variant {                              // EA::Variant (data at +0, flags +0x10, type id +0x12)
  uint32_t f0, f4, f8, fc;
  uint16_t flags, typeId;
  Variant() { flags = 2; typeId = 1; }
  ~Variant() { if (flags & 4) Destruct(false); }
  void __thiscall Assign(const bool* b);      // 0x00422e20  Variant::operator=<bool>
  void __thiscall Destruct(bool b);           // 0x0093db80  Variant::Destruct
};

struct Layout { bool __thiscall Init(const void* a, void* b, bool c, uint32_t d); };   // 0x00812160  cSPUILayout::Init

inline int RoundToInt(float f) {              // cvtss2si, as the original's asm helper
  int r;
  __asm {
    cvtss2si eax, f
    mov r, eax
  }
  return r;
}

extern const char gMsgName[];                 // 0x013f6b3c  allocation tag
extern void* vtRefBaseA22[];                  // 0x013eb90c
extern void* vtDrvBA22[];                     // 0x01452a38
struct Msg {                                  // 0x28-byte BehaviorMessage (RefBaseA22 -> DrvBA22)
  void* vt;
  long rc;
  uint32_t f8, fc, f10, f14, f18, f1c, f20, f24;
};

extern void* vtPropFilter[];                  // 0x013f662c
extern void* vtIMsgHandler[];                 // 0x013eb394
struct PropFilter {                           // stack object handed to Svc::Query; its dtor resets the vptr
  void* vt;
  uint32_t id;
  const void* arg;
};
struct Item12 { uint32_t a, b, c; };
struct Vec12 { Item12* b; Item12* e; Item12* c; };

struct V2 {
  float x, y;
  V2(float a, float b) { x = a; y = b; }
  V2(const V2& o) { x = o.x; y = o.y; }       // user copy ctor: the by-value argument is built in place
};

struct cPropertyUI {
  char pad0[0xc];
  uint32_t mCurrentGroupID;                   // +0xc
  uint32_t mCurrentInstanceID;                // +0x10
  char pad14[0x2c - 0x14];
  float mScrollRatio;                         // +0x2c
  float mScrollHeight;                        // +0x30
  char pad34[0x44 - 0x34];
  Layout mLayout;                             // +0x44
  char pad45[0x5c - 0x45];
  ARC mScrollbar;                             // +0x5c
  ARC mTitleText;                             // +0x60
  ARC mHolderWindow;                          // +0x64  window whose children are the property rows
  ARC mScrollWin;                             // +0x68
  ARC mSpacerWin;                             // +0x6c
  char pad70[0x128 - 0x70];
  ARC mGroupsGrid;                            // +0x128
  ARC mPropsGrid;                             // +0x12c

  void UpdateVisible();                       // 0x0081e070
  void ReloadPropResource();                  // 0x0081e230
  bool Init(const void* a, void* b);          // 0x0081e6c0
  void PopulateGroupsGrid();                  // 0x0081eb10
  void PopulatePropsGrid(const void* x);      // 0x0081ebe0
  void ModifyBool(IW* w, bool multi);         // 0x0081ed10
  void ProcessToggleButton(IW* w);            // 0x0081f020
  ARC FindPropertyUIWindow(uint32_t id);      // 0x0081df10
};

// ===========================================================================
// 0081e070  Hides the property rows that scrolled outside the holder window
//   (complete; 7 diff bytes -- two adjacent stack slots are swapped)
// ===========================================================================
#define NODE_ELEM(it) ((void*)((char*)g_nodeOfs + (int)(it)))
// @ 0x0081e070
void cPropertyUI::UpdateVisible() {
  float half, lo;
  V2 ctr(0, 0);
  void* tmp;
  void* par = VC0(void*, mScrollbar.p, 0x10);
  float* r = VC0(float*, par, 0x34);
  float a = r[1], b = r[3];
  ctr.y = (b + a) * 0.5f;
  ctr.x = (r[0] + r[2]) * 0.5f;
  half = (b - a) * 0.5f;
  char* it = *mHolderWindow.p->Begin(&tmp);
  if (it != *mHolderWindow.p->End(&tmp)) {
    do {
      lo = ctr.y - half + 80.0f;
      float* rr = VC0(float*, NODE_ELEM(it), 0x34);
      float rect[4] = {rr[0], rr[1], rr[2], rr[3]};
      void* p = VC0(void*, NODE_ELEM(it), 0x10);
      float out[2];
      ((void(__thiscall*)(void*, float*, V2))VT(p, 0xc0))(p, out, V2((rect[2] + rect[0]) * 0.5f, (rect[3] + rect[1]) * 0.5f));
      float hh = (rect[3] - rect[1]) * 0.5f;
      if (lo > out[1] + hh)
        ((IW*)NODE_ELEM(it))->S7c(1, 0);
      else if (out[1] - hh > half + ctr.y - 45.0f)
        ((IW*)NODE_ELEM(it))->S7c(1, 0);
      else
        ((IW*)NODE_ELEM(it))->S7c(1, 1);
      it = *(char**)it;
    } while (it != *mHolderWindow.p->End(&tmp));
  }
}

// ===========================================================================
// 0081e230  cPropertyUI::ReloadPropResource -- posts a 0xf62ade BehaviorMessage carrying the
//   current group and instance ids (complete)
// ===========================================================================
// @ 0x0081e230
void cPropertyUI::ReloadPropResource() {
  void* ms = GetMsgServer();
  Msg* m = (Msg*)Alloc(0x28, gMsgName, 0, 0, 0, 0);
  if (m) {
    m->f20 = 0;
    *(void* volatile*)&m->vt = vtRefBaseA22;
    _InterlockedExchange(&m->rc, 0);
    *(void* volatile*)&m->vt = vtDrvBA22;
    VC0(void, m, 4);                          // AddRef
  }
  m->f8 = 0xb1b104;
  m->f10 = mCurrentGroupID;
  m->f18 = mCurrentInstanceID;
  ((void(__thiscall*)(void*, uint32_t, Msg*, int))VT(ms, 0x14))(ms, 0xf62ade, m, 0);   // MessageServer::Post
  VC0(void, m, 8);                            // Release
}

// ===========================================================================
// 0081e6c0  cPropertyUI::Init -- loads the layout, finds the child windows and caches them
//   (complete; register allocation and spill slots differ)
// ===========================================================================
// @ 0x0081e6c0
bool cPropertyUI::Init(const void* a, void* b) {
  bool ok = mLayout.Init(a, b, true, 0x5b598fa);
  if (!ok) return ok;
  ARC root = FindPropertyUIWindow(0x153a7a9);
  IW* rw = root.p;
  if (!rw) return false;
  rw->AddProc(this);
  rw->S7c(1, 0);
  ARC wnd;
  wnd = FindPropertyUIWindow(0x153a7c9);
  mScrollbar = wnd.p ? wnd.p->QI(0x6f0b8ac9) : 0;
  wnd = FindPropertyUIWindow(0x154feb2);
  mTitleText = wnd.p ? wnd.p->QI(0x6f0b8ac9) : 0;
  wnd = FindPropertyUIWindow(0x154fec5);
  mGroupsGrid = wnd.p ? wnd.p->QI(0xaf1ee902) : 0;
  mGroupsGrid.p->S74(1, 1, 1);
  wnd = FindPropertyUIWindow(0x154fed1);
  mPropsGrid = wnd.p ? wnd.p->QI(0xaf1ee902) : 0;
  mPropsGrid.p->S74(1, 1, 1);
  mHolderWindow = FindPropertyUIWindow(0x15b42aa);
  wnd = FindPropertyUIWindow(0x15a490f);
  mScrollWin = wnd.p ? wnd.p->QI(0x2ef0c885) : 0;
  float h = (float)mScrollWin.p->GetN();
  mScrollHeight = h;
  mScrollWin.p->SetN(RoundToInt(h / mScrollRatio), 1);
  wnd = FindPropertyUIWindow(0x15b569f);
  mSpacerWin = wnd.p ? wnd.p->QI(0xf15f4bd) : 0;
  mSpacerWin.p->Slot4()->S7c(1, 0);
  return true;
}

// ===========================================================================
// 0081eb10  cPropertyUI::PopulateGroupsGrid (complete; this/PropMgr swap registers)
// ===========================================================================
// @ 0x0081eb10
void cPropertyUI::PopulateGroupsGrid() {
  PropMgr* pm = GetPropMgr();
  int n = pm->GroupCount();
  for (int i = 0; i < n; i++) {
    uint32_t id;
    pm->GroupIdAt(i, &id);
    const char* name = pm->GroupName(id);
    if (name) {
      WStr s;
      Grid* g = (Grid*)mGroupsGrid.p;
      wchar_t* ws = ConvertToString16(&s, name, -1)->b;
      g->SetCell(0, i, ws, 0, 1, 0);
      if ((s.cap - s.b) > 1 && s.b) Dealloc(s.b);
      ((Grid*)mGroupsGrid.p)->SetCellData(0, i, id);
    }
  }
}

// ===========================================================================
// 0081ebe0  cPropertyUI::PopulatePropsGrid (complete; stack-slot order differs)
// ===========================================================================
// @ 0x0081ebe0
void cPropertyUI::PopulatePropsGrid(const void* x) {
  Svc* ob = GetObjSvc();
  ((Grid*)mPropsGrid.p)->Clear();
  Vec12 vec;
  vec.b = 0;
  vec.e = 0;
  vec.c = 0;
  PropFilter filt;
  filt.vt = vtPropFilter;
  filt.id = 0xb1b104;
  filt.arg = x;
  int cnt = GetObjSvc()->Query(&vec, &filt, 0);
  if (cnt > 0) {
    int row = 0;
    int idx = 0;
    do {
      WStrE s;
      ob->GetName((char*)vec.b + idx, &s);
      ((Grid*)mPropsGrid.p)->SetCell(0, row, s.b, 0, 1, 0);
      ((Grid*)mPropsGrid.p)->SetCellData(0, row, *(uint32_t*)((char*)vec.b + idx));
      row++;
      if ((s.cap - s.b) > 1 && s.b) Dealloc(s.b);
      idx += 12;
    } while (--cnt);
  }
  *(void* volatile*)&filt.vt = vtIMsgHandler;     // ~PropFilter resets the vptr
  if (vec.b && ((int*)vec.b)[-1]) Dealloc(vec.b);
}

// ===========================================================================
// 0081ed10  cPropertyUI::ModifyBool -- pushes the toggle state of one button (multi == false) or of
//   every child button (multi == true) into the property's bool value (complete)
// ===========================================================================
// @ 0x0081ed10
void cPropertyUI::ModifyBool(IW* w, bool multi) {
  ARC btn;
  ARC prop;
  ARC cur;
  PropMgr* pm = GetPropMgr();
  pm->GetPropList(mCurrentInstanceID, mCurrentGroupID, (void**)prop.Out());
  if (!multi) {
    btn = w ? w->QI(0x8ed27e7a) : 0;
    bool bv = (btn.p->GetFlags() & 4) != 0;
    Variant v;
    v.Assign(&bv);
    ((PL*)prop.p)->SetValue(w->GetID(), &v);
  } else {
    Variant* iv = (Variant*)((PL*)prop.p)->GetItem(w->GetID());
    bool* base = (iv->flags & 0x30) ? *(bool**)iv : (iv->typeId ? (bool*)iv : 0);
    bool* out = base;
    void* t1;
    void* t2;
    char* n = *w->Begin(&t1);
    if (n != *w->End(&t2)) {
      do {
        IW* c = (IW*)NODE_ELEM(n);
        if (c->GetID()) {
          cur = (IW*)NODE_ELEM(n);
          btn = cur.p ? cur.p->QI(0x8ed27e7a) : 0;
          *out++ = (btn.p->GetFlags() & 4) == 4;
        }
        n = *(char**)n;
      } while (n != *w->End(&t2));
    }
    Variant v;
    v.f0 = (uint32_t)base;
    v.f4 = 1;
    v.f8 = 1;
    v.flags = 0x22;
    v.typeId = 1;
    ((PL*)prop.p)->SetValue(w->GetID(), &v);
  }
  ReloadPropResource();
}

// ===========================================================================
// 0081f020  cPropertyUI::ProcessToggleButton (complete; register allocation differs)
// ===========================================================================
// @ 0x0081f020
void cPropertyUI::ProcessToggleButton(IW* w) {
  IW* t = w;
  IW* b = mHolderWindow.p;
  if (t->Slot4() != b) t = w->Slot4();
  uint32_t id = t->GetID();
  ARC prop;
  PropMgr* pm = GetPropMgr();
  pm->GetPropList(mCurrentInstanceID, mCurrentGroupID, (void**)prop.Out());
  uint16_t ty = ((Variant*)((PL*)prop.p)->GetItem(id))->typeId;
  if (ty == 1) ModifyBool(w, false);
  else if ((uint32_t)ty == 0x80000001) ModifyBool(w->Slot4(), true);
}
