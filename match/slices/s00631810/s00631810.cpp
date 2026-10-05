// SP::cSPPlayModePhotoBrowser helpers. Region 0x631810-0x632779.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>

typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);
typedef void (__thiscall *TF2)(void*, int, int);

struct RefObj3 { virtual void s0(); virtual void s1(); virtual void s2(); };

// @ 0x00631810
void __fastcall FUN_00631810(void* self) { (void)self; }

// @ 0x00631a10
void __fastcall FUN_00631a10(void* self) { (void)self; }

// @ 0x00631b30
void __fastcall FUN_00631b30(void* self) { (void)self; }

// @ 0x00631dc0
extern "C" void __cdecl CALLEE_memcpy_11e0744(void* dst, const void* src, unsigned n);
void __fastcall FUN_00631dc0(void* self) {
  int* s = (int*)self;
  void* end = (void*)s[1];
  void* beg = (void*)s[0];
  CALLEE_memcpy_11e0744(beg, end, 0);
  s[1] += (int)beg - (int)end;
}

// @ 0x00631df0
struct Photo; // opaque
extern "C" void __cdecl FUN_005c8480(void*, void**);
void __fastcall FUN_00631df0(void* self, void* p) {
  int* s = (int*)self;
  void* obj = p;
  if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 4)))(obj);
  if (s[2] < s[3]) {
    int* end = (int*)s[2];
    s[2] = (int)(end + 1);
    if (end != 0) {
      *end = (int)obj;
      if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 4)))(obj);
    }
  } else {
    FUN_005c8480((void*)s[2], &obj);
  }
  if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 8)))(obj);
}

// @ 0x00631e50
void __fastcall FUN_00631e50(void* self) { (void)self; }

// @ 0x006320d0
__declspec(noinline) void __fastcall FUN_006320d0(void*, int, int) {}

// @ 0x00632320
void __fastcall FUN_00632320(void* self, int) { (void)self; }

// @ 0x00632660
extern void __fastcall ExitDeleteMode(void*);
void __fastcall FUN_00632660(void* self) {
  int* s = (int*)self;
  int n = (s[2] - s[1]) >> 2;
  for (int i = n - 1; i >= 0; --i) {
    void* p;
    if (i < ((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    if (*(unsigned char*)((char*)p + 0x38)) FUN_006320d0(self, i, 1);
  }
  for (unsigned i = 0; i < (unsigned)((s[2] - s[1]) >> 2); ++i) {
    void* p;
    if (i < (unsigned)((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
  }
  ExitDeleteMode(self);
}

// @ 0x006326f0
extern void __fastcall ExitMoveMode(void*);
void __fastcall FUN_006326f0(void* self) {
  int* s = (int*)self;
  int n = (s[2] - s[1]) >> 2;
  for (int i = n - 1; i >= 0; --i) {
    void* p;
    if (i < ((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    if (*(unsigned char*)((char*)p + 0x38)) FUN_00632320(self, i);
  }
  for (unsigned i = 0; i < (unsigned)((s[2] - s[1]) >> 2); ++i) {
    void* p;
    if (i < (unsigned)((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
  }
  ExitMoveMode(self);
}
