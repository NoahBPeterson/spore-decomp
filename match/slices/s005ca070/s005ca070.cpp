// slice s005ca070 -- SP::cSPPaletteUI chunk/navigation helpers + SetGlobalProperty, plus
// signature-only stubs for the two large Init/Update functions and the category teardown.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include <new>
#include "types.h"

extern "C" void EASTL_allocator_deallocate(void* p);
void* operator new(unsigned int n, const char* name, int flags, unsigned int debugFlags,
                   const char* file, int line);

#define PV(n) virtual void pv##n();

namespace EA {
namespace UTFWin {
class IUnknown32 {
 public:
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
class IWindow : public IUnknown32 {
 public:
  PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12)
  PV(13) PV(14) PV(15) PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23) PV(24)
  PV(25) PV(26) PV(27) PV(28) PV(29) PV(30)
  virtual void SetFlag(int flag, bool value);  // +0x7c
};
}  // namespace UTFWin
}  // namespace EA
using EA::UTFWin::IWindow;

namespace eastl {
template <typename T>
class sp_vector {
 public:
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  int mAllocator[2];
  sp_vector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~sp_vector();
};
}  // namespace eastl

class cSPUILayout {
 public:
  IWindow* FindWindowByID(unsigned int id, bool recursive);  // 0x008105b0
};

class cSPPaletteCategoryUI {
 public:
  void Update(int deltaTime);    // 0x005c28b0
  void Shutdown();               // 0x005c4e40
  bool IsPaintByNumber();        // 0x005c2cd0
};

class cSPPaletteUI {
 public:
  char pad0[0xc];                                        // vtable + refcount bases
  cSPUILayout* mLayout;                                  // +0xc
  char pad10[0x34 - 0x10];
  eastl::sp_vector<cSPPaletteCategoryUI*> mCategories;   // +0x34
  eastl::sp_vector<int*> mVec48;                         // +0x48
  int mPad5c;                                            // +0x5c
  int mVisibleChunk;                                     // +0x60
  cSPPaletteCategoryUI* mSelectedCategory;               // +0x64

  void UpdateCategories(int deltaTime);                  // 0x005ca980
  int FindCategoryIndex();                               // 0x005ca9c0
  bool IsPaintByNumber();                                // 0x005ca920
  void SetVisibleChunk(int value);                       // 0x005cadb0
  void UpdateNavigationVisiblity();                      // 0x005ca9f0 (out of line)
};

// @ 0x005CA980
void cSPPaletteUI::UpdateCategories(int deltaTime) {
  int count = (int)(mCategories.mpEnd - mCategories.mpBegin);
  for (int i = 0; i < count; i++)
    mCategories.mpBegin[i]->Update(deltaTime);
}

// @ 0x005CA9C0
int cSPPaletteUI::FindCategoryIndex() {
  int count = (int)(mCategories.mpEnd - mCategories.mpBegin);
  for (int i = 0; i < count; i++) {
    if (mSelectedCategory == mCategories.mpBegin[i])
      return i;
  }
  return -1;
}

// @ 0x005CA920
bool cSPPaletteUI::IsPaintByNumber() {
  if (mSelectedCategory)
    return mSelectedCategory->IsPaintByNumber();
  return false;
}

// @ 0x005CADB0
void cSPPaletteUI::SetVisibleChunk(int value) {
  mVisibleChunk = value;
  int count = (int)(mVec48.mpEnd - mVec48.mpBegin);
  unsigned int pages = (unsigned int)(count + 8) / 9;
  IWindow* w = mLayout->FindWindowByID(0x5aec4b8, true);
  if (w)
    w->SetFlag(1, value > 0);
  IWindow* w2 = mLayout->FindWindowByID(0x5aec4b9, true);
  if (w2)
    w2->SetFlag(1, value + 1 < (int)pages);
  UpdateNavigationVisiblity();
}

// ---------------------------------------------------------------------------------------------
// SetGlobalProperty: free __cdecl helper driving the audio system's virtual table.
class cAudioSystem {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
  virtual void SetId(int id);              // +0x38
  virtual void SetFloat(int id, float v);  // +0x3c
  virtual void SetInt(int id, int v);      // +0x40
  PV(17) PV(18) PV(19) PV(20) PV(21)
  virtual void Flush();                    // +0x58
};
cAudioSystem* GetSystemAT();  // 0x00a206f0

// @ 0x005CA880
void SetGlobalProperty(int a1, float a2) {
  cAudioSystem* sys = GetSystemAT();
  if (sys) {
    sys->SetId(0x3cdd1a9);
    sys->SetInt(0x34753a7, a1);
    sys->SetFloat(0x34753aa, a2);
    sys->Flush();
  }
}

// ---------------------------------------------------------------------------------------------
// Large functions: signature-only stubs (partial).
class cSPPaletteSubCategoryUI {
 public:
  bool Init(int a, int b, int c, int d);
  void Shutdown();
};

// @ 0x005CA070
bool cSPPaletteSubCategoryUI::Init(int a, int b, int c, int d) {
  (void)a;
  (void)b;
  (void)c;
  (void)d;
  return false;
}

// @ 0x005CA7B0
void cSPPaletteSubCategoryUI::Shutdown() {}

// @ 0x005CA9F0
// void cSPPaletteUI::UpdateNavigationVisiblity() is defined out of line (partial); declared
// without a body here so SetVisibleChunk emits a real call.

// @ 0x005CAE60
void cPaletteBig(void* a, void* b) {
  (void)a;
  (void)b;
}
