// SP::cSPUIAssetVerbs -- the verb buttons of the Sporepedia asset browser.
//
// The class body comes from src/game/include/SP/cSPUIAssetVerbs.h.  The canonical EA::UTFWin::IWindow
// and cSPUILayout headers declare no virtual slots, so the vtable helpers at the top spell the three
// slots this module calls (AddRef +0, Release +4, the destructor +8).

// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13ffc00[];

#include "game/types.h"
#include "SP/cSPUIAssetVerbs.h"
#include "SP/cSPUIAssetView.h"
#include "cSPUILayout.h"
#include <intrin.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void* __fastcall cSPUILayout_Ctor(void* self);
extern "C" void* __cdecl EA_operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void __cdecl RemoveHandler5(void* a, void* b, void* c, void* d, void* e);
extern "C" void __cdecl SPUIHelpers_SetWindowAreaToParent(void* w);
extern int gVtA, gVtB, gVtC, gVtD, gVtE, gVtF, gVtG, gVtH, gVtI;

inline void  vc0(void* p, int off) { ((void(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc1(void* p, int off, int a) { ((void(__thiscall*)(void*, int))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline void  vc2(void* p, int off, int a, int b) { ((void(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline int   vcr0(void* p, int off) { return ((int(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp0(void* p, int off) { return ((void*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void* vcp2(void* p, int off, int a, int b) { return ((void*(__thiscall*)(void*, int, int))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline void  vc1p(void* p, int off, void* a) { ((void(__thiscall*)(void*, void*))(*(void**)((char*)*(void**)p + off)))(p, a); }
inline float* vcfp(void* p, int off) { return ((float*(__thiscall*)(void*))(*(void**)((char*)*(void**)p + off)))(p); }
inline void  vc2f(void* p, int off, float a, float b) { ((void(__thiscall*)(void*, float, float))(*(void**)((char*)*(void**)p + off)))(p, a, b); }
inline void AssignWin(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 0);
        *slot = p;
        if (old) vc0(old, 4);
    }
}
inline void AssignLayout(void** slot, void* p) {
    void* old = *slot;
    if (p != old) {
        if (p) vc0(p, 4);
        *slot = p;
        if (old) vc0(old, 8);
    }
}
struct cSPUILayout_s0065_6310 {
    void* vf0;  // +0
    void* vf1;  // +4
    void* vf2;  // +8
    void* FindWindowByID(int id, int flag);  // 0x008105b0 (cSPUILayout::FindWindowByID)
    void  Shutdown(int flag);  // 0x00811ad0 (cSPUILayout::Shutdown)
    void  SetParentWin(void* parent, int a, int id);  // 0x008121b0 (cSPUILayout::SetParentWin)
    void  SetReloadCallback(void* fn, void* self);  // 0x00810090 (cSPUILayout::SetReloadCallback)
    void  Init(void* key, int a, int id);  // 0x008120d0 (cSPUILayout::Init)
};
struct cSPUIAssetVerbs {
    void* vf0;         // 0x00
    void* vf1;         // 0x04
    void* vf2;         // 0x08
    int   mf0c;        // 0x0c
    bool  mIsVisible;  // 0x10
    void* mLayout;     // 0x14
    void* mWinParent;  // 0x18
    void* mWinRoot;    // 0x1c
    void* mWin3;       // 0x20
    void* mWin4;       // 0x24
    void* mWin5;       // 0x28
    void* mWin6;       // 0x2c
    void* mWin7;       // 0x30
    void* mWin8;       // 0x34
    int   mAutoh[5];   // 0x38..0x4b  (AutoHandler)
    float mVec[4];     // 0x4c..0x5b

    void Shutdown();
    bool IsVerb(int idx);
    void Update(void* p);
    void UpdatePos(void* p);
    void SetVerbButtonEnabled(unsigned int idx);
    void Init(void* parent);
};

// ---- items of slice s00656c70 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern uint32_t g_ControlIDs[6];
struct IWindow {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
  virtual int GetControlID();            // 0x38
virtual void v0f();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v1a();
  virtual void SetControlID(int id);     // 0x6c
virtual void v1c();
virtual void v1d();
virtual void v1e();
  virtual void SetFlag(int flag, bool value); // 0x7c
};
struct ResKey { int a; uint32_t typeID; };
struct IItem {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
  virtual void v08();
  virtual int Get24();                    // 0x24
virtual void v0a();
virtual void v0b();
virtual void v0c();
virtual void v0d();
virtual void v0e();
virtual void v0f();
  virtual ResKey* GetKey();               // 0x40
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
  virtual bool Is60();                    // 0x60
  virtual void v19();
  virtual bool Is68();                    // 0x68
  virtual void v1b();
  virtual bool Is70();                    // 0x70
virtual void v1d();
virtual void v1e();
  virtual bool Is7c();                    // 0x7c
  virtual bool Is80();                    // 0x80
};
struct ItemVec { IItem** mpBegin; IItem** mpEnd; IItem** mpCap; int mAllocator[2];
  uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
  bool empty() const { return mpBegin == mpEnd; }
  void insert(IItem** pos, IItem* const& v);
};
struct Params { uint32_t id; bool f0, f1, f2; int index; bool f3;
  Params() : id(0), f0(false), f1(false), f2(false), index(1), f3(false) {} };
struct WindowMgr { IWindow* FindWindowByID(uint32_t id, bool recursive); };
struct Game { int Get645d90(); int Get6447b0(); bool Is6448e0(); };
Game* GetGame();
bool FUN_004bbe20(uint32_t type, int);
int FUN_00432f10(int);
void FUN_00806bf0(int);
void EASTL_allocator_deallocate(void* p); // 0x00f47380
struct Panel {
  char pad0[0x10];
  bool m10;
  char pad11[3];
  WindowMgr* m14;
  char pad18[4];
  IWindow* m1c;
  char pad20[4];
  IWindow* m24;
  char pad28[4];
  IWindow* m2c;
  int m30;
  void FUN_00656510(Params* p);
  void FUN_00656770(Params* p);
  void FUN_00656830(int i);
  __forceinline void ShowPair(uint32_t a, uint32_t b) {
    IWindow* w1 = m14->FindWindowByID(a, true);
    IWindow* w2 = m14->FindWindowByID(b, true);
    if (w1) w1->SetFlag(1, true);
    if (w2) w2->SetFlag(0x10, true);
  }
  inline void Link(bool v) {
    IWindow* w1 = m14->FindWindowByID(0x668ad90, true);
    IWindow* w2 = m14->FindWindowByID(0x668ada0, true);
    if (w1 && w2) {
      w1->SetFlag(1, !v);
      w2->SetControlID(w1->GetControlID());
      w2->SetFlag(1, v);
    }
  }
  void Update(bool show, const Params* p, ItemVec* items);
  void Update(bool show, const Params* p, IItem* item);
};
// ---- items of slice s00656c70 end

// @ 0x00656410
void __fastcall cSPUIAssetVerbs_dtor(cSPUIAssetVerbs* self)
{
    self->vf0 = &gVtC;
    self->vf1 = &gVtD;
    self->vf2 = &gVtE;
    _ReadWriteBarrier();
    int h0 = self->mAutoh[0];
    if (h0) {
        self->mAutoh[0] = 0;
        RemoveHandler5((void*)h0, (void*)self->mAutoh[1], (void*)self->mAutoh[2], (void*)self->mAutoh[3], (void*)self->mAutoh[4]);
    }
    if (self->mWin8) vc0(self->mWin8, 4);
    if (self->mWin7) vc0(self->mWin7, 4);
    if (self->mWin6) vc0(self->mWin6, 4);
    if (self->mWin5) vc0(self->mWin5, 4);
    if (self->mWin4) vc0(self->mWin4, 4);
    if (self->mWin3) vc0(self->mWin3, 4);
    if (self->mWinRoot) vc0(self->mWinRoot, 4);
    if (self->mWinParent) vc0(self->mWinParent, 4);
    if (self->mLayout) vc0(self->mLayout, 8);
    self->vf2 = &gVtF;
    self->vf1 = &gVtG;
    self->vf0 = &gVtH;
}

// @ 0x00656510
void cSPUIAssetVerbs::UpdatePos(void* p)
{
    float w = 40.0f;
    float x = 0.0f;
    float y = 0.0f;
    if (mWin3) {
        float* r = vcfp(mWin3, 0x38);
        w = r[2] - r[0];
        x = vcfp(mWin3, 0x38)[0];
        y = vcfp(mWin3, 0x38)[1];
    }
    int n = 0;
    int* ids1 = (int*)0x13ffc00;
    int* ids2 = (int*)0x13ffc18;
    for (int i = 0; i < 6; ++i) {
        void* w1 = ((cSPUILayout_s0065_6310*)mLayout)->FindWindowByID(ids1[i], 1);
        void* w2 = ((cSPUILayout_s0065_6310*)mLayout)->FindWindowByID(ids2[i], 1);
        if (w1) vc2f(w1, 0x70, x, y);
        if (w2) vc2f(w2, 0x70, x, y);
        bool add;
        if (i == 5) add = (*(int*)p == 0xad0e52);
        else if (i == 3) add = (*(char*)((char*)p + 0xc) != 0);
        else add = true;
        if (add) { x += w; ++n; }
    }
    if (mWinRoot && mWin3) {
        float v[4];
        v[0] = mVec[0];
        v[1] = mVec[1];
        v[2] = mVec[2];
        v[3] = mVec[3];
        float* rect = vcfp(mWin3, 0x38);
        float r = rect[2] - rect[0];
        v[0] = v[0] - r * (float)(n - 5);
        vc1p(mWinRoot, 0x6c, v);
    }
    if (mWin6 && mWin5) {
        float px = vcfp(mWin5, 0x38)[0];
        float py = vcfp(mWin5, 0x38)[1];
        vc2f(mWin6, 0x70, px, py);
    }
}

// @ 0x006566f0
void cSPUIAssetVerbs::Shutdown()
{
    if (mLayout) {
        ((cSPUILayout_s0065_6310*)mLayout)->Shutdown(1);
        AssignLayout(&mLayout, 0);
    }
    int h0 = mAutoh[0];
    if (h0) {
        mAutoh[0] = 0;
        RemoveHandler5((void*)h0, (void*)mAutoh[1], (void*)mAutoh[2], (void*)mAutoh[3], (void*)mAutoh[4]);
    }
}

// @ 0x00656740
bool cSPUIAssetVerbs::IsVerb(int idx)
{
    void* w = ((cSPUILayout_s0065_6310*)mLayout)->FindWindowByID(((int*)g_13ffc00)[idx], 1);
    if (w) return (vcr0(w, 0x28) & 1);
    return false;
}

// @ 0x00656770
void SP::cSPUIAssetVerbs::Update(unsigned int p)
{
    int* ids1 = (int*)0x13ffc00;
    int* ids2 = (int*)0x13ffc18;
    for (int i = 0; i < 6; ++i) {
        void* w1 = ((cSPUILayout*)mLayout.mpObject)->FindWindowByID(ids1[i], 1);
        void* w2 = ((cSPUILayout*)mLayout.mpObject)->FindWindowByID(ids2[i], 1);
        if (w1) vc2(w1, 0x7c, 1, 0);
        if (w2) {
            if (i == 5) {
                if (*(int*)p == 0xad0e52) vc2(w2, 0x7c, 1, 1);
                else vc2(w2, 0x7c, 1, 0);
            }
            else if (i == 3) {
                if (*(char*)((char*)p + 0xc)) vc2(w2, 0x7c, 1, 1);
                else vc2(w2, 0x7c, 1, 0);
            }
            else {
                vc2(w2, 0x7c, 1, 1);
            }
            vc2(w2, 0x7c, 0x10, 0);
        }
    }
    if (mAutoMsgHandler.mpServer) vc2(mAutoMsgHandler.mpServer, 0x7c, 1, 0);
    if (mAutoMsgHandler.mpIdArray) vc2(mAutoMsgHandler.mpIdArray, 0x7c, 1, 0);
}

// The parent window of the verbs, reached through the slots the module calls.  The canonical
// EA::UTFWin::IWindow header declares no virtual slots, so only FindWindow (vtable +0xf0) is spelled.
struct IWinParent {
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual void slot55();
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual void slot59();
    virtual void* FindWindow(int id, int flag);  // vtable +0xf0
};

// @ 0x00656890
void __cdecl ReloadCallback(cSPUIAssetVerbs* self, void* layout, bool reload)
{
    if (!reload) {
        AssignWin(&self->mWin7, 0);
        AssignWin(&self->mWinRoot, 0);
        AssignWin(&self->mWin3, 0);
        AssignWin(&self->mWin4, 0);
        AssignWin(&self->mWin6, 0);
        AssignWin(&self->mWin5, 0);
        return;
    }
    void* w = ((cSPUILayout_s0065_6310*)self->mLayout)->FindWindowByID(0x149371c4, 1);
    AssignWin(&self->mWin7, w);
    if (self->mWinParent) {
        void* w1 = ((IWinParent*)self->mWinParent)->FindWindow(0x67a3600, 1);
        AssignWin(&self->mWinRoot, w1);
        if (self->mWinRoot) {
            float* r = vcfp(self->mWinRoot, 0x38);
            self->mVec[0] = r[0];
            self->mVec[1] = r[1];
            self->mVec[2] = r[2];
            self->mVec[3] = r[3];
            vc1(self->mWinParent, 0xdc, (int)self->mWin7);
            vc1(self->mWinRoot, 0xd8, (int)self->mWin7);
        }
        void* w2 = ((IWinParent*)self->mWinParent)->FindWindow(0x667bf68, 1);
        AssignWin(&self->mWin3, w2);
        void* w3 = ((IWinParent*)self->mWinParent)->FindWindow(0x67a3238, 1);
        AssignWin(&self->mWin4, w3);
        void* w4 = ((cSPUILayout_s0065_6310*)self->mLayout)->FindWindowByID(0x67a32d0, 1);
        AssignWin(&self->mWin6, w4);
        if (self->mWin6) {
            void* inner = vcp0(self->mWin6, 0x10);
            vc1(inner, 0xdc, (int)self->mWin6);
            if (self->mWin4) vc1(self->mWin4, 0xd8, (int)self->mWin6);
        }
        void* w5 = ((IWinParent*)self->mWinParent)->FindWindow(0x67a36c0, 1);
        AssignWin(&self->mWin5, w5);
    }
    if (self->mWin7) SPUIHelpers_SetWindowAreaToParent(self->mWin7);
}

// @ 0x00656b00
cSPUIAssetVerbs* __fastcall cSPUIAssetVerbs_ctor(cSPUIAssetVerbs* self)
{
    *(void* volatile*)&self->vf1 = &gVtA;
    *(void* volatile*)&self->vf2 = &gVtB;
    _ReadWriteBarrier();
    self->mf0c = 0;
    self->vf0 = &gVtC;
    self->vf1 = &gVtD;
    self->vf2 = &gVtE;
    self->mIsVisible = false;
    self->mLayout = 0;
    self->mWinParent = 0;
    self->mWinRoot = 0;
    self->mWin3 = 0;
    self->mWin4 = 0;
    self->mWin5 = 0;
    self->mWin6 = 0;
    self->mWin7 = 0;
    self->mWin8 = 0;
    self->mAutoh[0] = 0;
    self->mAutoh[1] = 0;
    self->mAutoh[2] = 0;
    self->mAutoh[3] = 0;
    self->mAutoh[4] = 0;
    return self;
}

// @ 0x00656b80
void cSPUIAssetVerbs::Init(void* parent)
{
    AssignWin(&mWinParent, parent);
    void* p = EA_operator_new(0x18, "Sporepedia", 0, 0, 0, 0);
    void* layout;
    if (p) layout = cSPUILayout_Ctor(p);
    else layout = 0;
    AssignLayout(&mLayout, layout);
    int g = *(int*)0x15261e4;
    int key[3];
    key[0] = 0xba5ee251;
    key[1] = 0x510a95b;
    key[2] = g;
    ((cSPUILayout_s0065_6310*)mLayout)->Init(key, 1, 0x5b598fa);
    ((cSPUILayout_s0065_6310*)mLayout)->SetParentWin(mWinParent, 1, 0x5b598fa);
    ((cSPUILayout_s0065_6310*)mLayout)->SetReloadCallback((void*)&ReloadCallback, this);
    ReloadCallback(this, mLayout, true);
}

// @ 0x00656c70
void Panel::Update(bool show, const Params* p, ItemVec* items)
{
  Params s;
  if (p) s = *p;
  uint32_t id = s.id;
  bool f1 = s.f1;
  m10 = show;
  if (m1c) {
    m1c->SetFlag(1, show);
    FUN_00806bf0(m30);
  }
  FUN_00656510(&s);
  FUN_00656770(&s);
  if (m24 && m2c && s.f0) {
    m24->SetFlag(1, true);
    m2c->SetFlag(1, true);
  }
  if (show && !items->empty()) {
    int idx = 6;
    if (id) {
      for (int i = 0; i < 6; i++) {
        if (g_ControlIDs[i] == id) {
          idx = i;
          FUN_00656830(i);
        }
      }
    }
    bool all68 = true, all70 = true, all7c = true, all80 = true;
    bool e = false, g = false;
    for (uint32_t i = 0; i < items->size(); i++) {
      IItem* it = items->mpBegin[i];
      if (it->Is68()) {
        if (!it->Is70()) all70 = false;
      } else {
        all68 = false;
      }
      if (!it->Is7c()) all7c = false;
      if (!it->Is80()) all80 = false;
    }
    if (items->size() == 1) {
      IItem* it = items->mpBegin[0];
      e = f1 && it->Is60();
      if (FUN_004bbe20(it->GetKey()->typeID, 0)) {
        int x = GetGame()->Get645d90();
        int y = GetGame()->Get6447b0();
        if (x == -1) x = FUN_00432f10(it->Get24());
        g = s.f3 && x != y && it->Is60() && it->GetKey()->typeID == 0x2b978c46;
      }
    } else if (!all70) {
      goto other;
    }
    if (all68) {
      if (all70) {
        Link(true);
      } else {
        ShowPair(0x54acb9f5, 0x668ad90);
        Link(false);
      }
    } else {
    other:
      Link(false);
    }
    if (all7c && GetGame() && !GetGame()->Is6448e0()) ShowPair(0x54acb9f6, 0x667d118);
    if (all80) ShowPair(0x54acb9e0, 0x668adb0);
    if (e) ShowPair(0x54acb9f1, 0x667d120);
    if (g) ShowPair(0x54acb9f2, 0x7a43648);
    if (s.index >= 0 && items->size() > (uint32_t)s.index && idx != 6)
    {
      WindowMgr* m = m14;
      m->FindWindowByID(g_ControlIDs[idx], true)->SetFlag(1, false);
    }
  }
}

// @ 0x006571e0
void Panel::Update(bool show, const Params* p, IItem* item)
{
  IItem** b = 0;
  ItemVec v;
  v.mpBegin = b;
  v.mpEnd = b;
  v.mpCap = b;
  if (item) {
    v.insert(v.mpEnd, item);
    b = v.mpBegin;
  }
  Update(show, p, &v);
  if (b && ((int*)b)[-1]) EASTL_allocator_deallocate(b);
}
