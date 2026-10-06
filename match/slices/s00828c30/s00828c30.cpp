// Slice s00828c30 -- UI/render helper thunks around cSPUIPropertyLayout.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ===========================================================================
// 008290e0  conditional virtual-dispatch thunk (MATCH)
// ===========================================================================
struct C25c {
  char pad0[0x10];
  void* m10;          // +0x10
  char pad14[0x14];   // +0x14 .. +0x27
  void* m28;          // +0x28
  void Do(int arg);
};
void C25c::Do(int arg) {
  if (m10) {
    ((void(__thiscall*)(void*, int))(*(void***)m10)[2])(m10, arg);
  } else {
    void* o = m28;
    if (o) ((void(__thiscall*)(void*, int))(*(void***)o)[0x6c / 4])(o, arg);
  }
}

// ===========================================================================
// 00828df0  three virtual calls guarded by (m10 && mObj)
//   complete but not byte-exact: cl emits `cmp [mem],0; reload` for the null
//   test instead of the original `mov ecx,[mem]; test ecx,ecx`.
// ===========================================================================
struct IThing {
  virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
  virtual void v4(); virtual void v5(int, int); virtual void v6();
};
struct C25b {
  char pad0[0xc];
  IThing* mObj;       // +0xc
  int m10;            // +0x10
  void Do(int arg);
};
void C25b::Do(int arg) {
  if (m10 && mObj) {
    mObj->v4();
    mObj->v5(arg, m10);
    mObj->v6();
  }
}

// ===========================================================================
// Remaining functions of the slice (complete, compiled equivalents)
// ===========================================================================
struct Pt {
  float x, y;
  Pt() {}
  Pt(float a, float b) : x(a), y(b) {}
  Pt(const Pt& o) : x(o.x), y(o.y) {}
};
struct Rect {
  float l, t, r, b;
  Rect() {}
  Rect(float a, float b_, float c, float d) : l(a), t(b_), r(c), b(d) {}
  Rect(const Rect& o) : l(o.l), t(o.t), r(o.r), b(o.b) {}
  Rect& operator=(const Rect& o) { l = o.l; t = o.t; r = o.r; b = o.b; return *this; }
};
#define TL(rc) (*(Pt*)&(rc).l)
#define BR(rc) (*(Pt*)&(rc).r)
class IWin;

class IRef {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
};

class IProv {
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual IWin* GetWindow();  // slot 19 +0x4c
};

class IText {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void Measure(Rect* out, int a, int b);  // slot 8 +0x20
};

class IParent {
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual void s18();
    virtual void Place(int a, IWin* w);  // slot 19 +0x4c
};

class IWin {
public:
    virtual void AddRef();  // slot 0 +0x0
    virtual void Release();  // slot 1 +0x4
    virtual void s2();
    virtual IText* QueryText(unsigned id);  // slot 3 +0xc
    virtual IWin* GetParent();  // slot 4 +0x10
    virtual IParent* GetContainer();  // slot 5 +0x14
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual unsigned GetFlags();  // slot 10 +0x28
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual Rect* GetArea();  // slot 14 +0x38
    virtual void s15();
    virtual int GetStyleId();  // slot 16 +0x40
    virtual void s17();
    virtual void s18();
    virtual void s19();
    virtual void s20();
    virtual void s21();
    virtual void s22();
    virtual void s23();
    virtual void s24();
    virtual void s25();
    virtual void s26();
    virtual void SetArea(const Rect* r);  // slot 27 +0x6c
    virtual void s28();
    virtual void s29();
    virtual void s30();
    virtual void s31();
    virtual void s32();
    virtual void s33();
    virtual void s34();
    virtual void s35();
    virtual void s36();
    virtual void s37();
    virtual void s38();
    virtual void s39();
    virtual void s40();
    virtual void s41();
    virtual void s42();
    virtual void s43();
    virtual void s44();
    virtual void s45();
    virtual void s46();
    virtual void s47();
    virtual Pt* ToScreen(Pt* out, Pt p);  // slot 48 +0xc0
    virtual Pt* ToLocal(Pt* out, Pt p);  // slot 49 +0xc4
    virtual void s50();
    virtual void s51();
    virtual void s52();
    virtual void s53();
    virtual void Detach(IWin* w);  // slot 54 +0xd8
    virtual void Attach(IWin* w);  // slot 55 +0xdc
};

class IRectCb {
public:
    virtual bool IsDragging();  // slot 0 +0x0
    virtual void GetRect(Rect* out);  // slot 1 +0x4
    virtual void SetRect(const Rect* r);  // slot 2 +0x8
};

class IWinMgr {
public:
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();
    virtual void s15();
    virtual void s16();
    virtual void s17();
    virtual IWin* GetFocus(int a);  // slot 18 +0x48
};


template <class T> class AutoRef {
 public:
  T* p;
  AutoRef() : p(0) {}
  AutoRef(T* n) : p(n) { if (n) n->AddRef(); }
  ~AutoRef() { if (p) p->Release(); }
  AutoRef& operator=(T* n) {
    T* old = p;
    if (n != old) {
      if (n) n->AddRef();
      p = n;
      if (old) old->Release();
    }
    return *this;
  }
};
// AutoRefCount<IWinText>::operator= lives out of line in the original (0x00b5f950)
class AutoRefWin {
 public:
  IWin* p;
  AutoRefWin() : p(0) {}
  ~AutoRefWin();
  AutoRefWin& operator=(IWin* n);
};
inline AutoRefWin::~AutoRefWin() {
  if (p) ((IRef*)p)->Release();
}

struct Variant {
  char data[0x10];
  unsigned short mFlags;
  unsigned short mTypeId;
  Variant() : mFlags(0), mTypeId(0) {}
  ~Variant() { if (mFlags & 4) Destruct(0); }
  Variant& operator=(const Variant& o);   // 0x00542b80
  void Destruct(int);                     // 0x0093db80
};
struct VarSlot {
  AutoRef<IRef> p;
  Variant v;
  unsigned extra;
};

// ---- 0x00828c30: sorted-vector map insert --------------------------------------
struct MapNode {
  unsigned key;
  IRef* p;
  Variant v;
  unsigned flags;
};
struct MapVec {
  MapNode** mBegin;   // +0x2c
  MapNode** mEnd;     // +0x30
  MapNode** Insert(MapNode** pos, unsigned* key);   // 0x00828b80
};
class cEntryMap {
 public:
  char pad0[0x2c];
  MapVec mVec;        // +0x2c
  char pad34[0x40 - 0x34];
  bool mFlag;         // +0x40
  bool Set(unsigned key, const Variant* value, unsigned flags, IRef* ref);
};
MapNode** LowerBound(MapNode** first, MapNode** last, unsigned* key, bool flag);   // 0x00d01210

// @ 0x00828c30
bool cEntryMap::Set(unsigned key, const Variant* value, unsigned flags, IRef* ref) {
  MapNode** it;
  {
    VarSlot a;
    VarSlot b;
    b.v = a.v;
    b.extra = a.extra;
    unsigned k = key;
    it = LowerBound(mVec.mBegin, mVec.mEnd, &k, mFlag);
    if (it == mVec.mEnd || k < (*it)->key)
      it = mVec.Insert(it, &k);
  }
  MapNode* n = (MapNode*)it;
  n->v = *value;
  n->flags = flags | 4;
  IRef* old = n->p;
  if (ref != old) {
    if (ref) ref->AddRef();
    n->p = ref;
    if (old) old->Release();
  }
  return true;
}

// ---- wrapper object created by Begin2D (0x00828d40 / 0x00828e30 / 0x00828ea0 / 0x00828ef0) -----
class IResBase {
 public:
  virtual ~IResBase() {}
  virtual void rb1();
};
class IRC {
 public:
  IRC() : mnRefCount(0) {}
  virtual ~IRC() {}
  virtual void rc1();
  int mnRefCount;
};
class cRender2D {
 public:
  IRef* F9557c0();   // 0x009557c0
};
class RenderContext {
 public:
  void End2D();                 // 0x0095bb20
  cRender2D* Begin2D(IText* r);  // 0x0095bc10
};
IWin* F951d50();   // 0x00951d50

class cWrap : public IResBase, public IRC {
 public:
  AutoRef<IText> mC;     // +0xc
  AutoRef<IRef> m10;     // +0x10
  cRender2D* m14;        // +0x14
  cWrap(IProv* prov, IRef* ref);
  static void operator delete(void* p);
  void* operator new(unsigned sz, const void* name, int a, int b, int c, int d);
};
extern char g_wrapAllocName[];   // 0x013f6b3c

// @ 0x00828d40
cWrap::cWrap(IProv* prov, IRef* ref) : m10(ref) {
  m14 = 0;
  IWin* w = prov->GetWindow();
  if (!w) w = F951d50();
  IText* t;
  if (w) t = w->QueryText(0x5234b49);
  else t = 0;
  mC = t;
}

// @ 0x00828e30
cRender2D* __cdecl BeginRender(RenderContext* ctx, IProv* prov, cWrap** out) {
  ctx->End2D();
  cWrap* w = new (g_wrapAllocName, 0, 0, 0, 0) cWrap(prov, 0);
  *out = w;
  ((IRef*)(*out))->AddRef();
  (*out)->m14 = ctx->Begin2D((*out)->mC.p);
  return (*out)->m14;
}

// @ 0x00828ea0 (cWrap deleting destructor, inline above)

// @ 0x00828ef0
void __cdecl EndRender(RenderContext* ctx, cWrap* w) {
  if (w && w->m14) {
    IRef* r = w->m14->F9557c0();
    w->m10 = r;
    w->m14 = 0;
  }
  ctx->End2D();
}

// ---- the property layout object ------------------------------------------------------
class RefVec {
 public:
  IRef** mpBegin;
  IRef** mpEnd;
  IRef** mpCap;
  RefVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
  ~RefVec();                                              // 0x004b5440
  IRef** DoAllocateAndCopy(unsigned n, IRef** f, IRef** l);   // 0x00829a10
  void DoDestroy(IRef** f, IRef** l);                     // 0x00b007f0
  RefVec& operator=(const RefVec& x);
};
class cLayoutBase {
 public:
  cLayoutBase() : m4(0) {}
  virtual ~cLayoutBase() {}
  int m4;
};
class cPropLayout : public cLayoutBase {
 public:
  bool mBusy;          // +8
  bool mMoved;         // +9
  bool mPending;       // +0xa
  float mOffset;       // +0xc
  IRectCb* m10;        // +0x10
  RefVec mKids;        // +0x14
  char pad20[0x28 - 0x20];
  AutoRef<IWin> m28;   // +0x28
  AutoRef<IWin> m2c;   // +0x2c
  AutoRefWin m30;      // +0x30
  cPropLayout();
  static void operator delete(void* p);
  float MeasureOverflow();
  Rect* GetRect(Rect* out);
  Rect* GetRectLocal(Rect* out);
  void SetRect2(const Rect* in, bool flag);
  void ApplyRect(const Rect* r);   // 0x008290e0
  void UpdateLayout(bool active);
  void Tick();
};

// @ 0x00829770
cPropLayout::cPropLayout() : mBusy(false), mMoved(false), mPending(false), mOffset(0.0f), m10(0) {}

// @ 0x00829a70 (cPropLayout deleting destructor, inline above)

// helpers (cdecl)
Rect* __cdecl GetWindowArea(Rect* out, IWin* w);                      // 0x00805ef0
void __cdecl GetBoundingScreenRect(Rect* out, IWin* w, int a);        // 0x00808d20
void __cdecl UpdateMouseFocus(int a);                                 // 0x00804f50
bool __cdecl FUN_00805150(IWin* w, IWin* x);                          // 0x00805150
IWinMgr* __cdecl GetWindowManager();                                  // 0x0067caa0
class Style { public: char pad[0x254]; int mMode; };
class StyleManager { public: Style* GetStyle(int id, int a); };       // 0x00894670
StyleManager* __cdecl GetStyleManager(int a);                         // 0x00885bd0

// @ 0x00828f40
float cPropLayout::MeasureOverflow() {
  float best = 0.0f;
  unsigned i = 0;
  unsigned count = (unsigned)(mKids.mpEnd - mKids.mpBegin);
  if (0 < count) {
    do {
      IWin* w = (IWin*)mKids.mpBegin[i];
      if (w) {
        w->AddRef();
        IText* t = w->QueryText(0xf15f4bd);
        if (t && (w->GetFlags() & 1)) {
          Rect area;
          GetWindowArea(&area, w);
          int sid = w->GetStyleId();
          Style* st = GetStyleManager(1)->GetStyle(sid, 0);
          if (st->mMode != 2) {
            w->Release();
            goto next;
          }
          st->mMode = 0;
          Rect tr;
          t->Measure(&tr, 0, 1);
          st->mMode = 2;
          float tw = tr.r - tr.l;
          float aw = area.r - area.l;
          if (!(aw >= tw)) {
            float f = (tw - aw) + 8.0f;
            if (best < f) best = f;
          }
        }
        w->Release();
      }
    next:
      i++;
    } while (i < (unsigned)(((char*)mKids.mpEnd - (char*)mKids.mpBegin) >> 2));
  }
  return best;
}

// @ 0x00829080
Rect* cPropLayout::GetRect(Rect* out) {
  Rect tmp;
  Rect* p;
  if (m10) {
    m10->GetRect(out);
    return out;
  }
  IWin* w = m28.p;
  if (w) p = w->GetArea();
  else p = &tmp;
  *out = *p;
  return out;
}

// @ 0x00829110
IRef*** __cdecl UninitCopyRefs(IRef*** res, IRef** first, IRef** last, IRef** dest) {
  *res = dest;
  for (; first != last; ++first) {
    if (*res) {
      IRef* p = *first;
      **res = p;
      if (p) p->AddRef();
    }
    ++*res;
  }
  return res;
}

// @ 0x00829160
void cPropLayout::UpdateLayout(bool active) {
  if (mBusy) return;
  mBusy = true;
  if (m28.p) {
    if (active) {
      float w = MeasureOverflow();
      if (w > 0.0f) {
        Rect r30;
        GetRect(&r30);
        if (!mMoved) mOffset = r30.r - r30.l;
        if (!m30.p && m2c.p) {
          Rect bound;
          GetBoundingScreenRect(&bound, m28.p, 0);
          m30 = m28.p->GetParent();
          m30.p->Attach(m28.p);
          m2c.p->Detach(m28.p);
          m28.p->GetContainer()->Place(1, m28.p);
          Rect b2 = bound;
          Pt o1;
          m28.p->GetParent()->ToLocal(&o1, TL(b2));
          Pt s1 = o1;
          Pt o2;
          m28.p->GetParent()->ToLocal(&o2, BR(b2));
          Rect conv(s1.x, s1.y, o2.x, o2.y);
          m28.p->SetArea(&conv);
          Pt o3;
          m30.p->ToScreen(&o3, TL(r30));
          Pt o4;
          m28.p->GetParent()->ToLocal(&o4, o3);
          float nr = (r30.r - r30.l) + o4.x;
          float nb = (r30.b - r30.t) + o4.y;
          r30 = Rect(o4.x, o4.y, nr, nb);
        }
        Rect tmp;
        Rect* wa = GetWindowArea(&tmp, m28.p);
        Rect nr(r30.l, r30.t, ((wa->r - wa->l) + r30.l) + w, r30.b);
        ApplyRect(&nr);
        mMoved = true;
        mPending = false;
      }
    } else if (mMoved) {
      if (m30.p) mPending = true;
      mMoved = false;
      Rect g;
      GetRect(&g);
      Rect r40(g.l, g.t, (mOffset - (g.r - g.l)) + g.r, g.b);
      ApplyRect(&r40);
    }
  }
  mBusy = false;
  UpdateMouseFocus(1);
}

// @ 0x00829690
Rect* cPropLayout::GetRectLocal(Rect* out) {
  if (m30.p) {
    Rect r;
    GetRect(&r);
    Pt o1;
    m28.p->GetParent()->ToScreen(&o1, TL(r));
    Pt o2;
    IWin* w30 = m30.p;
    w30->ToLocal(&o2, o1);
    out->l = o2.x;
    out->t = o2.y;
    out->r = (r.r - r.l) + o2.x;
    out->b = (r.b - r.t) + o2.y;
    return out;
  }
  GetRect(out);
  return out;
}

// @ 0x008294c0
void cPropLayout::SetRect2(const Rect* in, bool flag) {
  Rect R;
  if (m30.p) {
    Pt o1;
    m30.p->ToScreen(&o1, *(const Pt*)&in->l);
    Pt o2;
    m28.p->GetParent()->ToLocal(&o2, o1);
    if (flag) {
      GetRect(&R);
      R = Rect(o2.x, o2.y, (R.r - R.l) + o2.x, (in->b - in->t) + o2.y);
    } else {
      R = Rect(o2.x, o2.y, (in->r - in->l) + o2.x, (in->b - in->t) + o2.y);
    }
  } else {
    if (!flag) {
      if (m10) {
        m10->SetRect(in);
        return;
      }
      if (m28.p) m28.p->SetArea(in);
      return;
    }
    GetRect(&R);
    R = Rect(in->l, in->t, (R.r - R.l) + in->l, in->b);
  }
  if (m10) {
    m10->SetRect(&R);
    return;
  }
  if (m28.p) m28.p->SetArea(&R);
}

// @ 0x008297b0
void cPropLayout::Tick() {
  bool act;
  if (m10) {
    act = m10->IsDragging();
  } else {
    IWin* f = GetWindowManager()->GetFocus(1);
    act = FUN_00805150(m28.p, f) != 0;
  }
  UpdateLayout(act);
  if (mPending) {
    mMoved = false;
    IWin* par = m28.p->GetParent();
    Rect tmp;
    Rect* wa = GetWindowArea(&tmp, m28.p);
    float delta = mOffset - (wa->r - wa->l);
    IWin* cur = m30.p;
    if (cur && par != cur) {
      float ad = delta < 0 ? -delta : delta;
      if (!(ad < 0.1f)) return;
      Rect L = *m28.p->GetArea();
      Pt a1;
      par->ToScreen(&a1, TL(L));
      Pt s1 = a1;
      Pt a2;
      par->ToScreen(&a2, BR(L));
      Pt s2 = a2;
      par->Attach(m28.p);
      m30.p->Detach(m28.p);
      Pt p1;
      m30.p->ToLocal(&p1, s1);
      Pt p2;
      m30.p->ToLocal(&p2, s2);
      Rect nr(p1.x, p1.y, p2.x, p2.y);
      m28.p->SetArea(&nr);
      cur = m30.p;
    }
    if (cur) {
      m30.p = 0;
      ((IRef*)cur)->Release();
    }
    mPending = false;
  }
}

// ---- 0x00829ad0: vector<AutoRef<IRef>>::operator= ------------------------------------
extern void __cdecl OperatorDeleteRaw(void* p);                                        // 0x00f47380
IRef** __cdecl CopyRefsRange(IRef** first, IRef** last, IRef** dest);                  // 0x006782c0
IRef*** __cdecl UninitCopyRefs5(IRef*** res, IRef** first, IRef** last, IRef** dest, const RefVec* junk);   // 0x00829110

// @ 0x00829ad0
RefVec& RefVec::operator=(const RefVec& x) {
  if (&x != this) {
    const unsigned n = (unsigned)(x.mpEnd - x.mpBegin);
    if (n > (unsigned)(mpCap - mpBegin)) {
      IRef** pNew = DoAllocateAndCopy(n, x.mpBegin, x.mpEnd);
      DoDestroy(mpBegin, mpEnd);
      if (mpBegin && ((int*)mpBegin)[-1] != 0) OperatorDeleteRaw(mpBegin);
      mpCap = pNew + n;
      mpEnd = pNew + n;
      mpBegin = pNew;
      return *this;
    }
    unsigned sz = (unsigned)(mpEnd - mpBegin);
    if (n > sz) {
      CopyRefsRange(x.mpBegin, x.mpBegin + sz, mpBegin);
      IRef** res;
      UninitCopyRefs5(&res, x.mpBegin + (mpEnd - mpBegin), x.mpEnd, mpEnd, &x);
      mpEnd = mpBegin + n;
      return *this;
    }
    IRef** p = CopyRefsRange(x.mpBegin, x.mpEnd, mpBegin);
    DoDestroy(p, mpEnd);
    mpEnd = mpBegin + n;
  }
  return *this;
}
