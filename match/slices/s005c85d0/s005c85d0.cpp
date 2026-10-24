// slice s005c85d0 -- SP::cSPPalettePage::CommonInit / Init and the page-UI helper methods
// (page-part iteration, refcounted-vector teardown, page-UI ctor/dtor). Flags as the module:
// /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

#define PV(n) virtual void pv##n();

namespace EA {
template <typename T>
class AutoRefCount {
 public:
  T* mpObject;
  AutoRefCount() : mpObject(0) {}
  AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
  ~AutoRefCount() { if (mpObject) mpObject->Release(); }
  AutoRefCount& operator=(T* p) {
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
};
}  // namespace EA

using EA::AutoRefCount;

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
};
}  // namespace eastl

// Refcount interface reached through a secondary base at +0xc (AddRef slot0 / Release slot1).
class IRefCount {
 public:
  virtual int AddRef();
  virtual int Release();
};

// First polymorphic base of 0xc bytes, so IRefCount of cRefObj lands at +0xc.
class cBase1 {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  int mPad4, mPad8;
};

class cRefObj : public cBase1, public IRefCount {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};

// Page-part element in the +0x34 refcounted vector.
class cRefNode : public cBase1, public IRefCount {
 public:
  virtual void Accept(int value);  // +0x18
  void Shutdown();                 // 0x005c7320
};

// UI layout: Release at vtable +0x8.
class cSPUILayout {
 public:
  PV(0) PV(1)
  virtual void Release();       // +0x8
  int AddRef();                 // non-virtual, only to satisfy AutoRefCount
  void Shutdown(bool destroy);  // 0x00811ad0
};

namespace EA {
namespace UTFWin {
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, int value);  // +0x7c
};
}  // namespace UTFWin
}  // namespace EA
using EA::UTFWin::IWindow;

// +0x34 vector: raw pointer array with Release/free (dtor @005c8fd0).
class cRefVector {
 public:
  cRefNode** mpBegin;
  cRefNode** mpEnd;
  cRefNode** mpCapacity;
  int mAllocator[2];
  cRefVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~cRefVector();
};

// Two no-data polymorphic bases; the first has a virtual dtor so the derived dtor and GetRef
// land at slots 0 and 8 (+0x20) exactly.
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
  AutoRefCount<cSPUILayout> mLayout;      // +0xc
  IWindow* mSwatch;                       // +0x10
  AutoRefCount<cSPUILayout> mField14;     // +0x14 (virtual Release at primary vtable +8, like mLayout)
  float mFloat18;                         // +0x18
  float mFloat1c;                         // +0x1c
  eastl::sp_vector<cRefNode*> mNodes20;   // +0x20
  cRefVector mRefs34;                     // +0x34

  void SetSwatchFlag(int value);  // 0x005c8bf0
  void Shutdown();                // 0x005c8cc0
  void Accept(int value);         // 0x005c8d30
  cRefObj* GetAndAssign(int a1, AutoRefCount<cRefObj>* out, int a3, int a4);  // 0x005c8c50
};

// @ 0x005C8BF0
void cSPPalettePageUI::SetSwatchFlag(int value) {
  if (mSwatch)
    mSwatch->SetFlag(1, value);
}

// @ 0x005C8D30
void cSPPalettePageUI::Accept(int value) {
  int count = (int)(mRefs34.mpEnd - mRefs34.mpBegin);
  for (int i = 0; i < count; i++)
    mRefs34.mpBegin[i]->Accept(value);
}

// @ 0x005C8CC0
void cSPPalettePageUI::Shutdown() {
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

// @ 0x005C8C50
cRefObj* cSPPalettePageUI::GetAndAssign(int a1, AutoRefCount<cRefObj>* out, int a3, int a4) {
  cRefObj* p = GetRef(a1, 0x4785a3d, a3, a4);
  *out = p;
  return *out;
}

// @ 0x005C8FD0
cRefVector::~cRefVector() {
  cRefNode** end = mpEnd;
  for (cRefNode** p = mpBegin; p < end; ++p) {
    if (*p)
      (*p)->Release();
  }
  if (mpBegin && ((int*)mpBegin)[-1] != 0)
    EASTL_allocator_deallocate(mpBegin);
}

extern float g_one;  // 0x01485720
// @ 0x005C9010
cSPPalettePageUI::cSPPalettePageUI()
    : mField8(0), mLayout(0), mSwatch(0), mField14(0), mFloat18(g_one), mFloat1c(g_one),
      mNodes20(), mRefs34() {}

// Deleting destructor (0x005C9070, ??_G) is generated from the inline ~cSPPalettePageUI.

// ---------------------------------------------------------------------------------------------
// cSPPalettePage: the property-driven palette page.
//
// Layout recovered from the disassembly.  cSPPalettePage derives from cSPPalettePageUI (its vtable
// and four data words come first), then holds a cCategoryKey at +0x64, the item vector at +0x70 and
// a couple of key objects further out.

struct cSPProperty;
struct cSPPropertyList {
  cSPProperty* mpFound;
  void Find(unsigned idLo, unsigned idHi, AutoRefCount<cRefObj>* out);   // 0x00 patch point
};

// A "key" object as returned by SP::GetPropertyAsKey: 8 bytes plus an id word at +8.
struct cCategoryKey {
  uint32_t mType;   // +0x00
  uint32_t mInst;   // +0x04
  uint32_t mId;     // +0x08
};

struct cSPPaletteItem {  // refcounted palette entry stored in mItems
  virtual void Accept(int value);
  int AddRef();
  int Release();
};

// The vector<bool> front-end used by both this file and slice s00585d40.
extern "C" void EastlVectorBoolDoInsertValue(void* a, void* b, int c);  // 0x011e0744

class cSPPalettePage : public cSPPalettePageUI {
 public:
  cCategoryKey mCategoryKey;      // +0x64
  eastl::sp_vector<AutoRefCount<cSPPaletteItem> > mItems;  // +0x70
  cCategoryKey mKey88;            // +0x88 (secondary key)
  char mPad94[0xa4 - 0x94];

  // ---- fields written by CommonInit (offsets straight from the disassembly) ----
  uint32_t mLayoutInstanceID;        // +0x0c
  float mItemWidth;                  // +0x14
  float mItemHorizontalOffset;       // +0x18
  float mItemVerticalOffset;         // +0x1c
  float mItemHorizontalSpacing;      // +0x20
  float mItemVerticalSpacing;        // +0x24
  float mItemWidthPercent;           // +0x28
  uint8_t mIgnoreThumbnailGroupOverride;  // +0x2c
  uint8_t mIgnoreResolutionScale;         // +0x2d
  uint8_t mMaxHeightPercent;              // +0x2e
  uint8_t mPad2f;
  float mPageBorderLeft;             // +0x30
  float mPageBorderTop2;             // +0x34
  float mPageBorderRight;            // +0x38
  float mPageBorderBottom;           // +0x3c
  float mItemAspectRatio;            // +0x40
  float mPageBorderTop;              // +0x44 (percent; non-zero means "explicit border")
  uint8_t mMaxHeightFlag;            // +0x48
  uint8_t mUseRelativeLayout;        // +0x49
  uint8_t mUseAbsoluteItemSize;      // +0x4a
  uint8_t mUseAbsoluteBorderSizes;   // +0x4b
  uint8_t mField47;                  // +0x47
  float mItemHeight;                 // +0x4c
  uint32_t mNumRows;                 // +0x50
  uint32_t mNumColumns;              // +0x54
  uint32_t mSetId;                   // +0x58
  uint32_t mPaintId;                 // +0x5c

  float mItemPageHeight;             // +0x10 (the "item height" stored by Init)

  bool CommonInit(int a, int b);                                     // 0x005c85d0
  bool Init(int a, int b, int c, int d, float e);                    // 0x005c8ad0
  void ProcessPagePart(const void* ka, const void* kb, unsigned id); // 0x005c7ff0
};

// ---- the "page part" descriptor walked by the page builder (0x005c8d70) ----
// A page part points at a rectangle provider (+0x10) and at a layout-config object (+0x14).
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
void* EditorObjectError();                            // 0x008de1a0

// cVarListSerializer-style property queries inlined at every call site.
extern cSPProperty* GetProperty(cSPPropertyList* list, unsigned id, void* out);  // 0x0083840
struct cSPProperty {
  cSPProperty* Query(unsigned id, void** out);   // virtual +0x24 at the call sites
  float GetFloat();                              // 0x0041ea70
  int GetInt();                                  // 0x0041e990
  unsigned GetUInt();                            // 0x0041ea00
  bool GetBool();                                // 0x0041e920
};

cSPPropertyList* PropertyManager();              // 0x0067de30
bool GetPropertyAsVector4(cSPPropertyList* list, unsigned id, float* out);  // 0x006a1160
void GetPropertyAsKey(cSPPropertyList* list, unsigned id, void* out);       // 0x006a1250
void GetPropertyAsKeyInstance(cSPPropertyList* list, unsigned id, void* out); // 0x006a12a0
void PagePartInsert(eastl::sp_vector<AutoRefCount<cSPPaletteItem> >* v, AutoRefCount<cSPPaletteItem>* e); // 0x005c8480
void PagePartCopyBackward(AutoRefCount<cSPPaletteItem>* first, AutoRefCount<cSPPaletteItem>* last,
                          AutoRefCount<cSPPaletteItem>* dest);          // 0x005c2fa0
void* PagePartAlloc(unsigned n);                                        // 0x00f473a0
void* EaBulkMove(void* a, const void* b, unsigned n);                   // 0x011e0744
extern float g_half;  // 0x01471064 (0.5f, the grid-cell centring bias)

// @ 0x005C85D0
// Reads the whole palette-page configuration out of the property list `a`, then pre-creates
// mNumRows*mNumColumns palette items.  Returns false if the property lookup itself failed.
bool cSPPalettePage::CommonInit(int a, int b)
{
  AutoRefCount<cRefObj> found(0);                 // [esp+0xc]: the looked-up property
  cSPPropertyList* props = PropertyManager();     // 0x0067de30
  if (found.mpObject) {
    AutoRefCount<cRefObj> tmp(0);
    found = tmp;                                  // release the stale handle
  }
  // PropertyManager::Find(list, id_lo, id_hi, &out) -- id passed as a 64-bit pair.
  props->Find((unsigned)a, (unsigned)b, &found);
  if (!found.mpObject)
    return false;

  cSPProperty* prop = (cSPProperty*)found.mpObject;
  cSPProperty* q;

  if ((q = prop->Query(0x21953e9, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mItemWidth = q->GetFloat();
  if ((q = prop->Query(0x21953ea, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mItemHorizontalOffset = q->GetFloat();
  if ((q = prop->Query(0xb0a1610a, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13)) {
    uint32_t v = (uint32_t)q->GetFloat();
    mIgnoreThumbnailGroupOverride = (uint8_t)v;
    mIgnoreResolutionScale = (uint8_t)(v >> 8);
    *(uint16_t*)&mMaxHeightPercent = (uint16_t)(v >> 16);
  }
  if ((q = prop->Query(0xb0a16109, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mItemVerticalSpacing = q->GetFloat();
  if ((q = prop->Query(0xb0a1610d, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mItemHorizontalSpacing = q->GetFloat();
  if ((q = prop->Query(0xb0a1610c, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mItemVerticalOffset = q->GetFloat();

  mMaxHeightFlag = 0;
  if ((q = prop->Query(0x5adc53b, 0)) && (*(uint16_t*)((char*)q + 0x12) == 1))
    mMaxHeightFlag = *(uint8_t*)q->GetBool();

  float borders[4];
  if (GetPropertyAsVector4(props, 0x5adc149, borders)) {
    mPageBorderRight = borders[0];
    mPageBorderLeft = borders[1];
    mPageBorderBottom = borders[2];
    mPageBorderTop2 = borders[3];
  }

  if ((q = prop->Query(0x5b9a649, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mNumRows = (uint32_t)q->GetFloat();
  if ((q = prop->Query(0x5adc172, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13))
    mItemAspectRatio = q->GetFloat();

  mPageBorderTop = g_one;                        // 0x01485720
  if ((q = prop->Query(0x5adc18d, 0)) && (*(uint16_t*)((char*)q + 0x12) == 13)) {
    uint32_t v = (uint32_t)q->GetFloat();
    mUseRelativeLayout = (uint8_t)v;
    mUseAbsoluteItemSize = (uint8_t)(v >> 8);
    mUseAbsoluteBorderSizes = (uint8_t)(v >> 16);
    mField47 = (uint8_t)(v >> 24);
  }
  if ((q = prop->Query(0x5b5566e, 0)) && (*(uint16_t*)((char*)q + 0x12) == 1))
    *(uint8_t*)&mMaxHeightPercent = *(uint8_t*)q->GetBool();
  if ((q = prop->Query(0x5b55d89, 0)) && (*(uint16_t*)((char*)q + 0x12) == 1))
    *(uint8_t*)((char*)&mMaxHeightPercent + 1) = *(uint8_t*)q->GetBool();
  if ((q = prop->Query(0x30a95517, 0)) && (*(uint16_t*)((char*)q + 0x12) == 9))
    mNumColumns = (uint32_t)q->GetInt();
  if ((q = prop->Query(0x33a8ec2, 0)) && (*(uint16_t*)((char*)q + 0x12) == 9))
    mSetId = (uint32_t)q->GetInt();

  GetPropertyAsKey(props, 0xc84067f7, &mCategoryKey);
  if ((q = prop->Query(0x9591f67, 0)) && (*(uint16_t*)((char*)q + 0x12) == 10))
    mPaintId = q->GetUInt();
  if ((q = prop->Query(0x1b8716d6, 0)) && (*(uint16_t*)((char*)q + 0x12) == 9))
    mSetId = (uint32_t)q->GetInt();

  if (mCategoryKey.mId == 0)
    GetPropertyAsKeyInstance(props, 0x35b12c24, &mLayoutInstanceID);
  else
    mLayoutInstanceID = mCategoryKey.mId;

  if ((q = prop->Query(0x52c798e, 0)) && (*(uint16_t*)((char*)q + 0x12) == 1))
    *(uint8_t*)&mPageBorderTop = *(uint8_t*)q->GetBool();
  if ((q = prop->Query(0x56e8657, 0)) && (*(uint16_t*)((char*)q + 0x12) == 1))
    *(uint8_t*)((char*)&mPageBorderTop + 1) = *(uint8_t*)q->GetBool();

  for (int i = 0; i < (int)(mSetId * mNumRows); ++i) {
    AutoRefCount<cSPPaletteItem> item(0);
    if (mItems.mpEnd < mItems.mpCapacity) {
      AutoRefCount<cSPPaletteItem>* slot = mItems.mpEnd;
      mItems.mpEnd = slot + 1;
      if (slot)
        slot->mpObject = 0;
    } else {
      PagePartInsert(&mItems, &item);            // 0x005c8480
      if (item.mpObject)
        item.mpObject->Release();
    }
  }

  if (found.mpObject)
    found = (cRefObj*)0;                          // release (virtual slot +4)
  return true;
}

// @ 0x005C8AD0
// Initialises the page: CommonInit, stores the item height, asks the editor object error handler
// for the list of page parts and walks it, calling ProcessPagePart for every entry.
bool cSPPalettePage::Init(int a, int b, int c, int d, float e)
{
  if (!CommonInit(a, d))
    return false;
  *(float*)((char*)this + 0x10) = e;              // mItemHeight

  // Build the descriptor consumed by the part list builder and fetch the list of parts.
  uint8_t desc[0x2c];
  *(uint32_t*)(desc + 0x00) = 0;
  *(uint32_t*)(desc + 0x04) = 0;
  *(uint32_t*)(desc + 0x08) = 0;
  *(uint32_t*)(desc + 0x1c) = (*(uint32_t*)((char*)a + 8) & 0xff00ff) | 0x40006d00;
  *(uint32_t*)(desc + 0x14) = 0x13eb898;
  *(uint32_t*)(desc + 0x18) = 0xffffffff;
  *(uint32_t*)(desc + 0x20) = 0xb1b104;
  *(uint32_t*)(desc + 0x24) = 0xffffffff;
  *(uint32_t*)(desc + 0x28) = 0;

  void* err = EditorObjectError();                // 0x008de1a0
  void* parts[3] = { 0, 0, 0 };
  (*(void(__thiscall**)(void*, void*, void*, int))(*(uint32_t*)err + 0x38))(err, parts, desc, 0);

  const void* first = parts[0];
  const void* last = parts[1];
  (void)c;
  if (*(uint8_t*)((char*)this + 0x2c) == 0 && b != 0)
    (void)d;

  uint32_t arg = 0x0;
  while (first != last) {
    ProcessPagePart((const void*)b, first, arg);
    first = (const char*)first + 0xc;
  }

  if (parts[0] != 0 && *(uint32_t*)((char*)parts[0] - 4) != 0)
    operator delete[](parts[0]);
  return true;
}

// @ 0x005C8D70
// SP::cPagePartBig::operator()(int index, Vec4* out): fills `out` with the rectangle of page part
// `index`.  With an explicit border (cfg->b48) the part is inset into the page area and scaled by
// the border percentages; otherwise it is a grid cell whose origin comes from the main window area
// (or from the part's own offsets when cfg->b49 is set).
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

// @ 0x005C90D0
// eastl::vector<AutoRefPtr<cSPEditorPaintLikeThis>>::insert(pos, value) in the "one element"
// flavour: grows the vector to 2*size when full, moves the tail backwards and stores the new
// refcounted handle at `pos`, fixing up the intrusive refcounts.
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
      PagePartCopyBackward((AutoRefCount<cSPPaletteItem>*)vpos,
                           (AutoRefCount<cSPPaletteItem>*)(e - 1),
                           (AutoRefCount<cSPPaletteItem>*)e);           // 0x005c2fa0
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
