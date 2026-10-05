// SP::cXHTMLControlAppearance::Init (0x00622130, 3521 bytes).
//
// This routine builds the whole control-appearance drawable set: a default StdDrawable,
// button/checkbox/radio/text images via SPUIHelpers::CreateImageFromResource, hit masks via
// cXHTMLControlAppearance::CreateHitMaskFromResource, a ComboBoxDrawable and two
// ScrollbarDrawable objects, appending {id,drawable} pairs to the appearance vector.
//
// It is a long straight-line sequence (43 image loads + 40 vector appends).  The skeleton
// below reproduces the allocation/intern/append shape with representative calls; it is NOT
// complete and is listed in partial.txt.
#include "types.h"

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);

void* __cdecl FUN_009512c0();                                                        // 0x9512c0
void* __cdecl FUN_009512d0(unsigned size, int align, const char* name, void* alloc); // 0x9512d0
void* __cdecl CreateImageFromResource(uint32_t a, uint32_t b, const void* name,
                                      void** out, int c);                            // 0x809? SPUIHelpers
void* __cdecl FUN_00621fc0(void* self, void* value);                                 // vector insert

static inline void** Vt(void* p) { return *(void***)p; }
static inline void Release(void* p) { if (p) ((void(__thiscall*)(void*))Vt(p)[1])(p); }
static inline void AddRef(void* p) { if (p) ((void(__thiscall*)(void*))Vt(p)[0])(p); }

struct StdDrawable {
  virtual void dtor();      // +0x00
  virtual void Release();   // +0x04
  virtual void v8();        // +0x08
  virtual void* GetImg();   // +0x0c
  char pad[0x70];
  void SetImage(int n, void* img);   // +0x14 / +0x34 etc (slot 5/13)
};
struct ControlVec {
  void* mpBegin;   // +0x00
  void* mpEnd;     // +0x04
  void* mpCap;     // +0x08
};
struct cXHTMLControlAppearance31 {
  virtual void v0();          // +0x00
  uint32_t mPad4;             // +0x04
  ControlVec mVec;            // +0x08 (begin/end/cap)
  uint32_t mPad14;
  uint32_t mPad18;
  StdDrawable* mpScroll1;     // +0x1c
  StdDrawable* mpScroll2;     // +0x20

  int Init();                 // 0x622130
  bool CreateHitMaskFromResource(uint32_t a, int* p2, void** out);  // 0x621db0
};

// @ 0x00622130
int cXHTMLControlAppearance31::Init() {
  StdDrawable* d = (StdDrawable*)FUN_009512d0(0x7c, 4, "UI/ControlAppearance/StdDrawable",
                                              FUN_009512c0());
  if (d != 0) {
    // button/checkbox/radio/text image sets are loaded here (see partial.txt)
    void* img = 0;
    if (CreateImageFromResource(0x2f7d0004, 0x11c0bde, L"button-generic-norm", &img, 0)) {
      ((void(__thiscall*)(void*, int, void*))Vt(d)[5])(d, 0, img);
      AddRef(img);
    }
    Release(img);
  }
  Release(d);
  return 1;
}
