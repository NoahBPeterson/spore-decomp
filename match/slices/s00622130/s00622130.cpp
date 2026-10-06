// SP::cXHTMLControlAppearance::Init (0x00622130, 3521 bytes).
//
// Builds the control-appearance drawable set: a StdDrawable per control kind (button, checkbox,
// radio, text) whose state images come from SPUIHelpers::CreateImageFromResource and whose hit
// mask comes from CreateHitMaskFromResource; each is published as an {id, drawable} pair into the
// appearance vector.  Then two ScrollbarDrawable objects (vertical, horizontal) are created and
// stored in the member ref_ptrs at +0x1c / +0x20 and filled with their five images each.
#include "types.h"

inline void* operator new(unsigned, void* p) { return p; }
inline void operator delete(void*, void*) {}

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

// Image/state holder embedded at +0x0c of the drawables.
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

struct Drawable : RefObj {
  virtual void v2();
  virtual RefObj* GetDrawable(uint32_t id);      // +0x0c (slot 3)
};

struct StdDrawable : Drawable {
  uint32_t pad4[2];
  ImageSet set;       // +0x0c
  uint32_t pad[27];   // to 0x7c
  StdDrawable();      // 0x988420
};

struct ScrollbarDrawable : Drawable {
  uint32_t pad4[2];
  ImageSet set;       // +0x0c
  uint32_t pad[7];    // to 0x2c
  ScrollbarDrawable();  // 0x9838a0
};

bool __cdecl CreateImageFromResource(uint32_t type, uint32_t group, const wchar_t* name,
                                     Image** out, int a, int b, int c);   // 0x806320

struct ControlDrawable {
  int id;
  ref_ptr<RefObj> d;
  ControlDrawable() : id(0) {}
  ControlDrawable(const ControlDrawable& o) : id(o.id), d(o.d) {}
};

struct ControlVec {
  ControlDrawable* mpBegin;  // +0x08 in the appearance object
  ControlDrawable* mpEnd;    // +0x0c
  ControlDrawable* mpCap;    // +0x10
  void DoInsertValue(ControlDrawable* pos, const ControlDrawable& v);   // 0x621fc0
  void push_back(const ControlDrawable& v) {
    ControlDrawable* e = mpEnd;
    if (e < mpCap) {
      mpEnd = e + 1;
      if (e) new (e) ControlDrawable(v);
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

// @ 0x00622130
bool cXHTMLControlAppearance31::Init() {
  ref_ptr<Image> img;
  ref_ptr<StdDrawable> p(NewStd());
  ControlDrawable cd;

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
