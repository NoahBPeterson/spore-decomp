// src/game/SPEditors/SPEditorPalettePageUI.cpp -- migrated from slice(s) s005c9230, s005c85d0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPEditorPalettePageUI.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayout.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern float g_one;  // 0x01485720
#include <new>
#include "SP/cSPPalettePageUI.h"
#include "EA/UTFWin/IWindow.h"
#include "SP/cSPPaletteItem.h"
#include "SP/cSPPalettePage.h"

// ---- items of slice s005c85d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern float g_half;  // 0x01471064 (0.5f, the grid-cell centring bias)
#define PV(n) virtual void pv##n();
namespace EA {
template <typename T>
class AutoRefCount_s005c_85d0 {
 public:
  T* mpObject;
  AutoRefCount_s005c_85d0() : mpObject(0) {}
  AutoRefCount_s005c_85d0(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount_s005c_85d0() { if (mpObject) mpObject->Release(); }
  AutoRefCount_s005c_85d0& operator=(T* p) {
    if (p != mpObject) {
      T* const pTemp = mpObject;
      if (p)
        p->AddRef();
      mpObject = p;
      if (pTemp)
        pTemp->Release();
    }
    return *this;
  }
  T* operator->() const { return mpObject; }
  operator T*() const { return mpObject; }
};  // namespace EA
}
using EA::AutoRefCount_s005c_85d0;
namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector();  // 0x005c7f10
  T* begin() { return mpBegin; }
  T* end() { return mpEnd; }
};  // namespace eastl
}
class IRefCount_s005c_85d0 {
 public:
  virtual int AddRef();
  virtual int Release();
};
class cBase1 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  int mPad4, mPad8;
};
class cRefObj : public cBase1, public IRefCount_s005c_85d0 {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};
class cRefNode : public cBase1, public IRefCount_s005c_85d0 {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};
class cSPUILayout_s005c_85d0 {
 public:
  PV(0) PV(1)
  virtual void Release();       // +0x8
  int AddRef();                 // non-virtual, only to satisfy AutoRefCount
  void Shutdown(bool destroy);  // 0x00811ad0
};
namespace EA {
namespace UTFWin {
class IWindow_s005c_85d0 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};  // namespace UTFWin
}
}
using EA::UTFWin::IWindow_s005c_85d0;
class cRefVector {
 public:
  cRefNode** mpBegin;
  cRefNode** mpEnd;
  cRefNode** mpCapacity;
  int mAllocator[2];
  cRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~cRefVector();
};
class cUIVtblA {
 public:
  virtual ~cUIVtblA() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
};
class cUIVtblB {
 public:
  virtual ~cUIVtblB() {}
  PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7)
};
class cSPPalettePageUI : public cUIVtblA, public cUIVtblB {
 public:
  cSPPalettePageUI();
  virtual ~cSPPalettePageUI() {}
  static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
  virtual cRefObj* GetRef(int a, int b, int c, int d);  // +0x20

  int mField8;                            // +0x8
  AutoRefCount_s005c_85d0<cSPUILayout_s005c_85d0> mLayout;      // +0xc
  IWindow_s005c_85d0* mSwatch;                       // +0x10
  AutoRefCount_s005c_85d0<cRefObj> mField14;         // +0x14
  float mFloat18;                         // +0x18
  float mFloat1c;                         // +0x1c
  eastl::sp_vector<cRefNode*> mNodes20;   // +0x20
  cRefVector mRefs34;                     // +0x34

  void SetSwatchFlag(int value);  // 0x005c8bf0
  void Shutdown();                // 0x005c8cc0
  void Accept(int value);         // 0x005c8d30
  cRefObj* GetAndAssign(int a1, AutoRefCount_s005c_85d0<cRefObj>* out, int a3, int a4);  // 0x005c8c50
};
struct cSPPaletteItem {  // refcounted palette entry stored in mItems
  virtual void Accept(int value);
  int AddRef();
  int Release();
};
struct PagePartSource {
  uint8_t mPad00[0x14];
  float v14;            // +0x14
  float v18;            // +0x18
  float v1c;            // +0x1c
  float v20;            // +0x20
  float v24;            // +0x24
  float v28;            // +0x28
  uint8_t b2d;          // +0x2d
  uint8_t mPad2e[2];
  float v30;            // +0x30
  float v34;            // +0x34
  float v38;            // +0x38
  float v3c;            // +0x3c
  float v40;            // +0x40
  float v44;            // +0x44
  uint8_t b48;          // +0x48
  uint8_t b49;          // +0x49
  uint8_t b4a;          // +0x4a
  uint8_t mPad4b;
  float v4c;            // +0x4c
  int32_t n50;          // +0x50
  int32_t n54;          // +0x54
};
struct PagePartDef {
  uint8_t mPad00[0x10];
  void* mpRectSource;    // +0x10
  PagePartSource* mpCfg; // +0x14
  float v18;             // +0x18
  float v1c;             // +0x1c
  void cPagePartBig(float* out, int index);   // 0x005c8d70
};
void* SPUIHelpers_GetMainWindowArea(void* outVec4);   // 0x00805ea0
void PagePartCopyBackward(AutoRefCount_s005c_85d0<cSPPaletteItem>* first, AutoRefCount_s005c_85d0<cSPPaletteItem>* last,
                          AutoRefCount_s005c_85d0<cSPPaletteItem>* dest);          // 0x005c2fa0
void* PagePartAlloc(unsigned n);                                        // 0x00f473a0
void* EaBulkMove(void* a, const void* b, unsigned n);                   // 0x011e0744
// ---- items of slice s005c85d0 end

// ---- items of slice s005c9230 begin (TODO(rewrite): local stubs, replace by canonical classes)
class cSPPalettePageUI_s005c_9230 {
 public:
  bool Init(int a, int b, int c, int d);  // 0x005c9230 (cSPPalettePageUI::Init)
};
// ---- items of slice s005c9230 end

// @ 0x005c8bf0
void cSPPalettePageUI::SetSwatchFlag(int value)
{
  if (mSwatch)
    mSwatch->SetFlag(1, value);
}

// @ 0x005c8c50
cRefObj* cSPPalettePageUI::GetAndAssign(int a1, AutoRefCount_s005c_85d0<cRefObj>* out, int a3, int a4)
{
  cRefObj* p = GetRef(a1, 0x4785a3d, a3, a4);
  *out = p;
  return *out;
}

// @ 0x005c8cc0
void cSPPalettePageUI::Shutdown()
{
  int count = (int)(mNodes20.mpEnd - mNodes20.mpBegin);
  for (int i = 0; i < count; i++)
    mNodes20.mpBegin[i]->Shutdown();
  int count2 = (int)(mRefs34.mpEnd - mRefs34.mpBegin);
  for (int i = 0; i < count2; i++)
    mRefs34.mpBegin[i]->pv2();
  if (mLayout) {
    mLayout->Shutdown(true);
    mLayout = 0;
  }
}

// @ 0x005c8d30
void cSPPalettePageUI::Accept(int value)
{
  int count = (int)(mRefs34.mpEnd - mRefs34.mpBegin);
  for (int i = 0; i < count; i++)
    mRefs34.mpBegin[i]->Accept(value);
}

// @ 0x005c8d70
void PagePartDef::cPagePartBig(float* out, int index)
{
  PagePartSource* c = mpCfg;
  const float K = g_half;                       // 0x01471064

  if (c->b48 == 0) {
    // ---- no explicit border: plain grid slot, optionally offset by the part's own values ----
    float w = g_one, h = g_one;                 // 0x01485720
    if (c->b2d == 0) {
      w = v18;
      h = v1c;
    }
    int q = index / c->n50;                     // rows
    int r = index % c->n50;

    float px = ((c->v24 + c->v18) * (float)q) * w;   // (v24+v18)*row*w
    float oy = c->v1c * w;
    float py = ((c->v28 + c->v14) * (float)r) * h;   // (v28+v14)*col*h
    float ox = c->v20 * h;

    out[0] = px + oy;
    out[1] = py + ox;
    out[2] = c->v18 * w + px + oy;
    out[3] = c->v14 * h + py + ox;
    return;
  }

  if (mpRectSource == 0)
    return;                                     // nothing to do: leaves `out` untouched

  // ---- explicit border: inset the part into the part's rectangle ----
  float* rect = (float*)(*(void*(__thiscall**)(void*))(*(uint32_t*)mpRectSource + 0x38))(mpRectSource);
  float w = rect[2] - rect[0];
  float h = rect[3] - rect[1];
  float b1 = c->v38, b2 = c->v30, b3 = c->v3c, b4 = c->v34;
  if (c->b4a == 0) {
    b1 *= w;
    b2 *= h;
    b3 *= w;
    b4 *= h;
  }
  int q = index / c->n50;
  int r = index % c->n50;
  float x = ((w - b1 - b3) / (float)c->n54) * ((float)q + K) + b1;
  float y = ((h - b2 - b4) / (float)c->n50) * ((float)r + K) + b2;

  float sw, sh;
  if (c->b49 != 0) {
    sw = c->v18;
    sh = c->v14;
  } else {
    float area[4];
    SPUIHelpers_GetMainWindowArea(area);        // 0x00805ea0
    float t = c->v40 * h;
    float d = c->v44;
    float lim = c->v4c * area[0];
    float m = t / d;
    if (m > lim) {
      m = lim;
      lim *= d;
      t = lim;
    }
    sw = t;
    sh = m;
  }

  out[0] = x - sw * K;
  out[1] = y - sh * K;
  out[2] = out[0] + sw;
  out[3] = out[1] + sh;
}

// @ 0x005c8fd0
cRefVector::~cRefVector()
{
  cRefNode** end = mpEnd;
  for (cRefNode** p = mpBegin; p < end; ++p) {
    if (*p)
      (*p)->Release();
  }
  if (mpBegin && ((int*)mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mpBegin);
}

// @ 0x005c9010
cSPPalettePageUI::cSPPalettePageUI()
: mField8(0), mLayout(0), mSwatch(0), mField14(0), mFloat18(g_one), mFloat1c(g_one),
      mNodes20(), mRefs34() {}

// @ 0x005c90d0
void cVectorInsertBig(void* vec, void* pos, void* value)
{
  uint32_t* v = (uint32_t*)vec;      // [0]=begin [4]=end [8]=capacity
  uint32_t* vpos = (uint32_t*)pos;
  uint32_t* vval = (uint32_t*)value;

  if (v[1] != v[2]) {
    // ---- room available: shift the [pos, end) range one slot backwards ----
    uint32_t* src = (vval >= vpos && vval < (uint32_t*)v[1]) ? vval + 1 : vval;
    uint32_t end = v[1];
    if (end != 0) {
      uint32_t cur = *(uint32_t*)(end - 4);
      *(uint32_t*)end = cur;
      if (cur != 0) {
        void* vt = *(void**)(cur + 0xc);
        (*(void(__thiscall**)(uint32_t))(*(uint32_t*)vt))(cur + 0xc);   // AddRef
      }
    }
    {
      uint32_t* e = (uint32_t*)v[1];
      PagePartCopyBackward((AutoRefCount_s005c_85d0<cSPPaletteItem>*)vpos,
                           (AutoRefCount_s005c_85d0<cSPPaletteItem>*)(e - 1),
                           (AutoRefCount_s005c_85d0<cSPPaletteItem>*)e);           // 0x005c2fa0
    }
    uint32_t newv = *src;
    uint32_t oldv = *vpos;
    if (newv != oldv) {
      if (newv != 0) {
        void* vt = *(void**)(newv + 0xc);
        (*(void(__thiscall**)(uint32_t))(*(uint32_t*)vt))(newv + 0xc);  // AddRef
      }
      *vpos = newv;
      if (oldv != 0) {
        void* vt = *(void**)(oldv + 0xc);
        (*(void(__thiscall**)(uint32_t))(*(uint32_t*)vt + 4))(oldv + 0xc);  // Release
      }
    }
    v[1] += 4;
    return;
  }

  // ---- full: grow to max(1, 2*size) and rebuild ----
  uint32_t count = (v[1] - v[0]) >> 2;
  uint32_t newCap;
  uint32_t* buf;
  if (count == 0) {
    newCap = 1;
    buf = (uint32_t*)PagePartAlloc(newCap * 4);
  } else {
    newCap = count * 2;
    buf = newCap ? (uint32_t*)PagePartAlloc(newCap * 4) : 0;
  }

  uint32_t* begin = (uint32_t*)v[0];
  uint32_t* p = (uint32_t*)vpos;
  uint32_t* inserted = (uint32_t*)EaBulkMove(buf, begin, (p - begin) * 4);
  inserted = (uint32_t*)((char*)inserted + (((p - begin) * 4) >> 2) * 4);
  if (inserted != 0) {
    uint32_t nv = *vval;
    *inserted = nv;
    if (nv != 0) {
      void* vt = *(void**)(nv + 0xc);
      (*(void(__thiscall**)(uint32_t))(*(uint32_t*)vt))(nv + 0xc);     // AddRef
    }
  }
  uint32_t tailBytes = v[1] - (uint32_t)p;
  uint32_t* tail = (uint32_t*)EaBulkMove(inserted + 1, p, tailBytes);
  tail = (uint32_t*)((char*)tail + (tailBytes >> 2) * 4);

  uint32_t* oldBegin = (uint32_t*)v[0];
  if (oldBegin != 0 && *(uint32_t*)(oldBegin - 1) != 0)
    operator delete[](oldBegin);

  v[1] = (uint32_t)tail;
  v[0] = (uint32_t)buf;
  v[2] = (uint32_t)(buf + newCap);
}

// @ 0x005c9230
bool cSPPalettePageUI_s005c_9230::Init(int a, int b, int c, int d)
{
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  return false;
}
