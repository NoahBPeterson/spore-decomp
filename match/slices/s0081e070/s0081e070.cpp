// Slice s0081e070 -- Spore UI: UI::PropertyEditor / SP::cPropertyUI.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

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
// Not reconstructed -- see partial.txt
// 0081e070, 0081e230, 0081e6c0, 0081eb10, 0081ebe0, 0081ed10, 0081f020
// ===========================================================================
