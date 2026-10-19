// src/game/SPEditors/SPXHTMLControlAppearance.cpp -- migrated from slice(s) s00622130, s00621830 by tools/migrate/rewrite.py
// Object file: SPEditors/SPXHTMLControlAppearance.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00621830 begin (TODO(rewrite): local stubs, replace by canonical classes)
uint32_t __cdecl FUN_00a35070(void* a, void* b, void* c);                    // 0xa35070
void* __cdecl FUN_008de1a0();                                                // 0x8de1a0 (resource manager)
uint32_t __cdecl Hash_FNV1_String16(const void* s, uint32_t basis, int a);    // 0x932f30
void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b,
                          const char* file, int line);                       // 0xf473a0
void  __cdecl EA_Free(void* p);                                              // 0xf47380
static inline void** Vt(void* p) { return *(void***)p; }
struct Drawable {
  virtual void dtor();     // +0x00 (slot 0)
  virtual void AddRef();   // +0x04 (slot 1)
  virtual void Release();  // +0x08 (slot 2)
};
struct ControlDrawable {
  uint32_t  mId;          // +0x00
  Drawable* mpDrawable;   // +0x04
  void AddRefIfAny() { if (mpDrawable) ((void(__thiscall*)(Drawable*))Vt(mpDrawable)[0])(mpDrawable); }
};
struct WinXHTML {
  void SetFormControlDrawable(uint32_t id, Drawable* p);
  void SetScrollbarDrawable(int which, void* p);
};
struct cXHTMLControlAppearance {
  virtual void v0();          // +0x00
  uint32_t mPad4;             // +0x04
  ControlDrawable* mpBegin;   // +0x08
  ControlDrawable* mpEnd;     // +0x0c
  ControlDrawable* mpCap;     // +0x10
  uint32_t mPad14;            // +0x14
  uint32_t mPad18;            // +0x18
  Drawable* mpScroll1;        // +0x1c
  Drawable* mpScroll2;        // +0x20

  cXHTMLControlAppearance();                       // 0x621ee0
  ~cXHTMLControlAppearance();                      // 0x621f00
  void Apply(WinXHTML* w);                         // 0x621bf0
  bool CreateHitMaskFromResource(int* p1, int* p2, void** out);  // 0x621db0
};
namespace eastl {
struct vector_s0062_1830 {   // stub for vector<ControlDrawable>; receiver arrives in ECX
  ControlDrawable* mpBegin; ControlDrawable* mpEnd; ControlDrawable* mpCap;
  ControlDrawable* erase(ControlDrawable* first, ControlDrawable* last);
  void DoInsertValue(ControlDrawable* position, const ControlDrawable& value);
};
}
// ---- items of slice s00621830 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
ControlDrawable* UninitCopyBackward(ControlDrawable* first, ControlDrawable* last, ControlDrawable* destEnd);  // 0x00621d50 (stays in the slice: not this object's)

// ---- items of slice s00622130 begin (TODO(rewrite): local stubs, replace by canonical classes)
inline void* operator new(unsigned, void* p) { return p; }
void* __cdecl FUN_009512c0();                                                        // 0x9512c0
void* __cdecl FUN_009512d0(unsigned size, int align, const char* name, void* alloc); // 0x9512d0
struct RefObj {
  virtual void AddRef();   // +0x00
  virtual void Release();  // +0x04
};
template <class T>
struct ref_ptr {
  T* mp;
  ref_ptr() : mp(0) {}
  ref_ptr(T* p) : mp(p) { if (mp) mp->AddRef(); }
  ref_ptr(const ref_ptr& o) : mp(o.mp) { if (mp) mp->AddRef(); }
  ~ref_ptr() { if (mp) mp->Release(); }
  ref_ptr& operator=(T* p) {
    if (p != mp) {
      T* old = mp;
      if (p) p->AddRef();
      mp = p;
      if (old) old->Release();
    }
    return *this;
  }
  void reset() {
    T* old = mp;
    if (old) { mp = 0; old->Release(); }
  }
  T* operator->() const { return mp; }
  operator T*() const { return mp; }
};
struct Image : RefObj {};
struct HitMask : RefObj {};
struct ImageSet {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void SetImage(int slot, Image* img);   // +0x14
  virtual void v6();
  virtual void SetMode(int mode);                // +0x1c
  virtual void v8();
  virtual void v9();
  virtual void v10();
  virtual void v11();
  virtual void v12();
  virtual void SetHitMask(HitMask* m);           // +0x34
};
struct Drawable_s0062_2130 : RefObj {
  virtual void v2();
  virtual RefObj* GetDrawable(uint32_t id);      // +0x0c (slot 3)
};
struct StdDrawable : Drawable_s0062_2130 {
  uint32_t pad4[2];
  ImageSet set;       // +0x0c
  uint32_t pad[27];   // to 0x7c
  StdDrawable();      // 0x988420
};
struct ScrollbarDrawable : Drawable_s0062_2130 {
  uint32_t pad4[2];
  ImageSet set;       // +0x0c
  uint32_t pad[7];    // to 0x2c
  ScrollbarDrawable();  // 0x9838a0
};
bool __cdecl CreateImageFromResource(uint32_t type, uint32_t group, const wchar_t* name,
                                     Image** out, int a, int b, int c);   // 0x806320
struct ControlDrawable_s0062_2130 {
  int id;
  ref_ptr<RefObj> d;
  ControlDrawable_s0062_2130() : id(0) {}
  ControlDrawable_s0062_2130(const ControlDrawable_s0062_2130& o) : id(o.id), d(o.d) {}
};
struct ControlVec {
  ControlDrawable_s0062_2130* mpBegin;  // +0x08 in the appearance object
  ControlDrawable_s0062_2130* mpEnd;    // +0x0c
  ControlDrawable_s0062_2130* mpCap;    // +0x10
  void DoInsertValue(ControlDrawable_s0062_2130* pos, const ControlDrawable_s0062_2130& v);   // 0x621fc0
  void push_back(const ControlDrawable_s0062_2130& v) {
    ControlDrawable_s0062_2130* e = mpEnd;
    if (e < mpCap) {
      mpEnd = e + 1;
      if (e) new (e) ControlDrawable_s0062_2130(v);
    } else {
      DoInsertValue(e, v);
    }
  }
};
struct cXHTMLControlAppearance31 {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  uint32_t mPad4;
  ControlVec mVec;               // +0x08
  uint32_t mPad14;
  uint32_t mPad18;
  ref_ptr<ScrollbarDrawable> mpScroll1;   // +0x1c
  ref_ptr<ScrollbarDrawable> mpScroll2;   // +0x20

  bool Init();                   // 0x622130
  bool CreateHitMaskFromResource(uint32_t group, const wchar_t* name, HitMask** out);  // 0x621db0
};
static inline StdDrawable* NewStd() {
  void* m = FUN_009512d0(0x7c, 4, "UI/ControlAppearance/StdDrawable", FUN_009512c0());
  return m ? new (m) StdDrawable : 0;
}
static inline ScrollbarDrawable* NewScroll() {
  void* m = FUN_009512d0(0x2c, 4, "UI/ControlAppearance/ComboBoxDrawable", FUN_009512c0());
  return m ? new (m) ScrollbarDrawable : 0;
}
#define IMG(set, name, slot)                                                        \
  if (CreateImageFromResource(0x2f7d0004, 0x11c0bde, name, (Image**)&img, 0, -1, -1)) \
    (set).SetImage(slot, img);                                                      \
  img.reset();
// ---- items of slice s00622130 end

// @ 0x00621cc0
ControlDrawable* UninitCopy(ControlDrawable* first, ControlDrawable* last, ControlDrawable* dest)
{
  while (first != last) {
    if (dest != 0) {
      dest->mId = first->mId;
      dest->mpDrawable = first->mpDrawable;
      if (dest->mpDrawable)
        ((void(__thiscall*)(Drawable*))Vt(dest->mpDrawable)[0])(dest->mpDrawable);
    }
    ++first;
    ++dest;
  }
  return dest;
}

// @ 0x00621db0
bool cXHTMLControlAppearance::CreateHitMaskFromResource(int* p1, int* p2, void** out)
{
  uint32_t hash = Hash_FNV1_String16(p2, 0x811c9dc5, 0);
  void* local18 = (void*)0x2f7d0004;
  (void)local18;
  uint32_t localc = hash;
  (void)localc;
  *out = 0;
  void* req = 0;
  void* mgr = FUN_008de1a0();
  if (req) { void* o = req; req = 0; ((void(__thiscall*)(void*))Vt(o)[1])(o); }
  bool ok = ((bool(__thiscall*)(void*, void*, void**, int, int, int, void*))Vt(mgr)[3])
               (mgr, &localc, &req, 0, 0, 0, &local18);
  if (ok) {
    if (p1 == 0) return false;
    void* r = ((void*(__thiscall*)(void*, uint32_t))Vt(p1)[3])(p1, 0xf074e1c8);
    if (r) {
      *out = r;
      ((void(__thiscall*)(void*))Vt(r)[0])(r);
      if (p1) ((void(__thiscall*)(void*))Vt(p1)[1])(p1);
      return true;
    }
  }
  if (p1) ((void(__thiscall*)(void*))Vt(p1)[1])(p1);
  return false;
}

// @ 0x00621ee0
cXHTMLControlAppearance::cXHTMLControlAppearance()
: mPad4(0), mpBegin(0), mpEnd(0), mpCap(0), mpScroll1(0), mpScroll2(0) {}

// @ 0x00621f00
cXHTMLControlAppearance::~cXHTMLControlAppearance()
{
  if (mpScroll2) ((void(__thiscall*)(Drawable*))Vt(mpScroll2)[1])(mpScroll2);
  if (mpScroll1) ((void(__thiscall*)(Drawable*))Vt(mpScroll1)[1])(mpScroll1);
  if (mpBegin) EA_Free(mpBegin);
}

// @ 0x00621f50
ControlDrawable* eastl::vector_s0062_1830::erase(ControlDrawable* first, ControlDrawable* last)
{
  void* self = this;
  ControlDrawable** pEnd = (ControlDrawable**)((char*)self + 4);
  uint32_t r = FUN_00a35070(last, *pEnd, first);
  if (r < (uint32_t)*pEnd) {
    int n = (int)((((uint32_t)*pEnd - r) - 1) >> 3) + 1;
    uint32_t* p = (uint32_t*)(r + 4);
    do {
      if (*p) ((void(__thiscall*)(void*))Vt((void*)*p)[1])((void*)*p);
      p += 2;
      --n;
    } while (n != 0);
  }
  *pEnd = (ControlDrawable*)((char*)*pEnd + (((char*)last - (char*)first) >> 3) * -8);
  return first;
}

// @ 0x00621fc0
void eastl::vector_s0062_1830::DoInsertValue(ControlDrawable* position, const ControlDrawable& value)
{
  void* self = this;
  ControlDrawable** pBegin = (ControlDrawable**)self;
  ControlDrawable** pEnd = (ControlDrawable**)((char*)self + 4);
  ControlDrawable** pCap = (ControlDrawable**)((char*)self + 8);
  ControlDrawable* end = *pEnd;
  if (end != *pCap) {
    if (position <= end && end < (ControlDrawable*)pEnd) position += 1;
    if (end) {
      end->mId = end[-1].mId;
      end->mpDrawable = end[-1].mpDrawable;
      if (end->mpDrawable)
        ((void(__thiscall*)(Drawable*))Vt(end->mpDrawable)[0])(end->mpDrawable);
    }
    UninitCopyBackward(position, end - 1, end);
    position->mId = value.mId;
    Drawable* p = value.mpDrawable;
    Drawable* old = position->mpDrawable;
    if (p != old) {
      if (p) ((void(__thiscall*)(Drawable*))Vt(p)[0])(p);
      position->mpDrawable = p;
      if (old) ((void(__thiscall*)(Drawable*))Vt(old)[1])(old);
    }
    *pEnd = end + 1;
    return;
  }
  int n = (int)(end - *pBegin);
  int cap;
  if (n == 0) cap = 1;
  else cap = n * 2;
  ControlDrawable* newBuf = 0;
  if (cap != 0)
    newBuf = (ControlDrawable*)EA_Allocate(cap * 8, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  ControlDrawable* mid = UninitCopy(*pBegin, position, newBuf);
  UninitCopyBackward(*pBegin, position, newBuf);
  if (mid) {
    mid->mId = value.mId;
    mid->mpDrawable = value.mpDrawable;
    if (mid->mpDrawable)
      ((void(__thiscall*)(Drawable*))Vt(mid->mpDrawable)[0])(mid->mpDrawable);
  }
  ControlDrawable* tail = UninitCopy(position, end, mid + 1);
  if (*pBegin && *(int*)((char*)*pBegin - 4) != 0) EA_Free(*pBegin);
  *pBegin = newBuf;
  *pEnd = tail;
  *pCap = newBuf + cap;
}

// @ 0x00622130
bool cXHTMLControlAppearance31::Init()
{
  ref_ptr<Image> img;
  ref_ptr<StdDrawable> p(NewStd());
  ControlDrawable_s0062_2130 cd;

  // button
  IMG(p->set, L"button-generic-norm", 0);
  IMG(p->set, L"button-generic-hl", 2);
  IMG(p->set, L"button-generic-act", 3);
  IMG(p->set, L"button-generic-off", 1);
  ref_ptr<HitMask> mask;
  if (CreateHitMaskFromResource(0x11c0bde, L"button-generic-hitmask", (HitMask**)&mask))
    p->set.SetHitMask(mask);
  p->set.SetMode(2);
  cd.d = p->GetDrawable(0x6ec581fd);
  mVec.push_back(cd);
  cd.id = 2;

  // checkbox
  p = NewStd();
  img.reset();
  IMG(p->set, L"button-chckbox-norm", 0);
  IMG(p->set, L"button-chckbox-hl", 2);
  IMG(p->set, L"button-chckbox-act", 3);
  IMG(p->set, L"button-chckbox-off", 1);
  IMG(p->set, L"button-chckbox-on-norm", 4);
  IMG(p->set, L"button-chckbox-on-hl", 6);
  IMG(p->set, L"button-chckbox-on-act", 7);
  IMG(p->set, L"button-chckbox-on-off", 5);
  mask.reset();
  if (CreateHitMaskFromResource(0x11c0bde, L"button-chckbox-hitmask", (HitMask**)&mask))
    p->set.SetHitMask(mask);
  p->set.SetMode(1);
  cd.d = p->GetDrawable(0x6ec581fd);
  mVec.push_back(cd);
  cd.id = 3;

  // radio
  p = NewStd();
  img.reset();
  IMG(p->set, L"radiobox-norm", 0);
  IMG(p->set, L"radiobox-hl", 2);
  IMG(p->set, L"radiobox-act", 3);
  IMG(p->set, L"radiobox-off", 1);
  IMG(p->set, L"radiobox-on-norm", 4);
  IMG(p->set, L"radiobox-on-hl", 6);
  IMG(p->set, L"radiobox-on-act", 7);
  IMG(p->set, L"radiobox-on-off", 5);
  mask.reset();
  if (CreateHitMaskFromResource(0x11c0bde, L"radiobox-hitmask", (HitMask**)&mask))
    p->set.SetHitMask(mask);
  p->set.SetMode(1);
  cd.d = p->GetDrawable(0x6ec581fd);
  mVec.push_back(cd);
  cd.id = 1;

  // text
  p = NewStd();
  img.reset();
  IMG(p->set, L"text-bakgrnd", 0);
  p->set.SetMode(2);
  cd.d = p->GetDrawable(0x6ec581fd);
  mVec.push_back(cd);

  // vertical scrollbar
  mpScroll1 = NewScroll();
  img.reset();
  IMG(mpScroll1->set, L"scroll-arrows-up", 1);
  IMG(mpScroll1->set, L"scroll-thumb", 3);
  IMG(mpScroll1->set, L"scroll-thumb-bkgrnd", 4);
  IMG(mpScroll1->set, L"scroll-arrows-down", 6);
  IMG(mpScroll1->set, L"scroll-bkgrnd-opaque", 0);

  // horizontal scrollbar
  mpScroll2 = NewScroll();
  img.reset();
  IMG(mpScroll2->set, L"scroll-arrows-left", 1);
  IMG(mpScroll2->set, L"scroll-thumb-hrz", 3);
  IMG(mpScroll2->set, L"scroll-thumb-bkgrnd-hrz", 4);
  IMG(mpScroll2->set, L"scroll-arrows-right", 6);
  IMG(mpScroll2->set, L"scroll-bkgrnd-opaque-hrz", 0);
  return true;
}
